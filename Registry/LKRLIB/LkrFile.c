#include <Compiler.h>


error_t
LouKeCreateSourceNodes(
    PCOMPILER_CONTEXT Context
){
    LPWSTR CheckString = (LPWSTR)((uintptr_t)Context->FileContext + sizeof(WCHAR)); 

    if(LKR_SOURCE_FILE_SANITY_FAILURE(CheckString)){
        return EINVAL;
    }

    //Context->CompilerNode = LouKeCreateLousineNode(
    
    //);


    return 0;
}