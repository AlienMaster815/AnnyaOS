#include <LouAPI.h>


void LouKeInitializeSecuritySubsystem(){
 
    LouKeCreateFastObjectClass(
        "LOUSINE_ACCESS_TOKEN",
        512,
        sizeof(LOUSINE_ACCESS_TOKEN),
        GET_ALIGNMENT(LOUSINE_ACCESS_TOKEN),
        0,
        KERNEL_GENERIC_MEMORY
    );

}