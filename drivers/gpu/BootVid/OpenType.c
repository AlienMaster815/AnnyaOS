//Copyright GPL-2 Tyler Grenier (2026)
#include "BootVid.h"

UNUSED
static 
void
TtfPrintTtfObjectData(
    PTTF_OBJECT TtfObject
){
    LouPrint("BOOTVID.SYS:Printing Data For TTF Object:%h\n", TtfObject);
    LouPrint("ScalerType    :%h\n", TtfObject->OffsetSubTable.ScalerType);
    LouPrint("TableCount    :%h\n", TtfObject->OffsetSubTable.TableCount);
    LouPrint("SearchRange   :%h\n", TtfObject->OffsetSubTable.SearchRange);
    LouPrint("EntrySelector :%h\n", TtfObject->OffsetSubTable.EntrySelector);
    LouPrint("RangeShift    :%h\n", TtfObject->OffsetSubTable.RangeShift);

    SIZE TableCount = TtfObject->OffsetSubTable.TableCount;

    for(size_t i = 0 ; i < TableCount; i++){
        LouPrint("Tag           :%c%c%c%c\n", ((UINT8*)&TtfObject->TableDirectories[i].Tag)[3], ((UINT8*)&TtfObject->TableDirectories[i].Tag)[2], ((UINT8*)&TtfObject->TableDirectories[i].Tag)[1], ((UINT8*)&TtfObject->TableDirectories[i].Tag)[0]);
        LouPrint("Checkusm      :%h\n", TtfObject->TableDirectories[i].Checksum);
        LouPrint("Length        :%h\n", TtfObject->TableDirectories[i].Length);
        LouPrint("Offset        :%h\n", TtfObject->TableDirectories[i].Offset);
    }
} 

static 
LOUSTATUS
TtfCopyFileTableDirectoriesToObject(
    PTTF_OFFSET_SUBTABLE    FileOffsetSubTable,
    PTTF_OBJECT             TtfObject
){
    if((!FileOffsetSubTable) || (!TtfObject)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE TableCount = TtfObject->OffsetSubTable.TableCount;
    TtfObject->TableDirectories = LouKeMallocArray(TTFOBJ_TABLE_DIRECTORY, TableCount, KERNEL_GENERIC_MEMORY);

    PTTF_TABLE_DIRECTORY TmpTable = (PTTF_TABLE_DIRECTORY)((UINT8*)FileOffsetSubTable + sizeof(TTF_OFFSET_SUBTABLE));

    for(size_t i = 0 ; i < TableCount; i++){
        TtfObject->TableDirectories[i].Tag = TtfReadUint32(&TmpTable[i].Tag);
        TtfObject->TableDirectories[i].Checksum = TtfReadUint32(&TmpTable[i].Checksum);
        TtfObject->TableDirectories[i].Offset = TtfReadUint32(&TmpTable[i].Offset);
        TtfObject->TableDirectories[i].Length = TtfReadUint32(&TmpTable[i].Length);
    }

    return STATUS_SUCCESS;
}


static 
LOUSTATUS
TtfCopyFileToObject(
    PTTF_OFFSET_SUBTABLE    FileOffsetSubTable,
    PTTF_OBJECT             TtfObject
){
    LOUSTATUS Status;
    if((!FileOffsetSubTable) || (!TtfObject)){
        return STATUS_INVALID_PARAMETER;
    }

    TtfObject->OffsetSubTable.ScalerType = TtfReadUint32(&FileOffsetSubTable->ScalerType); 
    TtfObject->OffsetSubTable.TableCount = TtfReadUint16(&FileOffsetSubTable->TableCount);
    TtfObject->OffsetSubTable.SearchRange = TtfReadUint16(&FileOffsetSubTable->SearchRange);
    TtfObject->OffsetSubTable.EntrySelector = TtfReadUint16(&FileOffsetSubTable->EntrySelector);
    TtfObject->OffsetSubTable.RangeShift = TtfReadUint16(&FileOffsetSubTable);
    
    Status = TtfCopyFileTableDirectoriesToObject(FileOffsetSubTable, TtfObject);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    return STATUS_SUCCESS;
}

LOUSTATUS TtfCreateTtfObject(
    PVOID           FileIn,
    PTTF_OBJECT*    Out
){
    LOUSTATUS Status;

    if((!FileIn) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    
    PTTF_OFFSET_SUBTABLE FileOffsetSubTable = (PTTF_OFFSET_SUBTABLE)FileIn;
    PTTF_OBJECT NewTtfObject = LouKeMallocType(TTF_OBJECT, KERNEL_GENERIC_MEMORY);

    Status = TtfCopyFileToObject(
        FileIn,
        NewTtfObject
    );

    *Out = NewTtfObject;

    return STATUS_SUCCESS;
}

UINT8 TtfReadUint8(PVOID Data){
    return *(UINT8*)Data;
}

UINT16 TtfReadUint16(PVOID Data){
    UINT16 Tmp;
    LouKeSwapEndianess(Data, &Tmp, sizeof(UINT16));
    return Tmp;
}

UINT32 TtfReadUint32(PVOID Data){
    UINT32 Tmp;
    LouKeSwapEndianess(Data, &Tmp, sizeof(UINT32));
    return Tmp;   
}

UINT64 TtfReadUint64(PVOID Data){
    UINT64 Tmp;
    LouKeSwapEndianess(Data, &Tmp, sizeof(UINT64));
    return Tmp;
}

int TtfMemCmp(PVOID Data, PVOID Check, size_t Size){
    PVOID Tmp = LouKeMallocEx(Size, 1, KERNEL_GENERIC_MEMORY);
    memcpy(Tmp, Data, Size);
    int Result = memcmp(Tmp, Data, Size);
    LouKeFree(Tmp);
    return Result;
}

LOUSTATUS 
TtfInitializeFile(
    PVOID   TtfStream
){
    LouPrint("BOOTVID.SYS:TtfInitializeFile()\n");


    PTTF_OBJECT NewTtfObject;

    LOUSTATUS Status = TtfCreateTtfObject(TtfStream, &NewTtfObject);

    if(Status != STATUS_SUCCESS){
        LouPrint("BOOTVID.SYS:TtfInitializeFile():ERROR Unable To Create TTF Object\n");
        return Status;
    }   

    TtfPrintTtfObjectData(NewTtfObject);

    LouPrint("BOOTVID.SYS:TtfInitializeFile() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}
