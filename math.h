#ifndef MATH_H
    #define MATH_H

    #include "common.h"

    typedef struct vec_t {
        float x, y, z, w;
    } *Vec;

    typedef struct matrix_t {
        struct vec_t r0, r1, r2, r3;
    } *Matrix;

    extern Vec make_vec();
    extern void free_vec(Vec v);

    extern Matrix make_matrix();
    extern void free_matrix(Matrix m);

#endif