#include <LouAPI.h>

void SaveEverythingWithInterruptBuffer(uint64_t* ContextHandle);
void RestoreEverythingWithInterruptBuffer(uint64_t* ContextHandle);

void LouKeDebugTrap();

void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
);

typedef LOUSTATUS   (*LOUSINE_INTERRUPT_ROUTINE)(UINT64);
typedef LOUSTATUS   (*LOUSINE_EXTENDED_INTERRUPT_ROUTINE)(UINT64, UINT64);
typedef UINT64      (*INTERRUPT_SERVICE_ROUTINE)(UINT64);

/*typedef enum{
    IsrRoutine = 0,
    LirRoutine, 
    LirExRoutine, 
}IPIC_ROUTINE_TYPE;*/

typedef struct _IPIC_VECTOR_OBJECT{
    ListHeader                              Peers;
    SIZE                                    VectorID;
    KHANDLE                                 Ipic;
    BOOLEAN                                 SoftMasked;
    BOOLEAN                                 NeedFlotationSave;
    UINT64                                  LirData;
    IPIC_ROUTINE_TYPE                       RoutineType;
    union{
        INTERRUPT_SERVICE_ROUTINE           Isr;
        LOUSINE_INTERRUPT_ROUTINE           Lir;
        LOUSINE_EXTENDED_INTERRUPT_ROUTINE  LirEx;
    }                                       Routine;
}IPIC_VECTOR_OBJECT, * PIPIC_VECTOR_OBJECT;

PListHeader LouKeIpicGetLocalVectorData(
    ULONG Cpu, 
    UINT8 Interrupt
);


void InterruptRouter(uint64_t Interrupt, uint64_t Args){

    ULONG Processor = LouKeGetCurrentProcessorNumber();
    PListHeader ProcessorVectorData = LouKeIpicGetLocalVectorData(Processor, (UINT8)Interrupt);
    PIPIC_VECTOR_OBJECT TmpVectorObject;
    LouKIRQL Irql;
    LouKeSetIrqlNoFlagUpdate(HIGH_LEVEL, &Irql);
    uint64_t ContextHandle = 0x00;
    
    ForEachLListEntry(TmpVectorObject, ProcessorVectorData, Peers){

        
        LouPrint("HERE:%h\n", TmpVectorObject->VectorID);
        while(1);

        if(TmpVectorObject->SoftMasked){
            continue;
        }

        if(TmpVectorObject->NeedFlotationSave){
            SaveEverythingWithInterruptBuffer(&ContextHandle);
        }
        switch(TmpVectorObject->RoutineType){
            case IsrRoutine:
                TmpVectorObject->Routine.Isr(Args);
                break;
            case LirRoutine:
                TmpVectorObject->Routine.Lir(TmpVectorObject->LirData);
                break;
            case LirExRoutine:
                TmpVectorObject->Routine.LirEx(TmpVectorObject->LirData, Args);
                break;
        }
        if(TmpVectorObject->NeedFlotationSave){
            RestoreEverythingWithInterruptBuffer(&ContextHandle);
        }
    }
    while(1);
    LouKeSetIrqlNoFlagUpdate(Irql, 0x00);
    ApicHalSignalLocalApicEoi();
    
}