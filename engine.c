#include "engine.h"

void InitializeAssets() {
    ePOINTS = (Point*) malloc(sizeof(Point));
    eLINES = (Line*) malloc(sizeof(Line));
    eSURFACES = (Surface*) malloc(sizeof(Surface));
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
    p->w = 1.0f;

    ePOINTS = realloc(ePOINTS, (++PCOUNT) * sizeof(struct point_t));
    ePOINTS[PCOUNT-1] = p;

    return p;
}

void FreePoint(Point p) {
    free(p);
}

Line MakeLine() {
    Line l = (Line) malloc(sizeof(struct line_t));
    l->A.w = 1.0f;
    l->B.w = 1.0f;

    eLINES = realloc(eLINES, (++LCOUNT) * sizeof(struct line_t));
    eLINES[LCOUNT-1] = l;

    return l;
}

void FreeLine(Line l) {
    free(l);
}

Surface MakeSurface() {
    Surface s = (Surface) malloc(sizeof(struct surface_t));
    s->A.w = 1.0f;
    s->B.w = 1.0f;
    s->C.w = 1.0f;

    eSURFACES = realloc(eSURFACES, (++SCOUNT) * sizeof(struct surface_t));
    eSURFACES[SCOUNT-1] = s;

    return s;
}

void FreeSurface(Surface s) {
    free(s);
}

void RenderPoints(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < PCOUNT; i++) {
        struct vec_t screen;
        BOOL confirm = compute_point((Vec) ePOINTS[i], &screen);

        if (confirm) {
            FLOAT size = 5 * powf(screen.z, 3.0f);
            Ellipse(hdc, screen.x-size, screen.y-size, screen.x+size, screen.y+size);
        }
    }
}

void RenderLines(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < LCOUNT; i++) {
        struct vec_t screen1, screen2;
        BOOL confirm = compute_line((Vec) &eLINES[i]->A, (Vec) &eLINES[i]->B, &screen1, &screen2);

        if (confirm) {
            HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

            MoveToEx(hdc, screen1.x, screen1.y, NULL);
            LineTo(hdc, screen2.x, screen2.y);

            SelectObject(hdc, hOldPen);
            DeleteObject(hPen);
        }
    }
}

void RenderSurfaces(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < SCOUNT; i++) {
        
    }
}

void Render(HWND hwnd, HDC hdc) {
    RenderSurfaces(hwnd, hdc);
    RenderLines(hwnd, hdc);
    RenderPoints(hwnd, hdc);
}