#ifndef CONTROLS_H
    #define CONTROLS_H

    #include "camera.h"

    static const FLOAT      DPOS = 0.125f;
    static const FLOAT      DROT = 0.001745f;

    static const FLOAT      SPEED = 1.0f;
    static const FLOAT      SENSIBILITY = 1.0f;

    static BOOL             HAS_MOUSE = FALSE;

    static LPARAM           PREV_MOUSE_LOCATION;

    static const LONG64     RIGHT = 0;
    static const LONG64     UP = 16;
    static const LONG64     FRONT = 32;

    static BOOL             DIRECTIONAL_MOVE = FALSE;

    extern void directional_move(LONG64 dir, UINT rate);

    void Move(HWND hwnd, WPARAM wParam, LPARAM lParam);
    BOOL IsDirectional();

    void Look(HWND hwnd, WPARAM wParam, LPARAM lParam);
    void Scroll(HWND hwnd, WPARAM wParam, LPARAM LPARAM);

    void OnLeftClick(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void CaptureMouse(HWND hwnd);
    void CenterMouse(HWND hwnd);
    void FreeMouse();

#endif