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

typedef struct _PCI_DEVICE_OBJECT {
	uint16_t 			VendorID;
	uint16_t 			DeviceID;
	uint16_t 			Group;
	uint8_t 			bus;
	uint8_t 			slot;
	uint8_t 			func;
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
}PCI_DEVICE_OBJECT, * PPCI_DEVICE_OBJECT;

typedef struct _AGP_BRIDGE_DATA{
	uint64_t Foo;
}AGP_BRIDGE_DATA, *PAGP_BRIDGE_DATA;

#define PCI_CONFIG_ADDRESS_PORT 0xCF8
#define PCI_CONFIG_DATA_PORT    0xCFC

// Define the PCI configuration space address space
#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

// Define PCI configuration space registers
#define PCI_VENDOR_ID      0x00
#define PCI_COMMAND        0x04
#define PCI_STATUS         0x06
#define PCI_REVISION_ID    0x08
#define PCI_CLASS_CODE     0x0B

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
    ListHeader Neigbors;
    PPCI_DEVICE_OBJECT PDEV;
    string RegistryEntry;
    string DeviceManagerString;
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
KERNEL_EXPORT uint8_t LouKeReadPciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT uint16_t LouKeReadPciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT uint32_t LouKeReadPciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT void LouKeWritePciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value);
KERNEL_EXPORT void LouKeWritePciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value);
KERNEL_EXPORT void LouKeWritePciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value);
KERNEL_EXPORT uint8_t LouKePciGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
#ifndef _KERNEL_MODULE_
uint8_t LouKePciReadHeaderType(PPCI_DEVICE_OBJECT PDEV);
uint32_t LouKeReadPciVendorId(PPCI_DEVICE_OBJECT PDEV);
uint32_t LouKeReadPciDeviceId(PPCI_DEVICE_OBJECT PDEV);
uint8_t LouKePciReadSubClass(PPCI_DEVICE_OBJECT PDEV);
uint8_t LouKePciReadClass(PPCI_DEVICE_OBJECT PDEV);
uint8_t LouKeGetPciInterruptPin(PPCI_DEVICE_OBJECT PDEV);
uint8_t LouKeGetPciInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void LouKeConfigureInterrupt(PPCI_DEVICE_OBJECT PDEV,  bool Mask, uint8_t Pin, uint8_t Destination);
void LouKeWritePciCommandRegister(PPCI_DEVICE_OBJECT PDEV,uint16_t Value);
uint16_t LouKeReadPciCommandRegister(PPCI_DEVICE_OBJECT PDEV);
uint32_t pci_read(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);
void write_pci(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset,uint32_t Value);
uint16_t pciConfigReadWord(uint16_t Group,uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);
uint8_t pciConfigReadByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg);
uint8_t getBaseClass(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
uint8_t getSubClass(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
uint8_t getSecondaryBus(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
uint16_t PciGetVendorID(uint16_t Group, uint8_t bus, uint8_t slot);
uint8_t getHeaderType(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
uint16_t PciGetDeviceID(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);
bool PciEnableDevice(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t function);
bool IsPciEnable(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);
void pciConfigWriteByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg, uint8_t value);
void pciConfigWriteWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset, uint16_t value);
void PCI_Scan_Bus();
void checkDevice(uint16_t Group, uint8_t bus, uint8_t device);
void checkBus(uint16_t Group, uint8_t bus);
void checkFunction(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
void PCI_Scan_Bus();
uint32_t pciConfigAddress(uint8_t bus, uint8_t device, uint8_t function, uint32_t reg);
uintptr_t PcieConfigAddress(uint16_t Group,uint8_t bus, uint8_t device, uint8_t function, uint32_t reg);
void pciConfigWriteByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg, uint8_t value);
void pciConfigWriteWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset, uint16_t value);
void PCI_Scan_Bus();
uint16_t PciGetVendorID(uint16_t Group, uint8_t bus, uint8_t slot);
void checkDevice(uint16_t Group, uint8_t bus, uint8_t device);
void checkBus(uint16_t Group, uint8_t bus);
void checkFunction(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
void PCI_Scan_Bus();
uint16_t PciGetDeviceID(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);
bool IsPciEnable(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);
uint8_t LouKePciGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);
void PCI_Setup();
bool PciEnableDevice(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t function);
uint16_t pciConfigReadWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);
uint8_t pciConfigReadByte(uint16_t Greoup, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg);
uint16_t pciConfigReadWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif