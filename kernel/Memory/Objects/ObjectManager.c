#include "ObjectManager.h"

static OBJECT_POOL_TRACKER ObjPoolTrackerList = {0};
static mutex_t ObjPoolTrackerLock = {0};

UNUSED static PVOID AllocatePoolTracker(OBJECT_MANAGER_POOL_CLASS Class){
    POBJECT_POOL_TRACKER Tmp = &ObjPoolTrackerList;
    MutexLock(&ObjPoolTrackerLock);
    while(Tmp->Peers.NextHeader){
        Tmp = (POBJECT_POOL_TRACKER)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)LouKeMallocType(OBJECT_POOL_TRACKER, KERNEL_GENERIC_MEMORY);
    Tmp = (POBJECT_POOL_TRACKER)Tmp->Peers.NextHeader;
    Tmp->PoolClass = Class;
    MutexUnlock(&ObjPoolTrackerLock);
    return (PVOID)Tmp;
}

UNUSED static void FreePoolTracker(
    POBJECT_POOL_TRACKER Tracker
){
    POBJECT_POOL_TRACKER Tmp = &ObjPoolTrackerList;
    MutexLock(&ObjPoolTrackerLock);
    while(Tmp->Peers.NextHeader){
        if((PVOID)Tmp->Peers.NextHeader == (PVOID)Tracker){
            Tmp->Peers.NextHeader = ((POBJECT_POOL_TRACKER)Tmp->Peers.NextHeader)->Peers.NextHeader;
            LouKeFree(Tmp);
            MutexUnlock(&ObjPoolTrackerLock);
            return;
        }
        Tmp = (POBJECT_POOL_TRACKER)Tmp->Peers.NextHeader;
    }
    MutexUnlock(&ObjPoolTrackerLock);
}

LOUSTATUS 
LouKeAllocateObjectPoolTracker(
    OBJECT_MANAGER_POOL_CLASS   PoolClass,
    PVOID*                      Out
){

    if(!Out){   
        LouPrint("LouKeAllocateObjectPoolTracker() STATUS_INVALID_PARAMETER\n");
        LouPrint("Out Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }
    POBJECT_POOL_TRACKER NewTracker = AllocatePoolTracker(PoolClass);
    switch(PoolClass){

        case SESSION_CHAIN:
            NewTracker->Pool = LouKeCreateFixedPool(
                KILOBYTE_PAGE / sizeof(SESSION_OBJECT_CHAIN),
                sizeof(SESSION_OBJECT_CHAIN),
                GET_ALIGNMENT(SESSION_OBJECT_CHAIN),
                "SessionChainPool",
                0x00,
                KERNEL_GENERIC_MEMORY
            );
            break;

        case PROCESS_CHAIN:
            NewTracker->Pool = LouKeCreateFixedPool(
                KILOBYTE_PAGE / sizeof(PROCESS_OBJECT_CHAIN),
                sizeof(PROCESS_OBJECT_CHAIN),
                GET_ALIGNMENT(PROCESS_OBJECT_CHAIN),
                "SessionChainPool",
                0x00,
                KERNEL_GENERIC_MEMORY
            );
            break;

        case THREAD_CHAIN:
            NewTracker->Pool = LouKeCreateFixedPool(
                KILOBYTE_PAGE / sizeof(THREAD_OBJECT_CHAIN),
                sizeof(THREAD_OBJECT_CHAIN),
                GET_ALIGNMENT(THREAD_OBJECT_CHAIN),
                "SessionChainPool",
                0x00,
                KERNEL_GENERIC_MEMORY
            );
            break;

        default:
            LouPrint("LouKeAllocateObjectPoolTracker() STATUS_INVALID_PARAMETER\n");
            LouPrint("PoolClass Is Invalid\n");
            FreePoolTracker(NewTracker);
            return STATUS_INVALID_PARAMETER;
    }

    *Out = (PVOID)NewTracker;
    return STATUS_SUCCESS;
}

PVOID AllocateSessionTracker(){
    POBJECT_POOL_TRACKER Tmp = &ObjPoolTrackerList;
    PVOID Result = 0x00;
    while(Tmp->Peers.NextHeader){
        Tmp = (POBJECT_POOL_TRACKER)Tmp->Peers.NextHeader;
        if(Tmp->PoolClass == SESSION_CHAIN){
            Result = LouKeMallocFromFixedPool(Tmp->Pool);
            if(Result){
                return Result;
            }
        }
    }
    LOUSTATUS Status = LouKeAllocateObjectPoolTracker(SESSION_CHAIN, (PVOID*)&Tmp);
    if(Status != STATUS_SUCCESS){
        return 0x00;
    }
    return LouKeMallocFromFixedPool(Tmp->Pool);
}