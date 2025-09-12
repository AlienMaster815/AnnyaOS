
#include <LouDDK.h>

static string LDDDS = 0; 

char DataMap[] = { 
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    0,
};

static inline uint8_t LDDDSAsciiToHexU8(string Ascii){
    uint8_t i = 0, j = 0;
    uint8_t Result = 0;
    while(Ascii[i] != '/'){ // '/' is the LDDDSAscii HEX null terminator
        j = 0;
        while(DataMap[j] != 0){
            if(DataMap[j] == Ascii[i]){
                Result |= (j << (4 - (i * 4))); //truns the ASCII into a value 
                break;
            }
            j++;
        }
        if(DataMap[j] == 0){ //LDDDSAscii invalid
            return 0;
        }
        i++;
    }

    return Result;
}

static inline uint16_t LDDDSAsciiToHexU16(string Ascii){
    uint8_t i = 0, j = 0;
    uint16_t Result = 0;
    while(Ascii[i] != '/'){ // '/' is the LDDDSAscii HEX null terminator
        j = 0;
        while(DataMap[j] != 0){
            if(DataMap[j] == Ascii[i]){
                Result |= (j << (12 - (i * 4))); //truns the ASCII into a value 
                break;
            }
            j++;
        }
        if(DataMap[j] == 0){ //LDDDSAscii invalid
            return 0;
        }
        i++;
    }

    return Result;
}


static
string LousineDriverManifestGetNextDevice(string CurrentDevice){
    CurrentDevice += 1;

    while(strncmp(CurrentDevice, "}DRIVERS", strlen("}DRIVERS")) != 0){
        if(strncmp(CurrentDevice, "DEVICE_TREE_ENTRY{", strlen("DEVICE_TREE_ENTRY{")) == 0){
            return CurrentDevice;
        }
        CurrentDevice += 1;
    }

    return 0x00;
}

LOUDDK_API_ENTRY
string LouKeGetNextManifestDevice(string CurrentDevice){
    return LousineDriverManifestGetNextDevice(CurrentDevice);
}

static string DoesDeviceMatch(string CurrentDevice, PPCI_COMMON_CONFIG Config){
    uint16_t DeviceID = 0;
    uint16_t VendorID = 0;
    uint8_t ClassID = 0;
    uint8_t ProgIf;
    size_t i = 0;
    while((strncmp(CurrentDevice, "}DRIVERS", strlen("}DRIVERS")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){

        while((strncmp(CurrentDevice, "VENDOR_ID:", strlen("VENDOR_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }

        CurrentDevice += strlen("VENDOR_ID:");
        if(strncmp(CurrentDevice, "ANY_VENDOR_ID", strlen("ANY_VENDOR_ID")) != 0){
            CurrentDevice += strlen("0x");
            VendorID = LDDDSAsciiToHexU16(CurrentDevice);        
            if(VendorID != Config->Header.VendorID){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "DEVICE_ID:", strlen("DEVICE_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice += 1;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }
        
        CurrentDevice += strlen("DEVICE_ID:");
        if(strncmp(CurrentDevice, "ANY_DEVICE_ID", strlen("ANY_DEVICE_ID")) != 0){
            CurrentDevice += strlen("0x");
            DeviceID = LDDDSAsciiToHexU16(CurrentDevice);        
            if(DeviceID != Config->Header.DeviceID){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "SUB_VENDOR_ID:", strlen("SUB_VENDOR_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }

        CurrentDevice += strlen("SUB_VENDOR_ID:");
        if(strncmp(CurrentDevice, "ANY_SUB_VENDOR_ID", strlen("ANY_SUB_VENDOR_ID")) != 0){
            CurrentDevice += strlen("0x");
            VendorID = LDDDSAsciiToHexU16(CurrentDevice);        
            if(VendorID != Config->Header.u.type0.SubVendorID){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "SUB_DEVICE_ID:", strlen("SUB_DEVICE_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }
        
        CurrentDevice += strlen("SUB_DEVICE_ID:");
        if(strncmp(CurrentDevice, "ANY_SUB_DEVICE_ID", strlen("ANY_SUB_DEVICE_ID")) != 0){
            CurrentDevice += strlen("0x");
            DeviceID = LDDDSAsciiToHexU16(CurrentDevice);        
            if(DeviceID != Config->Header.u.type0.SubSystemID){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "CLASS_ID:", strlen("CLASS_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }
        
        CurrentDevice += strlen("CLASS_ID:");
        if(strncmp(CurrentDevice, "ANY_CLASS_ID", strlen("ANY_CLASS_ID")) != 0){
            CurrentDevice += strlen("0x");
            ClassID = LDDDSAsciiToHexU8(CurrentDevice);        
            if(ClassID != Config->Header.BaseClass){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "SUB_CLASS_ID:", strlen("SUB_CLASS_ID:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }
        
        CurrentDevice += strlen("SUB_CLASS_ID:");
        if(strncmp(CurrentDevice, "ANY_SUB_CLASS_ID", strlen("ANY_SUB_CLASS_ID")) != 0){
            CurrentDevice += strlen("0x");
            ClassID = LDDDSAsciiToHexU8(CurrentDevice);        
            if(ClassID != Config->Header.SubClass){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "PROG_IF:", strlen("PROG_IF:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }

        CurrentDevice += strlen("PROG_IF:");
        if(strncmp(CurrentDevice, "ANY_PROG_IF", strlen("ANY_PROG_IF")) != 0){
            CurrentDevice += strlen("0x");
            ProgIf = LDDDSAsciiToHexU8(CurrentDevice);        
            if(ProgIf != Config->Header.ProgIf){
                continue;
            }
        }

        while((strncmp(CurrentDevice, "FILE_PATH:", strlen("FILE_PATH:")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){ //shift to the next Vendor ID
            CurrentDevice++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }
        
            
        CurrentDevice += strlen("FILE_PATH:");

        while((strncmp(CurrentDevice, ":FILE_PATH:", strlen(":FILE_PATH")) != 0) && (strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) != 0)){\
            CurrentDevice++;
            i++;
        }
        if(strncmp(CurrentDevice, "}DEVICE_TREE_ENTRY", strlen("}DEVICE_TREE_ENTRY")) == 0){
            return 0x00;
        }

        CurrentDevice -= i;
        i++; //add room for null terminator
        string NewString = (string)LouKeMallocArray(char, i, KERNEL_GENERIC_MEMORY);

        for(size_t j = 0 ; j < i; j++){
            if(j == (i - 1)){
                NewString[j] = '\0';
                break;
            }
            NewString[j] = CurrentDevice[j];
        }

        return NewString;
    }
    return 0x00;
}

LOUDDK_API_ENTRY
string LouKeDoesManifestDeviceMatch(string CurrentDevice, void* Config){
    return DoesDeviceMatch(CurrentDevice, (PPCI_COMMON_CONFIG)Config);
}

string ParseLousineDriverManifestForCompatibleDriver(void* Config, string Index){

    UNUSED PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)Config;

    if(!LDDDS){
        LDDDS = (string)fopen("C:/ANNYA/SYSTEM64/CONFIG/DRIVERS.CFG", KERNEL_GENERIC_MEMORY);
    }
    if(!LDDDS){
        return 0x00;
    }
    string Tmp = LDDDS;
    if(Index){
        Tmp = (string)((uint64_t)Index + 1);
    }
    if(strncmp(Tmp, "DRIVERS", strlen("DRIVERS")) == 0){
        //LouPrint("Parsing Driver Manifest\n");
        while(1){        
            Tmp = LousineDriverManifestGetNextDevice(Tmp);
            if(!Tmp){
                return 0x00;
            }
            //LouPrint("Checking If Device Matches The Table Member\n");
            
            string FilePath = DoesDeviceMatch(Tmp, CommonConfig);
            if(!FilePath){
                continue;
            }

            return FilePath;

        }
    }
    return 0x00;
}
