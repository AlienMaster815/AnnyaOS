#include "codecs.h"
#include "Png/png.h"
#include "Bmp/Bmp.h"

CODECS_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

CODECS_API
void 
AnnyaPaintClipWithBmp(
    HANDLE  Bitmap,
    HANDLE  Cliph,
    size_t  X, 
    size_t  Y,
    size_t  ScalingX,
    size_t  ScalingY
);

PCODECS_TYPE_QUERY AnnyaCodecsCreateHandle(
    CODEC_HANDLE_TYPE HandleType, 
    int SubHandle, 
    HANDLE PrivateData
){
    PCODECS_TYPE_QUERY Result = LouGlobalUserMallocType(CODECS_TYPE_QUERY);

    switch(HandleType){
        case IMAGE_HANDLE:
            Result->HandleType = IMAGE_HANDLE;
            Result->HandleInformation.ImageHandleData.ImageSubType = (CODEC_HANDLE_IMAGE_SUBTYPE)SubHandle;
            Result->HandleInformation.ImageHandleData.PrivateDataHandle = PrivateData;
            switch((CODEC_HANDLE_IMAGE_SUBTYPE)SubHandle){
                case PNG:
                    PPNG_HANDLE PngHandle = PrivateData;    
                    Result->HandleInformation.ImageHandleData.Width = PngHandle->Width;
                    Result->HandleInformation.ImageHandleData.Height = PngHandle->Height;
                    break;
                case BMP:
                    PBITMAP_HANDLE BmpHandle = PrivateData;
                    Result->HandleInformation.ImageHandleData.Width = BmpHandle->Width;
                    Result->HandleInformation.ImageHandleData.Height = BmpHandle->Height;
                    break;
            }
            break;
        default:
            Result->HandleType = INVALID_HANDLE;
            break;
    }

    return Result;
}


CODECS_API
LOUSTATUS AnnyaCodecsPaintClipFromImageHandle(
    PCODECS_TYPE_QUERY Handle, 
    HANDLE  Cliph,
    size_t  X, 
    size_t  Y,
    size_t  ScalingX,
    size_t  ScalingY
){
    if(Handle->HandleType != IMAGE_HANDLE){
        return STATUS_INVALID_PARAMETER;
    }

    switch(Handle->HandleInformation.ImageHandleData.ImageSubType){

        case BMP:
            AnnyaPaintClipWithBmp(
                (HANDLE)Handle,
                Cliph,
                X,
                Y,
                ScalingX,
                ScalingY
            );
            break;

        case PNG:
            return STATUS_UNSUCCESSFUL;
            break;
        default:
            return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}