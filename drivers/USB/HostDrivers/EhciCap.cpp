//Copyright GPL-2 Tyler Grenier (2025 - 2026)
#include "Ehci.h"

void EhciPrintCapabilities(
    PEHCI_DEVICE_CAPABILITIES Capabilities
){
    LouPrint("\n");
    LouPrint("START:EHCI_CAPS\n");
    LouPrint("EHCI Version:%d.%d\n", Capabilities->EhciMajorVersion, Capabilities->EhciMinorVersion);
    LouPrint("Number Of Ports:%d\n", Capabilities->NumberOfPorts);
    LouPrint("Ports Per Companion Controller:%d\n", Capabilities->PortsPerCompanionController);
    LouPrint("Number Of Companion Controllers:%d\n", Capabilities->NumberOfCompanionControllers);
    LouPrint("Debug Port Number:%d\n", Capabilities->DebugPortNumber);
    LouPrint("ISOCH Schedualing Threashold:%h\n", Capabilities->IsochronusSchedulingThreshold);
    LouPrint("Ehci Extended Cap Pointer:%h\n", Capabilities->EhciExtendedCapabilitiesPointer);

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PPC){
        LouPrint("Power Port Control Supported\n");
    }else{
        LouPrint("Power Port Control Not Supported\n");
    }

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_ROUTING_RULES){
        LouPrint("Has Port Routing Rules\n");
        LouPrint("Port Routing Data:%h\n", Capabilities->EhciOptionalPortRoute);
    }else{
        LouPrint("Does Not Have Port Routing Rules\n");
    }

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_INDICATORS){
        LouPrint("Has Port Indicators\n");
    }else{
        LouPrint("Does Not Have Port Indicators\n");
    }

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_64BIT_DMA){
        LouPrint("Supports Long Mode DMA\n");
    }else{
        LouPrint("Does Not Support Long Mode DMA\n");
    }

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PROGRAMMABLE_FRAME_LIST){
        LouPrint("Has Programmable Frame List\n");        
    }else{
        LouPrint("Does Not Have Programmable Frame List\n");        
    }

    if(Capabilities->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_ASYNC_SCHEDULE_PARK){
        LouPrint("Has Async Schedual Park\n");
    }else{
        LouPrint("Does Not Have Async Schedual Park\n");
    }

    LouPrint("ENDOF:EHCI_CAPS\n\n");    
}

void EhciGetHostCapabilities(PEHCI_DEVICE_OBJECT EhciObject){
    
    EhciObject->OperationalRegisters = (PEHCI_HOST_OPERATIONAL_REGISTERS)(UINT8*)(((UINT64)(UINT8*)EhciObject->CapabilitiesRegisters) + (UINT64)EhciObject->CapabilitiesRegisters->CapLength);
    PEHCI_CAPABILITY_REGISTERS CapRegs = EhciObject->CapabilitiesRegisters;    
    PEHCI_DEVICE_CAPABILITIES ObjCaps = &EhciObject->EhciDeviceCapabilities;
    UINT64 Tmp = CapRegs->HciVersion;
    
    ObjCaps->EhciMajorVersion = (Tmp >> 8) & 0xFF;
    ObjCaps->EhciMinorVersion = Tmp & 0xFF;
    
    Tmp = CapRegs->HcsParams;

    ObjCaps->NumberOfPorts = (Tmp >> EHCI_HCSPARAMS_N_PORTS_SHIFT) & EHCI_HCSPARAMS_N_PORTS_MASK;

    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCSPARAMS_PPC)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PPC : 0;
    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCSPARAMS_PRR)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_ROUTING_RULES : 0;

    ObjCaps->PortsPerCompanionController = (Tmp >> EHCI_HCSPARAMS_N_PCC_SHIFT) & EHCI_HCSPARAMS_N_PCC_MASK;
    ObjCaps->NumberOfCompanionControllers = (Tmp >> EHCI_HCSPARAMS_N_CC_SHIFT) & EHCI_HCSPARAMS_N_CC_MASK;
    
    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCSPARAMS_P_INDICATOR)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_INDICATORS : 0;

    ObjCaps->DebugPortNumber = (Tmp >> EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_SHIFT) & EHCI_HCSPARAMS_DEBUG_PORT_NUMBER_MASK;

    Tmp = CapRegs->HccParams;

    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCCPARAMS_64AC)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_64BIT_DMA : 0; 
    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCCPARAMS_PFLF)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PROGRAMMABLE_FRAME_LIST : 0; 
    ObjCaps->EhciMiscFlags |= (Tmp & (EHCI_HCCPARAMS_ASPC)) ? EHCI_DEVICE_CAPABILITIES_MISC_FLAG_ASYNC_SCHEDULE_PARK : 0; 

    ObjCaps->IsochronusSchedulingThreshold = (Tmp >> EHCI_HCCPARAMS_IST_SHIFT) & EHCI_HCCPARAMS_IST_MASK;
    ObjCaps->EhciExtendedCapabilitiesPointer = (Tmp >> EHCI_HCCPARAMS_EECP_SHIFT) & EHCI_HCCPARAMS_EECP_MASK;

    if(ObjCaps->EhciMiscFlags & EHCI_DEVICE_CAPABILITIES_MISC_FLAG_PORT_ROUTING_RULES){
        ObjCaps->EhciOptionalPortRoute = CapRegs->HcspPortRoute;
        ObjCaps->EhciOptionalPortRoute &= ((1ULL << 61) - 1);
    }

    EhciPrintCapabilities(ObjCaps);
}
