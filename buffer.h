#ifndef BUFFER_H
    #define BUFFER_H

    #include "common.h"

    extern FLOAT*               ZBUFFER;
    extern UINT*                CBUFFER;

    extern LONGLONG             BUFSIZE;
    extern LONG                 PIXELS;

    extern COLORREF             ENGINE_BG;

    extern void clear_bufs();
    extern void clear_bufs_nth();
    extern void clear_bufs_dual();

    extern void put(FLOAT x, FLOAT y, COLORREF color, FLOAT z);

    typedef enum BUFCLEAR {

        ALIGNED_AVX,

        DUAL_ALIGNED_AVX,
        
        NTH_AVX

    } BUFCLEAR;

    BUFCLEAR GetBufClearMode();
    void SetBufClearMode(BUFCLEAR mode);

    void MakeBuffers();
    void FreeBuffers();

    COLORREF GetEngineBG();
    void SetEngineBG(COLORREF col);

    BITMAPINFO* GetBMI();
    void UpdateBuffers();

#endif