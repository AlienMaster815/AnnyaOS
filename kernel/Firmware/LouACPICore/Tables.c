#include <LouACPI.h>
#include <acpi.h>

static size_t AcpiApicInstance = 0;

static LOUSTATUS CallHandler(
    PACPI_SUB_TABLE_PROCESSOR   Processor,
    PACPI_SUB_TABLE_HEADERS     Headers,
    size_t                      End
){
    if(Processor->Handler){
        return Processor->Handler(Headers, End);
    }
    if(Processor->HandlerArgs){
        return Processor->HandlerArgs(Headers,Processor->Arguments, End);
    }
    return STATUS_INVALID_PARAMETER;
}

static ACPI_SUB_TABLE_TYPE AcpiGetSubTableType(string Id){
    uint32_t IdUint = 0;
    memcpy(&IdUint, Id, sizeof(uint32_t));
    //TODO: add Le32ToCpu for the IdUint
    switch(IdUint){
        case ACPI_CDAT_SUB_TABLE:
        case ACPI_SUB_TABLE_HMAT:
        case ACPI_SUB_TABLE_PRMT:
        case ACPI_SUB_TABLE_CEDT:
            return IdUint;
        default:
            return ACPI_SUB_TABLE_COMMON;
    }
}

static size_t AcpiGetTableLength(
    ACPI_SUB_TABLE_TYPE     Type,
    PFIRMWARE_TABLE_HEADER  Header
){
    if(Type == ACPI_CDAT_SUB_TABLE){
        return Header->CdatTable.Length;
    }
    return Header->CommonTable.Length;
}

static size_t AcpiGetSubTableLength(
    PACPI_SUB_TABLE_ENTRY Entry
){
    switch(Entry->Type){
        case ACPI_SUB_TABLE_COMMON:
            return sizeof(Entry->Header->GenericHeader);
        case ACPI_SUB_TABLE_HMAT:
            return sizeof(Entry->Header->HmatHeader);
        case ACPI_SUB_TABLE_PRMT:
            return sizeof(Entry->Header->PrmtHeader);
        case ACPI_SUB_TABLE_CEDT:
            return sizeof(Entry->Header->CedtHeader);
        case ACPI_CDAT_SUB_TABLE:
            return sizeof(Entry->Header->CdatHeader);
    }
    return 0x00;
}

static size_t AcpiGetEntryLength(
    PACPI_SUB_TABLE_ENTRY Entry
){
    switch(Entry->Type){
        case ACPI_SUB_TABLE_COMMON:
            return Entry->Header->GenericHeader.Length;
        case ACPI_SUB_TABLE_HMAT:
            return Entry->Header->HmatHeader.Length;
        case ACPI_SUB_TABLE_PRMT:
            return Entry->Header->PrmtHeader.Length;
        case ACPI_SUB_TABLE_CEDT:
            return Entry->Header->CedtHeader.Length;
        case ACPI_CDAT_SUB_TABLE:
            return Entry->Header->CdatHeader.Length;
    }
    return 0x00;
}

static uint32_t AcpiGetEntryType(PACPI_SUB_TABLE_ENTRY Entry){
    switch(Entry->Type){
        case ACPI_SUB_TABLE_COMMON:
            return Entry->Header->GenericHeader.Type;
        case ACPI_SUB_TABLE_HMAT:
            return Entry->Header->HmatHeader.Type;
        case ACPI_SUB_TABLE_PRMT:
            return ACPI_SUB_TABLE_PRMT;
        case ACPI_SUB_TABLE_CEDT:
            return Entry->Header->CedtHeader.Type;
        case ACPI_CDAT_SUB_TABLE:
            return Entry->Header->CdatHeader.Type;
    }
    return 0x00;
}

int LouKeAcpiParseEntriesArray(
    string                      Id,
    size_t                      TableSize,
    PFIRMWARE_TABLE_HEADER      TableHeader,
    size_t                      MaxLength,
    PACPI_SUB_TABLE_PROCESSOR   Processor,
    int                         ProcessNumber,
    size_t                      MaxEntries
){
    UNUSED size_t TableLength = 0 , TableEnd = 0, SubTableLength = 0, EntryLength = 0;
    ACPI_SUB_TABLE_ENTRY    Entry = {0};
    ACPI_SUB_TABLE_TYPE     Type = 0;
    UNUSED int ReferenceCount = 0;
    UNUSED int i = 0;

    Type = AcpiGetSubTableType(Id);
    TableLength = AcpiGetTableLength(Type, TableHeader);

    if((MaxLength) && (MaxLength < TableLength)){
        TableLength = MaxLength;
    }

    TableEnd        = ((size_t)TableHeader + TableLength);
    Entry.Header    = (PACPI_SUB_TABLE_HEADERS)((size_t)TableHeader + TableSize);
    Entry.Type      = Type;
    SubTableLength  = AcpiGetSubTableLength(&Entry);
    while(((size_t)Entry.Header) + SubTableLength < TableEnd){
        for(i = 0 ; i < ProcessNumber; i++){
            if(AcpiGetEntryType(&Entry) != Processor[i].Id){
                continue;
            }
            if((!MaxEntries) || (ReferenceCount < MaxEntries)){
                if(CallHandler(&Processor[i], Entry.Header, TableEnd)){
                    return STATUS_INVALID_PARAMETER;
                }
            }
            Processor[i].ReferenceCount++;
            ReferenceCount++;
            break;
        }

        EntryLength = AcpiGetEntryLength(&Entry);
        
        if(!EntryLength){
            LouPrint("LouKeAcpiParseEntriesArray():ERROR:0 is an invalid Entry Length\n");
            return STATUS_INVALID_PARAMETER; 
        }

        Entry.Header = (PACPI_SUB_TABLE_HEADERS)((size_t)Entry.Header + EntryLength);
    }

    if((MaxEntries) && (ReferenceCount > MaxEntries)){
        LouPrint("LouKeAcpiParseEntriesArray():ERROR: Ignored :%d Entries Of %d Found\n", ReferenceCount - MaxEntries , MaxEntries);
    }

    return ReferenceCount;
}

int LouKeAcpiTableParseEntriesArray(
    string                          Id,
    size_t                          TableSize,
    PACPI_SUB_TABLE_PROCESSOR       Processor,
    int                             ProcessNumber,
    size_t                          MaxEntries
);

static int _LouKeAcpiTableParseEntries(
    string                          Id, 
    size_t                          TableSize,
    int                             EntryID,
    ACPI_TABLE_ENTRY_HANDLER        Handler,
    ACPI_TABLE_ENTRY_HANDLER_ARGS   HandlerArgs,
    void*                           Args,
    size_t                          MaxEntries
){

    ACPI_SUB_TABLE_PROCESSOR Processor = {
        .Id = EntryID,
        .Handler = Handler,
        .HandlerArgs = HandlerArgs,
        .Arguments = Args,
    };

    return LouKeAcpiTableParseEntriesArray(Id, TableSize, &Processor, 1, MaxEntries);
}


int LouKeAcpiTableParseEntriesArray(
    string                          Id,
    size_t                          TableSize,
    PACPI_SUB_TABLE_PROCESSOR       Processor,
    int                             ProcessorNumber,
    size_t                          MaxEntries
){
    ACPI_TABLE_HEADER*  TableHeader = 0x00;
    int                 ReferenceCount = 0x00;
    size_t              Instance = 0x00;

    if((!Id) || (!TableSize)){
        return STATUS_INVALID_PARAMETER;
    }

    if(!strncmp(Id, MULTIPLE_APIC_DESCRIPTION, 4)){
        Instance = AcpiApicInstance;
    }

    AcpiGetTable(Id, Instance, &TableHeader);
    if(!TableHeader){
        LouPrint("Table ID:%h Could Not Be Found\n", *(size_t*)Id);
        return STATUS_NO_SUCH_DEVICE;
    }

    ReferenceCount = LouKeAcpiParseEntriesArray(
        Id, 
        TableSize,
        (PFIRMWARE_TABLE_HEADER)TableHeader,
        0, 
        Processor,
        ProcessorNumber,
        MaxEntries
    );

    AcpiPutTable(TableHeader);

    return ReferenceCount;
}

LOUSTATUS LouKeAcpiTableParseEntries(
    string                      Id, 
    size_t                      TableSize,
    int                         EntryID,
    ACPI_TABLE_ENTRY_HANDLER    Handler,
    size_t                      MaxEntries
){
    return _LouKeAcpiTableParseEntries(Id, TableSize, EntryID, Handler, 0x00, 0x00, MaxEntries);
}