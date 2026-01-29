#ifndef _USB_H
#define _USB_H

#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C"{
#endif

#ifndef _USER_MODE_CODE_

struct _USB_HUB_DEVICE;
struct _USB_FUNCTION_DEVICE;
struct _USB_TOPOLOGY_TREE;

#define USB_ENCODE_PID(Pid) ((UINT8)(((Pid) & 0x0F) | ((~(Pid) & 0x0F) << 4)))

#define USB_PID_TOKEN_OUT   0b0001
#define USB_PID_TOKEN_IN    0b1001
#define USB_PID_TOKEN_SOF   0b0101
#define USB_PID_TOKEN_SETUP 0b1101

#define USB_PID_DATA0       0b0011
#define USB_PID_DATA1       0b1011
#define USB_PID_DATA2       0b0111
#define USB_PID_MDATA       0b1111

#define USB_PID_ACK         0b0010
#define USB_PID_NAK         0b1010
#define USB_PID_STALL       0b1110
#define USB_PID_NYET        0b0110

#define USB_PID_PRE         0b1100
#define USB_PID_ERR         0b1100
#define USB_PID_SPLIT       0b1000
#define USB_PID_PING        0b1000

typedef struct _USB_TOKEN_PACKET{
    UINT8       Pid;
    UINT8       Address     :   7;
    UINT8       Endpoint    :   4;
    UINT8       Crc5        :   5;
}USB_TOKEN_PACKET, * PUSB_TOKEN_PACKET;

#define USB_FULL_SPEED 0
#define USB_LOW_SPEED  1

//Split Special Token
#define USB_SST_ENDPOINT_TYPE_CONTROL       0b00
#define USB_SST_ENDPOINT_TYPE_ISOCHRONOUS   0b01
#define USB_SST_ENDPOINT_TYPE_BULK          0b10
#define USB_SST_ENDPOINT_TYPE_INTERRUPT     0b11

typedef struct _USB_COMPLETE_SPLIT_TRANSACTION_TOKEN{
    UINT8       Pid;
    UINT8       HubAddress      :   7;
    UINT8       StartComplete   :   1;
    UINT8       Port            :   7;
    UINT8       Speed           :   1;
    UINT8       Unused          :   1;
    UINT8       EndpointType    :   2;
    UINT8       Crc5            :   5;
}USB_COMPLETE_SPLIT_TRANSACTION_TOKEN, * PUSB_COMPLETE_SPLIT_TRANSACTION_TOKEN;

typedef struct _USB_START_OF_FRAME_PACKET{
    UINT16      Pid;//UINT16 for MINGW Packing bug
    UINT16      FrameNumber     :   11;
    UINT16      Crc5            :   5;
}USB_START_OF_FRAME_PACKET, * PUSB_START_OF_FRAME_PACKET;

//Data Packet Pid 8 bits Data 0 to 8192 bits CRC16 16 bits

typedef struct _USB_START_SPLIT_TRANSACTION_TOKEN{
    UINT8       SplitPid;
    UINT8       HubAddress          :       7;
    UINT8       StartComplete       :       1;
    UINT8       Port                :       7;
    UINT8       Speed               :       1;
    UINT8       End                 :       1;
    UINT8       EndpointType        :       2;
    UINT8       Crc5                :       5;  
}USB_START_SPLIT_TRANSACTION_TOKEN, * PUSB_START_SPLIT_TRANSACTION_TOKEN;

#define USB_TRANSFER_TYPE_CONTROL   0
#define USB_TRANSFER_TYPE_BULK      1
#define USB_TRANSFER_TYPE_INTERRUPT 2
#define USB_TRANSFER_TYPE_ISOCH     3


typedef enum {
    UsbLowSpeedFunction = 0,
    UsbFullSpeedFunction = 1,
    UsbHighSpeedFunction = 2,
    UsbSuperSpeedFunction = 3,
}USB_FUNCTION_SPEED;

typedef struct _USB_FUNCTION_OPERATIONS{
    LOUSTATUS   (*UsbInitializeFunctionDevice)(struct _USB_FUNCTION_DEVICE* FunctionDevice);
}USB_FUNCTION_OPERATIONS, * PUSB_FUNCTION_OPERATIONS;

typedef struct _USB_BUS_INFORMATION{
    PIDENTIFICATION_RANGE   BusAddresses;
}USB_BUS_INFORMATION, * PUSB_BUS_INFORMATION;

typedef struct PACKED _USB_STANDARD_DEVICE_DESCRIPTOR{
    UINT8       Length;
    UINT8       DescriptorType;
    UINT16      BcdUSB;
    UINT8       DeviceClass;
    UINT8       DeviceSubClass;
    UINT8       DeviceProtocol;
    UINT8       MaxPacketSize;
    UINT16      VendorID;
    UINT16      ProductID;
    UINT16      BcdDevice;
    UINT8       Manufacturer;
    UINT8       Product;
    UINT8       SerialNumber;
    UINT8       NumConfigs;
}USB_STANDARD_DEVICE_DESCRIPTOR, * PUSB_STANDARD_DEVICE_DESCRIPTOR;

typedef struct PACKED _USB_STANDARD_CONFIGURATION_DESCRIPTOR{
    UINT8       Length;
    UINT8       DescriptorType;
    UINT16      TotalLength;
    UINT8       NumInterfaces;
    UINT8       ConfigurationValue;
    UINT8       Configuration;
    UINT8       Attributes;
    UINT8       MaxPower;
}USB_STANDARD_CONFIGURATION_DESCRIPTOR, * PUSB_STANDARD_CONFIGURATION_DESCRIPTOR;

typedef struct _USB_FUNCTION_DEVICE{
    struct _USB_TOPOLOGY_TREE*                  Children;
    PUSB_BUS_INFORMATION                        OptionalBusData;
    USB_FUNCTION_OPERATIONS                     Operations;
    UINT8                                       PortNumber;
    USB_FUNCTION_SPEED                          FunctionSpeed;
    BOOL                                        PortEnabled;
    UINT8                                       MaxPacketSize;
    PVOID                                       PrivateHostFunctionData;
    USB_STANDARD_DEVICE_DESCRIPTOR              DeviceDescriptor;
    PUSB_STANDARD_CONFIGURATION_DESCRIPTOR      Configurations;
}USB_FUNCTION_DEVICE, * PUSB_FUNCTION_DEVICE;

typedef struct _USB_TOPOLOGY_TREE{
    struct _USB_HOST_DEVICE*    HostIdentifier;
    struct _USB_TOPOLOGY_TREE*  ULink; //hub owner
    struct _USB_TOPOLOGY_TREE*  FLink; //next port
    struct _USB_TOPOLOGY_TREE*  BLink; //last port
    USB_FUNCTION_DEVICE         FunctionDevice;
}USB_TOPOLOGY_TREE, * PUSB_TOPOLOGY_TREE;


typedef struct _USB_HOST_OPERATIONS{
    LOUSTATUS       (*UsbHcdResetHostController)(struct _USB_HOST_DEVICE* HostDevice);
    LOUSTATUS       (*UsbHcdStopHostController)(struct _USB_HOST_DEVICE* HostDevice);
    LOUSTATUS       (*UsbHcdStartHostController)(struct _USB_HOST_DEVICE* HostDevice);
    LOUSTATUS       (*UsbHcdProbeRootHub)(struct _USB_HOST_DEVICE* HostDevice);
    LOUSTATUS       (*UsbHcdCommitRequest)(struct _USB_HOST_IO_PACKET* IoPacket);
}USB_HOST_OPERATIONS, * PUSB_HOST_OPERATIONS;

typedef struct _USB_HOST_DEVICE{
    struct _USB_HOST_DEVICE*        Siblings;
    struct _USB_HOST_DEVICE*        Leader;
    PPCI_DEVICE_OBJECT              PDEV;
    mutex_t                         ExlusiveOwnership;
    mutex_t                         RootHubMutex;
    USB_TOPOLOGY_TREE               RootHub;
    USB_HOST_OPERATIONS             Operations;
    PIDENTIFICATION_RANGE           BusAddresses;
    PVOID                           DevicePrivateData;
}USB_HOST_DEVICE, * PUSB_HOST_DEVICE;

typedef struct _USB_HOST_IO_PACKET{
    PUSB_FUNCTION_DEVICE    FunctionDevice;
    UINT8                   TransferType;
    UINT8                   RequestType;
    UINT8                   Request;
    UINT16                  Value;
    UINT16                  Index;
    UINT16                  Length;
    PVOID                   Data;
    UINT8                   ConditionCode;
}USB_HOST_IO_PACKET, * PUSB_HOST_IO_PACKET;

#define USB_REQUEST_RECIPIANT_SHIFT         0
#define USB_REQUEST_TYPE_SHIFT              5
#define USB_REQUEST_XFER_DIRECTION_SHIFT    7

#define USB_RECIPIANT_DEVICE        0
#define USB_RECIPIANT_INTERFACE     1
#define USB_RECIPIANT_ENDPOINT      2
#define USB_RECIPIANT_OTHER         3

#define USB_TYPE_STANDARD           0
#define USB_TYPE_CLASS              1
#define USB_TYPE_VENDOR             2

#define USB_XFER_H2D                        0
#define USB_XFER_D2H                        1 

#define USB_REQUEST_GET_STATUS              0
#define USB_REQUEST_CLEAR_FEATURE           1
#define USB_REQUEST_SET_FEATURE             3
#define USB_REQUEST_SET_ADDRESS             5
#define USB_REQUEST_GET_DESCRIPTOR          6
#define USB_REQUEST_SET_DESCRIPTOR          7
#define USB_REQUEST_GET_CONFIGURATION       8
#define USB_REQUEST_SET_CONFIGURATION       9
#define USB_REQUEST_GET_INTERFACE           10
#define USB_REQUEST_SET_INTERFACE           11
#define USB_REQUEST_SYNCH_FRAMS             12

#define USB_DESCRIPTOR_TYPE_DEVICE          1
#define USB_DESCRIPTOR_TYPE_CONFIGURATION   2
#define USB_DESCRIPTOR_TYPE_STRING          3
#define USB_DESCRIPTOR_TYPE_INTERFACE       4
#define USB_DESCRIPTOR_TYPE_ENDPOINT        5

#define USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP   1
#define USB_FEATURE_SELECTOR_ENDPOINT_STALL         0

#define UsbFunctionDeviceToHcd(pFunctionDevice) (((PUSB_TOPOLOGY_TREE)CONTAINER_OF(pFunctionDevice, USB_TOPOLOGY_TREE, FunctionDevice))->HostIdentifier)



#ifndef _KERNEL_MODULE_

LOUSTATUS LouKeUsbAddHcd(
    PUSB_HOST_DEVICE    HostDevice
);

LOUSTATUS LouKeUsbAddDeviceToHcd(
    PUSB_HOST_DEVICE        HostDevice,
    PUSB_FUNCTION_DEVICE    ParrentFunction,
    PUSB_FUNCTION_DEVICE    DeviceDescription
);

LOUSTATUS LouKeUsbGetDescriptorRequest(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   DescriptorType,
    UINT8                   DescriptorIndex,
    UINT16                  Length,
    UINT16                  LanguageId,
    PVOID                   Data
);

LOUSTATUS LouKeUsbSetAddress(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewAddress
);

LOUSTATUS LouKeUsbSetConfiguration(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewConfig
);

#else

KERNEL_EXPORT
LOUSTATUS LouKeUsbAddHcd(
    PUSB_HOST_DEVICE    HostDevice
);

KERNEL_EXPORT
LOUSTATUS LouKeUsbAddDeviceToHcd(
    PUSB_HOST_DEVICE        HostDevice,
    PUSB_FUNCTION_DEVICE    ParrentFunction,
    PUSB_FUNCTION_DEVICE    DeviceDescription
);

KERNEL_EXPORT
LOUSTATUS LouKeUsbGetDescriptorRequest(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   DescriptorType,
    UINT8                   DescriptorIndex,
    UINT16                  Length,
    UINT16                  LanguageId,
    PVOID                   Data
);

KERNEL_EXPORT
LOUSTATUS LouKeUsbSetAddress(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewAddress
);

KERNEL_EXPORT
LOUSTATUS LouKeUsbSetConfiguration(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewConfig
);

#endif

#else //USER

#endif

#ifdef __cplusplus
}
#endif
#endif