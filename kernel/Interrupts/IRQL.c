#include <LouAPI.h>
/* Defined in <Kernel/interrupts.h>
#define PASSIVE_LEVEL 0
#define APC_LEVEL 1
#define DISPATCH_LEVEL 2
#define DIRQL 3
#define CLOCK_LEVEL 13
#define HIGH_LEVEL 15
*/

void LouKeIcUnmaskIrq(uint8_t irq);
bool GetAPICStatus();

static LouKIRQL SystemInterruptLevel = HIGH_LEVEL;

LouKIRQL InterruptSwitch(LouKIRQL New){
    LouKIRQL Old = SystemInterruptLevel;
    SystemInterruptLevel = New;
    return Old;
}

void LocalApicSetTimer(bool On);
void LouKeSendIcEOI();



void LouKeSetIrql(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
){
        if(OldIrql != 0x00){//0x00 is null in this system and is excplicitly checked for sanity
            *OldIrql = SystemInterruptLevel; // save the old irql1
        }
        //TODO: Once User Mode Gets hacked up a bit will implement user things and drivers when drivers are hacked up

        switch (NewIrql){
            case PASSIVE_LEVEL:{
                SystemInterruptLevel = PASSIVE_LEVEL;
                asm("sti");
                return;
            }
            case APC_LEVEL:{
                
                return;
            }
            case DISPATCH_LEVEL:{

                return;
            }
            case DIRQL:{

                return;
            } 
            case CLOCK_LEVEL:{

                return;
            }
            case HIGH_LEVEL:{
                SystemInterruptLevel = HIGH_LEVEL;
                asm("cli");
            }
            default: // error case
                return;
        }
}

void KeRaiseIrql( // for wdk compatibility
    LouKIRQL DispatchLevel, 
    LouKIRQL* OldIrql
){
    if(*OldIrql >= DispatchLevel)return;
    LouKeSetIrql(DispatchLevel, OldIrql);
}

void KeLowerIrql(LouKIRQL DispatchLevel){//For WDK Compatibility
    LouKeSetIrql(DispatchLevel, 0x00);
}

