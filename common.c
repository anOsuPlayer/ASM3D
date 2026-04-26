#include "common.h"

HFONT DEFAULT_FONT() {
    static HFONT font;
    static UINT current_size;

    if (font == NULL || FONT_SIZE != current_size) {
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

HBRUSH BACKGROUND() {
    static HBRUSH brush;

    if (brush == NULL) {
        brush = CreateSolidBrush(0x00000000);
    }

    return brush;
}

UINT GetFPS() {
    return FPS;
}

void SetFPS(UINT fps) {
    FPS = fps;
}

LONG GetFrameSize() {
    return 1000000000L / FPS;
}

ULONG GetFrameTime() {
    return FRAME_TIME;
}

void SetFrameTime(ULONG lastft) {
    FRAME_TIME = lastft;
}

WINMODE GetWinMode() {
    return MODE;
}

void SetWinMode(WINMODE wmode) {
    MODE = wmode;
    ResetWinState();
    SetRepaint();
}

UINT GetWinState() {
    return WINSTATE;
}

void SetWinState(UINT state) {
    WINSTATE = state;
    SetRepaint();
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

BOOL CanRepaint() {
    return CAN_REPAINT;
}

void SetRepaint() {
    CAN_REPAINT = TRUE;
}

void ClearRepaint() {
    CAN_REPAINT = FALSE;
}

BOOL HasDebug() {
    return SHOW_DEBUG;
}

void ShowDebug() {
    SHOW_DEBUG = TRUE;
}

void HideDebug() {
    SHOW_DEBUG = FALSE;
}