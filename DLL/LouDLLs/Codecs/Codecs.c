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

    LouPrint("Here:%h With Value:%h\n", NewPng, *(uint64_t*)NewPng);

    while(1);
    return 0x00;
}