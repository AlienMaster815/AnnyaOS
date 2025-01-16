#include <LouDDK.h>
#include <Hal.h>
#include <atalib.h>

#define PIIX_IOCFG                      0x54
#define ICH5_PMR                        0x90
#define ICH5_PCS                        0x92
#define PIIX_SIDPR_BAR                  5
#define PIIX_SIDPR_LENGTH               16
#define PIIX_SIDPR_INDEX                0
#define PIIX_SIDPR_DATA                 4
#define PIIX_FLAG_CHECK_INTERRUPT       (1 << 28)
#define PIIX_FLAG_SIDPR                 (1 << 29)
#define PIIX_PATA_FLAGS                 ATA_FLAG_SLAVE_POSS
#define PIIX_SATA_FLAGS                 ATA_FLAG_SATA | PIIX_FLAG_CHECK_INTERRUPT
#define PIIX_FLAG_PIO16                 (1 << 30)
#define PIIX_80C_PRIMARY                (1 << 5) | (1 << 4)
#define PIIX_80C_SECONDARY              (1 << 7) | (1 << 6)
#define P0                              0
#define P1                              1
#define P2                              2
#define P3                              3
#define IDE                             -1
#define NA                              -2
#define RV                              -3
#define PIIX_AHCI_DEVICE                6
#define PIIX_HOST_BROKEN_SUSSPEND       (1 << 24)

#define PIIX_PATA_MWDMA         0
#define PIIX_PATA33             1
#define ICH_PATA66              2
#define ICH_PATA100             3
#define ICH_PATA100_NOWMDMA1    4
#define ICH5_SATA               5
#define ICH6_SATA               6
#define ICH6M_SATA              7
#define ICH8_SATA               8
#define ICH8_2PORT_SATA         9
#define ICH8M_APPLE_SATA        10
#define TOLAPAI_SATA            11
#define PIIX_PATA_VMW           12
#define ICH8_SATA_SNB           13
#define ICH8_2PORT_SATA_SNB     14
#define ICH8_2PORT_SATA_BYT     15


typedef struct _PIIX_MAP_DATA_BUFFER{
    uint32_t Mask;
    uint16_t Pe;
    int      Map[][4];
}PIIX_MAP_DATA_BUFFER, * PPIIX_MAP_DATA_BUFFER;

typedef struct _PIIX_HOST_PRIVATE_DATA{
    int*        map;
    uint32_t    SavedIocConfig;
    void*       SidPtr;
}PIIX_HOST_PRIVATE_DATA, * PPIIX_HOST_PRIVATE_DATA;

#define DEVICE_LIST_MEMBERS 3

typedef struct _PIIX_PORT_INFO{
    uint32_t    Flags;
    uint32_t    PioMask;
    uint32_t    MwdmaMask;
    uint32_t    UdmaMask;
    uintptr_t   Operations;
}PIIX_PORT_INFO, * PPIIX_PORT_INFO;

typedef struct _PIIX_DRIVER_DEVICE_LIST{
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t SubVendorID;
    uint16_t SubSystemID;
    uint8_t  BaseClass;
    uint8_t  SubClass;
    uint8_t  ProprietaryID;
}PIIX_DRIVER_DEVICE_LIST, * PPIIX_DRIVER_DEVICE_LIST;

typedef struct _PCI_PIIX_ENABLE_BITS{
    unsigned long EnableData[4];
}PCI_PIIX_ENABLE_BITS, * PPCI_PIIX_ENABLE_BITS;

static const PIIX_DRIVER_DEVICE_LIST PiixTable[DEVICE_LIST_MEMBERS]{
    {0x8086, 0x7010, ANY_PCI_ID,ANY_PCI_ID,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA_MWDMA},
    {0x8086, 0x7111, 0x15AD,0x1976,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA_VMW},
    {0x8086, 0x7111, ANY_PCI_ID,ANY_PCI_ID,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA33},
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich5MapDataBuffer = {
    .Mask   = 0x07,
    .Pe     = 0x03,
    .Map    = {
        {P0, NA, P1, NA},
        {P1, NA, P0, NA},
        {RV, RV, RV, RV},
        {RV, RV, RV, RV},
        {RV, RV, RV, RV},
        {P0, P1, IDE, IDE},
        {P1, P0, IDE, IDE},
        {IDE, IDE, P0, P1},
        {IDE, IDE, P1, P0},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich6MapDataBuffer = {
    .Mask   = 0x03,
    .Pe     = 0x0F,
    .Map    = {
        {P0, P2, P1,P3},
        {IDE, IDE, P1, P3},
        {P0, P2, IDE, IDE},
        {RV, RV, RV, RV},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich6MobileMapDataBuffer = {
    .Mask   = 0x03,
    .Pe     = 0x05,
    .Map    = {
        {P0, P2, NA, NA},
        {IDE, IDE, P1, P3},
        {P0, P2, IDE, IDE},
        {RV, RV, RV, RV},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich8MapDataBuffer = {
    .Mask   = 0x03,
    .Pe     = 0x0F,
    .Map = {
        {P0, P2, NA, NA},
        {IDE, IDE, P1, P3},
        {P0, P2, IDE, IDE},
        {RV, RV, RV, RV},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich82PortMapDataBuffer = {
    .Mask   = 0x03,
    .Pe     = 0x03,
    .Map    = {
        {P0, NA, NA, NA},
        {RV, RV, RV, RV},
        {P0, P2, IDE, IDE},
        {RV, RV ,RV, RV},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER Ich8MoblieAppleMabDataBuffer = {
    .Mask   = 0x03,
    .Pe     = 0x01,
    .Map    = {
        {P0, NA, NA, NA},
        {RV, RV, RV, RV},
        {P0, P2, IDE, IDE},
        {RV, RV, RV, RV},
    },
};

UNUSED static const PIIX_MAP_DATA_BUFFER TolapaiMapDataBuffer = { 
    .Mask   = 0x03,
    .Pe     = 0x03,
    .Map    ={
        {P0, NA, P1, NA},
        {RV, RV, RV, RV},
        {RV, RV, RV, RV},
        {RV, RV, RV, RV},
    },
};

UNUSED static PCI_PIIX_ENABLE_BITS Bits[]{
    {0x41, 1, 0x80, 0x80},
    {0x41, 1, 0x80, 0x80},
};

typedef struct _ICH_LAPTOP_DEVICE{
    uint16_t DeviceID;
    uint16_t SubVendorID;
    uint16_t SubDeviceID;
}ICH_LAPTOP_DEVICE, * PICH_LAPTOP_DEVICE;

#define SUPPORTED_ICH_LAPTOPS 15

static const ICH_LAPTOP_DEVICE IchLaptops[SUPPORTED_ICH_LAPTOPS] = {
    {0x27DF, 0x0005, 0x0280},
    {0x27DF, 0x1025, 0x0102},
    {0x27DF, 0x1025, 0x0110},
    {0x27DF, 0x1028, 0x02B0},
    {0x27DF, 0x1043, 0x1267},
    {0x27DF, 0x103C, 0x30A1},
    {0x27DF, 0x103C, 0x361A},
    {0x27DF, 0x1071, 0xD221},
    {0x27DF, 0x152D, 0x0778},
    {0x24CA, 0x1025, 0x0061},
    {0x24CA, 0x1025, 0x003D},
    {0x24CA, 0x10Cf, 0x11AB},
    {0x266F, 0x1025, 0x0066},
    {0x2653, 0x1043, 0x82D8},
    {0x27DF, 0x1043, 0x900E},
};

bool IsDeviceCompatible(PPCI_COMMON_CONFIG CommonConfig, uint8_t ProprietaryID){
    if(
        ((CommonConfig->Header.VendorID == PiixTable[ProprietaryID].VendorID) ||  (PiixTable[ProprietaryID].VendorID == ANY_PCI_ID)) &&
        ((CommonConfig->Header.DeviceID == PiixTable[ProprietaryID].DeviceID) ||  (PiixTable[ProprietaryID].DeviceID == ANY_PCI_ID)) &&
        ((CommonConfig->Header.u.type0.SubVendorID == PiixTable[ProprietaryID].SubVendorID) ||  (PiixTable[ProprietaryID].SubVendorID == ANY_PCI_ID)) &&
        ((CommonConfig->Header.u.type0.SubSystemID == PiixTable[ProprietaryID].SubSystemID) ||  (PiixTable[ProprietaryID].SubSystemID == ANY_PCI_ID)) &&
        ((CommonConfig->Header.BaseClass == PiixTable[ProprietaryID].BaseClass) ||  (PiixTable[ProprietaryID].BaseClass == ANY_PCI_CLASS)) &&
        ((CommonConfig->Header.SubClass == PiixTable[ProprietaryID].SubClass) ||  (PiixTable[ProprietaryID].SubClass == ANY_PCI_CLASS))
    )return true;

    return false;
}

uint8_t GetDeviceListNumber(PPCI_COMMON_CONFIG CommonConfig){

    for(uint8_t i = 0 ; i < DEVICE_LIST_MEMBERS; i++){
        if(IsDeviceCompatible(CommonConfig, i)){
            return i;
        }
    }

    return DEVICE_LIST_MEMBERS;
}

int PiixPortStart(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort){
    if(!(AtaPort->AtaFlags & PIIX_FLAG_PIO16)){
        AtaPort->AtaPFlags |= ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32_CHANGE;
    }
    return AtaBmdaPortStart(AtaPort);
}

int IchPataCableDetect(PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort){
    P_PCI_DEVICE_OBJECT PDEV = AtaPort->PDEV;
    PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig; 
    PPIIX_HOST_PRIVATE_DATA HostPrivate = (PPIIX_HOST_PRIVATE_DATA)AtaPort->PrivateExtendedData;
    uint8_t Mask, Index;
    for(Index = 0 ; Index < SUPPORTED_ICH_LAPTOPS; Index++){
        if(
            IchLaptops[Index].DeviceID == CommonConfig->Header.DeviceID && 
            IchLaptops[Index].SubVendorID == CommonConfig->Header.u.type0.SubVendorID && 
            IchLaptops[Index].SubDeviceID == CommonConfig->Header.u.type0.SubSystemID
        ){
            return ATA_CABLE_TYPE_PATA40_SHORT;
        }
    }
    Mask = AtaPort->PortNumber == 0 ? PIIX_80C_PRIMARY : PIIX_80C_SECONDARY;
    if((HostPrivate->SavedIocConfig & Mask) == 0){
        return ATA_CABLE_TYPE_PATA40;
    }
    return ATA_CABLE_TYPE_PATA80;
}

//538

LOUSTATUS ProbePiixDevice(P_PCI_DEVICE_OBJECT PDEV){
    
    PPCI_COMMON_CONFIG CommonConfig = (PPCI_COMMON_CONFIG)PDEV->CommonConfig;

    uint8_t ListNumber = GetDeviceListNumber(CommonConfig);

    if(ListNumber == DEVICE_LIST_MEMBERS){
        return STATUS_NO_SUCH_DEVICE;
    }

    LouPrint("Device ID :%h\n", CommonConfig->Header.DeviceID);
    LouPrint("Vendor ID :%h\n", CommonConfig->Header.VendorID);
    LouPrint("BASE CLASS:%h\n", CommonConfig->Header.BaseClass);
    LouPrint("SUB CLASS :%h\n", CommonConfig->Header.SubClass);
    LouPrint("PROG IF   :%h\n", CommonConfig->Header.ProgIf);

    for(uint8_t i = 0 ; i < 6;i++){
        LouPrint("Bar %d:%h\n", i, CommonConfig->Header.u.type0.BaseAddresses[i]);    
    }

    LouPrint("ListNumber:%d\n",ListNumber);
    uint8_t ProprietaryID = PiixTable[ListNumber].ProprietaryID;
    LouPrint("ProprietaryID:%d\n", ProprietaryID);

    while(1);
    return STATUS_SUCCESS;
}