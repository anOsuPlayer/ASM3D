#ifndef BASIC_ASSETS_H
    #define BASIC_ASSETS_H

    #include "common.h"
    #include "math.h"

    typedef struct properties_t {
        CHAR name[20];
        CHAR group[20];
        
        BOOL hidden;
        UINT color;
    } *Properties;

    typedef struct point_t {
        struct vec_t P;
        Properties p;
    } *Point;

    typedef struct line_t {
        struct vec_t A, B;
        Properties p;
    } *Line;

    typedef struct surface_t {
        struct vec_t A, B, C;
        Properties p;
    } *Surface;

#endif