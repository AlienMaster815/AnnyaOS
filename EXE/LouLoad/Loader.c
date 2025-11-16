#include <LouLoad.h>
#include <LoaderPrivate.h>

LOUSINE_LOADER_INFO KernelLoaderInfo = {0};

extern LOULOAD_MEMORY_TRACKER MemoryTracker[512];


bool LoaderRequestMemory(
    void*   Address,
    size_t  size
);

void* ReserveKernelMemory(struct multiboot_tag* KernelTag){

    struct multiboot_tag_module* KernelMod = (struct multiboot_tag_module*)KernelTag; 
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader((UINT8*)(UINT64)KernelMod->mod_start);
    UNUSED UINT64 ImageBase, ImageSize, ImageAlignment;
    BOOL MemoryReserved = false;
    ImageBase = ImageHeader->OptionalHeader.PE64.ImageBase;
    ImageSize = ImageHeader->OptionalHeader.PE64.SizeOfImage;
    ImageAlignment = ImageHeader->OptionalHeader.PE64.SectionAlignment;

    MemoryReserved = LoaderRequestMemory((void*)ImageBase, ImageSize);
    if(!MemoryReserved){
        ImageBase = (UINT64)LoaderAllocateMemoryEx((size_t)ImageSize, ImageAlignment);
    }

    return (void*)ImageBase;
}

extern void LouLoaderStart(
    UINT64 MBoot,
    UINT64 BootStack
){
    struct multiboot_tag* mboot = (struct multiboot_tag*)(uintptr_t)(MBoot + 8);

    KernelLoaderInfo.MultibootInfo = (UINT64)(UINT8*)mboot;
    KernelLoaderInfo.BootStack = BootStack;
    KernelLoaderInfo.RatPartition.BootPartition = (UINT64)MemoryTracker;

    InitializeLoaderMultibootInformation(mboot);


    UNUSED void* KernelImage = ReserveKernelMemory((struct multiboot_tag*)KernelLoaderInfo.KernelTag);

    LoaderCreateKernelSpace();


    

    while(1);
}