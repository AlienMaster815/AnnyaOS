#ifndef _LAZY_ALLOCATIONS_H
#define _LAZY_ALLOCATIONS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef struct _LAZY_ALLOCATION_TRACKER{
    ListHeader                  Peers;
    PVOID                       VirtualLocation;
    SIZE                        VirtualSize;
    SIZE                        PageSize;
    PVOID*                      PhysicalMappings;
    UINT64                      PageFlags;
    struct _LMPOOL_DIRECTORY*   DynamicAllocations;
}LAZY_ALLOCATION_TRACKER, * PLAZY_ALLOCATION_TRACKER;


#ifndef _KERNEL_MODULE_

PLAZY_ALLOCATION_TRACKER 
LouKeAllocateLazyBuffer(
    PVOID VirtualLocation, 
    SIZE VirtualSize, 
    UINT64 PageFlags
);

BOOL 
LouKePageFaultIsDueToLazyBuffer(
    PVOID Location
);

PVOID 
LouKeMallocFromLazyBufferEx(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    SIZE                        Size,
    SIZE                        Alignment
);

PVOID 
LouKeMallocFromLazyBuffer(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    SIZE                        Size
);

#else


#endif

#ifdef __cplusplus
}
#endif
#endif