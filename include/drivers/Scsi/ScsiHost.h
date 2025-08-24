#ifndef _SCSI_HOST_H
#define _SCSI_HOST_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#ifndef _CSTDINT_H
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

#include "../ScatterList.h"

#include "FibreChannel/FibreChannelFrame.h"
#include "CxlFlashIoCtl.h"
#include "ScsiBsgFibreChannel.h"
#include "ScsiBsgUfs.h"
#include "ScsiFibreChannelNetlink.h"
#include "ScsiProtocol.h"
#include "ScsiCommon.h"
#include "IscsiIf.h"

#define SCATTER_GATHER_ALL      SCATTER_GATHER_CHUNK_SIZE

#define MODE_UNKOWN             0x00
#define MODE_INITIATOR          0x01
#define MODE_TARGET             0x02

#define SCSI_IO_STACK_REQUEST_DONE          0
#define SCSI_IO_STACK_REQUEST_RESET_TIMER   1
#define SCSI_IO_STACK_REQUEST_NOT_HANDLED   2

#define SCSI_HOST_STATE_CREATED             1
#define SCSI_HOST_STATE_RUNNING             2
#define SCSI_HOST_STATE_CANCEL              3
#define SCSI_HOST_STATE_DELET               4
#define SCSI_HOST_STATE_RECOVERY            5
#define SCSI_HOST_STATE_CANCEL_RECOVERY     6
#define SCSI_HOST_STATE_DELET_RECOVERY      7

#define SCSI_ADAPTER_RESET                  1
#define SCSI_FIRMWARE_RESET                 2

#define SCSI_DEFAULT_MAX_SECTORS            1024

#define SCSI_DEFAULT_HOST_BLOCKED           7

struct _LOUSINE_SCSI_HOST;
struct _SCSI_COMMAND;
struct _LOUSINE_SCSI_DEVICE;
struct _SCSI_TARGET;
struct _SCSI_HOST;
struct _LOUSINE_SCSI_TRANSPORT_TEMPLATE;
struct _LOUSINE_BLOCK_DEVICE;
struct _LOUSINE_SEQUENCE_FILE;

typedef struct _LOUSINE_SCSI_HOST_TEMPLATE{
    unsigned int    CommandSize;
    int             (*QueueCommand)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND*);
    int             (*ForceCommandComitment)(struct _LOUSINE_SCSI_HOST*, uint16_t);
    string          DeviceName;
    string          (*DevieInformation)(struct _LOUSINE_SCSI_HOST*);
    int             (*LousineKernelIoDispatch)(struct _LOUSINE_SCSI_HOST*, unsigned int, void*);
    int             (*CompatIoDispatch)(struct _LOUSINE_SCSI_HOST*, unsigned int, void*);
    int             (*InitializeCommandProprietary)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND*);
    int             (*ExitCommandProprietary)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND*);
    int             (*ErrorHandlerAbort)(struct _SCSI_COMMAND*);
    int             (*ErrorHandlerDeviceReset)(struct _SCSI_COMMAND*);
    int             (*ErrorHandlerTargetReset)(struct _SCSI_COMMAND*);
    int             (*ErrorHandlerBusReset)(struct _SCSI_COMMAND*);
    int             (*ErrorHandlerHostReset)(struct _SCSI_COMMAND*);
    int             (*ScsiSlaveAllocator)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*ScsiConfigureDevice)(struct _LOUSINE_SCSI_DEVICE*, PLOUQ_LIMITS);
    int             (*ScsiConfigureSlave)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*ScsiDestroySlave)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*ScsiAllocateTarget)(struct _SCSI_TARGET*);
    int             (*ScsiDestroyTarget)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*ScsiFinishedScan)(struct _LOUSINE_SCSI_HOST*);
    int             (*ScsiStartScan)(struct _LOUSINE_SCSI_HOST*);
    int             (*ChangeQueueDepth)(struct _LOUSINE_SCSI_DEVICE*, int);
    void            (*MapQueues)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*MqPoll)(struct _LOUSINE_SCSI_HOST*, uint32_t);
    bool            (*DmaNeedsDraining)(PLOUQ_REQUEST);
    int             (*BiosParameters)(struct _LOUSINE_SCSI_DEVICE*, struct _LOUSINE_BLOCK_DEVICE*, uint64_t, int*);
    void            (*ScsiUnlockNativeCapacity)(struct _LOUSINE_SCSI_DEVICE*);
    int             (*ShowInformation)(struct _LOUSINE_SEQUENCE_FILE*, struct _LOUSINE_SCSI_HOST*);
    int             (*WriteInformation)(struct _LOUSINE_SCSI_HOST*,string,int);
    uint32_t        (*ErrorHandlerTimeOut)(struct _SCSI_COMMAND*);
    bool            (*ErrorHandlerShouldScsiRetryCommand)(struct _SCSI_COMMAND*);
    int             (*HostReset)(struct _SCSI_HOST* ScsiHost, int ResetType);
    int             CanDeviceQueue;
    int             HandleIdentification;
    uint16_t        ScatterTableSize;
    uint16_t        ScatterProtocolTableSize;
    uint32_t        MaximumSectors;
    uint32_t        MaximumSegmentSize;
    uint32_t        DmaAlignment;
    uint64_t        DmaBoundry;
    uint64_t        VirtualAddressBoundryMask;
    int16_t         CommandsPerLUN;
    int32_t         TaggedAllocationPolicy;
    uint8_t         TrackQueueDepth : 1;
    uint8_t         SupportedMode   : 2;
    uint8_t         EmulatedDevice  : 1;
    uint8_t         SkipSettleDelay : 1;
    uint8_t         NoWriteSame     : 1;
    uint8_t         HostTagSet      : 1;
    uint8_t         CommandMayBlock : 1;
    uint32_t        MaxHostBlocked;
    uint64_t        VendorID;
}LOUSINE_SCSI_HOST_TEMPLATE, * PLOUSINE_SCSI_HOST_TEMPLATE;

#define DEFINE_SCSI_QUEUE_COMMAND(FunctionName) \
int FunctionName(struct _LOUSINE_SCSI_HOST* ScsiHost, struct _SCSI_COMMAND* ScsiCommand) { \
    LouKIRQL Irql; \
    int Result; \
    LouKeAcquireSpinLock(ScsiHost->HostLock , &Irql); \
    Result FunctionName##_lck(ScsiCommand); \
    LouKeReleaseSpinLock(ScsiHost->HostLock , &Irql); \
    return Result; \
}

typedef struct _LOUSINE_SCSI_HOST{
    ListHeader                                      DevicesList;
    ListHeader                                      TargetsList;
    ListHeader                                      StarvedList;
    spinlock_t                                      DeviceLock;
    spinlock_t*                                     HostLock;
    mutex_t                                         ScanningMutex;
    ListHeader                                      IoStackAbortList;
    ListHeader                                      IoStackCommandList;
    uint32_t                                        (*ErrorHandler)(void* ErrorHandleingData);
    PLOUQ_COMPLETION                                IoStackAction;
    LOUQ_WAIT                                       HostWait;
    PLOUSINE_SCSI_HOST_TEMPLATE                     HostTemplate;
    struct _LOUSINE_SCSI_TRANSPORT_TEMPLATE*        TransportTemplate;
    void*                                           TagsetHandle;
    LOUQ_COMPLETION                                 TagsetCompletion;
    atomic_t                                        IsHostBlocked;
    uint32_t                                        HostHasFailed;
    uint32_t                                        HostErrorHandlerSchedualedWithoughtCommand;
    uint32_t                                        HostNumber;
    int32_t                                         EhDeadline;
    uint64_t                                        LastReset;
    uint32_t                                        MaximumChannels;
    uint32_t                                        MaximumIdentifications;
    uint64_t                                        MaximumLUNs;
    uint32_t                                        UniqueIdentification;
    uint16_t                                        MaximumCommandLength;
    int32_t                                         HostIdentification;
    int32_t                                         CanQueue;
    uint16_t                                        CommandsPerLUNs;
    uint16_t                                        ScatterTableSize;
    uint16_t                                        ScatterProtocolTableSize;
    uint32_t                                        MaximumSectors;
    uint32_t                                        OperationallSectors;
    uint32_t                                        MaximumSegmentSize;
    uint32_t                                        DmaAlignement;
    uint64_t                                        DmaBoundry;
    uint64_t                                        VirtualAddressBoundryMask;
    uint64_t                                        NumberOfHardwareQueues;
    uint64_t                                        NumberOfMaps;
    uint8_t                                         ActiveMode          :   2;
    uint8_t                                         HostSelfBlocked     :   1;
    uint8_t                                         ReverseOrdering     :   1;
    uint8_t                                         TaskManagementOperating :   1;
    uint8_t                                         ErrorHandlerNoResume : 1;
    uint8_t                                         NoWriteSame : 1;
    uint8_t                                         HostTagSet : 1;
    uint8_t                                         CommandMayBlock : 1;
    uint8_t                                         ShortInquery : 1;
    uint8_t                                         NoScsi2LUNInCommandBlock;
    uint8_t                                         NoHighMemory : 1;
    PLOUQ_WORK                                      Work;
    PLOUQ_WORK                                      TmfWork;
    uint32_t                                        MaxHostBlocked;
    uint32_t                                        ProtectionCapabilites;
    uint8_t                                         ProtectionGuardType;
    uint64_t                                        Base;
    uint64_t                                        IoPort;
    uint8_t                                         DmaChannel;
    uint32_t                                        InterruptRequest;
    uint32_t                                        ScsiHostState;
    PPCI_DEVICE_OBJECT                             PDEV;
    void*                                           DeviceHandle;
    void*                                           DmaHandle;
    int                                             AutoSleepDelay;
    void*                                           HostData;
}LOUSINE_SCSI_HOST, * PLOUSINE_SCSI_HOST;


static inline void* ScsiHostGetPrivateData(PLOUSINE_SCSI_HOST ScsiHost){
    return ScsiHost->HostData;
}

static inline int SiScsiHostInRecovery(PLOUSINE_SCSI_HOST ScsiHost){
    return ((ScsiHost->ScsiHostState == SCSI_HOST_STATE_RECOVERY) || (ScsiHost->ScsiHostState == SCSI_HOST_STATE_CANCEL_RECOVERY) || (ScsiHost->ScsiHostState == SCSI_HOST_STATE_DELET_RECOVERY) || (ScsiHost->TaskManagementOperating));
}

static inline int IsScsiHostScanAllowed(PLOUSINE_SCSI_HOST ScsiHost){
    return ((ScsiHost->ScsiHostState == SCSI_HOST_STATE_RUNNING) || (SCSI_HOST_STATE_RECOVERY));
}



#ifdef __cplusplus
}
#endif

#endif //_SCSI_HOST_H