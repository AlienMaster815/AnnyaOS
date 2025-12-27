#include "EHCI.h"

static void EhciPrintCapabilities(
    PEHCI_DEVICE    EhciDevice
){
    LouPrint("EHCI.SYS:EhciPrintCapabilities()\n");
    
    if(EhciDevice->Dma64Supported){
        LouPrint("EHCI.SYS:Ehci Controller Supports 64 Bit DMA Data Structures\n");
    }else{
        LouPrint("EHCI.SYS:Ehci Controller Does Not Support 64 Bit DMA Data Structures\n");
    }

    if(EhciDevice->PortIndicatorSupport){
        LouPrint("EHCI.SYS:Ehci Controller Supports Port Indicators\n");
    }else {
        LouPrint("EHCI.SYS:Ehci Controller Does Not Support Port Indicators\n");
    }

    if(EhciDevice->EhciRoutingThroughPORTROUTE){
        LouPrint("EHCI.SYS:Ehci Controller Routes Through HCSP-PORTROUTE\n");
    }else{
        LouPrint("EHCI.SYS:Ehci Controller Routes Through A Commpanion Hiarchy\n");
    }

    if(EhciDevice->PortPowerControlSupport){
        LouPrint("EHCI.SYS:Ehci Controller Supports Power Control\n");
    }else{
        LouPrint("EHCI.SYS:Ehci Controller Does Not Support Power Control\n");
    }

    if(EhciDevice->HighSpeedParkSupport){
        LouPrint("EHCI.SYS:Ehci Controller Supports High Speed Park\n");
    }else{
        LouPrint("EHCI.SYS:Ehci Controller Does Not Support High Speed Park\n");
    } 

    if(EhciDevice->SmallFrameSizeSupport){
        LouPrint("EHCI.SYS:Ehci Controller Supports Small Frame Lists\n");
    }else{
        LouPrint("EHCI.SYS:Ehci Controller Does Not Support Small Frame Lists\n");
    }

    LouPrint("EHCI.SYS:Ehci Controller Has %d Ports\n", EhciDevice->EhciPortCount);

    LouPrint("EHCI.SYS:Ehci Controller Has %d Ports Per Companion\n", EhciDevice->OhciPortMultiplier);
    
    LouPrint("EHCI.SYS:Ehci Controller Has %d Companions\n", EhciDevice->OhciCompanionCount);

    LouPrint("EHCI.SYS:Ehci Controllers Debug Port Is Port:%d\n", EhciDevice->DebugPort);

    LouPrint("EHCI.SYS:Ehci Controller Has EECP Information At PCI Config Offset:%h\n", EhciDevice->EecpPciCapPointer);

    LouPrint("EHCI.SYS:Ehci Controllers Isochronus Schedualing Threshold Value Is:%h\n", EhciDevice->Ist);

    LouPrint("EHCI.SYS:EhciPrintCapabilities() DONE\n");
}

void EhciGetHostCapabilities(PEHCI_DEVICE EhciDevice){
    LouPrint("EHCI.SYS:EhciGetHostCapabilities()\n");
    PEHCI_CAPABILITY_REGISTERS CapReg = EhciDevice->Capabilities;
    UINT32 HcsParams = CapReg->HcsParams;
    UINT32 HccParams = CapReg->HccParams;

    //LouPrint("EHCI.SYS:HcsParams:%bi\n", HcsParams);
    //LouPrint("EHCI.SYS:HccParams:%bi\n", HccParams);

    EhciDevice->Dma64Supported = EHCI_CAP_TO_BOOLEAN(EHCI_SUPPORTS_64BIT_DATA_STRUCTURES(HccParams));
    EhciDevice->PortIndicatorSupport = EHCI_CAP_TO_BOOLEAN(EHCI_SUPPORTS_P_INDICATOR(HcsParams));
    EhciDevice->EhciRoutingThroughPORTROUTE = EHCI_CAP_TO_BOOLEAN(EHCI_PORT_ROUTING_BY_HCSPP_PORTROUTE(HcsParams));
    EhciDevice->PortPowerControlSupport = EHCI_CAP_TO_BOOLEAN(EHCI_SUPPORTS_PPC(HcsParams));
    EhciDevice->HighSpeedParkSupport = EHCI_CAP_TO_BOOLEAN(EHCI_SUPPORTS_HIGH_SPEED_PARK(HccParams));
    EhciDevice->SmallFrameSizeSupport = EHCI_CAP_TO_BOOLEAN(EHCI_SUPPORTS_SMALL_FRAME_LISTS(HccParams));
    EhciDevice->EhciPortCount = EHCI_GET_N_PORTS(HcsParams);
    EhciDevice->OhciPortMultiplier = EHCI_GET_N_PCC(HcsParams);
    EhciDevice->OhciCompanionCount = EHCI_GET_N_CC(HcsParams);
    EhciDevice->DebugPort = EHCI_GET_DEBUG_PORT_NUMBER(HcsParams);
    EhciDevice->EecpPciCapPointer = EHCI_GET_EECP(HccParams);
    EhciDevice->Ist = EHCI_GET_IST(HccParams);

    EhciPrintCapabilities(EhciDevice);

    LouPrint("EHCI.SYS:EhciGetHostCapabilities() DONE\n");
}