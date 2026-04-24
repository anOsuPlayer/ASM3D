#include "camera.h"
#include "controls.h"

void DisplayData(HWND hwnd, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);
    SelectObject(hdc, DEFAULT_FONT());

    RECT rec;
    GetClientRect(hwnd, &rec);
    rec.top += 20;
    rec.left += 20;
    rec.bottom -= 20;
    rec.right -= 20;

    CHAR str1[200];
    sprintf(str1, "x: %+.03f, y: %+.03f, z: %+.03f\nyaw: %+.03f, pitch: %+.03f, roll: %+.03f\nFOV: %.01f, AR: %.04f\nMovement: %s",
        Pos.x, Pos.y, Pos.z,
        Angle.x, Angle.y, Angle.z,
        FOV, AR,
        (IsDirectional() ? "Directional" : "Absolute"));
    
    DrawText(hdc, str1, -1, &rec, DT_CENTER);

    CHAR str2[500];
    sprintf(str2, "QUATERNION:\n%+.03f %+.03f %+.03f %+.03f\n" \
        "VIEW :\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f\n" \
        "PERSPECTIVE :\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f\n%+.02f %+.02f %+.02f %+.02f",
        QUATERNION->x, QUATERNION->y, QUATERNION->z, QUATERNION->w,
        VIEW->r0.x, VIEW->r0.y, VIEW->r0.z, VIEW->r0.w, 
        VIEW->r1.x, VIEW->r1.y, VIEW->r1.z, VIEW->r1.w, 
        VIEW->r2.x, VIEW->r2.y, VIEW->r2.z, VIEW->r2.w, 
        VIEW->r3.x, VIEW->r3.y, VIEW->r3.z, VIEW->r3.w,
        PERSPECTIVE->r0.x, PERSPECTIVE->r0.y, PERSPECTIVE->r0.z, PERSPECTIVE->r0.w,
        PERSPECTIVE->r1.x, PERSPECTIVE->r1.y, PERSPECTIVE->r1.z, PERSPECTIVE->r1.w,
        PERSPECTIVE->r2.x, PERSPECTIVE->r2.y, PERSPECTIVE->r2.z, PERSPECTIVE->r2.w,
        PERSPECTIVE->r3.x, PERSPECTIVE->r3.y, PERSPECTIVE->r3.z, PERSPECTIVE->r3.w 
    );
    
    DrawText(hdc, str2, -1, &rec, DT_LEFT);

    CHAR str3[500];
    sprintf(str3, "frametime: %9lluns\n FPS: %11.02f", GetFrameTime(), 1e9f / GetFrameTime());

    DrawText(hdc, str3, -1, &rec, DT_RIGHT);
}