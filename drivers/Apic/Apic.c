#define APIC_MAIN
#include "ApicInternals.h"
#include <LouACPI.h>

static PMULTIPLE_APIC_DESCRIPTION_TABLE MadtTable = 0x00;
static BOOLEAN X2ApicSupport = false;
KERNEL_EXPORT LOUSTATUS LouKeInitializeIpicSubsystem(SIZE Processors);
KERNEL_EXPORT void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx);
PPER_PROCESSOR_APIC_DATA PerProcessorApicData = 0x00;

static BOOLEAN ApicDebugOn = false;

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
    if(X2ApicSupport){
        ApicHalDbgPrint("APIC.SYS:System Supports X2APIC Using X2APIC mode\n");
    }

    UINT8* TableEnd = (UINT8*)MadtTable + MadtTable->MadtHeader.Length;
    UINT8* TmpMadtLocation = &MadtTable->DynamicMADTBuffer[0];
    PMADT_ICS_COMMON_FORMAT_STRUCTURE CommonMadtFormat;


    while(TmpMadtLocation < TableEnd){
        CommonMadtFormat = (PMADT_ICS_COMMON_FORMAT_STRUCTURE)TmpMadtLocation;
        switch(CommonMadtFormat->Type){
            //case MADT_ICS_PROCESSOR_LOCAL_APIC:

            //    break;
            default:
                ApicHalDbgPrint("APIC.SYS:WARNING:Unhandled Madt Table Entry:Type:%h:Length:%h\n", (UINT64)CommonMadtFormat->Type, (UINT64)CommonMadtFormat->Length);
                break;
        }
        TmpMadtLocation += CommonMadtFormat->Length;
    }


    ApicHalDbgPrint("ApicInitializeApicSubsystem():STATUS_SUCCESS\n");
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