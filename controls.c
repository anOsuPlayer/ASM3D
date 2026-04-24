#include "controls.h"

BOOL HasMouse() {
    return HAS_MOUSE;
}

void Move(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    switch (wParam) {
        case 'W' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(FRONT, ((GetKeyState(VK_SHIFT) < 0) ? 2 : 1));
            }
            else {
                Pos.x += ((GetKeyState(VK_SHIFT) < 0) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'S' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(FRONT, ((GetKeyState(VK_SHIFT) < 0) ? -2 : -1));
            }
            else {
                Pos.x -= ((GetKeyState(VK_SHIFT) < 0) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'D' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(RIGHT, ((GetKeyState(VK_SHIFT) < 0) ? 2 : 1));
            }
            else {
                Pos.y += ((GetKeyState(VK_SHIFT) < 0) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'A' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(RIGHT, ((GetKeyState(VK_SHIFT) < 0) ? -2 : -1));
            }
            else {
                Pos.y -= ((GetKeyState(VK_SHIFT) < 0) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'E' : {
            Angle.z += ((GetKeyState(VK_SHIFT) < 0) ? 1.0f : 2.0f) * 5.0f * DROT;
            break;
        }
        case 'Q' : {
            Angle.z -= ((GetKeyState(VK_SHIFT) < 0) ? 1.0f : 2.0f) * 5.0f * DROT;
            break;
        }
        case 'R' : {
            if (GetKeyState(VK_SHIFT) < 0) {
                FLOAT dx = (1-Pos.x)/10, dy = (1-Pos.y)/10, dz = (1-Pos.z)/10;
                FLOAT dyaw = (-Angle.x)/10, dpitch = (-Angle.y)/10, droll = (-Angle.z)/10;
                FLOAT df = (65.0f-FOV)/10;
    
                Pos.x += dx; Pos.y += dy; Pos.z += dz;
                Angle.x += dyaw; Angle.y += dpitch; Angle.z += droll;
                FOV += df;
            }
            else {
                Pos.x = Pos.y = Pos.z = 1.0f;
                Angle.x = Angle.y = Angle.z = 0.0f;
                FOV = 65.0f;
            }
            break;
        }
        case ' ' : {
            if (DIRECTIONAL_MOVE) {
                directional_move(UP, ((GetKeyState(VK_SHIFT) < 0) ? 2 : 1));
            }
            else {
                Pos.z += ((GetKeyState(VK_SHIFT) < 0) ? 2*DPOS : DPOS);
            }
            break;
        }
        case 'N' : {
            if (GetKeyState(VK_SHIFT) < 0) {
                SetWinMode(LOAD_ASSETS);
            }
            else {
                SetWinMode(CREATE_ASSETS);
            }
            break;
        }
        case VK_CONTROL : {
            if (DIRECTIONAL_MOVE) {
                directional_move(UP, ((GetKeyState(VK_SHIFT) < 0) ? -2 : -1));
            }
            else {
                Pos.z -= (GetKeyState(VK_SHIFT) ? 2*DPOS : DPOS);
            }
            break;
        }
        case VK_TAB : {
            DIRECTIONAL_MOVE = (DIRECTIONAL_MOVE) ? FALSE : TRUE;
            break;
        }
        case VK_F3 : {
            HasDebug() ? HideDebug() : ShowDebug();
            break;
        }
    }
}

BOOL IsDirectional() {
    return DIRECTIONAL_MOVE;
}

void Type(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    unsigned char c = (unsigned char) wParam;
    
    switch (c) {
        case '\r' : {
            ConfirmText();
            break;
        }
        case '\b' : {
            if (CanInput()) {
                EraseChar();
            }
            break;
        }
        default : {
            if (CanInput()) {
                if (c >= 32 && c <= 127) {
                    AppendChar(c);
                }
            }
            break;
        }
    }
}

void Special(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    switch (wParam) {
        case VK_ESCAPE : {
            if (GetWinMode() != RENDER) {
                SetWinMode(RENDER);
            }
            else {
                FreeMouse(hwnd);
            }
            break;
        }
    }
}

void Look(HWND hwnd, WPARAM wParam, LPARAM lParam) {
    if (HAS_MOUSE) {
        if (lParam != PREV_MOUSE_LOCATION && lParam != ((100) | (100 << 16))) {
            INT x = LOWORD(lParam);
            INT y = HIWORD(lParam);
        
            FLOAT dyaw = (FLOAT) x-100;
            FLOAT dpitch = (FLOAT) 100-y;

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

    POINT tl = { 0, 0 }, br = { 200, 200 };
    ClientToScreen(hwnd, &tl);
    ClientToScreen(hwnd, &br);

    RECT clip = { tl.x, tl.y, br.x, br.y };

    ClipCursor(&clip);
    ShowCursor(FALSE);
}

void CenterMouse(HWND hwnd) {
    POINT p = { 100, 100 };
    ClientToScreen(hwnd, &p);

    SetCursorPos(p.x, p.y);
}

void FreeMouse() {
    HAS_MOUSE = FALSE;

    ClipCursor(NULL);
    ShowCursor(TRUE);
}