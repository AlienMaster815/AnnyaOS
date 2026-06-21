//Copyright (2026) GPL-2 Tyler Grenier
#ifndef _CSTDLIB_H
#define _CSTDLIB_H

#include "cstdint.h"

#define LIMINE_REQUEST          __attribute__((used, section(".limine_requests"))) static volatile
#define LIMINE_REQUEST_START    __attribute__((used, section(".limine_requests_start"))) static volatile
#define LIMINE_REQUEST_END      __attribute__((used, section(".limine_requests_end"))) static volatile

void* memcpy(PVOID Dest, PCVOID Src, SIZE Size);
PVOID memset(PVOID Dest, int Val, SIZE Size);
int memcmp (void *VBuffer1, void *VBuffer2, UINT64 Count);


#endif