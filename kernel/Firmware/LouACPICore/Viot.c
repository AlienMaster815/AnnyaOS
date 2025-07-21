#include <LouACPI.h>
#include <acpi.h>

static ACPI_TABLE_VIOT* Viot = 0x00;

static LOUSTATUS ViotParseNode(ACPI_VIOT_HEADER* Header){

    LouPrint("ViotParseNode()\n");
    while(1);
    return STATUS_SUCCESS;
}

void EarlyInitializeViot(){
    INTEGER             i = 0;
    ACPI_STATUS         Status = AE_OK;
    PACPI_TABLE_HEADER  TableHeader = 0x00;
    ACPI_VIOT_HEADER*   Node = 0x00;

    Status = AcpiGetTable(ACPI_SIG_VIOT, 0, &TableHeader);
    if(ACPI_FAILURE(Status)){
        if(Status != AE_NOT_FOUND){
            const string Message = AcpiFormatException(Status);
            LouPrint("ACPICA Error:%s", Message);
        }
        return;
    }

    Viot = (ACPI_TABLE_VIOT*)(void*)TableHeader;
    Node = ACPI_ADD_PTR(ACPI_VIOT_HEADER, Viot, Viot->NodeOffset);
    for(i = 0 ; i < Viot->NodeCount; i++){
        if(ViotParseNode(Node)){
            return;
        }
        Node = ACPI_ADD_PTR(ACPI_VIOT_HEADER, Node, Node->Length);
    }

    AcpiPutTable(TableHeader);
}