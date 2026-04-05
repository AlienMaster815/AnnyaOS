#include "../BootVid.h"


UNUSED 
static 
LOUSTATUS 
TtfGetCmapFormat4GlyphIndex(
    PTTF_CMAP_FORMAT4 Format4, 
    SIZE Index, 
    UINT16* Out
) {
    if((!Out) || (!Format4)){
        return STATUS_INVALID_PARAMETER;
    }

    // 1. Get SegCount from the swapped SegCountX2
    UINT16 SegCount = TtfReadUint16(Format4->SegCountX2) / 2;
    UINT16 TargetSeg = 0xFFFF;

    // 2. Find the segment that contains our character Index
    for(UINT16 i = 0; i < SegCount; i++) {
        // Use the PTR macro and read the value through the swap function
        if (TtfReadUint16(*TTF_CMAP_FORMAT4_END_CODE_PTR(Format4, i)) >= (UINT16)Index) {
            TargetSeg = i;
            break;
        }
    }

    // Index is out of range for this table
    if(TargetSeg == 0xFFFF){
        return STATUS_UNSUCCESSFUL;
    } 

    // 3. Verify Index is not before the StartCode of this segment
    UINT16 StartCode = TtfReadUint16(*TTF_CMAP_FORMAT4_START_CODE_PTR(Format4, TargetSeg));
    if(Index < StartCode){
        return STATUS_UNSUCCESSFUL;
    }

    // 4. Get the mapping values (must swap!)
    UINT16 RangeOffset = TtfReadUint16(*TTF_CMAP_FORMAT4_ID_RANGE_OFFSET_PTR(Format4, TargetSeg));
    UINT16 IdDelta     = TtfReadUint16(*TTF_CMAP_FORMAT4_ID_DELTA_PTR(Format4, TargetSeg));

    if(RangeOffset == 0) {
        // Type 1: Simple idDelta math
        *Out = (UINT16)(Index + IdDelta);
        return STATUS_SUCCESS;
    } else {
        // Type 2: idRangeOffset math
        // idRangeOffset is a byte offset from the location of the idRangeOffset element itself
        UINT16* RangeOffsetAddr = TTF_CMAP_FORMAT4_ID_RANGE_OFFSET_PTR(Format4, TargetSeg);

        // Pointer arithmetic on UINT16* moves by 2 bytes per unit.
        // Formula: addr + (offset / 2) + (Index - StartCode)
        UINT16* GlyphPtr = RangeOffsetAddr + (RangeOffset / 2) + (Index - StartCode);
        
        // The value in the glyph array is also Big-Endian
        UINT16 GlyphIndex = TtfReadUint16(*GlyphPtr);

        if (GlyphIndex != 0) {
            // Apply IdDelta to the value found in the array
            *Out = (UINT16)(GlyphIndex + IdDelta); 
            return STATUS_SUCCESS;
        }
    }
    
    // Character maps to glyph 0 (notdef), which is usually considered unsuccessful here
    return STATUS_UNSUCCESSFUL;
}


static 
LOUSTATUS
TtfCmapParseUnicode(
    PVOID                   File, 
    PTTFOBJ_CMAP_SUBTABLE   CMapSubTable,    
    PTTF_OBJECT             TtfObject
){
    LOUSTATUS Status;
    LouPrint("Unicode Version:%d\n", CMapSubTable->PlatformSpecID);
    
    UINT16* Format = (UINT16*)(UINT8*)((UINTPTR)File + (UINTPTR)CMapSubTable->Offset);
    UINT16 FormatID = TtfReadUint16(*Format);

    LouPrint("Format:%d\n", FormatID);

    if(FormatID == 4){

        for(SIZE i = 0 ; i < 127; i++){

            Status = TtfGetCmapFormat4GlyphIndex(
                (PTTF_CMAP_FORMAT4)(UINT8*)Format,
                i,
                &TtfObject->CmapMetaData.AsciiSpace[i]
            );
            if(Status != STATUS_SUCCESS){
                //LouPrint("Ascii UTF8 Code:%d Not Mapped\n", i);
                TtfObject->CmapMetaData.AsciiSpace[i] = 0xFFFF;
            }
        }

        for(SIZE i = 0 ; i < 256; i++){
            Status = TtfGetCmapFormat4GlyphIndex(
                (PTTF_CMAP_FORMAT4)(UINT8*)Format,
                i + 0x0400,
                &TtfObject->CmapMetaData.RussianSpace[i]
            );
            if(Status != STATUS_SUCCESS){
                //LouPrint("Russian UTF16 Code:%d Not Mapped\n", i + 0x0400);
                TtfObject->CmapMetaData.RussianSpace[i] = 0xFFFF;
            }
        }

        return STATUS_SUCCESS;
    }

    return STATUS_INVALID_PARAMETER;
}

static 
LOUSTATUS
TtfCmapParseMacintosh(
    PVOID                   File, 
    PTTFOBJ_CMAP_SUBTABLE   CMapSubTable,    
    PTTF_OBJECT             TtfObject
){
    LouPrint("Macintosh Version:%d\n", CMapSubTable->PlatformSpecID);
    

    return STATUS_SUCCESS;
}

static 
LOUSTATUS
TtfCmapParseMicrosoft(
    PVOID                   File, 
    PTTFOBJ_CMAP_SUBTABLE   CMapSubTable,    
    PTTF_OBJECT             TtfObject
){
    LouPrint("Microsoft Version:%d\n", CMapSubTable->PlatformSpecID);

    

    return STATUS_SUCCESS;
}

LOUSTATUS 
TtfParseCmapData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
){
    PTTF_CMAP_INDEX     CMapTable = (PTTF_CMAP_INDEX)(File + (UINTPTR)Directory->Offset);
    PTTF_CMAP_SUBTABLE  CMapSubTables = (File + (UINTPTR)Directory->Offset + sizeof(TTF_CMAP_INDEX));
    LOUSTATUS Status;

    TtfObject->CmapMetaData.Index.Version = TtfReadUint16(CMapTable->Version);
    SIZE SubTableCount = TtfReadUint16(CMapTable->SubTableCount);

    TtfObject->CmapMetaData.Index.SubTableCount = SubTableCount;

    TtfObject->CmapMetaData.SubTables = LouKeMallocArray(TTFOBJ_CMAP_SUBTABLE, SubTableCount, KERNEL_GENERIC_MEMORY);


    for(SIZE i = 0 ; i < SubTableCount; i++){
        SIZE PlatformID = TtfReadUint16(CMapSubTables[i].PlatformID);
        SIZE Offset = TtfReadUint32(CMapSubTables[i].Offset);
        TtfObject->CmapMetaData.SubTables[i].PlatformID = PlatformID;
        TtfObject->CmapMetaData.SubTables[i].PlatformSpecID = TtfReadUint16(CMapSubTables[i].PlatformSpecID);
        TtfObject->CmapMetaData.SubTables[i].Offset = Offset;
        switch(PlatformID){
            case 0:
                Status = TtfCmapParseUnicode(
                    (PVOID)((UINTPTR)(UINT8*)CMapTable),
                    &TtfObject->CmapMetaData.SubTables[i],
                    TtfObject
                );
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                continue;
            case 1:
                Status = TtfCmapParseMacintosh(
                    (PVOID)((UINTPTR)(UINT8*)CMapTable),
                    &TtfObject->CmapMetaData.SubTables[i],
                    TtfObject
                );
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                continue;
            case 3:
                Status = TtfCmapParseMicrosoft(
                    (PVOID)((UINTPTR)(UINT8*)CMapTable),
                    &TtfObject->CmapMetaData.SubTables[i],
                    TtfObject
                );
                if(Status != STATUS_SUCCESS){
                    return Status;
                }
                continue;
            default: 
                continue;
        }
    }

    return STATUS_SUCCESS;
}