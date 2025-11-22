#ifndef _LOULOAD_H
#define _LOULOAD_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef __cplusplus

#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#define ROUND_DOWN64(value, multiple) \
    ((value) / (multiple) * (multiple))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif

#define NTAPI __stdcall //copied over from wines winnt.h see /AnnyaOS/include/WinAPI/Win32/winnt.h


typedef void* PVOID;
typedef unsigned short USHORT;
typedef wchar_t*       LPWSTR;

typedef char        CHAR;
typedef uint8_t     UINT8, BYTE;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;

typedef uintptr_t   UINTPTR;

typedef bool BOOL;
typedef BYTE BOOLEAN;

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
}LOUSINE_LOADER_INFO, * PLOUSINE_LOADER_INFO;

#define GetKSpaceBase() KernelLoaderInfo.KernelVm.KernelVmBase
#define SetKSpaceBase(x) KernelLoaderInfo.KernelVm.KernelVmBase = x


#endif