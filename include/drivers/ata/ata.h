#ifndef _ATA_DEVICE_LIBRARY_H
#define _ATA_DEVICE_LIBRARY_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif


typedef struct _LOUSINE_KERNEL_DEVICE_ATA_PORT{
    //SCSI_HOST                     ScsiHost;
    //PATA_PORT_OPERATION           Operations;
    spinlock_t                      PortLock;
    unsigned long                   AtaFlags;
    unsigned int                    AtaPFlags;
    unsigned int                    UserPortID;
    unsigned int                    PortNumber;
    //ATA_IO_PORT                   IoAddress;
    uint8_t                         ControlRegisterCahce;
    uint8_t                         LastWritenControlRegisterCache;
    //PATA_LINK                     SffPioTaskLink;
    DELAYED_FUNCTION                SffPioTask;
    //PATA_BMDMA_PRD                BmDmaPrd;
    uintptr_t                       DmaAddress;
    unsigned int                    PioMask;
    unsigned int                    MwDmaBits;
    unsigned int                    UDmaBits;
    unsigned int                    CableType;
    //PATA_QUEUED_COMMAND           QueuedCommand[ATA_MAX_QUEUE_COMMANDS + 1];
    uint64_t                        QueueCommandActive;
    int                             ActiveQcsLinks;
    //ATA_LINK                      HostDefaultLink;
    //PATA_LINK                     HostSlaveLink;
    int                             AvailablePmpLinks;
    //PATA_LINK                     PmpLink;
    //PATA_LINK                     PmpQcExclusionLink;
    //ATA_PORT_STATUS               PortStatus;
    //PATA_HOST                     AtaHost;
    P_PCI_DEVICE_OBJECT             PDEV;
    mutex_t                         ScsiScanMutex;
    DELAYED_FUNCTION                HotplugTask;
    DELAYED_FUNCTION                ScsiRescanTask;
    unsigned int                    HsmTaskState;
    ListHeader                      IoStackDoneQueue;
    LOUQ_WAIT                       IoStackWaitQueue;
    int                             IoStackTries;
    //LOUQ_COMPLETION               ParkRequestPending;
    //POWER_MANAGEMENT_MESSAGE      PowerMessgae
    uint32_t                        LpmPolicy;
    //TIMER_LIST                      FastdrainTimer;
    unsigned int                    FastdrainCount;
    //ASYNC_COOKIE                    AsyncCookie;
    int                             EclosuerManagementMessage;
    void*                           PrivateExtendedData;
    //ATA_ACPI_GTM                    AcpiInitializationGTM;
}LOUSINE_KERNEL_DEVICE_ATA_PORT, * PLOUSINE_KERNEL_DEVICE_ATA_PORT;



#ifdef __cplusplus
}
#endif
#endif //_ATA_DEVICE_LIBRARY_H
