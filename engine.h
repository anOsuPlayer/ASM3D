#ifndef ENGINE_H
    #define ENGINE_H

    #include "basic.h"

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

#endif