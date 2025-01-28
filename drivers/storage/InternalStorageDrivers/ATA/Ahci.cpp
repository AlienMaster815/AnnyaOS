#include <LouDDK.h>
#include <Hal.h>

typedef struct _AHCI_GENERIC_PRIVATE_DATA{
    AHCI_PRIVATE_DATA_TEMPLATE_HEADER   HostCapabilities;
    PAHCI_GENERIC_PORT                  AhciPort;
    uint32_t                            PortSignature;
    void*                               ClbVirtualAddress;
    void*                               FbVirtualAddress;
}AHCI_GENERIC_PORT_PRIVATE_DATA, * PAHCI_GENERIC_PORT_PRIVATE_DATA;

#define SATA_SIGNATURE_ATA      0x101
#define SATA_SIGNATURE_ATAPI    0xEB140101
#define SATA_SIGNATURE_SEMB     0xC33C0101
#define SATA_SIGNATURE_PM       0x96690101

#define HBA_PORT_IPM_ACTIVE     1
#define HBA_PORT_DET_PRESENT    3

static LOUSINE_ATA_PORT_OPERATIONS AhciGenericOperations;

static LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    LouPrint("AhciGenricDMAPrepCommand\n");
    while(1);
    return STATUS_SUCCESS;  
}


static LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("AhciaGenricDMAIssueCommand\n");
    while(1);
    return STATUS_SUCCESS;
}

static LOUSTATUS EnableAhciDevice(
    PAHCI_GENERIC_HOST_CONTROL Ghc, 
    PAHCI_GENERIC_PORT_PRIVATE_DATA Private
){

    if((Private->HostCapabilities.IsAnAhciOnlyDevice) || (Ghc->GlobalHostControl & (1 << 31))){
        return STATUS_SUCCESS;
    }
    LouPrint("TODO:Set AE Bit\n");


    return STATUS_SUCCESS;
}

static void AhciStartPort(PAHCI_GENERIC_PORT AhciPort){
    AhciPort->PxCMD |= AHCI_PxCMD_FRE;
    AhciPort->PxCMD |= AHCI_PxCMD_ST;
}

static LOUSTATUS AhciStopPort(PAHCI_GENERIC_PORT AhciPort){

    if(
        (AhciPort->PxCMD & (AHCI_PxCMD_ST))  || 
        (AhciPort->PxCMD & (AHCI_PxCMD_CR))  || 
        (AhciPort->PxCMD & (AHCI_PxCMD_FRE)) || 
        (AhciPort->PxCMD & (AHCI_PxCMD_FR))
    ){
        LouPrint("Controller Not IDLE Setting Controller To Idle\n");
        AhciPort->PxCMD &= ~(AHCI_PxCMD_ST);
        sleep(1000);
        if(AhciPort->PxCMD & (AHCI_PxCMD_CR)){
            LouPrint("ERROR:Could Not Set IDLE State\n");
            return STATUS_IO_DEVICE_ERROR;
        }

        AhciPort->PxCMD &= ~(AHCI_PxCMD_FRE);
        sleep(1000);
        if(AhciPort->PxCMD & (AHCI_PxCMD_FR)){
            LouPrint("ERROR:Could Not Set IDLE State\n");
            return STATUS_IO_DEVICE_ERROR;
        }
    }

    return STATUS_SUCCESS;
}

static LOUSTATUS PutAhciControllerInAKnownState(
    PAHCI_GENERIC_HOST_CONTROL Ghc,
    PLOUSINE_KERNEL_DEVICE_ATA_HOST AhciHost,
    uint8_t Count    
){
    uint8_t i;
    LOUSTATUS Status = STATUS_SUCCESS;

    for(i = 0; i < 32; i++){
        if(Ghc->PortsImplemented & (1 << i)){
            LouPrint("Setting Up Port:%d\n", i);
            PAHCI_GENERIC_PORT_PRIVATE_DATA PrivateData = (PAHCI_GENERIC_PORT_PRIVATE_DATA)AhciHost->Ports[i].PortPrivateData;
            PAHCI_GENERIC_PORT AhciPort = (PAHCI_GENERIC_PORT)((uintptr_t)Ghc + 0x100 + (i * 0x80));
            PrivateData->AhciPort = AhciPort;
            Status = AhciStopPort(AhciPort);
            if(Status != STATUS_SUCCESS){
                return Status;
            }
        }
    }
    return Status;
}

LOUSTATUS InitializeAhciDevice(P_PCI_DEVICE_OBJECT PDEV){
    LouPrint("Initializing Ahci Controller\n");
    LouKeHalEnablePciDevice(PDEV);
    LouKeHalPciSetMaster(PDEV);
    LOUSTATUS Status = STATUS_SUCCESS;
    UNUSED PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    uint8_t i;
    UNUSED PAHCI_GENERIC_HOST_CONTROL Ghc = (PAHCI_GENERIC_HOST_CONTROL)LouKeHalGetPciVirtualBaseAddress(CommonConfig, 5);
    if(!AHCI_SUPPORTS_S64A(Ghc->Capabilities)){
        LouPrint("This Driver Can Currently Only Drive 64 bit Addressing Systems\n");
    }

    uint8_t Count = 0;
    for(i = 0; i < 32; i++){
        if(Ghc->PortsImplemented & (1 << i)){
            Count++;
        }
    }

    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_HOST AhciHost = LouMallocAtaDevice(PDEV, Count);

    PAHCI_GENERIC_PORT_PRIVATE_DATA PrivateData = (PAHCI_GENERIC_PORT_PRIVATE_DATA)LouMalloc(sizeof(AHCI_GENERIC_HOST_CONTROL));
    AhciHost->HostPrivateData = (void*)PrivateData; 
    
    PrivateData->HostCapabilities.Supports64BitAddressing = AHCI_SUPPORTS_S64A(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsNativeCommandQueueing = AHCI_SUPPORTS_SNCQ(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsSNotificationRegister = AHCI_SUPPORTS_SSNTF(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsMechanicalPresenceSwitch = AHCI_SUPPORTS_SMPS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsStaggeredSpinup = AHCI_SUPPORTS_SSS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsAggresiveLinkPowerManagement = AHCI_SUPPORTS_SALP(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsActivityLED = AHCI_SUPPORTS_SAL(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsCommandListOveride = AHCI_SUPPORTS_SCLO(Ghc->Capabilities);
    PrivateData->HostCapabilities.MaximumInterfaceSpeedSupport = AHCI_GET_ISS(Ghc->Capabilities);
    PrivateData->HostCapabilities.IsAnAhciOnlyDevice = AHCI_SUPPORTS_SAM(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsPortMultiplier = AHCI_SUPPORTS_SPM(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsFisBasedSwitching = AHCI_SUPPORTS_FBSS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsMultiplePioDRQBlock = AHCI_SUPPORTS_PMD(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsSlumberState = AHCI_SUPPORTS_SSC(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsPartialState = AHCI_SUPPORTS_PSC(Ghc->Capabilities);
    PrivateData->HostCapabilities.NumberOfCommandSlots = AHCI_GET_NCS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsCommandCoalesing = AHCI_SUPPORTS_CCCS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsEnclosureManagement = AHCI_SUPPORTS_EMS(Ghc->Capabilities);
    PrivateData->HostCapabilities.SupportsExternalSata = AHCI_SUPPORTS_SXS(Ghc->Capabilities);
    PrivateData->HostCapabilities.ImplementedPorts = AHCI_GET_NP(Ghc->Capabilities);

    for(i = 0 ; i < AhciHost->PortCount; i++){
        AhciHost->Ports[i].PortPrivateData = (void*)LouMalloc(sizeof(AHCI_GENERIC_HOST_CONTROL));
        PrivateData = (PAHCI_GENERIC_PORT_PRIVATE_DATA)AhciHost->Ports[i].PortPrivateData;
        PrivateData->HostCapabilities.Supports64BitAddressing = AHCI_SUPPORTS_S64A(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsNativeCommandQueueing = AHCI_SUPPORTS_SNCQ(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsSNotificationRegister = AHCI_SUPPORTS_SSNTF(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsMechanicalPresenceSwitch = AHCI_SUPPORTS_SMPS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsStaggeredSpinup = AHCI_SUPPORTS_SSS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsAggresiveLinkPowerManagement = AHCI_SUPPORTS_SALP(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsActivityLED = AHCI_SUPPORTS_SAL(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsCommandListOveride = AHCI_SUPPORTS_SCLO(Ghc->Capabilities);
        PrivateData->HostCapabilities.MaximumInterfaceSpeedSupport = AHCI_GET_ISS(Ghc->Capabilities);
        PrivateData->HostCapabilities.IsAnAhciOnlyDevice = AHCI_SUPPORTS_SAM(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsPortMultiplier = AHCI_SUPPORTS_SPM(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsFisBasedSwitching = AHCI_SUPPORTS_FBSS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsMultiplePioDRQBlock = AHCI_SUPPORTS_PMD(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsSlumberState = AHCI_SUPPORTS_SSC(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsPartialState = AHCI_SUPPORTS_PSC(Ghc->Capabilities);
        PrivateData->HostCapabilities.NumberOfCommandSlots = AHCI_GET_NCS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsCommandCoalesing = AHCI_SUPPORTS_CCCS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsEnclosureManagement = AHCI_SUPPORTS_EMS(Ghc->Capabilities);
        PrivateData->HostCapabilities.SupportsExternalSata = AHCI_SUPPORTS_SXS(Ghc->Capabilities);
        PrivateData->HostCapabilities.ImplementedPorts = AHCI_GET_NP(Ghc->Capabilities);
    }

    Status = EnableAhciDevice(Ghc, PrivateData);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    PutAhciControllerInAKnownState(Ghc, AhciHost, Count);

    for(i = 0 ; i < Count; i++){
        if(Ghc->PortsImplemented & (1 << i)){
            //Allocate 1 Kilobyte Memory
            PrivateData = (PAHCI_GENERIC_PORT_PRIVATE_DATA)AhciHost->Ports[i].PortPrivateData;  
            UNUSED PAHCI_GENERIC_PORT AhciPort = PrivateData->AhciPort;

            PrivateData->ClbVirtualAddress = LouKeMalloc(1 * KILOBYTE, UNCACHEABLE_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
            PrivateData->FbVirtualAddress = LouKeMalloc(256, UNCACHEABLE_PAGE | WRITEABLE_PAGE | PRESENT_PAGE);
            //Allocations 0 memmory before use so im not going to zero the memory
            uint64_t ClbPhysicalAddress;
            uint64_t FbPhysicalAddress;

            RequestPhysicalAddress((uint64_t)PrivateData->ClbVirtualAddress, &ClbPhysicalAddress);
            RequestPhysicalAddress((uint64_t)PrivateData->FbVirtualAddress, &FbPhysicalAddress);

            AhciPort->PxCLB = ClbPhysicalAddress & 0xFFFFFFFF; 
            AhciPort->PxCLBU = (ClbPhysicalAddress >> 32) & 0xFFFFFFFF;
            sleep(500);

            uint32_t Serr = AhciPort->PxSERR;
            AhciPort->PxSERR = Serr;
            sleep(500);
            if(AhciPort->PxSERR){
                LouPrint("ERROR:Error Values Were Unable To Be Cleared\n");
                while(1);
                return STATUS_IO_DEVICE_ERROR;
            }

            LouPrint("Identifing Ports\n");
            uint32_t SSTS = AhciPort->PxSSTS;
            uint8_t  Ipm  = (SSTS >> 8) & 0x0F;
            uint8_t  Det  = SSTS & 0x0F;

            if(Det != HBA_PORT_DET_PRESENT){
                LouPrint("No Device Linked To Port:%d\n", i);
                continue;
            } 
            if(Ipm != HBA_PORT_IPM_ACTIVE){
                LouPrint("Device Connected To Port %d But Device Is Turned Off\n", i);
                continue;
            }   

            PrivateData->PortSignature = AhciPort->PxSIG; 
            switch(PrivateData->PortSignature){
                case SATA_SIGNATURE_ATAPI:
                    AhciHost->Ports[i].PortScsiDevice = true;
                    LouPrint("SATAPI Device Detected On Port:%d\n", i);
                    break;
                case SATA_SIGNATURE_SEMB:
                    AhciHost->Ports[i].PortScsiDevice = false;
                    LouPrint("SEMB Device Detected On Port:%d\n", i);
                    break;
                case SATA_SIGNATURE_PM:
                    AhciHost->Ports[i].PortScsiDevice = false;
                    LouPrint("PORT MULTIPLIER Device Detected On Poty:%d\n", i);
                    break;
                default:
                    AhciHost->Ports[i].PortScsiDevice = false;
                    LouPrint("SATA Device Detected On Port:%d\n", i);
            }

            PHBA_COMMAND_TABLE NewAllocatedTable = LouKeAhciMallocCommandTable(8);
            PHBA_COMMAND_HEADER CommandHeader = (PHBA_COMMAND_HEADER)PrivateData->ClbVirtualAddress; 
            uint64_t NewTable;
            RequestPhysicalAddress((uint64_t)NewAllocatedTable, &NewTable);
            for(uint8_t i = 0; i < 8; i++){
                CommandHeader->PhyRegionLength = 8;
                CommandHeader->CommandTableDescriptorBaseAddrressL = NewTable & 0xFFFFFFFF;
                CommandHeader->CommandTableDescriptorBaseAddrressU = (NewTable >> 32) & 0xFFFFFFFF;
            }
            AhciStartPort(AhciPort);
            AhciHost->Ports[i].Operations = &AhciGenericOperations;
        }
    }

    AhciGenericOperations.PrepCommand = AhciGenricDMAPrepCommand;
    AhciGenericOperations.IssueCommand = AhciGenricDMAIssueCommand;
    

    LouPrint("Adding Ahci Device To Device Manager\n");    
    LouKeRegisterDevice(
        PDEV, 
        ATA_DEVICE_T,
        "Annya/System64/Drivers/AhciGeneric.sys",
        (void*)AhciHost,
        0x00
    );

    LouPrint("Ahci Setup Success\n");
    return Status;
}