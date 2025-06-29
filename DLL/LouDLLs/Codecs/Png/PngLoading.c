#include "../codecs.h"
#include "png.h"
#include <zlib.h>


static HMODULE HmZlib = 0x00;
static const char* (*ImpZlibVersion)(void);
static int (*ImpInflateInit_)(z_stream*, const char*, int);
static int (*ImpInflate)(z_stream*, int);
static int (*ImpInflateEnd)(z_stream*);
static size_t (*strlen)(string);

#define IMP_ZLIB_VERSION ImpZlibVersion()

#define ImpInflateInit(strm) (ImpInflateInit_((strm), IMP_ZLIB_VERSION, (int)sizeof(z_stream)))

CODECS_API
LOUSTATUS InitializePNGHandleing(){
    LouPrint("CODECS.DLL:Initializing PNG Handling\n");
    HmZlib =  LoadLibraryA("C:/ANNYA/ZLIB1.DLL");
    if(!HmZlib){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize ZLIB1.DLL\n");
        return STATUS_UNSUCCESSFUL;
    }
    ImpZlibVersion = AnnyaGetLibraryFunctionN("ZLIB1.DLL", "zlibVersion");
    if(!ImpZlibVersion){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize Get zlibVersion Function\n");
        return STATUS_UNSUCCESSFUL;
    }
    ImpInflateInit_ = AnnyaGetLibraryFunctionN("ZLIB1.DLL", "inflateInit_");
    if(!ImpInflateInit_){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize Get inflateInit_ Function\n");
        return STATUS_UNSUCCESSFUL;
    }
    ImpInflate = AnnyaGetLibraryFunctionN("ZLIB1.DLL", "inflate");
    if(!ImpInflate){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize Get inflate Function\n");
        return STATUS_UNSUCCESSFUL;
    }
    ImpInflateEnd = AnnyaGetLibraryFunctionN("ZLIB1.DLL", "inflateEnd");
    if(!ImpInflateEnd){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize Get inflateEnd Function\n");
        return STATUS_UNSUCCESSFUL;
    }
    strlen = AnnyaGetLibraryFunctionN("LOUDLL.DLL", "strlen");
    if(!strlen){
        LouPrint("CODECS.DLL:ERROR Unable To Initialize Get strlen Function\n");
        return STATUS_UNSUCCESSFUL;
    }

    LouPrint("ZLIB Version:%s\n", ImpZlibVersion());

    LouPrint("CODECS.DLL:Initializing PNG Handling STATUS_SUCCESS\n");
}

static void CreateHeaderHandle(
    PPNG_CHUNK_HEADER_HANDLE HandleObject,
    PPNG_CHUNK_HEADER Header
){
    LouSwapEndianess(&Header->Length, &HandleObject->Length, sizeof(uint32_t)); 
    LouMemCpy(&HandleObject->Type, &Header->Type, 4);
    LouPrint("Header Chunk Length:%d Bytes\n", HandleObject->Length);
}

static void* CreateGenericDataHandle(
    PPNG_CHUNK_HEADER_HANDLE HandleObject,
    PPNG_CHUNK_HEADER Header
){
    void* DataHandle = LouGlobalUserMallocEx(sizeof(PNG_CHUNK_HEADER) + HandleObject->Length + sizeof(uint32_t), GET_ALIGNMENT(PNG_CHUNK_HEADER));
    LouMemCpy(DataHandle, Header, sizeof(PNG_CHUNK_HEADER) + HandleObject->Length + sizeof(uint32_t));
    return DataHandle;
}

static void InterperateImageHeaderData(
    PPNG_CHUNK_HEADER_HANDLE HandleObject, 
    PPNG_IMAGE_CHUNK ImageHeader
){
    CreateHeaderHandle(HandleObject, &ImageHeader->ChunkHeader);

    HandleObject->Data = (uint8_t*)CreateGenericDataHandle(HandleObject, &ImageHeader->ChunkHeader);
    PPNG_IMAGE_CHUNK ImageData = (PPNG_IMAGE_CHUNK)HandleObject->Data;

    uint32_t Tmp  = ImageData->ChunkHeader.Length;
    LouSwapEndianess(&Tmp, &ImageData->ChunkHeader.Length, sizeof(uint32_t));
    Tmp = ImageData->Width;
    LouSwapEndianess(&Tmp, &ImageData->Width, sizeof(uint32_t));
    Tmp = ImageData->Height;
    LouSwapEndianess(&Tmp, &ImageData->Height, sizeof(uint32_t));

    HandleObject->Data = (uint8_t*)ImageData;

}


static void InterperateImageData(   
    PPNG_CHUNK_HEADER ImageDataHeader,
    PIDAT_CODECS_STREAM_UNPACKER UnpackStream
){
    uint32_t Length;
    LouSwapEndianess(&ImageDataHeader->Length, &Length, sizeof(uint32_t));
    void* CurrentIndex = UnpackStream->CurrentIndex;
    LouMemCpy(CurrentIndex, (uint8_t*)((uint64_t)ImageDataHeader + sizeof(PNG_CHUNK_HEADER)), Length);
    UnpackStream->CurrentIndex = (void*)((uint64_t)CurrentIndex + (uint64_t)Length); 
}


static void InterperatePPCPCAWPCData(
    PPNG_CHUNK_HEADER_HANDLE HandleObject,
    PPCAWPH PpcawpcHeader
){
    CreateHeaderHandle(HandleObject, &PpcawpcHeader->ChunkHeader);
    HandleObject->Data = (uint8_t*)CreateGenericDataHandle(HandleObject, &PpcawpcHeader->ChunkHeader);
}

static void* InflatePng(void* Data, size_t* DataSize){
    LouPrint("InflatePng()\n");
    z_stream Stream = {0};
    Stream.next_in = Data;
    Stream.avail_in = *DataSize;

    if(ImpInflateInit(&Stream) != Z_OK){
        LouPrint("ImpInflateInit() ERROR\n");
        while(1);
    }

    #define CHUNK_SIZE 1024

    size_t TotalOutputSize = 0x00;
    size_t OutputCapacity = CHUNK_SIZE;
    uint8_t* DecompData = LouGlobalUserMallocEx(OutputCapacity , 8);
    uint8_t* BackupDecompData = 0x00;
    int Result = 0x00;
    do{
        if((TotalOutputSize + CHUNK_SIZE) > OutputCapacity){
            BackupDecompData = LouGlobalUserMallocEx(OutputCapacity + CHUNK_SIZE, 8);
            LouMemCpy(BackupDecompData, DecompData, OutputCapacity);
            OutputCapacity += CHUNK_SIZE;
            LouGlobalUserFree(DecompData);
            DecompData = BackupDecompData;
        }

        Stream.next_out = (void*)((uint64_t)DecompData + TotalOutputSize);
        Stream.avail_out = CHUNK_SIZE;
        
        Result = ImpInflate(&Stream, Z_NO_FLUSH);
        if(Result < 0){
            LouPrint("Inflate Error\n");
            ImpInflateEnd(&Stream);
            LouGlobalUserFree(DecompData);
            return 0x00;
        }

        TotalOutputSize += CHUNK_SIZE - Stream.avail_out;

    }while(Result != Z_STREAM_END);
    ImpInflateEnd(&Stream);
    LouPrint("InflatePng() STATUS_SUCCESS\n");
    
    return DecompData;
}


CODECS_API 
HANDLE AnnyaOpenPngA(
    string FileName
){
    FILE* NewPng = LouOpenFileA(FileName);
    IDAT_CODECS_STREAM_UNPACKER IDATUnpacker = {0};

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
    size_t PngHeaderCount = 1;
    while(strncmp(TmpChunkData.Type, PNG_IMAGE_TRAILER_HEADER_TYPE,  sizeof(uint32_t)) != 0x00){
        LouPrint("Header:%s\n", TmpChunkData.Type);
        if(strncmp(TmpChunkData.Type, PNG_IMAGE_DATA_HEADER_TYPE, 4) == 0){
            IDATUnpacker.StreamSize += TmpChunkData.Length;
            PngHeaderCount++;
        }else{
            PngHeaderCount++;
        }
        ChunkData = (PPNG_CHUNK_HEADER)((uint64_t)ChunkData + TmpChunkData.Length + (sizeof(PNG_CHUNK_HEADER) + sizeof(uint32_t))); 
        LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
        LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t));
    }
    
    IDATUnpacker.UnpackedStream = LouGlobalUserMallocEx(IDATUnpacker.StreamSize, 8); 
    IDATUnpacker.CurrentIndex = IDATUnpacker.UnpackedStream;

    PPNG_CHUNK_HEADER_HANDLE PngHeaderHandles = LouGlobalUserMallocArray(PNG_CHUNK_HEADER_HANDLE, PngHeaderCount);

    if(!PngHeaderHandles){
        LouCloseFile(NewPng);
        return 0x00;
    }

    ChunkData = (PPNG_CHUNK_HEADER)(uint8_t*)((uint64_t)NewPng + sizeof(uint64_t));    
    LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
    LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t)); 

    for(size_t i = 0; i < PngHeaderCount; i++){
        LouPrint("Interpreting %s Png Header\n", TmpChunkData.Type);
        if(strncmp(TmpChunkData.Type, PNG_IMAGE_HEADER_TYPE, 4) == 0){
            InterperateImageHeaderData(&PngHeaderHandles[i], (PPNG_IMAGE_CHUNK)ChunkData);
        }else if(strncmp(TmpChunkData.Type, PNG_IMAGE_DATA_HEADER_TYPE, 4) == 0){
            CreateHeaderHandle(&PngHeaderHandles[i], ChunkData);
            CreateGenericDataHandle(&PngHeaderHandles[i], ChunkData);
            InterperateImageData(ChunkData, &IDATUnpacker);
            PngHeaderHandles[i].CompressedData = true;
        }else{
            CreateHeaderHandle(&PngHeaderHandles[i], ChunkData);
            CreateGenericDataHandle(&PngHeaderHandles[i], ChunkData);
        }
        
        ChunkData = (PPNG_CHUNK_HEADER)((uint64_t)ChunkData + TmpChunkData.Length + (sizeof(PNG_CHUNK_HEADER) + sizeof(uint32_t))); 
        LouSwapEndianess(&ChunkData->Length, &TmpChunkData.Length, sizeof(uint32_t)); 
        LouMemCpy(TmpChunkData.Type, &ChunkData->Type, sizeof(uint32_t));
    }

    LouMemCpy(&PngHeaderHandles[PngHeaderCount - 1].Type, PNG_IMAGE_DATA_HEADER_TYPE, 4);
    
    PngHeaderHandles[PngHeaderCount - 1].Data = InflatePng((uint8_t*)IDATUnpacker.UnpackedStream, &IDATUnpacker.StreamSize);
    PngHeaderHandles[PngHeaderCount - 1].Length = IDATUnpacker.StreamSize;

    PPNG_HANDLE ReturnHandle = LouGlobalUserMallocType(PNG_HANDLE);
    ReturnHandle->PngName = LouGlobalUserMallocEx(strlen(FileName), 1);
    LouMemCpy(ReturnHandle->PngName, FileName, strlen(FileName));
    ReturnHandle->HeaderCount = PngHeaderCount; 
    ReturnHandle->HeaderData = (void*)PngHeaderHandles;
    return (HANDLE)ReturnHandle;
}