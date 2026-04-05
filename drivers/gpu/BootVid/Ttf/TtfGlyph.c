//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"

LOUSTATUS 
TtfParseGlyphData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    LouPrint("TtfParseGlyphData()\n");
    
    PTTF_GLPYH_DESCRIPTION GlyphDescription = (PTTF_GLPYH_DESCRIPTION)(((UINTPTR)Directory->Offset + (UINTPTR)File) + (UINTPTR)TtfObject->AsciiGlyphOffsets['A']);

    LouPrint("CountourCount:%d\n", TtfReadUint16(GlyphDescription->ContourCount));
    LouPrint("XMin:%d\n", TtfReadUint16(GlyphDescription->XMin));
    LouPrint("YMin:%d\n", TtfReadUint16(GlyphDescription->YMin));
    LouPrint("XMax:%d\n", TtfReadUint16(GlyphDescription->XMax));
    LouPrint("YMax:%d\n", TtfReadUint16(GlyphDescription->YMax));

    while(1);
}