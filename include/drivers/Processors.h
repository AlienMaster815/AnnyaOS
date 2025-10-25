#ifndef _PROCESSORS_H
#define _PROCESSORS_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

INTEGER 
GetCurrentCpuTrackMember();


LOUSTATUS LouKeSmpWakeAssistant(
    INTEGER Assistant, 
    UINT64 Stack, 
    UINT64 CpuInitFunction
);

#ifdef __cplusplus
}
#endif
#endif