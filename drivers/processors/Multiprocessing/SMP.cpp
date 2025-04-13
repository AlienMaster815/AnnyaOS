#include <LouDDK.h>
#include "../APIC/apic.h"

UNUSED static uint64_t GDTPointer;
UNUSED static uint64_t IDTPointer;

struct DescriptorTablePointer {
    uint16_t limit;
    uint64_t base;
} __;

void get_gdt_pointer(DescriptorTablePointer& gdtp) {
    asm volatile("sgdt %0" : "=m"(gdtp) : : "memory");
}

void get_idt_pointer(DescriptorTablePointer& idtp) {
    asm volatile("sidt %0" : "=m"(idtp) : : "memory");
}

KERNEL_IMPORT void WakeTheFuckUpBoysTailCall();
KERNEL_IMPORT uint16_t GetNPROC();
KERNEL_IMPORT uint64_t getTrampolineAddressTailCall();
KERNEL_IMPORT uint64_t GetWakeTheFuckUpBoysEndTailCall();
//extern void* ap_trampoline;  // Trampoline code address


#define ICR_INIT       0x00000500
#define ICR_STARTUP    0x00000600
#define IPI_DEST_ALL_EXCLUDING_SELF 0x000C0000
#define COZZY_CODE_SPACE 0x00008000
#define APIC_ISR_BASE  0x100
#define APIC_ESR       0x280


typedef struct {
    uint32_t reserved[8];
    uint32_t icr_low;
    uint32_t icr_high;
} apic_t;

extern uint64_t ApicBase;
uint64_t GetApicBase();

void start_aps() {
    uint16_t NumberOfProcessors = GetNPROC();

    if(NumberOfProcessors > 1){

        for(uint8_t Count = 1; Count < NumberOfProcessors; Count++){
            LouPrint("Initializing Processor:%d\n", Count);


        }
   
        LouPrint("Done Initializing Processors\n");
    }

    while(1);
}


LOUDDK_API_ENTRY void SMPInit(){

    LouPrint("Initializing SMP\n");

    start_aps();

    LouPrint("Done With SMP Initialization\n");
}


LOUDDK_API_ENTRY uint64_t GetGdtPointer(){
    return GDTPointer;
}

 LOUDDK_API_ENTRY uint64_t GetIdtPointer(){
    return IDTPointer;
 }

