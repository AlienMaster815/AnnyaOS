#include <LouAPI.h>


void LouKeAlpcSetInformation(
    uint64_t Data
);


void CheckWinCallTable(int64_t Call, uint64_t Data){
    switch (Call){
        case LOUALPCSETINFORMATION:{
            LouKeAlpcSetInformation(Data);
            break;
        }
        default:
            break;
    }
}