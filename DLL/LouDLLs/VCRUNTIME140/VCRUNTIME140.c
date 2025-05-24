//x86_64-w64-mingw32-gcc -shared -o VCRUNTIME140.dll VCRUNTIME140.c -nostdlib -nodefaultlibs -I../../../Include -L../../../UserLibraries -lLouDll
#include <Annya.h>

static inline size_t GetAlignmentBySize(size_t Size){
    if(Size <= 2)    return 2;
    if(Size <= 4)    return 4;
    if(Size <= 8)    return 8;
    if(Size <= 16)   return 16;
    if(Size <= 32)   return 32;
    if(Size <= 64)   return 64;
    if(Size <= 128)  return 128;
    if(Size <= 256)  return 256;
    if(Size <= 512)  return 512;
    if(Size <= 1024) return 1024;
    if(Size <= 2048) return 2048;
    return 4096;
}


FRAME_INFO FrameInfoChain;
PFRAME_INFO PFrameInfoChain = &FrameInfoChain;

__declspec(dllexport)
BOOL DllMainCRTStartup(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

__declspec(dllexport)
void* memset(
    void* Destination,
    int c,
    size_t count
){
    LouPrint("Memset()\n");
    while(1);
    if(!Destination)return 0x00;

    char* Foo = (char*)Destination;

    for(size_t Index = 0; Index < count; Index++){
        Foo[Index] = (char)c;
    }

    return Destination;
}

__declspec(dllexport)
void* memcpy(
    void* Destination,
    const void* Source,
    size_t count
){
    LouPrint("MemCpy()\n");
    while(1);

    if((!Destination) || (!Source)){
        return 0x00;
    }

    string SourceC = (string)Source;
    string DestinationC = Destination;

    for(size_t Index = 0 ; Index < count; Index++){
        DestinationC[Index] = SourceC[Index];
    }

    return Destination;

}

__declspec(dllexport)
void __std_type_info_destroy_list(
    __type_info_node* const root_node
){
    LouPrint("__std_type_info_destroy_list()\n");
    while(1);
}


__declspec(dllexport)
void __C_specific_handler(
    EXCEPTION_RECORD*       ExceptRec,
    void*                   EtablishFrame,
    void*                   Context,
    DISPATCHER_CONTEXT      DispContext
){
    LouPrint("__C_specific_handler()\n");
    while(1);

}

__declspec(dllexport)
PFRAME_INFO _CreateFrameInfo(
    PFRAME_INFO Frame,
    DISPATCHER_CONTEXT* Dispatch,
    PULONG WETHTI,
    void* Context
){
    while(1);

    return 0x00;
}

__declspec(dllexport)
void _CxxThrowException(
    void* ExceptionObject,
    void* PThrowInfo
){
    LouPrint("_CxxThrowException\n");
    while(1);
}

__declspec(dllexport)
void _FindAndUnlinkFrame(
    PFRAME_INFO Frame
){
    LouPrint("_FindAndUnlinkFrame\n");
    while(1);
}

__declspec(dllexport)
bool _IsExceptionObjectToBeDestroyed(
    void* Object
){
    LouPrint("_IsExceptionObjectToBeDestroyed\n");
    while(1);
    return false;
}

__declspec(dllexport)
void _SetWinRTOutOfMemoryExceptionCallback(
    void* Callback
){
    LouPrint("_SetWinRTOutOfMemoryExceptionCallback\n");
    while(1);
}

__declspec(dllexport)
void* __AdjustPointer(
    void* Object, 
    void* PointerOffset
){
    LouPrint("__AdjustPointer\n");
    while(1);
    return 0x00;
}

__declspec(dllexport)
void __BuildCatchObject(
    void* ExceptionRecord, 
    void* Rn, 
    void* HandlerType, 
    void* CatchableType
){
    LouPrint("__BuildCatchObject\n");
    while(1);
}

#define VCR140_API __declspec(dllexport)

VCR140_API
void __current_exception(){

    LouPrint("__c_current_exception()\n");

    while(1);
}

VCR140_API
void __current_exception_context(){
    LouPrint("__current_exception_context()\n");
    while(1);
}


/*
1800178d0  char __export_name(__BuildCatchObjectHelper)[0x19] = "__BuildCatchObjectHelper", 0
1800178e9  char __export_name(__C_specific_handler)[0x15] = "__C_specific_handler", 0
1800178fe  char __export_name(__C_specific_handler_noexcept)[0x1e] = "__C_specific_handler_noexcept", 0
18001791c  char __export_name(__CxxDetectRethrow)[0x13] = "__CxxDetectRethrow", 0
18001792f  char __export_name(__CxxExceptionFilter)[0x15] = "__CxxExceptionFilter", 0
180017944  char __export_name(__CxxFrameHandler)[0x12] = "__CxxFrameHandler", 0
180017956  char __export_name(__CxxFrameHandler2)[0x13] = "__CxxFrameHandler2", 0
180017969  char __export_name(__CxxFrameHandler3)[0x13] = "__CxxFrameHandler3", 0
18001797c  char __export_name(__CxxQueryExceptionSize)[0x18] = "__CxxQueryExceptionSize", 0
180017994  char __export_name(__CxxRegisterExceptionObject)[0x1d] = "__CxxRegisterExceptionObject", 0
1800179b1  char __export_name(__CxxUnregisterExceptionObject)[0x1f] = "__CxxUnregisterExceptionObject", 0
1800179d0  char __export_name(__DestructExceptionObject)[0x1a] = "__DestructExceptionObject", 0
1800179ea  char __export_name(__FrameUnwindFilter)[0x14] = "__FrameUnwindFilter", 0
1800179fe  char __export_name(__GetPlatformExceptionInfo)[0x1b] = "__GetPlatformExceptionInfo", 0
180017a19  char __export_name(__NLG_Dispatch2)[0x10] = "__NLG_Dispatch2", 0
180017a29  char __export_name(__NLG_Return2)[0xe] = "__NLG_Return2", 0
180017a37  char __export_name(__RTCastToVoid)[0xf] = "__RTCastToVoid", 0
180017a46  char __export_name(__RTDynamicCast)[0x10] = "__RTDynamicCast", 0
180017a56  char __export_name(__RTtypeid)[0xb] = "__RTtypeid", 0
180017a61  char __export_name(__TypeMatch)[0xc] = "__TypeMatch", 0
180017a6d  char __export_name(__current_exception)[0x14] = "__current_exception", 0
180017a81  char __export_name(__current_exception_context)[0x1c] = "__current_exception_context", 0
180017a9d  char __export_name(__intrinsic_setjmp)[0x13] = "__intrinsic_setjmp", 0
180017ab0  char __export_name(__intrinsic_setjmpex)[0x15] = "__intrinsic_setjmpex", 0
180017ac5  char __export_name(__processing_throw)[0x13] = "__processing_throw", 0
180017ad8  char __export_name(__report_gsfailure)[0x13] = "__report_gsfailure", 0
180017aeb  char __export_name(__std_exception_copy)[0x15] = "__std_exception_copy", 0
180017b00  char __export_name(__std_exception_destroy)[0x18] = "__std_exception_destroy", 0
180017b18  char __export_name(__std_terminate)[0x10] = "__std_terminate", 0
180017b28  char __export_name(__std_type_info_compare)[0x18] = "__std_type_info_compare", 0
180017b40  char __export_name(__std_type_info_destroy_list)[0x1d] = "__std_type_info_destroy_list", 0
180017b5d  char __export_name(__std_type_info_hash)[0x15] = "__std_type_info_hash", 0
180017b72  char __export_name(__std_type_info_name)[0x15] = "__std_type_info_name", 0
180017b87  char __export_name(__telemetry_main_invoke_trigger)[0x20] = "__telemetry_main_invoke_trigger", 0
180017ba7  char __export_name(__telemetry_main_return_trigger)[0x20] = "__telemetry_main_return_trigger", 0
180017bc7  char __export_name(__unDName)[0xa] = "__unDName", 0
180017bd1  char __export_name(__unDNameEx)[0xc] = "__unDNameEx", 0
180017bdd  char __export_name(__uncaught_exception)[0x15] = "__uncaught_exception", 0
180017bf2  char __export_name(__uncaught_exceptions)[0x16] = "__uncaught_exceptions", 0
180017c08  char __export_name(__vcrt_GetModuleFileNameW)[0x1a] = "__vcrt_GetModuleFileNameW", 0
180017c22  char __export_name(__vcrt_GetModuleHandleW)[0x18] = "__vcrt_GetModuleHandleW", 0
180017c3a  char __export_name(__vcrt_InitializeCriticalSectionEx)[0x23] = "__vcrt_InitializeCriticalSectionEx", 0
180017c5d  char __export_name(__vcrt_LoadLibraryExW)[0x16] = "__vcrt_LoadLibraryExW", 0
180017c73  char __export_name(_get_purecall_handler)[0x16] = "_get_purecall_handler", 0
180017c89  char __export_name(_get_unexpected)[0x10] = "_get_unexpected", 0
180017c99  char __export_name(_is_exception_typeof)[0x15] = "_is_exception_typeof", 0
180017cae  char __export_name(_local_unwind)[0xe] = "_local_unwind", 0
180017cbc  char __export_name(_purecall)[0xa] = "_purecall", 0
180017cc6  char __export_name(_set_purecall_handler)[0x16] = "_set_purecall_handler", 0
180017cdc  char __export_name(_set_se_translator)[0x13] = "_set_se_translator", 0
180017cef  char __export_name(longjmp)[0x8] = "longjmp", 0
180017cf7  char __export_name(memchr)[0x7] = "memchr", 0
180017cfe  char __export_name(memcmp)[0x7] = "memcmp", 0
180017d0c  char __export_name(memmove)[0x8] = "memmove", 0
180017d1b  char __export_name(set_unexpected)[0xf] = "set_unexpected", 0
180017d2a  char __export_name(strchr)[0x7] = "strchr", 0
180017d31  char __export_name(strrchr)[0x8] = "strrchr", 0
180017d39  char __export_name(strstr)[0x7] = "strstr", 0
180017d40  char __export_name(unexpected)[0xb] = "unexpected", 0
180017d4b  char __export_name(wcschr)[0x7] = "wcschr", 0
180017d52  char __export_name(wcsrchr)[0x8] = "wcsrchr", 0
180017d5a  char __export_name(wcsstr)[0x7] = "wcsstr", 0
*/