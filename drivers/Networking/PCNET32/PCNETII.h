// im following the WYOOS tutorial for Device infomration
// all credit for hardware manipulation should go to the
// WYOOS creator
#ifndef _PCI_NET_32_H
#define _PCI_NET_32_H

typedef struct __attribute__((packed)) _PCNET2_INITIALIZATION_BLOCK{
    uint16_t        OperationMode;
    uint8_t         Reserved1           : 4;
    uint8_t         SendBufferCount     : 4;
    uint8_t         Reserved2           : 4;
    uint8_t         RecieveBufferCount  : 4;
    uint64_t        PhysicalAddress     : 48;
    uint16_t        Reserved3;
    uint64_t        LogicalAddress;
    uint32_t        RecieveBufferDescriptorAddress;
    uint32_t        SendBufferDescriptorAddress;
}PCNET2_INITIALIZATION_BLOCK, * PPCNET2_INITIALIZATION_BLOCK;

typedef struct __attribute__((packed)) _PCNET2_BUFFER_DESCRIPTOR{
    uint32_t        Address;
    uint32_t        FlagsLow;
    uint32_t        FlagsHigh;
    uint32_t        Available;
}PCNET2_BUFFER_DESCRIPTOR, * PPCNET2_BUFFER_DESCRIPTOR;

typedef struct _PCNET_II_DRIVER_DATA{
    PDEVICE_OBJECT                      PlatformDevice;
    PDRIVER_OBJECT                      DriverObject;
    uint16_t                            MacAddressPortWord0;
    uint16_t                            MacAddressPortWord1;
    uint16_t                            MacAddressPortWord2;
    uint16_t                            RegisterAddressPort;
    uint16_t                            RegisterDataPort;
    uint16_t                            ResetPort;
    uint16_t                            BusControllRegisterDataPort;
    uintptr_t                           SendComBuffers[8];
    uintptr_t                           ReciveComBuffers[8];
    uintptr_t                           SendDescriptors;
    uintptr_t                           ReciveDescriptors;
    PCNET2_INITIALIZATION_BLOCK         InitializationBlock;
    uint8_t                             ActiveSendBuffer;       //bitmask
    uint8_t                             ActiveRecieveBuffer;    //bitmask
}PCNET_II_DRIVER_DATA, * PPCNET_II_DRIVER_DATA;

NTSTATUS InitializePcNetIIDevice(
    PDRIVER_OBJECT DriverObject,
    PDEVICE_OBJECT PlatformDevice
);

#endif //_PCI_NET_32_H