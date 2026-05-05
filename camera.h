#ifndef CAMERA_H
    #define CAMERA_H

    #include "math.h"
    #include "phisics.h"

    typedef struct camera_t {
        Vec         QUATERNION;
        Matrix      VIEW;
        Matrix      PERSPECTIVE;

        Transform   TRANSFORM;

        FLOAT       FOV;
        FLOAT       Near, Far;

        CHAR        name[20];
    } *Camera;

    extern volatile Camera  CCURRENT;

    extern FLOAT            Width;
    extern FLOAT            Height;
    
    extern FLOAT            AR;

    void InitializeCameras();
    void TerminateCameras();

    Camera MakeCamera();
    void FreeCamera(Camera c);

    void SwitchCamera(const char* to);
    void ConfirmCameraSwitch();

    void DeleteCamera(const char* c);

    extern void update();

    extern void update_quaternion();
    extern void update_view();
    extern void update_perspective();

    void DisplayData(HWND wndw, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam);

#endif