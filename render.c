#include "render.h"

void clear_frame() {
    #if defined(_WIN32)

        system("cls");

    #else

        system("clear");

    #endif
}

void style_frame() {
    
}

