//Copyright GPL-2 Tyler Grenier (2026)
#include "VmCore.h"

KERNEL_ENTRY 
LOUSTATUS 
VmCoreEntry(){
    PVOID IommuTable = (PVOID)LouKeAcquireAcpiTable(AMD_VIRTUALIZATION_ACPI_TABLE);
    if(IommuTable){

    }else{
        IommuTable = (PVOID)LouKeAcquireAcpiTable(INTEL_VIRTUALIZATION_ACPI_TABLE);
        if(!IommuTable){
            return STATUS_SUCCESS;
        } 



    }

    LouPrint("VmCoreEntry()\n");
    while(1);
    return STATUS_SUCCESS;
}