#ifndef KERNEL_H
#define KERNEL_H
/* Tyler Grenier 9/21/23 10:00 PM
-- This is Where the API For Our Kernel
-- is started with Kernel entry data Type 
-- Being defined as a no return void
-- Later on might be designated as no ssp 
-- as well... 
*/

#include <kernel/ports.h>
#include <kernel/Timers.h>
#include <kernel/atomic.h>
#include <kernel/SystemCalls.h>
#include <kernel/Binarys.h>
#include "threads.h"
#include "exec.h"
#include "DRSD.h"
#include "Process.h"



#ifdef __cplusplus
LOUAPI bool IsSystemEfi();
KERNEL_EXPORT
void* 
LouKeLoadSubsystem(string Subsystem, string EntryName);
#else
bool IsSystemEfi();
KERNEL_EXPORT
void* 
LouKeLoadSubsystem(string Subsystem, string EntryName);
KERNEL_EXPORT
void* 
LouKeLoadDriver(string Driver, string EntryName);
#endif


#ifndef _KERNEL_ENTRY_
#define _KERNEL_ENTRY_
#define KERNEL_ENTRY extern void
#endif

#ifdef __x86_64__


#define KernelCodeSegment 0x08
#ifndef __cplusplus

#ifndef _KERNEL_MODULE_

#endif

#endif

#endif

#ifdef __i386__

#ifndef _KERNEL_MODULE_
#define KernelCodeSegment 0x08
#endif

#endif

#endif
