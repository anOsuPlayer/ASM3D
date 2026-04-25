#include "engine.h"

void SetupAxes() {
    Line X = MakeLine();
    X->A.x = 0; X->A.y = 0; X->A.z = 0;
    X->B.x = 100000; X->B.y = 0; X->B.z = 0;
    X->p->color = 0x00000055;

    Line Y = MakeLine();
    Y->A.x = 0; Y->A.y = 0; Y->A.z = 0;
    Y->B.x = 0; Y->B.y = 100000; Y->B.z = 0;
    Y->p->color = 0x00005500;

    Line Z = MakeLine();
    Z->A.x = 0; Z->A.y = 0; Z->A.z = 0;
    Z->B.x = 0; Z->B.y = 0; Z->B.z = 100000;
    Z->p->color = 0x00550000;

    Point O = MakePoint();
    O->x = 0; O->y = 0; O->z = 0;
    O->p->color = 0x00555555;
}

void SetupGrid() {
    for (INT i = 0; i < 100; i++) {
        Line G1 = MakeLine();
        G1->A.x = 2*i; G1->A.y = 200; G1->A.z = 0;
        G1->B.x = 2*i; G1->B.y = -200; G1->B.z = 0;
        G1->p->color = 0x00111111;
        Line G2 = MakeLine();
        G2->A.x = -2*i; G2->A.y = 200; G2->A.z = 0;
        G2->B.x = -2*i; G2->B.y = -200; G2->B.z = 0;
        G2->p->color = 0x00111111;

        Line G3 = MakeLine();
        G3->A.x = 200; G3->A.y = 2*i; G3->A.z = 0;
        G3->B.x = -200; G3->B.y = 2*i; G3->B.z = 0;
        G3->p->color = 0x00111111;
        Line G4 = MakeLine();
        G4->A.x = 200; G4->A.y = -2*i; G4->A.z = 0;
        G4->B.x = -200; G4->B.y = -2*i; G4->B.z = 0;
        G4->p->color = 0x00111111;
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
    p->p = (Properties) malloc(sizeof(struct properties_t));
    p->w = 1.0f;

    p->p->color = 0x00ffffff;
    
    ePOINTS = realloc(ePOINTS, (++PCOUNT) * sizeof(struct point_t));
    ePOINTS[PCOUNT-1] = p;

    return p;
}

void DeletePoint(const char* pname) {
    Point p = NULL;

    for (UINT i = 0; i < PCOUNT; i++) {
        if (strcmp(ePOINTS[i]->p->name, pname) == 0) {
            p = ePOINTS[i];
            for (UINT e = i+1; e < PCOUNT; e++) {
                ePOINTS[e-1] = ePOINTS[e];
            }
            
            break;
        }
    }

    FreePoint(p);
    ePOINTS = realloc(ePOINTS, (--PCOUNT) * sizeof(struct point_t));
}

void FreePoint(Point p) {
    free(p->p);
    free(p);
}

Line MakeLine() {
    Line l = (Line) malloc(sizeof(struct line_t));
    l->p = (Properties) malloc(sizeof(struct properties_t));
    l->A.w = 1.0f;
    l->B.w = 1.0f;

    l->p->color = 0x00ffffff;

    eLINES = realloc(eLINES, (++LCOUNT) * sizeof(struct line_t));
    eLINES[LCOUNT-1] = l;

    return l;
}

void DeleteLine(const char* pname) {
    Line l = NULL;

    for (UINT i = 0; i < LCOUNT; i++) {
        if (strcmp(eLINES[i]->p->name, pname) == 0) {
            l = eLINES[i];
            for (UINT e = i+1; e < LCOUNT; e++) {
                eLINES[e-1] = eLINES[e];
            }
            
            break;
        }
    }

    FreeLine(l);
    eLINES = realloc(eLINES, (--LCOUNT) * sizeof(struct point_t));
}

void FreeLine(Line l) {
    free(l->p);
    free(l);
}

Surface MakeSurface() {
    Surface s = (Surface) malloc(sizeof(struct surface_t));
    s->p = (Properties) malloc(sizeof(struct properties_t));
    s->A.w = 1.0f;
    s->B.w = 1.0f;
    s->C.w = 1.0f;

    s->p->color = 0x00ffffff;

    eSURFACES = realloc(eSURFACES, (++SCOUNT) * sizeof(struct surface_t));
    eSURFACES[SCOUNT-1] = s;

    return s;
}

void DeleteSurface(const char* pname) {
    Surface s = NULL;

    for (UINT i = 0; i < SCOUNT; i++) {
        if (strcmp(eSURFACES[i]->p->name, pname) == 0) {
            s = eSURFACES[i];
            for (UINT e = i+1; e < SCOUNT; e++) {
                eSURFACES[e-1] = eSURFACES[e];
            }
            
            break;
        }
    }

    FreeSurface(s);
    eSURFACES = realloc(eSURFACES, (--SCOUNT) * sizeof(struct point_t));
}

void FreeSurface(Surface s) {
    free(s->p);
    free(s);
}

void RenderPoints(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < PCOUNT; i++) {
        struct vec_t screen;
        BOOL confirm = compute_point((Vec) ePOINTS[i], &screen);

        if (confirm) {
            Properties p = ePOINTS[i]->p;
            HBRUSH brush = CreateSolidBrush(p->color);
            HBRUSH old_brush = (HBRUSH)SelectObject(hdc, brush);
            
            Ellipse(hdc, screen.x-5, screen.y-5, screen.x+5, screen.y+5);

            SelectObject(hdc, old_brush);
            DeleteObject(brush);
        }
    }
}

void RenderLines(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < LCOUNT; i++) {
        struct vec_t screen1, screen2;
        BOOL confirm = compute_line((Vec) &eLINES[i]->A, (Vec) &eLINES[i]->B, &screen1, &screen2);

        if (confirm) {
            Properties p = eLINES[i]->p;
            HPEN pen = CreatePen(PS_SOLID, 3, p->color);
            HPEN old_pen = (HPEN)SelectObject(hdc, pen);

            MoveToEx(hdc, screen1.x, screen1.y, NULL);
            LineTo(hdc, screen2.x, screen2.y);

            SelectObject(hdc, old_pen);
            DeleteObject(pen);
        }
    }
}

void RenderSurfaces(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < SCOUNT; i++) {
        
    }
}

void RenderBackground(HWND hwnd, HDC hdc) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    FillRect(hdc, &rc, BACKGROUND());
}

void Render(HWND hwnd, HDC hdc) {
    RenderBackground(hwnd, hdc);

    RenderSurfaces(hwnd, hdc);
    RenderLines(hwnd, hdc);
    RenderPoints(hwnd, hdc);
}