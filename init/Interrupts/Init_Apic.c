#include <kernel/apic.h>

LOUSTATUS InitializeAdvancedProgramableController(){
    uint8_t Ver = IdentifyApicVersion();
    if(Ver == 0) return 1;
    
    return 0;
}
