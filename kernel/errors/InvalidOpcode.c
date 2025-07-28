#include <LouAPI.h>
extern uint64_t InstructionPointer;
int LouPrintPanic(char* format, ...);

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
	uint64_t ss
);


void InvalidOpcode(uint64_t FaultingStackP) {

    CPUContext* FualtingStack = (CPUContext*)FaultingStackP;
    LouPrint("Thread ID:%d\n", LouKeGetThreadIdentification());

    LouPrint("Thread IP:%h\n", FualtingStack->rip);
    LouPrint("Thread CS:%h\n", FualtingStack->cs);
    LouPrint("Thread FQ:%h\n", FualtingStack->fq);
    LouPrint("Thread SP:%h\n", FualtingStack->FaultStack);
    LouPrint("Thread SS:%h\n", FualtingStack->ss);


	while (1);
}