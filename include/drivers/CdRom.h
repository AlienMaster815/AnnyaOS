#ifndef _CD_ROM_H
#define _CD_ROM_H



#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

#define CDROM_PACKET_LENGTH 12
#define CGC_DATA_UNKOWN     0
#define CGC_DATA_WRITE      1
#define CGC_DATA_READ       2
#define CGC_DATA_NONE       3
#define MEDIA_HAS_CHANGED_FLAG 1
#define CD_RUNTIME_MINUTES          74
#define CD_RUNTIME_SECONDS          60
#define CD_FRAMES_PER_SECOND        75
#define CD_SYNCRONIZATION_SIZE      12
#define CD_MSF_OFFSET               150
#define CD_CHANK_SIZE               24
#define CD_CHUNK_COUNT              98
#define CD_SUB_FRAMESIZE            96
#define CD_HEAD_SIZE                4
#define CD_SUB_HEAD_SIZE            8
#define CD_EDC_SIZE                 4
#define CD_ZERO_SIZE                8
#define CD_ECC_SIZE                 276
#define CD_FRAMESIZE                2048
#define CD_RAW_FRAME_SIZE           2352
#define CD_MAX_RAW_FRAME_SIZE       2646
#define CD_FRAME_SIZE_RAW1          2340
#define CD_FRAME_SIZE_RAW0          2336
#define CD_XA_HEAD                  (CD_HEAD_SIZE + CD_SUB_HEAD_SIZE)
#define CD_XA_TAIL                  (CD_EDC_SIZE + CD_ECC_SIZE)
#define CD_XA_SYNCRONIZATION_HEAD   (CD_HEAD_SIZE + CD_XA_HEAD)
#define CDROM_LBA                   0x01
#define CDROM_MSF_CALL              0x02
#define CDROM_DATA_TRACK            0x04
#define CDROM_LEADOUT               0xAA
#define CDROM_AUDIO_INVALID         0x00
#define CDROM_AUDIO_PLAY            0x11
#define CDROM_AUDIO_PAUSED          0x12
#define CDROM_AUDIO_COMPLETED       0x13
#define CDROM_AUDIO_ERROR           0x14
#define CDROM_AUDIO_NO_STATUS       0x15
#define CDC_CLOSE_TRAY              0x01
#define CDC_OPEN_TRAY               0x02
#define CDC_LOCK                    0x04
#define CDC_SELECT_SPEED            0x08
#define CDC_SELECT_DISC             0x10
#define CDC_MULTI_SESSION           0x20
#define CDC_MCN                     0x40
#define CDC_MEDIA_CHANGED           0x80
#define CDC_PLAY_AUDIO              0x100
#define CDC_RESET                   0x200
#define CDC_DRIVE_STATUS            0x800
#define CDC_GENERIC_PACKET          0x1000
#define CDC_CD_R                    0x2000
#define CDC_CD_RW                   0x4000
#define CDC_DVD                     0x8000
#define CDC_DVD_R                   0x10000
#define CDC_DVD_RAM                 0x20000
#define CDC_MO_DRIVE                0x40000
#define CDC_WRM                     0x80000
#define CDC_WRM_W                   0x100000
#define CDC_RAM                     0x200000
#define CDS_NO_INFORMATION          0x00
#define CDS_NO_DISC                 0x01
#define CDS_TRAY_OPEN               0x02
#define CDS_DRIVE_NOT_READY         0x03
#define CDS_DISC_OK                 0x04
#define CDS_AUDION                  100
#define CDS_DATA1                   101
#define CDS_DATA2                   102
#define CDS_XA2_1                   103
#define CDS_XA2_2                   104
#define CDS_MIXED                   105
#define CD0_AUTO_CLOSE              0x01
#define CD0_AUTO_EJECT              0x02
#define CD0_USE_FFLAGS              0x04
#define CD0_LOCK                    0x08
#define CD0_CHECK_TYPE              0x10
#define CDSL_NONE                   0xFFFFFFFF-1
#define CDSL_CURRENT                0xFFFFFFFF
#define CD_PART_MAX                 64
#define CD_PART_MASK                63
#define GP_COMMAND_BLANK            0xA1
#define GP_COMMAND_CLOSE_TRACK      0x5B
#define GP_COMMAND_FLUSH_CACHE      0x35
#define GP_COMMAND_FORMAT_UNIT      0x04
#define GP_COMMAND_GET_CONFIG       0x46
#define GP_COMMAND_GET_ESN          0x4A
#define GP_GET_PERFORMACE           0xAC
#define GP_COMMAND_INQUIRY          0x12
#define GP_COMMAND_LOAD_UNLOAD      0xA6
#define GP_COMMAND_MECHANISM_STATUS 0xBD
#define GP_COMMAND_MODE_SLECT10     0x55
#define GP_COMMAND_MODE_SENECE10    0x5A
#define GP_COMMAND_PAUSE_RESUME     0x4B
#define GP_COMMAND_PLAY_AUDIO10     0x45
#define GP_COMMAND_PLAY_AUDIO_MSF   0x47
#define GP_COMMAND_PLAY_AUDIO_TI    0x48
#define GP_COMMAND_PLAY_CD          0xBC
#define GP_COMMAND_PAMR             0x1E
#define GP_COMMAND_READ10           0x28
#define GP_COMMAND_READ12           0xA8
#define GP_COMMAND_READ_BUFFER_CAP  0x5C
#define GP_COMMAND_READ_CDVD_CAP    0x25
#define GP_COMMAND_READ_CD          0xBE
#define GP_COMMAND_READ_CD_MSF      0xB9
#define GP_COMMAND_READ_DISC_INFO   0x51
#define GP_COMMAND_DVD_STRUCTURE    0xAD
#define GP_COMMAND_FORMAT_CAP       0x23
#define GP_COMMAND_HEADER           0x44
#define GP_COMMAND_READ_TRK_RZ_INFO 0x52
#define GP_COMMAND_READ_SUB_CHANNEL 0x42
#define GP_COMMAND_READ_TOC_PMA_ATIP 0x43
#define GP_COMMAND_REPAIR_RZ_TRACK  0x43
#define GP_COMMAND_REPORT_KEY       0xA4
#define GP_COMMAND_REQUEST_SENCE    0x03
#define GP_COMMAND_RESERVE_RZ_TRACK 0x53
#define GP_COMMAND_SEND_CUE_SHEET   0x4D
#define GP_COMMAND_SCAN             0xBA
#define GP_COMMAND_SEEK             0x2B
#define GP_COMMAND_SEND_DVD_STRUCT  0xBF
#define GP_COMMAND_SEND_EVENT       0xA2
#define GP_COMMAND_SEND_KEY         0xA3
#define GP_COMMAND_SEND_OPC         0x54
#define GP_COMMAND_SET_READ_AHEAD   0xA7
#define GP_COMMAND_SET_STREAMING    0xB6
#define GP_COMMAND_START_STOP_UNIT  0x1B
#define GP_COMMAND_STOP_PLAY_SCAN   0x4E
#define GP_COMMAND_TEST_UNIT_READY  0x00
#define GP_COMMAND_VERIFY10         0x2F
#define GP_COMMAND_WRITE10          0x2A
#define GP_COMMAND_WRITE12          0xAA
#define GP_COMMAND_WR_AND_VER10     0x2E
#define GP_COMMAND_WRITE_BUFFER     0x3B
#define GP_COMMAND_SET_SPEED        0xBB
#define GP_COMMAND_SET_PLAY_AUDIO_TI 0x48
#define GP_COMMAND_GET_MEDIA_STATUS 0xDA
#define GP_MODE_VENDOR_PAGE         0x00
#define GP_MODE_WR_ERROR_PAGE       0x01
#define GP_MODE_WRITE_PARAMS_PAGE   0x05
#define GP_MODE_WCACHING_PAGE       0x08
#define GP_MODE_AUDIO_CONTROL_PAGE  0x0E
#define GP_MODE_POWER_PAGE          0x1A
#define GP_MODE_FAULT_FAIL_PAGE     0x1C
#define GP_MODE_TO_PROTECT_PAGE     0x1D
#define GP_MODE_CAPABILITIES_PAGE   0x2A
#define GP_MODE_ALL_PAGES           0x3F
#define GP_MODE_CDROM_PAGE          0x0D
#define DVD_STRUCTURE_PHYSICAL      0x00
#define DVD_STRUCTURE_COPYRIGHT     0x01
#define DVD_STRUCTURE_DISC_KEY      0x02
#define DVD_STRUCTURE_BCA           0x03
#define DVD_STRUCTURE_MANUFATURE    0x04
#define DVD_LAYERS                      4
#define DVD_LU_SEND_AGID_OP             0
#define DVD_HOST_SEND_CHALLENGE_OP      1
#define DVD_LU_SEND_KEY1                2
#define DVD_LU_SEND_CHALLENGE_OP        3
#define DVD_HOST_SEND_KEY2              4
#define DVD_AUTHENT_ESTABLISHED         5
#define DVD_AUTHENT_FALIED              6
#define DVD_LU_SEND_TITLE_KEY_OP        7
#define DVD_LU_SEND_ASF_OP              8
#define DVD_INVALIDATE_AGID             9
#define DVD_LU_SEND_RPC_STATE_OP        10
#define DVD_HOST_SEND_RPC_STATE_OP      11
#define DVD_CPM_NO_COPYRIGHT            0
#define DVD_CPM_COPYRIGHTED             1
#define DVD_CP_SECOND_NONE              0
#define DVD_CP_SECOND_EXIST             1
#define DVD_CGMS_UNRESTRICTED           0
#define DVD_CGMS_SINGLE                 2
#define DVD_CGMS_RESTRICTED             3
#define CD_FEATURE_PROFILE_RWRT         0x20
#define CD_FEATURE_PROFILE_HWDM         0x24
#define CD_FEATURE_PROFILE_MRW          0x28
#define CD_MEDIA_STATUS_MRW_NOTMRW                      0
#define CD_MEDIA_STATUS_MRW_BGF_FORMAT_INACTIVE         1
#define CD_MEDIA_STATUS_MRW_BGF_FORMAT_ACTIVE           2
#define CD_MEDIA_STATUS_MRW_BGF_FORMAT_COMPLETE         3
#define MRW_LBA_DMA                                     0
#define MRW_LBA_GAA                                     1
#define MRW_MODE_PC_PRE1                                0x2C
#define MRW_MODE_PC                                     0x03


//system call structures
typedef struct _CDROM_MSF0{
    uint8_t Minutes;
    uint8_t Seconds;
    uint8_t Frame;
}CDROM_MSF0, * PCDROM_MSF0;

typedef union _CDROM_ADDRESS{
    CDROM_MSF0  MsfHeader;
    int         Lba; 
}CDROM_ADDRESS, * PCDROM_ADDRESS;

typedef struct _CDROM_MSF{
    uint8_t     CdMsfMinute0;
    uint8_t     CdMsfSeconds0;
    uint8_t     CdMsfFrame0;
    uint8_t     CdMsfMinute1;
    uint8_t     CdMsfSeconds1;
    uint8_t     CdMsfFrame1;
}CDROM_MSF, * PCDROM_MSF;

typedef struct _CDROM_TI{
    uint8_t     CdTiTrack0;
    uint8_t     CdTiIndex0;
    uint8_t     CdTiTrack1;
    uint8_t     CdTiIndex1;
}CDROM_TI, * PCDROM_TI;

typedef struct _CDROM_TO_CHDR{
    uint8_t     CdThTrack0;
    uint8_t     CdThTrack1;
}CDROM_TO_CHDR, * PCDROM_TO_CHDR;

typedef struct _CDROM_VOLCTL{
    uint8_t     Channel0;
    uint8_t     Channel1;
    uint8_t     Channel2;
    uint8_t     Channel3;
}CDROM_VOLCTL, * PCDROM_VOLCTL;

typedef struct _CDROM_SUBCHNL{
    uint8_t         CdScFormat;
    uint8_t         CdScAudioStatus;
    uint8_t         CdScAddress;
    uint8_t         CdScControll;
    uint8_t         CdScTrack;
    uint8_t         CdScIndex;
    CDROM_ADDRESS   CdScAbstractAddress;
    CDROM_ADDRESS   CdScRelativeAddress;
}CDROM_SUBCHNL, * PCDROM_SUBCHNL;

typedef struct _CDROM_TOCENTRY{
    uint8_t         CdTeTrack;
    uint8_t         CdTeADR      : 4;
    uint8_t         CdTeControll : 4;
    uint8_t         CdTeFormat;
    CDROM_ADDRESS   CdTeAddress;
    uint8_t         CdTeDataMode;
}CDROM_TOCENTRY, * PCDROM_TOCENTRY;

typedef struct _CDROM_READ{
    int             CdReadLba;
    string          CdReadBufferAddress;
    int             CdReadBufferLength;
}CDROM_READ, * PCDROM_READ;

typedef struct _CDROM_READ_AUDIO{
    CDROM_ADDRESS   Address;
    int             FrameCount;
    uint8_t*        Buffer;
}CDROM_READ_AUDIO, * PCDROM_READ_AUDIO;

typedef struct _CDROM_MULTISESSION{
    CDROM_ADDRESS   Address;
    uint8_t         XAFlags;
    uint8_t         AddressFormat;
}CDROM_MULTISESSION, * PCDROM_MULTISESSION;

typedef struct _CDROM_MCN{
    uint8_t McnData[14];
}CDROM_MCN, * PCDROM_MCN;

typedef struct _CDROM_BLOCK{
    uint64_t From;
    uint16_t Length;
}CDROM_BLOCK, * PCDROM_BLOCK;

typedef struct _CDROM_GENERIC_COMMAND{
    uint8_t         sCdCommand[CDROM_PACKET_LENGTH];
    uint8_t*        DataBuffer;
    uint32_t        BufferLength;
    LOUSTATUS       Status;
    LOUQ_REQUEST    SenceRequest;
    uint8_t         DataDirection;
    int             Quiet;
    int             Timeout;
    union{
        void*       Reserved[1];
        void*       UnusedData;
    };
}CDROM_GENERIC_COMMAND, * PCDROM_GENERIC_COMMAND;

typedef struct _CDROM_TIMED_MEDIA_CHANGE_INFO{
    int64_t         LastMediaChange;
    uint64_t        MediaFlags;
}CDROM_TIMED_MEDIA_CHANGE_INFO, * PCDROM_TIMED_MEDIA_CHANGE_INFO;

typedef struct _DVD_LAYER{
    uint8_t     BookVersion         :   4;
    uint8_t     BookType            :   4;
    uint8_t     MinuteRate          :   4;
    uint8_t     DiscSize            :   4;
    uint8_t     LayerType           :   4;
    uint8_t     TrackPath           :   1;
    uint8_t     LayerCount          :   2;
    uint8_t     TrackDensity        :   4;
    uint8_t     LinearDestiny       :   4;
    uint8_t     Bca                 :   1;
    uint32_t    StartSector;
    uint32_t    EndSector;
    uint32_t    EndSectorL0;
}DVD_LAYER, * PDVD_LAYER;

typedef struct _DVD_PHYSICAL{
    uint8_t     Type;
    uint8_t     LayerIdentification;
    DVD_LAYER   DvdLayers[DVD_LAYERS];
}DVD_PHYSICAL, * PDVD_PHYSICAL;

typedef struct _DVD_COPYRIGHT{
    uint8_t     Type;
    uint8_t     LayerIdentification;
    uint8_t     Cpst;
    uint8_t     Rmi;
}DVD_COPYRIGHT, * PDVD_COPYRIGHT;

typedef struct _DVD_DISC_KEY{
    uint8_t     Type;
    uint8_t     Agid : 2;
    uint8_t     KeyValue[2048];     
}DVD_DISC_KEY, * PDVD_DISC_KEY;

typedef struct _DVD_BCA{
    uint8_t     Type;
    int         Length;
    uint8_t     Value[2048];
}DVD_BCA, * PDVD_BCA;

typedef struct _DVD_MANUFACTURER{
    uint8_t     Type;
    uint8_t     LayerIdentification;
    int         Length;
    uint8_t     Value[2048];
}DVD_MANUFACTURER, * PDVD_MANUFACTURER;

typedef union _DVD_IO_STACK_PACKET{
    uint8_t             IoPacketType;
    DVD_PHYSICAL        PhysicalPacket;
    DVD_COPYRIGHT       CopyrightPacket;
    DVD_DISC_KEY        DiscKeyPacket;
    DVD_BCA             BcaPacket;
    DVD_MANUFACTURER    ManufacturerPacket;
}DVD_IO_STACK_PACKET, * PDVD_IO_STACK_PACKET;

typedef uint8_t DVD_KEY[5];
typedef uint8_t DVD_CHALLENGE[5];

typedef struct _DVD_LU_SEND_AGID{
    uint8_t     Type;
    uint8_t     Agid : 2;
}DVD_LU_SEND_AGID, * PDVD_LU_SEND_AGID;

typedef struct _DVD_HOST_SEND_CHALLENGE{
    uint8_t         Type;
    uint8_t         Agid : 2;
    DVD_CHALLENGE   Challenge;
}DVD_HOST_SEND_CHALLENGE, * PDVD_HOST_SEND_CHALLENGE;

typedef struct _DVD_SEND_KEY{
    uint8_t         Type;
    uint8_t         Agid : 2;
    DVD_KEY         DvdKey;
}DVD_SEND_KEY, * PDVD_SEND_KEY;

typedef struct _DVD_LU_SEND_CHALLENGE{
    uint8_t         Type;
    uint8_t         Agid : 2;
    DVD_CHALLENGE   DvdChallenge;
}DVD_LU_SEND_CHALLENGE, * PDVD_LU_SEND_CHALLENGE;

typedef struct _DVD_LU_SEND_TITLE_KEY{
    uint8_t         Type;
    uint8_t         Agid : 2;
    DVD_KEY         DvdTitleKey;
    uint8_t         Cpm : 1;
    uint8_t         CpSecond : 1;
    uint8_t         Cgms : 2;
}DVD_LU_SEND_TITLE_KEY, * PDVD_LU_SEND_TITLE_KEY;

typedef struct _DVD_LU_SEND_ASF{
    uint8_t         Type;
    uint8_t         Agid : 2;
    uint8_t         Asf  : 1; 
}DVD_LU_SEND_ASF, * PDVD_LU_SEND_ASF;

typedef struct _DVD_HOST_SEND_RPC_STATE{
    uint8_t         Type;
    uint8_t         Pdrc;
}DVD_HOST_SEND_RPC_STATE, * PDVD_HOST_SEND_RPC_STATE;

typedef struct _DVD_LU_SEND_RPC_STATE{
    uint8_t         Type : 2;
    uint8_t         Vra : 3;
    uint8_t         Ucca : 3;
    uint8_t         RegionBits;
    uint8_t         RpcScheme;
}DVD_LU_SEND_RPC_STATE, * PDVD_LU_SEND_RPC_STATE;

typedef union _DVD_AUTHENT_INFO_IO_PACKET{
    uint8_t                         IoOperationType;
    DVD_LU_SEND_AGID                LSA;
    DVD_HOST_SEND_CHALLENGE         HSC;
    DVD_SEND_KEY                    LSK;
    DVD_LU_SEND_CHALLENGE           LSC;
    DVD_SEND_KEY                    HSK;
    DVD_LU_SEND_CHALLENGE           LSTK;
    DVD_LU_SEND_ASF                 LSASF;
    DVD_HOST_SEND_RPC_STATE         HRPCS;
    DVD_LU_SEND_RPC_STATE           LRPCS;
}DVD_AUTHENT_INFO_IO_PACKET, * PDVD_AUTHENT_INFO_IO_PACKET;

//Im Sick with 103 fever And Im Going To Use 
//Comments Here for my own sanity
typedef struct _SENCE_REQUEST{
    //Byte 1
    uint8_t ErrorCode   : 7;
    uint8_t ValidBit    : 1;
    //Byte 2
    uint8_t SegmentNumber;
    //Byte 3
    uint8_t SenceKey    : 4;
    uint8_t Reserve2    : 1;//Reserve 2 is first due to hardware design
    uint8_t ILI         : 1;
    uint8_t Reserve1;
    //Byte 4 to 8
    uint8_t Information[4];
    //Byte 9
    uint8_t AddSenseLength;
    //Byte 10 to 14
    uint8_t CommandInformation[4];
    //Byte 15
    uint8_t Asc;
    //Byte 16
    uint8_t Ascq;
    //Byte 17
    uint8_t Fruc;
    //Byte 18 to 20
    uint8_t Sks[3];
    //Im not doing the math here
    uint8_t Asb[46];
}SENCE_REQUEST, * PSENCE_REQUEST;

typedef struct _MRW_FEATURE_DESCRIPTOR{
    //Byte 1 and 2 Big Endian
    uint16_t        FeatureCode;
    //Byte 3
    uint8_t         CurrBit                 : 1;
    uint8_t         PersistantBit           : 1;
    uint8_t         FeatureVersionNibble    : 4;
    uint8_t         Reserved1               : 2;
    //Byte 4
    uint8_t         AddLength;
    //Byte 5
    uint8_t         WriteBit                : 1;
    uint8_t         Reserved2               : 7;
    //Byte 6
    uint8_t         Reserved3;        
    uint8_t         Reserved4;        
    uint8_t         Reserved5;        
}MRW_FEATURE_DESCRIPTOR, * PMRW_FEATURE_DESCRIPTOR;



#ifdef __cplusplus
}
#endif
#endif //_CD_ROM_H