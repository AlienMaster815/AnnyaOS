#include <LouAPI.h>

#define TotalNeededVM (SectionHeader[CoffHeader->numberOfSections - 1].virtualAddress + SectionHeader[CoffHeader->numberOfSections - 1].virtualSize)

uint64_t LouKeLinkerGetAddress(string ModuleName, string FunctionName);

void LouKeInitializeLibraryLookup(
    string    ModuleName,
    uint32_t  NumberOfFunctions,
    string*   FunctionNames,
    uint64_t* FunctionAddresses,
    bool IsNativeLongmode
);

void ParseExportTables(
    uint64_t ModuleStart,
    PEXPORT_DIRECTORY_ENTRY ExportTable,
    bool IsLongModeBinary
){

    string ModuleName = (string)(ModuleStart + ExportTable->nameRva);
    uint64_t* FunctionPointers = LouKeMallocEx(ExportTable->numberOfNamePointers * sizeof(uint64_t), GET_ALIGNMENT(uint64_t), WRITEABLE_PAGE | PRESENT_PAGE);
    string* FunctionNames = LouKeMallocEx(sizeof(string*) * ExportTable->numberOfNamePointers, GET_ALIGNMENT(string*), WRITEABLE_PAGE | PRESENT_PAGE);

    if(strcmp(ModuleName, "kernbase.dll") == 0){
        ModuleName = "kernelbase.dll"; 
    }

    //LouPrint("ATR:%h\n",ExportTable->exportAddressTableRva);
    //LouPrint("NPR:%h\n",ExportTable->namePointerRva);
    //LouPrint("OTR:%h\n",ExportTable->ordinalTableRva);

    uint16_t* OTR = (uint16_t*)(ModuleStart + ExportTable->ordinalTableRva);
    uint32_t* NPR = (uint32_t*)(ModuleStart + ExportTable->namePointerRva);
    uint32_t* ATR = (uint32_t*)(ModuleStart + ExportTable->exportAddressTableRva);

    for (uint32_t i = 0; i < ExportTable->numberOfNamePointers; i++) {

        uint16_t OTRIndex = OTR[i];

        FunctionNames[i]    = (string) (NPR[i] + ModuleStart);
        FunctionPointers[i] = (uint64_t)(ATR[OTRIndex] + ModuleStart);

        //LouPrint("Function Name:%s\n", FunctionNames[i]);
        //LouPrint("Function Pointer:%h\n", FunctionPointers[i]);

    }

    LouKeInitializeLibraryLookup(
        ModuleName,
        ExportTable->numberOfNamePointers,
        FunctionNames,
        FunctionPointers,
        IsLongModeBinary
    );

}


bool CheckDosHeaderValidity(PDOS_HEADER PHeader) {
    //LouPrint("PHEADER:%h\n", PHeader);
    //LouPrint("Magic Value:%c%c\n", PHeader->e_magic[0], PHeader->e_magic[1]);

    if ((PHeader->e_magic[0] == 'M') && (PHeader->e_magic[1] == 'Z')) return true;
    return false;
}

typedef enum {
    COFF_T,
    PE64_T,
    SECTION_T,
    RICH_T,
} HeaderType;

#define ISOLATE_COFF (uintptr_t)((uintptr_t)DosHeader->e_lfanew + (uintptr_t)DosHeader)
#define ISOLATE_PE64 (uintptr_t)(ISOLATE_COFF + (uintptr_t)sizeof(COFF_HEADER))

static inline uintptr_t GetPEHeader(PDOS_HEADER DosHeader, HeaderType T) {
    if (T == COFF_T) {
        return ISOLATE_COFF;
    } else if (T == PE64_T) {
        return ISOLATE_PE64;
    } else if (T == SECTION_T) {
        PPE64_OPTIONAL_HEADER Pe64 = (PPE64_OPTIONAL_HEADER)ISOLATE_PE64;
        return (uintptr_t)&Pe64->PE_Data_Directory_Entries[Pe64->numberOfRvaAndSizes - 1] + sizeof(PE_DATA_DIRECTORY_ENTRY);
    }
    return 0x00;
}

void GetAllPEHeaders(
    PDOS_HEADER DosHeader,          // in
    PCOFF_HEADER* CoffHeader,       // out opt
    PPE64_OPTIONAL_HEADER* PE64Opt, // out opt
    PSECTION_HEADER* SectionHeaders,// out opt
    PRICH_HEADER* RichHeader        // out opt
) {
    volatile PCOFF_HEADER COFF = (volatile PCOFF_HEADER)GetPEHeader(DosHeader, COFF_T);
    volatile PPE64_OPTIONAL_HEADER PE64 = (volatile PPE64_OPTIONAL_HEADER)GetPEHeader(DosHeader, PE64_T);
    volatile PSECTION_HEADER SECTIONS = (volatile PSECTION_HEADER)GetPEHeader(DosHeader, SECTION_T);

    if (CoffHeader != 0x00) {
        *CoffHeader = COFF;
    }
    if (PE64Opt != 0x00) {
        *PE64Opt = PE64;
    }
    if (SectionHeaders != 0x00) {
        *SectionHeaders = SECTIONS;
    }
}

DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath);

static inline uint8_t FilePathCountBackToDirectory(string FilePath){
    uint16_t i = strlen(FilePath);
    //i know this looks weird this is not
    //my first implementation i couldent 
    //make it work otherwise
    while(*(volatile char*)((uintptr_t)FilePath + i) != '/'){
        i--;
    }
    return i + 1;
}

HANDLE LouKeLoadLibraryA(string LibraryName);
bool LouKeLinkerCheckLibraryPresence(string SystemName);
HANDLE LouKeLoadLibraryA(string LibraryName);

void ParseImportTables(
    uint64_t ModuleStart,
    PIMPORT_DIRECTORY_ENTRY ImportTable,
    string FilePath 
) {
    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t TableEntry;
    uint64_t TableOffset;
    string FunctionName;
    string SYSName;
    size_t DirectoryLength;
    string Directory;

    while (1) {
        if (ImportTable[j].ImportLookupRva == 0x00) {
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
            if(strcmp(SYSName, "kernelbase.dll") == 0){
                SYSName = "KERNBASE.DLL";
            }

            //LouPrint("Function Requested:%s\n", FunctionName);

            uint64_t AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);

            //TODO: Verify this logic works
            if((strncmp("ntdll.dll",SYSName, strlen("ntdll.dll")) == 0) && (!AddressOfPeFunction)){
                
                if(strncmp("_errno",FunctionName, strlen("_errno")) == 0){
                    FunctionName = "_errnoNT";
                    AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
                    goto _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL;
                }
                goto _NULL_LINKER_ADDRESS_ERROR_LABEL;
            }
            else if (!AddressOfPeFunction){
                _NULL_LINKER_ADDRESS_ERROR_LABEL:
                DirectoryLength = FilePathCountBackToDirectory(FilePath);
                Directory = (string)LouKeMalloc(DirectoryLength + strlen(SYSName) + 2, WRITEABLE_PAGE | PRESENT_PAGE);//apending two null strings
                

                strncpy(Directory, FilePath, DirectoryLength);
                strncpy((string)((uintptr_t)Directory + DirectoryLength), SYSName, strlen(SYSName));

                if(!LouKeLinkerCheckLibraryPresence(SYSName)){
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }

                    //Lousine Kernel some Files systems Are all uppercase
                    LouKeStrLowerToUpper(Directory);
                    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    
                    LouKeFree(Directory);

                    Directory = LouKeMalloc(strlen("C:/ANNYA/SYSTEM64/") + strlen(SYSName), WRITEABLE_PAGE | PRESENT_PAGE);
                    strncpy(Directory, "C:/ANNYA/SYSTEM64/", strlen("C:/ANNYA/SYSTEM64/"));
                    strncpy((string)((uint64_t)Directory + strlen("C:/ANNYA/SYSTEM64/")), SYSName, strlen(SYSName));    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    LouKeStrLowerToUpper(Directory);
                    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    

                    _LINKER_LOADED_A_MODULE:
                    LouPrint("Directory:%s\n", Directory);
                    AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
                    if(AddressOfPeFunction){
                        LouKeFree((void*)Directory);
                        goto _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL;
                    }
                }   
                LouPrint("ERROR M:E is 0 :: %s:%s\n", SYSName, FunctionName);
                while(1);
            }

            _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL:

            *(uint64_t*)TableOffset = AddressOfPeFunction;

            i += sizeof(uint64_t);
        }
        i = 0;
        j++;
    }

}

#define IMAGE_REL_BASED_ABSOLUTE        0x00
#define IMAGE_REL_BASED_HIGH            0x01
#define IMAGE_REL_BASED_LOW             0x02
#define IMAGE_REL_BASED_HIGHLOW         0x03
#define IMAGE_REL_BASED_HIGHADJ         0x04
#define IMAGE_REL_BASED_MIPS_JMPADDR    0x05
#define IMAGE_REL_BASED_SECTION         0x06
#define IMAGE_REL_BASED_REL             0x07
#define IMAGE_REL_BASED_MIPS_JMPADDR16  0x08
#define IMAGE_REL_BASED_IA64_IMM64      0x09
#define IMAGE_REL_BASED_DIR64           0x0A
#define IMAGE_REL_BASED_HIGH3ADJ        0x0B

typedef struct _IMAGE_BASE_RELOCATION {
    uint32_t VirtualAddress;
    uint32_t SizeOfBlock;
    // Followed by an array of TypeOffset entries
} IMAGE_BASE_RELOCATION;

uintptr_t ConfigCookie = 0;

PPE32_PROCESS_EXECUTION_DATA InitializeProcessData(uintptr_t Start, string ExecutablePath){
    PPE32_PROCESS_EXECUTION_DATA ExecutionData = (PPE32_PROCESS_EXECUTION_DATA)LouKeMallocEx(sizeof(PE32_PROCESS_EXECUTION_DATA), GET_ALIGNMENT(PE32_PROCESS_EXECUTION_DATA), WRITEABLE_PAGE | PRESENT_PAGE);
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;

    if(Start == 0){
        return 0x00;
    }

    LouPrint("Initializing Process Data\n");

    //at this point in the library 
    //mounting the library has 
    //already Verified that this
    //is a PE32 so no checking
    //is required now
    GetAllPEHeaders(
        (PDOS_HEADER)Start,
        &CoffHeader,
        &PE64Header,
        &SectionHeader,
        0x00
    );

    LouPrint("Using Annya Subsystem For Windows (ASW) Version:%d:%d\n", 
        PE64Header->majorOperatingSystemVersion, PE64Header->minorOperatingSystemVersion);

    //ExecutionData->HeapCommit;

    return ExecutionData;
}

typedef struct _SECTION_RELOCATION_PACKET{
    uint64_t    OldVirtualAddress;
    uint64_t    NewVirtualAddress;
    uint64_t    VirtualSize;
}SECTION_RELOCATION_PACKET, * PSECTION_RELOCATION_PACKET;

static uint64_t GetNewRva(
    PSECTION_RELOCATION_PACKET Relocations, 
    size_t RelocationCount,
    uint64_t OldRva
){
    for(size_t i = 0 ; i < RelocationCount; i++){
        if(RangeInterferes(
            OldRva,
            1,
            Relocations[i].OldVirtualAddress,
            Relocations[i].VirtualSize
        )){
            //calculate new virtualaddress and return
            return (OldRva - Relocations[i].OldVirtualAddress) + Relocations[i].NewVirtualAddress;
        }
    }
    return 0x00;
}


static inline void SetupConfigTableBySection(
    PSECTION_RELOCATION_PACKET Relocations,
    size_t  RelocationCount,
    uint64_t ImageBase,
    uint64_t Location,
    uint64_t size
) {
    PCONFIG_TABLE Conf = (PCONFIG_TABLE)Location;
    if(!Conf){
        return;
    }

    Conf->SecurityCookie = GetNewRva(Relocations, RelocationCount, (Conf->SecurityCookie - ImageBase));

    *(volatile uint64_t*)Conf->SecurityCookie = 81503;
}

void ParseExportTablesBySection(
    PSECTION_RELOCATION_PACKET Relocations,
    size_t  RelocationCount,
    PEXPORT_DIRECTORY_ENTRY ExportTable,
    bool IsLongModeBinary
){

    UNUSED string ModuleName = (string)GetNewRva(Relocations, RelocationCount, ExportTable->nameRva);
    uint64_t* FunctionPointers = LouKeMallocArray(uint64_t, ExportTable->numberOfNamePointers, KERNEL_GENERIC_MEMORY);
    string* FunctionNames = LouKeMallocArray(string*, ExportTable->numberOfNamePointers, KERNEL_GENERIC_MEMORY);

    if(strcmp(ModuleName, "kernbase.dll") == 0){
        ModuleName = "kernelbase.dll"; 
    }

    //LouPrint("ATR:%h\n",ExportTable->exportAddressTableRva);
    //LouPrint("NPR:%h\n",ExportTable->namePointerRva);
    //LouPrint("OTR:%h\n",ExportTable->ordinalTableRva);

    uint16_t* OTR = (uint16_t*)(GetNewRva(Relocations, RelocationCount, ExportTable->ordinalTableRva));
    uint32_t* NPR = (uint32_t*)(GetNewRva(Relocations, RelocationCount,  ExportTable->namePointerRva));
    uint32_t* ATR = (uint32_t*)(GetNewRva(Relocations, RelocationCount, ExportTable->exportAddressTableRva));

    for (uint32_t i = 0; i < ExportTable->numberOfNamePointers; i++) {

        uint16_t OTRIndex = OTR[i];

        FunctionNames[i]    = (string) (GetNewRva(Relocations, RelocationCount, NPR[i]));
        FunctionPointers[i] = (uint64_t)(GetNewRva(Relocations, RelocationCount, ATR[OTRIndex]));

        //LouPrint("Function Name:%s\n", FunctionNames[i]);
        //LouPrint("Function Pointer:%h\n", FunctionPointers[i]);

    }

    LouKeInitializeLibraryLookup(
        ModuleName,
        ExportTable->numberOfNamePointers,
        FunctionNames,
        FunctionPointers,
        IsLongModeBinary
    );

}


void ParseImportTablesBySection(
    PSECTION_RELOCATION_PACKET Relocations,
    size_t  RelocationCount,
    PIMPORT_DIRECTORY_ENTRY ImportTable,
    string FilePath 
) {
    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t TableEntry;
    uint64_t TableOffset;
    string FunctionName;
    string SYSName;
    size_t DirectoryLength;
    string Directory;

    while (1) {
        if (ImportTable[j].ImportLookupRva == 0x00) {
            break;
        }
        while (1) {

            TableEntry = *(uint64_t*)(uintptr_t)(GetNewRva(Relocations, RelocationCount, ImportTable[j].ImportLookupRva + i));
            if (TableEntry == 0) {
                break;
            }
            TableOffset = (GetNewRva(Relocations, RelocationCount, i + ImportTable[j].ImportAddressTableRva));
            FunctionName = (string)(GetNewRva(Relocations, RelocationCount, TableEntry + sizeof(uint16_t)));
            SYSName = (string)(GetNewRva(Relocations, RelocationCount, ImportTable[j].NameRva));
            if(strcmp(SYSName, "kernelbase.dll") == 0){
                SYSName = "KERNBASE.DLL";
            }

            //LouPrint("Function Requested:%s\n", FunctionName);

            uint64_t AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);

            //TODO: Verify this logic works
            if((strncmp("ntdll.dll",SYSName, strlen("ntdll.dll")) == 0) && (!AddressOfPeFunction)){
                
                if(strncmp("_errno",FunctionName, strlen("_errno")) == 0){
                    FunctionName = "_errnoNT";
                    AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
                    goto _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL;
                }
                goto _NULL_LINKER_ADDRESS_ERROR_LABEL;
            }
            else if (!AddressOfPeFunction){
                _NULL_LINKER_ADDRESS_ERROR_LABEL:
                DirectoryLength = FilePathCountBackToDirectory(FilePath);
                Directory = (string)LouKeMalloc(DirectoryLength + strlen(SYSName) + 2, WRITEABLE_PAGE | PRESENT_PAGE);//apending two null strings
                

                strncpy(Directory, FilePath, DirectoryLength);
                strncpy((string)((uintptr_t)Directory + DirectoryLength), SYSName, strlen(SYSName));

                if(!LouKeLinkerCheckLibraryPresence(SYSName)){
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }

                    //Lousine Kernel some Files systems Are all uppercase
                    LouKeStrLowerToUpper(Directory);
                    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    
                    LouKeFree(Directory);

                    Directory = LouKeMalloc(strlen("C:/ANNYA/SYSTEM64/") + strlen(SYSName), WRITEABLE_PAGE | PRESENT_PAGE);
                    strncpy(Directory, "C:/ANNYA/SYSTEM64/", strlen("C:/ANNYA/SYSTEM64/"));
                    strncpy((string)((uint64_t)Directory + strlen("C:/ANNYA/SYSTEM64/")), SYSName, strlen(SYSName));    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    LouKeStrLowerToUpper(Directory);
                    
                    if(fseek(Directory)){
                        LouKeLoadLibraryA(Directory);
                        goto _LINKER_LOADED_A_MODULE;
                    }
                    

                    _LINKER_LOADED_A_MODULE:
                    LouPrint("Directory:%s\n", Directory);
                    AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
                    if(AddressOfPeFunction){
                        LouKeFree((void*)Directory);
                        goto _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL;
                    }
                }   
                LouPrint("ERROR M:E is 0 :: %s:%s\n", SYSName, FunctionName);
                while(1);
            }

            _NULL_LINKER_ADDRESS_ERROR_RESOLVED_LABEL:

            *(uint64_t*)TableOffset = AddressOfPeFunction;

            i += sizeof(uint64_t);
        }
        i = 0;
        j++;
    }

}

void RelocateBaseAddressesBySection(
    PSECTION_RELOCATION_PACKET Relocations,
    size_t RelocationCount,
    uint64_t OldBase,
    uint64_t RelocationTable,
    size_t TableSize
) {
    size_t offset = 0;

    while (offset < TableSize) {
        IMAGE_BASE_RELOCATION* relocationBlock = (IMAGE_BASE_RELOCATION*)(RelocationTable + offset);
        size_t numEntries = (relocationBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
        uint16_t* typeOffsets = (uint16_t*)((uintptr_t)relocationBlock + sizeof(IMAGE_BASE_RELOCATION));

        for (size_t i = 0; i < numEntries; ++i) {
            uint16_t typeOffset = typeOffsets[i];
            uint16_t type = typeOffset >> 12;
            uint16_t offsetWithinPage = typeOffset & 0x0FFF;

            uint64_t targetRVA = relocationBlock->VirtualAddress + offsetWithinPage;
            uint64_t* patchAddr = (uint64_t*)GetNewRva(Relocations, RelocationCount, targetRVA);

            if (!patchAddr) {
                continue;
            }

            switch (type) {
                case IMAGE_REL_BASED_DIR64:
                    *patchAddr += GetNewRva(Relocations, RelocationCount, 0) - OldBase;
                    break;

                case IMAGE_REL_BASED_HIGHLOW:
                    *(uint32_t*)patchAddr += (uint32_t)(GetNewRva(Relocations, RelocationCount, 0) - OldBase);
                    break;

                case IMAGE_REL_BASED_ABSOLUTE:
                    // No relocation needed
                    break;

                default:
                    // Unknown or unsupported relocation type
                    break;
            }
        }

        offset += relocationBlock->SizeOfBlock;
    }
}


PHANDLE LoadKernelModule(uintptr_t Start, string ExecutablePath) {
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;

    if (CheckDosHeaderValidity((PDOS_HEADER)(Start))) {
        //LouPrint("Found A Valid Module\n");
        GetAllPEHeaders(
            (PDOS_HEADER)Start,
            &CoffHeader,
            &PE64Header,
            &SectionHeader,
            0x00
        );

        PSECTION_RELOCATION_PACKET SectionRlocations = LouKeMallocArray(SECTION_RELOCATION_PACKET, CoffHeader->numberOfSections, KERNEL_GENERIC_MEMORY);
        size_t SectionCount = CoffHeader->numberOfSections;
        for (uint16_t i = 0; i < SectionCount; i++) {
            //uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress);
            SectionRlocations[i].OldVirtualAddress = SectionHeader[i].virtualAddress;
            SectionRlocations[i].VirtualSize = SectionHeader[i].virtualSize;
            SectionRlocations[i].NewVirtualAddress = (uint64_t)LouKeMallocPage(KILOBYTE_PAGE, ROUND_UP64(SectionHeader[i].virtualSize, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY);

        
            //LouPrint("Section Placed At:%h From %h: And is %h: Bytes Long\n", SectionRlocations[i].NewVirtualAddress, SectionRlocations[i].OldVirtualAddress, SectionRlocations[i].VirtualSize);
           // LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            memcpy(
                (void*)SectionRlocations[i].NewVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

        }
        PIMPORT_DIRECTORY_ENTRY ImportTable = 0x00;// = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = 0x00;// = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);
        for(uint64_t i = 0 ; i < SectionCount; i++){
            if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[1].VirtualAddress){
                ImportTable = (PIMPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }else if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[0].VirtualAddress){
                ExportTable = (PEXPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }
            if((ImportTable) && (ExportTable))break;
        }

        if(ExportTable){
            //LouPrint("Parseing Export Table\n");
            ParseExportTablesBySection(
                SectionRlocations,
                SectionCount,
                ExportTable,
                true
            );
        }

        if(ImportTable){
            //LouPrint("Parseing Import Table\n");
            ParseImportTablesBySection(
                SectionRlocations,
                SectionCount,
                ImportTable,
                ExecutablePath
            );
        }

        uint64_t relocationTable = GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTableBySection(
            SectionRlocations,
            SectionCount,
            PE64Header->imageBase,
            GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[10].VirtualAddress),
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        if(relocationTable){
            RelocateBaseAddressesBySection(
                SectionRlocations,
                SectionCount,
                PE64Header->imageBase,
                relocationTable,
                relocationTableSize
            );
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        if(!PE64Header->addressOfEntryPoint){
            return 0x00;
        }
        return (PHANDLE)((uint64_t)GetNewRva(SectionRlocations, SectionCount, PE64Header->addressOfEntryPoint));
    } else {
        return 0x00;
    }
}

DllModuleEntry LoadUserDllModule(uintptr_t Start, string ExecutablePath){
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;

    if (CheckDosHeaderValidity((PDOS_HEADER)(Start))) {
        //LouPrint("Found A Valid Module\n");
        GetAllPEHeaders(
            (PDOS_HEADER)Start,
            &CoffHeader,
            &PE64Header,
            &SectionHeader,
            0x00
        );

        PSECTION_RELOCATION_PACKET SectionRlocations = LouKeMallocArray(SECTION_RELOCATION_PACKET, CoffHeader->numberOfSections, KERNEL_GENERIC_MEMORY);
        size_t SectionCount = CoffHeader->numberOfSections;
        for (uint16_t i = 0; i < SectionCount; i++) {
            //uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress);
            SectionRlocations[i].OldVirtualAddress = SectionHeader[i].virtualAddress;
            SectionRlocations[i].VirtualSize = SectionHeader[i].virtualSize;
            SectionRlocations[i].NewVirtualAddress = (uint64_t)LouKeMallocPage(KILOBYTE_PAGE, ROUND_UP64(SectionHeader[i].virtualSize, KILOBYTE_PAGE) / KILOBYTE_PAGE, USER_GENERIC_MEMORY);

        
            //LouPrint("Section Placed At:%h From %h: And is %h: Bytes Long\n", SectionRlocations[i].NewVirtualAddress, SectionRlocations[i].OldVirtualAddress, SectionRlocations[i].VirtualSize);
           // LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            memcpy(
                (void*)SectionRlocations[i].NewVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

        }
        PIMPORT_DIRECTORY_ENTRY ImportTable = 0x00;// = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = 0x00;// = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);
        for(uint64_t i = 0 ; i < SectionCount; i++){
            if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[1].VirtualAddress){
                ImportTable = (PIMPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }else if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[0].VirtualAddress){
                ExportTable = (PEXPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }
            if((ImportTable) && (ExportTable))break;
        }

        if(ExportTable){
            //LouPrint("Parseing Export Table\n");
            ParseExportTablesBySection(
                SectionRlocations,
                SectionCount,
                ExportTable,
                true
            );
        }

        if(ImportTable){
            //LouPrint("Parseing Import Table\n");
            ParseImportTablesBySection(
                SectionRlocations,
                SectionCount,
                ImportTable,
                ExecutablePath
            );
        }

        uint64_t relocationTable = GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTableBySection(
            SectionRlocations,
            SectionCount,
            PE64Header->imageBase,
            GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[10].VirtualAddress),
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        if(relocationTable){
            LouPrint("Relocation Table:%h :: %h Size:%h\n", relocationTable, PE64Header->PE_Data_Directory_Entries[5].VirtualAddress, relocationTableSize);
            while(1);
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        if(!PE64Header->addressOfEntryPoint){
            return 0x00;
        }
        return (DllModuleEntry)((uint64_t)GetNewRva(SectionRlocations, SectionCount, PE64Header->addressOfEntryPoint));
    } else {
        return 0x00;
    }
}


void* LoadPeExecutable(uintptr_t Start,string ExecutablePath){
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;

    if (CheckDosHeaderValidity((PDOS_HEADER)(Start))) {
        //LouPrint("Found A Valid Module\n");
        GetAllPEHeaders(
            (PDOS_HEADER)Start,
            &CoffHeader,
            &PE64Header,
            &SectionHeader,
            0x00
        );

        PSECTION_RELOCATION_PACKET SectionRlocations = LouKeMallocArray(SECTION_RELOCATION_PACKET, CoffHeader->numberOfSections, KERNEL_GENERIC_MEMORY);
        size_t SectionCount = CoffHeader->numberOfSections;
        for (uint16_t i = 0; i < SectionCount; i++) {
            //uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress);
            SectionRlocations[i].OldVirtualAddress = SectionHeader[i].virtualAddress;
            SectionRlocations[i].VirtualSize = SectionHeader[i].virtualSize;
            SectionRlocations[i].NewVirtualAddress = (uint64_t)LouKeMallocPage(KILOBYTE_PAGE, ROUND_UP64(SectionHeader[i].virtualSize, KILOBYTE_PAGE) / KILOBYTE_PAGE, USER_GENERIC_MEMORY);

        
            //LouPrint("Section Placed At:%h From %h: And is %h: Bytes Long\n", SectionRlocations[i].NewVirtualAddress, SectionRlocations[i].OldVirtualAddress, SectionRlocations[i].VirtualSize);
           // LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            memcpy(
                (void*)SectionRlocations[i].NewVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

        }
        PIMPORT_DIRECTORY_ENTRY ImportTable = 0x00;// = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = 0x00;// = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);
        for(uint64_t i = 0 ; i < SectionCount; i++){
            if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[1].VirtualAddress){
                ImportTable = (PIMPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }else if(SectionRlocations[i].OldVirtualAddress == PE64Header->PE_Data_Directory_Entries[0].VirtualAddress){
                ExportTable = (PEXPORT_DIRECTORY_ENTRY)SectionRlocations[i].NewVirtualAddress;
            }
            if((ImportTable) && (ExportTable))break;
        }

        if(ExportTable){
            //LouPrint("Parseing Export Table\n");
            ParseExportTablesBySection(
                SectionRlocations,
                SectionCount,
                ExportTable,
                true
            );
        }

        if(ImportTable){
            //LouPrint("Parseing Import Table\n");
            ParseImportTablesBySection(
                SectionRlocations,
                SectionCount,
                ImportTable,
                ExecutablePath
            );
        }

        uint64_t relocationTable = GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTableBySection(
            SectionRlocations,
            SectionCount,
            PE64Header->imageBase,
            GetNewRva(SectionRlocations, SectionCount, PE64Header->PE_Data_Directory_Entries[10].VirtualAddress),
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        if(relocationTable){
            RelocateBaseAddressesBySection(
                SectionRlocations,
                SectionCount,
                PE64Header->imageBase,
                relocationTable,
                relocationTableSize
            );
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        if(!PE64Header->addressOfEntryPoint){
            return 0x00;
        }
        return (DllModuleEntry)((uint64_t)GetNewRva(SectionRlocations, SectionCount, PE64Header->addressOfEntryPoint));
    } else {
        return 0x00;
    }
}