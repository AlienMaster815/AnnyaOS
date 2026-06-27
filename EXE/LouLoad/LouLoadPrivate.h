#define _LOUSINE_LOADER

#ifndef LOUSINE_LOADER_PRIVATE_H
#define LOUSINE_LOADER_PRIVATE_H

#include <LouLoad.h>
#include <Coff.h>
#include <Debug.h>

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")

static inline void LouKeReloadCR3(){
    uint64_t cr3;
    asm volatile ("mov %%cr3, %0" : "=r"(cr3));
    asm volatile ("mov %0, %%cr3" :: "r"(cr3));
}

PVOID memcpy(PVOID Dest, PCVOID Src, SIZE Size);
PVOID memset(PVOID Dest, int Val, SIZE Size);
PVOID memmove(PVOID Dest, PCVOID Src, SIZE Size);
int memcmp(void *VBuffer1, void *VBuffer2, UINT64 Count);

PVOID LoaderGetPhysicalAddress(PVOID Address);
UINT64* GetPageBase();
UINT64 GetCr3();
BOOLEAN LoaderInitializeMemoryManager(PLOADER_INFORMATION Info);
BOOLEAN LoaderInitializeKernelSpace(PLOADER_INFORMATION Info);
PVOID LouKeRatAllocatePhysicalAddress(SIZE Size, SIZE Alignment);

void cpuid(unsigned int code, unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx);
void cpuid_subleaf(unsigned int leaf, unsigned int subleaf, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx);
void LoaderGetCpuFeatures(PLOADER_INFORMATION Info);



#endif