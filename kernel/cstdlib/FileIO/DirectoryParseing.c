#include <LouAPI.h>

void* LouKeForkToUserModeSection(uint64_t OriginalLocation);

uint8_t CurrentDirectoryStringLength(string Dir){
    for(uint8_t i = 0; i < 255; i++){
        if(Dir[i] == '/')return i;
        else if(Dir[i] == '.')return i;
        else if(Dir[i] == '\0')return i;
    }
    return 0x00;
}

string GetNextDirectoryName(string PATH){


    if(PATH[0] == '/'){
        PATH++; //takes away the / charecter
        //LouPrint("Path is:%s\n", PATH);
        return PATH;
    }
    else {
        PATH = PATH + CurrentDirectoryStringLength(PATH) + 1;
        //LouPrint("Path is:%s\n", PATH);
        return PATH;
        
    }
}


LOUSTATUS LouKeLoadFileCall(uint64_t* Data, ACCESS_MASK RequestedAccess){
    string PathToFile = (string)*Data;
    LOUSTATUS Status;
    PVOID Object;
    HANDLE OutHandle;
    Status = LouKeGetObjectHeaderByName(PathToFile, &Object);
    if(Status == STATUS_SUCCESS){
        Status = LouKeAcquireHandleForObject(
            &OutHandle,
            PathToFile,
            RequestedAccess
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("LouKeLoadFileCall() Unable To Acquire Handle For Object\n");
            *Data = 0x00;
            return Status;
        }
        *Data = (uint64_t)OutHandle;
        return STATUS_SUCCESS;
    }

    FILE* File = fopen(PathToFile, KERNEL_GENERIC_MEMORY);   
    
    if(!File){
        LouPrint("LouKeLoadFileCall() Unable To Open File\n");
        *Data = 0x00;
        return STATUS_NO_SUCH_FILE;
    }

    Status = LouKeRegisterFileToObjectManager(
        File,
        PathToFile,
        0,
        0x00
    );
 
    if(Status != STATUS_SUCCESS){
        LouPrint("LouKeLoadFileCall() Unable To Register Object");
        *Data = 0x00;
        return Status;
    }
    
    
    Status = LouKeGetObjectHeaderByName(PathToFile, &Object);
    if(Status == STATUS_SUCCESS){
        Status = LouKeAcquireHandleForObject(
            &OutHandle,
            File,
            RequestedAccess
        );
        if(Status != STATUS_SUCCESS){
            LouPrint("LouKeLoadFileCall() Unable To Acquire Handle For Object\n");
            //TODO Remove Object From Object Manager And Close File
            *Data = 0x00;
            while(1);
            return Status;
        }
        *Data = (uint64_t)OutHandle;
        return STATUS_SUCCESS;
    }

    
    LouPrint("LouKeLoadFileCall() FAILED To Get Object\n");

    while(1);
    return STATUS_UNSUCCESSFUL;
}

void LouKeCloseFileCall(uint64_t* Data){
    fclose((FILE*)*Data);
}
