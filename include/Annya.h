#ifndef _ANNYA_API_H
#define _ANNYA_API_H

#define _USER_MODE_CODE_

//#include "USRSPC/API/WinAPItypes.h"
#include "kernel/SystemCalls.h"
#include <stdint.h>
#include <stdbool.h>
#include <USRSPC/UserThreads.h>

typedef char* string;


#ifdef __cplusplus
extern "C"{
#endif


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef void* PTHREAD;

#define LOU_EXPORT __declspec(dllexport)

#include <WinAPI/Win32/WinAPIStdType.h>
#include <FileHandleing/Bitmap.h>
#include <windows.h>

typedef void*    HWND;
typedef uint16_t MSG;




#ifndef _TIME_T_
#define _TIME_T_
typedef struct _TIME_T{
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint16_t MilliSeconds;
}TIME_T, * PTIME_T;
#endif

#ifndef _USER_32_

//__declspec(dllimport)
//uint64_t AnnyaRegisterCallbackProcedure(
//    void* CallbackHandler
//);

__declspec(dllimport)
void* malloc(size_t BytesNeeded);

__declspec(dllimport)
PBITMAP_HANDLE AnnyaOpenBitmapImage(
    string FileName
);

__declspec(dllimport)
void DrawDesktopBackground(FILE* FileHandle, uint16_t FileType);

__declspec(dllimport)
PBUTTONHANDLE AnnyaCreateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    uintptr_t Charecteristics
);

__declspec(dllimport)
void AnnyaChangeCanvasBufferColor(
    volatile PWINDHANDLE WindowHandle,
    uint16_t r,
    uint16_t g,
    uint16_t b,
    uint16_t a //not used yet but added for futrue proof
);

__declspec(dllimport)
volatile PWINDHANDLE AnnyaCreateCanvasBuffer(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    uintptr_t ParentWindow,
    PWINDOW_CHARECTERISTICS Charecteristics
);


#endif


#ifndef _LOUDLL_
__declspec(dllimport)
int LouPrint(char* Str, ...);

__declspec(dllimport)
uint16_t AnnyaGetScreenBufferWidth();

__declspec(dllimport)
uint16_t AnnyaGetScreenBufferHeight();

__declspec(dllimport)
PTHREAD AnnyaCreateThread(DWORD (*Function)(PVOID), PVOID FunctionParameters);

__declspec(dllimport)
void AnnyaDestroyThread(PTHREAD Thread);

__declspec(dllimport)
int _vsprintf(
    char* Buffer, 
    size_t BufferCount, 
    const string Format, 
    ...
);

__declspec(dllimport)
void GetRtcTimeData(TIME_T* PTIME);

__declspec(dllimport)
void AnnyaUpdateButton(
    uint16_t x, uint16_t y,
    uint16_t Width, uint16_t Height,
    PBUTTONHANDLE HBUTTON
);



#endif
#ifdef __cplusplus    
}
#endif

typedef void* HINSTANCE;


#endif
