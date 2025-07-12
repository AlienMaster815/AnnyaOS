#ifndef _EFI_STUBS_H
#define _EFI_STUBS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

#ifndef _EFI_TYPES
#define _EFI_TYPES
typedef unsigned long   EFI_STATUS;
typedef bool            EFI_BOOL;
typedef uint8_t         EFI_UINT8;
typedef uint16_t        EFI_UINT16;
typedef uint32_t        EFI_UINT32;
typedef uint64_t        EFI_UINT64;
typedef int8_t          EFI_INT8;
typedef int16_t         EFI_INT16;
typedef int32_t         EFI_INT32;
typedef int64_t         EFI_INT64;
typedef uintptr_t       EFI_PHYSICAL_ADDRESS;
typedef void*           EFI_HANDLE;
#endif

#include "Efi.h"

#ifndef EFI_ALLOCATION_ALGINMENT
#define EFI_ALLOCATION_ALGINMENT
#endif

#ifndef EFI_ALLOCATION_LIMIT
#define EFI_ALLOCATION_LIMIT UINT64_MAX
#endif

union _EFI_SYSTEM_TABLE;

EFI_STATUS EfiPeEntry(EFI_HANDLE Hanlde, union _EFI_SYSTEM_TABLE* SystemTableArgument);

#define EfiIsNative()                               (true)
#define EfiTableAttribute(Instance, Attribute)      (Instance)->Attribute
#define EfiFnCall(Instance, Function, ...)          (Instance)->Function(__VA_ARGS__)

#define EFI_CALL_PROTOTYPE(Instance, Function, ...)({           \
    __typeof__(Instance) __Instance = (Instance)                \
    EfiFnCall(__Instance, Function, __Instance, ##__VA_ARGS__); \
})



#ifdef __cplusplus
}
#endif
#endif
