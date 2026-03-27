#include "../DrsdCore.h"

static SIZE TtmGlobalPageCount = 0;

LOUSTATUS 
TtmPoolManagerInitialize(
    SIZE PageCount
){
    if(!TtmGlobalPageCount){
        TtmGlobalPageCount = PageCount;
    }

    //TODO:Allocate Page Orders

    

    return STATUS_SUCCESS;
}

void 
TtmPoolManagerDeInitialize(){



}