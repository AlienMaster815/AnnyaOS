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

//static LOUSINE_ATA_PORT_OPERATIONS AhciGenericOperations;

LOUSTATUS AhciGenricDMAPrepCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){  
    LouPrint("AhciGenricDMAPrepCommand\n");
    while(1);
    return STATUS_SUCCESS;  
}


LOUSTATUS AhciGenricDMAIssueCommand(
    PATA_QUEUED_COMMAND QueuedCommand
){
    LouPrint("AhciaGenricDMAIssueCommand\n");
    while(1);
    return STATUS_SUCCESS;
}

LOUSTATUS EnableAhciDevice(
    PAHCI_GENERIC_HOST_CONTROL Ghc, 
    PAHCI_GENERIC_PORT_PRIVATE_DATA Private
){

    if((Private->HostCapabilities.IsAnAhciOnlyDevice) || (Ghc->GlobalHostControl & (1 << 31))){
        return STATUS_SUCCESS;
    }
    LouPrint("TODO:Set AE Bit\n");


    return STATUS_SUCCESS;
}

void AhciStartPort(PAHCI_GENERIC_PORT AhciPort){
    AhciPort->PxCMD |= AHCI_PxCMD_FRE;
    AhciPort->PxCMD |= AHCI_PxCMD_ST;
}

LOUSTATUS AhciStopPort(PAHCI_GENERIC_PORT AhciPort){

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

LOUSTATUS PutAhciControllerInAKnownState(
    PAHCI_GENERIC_HOST_CONTROL Ghc
){
    uint8_t i;
    LOUSTATUS Status = STATUS_SUCCESS;

    for(i = 0; i < 32; i++){
        if(Ghc->PortsImplemented & (1 << i)){
            LouPrint("Setting Up Port:%d\n", i);
            PAHCI_GENERIC_PORT AhciPort = (PAHCI_GENERIC_PORT)((uintptr_t)Ghc + 0x100 + (i * 0x80));
            Status = AhciStopPort(AhciPort);
            if(Status != STATUS_SUCCESS){
                return Status;
            }
        }
    }
    return Status;
}

LOUDDK_API_ENTRY
PLOUSINE_KERNEL_DEVICE_ATA_HOST
LouMallocAtaDeviceWitPortMap(P_PCI_DEVICE_OBJECT PDEV, uint8_t PortCount, uint32_t PortMap);

LOUSTATUS InitializeAhciDevice(P_PCI_DEVICE_OBJECT PDEV){
    LouPrint("Initializing Ahci Controller\n");
    LouKeHalEnablePciDevice(PDEV);
    LouKeHalPciSetMaster(PDEV);
    LOUSTATUS Status = STATUS_SUCCESS;
    UNUSED PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;
    UNUSED uint8_t i;
    UNUSED PAHCI_GENERIC_HOST_CONTROL Ghc = (PAHCI_GENERIC_HOST_CONTROL)LouKeHalGetPciVirtualBaseAddress(CommonConfig, 5);
    if(!AHCI_SUPPORTS_S64A(Ghc->Capabilities)){
        LouPrint("This Driver Can Currently Only Drive 64 bit Addressing Systems\n");
    }

    UNUSED PLOUSINE_KERNEL_DEVICE_ATA_HOST AhciHost = LouMallocAtaDeviceWitPortMap(PDEV, 32, Ghc->PortsImplemented);

/*
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
*/
 
    LouPrint("Ahci Setup Success\n");
    return Status;
}