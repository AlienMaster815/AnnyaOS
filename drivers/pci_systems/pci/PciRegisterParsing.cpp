#include <LouDDK.h>
#include <NtAPI.h>

//Up Until BAR0 everything is the same

uint32_t LouKeReadPciVendorId(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint32(PDEV, 0x00);
}

uint32_t LouKeReadPciDeviceId(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint32(PDEV, 0x02);
}

uint16_t LouKeReadCommandRegister(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint16(PDEV, 0x04);
}

uint16_t LouKeReadStatusRegister(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint16(PDEV, 0x06);
}

uint8_t LouKePciReadRevisionId(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x08);
}

uint8_t LouKePciReadProgIf(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x09);
}

uint8_t LouKePciReadSubClass(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0A);
}

uint8_t LouKePciReadClass(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0B);
}

//chae line size 0x0C
uint8_t LouKePciReadCahceLine(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0C);
}

//Latency Timer 0x0D
uint8_t LouKePciReadLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0D);
}
//Header Type 0x0E
uint8_t LouKePciReadHeaderType(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0E);
}
//BIST 0x0F
uint8_t LouKePciReadBist(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint8(PDEV, 0x0F);
}

uint32_t LouKePciReadCardbusCISPointer(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00){ //regular Device
        return LouKeReadPciUint32(PDEV, 0x28);
    }
    else{
        return 0x00; //null
    }
}

uint16_t LouKePciReadSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00)return LouKeReadPciUint16(PDEV, 0x2C);
    else if(HeaderType == 0x02)return LouKeReadPciUint16(PDEV, 0x42);
    else return 0x00; //null
}

uint16_t LouKePciReadSubsystemId(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00)return LouKeReadPciUint16(PDEV, 0x2E);
    else return 0x00; //null
}

uint32_t LouKePciReadRomBase(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00) return LouKeReadPciUint32(PDEV, 0x30);
    else if(HeaderType == 0x01) return LouKeReadPciUint32(PDEV, 0x38);
    else return 0x00; //null
}

uint8_t LouKePciReadCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00)return LouKeReadPciUint8(PDEV, 0x34);
    else if(HeaderType == 0x01)return LouKeReadPciUint8(PDEV, 0x34);
    else return 0x00;//NULL 
}

uint8_t LouKePciReadMinGrant(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00) return LouKeReadPciUint8(PDEV, 0x3E);
    else return 0x00;//NULL
}

uint8_t LouKePciReadMaxLatency(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x00) return LouKeReadPciUint8(PDEV, 0x3F);
    else return 0x00;//null
}

uint8_t LouKePciReadPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x01)return LouKeReadPciUint16(PDEV, 0x18);
    else if(HeaderType == 0x02)return LouKeReadPciUint16(PDEV, 0x18);
    else return 0x00;//null
}

uint8_t LouKePciReadSecondaryBus(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x01) return LouKeReadPciUint8(PDEV, 0x19);
    else return 0x00; //null
}

uint8_t LouKePciReadSubordinateBus(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x01) return LouKeReadPciUint8(PDEV, 0x20);
    else if(HeaderType == 0x02) return LouKeReadPciUint8(PDEV, 0x20);
    else return 0x00;//null
}

uint8_t LouKePciReadSecondLatencyTimer(PPCI_DEVICE_OBJECT PDEV){
    uint8_t HeaderType = LouKePciReadHeaderType(PDEV);
    if(HeaderType == 0x01)return LouKeReadPciUint8(PDEV, 0x21);
    else return 0x00;//null
}

void LouKeWritePciCommandRegister(PPCI_DEVICE_OBJECT PDEV,uint16_t Value){
    LouKeWritePciUint16(PDEV, 0x04, Value);
}

uint16_t LouKeReadPciCommandRegister(PPCI_DEVICE_OBJECT PDEV){
    return LouKeReadPciUint16(PDEV, 0x04);
}

uint32_t LouKeReadBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber){
   return LouKeReadPciUint32(PDEV, BAR0_OFFSET + (4 * BarNumber)); 
}

void LouKeWriteBarValue(PPCI_DEVICE_OBJECT PDEV, uint8_t BarNumber, uint32_t Value){
    LouKeWritePciUint32(PDEV, BAR0_OFFSET + (4 * BarNumber), Value); 
}

