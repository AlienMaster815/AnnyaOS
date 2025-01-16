#ifndef _ATA_DEVICE_LIBRARY_H
#define _ATA_DEVICE_LIBRARY_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#define ATA_CABLE_TYPE_NONE                     0
#define ATA_CABLE_TYPE_PATA40                   1
#define ATA_CABLE_TYPE_PATA80                   2
#define ATA_CABLE_TYPE_PATA40_SHORT             3
#define ATA_CABLE_TYPE_PATA40_UNKONW            4
#define ATA_CABLE_TYPE_PATA40_IGNORE_CABLE      5
#define ATA_CABLE_TYPE_PATA40_SATA              6

#define ATA_PFLAG_IO_REQUEST_PENDING            1
#define ATA_PFLAG_IO_REQUEST_IN_PROGGRESS       1 << 1
#define ATA_PFLAG_PORT_FROZEN                   1 << 2
#define ATA_PFLAG_PORT_RECOVERED                1 << 3
#define ATA_PFLAG_PORT_LOADING                  1 << 4
#define ATA_PFLAG_SCSI_HOTPLUG                  1 << 6
#define ATA_PFLAG_INITIALIZING                  1 << 7
#define ATA_PFLAG_RESETTING                     1 << 8
#define ATA_PFLAG_UNLOADING                     1 << 8
#define ATA_PFLAG_UNLOADED                      1 << 10
#define ATA_PFLAG_RESUMING                      1 << 16
#define ATA_PFLAG_SUSPENDED                     1 << 17
#define ATA_PFLAG_PM_OPERATION_PENDING          1 << 18
#define ATA_PFLAG_INIT_GTM_VALID                1 << 19
#define ATA_PFLAG_PIO32                         1 << 20
#define ATA_PFLAG_PIO32_CHANGE                  1 << 21
#define ATA_PFLAG_EXTERNAL                      1 << 22

typedef struct _LOUSINE_KERNEL_DEVICE_ATA_PORT{
    struct _LOUSINE_SCSI_HOST*      ScsiHost;
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
    unsigned int                    PioBits;
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

int AtaBmdaPortStart(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort);

#ifdef __cplusplus
}
#endif
#endif //_ATA_DEVICE_LIBRARY_H
