#include <LouAPI.h>

void* LouKeForkToUserModeSection(uint64_t OriginalLocation);

string GetNextDirectoryName(string PATH){


    if(PATH[0] == '/'){
        PATH++; //takes away the / charecter
        LouPrint("Path is:%s\n", PATH);
        return PATH;
    }
    else {
        PATH = PATH + CurrenDirectoryStringLength(PATH) + 1;
        LouPrint("Path is:%s\n", PATH);
        return PATH;
        
    }
}


uint8_t CurrenDirectoryStringLength(string Dir){
    for(uint8_t i = 0; i < 255; i++){
        if(Dir[i] == '/')return i;
        else if(Dir[i] == '.')return i;
        else if(Dir[i] == '\0')return i;
    }
    return 0x00;
}

void LouKeFOpenCall(uint64_t* Data){
    string PathToFile = (string)*Data;
    *Data = (uint64_t)fopen(PathToFile);   
    uint64_t KData = *Data;
    *Data = (uint64_t)LouKeForkToUserModeSection(KData);
    LouFree((RAMADD)KData);
}