#include <LouACPI.h>

typedef struct _LOU_ACPI_TABLE_TRACK{
    ListHeader      TableList;
    void*           TableEntry;
}LOU_ACPI_TABLE_TRACK, * PLOU_ACPI_TABLE_TRACK;

static LOU_ACPI_TABLE_TRACK TableTracks = {0};
static size_t TableCount = 0;
static mutex_t AcpiTableTrackMutex = {0};

size_t LouKeAcpiGetTableCount(){
    return TableCount;
}

static PLOU_ACPI_TABLE_TRACK AllocateNewTableTrack(){
    PLOU_ACPI_TABLE_TRACK TmpTrack = &TableTracks;
    for(size_t i = 0 ; i < TableCount; i++){
        if(!TmpTrack->TableList.NextHeader){
            TmpTrack->TableList.NextHeader = (PListHeader)LouKeMallocType(LOU_ACPI_TABLE_TRACK, KERNEL_GENERIC_MEMORY);
        }
        TmpTrack = (PLOU_ACPI_TABLE_TRACK)TmpTrack->TableList.NextHeader;
    } 
    TableCount++;
    return TmpTrack;
}

//unused for now untill used
UNUSED static void FreeTableTrack(PLOU_ACPI_TABLE_TRACK Track){
    PLOU_ACPI_TABLE_TRACK TmpTrack = &TableTracks;
    for(size_t i = 0 ; i < TableCount; i++){
        if((uint64_t)TmpTrack->TableList.NextHeader == (uint64_t)Track){
            TmpTrack->TableList.NextHeader = ((PLOU_ACPI_TABLE_TRACK)TmpTrack->TableList.NextHeader)->TableList.NextHeader;
            LouKeFree(Track);
        }
        TmpTrack = (PLOU_ACPI_TABLE_TRACK)TmpTrack->TableList.NextHeader;
    }
    if(TableCount > 0){ //sanity check
        TableCount--;
    }
}

static bool AcpiConflict(void* Table){
    PLOU_ACPI_TABLE_TRACK TmpTrack = &TableTracks;
    for(size_t i = 0 ; i < TableCount; i++){
        if(((uint64_t)Table == (uint64_t)TmpTrack->TableEntry) || (strncmp((string)Table, (string)TmpTrack->TableEntry, 4) == 0)){
            return true;
        }
        TmpTrack = (PLOU_ACPI_TABLE_TRACK)TmpTrack->TableList.NextHeader;
    }
    return false;
}

static void LouACPIHandleSpecificTableInitialization(void* TableBase){
    //edge cases for specific tables
    IF_ACPI_TABLE_IS((string)TableBase, FIXED_ACPI_DESCRIPTION){
        LouKeInitializeFixedAcpiDescriptionTable((void*)(uintptr_t)TableBase);
    } else IF_ACPI_TABLE_IS((string)TableBase, FIRMWARE_ACPI_CONTROL_STRUCTURE){
        LouKeAcpiInitializeFacs((void*)(uintptr_t)TableBase);
    } else IF_ACPI_TABLE_IS((string)TableBase, DIFFERENTIATED_SYSTEM_DESCRIPTION){
        LouKeAcpiInitializeDsdt((void*)(uintptr_t)TableBase);
    }


}

void LouKeInitializeLouACPITable(void* TableBase){
    uint64_t AddressCheck = 0;
    PTABLE_DESCRIPTION_HEADER TmpHeader = 0;
    RequestPhysicalAddress((uint64_t)(uintptr_t)TableBase, &AddressCheck);
    if(AddressCheck != (uint64_t)TableBase){
        LouKeMapContinuousMemoryBlock((uint64_t)(uintptr_t)TableBase & ~(KILOBYTE_PAGE - 1), (uint64_t)(uintptr_t)TableBase & ~(KILOBYTE_PAGE - 1), KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY);
        if((uint64_t)(uintptr_t)TableBase >= (65 * MEGABYTE)){ //if system is in the memory allocations area then map it
            TmpHeader = (PTABLE_DESCRIPTION_HEADER)(uint64_t)(uintptr_t)TableBase;
            EnforceSystemMemoryMap((uint64_t)TmpHeader, TmpHeader->Length);
        }
    }
    MutexLock(&AcpiTableTrackMutex);
    if(AcpiConflict(TableBase)){
        MutexUnlock(&AcpiTableTrackMutex);
        return;
    }
    LouKeAcpiPrintTableSignature(TableBase);
    PLOU_ACPI_TABLE_TRACK NewTrack = AllocateNewTableTrack();    
    NewTrack->TableEntry = TableBase;
    MutexUnlock(&AcpiTableTrackMutex);
    //After adding a table to the database there
    //might be tables linked or specific data
    //that needs to be handled we will do that
    //in the static function below
    LouACPIHandleSpecificTableInitialization(TableBase);
}


void* LouKeAquireAcpiTable(string TableName){
    PLOU_ACPI_TABLE_TRACK TmpTrack = &TableTracks;
    for(size_t i = 0 ; i < TableCount; i++){
        if(strncmp((string)TableName, (string)TmpTrack->TableEntry, 4) == 0){
            return TmpTrack->TableEntry;
        }
        TmpTrack = (PLOU_ACPI_TABLE_TRACK)TmpTrack->TableList.NextHeader;
    }
    return 0x00;
}