#ifndef _NTAPI_FUNC_H
#define _NTAPI_FUNC_H
#include <NtAPI.h>
#pragma once

//Filler Types Until Found

typedef void* PALLOCATE_FUNCTION_EX;
typedef void* PFREE_FUNCTION_EX;
typedef void* PEX_PUSH_LOCK;
typedef void* PCALLBACK_FUNCTION;
typedef void* PEXT_DELETE_CALLBACK;
typedef void* PIO_COMPLETION_CONTEXT;
typedef void* PFPGA_BUS_SCAN;
typedef void* PFPGA_CONTROL_CONFIG_SPACE;
typedef void* PFPGA_CONTROL_ERROR_REPORTING;
typedef void* IO_CONNECT_INTERRUPT_FULLY_SPECIFIED_PARAMETERS;
typedef void* IO_CONNECT_INTERRUPT_LINE_BASED_PARAMETERS;
typedef void* IO_CONNECT_INTERRUPT_MESSAGE_BASED_PARAMETERS;
typedef void* PNAMED_PIPE_CREATE_PARAMETERS;
typedef void* PFILE_GET_QUOTA_INFORMATION;
typedef void* DEVICE_RELATION_TYPE;
typedef void* PIO_COMPLETION_ROUTINE;
typedef void* PIO_REMOVE_LOCK;
typedef void* PKSERVICE_ROUTINE;
typedef void* CREATE_FILE_TYPE;
typedef void* PKSTART_ROUTINE;
typedef void* PIO_CSQ_INSERT_IRP;
typedef void* PIO_CSQ_REMOVE_IRP;
typedef void* PIO_CSQ_PEEK_NEXT_IRP;
typedef void* PIO_CSQ_ACQUIRE_LOCK;
typedef void* PIO_CSQ_RELEASE_LOCK;
typedef void* PIO_CSQ_COMPLETE_CANCELED_IRP;
typedef void* PIO_CSQ_INSERT_IRP_EX;
typedef void* PIO_PERSISTED_MEMORY_ENUMERATION_CALLBACK;
typedef void* DRIVER_DIRECTORY_TYPE;
typedef void* PIO_DPC_ROUTINE;
typedef void* PIO_TIMER_ROUTINE;
typedef void* PGET_SDEV_IDENTIFIER;
typedef void* PREENUMERATE_SELF;
typedef void* POBJECT_NAME_INFORMATION;
typedef void* POB_PRE_OPERATION_CALLBACK;
typedef void* POB_POST_OPERATION_CALLBACK;
typedef void* PPCI_SET_ATS;
typedef void* PPCI_MSIX_SET_ENTRY;
typedef void* PPCI_MSIX_MASKUNMASK_ENTRY;
typedef void* PPCI_MSIX_GET_ENTRY;
typedef void* PPCI_MSIX_GET_TABLE_SIZE;
typedef void* PPCI_SET_ACS2;
typedef void* IOMMU_DEVICE_CREATION_CONFIGURATION_PASID;
typedef void* PIO_WORKITEM_ROUTINE;
typedef void* PIO_WORKITEM_ROUTINE_EX;
typedef void* PIO_CONTAINER_NOTIFICATION_FUNCTION;
typedef void* PDRIVER_NOTIFICATION_CALLBACK_ROUTINE;
typedef void* PDEVICE_CHANGE_COMPLETE_CALLBACK;
typedef void* WMI_NOTIFICATION_CALLBACK;
typedef void* PKBUGCHECK_CALLBACK_RECORD;
typedef void* PKBUGCHECK_REASON_CALLBACK_RECORD;
typedef void* PBOUND_CALLBACK;
typedef void* PKBUGCHECK_CALLBACK_ROUTINE;
typedef void* PKBUGCHECK_REASON_CALLBACK_ROUTINE;
typedef void* PNMI_CALLBACK;
typedef void* PPROCESSOR_CALLBACK_FUNCTION;
typedef void* PKSYNCHRONIZE_ROUTINE;
typedef void* KWAIT_REASON;
typedef void* PKWAIT_BLOCK;
typedef void* PMM_MDL_ROUTINE;
typedef void* LOCK_OPERATION;
typedef void* NOTIFICATION_MASK;
typedef void* PTRANSACTION_NOTIFICATION;
typedef void* PARTITION_INFORMATION_CLASS;
typedef void* PREQUEST_POWER_COMPLETE;
typedef void* PPTM_DEVICE_QUERY_GRANULARITY;
typedef void* PPTM_DEVICE_QUERY_TIME_SOURCE;
typedef void* PPTM_DEVICE_ENABLE;
typedef void* PPTM_DEVICE_DISABLE;
typedef void* PTIME_FIELDS;
typedef void* SECTION_INHERIT;
typedef void* PKINTERRUPT_ROUTINE;

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