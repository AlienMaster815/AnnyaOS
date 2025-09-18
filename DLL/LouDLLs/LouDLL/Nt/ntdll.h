#ifndef NTDLL_H
#define NTDLL_H

#include "../LouDll.h"

#define NTDLL_API __declspec(dllexport)

#include <Annya.h>
#include <WinTEB.h>
#include <stdalign.h>
#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define KILOBYTE_PAGE 4096ULL
#define MEGABYTE_PAGE (2 * 1024 * 1024ULL)
#define KILOBYTE (1 * 1024ULL)

#define PRESENT_PAGE           0b1
#define WRITEABLE_PAGE        0b10

#define USER_PAGE           (1 << 2)

#define WRITE_THROUGH_PAGE  0b1000
#define CACHE_DISABLED_PAGE 0b10000
#define UNCACHEABLE_PAGE    0b10000

#define PAGE_PRESENT        (1 << 0)
#define PAGE_WRITE          (1 << 1)
#define PAGE_USER           (1 << 2)
#define PAGE_PWT            (1 << 3)
#define PAGE_PCD            (1 << 4)
#define END_PAGE            (1 << 4)

#define KERNEL_GENERIC_MEMORY   WRITEABLE_PAGE | PRESENT_PAGE
#define KERNEL_DMA_MEMORY       UNCACHEABLE_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_GENERIC_MEMORY     USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
#define USER_DMA_MEMORY         USER_PAGE | WRITEABLE_PAGE |PRESENT_PAGE
#define USER_RO_DMA_MEMORY      UNCACHEABLE_PAGE | USER_PAGE | PRESENT_PAGE
#define USER_RO_GENERIC_MEMORY  USER_PAGE | PRESENT_PAGE
 
// Constants for gigabyte and megabyte sizes
#define GIGABYTE (1ULL << 30)  // 1 GB in bytes
#define MEGABYTE (1ULL << 20)  // 1 MB in bytes
#define KILOBYTE (1 * 1024ULL)

#define MAX_LONG  0x7FFFFFFF  // 2147483647 in decimal

typedef long long unsigned int U64;
typedef unsigned long ULONG; 

static inline void* __builtin_memcpy(void* Destination,void* Source, U64 ByteCount){
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
void LouGetSystemUpdate(PSYSTEM_STATE_STACK StateStack);
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
    PBUTTONHANDLE HBUTTON
);
void LouTrashAndDumpProcess();
void* LouGenericAllocateHeapEx(void* Heap, size_t AllocationSize, size_t Alignment);


#endif