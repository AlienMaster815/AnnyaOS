#ifndef _LOUDDK_H
#define _LOUDDK_H

#include <Modulation.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WINAPI __stdcall

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

//Include API Headers
#include <cstdint.h>
#include <drivers/PciIds.h>
#include <cstdlib.h>
#include <kernel/loustatus.h>


#define SYSV_CONVENTION __attribute__((sysv_abi))
#define NAKED_FUNCTION __attribute__((naked))

#include <cstdio.h>
#include <string.h>
#include <fstream.h>
#include <WinAPI/Win32/winnt.h>
#include <WinAPI/Win32/winternl.h>
#include <WDK/Loader.h>
#include <Devices.h>
#include <kernel/memmory.h>
#include <kernel/gdt.h>
#include <kernel/Clock.h>
#include <kernel/errors.h>
#include <kernel/interrupts.h>
#include <kernel/pic.h>
#include <kernel/ports.h>
#include <kernel/Timers.h>
#include <kernel/SystemCalls.h>
#include <kernel/Binarys.h>
#include <kernel/exec.h>
#include <DRSD.h>
#include <kernel/Process.h>
#include <Ldm.h>
#include <drivers/FileSystem.h>
#include <drivers/hardrive.h>
#include <drivers/pci.h>
#include <drivers/Vendors/VendorsDictionary.h>
#include <bootloader/grub/multiboot.h>
#include <CPUInstructionSet/CPURegisters.h>
#include <Random.h>
#include <geometry.h>
#include <stdarg.h>
#include <Hal.h>
#include <math.h>
#include <kernel/threads.h>
#include <ListManagement.h>
#include <kernel/LouQs.h>
#include <drivers/Scsi/Sam5.h>
#include <drivers/Ata/ata.h>
#include <WinTEB.h>
#include <drivers/Processors.h>
#include <kernel/Firmware.h>
#include <kernel/KernelPm.h>
#include <kernel/XArray.h>
#include <Dispatching.h>
#include <drivers/Busses.h>
#include <kernel/Objects.h>
#include <drivers/Ecam.h>
#include <kwstring.h>
#include <WinAPI/Win32/winnls.h>
#include <Coff.h>
#include <LouLoad.h>
#include <Power.h>
#include <kernel/Events.h>
#include <drivers/fpu.h>
#include <kernel/LKPCB.h>
#include <kernel/LouAccessTokens.h>
#include <Riff.h>
#include <Security.h>
#include <kernel/LazyAllocations.h>
#include <kernel/Stack.h>
#include <WinAPI/Win32/GdiCore.h>
#include <LKDM.h>
#include <drivers/FileSystems/ISO.h>
#include <Time.h>
#include <kernel/Rcu.h>
#include <kernel/Services.h>

#include <IoCtl.h>
#include <kernel/Sections.h>
#include <kernel/States.h>
#include <USRSPC/Heap.h>
#include <USRSPC/Syncapi.h>

#ifndef KERNEL_MAIN_FILE
EXTERNAL LOUSINE_LOADER_INFO KernelLoaderInfo;
#endif

#ifndef _USER_MODE_CODE_

#define ACPIBUFFER 512
#define ERRMAPPINGIO -1

KERNEL_EXPORT 
uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

#ifndef _KERNEL_MODULE_

#endif
#endif
#ifdef __cplusplus
}
#endif
#endif