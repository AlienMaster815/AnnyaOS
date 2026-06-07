#include "Xhci.h"

static void XhciPrintCapabilities(
    PXHCI_DEVICE XhciDevice
){
    LouPrint("XHCI.SYS:Device Capabilities\n\n");
    
    LouPrint("XHCI.SYS:DEV_CAP:Version                          :%h\n", XhciDevice->Capabilities.Version);
    LouPrint("XHCI.SYS:DEV_CAP:MaxSlots                         :%d\n", XhciDevice->Capabilities.MaxSlots);
    LouPrint("XHCI.SYS:DEV_CAP:MaxInterrupts                    :%d\n", XhciDevice->Capabilities.MaxInterrupts);
    LouPrint("XHCI.SYS:DEV_CAP:MaxPorts                         :%d\n", XhciDevice->Capabilities.MaxPorts);

    LouPrint("XHCI.SYS:DEV_CAP:IST                              :%d\n", XhciDevice->Capabilities.IsochSchedThreshold);
    LouPrint("XHCI.SYS:DEV_CAP:ErstMax                          :%d\n", XhciDevice->Capabilities.ErstMax);
    LouPrint("XHCI.SYS:DEV_CAP:MaxScrPadLo                      :%d\n", XhciDevice->Capabilities.MaxScratchpageBufsLo);
    LouPrint("XHCI.SYS:DEV_CAP:MaxScrPadHi                      :%d\n", XhciDevice->Capabilities.MaxScratchpageBufsHi);
    LouPrint("XHCI.SYS:DEV_CAP:ScrPadRestore                    :%d\n", XhciDevice->Capabilities.ScratchpadRestore);

    LouPrint("XHCI.SYS:DEV_CAP:U1ExitLatency                    :%d\n", XhciDevice->Capabilities.U1DeviceExitLatency);
    LouPrint("XHCI.SYS:DEV_CAP:U2ExitLatency                    :%d\n", XhciDevice->Capabilities.U2DeviceExitLatency);

    LouPrint("XHCI.SYS:Long Mode DMA Supported                  :%d\n", XhciDevice->Capabilities.Dma64Supported);
    LouPrint("XHCI.SYS:Bandwidth Negotiation Supported          :%d\n", XhciDevice->Capabilities.BncSupport);
    LouPrint("XHCI.SYS:64 Bit Context Size Supported            :%d\n", XhciDevice->Capabilities.Context64Byte);
    LouPrint("XHCI.SYS:Power Port Control Supported             :%d\n", XhciDevice->Capabilities.PortPowerControlSupport);
    LouPrint("XHCI.SYS:Port Indicators Supported                :%d\n", XhciDevice->Capabilities.PortIndicatorSupport);
    LouPrint("XHCI.SYS:Light HC Reset Supported                 :%d\n", XhciDevice->Capabilities.LightHCResetSupport);
    LouPrint("XHCI.SYS:Latency Tolerance Messageing Supported   :%d\n", XhciDevice->Capabilities.LtcSupport);
    LouPrint("XHCI.SYS:No Secondary SID Supported               :%d\n", XhciDevice->Capabilities.NssSupport);
    LouPrint("XHCI.SYS:Parse All Event Data Supported           :%d\n", XhciDevice->Capabilities.PaeSupport);
    LouPrint("XHCI.SYS:Stopped Short Packet Supported           :%d\n", XhciDevice->Capabilities.SpcSupport);
    LouPrint("XHCI.SYS:Stoped EDTLA Supported                   :%d\n", XhciDevice->Capabilities.SecSupport);
    LouPrint("XHCI.SYS:Contiguous Frame ID Supported            :%d\n", XhciDevice->Capabilities.CfcSupport);
    LouPrint("XHCI.SYS:Max PSA Size                             :%h\n", XhciDevice->Capabilities.MaxPsaSize);
    LouPrint("XHCI.SYS:xECP Pointer                             :%h\n", XhciDevice->Capabilities.xEcp);

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

    Tmp = CapRegs->HccParams1;
    XhciDevice->Capabilities.Dma64Supported = ((Tmp & XHCI_CAP_AC64) ? true : false);
    XhciDevice->Capabilities.BncSupport = ((Tmp & XHCI_CAP_BNC) ? true : false);
    XhciDevice->Capabilities.Context64Byte = ((Tmp & XHCI_CAP_CZS) ? true : false);
    XhciDevice->Capabilities.PortPowerControlSupport = ((Tmp & XHCI_CAP_PPC) ? true : false);
    XhciDevice->Capabilities.PortIndicatorSupport = ((Tmp & XHCI_CAP_PIND) ? true : false);
    XhciDevice->Capabilities.LightHCResetSupport = ((Tmp & XHCI_CAP_LHRC) ? true : false);
    XhciDevice->Capabilities.LtcSupport = ((Tmp & XHCI_CAP_LTC) ? true : false);
    XhciDevice->Capabilities.NssSupport = ((Tmp & XHCI_CAP_NSS) ? true : false);
    XhciDevice->Capabilities.PaeSupport = ((Tmp & XHCI_CAP_PAE) ? true : false);
    XhciDevice->Capabilities.SpcSupport = ((Tmp & XHCI_CAP_SPC) ? true : false);
    XhciDevice->Capabilities.SecSupport = ((Tmp & XHCI_CAP_SEC) ? true : false);
    XhciDevice->Capabilities.CfcSupport = ((Tmp & XHCI_CAP_CFC) ? true : false);
    XhciDevice->Capabilities.MaxPsaSize = (UINT8)((Tmp >> XHCI_CAP_MAX_PSA_SIZE_SHIFT) & XHCI_CAP_MAX_PSA_SIZE_MASK);
    XhciDevice->Capabilities.xEcp = (UINT16)((Tmp >> XHCI_CAP_XECP_SHIFT) & XHCI_CAP_XECP_MASK);

    XhciPrintCapabilities(XhciDevice);

    return STATUS_SUCCESS;
}