#include <LouACPI.h>
#include <acpi.h>


static LOUSTATUS MapLapicId(
    ACPI_SUBTABLE_HEADER*   Entry,
    UINT32                  AcpiId,
    UINT64*                 ApicId
){
    ACPI_MADT_LOCAL_APIC* Lapic = CONTAINER_OF(Entry, ACPI_MADT_LOCAL_APIC, Header);
    if(!(Lapic->LapicFlags & ACPI_MADT_ENABLED)){
        return STATUS_NO_SUCH_DEVICE; 
    }
    if(Lapic->ProcessorId != AcpiId){
        return STATUS_INVALID_PARAMETER;
    }
    *ApicId = Lapic->Id;
    return STATUS_SUCCESS;
}

static LOUSTATUS MapLsapicId(
    ACPI_SUBTABLE_HEADER*   Entry,
    INTEGER                 Type, 
    UINT32                  AcpiId,
    UINT64*                 LsapicId
){
    ACPI_MADT_LOCAL_SAPIC* Lsapic = CONTAINER_OF(Entry, ACPI_MADT_LOCAL_SAPIC, Header);
    if(!(Lsapic->LapicFlags & ACPI_MADT_ENABLED)){
        return STATUS_NO_SUCH_DEVICE; 
    }
    if(Type){
        if((Entry->Length < 16) || (Lsapic->Uid != AcpiId)){
            return STATUS_INVALID_PARAMETER;
        }
    }
    else if(Lsapic->ProcessorId != AcpiId){
        return STATUS_INVALID_PARAMETER;
    }
    *LsapicId = (Lsapic->Id << 8) | Lsapic->Eid;
    return STATUS_SUCCESS;
}

static LOUSTATUS Mapx2ApicId(
    ACPI_SUBTABLE_HEADER*   Entry,
    INTEGER                 Type, 
    UINT32                  AcpiId,
    UINT64*                 LsapicId
){

    LouPrint("Mapx2ApicId()\n");
    while(1);
    return STATUS_SUCCESS;
}

static LOUSTATUS MapGiccMpdir(
    ACPI_SUBTABLE_HEADER*   Entry,
    INTEGER                 Type, 
    UINT32                  AcpiId,
    UINT64*                 LsapicId
){

    LouPrint("MapGiccMpdir()\n");
    while(1);
    return STATUS_SUCCESS;
}

static LOUSTATUS MapCorePicId(
    ACPI_SUBTABLE_HEADER*   Entry,
    INTEGER                 Type, 
    UINT32                  AcpiId,
    UINT64*                 LsapicId
){

    LouPrint("MapCorePicId()\n");
    while(1);
    return STATUS_SUCCESS;
}

static UINT64 MapMatEntry(
    ACPI_HANDLE AcpiHandle, 
    INTEGER Type, 
    UINT32 AcpiId
){
    ACPI_BUFFER Buffer =    {ACPI_ALLOCATE_BUFFER, NULL};
    ACPI_OBJECT*            Obj;
    ACPI_SUBTABLE_HEADER*   Header;
    UINT64                  PhyID = UINT64_MAX;
    
    if(ACPI_FAILURE(AcpiEvaluateObject(AcpiHandle, "_MAT", NULL, &Buffer))){
        LouPrint("Unable To Evaluate _MAT Table\n");
        goto _MAP_MAT_ENTRY_EXIT;
    }
    
    if((!Buffer.Length) || (!Buffer.Pointer)){
        LouPrint("Error _MAT Evaluation Returned Bad Data\n");
        goto _MAP_MAT_ENTRY_EXIT;
    }

    Obj = (ACPI_OBJECT*)Buffer.Pointer;

    if((Obj->Type != ACPI_TYPE_BUFFER) || (Obj->Buffer.Length < sizeof(ACPI_SUBTABLE_HEADER))){
        goto _MAP_MAT_ENTRY_EXIT;
    }

    Header = (ACPI_SUBTABLE_HEADER*)Obj->Buffer.Pointer;
    if(Header->Type == ACPI_MADT_TYPE_LOCAL_APIC){
        MapLapicId(AcpiHandle, AcpiId, &PhyID);
    }
    else if(Header->Type == ACPI_MADT_TYPE_LOCAL_SAPIC){
        MapLsapicId(AcpiHandle, Type, AcpiId, &PhyID);
    }
    else if(Header->Type == ACPI_MADT_TYPE_LOCAL_X2APIC){
        Mapx2ApicId(AcpiHandle, Type, AcpiId, &PhyID);
    }
    else if(Header->Type == ACPI_MADT_TYPE_GENERIC_INTERRUPT){
        MapGiccMpdir(AcpiHandle, Type, AcpiId, &PhyID);
    }
    else if(Header->Type == ACPI_MADT_TYPE_CORE_PIC){
        MapCorePicId(AcpiHandle, Type, AcpiId, &PhyID);
    }

    _MAP_MAT_ENTRY_EXIT:
    if(Buffer.Pointer){
        AcpiOsFree(Buffer.Pointer);
    }    
    return PhyID;
}

UINT64 AcpiGetPhyId(
    ACPI_HANDLE AcpiHandle, 
    INTEGER Type, 
    UINT32 AcpiId
){
    UINT64 PhyId;
    PhyId = MapMatEntry(AcpiHandle, Type, AcpiId);
    if(INVALID_ACPI_CPU_PHY_ID(PhyId)){
        //MapMatEntry(GetMadtTable(), Type, AcpiId);
    }

    return PhyId;
}

INTEGER AcpiMapCpuid(UINT64 PhyID, UINT32 AcpiID){
    //INTEGER i = 0 ;
    if(INVALID_ACPI_CPU_PHY_ID(PhyID)){
        return INVALID_CPU_ID;
    }
    
    LouPrint("AcpiMapCpuid()\n");
    while(1);
    return PhyID;
}

INTEGER AcpiGetCpuId(
    ACPI_HANDLE AcpiHandle, 
    INTEGER Type, 
    UINT32 AcpiId
){
    UNUSED UINT64 CpuPhyId = 0x00;
    
    CpuPhyId = AcpiGetPhyId(AcpiHandle, Type, AcpiId);

    return AcpiMapCpuid(CpuPhyId, AcpiId);
}

bool IsProcessorPhysicallyPresent(ACPI_HANDLE AcpiHandle){
    INTEGER             CpuId, Type;
    UINT32              AcpiId;
    ACPI_STATUS         Status;
    ACPI_OBJECT_TYPE    AcpiType;
    UINT64              Tmp;
    ACPI_OBJECT         Obj = {0};
    ACPI_BUFFER         Buffer = {sizeof(ACPI_OBJECT), &Obj};

    Status = AcpiGetType(AcpiHandle, &AcpiType);
    if(ACPI_FAILURE(Status)){
        return false;
    }

    switch(AcpiType){
        case ACPI_TYPE_PROCESSOR:{
            Status = AcpiEvaluateObject(AcpiHandle, NULL, NULL, &Buffer);
            if(ACPI_FAILURE(Status)){
                return false;
            }
            AcpiId = Obj.Processor.ProcId;
            break;
        }
        case ACPI_TYPE_DEVICE:{
            Status = AcpiEvaluateInteger(AcpiHandle, METHOD_NAME__UID, NULL, &Tmp);
            if(ACPI_FAILURE(Status)){
                return false;
            }
            AcpiId = Tmp;
            break;
        }
        default:{
            return false;
        }
        
    }

    Type = (AcpiType == ACPI_TYPE_DEVICE) ? 1 : 0;
    CpuId = AcpiGetCpuId(AcpiHandle, Type, AcpiId);

    return !INVALID_ACPI_CPU_ID(CpuId);
}

static const GUID SbGuid = {DEFINE_GUID(0x4077A616, 0x290C, 0x47BE, 0x9E, 0xBD, 0xD8, 0x70, 0x58, 0x71, 0x39, 0x53)};
ACPI_STATUS AcpiProcessorOsc(
    ACPI_HANDLE AcpiHandle,
    UINT32      Level,
    PVOID       Context,
    PVOID*      Rv
){
    UINT32  CapBuffer[2]        = {0};
    ACPI_STATUS Status          = AE_OK;
    UNUSED ACPI_OSC_CONTEXT Ctx = {
        .Uuid                   = (GUID*)&SbGuid,
        .Revision               = 1,
        .Capabilities.Length    = 8,
        .Capabilities.Pointer   = CapBuffer, 
    };

    if(!IsProcessorPhysicallyPresent(AcpiHandle)){
        return Status; //return AE_OK
    }



    LouPrint("AcpiProcessorOsc()\n");
    while(1);
    return AE_OK;
}

static bool AcpiEarlyProcessorOsc(){
    ACPI_STATUS Status;

    Status = AcpiWalkNamespace(
        ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT, 
        ACPI_UINT32_MAX, AcpiProcessorOsc, NULL, 
        NULL, NULL
    );
    if(ACPI_FAILURE(Status)){
        return false;
    }

    Status = AcpiGetDevices(ACPI_PROCESSOR_DEVICE_HID, AcpiProcessorOsc, NULL, NULL);
    if(ACPI_FAILURE(Status)){
        return false;
    }

    return true;
}

static void AcpiEarlyProcessorSetPdc(){

}

void AcpiEarlyProcessorControlSetup(){
    if(AcpiEarlyProcessorOsc()){
        LouPrint("_OSC Evaluated Successfully For All Processors\n");
    }else{
        LouPrint("_OSC Evaluation Failed Trying _PDC\n");
        AcpiEarlyProcessorSetPdc();
        LouPrint("AcpiEarlyProcessorControlSetup()\n");
        while(1);
    }
}