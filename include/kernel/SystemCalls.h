
#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#ifndef _KERNEL_MODULE_
#ifndef _USER_MODE_CODE_
static inline void LouCALL(
    UNUSED uint64_t Call,
    UNUSED uint64_t Data,
    UNUSED uint64_t SystemEmulation
){
    asm("INT $0x80");
}
#ifdef __cplusplus
extern "C" {
#endif
void LouKeMakeKCall(
    UINT64  Call,
    UINT64  Data,
    UINT64  SystemEmulation
);
#ifdef __cplusplus
}
#endif
#else
#ifndef _LOUDLL_

__declspec(dllimport)
void LouCALL(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
);
#else 
void LouCALL(
    uint64_t Call,
    uint64_t Data,
    uint64_t SystemEmulation
);
#endif

#endif
#endif


#define LOUCALL_WIN64_EMU 1


//Original Great 18
#define LOUVMALLOC          0
#define LOUCREATETHREAD     1
#define LOUEXITDOSMODE      2
#define LOULOADFILE         3
#define LOUPRINTCALL        4
#define LOULOADBITMAP       5
#define LOUGLOBALMALLOC     6
#define LOUDRSDGETPLANEINFO 7
#define LOUDRSDCREATECLIP   8
#define LOUDRSDSYNCSCREEN   10
#define LOUUPDTATECLIP      11
#define LOUGLOBALFREE       12
#define LOUFREEGENERICHEAP  13
#define LOUGETRTCDATA       14
#define LOUREGISTERCALLBACK 15
#define LOUDPDATESHADOWCLIP 16
#define LOUVFREE            17
#define LOUDESTROYTHREAD    18

//User System Calls
#define LOU_KE_ISCSI_CREATE_SESSION             19
#define LOU_KE_ISCSI_DESTROY_SESSION            20
#define LOU_KE_ISCSI_CREATE_CONNECTION          21
#define LOU_KE_ISCSI_DESTORY_CONNECTION         22
#define LOU_KE_ISCSI_BIND_CONNECTION            23
#define LOU_KE_ISCSI_SET_PARAMETER              24
#define LOU_KE_ISCSI_START_CONNECTION           25
#define LOU_KE_ISCSI_STOP_CONNECTION            26
#define LOU_KE_ISCSI_SEND_PDU                   27
#define LOU_KE_ISCSI_GET_STATUS                 28
#define LOU_KE_ISCSI_GET_PARAMETER              29
#define LOU_KE_ISCSI_TRANSPORT_EP_CONNECT       30
#define LOU_KE_ISCSI_TRANSPORT_EP_POLL          31
#define LOU_KE_ISCSI_TRANSPORT_EP_DISCONNECT    32
#define LOU_KE_ISCSI_TARGET_DISCOVER            33
#define LOU_KE_ISCSI_SET_HOST_PARAMETER         34
#define LOU_KE_ISCSI_UNBIND_SESSION             35
#define LOU_KE_ISCSI_CREATE_BOUND_SESSION       36
#define LOU_KE_ISCSI_TRANSPORT_EP_CONNECTION_TH 37
#define LOU_KE_ISCSI_PATH_UPDATE                38
#define LOU_KE_ISCSI_SET_INTERFACE_PARAMETERS   39
#define LOU_KE_ISCSI_PING                       40
#define LOU_KE_ISCSI_GET_CHAP                   41
#define LOU_KE_ISCSI_DELETE_CHAP                42
#define LOU_KE_ISCSI_SET_FLASHNODE_PRAMETERS    43
#define LOU_KE_ISCSI_NEW_FLASHNODE              44
#define LOU_KE_ISCSI_DELETE_FLASHNODE           45
#define LOU_KE_ISCSI_LOGIN_FLASHNODE            46
#define LOU_KE_ISCSI_LOGOUT_FLASHNODE           47
#define LOU_KE_ISCSI_LOGOUT_FLASHNODE_SID       48
#define LOU_KE_ISCSI_SET_CHAP                   49
#define LOU_KE_ISCSI_GET_HOST_STATUS            50
#define LOU_KE_ISCSI_DESTROY_SESSION_ASYNC      51

#define LOU_KE_CDROM_PAUSE_AUDIO                52
#define LOU_KE_CDROM_RESUME_AUDIO               53
#define LOU_KE_CDROM_PLAY_MSF                   54
#define LOU_KE_CDROM_PLAY_TRACK                 55
#define LOU_KE_CDROM_READ_TOC_HEADER            56
#define LOU_KE_CDROM_READ_TOC_ENTRY             57
#define LOU_KE_CDROM_STOP                       58
#define LOU_KE_CDROM_START                      59
#define LOU_KE_CDROM_EJECT                      60
#define LOU_KE_CDROM_VOLUME_CONTROL             61
#define LOU_KE_CDROM_SUB_CHANNEL                62
#define LOU_KE_CDROM_READ_MODE2                 63  
#define LOU_KE_CDROM_READ_MODE1                 64
#define LOU_KE_CDROM_READ_AUDIO                 65
#define LOU_KE_CDROM_EJECT_SW                   66
#define LOU_KE_CDROM_MULTI_SESSION              67
#define LOU_KE_CDROM_GET_MCN                    68
#define LOU_KE_CDROM_GET_UPC                    69
#define LOU_KE_CDROM_RESET                      70
#define LOU_KE_CDROM_VOLUME_READ                71
#define LOU_KE_CDROM_READ_RAW_MODE              72
#define LOU_KE_CDROM_READ_COOKED                73
#define LOU_KE_CDROM_SEEK                       74
#define LOU_KE_CDROM_PLAY_BLOCK                 75
#define LOU_KE_CDROM_READ_ALL                   76
#define LOU_KE_CDROM_GET_SPINDOWN               77
#define LOU_KE_CDROM_SET_SPINDOWN               78
#define LOU_KE_CDROM_CLOSE_TRAY                 79
#define LOU_KE_CDROM_SET_OPTIONS                80
#define LOU_KE_CDROM_CLEAR_OPTIONS              81
#define LOU_KE_CDROM_SELECT_SPEED               82
#define LOU_KE_CDROM_SELECT_DISKS               83
#define LOU_KE_CDROM_MEDIA_CHANGED              84
#define LOU_KE_CDROM_DRIVE_STATUS               85
#define LOU_KE_CDROM_DISC_STATUS                86
#define LOU_KE_CDROM_GET_SLOTS                  87
#define LOU_KE_CDROM_LOCK_DOOR                  88
#define LOU_KE_CDROM_DEBUG                      89
#define LOU_KE_CDROM_GET_CAPABILITIES           90
#define LOU_KE_CDROM_AUDIO_BUFFER_SIZE          91
#define LOU_KE_CDROM_DVD_READ_STRUCTURE         92
#define LOU_KE_CDROM_DVD_WRITE_STRUCTURE        93
#define LOU_KE_DVD_AUTHENTICATION               94
#define LOU_KE_CDROM_SEND_PACKET                95
#define LOU_KE_CDROM_NEXT_WRITEABLE             96
#define LOU_KE_CDROM_LAST_WRITTEN               97
#define LOU_KE_CDROM_TIMED_MEDIA_CHANGE         98

#define LOULOADLIBRARYA                         99
#define LOULOADLIBRARYW                         100
#define LOULOADLIBRARYEXA                       101
#define LOULOADLIBRARYEXW                       102
#define LOUALLOCHEAPGENERICEX                   103
#define LOUGETTHREADID                          104
#define LOUVIRTUALALLOCUSER                     105
#define LOUAGLFN                                106
#define LOUCLOSEFILE                            107
#define LOUALPCSETINFORMATION                   108
#define LOUGETSYSTEMSTATE                       109
#define LOUDRSDUPDATECLIPSUBSTATE               110
#define LOUDRSDUPDATESHADOWCLIPSUBSTATE         111
#define LOUDRSDSETPLANEINFO                     112

#define WINECALL            1   
#define WINECALL_FASTFAIL   1
//Kernel SystemCalls

#include <stdbool.h>
#include <stdint.h>

typedef struct _MOUSE_STATE{
    int64_t     MouseX;
    int64_t     MouseY;
    bool        RightClick;
    bool        LeftClick;
    int64_t     Wheel;
    bool        WHeelButton;
}MOUSE_STATE, * PMOUSE_STATE;

typedef struct _SYSTEM_STATE_STACK{
    MOUSE_STATE     MouseState;
}SYSTEM_STATE_STACK, * PSYSTEM_STATE_STACK;

#endif
