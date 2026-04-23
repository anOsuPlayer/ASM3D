#include "loader.h"

void DisplayAssetLoader(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);
    SelectObject(hdc, DEFAULT_FONT());

    RECT rec;
    GetClientRect(hwnd, &rec);
    rec.top += 20;
    rec.left += 20;
    rec.bottom -= 20;
    rec.right -= 20;

    CHAR out[200];

    if (GetWinState() == 0) {
        ClearText();
        ClearConfirmed();
        SetInput();
        
        SetWinState(1);
    }
    else if (GetWinState() == 1) {
        if (GetConfirmedSize() != 0) {
            SetWinState(2);
        }
        else {
            sprintf(out, "Insert filename to load assets: %s", GetText());
    
            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 2) {
        StopInput();
        FILE* handle = fopen(GetConfirmedText(), "r");
        
        if (handle == NULL) {
            SetWinState(100);
        }
        else {
            SetWinState(100);
        }
    }
    else if (GetWinState() == 100) {
        if (GetConfirmedSize() == 0) {
            SetWinState(-1);
        }
        else {
            sprintf(out, "Asset loading failed: file \"%s\" doesn't exist.", GetConfirmedText());

            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else {
        ClearText();
        ClearConfirmed();

        SetWinMode(RENDER);
    }
}

void DisplayAssetCreator(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);
    SelectObject(hdc, DEFAULT_FONT());

    RECT rec;
    GetClientRect(hwnd, &rec);
    rec.top += 20;
    rec.left += 20;
    rec.bottom -= 20;
    rec.right -= 20;

    CHAR out[200];

    if (GetWinState() == 0) {
        ClearText();
        ClearConfirmed();
        SetInput();
        
        SetWinState(1);
    }
    else if (GetWinState() == 1) {
        if (GetConfirmedSize() != 0) {
            SetWinState(2);
        }
        else {
            sprintf(out, "Insert asset type (1: Point, 2: Line, 3: Surface): %s", GetText());
    
            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 2) {
        StopInput();

        UINT element;
        UINT success = sscanf(GetConfirmedText(), "%u", &element);
        
        if (!success || element < 1 || element > 3) {
            SetWinState(100);
        }
        else {
            switch (element) {
                case 1 : {
                    ClearConfirmed();
                    SetWinState(3);
                    break;
                }
                case 2 : {
                    ClearConfirmed();
                    SetWinState(5);
                    break;
                }
                case 3 : {

                }
            }
        }
    }
    else if (GetWinState() == 3) {
        SetInput();

        if (GetConfirmedSize() != 0) {
            SetWinState(4);
        }
        else {
            sprintf(out, "Input point coordinates in format \"x, y, z\": %s", GetText());
    
            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 4) {
        StopInput();

        if (GetConfirmedSize() == 0) {
            SetWinState(-1);
        }
        else {
            FLOAT x, y, z;
            UINT success = sscanf(GetConfirmedText(), "%f, %f, %f", &x, &y, &z);

            if (success != 3) {
                SetWinState(101);
            }
            else {
                sprintf(out, "Point created at (%.02f, %.02f, %.02f).", x, y, z);
        
                DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

                Point p = MakePoint();
                p->x = x; p->y = y; p->z = z;
            }

        }
    }
    else if (GetWinState() == 5) {
        SetInput();

        if (GetConfirmedSize() != 0) {
            SetWinState(6);
        }
        else {
            sprintf(out, "Input line coordinates in format \"x1, y1, z1; x2, y2, z2\": %s", GetText());
    
            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 6) {
        StopInput();

        if (GetConfirmedSize() == 0) {
            SetWinState(-1);
        }
        else {
            FLOAT x1, y1, z1, x2, y2, z2;
            UINT success = sscanf(GetConfirmedText(), "%f, %f, %f; %f, %f, %f", &x1, &y1, &z1, &x2, &y2, &z2);

            if (success != 6) {
                SetWinState(101);
            }
            else {
                sprintf(out, "Line created between (%.02f, %.02f, %.02f) and (%.02f, %.02f, %.02f).", x1, y1, z1, x2, y2, z2);
        
                DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

                Line l = MakeLine();
                l->A.x = x1; l->A.y = y1; l->A.z = z1;
                l->B.x = x2; l->B.y = y2; l->B.z = z2;
            }

        }
    }
    else if (GetWinState() == 100) {
        StopInput();

        if (GetConfirmedSize() == 0) {
            SetWinState(-1);
        }
        else {
            sprintf(out, "Asset creation failed: \"%s\" is no valid asset.", GetConfirmedText());

            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 101) {
        StopInput();

        if (GetConfirmedSize() == 0) {
            SetWinState(-1);
        }
        else {
            sprintf(out, "Asset creation failed: (\"%s\") are no valid coordinates.", GetConfirmedText());

            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else {
        ClearText();
        ClearConfirmed();

        SetWinMode(RENDER);
    }
}