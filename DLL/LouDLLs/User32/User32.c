#include "User32.h"


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
        LouCALL(LOUVMALLOC, (uint64_t)&CallData[0], 0);
    }
    return (void*)CallData[1];
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
PVOID AnnyaCreateCanvasBuffer(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    uintptr_t ParentWindow,
    PVOID Charecteristics
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