#ifndef _NTIFS_H
#define _NTIFS_H

#include <NtAPI.h>
#include <LouDDK.h>
#include "ntoapi.h"
#include "irp.h"
#include "Misc/undocumentedTypes.h"



NTSTATUS AllocateVirtualMemoryExCallback(
	HANDLE CallbackContext,
	HANDLE ProcessHandle,
	PVOID* BaseAddress,
	PSIZE_T RegionSize,
	ULONG AllocationType,
	ULONG PageProtection,
	PMEM_EXTENDED_PARAMETER ExtendedParameters,
	ULONG ExtendedParameterCount
);

typedef struct _ATOMIC_CREATE_ECP_CONTEXT {
	USHORT               Size;
	USHORT               InFlags;
	USHORT               OutFlags;
	USHORT               ReparseBufferLength;
	PREPARSE_DATA_BUFFER ReparseBuffer;
	LONGLONG             FileSize;
	LONGLONG             ValidDataLength;
	PFILE_TIMESTAMPS     FileTimestamps;
	ULONG                FileAttributes;
	ULONG                UsnSourceInfo;
	USN                  Usn;
	ULONG                SuppressFileAttributeInheritanceMask;
	ULONG                InOpFlags;
	ULONG                OutOpFlags;
	ULONG                InGenFlags;
	ULONG                OutGenFlags;
	ULONG                CaseSensitiveFlagsMask;
	ULONG                InCaseSensitiveFlags;
	ULONG                OutCaseSensitiveFlags;
} ATOMIC_CREATE_ECP_CONTEXT, * PATOMIC_CREATE_ECP_CONTEXT;

typedef struct _BOOT_AREA_INFO {
	ULONG                    BootSectorCount;
	typedef struct {
		LARGE_INTEGER Offset;
	}__unnamed_struct_15fe_70;
	__unnamed_struct_15fe_70 BootSectors[2];
} BOOT_AREA_INFO, * PBOOT_AREA_INFO;

typedef struct _CC_FILE_SIZES {
	LARGE_INTEGER AllocationSize;
	LARGE_INTEGER FileSize;
	LARGE_INTEGER ValidDataLength;
} CC_FILE_SIZES, * PCC_FILE_SIZES;

BOOLEAN CcCanIWrite(
	 PFILE_OBJECT FileObject,
	 ULONG        BytesToWrite,
	 BOOLEAN      Wait,
	 UCHAR        Retrying
);

typedef struct _COPY_INFORMATION {
	PFILE_OBJECT SourceFileObject;
	LONGLONG     SourceFileOffset;
} COPY_INFORMATION, * PCOPY_INFORMATION;

typedef struct _FILE_ACCESS_INFORMATION {
  ACCESS_MASK AccessFlags;
} FILE_ACCESS_INFORMATION, *PFILE_ACCESS_INFORMATION;

typedef struct _FILE_EA_INFORMATION {
	ULONG EaSize;
} FILE_EA_INFORMATION, * PFILE_EA_INFORMATION;

typedef struct _FILE_MODE_INFORMATION {
	ULONG Mode;
} FILE_MODE_INFORMATION, * PFILE_MODE_INFORMATION;

typedef struct _FILE_ALL_INFORMATION {
  FILE_BASIC_INFORMATION     BasicInformation;
  FILE_STANDARD_INFORMATION  StandardInformation;
  FILE_INTERNAL_INFORMATION  InternalInformation;
  FILE_EA_INFORMATION        EaInformation;
  FILE_ACCESS_INFORMATION    AccessInformation;
  FILE_POSITION_INFORMATION  PositionInformation;
  FILE_MODE_INFORMATION      ModeInformation;
  FILE_ALIGNMENT_INFORMATION AlignmentInformation;
  FILE_NAME_INFORMATION      NameInformation;
} FILE_ALL_INFORMATION, *PFILE_ALL_INFORMATION;



BOOLEAN IoCheckFileObjectOpenedAsCopyDestination(
   PFILE_OBJECT FileObject
);

BOOLEAN IoCheckFileObjectOpenedAsCopySource(
   PFILE_OBJECT FileObject
);

struct _DEVICE_OBJECT* IoGetAttachedDeviceReference(
   struct _DEVICE_OBJECT* DeviceObject
);

PCONFIGURATION_INFORMATION IoGetConfigurationInformation();

void IoSetStartIoAttributes(
   struct _DEVICE_OBJECT* DeviceObject,
   BOOLEAN        DeferredStartIo,
   BOOLEAN        NonCancelable
);

void IoSizeOfIrp(
   uint64_t StackSize
);

void IoStartNextPacket(
   struct _DEVICE_OBJECT* DeviceObject,
   BOOLEAN        Cancelable
);

void IoStartNextPacketByKey(
   struct _DEVICE_OBJECT* DeviceObject,
   BOOLEAN        Cancelable,
   ULONG          Key
);

void IoStartPacket(
             struct _DEVICE_OBJECT* DeviceObject,
             PIRP           Irp,
   PULONG         Key,
   PDRIVER_CANCEL CancelFunction
);

void IoStartTimer(
   struct _DEVICE_OBJECT* DeviceObject
);

void IoStopTimer(
   struct _DEVICE_OBJECT* DeviceObject
);

void IoWriteErrorLogEntry(
   PVOID ElEntry
);

ULONG KeGetProcessorIndexFromNumber(
   PPROCESSOR_NUMBER ProcNumber
);

NTSTATUS KeGetProcessorNumberFromIndex(
    ULONG             ProcIndex,
   PPROCESSOR_NUMBER ProcNumber
);

BOOLEAN KeSetKernelStackSwapEnable(
   BOOLEAN Enable
);

NTHALAPI VOID KeStallExecutionProcessor(
   ULONG MicroSeconds
);

LOUDDK_API_ENTRY
NTSTATUS
NtAllocateVirtualMemory(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
);

LOUDDK_API_ENTRY
NTSTATUS 
NtClose(
  HANDLE Handle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtCopyFileChunk(
             HANDLE           SourceHandle,
             HANDLE           DestHandle,
  		 HANDLE           Event,
            PIO_STATUS_BLOCK IoStatusBlock,
             ULONG            Length,
             PLARGE_INTEGER   SourceOffset,
             PLARGE_INTEGER   DestOffset,
  		 PULONG           SourceKey,
  		 PULONG           DestKey,
             ULONG            Flags
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtCreateFile(
            PHANDLE            FileHandle,
             ACCESS_MASK        DesiredAccess,
             POBJECT_ATTRIBUTES ObjectAttributes,
            PIO_STATUS_BLOCK   IoStatusBlock,
  		 PLARGE_INTEGER     AllocationSize,
             ULONG              FileAttributes,
             ULONG              ShareAccess,
             ULONG              CreateDisposition,
             ULONG              CreateOptions,
  		 PVOID              EaBuffer,
             ULONG              EaLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtCreateSection(
            PHANDLE            SectionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PLARGE_INTEGER     MaximumSize,
             ULONG              SectionPageProtection,
             ULONG              AllocationAttributes,
   HANDLE             FileHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtCreateSectionEx(
            PHANDLE                 SectionHandle,
            ACCESS_MASK             DesiredAccess,
   POBJECT_ATTRIBUTES      ObjectAttributes,
   PLARGE_INTEGER          MaximumSize,
             ULONG                   SectionPageProtection,
             ULONG                   AllocationAttributes,
   HANDLE                  FileHandle,
          PMEM_EXTENDED_PARAMETER ExtendedParameters,
				 ULONG                   ExtendedParameterCount
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtDeviceIoControlFile(
              HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            IoControlCode,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtDuplicateToken(
    HANDLE             ExistingTokenHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    BOOLEAN            EffectiveOnly,
    TOKEN_TYPE         TokenType,
   PHANDLE            NewTokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtFlushBuffersFileEx(
    HANDLE           FileHandle,
    ULONG            Flags,
    PVOID            Parameters,
    ULONG            ParametersSize,
   PIO_STATUS_BLOCK IoStatusBlock
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtFreeVirtualMemory(
        HANDLE  ProcessHandle,
    PVOID   *BaseAddress,
    PSIZE_T RegionSize,
        ULONG   FreeType
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtFsControlFile(
              HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            FsControlCode,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtLockFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
             PLARGE_INTEGER   ByteOffset,
             PLARGE_INTEGER   Length,
             ULONG            Key,
             BOOLEAN          FailImmediately,
             BOOLEAN          ExclusiveLock
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenFile(
   PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
   PIO_STATUS_BLOCK   IoStatusBlock,
    ULONG              ShareAccess,
    ULONG              OpenOptions
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenProcessToken(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenProcessTokenEx(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenThreadToken(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtOpenThreadTokenEx(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtPrivilegeCheck(
        HANDLE         ClientToken,
    PPRIVILEGE_SET RequiredPrivileges,
       PBOOLEAN       Result
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryDirectoryFile(
             HANDLE                 FileHandle,
   HANDLE                 Event,
   PIO_APC_ROUTINE        ApcRoutine,
   PVOID                  ApcContext,
            PIO_STATUS_BLOCK       IoStatusBlock,
            PVOID                  FileInformation,
             ULONG                  Length,
             FILE_INFORMATION_CLASS FileInformationClass,
             BOOLEAN                ReturnSingleEntry,
   PUNICODE_STRING        FileName,
             BOOLEAN                RestartScan
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryDirectoryFileEx(
             HANDLE                 FileHandle,
   HANDLE                 Event,
   PIO_APC_ROUTINE        ApcRoutine,
   PVOID                  ApcContext,
            PIO_STATUS_BLOCK       IoStatusBlock,
            PVOID                  FileInformation,
             ULONG                  Length,
				 FILE_INFORMATION_CLASS FileInformationClass,
             ULONG                  QueryFlags,
   PUNICODE_STRING        FileName
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
   PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryInformationToken(
    HANDLE                  TokenHandle,
    TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
    ULONG                   TokenInformationLength,
   PULONG                  ReturnLength
);
KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryObject(
    HANDLE                   Handle,
              OBJECT_INFORMATION_CLASS ObjectInformationClass,
   PVOID                    ObjectInformation,
              ULONG                    ObjectInformationLength,
   PULONG                   ReturnLength
);
KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryQuotaInformationFile(
             HANDLE           FileHandle,
            PIO_STATUS_BLOCK IoStatusBlock,
            PVOID            Buffer,
             ULONG            Length,
             BOOLEAN          ReturnSingleEntry,
   PVOID            SidList,
             ULONG            SidListLength,
   PSID             StartSid,
             BOOLEAN          RestartScan
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQuerySecurityObject(
    HANDLE               Handle,
    SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG                Length,
   PULONG               LengthNeeded
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryVirtualMemory(
              HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
              MEMORY_INFORMATION_CLASS MemoryInformationClass,
             PVOID                    MemoryInformation,
              SIZE_T                   MemoryInformationLength,
   PSIZE_T                  ReturnLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtReadFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
            PVOID            Buffer,
             ULONG            Length,
   PLARGE_INTEGER   ByteOffset,
   PULONG           Key
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtSetInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
    PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtSetInformationThread(
   HANDLE          ThreadHandle,
   THREADINFOCLASS ThreadInformationClass,
   PVOID           ThreadInformation,
   ULONG           ThreadInformationLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtSetInformationToken(
   HANDLE                  TokenHandle,
   TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
   ULONG                   TokenInformationLength
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtSetQuotaInformationFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtSetSecurityObject(
   HANDLE               Handle,
   SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtUnlockFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER   ByteOffset,
    PLARGE_INTEGER   Length,
    ULONG            Key
);

KERNEL_ENTRY NTSYSCALLAPI NTSTATUS NtWriteFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
             PVOID            Buffer,
             ULONG            Length,
   PLARGE_INTEGER   ByteOffset,
   PULONG           Key
);

NTSTATUS PoCallDriver(
        struct _DEVICE_OBJECT*        DeviceObject,
    PIRP Irp
);

NTSTATUS PoClearPowerRequest(
    PVOID              PowerRequest,
        POWER_REQUEST_TYPE Type
);

NTSTATUS PoCreatePowerRequest(
   PVOID                   *PowerRequest,
    struct _DEVICE_OBJECT*          DeviceObject,
    PCOUNTED_REASON_CONTEXT Context
);

void PoDeletePowerRequest(
    PVOID PowerRequest
);

void PoEndDeviceBusy(
    PULONG IdlePointer
);

BOOLEAN PoQueryWatchdogTime(
    struct _DEVICE_OBJECT* Pdo,
   PULONG         SecondsRemaining
);

PULONG PoRegisterDeviceForIdleDetection(
   struct _DEVICE_OBJECT*     DeviceObject,
   ULONG              ConservationIdleTime,
   ULONG              PerformanceIdleTime,
   DEVICE_POWER_STATE State
);

NTSTATUS PoRegisterPowerSettingCallback(
   struct _DEVICE_OBJECT*          DeviceObject,
             LPCGUID                 SettingGuid,
             PPOWER_SETTING_CALLBACK Callback,
   PVOID                   Context,
            PVOID                   *Handle
);

PVOID PoRegisterSystemState(
    PVOID           StateHandle,
         EXECUTION_STATE Flags
);

void PoSetDeviceBusyEx(
    PULONG IdlePointer
);

NTSTATUS PoSetPowerRequest(
    PVOID              PowerRequest,
        POWER_REQUEST_TYPE Type
);

POWER_STATE PoSetPowerState(
   struct _DEVICE_OBJECT*   DeviceObject,
   POWER_STATE_TYPE Type,
   POWER_STATE      State
);

void PoStartDeviceBusy(
    PULONG IdlePointer
);

void PoStartNextPowerIrp(
    PIRP Irp
);

NTSTATUS PoUnregisterPowerSettingCallback(
    PVOID Handle
);

void PoUnregisterSystemState(
    PVOID StateHandle
);

PETHREAD PsGetCurrentThread();

BOOLEAN PsIsSystemThread(
   PETHREAD Thread
);

NTSYSAPI NTSTATUS RtlInitStringEx(
            PSTRING               DestinationString,
    PCSZ SourceString
);

NTSYSAPI NTSTATUS RtlUTF8ToUnicodeN(
   PWSTR  UnicodeStringDestination,
              ULONG  UnicodeStringMaxByteCount,
             PULONG UnicodeStringActualByteCount,
              PCCH   UTF8StringSource,
              ULONG  UTF8StringByteCount
);

void SeFreePrivileges(
   PPRIVILEGE_SET Privileges
);

NTSYSAPI NTSTATUS ZwAllocateVirtualMemory(
        HANDLE    ProcessHandle,
    PVOID     *BaseAddress,
        ULONG_PTR ZeroBits,
    PSIZE_T   RegionSize,
        ULONG     AllocationType,
        ULONG     Protect
);

NTSYSAPI NTSTATUS ZwCreateEvent(
            PHANDLE            EventHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
             EVENT_TYPE         EventType,
             BOOLEAN            InitialState
);

NTSYSAPI NTSTATUS ZwDeleteFile(
   POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSAPI NTSTATUS ZwDeviceIoControlFile(
              HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            IoControlCode,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength
);

NTSYSAPI NTSTATUS ZwDuplicateObject(
              HANDLE      SourceProcessHandle,
              HANDLE      SourceHandle,
    HANDLE      TargetProcessHandle,
   PHANDLE     TargetHandle,
              ACCESS_MASK DesiredAccess,
              ULONG       HandleAttributes,
              ULONG       Options
);

NTSYSAPI NTSTATUS ZwDuplicateToken(
    HANDLE             ExistingTokenHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    BOOLEAN            EffectiveOnly,
    TOKEN_TYPE         TokenType,
   PHANDLE            NewTokenHandle
);

NTSYSAPI NTSTATUS ZwFlushBuffersFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSAPI NTSTATUS ZwFlushBuffersFileEx(
    HANDLE           FileHandle,
		ULONG            FLags,
		PVOID            Parameters,
		ULONG            ParametersSize,
   PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSAPI NTSTATUS ZwFlushVirtualMemory(
        HANDLE           ProcessHandle,
    PVOID            *BaseAddress,
    PSIZE_T          RegionSize,
       PIO_STATUS_BLOCK IoStatus
);


NTSYSAPI NTSTATUS ZwFreeVirtualMemory(
        HANDLE  ProcessHandle,
    PVOID   *BaseAddress,
    PSIZE_T RegionSize,
        ULONG   FreeType
);

NTSYSAPI NTSTATUS ZwFsControlFile(
              HANDLE           FileHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            FsControlCode,
    PVOID            InputBuffer,
              ULONG            InputBufferLength,
   PVOID            OutputBuffer,
              ULONG            OutputBufferLength
);

NTSYSAPI NTSTATUS ZwLockFile(
             HANDLE           FileHandle,
   HANDLE           Event,
   PIO_APC_ROUTINE  ApcRoutine,
   PVOID            ApcContext,
            PIO_STATUS_BLOCK IoStatusBlock,
             PLARGE_INTEGER   ByteOffset,
             PLARGE_INTEGER   Length,
             ULONG            Key,
             BOOLEAN          FailImmediately,
             BOOLEAN          ExclusiveLock
);

NTSYSAPI NTSTATUS ZwNotifyChangeKey(
              HANDLE           KeyHandle,
    HANDLE           Event,
    PIO_APC_ROUTINE  ApcRoutine,
    PVOID            ApcContext,
             PIO_STATUS_BLOCK IoStatusBlock,
              ULONG            CompletionFilter,
              BOOLEAN          WatchTree,
   PVOID            Buffer,
              ULONG            BufferSize,
              BOOLEAN          Asynchronous
);

NTSYSAPI NTSTATUS ZwOpenDirectoryObject(
   PHANDLE            DirectoryHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSAPI NTSTATUS ZwOpenProcessTokenEx(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

NTSYSAPI NTSTATUS ZwOpenThreadTokenEx(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

NTSYSAPI NTSTATUS ZwQueryDirectoryFile(
             HANDLE                 FileHandle,
   HANDLE                 Event,
   PIO_APC_ROUTINE        ApcRoutine,
   PVOID                  ApcContext,
            PIO_STATUS_BLOCK       IoStatusBlock,
            PVOID                  FileInformation,
             ULONG                  Length,
             FILE_INFORMATION_CLASS FileInformationClass,
             BOOLEAN                ReturnSingleEntry,
   PUNICODE_STRING        FileName,
             BOOLEAN                RestartScan
);

NTSYSAPI NTSTATUS ZwQueryDirectoryFileEx(
             HANDLE                 FileHandle,
   HANDLE                 Event,
   PIO_APC_ROUTINE        ApcRoutine,
   PVOID                  ApcContext,
            PIO_STATUS_BLOCK       IoStatusBlock,
            PVOID                  FileInformation,
             ULONG                  Length,
             FILE_INFORMATION_CLASS FileInformationClass,
             ULONG                  QueryFlags,
   PUNICODE_STRING        FileName
);

NTSTATUS ZwQueryEaFile(
             HANDLE           FileHandle,
            PIO_STATUS_BLOCK IoStatusBlock,
            PVOID            Buffer,
             ULONG            Length,
             BOOLEAN          ReturnSingleEntry,
   PVOID            EaList,
             ULONG            EaListLength,
   PULONG           EaIndex,
             BOOLEAN          RestartScan
);

NTSYSAPI NTSTATUS ZwQueryInformationToken(
    HANDLE                  TokenHandle,
    TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
    ULONG                   TokenInformationLength,
   PULONG                  ReturnLength
);

NTSYSAPI NTSTATUS ZwQueryObject(
    HANDLE                   Handle,
              OBJECT_INFORMATION_CLASS ObjectInformationClass,
   PVOID                    ObjectInformation,
              ULONG                    ObjectInformationLength,
   PULONG                   ReturnLength
);

NTSYSAPI NTSTATUS ZwQueryQuotaInformationFile(
             HANDLE           FileHandle,
            PIO_STATUS_BLOCK IoStatusBlock,
            PVOID            Buffer,
             ULONG            Length,
             BOOLEAN          ReturnSingleEntry,
   PVOID            SidList,
             ULONG            SidListLength,
   PSID             StartSid,
             BOOLEAN          RestartScan
);

NTSYSAPI NTSTATUS ZwQuerySecurityObject(
    HANDLE               Handle,
    SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG                Length,
   PULONG               LengthNeeded
);

NTSYSAPI NTSTATUS ZwQueryVirtualMemory(
              HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
              MEMORY_INFORMATION_CLASS MemoryInformationClass,
             PVOID                    MemoryInformation,
              SIZE_T                   MemoryInformationLength,
   PSIZE_T                  ReturnLength
);

NTSYSAPI NTSTATUS ZwQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

NTSTATUS ZwSetEaFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

NTSYSAPI NTSTATUS ZwSetEvent(
              HANDLE EventHandle,
   PLONG  PreviousState
);

NTSYSAPI NTSTATUS ZwSetInformationToken(
   HANDLE                  TokenHandle,
   TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
   ULONG                   TokenInformationLength
);

NTSYSAPI NTSTATUS ZwSetInformationVirtualMemory(
   HANDLE                           ProcessHandle,
   VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
   ULONG_PTR                        NumberOfEntries,
   PMEMORY_RANGE_ENTRY              VirtualAddresses,
   PVOID                            VmInformation,
   ULONG                            VmInformationLength
);

NTSYSAPI NTSTATUS ZwSetQuotaInformationFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

NTSYSAPI NTSTATUS ZwSetSecurityObject(
   HANDLE               Handle,
   SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSAPI NTSTATUS ZwSetVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
    PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

NTSYSAPI NTSTATUS ZwUnlockFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER   ByteOffset,
    PLARGE_INTEGER   Length,
    ULONG            Key
);

NTSYSAPI NTSTATUS ZwWaitForSingleObject(
             HANDLE         Handle,
             BOOLEAN        Alertable,
   PLARGE_INTEGER Timeout
);


#endif