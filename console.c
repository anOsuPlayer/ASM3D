#include "console.h"

INT Process(CHAR in[500], CHAR word[100], CHAR* cursor) {

}

void* ReadInput(void* null) {
    while (IS_RUNNING) {
        CHAR in[500];
        CHAR* cursor = in;
        
        printf(">> ");

        fgets(in, sizeof(in), stdin);
        in[strcspn(in, "\n")] = 0;

        if (strlen(in) != 0) {
            CHAR word[100];
            UINT off;

            sscanf(cursor, "%s%n", word, &off);
            cursor += off;

            if (strcmp(word, "cls") == 0) {
                system("cls");
            }
            else if (strcmp(word, "exit") == 0) {
                IS_RUNNING = FALSE;
            }
            else if (strcmp(word, "make") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    printf("Asset creation failed, no asset type was specified \"%s\"\n", in);
                    goto make_quit;
                }
                else if (strcmp(word, "point") == 0) {
                    FLOAT x, y, z;
                    UINT color = 0x00ffffff;
                    CHAR name[20], group[20];

                    INT out = sscanf(cursor, "%f,%f,%f%n", &x, &y, &z, &off);
                    cursor += off;

                    if (out != 3) {
                        printf("Point creation failed, malformed coordinates \"%s\"\n", in);
                        goto make_quit;
                    }
                    
                    if (sscanf(cursor, "%x%n", &color, &off) <= 0) {
                        printf("Unnamed Point created at (%.2f, %.2f, %.2f)\n", word, x, y, z);
                        Point p = MakePoint();
                        p->P.x = x; p->P.y = y; p->P.z = z;
                        p->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    cursor += off;

                    if (sscanf(cursor, "%s%n", name, &off) <= 0) {
                        printf("Unnamed Point of color \"%x\" created at (%.2f, %.2f, %.2f)", color, x, y, z);
                        Point p = MakePoint();
                        p->P.x = x; p->P.y = y; p->P.z = z;
                        p->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    if (strlen(name) > 20) {
                        printf("Point creation failed, invalid name \"%s\"\n", name);
                        goto make_quit;
                    }

                    cursor += off;

                    if (sscanf(cursor, "%s%n", group, &off) <= 0) {
                        printf("Point \"%s\" of color \"%x\" created at (%.2f, %.2f, %.2f)\n", name, color, x, y, z);
                        Point p = MakePoint();
                        p->P.x = x; p->P.y = y; p->P.z = z;
                        strcpy(p->p->name, name);
                        p->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    if (strlen(group) > 20) {
                        printf("Point creation failed, invalid group \"%s\"\n", group);
                        goto make_quit;
                    }

                    printf("Point \"%s\" of color \"%x\" created at (%.2f, %.2f, %.2f) in group \"%s\"\n",
                        name, color, x, y, z, group);
                    Point p = MakePoint();
                    p->P.x = x; p->P.y = y; p->P.z = z;
                    strcpy(p->p->name, word);
                    strcpy(p->p->group, group);
                    p->p->color = color;

                    SetRepaint();
                    goto make_quit;
                }
                else if (strcmp(word, "line") == 0) {
                    FLOAT x1, y1, z1, x2, y2, z2;
                    UINT color = 0x00ffffff;
                    CHAR name[20], group[20];

                    INT out = sscanf(cursor, "%f,%f,%f;%f,%f,%f%n", &x1, &y1, &z1, &x2, &y2, &z2, &off);
                    cursor += off;

                    if (out != 6) {
                        printf("Line creation failed, malformed coordinates \"%s\"\n", in);
                        goto make_quit;
                    }
                    
                    if (sscanf(cursor, "%x%n", &color, &off) <= 0) {
                        printf("Unnamed Line created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", word, x1, y1, z1, x2, y2, z2);
                        Line l = MakeLine();
                        l->A.x = x1; l->A.y = y1; l->A.z = z1;
                        l->B.x = x2; l->B.y = y2; l->B.z = z2;
                        l->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    cursor += off;

                    if (sscanf(cursor, "%s%n", name, &off) <= 0) {
                        printf("Unnamed Line of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)",
                            color, x1, y1, z1, x2, y2, z2);
                        Line l = MakeLine();
                        l->A.x = x1; l->A.y = y1; l->A.z = z1;
                        l->B.x = x2; l->B.y = y2; l->B.z = z2;
                        l->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    if (strlen(name) > 20) {
                        printf("Line creation failed, invalid name \"%s\"\n", name);
                        goto make_quit;
                    }

                    cursor += off;

                    if (sscanf(cursor, "%s%n", group, &off) <= 0) {
                        printf("Line \"%s\" of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", name,
                            color, x1, y1, z1, x2, y2, z2);
                        Line l = MakeLine();
                        l->A.x = x1; l->A.y = y1; l->A.z = z1;
                        l->B.x = x2; l->B.y = y2; l->B.z = z2;
                        strcpy(l->p->name, name);
                        l->p->color = color;

                        SetRepaint();
                        goto make_quit;
                    }

                    if (strlen(group) > 20) {
                        printf("Line creation failed, invalid group \"%s\"\n", group);
                        goto make_quit;
                    }

                    printf("Line \"%s\" of color \"%x\" created from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f) in group \"%s\"\n",
                        name, color, x1, y1, z1, x2, y2, z2, group);
                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    strcpy(l->p->name, name);
                    strcpy(l->p->group, group);
                    l->p->color = color;

                    SetRepaint();
                    goto make_quit;
                }

                printf("Unknown Asset type \"%s\"\n", word);

                make_quit:
            }
            else if (strcmp(word, "delete") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    printf("Asset deletion failed, no Asset type was specified \"%s\"\n", in);
                }
                else if (strcmp(word, "group") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset deletion failed, no Group was specified \"%s\"\n", in);
                    }
                    else {
                        DeleteGroup(word);
                        printf("Deleting Group \"%s\"\n", word);
                        
                        SetRepaint();
                    }
                }
                else if (strcmp(word, "point") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset deletion failed, no Point was specified \"%s\"\n", in);
                    }
                    else {
                        DeletePoint(word);
                        printf("Deleting Point \"%s\"\n", word);
                        
                        SetRepaint();
                    }

                }
                else if (strcmp(word, "line") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset deletion failed, no Line was specified \"%s\"\n", in);
                    }
                    else {
                        DeleteLine(word);
                        printf("Deleting Line \"%s\"\n", word);
                        
                        SetRepaint();
                    }
                }
                else {
                    DeleteAsset(word);
                    printf("Deleting Asset \"%s\"\n", word);

                    SetRepaint();
                }
            }
            else if (strcmp(word, "show") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    printf("Asset manipulation failed, no Asset type was specified \"%s\"\n", in);
                }
                else if (strcmp(word, "group") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Group was specified \"%s\"\n", in);
                    }
                    else {
                        ShowGroup(word, TRUE);
                        printf("Group \"%s\" is now visible\n", word);
                        
                        SetRepaint();
                    }
                }
                else if (strcmp(word, "point") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Point was specified \"%s\"\n", in);
                    }
                    else {
                        ShowPoint(word, TRUE);
                        printf("Point \"%s\" is now visible\n", word);
                        
                        SetRepaint();
                    }

                }
                else if (strcmp(word, "line") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Line was specified \"%s\"\n", in);
                    }
                    else {
                        ShowLine(word, TRUE);
                        printf("Line \"%s\" is now visible\n", word);
                        
                        SetRepaint();
                    }
                }
                else {
                    ShowAsset(word, TRUE);
                    printf("Asset \"%s\" is now visible\n", word);

                    SetRepaint();
                }
            }
            else if (strcmp(word, "hide") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    printf("Asset manipulation failed, no Asset type was specified \"%s\"\n", in);
                }
                else if (strcmp(word, "group") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Group was specified \"%s\"\n", in);
                    }
                    else {
                        ShowGroup(word, FALSE);
                        printf("Group \"%s\" is now hidden\n", word);
                        
                        SetRepaint();
                    }
                }
                else if (strcmp(word, "point") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Point was specified \"%s\"\n", in);
                    }
                    else {
                        ShowPoint(word, FALSE);
                        printf("Point \"%s\" is now hidden\n", word);
                        
                        SetRepaint();
                    }

                }
                else if (strcmp(word, "line") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("Asset manipulation failed, no Line was specified \"%s\"\n", in);
                    }
                    else {
                        ShowLine(word, FALSE);
                        printf("Line \"%s\" is now hidden\n", word);
                        
                        SetRepaint();
                    }
                }
                else {
                    ShowAsset(word, FALSE);
                    printf("Asset \"%s\" is now hidden\n", word);

                    SetRepaint();
                }
            }
            else if (strcmp(word, "fps") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (out == EOF) {
                    if (GetFPS() == -1) {
                        printf("Current FPS cap is unbound\n");
                    }
                    else {
                        printf("Current FPS cap is set to \"%u\"\n", GetFPS());
                    }
                }
                else if (strcmp(word, "cap") == 0) {
                    INT CAP;

                    out = sscanf(cursor, "%d%n", &CAP, &off);
                    cursor += off;

                    if (out == EOF) {
                        printf("No FPS cap provided \"%s\"\n", in);
                    }
                    else {
                        if (CAP < 1 || CAP > 10000) {
                            printf("Invalid FPS cap \"%d\"\n", CAP);
                        }
                        else {
                            printf("FPS cap set to \"%d\"\n", CAP);
                            SetFPS(CAP);
                        }
                    }
                }
                else if (strcmp(word, "uncap") == 0) {
                    printf("FPS cap removed\n");
                    SetFPS(-1);
                }
                else {
                    printf("Unknown FPS command option \"%s\"\n", in);
                }
            }
            else {
                printf("Invalid command \"%s\"\n", in);
            }
        }
    }
}

BOOL IsRunning() {
    return IS_RUNNING;
}

void InitializeConsole(HWND hwnd) {
    if (!IS_RUNNING) {
        WINDOW = hwnd;
        IS_RUNNING = TRUE;
        pthread_create(&CONSOLE_THREAD, NULL, ReadInput, NULL);
    }
}

void TerminateConsole() {
    if (IS_RUNNING) {
        IS_RUNNING = FALSE;
        pthread_kill(CONSOLE_THREAD, 0);
    }
}