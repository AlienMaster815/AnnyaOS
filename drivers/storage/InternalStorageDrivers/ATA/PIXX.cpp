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


typedef struct _PIIX_MAP_DB{
    uint32_t Mask;
    uint16_t Pe;
    int      Map[][4];
}PIIX_MAP_DB, * PPIIX_MAP_DB;

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

static const PIIX_DRIVER_DEVICE_LIST PiixTable[DEVICE_LIST_MEMBERS]{
    {0x8086, 0x7010, ANY_PCI_ID,ANY_PCI_ID,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA_MWDMA},
    {0x8086, 0x7111, 0x15AD,0x1976,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA_VMW},
    {0x8086, 0x7111, ANY_PCI_ID,ANY_PCI_ID,ANY_PCI_CLASS,ANY_PCI_CLASS,PIIX_PATA33},
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