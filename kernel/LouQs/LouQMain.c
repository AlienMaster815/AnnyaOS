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