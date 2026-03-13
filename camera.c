#include "camera.h"

void DisplayData(HWND hwnd, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);

    RECT r = { 20, 20, 500, 100 };

    CHAR str[100];
    sprintf(str, "x: %.03f, y: %.03f, z: %.03f\nyaw: %.03f, pitch: %.03f, roll: %.03f",
        Pos.x, Pos.y, Pos.z, Angle.x, Angle.y, Angle.z);
    
    DrawText(hdc, str, -1, &r, DT_LEFT);
}