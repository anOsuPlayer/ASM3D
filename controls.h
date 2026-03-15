#ifndef CONTROLS_H
    #define CONTROLS_H

    #include "camera.h"

    static const FLOAT      DPOS = 0.125f;
    static const FLOAT      DROT = 0.001745f;

    static const FLOAT      SPEED = 1.0f;
    static const FLOAT      SENSIBILITY = 1.0f;

    static BOOL             HAS_MOUSE = FALSE;

    static LPARAM           PREV_MOUSE_LOCATION;

    void Move(HWND hwnd, WPARAM wParam, LPARAM lParam);
    void Look(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void OnLeftClick(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void CaptureMouse(HWND hwnd);
    void CenterMouse(HWND hwnd);
    void FreeMouse();

#endif