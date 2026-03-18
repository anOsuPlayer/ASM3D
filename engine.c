#include "engine.h"

void InitializeAssets() {
    ePOINTS = (Point*) malloc(sizeof(Point));
    eLINES = (Line*) malloc(sizeof(Line));
    eSURFACES = (Surface*) malloc(sizeof(Surface));

    Point p = MakePoint();
    p->x = 5;
    p->y = 0;
    p->z = 0;

    Point p2 = MakePoint();
    p2->x = 3;
    p2->y = 0;
    p2->z = 5;
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
    eSURFACES[LCOUNT-1] = s;

    return s;
}

void FreeSurface(Surface s) {
    free(s);
}

void RenderPoints(HWND hwnd, HDC hdc) {
    for (UINT i = 0; i < PCOUNT; i++) {
        Vec pos = (Vec) ePOINTS[i];
        struct vec_t screen;
        compute_point(pos, &screen);

        if (screen.w != -1.0f) {
            if (screen.x >= 0 && screen.x <= Width && screen.y >= 0 && screen.y < Height) {
                FLOAT size = 3;
                Ellipse(hdc, screen.x-size, screen.y-size, screen.x+size, screen.y+size);
            }
        }
    }
}

void RenderLines(HWND hwnd, HDC hdc) {

}

void RenderSurfaces(HWND hwnd, HDC hdc) {

}

void Render(HWND hwnd, HDC hdc) {
    RenderPoints(hwnd, hdc);
    RenderLines(hwnd, hdc);
    RenderSurfaces(hwnd, hdc);
}