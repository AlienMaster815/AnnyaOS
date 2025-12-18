#include <LouDDK.h>
#include <NtAPI.h>
#include <Hal.h>
#include <drivers/Dma8237A.h>
#include <usb.h>
#include <KulaAPI.h>


typedef struct _TABLE_ENTRY{
    FILE_NAME        ModuleName;
    uint32_t         NumberOfFunctions;
    FUNCTION_NAME*   FunctionName;
    uint64_t*        VirtualAddress;
}TABLE_ENTRY, * PTABLE_ENTRY;

typedef struct _TableTracks{
    ListHeader                      Neighbors;
    TABLE_ENTRY                     Table;
    bool                            LongModeEntry;
    PKULA_TRANSITION_LAYER_OBECT    TransitionObject;
    KERNEL_REFERENCE                Counter;
}TableTracks, * PTableTracks;

#define PRE_LOADED_MODULES 4
//#define PRE_LOADED_NTOSKRNL_FUNCTIONS 0
#define PRE_LOADED_UNKOWN_FUNCTIONS 12
#define PRE_LOADED_WDFLDR_FUNCTIONS 5
#define PRE_LOADED_STORPORT_FUNCTIONS 9
#define PRE_LOADED_LOUOSKRNL_FUNCTIONS 192

static uint64_t LouOsKrnlFunctionAddresses[PRE_LOADED_LOUOSKRNL_FUNCTIONS];
static FUNCTION_NAME LouOsKrnlFunctionNames[PRE_LOADED_LOUOSKRNL_FUNCTIONS];
//UNUSED static uint64_t NTFunctionAddresses[PRE_LOADED_NTOSKRNL_FUNCTIONS];
//UNUSED static FUNCTION_NAME NTFunctionNames[PRE_LOADED_NTOSKRNL_FUNCTIONS];
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
void LouKeInitializeLibraryLookupEx(
    string                          ModuleName,
    uint32_t                        NumberOfFunctions,
    string*                         FunctionNames,
    uint64_t*                       FunctionAddresses,
    bool                            IsNativeLongmode,
    PKULA_TRANSITION_LAYER_OBECT    TransitionObject
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
    Tmp->TransitionObject = TransitionObject;

    DynamicLoadedLibrarieCount++;
}

LOUDDK_API_ENTRY
void LouKeInitializeLibraryLookup(
    string    ModuleName,
    uint32_t  NumberOfFunctions,
    string*   FunctionNames,
    uint64_t* FunctionAddresses,
    bool      IsNativeLongmode
){
    LouKeInitializeLibraryLookupEx(
        ModuleName,
        NumberOfFunctions,
        FunctionNames,
        FunctionAddresses,
        IsNativeLongmode,
        0x00
    );
}

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

KERNEL_IMPORT void* LouKePciGetIoRegion(
    PPCI_DEVICE_OBJECT PDEV, 
    uint8_t BarNumber,
    size_t BarOffset
);

KERNEL_IMPORT
PDMI_SYSTEM_ID LouKeDmiGetFirstMatch(PDMI_SYSTEM_ID IdList);

KERNEL_IMPORT
int snprintf(char *buffer, size_t buffer_size, const char *format, ...);

KERNEL_IMPORT
BOOL DmiGetDate(DMI_FIELD Field, INTEGER* Year, INTEGER* Month, INTEGER* Day);

static inline 
void InitializeLousineKernelTables(){
    ImportTables[0].ModuleName = "LOUOSKRNL.EXE";
    ImportTables[0].NumberOfFunctions = PRE_LOADED_LOUOSKRNL_FUNCTIONS;
    ImportTables[0].FunctionName = LouOsKrnlFunctionNames;   
    ImportTables[0].FunctionName[0] = "LouPrint";
    ImportTables[0].FunctionName[1] = "RegisterInterruptHandler";
    ImportTables[0].FunctionName[2] = "memcpy";
    ImportTables[0].FunctionName[3] = "strncmp";
    ImportTables[0].FunctionName[4] = "strcmp";
    ImportTables[0].FunctionName[5] = "memcmp";
    ImportTables[0].FunctionName[6] = "strncpy";
    ImportTables[0].FunctionName[7] = "insw";
    ImportTables[0].FunctionName[8] = "LouKeFreeFromPool";
    ImportTables[0].FunctionName[9] = "LouKeMallocFromPool";
    ImportTables[0].FunctionName[10] = "LouKeFreePool";
    ImportTables[0].FunctionName[11] = "LouKeMapPool";
    ImportTables[0].FunctionName[12] = "RequestPhysicalAddress";
    ImportTables[0].FunctionName[13] = "LouKeVMemmoryGetSize";
    ImportTables[0].FunctionName[14] = "LouKeMapContinuousMemoryBlock";
    ImportTables[0].FunctionName[15] = "LouVMalloc";
    ImportTables[0].FunctionName[16] = "LouVMallocEx";
    ImportTables[0].FunctionName[17] = "LouKeAllocateUncachedVMemoryEx";
    ImportTables[0].FunctionName[18] = "LouKeAllocateUncachedVMemory";
    ImportTables[0].FunctionName[19] = "SearchForMappedAddressSize";
    ImportTables[0].FunctionName[20] = "LouKeVMemmorySearchVirtualSpace";
    ImportTables[0].FunctionName[21] = "LouKeVMemmorySearchPhysicalSpace";
    ImportTables[0].FunctionName[22] = "LouKeMallocVMmIO";
    ImportTables[0].FunctionName[23] = "LouFree";
    ImportTables[0].FunctionName[24] = "LouKeTestAndResetBit8";
    ImportTables[0].FunctionName[25] = "LouKeTestBitAndUnSet8";
    ImportTables[0].FunctionName[26] = "LouKeTestBitAndSet8";
    ImportTables[0].FunctionName[27] = "LouKeTestBit8";
    ImportTables[0].FunctionName[28] = "LouKeUnSetBit8";
    ImportTables[0].FunctionName[29] = "LouKeSetBit8";
    ImportTables[0].FunctionName[30] = "LouKeTestAndResetBitU8";
    ImportTables[0].FunctionName[31] = "LouKeTestBitAndUnSetU8";
    ImportTables[0].FunctionName[32] = "LouKeTestBitAndSetU8";
    ImportTables[0].FunctionName[33] = "LouKeTestBitU8";
    ImportTables[0].FunctionName[34] = "LouKeUnSetBitU8";
    ImportTables[0].FunctionName[35] = "LouKeSetBitU8";
    ImportTables[0].FunctionName[36] = "LouKeTestAndResetBit16";
    ImportTables[0].FunctionName[37] = "LouKeTestBitAndUnSet16";
    ImportTables[0].FunctionName[38] = "LouKeTestBitAndSet16";
    ImportTables[0].FunctionName[39] = "LouKeTestBit16";
    ImportTables[0].FunctionName[40] = "LouKeUnSetBit16";
    ImportTables[0].FunctionName[41] = "LouKeSetBit16";
    ImportTables[0].FunctionName[42] = "LouKeTestAndResetBitU16";
    ImportTables[0].FunctionName[43] = "LouKeTestBitAndUnSetU16";
    ImportTables[0].FunctionName[44] = "LouKeTestBitAndSetU16";
    ImportTables[0].FunctionName[45] = "LouKeTestBitU16";
    ImportTables[0].FunctionName[46] = "LouKeUnSetBitU16";
    ImportTables[0].FunctionName[47] = "LouKeSetBitU16";
    ImportTables[0].FunctionName[48] = "LouKeTestAndResetBit32";
    ImportTables[0].FunctionName[49] = "LouKeTestBitAndUnSet32";
    ImportTables[0].FunctionName[50] = "LouKeTestBitAndSet32";
    ImportTables[0].FunctionName[51] = "LouKeTestBit32";
    ImportTables[0].FunctionName[52] = "LouKeUnSetBit32";
    ImportTables[0].FunctionName[53] = "LouKeSetBit32";
    ImportTables[0].FunctionName[54] = "LouKeTestAndResetBitU32";
    ImportTables[0].FunctionName[55] = "LouKeTestBitAndUnSetU32";
    ImportTables[0].FunctionName[56] = "LouKeTestBitAndSetU32";
    ImportTables[0].FunctionName[57] = "LouKeTestBitU32";
    ImportTables[0].FunctionName[58] = "LouKeUnSetBitU32";
    ImportTables[0].FunctionName[59] = "LouKeSetBitU32";
    ImportTables[0].FunctionName[60] = "LouKeTestAndResetBit64";
    ImportTables[0].FunctionName[61] = "LouKeTestBitAndUnSet64";
    ImportTables[0].FunctionName[62] = "LouKeTestBit64";
    ImportTables[0].FunctionName[63] = "LouKeUnSetBit64";
    ImportTables[0].FunctionName[64] = "LouKeSetBit64";
    ImportTables[0].FunctionName[65] = "LouKeTestAndResetBitU64";
    ImportTables[0].FunctionName[66] = "LouKeTestBitAndUnSetU64";
    ImportTables[0].FunctionName[67] = "LouKeTestBitAndSetU64";
    ImportTables[0].FunctionName[68] = "LouKeTDrsdInternalAtomicCheckestBitU64";
    ImportTables[0].FunctionName[69] = "LouKeUnSetBitU64";
    ImportTables[0].FunctionName[70] = "LouKeSetBitU64";
    ImportTables[0].FunctionName[71] = "LouKeCreateDemon";
    ImportTables[0].FunctionName[72] = "LouKeAcquireSpinLock";
    ImportTables[0].FunctionName[73] = "LouKeReleaseSpinLock";
    ImportTables[0].FunctionName[74] = "LouAllocatePhysical64UpEx";
    ImportTables[0].FunctionName[75] = "GetPciConfiguration";
    ImportTables[0].FunctionName[76] = "LouKeHalLinuxPciCheckForCompatibleConfiguration";
    ImportTables[0].FunctionName[77] = "pci_read";
    ImportTables[0].FunctionName[78] = "write_pci";
    ImportTables[0].FunctionName[79] = "LouKeReadPciUint8";
    ImportTables[0].FunctionName[80] = "LouKeReadPciUint16";
    ImportTables[0].FunctionName[81] = "LouKeReadPciUint32";
    ImportTables[0].FunctionName[82] = "LouKeWritePciUint8";
    ImportTables[0].FunctionName[83] = "LouKeWritePciUint16";
    ImportTables[0].FunctionName[84] = "LouKeWritePciUint32";
    ImportTables[0].FunctionName[85] = "LouKeHalEnablePciDevice";
    ImportTables[0].FunctionName[86] = "LouKePciGetIoRegion";
    ImportTables[0].FunctionName[87] = "LouKeHalPciSaveContext";
    ImportTables[0].FunctionName[88] = "LouKeHalPciRestoreContext";
    ImportTables[0].FunctionName[89] = "LouKeHalPciClearMaster";
    ImportTables[0].FunctionName[90] = "READ_REGISTER_ULONG";
    ImportTables[0].FunctionName[91] = "LouMallocAtaHost";
    ImportTables[0].FunctionName[92] = "LouKeHalMallocPciIrqVectors";
    ImportTables[0].FunctionName[93] = "WRITE_PORT_ULONG";
    ImportTables[0].FunctionName[94] = "WRITE_REGISTER_ULONG";
    ImportTables[0].FunctionName[95] = "sleep";
    ImportTables[0].FunctionName[96] = "LouKeHalPciSetMaster";
    ImportTables[0].FunctionName[97] = "LouKeRegisterDevice";
    ImportTables[0].FunctionName[98] = "AtaStdQcDefer";
    ImportTables[0].FunctionName[99] = "LouGeneralAllocateMemoryEx";
    ImportTables[0].FunctionName[100] = "memset";
    ImportTables[0].FunctionName[101] = "LouKeWaitForMmioState";
    ImportTables[0].FunctionName[102] = "LouKeCreateFixedPool";
    ImportTables[0].FunctionName[103] = "outw";
    ImportTables[0].FunctionName[104] = "LouKeMallocEx";
    ImportTables[0].FunctionName[105] = "LouKeMalloc";
    ImportTables[0].FunctionName[106] = "inw";
    ImportTables[0].FunctionName[107] = "outw";
    ImportTables[0].FunctionName[108] = "LouKeLinkerGetAddress";
    ImportTables[0].FunctionName[109] = "LoukeRegisterNetFrameHardwareDriver";
    ImportTables[0].FunctionName[110] = "LouKePciGetInterruptLine";
    ImportTables[0].FunctionName[111] = "inl";
    ImportTables[0].FunctionName[112] = "LouKeMapDynamicPool";
    ImportTables[0].FunctionName[113] = "LouKeMallocFromDynamicPool";
    ImportTables[0].FunctionName[114] = "LouKeMallocFromDynamicPoolEx";
    ImportTables[0].FunctionName[115] = "outl";
    ImportTables[0].FunctionName[116] = "LouKeFreeFromDynamicPool";
    ImportTables[0].FunctionName[117] = "LouKeHalGetPciBaseAddressSize";
    ImportTables[0].FunctionName[118] = "LouKeCreateGenericPool";
    ImportTables[0].FunctionName[119] = "LouKeGenricAllocateDmaPool";
    ImportTables[0].FunctionName[120] = "LouKeGenericPoolGetPhyAddress";
    ImportTables[0].FunctionName[121] = "LouKePassVramToDrsdMemoryManager";
    ImportTables[0].FunctionName[122] = "DrsdGxeCreateAsyncFramebuffer";
    ImportTables[0].FunctionName[123] = "DrsdGxeVramInternalModeValid";
    ImportTables[0].FunctionName[124] = "DrsdInternalAtomicCheck";
    ImportTables[0].FunctionName[125] = "DrsdInternalAtomicUpdate";
    ImportTables[0].FunctionName[126] = "DrsdInternalResetPlane";
    ImportTables[0].FunctionName[127] = "DrsdInternalDestroyPlane";
    ImportTables[0].FunctionName[128] = "DrsdInternalPlaneDisableAtomic";
    ImportTables[0].FunctionName[129] = "DrsdInternalPlaneUpdateAtomic";
    ImportTables[0].FunctionName[130] = "DrsdInternalDestroyPlaneAtomic";
    ImportTables[0].FunctionName[131] = "DrsdInternalDuplicateAtomicState";
    ImportTables[0].FunctionName[132] = "DrsdGxeInternalPrepareFrameBuffer";
    ImportTables[0].FunctionName[133] = "DrsdGxeInternalCleanupFrameBuffer";
    ImportTables[0].FunctionName[134] = "DrsdGxeInternalStartFrameBufferProcessing";
    ImportTables[0].FunctionName[135] = "DrsdGxeInternalStopFrameBufferProcessing";
    ImportTables[0].FunctionName[136] = "DrsdGxeDestroyShadowPlane";
    ImportTables[0].FunctionName[137] = "DrsdGxeDuplicateShadowPlaneState";
    ImportTables[0].FunctionName[138] = "DrsdGxeResetShadowPlane";
    ImportTables[0].FunctionName[139] = "DrsdInitializeGenericPlane";
    ImportTables[0].FunctionName[140] = "DrsdInitializeCrtcWithPlanes";
    ImportTables[0].FunctionName[141] = "DrsdInitializeCrtcGammaSize";
    ImportTables[0].FunctionName[142] = "DrsdInternalCrtcSetConfigurationAtomic";
    ImportTables[0].FunctionName[143] = "DrsdInternalCrtcPageFlipAtomic";
    ImportTables[0].FunctionName[144] = "DrsdInternalCrtcResetAtomic";
    ImportTables[0].FunctionName[145] = "DrsdInternalCrtcDuplicateStateAtomic";
    ImportTables[0].FunctionName[146] = "DrsdInternalCrtcDestroyStateAtomic";
    ImportTables[0].FunctionName[147] = "DrsdInitializeEncoder";
    ImportTables[0].FunctionName[148] = "DrsdInternalAtomicConnectorDestroyState";
    ImportTables[0].FunctionName[149] = "DrsdInternalAtomicConnectorDuplicateState";
    ImportTables[0].FunctionName[150] = "DrsdInternalResetConnector";
    ImportTables[0].FunctionName[151] = "DrsdConnectorInitialize";
    ImportTables[0].FunctionName[152] = "DrsdModeConfigurationReset";
    ImportTables[0].FunctionName[153] = "DrsdInternalProbeSingleConnectorModes";
    ImportTables[0].FunctionName[154] = "LouKeGetThreadIdentification";
    ImportTables[0].FunctionName[155] = "LouKeHalGetPciConfiguration";
    ImportTables[0].FunctionName[156] = "LouKeFree";
    ImportTables[0].FunctionName[157] = "LouKeMallocAtaDevice";
    ImportTables[0].FunctionName[158] = "LouKeMallocAtaPrivateData";
    ImportTables[0].FunctionName[159] = "LouKeForkAtaHostPrivateDataToPorts";
    ImportTables[0].FunctionName[160] = "DrsdAddModesNoEDID";
    ImportTables[0].FunctionName[161] = "DrsdModeVfresh";
    ImportTables[0].FunctionName[162] = "DrsdCvtMode";
    ImportTables[0].FunctionName[163] = "DrsdAddProbedDisplayModeToConnector";
    ImportTables[0].FunctionName[164] = "DrsdUpdateEdidConnectorProperties";
    ImportTables[0].FunctionName[165] = "DrsdGetNewPlaneState";
    ImportTables[0].FunctionName[166] = "LouKeDrsdHandleConflictingDevices";
    ImportTables[0].FunctionName[167] = "inb";
    ImportTables[0].FunctionName[168] = "outb";
    ImportTables[0].FunctionName[169] = "LouKeCreateBusClass";
    ImportTables[0].FunctionName[170] = "LouKeLoadSubsystem";
    ImportTables[0].FunctionName[171] = "LouKeLoadDriver";
    ImportTables[0].FunctionName[172] = "LouKeMouseAllocateMessageDevice";
    ImportTables[0].FunctionName[173] = "LouKeMouseUpdateInput";
    ImportTables[0].FunctionName[174] = "LouKeMallocDma16Ex";
    ImportTables[0].FunctionName[175] = "LouKeMallocDma16";
    ImportTables[0].FunctionName[176] = "LouKeFreeDma16";
    ImportTables[0].FunctionName[177] = "LouKeQueueWork";
    ImportTables[0].FunctionName[178] = "LouKeGetAllocationSize";
    ImportTables[0].FunctionName[179] = "LouKeGenericAllocateFixedDmaPool";
    ImportTables[0].FunctionName[180] = "LouKeFreeFromFixedPool";
    ImportTables[0].FunctionName[181] = "LouKeDmiGetFirstMatch";
    ImportTables[0].FunctionName[182] = "snprintf";
    ImportTables[0].FunctionName[183] = "PciTestAtaConfigurationBits";
    ImportTables[0].FunctionName[184] = "LouKeDmiGetFirstMatch";
    ImportTables[0].FunctionName[185] = "DmiGetDate";
    ImportTables[0].FunctionName[186] = "LouKeMallocExPhy32";
    ImportTables[0].FunctionName[187] = "READ_REGISTER_ULONGLONG";
    ImportTables[0].FunctionName[188] = "WRITE_REGISTER_ULONGLONG";
    ImportTables[0].FunctionName[189] = "LouKeCheckDmiSystem";
    ImportTables[0].FunctionName[190] = "LouKeHalGetPciIrqVectorCount";
    ImportTables[0].FunctionName[191] = "LouKeMallocPhy32";

    ImportTables[0].VirtualAddress = LouOsKrnlFunctionAddresses;

    ImportTables[0].VirtualAddress[0] = (uint64_t)LouPrint;
    ImportTables[0].VirtualAddress[1] = (uint64_t)RegisterInterruptHandler;
    ImportTables[0].VirtualAddress[2] = (uint64_t)memcpy;
    ImportTables[0].VirtualAddress[3] = (uint64_t)strncmp;
    ImportTables[0].VirtualAddress[4] = (uint64_t)strcmp;
    ImportTables[0].VirtualAddress[5] = (uint64_t)memcmp;
    ImportTables[0].VirtualAddress[6] = (uint64_t)strncpy;
    ImportTables[0].VirtualAddress[7] = (uint64_t)insw;
    ImportTables[0].VirtualAddress[8] = (uint64_t)outsw;
    ImportTables[0].VirtualAddress[9] = (uint64_t)LouKeFreeFromPool;
    ImportTables[0].VirtualAddress[10] = (uint64_t)LouKeMallocFromPool;
    ImportTables[0].VirtualAddress[11] = (uint64_t)LouKeMapPool;
    ImportTables[0].VirtualAddress[12] = (uint64_t)RequestPhysicalAddress;
    ImportTables[0].VirtualAddress[13] = (uint64_t)LouKeVMemmoryGetSize;
    ImportTables[0].VirtualAddress[14] = (uint64_t)LouKeMapContinuousMemoryBlock;
    ImportTables[0].VirtualAddress[15] = (uint64_t)LouVMalloc;
    ImportTables[0].VirtualAddress[16] = (uint64_t)LouVMallocEx;
    ImportTables[0].VirtualAddress[17] = (uint64_t)LouKeAllocateUncachedVMemoryEx;
    ImportTables[0].VirtualAddress[18] = (uint64_t)LouKeAllocateUncachedVMemory;
    ImportTables[0].VirtualAddress[19] = (uint64_t)SearchForMappedAddressSize;
    ImportTables[0].VirtualAddress[20] = (uint64_t)LouKeVMemmorySearchVirtualSpace;
    ImportTables[0].VirtualAddress[21] = (uint64_t)LouKeVMemmorySearchPhysicalSpace;
    ImportTables[0].VirtualAddress[22] = (uint64_t)LouKeMallocVMmIO;
    ImportTables[0].VirtualAddress[23] = (uint64_t)LouFree;
    ImportTables[0].VirtualAddress[24] = (uint64_t)LouKeTestAndResetBit8;
    ImportTables[0].VirtualAddress[25] = (uint64_t)LouKeTestBitAndUnSet8;
    ImportTables[0].VirtualAddress[26] = (uint64_t)LouKeTestBitAndSet8;
    ImportTables[0].VirtualAddress[27] = (uint64_t)LouKeTestBit8;
    ImportTables[0].VirtualAddress[28] = (uint64_t)LouKeUnSetBit8;
    ImportTables[0].VirtualAddress[29] = (uint64_t)LouKeSetBit8;
    ImportTables[0].VirtualAddress[30] = (uint64_t)LouKeTestAndResetBitU8;
    ImportTables[0].VirtualAddress[31] = (uint64_t)LouKeTestBitAndUnSetU8;
    ImportTables[0].VirtualAddress[32] = (uint64_t)LouKeTestBitAndSetU8;
    ImportTables[0].VirtualAddress[33] = (uint64_t)LouKeTestBitU8;
    ImportTables[0].VirtualAddress[34] = (uint64_t)LouKeUnSetBitU8;
    ImportTables[0].VirtualAddress[35] = (uint64_t)LouKeSetBitU8;
    ImportTables[0].VirtualAddress[36] = (uint64_t)LouKeTestAndResetBit16;
    ImportTables[0].VirtualAddress[37] = (uint64_t)LouKeTestBitAndUnSet16;
    ImportTables[0].VirtualAddress[38] = (uint64_t)LouKeTestBitAndSet16;
    ImportTables[0].VirtualAddress[39] = (uint64_t)LouKeTestBit16;
    ImportTables[0].VirtualAddress[40] = (uint64_t)LouKeUnSetBit16;
    ImportTables[0].VirtualAddress[41] = (uint64_t)LouKeSetBit16;
    ImportTables[0].VirtualAddress[42] = (uint64_t)LouKeTestAndResetBitU16;
    ImportTables[0].VirtualAddress[43] = (uint64_t)LouKeTestBitAndUnSetU16;
    ImportTables[0].VirtualAddress[44] = (uint64_t)LouKeTestBitAndSetU16;
    ImportTables[0].VirtualAddress[45] = (uint64_t)LouKeTestBitU16;
    ImportTables[0].VirtualAddress[46] = (uint64_t)LouKeUnSetBitU16;
    ImportTables[0].VirtualAddress[47] = (uint64_t)LouKeSetBitU16;
    ImportTables[0].VirtualAddress[48] = (uint64_t)LouKeTestAndResetBit32;
    ImportTables[0].VirtualAddress[49] = (uint64_t)LouKeTestBitAndUnSet32;
    ImportTables[0].VirtualAddress[50] = (uint64_t)LouKeTestBitAndSet32;
    ImportTables[0].VirtualAddress[51] = (uint64_t)LouKeTestBit32;
    ImportTables[0].VirtualAddress[52] = (uint64_t)LouKeUnSetBit32;
    ImportTables[0].VirtualAddress[53] = (uint64_t)LouKeSetBit32;
    ImportTables[0].VirtualAddress[54] = (uint64_t)LouKeTestAndResetBitU32;
    ImportTables[0].VirtualAddress[55] = (uint64_t)LouKeTestBitAndUnSetU32;
    ImportTables[0].VirtualAddress[56] = (uint64_t)LouKeTestBitU32;
    ImportTables[0].VirtualAddress[57] = (uint64_t)LouKeUnSetBitU32;
    ImportTables[0].VirtualAddress[58] = (uint64_t)LouKeSetBitU32;
    ImportTables[0].VirtualAddress[59] = (uint64_t)LouKeTestAndResetBit64;
    ImportTables[0].VirtualAddress[60] = (uint64_t)LouKeTestBitAndUnSet64;
    ImportTables[0].VirtualAddress[61] = (uint64_t)LouKeTestBitAndSet64;
    ImportTables[0].VirtualAddress[62] = (uint64_t)LouKeTestBit64;
    ImportTables[0].VirtualAddress[63] = (uint64_t)LouKeUnSetBit64;
    ImportTables[0].VirtualAddress[64] = (uint64_t)LouKeSetBit64;
    ImportTables[0].VirtualAddress[65] = (uint64_t)LouKeTestAndResetBitU64;
    ImportTables[0].VirtualAddress[66] = (uint64_t)LouKeTestBitAndUnSetU64;
    ImportTables[0].VirtualAddress[67] = (uint64_t)LouKeTestBitAndSetU64;
    ImportTables[0].VirtualAddress[68] = (uint64_t)LouKeTestBitU64;
    ImportTables[0].VirtualAddress[69] = (uint64_t)LouKeUnSetBitU64;
    ImportTables[0].VirtualAddress[70] = (uint64_t)LouKeSetBitU64;
    ImportTables[0].VirtualAddress[71] = (uint64_t)LouKeCreateDemon;
    ImportTables[0].VirtualAddress[72] = (uint64_t)LouKeAcquireSpinLock;
    ImportTables[0].VirtualAddress[73] = (uint64_t)LouKeReleaseSpinLock;
    ImportTables[0].VirtualAddress[74] = (uint64_t)LouAllocatePhysical64UpEx;
    ImportTables[0].VirtualAddress[75] = (uint64_t)GetPciConfiguration;
    ImportTables[0].VirtualAddress[76] = (uint64_t)LouKeHalLinuxPciCheckForCompatibleConfiguration;
    ImportTables[0].VirtualAddress[77] = (uint64_t)pci_read;
    ImportTables[0].VirtualAddress[78] = (uint64_t)write_pci;
    ImportTables[0].VirtualAddress[79] = (uint64_t)LouKeReadPciUint8;
    ImportTables[0].VirtualAddress[80] = (uint64_t)LouKeReadPciUint16;
    ImportTables[0].VirtualAddress[81] = (uint64_t)LouKeReadPciUint32;
    ImportTables[0].VirtualAddress[82] = (uint64_t)LouKeWritePciUint8;
    ImportTables[0].VirtualAddress[83] = (uint64_t)LouKeWritePciUint16;
    ImportTables[0].VirtualAddress[84] = (uint64_t)LouKeWritePciUint32;
    ImportTables[0].VirtualAddress[85] = (uint64_t)LouKeHalEnablePciDevice;
    ImportTables[0].VirtualAddress[86] = (uint64_t)LouKePciGetIoRegion;
    ImportTables[0].VirtualAddress[87] = (uint64_t)LouKeHalPciSaveContext;
    ImportTables[0].VirtualAddress[88] = (uint64_t)LouKeHalPciRestoreContext;
    ImportTables[0].VirtualAddress[89] = (uint64_t)LouKeHalPciClearMaster;
    ImportTables[0].VirtualAddress[90] = (uint64_t)READ_REGISTER_ULONG;
    ImportTables[0].VirtualAddress[92] = (uint64_t)LouKeHalMallocPciIrqVectors;
    ImportTables[0].VirtualAddress[93] = (uint64_t)WRITE_PORT_ULONG;
    ImportTables[0].VirtualAddress[94] = (uint64_t)WRITE_REGISTER_ULONG;
    ImportTables[0].VirtualAddress[95] = (uint64_t)sleep;
    ImportTables[0].VirtualAddress[96] = (uint64_t)LouKeHalPciSetMaster;
    ImportTables[0].VirtualAddress[97] = (uint64_t)LouKeRegisterDevice;
    ImportTables[0].VirtualAddress[99] = (uint64_t)LouGeneralAllocateMemoryEx;
    ImportTables[0].VirtualAddress[100] = (uint64_t)memset;
    ImportTables[0].VirtualAddress[101] = (uint64_t)LouKeWaitForMmioState;
    ImportTables[0].VirtualAddress[102] = (uint64_t)LouKeCreateFixedPool;
    ImportTables[0].VirtualAddress[103] = (uint64_t)outw; 
    ImportTables[0].VirtualAddress[104] = (uint64_t)LouKeMallocEx;
    ImportTables[0].VirtualAddress[105] = (uint64_t)LouKeMalloc;
    ImportTables[0].VirtualAddress[106] = (uint64_t)inw;
    ImportTables[0].VirtualAddress[107] = (uint64_t)outw;
    ImportTables[0].VirtualAddress[108] = (uint64_t)LouKeLinkerGetAddress;
    ImportTables[0].VirtualAddress[109] = (uint64_t)LoukeRegisterNetFrameHardwareDriver;
    ImportTables[0].VirtualAddress[110] = (uint64_t)LouKePciGetInterruptLine;
    ImportTables[0].VirtualAddress[111] = (uint64_t)inl;
    ImportTables[0].VirtualAddress[112] = (uint64_t)LouKeMapDynamicPool;
    ImportTables[0].VirtualAddress[113] = (uint64_t)LouKeMallocFromDynamicPool;
    ImportTables[0].VirtualAddress[114] = (uint64_t)LouKeMallocFromDynamicPoolEx;
    ImportTables[0].VirtualAddress[115] = (uint64_t)outl;
    ImportTables[0].VirtualAddress[116] = (uint64_t)LouKeFreeFromDynamicPool;
    ImportTables[0].VirtualAddress[117] = (uint64_t)LouKeHalGetPciBaseAddressSize;
    ImportTables[0].VirtualAddress[118] = (uint64_t)LouKeCreateGenericPool;
    ImportTables[0].VirtualAddress[119] = (uint64_t)LouKeGenricAllocateDmaPool;
    ImportTables[0].VirtualAddress[120] = (uint64_t)LouKeGenericPoolGetPhyAddress;
    ImportTables[0].VirtualAddress[121] = (uint64_t)LouKePassVramToDrsdMemoryManager;
    ImportTables[0].VirtualAddress[122] = (uint64_t)DrsdGxeCreateAsyncFramebuffer;
    ImportTables[0].VirtualAddress[123] = (uint64_t)DrsdGxeVramInternalModeValid;
    ImportTables[0].VirtualAddress[124] = (uint64_t)DrsdInternalAtomicCheck;
    ImportTables[0].VirtualAddress[125] = (uint64_t)DrsdInternalAtomicUpdate;
    ImportTables[0].VirtualAddress[126] = (uint64_t)DrsdInternalResetPlane;
    ImportTables[0].VirtualAddress[127] = (uint64_t)DrsdInternalDestroyPlane;
    ImportTables[0].VirtualAddress[128] = (uint64_t)DrsdInternalPlaneDisableAtomic;
    ImportTables[0].VirtualAddress[129] = (uint64_t)DrsdInternalPlaneUpdateAtomic;
    ImportTables[0].VirtualAddress[130] = (uint64_t)DrsdInternalDestroyPlaneAtomic;
    ImportTables[0].VirtualAddress[131] = (uint64_t)DrsdInternalDuplicateAtomicState;
    ImportTables[0].VirtualAddress[132] = (uint64_t)DrsdGxeInternalPrepareFrameBuffer;
    ImportTables[0].VirtualAddress[133] = (uint64_t)DrsdGxeInternalCleanupFrameBuffer;
    ImportTables[0].VirtualAddress[134] = (uint64_t)DrsdGxeInternalStartFrameBufferProcessing;
    ImportTables[0].VirtualAddress[135] = (uint64_t)DrsdGxeInternalStopFrameBufferProcessing;
    ImportTables[0].VirtualAddress[136] = (uint64_t)DrsdGxeDestroyShadowPlane;
    ImportTables[0].VirtualAddress[137] = (uint64_t)DrsdGxeDuplicateShadowPlaneState;
    ImportTables[0].VirtualAddress[138] = (uint64_t)DrsdGxeResetShadowPlane;
    ImportTables[0].VirtualAddress[139] = (uint64_t)DrsdInitializeGenericPlane;
    ImportTables[0].VirtualAddress[140] = (uint64_t)DrsdInitializeCrtcWithPlanes;
    ImportTables[0].VirtualAddress[141] = (uint64_t)DrsdInitializeCrtcGammaSize;
    ImportTables[0].VirtualAddress[142] = (uint64_t)DrsdInternalCrtcSetConfigurationAtomic;
    ImportTables[0].VirtualAddress[143] = (uint64_t)DrsdInternalCrtcPageFlipAtomic;
    ImportTables[0].VirtualAddress[144] = (uint64_t)DrsdInternalCrtcResetAtomic;
    ImportTables[0].VirtualAddress[145] = (uint64_t)DrsdInternalCrtcDuplicateStateAtomic;
    ImportTables[0].VirtualAddress[146] = (uint64_t)DrsdInternalCrtcDestroyStateAtomic;
    ImportTables[0].VirtualAddress[147] = (uint64_t)DrsdInitializeEncoder;
    ImportTables[0].VirtualAddress[148] = (uint64_t)DrsdInternalAtomicConnectorDestroyState;
    ImportTables[0].VirtualAddress[149] = (uint64_t)DrsdInternalAtomicConnectorDuplicateState;
    ImportTables[0].VirtualAddress[150] = (uint64_t)DrsdInternalResetConnector;
    ImportTables[0].VirtualAddress[151] = (uint64_t)DrsdConnectorInitialize;
    ImportTables[0].VirtualAddress[152] = (uint64_t)DrsdModeConfigurationReset;
    ImportTables[0].VirtualAddress[153] = (uint64_t)DrsdInternalProbeSingleConnectorModes;
    ImportTables[0].VirtualAddress[154] = (uint64_t)LouKeGetThreadIdentification;
    ImportTables[0].VirtualAddress[155] = (uint64_t)LouKeHalGetPciConfiguration;
    ImportTables[0].VirtualAddress[156] = (uint64_t)LouKeFree;
    ImportTables[0].VirtualAddress[157] = (uint64_t)LouKeMallocAtaDevice;
    ImportTables[0].VirtualAddress[158] = (uint64_t)LouKeMallocAtaPrivateData;
    ImportTables[0].VirtualAddress[159] = (uint64_t)LouKeForkAtaHostPrivateDataToPorts;
    ImportTables[0].VirtualAddress[160] = (uint64_t)DrsdAddModesNoEDID;
    ImportTables[0].VirtualAddress[161] = (uint64_t)DrsdModeVfresh;
    ImportTables[0].VirtualAddress[162] = (uint64_t)DrsdCvtMode;
    ImportTables[0].VirtualAddress[163] = (uint64_t)DrsdAddProbedDisplayModeToConnector;
    ImportTables[0].VirtualAddress[164] = (uint64_t)DrsdUpdateEdidConnectorProperties;
    ImportTables[0].VirtualAddress[165] = (uint64_t)DrsdGetNewPlaneState;
    ImportTables[0].VirtualAddress[166] = (uint64_t)LouKeDrsdHandleConflictingDevices;
    ImportTables[0].VirtualAddress[167] = (uint64_t)inb;
    ImportTables[0].VirtualAddress[168] = (uint64_t)outb;
    ImportTables[0].VirtualAddress[169] = (uint64_t)LouKeCreateBusClass;
    ImportTables[0].VirtualAddress[170] = (uint64_t)LouKeLoadSubsystem;
    ImportTables[0].VirtualAddress[171] = (uint64_t)LouKeLoadDriver;
    ImportTables[0].VirtualAddress[172] = (uint64_t)LouKeMouseAllocateMessageDevice;
    ImportTables[0].VirtualAddress[173] = (uint64_t)LouKeMouseUpdateInput;
    ImportTables[0].VirtualAddress[174] = (uint64_t)LouKeMallocDma16Ex;
    ImportTables[0].VirtualAddress[175] = (uint64_t)LouKeMallocDma16;
    ImportTables[0].VirtualAddress[176] = (uint64_t)LouKeFreeDma16;
    ImportTables[0].VirtualAddress[177] = (uint64_t)LouKeQueueWork;
    ImportTables[0].VirtualAddress[178] = (uint64_t)LouKeGetAllocationSize;
    ImportTables[0].VirtualAddress[179] = (uint64_t)LouKeGenericAllocateFixedDmaPool;
    ImportTables[0].VirtualAddress[180] = (uint64_t)LouKeFreeFromFixedPool;
    ImportTables[0].VirtualAddress[181] = (uint64_t)LouKeDmiGetFirstMatch;
    ImportTables[0].VirtualAddress[182] = (uint64_t)snprintf;
    ImportTables[0].VirtualAddress[183] = (uint64_t)PciTestAtaConfigurationBits;
    ImportTables[0].VirtualAddress[184] = (uint64_t)LouKeDmiGetFirstMatch;
    ImportTables[0].VirtualAddress[185] = (uint64_t)DmiGetDate;
    ImportTables[0].VirtualAddress[186] = (uint64_t)LouKeMallocExPhy32;
    ImportTables[0].VirtualAddress[187] = (uint64_t)READ_REGISTER_ULONGLONG;
    ImportTables[0].VirtualAddress[188] = (uint64_t)WRITE_REGISTER_ULONGLONG;
    ImportTables[0].VirtualAddress[189] = (uint64_t)LouKeCheckDmiSystem;
    ImportTables[0].VirtualAddress[190] = (uint64_t)LouKeHalGetPciIrqVectorCount;
    ImportTables[0].VirtualAddress[191] = (uint64_t)LouKeMallocPhy32;
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

PVOID 
LouKeGetKulaEmulatedFunctionN(
    string BinaryName, 
    string FunctionName
);

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddressEx(
    string ModuleName,
    string FunctionName,
    PKULA_TRANSITION_LAYER_OBECT TransitionObject
){
    size_t koo = strlen(ModuleName);
    for(size_t foo = 0 ; foo < koo; foo++){
        ModuleName[foo] = toupper(ModuleName[foo]);
    }
    size_t i = 0;
    size_t j = 0;

    //LouPrint("Module:%s Function:%s\n", ModuleName, FunctionName);

    for(i = 0; i < PRE_LOADED_MODULES; i++){

        if((strcmp(ImportTables[i].ModuleName, ModuleName) == 0) && (TransitionObject == 0x00)){
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
        if((strcmp(Tmp->Table.ModuleName, ModuleName) == 0) && (TransitionObject == Tmp->TransitionObject)){
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

    return (UINT64)LouKeGetKulaEmulatedFunctionN(
        ModuleName,
        FunctionName
    );
}

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
){
    return LouKeLinkerGetAddressEx(ModuleName, FunctionName, 0x00);
}

LOUDDK_API_ENTRY
bool 
LouKeLinkerCheckLibraryPresenceEx(string SystemName, PKULA_TRANSITION_LAYER_OBECT TransitionObject){
    
    size_t koo = strlen(SystemName);
    for(size_t foo = 0 ; foo < koo; foo++){
        SystemName[foo] = toupper(SystemName[foo]);
    }
    
    uint8_t i = 0;
    for(i = 0; i < PRE_LOADED_MODULES; i++){

        if((strcmp(ImportTables[i].ModuleName, SystemName) == 0) && (TransitionObject == 0x00)){
            return true;
        }  
    }

    //last resourt but most likely here
    PTableTracks Tmp = (PTableTracks)&DynamicLoadedLibraries; 
    for(uint16_t i = 0 ; i < DynamicLoadedLibrarieCount; i++){
        if((strcmp(Tmp->Table.ModuleName, SystemName) == 0) && (TransitionObject == Tmp->TransitionObject)){
            return true;
        }
        //LouPrint("Module:%s\n",Tmp->Table.ModuleName);
        if(Tmp->Neighbors.NextHeader){
            Tmp = (PTableTracks)Tmp->Neighbors.NextHeader;
        }
    }
    return false;
}

LOUDDK_API_ENTRY
bool 
LouKeLinkerCheckLibraryPresence(string SystemName){
    return LouKeLinkerCheckLibraryPresenceEx(SystemName, 0x00);
}