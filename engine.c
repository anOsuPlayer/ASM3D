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
    ePOINTS = realloc(ePOINTS, ++PCOUNT);
    ePOINTS[PCOUNT-1] = p;
}

void FreePoint(Point p) {
    free(p);
}

Line MakeLine() {
    Line l = (Line) malloc(sizeof(struct line_t));
    eLINES = realloc(eLINES, ++LCOUNT);
    eLINES[LCOUNT-1] = l;
}

void FreeLine(Line l) {
    free(l);
}

Surface MakeSurface() {
    Surface s = (Surface) malloc(sizeof(struct surface_t));
    eSURFACES = realloc(eSURFACES, ++SCOUNT);
    eSURFACES[LCOUNT-1] = s;
}

void FreeSurface(Surface s) {
    free(s);
}