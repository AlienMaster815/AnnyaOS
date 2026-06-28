#include <LouAPI.h>

static PLOADER_RAT_MBR_CHUNK RatMbrTable = 0x00;

BOOLEAN LouKeRatIsAddressFreeEx(PVOID Address, SIZE Size, UINTPTR* EndofAllocations){
    if(!Address || !Size){
        return false;
    }
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    for(SIZE i = 0; i < MbrChunksAllocated; i++){
        if(RangeInterferes(Mbr[i].Base, Mbr[i].Length, (UINT64)Address, Size)){
            if(EndofAllocations){
                *EndofAllocations = (Mbr[i].Base + Mbr[i].Length);  
            }
            return false;
        }
        MbrChunkIndex = (PRAT_TRACKER)((UINTPTR)Mbr[i].Base + KSpaceBase);
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            if(RangeInterferes(MbrChunkIndex[j].Base, MbrChunkIndex[j].Length, (UINT64)Address, Size)){
                if(EndofAllocations){
                    *EndofAllocations = (MbrChunkIndex[j].Base + MbrChunkIndex[j].Length);  
                }
                return false;
            }
        }
    }
    return true;
}

void LouKeRatFreeAddress(UINTPTR Address){
    //LouPrint("FREE:%h\n", Address);
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    for(SIZE i = 0; i < MbrChunksAllocated; i++){
        if(Mbr[i].Base == (UINT64)Address){
            Mbr[i].Base = 0;
            Mbr[i].Length = 0;
            return;
        }
        MbrChunkIndex = (PRAT_TRACKER)((UINTPTR)Mbr[i].Base + KSpaceBase);
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            if(MbrChunkIndex[j].Base == (UINT64)Address){
                MbrChunkIndex[j].Base = 0;
                MbrChunkIndex[j].Length = 0;
                return;
            }
        }
    }
}

BOOLEAN LouKeRatIsAddressFree(PVOID Address, SIZE Size){
    return LouKeRatIsAddressFreeEx(Address, Size, 0x00);
}

typedef BOOLEAN (*RAT_ENTRY_HANDLER)(PVOID Context, PRAT_TRACKER Tracker);

BOOLEAN LouKeRatForEachRatEntryTillTrue(RAT_ENTRY_HANDLER Handler, PVOID Context, LOADER_MEMORY_MAP_ATTRIBUTE Attributes){
    SIZE Count = RatMbrTable->Count;
    BOOLEAN Result;
    for(SIZE i = 0; i < Count; i++){
        if((Attributes == LOADER_ANY_ATTRIBUTE_MEMORY) || (RatMbrTable->Entries[i].Attributes == Attributes)){
            Result = Handler(Context, &RatMbrTable->Entries[i].Tracker);
            if(Result){
                return Result;
            }
        }
    }
    return false;
}


BOOLEAN LouKeRatForEachRatEntry(RAT_ENTRY_HANDLER Handler, PVOID Context, LOADER_MEMORY_MAP_ATTRIBUTE Attributes){
    SIZE Count = RatMbrTable->Count;
    BOOLEAN Result;
    for(SIZE i = 0; i < Count; i++){
        if((Attributes == LOADER_ANY_ATTRIBUTE_MEMORY) || (RatMbrTable->Entries[i].Attributes == Attributes)){
            Result = Handler(Context, &RatMbrTable->Entries[i].Tracker);
            if(!Result){
                return Result;
            }
        }
    }
    return true;
}


typedef struct _REP_GET_ALLOCATION_CTX{
    UINTPTR     Base;
    SIZE        Length;
    SIZE        Alignment;
}REP_GET_ALLOCATION_CTX, * PREP_GET_ALLOCATION_CTX;

static SIZE VirtualBase = 0;

static BOOLEAN GetFirstFree32BitAddress(PVOID Context, PRAT_TRACKER Tracker){
    if((Tracker->Base + Tracker->Length) <= UINT16_MAX){
        return false;
    }
    SIZE SpaceLimit = (4 * GIGABYTE);
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    PVOID Result = (PVOID)MAX(Tracker->Base, 0xFFFF);
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while((((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)) && (((UINT64)Result + AllocContext->Length) <= SpaceLimit)){
        UINTPTR NextHint = 0x00;
        if(LouKeRatIsAddressFreeEx(Result, AllocContext->Length, &NextHint)){
            AllocContext->Base = (UINTPTR)Result;
            return true;
        }        
        Result = (PVOID)ROUND_UP64((UINTPTR)NextHint, AllocContext->Alignment);   
        if((UINTPTR)Result == NextHint){
            Result = (PVOID)((UINTPTR)Result + AllocContext->Alignment);
        }
    }
    return false;
}


static BOOLEAN GetFirstFree64BitAddress(PVOID Context, PRAT_TRACKER Tracker){    
    if((Tracker->Base + Tracker->Length) < (4 * GIGABYTE)){
        return false;
    }
    
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    PVOID Result = (PVOID)MAX(Tracker->Base, (4 * GIGABYTE));
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while(((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)){
        UINTPTR NextHint = 0x00;
        if(LouKeRatIsAddressFreeEx(Result, AllocContext->Length, &NextHint)){
            AllocContext->Base = (UINTPTR)Result;
            return true;
        }        
        Result = (PVOID)ROUND_UP64((UINTPTR)NextHint, AllocContext->Alignment);   
        if((UINTPTR)Result == NextHint){
            Result = (PVOID)((UINTPTR)Result + AllocContext->Alignment);
        }
    }
    return false;
}

static BOOLEAN GetFirstFreeVirtualAddress(PVOID Context, PRAT_TRACKER Tracker){
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    UINTPTR Result = VirtualBase;
    Result = ROUND_UP64(Result, AllocContext->Alignment);
    LOUSTATUS Status = STATUS_SUCCESS;
    UINTPTR Checksum;
    while(1){
        UINTPTR NextHint = 0x00;
        if(LouKeRatIsAddressFreeEx((PVOID)Result, AllocContext->Length, &NextHint)){
            AllocContext->Base = (UINTPTR)Result;
            return true;
        }        
        Result = (UINTPTR)ROUND_UP64((UINTPTR)NextHint, AllocContext->Alignment);   
        if(Result < KSpaceBase){
            break;
        }
        if((UINTPTR)Result == NextHint){
            Status = LouKeRtlUintptrAdd(Result, AllocContext->Alignment, &Checksum);
            if(Status != STATUS_SUCCESS){
                break;
            }
            Result = Checksum;
        }
    }
    return false;
}

static BOOLEAN GetFirstFreeAddress(PVOID Context, PRAT_TRACKER Tracker){
    if((Tracker->Base + Tracker->Length) <= UINT16_MAX){
        return false;
    }
    PVOID Result = (PVOID)MAX(Tracker->Base, 0xFFFF);
    PREP_GET_ALLOCATION_CTX AllocContext = (PREP_GET_ALLOCATION_CTX)Context;
    Result = (PVOID)ROUND_UP64((UINTPTR)Result, AllocContext->Alignment);

    while(((UINTPTR)Result + AllocContext->Length) <= (UINTPTR)(Tracker->Base + Tracker->Length)){
        UINTPTR NextHint = 0x00;
        if(LouKeRatIsAddressFreeEx(Result, AllocContext->Length, &NextHint)){
            AllocContext->Base = (UINTPTR)Result;
            return true;
        }        
        Result = (PVOID)ROUND_UP64((UINTPTR)NextHint, AllocContext->Alignment);   
        if((UINTPTR)Result == NextHint){
            Result = (PVOID)((UINTPTR)Result + AllocContext->Alignment);
        }
    }
    return false;
}


PRAT_TRACKER LouKeRatGetNextFreeAllocationTracker(){
    PRAT_TRACKER Mbr = &RatMbrTable->Mbr[0];
    SIZE MbrChunksAllocated = RatMbrTable->MbrChunksAllocated;
    PRAT_TRACKER MbrChunkIndex = 0x00;
    SIZE MbrChunkAllocations = 0;
    SIZE i;
    //check for fragmentation and defragment
    for(i = 0; i < MbrChunksAllocated; i++){
        MbrChunkIndex = (PRAT_TRACKER)(Mbr[i].Base + KSpaceBase);
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i];
        for(SIZE j = 0; j < MbrChunkAllocations; j++){
            //defragment if posible
            if(!MbrChunkIndex[j].Base){
                return &MbrChunkIndex[j];
            }
        }
    }
    if(MbrChunkAllocations == RatMbrTable->ChunkSize){
        if(MbrChunksAllocated >= 100){
            return 0x00;
        }
        REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = RatMbrTable->ChunkSize * sizeof(RAT_TRACKER), .Alignment = GET_ALIGNMENT(RAT_TRACKER)};
        BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFreeAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
        if(!Successfull){
            return 0x00;
        }
        Mbr[i].Base = Context.Base;
        Mbr[i].Length = RatMbrTable->ChunkSize * sizeof(RAT_TRACKER);
        memset((PVOID)(Mbr[i].Base + KSpaceBase), 0, Mbr[i].Length);
        RatMbrTable->MbrChunksAllocated++;
        MbrChunkIndex = (PRAT_TRACKER)(Mbr[i].Base + KSpaceBase);
        MbrChunkAllocations = RatMbrTable->ChunkAllocatorIndexor[i]; //should be 0
        i++;
    }
    PRAT_TRACKER Result = &MbrChunkIndex[MbrChunkAllocations];
    MbrChunkAllocations++;
    RatMbrTable->ChunkAllocatorIndexor[i - 1] = MbrChunkAllocations;
    return Result;
}

static spinlock_t RatLock = {0};

PVOID LouKeRatAllocate32BitPhysicalAddress(SIZE Size, SIZE Alignment){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RatLock, &Irql);
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        LouPrint("LouKeRatAllocate32BitPhysicalAddress() No Free Trackers\n");
        LouKeReleaseSpinLock(&RatLock, &Irql);
        //while(1);
        return 0x00;
    }
    REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = Size, .Alignment = Alignment};
    BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFree32BitAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
    if(!Successfull){
        LouPrint("LouKeRatAllocate32BitPhysicalAddress() No Free Memory\n");
        LouKeReleaseSpinLock(&RatLock, &Irql);
        //while(1);
        return 0x00;
    } 
    NewTracker->Base = Context.Base;
    NewTracker->Length = Context.Length;
    LouKeReleaseSpinLock(&RatLock, &Irql);
    //LouPrint("ALOC:%h\n", NewTracker->Base);
    return (PVOID)Context.Base;
}

PVOID LouKeRatAllocate64BitPhysicalAddress(SIZE Size, SIZE Alignment){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RatLock, &Irql);
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        LouPrint("LouKeRatAllocate64BitPhysicalAddress() No Free Trackers\n");
        LouKeReleaseSpinLock(&RatLock, &Irql);
        //while(1);
        return 0x00;
    }
    REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = Size, .Alignment = Alignment};
    BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFree64BitAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
    if(!Successfull){
        Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFree32BitAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
        if(!Successfull){
            LouKeReleaseSpinLock(&RatLock, &Irql);
            LouPrint("LouKeRatAllocate64BitPhysicalAddress() No Free Memory\n");
            //while(1);
            return 0x00;
        }
    } 
    NewTracker->Base = Context.Base;
    NewTracker->Length = Context.Length;
    LouKeReleaseSpinLock(&RatLock, &Irql);
    //LouPrint("ALOC:%h\n", NewTracker->Base);
    return (PVOID)Context.Base;
}

PVOID LouKeRatAllocateVirtualAddress(SIZE Size, SIZE Alignment){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RatLock, &Irql);
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        LouPrint("LouKeRatAllocateVirtualAddress() No Free Tracker\n");
        LouKeReleaseSpinLock(&RatLock, &Irql);
        //while(1);
        return 0x00;
    }
    REP_GET_ALLOCATION_CTX Context = {.Base = 0, .Length = Size, .Alignment = Alignment};
    BOOLEAN Successfull = LouKeRatForEachRatEntryTillTrue(GetFirstFreeVirtualAddress, (PVOID)&Context, LOADER_USABLE_MEMORY);
    if(!Successfull){
        LouPrint("LouKeRatAllocateVirtualAddress() No Free Memory\n");
        LouKeReleaseSpinLock(&RatLock, &Irql);
        //while(1);
        return 0x00;
    } 
    NewTracker->Base = Context.Base;
    NewTracker->Length = Context.Length;
    LouKeReleaseSpinLock(&RatLock, &Irql);
    //LouPrint("ALOC:%h\n", NewTracker->Base);
    return (PVOID)Context.Base;
}

BOOLEAN LouKeRatReserveMemoryRegion(
    PVOID RegionBase,
    SIZE  RegionSize
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&RatLock, &Irql);
    PRAT_TRACKER NewTracker = LouKeRatGetNextFreeAllocationTracker();
    if(!NewTracker){
        LouKeReleaseSpinLock(&RatLock, &Irql);
        LouPrint("LouKeRatReserveMemoryRegion() No Free Tracker\n");
        //while(1);
        return false;
    }
    NewTracker->Base = (UINTPTR)RegionBase;
    NewTracker->Length = RegionSize;
    LouKeReleaseSpinLock(&RatLock, &Irql);
    return true;
}

LOUSTATUS LouKeInitializeRatSubsystem(
    PLOADER_INFORMATION Info
){
    RatMbrTable = Info->RatMbr;
    if((UINT64)RatMbrTable < KSpaceBase){
        RatMbrTable = (PLOADER_RAT_MBR_CHUNK)((UINT64)RatMbrTable + KSpaceBase);
    }
    VirtualBase = KSpaceBase + Info->MachineSize;

    return STATUS_SUCCESS;
}