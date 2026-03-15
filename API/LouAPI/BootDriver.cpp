#include <LouDDK.h>

KERNEL_EXPORT
void 
LouKeBootDriverCallbackFunction(
	PVOID                       CallbackContext,
	BDCB_CALLBACK_TYPE          Classification,
	PBDCB_IMAGE_INFORMATION     ImageInformation
){
    LouPrint("LouKeBootDriverCallbackFunction()\n");
    while(1);
}
