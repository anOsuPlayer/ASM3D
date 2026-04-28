#include "buffer.h"

static BUFCLEAR             CLEARMODE = NTH_AVX;

void MakeBuffers() {
    PIXELS = GetScaledWidth() * GetScaledHeight();
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
    PIXELS = GetScaledWidth() * GetScaledHeight();
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
}

UINT GetScaledWidth() {
    return (UINT) (GetWindowWidth() / RESOLUTION);
}

UINT GetScaledHeight() {
    return (UINT) (GetWindowHeight() / RESOLUTION);
}