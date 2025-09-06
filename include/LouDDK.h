#ifndef _LOUDDK_H
#define _LOUDDK_H

#include <cstdint.h>

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

#ifndef _GUID_TYPE
#define _GUID_TYPE
typedef struct _GUID {
	unsigned char DataByte[16];
} GUID,* LPGUID, UUID, * PGUID, * PUUID;
#endif


#include <drivers/Lou_drivers/PciIds.h>

#define SYSV_CONVENTION __attribute__((sysv_abi))
#define NAKED_FUNCTION __attribute__((naked))

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

#include <stdlib.h>


#define LOUDDK_API_ENTRY extern "C"
#define DRIVER_IO_FUNCTION extern "C"

#ifdef _KERNEL_MODULE_

#ifndef PVOID
typedef void* PVOID;
#endif

#ifndef _KERNEL_EXPORTS_
#define _KERNEL_EXPORTS_
#define KERNEL_EXPORT extern "C" __declspec(dllimport)
#endif
#endif

#define DRIVER_EXPORT extern "C" __declspec(dllexport)
#define DRIVER_IMPORT extern "C" __declspec(dllimport)

#define KERNEL_IMPORT extern "C"

//define common used cpp functions with drivers
#include <drivers/Lou_drivers/io.h>
#include <stat.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <drivers/Vendors/VendorsDictionary.h>
#include <kernel/memmory.h>
#include <kernel/Binarys.h>
#include <stdio.h>
#include <KernelAPI/BitCheck.h>

#include <kernel/interrupts.h>
#include <kernel/threads.h>
#include <SharedTypes.h>
#include <kernel/DRSD.h>
#include <kernel/LouQs.h>
#include "NtOsKrnlLib.h"
#include <HashTables.h>
#include <drivers/Networking/IpV4.h>

#include <WinAPI/Win32/Win32API.h>

#include <math.h>

#include <LKDM.h>

typedef void* FILE;

typedef void* DEVICE;

KERNEL_IMPORT void LouKeInitializeIntervalWork(
    void (*DelayedFunction)(uint64_t PrivateData),
    uint64_t PrivateData,
    uint64_t MsInterval
);

#define RAMADD unsigned char*
#define RAMADDDATA unsigned char *
#define BLOCK 4096

#ifdef __x86_64__
    #define SIZE uint64_t
    
#endif
#ifdef __i386__

    #define SIZE uint32_t

#endif



#define LOUSTATUS_GOOD 0
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
#ifndef _KERNEL_MODULE_
KERNEL_IMPORT int LouPrint(char *format, ...);

#else
KERNEL_EXPORT int LouPrint(char *format, ...);
KERNEL_EXPORT LOUSTATUS RegisterHardwareInterruptHandler(void(*Handler)(uint64_t), uint8_t InterruptNumber, bool ERS);
KERNEL_EXPORT void* memcpy(void* dest, const void* src, size_t n);
KERNEL_EXPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_EXPORT int strcmp(const char* str1, const char* str2);
KERNEL_EXPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_EXPORT char* strncpy(char* dest, const char* src, size_t n);
KERNEL_EXPORT void sleep(uint64_t Time);
KERNEL_EXPORT bool LouKeWaitForMmioState(uint32_t* Register, uint32_t State, uint32_t Mask, uint64_t MsTimeout);
KERNEL_EXPORT uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);
#endif
// PORTS Stuff

#ifdef __x86_64__
    KERNEL_IMPORT uint64_t read_msr(uint32_t msr_id);
#endif

#include <Helpers.h>
#include <KernelAPI/DriverAPI.h> 
#include <drivers/Lou_drivers/hardrive.h> 
#include <drivers/Lou_drivers/storage_struct.h>
#include <drivers/Lou_drivers/FileSystem.h>
#include <KernelAPI/IOManager.h> 
#include <drivers/Lou_drivers/FileSystems/ISO.h>
#include <KernelAPI/Drives.h> 
#include <drivers/Lou_drivers/hardrive.h>
#include <stdio.h>
#include <drivers/Lou_drivers/io.h> 
#include <drivers/Lou_drivers/pci.h>
#include <stdlib.h>
#include <drivers/Lou_drivers/Processor.h>
#include <KernelAPI/Video.h>
#include <fstream.h>
#include <KernelAPI/Devices.h>
#include <Time.h>
#include <kernel/exec.h>
#include <Random.h>

#include "drivers/Ata/ata.h"
#include "drivers/Scsi/ScsiHost.h"
#include <LKDM.h>
#include <drivers/Networking/IpV4.h>

#include <FileHandleing/LDDDS.h>
#include <WinTEB.h>
#include <drivers/cpu/IntelFamily.h>
#include <drivers/cpu/cpu.h>
#include <kernel/Firmware.h>
#include <kernel/KernelPm.h>
#include <Dispatching.h>
#include <kernel/XArray.h>
#include <drivers/Busses.h>
#include <kernel/Objects.h>
#include <drivers/Ecam.h>


#ifndef _KERNEL_MODULE_
#define KERNEL_EXPORT extern "C"

KERNEL_IMPORT uint8_t inb(uint64_t port);
KERNEL_IMPORT void outb(uint64_t port, uint8_t data);
KERNEL_IMPORT uint16_t inw(uint64_t port);
KERNEL_IMPORT void outw(uint64_t port, uint16_t data);
KERNEL_IMPORT uint32_t inl(uint64_t port);
KERNEL_IMPORT void outl(uint64_t port, uint32_t data);
KERNEL_IMPORT void outbSlow(uint64_t port,uint8_t data);
//MEMMORY ALLOCATION
KERNEL_IMPORT void LouPanic(char*,STATUS);
//STD Library
KERNEL_IMPORT void* memset(void* dest, int value, size_t count);


KERNEL_IMPORT void* memcpy(void* dest, const void* src, size_t n);
KERNEL_IMPORT int strncmp(const char* str1, const char* str2, size_t n);
KERNEL_IMPORT int strcmp(const char* str1, const char* str2);
KERNEL_IMPORT int memcmp(const void* ptr1, const void* ptr2, size_t num);
KERNEL_IMPORT char* strncpy(char* dest, const char* src, size_t n);

LOUDDK_API_ENTRY
void* 
LouKeLoadSubsystem(string Subsystem, string EntryName);

LOUDDK_API_ENTRY
void* 
LouKeLoadDriver(string Driver, string EntryName);

void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData);
//KERNEL_IMPORT void INTERRUPT(uint8_t InterruptNumber);

KERNEL_IMPORT void sleep(uint64_t Time);

#define ACPIBUFFER 256

#define ERRMAPPINGIO -1

#ifndef _ANNYA_DLL_CALL_REASONS
#define _ANNYA_DLL_CALL_REASONS
    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0
    #define DLL_THREAD_ATTACH  2
    #define DLL_THREAD_DETACH  3
#endif

typedef struct _WIN_API_SECUTIY_ATTRIBUTES{
    uint32_t    Length;
    void*       SecurityDescriptor;
    bool        HandleIsInherited;
}WIN_API_SECUTIY_ATTRIBUTES, * PWIN_API_SECUTIY_ATTRIBUTES;

typedef struct _WIN_API_STARTUP_INFOA{
    uint32_t    StructureSize; // = 0x40;
    string      Reserved;
    string      Desktop;
    string      Title;
    //the following is currently 
    //implemented in the kernel
    //as uint16 because i havent
    //heard of a screen bigger 
    //than 0xFFFF pixels
    uint32_t    windowX;
    uint32_t    WindowY;
    uint32_t    WindowXSize;
    uint32_t    WindowYSize;
    //endof uint16_t kernel implementation
    uint32_t    WindowXCharecterCount;
    uint32_t    WindowYCharecterCount;
    uint32_t    FillAttribute;
    uint32_t    Flags;
    uint16_t    ShowWindow;
    uint16_t    Reserved2;
    uint8_t*    Reserved3; //aka lpReserved2
    void*       StdInput;
    void*       StdOutput;
    void*       StdError;
}WIN_API_STARTUP_INFOA, * PWIN_API_STARTUP_INFOA;

typedef struct _WIN_API_PROCESS_INFORMATION{
    void*       ProcessHandle;
    void*       ThreadHandle;
    uint32_t    ProcessIdentification;
    uint32_t    ThreadIdentification;
}WIN_API_PROCESS_INFORMATION, * PWIN_API_PROCESS_INFORMATION;



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
KERNEL_EXPORT void outw(uint64_t port, uint16_t data);
KERNEL_EXPORT uint16_t inw(uint64_t port64);
KERNEL_EXPORT void RegisterInterruptHandler(void(*Handler)(uint64_t),uint8_t InterruptNumber, bool NeedFlotationSave, uint64_t OverideData);
KERNEL_EXPORT uint32_t inl(uint64_t Port64);
KERNEL_EXPORT uint32_t outl(uint64_t Port64, uint32_t Data);
KERNEL_EXPORT uint8_t inb(uint64_t port);
KERNEL_EXPORT void outb(uint64_t port, uint8_t data);
KERNEL_EXPORT
void* 
LouKeLoadSubsystem(string Subsystem, string EntryName);

KERNEL_EXPORT
void* 
LouKeLoadDriver(string Driver, string EntryName);

#ifndef _MEMORY_BARRIER
#define _MEMORY_BARRIER

#define LouKeMemoryBarrier() asm volatile("mfence" : : : "memory")
#define LouKePauseMemoryBarrier() asm volatile("pause" : : : "memory")

#endif


#endif