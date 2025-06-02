#include <LouACPI.h>
#include <acpi.h>

uintptr_t LouKeGetRsdp();

static POOL AcpicaPool = 0x00;

ACPI_STATUS AcpiOsInitialize(){
    AcpicaPool = LouKeCreateDynamicPool(
        32 * MEGABYTE,
        KILOBYTE_PAGE,
        "ACPICAPool",
        0,
        KERNEL_GENERIC_MEMORY
    );

    return AE_OK;
}

ACPI_STATUS AcpiOsTerminate(){

    return AE_OK;
}

ACPI_PHYSICAL_ADDRESS AcpiOsGetRootPointer(){
    return (ACPI_PHYSICAL_ADDRESS)LouKeGetRsdp();
}

ACPI_STATUS AcpiOsPredefinedOverride(
    const ACPI_PREDEFINED_NAMES*    PreDefinedNames, 
    ACPI_STRING*                    NewValue
){
    *NewValue = NULL; 
    return AE_OK;
}

ACPI_STATUS AcpiOsTableOverride(
    ACPI_TABLE_HEADER*  ExistingTable,
    ACPI_TABLE_HEADER** NewTable
){
    *NewTable = NULL; 
    return AE_OK;
}

ACPI_STATUS AcpiOsPhysicalTableOverride(
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_PHYSICAL_ADDRESS   *NewAddress,
    UINT32                  *NewTableLength
){
    *NewAddress = 0;
    *NewTableLength = 0;
    return AE_OK;
}

void* AcpiOsMapMemory(
    ACPI_PHYSICAL_ADDRESS   PhyAddress,
    ACPI_SIZE               Length
){
    uint64_t PhyCheck = 0x00;
    RequestPhysicalAddress((uint64_t)PhyAddress, &PhyCheck);
    if(PhyCheck == (uint64_t)PhyAddress){
        return (void*)PhyAddress;
    }

    LouPrint("AcpiOsMapMemory()\n");
    while(1);
}

void AcpiOsUnmapMemory(
    void*       PhyAddress,
    ACPI_SIZE   Length
){
    uint64_t PhyCheck = 0x00;
    RequestPhysicalAddress((uint64_t)PhyAddress, &PhyCheck);
    if(PhyCheck == (uint64_t)PhyAddress){
        return;
    }
    LouPrint("AcpiOsUnmapMemory()\n");
    while(1);
}

ACPI_STATUS AcpiOsGetPhysicalAddress(
    void*                   VirtualAddress,
    ACPI_PHYSICAL_ADDRESS*  PhyAddress
){
    LouPrint("AcpiOsGetPhysicalAddress()\n");
    while(1);
}

void* AcpiOsAllocate(ACPI_SIZE Size){
    return LouKeMallocFromDynamicPool(AcpicaPool, Size);
}

void AcpiOsFree(void* Memory){
    LouKeFreeFromDynamicPool(AcpicaPool, Memory);
}

BOOLEAN AcpiOsReadable(
    void* Memory, 
    ACPI_SIZE Length
){
    LouPrint("AcpiOsReadable()\n");
    while(1);
}

BOOLEAN AcpiOsWriteable(
    void* Memory, 
    size_t Length
){
    LouPrint("AcpiOsWriteable()\n");
    while(1);
}

uint64_t LouKeGetThreadIdentification();

ACPI_THREAD_ID AcpiOsGetThreadId(){
    return (ACPI_THREAD_ID)LouKeGetThreadIdentification();
}

ACPI_STATUS AcpiOsExecute(ACPI_EXECUTE_TYPE Type, ACPI_OSD_EXEC_CALLBACK Function, void* Context){
    LouPrint("AcpiOsExecute\n");
    while(1);
    return AE_OK;
}

void AcpiOsSleep(UINT64 Ms){
    LouPrint("AcpiOsSleep()\n");
    while(1);
    sleep((size_t)Ms);
}

void AcpiOsStall(UINT32 Mcs){
    LouPrint("AcpiOsStall()\n");
    while(1);   
    if(Mcs > 1000){
        sleep(Mcs / 1000);
    }
}

ACPI_STATUS AcpiOsCreateSemaphore(
    UINT32 MaxUnits, 
    UINT32 InitialUnits, 
    ACPI_SEMAPHORE* OutHandle
){
    *OutHandle = (ACPI_SEMAPHORE)LouKeCreateSemaphore(InitialUnits, MaxUnits);
    return AE_OK;
}

ACPI_STATUS AcpiOsDeleteSemaphore(
    ACPI_SEMAPHORE Handle
){  
    LouPrint("AcpiOsDeleteSemaphore()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS AcpiOsWaitSemaphore(
    ACPI_SEMAPHORE Handle,
    UINT32 Units,
    UINT16 Timeout
){
    for(uint32_t i = 0 ; i < Units; i++){
        SemaphoreLock((semaphore_t*)Handle);
    }
    return AE_OK;
}

ACPI_STATUS AcpiOsSignalSemaphore(
    ACPI_SEMAPHORE Handle,
    UINT32 Units
){
    for(uint32_t i = 0 ; i < Units; i++){
        SemaphoreUnlock((semaphore_t*)Handle);
    }
    return AE_OK;
}

ACPI_STATUS AcpiOsCreateLock(
    ACPI_SPINLOCK* OutHandle
){
    *OutHandle = (ACPI_SPINLOCK)LouKeMallocType(spinlock_t, KERNEL_GENERIC_MEMORY);
    return AE_OK;
}

void AcpiOsDeleteLock(
    ACPI_SPINLOCK Handle
){
    LouPrint("AcpiOsDeleteLock()\n");
    while(1);
}

ACPI_CPU_FLAGS AcpiOsAcquireLock(
    ACPI_SPINLOCK Handle
){
    LouKIRQL Irql = 0x00;
    LouKeAcquireSpinLock((spinlock_t*)Handle, &Irql);
    return (ACPI_CPU_FLAGS)Irql;
}

void AcpiOsReleaseLock(
    ACPI_SPINLOCK Handle,
    ACPI_CPU_FLAGS Flags
){
    LouKIRQL Irql = (LouKIRQL)Flags;
    LouKeReleaseSpinLock((spinlock_t*)Handle, &Irql);
}

ACPI_STATUS AcpiOsInstallInterruptHandler(
    UINT32 InterruptNumber, 
    ACPI_OSD_HANDLER Handler, 
    void* Context
){
    RegisterInterruptHandler(
        (void(*)(uint64_t))Handler,
        InterruptNumber,
        false,
        (uint64_t)Context
    );
    return AE_OK;
}

ACPI_STATUS AcpiOsRemoveInterruptHandler(
    UINT32 InterruptNumber, 
    ACPI_OSD_HANDLER Handler
){  
    LouPrint("AcpiOsRemoveInterruptHandler()\n");
    while(1);
    return AE_OK;
}

int LouPrint_s(char* format, va_list args);

void AcpiOsPrintf(const char* Format, ...){
    //va_list Args;
    //va_start(Args, Format);
    //LouPrint_s((string)Format, Args);
    //va_end(Args);
}

void AcpiOsVprintf(const char* Format,va_list Args){
    //LouPrint_s((string)Format, Args);
}


ACPI_STATUS AcpiOsEnterSleep(
    UINT8                   SleepState,
    UINT32                  RegaValue,
    UINT32                  RegbValue
){
    LouPrint("AcpiOsEnterSleep()\n");
    while(1);
    return AE_OK;   
}

void AcpiOsWaitEventsComplete(){
    LouPrint("AcpiOsWaitEventsComplete()\n");
    while(1);
}

ACPI_STATUS AcpiOsReadPciConfiguration(
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  *Value,
    UINT32                  Width
){
    LouPrint("AcpiOsReadPciConfiguration()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS AcpiOsWritePciConfiguration(
    ACPI_PCI_ID             *PciId,
    UINT32                  Reg,
    UINT64                  Value,
    UINT32                  Width
){
    LouPrint("AcpiOsWritePciConfiguration()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS AcpiOsWritePort(
    ACPI_IO_ADDRESS Address,
    UINT32 Value,
    UINT32 Width
){
    switch (Width) {
        case 8:
            outb((uint16_t)Address, (uint8_t)Value);
            break;
        case 16:
            outw((uint16_t)Address, (uint16_t)Value);
            break;
        case 32:
            outl((uint16_t)Address, (uint32_t)Value);
            break;
        default:
            return AE_BAD_PARAMETER;
    }

    return AE_OK;
}

ACPI_STATUS AcpiOsReadPort(
    ACPI_IO_ADDRESS Address,
    UINT32 *Value,
    UINT32 Width
){
    if (!Value) {
        return AE_BAD_PARAMETER;
    }

    switch (Width) {
        case 8:
            *Value = inb((uint16_t)Address);
            break;
        case 16:
            *Value = inw((uint16_t)Address);
            break;
        case 32:
            *Value = inl((uint16_t)Address);
            break;
        default:
            return AE_BAD_PARAMETER;
    }

    return AE_OK;
}


uint64_t GetCurrentTimeIn100ns();

UINT64 AcpiOsGetTimer(){
    return (UINT64)GetCurrentTimeIn100ns();
}

ACPI_STATUS AcpiOsSignal (
    UINT32                  Function,
    void                    *Info
){
    LouPrint("AcpiOsSignal()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS
AcpiOsWriteMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  Value,
    UINT32                  Width
){
    LouPrint("AcpiOsWriteMemory()\n");
    while(1);
    return AE_OK;
}

ACPI_STATUS AcpiOsReadMemory (
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT64                  *Value,
    UINT32                  Width
){
    LouPrint("AcpiOsReadMemory()\n");
    while(1);
    return AE_OK;
}


void LouKeInitializeAcpicaSubSystem(){
    ACPI_STATUS Status;

    LouPrint("Initializing Acpica Subsystem\n");

    Status = AcpiInitializeSubsystem();
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiInitializeSubsystem failed\n");
        return;
    }

    LouPrint("Initializing Tables\n");
    Status = AcpiInitializeTables(NULL, LouKeAcpiGetTableCount(), FALSE);
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiInitializeTables failed\n");
        return;
    }

    LouPrint("Loading Tables\n");
    Status = AcpiLoadTables();
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiLoadTables failed\n");
        return;
    }
    LouPrint("Enabling System\n");
    Status = AcpiEnableSubsystem(ACPI_FULL_INITIALIZATION);
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiEnableSubsystem failed\n");
        return;
    }
    LouPrint("Initializing Objects\n");
    Status = AcpiInitializeObjects(ACPI_FULL_INITIALIZATION);
    if (ACPI_FAILURE(Status)) {
        LouPrint("AcpiInitializeObjects failed\n");
        return;
    }

    LouPrint("LouKeInitializeAcpicaSubSystem() STATUS_SUCCESS\n");
}    
