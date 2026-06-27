#ifndef _LOUSINE_LOADER_H
#define _LOUSINE_LOADER_H

#include "cstdint.h"

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
    UINT64                  RsdpPointer;
    UINT64                  RsdpVersion;
    UINT64                  LoaderCpuFeatures;
    UINT64                  TscCount;
    SIZE                    RamSize;
    KHANDLE                 StackHandle;
    KHANDLE                 KernelStackHandle;
    KHANDLE                 EfiSystemTable;
    KHANDLE                 LoaderHandle;
    KHANDLE                 KernelHandle;
    PLOADER_RAT_MBR_CHUNK   RatMbr;
    PLOADER_MEMORY_MAP      LouLoadCoff;
    PLOADER_MEMORY_MAP      LousineCoff;
    SIZE                    LoadedModulesCount;
    PLOADER_MEMORY_MAP      LoadedModules;
    SIZE                    FrameBufferCount;
    PLOADER_FB_MEMORY_MAP   FrameBuffers;
    SIZE                    BootModulesCount;
    PLOADER_MEMORY_MAP      BootModulesBase;
}LOADER_INFORMATION, * PLOADER_INFORMATION;

#define KSpaceBase 0xFFFF800000000000

#include <stdalign.h>

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define GET_ALIGNMENT(x) (alignof(x))
#define FORCE_ALIGNMENT(alignment) __attribute__((aligned(alignment)))

#define KILOBYTE        (1      * 1024ULL)
#define MEGABYTE        (1024   * KILOBYTE)
#define GIGABYTE        (1024   * MEGABYTE)
#define MEGABYTE_PAGE   (2 * MEGABYTE)

#define GetStructureSize(type, member, count) \
    ((size_t)((uintptr_t)(&((type*)0x00)->member[count])))

static inline void LouKeReloadCR3() {
    uint64_t cr3;
    asm volatile ("mov %%cr3, %0" : "=r"(cr3));
    asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

UINT64 GetCr3();
UINT64* GetPageBase();
PVOID LimineGetVirtualAddress(PVOID Address);
PVOID LimineGetPhysicalAddress(PVOID Address);
PLOADER_RAT_MBR_CHUNK LoaderSetUpRatMbr();
BOOLEAN LoaderInitializeLoaderInformation(PLOADER_INFORMATION Info);
BOOLEAN InitializeRatSubsystem(PLOADER_INFORMATION Info);
PVOID LoaderAllocateSpace(SIZE AllocationSize, SIZE Alignment);
PVOID LouKeRatAllocatePhysicalAddress(SIZE Size, SIZE Alignment);

#include "Coff.h"
#include "../../../include/Debug.h"

#endif