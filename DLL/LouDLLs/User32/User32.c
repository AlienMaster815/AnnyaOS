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

USER32_API
void* malloc(size_t BytesNeeded){
    return AnnyaAPIVMalloc(BytesNeeded);
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
    uint64_t Data[3];
    Data[0] = 0;
    Data[1] = (uint64_t)FileHandle;
    Data[2] = (uint64_t)FileType;
    while(Data[0] != 1){
        LouCALL(LOUDRAWDESKBACK, (uint64_t)&Data, 0);
    }
}

USER32_API
volatile PWINDHANDLE AnnyaCreateWindow(
    const uint16_t x, const uint16_t y,
    const uint16_t width, const uint16_t height, 
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){
    uint64_t Data[7];
    Data[0] = 0;
    Data[1] = (uint64_t)x;
    Data[2] = (uint64_t)y;
    Data[3] = (uint64_t)width;   
    Data[4] = (uint64_t)height;
    Data[5] = (uint64_t)ParentWindow;
    Data[6] = (uint64_t)Charecteristics;
    while(Data[0] != 1){
        LouCALL(LOUCREATEWINDOW, (uint64_t)&Data, 0);
    }
    return (volatile PWINDHANDLE)Data[1];
}

USER32_API
volatile PWINDHANDLE AnnyaCreateCanvasBuffer(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
){
    uint64_t Data[7];
    Data[0] = 0;
    Data[1] = (uint64_t)x;
    Data[2] = (uint64_t)y;
    Data[3] = (uint64_t)Width;   
    Data[4] = (uint64_t)Height;
    Data[5] = (uint64_t)ParentWindow;
    Data[6] = (uint64_t)Charecteristics;
    while(Data[0] != 1){
        LouCALL(LOUCREATECANVASBUFF, (uint64_t)&Data, 0);
    }
    return (volatile PWINDHANDLE)Data[1];
}

USER32_API
void AnnyaChangeCanvasBufferColor(
    volatile PWINDHANDLE WindowHandle,
    uint16_t r,
    uint16_t g,
    uint16_t b,
    uint16_t a //not used yet but added for futrue proof
){
    uint64_t Data[6];
    Data[0] = 0;
    Data[1] = (uint64_t)WindowHandle;
    Data[2] = (uint64_t)r;
    Data[3] = (uint64_t)g;
    Data[4] = (uint64_t)b;
    while(Data[0] != 1){
        LouCALL(LOUCHAGECANVASCOLOR, (uint64_t)&Data, 0);
    }
}

static mutex_t ButtonCreationLock;


USER32_API
PBUTTONHANDLE AnnyaCreateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    PBUTTON_CHARECTERISTICS Charecteristics
){
    MutexLock(&ButtonCreationLock);
    uint64_t Data[7];
    Data[0] = 0;
    Data[1] = (uint64_t)x;
    Data[2] = (uint64_t)y;
    Data[3] = (uint64_t)Width;   
    Data[4] = (uint64_t)Height;
    Data[5] = (uint64_t)ParentWindow;
    Data[6] = (uint64_t)Charecteristics;
    while(Data[0] != 1){
        LouCALL(LOUCREATEBUTTON, (uint64_t)&Data, 0);
    }
    MutexUnlock(&ButtonCreationLock);
    return (PBUTTONHANDLE)Data[1];
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