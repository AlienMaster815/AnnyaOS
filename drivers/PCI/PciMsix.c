#include "PciMsi.h"


BOOLEAN PciMsixGetMsixCapPtr(PPCI_DEVICE_OBJECT PDEV, UINT16* Result){
    if((!Result) || (!PDEV)){
        return false;
    }
    *Result = PciHalGetCapabilitiesPointer(PDEV, PCI_CAPABILITY_MSI_X, false);   
    return true;
}

UINT16 PciMsixGetMessageControlEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr){
    return PciHalReadUint16(PDEV, CapPtr + PCI_MSIX_MESSAGE_CONTROL_OFFSET);
}

void PciMsixSetMessageControlEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Value){
    PciHalWriteUint16(PDEV, CapPtr + PCI_MSIX_MESSAGE_CONTROL_OFFSET, Value);
}

BOOLEAN PciMsixSetMessageControl(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    UINT16 CapPtr;
    if(!PDEV){
        return false;
    }
    if(!PciMsixGetMsixCapPtr(PDEV, &CapPtr)){
        return false;
    }
    if(!CapPtr){
        return false;
    }
    PciHalWriteUint16(PDEV, CapPtr + PCI_MSIX_MESSAGE_CONTROL_OFFSET, Value);
    return true;
}

BOOLEAN PciMsixGetMessageControl(PPCI_DEVICE_OBJECT PDEV, UINT16* Value){
    UINT16 CapPtr;
    if((!PDEV) || (!Value)){
        return false;
    }
    if(!PciMsixGetMsixCapPtr(PDEV, &CapPtr)){
        return false;
    }
    if(!CapPtr){
        return false;
    }
    *Value = PciHalReadUint16(PDEV, CapPtr + PCI_MSIX_MESSAGE_CONTROL_OFFSET);
    return true;
}
