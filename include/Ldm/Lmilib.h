
#ifndef _LMI_LIB_H
#define _LMI_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Ldm.h>

typedef void* PLMI_QUERY_DATABLOCK;
typedef void* PLMI_SET_DATABLOCK;
typedef void* PLMI_SET_DATAITEM;
typedef void* PLMI_FUNCTION_CONTROL;
typedef void* PLMI_EXECUTE_METHOD;

typedef enum _SYSCTL_IRP_DISPOSITION{
    IrpProcessed = 0,
    IrpNotCompleted,
    IrpNotLMI, 
    IrpForward,
}SYSCTL_IRP_DISPOSITION, * PSYSCTL_IRP_DISPOSITION;

typedef 
LOUSTATUS 
LMI_QUERY_REGINFO(
  PDEVICE_OBJECT      DeviceObject, 
  PULONG              RegFlags, 
  PUNICODE_STRING     InstanceName, 
  PUNICODE_STRING*    RegPath,
  PUNICODE_STRING*    MofResourceName,
  PDEVICE_OBJECT*     PDevObj
);

typedef LMI_QUERY_REGINFO* PLMI_QUERY_REGINFO;

typedef struct _LMIGUIDREGINFO {
  LPCGUID Guid;
  ULONG   InstanceCount;
  ULONG   Flags;
} LMIGUIDREGINFO, *PLMIGUIDREGINFO;

typedef struct _LMILIB_CONTEXT {
  ULONG                 GuidCount;
  PLMIGUIDREGINFO       GuidList;
  PLMI_QUERY_REGINFO    QueryLMIRegInfo;
  PLMI_QUERY_DATABLOCK  QueryLMIDataBlock;
  PLMI_SET_DATABLOCK    SetLMIDataBlock;
  PLMI_SET_DATAITEM     SetLMIDataItem;
  PLMI_EXECUTE_METHOD   ExecuteLMIMethod;
  PLMI_FUNCTION_CONTROL LMIFunctionControl;
} LMILIB_CONTEXT, *PLMILIB_CONTEXT;


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
//LOUSTATUS LMISystemControl(
//    PLMILIB_CONTEXT         LMILibInfo,
//    PDEVICE_OBJECT          DeviceObject,
//    PIRP                    Irp,
//    PSYSCTL_IRP_DISPOSITION IrpDisposition
//);


#ifdef __cplusplus
}
#endif
#endif