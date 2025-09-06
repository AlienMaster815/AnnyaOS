#ifndef _ECAM_H
#define _ECAM_H
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C"{
#endif


typedef struct _PCIE_ECAM_DEVICE{
    ListHeader      Peers;
    UINTPTR         Phys;
    UINTPTR         Virt;
    UINT16          Group;
    UINT8           StartBus;
    UINT8           EndBus;
}PCIE_ECAM_DEVICE, * PPCIE_ECAM_DEVICE;

#define ECAM_DMA_MEMORY_FLAGS ((1ULL << 0) | (1ULL << 1) | (1ULL << 3) | (1ULL << 4))

static inline PVOID 
PcieCalculateFunctionBase(PVOID Base, UINT8 Bus, UINT8 Device, UINT8 Function){
    return (PVOID)((UINTPTR)Base
        + ((UINTPTR)Bus     << 20) // Bus × 1MB
        + ((UINTPTR)Device  << 15) // Device × 32KB
        + ((UINTPTR)Function << 12)); // Function × 4KB
}

#define PcieCalculateDeviceBase(x, y, z) PcieCalculateFunctionBase(x, y, z, 0)

#ifdef __cplusplus
}
#endif
#endif