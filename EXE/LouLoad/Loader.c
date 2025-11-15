#include <LouLoad.h>
#include <bootloader/grub/multiboot2.h>


void InitializeLoaderMultibootInformation(struct multiboot_tag* MBoot);
int memcmp(void* pSource1, void* pSource2, size_t Count);
void memset(void* pDestination, size_t Count);

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};

extern LOULOAD_MEMORY_TRACKER MemoryTracker[512];

extern void LouLoaderStart(
    UINT64 MBoot,
    UINT64 BootStack
){
    UNUSED struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBoot + 8);
    KernelLoaderInfo.MultibootInfo = MBoot;
    KernelLoaderInfo.BootStack = BootStack;
    KernelLoaderInfo.RatPartition.RamMap = (UINT64)MemoryTracker;

    InitializeLoaderMultibootInformation(mboot);


    while(1);
}