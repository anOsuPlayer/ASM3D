#include "controls.h"

void Move(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    switch (wParam) {
        case 'W' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(FRONT, (GetKeyState(VK_SHIFT) ? 2 : 1));
            }
            else {
                Pos.x += (GetKeyState(VK_SHIFT) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'S' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(FRONT, (GetKeyState(VK_SHIFT) ? -2 : -1));
            }
            else {
                Pos.x -= (GetKeyState(VK_SHIFT) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'D' : {
            Pos.y += (GetKeyState(VK_SHIFT) ? 2*DPOS : DPOS);
            break;
        }
        case 'A' : {
            Pos.y -= (GetKeyState(VK_SHIFT) ? 2*DPOS : DPOS);
            break;
        }
        case 'E' : {
            Angle.z += (GetKeyState(VK_SHIFT) & 1) * 2 * 5 * DROT;
            break;
        }
        case 'Q' : {
            Angle.z -= (GetKeyState(VK_SHIFT) & 1) * 2 * 5 * DROT;
            break;
        }
        case 'R' : {
            Pos.x = Pos.y = Pos.z = 0;
            Angle.x = Angle.y = Angle.z = 0;
            FOV = 70.0;
            break;
        }
        case ' ' : {
            Pos.z += DPOS;
            break;
        }
        case VK_CONTROL : {
            Pos.z -= DPOS;
            break;
        }
        case VK_TAB : {
            DIRECTIONAL_MOVE = (DIRECTIONAL_MOVE) ? FALSE : TRUE;
            break;
        }
        case VK_ESCAPE : {
            FreeMouse(hwnd);
            break;
        }
    }
}

BOOL IsDirectional() {
    return DIRECTIONAL_MOVE;
}

void Look(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    if (HAS_MOUSE) {
        if (lParam != PREV_MOUSE_LOCATION && lParam != ((25) | (25 << 16))) {
            INT x = LOWORD(lParam);
            INT y = HIWORD(lParam);
        
            FLOAT dyaw = (FLOAT) x-25;
            FLOAT dpitch = (FLOAT) 25-y;

            Angle.x += dyaw * DROT;
            Angle.y -= dpitch * DROT;
            
            CenterMouse(hwnd);
        }
        
        PREV_MOUSE_LOCATION = lParam;
    }
}

void Scroll(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    INT scroll = -GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

    if (FOV + scroll <= 150.0f && FOV + scroll >= 30.0f) {
        FOV += (FLOAT) scroll;
    }
}

void OnLeftClick(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    if (!HAS_MOUSE) {
        CaptureMouse(hwnd);
    }
}

void CaptureMouse(HWND hwnd) {
    HAS_MOUSE = TRUE;
    CenterMouse(hwnd);

    POINT tl = { 0, 0 }, br = { 50, 50 };
    ClientToScreen(hwnd, &tl);
    ClientToScreen(hwnd, &br);

    RECT clip = { tl.x, tl.y, br.x, br.y };

    ClipCursor(&clip);
    ShowCursor(FALSE);
}

void CenterMouse(HWND hwnd) {
    POINT p = { 25, 25 };
    ClientToScreen(hwnd, &p);

    SetCursorPos(p.x, p.y);
}

void FreeMouse() {
    HAS_MOUSE = FALSE;

    ClipCursor(NULL);
    ShowCursor(TRUE);
}