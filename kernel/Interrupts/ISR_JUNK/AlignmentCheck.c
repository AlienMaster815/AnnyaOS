#include <LouAPI.h>
int LouPrintPanic(char* format, ...);

PWINDHANDLE SetBlueScreenPannel();
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
	uint64_t ss
);


void AlignmentCheck(uint64_t FaultingStackP) {

    PWINDHANDLE Bsod = SetBlueScreenPannel();

    CPUContext* FaultData = (CPUContext*)((uint64_t)FaultingStackP + 8);


    LouKeSetPanicInfo(
        Bsod, "Alignment Check",
        FaultData->rax, 
        FaultData->rbx, 
        FaultData->rcx, 
        FaultData->rdx,
        FaultData->rbp,
        FaultData->rsi,
        FaultData->rdi,
        FaultData->r8,
        FaultData->r9,
        FaultData->r10,
        FaultData->r11,
        FaultData->r12,
        FaultData->r13,
        FaultData->r14,
        FaultData->r15,
        FaultData->rip,
        FaultData->cs,
        FaultData->fq,
        FaultData->FaultStack,
        FaultData->ss
    );

	while (1);
}