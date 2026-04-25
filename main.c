#include "win.h"
#include "console.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    setup_camera();
    InitializeAssets();
    
    HWND hwnd = MakeWindow(inst, show);
    InitializeConsole(hwnd);
    Loop(hwnd);

    TerminateConsole();
    TerminateAssets();
    free_camera();

    return 0;
}