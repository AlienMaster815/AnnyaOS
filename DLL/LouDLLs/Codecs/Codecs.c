#include "codecs.h"
#include "png.h"


CODECS_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}


CODECS_API 
HANDLE AnnyaOpenPngA(
    string FileName
){
    FILE* NewPng = LouOpenFileA(FileName);

    uint64_t PngSignature = 0;
    uint32_t ChunkType = 0;
    LouSwapEndianess(NewPng, (void*)&PngSignature, sizeof(uint64_t));
    if(PngSignature != PNG_SIGNATURE){
        LouCloseFile(NewPng);
        return 0x00;
    }
    PNG_CHUNK_HEADER_HANDLE TmpChunkData = {0};
    PPNG_CHUNK_HEADER ChunkData = (PPNG_CHUNK_HEADER)(uint8_t*)((uint64_t)NewPng + sizeof(uint64_t));

    LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
    LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t)); 
    
    size_t PngHeaderCount = 0x00;
    while(strncmp(TmpChunkData.Type, PNG_IMAGE_TRAILER_HEADER_TYPE,  sizeof(uint32_t)) != 0x00){
        LouPrint("Header:%s\n", TmpChunkData.Type);
        PngHeaderCount++;
        ChunkData = (PPNG_CHUNK_HEADER)((uint64_t)ChunkData + TmpChunkData.Length + (sizeof(PNG_CHUNK_HEADER) + sizeof(uint32_t))); 
        LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
        LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t));
    }
    
    PPNG_CHUNK_HEADER_HANDLE PngHeaderHandles = malloc(ROUND_UP64(sizeof(PNG_CHUNK_HEADER_HANDLE), GET_ALIGNMENT(PNG_CHUNK_HEADER_HANDLE)) * PngHeaderCount);
    if(!PngHeaderHandles){
        LouCloseFile(NewPng);
        return 0x00;
    }

    ChunkData = (PPNG_CHUNK_HEADER)(uint8_t*)((uint64_t)NewPng + sizeof(uint64_t));    
    LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
    LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t)); 

    for(size_t i = 0; i < PngHeaderCount; i++){
        LouPrint("Interpreting %s Png Header\n", TmpChunkData.Type);

        

        ChunkData = (PPNG_CHUNK_HEADER)((uint64_t)ChunkData + TmpChunkData.Length + (sizeof(PNG_CHUNK_HEADER) + sizeof(uint32_t))); 
        LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
        LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t));
    }


    LouPrint("ChunkLength:%h ChunkType:%s\n", TmpChunkData.Length, TmpChunkData.Type);

    LouPrint("Here\n");
    while(1);
    return 0x00;
}