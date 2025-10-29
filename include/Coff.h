#ifndef _COFF_H
#define _COFF_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif

#define COFF_PE_SIGNATURE "PE\0\0"

#define CoffGetImageHeader(x) ((PCOFF_IMAGE_HEADER)((UINT8*)(x) + *(UINT32*)((UINT8*)(x) + 0x3C)))

typedef struct _COFF_IMAGE_STANDARD_HEADER{
    UINT32      PeSignature; //PE00;
    UINT16      MachineType;
    UINT16      NumberOfSections;
    UINT32      TimeDateStamp;
    UINT32      PointerToSymbolTable;
    UINT32      NumberOfSymbols;
    UINT16      SizeOfOptionalHeader;
    UINT16      Charecteristics;
}COFF_IMAGE_STANDARD_HEADER, * PCOFF_IMAGE_STANDARD_HEADER;

#define CFI_MACHINE_TYPE_UNKOWN         0x0000
#define CFI_MACHINE_TYPE_AM33           0x01D3
#define CFI_MACHINE_TYPE_AMD64          0x8664
#define CFI_MACHINE_TYPE_ARM            0x01C0
#define CFI_MACHINE_TYPE_ARM64          0xAA64
#define CFI_MACHINE_TYPE_ARMNT          0x01C4
#define CFI_MACHINE_TYPE_EBC            0x0EBC
#define CFI_MACHINE_TYPE_I386           0x014C
#define CFI_MACHINE_TYPE_IA64           0x0200
#define CFI_MACHINE_TYPE_M32R           0x9041
#define CFI_MACHINE_TYPE_MIPS16         0x0266
#define CFI_MACHINE_TYPE_MIPSFPU        0x0366
#define CFI_MACHINE_TYPE_MIPSFPU16      0x0466
#define CFI_MACHINE_TYPE_POWERPC        0x01F0
#define CFI_MACHINE_TYPE_POWERPCFPU     0x01F1
#define CFI_MACHINE_TYPE_R4000          0x0166
#define CFI_MACHINE_TYPE_RISCV32        0x5032
#define CFI_MACHINE_TYPE_RISCV64        0x5064
#define CFI_MACHINE_TYPE_RISCV128       0x5128
#define CFI_MACHINE_TYPE_SH3            0x01A2
#define CFI_MACHINE_TYPE_SH3DSP         0x01D3
#define CFI_MACHINE_TYPE_SH4            0x01D6
#define CFI_MACHINE_TYPE_SH5            0x01D8
#define CFI_MACHINE_TYPE_THUMB          0x01C2
#define CFI_MACHINE_TYPE_WCEMIPSV2      0x0169

#define CFI_CHARACTERISTICS_RELOCS_STRIPPED             (0x0001)
#define CFI_CHARACTERISTICS_EXECUTABLE_IMAGE            (0x0002)
#define CFI_CHARACTERISTICS_LINE_NUMS_STRIPED           (0x0004)
#define CFI_CHARACTERISTICS_SYMS_STRIPPED               (0x0008)
#define CFI_CHARACTERISTICS_AGGRESSIVE_WS_TRIM          (0x0010)
#define CFI_CHARARTERISTICS_LARGE_ADDRESS_AWARE         (0x0020)
//(0x0040) is reserved
#define CFI_CHARACTERISTICS_FILE_BYTES_RESERVED_LO      (0x0080)
#define CFI_CHARACTERISTICS_32BIT_MACHINE               (0x0100)
#define CFI_CHARACTERISTICS_DEBUG_STRIPPED              (0x0200)
#define CFI_CHARACTERISTICS_REMOVABLE_RUN_FROM_SWAP     (0x0400)
#define CFI_CHARACTERISTICS_NET_RUN_FROM_SWAP           (0x0800)
#define CFI_CHARACTERISTICS_SYSTEM                      (0x1000)
#define CFI_CHARACTERISTICS_DLL                         (0x2000)
#define CFI_CHARACTERISTICS_UP_SYSTEM_ONLY              (0x4000)
#define CFI_CHARACTERISTICS_FILE_BYTES_RESERVED_HI      (0x8000)

#define CFI_OPTIONAL_HEADER_PE32_MAGIC      0x010B
#define CFI_OPTIONAL_HEADER_PE3264_MAGIC    0x020B

#define CFI_SUBSYSTEM_UNKOWN                            0
#define CFI_SUBSYSTEM_NATIVE                            1
#define CFI_SUBSYSTEM_WINDOWS_GUI                       2
#define CFI_SUBSYSTEM_WINDOWS_CUI                       3
#define CFI_SUBSYSTEM_OS2_CUI                           5
#define CFI_SUBSYSTEM_POSIX_CUI                         7
#define CFI_SUBSYSTEM_NATIVE_WINDOWS                    8
#define CFI_SUBSYSTEM_WINDOWS_CE_GUI                    9
#define CFI_SUBSYSTEM_EFI_APPLICATION                   10
#define CFI_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER           11
#define CFI_SUBSYSTEM_EFI_RUNTIME_DRIVER                12
#define CFI_SUBSYSTEM_EFI_ROM                           13
#define CFI_SUBSYSTEM_XBOX                              14
#define CFI_SUBSYSTEM_WINDOWS_BOOT_APPLICATION          16

//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0001) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0002) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0004) 
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0008)
//      CFI_DLLCHARACTERISTICS_RESERVED                 (0x0010)
#define CFI_DLLCHARACTERISTICS_HIGH_ENTROPY_VA          (0x0020)
#define CFI_DLLCHARACTERISTICS_DYNAMIC_BASE             (0x0040)
#define CFI_DLLCHARACTERISTICS_FORCE_INTEGRITY          (0x0080)
#define CFI_DLLCHARACTERISTICS_NX_COMPATIBLE            (0x0100)
#define CFI_DLLCHARACTERISTICS_NO_ISOLATION             (0x0200)
#define CFI_DLLCHARACTERISTICS_NO_SEH                   (0x0400)
#define CFI_DLLCHARACTERISTICS_NO_BIND                  (0x0800)
#define CFI_DLLCHARACTERISTICS_APPCONTAINER             (0x1000)
#define CFI_DLLCHARACTERISTICS_WDM_DRIVER               (0x2000)
#define CFI_DLLCHARACTERISTICS_GUARD_CF                 (0x4000)
#define CFI_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE    (0x8000)

typedef struct _COFF_IMAGE_DATA_DIRECTORY{
    UINT32      VirtualAddress;
    UINT32      Size;
}COFF_IMAGE_DATA_DIRECTORY, * PCOFF_IMAGE_DATA_DIRECTORY;

#define CFI_DDOFFSET_EXPORT_TABLE                       0
#define CFI_DDOFFSET_IMPORT_TABLE                       1
#define CFI_DDOFFSET_RESOURCE_TABLE                     2
#define CFI_DDOFFSET_EXCEPTION_TABLE                    3
#define CFI_DDOFFSET_CERTIFICATE_TABLE                  4
#define CFI_DDOFFSET_BASE_RELOCATION_TABLE              5
#define CFI_DDOFFSET_DEBUG_TABLE                        6
#define CFI_DDOFFSET_ARCHITECTURE_TABLE                 7
#define CFI_DDOFFSET_GLOBAL_PTR_TABLE                   8
#define CFI_DDOFFSET_TLS_TABLE                          9
#define CFI_DDOFFSET_LOAD_CONFIG_TABLE                  10
#define CFI_DDOFFSET_BOUND_IMPORT                       11
#define CFI_DDOFFSET_IAT_TABLE                          12
#define CFI_DDOFFSET_DELAY_IMPORT_DESCRIPTOR_TABLE      13
#define CFI_DDOFFSET_CLR_RUNTIME_HEADER                 14
#define CFI_DDOFFSET_KULA_TABLE                         15 //LOUCOFF
#define CFI_TOTAL_DATA_DIRECTORY_OFFSETS                16

typedef struct _SECTION_TABLE{
    CHAR        Name[8];
    UINT32      VirtualSize;
    UINT32      VirtualAddress;
    UINT32      SizeOfRawData;
    UINT32      PointerToRawData;
    UINT32      PointerToRelocations;
    UINT32      PointerToLineNumbers;
    UINT16      NumberOfRelocations;
    UINT16      NumberOfLineNumbers;
    UINT32      Characteristics; //CFI_SCN
}SECTION_TABLE, * PSECTION_TABLE; 

//      CFI_SCN_RESERVED                    0x00000000
//      CFI_SCN_RESERVED                    0x00000001
//      CFI_SCN_RESERVED                    0x00000004
#define CFI_SCN_TYPE_NO_PAD                 0x00000008
//      CFI_SCN_RESERVED                    0x00000010
#define CFI_SCN_CNT_CODE                    0x00000020
#define CFI_SCN_CNT_INITIALIZED_DATA        0x00000040
#define CFI_SCN_CNT_UNINITIALIZED_DATA      0x00000080
#define CFI_SCN_LNK_OTHER                   0x00000100
#define CFI_SCN_LNK_INFO                    0x00000200
//      CFI_SCN_RESERVED                    0x00000400
#define CFI_SCN_LNK_REMOVE                  0x00000800
#define CFI_SCN_LNK_COMDAT                  0x00001000
//      CFI_SCN_RESERVED                    0x00002000
//      CFI_SCN_RESERVED                    0x00004000
#define CFI_SCN_GPREL                       0x00008000
#define CFI_SCN_MEM_PURGEABLE               0x00020000
#define CFI_SCN_MEM16_BIT                   0x00020000
#define CFI_SCN_MEM_LOCKED                  0x00040000
#define CFI_SCN_MEM_PRELOAD                 0x00080000
#define CFI_SCN_ALIGN_1BYTES                0x00100000
#define CFI_SCN_ALIGN_2BYTES                0x00200000
#define CFI_SCN_ALIGN_4BYTES                0x00300000
#define CFI_SCN_ALIGN_8BYTES                0x00400000
#define CFI_SCN_ALIGN_16BYTES               0x00500000
#define CFI_SCN_ALIGN_32BYTES               0x00600000
#define CFI_SCN_ALIGN_64BYTES               0x00700000
#define CFI_SCN_ALIGN_128BYTES              0x00800000
#define CFI_SCN_ALIGN_256BYTES              0x00900000
#define CFI_SCN_ALIGN_512BYTES              0x00A00000
#define CFI_SCN_ALIGN_1024BYTES             0x00B00000
#define CFI_SCN_ALIGN_2048BYTES             0x00C00000
#define CFI_SCN_ALIGN_4096BYTES             0x00D00000
#define CFI_SCN_ALIGN_8192BYTES             0x00E00000
#define CFI_SCN_LNK_NRELOC_OVFL             0x01000000
#define CFI_SCN_MEM_DISCARDABLE             0x02000000
#define CFI_SCN_MEM_NOT_CACHED              0x04000000
#define CFI_SCN_MEM_NOT_PAGED               0x08000000
#define CFI_SCN_MEM_SHARED                  0x10000000
#define CFI_SCN_MEM_EXECUTE                 0x20000000
#define CFI_SCN_MEM_READ                    0x40000000
#define CFI_SCN_MEM_WRITE                   0x80000000

typedef struct _COFF_IMAGE_OPTIONAL_HEADER32{
    UINT16                          Magic;
    UINT8                           LinkerMajorVersion;
    UINT8                           LinkerMinorVersion;
    UINT32                          SizeOfCode;
    UINT32                          SizeOfInitializedData;
    UINT32                          SizeOfUnInitializedData;
    UINT32                          AddressOfEntryPoint;
    UINT32                          BaseOfCode;
    UINT32                          BaseOfData;//this is not here in PE32+ AKA PE64
    UINT32                          ImageBase;
    UINT32                          SectionAlignment;
    UINT32                          FileAlignment;
    UINT16                          MajorOperatingSystemVersion;
    UINT16                          MinorOperatingSystemVersion;
    UINT16                          MajorImageVersion;
    UINT16                          MinorImageVersion;
    UINT16                          MajorSubsystemVersion;
    UINT16                          MinorSubsystemVersion;
    UINT32                          Win32VersionValue;
    UINT32                          SizeOfImage;
    UINT32                          SizeOfHeaders;
    UINT32                          Checksum;
    UINT16                          Subsystem;
    UINT16                          DllCharacteristics;
    UINT32                          SizeOfStackReserve;
    UINT32                          SizeOfStackCommit;
    UINT32                          SizeOfHeapReserve;
    UINT32                          SizeOfHeapCommit;
    UINT32                          LoaderFlags;
    UINT32                          NumberOfRvaAndSizes;
    COFF_IMAGE_DATA_DIRECTORY       DataDirectories[CFI_TOTAL_DATA_DIRECTORY_OFFSETS];
    SECTION_TABLE                   SectionTables[];
}COFF_IMAGE_OPTIONAL_HEADER32, * PCOFF_IMAGE_OPTIONAL_HEADER32;

typedef struct _COFF_IMAGE_OPTIONAL_HEADER64{
    UINT16                          Magic;
    UINT8                           LinkerMajorVersion;
    UINT8                           LinkerMinorVersion;
    UINT32                          SizeOfCode;
    UINT32                          SizeOfInitializedData;
    UINT32                          SizeOfUnInitializedData;
    UINT32                          AddressOfEntryPoint;
    UINT32                          BaseOfCode;
    UINT64                          ImageBase;
    UINT32                          SectionAlignment;
    UINT32                          FileAlignment;
    UINT16                          MajorOperatingSystemVersion;
    UINT16                          MinorOperatingSystemVersion;
    UINT16                          MajorImageVersion;
    UINT16                          MinorImageVersion;
    UINT16                          MajorSubsystemVersion;
    UINT16                          MinorSubsystemVersion;
    UINT32                          Win32VersionValue;
    UINT32                          SizeOfImage;
    UINT32                          SizeOfHeaders;
    UINT32                          Checksum;
    UINT16                          Subsystem;
    UINT16                          DllCharacteristics;
    UINT64                          SizeOfStackReserve;
    UINT64                          SizeOfStackCommit;
    UINT64                          SizeOfHeapReserve;
    UINT64                          SizeOfHeapCommit;
    UINT32                          LoaderFlags;
    UINT32                          NumberOfRvaAndSizes;
    COFF_IMAGE_DATA_DIRECTORY       DataDirectories[CFI_TOTAL_DATA_DIRECTORY_OFFSETS];
    SECTION_TABLE                   SectionTables[];
}COFF_IMAGE_OPTIONAL_HEADER64, * PCOFF_IMAGE_OPTIONAL_HEADER64;
    
typedef union _COFF_IMAGE_OPTIONAL_HEADER{
    COFF_IMAGE_OPTIONAL_HEADER32 PE32;
    COFF_IMAGE_OPTIONAL_HEADER64 PE64;
}COFF_IMAGE_OPTIONAL_HEADER, * PCOFF_IMAGE_OPTIONAL_HEADER;

typedef struct _COFF_IMAGE_HEADER{
    COFF_IMAGE_STANDARD_HEADER  StandardHeader;
    COFF_IMAGE_OPTIONAL_HEADER  OptionalHeader;
}COFF_IMAGE_HEADER, * PCOFF_IMAGE_HEADER;

typedef struct _CFI_OBJECT{
    FILE*                   CoffFile;
    BOOL                    AOA64;
    BOOL                    KernelObject;
    PCOFF_IMAGE_HEADER      ImageHeader;
    PVOID                   LoadedAddress;                                                                                                                                                
    PVOID                   PhysicalLoadedAddress;
    PVOID                   ExecututionLoading;
    UINT64                  KCopy;
}CFI_OBJECT, * PCFI_OBJECT;



LOUSTATUS 
LouKeLoadCoffImageA(
    string          Path,
    string          FileName,      
    PCFI_OBJECT     CfiObject
);


#ifdef __cplusplus
}
#endif
#endif