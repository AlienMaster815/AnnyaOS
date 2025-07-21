#include <LouACPI.h>
#include <acpi.h>

typedef struct PACKED _PRM_MMIO_ADDRESS_INFORMATION{
    UINT64                          PhyAddress;
    UINT64                          VirtAddress;
    UINT32                          Length;
}PRM_MMIO_ADDRESS_INFORMATION, * PPRM_MMIO_ADDRESS_INFORMATION;

typedef struct PACKED _PRM_MMIO_INFORMATION{
    UINT64                          MmioCount;
    PPRM_MMIO_ADDRESS_INFORMATION   AddressRanges;
}PRM_MMIO_INFORMATION, * PPRM_MMIO_INFORMATION;

typedef struct _PRM_HANDLER_INFORMATION{
    EFI_GUID                        Guid;
    EFI_STATUS                      (*EfiApiHandlerAddress)(UINT64, PVOID);
    UINT64                          StaticDataBufferAddress;
    UINT64                          AcpiParameterBufferAddress;
    ListHeader                      HandlerList;
}PRM_HANDLER_INFORMATION, * PPRM_HANDLER_INFORMATION;

typedef struct _PRM_MODULE_INFORMATION{
    GUID                            Guid;
    UINT16                          MajorRevision;
    UINT16                          MinorRevision;
    UINT16                          HandlerCount;
    PPRM_MMIO_INFORMATION           MmioInformation;
    bool                            Updateable;
    ListHeader                      ModuleList;
    PRM_HANDLER_INFORMATION         Handlers[];
}PRM_MODULE_INFORMATION, * PPRM_MODULE_INFORMATION;

static LOUSTATUS AcpiParsePrmt(
    PACPI_SUB_TABLE_HEADERS Header, 
    size_t End
){ 
    ACPI_PRMT_MODULE_INFO* ModuleInfo;
    UNUSED ACPI_PRMT_HANDLER_INFO* HandlerInfo;
    UNUSED PPRM_HANDLER_INFORMATION Th = 0x00;
    PPRM_MODULE_INFORMATION Tm = 0x00;
    UNUSED UINT64* MmioCount;
    UNUSED UINT64 CurrentHander = 0;
    UINT32 ModuleInfoSize = 0;
    UNUSED UINT64 MmioRangeSize = 0;
    UNUSED PVOID TempMmio;

    ModuleInfo = (ACPI_PRMT_MODULE_INFO*)Header;
    ModuleInfoSize = GetStructureSize(Tm, Handlers, ModuleInfo->HandlerInfoCount);
    Tm = LouKeMalloc(ModuleInfoSize, KERNEL_GENERIC_MEMORY);
    memcpy(&Tm->Guid, ModuleInfo->ModuleGuid, sizeof(GUID));
    Tm->MajorRevision = ModuleInfo->MajorRev;
    Tm->MinorRevision = ModuleInfo->MinorRev;
    Tm->HandlerCount = ModuleInfo->HandlerInfoCount;
    Tm->Updateable = true;


    LouPrint("AcpiParsePrmt()\n");
    while(1);
    return STATUS_SUCCESS;
}

void AcpiInitializePlatformRuntime(){
    ACPI_TABLE_HEADER*          Table;
    ACPI_STATUS                 Status;
    LOUSTATUS LouStatus = 0x00;

    Status = AcpiGetTable(ACPI_SIG_PRMT, 0, &Table);
    if(ACPI_FAILURE(Status)){
        LouPrint("LouACPI:ACPI_FAILURE PRMT Not Found:LOUSTATUS:STATUS_OK\n");
        return;
    }

    LouStatus = LouKeAcpiTableParseEntries(
        ACPI_SIG_PRMT,
        sizeof(ACPI_TABLE_PRMT) + sizeof(ACPI_TABLE_PRMT_HEADER),
        0, AcpiParsePrmt, 0
    );

    AcpiPutTable(Table);

    if(LouStatus == STATUS_UNSUCCESSFUL){
        return;
    }

    if(!IsSystemEfi()){
        LouPrint("ERROR: EFI Runtime Service Unavailable\n");
        return;
    }



    LouPrint("AcpiInitializePlatformRuntime()\n");
    while(1);
}