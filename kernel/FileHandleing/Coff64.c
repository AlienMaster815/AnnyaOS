#include "Coff.h"

UNUSED static void EnableCoffImageProtection(
    PCFI_OBJECT CfiObject
){
    //apply paging protections
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader; 
    UNUSED UINT64 LoadedAddress = (UINT64)CfiObject->LoadedAddress;
    UNUSED UINT64 PhysicalLoadedAddress = (UINT64)CfiObject->PhysicalLoadedAddress;
    
    size_t SectionCount = PeImageHeader->StandardHeader.NumberOfSections;
    UNUSED UINT32 SectionAlignment = PeImageHeader->OptionalHeader.PE64.SectionAlignment;
    
    for(size_t i = 0; i < SectionCount; i++){
        UINT64 PageFlags = CfiObject->KernelObject ? KERNEL_GENERIC_MEMORY : USER_GENERIC_MEMORY;
        UINT32 SectionCharacteristics = PeImageHeader->OptionalHeader.PE64.SectionTables[i].Characteristics;
        SIZE VirtualSize = (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualSize;
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
            PhysicalLoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress, 
            LoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress,
            VirtualSize,
            PageFlags
        );
    }    
}

static void UnpackCoffImage(
    PCFI_OBJECT CfiObject
){
    //do basic unbacking for the loader
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader; 
    UNUSED UINT64 LoadedAddress = (UINT64)CfiObject->LoadedAddress;
    UNUSED UINT64 PhysicalLoadedAddress = (UINT64)CfiObject->PhysicalLoadedAddress;
    UINT64 RawData = (UINT64)CfiObject->CoffFile;
    
    memcpy((PVOID)LoadedAddress, (PVOID)RawData, PeImageHeader->OptionalHeader.PE64.SizeOfHeaders);

    size_t SectionCount = PeImageHeader->StandardHeader.NumberOfSections;
    UNUSED UINT32 SectionAlignment = PeImageHeader->OptionalHeader.PE64.SectionAlignment;
    
    for(size_t i = 0; i < SectionCount; i++){
        SIZE VirtualSize = (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualSize;
        VirtualSize = ROUND_UP64(VirtualSize, KILOBYTE_PAGE);
                
        if(PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress){
            memcpy((PVOID)(LoadedAddress + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].VirtualAddress), (PVOID)(RawData + (UINT64)PeImageHeader->OptionalHeader.PE64.SectionTables[i].PointerToRawData), PeImageHeader->OptionalHeader.PE64.SectionTables[i].SizeOfRawData);
        }
    }
    CfiObject->ImageHeader = (PCOFF_IMAGE_HEADER)((UINT64)LoadedAddress + ((UINT64)PeImageHeader - RawData));
}

static LOUSTATUS ApplyCoffRelocations(
    PCFI_OBJECT CfiObject
){
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader;
    UINT64 RelocAddress = PeImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].VirtualAddress;
    if(!RelocAddress){
        return STATUS_SUCCESS;
    }
    UINT64 PreferedBase = PeImageHeader->OptionalHeader.PE64.ImageBase;
    UINT64 NewBase = (UINT64)(UINT8*)CfiObject->LoadedAddress;
    UNUSED UINT64 BaseDelta;
    UNUSED BOOL AddressDrop = false;

    RelocAddress += NewBase;

    if(NewBase < PreferedBase){
        AddressDrop = true;
        BaseDelta = PreferedBase - NewBase;
    }else{
        BaseDelta = NewBase - PreferedBase;
    }

    size_t Offset = 0;
    size_t RelocSize = PeImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_BASE_RELOCATION_TABLE].Size;
    while(Offset < RelocSize){
        PCFI_BASE_RELOCATION_BLOCK TmpReloc = (PCFI_BASE_RELOCATION_BLOCK)(UINT8*)(RelocAddress + Offset);
        size_t EntryCount = ((TmpReloc->BlockSize - sizeof(UINT64)) / sizeof(UINT16)); 
        for(size_t i = 0 ; i < EntryCount; i++){            
            switch(TmpReloc->RelocationEntires[i].Type){
                case CFI_BASE_RELOCATION_TYPE_BASED_DIR64:{
                    UNUSED UINT64* Target = (UINT64*)(UINT8*)(((UINT64)TmpReloc->PageRVA + (UINT64)TmpReloc->RelocationEntires[i].Offset) + NewBase);
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

    return STATUS_SUCCESS;
}

static LOUSTATUS ConfigureConfigurationStructure(PCFI_OBJECT CfiObject){
    //CFI_DDOFFSET_LOAD_CONFIG_TABLE
    PCOFF_IMAGE_HEADER PeImageHeader = CfiObject->ImageHeader;
    PCOFF_IMAGE_DATA_DIRECTORY LoadConfigTable = &PeImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_LOAD_CONFIG_TABLE];

    if(!LoadConfigTable->VirtualAddress){
        LouPrint("WARNING:Coff Load Config Table Was Not Found\n");
        return STATUS_SUCCESS;
    }

    PCFI_LOAD_CONFIGURATION_LAYOUT LoadConfigurationLayout = (PCFI_LOAD_CONFIGURATION_LAYOUT)(UINT8*)((UINTPTR)CfiObject->ImageHeader + (UINTPTR)LoadConfigTable->VirtualAddress);

    LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie = (((UINTPTR)LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie - (UINTPTR)PeImageHeader->OptionalHeader.PE64.ImageBase) + (UINTPTR)CfiObject->ImageHeader);

    *(UINT64*)LoadConfigurationLayout->LoadConfigurationLayout64.SecurityCookie = 81503;

    return STATUS_SUCCESS;
}

//continue from here on with coff 32

static LOUSTATUS ConfigureExportTables(
    PCFI_OBJECT CfiObject
){

    if(!CfiObject->ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_EXPORT_TABLE].VirtualAddress){
        return STATUS_SUCCESS;
    }

    UINTPTR ImageBase = (UINTPTR)CfiObject->LoadedAddress;
    PCFI_EXPORT_DIRECTORY_TABLE ExportTable = (PCFI_EXPORT_DIRECTORY_TABLE)((UINTPTR)CfiObject->LoadedAddress + (UINTPTR)CfiObject->ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_EXPORT_TABLE].VirtualAddress);
    CfiObject->FormalName = (string)(ImageBase + ExportTable->NameRVA);
    size_t Koo = strlen(CfiObject->FormalName);
    for(size_t Foo = 0 ; Foo < Koo; Foo++){
        CfiObject->FormalName[Foo] = toupper(CfiObject->FormalName[Foo]);
    }

    uint64_t* FunctionPointers = LouKeMallocArray(uint64_t, ExportTable->NumberOfNamePointers, KERNEL_GENERIC_MEMORY);
    string* FunctionNames = LouKeMallocArray(string, ExportTable->NumberOfNamePointers, KERNEL_GENERIC_MEMORY);


    uint16_t* OTR = (uint16_t*)(ImageBase + ExportTable->OrdinalTableRVA);
    uint32_t* NPR = (uint32_t*)(ImageBase + ExportTable->NamePointerTableRVA);
    uint32_t* ATR = (uint32_t*)(ImageBase + ExportTable->ExportAddressTableRVA);

    for (uint32_t i = 0; i < ExportTable->NumberOfNamePointers; i++) {

        uint16_t OTRIndex = OTR[i];

        FunctionNames[i] = (string)(ImageBase + (uint64_t)(uint32_t)NPR[i]);
        FunctionPointers[i] = ImageBase + (uint64_t)(uint32_t)ATR[OTRIndex];
        
        //LouPrint("ModuleName:%s Function Name:%s\n", ModuleName, FunctionNames[i]);
        //LouPrint("Function Pointer:%h\n", FunctionPointers[i]);
    }
    
    LouKeInitializeLibraryLookup(
        CfiObject->FormalName,
        ExportTable->NumberOfNamePointers,
        FunctionNames,
        FunctionPointers,
        CfiObject->AOA64 ? 0 : 1
    );

    return STATUS_SUCCESS;
}

static inline uint8_t FilePathCountBackToDirectory(string FilePath){
    uint16_t i = strlen(FilePath);
    //i know this looks weird this is not
    //my first implementation i couldent 
    //make it work otherwise
    while(*(char*)((uintptr_t)FilePath + i) != '/'){
        i--;
    }
    return i + 1;
}

static LOUSTATUS ConfigureImportTables(
    PCFI_OBJECT CfiObject
){
    //TODO: redo the error Handleing of this file
    uint64_t ModuleStart = (uint64_t)CfiObject->LoadedAddress;
    PIMPORT_DIRECTORY_ENTRY ImportTable = (PIMPORT_DIRECTORY_ENTRY)((UINTPTR)CfiObject->LoadedAddress + (UINTPTR)CfiObject->ImageHeader->OptionalHeader.PE64.DataDirectories[CFI_DDOFFSET_IMPORT_TABLE].VirtualAddress);;
    //string FilePath;

    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t TableEntry;
    uint64_t TableOffset;
    string FunctionName;
    string SYSName;
    //size_t DirectoryLength;
    //string Directory;

    while (1) {
        if(ImportTable[j].ImportLookupRva == 0x00) {
            break;
        }
        while (1) {

            TableEntry = *(uint64_t*)(uintptr_t)(ModuleStart + ImportTable[j].ImportLookupRva + i);
            if (TableEntry == 0) {
                break;
            }
            TableOffset = (i + ImportTable[j].ImportAddressTableRva + ModuleStart);
            FunctionName = (string)(TableEntry + ModuleStart + sizeof(uint16_t));
            SYSName = (string)(ModuleStart + ImportTable[j].NameRva);
            size_t koo = strlen(SYSName);
            for(size_t foo = 0 ; foo < koo; foo++){
                SYSName[foo] = toupper(SYSName[foo]);
            }
            //LouPrint("Function Requested:%s\n", FunctionName);

            uint64_t AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
            if (!AddressOfPeFunction){

                LouPrint("ERROR M:E is 0 :: %s:%s\n", SYSName, FunctionName);
                while(1);
                return STATUS_UNSUCCESSFUL;
            }

            //_NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL:

            *(uint64_t*)TableOffset = AddressOfPeFunction;

            i += sizeof(uint64_t);
        }
        i = 0;
        j++;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeLoadCoffImageA64(
    PCFI_OBJECT CfiObject
){

    PCOFF_IMAGE_HEADER Pe64ImageHeader = CfiObject->ImageHeader; 

    CfiObject->LoadedAddress = (PVOID)Pe64ImageHeader->OptionalHeader.PE64.ImageBase;

    
    UINT64 ISize = Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage;
    ISize = ROUND_UP64(ISize, KILOBYTE_PAGE);

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
            ISize, 
            ImageAlignment
        );
    }

    CfiObject->PhysicalLoadedAddress = LouMallocEx64(Pe64ImageHeader->OptionalHeader.PE64.SizeOfImage, ImageAlignment);

    LouKeMapContinuousMemoryBlock((UINT64)CfiObject->PhysicalLoadedAddress, (UINT64)CfiObject->LoadedAddress, ISize, KERNEL_GENERIC_MEMORY);

    UnpackCoffImage(CfiObject);

    //image header location changed
    Pe64ImageHeader = CfiObject->ImageHeader;

    if(memcmp((PVOID)(UINT8*)&Pe64ImageHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)COFF_PE_SIGNATURE, sizeof(UINT32))){
        LouPrint("Error Loading Coff Image: File Could Not Fork\n");
        return STATUS_UNSUCCESSFUL;
    }


    if((UINT64)CfiObject->LoadedAddress != (UINT64)Pe64ImageHeader->OptionalHeader.PE64.ImageBase){
        
        LouPrint("Applying New Relocations\n");
    
        Status = ApplyCoffRelocations(CfiObject);

        if(Status != STATUS_SUCCESS){
            LouPrint("Error Loading Coff Image: Image Relocations Could Not Be Applied\n");
        }

        LouPrint("Finished Applying Relocations\n");
    }

    Status = ConfigureConfigurationStructure(CfiObject);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = ConfigureExportTables(CfiObject);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    Status = ConfigureImportTables(CfiObject);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(CfiObject->ImageHeader->OptionalHeader.PE64.AddressOfEntryPoint){
        CfiObject->Entry = (PVOID)((UINT64)CfiObject->ImageHeader->OptionalHeader.PE64.AddressOfEntryPoint + (UINT64)CfiObject->LoadedAddress);
    }

    EnableCoffImageProtection(CfiObject);

    return STATUS_SUCCESS;
}