#include <LouAPI.h>

#define TOTAL_PROCESSOR_VECTORS 223

typedef LOUSTATUS   (*LOUSINE_INTERRUPT_ROUTINE)(UINT64);
typedef LOUSTATUS   (*LOUSINE_EXTENDED_INTERRUPT_ROUTINE)(UINT64, UINT64);
typedef UINT64      (*INTERRUPT_SERVICE_ROUTINE)(UINT64);

typedef struct _IPIC_VECTOR_OBJECT{
    ListHeader                              Peers;
    SIZE                                    VectorID;
    KHANDLE                                 Ipic;
    BOOLEAN                                 SoftMasked;
    BOOLEAN                                 NeedFlotationSave;
    UINT64                                  LirData;
    enum{
                                            IsrRoutine = 0,
                                            LirRoutine, 
                                            LirExRoutine, 
    }                                       RoutineType;
    union{
        INTERRUPT_SERVICE_ROUTINE           Isr;
        LOUSINE_INTERRUPT_ROUTINE           Lir;
        LOUSINE_EXTENDED_INTERRUPT_ROUTINE  LirEx;
    }                                       Routine;
}IPIC_VECTOR_OBJECT, * PIPIC_VECTOR_OBJECT;



static const IPIC_VECTOR_OBJECT IpicVectorObjectTemplate = {
    .Peers = {0x00, 0x00},
    .VectorID = 0x21,
    .Ipic = 0x00,
    .SoftMasked = true,
    .NeedFlotationSave = false,
    .LirData = 0x00,
    .RoutineType = IsrRoutine,
    .Routine.Isr = LouKeInterruptFallbackRounter,
};

typedef struct _IPIC{
    ListHeader              Peers;
    SIZE                    ProcessorID;
    SIZE                    VectorAllocationCount;
    PIPIC_VECTOR_OBJECT     VectirData[256];
}IPIC, * PIPIC;

static PIPIC Ipics = 0x00;

static LOUSTATUS LouKeIpicVectorObjectConstuctor(
    PVOID   Object,
    PVOID   ConstructorData
){
    memcpy(Object, &IpicVectorObjectTemplate, sizeof(IPIC_VECTOR_OBJECT));
    LouKeMemoryBarrier();
    return STATUS_SUCCESS;
} 

LOUSTATUS LouKeInitializeIpicSubsystem(SIZE Processors){
    
    LouKeCreateFastObjectClassEx(
        "IPIC_VECTOR_OBJECT",
        256,
        sizeof(IPIC_VECTOR_OBJECT),
        GET_ALIGNMENT(IPIC_VECTOR_OBJECT),
        POOL_FLAG_NO_MEMSET,
        KERNEL_GENERIC_MEMORY,
        LouKeIpicVectorObjectConstuctor,
        0x00
    );

    Ipics = LouKeMallocArray(IPIC, Processors, KERNEL_GENERIC_MEMORY);
    if(!Ipics){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    return STATUS_SUCCESS;

}

LOUSTATUS LouKeIpicAllocateVectorObjectEx(
    PIPIC_VECTOR_OBJECT*    VectorObjectOut,
    SIZE                    Processor,
    SIZE                    Vectors    
){
    if((Vectors > 32) || (!VectorObjectOut)){
        return STATUS_INVALID_PARAMETER;
    }
    
    UNUSED PIPIC TmpIpic = &Ipics[Processor];

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeIpicAllocateVectorObject(
    PIPIC_VECTOR_OBJECT*    VectorObjectOut,
    SIZE                    Vectors    
){
    if((Vectors > 32) || (!VectorObjectOut)){
        return STATUS_INVALID_PARAMETER;
    }
    UNUSED PIPIC       TmpIpic;
    UNUSED SIZE        GroundState = UINT32_MAX;
    UNUSED SIZE        GroundStateProcessorID = 0;

    
    return LouKeIpicAllocateVectorObjectEx(
        VectorObjectOut,
        GroundStateProcessorID,
        Vectors
    );
}
