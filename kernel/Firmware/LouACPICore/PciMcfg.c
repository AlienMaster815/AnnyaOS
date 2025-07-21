#include <LouACPI.h>
#include <acpi.h>

LOUSTATUS ParsePciMcfg(PACPI_TABLE_HEADER Header){


    LouPrint("ParsePciMcfg()\n");
    while(1);
    return AE_OK;
}

void PciMmcfgLateInit(){
    LouPrint("PciMmcfgLateInit()\n");
    LOUSTATUS Status = LouKeAcpiTableTableParse(ACPI_SIG_MCFG, ParsePciMcfg);
    if(Status != STATUS_SUCCESS){
        LouPrint("Error Saving PCI MCFG\n");
    }
}