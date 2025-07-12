#ifndef _ACPI_NAMESPACE_H
#define _ACPI_NAMESPACE_H

#ifndef __cplusplus
#include <LouAPI.h>
#else
#include <LouDDK.h>
extern "C" {
#endif

#include <AcpiAml.h>

#define GENERAL_EVENTS_NAMESPACE        "\\_GPE"
#define PROCESSOR_NAMESPACE             "\\_PR"
#define DEVICES_AND_BUSSES_NAMESPACE    "\\_SB"
#define SYSTEM_INDICATOR_NAMESPACE      "\\_SI"
#define THERMAL_ZONE_NAMESPACE          "\\_TZ"

typedef struct PACKED _AML_PACKAGE_LEAD_BYTE{
    uint8_t Length : 4;
    uint8_t Reserved : 2;
    uint8_t ByteCount : 2;
}AML_PACKAGE_LEAD_BYTE, * PAML_PACKAGE_LEAD_BYTE;

#define LouKeAcpiGetAmlPackageByteCount(PackageLeadByte) (((PAML_PACKAGE_LEAD_BYTE)PackageLeadByte)->ByteCount + 1)

size_t LouKeAcpiGetAmlPackageLength(uint8_t* Buffer);

size_t AmlNameSpaceNameStringLength(uint8_t* String);
string CreateUTF8StringFromAcpiNameString(uint8_t* AmlString);
size_t AmlNameSpaceNameStringLengthToUTF8Length(uint8_t* String);

void LouKeAcpiParsePackageLength(
    uint8_t* AmlStream, 
    size_t Index, 
    string* NameHandle,
    size_t* PackageLength,
    size_t* DataStart
);
#ifdef __cplusplus
}
#endif
#endif