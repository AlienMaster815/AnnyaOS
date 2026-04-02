#include "BootVid.h" 

static 
LOUSTATUS
TtfCmapParseUnicode(
    PVOID                   File, 
    PTTFOBJ_CMAP_SUBTABLE   CMapSubTable,    
    PTTF_OBJECT             TtfObject
){

    LouPrint("Unicode Version:%d\n", CMapSubTable->PlatformSpecID);
    
    UINT16* Format = (UINT16*)(UINT8*)((UINTPTR)File + (UINTPTR)CMapSubTable->Offset);

    LouPrint("Format:%d\n", TtfReadUint16(Format));

    return STATUS_SUCCESS;
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

    TtfObject->CmapMetaData.Index.Version = TtfReadUint16(&CMapTable->Version);
    SIZE SubTableCount = TtfReadUint16(&CMapTable->SubTableCount);

    TtfObject->CmapMetaData.Index.SubTableCount = SubTableCount;

    TtfObject->CmapMetaData.SubTables = LouKeMallocArray(TTFOBJ_CMAP_SUBTABLE, SubTableCount, KERNEL_GENERIC_MEMORY);


    for(SIZE i = 0 ; i < SubTableCount; i++){
        SIZE PlatformID = TtfReadUint16(&CMapSubTables[i].PlatformID);
        SIZE Offset = TtfReadUint32(&CMapSubTables[i].Offset);;
        TtfObject->CmapMetaData.SubTables[i].PlatformID = PlatformID;
        TtfObject->CmapMetaData.SubTables[i].PlatformSpecID = TtfReadUint16(&CMapSubTables[i].PlatformSpecID);
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

    while(1);
    return STATUS_SUCCESS;
}