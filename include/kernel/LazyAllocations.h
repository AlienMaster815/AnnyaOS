#ifndef _LAZY_ALLOCATIONS_H
#define _LAZY_ALLOCATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LAZY_ALLOCATION_TRACKER{
    ListHeader                  Peers;
    PVOID                       VirtualLocation;
    SIZE                        VirtualSize;
    SIZE                        PageSize;
    SIZE                        PhyMappingCount;
    PVOID*                      PhysicalMappings;
    UINT64                      PageFlags;
    struct _LMPOOL_DIRECTORY*   DynamicAllocations;
}LAZY_ALLOCATION_TRACKER, * PLAZY_ALLOCATION_TRACKER;


#ifndef _USER_MODE_CODE_
#ifndef _KERNEL_MODULE_

PLAZY_ALLOCATION_TRACKER 
LouKeAllocateLazyBuffer(
    PVOID VirtualLocation, 
    SIZE VirtualSize, 
    SIZE CommitSize,
    UINT64 PageFlags
);

void 
LouKeFreeLazyBuffer(
    PLAZY_ALLOCATION_TRACKER Tracker
);

BOOL 
LouKePageFaultIsDueToLazyBuffer(
    PVOID Location,
    PLAZY_ALLOCATION_TRACKER* Out
);

LOUSTATUS 
LouKeLazyBufferCommitPage(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    PVOID                       Address, //Optional
    SIZE                        Count    //Optional
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

void LouKeFreeFromLazyBuffer(
    PLAZY_ALLOCATION_TRACKER    LazyBuffer,
    PVOID                       Address
);

#endif
#endif
#ifdef __cplusplus
}
#endif
#endif