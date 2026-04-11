#include <LouAPI.h>

typedef struct _LOUSINE_ECS_DRIVER_MANAGER{
    mutex_t     DriversLock;
    ListHeader  Drivers;
}LOUSINE_ECS_DRIVER_MANAGER, * PLOUSINE_ECS_DRIVER_MANAGER;

typedef struct _LOUSINE_ECS_DRIVER_TACKER{
    ListHeader              Peers;
    mutex_t                 LockOut;
    PLOUSINE_ECS_DRIVER     DriverObject;
}LOUSINE_ECS_DRIVER_TACKER, * PLOUSINE_ECS_DRIVER_TACKER;

static LOUSINE_ECS_DRIVER_MANAGER EcsDriverManager = {0};

KERNEL_EXPORT 
LOUSTATUS 
LouKeRegisterEcsDriver(
    PLOUSINE_ECS_DRIVER EcsDriver
){
    PLOUSINE_ECS_DRIVER_TACKER NewTracker = LouKeMallocType(LOUSINE_ECS_DRIVER_TACKER, KERNEL_GENERIC_MEMORY);
    NewTracker->DriverObject = EcsDriver;
    //MutexLock(&EcsDriverManager.DriversLock);
    LouKeListAddTail(&NewTracker->Peers, &EcsDriverManager.Drivers);
    //MutexUnlock(&EcsDriverManager.DriversLock);
    return STATUS_SUCCESS;
}


int
LouKeEcsPrintAsciiCharecter(
    CHAR    Charecter
){
    PLOUSINE_ECS_DRIVER_TACKER Tracker;
    if(LouKeListIsEmpty(&EcsDriverManager.Drivers)){
        return 0x00;
    }
    ForEachListEntry(Tracker, &EcsDriverManager.Drivers, Peers){
        //ForEachIf(!MutexIsLocked(&Tracker->LockOut)){
            //if(Tracker->DriverObject->EcsOperations.PrintAsciiCharecter){
                //MutexLock(&Tracker->LockOut);
                Tracker->DriverObject->EcsOperations.PrintAsciiCharecter(Charecter);
                //MutexUnlock(&Tracker->LockOut);
            //}
        //}
    } 
    return 0x00;
}

int 
LouKeEcsPrintUnicodeCharecter(
    UINT32  Charecter
){
    PLOUSINE_ECS_DRIVER_TACKER Tracker;
    if(LouKeListIsEmpty(&EcsDriverManager.Drivers)){
        return 0x00;
    }
    ForEachListEntry(Tracker, &EcsDriverManager.Drivers, Peers){
        //ForEachIf(!MutexIsLocked(&Tracker->LockOut)){
            //if(Tracker->DriverObject->EcsOperations.PrintUnicodeCharecter){
                //MutexLock(&Tracker->LockOut);
                Tracker->DriverObject->EcsOperations.PrintUnicodeCharecter(Charecter);
                //MutexUnlock(&Tracker->LockOut);
            //}
        //}
    } 
    return 0x00;
}

void
LouKeEcsEndofData(){
    
    if(LouKeListIsEmpty(&EcsDriverManager.Drivers)){
        return;
    }
    PLOUSINE_ECS_DRIVER_TACKER Tracker;
    ForEachListEntry(Tracker, &EcsDriverManager.Drivers, Peers){
        //ForEachIf(!MutexIsLocked(&Tracker->LockOut)){
            //if(Tracker->DriverObject->EcsOperations.EndofData){
                //MutexLock(&Tracker->LockOut);
                Tracker->DriverObject->EcsOperations.EndofData();
                //MutexUnlock(&Tracker->LockOut);
            //}
        //}
    } 
}