#ifndef _PROCESSORS_H
#define _PROCESSORS_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _USER_MODE_CODE_

#ifndef _KERNEL_MODULE_
INTEGER 
GetCurrentCpuTrackMember();

LOUSTATUS LouKeSmpWakeAssistant(
    INTEGER Assistant, 
    UINT64 Stack, 
    UINT64 CpuInitFunction
);
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif