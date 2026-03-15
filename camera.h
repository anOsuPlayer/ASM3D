#ifndef CAMERA_H
    #define CAMERA_H

    #include "math.h"

    extern Vec              QUATERNION;
    extern Matrix           VIEW;
    extern Matrix           PERSPECTIVE;

    extern struct vec_t     Angle;
    extern struct vec_t     Pos;

    extern FLOAT            FOV;
    extern FLOAT            AR;

    extern void setup_camera();
    extern void free_camera();

    extern void update();

    extern void update_quaternion();
    extern void update_view();
    extern void update_perspective();

    void DisplayData(HWND wndw, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam);

#endif