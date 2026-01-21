#ifndef RENDER_H
    #define RENDER_H

    #include <stdlib.h>
    #include <stdio.h>

    extern const void* frame;

    extern void make_frame();
    extern void free_frame();
    
    void clear_frame();
    void style_frame();

    extern void buffer_frame();

#endif