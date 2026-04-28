#include "buffer.h"

static BUFCLEAR             CLEARMODE = NTH_AVX;

BUFCLEAR GetBufClearMode() {
    return CLEARMODE;
}

void SetBufClearMode(BUFCLEAR mode) {
    CLEARMODE = mode;
    ResetFrameTimes();
}

void MakeBuffers() {
    PIXELS = GetWindowWidth() * GetWindowHeight();
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

void UpdateBuffers() {
    PIXELS = GetWindowWidth() * GetWindowHeight();
    BUFSIZE = PIXELS * 4;

    ZBUFFER = (FLOAT*) _aligned_realloc(ZBUFFER, BUFSIZE, 64);
    CBUFFER = (UINT*) _aligned_realloc(CBUFFER, BUFSIZE, 64);

    if (BMI.bmiHeader.biSize == 0) {
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biPlanes = 1;
        BMI.bmiHeader.biBitCount = 32;
        BMI.bmiHeader.biCompression = BI_RGB;
    }

    BMI.bmiHeader.biWidth = GetWindowWidth();
    BMI.bmiHeader.biHeight = -((INT) GetWindowHeight());
}