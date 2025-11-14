#ifndef _LOULOAD_H
#define _LOULOAD_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef __cplusplus

#define UNUSED __attribute__((unused))

#define ROUND_UP64(value, multiple) \
    (((value) + (multiple) - 1) / (multiple) * (multiple))

#endif

typedef uint8_t     UINT8, BYTE;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;

typedef bool BOOL;
typedef BYTE BOOLEAN;

typedef struct _LOUSINE_KERNEL_VM_TABLE{
    UINT8       KernelPml4;
    UINT8       KernelPml3;
    UINT8       KernelPml2;
    UINT8       KernelPml1;
    UINT64      PageCluster;
    UINT64      KernelVmBase;
    UINT64      KernelVmLimit;
}LOUSINE_KERNEL_VM_TABLE, * PLOUSINE_KERNEL_VM_TABLE;

typedef struct _LOUSINE_LOADER_INFO{
    UINT64                      KernelBase;
    UINT64                      KernelLimit;    
    UINT64                      MultibootInfo;
    UINT64                      BootStack;
    LOUSINE_KERNEL_VM_TABLE     KernelVm;
}LOUSINE_LOADER_INFO, * PLOUSINE_LOADER_INFO;



#endif