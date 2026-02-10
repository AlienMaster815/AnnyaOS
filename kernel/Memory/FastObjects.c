#include "PrivMem.h"

static FAST_ALLOCATION_TEMPLATE FastAllocationTemplateList = {0};
static mutex_t FastAllocationTemplateLock = {0};

static bool CheckTemplatesForDuplicate(LOUSTR ClassName){
    PFAST_ALLOCATION_TEMPLATE TmpTemplate = &FastAllocationTemplateList;
    MutexLock(&FastAllocationTemplateLock);
    while(TmpTemplate->Peers.NextHeader){
        TmpTemplate = (PFAST_ALLOCATION_TEMPLATE)TmpTemplate->Peers.NextHeader;
        if(!strcmp(TmpTemplate->TrackingTag, ClassName)){
            MutexUnlock(&FastAllocationTemplateLock);
            return true;
        }
    }
    MutexUnlock(&FastAllocationTemplateLock);
    return false;
}

static PFAST_ALLOCATION_TEMPLATE AllocateFastObjectClassTemplate(
    LOUSTR                          ClassName,
    SIZE                            ObjectCount,
    SIZE                            ObjectSize,
    SIZE                            ObjectAlignment,
    SIZE                            Flags,
    SIZE                            PageFlags,
    LOUSINE_OBJECT_CONSTRUCTOR      Constructor,
    LOUSINE_OBJECT_DECONSTRUCTOR    DeConstructor
){
    PFAST_ALLOCATION_TEMPLATE TmpTemplate = &FastAllocationTemplateList;
    MutexLock(&FastAllocationTemplateLock);
    while(TmpTemplate->Peers.NextHeader){
        TmpTemplate = (PFAST_ALLOCATION_TEMPLATE)TmpTemplate->Peers.NextHeader;
    }

    TmpTemplate->Peers.NextHeader = (PListHeader)LouKeMallocType(FAST_ALLOCATION_TEMPLATE, KERNEL_GENERIC_MEMORY);
    TmpTemplate = (PFAST_ALLOCATION_TEMPLATE)TmpTemplate->Peers.NextHeader;
    TmpTemplate->TrackingTag = LouKeMallocArray(CHAR, strlen(ClassName) + 1, KERNEL_GENERIC_MEMORY);
    strcpy(TmpTemplate->TrackingTag, ClassName);
    TmpTemplate->ObjectSize = ObjectSize;
    TmpTemplate->ObjectCount = ObjectCount;
    TmpTemplate->ObjectAlignment = ObjectAlignment;
    TmpTemplate->Flags = Flags;
    TmpTemplate->PageFlags = PageFlags;
    TmpTemplate->Constructor = Constructor;
    TmpTemplate->DeConstructor = DeConstructor;

    MutexUnlock(&FastAllocationTemplateLock);
    return TmpTemplate;
} 

static PFAST_ALLOCATION_TEMPLATE AcquireFastObjectTemplate(LOUSTR ClassName){
    PFAST_ALLOCATION_TEMPLATE TmpTemplate = &FastAllocationTemplateList;
    MutexLock(&FastAllocationTemplateLock);
    while(TmpTemplate->Peers.NextHeader){
        TmpTemplate = (PFAST_ALLOCATION_TEMPLATE)TmpTemplate->Peers.NextHeader;
        if(!strcmp(TmpTemplate->TrackingTag, ClassName)){
            MutexUnlock(&FastAllocationTemplateLock);
            MutexLock(&TmpTemplate->TemplateLock);
            return TmpTemplate;
        }
    }
    MutexUnlock(&FastAllocationTemplateLock);
    return 0x00;
}

static void ReleaseFastObjectTemplate(PFAST_ALLOCATION_TEMPLATE Template){
    MutexUnlock(&Template->TemplateLock);
}

static PFAST_ALLOCATION_TRACKER AllocatePoolTracker(PFAST_ALLOCATION_TEMPLATE Template){
    PFAST_ALLOCATION_TRACKER NewTracker = &Template->PoolTrackers;
    PFAST_ALLOCATION_TRACKER Follower = &Template->PoolTrackers;
    MutexLock(&Template->PoolTrackerLock);
    while(NewTracker->Peers.NextHeader){
        Follower = NewTracker;
        NewTracker = (PFAST_ALLOCATION_TRACKER)NewTracker->Peers.NextHeader;
    }

    NewTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(FAST_ALLOCATION_TRACKER, KERNEL_GENERIC_MEMORY);
    NewTracker = (PFAST_ALLOCATION_TRACKER)NewTracker->Peers.NextHeader;
    NewTracker->AllocationPool = LouKeCreateFixedPool(
        Template->ObjectCount,
        Template->ObjectSize,
        Template->ObjectAlignment,
        Template->TrackingTag,
        Template->Flags,
        Template->PageFlags
    );    
    
    if(!NewTracker->AllocationPool){
        LouKeFree(NewTracker);
        Follower->Peers.NextHeader = 0x00;
        MutexUnlock(&Template->PoolTrackerLock);
    }

    MutexUnlock(&Template->PoolTrackerLock);
    return NewTracker;
}

static void FreePoolTracker(PFAST_ALLOCATION_TEMPLATE Template, PFAST_ALLOCATION_TRACKER Tracker){

    PFAST_ALLOCATION_TRACKER TmpTracker = &Template->PoolTrackers;
    while((TmpTracker) && ((PFAST_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader != Tracker)){
        TmpTracker = (PFAST_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
    }

    if(!TmpTracker){
        goto _FINISH_CLEANUP;
    }

    TmpTracker->Peers.NextHeader = Tracker->Peers.NextHeader;

    _FINISH_CLEANUP:
    LouKeDestroyFixedPool(Tracker->AllocationPool);
}

LOUSTATUS LouKeCreateFastObjectClassEx(
    LOUSTR                          ClassName,
    SIZE                            ObjectCount,
    SIZE                            ObjectSize,
    SIZE                            ObjectAlignment,
    SIZE                            Flags,
    SIZE                            PageFlags,
    LOUSINE_OBJECT_CONSTRUCTOR      Constructor,
    LOUSINE_OBJECT_DECONSTRUCTOR    DeConstructor
){
  
    if(CheckTemplatesForDuplicate(ClassName)){
        LouPrint("LouKeCreateFastObjectClass() ERESOURCE_EXISTS\n");
        return STATUS_UNSUCCESSFUL;
    }
    
    PFAST_ALLOCATION_TEMPLATE NewTemplate = AllocateFastObjectClassTemplate(
        ClassName,
        ObjectCount,
        ObjectSize,
        ObjectAlignment,
        Flags,
        PageFlags,
        Constructor,
        DeConstructor
    );

    if(!NewTemplate){
        LouPrint("LouKeCreateFastObjectClass() ENO_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return STATUS_SUCCESS;
}


LOUSTATUS LouKeCreateFastObjectClass(
    LOUSTR  ClassName,
    SIZE    ObjectCount,
    SIZE    ObjectSize,
    SIZE    ObjectAlignment,
    SIZE    Flags,
    SIZE    PageFlags
){
    return LouKeCreateFastObjectClassEx(
        ClassName,
        ObjectCount,
        ObjectSize,
        ObjectAlignment,
        Flags,
        PageFlags,
        0x00,
        0x00        
    );
}

PVOID LouKeAllocateFastObjectEx(
    LOUSTR  ObjectLookup,
    PVOID   ConstructData
){
    PFAST_ALLOCATION_TEMPLATE Template = AcquireFastObjectTemplate(ObjectLookup);
    if(!Template){
        LouPrint("LouKeAllocateFastObjectEx():Object Dosent Exist:%s\n", ObjectLookup);
        return 0x00;
    }

    PVOID Result = 0;
    PFAST_ALLOCATION_TRACKER TmpTracker = &Template->PoolTrackers;
    MutexLock(&Template->PoolTrackerLock);

    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PFAST_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
        if(LouKeGetReferenceCount(&TmpTracker->KRef) >= Template->ObjectCount)continue;
        Result = LouKeMallocFromFixedPool(TmpTracker->AllocationPool);
        if(Result){
            LouKeAcquireReference(&TmpTracker->KRef);
            MutexUnlock(&Template->PoolTrackerLock);
            if(Template->Constructor){
                MutexLock(&Template->BuildLock);
                Template->Constructor(Result, ConstructData);
                MutexUnlock(&Template->BuildLock);
            }
            goto _ALLOCATION_FINISHED;
        }
    }

    MutexUnlock(&Template->PoolTrackerLock);
  
    PFAST_ALLOCATION_TRACKER NewPool = AllocatePoolTracker(Template);

    if(!NewPool){
        LouPrint("LouKeAllocateFastObjectEx() ENO_RESOURCES\n");
        goto _ALLOCATION_FINISHED;
    }

    Result = LouKeMallocFromFixedPool(NewPool->AllocationPool);
    if(Result){
        LouKeAcquireReference(&NewPool->KRef);
        if(Template->Constructor){
            MutexLock(&Template->BuildLock);
            Template->Constructor(Result, ConstructData);
            MutexUnlock(&Template->BuildLock);
        }
    }

    _ALLOCATION_FINISHED:
    ReleaseFastObjectTemplate(Template);    
    return Result;

}

PVOID LouKeAllocateFastObject(
    LOUSTR  ObjectLookup
){
    return LouKeAllocateFastObjectEx(ObjectLookup, 0x00);
}

void LouKeFreeFastObject(LOUSTR ObjectLookup, PVOID Address){
    PFAST_ALLOCATION_TEMPLATE Template = AcquireFastObjectTemplate(ObjectLookup);
    if(!Template){
        LouPrint("LouKeFreeFastObject():Object Dosent Exist:%s\n", ObjectLookup);
        return;
    }

    PFAST_ALLOCATION_TRACKER TmpTracker = &Template->PoolTrackers;
    UINT64 PoolSize = (ROUND_UP64(Template->ObjectSize, Template->ObjectAlignment) * Template->ObjectCount);
    MutexLock(&Template->PoolTrackerLock);
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PFAST_ALLOCATION_TRACKER)TmpTracker->Peers.NextHeader;
        POOL TmpPool = TmpTracker->AllocationPool;
        if(RangeInterferes((UINT64)Address, 1, TmpPool->VLocation, PoolSize)){
            LouKeFreeFromFixedPool(TmpPool, Address);
            LouKeReleaseReference(&TmpTracker->KRef);
            if(!LouKeGetReferenceCount(&TmpTracker->KRef)){
                LouPrint("HERE\n");
                FreePoolTracker(Template, TmpTracker);
            }
            goto _FREE_FINISHED;
        }        
    }

    _FREE_FINISHED:
    MutexUnlock(&Template->PoolTrackerLock);
    ReleaseFastObjectTemplate(Template);    
} 