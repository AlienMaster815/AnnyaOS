//Tyler Grenier - DevMan.c :: Lousine Kernel:PCI.SYS :: (C) 2026 GPL2

//Developer Notes:

#include "Pci.h"

static PCI_MANAGER_DATA PciData = {0};
static size_t RegisteredPciDevices = 0;
static mutex_t PciDataLock = {0};
static mutex_t PciTmpGenericLock = {0};

//TODO Implement Registry loopkup

static WCHAR PciTmpGeneric[80] = {0};

/*static void SanityCheckString(LPWSTR String){
    for(size_t i = 0 ; i < wcslen(String); i++){
        LouPrint("%c", (CHAR)String[i]);
    }
    LouPrint("\n");
}*/

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
            break;
        case 0x01: //PCI Bridges Dont Have Subvendors
            Tmp->SubVendorID = PciHalGetVendorId(PDEV);
            Tmp->SubSystemID = PciHalGetDeviceId(PDEV);
            break;
        case 0x02:
            Tmp->SubVendorID = PciHalCardBusDeviceGetSubsystemVendorId(PDEV);    
            Tmp->SubSystemID = PciHalCardBusDeviceGetSubsystemDeviceId(PDEV);    
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


    PciHalPciDbgPrint("PCI.SYS:Registered Pci Device:%d\n", RegisteredPciDevices);
    PciHalPciDbgPrint("PCI.SYS:VendorID:%h ::  DeviceID:%h\n", (UINT64)Tmp->VendorID, (UINT64)Tmp->DeviceID);
    PciHalPciDbgPrint("PCI.SYS:PCI BUS:%d  ::  SLOT:%d  ::  FUNC:%d\n", (UINT64)PDEV->Bus, (UINT64)PDEV->Slot, (UINT64)PDEV->Function);

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

DRIVER_EXPORT LOUSTATUS PciHalScanBootDevices(){


    PciHalPciDbgPrint("PCI.SYS:PciHalScanBootDevices()\n");

    PPCI_MANAGER_DATA TmpObject;
    MutexLock(&PciDataLock);
    ForEachListEntry(TmpObject, &PciData.Peers, Peers){
        PVOID BootDriver = PciHalWalkPnpTree(TmpObject->DeviceManagerName);
        if(!BootDriver){
            continue;
        }
        //cross locking

        LouPrint("PCI.SYS:HERE\n");
        while(1);
    }
    MutexUnlock(&PciDataLock);

    PciHalPciDbgPrint("PCI.SYS:PciHalScanBootDevices() STATUS_SUCCESS\n");
    while(1);
    return STATUS_SUCCESS;
}