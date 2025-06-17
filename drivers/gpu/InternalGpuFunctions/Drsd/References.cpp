#include "DrsdCore.h"

void DrsdModeObjectObjectFree(PDRSD_MODE_OBJECT Object){
    if(Object->FreeCb){ 
        int Tmp = LouKeGetAtomic(&Object->ReferenceCount); 
        if(Tmp){
            Tmp--;
            LouKeSetAtomic(&Object->ReferenceCount, Tmp);
            Object->FreeCb(Tmp);
        }       
    }
}