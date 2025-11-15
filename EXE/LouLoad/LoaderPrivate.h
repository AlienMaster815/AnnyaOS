#ifndef _LOADER_PRIVATE_H
#define _LOADER_PRIVATE_H
#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>

typedef struct _UNICODE_STRING{
    USHORT  Length;
    USHORT  MaximumLength;
    LPWSTR  Buffer;
}UNICODE_STRING, * PUNICODE_STRING, * LPUNICODE_STRING;

void EnforceLoaderMemoryMap(UINT64 Address, UINT64 size);
void InitializeModuleForLoading(struct multiboot_tag* Module);
void ParseRamMap(struct multiboot_tag* RamMap);
void InitializeLoaderMultibootInformation(struct multiboot_tag* MBoot);
int memcmp(void* pSource1, void* pSource2, size_t Count);
void memset(void* pDestination, size_t Count);

#define _LOUSINE_LOADER

#include <Coff.h>



#endif