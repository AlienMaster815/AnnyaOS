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
    UINT64 ImageBase, ImageSize, ImageAlignment;
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

PCOFF_IMAGE_HEADER UnpackKernelImage(
    struct multiboot_tag* KernelTag,
    void* ImageBase
){
    UINT64 KSpaceBase = GetKSpaceBase();
    void* ImageVBase = (void*)((UINT64)ImageBase + KSpaceBase);
    struct multiboot_tag_module* KernelMod = (struct multiboot_tag_module*)KernelTag; 
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader((UINT8*)(UINT64)KernelMod->mod_start);
    memset(ImageVBase, 0, ImageHeader->OptionalHeader.PE64.SizeOfImage);
    memcpy(ImageVBase, (void*)(UINTPTR)KernelMod->mod_start, ImageHeader->OptionalHeader.PE64.SizeOfHeaders);

    size_t SectionCount = ImageHeader->StandardHeader.NumberOfSections;
    
    for(size_t i = 0; i < SectionCount; i++){
        if(ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress){
            memcpy(
                (void*)(ImageVBase + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress),
                (void*)((UINT64)KernelMod->mod_start + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData),
                ImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData
            );
        }
    }

    return (PCOFF_IMAGE_HEADER)((UINT64)ImageVBase + ((UINT64)ImageHeader - (UINT64)KernelMod->mod_start));
}

void RelocateKernelImage(
    PCOFF_IMAGE_HEADER KernelImage
){


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

    void* KernelImage = ReserveKernelMemory((struct multiboot_tag*)KernelLoaderInfo.KernelTag);

    LoaderCreateKernelSpace();

    UNUSED PCOFF_IMAGE_HEADER LousineImage = UnpackKernelImage((struct multiboot_tag*)KernelLoaderInfo.KernelTag, KernelImage);

    RelocateKernelImage(LousineImage);

    
    
    while(1);
}