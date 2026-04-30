#include "math.h"

void mulmv(Matrix m, Vec v, Vec dst) {
    switch (GetEngineMode()) {
        case AVX256 : { _256_mulmv(m, v, dst); break; }
        case AVX512 : { _512_mulmv(m, v, dst); break; }
    }
}

void mulqq(Vec q1, Vec q2, Vec qdst) {
    switch (GetEngineMode()) {
        case AVX256 : { _256_mulqq(q1, q2, qdst); break; };
        case AVX512 : { _512_mulqq(q1, q2, qdst); break; };
    }
}