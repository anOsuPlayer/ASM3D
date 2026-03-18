#ifndef BASIC_ASSETS_H
    #define BASIC_ASSETS_H

    #include "common.h"

    typedef struct point_t {
        float x, y, z, w;
    } *Point;

    typedef struct line_t {
        struct point_t A, B;
    } *Line;

    typedef struct surface_t {
        struct point_t A, B, C;
    } *Surface;

#endif