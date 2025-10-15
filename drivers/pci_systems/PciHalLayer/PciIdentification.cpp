#include <LouDDK.h>
#include <NtAPI.h>
#include <Hal.h>


uint64_t LouKeHalLinuxPciCheckForCompatibleConfiguration(
    PPCI_COMMON_CONFIG PciSearch, 
    PLINUX_PCI_DEVICE_ID LinuxCmpatibleDirectory
) {
    for (uint64_t i = 0; ; i++) {
        if((LinuxCmpatibleDirectory[i].vendor == 0) && (LinuxCmpatibleDirectory[i].device == 0) && 
        (LinuxCmpatibleDirectory[i].subvendor == 0) && (LinuxCmpatibleDirectory[i].subdevice == 0) &&
        (LinuxCmpatibleDirectory[i].Class == 0) && (LinuxCmpatibleDirectory[i].class_mask == 0)){
            return i;
        }
        uint32_t pci_class_code = (PciSearch->Header.BaseClass << 16) | (PciSearch->Header.SubClass << 8) | PciSearch->Header.ProgIf;
        if (((LinuxCmpatibleDirectory[i].vendor != PciSearch->Header.VendorID) && (LinuxCmpatibleDirectory[i].vendor != ANY_PCI_ID)) 
        || ((LinuxCmpatibleDirectory[i].device != PciSearch->Header.DeviceID) && (LinuxCmpatibleDirectory[i].device != ANY_PCI_ID))
        || ((LinuxCmpatibleDirectory[i].subvendor != PciSearch->Header.u.type0.SubVendorID) && (LinuxCmpatibleDirectory[i].subvendor != ANY_PCI_ID))
        || ((LinuxCmpatibleDirectory[i].subdevice != PciSearch->Header.u.type0.SubSystemID) && (LinuxCmpatibleDirectory[i].subdevice != ANY_PCI_ID))
        || (pci_class_code & LinuxCmpatibleDirectory[i].class_mask) != (LinuxCmpatibleDirectory[i].Class & LinuxCmpatibleDirectory[i].class_mask)
        ) {
            continue;
        }

        return i;
    }

    // leave for no compiler error
    return 0;
}

KERNEL_IMPORT size_t GetBootDeviceCount();

UNUSED static void SanityCheck(LPWSTR Str, size_t Length){
    for(size_t i = 0 ; i < Length; i++){
        LouPrint("%c", (char)Str[i]);
    }
    LouPrint("\n");
}

static LPWSTR CreateRegistryEntryFromPciDevice(PPCI_COMMON_CONFIG Config){
    LPWSTR Result;

    UINT16 DeviceID = Config->Header.DeviceID;
    UINT16 VendorID = Config->Header.VendorID;
    UINT16 SubDeviceID = Config->Header.u.type0.SubSystemID;
    UINT16 SubVendorID = Config->Header.u.type0.SubVendorID;
    UINT8 Class = Config->Header.BaseClass;
    UINT8 SubClass = Config->Header.SubClass;
    UINT8 ProgIf = Config->Header.ProgIf;

    WCHAR VendorIDs[8 * sizeof(WCHAR)] = {0};
    WCHAR DeviceIDs[8 * sizeof(WCHAR)] = {0};
    WCHAR SubVendorIDs[8 * sizeof(WCHAR)] = {0};
    WCHAR SubDeviceIDs[8 * sizeof(WCHAR)] = {0};
    WCHAR Classs[8 * sizeof(WCHAR)] = {0};
    WCHAR SubClasss[8 * sizeof(WCHAR)] = {0};
    WCHAR ProgIfs[8 * sizeof(WCHAR)] = {0};


    if((Class == 0x01) && (SubClass == 0x06)){

        VendorIDs[0] = L'\\';
        VendorIDs[1] = L'0';
        VendorIDs[2] = L'x';
        _ui64tow_s(VendorID, &VendorIDs[3], 5 * sizeof(WCHAR),16);

        DeviceIDs[0] = L'\\';
        DeviceIDs[1] = L'0';
        DeviceIDs[2] = L'x';
        _ui64tow_s(DeviceID, &DeviceIDs[3], 5 * sizeof(WCHAR),16);

        SubVendorIDs[0] = L'\\';
        SubVendorIDs[1] = L'0';
        SubVendorIDs[2] = L'x';
        _ui64tow_s(SubVendorID, &SubVendorIDs[3], 5 * sizeof(WCHAR),16);

        SubDeviceIDs[0] = L'\\';
        SubDeviceIDs[1] = L'0';
        SubDeviceIDs[2] = L'x';
        _ui64tow_s(SubDeviceID, &SubDeviceIDs[3], 5 * sizeof(WCHAR),16);


        Classs[0] = L'\\';
        Classs[1] = L'0';
        Classs[2] = L'x';
        _ui64tow_s(Class, &Classs[3], 5 * sizeof(WCHAR),16);

        SubClasss[0] = L'\\';
        SubClasss[1] = L'0';
        SubClasss[2] = L'x';
        _ui64tow_s(SubClass, &SubClasss[3], 5 * sizeof(WCHAR),16);

        ProgIfs[0] = L'\\';
        ProgIfs[1] = L'0';
        ProgIfs[2] = L'x';
        _ui64tow_s(ProgIf, &ProgIfs[3], 5 * sizeof(WCHAR),16);

        Result = LouKeMallocArray(WCHAR, wcslen(L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI") + wcslen(VendorIDs) + wcslen(DeviceIDs) + wcslen(SubVendorIDs) + wcslen(SubDeviceIDs) + wcslen(Classs) + wcslen(SubClasss) + wcslen(ProgIfs) + 1 , KERNEL_GENERIC_MEMORY);

        wcscpy(Result, L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI");
        wcscat(Result, VendorIDs);
        wcscat(Result, DeviceIDs);
        wcscat(Result, SubVendorIDs);
        wcscat(Result, SubDeviceIDs);
        wcscat(Result, Classs);
        wcscat(Result, SubClasss);
        wcscat(Result, ProgIfs);

        return Result;
    }

    return 0x00;
}



size_t LouKePciGetLoadOrderForEntry(
    LPWSTR Entry
){

    PVOID PciKeys = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI", 0x00);
    if(!PciKeys){

        LouPrint("Unable To Open PCI Keys\n");

        return GetBootDeviceCount();
    }

    LouPrint("YAY!!!\n");

    while(1);
    return GetBootDeviceCount();
}

size_t LouKeGetBootDeviceIndex(PPCI_COMMON_CONFIG Config){

    LPWSTR Tmp = CreateRegistryEntryFromPciDevice(Config);

    if(Tmp){
        size_t Result = LouKePciGetLoadOrderForEntry(Tmp);

        LouPrint("LoadOrder:%d\n", Result);

        while(1);
    }

    return GetBootDeviceCount();
}