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
    X->props->shader = FetchHandle("base", "xshader");
    strcpy(X->props->name, "x_axis");
    strcpy(X->props->group, "axes");
    
    Line Y = MakeLine();
    Y->A.x = 0; Y->A.y = -100000; Y->A.z = 0;
    Y->B.x = 0; Y->B.y = 100000; Y->B.z = 0;
    Y->props->shader = FetchHandle("base", "yshader");
    strcpy(Y->props->name, "y_axis");
    strcpy(Y->props->group, "axes");

    Line Z = MakeLine();
    Z->A.x = 0; Z->A.y = 0; Z->A.z = -100000;
    Z->B.x = 0; Z->B.y = 0; Z->B.z = 100000;
    Z->props->shader = FetchHandle("base", "zshader");
    strcpy(Z->props->name, "z_axes");
    strcpy(Z->props->group, "axes");

    Point O = MakePoint();
    O->P.x = 0; O->P.y = 0; O->P.z = 0;
    O->props->shader = FetchHandle("base", "gridshader");
    strcpy(O->props->name, "origin");
    strcpy(O->props->group, "axes");
}

void SetupGrid() {
    for (INT i = 1; i < 100; i++) {
        Line G1 = MakeLine();
        G1->A.x = 2*i; G1->A.y = 200; G1->A.z = 0;
        G1->B.x = 2*i; G1->B.y = -200; G1->B.z = 0;
        G1->props->shader = FetchHandle("base", "gridshader");
        strcpy(G1->props->name, "grid");
        strcpy(G1->props->group, "grid");
        Line G2 = MakeLine();
        G2->A.x = -2*i; G2->A.y = 200; G2->A.z = 0;
        G2->B.x = -2*i; G2->B.y = -200; G2->B.z = 0;
        G2->props->shader = FetchHandle("base", "gridshader");
        strcpy(G2->props->name, "grid");
        strcpy(G2->props->group, "grid");

        Line G3 = MakeLine();
        G3->A.x = 200; G3->A.y = 2*i; G3->A.z = 0;
        G3->B.x = -200; G3->B.y = 2*i; G3->B.z = 0;
        G3->props->shader = FetchHandle("base", "gridshader");        
        strcpy(G3->props->name, "grid");
        strcpy(G3->props->group, "grid");
        Line G4 = MakeLine();
        G4->A.x = 200; G4->A.y = -2*i; G4->A.z = 0;
        G4->B.x = -200; G4->B.y = -2*i; G4->B.z = 0;
        G4->props->shader = FetchHandle("base", "gridshader");
        strcpy(G4->props->name, "grid");
        strcpy(G4->props->group, "grid");
    }
}

void InitializeAssets() {
    ePOINTS = (Point*) malloc(sizeof(Point));
    eLINES = (Line*) malloc(sizeof(Line));
    eSURFACES = (Surface*) malloc(sizeof(Surface));

    OpenModule(ENGINE_SHADERS_HANDLE);

    SetupGrid();
    SetupAxes();
    
    InitializeCameras();
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

    TerminateCameras();
}

Point MakePoint() {
    Point p = (Point) malloc(sizeof(struct point_t));
    p->props = (Properties) malloc(sizeof(struct properties_t));
    p->P.w = 1.0f;

    p->props->hidden = FALSE;
    p->props->shader = VoidHandle();
    
    ePOINTS = (Point*) realloc(ePOINTS, (++PCOUNT) * sizeof(Point));
    ePOINTS[PCOUNT-1] = p;

    return p;
}

void FreePoint(Point p) {
    free(p->props);
    free(p);
}

BOOL DeletePoint(const char* pname) {
    Point p = NULL;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->name, pname) == 0) {
            p = ePOINTS[i];
            ePOINTS[i] = ePOINTS[--PCOUNT];
            break;
        }
    }

    if (p != NULL) {
        FreePoint(p);
        ePOINTS = (Point*) realloc(ePOINTS, PCOUNT * sizeof(Point));
        
        return TRUE;
    }

    return FALSE;
}

UINT ShowPoint(const char* pname, BOOL show) {
    UINT showed = 0;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->name, pname) == 0) {
            ePOINTS[i]->props->hidden = !show;
            showed++;
        }
    }

    return showed;
}

Line MakeLine() {
    Line l = (Line) malloc(sizeof(struct line_t));
    l->props = (Properties) malloc(sizeof(struct properties_t));

    l->A.w = 1.0f;
    l->B.w = 1.0f;

    l->props->hidden = FALSE;
    l->props->shader = VoidHandle();

    eLINES = (Line*) realloc(eLINES, (++LCOUNT) * sizeof(Line));
    eLINES[LCOUNT-1] = l;

    return l;
}

void FreeLine(Line l) {
    free(l->props);
    free(l);
}

BOOL DeleteLine(const char* lname) {
    Line l = NULL;

    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->name, lname) == 0) {
            l = eLINES[i];
            eLINES[i] = eLINES[--LCOUNT];
            break;
        }
    }

    if (l != NULL) {
        FreeLine(l);
        eLINES = (Line*) realloc(eLINES, (LCOUNT) * sizeof(Line));

        return TRUE;
    }

    return FALSE;
}

UINT ShowLine(const char* lname, BOOL show) {
    UINT showed = 0;

    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->name, lname) == 0) {
            eLINES[i]->props->hidden = !show;
            showed++;
        }
    }

    return showed;
}

Surface MakeSurface() {
    Surface s = (Surface) malloc(sizeof(struct surface_t));
    s->props = (Properties) malloc(sizeof(struct properties_t));
    s->A.w = 1.0f;
    s->B.w = 1.0f;
    s->C.w = 1.0f;

    s->props->hidden = FALSE;
    s->props->shader = VoidHandle();

    eSURFACES = (Surface*) realloc(eSURFACES, (++SCOUNT) * sizeof(Surface));
    eSURFACES[SCOUNT-1] = s;

    return s;
}

void FreeSurface(Surface s) {
    free(s->props);
    free(s);
}

BOOL DeleteSurface(const char* pname) {
    Surface s = NULL;

    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->name, pname) == 0) {
            s = eSURFACES[i];
            eSURFACES[i] = eSURFACES[--SCOUNT];
            break;
        }
    }

    if (s != NULL) {
        FreeSurface(s);
        eSURFACES = (Surface*) realloc(eSURFACES, (--SCOUNT) * sizeof(Surface));

        return TRUE;
    }

    return FALSE;
}

UINT ShowSurface(const char* sname, BOOL show) {
    UINT showed = 0;

    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->name, sname) == 0) {
            eSURFACES[i]->props->hidden = !show;
            showed++;
        }
    }

    return showed;
}

BOOL DeleteAsset(const char* name) {
    BOOL deleted = FALSE;
    
    deleted |= DeletePoint(name);
    deleted |= (!deleted) ? DeleteLine(name) : deleted;
    deleted |= (!deleted) ? DeleteSurface(name) : deleted;

    return deleted;
}

UINT ShowAsset(const char* name, BOOL show) {
    UINT showed = 0;
    
    showed += ShowPoint(name, show);
    showed += ShowLine(name, show);
    showed += ShowSurface(name, show);

    return showed;
}

UINT DeleteGroup(const char* gname) {
    UINT deleted = 0;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->group, gname) == 0) {
            Point p = ePOINTS[i];
            ePOINTS[i--] = ePOINTS[--PCOUNT];
            FreePoint(p);
            
            deleted++;
        }
    }
    ePOINTS = (Point*) realloc(ePOINTS, PCOUNT * sizeof(Point));

    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->group, gname) == 0) {
            Line l = eLINES[i];
            eLINES[i--] = eLINES[--LCOUNT];
            FreeLine(l);

            deleted++;
        }
    }
    eLINES = (Line*) realloc(eLINES, LCOUNT * sizeof(Line));

    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->group, gname) == 0) {
            Surface s = eSURFACES[i];
            eSURFACES[i--] = eSURFACES[--SCOUNT];
            FreeSurface(s);

            deleted++;
        }
    }
    eSURFACES = (Surface*) realloc(eSURFACES, SCOUNT * sizeof(Surface));

    return deleted;
}

UINT ShowGroup(const char* gname, BOOL show) {
    UINT showed = 0;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->props->group, gname) == 0) {
            ePOINTS[i]->props->hidden = !show;

            showed++;
        }
    }
    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->props->group, gname) == 0) {
            eLINES[i]->props->hidden = !show;

            showed++;
        }
    }
    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->props->group, gname) == 0) {
            eSURFACES[i]->props->hidden = !show;

            showed++;
        }
    }

    return showed;
}

void RenderPoints() {
    for (UINT i = 0; i < PCOUNT; i++) {
        if (!ePOINTS[i]->props->hidden) {
            struct vec_t screen;
            BOOL confirm = compute_point((Vec) &ePOINTS[i]->P, &screen);
    
            if (confirm) {
                put(screen.x, screen.y, *ePOINTS[i]->props->shader, screen.z);
            }
        }
    }
}

void RenderLines() {
    for (UINT i = 0; i < LCOUNT; i++) {
        if (!eLINES[i]->props->hidden) {
            struct vec_t screen1, screen2;
            BOOL confirm = compute_line((Vec) &eLINES[i]->A, (Vec) &eLINES[i]->B, &screen1, &screen2);

            if (confirm) {
                put_line(&screen1, &screen2, *eLINES[i]->props->shader);
            }
        }
    }
}

void RenderSurfaces() {
    for (UINT i = 0; i < SCOUNT; i++) {
        
    }
}

void Render(HWND hwnd, HDC hdc) {
    ClearBuffers();

    if (CCURRENT != NULL) {
        RenderPoints();
        RenderLines();
        RenderSurfaces();
    }

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