#include "Pci.h"

static PCI_MANAGER_DATA PciData = {0};
static size_t RegisteredPciDevices = 0;
static mutex_t PciDataLock = {0};
static mutex_t PciTmpGenericLock = {0};

//TODO Implement Registry loopkup

static const LPWSTR PciGenericString = L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI\\0xFFFF\\0xFFFF\\0xFFFF\\0xFFFF\\0xFF\\0xFF\\0xFF"; 
static WCHAR PciTmpGeneric[80] = {0};

static void SanityCheck(LPWSTR Foo){
    SIZE Len = wcslen(Foo);
    PciHalPciDbgPrint("New Pci/e Device:");
    for(SIZE i = 0 ; i < Len; i++){
        PciHalPciDbgPrint("%c", (CHAR)Foo[i]);
    }
    PciHalPciDbgPrint("\n");
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
    _ui64tow(Tmp->VendorID, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    //device
    _ui64tow(Tmp->DeviceID, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    //SubVendor
    _ui64tow(Tmp->SubVendorID, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    //SubSystem
    _ui64tow(Tmp->SubSystemID, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    _ui64tow(Tmp->ClassCode, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    _ui64tow(Tmp->SubClass, TmpValue, 16);
    wcscat(PciTmpGeneric, L"0x");
    wcscat(PciTmpGeneric, TmpValue);
    wcscat(PciTmpGeneric, L"\\");

    wcscat(PciTmpGeneric, L"0x");
    _ui64tow(Tmp->ProgIf, TmpValue, 16);
    wcscat(PciTmpGeneric, TmpValue);
    
    SanityCheck(PciTmpGeneric);

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