#ifndef _RAM_ALLOCATION_TABLE_API_H
#define _RAM_ALLOCATION_TABLE_API_H

#include <cstdint.h>

BOOLEAN LouKeRatIsAddressFreeEx(PVOID Address, SIZE Size, UINTPTR* EndofAllocations);
void LouKeRatFreeAddress(UINTPTR Address);
BOOLEAN LouKeRatIsAddressFree(PVOID Address, SIZE Size);
PVOID LouKeRatAllocate32BitPhysicalAddress(SIZE Size, SIZE Alignment);
PVOID LouKeRatAllocate64BitPhysicalAddress(SIZE Size, SIZE Alignment);
PVOID LouKeRatAllocateVirtualAddress(SIZE Size, SIZE Alignment);
BOOLEAN LouKeRatReserveMemoryRegion(PVOID RegionBase, SIZE RegionSize);

#endif