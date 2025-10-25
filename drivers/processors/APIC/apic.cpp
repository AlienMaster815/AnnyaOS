#include <LouDDK.h>
#include <NtAPI.h>
#include "../Processors.h"
#include "apic.h"
#include <LouACPI.h>

static inline uint32_t get_processor_id() {
    uint32_t eax, ebx, ecx, edx;
    eax = 1; // Processor info and feature bits
    __asm__ volatile(
        "cpuid"
        : "=b" (ebx), "=d" (edx), "=c" (ecx)
        : "a" (eax)
    );
    uint32_t processor_id = ebx >> 24;
    return processor_id;
}




// Structure representing the lower 32 bits of an IOAPIC redirection table entry
typedef struct {
    uint32_t vector : 8;          // Bits 0-7
    uint32_t delivery_mode : 3;   // Bits 8-10
    uint32_t destination_mode : 1;// Bit 11
    uint32_t delivery_status : 1; // Bit 12
    uint32_t polarity : 1;        // Bit 13
    uint32_t remote_irr : 1;      // Bit 14
    uint32_t trigger_mode : 1;    // Bit 15
    uint32_t mask : 1;            // Bit 16
    uint32_t reserved : 15;       // Bits 17-31
} IOAPICRedirectionEntryLow;

// Structure representing the upper 32 bits of an IOAPIC redirection table entry
typedef struct {
    uint32_t reserved : 24;       // Bits 0-23
    uint32_t destination : 8;     // Bits 24-31
} IOAPICRedirectionEntryHigh;

// Structure representing a full IOAPIC redirection table entry
typedef struct {
    IOAPICRedirectionEntryLow low;
    IOAPICRedirectionEntryHigh high;
} IOAPICRedirectionEntry;


typedef struct _ACPI_TABLE_HEADER {
    char Signature[4];        // "APIC"
    uint32_t Length;          // Length of the table, including the header
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} ACPI_TABLE_HEADER, * PACPI_TABLE_HEADER;

typedef struct _ACPI_MADT {
    ACPI_TABLE_HEADER Header;
    uint32_t LocalApicAddress;
    uint32_t Flags;
    // Followed by a variable number of APIC structures
} ACPI_MADT, * PACPI_MADT;

typedef struct _ACPI_MADT_ENTRY_HEADER {
    uint8_t Type;
    uint8_t Length;
} ACPI_MADT_ENTRY_HEADER, * PACPI_MADT_ENTRY_HEADER;

typedef struct _ACPI_MADT_LOCAL_APIC {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t ProcessorID;
    uint8_t APICID;
    uint32_t Flags;
} ACPI_MADT_LOCAL_APIC, * PACPI_MADT_LOCAL_APIC;

typedef struct _ACPI_MADT_IO_APIC {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t IOAPICID;
    uint8_t Reserved;
    uint32_t IOAPICAddress;
    uint32_t GlobalSystemInterruptBase;
} ACPI_MADT_IO_APIC, * PACPI_MADT_IO_APIC;

typedef struct _ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t Bus;
    uint8_t Source;
    uint32_t GlobalSystemInterrupt;
    uint16_t Flags;
} ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE, * PACPI_MADT_INTERRUPT_SOURCE_OVERRIDE;

typedef struct _ACPI_MADT_NMI {
    ACPI_MADT_ENTRY_HEADER Header;
    uint16_t Flags;
    uint32_t GlobalSystemInterrupt;
} ACPI_MADT_NMI, * PACPI_MADT_NMI;

typedef struct _ACPI_MADT_LOCAL_APIC_NMI {
    ACPI_MADT_ENTRY_HEADER Header;
    uint8_t ProcessorID;
    uint16_t Flags;
    uint8_t LocalAPICLint;
} ACPI_MADT_LOCAL_APIC_NMI, * PACPI_MADT_LOCAL_APIC_NMI;

typedef struct _ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE {
    ACPI_MADT_ENTRY_HEADER Header;
    uint16_t Reserved;
    uint64_t LocalApicAddress;
} ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE, * PACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE;

typedef struct {
    uint32_t ioapic_id;
    uint64_t ioapic_address;
    uint32_t gsi_base;
    uint64_t ioapic_vaddress;
} IOAPICInfo;

#define APICADDRESSCAST (volatile uint32_t*)(uintptr_t)
#define LEGACY_IRQ_SCOPE 16

KERNEL_IMPORT uint64_t read_msr(uint32_t msr);
KERNEL_IMPORT void write_msr(uint32_t msr, uint64_t Value);

KERNEL_IMPORT void disable_pic();
string DRV_VERSION_APIC = "\nLousine Internal Kernel APIC.SYS Module Version 1.10\n";
string DRV_UNLOAD_STRING_SUCCESS_APIC = "Driver Execution Completed Successfully Exiting Proccess\n\n"; 
string DRV_UNLOAD_STRING_FAILURE_APIC = "Driver Execution Failed To Execute Properly Exiting Proccess\n\n"; 

LOUDDK_API_ENTRY void SMPInit();

void SetTotalIoApicInterrupts(UINT8 TotalInterrupts);
bool InitializeIoApic(PACPI_MADT_IO_APIC IoApic);
LOUSTATUS EnableAdvancedBspFeatures(CPU::FEATURE Feature);
LOUDDK_API_ENTRY void IoApicConfigureEntryFlags(
    uint8_t     irq,
    uint16_t    Flags
);

typedef struct _IO_APIC_TRACKER{
    ListHeader          Peers;
    ACPI_MADT_IO_APIC   IoApic;
}IO_APIC_TRACKER, * PIO_APIC_TRACKER;;

typedef struct _APIC_ISO_TRACKER{
    ListHeader                              Peers;
    ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE     Overide;    
}APIC_ISO_TRACKER, * PAPIC_ISO_TRACKER;

typedef struct _CPU_TRACKER_INFORMATION{
    ListHeader  Peers;
    UINT32      ProcID;
    UINT32      ApicID;
    UINT64      ApicBase;
    bool        Broken;
}CPU_TRACKER_INFORMATION, * PCPU_TRACKER_INFORMATION;

static CPU_TRACKER_INFORMATION CpuTracker = {0};
static APIC_ISO_TRACKER IoApicOverideTracker = {0};
static IO_APIC_TRACKER IoApicTracker = {0};

LOUDDK_API_ENTRY PCPU_TRACKER_INFORMATION GetCpuInfoFromTrackerMember(INTEGER Member){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    INTEGER i = 0;
    while(TmpTracker->Peers.NextHeader){

        if(i == Member){
            return TmpTracker;
        }

        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
        i++;
    }
    return 0x00;
}

LOUDDK_API_ENTRY INTEGER GetCpuTrackMemberFromID(UINT32 CpuID){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    INTEGER i = 0;
    while(TmpTracker->Peers.NextHeader){
        if(TmpTracker->ProcID == CpuID){
            return i; 
        }
        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
        i++;
    }
    return (INTEGER)-1;
}

INTEGER 
GetCurrentCpuTrackMember(){
    INTEGER Tmp = GetCpuTrackMemberFromID(get_processor_id());
    return (Tmp == (INTEGER)-1) ?  0 : Tmp;  
}

void LouKeCreateCpuTracker(
    UINT32 ProcID,
    UINT32 ApicID
){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
    }

    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(CPU_TRACKER_INFORMATION, KERNEL_GENERIC_MEMORY);
    TmpTracker->ProcID = ProcID;
    TmpTracker->ApicID = ApicID;  
    TmpTracker->ApicBase = 0x00;  
}

UINT32 CpuToApicID(UINT32 CpuID){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    while(TmpTracker->Peers.NextHeader){
        if(TmpTracker->ProcID == CpuID){
            return TmpTracker->ApicID;
        }
        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
    }
    return (UINT32)-1;
}

void LouKeSetApicBase(UINT32 ApicID, UINT64 ApicBase){
    if(ApicID == (UINT32)-1){
        return;
    }
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    while(TmpTracker->Peers.NextHeader){
        if(TmpTracker->ApicID == ApicID){
            TmpTracker->ApicBase = ApicBase;
            return;
        }
        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
    }
}

UINT64 LouKeGetCurrentApicBase(){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    UINT32 Cpu = get_processor_id();
    while(TmpTracker->Peers.NextHeader){
        if(TmpTracker->ProcID == Cpu){
            return TmpTracker->ApicBase;
        }
        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
    }
    return 0x00;
}


void LouKeInitializeOverideEntry(ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE* Overide){
    PAPIC_ISO_TRACKER TmpTracker = &IoApicOverideTracker;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PAPIC_ISO_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(APIC_ISO_TRACKER, KERNEL_GENERIC_MEMORY);
    TmpTracker->Overide = *Overide;
}


KERNEL_IMPORT uint8_t FindTrueIRQ(uint8_t IRQ){
    PAPIC_ISO_TRACKER TmpTracker = &IoApicOverideTracker;
    while(TmpTracker->Peers.NextHeader){
        if(TmpTracker->Overide.Source == IRQ){
            IoApicConfigureEntryFlags(TmpTracker->Overide.GlobalSystemInterrupt, TmpTracker->Overide.Flags);
            return TmpTracker->Overide.GlobalSystemInterrupt;
        }
        TmpTracker = (PAPIC_ISO_TRACKER)TmpTracker->Peers.NextHeader;
    }    
    return IRQ;
}

void LouKeInitializeIoApicTracker(PACPI_MADT_IO_APIC IoApic){
    PIO_APIC_TRACKER TmpTracker = &IoApicTracker;
    while(TmpTracker->Peers.NextHeader){
        TmpTracker = (PIO_APIC_TRACKER)TmpTracker->Peers.NextHeader;
    }
    TmpTracker->Peers.NextHeader = (PListHeader)LouKeMallocType(APIC_ISO_TRACKER, KERNEL_GENERIC_MEMORY);
    TmpTracker->IoApic = *IoApic;
}

uint32_t IoApicRead(uint64_t ioapic_base, uint32_t reg);

PACPI_MADT_IO_APIC GetIoApicHandleFromIrq(UINT8 Irq){
    PIO_APIC_TRACKER TmpTracker = &IoApicTracker;
    while(TmpTracker->Peers.NextHeader){
        if(Irq >= TmpTracker->IoApic.GlobalSystemInterruptBase){
            if(((IoApicRead(TmpTracker->IoApic.IOAPICAddress, 0x01) >> 16) + TmpTracker->IoApic.GlobalSystemInterruptBase) >= Irq){
                return &TmpTracker->IoApic;
            }
        }
        TmpTracker = (PIO_APIC_TRACKER)TmpTracker->Peers.NextHeader;
    }
    return 0x00;
}

LOUDDK_API_ENTRY void local_apic_send_eoi() {    
    uint64_t ApicBase = LouKeGetCurrentApicBase();
    if(!ApicBase){
        return;
    }
    WRITE_REGISTER_ULONG(EOI_REGISTER, 0);
}

KERNEL_IMPORT void IoApicMaskIrq(uint8_t tirq);
KERNEL_IMPORT void IoApicUnmaskIrq(uint8_t tirq);

void ApicInstallIoApicHandlers(){
    PCPU_TRACKER_INFORMATION TmpTracker = &CpuTracker;
    while(TmpTracker->Peers.NextHeader){

        LouKeInitializeMaskHandler((PVOID)IoApicMaskIrq, TmpTracker->ProcID);
        LouKeInitializeUnmaskHandler((PVOID)IoApicUnmaskIrq, TmpTracker->ProcID);

        TmpTracker = (PCPU_TRACKER_INFORMATION)TmpTracker->Peers.NextHeader;
    }

}

void ParseAPIC(uint8_t* entryAddress, uint8_t* endAddress) {
    while (entryAddress < endAddress) {
        ACPI_MADT_ENTRY_HEADER* header = (ACPI_MADT_ENTRY_HEADER*)entryAddress;
        switch (header->Type) {
        case 0: {
            ACPI_MADT_LOCAL_APIC* localAPIC = (ACPI_MADT_LOCAL_APIC*)entryAddress;
            if(localAPIC->APICID == 0xFF){
                break;
            }
            UpgradeNPROC();
            LouKeCreateCpuTracker(localAPIC->ProcessorID, localAPIC->APICID);
            LouPrint("Processor ID:%d, APIC ID:%d, Flags:%d\n", localAPIC->ProcessorID, localAPIC->APICID, localAPIC->Flags);
            break;
        }
        case 1: {
            ACPI_MADT_IO_APIC* ioAPIC = (ACPI_MADT_IO_APIC*)entryAddress;
            LouKeInitializeIoApicTracker(ioAPIC);
            LouPrint("I/O APIC ID:%d, Address:%h, Global System Interrupt Base:%d\n", ioAPIC->IOAPICID, ioAPIC->IOAPICAddress, ioAPIC->GlobalSystemInterruptBase);
            break;
        }
        case 2: {
            ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE* iso = (ACPI_MADT_INTERRUPT_SOURCE_OVERRIDE*)entryAddress;
            LouKeInitializeOverideEntry(iso);            
            LouPrint("Bus: %d, Source:%d, Global System Interrupt:%d, Flags:%d\n", iso->Bus, iso->Source, iso->GlobalSystemInterrupt, iso->Flags);
            break;
        }
        case 3: {
            ACPI_MADT_NMI* nmi = (ACPI_MADT_NMI*)entryAddress;
            LouPrint("Flags:%d, Global System Interrupt:%d\n", nmi->Flags, nmi->GlobalSystemInterrupt);
            break;
        }
        case 4: {
            ACPI_MADT_LOCAL_APIC_NMI* localAPICNMI = (ACPI_MADT_LOCAL_APIC_NMI*)entryAddress;
            LouPrint("Processor ID: %d, Flags: %d, LINT:%d\n", localAPICNMI->ProcessorID, localAPICNMI->Flags, localAPICNMI->LocalAPICLint);
            break;
        }
        case 5: {
            ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE* laa = (ACPI_MADT_LOCAL_APIC_ADDRESS_OVERRIDE*)entryAddress;
            LouPrint("Local APIC Address:%h\n", laa->LocalApicAddress);
            //LocalApicBase = laa->LocalApicAddress;
            while(1);
            break;
        }
        default:
            LouPrint("Unknown entry type:%d\n", header->Type);
            while(1);
            break;
        }
        entryAddress += header->Length;
    }
}

static bool ApicSet = false;

LOUDDK_API_ENTRY bool GetAPICStatus() {
    return ApicSet;
}

#define IA32_APIC_BASE_MSR 0x1B
#define MSR_BASE_MASK 0xFFFFFFFFF000ULL
#define IA32_X2APIC_BASE_MSR_ADDR 0x802
#define MSR_BASE_MASKX2 0xFFFFFFFFFFFFF000


uint64_t GetLocalApicBase() {
   uint64_t msr_value = read_msr(IA32_APIC_BASE_MSR);
   return msr_value & 0xFFFFFFFFFFFFF000;
}

// Function to set the APIC base address
void cpu_set_apic_base(uintptr_t apic) {
   uint64_t msr_value = (apic & 0xFFFFFFFFFFFFF000) | IA32_APIC_BASE_MSR_ENABLE;
   write_msr(IA32_APIC_BASE_MSR, msr_value);
}

void ApcInstallIoApicHandlers();
void LouKeInitializeBackupPic();

bool InitializeLapic(UINT32 CpuID){
    uint64_t ApicBase;
    LouPrint("Initializing Processor:%d\n", CpuID);
    ApicBase = (uint64_t)LouKeMallocPageEx32(KILOBYTE_PAGE, 1,KERNEL_PAGE_WRITE_UNCAHEABLE_PRESENT, GetLocalApicBase());
    LouKeSetApicBase(CpuToApicID(get_processor_id()), ApicBase);
    CPU::CPUID Cpu;
    if(Cpu.IsFeatureSupported(CPU::X2APIC)){
        //initiailize x2 standard
        LouPrint("Using X2 Standard\n");
        //Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts
        WRITE_REGISTER_ULONG(SPURRIOUS_INTERRUPT_REGISTER, (READ_REGISTER_ULONG(SPURRIOUS_INTERRUPT_REGISTER) & 0xFFFFFF00) | APIC_ENABLE | 0xFF);
        
        WRITE_REGISTER_ULONG(LVT_DIVIDE_CONFIGURATION_REGISTER, 0b1010); //divide by 128
        WRITE_REGISTER_ULONG(LVT_INITIAL_COUNT_REGISTER, 0xFFFFFFFF);
        sleep(1); //sleep 1 ms for 1 ms acuracy

        uint32_t CRC = 0xFFFFFFFF - READ_REGISTER_ULONG(LVT_CURRENT_COUNT_REGISTER);

        LouPrint("CRC IS:%h\n",CRC);
        // Start timer as periodic on IRQ 0, divider 128, with the number of ticks we counted
        WRITE_REGISTER_ULONG(LVT_TIMER_REGISTER, 32 | 0x20000);
        WRITE_REGISTER_ULONG(LVT_DIVIDE_CONFIGURATION_REGISTER, 0b1010);
        WRITE_REGISTER_ULONG(LVT_INITIAL_COUNT_REGISTER, CRC);
        
    }
    else if (Cpu.IsFeatureSupported(CPU::XAPIC)){
        //initialize x1 standard
        LouPrint("Using X1 Standard\n");

        //Set the Spurious Register
        WRITE_REGISTER_ULONG(SPURRIOUS_INTERRUPT_REGISTER, (READ_REGISTER_ULONG(SPURRIOUS_INTERRUPT_REGISTER) & 0xFFFFFF00) | APIC_ENABLE | 0xFF);
        WRITE_REGISTER_ULONG(TPR_REGISTER, 0x00);
        
        WRITE_REGISTER_ULONG(LVT_DIVIDE_CONFIGURATION_REGISTER, 0b1010); //divide by 128
        WRITE_REGISTER_ULONG(LVT_INITIAL_COUNT_REGISTER, 0xFFFFFFFF);
        sleep(1); //sleep 1 ms for 1 ms acuracy

        uint32_t CRC = 0xFFFFFFFF - READ_REGISTER_ULONG(LVT_CURRENT_COUNT_REGISTER);

        LouPrint("CRC IS:%h\n",CRC);
        // Start timer as periodic on IRQ 0, divider 128, with the number of ticks we counted
        WRITE_REGISTER_ULONG(LVT_TIMER_REGISTER, 32 | 0x20000);
        WRITE_REGISTER_ULONG(LVT_DIVIDE_CONFIGURATION_REGISTER, 0b1010);
        WRITE_REGISTER_ULONG(LVT_INITIAL_COUNT_REGISTER, CRC);

    }
    else{
        //determine Discreet or integrated chip
        LouPrint("APIC Version Is:%h\n", READ_REGISTER_ULONG(LAPICID_REGISTER) & 0xFF);

        switch(READ_REGISTER_ULONG(LAPICID_REGISTER) & 0xFF){
            
            case 0:
                //initialize descreet apic
                LouPrint("Descrete Apic Found\n");
                // Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts
                break;

            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
                LouPrint("Integrated Apic Found\n");
                // Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts
                
                while(1);    
                break;

            default:{
                LouPrint("Unkown APIC CHIP\n");
                while(1);
                return false;
            }
        }
    }
    return true;
}

bool InitializeApic(){
    LouPrint("Setting Up APIC\n");
    uint64_t MSR = read_msr(IA32_APIC_BASE_MSR);
    if(!(MSR >> 11) & 0x01) return false;
    return true;
}

LOUDDK_API_ENTRY LOUSTATUS InitApicSystems() {
    LOUSTATUS Status = LOUSTATUS_GOOD;  
    LouPrint(DRV_VERSION_APIC);

    PACPI_MADT ApicTable = (PACPI_MADT)LouKeAquireAcpiTable("APIC");

    if(!ApicTable){
        ApicTable = (PACPI_MADT)LouKeAquireAcpiTable("MADT");
    }
    if(!ApicTable){
        LouPrint("Unable To Find APIC Using Backup Pic\n");
        LouKeInitializeBackupPic();
        return LOUSTATUS_GOOD;
    }

    disable_pic();

    uint8_t* EntryHeaderAddress = ((uint8_t*)ApicTable + sizeof(ACPI_MADT));
    uint8_t* HeaderEndAddress = ((uint8_t*)ApicTable + ApicTable->Header.Length);

    ParseAPIC(
        EntryHeaderAddress,
        HeaderEndAddress
    );

    LouKeInitializeEoiHandler((PVOID)local_apic_send_eoi, 0);

    if(InitializeApic())LouPrint("APIC ENABLED SUCCESSFULLY\n");
    else{   
        LouPrint("ERROR Could Not Initialize APIC\n");
        while(1);   
    }

    InitializeLapic(get_processor_id());

    //configure FPU for BSP

    ApicSet = true;

    PIO_APIC_TRACKER TmpIoApic = &IoApicTracker;

    while(TmpIoApic->Peers.NextHeader){
        TmpIoApic = (PIO_APIC_TRACKER)TmpIoApic->Peers.NextHeader;
    }

    SetTotalIoApicInterrupts(TmpIoApic->IoApic.GlobalSystemInterruptBase);

    TmpIoApic = &IoApicTracker;

    while(TmpIoApic->Peers.NextHeader){

        InitializeIoApic(&TmpIoApic->IoApic);

        TmpIoApic = (PIO_APIC_TRACKER)TmpIoApic->Peers.NextHeader;
    }
    
    ApicInstallIoApicHandlers();

    LouPrint(DRV_UNLOAD_STRING_SUCCESS_APIC);
    return Status;
}


LOUDDK_API_ENTRY void LouKeSendProcessorWakeupSignal(INTEGER TrackMember){

    mutex_t* Lock = (mutex_t*)(UINT64)0x7020;

    PCPU_TRACKER_INFORMATION CpuInfo = GetCpuInfoFromTrackerMember(TrackMember);
    UINT64 ApicBase = LouKeGetCurrentApicBase();
    UINT32 CpuID = CpuInfo->ProcID;
    UINT32 ApicID = CpuInfo->ApicID;
    
    if(CpuID > 0xFF){
        return;
    }

    LouPrint("Waking CPU:%d With Apic:%d IPI\n", CpuID, ApicID);


    WRITE_REGISTER_ULONG(ERR_STATUS_REGISTER, 0x00);
    WRITE_REGISTER_ULONG(ICR_REGISTER_HI, (READ_REGISTER_ULONG(ICR_REGISTER_HI) & ((1 << 24) - 1)) | ((ApicID & 0xFF) << 24));
    WRITE_REGISTER_ULONG(ICR_REGISTER_LOW, (READ_REGISTER_ULONG(ICR_REGISTER_LOW) & 0xFFF00000) | INIT_IPI_MAGIC);
    do {
        LouKePauseMemoryBarrier();
    }while(READ_REGISTER_ULONG(ICR_REGISTER_LOW) & (1 << 12));
    WRITE_REGISTER_ULONG(ICR_REGISTER_HI, (READ_REGISTER_ULONG(ICR_REGISTER_HI) & ((1 << 24) - 1)) | ((ApicID & 0xFF) << 24));
    WRITE_REGISTER_ULONG(ICR_REGISTER_LOW, (READ_REGISTER_ULONG(ICR_REGISTER_LOW) & 0xFFF00000) | DEASSERT_IPI_MAGIC);
    do {
        LouKePauseMemoryBarrier();
    }while(READ_REGISTER_ULONG(ICR_REGISTER_LOW) & (1 << 12));
    sleep(10);

    for(size_t i = 0 ; i < 2; i++){
        WRITE_REGISTER_ULONG(ERR_STATUS_REGISTER, 0x00);
        WRITE_REGISTER_ULONG(ICR_REGISTER_HI,  (READ_REGISTER_ULONG(ICR_REGISTER_HI) & ((1 << 24) - 1)) | ((ApicID & 0xFF) << 24));
        WRITE_REGISTER_ULONG(ICR_REGISTER_LOW, (READ_REGISTER_ULONG(ICR_REGISTER_LOW) & 0xFFF0F800) | 0x000608); //IPI 0x8000
        sleep(200);
        do {
            LouKePauseMemoryBarrier();
        }while(READ_REGISTER_ULONG(ICR_REGISTER_LOW) & (1 << 12));
    }
    
    size_t Timeout = 0;
    while(MutexIsLocked(Lock)){
        sleep(10);
        Timeout += 10;
        if(Timeout >= 100){
            MutexUnlock(Lock);
            break;
        }
    }   
    if(Timeout >= 100){
        LouPrint("Cpu:%d Faild To Wakeup In Time\n", CpuID);
        CpuInfo->Broken = true;
    }

}


LOUDDK_API_ENTRY void LocalApicSetTimer(bool On){
    //ULONG TimerValue = READ_REGISTER_ULONG(LVT_TIMER_REGISTER);
    //if(On){
    //    TimerValue |= (1 << 16);
    //}else{
    //    TimerValue &= ~(1 << 16);
    //}
    //WRITE_REGISTER_ULONG(LVT_TIMER_REGISTER, TimerValue);
}
