#include <Compiler.h>


static PCOMPILER_CONTEXT CreateCompilerContext(
    LOU_STRING Path
){
    FILE* SourceFile = fopen(Path, "rb");
    size_t ReadCount;

    if(!SourceFile){
        printf("Source File Could Not Be Opened\n");
        return (PCOMPILER_CONTEXT)0x00;
    }

    PCOMPILER_CONTEXT NewContext = (PCOMPILER_CONTEXT)malloc(sizeof(COMPILER_CONTEXT));
    memset(NewContext, 0 , sizeof(COMPILER_CONTEXT));

    NewContext->Path = Path;

    if(fseek(SourceFile, 0, SEEK_END)){
        perror("fseek");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    long FileSize = ftell(SourceFile);

    if(FileSize < 0){
        perror("ftell\n");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    NewContext->FileSize = (size_t)FileSize;
    printf("FileSize:%zu\n", NewContext->FileSize);

    rewind(SourceFile);

    NewContext->FileContext = malloc(NewContext->FileSize);

    ReadCount = fread(NewContext->FileContext, 1, NewContext->FileSize, SourceFile);
    if(ReadCount != NewContext->FileSize){
        perror("fread");
        fclose(SourceFile);
        free(NewContext);
        return (PCOMPILER_CONTEXT)0x00;
    }

    fclose(SourceFile);
    return NewContext;
}

static int DestroyCompilerContext(
    PCOMPILER_CONTEXT CompilerContext
){
    memset(CompilerContext->FileContext, 0, CompilerContext->FileSize);
    free(CompilerContext->FileContext);
    memset(CompilerContext, 0 , sizeof(COMPILER_CONTEXT));
    free(CompilerContext);
    return 0;
}

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("Too Many Parameters\n");
        return -1;
    }

    PCOMPILER_CONTEXT NewContext = CreateCompilerContext(argv[1]);
    if(!NewContext){
        printf("Could Not Create New Compiler Context\n");
        return -1;
    }
        


    return DestroyCompilerContext(NewContext);
}