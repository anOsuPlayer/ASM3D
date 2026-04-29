#ifndef BASIC_ASSETS_H
    #define BASIC_ASSETS_H

    #include "common.h"
    #include "math.h"

    typedef struct properties_t {
        CHAR name[20];
        CHAR group[20];
        
        BOOL hidden;
        COLORREF color;
    } *Properties;

    typedef struct point_t {
        struct vec_t P;
        Properties props;
    } *Point;

    typedef struct line_properties_t {
        COLORREF end_color;
    } *LProperties;

    typedef struct line_t {
        struct vec_t A, B;
        Properties props;
        LProperties lprops;
    } *Line;

    typedef struct surface_t {
        struct vec_t A, B, C;
        Properties props;
    } *Surface;

#endif