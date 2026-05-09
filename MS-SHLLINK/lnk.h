#ifndef _LNK_COMPILER_H
#define _LNK_COMPILER_H

#include <kernel/loustatus.h>

#define PACKED __attribute__((packed))

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef uint8_t     UINT8;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;

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
        UINT32  HasLinkTargetIDList     :   1;
        UINT32  HasLinkInfo             :   1;
        UINT32  HasName                 :   1;
        UINT32  HasRelativePath         :   1;
        UINT32  HasWorkingDirectory     :   1;
        UINT32  HasArguments            :   1;
        UINT32  HasIconLocation         :   1;
        UINT32  IsUnicode               :   1;
        UINT32  ForceNoLinkInfo         :   1;
        UINT32  HasExpString            :   1;
        UINT32  RunInSeperateProcess    :   1;
        UINT32  Unused1                 :   1;
        UINT32  HasDarwinID             :   1;
        UINT32  RunAsUser               :   1;
        UINT32  HasExpIcon              :   1;
        UINT32  NoPidAlias              :   1;
        UINT32  Unused2                 :   1;
        UINT32  RunWithShimLayer        :   1;
        UINT32  ForceNoLinkTrack        :   1;
        UINT32  EnableTargetMetaData    :   1;
        UINT32  DisableLinkPathTracking :   1;
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
        UINT32  Raw;
    };
    UINT32      Uint32;
}FILE_ATTRIBUTES_FLAGS, * PFILE_ATTRIBUTES_FLAGS;

#define MSSHLLINK_SW_SHOW_NORMAL        0x00000001
#define MSSHLLINK_SW_SHOW_MAXIMIZED     0x00000003
#define MSSHLLINK_SW_SHOW_MINNOACTIVE   0x00000007

typedef union PACKED _HOT_KEY_FLAGS{
    struct {
        UINT16  Raw;
    };
    UINT16      Uint16;
}HOT_KEY_FLAGS, * PHOT_KEY_FLAGS;

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


#endif