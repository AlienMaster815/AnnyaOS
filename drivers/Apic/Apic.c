#define APIC_MAIN
#include "ApicInternals.h"
#include "X1ApicInternals.h"
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
    UINT32                          ApicID;
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
PPER_IO_APIC_DATA PerIoApicData = 0x00;
PPER_IO_OVERIDE_DATA PerIoOverideData = 0x00;

KERNEL_EXPORT void LouKeSignalApicSubsystemInitialized();
KERNEL_EXPORT UINT64 GetPageBase();

SIZE IoApicCount = 0;
SIZE IoOverideObjectCount = 0;


static BOOLEAN ApicDebugOn = false;

static ListHeader LocalApicInitList = {0};
static ListHeader IoApicInitList = {0};
static ListHeader IntOverideList = {0};
static ListHeader NmiOverideList = {0};
static ListHeader LocalNmiOverideList = {0};
static ListHeader PlatformSourceList = {0};

KERNEL_EXPORT
size_t LouKeGetBootDeviceSize(size_t Index);

DRIVER_EXPORT ULONG ApicHalCpuIdToApicId(ULONG Cpu){
    return PerProcessorApicData[Cpu].ApicID;
}

KERNEL_EXPORT UINT64 LouKeGetMultibootTrampolineEntrance();

DRIVER_EXPORT void ApicHalConfigureNextApicTimerEvent(SIZE Ms){
    if(Ms){
        ApicHalSignalLocalApicEoi();
    }
    Ms = Ms ? Ms : 1;
    ULONG Processor = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[Processor].ApicDeviceObject;
    ApicHalSetLocalApicTimerInitialCount(ApicDeviceObject->MsTimerCount);
}

static const APIC_TIMER_DIVIDE_CONFIG TimerConfigs[7] = {
    APIC_TIMER_DIVIDE_BY128,
    APIC_TIMER_DIVIDE_BY64,
    APIC_TIMER_DIVIDE_BY32,
    APIC_TIMER_DIVIDE_BY16,
    APIC_TIMER_DIVIDE_BY8,
    APIC_TIMER_DIVIDE_BY4,
    APIC_TIMER_DIVIDE_BY2,
};

DRIVER_EXPORT
void ApciHalStopApicTimerEvents(){
    BOOLEAN TimerSetupMask = true;
    ULONG Processor = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[Processor].ApicDeviceObject;
    ApicHalSetLocalApicLvtTimerRegister(0x00, &TimerSetupMask, 0x00);
}

DRIVER_EXPORT 
void ApciHalStartApicTimerEvents(){
    BOOLEAN TimerSetupMask = false;
    ULONG Processor = LouKeGetCurrentProcessorNumber();
    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[Processor].ApicDeviceObject;
    UINT32 CurrentCount;
    ApicHalGetLocalApicTimerCurrentCount(&CurrentCount);
    ApicHalSetLocalApicLvtTimerRegister(0x00, &TimerSetupMask, 0x00);
    if(CurrentCount){
        ApicHalSetLocalApicTimerInitialCount(CurrentCount);
    }else{
        ApicHalSetLocalApicTimerInitialCount(ApicDeviceObject->TimerConfigTick);
    }
}

static LOUSTATUS ApicHalInitializeTimer(ULONG Cpu){
    BOOLEAN TimerSetupMask = false;
    UINT8 TimerSetupVector = APIC_TIMER_VECTOR;
    UINT32 CurrentCount;
    APIC_TIMER_MODE TimerSetupMode = APIC_TIMER_MODE_ONE_SHOT;

    PAPIC_DEVICE_OBJECT ApicDeviceObject = &PerProcessorApicData[Cpu].ApicDeviceObject;
    
    LOUSTATUS Status = STATUS_UNSUCCESSFUL;
    for(SIZE i = 0 ; i < 7; i++){
        ApicHalSetLocalApicDivideConfigurationRegister(TimerConfigs[i]);
        ApicHalSetLocalApicLvtTimerRegister(&TimerSetupMode, &TimerSetupMask, &TimerSetupVector);
        ApicHalSetLocalApicTimerInitialCount(0xFFFFFFFF);
        sleep(1);
        ApicHalGetLocalApicTimerCurrentCount(&CurrentCount);

        ApicDeviceObject->MsTimerCount = 0xFFFFFFFF - CurrentCount;
        
        if(ApicDeviceObject->MsTimerCount){
            Status = STATUS_SUCCESS;
            ApicDeviceObject->TimerConfigSelector = i;
            switch(i){
                case 0:{
                    ApicDeviceObject->TimerConfigTick = 128;
                    break;
                }
                case 1:{
                    ApicDeviceObject->TimerConfigTick = 64;
                    break;
                }
                case 2:{
                    ApicDeviceObject->TimerConfigTick = 32;
                    break;
                }
                case 3:{
                    ApicDeviceObject->TimerConfigTick = 16;
                    break;
                }
                case 4:{
                    ApicDeviceObject->TimerConfigTick = 8;
                    break;
                }
                case 5:{
                    ApicDeviceObject->TimerConfigTick = 4;
                    break;
                }
                case 6:{
                    ApicDeviceObject->TimerConfigTick = 2;
                    break;
                }
            }
            break;
        }
    }
    if(Status != STATUS_SUCCESS){
        LouPrint("ApicHalInitializeTimer():ERROR:Unable To Initialize Timer\n");
        while(1);
    }

    ApicHalSetLocalApicTimerInitialCount(ApicDeviceObject->MsTimerCount);

    ApicHalDbgPrint("APIC.SYS:Ms Timer Count:%h\n", ApicDeviceObject->MsTimerCount);

    return STATUS_SUCCESS;
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


static UINT8 ApicGetIoInitItemApicID(
    PIO_APIC_INIT_LIST_ITEM Item
){
    UINT8 Result = 0;
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

static UINT8 ApicGetIoInitItemApicGsiBase(
    PIO_APIC_INIT_LIST_ITEM Item
){
    UINT8 Result = 0;
    switch(Item->EntryVersion){
        case IO_APIC_ACPI_ENTRY_VERSION_IO_APIC:
            Result = Item->Entry->IoApicEntry.GsiBase;
            break;
        case IO_APIC_ACPI_ENTRY_VERSION_IO_SAPIC:
            Result = Item->Entry->IoSapicEntry.GsiBase;
            break;
    }
    return Result;
}

static UINT32 ApicGetIoInitApicAddress(
    PIO_APIC_INIT_LIST_ITEM Item
){
    UINT32 Result = 0;
    switch(Item->EntryVersion){
        case IO_APIC_ACPI_ENTRY_VERSION_IO_APIC:
            Result = Item->Entry->IoApicEntry.IoApicAddress;
            break;
        case IO_APIC_ACPI_ENTRY_VERSION_IO_SAPIC:
            Result = Item->Entry->IoSapicEntry.IoSapicAddress;
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
    TmpNewListItem.ApicID = ApicGetLocalInitItemApicId(&TmpNewListItem);
    if(X2ApicSupport && TmpNewListItem.ApicID == 0xFFFFFFFF){
        return STATUS_SUCCESS;
    }else if(TmpNewListItem.ApicID == 0xFF){
        return STATUS_SUCCESS;
    }
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
    TmpListItem->ApicID = TmpNewListItem.ApicID;
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
    if(X2ApicSupport && TmpNewListItem.ApicID == 0xFFFFFFFF){
        return STATUS_SUCCESS;
    }else if(TmpNewListItem.ApicID == 0xFF){
        return STATUS_SUCCESS;
    }
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
    ApicHalDbgPrint("APIC.SYS:New IO APIC Init Entry Added:Entry:%h:Version:%h:Id:%h\n",(UINT64)Entry, (UINT64)EntryVersion, (UINT64)TmpListItem->ApicID);
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

LOUSTATUS ApicInitializeApicSubsystem(PAPIC_DEVICE_OBJECT ApicDeviceObject){
    PLOCAL_APIC_INIT_LIST_ITEM TmpItem;
    PLOCAL_APIC_INIT_LIST_ITEM SafeTmpItem;
    PIO_APIC_INIT_LIST_ITEM TmpIoListItem;
    PIO_APIC_INIT_LIST_ITEM SafeTmpIoListItem;
    PINTERRUPT_SOURCE_OVERIDE_ENTRY TmpIntOveride;
    PINTERRUPT_SOURCE_OVERIDE_ENTRY SafeTmpIntOveride;

    ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem()\n");
    MadtTable = (PMULTIPLE_APIC_DESCRIPTION_TABLE)LouKeAcquireAcpiTable(MULTIPLE_APIC_DESCRIPTION);
    if(!MadtTable){
        ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem():ERROR Apic Not Supported\n");
        return STATUS_NOT_SUPPORTED;
    }
    DisablePic(); 

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
                IoOverideObjectCount++;
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

    UINT32 CurrentID;
    ApicHalGetApicIdRegister(ApicDeviceObject, &CurrentID);
    CurrentID = ApicDeviceObject->ApicObjectType ? CurrentID : GET_X1APIC_ID_VALUE(CurrentID);

    SIZE Index = 1;
    ForEachListEntrySafe(TmpItem, SafeTmpItem, &LocalApicInitList, Peers){
        if(ApicGetLocalInitItemApicId(TmpItem) != CurrentID){
            PerProcessorApicData[Index].ProcessorID = ApicGetLocalInitItemProcessorId(TmpItem);
            PerProcessorApicData[Index].ApicID = ApicGetLocalInitItemApicId(TmpItem);
            Index++;         
        }else{
            PerProcessorApicData[0].ProcessorID = ApicGetLocalInitItemProcessorId(TmpItem);
            PerProcessorApicData[0].ApicID = ApicGetLocalInitItemApicId(TmpItem);
        }
        LouKeListDeleteItem(&TmpItem->Peers);
        LouKeFree(TmpItem);
    }

    SIZE i = 0;
    PerIoApicData = LouKeMallocArray(PER_IO_APIC_DATA, IoApicCount, KERNEL_GENERIC_MEMORY);

    ForEachListEntrySafe(TmpIoListItem, SafeTmpIoListItem, &IoApicInitList, Peers){
        UINT32 ApicPhyAddress = ApicGetIoInitApicAddress(TmpIoListItem);
        UINT8 IoApicId = ApicGetIoInitItemApicID(TmpIoListItem);
        UINT8 GsiBase = ApicGetIoInitItemApicGsiBase(TmpIoListItem);
        UINT32 GsiCount = 0;
        PerIoApicData[i].ApicDeviceObject.ApicObjectType = IO_APIC_OBJECT_TYPE;
        PerIoApicData[i].ApicDeviceObject.IoApicObject.ApicBase = LouKeMallocKbPageExVirt32(1, KERNEL_WRITEABLE_PAGE_UNCAHEABLE_PRESENT, ApicPhyAddress, true);
        PerIoApicData[i].ApicID = IoApicId;
        PerIoApicData[i].ApicGsiBase = GsiBase;

        ApicHalGetIoApicVersionRegisterFromObject(
            &PerIoApicData[i].ApicDeviceObject,
            0x00,
            &GsiCount
        );
        PerIoApicData[i].ApicGsiCount = (UINT8)GsiCount;

        PerIoApicData[i].PinVectorData = LouKeMallocArray(PER_IO_APIC_PIN_DATA, GsiCount, KERNEL_GENERIC_MEMORY);
        if(!PerIoApicData[i].PinVectorData){
            LouPrint("APIC.SYS:ApicInitializeApicSubsystem:HERE\n");
            while(1);
        }
        i++;
        LouKeListDeleteItem(&TmpIoListItem->Peers);
        LouKeFree(TmpIoListItem);
    }

    PerIoOverideData = LouKeMallocArray(PER_IO_OVERIDE_DATA, IoOverideObjectCount, KERNEL_GENERIC_MEMORY);
    i = 0;
    ForEachListEntrySafe(TmpIntOveride, SafeTmpIntOveride, &IntOverideList, Peers){
        PerIoOverideData[i].InDirectionIrq = TmpIntOveride->Overide->IrqSource;
        PerIoOverideData[i].OutDirectionIrq = TmpIntOveride->Overide->Gsi;
        UINT32 Tmp = ((TmpIntOveride->Overide->MpsIntiFlags & MADT_ICS_ISO_MPS_INTI_FLAG_POLARITY) >> MADT_ICS_ISO_MPS_INTI_FLAG_POLARITY_SHIFT);
        if(Tmp == 3){
            PerIoOverideData[i].PinPolarity = IO_APIC_PIN_POLARITY_ACTIVE_LOW;
        }else{
            PerIoOverideData[i].PinPolarity = IO_APIC_PIN_POLARITY_ACTIVE_HIGH;
        }
        Tmp = ((TmpIntOveride->Overide->MpsIntiFlags & MADT_ICS_ISO_MPS_INTI_FLAG_TRIGGER_MODE) >> MADT_ICS_ISO_MPS_INTI_FLAG_TRIGGER_MODE_SHIFT);        
        if(Tmp == 3){
            PerIoOverideData[i].TriggerMode = IO_APIC_TRIGGER_MODE_LEVEL;
        }else{
            PerIoOverideData[i].TriggerMode = IO_APIC_TRIGGER_MODE_EDGE;
        }
        i++;
        LouKeListDeleteItem(&TmpIntOveride->Peers);
        LouKeFree(TmpIntOveride);
    }

    LouKeSignalApicSubsystemInitialized();    

    LouKeInitializeIpicSubsystem(GetNPROC());

    ApicHalDbgPrint("APIC.SYS:ApicInitializeApicSubsystem():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;

_INIT_ERROR:

    if(PerProcessorApicData){
        LouKeFree(PerProcessorApicData);
    }

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
ApicInitializeAdvancedProgramableInterruptControllerAbstraction(UINT32* CpuIdOut){  
    LOUSTATUS Status;
    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptControllerAbstraction()\n");

    UINT64 XapicBaseRegister = LouKeReadMsr(IA32_APIC_BASE_MSR_OFFSET);
    UINT64 ApicPhyAddress = XapicBaseRegister & 0x000FFFFFFFFFF000ULL;
    APIC_DEVICE_OBJECT ApicDeviceObject = {0};

    if(!X2ApicSupport){
        X2ApicSupport = (XapicBaseRegister & IA32_APIC_BASE_MSR_X2APIC_ENABLE_BIT) ? true : false;
    }
    
    if(X2ApicSupport){
        ApicHalDbgPrint("APIC.SYS:Communicating With X2 LAPIC Via MSR\n");
        ApicDeviceObject.ApicObjectType = X2_LOCAL_APIC_OBJECT_TYPE;
    }else{
        ApicHalDbgPrint("APIC.SYS:LAPIC X1 Physical Address:%h\n", ApicPhyAddress);
        ApicDeviceObject.ApicObjectType = X1_LOCAL_APIC_OBJECT_TYPE;
        ApicDeviceObject.X1ApicObject.ApicBase = (PVOID)LouKeMallocKbPageExVirt32(1, KERNEL_WRITEABLE_PAGE_UNCAHEABLE_PRESENT, ApicPhyAddress, true);
        if(!(XapicBaseRegister & IA32_APIC_BASE_MSR_XAPIC_ENABLE_BIT)){
            XapicBaseRegister |= IA32_APIC_BASE_MSR_XAPIC_ENABLE_BIT;
            LouKeWriteMsr(IA32_APIC_BASE_MSR_OFFSET, XapicBaseRegister);
        }
    }
   
    if(!PerProcessorApicData){
        Status = ApicInitializeApicSubsystem(&ApicDeviceObject);
        if(Status != STATUS_SUCCESS){
            LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic Subsystem\n");
            while(1);
        }
    }

    UINT32 ApicID = 0;
    UINT32 ProcessorCount = GetNPROC();
    Status = ApicHalGetApicIdRegister(&ApicDeviceObject, &ApicID);
    ApicID = ApicDeviceObject.ApicObjectType ? ApicID : GET_X1APIC_ID_VALUE(ApicID);
    if(Status != STATUS_SUCCESS){
        ApicHalDbgPrint("APIC.SYS:Unable To Get Apic ID\n");
        while(1);
    }

    BOOLEAN Found = false;
    SIZE i;
    for(i = 0 ; i < ProcessorCount; i++){
        if(PerProcessorApicData[i].ApicID == ApicID){
            Found = true;
            break;
        }
    }

    if(!Found){
        ApicHalDbgPrint("APIC.SYS:Unable To Find Apic ID In Abstraction\n");
        while(1);
    }

    if(CpuIdOut){
        *CpuIdOut = i;
    }

    memcpy(&PerProcessorApicData[i].ApicDeviceObject, &ApicDeviceObject, sizeof(APIC_DEVICE_OBJECT));

    Status = ApicHalInitializeInterProcessorInterrupts(i);
    if(Status != STATUS_SUCCESS){
        LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic IPI\n");
        while(1);
    }

    ApicHalDbgPrint("APIC.SYS:IPI System Initialized\n");

    Status = ApicHalConfigureSpriousVector(i);
    if(Status != STATUS_SUCCESS){
        LouPrint("APIC.SYS:ERROR:Unable To Initialize Apic SPV\n");
        while(1);
    }

    ApicHalDbgPrint("APIC.SYS:Spurious Vector Initialized\n");

    Status = ApicHalInitializeTimer(i);
    if(Status != STATUS_SUCCESS){
        LouPrint("APIC.SYS:Error Unable To Initialize Timer\n");
        while(1);
    }

    ApicHalDbgPrint("APIC.SYS:ApicInitializeAdvancedProgramableInterruptControllerAbstraction():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUAPI
LOUSTATUS 
ApicSubsystemEntry(){    
    HANDLE ApicDebugKey = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\DEBUG\\APIC_DEBUG", 0x00);
    BYTE DbgValue = 0;
    LouKeReadRegistryByteValue(ApicDebugKey, &DbgValue);
    ApicDebugOn = DbgValue ? true : false;
    LouPrint("APIC.SYS:ApicSubsystemEntry()\n");


    LouPrint("APIC.SYS:ApicSubsystemEntry():STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}