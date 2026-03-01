#include "NtOsKrnl.h"


LOUAPI
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
