//Copyright GPL-2 Tyler Grenier (2023 - 2026)
#include <LouDDK.h>
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
    LIST_LINK                       Peers;
    TABLE_ENTRY                     Table;
    bool                            LongModeEntry;
    PKULA_TRANSITION_LAYER_OBECT    TransitionObject;
    KERNEL_REFERENCE                Counter;
}TableTracks, * PTableTracks;

static LIST_OBJECT DynamicLoadedLibraries = {0};
static size_t DynamicLoadedLibrarieCount = 0x00;

LOUAPI LOUSTATUS LouKePassVramToDrsdMemoryManager(PDRSD_DEVICE Device, void* VramBase, size_t size, void* PAddress);

ULONG KeNumberProcessors();

//define JITL Section data
#define CURRENT_JITLS   1

//Jitl list
//extern SECTIONED_CODE(".JitlDirectory") JITL_DIRECTORY AhciJitlDirectory;

static PJITL_DIRECTORY SystemSections[CURRENT_JITLS];

LOUAPI char* Winstrcpy(char* dest, const char* src);
LOUAPI char* Winstrcat(char* dest, const char* src);

LOUAPI
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

LOUAPI
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

LOUAPI
ULONG
vDbgPrintEx(
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
);

LOUAPI
ULONG
vDbgPrintExWithPrefix (
    PCCH Prefix,
    ULONG ComponentId,
    ULONG Level,
    PCCH Format,
    va_list args
);


LOUAPI
LOUSTATUS
NtAddAtom(
    PWSTR       AtomName,
    ULONG       Length,
    PRTL_ATOM   Atom
);

LOUAPI
LOUSTATUS
NtAddAtomEx(
    PWSTR AtomName,
    ULONG Length,
    PRTL_ATOM Atom,
    ULONG Flags
);

LOUSTATUS NtAdjustPrivilegesToken(
    HANDLE TokenHandle,
    bool DisableAllPrivaledges,
    PTOKEN_PRIVALEDGES NewState,
    ULONG BufferLength,
    PTOKEN_PRIVALEDGES PreviousState,
    PULONG ReturnLength
);

LOUAPI
LOUSTATUS
NtAllocateLocallyUniqueId(
    PLUID Luid
);

LOUAPI
LOUSTATUS
NtAllocateUuids(
    PULARGE_INTEGER Time,
    PULONG Range,
    PULONG Sequnce,
    PCHAR Seed
);

LOUAPI
int toupper(int c);

LOUAPI
void LouKeInitializeLibraryLookupEx(
    string                          ModuleName,
    uint32_t                        NumberOfFunctions,
    string*                         FunctionNames,
    uint64_t*                       FunctionAddresses,
    bool                            IsNativeLongmode,
    PKULA_TRANSITION_LAYER_OBECT    TransitionObject
){
    //&DynamicLoadedLibraries;
    PTableTracks Tmp = LouKeMallocType(TableTracks, KERNEL_GENERIC_MEMORY);
    LouKeLinkObjectToListTail(&DynamicLoadedLibraries, &Tmp->Peers);
    
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

LOUAPI
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

LOUAPI uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

LOUAPI void* LouKePciGetIoRegion(
    PPCI_DEVICE_OBJECT PDEV, 
    uint8_t BarNumber,
    size_t BarOffset
);

static inline 
void InitializeLousineKernelTables(){
    
}

LOUAPI
int vswprintf_s(
    wchar_t* Buffer,
    size_t BufferCount,
    wchar_t* Format,
    va_list Args
);

LOUAPI
int vsprintf_s(
    string Buffer,
    size_t BufferCount,
    string Format,
    va_list Args
);

LOUAPI
wchar_t towupper(wchar_t wc);

LOUAPI
wchar_t towlower(wchar_t wc);

LOUAPI
int tolower(int c);



static inline
void InitializeNtKernelTable(){


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

LOUSTATUS StorPortInitialize(
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

LOUSTATUS StorPortGetBusData(
  PVOID HwDeviceExtension,
  ULONG BusDataType,
  ULONG SystemIoBusNumber,
  ULONG SlotNumber,
  PVOID Buffer,
  ULONG Length
);

void InitializeJitlTables(){
    //Ahci Function
    //SystemSections[0] = &AhciJitlDirectory;
}


PVOID 
LouKeGetKulaEmulatedFunctionN(
    string BinaryName, 
    string FunctionName
);

struct _TableTrackFinderParams{
    PVOID ModuleName;
    PVOID TransitionObject;
};

static BOOL FindModuleTracker(PLIST_LINK Link, PVOID Params){
    struct _TableTrackFinderParams* Foo = (struct _TableTrackFinderParams*)Params;
    PTableTracks Tmp = CONTAINER_OF(Link, TableTracks, Peers);
    
    if((strcmp(Tmp->Table.ModuleName, (string)Foo->ModuleName) == 0) && (Foo->TransitionObject == Tmp->TransitionObject)){
        return true;
    }
    return false;
}

LOUAPI uint64_t LouKeLinkerGetAddressEx(
    string ModuleName,
    string FunctionName,
    PKULA_TRANSITION_LAYER_OBECT TransitionObject
){

    //LouPrint("Module:%s Function:%s\n", ModuleName, FunctionName);

    struct _TableTrackFinderParams Foo = {.ModuleName = ModuleName, .TransitionObject = TransitionObject};

    PTableTracks Tmp = (PTableTracks)LouKeLinkGetMemberWithFunction(&DynamicLoadedLibraries, FindModuleTracker, &Foo);
    
    if(!Tmp){
        return 0x00;
    }
    //if((strcmp(Tmp->Table.ModuleName, ModuleName) == 0) && (TransitionObject == Tmp->TransitionObject)){
        for(size_t j = 0 ; j < Tmp->Table.NumberOfFunctions; j++){
            if(strcmp(Tmp->Table.FunctionName[j], FunctionName) == 0){
                //LouPrint("Getting A Address From Loaded Module:%s\n",   Tmp->Table.FunctionName[j]);
                //LouPrint("Getting A Address From Loaded Address:%h\n",  Tmp->Table.VirtualAddress[j]);
                //LouPrint("::%h : 3\n", Tmp->Table.VirtualAddress[j]);
                return Tmp->Table.VirtualAddress[j];
            }
        }
    //}

    return (UINT64)LouKeGetKulaEmulatedFunctionN(
        ModuleName,
        FunctionName
    );
}

LOUAPI HANDLE LouKeLinkerGetModuleLookupHandleEx(
    string ModuleName,
    PKULA_TRANSITION_LAYER_OBECT TransitionObject
){
    
    if(!ModuleName){
        return 0x00;
    }
    struct _TableTrackFinderParams Foo = {.ModuleName = ModuleName, .TransitionObject = TransitionObject};
  
    PTableTracks Tmp = (PTableTracks)LouKeLinkGetMemberWithFunction(&DynamicLoadedLibraries, FindModuleTracker, &Foo);
    if(!Tmp){
        return 0x00;
    }

    return (HANDLE)&Tmp->Table;
}

LOUAPI HANDLE LouKeLinkerGetModuleLookupHandle(
    string ModuleName
){
    return LouKeLinkerGetModuleLookupHandleEx(ModuleName, 0x00);
}

LOUAPI uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
){
    return LouKeLinkerGetAddressEx(ModuleName, FunctionName, 0x00);
}

LOUAPI
bool 
LouKeLinkerCheckLibraryPresenceEx(string SystemName, PKULA_TRANSITION_LAYER_OBECT TransitionObject){
    
    size_t koo = strlen(SystemName);
    for(size_t foo = 0 ; foo < koo; foo++){
        SystemName[foo] = toupper(SystemName[foo]);
    }
    
    return LouKeLinkerGetModuleLookupHandleEx(SystemName, TransitionObject) ? true : false;
}

LOUAPI
bool 
LouKeLinkerCheckLibraryPresence(string SystemName){
    return LouKeLinkerCheckLibraryPresenceEx(SystemName, 0x00);
}