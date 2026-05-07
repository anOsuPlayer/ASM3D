#include "mhandler.h"

static HMODULE*         MODULES;
static CHAR**           MNAMES;

static UINT             MCOUNT;

static HANDLE*          HANDLES;
static UINT*            HMREF;
static CHAR**           HNAMES;

static UINT             HCOUNT;

void InitializeHandler() {
    MODULES = (HMODULE*) malloc(sizeof(HMODULE));
    MNAMES = (CHAR**) malloc(sizeof(CHAR*));

    HANDLES = (HANDLE*) malloc(sizeof(HANDLE));
    HNAMES = (CHAR**) malloc(sizeof(CHAR*));
    HMREF = (UINT*) malloc(sizeof(UINT));
}

void TerminateHandler() {
    for (UINT i = 0; i < MCOUNT; i++) {
        FreeLibrary(MODULES[i]);
        free(MNAMES[i]);
    }

    free(MODULES);
    free(MNAMES);

    for (UINT i = 0; i < HCOUNT; i++) {
        free(HNAMES[i]);
    }

    free(HANDLES);
    free(HNAMES);
    free(HMREF);
}

BOOL OpenModule(const CHAR* m) {
    HMODULE mod = LoadLibraryA(m);
    
    if (mod == NULL) {
        return 0;
    }
    
    MODULES = (HMODULE*) malloc((++MCOUNT) * sizeof(HMODULE));
    MNAMES = (CHAR**) malloc((MCOUNT) * sizeof(CHAR*));
    
    MODULES[MCOUNT-1] = mod;

    CHAR* name = (CHAR*) malloc(30 * sizeof(CHAR));
    strcpy(name, m);
    MNAMES[MCOUNT-1] = name;

    return 1;
}

BOOL CloseModule(const CHAR* m) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(m, MNAMES[i]) == 0) {
            HMODULE mod = MODULES[i];
            MODULES[i] = MODULES[MCOUNT-1];
            MNAMES[i] = MNAMES[MCOUNT-1];

            for (UINT e = 0; e < HCOUNT; e++) {
                HANDLES[e] = (HMREF[e] == i) ? NULL : HANDLES[e];
            }

            FreeLibrary(mod);
            return 1;
        }
    }

    return 0;
}

BOOL CompileModule(CHAR** src, UINT srcc, const CHAR* hname) {
    CHAR cmd[200] = "gcc -shared ";
    UINT delta = strlen(cmd);
    
    for (UINT i = 0; i < srcc; i++) {
        sprintf(cmd + delta, "%s ", src[i]);
        delta += strlen(src[i])+1;
    }

    sprintf(cmd + delta, "-o %s.dll", hname);

    INT out = system(cmd);
    return (out == 0);
}

HANDLE* Fetch(const CHAR* from, const CHAR* hname) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(from, MNAMES[i]) == 0) {
            HANDLE h = (HANDLE) GetProcAddress(MODULES[i], hname);
            
            if (h == NULL) {
                return NULL;
            }
            
            HANDLES = (HANDLE*) malloc((++HCOUNT) * sizeof(HANDLE));
            HNAMES = (CHAR**) malloc((HCOUNT) * sizeof(CHAR*));
            HMREF = (UINT*) malloc((HCOUNT) * sizeof(UINT));
            
            HANDLES[HCOUNT-1] = h;

            CHAR* name = (CHAR*) malloc(30 * sizeof(CHAR));
            strcpy(name, hname);
            HNAMES[HCOUNT-1] = name;

            HMREF[HCOUNT-1] = i;

            return &HANDLES[HCOUNT-1];
        }
    }

    return NULL;
}