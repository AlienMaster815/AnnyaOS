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
    //for(size_t i = 0 ; i < Length; i++){
    //    LouPrint("%c", (char)Str[i]);
    //}
    //LouPrint("\n");
}

static void CreateRegistryEntryFromPciDevice(
    PPCI_COMMON_CONFIG Config,
    LPWSTR* WcsVendorID, LPWSTR* WcsDeviceID,
    LPWSTR* WcsSubVendorID, LPWSTR* WcsSubDeviceID,
    LPWSTR* WcsClassID, LPWSTR* WcsSubClassID,
    LPWSTR* WcsProgIf
){
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

        VendorIDs[0] = L'0';
        VendorIDs[1] = L'x';
        _ui64towUppr_s(VendorID, &VendorIDs[2], 5 * sizeof(WCHAR),16);

        DeviceIDs[0] = L'0';
        DeviceIDs[1] = L'x';
        _ui64towUppr_s(DeviceID, &DeviceIDs[2], 5 * sizeof(WCHAR),16);

        SubVendorIDs[0] = L'0';
        SubVendorIDs[1] = L'x';
        _ui64towUppr_s(SubVendorID, &SubVendorIDs[2], 5 * sizeof(WCHAR),16);

        SubDeviceIDs[0] = L'0';
        SubDeviceIDs[1] = L'x';
        _ui64towUppr_s(SubDeviceID, &SubDeviceIDs[2], 5 * sizeof(WCHAR),16);


        Classs[0] = L'0';
        Classs[1] = L'x';
        _ui64towUppr_s(Class, &Classs[2], 5 * sizeof(WCHAR),16);

        SubClasss[0] = L'0';
        SubClasss[1] = L'x';
        _ui64towUppr_s(SubClass, &SubClasss[2], 5 * sizeof(WCHAR),16);

        ProgIfs[0] = L'0';
        ProgIfs[1] = L'x';
        _ui64towUppr_s(ProgIf, &ProgIfs[2], 5 * sizeof(WCHAR),16);

        Result = LouKeMallocArray(WCHAR, (wcslen(VendorIDs) + 1) + (wcslen(DeviceIDs) + 1) + (wcslen(SubVendorIDs) + 1) + (wcslen(SubDeviceIDs) + 1) + (wcslen(Classs) + 1) + (wcslen(SubClasss) + 1) + (wcslen(ProgIfs) + 1), KERNEL_GENERIC_MEMORY);
        *WcsVendorID = Result;         
        wcscpy(Result, VendorIDs);
        
        Result += wcslen(Result) + 1;
        *WcsDeviceID = Result;
        wcscpy(Result , DeviceIDs);
        
        Result += wcslen(Result) + 1;
        *WcsSubVendorID = Result;
        wcscpy(Result, SubVendorIDs);
        
        Result += wcslen(Result) + 1;
        *WcsSubDeviceID = Result;
        wcscpy(Result, SubDeviceIDs);
        
        Result += wcslen(Result) + 1;
        *WcsClassID = Result;
        wcscpy(Result, Classs);
        
        Result += wcslen(Result) + 1;
        *WcsSubClassID = Result;
        wcscpy(Result, SubClasss);
        
        Result += wcslen(Result) + 1;
        *WcsProgIf = Result;
        wcscpy(Result, ProgIfs);
}

PVOID LouKeGetPciDeviceRegistryHandle(
    LPWSTR VendorID, LPWSTR DeviceID,
    LPWSTR SubVendorID, LPWSTR SubDeviceID,
    LPWSTR ClassID, LPWSTR SubClassID,
    LPWSTR ProgIf 
){
    PVOID PciKeys = LouKeOpenRegistryHandle(L"KERNEL_DEFAULT_CONFIG\\Drivers\\PCI", 0x00);
    PVOID VendorKey = 0;
    PVOID DeviceKey = 0;
    PVOID SubVendorKey = 0;
    PVOID SubDeviceKey = 0;
    PVOID ClassKey = 0;
    PVOID SubClassKey = 0;
    PVOID ProgIfKey = 0;
    if(!PciKeys){
        LouPrint("Unable To Open PCI Keys\n");
        return 0x00;
    }
    //what im about to do is about to piss
    //everyone off if you get pissed off by
    //this either deal with it or make it 
    //better and exspect me to deny a patch
    //if it dosent work on my machine...
    bool VenSpecficKey = true;
    bool DevSpecficKey = true;
    bool SubVenSpecficKey = true;
    bool SubDevSpecficKey = true;
    bool ClassSpecificKey = true;
    bool SubClassSpecificKey = true;
    VendorKey = LouKeOpenRegistryHandle(VendorID, PciKeys);
    if(!VendorKey){
        _ABORT_VENDOR_SPECIFC_KEY:
        VenSpecficKey = false;
        DevSpecficKey = true;
        SubVenSpecficKey = true;
        SubDevSpecficKey = true;
        ClassSpecificKey = true;
        SubClassSpecificKey = true;
        VendorKey = LouKeOpenRegistryHandle(L"0xFFFF", PciKeys);
        if(!VendorKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    DeviceKey = LouKeOpenRegistryHandle(DeviceID, VendorKey);
    if(!DeviceKey){
        _ABORT_DEVICE_SPECIFC_KEY:
        DevSpecficKey = false;
        SubVenSpecficKey = true;
        SubDevSpecficKey = true;
        ClassSpecificKey = true;
        SubClassSpecificKey = true;
        //if device specific Device key is not found use a generic one
        DeviceKey = LouKeOpenRegistryHandle(L"0xFFFF", VendorKey);
        if(!DeviceKey && VenSpecficKey){
            //if we use a vendor specific Vendor Key fallback to a Generic Key
            goto _ABORT_VENDOR_SPECIFC_KEY;
        }
        else if(!DeviceKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    SubVendorKey = LouKeOpenRegistryHandle(SubVendorID, DeviceKey);
    if(!SubVendorKey){
        _ABORT_SUB_VENDOR_SPECIFC_KEY:
        SubVenSpecficKey = false;
        SubDevSpecficKey = true;
        ClassSpecificKey = true;
        SubClassSpecificKey = true;
        //if a vendor specific key is not found fall back to a generic one
        SubVendorKey = LouKeOpenRegistryHandle(L"0xFFFF", DeviceKey);
        if(!SubVendorKey && DevSpecficKey){
            goto _ABORT_DEVICE_SPECIFC_KEY;
        }
        else if(!SubVendorKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    SubDeviceKey = LouKeOpenRegistryHandle(SubDeviceID, SubVendorKey);
    if(!SubDeviceKey){
        _ABORT_SUB_DEVICE_SPECIFC_KEY:
        SubDevSpecficKey = false;
        ClassSpecificKey = true;
        SubClassSpecificKey = true;
        //if device specific Device key is not found use a generic one
        SubDeviceKey = LouKeOpenRegistryHandle(L"0xFFFF", SubVendorKey);
        if(!SubDeviceKey && SubVenSpecficKey){
            //if we use a vendor specific Vendor Key fallback to a Generic Key
            goto _ABORT_SUB_VENDOR_SPECIFC_KEY;
        }
        else if(!SubDeviceKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    ClassKey = LouKeOpenRegistryHandle(ClassID, SubDeviceKey);
    if(!ClassKey){
        _ABORT_CLASS_SPECIFC_KEY:
        ClassSpecificKey = false;
        SubClassSpecificKey = true;
        //if device specific Device key is not found use a generic one
        ClassKey = LouKeOpenRegistryHandle(L"0xFF", SubDeviceKey);
        if(!ClassKey && SubDevSpecficKey){
            //if we use a vendor specific Vendor Key fallback to a Generic Key
            goto _ABORT_SUB_DEVICE_SPECIFC_KEY;
        }
        else if(!ClassKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    SubClassKey = LouKeOpenRegistryHandle(SubClassID, ClassKey);
    if(!SubClassKey){
        //_ABORT_SUB_CLASS_SPECIFC_KEY:
        SubClassSpecificKey = false;
        //if device specific Device key is not found use a generic one
        SubClassKey = LouKeOpenRegistryHandle(L"0xFF", ClassKey);
        if(!SubClassKey && ClassSpecificKey){
            //if we use a vendor specific Vendor Key fallback to a Generic Key
            goto _ABORT_CLASS_SPECIFC_KEY;
        }
        else if(!SubClassKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    ProgIfKey = LouKeOpenRegistryHandle(ProgIf, SubClassKey);
    if(!ProgIfKey){
        //if device specific Device key is not found use a generic one
        ProgIfKey = LouKeOpenRegistryHandle(L"0xFF", SubClassKey);
        if(!ProgIfKey && SubClassSpecificKey){
            //if we use a vendor specific Vendor Key fallback to a Generic Key
            goto _ABORT_CLASS_SPECIFC_KEY;
        }
        else if(!ProgIfKey){
            goto _REGISTRY_SEARCH_IMPLODED;
        }
    }
    return ProgIfKey;

    _REGISTRY_SEARCH_IMPLODED:
    return 0x00;
}

size_t LouKePciGetLoadOrderForEntry(
    LPWSTR VendorID, LPWSTR DeviceID,
    LPWSTR SubVendorID, LPWSTR SubDeviceID,
    LPWSTR ClassID, LPWSTR SubClassID,
    LPWSTR ProgIf
){
    PVOID PciDeviceHandle = 0x00;
    PVOID LoadOrderHandle = 0x00;
    PVOID DriverKeyHandle = 0x00;
    PVOID LoadOrder = 0x00;
    LPWSTR DriverKey = 0;
    if(VendorID){
        
        PciDeviceHandle = LouKeGetPciDeviceRegistryHandle(
            VendorID,
            DeviceID,
            SubVendorID,
            SubDeviceID,
            ClassID,
            SubClassID,
            ProgIf
        );

        if(!PciDeviceHandle){
            goto _NOT_LOADED_DEVICE;
        }

        DriverKeyHandle = LouKeOpenRegistryHandle(L"DriverKey", PciDeviceHandle);
        if(!DriverKeyHandle){
            goto _NOT_LOADED_DEVICE;
        }
        
        size_t WcsDriverKeySize = LouKeGetRegistryKeySize(DriverKeyHandle);

        DriverKey = LouKeMallocArray(WCHAR, (WcsDriverKeySize / 2) + 1, KERNEL_GENERIC_MEMORY);
        UNUSED LOUSTATUS ReadResult = LouKeReadRegistryWcsValue(DriverKeyHandle, DriverKey);
        if(ReadResult != STATUS_SUCCESS){
            goto _NOT_LOADED_DEVICE;
        }

        LoadOrderHandle = LouKeOpenRegistryHandle(DriverKey, 0x00);
        if(!LoadOrderHandle){
            goto _NOT_LOADED_DEVICE;
        }

        LoadOrder = LouKeOpenRegistryHandle(L"LoadOrder", LoadOrderHandle);
        if(!LoadOrder){
            LoadOrder = LouKeOpenRegistryHandle(L"PreLoadedFallback", LoadOrderHandle); //generic fallback
            if(!LoadOrder){
                goto _NOT_LOADED_DEVICE;
            }
        }
        WORD LoadID = 0x00;
        ReadResult = LouKeReadRegistryWordValue(LoadOrder, &LoadID);
        if(ReadResult != STATUS_SUCCESS){
            goto _NOT_LOADED_DEVICE;
        }
        LouKeFree(VendorID);
        return (size_t)LoadID;
    }
    _NOT_LOADED_DEVICE:
    if(VendorID){
        LouKeFree(VendorID);
        if(DriverKey){
            LouKeFree(DriverKey);
        }
    }
    return GetBootDeviceCount();
}

size_t LouKeGetBootDeviceIndex(PPCI_COMMON_CONFIG Config){
    size_t Result = 0;
    LPWSTR VendorID = 0; 
    LPWSTR DeviceID = 0;
    LPWSTR SubVendorID = 0; 
    LPWSTR SubDeviceID = 0;
    LPWSTR ClassID = 0; 
    LPWSTR SubClassID = 0;
    LPWSTR ProgIf = 0;

    CreateRegistryEntryFromPciDevice(
        Config,
        &VendorID,
        &DeviceID,
        &SubVendorID,
        &SubDeviceID,
        &ClassID,
        &SubClassID,
        &ProgIf
    );
    
    Result = LouKePciGetLoadOrderForEntry(
        VendorID,
        DeviceID,
        SubVendorID,
        SubDeviceID,
        ClassID,
        SubClassID,
        ProgIf
    );

    return Result;
}

KERNEL_IMPORT
char *
strcat(
    char                    *DstString,
    const char              *SrcString
);


string LouKeAcquirePciDriverPath(PPCI_COMMON_CONFIG Config){
    LPWSTR VendorID = 0; 
    LPWSTR DeviceID = 0;
    LPWSTR SubVendorID = 0; 
    LPWSTR SubDeviceID = 0;
    LPWSTR ClassID = 0; 
    LPWSTR SubClassID = 0;
    LPWSTR ProgIf = 0;
    PVOID PciDeviceHandle = 0x00;
    PVOID DriverKeyHandle = 0x00;
    PVOID DriverPathHandle = 0x00;
    LPWSTR DriverKey = 0x00;
    LPWSTR WcsDriverPath = 0x00;
    string BcsDriverPath = 0x00;  
    
    CreateRegistryEntryFromPciDevice(
        Config,
        &VendorID,
        &DeviceID,
        &SubVendorID,
        &SubDeviceID,
        &ClassID,
        &SubClassID,
        &ProgIf
    );

    if(VendorID){

        PciDeviceHandle = LouKeGetPciDeviceRegistryHandle(
            VendorID,
            DeviceID,
            SubVendorID,
            SubDeviceID,
            ClassID,
            SubClassID,
            ProgIf
        );
        if(!PciDeviceHandle){
            goto _DEVICE_NOT_SUPPORTED;
        }
        
        DriverKeyHandle = LouKeOpenRegistryHandle(L"DriverKey", PciDeviceHandle);
        if(!DriverKeyHandle){
            goto _DEVICE_NOT_SUPPORTED;
        }
        
        size_t WcsDriverKeySize = LouKeGetRegistryKeySize(DriverKeyHandle);

        DriverKey = LouKeMallocArray(WCHAR, (WcsDriverKeySize / 2) + 1, KERNEL_GENERIC_MEMORY);
        UNUSED LOUSTATUS ReadResult = LouKeReadRegistryWcsValue(DriverKeyHandle, DriverKey);
        if(ReadResult != STATUS_SUCCESS){
            goto _DEVICE_NOT_SUPPORTED;
        }

        DriverPathHandle = LouKeOpenRegistryHandle(DriverKey, 0x00);
        if(!DriverPathHandle){
            goto _DEVICE_NOT_SUPPORTED;
        }

        DriverPathHandle = LouKeOpenRegistryHandle(L"DriverName", DriverPathHandle);
        if(!DriverPathHandle){
            goto _DEVICE_NOT_SUPPORTED;
        }

        size_t WcsPathKeySize = (LouKeGetRegistryKeySize(DriverPathHandle) / 2) + 1;
        WcsDriverPath = LouKeMallocArray(WCHAR, WcsPathKeySize, KERNEL_GENERIC_MEMORY);

        ReadResult = LouKeReadRegistryWcsValue(DriverPathHandle, WcsDriverPath);
        if(ReadResult != STATUS_SUCCESS){
            goto _DEVICE_NOT_SUPPORTED;
        }

        SanityCheck(WcsDriverPath, wcslen(WcsDriverPath));

        size_t DriverDirLength = strlen("C:/ANNYA/SYSTEM64/DRIVERS/");

        BcsDriverPath = LouKeMallocArray(CHAR, DriverDirLength + WcsPathKeySize, KERNEL_GENERIC_MEMORY);
        
        strncpy(BcsDriverPath, "C:/ANNYA/SYSTEM64/DRIVERS/", DriverDirLength);

        for(size_t i = 0 ; i < (WcsPathKeySize - 1); i++){
            BcsDriverPath[DriverDirLength + i] = (CHAR)WcsDriverPath[i];
        }
            
        LouKeFree(VendorID);
        if(DriverKey){
            LouKeFree(DriverKey);
        }
        if(WcsDriverPath){
            LouKeFree(WcsDriverPath);
        }
        return BcsDriverPath;
    }
    _DEVICE_NOT_SUPPORTED:
    if(VendorID){
        LouKeFree(VendorID);
        if(DriverKey){
            LouKeFree(DriverKey);
        }
        if(WcsDriverPath){
            LouKeFree(WcsDriverPath);
        }
        if(BcsDriverPath){
            LouKeFree(BcsDriverPath);
        }
    }

    return 0x00;
}

void LouKeReleasePciDriverPath(string Path){
    LouKeFree(Path);
}