#include <Modifier.h>

static const string ValidModifiers[] = {
    MODIFIER_PARAMETER_MODIFIER,
    MODIFIER_PARAMETER_EXECUTABLE,
    MODIFIER_PARAMETER_SOURCE,
    MODIFIER_PARAMETER_PRIVLEDGE,
    0
};



static bool IsModifierValid(
    PLOUCOFF_MODIFIER_CONTEXT   Context,
    string                      Modifier
){
    size_t i = 0;
    while(ValidModifiers[i]){
        if(!strncmp(Modifier, ValidModifiers[i], 2)){
            if(!strcmp(ValidModifiers[i], MODIFIER_PARAMETER_EXECUTABLE)){
                Context->CoffFile.FilePath = &Modifier[strlen(MODIFIER_PARAMETER_EXECUTABLE)];
            }else if(!strcmp(ValidModifiers[i], MODIFIER_PARAMETER_SOURCE)){
                Context->SourceFile.FilePath = &Modifier[strlen(MODIFIER_PARAMETER_SOURCE)];
            }else if(!strcmp(ValidModifiers[i], MODIFIER_PARAMETER_PRIVLEDGE)){
                string ModifierValue = &Modifier[strlen(MODIFIER_PARAMETER_PRIVLEDGE)];
                StrToLower(ModifierValue);
                if(!strcmp(ModifierValue, "kernel")){
                    Context->KernelObject = true;
                }else if(!strcmp(ModifierValue, "user")){
                    Context->KernelObject = false;
                }else{
                    printf("ERROR:Invalid Privledge:%s\n", Modifier);
                    return false;
                }
            }
            return true;
        }
        i++;
    }
    printf("ERROR::Invalid parameter:%s\n", Modifier);
    return false;
}

static LOUSTATUS ModifierParseInput(
    PLOUCOFF_MODIFIER_CONTEXT   Context,
    char*                       ArgStrings[],
    int                         ArgCount
){
    Context->KernelObject = false;//this will be set in the modifier valid function
    Context->Arguments = LouKeMallocArray(string, ArgCount, KERNEL_GENERIC_MEMORY);
    Context->ArgumentCount = ArgCount;
    for(int i = 0 ; i < ArgCount; i++){
        Context->Arguments[i] = ArgStrings[i];
        if(!IsModifierValid(Context, Context->Arguments[i])){
            return STATUS_UNSUCCESSFUL;
        }
    }
    return STATUS_SUCCESS;
}

static void DestroyModifierCOntext(
    PLOUCOFF_MODIFIER_CONTEXT Context
){

    if(Context->Arguments){
        LouKeFree(Context->Arguments);
    }
}

int main(int Argc, char *Argv[]){
    LOUCOFF_MODIFIER_CONTEXT CompilerContext;
    LOUSTATUS Status;
    Status = ModifierParseInput(
        &CompilerContext,
        Argv,
        Argc
    );
    if(Status != STATUS_SUCCESS){
        DestroyModifierCOntext(
            &CompilerContext
        );
        return -1;
    }



    Status = MakeCoffModifications(&CompilerContext);
    if(Status != STATUS_SUCCESS){
        printf("Error Making Modifications\n");
    }

    DestroyModifierCOntext(
        &CompilerContext
    );
    return 0;
}