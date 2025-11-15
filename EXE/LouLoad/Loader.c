#include <LouLoad.h>
#include <LoaderPrivate.h>

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};

extern LOULOAD_MEMORY_TRACKER MemoryTracker[512];

void ReserveKernelMemory(struct multiboot_tag* KernelTag){
    struct multiboot_tag_module* KernelMod = (struct multiboot_tag_module*)KernelTag; 
    UNUSED PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader((UINT8*)(UINT64)KernelMod->mod_start);

    

}

extern void LouLoaderStart(
    UINT64 MBoot,
    UINT64 BootStack
){
    UNUSED struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBoot + 8);
    KernelLoaderInfo.MultibootInfo = MBoot;
    KernelLoaderInfo.BootStack = BootStack;
    KernelLoaderInfo.RatPartition.RamMap = (UINT64)MemoryTracker;

    InitializeLoaderMultibootInformation(mboot);

    ReserveKernelMemory((struct multiboot_tag*)KernelLoaderInfo.KernelTag);

    while(1);
}