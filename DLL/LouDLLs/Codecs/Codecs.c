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
    FILE NewPng = LouOpenFileA(FileName);

    uint64_t PngSignature = 0;
    LouSwapEndianess(NewPng, &PngSignature,sizeof(uint64_t));


    LouPrint("Signature Value:%h ", PngSignature);

    while(1);
    return 0x00;
}