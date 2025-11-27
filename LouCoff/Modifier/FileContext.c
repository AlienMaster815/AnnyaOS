#include <Modifier.h>

LOUSTATUS FileContextOpenFile(
    PFILE_CONTEXT FileContext
){
    if(!FileContext->FilePath){
        printf("ERROR::Invalid File Path\n");
        return STATUS_INVALID_PARAMETER;
    }
    FILE* File = fopen(FileContext->FilePath, "rb");
    if(!File){
        printf("ERROR::No Such File\n");
        return STATUS_NO_SUCH_FILE;
    }

    if(fseek(File, 0, SEEK_END)){
        perror("fseek");
        fclose(File);
        printf("ERROR::Unable To Parse File\n");
        return STATUS_UNSUCCESSFUL;
    }

    long FileSize = ftell(File);

    if(FileSize < 0){
        perror("ftell\n");
        fclose(File);
        printf("ERROR::Unable To Find File Size\n");
        return STATUS_UNSUCCESSFUL;
    }

    FileContext->FileSize = (size_t)FileSize;

    rewind(File);

    FileContext->FileContext = LouKeMallocEx(FileContext->FileSize, SECTION_ALIGNMENT, KERNEL_GENERIC_MEMORY);

    size_t ReadCount;

    ReadCount = fread(FileContext->FileContext, 1, FileContext->FileSize, File);
    if(ReadCount != FileContext->FileSize){
        perror("fread");
        fclose(File);
        free(FileContext);
        printf("ERROR::Could Not Gather File Data\n");
        return STATUS_UNSUCCESSFUL;
    }

    fclose(File);
    return STATUS_SUCCESS;
}

void FileContextCloseFile(
    PFILE_CONTEXT   FileContext
){
    if(FileContext->FileContext){
        FILE* File = fopen(FileContext->FilePath,"wb"); 
        fwrite(FileContext->FileContext, 1, FileContext->FileSize, File);
        fclose(File);
        LouKeFree(FileContext->FileContext);
    }else {
        printf("ERROR::No Such File To Close\n");
    }
}