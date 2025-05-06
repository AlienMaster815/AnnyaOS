#include <LouDDK.h>

uint32_t GetNtEmualationBuild();

static uint64_t NtKernelGlobalCsdVersionMaxLength = 0;
static UNICODE_STRING NtKernelGlobalCsdVersion = {0};

void NtTransitionLayerInitCsdVersion(PUNICODE_STRING CsdVersion){
    RtlCopyUnicodeString(&NtKernelGlobalCsdVersion, CsdVersion);
    NtKernelGlobalCsdVersionMaxLength = CsdVersion->MaximumLength;
}

LOUDDK_API_ENTRY
bool
PsGetVersion(
    PULONG              MajorVersion, 
    PULONG              MinorVersion, 
    PULONG              BuildNumber,
    PUNICODE_STRING     CsdVersion
){
    if(MajorVersion){
        *MajorVersion = 5;
    }
    if(MinorVersion){
        *MinorVersion = 2;
    }
    if(BuildNumber){
        *BuildNumber = (GetNtEmualationBuild() & 0x3FFF);
    }
    if(CsdVersion){
        CsdVersion->Length          = NtKernelGlobalCsdVersionMaxLength;
        CsdVersion->MaximumLength   = NtKernelGlobalCsdVersionMaxLength;
    }
    return ((GetNtEmualationBuild() & 0xF0000000) == 0xc0000000);
}