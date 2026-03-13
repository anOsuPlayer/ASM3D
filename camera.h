#ifndef CAMERA_H
    #define CAMERA_H

    #include "math.h"

    extern Matrix           VIEW;
    extern Matrix           PERSPECTIVE;
    extern Vec              QUATERNION;

    extern struct vec_t     Angle;
    extern struct vec_t     Pos;

    extern void setup_camera();
    extern void free_camera();

    void DisplayData(HWND wndw, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam);

#endif