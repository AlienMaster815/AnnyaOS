
#ifndef LOUAPI_H
#define LOUAPI_H

#define WINAPI __stdcall

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

//Include API Headers
#include <cstdint.h>
#include <Helpers.h>
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
#include <drivers/Scsi/Sam5.h>
#include "drivers/Ata/ata.h"
#include <drivers/Networking/IpV4.h>
#include <WinTEB.h>
#include <drivers/cpu/Apic.h>
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
#include <KernelAPI/Processes.h>
#include <FileHandleing/Coff.h>
#include <drivers/Processors.h>
#include <Coff.h>
#include <LouLoad.h>
#include <Power.h>
#include <kernel/Events.h>
#include <drivers/fpu.h>
#include <kernel/LKPCB.h>
#include <kernel/LouAccessTokens.h>


#ifndef KERNEL_MAIN_FILE
extern LOUSINE_LOADER_INFO KernelLoaderInfo;
#endif


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

uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

#else //Kernel Module

#endif
#endif
