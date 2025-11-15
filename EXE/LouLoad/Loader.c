#include <LouLoad.h>
#include <LoaderPrivate.h>

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};

extern LOULOAD_MEMORY_TRACKER MemoryTracker[512];

static void ReserveKernelMemory(UINT64 KernelTag){

    

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

    ReserveKernelMemory(KernelLoaderInfo.KernelTag);

    while(1);
}