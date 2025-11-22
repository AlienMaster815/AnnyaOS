#include <LouAPI.h>

int LouPrintPanic(char* format, ...);

extern uint64_t InterruptCode;

uint64_t get_cr2() {
    uint64_t value;
    asm volatile ("movq %%cr2, %0" : "=r" (value));
    return value;
}

extern void clear_cr2();

bool IsCheckingPageFault = false;
bool CheckIsSuccess = true;

LOUSTATUS RequestPhysicalAddress(
    uint64_t VAddress,
    uint64_t* PAddress
);


typedef struct  PACKED _CPUContext{
    // General-Purpose Registers    
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rbp;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;

    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;

    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;

    uint64_t cs;
    uint64_t fq;
    uint64_t FaultStack;
    uint64_t ss;
} CPUContext;

PWINDHANDLE SetBlueScreenPannel();

void LouKeSetPanicInfo(
	PWINDHANDLE BsodHandle, string DynamicErrorMessage,
	uint64_t rax,
	uint64_t rbx,
	uint64_t rcx,
	uint64_t rdx,
	uint64_t rbp,
    uint64_t rsi,
    uint64_t rdi,
	uint64_t r8,
	uint64_t r9,
	uint64_t r10,
	uint64_t r11,
	uint64_t r12,
	uint64_t r13,
	uint64_t r14,
	uint64_t r15,
	uint64_t rip,
	uint64_t cs,
	uint64_t fq,
	uint64_t rsp,
	uint64_t ss,
    uint64_t PageFaultData
);

void LouKePanic(string Message, CPUContext* CpuContext, uint64_t PageFaultData);

void PageFault(uint64_t FaultingStackP) {
    uint64_t VAddress = get_cr2();
    uint64_t PAddress = 0x00;
    
    LouPrint("PAGE FUALT\n");
    RequestPhysicalAddress(VAddress, &PAddress);

    LouPrint("\nPage Fault Detected At Address %h Handleing Now\n",VAddress);
    LouPrint("Physical Address:%h\n", PAddress);

    //LouPrintPanic("\nPage Fault Detected At Address %h Handleing Now\n",VAddress);
    string PanicMessage = (string)LouGeneralAllocateMemoryEx(strlen("Page Fault Protection Violation At Address:%h") + 21, 1);

    _vsnprintf(PanicMessage, strlen("Page Fault Protection Violation At Address:%h") + 21, "Page Fault Protection Violation At Address:%h",  VAddress);
    // Check for specific error causes, e.g.:
    //if (InterruptCode & 0x1) {
        LouKePanic(PanicMessage, (CPUContext*)FaultingStackP, InterruptCode);
    //} else {
    //    if(PAddress != 0x00){
    //        //PAddress = (uint64_t)LouMalloc(KILOBYTE_PAGE);
    //        LouPrintPanic("Physicall Address Is:%h\n", PAddress);
    //        LouKeMapContinuousMemoryBlock(PAddress, VAddress, KILOBYTE_PAGE, KERNEL_PAGE_WRITE_PRESENT);
    //    }
    //    else{
    //        LouPrintPanic("Allocateing New Page\n");
    //        PAddress = (uint64_t)LouMalloc(KILOBYTE_PAGE);
    //        //LouKeMapcontinuousMemmoryBlock(PAddress, VAddress, KILOBYTE_PAGE, KERNEL_PAGE_WRITE_PRESENT);
    //        LouKeMapContinuousMemoryBlock(VAddress, VAddress, KILOBYTE_PAGE, KERNEL_PAGE_WRITE_PRESENT);
    //    }
    //}

    //clear_cr2();
    while(1);
}


