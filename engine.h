#ifndef ENGINE_H
    #define ENGINE_H

    #include "basic.h"
    #include "camera.h"

    static Point*       ePOINTS;
    static UINT         PCOUNT = 0;

    static Line*        eLINES;
    static UINT         LCOUNT = 0;

    static Surface*     eSURFACES;
    static UINT         SCOUNT = 0;

    void InitializeAssets();
    void TerminateAssets();

    Point MakePoint();
    void FreePoint(Point p);

    Line MakeLine();
    void FreeLine(Line l);

    Surface MakeSurface();
    void FreeSurface(Surface s);

    extern BOOL compute_point(Vec pos, Vec screen);
    extern BOOL compute_line(Vec pos1, Vec pos2, Vec screen1, Vec screen2);

    void RenderPoints(HWND hwnd, HDC hdc);
    void RenderLines(HWND hwnd, HDC hdc);
    void RenderSurfaces(HWND hwnd, HDC hdc);

    void Render(HWND hwnd, HDC hdc);

#endif