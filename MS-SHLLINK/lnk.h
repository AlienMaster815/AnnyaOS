#ifndef _LNK_COMPILER_H
#define _LNK_COMPILER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/kernel/loustatus.h"

#define PACKED __attribute__((packed))

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef uint8_t     UINT8;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;

typedef char* string;

typedef struct PACKED _GUID{
    UINT8       Buffer[16];
}GUID, * PGUID;

typedef GUID CLSID;

typedef union PACKED _FILE_TIME{
    struct {
        UINT64  Raw;
    };
    UINT64      Uint64;
}FILE_TIME, * PFILE_TIME;

typedef union PACKED _LINK_FLAGS{
    struct{
        UINT32  HasLinkTargetIDList             :   1;
        UINT32  HasLinkInfo                     :   1;
        UINT32  HasName                         :   1;
        UINT32  HasRelativePath                 :   1;
        UINT32  HasWorkingDirectory             :   1;
        UINT32  HasArguments                    :   1;
        UINT32  HasIconLocation                 :   1;
        UINT32  IsUnicode                       :   1;
        UINT32  ForceNoLinkInfo                 :   1;
        UINT32  HasExpString                    :   1;
        UINT32  RunInSeperateProcess            :   1;
        UINT32  Unused1                         :   1;
        UINT32  HasDarwinID                     :   1;
        UINT32  RunAsUser                       :   1;
        UINT32  HasExpIcon                      :   1;
        UINT32  NoPidAlias                      :   1;
        UINT32  Unused2                         :   1;
        UINT32  RunWithShimLayer                :   1;
        UINT32  ForceNoLinkTrack                :   1;
        UINT32  EnableTargetMetaData            :   1;
        UINT32  DisableLinkPathTracking         :   1;
        UINT32  DisableKnownFolderTracking      :   1;
        UINT32  DisableKnownFolderAlias         :   1;
        UINT32  AllowLinkToLink                 :   1;
        UINT32  UnaliasedOnSave                 :   1;
        UINT32  PreferedEnviornmentPath         :   1;
        UINT32  KeepLocalIDListForUNCTarget     :   1;
    };
    UINT32      Uint32;
}LINK_FLAGS, * PLINK_FLAGS;

typedef union PACKED _FILE_ATTRIBUTES_FLAGS{
    struct {
        UINT32  ReadOnly            :   1;
        UINT32  Hidden              :   1;
        UINT32  Reserved1           :   1;
        UINT32  Directory           :   1;
        UINT32  Archive             :   1;
        UINT32  Reserved2           :   1;
        UINT32  Normal              :   1;
        UINT32  Temporary           :   1;
        UINT32  SparseFile          :   1;
        UINT32  ReparseFile         :   1;
        UINT32  Compressed          :   1;
        UINT32  Offline             :   1;
        UINT32  NotContextIndexed   :   1;
        UINT32  Encrypted           :   1;
    };
    UINT32      Uint32;
}FILE_ATTRIBUTES_FLAGS, * PFILE_ATTRIBUTES_FLAGS;

#define MSSHLLINK_SW_SHOW_NORMAL        0x00000001
#define MSSHLLINK_SW_SHOW_MAXIMIZED     0x00000003
#define MSSHLLINK_SW_SHOW_MINNOACTIVE   0x00000007

#define MSSHLLINK_HKF_NO_KEY    0x00

//numerics
#define MSSHLLINK_HKF_0         0x30
#define MSSHLLINK_HKF_1         0x31
#define MSSHLLINK_HKF_2         0x32
#define MSSHLLINK_HKF_3         0x33
#define MSSHLLINK_HKF_4         0x34
#define MSSHLLINK_HKF_5         0x35
#define MSSHLLINK_HKF_6         0x36
#define MSSHLLINK_HKF_7         0x37
#define MSSHLLINK_HKF_8         0x38
#define MSSHLLINK_HKF_9         0x39
//ansi
#define MSSHLLINK_HKF_A         0x41
#define MSSHLLINK_HKF_B         0x42
#define MSSHLLINK_HKF_C         0x43
#define MSSHLLINK_HKF_D         0x44
#define MSSHLLINK_HKF_E         0x45
#define MSSHLLINK_HKF_F         0x46
#define MSSHLLINK_HKF_G         0x47
#define MSSHLLINK_HKF_H         0x48
#define MSSHLLINK_HKF_I         0x49
#define MSSHLLINK_HKF_J         0x4A
#define MSSHLLINK_HKF_K         0x4B
#define MSSHLLINK_HKF_L         0x4C
#define MSSHLLINK_HKF_M         0x4D
#define MSSHLLINK_HKF_N         0x4E
#define MSSHLLINK_HKF_O         0x4F
#define MSSHLLINK_HKF_P         0x50
#define MSSHLLINK_HKF_Q         0x51
#define MSSHLLINK_HKF_R         0x52
#define MSSHLLINK_HKF_S         0x53
#define MSSHLLINK_HKF_T         0x54
#define MSSHLLINK_HKF_U         0x55
#define MSSHLLINK_HKF_V         0x56
#define MSSHLLINK_HKF_W         0x57
#define MSSHLLINK_HKF_X         0x58
#define MSSHLLINK_HKF_Y         0x59
#define MSSHLLINK_HKF_Z         0x5A
//functions
#define MSSHLLINK_HKF_F1        0x70
#define MSSHLLINK_HKF_F2        0x71
#define MSSHLLINK_HKF_F3        0x72
#define MSSHLLINK_HKF_F4        0x73
#define MSSHLLINK_HKF_F5        0x74
#define MSSHLLINK_HKF_F6        0x75
#define MSSHLLINK_HKF_F7        0x76
#define MSSHLLINK_HKF_F8        0x77
#define MSSHLLINK_HKF_F9        0x78
#define MSSHLLINK_HKF_F10       0x79
#define MSSHLLINK_HKF_F11       0x7A
#define MSSHLLINK_HKF_F12       0x7B
#define MSSHLLINK_HKF_F13       0x7C
#define MSSHLLINK_HKF_F14       0x7D
#define MSSHLLINK_HKF_F15       0x7E
#define MSSHLLINK_HKF_F16       0x7F
#define MSSHLLINK_HKF_F17       0x80
#define MSSHLLINK_HKF_F18       0x81
#define MSSHLLINK_HKF_F19       0x82
#define MSSHLLINK_HKF_F20       0x83
#define MSSHLLINK_HKF_F21       0x84
#define MSSHLLINK_HKF_F22       0x85
#define MSSHLLINK_HKF_F23       0x86
#define MSSHLLINK_HKF_F24       0x87
//Locks
#define MSSHLLINK_HKF_NUMLOCK       0x90
#define MSSHLLINK_HKF_SCROLLLOCK    0x91

#define MSSHLLINK_HKF_HOTKEYF_NONE      0x00
#define MSSHLLINK_HKF_HOTKEYF_SHIFT     0x01
#define MSSHLLINK_HKF_HOTKEYF_CONTROL   0x02
#define MSSHLLINK_HKF_HOTKEYF_ALT       0x04

typedef union PACKED _HOT_KEY_FLAGS{
    struct {
        UINT8   VirtualKey;
        UINT8   Modifier;
    };
    UINT16      Uint16;
}HOT_KEY_FLAGS, * PHOT_KEY_FLAGS;

#define SHELL_LINK_HEADER_SIZE  0x4C

typedef struct PACKED _SHELL_LINK_HEADER{
    UINT32                  HeaderSize;
    CLSID                   LinkCLSID;
    LINK_FLAGS              LinkFlags;
    FILE_ATTRIBUTES_FLAGS   FileAttrubutes;
    FILE_TIME               CreationTime;
    FILE_TIME               AccessTime;
    FILE_TIME               WriteTime;
    UINT32                  FileSize;
    UINT32                  IconIndex;
    UINT32                  ShowCommand;
    HOT_KEY_FLAGS           HotKey;
    UINT16                  Reserved1;
    UINT32                  Reserved2;
    UINT32                  Reserved3;
}SHELL_LINK_HEADER, * PSHELL_LINK_HEADER;

static inline LOUSTATUS MsShlLinkGetShowCommandValue(
    PSHELL_LINK_HEADER  LinkHeader,
    UINT32*             Out
){
    if(!Out || !LinkHeader){
        return STATUS_UNSUCCESSFUL;
    }
    switch(LinkHeader->ShowCommand){
        case MSSHLLINK_SW_SHOW_MAXIMIZED:
        case MSSHLLINK_SW_SHOW_MINNOACTIVE:
            *Out = LinkHeader->ShowCommand;
            break;
        default:
            *Out = MSSHLLINK_SW_SHOW_NORMAL;
            break;
    }
    return STATUS_SUCCESS;
}

typedef struct PACKED _SHLLINK_ID_LIST{
    UINT16  ItemIDSize;
    UINT8   Data[];
}SHLLINK_ID_LIST, * PSHLLINK_ID_LIST;

typedef struct PACKED _SHLLINK_TARGET_ID_LIST{
    UINT16      IDListSize;
    UINT8       IdList[];
}SHLLINK_TARGET_ID_LIST, * PSHLLINK_TARGET_ID_LIST;

typedef union PACKED _SHLLINK_LINK_INFO_FLAGS{
    struct {
        UINT32  VolumeIDAndLocalBasePath            :   1;
        UINT32  CommonNetworkRelativeLinkAndPath    :   1;
    };
    UINT32      Uint32;
}SHLLINK_LINK_INFO_FLAGS, * PSHLLINK_LINK_INFO_FLAGS;

typedef struct PACKED _SHLLING_LINK_INFO{
    UINT32                      Size;
    UINT32                      HeaderSize;
    SHLLINK_LINK_INFO_FLAGS     LinkInfoFlags;
    UINT32                      VolumeIDOffset;
    UINT32                      LocalBasePathOffset;
    UINT32                      CommonNetworkRelativeLinkOffset;
    UINT32                      CommonPathSuffixOffset;
    //Optional
    UINT32                      LocalBasePathOffsetUnicode;
    UINT32                      CommonPathSuffixOffsetUnicode;  
}SHLLING_LINK_INFO, * PSHLLING_LINK_INFO;

#define SHLLINK_DRIVE_TYPE_UNKOWN           0x00000000
#define SHLLINK_DRIVE_TYPE_NO_ROOT_DIR      0x00000001
#define SHLLINK_DRIVE_TYPE_REMOVABLE        0x00000002
#define SHLLINK_DRIVE_TYPE_FIXED            0x00000003
#define SHLLINK_DRIVE_TYPE_REMOTE           0x00000004
#define SHLLINK_DRIVE_TYPE_CDROM            0x00000005
#define SHLLINK_DRIVE_TYPE_RAMDISK          0x00000006

#define SHLLIONK_IGNORE_VOLUME_LABEL_OFFSET_UNICODE 0x14

typedef struct PACKED _SHLLINK_VOLUME_ID{
    UINT32  VolumeIDSize;
    UINT32  DriveType;
    UINT32  DriveSerialNumber;
    UINT32  VolumeLabelOffset;
    UINT8   Data[]; //Data[0] is VolumeLabelOffsetUnicode
}SHLLINK_VOLUME_ID, * PSHLLINK_VOLUME_ID;

typedef struct _SHLLINK_FILE_CONTEXT{
    PFILE_ATTRIBUTES_FLAGS      FileFlags;
    PSHELL_LINK_HEADER          ShellLinkHeader;
    PSHLLINK_TARGET_ID_LIST     IdList;
    PSHLLING_LINK_INFO          LinkInfo;
    PSHLLINK_VOLUME_ID          VolumeIDRecord;
}SHLLINK_FILE_CONTEXT, * PSHLLINK_FILE_CONTEXT;

typedef struct _SHLLINK_COMPILER_CONTEXT{
    string                  ShortcutPathAndFile;
    string                  OutputPathAndFile;
    SHLLINK_FILE_CONTEXT    ShellLinkFileContext;
}SHLLINK_COMPILER_CONTEXT, * PSHLLINK_COMPILER_CONTEXT;

#endif