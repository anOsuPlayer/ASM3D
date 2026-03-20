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