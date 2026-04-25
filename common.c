#include "common.h"

HFONT DEFAULT_FONT() {
    static HFONT font;
    
    if (font == NULL) {
        font = CreateFont(
            16, 0, 0, 0,
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