#ifndef MATH_H
    #define MATH_H

    #include "common.h"

    typedef struct vec_t {
        FLOAT x, y, z, w;
    } *Vec;

    typedef struct matrix_t {
        struct vec_t r0, r1, r2, r3;
    } *Matrix;

    extern Vec make_vec();
    extern void free_vec(Vec v);
    
    extern Matrix make_matrix();
    extern void free_matrix(Matrix m);

    extern FLOAT vmod(Vec v);

    extern void vneg(Vec src, Vec dst);
    extern void vnorm(Vec src, Vec dst);
    extern void vndc(Vec src, Vec dst);

    extern FLOAT vdot(Vec v1, Vec v2);
    extern void vcross(Vec v1, Vec v2, Vec dst);

    extern void mulmv(Matrix m, Vec v, Vec dst);
    extern void mulqq(Vec q1, Vec q2, Vec qdst);

#endif