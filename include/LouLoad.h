#ifndef _LOULOAD_H
#define _LOULOAD_H

#include <stdbool.h>
#include <stddef.h>
#include <cstdlib.h>

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


#ifdef __cplusplus
#define EXTERNAL extern "C"
extern "C" {
#else
#define EXTERNAL extern
#endif

#define NTAPI __stdcall //copied over from wines winnt.h see /AnnyaOS/include/WinAPI/Win32/winnt.h


typedef struct _LOUSINE_KERNEL_VM_TABLE{
    UINT16      KernelPml4;
    UINT16      KernelPml3;
    UINT16      KernelPml2;
    UINT64      LargePageClusters;
    UINT64      vLargePageClusters;
    UINT64      KernelVmBase;
    UINT64      KernelVmLimit;
}LOUSINE_KERNEL_VM_TABLE, * PLOUSINE_KERNEL_VM_TABLE;

typedef struct _LOUSINE_RAT_PARTITION{
    UINT64      RamMap;
    UINT64      BootPartition;
    UINT16      PartitionItems;
}LOUSINE_RAT_PARTITION, * PLOUSINE_RAT_PARTITION;

typedef struct _LOULOAD_MEMORY_TRACKER{
    UINT64 Address;
    UINT64 size;
}LOULOAD_MEMORY_TRACKER, * PLOULOAD_MEMORY_TRACKER;

typedef struct _LOUSINE_FIRWARE_INFO{
    UINT64 EfiTable;
    UINT64 Smbios;
    UINT64 Rsdp;
    UINT64 Rsdp2;
    UINT64 Vbe;
    UINT64 Apm;
    UINT64 Framebuffer;
    UINT64 EfiMap;
}LOUSINE_FIRWARE_INFO, * PLOUSINE_FIRWARE_INFO;

typedef struct _LOUSINE_LOADER_INFO{
    UINT64                      KernelBase;
    UINT64                      KernelLimit;    
    UINT64                      MultibootInfo;
    UINT64                      BootStack;
    UINT64                      KernelTag;
    UINT64                      RegistryTag;
    LOUSINE_KERNEL_VM_TABLE     KernelVm;
    LOUSINE_RAT_PARTITION       RatPartition;
    LOUSINE_FIRWARE_INFO        FirmwareInfo;
    PVOID                       KernelExportTable;
    PVOID                       KernelImportTable;
}LOUSINE_LOADER_INFO, * PLOUSINE_LOADER_INFO;

#ifndef KERNEL_MAIN_FILE
EXTERNAL LOUSINE_LOADER_INFO KernelLoaderInfo;
#endif

#define GetKSpaceBase() KernelLoaderInfo.KernelVm.KernelVmBase
#define GetBootStackTop() KernelLoaderInfo.BootStack
#define SetKSpaceBase(x) KernelLoaderInfo.KernelVm.KernelVmBase = x



#ifdef __cplusplus
}
#endif
#endif