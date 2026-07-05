#include <LouAPI.h>


UINT64 LouKeRouterFallbackIsr(UINT64 StackPtr){
  
    return StackPtr;
} 


void LouKeDebugTrap();

void LouKeSetIrqlNoFlagUpdate(
    LouKIRQL  NewIrql,
    LouKIRQL* OldIrql
);