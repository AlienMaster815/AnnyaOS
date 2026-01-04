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
static LouKIRQL* SmpSystemInterruptLayer = 0x00;

void LouKeEnableSmpIrqlManagement(INTEGER Cpus){
    SmpSystemInterruptLayer = LouKeMallocArray(LouKIRQL, Cpus, KERNEL_GENERIC_MEMORY);
    for(INTEGER i = 0 ; i <  Cpus; i++){
        SmpSystemInterruptLayer[i] = HIGH_LEVEL;
    }
}

LouKIRQL InterruptSwitch(LouKIRQL New){
    LouKIRQL Old; 
    INTEGER ProcessorID = GetCurrentCpuTrackMember();

    if(SmpSystemInterruptLayer){
        Old = SmpSystemInterruptLayer[ProcessorID];
        SmpSystemInterruptLayer[ProcessorID] = New;
        LouKeMemoryBarrier();
        return Old;
    }
    
    Old = SystemInterruptLevel;
    SystemInterruptLevel = New;
    LouKeMemoryBarrier();
    return Old;
}

void LocalApicSetTimer(bool On);
void LouKeSendIcEOI();

LouKIRQL LouKeGetIrql(){
    LouKeMemoryBarrier();
    INTEGER ProcessorID = GetCurrentCpuTrackMember();
    if(SmpSystemInterruptLayer){
        return SmpSystemInterruptLayer[ProcessorID];
    }
    return SystemInterruptLevel;
}

void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
){
    if(SmpSystemInterruptLayer){
        INTEGER ProcessorID = GetCurrentCpuTrackMember();

        if(OldIrql != 0x00){//0x00 is null in this system and is excplicitly checked for sanity
            *OldIrql = SmpSystemInterruptLayer[ProcessorID]; // save the old irql1
        }

        switch (NewIrql){
            case PASSIVE_LEVEL:{
                SmpSystemInterruptLayer[ProcessorID] = PASSIVE_LEVEL;
                LouKeMemoryBarrier();
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
                SmpSystemInterruptLayer[ProcessorID] = HIGH_LEVEL;
                LouKeMemoryBarrier();
                return;
            }
            default: // error case
                return;
        }

    }else{
        if(OldIrql != 0x00){//0x00 is null in this system and is excplicitly checked for sanity
            *OldIrql = SystemInterruptLevel; // save the old irql1
        }

        switch (NewIrql){
            case PASSIVE_LEVEL:{
                SystemInterruptLevel = PASSIVE_LEVEL;
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
            }
            default: // error case
                return;
        }
    }
}

void LouKeSetIrql(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
){
    if(SmpSystemInterruptLayer){
        INTEGER ProcessorID = GetCurrentCpuTrackMember();

        if(OldIrql != 0x00){//0x00 is null in this system and is excplicitly checked for sanity
            *OldIrql = SmpSystemInterruptLayer[ProcessorID]; // save the old irql1
        }

        switch (NewIrql){
            case PASSIVE_LEVEL:{
                SmpSystemInterruptLayer[ProcessorID] = PASSIVE_LEVEL;
                asm("sti");
                LouKeMemoryBarrier();
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
                SmpSystemInterruptLayer[ProcessorID] = HIGH_LEVEL;
                asm("cli");
                LouKeMemoryBarrier();
                return;
            }
            default: // error case
                return;
        }

    }else{
        if(OldIrql != 0x00){//0x00 is null in this system and is excplicitly checked for sanity
            *OldIrql = SystemInterruptLevel; // save the old irql1
        }

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

