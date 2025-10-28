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

#define CFI_CHARACTERISTICS_RELOCS_STRIPPED             1
#define CFI_CHARACTERISTICS_EXECUTABLE_IMAGE            (1 << 1)
#define CFI_CHARACTERISTICS_LINE_NUMS_STRIPED           (1 << 2)
#define CFI_CHARACTERISTICS_SYMS_STRIPPED               (1 << 3)
#define CFI_CHARACTERISTICS_AGGRESSIVE_WS_TRIM          (1 << 4)
#define CFI_CHARARTERISTICS_LARGE_ADDRESS_AWARE         (1 << 5)
//(1 << 6) is reserved
#define CFI_CHARACTERISTICS_FILE_BYTES_RESERVED_LO      (1 << 7)
#define CFI_CHARACTERISTICS_32BIT_MACHINE               (1 << 8)
#define CFI_CHARACTERISTICS_DEBUG_STRIPPED              (1 << 9)
#define CFI_CHARACTERISTICS_REMOVABLE_RUN_FROM_SWAP     (1 << 10)
#define CFI_CHARACTERISTICS_NET_RUN_FROM_SWAP           (1 << 11)
#define CFI_CHARACTERISTICS_SYSTEM                      (1 << 12)
#define CFI_CHARACTERISTICS_DLL                         (1 << 13)
#define CFI_CHARACTERISTICS_UP_SYSTEM_ONLY              (1 << 14)
#define CFI_CHARACTERISTICS_FILE_BYTES_RESERVED_HI      (1 << 15)

#define CFI_OPTIONAL_HEADER_PE32_MAGIC      0x010B
#define CFI_OPTIONAL_HEADER_PE3264_MAGIC    0x020B

typedef struct _COFF_IMAGE_OPTIONAL_HEADER32{
    UINT16      Magic;
    UINT8       LinkerMajorVersion;
    UINT8       LinkerMinorVersion;
    UINT32      SizeOfCode;
    UINT32      SizeOfInitializedData;
    UINT32      SizeOfUnInitializedData;
    UINT32      AddressOfEntryPoint;
    UINT32      BaseOfCode;
    UINT32      BaseOfData;//this is not here in PE32+ AKA PE3264
    UINT32      ImageBase;
    UINT32      SectionAligment;
    UINT32      FileAlignment;
    UINT16      MajorOperatingSystemVersion;
    UINT16      MinorOperatingSystemVersion;
    UINT16      MajorImageVersion;
    UINT16      MinorImageVersion;
    UINT16      MajorSubsystemVersion;
    UINT16      MinorSubsystemVersion;
    UINT32      Win32VersionValue;
    UINT32      SizeOfImage;
    UINT32      SizeOfHeader;
    UINT32      Checksum;
    UINT16      Subsystem;
    UINT16      DllCharacteristics;
    UINT32      SizeOfStackReserve;
    UINT32      SizeOfStackCommit;
    UINT32      SizeOfHeapReserve;
    UINT32      SizeOfHeapCommit;
    UINT32      LoaderFlags;
    UINT32      NumberOfRvaAndSizes;
}COFF_IMAGE_OPTIONAL_HEADER32, * PCOFF_IMAGE_OPTIONAL_HEADER32;

typedef struct _COFF_IMAGE_OPTIONAL_HEADER64{
    UINT16      Magic;
    UINT8       LinkerMajorVersion;
    UINT8       LinkerMinorVersion;
    UINT32      SizeOfCode;
    UINT32      SizeOfInitializedData;
    UINT32      SizeOfUnInitializedData;
    UINT32      AddressOfEntryPoint;
    UINT32      BaseOfCode;
    UINT64      ImageBase;
    UINT32      SectionAligment;
    UINT32      FileAlignment;
    UINT16      MajorOperatingSystemVersion;
    UINT16      MinorOperatingSystemVersion;
    UINT16      MajorImageVersion;
    UINT16      MinorImageVersion;
    UINT16      MajorSubsystemVersion;
    UINT16      MinorSubsystemVersion;
    UINT32      Win32VersionValue;
    UINT32      SizeOfImage;
    UINT32      SizeOfHeader;
    UINT32      Checksum;
    UINT16      Subsystem;
    UINT16      DllCharacteristics;
    UINT64      SizeOfStackReserve;
    UINT64      SizeOfStackCommit;
    UINT64      SizeOfHeapReserve;
    UINT64      SizeOfHeapCommit;
    UINT32      LoaderFlags;
    UINT32      NumberOfRvaAndSizes;
}COFF_IMAGE_OPTIONAL_HEADER64, * PCOFF_IMAGE_OPTIONAL_HEADER64;
    
typedef union _COFF_IMAGE_OPTIONAL_HEADER{
    COFF_IMAGE_OPTIONAL_HEADER32 PE32;
    COFF_IMAGE_OPTIONAL_HEADER64 PE64;
}COFF_IMAGE_OPTIONAL_HEADER, * PCOFF_IMAGE_OPTIONAL_HEADER;

typedef struct _COFF_IMAGE_HEADER{
    COFF_IMAGE_STANDARD_HEADER  StandardHeader;
    COFF_IMAGE_OPTIONAL_HEADER  OptionalHeader;
}COFF_IMAGE_HEADER, * PCOFF_IMAGE_HEADER;

//14 windows subsystem

#ifdef __cplusplus
}
#endif
#endif