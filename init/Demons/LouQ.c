#include <LouAPI.h>

LOUQ_WORK WorkQueue = {0};

void LouQWorkDemon(PVOID WorkQueue){
    while(1){
        sleep(100);
        LouPrint("HERE\n");       
    }
}