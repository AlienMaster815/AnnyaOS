#include "Coff.h"

static void UnpackCoffImage(
    PCFI_OBJECT CfiObject
){
    //do basic unbacking for the loader
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader; 
    UINT64 LoadedAddress = (UINT64)CfiObject->LoadedAddress;
    UINT64 PhysicalLoadedAddress = (UINT64)CfiObject->PhysicalLoadedAddress;
    UINT64 RawData = (UINT64)CfiObject->CoffFile;

    UINT64 ISize = PeImageHeader->OptionalHeader.PE64.SizeOfImage;
    ISize = ROUND_UP64(ISize, KILOBYTE_PAGE);
    UINT64 KCopy = (UINT64)LouKeMallocPageEx(KILOBYTE_PAGE, ISize / KILOBYTE_PAGE , KERNEL_GENERIC_MEMORY, PhysicalLoadedAddress);

    memcpy((PVOID)LoadedAddress, (PVOID)RawData, PeImageHeader->OptionalHeader.PE64.SizeOfHeaders);

    size_t SectionCount = PeImageHeader->StandardHeader.NumberOfSections;
    UNUSED UINT32 SectionAlignment = PeImageHeader->OptionalHeader.PE64.SectionAlignment;
    
    for(size_t i = 0; i < SectionCount; i++){
        UINT64 PageFlags = CfiObject->KernelObject ? KERNEL_GENERIC_MEMORY : USER_GENERIC_MEMORY;
        UINT32 SectionCharacteristics = PeImageHeader->OptionalHeader.PE64.SectionTables[i].Characteristics;
        SIZE VirtualSize = (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualSize;
        VirtualSize = ROUND_UP64(VirtualSize, KILOBYTE_PAGE);
                
        if(SectionCharacteristics & CFI_SCN_CNT_INITIALIZED_DATA){
            memcpy((PVOID)(KCopy + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress), (PVOID)(RawData + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData), PeImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData);
        }

        if(SectionCharacteristics & CFI_SCN_MEM_NOT_PAGED){
            PageFlags &= ~PRESENT_PAGE;
        }       

        if(SectionCharacteristics & CFI_SCN_MEM_NOT_CACHED){
            PageFlags |= UNCACHEABLE_PAGE;
        }

        if(!(SectionCharacteristics & CFI_SCN_MEM_READ)){
            PageFlags &= ~PAGE_USER;
        }

        if(!(SectionCharacteristics & CFI_SCN_MEM_WRITE)){
            PageFlags &= ~WRITEABLE_PAGE;
        }
        
        LouKeMapContinuousMemoryBlock(
            PhysicalLoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress, 
            LoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress,
            VirtualSize,
            PageFlags
        );
    }    

    LouKeFreePage((PVOID)KCopy);

    CfiObject->ImageHeader = (PCOFF_IMAGE_HEADER)((UINT64)LoadedAddress + ((UINT64)PeImageHeader - RawData));
}

LOUSTATUS LouKeLoadCoffImageA64(
    PCFI_OBJECT CfiObject
){
    PCOFF_IMAGE_HEADER Pe64ImageHeader = CfiObject->ImageHeader; 

    CfiObject->LoadedAddress = (PVOID)Pe64ImageHeader->OptionalHeader.PE64.ImageBase;

    size_t ImageAlignment = Pe64ImageHeader->OptionalHeader.PE64.SectionAlignment;
    
    //this is a dirty way to get an alignment but screw it
    for(size_t i = 0 ; i < 63; i++){
        if(Pe64ImageHeader->OptionalHeader.PE64.ImageBase & (1ULL << i)){
            ImageAlignment = (1ULL << i);
            break;
        }   
    }

    LOUSTATUS Status = LouKeRequestVirtualAddressAllocation(
        Pe64ImageHeader->OptionalHeader.PE64.ImageBase,
        Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage
    );

    if(Status != STATUS_SUCCESS){
        LouPrint("WARNING:Prefered Image Base Is Not Available\n");
        if(!(Pe64ImageHeader->OptionalHeader.PE64.DllCharacteristics & CFI_DLLCHARACTERISTICS_DYNAMIC_BASE)){
            LouPrint("Error Loading Coff Image: Image Cannot Be Relocated\n");
            return STATUS_UNSUCCESSFUL;
        }
        CfiObject->LoadedAddress = LouVMallocEx(        
            Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage, 
            ImageAlignment
        );
    }
 
    CfiObject->PhysicalLoadedAddress = LouMallocEx64(Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage, ImageAlignment);

    LouKeMapContinuousMemoryBlock((UINT64)CfiObject->PhysicalLoadedAddress, (UINT64)CfiObject->LoadedAddress, Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage, KERNEL_GENERIC_MEMORY);

    UnpackCoffImage(CfiObject);

    //image header location changed
    Pe64ImageHeader = CfiObject->ImageHeader;

    if(memcmp((PVOID)(UINT8*)&Pe64ImageHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))){
        LouPrint("Error Loading Coff Image: File Could Not Fork\n");

    }

    

    return STATUS_SUCCESS;
}