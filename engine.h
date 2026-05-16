#ifndef ENGINE_H
    #define ENGINE_H

    #include "assets.h"
    #include "camera.h"
    #include "buffer.h"

    extern ULONGLONG        ENGINE_TIME;
    
    extern BOOL compute_point(Vec pos, Vec screen);
    extern BOOL compute_line(Vec pos1, Vec pos2, Vec screen1, Vec screen2);
    
    void InitializeAssets();
    void TerminateAssets();

    Point MakePoint();
    void FreePoint(Point p);
    
    BOOL DeletePoint(const char* pname);
    UINT ShowPoint(const char* pname, BOOL show);

    Line MakeLine();
    void FreeLine(Line l);
    
    BOOL DeleteLine(const char* lname);
    UINT ShowLine(const char* lname, BOOL show);

    Surface MakeSurface();
    void FreeSurface(Surface s);
    
    BOOL DeleteSurface(const char* sname);
    UINT ShowSurface(const char* sname, BOOL show);

    BOOL DeleteAsset(const char* name);
    UINT ShowAsset(const char* name, BOOL show);
    
    UINT DeleteGroup(const char* gname);
    UINT ShowGroup(const char* gname, BOOL show);

    void RenderPoints();
    void RenderLines();
    void RenderSurfaces();

    void Render(HWND hwnd, HDC hdc);

#endif