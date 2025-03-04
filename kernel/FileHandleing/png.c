#include <LouAPI.h>

//TODO File Editor

typedef struct __attribute__((packed, aligned(1))) _PNG_CHUNK_HEADER{
    uint32_t Length;
    uint32_t Type;
}PNG_CHUNK_HEADER, * PPNG_CHUNK_HEADER;

static inline PPNG_CHUNK_HEADER GetNextPngChunk(PPNG_CHUNK_HEADER CurrentChunk){
    uint32_t ChunkLength = U32_TO_NETWORK_BYTE_ORDER(CurrentChunk->Length);
    ChunkLength += 4;//fixes optimization quirks
    return (PPNG_CHUNK_HEADER)(uint8_t*)(((uintptr_t)(uint8_t*)CurrentChunk) + (uintptr_t)(4 + ChunkLength + 4));
}

FILE* EncodePngFile(FILE* PngLocation){



    return 0x00;
}

static size_t PngGetIdatDataCount(PPNG_CHUNK_HEADER IHDR){
    char ChunkType[5] = {'\0'};
    ISO646StandardAlphaNumericToAsciiAlphaNumeric(ChunkType, (uint8_t*)&IHDR->Type, 4);
    size_t Result = 0; 
    while(strncmp(ChunkType, "IEND" , strlen("IEND")) != 0){

        if(strncmp(ChunkType, "IDAT" , strlen("IDAT")) == 0){
            Result++;
        }

        IHDR = GetNextPngChunk(IHDR);
        ISO646StandardAlphaNumericToAsciiAlphaNumeric(ChunkType, (uint8_t*)&IHDR->Type, 4);
    }
    return Result;
}

FILE* DecodePngFile(FILE* PngLoaction){
    PPNG_CHUNK_HEADER TmpChunk = (PPNG_CHUNK_HEADER)((uint8_t*)PngLoaction + 8);//IHDR Chunk is at offset 8
    UNUSED PPNG_CHUNK_HEADER IHDR = TmpChunk;

    char ChunkType[5] = {'\0'};
    ISO646StandardAlphaNumericToAsciiAlphaNumeric(ChunkType, (uint8_t*)&TmpChunk->Type, 4);

    size_t IDATCount = PngGetIdatDataCount(TmpChunk);
    uint8_t* TmpZlibBuffer = 0;
    size_t TmpUncompressesdSize = 0;
    UNUSED uint8_t** ZlibUnpackedBuffers = (uint8_t**)LouMalloc(sizeof(uint8_t*) * IDATCount);
    uint8_t IdatIndex = 0;
    while(strncmp(ChunkType, "IEND" , strlen("IEND")) != 0){

        LouPrint("PNG HEADER Length:%h\n", U32_TO_NETWORK_BYTE_ORDER(TmpChunk->Length));
        LouPrint("PNG HEADER Type  :%s\n", ChunkType);

        if(strncmp(ChunkType, "IDAT" , strlen("IDAT")) == 0){
            TmpZlibBuffer = (uint8_t*)(((uintptr_t)(uint8_t*)TmpChunk) + 8);      
            //LouPrint("Buffer Offset:%h\n", (uintptr_t)TmpZlibBuffer - (uintptr_t)PngLoaction);
            TmpUncompressesdSize = LouKeGetZlibUnCompressedSize(TmpZlibBuffer, U32_TO_NETWORK_BYTE_ORDER(TmpChunk->Length));
            if((TmpUncompressesdSize == 0xFFFFFFFF) || (!TmpUncompressesdSize)){
                ZlibUnpackedBuffers[IdatIndex] = (uint8_t*)LouMalloc(U32_TO_NETWORK_BYTE_ORDER(TmpChunk->Length) * 4);
            }else{
                ZlibUnpackedBuffers[IdatIndex] = (uint8_t*)LouMalloc(TmpUncompressesdSize);
            }
            //LOUSTATUS LouKeZlibUnpackStream(uint8_t* OutputStream, size_t* OutputStreamSize, uint8_t* InputStream, size_t InputLength)
            LouKeZlibUnpackStream(ZlibUnpackedBuffers[IdatIndex], &TmpUncompressesdSize, TmpZlibBuffer, U32_TO_NETWORK_BYTE_ORDER(TmpChunk->Length));
            IdatIndex++;
        }

        TmpChunk = GetNextPngChunk(TmpChunk);
        ISO646StandardAlphaNumericToAsciiAlphaNumeric(ChunkType, (uint8_t*)&TmpChunk->Type, 4);
    }

    return 0x00;
}

PPNG_FILE_HANDLE LouKeOpenPngImage(string Path){
    
    FILE* RawPng = fopen(Path); 
    if(!RawPng){
        return 0x00;
    }
    uint8_t* Buffer = (uint8_t*)RawPng;
    if((Buffer[0] != 0x89)  ||
       (Buffer[1] != 'P')   ||
       (Buffer[2] != 'N')   ||
       (Buffer[3] != 'G')   
    ){
        LouPrint("ERROR: File Is Not A PNG Image\n");
        //fclose(RawPng);
        return 0x00;
    }

    PPNG_FILE_HANDLE Result = (PPNG_FILE_HANDLE)LouKeMalloc(sizeof(PNG_FILE_HANDLE), USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);

    Result->UnpackedBase = DecodePngFile(RawPng);


    LouPrint("Success\n");
    while(1);
    return Result;
}