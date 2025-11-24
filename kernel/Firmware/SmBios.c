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

char* SmbiosGetString(SMBIOS_HEADER* Header, UINT8 Index) {
    char* StringArea = (char*)Header + Header->Length;
    while (--Index && *StringArea) {
        while (*StringArea++) {} // Skip to next string
    }
    return (*StringArea) ? StringArea : "";
}

void RegisterDmiDevice(DMI_FIELD Field, string String);

static void DmiRegisterFromSmBios(DMI_FIELD Field, string String){
    if(!memcmp(String, 0, 1)){
        RegisterDmiDevice(Field, 0x00);
        return;
    }
    RegisterDmiDevice(Field, String);
}

static void IterateSmbiosTables(uint8_t* TablePtr, uint8_t* End) {
    while (TablePtr < End) {
        SMBIOS_HEADER* Header = (SMBIOS_HEADER*)TablePtr;
        if (Header->Length < sizeof(SMBIOS_HEADER)) break;
        if ((TablePtr + Header->Length) >= End) break;


        switch(Header->Type){
            case SMBIOS_TYPE_FIRMWAE_INFORMATION:{
                PSMBIOS_FIRMWARE_INFORMATION FirmInfo = (PSMBIOS_FIRMWARE_INFORMATION)Header;
                DmiRegisterFromSmBios(DMI_BIOS_VENDOR, SmbiosGetString(Header, FirmInfo->Vendor));
                DmiRegisterFromSmBios(DMI_BIOS_VERSION, SmbiosGetString(Header, FirmInfo->FirmwareVersion));
                DmiRegisterFromSmBios(DMI_BIOS_DATE, SmbiosGetString(Header, FirmInfo->FirmwareReleaseData));

                

                break;
            }
            case SMBIOS_TYPE_SYSTEM_INFORMATION:{
                PSMBIOS_SYSTEM_INFORMATION SysInfo = (PSMBIOS_SYSTEM_INFORMATION)Header;
                DmiRegisterFromSmBios(DMI_SYSTEM_VENDOR, SmbiosGetString(Header, SysInfo->Manufacturer));
                DmiRegisterFromSmBios(DMI_PRODUCT_NAME, SmbiosGetString(Header, SysInfo->ProductName));
                
            }
        }


        uint8_t* Next = TablePtr + Header->Length;
        while (Next + 1 < End && !(Next[0] == 0 && Next[1] == 0)) {
            Next++;
        }
        Next += 2;
        TablePtr = Next;
    }
}




void InitializeSmbiosTables(void* Entry){
    if(Entry == (void*)-1){
        return;
    }
    SIZE Offset = 0x00;
    if(!strncmp(Entry, SMBIOS64_ANCHOR_STRING, strlen(SMBIOS64_ANCHOR_STRING))){
        PSMBIOS_ENTRY_3_64  Entry64 = (PSMBIOS_ENTRY_3_64)Entry;
        EnforceSystemMemoryMap(Entry64->TableAddress, ROUND_UP64(Entry64->MaxSize, KILOBYTE_PAGE));
        SmBiosAddress = LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(Entry64->MaxSize, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY, Entry64->TableAddress);
        SmBiosSupported = true;
        Offset = Entry64->TableAddress - (Entry64->TableAddress & ~(KILOBYTE_PAGE - 1));
        SmBiosAddress += Offset;
        IterateSmbiosTables((uint8_t*)SmBiosAddress, (uint8_t*)((uintptr_t)SmBiosAddress + Entry64->MaxSize));

    }else if(!strncmp(Entry, SMBIOS32_ANCHOR_STRING, strlen(SMBIOS32_ANCHOR_STRING))){
        PSMBIOS_ENTRY_2_32  Entry32 = (PSMBIOS_ENTRY_2_32)Entry;
        EnforceSystemMemoryMap(Entry32->TableAddress, ROUND_UP64(Entry32->TableLength, KILOBYTE_PAGE));
        SmBiosAddress = LouKeMallocPageEx(KILOBYTE_PAGE, ROUND_UP64(Entry32->TableLength, KILOBYTE_PAGE) / KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY, Entry32->TableAddress);
        Offset = Entry32->TableAddress - (Entry32->TableAddress & ~(KILOBYTE_PAGE - 1));
        SmBiosSupported = true;
        SmBiosAddress += Offset;
        IterateSmbiosTables((uint8_t*)(uintptr_t)SmBiosAddress , (uint8_t*)((uintptr_t)SmBiosAddress + (uintptr_t)Entry32->TableLength));
    }
}

void InitializeSmBiosSystem(void* SmBiosEntry){

    if(SmBiosEntry){
        LouKeMapContinuousMemoryBlock((uintptr_t)SmBiosEntry, (uintptr_t)SmBiosEntry, KILOBYTE_PAGE, KERNEL_GENERIC_MEMORY);
        InitializeSmbiosTables(SmBiosEntry);
        LouKeUnMapContinuousMemoryBlock((uintptr_t)SmBiosEntry, KILOBYTE_PAGE);
    }else{
        InitializeSmbiosTables(SearchForSmBiosBiosEntry());
    }
}