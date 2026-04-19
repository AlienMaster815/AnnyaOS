#ifndef _XARRAY_H
#define _XARRAY_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _XARRAY_LOCK_TYPE{
    Mutex = 0,
    Spinlock,
    Semaphore,
}XARRAY_LOCK_TYPE, * PXARRAY_LOCK_TYPE;

#define XARRAY_FLAGS_MEMBER_POOL_USED   (1 << 0)
#define XARRAY_FLAGS_OBJECT_POOL_USED   (1 << 1)
#define XARRAY_FLAGS_MINIMAL_COUNT      (1 << 2)
#define XARRAY_FLAGS_MAXIMUM_COUNT      (1 << 3)
#define XARRAY_FLAGS_STATIC_ALLOCATED   (1 << 4)
#define XARRAY_FLAGS_STATIC_ALLOC1      (1 << 5)

#define XARRAY_METTADATA_IS_VALUE       (1ULL << 63)

typedef UINT64 XARRAY_FLAGS;

typedef struct _XARRAY_NODE{
    ListHeader      Peers;
    UINT64          Base;
    UINT64          Bitmap;
    UINT64          Entries[64];
}XARRAY_NODE, * PXARRAY_NODE;

typedef struct _XARRAY{
    XARRAY_LOCK_TYPE    LockType;
    LouKIRQL            IntermitenIrql;
    union{
        mutex_t         Mutex;
        spinlock_t      SpinLock;
        semaphore_t     Semaphore;        
    }Lock;    
    XARRAY_FLAGS        Flags;
    ListHeader          Nodes;    
}XARRAY, * PXARRAY;



#ifndef _USER_MODE_CODE_

#define LouKeXaDefineFlags(Name, Flags) \
XARRAY Name = { \
    .Flags = Flags \
};

#define LouKeXaDefine(Name) \
XARRAY Name;

#define LouKeXaDefineAlloc(Name) LouKeXaDefine(Name)

#define LouKeXaDefineAlloc1(Name) LouKeXaDefineFlags(Name, XARRAY_FLAGS_STATIC_ALLOC1)

static
inline 
void
LouKeXaInitFlags(
    PXARRAY Array, 
    XARRAY_FLAGS Flags
){
    memset(Array, 0, sizeof(XARRAY));
    Array->Flags = Flags;
}

static
inline 
void
LouKeXaInit(
    PXARRAY Array
){
    memset(Array, 0, sizeof(XARRAY));
}

static inline 
BOOLEAN 
LouKeXaEmpty(
    PXARRAY Array
){
    return (Array->Nodes.NextHeader ? false : true);   
} 

//TODO: put this in the kernel {

static inline void LouKeXaLockArray(PXARRAY Array){
    switch(Array->LockType){
        case Spinlock:
            LouKeAcquireSpinLock(&Array->Lock.SpinLock, &Array->IntermitenIrql);
            break;
        case Mutex:
            MutexLock(&Array->Lock.Mutex);
            break;
        case Semaphore: //TODO
            break;
        default:
            break;
    }
}
static inline void LouKeXaUnlockArray(PXARRAY Array){
    switch(Array->LockType){
        case Spinlock:
            LouKeReleaseSpinLock(&Array->Lock.SpinLock, &Array->IntermitenIrql);
            break;
        case Mutex:
            MutexUnlock(&Array->Lock.Mutex);
            break;
        case Semaphore: //TODO
            break;
        default:
            break;
    }
}

KERNEL_EXPORT
void 
LouKeXaFreeUint64(
    PXARRAY Array,
    UINT64  Id
);

KERNEL_EXPORT
void 
LouKeXaFreeUint32(
    PXARRAY Array,
    UINT32  Id
);

KERNEL_EXPORT 
void 
LouKeXaDestroy(
    PXARRAY Array
);

//}

KERNEL_EXPORT
PVOID 
LouKeXaStore(
    PXARRAY     Array,
    UINT64      Index,
    PVOID       Pointer,
    UINT64      PageFlags
);

KERNEL_EXPORT
BOOLEAN 
LouKeXaIsIndexUsed(
    PXARRAY     Array,
    UINT64      Index
);

KERNEL_EXPORT
BOOLEAN 
LouKeXaIsIndexUsedEx(
    PXARRAY     Array,
    UINT64      Index
);

KERNEL_EXPORT
PVOID 
LouKeXaStoreEx(
    PXARRAY     Array,
    UINT64      Index,
    PVOID       Pointer,
    UINT64      PageFlags
);

KERNEL_EXPORT
LOUSTATUS
LouKeXaGetEx(
    PXARRAY     Array,
    UINT64      Index,
    UINT64*     Out
);

KERNEL_EXPORT
LOUSTATUS
LouKeXaGet(
    PXARRAY     Array,
    UINT64      Index,
    UINT64*     Out
);

KERNEL_EXPORT 
LOUSTATUS 
LouKeXaIdrAllocate(
    PXARRAY     Array,
    PVOID       Pointer,
    int*        Start,
    int         End,
    UINT64      PageFlags 
);

KERNEL_EXPORT
LOUSTATUS 
LouKeXarrayAllocateUint64(
    PXARRAY Array,
    UINT64* Id,
    PVOID   Entry, 
    UINT64  Limit,
    UINT64  PageFlags
);

KERNEL_EXPORT
LOUSTATUS 
LouKeXarrayAllocateInt(
    PXARRAY Array,
    int*    Id,
    PVOID   Entry, 
    int     Limit,
    UINT64  PageFlags
);

KERNEL_EXPORT
LOUSTATUS 
LouKeXarrayAllocateUint32(
    PXARRAY Array,
    UINT32* Id,
    PVOID   Entry, 
    UINT32  Limit,
    UINT64  PageFlags
);

#else 

#endif
#ifdef __cplusplus
}
#endif
#endif