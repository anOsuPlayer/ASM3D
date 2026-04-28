#ifndef CONTROLS_H
    #define CONTROLS_H

    #include "engine.h"
    #include "text.h"

    extern FLOAT            DPOS;
    extern FLOAT            DROT;

    extern FLOAT            SPEED;
    extern FLOAT            SENS;

    BOOL HasMouse();

    void HideMouse();
    void ShowMouse();

    static const LONG64     DMOV_RIGHT = 0;
    static const LONG64     DMOV_UP = 16;
    static const LONG64     DMOV_FRONT = 32;

    extern void directional_move(LONG64 dir, UINT rate);

    void GetKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
    void GetKeyUp(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void Move();
    BOOL IsDirectional();

    void Type(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void Special(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void Look(HWND hwnd, WPARAM wParam, LPARAM lParam);
    void Scroll(HWND hwnd, WPARAM wParam, LPARAM LPARAM);

    void OnLeftClick(HWND hwnd, WPARAM wParam, LPARAM lParam);

    void CaptureMouse(HWND hwnd);
    void CenterMouse(HWND hwnd);
    void FreeMouse();

#endif