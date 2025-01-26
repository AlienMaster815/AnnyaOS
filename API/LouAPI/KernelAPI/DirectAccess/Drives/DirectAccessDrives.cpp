#include <LouDDK.h>
#include <NtAPI.h>

void* ReadPata(uint8_t DriveNum, uint64_t LBA, uint64_t* BufferSize);
KERNEL_IMPORT 
uint8_t LouKeGetLegacyAtaPort(uint8_t DriveNumber);

LOUDDK_API_ENTRY 
void* 
ReadDrive(
uint8_t Drive,
uint64_t LBA,
uint32_t SectorCount,
uint64_t* BufferSize,
LOUSTATUS* State
){
	void* Result = LouMalloc(*BufferSize);
	SYSTEM_DEVICE_IDENTIFIER DevID = LouKeGetStorageDeviceSystemIdentifier(Drive);
	if(DevID == ATA_DEVICE_T){
		//PATA_PORT Ap = LouKeGetAtaStoragePortObject(Drive);
		LouPrint("Device Detection Success\n");
		while(1);
	}
	
	return Result;
}

LOUDDK_API_ENTRY 
void 
WriteDrive(
uint8_t Drive,
uint32_t LBA_LOW,
uint32_t LBA_HIGH,
uint32_t SectorCount,
void* Data
){

}