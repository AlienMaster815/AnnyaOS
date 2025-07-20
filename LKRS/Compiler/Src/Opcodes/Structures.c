#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Lkrs.h>

static size_t LkrsGetStructSize(char* Buffer) {
    Buffer++;
    size_t Indents = 1;
    size_t NodeSize = 1;
    while(Indents){
        if(Buffer[NodeSize] == '}'){
            Indents--;
        }else if(Buffer[NodeSize] == '{'){
            Indents++;
        }
        NodeSize++;
    }
    return NodeSize + 1;//semicolon
}

size_t LkrsGetStructStart(char* Name){
    size_t Length = 0;
    while(1){
        if(Name[Length] == '{'){
            return Length;
        }
        Length++;
    }
} 

size_t LkrsCreateStructureDeclarationHandle(
    PLKRS_NAMESPACE_HANDLE_TREE MasterTree,
    PLKRS_NAMESPACE_HANDLE_TREE TreeHandle, 
    char* StructBuffer
){
    size_t StuctSize = 0;
    StructBuffer += strlen(LKRS_STRUCTURE);
    StructBuffer += LkrsGetStructStart(StructBuffer);
    size_t BufferSize = LkrsGetStructSize(StructBuffer);
    size_t i = 0;
    size_t Elements = 0;
    while(i < BufferSize){
        if(!strncmp(&StructBuffer[i], LKRS_BYTE,strlen(LKRS_BYTE))){
            //size_t ByteSize = LkrsCountByteDeclarationSize(&StructBuffer[i]);
            //StuctSize += ByteSize;
            i += LkrsCountByteDeclarationSourceLength(&StructBuffer[i]);
            Elements++;
        }else if(!strncmp(&StructBuffer[i], LKRS_WORD, strlen(LKRS_WORD))){
            //size_t WordSize = LkrsCountWordDeclarationSize(&StructBuffer[i]);
            //StuctSize += WordSize;
            i+= LkrsCountWordDeclarationSourceLength(&StructBuffer[i]);
            Elements++;
        }else if(!strncmp(&StructBuffer[i], LKRS_STRING, strlen(LKRS_STRING))){
            //size_t StringSize = LkrsCountStringDeclarationSize;
            i+= LkrsCountStringDeclarationSourceLength(&StructBuffer[i]);
            Elements++;
        }else{
            i++;
        }
    }

    return 0;
}

size_t LkrsIncrementStructureDeclaration(char* StructBuffer){
    size_t StructSize = strlen(LKRS_STRUCTURE);
    StructSize += LkrsGetStructStart(&StructBuffer[StructSize]);
    StructSize += LkrsGetStructSize(&StructBuffer[StructSize]);
    return StructSize;
}