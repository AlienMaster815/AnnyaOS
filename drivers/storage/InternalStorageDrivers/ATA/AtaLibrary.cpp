#include <LouDDK.h>


LOUDDK_API_ENTRY
PLOUSINE_KERNEL_DEVICE_ATA_HOST
LouMallocAtaDevice(P_PCI_DEVICE_OBJECT PDEV, uint8_t PortCount){

    PLOUSINE_KERNEL_DEVICE_ATA_HOST NewHost;

    NewHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)LouMallocEx((sizeof(LOUSINE_KERNEL_DEVICE_ATA_HOST) + (sizeof(LOUSINE_KERNEL_DEVICE_ATA_PORT) * PortCount)), sizeof(LOUSINE_KERNEL_DEVICE_ATA_HOST));
    NewHost->PDEV = PDEV;
    NewHost->PortCount = PortCount;
    
    for(uint8_t i = 0 ; i < PortCount; i++){
        NewHost->Ports[i].Siblings = PortCount - 1;
        NewHost->Ports[i].PDEV = PDEV;
        NewHost->Ports[i].AtaHost = NewHost;    
        NewHost->Ports[i].PortNumber = i + 1;    
    }


    return NewHost;
}

void* ReadPata(uint8_t DriveNum, uint64_t LBA, uint64_t* BufferSize){
    void* Buffer = LouMalloc(*BufferSize);

    

    return Buffer;
}


bool IsAtaController(P_PCI_DEVICE_OBJECT PDEV){
    PCI_COMMON_CONFIG PciConfig;
    GetPciConfiguration(PDEV->bus, PDEV->slot, PDEV->func, &PciConfig);

    if((PciConfig.Header.BaseClass == 0x01) && PciConfig.Header.SubClass == 0x01){
        LouPrint("Found ATA Controller\n");
        return true;
    }
    return false;
}

LOUDDK_API_ENTRY
LOUSTATUS LouKeAtaSendAtaIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    void* IdBuffer
){



    return STATUS_SUCCESS;
}

LOUDDK_API_ENTRY 
LOUSTATUS LouKeAtaSendAtapiIdentifyCommand(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT  AtapiPort,
    void*                            IdBuffer
){
    //TODO: Add SPinlocks for Ports And Host
    LOUSTATUS Result = STATUS_SUCCESS;
    LouPrint("LOUSINE ATA LIB:Creating Atapi Identify Command\n");
    UNUSED ATA_QUEUED_COMMAND Command;
    Command.Command     = ATA_COMMAND_IDENTIFY_ATAPI;
    Command.WriteCommand= false;
    Command.DataAddress = (uint64_t)IdBuffer;
    Command.Port        = AtapiPort;
    Command.WriteCommand= false;
    Command.Lbal        = 0;
    Command.Lbam        = 0;
    Command.Lbah        = 0;
    Command.SectorCount = 0;
    Command.ScsiCommandLength = 0;
    Command.PacketCommand = false;
    memset((void*)Command.ScsiCommand, 0 , 16);
    LouPrint("LOUSINE ATA_LIB:Preping Atapi Identify Command\n");
    if(AtapiPort->Operations->PrepCommand){
        Result = AtapiPort->Operations->PrepCommand(&Command);
        if(Result != STATUS_SUCCESS){
            return Result;
        }
    }
    if(AtapiPort->Operations->IssueCommand){
        Result = AtapiPort->Operations->IssueCommand(&Command);
    }

    return Result;
}
