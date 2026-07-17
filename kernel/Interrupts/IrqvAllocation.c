#include <LouAPI.h>

#define TOTAL_PROCESSOR_VECTORS 223

typedef LOUSTATUS   (*LOUSINE_INTERRUPT_ROUTINE)(UINT64);
typedef LOUSTATUS   (*LOUSINE_EXTENDED_INTERRUPT_ROUTINE)(UINT64, UINT64*);
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

typedef struct _IPIC{
    ListHeader              Peers;
    BOOLEAN                 ProcessorEnabled;
    SIZE                    VectorAllocationCount;
    SIZE                    VectorDataCount[0xFF];
    ListHeader              VectorData[0xFF];
}IPIC, * PIPIC;


typedef struct _IPIC_VECTOR_OBJECT_HANDLE{
    enum{
                                    VectorObject = 0,
                                    VectorGroup,
    }                               HandleType;
    union{
        struct{
            SIZE                    GroupCount;
            PIPIC_VECTOR_OBJECT     GroupMembers;
        }                           VectorGroup;
        IPIC_VECTOR_OBJECT          VectorObject;
    };
}IPIC_VECTOR_OBJECT_HANDLE, * PIPIC_VECTOR_OBJECT_HANDLE;

static PIPIC Ipics = 0x00;
static SIZE IpicsAllocated = 0;

KERNEL_EXPORT LOUSTATUS LouKeInitializeIpicSubsystem(SIZE Processors){
    Ipics = LouKeMallocArray(IPIC, Processors, KERNEL_GENERIC_MEMORY);
    if(!Ipics){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    IpicsAllocated = Processors;
    Ipics[0].ProcessorEnabled = true;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS LouKeIpicCreateVectorObject(
    OPAQUE_PTR*         VectorObjectOut,
    SIZE                Processor,
    SIZE                Vector,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData,
    SIZE                Items
){

    if(
        (!Items) || (!VectorObjectOut) || (!Routine) || 
        ((SIZE)RoutineType > (SIZE)LirExRoutine) || ((Vector + Items) > 0xFF)
    ){
        return STATUS_INVALID_PARAMETER;
    }
    PIPIC_VECTOR_OBJECT_HANDLE Out = LouKeMallocType(IPIC_VECTOR_OBJECT_HANDLE, KERNEL_GENERIC_MEMORY);
    PIPIC_VECTOR_OBJECT NewVectorObject;
    if(!Out){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *VectorObjectOut = (OPAQUE_PTR)Out;
    if(Items == 1){
        Out->HandleType = VectorObject;
        NewVectorObject = &Out->VectorObject;
        goto _INITIALIZE_VECTOR_OBJECT;
    }
    NewVectorObject = LouKeMallocArray(IPIC_VECTOR_OBJECT, Items, KERNEL_GENERIC_MEMORY);
    if(!NewVectorObject){
        LouKeFree(Out);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Out->HandleType = VectorGroup;
    Out->VectorGroup.GroupCount = Items;
    Out->VectorGroup.GroupMembers = NewVectorObject;

_INITIALIZE_VECTOR_OBJECT:

    for(SIZE i = 0; i < Items; i++){
        NewVectorObject[i].VectorID = Vector + i;
        NewVectorObject[i].Ipic = &Ipics[Processor];
        NewVectorObject[i].SoftMasked = true;
        NewVectorObject[i].NeedFlotationSave = NeedFlotationSave;
        NewVectorObject[i].LirData = LirData;
        NewVectorObject[i].RoutineType = RoutineType;
        switch(RoutineType){
            case IsrRoutine:
                NewVectorObject[i].Routine.Isr = (INTERRUPT_SERVICE_ROUTINE)Routine;
                break;
            case LirRoutine:
                NewVectorObject[i].Routine.Lir = (LOUSINE_INTERRUPT_ROUTINE)Routine;
                break;
            case LirExRoutine:
                NewVectorObject[i].Routine.LirEx = (LOUSINE_EXTENDED_INTERRUPT_ROUTINE)Routine;
                break;
        }
        Ipics[Processor].VectorDataCount[Vector + i]++;
        Ipics[Processor].VectorAllocationCount++;
        LouKeMemoryBarrier();
        LouKeLListAddTail(&NewVectorObject[i].Peers, &Ipics[Processor].VectorData[Vector + i]);
    }
    return STATUS_SUCCESS;
}

LOUSTATUS LouKeIpicAllocateVectorObjectsEx(
    OPAQUE_PTR*         VectorObjectOut,
    SIZE                Processor,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData,
    SIZE                Vectors
){
    if((Vectors > 32) || (!VectorObjectOut)){
        return STATUS_INVALID_PARAMETER;
    }
    PIPIC TmpIpic = &Ipics[Processor];

    SIZE GroundStates = UINT32_MAX;
    SIZE GroundStatesVector = 0x30;
    for(SIZE TmpVector = GroundStatesVector; TmpVector < (0xFF - Vectors); TmpVector++){
        SIZE Sum = 0;
        for(SIZE i = 0 ; i < Vectors; i++){
            Sum += TmpIpic->VectorDataCount[TmpVector + i];
        }   
        if(Sum < GroundStates){
            GroundStates = Sum;
            GroundStatesVector = TmpVector;
        }
    }

    LouKeIpicCreateVectorObject(
        VectorObjectOut,
        Processor,
        GroundStatesVector,
        NeedFlotationSave,
        RoutineType,
        Routine,
        LirData,
        Vectors
    );

    return STATUS_SUCCESS;
}

LOUSTATUS LouKeIpicAllocateVectorObjects(
    OPAQUE_PTR*         VectorObjectOut,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData,
    SIZE                Vectors    
){
    if((Vectors > 32) || (!VectorObjectOut)){
        return STATUS_INVALID_PARAMETER;
    }
    UNUSED PIPIC       TmpIpic;
    UNUSED SIZE        GroundState = UINT32_MAX;
    UNUSED SIZE        GroundStateProcessorID = 0;

    for(SIZE i = 0; i < IpicsAllocated; i++){
        if(!Ipics[i].ProcessorEnabled){
            continue;
        }
        if(Ipics[i].VectorAllocationCount < GroundState){
            GroundStateProcessorID = i;
            GroundState = Ipics[i].VectorAllocationCount;
        }
    }
    
    return LouKeIpicAllocateVectorObjectsEx(
        VectorObjectOut,
        GroundStateProcessorID,
        NeedFlotationSave,
        RoutineType,
        Routine,
        LirData,
        Vectors
    );
}

LOUSTATUS LouKeIpicAllocateVectorObjectEx(
    OPAQUE_PTR*         VectorObjectOut, 
    SIZE                Processor,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData
){
    return LouKeIpicAllocateVectorObjectsEx(
        VectorObjectOut, 
        Processor, 
        NeedFlotationSave,
        RoutineType,
        Routine,
        LirData,
        1
    );
}

LOUSTATUS LouKeIpicAllocateVectorObject(
    OPAQUE_PTR*         VectorObjectOut,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData
){
    return LouKeIpicAllocateVectorObjects(
        VectorObjectOut, 
        NeedFlotationSave,
        RoutineType,
        Routine,
        LirData,
        1
    );
}

KERNEL_EXPORT LOUSTATUS LouKeIpicSoftwareMaskVectorObject(OPAQUE_PTR Object, SIZE GroupMember, BOOLEAN Mask){
    if(!VectorObject){
        return STATUS_INVALID_PARAMETER;
    }
    PIPIC_VECTOR_OBJECT_HANDLE ObjectHandle = (PIPIC_VECTOR_OBJECT_HANDLE)Object;
    if(ObjectHandle->HandleType == VectorObject){
        if(GroupMember){
            return STATUS_INVALID_PARAMETER;
        }

        ObjectHandle->VectorObject.SoftMasked = Mask;
        return STATUS_SUCCESS;
    }
    if(ObjectHandle->VectorGroup.GroupCount <= GroupMember){
        return STATUS_INVALID_PARAMETER;
    }
    ObjectHandle->VectorGroup.GroupMembers[GroupMember].SoftMasked = Mask;
    return STATUS_SUCCESS;
}
