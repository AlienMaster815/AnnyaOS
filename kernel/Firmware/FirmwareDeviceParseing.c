#include <LouAPI.h>

typedef unsigned ULONG;
typedef ULONG* PULONG;

LOUSTATUS LouKeGetSystemFirmwareTable(
	ULONG FirmwareTableProviderSignature,
	ULONG FirmwareTabeId,
	PVOID FirmwareTableBuffer,
	ULONG BufferLength,
	PULONG ReturnLength
);

static void* DSDT = 0x00;
static size_t DSDTLength = 0;
static void* SSDT = 0x00;
static size_t SSDTLength = 0;

void LouKeInitializeFirmwareDeviceParseing(){
    LOUSTATUS Status = LOUSTATUS_GOOD;
    uint8_t* Buffer = (uint8_t*)LouMalloc(512 * KILOBYTE);
    ULONG ReturnLength = 0x000;
    Status = LouKeGetSystemFirmwareTable(
        'ACPI',
        'DSDT', 
        Buffer, 
        512 * KILOBYTE, 
        &ReturnLength
    );

	if(Status != STATUS_SUCCESS){
        LouFree(Buffer);
	}else{
        DSDT = (void*)Buffer;
        DSDTLength = ReturnLength;
    }

    Buffer = (uint8_t*)LouMalloc(512 * KILOBYTE);

    Status = LouKeGetSystemFirmwareTable(
        'ACPI',
        'SSDT', 
        Buffer, 
        512 * KILOBYTE, 
        &ReturnLength
    );

	if(Status != STATUS_SUCCESS){
        LouFree(Buffer);
    }else {
        SSDT = (void*)Buffer;
        SSDTLength = ReturnLength;
    }

}

#pragma pack(push, 1)
typedef struct _FIRM_TABLE_GROUP {
    char DeviceName[8];
    char HardwareID[16];
    char CompatibleID[16];    
    uint64_t MMIOBaseAddress;
    uint64_t MMIOSize;
    uint16_t IOPortBase;
    uint16_t IOPortSize;
    uint8_t IRQ;
    uint8_t IRQTrigger;
    uint8_t PowerState;
    uint8_t SleepState;           
} FIRM_TABLE_GROUP, *PFIRM_TABLE_GROUP;
#pragma pack(pop)

size_t CountDevicesMatchingHID(uint8_t* aml, uint32_t length, string TargetHID);
int CheckForHID(uint8_t* aml, uint32_t length, string TargetHID);
void FillDevicesMatchingHID(uint8_t* aml, uint32_t length, string TargetHID, PFIRM_TABLE_GROUP NewGroup, size_t* DeviceIndex);
void ParseCRSResources(uint8_t* aml, uint32_t length, PFIRM_TABLE_GROUP DeviceGroup);


size_t CountDevicesMatchingHID(uint8_t* aml, uint32_t length, string TargetHID) {
    size_t count = 0;
    uint32_t i = 0;

    while (i < length) {
        if (aml[i] == 0x82) {  // Device OpCode
            i += 2;  // Skip length
            char device_name[5] = {aml[i], aml[i+1], aml[i+2], aml[i+3], '\0'};
            i += 4;

            LouPrint("Found Device: %s\n", device_name);  // Debug: Print the device name

            if (CheckForHID(aml + i, length - i, TargetHID)) {
                LouPrint("Device %s has matching HID: %s\n", device_name, TargetHID);
                count++;
            }
        } else {
            i++;
        }
    }
    return count;
}

int CheckForHID(uint8_t* aml, uint32_t length, string TargetHID) {
    uint32_t i = 0;

    while (i < length) {
        if (aml[i] == 0x08 && memcmp(aml + i + 1, "_HID", 4) == 0) {  // _HID Method
            char hid_string[16];
            memcpy(hid_string, aml + i + 5, 8);  // Assume HID is a string
            hid_string[8] = '\0';

            //LouPrint("Found HID\n");

            if (strcmp(hid_string, TargetHID) == 0) {
                return 1;  // Found matching _HID
            }
        }
        i++;
    }
    return 0;
}

void FillDevicesMatchingHID(
    uint8_t* aml, 
    uint32_t length, 
    string TargetHID,
    PFIRM_TABLE_GROUP NewGroup, 
    size_t* DeviceIndex
) {
    uint32_t i = 0;

    while (i < length) {
        if (aml[i] == 0x82) {  // Device OpCode
            i += 2;  // Skip length
            char device_name[5] = {aml[i], aml[i+1], aml[i+2], aml[i+3], '\0'};
            i += 4;

            if (CheckForHID(aml + i, length - i, TargetHID)) {
                // Fill the group
                strcpy(NewGroup[*DeviceIndex].DeviceName, device_name);
                strcpy(NewGroup[*DeviceIndex].HardwareID, TargetHID);

                // Extract _CRS resource settings
                ParseCRSResources(aml + i, length - i, &NewGroup[*DeviceIndex]);
                (*DeviceIndex)++;
            }
        } else {
            i++;
        }
    }
}

void ParseCRSResources(uint8_t* aml, uint32_t length, PFIRM_TABLE_GROUP DeviceGroup) {
    uint32_t i = 0;

    while (i < length) {
        if (aml[i] == 0x5B && aml[i+1] == 0x82) {  // _CRS OpCode
            i += 2;

            while (aml[i] != 0x79) {  // End tag
                if (aml[i] == 0x87) {  // MMIO Descriptor
                    DeviceGroup->MMIOBaseAddress = *(uint64_t*)(aml + i + 4);
                    DeviceGroup->MMIOSize = *(uint64_t*)(aml + i + 12);
                    i += 20;
                } else if (aml[i] == 0x47) {  // I/O Port Descriptor
                    DeviceGroup->IOPortBase = *(uint16_t*)(aml + i + 1);
                    DeviceGroup->IOPortSize = *(uint8_t*)(aml + i + 3);
                    i += 4;
                } else if (aml[i] == 0x89) {  // IRQ Descriptor
                    DeviceGroup->IRQ = *(uint8_t*)(aml + i + 3);
                    i += 4;
                } else {
                    i++;
                }
            }
        } else {
            i++;
        }
    }
}


PFIRM_TABLE_GROUP LouKeGetDeviceGroupFirmwareTables(
    string HardwareID,
    uint64_t* NumberOfDevices
){
    size_t DSDTCount = 0;
    size_t SSDTCount = 0;
    if(DSDT){
        DSDTCount = CountDevicesMatchingHID(DSDT, DSDTLength, HardwareID);
    }
    if(SSDT) {
        SSDTCount = CountDevicesMatchingHID(SSDT, SSDTLength, HardwareID);
    }

    *NumberOfDevices = SSDTCount + DSDTCount;

    if(!(*NumberOfDevices)){
        return 0x00;
    }

    PFIRM_TABLE_GROUP NewGroup = (PFIRM_TABLE_GROUP)LouMallocEx(sizeof(FIRM_TABLE_GROUP) * (*NumberOfDevices), 1);

    size_t Index = 0;
    
    if(DSDT){
        FillDevicesMatchingHID(DSDT, DSDTLength, HardwareID, NewGroup, &Index);
    }
    if(SSDT) {
        FillDevicesMatchingHID(SSDT, SSDTLength, HardwareID, NewGroup, &Index);
    }

    return NewGroup;
}