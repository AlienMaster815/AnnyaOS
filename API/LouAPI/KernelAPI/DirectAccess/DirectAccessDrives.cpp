#include <LouDDK.h>
#include <NtAPI.h>

KERNEL_IMPORT
PLOUSINE_KERNEL_DEVICE_ATA_PORT LouKeGetAtaStoragePortObject(uint8_t DriveNumber);

LOUDDK_API_ENTRY
LOUSTATUS LouKeAtaReadDevice(
	PLOUSINE_KERNEL_DEVICE_ATA_PORT AtaPort,
    uint64_t LBA,
    uint32_t SectorCount,
    uint64_t BufferSize,
    void* DataBuffer
);

LOUDDK_API_ENTRY 
void* 
ReadDrive(
uint8_t Drive,
uint64_t LBA,
uint32_t SectorCount,
uint64_t* BufferSize,
LOUSTATUS* State
){	

	uint64_t BufferChecksum;

	void* Result;
	SYSTEM_DEVICE_IDENTIFIER DevID = LouKeGetStorageDeviceSystemIdentifier(Drive);
	if(DevID == ATA_DEVICE_T){
		BufferChecksum = ROUND_UP64(*BufferSize, 2048);
		BufferChecksum /= 2048;
		if(SectorCount > BufferChecksum){
			BufferChecksum = SectorCount * 2048;
		}else{
			SectorCount = BufferChecksum;
			BufferChecksum = BufferChecksum * 2048;
		}
		Result = LouMalloc(BufferChecksum);//, WRITEABLE_PAGE | UNCACHEABLE_PAGE | PRESENT_PAGE);
		PLOUSINE_KERNEL_DEVICE_ATA_PORT Port = LouKeGetAtaStoragePortObject(Drive);
		*State = LouKeAtaReadDevice(Port, LBA, SectorCount, *BufferSize, Result);
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