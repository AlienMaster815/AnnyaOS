//g++ cmd.cpp assoc.cpp cd.cpp color.cpp Dir.cpp -o cmd.exe -L../CMD -ladvapi -lshell
//dlltool --input-def advapi.def 
//dlltool --input-def shell.def --output-lib shell.lib

#define _COMMAND_MAIN_

#include "cmd.h"

std::string DriveLetter = "C";
std::string DrivePath = "\\";

AnnyaOsCommandEngine::AnnyaOsCommandEngine(){
}

AnnyaOsCommandEngine::~AnnyaOsCommandEngine(){
}

CMD_STATUS 
AnnyaOsCommandEngine::ParseCommand(
    std::string         CommandLine, 
    COMMAND*            OutCommand,
    COMMAND_PARAMETER*  OutParams
){
    *OutParams = "";
    int CommandLineLength = CommandLine.length();
    int FirstSpace = CommandLine.find(' ');
    int CommandLength = (FirstSpace == std::string::npos) ? CommandLineLength : FirstSpace;
    int i;
    for(i = 0 ; i < DOS_DYNAMIC_COMMAND_COUNT; i++){
        if(
            (!strncasecmp(CommandLine.c_str(), this->Commands[i].CommandLineString.c_str(), CommandLength)) &&
            (CommandLength == this->Commands[i].CommandLineString.length())
        ){
            break;
        }
    }
    if(i < DOS_DYNAMIC_COMMAND_COUNT){
        //std::cout << this->Commands[i].CommandLineString << " " << this->Commands[i].CommandMessage;
        *OutCommand = this->Commands[i].CommandMessage; 
        if(CommandLine.length() == (this->Commands[i].CommandLineString.length() + 1)){
            std::cout << "Error Invalid Command\n";
            return STATUS_EINVAL;
        }
        switch(this->Commands[i].CommandMessage){
            case CMD_ASSOC:{
                if(CommandLine.length() < (this->Commands[i].CommandLineString.length() + 2)){
                    return STATUS_OK;
                }
                *OutParams = CommandLine.substr(this->Commands[i].CommandLineString.length() + 1);
                return STATUS_OK;
            }
            case CMD_CHDIR:
            case CMD_CD:{
                if(CommandLine.length() < (this->Commands[i].CommandLineString.length() + 2)){
                    return STATUS_OK;
                }
                *OutParams = CommandLine.substr(this->Commands[i].CommandLineString.length() + 1);
                return STATUS_OK;
            }
            case CMD_CLS:{
                if(CommandLineLength == this->Commands[i].CommandLineString.length()){
                    std::cout << "\033[2J\033[H" << std::flush;
                    return STATUS_NEXT_CMD;
                }
                break;
            }
            case CMD_COLOR:{
                if(CommandLine.length() < (this->Commands[i].CommandLineString.length() + 2)){
                    return STATUS_OK;
                }
                *OutParams = CommandLine.substr(this->Commands[i].CommandLineString.length() + 1);
                return STATUS_OK;
            }
            case CMD_DIR:{
                if(CommandLine.length() < (this->Commands[i].CommandLineString.length() + 2)){
                    return STATUS_OK;
                }
                *OutParams = CommandLine.substr(this->Commands[i].CommandLineString.length() + 1);
                return STATUS_OK;
            }
            case CMD_EXIT:{
                if(CommandLineLength == this->Commands[i].CommandLineString.length()){
                    return STATUS_EXIT;
                }
                break;
            }
            default:
                break;
        }
    }
    
    std::cout << "Error Invalid Command\n";
    return STATUS_EINVAL;
}

CMD_STATUS 
AnnyaOsCommandEngine::GetMessage(
    COMMAND*            CommandOut, 
    COMMAND_PARAMETER*  Params
){
    CMD_STATUS Status;
    *Params = "";
    std::string NewEntry;
    std::cout << DriveLetter << ":" << DrivePath << ">";
    std::getline(std::cin, NewEntry);

    if(NewEntry.empty()){
        return STATUS_EINVAL;
    }

    if(
        (!strncasecmp(NewEntry.c_str(), "help", NewEntry.length())) &&
        (NewEntry.length() == strlen("help"))
    ){
        std::cout << "Commands Available:\n";
        for(size_t i = 0 ; i < DOS_DYNAMIC_COMMAND_COUNT; i++){
            std::cout << this->Commands[i].CommandLineString << std::endl;
        }
        std::cout << std::endl;
        return STATUS_EINVAL;
    }

    return ParseCommand(NewEntry, CommandOut, Params);
}

CMD_STATUS 
AnnyaOsCommandEngine::DispatchMessage(
    COMMAND             CommandIn, 
    COMMAND_PARAMETER   Params
){
    if(this->Commands[CommandIn].CommandDispatch){
        return this->Commands[CommandIn].CommandDispatch(Params);
    }
    return STATUS_EINVAL;
}

int main(){
    CMD_STATUS Status;
    ANNYA_COMMNAD_ENGINE CommandEngine;
    COMMAND Command;
    COMMAND_PARAMETER Params;

    std::cout << "Annya OS Command Prompt - (C) Tyler Grenier 2026\n\n";

    while((Status = CommandEngine.GetMessage(&Command, &Params)) != STATUS_EXIT){
        if(Status == STATUS_OK){
            Status = CommandEngine.DispatchMessage(Command, Params);
        }
    }
    return 0x00;
}