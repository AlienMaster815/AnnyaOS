#ifndef _KERNEL_EFI_H
#define _KERNEL_EFI_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

#include <cstdint.h>
#include "EfiStubs.h"
#include "Smbios.h"

#define EFI_STATUS_SUCCESS               
#define EFI_STATUS_LOAD_ERROR           (1 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_INVALID_PARAMETER    (2 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_UNSUPORTED           (3 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_BAD_BUFFER_SIZE      (4 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_BUFFER_TOO_SMALL     (5 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_NOT_READY            (6 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_DEVICE_ERROR         (7 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_WRITE_PROTECTED      (8 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_OUT_OF_RESOURCES     (9 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_NOT_FOUND            (14 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_ACCESS_DENIED        (15 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_TIMEOUT              (18 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_ABORTED              (21 | (1 << ((sizeof(long) * 8) - 1)))
#define EFI_STATUS_SECURITY_VILATION    (26 | (1 << ((sizeof(long) * 8) - 1)))

#ifndef _EFI_TYPES
#define _EFI_TYPES
typedef unsigned long   EFI_STATUS;
typedef bool            EFI_BOOL;
typedef uint8_t         EFI_UINT8;
typedef uint16_t        EFI_UINT16;
typedef uint32_t        EFI_UINT32;
typedef uint64_t        EFI_UINT64;
typedef int8_t          EFI_INT8;
typedef int16_t         EFI_INT16;
typedef int32_t         EFI_INT32;
typedef int64_t         EFI_INT64;
typedef uintptr_t       EFI_PHYSICAL_ADDRESS;
typedef void*           EFI_HANDLE;
#endif

typedef struct _EFI_GUID{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[8];
} EFI_GUID, * PEFI_GUID;

#define DEFINE_EFI_GUID(Alpha, Brovo, Charlie, Delta...)((EFI_GUID){                        \
    (Alpha) & 0xFF, ((Alpha) >> 8) & 0xFF, ((Alpha) >> 16) & 0xFF, {((Alpha) >> 24) & 0xFF, \
    (Brovo) & 0xFF, ((Bravo) >> 8) & 0xFF,                                                  \
    (Charlie) & 0xFF, ((Charlie) >> 8) & 0xFF, Delta}                                       \
})

typedef struct _EFI_TABLE_HEADER{
    EFI_UINT64          Signature;
    EFI_UINT32          Revision;
    EFI_UINT32          HeaderSize;
    EFI_UINT32          Crc32;
    EFI_UINT32          Reserved;
}EFI_TABLE_HEADER, * PEFI_TABLE_HEADER;

#define EFI_MEMORY_TYPE_RESERVED                    0
#define EFI_MEMORY_TYPE_LOADER_CODE                 1
#define EFI_MEMORY_YUPE_LOADER_DATA                 2
#define EFI_MEMORY_TYPE_BOOT_SERVICES_CODE          3
#define EFI_MEMORY_TYPE_BOOT_SERVICES_DATA          4
#define EFI_MEMORY_TYPE_RUNTIME_SERVICE_CODE        5
#define EFI_MEMORY_TYPE_RUNTIME_SERVICE_DATA        6
#define EFI_MEMORY_TYPE_CONVENTIONAL_MEMORY         7
#define EFI_MEMORY_TYPE_UNUSABLE_MEMORY             8
#define EFI_MEMORY_TYPE_RECLAIMABLE_MEMORY          9
#define EFI_MEMORY_TYPE_ACPI_NVS                    10
#define EFI_MEMORY_TYPE_MAPPED_IO                   11
#define EFI_MEMORY_TYPE_MAPPED_IO_PORT_SPACE        12
#define EFI_MEMORY_TYPE_PAL_CODE                    13
#define EFI_MEMORY_TYPE_PERSISTENT_MEMORY           14
#define EFI_MEMORY_TYPE_UNACCEPTED_MEMORY           15
#define EFI_MEMORY_TYPE_MAX_MEMORY_TYPE             16

#define EFI_MEMORY_ATTRIBIT_UNCACHED                (1)
#define EFI_MEMORY_ATTRIBIT_WRITE_COALESCING        (1 << 1)
#define EFI_MEMORY_ATTRIBIT_WRITE_THROUGH           (1 << 2)
#define EFI_MEMORY_ATTRIBIT_WRITE_BACK              (1 << 3)
#define EFI_MEMORY_ATTRIBIT_UNCACHED_EXPORTED       (1 << 12)
#define EFI_MEMORY_ATTRIBIT_WRITE_PROTECTED         (1 << 13)
#define EFI_MEMORY_ATTRIBIT_READ_PROTECTED          (1 << 14)
#define EFI_MEMORY_ATTRIBIT_EXECUTE_PROTECTED       (1 << 15)
#define EFI_MEMORY_ATTRIBIT_NON_VOLATILE            (1 << 16)
#define EFI_MEMORY_ATTRIBIT_READ_ONLY               (1 << 17)
#define EFI_MEMORY_ATTRIBIT_SOFT_RESERVED           (1 << 18)
#define EFI_MEMORY_ATTRIBIT_ENCRYPTION_SUPPORTED    (1 << 19)
#define EFI_MEMORY_ATTRIBIT_HOT_PLUGGABLE           (1 << 20)
#define EFI_MEMORY_ATTRIBIT_RUNTIME_REQUREMENT      (1 << 63)

#define EFI_CURRENT_MEMORY_DESCRIPTOR_VERSION       1

#define EFI_PAGE_SHIFT                              (1 << 12)
#define EFI_PAGE_SIZE                               (1ULL << EFI_PAGE_SHIFT)
#define EFI_MAX_PAGES                               (UINT64_MAX >> EFI_PAGE_SHIFT)

typedef struct _EFI_MEMORY_DESCRIPTOR{
    EFI_UINT32      Type;
    EFI_UINT32      Padding;
    EFI_UINT64      PhysicalStart;
    EFI_UINT64      VirtualStart;
    EFI_UINT64      NumberOfPages;
    EFI_UINT64      Attribute;
}EFI_MEMORY_DESCRIPTOR, * PEFI_MEMORY_DESCRIPTOR;

typedef struct _EFI_CAPSULE_HEADER{
    EFI_GUID        Guid;
    EFI_UINT32      HeaderSize;
    EFI_UINT32      Flags;
    EFI_UINT32      ImageSize;
}EFI_CAPSULE_HEADER, * PEFI_CAPSULE_HEADER;

typedef struct PACKED _EFI_MANAGE_CAPSULE_HEADER{
    EFI_UINT32      Version;
    EFI_UINT16      EmbDrvCount;
    EFI_UINT16      PayloadCount;
    EFI_UINT64      OffsetList[];
}EFI_MANAGE_CAPSULE_HEADER, * PEFI_MANAGE_CAPSULE_HEADER;

typedef struct PACKED _EFI_MANAGE_CAPSULE_IMAGE_HEADER{
    EFI_UINT32      Version;
    EFI_GUID        ImageTypeId;
    EFI_UINT8       ImageIndex;
    EFI_UINT8       ReservedByte[3];
    EFI_UINT32      ImageSize;
    EFI_UINT32      VendorCodeSize;
    EFI_UINT64      HwIns;
    EFI_UINT64      CapsuleSupport;
}EFI_MANAGE_CAPSULE_IMAGE_HEADER, * PEFI_MANAGE_CAPSULE_IMAGE_HEADER;

typedef struct _WIN_CERTIFICATE{
    EFI_UINT32      Length;
    EFI_UINT16      Revision;
    EFI_UINT16      CertType;
}WIN_CERTIFICATE, * PWIN_CERTIFICATE;

typedef struct _WIN_CERTIFICATE_UEFI_GUID{
    WIN_CERTIFICATE Header;
    EFI_GUID        CertType;
    EFI_UINT8       CertificateData[];
}WIN_CERTIFICATE_UEFI_GUID, * PWIN_CERTIFICATE_UEFI_GUID;

typedef struct _EFI_IMAGE_AUTHENTIFICATION{
    EFI_UINT64                  Count;
    WIN_CERTIFICATE_UEFI_GUID   AuthInfo;
}EFI_IMAGE_AUTHENTIFICATION, * PEFI_IMAGE_AUTHENTIFICATION;

#define EFI_CAPSULE_FLAGS_PERSIST_ACROSS_RESET      0x00010000
#define EFI_CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE     0x00020000
#define EFI_CAPSULE_FLAGS_INITIATE_RESET            0x00040000

typedef struct _EFI_CAPSULE_INFORMATION{
    EFI_MANAGE_CAPSULE_IMAGE_HEADER     InformationHeader;
    PEFI_MANAGE_CAPSULE_IMAGE_HEADER    ChildCapsule;
    int                                 ResetType;
    long                                Index;
    size_t                              Count;
    size_t                              TotalSize;
    EFI_PHYSICAL_ADDRESS                PhysicalAddress;
    uintptr_t                           VirtualAddress;
    size_t                              BageBytesRemain;
}EFI_CAPSULE_INFORMATION, * PEFI_CAPSULE_INFORMATION;



int EfiCapsuleSetupInfo(
    PEFI_CAPSULE_INFORMATION    CapsuleInfo, 
    void*                       KernelBuffer,
    size_t                      HeaderBytes
);

int _EfiCapsuleSetupInfo(
    PEFI_CAPSULE_INFORMATION CapsuleInfo
);

#define EFI_TIME_SERVICE_TYPE_ADJUST_DAYLIGHT           0x01
#define EFI_TIME_SERVICE_TYPE_IN_DAYLIGHT               0x02
#define EFI_TIME_SERVICE_TYPE_UNSPECIFIED_TIMEZONE      0x07FF

typedef struct _EFI_TIME{
    EFI_UINT16      Year;
    EFI_UINT8       Month;
    EFI_UINT8       Day;
    EFI_UINT8       Hour;
    EFI_UINT8       Minute;
    EFI_UINT8       Second;
    EFI_UINT8       Padding1;
    EFI_UINT32      Nanosecond;
    EFI_INT16       TimeZone;
    EFI_UINT8       Daylight;
    EFI_UINT8       Padding2;
}EFI_TIME, * PEFI_TIME;

typedef struct _EFI_TIME_CAPABILITIES{
    EFI_UINT32      Resolution;
    EFI_UINT32      Accuracy;
    EFI_UINT8       SetsToZero;
}EFI_TIME_CAPABILITIES, * PEFI_TIME_CAPABILITIES;

#define EFI_RESET_SYSTEM_RESET_COLD     0
#define EFI_RESET_SYSTEM_RESET_WARM     1
#define EFI_RESET_SYSTEM_SHUTDOWN       2

#define EFI_RUNTIME_SERVICE_SIGNATURE   ((EFI_UINT64)0x5652453544E5552)
#define EFI_RUNTIME_SERVICE_REVISION    0x00010000

typedef struct _EFI_RUNTIME_SERVICE_32{
    EFI_TABLE_HEADER        Header;
    EFI_UINT32              GetTime;
    EFI_UINT32              SetTime;
    EFI_UINT32              GetWakeTime;
    EFI_UINT32              SetWakeTime;
    EFI_UINT32              SetVAddrMap;
    EFI_UINT32              ConvertPointer;
    EFI_UINT32              GetVariable;
    EFI_UINT32              GetNextVariable;
    EFI_UINT32              SetVariable;
    EFI_UINT32              GetNextHighMonoCount;
    EFI_UINT32              ResetSystem;
    EFI_UINT32              UpdateCapital;
    EFI_UINT32              QueryCapsuleCapabilities;
    EFI_UINT32              QueryVariableInfo;
}EFI_RUNTIME_SERVICE_32, * PEFI_RUNTIME_SERVICE_32;

typedef EFI_STATUS  (*FuncEfiGetTime)                  (PEFI_TIME Time, PEFI_TIME_CAPABILITIES TimeCap);
typedef EFI_STATUS  (*FuncEfiSetTime)                  (PEFI_TIME Time);
typedef EFI_STATUS  (*FuncEfiGetWakeTime)              (EFI_BOOL* Enabled, EFI_BOOL* Pending, PEFI_TIME Time);
typedef EFI_STATUS  (*FuncEfiSetWakeTime)              (EFI_BOOL  Enabled, PEFI_TIME Time);
typedef EFI_STATUS  (*FuncEfiGetVariable)              (EFI_UINT16* NameString, PEFI_GUID Vendor, EFI_UINT32* Attribute, ULONG* DataSize, PVOID Data);
typedef EFI_STATUS  (*FuncEfiGetNextVariable)          (ULONG* NameSize, EFI_UINT16* NameString, PEFI_GUID Vendor);
typedef EFI_STATUS  (*FuncEfiSetVariable)              (EFI_UINT16* NameString, PEFI_GUID Vendor, EFI_UINT32 Attribute, ULONG DataSize, PVOID Data);
typedef EFI_STATUS  (*FuncEfiGetNextHighMonoCount)     (EFI_UINT32* Count);
typedef void        (*FuncEfiResetSystem)              (INTEGER ResetType, EFI_STATUS Status, ULONG DataSize, EFI_UINT16* Data);
typedef EFI_STATUS  (*FuncEfiSetVirtualAddressMap)     (ULONG MapSize, ULONG DescriptorSize, EFI_UINT32 DescriptorVersion, PEFI_MEMORY_DESCRIPTOR VirtualMap);
typedef EFI_STATUS  (*FuncEfiQueryVariableInfo)        (EFI_UINT32 Attribute, EFI_UINT64* StorageSpace, EFI_UINT64* RemainingSpace, EFI_UINT64* MaxVariableSize);
typedef EFI_STATUS  (*FuncEfiUpdateCapsule)            (PEFI_CAPSULE_HEADER* Capsules, ULONG Count, ULONG ScatterGatherList);
typedef EFI_STATUS  (*FuncEfiQueryCapsuleCaps)         (PEFI_CAPSULE_HEADER* Capsules, ULONG Count, EFI_UINT64* MaxSize, INTEGER* ResetType);
typedef EFI_STATUS  (*FuncEfiQueryVariableStore)       (EFI_UINT32 Attributes, ULONG Size, bool NonBlocking);

typedef union{
    struct{
        EFI_TABLE_HEADER                EfiHeader;
        FuncEfiGetTime                  EfiGetTime;
        FuncEfiSetTime                  EfiSetTime;
        FuncEfiGetWakeTime              EfiGetWakeTime;
        FuncEfiSetWakeTime              EfiSetWakeTime;
        FuncEfiSetVirtualAddressMap     EfiSetVirtualAddressMap;
        void*                           ConvertPointer;
        FuncEfiGetVariable              EfiGetVariable;
        FuncEfiGetNextVariable          EfiGetNextVariable;
        FuncEfiSetVariable              EfiSetVariable;
        FuncEfiGetNextHighMonoCount     EfiGetNextHighMonoCount;
        FuncEfiResetSystem              EfiResetSystem;
        FuncEfiUpdateCapsule            EfiUpdateCapsule;
        FuncEfiQueryCapsuleCaps         EfiQueryCapsuleCaps;
        FuncEfiQueryVariableInfo        EfiQueryVariableInfo;
    };
    EFI_RUNTIME_SERVICE_32              MixedMode;
}EFI_RUNTIME_SERVICE, * PEFI_RUNTIME_SERVICE;

#define NULL_GUID				                        DEFINE_EFI_GUID(0x00000000, 0x0000, 0x0000,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
#define MPS_TABLE_GUID				                    DEFINE_EFI_GUID(0xEB9D2D2F, 0x2D88, 0x11D3,  0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D)
#define ACPI_TABLE_GUID				                    DEFINE_EFI_GUID(0xEB9D2D30, 0x2D88, 0x11D3,  0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D)
#define ACPI_20_TABLE_GUID			                    DEFINE_EFI_GUID(0x8868E871, 0xE4F1, 0x11D3,  0xBC, 0x22, 0x00, 0x80, 0xC7, 0x3C, 0x88, 0x81)
#define SMBIOS_TABLE_GUID			                    DEFINE_EFI_GUID(0xEB9D2D31, 0x2D88, 0x11D3,  0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D)
#define SMBIOS3_TABLE_GUID			                    DEFINE_EFI_GUID(0xF2FD1544, 0x9794, 0x4A2C,  0x99, 0x2E, 0xE5, 0xBB, 0xCF, 0x20, 0xE3, 0x94)
#define SAL_SYSTEM_TABLE_GUID			                DEFINE_EFI_GUID(0xEB9D2D32, 0x2D88, 0x11D3,  0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D)
#define HCDP_TABLE_GUID				                    DEFINE_EFI_GUID(0xF951938D, 0x620B, 0x42EF,  0x82, 0x79, 0xA8, 0x4B, 0x79, 0x61, 0x78, 0x98)
#define UGA_IO_PROTOCOL_GUID			                DEFINE_EFI_GUID(0x61A4D49E, 0x6F68, 0x4F1B,  0xB9, 0x22, 0xA8, 0x6E, 0xED, 0x0B, 0x07, 0xA2)
#define EFI_GLOBAL_VARIABLE_GUID		                DEFINE_EFI_GUID(0x8BE4DF61, 0x93CA, 0x11D2,  0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C)
#define UV_SYSTEM_TABLE_GUID			                DEFINE_EFI_GUID(0x3B13A7D4, 0x633E, 0x11DD,  0x93, 0xEC, 0xDA, 0x25, 0x56, 0xD8, 0x95, 0x93)
#define LOADED_IMAGE_PROTOCOL_GUID		                DEFINE_EFI_GUID(0x5B1B31A1, 0x9562, 0x11D2,  0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)
#define LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID	        DEFINE_EFI_GUID(0xBC62157E, 0x3E33, 0x4FEC,  0x99, 0x20, 0x2D, 0x3B, 0x36, 0xD7, 0x50, 0xDF)
#define EFI_DEVICE_PATH_PROTOCOL_GUID		            DEFINE_EFI_GUID(0x09576E91, 0x6D3F, 0x11D2,  0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)
#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID	        DEFINE_EFI_GUID(0x8B843E20, 0x8132, 0x4852,  0x90, 0xCC, 0x55, 0x1A, 0x4E, 0x4A, 0x7F, 0x1C)
#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID	        DEFINE_EFI_GUID(0x05C99A21, 0xC70F, 0x4AD2,  0x8A, 0x5F, 0x35, 0xDF, 0x33, 0x43, 0xF5, 0x1E)
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID	            DEFINE_EFI_GUID(0x9042A9DE, 0x23DC, 0x4A38,  0x96, 0xFB, 0x7A, 0xDE, 0xD0, 0x80, 0x51, 0x6A)
#define EFI_UGA_PROTOCOL_GUID			                DEFINE_EFI_GUID(0x982C298B, 0xF4FA, 0x41CB,  0xB8, 0x38, 0x77, 0xAA, 0x68, 0x8F, 0xB8, 0x39)
#define EFI_PCI_IO_PROTOCOL_GUID		                DEFINE_EFI_GUID(0x4CF5B200, 0x68B8, 0x4CA5,  0x9E, 0xEC, 0xB2, 0x3E, 0x3F, 0x50, 0x02, 0x9A)
#define EFI_FILE_INFO_ID			                    DEFINE_EFI_GUID(0x09576E92, 0x6D3F, 0x11D2,  0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)
#define EFI_SYSTEM_RESOURCE_TABLE_GUID		            DEFINE_EFI_GUID(0xB122A263, 0x3661, 0x4F68,  0x99, 0x29, 0x78, 0xF8, 0xB0, 0xD6, 0x21, 0x80)
#define EFI_FILE_SYSTEM_GUID			                DEFINE_EFI_GUID(0x964E5B22, 0x6459, 0x11D2,  0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)
#define DEVICE_TREE_GUID			                    DEFINE_EFI_GUID(0xB1B621D5, 0xF19C, 0x41A5,  0x83, 0x0B, 0xD9, 0x15, 0x2C, 0x69, 0xAA, 0xE0)
#define EFI_PROPERTIES_TABLE_GUID		                DEFINE_EFI_GUID(0x880AACA3, 0x4ADC, 0x4A04,  0x90, 0x79, 0xB7, 0x47, 0x34, 0x08, 0x25, 0xE5)
#define EFI_RNG_PROTOCOL_GUID			                DEFINE_EFI_GUID(0x3152BCA5, 0xEADE, 0x433D,  0x86, 0x2E, 0xC0, 0x1C, 0xDC, 0x29, 0x1F, 0x44)
#define EFI_RNG_ALGORITHM_RAW			                DEFINE_EFI_GUID(0xE43176D7, 0xB6E8, 0x4827,  0xB7, 0x84, 0x7F, 0xFD, 0xC4, 0xB6, 0x85, 0x61)
#define EFI_MEMORY_ATTRIBUTES_TABLE_GUID	            DEFINE_EFI_GUID(0xDCFA911D, 0x26EB, 0x469F,  0xA2, 0x20, 0x38, 0xB7, 0xDC, 0x46, 0x12, 0x20)
#define EFI_CONSOLE_OUT_DEVICE_GUID		                DEFINE_EFI_GUID(0xD3B36F2C, 0xD551, 0x11D4,  0x9A, 0x46, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D)
#define APPLE_PROPERTIES_PROTOCOL_GUID		            DEFINE_EFI_GUID(0x91BD12FE, 0xF6C3, 0x44FB,  0xA5, 0xB7, 0x51, 0x22, 0xAB, 0x30, 0x3A, 0xE0)
#define EFI_TCG2_PROTOCOL_GUID			                DEFINE_EFI_GUID(0x607F766C, 0x7455, 0x42BE,  0x93, 0x0B, 0xE4, 0xD7, 0x6D, 0xB2, 0x72, 0x0F)
#define EFI_LOAD_FILE_PROTOCOL_GUID		                DEFINE_EFI_GUID(0x56EC3091, 0x954C, 0x11D2,  0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B)
#define EFI_LOAD_FILE2_PROTOCOL_GUID		            DEFINE_EFI_GUID(0x4006C0C1, 0xFCB3, 0x403E,  0x99, 0x6D, 0x4A, 0x6C, 0x87, 0x24, 0xE0, 0x6D)
#define EFI_RT_PROPERTIES_TABLE_GUID		            DEFINE_EFI_GUID(0xEB66918A, 0x7EEF, 0x402A,  0x84, 0x2E, 0x93, 0x1D, 0x21, 0xC3, 0x8A, 0xE9)
#define EFI_DXE_SERVICES_TABLE_GUID		                DEFINE_EFI_GUID(0x05AD34BA, 0x6F02, 0x4214,  0x95, 0x2E, 0x4D, 0xA0, 0x39, 0x8E, 0x2B, 0xB9)
#define EFI_SMBIOS_PROTOCOL_GUID		                DEFINE_EFI_GUID(0x03583FF6, 0xCB36, 0x4940,  0x94, 0x7E, 0xB9, 0xB3, 0x9F, 0x4A, 0xFA, 0xF7)
#define EFI_MEMORY_ATTRIBUTE_PROTOCOL_GUID	            DEFINE_EFI_GUID(0xF4560CF6, 0x40EC, 0x4B4A,  0xA1, 0x92, 0xBF, 0x1D, 0x57, 0xD0, 0xB1, 0x89)
#define EFI_IMAGE_SECURITY_DATABASE_GUID	            DEFINE_EFI_GUID(0xD719B2CB, 0x3D3A, 0x4596,  0xA3, 0xBC, 0xDA, 0xD0, 0x0E, 0x67, 0x65, 0x6F)
#define EFI_SHIM_LOCK_GUID			                    DEFINE_EFI_GUID(0x605DAB50, 0xE046, 0x4300,  0xAB, 0xB6, 0x3D, 0xD8, 0x10, 0xDD, 0x8B, 0x23)
#define EFI_CERT_SHA256_GUID			                DEFINE_EFI_GUID(0xC1C41626, 0x504C, 0x4092, 0xAC, 0xA9, 0x41, 0xF9, 0x36, 0x93, 0x43, 0x28)
#define EFI_CERT_X509_GUID			                    DEFINE_EFI_GUID(0xA5C059A1, 0x94E4, 0x4AA7, 0x87, 0xB5, 0xAB, 0x15, 0x5C, 0x2B, 0xF0, 0x72)
#define EFI_CERT_X509_SHA256_GUID		                DEFINE_EFI_GUID(0x3BD2A492, 0x96C0, 0x4079, 0xB4, 0x20, 0xFC, 0xF9, 0x8E, 0xF1, 0x03, 0xED)
#define EFI_CC_BLOB_GUID			                    DEFINE_EFI_GUID(0x067B1F5F, 0xCF26, 0x44C5, 0x85, 0x54, 0x93, 0xD7, 0x77, 0x91, 0x2D, 0x42)
#define DELLEMC_EFI_RCI2_TABLE_GUID		                DEFINE_EFI_GUID(0x2D9F28A2, 0xA886, 0x456A,  0x97, 0xA8, 0xF1, 0x1E, 0xF2, 0x4F, 0xF4, 0x55)
#define AMD_SEV_MEM_ENCRYPT_GUID		                DEFINE_EFI_GUID(0x0CF29B71, 0x9E51, 0x433A,  0xA3, 0xB7, 0x81, 0xF3, 0xAB, 0x16, 0xB8, 0x75)
#define OVMF_SEV_MEMORY_ACCEPTANCE_PROTOCOL_GUID	    DEFINE_EFI_GUID(0xC5A010FE, 0x38A7, 0x4531,  0x8A, 0x4A, 0x05, 0x00, 0xD2, 0xFD, 0x16, 0x49)

typedef struct _EFI_CONFIG_TABLE_64{
    EFI_GUID        EfiGuid;
    EFI_UINT64      Table;
}EFI_CONFIG_TABLE_64, * PEFI_CONFIG_TABLE_64;

typedef struct _EFI_CONFIG_TABLE_32{
    EFI_GUID        EfiGuid;
    EFI_UINT32      Table;
}EFI_CONFIG_TABLE_32, * PEFI_CONFIG_TABLE_32;

typedef union _EFI_CONFIG_TABLE{
    struct{
        EFI_GUID        EfiGuid;
        void*           Table;
    };
    EFI_CONFIG_TABLE_32 MixedMode;
}EFI_CONFIG_TABLE, * PEFI_CONFIG_TABLE;

#define EFI_SYSTEM_TABLE_SIGNATURE          ((EFI_UINT64)0x5453595320494249ULL)
#define EFI_DXE_SERVICES_TABLE_SIGNATURE    ((EFI_UINT64)0x565245535F455844ULL)

#define EFI_2_30_SYSTEM_TABLE_REVISION      ((2 << 16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION      ((2 << 16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION      ((2 << 16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION      ((2 << 16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION      ((1 << 16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION      ((1 << 16) | (02))

typedef struct _EFI_SYSTEM_TABLE_64{
    EFI_TABLE_HEADER    Header;
    EFI_UINT64          FwVendor;	
	EFI_UINT32          FwRevision;
	EFI_UINT32          Padding1;
	EFI_UINT64          ConInHandle;
	EFI_UINT64          ConIn;
	EFI_UINT64          ConOutHandle;
	EFI_UINT64          ConOut;
	EFI_UINT64          StdeErrHandle;
	EFI_UINT64          StdErr;
	EFI_UINT64          RunTime;
	EFI_UINT64          BootTime;
	EFI_UINT32          NrTables;
	EFI_UINT32          Padding2;
	EFI_UINT64          Tables;
}EFI_SYSTEM_TABLE_64, * PEFI_SYSTEM_TABLE_64;

typedef struct _EFI_SYSTEM_TABLE_32{
    EFI_TABLE_HEADER    Header;
    EFI_UINT32          FwVendor;
    EFI_UINT32          FwRevision;
    EFI_UINT32          ConInHandle;
    EFI_UINT32          ConIn;
    EFI_UINT32          ConOutHandle;
    EFI_UINT32          CouOut;
    EFI_UINT32          StdErrHandle;
    EFI_UINT32          StdErr;
    EFI_UINT32          RunTime;
    EFI_UINT32          BootTime;
    EFI_UINT32          NrTables;
    EFI_UINT32          Tables;
}EFI_SYSTEM_TABLE_32, * PEFI_SYSTEM_TABLE_32;

typedef union _EFI_SYSTEM_TABLE{
    struct{
        EFI_TABLE_HEADER        TableHeader;
        EFI_UINT64              FirmwareVendor;
        EFI_UINT32              FirmwareRevision;
        EFI_UINT64              ConInHandle;
        void*                   ConIn;
        EFI_UINT64              ConOutHandle;
        void*                   ConOut;
        EFI_UINT64              StdErrorHandle;
        EFI_UINT64              StdError;
        EFI_RUNTIME_SERVICE*    RuntimeService;
        void*                   BootService;
        EFI_UINT64              TableCount;
        EFI_UINT64              Tables;
    };
    EFI_SYSTEM_TABLE_32         MixedMode;
}EFI_SYSTEM_TABLE, * PEFI_SYSTEM_TABLE;

typedef struct _EFI_BOOT_MEMORY_MAP{
    EFI_UINT64              MapSize;
    EFI_UINT64              DescriptorSize;
    EFI_UINT32              DescriptorVersion;
    EFI_UINT64              MapKey;
    EFI_UINT64              BufferSize;
    EFI_MEMORY_DESCRIPTOR   Mappings[];
}EFI_BOOT_MEMORY_MAP, * PEFI_BOOT_MEMORY_MAP;

typedef struct _EFI_UNACEPTED_MEMORY{
    EFI_UINT32  Version;              
    EFI_UINT32  UnitSize;    
    EFI_UINT64  PhysicalBase;
    EFI_UINT64  Size;
    EFI_UINT64  Bmp[];
}EFI_UNACEPTED_MEMORY, * PEFI_UNACEPTED_MEMORY;

typedef struct _EFI_MEMORY_MAP_DATA{
    EFI_PHYSICAL_ADDRESS    PhysicalMap;
    EFI_UINT64              Size;
    EFI_UINT64              DescriptorVersion;
    EFI_UINT64              DescriptorSize;
    EFI_UINT64              Flags;
}EFI_MEMORY_MAP_DATA, * PEFI_MEMORY_MAP_DATA;

#define EFI_MEMORY_MAP_LATE     (1)
#define EFI_MEMORY_MAP_BLOCK    (1 << 1)
#define EFI_MEMORY_MAP_SLAB     (1 << 2)

typedef struct _EFI_MEMORY_MAP{
    EFI_PHYSICAL_ADDRESS    PhysicalMap;
    void*                   Map;
    void*                   MapEnd;
    int                     MapCount;
    EFI_UINT64              DescriptorVersion;
    EFI_UINT64              DescriptorSize;
    EFI_UINT64              Flags;
}EFI_MEMORY_MAP, * PEFI_MEMORY_MAP;

typedef struct _EFI_MEMORY_RANGE{
    RANGE           Range;
    EFI_UINT64      Attribute;
}EFI_MEMORY_RANGE, * PEFI_MEMORY_RANGE;

typedef struct _EFI_RT_PROPERTIES_TABLE{
    EFI_UINT16      Version;
    EFI_UINT16      Length;
    EFI_UINT32      RuntimeServiceSupported;
}EFI_RT_PROPERTIES_TABLE, * PEFI_RT_PROPERTIES_TABLE;

#define EFI_RT_PROPERTIES_TABLE_VERSION                             1
#define EFI_INVALID_TABLE_ADDRESS                                   (UINT64_MAX)
#define EFI_MEMORY_ATTRIBUTES_FLAGS_RT_FORWARD_CONTROL_FLOW_GUARD	1

typedef struct _EFI_ATTRIBUTE_TABLE{
    EFI_UINT32              Version;
    EFI_UINT32              EntryCount;
    EFI_UINT32              DescriptorSize;
    EFI_UINT32              Flags;
    EFI_MEMORY_DESCRIPTOR   Entry;
}EFI_ATTRIBUTE_TABLE, * PEFI_ATTRIBUTE_TABLE;

typedef struct _EFI_SIGNATURE_DATA{
    EFI_GUID                SignatureOwner;
    EFI_UINT8               SignatureData[];
}EFI_SIGNATURE_DATA, * PEFI_SIGNATURE_DATA;

typedef struct _EFI_SIGNATURE_LIST{
    EFI_GUID                SignatureType;
    EFI_UINT32              SignatureListSize;
    EFI_UINT32              SignatureHeaderSize;
    EFI_UINT32              SignatureSize;
    EFI_UINT8               SignatureHeader[];
}EFI_SIGNATURE_LIST, * PEFI_SIGNATURE_LIST;

typedef EFI_UINT8   EFI_SHA256_HASH[32];

typedef struct _EFI_X509_SHA256_CERTIFICATE{
    EFI_SHA256_HASH         TbSignedHash;
    EFI_TIME                TimeToRevocation;
}EFI_X509_SHA256_CERTIFICATE, * PEFI_X509_SHA256_CERTIFICATE;

typedef struct _LOUSINE_EFI_CORE_STRUCTURE{
    PEFI_RUNTIME_SERVICE    Runtime;
    EFI_UINT32              RuntimeVersion;
    EFI_UINT32              RuntimeSupportedMask;
    EFI_UINT64              Acpi;
    EFI_UINT64              Acpi2;
    EFI_UINT64              SmBios;
    EFI_UINT64              SmBios3;
    EFI_UINT64              Esrt;
    EFI_UINT64              TpmLog;
    EFI_UINT64              TpmFinalLog;
    EFI_UINT64              MokvarTable;
    EFI_UINT64              CocoSecret;
    EFI_UINT64              Unaccepted;
}LOUSINE_EFI_CORE_STRUCTURE, * PLOUSINE_EFI_CORE_STRUCTURE;

#ifndef _EFI_CORE_C
extern LOUSINE_EFI_CORE_STRUCTURE Efi;
#endif

#ifdef __cplusplus
}
#endif
#endif