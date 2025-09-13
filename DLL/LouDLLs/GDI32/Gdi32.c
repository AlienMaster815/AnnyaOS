#include "Gdi32.h"


GDI32_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}


GDI32_API
BOOL
Chord(
    HDC Hdc,
    int X1,
    int Y1,
    int X2,
    int Y2,
    int X3,
    int Y3,
    int X4,
    int Y4
){

    

    return false;
}



GDI32_API
BOOL 
CloseFigure(
    HDC Hdc
){



    return false;
}

GDI32_API
BOOL
DeleteObject(
    HGDIOBJ Object
){



    return false;
}

GDI32_API
BOOL
DPtoLP(
    HDC     Hdc,
    LPPOINT Point,
    int     c
){



    return false;
}

GDI32_API
int
DrawEscape(
    HDC     Hdc,
    int     Escape,
    int     CjIn,
    LPCSTR  LpIn
){



    return 0x00;
}


GDI32_API
BOOL
Ellipse(
    HDC     Hdc, 
    int     Left,
    int     Top,
    int     Right,
    int     Bottom
){

    

    return false;
}