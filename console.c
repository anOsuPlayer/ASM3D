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

                if (!out) {
                    printf("Asset creation failed, no asset type was specified \"%s\"\n", in);
                    goto make_quit;
                }

                if (strcmp(word, "point") == 0) {
                    FLOAT x, y, z;

                    INT out = sscanf(cursor, "%f,%f,%f%n", &x, &y, &z, &off);
                    cursor += off;

                    if (out != 3) {
                        printf("Point creation failed, malformed coordinates \"%s\"\n", in);
                        goto make_quit;
                    }
                    
                    UINT color = 0x00ffffff;
                    
                    if (sscanf(cursor, "%s%n", word, &off) == 0) {
                        printf("Unnamed Point created at (%f, %f, %f)", x, y, z);
                        Point p = MakePoint();
                        p->x = x; p->y = y; p->z = z;

                        goto make_quit;
                    }

                    if (strlen(word) > 20) {
                        printf("Point creation failed, invalid name \"%s\"\n", word);
                        goto make_quit;
                    }

                    cursor += off;
                    
                    if (sscanf(cursor, "%x%n", &color, &off) == 0) {
                        printf("Point \"%s\" created at (%f, %f, %f)\n", word, x, y, z);
                        Point p = MakePoint();
                        p->x = x; p->y = y; p->z = z;
                        strcpy(p->p->name, word);

                        goto make_quit;
                    }

                    printf("Point \"%s\" of color \"%x\" created at (%f, %f, %f)\n", word, color, x, y, z);

                    Point p = MakePoint();
                    p->x = x; p->y = y; p->z = z;
                    strcpy(p->p->name, word);
                    p->p->color = color;

                    SetRepaint();
                    goto make_quit;
                }

                if (strcmp(word, "line") == 0) {
                    FLOAT x1, y1, z1, x2, y2, z2;

                    INT out = sscanf(cursor, "%f,%f,%f;%f,%f,%f%n", &x1, &y1, &z1, &x2, &y2, &z2, &off);
                    cursor += off;

                    if (out != 6) {
                        printf("Line creation failed, malformed coordinates \"%s\"\n", in);
                        goto make_quit;
                    }
                    
                    UINT color = 0x00ffffff;
                    
                    if (sscanf(cursor, "%s%n", word, &off) == 0) {
                        printf("Unnamed Line created from (%f, %f, %f) to (%f, %f, %f)", x1, y1, z1, x2, y2, z2);
                        Line l = MakeLine();
                        l->A.x = x1; l->A.y = y1; l->A.z = z1;
                        l->B.x = x2; l->B.y = y2; l->B.z = z2;

                        goto make_quit;
                    }

                    if (strlen(word) > 20) {
                        printf("Line creation failed, invalid name \"%s\"\n", word);
                        goto make_quit;
                    }

                    cursor += off;
                    
                    if (sscanf(cursor, "%x%n", &color, &off) == 0) {
                        printf("Line \"%s\" created from (%f, %f, %f) to (%f, %f, %f)\n", word, x1, y1, z1, x2, y2, z2);
                        Line l = MakeLine();
                        l->A.x = x1; l->A.y = y1; l->A.z = z1;
                        l->B.x = x2; l->B.y = y2; l->B.z = z2;
                        strcpy(l->p->name, word);

                        goto make_quit;
                    }

                    printf("Line \"%s\" of color \"%x\" created from (%f, %f, %f) to (%f, %f, %f)\n", word, color,
                        x1, y1, z1, x2, y2, z2);

                    Line l = MakeLine();
                    l->A.x = x1; l->A.y = y1; l->A.z = z1;
                    l->B.x = x2; l->B.y = y2; l->B.z = z2;
                    strcpy(l->p->name, word);
                    l->p->color = color;

                    SetRepaint();
                    goto make_quit;
                }

                printf("Unknown asset type \"%s\"\n", word);

                make_quit:
            }
            else if (strcmp(word, "delete") == 0) {
                INT out = sscanf(cursor, "%s%n", word, &off);
                cursor += off;

                if (!out) {
                    printf("Asset deletion failed, no asset type was specified \"%s\"\n", in);
                    goto delete_quit;
                }

                if (strcmp(word, "point") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (!out) {
                        printf("Asset deletion failed, no Point was specified \"%s\"\n", in);
                        goto delete_quit;
                    }

                    DeletePoint(word);
                    printf("Deleting Point \"%s\"\n", word);
                    
                    SetRepaint();
                    goto delete_quit;
                }

                if (strcmp(word, "line") == 0) {
                    INT out = sscanf(cursor, "%s%n", word, &off);
                    cursor += off;

                    if (!out) {
                        printf("Asset deletion failed, no Line was specified \"%s\"\n", in);
                        goto delete_quit;
                    }

                    DeleteLine(word);
                    printf("Deleting Line \"%s\"\n", word);
                    
                    SetRepaint();
                    goto delete_quit;
                }

                printf("Unknown asset type \"%s\"\n", word);

                delete_quit:
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