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
    RHPORT_STATUS_NO_DEVICE,
}RHPORT_STATUS;

struct _USB_DEVICE_OBJECT;
struct _USB_PIPE_OBJECT;

typedef enum {
    USB_ENDPOINT_DIRECTION_IN = 0,
    USB_ENDPOINT_DIRECTION_OUT,
}USB_ENDPOINT_DIRECTION;

typedef struct _USB_ENDPOINT_OBJECT{
    struct _USB_PIPE_OBJECT*    PipeObject;
    USB_ENDPOINT_DIRECTION      Direction;
    SIZE                        EndpointMaxBandwith;
    PVOID                       HcdEndpointPrivateData;
}USB_ENDPOINT_OBJECT, * PUSB_ENDPOINT_OBJECT;

#define USB_PIPE_FLAGS_INOUT_MASK           0x03
#define USB_PIPE_FLAGS_INOUT_SHIFT          0
#define USB_PIPE_FLAGS_GET_INOUT(f)         ((f >> USB_PIPE_FLAGS_INOUT_SHIFT) & USB_PIPE_FLAGS_INOUT_MASK)
#define USB_PIPE_FLAGS_SET_INOUT(x)         ((f & USB_PIPE_FLAGS_INOUT_MASK) << USB_PIPE_FLAGS_INOUT_SHIFT)
#define USB_PIPE_FLAGS_HAS_INPUT            0x01
#define USB_PIPE_FLAGS_HAS_OUTPUT           0x02
#define USB_PIPE_FLAGS_IOFLAG_TO_VECTOR(f)  (f - 1)

typedef struct _USB_PIPE_OBJECT{
    ListHeader                  Peers;
    struct _USB_DEVICE_OBJECT*  UsbDevice;
    SIZE                        PipeID; //ID for the endpoints
    ULONG                       PipeFlags;
    PVOID                       EpoHandle;
    PUSB_ENDPOINT_OBJECT        EndpointObject[2];
}USB_PIPE_OBJECT, * PUSB_PIPE_OBJECT;

typedef struct _USB_DEVICE_OBJECT{
    struct _USB_DEVICE_OBJECT*  Uplink;         //Hub or similar device (if connected)
    ListHeader                  Peers;          //Current Topology Peers
    ListHeader                  Subordinates;   //Subordinate members (if Hub or similar device)
    struct _USB_HCD_OBJECT*     Hcd;
    UINT8                       DeviceAddress;
    USB_PIPE_OBJECT             DefaultControlPipe;
    ListHeader                  PipeObjects;
    PVOID                       DevicePrivateData;
}USB_DEVICE_OBJECT, * PUSB_DEVICE_OBJECT;

typedef struct _USB_HCD_OPERATIONS{
    //HCD Operations
    LOUSTATUS       (*ResetHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    LOUSTATUS       (*StartHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    LOUSTATUS       (*StopHcdDevice)(struct _USB_HCD_OBJECT* Hcd);
    LOUSTATUS       (*HcdCreateEndpoint)(struct _USB_HCD_OBJECT* Hcd, PUSB_ENDPOINT_OBJECT NewEndpoint);
    LOUSTATUS       (*HcdDestroyEndpoint)(PUSB_ENDPOINT_OBJECT Endpoint);
    //Roothub Operations
    RHPORT_STATUS   (*GetHcdRhPortStatus)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*ResetRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*StartRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    LOUSTATUS       (*StopRhPort)(struct _USB_HCD_OBJECT* Hcd, UINT32 Port);
    //Transfer Operations
    LOUSTATUS       (*PrepTransfer)(struct _USB_TRANSFER_DATA* Transfer);
    LOUSTATUS       (*CommitTransfer)(struct _USB_TRANSFER_DATA* Transfer);
    LOUSTATUS       (*GetTransferStatus)(struct _USB_TRANSFER_DATA* Transfer);
}USB_HCD_OPERATIONS, * PUSB_HCD_OPERATIONS;

typedef struct _USB_HCD_OBJECT{
    ListHeader              Peers;
    PPCI_DEVICE_OBJECT      PDEV;
    SIZE                    DmaTransferMinimumAlignment;
    ULONG                   HcdFlags;
    ListHeader              Companions;
    PIDENTIFICATION_RANGE   DeviceAddresses;
    ListHeader              HcdDevices;
    PVOID                   HcdPrivateData;
    PUSB_HCD_OPERATIONS     Operations;
    LOUSINE_DMA_DEVICE      DmaDevice;
    SIZE                    HcdMaxBandwith;
    PTHREAD                 IoQueueManager;
    mutex_t                 IoQueueLock;
    ListHeader              IoQueueItems;
    PTHREAD                 IoDeQueueManager;
    mutex_t                 IoDeQueueLock;
    ListHeader              IoDeQueueItems;
    USB_DEVICE_OBJECT       DefaultDevice;
}USB_HCD_OBJECT, * PUSB_HCD_OBJECT; 


#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_DEVICE    0x00
#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_INTERFACE 0x01
#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_ENDPOINT  0x02
#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_OTHER     0x03

#define USB_DEVREQ_REQUEST_TYPE_REQUEST_STANDARD    0x00
#define USB_DEVREQ_REQUEST_TYPE_REQUEST_CLASS       0x01
#define USB_DEVREQ_REQUEST_TYPE_REQUEST_VENDOR      0x02

#define USB_DEVREQ_REQUEST_TYPE_DIRECTION_H2D       0x00
#define USB_DEVREQ_REQUEST_TYPE_DIRECTION_D2H       0x01

#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_SHIFT     0
#define USB_DEVREQ_REQUEST_TYPE_RECIPIENT_MASK      0x1F

#define USB_DEVREQ_REQUEST_TYPE_REQUEST_SHIFT       5
#define USB_DEVREQ_REQUEST_TYPE_REQUEST_MASK        0x03

#define USB_DEVREQ_REQUEST_TYPE_DIRECTION_SHIFT     7
#define USB_DEVREQ_REQUEST_TYPE_DIRECTION_MASK      1

#define USB_DEVREQ_ENCODE_REQUEST_TYPE(Recipient, Request, Direction)  (((Recipient & USB_DEVREQ_REQUEST_TYPE_RECIPIENT_MASK) << USB_DEVREQ_REQUEST_TYPE_RECIPIENT_SHIFT) | ((Request & USB_DEVREQ_REQUEST_TYPE_REQUEST_MASK) << USB_DEVREQ_REQUEST_TYPE_REQUEST_SHIFT) | ((Direction & USB_DEVREQ_REQUEST_TYPE_DIRECTION_MASK) << USB_DEVREQ_REQUEST_TYPE_DIRECTION_SHIFT))

#define USB_DEVREQ_REQUEST_GET_STATUS           0
#define USB_DEVREQ_REQUEST_CLEAR_FEATURE        1
#define USB_DEVREQ_REQEUST_SET_FEATURE          3
#define USB_DEVREQ_REQUEST_SET_ADDRESS          5
#define USB_DEVREQ_REQUEST_GET_DESCRIPTOR       6
#define USB_DEVREQ_REQUEST_SET_DESCRIPTOR       7
#define USB_DEVREQ_REQUEST_GET_CONFIGURATION    8
#define USB_DEVREQ_REQUEST_SET_CONFIGURATION    9
#define USB_DEVREQ_REQUEST_GET_INTERFACE        10
#define USB_DEVREQ_REQUEST_SET_INTERFACE        11
#define USB_DEVREQ_REQUEST_SYNC_FRAME           12

typedef struct _USB_TRANSFER_DATA{
    UINT64 Foo;
}USB_TRANSFER_DATA, * PUSB_TRANSFER_DATA;

#ifndef _USB_CORE_H

DRIVER_IMPORT LOUSTATUS UsbCoreCreateHcdObject(PPCI_DEVICE_OBJECT PDEV, ULONG Flags, PVOID PrivateData, PLOUSINE_DMA_DEVICE DmaDevice, PUSB_HCD_OPERATIONS Operations);

#else 

SIZE UsbCoreGetEndpointId(PUSB_ENDPOINT_OBJECT EndpointObject);
SIZE UsbCoreGetEndpointDeviceAddress(PUSB_ENDPOINT_OBJECT EndpointObject);
PUSB_DEVICE_OBJECT UsbCoreGetDeviceFromEndpoint(PUSB_ENDPOINT_OBJECT EndpointObject);

DRIVER_EXPORT LOUSTATUS UsbCoreCreateHcdObject(PPCI_DEVICE_OBJECT PDEV, ULONG Flags, PVOID PrivateData, PLOUSINE_DMA_DEVICE DmaDevice, PUSB_HCD_OPERATIONS Operations);

#endif

#else //user mode code

#endif

#ifdef __cplusplus
}
#endif
#endif
