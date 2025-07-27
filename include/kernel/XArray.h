#ifndef _XARRAY_H
#define _XARRAY_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

typedef struct _XARRAY{
    spinlock_t  XaLock;
    UINT64      XaFlags;
    PVOID       XaHead;
}XARRAY, * PXARRAY;

#define INITIALIZE_XARRAY(Name, Flags){             \
    .XaLock = LouKeReleaseSpinLock(&Name, 0x00),    \
    .XaFlags = Flags,                               \
    .XaHead = 0x00,                                 \
}

typedef XARRAY RADIX_TREE_ROOT;


#ifdef __cplusplus
}
#endif
#endif