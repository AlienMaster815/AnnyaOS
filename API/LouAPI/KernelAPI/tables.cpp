#include <LouDDK.h>
#include <NtAPI.h>
#include <Hal.h>


typedef struct _TABLE_ENTRY{
    FILE_NAME        ModuleName;
    uint32_t         NumberOfFunctions;
    FUNCTION_NAME*   FunctionName;
    uint64_t*        VirtualAddress;
}TABLE_ENTRY, * PTABLE_ENTRY;

typedef struct _TableTracks{
    ListHeader Neighbors;
    TABLE_ENTRY Table;
    bool LongModeEntry;
}TableTracks, * PTableTracks;

#define PRE_LOADED_MODULES 5
#define PRE_LOADED_NTOSKRNL_FUNCTIONS 75
#define PRE_LOADED_UNKOWN_FUNCTIONS 12
#define PRE_LOADED_WDFLDR_FUNCTIONS 5
#define PRE_LOADED_STORPORT_FUNCTIONS 9
#define PRE_LOADED_LOUOSKRNL_FUNCTIONS 172

static uint64_t LouOsKrnlFunctionAddresses[PRE_LOADED_LOUOSKRNL_FUNCTIONS];
static FUNCTION_NAME LouOsKrnlFunctionNames[PRE_LOADED_LOUOSKRNL_FUNCTIONS];
static uint64_t NTFunctionAddresses[PRE_LOADED_NTOSKRNL_FUNCTIONS];
static FUNCTION_NAME NTFunctionNames[PRE_LOADED_NTOSKRNL_FUNCTIONS];
static uint64_t UnkownFunctionAddresses[PRE_LOADED_UNKOWN_FUNCTIONS];
static FUNCTION_NAME UnkownFunctionNames[PRE_LOADED_UNKOWN_FUNCTIONS];
static uint64_t WDFLDRFunctionAddresses[PRE_LOADED_WDFLDR_FUNCTIONS];
static FUNCTION_NAME WDFLDRFunctionNames[PRE_LOADED_WDFLDR_FUNCTIONS];
static uint64_t StorportFunctionAddresses[PRE_LOADED_STORPORT_FUNCTIONS];
static FUNCTION_NAME StorportFunctionNames[PRE_LOADED_STORPORT_FUNCTIONS];

static TableTracks  DynamicLoadedLibraries;
static size_t DynamicLoadedLibrarieCount = 0x00;

static TABLE_ENTRY GenericTable[PRE_LOADED_MODULES];
static PTABLE_ENTRY ImportTables = (PTABLE_ENTRY)GenericTable;

KERNEL_IMPORT LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);


typedef void* PEXCEPTION_RECORD;

ULONG KeNumberProcessors();

//define JITL Section data
#define CURRENT_JITLS   1

//Jitl list
//extern SECTIONED_CODE(".JitlDirectory") JITL_DIRECTORY AhciJitlDirectory;

static PJITL_DIRECTORY SystemSections[CURRENT_JITLS];

LOUDDK_API_ENTRY char* Winstrcpy(char* dest, const char* src);
LOUDDK_API_ENTRY char* Winstrcat(char* dest, const char* src);

LOUDDK_API_ENTRY
DRIVER_MODULE_ENTRY LouKeGetJitlManagedFunction(string SectionName, string FunctionName){
    for(uint8_t i = 0; i < CURRENT_JITLS; i++){
        if(strcmp(SectionName, SystemSections[i]->SectionName) == 0){
            if(SystemSections[i]->Detached){
                return 0x00;
            }
            for(uint8_t j = 0 ; SystemSections[i]->JitlEntries->Name != 0; j++){
                if(strcmp(FunctionName, SystemSections[i]->JitlEntries->Name) == 0){
                    return (DRIVER_MODULE_ENTRY)SystemSections[i]->JitlEntries->Location;
                }
            }
        }

    }
    return 0x00;
};

LOUDDK_API_ENTRY
void* LouKeGetJitlManagedDataLocation(string SectionName, string FunctionName){
    for(uint8_t i = 0; i < CURRENT_JITLS; i++){
        if(strcmp(SectionName, SystemSections[i]->SectionName) == 0){
            if(SystemSections[i]->Detached){
                return 0x00;
            }
            for(uint8_t j = 0 ; SystemSections[i]->JitlEntries->Name != 0; j++){
                if(strcmp(FunctionName, SystemSections[i]->JitlEntries->Name) == 0){
                    SystemSections[i]->BeingUsed = true;
                    return (void*)SystemSections[i]->JitlEntries->Location;
                }
            }
        }

    }
    return 0x00;
};

VOID
RtlUnwind(
     PVOID TargetFrame,
     PVOID TargetIp,
     PEXCEPTION_RECORD ExceptionRecord,
     PVOID ReturnValue
);

LOUDDK_API_ENTRY
ULONG
vDbgPrintEx(
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
);

LOUDDK_API_ENTRY
ULONG
vDbgPrintExWithPrefix (
    PCCH Prefix,
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
);


LOUDDK_API_ENTRY
NTSTATUS
NtAddAtom(
    PWSTR       AtomName,
    ULONG       Length,
    PRTL_ATOM   Atom
);

LOUDDK_API_ENTRY
NTSTATUS
NtAddAtomEx(
    PWSTR AtomName,
    ULONG Length,
    PRTL_ATOM Atom,
    ULONG Flags
);

NTSTATUS NtAdjustPrivilegesToken(
    HANDLE TokenHandle,
    bool DisableAllPrivaledges,
    PTOKEN_PRIVALEDGES NewState,
    ULONG BufferLength,
    PTOKEN_PRIVALEDGES PreviousState,
    PULONG ReturnLength
);

LOUDDK_API_ENTRY
NTSTATUS
NtAllocateLocallyUniqueId(
    PLUID Luid
);

LOUDDK_API_ENTRY
NTSTATUS
NtAllocateUuids(
    PULARGE_INTEGER Time,
    PULONG Range,
    PULONG Sequnce,
    PCHAR Seed
);

LOUDDK_API_ENTRY
int toupper(int c);

LOUDDK_API_ENTRY
void LouKeInitializeLibraryLookup(
    string    ModuleName,
    uint32_t  NumberOfFunctions,
    string*   FunctionNames,
    uint64_t* FunctionAddresses,
    bool IsNativeLongmode
){
    uint16_t i;
    PTableTracks Tmp = (PTableTracks)&DynamicLoadedLibraries;
    for(i = 0; i < DynamicLoadedLibrarieCount; i++){
        if(!Tmp->Neighbors.NextHeader){
            Tmp->Neighbors.NextHeader = (ListHeader*)LouKeMallocType(TableTracks, KERNEL_GENERIC_MEMORY);
        }
        Tmp = (PTableTracks)Tmp->Neighbors.NextHeader;
    }

    Tmp->LongModeEntry = IsNativeLongmode;
    Tmp->Table.ModuleName = ModuleName;
    size_t koo = strlen(ModuleName);
    for(size_t foo = 0 ; foo < koo; foo++){
        ModuleName[foo] = toupper(ModuleName[foo]);
    }
    Tmp->Table.NumberOfFunctions = NumberOfFunctions;
    Tmp->Table.FunctionName = FunctionNames;
    Tmp->Table.VirtualAddress = FunctionAddresses;

    DynamicLoadedLibrarieCount++;
}

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

KERNEL_IMPORT void* LouKePciGetIoRegion(
    P_PCI_DEVICE_OBJECT PDEV, 
    uint8_t BarNumber,
    size_t BarOffset
);


static inline 
void InitializeLousineKernelTables(){
    ImportTables[4].ModuleName = "LOUOSKRNL.EXE";
    ImportTables[4].NumberOfFunctions = PRE_LOADED_LOUOSKRNL_FUNCTIONS;

    ImportTables[4].FunctionName = LouOsKrnlFunctionNames;   
    
    ImportTables[4].FunctionName[0] = "LouPrint";
    ImportTables[4].FunctionName[1] = "RegisterInterruptHandler";
    ImportTables[4].FunctionName[2] = "memcpy";
    ImportTables[4].FunctionName[3] = "strncmp";
    ImportTables[4].FunctionName[4] = "strcmp";
    ImportTables[4].FunctionName[5] = "memcmp";
    ImportTables[4].FunctionName[6] = "strncpy";
    ImportTables[4].FunctionName[7] = "insw";
    ImportTables[4].FunctionName[8] = "LouKeFreeFromPool";
    ImportTables[4].FunctionName[9] = "LouKeMallocFromPool";
    ImportTables[4].FunctionName[10] = "LouKeFreePool";
    ImportTables[4].FunctionName[11] = "LouKeMapPool";
    ImportTables[4].FunctionName[12] = "RequestPhysicalAddress";
    ImportTables[4].FunctionName[13] = "LouKeVMemmoryGetSize";
    ImportTables[4].FunctionName[14] = "LouKeMapContinuousMemoryBlock";
    ImportTables[4].FunctionName[15] = "LouVMalloc";
    ImportTables[4].FunctionName[16] = "LouVMallocEx";
    ImportTables[4].FunctionName[17] = "LouKeAllocateUncachedVMemoryEx";
    ImportTables[4].FunctionName[18] = "LouKeAllocateUncachedVMemory";
    ImportTables[4].FunctionName[19] = "SearchForMappedAddressSize";
    ImportTables[4].FunctionName[20] = "LouKeVMemmorySearchVirtualSpace";
    ImportTables[4].FunctionName[21] = "LouKeVMemmorySearchPhysicalSpace";
    ImportTables[4].FunctionName[22] = "LouKeMallocVMmIO";
    ImportTables[4].FunctionName[23] = "LouFree";
    ImportTables[4].FunctionName[24] = "LouKeTestAndResetBit8";
    ImportTables[4].FunctionName[25] = "LouKeTestBitAndUnSet8";
    ImportTables[4].FunctionName[26] = "LouKeTestBitAndSet8";
    ImportTables[4].FunctionName[27] = "LouKeTestBit8";
    ImportTables[4].FunctionName[28] = "LouKeUnSetBit8";
    ImportTables[4].FunctionName[29] = "LouKeSetBit8";
    ImportTables[4].FunctionName[30] = "LouKeTestAndResetBitU8";
    ImportTables[4].FunctionName[31] = "LouKeTestBitAndUnSetU8";
    ImportTables[4].FunctionName[32] = "LouKeTestBitAndSetU8";
    ImportTables[4].FunctionName[33] = "LouKeTestBitU8";
    ImportTables[4].FunctionName[34] = "LouKeUnSetBitU8";
    ImportTables[4].FunctionName[35] = "LouKeSetBitU8";
    ImportTables[4].FunctionName[36] = "LouKeTestAndResetBit16";
    ImportTables[4].FunctionName[37] = "LouKeTestBitAndUnSet16";
    ImportTables[4].FunctionName[38] = "LouKeTestBitAndSet16";
    ImportTables[4].FunctionName[39] = "LouKeTestBit16";
    ImportTables[4].FunctionName[40] = "LouKeUnSetBit16";
    ImportTables[4].FunctionName[41] = "LouKeSetBit16";
    ImportTables[4].FunctionName[42] = "LouKeTestAndResetBitU16";
    ImportTables[4].FunctionName[43] = "LouKeTestBitAndUnSetU16";
    ImportTables[4].FunctionName[44] = "LouKeTestBitAndSetU16";
    ImportTables[4].FunctionName[45] = "LouKeTestBitU16";
    ImportTables[4].FunctionName[46] = "LouKeUnSetBitU16";
    ImportTables[4].FunctionName[47] = "LouKeSetBitU16";
    ImportTables[4].FunctionName[48] = "LouKeTestAndResetBit32";
    ImportTables[4].FunctionName[49] = "LouKeTestBitAndUnSet32";
    ImportTables[4].FunctionName[50] = "LouKeTestBitAndSet32";
    ImportTables[4].FunctionName[51] = "LouKeTestBit32";
    ImportTables[4].FunctionName[52] = "LouKeUnSetBit32";
    ImportTables[4].FunctionName[53] = "LouKeSetBit32";
    ImportTables[4].FunctionName[54] = "LouKeTestAndResetBitU32";
    ImportTables[4].FunctionName[55] = "LouKeTestBitAndUnSetU32";
    ImportTables[4].FunctionName[56] = "LouKeTestBitAndSetU32";
    ImportTables[4].FunctionName[57] = "LouKeTestBitU32";
    ImportTables[4].FunctionName[58] = "LouKeUnSetBitU32";
    ImportTables[4].FunctionName[59] = "LouKeSetBitU32";
    ImportTables[4].FunctionName[60] = "LouKeTestAndResetBit64";
    ImportTables[4].FunctionName[61] = "LouKeTestBitAndUnSet64";
    ImportTables[4].FunctionName[62] = "LouKeTestBit64";
    ImportTables[4].FunctionName[63] = "LouKeUnSetBit64";
    ImportTables[4].FunctionName[64] = "LouKeSetBit64";
    ImportTables[4].FunctionName[65] = "LouKeTestAndResetBitU64";
    ImportTables[4].FunctionName[66] = "LouKeTestBitAndUnSetU64";
    ImportTables[4].FunctionName[67] = "LouKeTestBitAndSetU64";
    ImportTables[4].FunctionName[68] = "LouKeTDrsdInternalAtomicCheckestBitU64";
    ImportTables[4].FunctionName[69] = "LouKeUnSetBitU64";
    ImportTables[4].FunctionName[70] = "LouKeSetBitU64";
    ImportTables[4].FunctionName[71] = "LouKeCreateThread";
    ImportTables[4].FunctionName[72] = "LouKeAcquireSpinLock";
    ImportTables[4].FunctionName[73] = "LouKeReleaseSpinLock";
    ImportTables[4].FunctionName[74] = "LouMalloc";
    ImportTables[4].FunctionName[75] = "GetPciConfiguration";
    ImportTables[4].FunctionName[76] = "LouKeHalLinuxPciCheckForCompatibleConfiguration";
    ImportTables[4].FunctionName[77] = "pci_read";
    ImportTables[4].FunctionName[78] = "write_pci";
    ImportTables[4].FunctionName[79] = "LouKeReadPciUint8";
    ImportTables[4].FunctionName[80] = "LouKeReadPciUint16";
    ImportTables[4].FunctionName[81] = "LouKeReadPciUint32";
    ImportTables[4].FunctionName[82] = "LouKeWritePciUint8";
    ImportTables[4].FunctionName[83] = "LouKeWritePciUint16";
    ImportTables[4].FunctionName[84] = "LouKeWritePciUint32";
    ImportTables[4].FunctionName[85] = "LouKeHalEnablePciDevice";
    ImportTables[4].FunctionName[86] = "LouKePciGetIoRegion";
    ImportTables[4].FunctionName[87] = "LouKeHalPciSaveContext";
    ImportTables[4].FunctionName[88] = "LouKeHalPciRestoreContext";
    ImportTables[4].FunctionName[89] = "LouKeHalPciClearMaster";
    ImportTables[4].FunctionName[90] = "READ_REGISTER_ULONG";
    ImportTables[4].FunctionName[91] = "LouMallocAtaHost";
    ImportTables[4].FunctionName[92] = "LouKeHalMallocPciIrqVectors";
    ImportTables[4].FunctionName[93] = "WRITE_PORT_ULONG";
    ImportTables[4].FunctionName[94] = "WRITE_REGISTER_ULONG";
    ImportTables[4].FunctionName[95] = "sleep";
    ImportTables[4].FunctionName[96] = "LouKeHalPciSetMaster";
    ImportTables[4].FunctionName[97] = "LouKeRegisterDevice";
    ImportTables[4].FunctionName[98] = "AtaStdQcDefer";
    ImportTables[4].FunctionName[99] = "LouMallocEx";
    ImportTables[4].FunctionName[100] = "memset";
    ImportTables[4].FunctionName[101] = "LouKeWaitForMmioState";
    ImportTables[4].FunctionName[102] = "LouKeCreateFixedPool";
    ImportTables[4].FunctionName[103] = "outw";
    ImportTables[4].FunctionName[104] = "LouKeMallocEx";
    ImportTables[4].FunctionName[105] = "LouKeMalloc";
    ImportTables[4].FunctionName[106] = "inw";
    ImportTables[4].FunctionName[107] = "outw";
    ImportTables[4].FunctionName[108] = "LouKeLinkerGetAddress";
    ImportTables[4].FunctionName[109] = "LoukeRegisterNetFrameHardwareDriver";
    ImportTables[4].FunctionName[110] = "LouKePciGetInterruptLine";
    ImportTables[4].FunctionName[111] = "inl";
    ImportTables[4].FunctionName[112] = "LouKeMapDynamicPool";
    ImportTables[4].FunctionName[113] = "LouKeMallocFromDynamicPool";
    ImportTables[4].FunctionName[114] = "LouKeMallocFromDynamicPoolEx";
    ImportTables[4].FunctionName[115] = "outl";
    ImportTables[4].FunctionName[116] = "LouKeFreeFromDynamicPool";
    ImportTables[4].FunctionName[117] = "LouKeHalGetPciBaseAddressSize";
    ImportTables[4].FunctionName[118] = "LouKeCreateGenericPool";
    ImportTables[4].FunctionName[119] = "LouKeGenricAllocateDmaPool";
    ImportTables[4].FunctionName[120] = "LouKeGenericPoolGetPhyAddress";
    ImportTables[4].FunctionName[121] = "LouKePassVramToDrsdMemoryManager";
    ImportTables[4].FunctionName[122] = "DrsdGxeCreateAsyncFramebuffer";
    ImportTables[4].FunctionName[123] = "DrsdGxeVramInternalModeValid";
    ImportTables[4].FunctionName[124] = "DrsdInternalAtomicCheck";
    ImportTables[4].FunctionName[125] = "DrsdInternalAtomicUpdate";
    ImportTables[4].FunctionName[126] = "DrsdInternalResetPlane";
    ImportTables[4].FunctionName[127] = "DrsdInternalDestroyPlane";
    ImportTables[4].FunctionName[128] = "DrsdInternalPlaneDisableAtomic";
    ImportTables[4].FunctionName[129] = "DrsdInternalPlaneUpdateAtomic";
    ImportTables[4].FunctionName[130] = "DrsdInternalDestroyPlaneAtomic";
    ImportTables[4].FunctionName[131] = "DrsdInternalDuplicateAtomicState";
    ImportTables[4].FunctionName[132] = "DrsdGxeInternalPrepareFrameBuffer";
    ImportTables[4].FunctionName[133] = "DrsdGxeInternalCleanupFrameBuffer";
    ImportTables[4].FunctionName[134] = "DrsdGxeInternalStartFrameBufferProcessing";
    ImportTables[4].FunctionName[135] = "DrsdGxeInternalStopFrameBufferProcessing";
    ImportTables[4].FunctionName[136] = "DrsdGxeDestroyShadowPlane";
    ImportTables[4].FunctionName[137] = "DrsdGxeDuplicateShadowPlaneState";
    ImportTables[4].FunctionName[138] = "DrsdGxeResetShadowPlane";
    ImportTables[4].FunctionName[139] = "DrsdInitializeGenericPlane";
    ImportTables[4].FunctionName[140] = "DrsdInitializeCrtcWithPlanes";
    ImportTables[4].FunctionName[141] = "DrsdInitializeCrtcGammaSize";
    ImportTables[4].FunctionName[142] = "DrsdInternalCrtcSetConfigurationAtomic";
    ImportTables[4].FunctionName[143] = "DrsdInternalCrtcPageFlipAtomic";
    ImportTables[4].FunctionName[144] = "DrsdInternalCrtcResetAtomic";
    ImportTables[4].FunctionName[145] = "DrsdInternalCrtcDuplicateStateAtomic";
    ImportTables[4].FunctionName[146] = "DrsdInternalCrtcDestroyStateAtomic";
    ImportTables[4].FunctionName[147] = "DrsdInitializeEncoder";
    ImportTables[4].FunctionName[148] = "DrsdInternalAtomicConnectorDestroyState";
    ImportTables[4].FunctionName[149] = "DrsdInternalAtomicConnectorDuplicateState";
    ImportTables[4].FunctionName[150] = "DrsdInternalResetConnector";
    ImportTables[4].FunctionName[151] = "DrsdConnectorInitialize";
    ImportTables[4].FunctionName[152] = "DrsdModeConfigurationReset";
    ImportTables[4].FunctionName[153] = "DrsdInternalProbeSingleConnectorModes";
    ImportTables[4].FunctionName[154] = "LouKeGetThreadIdentification";
    ImportTables[4].FunctionName[155] = "LouKeHalGetPciConfiguration";
    ImportTables[4].FunctionName[156] = "LouKeFree";
    ImportTables[4].FunctionName[157] = "LouKeMallocAtaDevice";
    ImportTables[4].FunctionName[158] = "LouKeMallocAtaPrivateData";
    ImportTables[4].FunctionName[159] = "LouKeForkAtaHostPrivateDataToPorts";
    ImportTables[4].FunctionName[160] = "DrsdAddModesNoEDID";
    ImportTables[4].FunctionName[161] = "DrsdModeVfresh";
    ImportTables[4].FunctionName[162] = "DrsdCvtMode";
    ImportTables[4].FunctionName[163] = "DrsdAddProbedDisplayModeToConnector";
    ImportTables[4].FunctionName[164] = "DrsdUpdateEdidConnectorProperties";
    ImportTables[4].FunctionName[165] = "DrsdGetNewPlaneState";
    ImportTables[4].FunctionName[166] = "LouKeDrsdHandleConflictingDevices";
    ImportTables[4].FunctionName[167] = "inb";
    ImportTables[4].FunctionName[168] = "outb";
    ImportTables[4].FunctionName[169] = "LouKeCreateBusClass";
    ImportTables[4].FunctionName[170] = "LouKeLoadSubsystem";
    ImportTables[4].FunctionName[171] = "LouKeLoadDriver";


    ImportTables[4].VirtualAddress = LouOsKrnlFunctionAddresses;

    ImportTables[4].VirtualAddress[0] = (uint64_t)LouPrint;
    ImportTables[4].VirtualAddress[1] = (uint64_t)RegisterInterruptHandler;
    ImportTables[4].VirtualAddress[2] = (uint64_t)memcpy;
    ImportTables[4].VirtualAddress[3] = (uint64_t)strncmp;
    ImportTables[4].VirtualAddress[4] = (uint64_t)strcmp;
    ImportTables[4].VirtualAddress[5] = (uint64_t)memcmp;
    ImportTables[4].VirtualAddress[6] = (uint64_t)strncpy;
    ImportTables[4].VirtualAddress[7] = (uint64_t)insw;
    ImportTables[4].VirtualAddress[8] = (uint64_t)outsw;
    ImportTables[4].VirtualAddress[9] = (uint64_t)LouKeFreeFromPool;
    ImportTables[4].VirtualAddress[10] = (uint64_t)LouKeMallocFromPool;
    ImportTables[4].VirtualAddress[11] = (uint64_t)LouKeMapPool;
    ImportTables[4].VirtualAddress[12] = (uint64_t)RequestPhysicalAddress;
    ImportTables[4].VirtualAddress[13] = (uint64_t)LouKeVMemmoryGetSize;
    ImportTables[4].VirtualAddress[14] = (uint64_t)LouKeMapContinuousMemoryBlock;
    ImportTables[4].VirtualAddress[15] = (uint64_t)LouVMalloc;
    ImportTables[4].VirtualAddress[16] = (uint64_t)LouVMallocEx;
    ImportTables[4].VirtualAddress[17] = (uint64_t)LouKeAllocateUncachedVMemoryEx;
    ImportTables[4].VirtualAddress[18] = (uint64_t)LouKeAllocateUncachedVMemory;
    ImportTables[4].VirtualAddress[19] = (uint64_t)SearchForMappedAddressSize;
    ImportTables[4].VirtualAddress[20] = (uint64_t)LouKeVMemmorySearchVirtualSpace;
    ImportTables[4].VirtualAddress[21] = (uint64_t)LouKeVMemmorySearchPhysicalSpace;
    ImportTables[4].VirtualAddress[22] = (uint64_t)LouKeMallocVMmIO;
    ImportTables[4].VirtualAddress[23] = (uint64_t)LouFree;
    ImportTables[4].VirtualAddress[24] = (uint64_t)LouKeTestAndResetBit8;
    ImportTables[4].VirtualAddress[25] = (uint64_t)LouKeTestBitAndUnSet8;
    ImportTables[4].VirtualAddress[26] = (uint64_t)LouKeTestBitAndSet8;
    ImportTables[4].VirtualAddress[27] = (uint64_t)LouKeTestBit8;
    ImportTables[4].VirtualAddress[28] = (uint64_t)LouKeUnSetBit8;
    ImportTables[4].VirtualAddress[29] = (uint64_t)LouKeSetBit8;
    ImportTables[4].VirtualAddress[30] = (uint64_t)LouKeTestAndResetBitU8;
    ImportTables[4].VirtualAddress[31] = (uint64_t)LouKeTestBitAndUnSetU8;
    ImportTables[4].VirtualAddress[32] = (uint64_t)LouKeTestBitAndSetU8;
    ImportTables[4].VirtualAddress[33] = (uint64_t)LouKeTestBitU8;
    ImportTables[4].VirtualAddress[34] = (uint64_t)LouKeUnSetBitU8;
    ImportTables[4].VirtualAddress[35] = (uint64_t)LouKeSetBitU8;
    ImportTables[4].VirtualAddress[36] = (uint64_t)LouKeTestAndResetBit16;
    ImportTables[4].VirtualAddress[37] = (uint64_t)LouKeTestBitAndUnSet16;
    ImportTables[4].VirtualAddress[38] = (uint64_t)LouKeTestBitAndSet16;
    ImportTables[4].VirtualAddress[39] = (uint64_t)LouKeTestBit16;
    ImportTables[4].VirtualAddress[40] = (uint64_t)LouKeUnSetBit16;
    ImportTables[4].VirtualAddress[41] = (uint64_t)LouKeSetBit16;
    ImportTables[4].VirtualAddress[42] = (uint64_t)LouKeTestAndResetBitU16;
    ImportTables[4].VirtualAddress[43] = (uint64_t)LouKeTestBitAndUnSetU16;
    ImportTables[4].VirtualAddress[44] = (uint64_t)LouKeTestBitAndSetU16;
    ImportTables[4].VirtualAddress[45] = (uint64_t)LouKeTestBitU16;
    ImportTables[4].VirtualAddress[46] = (uint64_t)LouKeUnSetBitU16;
    ImportTables[4].VirtualAddress[47] = (uint64_t)LouKeSetBitU16;
    ImportTables[4].VirtualAddress[48] = (uint64_t)LouKeTestAndResetBit32;
    ImportTables[4].VirtualAddress[49] = (uint64_t)LouKeTestBitAndUnSet32;
    ImportTables[4].VirtualAddress[50] = (uint64_t)LouKeTestBitAndSet32;
    ImportTables[4].VirtualAddress[51] = (uint64_t)LouKeTestBit32;
    ImportTables[4].VirtualAddress[52] = (uint64_t)LouKeUnSetBit32;
    ImportTables[4].VirtualAddress[53] = (uint64_t)LouKeSetBit32;
    ImportTables[4].VirtualAddress[54] = (uint64_t)LouKeTestAndResetBitU32;
    ImportTables[4].VirtualAddress[55] = (uint64_t)LouKeTestBitAndUnSetU32;
    ImportTables[4].VirtualAddress[56] = (uint64_t)LouKeTestBitU32;
    ImportTables[4].VirtualAddress[57] = (uint64_t)LouKeUnSetBitU32;
    ImportTables[4].VirtualAddress[58] = (uint64_t)LouKeSetBitU32;
    ImportTables[4].VirtualAddress[59] = (uint64_t)LouKeTestAndResetBit64;
    ImportTables[4].VirtualAddress[60] = (uint64_t)LouKeTestBitAndUnSet64;
    ImportTables[4].VirtualAddress[61] = (uint64_t)LouKeTestBitAndSet64;
    ImportTables[4].VirtualAddress[62] = (uint64_t)LouKeTestBit64;
    ImportTables[4].VirtualAddress[63] = (uint64_t)LouKeUnSetBit64;
    ImportTables[4].VirtualAddress[64] = (uint64_t)LouKeSetBit64;
    ImportTables[4].VirtualAddress[65] = (uint64_t)LouKeTestAndResetBitU64;
    ImportTables[4].VirtualAddress[66] = (uint64_t)LouKeTestBitAndUnSetU64;
    ImportTables[4].VirtualAddress[67] = (uint64_t)LouKeTestBitAndSetU64;
    ImportTables[4].VirtualAddress[68] = (uint64_t)LouKeTestBitU64;
    ImportTables[4].VirtualAddress[69] = (uint64_t)LouKeUnSetBitU64;
    ImportTables[4].VirtualAddress[70] = (uint64_t)LouKeSetBitU64;
    ImportTables[4].VirtualAddress[71] = (uint64_t)LouKeCreateThread;
    ImportTables[4].VirtualAddress[72] = (uint64_t)LouKeAcquireSpinLock;
    ImportTables[4].VirtualAddress[73] = (uint64_t)LouKeReleaseSpinLock;
    ImportTables[4].VirtualAddress[74] = (uint64_t)LouMalloc;
    ImportTables[4].VirtualAddress[75] = (uint64_t)GetPciConfiguration;
    ImportTables[4].VirtualAddress[76] = (uint64_t)LouKeHalLinuxPciCheckForCompatibleConfiguration;
    ImportTables[4].VirtualAddress[77] = (uint64_t)pci_read;
    ImportTables[4].VirtualAddress[78] = (uint64_t)write_pci;
    ImportTables[4].VirtualAddress[79] = (uint64_t)LouKeReadPciUint8;
    ImportTables[4].VirtualAddress[80] = (uint64_t)LouKeReadPciUint16;
    ImportTables[4].VirtualAddress[81] = (uint64_t)LouKeReadPciUint32;
    ImportTables[4].VirtualAddress[82] = (uint64_t)LouKeWritePciUint8;
    ImportTables[4].VirtualAddress[83] = (uint64_t)LouKeWritePciUint16;
    ImportTables[4].VirtualAddress[84] = (uint64_t)LouKeWritePciUint32;
    ImportTables[4].VirtualAddress[85] = (uint64_t)LouKeHalEnablePciDevice;
    ImportTables[4].VirtualAddress[86] = (uint64_t)LouKePciGetIoRegion;
    ImportTables[4].VirtualAddress[87] = (uint64_t)LouKeHalPciSaveContext;
    ImportTables[4].VirtualAddress[88] = (uint64_t)LouKeHalPciRestoreContext;
    ImportTables[4].VirtualAddress[89] = (uint64_t)LouKeHalPciClearMaster;
    ImportTables[4].VirtualAddress[90] = (uint64_t)READ_REGISTER_ULONG;
    ImportTables[4].VirtualAddress[92] = (uint64_t)LouKeHalMallocPciIrqVectors;
    ImportTables[4].VirtualAddress[93] = (uint64_t)WRITE_PORT_ULONG;
    ImportTables[4].VirtualAddress[94] = (uint64_t)WRITE_REGISTER_ULONG;
    ImportTables[4].VirtualAddress[95] = (uint64_t)sleep;
    ImportTables[4].VirtualAddress[96] = (uint64_t)LouKeHalPciSetMaster;
    ImportTables[4].VirtualAddress[97] = (uint64_t)LouKeRegisterDevice;
    ImportTables[4].VirtualAddress[99] = (uint64_t)LouMallocEx;
    ImportTables[4].VirtualAddress[100] = (uint64_t)memset;
    ImportTables[4].VirtualAddress[101] = (uint64_t)LouKeWaitForMmioState;
    ImportTables[4].VirtualAddress[102] = (uint64_t)LouKeCreateFixedPool;
    ImportTables[4].VirtualAddress[103] = (uint64_t)outw; 
    ImportTables[4].VirtualAddress[104] = (uint64_t)LouKeMallocEx;
    ImportTables[4].VirtualAddress[105] = (uint64_t)LouKeMalloc;
    ImportTables[4].VirtualAddress[106] = (uint64_t)inw;
    ImportTables[4].VirtualAddress[107] = (uint64_t)outw;
    ImportTables[4].VirtualAddress[108] = (uint64_t)LouKeLinkerGetAddress;
    ImportTables[4].VirtualAddress[109] = (uint64_t)LoukeRegisterNetFrameHardwareDriver;
    ImportTables[4].VirtualAddress[110] = (uint64_t)LouKePciGetInterruptLine;
    ImportTables[4].VirtualAddress[111] = (uint64_t)inl;
    ImportTables[4].VirtualAddress[112] = (uint64_t)LouKeMapDynamicPool;
    ImportTables[4].VirtualAddress[113] = (uint64_t)LouKeMallocFromDynamicPool;
    ImportTables[4].VirtualAddress[114] = (uint64_t)LouKeMallocFromDynamicPoolEx;
    ImportTables[4].VirtualAddress[115] = (uint64_t)outl;
    ImportTables[4].VirtualAddress[116] = (uint64_t)LouKeFreeFromDynamicPool;
    ImportTables[4].VirtualAddress[117] = (uint64_t)LouKeHalGetPciBaseAddressSize;
    ImportTables[4].VirtualAddress[118] = (uint64_t)LouKeCreateGenericPool;
    ImportTables[4].VirtualAddress[119] = (uint64_t)LouKeGenricAllocateDmaPool;
    ImportTables[4].VirtualAddress[120] = (uint64_t)LouKeGenericPoolGetPhyAddress;
    ImportTables[4].VirtualAddress[121] = (uint64_t)LouKePassVramToDrsdMemoryManager;
    ImportTables[4].VirtualAddress[122] = (uint64_t)DrsdGxeCreateAsyncFramebuffer;
    ImportTables[4].VirtualAddress[123] = (uint64_t)DrsdGxeVramInternalModeValid;
    ImportTables[4].VirtualAddress[124] = (uint64_t)DrsdInternalAtomicCheck;
    ImportTables[4].VirtualAddress[125] = (uint64_t)DrsdInternalAtomicUpdate;
    ImportTables[4].VirtualAddress[126] = (uint64_t)DrsdInternalResetPlane;
    ImportTables[4].VirtualAddress[127] = (uint64_t)DrsdInternalDestroyPlane;
    ImportTables[4].VirtualAddress[128] = (uint64_t)DrsdInternalPlaneDisableAtomic;
    ImportTables[4].VirtualAddress[129] = (uint64_t)DrsdInternalPlaneUpdateAtomic;
    ImportTables[4].VirtualAddress[130] = (uint64_t)DrsdInternalDestroyPlaneAtomic;
    ImportTables[4].VirtualAddress[131] = (uint64_t)DrsdInternalDuplicateAtomicState;
    ImportTables[4].VirtualAddress[132] = (uint64_t)DrsdGxeInternalPrepareFrameBuffer;
    ImportTables[4].VirtualAddress[133] = (uint64_t)DrsdGxeInternalCleanupFrameBuffer;
    ImportTables[4].VirtualAddress[134] = (uint64_t)DrsdGxeInternalStartFrameBufferProcessing;
    ImportTables[4].VirtualAddress[135] = (uint64_t)DrsdGxeInternalStopFrameBufferProcessing;
    ImportTables[4].VirtualAddress[136] = (uint64_t)DrsdGxeDestroyShadowPlane;
    ImportTables[4].VirtualAddress[137] = (uint64_t)DrsdGxeDuplicateShadowPlaneState;
    ImportTables[4].VirtualAddress[138] = (uint64_t)DrsdGxeResetShadowPlane;
    ImportTables[4].VirtualAddress[139] = (uint64_t)DrsdInitializeGenericPlane;
    ImportTables[4].VirtualAddress[140] = (uint64_t)DrsdInitializeCrtcWithPlanes;
    ImportTables[4].VirtualAddress[141] = (uint64_t)DrsdInitializeCrtcGammaSize;
    ImportTables[4].VirtualAddress[142] = (uint64_t)DrsdInternalCrtcSetConfigurationAtomic;
    ImportTables[4].VirtualAddress[143] = (uint64_t)DrsdInternalCrtcPageFlipAtomic;
    ImportTables[4].VirtualAddress[144] = (uint64_t)DrsdInternalCrtcResetAtomic;
    ImportTables[4].VirtualAddress[145] = (uint64_t)DrsdInternalCrtcDuplicateStateAtomic;
    ImportTables[4].VirtualAddress[146] = (uint64_t)DrsdInternalCrtcDestroyStateAtomic;
    ImportTables[4].VirtualAddress[147] = (uint64_t)DrsdInitializeEncoder;
    ImportTables[4].VirtualAddress[148] = (uint64_t)DrsdInternalAtomicConnectorDestroyState;
    ImportTables[4].VirtualAddress[149] = (uint64_t)DrsdInternalAtomicConnectorDuplicateState;
    ImportTables[4].VirtualAddress[150] = (uint64_t)DrsdInternalResetConnector;
    ImportTables[4].VirtualAddress[151] = (uint64_t)DrsdConnectorInitialize;
    ImportTables[4].VirtualAddress[152] = (uint64_t)DrsdModeConfigurationReset;
    ImportTables[4].VirtualAddress[153] = (uint64_t)DrsdInternalProbeSingleConnectorModes;
    ImportTables[4].VirtualAddress[154] = (uint64_t)LouKeGetThreadIdentification;
    ImportTables[4].VirtualAddress[155] = (uint64_t)LouKeHalGetPciConfiguration;
    ImportTables[4].VirtualAddress[156] = (uint64_t)LouKeFree;
    ImportTables[4].VirtualAddress[157] = (uint64_t)LouKeMallocAtaDevice;
    ImportTables[4].VirtualAddress[158] = (uint64_t)LouKeMallocAtaPrivateData;
    ImportTables[4].VirtualAddress[159] = (uint64_t)LouKeForkAtaHostPrivateDataToPorts;
    ImportTables[4].VirtualAddress[160] = (uint64_t)DrsdAddModesNoEDID;
    ImportTables[4].VirtualAddress[161] = (uint64_t)DrsdModeVfresh;
    ImportTables[4].VirtualAddress[162] = (uint64_t)DrsdCvtMode;
    ImportTables[4].VirtualAddress[163] = (uint64_t)DrsdAddProbedDisplayModeToConnector;
    ImportTables[4].VirtualAddress[164] = (uint64_t)DrsdUpdateEdidConnectorProperties;
    ImportTables[4].VirtualAddress[165] = (uint64_t)DrsdGetNewPlaneState;
    ImportTables[4].VirtualAddress[166] = (uint64_t)LouKeDrsdHandleConflictingDevices;
    ImportTables[4].VirtualAddress[167] = (uint64_t)inb;
    ImportTables[4].VirtualAddress[168] = (uint64_t)outb;
    ImportTables[4].VirtualAddress[169] = (uint64_t)LouKeCreateBusClass;
    ImportTables[4].VirtualAddress[170] = (uint64_t)LouKeLoadSubsystem;
    ImportTables[4].VirtualAddress[171] = (uint64_t)LouKeLoadDriver;

}

LOUDDK_API_ENTRY
int vswprintf_s(
    wchar_t* Buffer,
    size_t BufferCount,
    wchar_t* Format,
    va_list Args
);

LOUDDK_API_ENTRY
int vsprintf_s(
    string Buffer,
    size_t BufferCount,
    string Format,
    va_list Args
);

LOUDDK_API_ENTRY
wchar_t towupper(wchar_t wc);

LOUDDK_API_ENTRY
wchar_t towlower(wchar_t wc);

LOUDDK_API_ENTRY
int tolower(int c);



static inline
void InitializeNtKernelTable(){
    ImportTables[0].ModuleName = "NTOSKRNL.EXE";
    ImportTables[0].NumberOfFunctions = PRE_LOADED_NTOSKRNL_FUNCTIONS;
    
    ImportTables[0].FunctionName = NTFunctionNames;

    ImportTables[0].FunctionName[0] = "RtlCopyUnicodeString";
    ImportTables[0].FunctionName[1] = "DbgPrint";
    ImportTables[0].FunctionName[2] = "DbgPrintEx";
    //ioaccess
    ImportTables[0].FunctionName[3] = "READ_REGISTER_UCHAR";
    ImportTables[0].FunctionName[4] = "WRITE_REGISTER_UCHAR";
    ImportTables[0].FunctionName[5] = "READ_REGISTER_USHORT";
    ImportTables[0].FunctionName[6] = "WRITE_REGISTER_USHORT";
    ImportTables[0].FunctionName[7] = "READ_REGISTER_ULONG";
    ImportTables[0].FunctionName[8] = "WRITE_REGISTER_ULONG";
 
    ImportTables[0].FunctionName[9] =  "wcslen";
    ImportTables[0].FunctionName[10] = "wcscmp";
    ImportTables[0].FunctionName[11] = "wcstoul";
    ImportTables[0].FunctionName[12] = "wcstombs";
    ImportTables[0].FunctionName[13] = "wcsstr";
    ImportTables[0].FunctionName[14] = "wcsspn";
    ImportTables[0].FunctionName[15] = "wcsrchr";
    ImportTables[0].FunctionName[16] = "vDbgPrintEx";
    ImportTables[0].FunctionName[17] = "vDbgPrintExWithPrefix";
    ImportTables[0].FunctionName[18] = "vswprintf_s";
    ImportTables[0].FunctionName[19] = "vsprintf_s";
    ImportTables[0].FunctionName[20] = "towupper";
    ImportTables[0].FunctionName[21] = "towlower";
    ImportTables[0].FunctionName[22] = "tolower";
    ImportTables[0].FunctionName[23] = "toupper";
    ImportTables[0].FunctionName[24] = "sscanf_s";
    ImportTables[0].FunctionName[25] = "_sscanf_s_l";
    ImportTables[0].FunctionName[26] = "swscanf_s";
    ImportTables[0].FunctionName[27] = "_swscanf_s_l";
    ImportTables[0].FunctionName[28] = "swprintf_s";
    ImportTables[0].FunctionName[29] = "swprintf";
    ImportTables[0].FunctionName[30] = "strtok_s";
    ImportTables[0].FunctionName[31] = "strstr";
    ImportTables[0].FunctionName[32] = "strspn";
    ImportTables[0].FunctionName[33] = "strrchr";
    ImportTables[0].FunctionName[34] = "strlen";
    ImportTables[0].FunctionName[35] = "strncpy_s";
    ImportTables[0].FunctionName[36] = "strncpy";
    ImportTables[0].FunctionName[37] = "strncmp";
    ImportTables[0].FunctionName[38] = "strcpy";
    ImportTables[0].FunctionName[39] = "strcmp";
    ImportTables[0].FunctionName[40] = "strncat_s";
    ImportTables[0].FunctionName[41] = "strncat";
    ImportTables[0].FunctionName[42] = "strcpy_s";
    ImportTables[0].FunctionName[43] = "strcat_s";
    ImportTables[0].FunctionName[44] = "strcat";
    ImportTables[0].FunctionName[45] = "srand";
    ImportTables[0].FunctionName[46] = "rand";
    ImportTables[0].FunctionName[47] = "sqrtf";
    ImportTables[0].FunctionName[48] = "sqrt";
    ImportTables[0].FunctionName[49] = "memset";
    ImportTables[0].FunctionName[50] = "_BitTest64";
    ImportTables[0].FunctionName[51] = "memset";
    ImportTables[0].FunctionName[52] = "sprintf_s";
    ImportTables[0].FunctionName[53] = "memcmp";
    ImportTables[0].FunctionName[54] = "memmove";
    ImportTables[0].FunctionName[55] = "sprintf";
    ImportTables[0].FunctionName[56] = "vsprintf";
    ImportTables[0].FunctionName[57] = "HeadlessDispatch";
    ImportTables[0].FunctionName[58] = "InitializeSListHead";
    ImportTables[0].FunctionName[59] = "RtlRaiseStatus";
    ImportTables[0].FunctionName[60] = "InterlockedPushListSList";
    ImportTables[0].FunctionName[61] = "NtAddAtom";
    ImportTables[0].FunctionName[62] = "NtAddAtomEx";
    ImportTables[0].FunctionName[63] = "NtAdjustPrivilegesToken";
    ImportTables[0].FunctionName[64] = "NtAllocateLocallyUniqueId";
    ImportTables[0].FunctionName[65] = "NtAllocateUuids";
    ImportTables[0].FunctionName[66] = "NtAllocateVirtualMemory";
    ImportTables[0].FunctionName[67] = "NtClose";
    ImportTables[0].FunctionName[68] = "NtCommitComplete";
    ImportTables[0].FunctionName[69] = "NtCommitEnlistment";
    ImportTables[0].FunctionName[70] = "RtlUpcaseUnicodeChar";
    ImportTables[0].FunctionName[71] = "PsGetVersion";
    ImportTables[0].FunctionName[72] = "WmiTraceMessageVa";
    ImportTables[0].FunctionName[73] = "WmiTraceMessage";
    ImportTables[0].FunctionName[74] = "WmiQueryTraceInformation";
    
    ImportTables[0].VirtualAddress = NTFunctionAddresses;

    ImportTables[0].VirtualAddress[0] = (uint64_t)RtlCopyUnicodeString;
    ImportTables[0].VirtualAddress[1] = (uint64_t)DbgPrint;
    ImportTables[0].VirtualAddress[2] = (uint64_t)DbgPrintEx;

    ImportTables[0].VirtualAddress[3] = (uint64_t)READ_REGISTER_UCHAR;
    ImportTables[0].VirtualAddress[4] = (uint64_t)WRITE_REGISTER_UCHAR;
    ImportTables[0].VirtualAddress[5] = (uint64_t)READ_REGISTER_USHORT;
    ImportTables[0].VirtualAddress[6] = (uint64_t)WRITE_REGISTER_USHORT;
    ImportTables[0].VirtualAddress[7] = (uint64_t)READ_REGISTER_ULONG;
    ImportTables[0].VirtualAddress[8] = (uint64_t)WRITE_REGISTER_ULONG;

    ImportTables[0].VirtualAddress[9] = (uint64_t)wcslen;
    ImportTables[0].VirtualAddress[10] = (uint64_t)wcscmp;
    ImportTables[0].VirtualAddress[11] = (uint64_t)wcstoul;
    ImportTables[0].VirtualAddress[12] = (uint64_t)wcstombs;
    ImportTables[0].VirtualAddress[13] = (uint64_t)wcsstr;
    ImportTables[0].VirtualAddress[14] = (uint64_t)wcsspn;
    ImportTables[0].VirtualAddress[15] = (uint64_t)wcsrchr;
    ImportTables[0].VirtualAddress[16] = (uint64_t)vDbgPrintEx;
    ImportTables[0].VirtualAddress[17] = (uint64_t)vDbgPrintExWithPrefix;
    ImportTables[0].VirtualAddress[18] = (uint64_t)vswprintf_s;
    ImportTables[0].VirtualAddress[19] = (uint64_t)vsprintf_s;
    ImportTables[0].VirtualAddress[20] = (uint64_t)towupper;
    ImportTables[0].VirtualAddress[21] = (uint64_t)towlower;
    ImportTables[0].VirtualAddress[22] = (uint64_t)tolower;
    ImportTables[0].VirtualAddress[23] = (uint64_t)toupper;
    ImportTables[0].VirtualAddress[24] = (uint64_t)sscanf_s;
    ImportTables[0].VirtualAddress[25] = (uint64_t)_sscanf_s_l;
    ImportTables[0].VirtualAddress[26] = (uint64_t)swscanf_s;
    ImportTables[0].VirtualAddress[27] = (uint64_t)_swscanf_s_l;
    ImportTables[0].VirtualAddress[28] = (uint64_t)swprintf_s;
    ImportTables[0].VirtualAddress[29] = (uint64_t)swprintf;
    ImportTables[0].VirtualAddress[30] = (uint64_t)strtok_s;
    ImportTables[0].VirtualAddress[31] = (uint64_t)strstr;
    ImportTables[0].VirtualAddress[32] = (uint64_t)strspn;
    ImportTables[0].VirtualAddress[33] = (uint64_t)strrchr;
    ImportTables[0].VirtualAddress[34] = (uint64_t)strlen;
    ImportTables[0].VirtualAddress[35] = (uint64_t)strncpy_s;
    ImportTables[0].VirtualAddress[36] = (uint64_t)strncpy;
    ImportTables[0].VirtualAddress[37] = (uint64_t)strncmp;
    ImportTables[0].VirtualAddress[38] = (uint64_t)Winstrcpy;
    ImportTables[0].VirtualAddress[39] = (uint64_t)strcmp;
    ImportTables[0].VirtualAddress[40] = (uint64_t)strncat_s;
    ImportTables[0].VirtualAddress[41] = (uint64_t)strncat;
    ImportTables[0].VirtualAddress[42] = (uint64_t)strcpy_s;
    ImportTables[0].VirtualAddress[43] = (uint64_t)strcat_s;
    ImportTables[0].VirtualAddress[44] = (uint64_t)Winstrcat;
    ImportTables[0].VirtualAddress[45] = (uint64_t)srand;
    ImportTables[0].VirtualAddress[46] = (uint64_t)rand;
    ImportTables[0].VirtualAddress[47] = (uint64_t)sqrtf;
    ImportTables[0].VirtualAddress[48] = (uint64_t)sqrt;
    ImportTables[0].VirtualAddress[49] = (uint64_t)memset;
    ImportTables[0].VirtualAddress[50] = (uint64_t)_BitTest64;
    ImportTables[0].VirtualAddress[51] = (uint64_t)memset;
    ImportTables[0].VirtualAddress[52] = (uint64_t)sprintf_s;
    ImportTables[0].VirtualAddress[53] = (uint64_t)memcmp;
    ImportTables[0].VirtualAddress[54] = (uint64_t)memmove;
    ImportTables[0].VirtualAddress[55] = (uint64_t)sprintf;
    ImportTables[0].VirtualAddress[56] = (uint64_t)vsprintf;
    ImportTables[0].VirtualAddress[57] = (uint64_t)HeadlessDispatch;
    ImportTables[0].VirtualAddress[58] = (uint64_t)InitializeSListHead;
    ImportTables[0].VirtualAddress[59] = (uint64_t)RtlRaiseStatus;
    ImportTables[0].VirtualAddress[60] = (uint64_t)InterlockedPushListSList;
    ImportTables[0].VirtualAddress[61] = (uint64_t)NtAddAtom;
    ImportTables[0].VirtualAddress[62] = (uint64_t)NtAddAtomEx;
    ImportTables[0].VirtualAddress[63] = (uint64_t)NtAdjustPrivilegesToken;
    ImportTables[0].VirtualAddress[64] = (uint64_t)NtAllocateLocallyUniqueId;
    ImportTables[0].VirtualAddress[65] = (uint64_t)NtAllocateUuids;
    ImportTables[0].VirtualAddress[66] = (uint64_t)NtAllocateVirtualMemory;
    ImportTables[0].VirtualAddress[67] = (uint64_t)NtClose;
    ImportTables[0].VirtualAddress[68] = (uint64_t)NtCommitComplete;
    ImportTables[0].VirtualAddress[69] = (uint64_t)NtCommitEnlistment;
    ImportTables[0].VirtualAddress[70] = (uint64_t)RtlUpcaseUnicodeChar;
    ImportTables[0].VirtualAddress[71] = (uint64_t)PsGetVersion;
    ImportTables[0].VirtualAddress[72] = (uint64_t)WmiTraceMessageVa;
    ImportTables[0].VirtualAddress[73] = (uint64_t)WmiTraceMessage;
    ImportTables[0].VirtualAddress[74] = (uint64_t)WmiQueryTraceInformation;

}

static inline    
void InitializeUnKownTable(){

    ImportTables[1].ModuleName = "UNKNOWN";
    ImportTables[1].NumberOfFunctions = PRE_LOADED_UNKOWN_FUNCTIONS;

    ImportTables[1].FunctionName = UnkownFunctionNames;

    //aux_klib
    ImportTables[1].FunctionName[0] = "AuxKlibEnumerateSystemFirmwareTables";
    ImportTables[1].FunctionName[1] = "AuxKlibGetBugCheckData";
    ImportTables[1].FunctionName[2] = "AuxKlibGetImageExportDirectory";
    ImportTables[1].FunctionName[3] = "AuxKlibGetSystemFirmwareTable";
    ImportTables[1].FunctionName[4] = "AuxKlibInitialize";
    ImportTables[1].FunctionName[5] = "AuxKlibQueryModuleInformation";
    //IOACCESS
    ImportTables[1].FunctionName[6] = "READ_PORT_UCHAR";
    ImportTables[1].FunctionName[7] = "READ_PORT_ULONG";
    ImportTables[1].FunctionName[8] = "READ_PORT_USHORT";
    ImportTables[1].FunctionName[9] = "WRITE_PORT_UCHAR";
    ImportTables[1].FunctionName[10] = "WRITE_PORT_ULONG";
    ImportTables[1].FunctionName[11] = "WRITE_PORT_USHORT";
    
    ImportTables[1].VirtualAddress = UnkownFunctionAddresses;

    ImportTables[1].VirtualAddress[0] = (uint64_t)AuxKlibEnumerateSystemFirmwareTables;
    ImportTables[1].VirtualAddress[1] = (uint64_t)AuxKlibGetBugCheckData;
    ImportTables[1].VirtualAddress[2] = (uint64_t)AuxKlibGetImageExportDirectory;
    ImportTables[1].VirtualAddress[3] = (uint64_t)AuxKlibGetSystemFirmwareTable;
    ImportTables[1].VirtualAddress[4] = (uint64_t)AuxKlibInitialize;
    ImportTables[1].VirtualAddress[5] = (uint64_t)AuxKlibQueryModuleInformation;

    ImportTables[1].VirtualAddress[6] = (uint64_t)READ_PORT_UCHAR;
    ImportTables[1].VirtualAddress[7] = (uint64_t)READ_PORT_ULONG;
    ImportTables[1].VirtualAddress[8] = (uint64_t)READ_PORT_USHORT;
    ImportTables[1].VirtualAddress[9] = (uint64_t)WRITE_PORT_UCHAR;
    ImportTables[1].VirtualAddress[10] = (uint64_t)WRITE_PORT_ULONG;
    ImportTables[1].VirtualAddress[11] = (uint64_t)WRITE_PORT_USHORT;

}

static inline
void InitializeWDFLDR_SYS(){
    ImportTables[2].ModuleName = "WDFLDR.SYS";
    ImportTables[2].NumberOfFunctions = PRE_LOADED_WDFLDR_FUNCTIONS;

    ImportTables[2].FunctionName = WDFLDRFunctionNames;

    ImportTables[2].FunctionName[0] = "WdfVersionUnbindClass";
    ImportTables[2].FunctionName[1] = "WdfVersionBindClass";
    ImportTables[2].FunctionName[2] = "WdfVersionUnbind";
    ImportTables[2].FunctionName[3] = "WdfVersionBind";
    ImportTables[2].FunctionName[4] = "WdfLdrQueryInterface";

    ImportTables[2].VirtualAddress = WDFLDRFunctionAddresses;

    ImportTables[2].VirtualAddress[0] = (uint64_t)WdfVersionUnbindClass;
    ImportTables[2].VirtualAddress[1] = (uint64_t)WdfVersionBindClass;
    ImportTables[2].VirtualAddress[2] = (uint64_t)WdfVersionUnbind;
    ImportTables[2].VirtualAddress[3] = (uint64_t)WdfVersionBind;
    ImportTables[2].VirtualAddress[4] = (uint64_t)WdfLdrQueryInterface;

}

STOR_PHYSICAL_ADDRESS StorPortGetPhysicalAddress(
     PVOID HwDeviceExtension,
     PSCSI_REQUEST_BLOCK Srb,
     PVOID VirtualAddress,
    ULONG *Length
);

VOID StorPortStallExecution(
    ULONG Microseconds
);

void StorPortNotification(
    SCSI_NOTIFICATION_TYPE NotificationType,
    PVOID HwDeviceExtension,
    ...
);

void StorPortSetDeviceQueueDepth();

PVOID StorPortGetUncachedExtension(
   PVOID HwDeviceExtension,
   PPORT_CONFIGURATION_INFORMATION ConfigInfo,
   ULONG NumberOfBytes
);

NTSTATUS StorPortInitialize(
    PDRIVER_OBJECT DevObj,
    PUNICODE_STRING RegistryEntry,
    PSTORPORT_HW_INITIALIZATION_DATA HwInitializationData,
    PVOID HwContext
);

void StorPortGetScatterGatherList();

PVOID StorPortGetDeviceBase(
    PVOID   HwDeviceExtension,
    INTERFACE_TYPE BusType,
    ULONG   SystemIoBusNumber,
    PHYSICAL_ADDRESS IoAddress,
    ULONG   NumberOfBytes,
    BOOLEAN InIoSpace
);

NTSTATUS StorPortGetBusData(
  PVOID HwDeviceExtension,
  ULONG BusDataType,
  ULONG SystemIoBusNumber,
  ULONG SlotNumber,
  PVOID Buffer,
  ULONG Length
);
static inline
void InitializeStorePort_SYS(){

    ImportTables[3].ModuleName = "storport.sys";
    ImportTables[3].NumberOfFunctions = PRE_LOADED_STORPORT_FUNCTIONS;

    ImportTables[3].FunctionName = StorportFunctionNames;

    ImportTables[3].FunctionName[0] = "StorPortGetPhysicalAddress";
    ImportTables[3].FunctionName[1] = "StorPortStallExecution";
    ImportTables[3].FunctionName[2] = "StorPortNotification";
    ImportTables[3].FunctionName[3] = "StorPortSetDeviceQueueDepth";
    ImportTables[3].FunctionName[4] = "StorPortGetUncachedExtension";
    ImportTables[3].FunctionName[5] = "StorPortInitialize";
    ImportTables[3].FunctionName[6] = "StorPortGetScatterGatherList";
    ImportTables[3].FunctionName[7] = "StorPortGetDeviceBase";
    ImportTables[3].FunctionName[8] = "StorPortGetBusData";

    ImportTables[3].VirtualAddress = StorportFunctionAddresses;

    ImportTables[3].VirtualAddress[0] = (uint64_t)StorPortGetPhysicalAddress;
    ImportTables[3].VirtualAddress[1] = (uint64_t)StorPortStallExecution;
    ImportTables[3].VirtualAddress[2] = (uint64_t)StorPortNotification;
    ImportTables[3].VirtualAddress[3] = (uint64_t)StorPortSetDeviceQueueDepth;
    ImportTables[3].VirtualAddress[4] = (uint64_t)StorPortGetUncachedExtension;
    ImportTables[3].VirtualAddress[5] = (uint64_t)StorPortInitialize;
    ImportTables[3].VirtualAddress[6] = (uint64_t)StorPortGetScatterGatherList;
    ImportTables[3].VirtualAddress[7] = (uint64_t)StorPortGetDeviceBase;
    ImportTables[3].VirtualAddress[8] = (uint64_t)StorPortGetBusData;


}

void InitializeJitlTables(){
    //Ahci Function
    //SystemSections[0] = &AhciJitlDirectory;
}

LOUDDK_API_ENTRY void InitializeGenericTables(){

    InitializeNtKernelTable();
    InitializeUnKownTable();
    InitializeWDFLDR_SYS();
    InitializeStorePort_SYS();
    InitializeLousineKernelTables();
    InitializeJitlTables();

}


LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
){
    size_t koo = strlen(ModuleName);
    for(size_t foo = 0 ; foo < koo; foo++){
        ModuleName[foo] = toupper(ModuleName[foo]);
    }
    size_t i = 0;
    size_t j = 0;

    //LouPrint("Module:%s Function:%s\n", ModuleName, FunctionName);

    for(i = 0; i < PRE_LOADED_MODULES; i++){

        if(strcmp(ImportTables[i].ModuleName, ModuleName) == 0){
            //LouPrint("Getting A Address From Loaded Module:%s ", ModuleName);
            for(j = 0; j < ImportTables[i].NumberOfFunctions; j++){
                //LouPrint("Getting A Address From Loaded Module:%s ", ImportTables[i].FunctionName[j]);
                if(strcmp(ImportTables[i].FunctionName[j], FunctionName) == 0){
                    //LouPrint("Getting A Address From Loaded Module:%s ", ImportTables[i].FunctionName[j]);
                    //LouPrint("::%h : i:%d j:%d\n", ImportTables[i].VirtualAddress[j], i , j);
                    return ImportTables[i].VirtualAddress[j];
                }
            }
            goto WDK_MODULE_FALLBACK_FUNCTIONS;
        }  
    }

    WDK_MODULE_FALLBACK_FUNCTIONS:
    for(j = 0; j < ImportTables[1].NumberOfFunctions; j++){
        //LouPrint("Getting A Address From Loaded Module:%s ", ImportTables[i].FunctionName[j]);
        if(strcmp(ImportTables[1].FunctionName[j], FunctionName) == 0){
            //LouPrint("::%h : 2\n", ImportTables[1].VirtualAddress[j]);
            return ImportTables[1].VirtualAddress[j];
        }
    }

    //last resourt but most likely here
    PTableTracks Tmp = (PTableTracks)&DynamicLoadedLibraries; 
    for(size_t i = 0 ; i < DynamicLoadedLibrarieCount; i++){
        if(strcmp(Tmp->Table.ModuleName, ModuleName) == 0){
            for(size_t j = 0 ; j < Tmp->Table.NumberOfFunctions; j++){
                if(strcmp(Tmp->Table.FunctionName[j], FunctionName) == 0){
                    //LouPrint("Getting A Address From Loaded Module:%s\n",   Tmp->Table.FunctionName[j]);
                    //LouPrint("Getting A Address From Loaded Address:%h\n",  Tmp->Table.VirtualAddress[j]);
                    //LouPrint("::%h : 3\n", Tmp->Table.VirtualAddress[j]);
                    return Tmp->Table.VirtualAddress[j];
                }
            }
        }
        //LouPrint("Module:%s\n",Tmp->Table.ModuleName);
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PTableTracks)Tmp->Neighbors.NextHeader;
        }
    }

    return 0x00;
}

LOUDDK_API_ENTRY
bool 
LouKeLinkerCheckLibraryPresence(string SystemName){
    
    size_t koo = strlen(SystemName);
    for(size_t foo = 0 ; foo < koo; foo++){
        SystemName[foo] = toupper(SystemName[foo]);
    }
    
    uint8_t i = 0;
    for(i = 0; i < PRE_LOADED_MODULES; i++){

        if(strcmp(ImportTables[i].ModuleName, SystemName) == 0){
            return true;
        }  
    }

    //last resourt but most likely here
    PTableTracks Tmp = (PTableTracks)&DynamicLoadedLibraries; 
    for(uint16_t i = 0 ; i < DynamicLoadedLibrarieCount; i++){
        if(strcmp(Tmp->Table.ModuleName, SystemName) == 0){
            return true;
        }
        //LouPrint("Module:%s\n",Tmp->Table.ModuleName);
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PTableTracks)Tmp->Neighbors.NextHeader;
        }
    }
    return false;
}