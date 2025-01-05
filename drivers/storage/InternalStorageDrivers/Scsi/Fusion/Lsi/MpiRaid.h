//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/31/2024  8:53 AM
//Time Finished : 12/31/2024 10:20 AM
//Last Modified : 12/31/2024 10:20 AM

#ifndef _MPI_RAID_H
#define _MPI_RAID_H
#pragma pack(push,1)

#define MPI_RAID_ACTION_REQUEST_STATUS                              0x00
#define MPI_RAID_ACTION_REQUEST_INDICATOR_STRUCTURE                 0x01
#define MPI_RAID_ACTION_REQUEST_CREATE_VOLUME                       0x02
#define MPI_RAID_ACTION_REQUEST_DELETE_VOLUME                       0x03
#define MPI_RAID_ACTION_REQUEST_DISABLE_VOLUME                      0x04
#define MPI_RAID_ACTION_REQUEST_ENABLE_VOLUME                       0x05
#define MPI_RAID_ACTION_REQUEST_QUIESCE_PHYS_IO                     0x06
#define MPI_RAID_ACTION_REQUEST_ENABLE_PHYS_IO                      0x07
#define MPI_RAID_ACTION_REQUEST_CHANGE_VOLUME_SETTING               0x08
#define MPI_RAID_ACTION_REQUEST_PHYSICAL_DISK_OFFLINE               0x0A
#define MPI_RAID_ACTION_REQUEST_PHYSICAL_DISK_ONLINE                0x0B
#define MPI_RAID_ACTION_REQUEST_CHANGE_PHYICAL_DISK_SETTING         0x0C
#define MPI_RAID_ACTION_REQUEST_CREATE_PHYSICAL_DISK                0x0D
#define MPI_RAID_ACTION_REQUEST_DELETE_PHYSICAL_DISK                0x0E
#define MPI_RAID_ACTION_REQUEST_FAIL_PHYSICAL_DISK                  0x0F
#define MPI_RAID_ACTION_REQUEST_REPLACE_PHYSICAL_DISK               0x10
#define MPI_RAID_ACTION_REQUEST_ACTIVATE_VOLUME                     0x11
#define MPI_RAID_ACTION_REQUEST_DEACTIVATE_VOLUEM                   0x12
#define MPI_RAID_ACTION_REQUEST_SET_RESYNC_RATE                     0x13
#define MPI_RAID_ACTION_REQUEST_SET_DATA_SCRUB_RATE                 0x14
#define MPI_RAID_ACTION_REQUEST_DEVICE_FIRMWARE_UPDATE_MODE         0x15
#define MPI_RAID_ACTION_REQUEST_SET_VOLUME_NAME                     0x16

#define MPI_RAID_ACTION_DATA_DO_NOT_SYNC        1
#define MPI_RAID_ACTION_DATA_LOW_LEVEL_INIT     2

#define MPI_RAID_ACTION_DATA_KEEP_PHYSICAL_DISKS    0
#define MPI_RAID_ACTION_DATA_DELETE_PHYSICAL_DISKS  1

#define MPI_RAID_ACTION_DATA_KEEP_LBA0  0
#define MPI_RAID_ACTION_DATA_ZERO_LBA0  2

#define MPI_RAID_ACTION_DATA_DISABLE_FULL_REBUILD   1

#define MPI_RAID_ACTION_DATA_DEACTIVATE_ALL     1
#define MPI_RAID_ACTION_DATA_RESYNC_RATE_BITS   0xFF
#define MPI_RAID_ACTION_DATA_SCRUB_RATE_BITS    0xFF

#define MPI_RAID_ACTION_DATA_ENABLE_FIRMWARE_UPDATE             0x00000001
#define MPI_RAID_ACTION_DATA_FIRMWARE_UPDATE_TIMEOUT_BITS       0x0000FF00
#define MPI_RAID_ACTION_DATA_FIRMWARE_UPDATE_TIMEOUT_SHIFT      8

#define MPI_RAID_ACTION_STATUS_SUCCESS              0
#define MPI_RAID_ACTION_STATUS_INVALID_ACTION       1
#define MPI_RAID_ACTION_STATUS_FAILURE              2
#define MPI_RAID_ACTION_STATUS_IN_PROGRESS          3


//raid Action Request
typedef struct _MESSAGE_RAID_ACTION{
    MPIU8                               ActionID;
    MPIU8                               Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU8                               VolumeID;
    MPIU8                               VolumeBus;
    MPIU8                               PhysicalDiskNumber;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU32                              Rsv2;
    MPIU32                              ActionDataDWORD;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ActionDataEntry;
}MESSAGE_RAID_ACTION, * PMESSAGE_RAID_ACTION;

//Raid Action Reply message
typedef struct _MESSAGE_RAID_ACTION_REPLY{
    MPIU8       ActionID;
    MPIU8       Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU8       ID;
    MPIU8       Bus;
    MPIU8       PhysicalDiskNumber;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      ActionStatus;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
    MPIU32      VolumeStatus;
    MPIU32      ActionData;
}MESSAGE_RAID_ACTION_REPLY, * PMESSAGE_RAID_ACTION_REPLY;

typedef struct _MPI_RAID_VOLUME_INDICATOR{
    MPIU64      TotalBlocks;
    MPIU64      BlocksRemaining;
}MPI_RAID_VOLUME_INDICATOR, * PMPI_RAID_VOLUME_INDICATOR;

typedef struct _MESSAGE_SCSI_IO_RAID_PASSTHROUGH_REQUEST{
    MPIU8                               PhysicalDiskNumber;
    MPIU8                               Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU8                               CommandBufferLength;
    MPIU8                               SenceBufferLength;
    MPIU8                               Rsv2;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU8                               LUN[8];
    MPIU32                              Control;
    MPIU8                               CommandBuffer[16];
    MPIU32                              DataLength;
    MPIU32                              LowAddressOfSenceBuffer;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}MESSAGE_SCSI_IO_RAID_PASSTHROUGH_REQUEST, * PMESSAGE_SCSI_IO_RAID_PASSTHROUGH_REQUEST;

typedef struct _MESSAGE_SCSI_IO_RAID_PASSTHROUGH_REPLY{
    MPIU8                               PhysicalDiskNumber;
    MPIU8                               Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU8                               CommandBufferLength;
    MPIU8                               SenceBufferLength;
    MPIU8                               Rsv2;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU8                               LUN[8];
    MPIU32                              Control;
    MPIU8                               CommandBuffer[16];
    MPIU32                              DataLegnth;
    MPIU32                              LowAddressOfSenceBuffer;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}MESSAGE_SCSI_IO_RAID_PASSTHROUGH_REPLY, * PMESSAGE_SCSI_IO_RAID_PASSTHROUGH_REPLY;

typedef struct _MESSAGE_MAILBOX_REQUEST{
    MPIU16                              Rsv1;
    MPIU8                               ChainOffset;
    MPIU8                               MpiFunction;
    MPIU16                              Rsv2;
    MPIU8                               Rsv3;
    MPIU8                               MessageFlags;
    MPIU32                              MessageContext;
    MPIU8                               CommandBuffer[10];
    MPIU16                              Rsv4;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   ScatterGatherList;
}MESSAGE_MAILBOX_REQUEST, * PMESSAGE_MAILBOX_REQUEST;

typedef struct _MESSAGE_MAILBOX_REPLY{
    MPIU16      Rsv1;
    MPIU8       MessageLength;
    MPIU8       MpiFunction;
    MPIU16      Rsv2;
    MPIU8       Rsv3;
    MPIU8       MessageFlags;
    MPIU32      MessageContext;
    MPIU16      MailboxStatus;
    MPIU16      IocStatus;
    MPIU32      IocLogInfo;
    MPIU32      Rsv4;
}MESSAGE_MAILBOX_REPLY, * PMESSAGE_MAILBOX_REPLY;

#pragma pack(pop)
#endif //_MPI_RAID_H