

#include "PciMsi.h"

BOOLEAN PciMsiGetMsiCapPtr(PPCI_DEVICE_OBJECT PDEV, UINT16* Result){
    if((!Result) || (!PDEV)){
        return false;
    }
    *Result = PciHalGetCapabilitiesPointer(PDEV, PCI_CAPABILITY_MSI, false);   
    return true;
}

UINT16 PciMsiGetMessageControlEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr){
    return PciHalReadUint16(PDEV, CapPtr + PCI_MSI_MESSAGE_CONTROL_OFFSET);
}

void PciMsiSetMessageControlEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Value){
    PciHalWriteUint16(PDEV, CapPtr + PCI_MSI_MESSAGE_CONTROL_OFFSET, Value);
}

UINT64 PciMsiGetMessageAddressEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    UINT64 Result = PciHalReadUint32(PDEV, CapPtr + PCI_MSI_MESSAGE_ADDRESS_LOW_OFFSET);
    if(MessageControl & PCI_MSI_MSG_CTRL_64BIT){
        Result |= ((UINT64)PciHalReadUint32(PDEV, CapPtr + PCI_MSI_MESSAGE_ADDRESS_LOW_OFFSET) << 32);
    }
    return Result;
}

BOOLEAN PciMsiSetMessageAddressEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT64 Value){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    BOOLEAN LongModeSupport = MessageControl & PCI_MSI_MSG_CTRL_64BIT;
    if((Value > UINT32_MAX) && (!LongModeSupport)){
        return false;
    }
    PciHalWriteUint32(PDEV, CapPtr + PCI_MSI_MESSAGE_ADDRESS_LOW_OFFSET, Value & UINT32_MAX);
    if(LongModeSupport){
        PciHalWriteUint32(PDEV, CapPtr + PCI_MSI_MESSAGE_ADDRESS_HIGH_OFFSET, (Value >> 32) & UINT32_MAX);
    }
    return true;
}

UINT16 PciMsiGetMessageDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    UINT16 Offset = PCI_MSI_MESSAGE_DATA_OFFSET;
    if(MessageControl & PCI_MSI_MSG_CTRL_64BIT){
        Offset += PCI_MSI_MESSAGE_LONG_MODE_SHIFT;
    }
    return PciHalReadUint16(PDEV, CapPtr + Offset);
}

void PciMsiSetMessageDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Value){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    UINT16 Offset = PCI_MSI_MESSAGE_DATA_OFFSET;
    if(MessageControl & PCI_MSI_MSG_CTRL_64BIT){
        Offset += PCI_MSI_MESSAGE_LONG_MODE_SHIFT;
    }
    PciHalWriteUint16(PDEV, CapPtr + Offset, Value);
}

BOOLEAN PciMsiGetMaskDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16* Result){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    if(!(MessageControl & PCI_MSI_MSG_CTRL_64BIT)){
        return false;
    }
    *Result = PciHalReadUint16(PDEV, CapPtr + PCI_MSI_MASK_OFFSET);
    return true;
}

BOOLEAN PciMsiSetMaskDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Value){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    if(!(MessageControl & PCI_MSI_MSG_CTRL_64BIT)){
        return false;
    }
    PciHalWriteUint16(PDEV, CapPtr + PCI_MSI_MASK_OFFSET, Value);
    return true;
}

BOOLEAN PciMsiGetPendingDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16* Result){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    if(!(MessageControl & PCI_MSI_MSG_CTRL_64BIT)){
        return false;
    }
    *Result = PciHalReadUint16(PDEV, CapPtr + PCI_MSI_PENDING_OFFSET);
    return true;
}

BOOLEAN PciMsiSetPendingDataEx(PPCI_DEVICE_OBJECT PDEV, UINT16 CapPtr, UINT16 Value){
    UINT16 MessageControl = PciMsiGetMessageControlEx(PDEV, CapPtr);
    if(!(MessageControl & PCI_MSI_MSG_CTRL_64BIT)){
        return false;
    }
    PciHalWriteUint16(PDEV, CapPtr + PCI_MSI_PENDING_OFFSET, Value);
    return true;
}

BOOLEAN PciMsiGetMessageControl(PPCI_DEVICE_OBJECT PDEV, UINT16* Result){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    *Result = PciMsiGetMessageControlEx(PDEV, CapPtr);
    return true;
}

BOOLEAN PciMsiSetMessageControl(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    PciMsiSetMessageControlEx(PDEV, CapPtr, Value);
    return true;
}

BOOLEAN PciMsiGetMessageAddress(PPCI_DEVICE_OBJECT PDEV, UINT64* Result){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    *Result = PciMsiGetMessageAddressEx(PDEV, CapPtr);
    return true;
}

BOOLEAN PciMsiSetMessageAddress(PPCI_DEVICE_OBJECT PDEV, UINT64 Value){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    return PciMsiSetMessageAddressEx(PDEV, CapPtr, Value);
}

BOOLEAN PciMsiGetMessageData(PPCI_DEVICE_OBJECT PDEV, UINT16* Result){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    *Result = PciMsiGetMessageDataEx(PDEV, CapPtr);
    return true;
}

BOOLEAN PciMsiSetMessageData(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    PciMsiSetMessageDataEx(PDEV, CapPtr, Value);
    return true;
}

BOOLEAN PciMsiGetMaskData(PPCI_DEVICE_OBJECT PDEV, UINT16* Result){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    return PciMsiGetMaskDataEx(PDEV, CapPtr, Result);
}

BOOLEAN PciMsiSetMaskData(PPCI_DEVICE_OBJECT PDEV, UINT16 Value){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return false;
    }else if(!CapPtr){
        return false;
    }
    return PciMsiSetMaskDataEx(PDEV, CapPtr, Value);
}

UINT8 PciMsiGetMultiMessageCount(PPCI_DEVICE_OBJECT PDEV){
    UINT16 CapPtr;
    if(!PciMsiGetMsiCapPtr(PDEV, &CapPtr)){
        return 0x00;
    }else if(!CapPtr){
        return 0x00;
    }
    SIZE Control = PciMsiGetMessageControlEx(PDEV, CapPtr);
    Control >>= 1;
    Control &= 0x07;
    return(UINT8)ToThePowerOf2(Control);
}