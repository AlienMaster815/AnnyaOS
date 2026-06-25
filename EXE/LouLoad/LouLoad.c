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

    LoaderData.RatMbr = (PLOADER_RAT_MBR_CHUNK)((UINT64)LoaderData.RatMbr + KSpaceBase);

    PVOID LoaderBase = (PVOID)LoaderData.LoadedModules[1].Tracker.Base;
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader(LoaderBase);

    if(memcmp(&ImageHeader->StandardHeader.PeSignature, COFF_PE_SIGNATURE, 4)){
        asm("INT $0");
    }

    

    HaltAndCatchFile();
    return (LOUSTATUS)~0;
}