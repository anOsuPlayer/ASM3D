#include "win.h"
#include "console.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {

    InitializeHandler();
    InitializeAssets();

    HWND hwnd = MakeWindow(inst, show);
    Loop(hwnd);

    TerminateAssets();
    TerminateHandler();

    return 0;
}