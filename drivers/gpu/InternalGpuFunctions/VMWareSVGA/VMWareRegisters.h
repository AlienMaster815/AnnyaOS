//  Tyler Grenier : GPL-2
//  Copyright (c) 2024 : All Rights Reserved
//  Register Header For The Internal Lousine VMWare
//  SVGA Drivers

#ifndef VMWARE_REG_H
#define VMWARE_REG_H

#include <LouDDK.h>

typedef struct _SVGA_GUEST_MEMORY_DESCRIPTOR{
    uint32_t PPM;
    uint32_t NumberOfPages;
}SVGA_GUEST_MEMORY_DESCRIPTOR,* PSVGA_GUEST_MEMORY_DESCRIPTOR ;

typedef struct _SVGA_FIFI_COMMAND_FENCE{
    uint32_t Fence;
}SVGA_FIFI_COMMAND_FENCE, * PSVGA_FIFI_COMMAND_FENCE;

#define SVGA_SYNC_GENERIC  1
#define SVGA_SYNC_FIFOFALL 2

#include "VMWareInclude/SVGA3DRegisters.h"

#endif