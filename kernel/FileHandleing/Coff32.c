#include "Coff.h"

UNUSED static void EnableCoffImageProtection(
    PCFI_OBJECT CfiObject
){
    //apply paging protections
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader; 
    UNUSED UINT64 LoadedAddress = (UINT64)CfiObject->LoadedAddress;
    UNUSED UINT64 PhysicalLoadedAddress = (UINT64)CfiObject->PhysicalLoadedAddress;
    
    size_t SectionCount = PeImageHeader->StandardHeader.NumberOfSections;
    UNUSED UINT32 SectionAlignment = PeImageHeader->OptionalHeader.PE32.SectionAlignment;
    
    for(size_t i = 0; i < SectionCount; i++){
        UINT64 PageFlags = CfiObject->KernelObject ? KERNEL_GENERIC_MEMORY : USER_GENERIC_MEMORY;
        UINT32 SectionCharacteristics = PeImageHeader->OptionalHeader.PE32.SectionTables[i].Characteristics;
        SIZE VirtualSize = (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].VirtualSize;
        VirtualSize = ROUND_UP64(VirtualSize, KILOBYTE_PAGE);
                
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
            PhysicalLoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].VirtualAddress, 
            LoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].VirtualAddress,
            VirtualSize,
            PageFlags
        );
    }    
}

UNUSED static void UnpackCoffImage(
    PCFI_OBJECT CfiObject
){
    //do basic unbacking for the loader
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader; 
    UNUSED UINT64 LoadedAddress = (UINT64)CfiObject->LoadedAddress;
    UNUSED UINT64 PhysicalLoadedAddress = (UINT64)CfiObject->PhysicalLoadedAddress;
    UINT64 RawData = (UINT64)CfiObject->CoffFile;
    
    memcpy((PVOID)LoadedAddress, (PVOID)RawData, PeImageHeader->OptionalHeader.PE32.SizeOfHeaders);

    size_t SectionCount = PeImageHeader->StandardHeader.NumberOfSections;
    UNUSED UINT32 SectionAlignment = PeImageHeader->OptionalHeader.PE32.SectionAlignment;
    
    for(size_t i = 0; i < SectionCount; i++){
        UINT32 SectionCharacteristics = PeImageHeader->OptionalHeader.PE32.SectionTables[i].Characteristics;
        SIZE VirtualSize = (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].VirtualSize;
        VirtualSize = ROUND_UP64(VirtualSize, KILOBYTE_PAGE);
                
        if(SectionCharacteristics & CFI_SCN_CNT_INITIALIZED_DATA){
            memcpy((PVOID)(LoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].VirtualAddress), (PVOID)(RawData + (UINT64)PeImageHeader->OptionalHeader.PE32.SectionTables[i].PointerToRawData), PeImageHeader->OptionalHeader.PE32.SectionTables[i].SizeOfRawData);
        }
    }
    CfiObject->ImageHeader = (PCOFF_IMAGE_HEADER)((UINT64)LoadedAddress + ((UINT64)PeImageHeader - RawData));
}


UNUSED static LOUSTATUS ApplyCoffRelocations(
    PCFI_OBJECT CfiObject
){
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader;
    UINT32 RelocAddress = PeImageHeader->OptionalHeader.PE32.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].VirtualAddress;
    if(!RelocAddress){
        return STATUS_SUCCESS;
    }
    UINT32 PreferedBase = PeImageHeader->OptionalHeader.PE32.ImageBase;
    UINT32 NewBase = (UINT32)(UINTPTR)(UINT8*)CfiObject->LoadedAddress;
    UNUSED UINT32 BaseDelta;
    UNUSED BOOL AddressDrop = false;

    RelocAddress += NewBase;

    if(NewBase < PreferedBase){
        AddressDrop = true;
        BaseDelta = PreferedBase - NewBase;
    }else{
        BaseDelta = NewBase - PreferedBase;
    }

    size_t Offset = 0;
    size_t RelocSize = PeImageHeader->OptionalHeader.PE32.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].Size;
    while(Offset < RelocSize){
        PCFI_BASE_RELOCATION_BLOCK TmpReloc = (PCFI_BASE_RELOCATION_BLOCK)(UINT8*)(RelocAddress + Offset);
        size_t EntryCount = ((TmpReloc->BlockSize - sizeof(UINT32)) / sizeof(UINT16)); 
        for(size_t i = 0 ; i < EntryCount; i++){            
            switch(TmpReloc->RelocationEntires[i].Type){
                case CFI_BASE_RELOCATION_TYPE_BASED_HIGH_LOW:{
                    UNUSED UINT32* Target = (UINT32*)(UINTPTR)(((UINT32)TmpReloc->PageRVA + (UINT32)TmpReloc->RelocationEntires[i].Offset) + NewBase);
                    if(AddressDrop){
                        *Target -= BaseDelta;
                    
                    }else{
                        *Target += BaseDelta;
                    }
                    break;
                }
                case CFI_BASE_RELOCATION_TYPE_BASED_HIGH:{
                    UNUSED UINT16* Target = (UINT16*)(UINTPTR)(((UINT32)TmpReloc->PageRVA + (UINT32)TmpReloc->RelocationEntires[i].Offset) + NewBase);
                    if(AddressDrop){
                        *Target -= (BaseDelta >> 16);
                    
                    }else{
                        *Target += (BaseDelta >> 16);
                    }
                    break;
                }
                case CFI_BASE_RELOCATION_TYPE_BASED_LOW:{
                    UNUSED UINT16* Target = (UINT16*)(UINTPTR)(((UINT32)TmpReloc->PageRVA + (UINT32)TmpReloc->RelocationEntires[i].Offset) + NewBase);
                    if(AddressDrop){
                        *Target -= (BaseDelta & 0xFF);
                    
                    }else{
                        *Target += (BaseDelta & 0xFF);
                    }
                    break;
                }
                case CFI_BASE_RELOCATION_TYPE_BASED_HIGH_ADJ:
                {
                    if (i + 1 >= EntryCount) {
                        return STATUS_ILLEGAL_DLL_RELOCATION;
                    }
                    UINT16* HighWord = (UINT16*)(UINTPTR)(NewBase + TmpReloc->PageRVA + TmpReloc->RelocationEntires[i].Offset);
                    UINT16 LowEntryRaw = TmpReloc->RelocationEntires[i + 1].SanityIndexor;
                    UINT16 LowOffset   = (LowEntryRaw & 0x0FFF);
                    UINT16* LowWord = (UINT16*)(UINTPTR)(NewBase + TmpReloc->PageRVA + LowOffset);
                    UINT32 Original = ((UINT32)(*HighWord) << 16) | (*LowWord);
                    UINT32 Adjusted;
                    if (AddressDrop){
                        Adjusted = Original - BaseDelta;
                    }
                    else{
                        Adjusted = Original + BaseDelta;
                    }
                    *HighWord = (UINT16)(Adjusted >> 16);
                    i++;
                    break;
                }
                default:
                    continue;
            }

        }
        Offset += TmpReloc->BlockSize;
    }   

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeLoadCoffImageA32(
    PCFI_OBJECT CoffObject
){
    LouPrint("LouKeLoadCoffImageA32()\n");
    while(1);
    return STATUS_SUCCESS;
}