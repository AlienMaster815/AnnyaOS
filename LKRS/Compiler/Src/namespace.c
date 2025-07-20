#include <Lkrs.h>



static size_t LkrsInitializeNameSpaceOpject(
    PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle,
    PLKRS_NAMESPACE_NODE NameNode, 
    char* NameSpacePointer
){
    size_t FileSize = KrfHandle->KrfSize;
    size_t StringOffset = ((uintptr_t)NameSpacePointer - (uintptr_t)KrfHandle->KrfData);
    size_t Name = strlen(LKRS_NAMESPACE);
    size_t NameSize = 0;
    size_t InvalidCharecters = 0;
    while((StringOffset + Name) < FileSize){
        if(NameSpacePointer[Name] != ' '){
            break;
        }
        Name++;
    }
    while((StringOffset + Name + NameSize) < FileSize){
        if((NameSpacePointer[Name + NameSize] == ';') || (NameSpacePointer[Name + NameSize] == '{')){
            break;
        }else if(NameSpacePointer[Name + NameSize] == ' '){
            InvalidCharecters++;
        }
        NameSize++;
    }
    
    NameNode->NodeName = LkrsMalloc((NameSize - InvalidCharecters) + 1);
    NameNode->NodeName[NameSize - InvalidCharecters] = '\0';
    memcpy(NameNode->NodeName, &NameSpacePointer[Name], NameSize - InvalidCharecters);

    if(NameSpacePointer[Name + NameSize] == '{'){
        NameNode->NodeData = &NameSpacePointer[Name + NameSize];
        while((StringOffset + Name + NameSize) < FileSize){
            if(NameSpacePointer[Name + NameSize] == '}'){
                break;
            }
            NameSize++;
        }
        return Name + NameSize;
    }else{

        return Name + NameSize + 1;
    }
}

static int LkrsBuildCompilation(PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle){
    PLKRS_NAMESPACE_NODE NameNode = &KrfHandle->NameNodes;
    size_t WriteIndex = strlen("LOUSINESYSTEMFILE");

    size_t AllocationSize = 17;// L O U S I N E S Y S T E M F I L E 
    while(NameNode){
        AllocationSize += 2; //1 byte opcode 1 and 1 byte for size
        if(NameNode->NodeName){
            AllocationSize += strlen(NameNode->NodeName);
        }else{
            NameNode->NodeName = LKRS_NAMESPACE_HEADER_END;
            AllocationSize += strlen(LKRS_NAMESPACE_HEADER_END);
        }
        AllocationSize += 16; //8 bytes for the offset and 8 for length of the namespace in file
        NameNode = NameNode->NextNode;
    }

    KrfHandle->CompiledSize = AllocationSize;
    KrfHandle->CompiledData = LkrsMalloc(AllocationSize);
    
    strcpy((char*)KrfHandle->CompiledData, "LOUSINESYSTEMFILE");
    
    NameNode = &KrfHandle->NameNodes;
    while(NameNode){
        KrfHandle->CompiledData[WriteIndex++] = LKRS_NAMESPACE_DECLARATION_OPCODE;
        KrfHandle->CompiledData[WriteIndex++] = strlen(NameNode->NodeName);
        strcpy((char*)&KrfHandle->CompiledData[WriteIndex], NameNode->NodeName); 
        WriteIndex += strlen(NameNode->NodeName);
        for(size_t z = 0 ; z < 8; z++){
            KrfHandle->CompiledData[WriteIndex + z] = 0;
        }
        WriteIndex += 16;
        NameNode = NameNode->NextNode;
    }
    return 0;
}

int LkrsBuildGlobalNameSpaceDefinitions(PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle){

    char* RawData = (char*)KrfHandle->KrfData;
    size_t FileSize = KrfHandle->KrfSize;
    PLKRS_NAMESPACE_NODE CurrentNameNode = &KrfHandle->NameNodes;
    for(size_t i = 0 ; i < FileSize; i++){
        if(!strncmp(&RawData[i], LKRS_NAMESPACE, strlen(LKRS_NAMESPACE))){  
            i += LkrsInitializeNameSpaceOpject(
                KrfHandle, 
                CurrentNameNode, 
                &RawData[i]
            );
            CurrentNameNode->NextNode = LkrsMalloc(sizeof(LKRS_NAMESPACE_NODE));
            memset(CurrentNameNode->NextNode, 0 , sizeof(LKRS_NAMESPACE_NODE));
            CurrentNameNode = CurrentNameNode->NextNode;
        }
    }
    LkrsBuildCompilation(KrfHandle);
    return 0;
}

size_t LkrsGetNameSpaceSize(PLKRS_NAMESPACE_NODE Node) {
    char* NodeData = Node->NodeData + 1;
    size_t Indents = 1;
    size_t NodeSize = 0;
    while(Indents){
        if(NodeData[NodeSize] == '}'){
            Indents--;
        }else if(NodeData[NodeSize] == '{'){
            Indents++;
        }
        NodeSize++;
    }
    return NodeSize;
}


int LkrsBuildNameSpaceData(PKERNEL_REGISTRY_SOURCE_HANDLE KrfHandle){
    PLKRS_NAMESPACE_NODE NameNode = &KrfHandle->NameNodes;
    while(NameNode->NextNode){
        size_t SearchLength = LkrsGetNameSpaceSize(NameNode);
        NameNode->NodeDataSize = SearchLength;
        size_t DataSize = CountNameSpaceData(NameNode);
        uint8_t* CompiledDataTmp = KrfHandle->CompiledData;
        KrfHandle->CompiledData = LkrsMalloc(KrfHandle->CompiledSize + DataSize);
        memcpy(KrfHandle->CompiledData, CompiledDataTmp, KrfHandle->CompiledSize);
        char* NameSpaceHeaderEntry = LkrsGetNameSpaceEntryFromRawStreamSafe((char*)KrfHandle->CompiledData, KrfHandle->CompiledSize, NameNode->NodeName);
        uint64_t DataOffset = (uint64_t)(&KrfHandle->CompiledData[KrfHandle->CompiledSize] - KrfHandle->CompiledData);
        LkrsWriteUint64(&NameSpaceHeaderEntry[NameSpaceHeaderEntry[1] + 2], DataOffset);        
        LkrsWriteUint64(&NameSpaceHeaderEntry[(NameSpaceHeaderEntry[1] + 2) + 8], DataSize);

        KrfHandle->CompiledData[KrfHandle->CompiledSize] = LKRS_NAMESPACE_DATA_START;
        NameNode->CompilationBuffer = (char*)&KrfHandle->CompiledData[KrfHandle->CompiledSize];
        KrfHandle->CompiledSize += DataSize;
        KrfHandle->CompiledData[KrfHandle->CompiledSize - 1] = LKRS_NAMESPACE_DATA_END;
        free(CompiledDataTmp);
        NameNode->CurrentWriteIndex = 1;
        WriteNameSpaceToFile(NameNode);

        NameNode = NameNode->NextNode;
    }
    return 0;
}


char* LkrsGetNameSpaceEntryFromRawStreamSafe(char* Stream, size_t StreamSize, char* NameSpaceVariable){
    size_t StreamIndex = 0;
    while(StreamIndex < StreamSize){
        
        if((!strcmp(&Stream[StreamIndex + 2], NameSpaceVariable)) && ((Stream[StreamIndex + 1] == strlen(NameSpaceVariable)))){
            return &Stream[StreamIndex];
        }
        StreamIndex++;
    }
    return 0x00;
}