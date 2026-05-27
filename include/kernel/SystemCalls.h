
#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint.h>
#include <cstdlib.h>

//Original Great 18
#define LOUVMALLOC                              0
#define LOUCREATETHREAD                         1
#define LOUEXITDOSMODE                          2
#define LOULOADFILE                             3
#define LOUPRINTCALL                            4
#define LOULOADBITMAP                           5
#define LOUADDATOMEX                            6 
#define LOUDRSDGETPLANEINFO                     7
#define LOUDRSDCREATECLIP                       8
#define LOUDRSDSYNCSCREEN                       10
#define LOUUPDTATECLIP                          11
#define LOUCREATEIPCMANAGER                     12
#define LOUFREEGENERICHEAP                      13
#define LOUGETRTCDATA                           14
#define LOUREGISTERCALLBACK                     15
#define LOUDPDATESHADOWCLIP                     16
#define LOUVFREE                                17
#define LOUDESTROYTHREAD                        18
#define LOULOADLIBRARYA                         19
#define LOULOADLIBRARYW                         20
#define LOULOADLIBRARYEXA                       21
#define LOULOADLIBRARYEXW                       22
#define LOUALLOCHEAPGENERICEX                   23
#define LOUGETTHREADID                          24
#define LOUVIRTUALALLOCUSER                     25
#define LOUAGLFN                                26
#define LOUCLOSEFILE                            27
#define LOUALPCSETINFORMATION                   28
#define LOUINITIOCTLTABLE                       29
#define LOUDRSDUPDATECLIPSUBSTATE               30
#define LOUDRSDUPDATESHADOWCLIPSUBSTATE         31
#define LOUDRSDSETPLANEINFO                     32
#define LOUSHUTDOWN                             33
#define LOUYEILDEXE                             34
#define LOUCREATESECTIONEX                      35
#define LOUIOCTLCALLFUNC                        36
#define LOUCREATEACCESSTOKEN                    37
#define LOUCREATEPROCESS                        38
#define LOUGETPROCNAME                          39
#define LOUGETCURRENTPROCHANDLE                 40
#define LOUPUTCURRENTPROCHANDLE                 41
#define LOUALLOCVMMBUFF64                       42
#define LOURAISEEXCEPTION                       43
#define LOUGETPROCFSI                           44
#define LOUGETIPCMESSAGE                        45
#define LOUCREATEIPCMESSAGE                     46
#define LOUSENDIPCMESSAGE                       47
#define LOUDESTROYIPCMESSAGE                    48
#define LOUREGISTERGLOBALOBJECT                 49
#define LOUUNREGISTERGLOBALOBJECT               50
#define LOUGETGLOBALOBJECT                      51

//TODO Move The following to IOCTL 
/*#define LOU_KE_ISCSI_CREATE_SESSION
#define LOU_KE_ISCSI_DESTROY_SESSION
#define LOU_KE_ISCSI_CREATE_CONNECTION
#define LOU_KE_ISCSI_DESTORY_CONNECTION
#define LOU_KE_ISCSI_BIND_CONNECTION
#define LOU_KE_ISCSI_SET_PARAMETER
#define LOU_KE_ISCSI_START_CONNECTION
#define LOU_KE_ISCSI_STOP_CONNECTION
#define LOU_KE_ISCSI_SEND_PDU
#define LOU_KE_ISCSI_GET_STATUS
#define LOU_KE_ISCSI_GET_PARAMETER
#define LOU_KE_ISCSI_TRANSPORT_EP_CONNECT
#define LOU_KE_ISCSI_TRANSPORT_EP_POLL
#define LOU_KE_ISCSI_TRANSPORT_EP_DISCONNECT
#define LOU_KE_ISCSI_TARGET_DISCOVER
#define LOU_KE_ISCSI_SET_HOST_PARAMETER
#define LOU_KE_ISCSI_UNBIND_SESSION
#define LOU_KE_ISCSI_CREATE_BOUND_SESSION
#define 
#define LOU_KE_ISCSI_PATH_UPDATE
#define LOU_KE_ISCSI_SET_INTERFACE_PARAMETERS
#define LOU_KE_ISCSI_PING
#define LOU_KE_ISCSI_GET_CHAP
#define LOU_KE_ISCSI_DELETE_CHAP
#define LOU_KE_ISCSI_SET_FLASHNODE_PRAMETERS
#define LOU_KE_ISCSI_NEW_FLASHNODE
#define LOU_KE_ISCSI_DELETE_FLASHNODE
#define LOU_KE_ISCSI_LOGIN_FLASHNODE
#define LOU_KE_ISCSI_LOGOUT_FLASHNODE
#define LOU_KE_ISCSI_LOGOUT_FLASHNODE_SID
#define LOU_KE_ISCSI_SET_CHAP
#define LOU_KE_ISCSI_GET_HOST_STATUS
#define LOU_KE_ISCSI_DESTROY_SESSION_ASYNC

#define LOU_KE_CDROM_PAUSE_AUDIO
#define LOU_KE_CDROM_RESUME_AUDIO
#define LOU_KE_CDROM_PLAY_MSF
#define LOU_KE_CDROM_PLAY_TRACK
#define LOU_KE_CDROM_READ_TOC_HEADER
#define LOU_KE_CDROM_READ_TOC_ENTRY
#define LOU_KE_CDROM_STOP
#define LOU_KE_CDROM_START
#define LOU_KE_CDROM_EJECT
#define LOU_KE_CDROM_VOLUME_CONTROL
#define LOU_KE_CDROM_SUB_CHANNEL
#define LOU_KE_CDROM_READ_MODE2  
#define LOU_KE_CDROM_READ_MODE1
#define LOU_KE_CDROM_READ_AUDIO
#define LOU_KE_CDROM_EJECT_SW
#define LOU_KE_CDROM_MULTI_SESSION
#define LOU_KE_CDROM_GET_MCN
#define LOU_KE_CDROM_GET_UPC
#define LOU_KE_CDROM_RESET
#define LOU_KE_CDROM_VOLUME_READ
#define LOU_KE_CDROM_READ_RAW_MODE
#define LOU_KE_CDROM_READ_COOKED
#define LOU_KE_CDROM_SEEK
#define LOU_KE_CDROM_PLAY_BLOCK
#define LOU_KE_CDROM_READ_ALL
#define LOU_KE_CDROM_GET_SPINDOWN
#define LOU_KE_CDROM_SET_SPINDOWN
#define LOU_KE_CDROM_CLOSE_TRAY
#define LOU_KE_CDROM_SET_OPTIONS
#define LOU_KE_CDROM_CLEAR_OPTIONS
#define LOU_KE_CDROM_SELECT_SPEED
#define LOU_KE_CDROM_SELECT_DISKS
#define LOU_KE_CDROM_MEDIA_CHANGED
#define LOU_KE_CDROM_DRIVE_STATUS
#define LOU_KE_CDROM_DISC_STATUS
#define LOU_KE_CDROM_GET_SLOTS
#define LOU_KE_CDROM_LOCK_DOOR
#define LOU_KE_CDROM_DEBUG
#define LOU_KE_CDROM_GET_CAPABILITIES
#define LOU_KE_CDROM_AUDIO_BUFFER_SIZE
#define LOU_KE_CDROM_DVD_READ_STRUCTURE
#define LOU_KE_CDROM_DVD_WRITE_STRUCTURE
#define LOU_KE_DVD_AUTHENTICATION
#define LOU_KE_CDROM_SEND_PACKET
#define LOU_KE_CDROM_NEXT_WRITEABLE
#define LOU_KE_CDROM_LAST_WRITTEN
#define LOU_KE_CDROM_TIMED_MEDIA_CHANGE*/

#define WINECALL                                1   
#define WINECALL_FASTFAIL                       1

#ifndef _USER_MODE_CODE_

static inline void LouCALL(
    UNUSED uint64_t Call,
    UNUSED uint64_t Data,
    UNUSED uint64_t SystemEmulation
){
    asm("INT $0x80");
}

void LouKeMakeKCall(
    UINT64  Call,
    UINT64  Data,
    UINT64  SystemEmulation
);
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

#ifdef __cplusplus
}
#endif
#endif