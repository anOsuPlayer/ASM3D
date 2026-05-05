#include "win.h"
#include "console.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {

    InitializeAssets();
    
    HWND hwnd = MakeWindow(inst, show);
    Loop(hwnd);

    TerminateAssets();

    return 0;
}