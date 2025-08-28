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

typedef struct _CALLBACK_HEAD{
    ListHeader      Peers;
    void            (*Function)(struct _CALLBACK_HEAD* Head);
}CALLBACK_HEAD, * PCALLBACK_HEAD;

#ifndef XA_CHUNK_SIZE
#define XA_CHUNK_SHIFT 4
#define XA_CHUNK_SIZE  1 << XA_CHUNK_SHIFT
#endif

#define RADIX_TREE_MAP_SIZE (1 << XA_CHUNK_SHIFT)

#define XA_MAX_MARKS 3
#define XA_MAX_LONGS (XA_CHUNK_SIZE)

typedef struct FORCE_ALIGNMENT(sizeof(PVOID)) _XARRAY_NODE{
    UINT8                   Shift;
    UINT8                   Offset;
    UINT8                   Count;
    UINT8                   ValueCount;
    struct _XARRAY_NODE*    Parrent;
    PXARRAY                 Array;
    CALLBACK_HEAD           Callback;       
    PVOID                   Slots[XA_CHUNK_SIZE];
    union{
        UINT64              Tags[XA_MAX_MARKS][XA_MAX_LONGS];
        UINT64              Marks[XA_MAX_MARKS][XA_MAX_LONGS];
    };
}XARRAY_NODE, * PXARRAY_NODE;



#define INITIALIZE_XARRAY(Name, Flags){             \
    .XaLock = LouKeReleaseSpinLock(&Name, 0x00),    \
    .XaFlags = Flags,                               \
    .XaHead = 0x00,                                 \
}

typedef XARRAY RADIX_TREE_ROOT, * PRADIX_TREE_ROOT;
typedef XARRAY_NODE RADIX_TREE_NODE, * PRADIX_TREE_NODE;

#ifndef _KERNEL_MODULE_


#else 


#endif
#ifdef __cplusplus
}
#endif
#endif