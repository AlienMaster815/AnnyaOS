#include "MSVCRT.h"

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


__declspec(dllimport)
void LouGenericFreeHeap(void* Heap, void* Address);

__declspec(dllimport)
void* GetProcessHeap();

int* _errno();

#define HEAP_NO_SERIALIZE               0x00000001
#define HEAP_GROWABLE                   0x00000002
#define HEAP_GENERATE_EXCEPTIONS        0x00000004
#define HEAP_ZERO_MEMORY                0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY      0x00000010
#define HEAP_TAIL_CHECKING_ENABLED      0x00000020
#define HEAP_FREE_CHECKING_ENABLED      0x00000040
#define HEAP_DISABLE_COALESCE_ON_FREE   0x00000080
#define HEAP_CREATE_ALIGN_16            0x00010000
#define HEAP_CREATE_ENABLE_TRACING      0x00020000
#define HEAP_CREATE_ENABLE_EXECUTE      0x00040000

//BUGBUG : Theres an issue with the Msvc Heap

static HANDLE MsvcHeap = 0;
static HANDLE MsvcSbHeap = 0;

MSVCRT_API
void InitializeMsvcrtHeap(){
    MsvcHeap = LouVirtualAllocUser(
        KILOBYTE_PAGE,
        MEGABYTE_PAGE,
        USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
    );
    MsvcSbHeap = LouVirtualAllocUser(
        KILOBYTE_PAGE,
        MEGABYTE_PAGE,
        USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
    );
}


MSVCRT_API
void* calloc(size_t Count, size_t size){
    size_t Bytes = Count * size;
    if (size && ((Bytes / size) != Count))
    {
      *_errno() = ENOMEM;
      return 0x00;
    }
    void* Result = LouGenericAllocateHeapEx(MsvcHeap, Bytes, Bytes);
    for(size_t i = 0 ; i < Bytes; i++){
        *(uint8_t*)((uint64_t)Result + i) = 0;    
    }
    return Result;
}

MSVCRT_API
void* malloc(size_t BytesNeeded){
    return LouGenericAllocateHeapEx(
        GetProcessHeap(), 
        BytesNeeded,
        GetAlignmentBySize(BytesNeeded)
    );
}

MSVCRT_API
void free(void* Address){
    LouGenericFreeHeap(
        GetProcessHeap(),
        Address
    );
}