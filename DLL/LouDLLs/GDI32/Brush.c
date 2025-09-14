#include "Gdi32.h"

GDI32_API
HBRUSH 
CreateBrushIndirect(
    PLOGBRUSH BrushTemplate
){
    HBRUSH NewBrush = LouGlobalUserMallocType(BRUSH);
    LouMemCpy(&NewBrush->LogBrush, BrushTemplate, sizeof(BRUSH));
    return NewBrush;
}

GDI32_API
HBRUSH
CreateHatchBrush(
    int         Hatch,
    COLORREF    Color
){



    return 0x00;
}


GDI32_API
HBRUSH
CreatePatternBrush(
    HBITMAP     BitmapHandle
){



    return 0x00;
}


GDI32_API
HBRUSH
CreateSolidBrush(
    COLORREF    Color
){



    return 0x00;
}

