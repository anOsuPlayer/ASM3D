#include "mhandler.h"

static Module*          MODULES;
static UINT             MCOUNT;

static Handle*          HANDLES;
static UINT             HCOUNT;

static Handle           VOID_HANDLE;

void InitializeHandler() {
    MODULES = (Module*) malloc(sizeof(struct module_t));
    HANDLES = (Handle*) malloc(sizeof(struct handle_t));

    VOID_HANDLE = (Handle) malloc(sizeof(struct handle_t));
    VOID_HANDLE->H = NULL;
    strcpy(VOID_HANDLE->name, "");
}

void TerminateHandler() {
    for (UINT i = 0; i < MCOUNT; i++) {
        FreeLibrary(MODULES[i]->MOD);
        free(MODULES[i]);
    }
    free(MODULES);

    for (UINT i = 0; i < HCOUNT; i++) {
        free(HANDLES[i]);
    }
    free(HANDLES);

    free(VOID_HANDLE);
}

BOOL OpenModule(const CHAR* mname) {
    Module m = NULL;

    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(MODULES[i]->name, mname) == 0 && MODULES[i]->MOD == NULL) {
            m = MODULES[i];
            break;
        }
    }

    HMODULE mod = LoadLibraryA(mname);
    
    if (mod == NULL) {
        return FALSE;
    }
    
    if (m == NULL) {
        MODULES = (Module*) malloc((++MCOUNT) * sizeof(Module));
        m = malloc(sizeof(struct module_t));
        MODULES[MCOUNT-1] = m;
    }

    m->MOD = mod;
    strcpy(m->name, mname);

    ULONG mhash = hash(mname);

    for (UINT i = 0; i < HCOUNT; i++) {
        if (HANDLES[i]->mhash == mhash) {
            HANDLES[i]->H = (HMODULE) GetProcAddress(m->MOD, HANDLES[i]->name);
        }
    }

    return TRUE;
}

BOOL CloseModule(const CHAR* mname) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(mname, MODULES[i]->name) == 0) {
            Module mod = MODULES[i];
            MODULES[i] = MODULES[MCOUNT-1];
            ULONG dmhash = hash(mod->name);

            for (UINT e = 0; e < HCOUNT; e++) {
                HANDLES[e]->H = (HANDLES[e]->mhash == dmhash) ? NULL : HANDLES[e]->H;
            }

            FreeLibrary(mod->MOD);
            mod->MOD = NULL;
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CompileModule(CHAR (*src)[30], UINT srcc, const CHAR* mname) {
    for (UINT i = 0; i < MCOUNT; i++) {
        if (strcmp(MODULES[i]->name, mname) == 0 && MODULES[i]->MOD != NULL) {
            return FALSE;
        }
    }

    CHAR cmd[200] = "gcc -shared ";
    UINT delta = strlen(cmd);
    
    for (UINT i = 0; i < srcc; i++) {
        FILE* f = fopen(src[i], "r");
        if (f == NULL) {
            return FALSE;
        }
        fclose(f);

        sprintf(cmd + delta, "%s ", src[i]);
        delta += strlen(src[i])+1;
    }

    sprintf(cmd + delta, "-o %s.dll", mname);

    INT out = system(cmd);
    return (out == 0);
}

BOOL RecompileModule(CHAR (*src)[30], UINT srcc, const CHAR* mname) {
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
        FILE* f = fopen(src[i], "r");
        if (f == NULL) {
            return FALSE;
        }
        fclose(f);
        
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
                return &VOID_HANDLE;
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

    return &VOID_HANDLE;
}

Handle* VoidHandle() {
    return &VOID_HANDLE;
}