#include "cmd.h"
 
CMD_STATUS
GoToNextPath(
    std::string     CurrentPath,
    std::string     NewDirectory,
    std::string*    OutPath
){
    if(NewDirectory == ".." || NewDirectory == "."){
        CurrentPath.erase(CurrentPath.length() - 1);
        int UpPath = CurrentPath.rfind('\\');
        if(UpPath != std::string::npos){
            CurrentPath.erase(UpPath + 1);
            *OutPath = CurrentPath;
        }else{
            *OutPath = "\\";
        }
        return STATUS_OK;
    }

    CurrentPath += NewDirectory;

    std::string FullSystemPath = DriveLetter + ":" + CurrentPath; 

    DWORD Attributes = GetFileAttributesA(FullSystemPath.c_str());
    if(
        (Attributes == INVALID_FILE_ATTRIBUTES) ||
        ((Attributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
    ){
        return STATUS_EINVAL;
    }

    CurrentPath += '\\';

    *OutPath = CurrentPath;

    return STATUS_OK;
}

CMD_STATUS 
DispatchCdCommand(
    COMMAND_PARAMETER Params
){
    
    if(Params == "help"){
        std::cout << "CHDIR:[Path]\n";
        std::cout << "CHDIR:[..]\n";
        std::cout << "CD   :[Path]\n";
        std::cout << "CD   :[..]\n";
        std::cout << std::endl;
        std::cout << "CD/CHDIR:[Path] changes the current directory to the sub directory specified\n";
        std::cout << "CD/CHDIR:[..] changes the current director to the parent directory\n";
        std::cout << std::endl;
        return STATUS_OK;
    }
    
    if(Params == ""){
        DrivePath = "\\";
        return STATUS_OK;    
    }
    char*  TmpCString = (char*)Params.c_str();
    size_t StrLength = Params.length();
    size_t CurrentIndex = 0; 
    size_t NextIndex;
    std::string NewPath;
    std::string OldPath = DrivePath;
    while(CurrentIndex < StrLength){
        NextIndex = strcspn(&TmpCString[CurrentIndex], "\\/");

        std::string TmpString(&TmpCString[CurrentIndex], NextIndex);
         
        if(GoToNextPath(OldPath, TmpString, &NewPath) != STATUS_OK){
            std::cout << "ERROR:Directory Does Not Exist\n";
            return STATUS_EINVAL;
        }

        OldPath = NewPath;

        CurrentIndex += NextIndex + 1;
    }

    DrivePath = NewPath;

    return STATUS_OK;
}
