#include "math.h"

void _c_mulmv(Matrix m, Vec v, Vec dst) {
    dst->x = (m->r0.x * v->x) + (m->r0.y * v->y) + (m->r0.z * v->z) + (m->r0.w * v->w);
    dst->y = (m->r1.x * v->x) + (m->r1.y * v->y) + (m->r1.z * v->z) + (m->r1.w * v->w);
    dst->z = (m->r2.x * v->x) + (m->r2.y * v->y) + (m->r2.z * v->z) + (m->r2.w * v->w);
    dst->w = (m->r3.x * v->x) + (m->r3.y * v->y) + (m->r3.z * v->z) + (m->r3.w * v->w);
}

void mulmv(Matrix m, Vec v, Vec dst) {
    switch (GetEngineMode()) {
        case PLAINC : { _c_mulmv(m, v, dst); break; }
        case AVX256 : { _256_mulmv(m, v, dst); break; }
        case AVX512 : { _512_mulmv(m, v, dst); break; }
    }
}

void _c_mulqq(Vec q1, Vec q2, Vec qdst) {
    qdst->x = (q1->w * q2->x) + (q1->x * q2->w) + (q1->y * q2->z) - (q1->z * q2->y);
    qdst->y = (q1->w * q2->y) - (q1->x * q2->z) + (q1->y * q2->w) + (q1->z * q2->x);
    qdst->z = (q1->w * q2->z) + (q1->x * q2->y) - (q1->y * q2->x) + (q1->z * q2->w);
    qdst->w = (q1->w * q2->w) - (q1->x * q2->x) - (q1->y * q2->y) - (q1->z * q2->z);
}

void mulqq(Vec q1, Vec q2, Vec qdst) {
    switch (GetEngineMode()) {
        case PLAINC : { _c_mulqq(q1, q2, qdst); break; }
        case AVX256 : { _256_mulqq(q1, q2, qdst); break; }
        case AVX512 : { _512_mulqq(q1, q2, qdst); break; }
    }
}

ULONG hash(const CHAR* str) {
    ULONG hash = 5381;
    UINT c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}