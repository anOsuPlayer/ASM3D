#ifndef ENGINE_H
    #define ENGINE_H

    #include "assets.h"
    #include "camera.h"
    #include "buffer.h"
    
    extern BOOL compute_point(Vec pos, Vec screen);
    extern BOOL compute_line(Vec pos1, Vec pos2, Vec screen1, Vec screen2);
    
    void InitializeAssets();
    void TerminateAssets();

    Point MakePoint();
    void FreePoint(Point p);
    
    void DeletePoint(const char* pname);
    void ShowPoint(const char* pname, BOOL show);

    Line MakeLine();
    void FreeLine(Line l);
    
    void DeleteLine(const char* lname);
    void ShowLine(const char* lname, BOOL show);

    Surface MakeSurface();
    void FreeSurface(Surface s);
    
    void DeleteSurface(const char* sname);
    void ShowSurface(const char* sname, BOOL show);

    void DeleteAsset(const char* name);
    void ShowAsset(const char* name, BOOL show);
    
    void DeleteGroup(const char* gname);
    void ShowGroup(const char* gname, BOOL show);

    void RenderPoints(HWND hwnd, HDC hdc);
    void RenderLines(HWND hwnd, HDC hdc);
    void RenderSurfaces(HWND hwnd, HDC hdc);

    void Render(HWND hwnd, HDC hdc);

#endif