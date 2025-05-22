#ifndef _AMD_BASIC_GPU_H
#define _AMD_BASIC_GPU_H

#include <LouDDK.h>

#define TAHITTI_CHIP            (uint32_t)1
#define PITCARIN_CHIP           (uint32_t)2
#define OLAND_CHIP              (uint32_t)3
#define VERDE_CHIP              (uint32_t)4
#define HAINAN_CHIP             (uint32_t)5
#define KAVERI_CHIP             (uint32_t)6
#define BONAIRE_CHIP            (uint32_t)7
#define HAWAII_CHIP             (uint32_t)8
#define KABINI_CHIP             (uint32_t)9
#define MULLINS_CHIP            (uint32_t)10
#define TOPAZ_CHIP              (uint32_t)11
#define TONGA_CHIP              (uint32_t)12
#define FIJI_CHIP               (uint32_t)13
#define CARIZO_CHIP             (uint32_t)14
#define STONEY_CHIP             (uint32_t)15
#define POLARIS11_CHIP          (uint32_t)16
#define POLARIS10_CHIP          (uint32_t)17
#define POLARIS12_CHIP          (uint32_t)18
#define VEGAM_CHIP              (uint32_t)19
#define VEGA10_CHIP             (uint32_t)20
#define VEGA12_CHIP             (uint32_t)21
#define VEGA20_CHIP             (uint32_t)22
#define RAVEN_CHIP              (uint32_t)23
#define ARCTURUS_CHIP           (uint32_t)24
#define NAVI10_CHIP             (uint32_t)25
#define NAVI14_CHIP             (uint32_t)26
#define RENOIR_CHIP             (uint32_t)27
#define NAVI12_CHIP             (uint32_t)28
#define SIENNA_CICHLID_CHIP     (uint32_t)29
#define YELLOW_CARP_CHIP        (uint32_t)30
#define NAVY_FLOUNDER_CHIP      (uint32_t)31
#define DIMGREY_CAVEFISH_CHIP   (uint32_t)32
#define ALDEBARAN_CHIP          (uint32_t)33
#define CYAN_SKILLFISH_CHIP     (uint32_t)34
#define BEIGE_GOBY_CHIP         (uint32_t)35
#define IP_DISCOVERY_CHIP       (uint32_t)36


enum radeon_family {
	CHIP_R100 = 0,
	CHIP_RV100,
	CHIP_RS100,
	CHIP_RV200,
	CHIP_RS200,
	CHIP_R200,
	CHIP_RV250,
	CHIP_RS300,
	CHIP_RV280,
	CHIP_R300,
	CHIP_R350,
	CHIP_RV350,
	CHIP_RV380,
	CHIP_R420,
	CHIP_R423,
	CHIP_RV410,
	CHIP_RS400,
	CHIP_RS480,
	CHIP_RS600,
	CHIP_RS690,
	CHIP_RS740,
	CHIP_RV515,
	CHIP_R520,
	CHIP_RV530,
	CHIP_RV560,
	CHIP_RV570,
	CHIP_R580,
	CHIP_R600,
	CHIP_RV610,
	CHIP_RV630,
	CHIP_RV670,
	CHIP_RV620,
	CHIP_RV635,
	CHIP_RS780,
	CHIP_RS880,
	CHIP_RV770,
	CHIP_RV730,
	CHIP_RV710,
	CHIP_RV740,
	CHIP_CEDAR,
	CHIP_REDWOOD,
	CHIP_JUNIPER,
	CHIP_CYPRESS,
	CHIP_HEMLOCK,
	CHIP_PALM,
	CHIP_SUMO,
	CHIP_SUMO2,
	CHIP_BARTS,
	CHIP_TURKS,
	CHIP_CAICOS,
	CHIP_CAYMAN,
	CHIP_ARUBA,
	CHIP_TAHITI,
	CHIP_PITCAIRN,
	CHIP_VERDE,
	CHIP_OLAND,
	CHIP_HAINAN,
	CHIP_BONAIRE,
	CHIP_KAVERI,
	CHIP_KABINI,
	CHIP_HAWAII,
	CHIP_MULLINS,
};

#define RADEON_MOBILE       (uint32_t)(1 << 31)
#define APU_AMD_DEV         (uint32_t)(1 << 30)
#define RADEON_NEW_MEMMAP   (uint32_t)(1 << 29)
#define RADEON_IS_IGP       (uint32_t)(1 << 28)
#define RADEON_IS_IGPGART   (uint32_t)(1 << 27)
#define RADEON_SINGLE_CRTC  (uint32_t)(1 << 26)
#define RADEON_IS_AGP       (uint32_t)(1 << 25)
#define RADEON_IS_PCIE      (uint32_t)(1 << 24)
#define RADEON_IS_PCI       (uint32_t)(1 << 23)
#define RADEON_FAMILY_BITS 0xFF

#include <Hal.h>

#endif//Basic AMD GPU_H