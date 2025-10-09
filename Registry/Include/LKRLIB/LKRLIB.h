#ifndef _LKR_LIB_H
#define _LKR_LIB_H


#define LPWSTR uint16_t*
#define WCHAR uint16_t


typedef struct _LOUSINE_NODE_LIST{
    struct _LOUSINE_NODE_LIST*   Forward;
    struct _LOUSINE_NODE_LIST*   Aftward;
    struct _LOUSINE_NODE_LIST*   Downward;
    struct _LOUSINE_NODE_LIST*   Upward;
}LOUSINE_NODE_LIST, * PLOUSINE_NODE_LIST;


typedef struct _LOUSINE_NODE{
    LOUSINE_NODE_LIST       NodePeers;
    LPWSTR                  NodeID;
    LPWSTR                  DirectoryName;
    void*                   NodeData;
}LOUSINE_NODE, * PLOUSINE_NODE;

typedef struct _LKR_NODE_ENTRY{
    LOUSINE_NODE_LIST   NodePeers;
    size_t              NameSize;
    size_t              OpItemOffset;
    size_t              ItemSize;
}LKR_NODE_ENTRY, * PLKR_NODE_ENTRY;

#define BYTE_OPCODE             1
#define WORD_OPCODE             2
#define DWORD_OPCODE            3
#define QWORD_OPCODE            4
#define STRING_OPCODE           5
#define STRUCT_OPCODE           6
#define DEFINITION              (1 << 4)

#define ENCODE_OP(Node, Op)                 (((PLKR_NODE_ENTRY)Node)->OpItemOffset = (((PLKR_NODE_ENTRY)Node)->OpItemOffset & 0xFFFFFFFFFFFFFFF0ULL) | (Op))
#define ENCODE_ITEM_OFFSET(Node, Offset)    (((PLKR_NODE_ENTRY)Node)->OpItemOffset = (((PLKR_NODE_ENTRY)Node)->OpItemOffset & 0x0FULL) |  (Offset) << 4) 
#define GET_ITEM_OPCODE(Node)               (((PLKR_NODE_ENTRY)Node)->OpItemOffset & 0x0FULL) 
#define GET_ITEM_OFFSET(Node)               ((((PLKR_NODE_ENTRY)Node)->OpItemOffset & 0xFFFFFFFFFFFFFFF0ULL) >> 4) 

typedef struct _LKR_FILE_HEADER{
    LPWSTR              NodeID;
    LPWSTR              MountPoint;
    size_t              TotalSections;
    size_t              FirstEntry;
}LKR_FILE_HEADER, * PLKR_FILE_HEADER;

#include "LKRSRC.h"

PLKR_NODE_ENTRY LkrAllocateNode(
    LPWSTR NodeName,
    size_t AllocationSize
);


#endif