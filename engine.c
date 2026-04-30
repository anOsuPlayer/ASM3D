#include "engine.h"

static Point*       ePOINTS;
static UINT         PCOUNT = 0;

static Line*        eLINES;
static UINT         LCOUNT = 0;

static Surface*     eSURFACES;
static UINT         SCOUNT = 0;

void SetupAxes() {
    Line X = MakeLine();
    X->A.x = -100000; X->A.y = 0; X->A.z = 0;
    X->B.x = 100000; X->B.y = 0; X->B.z = 0;
    X->props->color = 0x00550055;
    X->lprops->end_color = 0x00550000;
    strcpy(X->props->name, "x_axis");
    strcpy(X->props->group, "axes");
    
    Line Y = MakeLine();
    Y->A.x = 0; Y->A.y = -100000; Y->A.z = 0;
    Y->B.x = 0; Y->B.y = 100000; Y->B.z = 0;
    Y->props->color = 0x00555500;
    Y->lprops->end_color = 0x00005500;
    strcpy(Y->props->name, "y_axis");
    strcpy(Y->props->group, "axes");

    Line Z = MakeLine();
    Z->A.x = 0; Z->A.y = 0; Z->A.z = -100000;
    Z->B.x = 0; Z->B.y = 0; Z->B.z = 100000;
    Z->props->color = 0x00005555;
    Z->lprops->end_color = 0x00000055;
    strcpy(Z->props->name, "z_axes");
    strcpy(Z->props->group, "axes");

    Point O = MakePoint();
    O->P.x = 0; O->P.y = 0; O->P.z = 0;
    O->props->color = 0x00555555;
    strcpy(O->props->name, "origin");
    strcpy(O->props->group, "axes");
}

void SetupGrid() {
    for (INT i = 1; i < 100; i++) {
        Line G1 = MakeLine();
        G1->A.x = 2*i; G1->A.y = 200; G1->A.z = 0;
        G1->B.x = 2*i; G1->B.y = -200; G1->B.z = 0;
        G1->props->color = 0x00333333;
        strcpy(G1->props->name, "grid");
        strcpy(G1->props->group, "grid");
        Line G2 = MakeLine();
        G2->A.x = -2*i; G2->A.y = 200; G2->A.z = 0;
        G2->B.x = -2*i; G2->B.y = -200; G2->B.z = 0;
        G2->props->color = 0x00333333;
        strcpy(G2->props->name, "grid");
        strcpy(G2->props->group, "grid");

        Line G3 = MakeLine();
        G3->A.x = 200; G3->A.y = 2*i; G3->A.z = 0;
        G3->B.x = -200; G3->B.y = 2*i; G3->B.z = 0;
        G3->props->color = 0x00333333;
        strcpy(G3->props->name, "grid");
        strcpy(G3->props->group, "grid");
        Line G4 = MakeLine();
        G4->A.x = 200; G4->A.y = -2*i; G4->A.z = 0;
        G4->B.x = -200; G4->B.y = -2*i; G4->B.z = 0;
        G4->props->color = 0x00333333;
        strcpy(G4->props->name, "grid");
        strcpy(G4->props->group, "grid");
    }
}

void InitializeAssets() {
    ePOINTS = (Point*) malloc(sizeof(Point));
    eLINES = (Line*) malloc(sizeof(Line));
    eSURFACES = (Surface*) malloc(sizeof(Surface));

    SetupGrid();
    SetupAxes();
}

void TerminateAssets() {
    for (UINT i = 0; i < PCOUNT; i++) {
        FreePoint(ePOINTS[i]);
    }
    free(ePOINTS);

    for (UINT i = 0; i < LCOUNT; i++) {
        FreeLine(eLINES[i]);
    }
    free(eLINES);

    for (UINT i = 0; i < SCOUNT; i++) {
        FreeSurface(eSURFACES[i]);
    }
    free(eSURFACES);
}

Point MakePoint() {
    Point p = (Point) malloc(sizeof(struct point_t));
    p->props = (Properties) malloc(sizeof(struct properties_t));
    p->P.w = 1.0f;

    p->props->color = 0x00ffffff;
    p->props->hidden = FALSE;
    
    ePOINTS = realloc(ePOINTS, (++PCOUNT) * sizeof(struct point_t));
    ePOINTS[PCOUNT-1] = p;

    return p;
}

void FreePoint(Point p) {
    free(p->props);
    free(p);
}

void DeletePoint(const char* pname) {
    Point p = NULL;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->name, pname) == 0) {
            p = ePOINTS[i];
            ePOINTS[i] = ePOINTS[--PCOUNT];
            break;
        }
    }

    FreePoint(p);
    ePOINTS = (Point*) realloc(ePOINTS, PCOUNT);
}

void ShowPoint(const char* pname, BOOL show) {
    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->name, pname) == 0) {
            ePOINTS[i]->props->hidden = !show;
        }
    }
}

Line MakeLine() {
    Line l = (Line) malloc(sizeof(struct line_t));
    l->props = (Properties) malloc(sizeof(struct properties_t));
    l->lprops = (LProperties) malloc(sizeof(struct line_properties_t));

    l->A.w = 1.0f;
    l->B.w = 1.0f;

    l->props->color = 0x00ffffff;
    l->lprops->end_color = 0xffffffff;
    l->props->hidden = FALSE;

    eLINES = realloc(eLINES, (++LCOUNT) * sizeof(struct line_t));
    eLINES[LCOUNT-1] = l;

    return l;
}

void FreeLine(Line l) {
    free(l->props);
    free(l->lprops);
    free(l);
}

void DeleteLine(const char* lname) {
    Line l = NULL;

    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->name, lname) == 0) {
            l = eLINES[i];
            eLINES[i] = eLINES[--LCOUNT];
            break;
        }
    }

    FreeLine(l);
    eLINES = realloc(eLINES, (LCOUNT) * sizeof(struct line_t));
}

void ShowLine(const char* lname, BOOL show) {
    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->name, lname) == 0) {
            eLINES[i]->props->hidden = !show;
        }
    }
}

Surface MakeSurface() {
    Surface s = (Surface) malloc(sizeof(struct surface_t));
    s->props = (Properties) malloc(sizeof(struct properties_t));
    s->A.w = 1.0f;
    s->B.w = 1.0f;
    s->C.w = 1.0f;

    s->props->color = 0x00ffffff;
    s->props->hidden = FALSE;

    eSURFACES = realloc(eSURFACES, (++SCOUNT) * sizeof(struct surface_t));
    eSURFACES[SCOUNT-1] = s;

    return s;
}

void FreeSurface(Surface s) {
    free(s->props);
    free(s);
}

void DeleteSurface(const char* pname) {
    Surface s = NULL;

    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->name, pname) == 0) {
            s = eSURFACES[i];
            eSURFACES[i] = eSURFACES[--SCOUNT];
            break;
            
            break;
        }
    }

    FreeSurface(s);
    eSURFACES = realloc(eSURFACES, (--SCOUNT) * sizeof(struct surface_t));
}

void ShowSurface(const char* sname, BOOL show) {
    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->name, sname) == 0) {
            eSURFACES[i]->props->hidden = !show;
        }
    }
}

void DeleteAsset(const char* name) {
    DeletePoint(name);
    DeleteLine(name);
    DeleteSurface(name);
}

void ShowAsset(const char* name, BOOL show) {
    ShowPoint(name, show);
    ShowLine(name, show);
    ShowSurface(name, show);
}

void DeleteGroup(const char* gname) {
    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->group, gname) == 0) {
            DeletePoint(ePOINTS[i--]->props->name);
        }
    }
    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->group, gname) == 0) {
            DeleteLine(eLINES[i--]->props->name);
        }
    }
    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->group, gname) == 0) {
            DeleteSurface(eSURFACES[i--]->props->name);
        }
    }
}

void ShowGroup(const char* gname, BOOL show) {
    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->group, gname) == 0) {
            ePOINTS[i]->props->hidden = !show;
        }
    }
    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->group, gname) == 0) {
            eLINES[i]->props->hidden = !show;
        }
    }
    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->group, gname) == 0) {
            eSURFACES[i]->props->hidden = !show;
        }
    }
}

void RenderPoints(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < PCOUNT; i++) {
        if (!ePOINTS[i]->props->hidden) {
            struct vec_t screen;
            BOOL confirm = compute_point((Vec) &ePOINTS[i]->P, &screen);
    
            if (confirm) {
                put(screen.x, screen.y, ePOINTS[i]->props->color, screen.z);
            }
        }
    }
}

void RenderLines(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < LCOUNT; i++) {
        if (!eLINES[i]->props->hidden) {
            struct vec_t screen1, screen2;
            BOOL confirm = compute_line((Vec) &eLINES[i]->A, (Vec) &eLINES[i]->B, &screen1, &screen2);

            if (confirm == 1) {
                FLOAT dx = screen2.x - screen1.x;
                FLOAT dy = screen2.y - screen1.y;
                FLOAT dz = screen2.z - screen1.z;

                FLOAT dr = 0, dg = 0, db = 0;

                if (eLINES[i]->lprops->end_color != 0xffffffff) {
                    dr = (FLOAT) ((INT)(eLINES[i]->lprops->end_color & 0x000000ff)
                        - (INT)(eLINES[i]->props->color & 0x000000ff));
                    dg = (FLOAT) ((INT)((eLINES[i]->lprops->end_color & 0x0000ff00) >> 8)
                        - ((INT)(eLINES[i]->props->color & 0x0000ff00) >> 8));
                    db = (FLOAT) ((INT)((eLINES[i]->lprops->end_color & 0x00ff0000) >> 16)
                        - ((INT)(eLINES[i]->props->color & 0x00ff0000) >> 16));
                }

                FLOAT steps = (fabsf(dx) > fabsf(dy)) ? fabsf(dx) : fabsf(dy);

                if (steps == 0) {
                    put(screen1.x, screen1.y, eLINES[i]->props->color, screen1.z);
                    return;
                }

                FLOAT xi = dx / steps, yi = dy / steps, zi = dz / steps;
                FLOAT ri = dr / steps, gi = dg / steps, bi = db / steps;

                FLOAT x = screen1.x, y = screen1.y, z = screen1.z;

                FLOAT r = (FLOAT) (eLINES[i]->props->color & 0x000000ff);
                FLOAT g = (FLOAT) ((eLINES[i]->props->color & 0x0000ff00) >> 8);
                FLOAT b = (FLOAT) ((eLINES[i]->props->color & 0x00ff0000) >> 16);

                for (INT e = 0; e <= (INT) steps; e++) {
                    put(x, y, (UINT) RGB((UINT) r, (UINT) g, (UINT) b), z);
                    x += xi; y += yi; z += zi;
                    r += ri; g += gi; b += bi;
                }
            }
        }
    }
}

void RenderSurfaces(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < SCOUNT; i++) {
        
    }
}

void Render(HWND hwnd, HDC hdc) {
    ClearBuffers();

    RenderPoints(hwnd, hdc);
    RenderLines(hwnd, hdc);
    RenderSurfaces(hwnd, hdc);

    StretchDIBits(
        hdc,
        0, 0, GetWindowWidth(), GetWindowHeight(),
        0, 0, GetScaledWidth(), GetScaledHeight(),
        CBUFFER,
        GetBMI(),
        DIB_RGB_COLORS,
        SRCCOPY
    );
}