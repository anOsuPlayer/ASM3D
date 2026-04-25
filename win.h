#ifndef WIN_H
    #define WIN_H

    #include "camera.h"
    #include "controls.h"
    #include "engine.h"
    #include "console.h"

    HWND MakeWindow(HINSTANCE inst, int show);

    void Loop(HWND hwnd);

    LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void Repaint(HWND hwnd);

#endif