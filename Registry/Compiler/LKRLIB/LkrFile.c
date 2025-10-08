#include <Compiler.h>

PLKR_NODE_ENTRY LkrAllocateNode(
    LPWSTR NodeName,
    size_t AllocationSize
){
    size_t NameSize = Lou_wcslen(NodeName) + 1;
    PLKR_NODE_ENTRY NewNode = (PLKR_NODE_ENTRY)LouKeMalloc(sizeof(LKR_NODE_ENTRY) + AllocationSize + (NameSize * sizeof(WCHAR)), 0);

    NewNode->NameSize = NameSize;
    NewNode->ItemSize = AllocationSize;
 
    LPWSTR AllocatedName = (LPWSTR)((uint8_t*)NewNode + sizeof(LKR_NODE_ENTRY));
    
    Lou_wcscpy(AllocatedName, NodeName);
    AllocatedName += NameSize;

    uint8_t* Tmp = (uint8_t*)AllocatedName; 
    memset(Tmp, 0, AllocationSize);
    return NewNode;
}


errno_t
LkrFillNodeData(
    PLKR_NODE_ENTRY Node,
    uint8_t*        Buffer,
    size_t          BufferSize
){
    if((Node->ItemSize < BufferSize) || (!Buffer) || (!BufferSize)){
        return EINVAL;
    }
    uint8_t* To = ((uint8_t*)Node + (sizeof(LKR_NODE_ENTRY) + (Node->NameSize * sizeof(WCHAR))));
    memcpy(To, Buffer, BufferSize);
    return 0;
}