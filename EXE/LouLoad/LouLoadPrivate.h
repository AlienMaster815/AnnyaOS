#define _LOUSINE_LOADER

#ifndef LOUSINE_LOADER_PRIVATE_H
#define LOUSINE_LOADER_PRIVATE_H

#include <LouLoad.h>
#include <Coff.h>

#define LOADER_CPU_FEATURES_GB_PAGES    1ULL
#define LOADER_CPU_FEATURES_NX          (1ULL << 1)


typedef enum {
    LOADER_USABLE_MEMORY = 0,
    LOADER_RESERVED_MEMORY,
    LOADER_ACPI_RECLAIM_MEMORY,
    LOADER_ACPI_NVS_MEMORY,
    LOADER_BAD_MEMORY,
    LOADER_RECLAIMABLE_MEMORY,
    LOADER_MODULE_MEMORY,
    LOADER_FRAMEBUFFER_MEMORY,
    LOADER_RESERVED_MAPED_MEMORY, 
    LOADER_ANY_ATTRIBUTE_MEMORY, 
}LOADER_MEMORY_MAP_ATTRIBUTE;

typedef struct _RAT_TRACKER{
    UINTPTR             Base;
    SIZE                Length;
}RAT_TRACKER, * PRAT_TRACKER;

typedef struct _RAT_FB_TRACKER{
    UINTPTR             Base;
    SIZE                Width;
    SIZE                Height;
    SIZE                Bpp;
    SIZE                Pitch;
}RAT_FB_TRACKER, * PRAT_FB_TRACKER;

typedef struct _LOADER_MEMORY_MAP{
    LOADER_MEMORY_MAP_ATTRIBUTE     Attributes;
    RAT_TRACKER                     Tracker;
}LOADER_MEMORY_MAP, * PLOADER_MEMORY_MAP;

typedef struct _LOADER_FB_MEMORY_MAP{
    LOADER_MEMORY_MAP_ATTRIBUTE     Attributes;
    RAT_FB_TRACKER                  Tracker;
}LOADER_FB_MEMORY_MAP, * PLOADER_FB_MEMORY_MAP;

typedef struct _LOADER_RAT_MBR_CHUNK{
    SIZE                Count; 
    SIZE                ChunkSize;
    SIZE                MbrChunksAllocated;
    SIZE                ChunkAllocatorIndexor[100];
    RAT_TRACKER         Mbr[100];
    LOADER_MEMORY_MAP   Entries[];
}LOADER_RAT_MBR_CHUNK, * PLOADER_RAT_MBR_CHUNK;

typedef struct _LOADER_INFORMATION{
    UINT64                  LoaderCpuFeatures;
    UINT64                  TscCount;
    SIZE                    RamSize;
    KHANDLE                 StackHandle;
    KHANDLE                 EfiSystemTable;
    KHANDLE                 LoaderHandle;
    KHANDLE                 KernelHandle;
    PLOADER_RAT_MBR_CHUNK   RatMbr;
    LOADER_MEMORY_MAP       LouLoadCoff;
    LOADER_MEMORY_MAP       LousineCoff;
    SIZE                    LoadedModulesCount;
    PLOADER_MEMORY_MAP      LoadedModules;
    SIZE                    FrameBufferCount;
    PLOADER_FB_MEMORY_MAP   FrameBuffers;
    SIZE                    BootModulesCount;
    PLOADER_MEMORY_MAP      BootModulesBase;
}LOADER_INFORMATION, * PLOADER_INFORMATION;

#include <stdalign.h>

#define KSpaceBase 0xFFFF800000000000

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define KILOBYTE        (1      * 1024ULL)
#define MEGABYTE        (1024   * KILOBYTE)
#define GIGABYTE        (1024   * MEGABYTE)
#define MEGABYTE_PAGE   (2 * MEGABYTE)
#define KILOBYTE_PAGE   (4 * KILOBYTE)

#define GetStructureSize(type, member, count) \
    ((size_t)((uintptr_t)(&((type*)0x00)->member[count])))

static inline void LouKeReloadCR3(){
    uint64_t cr3;
    asm volatile ("mov %%cr3, %0" : "=r"(cr3));
    asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

PVOID memcpy(PVOID Dest, PCVOID Src, SIZE Size);
PVOID memset(PVOID Dest, int Val, SIZE Size);
PVOID memmove(PVOID Dest, PCVOID Src, SIZE Size);

PVOID LoaderGetPhysicalAddress(PVOID Address);
UINT64* GetPageBase();
UINT64 GetCr3();
BOOLEAN LoaderInitializeMemoryManager(PLOADER_INFORMATION Info);
BOOLEAN LoaderInitializeKernelSpace(PLOADER_INFORMATION Info);

void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx);
void cpuid_subleaf(unsigned int leaf, unsigned int subleaf, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx);
void LoaderGetCpuFeatures(PLOADER_INFORMATION Info);



#endif