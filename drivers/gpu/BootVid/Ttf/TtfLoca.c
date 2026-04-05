//Copyright GPL-2 Tyler Grenier (2026)
#include "../BootVid.h"


LOUSTATUS 
TtfParseLocaData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    SIZE LocaTableIndex;
    if(TtfObject->UsesLongLocaTableFormat){
        PTTF_LOCA_LONG TmpOffset = (PTTF_LOCA_LONG)((UINTPTR)File + Directory->Offset);
        for(size_t i = 0; i < 127; i++){
            LocaTableIndex = TtfObject->CmapMetaData.AsciiSpace[i];
            if(LocaTableIndex != 0xFFFF){
                TtfObject->AsciiGlyphOffsets[i] = (UINT32)TtfReadUint32(TmpOffset[LocaTableIndex]);
            }
        }
        for(size_t i = 0 ; i < 256; i++){
            LocaTableIndex = TtfObject->CmapMetaData.RussianSpace[i];
            if(LocaTableIndex != 0xFFFF){
                TtfObject->RussianGlyphOffsets[i] = (UINT32)TtfReadUint32(TmpOffset[LocaTableIndex]);
            }
        }
    }else{
        PTTF_LOCA_SHORT TmpOffset = (PTTF_LOCA_SHORT)((UINTPTR)File + Directory->Offset);
        for(size_t i = 0; i < 127; i++){
            LocaTableIndex = TtfObject->CmapMetaData.AsciiSpace[i];
            if(LocaTableIndex != 0xFFFF){
                TtfObject->AsciiGlyphOffsets[i] = (UINT32)TtfReadUint16(TmpOffset[LocaTableIndex]) * 2;
            }
        }
        for(size_t i = 0 ; i < 256; i++){
            LocaTableIndex = TtfObject->CmapMetaData.RussianSpace[i];
            if(LocaTableIndex != 0xFFFF){
                TtfObject->RussianGlyphOffsets[i] = (UINT32)TtfReadUint16(TmpOffset[LocaTableIndex]) * 2;
            }
        }
    }

    return STATUS_SUCCESS;
}