#ifndef _LDM_MINIPORT_H
#define _LDM_MINIPORT_H

#include <cstdio.h>
#include <kernel/memmory.h>
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


typedef struct _IO_RESOURCE_DESCRIPTORV2{
	UCHAR  						Option;
	UCHAR  						Type;
	UCHAR  						ShareDisposition;
	UCHAR  						Spare1;
	USHORT 						Flags;
	USHORT 						Spare2;
	union {
		struct {
			ULONG 				Length;
			ULONG 				Alignment;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS 	MaximumAddress;
		} 						Port;
		struct {
			ULONG 				Length;
			ULONG 				Alignment;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS 	MaximumAddress;
		} 						Memory;
		struct {
			ULONG 				MinimumVector;
			ULONG 				MaximumVector;
			IRQ_DEVICE_POLICY 	AffinityPolicy;
			IRQ_PRIORITY 		PriorityPolicy;
			KAFFINITY 			TargetedProcessors;
		} 						Interrupt;
		struct {
			ULONG 				MinimumChannel;
			ULONG 				MaximumChannel;
		} 						Dma;
		struct {
			ULONG 				RequestLine;
			ULONG 				Reserved;
			ULONG 				Channel;
			ULONG 				TransferWidth;
		} 						DmaV3;
		struct {
			ULONG 				Length;
			ULONG 				Alignment;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS 	MaximumAddress;
		} 						Generic;
		struct {
			ULONG 				Data[3];
		} 						DevicePrivate;
		struct {
			ULONG 				Length;
			ULONG 				MinBusNumber;
			ULONG 				MaxBusNumber;
			ULONG 				Reserved;
		} 						BusNumber;
		struct {
			ULONG 				Priority;
			ULONG 				Reserved1;
			ULONG 				Reserved2;
		} 						ConfigData;
		struct {
			ULONG 				Length40;
			ULONG 				Alignment40;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS	MaximumAddress;
		} 						Memory40;
		struct {
			ULONG 				Length48;
			ULONG 				Alignment48;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS 	MaximumAddress;
		} 						Memory48;
		struct {
			ULONG 				Length64;
			ULONG 				Alignment64;
			PHYSICAL_ADDRESS 	MinimumAddress;
			PHYSICAL_ADDRESS 	MaximumAddress;
		} 						Memory64;
		struct {
			UCHAR 				Class;
			UCHAR 				Type;
			UCHAR 				Reserved1;
			UCHAR 				Reserved2;
			ULONG 				IdLowPart;
			ULONG 				IdHighPart;
		} 						Connection;
	} 							u;
}IO_RESOURCE_DESCRIPTORV2, * PIO_RESOURCE_DESCRIPTORV2;

typedef struct _IO_RESOURCE_LIST{
  USHORT 					Version;
  USHORT 					Revision;
  ULONG 					Count;
  IO_RESOURCE_DESCRIPTOR 	Descriptors[1];
}IO_RESOURCE_LIST, * PIO_RESOURCE_LIST;

typedef struct _IO_RESOURCE_REQUIREMENTS_LIST {
  ULONG 			ListSize;
  INTERFACE_TYPE 	InterfaceType;
  ULONG 			BusNumber;
  ULONG 			SlotNumber;
  ULONG 			Reserved[3];
  ULONG 			AlternativeLists;
  IO_RESOURCE_LIST 	List[1];
}IO_RESOURCE_REQUIREMENTS_LIST, * PIO_RESOURCE_REQUIREMENTS_LIST;

typedef struct _INTERFACE{
	USHORT 					Size;
	USHORT 					Version;
	PVOID 					Context;
	PINTERFACE_REFERENCE 	InterfaceReference;
	PINTERFACE_DEREFERENCE 	InterfaceDereference;
}INTERFACE, * PINTERFACE;

typedef struct _EMULATOR_ACCESS_ENTRY{
	ULONG 						BasePort;
	ULONG 						NumConsecutivePorts;
	EMULATOR_PORT_ACCESS_TYPE 	AccessType;
	UCHAR 						AccessMode;
	UCHAR 						StringSupport;
	PVOID 						Routine;
}EMULATOR_ACCESS_ENTRY, * PEMULATOR_ACCESS_ENTRY;

typedef struct _CM_MCA_POS_DATA{
	USHORT 					AdapterId;
	UCHAR  					PosData1;
	UCHAR  					PosData2;
	UCHAR  					PosData3;
	UCHAR  					PosData4;
}CM_MCA_POS_DATA, * PCM_MCA_POS_DATA;

typedef struct _CM_EISA_SLOT_INFORMATION{
	UCHAR  					ReturnCode;
	UCHAR  					ReturnFlags;
	UCHAR  					MajorRevision;
	UCHAR  					MinorRevision;
	USHORT 					Checksum;
	UCHAR  					NumberFunctions;
	UCHAR  					FunctionInformation;
	ULONG  					CompressedId;
}CM_EISA_SLOT_INFORMATION, * PCM_EISA_SLOT_INFORMATION;

typedef struct _EISA_MEMORY_TYPE{
    UCHAR 	ReadWrite 	: 1;
    UCHAR 	Cached 		: 1;
    UCHAR 	Reserved0 	: 1;
    UCHAR 	Type 		: 2;
    UCHAR 	Shared 		: 1;
    UCHAR 	Reserved1 	: 1;
    UCHAR 	MoreEntries : 1;
}EISA_MEMORY_TYPE, * PEISA_MEMORY_TYPE;

typedef struct _EISA_MEMORY_CONFIGURATION{
	EISA_MEMORY_TYPE 		ConfigurationByte;
	UCHAR 					DataSize;
	USHORT 					AddressLowWord;
	UCHAR 					AddressHighByte;
	USHORT 					MemorySize;
}EISA_MEMORY_CONFIGURATION, * PEISA_MEMORY_CONFIGURATION;

typedef struct _EISA_IRQ_DESCRIPTOR{
    UCHAR Interrupt 		: 4;
    UCHAR Reserved 			: 1;
    UCHAR LevelTriggered 	: 1;
    UCHAR Shared 			: 1;
    UCHAR MoreEntries 		: 1;
} EISA_IRQ_DESCRIPTOR, * PEISA_IRQ_DESCRIPTOR;

typedef struct _EISA_IRQ_CONFIGURATION{
	EISA_IRQ_DESCRIPTOR 	ConfigurationByte;
	UCHAR 					Reserved;
}EISA_IRQ_CONFIGURATION, * PEISA_IRQ_CONFIGURATION;

typedef struct _DMA_CONFIGURATION_BYTE0{
    UCHAR 	Channel 	: 3;
    UCHAR 	Reserved1 	: 1;
    UCHAR 	Shared 		: 1;
    UCHAR 	Reserved2 	: 1;
    UCHAR 	MoreEntries : 1;
}DMA_CONFIGURATION_BYTE0, * PDMA_CONFIGURATION_BYTE0;

typedef struct _DMA_CONFIGURATION_BYTE1{
	UCHAR 	TransferSize 	: 2;
	UCHAR 	Reserved1		: 1;
	UCHAR 	Timing			: 2;
	UCHAR 	Reserved2 		: 3; 
}DMA_CONFIGURATION_BYTE1, * PDMA_CONFIGURATION_BYTE1;

typedef struct _EISA_DMA_CONFIGURATION{
	DMA_CONFIGURATION_BYTE0 	ConfigurationByte0;
	DMA_CONFIGURATION_BYTE1 	ConfigurationByte1;
}EISA_DMA_CONFIGURATION, * PEISA_DMA_CONFIGURATION;

typedef struct _EISA_PORT_DESCRIPTOR{
    UCHAR 	NumberPorts : 5;
    UCHAR 	Reserved 	: 1;
    UCHAR 	PortUsage 	: 1;
    UCHAR 	MoreEntries : 1;
}EISA_PORT_DESCRIPTOR, * PEISA_PORT_DESCRIPTOR;

typedef struct _EISA_PORT_CONFIGURATION{
	EISA_PORT_DESCRIPTOR 	Configuration;
	USHORT 					PortAddress;
}EISA_PORT_CONFIGURATION, * PEISA_PORT_CONFIGURATION;

typedef struct _CM_EISA_FUNCTION_INFORMATION{
	ULONG                     CompressedId;
	UCHAR                     IdSlotFlags1;
	UCHAR                     IdSlotFlags2;
	UCHAR                     MinorRevision;
	UCHAR                     MajorRevision;
	UCHAR                     Selections[26];
	UCHAR                     FunctionFlags;
	UCHAR                     TypeString[80];
	EISA_MEMORY_CONFIGURATION EisaMemory[9];
	EISA_IRQ_CONFIGURATION    EisaIrq[7];
	EISA_DMA_CONFIGURATION    EisaDma[4];
	EISA_PORT_CONFIGURATION   EisaPort[20];
	UCHAR                     InitializationData[60];
}CM_EISA_FUNCTION_INFORMATION, * PCM_EISA_FUNCTION_INFORMATION;

FORCE_INLINE
unsigned char
_BitTest64(
	__int64 const* 	Base,
	__int64       	Index
){
    unsigned char OldBit;
    __asm__ __volatile__ (
        "btq %[Index], %[Base];"
        "setc %[OldBit];"
        : [OldBit] "=r" (OldBit)
        : [Base] "m" (*Base), [Index] "Ir" (Index)
        : "cc"
    );
    return OldBit;
}

FORCE_INLINE
unsigned char 
_BitTestAndComplement64(
	__int64* 	Base,
	__int64 	Index
){
    unsigned char OldBit;
    __asm__ __volatile__ (
        "btcq %[Index], %[Base];"
        "setc %[OldBit];"
        : [OldBit] "=r" (OldBit), [Base] "+m" (*Base)
        : [Index] "Ir" (Index)
        : "cc"
    );
    return OldBit;
}

FORCE_INLINE
unsigned char 
_BitTestAndReset64(
	__int64* Base,
	__int64 Index
){
    unsigned char OldBit;
    __asm__ __volatile__ (
        "btrq %[Index], %[Base];"
        "setc %[OldBit];"
        : [OldBit] "=r" (OldBit), [Base] "+m" (*Base) 
        : [Index] "Ir" (Index)
        : "cc"
    );
    return OldBit;	
}

FORCE_INLINE
unsigned char _BitTestAndSet64(
	__int64* Base,
	__int64 Index
){
  unsigned char OldBit;
    __asm__ __volatile__ (
        "btsq %[Index], %[Base];" // 'bts' = Bit Test and Set (sets to 1)
        "setc %[OldBit];"          // Capture original bit from Carry Flag
        : [OldBit] "=r" (OldBit), [Base] "+m" (*Base) 
        : [Index] "Ir" (Index)
        : "cc"
    );
    return OldBit;
}

#define _ReadWriteBarrier() __asm__ __volatile__ ("" ::: "memory")

#define BarrierAfterRead() _ReadWriteBarrier()
#define BarrierAfterReadR1() _ReadWriteBarrier()
#define BarrierAfterReadR2() _ReadWriteBarrier()

FORCE_INLINE
UCHAR READ_REGISTER_UCHAR(PUCHAR Register){
    return *Register;
}

FORCE_INLINE
VOID WRITE_REGISTER_UCHAR(PUCHAR Register, UCHAR Value){
    *Register = Value;
}

FORCE_INLINE
USHORT READ_REGISTER_USHORT(volatile PUSHORT Register){
    return *Register;
}

FORCE_INLINE
VOID WRITE_REGISTER_USHORT(volatile PUSHORT Register, USHORT Value){
    *Register = Value;
}

FORCE_INLINE
ULONG READ_REGISTER_ULONG(volatile PULONG Register){
    return *Register;
}

FORCE_INLINE
VOID WRITE_REGISTER_ULONG(volatile PULONG Register, ULONG Value){
    *Register = Value;
}

FORCE_INLINE
ULONGLONG READ_REGISTER_ULONGLONG(volatile PULONGLONG Register){
    return *Register;
}

FORCE_INLINE
VOID WRITE_REGISTER_ULONGLONG(volatile PULONGLONG Register, ULONGLONG Value){
    *Register = Value;
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void READ_REGISTER_BUFFER_UCHAR(
	volatile UCHAR* Register,
	PUCHAR         	Buffer,
	ULONG          	Count
){
	for(ULONG i = 0; i < Count; i++){
		Buffer[i] = Register[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void READ_REGISTER_BUFFER_USHORT(
	volatile USHORT* 	Register,
	PUSHORT         	Buffer,
	ULONG           	Count
){
	for(ULONG i = 0; i < Count; i++){
		Buffer[i] = Register[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void READ_REGISTER_BUFFER_ULONG(
	volatile ULONG* Register,
	PULONG         	Buffer,
	ULONG          	Count
){
	for(ULONG i = 0; i < Count; i++){
		Buffer[i] = Register[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void READ_REGISTER_BUFFER_ULONGLONG(
	volatile ULONG* Register,
	PULONGLONG      Buffer,
	ULONGLONG		Count
){
	for(ULONG i = 0; i < Count; i++){
		Buffer[i] = Register[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void WRITE_REGISTER_BUFFER_UCHAR(
	volatile UCHAR*	Register,
	PUCHAR         	Buffer,
	ULONG          	Count
){
	for(ULONG i = 0; i < Count; i++){
		Register[i] = Buffer[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void WRITE_REGISTER_BUFFER_USHORT(
	volatile USHORT* 	Register,
	PUSHORT         	Buffer,
	ULONG           	Count
){
	for(ULONG i = 0; i < Count; i++){
		Register[i] = Buffer[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void WRITE_REGISTER_BUFFER_ULONG(
	volatile ULONG*	Register,
	PULONG         	Buffer,
	ULONG          	Count
){
	for(ULONG i = 0; i < Count; i++){
		Register[i] = Buffer[i];
	}
}

FORCE_INLINE
STRIP_OPTIMIZATIONS
void WRITE_REGISTER_BUFFER_ULONGLONG(
	volatile ULONGLONG* Register,
	PULONGLONG         	Buffer,
	ULONGLONG          	Count
){
	for(ULONG i = 0; i < Count; i++){
		Register[i] = Buffer[i];
	}
}

typedef struct _SUPPORTED_RANGE{
    PHYSICAL_ADDRESS 	SystemAddressSpace;
    PHYSICAL_ADDRESS 	SystemLowAddress;
    PHYSICAL_ADDRESS 	SystemHighAddress;
    LONGLONG 			Base;
    LONGLONG 			Limit;
}SUPPORTED_RANGE, * PSUPPORTED_RANGE;

typedef struct _SUPPORTED_RANGES{
    USHORT 				Version;
    BOOLEAN 			Sorted;
    UCHAR 				Reserved;
    ULONG 				Count;
    SUPPORTED_RANGE 	Ranges[1];
}SUPPORTED_RANGES, * PSUPPORTED_RANGES;

typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR {
  UCHAR  					Type;
  UCHAR  					ShareDisposition;
  USHORT 					Flags;
  union {
    struct{
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length;
    } 						Generic;
    struct{
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length;
    } 						Port;
    struct{
#ifdef CM_PARTIAL_RESOURCE_DESCRIPTOR_INTERRUPT_GROUP
      USHORT    			Level;
      USHORT    			Group;
#else
      ULONG     			Level;
#endif
      ULONG     			Vector;
      KAFFINITY 			Affinity;
    } 						Interrupt;
    struct{
      union{
        struct{
          USHORT    		Group;
          USHORT    		Reserved;
          USHORT    		MessageCount;
          ULONG     		Vector;
          KAFFINITY 		Affinity;
        } 					Raw;
        struct{
#ifdef CM_PARTIAL_RESOURCE_DESCRIPTOR_TRANSLATED_GROUP
          USHORT    		Level;
          USHORT    		Group;
#else
          ULONG     		Level;
#endif
          ULONG     		Vector;
          KAFFINITY 		Affinity;
        } 					Translated;
      };
    } 						MessageInterrupt;
    struct {
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length;
    } 						Memory;
    struct {
      ULONG 				Channel;
      ULONG 				Port;
      ULONG 				Reserved1;
    } 						Dma;
    struct {
      ULONG 				Channel;
      ULONG 				RequestLine;
      UCHAR 				TransferWidth;
      UCHAR 				Reserved1;
      UCHAR 				Reserved2;
      UCHAR 				Reserved3;
    } 						DmaV3;
    struct {
      ULONG 				Data[3];
    } 						DevicePrivate;
    struct {
      ULONG 				Start;
      ULONG 				Length;
      ULONG 				Reserved;
    } 						BusNumber;
    struct {
      ULONG 				DataSize;
      ULONG 				Reserved1;
      ULONG 				Reserved2;
    } 						DeviceSpecificData;
    struct {
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length40;
    } 						Memory40;
    struct {
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length48;
    } 						Memory48;
    struct {
      PHYSICAL_ADDRESS 		Start;
      ULONG            		Length64;
    } 						Memory64;
    struct {
      UCHAR 				Class;
      UCHAR 				Type;
      UCHAR 				Reserved1;
      UCHAR 				Reserved2;
      ULONG 				IdLowPart;
      ULONG 				IdHighPart;
    } 						Connection;
  } 						u;
}CM_PARTIAL_RESOURCE_DESCRIPTOR, * PCM_PARTIAL_RESOURCE_DESCRIPTOR;


typedef struct _CM_PARTIAL_RESOURCE_LIST {
    USHORT                         Version;
    USHORT                         Revision;
    ULONG                          Count;
    CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
} CM_PARTIAL_RESOURCE_LIST, *PCM_PARTIAL_RESOURCE_LIST;


typedef struct _CM_FULL_RESOURCE_DESCRIPTOR {
    INTERFACE_TYPE           InterfaceType;
    ULONG                    BusNumber;
    CM_PARTIAL_RESOURCE_LIST PartialResourceList;
}CM_FULL_RESOURCE_DESCRIPTOR, * PCM_FULL_RESOURCE_DESCRIPTOR;


typedef struct _CM_RESOURCE_LIST{
    ULONG                       Count;
    CM_FULL_RESOURCE_DESCRIPTOR List[1];
}CM_RESOURCE_LIST, * PCM_RESOURCE_LIST;


typedef struct _BUS_HANDLER{
    ULONG                   Version;
    INTERFACE_TYPE          InterfaceType;
    BUS_DATA_TYPE           ConfigurationType;
    ULONG                   BusNumber;
    PDEVICE_OBJECT          DeviceObject;
    struct _BUS_HANDLER*    ParentHandler;
    PVOID                   BusData;
    ULONG                   DeviceControlExtentionSize;
    PSUPPORTED_RANGES       BusAddresses;
    ULONG                   Reserved[4];
    ULONG                   (*GetBusData)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, ULONG arg3, VOID* arg4, ULONG arg5, ULONG arg6);
    ULONG                   (*SetBusData)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, ULONG arg3, VOID* arg4, ULONG arg5, ULONG arg6);
    LONG                    (*AdjustResourceList)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, struct _IO_RESOURCE_REQUIREMENTS_LIST** arg3);
    LONG                    (*AssignSlotResources)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, struct _UNICODE_STRING* arg3, struct _UNICODE_STRING* arg4, struct _DRIVER_OBJECT* arg5, struct _DEVICE_OBJECT* arg6, ULONG arg7, struct _CM_RESOURCE_LIST** arg8);
    UCHAR                   (*TranslateBusAddress)(struct _BUS_HANDLER* arg1, struct _BUS_HANDLER* arg2, union _LARGE_INTEGER arg3, ULONG* arg4, union _LARGE_INTEGER* arg5);
    PVOID                   Spare1;
    PVOID                   Spare2;
    PVOID                   Spare3;
    PVOID                   Spare4;
    PVOID                   Spare5;
    PVOID                   Spare6;
    PVOID                   Spare7;
    PVOID                   Spare8;
}BUS_HANDLER, * PBUS_HANDLER;


#ifndef _USER_MODE_CODE_

FORCE_INLINE
VOID WRITE_PORT_UCHAR(PVOID Port, UCHAR Value){
    outb((uint64_t)Port, (uint8_t)Value);
}

FORCE_INLINE
VOID WRITE_PORT_USHORT(PVOID Port, USHORT Value){
    outw((uint64_t)Port, (uint16_t)Value);
}

FORCE_INLINE
VOID WRITE_PORT_ULONG(PVOID Port, ULONG Value){
    outl((uint64_t)Port, (uint32_t)Value);
}

FORCE_INLINE
UCHAR READ_PORT_UCHAR(PVOID Port){
    return inb((uint64_t)Port);
}

FORCE_INLINE
USHORT READ_PORT_USHORT(PVOID Port){
    return inw((uint64_t)Port);
}

FORCE_INLINE
ULONG READ_PORT_ULONG(PVOID Port){
    return inl((uint64_t)Port);
}

FORCE_INLINE
void READ_PORT_BUFFER_UCHAR(
	PUCHAR Port,
	PUCHAR Buffer,
	ULONG  Count
){
	return insb(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

FORCE_INLINE
void READ_PORT_BUFFER_USHORT(
	PUSHORT Port,
	PUSHORT Buffer,
	ULONG   Count
){
	return insw(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

FORCE_INLINE
void READ_PORT_BUFFER_ULONG(
	PULONG Port,
	PULONG Buffer,
	ULONG  Count
){
	return insl(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

FORCE_INLINE
void WRITE_PORT_BUFFER_UCHAR(
	PUCHAR Port,
	PUCHAR Buffer,
	ULONG  Count
){
	outsb(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

FORCE_INLINE
void WRITE_PORT_BUFFER_USHORT(
	 PUSHORT Port,
	 PUSHORT Buffer,
	 ULONG   Count
){
	outsw(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

FORCE_INLINE
void WRITE_PORT_BUFFER_ULONG(
	 PULONG Port,
	 PULONG Buffer,
	 ULONG  Count
){
	outsl(
		(UINT16)(UINTPTR)Port,
		Buffer,
		Count
	);
}

typedef struct _ACCESS_RANGE {
    PHYSICAL_ADDRESS RangeStart;
    ULONG RangeLength;
    BOOLEAN RangeInMemory;
} ACCESS_RANGE, *PACCESS_RANGE;

#define DmaWidth32 0x01
#define CheckAhci64 31

#define StorSynchronizeFullDuplex 0x01

typedef struct  _PORT_CONFIGURATION_INFORMATION {
    ULONG 		Length;
    ULONG 		SystemIoBusNumber;
	ULONG 		AdapterInterfaceType;
	uint8_t 	PADING1[0x28];
	uint32_t 	NumberOfAccessRanges;
	uint64_t* 	AddressRanges;
    uint8_t 	PADDING[0x24];
    ULONG 		SlotNumber;
	BOOLEAN 	Master;
	uint8_t 	AlignmentMask;
	BOOLEAN 	ScatterMeGather;
	uint8_t 	DmaWidth;
	BOOLEAN 	WmiDataProvider;
	BOOLEAN 	Dma32Address;
	BOOLEAN 	Dma64Address;
	uint8_t 	MaximumTargets;
	BOOLEAN 	ResetTargetSupport;
	uint8_t 	NumberOfPhysicalBreks;
	uint8_t 	NumberOfLogicalUnits;
	uint8_t 	NumberOfBusses;
	uint16_t 	MaximumTransferLength;
	uint8_t 	SynchronizationModel;
} PORT_CONFIGURATION_INFORMATION, *PPORT_CONFIGURATION_INFORMATION;

typedef struct  _SCSI_REQUEST_BLOCK{
    USHORT 						Length;
    UCHAR 						Function;
    UCHAR 						SrbStatus;
    UCHAR 						ScsiStatus;
    UCHAR 						PathId;
    UCHAR 						TargetId;
    UCHAR 						Lun;
    UCHAR 						QueueTag;
    UCHAR 						QueueAction;
    UCHAR 						CdbLength;
    UCHAR 						SenseInfoBufferLength;
    ULONG 						SrbFlags;
    ULONG 						DataTransferLength;
    ULONG 						TimeOutValue;
    PVOID 						DataBuffer;
    PVOID 						SenseInfoBuffer;
    struct _SCSI_REQUEST_BLOCK*	NextSrb;
    PVOID 						OriginalRequest;
    PVOID 						SrbExtension;
    union {
        ULONG 					InternalStatus;
        ULONG 					QueueSortKey;
        ULONG 					LinkTimeoutValue;
    };
    ULONG 						Reserved;
    UCHAR 						Cdb[16];
}SCSI_REQUEST_BLOCK, *PSCSI_REQUEST_BLOCK;


typedef BOOLEAN (*PHW_ADAPTER_STATE)(PVOID, PVOID, BOOLEAN);
typedef BOOLEAN (*PHW_ADAPTER_CONTROL)(PVOID, PVOID, BOOLEAN);
typedef BOOLEAN (*PHW_INITIALIZE)(PVOID);
typedef void (*PHW_DMA_STARTED)(PVOID);
typedef BOOLEAN (*PHW_RESET_BUS)(PVOID, ULONG);
typedef ULONG (*PHW_FIND_ADAPTER)(PVOID, PVOID,PVOID, PCHAR, PPORT_CONFIGURATION_INFORMATION, PBOOLEAN);
typedef BOOLEAN (*PHW_INTERRUPT)(PVOID);
typedef BOOLEAN (*PHW_STARTIO)(PVOID DeviceExtension, PSCSI_REQUEST_BLOCK);


typedef struct _STORPORT_HW_INITIALIZATION_DATA {
  ULONG               	HwInitializationDataSize;
  INTERFACE_TYPE      	AdapterInterfaceType;
  PHW_INITIALIZE      	HwInitialize;
  PHW_STARTIO         	HwStartIo;
  PHW_INTERRUPT       	HwInterrupt;
  PHW_FIND_ADAPTER    	HwFindAdapter;
  PHW_RESET_BUS       	HwResetBus;
  PHW_DMA_STARTED     	HwDmaStarted;
  PHW_ADAPTER_STATE   	HwAdapterState;
  ULONG               	DeviceExtensionSize;
  ULONG               	SpecificLuExtensionSize;
  ULONG               	SrbExtensionSize;
  ULONG               	NumberOfAccessRanges;
  PVOID               	Reserved;
  BOOLEAN             	MapBuffers;
  BOOLEAN             	NeedPhysicalAddresses;
  BOOLEAN             	TaggedQueuing;
  BOOLEAN             	AutoRequestSense;
  BOOLEAN             	MultipleRequestPerLu;
  BOOLEAN             	ReceiveEvent;
  USHORT              	VendorIdLength;
  PVOID               	VendorId;
  union {
    USHORT 				ReservedUshort;
    USHORT 				PortVersionFlags;
  };
  USHORT              	DeviceIdLength;
  PVOID               	DeviceId;
  PHW_ADAPTER_CONTROL 	HwAdapterControl;
}STORPORT_HW_INITIALIZATION_DATA, * PSTORPORT_HW_INITIALIZATION_DATA;

typedef struct  _STOR_PORT_STACK_OBJECT{
    struct _DRIVER_OBJECT* 			DrvObj;
    PUNICODE_STRING 				RegistryEntry;
	uint64_t 						FindAdapter;
	uint64_t 						InitAdapter;
	uint64_t 						InterruptHandler;
    PVOID 							DeviceExtention;
    PVOID 							SpecificLuExtention;
    PVOID 							SrbExtension;
	PPORT_CONFIGURATION_INFORMATION ConfigInfo;
}STOR_PORT_STACK_OBJECT, * PSTOR_PORT_STACK_OBJECT;

PSTOR_PORT_STACK_OBJECT GetStorPortObject(struct _DRIVER_OBJECT* DrvObject);

typedef enum _SCSI_NOTIFICATION_TYPE {
    RequestComplete,
    NextRequest,
    NextLuRequest,
    ResetDetected,
    CallDisableInterrupts,
    CallEnableInterrupts,
    RequestTimerCall,
    BusChangeDetected,
    WMIEvent,
    WMIReregister,
    LinkUp,
    LinkDown,
    ProcessingErrorDetected
} SCSI_NOTIFICATION_TYPE, *PSCSI_NOTIFICATION_TYPE;

typedef LARGE_INTEGER STOR_PHYSICAL_ADDRESS;

typedef struct _AHCI_SRB_EXTENSION {
    ULONG_PTR OriginalSrb;
    PVOID     Context;
    ULONG     Flags;
    ULONG     PortNumber;
    ULONG     SlotNumber;
    PVOID     CommandTable;
    PVOID     FisBaseAddress;
    ULONG     AtaStatus;
    ULONG     Reserved[4];
} AHCI_SRB_EXTENSION, *PAHCI_SRB_EXTENSION;

#define STOR_MAP_NON_READ_WRITE_BUFFERS             (2)


#endif
#endif