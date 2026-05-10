#ifndef SHADERS_H
    #define SHADERS_H

    #include "common.h"

    typedef void* Shader;

    typedef void(*Uniform)(COLORREF*);
    typedef void(*UniformTemporal)(COLORREF*, ULONGLONG);

    typedef void(*Linear)(COLORREF**, UINT*, FLOAT);
    typedef void(*LinearTemporal)(COLORREF**, UINT*, FLOAT, ULONGLONG);

    typedef void(*Areal)(COLORREF**, UINT*, FLOAT, FLOAT);
    typedef void(*ArealTemporal)(COLORREF**, UINT*, FLOAT, FLOAT, ULONGLONG);

#endif