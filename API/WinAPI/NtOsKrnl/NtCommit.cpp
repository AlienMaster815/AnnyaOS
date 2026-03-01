#include <LouDDK.h>


LOUAPI
LOUSTATUS 
NtCommitComplete(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){
    return STATUS_SUCCESS;
}


LOUAPI
LOUSTATUS 
NtCommitEnlistment(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){

    return STATUS_SUCCESS;
}

// NtCommitTransaction