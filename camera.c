#include "camera.h"

void DisplayData(HWND hwnd, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);

    RECT r = { 20, 20, 400, 200 };

    CHAR str[200];
    sprintf(str, "x: %.03f, y: %.03f, z: %.03f\nyaw: %.03f, pitch: %.03f, roll: %.03f\nFOV: %.01f, AR: %.04f\nqx: %.03f, qy: %.03f, qz: %.03f, qw: %.03f",
        Pos.x, Pos.y, Pos.z,
        Angle.x, Angle.y, Angle.z,
        FOV, AR,
        QUATERNION->x, QUATERNION->y, QUATERNION->z, QUATERNION->w);
    
    DrawText(hdc, str, -1, &r, DT_LEFT);
}