
#include "PIIX.h"



static LOUSINE_PCI_DEVICE_TABLE PiixPciDeviceTable[] = {
    //PATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x7010 , .BoardID = PIIX_CONTROLLER_ID_PATA_MWDMA, .SimpleEntry = true},
    /*{.VendorID = 0x8086, .DeviceID = 0x7111 , .SubVendorID = 0x15AD, .SubDeviceID = 0x1976, .BoardID = PIIX_CONTROLLER_ID_VMWARE, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7111 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7199 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x7601 , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x84CA , .BoardID = PIIX_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2421 , .BoardID = ICH_CONTROLLER_ID_PATA_33, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2411 , .BoardID = ICH_CONTROLLER_ID_PATA_66, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x244A , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x244B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x248A , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x248B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24C1 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24CA , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24CB , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24DB , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x245B , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25A2 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x266F , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2850 , .BoardID = ICH_CONTROLLER_ID_PATA_100, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x27DF , .BoardID = ICH_CONTROLLER_ID_PATA_100_NO_MWDMA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x269E , .BoardID = ICH_CONTROLLER_ID_PATA_100_NO_MWDMA, .SimpleEntry = true},
    //SATA Devices
    {.VendorID = 0x8086, .DeviceID = 0x24D1 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x24DF , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25A3 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x25B0 , .BoardID = ICH5_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2651 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2652 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x27C0 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2680 , .BoardID = ICH6_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2653 , .BoardID = ICH6M_CONTROLLER_ID_SATA, .SimpleEntry = true}, //simple entry because the maniges already handles the class
    {.VendorID = 0x8086, .DeviceID = 0x27C4 , .BoardID = ICH6M_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2820 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2825 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A0, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A1, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .SubVendorID = 0x106B, .SubDeviceID = 0x00A3, .BoardID = ICH8M_APPLE_CONTROLLER_ID_SATA, .AdvancedEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2828 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2920 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2921 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2926 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x2928 , .BoardID = ICH8_2P_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x292E , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x5028 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A00 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A06 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},
    {.VendorID = 0x8086, .DeviceID = 0x3A20 , .BoardID = ICH8_CONTROLLER_ID_SATA, .SimpleEntry = true},*/
    {0},
};

void UnloadDriver(PDRIVER_OBJECT Driver){

}

static LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LOUSTATUS Status;
    UINT16  Tmp;
    UINT8   MaxPio;
    UINT8   MaxUDma;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    BOOL Channel1Used;
    BOOL Channel2Used;
    LouKeMallocAtaPrivateData(AtaHost, sizeof(PIIX3_HOST_PRIVATE_DATA), GET_ALIGNMENT(PIIX3_HOST_PRIVATE_DATA));
    PPIIX3_HOST_PRIVATE_DATA PiixPrivateData = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;

    PiixPrivateData->Bmiba = (UINT32)(UINTPTR)LouKePciGetIoRegion(PDEV, BMBIA_BAR, 0);
    PiixPrivateData->MaxPioMode = 4;
    PiixPrivateData->MaxUDmaMode = 7;

    LouKeForkAtaHostPrivateDataToPorts(AtaHost);

    LouPrint("PIIX.SYS:PIIX BMIBA IO Port:%h\n", PiixPrivateData->Bmiba);
    UINT16* Buffer = (UINT16*)LouKeMalloc(512, KERNEL_GENERIC_MEMORY);    
    for(size_t i = 0 ; i < 4; i++){
        MaxPio = 2;
        MaxUDma = 0;
        if(AtaHost->Ports[i].PortScsiDevice){

            Status = LouKeAtaSendAtapiIdentifyCommand(
                &AtaHost->Ports[i],
                Buffer
            );

            if(Status != STATUS_SUCCESS){
                LouPrint("PIIX.SYS:ERROR:Faild To Send Identify Data\n");
                continue;
            }

        }else if(AtaHost->Ports[i].DeviceAttached){
            Status = LouKeAtaSendAtaIdentifyCommand(
                &AtaHost->Ports[i],
                Buffer
            );

            if(Status != STATUS_SUCCESS){
                LouPrint("PIIX.SYS:ERROR:Faild To Send Identify Data\n");
                continue;
            }
        }else {
            continue;
        }

        Tmp = Buffer[53];

        if(Tmp & (1 << 1)){
            LouPrint("PIIX.SYS:Fast PIO Supported\n");
            Tmp = Buffer[64];
            if(Tmp & (1 << 1)){
                MaxPio = 4;
            }
            else if(Tmp & (1 << 0)){
                MaxPio = 3;
            }
        }

        if(i < 2){
            Channel1Used = true;
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode = MIN(MaxPio, ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode);
        }else{
            Channel2Used = true;
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode = MIN(MaxPio, ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode);
        }

        Tmp = Buffer[53];
        if(Tmp & (1 << 2)){
            LouPrint("PIIX.SYS:UDMA Supported\n");
            Tmp = Buffer[88];
            for(int i = 7; i >= 0; i--){
                if(!(Tmp & (1 << i))){
                    MaxUDma = i;
                    break;
                }
            }   
            if(i < 2){
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxUDmaMode);
            }else{
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxUDmaMode);
            }
        }
        memset(Buffer, 0, 512);
    }
    LouKeFree(Buffer);

    UINT16 Time;

    if(Channel1Used){
        MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode;
        MaxUDma = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxUDmaMode;

        LouPrint("PIIX.SYS:Primary Max PIO Mode:%d\n", MaxPio);
        LouPrint("PIIX.SYS:Primary Max UDMA Mode:%d\n", MaxUDma);

        Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
            
        Time |= IDETIM_IE0;

        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

        Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

        if(MaxPio == 4){
            Time &= ~(SIDTIM_PISP1);
            Time |= (SIDTIM_PISP1_2CLOCKS | SIDTIM_PRTC1_1CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 4;
        }else if(MaxPio == 3){            
            Time &= ~(SIDTIM_PISP1);
            Time |= (SIDTIM_PISP1_3CLOCKS | SIDTIM_PRTC1_2CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 3 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
        }else if(MaxPio == 2){
            Time &= ~(SIDTIM_PISP1);
            Time |= (SIDTIM_PISP1_4CLOCKS | SIDTIM_PRTC1_3CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 2 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
        }else if(MaxPio == 1){
            Time &= ~(SIDTIM_PISP1);
            Time |= (SIDTIM_PISP1_5CLOCKS | SIDTIM_PRTC1_4CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 1 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
        }else{
            LouPrint("PIIX.SYS:Clocks Could Not Be Set Device Dosent Support Speeds\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
        }

    }

    if(Channel2Used){

        MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode;
        MaxUDma = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxUDmaMode;
        LouPrint("PIIX.SYS:Secondary Max PIO Mode:%d\n", MaxPio);
        LouPrint("PIIX.SYS:Secondary Max UDMA Mode:%d\n", MaxUDma);

        Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
            
        Time |= IDETIM_IE0;

        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);

        Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

        if(MaxPio == 4){
            Time &= ~(SIDTIM_SISP1);
            Time |= (SIDTIM_SISP1_2CLOCKS | SIDTIM_SRTC1_1CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 4;
        }else if(MaxPio == 3){
            Time &= ~(SIDTIM_SISP1);
            Time |= (SIDTIM_SISP1_3CLOCKS | SIDTIM_SRTC1_2CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 3 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
        }else if(MaxPio == 2){
            Time &= ~(SIDTIM_SISP1);
            Time |= (SIDTIM_SISP1_4CLOCKS | SIDTIM_SRTC1_3CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 2 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
        }else if(MaxPio == 1){
            Time &= ~(SIDTIM_SISP1);
            Time |= (SIDTIM_SISP1_5CLOCKS | SIDTIM_SRTC1_4CLOCKS);
            LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
            LouPrint("PIIX.SYS:Clocks Set To PIO 1 Mode\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
        }else{
            LouPrint("PIIX.SYS:Clocks Could Not Be Set Device Dosent Support Speeds\n");
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
        }

    }

    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, struct _DEVICE_OBJECT* PlatformDevice){
    
    LouPrint("PIIX.SYS:AddDevice()\n");
    PPCI_DEVICE_OBJECT PDEV = PlatformDevice->PDEV;
    LOUSTATUS Status;

    Status = InitializeGenericAtaDevice(PDEV);
    
    if(Status != STATUS_SUCCESS){
        LouPrint("PIIX.SYS:Unable To Create Generic IDE Device\n");
        return Status;
    }

    uint8_t DeviceID = PlatformDevice->DeviceID;
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = LouKeDeviceManagerGetAtaDevice(PDEV);

    if(!AtaHost){
        LouPrint("PIIX.SYS:Error Controller Not In Ata Manager\n");
        return STATUS_NO_SUCH_DEVICE;
    }

    Status = LouKeHalEnablePciDevice(PDEV);
    if(Status != STATUS_SUCCESS){
        return (NTSTATUS)Status;
    }


    if(PiixPciDeviceTable[DeviceID].BoardID == PIIX_CONTROLLER_ID_PATA_MWDMA){
        Status = PiixInitializePiix3Xceleration(AtaHost);
    }

    if(Status != STATUS_SUCCESS){
        LouPrint("PIIX.SYS:Error Unable To Initialize Acceleration\n");
        return Status;
    }

    LouPrint("PIIX.SYS:AddDevice() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY
NTSTATUS DriverEntry(
    PDRIVER_OBJECT  DriverObject,
    PUNICODE_STRING RegistryEntry
){

    LouPrint("PIIX.SYS:DriverEntry()\n");
    //tell the System where are key Nt driver functions are
    DriverObject->DriverExtension->AddDevice = AddDevice;
    DriverObject->DriverUnload = UnloadDriver;
    //tell the lousine kernel we will be using the
    //Lousine Kernel Driver Module (LKDM) alongside the
    //NT Kernel Moudle Subsystem so it fills
    //out the extra information relating to the LKDM
    DriverObject->DriverUsingLkdm = true;
    //fill LDM information
    DriverObject->DeviceTable = (uintptr_t)PiixPciDeviceTable;

    LouPrint("PIIX.SYS:DriverEntry() STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}