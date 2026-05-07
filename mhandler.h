#ifndef MHANDLER_H
    #define MHANDLER_H

    #include "common.h"

    void InitializeHandler();
    void TerminateHandler();

    BOOL OpenModule(const CHAR* m);
    BOOL CloseModule(const CHAR* m);

    BOOL CompileModule(CHAR** src, UINT srcc, const CHAR* hname);

    HANDLE* Fetch(const CHAR* from, const CHAR* hname);

#endif