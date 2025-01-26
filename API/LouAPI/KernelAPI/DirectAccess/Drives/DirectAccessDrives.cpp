#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT
PLOUSINE_KERNEL_DEVICE_ATA_PORT LouKeGetAtaStoragePortObject(uint8_t DriveNumber);

LOUDDK_API_ENTRY 
void* 
ReadDrive(
uint8_t Drive,
uint64_t LBA,
uint32_t SectorCount,
uint64_t* BufferSize,
LOUSTATUS* State
){
	uint8_t* Result = (uint8_t*)LouMalloc(KILOBYTE_PAGE);
	LouKeMapContinuousMemoryBlock((uint64_t)Result, (uint64_t)Result, KILOBYTE_PAGE, WRITEABLE_PAGE | PRESENT_PAGE | UNCACHEABLE_PAGE);

	LouPrint("Result Is : %h\n", Result);
	SYSTEM_DEVICE_IDENTIFIER DevID = LouKeGetStorageDeviceSystemIdentifier(Drive);
	if(DevID == ATA_DEVICE_T){
		UNUSED PLOUSINE_KERNEL_DEVICE_ATA_PORT Port = LouKeGetAtaStoragePortObject(Drive);
		UNUSED ATA_QUEUED_COMMAND Command;
		Command.WriteCommand = false;
		if(Port->PortScsiDevice){
			Command.Command     = ATA_COMMAND_IDENTIFY_ATAPI;
			Command.WriteCommand= false;
			Command.DataAddress = (uint64_t)Result;
			Command.Port        = Port;
			Command.WriteCommand= false;
			Command.Lbal        = 0;
			Command.Lbam        = 0;
			Command.Lbah        = 0;
			Command.SectorCount = 0;
			Command.ScsiCommandLength = 0;
			Command.PacketCommand = false;

			LouPrint("Port Number:%d\n", Port->PortNumber);
			*State = Port->Operations->PrepCommand(&Command);
			if(*State != STATUS_SUCCESS){
				return Result;
			}
			*State = Port->Operations->IssueCommand(&Command);
		}else{

		}

	}

	for(uint8_t i = 0 ; i <  12; i++){
		LouPrint("%h ", Result[i]);
	}

	while(1);
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