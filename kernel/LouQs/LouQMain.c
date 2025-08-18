#include <LouAPI.h>


PLOUQ_WORK_STRUCTURE 
LouKeMallocLouQWorkManagement(
    string      Identifier, 
    uint64_t    StructureFlags, 
    size_t      MaxActive
){
    uint64_t PageFlags = KERNEL_GENERIC_MEMORY;
    (StructureFlags & USER_WORK_QUEUE) ? PageFlags |= USER_PAGE : 0; 
    PLOUQ_WORK_STRUCTURE Result = LouKeMallocType(LOUQ_WORK_STRUCTURE, PageFlags);
    Result->ActiveMembers = LouKeMallocArray(LOUQ_WORK, MaxActive, PageFlags);
    Result->ActiveQCount = 0 ;
    Result->StructureFlags = StructureFlags;
    Result->Identifier = Identifier;
    return Result;
}

LOUSTATUS LouKeInitializeLouQ(
    PLOUQ               Queue,
    string              Identifier,
    UINT64              QueueFlags,
    UINT64              Timeout,
    UINT64              QueueLimit,
    UINT64              Priority,
    PLOUQ_COMPLETION    Completion,
    PVOID               QueueHandler,
    PVOID               QueueHandlerData
){
    if((!Queue) || (!QueueHandler)){
        return STATUS_INVALID_PARAMETER;
    }

    memset(Queue, 0, sizeof(LOUQ));

    Queue->Identifer = Identifier;
    Queue->LOUQFlags = QueueFlags;
    Queue->QueueTimeout = Timeout;
    Queue->QueueLimit = QueueLimit;
    Queue->Priority = Priority;
    Queue->Completion = Completion;



    return STATUS_SUCCESS;
}