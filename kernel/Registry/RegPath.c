#include <LouAPI.h>
#include "Registry.h"

LOUSTATUS LouKeRegLpwstrPathToLpstrPath(
    LPWSTR  InLpwstr,
    string* OutString
){
    if((!OutString) || (!InLpwstr)){
        return STATUS_INVALID_PARAMETER;
    }
    
    SIZE InLpwstrLength = wcslen(InLpwstr) + 1;
    string NewOutString = LouKeMallocArray(CHAR, InLpwstrLength, KERNEL_GENERIC_MEMORY);
    InLpwstrLength--;

    //TODO: Later Replace To wcstombstr 
    for(size_t i = 0 ; i < InLpwstrLength; i++){
        if(InLpwstr[i] > 0xFF){
            LouKeFree(NewOutString);
            return STATUS_INVALID_PARAMETER;
        }else if(InLpwstr[i] == L'\\'){
            InLpwstr[i] = L'/';
        }
        NewOutString[i] = (CHAR)InLpwstr[i];
    }
    *OutString = NewOutString;
    return  STATUS_SUCCESS;
}

LOUSTATUS LouKeRegGetAndCombineStringPath(  
    PVOID   RootKey,
    LPWSTR  PathKey,
    LPWSTR  ExeKey,
    string* OutString
){
    LOUSTATUS Status;
    PVOID TmpKey; 
    string Result;
    if((!RootKey) || (!PathKey) || (!ExeKey) || (!OutString)){
        return STATUS_INVALID_PARAMETER;
    }

    //Open Path First
    TmpKey = LouKeOpenRegistryHandle(
        PathKey,
        RootKey
    );
    if(!TmpKey){
        LouPrint("ERROR Unable To Open Path Key\n");
        return STATUS_UNSUCCESSFUL;;
    }

    LPWSTR TmpLString = LouKeMallocArray(WCHAR, LouKeGetRegistryKeySize(TmpKey), KERNEL_GENERIC_MEMORY);
    Status = LouKeReadRegistryWcsValue(TmpKey, TmpLString);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Read Path String\n");
        LouKeFree(TmpLString);
        return Status;
    }
    
    string PathString;

    Status = LouKeRegLpwstrPathToLpstrPath(
        TmpLString,
        &PathString
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Make Path C String\n");
        LouKeFree(TmpLString);
        return Status;
    }
    Result = PathString;
    size_t PathLength = strlen(PathString);
    if(PathString[PathLength - 1] != '/'){
        PathString = LouKeMallocArray(CHAR, PathLength + 2, KERNEL_GENERIC_MEMORY);
        strcpy(PathString, Result);
        PathString[PathLength] = '/';
        LouKeFree(Result);
        Result = PathString;
    }
    PathLength = strlen(PathString);

    //Next Open Executable
    TmpKey = LouKeOpenRegistryHandle(
        ExeKey,
        RootKey
    );
    if(!TmpKey){
        LouPrint("ERROR Unable To Open Executable Key\n");
        return STATUS_UNSUCCESSFUL;;
    }
    TmpLString = LouKeMallocArray(WCHAR, LouKeGetRegistryKeySize(TmpKey), KERNEL_GENERIC_MEMORY);
    Status = LouKeReadRegistryWcsValue(TmpKey, TmpLString);
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Read Executable String\n");
        LouKeFree(TmpLString);
        return Status;
    }
    
    string ExeString;
    Status = LouKeRegLpwstrPathToLpstrPath(
        TmpLString,
        &ExeString
    );
    if(Status != STATUS_SUCCESS){
        LouPrint("ERROR Unable To Make Executable C String\n");
        LouKeFree(TmpLString);
        return Status;
    }

    //create new string, cleanup, retrurn    
    Result = LouKeMallocArray(CHAR, PathLength + strlen(ExeString) + 1, KERNEL_GENERIC_MEMORY);
    strcpy(Result, PathString);
    LouKeFree(PathString);
    strcat(Result, ExeString);
    LouKeFree(ExeString);

    *OutString = Result;
    return STATUS_SUCCESS;
}