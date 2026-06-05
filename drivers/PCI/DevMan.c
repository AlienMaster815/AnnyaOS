//Tyler Grenier - DevMan.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

#define DEVICE_TABLE_TERMINATOR (DeviceTable[DeviceNumber].VendorID == 0x00) && (DeviceTable[DeviceNumber].DeviceID == 0x00) && (DeviceTable[DeviceNumber].GenericEntry == false)
#define ANY_PCI_CLASS 255

DRIVER_MODULE_ENTRY LouKeLoadBootKernelModule(uintptr_t Base, void** DriverObject, size_t DriverObjectSize);

static PCI_MANAGER_DATA PciData = {0};
static size_t RegisteredPciDevices = 0;
static mutex_t PciDataLock = {0};
static mutex_t PciTmpGenericLock = {0};
static ListHeader PciLoadedModules = {0};
static mutex_t PciLoadedModulesLock = {0};

//TODO Implement Registry loopkup

static WCHAR PciTmpGeneric[80] = {0};

/*static void SanityCheckString(LPWSTR String){
    for(size_t i = 0 ; i < wcslen(String); i++){
        LouPrint("%c", (CHAR)String[i]);
    }
    LouPrint("\n");
}*/

static HANDLE PciHalGetNextSpecificKey(
    LPWSTR  StartSearch,
    HANDLE  ParrentKey   
){
    WCHAR   TmpSearch[8] = {0};
    LPWSTR  EndSeach = wcschr(StartSearch, L'\\');
    SIZE    Length = wcslen(StartSearch);
    if(EndSeach){
        Length = EndSeach - StartSearch;
    }
    wcscpy_s(TmpSearch, Length, StartSearch);
    return LouKeOpenRegistryHandle(TmpSearch, ParrentKey);
}

static HANDLE PciHalGetNextGenericUint16Key(
    HANDLE ParrentKey
){
    return LouKeOpenRegistryHandle(L"0xFFFF", ParrentKey);   
}

static HANDLE PciHalGetNextGenericUint8Key(
    HANDLE ParrentKey
){
    return LouKeOpenRegistryHandle(L"0xFF", ParrentKey);   
}


static HANDLE PciHalWalkPnpIds(
    LPWSTR  PnpString, 
    HANDLE  ParrentKey,
    SIZE    Recursion
){
    //SanityCheckString(PnpString);
    HANDLE ReturnKey = (HANDLE)0x00;
    HANDLE DownKey = PciHalGetNextSpecificKey(PnpString, ParrentKey);
    if(DownKey && Recursion < 3){
        ReturnKey = PciHalWalkPnpIds(
            wcschr(PnpString, L'\\') + 1, 
            DownKey,
            Recursion + 1
        );
    }else if(Recursion == 3){
        ReturnKey = DownKey;
    }
    if(!ReturnKey){
        DownKey = PciHalGetNextGenericUint16Key(ParrentKey);
        if(DownKey && Recursion < 3){
            ReturnKey = PciHalWalkPnpIds(
                wcschr(PnpString, L'\\') + 1,
                DownKey,
                Recursion + 1 
            );
        }else if(Recursion == 3){
            ReturnKey = DownKey;
        }
    }
    return ReturnKey;
}

static HANDLE PciHalWalkPnpCodes(
    LPWSTR  PnpString, 
    HANDLE  ParrentKey,
    SIZE    Recursion
){
    //SanityCheckString(PnpString);
    HANDLE ReturnKey = (HANDLE)0x00;
    HANDLE DownKey = PciHalGetNextSpecificKey(PnpString, ParrentKey);
    if(DownKey && Recursion < 2){
        ReturnKey = PciHalWalkPnpCodes(
            wcschr(PnpString, L'\\') + 1, 
            DownKey,
            Recursion + 1
        );
    }else if(Recursion == 2){
        ReturnKey = DownKey;
    }
    if(!ReturnKey){
        DownKey = PciHalGetNextGenericUint8Key(ParrentKey);
        if(DownKey && Recursion < 2){
            ReturnKey = PciHalWalkPnpCodes(
                wcschr(PnpString, L'\\') + 1,
                DownKey,
                Recursion + 1 
            );
        }else if(Recursion == 2){
            ReturnKey = DownKey;
        }
    }
    return ReturnKey;
}


static PVOID PciHalWalkPnpTree(
    LPWSTR DeviceManagerName
){
    LPWSTR Tmp = DeviceManagerName; 
    LPWSTR Tmp2;
    Tmp = wcsstr(Tmp, L"PCI");
    if(!Tmp){
        return 0x00;
    }
    Tmp += wcslen(L"PCI\\");;
    HANDLE Key = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI", 0x00);
    if(!Key){
        return 0x00;
    }
    
    //TODO
    //SanityCheckString(DeviceManagerName);
    
    Key = PciHalWalkPnpIds(Tmp, Key, 0);
    if(!Key){
        return 0x00;
    }

    for(size_t i = 0; i < 4; i++){
        Tmp = wcschr(Tmp, L'\\');
        if(!Tmp){
            return 0;
        }
        Tmp++;
    }

    return PciHalWalkPnpCodes(Tmp, Key, 0);
}

LOUSTATUS PciHalRegisterPciDevice(PPCI_DEVICE_OBJECT PDEV){

    PPCI_MANAGER_DATA Tmp = LouKeMallocType(PCI_MANAGER_DATA, KERNEL_GENERIC_MEMORY);
    Tmp->PDEV = PDEV;    
    Tmp->VendorID = PciHalGetVendorId(PDEV);
    Tmp->DeviceID = PciHalGetDeviceId(PDEV);
    Tmp->ClassCode = PciHalGetClassCode(PDEV);
    Tmp->SubClass = PciHalGetSubClass(PDEV);
    Tmp->ProgIf = PciHalGetProgIf(PDEV);

    PDEV->MangerData = Tmp;
    
    PDEV->CommonConfig = LouKeAllocateFastObject("PCICONFIG");
    PciHalGetConfigurationSnapshot(PDEV, PDEV->CommonConfig);

    UINT8 DeviceType = PciHalGetHeaderType(PDEV) & 0x03;

    switch(DeviceType){
        case 0x00:
            Tmp->SubVendorID = PciHalGeneralDeviceGetSubsystemVendorId(PDEV);
            Tmp->SubSystemID = PciHalGeneralDeviceGetSubsystemId(PDEV);
            PDEV->InterruptPin = PciHalGeneralDeviceGetInterruptPin(PDEV);
            break;
        case 0x01: //PCI Bridges Dont Have Subvendors
            Tmp->SubVendorID = PciHalGetVendorId(PDEV);
            Tmp->SubSystemID = PciHalGetDeviceId(PDEV);
            PDEV->InterruptPin = PciHalBridgeDeviceGetInterruptPin(PDEV);
            break;
        case 0x02:
            Tmp->SubVendorID = PciHalCardBusDeviceGetSubsystemVendorId(PDEV);    
            Tmp->SubSystemID = PciHalCardBusDeviceGetSubsystemDeviceId(PDEV); 
            PDEV->InterruptPin = PciHalCardBusDeviceGetInterruptPin(PDEV);   
            break;   
        default:
            LouPrint("PCI.SYS:ERROR:PciHalRegisterPciDevice():Unkown Device Type:%h\n", (UINT64)DeviceType);
            break;
    }



    MutexLock(&PciDataLock);
    LouKeListAddTail(&Tmp->Peers, &PciData.Peers);
    RegisteredPciDevices++;
    MutexUnlock(&PciDataLock);

    MutexLock(&PciTmpGenericLock);
    WCHAR TmpValue[8] = {0};
    wcscpy(PciTmpGeneric, L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI\\");
    
    //vendor
    _ui64tow((UINT64)Tmp->VendorID, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    //device
    _ui64tow((UINT64)Tmp->DeviceID, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    //SubVendor
    _ui64tow((UINT64)Tmp->SubVendorID, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    //SubSystem
    _ui64tow((UINT64)Tmp->SubSystemID, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    _ui64tow((UINT64)Tmp->ClassCode, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    _ui64tow((UINT64)Tmp->SubClass, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    wcscat(PciTmpGeneric, L"0x");
    _ui64tow((UINT64)Tmp->ProgIf, TmpValue, 16);
    _wcsupr(TmpValue);
    wcscat(PciTmpGeneric, TmpValue);
    memset(TmpValue, 0, sizeof(WCHAR) * 8);

    Tmp->DeviceManagerName = LouKeMallocArray(WCHAR, wcslen(PciTmpGeneric) + 1, KERNEL_GENERIC_MEMORY);
    
    wcscpy(Tmp->DeviceManagerName, PciTmpGeneric);

    memset(PciTmpGeneric, 0, wcslen(PciTmpGeneric) * sizeof(WCHAR));

    MutexUnlock(&PciTmpGenericLock);


    PciHalDbgPrint("PCI.SYS:Registered Pci Device:%d\n", RegisteredPciDevices);
    PciHalDbgPrint("PCI.SYS:VendorID:%h ::  DeviceID:%h\n", (UINT64)Tmp->VendorID, (UINT64)Tmp->DeviceID);
    PciHalDbgPrint("PCI.SYS:PCI BUS:%d  ::  SLOT:%d  ::  FUNC:%d\n", (UINT64)PDEV->Bus, (UINT64)PDEV->Slot, (UINT64)PDEV->Function);

    return STATUS_SUCCESS;
}

PPCI_MANAGER_DATA PciHalGetPciDataTable(){
    return (PPCI_MANAGER_DATA)&PciData;
}

uint8_t PciHalGetPciGlobalMembers(){
    return RegisteredPciDevices;
}

DRIVER_EXPORT PPCI_DEVICE_OBJECT PciHalGetDeviceFromBusAddress(
    UINT16  Group,
    UINT8   Bus,
    UINT8   Slot,
    UINT8   Function
){
    PPCI_MANAGER_DATA TmpObject;
    MutexLock(&PciDataLock);
    ForEachListEntry(TmpObject, &PciData.Peers, Peers){
        PPCI_DEVICE_OBJECT PDEV = TmpObject->PDEV;
        if(
            (PDEV->Group == Group) &&
            (PDEV->Bus == Bus) &&
            (PDEV->Slot == Slot) &&
            (PDEV->Function == Function)
        ){
            MutexUnlock(&PciDataLock);
            return PDEV;
        }
    }
    MutexUnlock(&PciDataLock);
    return 0x00;
}

PLOADED_PCI_MODULE PciHalGetLoadedPciModule(
    LPWSTR RegistryEntry
){
    PLOADED_PCI_MODULE TmpModule;
    MutexLock(&PciLoadedModulesLock);
    ForEachListEntry(TmpModule, &PciLoadedModules, Peers){
        LPWSTR TmpRegistryEntry = TmpModule->RegistryEntry.Buffer;
        if(!wcscmp(RegistryEntry, TmpRegistryEntry)){
            MutexUnlock(&PciLoadedModulesLock);
            return TmpModule;
        }
    }
    MutexUnlock(&PciLoadedModulesLock);
    return 0x00;
}

PLOADED_PCI_MODULE PciHalGetLoadedPciModuleObjectFromDriverObject(
    PDRIVER_OBJECT  DriverObject
){
    PLOADED_PCI_MODULE TmpModule;
    MutexLock(&PciLoadedModulesLock);
    ForEachListEntry(TmpModule, &PciLoadedModules, Peers){
        if(TmpModule->DriverObject == DriverObject){
            MutexUnlock(&PciLoadedModulesLock);
            return TmpModule;
        }
    }
    MutexUnlock(&PciLoadedModulesLock);
    return 0x00;
}

PLOADED_PCI_MODULE PciHalLoadAndInitializePciModule(
    LPWSTR  RegistryEntry,
    BOOLEAN OnlyLoadBootModules
){
    
    DRIVER_MODULE_ENTRY Driver;
    PLOADED_PCI_MODULE NewModule = PciHalGetLoadedPciModule(RegistryEntry);
    if(NewModule){
        return NewModule;
    }
    HANDLE RegistryHandle = LouKeOpenRegistryHandle(RegistryEntry, 0);
    HANDLE LoadOrderKeyHandle = LouKeOpenRegistryHandle(L"LoadOrder", RegistryHandle);
    
    if(!RegistryHandle){
        LouPrint("PCI.SYS:ERROR:Unable To Get Devices Registry Handle\n");
        return 0x00;
    }
    if(OnlyLoadBootModules && !LoadOrderKeyHandle){
        return 0x00;
    }

    //TODO use Rtl
    NewModule = LouKeMallocType(LOADED_PCI_MODULE, KERNEL_GENERIC_MEMORY);
    //Regisry Entry Path
    NewModule->RegistryEntry.Length = wcslen(RegistryEntry);
    NewModule->RegistryEntry.MaximumLength = NewModule->RegistryEntry.Length;
    NewModule->RegistryEntry.Buffer = RegistryEntry;

    //Registry Entry Handle    
    NewModule->RegistryHandle = RegistryHandle;
    if(!LoadOrderKeyHandle){
        /*NewModule->BootModule = false;
        NewModule->LoadOrder = 0;
        HANDLE DeviceNameHandle = LouKeOpenRegistryHandle(L"DeviceName", RegistryHandle);
        SIZE StringLength = LouKeGetRegistryKeySize(DeviceNameHandle);
        LPWSTR wDevName = LouKeMallocArray(WCHAR, StringLength + 1, KERNEL_GENERIC_MEMORY);
        string cDevName = LouKeMallocArray(CHAR, StringLength + 1, KERNEL_GENERIC_MEMORY);
        LouKeReadRegistryWcsValue(DeviceNameHandle, wDevName);
        for(SIZE i = 0 ; i <  StringLength; i++){
            cDevName[i] = (CHAR)wDevName[i];
        }
        LouKeFree(wDevName);
        Driver = LouKeLoadKernelModule(cDevName, (PVOID*)&NewModule->DriverObject, sizeof(DRIVER_OBJECT));
        LouKeFree(cDevName);*/
        LouPrint("PCI.SYS:!LoadOrderKeyHandle\n");
        while(1);
    }else{
        NewModule->BootModule = true;
        LouKeReadRegistryWordValue(LoadOrderKeyHandle, &NewModule->LoadOrder);
        NewModule->DriverFile = LouKeGetBootDevice(NewModule->LoadOrder);
        Driver = LouKeLoadBootKernelModule((uintptr_t)NewModule->DriverFile, (PVOID*)&NewModule->DriverObject, sizeof(DRIVER_OBJECT));
    }

    MutexLock(&PciLoadedModulesLock);
    LouKeListAddTail(&NewModule->Peers, &PciLoadedModules);
    MutexUnlock(&PciLoadedModulesLock);

    if(!NewModule->DriverObject->DriverExtension){
        NewModule->DriverObject->DriverExtension = LouKeMallocType(DRIVER_EXTENSION,  KERNEL_GENERIC_MEMORY);
        if(Driver(NewModule->DriverObject, (PUNICODE_STRING)&NewModule->RegistryEntry) != STATUS_SUCCESS){
            LouPrint("PSI.SYS:PciHalLoadAndInitializePciModule():ERROR");
            while(1);
        }
    }

    NewModule->DriverEntry = Driver;

    return NewModule;
}


uint64_t PciHalGetDeviceListIdEx(PPCI_COMMON_CONFIG Config, PLOUSINE_PCI_DEVICE_TABLE DeviceTable){

    UNUSED uint16_t DeviceID, VendorID, SubVendorID, SubDeviceID;
    UNUSED uint8_t BaseClass, SubClass, ProgIf;

    DeviceID = Config->Header.DeviceID;
    VendorID = Config->Header.VendorID;
    SubDeviceID = Config->Header.Type0.SubSystemID;
    SubVendorID = Config->Header.Type0.SubVendorID;

    BaseClass = Config->Header.BaseClass;
    SubClass = Config->Header.SubClass;
    ProgIf = Config->Header.ProgIf;

    uint64_t DeviceNumber = 0;

    while(1){   

        if(
            ((DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS) && 
                (DeviceTable[DeviceNumber].ProgIf == ProgIf || DeviceTable[DeviceNumber].ProgIf == ANY_PCI_CLASS)
            ) || 
            (
                (DeviceTable[DeviceNumber].SimpleEntry) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID)
            ) ||
            (
                (DeviceTable[DeviceNumber].SimpleWithClass) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) && 
                (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS)
            ) ||  
            (
                (DeviceTable[DeviceNumber].AdvancedEntry) && 
                (DeviceTable[DeviceNumber].DeviceID == DeviceID || DeviceTable[DeviceNumber].DeviceID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].VendorID == VendorID || DeviceTable[DeviceNumber].VendorID == ANY_PCI_ID) && 
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID) &&
                (DeviceTable[DeviceNumber].SubVendorID == VendorID || DeviceTable[DeviceNumber].SubVendorID == ANY_PCI_ID)
            ) || 
            (
                (DeviceTable[DeviceNumber].GenericEntry) && 
                (DeviceTable[DeviceNumber].BaseClass == BaseClass || DeviceTable[DeviceNumber].BaseClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].SubClass == SubClass || DeviceTable[DeviceNumber].SubClass == ANY_PCI_CLASS) &&
                (DeviceTable[DeviceNumber].ProgIf == ProgIf || DeviceTable[DeviceNumber].ProgIf == ANY_PCI_CLASS)
            )
        ){
            return DeviceNumber;
        }

        if(DEVICE_TABLE_TERMINATOR){
            return (uint64_t)-1;
        }
        DeviceNumber++;
    }
}

LOUSTATUS PciHalGetDeviceListId(
    PLOADED_PCI_MODULE  Module,
    PPCI_DEVICE_OBJECT  PDEV,
    SIZE*               DeviceID
){
    if(!PDEV->CommonConfig || !Module->DeviceTable){
        LouPrint("PCI.SYS:PciHalGetDeviceListId():ERROR:\n");
        if(!PDEV->CommonConfig){
            LouPrint("No Config\n");
        }
        if(!Module->DeviceTable){
            LouPrint("No Table\n");
        }
        return STATUS_INVALID_PARAMETER;
    }
    *DeviceID = PciHalGetDeviceListIdEx(PDEV->CommonConfig, Module->DeviceTable);
    if(*DeviceID == (UINT64)-1){
        return STATUS_INVALID_PARAMETER;
    }
    return STATUS_SUCCESS;
}

LOUSTATUS PciHalInitializePciDeviceToDriver(
    PLOADED_PCI_MODULE Module,
    PPCI_DEVICE_OBJECT PDEV
){  
    SIZE DeviceID = 0x00;
    LOUSTATUS Status = PciHalGetDeviceListId(Module, PDEV, &DeviceID);
    if(Status != STATUS_SUCCESS){
        LouPrint("PCI.SYS:ERROR Unable To Get Devices ID\n");
        return Status;
    }
    PDEV->DeviceID = DeviceID;
    PPCI_DEVICE_GROUP PGROUP = LouKeMallocType(PCI_DEVICE_GROUP, KERNEL_GENERIC_MEMORY);
    PGROUP->PciDeviceobject = PDEV;
    //TODO:use Rtl Function
    PGROUP->DeviceName.Buffer = PDEV->MangerData->DeviceManagerName;
    PGROUP->DeviceName.Length = wcslen(PDEV->MangerData->DeviceManagerName); 
    PGROUP->DeviceName.MaximumLength = PGROUP->DeviceName.Length;
    

    MutexLock(&Module->UninitializedDeviceGroupLock);
    LouKeListAddTail(&PGROUP->Peers, &Module->UninitializedDeviceGroup);
    MutexUnlock(&Module->UninitializedDeviceGroupLock);

    return STATUS_SUCCESS;
}

LOUSTATUS PciHalInitializeUninitializedDevices(
    PLOADED_PCI_MODULE Module
){
    ListHeader TmpList = {0};
    PPCI_DEVICE_GROUP TmpUninitializedDevice;
    if(!Module->DriverObject->DriverExtension->AddDevice){
        return STATUS_UNSUCCESSFUL;
    }
    MutexLock(&Module->UninitializedDeviceGroupLock);
    
    TmpList = Module->UninitializedDeviceGroup;
    LouKeListDeleteAll(&Module->UninitializedDeviceGroup);
    
    MutexUnlock(&Module->UninitializedDeviceGroupLock);
    
    LOUSTATUS Status;
    MutexLock(&Module->InitializedDeviceGroupLock);
    ForEachListEntry(TmpUninitializedDevice, &TmpList, Peers){
        Status = Module->DriverObject->DriverExtension->AddDevice(Module->DriverObject, &TmpUninitializedDevice->LdmDeviceObject);    
        if(!NT_SUCCESS(Status)){
            MutexUnlock(&Module->InitializedDeviceGroupLock);
            return Status;
        }
        LouKeListAddTail(&TmpUninitializedDevice->Peers, &Module->InitializedDeviceGroup);
    }
    MutexUnlock(&Module->InitializedDeviceGroupLock);
    return STATUS_SUCCESS;
}

LOUSTATUS PciHalInitializeAllUninitializedDevices(){
    PLOADED_PCI_MODULE TmpModule;
    LOUSTATUS Status;
    MutexLock(&PciLoadedModulesLock);
    ForEachListEntry(TmpModule, &PciLoadedModules, Peers){
        Status = PciHalInitializeUninitializedDevices(TmpModule);
        if(!NT_SUCCESS(Status)){
            return Status;
        }
    }
    MutexUnlock(&PciLoadedModulesLock);
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalScanBootDevices(){


    PciHalDbgPrint("PCI.SYS:PciHalScanBootDevices()\n");

    PPCI_MANAGER_DATA TmpObject;
    MutexLock(&PciDataLock);
    ForEachListEntry(TmpObject, &PciData.Peers, Peers){
        PVOID BootDriver = PciHalWalkPnpTree(TmpObject->DeviceManagerName);
        if(!BootDriver){
            continue;
        }
        HANDLE DriverKeyHandle = LouKeOpenRegistryHandle(L"DriverKey", BootDriver);
        SIZE KeySize = LouKeGetRegistryKeySize(DriverKeyHandle);
        LPWSTR RegistryKey = LouKeMallocArray(WCHAR, KeySize + 1, KERNEL_GENERIC_MEMORY);
        LouKeReadRegistryWcsValue(DriverKeyHandle, RegistryKey);
        PLOADED_PCI_MODULE NewBootModule = PciHalLoadAndInitializePciModule(RegistryKey, true);
        if(!NewBootModule){
            LouKeFree(RegistryKey);
            continue;
        }

        PciHalInitializePciDeviceToDriver(NewBootModule, TmpObject->PDEV);

    }
    MutexUnlock(&PciDataLock);

    PciHalInitializeAllUninitializedDevices();

    PciHalDbgPrint("PCI.SYS:PciHalScanBootDevices() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

DRIVER_EXPORT LOUSTATUS PciHalRegisterLousinePciDeviceTable(
    PDRIVER_OBJECT              DriverObject,
    PLOUSINE_PCI_DEVICE_TABLE   DeviceTable
){
    PLOADED_PCI_MODULE Module = PciHalGetLoadedPciModuleObjectFromDriverObject(DriverObject);
    if(!Module){
        LouPrint("PCI.SYS:PciHalRegisterLousinePciDeviceTable():ERROR Module Doesnt Exist\n");
        return STATUS_INVALID_PARAMETER;
    }
    if(Module->DeviceTable){
        LouPrint("PCI.SYS:PciHalRegisterLousinePciDeviceTable():ERROR Table Already Exist\n");
        return STATUS_UNSUCCESSFUL;
    }
    Module->DeviceTable = DeviceTable;
    return STATUS_SUCCESS;
}

DRIVER_EXPORT PPCI_DEVICE_OBJECT PciHalGetPciDeviceObjectFromLdmDeviceObject(
    PDEVICE_OBJECT DeviceObject
){
    return (CONTAINER_OF(DeviceObject, PCI_DEVICE_GROUP, LdmDeviceObject))->PciDeviceobject;
}