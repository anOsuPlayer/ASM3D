#include "win.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    HWND wndw = MakeWindow(inst, show);
    
    Loop(wndw);

    return 0;
}