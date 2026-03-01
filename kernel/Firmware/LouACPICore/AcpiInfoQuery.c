#include <LouACPI.h>

#define INTERMEDIATE_TABLE_PARSER_CHECK (CurreLOUSTATUS == STATUS_SUCCESS) || (CurreLOUSTATUS == STATUS_NO_SUCH_DEVICE)


LOUSTATUS LouACPIInfoQueryCheckFADT(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput);
LOUSTATUS LouACPIInfoSetCheckFADT(LOU_ACPI_INFORMATION_ID InputID ,PLOU_ACPI_INFORMATION InfoInput);

LOUSTATUS LouACPIInfoQueryCheckFACS(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput);
LOUSTATUS LouACPIInfoSetCheckFACS(LOU_ACPI_INFORMATION_ID InputID, PLOU_ACPI_INFORMATION InfoInput);


LOUSTATUS LouKeAcpiInformationQuery(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput){
    if(!InfoOutput){
        return STATUS_INVALID_PARAMETER;
    }
    InfoOutput->InfoID = OutputID;
    LOUSTATUS CurreLOUSTATUS = STATUS_SUCCESS;
    CurreLOUSTATUS = LouACPIInfoQueryCheckFADT(OutputID, InfoOutput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurreLOUSTATUS;
    }
    CurreLOUSTATUS = LouACPIInfoQueryCheckFACS(OutputID, InfoOutput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurreLOUSTATUS;
    }
    return CurreLOUSTATUS;
}

LOUSTATUS LouKeAcpiSetInformation(PLOU_ACPI_INFORMATION InfoInput){
    if(!InfoInput){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS CurreLOUSTATUS = STATUS_SUCCESS;
    CurreLOUSTATUS = LouACPIInfoSetCheckFADT(InfoInput->InfoID, InfoInput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurreLOUSTATUS;
    }
    CurreLOUSTATUS = LouACPIInfoSetCheckFACS(InfoInput->InfoID, InfoInput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurreLOUSTATUS;
    }
    return CurreLOUSTATUS;
}