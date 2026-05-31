#include "Xhci.h"

static void XhciPrintCapabilities(
    PXHCI_DEVICE XhciDevice
){
    LouPrint("XHCI.SYS:Device Capabilities\n\n");
    
    LouPrint("XHCI.SYS:DEV_CAP:Version       :%h\n", XhciDevice->Capabilities.Version);
    LouPrint("XHCI.SYS:DEV_CAP:MaxSlots      :%d\n", XhciDevice->Capabilities.MaxSlots);
    LouPrint("XHCI.SYS:DEV_CAP:MaxInterrupts :%d\n", XhciDevice->Capabilities.MaxInterrupts);
    LouPrint("XHCI.SYS:DEV_CAP:MaxPorts      :%d\n", XhciDevice->Capabilities.MaxPorts);

    LouPrint("XHCI.SYS:DEV_CAP:IST           :%d\n", XhciDevice->Capabilities.IsochSchedThreshold);
    LouPrint("XHCI.SYS:DEV_CAP:ErstMax       :%d\n", XhciDevice->Capabilities.ErstMax);
    LouPrint("XHCI.SYS:DEV_CAP:MaxScrPadLo   :%d\n", XhciDevice->Capabilities.MaxScratchpageBufsLo);
    LouPrint("XHCI.SYS:DEV_CAP:MaxScrPadHi   :%d\n", XhciDevice->Capabilities.MaxScratchpageBufsHi);
    LouPrint("XHCI.SYS:DEV_CAP:ScrPadRestore :%d\n", XhciDevice->Capabilities.ScratchpadRestore);

    LouPrint("XHCI.SYS:DEV_CAP:U1ExitLatency :%d\n", XhciDevice->Capabilities.U1DeviceExitLatency);
    LouPrint("XHCI.SYS:DEV_CAP:U2ExitLatency :%d\n", XhciDevice->Capabilities.U2DeviceExitLatency);



    LouPrint("\nXHCI.SYS:ENDOF Device Capabilities\n");
}

LOUSTATUS 
XhciGetCapabilities(
    PXHCI_DEVICE     XhciDevice
){
    PXHCI_CAPABILITIES_REGISTER CapRegs = XhciDevice->CapRegisters;
    UINT32 Tmp;
    XhciDevice->Capabilities.Version = CapRegs->HciVersion;

    Tmp = CapRegs->HcsParams1;
    XhciDevice->Capabilities.MaxSlots = (UINT8)((Tmp >> XHCI_CAP_MAX_DEVICE_SLOTS_SHIFT) & XHCI_CAP_MAX_DEVICE_SLOTS_MASK);
    XhciDevice->Capabilities.MaxInterrupts = (UINT16)((Tmp >> XHCI_CAP_MAX_INTERRUPTS_SHIFT) & XHCI_CAP_MAX_INTERRUPTS_MASK);
    XhciDevice->Capabilities.MaxPorts = (UINT8)((Tmp >> XHCI_CAP_MAX_PORTS_SHIFT) & XHCI_CAP_MAX_PORTS_MASK);

    Tmp = CapRegs->HcsParams2;
    XhciDevice->Capabilities.IsochSchedThreshold = (UINT8)((Tmp >> XHCI_CAP_IST_SHIFT) & XHCI_CAP_IST_MASK);
    XhciDevice->Capabilities.ErstMax = (UINT8)((Tmp >> XHCI_CAP_MAX_ERST_SHIFT) & XHCI_CAP_MAX_ERST_MASK);
    XhciDevice->Capabilities.MaxScratchpageBufsLo = (UINT8)((Tmp >> XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO_SHIFT) & XHCI_CAP_MAX_SCRATCHPAD_BUFFERSLO_MASK);
    XhciDevice->Capabilities.MaxScratchpageBufsHi = (UINT8)((Tmp >> XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_SHIFT) & XHCI_CAP_MAX_SCRATCHPAD_BUFFERSHI_MASK);
    XhciDevice->Capabilities.ScratchpadRestore = ((Tmp & XHCI_CAP_SCRATCHPAD_RESTORE) ? true : false);

    Tmp = CapRegs->HcsParams3;
    XhciDevice->Capabilities.U1DeviceExitLatency = (UINT8)((Tmp >> XHCI_CAP_U1_DEV_EXIT_LATENCY_SHIFT) & XHCI_CAP_U1_DEV_EXIT_LATENCY_MASK);
    XhciDevice->Capabilities.U2DeviceExitLatency = (UINT8)((Tmp >> XHCI_CAP_U2_DEV_EXIT_LATENCY_SHIFT) & XHCI_CAP_U2_DEV_EXIT_LATENCY_MASK);

    XhciPrintCapabilities(XhciDevice);

    return STATUS_SUCCESS;
}