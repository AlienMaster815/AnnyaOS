/*
-- Tyler Grenier 2/6/24 11:14:45 AM
*/

//Define the Lou Driver Kit For Our Constants

#ifndef _KERNEL_MODULE_
#ifndef _PCI_MODULES_H
#define _PCI_MODULES_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif
#include "PciIds.h"
#include <kernel/atomic.h>

typedef struct _LOUSINE_PCI_DEVICE_TABLE{
	uint16_t VendorID;
	uint16_t DeviceID;
	uint16_t SubVendorID;
	uint16_t SubDeviceID;
	uint8_t  BaseClass;
	uint8_t  SubClass;
	uint64_t BoardID;
	uint64_t DriverData;
	bool     SimpleEntry;
	bool     AdvancedEntry;
	bool 	 SimpleWithClass;
	bool 	 GenericEntry;
}LOUSINE_PCI_DEVICE_TABLE, * PLOUSINE_PCI_DEVICE_TABLE;;


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
#define PCI_IRQ_MSI (1 << 0)
#define PCI_IRQ_MSIX (1 << 1)

typedef struct _PCIDev {

}PCIDev, * P_PCIDEV;

typedef struct _PCIBuffer {

}PCIBuffer, * P_PCIBuffer;


typedef int pci_power_t;

#ifndef _PCI_DEVICE_OBJECT_
#define _PCI_DEVICE_OBJECT_
typedef struct _PCI_DEVICE_OBJECT {
	uint16_t 			VendorID;
	uint16_t 			DeviceID;
	uint16_t 			Group;
	uint8_t 			bus;
	uint8_t 			slot;
	uint8_t 			func;
	bool				InterruptsEnabled;
	int 				NumberOfSAssignedVectors;
	uint64_t* 			InterruptVectors;
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
#endif

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

enum BaseAddressRegisterType {
	MemoryMapping = 0,
	InputOutPut = 1
};


uint8_t LouKePciGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);

//Is C Land
void PCI_Setup();

bool PciEnableDevice(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t function);

uint16_t pciConfigReadWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);


uint8_t pciConfigReadByte(uint16_t Greoup, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg);


uint16_t pciConfigReadWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset);

void PCI_Scan_Bus();
uint16_t PciGetVendorID(uint16_t Group, uint8_t bus, uint8_t slot);
void checkDevice(uint16_t Group, uint8_t bus, uint8_t device);
void checkBus(uint16_t Group, uint8_t bus);
void checkFunction(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function);
void PCI_Scan_Bus();
uint16_t PciGetDeviceID(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);
bool IsPciEnable(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func);

void pciConfigWriteByte(uint16_t Group, uint8_t bus, uint8_t device, uint8_t function, uint32_t reg, uint8_t value);
void pciConfigWriteWord(uint16_t Group, uint8_t bus, uint8_t slot, uint8_t func, uint32_t offset, uint16_t value);


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

uint8_t LouKeReadPciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
uint16_t LouKeReadPciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
uint32_t LouKeReadPciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
void LouKeWritePciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value);
void LouKeWritePciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value);
void LouKeWritePciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value);

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

#ifdef __cplusplus
}
#endif
#endif

#else //_KERNEL_MODULE_
#ifndef _PCI_MODULES_H
#define _PCI_MODULES_H

#include <LouDDK.h>
#include <kernel/atomic.h>

typedef struct _ACPI_MCFG_ALLOCATION{
    uint64_t    BaseAddress;
    uint16_t    PCISegmentGroupNumber;
    uint8_t     StartBusNumber;
    uint8_t     EndBusNumber;
    uint32_t    Reserved;
} ACPI_MCFG_ALLOCATION, * PACPI_MCFG_ALLOCATION;

typedef struct _LOUSINE_PCI_DEVICE_TABLE{
	uint16_t VendorID;
	uint16_t DeviceID;
	uint16_t SubVendorID;
	uint16_t SubDeviceID;
	uint8_t  BaseClass;
	uint8_t  SubClass;
	uint64_t BoardID;
	uint64_t DriverData;
	bool     SimpleEntry;
	bool     AdvancedEntry;
	bool 	 SimpleWithClass;
	bool 	 GenericEntry;
}LOUSINE_PCI_DEVICE_TABLE, * PLOUSINE_PCI_DEVICE_TABLE;;

typedef struct _PCIDev {

}PCIDev, * P_PCIDEV;

typedef struct _PCIBuffer {

}PCIBuffer, * P_PCIBuffer;


typedef int pci_power_t;

#ifndef _PCI_DEVICE_OBJECT_
#define _PCI_DEVICE_OBJECT_
typedef struct _PCI_DEVICE_OBJECT {
	uint16_t 			VendorID;
	uint16_t 			DeviceID;
	uint16_t 			Group;
	uint8_t 			bus;
	uint8_t 			slot;
	uint8_t 			func;
	bool				InterruptsEnabled;
	int 				NumberOfSAssignedVectors;
	uint64_t* 			InterruptVectors;
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
#endif

KERNEL_EXPORT uint8_t LouKeReadPciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT uint16_t LouKeReadPciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT uint32_t LouKeReadPciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset);
KERNEL_EXPORT void LouKeWritePciUint8(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint8_t Value);
KERNEL_EXPORT void LouKeWritePciUint16(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint16_t Value);
KERNEL_EXPORT void LouKeWritePciUint32(PPCI_DEVICE_OBJECT PDEV, uint32_t Offset, uint32_t Value);
KERNEL_EXPORT uint8_t LouKePciGetInterruptLine(PPCI_DEVICE_OBJECT PDEV);

#define ANY_PCI_ID 0xFFFF
#define ANY_PCI_CLASS 255

#endif
#endif