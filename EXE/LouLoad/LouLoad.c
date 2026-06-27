#include "LouLoadPrivate.h"

static LOADER_INFORMATION LoaderData = {0};

static void HaltAndCatchFile() {
    for (;;) {
        asm ("hlt");
    }
}

void UnpackKernel(PCOFF_IMAGE_HEADER* ImageHeaderp, PVOID PhysicalAddress, PVOID CoffData){
    PCOFF_IMAGE_HEADER ImageHeader = *ImageHeaderp;

    memcpy(PhysicalAddress, CoffData, ImageHeader->OptionalHeader.PE64.SizeOfHeaders);
    SIZE SectionCount = ImageHeader->StandardHeader.NumberOfSections;

    for(SIZE i = 0; i < SectionCount; i++){
        if(ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData){
            memcpy(
                (PVOID)((UINT64)PhysicalAddress + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress),
                (PVOID)((UINT64)CoffData + (UINT64)ImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData),
                ImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData
            );
        }
    }    
    *ImageHeaderp = (PCOFF_IMAGE_HEADER)((UINT64)PhysicalAddress + ((UINT64)ImageHeader - (UINT64)CoffData));
}

BOOLEAN ApplyKernelRelocation(
    PCOFF_IMAGE_HEADER  ImageHeader,
    PVOID               PhysicalAddress
){
    UINT64 RelocAddress = ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].VirtualAddress;
    if(!RelocAddress){
        return true;
    }
    UINT64  PreferedBase = ImageHeader->OptionalHeader.PE64.ImageBase;
    UINT64  BaseDelta;
    BOOLEAN AddressDrop = false;

    RelocAddress += (UINT64)PhysicalAddress;

    if((UINT64)PhysicalAddress < PreferedBase){
        AddressDrop = true;
        BaseDelta = PreferedBase - (UINT64)PhysicalAddress;
    }else{
        BaseDelta = (UINT64)PhysicalAddress - PreferedBase;
    }

    SIZE Offset = 0;
    SIZE RelocSize = ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].Size;
    while(Offset < RelocSize){
        PCFI_BASE_RELOCATION_BLOCK TmpReloc = (PCFI_BASE_RELOCATION_BLOCK)(UINT8*)(RelocAddress + Offset);
        SIZE EntryCount = ((TmpReloc->BlockSize - sizeof(UINT64)) / sizeof(UINT16));
        for(SIZE i = 0 ; i < EntryCount; i++){
            switch(TmpReloc->RelocationEntries[i].Type){
                case CFI_BASE_RELOCATION_TYPE_BASED_DIR64:{
                    UINT64* Target = (UINT64*)(UINT8*)(((UINT64)TmpReloc->PageRVA + (UINT64)TmpReloc->RelocationEntries[i].Offset) + PhysicalAddress); 
                    if(AddressDrop){
                        *Target -= BaseDelta;
                    }else{
                        *Target += BaseDelta;
                    }
                    break;
                }
                default:
                    continue;
            }
        }
        Offset += TmpReloc->BlockSize;
    }
    return true;
}

extern void MsvcAbiJump(UINT64 Param1, UINT64 Stack, UINT64 Entry);

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

    PVOID KernelBase = (PVOID)LoaderData.LoadedModules[1].Tracker.Base;
    PCOFF_IMAGE_HEADER ImageHeader = CoffGetImageHeader(KernelBase);

    if(memcmp(&ImageHeader->StandardHeader.PeSignature, COFF_PE_SIGNATURE, 4)){
        asm("INT $0");
    }

    LoaderData.KernelHandle = (KHANDLE)LouKeRatAllocatePhysicalAddress(ImageHeader->OptionalHeader.PE64.SizeOfImage, ImageHeader->OptionalHeader.PE64.SectionAlignment);
    if(!LoaderData.KernelHandle){
        asm("INT $0");
    }
    LoaderData.KernelHandle = (KHANDLE)((UINT64)LoaderData.KernelHandle + KSpaceBase); 
    memset(LoaderData.KernelHandle, 0, ImageHeader->OptionalHeader.PE64.SizeOfImage);

    UnpackKernel(&ImageHeader, LoaderData.KernelHandle, KernelBase);

    if(memcmp(&ImageHeader->StandardHeader.PeSignature, COFF_PE_SIGNATURE, 4)){
        asm("INT $0");
    }

    ApplyKernelRelocation(ImageHeader, LoaderData.KernelHandle);
    UINT64 KernelEntry = (UINT64)(ImageHeader->OptionalHeader.PE64.AddressOfEntryPoint + (UINT64)LoaderData.KernelHandle); 
    if(!KernelEntry){
        asm("INT $0");
    }


    UINT64 KernelStack = ((UINT64)LouKeRatAllocatePhysicalAddress(16 * KILOBYTE, 16) + (16 * KILOBYTE)) + KSpaceBase;
    LoaderData.KernelStackHandle = (KHANDLE)KernelStack;

    MsvcAbiJump((UINT64)&LoaderData, KernelStack, KernelEntry);

    HaltAndCatchFile();
    return (LOUSTATUS)~0;
}