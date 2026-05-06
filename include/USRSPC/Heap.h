#ifndef _USER_HEAPS_H
#define _USER_HEAPS_H

#include <Ldm.h>

#define USER_HEAP_FLAG_GENERATE_EXCEPTIONS      (1 << 0)
#define USER_HEAP_FLAG_GROWABLE                 (1 << 1)
#define USER_HEAP_FLAG_NO_SERIALIZE             (1 << 2)
#define USER_HEAP_FLAG_ZERO_MEMORY              (1 << 3)

#define USER_HEAP_PARAM_LENGTH                  sizeof(USER_HEAP_PARAMETERS)
#define USER_HEAP_PARAM_SEGRES(x)               (x ? x : (2 * MEGABYTE_PAGE))
#define USER_HEAP_PARAM_SEGCOM(x)               (x ? x : (2 * MEGABYTE_PAGE))
#define USER_HEAP_PARAM_DECOM_FBT(x)            (x ? x : (MEGABYTE_PAGE))
#define USER_HEAP_PARAM_DECOM_TFT(x)            (x ? x : 0xFFFF)
#define USER_HEAP_PARAM_MAS(x, ReserveSize)     (x ? x : (ReserveSize - MEGABYTE_PAGE))    
#define USER_HEAP_PARAM_VMT(x, ReservedSize)    (((x < (ReserveSize - MEGABYTE_PAGE)) && x) ? x : 0x7F000)



#define USER_HEAP_RESERVE_ROUND_UP(Commit)  ROUND_UP64(Commit, MEGABYTE_PAGE * 16)

typedef LOUSTATUS (*USER_HEAP_COMMIT_ROUTINE)(
    PVOID   Base,
    PVOID*  CommitAddress,
    SIZE*   CommitSize
);

typedef struct _USER_HEAP_PARAMETERS{
    ULONG                       Length;
    SIZE                        SegmentReserve;
    SIZE                        SegmentCommit;
    SIZE                        DeCommitFreeBlockThreshold;
    SIZE                        DeCommitTotalFreeThreshold;
    SIZE                        MaximumAllocationSize;
    SIZE                        VirtualMemoryThreshold;
    SIZE                        InitialCommit;
    SIZE                        InitialReserve;
    USER_HEAP_COMMIT_ROUTINE    CommitRoutine;
    SIZE                        Reserved[2];
}USER_HEAP_PARAMETERS, * PUSER_HEAP_PARAMETERS,
    RTL_HEAP_PARAMETERS, RTL_HEAP_PARAMETERS;

typedef struct _USER_HEAP_ALLOCATION_TRACKER{
    ListHeader      Peers;
    UINT64          Base;
    UINT64          Size;
}USER_HEAP_ALLOCATION_TRACKER, * PUSER_HEAP_ALLOCATION_TRACKER;

typedef struct _USER_PROCESS_HEAP{
    mutex_t                 HeapLock;
    PVOID                   HeapBase;
    SIZE                    ReservedSize;
    SIZE                    CommitSize;
    ULONG                   HeapFlags;
    USER_HEAP_PARAMETERS    HeapParametersCopy;
    ULONG                   ThreadID;
    ListHeader              ExtraSpaces;
    ListHeader              Allocations;
}USER_PROCESS_HEAP, * PUSER_PROCESS_HEAP;

#ifdef  _USER_MODE_CODE_
#ifndef _LOUDLL_

ANNA_IMPORT
PUSER_PROCESS_HEAP
LouRtlCreateHeap(
    ULONG                   Flags,
    PVOID                   HeapBase,
    SIZE                    ReservedSize,
    SIZE                    CommitSize,
    PERESOURCE_OBJECT       ResourceLock,
    PUSER_HEAP_PARAMETERS   Parameters
);

ANNA_IMPORT
PVOID
LouRtlAllocateHeapEx(
    PUSER_PROCESS_HEAP  Heap,
    SIZE                Size,
    SIZE                Alignment,
    ULONG               Flags
);

ANNA_IMPORT
PVOID
LouRtlAllocateHeap(
    PUSER_PROCESS_HEAP  Heap,
    SIZE                Size,
    ULONG               Flags
);

ANNA_IMPORT
LOGICAL
LouRtlFreeHeap(
    PUSER_PROCESS_HEAP  Heap,
    PVOID               Address,
    ULONG               Flags
);

#else //_LOUDLL_

ANNA_EXPORT
PUSER_PROCESS_HEAP
LouRtlCreateHeap(
    ULONG                   Flags,
    PVOID                   HeapBase,
    SIZE                    ReservedSize,
    SIZE                    CommitSize,
    PERESOURCE_OBJECT       ResourceLock,
    PUSER_HEAP_PARAMETERS   Parameters
);

#endif
#endif//_USER_MODE_CODE_
#endif