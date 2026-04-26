#ifndef _FILE_ABSTRACTION_INTERNAL_H
#define _FILE_ABSTRACTION_INTERNAL_H


typedef struct _LOU_FILE_SEGMENT{
    ListHeader  Peers;
    SIZE        SegmentBase;
    SIZE        SegmentSize;
    SIZE        SegmentLbu;
    PVOID       Segment;
}LOU_FILE_SEGMENT, * PLOU_FILE_SEGMENT;

typedef struct _LOU_FILE_OBJECT{
    UINT64      FileClass;
    UINT64      OpenFlags;
    SIZE        FileIndex;
    SIZE        FileSize;
    mutex_t     FileLock;
    ListHeader  Segments;
}LOU_FILE_OBJECT, * PLOU_FILE_OBJECT;

UINT64 LouKeOpenFileGetFileClass(LOUSTR Extention);

#endif