#ifndef BUFFER_H
    #define BUFFER_H

    #include "common.h"

    extern FLOAT*               ZBUFFER;
    extern UINT*                CBUFFER;

    extern LONGLONG             BUFSIZE;
    extern LONG                 PIXELS;

    extern COLORREF             ENGINE_BG;

    extern void _256_clear_bufs();
    extern void _512_clear_bufs();

    extern void _256_clear_bufs_nth();
    extern void _512_clear_bufs_nth();

    extern void _256_clear_bufs_dual();
    extern void _512_clear_bufs_dual();
    
    extern void _256_clear_bufs_nthd();
    extern void _512_clear_bufs_nthd();

    extern void put(FLOAT x, FLOAT y, COLORREF color, FLOAT z);

    void ClearBuffers();

    void MakeBuffers();
    void FreeBuffers();
    
    typedef enum BUFCLEAR {

        ALIGNED_AVX,

        DUAL_ALIGNED_AVX,
        
        NTH_AVX,

        DUAL_NTH_AVX

    } BUFCLEAR;
    
    BUFCLEAR GetBufClearMode();
    void SetBufClearMode(BUFCLEAR mode);

    COLORREF GetEngineBG();
    void SetEngineBG(COLORREF col);

    BITMAPINFO* GetBMI();
    void UpdateBuffers();

    FLOAT GetResolution();
    void SetResolution(FLOAT res);

    UINT GetScaledWidth();
    UINT GetScaledHeight();

#endif