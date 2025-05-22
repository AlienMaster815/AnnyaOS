#ifndef _CXL_FLASH_IOCTL_H
#define _CXL_FLASH_IOCTL_H

#pragma pack(push,1)

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

#define CXL_FLASH_WWID_LENGTH   16

#define DK_CXL_FLASH_VERSION0   0

typedef struct _DK_CXL_FLASH_HEADER{
    uint16_t Version;
    uint16_t Reserved[3];
    uint64_t Flags;
    uint64_t ReturnFlags;
}DK_CXL_FLASH_HEADER, * PDK_CXL_FLASH_HEADER;

#define DK_CXL_FLASH_ALL_PORTS_ACTIVE           0x0000000000000001
#define DK_CXL_FLASH_APP_CLOSE_ADAP_FO          0x0000000000000002
#define DK_CXL_FLASH_CONTEXT_SQ_COMMAND_MODE    0x0000000000000004
#define DK_CXL_FLASH_ATTACH_REUSE_CONTEXT       0x8000000000000000

typedef struct _DK_CXL_FLASH_ATTACH{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                InterruptCount;
    uint64_t                ContextID;
    uint64_t                MmioSize;
    uint64_t                BlockSize;
    uint64_t                AdapFileDescriptor;
    uint64_t                LastLBA;
    uint64_t                MaxXFER;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_ATTACH, * PDK_CXL_FLASH_ATTACH;

typedef struct _DK_CXL_FLASH_DETACH{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextID;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_DETACH, * PDK_CXL_FLASH_DETACH;

typedef struct _DK_CXL_FLASH_UDIRECT{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextID;
    uint64_t                ResourceHandle;
    uint64_t                LastLBA;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_UDIRECT, * PDK_CXL_FLASH_UDIRECT;

#define DK_CXL_FLASH_UVIRTUAL_NEED_WRITE_SAVE   0x8000000000000000

typedef struct _DK_CXL_FLASH_UVIRTUAL{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextID;
    uint64_t                LunSize;
    uint64_t                ResourceHandle;
    uint64_t                LastLBA;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_UVIRTUAL, * PDK_CXL_FLASH_UVIRTUAL;

typedef struct _DK_CXL_FLASH_RELEASE{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextID;
    uint64_t                ResourceHandle;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_RELEASE, * PDK_CXL_FLASH_RELEASE;

typedef struct _DK_CXL_FLASH_RESIZE{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextID;
    uint64_t                ResourceHandle;
    uint64_t                RequestedSize;
    uint64_t                LastLBA;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_RESIZE, * PDK_CXL_FLASH_RESIZE;

typedef struct _DK_CXL_FLASH_CLONE{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                ContextIDSource;
    uint64_t                ContextIDDestination;
    uint64_t                SourceAdapter;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_CLONE, * PDK_CXL_FLASH_CLONE;

#define DK_CXL_FLASH_VERIFY_SENSE_LENGTH    18
#define DK_CXL_FLASH_VERIFY_HINT_SENSE      0x8000000000000000

typedef struct _DK_CXL_FLASH_VERIFY{
    uint64_t    ContextID;
    uint64_t    ResourceHandle;
    uint64_t    Hint;
    uint64_t    LastLBA;
    uint8_t     SenseData[DK_CXL_FLASH_VERIFY_SENSE_LENGTH];
    uint8_t     Pad[6];
    uint64_t    Reserved[8];
}DK_CXL_FLASH_VERIFY, * PDK_CXL_FLASH_VERIFY;

#define DK_CXL_FLASH_RECOVER_AFU_CONTEXT_RESET  0x8000000000000000

typedef struct _DK_CXL_FLASH_RECOVER_AFU{
    DK_CXL_FLASH_HEADER     Header;
    uint64_t                Reason;
    uint64_t                ContextID;
    uint64_t                MmioSize;
    uint64_t                AdapterFileDescriptor;
    uint64_t                Reserved[8];
}DK_CXL_FLASH_RECOVER_AFU, * PDK_CXL_FLASH_RECOVER_AFU;

#define DK_CXL_FLASH_MANAGE_LUN_WWID_LENGTH                 CXL_FLASH_WWID_LENGTH
#define DK_CXL_FLASH_MANAGE_LUN_ENABLE_SUPER_PIPE           0x8000000000000000
#define DK_CXL_FLASH_MANAGE_LUN_DISABLE_SUPER_PIPE          0x4000000000000000
#define DK_CXL_FLASH_MANAGE_LUN_ALL_PORTS_ACCESSIBLE        0x2000000000000000

typedef struct _DK_CXL_FLASH_MANAGE_LUN{
    DK_CXL_FLASH_HEADER     Header;
    uint8_t                 Wwid[DK_CXL_FLASH_MANAGE_LUN_WWID_LENGTH];
    uint64_t                Reserved[8];
}DK_CXL_FLASH_MANAGE_LUN, * PDK_CXL_FLASH_MANAGE_LUN;

typedef union _DK_CXL_FLASH_IO_CTL{  
    DK_CXL_FLASH_ATTACH         Attach;
    DK_CXL_FLASH_DETACH         Detach;
    DK_CXL_FLASH_UDIRECT        UDirect;
    DK_CXL_FLASH_UVIRTUAL       UVirtual;
    DK_CXL_FLASH_RELEASE        Release;
    DK_CXL_FLASH_RESIZE         Resize;
    DK_CXL_FLASH_CLONE          Clone;
    DK_CXL_FLASH_VERIFY         Verify;
    DK_CXL_FLASH_RECOVER_AFU    RecoverAfu;
    DK_CXL_FLASH_MANAGE_LUN     ManageLun;
}DK_CXL_FLASH_IO_CTL, * PDK_CXL_FLASH_IO_CTL;

#define MAX_CXL_FLASH_IO_CTL_SIZE   (sizeof(DK_CXL_FLASH_IO_CTL))

#define HT_CXL_FLASH_VERSION0   0

typedef struct _HT_CXL_FLASH_HEADER{
    uint16_t    Version;
    uint16_t    SubCommand;
    uint16_t    Reserved[2];
    uint64_t    Flags;
    uint64_t    ReturnFlags;
}HT_CXL_FLASH_HEADER, * PHT_CXL_FLASH_HEADER;

#define HT_CXL_FLAHS_HOST_READ  0x0000000000000000
#define HT_CXL_FLAHS_HOST_WITE  0x0000000000000001

#define HT_CXL_FLASH_LUN_PROVISION_SUB_COMMAND_CREATE_LUN   0x0001
#define HT_CXL_FLASH_LUN_PROVISION_SUB_COMMAND_DELETE_LUN   0x0002
#define HT_CXL_FLASH_LUN_PROVISION_SUB_COMMAND_QUERY_PORT   0x0003

typedef struct _HT_CXL_FLASH_LUN_PROVISION{
    HT_CXL_FLASH_HEADER     Header;
    uint16_t                Port;
    uint16_t                Reserved1[3];
    uint64_t                Size;
    uint64_t                LunID;
    uint8_t                 Wwid[CXL_FLASH_WWID_LENGTH];
    uint64_t                MaxLuns;
    uint64_t                CurrentLuns;
    uint64_t                MaxCapPorts;
    uint64_t                CurrentCapPorts;
    uint64_t                Reserved[8];
}HT_CXL_FLASH_LUN_PROVISION, * PHT_CXL_FLASH_LUN_PROVISION;

#define HT_CXL_FLASH_AFU_DEBUG_MAX_DATA_LENGTH      262144
#define HT_CXL_FLASH_AFU_DEBUG_SUB_COMMAND_LENGTH   12

typedef struct _HT_CXL_FLASH_AFU_DEBUG{
    HT_CXL_FLASH_HEADER     Header;
    uint8_t                 Reserved1[4];
    uint8_t                 AfuCubCommand[HT_CXL_FLASH_AFU_DEBUG_SUB_COMMAND_LENGTH];
    uint64_t                DataEffectiveAddress;
    uint32_t                DataLength;
    uint32_t                Reserved2;
    uint64_t                Reserved3[8];
}HT_CXL_FLASH_AFU_DEBUG, * PHT_CXL_FLASH_AFU_DEBUG;

typedef union _CXL_FLASH_HT_IO_CTLS{
    HT_CXL_FLASH_LUN_PROVISION  LunProvision;
    HT_CXL_FLASH_AFU_DEBUG      AfuDebug;
}CXL_FLASH_HT_IO_CTLS, * PCXL_FLASH_HT_IO_CTLS;

#define MAX_HT_CXL_FLASH_IOCTL_SIZE     sizeof(CXL_FLASH_HT_IO_CTLS)

//todo Cxl Systems with user and Kernel mode transfers
#ifdef __cplusplus
}
#endif
#pragma pack(pop)
#endif //_CXL_FLASH_IOCTL_H