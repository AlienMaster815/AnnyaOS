#include "PIIX.h"

//According to specification we can wait the 400ns byt reaing AS 4 times
static inline void AtaIoWait400ns(uint16_t ControlPort){
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
    CONTROL_READ_ALTERNATE_STATUS_PORT;
}


static void PiixSetPrimaryMasterPioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_2CLOCK | IDETIM_RTC_1CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_3CLOCK | IDETIM_RTC_2CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_4CLOCK | IDETIM_RTC_3CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_5CLOCK | IDETIM_RTC_4CLOCK);
        LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetPrimarySlavePioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_2CLOCK | SIDTIM_PRTC1_1CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_3CLOCK | SIDTIM_PRTC1_2CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_4CLOCK | SIDTIM_PRTC1_3CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(SIDTIM_PISP1 | SIDTIM_PRTC1);
        Time |= (SIDTIM_PISP1_5CLOCK | SIDTIM_PRTC1_4CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetSecondaryMasterPioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE | IDETIM_TIME0);
    
    LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_2CLOCK | IDETIM_RTC_1CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_3CLOCK | IDETIM_RTC_2CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_4CLOCK | IDETIM_RTC_3CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(IDETIM_ISP | IDETIM_RTC);
        Time |= (IDETIM_ISP_5CLOCK | IDETIM_RTC_4CLOCK);
        LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}

static void PiixSetSecondarySlavePioTiming(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost, UINT8 Mode){
    UINT8 MaxPio = ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    Mode = MIN(Mode, MaxPio);
    UINT16 Time;

    Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
        
    Time |= (IDETIM_IDE | IDETIM_IE0 | IDETIM_IE1 | IDETIM_SITRE);
    
    LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);
    
    Time = LouKeReadPciUint16(PDEV, SIDETIM_REGISTER_OFFSET);

    if(Mode == 4){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_2CLOCK | SIDTIM_SRTC1_1CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 4;
    }else if(Mode == 3){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_3CLOCK | SIDTIM_SRTC1_2CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 2){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_4CLOCK | SIDTIM_SRTC1_3CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else if(Mode == 1){
        Time &= ~(SIDTIM_SISP1 | SIDTIM_SRTC1);
        Time |= (SIDTIM_SISP1_5CLOCK | SIDTIM_SRTC1_4CLOCK);
        LouKeWritePciUint16(PDEV, SIDETIM_REGISTER_OFFSET, Time);
        LouPrint("PIIX.SYS:Clocks Set To PIO 4 Mode\n");
        ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->CurrentPioMode = 3;
    }else {
        LouPrint("PIIX.SYS:WARNING Piix Clocks Could Not Be Set\n");
    }

}


void Piix3SecondaryInterruptHandler(UINT64 Data){
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost = (PLOUSINE_KERNEL_DEVICE_ATA_HOST)Data;
    PPIIX3_HOST_PRIVATE_DATA PiixPrivate = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;
    UNUSED UINT16 BmiCommand;
    UINT16 BmiStatus;
    UINT8 StatusValue; 
    UINT8 CommandValue;

    BmiCommand = SECONDARY_BMICOM_REGISTER(PiixPrivate);
    BmiStatus = SECONDARY_BMISTA_REGISTER(PiixPrivate);

    StatusValue = inb(BmiStatus);
    if(!(StatusValue & BMISTA_IDEINTR)){
        return;
    }

    outb(BmiStatus, BMISTA_IDEINTR | BMISTA_DMAERR);
    
    if(StatusValue & BMISTA_DMAERR){
        LouPrint("PIIX.SYS:DMAERR\n");
    }

    CommandValue = inb(BmiCommand);
    CommandValue &= ~BMICOM_SSBM;
    outb(BmiCommand, CommandValue);
    LouKeSignalEvent(&PiixPrivate->SecondaryEvent);
}


LOUSTATUS PiixInitializePiix3Xceleration(PLOUSINE_KERNEL_DEVICE_ATA_HOST AtaHost){
    LOUSTATUS Status;
    UINT16  Tmp;
    UINT8   MaxPio;
    UINT8   MaxUDma;
    PPCI_DEVICE_OBJECT PDEV = AtaHost->PDEV;
    BOOL Channel1Used;
    BOOL Channel2Used;
    LouKeMallocAtaPrivateData(AtaHost, sizeof(PIIX3_HOST_PRIVATE_DATA), GET_ALIGNMENT(PIIX3_HOST_PRIVATE_DATA));
    PPIIX3_HOST_PRIVATE_DATA PiixPrivateData = (PPIIX3_HOST_PRIVATE_DATA)AtaHost->HostPrivateData;

    LouKeInitializeEventTimeOut(&PiixPrivateData->PrimaryEvent, 10000);
    LouKeInitializeEventTimeOut(&PiixPrivateData->SecondaryEvent, 10000);

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
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxPioMode = MaxPio;
        }else{
            Channel2Used = true;
            ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxPioMode = MaxPio;
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
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, 2);
            }else{
                ((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[i].PortPrivateData)->MaxUDmaMode = MIN(MaxUDma, 2);
            }

        }
        AtaHost->Ports[i].DmaPort = true;
        memset(Buffer, 0, 512);
    }
    LouKeFree(Buffer);

    UINT16 Time;

    if(Channel1Used){

        LouPrint("PIIX.SYS:Primary Max PIO Mode:%d\n", MaxPio);
        LouPrint("PIIX.SYS:Primary Max UDMA Mode:%d\n", MaxUDma);

        if(AtaHost->Ports[0].DeviceAttached){
            PiixSetPrimaryMasterPioTiming(AtaHost, MaxPio);
        }

        if(AtaHost->Ports[1].DeviceAttached){
            PiixSetPrimarySlavePioTiming(AtaHost, MaxPio);
        }

        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[0].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE0;
            LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

            //AtaHost->Ports[0].Operations->IssueCommand = Piix3DmaIssueCommand;

        }


        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[1].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE1;
            LouKeWritePciUint16(PDEV, PRIMARY_IDETIM_REGISTER_OFFSET, Time);

            //AtaHost->Ports[1].Operations->IssueCommand = Piix3DmaIssueCommand;


        }
    
        //RegisterInterruptHandler(Piix3PrimaryInterruptHandler, 0x20 + 14, false, (UINT64)AtaHost);

    }

    if(Channel2Used){

        if(AtaHost->Ports[2].DeviceAttached){
            PiixSetSecondaryMasterPioTiming(AtaHost, MaxPio);
        }

        if(AtaHost->Ports[3].DeviceAttached){
            PiixSetSecondarySlavePioTiming(AtaHost, MaxPio);
        }
    

        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[2].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE0;
            LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);

            //AtaHost->Ports[2].Operations->IssueCommand = Piix3DmaIssueCommand;

        }


        if(((PPIIX3_HOST_PRIVATE_DATA)AtaHost->Ports[3].PortPrivateData)->MaxPioMode){
            
            UINT16 Time = LouKeReadPciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET);
            Time |= IDETIM_DTE1;
            LouKeWritePciUint16(PDEV, SECONDARY_IDETIM_REGISTER_OFFSET, Time);

            //AtaHost->Ports[3].Operations->IssueCommand = Piix3DmaIssueCommand;

        }

        //RegisterInterruptHandler(Piix3SecondaryInterruptHandler, 0x20 + 15, false, (UINT64)AtaHost);

    }

    LouKeHalPciSetMaster(PDEV);

    return STATUS_SUCCESS;
}
