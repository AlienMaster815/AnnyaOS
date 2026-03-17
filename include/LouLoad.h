#ifndef _LOULOAD_H
#define _LOULOAD_H

#include <stdbool.h>
#include <stddef.h>
#include <cstdlib.h>



#ifdef __cplusplus
#define EXTERNAL extern "C"
extern "C" {
#else
#define EXTERNAL extern
#endif

#define NTAPI __stdcall //copied over from wines winnt.h see /AnnyaOS/include/WinAPI/Win32/winnt.h


typedef struct _LOUSINE_KERNEL_VM_TABLE{
    UINT8       KernelPml4;
    UINT8       KernelPml3;
    UINT8       KernelPml2;
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