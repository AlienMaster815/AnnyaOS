#include <LouDDK.h>
#include "file.h"

FILE* LouKeZwOpenFile(
    LOUSTR  FilePath,
    UINT64  OpenFlags
){
    UINT64 PageFlags = 0;
    UINT64 FileClass = 0;
    LOUSTR Extention = StrFingFirstFromEnd(FilePath, ".");
    if(!Extention){
        LouPrint("LouKeZwOpenFile():Warning Path Parameter Withought Extention\n");
    }else{
        FileClass = LouKeOpenFileGetFileClass(Extention);
    }


    switch(OpenFlags & FOPEN_MEMORY_FLAGS_MASK){
        case FOPEN_USER_GENERIC_MEMORY:
            PageFlags = USER_GENERIC_MEMORY;
            break;
        case FOPEN_USER_DMA_MEMORY:
            PageFlags = USER_DMA_MEMORY;
            break;
        case FOPEN_KERNEL_DMA_MEMORY:
            PageFlags = KERNEL_DMA_MEMORY;
            break;
        case FOPEN_KERNEL_GENERIC_MEMORY:
        default:
            PageFlags = KERNEL_GENERIC_MEMORY;
            break;
    }

    PVOID   FileData = fopen(FilePath, PageFlags);
    SIZE    FileSize = 0x00;
    SIZE    FileIndex = FileSize;
    BOOLEAN NewFile = false;
    if(!FileData && (OpenFlags & FOPEN_CREATE_ON_FDNE)){
        LouPrint("WARNING: File Not Found Creating File\n");
        FileData = LouKeMallocEx(KILOBYTE_PAGE, KILOBYTE_PAGE, PageFlags);
        FileSize = KILOBYTE_PAGE;
        FileIndex = 0;
        NewFile = true;
    }else if(!FileData){
        LouPrint("ERROR: Exspected File Not Found\n");
        return 0x00;
    }else {
        FileSize = fsize(FileData);
        if(!FileSize){
            LouPrint("WARNING: File Size Is Null\n");
        }
    }

    PLOU_FILE_OBJECT FileObject = LouKeMallocType(LOU_FILE_OBJECT, KERNEL_GENERIC_MEMORY);

    FileObject->FileIndex = FileIndex;
    FileObject->FileSize  = FileSize;
    FileObject->FileClass = FileClass;
    FileObject->OpenFlags = OpenFlags;

    PLOU_FILE_SEGMENT NewSegment = LouKeMallocType(LOU_FILE_SEGMENT, KERNEL_GENERIC_MEMORY);

    NewSegment->SegmentSize = FileSize;
    NewSegment->SegmentLbu  = FileIndex;
    NewSegment->SegmentBase = 0;

    if(!NewFile){
        NewSegment->Segment = LouKeMallocEx(FileSize, KILOBYTE_PAGE, PageFlags);
        memcpy(NewSegment->Segment, FileData, FileSize);
        fclose(FileData);
    }
    LouKeListAddTail(&NewSegment->Peers, &FileObject->Segments);
    return (FILE*)FileObject;
}

