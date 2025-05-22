#include <LouDDK.h>



NTSTATUS NtAdjustPrivilegesToken(
    HANDLE TokenHandle,
    bool DisableAllPrivaledges,
    PTOKEN_PRIVALEDGES NewState,
    ULONG BufferLength,
    PTOKEN_PRIVALEDGES PreviousState,
    PULONG ReturnLength
){



    return STATUS_SUCCESS;
}