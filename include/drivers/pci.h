/*
-- Tyler Grenier 2/6/24 11:14:45 AM
-- last edit 3/3/26 7:01:15 PM
*/

#ifndef _PCI_H
#define _PCI_H

#ifdef __cplusplus
extern "C" {
#endif

#define PCI_IRQ_USE_LEGACY 	(1)
#define PCI_IRQ_USE_MSI		(1 << 1)
#define PCI_IRQ_USE_MSI_X	(1 << 2)

#define PCI_CAP_MSI 	0x05
#define PCI_CAP_MSI_X  	0x11

#include <cstdint.h>
#include <cstdlib.h>
#include <kernel/atomic.h>
#include "PciIds.h"

typedef struct _LOUSINE_PCI_DEVICE_TABLE{
	uint16_t VendorID;
	uint16_t DeviceID;
	uint16_t SubVendorID;
	uint16_t SubDeviceID;
	uint8_t  BaseClass;
	uint8_t  SubClass;
	uint8_t	 ProgIf;
	uint64_t BoardID;
	uint64_t DriverData;
	bool     SimpleEntry;
	bool     AdvancedEntry;
	bool 	 SimpleWithClass;
	bool 	 GenericEntry;
}LOUSINE_PCI_DEVICE_TABLE, * PLOUSINE_PCI_DEVICE_TABLE;

#define PROGIF 9

#define PCI_INTERRUPT_DISABLE (1 << 10)
#define PCI_INTERRUPT_ENABLE ~(1 << 10)
#define SERR_ENABLE (1 << 8)
#define SERR_DISABLE ~(1 << 8)
#define PARITY_NORMAL (1 << 6)
#define PARITY_SPECIAL ~(1 << 6)
#define BUS_MASTER_ENABLE (1 << 2)
#define BUS_MASTER_DISABLE ~(1 << 2)
#define MEMORY_SPACE_ENABLE (1 << 1)
#define MEMORY_SPACE_DISABLE ~(1 << 1)
#define IO_SPACE_ENABLE (1)
#define IO_SPACE_DISABLE ~(1)

typedef int pci_power_t;

typedef enum{
	PciLegacyDispatch = 0,
	PciNativeDispatch,
	PciTotalDispatch,
}PCI_DRIVER_DISPATCH;

typedef struct _PCI_DEVICE_OBJECT{
	uint16_t 			VendorID;
	uint16_t 			DeviceID;
	UINT16 				Group;
	UINT8				Bus;
	UINT8				Slot;
	UINT8				Function;
	PCI_DRIVER_DISPATCH	Dispatch;
	spinlock_t 			ConfigSpaceLock;
	UINT32*				EcamDeviceBase;
	//remove start
	uint8_t 			bus;
	uint8_t 			slot;
	uint8_t 			func;
	//remove end
	bool				InterruptsEnabled;
	int 				NumberOfSAssignedVectors;
	uint8_t* 			InterruptVectors;
	void* 				Dev;
	void* 				CommonConfig;
	void*				EcamDevice;//literal base
	struct{
		LOUSTATUS 		(*PcieReadEcam)(struct _PCI_DEVICE_OBJECT* Device, size_t Offset, size_t Width, uint32_t* Value);
		LOUSTATUS 		(*PcieWriteEcam)(struct _PCI_DEVICE_OBJECT* Device, size_t Offset, size_t Width, uint32_t Value);
	}EcamOperations;
	pci_power_t 		CurrentState;
	uint8_t 			PmCap;
	atomic_t 			enable_cnt;
	uint8_t	  			InterruptLine;
	uint8_t	  			InterruptPin;
	uintptr_t 			DeviceExtendedObject; 
	uintptr_t 			DevicePrivateData;
	uintptr_t 			VgaDecode; //only video devces
	bool				DeviceManaged;
	UINT64				DriverFeatures;
}PCI_DEVICE_OBJECT, * PPCI_DEVICE_OBJECT;

typedef struct _AGP_BRIDGE_DATA{
	uint64_t Foo;
}AGP_BRIDGE_DATA, *PAGP_BRIDGE_DATA;

#define PCI_CONFIG_ADDRESS_PORT 	0xCF8
#define PCI_CONFIG_DATA_PORT    	0xCFC

#define PCI_CONFIG_VENDOR_ID      	0x00
#define PCI_CONFIG_DEVICE_ID      	0x02
#define PCI_CONFIG_COMMAND        	0x04
#define PCI_CONFIG_STATUS         	0x06
#define PCI_CONFIG_REVISION_ID    	0x08
#define PCI_CONFIG_PROGIF    		0x09
#define PCI_CONFIG_SUBCLASS    		0x0A
#define PCI_CONFIG_CLASS_CODE     	0x0B
#define PCI_CONFIG_CACHE_LINE_SIZE	0x0C
#define PCI_CONFIG_LATENCY_TIMER	0x0D
#define PCI_CONFIG_HEADER_TYPE		0x0E
#define PCI_CONFIG_BIST				0x0F

#define PCI_GENERAL_DEVICE_CONFIG_BAR_STACK				0x10
#define PCI_GENERAL_DEVICE_CONFIG_CARDBUS_CIS_POINTER 	0x28
#define PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_VENDOR_ID	0x2C
#define PCI_GENERAL_DEVICE_CONFIG_SUBSYSTEM_ID 			0x2E
#define PCI_GENERAL_DEVICE_CONFIG_EXPANSION_ROM_BASE	0x30
#define PCI_GENERAL_DEVICE_CONFIG_CAPABILITIES_POINTER	0x34
#define PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_LINE		0x3C
#define PCI_GENERAL_DEVICE_CONFIG_INTERRUPT_PIN			0x3D
#define PCI_GENERAL_DEVICE_CONFIG_MIN_GRANT				0x3E
#define PCI_GENERAL_DEVICE_CONFIG_MAX_LATENCY			0x3F

#define PCI_BRIDGE_DEVICE_CONFIG_BAR_STACK					0x10
#define PCI_BRIDGE_DEVICE_CONFIG_PRIMARY_BUS_NUMBER			0x18
#define PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_BUS_NUMBER    	0x19
#define PCI_BRIDGE_DEVICE_CONFIG_SUBORDINATE_BUS_NUMBER		0x1A
#define PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_LATENCY_TIMER	0x1B
#define PCI_BRIDGE_DEVICE_CONFIG_IO_BASE					0x1C
#define PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT					0x1D
#define PCI_BRIDGE_DEVICE_CONFIG_SECONDARY_STATUS			0x1E
#define PCI_BRIDGE_DEVICE_CONFIG_MEMORY_BASE				0x20
#define PCI_BRIDGE_DEVICE_CONFIG_MEMORY_LIMIT				0x22
#define PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_BASE		0x24
#define PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_MEMORY_LIMIT		0x26
#define PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_BASE		0x28
#define PCI_BRIDGE_DEVICE_CONFIG_PREFETCH_UPPER32_LIMIT		0x2C
#define PCI_BRIDGE_DEVICE_CONFIG_IO_BASE_UPPER16			0x30
#define PCI_BRIDGE_DEVICE_CONFIG_IO_LIMIT_UPPER16			0x32
#define PCI_BRIDGE_DEVICE_CONFIG_CAPABILITIES_POINTER		0x34
#define PCI_BRIDGE_DEVICE_CONFIG_EXPANSION_ROM_BASE			0x38
#define PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_LINE				0x3C
#define PCI_BRIDGE_DEVICE_CONFIG_INTERRUPT_PIN				0x3D
#define PCI_BRIDGE_DEVICE_CONFIG_BRIDGE_CONTROL				0x3E

#define PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_SOCKET_EXCA_BASE	0x10
#define PCI_CARDBUS_DEVICE_CONFIG_OFFSET_CAPABILITIES_LIST	0x14
#define PCI_CARDBUS_DEVICE_CONFIG_SECONDARY_STATUS			0x16
#define PCI_CARDBUS_DEVICE_CONFIG_PCI_BUS_NUMBER			0x18
#define PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_NUMBER			0x19
#define PCI_CARDBUS_DEVICE_CONFIG_SUBORDINATE_BUS_NUMBER	0x1A
#define PCI_CARDBUS_DEVICE_CONFIG_CARDBUS_LATENCY_TIMER		0x1B
#define PCI_CARDBUS_DEVICE_CONFIG_MEMORY_BASE_ADDRESS_0		0x1C
#define PCI_CARDBUS_DEVICE_CONFIG_MEMORY_LIMIT_0			0x20
#define PCI_CARDBUS_DEVICE_CONFIG_MEMORY_BASE_ADDRESS_1		0x24
#define PCI_CARDBUS_DEVICE_CONFIG_MEMORY_LIMIT_1			0x28
#define PCI_CARDBUS_DEVICE_CONFIG_IO_BASE_ADDRESS_0			0x2C
#define PCI_CARDBUS_DEVICE_CONFIG_IO_LIMIT_0				0x30
#define PCI_CARDBUS_DEVICE_CONFIG_IO_BASE_ADDRESS_1			0x34
#define PCI_CARDBUS_DEVICE_CONFIG_IO_LIMIT_1				0x38
#define PCI_CARDBUS_DEVICE_CONFIG_INTERRUPT_LINE			0x3C
#define PCI_CARDBUS_DEVICE_CONFIG_INTERRUPT_PIN				0x3D
#define PCI_CARDBUS_DEVICE_CONFIG_BRIDGE_CONTROL			0x3E
#define PCI_CARDBUS_DEVICE_CONFIG_SUBSYSTEM_DEVICE_ID		0x40
#define PCI_CARDBUS_DEVICE_CONFIG_SUBSYSTEM_VENDOR_ID		0x42
#define PCI_CARDBUS_DEVICE_CONFIG_16BIT_PC_CARD_LEGACY_BASE	0x44

#define PCIE_BUS_CONFIG_SIZE 0x00100000

#define PCI_D0		((pci_power_t) 0)
#define PCI_D1		((pci_power_t) 1)
#define PCI_D2		((pci_power_t) 2)
#define PCI_D3hot	((pci_power_t) 3)
#define PCI_D3cold	((pci_power_t) 4)
#define PCI_UNKNOWN	((pci_power_t) 5)
#define PCI_POWER_ERROR	((pci_power_t) -1)

#define ANY_PCI_ID 0xFFFF
#define ANY_PCI_CLASS 255

#define PCI_STATUS_CAP_LIST 0x10
#define PCI_CAP_ID_AGP	0x02

typedef struct _PCI_BITS{
    UINT32  Register;
    UINT32  Width;
    UINT32  Mask;
    UINT32  Value;
}PCI_BITS, * PPCI_BITS;

typedef struct _PCI_BIT_TEST_PACKET{
	PPCI_BITS	Bits;
	bool		Result;
}PCI_BIT_TEST_PACKET, * PPCI_BIT_TEST_PACKET;

typedef struct _PCIE_SYSTEM_MANAGER{
    ListHeader  Neighbors;
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
}PCIE_SYSTEM_MANAGER, * PPCIE_SYSTEM_MANAGER;

typedef struct _PCI_MANAGER_DATA{
    ListHeader 			Peers;
    PPCI_DEVICE_OBJECT 	PDEV;
    string 				RegistryEntry;
    string 				DeviceManagerString;
}PCI_MANAGER_DATA, * PPCI_MANAGER_DATA, PCI_DEVICE_GROUP,* PPCI_DEVICE_GROUP;

typedef struct _PCI_CAPABILITIES_HEADER {
    UCHAR   CapabilityID;
    UCHAR   Next;
} PCI_CAPABILITIES_HEADER, * PPCI_CAPABILITIES_HEADER;

typedef enum{
	BusWidth32Bits = 0,
	BusWidth64Bits
}PCI_BUS_WIDTH;

#define PCI_TYPE0_ADDRESSES             6
#define PCI_TYPE1_ADDRESSES             2
#define PCI_TYPE2_ADDRESSES             5

typedef struct _PCI_COMMON_HEADER{
    USHORT  			VendorID;            
    USHORT  			DeviceID;            
    USHORT  			Command;             
    USHORT  			Status;
    UCHAR   			RevisionID;          
    UCHAR   			ProgIf;              
    UCHAR   			SubClass;            
    UCHAR   			BaseClass;           
    UCHAR   			CacheLineSize;       
    UCHAR   			LatencyTimer;        
    UCHAR   			HeaderType;          
    UCHAR   			BIST;                
    union{
        struct _PCI_HEADER_TYPE_0{
            ULONG   	BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   	CIS;
            USHORT  	SubVendorID;
            USHORT  	SubSystemID;
            ULONG   	ROMBaseAddress;
            UCHAR   	CapabilitiesPtr;
            UCHAR   	Reserved1[3];
            ULONG   	Reserved2;
            UCHAR   	InterruptLine;
            UCHAR   	InterruptPin;
            UCHAR   	MinimumGrant;
            UCHAR   	MaximumLatency;
        }				type0;
        struct _PCI_HEADER_TYPE_1 {
            ULONG   	BaseAddresses[PCI_TYPE1_ADDRESSES];
            UCHAR   	PrimaryBus;
            UCHAR   	SecondaryBus;
            UCHAR   	SubordinateBus;
            UCHAR   	SecondaryLatency;
            UCHAR   	IOBase;
            UCHAR   	IOLimit;
            USHORT  	SecondaryStatus;
            USHORT  	MemoryBase;
            USHORT  	MemoryLimit;
            USHORT  	PrefetchBase;
            USHORT  	PrefetchLimit;
            ULONG   	PrefetchBaseUpper32;
            ULONG   	PrefetchLimitUpper32;
            USHORT  	IOBaseUpper16;
            USHORT  	IOLimitUpper16;
            UCHAR   	CapabilitiesPtr;
            UCHAR   	Reserved1[3];
            ULONG   	ROMBaseAddress;
            UCHAR   	InterruptLine;
            UCHAR   	InterruptPin;
            USHORT  	BridgeControl;
        } 				type1;
        struct _PCI_HEADER_TYPE_2 {
            ULONG   	SocketRegistersBaseAddress;
            UCHAR   	CapabilitiesPtr;
            UCHAR   	Reserved;
            USHORT  	SecondaryStatus;
            UCHAR   	PrimaryBus;
            UCHAR   	SecondaryBus;
            UCHAR   	SubordinateBus;
            UCHAR   	SecondaryLatency;
            struct  {
                ULONG   Base;
                ULONG   Limit;
            }       	Range[PCI_TYPE2_ADDRESSES-1];
            UCHAR   	InterruptLine;
            UCHAR   	InterruptPin;
            USHORT  	BridgeControl;
        } 				type2;
    } u;
} PCI_COMMON_HEADER, *PPCI_COMMON_HEADER;

typedef struct _PCI_COMMON_CONFIG {
    PCI_COMMON_HEADER 	Header;
    UCHAR   			DeviceSpecific[192];
	uint64_t 			BarSize[6];
	uint64_t 			BarBase[6];
	uint64_t 			RawBarBase[6];
	uint8_t  			BarFlags[6];
} PCI_COMMON_CONFIG, * PPCI_COMMON_CONFIG;

typedef struct  _PCI_CONTEXT{
    PCI_COMMON_CONFIG 	PciConfig;
    PPCI_DEVICE_OBJECT	PDEV;
}PCI_CONTEXT, * PPCI_CONTEXT;



typedef enum{
	PciDeviceD3Cold_State_Disabled_BitIndex = 0,
	PciDeviceD3Cold_State_Enabled_BitIndex,
	PciDeviceD3Cold_State_ParentRootPortS0WakeSupported_BitIndex,
	PciDeviceD3Cold_State_Disabled_Bridge_HackFlags_BitIndex,
	PciDeviceD3Cold_Reason_Default_State_BitIndex,
	PciDeviceD3Cold_Reason_INF_BitIndex,
	PciDeviceD3Cold_Reason_Interface_Api_BitIndex
}PCI_DEVICE_D3COLD_STATE_REASON;

typedef enum{
	L0sAndL1EntryDisabled = 0,
	L0sEntryEnabled,
	L1EntryEnabled,
	L0sAndL1EntryEnabled
} PCI_EXPRESS_ASPM_CONTROL;

typedef enum {
	NoAspmSupport = 0,
	L0sEntrySupport,
	L1EntrySupport,
	L0sAndL1EntrySupport
}PCI_EXPRESS_ASPM_SUPPORT;

typedef enum{
	SlotEmpty = 0,
	CardPresent
}PCI_EXPRESS_CARD_PRESENCE;

typedef enum {
	PciExpressEndpoint = 0,
	PciExpressLegacyEndpoint,
	PciExpressRootPort,
	PciExpressUpstreamSwitchPort,
	PciExpressDownstreamSwitchPort,
	PciExpressToPciXBridge,
	PciXToExpressBridge,
	PciExpressRootComplexIntegratedEndpoint,
	PciExpressRootComplexEventCollector
}PCI_EXPRESS_DEVICE_TYPE;

typedef enum{
	IndicatorOn = 0,
	IndicatorBlink,
	IndicatorOff
}PCI_EXPRESS_INDICATOR_STATE;

typedef enum{
	L0s_Below64ns = 0,
	L0s_64ns_128ns,
	L0s_128ns_256ns,
	L0s_256ns_512ns,
	L0s_512ns_1us,
	L0s_1us_2us,
	L0s_2us_4us,
	L0s_Above4us
}PCI_EXPRESS_L0s_EXIT_LATENCY;

typedef enum{
	L1_Below1us = 0,
	L1_1us_2us,
	L1_2us_4us,
	L1_4us_8us,
	L1_8us_16us,
	L1_16us_32us,
	L1_32us_64us,
	L1_Above64us
}PCI_EXPRESS_L1_EXIT_LATENCY;

typedef enum{
	MRLClosed = 0,
	MRLOpen
}PCI_EXPRESS_MRL_STATE;

typedef enum{
	PowerOn = 0,
	PowerOff
}PCI_EXPRESS_POWER_STATE;

typedef enum {
	RCB64Bytes = 0,
	RCB128Bytes
} PCI_EXPRESS_RCB;

typedef struct _PCI_SLOT_NUMBER {
	union {
		struct {
			ULONG 	DeviceNumber : 5;
			ULONG 	FunctionNumber : 3;
			ULONG 	Reserved : 24;
		} 			bits;
		ULONG 		AsULONG;
	} u;
} PCI_SLOT_NUMBER, * PPCI_SLOT_NUMBER;

typedef union _PCI_EXPRESS_LINK_CAPABILITIES_2_REGISTER {
	struct {
		ULONG 		Rsvd0 : 1;
		ULONG 		SupportedLinkSpeedsVector : 7;
		ULONG 		Rsvd8_31 : 24;
	};
	ULONG  			AsULONG;
} PCI_EXPRESS_LINK_CAPABILITIES_2_REGISTER, * PPCI_EXPRESS_LINK_CAPABILITIES_2_REGISTER;

typedef union _PCI_EXPRESS_LINK_CONTROL_2_REGISTER {
	struct {
		USHORT 		TargetLinkSpeed : 4;
		USHORT 		Rsvd4_15 : 12;
	};
	USHORT 			AsUSHORT;
} PCI_EXPRESS_LINK_CONTROL_2_REGISTER, * PPCI_EXPRESS_LINK_CONTROL_2_REGISTER;

typedef union _PCI_EXPRESS_LINK_STATUS_2_REGISTER {
	struct {
		USHORT 		Rsvd0_15 : 16;
	};
	USHORT 			AsUSHORT;
}PCI_EXPRESS_LINK_STATUS_2_REGISTER, * PPCI_EXPRESS_LINK_STATUS_2_REGISTER;

typedef enum {
	PciExpressPciPmLinkSubState_L11_BitIndex = 0,
	PciExpressPciPmLinkSubState_L12_BitIndex,
	PciExpressASPMLinkSubState_L11_BitIndex,
	PciExpressASPMLinkSubState_L12_BitIndex
} PCI_EXPRESS_LINK_SUBSTATE;

typedef struct _PCI_VENDOR_SPECIFIC_CAPABILITY {
	PCI_CAPABILITIES_HEADER Header;
	UCHAR                   VscLength;
	UCHAR                   VendorSpecific;
} PCI_VENDOR_SPECIFIC_CAPABILITY, * PPCI_VENDOR_SPECIFIC_CAPABILITY;




#ifndef _USER_MODE_CODE_
#ifndef _PCI_INTERNALS_H
DRIVER_IMPORT UINT32 PciHalReadUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_IMPORT void PciHalWriteUint32(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT32 Value);
DRIVER_IMPORT UINT16 PciHalReadUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_IMPORT void PciHalWriteUint16(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT16 Value);
DRIVER_IMPORT UINT8 PciHalReadUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset);
DRIVER_IMPORT void PciHalWriteUint8(PPCI_DEVICE_OBJECT PDEV, UINT32 Offset, UINT8 Value);
DRIVER_IMPORT UINT16 PciHalGetVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalGetDeviceId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalGetCommand(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalSetCommand(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_IMPORT UINT16 PciHalGetStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalSetStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_IMPORT UINT8 PciHalGetRevisionId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetProgIf(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetSubClass(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetClassCode(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetCacheLineSize(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalSetCacheLineSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_IMPORT void PciHalSetLatencyTimer(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_IMPORT UINT8 PciHalGetLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetHeaderType(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetBist(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalSetBist(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);

DRIVER_IMPORT UINT32 PciHalGeneralDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_IMPORT void PciHalGeneralDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
DRIVER_IMPORT UINT32 PciHalGeneralDeviceGetCardBusCisPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalGeneralDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalGeneralDeviceGetSubsystemId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT32 PciHalGeneralDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGeneralDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGeneralDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalGeneralDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_IMPORT UINT8 PciHalGeneralDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGeneralDeviceGetMinGrant(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGeneralDeviceGetMaxLatency(PPCI_DEVICE_OBJECT PDEV);

DRIVER_IMPORT UINT32 PciHalBridgeDeviceGetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_IMPORT void PciHalBridgeDeviceSetBar(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT32 Value);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetPrimaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetSecondaryBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetSecondaryLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetIoBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void  PciHalBridgeDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetMemoryBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetPrefetchableMemoryLimit(PPCI_DEVICE_OBJECT PDEV); 
DRIVER_IMPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Base(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT32 PciHalBridgeDeviceGetPrefetchableMemoryUpper32Limit(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetIoUpper16Base(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetIoUpper16Limit(PPCI_DEVICE_OBJECT PDEV);    
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetCapabilitiesPointer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT32 PciHalBridgeDeviceGetExpansionRomBase(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalBridgeDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_IMPORT UINT8 PciHalBridgeDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalBridgeDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);

DRIVER_IMPORT UINT32 PciHalCardBusDeviceGetCardBusSocketExCaBaseAddress(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetOffsetCapabilities(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalCardBusDeviceGetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalCardBusDeviceSetSecondaryStatus(PPCI_DEVICE_OBJECT PDEV, UINT16 Value);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetPciBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetCardBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetSubordinateBusNumber(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetCardBusLatencyTimer(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT32 PciHalCardBusDeviceGetMemoryBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_IMPORT UINT32 PciHalCardBusDeviceGetMemoryLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_IMPORT UINT32 PciHalCardBusDeviceGetIoBaseAddress(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_IMPORT UINT32 PciHalCardBusDeviceGetIoLimit(PPCI_DEVICE_OBJECT PDEV, UINT8 x);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalCardBusDeviceSetInterruptLine(PPCI_DEVICE_OBJECT PDEV, UINT8 Value);
DRIVER_IMPORT UINT8 PciHalCardBusDeviceGetInterruptPin(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalCardBusDeviceGetBridgeControl(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalCardBusDeviceGetSubsystemVendorId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT16 PciHalCardBusDeviceGetSubsystemDeviceId(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT32 PciHalCardBusDeviceGet16BitPcCardLegacyModeBaseAddress(PPCI_DEVICE_OBJECT PDEV);


DRIVER_IMPORT LOUSTATUS PciHalEnableIoSpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT LOUSTATUS PciHalDisableIoSpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT BOOLEAN PciHalIsIoSpaceEnabled(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT LOUSTATUS PciHalEnableMemorySpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT LOUSTATUS PciHalEnableBusMaster(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT LOUSTATUS PciHalDisableBusMaster(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT BOOLEAN PciHalIsBusMasterEnabled(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT LOUSTATUS PciHalDisableMemorySpace(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT BOOLEAN PciHalIsMemorySpaceEnabled(PPCI_DEVICE_OBJECT PDEV);


DRIVER_IMPORT PVOID PciHalGetIoRegion(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, SIZE Offset);
DRIVER_IMPORT LOUSTATUS PciHalAllocatePciIrqVectors(PPCI_DEVICE_OBJECT PDEV, UINT32 RequestedVectors, UINT64 Flags);
DRIVER_IMPORT UINT8 PciHalGetIrqVector(PPCI_DEVICE_OBJECT PDEV, UINT8 Member);
DRIVER_IMPORT void PciHalFreeIrqVectors(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT UINT8 PciHalGetIrqVectorCount(PPCI_DEVICE_OBJECT PDEV);
DRIVER_IMPORT void PciHalGetConfigurationSnapshot(PPCI_DEVICE_OBJECT PDEV, PPCI_COMMON_CONFIG Config);
DRIVER_IMPORT SIZE PciHalGetIoRegionSize(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar);
DRIVER_IMPORT PPCI_DEVICE_OBJECT PciHalGetDeviceFromBusAddress(UINT16 Group, UINT8 Bus, UINT8 Slot, UINT8 Function);


DRIVER_IMPORT LOUSTATUS PciHalMapPciResource(PPCI_DEVICE_OBJECT PDEV, UINT8 Bar, UINT64 OverideFlags);

#endif

KERNEL_EXPORT size_t LouKeGetMcfgCount(void* Table);

#endif

#ifdef __cplusplus
}
#endif
#endif