#ifndef BASIC_ASSETS_H
    #define BASIC_ASSETS_H

    #include "common.h"

    typedef struct point_t {
        float x, y, z;
    } *Point;

    typedef struct line_t {
        float x1, y1, z1;
        float x2, y2, z2;
    } *Line;

    typedef struct surface_t {
        float x1, y1, z1;
        float x2, y2, z2;
        float x3, y3, z3;
    } *Surface;

    Point MakePoint();
    void FreePoint(Point p);

    Line MakeLine();
    void FreeLine(Line l);

    Surface MakeSurface();
    void FreeSurface(Surface s);

#endif