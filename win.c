#include "win.h"

HWND MakeWindow(HINSTANCE inst, int show) {
    const char CLASS_NAME[] = "Default";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = HandleMSG;
    wc.hInstance = inst;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(0x00000000);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        WIN_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIN_WIDTH, WIN_HEIGHT,
        NULL,
        NULL,
        inst,
        NULL
    );

    ShowWindow(hwnd, show);
    SetTimer(hwnd, 1, 0, NULL);

    return hwnd;
}

void Loop(HWND hwnd) {
    MSG message;
    while (GetMessage(&message, NULL, 0, 0) && IsRunning()) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    DestroyWindow(hwnd);
}

LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HDC bg;
    static HDC fg;
    static HBITMAP hbmbg;
    static HBITMAP hbmfg;
    static RECT winsize;

    switch (msg) {
        case WM_CREATE : {
            return 0;
        }
        case WM_TIMER : {
            if (CanRepaint()) {
                Repaint(hwnd);
                ClearRepaint();
            }
            return 0;
        }
        case WM_PAINT : {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            SelectObject(bg, hbmbg);
            SelectObject(fg, hbmfg);

            HBRUSH hKeyBrush = CreateSolidBrush(0x00ff00ff);
            FillRect(fg, &winsize, hKeyBrush);
            DeleteObject(hKeyBrush);

            if (HasDebug()) {
                DisplayData(hwnd, fg, msg, wParam, lParam);
            }
            Render(hwnd, bg);

            BitBlt(hdc, 0, 0, winsize.right, winsize.bottom, bg, 0, 0, SRCCOPY);
            TransparentBlt(hdc, 0, 0, winsize.right, winsize.bottom, fg, 0, 0, winsize.right, winsize.bottom, 0x00ff00ff);
            
            clock_gettime(CLOCK_MONOTONIC, &end);
            LONG delta = ((end.tv_sec * 1000000000L + end.tv_nsec) - (start.tv_sec * 1000000000L + start.tv_nsec));
            LONG nsdiff = GetFrameSize() - delta;
            
            if (nsdiff > 0) {
                struct timespec tdelta;
                tdelta.tv_sec = nsdiff / 1000000000L;
                tdelta.tv_nsec = nsdiff % 1000000000L;
                SetFrameTime(nsdiff + delta);
                nanosleep(&tdelta, NULL);
            }
            else {
                SetFrameTime(delta);
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_KILLFOCUS : {
            FreeMouse();
            return 0;
        }
        case WM_SIZE : {
            INT w = LOWORD(lParam);
            INT h = HIWORD(lParam);
            
            winsize.right = w;
            winsize.bottom = h;

            Width = ((FLOAT) w);
            Height = ((FLOAT) h);

            AR =  Width / Height;

            HDC hdc = GetDC(hwnd);
        
            if (bg) {
                DeleteDC(bg);
                DeleteDC(fg);
                DeleteObject(hbmbg);
                DeleteObject(hbmfg);
            }

            bg = CreateCompatibleDC(hdc);
            fg = CreateCompatibleDC(hdc);
            hbmbg = CreateCompatibleBitmap(hdc, w, h);
            hbmfg = CreateCompatibleBitmap(hdc, w, h);

            SelectObject(bg, hbmbg);
            SelectObject(fg, hbmfg);

            ReleaseDC(hwnd, hdc);

            SetRepaint();
            return 0;
        }
        case WM_KEYDOWN : {
            Move(hwnd, wParam, lParam);
            SetRepaint();
            return 0;
        }
        case WM_LBUTTONDOWN : {
            OnLeftClick(hwnd, wParam, lParam);
            SetRepaint();
            return 0;
        }
        case WM_MOUSEMOVE : {
            if (HasMouse()) {
                Look(hwnd, wParam, lParam);
                SetRepaint();
            }
            return 0;
        }
        case WM_MOUSEWHEEL : {
            Scroll(hwnd, wParam, lParam);
            SetRepaint();
            return 0;
        }
        case WM_DESTROY : {
            DeleteObject(DEFAULT_FONT());
            DeleteObject(BACKGROUND());

            PostQuitMessage(0);
            return 0;
        }
    }

    DefWindowProc(hwnd, msg, wParam, lParam);
}

void Repaint(HWND hwnd) {
    update();
    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}