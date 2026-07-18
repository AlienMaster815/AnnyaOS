#include <LouAPI.h>

#define TOTAL_PROCESSOR_VECTORS 223

typedef enum{
    VECTOR_HANDLE_ID_OBJECT = 0,
    VECTOR_HANDLE_ID_GROUP,
}VECTOR_HANDLE_ID;


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

typedef struct _IPIC_CRITICAL_SECTION{
    LouKIRQL                IpicIrql;
    spinlock_t              IpicLock;
    PVOID                   IpicPeerDataHandle;
}IPIC_CRITICAL_SECTION, * PIPIC_CRITICAL_SECTION;

typedef struct _IPIC{
    IPIC_CRITICAL_SECTION   IpicCriticalSection;
    BOOLEAN                 ProcessorEnabled;
    SIZE                    VectorAllocationCount;
    SIZE                    VectorDataCount[0xFF];
    ListHeader              VectorData[0xFF];
}IPIC, * PIPIC;


typedef struct _IPIC_VECTOR_OBJECT_HANDLE{
    VECTOR_HANDLE_ID                HandleType;
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



LOUSTATUS
LouKeIpicEnterCriticalSection(
    PIPIC_CRITICAL_SECTION  IpicCriticalSection,
    SIZE                    PeerCpu
){
    if(!IpicCriticalSection){
        return STATUS_INVALID_PARAMETER;
    }
    

    LouKeAcquireSpinLock(&IpicCriticalSection->IpicLock, &IpicCriticalSection->IpicIrql);

    return STATUS_SUCCESS;
}


LOUSTATUS
LouKeIpicExitCriticalSection(
    PIPIC_CRITICAL_SECTION  IpicCriticalSection
){
    LouKeReleaseSpinLock(&IpicCriticalSection->IpicLock, &IpicCriticalSection->IpicIrql);
    return STATUS_SUCCESS;
}

PListHeader LouKeIpicGetLocalVectorData(
    ULONG Cpu, 
    UINT8 Interrupt
){
    return &Ipics[Cpu].VectorData[Interrupt];
}

OPAQUE_PTR* GenericRouters = 0x00;

void DivideByZero(UINT64 Stack);
void Debug(UINT64 Rsp);
void NMI(UINT64 Rsp);
void BreakPoint(UINT64 Rsp);
void OverFlow(UINT64 Rsp);
void BoundRange(UINT64 Rsp);
void InvalidOpcode(UINT64 Rsp);
void FloatDeviceNotAvailable(UINT64 Rsp);
void CpOverun(UINT64 Rsp);
void SegmentNotPresent(UINT64 Rsp);
void StackSegmentFault(UINT64 Rsp);
void GPF(UINT64 Rsp);
void PageFault(UINT64 Rsp);
void x87FloatPointError(UINT64 Rsp);
void AlignmentCheck(UINT64 Rsp);
void MachineCheck(UINT64 Rsp);
void SIMDFloatPointException(UINT64 Rsp);
void VirtualizationException(UINT64 Rsp);
void ControlProtectionException(UINT64 Rsp);



KERNEL_EXPORT LOUSTATUS LouKeInitializeIpicSubsystem(SIZE Processors){
    Ipics = LouKeMallocArray(IPIC, Processors, KERNEL_GENERIC_MEMORY);
    if(!Ipics){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    GenericRouters = LouKeMallocArray(OPAQUE_PTR, Processors * 0x16, KERNEL_GENERIC_MEMORY);
    if(!GenericRouters){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    IpicsAllocated = Processors;
    Ipics[0].ProcessorEnabled = true;
    
    for(SIZE i = 0 ; i < Processors; i++){

        OPAQUE_PTR* ObjectPointer = &GenericRouters[i * 0x16];
        LouKeIpicCreateVectorObject(&ObjectPointer[0x00], i, 0x00, false, IsrRoutine, (OPAQUE_PTR)DivideByZero, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x01], i, 0x01, false, IsrRoutine, (OPAQUE_PTR)Debug, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x02], i, 0x02, false, IsrRoutine, (OPAQUE_PTR)NMI, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x03], i, 0x03, false, IsrRoutine, (OPAQUE_PTR)BreakPoint, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x04], i, 0x04, false, IsrRoutine, (OPAQUE_PTR)OverFlow, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x05], i, 0x05, false, IsrRoutine, (OPAQUE_PTR)BoundRange, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x06], i, 0x06, false, IsrRoutine, (OPAQUE_PTR)InvalidOpcode, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x07], i, 0x07, false, IsrRoutine, (OPAQUE_PTR)FloatDeviceNotAvailable, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x08], i, 0x08, false, IsrRoutine, (OPAQUE_PTR)CpOverun, 0, 1);

        LouKeIpicCreateVectorObject(&ObjectPointer[0x0B], i, 0x0B, false, IsrRoutine, (OPAQUE_PTR)SegmentNotPresent, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x0C], i, 0x0C, false, IsrRoutine, (OPAQUE_PTR)StackSegmentFault, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x0D], i, 0x0D, false, IsrRoutine, (OPAQUE_PTR)GPF, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x0E], i, 0x0E, false, IsrRoutine, (OPAQUE_PTR)PageFault, 0, 1);

        LouKeIpicCreateVectorObject(&ObjectPointer[0x10], i, 0x10, false, IsrRoutine, (OPAQUE_PTR)x87FloatPointError, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x11], i, 0x11, false, IsrRoutine, (OPAQUE_PTR)AlignmentCheck, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x12], i, 0x12, false, IsrRoutine, (OPAQUE_PTR)MachineCheck, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x13], i, 0x13, false, IsrRoutine, (OPAQUE_PTR)SIMDFloatPointException, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x14], i, 0x14, false, IsrRoutine, (OPAQUE_PTR)VirtualizationException, 0, 1);
        LouKeIpicCreateVectorObject(&ObjectPointer[0x15], i, 0x15, false, IsrRoutine, (OPAQUE_PTR)ControlProtectionException, 0, 1);

    }

    for(SIZE i = 0 ; i < Processors * 0x16; i++){
        LouKeIpicSoftwareMaskVectorObject(GenericRouters[i], 0, false);
    }
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS LouKeIpicCreateVectorObjectEx(
    OPAQUE_PTR*         VectorObjectOut,
    SIZE                Processor,
    SIZE                Vector,
    BOOLEAN             NeedFlotationSave,
    IPIC_ROUTINE_TYPE   RoutineType,
    OPAQUE_PTR          Routine,
    UINT64              LirData,
    SIZE                Items,
    BOOLEAN             DisableIpcSafety
){
    if(
        (!Items) || (!VectorObjectOut) || (!Routine) || 
        ((SIZE)RoutineType > (SIZE)LirExRoutine) || ((Vector + Items) > 0xFF)
    ){
        //if(!Items){
        //    LouPrint("LouKeIpicCreateVectorObject():Items NULL\n");
        //}
        //if(!VectorObjectOut){
        //    LouPrint("LouKeIpicCreateVectorObject():VectorObjectOut NULL\n");
        //}
        //if(!Routine){
        //    LouPrint("LouKeIpicCreateVectorObject():Routine NULL\n");
        //}
        //if((Vector + Items) > 0xFF){
        //    LouPrint("LouKeIpicCreateVectorObject():Vector Request Overflow\n");
        //}
        return STATUS_INVALID_PARAMETER;
    }
    PIPIC_VECTOR_OBJECT_HANDLE Out = LouKeMallocType(IPIC_VECTOR_OBJECT_HANDLE, KERNEL_GENERIC_MEMORY);
    PIPIC_VECTOR_OBJECT NewVectorObject;
    if(!Out){
        //LouPrint("LouKeIpicCreateVectorObject():Could Not Allocate Object Handle\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    *VectorObjectOut = (OPAQUE_PTR)Out;
    if(Items == 1){
        Out->HandleType = VECTOR_HANDLE_ID_OBJECT;
        NewVectorObject = &Out->VectorObject;
        goto _INITIALIZE_VECTOR_OBJECT;
    }
    NewVectorObject = LouKeMallocArray(IPIC_VECTOR_OBJECT, Items, KERNEL_GENERIC_MEMORY);
    if(!NewVectorObject){
        //LouPrint("LouKeIpicCreateVectorObject():Could Not Allocate Group Data\n");
        LouKeFree(Out);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Out->HandleType = VECTOR_HANDLE_ID_GROUP;
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
        if(DisableIpcSafety){
            LouKeListAddTail(&NewVectorObject[i].Peers, &Ipics[Processor].VectorData[Vector + i]);
        }else{
            LouKeIpicEnterCriticalSection(&Ipics[Processor].IpicCriticalSection, Processor);
            LouKeListAddTail(&NewVectorObject[i].Peers, &Ipics[Processor].VectorData[Vector + i]);
            LouKeIpicExitCriticalSection(&Ipics[Processor].IpicCriticalSection);
        }
        LouKeMemoryBarrier();
    }
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
    return LouKeIpicCreateVectorObjectEx(
        VectorObjectOut,
        Processor,
        Vector,
        NeedFlotationSave,
        RoutineType,
        Routine,
        LirData,
        Items,
        false
    );
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
    if(!Object){
        //LouPrint("LouKeIpicSoftwareMaskVectorObject():Object Is NULL\n");
        return STATUS_INVALID_PARAMETER;
    }
    PIPIC_VECTOR_OBJECT_HANDLE ObjectHandle = (PIPIC_VECTOR_OBJECT_HANDLE)Object;
    if(ObjectHandle->HandleType == VECTOR_HANDLE_ID_OBJECT){
        if(GroupMember){
            //LouPrint("LouKeIpicSoftwareMaskVectorObject():Input Object With Group Object\n");
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
