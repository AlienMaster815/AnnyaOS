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
        return;
    }
    
    if(OldIrql){//0x00 is null in this system and is excplicitly checked for sanity
        *OldIrql = GetWinIRQL(); // save the old irql1
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

static BOOLEAN ApicTimerUnmask = false;
static BOOLEAN ApicTimerMask = true;
static BOOLEAN ApicTimerInitialized = false;

void InitializeApicTimerVariableForIrql(){
    ApicTimerInitialized = true;
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

    switch (NewIrql){
        case PASSIVE_LEVEL:{
            //sanity clear interrupts so nesting occours
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)PASSIVE_LEVEL);
            asm("sti");
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerUnmask, 0x00);
            return;
        }
        case APC_LEVEL:{
            //sanity clear interrupts so nesting occours
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)APC_LEVEL);    
            asm("sti");
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerUnmask, 0x00);
            return;
        }
        case DISPATCH_LEVEL:{
            //sanity clear interrupts so nesting occours
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)DISPATCH_LEVEL);    
            asm("sti");
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerUnmask, 0x00);
            return;
        }
        case DIRQL:{
            //sanity clear interrupts so nesting occours
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)DIRQL);    
            asm("sti");
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerUnmask, 0x00);
            return;
        } 
        case CLOCK_LEVEL:{
            //sanity clear interrupts so nesting occours
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)CLOCK_LEVEL);    
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerUnmask, 0x00);
            return;
        }
        case HIGH_LEVEL:{
            if(ApicTimerInitialized)ApicHalSetLocalApicLvtTimerRegister(0x00, &ApicTimerMask, 0x00);
            asm("cli");
            SetWinIRQL((UINT8)HIGH_LEVEL);    
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
    LouKeMemoryBarrier();
}

void KeLowerIrql(LouKIRQL DispatchLevel){//For WDK Compatibility
    LouKeSetIrql(DispatchLevel, 0x00);
    LouKeMemoryBarrier();
}

