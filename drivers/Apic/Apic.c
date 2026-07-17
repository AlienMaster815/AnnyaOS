#define APIC_MAIN
#include "ApicInternals.h"
#include <LouACPI.h>

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

static SIZE IoApicCount = 0;

static BOOLEAN ApicDebugOn = false;

static ListHeader LocalApicInitList = {0};
static ListHeader IoApicInitList = {0};
static ListHeader IntOverideList = {0};
static ListHeader NmiOverideList = {0};
static ListHeader LocalNmiOverideList = {0};
static ListHeader PlatformSourceList = {0};

static PVOID LocalApicAddress = (UINT8*)0xFEE00000;



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

static void ApicInitializeLocalNmiItem(
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
                return;
            }
            ApicHalDbgPrint("APIC.SYS:Upgrading Local NMI Overide:Version:%h:ID:%h:Vector:%h\n", TmpListItem->EntryVersion, TmpListItem->ProcessorID, TmpListItem->LocalInterrupt);
            TmpListItem->EntryVersion = Item.EntryVersion;
            TmpListItem->Entry = Item.Entry;
            ApicHalDbgPrint("APIC.SYS:Local NMI Overide Now Version:%h\n", TmpListItem->EntryVersion);
            return;
        }


    }
}


static void ApicInitializeLocalInitItem(
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
                return;
            }
            ApicHalDbgPrint("APIC.SYS:LAPIC Init Entry Upgraded:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ProcessorID);
            TmpListItem->EntryVersion = EntryVersion;
            TmpListItem->Entry = Entry;
            ApicHalDbgPrint("APIC.SYS:LAPIC Init Entry Changed To:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ProcessorID);
            return;
        }
    }
    TmpListItem = LouKeMallocType(LOCAL_APIC_INIT_LIST_ITEM, KERNEL_GENERIC_MEMORY);
    TmpListItem->EntryVersion = TmpNewListItem.EntryVersion;
    TmpListItem->Entry = TmpNewListItem.Entry;
    TmpListItem->ProcessorID = TmpNewListItem.ProcessorID;
    ApicHalDbgPrint("APIC.SYS:New LAPIC Init Entry Added:Entry:%h:Version:%h:Id:%h\n", (UINT64)Entry, (UINT64)EntryVersion, (UINT64)TmpListItem->ProcessorID);
    UpgradeNPROC();
    LouKeListAddTail(&TmpListItem->Peers, &LocalApicInitList);
}

static void ApicInitializeIoInitItem(
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
                return;
            }
            ApicHalDbgPrint("APIC.SYS:IO APIC Init Entry Upgraded:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ApicID);
            TmpListItem->EntryVersion = EntryVersion;
            TmpListItem->Entry = Entry;
            ApicHalDbgPrint("APIC.SYS:IO APIC Init Entry Changed To:Entry:%h:Version:%h:Id:%h\n", (UINT64)TmpListItem->Entry, (UINT64)TmpListItem->EntryVersion, (UINT64)TmpListItem->ApicID);
            return;
        }
    }
    TmpListItem = LouKeMallocType(IO_APIC_INIT_LIST_ITEM, KERNEL_GENERIC_MEMORY);
    TmpListItem->EntryVersion = TmpNewListItem.EntryVersion;
    TmpListItem->Entry = TmpNewListItem.Entry;
    TmpListItem->ApicID = TmpNewListItem.ApicID;
    ApicHalDbgPrint("APIC.SYS:New IO APIC Init Entry Added:Entry:%h:Version:%h:Id:%h\n", (UINT64)Entry, (UINT64)EntryVersion, (UINT64)TmpListItem->ApicID);
    IoApicCount++;
    LouKeListAddTail(&TmpListItem->Peers, &IoApicInitList);
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


    while(TmpMadtLocation < TableEnd){
        CommonMadtFormat = (PMADT_ICS_COMMON_FORMAT_STRUCTURE)TmpMadtLocation;
        switch(CommonMadtFormat->Type){
            //Local Processor Initializations
            case MADT_ICS_PROCESSOR_LOCAL_APIC:
            case MADT_ICS_LOCAL_SAPIC:
            case MADT_ICS_PROCESSOR_LOCAL_X2APIC:
                ApicInitializeLocalInitItem((LOCAL_APIC_ACPI_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PLOCAL_APIC_ACPI_ENTRY)(UINT8*)CommonMadtFormat);
                break;
            case MADT_ICS_IO_APIC:
            case MADT_ICS_IO_SAPIC:
                ApicInitializeIoInitItem((IO_APIC_ACPI_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PIO_APIC_INIT_LIST_ITEM_ENTRY)(UINT8*)CommonMadtFormat);
                break;
            case MADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE:
                PMADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE Overide = (PMADT_ICS_LOCAL_APIC_ADDRESS_OVERIDE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LocalApicAddress = (UINT8*)(UINTPTR)Overide->LocalApicAddress;
            case MADT_ICS_INTERRUPT_SOURCE_OVERIDE:
                PINTERRUPT_SOURCE_OVERIDE_ENTRY NewIntOveride = LouKeMallocType(INTERRUPT_SOURCE_OVERIDE_ENTRY, KERNEL_GENERIC_MEMORY);
                NewIntOveride->Overide = (PMADT_ICS_INTERRUPT_SOURCE_OVERIDE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LouKeListAddTail(&NewIntOveride->Peers, &IntOverideList);
                break;
            case MADT_ICS_NON_MASKABLE_OVERIDE:
                PNMI_SOURCE_OVERIDE_ENTRY NewNmiOveride = LouKeMallocType(NMI_SOURCE_OVERIDE_ENTRY, KERNEL_GENERIC_MEMORY);
                NewNmiOveride->Overide = (PMADT_ICS_NON_MASKABLE_INTERRUPT_SOURCE_STRUCTURE)(UINT8*)CommonMadtFormat;
                LouKeListAddTail(&NewNmiOveride->Peers, &NmiOverideList);
                break;
            case MADT_ICS_LOCAL_APIC_NMI:
            case MADT_ICS_LOCAL_X2APIC_NMI:
                ApicInitializeLocalNmiItem((LOCAL_NMI_OVERIDE_ENTRY_VERSION)(UINT64)CommonMadtFormat->Type, (PLOCAL_NMI_OVERIDE_ENTRY)(UINT8*)CommonMadtFormat);
                break;
            case MADT_ICS_PLATFORM_INTERRUPT_SOURCE:
                PPLATFORM_INTERRUPT_ENTRY NewPlatformSource = LouKeMallocType(PLATFORM_INTERRUPT_ENTRY, KERNEL_GENERIC_MEMORY);
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
    ApicHalDbgPrint("APIC.SYS:Apic Subsystem Detected:%d Processors And:%d IO/Apics\n", GetNPROC(), IoApicCount);
    ApicHalDbgPrint("APIC.SYS:LAPIC Addresses Are:%h\n", LocalApicAddress);


    ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS 
ApicInitializeAdvancedProgramableInterruptController(
    ULONG Cpu
){  
    LOUSTATUS Status;
    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptController()\n");
    if(!PerProcessorApicData){
        Status = ApicInitializeApicSubsystem();
        if(Status != STATUS_SUCCESS){
            LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic Subsystem\n");
        }
    }


    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptController():STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS 
ApicSubsystemEntry(){
    LouPrint("APICS.SYS:ApicSubsystemEntry()\n");
    
    HANDLE ApicDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\APIC_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(ApicDebugKey, &DbgValue);
    ApicDebugOn = DbgValue ? true : false;


    LouPrint("APICS.SYS:ApicSubsystemEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}