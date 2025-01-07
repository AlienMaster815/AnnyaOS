#ifndef WDMSEC_H
#define WDMSEC_H

#include <NtAPI.h>
#include "../WinAPITypes/CommonTypes.h"

NTSTATUS WdmlibIoCreateDeviceSecure(
             PDRIVER_OBJECT   DriverObject,
             ULONG            DeviceExtensionSize,
   PUNICODE_STRING  DeviceName,
             DEVICE_TYPE      DeviceType,
             ULONG            DeviceCharacteristics,
             BOOLEAN          Exclusive,
             PCUNICODE_STRING DefaultSDDLString,
   LPCGUID          DeviceClassGuid,
                 PDEVICE_OBJECT   *DeviceObject
);

NTSTATUS WdmlibIoValidateDeviceIoControlAccess(
   PIRP  Irp,
   ULONG RequiredAccess
);

NTSTATUS WdmlibRtlInitUnicodeStringEx(
            PUNICODE_STRING DestinationString,
   PCWSTR          SourceString
);

#ifndef _WMI_CHANGER_PROBLEM_DEVICE_ERROR
#define _WMI_CHANGER_PROBLEM_DEVICE_ERROR
typedef struct _WMI_CHANGER_PROBLEM_DEVICE_ERROR {
  ULONG ChangerProblemType;
} WMI_CHANGER_PROBLEM_DEVICE_ERROR, *PWMI_CHANGER_PROBLEM_DEVICE_ERROR;
#endif




#endif 