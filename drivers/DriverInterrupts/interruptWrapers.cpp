//TODO: Write a wrapper function for interrupt handleing

#include <LouDDK.h>

KERNEL_IMPORT void InterruptWrapper(uint64_t Handler,uint8_t InterruptNumber, bool NeedFlotationSave, uintptr_t OverideData);

void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uintptr_t OverideData) {
	InterruptWrapper((uint64_t)Handler, InterruptNumber, NeedFlotationSave, OverideData);
}