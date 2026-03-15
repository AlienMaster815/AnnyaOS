#include <LouDDK.h>

KERNEL_EXPORT
void 
LouKeCustomSystemEventTriggerInit(//export as NTOSKRNL:CUSTOM_SYSTEM_EVENT_TRIGGER_INIT
	PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG Config,
	PCWSTR                              TriggerId
){
    LouPrint("LouKeCustomSystemEventTriggerInit()\n");
    while(1);
}