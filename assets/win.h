#ifndef WIN_H
    #define WIN_H

    #include "assets/controls.h"
    #include "console/console.h"
    #include "elements/camera.h"
    #include "render/engine.h"

    HWND MakeWindow(HINSTANCE inst, int show);

    void Loop(HWND hwnd);

    LRESULT HandleMSG(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void Repaint(HWND hwnd);

    void Update();
    
#endif