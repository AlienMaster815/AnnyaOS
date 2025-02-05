
// allocation.c
// Tyler Grenier

//include headers from freestanding

#define StartMap (60ULL * MEGABYTE)

#include <LouAPI.h>
// define constants
#include <bootloader/grub/multiboot2.h>

void* LouMalloc(size_t BytesToAllocate);

#define BITMAP_TABLE_BASE 0
#define TABLE_SIZE  8

uint64_t GetRamSize();

static spinlock_t MemmoryMapLock;

RAMADD Lou_Alloc_Mem(SIZE size) {
    return (RAMADD)LouMalloc(size);
}

STATUS Lou_Free_Mem(RAMADD Addr, SIZE size) {
    LouFree(Addr);
    return GOOD;
}

void* Lou_Calloc_Mem(size_t numElements, size_t sizeOfElement) {
    // Check for overflow in the multiplication
    if (numElements == 0 || sizeOfElement == 0 || SIZE_MAX / numElements < sizeOfElement) {
        return NULL; // Overflow occurred, return NULL
    }

    // Calculate the total size needed
    size_t totalSize = numElements * sizeOfElement;

    // Allocate memory using malloc
    void* ptr = Lou_Alloc_Mem(totalSize);

    // Check if memory allocation was successful
    if (ptr != NULL) {
        // Clear the allocated memory by setting all bytes to zero
        memset(ptr, 0, totalSize);
    }

    return ptr;
}

RAMADD Lou_Alloc_Mem_Alligned(SIZE size, uint64_t alignment) {
    // Ensure the alignment is at least the size of a pointer and is a power of 2
    if (alignment < sizeof(void*) || (alignment & (alignment - 1)) != 0) {
        alignment = sizeof(void*); // Set minimum alignment to pointer size
    }

    // Allocate extra memory to ensure we can align properly within it
    SIZE totalSize = size + alignment - 1 + sizeof(uintptr_t); // Include space to store the base address
    uintptr_t rawAddress = (uintptr_t)Lou_Alloc_Mem(totalSize);

    if (!rawAddress) {
        return NULL; // Allocation failed
    }

    // Calculate the aligned memory address
    uintptr_t alignedAddress = (rawAddress + sizeof(uintptr_t) + alignment - 1) & ~(alignment - 1);

    // Store the original address just before the aligned address
    *((uintptr_t*)(alignedAddress - sizeof(uintptr_t))) = rawAddress;

    return (RAMADD)alignedAddress;
}


void LouFreeAlignedMemory(RAMADD alignedAddr, SIZE size) {
    // Retrieve the original address stored just before the aligned address
    uintptr_t originalAddress = *((uintptr_t*)((uintptr_t)alignedAddr - sizeof(uintptr_t)));

    // Calculate the total size allocated originally
    uintptr_t alignmentOffset = (uintptr_t)alignedAddr - originalAddress;
    SIZE totalSize = size + alignmentOffset + sizeof(uintptr_t);

    // Free the original memory block
    Lou_Free_Mem((void*)originalAddress, totalSize);
}

void* LouMallocAlligned(SIZE size, uint64_t allignment){
    return (void*)Lou_Alloc_Mem_Alligned(size,allignment);
}


struct master_multiboot_mmap_entry* LousineMemoryMapTable;

void SendMapToAllocation(struct master_multiboot_mmap_entry* mmap) {
    LousineMemoryMapTable = mmap;
}

struct master_multiboot_mmap_entry* LouKeGetMemoryMapTable(){
    return LousineMemoryMapTable;
}

#define LongLongBitDemention 64
#define LongLongBitDimension 64
#define BlockDemention 1024

#define BitMapDivisor 1

UNUSED static uint64_t* BitMap;



bool is_aligned(void *address, size_t alignment) {
    // Cast the address to uintptr_t to perform arithmetic on it
    uintptr_t addr = (uintptr_t)address;
    // Check if the address is aligned by checking if it is divisible by the alignment
    return addr % alignment == 0;
}


bool GetNextAllignedBitmap(){



    return true;
}

typedef struct __attribute__((packed)) _AllocationBlock{
    uint64_t Address;
    uint64_t size;
}AllocationBlock;

static uint8_t DataSlab[sizeof(AllocationBlock) * 512];

static AllocationBlock* AddressBlock = (AllocationBlock*)&DataSlab;

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
        if((AddressBlock[i].Address <= Address) && ((AddressBlock[i].Address + AddressBlock[i].size) > Address)){
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return AddressBlock[i].size - (Address - AddressBlock[i].Address);
        }
    }
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
    return 0x00;
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

    AddressBlock[AddressesLogged].Address = Address;
    AddressBlock[AddressesLogged].size = size;
    AddressesLogged++;
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);  
    return true;
}

static bool IsEarlyMallocation = true;



void* LouVMalloc(size_t BytesToAllocate){
    return LouVMallocEx(BytesToAllocate, BytesToAllocate);
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

                uint64_t AlignmentCheck = (address & ~(Alignment - 1));
                LouKIRQL OldIrql;
                LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
                if(IsEarlyMallocation == true){
                    if (AddressesLogged == 0) {
                        AddressBlock[0].Address = AlignmentCheck;
                        AddressBlock[0].size = BytesToAllocate;
                        AddressesLogged++; // Increment after logging the first address
                        memset((void*)AlignmentCheck, 0 , BytesToAllocate);
                        LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                        return (void*)AlignmentCheck;
                    }

                    while (1) {
                        if (((AlignmentCheck + Alignment) > limit) || ((AlignmentCheck + BytesToAllocate + Alignment) > limit)) {
                            break;
                        }
                        AlignmentCheck += Alignment;

                        bool addrssSpaceCheck = true;

                        for (uint32_t i = 0; i < AddressesLogged; i++) {
                            uint64_t start = AddressBlock[i].Address;
                            uint64_t end = start + AddressBlock[i].size;

                            // Check if the new allocation overlaps with an existing block
                            if ((AlignmentCheck >= start && AlignmentCheck < end) ||  // Start within an existing block
                                ((AlignmentCheck + BytesToAllocate) > start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                                (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
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
                                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                                return (void*)AlignmentCheck;
                            }
                        }

                        if (AddressesLogged >= (786432)) {
                            // System overload
                            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);     
                            while(1);                           
                            return NULL;
                        }

                        AddressBlock[AddressesLogged].Address = AlignmentCheck;
                        AddressBlock[AddressesLogged].size = BytesToAllocate;
                        AddressesLogged++; // Increment after logging the new address
                        //LouPrint("Address:%h\n", AlignmentCheck);
                        memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                        LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
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

void* LouMalloc(size_t BytesToAllocate) {

    return LouMallocEx(BytesToAllocate, BytesToAllocate);

}

void ListUsedAddresses(){

}

uint64_t SearchForMappedAddressSize(uint64_t Address){
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    for(uint32_t i = 0; i < AddressesLogged; i++){
        if(Address == AddressBlock[i].Address){
            uint64_t size = AddressBlock[i].size; 
            LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
            return size;
        }
    }
    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
    return 0x00;
}

typedef struct _LOU_MALLOC_TRACKER{
    uint64_t    Address;
    uint64_t    size;
}LOU_MALLOC_TRACKER, * PLOU_MALLOC_TRACKER;

UNUSED PLOU_MALLOC_TRACKER  AllocationBlocks[100] = {0};
UNUSED static uint64_t      AllocationBlocksConfigured = 0; 
UNUSED static uint32_t      TotalAllocations[100] = {0};
#define CURRENT_ALLOCATION_BLOCK AllocationBlocksConfigured - 1

void* LouMallocEx(size_t BytesToAllocate, uint64_t Alignment) {
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
                
                UNUSED uint64_t AlignmentCheck = (address & ~(Alignment - 1));
                LouKIRQL OldIrql;
                LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);

                PLOU_MALLOC_TRACKER FreeTrack = AllocationBlocks[CURRENT_ALLOCATION_BLOCK];

                FreeTrack = &FreeTrack[TotalAllocations[CURRENT_ALLOCATION_BLOCK]];

                while (1) {
                    if (((AlignmentCheck + Alignment) > limit) || ((AlignmentCheck + BytesToAllocate + Alignment) > limit)) {
                        break;
                    }
                    AlignmentCheck += Alignment;
                    bool addrssSpaceCheck = true;

                    for (uint32_t i = 0; i < AddressesLogged; i++) {
                        uint64_t start = AddressBlock[i].Address;
                        uint64_t end = start + AddressBlock[i].size;

                        // Check if the new allocation overlaps with an existing block
                        if ((AlignmentCheck >= start && AlignmentCheck < end) ||  // Start within an existing block
                            ((AlignmentCheck + BytesToAllocate) > start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                            (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
                            addrssSpaceCheck = false;
                            break;
                        }
                    }
                    if(!addrssSpaceCheck){
                        continue;
                    }
                    for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
                        for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
                            uint64_t start = AllocationBlocks[k][i].Address;
                            uint64_t end = start + AllocationBlocks[k][i].size;

                            // Check if the new allocation overlaps with an existing block
                            if ((AlignmentCheck >= start && AlignmentCheck < end) ||  // Start within an existing block
                                ((AlignmentCheck + BytesToAllocate) > start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                                (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
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
                                //LouPrint("Address:%h\n", AlignmentCheck);
                                memset((void*)AlignmentCheck, 0 , BytesToAllocate);
                                LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
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
                    memset((void*)AlignmentCheck, 0 , BytesToAllocate);                   
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
                    return (void*)AlignmentCheck;
                }

                while(1);
            }
            else if (mmap_entry->type == 2) continue;
            else if (mmap_entry->type == 3) continue;
            else continue;
        }
    }
    while(1);
    return NULL;    
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

typedef struct _LOU_MALLOC_ARRAY_TRACKER{
    ListHeader      List;
    uint64_t        BaseAddress;
    uint64_t        MemberAddress;
}LOU_MALLOC_ARRAY_TRACKER, * PLOU_MALLOC_ARRAY_TRACKER;

static PLOU_MALLOC_ARRAY_TRACKER ArrayTracker = 0;
static uint64_t ArrayTrackerCount = 0;


void* LouMallocArray(size_t Members, size_t MemberSize){
    if(!ArrayTrackerCount){
        ArrayTracker = (PLOU_MALLOC_ARRAY_TRACKER)LouMalloc(sizeof(LOU_MALLOC_ARRAY_TRACKER));
    }

    PLOU_MALLOC_ARRAY_TRACKER TmpTracker = ArrayTracker;

    for(uint64_t i = 0 ; i < ArrayTrackerCount;i++){
        if(TmpTracker->List.NextHeader){
            TmpTracker = (PLOU_MALLOC_ARRAY_TRACKER)TmpTracker->List.NextHeader;
        }
    }
    uint64_t BaseAddress = (uint64_t)LouMalloc(MemberSize); 
    TmpTracker->BaseAddress = BaseAddress; 
    for(uint64_t i = 1 ; i < (Members); i++){
        if(!TmpTracker->List.NextHeader){
            TmpTracker->List.NextHeader = (PListHeader)LouMalloc(sizeof(LOU_MALLOC_ARRAY_TRACKER));
        }
        TmpTracker = (PLOU_MALLOC_ARRAY_TRACKER)TmpTracker->List.NextHeader;
        TmpTracker->BaseAddress = BaseAddress;
        TmpTracker->MemberAddress = (uint64_t)LouMalloc(MemberSize);
    }
    return (void*)BaseAddress;
}

void* LouVMallocEx(size_t BytesToAllocate, uint64_t Alignment){
    uint64_t AlignmentCheck = GetRamSize();
    AlignmentCheck &= ~(Alignment - 1);
    LouKIRQL OldIrql;
    LouKeAcquireSpinLock(&MemmoryMapLock, &OldIrql);
    while (1) {
        AlignmentCheck += Alignment;
        bool addrssSpaceCheck = true;
        for (uint32_t i = 0; i < AddressesLogged; i++) {
            uint64_t start = AddressBlock[i].Address;
            uint64_t end = start + AddressBlock[i].size;

            // Check if the new allocation overlaps with an existing block
            if ((AlignmentCheck >= start && AlignmentCheck < end) ||  // Start within an existing block
                ((AlignmentCheck + BytesToAllocate) > start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                 (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
                addrssSpaceCheck = false;
                break;
            }
        }
        if(!addrssSpaceCheck){
            continue;
        }
        for(uint64_t k = 0; k < AllocationBlocksConfigured; k++){
            for (uint32_t i = 0; i < TotalAllocations[k]; i++) {
                uint64_t start = AllocationBlocks[k][i].Address;
                uint64_t end = start + AllocationBlocks[k][i].size;

                // Check if the new allocation overlaps with an existing block
            if ((AlignmentCheck >= start && AlignmentCheck < end) ||  // Start within an existing block
                ((AlignmentCheck + BytesToAllocate) > start && (AlignmentCheck + BytesToAllocate) <= end) || // End within an existing block
                 (AlignmentCheck <= start && (AlignmentCheck + BytesToAllocate) >= end)) { // Encompasses an existing block
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
                    //LouPrint("Address:%h\n", AlignmentCheck);
                    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
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
        return (void*)AlignmentCheck;
    }

    LouKeReleaseSpinLock(&MemmoryMapLock, &OldIrql);    
    while(1);
    return NULL;
}


typedef struct _MEMORY_CHUNK{
    ListHeader TrackLink;
    uint64_t PAddress;
    uint64_t VAddress;
    uint8_t NumPages;
}MEMORY_CHUNK, * PMEMORY_CHUNK;

typedef struct _KMALLOC_PAGE_TRACK{
    ListHeader      Chain;
    uint64_t        Flags;
    MEMORY_CHUNK    Chunk;
}KMALLOC_PAGE_TRACK, * PKMALLOC_PAGE_TRACK;


typedef struct _KMALLOC_VMEM_TRACK{
    ListHeader  Chain;
    uint64_t    PAddress;
    uint64_t    VAddress;
    uint64_t    size;
}KMALLOC_VMEM_TRACK, * PKMALLOC_VMEM_TRACK;

UNUSED static KMALLOC_PAGE_TRACK    PageTracks;
UNUSED static size_t                PageTracksCount = 1;
UNUSED static KMALLOC_VMEM_TRACK    VMemTracks;
UNUSED static size_t                VMemTracksCount = 0;

uint64_t LouKeMallocFromMapEx(
    uint64_t BytesNeeded,
    uint64_t Alignement,
    uint64_t MapStart,
    uint64_t MapEnd,
    uint64_t MappedTrack,
    PKMALLOC_VMEM_TRACK MappedAddresses
);

void* LouKeMallocEx(
    size_t      AllocationSize,
    size_t      Alignment,
    uint64_t    AllocationFlags
){

    PKMALLOC_PAGE_TRACK TmpTracker = &PageTracks; 
    uint64_t RoundedSize = ROUND_UP64(AllocationSize, MEGABYTE_PAGE);
    uint64_t Pointer = 0;
    size_t i = 0;
    RoundedSize /= MEGABYTE_PAGE;
    uint8_t NeededPages = (uint8_t)RoundedSize;

    while(!Pointer){
        for(; i < PageTracksCount; i++){
            if(TmpTracker->Flags == AllocationFlags){
                goto _LOU_KE_MALLOC_WITH_FLAGS_EX_COMPATIBLE_BLOCK_FOUND;
            }
            if(TmpTracker->Chain.NextHeader){
                TmpTracker = (PKMALLOC_PAGE_TRACK)TmpTracker->Chain.NextHeader;
            }
        }
        TmpTracker->Chain.NextHeader = (PListHeader)LouMalloc(sizeof(KMALLOC_PAGE_TRACK));
        TmpTracker = (PKMALLOC_PAGE_TRACK)TmpTracker->Chain.NextHeader;
        
        TmpTracker->Chunk.PAddress = (uint64_t)LouMalloc(NeededPages * MEGABYTE_PAGE);
        TmpTracker->Chunk.VAddress = (uint64_t)LouVMalloc(NeededPages * MEGABYTE_PAGE);
        TmpTracker->Chunk.NumPages = NeededPages;
        LouKeMapContinuousMemoryBlock(TmpTracker->Chunk.PAddress, TmpTracker->Chunk.VAddress,NeededPages * MEGABYTE_PAGE, AllocationFlags);
        PageTracksCount++;
        _LOU_KE_MALLOC_WITH_FLAGS_EX_COMPATIBLE_BLOCK_FOUND:
        
        Pointer = LouKeMallocFromMapEx(
            AllocationSize,
            Alignment,
            TmpTracker->Chunk.VAddress,
            TmpTracker->Chunk.VAddress + (TmpTracker->Chunk.NumPages * MEGABYTE_PAGE),
            VMemTracksCount,
            &VMemTracks
        );
    }
    

    memset((void*)Pointer,0, AllocationSize);
    VMemTracksCount++;
    return (void*)Pointer;
}

void* LouKeMalloc(
    size_t      AllocationSize,
    uint64_t    AllocationFlags
){
    return LouKeMallocEx(AllocationSize, AllocationSize, AllocationFlags);
}

void LouKeFreeFromMap(
    uint64_t                Address,
    uint64_t*               MappedTrack,
    PKMALLOC_VMEM_TRACK     MappedAddresses
);

void LouKeFree(void* AddressToFree){
    LouKeFreeFromMap(
        (uint64_t)AddressToFree,
        &VMemTracksCount,
        &VMemTracks
    );
}