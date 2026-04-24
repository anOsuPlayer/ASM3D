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

    HWND wndw = CreateWindowEx(
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

    ShowWindow(wndw, show);
    SetTimer(wndw, 1, 8, NULL);
}

void Loop(HWND wndw) {
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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

            if (GetWinMode() == LOAD_ASSETS) {
                DisplayAssetLoader(hwnd, hdc, wParam, lParam);
            }
            else if (GetWinMode() == CREATE_ASSETS) {
                DisplayAssetCreator(hwnd, hdc, wParam, lParam);
            }

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            Render(hwnd, hdc);
            if (HasDebug()) {
                DisplayData(hwnd, hdc, msg, wParam, lParam);
            }

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

            Width = ((FLOAT) w);
            Height = ((FLOAT) h);

            AR =  Width / Height;
            SetRepaint();
            return 0;
        }
        
        case WM_KEYDOWN : {
            if (GetWinMode() == RENDER) {
                Move(hwnd, wParam, lParam);
            }

            Special(hwnd, wParam, lParam);
            SetRepaint();
            return 0;
        }
        case WM_CHAR : {
            if (GetWinMode() != RENDER) {
                Type(hwnd, wParam, lParam);
            }

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

            PostQuitMessage(0);
            return 0;
        }
    }

    DefWindowProc(hwnd, msg, wParam, lParam);
}

void Repaint(HWND hwnd) {
    update();
    InvalidateRect(hwnd, NULL, TRUE);
}