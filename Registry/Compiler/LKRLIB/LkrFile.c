#include <Compiler.h>

PLKR_NODE_ENTRY LkrAllocateNode(
    LPWSTR NodeName,
    size_t AllocationSize
){
    size_t NameSize = Lou_wcslen(NodeName);
    PLKR_NODE_ENTRY NewNode = (PLKR_NODE_ENTRY)LouKeMalloc(sizeof(LKR_NODE_ENTRY) + AllocationSize + ((NameSize + 1) * sizeof(WCHAR)), 0);
    NewNode->NameSize = NameSize;
    NewNode->ItemSize = AllocationSize;
    ENCODE_ITEM_OFFSET(NewNode, sizeof(LKR_NODE_ENTRY) + ((NameSize + 1) * sizeof(WCHAR)));
    LPWSTR AllocatedName = (LPWSTR)((uint8_t*)NewNode + sizeof(LKR_NODE_ENTRY));
    Lou_wcscpy(AllocatedName, NodeName);
    uint8_t* Tmp = (uint8_t*)(AllocatedName + NameSize + 1);
    memset(Tmp, 0, AllocationSize);
    return NewNode;
}

size_t LkrGetNodeSize(PLKR_NODE_ENTRY Node){
    size_t Result = Node->NameSize * sizeof(WCHAR);
    Result += Node->ItemSize;
    return Result + sizeof(LKR_NODE_ENTRY);
}

size_t LkrGetNodeDataSize(PLKR_NODE_ENTRY Node){
    return Node->ItemSize;
}

size_t LkrGetNodeNameSize(PLKR_NODE_ENTRY Node){
    return Node->NameSize;
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
    uint8_t* To = (uint8_t*)Node + GET_ITEM_OFFSET(Node);
    memcpy(To, Buffer, BufferSize);
    return 0;
}

LPWSTR LkrGetNodeName(PLKR_NODE_ENTRY Node){
    return (LPWSTR)((uint8_t*)Node + sizeof(LKR_NODE_ENTRY));
}

PVOID LkrGetNodeData(
    PLKR_NODE_ENTRY Node
){
    return (PVOID)(uint8_t*)Node + GET_ITEM_OFFSET(Node);
}

PVOID LkrOpenNodeData(
    PLKR_NODE_ENTRY Node
){  
    PVOID Data = LkrGetNodeData(Node);
    size_t DataSize = LkrGetNodeDataSize(Node);
    PVOID Result = LouKeMalloc(DataSize, KERNEL_GENERIC_MEMORY);
    memcpy(Result, Data, DataSize);
    return Result;
}

void LkrCloseNodeData(
    PLKR_NODE_ENTRY Node,
    PVOID           Data
){
    size_t DataSize = LkrGetNodeDataSize(Node);
    LkrFillNodeData(Node, Data, DataSize);
    LouKeFree(Data);
}

PVOID 
LkrCreateStandardTypedefNode(
    LPWSTR  NewName,
    UINT8   Opcode
){
    PLKR_NODE_ENTRY NewNode = LkrAllocateNode(
        NewName,
        0
    );
    
    ENCODE_OP(NewNode, Opcode | DEFINITION);
    
    switch(Opcode){

        case BYTE_OPCODE:
            CreateSourceDeclarationLookup(
                NewName,
                Lou_wcslen(NewName),
                CompilerDeclarationLookup("BYTE"),
                strlen("BYTE")
            );
            break;

        case WORD_OPCODE:
            CreateSourceDeclarationLookup(
                NewName,
                Lou_wcslen(NewName),
                CompilerDeclarationLookup("WORD"),
                strlen("WORD")
            );
            break;

        case DWORD_OPCODE:
            CreateSourceDeclarationLookup(
                NewName,
                Lou_wcslen(NewName),
                CompilerDeclarationLookup("DWORD"),
                strlen("DWORD")
            );
            break;

        case QWORD_OPCODE:
            CreateSourceDeclarationLookup(
                NewName,
                Lou_wcslen(NewName),
                CompilerDeclarationLookup("DWORD"),
                strlen("DWORD")
            );
            break;

        case STRING_OPCODE:
            CreateSourceDeclarationLookup(
                NewName,
                Lou_wcslen(NewName),
                CompilerDeclarationLookup("STRING"),
                strlen("STRING")
            );
            break;

        default:
            return 0x00;
    }

    return (PVOID)NewNode;
}