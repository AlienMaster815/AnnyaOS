#ifndef _LKR_LIB_H
#define _LKR_LIB_H

#include <stdint.h>

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
    LPWSTR              ItemName;
    size_t              ItemSize;
    uint8_t             ItemData[];
}LKR_NODE_ENTRY, * PLKR_NODE_ENTRY;

typedef struct _LKR_FILE_HEADER{
    LPWSTR              NodeID;
    LPWSTR              MountPoint;
    size_t              TotalSections;
    size_t              FirstEntry;
}LKR_FILE_HEADER, * PLKR_FILE_HEADER;

#include "LKRSRC.h"

#endif