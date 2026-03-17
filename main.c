#include "win.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    HWND wndw = MakeWindow(inst, show);

    setup_camera();
    InitializeAssets();

    Loop(wndw);

    TerminateAssets();
    free_camera();

    return 0;
}