#ifndef BASIC_ASSETS_H
    #define BASIC_ASSETS_H

    #include "common.h"

    typedef struct properties_t {
        CHAR name[20];
        UINT color;
    } *Properties;

    typedef struct point_t {
        FLOAT x, y, z, w;
        Properties p;
    } *Point;

    typedef struct line_t {
        struct point_t A, B;
        Properties p;
    } *Line;

    typedef struct surface_t {
        struct point_t A, B, C;
        Properties p;
    } *Surface;

#endif