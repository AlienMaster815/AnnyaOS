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
#define CFI_DDOFFSET_UNUSED_TABLE                       15
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


typedef union _CFI_SYMBOL_TABLE_NAME{
    UINT64                  ShortName;
    struct {
        UINT32              Zeroes;
        UINT32              Offset;
    };
}CFI_SYMBOL_TABLE_NAME, * PCFI_SYMBOL_TABLE_NAME;

typedef struct _CFI_SYMTABLE_AUXFMT_1{
    UINT32      TagIndex;
    UINT32      TotalSize;
    UINT32      PointerToLineNumber;
    UINT32      PointerToNextFunction;
    UINT16      Unused;
}CFI_SYMTABLE_AUXFMT_1, * PCFI_SYMTABLE_AUXFMT_1;

typedef struct _CFI_SYMTABLE_AUXFMT_2{
    UINT32      Unused;
    UINT16      LineNumber;
    UINT8       Unused1[6];
    UINT32      PointerToNextFunction;
    UINT16      Unused2;
}CFI_SYMTABLE_AUXFMT_2, * PCFI_SYMTABLE_AUXFMT_2;

typedef struct _CFI_SYMTABLE_AUXFMT_3{
    UINT32      TagIndex;
    UINT32      Characteristics;
    UINT8       Unused[10];
}CFI_SYMTABLE_AUXFMT_3, * PCFI_SYMTABLE_AUXFMT_3;

typedef struct _CFI_SYMTABLE_AUXFMT_4{
    UINT8       FileName[18];
}CFI_SYMTABLE_AUXFMT_4, * PCFI_SYMTABLE_AUXFMT_4;

typedef struct _CFI_SYMTABLE_AUXFMT_5{
    UINT32      Length;
    UINT16      NumberOfRelocations;
    UINT16      NumberOfLineNumbers;
    UINT32      CheckSum;
    UINT16      Number;
    UINT8       Selection;
    UINT8       Unused[3];
}CFI_SYMTABLE_AUXFMT_5, * PCFI_SYMTABLE_AUXFMT_5;

typedef union PACKED _CFI_SYMTABLE_AUXFMT{ //sanity pack
    CFI_SYMTABLE_AUXFMT_1   Fmt1;
    CFI_SYMTABLE_AUXFMT_2   Fmt2;
    CFI_SYMTABLE_AUXFMT_3   Fmt3;
    CFI_SYMTABLE_AUXFMT_4   Fmt4;
    CFI_SYMTABLE_AUXFMT_5   Fmt5;
    UINT8                   Sanity[18]; //all tables sum to 18 
}CFI_SYMTABLE_AUXFMT, * PCFI_SYMTABLE_AUXFMT;

typedef struct _CFI_SYMBOL_TABLE{
    CFI_SYMBOL_TABLE_NAME   Name;
    UINT32                  Value;
    UINT16                  SectionNumber;
    UINT16                  Type;
    UINT8                   StorageClass;
    UINT8                   NumberOfAuxSymbols;
    CFI_SYMTABLE_AUXFMT     Formats[];
}CFI_SYMBOL_TABLE, * PCFI_SYMBOL_TABLE;

static inline UINT32* GetCoffStringTable(PCFI_SYMBOL_TABLE Table){
    if(!Table){
        return 0x00;
    }
    return (UINT32*)((UINT8*)&Table->Formats[Table->NumberOfAuxSymbols] + sizeof(CFI_SYMBOL_TABLE));
}

#define CFI_SYMTBL_SN_UNDEFINED    0     
#define CFI_SYMTBL_SN_ABSOLUTE     (UINT16)-1
#define CFI_SYMTBL_SN_DEBUG        (UINT16)-2

#define CFI_SYMTBLE_TYPE_NULL           0
#define CFI_SYMTBLE_TYPE_VOID           1
#define CFI_SYMTBLE_TYPE_CHAR           2
#define CFI_SYMTBLE_TYPE_SHORT          3
#define CFI_SYMTBLE_TYPE_INT            4
#define CFI_SYMTBLE_TYPE_LONG           5
#define CFI_SYMTBLE_TYPE_FLOAT          6
#define CFI_SYMTBLE_TYPE_DOUBLE         7
#define CFI_SYMTBLE_TYPE_STRUCT         8
#define CFI_SYMTBLE_TYPE_UNION          9
#define CFI_SYMTBLE_TYPE_ENUM           10
#define CFI_SYMTBLE_TYPE_MOE            11
#define CFI_SYMTBLE_TYPE_BYTE           12
#define CFI_SYMTBLE_TYPE_WORD           13
#define CFI_SYMTBLE_TYPE_UINT           14
#define CFI_SYMTBLE_TYPE_DWORD          15

#define CFI_SYMTABLE_DTYPE_NULL         0
#define CFI_SYMTABLE_DTYPE_POINTER      1
#define CFI_SYMTABLE_DTYPE_FUNCTION     2
#define CFI_SYMTABLE_DTYPE_ARRAY        3

#define CFI_SYMTABLE_CLASS_END_OF_FUNCTION  (UINT8)-1
#define CFI_SYMTABLE_CLASS_NULL                     0
#define CFI_SYMTABLE_CLASS_AUTOMATIC                1
#define CFI_SYMTABLE_CLASS_EXTERNAL                 2
#define CFI_SYMTABLE_CLASS_STATIC                   3
#define CFI_SYMTABLE_CLASS_REGISTER                 4
#define CFI_SYMTABLE_CLASS_EXTERNAL_DEF             5
#define CFI_SYMTABLE_CLASS_LABEL                    6
#define CFI_SYMTABLE_CLASS_UNDEFINED_LABEL          7
#define CFI_SYMTABLE_CLASS_MEMBER_OF_STRUCT         8
#define CFI_SYMTABLE_CLASS_ARGUMENT                 9
#define CFI_SYMTABLE_CLASS_STRUCT_TAG               10
#define CFI_SYMTABLE_CLASS_MEMBER_OF_UNION          11
#define CFI_SYMTABLE_CLASS_UNION_TAG                12
#define CFI_SYMTABLE_CLASS_TYPE_DEFINITION          13
#define CFI_SYMTABLE_CLASS_UNDEFINED_STATIC         14
#define CFI_SYMTABLE_CLASS_ENUM_TAG                 15
#define CFI_SYMTABLE_CLASS_MEMBER_OF_ENUM           16
#define CFI_SYMTABLE_CLASS_REGISTER_PARANM          17
#define CFI_SYMTABLE_CLASS_BIT_FIELD                18
#define CFI_SYMTABLE_CLASS_BLOCK                    100
#define CFI_SYMTABLE_CLASS_FUNCTION                 101
#define CFI_SYMTABLE_CLASS_END_OF_STRUCTURE         102
#define CFI_SYMTABLE_CLASS_FILE                     103
#define CFI_SYMTABLE_CLASS_SECTION                  104
#define CFI_SYMTABLE_CLASS_WEAK_EXTERNAL            105
#define CFI_SYMTABLE_CLASS_CLR_TOKEN                107

typedef struct _CFI_ATTRIBUTE_CERTICIFATE_TABLE{
    UINT32      Length;
    UINT16      Revision;
    UINT16      CertificateType;
    UINT8       Certificate;
}CFI_ATTRIBUTE_CERTICIFATE_TABLE, * PCFI_ATTRIBUTE_CERTICIFATE_TABLE;

#define CFI_WINCERT_REVISION_10     0x0100
#define CFI_WINCERT_REVISION_20     0x0200

#define CFI_WINCERT_TYPE_X509       0x0001
#define CFI_WINCERT_TYPE_DATA       0x0002
#define CFI_WINCERT_TYPE_RESERVED   0x0003
#define CFI_WINCERT_TYPE_SIGNED     0x0004

typedef struct _CFI_DELAY_LOAD_DIRECTORY_TABLE{
    UINT32          Attribute;
    UINT32          Name;
    UINT32          ModuleHandle;
    UINT32          DelayImportNameTable;
    UINT32          BoundDelayImportNameTable;
    UINT32          UnloadDelayImportTable;
    UINT32          TimeStamp;
}CFI_DELAY_LOAD_DIRECTORY_TABLE, * PCFI_DELAY_LOAD_DIRECTORY_TABLE;

typedef struct _CFI_DEBUG_DIRECTORY{
    UINT32          Characteristics;
    UINT32          TimeDateStamp;
    UINT16          MajorVersion;
    UINT16          MinorVersion;
    UINT32          Type;
    UINT32          SizeOfData;
    UINT32          AddressOfRawData;
    UINT32          PointerToRawData;
}CFI_DEBUG_DIRECTORY, * PCFI_DEBUG_DIRECTORY;

#define CFI_DEBUG_TYPE_UNKOWN           0
#define CFI_DEBUG_TYPE_COFF             1
#define CFI_DEBUG_TYPE_CODEVIEW         2
#define CFI_DEBUG_TYPE_FPO              3
#define CFI_DEBUG_TYPE_MISC             4
#define CFI_DEBUG_TYPE_EXCEPTION        5
#define CFI_DEBUG_TYPE_FIXUP            6
#define CFI_DEBUG_TYPE_OMAP_TO_SRC      7
#define CFI_DEBUG_TYPE_OMAP_FROM_SRC    8
#define CFI_DEBUG_TYPE_BORLAND          9
#define CFI_DEBUG_TYPE_RESERVED10       10
#define CFI_DEBUG_TYPE_CLSID            11
#define CFI_DEBUG_TYPE_REPRO            16

#define CFI_FPO_FRAME_FPO   0
#define CFI_FPO_FRAME_TRAP  1
#define CFI_FPO_FRAME_TSS   2

typedef struct _CFI_FPO_DATA{
    UINT32      OffsetStart;
    UINT32      ProcSize;
    UINT32      Locals;
    UINT16      Params;
    UINT16      Polog       :   8;
    UINT16      Regs        :   3;
    UINT16      HasSEH      :   1;
    UINT16      UseBP       :   1;
    UINT16      Reserved    :   1;
    UINT16      Frame       :   2;
}CFI_FPO_DATA, * PCFI_FPO_DATA;

typedef struct _CFI_EXPORT_DIRECTORY_TABLE{
    UINT32      ExportFlags;
    UINT32      TimeDateStamp;
    UINT16      MajorVersion;
    UINT16      MinorVersion;
    UINT32      NameRVA;
    UINT32      OrdinalBase;
    UINT32      AddressTableEntries;
    UINT32      NumberOfNamePointers;
    UINT32      ExportAddressTableRVA;
    UINT32      NamePointerTableRVA;
    UINT32      OrdinalTableRVA; 
}CFI_EXPORT_DIRECTORY_TABLE, * PCFI_EXPORT_DIRECTORY_TABLE;

typedef union _CFI_EXPORT_ADDRESS_TABLE{
    UINT32      ExportRVA;
    UINT32      ForwarderRVA;
}CFI_EXPORT_ADDRESS_TABLE, * PCFI_EXPORT_ADDRESS_TABLE;

typedef struct _CFI_IMPORT_DIRECTORY_TABLE{
    UINT32      IltRvaCharacteristics;
    UINT32      TimeDateStamp;
    UINT32      ForwarderChain;
    UINT32      NameRVA;
    UINT32      ImportAddressTable;
}CFI_IMPORT_DIRECTORY_TABLE, * PCFI_IMPORT_DIRECTORY_TABLE;

typedef UINT32* CFI_IMPORT_LOOKUP_TABLE64, * PCFI_IMPORT_LOOKUP_TABLE64; 
typedef UINT32* CFI_IMPORT_LOOKUP_TABLE32, * PCFI_IMPORT_LOOKUP_TABLE32;

#define CFI_IMPORT_LOOKUP_TABLE32_PARSE_BY_ORDINAL    0x80000000
#define CFI_IMPORT_LOOKUP_TABLE64_PARSE_BY_ORDINAL    0x8000000000000000

typedef struct _CFI_HINT_NAME_TABLE{
    UINT16      Hint;
    UINT8       Name[];
}CFI_HINT_NAME_TABLE, * PCFI_HINT_NAME_TABLE;

typedef struct _X66_PLATFORM_FUNCTION_TABLE{
    UINT32      BeginAddress;
    UINT32      EndAddress;
    UINT32      UnwindInformation;
}X66_PLATFORM_FUNCTION_TABLE, * PX66_PLATFORM_FUNCTION_TABLE;

typedef struct _CFI_BASE_RELOCATION_BLOCK{
    UINT32              PageRVA;
    UINT32              BlockSize;
    union{
        struct{
            UINT16      Offset : 12;
            UINT16      Type   : 4; 
        };
        UINT16          SanityIndexor;//compiler rounds to 16 bit indexing
    }                   RelocationEntires[];
}CFI_BASE_RELOCATION_BLOCK, * PCFI_BASE_RELOCATION_BLOCK;

#define CFI_BASE_RELOCATION_TYPE_BASED_ABSOLUTE         0
#define CFI_BASE_RELOCATION_TYPE_BASED_HIGH             1
#define CFI_BASE_RELOCATION_TYPE_BASED_LOW              2
#define CFI_BASE_RELOCATION_TYPE_BASED_HIGH_LOW         3
#define CFI_BASE_RELOCATION_TYPE_BASED_HIGH_ADJ         4
#define CFI_BASE_RELOCATION_TYPE_BASED_MIPS_JMPADDR     5
#define CFI_BASE_RELOCATION_TYPE_BASED_ARM_MOV32        5
#define CFI_BASE_RELOCATION_TYPE_BASED_RISCV_HIGH20     5
#define CFI_BASE_RELOCATION_TYPE_BASED_THUMB_MOV32      7
#define CFI_BASE_RELOCATION_TYPE_BASED_RISCV_LOW12L     7
#define CFI_BASE_RELOCATION_TYPE_BASED_RISCV_LOW12S     8
#define CFI_BASE_RELOCATION_TYPE_BASED_MIPS_JMPADDR16   9
#define CFI_BASE_RELOCATION_TYPE_BASED_DIR64            10


typedef struct _CFI_TLS_DIRECTORY32{
    UINT32      RawDataStartVA;
    UINT32      RawDaraEndVA;
    UINT32      AddressOfIndex;
    UINT32      AddressOfCallbacks;
    UINT32      SizeOfZeroFill;
    UINT32      Characteristics;
}CFI_TLS_DIRECTORY32, * PCFI_TLS_DIRECTORY32;

typedef struct _CFI_TLS_DIRECTORY64{
    UINT64      RawDataStartVA;
    UINT64      RawDaraEndVA;
    UINT64      AddressOfIndex;
    UINT64      AddressOfCallbacks;
    UINT32      SizeOfZeroFill;
    UINT32      Characteristics;
}CFI_TLS_DIRECTORY64, * PCFI_TLS_DIRECTORY64;

typedef union _CFI_TLS_DIRECTORY{
    CFI_TLS_DIRECTORY32     Directory32;
    CFI_TLS_DIRECTORY64     Directory64;
}CFI_TLS_DIRECTORY, * PCFI_TLS_DIRECTORY;

typedef VOID (NTAPI *PCFI_IMAGE_TLS_CALLBACK)(PVOID DllHandle, UINT32 Reason, PVOID Reserved);

#define CFI_DLL_PROCESS_DETATCH 0
#define CFI_DLL_PROCESS_ATTATCH 1
#define CFI_DLL_THREAD_ATTATCH  2
#define CFI_DLL_THREAD_DETATCH  3

typedef struct _CFI_LOAD_CONFIGURATION_LAYOUT32{
    UINT32      Characteristics;
    UINT32      TimeDateStamp;
    UINT16      MajorVersion;
    UINT16      MinorVersion;
    UINT32      GlobalFlagsClear;
    UINT32      GlobalFlagsSet;
    UINT32      CriticalSectionDefaultTimeout;
    UINT32      DeCommitFreeBlockThreshold;
    UINT32      DeCommitTotalFreeThreshold;
    UINT32      LockPrefixTable;
    UINT32      MaximumAllocationSize;
    UINT32      VirtualMemoryThreshold;
    UINT32      ProcessAffinityMask;    
    UINT32      ProcessHeapFlags;
    UINT16      CSDVersion;
    UINT16      Reserved;
    UINT32      EditList;
    UINT32      SecurityCookie;
    UINT32      SEHandlerTable;
    UINT32      SEHandlerCount;
    UINT32      GuardCFCheckFunctionPointer;
    UINT32      GuardCFDispatchFunctionPointe;
    UINT32      GuardCFFunctionTable;
    UINT32      GuardCFFunctionCount;
    UINT32      GuardFlags;
    UINT8       CodeIntegrity[12];
    UINT32      GuardAddressTakenIatEntryTable;
    UINT32      GuardAddressTakenIatEntryCount;
    UINT32      GuardLongJumpTargetTable;
    UINT32      GuardLongJumpTargetCount;
}CFI_LOAD_CONFIGURATION_LAYOUT32, * PCFI_LOAD_CONFIGURATION_LAYOUT32;

typedef struct _CFI_LOAD_CONFIGURATION_LAYOUT64{
    UINT32      Characteristics;
    UINT32      TimeDateStamp;
    UINT16      MajorVersion;
    UINT16      MinorVersion;
    UINT32      GlobalFlagsClear;
    UINT32      GlobalFlagsSet;
    UINT32      CriticalSectionDefaultTimeout;
    UINT64      DeCommitFreeBlockThreshold;
    UINT64      DeCommitTotalFreeThreshold;
    UINT64      LockPrefixTable;
    UINT64      MaximumAllocationSize;
    UINT64      VirtualMemoryThreshold;
    UINT64      ProcessAffinityMask;
    UINT32      ProcessHeapFlags;
    UINT16      CSDVersion;
    UINT16      Reserved;
    UINT64      EditList;
    UINT64      SecurityCookie;
    UINT64      SEHandlerTable;
    UINT64      SEHandlerCount;
    UINT64      GuardCFCheckFunctionPointer;
    UINT64      GuardCFDispatchFunctionPointe;
    UINT64      GuardCFFunctionTable;
    UINT64      GuardCFFunctionCount;
    UINT32      GuardFlags;
    UINT8       CodeIntegrity[12];
    UINT64      GuardAddressTakenIatEntryTable;
    UINT64      GuardAddressTakenIatEntryCount;
    UINT64      GuardLongJumpTargetTable;
    UINT64      GuardLongJumpTargetCount;
}CFI_LOAD_CONFIGURATION_LAYOUT64, * PCFI_LOAD_CONFIGURATION_LAYOUT64;

typedef union _CFI_LOAD_CONFIGURATION_LAYOUT{
    CFI_LOAD_CONFIGURATION_LAYOUT64 LoadConfigurationLayout64;
    CFI_LOAD_CONFIGURATION_LAYOUT32 LoadConfigurationLayout32;
}CFI_LOAD_CONFIGURATION_LAYOUT, * PCFI_LOAD_CONFIGURATION_LAYOUT;

#define CFI_GUARD_CF_INSTRUMENTED                       0x00000100
#define CFI_GUARD_CFW_INSTRUMENTED                      0x00000200
#define CFI_GUARD_CF_FUNCTION_TABLE_PRESENT             0x00000400
#define CFI_GUARD_SECURITY_COOKIE_UNUSED                0x00000800
#define CFI_GUARD_PROTECT_DELAYLOAD_IAT                 0x00001000
#define CFI_GUARD_DELAYLOAD_IAT_IN_ITS_OWN_SECTION      0x00002000
#define CFI_GUARD_CF_EXPORT_SUPPRESSION_INFO_PRESENT    0x00004000
#define CFI_GUARD_CF_ENABLE_EXPORT_SUPPRESSION          0x00008000
#define CFI_GUARD_CF_LONGJUMP_TABLE_PRESENT             0x00010000
#define CFI_GUARD_CF_FUNCTION_TABLE_SIZE_MASK           0xF0000000

#define CFI_GUARD_CF_FUNCTION_TABLE_SIZE_SHIFT          28

typedef struct _CFI_RESOURCE_DIRECTORY_ENTRIES{
    union{
        UINT32      NameOffset;
        UINT32      ID;
    };
    UINT32          DataEntryOffset;
    UINT32          SubDirectoryOffset;
}CFI_RESOURCE_DIRECTORY_ENTRIES, * PCFI_RESOURCE_DIRECTORY_ENTRIES;

typedef struct _CFI_RESOURCE_DIRECTORY_TABLE{
    UINT32                              Charecteristics;
    UINT32                              TimeDateStamp;
    UINT16                              MajorVersion;
    UINT16                              MinorVersion;
    UINT16                              NumberOfNameEntries;
    UINT16                              NumberOfIDEntries;
    CFI_RESOURCE_DIRECTORY_ENTRIES      Entires[];
}CFI_RESOURCE_DIRECTORY_TABLE, * PCFI_RESOURCE_DIRECTORY_TABLE;

typedef UNICODE_STRING CFI_RESOURCE_DIRECTORY_STRING, * PCFI_RESOURCE_DIRECTORY_STRING;

typedef struct _CFI_RESOURCE_DATA_ENTRY{
    UINT32      DataRva;
    UINT32      Size;
    UINT32      CodePage;
    UINT32      Reserved;
}CFI_RESOURCE_DATA_ENTRY, * PCFI_RESOURCE_DATA_ENTRY;

typedef struct _CFI_ARCHIVE_MEMBER_HEADERS{
    UINT8       Name[16];
    UINT8       Date[12];
    UINT8       UserID[6];
    UINT8       GroupID[6];
    UINT64      Mode;
    UINT8       Size[10];
    UINT16      EndOfHeader;
}CFI_ARCHIVE_MEMBER_HEADERS, * PCFI_ARCHIVE_MEMBER_HEADERS;

typedef struct _CFI_FIRST_LINKER_MEMBER{
    UINT32      NumberOfSymbols;
    UINT32      Offsets[];
}CFI_FIRST_LINKER_MEMBER, * PCFI_FIRST_LINKER_MEMBER;

//the following structure only represents the bottom half of the second linker
//and uses the first linker member for the upper half of the second linker
//to reduce redundancy of code 
typedef struct _CFI_SECOND_LINKER_MEMBER{ 
    UINT32      NumberOfSymbols;
    UINT16      Indices;
}CFI_SECOND_LINKER_MEMBER, * PCFI_SECOND_LINKER_MEMBER;

//use this to get the second member structure from the base of the second member table 
#define GET_SECOND_LINKER_MEMBER_FROM_BASE(BaseOfSecond)    ((PCFI_SECOND_LINKER_MEMBER)(UINT8*)((((PCFI_FIRST_LINKER_MEMBER)BaseOfSecond)->Indices *  sizeof(UINT32)) + sizeof(UINT32)) + (UINT8*)BaseOfSecond)

typedef struct _CFI_IMPORT_HEADER{
    UINT16      Signature1;
    UINT16      Signature2;
    UINT16      Version;
    UINT16      Machine;
    UINT32      TimeDateStamp;
    UINT32      SizeOfData;
    UINT16      OrdinalHint;
    UINT16      Type    :   2;
    UINT16      NameType:   3;
    UINT16      Reserved:   11;
}CFI_IMPORT_HEADER, * PCFI_IMPORT_HEADER;

#define CFI_IMPORT_TYPE_CODE    0
#define CFI_IMPORT_TYPE_DATA    1
#define CFI_IMPORT_TYPE_CONST   2

#define CFI_IMPORT_NAME_TYPE_ORDINAL    0
#define CFI_IMPORT_NAME_TYPE_NAME       1
#define CFI_IMPORT_NAME_TYPE_NOPREFIX   2
#define CFI_IMPORT_NAME_TYPE_UNDECORATE 3

typedef struct _CFI_OBJECT{
    FILE*                   CoffFile;
    string                  FormalName;
    BOOL                    AOA64;
    BOOL                    KernelObject;
    PCOFF_IMAGE_HEADER      ImageHeader;
    PVOID                   LoadedAddress;
    PVOID                   PhysicalLoadedAddress;
    PVOID                   ExecututionLoading;
    KERNEL_REFERENCE        Reference;
    PVOID                   Entry;
    mutex_t                 LockOutTagOut;    
}CFI_OBJECT, * PCFI_OBJECT;

LOUSTATUS
LouKeLoadCoffImageExA(
    string          FileNameAndPath,
    PCFI_OBJECT     LoadedObjectCheck,
    BOOL            KernelObject
);

LOUSTATUS 
LouKeLoadCoffImageA(
    string          Path,
    string          FileName,      
    PCFI_OBJECT     CfiObject,
    BOOL            KernelObject
);

#ifdef __cplusplus
}
#endif
#endif