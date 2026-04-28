#include "common.h"

static UINT             WIN_WIDTH   = 1200;
static UINT             WIN_HEIGHT  = 800;

UINT GetWindowWidth() {
    return WIN_WIDTH;
}

UINT GetWindowHeight() {
    return WIN_HEIGHT;
}

RECT GetWindowSize() {
    return (RECT) { 0, 0, WIN_WIDTH, WIN_HEIGHT };
}

void SetWindowSize(UINT width, UINT height) {
    WIN_WIDTH = width;
    WIN_HEIGHT = height;

    ResizeFont(WIN_WIDTH);
}

static COLORREF         TEXT_FG = RGB(255, 255, 255);
static COLORREF         TEXT_BG = RGB(0, 0, 0);

COLORREF GetFontFG() {
    return TEXT_FG;
}

void SetFontFG(COLORREF c) {
    TEXT_FG = c;
}

COLORREF GetFontBG() {
    return TEXT_BG;
}

void SetFontBG(COLORREF c) {
    TEXT_BG = c;
}

static UINT             FONT_SIZE = 16;

HFONT DEFAULT_FONT() {
    static HFONT font;
    static UINT current_size;

    if (font == NULL || FONT_SIZE != current_size) {
        if (font != NULL) {
            DeleteObject(font);
        }
        
        current_size = FONT_SIZE;

        font = CreateFont(
            current_size, 0, 0, 0,
            FW_DONTCARE,
            FALSE, FALSE, FALSE,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            "Consolas"
        );
    }

    return font;
}

void ResizeFont(UINT w) {
    UINT newsize = (w / 70);
    FONT_SIZE = newsize > 16 ? 16 : newsize < 1 ? 1 : newsize;
}

static UINT             FPS = 240;
static ULONG            FRAME_TIME = 0;

static ULONG            MINFT = -1, MAXFT = 0;

UINT GetFPS() {
    return FPS;
}

void SetFPS(UINT fps) {
    FPS = fps;
    ResetFrameTimes();
}

LONG GetFrameSize() {
    return 1000000000L / FPS;
}

ULONG GetFrameTime() {
    return FRAME_TIME;
}

void ResetFrameTimes() {
    MINFT = -1;
    MAXFT = 0;
}

void SetFrameTime(ULONG lastft) {
    MINFT = (lastft < MINFT) ? lastft : MINFT;
    MAXFT = (lastft > MAXFT) ? lastft : MAXFT;

    FRAME_TIME = lastft;
}

ULONG GetLowestFrameTime() {
    return MINFT;
}

ULONG GetHighestFrameTime() {
    return MAXFT;
}

static WINMODE          MODE = RENDER;

static UINT             WINSTATE = 0;

WINMODE GetWinMode() {
    return MODE;
}

void SetWinMode(WINMODE wmode) {
    MODE = wmode;
    ResetWinState();
}

UINT GetWinState() {
    return WINSTATE;
}

void SetWinState(UINT state) {
    WINSTATE = state;
}

void ProgressWinState() {
    WINSTATE++;
}

void DecreaseWinState() {
    WINSTATE--;
}

void ResetWinState() {
    WINSTATE = 0;
}

static BOOL             SHOW_DEBUG = TRUE;

BOOL HasDebug() {
    return SHOW_DEBUG;
}

void ShowDebug() {
    SHOW_DEBUG = TRUE;
}

void HideDebug() {
    SHOW_DEBUG = FALSE;
}