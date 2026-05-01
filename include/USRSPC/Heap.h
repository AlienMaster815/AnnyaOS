#ifndef _USER_HEAPS_H
#define _USER_HEAPS_H

#include <Ldm.h>

#define USER_HEAP_FLAG_GENERATE_EXCEPTIONS      (1 << 0)
#define USER_HEAP_FLAG_GROWABLE                 (1 << 1)
#define USER_HEAP_FLAG_NO_SERIALIZE             (1 << 2)

#define USER_HEAP_PARAM_LENGTH                  sizeof(USER_HEAP_PARAMETERS)
#define USER_HEAP_PARAM_SEGRES(x)               (x ? x : (2 * MEGABYTE_PAGE))
#define USER_HEAP_PARAM_SEGCOM(x)               (x ? x : (2 * MEGABYTE_PAGE))
#define USER_HEAP_PARAM_DECOM_FBT(x)            (x ? x : (MEGABYTE_PAGE))
#define USER_HEAP_PARAM_DECOM_TFT(x)            (x ? x : 0xFFFF)
#define USER_HEAP_PARAM_MAS(x, ReserveSize)     (x ? x : (ReserveSize - MEGABYTE_PAGE))    
#define USER_HEAP_PARAM_VMT(x, ReservedSize)    (((x < (ReserveSize - MEGABYTE_PAGE)) && x) ? x : 0x7F000)



#define USER_HEAP_RESERVE_ROUND_UP(Commit)  ROUND_UP64(Commit, MEGABYTE_PAGE * 16)

static inline LOUSTATUS LouUserHeapCalculateSize(
    SIZE* Reserve,
    SIZE* Commit
){
    if(!Reserve || !Commit){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE TmpReserve = *Reserve;
    SIZE TmpCommit = *Commit;

    if((TmpReserve) && (TmpCommit)){
        
        TmpCommit = MIN(TmpCommit, TmpReserve);
    
    }else if((TmpReserve) && (!TmpCommit)){
    
        TmpCommit = MEGABYTE_PAGE;
    
    }else if((TmpCommit) && (!TmpReserve)){
    
        TmpReserve = TmpCommit;
        TmpReserve = USER_HEAP_RESERVE_ROUND_UP(TmpReserve);
    
    }else{
    
        TmpReserve = 64 * MEGABYTE_PAGE;
        TmpCommit  = MEGABYTE_PAGE;
    
    }


    *Reserve = TmpReserve;
    *Commit = TmpCommit;
    return STATUS_SUCCESS;
}

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

typedef struct _USER_PROCESS_HEAP{
    PVOID                   HeapBase;
    SIZE                    ReserveSize;
    SIZE                    CommitSize;
    ULONG                   HeapFlags;
    USER_HEAP_PARAMETERS    HeapParametersCopy;
    ULONG                   ThreadID;
    ListHeader              ExtraSpaces;
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