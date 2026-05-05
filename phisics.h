#ifndef PHISICS_H
    #define PHISICS_H

    #include "common.h"
    #include "math.h"

    typedef struct transform_t {
        struct vec_t pos;
        struct vec_t angle;
    } *Transform;

#endif