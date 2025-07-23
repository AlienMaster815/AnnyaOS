#include <LouACPI.h>
#include <acpi.h>

uintptr_t LouKeGetRsdp();

static POOL AcpicaPool = 0x00;

ACPI_STATUS AcpiOsInitialize(){
    AcpicaPool = LouKeCreateDynamicPool(
        16 * MEGABYTE,
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
    return LouKeMemReMap((void*)PhyAddress, (size_t)Length, KERNEL_DMA_MEMORY);
}

void AcpiOsUnmapMemory(
    void*       Address,
    ACPI_SIZE   Length
){
    LouKeMemReleaseReMap(Address);
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

typedef struct _ACPICA_INTERRUPT_TRACKER{
    ListHeader  Peers;
    uint8_t     Isr;
    bool        Used;
}ACPICA_INTERRUPT_TRACKER, * PACPICA_INTERRUPT_TRACKER;

static ACPICA_INTERRUPT_TRACKER Ait = {0};

static void InitializeAcpiInterruptTracker(
    uint8_t Isr
){
    PACPICA_INTERRUPT_TRACKER TmpTrk = &Ait;
    while(TmpTrk->Peers.NextHeader){
        TmpTrk = (PACPICA_INTERRUPT_TRACKER)TmpTrk->Peers.NextHeader;
    }
    TmpTrk->Isr = Isr;
    TmpTrk->Isr = true;
    TmpTrk->Peers.NextHeader = (PListHeader)LouKeMallocType(ACPICA_INTERRUPT_TRACKER, KERNEL_GENERIC_MEMORY);
}

UNUSED static bool CheckAcpicaForInterruptManagement(uint8_t Isr){
    PACPICA_INTERRUPT_TRACKER TmpTrk = &Ait;
    while(TmpTrk->Peers.NextHeader){
        if((TmpTrk->Isr == Isr) && (TmpTrk->Used)){
            return true;
        }
        TmpTrk = (PACPICA_INTERRUPT_TRACKER)TmpTrk->Peers.NextHeader;
    }
    return false;
}

ACPI_STATUS AcpiOsInstallInterruptHandler(
    UINT32 InterruptNumber, 
    ACPI_OSD_HANDLER Handler, 
    void* Context
){
    RegisterInterruptHandler(
        (void(*)(uint64_t))Handler,
        InterruptNumber + 32,
        false,
        (uint64_t)Context
    );
    InitializeAcpiInterruptTracker(InterruptNumber);
    LouPrint("IRQ:%d Installed for ACPI\n", InterruptNumber);
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
    ACPI_PCI_ID *PciId,
    UINT32 Reg,
    UINT64 *Value,
    UINT32 Width
){
    uint16_t Group      = PciId->Segment;
    uint8_t bus         = (uint8_t)PciId->Bus;
    uint8_t device      = (uint8_t)PciId->Device;
    uint8_t func        = (uint8_t)PciId->Function;
    
    if(Group){
        LouPrint("Group:%h\n", Group);
        while(1);
    }

    switch(Width){
        case 8:
            *Value = pciConfigReadByte(Group, bus, device, func, Reg);
            break;
        case 16:
            *Value = pciConfigReadWord(Group, bus, device, func, Reg);
            break;
        case 32:
            *Value = pci_read(Group, bus, device, func, Reg);
            break;
        default:
            return AE_BAD_PARAMETER;
    }

    return AE_OK;
}

ACPI_STATUS AcpiOsWritePciConfiguration(
    ACPI_PCI_ID *PciId,
    UINT32 Reg,
    UINT64 Value,
    UINT32 Width
){
    uint16_t Group      = PciId->Segment;
    uint8_t bus         = (uint8_t)PciId->Bus;
    uint8_t device      = (uint8_t)PciId->Device;
    uint8_t func        = (uint8_t)PciId->Function;

    if(Group){
        LouPrint("Group:%h\n", Group);
        while(1);
    }

    switch(Width){
        case 8:
            pciConfigWriteByte(Group, bus, device, func, Reg, (uint8_t)Value);
            break;
        case 16:
            pciConfigWriteWord(Group, bus, device, func, Reg, (uint16_t)Value);
            break;
        case 32:
            write_pci(Group, bus, device, func, Reg, (uint32_t)Value);
            break;
        default:
            return AE_BAD_PARAMETER;
    }

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

void AcpiFadtSciInterruptHandler(uint64_t Context);

