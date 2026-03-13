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
}

void Loop(HWND wndw) {
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        DispatchMessage(&message);
    }
}

LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT : {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            DisplayData(hwnd, hdc, msg, wParam, lParam);
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY : {
            PostQuitMessage(0);
            return 0;
        }
    }

    DefWindowProc(hwnd, msg, wParam, lParam);
}