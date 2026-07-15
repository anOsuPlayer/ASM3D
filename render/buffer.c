#include "buffer.h"

void _c_clear_bufs() {
    UINT INF = 0x7F800000;
    FLOAT clear = *((FLOAT*) &INF);

    UINT element_count = BUFSIZE / sizeof(uint32_t);

    for (UINT i = 0; i < element_count; i++) {
        ZBUFFER[i] = clear;
        CBUFFER[i] = ENGINE_BG;
    }
}

void _c_put(FLOAT x, FLOAT y, Shader* shader, FLOAT z) {
    INT index = (((INT) GetWindowWidth()) * ((INT) y)) + ((INT) x) - 1;

    if (index < 0) {
        return;
    }
    if (index > PIXELS) {
        return;
    }

    if (ZBUFFER[index] >= z) {
        UINT color;

        if (shader != NULL) {
            color = (*((shader_t*) *shader))(0.0f, 0.0f, ENGINE_TIME);
        }
        else {
            color = 0x00FFFFFF;
        }

        ZBUFFER[index] = z;
        CBUFFER[index] = color;
    }
}

void put(FLOAT x, FLOAT y, Shader* shader, FLOAT z) {
    switch (GetEngineMode()) {
        case PLAINC : { _c_put(x, y, shader, z); break; }
        case AVX256 :
        case AVX512 : { _256_put(x, y, shader, z); break; }
    }
}

void _c_put_line(Vec p1, Vec p2, Shader* shader) {
    struct vec_t delta;
    delta.x = p2->x - p1->x;
    delta.y = p2->y - p1->y;
    delta.z = p2->z - p1->z;
    delta.w = p2->w - p1->w;

    FLOAT abs_x = fabsf((FLOAT) delta.x);
    FLOAT abs_y = fabsf((FLOAT) delta.y);
    FLOAT steps = (abs_x > abs_y) ? abs_x : abs_y;

    INT isteps = (INT) steps;

    if (isteps == 0) {
        _c_put(p1->x, p1->y, NULL, p1->z);
        return;
    }

    struct vec_t inc;
    inc.x = delta.x / steps;
    inc.y = delta.y / steps;
    inc.z = delta.z / steps;
    inc.w = delta.w / steps;

    FLOAT t_inc = 1.0f / steps;
    FLOAT t = 0.0f;

    struct vec_t curr = *p1;

    for (INT i = isteps; i > 0; i--) {
        INT index = (((INT) GetWindowWidth()) * ((INT) curr.y)) + ((INT) curr.x) - 1;

        if (index >= 0 && index <= PIXELS) {
            if (ZBUFFER[index] >= curr.z) {
                UINT color;

                if (shader != NULL) {
                    color = (*((shader_t*) *shader))(t, 0.0f, ENGINE_TIME);
                }
                else {
                    color = 0x00FFFFFF;
                }

                ZBUFFER[index] = curr.z;
                CBUFFER[index] = color;
            }
        }

        t += t_inc;
        curr.x += inc.x;
        curr.y += inc.y;
        curr.z += inc.z;
        curr.w += inc.w;
    }
}

void put_line(Vec p1, Vec p2, Shader* shader) {
    switch (GetEngineMode()) {
        case PLAINC : { _c_put_line(p1, p2, shader); break; }
        case AVX256 : 
        case AVX512 : { _256_put_line(p1, p2, shader); break; }
    }
}

static BUFCLEAR             CLEARMODE = NTH_AVX;

void ClearBuffers() {
    switch (GetEngineMode()) {
        case PLAINC : {
            _c_clear_bufs();
            break;
        }
        case AVX256 : {
            switch (GetBufClearMode()) {
                case ALIGNED_AVX : { _256_clear_bufs(); break; }
                case DUAL_ALIGNED_AVX : { _256_clear_bufs_dual(); break; }
                case NTH_AVX : { _256_clear_bufs_nth(); break; }
                case DUAL_NTH_AVX : {_256_clear_bufs_nthd(); break; }
            }
            break;
        }
        case AVX512 : {
            switch (GetBufClearMode()) {
                case ALIGNED_AVX : { _512_clear_bufs(); break; }
                case DUAL_ALIGNED_AVX : { _512_clear_bufs_dual(); break; }
                case NTH_AVX : { _512_clear_bufs_nth(); break; }
                case DUAL_NTH_AVX : { _512_clear_bufs_nthd(); break; }
            }
            break;
        }
    }
}

void MakeBuffers() {
    PIXELS = (GetScaledWidth() + 1) * GetScaledHeight();
    BUFSIZE = PIXELS * 4;
    FreeBuffers();

    ZBUFFER = (FLOAT*) _aligned_malloc(BUFSIZE, 64);
    CBUFFER = (UINT*) _aligned_malloc(BUFSIZE, 64);
}

void FreeBuffers() {
    if (ZBUFFER != NULL) {
        _aligned_free(ZBUFFER);
        _aligned_free(CBUFFER);
    }
}

BUFCLEAR GetBufClearMode() {
    return CLEARMODE;
}

void SetBufClearMode(BUFCLEAR mode) {
    CLEARMODE = mode;
    ResetFrameTimes();
}

COLORREF GetEngineBG() {
    return ENGINE_BG;
}

void SetEngineBG(COLORREF col) {
    ENGINE_BG = col;
}

static BITMAPINFO           BMI;

BITMAPINFO* GetBMI() {
    return &BMI;
}

static FLOAT                RESOLUTION = 1.0f;

extern FLOAT                Width, Height;

void UpdateBuffers() {
    PIXELS = (GetScaledWidth() + 1) * GetScaledHeight();
    BUFSIZE = PIXELS * 4;

    Width = ((FLOAT) GetScaledWidth());
    Height = ((FLOAT) GetScaledHeight());

    ZBUFFER = (FLOAT*) _aligned_realloc(ZBUFFER, BUFSIZE, 64);
    CBUFFER = (UINT*) _aligned_realloc(CBUFFER, BUFSIZE, 64);

    if (BMI.bmiHeader.biSize == 0) {
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biPlanes = 1;
        BMI.bmiHeader.biBitCount = 32;
        BMI.bmiHeader.biCompression = BI_RGB;
    }

    BMI.bmiHeader.biWidth = GetScaledWidth();
    BMI.bmiHeader.biHeight = -((INT) GetScaledHeight());
}

FLOAT GetResolution() {
    return RESOLUTION;
}

void SetResolution(FLOAT res) {
    RESOLUTION = res;

    UpdateBuffers();
    ResetFrameTimes();
}

UINT GetScaledWidth() {
    return (UINT) (GetWindowWidth() / RESOLUTION);
}

UINT GetScaledHeight() {
    return (UINT) (GetWindowHeight() / RESOLUTION);
}