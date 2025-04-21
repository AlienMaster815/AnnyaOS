#include <LouAPI.h>

static LMPOOL_DIRECTORY FixedPoolDirectory;
static uint64_t AllocatedFixedPools = 0;
static spinlock_t FixedPoolManagerMutex;

static inline 
void InitializeFixedPool(
    PLMPOOL_DIRECTORY NewDirectory,
    string Tag,
    uint64_t Location,
    uint64_t VLocation,
    uint64_t MemberCount,
    uint64_t ObjectSize,
    uint64_t Flags
){    
    NewDirectory->List.NextHeader = 0x00;
    NewDirectory->Tag = Tag;
    NewDirectory->Location = Location;
    NewDirectory->ObjectSize = ObjectSize; 
    NewDirectory->Flags = Flags;
    NewDirectory->PoolSize = MemberCount;
    NewDirectory->PoolBitMap = LouKeMallocEx(ROUND_UP64(MemberCount, 8) / 8, 1, KERNEL_GENERIC_MEMORY);
    NewDirectory->VLocation = VLocation;
}

PLMPOOL_DIRECTORY LouKeMapFixedPool(
    uint64_t LocationOfPool,
    uint64_t LocationOfVMem,
    uint64_t PoolSize,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags
){
    //NOTE: Im going to do this later its 3AM and im tired  

    return 0x00;//NewDir;
}

void LouKeFreePool(PLMPOOL_DIRECTORY PoolToFree){
    PLMPOOL_DIRECTORY Tmp = &FixedPoolDirectory;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&FixedPoolManagerMutex, &Irql);
    for(size_t i = 0 ; i < AllocatedFixedPools; i++){
        if((PLMPOOL_DIRECTORY)Tmp->List.NextHeader == PoolToFree){
            PLMPOOL_DIRECTORY Tmp2 = (PLMPOOL_DIRECTORY)Tmp->List.NextHeader;
            Tmp->List.NextHeader = Tmp2->List.NextHeader;
            LouKeFree(Tmp2->PoolLock);
            LouKeFree((void*)Tmp2->VLocation);
            LouKeFree(Tmp2);
            AllocatedFixedPools++;
            LouKeReleaseSpinLock(&FixedPoolManagerMutex, &Irql);
            return;
        }
        if(Tmp->List.NextHeader){
            Tmp = (PLMPOOL_DIRECTORY)Tmp->List.NextHeader;
        } 
    }
    LouKeReleaseSpinLock(&FixedPoolManagerMutex, &Irql);
}

void* LouKeMallocFromFixedPool(
    PLMPOOL_DIRECTORY Pool
){
    LouKIRQL Irql;
    LouKeAcquireSpinLock(Pool->PoolLock, &Irql);
    uint8_t* Bitmap = Pool->PoolBitMap;
    uint64_t MemberCount = Pool->PoolSize;
    uint64_t SectionCount = ROUND_UP64(MemberCount, 8) / 8;
    for(uint64_t Sc = 0; Sc < SectionCount; Sc++){
        for(uint64_t Mc = 0; Mc < 8; Mc++){
            uint64_t index = (Sc * 8) + Mc;
            if(index >= MemberCount){
                LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
                return 0x00;
            }
            if(!(Bitmap[Sc] & (1 << Mc))){
                Bitmap[Sc] |= (1 << Mc);
                LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
                return (void*)(Pool->VLocation + CALCULATE_ARAY_ADDRESS(index, Pool->ObjectSize, 16));
            }
        }
    }
    LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
    return 0x00;
}

void LouKeFreeFromFixedPool(PLMPOOL_DIRECTORY Pool, void* Address) {
    LouKIRQL Irql;
    LouKeAcquireSpinLock(Pool->PoolLock, &Irql);
    uint8_t* Bitmap = Pool->PoolBitMap;
    uint64_t MemberCount = Pool->PoolSize;
    uint64_t SectionCount = ROUND_UP64(MemberCount, 8) / 8;
    for(uint64_t Sc = 0; Sc < SectionCount; Sc++){
        for(uint64_t Mc = 0; Mc < 8; Mc++){
            uint64_t index = (Sc * 8) + Mc;
            if(index >= MemberCount){
                LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
                return;
            }
            if((void*)(Pool->VLocation + CALCULATE_ARAY_ADDRESS(index, Pool->ObjectSize, 16)) == Address){
                Bitmap[Sc] &= ~(1 << Mc);
                LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
                return;
            }
        }
    }
    LouKeReleaseSpinLock(Pool->PoolLock, &Irql);
}


PLMPOOL_DIRECTORY LouKeCreateFixedPool(
    uint64_t NumberOfPoolMembers,
    uint64_t ObjectSize,
    string Tag,
    uint64_t Flags,
    uint64_t PageFlags
){
    if (NumberOfPoolMembers == 0 || ObjectSize == 0) return 0x00;

    uint64_t PoolVAddress = (uint64_t)LouKeMallocEx(CALCULATE_ARAY_ADDRESS(NumberOfPoolMembers, ObjectSize, 16) + ObjectSize, 16, PageFlags);
    uint64_t PoolPhysicalAddress = 0;
    RequestPhysicalAddress((uint64_t)PoolVAddress, &PoolPhysicalAddress);
    PLMPOOL_DIRECTORY NewPool = (PLMPOOL_DIRECTORY)LouKeMallocEx(sizeof(LMPOOL_DIRECTORY), GET_ALIGNMENT(LMPOOL_DIRECTORY), KERNEL_GENERIC_MEMORY);
    NewPool->PoolLock = (spinlock_t*)LouKeMallocEx(sizeof(spinlock_t), GET_ALIGNMENT(spinlock_t), KERNEL_GENERIC_MEMORY); 
    InitializeFixedPool(
        NewPool,
        Tag,
        PoolPhysicalAddress,
        PoolVAddress,
        NumberOfPoolMembers,
        ObjectSize,
        Flags
    );

    PLMPOOL_DIRECTORY Tmp = &FixedPoolDirectory;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&FixedPoolManagerMutex, &Irql);
    for(size_t i = 0 ; i < AllocatedFixedPools; i++){
        if(Tmp->List.NextHeader){
            Tmp = (PLMPOOL_DIRECTORY)Tmp->List.NextHeader;
        } 
    }
    Tmp->List.NextHeader = (PListHeader)NewPool;
    AllocatedFixedPools++;
    LouKeReleaseSpinLock(&FixedPoolManagerMutex, &Irql);
    return NewPool;
}