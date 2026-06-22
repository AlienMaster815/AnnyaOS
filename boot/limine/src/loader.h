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
    LOADER_EXE_AND_MODULE_MEMORY,
    LOADER_FRAMEBUFFER_MEMORY,
    LOADER_RESERVED_MAPED_MEMORY, 
}LOADER_MEMORY_MAP_ATTRIBUTE;

typedef struct _RAT_TRACKER{
    UINTPTR             Base;
    SIZE                Limit;
}RAT_TRACKER, * PRAT_TRACKER;

typedef struct _LOADER_MEMORY_MAP{
    LOADER_MEMORY_MAP_ATTRIBUTE     Attributes;
    RAT_TRACKER                     Tracker;
}LOADER_MEMORY_MAP, * PLOADER_MEMORY_MAP;

typedef struct _LOADER_RAT_MBR_CHUNK{
    SIZE                Count; 
    SIZE                TrimSpace;
    RAT_TRACKER         Mbr[512];
    LOADER_MEMORY_MAP   Entires[];
}LOADER_RAT_MBR_CHUNK, * PLOADER_RAT_MBR_CHUNK;

typedef struct _LOADER_INFORMATION{
    KHANDLE                 LoaderHandle;
    PLOADER_RAT_MBR_CHUNK   RatMbr;
    LOADER_MEMORY_MAP       LimineKernel;
    LOADER_MEMORY_MAP       LouLoadCoff;
    LOADER_MEMORY_MAP       LousineCoff;
    SIZE                    LoadedModulesCount;
    PLOADER_MEMORY_MAP      LoadedModules;
    SIZE                    FrameBufferCount;
    PLOADER_MEMORY_MAP      FrameBuffers;
}LOADER_INFORMATION, * PLOADER_INFORMATION;

#endif