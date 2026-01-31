#include <LouDDK.h>
#include <Hal.h>



LOUDDK_API_ENTRY 
LOUSTATUS 
PciTestAtaConfigurationBits(
    PPCI_DEVICE_OBJECT PDEV, 
    PPCI_BIT_TEST_PACKET Packet
){
    PPCI_BITS Bits = Packet->Bits;

    UINT32 Result = 0;
    switch(Bits->Width){
        case sizeof(UINT8):  //1
            Result = LouKeReadPciUint8(PDEV, Bits->Register);
            break;
        case sizeof(UINT16): //2
            Result = LouKeReadPciUint16(PDEV, Bits->Register);
            break;
        case sizeof(UINT32): //4
            Result = LouKeReadPciUint32(PDEV, Bits->Register);
            break;
        default:
            return STATUS_INVALID_PARAMETER;
    }
    Packet->Result = ((Result & Bits->Mask) == Bits->Value);
    return STATUS_SUCCESS;
}
