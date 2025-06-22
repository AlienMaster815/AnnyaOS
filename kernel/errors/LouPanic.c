#include <kernel/kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <kernel/errors.h>
#include <drivers/display/vga.h>
#include <stat.h>

#ifdef ARCH_I386_VGA_H
#define LOU_PANIC

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
	WINDOW_CHARECTERISTICS BSODCharecteristics;
    BSODCharecteristics.Type = CANVAS_WINDOW;
    BSODCharecteristics.WindowName = "BSOD";


	PWINDHANDLE Result = LouCreateCanvasBuffer(
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
    );

	return Result;
}


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
	while(1);
}

#endif

