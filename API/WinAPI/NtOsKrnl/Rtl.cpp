#include "NtOsKrnl.h"


LOUDDK_API_ENTRY
bool
RtlDeleteElementGenericTable(
    PRTL_GENERIC_TABLE Table,
    PVOID              Buffer
){
    if (!Table) {
        return false;
    }

    return false;
}
