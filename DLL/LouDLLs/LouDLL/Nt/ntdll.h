//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#ifndef NTDLL_H
#define NTDLL_H

#include "../LouDll.h"

#define NTDLL_API __declspec(dllexport)

#include <Annya.h>
#include <WinTEB.h>
#include <stdalign.h>

#define RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFORMATION     0x01000000
#define RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN             0x02000000
#define RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION    0x04000000
#define RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE            0x08000000
#define RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFORMATION  0x10000000
#define RTL_CRITICAL_SECTION_ALL_FLAG_MASK                 0xFF000000
#define RTL_CRITICAL_SECTION_FLAG_RESERVED_FLAGS           0xE0000000

#define RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION_DYNAMIC_SPIN (RTL_CRITICAL_SECTION_FLAG_STATIC_INITIALIZATION | RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN)


static inline void* __builtin_memcpy(void* Destination,void* Source, SIZE ByteCount){
    // Cast pointers to char* for byte-wise copying
    char* dest = (char*)Destination;
    const char* src = (const char*)Source;

    // Check if the source and destination overlap
    if (dest > src && dest < src + ByteCount) {
        // Copy backwards if there's overlap to prevent data corruption
        for (size_t i = ByteCount; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    } else {
        // Standard forward copy
        for (size_t i = 0; i < ByteCount; i++) {
            dest[i] = src[i];
        }
    }

    return Destination;
}

typedef struct _CSR_CAPTURE_BUFFER{
    ULONG                       Size;
    struct _CSR_CAPTURE_BUFFER* LastCaptureBuffer;
    ULONG                       PointerCount;
    uintptr_t                   BufferEnd;
    uintptr_t                   PointerArray[];
}CSR_CAPTURE_BUFFER, * PCSR_CAPTURE_BUFFER;

void* GetCsrPortHeap();
void* GetNtDllPointerHeap();
void* RtlAllocateHeap(
    PVOID       HeapHandle,
    uint64_t    HeapAllocationFlags,
    size_t      HeapSize
);
void 
LouDrsdClipToClip(
    struct _DRSD_CLIP* BackClip,
    struct _DRSD_CLIP* FrontClip,
    INT64 X,
    INT64 Y
);
void 
LouUpdateClipLocation(struct _DRSD_CLIP* Clip, INT64 DeltaX, INT64 DeltaY);
int strcmp(const char* str1, const char* str2);
void LouUpdateShadowClipSubState(
    void* Clip, 
    size_t X, size_t Y, 
    size_t Width, size_t Height
);
void LouYeildExecution();
void LouUpdateClipSubState(
    void* Clip,
    size_t X, size_t Y, 
    size_t Width, size_t Height
);
void 
LouUpdateShadowClipState(
    void* Clip
);
void LouGenericFreeHeap(void* Heap, void* Address);
void*
LouDrsdGetPlaneInformation(size_t* CountHandle);
LOUSTATUS
LouDrsdSetPlaneInformation(void* Context);
void*
LouGlobalUserMallocEx(size_t Size, uint64_t Alignment);
void LouGlobalUserFree(void* Addr);
#define LouGlobalUserMallocArray(type, count) (type*)LouGlobalUserMallocEx((ROUND_UP64(sizeof(type), GET_ALIGNMENT(type))) * (count), GET_ALIGNMENT(type))
#define LouGlobalUserMallocType(Type) (Type*)LouGlobalUserMallocEx(sizeof(Type), GET_ALIGNMENT(Type))
void*
LouGlobalUserMalloc(size_t Size);
void 
LouExitDosMode();
int strncmp(const char* str1, const char* str2, size_t n);
void
LouCloseFile(
    FILE* ClosingFile
);
void*
LouMemCpy(
    void* OutStream,
    void* InStream,
    size_t ByteCount
);
LOUSTATUS 
LouSwapEndianess(
    void* InStreamTmp, 
    void* OutStreamTmp, 
    size_t StreamSize
);
void* LouGenericAllocateHeapEx(
    void* Heap, 
    size_t AllocationSize,
    size_t Alginment
);
void* AnnyaGetLibraryFunctionN(string ModuleName,string FunctionName);
void* AnnyaGetLibraryFunctionH(HANDLE ModuleHandle, string FunctionName);
void* LouVirtualAllocUser(
    size_t      CommitSize,     //allocated PhysicalMemory
    size_t      ReservedSize,   //AllocatedVirtual
    uint64_t    PageFlags
);
FILE*
LouOpenFileA(
    string FileName
);
int LouPrint(char* Str, ...);
void 
LouDrsdSyncScreen();
void LouUpdateClipState(void* Clip);
void* LouDrsdCreateClip(
    INT64 X, INT64 Y, 
    INT64 Width, INT64 Height, 
    uint8_t R, uint8_t G, uint8_t B, uint8_t A
);
PTHREAD AnnyaCreateThread(DWORD (*Function)(PVOID), PVOID FunctionParameters);
void AnnyaDestroyThread(PTHREAD Thread);
int _vsprintf(
    char* Buffer, 
    size_t BufferCount, 
    const string Format, 
    ...
);
void GetRtcTimeData(TIME_T* PTIME);
void AnnyaUpdateButton(
    int64_t x, int64_t y,
    uint32_t Width, uint32_t Height,
    PVOID HBUTTON
);
void LouTrashAndDumpProcess();
void* LouGenericAllocateHeapEx(void* Heap, size_t AllocationSize, size_t Alignment);


#endif