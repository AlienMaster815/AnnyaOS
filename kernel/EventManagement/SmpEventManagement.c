#include <LouAPI.h>

typedef enum{
    SmpStart = 0, 
}SMP_EVENT_TYPE;

//typedef enum{
//    Low    = 0,
//    Casual,
//    Unusual,
//    Important,
//    Critical,
//}SMP_EVENT_PRIORITY;

typedef struct _SMP_EVENT_LIST{
    ListHeader                  Neighbors; 
    SMP_EVENT_TYPE              EventType;  
    //SMP_EVENT_PRIORITY        EventPriority;
    mutex_t                     EventWaitHandle;
    uintptr_t                   EventData;
}SMP_EVENT_LIST, * PSMP_EVENT_LIST;

static SMP_EVENT_LIST MasterSmpEventList;
static uint64_t NumberOfHandles = 0;

static inline PSMP_EVENT_LIST LouCreateSmpEventHandle(){
    PSMP_EVENT_LIST TmpHandle = &MasterSmpEventList;
    
    for(uint64_t i = 0; i < NumberOfHandles; i++){
        if(TmpHandle->Neighbors.NextHeader){
            TmpHandle = (PSMP_EVENT_LIST)TmpHandle->Neighbors.NextHeader;
        }
    }
    TmpHandle->Neighbors.NextHeader = (PListHeader)LouMalloc(sizeof(SMP_EVENT_LIST));
    return (EventHandle)TmpHandle->Neighbors.NextHeader;
}

static inline void LouDestroySmpEventHandle(
    PSMP_EVENT_LIST SmpList
){
    PSMP_EVENT_LIST TmpHandle = &MasterSmpEventList;
    
    for(uint64_t i = 0; i < NumberOfHandles; i++){
        if(TmpHandle == SmpList){
            PSMP_EVENT_LIST TmpHandle2 = &MasterSmpEventList;
            for(uint64_t j = 0; j < i; j++){
                TmpHandle2 = (PSMP_EVENT_LIST)TmpHandle2->Neighbors.NextHeader;
            }
            TmpHandle2->Neighbors.NextHeader = TmpHandle->Neighbors.NextHeader;
            LouFree((RAMADD)TmpHandle);
            return;
        }
        if(TmpHandle->Neighbors.NextHeader){
            TmpHandle = (PSMP_EVENT_LIST)TmpHandle->Neighbors.NextHeader;
        }
    }
}

static spinlock_t SmpEventCreationLock;

EventHandle LouKeInitiateStartSmpEvent(uint8_t SmpId){
    PSMP_EVENT_LIST SmpEventHandle;
    LouKIRQL Irql;
    LouKeAcquireSpinLock(&SmpEventCreationLock, &Irql);
    SmpEventHandle = LouCreateSmpEventHandle();
    LouKeReleaseSpinLock(&SmpEventCreationLock, &Irql);

    //fill out the table here once this returns theres no manipulation
    //of the data until the finish function
    SmpEventHandle->EventType = SmpStart;
    SmpEventHandle->EventData = SmpId;
    MutexLock(&SmpEventHandle->EventWaitHandle);
    //return Handle
    return (EventHandle)SmpEventHandle;
}
 
void LouKeFinishStartSmpEvent(uint8_t SmpId){


    PSMP_EVENT_LIST SmpEventHandle = &MasterSmpEventList;
    
    for(uint64_t i = 0; i < NumberOfHandles; i++){
        if((uintptr_t)SmpEventHandle->EventData == SmpId){
            break;
        }
        if(SmpEventHandle->Neighbors.NextHeader){
            SmpEventHandle = (PSMP_EVENT_LIST)SmpEventHandle->Neighbors.NextHeader;
        }else if(!SmpEventHandle->Neighbors.NextHeader){
            return;
        }
    }

    LouKIRQL Irql;
    LouKeAcquireSpinLock(&SmpEventCreationLock, &Irql);
    LouDestroySmpEventHandle(SmpEventHandle);
    LouKeReleaseSpinLock(&SmpEventCreationLock, &Irql);

    MutexUnlock(&SmpEventHandle->EventWaitHandle);
}

void LouKeWaitForSmpEventToFinish(EventHandle Event){
    LouPrint("Waiting For Smp Event To Finish\n");
    PSMP_EVENT_LIST SmpHandle = (PSMP_EVENT_LIST)Event;
    while(SmpHandle->EventWaitHandle.locked){
        //TODO: Use A Yeild for faster handleing
        sleep(4); //wait a proc swap cycle
    }
}