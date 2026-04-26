//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>
#include "file.h"

static bool IsFileCoffFile(FILE File){
    PCOFF_IMAGE_HEADER  CoffStdHeader;
    if(memcmp((UINT8*)File, "MZ", 2)){
        return false;
    }
    CoffStdHeader = CoffGetImageHeader((UINT8*)File);
    if(
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))) &&
        (memcmp((PVOID)(UINT8*)&CoffStdHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, sizeof(UINT32)))
    ){
        return false;
    }
    return true;
}

LOUAPI FILE_TYPE LouKeGetFileType(FILE File){

    if(IsFileCoffFile(File)){
        return COFF_FILE_TYPE;
    }


    return UNKOWN_FILE_TYPE;
}

LOUAPI
SIZE 
LouKeZwGetFileSize(
    FILE* File
){
    return ((PLOU_FILE_OBJECT)File)->FileSize;
}

LOUAPI
UINT64 
LouKeZwGetFileClass(
    FILE* File
){
    return ((PLOU_FILE_OBJECT)File)->FileClass;
}

LOUAPI
LOUSTATUS
LouKeZwReadFileBuffer(
    FILE*   File,
    SIZE    Index,
    SIZE    Length,
    PVOID   Out
){
    if(!File){
        return STATUS_INVALID_PARAMETER;
    }
    PLOU_FILE_OBJECT FileObject = (PLOU_FILE_OBJECT)File;
    if(((Index + Length) > FileObject->FileSize) || (!Out)){
        return STATUS_INVALID_PARAMETER;
    }
    PLOU_FILE_SEGMENT Segment;
    SIZE OutContextIndex = 0;
    MutexLock(&FileObject->FileLock);
    ForEachListEntry(Segment, &FileObject->Segments, Peers){
        ForEachIf(RangeInterferes(Index, 1, Segment->SegmentBase, Segment->SegmentSize)){
            SIZE BufferByteInSegment = MIN(Length, (Segment->SegmentBase + Segment->SegmentSize) - Index);
            SIZE OffsetInSegment = Index - Segment->SegmentBase;
            for(SIZE i = 0 ; i < BufferByteInSegment; i++){
                ((UINT8*)Out)[OutContextIndex + i] = ((UINT8*)Segment->Segment)[OffsetInSegment + i]; 
            }
            OutContextIndex += BufferByteInSegment;
            Length -= BufferByteInSegment;
            Index += BufferByteInSegment;
            if(!Length){
                goto _DONE_READING_FILE;
            }
        }
    }
_DONE_READING_FILE:
    MutexUnlock(&FileObject->FileLock);
    return Length ? STATUS_UNSUCCESSFUL : STATUS_SUCCESS;
}
