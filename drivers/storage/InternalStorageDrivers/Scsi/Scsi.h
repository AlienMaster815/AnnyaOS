#include <LouDDK.h>
#include <Hal.h>

#pragma pack(push, 1)

//fixed length CBDs
typedef struct _CDB6BTag{
    uint8_t OperationCode;
    uint8_t MiscCDBInf_LbaHigh;
    uint8_t LbaMid;
    uint8_t LbaLow;
    uint8_t Length;
    uint8_t Control;
}CDB6B, * PCDB6B;

typedef struct _CDB10BTag{
    uint8_t         OperationCode;
    uint8_t         MiscNService;
    uint32_t        Lba;
    uint8_t         Misc2;
    uint16_t        Length;
    uint8_t         Control;
}CDB10B, * PCDB10B;

typedef struct _CDB12BTag{
    uint8_t         OperationCode;
    uint8_t         MiscNService;
    uint32_t        Lba;
    uint32_t        Length;
    uint8_t         Misc2;
    uint8_t         Control;
}CDB12B, * PCDB12B;

typedef struct _CDB16BTag{
    uint8_t         OperationCode;
    uint8_t         Misc;
    uint64_t        Lba;
    uint32_t        Length;
    uint8_t         Misc2;
    uint8_t         Control;
}CDB16B, * PCDB16B;

static inline 
LOUSTATUS InitializeCDB16(
    PCDB16B CDB,
    uint8_t OperationCode,
    uint8_t Misc,
    uint64_t Lba,
    uint32_t Length,
    uint8_t Misc2,
    uint8_t Control
){

    if(CDB == 0x00){
        return STATUS_INVALID_PARAMETER;
    }

    CDB->OperationCode = OperationCode;
    CDB->Misc    = Misc;
    CDB->Lba     = Lba;
    CDB->Misc2   = Misc2;
    CDB->Length  = Length;
    CDB->Control = Control;

    return STATUS_SUCCESS;

}

static inline
LOUSTATUS InitializeCDB12(
    PCDB12B CDB,
    uint8_t OperationCode,
    uint8_t Misc,
    uint8_t Service,
    uint32_t Lba,
    uint32_t Length,
    uint8_t Misc2,
    uint8_t Control
){

    if((CDB == 0x00) || (Service > 0x1F) || (Misc > 0x07)){
        return STATUS_INVALID_PARAMETER;
    }

    CDB->OperationCode = OperationCode;
    CDB->MiscNService = (Misc << 5) | Service;
    CDB->Lba     = Lba;
    CDB->Misc2   = Misc2;
    CDB->Length  = Length;
    CDB->Control = Control;

    return STATUS_SUCCESS;
}

static inline 
LOUSTATUS InitializeCDB10(
    PCDB10B CDB,
    uint8_t OperationCode,
    uint8_t Misc,
    uint8_t Service,
    uint32_t Lba,
    uint8_t Misc2,
    uint16_t Length,
    uint8_t Control
){

    if((CDB == 0x00) || (Service > 0x1F) || (Misc > 0x07)){
        return STATUS_INVALID_PARAMETER;
    }

    CDB->OperationCode = OperationCode;
    CDB->MiscNService = (Misc << 5) | Service;
    CDB->Lba     = Lba;
    CDB->Misc2   = Misc2;
    CDB->Length  = Length;
    CDB->Control = Control;

    return STATUS_SUCCESS;
}

static inline
LOUSTATUS InitializeCDB6(
    PCDB6B CDB, 
    uint8_t OperationCode,
    uint8_t Misc,
    uint32_t Lba,
    uint8_t Length,
    uint8_t Control
){

    if((Lba > 0x1FFFFF) || (CDB == 0x00) || (Misc > 0x07)){
        return STATUS_INVALID_PARAMETER;
    }

    CDB->OperationCode = OperationCode;
    CDB->MiscCDBInf_LbaHigh = ((Misc & 0x7) << 5) | ((Lba >> 16) & 0x1F); 
    CDB->LbaMid = (Lba >> 8) & 0xFF;
    CDB->LbaLow = Lba & 0xFF;
    CDB->Length = Length;
    CDB->Control = Control;

    return STATUS_SUCCESS;
}

//Variac length CBDs

typedef struct _VAR_CDB{
    uint8_t         OperationCode;
    uint8_t         Control;
    uint8_t         Misc[5];
    uint8_t         Length;
    uint16_t        Service;
    uint8_t         SASF[];
}VAR_CDB, * PVAR_CDB;   

typedef struct _VAR_CDB_LBA32{
    uint8_t         OperationCode;
    uint8_t         Control;
    uint8_t         Misc[5];
    uint8_t         CdbLength;
    uint16_t        Service;
    uint8_t         Misc_Dpo_Fua_Misc;
    uint8_t         Misc2;
    uint64_t        Lba;
    uint64_t        Misc3;
    uint32_t        Length;
}VAR_CDB_LBA32, * PVAR_CDB_LBA32;

//Operations
#define GROUP_CODE          (x)(x << 5)
#define COMMAND_CODE        (x)(x)

#define COMMAND_6_BYTE      0b000
#define COMMAND_10_BYTE     0b001
#define COMMAND_10_BYTE2    0b010
#define COMMAND_16_BYTE     0b100
#define COMMAND_12_BYTE     0b101
#define VEDOR_SPECIFIC_1    0b110
#define VEDOR_SPECIFIC_2    0b111

#define NACA_BIT    (1 << 2)

//Sense Data
#define RESPONCE_CODE_CURRENT_FIXED 0x70
#define RESPONCE_CODE_DEFERED_FIXED 0x71
#define RESPONCE_CODE_CURRENT_DESC  0x72
#define RESPONCE_CODE_DEFERED_DESC  0x73

typedef struct _DFSD{
    uint8_t         ResponceCode;
    uint8_t         SenceKey;
    uint8_t         AdditionalSenceCode;
    uint8_t         AdditionalSenceQualifier;
    uint8_t         Reserved[3];
    uint8_t         AdditionalSenceLength;
    uint8_t         SDDArray[];
}DFSD, * PDSFD;

#pragma pack(pop)