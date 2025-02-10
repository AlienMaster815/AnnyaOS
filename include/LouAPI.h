
#ifndef LOUAPI_H
#define LOUAPI_H

//Include API Headers

#include <stdlib.h>

#include <stdint.h>
#include <stat.h>
#include <stdio.h>
#include <string.h>
#include <Time.h>
#include <fstream.h>
#include <KernelAPI/KernelAPI.h>
#include <kernel/kernel.h>
#include <drivers/drivers.h>
#include <bootloader/grub/multiboot.h>
#include <CPUInstructionSet/CPURegisters.h>

#include "WinAPI/NtAPI/ntstatus.h"

#include <Random.h>

#include <windows.h>
#include <geometry.h>
#include <SharedTypes.h>
#include "NtOsKrnlLib.h"

#include <FileHandleing/Bitmap.h>
//#include <Hal.h>
#include <math.h>
#include <kernel/threads.h>
#include <kernel/LouQs.h>
#include "drivers/Scsi/ScsiHost.h"
#include "drivers/Ata/ata.h"
#include <drivers/Networking/IpV4.h>


#ifndef _KERNEL_MODULE_

#define ACPIBUFFER 512
#define ERRMAPPINGIO -1

typedef void* FILE;

#define CPU_TO_LE32(x) ((uint32_t)(             \
    (((uint32_t)(x) & 0x000000FFU) << 24) |     \
    (((uint32_t)(x) & 0x0000FF00U) << 8)  |     \
    (((uint32_t)(x) & 0x00FF0000U) >> 8)  |     \
    (((uint32_t)(x) & 0xFF000000U) >> 24)))

LOUSTATUS RegisterHardwareInterruptHandler(void(*InterruptHandler)(uint64_t), uint8_t PIN, bool ExtraRegisterSave);
void HardwareInterruptManager();
typedef void* EventHandle;

#else //Kernel Module

#endif
#endif
