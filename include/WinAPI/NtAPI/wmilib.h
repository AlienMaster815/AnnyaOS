#ifndef WMILIB_H
#define WMILIB_H

#include <NtAPI.h>
#include "irp.h"


LOUSTATUS WmiCompleteRequest(
         struct _DEVICE_OBJECT* DeviceObject,
    PIRP           Irp,
         LOUSTATUS       Status,
         ULONG          BufferUsed,
         CCHAR          PriorityBoost
);



LOUSTATUS WmiFireEvent(
             struct _DEVICE_OBJECT* DeviceObject,
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

LOUSTATUS WmiSystemControl(
        PWMILIB_CONTEXT         WmiLibInfo,
        struct _DEVICE_OBJECT*          DeviceObject,
    PIRP                    Irp,
       PSYSCTL_IRP_DISPOSITION IrpDisposition
);



#endif
