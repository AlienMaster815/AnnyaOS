#ifndef _HDA_PCI_H
#define _HDA_PIC_H

//Intel HDA PCI Device IDs
#define HDA_CPT                 0x1C20
#define HDA_PBG                 0x1D20
#define HDA_PPT                 0x1E20
#define HDA_LPT                 0x8C20
#define HDA_9_SERIES            0x8CA0
#define HDA_WBG0                0x8D20
#define HDA_WBG1                0x8D21
#define HDA_LBG0                0xA1F0
#define HDA_LBG1                0xA270
#define HDA_LPT0                0x9C20
#define HDA_LPT1                0x9C21
#define HDA_WPT_LP              0x9CA0
#define HDA_SKL                 0xA170
#define HDA_KBL                 0xA171
#define HDA_KBL_LP              0x9D71
#define HDA_KBL_H               0xA2F0
#define HDA_CNL_H               0xA348
#define HDA_CNL_LP              0x9DC8
#define HDA_CML_LP              0x02C8
#define HDA_CML_H               0x06C8
#define HDA_RKL_S               0xF1C8
#define HDA_CML_S               0xA3F0
#define HDA_CML_R               0xF0C8
#define HDA_ICL_LP              0x34C8
#define HDA_ICL_H               0x3DC8
#define HDA_ICL_N               0x38C8
#define HDA_JSL_N               0x4DC8
#define HDA_TGL_LP              0xA0C8
#define HDA_DG1                 0x490D
#define HDA_DG2_0               0x4F90
#define HDA_DG2_1               0x4F91
#define HDA_DG2_2               0x4F92
#define HDA_ADL_S               0x7AD0
#define HDA_ADL_P               0x51C8
#define HDA_ADL_PS              0x51C9
#define HDA_ADL_PX              0x51CD
#define HDA_ADL_M               0x51CC
#define HDA_ADL_N               0x53C8
#define HDA_EHL_0               0x4B55
#define HDA_EHL_3               0x4B58
#define HDA_RPL_S               0x7A50
#define HDA_RPL_P0              0x51CA
#define HDA_RPL_P1              0x51CB
#define HDA_RPL_M               0x51CE
#define HDA_RPL_PX              0x51CF
#define HDA_MTL                 0x7E28
#define HDA_BMG                 0xE2F7
#define HDA_LNL_P               0xA828
#define HDA_ARL_S               0x7F50
#define HDA_ARL                 0x7728
#define HDA_PTL                 0xE428
#define HDA_PTL_H               0xE328
#define HDA_APL                 0x5A98
#define HDA_GML                 0x3198
#define HDA_HASWELL0            0x0A0C
#define HDA_HASWELL2            0x0C0C
#define HDA_HASWELL3            0x0D0C
#define HDA_BROADWELL           0x160C
#define HDA_5_3400_SERIES0      0x3B56
#define HDA_5_3400_SERIES1      0x3B57
#define HDA_POULSBO             0x811B
#define HDA_OAKTRAIL            0x080A
#define HDA_BAYTRAIL            0x0F04
#define HDA_BRASWELL            0x2284
#define HDA_ICH6                0x2668
#define HDA_ICH7                0x27D8
#define HDA_ESB2                0x629A
#define HDA_ICH8                0x284B
#define HDA_ICH9_0              0x293E
#define HDA_ICH9_1              0x293F
#define HDA_ICH10_0             0x3A3E
#define HDA_ICH10_1             0x3A6E
#define HDA_LOONGSON            0x7A07
#define HDMI_LOONGSON           0x7A37

//pci identification Flags
//INTEL
#define AZX_DRIVER_PCH                          1
#define AZX_DCAPS_INTEL_PCH_NO_POWER_MANAGEMENT 1 << 1
#define AZX_DCAPS_INTEL_PCH                     1 << 2
#define AZX_DCAPS_SKYLAKE                       1 << 3
#define AZX_DRIVER_SKYLAKE                      1 << 4
#define AZX_DCAPS_INTEL_LNL                     1 << 5
#define AZX_DCAPS_INTEL_BROXTON                 1 << 6
#define AZX_DRIVER_HDMI                         1 << 7
#define AZX_DCAPS_INTEL_HASWELL                 1 << 8
#define AZX_DCAPS_INTEL_BRODWELL                1 << 9
#define AZX_DRIVER_SCH                          1 << 10
#define AZX_DCAPS_INTEL_PCH_BASE                1 << 11
#define AZX_DCAPS_POSFIX_LPIB                   1 << 12
#define AZX_DCAPS_INTEL_BAYTRAIL                1 << 13
#define AZX_DCAPS_INTEL_BRASWELL                1 << 14
#define AZX_DRIVER_ICH                          1 << 15
#define AZX_DCAPS_INTEL_ICH                     1 << 16
#define AZX_DCAPS_NO_ALIGN_BUFSIZE              1 << 17

#define INTEL_HDA_CLASS     0x04
#define INTEL_HDA_SUB_CLASS 0x03

//ATI/AMD
#define AZX_DRIVER_ATI                          1 << 18
#define AZX_DECAPS_ATI_SB                       1 << 19
#define AZX_DRIVER_GENERIC                      1 << 20
#define AZX_DECAPS_AMD_SB                       1 << 21
#define AZX_DECAPS_POWER_MANAGEMENT_RUNTIME     1 << 22
#define AZX_DRIVER_ATI_HDMI_NS                  1 << 23
#define AZX_DECAPS_ATI_HDMI                     1 << 24
#define AZX_DECAPS_ATI_HDMI_NS                  1 << 25

//glenfly
#define AZX_DRIVER_GLENFY_HDMI                  1 << 26
#define AZX_DCAPS_NO_64BIT                      1 << 27
#define AZX_DCAPS_NO_MSI                        1 << 28

//VIA 
#define AZX_DRIVER_VIA                          1 << 29

//SI
#define AZX_DRIVER_SIS                          1 << 30
#define AZX_DRIVER_ULI                          1 << 31

//NVIDIA
#define AZX_DRIVER_NVIDIA                       1 << 32
#define AZX_DCAPS_NVIDIA                        1 << 33

//TERADICA
#define AZX_DRIVER_TERADICA                     1 << 34

//CTHDA
#define AZX_DRIVER_CTHDA                        1 << 35
#define AZX_DCAPS_CTHDA                         1 << 36

//CREATIVE
#define AZX_DRIVER_CREATIVE                     1 << 37
#define AZX_DCAPS_CREATIVE                      1 << 38

//CMEDIA
#define AZX_DRIVERS_CMEDIA                      1 << 39
#define AZX_DCAPS_SNOOP_OFF                     1 << 40

//ZHAOXIN
#define AZX_DRIVER_ZHAOXIN                      1 << 41

#define AZX_DRIVER_LOONGSON                     1 << 42
#define AZX_DECAPS_NO_TCSEL                     1 << 43

#endif //_HDAPCI_H