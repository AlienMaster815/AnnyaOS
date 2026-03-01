#ifndef _NTIFS_H
#define _NTIFS_H

#include <NtAPI.h>
#include <LouDDK.h>
#include "ntoapi.h"
#include "irp.h"
#include "Misc/undocumentedTypes.h"



LOUSTATUS AllocateVirtualMemoryExCallback(
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

LOUSTATUS KeGetProcessorNumberFromIndex(
    ULONG             ProcIndex,
   PPROCESSOR_NUMBER ProcNumber
);

BOOLEAN KeSetKernelStackSwapEnable(
   BOOLEAN Enable
);

NTHALAPI VOID KeStallExecutionProcessor(
   ULONG MicroSeconds
);

LOUAPI
LOUSTATUS
NtAllocateVirtualMemory(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
);

LOUAPI
LOUSTATUS 
NtClose(
  HANDLE Handle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtCopyFileChunk(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtCreateFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtCreateSection(
            PHANDLE            SectionHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
   PLARGE_INTEGER     MaximumSize,
             ULONG              SectionPageProtection,
             ULONG              AllocationAttributes,
   HANDLE             FileHandle
);

#define NtCreateSectionEx(a,b,c,d,e,f,g,h,i) LouKeVmmCreateSectionEx(a,b,c,d,e,f,g,h,i)

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtDeviceIoControlFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtDuplicateToken(
    HANDLE             ExistingTokenHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    BOOLEAN            EffectiveOnly,
    TOKEN_TYPE         TokenType,
   PHANDLE            NewTokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtFlushBuffersFileEx(
    HANDLE           FileHandle,
    ULONG            Flags,
    PVOID            Parameters,
    ULONG            ParametersSize,
   PIO_STATUS_BLOCK IoStatusBlock
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtFreeVirtualMemory(
        HANDLE  ProcessHandle,
    PVOID   *BaseAddress,
    PSIZE_T RegionSize,
        ULONG   FreeType
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtFsControlFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtLockFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtOpenFile(
   PHANDLE            FileHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
   PIO_STATUS_BLOCK   IoStatusBlock,
    ULONG              ShareAccess,
    ULONG              OpenOptions
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtOpenProcessToken(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtOpenProcessTokenEx(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtOpenThreadToken(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtOpenThreadTokenEx(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtPrivilegeCheck(
        HANDLE         ClientToken,
    PPRIVILEGE_SET RequiredPrivileges,
       PBOOLEAN       Result
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryDirectoryFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryDirectoryFileEx(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
   PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryInformationToken(
    HANDLE                  TokenHandle,
    TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
    ULONG                   TokenInformationLength,
   PULONG                  ReturnLength
);
KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryObject(
    HANDLE                   Handle,
              OBJECT_INFORMATION_CLASS ObjectInformationClass,
   PVOID                    ObjectInformation,
              ULONG                    ObjectInformationLength,
   PULONG                   ReturnLength
);
KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryQuotaInformationFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQuerySecurityObject(
    HANDLE               Handle,
    SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG                Length,
   PULONG               LengthNeeded
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryVirtualMemory(
              HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
              MEMORY_INFORMATION_CLASS MemoryInformationClass,
             PVOID                    MemoryInformation,
              SIZE_T                   MemoryInformationLength,
   PSIZE_T                  ReturnLength
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtReadFile(
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

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtSetInformationFile(
    HANDLE                 FileHandle,
   PIO_STATUS_BLOCK       IoStatusBlock,
    PVOID                  FileInformation,
    ULONG                  Length,
    FILE_INFORMATION_CLASS FileInformationClass
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtSetInformationThread(
   HANDLE          ThreadHandle,
   THREADINFOCLASS ThreadInformationClass,
   PVOID           ThreadInformation,
   ULONG           ThreadInformationLength
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtSetInformationToken(
   HANDLE                  TokenHandle,
   TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
   ULONG                   TokenInformationLength
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtSetQuotaInformationFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtSetSecurityObject(
   HANDLE               Handle,
   SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtUnlockFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER   ByteOffset,
    PLARGE_INTEGER   Length,
    ULONG            Key
);

KERNEL_ENTRY NTSYSCALLAPI LOUSTATUS NtWriteFile(
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

LOUSTATUS PoCallDriver(
        struct _DEVICE_OBJECT*        DeviceObject,
    PIRP Irp
);

LOUSTATUS PoClearPowerRequest(
    PVOID              PowerRequest,
        POWER_REQUEST_TYPE Type
);

LOUSTATUS PoCreatePowerRequest(
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

LOUSTATUS PoRegisterPowerSettingCallback(
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

LOUSTATUS PoSetPowerRequest(
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

LOUSTATUS PoUnregisterPowerSettingCallback(
    PVOID Handle
);

void PoUnregisterSystemState(
    PVOID StateHandle
);

PETHREAD PsGetCurrentThread();

BOOLEAN PsIsSystemThread(
   PETHREAD Thread
);

NTSYSAPI LOUSTATUS RtlInitStringEx(
            PSTRING               DestinationString,
    PCSZ SourceString
);

NTSYSAPI LOUSTATUS RtlUTF8ToUnicodeN(
   PWSTR  UnicodeStringDestination,
              ULONG  UnicodeStringMaxByteCount,
             PULONG UnicodeStringActualByteCount,
              PCCH   UTF8StringSource,
              ULONG  UTF8StringByteCount
);

void SeFreePrivileges(
   PPRIVILEGE_SET Privileges
);

NTSYSAPI LOUSTATUS ZwAllocateVirtualMemory(
        HANDLE    ProcessHandle,
    PVOID     *BaseAddress,
        ULONG_PTR ZeroBits,
    PSIZE_T   RegionSize,
        ULONG     AllocationType,
        ULONG     Protect
);

NTSYSAPI LOUSTATUS ZwCreateEvent(
            PHANDLE            EventHandle,
             ACCESS_MASK        DesiredAccess,
   POBJECT_ATTRIBUTES ObjectAttributes,
             EVENT_TYPE         EventType,
             BOOLEAN            InitialState
);

NTSYSAPI LOUSTATUS ZwDeleteFile(
   POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSAPI LOUSTATUS ZwDeviceIoControlFile(
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

NTSYSAPI LOUSTATUS ZwDuplicateObject(
              HANDLE      SourceProcessHandle,
              HANDLE      SourceHandle,
    HANDLE      TargetProcessHandle,
   PHANDLE     TargetHandle,
              ACCESS_MASK DesiredAccess,
              ULONG       HandleAttributes,
              ULONG       Options
);

NTSYSAPI LOUSTATUS ZwDuplicateToken(
    HANDLE             ExistingTokenHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    BOOLEAN            EffectiveOnly,
    TOKEN_TYPE         TokenType,
   PHANDLE            NewTokenHandle
);

NTSYSAPI LOUSTATUS ZwFlushBuffersFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSAPI LOUSTATUS ZwFlushBuffersFileEx(
    HANDLE           FileHandle,
		ULONG            FLags,
		PVOID            Parameters,
		ULONG            ParametersSize,
   PIO_STATUS_BLOCK IoStatusBlock
);

NTSYSAPI LOUSTATUS ZwFlushVirtualMemory(
        HANDLE           ProcessHandle,
    PVOID            *BaseAddress,
    PSIZE_T          RegionSize,
       PIO_STATUS_BLOCK IoStatus
);


NTSYSAPI LOUSTATUS ZwFreeVirtualMemory(
        HANDLE  ProcessHandle,
    PVOID   *BaseAddress,
    PSIZE_T RegionSize,
        ULONG   FreeType
);

NTSYSAPI LOUSTATUS ZwFsControlFile(
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

NTSYSAPI LOUSTATUS ZwLockFile(
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

NTSYSAPI LOUSTATUS ZwNotifyChangeKey(
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

NTSYSAPI LOUSTATUS ZwOpenDirectoryObject(
   PHANDLE            DirectoryHandle,
    ACCESS_MASK        DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes
);

NTSYSAPI LOUSTATUS ZwOpenProcessTokenEx(
    HANDLE      ProcessHandle,
    ACCESS_MASK DesiredAccess,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

NTSYSAPI LOUSTATUS ZwOpenThreadTokenEx(
    HANDLE      ThreadHandle,
    ACCESS_MASK DesiredAccess,
    BOOLEAN     OpenAsSelf,
    ULONG       HandleAttributes,
   PHANDLE     TokenHandle
);

NTSYSAPI LOUSTATUS ZwQueryDirectoryFile(
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

NTSYSAPI LOUSTATUS ZwQueryDirectoryFileEx(
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

LOUSTATUS ZwQueryEaFile(
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

NTSYSAPI LOUSTATUS ZwQueryInformationToken(
    HANDLE                  TokenHandle,
    TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
    ULONG                   TokenInformationLength,
   PULONG                  ReturnLength
);

NTSYSAPI LOUSTATUS ZwQueryObject(
    HANDLE                   Handle,
              OBJECT_INFORMATION_CLASS ObjectInformationClass,
   PVOID                    ObjectInformation,
              ULONG                    ObjectInformationLength,
   PULONG                   ReturnLength
);

NTSYSAPI LOUSTATUS ZwQueryQuotaInformationFile(
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

NTSYSAPI LOUSTATUS ZwQuerySecurityObject(
    HANDLE               Handle,
    SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor,
    ULONG                Length,
   PULONG               LengthNeeded
);

NTSYSAPI LOUSTATUS ZwQueryVirtualMemory(
              HANDLE                   ProcessHandle,
    PVOID                    BaseAddress,
              MEMORY_INFORMATION_CLASS MemoryInformationClass,
             PVOID                    MemoryInformation,
              SIZE_T                   MemoryInformationLength,
   PSIZE_T                  ReturnLength
);

NTSYSAPI LOUSTATUS ZwQueryVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
   PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

LOUSTATUS ZwSetEaFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

NTSYSAPI LOUSTATUS ZwSetEvent(
              HANDLE EventHandle,
   PLONG  PreviousState
);

NTSYSAPI LOUSTATUS ZwSetInformationToken(
   HANDLE                  TokenHandle,
   TOKEN_INFORMATION_CLASS TokenInformationClass,
   PVOID                   TokenInformation,
   ULONG                   TokenInformationLength
);

NTSYSAPI LOUSTATUS ZwSetInformationVirtualMemory(
   HANDLE                           ProcessHandle,
   VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
   ULONG_PTR                        NumberOfEntries,
   PMEMORY_RANGE_ENTRY              VirtualAddresses,
   PVOID                            VmInformation,
   ULONG                            VmInformationLength
);

NTSYSAPI LOUSTATUS ZwSetQuotaInformationFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PVOID            Buffer,
    ULONG            Length
);

NTSYSAPI LOUSTATUS ZwSetSecurityObject(
   HANDLE               Handle,
   SECURITY_INFORMATION SecurityInformation,
   PSECURITY_DESCRIPTOR SecurityDescriptor
);

NTSYSAPI LOUSTATUS ZwSetVolumeInformationFile(
    HANDLE               FileHandle,
   PIO_STATUS_BLOCK     IoStatusBlock,
    PVOID                FsInformation,
    ULONG                Length,
    FS_INFORMATION_CLASS FsInformationClass
);

NTSYSAPI LOUSTATUS ZwUnlockFile(
    HANDLE           FileHandle,
   PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER   ByteOffset,
    PLARGE_INTEGER   Length,
    ULONG            Key
);

NTSYSAPI LOUSTATUS ZwWaitForSingleObject(
             HANDLE         Handle,
             BOOLEAN        Alertable,
   PLARGE_INTEGER Timeout
);


#endif