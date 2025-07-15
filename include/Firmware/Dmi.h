#ifndef _DMI_CORE_H
#define _DMI_CORE_H
#ifndef __cplusplus
#include <LouAPI.h>
#else 
#include <LouDDK.h>
extern "C" {
#endif


typedef enum {
    DMI_NONE                    = 0,
    DMI_BIOS_VENDOR             = 1,
    DMI_BIOS_VERSION            = 2,
    DMI_BIOS_DATE               = 3,
    DMI_BIOS_RELEASE            = 4,
    DMI_EC_FIRMWARE_RELEASE     = 5,
    DMI_SYSTEM_VENDOR           = 6,
    DMI_PRODUCT_NAME            = 7,
    DMI_PRODUCT_VERSION         = 8,
    DMI_PRODUCT_SERIAL          = 9,
    DMI_PRODCT_UUID             = 10,
    DMI_PRODUCT_SKU             = 11,
    DMI_PRODUCT_FAMILY          = 12,
    DMI_BOARD_VENDOR            = 13,
    DMI_BOARD_NAME              = 14,
    DMI_BOARD_VERSION           = 15,
    DMI_BOARD_SERIAL            = 16,
    DMI_BOARD_ASSET_TAG         = 17,
    DMI_CHASSIS_VENDOR          = 18,
    DMI_CHASSIS_TYPE            = 19,
    DMI_CHASSIS_VERSION         = 20,
    DMI_CHASSIS_SERIAL          = 21,
    DMI_CHASSIS_ASSET_TAG       = 22,
    DMI_STRING_MAX              = 23,
    DMI_OEM_STRING              = 24,
}DMI_FIELD;

typedef struct _DMI_STRING_MATCH{
    uint8_t     Slot         : 7;
    uint8_t     ExactMatch   : 1;
    CHAR        SubString[79]; 
    bool        ValidEntry;
}DMI_STRING_MATCH, * PDMI_STRING_MATCH;

typedef struct _DMI_SYSTEM_ID{
    INTEGER             (*Callback)(struct _DMI_SYSTEM_ID*);
    string              Identification;
    DMI_STRING_MATCH    Matches[4];
    void*               DriverData;
    bool                ValidEntry;
}DMI_SYSTEM_ID, * PDMI_SYSTEM_ID;


INTEGER CheckDmiSystem(PDMI_SYSTEM_ID IdList);
INTEGER DmiGetBiosYear();
INTEGER CheckDmiSystem(PDMI_SYSTEM_ID IdList);

#define DMI_MATCH(Id, String) {.Slot = (Id), .SubString = (String), .ValidEntry = true}

#ifdef __cplusplus
}
#endif
#endif