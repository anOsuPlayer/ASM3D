#include "win.h"
#include "console.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    setup_camera();
    InitializeAssets();
    
    HWND hwnd = MakeWindow(inst, show);
    Loop(hwnd);

    TerminateAssets();
    free_camera();

    return 0;
}