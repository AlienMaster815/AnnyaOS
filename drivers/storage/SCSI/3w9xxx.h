#include <LouDDK.h>

#ifndef _3W9XXX_H_
#define _3W9XXX_H_

typedef struct _TWA_MESSAGE_TYPE{
    uint32_t Code;
    string   Text;
}TWA_MESSAGE_TYPE, * PTWA_MESSAGE_TYPE;

#define NUMBER_OF_TWA_AEN_MESSAGES 70
#define NUMBER_OF_TWA_ERROR_MESSGES 112
#define NUMBER_OF_SEVERITY_MESSAGES 5

UNUSED static char* TWA_SEVERITY_TABLE[NUMBER_OF_SEVERITY_MESSAGES] = {
    "NONE",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
};

UNUSED static TWA_MESSAGE_TYPE TWA_AEN_TABLE[NUMBER_OF_TWA_AEN_MESSAGES] = {
    {0x0000, "AEN QUEUE EMPTY"},                                        //1 : 0
    {0x0001, "Controller Reset Occured"},                               //2 : 1
    {0x0002, "Degraded Unit Detected"},                                 //3 : 2
    {0x0003, "Controller Error Occurred"},                              //4 : 3
    {0x0004, "Background Rebuild Failed"},                              //5 : 4
    {0x0005, "Background Rebuild Finished"},                            //6 : 5
    {0x0006, "Incomplete Unit Detected"},                               //7 : 6
    {0x0007, "Background Initialization Done"},                         //8 : 7
    {0x0008, "Unclean Shutdown Detected"},                              //9 : 8
    {0x0009, "Drive Timeout Detected"},                                 //10 : 9
    {0x000A, "Driver Error Detected"},                                  //11 : 10
    {0x000B, "Rebuild Started"},                                        //12 : 11
    {0x000C, "Background initialization Started"},                      //13 : 12
    {0x000D, "Entire Logical Unit Was Deleted"},                        //14 : 13
    {0x000E, "Background Initialization Failed"},                       //15 : 14
    {0x000F, "SMART Attribute Exceeded Threshold"},                     //16 : 15
    {0x0010, "Power Supply Reported AC Under Acceptable Range"},        //17 : 16
    {0x0011, "Power Supply Reported DC Out Of Acceptable Range"},       //18 : 17
    {0x0012, "Power Supply Reported A Malfunction"},                    //19 : 18
    {0x0013, "Power Supply Predicted A Malfunction"},                   //20 : 19
    {0x0014, "Battery Charge Is Below Threshold"},                      //21 : 20
    {0x0015, "Fan Speed is Below Threshold"},                           //22 : 21
    {0x0016, "Temperature Sensor is Above Threshold"},                  //23 : 22
    {0x0017, "Power Supply Was Removed"},                               //24 : 23
    {0x0018, "Power Supply Was Inserted"},                              //25 : 24
    {0x0019, "Drive Was Removed From A Bay"},                           //26 : 25
    {0x001A, "Drive Was Inserted Into Bay"},                            //27 : 26
    {0x001B, "Drive Bay Cover Door Was opened"},                        //28 : 27
    {0x001C, "Drive Bay Cover Door Was Closed"},                        //29 : 28
    {0x001D, "Product Case Was Opened"},                                //30 : 29
    {0x0020, "Prepare For Power Down"},                                 //31 : 30
    {0x0021, "Downgrade UDMA To Lower Speed"},                          //32 : 31
    {0x0022, "Upgrade UDMA Mode To Higher Speed"},                      //33 : 32
    {0x0023, "Sector Repair Completed"},                                //34 : 33
    {0x0024, "SBUF Memory Test Failed"},                                //35 : 34
    {0x0025, "Error Flushing Cached Write Data To Array"},              //36 : 35
    {0x0026, "Drive Reported Data ECC Error"},                          //37 : 36
    {0x0027, "DCB Has Checksum Error"},                                 //38 : 37
    {0x0028, "DCB Version Is Unsupported"},                             //39 : 38
    {0x0029, "Background Verify Started"},                              //40 : 39
    {0x002A, "Background Verify Failed"},                               //41 : 40
    {0x002B, "Background Verify Done"},                                 //42 : 41
    {0x002C, "Bad Sector Over Written Durring Build"},                  //43 : 42
    {0x002D, "Background Rebuild Error On Source Drive"},               //44 : 43
    {0x002E, "Replace Failed Because Replacement Drive Too small"},     //45 : 44
    {0x002F, "Verify Failed Because Array Was Never Initialized"},      //46 : 45
    {0x0030, "Unsupported ATA Drive"},                                  //47 : 46
    {0x0031, "Syncronize Host/Controller Time"},                        //48 : 47
    {0x0032, "Spare Capacity Is Inadequate For Some Units"},            //49 : 48 
    {0x0033, "Background Migration Started"},                           //50 : 49
    {0x0034, "Background Migration Failed"},                            //51 : 50
    {0x0035, "Background Migration Done"},                               //52 : 51
    {0x0036, "Verify Detected And Fixed Data/Parity Mismatch"},         //53 : 52
    {0x0037, "SO-DIMM Incompatible"},                                   //54 : 43
    {0x0038, "SO-DIMM Not Detected"},                                   //55 : 54
    {0x0039, "Corrected SBUF ECC Error"},                               //56 : 55
    {0x003A, "Drive Power On Reset Detected"},                          //57 : 56     
    {0x003B, "Background Rebuild Paused"},                              //58 : 57
    {0x003C, "Background Initializeation Paused"},                      //59 : 58
    {0x003D, "Background Verify Paused"},                               //60 : 59
    {0x003E, "Background Migration Paused"},                            //61 : 60
    {0x003F, "Corrupt Flash File System Detected"},                     //62 : 61
    {0x0040, "Flash File System Repaired"},                             //63 : 62
    {0x0041, "Unit Number Assignment Were lost"},                       //64 : 63
    {0x0042, "Error Durring Last Read Of DCB"},                         //65 : 64
    {0x0043, "Latent Error Found In Backup DCB"},                       //66 : 65
    {0x00FC, "Recovered/Finished Array Membership Update"},             //67 : 66
    {0x00FD, "Handler Lock Up"},                                        //68 : 67
    {0x00FE, "Retrying Pci Transfer"},                                  //69 : 68
    {0x00FF, "AEN Queue Is Full"},                                      //70 : 69   
};

UNUSED static TWA_MESSAGE_TYPE TWA_ERROR_TABLE[NUMBER_OF_TWA_ERROR_MESSGES] = {
    {0x0100, "SGL Entry Contains Zero Data"},                                   //1 : 0
    {0x0101, "Invalid Command Opcode"},                                         //2 : 1
    {0x0102, "SGL Entry Has Unaligned Address"},                                //3 : 2
    {0x0103, "SGL Size Does Not Match Command"},                                //4 : 3
    {0x0104, "SGL Entry Has Illegal Length"},                                   //5 : 4
    {0x0105, "Command Packet Is Not Aligned"},                                  //6 : 5
    {0x0106, "Invalid Request ID"},                                             //7 : 6
    {0x0107, "Duplicate Request ID"},                                           //8 : 7
    {0x0108, "ID Not Locked"},                                                  //9 : 8
    {0x0109, "Lba Out Of Range"},                                               //10 : 9
    {0x010A, "Logical Unit not Supported"},                                     //11 : 10
    {0x010B, "Parameter Table Does Not Exist"},                                 //12 : 11
    {0x010C, "Parameter Index Does Not Exist"},                                 //13 : 12
    {0x010D, "Invalid Field In CDB"},                                           //14 : 13
    {0x010E, "Specific Port Has Invalid Drive"},                                //15 : 14
    {0x010F, "Parameter Index Does Not Exist"},                                 //16 : 15
    {0x0110, "Failed Memory Allocation"},                                       //17 : 16
    {0x0111, "Memory Request To Large"},                                        //18 : 17
    {0x0112, "Out Of Memory Segments"},                                         //19 : 18
    {0x0113, "Invalid Address To DeAllocate"},                                  //20 : 19
    {0x0114, "Out Of Memory"},                                                  //21 : 20
    {0x0115, "Out Of Heap"},                                                    //22 : 21
    {0x0120, "Double Degrade"},                                                 //23 : 22
    {0x0121, "Drive Not Degraded"},                                             //24 : 23
    {0x0122, "Re Construct Error"},                                             //25 : 24
    {0x0123, "Replace Not Accepted"},                                           //26 : 25
    {0x0124, "Replace Drive Copacity To Small"},                                //27 : 26
    {0x0125, "Sector Count Not Allowed"},                                       //28 : 27
    {0x0126, "No Spares Left"},                                                 //29 : 28
    {0x0127, "Re Constructy Error"},                                            //30 : 29
    {0x0128, "Unit Is Offline"},                                                //31 : 30
    {0x0129, "Cannot Update Status To DBC"},                                    //32 : 31
    {0x0130, "Invalid Stripe Handle"},                                          //33 : 32
    {0x0131, "Handle That Was Not Locked"},                                     //34 : 33
    {0x0132, "Handle That Was Not Empty"},                                      //35 : 34
    {0x0133, "Handle Has A Different Owner"},                                   //36 : 35
    {0x0140, "IPR Has Parrent"},                                                //37 : 36
    {0x0150, "Illegal PBUF Address Alignment"},                                 //38 : 37
    {0x0151, "Illegal PBUF Transfer Length"},                                   //39 : 38
    {0x0152, "Illegal SBUF Address Alignment"},                                 //40 : 39
    {0x0153, "Illegal SBUF Transfer Length"},                                   //41 : 40
    {0x0160, "Command Packet Too Large"},                                       //42 : 41
    {0x0161, "SGL Exceedes Maximum Length"},                                    //43 : 42
    {0x0162, "SGL Has Too Many Entries"},                                       //44 : 43
    {0x0170, "Insufficent Resources For Rebuilder"},                            //45 : 44
    {0x0171, "Verify error Data Does Not Equal Parity"},                        //46 : 45
    {0x0180, "Requested Segment Not in Directory Of This DCB"},                 //47 : 46
    {0x0181, "DCB Segment Has Unsupported Version"},                            //48 : 47
    {0x0182, "DCB Segment Has Checksum Error"},                                 //49 : 48
    {0x0183, "DCB Support Setting Segment Invalid"},                            //50 : 49
    {0x0184, "DCB UDB Segment Invalid"},                                        //51 : 50
    {0x0185, "DCB GUID Segment Invalid"},                                       //52 : 51
    {0x01A0, "Could Not Clear SBUF"},                                           //53 : 52
    {0x01C0, "Flash Identify Failed"},                                          //54 : 53
    {0x01C1, "Flash Out Of Bounds"},                                            //55 : 54
    {0x01C2, "Flash Verify Error"},                                             //56 : 55
    {0x01C3, "Flash File Object Not Found"},                                    //57 : 56
    {0x01C4, "Flash File Already Present"},                                     //58 : 57
    {0x01C5, "Flash File System Full"},                                         //59 : 58
    {0x01C6, "Flash File Not Present"},                                         //60 : 59
    {0x01C7, "Flash File Size Error"},                                          //61 : 60
    {0x01C8, "Bad Flash File Checksum"},                                        //62 : 61
    {0x01CA, "Corrupt Flash File System Detected"},                             //63 : 62
    {0x01D0, "Invalid Field In Parameter List"},                                //64 : 63
    {0x01D1, "Parameter List Length Error"},                                    //65 : 64
    {0x01D2, "Parameter Item Is Not Changeable"},                               //66 : 65
    {0x01D3, "Parameter Item Is Not Saveable"},                                 //67 : 66
    {0x0200, "UDMA CRC Error"},                                                 //68 : 67
    {0x0201, "Internal CRC Error"},                                             //69 : 68 
    {0x0202, "Data ECC Error"},                                                 //70 : 69
    {0x0203, "ADP Level 1 Error"},                                              //71 : 70
    {0x0204, "Port Timeout"},                                                   //72 : 71
    {0x0205, "Drive Power On Reset"},                                           //73 : 72
    {0x0206, "ADP Level 2 Error"},                                              //74 : 73
    {0x0207, "Software Reset Failed"},                                          //75 : 74
    {0x0208, "Drive Not Ready"},                                                //76 : 75
    {0x0209, "Unclasified Port Error"},                                         //77 : 76
    {0x020A, "Drive Aborted Command"},                                          //78 : 77
    {0x0210, "Internal CRC Error"},                                             //79 : 78
    {0x0211, "PCI Abort Error"},                                                //80 : 79
    {0x0212, "PCI Parity Error"},                                               //81 : 80
    {0x0213, "Port Handler Error"},                                             //82 : 81
    {0x0214, "Token Interruot Count Error"},                                    //83 : 82
    {0x0215, "Timeout Waiting For PCI Transfer"},                               //84 : 83
    {0x0216, "Corrected Buffer ECC"},                                           //85 : 84
    {0x0217, "Uncorrected Buffer ECC"},                                         //86 : 85
    {0x0230, "Unsupported Command Durring Flash Recovery"},                     //87 : 86
    {0x0231, "Next Image Buffer Ecspected"},                                    //88 : 87
    {0x0232, "Binary Image Architecture Incompatible"},                         //89 : 88
    {0x0233, "Binary Image Has No Signature"},                                  //90 : 89
    {0x0234, "Binary Image Has Bad Checksum"},                                  //91 : 90
    {0x0235, "Image Downloaded Overflowed Buffer"},                             //92 : 91
    {0x0240, "I2C Device Not Found"},                                           //93 : 92
    {0x0241, "I2C Transaction Aborted"},                                        //94 : 93
    {0x0242, "SO-DIMM Parameters Incompatible Using Defaults"},                 //95 : 94
    {0x0243, "SO-DIMM Unsupported"},                                            //96 : 95
    {0x0248, "SPI Transfer Status Error"},                                      //97 : 96
    {0x0249, "SPI Transfer Timeout Error"},                                     //98 : 97
    {0x0250, "Invalid Descriptor Size In  CreateUnit"},                         //99 : 98
    {0x0251, "Unit Descriptor Size Ecxeeds Data Buffer In CreateUnit"},         //100 : 99
    {0x0252, "Invalid Value In CreateUnit Descriptor"},                         //101 : 100
    {0x0253, "Inadequate Disk Space To Support Descriptor In Create Unit"},     //102 : 101
    {0x0254, "Unable To Create Data Channel For This Unit Descriptor"},         //103 : 102
    {0x0255, "CreateUnit Descriptor Describes Drive Already In Use"},           //104 : 103
    {0x0256, "Unable To Write Configuration To All Disks Durring CreateUnit"},  //105 : 104
    {0x0257, "CreateUnit Does Not Support This Descriptor Version"},            //106 : 105
    {0x0258, "Invalid Sub Unit For Raid 0 Or 5 In Create Unit"},                //107 : 106
    {0x0259, "Too Many Descriptors In CreateUnit"},                             //108 : 107
    {0x025A, "Invalid Configuration For CreateUnit Descriptor"},                //109 : 108
    {0x025B, "Invalid LBA Offset For CreateUnit Descriptor"},                   //110 : 109
    {0x025C, "Invalid Striplet Size Specified In CreateUnit Descriptor"},       //111 : 110
    {0x0260, "SMART Attribute Exceeded Threshold"},                             //112 : 111
};

//Controll Bit Defs
#define TW_CONTROL_CLEAR_HOST_INTERRUPT         0x00080000
#define TW_CONTROL_CLEAR_ATTENTION_INTERRUPT    0x00040000
#define TW_CONTROL_MASK_COMMAND_INTERRUPT       0x00020000
#define TW_CONTROL_MASK_RESPONCE_INTERRUPT      0x00010000
#define TW_CONTROL_UNMASK_COMMAND_INTERRUPT     0x00008000
#define TW_CONTROL_UNMASK_RESPONCE_INTERRUPT    0x00004000
#define TW_CONTROL_CLEAR_ERROR_STATUS           0x00000200
#define TW_CONTROL_ISSUE_SOPFT_RESET            0x00000100
#define TW_CONTROL_ENABLE_INTERRUPTS            0x00000080
#define TW_CONTROL_DISABLE_INTERRUPTS           0x00000040
#define TW_CONTROL_ISSUE_HOST_INTERRUPT         0x00000020
#define TW_CONTROL_CLEAR_PRARITY_ERROR          0x00800000
#define TW_CONTROL_CLEAR_QUEUE_ERROR            0x00400000
#define TW_CONTROL_CLEAR_PCI_ABORT              0x00100000

//Status Bit Defs
#define TW_STATUS_MAJOR_VERSION_MASK            0xF0000000
#define TW_STATUS_MINOR_VERSION_MASK            0x0F000000
#define TW_STATUS_PCI_PARITY_ERROR              0x00800000
#define TW_STATUS_QUEUE_ERROR                   0x00400000
#define TW_STATUS_MICRO_CONTROLLER_ERROR        0x00200000
#define TW_STATUS_PCI_ABORT                     0x00100000
#define TW_STATUS_HOST_INTERRUPT                0x00080000
#define TW_STATUS_ATTENTION_INTERRUPT           0x00040000
#define TW_STATUS_COMMAND_INTERRUPT             0x00020000
#define TW_STATUS_RESPONCE_INTERRUPT            0x00010000
#define TW_STATUS_COMMAND_QUEUE_FULL            0x00008000
#define TW_STATUS_RESPONCE_QUEUE_EMPTY          0x00004000
#define TW_STATUS_MICRO_CONTROLLER_READY        0x00002000
#define TW_STATUS_COMMAND_QUEUE_EMPTY           0x00001000
#define TW_STATUS_EXPECTED_BITS                 0x00002000
#define TW_STATUS_UNEXPECTED_BITS               0x00F00000
#define TW_STATUS_VALID_INTERRUPT               0x00DF0000

//PCI Defs
#define TW_PCI_CLEAR_PARITY_ERRORS      0xC100
#define TW_PCI_CLEAR_PCI_ABORT          0x2000

//Command Packet Opcodes
#define TW_OP_INNITIALIZE_CONNECTION 0x01
#define TW_OP_GET_PARAMETERS         0x12
#define TW_OP_SET_PARAMETERS         0X13
#define TW_OP_EXECUTE_SCSI           0x10
#define TW_OP_DOWNLOAD_FIRMWARE      0x16
#define TW_OP_RESET                  0x1C

//AEN Codes
#define TW_AEN_QUEUE_EMPTY              0x0000
#define TW_AEN_SOFT_RESET               0x0001
#define TW_AEN_SYNC_TIME_WITH_HOST      0x0031
#define TW_AEN_SEVERIY_ERROR            0x0001
#define TW_AEN_SEVERITY_DEBUG           0x0004
#define TW_AEN_NOT_RETRIEVED            0x0001
#define TW_AEN_RETRIEVED                0x0002

//Command States
#define TW_S_INITIAL    0x01
#define TW_S_STARTED    0x02
#define TW_S_POSTED     0x04
#define TW_S_PENDING    0x08
#define TW_S_COMPLETED  0x10
#define TW_S_FINISHED   0x20

//Compatibility Design
#define TW_9000_ARCH_ID             0x05
#define TW_CURRENT_DRIVER_SRL       35
#define TW_CURRENT_DRIVER_BUILD     0
#define TW_CURRENT_DRIVER_BRANCH    0

//Misc Defines
#define TW_9550SX_DRAIN_COMPLETED           0xFFFF
#define TW_SECTOR_SIZE                      512
#define TW_ALIGNMENT_9000                   4
#define TW_ALIGNMENT_9000_SGL               0x03
#define TW_MAX_UNITS                        16
#define TW_MAX_UNITS_9650SE                 32
#define TW_INIT_MESSAGE_CREDITS             0x100
#define TW_INIT_COMMAND_PACKET_SIZE         0x03
#define TW_INIT_COMMAND_PACKET_SIZE_EXT     0x06
#define TW_EXTENDED_INIT_CONNECT            0x02
#define TW_BUNDLED_FW_SAFE_TO_FLASH         0x04
#define TW_CTLR_FW_RECOMMENDS_FLASH         0x08
#define TW_CTLR_FW_COMPATIBLE               0x02
#define TW_BASE_FW_SRL                      24
#define TW_BASE_FW_BRANCH                   0
#define TW_BASE_FW_BUILD                    1
#define TW_FW_SRL_LUNS_SUPPORTED            28
#define TW_Q_LENGTH                         256
#define TW_Q_START                          0
#define TW_MAX_SLOT                         32
#define TW_MAX_RESET_TRIES                  2
#define TW_MAX_CMDS_PER_LUN                 254
#define TW_MAX_RESPONCE_DRAIN               256
#define TW_MAX_AEN_DRAIN                    255
#define TW_IN_RESET                         2
#define TW_USING_MSI                        3
#define TW_IN_ATTENTION_LOOP                4
#define TW_MAX_SECTORS                      256
#define TW_AEN_WAIT_TIME                    1000
#define TW_IOCTL_WAIT_TIME                  1000 //1 Kiloquark
#define TW_MAX_CDB_LENGTH                   16
#define TW_ISR_DONT_COMPLETE                2
#define TW_ISR_DONT_RESULT                  3
#define TW_IOCTL_CHR_DEV_TIMEOUT            60
#define TW_IOCTL_CHR_DEV_FREE               -1
#define TW_COMMAND_OFFSET                   128
#define TW_VERSION_TABLE                    0x0402
#define TW_TIMEKEEP_TABLE                   0x040A
#define TW_INFORMATION_TABLE                0x0403
#define TW_PARAMETER_FW_VERSION             3
#define TW_PARAMETER_FW_VERSION_LENGTH      16
#define TW_PARAMETER_BIOS_VERSION           4
#define TW_PARAMETER_BIOS_VERSION_LENGTH    16
#define TW_PARAMETER_PORT_COUNT             3
#define TW_PARAMETER_PORT_COUNT_LENGTH      1
#define TW_MIN_SGL_LENGTH                   512
#define TW_MAX_SENCE_LENGTH                 256
#define TW_EVENT_SOURCES_AEN                0x1000
#define TW_EVENT_SOURCE_COMMAND             0x1001
#define TW_EVENT_SOURCE_PCHIP               0x1002
#define TW_EVENT_SOURCE_DRIVER              0x1003
#define TW_IOCTL_GET_COMPATIBILITY_INFO     0x0101
#define TW_IOCTL_GET_LAST_EVENT             0x0102
#define TW_IOCTL_GET_FIRST_EVENT            0x0103
#define TW_IOCTL_GET_NEXT_EVENT             0x0104
#define TW_IOCTL_GET_PREV_EVENT             0x0105
#define TW_IOCTL_GET_LOCK                   0x0106
#define TW_IOCTL_RELEASE_LOCK               0x0107
#define TW_IOCTL_FIRMWARE_PASS_THROUGH      0x0108
#define TW_IOCTL_ERROR_STATUS_NOT_LOCKED    0x1001
#define TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS 0x1003
#define TW_IOCTL_ERROR_STATUS_AEN_CLOBBER   0x1004
#define TW_ALLOCATION_LENGTH                128
#define TW_SENCE_DATA_LENGTH                18
#define TW_STATUS_CHECK_CONDITION           2
#define TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED 0x010A
#define TW_ERROR_UNIT_OFFLINE               0x0128
#define TW_MESSAGE_SOURCE_CONTROLLER_ERROR  3
#define TW_MESSAGE_SOURCE_CONTROLLER_EVENT  3
#define TW_MESSAGE_SOURCE_LOUSINE_DRIVER    6
#define TW_DRIVER TW_MESSAGE_SOURCE_LOUSINE_DRIVER
#define TW_MESSAGE_SOURCE_LOUSINE_KERNEL    9
#define TW_OS TW_MESSAGE_SOURCE_LOUSINE_KERNEL


//PCI IDS
#ifndef PCI_DEVICE_ID_3WARE_9000
#define PCI_DEVICE_ID_3WARE_9000    0x1002
#endif
#ifndef PCI_DEVICE_ID_3WARE_9550SX
#define PCI_DEVICE_ID_3WARE_9550SX  0x1003
#endif
#ifndef PCI_DEVICE_ID_3WARE_9650SE
#define PCI_DEVICE_ID_3WARE_9650SE  0x1004
#endif
#ifndef PCI_DEVICE_ID_3WARE_9690SA
#define PCI_DEVICE_ID_3WARE_9690SA  0x1005
#endif

//BitMasks
#define TW_OPRESS_IN(x,y) ((x << 5) | (y & 0x1F))
#define TW_OP_OUT(x) (x & 0x1F)
#define TW_OPSGL_IN(x,y) ((x << 5) | (y & 0x1F))
#define TW_SGL_OUT(x) ((x >> 5) & 0x07)
#define TW_SEV_OUT(x) (x & 0x07)
#define TW_RESID_OUT(x) ((x >> 4) & 0xFF)

#endif //_3W9XXX_H