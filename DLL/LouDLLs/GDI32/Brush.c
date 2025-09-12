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