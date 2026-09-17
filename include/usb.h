#ifndef _USB_CORE_H
#define _USB_CORE_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

struct _USB_HCD_OBJECT;

#ifndef _USER_MODE_CODE_


#define USBHCD_FLAGS_VERSION_MASK       0x0F
#define USBHCD_FLAGS_VERSION_SHIFT      0
#define USBHCD_FLAGS_GET_VERSION(f)     ((f >> USBHCD_FLAGS_VERSION_SHIFT) & USBHCD_FLAGS_VERSION_MASK)
#define USBHCD_FLAGS_SET_VERSION(x)     ((x & USBHCD_FLAGS_VERSION_MASK) << USBHCD_FLAGS_VERSION_SHIFT)

typedef enum {
    RHPORT_STATUS_NEEDS_RESET = 0,
    RHPORT_STATUS_RUNNING,
    RHPORT_STATUS_IDLE,
}RHPORT_STATUS;

struct _USB_DEVICE_OBJECT;

typedef struct _USB_ENDPOINT_OBJECT{

}USB_ENDPOINT_OBJECT, * PUSB_ENDPOINT_OBJECT;

#define USB_PIPE_FLAGS_INOUT_MASK           0x03
#define USB_PIPE_FLAGS_INOUT_SHIFT          0
#define USB_PIPE_FLAGS_GET_INOUT(f)         ((f >> USB_PIPE_FLAGS_INOUT_SHIFT) & USB_PIPE_FLAGS_INOUT_MASK)
#define USB_PIPE_FLAGS_SET_INOUT(x)         ((f & USB_PIPE_FLAGS_INOUT_MASK) << USB_PIPE_FLAGS_INOUT_SHIFT)
#define USB_PIPE_FLAGS_HAS_INPUT            0x01
#define USB_PIPE_FLAGS_HAS_OUTPUT           0x02
#define USB_PIPE_FLAGS_IOFLAG_TO_VECTOR(f)  (f - 1)


typedef struct _USB_PIPE_OBJECT{
    ListHeader              Peers;
    ULONG                   PipeFlags;
    PUSB_ENDPOINT_OBJECT    EndpointObject[2];
}USB_PIPE_OBJECT, * PUSB_PIPE_OBJECT;

typedef struct _USB_DEVICE_OBJECT{
    struct _USB_DEVICE_OBJECT*  Uplink;         //Hub or similar device (if connected)
    ListHeader                  Peers;          //Current Topology Peers
    ListHeader                  Subordinates;   //Subordinate members (if Hub or similar device)
    struct _USB_HCD_OBJECT*     Hcd;
    UINT8                       DeviceAddress;
    ListHeader                  PipeObjects;
    PVOID                       DevicePrivateData;
}USB_DEVICE_OBJECT, * PUSB_DEVICE_OBJECT;

typedef struct _USBHCD_OPERATIONS{
    //HCD Operations
    LOUSTATUS       (*ResetHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    LOUSTATUS       (*StartHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    LOUSTATUS       (*StopHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    //Roothub Operations
    RHPORT_STATUS   (*GetHcdRhPortStatus)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*ResetRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*StartRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*StopRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    //Device Operations
    LOUSTATUS       (*ConnectDevice)(PUSB_DEVICE_OBJECT Device);
    LOUSTATUS       (*DisconnectDevice)(PUSB_DEVICE_OBJECT Device);
    //Endpoint Operations
    LOUSTATUS       (*ConnectEndpoint)(PUSB_ENDPOINT_OBJECT Endpoint);
    LOUSTATUS       (*DisconnectEndpoint)(PUSB_ENDPOINT_OBJECT Endpoint);
}USBHCD_OPERATIONS, * PUSBHCD_OPERATIONS;

typedef struct _USB_HCD_OBJECT{
    PPCI_DEVICE_OBJECT  PDEV;
    ULONG               HcdFlags;
    ListHeader          Companions;
    XARRAY              DeviceAddressPool;
    ListHeader          HcdDevices;
    PVOID               HcdPrivateData;
}USB_HCD_OBJECT, * PUSB_HCD_OBJECT; 



#else //user mode code



#endif

#ifdef __cplusplus
}
#endif
#endif


/*#ifndef _USB_H
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

#ifndef _USBCORE_H

DRIVER_IMPORT
LOUSTATUS LouKeUsbAddHcd(
    PUSB_HOST_DEVICE    HostDevice
);

DRIVER_IMPORT
LOUSTATUS LouKeUsbAddDeviceToHcd(
    PUSB_HOST_DEVICE        HostDevice,
    PUSB_FUNCTION_DEVICE    ParrentFunction,
    PUSB_FUNCTION_DEVICE    DeviceDescription
);

DRIVER_IMPORT
LOUSTATUS LouKeUsbGetDescriptorRequest(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   DescriptorType,
    UINT8                   DescriptorIndex,
    UINT16                  Length,
    UINT16                  LanguageId,
    PVOID                   Data
);

DRIVER_IMPORT
LOUSTATUS LouKeUsbSetAddress(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewAddress
);

DRIVER_IMPORT
LOUSTATUS LouKeUsbSetConfiguration(
    PUSB_FUNCTION_DEVICE    FunctionDevice, 
    PUSB_HOST_IO_PACKET     IoPacket,
    UINT8                   NewConfig
);

#endif //usbcore



#else //USER

#endif

#ifdef __cplusplus
}
#endif
#endif
*/