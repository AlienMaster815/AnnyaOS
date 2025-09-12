#include "Gdi32.h"

GDI32_API 
bool
AlphaBlend(
    HDC             HdcDestination,
    int             XOriginDest,
    int             YOriginDest,
    int             WidthDest,
    int             HeightDest,
    HDC             HdcSource,
    int             XOriginSource,
    int             YOriginSource,
    int             WidthSource,
    int             HeightSource,
    BLEND_FUNCTION  BlendFunction;
){


    return false;
}

GDI32_API
BOOL
BitBlt(
    HDC     Hdc,
    int     X,
    int     Y,
    int     Cx,
    int     Cy,
    HDC     HdcSource,
    int     X1,
    int     X2,
    DWORD   RenderOperation
){


    return false;
}

GDI32_API
HBITMAP
CreateBitmap(
    int     Width,
    int     Height,
    UINT32  Planes,
    UINT32  BitsCount,
    PVOID   Data
){



    return 0x00;
}

GDI32_API
HBITMAP
CreateBitmapIndirect(
    PBITMAP Bitmap
){



    return 0x00;
}

GDI32_API
HBITMAP
CreateCompatibleBitmap(
    HDC Hdc,
    int Cx,
    int Cy
){

    

    return 0x00;
}