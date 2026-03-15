#ifndef _LOUIFS_H
#define _LOUIFS_H

#include <Ldm.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _FILE_OBJECT;

typedef struct _ATOMIC_CREATE_ECP_CONTEXT{
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
}ATOMIC_CREATE_ECP_CONTEXT, * PATOMIC_CREATE_ECP_CONTEXT;

typedef struct _BOOT_AREA_INFO {
	ULONG               BootSectorCount;
    struct{
		LARGE_INTEGER   Offset;
	}                   BootSectors[2];
} BOOT_AREA_INFO, * PBOOT_AREA_INFO;

typedef struct _CC_FILE_SIZES{
	LARGE_INTEGER   AllocationSize;
	LARGE_INTEGER   FileSize;
	LARGE_INTEGER   ValidDataLength;
}CC_FILE_SIZES, * PCC_FILE_SIZES;

typedef struct _COPY_INFORMATION{
	struct _FILE_OBJECT*    SourceFileObject;
	LONGLONG                SourceFileOffset;
}COPY_INFORMATION, * PCOPY_INFORMATION;

typedef struct _FILE_ACCESS_INFORMATION{
    ACCESS_MASK     AccessFlags;
}FILE_ACCESS_INFORMATION, * PFILE_ACCESS_INFORMATION;

typedef struct _FILE_EA_INFORMATION{
	ULONG   EaSize;
}FILE_EA_INFORMATION, * PFILE_EA_INFORMATION;

typedef struct _FILE_MODE_INFORMATION{
	ULONG   Mode;
}FILE_MODE_INFORMATION, * PFILE_MODE_INFORMATION;

typedef struct _FILE_ALL_INFORMATION{
    FILE_BASIC_INFORMATION        BasicInformation;
    FILE_STANDARD_INFORMATION     StandardInformation;
    FILE_INTERNAL_INFORMATION     InternalInformation;
    FILE_EA_INFORMATION           EaInformation;
    FILE_ACCESS_INFORMATION       AccessInformation;
    FILE_POSITION_INFORMATION     PositionInformation;
    FILE_MODE_INFORMATION         ModeInformation;
    FILE_ALIGNMENT_INFORMATION    AlignmentInformation;
    FILE_NAME_INFORMATION         NameInformation;
}FILE_ALL_INFORMATION, * PFILE_ALL_INFORMATION;

struct _FILE_OBJECT;
struct _IRP;

typedef 
void 
DRIVER_CANCEL(
    struct _DEVICE_OBJECT* DeviceObject,
    struct _IRP* Irp
);
typedef DRIVER_CANCEL* PDRIVER_CANCEL;

struct _COUNTED_REASON_CONTEXT;

typedef enum _POWER_STATE_TYPE{
    SystemPowerState = 0,
    DevicePowerStatem,
}POWER_STATE_TYPE, * PPOWER_STATE_TYPE;


#ifndef _USER_MODE_CODE_

KERNEL_EXPORT LOUSTATUS LouKeAllocateVirtualMemoryExCallback(HANDLE CallbackContext, HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG AllocationType, ULONG PageProtection, PMEM_EXTENDED_PARAMETER ExtendedParameters, ULONG ExtendedParameterCount);
KERNEL_EXPORT BOOLEAN LouKeCcCanIWrite(struct _FILE_OBJECT* FileObject, ULONG BytesToWrite, BOOLEAN Wait, UCHAR Retrying);

KERNEL_EXPORT BOOLEAN LouKeIoCheckFileObjectOpenedAsCopyDestination(struct _FILE_OBJECT* FileObject);
KERNEL_EXPORT BOOLEAN LouKeIoCheckFileObjectOpenedAsCopySource(struct _FILE_OBJECT* FileObject);
KERNEL_EXPORT PDEVICE_OBJECT LouKeIoGetAttachedDeviceReference(PDEVICE_OBJECT DeviceObject);
KERNEL_EXPORT void LouKeIoSetStartIoAttributes(PDEVICE_OBJECT DeviceObject, BOOLEAN DeferredStartIo, BOOLEAN NonCancelable);
KERNEL_EXPORT void LouKeIoSizeOfIrp(uint64_t StackSize);
KERNEL_EXPORT void LouKeIoStartNextPacket(PDEVICE_OBJECT DeviceObject, BOOLEAN Cancelable);
KERNEL_EXPORT void LouKeIoStartNextPacketByKey(PDEVICE_OBJECT DeviceObject, BOOLEAN Cancelable, ULONG Key);
KERNEL_EXPORT void LouKeIoStartPacket(PDEVICE_OBJECT DeviceObject, struct _IRP* Irp, PULONG Key, PDRIVER_CANCEL CancelFunction);
KERNEL_EXPORT void LouKeIoStartTimer(PDEVICE_OBJECT DeviceObject);
KERNEL_EXPORT void LouKeIoStopTimer(PDEVICE_OBJECT DeviceObject);
KERNEL_EXPORT void LouKeIoWriteErrorLogEntry(PVOID ElEntry);

//KE START
KERNEL_EXPORT ULONG LouKeKeGetProcessorIndexFromNumber(PPROCESSOR_NUMBER ProcNumber);
KERNEL_EXPORT LOUSTATUS LouKeKeGetProcessorNumberFromIndex(ULONG ProcIndex, PPROCESSOR_NUMBER ProcNumber);
KERNEL_EXPORT BOOLEAN LouKeSetKernelStackSwapEnable(BOOLEAN Enable);
KERNEL_EXPORT VOID LouKeStallExecutionProcessor(ULONG MicroSeconds);
//KE END

KERNEL_EXPORT LOUSTATUS LouKeAllocateVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
KERNEL_EXPORT LOUSTATUS LouKeClose(HANDLE Handle);
KERNEL_EXPORT LOUSTATUS LouKeCopyFileChunk(HANDLE SourceHandle, HANDLE DestHandle, HANDLE Event, PIO_STATUS_BLOCK IoStatusBlock, ULONG Length, PLARGE_INTEGER SourceOffset, PLARGE_INTEGER DestOffset, PULONG SourceKey, PULONG DestKey, ULONG Flags);
KERNEL_EXPORT LOUSTATUS LouKeCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
KERNEL_EXPORT LOUSTATUS LouKeCreateSection(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize, ULONG SectionPageProtection, ULONG AllocationAttributes, HANDLE FileHandle);
KERNEL_EXPORT LOUSTATUS LouKeDeviceIoControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG IoControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);
KERNEL_EXPORT LOUSTATUS LouKeDuplicateToken(HANDLE ExistingTokenHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, BOOLEAN EffectiveOnly, TOKEN_TYPE TokenType, PHANDLE NewTokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeFlushBuffersFileEx(HANDLE FileHandle, ULONG Flags, PVOID Parameters, ULONG ParametersSize, PIO_STATUS_BLOCK IoStatusBlock);
KERNEL_EXPORT LOUSTATUS LouKeFreeVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG FreeType);
KERNEL_EXPORT LOUSTATUS LouKeFsControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG FsControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);
KERNEL_EXPORT LOUSTATUS LouKeLockFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER ByteOffset, PLARGE_INTEGER Length, ULONG Key, BOOLEAN FailImmediately, BOOLEAN ExclusiveLock);
KERNEL_EXPORT LOUSTATUS LouKeOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions);
KERNEL_EXPORT LOUSTATUS LouKeOpenProcessToken(HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeOpenProcessTokenEx(HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, ULONG HandleAttributes, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeOpenThreadToken(HANDLE ThreadHandle, ACCESS_MASK DesiredAccess, BOOLEAN OpenAsSelf, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeOpenThreadTokenEx(HANDLE ThreadHandle, ACCESS_MASK DesiredAccess, BOOLEAN OpenAsSelf, ULONG HandleAttributes, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKePrivilegeCheck(HANDLE ClientToken, PPRIVILEGE_SET RequiredPrivileges, PBOOLEAN Result);
KERNEL_EXPORT LOUSTATUS LouKeQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);
KERNEL_EXPORT LOUSTATUS LouKeQueryDirectoryFileEx(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, ULONG QueryFlags, PUNICODE_STRING FileName);
KERNEL_EXPORT LOUSTATUS LouKeQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);
KERNEL_EXPORT LOUSTATUS LouKeQueryInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength, PULONG ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeQueryObject(HANDLE Handle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeQueryQuotaInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, BOOLEAN ReturnSingleEntry, PVOID SidList, ULONG SidListLength, PSID StartSid, BOOLEAN RestartScan);
KERNEL_EXPORT LOUSTATUS LouKeQuerySecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG Length, PULONG LengthNeeded);
KERNEL_EXPORT LOUSTATUS LouKeQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FS_INFORMATION_CLASS FsInformationClass);
KERNEL_EXPORT LOUSTATUS LouKeReadFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);
KERNEL_EXPORT LOUSTATUS LouKeSetInformationFile( HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);
KERNEL_EXPORT LOUSTATUS LouKeSetInformationThread(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
KERNEL_EXPORT LOUSTATUS LouKeSetInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength);
KERNEL_EXPORT LOUSTATUS LouKeSetQuotaInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length);
KERNEL_EXPORT LOUSTATUS LouKeSetSecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor);
KERNEL_EXPORT LOUSTATUS LouKeUnlockFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER ByteOffset, PLARGE_INTEGER Length, ULONG Key);
KERNEL_EXPORT LOUSTATUS LouKeWriteFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);

KERNEL_EXPORT LOUSTATUS LouKePoCallDriver(PDEVICE_OBJECT DeviceObject, struct _IRP* Irp);
KERNEL_EXPORT LOUSTATUS LouKePoClearPowerRequest(PVOID PowerRequest, POWER_REQUEST_TYPE Type);
KERNEL_EXPORT LOUSTATUS LouKePoCreatePowerRequest(PVOID* PowerRequest, PDEVICE_OBJECT DeviceObject, struct _COUNTED_REASON_CONTEXT* Context);
KERNEL_EXPORT void LouKePoDeletePowerRequest(PVOID PowerRequest);
KERNEL_EXPORT void LouKePoEndDeviceBusy(PULONG IdlePointer);
KERNEL_EXPORT BOOLEAN LouKePoQueryWatchdogTime(PDEVICE_OBJECT Pdo, PULONG SecondsRemaining);
KERNEL_EXPORT PULONG LouKePoRegisterDeviceForIdleDetection(PDEVICE_OBJECT DeviceObject, ULONG ConservationIdleTime, ULONG PerformanceIdleTime, DEVICE_POWER_STATE State);
KERNEL_EXPORT LOUSTATUS LouKePoRegisterPowerSettingCallback(PDEVICE_OBJECT DeviceObject, LPCGUID SettingGuid, PPOWER_SETTING_CALLBACK Callback, PVOID Context, PVOID* Handle);
KERNEL_EXPORT PVOID LouKePoRegisterSystemState(PVOID StateHandle, EXECUTION_STATE Flags);
KERNEL_EXPORT void LouKePoSetDeviceBusyEx(PULONG IdlePointer);
KERNEL_EXPORT LOUSTATUS LouKePoSetPowerRequest(PVOID PowerRequest, POWER_REQUEST_TYPE Type);
KERNEL_EXPORT POWER_STATE LouKePoSetPowerState(PDEVICE_OBJECT DeviceObject, POWER_STATE_TYPE Type, POWER_STATE State);
KERNEL_EXPORT void LouKePoStartDeviceBusy(PULONG IdlePointer);
KERNEL_EXPORT void LouKePoStartNextPowerIrp(struct _IRP* Irp);
KERNEL_EXPORT LOUSTATUS LouKePoUnregisterPowerSettingCallback(PVOID Handle);
KERNEL_EXPORT void LouKePoUnregisterSystemState(PVOID StateHandle);

KERNEL_EXPORT BOOLEAN LouKePsIsSystemThread(PETHREAD Thread);

KERNEL_EXPORT LOUSTATUS LouKeRtlInitStringEx(PSTRING DestinationString, PCSZ SourceString);
KERNEL_EXPORT LOUSTATUS LouKeRtlUTF8ToUnicodeN(PWSTR UnicodeStringDestination, ULONG UnicodeStringMaxByteCount, PULONG UnicodeStringActualByteCount, PCCH UTF8StringSource, ULONG UTF8StringByteCount);

KERNEL_EXPORT void LouKeSeFreePrivileges(PPRIVILEGE_SET Privileges);

KERNEL_EXPORT LOUSTATUS LouKeZwAllocateVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
KERNEL_EXPORT LOUSTATUS LouKeZwCreateEvent(PHANDLE EventHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, EVENT_TYPE EventType, BOOLEAN InitialState);
KERNEL_EXPORT LOUSTATUS LouKeZwDeleteFile(POBJECT_ATTRIBUTES ObjectAttributes);
KERNEL_EXPORT LOUSTATUS LouKeZwDuplicateObject(HANDLE SourceProcessHandle, HANDLE SourceHandle, HANDLE TargetProcessHandle, PHANDLE TargetHandle, ACCESS_MASK DesiredAccess, ULONG HandleAttributes, ULONG Options);
KERNEL_EXPORT LOUSTATUS LouKeZwDuplicateToken(HANDLE ExistingTokenHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, BOOLEAN EffectiveOnly, TOKEN_TYPE TokenType, PHANDLE NewTokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeZwFlushBuffersFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock);
KERNEL_EXPORT LOUSTATUS LouKeZwFlushBuffersFileEx(HANDLE FileHandle, ULONG FLags, PVOID Parameters, ULONG ParametersSize, PIO_STATUS_BLOCK IoStatusBlock);
KERNEL_EXPORT LOUSTATUS LouKeZwFlushVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, PIO_STATUS_BLOCK IoStatus);
KERNEL_EXPORT LOUSTATUS LouKeZwFreeVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG FreeType);
KERNEL_EXPORT LOUSTATUS LouKeZwFsControlFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG FsControlCode, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength);
KERNEL_EXPORT LOUSTATUS LouKeZwLockFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER ByteOffset, PLARGE_INTEGER Length, ULONG Key, BOOLEAN FailImmediately, BOOLEAN ExclusiveLock);
KERNEL_EXPORT LOUSTATUS LouKeZwNotifyChangeKey(HANDLE KeyHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG CompletionFilter, BOOLEAN WatchTree, PVOID Buffer, ULONG BufferSize, BOOLEAN Asynchronous);
KERNEL_EXPORT LOUSTATUS LouKeZwOpenDirectoryObject(PHANDLE DirectoryHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes);
KERNEL_EXPORT LOUSTATUS LouKeZwOpenProcessTokenEx(HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, ULONG HandleAttributes, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeZwOpenThreadTokenEx(HANDLE ThreadHandle, ACCESS_MASK DesiredAccess, BOOLEAN OpenAsSelf, ULONG HandleAttributes, PHANDLE TokenHandle);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryDirectoryFileEx(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, ULONG QueryFlags, PUNICODE_STRING FileName);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryEaFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, BOOLEAN ReturnSingleEntry, PVOID EaList, ULONG EaListLength, PULONG EaIndex, BOOLEAN RestartScan);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength, PULONG ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryObject(HANDLE Handle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryQuotaInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, BOOLEAN ReturnSingleEntry, PVOID SidList, ULONG SidListLength, PSID StartSid, BOOLEAN RestartScan);
KERNEL_EXPORT LOUSTATUS LouKeZwQuerySecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG Length, PULONG LengthNeeded);
KERNEL_EXPORT LOUSTATUS LouKeZwQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
KERNEL_EXPORT LOUSTATUS LouKeZwSetEaFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length);
KERNEL_EXPORT LOUSTATUS LouKeZwSetEvent(HANDLE EventHandle, PLONG PreviousState);
KERNEL_EXPORT LOUSTATUS LouKeZwSetInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength);
KERNEL_EXPORT LOUSTATUS LouKeZwSetInformationVirtualMemory(HANDLE ProcessHandle, VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass, ULONG_PTR NumberOfEntries, PMEMORY_RANGE_ENTRY VirtualAddresses, PVOID VmInformation, ULONG VmInformationLength);
KERNEL_EXPORT LOUSTATUS LouKeZwSetQuotaInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length);
KERNEL_EXPORT LOUSTATUS LouKeZwSetSecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor);
KERNEL_EXPORT LOUSTATUS LouKeZwSetVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FS_INFORMATION_CLASS FsInformationClass);
KERNEL_EXPORT LOUSTATUS LouKeZwUnlockFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER ByteOffset, PLARGE_INTEGER Length, ULONG Key);
KERNEL_EXPORT LOUSTATUS LouKeZwWaitForSingleObject(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout);
#endif

#ifdef __cplusplus
}
#endif
#endif