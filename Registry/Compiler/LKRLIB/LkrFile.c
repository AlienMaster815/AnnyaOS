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
        FileSize += 1;
    }


    FileSize = ROUND_UP64(FileSize, 4096);

    return FileSize;
}

size_t RecursiveCompileNodes(
    UNUSED PLOUSINE_NODE           UpNode,
    UNUSED POOL                    FilePool
){
    UNUSED PCOMPILED_NODE_ENTRY LastEntry = 0x00;
    UNUSED PCOMPILED_NODE_ENTRY CurrentEntry = 0x00;
    UNUSED size_t CurrentOffset = 0x00;
    UNUSED size_t LastOffset = 0x00;
    UNUSED size_t Result = 0x00; 
    while(UpNode){

        if(UpNode->NodeData){
            PLKR_NODE_ENTRY TmpEntry = (PLKR_NODE_ENTRY)UpNode->NodeData;
            CurrentEntry = (PCOMPILED_NODE_ENTRY)LouKeGenricAllocateDmaPool(FilePool, sizeof(COMPILED_NODE_ENTRY) + ((TmpEntry->NameSize + 1) * sizeof(WCHAR)) + TmpEntry->ItemSize, &CurrentOffset);
            memcpy(&CurrentEntry->Node, TmpEntry, sizeof(LKR_NODE_ENTRY));
            Lou_wcscpy((LPWSTR)(uint8_t*)((size_t)CurrentEntry + sizeof(COMPILED_NODE_ENTRY)), (LPWSTR)(uint8_t*)((size_t)TmpEntry + sizeof(LKR_NODE_ENTRY)));
            memcpy((uint8_t*)((size_t)&CurrentEntry->Node + GET_ITEM_OFFSET(TmpEntry)), (uint8_t*)TmpEntry + GET_ITEM_OFFSET(TmpEntry), TmpEntry->ItemSize);

            if(LastEntry){
                LastEntry->NodePeers.Forward = (PLOUSINE_NODE_LIST)CurrentOffset;
                CurrentEntry->NodePeers.Aftward = (PLOUSINE_NODE_LIST)LastOffset;
            }
            
        }
        else if(UpNode->DirectoryName){
            CurrentEntry = (PCOMPILED_NODE_ENTRY)LouKeGenricAllocateDmaPool(FilePool, sizeof(COMPILED_NODE_ENTRY) + ((Lou_wcslen(UpNode->DirectoryName) + 1) * sizeof(WCHAR)), &CurrentOffset);
            if(LastEntry){
                LastEntry->NodePeers.Forward = (PLOUSINE_NODE_LIST)CurrentOffset;
                CurrentEntry->NodePeers.Aftward = (PLOUSINE_NODE_LIST)LastOffset;
            }
            CurrentEntry->Node.NameSize = Lou_wcslen(UpNode->DirectoryName);
            Lou_wcscpy((LPWSTR)(uint8_t*)((size_t)CurrentEntry + sizeof(COMPILED_NODE_ENTRY)), UpNode->DirectoryName);
            if(UpNode->NodePeers.Downward){
                CurrentEntry->NodePeers.Downward = (PLOUSINE_NODE_LIST)RecursiveCompileNodes((PLOUSINE_NODE)UpNode->NodePeers.Downward, FilePool);
            }
        }

        if(!Result){
            Result = CurrentOffset;
        }
        LastOffset = CurrentOffset;
        LastEntry = CurrentEntry;
        UpNode = (PLOUSINE_NODE)UpNode->NodePeers.Forward;
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


    UNUSED POOL FilePool = LouKeCreateGenericPool((uint64_t)FileBuffer, 0, Context->OutSize, 0);
    PLKR_FILE_HEADER FileHeader = (PLKR_FILE_HEADER)LouKeGenricAllocateDmaPool(FilePool, sizeof(LKR_FILE_HEADER), 0);

    Lou_wcscpy(&FileHeader->Signature[0], CompilerDeclarationLookup("LOUSINE_SYSTEM_FILE"));
    FileHeader->SectionCount = Context->OutSize / 4096;
    PLOUSINE_NODE RootNodes = (PLOUSINE_NODE)Context->CompilerNode->NodePeers.Forward;
    UNUSED PCOMPILED_NODE_ENTRY CurrentRootCompilerHandle = 0x00;
    UNUSED PCOMPILED_NODE_ENTRY LastEntry = 0x00;
    size_t CurrentOffset = 0;
    size_t LastOffset = 0;

    while(RootNodes){
        if(RootNodes->NodeData){
            PLKR_NODE_ENTRY TmpEntry = (PLKR_NODE_ENTRY)RootNodes->NodeData;
            CurrentRootCompilerHandle = (PCOMPILED_NODE_ENTRY)LouKeGenricAllocateDmaPool(FilePool, sizeof(COMPILED_NODE_ENTRY) + ((TmpEntry->NameSize + 1) * sizeof(WCHAR)) + TmpEntry->ItemSize, &CurrentOffset);
            memcpy(&CurrentRootCompilerHandle->Node, TmpEntry, sizeof(LKR_NODE_ENTRY));
            Lou_wcscpy((LPWSTR)(uint8_t*)((size_t)CurrentRootCompilerHandle + sizeof(COMPILED_NODE_ENTRY)), (LPWSTR)(uint8_t*)((size_t)TmpEntry + sizeof(LKR_NODE_ENTRY)));
            memcpy((uint8_t*)((size_t)&CurrentRootCompilerHandle->Node + GET_ITEM_OFFSET(TmpEntry)), (uint8_t*)TmpEntry + GET_ITEM_OFFSET(TmpEntry), TmpEntry->ItemSize);

            if(LastEntry){
                LastEntry->NodePeers.Forward = (PLOUSINE_NODE_LIST)CurrentOffset;
                CurrentRootCompilerHandle->NodePeers.Aftward = (PLOUSINE_NODE_LIST)LastOffset;
            }
        }else{
            CurrentRootCompilerHandle = LouKeGenricAllocateDmaPool(FilePool, sizeof(COMPILED_NODE_ENTRY) + ((Lou_wcslen(RootNodes->DirectoryName) + 1) * sizeof(WCHAR)), &CurrentOffset);
            Lou_wcscpy((LPWSTR)(uint8_t*)((size_t)CurrentRootCompilerHandle + sizeof(COMPILED_NODE_ENTRY)), RootNodes->DirectoryName);
            CurrentRootCompilerHandle->Node.NameSize = Lou_wcslen(RootNodes->DirectoryName);
            if(LastEntry){
                LastEntry->NodePeers.Forward = (PLOUSINE_NODE_LIST)CurrentOffset;
                CurrentRootCompilerHandle->NodePeers.Aftward = (PLOUSINE_NODE_LIST)LastOffset;
            }
            if(RootNodes->NodePeers.Downward){
                CurrentRootCompilerHandle->NodePeers.Downward = (PLOUSINE_NODE_LIST)RecursiveCompileNodes((PLOUSINE_NODE)RootNodes->NodePeers.Downward, FilePool);
            }
        }
    
        if(!FileHeader->FirstEntry){
            FileHeader->FirstEntry = CurrentOffset;
            CurrentRootCompilerHandle->NodePeers.Aftward = (PLOUSINE_NODE_LIST)FileHeader->FirstEntry;
        }

        LastEntry = CurrentRootCompilerHandle;
        LastOffset = CurrentOffset;
        RootNodes = (PLOUSINE_NODE)RootNodes->NodePeers.Forward;
    }

    //LkrCreateFile((PLOUSINE_NODE)Context->CompilerNode, 0x00, &Context->OutContext);

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