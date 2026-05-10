#include "mhandler.h"

static Module*          MODULES;
static UINT             MCOUNT;

static Handle*          HANDLES;
static UINT             HCOUNT;

void InitializeHandler() {
    MODULES = (Module*) malloc(sizeof(struct module_t));
    HANDLES = (Handle*) malloc(sizeof(struct handle_t));
}

void TerminateHandler() {
    for (UINT i = 0; i < MCOUNT; i++) {
        free(MODULES[i]);
    }
    free(MODULES);

    for (UINT i = 0; i < HCOUNT; i++) {
        free(HANDLES[i]);
    }
    free(HANDLES);
}

BOOL OpenModule(const CHAR* mname) {
    HMODULE mod = LoadLibraryA(mname);
    
    if (mod == NULL) {
        return FALSE;
    }
    
    MODULES = (Module*) malloc((++MCOUNT) * sizeof(Module));
    
    Module m = malloc(sizeof(struct module_t));
    m->MOD = mod;
    strcpy(m->name, mname);

    MODULES[MCOUNT-1] = m;
    ULONG mhash = hash(mname);

    for (UINT i = 0; i < HCOUNT; i++) {
        if (HANDLES[i]->mhash == mhash) {
            HANDLES[i]->H = (HMODULE) GetProcAddress(m->MOD, HANDLES[i]->name);
        }
    }

    return TRUE;
}

BOOL CloseModule(const CHAR* m) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(m, MODULES[i]->name) == 0) {
            Module mod = MODULES[i];
            MODULES[i] = MODULES[MCOUNT-1];
            ULONG dmhash = hash(mod->name);

            for (UINT e = 0; e < HCOUNT; e++) {
                HANDLES[e]->H = (HANDLES[e]->mhash == dmhash) ? NULL : HANDLES[e]->H;
            }

            FreeLibrary(mod->MOD);
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CompileModule(CHAR** src, UINT srcc, const CHAR* mname) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(MODULES[i]->name, mname) == 0) {
            return FALSE;
        }
    }

    CHAR cmd[200] = "gcc -shared ";
    UINT delta = strlen(cmd);
    
    for (UINT i = 0; i < srcc; i++) {
        sprintf(cmd + delta, "%s ", src[i]);
        delta += strlen(src[i])+1;
    }

    sprintf(cmd + delta, "-o %s.dll", mname);

    INT out = system(cmd);
    return (out == 0);
}

BOOL RecompileModule(CHAR** src, UINT srcc, const CHAR* mname) {
    Module target = NULL;
    for (UINT i = 0; i < MCOUNT && target == NULL; i++) {
        if (strcmp(MODULES[i]->name, mname) == 0) {
            target = MODULES[i];
        }
    }

    if (target == NULL) {
        return FALSE;
    }

    FreeLibrary(target->MOD);

    CHAR cmd[200] = "gcc -shared ";
    UINT delta = strlen(cmd);
    
    for (UINT i = 0; i < srcc; i++) {
        sprintf(cmd + delta, "%s ", src[i]);
        delta += strlen(src[i])+1;
    }

    sprintf(cmd + delta, "-o %s.dll", mname);

    INT out = system(cmd);
    if (out != 0) {
        return FALSE;
    }

    target->MOD = LoadLibrary(mname);
    ULONG mhash = hash(mname);

    for (UINT i = 0; i < HCOUNT; i++) {
        if (HANDLES[i]->mhash == mhash) {
            HANDLES[i]->H = (HANDLE) GetProcAddress(target->MOD, HANDLES[i]->name);
        }
    }

    return TRUE;
}

Handle* FetchHandle(const CHAR* mname, const CHAR* hname) {
    ULONG mhash = hash(mname);
    for (UINT i = 0; i < HCOUNT; i++) {
        if (HANDLES[i]->mhash == mhash && strcmp(HANDLES[i]->name, hname) == 0) {
            return &HANDLES[i];
        }
    }

    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(MODULES[i]->name, mname) == 0) {
            HANDLE proc = (HANDLE) GetProcAddress(MODULES[i]->MOD, hname);

            if (proc == NULL) {
                return NULL;
            }

            HANDLES = (Handle*) malloc((++HCOUNT) * sizeof(Handle));
            
            Handle h = (Handle) malloc(sizeof(struct handle_t));
            h->H = proc;
            h->mhash = hash(mname);
            strcpy(h->name, hname);

            HANDLES[HCOUNT-1] = h;

            return &HANDLES[HCOUNT-1];
        }
    }

    return NULL;
}