#include <Compiler.h>

PLKR_NODE_ENTRY LkrAllocateNode(
    LPWSTR NodeName,
    size_t AllocationSize
){
    size_t NameSize = Lou_wcslen(NodeName);
    PLKR_NODE_ENTRY NewNode = (PLKR_NODE_ENTRY)LouKeMalloc(sizeof(LKR_NODE_ENTRY) + AllocationSize + (NameSize * sizeof(WCHAR)), 0);
    NewNode->NameSize = NameSize;
    NewNode->ItemSize = AllocationSize;
    ENCODE_ITEM_OFFSET(NewNode, (sizeof(LKR_NODE_ENTRY) + ((NameSize + 1) * sizeof(WCHAR))));
    LPWSTR AllocatedName = (LPWSTR)((uint8_t*)NewNode + sizeof(LKR_NODE_ENTRY));
    Lou_wcscpy(AllocatedName, NodeName);
    uint8_t* Tmp = (uint8_t*)(AllocatedName + NameSize); 
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
    uint8_t* To = (uint8_t*)Node + GET_ITEM_OFFSET(Node);
    memcpy(To, Buffer, BufferSize);
    return 0;
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