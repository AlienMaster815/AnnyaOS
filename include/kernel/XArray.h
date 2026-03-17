#ifndef _XARRAY_H
#define _XARRAY_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _XARRAY_LOCK_TYPE{
    NoLock = 0,
    Spinlock,
    Mutex,
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

typedef struct _XARRAY_ENTRY{
    ListHeader          Peers;
    struct _XARRAY*     Parrent;
    BOOLEAN             Marked;
    PVOID               Data;
}XARRAY_ENTRY, * PXARRAY_ENTRY;

typedef struct _XARRAY{
    XARRAY_LOCK_TYPE    LockType;
    LouKIRQL            IntermitenIrql;
    union{
        mutex_t         Mutex;
        spinlock_t      SpinLock;
        semaphore_t     Semaphore;        
    }Lock;    
    XARRAY_FLAGS        Flags;
    atomic_t            MemberCount;
    SIZE                MinimalCount;
    POOL                ArrayPool;
    POOL                MemberPool;
    PXARRAY_ENTRY       Array;    
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
    if(Array->Flags & XARRAY_FLAGS_STATIC_ALLOCATED){
        int Members = LouKeGetAtomic(&Array->MemberCount);
        for(int i = 0; i < Members; i++){
            if(Array->Array[i].Data){
                return false;
            }
        }
        return true;
    }else{
        return (Array->Array->Peers.NextHeader ? false : true);
    }   
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


static inline 
void 
LouKeXaDestroy(
    PXARRAY Array
){  
    LouKeXaLockArray(Array);
    if(Array->Flags & XARRAY_FLAGS_STATIC_ALLOCATED){
        int Members = LouKeGetAtomic(&Array->MemberCount);
        for(int i = 0 ; i < Members; i++){
            LouKeFree(Array->Array[i].Data);
        }
        LouKeFree(Array->Array);
        Array->Array = 0x00;
    }else{
        PXARRAY_ENTRY Leader = Array->Array;
        PXARRAY_ENTRY Follower;
        while(Leader){
            Follower = Leader;
            Leader = (PXARRAY_ENTRY)Leader->Peers.NextHeader;
            LouKeFree(Follower->Data);
            LouKeFree(Follower);
        }         
        Array->Array = 0x00;
    }
    LouKeXaUnlockArray(Array);
}

//}

#else 

#endif
#ifdef __cplusplus
}
#endif
#endif