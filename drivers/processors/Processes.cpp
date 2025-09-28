#include <LouDDK.h>

LOUSTATUS
LouKeCreateUserProcess(
    HANDLE*                         ProcessHandle,
    HANDLE*                         ThreadHandle,
    ACCESS_MASK                     ProcessDesiredAccess,
    ACCESS_MASK                     ThreadDesiredAccess,
    PCOBJECT_ATTRIBUTES             ProcessAttributes,
    PCOBJECT_ATTRIBUTES             ThreadAttributes,
    ULONG                           ProcessFlags,
    ULONG                           ThreadFlags,
    PRTL_USER_PROCESS_PARAMETERS    ProcessParameters,
    PPS_CREATE_INFO                 CreateInfo,
    PPS_ATTRIBUTE_LIST              Attributes
){

    return STATUS_SUCCESS;
}