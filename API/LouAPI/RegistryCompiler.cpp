#include <LouDDK.h>

typedef struct __attribute__((packed)) _LKR_FILE_HEADER{
    BYTE        Signature[]; //regf
    UINT32      PrimarySequenceID;
    UINT32      SecondarySequenceID;
    UINT64      FileTime;
    UINT32      MajorVersion;
    UINT32      MinorVersion;
    UINT32      FileType;
    UINT32      FileFormat;
    UINT32      RootKeyOffset;
    UINT32      HiveBinDataSize;
    UINT32      ClusterFactor;
    UINT8       Unused[64];
    UINT8       Padding[512 - 112];
}LKR_FILE_HEADER, * PLKR_FILE_HEADER;

#define LKR_FILE_HEADER_SIZE    4096

#define LKR_HBIN_OFFSET(x)   (((x) + 1) * 0x1000)

#define LKR_FILE_VERSION_MAJOR      1
#define LKR_FILE_VERSION_MINOR      6

#define LKR_FILE_TYPE_HIVE          0x00
#define LKR_FILE_TYPE_TRANSACTION_1 0x01
#define LKR_FILE_TYPE_TRANSACTION_2 0x02
#define LKR_FILE_TYPE_TRANSACTION_3 0x03
#define LKR_FILE_TYPE_TRANSACTION_4 0x04
#define LKR_FILE_TYPE_TRANSACTION_5 0x05
#define LKR_FILE_TYPE_TRANSACTION_6 0x06

typedef struct __attribute__((packed)) _LKR_HBIN_HEADER{
    UINT8       Signature[4]; //hbin
    UINT32      HiveBinOffset;
    UINT32      HiveBinSize;
    UINT64      Reserved;
    UINT64      TimeStamp;
    UINT32      Spare;
}LKR_HBIN_HEADER, * PLKR_HBIN_HEADER;

//following structure is 8 byte algined on disk
typedef struct __attribute__((packed)) _LKR_HBIN_CELL{
    UINT32      CellSize;
    UINT8       CellData[];
}LKR_HBIN_CELL, * PLKR_HBIN_CELL;

//following structure is 8 byte algined on disk
typedef struct __attribute__((packed)) _LKR_NAMED_KEY{
    UINT8       Signature[2]; //nk
    UINT16      Flags;
    UINT64      FileTime;
    UINT32      Reserved;
    UINT32      ParentKeyOffset;
    UINT32      SubKeyCount;
    UINT32      VolotileSubKeyCount;
    UINT32      VolatileSubKeyListOffset;
    UINT32      ValueCount;
    UINT32      SecurityKeyOffset;
    UINT32      ClassNameOffset;
    UINT32      LargestSubKeyNameSize;
    UINT32      LargestClassKeyNameSize;
    UINT32      LargestValueNameSize;
    UINT32      LargestValueDataSize;
    UINT32      Ignore;
    UINT16      KeyNameSize;
    UINT16      CLassNameSize;
    LPWSTR      KeyNameString;
}LKR_NAMED_KEY, * PLKR_NAMED_KEY;

#define NAMED_KEY_FLAG_VOLATILE         (1)
#define NAMED_KEY_FLAG_HIVE_EXIT        (1 << 1)
#define NAMED_KEY_FLAG_HIVE_ENTRY       (1 << 2)
#define NAMED_KEY_FLAG_NO_DELETE        (1 << 3)
#define NAMED_KEY_FLAG_SYM_LINK         (1 << 4)
#define NAMED_KEY_FLAG_COMP_NAME        (1 << 5)
#define NAMED_KEY_FLAG_PREFEF_HANDLE    (1 << 6)
#define NAMED_KEY_FLAG_VIRT_MIRROR      (1 << 7)
#define NAMED_KEY_FLAG_VIRT_TARGET      (1 << 8)
#define NAMED_KEY_FLAG_UNKNOWN          (0xFE << 8)
#define NAMED_KEY_FLAG_VIRT_STORE       (1 << 9)

typedef struct __attribute__((packed)) _LKR_SECURITY_KEY{
    UINT8       Signature[2];//sk
    UINT16      Reserved;
    UINT32      PrevSkOffset;
    UINT32      NextSkOffset;
    UINT32      ReferenceCount;
    UINT32      DescriptorSize;
    UINT8       DescriptorData[];
}LKR_SECURITY_KEY, * PLKR_SECURITY_KEY; 

typedef struct __attribute__((packed)) _LEAF_HASH_SUB_KEY{
    UINT32      NamedKeyOffset;
    UINT32      Hash;
}LEAF_HASH_SUB_KEY, * PLEAF_HASH_SUB_KEY;

typedef struct __attribute__((packed)) _LEAF_ITEM_SUB_KEY{
    UINT32      NamedKeyOffset;
}LEAF_ITEM_SUB_KEY, * PLEAF_ITEM_SUB_KEY;

typedef struct __attribute__((packed)) _REFERENCE_ITEM_SUB_KEY{
    UINT32      SubKeyListOffset;
}REFERENCE_ITEM_SUB_KEY, * PREFERENCE_ITEM_SUB_KEY;

typedef struct __attribute__((packed)) _LKR_SUB_KEY_LIST{
    UINT8                       Signature[2];//lf, lh, li, ri
    UINT16                      ElementCount;
    union{
        UINT8                   ElementData[];
        LEAF_HASH_SUB_KEY       LeafHash;
        LEAF_HASH_SUB_KEY       Leaf;
        LEAF_ITEM_SUB_KEY       LeafItem;
        REFERENCE_ITEM_SUB_KEY  ReferenceItem;
    };  
}LKR_SUB_KEY_LIST, * PLKR_SUB_KEY_LIST;

typedef struct __attribute__((packed)) _LKR_VALUE_KEY{
    UINT8       Signature[2]; //vk
    UINT16      ValueNameSize;
    UINT32      DataSize;
    UINT32      DataOfset;
    UINT32      DataType;
    UINT16      Flags;
    UINT16      Reserved;
    UINT8       ValueName;
}LKR_VALUE_KEY, * PLKR_VALUE_KEY;

#define VALUE_KEY_DATA_SIZE_MAGIC 0x80000000
#define VALUE_KEY_DATA_SIZE_CHECK (UINT32_MAX & ~(DATA_SIZE_MAGIC))

#define VALUE_KEY_DATA_SIZE_DWORD 4
#define VALUE_KEY_DATA_SIZE_WORD  2
#define VALUE_KEY_DATA_SIZE_BYTE  1
#define VALUE_KEY_DATA_SIZE_NULL  0

#define VALUE_KEY_DATA_TYPE_NONE                0x00000000
#define VALUE_KEY_DATA_TYPE_STRING              0x00000001
#define VALUE_KEY_DATA_TYPE_EXPANADABLE         0x00000002
#define VALUE_KEY_DATA_TYPE_BINARY              0x00000003
#define VALUE_KEY_DATA_TYPE_DWORD_LE            0x00000004
#define VALUE_KEY_DATA_TYPE_DWORD_BE            0x00000005
#define VALUE_KEY_DATA_TYPE_SYM_LINK            0x00000006
#define VALUE_KEY_DATA_TYPE_MULTI               0x00000007
#define VALUE_KEY_DATA_TYPE_RESOURCE_LIST       0x00000008
#define VALUE_KEY_DATA_TYPE_FULL_RESOURCE_DESC  0x00000009
#define VALUE_KEY_DATA_TYPE_RESOURCE_REQ_LIST   0x0000000A
#define VALUE_KEY_DATA_TYPE_QWORD               0x0000000B

#define VALUE_KEY_FLAG_COMP_NAME                0x0001

typedef struct _LKR_DATA_BLOCK_KEY{
    UINT8       Signature[2];
    UINT16      Segments;
    UINT32      DataBlock;
}LKR_DATA_BLOCK_KEY, * PLKR_DATA_BLOCK_KEY;

#define ACTIVEDS_DLL_CLASS      L"activeds.dll"
#define CLASS_CLASS             L"Class"
#define CYGNUS_CLASS            L"Cygnus"
#define CYGWIN_CLASS            L"Cygwin"
#define DEFAULT_CLASS           L"DefaultClass"
#define OS2SS_CLASS             L"O2SS"
#define PROGMAN_CLASS           L"progman"
#define REG_SZ_CLASS            L"REG_SZ_CLASS"
#define SHELL_CLASS             L"Shell"
#define TCPMON_CLASS            L"TCPMon"

static UINT32 CreateLhSubHashFromUtf16(LPWSTR Str){
    size_t StrSize = wcslen(Str);

    UINT32 Hash = 0;
    for(size_t i = 0 ; i < StrSize; i++){
        Hash *= 37;
        Hash += _wcsupr(Str[i]);
    }

    return Hash;
}

typedef struct _LKR_FILE_HANDLE{
    FILE*               FileStreamHandle;
    PLKR_FILE_HEADER    FileHeader;
}LKR_FILE_HANDLE, * PLKR_FILE_HANDLE;

FILE* LouKeCreateRegistryFile(
    LPWSTR Path,
    LPWSTR FileName
){
    PLKR_FILE_HANDLE NewFile = LouKeMallocType(LKR_FILE_HANDLE, KERNEL_GENERIC_MEMORY);
    NewFile->FileStreamHandle = LouKeCreateFile(
        Path,
        FileName
    );
    PLKR_FILE_HEADER FileHeader = (PLKR_FILE_HEADER)LouKeMalloc(4096, KERNEL_GENERIC_MEMORY);

    memcpy(FileHeader->Signature, "regf", 4);

    NewFile->FileHeader->MajorVersion = LKR_FILE_VERSION_MAJOR;
    NewFile->FileHeader->MinorVersion = LKR_FILE_VERSION_MINOR;
    NewFile->FileHeader->FileType = LKR_FILE_TYPE_HIVE;
    NewFile->FileHeader->ClusterFactor = 1; //VFS uses 512 byte sectors

    LouKeConcatenateFile(
        NewFile->FileStreamHandle,
        NewFile->FileHeader,
        4096
    );

    return (FILE*)NewFile;
}