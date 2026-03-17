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

#ifndef KERNEL_MAIN_FILE
EXTERNAL LOUSINE_LOADER_INFO KernelLoaderInfo;
#endif

#ifndef _USER_MODE_CODE_
#ifndef _KERNEL_MODULE_

#define ACPIBUFFER 512
#define ERRMAPPINGIO -1

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

#endif
#endif
#ifdef __cplusplus
}
#endif


#ifndef _GUID_TYPE
#define _GUID_TYPE
typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif





typedef void* EventHandle;

#ifdef _KERNEL_MODULE_
#pragma warning(push)
#pragma warning(disable: 4083) // Disable specific warning
#pragma warning(disable: 4005) // Disable macro redefinition warning
#pragma warning(disable: 5051) // Disable C5051 warning
#pragma warning(disable: 4103) // Disable C4103
#pragma warning(disable: 4201) // Disable C4103
#pragma warning(disable: 4200) // Disable C4103
#pragma warning(disable: 4086) // Disable C4103
#pragma warning(disable: 4100) // Disable C4103warning C4273
#pragma warning(disable: 4217) // Disable C4103 4245
#pragma warning(disable: 4245) // Disable C4103 4245
#pragma warning(disable: 4293) // Disable C4103 4245
//#pragma warning(disable: 1218) // Disable C4103
#endif


#ifdef _KERNEL_MODULE_

#ifndef PVOID
#endif


#endif


//define common used cpp functions with drivers
#include <stddef.h>
#include <drivers/Vendors/VendorsDictionary.h>
#include <kernel/memmory.h>
#include <kernel/Binarys.h>
#include <cstdio.h>

#include <kernel/interrupts.h>
#include <kernel/threads.h>
#include <DRSD.h>
#include <kernel/LouQs.h>
#include <HashTables.h>
#include <drivers/Networking/IpV4.h>
#include <WinAPI/Win32/Win32API.h>

#include <math.h>

#include <LKDM.h>

typedef void* DEVICE;

LOUAPI void LouKeInitializeIntervalWork(
    void (*DelayedFunction)(uint64_t PrivateData),
    uint64_t PrivateData,
    uint64_t MsInterval
);



#define PATADEV 1
#define PATAPIDEV 2


#define STATUS bool

//Define Each IO Manager File Seperately To Segregate Important Kernel Features


//typedef struct _LOUDDK_API {
//    uint64_t initStatus;
//}LOUDDK_API,*PLOUDDK_API;



#ifdef __cplusplus

//define kernel c functions that we translate to the cpp world
//Printing And Debugging

KERNEL_EXPORT int LouPrint(char *format, ...);
KERNEL_EXPORT LOUSTATUS RegisterHardwareInterruptHandler(void(*Handler)(uint64_t), uint8_t InterruptNumber, bool ERS);
KERNEL_EXPORT void* memcpy(void* dest, const void* src, size_t n);
KERNEL_EXPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_EXPORT int strcmp(const char* str1, const char* str2);
KERNEL_EXPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_EXPORT char* strncpy(char* dest, const char* src, size_t n);
KERNEL_EXPORT void sleep(uint64_t Time);
KERNEL_EXPORT LOUSTATUS 
LouKeWaitForUlongRegisterCondition(
    PULONG  Mmio, 
    size_t  MsWait,
    ULONG   Mask, 
    ULONG   Value
);
KERNEL_EXPORT uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);
// PORTS Stuff

#ifdef __x86_64__
    LOUAPI uint64_t read_msr(uint32_t msr_id);
#endif

#include <ListManagement.h>
#include <drivers/Lou_drivers/FileSystems/ISO.h>
#include <cstdio.h>
#include <drivers/pci.h>
#include <cstdlib.h>
#include <cstdint.h>
#include <fstream.h>
#include <Time.h>
#include <kernel/exec.h>
#include <Random.h>

#include "drivers/Ata/ata.h"
#include <drivers/Scsi/Sam5.h>
#include <LKDM.h>
#include <drivers/Networking/IpV4.h>

#include <FileHandleing/LDDDS.h>
#include <WinTEB.h>
#include <drivers/Processors.h>
#include <kernel/Firmware.h>
#include <kernel/KernelPm.h>
#include <Dispatching.h>
#include <kernel/XArray.h>
#include <drivers/Busses.h>
#include <kernel/Objects.h>
#include <drivers/Ecam.h>
#include <kwstring.h>
#include <WinAPI/Win32/winnls.h>
#include <drivers/Processors.h>
#include <Coff.h>
#include <LouLoad.h>
#include <Power.h>
#include <kernel/Events.h>
#include <drivers/fpu.h>
#include <kernel/LKPCB.h>
#include <kernel/LouAccessTokens.h>
#include <Riff.h>
#include <kernel/LouAccessTokens.h>
#include <Security.h>
#include <kernel/LazyAllocations.h>
#include <kernel/Stack.h>
#include <WinAPI/Win32/GdiCore.h>

#ifndef _KERNEL_MODULE_


//MEMMORY ALLOCATION
LOUAPI void LouPanic(char*);
//STD Library
LOUAPI void* memset(void* dest, int value, size_t count);


KERNEL_EXPORT void* memcpy(void* dest, const void* src, size_t n);
KERNEL_EXPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_EXPORT int strcmp(const char* str1, const char* str2);
KERNEL_EXPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_EXPORT char* strncpy(char* dest, const char* src, size_t n);


KERNEL_EXPORT void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData);
//LOUAPI void INTERRUPT(uint8_t InterruptNumber);

KERNEL_EXPORT void sleep(uint64_t Time);



#else 

#endif//kernelmod



#else


#endif
#endif

#ifdef _KERNEL_MODULE_
KERNEL_EXPORT LOUSTATUS RegisterHardwareInterruptHandler(void(*Handler)(uint64_t), uint8_t InterruptNumber, bool ERS);
KERNEL_EXPORT void* memcpy(void* dest, const void* src, size_t n);
KERNEL_EXPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_EXPORT int strcmp(const char* str1, const char* str2);
KERNEL_EXPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_EXPORT char* strncpy(char* dest, const char* src, size_t n);
KERNEL_EXPORT void sleep(uint64_t Time);
KERNEL_EXPORT void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData);

KERNEL_EXPORT
int snprintf(char *buffer, size_t buffer_size, const char *format, ...);

#ifdef _DMI_CORE_H
KERNEL_EXPORT BOOL DmiGetDate(DMI_FIELD Field, INTEGER* Year, INTEGER* Month, INTEGER* Day);
#endif

#ifndef _MEMORY_BARRIER
#define _MEMORY_BARRIER

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")
#define LouKePauseMemoryBarrier() asm volatile("pause" : : : "memory")

#endif


#endif