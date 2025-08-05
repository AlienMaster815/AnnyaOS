#include <LouDDK.h>

LOUDDK_API_ENTRY uint64_t LouKeLinkerGetAddress(
    string ModuleName,
    string FunctionName
);

LOUDDK_API_ENTRY
void* 
LouKeLoadSubsystem(string Subsystem, string EntryName){
    PDRIVER_OBJECT DriverObject;
    string SubsystemPath = LouKeMallocArray(char , strlen("C:/ANNYA/SYSTEM64/") + strlen(Subsystem), KERNEL_GENERIC_MEMORY);    
    strncpy(SubsystemPath, "C:/ANNYA/SYSTEM64/", strlen("C:/ANNYA/SYSTEM64/"));
    strncpy(SubsystemPath + strlen("C:/ANNYA/SYSTEM64/"), Subsystem, strlen(Subsystem));
    DRIVER_MODULE_ENTRY Driver = LouKeLoadKernelModule(SubsystemPath, (void**)&DriverObject, sizeof(DRIVER_OBJECT));
    if(!DriverObject->DriverExtension){
        DriverObject->DriverExtension = (PDRIVER_EXTENSION)LouKeMallocType(DRIVER_EXTENSION, KERNEL_GENERIC_MEMORY);
        Driver(DriverObject, (PUNICODE_STRING)SubsystemPath);
    }
    LouKeFree(SubsystemPath);
    if(!EntryName){
        return 0x00;
    }
    return (void*)LouKeLinkerGetAddress(Subsystem, EntryName);
}



LOUDDK_API_ENTRY
void* 
LouKeLoadDriver(string Subsystem, string EntryName){
    PDRIVER_OBJECT DriverObject;
    string SubsystemPath = LouKeMallocArray(char , strlen("C:/ANNYA/SYSTEM64/DRIVERS/") + strlen(Subsystem), KERNEL_GENERIC_MEMORY);    
    strncpy(SubsystemPath, "C:/ANNYA/SYSTEM64/DRIVERS/", strlen("C:/ANNYA/SYSTEM64/DRIVERS/"));
    strncpy(SubsystemPath + strlen("C:/ANNYA/SYSTEM64/DRIVERS/"), Subsystem, strlen(Subsystem));
    DRIVER_MODULE_ENTRY Driver = LouKeLoadKernelModule(SubsystemPath, (void**)&DriverObject, sizeof(DRIVER_OBJECT));
    if(!DriverObject->DriverExtension){
        DriverObject->DriverExtension = (PDRIVER_EXTENSION)LouKeMallocType(DRIVER_EXTENSION, KERNEL_GENERIC_MEMORY);
        Driver(DriverObject, (PUNICODE_STRING)SubsystemPath);
    }
    LouKeFree(SubsystemPath);
    if(!EntryName){
        return 0x00;
    }
    return (void*)LouKeLinkerGetAddress(Subsystem, EntryName);
}