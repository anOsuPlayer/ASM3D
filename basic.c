#include "basic.h"

Point MakePoint() {
    return (Point) malloc(sizeof(struct point_t));
}

void FreePoint(Point p) {
    free(p);
}

Line MakeLine() {
    return (Line) malloc(sizeof(struct line_t));
}

void FreeLine(Line l) {
    free(l);
}

Surface MakeSurface() {
    return (Surface) malloc(sizeof(struct surface_t));
}

void FreeSurface(Surface s) {
    free(s);
}