
#ifndef _LMI_LIB_H
#define _LMI_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm.h>

typedef void* PWMI_QUERY_DATABLOCK;
typedef void* PWMI_SET_DATABLOCK;
typedef void* PWMI_SET_DATAITEM;
typedef void* PWMI_FUNCTION_CONTROL;
typedef void* PWMI_EXECUTE_METHOD;

typedef enum _SYSCTL_IRP_DISPOSITION{
    IrpProcessed = 0,
    IrpNotCompleted,
    IrpNotWmi, 
    IrpForward,
}SYSCTL_IRP_DISPOSITION, * PSYSCTL_IRP_DISPOSITION;

typedef LOUSTATUS(*PLMI_QUERY_REGINFO)(
    PDEVICE_OBJECT      DeviceObject, 
    PULONG              RegFlags, 
    PUNICODE_STRING     InstanceName, 
    PUNICODE_STRING*    RegPath,
    PUNICODE_STRING*    MofResourceName,
    PDEVICE_OBJECT*     PDevObj
);

typedef struct _WMIGUIDREGINFO {
  LPCGUID Guid;
  ULONG   InstanceCount;
  ULONG   Flags;
} WMIGUIDREGINFO, *PWMIGUIDREGINFO;

typedef struct _WMILIB_CONTEXT {
  ULONG                 GuidCount;
  PWMIGUIDREGINFO       GuidList;
  PLMI_QUERY_REGINFO    QueryWmiRegInfo;
  PWMI_QUERY_DATABLOCK  QueryWmiDataBlock;
  PWMI_SET_DATABLOCK    SetWmiDataBlock;
  PWMI_SET_DATAITEM     SetWmiDataItem;
  PWMI_EXECUTE_METHOD   ExecuteWmiMethod;
  PWMI_FUNCTION_CONTROL WmiFunctionControl;
} WMILIB_CONTEXT, *PWMILIB_CONTEXT;


//export as Wmi With Wmilib Kula Alias
//LOUSTATUS LmiCompleteRequest(
//    PDEVICE_OBJECT DeviceObject,
//    PIRP           Irp,
//    LOUSTATUS      Status,
//    ULONG          BufferUsed,
//    CCHAR          PriorityBoost
//);

//export as Wmi With Wmilib Kula Alias
LOUSTATUS LmiFireEvent(
    PDEVICE_OBJECT DeviceObject,
    LPCGUID        Guid,
    ULONG          InstanceIndex,
    ULONG          EventDataSize,
  	PVOID          EventData
);

//export as Wmi With Wmilib Kula Alias
//LOUSTATUS WmiSystemControl(
//    PWMILIB_CONTEXT         WmiLibInfo,
//    PDEVICE_OBJECT          DeviceObject,
//    PIRP                    Irp,
//    PSYSCTL_IRP_DISPOSITION IrpDisposition
//);


#ifdef __cplusplus
}
#endif
#endif