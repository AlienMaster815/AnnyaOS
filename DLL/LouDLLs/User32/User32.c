#define USER32_API __declspec(dllexport)
#define _USER_32_

#include <Annya.h>

//x86_64-w64-mingw32-gcc -shared -o user32.dll User32.c -nostdlib -nodefaultlibs -I../../../Include -L../../../UserLibraries -lLouDll



USER32_API
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

USER32_API
void* AnnyaAPIVMalloc(uint64_t BytesNeeded){
    uint64_t CallData[2];
    CallData[0] = 0;
    CallData[1] = BytesNeeded;
    while(CallData[0] != 1){
        LouCALL(LOUVMALLOC, (uint64_t)&CallData, 0);
    }
    return (void*)CallData[1];
}


static inline size_t GetAlignmentBySize(size_t Size){
    if(Size <= 2)    return 2;
    if(Size <= 4)    return 4;
    if(Size <= 8)    return 8;
    if(Size <= 16)   return 16;
    if(Size <= 32)   return 32;
    if(Size <= 64)   return 64;
    if(Size <= 128)  return 128;
    if(Size <= 256)  return 256;
    if(Size <= 512)  return 512;
    if(Size <= 1024) return 1024;
    if(Size <= 2048) return 2048;
    return 4096;
}

USER32_API
void* malloc(size_t BytesNeeded){

    return LouGenericAllocateHeapEx(
        GetProcessHeap(), 
        BytesNeeded,
        GetAlignmentBySize(BytesNeeded)
    );
}

//USER32_API
//void AnnyaAPIVFree(uint64_t FreeHandle){
//    uint64_t Data = FreeHandle;
//    LouCALL(LOUVFREE, &Data, 0);
//}

USER32_API
void* AnnyaAPI(){

}

USER32_API
void AnnyaResetGpu(uint64_t Monitor){


}

USER32_API
PBITMAP_HANDLE AnnyaOpenBitmapImage(
    string FileName
){
    uint64_t Data[2]; 
    Data[0] = 0;
    Data[1] = (uint64_t)FileName;
    while(Data[0] != 1){
        LouCALL(LOULOADBITMAP, (uint64_t)&Data, 0);
    }
    return (PBITMAP_HANDLE)Data[1];
}

USER32_API
void DrawDesktopBackground(FILE* FileHandle, uint16_t FileType){

    while(1);
}

USER32_API
PWINDHANDLE AnnyaCreateWindow(
    const int64_t x, const int64_t y,
    const uint32_t width, const uint32_t height, 
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){
    LouPrint("AnnyaCreateWindow()\n");
    while(1);
    return (PWINDHANDLE)0x00;
}

USER32_API
PWINDHANDLE AnnyaCreateCanvasBuffer(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){  
    LouPrint("AnnyaCreateCanvasBuffer(n");
    return 0x00;
}

USER32_API
void AnnyaChangeCanvasBufferColor(
    PWINDHANDLE WindowHandle,
    uint16_t r,
    uint16_t g,
    uint16_t b,
    uint16_t a //not used yet but added for futrue proof
){
    LouPrint("AnnyaChangeCanvasBufferColor()\n");
    while(1);
}

static mutex_t ButtonCreationLock;


USER32_API
PBUTTONHANDLE AnnyaCreateButton(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    uintptr_t ParentWindow,
    PBUTTON_CHARECTERISTICS Charecteristics
){

    LouPrint("AnnyaCreateButton()\n");
    while(1);
    return (PBUTTONHANDLE)0x00;
}


//USER32_API
//BOOL AnnyaGetMessage(
//    MSG* Message, 
//    HWND* Window, 
//    UINT MinFilter, 
//    UINT MaxFilter
//){



//    return true;
//}

USER32_API
void MessageBoxW(){

    LouPrint("Hello Win32 World\n");

    while(1);
}