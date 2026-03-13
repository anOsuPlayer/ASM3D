#ifndef BASE_ASSETS_H
    #define BASE_ASSETS_H

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

    Point make_point();
    void free_point(Point p);

    Line make_line();
    void free_line(Line l);

    Surface make_surface();
    void free_surface(Surface s);

#endif