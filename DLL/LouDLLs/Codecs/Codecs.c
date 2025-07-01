#include "codecs.h"
#include "Png/png.h"
#include "Bmp/Bmp.h"

CODECS_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

PCODECS_TYPE_QUERY AnnyaCodecsCreateHandle(
    CODEC_HANDLE_TYPE HandleType, 
    int SubHandle, 
    HANDLE PrivateData
){
    PCODECS_TYPE_QUERY Result = LouGlobalUserMallocType(CODECS_TYPE_QUERY);

    switch(HandleType){
        case IMAGE_HANDLE:
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