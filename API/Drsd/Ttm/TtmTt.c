#include "../DrsdCore.h"

static SIZE TtmGlobalPageLimit; 
static SIZE TtmGlobalDma32PageLimit; 

void TtmTtManagerInitialize(
    SIZE    PageCount,
    SIZE    Dma32PageCount
){
    if(!TtmGlobalPageLimit){
        TtmGlobalPageLimit = PageCount;
    }
    if(!TtmGlobalDma32PageLimit){
        TtmGlobalDma32PageLimit = Dma32PageCount;
    }
}