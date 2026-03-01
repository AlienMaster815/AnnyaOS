#include <LouDDK.h>


LOUDDK_API_ENTRY
LOUSTATUS 
NtCommitComplete(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY
LOUSTATUS 
NtCommitEnlistment(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){

    return STATUS_SUCCESS;
}

// NtCommitTransaction