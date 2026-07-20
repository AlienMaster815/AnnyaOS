#define APIC_MAIN
#include "ApicInternals.h"
#include <LouACPI.h>

LOUSTATUS ApicHalConfigureSpriousVector(ULONG Processor);

typedef enum{
    LOCAL_APIC_ACPI_ENTRY_VERSION_X1LOCAL_STRUCT = 0,
    LOCAL_APIC_ACPI_ENTRY_VERSION_XSLOCAL_STRUCT = 7,
    LOCAL_APIC_ACPI_ENTRY_VERSION_X2LOCAL_STRUCT = 9,
}LOCAL_APIC_ACPI_ENTRY_VERSION;

typedef union _LOCAL_APIC_ACPI_ENTRY{
    MADT_ICS_PROCESSOR_LOCAL_APIC_STRUCTURE     X1Entry;
    MADT_ICS_LOCAL_SAPIC_STRUCTURE              SapicEntry;
    MADT_ICS_LOCAL_X2_APIC_STRUCTURE            X2Entry;
}LOCAL_APIC_ACPI_ENTRY, * PLOCAL_APIC_ACPI_ENTRY;

typedef struct _LOCAL_APIC_INIT_LIST_ITEM{
    ListHeader                      Peers;
    LOCAL_APIC_ACPI_ENTRY_VERSION   EntryVersion;
    UINT32                          ProcessorID;
    PLOCAL_APIC_ACPI_ENTRY          Entry;
}LOCAL_APIC_INIT_LIST_ITEM, * PLOCAL_APIC_INIT_LIST_ITEM;

typedef enum {
    IO_APIC_ACPI_ENTRY_VERSION_IO_APIC = 1,
    IO_APIC_ACPI_ENTRY_VERSION_IO_SAPIC = 6,
}IO_APIC_ACPI_ENTRY_VERSION;

typedef union _IO_APIC_INIT_LIST_ITEM_ENTRY{
    MADT_ICS_IO_APIC_STRUCTURE  IoApicEntry;
    MADT_ICS_IO_SAPIC_STRUCTURE IoSapicEntry;
}IO_APIC_INIT_LIST_ITEM_ENTRY, * PIO_APIC_INIT_LIST_ITEM_ENTRY;

typedef struct _IO_APIC_INIT_LIST_ITEM{
    ListHeader                              Peers;
    IO_APIC_ACPI_ENTRY_VERSION              EntryVersion;
    UINT32                                  ApicID;
    PIO_APIC_INIT_LIST_ITEM_ENTRY           Entry;
}IO_APIC_INIT_LIST_ITEM, * PIO_APIC_INIT_LIST_ITEM;

typedef struct _INTERRUPT_SOURCE_OVERIDE_ENTRY{
    ListHeader                                      Peers;
    PMADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE    Overide;
}INTERRUPT_SOURCE_OVERIDE_ENTRY, * PINTERRUPT_SOURCE_OVERIDE_ENTRY;

typedef struct _NMI_SOURCE_OVERIDE_ENTRY{
    ListHeader                                          Peers;
    PMADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE   Overide;
}NMI_SOURCE_OVERIDE_ENTRY, * PNMI_SOURCE_OVERIDE_ENTRY;

typedef enum{
    X1_APIC_LOCAL_NMI_OVERIDE = 4,
    X2_APIC_LOCAL_NMI_OVERIDE = 0x0A,
}LOCAL_NMI_OVERIDE_ENTRY_VERSION;

typedef union{
    MADT_ICS_LOCAL_APIC_NMI_STRUCTURE       X1Entry;
    MADT_ICS_LOCAL_X2_APIC_NMI_STRUCTURE    X2Entry;
}LOCAL_NMI_OVERIDE_ENTRY, * PLOCAL_NMI_OVERIDE_ENTRY;

typedef struct _LOCAL_NMI_OVERIDE_ITEM{
    ListHeader                      Peers;
    LOCAL_NMI_OVERIDE_ENTRY_VERSION EntryVersion;
    PLOCAL_NMI_OVERIDE_ENTRY        Entry;
    UINT32                          ProcessorID;
    UINT8                           LocalInterrupt;
}LOCAL_NMI_OVERIDE_ITEM, * PLOCAL_NMI_OVERIDE_ITEM;

typedef struct _PLATFORM_INTERRUPT_ENTRY{
    ListHeader                                      Peers;
    PMADT_ICS_PLATFORM_INTERRUPT_SOURCE_STRUCTURE   Source;
}PLATFORM_INTERRUPT_ENTRY, * PPLATFORM_INTERRUPT_ENTRY;

static PMADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE AddressOveride = 0x00;
static PMULTIPLE_APIC_DESCRIPTION_TABLE MadtTable = 0x00;
static BOOLEAN X2ApicSupport = false;
KERNEL_EXPORT LOUSTATUS LouKeInitializeIpicSubsystem(SIZE Processors);
KERNEL_EXPORT void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx);
PPER_PROCESSOR_APIC_DATA PerProcessorApicData = 0x00;
KERNEL_EXPORT void LouKeSignalApicSubsystemInitialized();
KERNEL_EXPORT UINT64 GetPageBase();

static SIZE IoApicCount = 0;

static BOOLEAN ApicDebugOn = false;

static ListHeader LocalApicInitList = {0};
static ListHeader IoApicInitList = {0};
static ListHeader IntOverideList = {0};
static ListHeader NmiOverideList = {0};
static ListHeader LocalNmiOverideList = {0};
static ListHeader PlatformSourceList = {0};

KERNEL_EXPORT
size_t LouKeGetBootDeviceSize(size_t Index);

KERNEL_EXPORT void LouKeInitializeSmpLouPrint();
KERNEL_EXPORT UINT64 LouKeGetMultibootTrampolineEntrance();

static LOUSTATUS InitializeSmpTrampoline(){
    WORD LoadOrder = 0x00;
    PVOID Key = LouKeOpenRegistryHandle(
        L"KERNEL_DEFAULT_CONFIG\\Subsystems\\Smp",
        0x00
    );
    if(!Key){
        return STATUS_UNSUCCESSFUL;
    }

    Key = LouKeOpenRegistryHandle(
        L"LoadOrder",
        Key
    );

    if(!Key){
        return STATUS_UNSUCCESSFUL;
    }
    LouKeReadRegistryWordValue(Key, &LoadOrder);
        
    void* DriverBase = LouKeGetBootDevice(LoadOrder);  
    SIZE DriverSize = LouKeGetBootDeviceSize(LoadOrder);

    PVOID TrampolineArea = (PVOID)0x8000;
    LouKeMapContinuousMemoryBlock((UINT64)(UINTPTR)TrampolineArea, (UINT64)(UINTPTR)TrampolineArea, ROUND_UP64(4096 + ROUND_UP64(DriverSize, 4096) + sizeof(LKSEB), KILOBYTE_PAGE), KERNEL_DMA_MEMORY);
    memcpy((PVOID)(UINT8*)TrampolineArea, DriverBase, DriverSize);
    UINT16  LksebOffset = ROUND_UP64(DriverSize, 4096) + 4096;
    UINT16  BootStackOffset = LksebOffset - 16;
    UINT16* StackEntry = (UINT16*)((UINT8*)TrampolineArea + BootStackOffset);
    UINT8* MovBxInstruction = (UINT8*)TrampolineArea;
    *StackEntry = (UINT16)((UINTPTR)(UINT8*)TrampolineArea + LksebOffset);
    MovBxInstruction[2] = (UINT16)(UINTPTR)(UINT8*)StackEntry & 0xFF;
    MovBxInstruction[3] = ((UINT16)(UINTPTR)(UINT8*)StackEntry >> 8) & 0xFF;
    
    PLKSEB TrampolineLkseb = (PLKSEB)(UINT8*)(UINTPTR)((UINTPTR)(UINT8*)TrampolineArea + LksebOffset);
    memset(TrampolineLkseb, 0, sizeof(LKSEB));
    PLKSEBEX LksebEx = (PLKSEBEX)(UINT8*)(UINTPTR)((UINTPTR)(UINT8*)LouGeneralAllocateMemoryUnder1Gig(sizeof(LKSEBEX), 4096));
    if(!LksebEx){
        LouPrint("Unable To Initialize Smp Subsystem\n");
        while(1);
    }
    TrampolineLkseb->KernelApEntry = (UINT64)LouKeGetMultibootTrampolineEntrance();
    TrampolineLkseb->KernelPml4 = GetPageBase();
    
    TrampolineLkseb->Gdt32[0] = 0x0000000000000000ULL;
    TrampolineLkseb->Gdt32[1] = 0x00CF9A000000FFFFULL;
    TrampolineLkseb->Gdt32[2] = 0x00CF92000000FFFFULL;

    TrampolineLkseb->Gdt64[0] = 0x0000000000000000ULL;
    TrampolineLkseb->Gdt64[1] = 0x00AF9A000000FFFFULL;
    TrampolineLkseb->Gdt64[2] = 0x00AF92000000FFFFULL;
    TrampolineLkseb->Gdt64[3] = 0x00A09A000000FFFFULL;
    TrampolineLkseb->Gdt64[4] = 0x00A092000000FFFFULL;
    TrampolineLkseb->Gdt64[5] = 0x0000000000000000ULL;
    TrampolineLkseb->Gdt64[6] = 0x0000000000000000ULL;

    TrampolineLkseb->GDTP32[0] = (8 * 3) - 1;
    TrampolineLkseb->GDTP32[1] = ((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt32) & UINT16_MAX;
    TrampolineLkseb->GDTP32[2] = (((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt32) >> 16) & UINT16_MAX;

    TrampolineLkseb->BootStack = (UINT16)(UINTPTR)(UINT8*)TrampolineArea + BootStackOffset;

    TrampolineLkseb->LKSEBEX = (UINT32)((UINTPTR)(UINT8*)LksebEx - KSpaceBase) & UINT32_MAX;
    TrampolineLkseb->StackPointer = (((((UINT64)(UINTPTR)(UINT8*)LouGeneralAllocateMemoryUnder1Gig(4096, 4096))) - KSpaceBase) & UINT32_MAX) + (4096 - 16);
    if(!TrampolineLkseb->StackPointer){
        LouPrint("Unable To Initialize Smp Subsystem\n");
        while(1);
    }


    TrampolineLkseb->GDTP64[0] = (8 * 7) - 1;
    TrampolineLkseb->GDTP64[1] =  ((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt64) & UINT16_MAX;
    TrampolineLkseb->GDTP64[2] = (((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt64) >> 16) & UINT16_MAX;
    TrampolineLkseb->GDTP64[3] = (((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt64) >> 32) & UINT16_MAX;
    TrampolineLkseb->GDTP64[4] = (((UINT64)(UINTPTR)(UINT8*)TrampolineLkseb->Gdt64) >> 48) & UINT16_MAX;

    PLKSEBEX LksebExPhy = (PLKSEBEX)((UINTPTR)(UINT8*)LksebEx - KSpaceBase); 

    LksebEx->Pml4[0] = (UINT64)(UINTPTR)(UINT8*)LksebExPhy->Pml3Low | 0b111;
    LksebEx->Pml4[256] = (UINT64)(UINTPTR)(UINT8*)LksebExPhy->Pml3High | 0b111;
    LksebEx->Pml3Low[0] = (UINT64)(UINTPTR)(UINT8*)LksebExPhy->Pml2Low | 0b111;
    LksebEx->Pml3High[0] = (UINT64)(UINTPTR)(UINT8*)LksebExPhy->Pml2High | 0b111;
    for(SIZE i = 0 ; i < 512; i++){
        LksebEx->Pml2Low[i] = i * MEGABYTE_PAGE | 0b111 | (1 << 7);
        LksebEx->Pml2High[i] = i * MEGABYTE_PAGE | 0b111 | (1 << 7);
    }

    LouKeMemoryBarrier();

    ApicHalDbgPrint("APIC.SYS:Smp Trampoline Initialized\n");

    return STATUS_SUCCESS;
} 


//LouKeUnMapContinuousMemoryBlock(0x8000, ROUND_UP64(4096 + ROUND_UP64(DriverSize, 9) + sizeof(LKSEB), KILOBYTE_PAGE));


DRIVER_EXPORT void ApicHalConfigureNextApicTimerEvent(SIZE Ms){

    LouPrint("ApicHalConfigureNextApicTimerEvent()\n");
    while(1);
}

DRIVER_EXPORT LOUSTATUS ApicHalGetCurrentCpuVirtualID(UINT32* Cpu){
    if(!Cpu){
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 ProcessorID = LouKeGetCurrentCpuPhysicalId();
    SIZE TotalProcessors = GetNPROC();
    for(SIZE i = 0; i < TotalProcessors; i++){
        if(PerProcessorApicData[i].ProcessorID == ProcessorID){
            *Cpu = i;
            return STATUS_SUCCESS;
        }
    }
    return STATUS_UNSUCCESSFUL;
}

static UINT32 ApicGetLocalInitItemProcessorId(
    PLOCAL_APIC_INIT_LIST_ITEM Item
){
    UINT32 Result = 0;
    switch(Item->EntryVersion){
        case LOCAL_APIC_ACPI_ENTRY_VERSION_X1LOCAL_STRUCT:
            Result = Item->Entry->X1Entry.ProcessorID;
            break;
        case LOCAL_APIC_ACPI_ENTRY_VERSION_XSLOCAL_STRUCT:
            Result = Item->Entry->SapicEntry.LocalSapicStatic.ProcessorID;
            break;
        case LOCAL_APIC_ACPI_ENTRY_VERSION_X2LOCAL_STRUCT:
            Result = Item->Entry->X2Entry.ProcessorID;
            break;
    }
    return Result;
}

static UINT32 ApicGetLocalInitItemApicId(
    PLOCAL_APIC_INIT_LIST_ITEM Item
){
    UINT32 Result = 0;
    switch(Item->EntryVersion){
        case LOCAL_APIC_ACPI_ENTRY_VERSION_X1LOCAL_STRUCT:
            Result = Item->Entry->X1Entry.ApicID;
            break;
        case LOCAL_APIC_ACPI_ENTRY_VERSION_XSLOCAL_STRUCT:
            Result = Item->Entry->SapicEntry.LocalSapicStatic.LocalSapicID;
            break;
        case LOCAL_APIC_ACPI_ENTRY_VERSION_X2LOCAL_STRUCT:
            Result = Item->Entry->X2Entry.X2ApicId;
            break;
    }
    return Result;
}


static UINT32 ApicGetIoInitItemApicID(
    PIO_APIC_INIT_LIST_ITEM Item
){
    UINT32 Result = 0;
    switch(Item->EntryVersion){
        case IO_APIC_ACPI_ENTRY_VERSION_IO_APIC:
            Result = Item->Entry->IoApicEntry.IoApicID;
            break;
        case IO_APIC_ACPI_ENTRY_VERSION_IO_SAPIC:
            Result = Item->Entry->IoSapicEntry.IoApicID;
            break;
    }
    return Result;
}

static UINT32 ApicGetLocalNmiItemProcessorID(
    PLOCAL_NMI_OVERIDE_ITEM Item
){
    UINT32 Result = 0;
    switch(Item->EntryVersion){
        case X1_APIC_LOCAL_NMI_OVERIDE:
            Result = Item->Entry->X1Entry.ProcessorID;
            break;
        case X2_APIC_LOCAL_NMI_OVERIDE:
            Result = Item->Entry->X2Entry.ProcessorID;
            break;
    }
    return Result;
}

static UINT8 ApicGetLocalNmiItemLocalInterrupt(
    PLOCAL_NMI_OVERIDE_ITEM Item
){
    UINT8 Result = 0;
    switch(Item->EntryVersion){
        case X1_APIC_LOCAL_NMI_OVERIDE:
            Result = Item->Entry->X1Entry.LocalInterrupt;
            break;
        case X2_APIC_LOCAL_NMI_OVERIDE:
            Result = Item->Entry->X2Entry.LocalInterrupt;
            break;
    }
    return Result;
}

static LOUSTATUS ApicInitializeLocalNmiItem(
    LOCAL_NMI_OVERIDE_ENTRY_VERSION EntryVersion,
    PLOCAL_NMI_OVERIDE_ENTRY        Entry
){
    LOCAL_NMI_OVERIDE_ITEM Item;
    Item.EntryVersion = EntryVersion;
    Item.Entry = Entry;
    Item.LocalInterrupt = ApicGetLocalNmiItemLocalInterrupt(&Item);
    Item.ProcessorID = ApicGetLocalNmiItemProcessorID(&Item);
    PLOCAL_NMI_OVERIDE_ITEM TmpListItem; 
    ForEachListEntry(TmpListItem, &LocalNmiOverideList, Peers){
        if(
            (TmpListItem->ProcessorID == Item.ProcessorID) &&
            (TmpListItem->LocalInterrupt == Item.LocalInterrupt)
        ){
            if(Item.EntryVersion <= TmpListItem->EntryVersion){
                return STATUS_SUCCESS;
            }
            ApicHalDbgPrint("APIC.SYS:Upgrading Local NMI Overide:Version:%h:ID:%h:Vector:%h\n", TmpListItem->EntryVersion, TmpListItem->ProcessorID, TmpListItem->LocalInterrupt);
            TmpListItem->EntryVersion = Item.EntryVersion;
            TmpListItem->Entry = Item.Entry;
            ApicHalDbgPrint("APIC.SYS:Local NMI Overide Now Version:%h\n", TmpListItem->EntryVersion);
            return STATUS_SUCCESS;
        }
    }
    TmpListItem = LouKeMallocType(LOCAL_NMI_OVERIDE_ITEM, KERNEL_GENERIC_MEMORY);
    if(!TmpListItem){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    TmpListItem->EntryVersion = Item.EntryVersion;
    TmpListItem->Entry = Item.Entry;
    TmpListItem->ProcessorID = Item.ProcessorID;
    TmpListItem->LocalInterrupt = Item.LocalInterrupt;
    LouKeListAddTail(&TmpListItem->Peers, &LocalNmiOverideList);
    return STATUS_SUCCESS;
}


static LOUSTATUS ApicInitializeLocalInitItem(
    LOCAL_APIC_ACPI_ENTRY_VERSION   EntryVersion,
    PLOCAL_APIC_ACPI_ENTRY          Entry
){
    LOCAL_APIC_INIT_LIST_ITEM TmpNewListItem = {0};
    TmpNewListItem.EntryVersion = EntryVersion;
    TmpNewListItem.Entry = Entry;
    TmpNewListItem.ProcessorID = ApicGetLocalInitItemProcessorId(&TmpNewListItem);
    PLOCAL_APIC_INIT_LIST_ITEM TmpListItem;
    ForEachListEntry(TmpListItem, &LocalApicInitList, Peers){
        if(TmpNewListItem.ProcessorID == TmpListItem->ProcessorID){
            if(TmpNewListItem.EntryVersion <= TmpListItem->EntryVersion){
                return STATUS_SUCCESS;
            }
            ApicHalDbgPrint("APIC.SYS:LAPIC Init Entry Upgraded:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ProcessorID);
            TmpListItem->EntryVersion = EntryVersion;
            TmpListItem->Entry = Entry;
            ApicHalDbgPrint("APIC.SYS:LAPIC Init Entry Changed To:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ProcessorID);
            return STATUS_SUCCESS;
        }
    }
    TmpListItem = LouKeMallocType(LOCAL_APIC_INIT_LIST_ITEM, KERNEL_GENERIC_MEMORY);
    if(!TmpListItem){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    TmpListItem->EntryVersion = TmpNewListItem.EntryVersion;
    TmpListItem->Entry = TmpNewListItem.Entry;
    TmpListItem->ProcessorID = TmpNewListItem.ProcessorID;
    ApicHalDbgPrint("APIC.SYS:New LAPIC Init Entry Added:Entry:%h:Version:%h:Id:%h\n", (UINT64)Entry, (UINT64)EntryVersion, (UINT64)TmpListItem->ProcessorID);
    UpgradeNPROC();
    LouKeListAddTail(&TmpListItem->Peers, &LocalApicInitList);
    return STATUS_SUCCESS;
}

static LOUSTATUS ApicInitializeIoInitItem(
    IO_APIC_ACPI_ENTRY_VERSION      EntryVersion,
    PIO_APIC_INIT_LIST_ITEM_ENTRY   Entry
){
    IO_APIC_INIT_LIST_ITEM TmpNewListItem = {0};
    TmpNewListItem.EntryVersion = EntryVersion;
    TmpNewListItem.Entry = Entry;
    TmpNewListItem.ApicID = ApicGetIoInitItemApicID(&TmpNewListItem);
    PIO_APIC_INIT_LIST_ITEM TmpListItem;
    ForEachListEntry(TmpListItem, &IoApicInitList, Peers){
        if(TmpNewListItem.ApicID == TmpListItem->ApicID){
            if(TmpNewListItem.EntryVersion <= TmpListItem->EntryVersion){
                return STATUS_SUCCESS;
            }
            ApicHalDbgPrint("APIC.SYS:IO APIC Init Entry Upgraded:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ApicID);
            TmpListItem->EntryVersion = EntryVersion;
            TmpListItem->Entry = Entry;
            ApicHalDbgPrint("APIC.SYS:IO APIC Init Entry Changed To:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ApicID);
            return STATUS_SUCCESS;
        }
    }
    TmpListItem = LouKeMallocType(IO_APIC_INIT_LIST_ITEM, KERNEL_GENERIC_MEMORY);
    if(!TmpListItem){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    TmpListItem->EntryVersion = TmpNewListItem.EntryVersion;
    TmpListItem->Entry = TmpNewListItem.Entry;
    TmpListItem->ApicID = TmpNewListItem.ApicID;
    ApicHalDbgPrint("APIC.SYS:New IO APIC Init Entry Added:Entry:%h:Version:%h:Id:%h\n", (UINT64)Entry, (UINT64)EntryVersion, (UINT64)TmpListItem->ApicID);
    IoApicCount++;
    LouKeListAddTail(&TmpListItem->Peers, &IoApicInitList);
    return STATUS_SUCCESS;
}


void ApicHalDbgPrint(char* format, ...){
    if(ApicDebugOn){
        va_list args;
        va_start(args, format);
        LouPrintEx(format, args);
        va_end(args);
    }
}

void RemapPic(int offset1, int offset2){
      unsigned char a1, a2;

    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);  
}

void DisablePic(){
    RemapPic(0x40, 0x40 + 0x08);
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

LOUSTATUS ApicInitializeApicSubsystem(){
    ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem()\n");
    MadtTable = (PMULTIPLE_APIC_DESCRIPTION_TABLE)LouKeAcquireAcpiTable(MULTIPLE_APIC_DESCRIPTION);
    if(!MadtTable){
        ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem():ERROR Apic Not Supported\n");
        return STATUS_NOT_SUPPORTED;
    }
    DisablePic(); 

    unsigned int eax, ebx, ecx, edx;
    cpuid(1, &eax, &ebx, &ecx, &edx);
    X2ApicSupport = ecx & (1 << 21) ? true : false;


    UINT8* TableEnd = (UINT8*)MadtTable + MadtTable->MadtHeader.Length;
    UINT8* TmpMadtLocation = &MadtTable->DynamicMADTBuffer[0];
    PMADT_ICS_COMMON_FORMAT_STRUCTURE CommonMadtFormat;

    LOUSTATUS Status;

    while(TmpMadtLocation < TableEnd){
        CommonMadtFormat = (PMADT_ICS_COMMON_FORMAT_STRUCTURE)TmpMadtLocation;
        switch(CommonMadtFormat->Type){
            //Local Processor Initializations
            case MADT_ICS_PROCESSOR_LOCAL_APIC:
            case MADT_ICS_LOCAL_SAPIC:
            case MADT_ICS_PROCESSOR_LOCAL_X2APIC:
                Status = ApicInitializeLocalInitItem((LOCAL_APIC_ACPI_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PLOCAL_APIC_ACPI_ENTRY)(UINT8*)CommonMadtFormat);
                if(Status != STATUS_SUCCESS){
                    goto _INIT_ERROR;
                }
                break;
            case MADT_ICS_IO_APIC:
            case MADT_ICS_IO_SAPIC:
                Status = ApicInitializeIoInitItem((IO_APIC_ACPI_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PIO_APIC_INIT_LIST_ITEM_ENTRY)(UINT8*)CommonMadtFormat);
                if(Status != STATUS_SUCCESS){
                    goto _INIT_ERROR;
                }
                break;
            case MADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE:
                break;
            case MADT_ICS_INTERRUPT_SOURCE_OVERIDE:
                PINTERRUPT_SOURCE_OVERIDE_ENTRY NewIntOveride = LouKeMallocType(INTERRUPT_SOURCE_OVERIDE_ENTRY, KERNEL_GENERIC_MEMORY);
                if(!NewIntOveride){
                    goto _INIT_ERROR;
                }
                NewIntOveride->Overide = (PMADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LouKeListAddTail(&NewIntOveride->Peers, &IntOverideList);
                break;
            case MADT_ICS_NON_MASKABLE_OVERIDE:
                PNMI_SOURCE_OVERIDE_ENTRY NewNmiOveride = LouKeMallocType(NMI_SOURCE_OVERIDE_ENTRY, KERNEL_GENERIC_MEMORY);
                if(!NewNmiOveride){
                    goto _INIT_ERROR;
                }
                NewNmiOveride->Overide = (PMADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LouKeListAddTail(&NewNmiOveride->Peers, &NmiOverideList);
                break;
            case MADT_ICS_LOCAL_APIC_NMI:
            case MADT_ICS_LOCAL_X2APIC_NMI:
                Status = ApicInitializeLocalNmiItem((LOCAL_NMI_OVERIDE_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PLOCAL_NMI_OVERIDE_ENTRY)(UINT8*)CommonMadtFormat);
                if(Status != STATUS_SUCCESS){
                    goto _INIT_ERROR;
                }
                break;
            case MADT_ICS_PLATFORM_INTERRUPT_SOURCE:
                PPLATFORM_INTERRUPT_ENTRY NewPlatformSource = LouKeMallocType(PLATFORM_INTERRUPT_ENTRY, KERNEL_GENERIC_MEMORY);
                if(!NewPlatformSource){
                    goto _INIT_ERROR;
                }
                NewPlatformSource->Source = (PMADT_ICS_PLATFORM_INTERRUPT_SOURCE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LouKeListAddTail(&NewPlatformSource->Peers, &PlatformSourceList);
                break;
            default:
                ApicHalDbgPrint("APIC.SYS:WARNING:Unhandled Madt Table Entry:Type:%h:Length:%h\n", (UINT64)CommonMadtFormat->Type, (UINT64)CommonMadtFormat->Length);
                break;
        }
        TmpMadtLocation += CommonMadtFormat->Length;
    }
        
    if(X2ApicSupport){
        ApicHalDbgPrint("APIC.SYS:System Supports X2APIC Using X2APIC mode\n");
    }
    UINT32 Processors = (UINT32)GetNPROC();

    ApicHalDbgPrint("APIC.SYS:Apic Subsystem Detected:%d Processors And:%d IO/Apics\n", Processors, IoApicCount);
    
    PerProcessorApicData = LouKeMallocArray(PER_PROCESSOR_APIC_DATA, Processors, KERNEL_GENERIC_MEMORY);
    if(!PerProcessorApicData){
        goto _INIT_ERROR;
    }

    ULONG CurrentID = LouKeGetCurrentCpuPhysicalId();
    PLOCAL_APIC_INIT_LIST_ITEM TmpItem;
    PLOCAL_APIC_INIT_LIST_ITEM SafeTmpItem;
    SIZE Index = 1;
    ForEachListEntrySafe(TmpItem, SafeTmpItem, &LocalApicInitList, Peers){
        if(TmpItem->ProcessorID == CurrentID){
            PerProcessorApicData[0].ProcessorID = ApicGetLocalInitItemProcessorId(TmpItem);
            PerProcessorApicData[0].ApicID = ApicGetLocalInitItemApicId(TmpItem); 
        }else{
            PerProcessorApicData[Index].ProcessorID = ApicGetLocalInitItemProcessorId(TmpItem);
            PerProcessorApicData[Index].ApicID = ApicGetLocalInitItemApicId(TmpItem);
            Index++; 
        }
        LouKeListDeleteItem(&TmpItem->Peers);
        LouKeFree(TmpItem);
    }

    LouKeSignalApicSubsystemInitialized();    

    LouKeInitializeIpicSubsystem(GetNPROC());

    if(GetNPROC() > 1){
        Status = InitializeSmpTrampoline();
        if(Status != STATUS_SUCCESS){
            ApicHalDbgPrint("APIC.SYS:Unable To Initialze SMP Subsystems\n");
            while(1);
        }
        LouKeInitializeSmpLouPrint();

    }


    //TODO Initialize IO Apic array

    ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

_INIT_ERROR:

    PLOCAL_NMI_OVERIDE_ITEM TmpNmiOverideListItem;    
    PLOCAL_NMI_OVERIDE_ITEM SafeTmpNmiOverideListItem;    
    ForEachListEntrySafe(TmpNmiOverideListItem, SafeTmpNmiOverideListItem, &LocalNmiOverideList, Peers){
        LouKeListDeleteItem(&TmpNmiOverideListItem->Peers);
        LouKeFree(TmpNmiOverideListItem);
    }

    PLOCAL_APIC_INIT_LIST_ITEM TmpInitListItem;
    PLOCAL_APIC_INIT_LIST_ITEM SafeTmpInitListItem;
    ForEachListEntrySafe(TmpInitListItem, SafeTmpInitListItem, &LocalApicInitList, Peers){
        LouKeListDeleteItem(&TmpInitListItem->Peers);
        LouKeFree(TmpInitListItem);
        DowngradeNPROC();
    }
    
    PIO_APIC_INIT_LIST_ITEM TmpIoListItem;
    PIO_APIC_INIT_LIST_ITEM SafeTmpIoListItem;
    ForEachListEntrySafe(TmpIoListItem, SafeTmpIoListItem, &IoApicInitList, Peers){
        LouKeListDeleteItem(&TmpIoListItem->Peers);
        LouKeFree(TmpIoListItem);
    }

    PNMI_SOURCE_OVERIDE_ENTRY TmpNmiOveride;
    PNMI_SOURCE_OVERIDE_ENTRY SafeTmpNmiOveride;
    ForEachListEntrySafe(TmpNmiOveride, SafeTmpNmiOveride, &NmiOverideList, Peers){
        LouKeListDeleteItem(&TmpIoListItem->Peers);
        LouKeFree(TmpNmiOveride);
    }

    PINTERRUPT_SOURCE_OVERIDE_ENTRY TmpIntOveride;
    PINTERRUPT_SOURCE_OVERIDE_ENTRY SafeTmpIntOveride;
    ForEachListEntrySafe(TmpIntOveride, SafeTmpIntOveride, &IntOverideList, Peers){
        LouKeListDeleteItem(&TmpIntOveride->Peers);
        LouKeFree(TmpIntOveride);
    }

    PPLATFORM_INTERRUPT_ENTRY TmpPlatformSource;
    PPLATFORM_INTERRUPT_ENTRY SafeTmpPlatformSource;
    ForEachListEntrySafe(TmpPlatformSource, SafeTmpPlatformSource, &PlatformSourceList, Peers){
        LouKeListDeleteItem(&TmpPlatformSource->Peers);
        LouKeFree(TmpPlatformSource);
    }

    return STATUS_INSUFFICIENT_RESOURCES;
}

DRIVER_EXPORT 
LOUSTATUS 
ApicInitializeAdvancedProgramableInterruptControllerAbstraction(
    ULONG Cpu
){  
    LOUSTATUS Status;
    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptControllerAbstraction(%h)\n", Cpu);
    if(!PerProcessorApicData){
        Status = ApicInitializeApicSubsystem();
        if(Status != STATUS_SUCCESS){
            LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic Subsystem\n");
            while(1);
        }
    }

    UINT64 XapicBaseRegister = LouKeReadMsr(IA32_APIC_BASE_MSR_OFFSET);
    UINT64 ApicPhyAddress = XapicBaseRegister & 0x000FFFFFFFFFF000ULL;
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[Cpu].ApicDeviceObject;
    XapicBaseRegister |= IA32_APIC_BASE_MSR_XAPIC_ENABLE_BIT;
    if(X2ApicSupport){
        ApicHalDbgPrint("APIC.SYS:Communicating With X2 LAPIC Via MSR\n");
        XapicBaseRegister |= IA32_APIC_BASE_MSR_X2APIC_ENABLE_BIT;
        ApicDeviceObject->ApicObjectType = X2_LOCAL_APIC_OBJECT_TYPE;
        
    }else{
        ApicHalDbgPrint("APIC.SYS:LAPIC X1 Physical Address:%h\n", ApicPhyAddress);
        ApicDeviceObject->ApicObjectType = X1_LOCAL_APIC_OBJECT_TYPE;
        ApicDeviceObject->X1ApicObject.ApicBase = (PVOID)LouKeMallocKbPageExVirt32(1, KERNEL_WRITEABLE_PAGE_UNCAHEABLE_PRESENT, ApicPhyAddress, true);
    }
    LouKeWriteMsr(IA32_APIC_BASE_MSR_OFFSET, XapicBaseRegister);

    Status = ApicHalInitializeInterProcessorInterrupts(Cpu);
    if(Status != STATUS_SUCCESS){
        LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic IPI\n");
        while(1);
    }

    ApicHalDbgPrint("APIC.SYS:IPI System Initialized\n");

    Status = ApicHalConfigureSpriousVector(Cpu);
    if(Status != STATUS_SUCCESS){
        LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic SPV\n");
        while(1);
    }

    ApicHalDbgPrint("APIC.SYS:Spurious Vector Initialized\n");

    ULONG i;
    ULONG Count = GetNPROC(); 
    ULONG CurrentID = LouKeGetCurrentCpuPhysicalId();

    if(!Cpu){
        for(i = 0; i < Count; i++){
            if(PerProcessorApicData[i].ProcessorID != CurrentID){
                Status = ApicHalSendSipiToAp(i);
                if(Status != STATUS_SUCCESS){
                    ApicHalDbgPrint("APIC.SYS:Error Initializing CPU\n");
                    while(1);
                }
                ApicHalDbgPrint("APIC.SYS:Initialization Of First AP Successfull\n");
                break;
            }
        }
    }

    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptControllerAbstraction():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS 
ApicSubsystemEntry(){
    LouPrint("APIC.SYS:ApicSubsystemEntry()\n");
    
    HANDLE ApicDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\APIC_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(ApicDebugKey, &DbgValue);
    ApicDebugOn = DbgValue ? true : false;


    LouPrint("APIC.SYS:ApicSubsystemEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}