#include <kernel/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <kernel/errors.h>
#include <drivers/display/vga.h>
#include <stat.h>

#ifdef ARCH_I386_VGA_H
#define LOU_PANIC

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

LOUSTATUS SilentPanic() {
	LOUSTATUS Status = 1;


	return Status;
}

void VgaRgbModeFillBackgroundEx(uint8_t r,uint8_t g, uint8_t b, uint8_t a);


void LouPanicPrint(string Format){

}


void LouPanic(char* error_message,STATUS recoverable) {
	
	if (true == recoverable) {
		if(LOUSTATUS_GOOD == SilentPanic()) return;
	}

	//VgaRgbModeFillBackgroundEx(0,120,215,0);
	//PanicPrint(error_message);
    asm volatile("cli");
    asm volatile("hlt");
	while (1);
}

PWINDHANDLE SetBlueScreenPannel(){


	/*PWINDHANDLE Result = LouCreateCanvasBuffer(
		0,0,
		GetScreenBufferWidth(), GetScreenBufferHeight(),
		0x00,
		&BSODCharecteristics
	);

    LouChangeCanvasBufferColor(
        Result,
        0,
        0,
        128
    );*/

	return 0x00;//Result;
}

void LouKeLibTraceCheckPanic(
    UINT64 Instruction
);


void LouKeSetPanicMode(){
	UNUSED PWINDHANDLE Bsod = SetBlueScreenPannel();
}

void PlaceFloatingString(
    string FloatingString,
    int64_t x, int64_t y,
    uint16_t ScalingX, uint16_t ScalingY,
    uint8_t r, uint8_t g, uint8_t b,
    ...
);


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
){


/*
	UNUSED int64_t CurrentX = 0, CurrentY = 0;
	UNUSED int64_t CurrentW = 0, CurrentH = 0;

	CurrentW = GetScreenBufferWidth();
	CurrentH = GetScreenBufferHeight();

	CurrentX = (CurrentW / 16);	
	CurrentY = (CurrentH / 8);
	

	
	PlaceFloatingString(
		":(", 
		CurrentX, 
		CurrentY,
		18,18,
		255,
		255,
		255
	);

	CurrentY *= 3;

	PlaceFloatingString(
		"The Lousine Kernel has initialized a kernel panic. Information from the panic is below.", 
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);
	

	CurrentY += 28;
	size_t ErrorMessageSize = (strlen("The Fault Was Caused By A:%s") * strlen(DynamicErrorMessage));
	string ErrorMessage = (string)LouMallocEx(ErrorMessageSize, 1);
	_vsnprintf(ErrorMessage, ErrorMessageSize, "The Fault Was Caused By A:%s", DynamicErrorMessage);
	

	PlaceFloatingString(
		ErrorMessage,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	char TmpString[256];

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "RAX:%h :: RBX:%h :: RCX:%h :: RDX:%h", rax, rbx,rcx, rdx);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "RBP:%h :: RSI:%h :: RDI:%h :: R8:%h", rbp, rsi, rdi, r8);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "R9:%h :: R10:%h :: R11:%h :: R12:%h", r9, r10, r11, r12);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "R13:%h :: R14:%h :: R15:%h :: RIP:%h", r13, r14, r15, rip);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "CS:%h :: FQ:%h :: RSP:%h :: SS:%h", cs, fq, rsp, ss);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);
	 
	if(strcmp(DynamicErrorMessage, "Page Fault Protection Violation") == 0){
		goto _PAGE_FUALT_PANIC;
	}else {
		goto _GENERIC_FUALT_PANIC;
	}

	_PAGE_FUALT_PANIC:

	CurrentY += 28;
	_vsnprintf((string)TmpString, 256, "Page Fault At Address:%h", PageFaultData);
	PlaceFloatingString(
		(string)TmpString,
		CurrentX, 
		CurrentY,
		2,2,
		255,
		255,
		255
	);

	_GENERIC_FUALT_PANIC:
	LouKeDrsdSyncScreens();
	*/

	LouPrint("The Lousine Kernel has initialized a kernel panic. Information from the panic is below.\n");

	LouPrint("ThreadID:%d\n", LouKeGetThreadIdentification());

    LouKeLibTraceCheckPanic(rip);

	size_t ErrorMessageSize = (strlen("The Fault Was Caused By A:%s") * strlen(DynamicErrorMessage));
	string ErrorMessage = (string)LouGeneralAllocateMemoryEx(ErrorMessageSize, 1);
	_vsnprintf(ErrorMessage, ErrorMessageSize, "The Fault Was Caused By A:%s", DynamicErrorMessage);
	LouPrint("%s\n", ErrorMessage);

	char TmpString[256];

	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "RAX:%h :: RBX:%h", rax, rbx);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "RCX:%h :: RDX:%h", rcx, rdx);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "RBP:%h :: RSI:%h", rbp, rsi);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "RDI:%h :: R8 :%h", rdi, r8);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "R9 :%h :: R10:%h", r9, r10);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "R11:%h :: R12:%h", r11, r12);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "R13:%h :: R14:%h", r13, r14);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "R15:%h :: RIP:%h", r15, rip);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "CS :%h :: FQ :%h", cs, fq);
	LouPrint("%s\n", TmpString);
	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "RSP:%h :: SS :%h", rsp, ss);
	LouPrint("%s\n", TmpString);

	if(strncmp(DynamicErrorMessage, "Page Fault Protection Violation", strlen("Page Fault Protection Violation")) == 0){
		goto _PAGE_FUALT_PANIC;
	}else {
		goto _GENERIC_FUALT_PANIC;
	}

	_PAGE_FUALT_PANIC:

	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "Page Fault Code HexValue:%h", PageFaultData);
	LouPrint("%s\n", TmpString);

	_GENERIC_FUALT_PANIC:

	memset(TmpString, 0, 256);
	_vsnprintf((string)TmpString, 256, "Test:%h", 0xFFFF800000000000);
	LouPrint("%s\n", TmpString);

	while(1);
}

void LouKePanic(string Message, CPUContext* CpuContext, uint64_t PageFaultData){
        PWINDHANDLE Bsod = SetBlueScreenPannel();

        CPUContext* FaultData = (CPUContext*)((uint64_t)CpuContext);

        LouKeSetPanicInfo(
        Bsod, Message,
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
        FaultData->ss,
        PageFaultData
    );
    while(1);
}


#endif

