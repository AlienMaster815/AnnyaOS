#ifndef _POWER_H
#define _POWER_H

#ifndef _USER_MODE_CODE_
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif
#else 
#include <Annya.h>
#endif

typedef enum _SHUTDOWN_ACTION{
    ShutdownNoReboot = 0,
    ShutdownReboot = 1,
    ShutdownPowerOff = 2,
}SHUTDOWN_ACTION;

void LouKeSystemShutdown(
    SHUTDOWN_ACTION Action
);

#ifndef _USER_MODE_CODE_
#ifdef __cplusplus
}
#endif
#endif
#endif