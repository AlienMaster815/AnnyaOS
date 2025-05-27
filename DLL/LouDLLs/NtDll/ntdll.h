#ifndef NTDLL_H
#define NTDLL_H

#define NTDLL_API __declspec(dllexport)

#include <Annya.h>
#include <WinTEB.h>
#include <stdalign.h>
#define GET_ALIGNMENT(x) (alignof(x))


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

#endif