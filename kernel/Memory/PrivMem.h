#ifndef _PRIVATE_MEM_H
#define _PRIVATE_MEM_H

#include <LouAPI.h>

typedef struct _FAST_ALLOCATION_TRACKER{
    ListHeader                      Peers;
    KERNEL_REFERENCE                KRef; 
    POOL                            AllocationPool;
}FAST_ALLOCATION_TRACKER, * PFAST_ALLOCATION_TRACKER;

typedef struct _FAST_ALLOCATION_TEMPLATE{
    ListHeader                      Peers;
    mutex_t                         TemplateLock;
    KERNEL_REFERENCE                KRef; 
    LOUSTR                          TrackingTag;
    FAST_ALLOCATION_TRACKER         PoolTrackers;
    mutex_t                         PoolTrackerLock;
    SIZE                            ObjectSize;
    SIZE                            ObjectCount;
    SIZE                            ObjectAlignment;
    SIZE                            Flags;
    SIZE                            PageFlags;
    mutex_t                         BuildLock;
    LOUSINE_OBJECT_CONSTRUCTOR      Constructor;
    LOUSINE_OBJECT_DECONSTRUCTOR    DeConstructor;
}FAST_ALLOCATION_TEMPLATE, * PFAST_ALLOCATION_TEMPLATE;



#endif