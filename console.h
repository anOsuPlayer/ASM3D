#ifndef CONSOLE_H
    #define CONSOLE_H

    #include "engine.h"

    static pthread_t CONSOLE_THREAD = 0;

    static HWND WINDOW;
    static BOOL IS_RUNNING = FALSE;

    BOOL IsRunning();

    void InitializeConsole(HWND hwnd);
    void TerminateConsole();

#endif