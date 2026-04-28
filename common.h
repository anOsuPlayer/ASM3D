#ifndef COMMON_H
    #define COMMON_H

    #include <windows.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <math.h>
    #include <time.h>
    #include <pthread.h>

    static const LPCSTR             WIN_NAME    = "ASM3D";

    UINT GetWindowWidth();
    UINT GetWindowHeight();

    RECT GetWindowSize();
    void SetWindowSize(UINT width, UINT height);

    COLORREF GetFontFG();
    void SetFontFG(COLORREF c);

    COLORREF GetFontBG();
    void SetFontBG(COLORREF c);
    
    HFONT DEFAULT_FONT();
    void ResizeFont(UINT w);

    UINT GetFPS();
    void SetFPS(UINT FPS);

    LONG GetFrameSize();

    ULONG GetFrameTime();
    void SetFrameTime(ULONG fps);

    ULONG GetLowestFrameTime();
    ULONG GetHighestFrameTime();

    void ResetFrameTimes();

    typedef enum WINMODE {

        RENDER,

        CONSOLE

    } WINMODE;

    WINMODE GetWinMode();
    void SetWinMode(WINMODE wmode);

    UINT GetWinState();
    void SetWinState(UINT state);
    
    void ProgressWinState();
    void DecreaseWinState();

    void ResetWinState();

    BOOL HasDebug();

    void ShowDebug();
    void HideDebug();

#endif