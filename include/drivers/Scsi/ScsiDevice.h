#ifndef _SCSI_DEVICE_H
#define _SCSI_DEVICE_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif


typedef uint64_t BLIST_FLAGS;

#define SCSI_SENCE_BUFFERSIZE   96

typedef struct _SCSI_MODE_DATA{
    uint32_t    EntryLength;
    uint16_t    BDL;
    uint8_t     MediumType;
    uint8_t     DeviceSpecifc;
    uint8_t     HeaderLength;
    uint8_t     LongLba : 1;
}SCSI_MODE_DATA, * PSCSI_MODE_DATA;

#define SCSI_DEV_STATE_CREATED              1
#define SCSI_DEV_STATE_RUNNING              2
#define SCSI_DEV_STATE_CANCEL               3
#define SCSI_DEV_STATE_DELETE               4
#define SCSI_DEV_STATE_QUIESCENT            5
#define SCSI_DEV_STATE_OFFLINE              6
#define SCSI_DEV_STATE_TRANSPORT_OFFLINE    7
#define SCSI_DEV_STATE_BLOCK                8
#define SCSI_DEV_STATE_CREATED_BLOCK        9

#define SCSI_SCAN_INITIAL 0
#define SCSI_SCAN_RESCAN  1
#define SCSI_SCAN_MANUAL  2

#define SCSI_EVENT_MEDIA_CHANGE                         1
#define SCSI_EVENT_INQUIRY_CHANGE_REPORTED              2
#define SCSI_EVENT_CAPACITY_CHANGE_REPORTED             3
#define SCSI_EVENT_SOFT_THRESHOLD_REACHED_REPORTED      4
#define SCSI_EVENT_MODE_PARAMETER_CHANGE_REPORTED       5
#define SCSI_EVENT_LUN_CHANGE_REPORTED                  6
#define SCSI_EVENT_ALUA_STATE_CHANGE_REPORTED           7
#define SCSI_EVENT_POWER_ON_RESET_OCCOURED              8
#define SCSI_EVENT_FIRST                                SCSI_EVENT_MEDIA_CHANGE
#define SCSI_EVENT_LAST                                 SCSI_EVENT_POWER_ON_RESET_OCCOURED
#define SCSI_EVENT_MAXBITS                              SCSI_EVENT_POWER_ON_RESET_OCCOURED + 1

typedef struct _READ_COPY_UPDATE_HEADER{
    struct _READ_COPY_UPDATE_HEADER* NextHeader;
    void (*ReadCopyUpdate)(struct _READ_COPY_UPDATE_HEADER* Header);
}READ_COPY_UPDATE_HEADER, * PREAD_COPY_UPDATE_HEADER;

typedef struct _SCSI_EVENT{
    uint32_t    EventType;
    ListHeader  NodeChain;
}SCSI_EVENT, * PSCSI_EVENT;

typedef struct _SCSI_VIRTUAL_PRODUCT_DATA{
    READ_COPY_UPDATE_HEADER     ReadCopyUpdateHeader;
    int                         Length;
    uint8_t                     DataBuffer[];
}SCSI_VIRTUAL_PRODUCT_DATA, * PSCSI_VIRTUAL_PRODUCT_DATA;

#define SCSI_DEVICE_RAMP_UP_VPD_LENGTH          255
#define SCSI_DEVICE_DEFAULT_DEVICES_BLOCKED     3

typedef struct _LOUSINE_SCSI_DEVICE{
    struct _LOUSINE_SCSI_HOST*      ScsiHost;
    LOUQ_REQUEST                    LouQRequestData;
    ListHeader                      Relatives;
    ListHeader                      STRealatives;
    uint64_t                        BudgetMapping;
    atomic_t                        DevicePriveledges;
    atomic_t                        DeviceRestarts;
    spinlock_t                      ListLock;
    ListHeader                      StarvedEntry;
    uint16_t                        QueueDepth;
    uint16_t                        MaximumQueueDepth;
    uint16_t                        LastQueueFullDepth;
    uint16_t                        LastQueueFullCount;
    uint64_t                        LastQueueFullTime;
    uint64_t                        QueueRampUpPeriods;
    uint64_t                        LastQueueRampUp;
    uint32_t                        Id;
    uint32_t                        Channel;
    uint64_t                        SectorSize;
    void*                           HostData;
    uint8_t                         DeviceType;
    char                            ScsiLevel;
    char                            In1PeriphQual;
    mutex_t                         InquiryMutex;
    uint8_t                         InquiryLength;
    uint8_t*                        InqBuffer;
    string                          VendorData;
    string                          ModelData;
    string                          RevisionData;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPage0;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPage83;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPage80;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPage89;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPageb0;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPageb1;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPageb2;
    PSCSI_VIRTUAL_PRODUCT_DATA      VpdPageb7;
    struct _LOUSINE_SCSI_TARGET*    ScsiDeviceTarget;
    uint64_t                        ScsiDeviceFlags;
    uint32_t                        ErrorHandleTimeout;
    //SystemFlags
    uint8_t                         ManageSystemRunState            :   1;
    uint8_t                         ManageRuntimeRunState           :   1;
    uint8_t                         ManageSystemShutdown            :   1;
    uint8_t                         ForceRuntimeOnBootup            :   1;
    uint8_t                         Removable                       :   1;
    uint8_t                         Changed                         :   1;
    uint8_t                         Busy                            :   1;
    uint8_t                         Lockable                        :   1;
    uint8_t                         Locked                          :   1;
    uint8_t                         ChineseDevice                   :   1;//Chinese device the offical way to say a device was realeased broken for extra profit
    uint8_t                         DisconnectableDevice            :   1;//the age of flash is oppon us
    uint8_t                         SoftResetCompatable             :   1;//God Help me if this isnt checked
    uint8_t                         DeviceSupportsSDTRMessageing    :   1;
    uint8_t                         DeviceSupportsWDTRMessageing    :   1;
    uint8_t                         DeviceSupportsPPRMessageing     :   1;
    uint8_t                         DeviceSupportsTagging           :   1;
    uint8_t                         SimpleTaggingEnabled            :   1;
    uint8_t                         SystemBusRest                   :   1;
    uint8_t                         DeviceExspectingCcUa            :   2;
    uint8_t                         ReadWrite10Supported            :   1;
    uint8_t                         ModeSence10Supported            :   1;
    uint8_t                         SetDbdForModeSence              :   1;
    uint8_t                         NoReportOpcodes                 :   1;
    uint8_t                         NoWriteSameOpcodes              :   1;
    uint8_t                         ReadWrite16Supported            :   1;
    uint8_t                         Use16ForSyncronizationOver10    :   1;
    uint8_t                         SkipModeSyncPage8               :   1;
    uint8_t                         SkipModeSyncPage3F              :   1;
    uint8_t                         SkipVpdPages                    :   1;
    uint8_t                         Use192ByesFor3F                 :   1;
    uint8_t                         DontIssueStartOnAdd             :   1;
    uint8_t                         AllowRestartInErrorHandleing    :   1;
    uint8_t                         RunStatePowerCondition          :   1;
    uint8_t                         NoUpperLevelDriverAttached      :   1;
    uint8_t                         SlectNoAtn                      :   1;
    uint8_t                         FixCapacity                     :   1;
    uint8_t                         GuessCapacity                   :   1;
    uint8_t                         RetryHardwareError              :   1;
    uint8_t                         MultiSectorBug                  :   1;
    uint8_t                         NoReadDiscInformation           :   1;
    uint8_t                         NoReadCapacity16                :   1;
    uint8_t                         Rc10Supported                   :   1;
    uint8_t                         SecurityProtocolsSupported      :   1;
    uint8_t                         DeviceIdInLSSD                  :   1;
    uint8_t                         WceOnByDefault                  :   1;
    uint8_t                         ChineseT10DIF                   :   1;
    uint8_t                         ChineseFUA                      :   1;
    uint8_t                         LunBitsInSommandDataBuffer      :   1;
    uint8_t                         UnmapLimitForWs                 :   1;
    uint8_t                         RpmAutoSuspend                  :   1;
    uint8_t                         IgnoreMediaChange               :   1;
    uint8_t                         SilenceSuspend                  :   1;
    uint8_t                         VpdSizeNotConfirmed             :   1;
    uint8_t                         CommandDurrationLimitSupported  :   1;
    uint8_t                         CommandDurrationLimitEnabled    :   1;
    int32_t                         QueuedStop;
    bool                            DeviceOffline;
    atomic_t                        DEDD;
    ListHeader                      EventTree;
    LOUQ_WORK                       WorkTree;
    uint32_t                        MaximumDevicesBlocked;
    atomic_t                        IoRequestCount;
    atomic_t                        IoDoneCount;
    atomic_t                        IoErrorCount;
    atomic_t                        IoTimeoutCount;
    void*                           DeviceHandle;
    LOUQ_WORK                       RetryWork;
    //struct _SCSI_DEVICE_HANDLER*  ScsiDeviceHandler;
    void*                           ScsiDeviceHandlerData;
    uint64_t                        ScsiDmaDrainLength;
    void*                           ScsiDmaDrainBuffer;
    uint32_t                        ScsiScatterGatherTimeout;
    uint32_t                        ScsiScatterGatherReserveSize;
    //struct _BSG_DEVICE*           BsgDevice;
    uint8_t                         AccessState;
    mutex_t                         StateMutex;
    uint32_t                        ScsiDeviceState;
    void*                           QuiescedThreadData;
    uint8_t                         ScsiDenviceData[];
}LOUSINE_SCSI_DEVICE, * PLOUSINE_SCSI_DEVICE;

#define SCSI_TARGET_STATE_CREATED           1
#define SCSI_TARGET_STATE_RUNNING           2
#define SCSI_TARGET_STATE_REMOVE            3
#define SCSI_TARGET_STATE_CREATED_REMOVE    4
#define SCSI_TARGET_STATE_DELETE            5      

typedef struct _LOUSINE_SCSI_TARGET{
    uintptr_t Foo;
}LOUSINE_SCSI_TARGET, * PLOUSINE_SCSI_TARGET;

#ifdef __cplusplus
}
#endif

#endif //_SCSI_DEVICE_H