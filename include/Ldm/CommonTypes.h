#ifndef _LDM_COMMON_TYPES_H
#define _LDM_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <WinAPI/Win32/winnt.h>
#include <WinAPI/Win32/winternl.h>
#include <cstdlib.h>
#include <Security.h>

#define CONST const
#define IRP_MJ_MAXIMUM_FUNCTION         0x1B

#define DEVICE_TYPE ULONG
#define MAXIMUM_VOLUME_LABEL_LENGTH  (32 * sizeof(WCHAR)) // 32 characters

typedef ULONG_PTR KSPIN_LOCK;
typedef KSPIN_LOCK *PKSPIN_LOCK;
typedef ULONG_PTR KAFFINITY;
typedef KAFFINITY *PKAFFINITY;
typedef USHORT SECURITY_DESCRIPTOR_CONTROL;

//#define KENCODED_TIMER_PROCESSOR        1

#define TIMER_TOLERABLE_DELAY_BITS      6
#define TIMER_EXPIRED_INDEX_BITS        6
#define TIMER_PROCESSOR_INDEX_BITS      5


typedef struct _DISPATCHER_HEADER {
    union {
        union {
            volatile LONG Lock;
            LONG LockNV;
        } DUMMYUNIONNAME;

        struct {                            // Events, Semaphores, Gates, etc.
            UCHAR Type;                     // All (accessible via KOBJECT_TYPE)
            UCHAR Signalling;
            UCHAR Size;
            UCHAR Reserved1;
        } DUMMYSTRUCTNAME;

        struct {                            // Timer
            UCHAR TimerType;
            union {
                UCHAR TimerControlFlags;
                struct {
                    UCHAR Absolute : 1;
                    UCHAR Wake : 1;
                    UCHAR EncodedTolerableDelay : TIMER_TOLERABLE_DELAY_BITS;
                } DUMMYSTRUCTNAME;
            };

            UCHAR Hand;
            union {
                UCHAR TimerMiscFlags;
                struct {

#if !defined(KENCODED_TIMER_PROCESSOR)

                    UCHAR Index : TIMER_EXPIRED_INDEX_BITS;

#else

                    UCHAR Index : 1;
                    UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;

#endif

                    UCHAR Inserted : 1;
                    volatile UCHAR Expired : 1;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
        } DUMMYSTRUCTNAME2;

        struct {                            // Timer2
            UCHAR Timer2Type;
            union {
                UCHAR Timer2Flags;
                struct {
                    UCHAR Timer2Inserted : 1;
                    UCHAR Timer2Expiring : 1;
                    UCHAR Timer2CancelPending : 1;
                    UCHAR Timer2SetPending : 1;
                    UCHAR Timer2Running : 1;
                    UCHAR Timer2Disabled : 1;
                    UCHAR Timer2ReservedFlags : 2;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            UCHAR Timer2ComponentId;
            UCHAR Timer2RelativeId;
        } DUMMYSTRUCTNAME3;

        struct {                            // Queue
            UCHAR QueueType;
            union {
                UCHAR QueueControlFlags;
                struct {
                    UCHAR Abandoned : 1;
                    UCHAR DisableIncrement : 1;
                    UCHAR QueueReservedControlFlags : 6;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            UCHAR QueueSize;
            UCHAR QueueReserved;
        } DUMMYSTRUCTNAME4;

        struct {                            // Thread
            UCHAR ThreadType;
            UCHAR ThreadReserved;

            union {
                UCHAR ThreadControlFlags;
                struct {
                    UCHAR CycleProfiling : 1;
                    UCHAR CounterProfiling : 1;
                    UCHAR GroupScheduling : 1;
                    UCHAR AffinitySet : 1;
                    UCHAR Tagged : 1;
                    UCHAR EnergyProfiling: 1;
                    UCHAR SchedulerAssist: 1;
                    UCHAR Instrumented : 1;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            union {
                UCHAR DebugActive;
            } DUMMYUNIONNAME2;
        } DUMMYSTRUCTNAME5;

        struct {                         // Mutant
            UCHAR MutantType;
            UCHAR MutantSize;
            BOOLEAN DpcActive;
            UCHAR MutantReserved;
        } DUMMYSTRUCTNAME6;
    } DUMMYUNIONNAME;

    LONG SignalState;                   // Object lock
    LIST_ENTRY WaitListHead;            // Object lock
} DISPATCHER_HEADER, *PDISPATCHER_HEADER;

struct _KDPC;

typedef
VOID
KDEFERRED_ROUTINE (
     struct _KDPC *Dpc,
     PVOID DeferredContext,
     PVOID SystemArgument1,
     PVOID SystemArgument2
    );

typedef KDEFERRED_ROUTINE *PKDEFERRED_ROUTINE;

typedef struct _KEVENT {
    DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT, PRKEVENT;

typedef struct _KDPC {
    union {
        ULONG TargetInfoAsUlong;
        struct {
            UCHAR Type;
            UCHAR Importance;
            volatile USHORT Number;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    //TODO:
    SINGLE_LIST_ENTRY DpcListEntry;
    KAFFINITY ProcessorHistory;
    PKDEFERRED_ROUTINE DeferredRoutine;
    PVOID DeferredContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    PVOID DpcData;
} KDPC, *PKDPC, *PRKDPC;

struct _DEVICE_OBJECT;
struct _DRIVER_OBJECT;
struct _IRP;

typedef
LOUSTATUS
DRIVER_ADD_DEVICE (
     struct _DRIVER_OBJECT *DriverObject,
     struct _DEVICE_OBJECT *PhysicalDeviceObject
    );

typedef DRIVER_ADD_DEVICE *PDRIVER_ADD_DEVICE;

typedef
LOUSTATUS
DRIVER_INITIALIZE (
     struct _DRIVER_OBJECT *DriverObject,
     PUNICODE_STRING RegistryPath
    );

typedef
VOID
DRIVER_UNLOAD (
     struct _DRIVER_OBJECT *DriverObject
    );

typedef DRIVER_UNLOAD *PDRIVER_UNLOAD;

typedef
LOUSTATUS
DRIVER_DISPATCH (
     struct _DEVICE_OBJECT *DeviceObject,
     struct _IRP *Irp
    );

typedef DRIVER_DISPATCH *PDRIVER_DISPATCH;

typedef DRIVER_INITIALIZE *PDRIVER_INITIALIZE;

typedef
VOID
DRIVER_STARTIO (
     struct _DEVICE_OBJECT *DeviceObject,
     struct _IRP *Irp
    );

typedef DRIVER_STARTIO *PDRIVER_STARTIO;

typedef struct _KDEVICE_QUEUE_ENTRY {
    LIST_ENTRY DeviceListEntry;
    ULONG SortKey;
    BOOLEAN Inserted;
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY, *PRKDEVICE_QUEUE_ENTRY;

typedef struct _KDEVICE_QUEUE {
    SHORT Type;
    SHORT Size;
    LIST_ENTRY DeviceListHead;
    KSPIN_LOCK Lock;
    union {
        bool Busy;
        struct {
            LONG64 Reserved : 8;
            LONG64 Hint : 56;
        };
    };    
} KDEVICE_QUEUE, *PKDEVICE_QUEUE, *PRKDEVICE_QUEUE;

typedef struct _IO_STATUS_BLOCK {
    union {
        LOUSTATUS Status;
        PVOID Pointer;
    } DUMMYUNIONNAME;

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

struct _FILE_OBJECT;

typedef
BOOLEAN
FAST_IO_READ (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     BOOLEAN Wait,
     ULONG LockKey,
     PVOID Buffer,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_READ *PFAST_IO_READ;

typedef enum _IO_ALLOCATION_ACTION {
    KeepObject = 1,
    DeallocateObject,
    DeallocateObjectKeepRegisters
}IO_ALLOCATION_ACTION, *PIO_ALLOCATION_ACTION;

typedef
IO_ALLOCATION_ACTION
DRIVER_CONTROL (
     struct _DEVICE_OBJECT *DeviceObject,
     struct _IRP *Irp,
     PVOID MapRegisterBase,
     PVOID Context
    );
typedef DRIVER_CONTROL *PDRIVER_CONTROL;

typedef
BOOLEAN
FAST_IO_CHECK_IF_POSSIBLE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     BOOLEAN Wait,
     ULONG LockKey,
     BOOLEAN CheckForReadOperation,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_CHECK_IF_POSSIBLE *PFAST_IO_CHECK_IF_POSSIBLE;

typedef struct _WAIT_CONTEXT_BLOCK {
    union {
        KDEVICE_QUEUE_ENTRY WaitQueueEntry;
        struct {
            LIST_ENTRY DmaWaitEntry;
            ULONG NumberOfChannels;
            ULONG SyncCallback : 1;
            ULONG DmaContext : 1;
            ULONG ZeroMapRegisters : 1;
            ULONG Reserved : 9;
            ULONG NumberOfRemapPages : 20;
        };
    };
    PDRIVER_CONTROL DeviceRoutine;
    PVOID DeviceContext;
    ULONG NumberOfMapRegisters;
    PVOID DeviceObject;
    PVOID CurrentIrp;
    PKDPC BufferChainingDpc;
} WAIT_CONTEXT_BLOCK, *PWAIT_CONTEXT_BLOCK;

typedef
BOOLEAN
FAST_IO_WRITE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     BOOLEAN Wait,
     ULONG LockKey,
     PVOID Buffer,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_WRITE *PFAST_IO_WRITE;

typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef
BOOLEAN
FAST_IO_QUERY_BASIC_INFO (
     struct _FILE_OBJECT *FileObject,
     BOOLEAN Wait,
     PFILE_BASIC_INFORMATION Buffer,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_BASIC_INFO *PFAST_IO_QUERY_BASIC_INFO;

typedef struct _FILE_STANDARD_INFORMATION {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;


typedef struct _KPROCESS *PEPROCESS;

typedef
BOOLEAN
FAST_IO_LOCK (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     PLARGE_INTEGER Length,
     PEPROCESS ProcessId,
     ULONG Key,
     BOOLEAN FailImmediately,
     BOOLEAN ExclusiveLock,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );


typedef FAST_IO_LOCK *PFAST_IO_LOCK;

typedef
BOOLEAN
FAST_IO_QUERY_STANDARD_INFO (
     struct _FILE_OBJECT *FileObject,
     BOOLEAN Wait,
     PFILE_STANDARD_INFORMATION Buffer,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_STANDARD_INFO *PFAST_IO_QUERY_STANDARD_INFO;

typedef
BOOLEAN
FAST_IO_UNLOCK_ALL (
     struct _FILE_OBJECT *FileObject,
     PEPROCESS ProcessId,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_ALL *PFAST_IO_UNLOCK_ALL;


typedef
BOOLEAN
FAST_IO_UNLOCK_SINGLE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     PLARGE_INTEGER Length,
     PEPROCESS ProcessId,
     ULONG Key,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_SINGLE *PFAST_IO_UNLOCK_SINGLE;

typedef
BOOLEAN
FAST_IO_UNLOCK_ALL_BY_KEY (
     struct _FILE_OBJECT *FileObject,
     PVOID ProcessId,
     ULONG Key,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_ALL_BY_KEY *PFAST_IO_UNLOCK_ALL_BY_KEY;

typedef
BOOLEAN
FAST_IO_DEVICE_CONTROL (
     struct _FILE_OBJECT *FileObject,
     BOOLEAN Wait,
     PVOID InputBuffer,
     ULONG InputBufferLength,
     PVOID OutputBuffer,
     ULONG OutputBufferLength,
     ULONG IoControlCode,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_DEVICE_CONTROL *PFAST_IO_DEVICE_CONTROL;

typedef
VOID
FAST_IO_RELEASE_FILE (
     struct _FILE_OBJECT *FileObject
    );

typedef FAST_IO_RELEASE_FILE *PFAST_IO_RELEASE_FILE;

typedef
VOID
FAST_IO_ACQUIRE_FILE (
     struct _FILE_OBJECT *FileObject
    );

typedef FAST_IO_ACQUIRE_FILE *PFAST_IO_ACQUIRE_FILE;


typedef
VOID
FAST_IO_DETACH_DEVICE (
     struct _DEVICE_OBJECT *SourceDevice,
     struct _DEVICE_OBJECT *TargetDevice
    );

typedef FAST_IO_DETACH_DEVICE *PFAST_IO_DETACH_DEVICE;

struct _FILE_NETWORK_OPEN_INFORMATION;

typedef
BOOLEAN
FAST_IO_QUERY_NETWORK_OPEN_INFO (
     struct _FILE_OBJECT *FileObject,
     BOOLEAN Wait,
     struct _FILE_NETWORK_OPEN_INFORMATION *Buffer,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_NETWORK_OPEN_INFO *PFAST_IO_QUERY_NETWORK_OPEN_INFO;

struct _ERESOURCE;

typedef
LOUSTATUS
FAST_IO_ACQUIRE_FOR_MOD_WRITE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER EndingOffset,
     struct _ERESOURCE **ResourceToRelease,
     struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_ACQUIRE_FOR_MOD_WRITE *PFAST_IO_ACQUIRE_FOR_MOD_WRITE;

typedef struct _MDL {
    struct _MDL *MdlNext;
    short MdlSize;
    short MdlFlags;
    struct _EPROCESS *Process;
    ULONG *lpMappedSystemVa;
    ULONG *lpStartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
} MDL;
typedef MDL *PMDL;


typedef
BOOLEAN
FAST_IO_MDL_READ (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     ULONG LockKey,
     PMDL *MdlChain,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ *PFAST_IO_MDL_READ;

typedef
BOOLEAN
FAST_IO_MDL_READ_COMPLETE (
     struct _FILE_OBJECT *FileObject,
     PMDL MdlChain,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ_COMPLETE *PFAST_IO_MDL_READ_COMPLETE;


typedef
BOOLEAN
FAST_IO_PREPARE_MDL_WRITE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     ULONG LockKey,
     PMDL *MdlChain,
     PIO_STATUS_BLOCK IoStatus,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_PREPARE_MDL_WRITE *PFAST_IO_PREPARE_MDL_WRITE;

typedef
BOOLEAN
FAST_IO_MDL_WRITE_COMPLETE (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     PMDL MdlChain,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_WRITE_COMPLETE *PFAST_IO_MDL_WRITE_COMPLETE;

struct _COMPRESSED_DATA_INFO;

typedef
BOOLEAN
FAST_IO_READ_COMPRESSED (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     ULONG LockKey,
     PVOID Buffer,
     PMDL *MdlChain,
     PIO_STATUS_BLOCK IoStatus,
     struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
     ULONG CompressedDataInfoLength,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_READ_COMPRESSED *PFAST_IO_READ_COMPRESSED;

typedef
BOOLEAN
FAST_IO_WRITE_COMPRESSED (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     ULONG Length,
     ULONG LockKey,
     PVOID Buffer,
     PMDL *MdlChain,
     PIO_STATUS_BLOCK IoStatus,
     struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
     ULONG CompressedDataInfoLength,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_WRITE_COMPRESSED *PFAST_IO_WRITE_COMPRESSED;

typedef
BOOLEAN
FAST_IO_MDL_READ_COMPLETE_COMPRESSED (
     struct _FILE_OBJECT *FileObject,
     PMDL MdlChain,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ_COMPLETE_COMPRESSED *PFAST_IO_MDL_READ_COMPLETE_COMPRESSED;

typedef
BOOLEAN
FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED (
     struct _FILE_OBJECT *FileObject,
     PLARGE_INTEGER FileOffset,
     PMDL MdlChain,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED *PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED;

typedef struct _FILE_NETWORK_OPEN_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;


typedef
BOOLEAN
FAST_IO_QUERY_OPEN (
     struct _IRP *Irp,
     PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
     struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_OPEN *PFAST_IO_QUERY_OPEN;

typedef
LOUSTATUS
FAST_IO_RELEASE_FOR_MOD_WRITE (
     struct _FILE_OBJECT *FileObject,
     struct _ERESOURCE *ResourceToRelease,
     struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_RELEASE_FOR_MOD_WRITE *PFAST_IO_RELEASE_FOR_MOD_WRITE;

typedef
LOUSTATUS
FAST_IO_ACQUIRE_FOR_CCFLUSH (
     struct _FILE_OBJECT *FileObject,
     struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_ACQUIRE_FOR_CCFLUSH *PFAST_IO_ACQUIRE_FOR_CCFLUSH;

typedef
LOUSTATUS
FAST_IO_RELEASE_FOR_CCFLUSH (
     struct _FILE_OBJECT *FileObject,
     struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_RELEASE_FOR_CCFLUSH *PFAST_IO_RELEASE_FOR_CCFLUSH;

typedef struct _FAST_IO_DISPATCH {
    ULONG SizeOfFastIoDispatch;
    PFAST_IO_CHECK_IF_POSSIBLE FastIoCheckIfPossible;
    PFAST_IO_READ FastIoRead;
    PFAST_IO_WRITE FastIoWrite;
    PFAST_IO_QUERY_BASIC_INFO FastIoQueryBasicInfo;
    PFAST_IO_QUERY_STANDARD_INFO FastIoQueryStandardInfo;
    PFAST_IO_LOCK FastIoLock;
    PFAST_IO_UNLOCK_SINGLE FastIoUnlockSingle;
    PFAST_IO_UNLOCK_ALL FastIoUnlockAll;
    PFAST_IO_UNLOCK_ALL_BY_KEY FastIoUnlockAllByKey;
    PFAST_IO_DEVICE_CONTROL FastIoDeviceControl;
    PFAST_IO_ACQUIRE_FILE AcquireFileForNtCreateSection;
    PFAST_IO_RELEASE_FILE ReleaseFileForNtCreateSection;
    PFAST_IO_DETACH_DEVICE FastIoDetachDevice;
    PFAST_IO_QUERY_NETWORK_OPEN_INFO FastIoQueryNetworkOpenInfo;
    PFAST_IO_ACQUIRE_FOR_MOD_WRITE AcquireForModWrite;
    PFAST_IO_MDL_READ MdlRead;
    PFAST_IO_MDL_READ_COMPLETE MdlReadComplete;
    PFAST_IO_PREPARE_MDL_WRITE PrepareMdlWrite;
    PFAST_IO_MDL_WRITE_COMPLETE MdlWriteComplete;
    PFAST_IO_READ_COMPRESSED FastIoReadCompressed;
    PFAST_IO_WRITE_COMPRESSED FastIoWriteCompressed;
    PFAST_IO_MDL_READ_COMPLETE_COMPRESSED MdlReadCompleteCompressed;
    PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED MdlWriteCompleteCompressed;
    PFAST_IO_QUERY_OPEN FastIoQueryOpen;
    PFAST_IO_RELEASE_FOR_MOD_WRITE ReleaseForModWrite;
    PFAST_IO_ACQUIRE_FOR_CCFLUSH AcquireForCcFlush;
    PFAST_IO_RELEASE_FOR_CCFLUSH ReleaseForCcFlush;
} FAST_IO_DISPATCH, *PFAST_IO_DISPATCH;

typedef struct _VPB {
    SHORT Type;
    SHORT Size;
    USHORT Flags;
    USHORT VolumeLabelLength;   // in bytes
    struct _DEVICE_OBJECT *DeviceObject;
    struct _DEVICE_OBJECT *RealDevice;
    ULONG SerialNumber;
    ULONG ReferenceCount;
    WCHAR VolumeLabel[MAXIMUM_VOLUME_LABEL_LENGTH / sizeof(WCHAR)];
} VPB, *PVPB;

typedef struct _VPB *PVPB;

typedef struct _DRIVER_EXTENSION {
    struct _DRIVER_OBJECT *DriverObject;
    PDRIVER_ADD_DEVICE AddDevice;
    ULONG Count;
    UNICODE_STRING ServiceKeyName;
} DRIVER_EXTENSION, *PDRIVER_EXTENSION;

typedef struct _IO_TIMER *PIO_TIMER;

typedef struct _DEVICE_OBJECT {
  SHORT                   Type;
  USHORT                   Size;
  LONG                     ReferenceCount;
  struct _DRIVER_OBJECT    *DriverObject;
  struct _DEVICE_OBJECT    *NextDevice;
  struct _DEVICE_OBJECT    *AttachedDevice;
  struct _IRP              *CurrentIrp;
  PIO_TIMER                Timer;
  ULONG                    Flags;
  ULONG                    Characteristics;
  PVPB          Vpb;
  PVOID                    DeviceExtension;
  DEVICE_TYPE              DeviceType;
  CHAR                     StackSize;
  union {
    LIST_ENTRY         ListEntry;
    WAIT_CONTEXT_BLOCK Wcb;
  } Queue;
  ULONG                    AlignmentRequirement;
  KDEVICE_QUEUE            DeviceQueue;
  KDPC                     Dpc;
  ULONG                    ActiveThreadCount;
  PSECURITY_DESCRIPTOR     SecurityDescriptor;
  KEVENT                   DeviceLock;
  USHORT                   SectorSize;
  USHORT                   Spare1;
  struct _DEVOBJ_EXTENSION *DeviceObjectExtension;
  PVOID                    Reserved;
  //LDM
  struct _PCI_DEVICE_OBJECT*    PDEV;
  uint64_t                      DeviceID;
} DEVICE_OBJECT, *PDEVICE_OBJECT;

typedef struct _DEVOBJ_EXTENSION {
    SHORT          Type;
    USHORT          Size;
    PDEVICE_OBJECT  DeviceObject;
    ULONG           PowerFlags;
    struct          _DEVICE_OBJECT_POWER_EXTENSION  *Dope;
    ULONG ExtensionFlags;
    PVOID           DeviceNode;
    PDEVICE_OBJECT  AttachedTo;
    LONG StartIoCount;
    LONG           StartIoKey;
    ULONG          StartIoFlags;
    PVPB           Vpb;
    PVOID DependencyNode;
    PVOID InterruptContext;
    LONG InterruptCount;
    PVOID VerifierContext;
} DEVOBJ_EXTENSION, *PDEVOBJ_EXTENSION;

typedef struct _DRIVER_OBJECT {
  SHORT              Type;
  SHORT              Size;
  PDEVICE_OBJECT     DeviceObject;
  ULONG              Flags;
  PVOID              DriverStart;
  ULONG              DriverSize;
  PVOID              DriverSection;
  PDRIVER_EXTENSION  DriverExtension;
  UNICODE_STRING     DriverName;
  PUNICODE_STRING    HardwareDatabase;
  PFAST_IO_DISPATCH  FastIoDispatch;
  PDRIVER_INITIALIZE DriverInit;
  PDRIVER_STARTIO    DriverStartIo;
  PDRIVER_UNLOAD     DriverUnload;
  PDRIVER_DISPATCH   MajorFunction[IRP_MJ_MAXIMUM_FUNCTION + 1];
  //DriverObjectModificationss for ldm
  bool              DriverUsingLkdm;
  uintptr_t         DeviceTable;
} DRIVER_OBJECT, * PDRIVER_OBJECT;

#ifdef __cplusplus
}
#endif
#endif