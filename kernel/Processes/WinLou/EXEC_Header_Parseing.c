#include <LouAPI.h>

#define TotalNeededVM ROUND_UP64((SectionHeader[CoffHeader->numberOfSections - 1].virtualAddress + SectionHeader[CoffHeader->numberOfSections - 1].virtualSize), KILOBYTE_PAGE)

uint64_t LouKeLinkerGetAddress(string ModuleName, string FunctionName);

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

void LouKeInitializeLibraryLookup(
    string    ModuleName,
    uint32_t  NumberOfFunctions,
    string*   FunctionNames,
    uint64_t* FunctionAddresses,
    bool IsNativeLongmode
);

void
LouKeInitializeKulaEmulatedFunctions(
    string      HostBinary,
    PKULA_TABLE Table
);

void ParseExportTables(
    uint64_t ModuleStart,
    PEXPORT_DIRECTORY_ENTRY ExportTable,
    bool IsLongModeBinary,
    string* pModuleName
){

    string ModuleName = (string)(ModuleStart + ExportTable->nameRva);
    *pModuleName = ModuleName;
    size_t koo = strlen(ModuleName);
    for(size_t foo = 0 ; foo < koo; foo++){
        ModuleName[foo] = toupper(ModuleName[foo]);
    }
    
    uint64_t* FunctionPointers = LouKeMallocArray(uint64_t, ExportTable->numberOfNamePointers, KERNEL_GENERIC_MEMORY);
    string* FunctionNames = LouKeMallocArray(string, ExportTable->numberOfNamePointers, KERNEL_GENERIC_MEMORY);

    //LouPrint("ATR:%h\n",ExportTable->exportAddressTableRva);
    //LouPrint("NPR:%h\n",ExportTable->namePointerRva);
    //LouPrint("OTR:%h\n",ExportTable->ordinalTableRva);

    uint16_t* OTR = (uint16_t*)(ModuleStart + ExportTable->ordinalTableRva);
    uint32_t* NPR = (uint32_t*)(ModuleStart + ExportTable->namePointerRva);
    uint32_t* ATR = (uint32_t*)(ModuleStart + ExportTable->exportAddressTableRva);

    for (uint32_t i = 0; i < ExportTable->numberOfNamePointers; i++) {

        uint16_t OTRIndex = OTR[i];

        FunctionNames[i] = (string)(ModuleStart + (uint64_t)(uint32_t)NPR[i]);
        FunctionPointers[i] = ModuleStart + (uint64_t)(uint32_t)ATR[OTRIndex];
        
        //LouPrint("ModuleName:%s Function Name:%s\n", ModuleName, FunctionNames[i]);
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
    PCOFF_HEADER COFF = (PCOFF_HEADER)GetPEHeader(DosHeader, COFF_T);
    PPE64_OPTIONAL_HEADER PE64 = (PPE64_OPTIONAL_HEADER)GetPEHeader(DosHeader, PE64_T);
    PSECTION_HEADER SECTIONS = (PSECTION_HEADER)GetPEHeader(DosHeader, SECTION_T);

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
    while(*(char*)((uintptr_t)FilePath + i) != '/'){
        i--;
    }
    return i + 1;
}

HANDLE LouKeLoadLibraryA(string LibraryName);
bool LouKeLinkerCheckLibraryPresence(string SystemName);

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
            size_t koo = strlen(SYSName);
            for(size_t foo = 0 ; foo < koo; foo++){
                SYSName[foo] = toupper(SYSName[foo]);
            }
            //LouPrint("Function Requested:%s\n", FunctionName);

            uint64_t AddressOfPeFunction = LouKeLinkerGetAddress(SYSName, FunctionName);
            if (!AddressOfPeFunction){
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

static inline void GetNewRelocVariableAddress(
    uint64_t NewBase,
    uint64_t VirtualAddress,
    uint64_t offsetWithinPage,
    uint64_t BaseDelta,
    bool AddressDrop
) {
    uint32_t* address = (uint32_t*)(NewBase + VirtualAddress + offsetWithinPage);

    if (ConfigCookie == *address) {
        return;
    }

    if (AddressDrop) {
        *address -= BaseDelta;
    } else {
        *address += BaseDelta;
    }
}

void RelocateBaseAddresses(
    uint64_t DataLocation,
    uint64_t NewBase,
    uint64_t OldBase,
    uint32_t size
) {
    bool AddressDrop = false; // variable for base delta sign
    uint64_t BaseDelta = 0; // initialize memory
    if (NewBase < OldBase) {
        AddressDrop = true;
        BaseDelta = OldBase - NewBase;
    } else if (NewBase > OldBase) {
        BaseDelta = NewBase - OldBase;
    } else {
        // nothing to be done
        return;
    }

    size_t offset = 0;
    while (offset < size) {
        IMAGE_BASE_RELOCATION* relocationBlock = (IMAGE_BASE_RELOCATION*)(DataLocation + offset);
        size_t numEntries = (relocationBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(uint16_t);
        uint16_t* typeOffsets = (uint16_t*)((uint8_t*)relocationBlock + sizeof(IMAGE_BASE_RELOCATION));

        for (size_t i = 0; i < numEntries; ++i) {
            uint16_t typeOffset = typeOffsets[i];
            uint16_t type = typeOffset >> 12;
            uint16_t offsetWithinPage = typeOffset & 0xFFF;

            switch (type) {
                case IMAGE_REL_BASED_HIGH:{
                    LouPrint("IMAGE_REL_BASED_HIGH\n");
                    while(1);   
                    continue;
                }
                case IMAGE_REL_BASED_LOW:{
                    LouPrint("IMAGE_REL_BASED_LOW\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_HIGHLOW:{
                    LouPrint("IMAGE_REL_BASED_HIGHLOW\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_HIGHADJ:{
                    LouPrint("IMAGE_REL_BASED_HIGHADJ\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_MIPS_JMPADDR:{
                    LouPrint("IMAGE_REL_BASED_MIPS_JMPADDR\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_SECTION:{
                    LouPrint("IMAGE_REL_BASED_SECTION\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_REL:{
                    LouPrint("IMAGE_REL_BASED_REL");
                    while(1);
                    continue;
                }

                case IMAGE_REL_BASED_MIPS_JMPADDR16:{
                    LouPrint("IMAGE_REL_BASED_MIPS_JMPADDR16\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_IA64_IMM64:{
                    LouPrint("IMAGE_REL_BASED_IA64_IMM64\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_DIR64:{                    
                    uint64_t* target = (uint64_t*)((relocationBlock->VirtualAddress + offsetWithinPage) + NewBase);
                    if(AddressDrop){
                        *target -= BaseDelta;
                    }else{
                        *target += BaseDelta;
                    }
                    break;
                }
                case IMAGE_REL_BASED_HIGH3ADJ: {
                    LouPrint("IMAGE_REL_BASED_HIGH3ADJ\n");
                    while(1);
                    continue;
                }
                case IMAGE_REL_BASED_ABSOLUTE:
                default:
                    continue;
            }
        }
        offset += relocationBlock->SizeOfBlock;
    }    
}

static inline void SetupConfigTable(
    uint64_t ProgramBase,
    uint64_t ImageBase,
    uint64_t Location,
    uint64_t size
) {
    PCONFIG_TABLE Conf = (PCONFIG_TABLE)Location;

    Conf->SecurityCookie = (Conf->SecurityCookie - ImageBase) + ProgramBase;

    if(ProgramBase == (uint64_t)Conf){
        //No Table It Happens!!!
        return;
    }

    *(uint64_t*)Conf->SecurityCookie = 81503;//(uint64_t)Random(ImageBase);
}

PHANDLE LoadKernelModule(uintptr_t Start, string ExecutablePath) {
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;    

    if (CheckDosHeaderValidity((PDOS_HEADER)(Start))) {
        //LouPrint("Found A Valid Kernel Module\n");
        GetAllPEHeaders(
            (PDOS_HEADER)Start,
            &CoffHeader,
            &PE64Header,
            &SectionHeader,
            0x00
        );
        //UNUSED PLOADED_WIN32_BINARY_OBJECT BinaryObject = LouKeCreateBinaryObjectLog(ExecutablePath);
        //LouKeLogBinaryTotalSize(BinaryObject, TotalNeededVM);

        //LouKeLogKernelBinary(BinaryObject, true);

        uint64_t allocatedModuleVirtualAddress =
        (uint64_t)LouKeMallocEx(
            TotalNeededVM,
            KILOBYTE_PAGE,
            KERNEL_PAGE_WRITE_PRESENT
        );
        //LouPrint("KernelModule:%s Loaded At Address:%h With Size:%h\n", ExecutablePath, allocatedModuleVirtualAddress, TotalNeededVM);
        //LouKeMapContinuousMemoryBlock(allocatedModuleVirtualAddress, allocatedModuleVirtualAddress, TotalNeededVM, PRESENT_PAGE | WRITEABLE_PAGE);
        //LouKeLogBinaryPhysicalAddress(BinaryObject, allocatedModuleVirtualAddress);


        memset((void*)allocatedModuleVirtualAddress, 0, TotalNeededVM);
        //LouKeMallocBinarySectionLogs(BinaryObject, CoffHeader->numberOfSections);

        // Align section addresses
        uint64_t sectionAlignment = PE64Header->sectionAlignment;

        for (uint16_t i = 0; i < CoffHeader->numberOfSections; i++) {
            uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress + sectionAlignment - 1) & ~(sectionAlignment - 1);

            //LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            //LouKeLogBinarySection(
            //    BinaryObject,
            //    i,
            //    &SectionHeader[i]
            //);

            memcpy(
                (void*)alignedVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

            //LouPrint("Copied section %s to address %h\n", SectionHeader[i].name, alignedVirtualAddress);
        }

        PIMPORT_DIRECTORY_ENTRY ImportTable = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);
        
        string ModuleName;

        ParseExportTables(
            allocatedModuleVirtualAddress,  
            ExportTable,
            true,
            &ModuleName
        );

        ParseImportTables(
            allocatedModuleVirtualAddress,
            ImportTable,
            ExecutablePath
        );

        // Locate the relocation table
        uint64_t relocationTable = (uint64_t)((uint64_t)allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTable(
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            allocatedModuleVirtualAddress + PE64Header->PE_Data_Directory_Entries[10].VirtualAddress,
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        RelocateBaseAddresses(
            relocationTable,
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            relocationTableSize
        );


        PKULA_TABLE NewTable = (PKULA_TABLE)LouKeLinkerGetAddress(ModuleName, "KulaTable"); 
        if(NewTable){
            LouKeInitializeKulaEmulatedFunctions(
                ModuleName,
                NewTable
            );
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        if(!PE64Header->addressOfEntryPoint){
            return 0x00;
        }
        return (PHANDLE)((uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
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

        //UNUSED PLOADED_WIN32_BINARY_OBJECT BinaryObject = LouKeCreateBinaryObjectLog(ExecutablePath);
        //LouKeLogBinaryTotalSize(BinaryObject, TotalNeededVM);

        uint64_t allocatedModuleVirtualAddress =
        (uint64_t)LouKeMallocEx(
            TotalNeededVM,
            PE64Header->sectionAlignment,
            USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
        );
        //LouPrint("User DLL:%s Loaded At Address:%h ans Size:%h\n", ExecutablePath, allocatedModuleVirtualAddress, TotalNeededVM);

        //LouKeMapContinuousMemoryBlock(allocatedModuleVirtualAddress, allocatedModuleVirtualAddress, TotalNeededVM, USER_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
        
        //LouKeLogBinaryPhysicalAddress(BinaryObject, allocatedModulePhysicalAddress);

        //LouKeMallocBinarySectionLogs(BinaryObject, CoffHeader->numberOfSections);
        for (uint16_t i = 0; i < CoffHeader->numberOfSections; i++) {
            uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress);

            //LouKeLogBinarySection(
            //    BinaryObject,
            //    i,
            //    &SectionHeader[i]
            //);

           // LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            memcpy(
                (void*)alignedVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

            //LouPrint("Copied section %s to address %h\n", SectionHeader[i].name, alignedVirtualAddress);
        }

        PIMPORT_DIRECTORY_ENTRY ImportTable = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);

        string ModuleName;

        if(PE64Header->PE_Data_Directory_Entries[0].VirtualAddress){
            ParseExportTables(
                allocatedModuleVirtualAddress,  
                ExportTable,
                true,
                &ModuleName
            );
        }

        if(PE64Header->PE_Data_Directory_Entries[1].VirtualAddress){
            ParseImportTables(
                allocatedModuleVirtualAddress,
                ImportTable,
                ExecutablePath
            );
        }

        // Locate the relocation table
        uint64_t relocationTable = (uint64_t)((uint64_t)allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTable(
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            allocatedModuleVirtualAddress + PE64Header->PE_Data_Directory_Entries[10].VirtualAddress,
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        RelocateBaseAddresses(
            relocationTable,
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            relocationTableSize
        );

        PKULA_TABLE NewTable = (PKULA_TABLE)LouKeLinkerGetAddress(ModuleName, "KulaTable"); 
        if(NewTable){
            LouKeInitializeKulaEmulatedFunctions(
                ModuleName,
                NewTable
            );
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        if(!PE64Header->addressOfEntryPoint){
            return 0x00;
        }
        return (DllModuleEntry)((uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
    } else {
        return 0x00;
    }
}

void* LoadPeExecutable(uintptr_t Start,string ExecutablePath){
    PCOFF_HEADER CoffHeader;
    PPE64_OPTIONAL_HEADER PE64Header;
    PSECTION_HEADER SectionHeader;


    if (CheckDosHeaderValidity((PDOS_HEADER)(Start))) {
        //LouPrint("Found A Valid Executeable\n");
        GetAllPEHeaders(
            (PDOS_HEADER)Start,
            &CoffHeader,
            &PE64Header,
            &SectionHeader,
            0x00
        );

        //UNUSED PLOADED_WIN32_BINARY_OBJECT BinaryObject = LouKeCreateBinaryObjectLog(ExecutablePath);
        //LouKeLogBinaryTotalSize(BinaryObject, TotalNeededVM);


        uint64_t allocatedModuleVirtualAddress =
        (uint64_t)LouKeMallocEx(
            TotalNeededVM,
            PE64Header->sectionAlignment,
            USER_PAGE | WRITEABLE_PAGE | PRESENT_PAGE
        );
        //LouPrint("User Executable:%s Loaded At Address:%h With Size:%h\n", ExecutablePath, allocatedModuleVirtualAddress, TotalNeededVM);

        //LouKeMapContinuousMemoryBlock(allocatedModuleVirtualAddress, allocatedModuleVirtualAddress, TotalNeededVM, USER_PAGE | PRESENT_PAGE | WRITEABLE_PAGE);
        
        // /LouKeLogBinaryPhysicalAddress(BinaryObject, allocatedModulePhysicalAddress);

        //LouKeLogBinaryVirtualAddress(BinaryObject, allocatedModuleVirtualAddress);

        //LouKeMallocBinarySectionLogs(BinaryObject, CoffHeader->numberOfSections);

        for (uint16_t i = 0; i < CoffHeader->numberOfSections; i++) {
            uint64_t alignedVirtualAddress = (allocatedModuleVirtualAddress + SectionHeader[i].virtualAddress); 

            //LouKeLogBinarySection(
            //    BinaryObject,
            //    i,
            //    &SectionHeader[i]
            //);

           // LouPrint("Section %s: aligned address %h\n", SectionHeader[i].name, alignedVirtualAddress);
            memcpy(
                (void*)alignedVirtualAddress,
                (void*)(Start + SectionHeader[i].pointerToRawData),
                SectionHeader[i].sizeOfRawData
            );

            //LouPrint("Copied section %s to address %h\n", SectionHeader[i].name, alignedVirtualAddress);
        }

        PIMPORT_DIRECTORY_ENTRY ImportTable = (PIMPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[1].VirtualAddress);
        PEXPORT_DIRECTORY_ENTRY ExportTable = (PEXPORT_DIRECTORY_ENTRY)(allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[0].VirtualAddress);
        
        string ModuleName;
        
        if((uintptr_t)ExportTable != (uintptr_t)allocatedModuleVirtualAddress){
            ParseExportTables(
                allocatedModuleVirtualAddress,  
                ExportTable,
                ExecutablePath,
                &ModuleName
            );
        }

        if((uintptr_t)ImportTable != (uintptr_t)allocatedModuleVirtualAddress){
            ParseImportTables(
                allocatedModuleVirtualAddress,
                ImportTable,
                ExecutablePath
            );
        }

        // Locate the relocation table
        uint64_t relocationTable = (uint64_t)((uint64_t)allocatedModuleVirtualAddress + (uint64_t)PE64Header->PE_Data_Directory_Entries[5].VirtualAddress);
        size_t relocationTableSize = PE64Header->PE_Data_Directory_Entries[5].Size;

        SetupConfigTable(
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            allocatedModuleVirtualAddress + PE64Header->PE_Data_Directory_Entries[10].VirtualAddress,
            PE64Header->PE_Data_Directory_Entries[10].Size
        );

        RelocateBaseAddresses(
            relocationTable,
            allocatedModuleVirtualAddress,
            PE64Header->imageBase,
            relocationTableSize
        );

        PKULA_TABLE NewTable = (PKULA_TABLE)LouKeLinkerGetAddress(ModuleName, "KulaTable"); 
        if(NewTable){
            LouKeInitializeKulaEmulatedFunctions(
                ModuleName,
                NewTable
            );
        }

        //LouPrint("Program Base:%h\n", allocatedModuleVirtualAddress);
        // Print function address debug info
        //LouPrint("Entry Point Address:%h\n", (uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
        return (void*)((uint64_t)PE64Header->addressOfEntryPoint + allocatedModuleVirtualAddress);
    } else {
        return 0x00;
    }
}


PPE32_PROCESS_EXECUTION_DATA InitializeProcessData(uintptr_t Start, string ExecutablePath){
    PPE32_PROCESS_EXECUTION_DATA ExecutionData = (PPE32_PROCESS_EXECUTION_DATA)LouKeMallocType(PE32_PROCESS_EXECUTION_DATA, KERNEL_GENERIC_MEMORY);
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

    LouPrint("Using Annya Subsystem For Windows (ASL) Version:%d:%d\n", 
        PE64Header->majorOperatingSystemVersion, PE64Header->minorOperatingSystemVersion);

    //ExecutionData->HeapCommit;

    return ExecutionData;
}
