#include "win.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    setup_camera();
    InitializeAssets();
    
    HWND wndw = MakeWindow(inst, show);
    Loop(wndw);

    TerminateAssets();
    free_camera();

    return 0;
}