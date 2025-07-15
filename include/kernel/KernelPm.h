#ifndef _KERNEL_PM_H
#define _KERNEL_PM_H
#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

typedef enum{
    SYSTEM_POWER_OFF_PREPARE = 0,
    SYSTEM_POWER_OFF_POWER_OFF,
    SYSTEM_POWER_OFF_RESTART_PREPARE,
    SYSTEM_POWER_OFF_RESTART,
    SYSTEM_POWER_STATE_COUNT,
}SYSTEM_POWER_OFF_STATES;

typedef struct _SYSTEM_POWER_OFF_STATE_DATA{
    INTEGER     PowerState;
    PVOID       CommandBuffer;
    string      Command;
    PVOID       PlatformDevice;
}SYSTEM_POWER_OFF_STATE_DATA, * PSYSTEM_POWER_OFF_STATE_DATA;

#define SYSTEM_POWER_OFF_PRIORITY_PLATFORM      -256
#define SYSTEM_POWER_OFF_PRIORITY_LOW           -128
#define SYSTEM_POWER_OFF_PRIORITY_DEFAULT       0
#define SYSTEM_POWER_OFF_PRIORITY_HIGH          192
#define SYSTEM_POWER_OFF_PRIORITY_FIRMWARE      256

typedef PVOID HANDLE; 

HANDLE LouKeRegisterPowerOffMechanism(
    SYSTEM_POWER_OFF_STATES         State,
    INTEGER                         Priority,
    LOUSTATUS                       (*Callback)(PSYSTEM_POWER_OFF_STATE_DATA),
    PSYSTEM_POWER_OFF_STATE_DATA    CallData
);

void LouKeUnRegisterPowerOffMechanism(
    HANDLE PowerOffHandle
);

typedef struct _LOUSINE_POWER_TRANSITION_OPERATIONS{
    void (*SuspendOperation)();
    void (*ResumeOperation)();
}LOUSINE_POWER_TRANSITION_OPERATIONS, * PLOUSINE_POWER_TRANSITION_OPERATIONS;

void LouKeRegisterPowerTransitionOperations(
    PLOUSINE_POWER_TRANSITION_OPERATIONS Operations
);

#ifdef __cplusplus
}
#endif
#endif