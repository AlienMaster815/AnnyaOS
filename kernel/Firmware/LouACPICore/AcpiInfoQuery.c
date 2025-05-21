#include <LouACPI.h>

#define INTERMEDIATE_TABLE_PARSER_CHECK (CurrentStatus == STATUS_SUCCESS) || (CurrentStatus == STATUS_NO_SUCH_DEVICE)


LOUSTATUS LouACPIInfoQueryCheckFADT(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput);
LOUSTATUS LouACPIInfoSetCheckFADT(LOU_ACPI_INFORMATION_ID InputID ,PLOU_ACPI_INFORMATION InfoInput);

LOUSTATUS LouACPIInfoQueryCheckFACS(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput);
LOUSTATUS LouACPIInfoSetCheckFACS(LOU_ACPI_INFORMATION_ID InputID, PLOU_ACPI_INFORMATION InfoInput);


LOUSTATUS LouKeAcpiInformationQuery(LOU_ACPI_INFORMATION_ID OutputID, PLOU_ACPI_INFORMATION InfoOutput){
    if(!InfoOutput){
        return STATUS_INVALID_PARAMETER;
    }
    InfoOutput->InfoID = OutputID;
    LOUSTATUS CurrentStatus = STATUS_SUCCESS;
    CurrentStatus = LouACPIInfoQueryCheckFADT(OutputID, InfoOutput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurrentStatus;
    }
    CurrentStatus = LouACPIInfoQueryCheckFACS(OutputID, InfoOutput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurrentStatus;
    }
    return CurrentStatus;
}

LOUSTATUS LouKeAcpiSetInformation(PLOU_ACPI_INFORMATION InfoInput){
    if(!InfoInput){
        return STATUS_INVALID_PARAMETER;
    }
    LOUSTATUS CurrentStatus = STATUS_SUCCESS;
    CurrentStatus = LouACPIInfoSetCheckFADT(InfoInput->InfoID, InfoInput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurrentStatus;
    }
    CurrentStatus = LouACPIInfoSetCheckFACS(InfoInput->InfoID, InfoInput);
    if(INTERMEDIATE_TABLE_PARSER_CHECK){
        return CurrentStatus;
    }
    return CurrentStatus;
}