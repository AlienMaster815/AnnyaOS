
#include "lnk.h"

const CLSID LinkCLSID = {0x46, 0x00 , 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x14, 0x02, 0x00}; // 00021401-0000-0000-C000-000000000046 in LE 

LOUSTATUS MsShlLinkCreateShellLinkHeader(
    PSHLLINK_COMPILER_CONTEXT   Context
){



    return STATUS_SUCCESS;
}

LOUSTATUS 
MsShlLinkCreateCompilerContext(
    PSHLLINK_COMPILER_CONTEXT*      OutContext,
    string                          ShortcutPathAndFile,
    string                          OutputPathAndFile
){
    PSHLLINK_COMPILER_CONTEXT NewContext = malloc(sizeof(SHLLINK_COMPILER_CONTEXT));
    memset(NewContext, 0, sizeof(SHLLINK_COMPILER_CONTEXT));

    NewContext->ShortcutPathAndFile = ShortcutPathAndFile;
    NewContext->OutputPathAndFile = OutputPathAndFile;

}

void MsShlLinkDestroyCompilerContext(
    PSHLLINK_COMPILER_CONTEXT Context
){
    free(Context);
}

const struct{
    string  ParamString;
    int     ParamID;
}ValidArgs[] = {
    {"-S", 0},
    {"-O", 1},
    {0x00, 2},
};

LOUSTATUS 
MsShlLinkGetArgs(
    string*     Args,
    int         ArgCount,
    string*     ShortcutPathAndFile,
    string*     OutputPathAndFile
){
    if((!Args) || (!ArgCount) || (ArgCount > 2) || (!ShortcutPathAndFile) || (!OutputPathAndFile)){
        return STATUS_INVALID_PARAMETER;
    }

    for(size_t i = 0; i < ArgCount; i++){
        size_t j;
        for(j = 0 ; ValidArgs[j].ParamString; j++){
            if(!strncmp(Args[i], ValidArgs[j].ParamString, 2)){
                break;
            }
        }
        if(!ValidArgs[j].ParamString){
            return STATUS_INVALID_PARAMETER;
        }

        switch(ValidArgs[j].ParamID){
            case 0:
                ShortcutPathAndFile = &Args[i] + 2;
                continue;
            case 1:
                OutputPathAndFile = &Args[i] + 2;
                continue;
            default:
                return STATUS_INVALID_PARAMETER;    
        }

    }

    return STATUS_SUCCESS;
}

int main(int ArgCount, char** Args){
    string ShortcutPathAndFile = 0x00;
    string OutputPathAndFile = 0x00;

    LOUSTATUS Status = MsShlLinkGetArgs(
        Args,
        ArgCount,
        &ShortcutPathAndFile,
        &OutputPathAndFile
    );
    if(Status != STATUS_SUCCESS){
        printf("Error Invalid Parameter\n");
        return -1;
    }


    return 0;
}