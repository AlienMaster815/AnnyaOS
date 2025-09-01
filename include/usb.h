#ifndef _USB_H
#define _USB_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef void(*USB_COMPLETE)(struct _URB*);
 
typedef enum{
    USB_STATE_NOT_ATTACHED          = 0,
    USB_STATE_ATTACHED              = 1,
    USB_STATE_POWERED               = 2,
    USB_STATE_RECONNECTING          = 3,
    USB_STATE_UN_AUTHENTICATED      = 4,
    USB_STATE_DEFAULT               = 5,
    USB_STATE_ADDRESS               = 6,
    USB_STATE_CONFIGURED            = 7,
    USB_STATE_SUSPENDED             = 8,
}USB_DEVICE_STATE;

typedef enum {
    USB_SSP_GEN_UNKOWN = 0,
    USB_SSP_GEN_2x1 = 1,
    USB_SSP_GEN_1x2 = 2,
    USB_SSP_GEN_2x2 = 3,
}USB_SSP_RATE;

typedef enum {
    USB_SPEED_UNKOWN = 0,
    USB_SPEED_LOW = 1,
    USB_SPEED_FULL = 2,
    USB_SPEED_HIGH = 3,
    USB_SPEED_SUPER = 4,
    USB_SPEED_SUPER_PLUS = 5,
}USB_DEVICE_SPEED;

typedef struct _MON_BUS{
    ListHeader          BusLink;
    spinlock_t          MonBuasLock;
    struct _USB_BUS*    UsbBus;
    int                 TextInitialized;
    int                 BinaryInitialized;
    FILE*               DebugFile;
    FILE*               TextInterfaceFile;
    #ifdef __cplusplus  //C++ only recognizes platform devices
    PDEVICE_OBJECT      ClassDevice;
    #else
    void*               ClassDevice;
    #endif
    int                 ReaderCount;
    ListHeader          ReaderList;
    void*               KernelReference;
    uint32_t            EventCount;
    uint32_t            LostTextCount;
}MON_BUS, * PMON_BUS;

typedef struct _USB_BUS{
    void*                   ControllerDevice;
    void*                   SystemDevice;
    int                     BusNumber;
    string                  BusName;
    uint8_t                 PioForControl;
    uint8_t                 OtgPortCount;
    uint8_t                 BusFlags;
    size_t                  ScatterGatherSize;
    int                     NextDeviceNumber;
    mutex_t                 NextDeviceNumberMutex;
    uint8_t                 DeviceMap[128/8];//bitmap 128 bits
    struct _USB_DEVICE*     RootHub;
    struct _USB_BUS*        HsCompanion;
    int                     BandwithAllocated;
    int                     BandwithInterrupts;
    int                     BandwithIsoc;
    PMON_BUS                MonBus;
    int                     Monitored;
}USB_BUS, * PUSB_BUS;

typedef struct _USB_ANCHOR{
    ListHeader      UrbList;
    LOUQ_WAIT       WaitQueue;
    spinlock_t      WaitLock;
    atomic_t        SuspendWakeupCount;
    bool            Poisoned;
}USB_ANCHOR, * PUSB_ANCHOR;

typedef struct _USB_TT{
    struct _USB_DEVICE*         UsbHub;
    int                         Multiple;
    uint64_t                    ReactionDelay;
    void*                       HostControllerPrivateData;
    spinlock_t                  TtLock;
    ListHeader                  ClearList;
    LOUQ_WORK                   ClearWork;  
}USB_TT, * PUSB_TT;

typedef struct _USB_GADGET{
    uint8_t                         Afinity;
    void*                           NonUsbPhyData;
    struct _USB_PHY_LAYER_CHAIN*    PhyTree;
    struct _USB_BUS*                UsbHost;
    struct _USB_GADGET*             GadgetList;
    uint8_t                         GadgetState;
    LOUSTATUS                       (*SetHostBinding)(struct _USB_OTG* Otg, struct _USB_BUS* HostBus);
    LOUSTATUS                       (*SetPeripheralBind)(struct _USB_OTG* Otg, struct _USB_GADGET*  Gadget);
    LOUSTATUS                       (*SetVBus)(struct _USB_OTG* Otg, bool Powermode);
    LOUSTATUS                       (*StartHostSession)(struct _USB_OTG* Otg);
    LOUSTATUS                       (*StartHNPRoleSwitch)(struct _USB_OTG* Otg);
}USB_GADGET, * PUSB_GADGET;

typedef struct _USB_OTG{
    uint8_t                         Default;
    struct _USB_PHY_LAYER_CHAIN*    PhyTree;
    struct _USB_BUS*                HostBus;
    PUSB_GADGET                     UsbGadget;
    uint8_t                         OtgState;
    LOUSTATUS                       (*SetHostBinding)(struct _USB_OTG* Otg, struct _USB_BUS* HostBus);
    LOUSTATUS                       (*SetPeripheralBind)(struct _USB_OTG* Otg, struct _USB_GADGET*  Gadget);
    LOUSTATUS                       (*SetVBus)(struct _USB_OTG* Otg, bool Powermode);
    LOUSTATUS                       (*StartHostSession)(struct _USB_OTG* Otg);
    LOUSTATUS                       (*StartHNPRoleSwitch)(struct _USB_OTG* Otg);
}USB_OTG, *PUSB_OTG;

typedef struct _USB_PHY_LAYER_IO_OPERATIONS{
    LOUSTATUS   (*UsbRead)(struct _USB_PHY_LAYER_CHAIN* TreeMember, uint32_t Register);
    LOUSTATUS   (*UsbWrite)(struct _USB_PHY_LAYER_CHAIN* TreeMember, uint32_t Register, uint32_t Value);
}USB_PHY_LAYER_IO_OPERATIONS, * PUSB_PHY_LAYER_IO_OPERATIONS;

typedef struct _CURRENT_USB_CHARGER{
    uint32_t    SdpMinimum;
    uint32_t    SdpMaximum;
    uint32_t    DcpMinimum;
    uint32_t    DcpMaximum;
    uint32_t    CdpMinimum;
    uint32_t    CdpMaximum;
    uint32_t    AcaMimimum;
    uint32_t    AcaMaximum;
}CURRENT_USB_CHARGER, * PCURRENT_USB_CHARGER;

typedef struct _USB_PHY_LAYER_CHAIN{
    struct _USB_PHY_LAYER_CHAIN*                PhyChain;
    #ifdef __cplusplus
    PDEVICE_OBJECT                              Device;
    PDEVICE_OBJECT                              IoDevice;
    #else
    void*                                       Device;
    void*                                       IoDevice;
    #endif
    string                                      Label;
    uint32_t                                    Flags;
    uint8_t                                     PhyType;
    uint8_t                                     LastUsbPhyEvent;
    PUSB_OTG                                    Otg;
    PUSB_PHY_LAYER_IO_OPERATIONS                IoOperations;
    void*                                       IoMemory;
    PEXTERNALLY_CONNECTED_DEVICE                ExternalDevice;
    PEXTERNALLY_CONNECTED_DEVICE                IDExternalDevice;
    PLOUSINE_KERNEL_NOTIFICATION_BLOCK          IdNotificationBlock;
    PLOUSINE_KERNEL_NOTIFICATION_BLOCK          TypeNotificationBlock;
    uint8_t                                     UsbChargerType;
    uint8_t                                     UsbChargerState;
    CURRENT_USB_CHARGER                         CurrentChargerState;
    PLOUQ_WORK                                  ChargerWork;
    PLOUSINE_KERNEL_ATOMIC_NOTIFICATION_HEAD    PhyLayerEvents;
    uint16_t                                    PortStatus;
    uint16_t                                    PortChange;
    struct _USB_PHY_LAYER_CHAIN*                PhyTree;
    LOUSTATUS                                   (*PhyLayerInitialize)(struct _USB_PHY_LAYER_CHAIN* TreeMember);
    void                                        (*PhyLayerShutDown)(struct _USB_PHY_LAYER_CHAIN* TreeMember);
    LOUSTATUS                                   (*SetVBus)(struct _USB_PHY_LAYER_CHAIN* TreeMember, bool PowerMode);
    LOUSTATUS                                   (*SetPowerRegulator)(struct _USB_PHY_LAYER_CHAIN* TreeMember, uint64_t MillaAmpere);
    LOUSTATUS                                   (*SetSuspendMode)(struct _USB_PHY_LAYER_CHAIN* TreeMember, bool SuspendEnabled);
    LOUSTATUS                                   (*SendWakeup)(struct _USB_PHY_LAYER_CHAIN* TreeMember, bool PowerMode);
    LOUSTATUS                                   (*NotifyConnection)(struct _USB_PHY_LAYER_CHAIN* TreeMember, uint8_t DeviceSpeed);
    LOUSTATUS                                   (*NotifyDisconnection)(struct _USB_PHY_LAYER_CHAIN* TreeMember, uint8_t DeviceSpeed);
    uint8_t                                     (*DetectCharger)(struct _USB_PHY_LAYER_CHAIN* TreeMember);
}USB_PHY_LAYER_CHAIN, * PUSB_PHY_LAYER_CHAIN;

typedef struct _USB_PHY_LAYER_ROOTHUB_CHAIN{
    void*           PhyStrcuture;
    ListHeader      PhyList;
}USB_PHY_LAYER_ROOTHUB_CHAIN, * PUSB_PHY_LAYER_ROOTHUB_CHAIN;

typedef struct PACKED _USB_ENDPOINT_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         EndpointAddress;
    uint8_t         Attributes;
    uint16_t        MaxPacketSize;
    uint8_t         Interval;
    uint8_t         Refresh;
    uint8_t         SyncAddress;
}USB_ENDPOINT_DESCRIPTOR, * PUSB_ENDPOINT_DESCRIPTOR;

typedef struct PACKED _USB_SS_ENDPOINT_COMP_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         MaxBurst;
    uint8_t         Attributes;
    uint16_t        BytesPerInterval;
}USB_SS_ENDPOINT_COMP_DESCRIPTOR, * PUSB_SS_ENDPOINT_COMP_DESCRIPTOR;

typedef struct PACKED _USB_SSP_ISOC_ENDPOINT_COMP_DESCRIPTROR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint16_t        Reserved;
    uint32_t        BPI;
}USB_SSP_ISOC_ENDPOINT_COMP_DESCRIPTROR, * PUSB_SSP_ISOC_ENDPOINT_COMP_DESCRIPTROR;

typedef struct _USB_ENDPOINT_DEVICE{
    PUSB_ENDPOINT_DESCRIPTOR    Descriptor;
    struct _USB_DEVICE*         UsbDevice;
    #ifdef __cplusplus
    PDEVICE_OBJECT              Device;
    #else
    void*                       Device;
    #endif
}USB_ENDPOINT_DEVICE, * PUSB_ENDPOINT_DEVICE;

typedef struct _USB_ISO_PACKET_DECRIPTOR{
    uint32_t    Offset;
    uint32_t    Length;
    uint32_t    ActualLength;
    int         Status;
}USB_ISO_PACKET_DECRIPTOR, * PUSB_ISO_PACKET_DECRIPTOR;

typedef struct _USB_HOST_ENDPOINT{
    USB_ENDPOINT_DESCRIPTOR                     EndpointDescriptor;
    USB_SS_ENDPOINT_COMP_DESCRIPTOR             SsEndpointComp;
    USB_SSP_ISOC_ENDPOINT_COMP_DESCRIPTROR      SsIsoc;
    ListHeader                                  UrbList;
    void*                                       HcdPrivateData;
    PUSB_ENDPOINT_DEVICE                        EndpointDevice;
    uint8_t*                                    ExtraDescriptors;
    int                                         ExtraDescriptorLength;
    int                                         Enabled;
    int                                         StreamCount;
}USB_HOST_ENDPOINT, * PUSB_HOST_ENDPOINT;

typedef struct _URB{
    void*                           KernelReference;
    int                             UnlinkedErrorCode;
    void*                           HostControllerPrivateData;
    atomic_t                        UseCount;
    atomic_t                        RejectCount;
    ListHeader                      UrbList;
    ListHeader                      AnchorList;
    PUSB_ANCHOR                     Anchor;
    struct _USB_DEVICE*             UsbDevice;
    PUSB_HOST_ENDPOINT              Endpoint;
    uint32_t                        PipeInformation;
    uint32_t                        StreamID;
    int                             Status;
    uint32_t                        TransferFlags;
    PSCATTER_GATHER_LIST            ScatterGatherList;
    int                             MappedScatterGatherCount;
    int                             ScatterGatherCount;
    uint32_t                        TransferLength;
    uint32_t                        ActualTransferLength;
    uint8_t*                        SetupPacket;
    uintptr_t                       SetupDmaAddress;
    int                             StartFrame;
    int                             NumberOfPackets;
    int                             Interval;
    int                             ErrorCount;
    void*                           Context;
    USB_COMPLETE                    Complete;
    USB_ISO_PACKET_DECRIPTOR        IsoFrameDescriptor[];
}URB, * PURB;

typedef struct PACKED _USB_DEVICE_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint16_t        BcdUDB;
    uint8_t         DeviceClass;
    uint8_t         DeviceSubClass;
    uint8_t         DeviceProtocol;
    uint8_t         MaxPacketSize0;
    uint16_t        VendorIdentification;
    uint16_t        ProductIdentification;
    uint16_t        BcdDevice;
    uint8_t         Manufacturer;
    uint8_t         Product;
    uint8_t         SerialNumber;
    uint8_t         ConfigurationCount;
}USB_DEVICE_DESCRIPTOR, * PUSB_DEVICE_DESCRIPTOR;

typedef struct PACKED _USB_BOS_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint16_t        TotalLength;
    uint8_t         DeviceCapCount;
}USB_BOS_DESCRIPTOR, * PUSB_BOS_DESCRIPTOR;

typedef struct PACKED _USB_EXTENDED_CAP_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         DeviceCapabilityType;
    uint32_t        Attributes;
}USB_EXTENDED_CAP_DESCRIPTOR, * PUSB_EXTENDED_CAP_DESCRIPTOR;

typedef struct PACKED _USB_SS_CAP_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         DeviceCapabilitiesType;
    uint16_t        SpeedSupported;
    uint8_t         FunctionalitySupport;
    uint8_t         U1DeviceExitLatency;
    uint16_t        U2DeviceExitLatency;
}USB_SS_CAP_DESCRIPTOR, * PUSB_SS_CAP_DESCRIPTOR;

typedef struct PACKED _USB_SSP_CAP_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         DeviceCapabilityType;
    uint8_t         Reserved;
    uint32_t        Attributes;
    uint16_t        FunctionalitySupport;
    uint16_t        Reserved2;
    uint32_t        SublinkSpeedAttributes[];
}USB_SSP_CAP_DESCRIPTOR, * PUSB_SSP_CAP_DESCRIPTOR;

typedef struct PACKED _USB_PTM_CAP_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         DeviceCapabilityType; 
}USB_PTM_CAP_DESCRIPTOR, * PUSB_PTM_CAP_DESCRIPTOR;

typedef struct PACKED _USB_SS_CONTAINER_ID_DESCRIPTOR{
    uint8_t         Length;
    uint8_t         DescriptorType;
    uint8_t         DeviceCapabilitiesType;
    uint8_t         Reserved;
    uint8_t         ContainerID[16];
}USB_SS_CONTAINER_ID_DESCRIPTOR, * PUSB_SS_CONTAINER_ID_DESCRIPTOR;

typedef struct _USB_HOST_BOS{
    PUSB_BOS_DESCRIPTOR             BosDescriptor;
    PUSB_EXTENDED_CAP_DESCRIPTOR    BosExtendedCap;
    PUSB_SS_CAP_DESCRIPTOR          BosSsCapDescriptor;
    PUSB_SSP_CAP_DESCRIPTOR         BosSspCapDescriptor;
    PUSB_SS_CONTAINER_ID_DESCRIPTOR SsIdentification;
    PUSB_PTM_CAP_DESCRIPTOR         BosPtmCapDescriptor;
}USB_HOST_BOS, * PUSB_HOST_BOS;

typedef struct PACKED _USB_CONFIGURATION_DESCRIPTOR{
    uint8_t     Length;
    uint8_t     DescriptorType;
    uint16_t    TotalLength;
    uint8_t     InterfaceCount;
    uint8_t     ConfigurationValue;
    uint8_t     Configuration;
    uint8_t     Attributes;
    uint8_t     MaxPower;
}USB_CONFIGURATION_DESCRIPTOR, * PUSB_CONFIGURATION_DESCRIPTOR;

typedef struct PACKED _USB_INTERFACE_ASSOC_DESCRIPTOR{
    uint8_t     Length;
    uint8_t     DescriptorType;
    uint8_t     FirstInterface;
    uint8_t     InterfaceCount;
    uint8_t     FunctionClass;
    uint8_t     FunctionSubClass;
    uint8_t     FunctionProtocol;
    uint8_t     Function;
}USB_INTERFACE_ASSOC_DESCRIPTOR, * PUSB_INTERFACE_ASSOC_DESCRIPTOR;

typedef struct PACKED _USB_INTERFACE_DESCRIPTOR{
    uint8_t     Length;
    uint8_t     DescriptorType;
    uint8_t     InterfaceID;
    uint8_t     AlternateSettings;
    uint8_t     EndpointCount;
    uint8_t     InterfaceClass;
    uint8_t     InterfaceSubClass;
    uint8_t     InterfaceProtocol;
    uint8_t     Interface;
}USB_INTERFACE_DESCRIPTOR, * PUSB_INTERFACE_DESCRIPTOR;

typedef struct _USB_HOST_INTERFACE{
    USB_INTERFACE_DESCRIPTOR    Descriptor;
    int                         ExtraLength;
    uint8_t*                    ExtraDescriptors;
    PUSB_HOST_ENDPOINT          Endpoint;
    string                      InterfaceString;
}USB_HOST_INTERFACE, * PUSB_HOST_INTERFACE;

typedef struct _USB_INTERFACE{
    PUSB_HOST_INTERFACE                 AlternateSettings;
    PUSB_HOST_INTERFACE                 CurrentAlternateSettings;
    uint64_t                            AlternateSettingsCount;
    PUSB_INTERFACE_ASSOC_DESCRIPTOR     InterfaceAssociation;
    int                                 Minor;
    uint8_t                             InterfaceCondition;
    uint64_t                            Flags;
    uint8_t                             WirelessStatus;
    PLOUQ_WORK                          WirelessStatusWork;
    #ifdef __cplusplus
    PDEVICE_OBJECT                      Device;
    PDEVICE_OBJECT                      UsbDevice;
    #else
    void*                               Device;
    void*                               UsbDevice;
    #endif
    PLOUQ_WORK                          ResetWork;
}USB_INTERFACE, * PUSB_INTERFACE;

typedef struct _USB_INTERFACE_CACHE{
    uint64_t            AlternateSettingsCount;
    void*               KernelReference;
    USB_HOST_INTERFACE  AlternateSettings;
}USB_INTERFACE_CACHE, * PUSB_INTERFACE_CACHE;

typedef struct _USB_HOST_CONFIGURATION{
    USB_CONFIGURATION_DESCRIPTOR        Descriptor;
    string                              ConfigurationString;
    PUSB_INTERFACE_ASSOC_DESCRIPTOR     InterfaceAssoc[16];
    PUSB_INTERFACE                      Interface[32];
    PUSB_INTERFACE_CACHE                InterfaceCache[32];
    uint8_t*                            ExtraDescriptors;
    int                                 ExtraLength;
}USB_HOST_CONFIGURATION, PUSB_HOST_CONFIGURATION;

typedef struct _USB2_LOW_POWER_MODE_PARAMETERS{
    uint32_t        Besl;
    int             Timeout;
}USB2_LOW_POWER_MODE_PARAMETERS, * PUSB2_LOW_POWER_MODE_PARAMETERS;

typedef struct _USB3_LOW_POWER_MODE_PARAMETERS{
    uint32_t        MEL;
    uint32_t        PEL;
    uint32_t        SEL;
    int             Timeout;
}USB3_LOW_POWER_MODE_PARAMETERS, * PUSB3_LOW_POWER_MODE_PARAMETERS;


typedef struct _USB_DEVICE{
    int                             DeviceNumber;
    string                          DevicePath;
    uint32_t                        Route;
    USB_DEVICE_STATE                UsbDeviceState;
    USB_DEVICE_SPEED                Speed;
    atomic_t                        UrbNumber;
    uint32_t                        RxLanes;
    uint32_t                        TxLanes;
    USB_SSP_RATE                    SspRate;
    PUSB_TT                         Tt;
    int                             TtPort;
    uint32_t                        Toggle[2];
    struct _USB_DEVICE*             Parent;
    struct _USB_DEVICE*             UsbDevice;
    USB_HOST_ENDPOINT               Endpoint0;
    PUSB_BUS                        UsbBus;
    USB_DEVICE_DESCRIPTOR           DeviceDescriptor;
    PUSB_HOST_BOS                   UsbBos;
    PUSB_HOST_CONFIGURATION         HostConfiguration;
    PUSB_HOST_CONFIGURATION         ActConfiguration;
    PUSB_HOST_ENDPOINT              InputEndpoint[16];
    PUSB_HOST_ENDPOINT              OutputEndpoint[16];
    string*                         RawDescriptors;
    uint16_t                        BusMillaAmperes;
    uint8_t                         PortID;
    uint8_t                         Level;
    uint8_t                         DeviceAddress;
    uint16_t                        UsbDeviceFlags1;
    int                             StringLangID;
    string                          ProductID;
    string                          Manufacturer;
    string                          Serial;
    ListHeader                      FileList;
    int                             MaxChildren;
    uint32_t                        QuirkFlags;
    uint32_t                        ActiveDuration;
    uint32_t                        ConnectionTime;
    uint8_t                         UsbDeviceFlags2;
    uint8_t                         TunnelMode;  
    int                             SlotIdentification;
    USB2_LOW_POWER_MODE_PARAMETERS  L1Parameter;
    USB3_LOW_POWER_MODE_PARAMETERS  U1Parameter;
    USB3_LOW_POWER_MODE_PARAMETERS  U2Parameter;
    uint64_t                        LowPowerModeDisableCount;
    uint16_t                        HubDelay;
    bool                            GenericDriverInUse;
}USB_DEVICE, * PUSB_DEVICE;


typedef struct _GIVEBACK_URB_BH{
    bool                Running;
    bool                HighPriority;
    spinlock_t          BhLock;
    ListHeader          Urbs;
    LOUQ_WORK           Bh;
    PUSB_HOST_ENDPOINT  CompletingEndpoint;
}GIVEBACK_URB_BH, * PGIVEBACK_URB_BH;

typedef struct _PUSB_HOST_CONTROLLER_DEVICE{
    string                              ProductDescriptor;    
    PPCI_DEVICE_OBJECT                  PDEV;
    BOOL                                AmdResumeBug;
    USB_BUS                             UsbSelf;
    KERNEL_REFERENCE                    KRef;
    int32_t                             Speed;
    uint8_t                             InterruptDescriptors[24];
    ListHeader                          RootHubPolls;
    bool                                UsesNewPoling;
    bool                                MsiEnabled;
    PURB                                StatusUrb;
    PLOUQ_WORK                          WakeyWork;
    PLOUQ_WORK                          DeathWork;
    struct _USB_HOST_CONTROLLER_DRIVER*  HcdDriver;
    PUSB_PHY_LAYER_CHAIN                UsbPhyLayer;
    PUSB_PHY_LAYER_ROOTHUB_CHAIN        UsbRootHubPhyLayer;
    uint16_t                            Flags;
    uint8_t                             DevicePolicy;
    uint16_t                            HCDS; //host controller driver settings
    size_t                              AllocatedIrqs;
    void*                               DeviceMemory;
    uintptr_t                           IoRegionBase;
    size_t                              IoRegionLimit;
    uint64_t                            MillaAmpereRation;
    GIVEBACK_URB_BH                     HighPriorityBh;
    GIVEBACK_URB_BH                     LowPriorityBh;
    mutex_t*                            Address0Mutex;
    mutex_t*                            BandwithMutex;
    struct _PUSB_HOST_CONTROLLER_DEVICE*  PrimaryHcd;
    struct _PUSB_HOST_CONTROLLER_DEVICE*  SharedHcd;
    int                                 HcdState;
    POOL                                HcdLocalMemory;
    void*                               PrivateData;
}USB_HOST_CONTROLLER_DEVICE, * PUSB_HOST_CONTROLLER_DEVICE;

typedef struct _USB_HOST_CONTROLLER_DRIVER{
    string              DeviceDescription;
    string              ProductDescriptor;
    size_t              HcdPrivateSize;
    void*               PrivateData;
    void              (*InterruptHandler)(uint64_t HcdHandle);
    uint16_t            DriverFlags;
    LOUSTATUS         (*ResetHcd)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*StartHcd)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*SuspendPciDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*ResumePciDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*PciPowerOff)(PUSB_HOST_CONTROLLER_DEVICE Hcd, bool Wakeup);
    void              (*HaltHcdExecution)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    void              (*ShutdownHcd)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    int               (*HcdRequestFrameNumber)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*HcdQueueUrb)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PURB Urb, uint64_t MemoryFlags);
    LOUSTATUS         (*HcdUnQueueUrb)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PURB Urb, LOUSTATUS* Status);
    LOUSTATUS         (*MapUrbToDma)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PURB Urb, uint64_t MemoryFlags);
    void              (*UnmapUrbToDma)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PURB Urb);
    void              (*DisableEndpoint)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_HOST_ENDPOINT Endpoint);
    void              (*ResetEndpoint)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_HOST_ENDPOINT   Endpoint);
    LOUSTATUS         (*HubStatusData)(PUSB_HOST_CONTROLLER_DEVICE Hcd, string DataString);
    LOUSTATUS         (*HubControl)(PUSB_HOST_CONTROLLER_DEVICE Hcd, uint16_t RequestType, uint16_t Value, uint16_t Index, string DataString, uint16_t Length);
    LOUSTATUS         (*SuspendBus)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*ResumeBus)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    LOUSTATUS         (*InitiatePortReset)(PUSB_HOST_CONTROLLER_DEVICE Hcd, uint64_t PortID);
    uint32_t          (*RequestResumingPorts)(PUSB_HOST_CONTROLLER_DEVICE Hcd);
    void              (*ReleasePort)(PUSB_HOST_CONTROLLER_DEVICE Hcd, uint64_t PortID);
    LOUSTATUS         (*CheckHandOver)(PUSB_HOST_CONTROLLER_DEVICE Hcd, uint64_t PortID);
    void              (*CtbComplete)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_HOST_ENDPOINT Endpoint);
    LOUSTATUS         (*LouKeMallocDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    void              (*LouKeFreeDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    LOUSTATUS         (*LouKeMallocStreams)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, PUSB_HOST_ENDPOINT* Endpoints, uint32_t EndpointCount, uint32_t StreamCount, uint64_t MemoryFlags);
    LOUSTATUS         (*LouKeFreeStreams)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, PUSB_HOST_ENDPOINT* Endpoints, uint32_t EndpointCount, uint32_t StreamCount, uint64_t MemoryFlags);
    LOUSTATUS         (*AddEndpoint)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, PUSB_HOST_ENDPOINT Endpoint);
    LOUSTATUS         (*DropEndpoint)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, PUSB_HOST_ENDPOINT Endpoint);
    LOUSTATUS         (*CheckBandwith)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    void              (*ResetBandwith)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, uint64_t Timeout);
    LOUSTATUS         (*AddressDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, uint64_t Timeout);
    LOUSTATUS         (*EnableDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    LOUSTATUS         (*UpdateHubDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    LOUSTATUS         (*ResetDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    LOUSTATUS         (*UpdateDevice)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice);
    LOUSTATUS         (*SetUsb2LowPowerMode)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, int PowerFlags);
    LOUSTATUS         (*EnableUsb3LowPowerModeTimeout)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, int PowerFlags);
    LOUSTATUS         (*DisableUsb3LowPowerModeTimeout)(PUSB_HOST_CONTROLLER_DEVICE Hcd, PUSB_DEVICE UsbDevice, int Usb3LinkState);
    LOUSTATUS         (*SearchRawPortID)(PUSB_HOST_CONTROLLER_DEVICE Hcd, int PortID);
    LOUSTATUS         (*PortPowerSwitch)(PUSB_HOST_CONTROLLER_DEVICE Hcd, int PortID, bool LightSwich);//santa clause turn on the lights please
    LOUSTATUS         (*SubmitSingleStepSetFeature)(PUSB_HOST_CONTROLLER_DEVICE* Hcd, PURB Urb, int FeatureFlags);
}USB_HOST_CONTROLLER_DRIVER, * PUSB_HOST_CONTROLLER_DRIVER;



#define HCD_HARDWARE_ACCESSIBLE(Hcd)    ((Hcd)->Flags & 1)
#define HCD_ROOTHUB_POLL(Hcd)           ((Hcd)->Flags & (1 << 2))
#define HCD_POLL_PENDING(Hcd)           ((Hcd)->Flags & (1 << 3))
#define HCD_WAKE_PENDING(Hcd)           ((Hcd)->Flags & (1 << 4))
#define HCD_ROOTHUB_RUNNING(Hcd)        ((Hcd)->Flags & (1 << 5))
#define HCD_DIED(Hcd)                   ((Hcd)->Flags & (1 << 6))
#define HCD_INTERFACE_AUTHORIZED(Hcd)   ((Hcd)->Flags & (1 << 7))
#define HCD_DELAY_ROOTHUB_REGISTER(Hcd) ((Hcd)->Flags & (1 << 8))

#define USB_DEVICE_AUTHORITY_NONE       0
#define USB_DEVICE_AUTHORITY_ALL        1
#define USB_DEVICE_AUTHORITY_INTERNAL   2
#define USB_DEVICE_AUTHORITY_WIRED      3

#define HCDS_ROOTHUB_REGISTERED(Hcd)            ((Hcd)->HCDS & 1)
#define HCDS_ROOTHUB_POLLABLE(Hcd)              ((Hcd)->HCDS & (1 << 1))
#define HCDS_MSIX_ENABLED(Hcd)                  ((Hcd)->HCDS & (1 << 2))
#define HCDS_MSI_ENABLED(Hcd)                   ((Hcd)->HCDS & (1 << 3))
#define HCDS_SKIP_PHY_LAYER_INITIALIZATION(Hcd) ((Hcd)->HCDS & (1 << 4))
#define HCDS_USES_NEW_POLLING(Hcd)              ((Hcd)->HCDS & (1 << 5))
#define HCDS_HAS_INTEGRATED_TT(Hcd)             ((Hcd)->HCDS & (1 << 6))
#define HCDS_HAS_AMD_RESUME_BUG(Hcd)            ((Hcd)->HCDS & (1 << 7))
#define HCDS_SUPPORTS_STREAMS(Hcd)              ((Hcd)->HCDS & (1 << 8))
#define HCDS_SUPPORTS_TPL(Hcd)                  ((Hcd)->HCDS & (1 << 9))
#define HCDS_CANT_RECIEVE_WAKEUPS               ((Hcd)->HCDS & (1 << 10))

#define HCD_STATE_ACTIVE     0x01
#define HCD_STATE_SUSPEND    0x02
#define HCD_STATE_TRANSIENT  0x80

#define HCD_STATE_HALTED    0x00
#define HCD_STATE_RUNNING   HC_STATE_ACTIVE
#define HCD_STATE_QUIESING  (HC_STATE_SUSPEND | HC_STATE_TRANSIENT | HC_STATE_ACTIVE)
#define HCD_STATE_RESUMING  (HC_STATE_SUSPEND | HC_STATE_TRANSIENT)

#define HC_IS_RUNNING(State)    ((State) & HCD_STATE_ACTIVE)
#define HC_IS_SUSPENDED(State)  ((State) & HCD_STATE_SUSPEND)

#define HCD_MEMORY  0x0001
#define HCD_DMA     0x0002
#define HCD_SHARED  0x0004
#define HCD_USB1_1  0x0010
#define HCD_USB2_0  0x0020
#define HCD_USB3_0  0x0040
#define HCD_USB3_1  0x0050
#define HCD_USB3_2  0x0060
#define HCD_MASK    0x0070
#define HCD_BH      0x0100

#define MAXIMUM_TOPOLOGY_LEVEL 6

#define USB_PACKET_ID_EXT       0xF0
#define USB_PACKET_ID_OUT       0xE1
#define USB_PACKET_ID_ACK       0xD2
#define USB_PACKET_ID_DATA0     0xC3
#define USB_PACKET_ID_PING      0xB4
#define USB_PACKET_ID_SOF       0xA5
#define USB_PACKET_ID_NYET      0x96
#define USB_PACKET_ID_DATA2     0x87
#define USB_PACKET_ID_SPLIT     0x78
#define USB_PACKET_ID_IN        0x69
#define USB_PACKET_ID_NAK       0x5A
#define USB_PACKET_ID_DATA1     0x4B
#define USB_PACKET_ID_PREAMBLE  0x3C
#define USB_PACKET_ID_ERROR     0x3C
#define USB_PACKET_ID_SETUP     0x2D
#define USB_PACKET_ID_STALL     0x1E
#define USB_PACKET_ID_MDATA     0x0F

#define EHSET_SINGLE_STEP_SET_FEATURE_TEST 0x06

#define HcdGivebackUrbInBh(Hcd) ((Hcd)->Driver->Flags & HCD_BH)

#define USB_BUS_FLAGS_IS_B_HOST(Bus)        ((Bus)->BusFlags & 1)
#define USB_BUS_FLAGS_B_HNP_ENABLE(Bus)     ((Bus)->BusFlags & (1 << 1))
#define USB_BUS_FLAGS_NO_STOP_ON_CHORT(Bus) ((Bus)->BusFlags & (1 << 2))
#define USB_BUS_FLAGS_NO_SG_CONSTRAINTS(Bus)((Bus)->BusFlags & (1 << 3))

#define USB_DEVICE_FLAGS1_CAN_SUBMIT(UsbDevice)                                                 ((UsbDevice)->UsbDeviceFlags1 & 1)
#define USB_DEVICE_FLAGS1_PERSIST_ENABLED(UsbDevice)                                            ((UsbDevice)->UsbDeviceFlags1 & (1 << 1))
#define USB_DEVICE_FLAGS1_RESET_IN_PROGRESS(UsbDevice)                                          ((UsbDevice)->UsbDeviceFlags1 & (1 << 2))
#define USB_DEVICE_FLAGS1_HAVE_LANG_ID(UsbDevice)                                               ((UsbDevice)->UsbDeviceFlags1 & (1 << 3))
#define USB_DEVICE_FLAGS1_AUTHORIZED(UsbDevice)                                                 ((UsbDevice)->UsbDeviceFlags1 & (1 << 4))
#define USB_DEVICE_FLAGS1_AUTHENTICATED(UsbDevice)                                              ((UsbDevice)->UsbDeviceFlags1 & (1 << 5))
#define USB_DEVICE_FLAGS1_LOW_POWER_MANAGEMENT_CAPEABLE(UsbDevice)                              ((UsbDevice)->UsbDeviceFlags1 & (1 << 6))
#define USB_DEVICE_FLAGS1_LOW_POWER_MANAGEMENT_DEVICE_INITIALIZATION_ALLOWED(UsbDevice)         ((UsbDevice)->UsbDeviceFlags1 & (1 << 7))
#define USB_DEVICE_FLAGS1_USB2_LOW_POWER_MANAGEMENT_CAPABLE(UsbDevice)                          ((UsbDevice)->UsbDeviceFlags1 & (1 << 8))
#define USB_DEVICE_FLAGS1_USB2_LOW_POWER_MANAGEMENT_BESL_CAPABLE(UsbDevice)                     ((UsbDevice)->UsbDeviceFlags1 & (1 << 9))
#define USB_DEVICE_FLAGS1_USB2_LOW_POWER_MANAGEMENT_ENABLED(UsbDevice)                          ((UsbDevice)->UsbDeviceFlags1 & (1 << 10))
#define USB_DEVICE_FLAGS1_USB2_LOW_POWER_MANAGEMENT_ALLOWED(UsbDevice)                          ((UsbDevice)->UsbDeviceFlags1 & (1 << 11))
#define USB_DEVICE_FLAGS1_USB3_LOW_POWER_MANAGEMENT_U1_ENABLED(UsbDevice)                       ((UsbDevice)->UsbDeviceFlags1 & (1 << 12))
#define USB_DEVICE_FLAGS1_USB3_LOW_POWER_MANAGEMENT_U2_ENABLED(UsbDevice)                       ((UsbDevice)->UsbDeviceFlags1 & (1 << 13))

#define USB_DEVICE_FLAGS2_DO_REMOTE_WAKEUP(UsbDevice)       ((UsbDevice)->UsbDeviceFlags2 & 1)
#define USB_DEVICE_FLAGS2_RESET_RESUME(UsbDevice)           ((UsbDevice)->UsbDeviceFlags2 & (1 << 1))
#define USB_DEVICE_FLAGS2_PORT_SUSPENDED(UsbDevice)         ((UsbDevice)->UsbDeviceFlags2 & (1 << 2))

#define USB_EXT_CAP_DESCRIPTOR_LPM_SUPPORT                  (1 << 1)
#define USB_EXT_CAP_DESCRIPTOR_BESL_SUPPORT                 (1 << 2)
#define USB_EXT_CAP_DESCRIPTOR_BASELINE_VALID               (1 << 3)
#define USB_EXT_CAP_DESCRIPTOR_DEEP_VALID                   (1 << 4)
#define USB_EXT_CAP_DESCRIPTOR_SET_BESL_BASELINE(BaseLine)  (((BaseLine) & 0x0F) << 8)
#define USB_EXT_CAP_DESCRIPTOR_SET_BESL_DEEP(Deep)          (((Deep) & 0x0F) << 12)
#define USB_EXT_CAP_DESCRIPTOR_GET_BESL_BASELINE(BaseLine)  (((BaseLine) & (0x0F << 8)) >> 8)
#define USB_EXT_CAP_DESCRIPTOR_GET_BESL_DEEP(Deep)          (((Deep) & (0x0F << 12)) >> 12)

#define USB_SS_CAP_DESCRIPTOR_LTM_SUPPORT           (1 << 1)
#define USB_SS_CAP_DESCRIPTOR_LOW_SPEED_OPERATION    1
#define USB_SS_CAP_DFECRIPTOR_FULL_SPEED_OPERATION  (1 << 1)
#define USB_SS_CAP_DESCRIPTOR_HIGH_SPEED_OPERATION  (1 << 2)
#define USB_SS_CAP_DESCRIPTOR_5GBPS_OPERATION       (1 << 3)

#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ATTRIBUTES                 (0x1F)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_IDS                        (0x0F << 5)
#define USB_SSP_CAP_DESCRIPTOR_MINIMUM_SUBLINK_SPEED_ATTRIBUTE_ID       (0x0F)
#define USB_SSP_CAP_DESCRIPTOR_MINIMUM_RX_LANE_COUNT                    (0x0F << 8)
#define USB_SSP_CAP_DESCRIPTOR_MINIMUM_TX_LANE_COUNT                    (0x0F << 12)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_SSID                       (0x0F)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSE                        (0x03 << 4)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSE_BPS                    0
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSE_KBPS                   1
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSE_MBPS                   2
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSE_GBPS                   3
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ST                         (0x03 << 6)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ST_SYM_RX                  0
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ST_ASYM_RX                 1
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ST_SYM_TX                  2
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_ST_ASYM_TX                 3
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_RESERVED                   (0x3F << 8)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LP                         (0x03 << 14)
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LP_SS                      0
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LP_SSP                     1
#define USB_SSP_CAP_DESCRIPTOR_SUBLINK_SPEED_LSM                        (0xFF << 16)

#define USB_INTERFACE_DEVICE_FILE_FLAG(UsbInterface)                    ((UsbInterface)->Flags & 1)
#define USB_INTERFACE_ENDPOINT_DEVICES_CREATED_FLAG(UsbInterface)       ((UsbInterface)->Flags & (1 << 1))
#define USB_INTERFACE_UNREGISTERING_FLAG(UsbInterface)                  ((UsbInterface)->Flags & (1 << 2))
#define USB_INTERFACE_NEEDS_REMOTE_WAKEUP_FLAG(UsbInterface)            ((UsbInterface)->Flags & (1 << 3))
#define USB_INTERFACE_NEEDS_ALTERNATE_SETTINGS_FLAG(UsbInterface)       ((UsbInterface)->Flags & (1 << 4))
#define USB_INTERFACE_NEEDS_BINDING(UsbInterface)                       ((UsbInterface)->Flags & (1 << 5))
#define USB_INTERFACE_RESETTING_DEVICE(UsbInterface)                    ((UsbINterface)->Flags & (1 << 6))
#define USB_INTERFACE_AUTHORIZED(UsbInterface)                          ((UsbInterface)->Flags & (1 << 7))

#define USB_DIR_IN                  0x00
#define USB_DIR_OUT                 0x80

#define USB_TYPE_MASK               (3 << 5)
#define USB_TYPE_STANDARD           (0 << 5)
#define USB_TYPE_CLASS              (1 << 5)
#define USB_TYPE_VENDOR             (2 << 5)
#define USB_TYPE_RESERVED           (3 << 5)

#define USB_RECIP_MASK              0x1F
#define USB_RECIP_DEVICE            0x00
#define USB_RECIP_INTERFACE         0x01
#define USB_RECIP_ENDPOINT          0x02
#define USB_RECIP_OTHER             0x03
#define USB_RECIP_PORT              0x04
#define USB_RECIP_RPIPE             0x05



#define USB_DT_ENDPOINT_SIZE        7
#define USB_DT_ENDPOINT_AUDIO_SIZE  9

#define USB_DT_DEVICE                       0x01
#define USB_DT_CONFIG                       0x02
#define USB_DT_STRING                       0x03
#define USB_DT_INTERFACE                    0x04
#define USB_DT_ENDPOINT                     0x05
#define USB_DT_DEVICE_QUALIFIER             0x06
#define USB_DT_OTHER_SPEED_CONFIG           0x07
#define USB_DT_INTERFACE_POWER              0x08
#define USB_DT_OTG                          0x09
#define USB_DT_DEBUG                        0x0A
#define USB_DT_INTERFACE_ASSOCIATION        0x0B
#define USB_DT_SECURITY                     0x0C
#define USB_DT_KEY                          0x0D
#define USB_DT_ENCRYPTION_TYPE              0x0E
#define USB_DT_BOS                          0x0F
#define USB_DT_DEVICE_CAPABILITIES          0x10
#define USB_DT_WIRELESS_ENDPOINT_COMP       0x11
#define USB_DT_EUSB2_ISOC_ENDPOINT_COMP     0x12
#define USB_DT_WIRE_ADAPTER                 0x21
#define USB_DT_DFU_FUNCTIONAL               0x21
#define USB_DT_RPIPE                        0x22
#define USB_DT_CS_RADIO_CONTROL             0x23
#define USB_DT_PIPE_USAGE                   0x24
#define USB_DT_SS_ENDPOINT_COMP             0x30
#define USB_DT_SSP_ISOC_ENDPOINT_COMP       0x31
#define USB_DT_CS_DEVICE                    (USB_TYPE_CLASS | USB_DT_DEVICE)
#define USB_DT_CS_CONFIG                    (USB_TYPE_CLASS | USB_DT_CONFIG)
#define USB_DT_CS_STRING                    (USB_TYPE_CLASS | USB_DT_STRING)
#define USB_DT_CS_INTERFACE                 (USB_TYPE_CLASS | USB_DT_INTERFACE)
#define USB_DT_CS_ENDPOINT                  (USB_TYPE_CLASS | USB_DT_ENDPOINT)

#define USB_ENDPOINT_NUMBER_MASK            0x0F
#define USB_ENDPOINT_DIR_MASK               0x80
#define USB_ENDPOINT_XFERTYPE_MASK          0x03
#define USB_ENDPOINT_XFER_CONTROL           0x00
#define USB_ENDPOINT_XFER_ISOC              0x01
#define USB_ENDPOINT_XFER_BULK              0x02
#define USB_ENDPOINT_XFER_INT               0x03

#define USB_REQ_GET_STATUS                  0x00
#define USB_REQ_CLEAR_FEATURE               0x01
#define USB_REQ_SET_FEATURE                 0x03
#define USB_REQ_SET_ADDRESS                 0x05
#define USB_REQ_GET_DESCRIPTOR              0x06
#define USB_REQ_SET_DESCRIPTOR              0x07
#define USB_REQ_GET_CONFIG                  0x08
#define USB_REQ_SET_CONFIG                  0x09
#define USB_REQ_GET_INTERFACE               0x0A
#define USB_REQ_SET_INTERFACE               0x0B
#define USB_REQ_SYNCH_FRAME                 0x0C
#define USB_REQ_SET_SEL                     0x30
#define USB_REQ_SET_ISOCH_DELAY             0x31
#define USB_REQ_SET_ENCRYPTION              0x0D
#define USB_REQ_GET_ENCRYPTION              0x0E
#define USB_REQ_RPIPE_ABORT                 0x0E
#define USB_REQ_SET_HANDSHAKE               0x0F
#define USB_REQ_RPIPE_RESET                 0x0F
#define USB_REQ_GET_HANDSHAKE               0x10
#define USB_REQ_SET_CONNECTION              0x11
#define USB_REQ_SET_SECURITY_DATA           0x12
#define USB_REQ_GET_SECURITY_DATA           0x13
#define USB_REQ_SET_WSUB_DATA               0x14
#define USB_REQ_LOOPBACK_DATA_WRITE         0x15
#define USB_REQ_LOOPBACK_DATA_READ          0x16
#define USB_REQ_SET_INTERFACE_DS            0x17

#define USB_REQ_GET_PARTNER_PD0             20
#define USB_REQ_GET_BATTERY_STATUS          21
#define USB_REQ_SET_PD0                     22
#define USB_REQ_GET_VDM                     23
#define USB_REQ_SEND_VDM                    24

#define USB_DEVICE_SELF_POWERED             0
#define USB_DEVICE_REMOTE_WAKEUP            1
#define USB_DEVICE_TEST_MODE                2
#define USB_DEVICE_BATTERY                  2
#define USB_DEVICE_B_HNP_ENABLE             3
#define USB_DEVICE_WSUB_DEVICE              3
#define USB_DEVICE_A_HNP_SUPPORT            4
#define USB_DEVICE_A_ALT_HNP_SUPPORT        5
#define USB_DEVICE_DEBUG_MODE               6

#define USB_TEST_J                          1
#define USB_TEST_K                          2
#define USB_TEST_SE0_NAK                    3
#define USB_TEST_PACKET                     4
#define USB_TEST_FORCE_ENABLE               5

#define USB_STATUS_TYPE_STANDARD            0
#define USB_STATUS_TYPE_PTM                 1

#define USB_DEVICE_U1_ENABLE                48
#define USB_DEVICE_U2_ENABLE                49
#define USB_DEVICE_LTM_ENABLE               50
#define USB_INTF_FUNC_SUSPEND               0

#define USB_INTR_FUNC_SUSPEND_OPT_MASK      0xFF00

#define USB_INTR_FUNC_SUSPEND_LP            (1 << 8)
#define USB_INTR_FUNC_SUSPEND_RW            (1 << 9)

#define USB_INTRF_STAT_FUNC_RW_CAP          1
#define USB_INTRF_STAT_FUNC_RW              2

#define USB_ENDPOINT_HALT                   0

#ifndef _KERNEL_MODULE_

PUSB_HOST_CONTROLLER_DEVICE 
LouKeCreateUsbHostControllerDevice(
    const USB_HOST_CONTROLLER_DRIVER*   Hcd,
    PPCI_DEVICE_OBJECT                  PDEV
);

LOUSTATUS 
LouKeUsbHcdPciProbe(
    PPCI_DEVICE_OBJECT Pdev, 
    const USB_HOST_CONTROLLER_DRIVER*   Hcd
);

#else

KERNEL_EXPORT
PUSB_HOST_CONTROLLER_DEVICE 
LouKeCreateUsbHostControllerDevice(
    const USB_HOST_CONTROLLER_DRIVER*   Hcd,
    PPCI_DEVICE_OBJECT                  PDEV
);

KERNEL_EXPORT
LOUSTATUS 
LouKeUsbHcdPciProbe(
    PPCI_DEVICE_OBJECT Pdev, 
    const USB_HOST_CONTROLLER_DRIVER* Hcd 
);

#endif

#ifdef __cplusplus
}
#endif
#endif