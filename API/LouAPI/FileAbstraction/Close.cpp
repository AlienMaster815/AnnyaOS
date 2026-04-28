#include <LouDDK.h>
#include "file.h"

LOUAPI void LouKeCloseFile(FILE* KFileHandle){
    PLOU_FILE_OBJECT FileObject = (PLOU_FILE_OBJECT)KFileHandle;
    PLOU_FILE_SEGMENT TmpSegment;
    PLOU_FILE_SEGMENT ForwardSegment;
    //TODO: Write FileData To Disk

    
    ForEachListEntrySafe(TmpSegment, ForwardSegment, &FileObject->Segments, Peers){
        LouKeFree(TmpSegment->Segment);
        LouKeFree(TmpSegment);
    }
    LouKeFree(FileObject);
}