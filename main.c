#include "win.h"
#include "console.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {

    InitializeAssets();
    InitializeHandler();

    HWND hwnd = MakeWindow(inst, show);
    Loop(hwnd);

    TerminateHandler();
    TerminateAssets();

    return 0;
}