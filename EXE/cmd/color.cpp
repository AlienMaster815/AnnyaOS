#include "cmd.h"

const char* ColorHex[] = {
    "#000000", "#0000AA", "#00AA00", "#00AAAA", // 0-3
    "#AA0000", "#AA00AA", "#FFF000", "#CCCCCC", // 4-7
    "#555555", "#5555FF", "#55FF55", "#55FFFF", // 8-B
    "#FF5555", "#FF55FF", "#FFFF55", "#FFFFFF"  // C-F
};


CMD_STATUS 
DispatchColorCommand(
    COMMAND_PARAMETER Params
){

    if(Params == "help"){
        std::cout << "color [2] {foreground, background} sets the color of the terminal\n";
        std::cout << std::endl;
        std::cout << "0:Black      1:Blue         2:Green\n";
        std::cout << "3:Cyan       4:Red          5:Megenta\n";
        std::cout << "6:Yellow     7:White        8:Gray\n";
        std::cout << "9:LightBlue  A:LightGreen   B:LightCyan\n";
        std::cout << "C:LightRed   D:LightMagenta E:LightYellow\n";
        std::cout << "F:BrightWhite\n";
        std::cout << std::endl;
        return STATUS_OK;
    }
    
    if(Params == ""){
        Params = "07";
    }

    if(
        (Params.length() != 2) ||
        (!std::isxdigit(Params[0])) ||
        (!std::isxdigit(Params[1])) ||
        (Params[0] == Params[1])
    ){
        std::cout << "ERROR Invalid Color\n";
        return STATUS_EINVAL;
    }

    std::string Foo(1, Params[0]);
    std::string Bar(1, Params[1]);

    std::cout   << "\033]11;" << ColorHex[std::stoi(Foo, nullptr, 16)] << "\007"
                << "\033]10;" << ColorHex[std::stoi(Bar, nullptr, 16)] << "\007";

    return STATUS_OK;
}
