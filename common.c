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