#include "LouLoadPrivate.h"

static LOADER_INFORMATION LoaderData = {0};

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

LOUSTATUS LouLoadStartLoader(
    UINT64  LimineData
){
    
    PLOADER_INFORMATION pLoaderData = (PLOADER_INFORMATION)LimineData;
    memcpy(&LoaderData, pLoaderData, sizeof(LOADER_INFORMATION));    

    //sanitize limine
    pLoaderData = 0x00;

    LoaderInitializeMemoryManager(&LoaderData);

    LoaderGetCpuFeatures(&LoaderData);

    BOOLEAN LockedAndLoaded = LoaderInitializeKernelSpace(&LoaderData);
    if(!LockedAndLoaded){
        asm("INT $0");
    }

    PVOID LoaderBase = (PVOID)LoaderData.LoadedModules[1].Tracker.Base;
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader(LoaderBase);

    if(memcmp(&ImageHeader->StandardHeader.PeSignature, COFF_PE_SIGNATURE, 4)){
        asm("INT $0");
    }

    LoaderData.KernelHandle = (KHANDLE)LouKeRatAllocatePhysicalAddress(ImageHeader->OptionalHeader.PE64.SizeOfImage, ImageHeader->OptionalHeader.PE64.SectionAlignment);
    if(!LoaderData.KernelHandle){
        asm("INT $0");
    }
    LoaderData.KernelHandle = (KHANDLE)((UINT64)LoaderData.KernelHandle + KSpaceBase); 
    memset(LoaderData.KernelHandle, 0, ImageHeader->OptionalHeader.PE64.SizeOfImage);



    HaltAndCatchFile();
    return (LOUSTATUS)~0;
}