#ifndef _POWER_H
#define _POWER_H

#ifdef __cplusplus
extern "C" { 
#endif

typedef enum _SHUTDOWN_ACTION{
    ShutdownNoReboot = 0,
    ShutdownReboot = 1,
    ShutdownPowerOff = 2,
}SHUTDOWN_ACTION;

#ifndef _USER_MODE_CODE_
#ifndef _KERNEL_MODULE_

void LouKeSystemShutdown(
    SHUTDOWN_ACTION Action
);

#endif
#endif
#ifdef __cplusplus
}
#endif
#endif