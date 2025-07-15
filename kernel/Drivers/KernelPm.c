#include <LouACPI.h>
#include <acpi.h>

typedef struct _SYSTEM_POWER_OFF_HANDLE{
    ListHeader                      Peers;
    LOUSTATUS                       (*Callback)(PSYSTEM_POWER_OFF_STATE_DATA);
    INTEGER                         Priority;
    SYSTEM_POWER_OFF_STATES         PowerStateType;
    PSYSTEM_POWER_OFF_STATE_DATA    PowerOffData;
}SYSTEM_POWER_OFF_HANDLE, * PSYSTEM_POWER_OFF_HANDLE;

static SYSTEM_POWER_OFF_HANDLE PowerOffManagementStack = {
    0
};

static PLOUSINE_POWER_TRANSITION_OPERATIONS PowerTransitionOperations = 0x00;

HANDLE LouKeRegisterPowerOffMechanism(
    SYSTEM_POWER_OFF_STATES         State,
    INTEGER                         Priority,
    LOUSTATUS                       (*Callback)(PSYSTEM_POWER_OFF_STATE_DATA),
    PSYSTEM_POWER_OFF_STATE_DATA    CallData
){
    PSYSTEM_POWER_OFF_HANDLE PowerOffHandle = LouKeMallocType(SYSTEM_POWER_OFF_HANDLE, KERNEL_GENERIC_MEMORY);
    PowerOffHandle->PowerStateType = State;  
    PowerOffHandle->Priority = Priority;
    PowerOffHandle->Callback = Callback;
    PowerOffHandle->PowerOffData = CallData;
    PSYSTEM_POWER_OFF_HANDLE Tmp = &PowerOffManagementStack;
    while(Tmp->Peers.NextHeader){
        Tmp = (PSYSTEM_POWER_OFF_HANDLE)Tmp->Peers.NextHeader;
    }
    Tmp->Peers.NextHeader = (PListHeader)PowerOffHandle;
    return (HANDLE)PowerOffHandle;
}

void LouKeUnRegisterPowerOffMechanism(
    HANDLE PowerOffHandle
){



}

void LouKeRegisterPowerTransitionOperations(
    PLOUSINE_POWER_TRANSITION_OPERATIONS Operations
){
    PowerTransitionOperations = Operations;

}