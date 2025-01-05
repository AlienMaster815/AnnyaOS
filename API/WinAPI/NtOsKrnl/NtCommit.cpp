#include <LouDDK.h>


LOUDDK_API_ENTRY
NTSTATUS 
NtCommitComplete(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){
    return STATUS_SUCCESS;
}


LOUDDK_API_ENTRY
NTSTATUS 
NtCommitEnlistment(
  HANDLE         EnlistmentHandle,
  PLARGE_INTEGER TmVirtualClock
){

    return STATUS_SUCCESS;
}

// NtCommitTransaction