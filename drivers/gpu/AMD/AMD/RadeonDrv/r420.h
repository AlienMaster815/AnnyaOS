#ifndef _R420_H
#define _R420_H

#include <LouDDK.h>
#include "Radeon.h"


#define R_000lF8_MC_INDEX            0x0001F8
#define R_0001FC_MC_INDEX_DATA            0x0001FC
#define  S_0001F8_MC_INDEX_ADDRESS(x)(((x) & 0x7F) << 8)
#define  S_0001F8_MC_INDEX_WR_ENNABLE(x)(((x) & 0x01) << 8)

#endif