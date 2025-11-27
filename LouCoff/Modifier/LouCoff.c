#include <Modifier.h>

static bool IsPeFileCoff(PFILE_CONTEXT CoffFile){
    PVOID FileData = CoffFile->FileContext;

    PCOFF_IMAGE_HEADER CoffHeader = CoffGetImageHeader(FileData);

    if(memcmp(&CoffHeader->StandardHeader.PeSignature, COFF_PE_SIGNATURE, 4)){
        return false;
    }

    return true;
}

static void SetLouCoffSignature(PFILE_CONTEXT CoffFile){
    PVOID FileData = CoffFile->FileContext;
    PCOFF_IMAGE_HEADER CoffHeader = CoffGetImageHeader(FileData);
    memcpy((PVOID)(UINT8*)&CoffHeader->StandardHeader.PeSignature, (PVOID)(UINT8*)CFI_HEADER_LOUCOFF_SIGNATURE, 4);
}

static void _SetLouCoffSubsystem(UINT16* Subsystem, bool KernelObject){
    *Subsystem = (KernelObject ? CFI_SUBSYSTEM_LOUSINE_KERNEL_OBJECT : CFI_SUBSYSTEM_LOUSINE_USER_OBJECT);
}


static void SetLouCoffSubsystem(PFILE_CONTEXT CoffFile, bool KernelObject){
    PVOID FileData = CoffFile->FileContext;
    PCOFF_IMAGE_HEADER CoffHeader = CoffGetImageHeader(FileData);

    if(CoffHeader->OptionalHeader.PE64.Magic == CFI_OPTIONAL_HEADER_PE3264_MAGIC){
        _SetLouCoffSubsystem(&CoffHeader->OptionalHeader.PE64.Subsystem, KernelObject);
    }else if(CoffHeader->OptionalHeader.PE32.Magic == CFI_OPTIONAL_HEADER_PE32_MAGIC){
        _SetLouCoffSubsystem(&CoffHeader->OptionalHeader.PE32.Subsystem, KernelObject);
    }else{
        printf("ERROR:Coff Version Not Recognized\n");
    }
}

LOUSTATUS 
MakeCoffModifications(
    PLOUCOFF_MODIFIER_CONTEXT Context
){
    LOUSTATUS Status;
    
    Status = FileContextOpenFile(&Context->CoffFile);
    if(Status != STATUS_SUCCESS){
        printf("ERROR:Unable To Open Coff File\n");
        return Status;
    }
    

    if(!IsPeFileCoff(&Context->CoffFile)){
        printf("ERROR:File Is Not Coff File\n");
        FileContextCloseFile(&Context->CoffFile);
        return STATUS_INVALID_PARAMETER;
    }

    SetLouCoffSignature(&Context->CoffFile);

    SetLouCoffSubsystem(&Context->CoffFile, Context->KernelObject);

    FileContextCloseFile(&Context->CoffFile);

    return STATUS_SUCCESS;
}