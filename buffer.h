#ifndef BUFFER_H
    #define BUFFER_H

    #include "common.h"
    #include "assets.h"

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

    extern void _256_put_line(Vec p1, Vec p2, COLORREF c1, COLORREF c2);
    extern void _512_put_line(Vec p1, Vec p2, COLORREF c1, COLORREF c2);

    void put_line(Vec p1, Vec p2, COLORREF c1, COLORREF c2);

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