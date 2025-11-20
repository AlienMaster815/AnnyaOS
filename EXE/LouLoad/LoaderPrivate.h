#ifndef _LOADER_PRIVATE_H
#define _LOADER_PRIVATE_H
#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>

typedef struct _UNICODE_STRING{
    USHORT  Length;
    USHORT  MaximumLength;
    LPWSTR  Buffer;
}UNICODE_STRING, * PUNICODE_STRING, * LPUNICODE_STRING;


static inline struct multiboot_mmap_entry* MapIndexToEntry(struct master_multiboot_mmap_entry* mmap, UINT16 i){
    return (struct multiboot_mmap_entry*)(uintptr_t)((uint64_t)mmap + (uint64_t)sizeof(struct master_multiboot_mmap_entry) + (uint64_t)i * (uint64_t)mmap->entry_size);
}

void EnforceLoaderMemoryMap(UINT64 Address, UINT64 size);
void InitializeModuleForLoading(struct multiboot_tag* Module);
void ParseRamMap(struct multiboot_tag* RamMap);
void InitializeLoaderMultibootInformation(struct multiboot_tag* MBoot);
int memcmp(void* pSource1, void* pSource2, size_t Count);
void memzero(void* pDestination, size_t Count);
void* LoaderAllocateMemory(size_t size);
void* LoaderAllocateMemoryEx(size_t size, size_t Alignment);
size_t GetRamSize();
void LoaderCreateKernelSpace();
void memcpy(void* pDestination, void* pSource, size_t Count);
void LoaderMapKernelMemoryBlock(UINT64 PAddress, UINT64 VAddress, UINT64 Size, UINT64 Flags);
// Constants for gigabyte and megabyte sizes
#define GIGABYTE (1ULL << 30)  // 1 GB in bytes
#define MEGABYTE (1ULL << 20)  // 1 MB in bytes
#define KILOBYTE (1 * 1024)

#define GetKSpaceBase() KernelLoaderInfo.KernelVm.KernelVmBase
#define SetKSpaceBase(x) KernelLoaderInfo.KernelVm.KernelVmBase = x



#define FLAGSSPACE 0x1FF

#define _LOUSINE_LOADER

#include <Coff.h>



#endif