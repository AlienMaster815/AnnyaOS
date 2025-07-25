#include <LouAPI.h>


//this is more for a future proof the real amount of devices might be different
static DEVICE_DIRECTORY_TABLE MasterDeviceTable;
static uint32_t NumberOfDevices = 0;

LOUSTATUS LouRegisterAtaDeviceToInformationTable(
    PDEVICE_DIRECTORY_TABLE Table,
    P_PCI_DEVICE_OBJECT PDEV, 
    SYSTEM_DEVICE_IDENTIFIER Sdi,
    string LRE, //optional
    void* KeyData, //optional
    void* DevicePrivateData
);

LOUSTATUS LouRegisterDrsdGraphicsDevice(
    PDEVICE_DIRECTORY_TABLE Table
);

LOUSTATUS LouRegisterStorageDevice(
    PDEVICE_DIRECTORY_TABLE Table
);


LOUSTATUS DeviceManagerInitializeAtaHostDevice(PDEVICE_DIRECTORY_TABLE DeviceDirectoryTable);

LOUSTATUS LouRegisterFileSystemDevice(PDEVICE_DIRECTORY_TABLE NewFileSystem);
LOUSTATUS LouKeDrsdInitializeDevice(
    PDRSD_DEVICE Device
);

LOUSTATUS LouKeRegisterDevice(
    P_PCI_DEVICE_OBJECT PDEV, 
    SYSTEM_DEVICE_IDENTIFIER Sdi,
    string LRE, //optional
    void* KeyData, //optional
    void* DevicePrivateData
){

    PDEVICE_DIRECTORY_TABLE TmpDevice;
    TmpDevice =  &MasterDeviceTable;
    LOUSTATUS Status = STATUS_SUCCESS;

    LouPrint("Registering Device With Key:%s\n", LRE);

    if(NumberOfDevices == 0) {//initialze the system
        TmpDevice->Sdi = MASTER_TABLE;
        TmpDevice->LOUSINE_REGISTRATION_ENTRY = "HostKeyDevice:Master";
        //Key Data Is Null For Master Table
        TmpDevice->KeyData = 0x00;
        TmpDevice->DevicePrivateData = 0x00;
        TmpDevice->DeviceSpecificData = 0x00;
        TmpDevice->PDEV = 0x00;
    }

    bool FoundTable = false;
    for(uint32_t i = 0; i <= NumberOfDevices; i++){
        if(TmpDevice->TableStart.NextHeader != 0x00){
            TmpDevice = (PDEVICE_DIRECTORY_TABLE)TmpDevice->TableStart.NextHeader;
            if(TmpDevice->PDEV == 0x00){
                FoundTable = true;
                break;
            }
        }
        else {
            break;
        }
    }
    
    if(!FoundTable){
        TmpDevice->TableStart.NextHeader = (PListHeader)LouKeMallocType(DEVICE_DIRECTORY_TABLE, KERNEL_GENERIC_MEMORY);
        TmpDevice = (PDEVICE_DIRECTORY_TABLE)TmpDevice->TableStart.NextHeader;
    }
    TmpDevice->PDEV = PDEV;
    TmpDevice->Sdi = Sdi;
    TmpDevice->LOUSINE_REGISTRATION_ENTRY = LRE;
    TmpDevice->KeyData = KeyData;
    TmpDevice->DevicePrivateData = DevicePrivateData;

    switch(Sdi){
        case ATA_DEVICE_T:{
            return DeviceManagerInitializeAtaHostDevice(TmpDevice);
        }
        case GRAPHICS_DEVICE_T:{
            return LouKeDrsdInitializeDevice(
                TmpDevice->DevicePrivateData
            );
        }
        case NETWORK_DEVICE_T:{
            break;
        }
        case SOUND_DEVICE_T:{
            break;
        }
        case MBOARD_DEVICE_T:{
            break;
        }   
        case ACPI_DEVICE_T:{
            break;
        }
        case POINTING_DEVICE_T:{
            break;
        }
        case INTERFACING_DEVICE_T:{
            break;
        }
        case SERIAL_DEVICE_T:{
            break;
        }
        case SCSI_DEVICE_T:{
            break;
        }
        case GENERIC_PCI_DEVICE_T:{
            break;
        }
        case USB_DEVICE_T:{
            break;
        }
        case BLUETOOTH_DEVICE_T:{
            break;
        }
        case PRINTER_DEVICE_T:{
            break;
        }
        case POWER_MANAGEMENT_DEVICE_T:{
            break;
        }
        case VIRTUAL_DEVICE_T:{
            break;
        }
        case SECURITY_DEVICE_T:{
            break;
        }
        case INPUT_DEVICE_T:{
            break;
        }   
        case NVME_DEVICE_T:{
            break;
        }
        case WIFI_DEVICE_T:{

            break;
        }    
        case FILESYSTEM_DEVICE_T:{
            Status = LouRegisterFileSystemDevice(TmpDevice);
            break;
        }
        default:
            Status = STATUS_UNSUCCESSFUL;
    }

    return Status;
}