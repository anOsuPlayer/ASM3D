#include "console.h"

void DisplayConsole(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, TEXT_FG);
    SetBkColor(hdc, TEXT_BG);
    SelectObject(hdc, DEFAULT_FONT());

    RECT rec;
    GetClientRect(hwnd, &rec);
    rec.top += 20;
    rec.left += 20;
    rec.bottom -= 20;
    rec.right -= 20;

    CHAR out[500];

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
            sprintf(out, ">> %s", GetText());
            DrawText(hdc, out, -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else if (GetWinState() == 2) {
        StopInput();
        CHAR* cursor = GetConfirmedText();

        CHAR word[100];
        UINT off;

        sscanf(cursor, "%s%n", word, &off);
        cursor += off;

        if (strcmp(word, "exit") == 0) {
            DestroyWindow(hwnd);
        }
        else if (strcmp(word, "make") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Asset creation failed, no asset type was specified \"%s\"\n", GetConfirmedText());
                
                SetWinState(3);
                return;
            }
            else if (strcmp(word, "point") == 0) {
                FLOAT x, y, z;
                UINT color = 0x00ffffff;
                CHAR name[20], group[20];

                INT out = sscanf(cursor, "%f,%f,%f%n", &x, &y, &z, &off);
                cursor += off;

                if (out != 3) {
                    sprintf(GetText(), "Point creation failed, malformed coordinates \"%s\"\n", GetConfirmedText());
                    
                    SetWinState(3);
                    return;
                }
                
                if (sscanf(cursor, "%x%n", &color, &off) <= 0) {
                    sprintf(GetText(), "Unnamed Point created at (%.2f, %.2f, %.2f)\n", word, x, y, z);
                    Point p = MakePoint();
                    p->P.x = x; p->P.y = y; p->P.z = z;
                    p->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                cursor += off;

                if (sscanf(cursor, "%s%n", name, &off) <= 0) {
                    sprintf(GetText(), "Unnamed Point of color \"%x\" created at (%.2f, %.2f, %.2f)", color, x, y, z);
                    Point p = MakePoint();
                    p->P.x = x; p->P.y = y; p->P.z = z;
                    p->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                if (strlen(name) > 20) {
                    sprintf(GetText(), "Point creation failed, GetConfirmedText()valid name \"%s\"\n", name);
                    
                    SetWinState(3);
                    return;
                }

                cursor += off;

                if (sscanf(cursor, "%s%n", group, &off) <= 0) {
                    sprintf(GetText(), "Point \"%s\" of color \"%x\" created at (%.2f, %.2f, %.2f)\n", name, color, x, y, z);
                    Point p = MakePoint();
                    p->P.x = x; p->P.y = y; p->P.z = z;
                    strcpy(p->p->name, name);
                    p->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                if (strlen(group) > 20) {
                    sprintf(GetText(), "Point creation failed, GetConfirmedText()valid group \"%s\"\n", group);
                    
                    SetWinState(3);
                    return;
                }

                sprintf(GetText(), "Point \"%s\" of color \"%x\" created at (%.2f, %.2f, %.2f) in group \"%s\"\n",
                    name, color, x, y, z, group);
                Point p = MakePoint();
                p->P.x = x; p->P.y = y; p->P.z = z;
                strcpy(p->p->name, word);
                strcpy(p->p->group, group);
                p->p->color = color;

                SetRepaint();
                
                SetWinState(3);
                return;
            }
            else if (strcmp(word, "line") == 0) {
                FLOAT x1, y1, z1, x2, y2, z2;
                UINT color = 0x00ffffff;
                CHAR name[20], group[20];

                INT out = sscanf(cursor, "%f,%f,%f;%f,%f,%f%n", &x1, &y1, &z1, &x2, &y2, &z2, &off);
                cursor += off;

                if (out != 6) {
                    sprintf(GetText(), "Line creation failed, malformed coordinates \"%s\"\n", GetConfirmedText());
                    
                    SetWinState(3);
                    return;
                }
                
                if (sscanf(cursor, "%x%n", &color, &off) <= 0) {
                    sprintf(GetText(), "Unnamed Line created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", word, x1, y1, z1, x2, y2, z2);
                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    l->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                cursor += off;

                if (sscanf(cursor, "%s%n", name, &off) <= 0) {
                    sprintf(GetText(), "Unnamed Line of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)",
                        color, x1, y1, z1, x2, y2, z2);
                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    l->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                if (strlen(name) > 20) {
                    sprintf(GetText(), "Line creation failed, GetConfirmedText()valid name \"%s\"\n", name);
                    
                    SetWinState(3);
                    return;
                }

                cursor += off;

                if (sscanf(cursor, "%s%n", group, &off) <= 0) {
                    sprintf(GetText(), "Line \"%s\" of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", name,
                        color, x1, y1, z1, x2, y2, z2);
                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    strcpy(l->p->name, name);
                    l->p->color = color;

                    SetRepaint();
                    
                    SetWinState(3);
                    return;
                }

                if (strlen(group) > 20) {
                    sprintf(GetText(), "Line creation failed, GetConfirmedText()valid group \"%s\"\n", group);
                    
                    SetWinState(3);
                    return;
                }

                sprintf(GetText(), "Line \"%s\" of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f) in group \"%s\"\n",
                    name, color, x1, y1, z1, x2, y2, z2, group);
                Line l = MakeLine();
                l->A.x = x1; l->A.y = y1; l->A.z = z1;
                l->B.x = x2; l->B.y = y2; l->B.z = z2;
                strcpy(l->p->name, name);
                strcpy(l->p->group, group);
                l->p->color = color;

                SetRepaint();

                SetWinState(3);
                return;
            }

            sprintf(GetText(), "Unknown Asset type \"%s\"\n", word);
        }
        else if (strcmp(word, "delete") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Asset deletion failed, no Asset type was specified \"%s\"\n", GetConfirmedText());
            }
            else if (strcmp(word, "group") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset deletion failed, no Group was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    DeleteGroup(word);
                    sprintf(GetText(), "Deleting Group \"%s\"\n", word);
                    
                    SetRepaint();
                }
            }
            else if (strcmp(word, "point") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset deletion failed, no Point was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    DeletePoint(word);
                    sprintf(GetText(), "Deleting Point \"%s\"\n", word);
                    
                    SetRepaint();
                }

            }
            else if (strcmp(word, "line") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset deletion failed, no Line was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    DeleteLine(word);
                    sprintf(GetText(), "Deleting Line \"%s\"\n", word);
                    
                    SetRepaint();
                }
            }
            else {
                DeleteAsset(word);
                sprintf(GetText(), "Deleting Asset \"%s\"\n", word);

                SetRepaint();
            }
        }
        else if (strcmp(word, "show") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Asset manipulation failed, no Asset type was specified \"%s\"\n", GetConfirmedText());
            }
            else if (strcmp(word, "group") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Group was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowGroup(word, TRUE);
                    sprintf(GetText(), "Group \"%s\" is now visible\n", word);
                    
                    SetRepaint();
                }
            }
            else if (strcmp(word, "point") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Point was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowPoint(word, TRUE);
                    sprintf(GetText(), "Point \"%s\" is now visible\n", word);
                    
                    SetRepaint();
                }

            }
            else if (strcmp(word, "line") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Line was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowLine(word, TRUE);
                    sprintf(GetText(), "Line \"%s\" is now visible\n", word);
                    
                    SetRepaint();
                }
            }
            else {
                ShowAsset(word, TRUE);
                sprintf(GetText(), "Asset \"%s\" is now visible\n", word);

                SetRepaint();
            }
        }
        else if (strcmp(word, "hide") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Asset manipulation failed, no Asset type was specified \"%s\"\n", GetConfirmedText());
            }
            else if (strcmp(word, "group") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Group was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowGroup(word, FALSE);
                    sprintf(GetText(), "Group \"%s\" is now hidden\n", word);
                    
                    SetRepaint();
                }
            }
            else if (strcmp(word, "point") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Point was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowPoint(word, FALSE);
                    sprintf(GetText(), "Point \"%s\" is now hidden\n", word);
                    
                    SetRepaint();
                }

            }
            else if (strcmp(word, "line") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Asset manipulation failed, no Line was specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    ShowLine(word, FALSE);
                    sprintf(GetText(), "Line \"%s\" is now hidden\n", word);
                    
                    SetRepaint();
                }
            }
            else {
                ShowAsset(word, FALSE);
                sprintf(GetText(), "Asset \"%s\" is now hidden\n", word);

                SetRepaint();
            }
        }
        else if (strcmp(word, "fps") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                if (GetFPS() == -1) {
                    sprintf(GetText(), "Current FPS cap is unbound\n");
                }
                else {
                    sprintf(GetText(), "Current FPS cap is set to \"%u\"\n", GetFPS());
                }
            }
            else if (strcmp(word, "cap") == 0) {
                INT CAP;

                out = sscanf(cursor, "%d%n", &CAP, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "No FPS cap provided \"%s\"\n", GetConfirmedText());
                }
                else {
                    if (CAP < 1 || CAP > 10000) {
                        sprintf(GetText(), "Invalid FPS cap \"%d\"\n", CAP);
                    }
                    else {
                        sprintf(GetText(), "FPS cap set to \"%d\"\n", CAP);
                        SetFPS(CAP);
                    }
                }
            }
            else if (strcmp(word, "uncap") == 0) {
                sprintf(GetText(), "FPS cap removed\n");
                SetFPS(-1);
            }
            else {
                sprintf(GetText(), "Unknown FPS command option \"%s\"\n", GetConfirmedText());
            }
        }
        else {
            sprintf(GetText(), "Invalid command \"%s\"\n", GetConfirmedText());
        }

        SetWinState(3);
    }
    else if (GetWinState() == 3) {
        static INT size = -1;

        if (size == -1) {
            SetInput(TRUE);
            size = GetTextSize();
            SetRepaint(TRUE);
        }
        else if (GetConfirmedSize() == 0 || GetTextSize() > size) {
            SetWinState(-1);
            SetInput(FALSE);
            size = -1;
        }
        else {
            DrawText(hdc, GetText(), -1, &rec, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
        }
    }
    else {
        ClearText();
        ClearConfirmed();
        SetWinState(0);

        SetWinMode(RENDER);
    }
}