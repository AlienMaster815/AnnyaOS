
// allocation.c
// Tyler Grenier

//include headers from freestanding

#define StartMap (60ULL * MEGABYTE)
#define StartMap64 (4ULL * GIGABYTE)

#include <LouAPI.h>
// define constants
#include <bootloader/grub/multiboot2.h>

void* LouMalloc(size_t BytesToAllocate);

#define BITMAP_TABLE_BASE 0
#define TABLE_SIZE  8

uint64_t GetRamSize();


static spinlock_t MemmoryMapLock;

static struct master_multiboot_mmap_entry* LousineMemoryMapTable;


void SendMapToAllocation(struct master_multiboot_mmap_entry* mmap) {
    LousineMemoryMapTable = mmap;
}

struct master_multiboot_mmap_entry* LouKeGetMemoryMapTable(){
    return LousineMemoryMapTable;
}

typedef struct _LOU_MALLOC_TRACKER{
    uint64_t    Address;
    uint64_t    size;
}LOU_MALLOC_TRACKER, * PLOU_MALLOC_TRACKER;

typedef struct _AllocationBlock{
    uint64_t Address;
    uint64_t size;
}AllocationBlock;


static PLOU_MALLOC_TRACKER  AllocationBlocks[100] = {0};
static uint64_t             AllocationBlocksConfigured = 0; 
static uint32_t             TotalAllocations[100] = {0};
#define CURRENT_ALLOCATION_BLOCK AllocationBlocksConfigured - 1

uint8_t TB[sizeof(AllocationBlock) * 512] = {0};
static AllocationBlock* AddressBlock = (AllocationBlock*)TB;

static uint32_t AddressesLogged = 0;

uint64_t GetUsedMemory(){
    uint64_t UsedRam = 0;
    for(uint16_t i = 0; i < AddressesLogged; i++){
        if(AddressBlock[i].Address){
            UsedRam += AddressBlock[i].size;
        }
    }
    return UsedRam;
}

uint64_t GetAllocationBlockSize(uint64_t Address){
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    for(uint16_t i = 0; i < AddressesLogged; i++){
        if(AddressBlock[i].Address == Address){
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return AddressBlock[i].size;
        }
    }
    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
        for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
            if(AllocationBlocks[k][i].Address == Address){
                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                return AllocationBlocks[k][i].size;
            }
        }
    }
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
    return 0x00;
}

uint64_t GetAllocationBlockBase(uint64_t Address){
    for(uint16_t i = 0; i < AddressesLogged; i++){
        if(RangeInterferes(Address, 1, AddressBlock[i].Address, AddressBlock[i].size)){
            return AddressBlock[i].Address;
        }
    }
    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
        for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
            if(RangeInterferes(Address, 1, AllocationBlocks[k][i].Address, AllocationBlocks[k][i].size)){
                return AllocationBlocks[k][i].Address;
            }
        }
    }
    return 0x00;
}

static bool IsEarlyMallocation = true;



void* LouVMalloc(size_t BytesToAllocate){
    return LouVMallocEx(BytesToAllocate, GetAlignmentBySize(BytesToAllocate));
}

void* LouMallocExFromStartup(size_t BytesToAllocate, uint64_t Alignment) {
    uint16_t Number_Of_Entries = (LousineMemoryMapTable->tag.size - sizeof(struct master_multiboot_mmap_entry)) / LousineMemoryMapTable->entry_size;
    if (LousineMemoryMapTable->entry_version == 0) {
        struct multiboot_mmap_entry* mmap_entry;
        for (uint16_t i = 0; i < Number_Of_Entries; i++) {
            mmap_entry = (struct multiboot_mmap_entry*)(uintptr_t)((uint64_t)LousineMemoryMapTable + (uint64_t)sizeof(struct master_multiboot_mmap_entry) + (uint64_t)i * (uint64_t)LousineMemoryMapTable->entry_size);
            uint64_t limit = mmap_entry->len;
            uint64_t address = mmap_entry->addr;
            if (mmap_entry->type == 0) continue; // Skip unusable memory
            else if (mmap_entry->type == 1) {
                // Skip if system memory

                if ((mmap_entry->addr + mmap_entry->len) < StartMap) continue;
                else if (mmap_entry->addr < StartMap) {
                    limit = (mmap_entry->addr + mmap_entry->len) - StartMap;
                    address = StartMap;
                }

                uint64_t AlignmentCheck = ROUND_UP64(address, Alignment);
                if(IsEarlyMallocation == true){
                    if (AddressesLogged == 0) {
                        AddressBlock[0].Address = AlignmentCheck;
                        AddressBlock[0].size = BytesToAllocate;
                        AddressesLogged++; // Increment after logging the first address
                        memset((void*)AlignmentCheck, 0 , BytesToAllocate);
                        return (void*)AlignmentCheck;
                    }

                    while (1) {
                        if (((AlignmentCheck + Alignment) > limit) || ((AlignmentCheck + BytesToAllocate + Alignment) > limit)) {
                            break;
                        }
                        //AlignmentCheck += Alignment;

                        bool addrssSpaceCheck = true;

                        for (uint32_t i = 0; i < AddressesLogged; i++) {
                            uint64_t start = AddressBlock[i].Address;
                            uint64_t end = start + AddressBlock[i].size;

                            // Check if the new allocation overlaps with an existing block
                            if ((AlignmentCheck >= start && AlignmentCheck <= end) ||  // Start within an existing block
                                ((AlignmentCheck + BytesToAllocate) >= start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                                (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
                                AlignmentCheck += ROUND_UP64(AddressBlock[i].size, Alignment);
                                addrssSpaceCheck = false;
                                break;
                            }
                        }


                        if (!addrssSpaceCheck) {
                            continue;
                        }

                        // Found an address
                        for (uint32_t i = 0; i < AddressesLogged; i++) {
                            if (AddressBlock[i].Address == 0x00) {
                                AddressBlock[i].Address = AlignmentCheck;
                                AddressBlock[i].size = BytesToAllocate;
                                //LouPrint("Address:%h\n", AlignmentCheck);
                                memset((void*)AlignmentCheck, 0 , BytesToAllocate);
                                return (void*)AlignmentCheck;
                            }
                        }

                        if (AddressesLogged >= (786432)) {
                            // System overload
                            while(1);                           
                            return NULL;
                        }

                        AddressBlock[AddressesLogged].Address = AlignmentCheck;
                        AddressBlock[AddressesLogged].size = BytesToAllocate;
                        AddressesLogged++; // Increment after logging the new address
                        //LouPrint("Address:%h\n", AlignmentCheck);
                        memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                        return (void*)AlignmentCheck;
                    }
                }
            }
            else if (mmap_entry->type == 2) continue;
            else if (mmap_entry->type == 3) continue;
            else continue;
        }
    }
    while(1);
    return NULL;    
}

bool EnforceSystemMemoryMap(
    uint64_t Address, 
    uint64_t size
){
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    for(uint32_t i = 0 ; i < AddressesLogged; i++){
        if(AddressBlock[i].Address == Address){
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return false; //System Already Mapped Address
        }
        if(AddressBlock[i].Address == 0x00){
            AddressBlock[i].Address = Address;
            AddressBlock[i].size = size;
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return true;
        }
    }
    if(AllocationBlocksConfigured){
        for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
            for (uint32_t j = 0; j < TotalAllocations[k]; j++) {
                if (AllocationBlocks[k][j].Address == 0x00) {
                    AllocationBlocks[k][j].Address = Address;
                    AllocationBlocks[k][j].size = size;
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    return true;
                }
            }
        }
        if((TotalAllocations[CURRENT_ALLOCATION_BLOCK] * sizeof(LOU_MALLOC_TRACKER)) > (10 * MEGABYTE)){
            AllocationBlocksConfigured++;
            if(AllocationBlocksConfigured == 100){
                LouPrint("error using 100% memory is imposible\n");
                while(1);//error using 100 % memory is imposible
            }
            AllocationBlocks[CURRENT_ALLOCATION_BLOCK] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
        }
        AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].Address = Address;
        AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].size = size;
        TotalAllocations[CURRENT_ALLOCATION_BLOCK]++;
        LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
        return true;
    }
    if(AddressesLogged < 512){
        AddressBlock[AddressesLogged].Address = Address;
        AddressBlock[AddressesLogged].size = size;
        AddressesLogged++;
        LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);  
        return true;
    }
    LouPrint("KERNEL_PANIC:Out Of Memory EnforceSystemMemoryMap()\n");
    while(1);
    return false;
}


void* LouMalloc(size_t BytesToAllocate) {

    return LouMallocEx(BytesToAllocate, GetAlignmentBySize(BytesToAllocate));

}

void ListUsedAddresses(){

}

uint64_t SearchForMappedAddressSize(uint64_t Address){
    return GetAllocationBlockSize(Address);
}

void* _LouMallocEx(
    SIZE BytesToAllocate, 
    UINT64 Alignment
){
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    uint16_t Number_Of_Entries = (LousineMemoryMapTable->tag.size - sizeof(struct master_multiboot_mmap_entry)) / LousineMemoryMapTable->entry_size;
    if (LousineMemoryMapTable->entry_version == 0) {
        struct multiboot_mmap_entry* mmap_entry;
        for (uint16_t i = 0; i < Number_Of_Entries; i++) {
            mmap_entry = (struct multiboot_mmap_entry*)(uintptr_t)((uint64_t)LousineMemoryMapTable + (uint64_t)sizeof(struct master_multiboot_mmap_entry) + (uint64_t)i * (uint64_t)LousineMemoryMapTable->entry_size);
            UNUSED uint64_t limit = mmap_entry->len;
            UNUSED uint64_t address = mmap_entry->addr;
            if (mmap_entry->type == 0) continue; // Skip unusable memory
            else if (mmap_entry->type == 1) {
                // Skip if system memory

                if ((mmap_entry->addr + mmap_entry->len) < StartMap) continue;
                else if (mmap_entry->addr < StartMap) {
                    limit = (mmap_entry->addr + mmap_entry->len) - StartMap;
                    address = StartMap;
                }
                if(!AllocationBlocksConfigured){
                    AllocationBlocks[0] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
                    AllocationBlocksConfigured++;
                }
                
                UNUSED uint64_t AlignmentCheck = ROUND_UP64(address,Alignment);

                PLOU_MALLOC_TRACKER FreeTrack = AllocationBlocks[CURRENT_ALLOCATION_BLOCK];

                FreeTrack = &FreeTrack[TotalAllocations[CURRENT_ALLOCATION_BLOCK]];

                while ((AlignmentCheck + Alignment) <= StartMap64) {
                    if (((AlignmentCheck + Alignment) > limit) || ((AlignmentCheck + BytesToAllocate + Alignment) > limit)) {
                        break;
                    }
                    //AlignmentCheck += Alignment;
                    bool addrssSpaceCheck = true;

                    for (uint32_t i = 0; i < AddressesLogged; i++) {

                        if(RangeInterferes(
                            AlignmentCheck,
                            BytesToAllocate,
                            AddressBlock[i].Address,
                            AddressBlock[i].size
                        )){
                            AlignmentCheck += ROUND_UP64(AddressBlock[i].size, Alignment);
                            addrssSpaceCheck = false;
                            break;
                        }
                    }
                    if(!addrssSpaceCheck){
                        continue;
                    }
                    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
                        for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
                            if(RangeInterferes(
                                AlignmentCheck,
                                BytesToAllocate,
                                AllocationBlocks[k][i].Address,
                                AllocationBlocks[k][i].size
                            )){
                                AlignmentCheck += ROUND_UP64(AllocationBlocks[k][i].size, Alignment);
                                addrssSpaceCheck = false;
                                break;
                            }
                        }
                    }
                    if(!addrssSpaceCheck){
                        continue;
                    }
                    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
                        for (uint32_t j = 0; j < TotalAllocations[k]; j++) {
                            if (AllocationBlocks[k][j].Address == 0x00) {
                                AllocationBlocks[k][j].Address = AlignmentCheck;
                                AllocationBlocks[k][j].size = BytesToAllocate;
                                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);  
                                memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                                return (void*)AlignmentCheck;
                            }
                        }
                    }
                    if((TotalAllocations[CURRENT_ALLOCATION_BLOCK] * sizeof(LOU_MALLOC_TRACKER)) > (10 * MEGABYTE)){
                        AllocationBlocksConfigured++;
                        if(AllocationBlocksConfigured == 100){
                            LouPrint("error using 100% memory is imposible\n");
                            while(1);//error using 100 % memory is imposible
                        }
                        AllocationBlocks[CURRENT_ALLOCATION_BLOCK] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
                    }

                    AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].Address = AlignmentCheck;
                    AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].size = BytesToAllocate;
                    TotalAllocations[CURRENT_ALLOCATION_BLOCK]++;
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                    return (void*)AlignmentCheck;
                }

            }
            else if (mmap_entry->type == 2) continue;
            else if (mmap_entry->type == 3) continue;
            else continue;
        }
    }
    LouPrint("Out Of Memory Needed:%h\n", BytesToAllocate);
    while(1);
    return NULL; 
}

void* _LouMallocEx64(
    SIZE BytesToAllocate, 
    UINT64 Alignment
){
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    uint16_t Number_Of_Entries = (LousineMemoryMapTable->tag.size - sizeof(struct master_multiboot_mmap_entry)) / LousineMemoryMapTable->entry_size;
    if (LousineMemoryMapTable->entry_version == 0) {
        struct multiboot_mmap_entry* mmap_entry;
        for (uint16_t i = 0; i < Number_Of_Entries; i++) {
            mmap_entry = (struct multiboot_mmap_entry*)(uintptr_t)((uint64_t)LousineMemoryMapTable + (uint64_t)sizeof(struct master_multiboot_mmap_entry) + (uint64_t)i * (uint64_t)LousineMemoryMapTable->entry_size);
            UNUSED uint64_t limit = mmap_entry->len;
            UNUSED uint64_t address = mmap_entry->addr;
            if (mmap_entry->type == 0) continue; // Skip unusable memory
            else if (mmap_entry->type == 1) {
                // Skip if system memory

                if ((mmap_entry->addr + mmap_entry->len) < StartMap64) continue;
                else if (mmap_entry->addr < StartMap64) {
                    limit = (mmap_entry->addr + mmap_entry->len) - StartMap64;
                    address = StartMap64;
                }
                if(!AllocationBlocksConfigured){
                    AllocationBlocks[0] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
                    AllocationBlocksConfigured++;
                }
                
                UNUSED uint64_t AlignmentCheck = ROUND_UP64(address,Alignment);

                PLOU_MALLOC_TRACKER FreeTrack = AllocationBlocks[CURRENT_ALLOCATION_BLOCK];

                FreeTrack = &FreeTrack[TotalAllocations[CURRENT_ALLOCATION_BLOCK]];

                while (1) {
                    if (((AlignmentCheck + Alignment) > limit) || ((AlignmentCheck + BytesToAllocate + Alignment) > limit)) {
                        break;
                    }
                    //AlignmentCheck += Alignment;
                    bool addrssSpaceCheck = true;

                    for (uint32_t i = 0; i < AddressesLogged; i++) {

                        if(RangeInterferes(
                            AlignmentCheck,
                            BytesToAllocate,
                            AddressBlock[i].Address,
                            AddressBlock[i].size
                        )){
                            AlignmentCheck += ROUND_UP64(AddressBlock[i].size, Alignment);
                            addrssSpaceCheck = false;
                            break;
                        }
                    }
                    if(!addrssSpaceCheck){
                        continue;
                    }
                    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
                        for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
                            if(RangeInterferes(
                                AlignmentCheck,
                                BytesToAllocate,
                                AllocationBlocks[k][i].Address,
                                AllocationBlocks[k][i].size
                            )){
                                AlignmentCheck += ROUND_UP64(AllocationBlocks[k][i].size, Alignment);
                                addrssSpaceCheck = false;
                                break;
                            }
                        }
                    }
                    if(!addrssSpaceCheck){
                        continue;
                    }
                    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
                        for (uint32_t j = 0; j < TotalAllocations[k]; j++) {
                            if (AllocationBlocks[k][j].Address == 0x00) {
                                AllocationBlocks[k][j].Address = AlignmentCheck;
                                AllocationBlocks[k][j].size = BytesToAllocate;
                                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);  
                                memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                                return (void*)AlignmentCheck;
                            }
                        }
                    }
                    if((TotalAllocations[CURRENT_ALLOCATION_BLOCK] * sizeof(LOU_MALLOC_TRACKER)) > (10 * MEGABYTE)){
                        AllocationBlocksConfigured++;
                        if(AllocationBlocksConfigured == 100){
                            LouPrint("error using 100% memory is imposible\n");
                            while(1);//error using 100 % memory is imposible
                        }
                        AllocationBlocks[CURRENT_ALLOCATION_BLOCK] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
                    }

                    AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].Address = AlignmentCheck;
                    AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].size = BytesToAllocate;
                    TotalAllocations[CURRENT_ALLOCATION_BLOCK]++;
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                    return (void*)AlignmentCheck;
                }

            }
            else if (mmap_entry->type == 2) continue;
            else if (mmap_entry->type == 3) continue;
            else continue;
        }
    }
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
    return NULL; 
}

void* LouMallocEx(size_t BytesToAllocate, uint64_t Alignment) {
   return _LouMallocEx(BytesToAllocate, Alignment);
}

static void* (*LouMallocEx64Instance)(SIZE BytesToAllocate, UINT64 Alignment);

void* LouMallocEx64(SIZE BytesToAllocate, UINT64 Alignment){
    PVOID Result;
    if(LouMallocEx64Instance){
        Result = LouMallocEx64Instance(BytesToAllocate, Alignment);
        if(Result){
            return Result;
        }
    }
    return _LouMallocEx(BytesToAllocate, Alignment);
}

void LouFree(RAMADD Addr) {
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    for(uint32_t i = 0 ; i < AddressesLogged; i++){
        if(AddressBlock[i].Address == (uint64_t)Addr){
            AddressBlock[i].Address     = 0x00;
            AddressBlock[i].size        = 0x00;
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return;
        }
    }
    for(uint32_t i = 0; i < AllocationBlocksConfigured;i++){
        for(uint32_t j = 0 ; j < TotalAllocations[i]; j++){
            if(AllocationBlocks[i][j].Address == (uint64_t)Addr){
                AllocationBlocks[i][j].Address  = 0x00;
                AllocationBlocks[i][j].size     = 0x00;
                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                return;
            }
        }
    }
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
}


void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment){

    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    uint64_t AlignmentCheck = GetRamSize();
    if(!AlignmentCheck){
        AlignmentCheck = 4 * GIGABYTE;
    }

    PLOU_MALLOC_TRACKER FreeTrack = AllocationBlocks[CURRENT_ALLOCATION_BLOCK];
    FreeTrack = &FreeTrack[TotalAllocations[CURRENT_ALLOCATION_BLOCK]];
    AlignmentCheck = ROUND_UP64(AlignmentCheck, Alignment);    
    while (1) {
        //AlignmentCheck += Alignment;
        bool addrssSpaceCheck = true;

        for (uint32_t i = 0; i < AddressesLogged; i++) {

            if(RangeInterferes(
                AlignmentCheck,
                BytesToAllocate,
                AddressBlock[i].Address,
                AddressBlock[i].size
            )){
                AlignmentCheck += ROUND_UP64(AddressBlock[i].size, Alignment);
                addrssSpaceCheck = false;
                break;
            }
        }
        if(!addrssSpaceCheck){
            continue;
        }
        for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
            for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
                if(RangeInterferes(
                    AlignmentCheck,
                    BytesToAllocate,
                    AllocationBlocks[k][i].Address,
                    AllocationBlocks[k][i].size
                )){
                    AlignmentCheck += ROUND_UP64(AllocationBlocks[k][i].size, Alignment);
                    addrssSpaceCheck = false;
                    break;
                }
            }
        }
        if(!addrssSpaceCheck){
            continue;
        }
        for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
            for (uint32_t j = 0; j < TotalAllocations[k]; j++) {
                if (AllocationBlocks[k][j].Address == 0x00) {
                    AllocationBlocks[k][j].Address = AlignmentCheck;
                    AllocationBlocks[k][j].size = BytesToAllocate;
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    return (void*)AlignmentCheck;
                }
            }
        }
        for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
            for (uint32_t j = 0; j < TotalAllocations[k]; j++) {
                if (AllocationBlocks[k][j].Address == 0x00) {
                    AllocationBlocks[k][j].Address = AlignmentCheck;
                    AllocationBlocks[k][j].size = BytesToAllocate;
                    //LouPrint("Address:%h\n", AlignmentCheck);
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    return (void*)AlignmentCheck;
                }
            }
        }
        if((TotalAllocations[CURRENT_ALLOCATION_BLOCK] * sizeof(LOU_MALLOC_TRACKER)) > (10 * MEGABYTE)){
            AllocationBlocksConfigured++;
            if(AllocationBlocksConfigured >= 100){
                LouPrint("error using 100% memory is imposible\n");
                while(1);//error using 100 % memory is imposible
            }
            AllocationBlocks[CURRENT_ALLOCATION_BLOCK] = LouMallocExFromStartup(10 * MEGABYTE,sizeof(LOU_MALLOC_TRACKER));
        }

        AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].Address = AlignmentCheck;
        AllocationBlocks[CURRENT_ALLOCATION_BLOCK][TotalAllocations[CURRENT_ALLOCATION_BLOCK]].size = BytesToAllocate;
        TotalAllocations[CURRENT_ALLOCATION_BLOCK]++;
        LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
        return (void*)AlignmentCheck;
    }

    while(1);

    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);
    while(1);
    return NULL;
}

void LouKeInitializeSafeMemory(){

    void* Foo = LouMalloc(LousineMemoryMapTable->tag.size);
    memcpy(Foo, LousineMemoryMapTable, LousineMemoryMapTable->tag.size);

    LousineMemoryMapTable = Foo;

    if(GetRamSize() > StartMap64){
        LouMallocEx64Instance = _LouMallocEx64;
    }

}