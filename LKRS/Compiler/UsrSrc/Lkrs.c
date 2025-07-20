#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#define _USER_MODE_COMPILER_
#include <Lkrs.h>

static void LkrsDeInit(PKERNEL_REGISTRY_SOURCE_HANDLE Handle){
    PLKRS_NAMESPACE_NODE LastGlbNameSpaceNode = &Handle->NameNodes;
    PLKRS_NAMESPACE_NODE GlbNameSpaceNode;

    if(Handle->CompiledData){
        free(Handle->CompiledData);
    }
    
    if(Handle->NameNodes.NextNode){
        GlbNameSpaceNode = &Handle->NameNodes;
        while(GlbNameSpaceNode){
            LastGlbNameSpaceNode = GlbNameSpaceNode;
            GlbNameSpaceNode = GlbNameSpaceNode->NextNode;
            if(LastGlbNameSpaceNode != &Handle->NameNodes){
                free(LastGlbNameSpaceNode);
            }
        }
    }
    if(Handle->KrfData){
        free(Handle->KrfData);
    }
    if(Handle->Krf){
        fclose(Handle->Krf);
    }
}

static int LkrsGetRawData(PKERNEL_REGISTRY_SOURCE_HANDLE Handle){
    Handle->KrfData = malloc(Handle->KrfSize);
    if(!Handle->KrfData){
        printf("LkrsGetRawData:ERROR: Unable To Allocate Buffer\n");
        return 1;
    }
    size_t bytesRead = fread(Handle->KrfData, 1, Handle->KrfSize, Handle->Krf);
    if(bytesRead != Handle->KrfSize){
        printf("LkrsGetRawData:ERROR: Buffer Was Not Populated Correctly\n");
        return 1;
    }

    return 0;
}

static int LkrsOpenKernelSourceFile(PKERNEL_REGISTRY_SOURCE_HANDLE Handle, char* FileName){
    Handle->Krf = fopen(FileName, "rb"); 


    if (!Handle->Krf) {
        perror("Error opening file");
        return 1;
    }

    fseek(Handle->Krf, 0, SEEK_END);
    long FileSize = ftell(Handle->Krf);
    rewind(Handle->Krf);

    Handle->KrfSize = (size_t)FileSize;
    return 0;
}



int main(int argc, char *argv[]) {
    int Status = 0x00;
    KERNEL_REGISTRY_SOURCE_HANDLE SourceHandle = {0};
  
    if(argc != 2){
        printf("LkrsUser::ERROR: Invalid Parameter\n");
        return 1;
    }
    printf("LkrsUser Creating KRF From:%s.\n", argv[1]);
    Status = LkrsOpenKernelSourceFile(&SourceHandle, argv[1]);
    if(Status){
        printf("LkrsUser::ERROR: Unable To Open KRS File:%s\n", argv[1]);
        LkrsDeInit(&SourceHandle);
        return 1;
    }

    Status = LkrsGetRawData(&SourceHandle);
    if(Status){
        printf("LkrsUser::ERROR: Unable To Get Raw Data For KRS File:%s\n", argv[1]);
        LkrsDeInit(&SourceHandle);
        return 1;
    }

    Status = LkrsCompileSourceFile(&SourceHandle);
    if(Status){
        printf("LkrsUser::ERROR: Unable To Compile Source For KRS File:%s\n", argv[1]);
        LkrsDeInit(&SourceHandle);
        return 1;
    }

    uint8_t* CompiledData = SourceHandle.CompiledData;
    size_t CompiledSize   = SourceHandle.CompiledSize;
    char* FileName = malloc(strlen(argv[1]));
    size_t ApendIndex = strlen(argv[1]) - strlen(".KRS");
    strncpy(FileName, argv[1], strlen(argv[1]) - strlen(".KRS"));
    strncpy(&FileName[ApendIndex], ".KRF", strlen(".KRS"));
    ApendIndex = 0;
    for(; ApendIndex < strlen(FileName); ApendIndex++){
        FileName[ApendIndex] = toupper(FileName[ApendIndex]);
    }
    printf("Compiling to new File:%s\n", FileName);
    FILE* OutFile = fopen(FileName, "wb");
    if (!OutFile) {
        printf("Failed to open output file");
        free(FileName);
        return 1;
    }

    size_t written = fwrite(CompiledData, 1, CompiledSize, OutFile);
    if (written != CompiledSize) {
        printf("Failed to write all data");
        fclose(OutFile);
        free(FileName);
        return 1;
    }

    fclose(OutFile);
    free(FileName);

    LkrsDeInit(&SourceHandle);
    return 0;
}