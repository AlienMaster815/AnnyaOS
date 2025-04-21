
#include <ACPICA/acpi.h>
#include <ACPICA/accommon.h>

#include <LouAPI.h>

uintptr_t GetRsdpMaster();

ACPI_STATUS
AcpiOsWaitSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units,
    UINT16                  Timeout
){
    for(uint32_t i = 0 ; i < Units; i++){
        SemaphoreLock((semaphore_t*)Handle);
    }
    return AE_OK;
}

ACPI_STATUS
AcpiOsSignalSemaphore (
    ACPI_SEMAPHORE          Handle,
    UINT32                  Units
){
    for (uint32_t i = 0; i < Units; i++) {
        SemaphoreUnlock((semaphore_t*)Handle);
    }
    return AE_OK;
}




ACPI_STATUS
AcpiOsInitialize (){

    //TODO: make subsystems that are 
    //required by ACPICA ready for
    //use 

    return AE_OK;
}

int LouPrint_s(char* format, va_list args);

void ACPI_INTERNAL_VAR_XFACE
AcpiOsPrintf(
    const char *Format,
    ...
){
    va_list args;
    va_start(args, Format);
    LouPrint_s((string)Format, args);
    va_end(args);
}

void
AcpiOsVprintf (
    const char              *Format,
    va_list                 Args
){
    //LouPrint("AcpiOsVprintf()\n");
    LouPrint_s((string)Format, Args);
}

ACPI_STATUS
AcpiOsTerminate(){
    LouPrint("AcpiOsTerminate\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsPurgeCache (
    ACPI_CACHE_T *Cache
){
    if (!Cache) {
        return AE_BAD_PARAMETER;
    }
    memset(((PLMPOOL_DIRECTORY)Cache)->PoolBitMap, 0, ROUND_UP64(((PLMPOOL_DIRECTORY)Cache)->PoolSize, 8) / 8);
    return AE_OK;
}

ACPI_STATUS
AcpiOsReleaseObject (
    ACPI_CACHE_T            *Cache,
    void                    *Object
){
    LouPrint("AcpiOsReleaseObject\n");
    while(1);
    return 0x00;
}

void *
AcpiOsAcquireObject (
ACPI_CACHE_T *Cache
){
    void* Object = LouKeMallocFromFixedPool((POOL)Cache);
    if (Object) {
        memset(Object, 0, ((POOL)Cache)->ObjectSize); // Optional but helpful
    }
    return Object;
}

uint64_t LouKeGetThreadIdentification();

ACPI_THREAD_ID
AcpiOsGetThreadId (){
    return LouKeGetThreadIdentification();
}

void
AcpiOsFree(void* Memory){
    LouKeFree(Memory);
}

void
AcpiOsDeleteLock (ACPI_SPINLOCK Handle){
    LouPrint("AcpiOsDeleteLock\n");
    while(1);
}

ACPI_STATUS
AcpiOsDeleteSemaphore (ACPI_SEMAPHORE Handle){
    LouPrint("AcpiOsDeleteSemaphore\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsCreateSemaphore (
    UINT32                  MaxUnits,
    UINT32                  InitialUnits,
    ACPI_SEMAPHORE          *OutHandle
){
    semaphore_t* NewSemaphore = (semaphore_t*)LouKeMallocEx(sizeof(semaphore_t), GET_ALIGNMENT(semaphore_t), KERNEL_GENERIC_MEMORY);
    if(!NewSemaphore){
        return AE_NO_MEMORY;
    }
    SemaphoreInitialize(NewSemaphore, (atomic_t)MaxUnits);
    SetAtomicValue(&NewSemaphore->Count, InitialUnits);
    *OutHandle = (ACPI_SEMAPHORE)NewSemaphore;
    return AE_OK;
}

void
AcpiOsUnmapMemory (
    void        *LogicalAddress,
    ACPI_SIZE    Size
){
    uint64_t AlignedAddress = (uint64_t)LogicalAddress & ~(KILOBYTE_PAGE - 1);
    uint64_t Offset = (uint64_t)LogicalAddress - AlignedAddress;
    uint64_t TotalSize = ROUND_UP64(Size + Offset, KILOBYTE_PAGE);
    LouKeUnMapContinuousMemoryBlock(AlignedAddress, TotalSize);
    LouFree((void*)AlignedAddress);
}

void *
AcpiOsMapMemory (
    ACPI_PHYSICAL_ADDRESS   Where,
    ACPI_SIZE               Length
){
    //Round Up For Sanity
    uint64_t Where2 = (uint64_t)Where;
    Where2 &= ~(KILOBYTE_PAGE - 1);
    Length += Where - Where2;
    void* to = LouVMallocEx(ROUND_UP64(Length, KILOBYTE_PAGE), KILOBYTE_PAGE);
    LouKeMapContinuousMemoryBlock((uint64_t)Where2, (uint64_t)to, ROUND_UP64(Length, KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
    return (void*)((uint64_t)to + (Where - Where2));
}

ACPI_STATUS
AcpiOsCreateLock (ACPI_SPINLOCK *OutHandle){
    spinlock_t* NewSpinlock = (spinlock_t*)LouKeMallocEx(sizeof(spinlock_t), GET_ALIGNMENT(spinlock_t), KERNEL_GENERIC_MEMORY);
    if(!NewSpinlock){
        return AE_NO_MEMORY;
    }   
    *OutHandle = (ACPI_SPINLOCK)NewSpinlock;
    return AE_OK;
}

void
AcpiOsReleaseLock (
    ACPI_SPINLOCK           Handle,
    ACPI_CPU_FLAGS          Flags
){
    LouKeReleaseSpinLock((spinlock_t*)Handle, (LouKIRQL*)&Flags);
}

ACPI_STATUS
AcpiOsDeleteCache (ACPI_CACHE_T *Cache){
    LouPrint("AcpiOsDeleteCache\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsCreateCache (
    char                    *CacheName,
    UINT16                  ObjectSize,
    UINT16                  MaxDepth,
    ACPI_CACHE_T            **ReturnCache
){
    ACPI_CACHE_T* Result = (ACPI_CACHE_T*)LouKeCreateFixedPool(
        MaxDepth,
        ObjectSize,
        CacheName,
        0,
        KERNEL_GENERIC_MEMORY
    );
    *ReturnCache = Result;
    if(!Result){
        return AE_NO_MEMORY;
    }
    return AE_OK;
}

ACPI_CPU_FLAGS
AcpiOsAcquireLock (ACPI_SPINLOCK Handle){
    LouKIRQL Irql;
    LouKeAcquireSpinLock((spinlock_t*)Handle, &Irql);
    return (ACPI_CPU_FLAGS)Irql;
}


void *
AcpiOsAllocate (ACPI_SIZE Size){
    return LouKeMalloc(Size, KERNEL_GENERIC_MEMORY);
}

ACPI_PHYSICAL_ADDRESS
AcpiOsGetRootPointer(){
    return GetRsdpMaster();
}

UINT64
AcpiOsGetTimer (){
    LouPrint("AcpiOsGetTimer\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsSignal (
    UINT32                  Function,
    void                    *Info
){
    LouPrint("AcpiOsSignal\n");
    while(1);
    return 0x00;
}


ACPI_STATUS
AcpiOsPhysicalTableOverride (
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_PHYSICAL_ADDRESS   *NewAddress,
    UINT32                  *NewTableLength
){
    *NewAddress = 0;         
    *NewTableLength = 0;     
    return AE_OK;            
}

ACPI_STATUS
AcpiOsTableOverride (
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_TABLE_HEADER       **NewTable
){
    *NewTable = NULL;
    return AE_OK;
}


ACPI_STATUS
AcpiOsPredefinedOverride (
    const ACPI_PREDEFINED_NAMES *InitVal,
    ACPI_STRING                 *NewVal
){
    *NewVal = NULL;
    return AE_OK;
}

void
AcpiOsSleep(UINT64 Milliseconds){
    LouPrint("AcpiOsSleep\n");
    while(1);
}

void
AcpiOsStall (UINT32 Microseconds){
    LouPrint("AcpiOsStall\n");
    while(1);
}


ACPI_STATUS
AcpiOsWritePciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  Value,
    UINT32                  Width
){
    LouPrint("AcpiOsWritePciConfiguration\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsReadPciConfiguration (
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  *Value,
    UINT32                  Width
){
    LouPrint("AcpiOsReadPciConfiguration\n");
    while(1);
    return 0x00;
}


ACPI_STATUS
AcpiOsWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width
){
    LouPrint("AcpiOsWritePort\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsReadPort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  *Value,
    UINT32                  Width
){
    LouPrint("AcpiOsReadPort\n");
    while(1);
    return 0x00;
}


void
AcpiOsWaitEventsComplete(){

    LouPrint("AcpiOsWaitEventsComplete\n");
    while(1);
}

ACPI_STATUS
AcpiOsInstallInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine,
    void                    *Context
){
    LouPrint("AcpiOsInstallInterruptHandler\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsExecute (
    ACPI_EXECUTE_TYPE       Type,
    ACPI_OSD_EXEC_CALLBACK  Function,
    void                    *Context
){
    LouPrint("AcpiOsExecute\n");
    return 0x00;
}

ACPI_STATUS
AcpiOsRemoveInterruptHandler (
    UINT32                  InterruptNumber,
    ACPI_OSD_HANDLER        ServiceRoutine
){

    LouPrint("AcpiOsRemoveInterruptHandler\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsEnterSleep (
    UINT8                   SleepState,
    UINT32                  RegaValue,
    UINT32                  RegbValue
){

    LouPrint("AcpiOsEnterSleep\n");
    while(1);
    return 0x00;
}

ACPI_STATUS
AcpiOsReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width
){

    LouPrint("AcpiOsReadMemory\n");
    while(1);
    return 0x00;
}
ACPI_STATUS
AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width
){
    LouPrint("AcpiOsWriteMemory\n");
    while(1);
    return 0x00;
}

void InitializeLouACPICA(){
    AcpiInitializeSubsystem();
    AcpiInitializeTables(NULL, 16, FALSE);
    AcpiInitializeObjects(0x00000000);
}