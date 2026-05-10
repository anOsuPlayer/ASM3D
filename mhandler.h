#ifndef MHANDLER_H
    #define MHANDLER_H

    #include "common.h"
    #include "math.h"

    typedef struct module_t {
        HMODULE MOD;
        CHAR name[30];
    } *Module;

    typedef struct handle_t {
        HANDLE H;
        CHAR name[30];
        ULONG mhash;
    } *Handle;

    void InitializeHandler();
    void TerminateHandler();

    BOOL OpenModule(const CHAR* mname);
    BOOL CloseModule(const CHAR* mname);

    BOOL CompileModule(CHAR** src, UINT srcc, const CHAR* mname);
    BOOL RecompileModule(CHAR** src, UINT srcc, const CHAR* mname);

    Handle* FetchHandle(const CHAR* from, const CHAR* hname);

#endif