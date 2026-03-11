#ifndef _NTAPI_FUNC_H
#define _NTAPI_FUNC_H
#include <NtAPI.h>
#pragma once


//Filler Types Until Found

typedef void* HalStartMirroring;
typedef void* HalEndMirroring;
typedef void* HalMirrorPhysicalMemory;
typedef void* HalEndOfBoot;
typedef void* HalMirrorVerify;
typedef void* HalGetAcpiTable;
typedef void* HalSetPciErrorHandlerCallback;
typedef void* HalGetPrmCache;
typedef void* KSYSTEM_TIME;
typedef void* NT_PRODUCT_TYPE;
typedef void* ALTERNATIVE_ARCHITECTURE_TYPE;
typedef void* PPHYSICAL_COUNTER_EVENT_BUFFER_OVERFLOW_HANDLER;
typedef void* PPHYSICAL_COUNTER_OVERFLOW_HANDLER;
typedef void* PKTHREAD;
typedef void* PBOOT_DRIVER_CALLBACK_FUNCTION;
typedef void* PDRIVER_REINITIALIZE;
typedef void* LOGICAL;
typedef void* PEXPAND_STACK_CALLOUT;
typedef void* KPRIORITY;
typedef void* KDPC_IMPORTANCE;
typedef void* PPHYSICAL_MEMORY_RANGE;
typedef void* PGET_LOCATION_STRING;
typedef void* PESILO;
typedef void* SILO_CONTEXT_CLEANUP_CALLBACK;
typedef void* PEJOB;
typedef void* PSILO_MONITOR;
typedef void* PCREATE_THREAD_NOTIFY_ROUTINE;
typedef void* PLOAD_IMAGE_NOTIFY_ROUTINE;
typedef void* PCREATE_PROCESS_NOTIFY_ROUTINE;
typedef void* PCREATE_PROCESS_NOTIFY_ROUTINE_EX;
typedef void* PCORRELATION_VECTOR;



typedef void* SILO_MONITOR_CREATE_CALLBACK;
typedef void* SILO_MONITOR_TERMINATE_CALLBACK;
typedef void* WHEA_ERROR_SOURCE_TYPE;
typedef void* WHEA_EVENT_LOG_ENTRY;
typedef void* PWHEA_ERROR_RECORD;
typedef void* PWHEA_ERROR_PACKET_V2;
typedef void* WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS;
typedef void* WHEA_ERROR_SEVERITY;
typedef void* WHEA_NOTIFICATION_DESCRIPTOR;
typedef void* WHEAP_DPC_ERROR_EVENT_TYPE;
typedef void* PFN_NUMBER;
typedef void* PWHEA_ERROR_SOURCE_CONFIGURATION;
typedef void* WHEA_SIGNAL_HANDLER_OVERRIDE_CALLBACK;


typedef void* PGPE_CONNECT_VECTOR2;
typedef void* PGPE_DISCONNECT_VECTOR2;
typedef void* PGPE_ENABLE_EVENT2;
typedef void* PGPE_DISABLE_EVENT2;
typedef void* PGPE_CLEAR_STATUS2;
typedef void* PREGISTER_FOR_DEVICE_NOTIFICATIONS2;
typedef void* PUNREGISTER_FOR_DEVICE_NOTIFICATIONS2;
typedef void* PTRANSLATE_BUS_ADDRESS;
typedef void* PGET_DMA_ADAPTER;
typedef void* PGET_SET_DEVICE_DATA;
typedef void* PGET_UPDATED_BUS_RESOURCE;
typedef void* PCLFS_CLIENT_ADVANCE_TAIL_CALLBACK;
typedef void* PCLFS_CLIENT_LFF_HANDLER_COMPLETE_CALLBACK;
typedef void* PCLFS_CLIENT_LOG_UNPINNED_CALLBACK;
typedef void* PLOG_FILE_OBJECT;
typedef void* PCLFS_LSN;
typedef void* PPLOG_FILE_OBJECT;
typedef void* PALLOCATE_FUNCTION;
typedef void* PFREE_FUNCTION;
typedef void* CLFS_SCAN_MODE;
typedef void* PCLFS_SCAN_CONTEXT;
typedef void* CLFS_LSN;
typedef void* CLFS_IOSTATS_CLASS;
typedef void* CLFS_CONTAINER_ID;
typedef void* CLFS_MGMT_CLIENT;
typedef void* PCLFS_MGMT_CLIENT;
typedef void* PCLFS_SET_LOG_SIZE_COMPLETE_CALLBACK;
typedef void* CLFS_LOG_INFORMATION_CLASS;
typedef void* PCLFS_RECORD_TYPE;
typedef void* PCLFS_WRITE_ENTRY;
typedef void* CLFS_CONTAINER_STATE;
typedef void* CLFS_NODE_ID;
typedef void* PEX_CALLBACK_FUNCTION;
typedef void* PSET_D3COLD_SUPPORT;
typedef void* PD3COLD_REQUEST_CORE_POWER_RAIL;
typedef void* PD3COLD_REQUEST_AUX_POWER;
typedef void* PD3COLD_REQUEST_PERST_DELAY;
typedef void* PGET_IDLE_WAKE_INFO;
typedef void* PGET_D3COLD_CAPABILITY;
typedef void* PGET_D3COLD_LAST_TRANSITION_STATUS;

typedef void* PIOMMU_DEVICE_FAULT_HANDLER;
typedef void* PDEVICE_RESET_HANDLER;
typedef void* PDEVICE_QUERY_BUS_SPECIFIC_RESET_HANDLER;
typedef void* PDEVICE_BUS_SPECIFIC_RESET_HANDLER;
typedef void* PGET_DEVICE_RESET_STATUS;


typedef void* REGHANDLE;
typedef void* EVENT_INFO_CLASS;
typedef void* PFAST_MUTEX;
typedef void* PERESOURCE;
typedef void* PEX_RUNDOWN_REF;
typedef void* PEX_SPIN_LOCK;
typedef void* PEX_RUNDOWN_REF_CACHE_AWARE;
typedef void* PLOOKASIDE_LIST_EX;
typedef void* PNPAGED_LOOKASIDE_LIST;
typedef void* PPAGED_LOOKASIDE_LIST;
typedef void* POOL_FLAGS;
typedef void* PCPOOL_EXTENDED_PARAMETER;
typedef void* PEX_TIMER;
typedef void* PEXT_CALLBACK;
typedef void* PEXT_CANCEL_PARAMETERS;
typedef void* PCALLBACK_OBJECT;
typedef void* PALLOCATE_FUNCTION_EX;
typedef void* PFREE_FUNCTION_EX;
typedef void* PEX_PUSH_LOCK;
typedef void* PCALLBACK_FUNCTION;
typedef void* ERESOURCE_THREAD;
typedef void* PEXT_DELETE_CALLBACK;
typedef void* PIO_COMPLETION_CONTEXT;
typedef void* PSECTION_OBJECT_POINTERS;
typedef void* PFPGA_BUS_SCAN;
typedef void* PFPGA_CONTROL_LINK;
typedef void* PFPGA_CONTROL_CONFIG_SPACE;
typedef void* PFPGA_CONTROL_ERROR_REPORTING;
typedef void* IO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS;
typedef void* IO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS;
typedef void* IO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS;
typedef void* PACCESS_STATE;
typedef void* PNAMED_PIPE_CREATE_PARAMETERS;
typedef void* DIRECTORY_NOTIFY_INFORMATION_CLASS;
typedef void* PFILE_GET_QUOTA_INFORMATION;
typedef void* DEVICE_RELATION_TYPE;
typedef void* PPOWER_SEQUENCE;
typedef void* PIO_COMPLETION_ROUTINE;
typedef void* PVOID64;
typedef void* PKIRQL;
typedef void* PIO_REMOVE_LOCK;
typedef void* PIO_WORKITEM;
typedef void* PSHARE_ACCESS;
typedef void* PKSERVICE_ROUTINE;
typedef void* CREATE_FILE_TYPE;
typedef void* PKSTART_ROUTINE;
typedef void* PIO_CSQ;
typedef void* PIO_CSQ_INSERT_IRP;
typedef void* PIO_CSQ_REMOVE_IRP;
typedef void* PIO_CSQ_PEEK_NEXT_IRP;
typedef void* PIO_CSQ_ACQUIRE_LOCK;
typedef void* PIO_CSQ_RELEASE_LOCK;
typedef void* PIO_CSQ_COMPLETE_CANCELED_IRP;
typedef void* PIO_CSQ_INSERT_IRP_EX;
typedef void* PIO_CSQ_IRP_CONTEXT;
typedef void* PIO_PERSISTED_MEMORY_ENUMERATION_CALLBACK;
typedef void* DEVPROPKEY;
typedef void* PDEVPROPTYPE;
typedef void* DEVICE_REGISTRY_PROPERTY;
typedef void* DRIVER_DIRECTORY_TYPE;
typedef void* PIO_DPC_ROUTINE;
typedef void* PIO_TIMER_ROUTINE;
typedef void* _IORING_OBJECT;
typedef void* POOL_EXTENDED_PARAMS_SECURE_POOL;
typedef void* POOL_NODE_REQUIREMENT;
typedef void* PGET_SDEV_IDENTIFIER;
typedef void* PREENUMERATE_SELF;
typedef void* POBJECT_NAME_INFORMATION;
typedef void* POBJECT_TYPE;
typedef void* OB_OPERATION;
typedef void* POB_PRE_OPERATION_CALLBACK;
typedef void* POB_POST_OPERATION_CALLBACK;
typedef void* PPCI_SET_ATS;
typedef void* PPCI_MSIX_SET_ENTRY;
typedef void* PPCI_MSIX_MASKUNMASK_ENTRY;
typedef void* PPCI_MSIX_GET_ENTRY;
typedef void* PPCI_MSIX_GET_TABLE_SIZE;
typedef void* PPCI_SET_ACS2;

typedef void* IOMMU_DEVICE_CREATION_CONFIGURATION_PASID;
typedef void* PPFN_NUMBER;
typedef void* PIO_WORKITEM_ROUTINE;
typedef void* PIO_WORKITEM_ROUTINE_EX;
typedef void* PIO_CONTAINER_NOTIFICATION_FUNCTION;
typedef void* PDRIVER_NOTIFICATION_CALLBACK_ROUTINE;
typedef void* PDEVICE_CHANGE_COMPLETE_CALLBACK;
typedef void* DEVPROPTYPE;
typedef void* WMI_NOTIFICATION_CALLBACK;
typedef void* PKGUARDED_MUTEX;
typedef void* PKLOCK_QUEUE_HANDLE;
typedef void* SpinLock;
typedef void* OldIrql;
typedef void* PKTRIAGE_DUMP_DATA_ARRAY;
typedef void* PKTIMER;
typedef void* PKBUGCHECK_CALLBACK_RECORD;
typedef void* PKBUGCHECK_REASON_CALLBACK_RECORD;
typedef void* PRKSEMAPHORE;
typedef void* PKIPI_BROADCAST_WORKER;
typedef void* PBOUND_CALLBACK;
typedef void* PKBUGCHECK_CALLBACK_ROUTINE;
typedef void* PKBUGCHECK_REASON_CALLBACK_ROUTINE;
typedef void* PNMI_CALLBACK;
typedef void* PPROCESSOR_CALLBACK_FUNCTION;
typedef void* PXSTATE_SAVE;
typedef void* PKFLOATING_SAVE;
typedef void* PKSYNCHRONIZE_ROUTINE;
typedef void* KWAIT_REASON;
typedef void* PKWAIT_BLOCK;
typedef void* PMM_MDL_ROUTINE;
typedef void* LOCK_OPERATION;
typedef void* MM_SYSTEMSIZE;
typedef void* NOTIFICATION_MASK;
typedef void* PTRANSACTION_NOTIFICATION;
typedef void* PARTITION_INFORMATION_CLASS;
typedef void* TRANSACTIONMANAGER_INFORMATION_CLASS;
typedef void* POBJECT_HANDLE_INFORMATION;
typedef void* PREQUEST_POWER_COMPLETE;
typedef void* PAFFINITY_TOKEN;
typedef void* PPTM_DEVICE_QUERY_GRANULARITY;
typedef void* PPTM_DEVICE_QUERY_TIME_SOURCE;
typedef void* PPTM_DEVICE_ENABLE;
typedef void* PPTM_DEVICE_DISABLE;
typedef void* PUTF8_STRING;
typedef void* PRTL_QUERY_REGISTRY_TABLE;
typedef void* REFGUID;
typedef void* PTIME_FIELDS;
typedef void* PSECURITY_SUBJECT_CONTEXT;
typedef void* PKENLISTMENT;
typedef void* PKTRANSACTION;
typedef void* PRKRESOURCEMANAGER;
typedef void* PKRESOURCEMANAGER;
typedef void* PTM_RM_NOTIFICATION;
typedef void* PUOW;
typedef void* PRKTM;
typedef void* PKTM;
typedef void* TRACEHANDLE;
typedef void* SECTION_INHERIT;
typedef void* PKINTERRUPT_ROUTINE;

typedef USHORT RTL_ATOM;
typedef RTL_ATOM* PRTL_ATOM;

typedef struct _TOKEN_PRIVALEDGES{
    DWORD PrivaledgeCount;
    LUID_AND_ATTRIBUTES Priviledges[];
}TOKEN_PRIVALEDGES, * PTOKEN_PRIVALEDGES;

#define POOL_EXTENDED_PARAMETER_TYPE_BITS 1
#define POOL_EXTENDED_PARAMETER_REQUIRED_FIELD_BITS 1
#define POOL_EXTENDED_PARAMETER_RESERVED_BITS 1

//ENDOF: TODO LIST\n




#ifdef __cplusplus
#define NTHALAPI extern "C"
#define NTSYSCALLAPI extern "C"
#define CLFSUSER_API extern "C"
#define NTAPI_INLINE inline
#define NTKERNELAPI extern "C"
#define _DECL_HAL_KE_IMPORT extern "C"
#else

#define NTHALAPI extern
#define NTSYSCALLAPI extern
#define CLFSUSER_API extern
#define NTAPI_INLINE inline
#define NTKERNELAPI extern
#define _DECL_HAL_KE_IMPORT extern
#endif


typedef size_t SIZE_T, * PSIZE_T;


//VOID RtlCopyUnicodeString( PUNICODE_STRING DestinationString,  PUNICODE_STRING SourceString);
#ifndef _KERNEL_MODULE_
ULONG DbgPrint( PCSTR Format, ...);
ULONG DbgPrintEx (  ULONG ComponentId,  ULONG Level,  PCSTR Format, ...);
#else 
LOUAPI unsigned long DbgPrint(char const*, ...);
#endif

#include "Misc/undocumentedTypes.h"
#include "ioaccess.h"
#include "ntddk.h"
#include "ntddsfio.h"
#include "ntddsysenv.h"
#include "ntifs.h"
#include "wmistr.h"
#include "ntddsfio.h"
#include "wmilib.h"
#include "irp.h"
#include "ntddsysenv.h"
#include "Ntintsafe.h"
#include "ntoapi.h"
#include "ntifs.h"
#include "wmidata.h"
#include "wdmsec.h"
#include "procgrp.h"
#include "ntstrsafe.h"
#include "wdm.h"
#include "../../kernel/loustatus.h"
#include "iointx.h"

#endif