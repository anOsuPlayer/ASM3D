#ifndef WIN_H
    #define WIN_H

    #include "camera.h"
    #include "controls.h"
    #include "engine.h"

    HWND MakeWindow(HINSTANCE inst, int show);

    void Loop(HWND wndw);

    LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static UINT REPAINT_INDEX = 0;
    void Repaint(HWND hwnd);

#endif