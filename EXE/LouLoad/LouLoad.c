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



    HaltAndCatchFile();
    return (LOUSTATUS)~0;
}