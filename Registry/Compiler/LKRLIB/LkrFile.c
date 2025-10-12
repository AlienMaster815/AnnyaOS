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
    size_t Result = (Node->NameSize + 1) * sizeof(WCHAR);
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



size_t LkrGetFileTotalSize(
    PLOUSINE_NODE Node
){
    PLOUSINE_NODE TmpNode = Node; 
    size_t Result = 0;

    while(TmpNode->NodePeers.Forward){
        TmpNode = (PLOUSINE_NODE)TmpNode->NodePeers.Forward;
        if(TmpNode->NodeData){
            Result += ROUND_UP64(sizeof(COMPILED_NODE_ENTRY) + LkrGetNodeSize(TmpNode->NodeData), 8);
        }
        else if(TmpNode->DirectoryName){
            Result += ROUND_UP64(sizeof(COMPILED_NODE_ENTRY), 8);
            Result += ROUND_UP64((Lou_wcslen(TmpNode->DirectoryName) + 1) * sizeof(WCHAR), 8);

        }


        if(TmpNode->NodePeers.Downward){
            Result += LkrGetFileTotalSize(
                (PLOUSINE_NODE)TmpNode->NodePeers.Downward
            );
        }
    }
    return Result;
}


static size_t CalculateFileSize(
    UNUSED PCOMPILER_CONTEXT Context
){
    size_t FileSize = LkrGetFileTotalSize(
        Context->CompilerNode
    );

    if(FileSize == ROUND_UP64(FileSize, 4096)){
        FileSize += 2048;
    }


    FileSize = ROUND_UP64(FileSize, 4096);

    return 4096;
}

errno_t LkrCreateFile(
    UNUSED PLOUSINE_NODE            CurrentNode,
    UNUSED PCOMPILED_NODE_ENTRY     FileListHeader,
    UNUSED PVOID*                   CurrentContext
){
    errno_t Result = 0;

    size_t NodeSize = 0;
    bool Pass1 = true;
    while(CurrentNode->NodePeers.Forward){
        CurrentNode = (PLOUSINE_NODE)CurrentNode->NodePeers.Forward;
        PCOMPILED_NODE_ENTRY NewEntry = (PCOMPILED_NODE_ENTRY)*CurrentContext; 
        if(CurrentNode->NodeData){
            NodeSize = ROUND_UP64(sizeof(COMPILED_NODE_ENTRY) + LkrGetNodeSize(CurrentNode->NodeData), 8);
            memcpy(&NewEntry->Node, CurrentNode->NodeData, LkrGetNodeSize(CurrentNode->NodeData));
            if(Pass1 && FileListHeader){
                NewEntry->NodePeers.Upward = (PLOUSINE_NODE_LIST)FileListHeader->NodePeers.Downward;
            }else if(FileListHeader){
                NewEntry->NodePeers.Aftward = (PLOUSINE_NODE_LIST)FileListHeader->NodePeers.Forward;
            }            
            Pass1 = false;
            FileListHeader = *CurrentContext;
            *CurrentContext += NodeSize;
        }
        else if(CurrentNode->DirectoryName){
            NodeSize = ROUND_UP64(sizeof(COMPILED_NODE_ENTRY), 8);
            NodeSize += ROUND_UP64((Lou_wcslen(CurrentNode->DirectoryName) + 1) * sizeof(WCHAR), 8);
            NewEntry->Node.NameSize = Lou_wcslen(CurrentNode->DirectoryName);
            Lou_wcscpy((PVOID)NewEntry + sizeof(COMPILED_NODE_ENTRY), CurrentNode->DirectoryName);
            if(Pass1 && FileListHeader){
                NewEntry->NodePeers.Upward = (PLOUSINE_NODE_LIST)FileListHeader->NodePeers.Downward;
            }else if(FileListHeader){
                NewEntry->NodePeers.Aftward = (PLOUSINE_NODE_LIST)FileListHeader->NodePeers.Forward;
            }
            Pass1 = false;
            FileListHeader = *CurrentContext;
            *CurrentContext += NodeSize;
        }


        //printf("Current Context:%zu\n", (size_t)*CurrentContext);
        //printf("Last    Context:%zu\n", (size_t)FileListHeader);

        if(CurrentNode->NodePeers.Downward){
            NewEntry->NodePeers.Downward = (PLOUSINE_NODE_LIST)((PVOID)*CurrentContext - (PVOID)NewEntry);
            LkrCreateFile(
                (PLOUSINE_NODE)CurrentNode->NodePeers.Downward,
                FileListHeader,
                CurrentContext
            );
        }else{
            NewEntry->NodePeers.Forward = (PLOUSINE_NODE_LIST)((PVOID)*CurrentContext - (PVOID)NewEntry);
        }
    }
    return Result;
}

errno_t 
LkrCreateLkrFileContext(
    UNUSED LOU_STRING          Output,
    UNUSED PCOMPILER_CONTEXT   Context
){

    if (!Output || !Context){
        return EINVAL;
    }

    Context->OutSize = CalculateFileSize(Context);
    PVOID FileBuffer = LouKeMalloc(Context->OutSize, KERNEL_GENERIC_MEMORY);
    if(!FileBuffer){
        return ENOMEM;
    }

    FILE* File = fopen(Output, "wb");
    if (!File) {
        LouKeFree(FileBuffer);
        return errno; // errno is automatically set by fopen()
    }

    PLKR_FILE_HEADER FileHeader = (PLKR_FILE_HEADER)FileBuffer;

    Lou_wcscpy(&FileHeader->Signature[0], CompilerDeclarationLookup("LOUSINE_SYSTEM_FILE"));
    FileHeader->SectionCount = Context->OutSize / 4096;
    Context->OutContext = (FileBuffer + ROUND_UP64(sizeof(LKR_FILE_HEADER), 8));
    FileHeader->FirstEntry = (size_t)ROUND_UP64(sizeof(LKR_FILE_HEADER), 8);

    LkrCreateFile((PLOUSINE_NODE)Context->CompilerNode, 0x00, &Context->OutContext);

    size_t written = fwrite(FileBuffer, 1, Context->OutSize, File);
    if (written != Context->OutSize) {
        fclose(File);
        LouKeFree(FileBuffer);
        return EIO;
    }

    fclose(File);
    LouKeFree(FileBuffer);
    return 0;
}