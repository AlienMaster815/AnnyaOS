#include "PIIX.h"

//According to specification we can wait the 400ns byt reaing AS 4 times
static inline void AtaIoWait400ns(uint16_t ControlPort){
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
}

LOUSTATUS PiixSetPioTiming(
    PLOUSINE_KERNEL_DEVICE_ATA_PORT Port,
    UINT8                           TimingMode
);


LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LOUSTATUS Status;
    UINT16  Tmp;
    UINT8   MaxPio;
    UINT8   MaxUDma;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    BOOL Channel1Used;
    BOOL Channel2Used;
    LouKeMallocAtaPrivateData(AtaHost, sizeof(PIIX_HOST_PRIVATE_DATA), GET_ALIGNMENT(PIIX_HOST_PRIVATE_DATA));
    PPIIX_HOST_PRIVATE_DATA PiixPrivateData = (PPIIX_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;

    LouKeInitializeEventTimeOut(&PiixPrivateData->PrimaryEvent, 10000);
    LouKeInitializeEventTimeOut(&PiixPrivateData->SecondaryEvent, 10000);

    PiixPrivateData->Bmiba = (UINT32)(UINTPTR)LouKePciGetIoRegion(PDEV, BMBIA_BAR, 0);
    PiixPrivateData->MaxPioMode = 4;
    PiixPrivateData->MaxDmaMode = 7;
    PiixPrivateData->UsesUDMA = false;

    UINT16 Time;
    
    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
    Time |= IDETIM_SITRE;
    LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
    Time |= IDETIM_SITRE;
    LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);


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

        ((PPIIX_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxPioMode = MaxPio;

        PiixSetPioTiming(&AtaHost->Ports[i], MaxPio);

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
                ((PPIIX_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxDmaMode = MIN(MaxUDma, 2);
            }else{
                ((PPIIX_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxDmaMode = MIN(MaxUDma, 2);
            }

        }
        AtaHost->Ports[i].DmaPort = true;
        memset(Buffer, 0, 512);
    }
    LouKeFree(Buffer);

    LouKeHalPciSetMaster(PDEV);

    return STATUS_SUCCESS;
}
