//SPDX-Licence-IdentifierL AGPL 3.0/Proprietary
//Copyright (C) 2024-2025 Tyler Grenier
//Time Started  : 12/29/2024  9:10 PM
//Time Finished : NA

#ifndef _MPI_CONFIGURATION_H
#define _MPI_CONFIGURATION_H
#pragma pack(push,1)

#include "MpiTypes.h"
#include "Mpi.h"

//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

//Page Type Values
#define MPI_CONFIGURATION_PAGE_ATTRIBUTE_READ_ONLY                          0x00
#define MPI_CONFIGURATION_PAGE_ATTRIBUTE_CHAGEABLE                          0x10
#define MPI_CONFIGURATION_PAGE_ATTRIBUTE_PERSISTENT                         0x20
#define MPI_CONFIGURATION_PAGE_ATTRIBUTE_READ_ONLY_PERSISTENT               0x30
#define MPI_CONFIGURATION_PAGE_ATTRIBUTE_BITS                               0xF0

#define MPI_CONFIGURATION_PAGE_TYPE_IO_UNIT                                 0x00
#define MPI_CONFIGURATION_PAGE_TYPE_IOC                                     0x01
#define MPI_CONFIGURATION_PAGE_TYPE_BIOS                                    0x02
#define MPI_CONFIGURATION_PAGE_TYPE_SCSI_PORT                               0x03
#define MPI_CONFIGURATION_PAGE_TYPE_SCSI_DEVICE                             0x04
#define MPI_CONFIGURATION_PAGE_TYPE_FIBRE_CHANNEL_PORT                      0x05
#define MPI_CONFIGURATION_PAGE_TYPE_FIBRE_CHANNEL_DEVICE                    0x06
#define MPI_CONFIGURATION_PAGE_TYPE_LAN                                     0x07
#define MPI_CONFIGURATION_PAGE_TYPE_RAID_VOLUME                             0x08
#define MPI_CONFIGURATION_PAGE_TYPE_MANUFACTURING                           0x09
#define MPI_CONFIGURATION_PAGE_TYPE_RAID_PHYSICAL_DISK                      0x0A
#define MPI_CONFIGURATION_PAGE_TYPEBAND                                 0x0B
#define MPI_CONFIGURATION_PAGE_TYPE_EXTENDED                                0x0F
#define MPI_CONFIGURATION_PAGE_TYPE_BITS                                    0x0F

#define MPI_CONFIGURATION_PAGE_TYPE_NUMBER_BITS                             0x0FFF

//Extendedf Page Type Values
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_SAS_IO_UNIT                    0x10
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_SAS_EXPANDER                   0x11
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_SAS_DEVICE                     0x12
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_SAS_PHY                        0x13
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_LOG                            0x14
#define MPI_CONFIGURATION_EXTENDED_PAGE_TYPE_ENCLOSURE                      0x15

//Page Address Values
#define MPI_SCSI_PORT_PGAD_PORT_BITS                                        0xFF

#define MPI_SCSI_DEVICE_FORM_BITS                   0xF0000000
#define MPI_SCSI_DEVICE_FORM_BUS_TID                0x00000000
#define MPI_SCSI_DEVICE_TARGET_ID_BITS              0x000000FF    
#define MPI_SCSI_DEVICE_TARGET_ID_SHIFT             0
#define MPI_SCSI_DEVICE_BUS_BITS                    0x0000FF00
#define MPI_SCSI_DEVICE_BUS_SHIFT                   8
#define MPI_SCSI_DEVICE_FORM_TARGET_MODE            0x10000000
#define MPI_SCSI_DEVICE_TM_RESPOND_ID_BITS          0x000000FF
#define MPI_SCSI_DEVICE_TM_RESPOND_ID_SHIFT         0
#define MPI_SCSI_DEVICE_TM_BUS_BITS                 0x0000FF00
#define MPI_SCSI_DEVICE_TM_BUS_SHIFT                8
#define MPI_SCSI_DEVICE_TM_INIT_ID_BITS             0x00FF0000
#define MPI_SCSI_DEVICE_TM_INIT_ID_SHIFT            16

#define MPI_FIBRE_CHANNEL_PORT_PGAD_PORT_BITSD      0xF0000000
#define MPI_FIBRE_CHANNEL_PORT_PGAD_PORT_SHIFT      28
#define MPI_FIBRE_CHANNEL_PORT_PGAD_FORM_BITS       0x0F000000
#define MPI_FIBRE_CHANNEL_PORT_PGAD_FORM_INDEX      0x01000000
#define MPI_FIBRE_CHANNEL_PORT_PGAD_INDEX_BITS      0x0000FFFF
#define MPI_FIBRE_CHANNEL_PORT_PGAD_INDEX_SHIFT     0

#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_PORT_BITS     0xF0000000
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_PORT_SHIFT    28
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_FORM_BITS     0x0F000000
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_FORM_NEXT_DID 0x00000000
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_ND_PORT_BITS  0xF0000000
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_ND_PORT_SHIFT 28
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_ND_DID_BITS   0x00FFFFFF
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_ND_DID_SHIFT  0
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_FORM_BUS_TID  0x01000000
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_BT_BUS_BITS   0x0000FF00
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_BT_BUS_SHIFT  8
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_BT_TID_BITS   0x000000FF
#define MPI_FIBRE_CHANNEL_DEVICE_PGAD_BT_TID_SHIFT  0

#define MPI_PHYSICAL_DISK_PGAD_FORM_BITS            0xF0000000
#define MPI_PHYSICAL_DISK_PGAD_FORM_SHIFT           0

#define MPI_SAS_EXPANDED_PGAD_FORM_BITS             0xF0000000
#define MPI_SAS_EXPANDED_PGAD_FORM_SHIFT            28
#define MPI_SAS_EXPANDED_PGAD_FORM_GET_NEXT_HANDLE  0x00
#define MPI_SAS_EXPANDED_PGAD_FORM_HANDLE_PHY_NUM   0x01
#define MPI_SAS_EXPANDED_PGAD_FORM_HANDLE           0x02
#define MPI_SAS_EXPANDED_PGAD_GNH_BITS_HANDLE       0xFFFF
#define MPI_SAS_EXPANDED_PGAD_GNH_SHIFT_HANDLE      0
#define MPI_SAS_EXPANDED_PGAD_HPN_BITS_PHY          0x00FF0000
#define MPI_SAS_EXPANDED_PGAD_HPN_SHIFT_PHY         16
#define MPI_SAS_EXPANDED_PGAD_HPN_BITS_HANDLE       0x0000FFFF
#define MPI_SAS_EXPANDED_PGAD_HPN_SHIFT_HANDLE      0
#define MPI_SAS_EXPANDED_PGAD_H_BITS_HANDLE         0x0000FFFF
#define MPI_SAS_EXPANDED_PGAD_H_SHIFT_HANDLE        0

#define MPI_SAS_DEVICE_PGAD_FORM_BITS               0xF0000000
#define MPI_SAS_DEVICE_PGAD_FORM_SHIFT              28
#define MPI_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE    0x00
#define MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID      0x01
#define MPI_SAS_DEVICE_PGAD_FORM_HANDLE             0x02
#define MPI_SAS_DEVICE_PGAD_GNH_HANDLE_BITS         0xFFFF
#define MPI_SAS_DEVICE_PGAD_GNH_HANDLE_SHIFT        0
#define MPI_SAS_DEVICE_PGAD_BT_BUS_BITS             0xFF00
#define MPI_SAS_DEVICE_PGAD_BT_BUS_SHIFT            8
#define MPI_SAS_DEVICE_PGAD_BT_TID_BITS             0xFF
#define MPI_SAS_DEVICE_PGAD_BT_TID_SHIFT            0
#define MPI_SAS_DEVICE_PGAD_H_HANDLE_BITS           0xFFFF
#define MPI_SAS_DEVICE_PGAD_H_HANDLE_SHIFT          0

#define MPI_SAS_PHY_PGAD_FORM_BITS                  0xF0000000
#define MPI_SAS_PHY_PGAD_FORM_SHIFT                 28
#define MPI_SAS_PHY_PGAD_FORM_PHY_NUMBER            0x00
#define MPI_SAS_PHY_PGAD_FORM_PHY_TABLE_INDEX       0x01
#define MPI_SAS_PHY_PGAD_PHY_NUMBER_BITS            0xFF
#define MPI_SAS_PHY_PGAD_PHY_NUMBER_SHIFT           0
#define MPI_SAS_PHY_PGAD_PHY_TABLE_INDEX_BITS       0xFFFF
#define MPI_SAS_PHY_PGAD_PHY_TABLE_INDEX_SHIFT      0

#define MPI_SAS_ENCLOSURE_PGAD_FORM_BITS            0xF0000000
#define MPI_SAS_ENCLOSURE_PGAD_FORM_SHIFT           28
#define MPI_SAS_ENCLOSURE_PGAD_FORM_GET_NEXT_HANDLE 0x00
#define MPI_SAS_ENCLOSURE_PGAD_FROM_HANDLE          0x01
#define MPI_SAS_ENCLOSURE_PGAD_GNH_HANDLE_BITS      0xFFFF
#define MPI_SAS_ENCLOSURE_PGAD_GNH_HANDLE_SHIFT     0
#define MPI_SAS_ENCLOSURE_PGAD_H_HANDLE_BITS        0xFFFF
#define MPI_SAS_ENCLOSURE_PGAD_H_HANDLE_SHIFT       0

//Action Values
#define MPI_CONFIGURATION_ACTION_PAGE_HEADER            0x00
#define MPI_CONFIGURATION_ACTION_PAGE_READ_CURRENT      0x01
#define MPI_CONFIGURATION_ACTION_PAGE_WRITE_CURRENT     0x02
#define MPI_CONFIGURATION_ACTION_PAGE_DEFAULT           0x03
#define MPI_CONFIGURATION_ACTION_PAGE_WRITE_NVRAM       0x04
#define MPI_CONFIGURATION_ACTION_PAGE_READ_DEFAULT      0x05
#define MPI_CONFIGURATION_ACTION_PAGE_READ_NVRAM        0x06

//Manufactureing Configuration Pages
#define MPI_MANUFACTURE_PAGE_VENDOR_ID_LSI_LOGIC        0x1000

//FIBRE Channel Devices
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC909            0x0621
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC919            0x0624
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC929            0x0622
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC919X           0x0628
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC929X           0x0626
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC939X           0x0642
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC949X           0x0640
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_FC949E           0x0646
//Plain SCSI Devices
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_53C1030          0x0030  //Tested Working
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_53C1030ZC        0x0031  
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_1030_5C1035      0x0032
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_1030ZC_5C1035    0x0033
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_53C1035          0x0040
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_53C1035ZC        0x0041
//SAS
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1064          0x0050
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1064A         0x005C
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1064E         0x0056
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1066          0x005E
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1066E         0x005A
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1068          0x0054  //Tested Working
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1068E         0x0058
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1068_820XELP  0x0059
#define MPI_MANUFACTURE_PAGE_DEVICE_ID_SAS1078          0x0062

#define MPI_MANUFACTURE_TYPE0_CURRENT_PAGE_REVISION     0x00
#define MPI_MANUFACTURE_TYPE1_CURRENT_PAGE_REVISION     0x00

#ifndef MPI_MANUFACTURE_PAGE_TYPE_2_HARDWARE_SETTING_LENGTH
#define MPI_MANUFACTURE_PAGE_TYPE_2_HARDWARE_SETTING_LENGTH 1
#endif


//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

#define MPI_MANUFACTURE_PAGE_TYPE2_VERSION              0

#ifndef MPI_MANUFACTURE_PAGE_TYPE3_INFO_LENGTH
#define MPI_MANUFACTURE_PAGE_TYPE3_INFO_LENGTH 1        //       1 // :|)
#endif

#define MPI_MANUFACTURE_PAGE_TYPE3_VERSION              0

//Definitions For MANUFACTURE PAGE FLAGS
#define MPI_MANUFACTURE_PAGE_TYPE4_FORCE_BAD_BLOCK_TABLE        0x80
#define MPI_MANUFACTURE_PAGE_TYPE4_FORCE_OFFLINE_FAILOVER       0x40
#define MPI_MANUFACTURE_PAGE_TYPE4_IME_DISABLE                  0x20
#define MPI_MANUFACTURE_PAGE_TYPE4_IM_DISABLE                   0x10
#define MPI_MANUFACTURE_PAGE_TYPE4_IS_DISABLE                   0x08
#define MPI_MANUFACTURE_PAGE_TYPE4_IR_MODE_PAGE8_DISABLE        0x04
#define MPI_MANUFACTURE_PAGE_TYPE4_IM_RESYNC_CACHE_ENABLE       0x02
#define MPI_MANUFACTURE_PAGE_TYPE4_NO_MIX_SAS_SATA              0x01

//Define For MANUFACTURE PAGE EXTENDED FLAGS
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_COERCION_SIZE_BITS        0x0180
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_COERCION_SIZE_SHIFT       7
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_1GIG_COERCION_SIZE        0
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_128MB_COERCION_SIZE       1

#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_NO_MIX_SSD_SAS_SATA       0x40
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_MIX_SSD_AND_NON_SSD       0x20
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_DUAL_PORT_SUPPORT         0x10
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_HIDE_NON_IR_DATA          0x08
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_SAS_CACHE_DISABLE         0x04
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_SATA_CACHE_DISABLE        0x02
#define MPI_MANUFACTURE_PAGE_TYPE4_EXTENDED_FLAGS_LEGACY_MODE               0x01

#ifndef MPI_MANUFACTURE_PAGES_FORCEWID_NUMBER
#define MPI_MANUFACTURE_PAGES_FORCEWID_NUMBER 1
#endif 

#define MPI_MANUFACTURE_PAGE_TYPE5_VERSION          2
#define MPI_MANUFACTURE_PAGE_TYPE5_TWO_WWID_PER_PHY 1

#define MPI_MANUFACTURING_PAGE_VERSION6 0x00

//Pinout Fields
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8484_L4             0x00080000
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8484_L3             0x00040000
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8484_L2             0x00020000
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8484_L1             0x00010000
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8470_L4             0x00000800
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8470_L3             0x00000400
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8470_L2             0x00000200
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8470_L1             0x00000100
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_SFF_8482                0x00000002
#define MPI_MANUFACTURING_PAGE_TYPE7_PINOUT_CONNECTION_UNKONW       0x00000001

//Location Field Defines
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_UNKONW            0x01
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_INTERNAL          0x02
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_EXTERNAL          0x04
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_SWITCHABLE        0x08
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_AUTO              0x10
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_NOT_PRESENT       0x20
#define MPI_MANUFACTURING_PAGE_TYPE7_LOCATION_NOT_CONNECTED     0x80

#ifndef MPI_MANUFACTURING_PAGE_TYPE7_CONNECTOR_INFO_MAXIMUM 
#define MPI_MANUFACTURING_PAGE_TYPE7_CONNECTOR_INFO_MAXIMUM 1
#endif

#define MPI_MANUFACTURING_PAGE_TYPE7_VERSION            0x00
#define MPI_MANUFACTURING_PAGE_TYPE7_USE_SLOT_INFO_FLAG 1

#define MPI_MANUFACTURING_PAGE_TYPE8_VERSION    0
#define MPI_MANUFACTURING_PAGE_TYPE9_VERSION    0
#define MPI_MANUFACTURING_PAGE_TYPE10_VERSION   0

#define MPI_IO_UNIT_PAGE0_VERSION   0
#define MPI_IO_UNIT_PAGE1_VERSION   2

//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

//Io Unit Page 1 Flags
#define MPI_IO_UNIT_PAGE1_MULTI_FUNCTION                0x00000000
#define MPI_IO_UNIT_PAGE1_SINGLE_FUNCTION               0x00000001
#define MPI_IO_UNIT_PAGE1_MULTI_PATHING                 0x00000002
#define MPI_IO_UNIT_PAGE1_SINGLE_PATHING                0x00000000
#define MPI_IO_UNIT_PAGE1_IR_USE_STATIC_VOLUME_ID       0x00000004
#define MPI_IO_UNIT_PAGE1_DISABLE_QUEUE_FULL_HANLING    0x00000020
#define MPI_IO_UNIT_PAGE1_DISABLE_IR_SYSTEM             0x00000040
#define MPI_IO_UNIT_PAGE1_FORCE_32_BIT                  0x00000080
#define MPI_IO_UNIT_PAGE1_NCQ_DISABLE                   0x00000100
#define MPI_IO_UNIT_PAGE1_SATA_WRITE_CACHE_DISABLE      0x00000200

#define MPI_ADAPTER_INFORMATION_FLAGS_EMBEDDED          0x0001
#define MPI_ADAPTER_INFORMATION_FLAGS_INIT_STATUS       0x0002

#define MPI_IO_UNIT_PAGE2_VERSION       0x02

#define MPI_IO_UNIT_PAGE2_FLAGS_PAUSE_ON_ERROR              0x00000002
#define MPI_IO_UNIT_PAGE2_FLAGS_VERBOSE_ENABLE              0x00000004
#define MPI_IO_UNIT_PAGE2_FLAGS_COLOR_VIDEO_DISABLE         0x00000008
#define MPI_IO_UNIT_PAGE2_FLAGS_HOOK_INT40                  0x00000010

#define MPI_IO_UNIT_PAGE2_FLAGS_DEVICE_LIST_DISPLAY_BITS    0x000000E0
#define MPI_IO_UNIT_PAGE2_FLAGS_INSTALLED_DEVICE_DISPLAY    0x00000000
#define MPI_IO_UNIT_PAGE2_FLAGS_ADAPTER_DISPLAY             0x00000020
#define MPI_IO_UNIT_PAGE2_FLAGS_ADAPTER_DEVICE_DISPLAY      0x00000040

#ifndef MPI_IO_UNIT_PAGE3_GPIO_VALUE_MAXIMUM
#define MPI_IO_UNIT_PAGE3_GPIO_VALUE_MAXIMUM    1
#endif

#define MPI_IO_UNIT_PAGE3_VERSION       0x01

#define MPI_IO_UNIT_PAGE3_GPIO_FUNCTION_BITS        0xFC
#define MPI_IO_UNIT_PAGE3_GPIO_FUNCTION_SHIFT       2
#define MPI_IO_UNIT_PAGE3_GPIO_SETTING_OFF          0
#define MPI_IO_UNIT_PAGE3_GPIO_SETTING_ON           1

#define MPI_IO_UNIT_PAGE4_VERSION       0x00

#define MPI_IOC_PAGE0_VERSION   1

#define MPI_IOC_PAGE1_VERSION   3

//IOC Page 1 Flags
#define MPI_IOC_PAGE1_FLAGS_EEDP_MODE_BITS                      0x07000000
#define MPI_IOC_PAGE1_FLAGS_EEDP_MODE_OFF                       0x00000000
#define MPI_IOC_PAGE1_FLAGS_EEDP_MODE_T10                       0x01000000
#define MPI_IOC_PAGE1_FLAGS_EEDP_MODE_LSI1                      0x02000000
#define MPI_IOC_PAGE1_FLAGS_INITIATOR_CONTEX_REPLY_DISABLE      0x00000010
#define MPI_IOC_PAGE1_FLAGS_REPLY_COALESCING                    0x00000001

#define MPI_IOC_PAGE1_PCI_SLOT_UNKNOWN                          0xFF

#define MPI_RAID_VOLUME_TYPE_IS             0
#define MPI_RAID_VOLUME_TYPE_IME            1
#define MPI_RAID_VOLUME_TYPE_IM             2
#define MPI_RAID_VOLUME_TYPE_RAID5          3
#define MPI_RAID_VOLUME_TYPE_RAID6          4
#define MPI_RAID_VOLUME_TYPE_RAID10         5
#define MPI_RAID_VOLUME_TYPE_RAID50         6
#define MPI_RAID_VOLUME_TYPE_UNKNOWN        0xFF

#define MPI_IOC_PAGE2_FLAGS_VOLUME_INACTIVE 8

#define MPI_IOC_PAGE2_VERSION   4

#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_IS_SUPPORTED                   0x00000001
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_IME_SUPPORTED                  0x00000002
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_IM_SUPPORTED                   0x00000004
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_RAID5_SUPPORTED                0x00000008
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_RAID6_SUPPORTED                0x00000010
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_RAID10_SUPPORTED               0x00000020
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_RAID50_SUPPORTED               0x00000040
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_RAID64_SUPPORTED               0x10000000
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_SES_SUPPORTED                  0x20000000
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_SAFTE_SUPPORTED                0x40000000
#define MPI_IOC_PAGE2_CAPABILITIES_FLAGS_CROSS_CHANNEL_SUPPORTED        0x80000000

#define MPI_IOC_PAGE3_VERSION   0

#define MPI_IOC_PAGE4_PAGE_VERSION      0

#define MPI_IOC_PAGE5_HOT_SPARE_ACTIVE      1

#ifndef MPI_IOC_PAGE5_HOT_SPARE_MAXIMUM
#define MPI_IOC_PAGE5_HOT_SPARE_MAXIMUM 1
#endif

#define MPI_IOC_PAGE5_PAGE_VERSION      0

#define MPI_IOC_PAGE6_PAGE_VERSION      1

#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_SSD_SUPPORT                    0x00000020
#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_MULTIPORT_DRIVE_SUPPORT        0x00000010
#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_DISABLE_SMART_POLLING          0x00000008

#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_META_DATA_SIZE_BITS            0x00000006
#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_64MB_META_DATA_SIZE            0x00000000
#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_512MB_META_DATA_SIZE           0x00000002

#define MPI_IOC_PAGE6_CAPABILITIES_FLAGS_GLOBAL_HOT_SPARE               0x00000001

#define MPI_BIOS_PAGE1_PAGE_VERSION     0x03

#define MPI_BIOS_PAGE1_OPTIONS_SPI_ENABLE       0x00000400
#define MPI_BIOS_PAGE1_OPTIONS_FC_ENABLE        0x00000200
#define MPI_BIOS_PAGE1_OPTIONS_SAS_ENABLE       0x00000100
#define MPI_BIOS_PAGE1_OPTIONS_DISABLE_BIOS     0x00000001

#define MPI_BIOS_PAGE1_IOC_SET_INIT_SPINUP_DELAY_BITS       0x0F000000
#define MPI_BIOS_PAGE1_IOC_SET_INIT_SPINUP_DELAY_SHIFT      24

#define MPI_BIOS_PAGE1_IOC_SET_PORT_ENABLE_DELAY_BITS       0x00F00000
#define MPI_BIOS_PAGE1_IOC_SET_PORT_ENABLE_DELAY_SHIFT      20

#define MPI_BIOS_PAGE1_IOC_SET_AUTO_PORT_ENABLE             0x00080000
#define MPI_BIOS_PAGE1_IOC_SET_DIRECT_ATTACH_SPINUP_MODE    0x00040000

#define MPI_BIOS_PAGE1_IOC_SET_BOOT_PREFERECE_BITS          0x00030000
#define MPI_BIOS_PAGE1_IOC_SET_ENCLOSURE_SLOT_BOOT          0x00000000
#define MPI_BIOS_PAGE1_IOC_SET_SAS_ADDRESS_BOOT             0x00010000

#define MPI_BIOS_PAGE1_IOC_SET_MAX_TARGET_SPIN_UP_BITS      0x0000F000
#define MPI_BIOS_PAGE1_IOC_SET_MAX_TARGET_SPIN_UP_SHIFT     12

#define MPI_BIOS_PAGE1_IOC_SET_SPINUP_DELAY_BITS            0x00000F00
#define MPI_BIOS_PAGE1_IOC_SET_SPINUP_DELAY_SHIFT           8

#define MPI_BIOS_PAGE1_IOC_SET_RM_SETTING_BITS              0x000000C0
#define MPI_BIOS_PAGE1_IOC_SET_NONE_RM_SETTING              0x00000000
#define MPI_BIOS_PAGE1_IOC_SET_BOOT_RM_SETTING              0x00000040
#define MPI_BIOS_PAGE1_IOC_SET_MEDIA_RM_SETING              0x00000080

#define MPI_BIOS_PAGE1_IOC_SET_ADAPTER_SUPPORT_BITS         0x00000030
#define MPI_BIOS_PAGE1_IOC_SET_NO_SUPPORT                   0x00000000
#define MPI_BIOS_PAGE1_IOC_SET_BIOS_SUPPORT                 0x00000010
#define MPI_BIOS_PAGE1_IOC_SET_OS_SUPPORT                   0x00000020
#define MPI_BIOS_PAGE1_IOC_SET_ALL_SUPPORT                  0x00000030

#define MPI_BIOS_PAGE1_IOC_SET_ALTERNATE_CHS                0x00000008

#define MPI_BIOS_PAGE1_DEV_SET_DISABLE_SMART_POLLING        0x00000010
#define MPI_BIOS_PAGE1_DEV_SET_DISABLE_SEQ_LUN              0x00000008
#define MPI_BIOS_PAGE1_DEV_SET_DISABLE_RM_LUN               0x00000004
#define MPI_BIOS_PAGE1_DEV_SET_DISABLE_NON_RM_LUN           0x00000002
#define MPI_BIOS_PAGE1_DEV_SET_DISABLE_OTHER_LUN            0x00000001

#define MPI_BIOS_PAGE1_EXP_SPINUP_MAX_TARGET_BITS           0xF0
#define MPI_BIOS_PAGE1_EXP_SPINUP_MAX_TARGET_SHIFT          4
#define MPI_BIOS_PAGE1_EXP_SPINUP_DLEAY_BITS                0x0F

#define MPI_BIOS_PAGe2_PAGE_VERSION             0x02

#define MPI_BIOS_PAGE2_FORM_BITS                0x0F
#define MPI_BIOS_PAGE2_FORM_ADAPTER_ORDER       0x00
#define MPI_BIOS_PAGE2_FORM_ADAPTER_NUMBER      0x01
#define MPI_BIOS_PAGE2_FORM_PCI_ADDRESS         0x02
#define MPI_BIOS_PAGE2_FORM_PCI_SLOT_NUMBER     0x03
#define MPI_BIOS_PAGE2_FORM_FIBRE_CHANNEL_WHN   0x04
#define MPI_BIOS_PAGE2_FORM_SAS_WHN             0x05
#define MPI_BIOS_PAGE2_FORM_ENCLOSURE_SLOT      0x06    

#define MPI_BIOS_PAGE4_PAGE_VERSION             0x00

#define MPI_SCSI_PORT_PAGE0_PAGE_VERSION        0x02

#define MPI_SCSI_PORT_PAGE0_CAP_IU                              0x00000001
#define MPI_SCSI_PORT_PAGE0_CAP_DT                              0x00000002
#define MPI_SCSI_PORT_PAGE0_CAP_QAS                             0x00000004
#define MPI_SCSI_PORT_PAGE0_CAP_MIN_SYNC_PERIOD_BITS            0x0000FF00
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC_ASYNC                      0x00
#define MPI_SCSI_PORT_PAGE0_CAP_SNYC5                           0x32
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC10                          0x19
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC20                          0x0C
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC33_33                       0x0B
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC40                          0x0A
#define MPI_SCSI_PORT_PAGE0_CAP_SNYC80                          0x09
#define MPI_SCSI_PORT_PAGE0_CAP_SNYC160                         0x08
#define MPI_SCSI_PORT_PAGE0_CAP_SYNC_UNKOWN                     0xFF

#define MPI_SCSI_PORT_PAGE0_CAP_MIN_SYNC_PERIOD_SHIFT           8
#define MPI_SCSI_PORT_PAGE0_CAP_GET_MIN_SNYC_PERIOD(Capabilities) (((Capabilities) & MPI_SCSI_PORT_PAGE0_CAP_MIN_SYNC_PERIOD_BITS) >> MPI_SCSI_PORT_PAGE0_CAP_MIN_SYNC_PERIOD_SHIFT)

#define MPI_SCSI_PORT_PAGE0_CAP_MAX_SYNC_OFFSET_BITS            0x00FF0000
#define MPI_SCSI_PORT_PAGE0_CAP_MAX_SYNC_OFFSET_SHIFT           16
#define MPI_SCSI_PORT_PAGE0_CAP_GET_MAX_SYNC_OFFSET(Capabilities) (((Capabilities) & MPI_SCSI_PORT_PAGE0_CAP_MAX_SYNC_OFFSET_BITS) >> MPI_SCSI_PORT_PAGE0_CAP_MAX_SYNC_OFFSET_SHIFT)

#define MPI_SCSI_PORT_PAGE0_CAP_IDP                             0x00000000
#define MPI_SCSI_PORT_PAGE0_CAP_WIDE                            0x20000000
#define MPI_SCSI_PORT_PAGE0_CAP_AIP                             0x80000000

#define MPI_SCSI_PORT_PAGE0_PHY_SIGNAL_TYPE_BITS                0x00000003
#define MPI_SCSI_PORT_PAGE0_PHY_SIGNAL_HVD                      0x01
#define MPI_SCSI_PORT_PAGE0_PHY_SIGNAL_SE                       0x02
#define MPI_SCSI_PORT_PAGE0_PHY_SIGNAL_LVD                      0x03
#define MPI_SCSI_PORT_PAGE0_PHY_CONNECTED_ID_BITS               0xFF000000
#define MPI_SCSI_PORT_PAGE0_PHY_CONNECTED_ID_SHIFT              24
#define MPI_SCSI_PORT_PAGE0_PHY_BUS_FREE_CONNECTED_ID           0xFE
#define MPI_SCSI_PORT_PAGE0_PHY_UNKOWN_CONNECTED_ID             0xFFs



typedef struct _CONFIGURATION_PAGE_HEADER{
    MPIU8       Version;
    MPIU8       Length;
    MPIU8       Number;
    MPIU8       Type;
}CONFIGURATION_PAGE_HEADER, * PCONFIGURATION_PAGE_HEADER;

typedef union _CONFIGURATION_PAGE_UNION{
    CONFIGURATION_PAGE_HEADER       Header;
    MPIU8                           Bytes[4];
    MPIU16                          Words[2];
    MPIU32                          Dword;
}CONFIGURATION_PAGE_UNION,* PCONFIGURATION_PAGE_UNION;

typedef struct _CONFIGURATION_EXTNEDED_PAGE_HEADER{
    MPIU8       Version;
    MPIU8       Rsv1;
    MPIU8       Number;
    MPIU8       Type;
    MPIU16      ExtendedLength;
    MPIU8       ExtendefType;
    MPIU8       Rsv2;
}CONFIGURATION_EXTNEDED_PAGE_HEADER, * PCONFIGURATION_EXTNEDED_PAGE_HEADER;

//Configuration Request Message 
typedef struct _MESSAGE_CONFIGURATION{
    MPIU8                           MessageAction;
    MPIU8                           Rsv1;
    MPIU8                           ChainOffset;
    MPIU8                           MessageFunction;
    MPIU16                          ExtendePageLength;
    MPIU8                           ExtendedPageType;
    MPIU8                           MessageFlags;
    MPIU32                          MessageContext;
    MPIU8                           Rsv2[8];
    CONFIGURATION_PAGE_HEADER       PageHeader;
    MPIU32                          PageAddress;
    SCATTER_GATHER_ENTRY_IO_UNION   PageBufferScatterGatherEntry;
}MESSAGE_CONFIGURATION, * PMESSAGE_CONFIGURATION;

//Configuration Reply Message
typedef struct _CONFIGURATION_MESSAGE_REPLY{
    MPIU8                           MessageAction;
    MPIU8                           Rsv1;
    MPIU8                           MessageLength;
    MPIU8                           MessageFunction;
    MPIU16                          ExtendedPageLength;
    MPIU8                           ExtendefPageType;
    MPIU8                           MessageFlags;
    MPIU32                          MessageContext;
    MPIU8                           Rsv2[2];
    MPIU16                          IocStatus;
    MPIU32                          IocLogInfo;
    CONFIGURATION_PAGE_HEADER       PageHeader;
}CONFIGURATION_MESSAGE_REPLY, * PCONFIGURATION_MESSAGE_REPLY;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE0{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU8                       ChipID[16];
    MPIU8                       ChipVersion[8];
    MPIU8                       BoardID[16];
    MPIU8                       BoardAssembly[16];
    MPIU8                       BoardTracerID[16];
}CONFIGURATION_PAGE_MANUFACTURING_TYPE0, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE0;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE1{
    CONFIGURATION_PAGE_HEADER       PageHeader;
    MPIU8                           VPD[256];
}CONFIGURATION_PAGE_MANUFACTURING_TYPE1, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE1;

typedef struct _MPI_CHIPSET_REVISION_ID{
    MPIU16      DeviceID;
    MPIU8       PCIRevision;
    MPIU8       Rsv;
}MPI_CHIPSET_REVISION_ID, * PMPI_CHIPSET_REVISION_ID;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE2{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPI_CHIPSET_REVISION_ID     ChipsetID;
    MPIU32                      HardWareSettings[MPI_MANUFACTURE_PAGE_TYPE_2_HARDWARE_SETTING_LENGTH];
}CONFIGURATION_PAGE_MANUFACTURING_TYPE2, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE2;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE3{
    CONFIGURATION_PAGE_HEADER       PageHeader;
    MPI_CHIPSET_REVISION_ID         ChipsetID;
    MPIU32                          Information[MPI_MANUFACTURE_PAGE_TYPE_2_HARDWARE_SETTING_LENGTH];
}CONFIGURATION_PAGE_MANUFACTURING_TYPE3, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE3;

//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE4{
    CONFIGURATION_PAGE_HEADER           PageHeader;
    MPIU32                              Rsv1;
    MPIU8                               InfoOffset0;
    MPIU8                               InfoSize0;
    MPIU8                               InfoOffset1;
    MPIU8                               InfoSize1;
    MPIU8                               InquirySize;
    MPIU8                               Flags;
    MPIU16                              ExtendedFlags;
    MPIU8                               InquiryData[56];
    MPIU32                              IsVolumeSettings;
    MPIU32                              ImeVolumeSettings;
    MPIU32                              ImVolumeSettings;
    MPIU32                              Rsv2;
    MPIU32                              Rsv3;
    MPIU32                              Rsv4;
    MPIU8                               ImeDataScrubRate;
    MPIU8                               ImeRsSyncRate;
    MPIU16                              Rsv5;
    MPIU8                               ImDataDataScrubRate;
    MPIU8                               ImResyncRate;
    MPIU16                              Rsv6;
    MPIU32                              Rsv7;
    MPIU32                              Rsv8;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE4, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE4;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE5{
    CONFIGURATION_PAGE_HEADER           PageHeader;
    MPIU64                              BaseWWID;
    MPIU8                               Flags;
    MPIU8                               NumberOfForceWWID;
    MPIU16                              Rsv1;
    MPIU32                              Rsv2;
    MPIU32                              Rsv3;
    MPIU64                              ForceWWID[MPI_MANUFACTURE_PAGES_FORCEWID_NUMBER];
}CONFIGURATION_PAGE_MANUFACTURING_TYPE5, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE5;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE6{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      ProductInfo;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE6, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE6;

typedef struct _MPI_MANUFACTURING_PAGE_TYPE7_CONECTOR_INFO{
    MPIU32      Pinout;
    MPIU8       Connector[16];
    MPIU8       Location;
    MPIU8       Rsv1;
    MPIU16      Slot;
    MPIU32      Rsv2;
}MPI_MANUFACTURING_PAGE_TYPE7_CONECTOR_INFO, * PMPI_MANUFACTURING_PAGE_TYPE7_CONECTOR_INFO;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE7{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU8                       ProductInfo;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE7, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE7;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE8{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      ProductInfo;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE8, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE8;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE9{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      ProductInfo;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE9, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE9;

typedef struct _CONFIGURATION_PAGE_MANUFACTURING_TYPE10{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      ProductInfo;
}CONFIGURATION_PAGE_MANUFACTURING_TYPE10, * PCONFIGURATION_PAGE_MANUFACTURING_TYPE10;

typedef struct _CONFIGURATION_PAGE_IO_UNIT0{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU64                      SpecialValue;
}CONFIGURATION_PAGE_IO_UNIT0, * PCONFIGURATION_PAGE_IO_UNIT0;

typedef struct _CONFIGURATION_PAGE_IO_UNIT1{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      Flags;
}CONFIGURATION_PAGE_IO_UNIT1, * PCONFIGURATION_PAGE_IO_UNIT1;

//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

typedef struct _MPI_ADAPTER_INFORMATION{
    MPIU8   PciBus;
    MPIU8   PciDeviceAndFunction;
    MPIU16  AdapterFlags;
}MPI_ADAPTER_INFORMATION, * PMPI_ADAPTER_INFORMATION; 

typedef struct _CONFIGURATION_PAGE_IO_UNIT2{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      Flags;
    MPIU32                      BiosVersion;
    MPI_ADAPTER_INFORMATION     Adapter[4];
    MPIU32                      Rsv1;
}CONFIGURATION_PAGE_IO_UNIT2, * PCONFIGURATION_PAGE_IO_UNIT2;

typedef struct _CONFIGURATION_PAGE_IO_UNIT3{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU8                       GpioCount;
    MPIU8                       Rsv1;
    MPIU16                      Rsv2;
    MPIU16                      GpioValue[MPI_IO_UNIT_PAGE3_GPIO_VALUE_MAXIMUM];
}CONFIGURATION_PAGE_IO_UNIT3, * PCONFIGURATION_PAGE_IO_UNIT3;

typedef struct _CONFIGURATION_PAGE_IO_UNIT4{
    CONFIGURATION_PAGE_HEADER           Pageheader;
    MPIU32                              Rsv1;
    SCATTER_GATHER_ENTRY_SIMPLE_UNION   FirmwareImage;
}CONFIGURATION_PAGE_IO_UNIT4, * PCONFIGURATION_PAGE_IO_UNIT4;

typedef struct _CONFIGURATION_PAGE_IOC0{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      TotalNvStorage;
    MPIU32                      FreeNvStorage;
    MPIU16                      VendorID;
    MPIU16                      DeviceID;
    MPIU8                       Revision;
    MPIU8                       Rsv1[3];
    MPIU32                      ClassCode;
    MPIU16                      SubVendor;
    MPIU16                      SubID;
}CONFIGURATION_PAGE_IOC0, * PCONFIGURATION_PAGE_IOC0;

typedef struct _CONFIGURATION_PAGE_IOC1{
    CONFIGURATION_PAGE_HEADER   Pageheader;
    MPIU32                      Flags;
    MPIU32                      CCTimeout;// Coalescing Timeout for Commad Coalescing
    MPIU8                       CCDepth;//   Coalescing Depth
    MPIU8                       PciSlot;
    MPIU8                       Rsv1[2];
}CONFIGURATION_PAGE_IOC1, * PCONFIGURATION_PAGE_IOC1;

typedef struct _CONFIGURATION_PAGE_IOC2_RAID_VOLUME{
    MPIU8   Volume;
    MPIU8   Bus;
    MPIU8   Ioc;
    MPIU8   PageNumer;
    MPIU8   Type;
    MPIU8   Flags;
    MPIU16  Rsv1;
}CONFIGURATION_PAGE_IOC2_RAID_VOLUME, * PCONFIGURATION_PAGE_IOC2_RAID_VOLUME;

typedef struct _CONFIGURATION_PAGE_IOC2{
    CONFIGURATION_PAGE_HEADER           PageHeader;
    MPIU32                              CapFlags;
    MPIU8                               ActiveValues;
    MPIU8                               MaxVolumes;
    MPIU8                               ActivePhysicalDisks;
    MPIU8                               MaximumPhysicalDisks;
    CONFIGURATION_PAGE_IOC2_RAID_VOLUME RaidVolume[];
}CONFIGURATION_PAGE_IOC2, * PCONFIGURATION_PAGE_IOC2;

typedef struct _IOC3_PHYSICAL_DISK{
    MPIU8   ID;
    MPIU8   Bus;
    MPIU8   IOC;
    MPIU8   Number;
}IOC3_PHYSICAL_DISK, * PIOC3_PHYSICAL_DISK;

typedef struct _CONFIGURATION_PAGE_IOC3{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU8                       NumberOfPhysicalDisks;
    IOC3_PHYSICAL_DISK          PhysicalDisk[];
}CONFIGURATION_PAGE_IOC3, * PCONFIGURATION_PAGE_IOC3;

typedef struct _IOC4_SEP{
    MPIU8   SEPTargetID;
    MPIU8   SEPBus;
    MPIU16  Rsv1;
}IOC4_SEP, * PIOC4_SEP;

typedef struct _CONFIGURATION_PAGE_IOC4{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU8                       ActiveSep;
    MPIU8                       MaxSep;
    MPIU16                      Rsv1;
    IOC4_SEP                    sep[];
}CONFIGURATION_PAGE_IOC4, * PCONFIGURATION_PAGE_IOC4;

typedef struct _IOC5_HOT_SPARE{
    MPIU8       PhysicalDiskNumber;
    MPIU8       Rsv1;
    MPIU8       HotSparePool;
    MPIU8       Flags;
}IOC5_HOT_SPARE, * PIOC5_HOT_SPARE;

typedef struct _CONFIGURATION_PAGE_IOC5{
    CONFIGURATION_PAGE_HEADER   PageHeaer;
    MPIU32                      Rsv1;
    MPIU8                       NumberOfHotSpare;
    MPIU8                       Rsv2;
    MPIU16                      Rsv3;
    IOC5_HOT_SPARE              HotSpare[MPI_IOC_PAGE5_HOT_SPARE_MAXIMUM];
}CONFIGURATION_PAGE_IOC5, * PCONFIGURATION_PAGE_IOC5;

typedef struct _CONFIGURATION_PAGE_IOC6{
    CONFIGURATION_PAGE_HEADER       PageHeader;
    MPIU32                          CapabilitiesAndFlags;
    MPIU8                           MaxISDrives;
    MPIU8                           MaxIMDrives;
    MPIU8                           MaxIMEDrives;
    MPIU8                           Rsv1;
    MPIU8                           MinISDrives;
    MPIU8                           MinIMDrives;
    MPIU8                           MinIMEDrives;
    MPIU8                           Rsv2;
    MPIU8                           MaxGlobalHotSpares;
    MPIU8                           Rsv3;
    MPIU16                          Rsv4;
    MPIU32                          Rsv5;
    MPIU32                          SupportedStripeSizeMapIS;
    MPIU32                          SupportedStripeSizeMapIME;
    MPIU32                          Rsv6;
    MPIU8                           MetaSize;
    MPIU8                           Rsv7;
    MPIU16                          Rsv8;
    MPIU16                          MaximumBadBlockEntries;
    MPIU16                          Rsv9;
    MPIU32                          IRNvsramVersion;
    MPIU32                          Rsv11;
    MPIU32                          Rsv12;
}CONFIGURATION_PAGE_IOC6, * PCONFIGURATION_PAGE_IOC6;

typedef struct _CONFIGURATION_PAGE_BIOS1{
    CONFIGURATION_PAGE_HEADER       PageHeader;
    MPIU32                          BiosOptions;
    MPIU32                          IocSettings;
    MPIU32                          Rsv1;
    MPIU32                          DeviceSettings;
    MPIU16                          DeviceCount;
    MPIU8                           ExpanderSpinup;
    MPIU8                           Rsv2;
    MPIU16                          IoTimeoutBlockDevicesNonRM;
    MPIU16                          IoTimeoutSequntial;
    MPIU16                          IoTimeoutOther;
    MPIU16                          IoTimeoutBlockDevicesRM;
}CONFIGURATION_PAGE_BIOS1, * PCONFIGURATION_PAGE_BIOS1;

typedef struct _MPI_BOOT_DEVICE_ADAPTER_ORDER{
    MPIU32      Rsv[17];
}MPI_BOOT_DEVICE_ADAPTER_ORDER, * PMPI_BOOT_DEVICE_ADAPTER_ORDER;

typedef struct _MPI_BOOT_DEVICE_ADAPTER_NUMBER{
    MPIU8   Target;
    MPIU8   Bus;
    MPIU8   Adapter;
    MPIU8   Rsv1;
    MPIU32  Rsv2[3];
    MPIU8   LUN[8];
    MPIU32  Rsv3[11];
}MPI_BOOT_DEVICE_ADAPTER_NUMBER, * PMPI_BOOT_DEVICE_ADAPTER_NUMBER;

typedef struct _MPI_BOOT_DEVICE_PCI_ADDRESS{
    MPIU8   Target;
    MPIU8   Bus;
    MPIU16  PciAddress;
    MPIU32  Rsv1[3];
    MPIU8   LUN[8];
    MPIU32  Rsv2[11];
}MPI_BOOT_DEVICE_PCI_ADDRESS, * PMPI_BOOT_DEVICE_PCI_ADDRESS;

typedef struct _MPI_BOOT_DEVICE_PCI_SLOT_ADDRESS{
    MPIU8   Target;
    MPIU8   Bus;
    MPIU8   Slot;
    MPIU8   Rsv1;
    MPIU32  Rsv2[3];
    MPIU8   LUN[8];
    MPIU32  Rsv3[11];
}MPI_BOOT_DEVICE_PCI_SLOT_ADDRESS, * PMPI_BOOT_DEVICE_PCI_SLOT_ADDRESS;

typedef struct _MPI_BOOT_DEVICE_FIBRE_CHANNEL_WHN{
    MPIU64  WWPN;
    MPIU32  Rsv1[2];
    MPIU8   LUN[8];
    MPIU32  Rsv2[11];
}MPI_BOOT_DEVICE_FIBRE_CHANNEL_WHN, * PMPI_BOOT_DEVICE_FIBRE_CHANNEL_WHN;

typedef struct _MPI_BOOT_DEVICE_SAS_WHN{
    MPIU64  SasAddress;
    MPIU32  Rsv1[2];
    MPIU8   LUN[8];
    MPIU32  Rsv2[11];
}MPI_BOOT_DEVICE_SAS_WHN, * PMPI_BOOT_DEVICE_SAS_WHN;

typedef struct _MPI_BOOT_DEVICE_ENCLOSURE_SLOT{
    MPIU64  EnclosureID;
    MPIU32  Rsv1[2];
    MPIU8   LUN[8];
    MPIU16  SlotNumber;
    MPIU16  Rsv2;
    MPIU32  Rsv3[10];
}MPI_BOOT_DEVICE_ENCLOSURE_SLOT, * PMPI_BOOT_DEVICE_ENCLOSURE_SLOT;

typedef struct _MPI_BIOS_PAGE2_BOOT_DEVICE{
    MPI_BOOT_DEVICE_ADAPTER_ORDER           AdapterOrder; 
    MPI_BOOT_DEVICE_ADAPTER_NUMBER          AdapterNumber;
    MPI_BOOT_DEVICE_PCI_ADDRESS             PciAddress;
    MPI_BOOT_DEVICE_PCI_SLOT_ADDRESS        PciSlot;
    MPI_BOOT_DEVICE_FIBRE_CHANNEL_WHN       FibreChannelWhn;
    MPI_BOOT_DEVICE_SAS_WHN                 SasWhn;
    MPI_BOOT_DEVICE_ENCLOSURE_SLOT          EnclosureSlot;
}MPI_BIOS_PAGE2_BOOT_DEVICE, * PMPI_BIOS_PAGE2_BOOT_DEVICE;

typedef struct _MPI_CONFIGURATION_PAGE_BIOS2{
    CONFIGURATION_PAGE_HEADER       Pageheader;
    MPIU32                          Rsv1[6];
    MPIU8                           BootDeviceForm;
    MPIU8                           PreviousBootDeviceForm;
    MPIU16                          Rsv2;
    MPI_BIOS_PAGE2_BOOT_DEVICE      BootDevice;
}MPI_CONFIGURATION_PAGE_BIOS2, * PMPI_CONFIGURATION_PAGE_BIOS2;

//Crazy, I Was Crazy Once.
//I Locked Myself In A Room.
//A Room With A Mpi Fusion Specification.
//And The Mpi Fusion Specification Made Me Crazy...

typedef struct _CONFIGURATION_PAGE_BIOS4{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU64                      ResBaseWWID;
}CONFIGURATION_PAGE_BIOS4, * PCONFIGURATION_PAGE_BIOS4;

typedef struct _CONFIGURATION_PAGE_SCSI_PORT0{
    CONFIGURATION_PAGE_HEADER   PageHeader;
    MPIU32                      Cap;
    MPIU32                      PI;
}CONFIGURATION_PAGE_SCSI_PORT0, * PCONFIGURATION_PAGE_SCSI_PORT0;

//1496

#pragma pack(pop)
#endif //_MPI_CONFIGURATION_H
