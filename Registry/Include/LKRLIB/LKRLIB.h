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
    size_t              NameSize;
    size_t              OpItemOffset;
    size_t              ItemSize;
}LKR_NODE_ENTRY, * PLKR_NODE_ENTRY;

typedef struct _COMPILED_NODE_ENTRY{
    LOUSINE_NODE_LIST       NodePeers;
    LKR_NODE_ENTRY          Node;
}COMPILED_NODE_ENTRY, * PCOMPILED_NODE_ENTRY;

#define BYTE_OPCODE             (0b00001)
#define WORD_OPCODE             (0b00010)
#define DWORD_OPCODE            (0b00011)
#define QWORD_OPCODE            (0b00100)
#define STRING_OPCODE           (0b00101)
#define STRUCT_OPCODE           (0b00110)
#define DEFINITION              (0b01000)
#define ARRAY_DATA              (0b10000)

#define OPCODE_FLAG_MASKS       (0b11000)

#define OPCODE_MASK             (0x1FULL)
#define OFFSET_MASK             (0xFFFFFFFFFFFFFFE0ULL)

#define ENCODE_OP(Node, Op)                 (((PLKR_NODE_ENTRY)Node)->OpItemOffset = (((PLKR_NODE_ENTRY)Node)->OpItemOffset & OFFSET_MASK) | (uint8_t)(Op))
#define ENCODE_ITEM_OFFSET(Node, Offset)    (((PLKR_NODE_ENTRY)Node)->OpItemOffset = (((PLKR_NODE_ENTRY)Node)->OpItemOffset & OPCODE_MASK) |  (uint64_t)(Offset) << 5) 
#define GET_ITEM_OPCODE(Node)               (((PLKR_NODE_ENTRY)Node)->OpItemOffset & OPCODE_MASK)
#define GET_ITEM_OFFSET(Node)               ((((PLKR_NODE_ENTRY)Node)->OpItemOffset & OFFSET_MASK) >> 5) 

typedef struct _LKR_FILE_HEADER{
    WCHAR               Signature[20];//LOUSINE_SYSTEM_FILE
    size_t              FirstEntry;
    size_t              SectionCount;
}LKR_FILE_HEADER, * PLKR_FILE_HEADER;


PLKR_NODE_ENTRY LkrAllocateNode(
    LPWSTR NodeName,
    size_t AllocationSize
);

#include "StructureTypes.h"

#endif