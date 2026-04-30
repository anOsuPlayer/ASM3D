#include "console.h"

void DisplayConsole(HWND hwnd, HDC hdc, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, GetFontFG());
    SetBkColor(hdc, GetFontBG());
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
            PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
        else if (strcmp(word, "tp") == 0 || strcmp(word, "warp") == 0) {
            FLOAT x, y, z;
            INT out = sscanf(cursor, "%f,%f,%f%n", &x, &y, &z, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Warping failed, no coordinates were specified \"%s\"\n", GetConfirmedText());
            }
            else if (out != 3) {
                sprintf(GetText(), "Warping failed, malformed coordinates \"%s\"\n", GetConfirmedText());
            }
            else {
                Pos.x = x; Pos.y = y; Pos.z = z;
                sprintf(GetText(), "Warped to (%.2f, %.2f, %.2f)\n", x, y, z);
            }

            SetWinState(3);
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
                CHAR name[20] = "", group[20] = "";

                INT out = sscanf(cursor, "%f,%f,%f%n", &x, &y, &z, &off);
                cursor += off;

                if (out != 3) {
                    sprintf(GetText(), "Point creation failed, malformed coordinates \"%s\"\n", GetConfirmedText());
                    SetWinState(3);
                }
                else {
                    out = sscanf(cursor, "%x %s %s%n", &color, name, group, &off);
                    cursor += off;

                    if (out == EOF) {
                        sprintf(name, "point%d", rand());
                        strcpy(group, "default");
                    }
                    else {
                        if (strcmp(name, "-") == 0 || strlen(name) == 0) {
                            sprintf(name, "point%d", rand());
                        }
                        if (strcmp(group, "-") == 0 || strlen(group) == 0) {
                            strcpy(group, "default");
                        }
                    }
                    
                    sprintf(GetText(), "Point \"%s\" of color \"%08x\" was created at (%.2f, %.2f, %.2f) in group \"%s\"",
                        name, color, x, y, z, group);

                    Point p = MakePoint();
                    p->P.x = x; p->P.y = y; p->P.z = z;
                    p->props->color = color;
                    strcpy(p->props->name, name);
                    strcpy(p->props->group, group);
                }
                
                SetWinState(3);
            }
            else if (strcmp(word, "line") == 0) {
                FLOAT x1, y1, z1, x2, y2, z2;
                UINT color = 0x00ffffff, end_color = 0xffffffff;
                CHAR name[20] = "", group[20] = "";

                INT out = sscanf(cursor, "%f,%f,%f;%f,%f,%f%n", &x1, &y1, &z1, &x2, &y2, &z2, &off);
                cursor += off;

                if (out != 6) {
                    sprintf(GetText(), "Line creation failed, malformed coordinates \"%s\"\n", GetConfirmedText());
                    SetWinState(3);
                }
                else {
                    out = sscanf(cursor, "%x %s %s %x%n", &color, name, group, &end_color, &off);
                    cursor += off;

                    if (out == EOF) {
                        sprintf(name, "line%d", rand());
                        strcpy(group, "default");
                    }
                    else {
                        if (strcmp(name, "-") == 0 || strlen(name) == 0) {
                            sprintf(name, "line%d", rand());
                        }
                        if (strcmp(group, "-") == 0 || strlen(group) == 0) {
                            strcpy(group, "default");
                        }
                    }

                    sprintf(GetText(), "Line \"%s\" of color \"%08x-%08x\" was created from (%.2f, %.2f, %.2f)"
                        " to (%.2f, %.2f, %.2f) in group \"%s\"",
                        name, color, end_color, x1, y1, z1, x2, y2, z2, group);

                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    l->props->color = color;
                    l->lprops->end_color = end_color;

                    strcpy(l->props->name, name);
                    strcpy(l->props->group, group);
                }

                SetWinState(3);
            }
            else {
                sprintf(GetText(), "Unknown Asset type \"%s\"\n", word);
                SetWinState(3);
            }
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
                }
            }
            else {
                DeleteAsset(word);
                sprintf(GetText(), "Deleting Asset \"%s\"\n", word);
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
                }
            }
            else {
                ShowAsset(word, TRUE);
                sprintf(GetText(), "Asset \"%s\" is now visible\n", word);
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
                }
            }
            else {
                ShowAsset(word, FALSE);
                sprintf(GetText(), "Asset \"%s\" is now hidden\n", word);
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
                    sprintf(GetText(), "Current FPS cap is set to %u\n", GetFPS());
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
                        sprintf(GetText(), "Invalid FPS cap %d\n", CAP);
                    }
                    else {
                        sprintf(GetText(), "FPS cap set to %d\n", CAP);
                        SetFPS(CAP);
                    }
                }
            }
            else if (strcmp(word, "uncap") == 0 || strcmp(word, "unlock") == 0) {
                sprintf(GetText(), "FPS cap removed\n");
                SetFPS(-1);
            }
            else if (strcmp(word, "reset") == 0) {
                sprintf(GetText(), "FPS Highest and Lowest records reset\n");
                ResetFrameTimes();
            }
            else if (strcmp(word, "update") == 0) {
                LONGLONG INTERVAL;

                out = sscanf(cursor, "%lld%n", &INTERVAL, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "FPS Update Interval is set to once per %lld frames\n", INTERVAL);
                }
                else {
                    if (INTERVAL < 0) {
                        sprintf(GetText(), "Invalid FPS Update Interval \"%lld\"\n", INTERVAL);
                    }
                    else {
                        SetFrameUpdateInterval(INTERVAL);
                        sprintf(GetText(), "FPS Update Interval set to once per %lld frames \n", INTERVAL);
                    }
                }
            }
            else {
                sprintf(GetText(), "Unknown FPS command option \"%s\"\n", GetConfirmedText());
            }
        }
        else if (strcmp(word, "color") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Coloring failed, no option specified \"%s\"\n", GetConfirmedText());
            }
            else if (strcmp(word, "bg") == 0) {
                UINT color;

                out = sscanf(cursor, "%x%n", &color, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Coloring failed, no Background color specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    SetEngineBG(color);
                    sprintf(GetText(), "Background Color changed to \"%08x\"\n", color);
                }
            }
            else if (strcmp(word, "font") == 0) {
                UINT color;

                out = sscanf(cursor, "%x%n", &color, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Coloring failed, no Font color specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    SetFontFG(color);
                    sprintf(GetText(), "Font Color changed to \"%08x\"\n", color);
                }
            }
            else if (strcmp(word, "fontbg") == 0) {
                UINT color;

                out = sscanf(cursor, "%x%n", &color, &off);
                cursor += off;

                if (out == EOF) {
                    sprintf(GetText(), "Coloring failed, no Background Font color specified \"%s\"\n", GetConfirmedText());
                }
                else {
                    SetFontBG(color);
                    sprintf(GetText(), "Font Background Color changed to \"%08x\"\n", color);
                }
            }
            else {
                sprintf(GetText(), "Unknown Color command option \"%s\"\n", GetConfirmedText());
            }
        }
        else if (strcmp(word, "engine") == 0) {
            INT out = sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "No Engine option specified \"%s\"\n", GetConfirmedText());
            }
            else if (strcmp(word, "buffer") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (strcmp(word, "default") == 0 || strcmp(word, "aligned") == 0) {
                    SetBufClearMode(ALIGNED_AVX);
                    sprintf(GetText(), "Engine Buffer clear mode set to ALIGNED_AVX\n", GetConfirmedText());
                }
                else if (strcmp(word, "nth") == 0) {
                    SetBufClearMode(NTH_AVX);
                    sprintf(GetText(), "Engine Buffer clear mode set to NTH_AVX\n", GetConfirmedText());
                }
                else if (strcmp(word, "dual_aligned") == 0) {
                    SetBufClearMode(DUAL_ALIGNED_AVX);
                    sprintf(GetText(), "Engine Buffer clear mode set to DUAL_ALIGNED_AVX\n", GetConfirmedText());
                }
                else if (strcmp(word, "dual_nth") == 0) {
                    SetBufClearMode(DUAL_NTH_AVX);
                    sprintf(GetText(), "Engine Buffer clear mode set to DUAL_NTH_AVX\n", GetConfirmedText());
                }
                else {
                    sprintf(GetText(), "Unknown Engine Buffer option \"%s\"\n", GetConfirmedText());
                }
            }
            else if (strcmp(word, "mode") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (strcmp(word, "default") == 0 || strcmp(word, "avx256") == 0) {
                    SetEngineMode(AVX256);
                    sprintf(GetText(), "Engine Mode set to (default) AVX256\n", GetConfirmedText());
                }
                else if (strcmp(word, "avx512") == 0) {
                    SetEngineMode(AVX512);
                    sprintf(GetText(), "Engine Mode set to Accelerated AVX512\n", GetConfirmedText());
                }
                else {
                    sprintf(GetText(), "Unknown Engine Mode \"%s\"\n", GetConfirmedText());
                }
            }
            else {
                sprintf(GetText(), "Unknown Engine option \"%s\"\n", GetConfirmedText());
            }
        }
        else if (strcmp(word, "scale") == 0) {
            FLOAT res;

            INT out = sscanf(cursor, "%f%n", &res, &off);
            cursor += off;

            if (out == EOF) {
                sprintf(GetText(), "Current Engine Resolution is set to x%.1f\n", GetResolution());
            }
            else {
                if (out == 0) {
                    sprintf(GetText(), "Expected a floating point Resolution value \"%s\"\n", GetConfirmedText());
                }
                else {
                    if (res < 1.0f || res > 15.0f) {
                        sprintf(GetText(), "Invalid resolution value \"x%.1f\"\n", res);
                    }
                    else {
                        SetResolution(res);
                        sprintf(GetText(), "Engine Resolution set to x%.1f\n", GetResolution());
                    }
                }
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