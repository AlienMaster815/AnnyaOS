#include "WinCreation.h"



USER32_API
HWND
CreateWindowExA(
    DWORD       ExStyle,
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int64_t     X,
    int64_t     Y,
    uint32_t    Width,
    uint32_t    Height,
    HWND        ParrentHandle,
    HMENU       Menu,
    HINSTANCE   Instance,
    LPVOID      Parameter
){

    return (PWINDHANDLE)0x00;
}

USER32_API
HWND 
CreateWindowA(
    LPCSTR      ClassName,
    LPCSTR      WindowName,
    DWORD       Style,
    int64_t     X,
    int64_t     Y,
    uint32_t    Width,
    uint32_t    Height,
    HWND        ParrentHandle,
    HMENU       Menu,
    HINSTANCE   Instance,
    LPVOID      Parameter
){
    return CreateWindowExA(
        0,
        ClassName,
        WindowName,
        Style,
        X, Y,
        Width, Height,
        ParrentHandle,
        Menu,
        Instance,
        Parameter
    );
}
