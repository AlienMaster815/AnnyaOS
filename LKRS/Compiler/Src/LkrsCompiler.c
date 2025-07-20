#include <stdio.h>
#include <stdlib.h>
#include <Lkrs.h>



int LkrsCompileSourceFile(PKERNEL_REGISTRY_SOURCE_HANDLE KrsFile){
    int Result = LkrsBuildGlobalNameSpaceDefinitions(KrsFile);
    if(Result){
        return Result;
    }
    Result = LkrsBuildNameSpaceData(KrsFile);
    if(Result){
        return Result;
    }

    return 0;
}