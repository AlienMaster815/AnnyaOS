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


struct _LOUSINE_SCSI_HOST;


typedef struct _LOUSINE_SCSI_HOST_TEMPLATE{
    unsigned int    CommandSize;
    //LOUSTATUS       (*QueueCommand)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND*);
    LOUSTATUS       (*ForceCommandComitment)(struct _LOUSINE_SCSI_HOST*, uint16_t);
    string          DeviceName;
    string          (*DevieInformation)(struct _LOUSINE_SCSI_HOST*);
    LOUSTATUS       (*LousineKernelIoDispatch)(struct _LOUSINE_SCSI_HOST*, unsigned int, void*);
    LOUSTATUS       (*CompatIoDispatch)(struct _LOUSINE_SCSI_HOST*, unsigned int, void*);
    //LOUSTATUS       (*InitializeCommandProprietary)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND);
    //LOUSTATUS       (*InitializeCommandProprietary)(struct _LOUSINE_SCSI_HOST*, struct _SCSI_COMMAND);
}LOUSINESCSI_HOST_TEMPLATE, * PLOUSINESCSI_HOST_TEMPLATE;

typedef struct _LOUSINE_SCSI_HOST{
    ListHeader          DevicesList;
    ListHeader          TargetsList;
    ListHeader          StarvedList;
    spinlock_t          DeviceLock;
    spinlock_t*         HostLock;
    mutex_t             ScanningMutex;
    ListHeader          IoStackAbortList;
    ListHeader          IoStackCommandList;
    uint32_t            (*ErrorHandler)(void* ErrorHandleingData);
    PLOUQ_COMPLETION    IoStackAction;
    LOUQ_WAIT           HostWait;
    
}LOUSINE_SCSI_HOST, * PLOUSINE_SCSI_HOST;

#ifdef __cplusplus
}
#endif

#endif //_SCSI_HOST_H