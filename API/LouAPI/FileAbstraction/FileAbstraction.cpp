//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>
#include "file.h"


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
