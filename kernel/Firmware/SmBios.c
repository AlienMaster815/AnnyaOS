#include <LouACPI.h>
#include <acpi.h>



#define SMBIOS_BIOS_ENTRY           0x000F0000 
#define SMBIOS_BIOS_SCAN_RANGE      (64 * KILOBYTE)

UNUSED static bool SmBiosSupported = false;
UNUSED static void* SmBiosAddress;

static void* SearchForSmBiosBiosEntry(){
    UNUSED UINT8* VirtualScanArea = LouKeMallocPageEx(KILOBYTE_PAGE, (SMBIOS_BIOS_SCAN_RANGE / KILOBYTE_PAGE), KERNEL_GENERIC_MEMORY, SMBIOS_BIOS_ENTRY);
    for(size_t i = 0 ; i < (SMBIOS_BIOS_SCAN_RANGE - 4); i++){
        if(memcmp(&VirtualScanArea[i], "_SM_", 4) == 0){
            LouPrint("Found the SMBIOS Entry At:%h\n", &VirtualScanArea[i]);
            return (void*)&VirtualScanArea[i];
        }
    }
    return (void*)-1;
}

void* GetSmBiosAddress(){
    if(!SmBiosSupported){
        return 0x00;
    }
    return SmBiosAddress;
}

void InitializeSmbiosTables(void* Entry){

    if(!strncmp(Entry, SMBIOS32_ANCHOR_STRING, strlen(SMBIOS32_ANCHOR_STRING))){
        PSMBIOS_ENTRY_2_32  Entry32 = (PSMBIOS_ENTRY_2_32)Entry;
        EnforceSystemMemoryMap(Entry32->TableAddress, ROUND_UP64(Entry32->TableLength, KILOBYTE_PAGE));
        SmBiosAddress = LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(Entry32->TableLength, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY, Entry32->TableAddress);
        SmBiosSupported = true;
    }else if(!strncmp(Entry, SMBIOS64_ANCHOR_STRING, strlen(SMBIOS64_ANCHOR_STRING))){
        PSMBIOS_ENTRY_3_64  Entry64 = (PSMBIOS_ENTRY_3_64)Entry;
        EnforceSystemMemoryMap(Entry64->TableAddress, ROUND_UP64(Entry64->MaxSize, KILOBYTE_PAGE));
        SmBiosAddress = LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(Entry64->MaxSize, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY, Entry64->TableAddress);
        SmBiosSupported = true;
    }

}

void InitializeSmBiosSystem(void* SmBiosEntry){
    if(SmBiosEntry){
        InitializeSmbiosTables(SmBiosEntry);
    }else{
        InitializeSmbiosTables(SearchForSmBiosBiosEntry());
    }
}