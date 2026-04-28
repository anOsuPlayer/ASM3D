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
        GetWindowWidth(), GetWindowHeight(),
        NULL,
        NULL,
        inst,
        NULL
    );

    ShowWindow(hwnd, show);

    return hwnd;
}

void Loop(HWND hwnd) {
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        Repaint(hwnd);
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
            MakeBuffers();
            return 0;
        }
        case WM_PAINT : {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            SelectObject(bg, hbmbg);
            SelectObject(fg, hbmfg);

            HBRUSH fgbrush = CreateSolidBrush(0x00ff00fe);
            FillRect(fg, &winsize, fgbrush);
            DeleteObject(fgbrush);

            if (HasDebug()) {
                DisplayData(hwnd, fg, msg, wParam, lParam);
            }
            if (GetWinMode() == CONSOLE) {
                DisplayConsole(hwnd, fg, wParam, lParam);
            }
            
            Render(hwnd, bg);
            
            TransparentBlt(bg, 0, 0, winsize.right, winsize.bottom, fg, 0, 0, winsize.right, winsize.bottom, 0x00ff00fe);
            BitBlt(hdc, 0, 0, winsize.right, winsize.bottom, bg, 0, 0, SRCCOPY);
            
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

            SetWindowSize(w, h);
            UpdateBuffers();
            ResetFrameTimes();

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
            return 0;
        }
        
        case WM_KEYDOWN : {
            if (GetWinMode() == RENDER) {
                GetKeyDown(hwnd, wParam, lParam);
            }
            
            Special(hwnd, wParam, lParam);
            return 0;
        }
        case WM_KEYUP : {
            if (GetWinMode() == RENDER) {
                GetKeyUp(hwnd, wParam, lParam);
            }
            
            return 0;
        }
        case WM_CHAR : {
            if (GetWinMode() != RENDER) {
                Type(hwnd, wParam, lParam);
            }

            return 0;
        }

        case WM_LBUTTONDOWN : {
            OnLeftClick(hwnd, wParam, lParam);
            return 0;
        }
        case WM_MOUSEMOVE : {
            if (HasMouse()) {
                Look(hwnd, wParam, lParam);
            }
            return 0;
        }
        case WM_MOUSEWHEEL : {
            Scroll(hwnd, wParam, lParam);
            return 0;
        }
        case WM_DESTROY : {
            DeleteObject(DEFAULT_FONT());

            if (bg) {
                DeleteDC(bg);
                DeleteDC(fg);
                DeleteObject(hbmbg);
                DeleteObject(hbmfg);
            }

            FreeBuffers();

            PostQuitMessage(0);
            return 0;
        }
    }

    DefWindowProc(hwnd, msg, wParam, lParam);
}

void Update(HWND hwnd) {
    Move();
    update();
}

void Repaint(HWND hwnd) {
    Update(hwnd);
    InvalidateRect(hwnd, NULL, FALSE);
}