#include "cmd.h"

static const std::string Days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


CMD_STATUS DispatchDateCommand(COMMAND_PARAMETER Params){
    SYSTEMTIME LocalTime;
    GetLocalTime(&LocalTime);

    if(Params.length()){
        if(strncasecmp(Params.c_str(), "/T", 2) || (Params.length() != 2)){
            return STATUS_EINVAL;
        }
        std::cout << Days[LocalTime.wDayOfWeek] << " " << LocalTime.wMonth << "/" << LocalTime.wDay << "/" << LocalTime.wYear << std::endl;
        return STATUS_OK;
    }



    return STATUS_OK;
}