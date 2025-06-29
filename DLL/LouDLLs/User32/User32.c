#include "User32.h"
#include "Awm.h"


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

USER32_API
void free(void* Address){
    LouGenericFreeHeap(
        GetProcessHeap(),
        Address
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
PWINDHANDLE AnnyaCreateCanvasBuffer(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){  
    LouPrint("AnnyaCreateCanvasBuffer(n");
    return 0x00;
}


static mutex_t ButtonCreationLock;




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