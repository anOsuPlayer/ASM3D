#ifndef COMMON_H
    #define COMMON_H

    #include <windows.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <math.h>
    #include <time.h>

    static const UINT       WIN_WIDTH   = 1200;
    static const UINT       WIN_HEIGHT  = 800;
    static const LPCSTR     WIN_NAME    = "ASM3D";

    HFONT DEFAULT_FONT();

    static const COLORREF   TEXT_FG     = RGB(255, 255, 255);
    static const COLORREF   TEXT_BG     = RGB(0, 0, 0);

    typedef enum WINMODE {

        RENDER,

        LOAD_ASSETS,

        CREATE_ASSETS

    } WINMODE;

    static UINT              FPS = 240;

    UINT GetFPS();
    void SetFPS(UINT FPS);

    LONG GetFrameSize();

    static ULONG            FRAME_TIME = 0;

    ULONG GetFrameTime();
    void SetFrameTime(ULONG fps);

    static WINMODE          MODE = RENDER;

    WINMODE GetWinMode();
    void SetWinMode(WINMODE wmode);

    static UINT             WINSTATE = 0;

    UINT GetWinState();
    void SetWinState(UINT state);
    
    void ProgressWinState();
    void DecreaseWinState();

    void ResetWinState();

    static BOOL             CAN_REPAINT = TRUE;

    BOOL CanRepaint();

    void SetRepaint();
    void ClearRepaint();

    static BOOL             SHOW_DEBUG = TRUE;

    BOOL HasDebug();

    void ShowDebug();
    void HideDebug();

#endif