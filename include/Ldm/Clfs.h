#ifndef _LDM_CLFS_H
#define _LDM_CLFS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _CLFS_LSN{
    ULONGLONG   Internal;
}CLFS_LSN, * PCLFS_LSN;

typedef 
void 
CLFS_CLIENT_LOG_UNPINNED_CALLBACK(
    PLOG_FILE_OBJECT    LogFile,
    PVOID               ClientData
);
typedef CLFS_CLIENT_LOG_UNPINNED_CALLBACK* PCLFS_CLIENT_LOG_UNPINNED_CALLBACK;

typedef 
void
CLFS_CLIENT_LFF_HANDLER_COMPLETE_CALLBACK(
    PLOG_FILE_OBJECT    LogFile,
    LOUSTATUS           OperationStatus,
    BOOLEAN             LogIdPinned,
    PVOID               ClientData
);
typedef CLFS_CLIENT_LFF_HANDLER_COMPLETE_CALLBACK* PCLFS_CLIENT_LFF_HANDLER_COMPLETE_CALLBACK;

typedef 
LOUSTATUS
CLFS_CLIENT_ADVANCE_TAIL_CALLBACK(
    PLOG_FILE_OBJECT    LogFile,
    PCLFS_LSN           TargetLsn,
    PVOID               ClientData
);
typedef CLFS_CLIENT_ADVANCE_TAIL_CALLBACK* PCLFS_CLIENT_ADVANCE_TAIL_CALLBACK;

typedef UCHAR CLFS_SCAN_MODE;

#define CLFS_SCAN_INIT          1
#define CLFS_SCAN_FORWARD       2
#define CLFS_SCAN_BACKWARD      4
#define CLFS_SCAN_CLOSE         8
#define CLFS_SCAN_INITIALIZED   16
#define CLFS_SCAN_BUFFERED      32

typedef struct _CLFS_NODE_ID{
    ULONG Type;
    ULONG Node;
}CLFS_NODE_ID, * PCLFS_NODE_ID;

typedef UINT32 CLFS_CONTAINER_STATE;

#define ClsContainerInitializing            1
#define ClsContainerInactive                2
#define ClsContainerActive                  4
#define ClsContainerActivePendingDelete     8
#define ClsContainerPendingArchive          16
#define ClsContainerPendingArchiveDelete    32

typedef ULONG CLFS_CONTAINER_ID, * PCLFS_CONTAINER_ID;

typedef struct _CLS_CONTAINER_INFORMATION {
    ULONG                FileAttributes;
    ULONGLONG            CreationTime;
    ULONGLONG            LastAccessTime;
    ULONGLONG            LastWriteTime;
    LONGLONG             ContainerSize;
    ULONG                FileNameActualLength;
    ULONG                FileNameLength;
    WCHAR*               FileName;
    CLFS_CONTAINER_STATE State;
    CLFS_CONTAINER_ID    PhysicalContainerId;
    CLFS_CONTAINER_ID    LogicalContainerId;
} CLS_CONTAINER_INFORMATION, * PCLS_CONTAINER_INFORMATION, PPCLS_CONTAINER_INFORMATION;

typedef struct _CLFS_SCAN_CONTEXT{
    CLFS_NODE_ID                Node;
    PLOG_FILE_OBJECT            LogFile;
    ULONG                       Index;
    ULONG                       Containers;
    ULONG                       ContainersReturned;
    CLFS_SCAN_MODE              ScanMode;
    PCLS_CONTAINER_INFORMATION  ContainerInformation;
}CLFS_SCAN_CONTEXT, * PCLFS_SCAN_CONTEXT;

typedef enum _CLFS_IOSTATS_CLASS{
    ClfsIoSlotsDefault  = 0x0000,
    ClfsIoSlotsMax      = 0xFFFF,
}CLFS_IOSTATS_CLASS, * PCLFS_IOSTATS_CLASS;

typedef PVOID CLFS_MGMT_CLIENT, *PCLFS_MGMT_CLIENT;

typedef enum _CLFS_LOG_SIZE_TYPE{
    ClfsLogSizeMin = 0x0000,
    ClfsLogSizeMax = 0xFFFF,
}CLFS_LOG_SIZE_TYPE, * PCLFS_LOG_SIZE_TYPE;

typedef 
void 
CLFS_SET_LOG_SIZE_COMPLETE_CALLBACK(
    PVOID               ClientData,
    CLFS_LOG_SIZE_TYPE  SizeType,
    ULONG               OpStatus
);
typedef CLFS_SET_LOG_SIZE_COMPLETE_CALLBACK* PCLFS_SET_LOG_SIZE_COMPLETE_CALLBACK;

typedef enum _CLFS_LOG_INFORMATION_CLASS{
  ClfsLogBasicInformation = 0,
  ClfsLogBasicInformationPhysical,
  ClfsLogPhysicalNameInformation,
  ClfsLogStreamIdentifierInformation,
  ClfsLogSystemMarkingInformation,
  ClfsLogPhysicalLsnInformation,
}CLFS_LOG_INFORMATION_CLASS, * PCLFS_LOG_INFORMATION_CLASS,
    CLS_LOG_INFORMATION_CLASS, * PCLS_LOG_INFORMATION_CLASS, PPCLS_LOG_INFORMATION_CLASS;

typedef enum _CLFS_RECORD_TYPE{
    ClfsDataRecord = 0,
    ClfsRestartRecord,
}CLFS_RECORD_TYPE, * PCLFS_RECORD_TYPE;

typedef struct _CLFS_WRITE_ENTRY{
    PVOID   Buffer;
    ULONG   ByteLength;
}CLFS_WRITE_ENTRY, * PCLFS_WRITE_ENTRY;



#ifdef __cplusplus
}
#endif
#endif