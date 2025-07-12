#include <LouACPI.h>
#include <acpi.h>

static PLOUQ_WORK_STRUCTURE Acpid       = 0x00;
static PLOUQ_WORK_STRUCTURE AcpiNotify  = 0x00;
static PLOUQ_WORK_STRUCTURE AcpiHotplug = 0x00;
LOUSTATUS AcpiOsiInitialize();

ACPI_STATUS AcpiOsInitialize1(){

    Acpid = LouKeMallocLouQWorkManagement("Acpid", KERNEL_WORK_QUEUE, 1);
    AcpiNotify = LouKeMallocLouQWorkManagement("AcpiNotify", KERNEL_WORK_QUEUE, 1);
    AcpiHotplug = LouKeMallocLouQWorkStream("AcpiHotplug", KERNEL_WORK_QUEUE);
    AcpiOsiInitialize();
    return AE_OK;
}