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

UINT8 GetWinIRQL();
void  SetWinIRQL(UINT8 Irql);


void LocalApicSetTimer(bool On);


LouKIRQL LouKeGetIrql(){
    if(!GetGSBase()){
        return HIGH_LEVEL;
    }
    return (LouKIRQL)GetWinIRQL();
}

void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
){
    if(!GetGSBase()){
        *OldIrql = HIGH_LEVEL;
        return;
    }
    
    if(OldIrql){//0x00 is null in this system and is excplicitly checked for sanity
        *OldIrql = GetWinIRQL(); // save the old irql1
    }
        
    if(GetWinIRQL() == NewIrql){
        return;
    }

    switch (NewIrql){
        case PASSIVE_LEVEL:{
            SetWinIRQL((UINT8)PASSIVE_LEVEL);
            return;
        }
        case APC_LEVEL:{
            SetWinIRQL((UINT8)APC_LEVEL);    
            return;
        }
        case DISPATCH_LEVEL:{
            SetWinIRQL((UINT8)DISPATCH_LEVEL);    
            return;
        }
        case DIRQL:{
            SetWinIRQL((UINT8)DIRQL);    
            return;
        } 
        case CLOCK_LEVEL:{
            SetWinIRQL((UINT8)CLOCK_LEVEL);    
            return;
        }
        case HIGH_LEVEL:{
            SetWinIRQL((UINT8)HIGH_LEVEL);    
        }
        default: // error case
            return;
    }
}



void LouKeSetIrql(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
){
    if(!GetGSBase()){
        return;
    }
    if(OldIrql){
        *OldIrql = GetWinIRQL(); // save the old irql1
    }
    if(GetWinIRQL() == NewIrql){
        return;
    }
    switch (NewIrql){
        case PASSIVE_LEVEL:{
            //sanity clear interrupts so nesting occours
            asm("cli");
            SetWinIRQL((UINT8)PASSIVE_LEVEL);
            asm("sti");
            return;
        }
        case APC_LEVEL:{
            //sanity clear interrupts so nesting occours
            asm("cli");
            SetWinIRQL((UINT8)APC_LEVEL);    
            asm("sti");
            return;
        }
        case DISPATCH_LEVEL:{
            //sanity clear interrupts so nesting occours
            asm("cli");
            SetWinIRQL((UINT8)DISPATCH_LEVEL);    
            asm("sti");
            return;
        }
        case DIRQL:{
            //sanity clear interrupts so nesting occours
            asm("cli");
            SetWinIRQL((UINT8)DIRQL);    
            asm("sti");
            ApciHalStartApicTimerEvents();
            return;
        } 
        case CLOCK_LEVEL:{
            //sanity clear interrupts so nesting occours
            ApciHalStopApicTimerEvents();
            asm("cli");
            SetWinIRQL((UINT8)CLOCK_LEVEL);    
            asm("sti");
            ApciHalStartApicTimerEvents();
            return;
        }
        case HIGH_LEVEL:{
            ApciHalStopApicTimerEvents();
            asm("cli");
            SetWinIRQL((UINT8)HIGH_LEVEL);    
            return;
        }
        default: // error case
            return;
    }
}

void LouKeRaiseIrql(
    LouKIRQL    Irql,
    LouKIRQL*   OldIrql
){
    if(OldIrql){
        *OldIrql = LouKeGetIrql();
    }
    if(*OldIrql >= Irql)return;
    LouKeSetIrql(Irql, 0x00);
}

void LouKeLowerIrql(
    LouKIRQL    Irql
){
    if(LouKeGetIrql() <= Irql)return;
    LouKeSetIrql(Irql, 0x00);
}

void KeRaiseIrql( // for wdk compatibility
    LouKIRQL DispatchLevel, 
    LouKIRQL* OldIrql
){

}

void KeLowerIrql(LouKIRQL DispatchLevel){//For WDK Compatibility

}

