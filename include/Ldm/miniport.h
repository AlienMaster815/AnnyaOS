#ifndef _LDM_MINIPORT_H
#define _LDM_MINIPORT_H

#include <Ldm.h>

typedef enum _BUS_DATA_TYPE{
	Cmos = 0,
	EisaConfiguration = 1,
	Pos = 2,
	CbusConfiguration = 3,
	PCIConfiguration = 4,
	VMEConfiguration = 5,
	NuBusConfiguration = 6,
	PCMCIAConfiguration = 7,
	MPIConfiguration = 8,
	MPSAConfiguration = 9,
	PNPISAConfiguration = 10,
	SgiInternalConfiguration = 11,
	MaximumBusDataType = 12,
}BUS_DATA_TYPE, * PBUS_DATA_TYPE;

typedef enum _INTERFACE_TYPE{
	InterfaceTypeUndefined = 0,
	Internal,
	Isa,
	Eisa,
	MicroChannel,
	TurboChannel,
	PCIBus,
	VMEBus,
	NuBus,
	PCMCIABus,
	CBus,
	MPIBus,
	MPSABus,
	ProcessorInternal,
	InternalPowerBus,
	PNPISABus,
	PNPBus,
	Vmcs,
	ACPIBus,
	MaximumInterfaceType
}INTERFACE_TYPE, * PINTERFACE_TYPE;

typedef enum _IRQ_DEVICE_POLICY{
	IrqPolicyMachineDefault = 0,
	IrqPolicyAllCloseProcessors,
	IrqPolicyOneCloseProcessor,
	IrqPolicyAllProcessorsInMachine,
	IrqPolicySpecifiedProcessors,
	IrqPolicySpreadMessagesAcrossAllProcessors,
	IrqPolicyAllProcessorsInMachineWhenSteered
}IRQ_DEVICE_POLICY, * PIRQ_DEVICE_POLICY;

typedef enum _IRQ_PRIORITY{
	IrqPriorityUndefined = 0,
	IrqPriorityLow,
	IrqPriorityNormal,
	IrqPriorityHigh
}IRQ_PRIORITY, * PIRQ_PRIORITY;

typedef enum _KINTERRUPT_MODE{
	LevelSensitive = 0,
	Latched
}KINTERRUPT_MODE;

typedef enum _KINTERRUPT_POLARITY{
	InterruptPolarityUnknown = 0,
	InterruptActiveHigh,
	InterruptRisingEdge,
	InterruptActiveLow,
	InterruptFallingEdge,
	InterruptActiveBoth,
	InterruptActiveBothTriggerLow,
	InterruptActiveBothTriggerHigh
}KINTERRUPT_POLARITY, * PKINTERRUPT_POLARITY;

typedef enum _MEMORY_CACHING_TYPE{
	MmNonCached = 0,
	MmCached,
	MmWriteCombined,
	MmHardwareCoherentCached,
	MmNonCachedUnordered,
	MmUSWCCached,
	MmMaximumCacheType,
	MmNotMapped
}MEMORY_CACHING_TYPE;

typedef struct _IO_RESOURCE_DESCRIPTOR{
	UCHAR                           Option;
	UCHAR                           Type;
	UCHAR                           ShareDisposition;
	UCHAR                           Spare1;
	USHORT                          Flags;
	USHORT                          Spare2;
	union {
		struct {
			ULONG                   Length;
			ULONG                   Alignment;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Port;
		struct {
			ULONG                   Length;
			ULONG                   Alignment;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Memory;
		struct {
			ULONG                   MinimumVector;
			ULONG                   MaximumVector;
			IRQ_DEVICE_POLICY       AffinityPolicy;
			USHORT                  Group;
			IRQ_PRIORITY            PriorityPolicy;
			KAFFINITY               TargetedProcessors;
		}                           Interrupt;
		struct {
			ULONG                   MinimumChannel;
			ULONG                   MaximumChannel;
		}                           Dma;
		struct {
			ULONG                   RequestLine;
			ULONG                   Reserved;
			ULONG                   Channel;
			ULONG                   TransferWidth;
		}                           DmaV3;
		struct {
			ULONG                   Length;
			ULONG                   Alignment;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Generic;
		struct {
			ULONG                   Data[3];
		}                           DevicePrivate;
		struct {
			ULONG                   Length;
			ULONG                   MinBusNumber;
			ULONG                   MaxBusNumber;
			ULONG                   Reserved;
		}                           BusNumber;
		struct {
			ULONG                   Priority;
			ULONG                   Reserved1;
			ULONG                   Reserved2;
		}                           ConfigData;
		struct {
			ULONG                   Length40;
			ULONG                   Alignment40;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Memory40;
		struct {
			ULONG                   Length48;
			ULONG                   Alignment48;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Memory48;
		struct {
			ULONG                   Length64;
			ULONG                   Alignment64;
			PHYSICAL_ADDRESS        MinimumAddress;
			PHYSICAL_ADDRESS        MaximumAddress;
		}                           Memory64;
		struct {
			UCHAR                   Class;
			UCHAR                   Type;
			UCHAR                   Reserved1;
			UCHAR                   Reserved2;
			ULONG                   IdLowPart;
			ULONG                   IdHighPart;
		}                           Connection;
	}                               u;
}IO_RESOURCE_DESCRIPTOR, * PIO_RESOURCE_DESCRIPTOR;



struct _CM_RESOURCE_LIST;

typedef struct _BUS_HANDLER{
    ULONG                   Version;
    //INTERFACE_TYPE          InterfaceType;
    BUS_DATA_TYPE           ConfigurationType;
    ULONG                   BusNumber;
    PDEVICE_OBJECT          DeviceObject;
    struct _BUS_HANDLER*    ParentHandler;
    PVOID                   BusData;
    ULONG                   DeviceControlExtentionSize;
    //PSUPPORTED_RANGES       BusAddresses;
    //ULONG                   Reserved[4];
    //ULONG                   (*GetBusData)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, ULONG arg3, VOID* arg4, ULONG arg5, ULONG arg6);
    //ULONG                   (*SetBusData)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, ULONG arg3, VOID* arg4, ULONG arg5, ULONG arg6);
    //LONG                    (*AdjustResourceList)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, struct _IO_RESOURCE_REQUIREMENTS_LIST** arg3);
    //LONG                    (*AssignSlotResources)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, struct _UNICODE_STRING* arg3, struct _UNICODE_STRING* arg4, struct _DRIVER_OBJECT* arg5, struct _DEVICE_OBJECT* arg6, ULONG arg7, struct _CM_RESOURCE_LIST** arg8);
    //UCHAR                   (*TranslateBusAddress)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, union _LARGE_INTEGER arg3, ULONG* arg4, union _LARGE_INTEGER* arg5);
    PVOID                   Spare1;
    PVOID                   Spare2;
    PVOID                   Spare3;
    PVOID                   Spare4;
    PVOID                   Spare5;
    PVOID                   Spare6;
    PVOID                   Spare7;
    PVOID                   Spare8;
}BUS_HANDLER, * PBUS_HANDLER;


#endif