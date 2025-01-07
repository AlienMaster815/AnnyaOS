#ifndef WMILIB_H
#define WMILIB_H

#include <NtAPI.h>
#include "irp.h"


NTSTATUS WmiCompleteRequest(
         PDEVICE_OBJECT DeviceObject,
    PIRP           Irp,
         NTSTATUS       Status,
         ULONG          BufferUsed,
         CCHAR          PriorityBoost
);



NTSTATUS WmiFireEvent(
             PDEVICE_OBJECT DeviceObject,
             LPCGUID        Guid,
             ULONG          InstanceIndex,
             ULONG          EventDataSize,
  		 PVOID          EventData
);

typedef struct _WMIGUIDREGINFO {
  LPCGUID Guid;
  ULONG   InstanceCount;
  ULONG   Flags;
} WMIGUIDREGINFO, *PWMIGUIDREGINFO;

typedef struct _WMILIB_CONTEXT {
  ULONG                 GuidCount;
  PWMIGUIDREGINFO       GuidList;
  PWMI_QUERY_REGINFO    QueryWmiRegInfo;
  PWMI_QUERY_DATABLOCK  QueryWmiDataBlock;
  PWMI_SET_DATABLOCK    SetWmiDataBlock;
  PWMI_SET_DATAITEM     SetWmiDataItem;
  PWMI_EXECUTE_METHOD   ExecuteWmiMethod;
  PWMI_FUNCTION_CONTROL WmiFunctionControl;
} WMILIB_CONTEXT, *PWMILIB_CONTEXT;

NTSTATUS WmiSystemControl(
        PWMILIB_CONTEXT         WmiLibInfo,
        PDEVICE_OBJECT          DeviceObject,
    PIRP                    Irp,
       PSYSCTL_IRP_DISPOSITION IrpDisposition
);



#endif
