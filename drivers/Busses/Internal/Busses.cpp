#include <LouDDK.h>
#include <LouACPI.h>

typedef struct _LOU_BUS_CLASS_TRACKER{
    ListHeader      Peers;
    PLOU_BUS        ClassMember; 
}LOU_BUS_CLASS_TRACKER, * PLOU_BUS_CLASS_TRACKER;

static LOU_BUS_CLASS_TRACKER GobalBusses = {0};

static void AllocateNewClassTracker(PLOU_BUS ClassMember){
    PLOU_BUS_CLASS_TRACKER Busses = &GobalBusses;
    while(Busses->Peers.NextHeader){
        Busses = (PLOU_BUS_CLASS_TRACKER)Busses->Peers.NextHeader;
    }
    Busses->Peers.NextHeader = (PListHeader)LouKeMallocType(LOU_BUS_CLASS_TRACKER, KERNEL_GENERIC_MEMORY);
    Busses = (PLOU_BUS_CLASS_TRACKER)Busses->Peers.NextHeader;
    Busses->ClassMember = ClassMember;
}

static void DeAllocateClassTracker(PLOU_BUS ClassMember){
    PLOU_BUS_CLASS_TRACKER Busses = &GobalBusses;
    PLOU_BUS_CLASS_TRACKER Last = &GobalBusses;
    while(Busses->Peers.NextHeader){
        Last = Busses;
        Busses = (PLOU_BUS_CLASS_TRACKER)Busses->Peers.NextHeader;
        if(Busses->ClassMember == ClassMember){
            Last->Peers.NextHeader = Busses->Peers.NextHeader;
            LouKeFree(Busses);
            return;
        }
    }
}


LOUDDK_API_ENTRY
LOUSTATUS 
LouKeCreateBusClass(
    PLOU_BUS    Bus
){
    LOUSTATUS   Status;
    LouKIRQL    Irql;
    AllocateNewClassTracker(Bus);
    LouKeAcquireSpinLock(&Bus->BusScanLock, &Irql);
    if(Bus->SearchMachine){
        Status = Bus->SearchMachine(Bus);
        if(Status != STATUS_SUCCESS){
            LouKeReleaseSpinLock(&Bus->BusScanLock, &Irql);
            return Status;
        }
    }
    if(Bus->InitializeBus){
        PLOU_BUS_OBJECT Object = Bus->BusObjects;
        while(Object){
            Status = Bus->InitializeBus(Bus, Object);
            if(Status != STATUS_SUCCESS){
                if(Bus->DeInitializeBus){
                    PLOU_BUS_OBJECT Object2 = Bus->BusObjects;
                    while((Object2 != Object) && (Object2)){
                        Bus->DeInitializeBus(Bus, Object2);
                        Object2 =(PLOU_BUS_OBJECT)Object2->Peers.NextHeader;
                    }
                }
                DeAllocateClassTracker(Bus);
                LouKeReleaseSpinLock(&Bus->BusScanLock, &Irql);
                return Status;
            }
            Object = (PLOU_BUS_OBJECT)Object->Peers.NextHeader;
        }
    }
    LouKeReleaseSpinLock(&Bus->BusScanLock, &Irql);
    return STATUS_SUCCESS;
}

void InitializeSerialIo();

LOUDDK_API_ENTRY 
void InitializeBusCore(){
    
    InitializeSerialIo();

}