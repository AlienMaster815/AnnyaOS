#include <LouAPI.h>



bool LouKeCreateProcessA(
    string                          ApplicationName,
    string                          CommandLine,
    PWIN_API_SECUTIY_ATTRIBUTES     ProcessAttributes,
    PWIN_API_SECUTIY_ATTRIBUTES     ThreadAttributes,
    bool                            Inherited,
    uint32_t                        Flags,
    void*                           Enviornment,
    string                          CurrentDirectory,
    PWIN_API_STARTUP_INFOA          StartupInformation,
    PWIN_API_PROCESS_INFORMATION    ProcessInformation,
    bool                            AnnyaAPIProcess //AnnyaAPI uses different flags and setups
){


    return true;
}

void LouKeCreateProcessW(){

}