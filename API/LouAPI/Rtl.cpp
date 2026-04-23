//Copyright GPL-2 Tyler Grenier (2026)
#include <LouDDK.h>

#define ASCII_CHAR_IS_DECIMAL       (0)
#define ASCII_CHAR_IS_CHARECTER     (1)
#define ASCII_CHAR_IS_CONTROL_CHAR  (2)
#define ASCII_CHAR_IS_OTHER         (3)
#define ASCII_CHAR_IDENTITY_MASK    0x03
#define ASCII_MAX_VALUE             127
#define ASCII_SPECIAL_CHARECTER     (1 << 3)

UNUSED static const UCHAR AsciiMap[] = {
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //NULL  
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SOH   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //STX   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //ETX   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //EOT   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //ENQ   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //ACK   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //BEL   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //BS    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //HT    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //LF    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //VT    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //FF      
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //CR    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SO    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SI    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DLE   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DC1   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DC2   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DC3   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DC4   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //NAK   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SYN   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //ETB   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //CAN   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //EM    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SUB   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //ESC   
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //FS    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //GS    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //RS    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //US    
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //SP    
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //!     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //"     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //#     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //$     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //%     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //&     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //'     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //(     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //)     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //*     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //+     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //,     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //-     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //.     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //slash 
    ASCII_CHAR_IS_DECIMAL,                                      //0     
    ASCII_CHAR_IS_DECIMAL,                                      //1     
    ASCII_CHAR_IS_DECIMAL,                                      //2        
    ASCII_CHAR_IS_DECIMAL,                                      //3     
    ASCII_CHAR_IS_DECIMAL,                                      //4     
    ASCII_CHAR_IS_DECIMAL,                                      //5     
    ASCII_CHAR_IS_DECIMAL,                                      //6     
    ASCII_CHAR_IS_DECIMAL,                                      //7     
    ASCII_CHAR_IS_DECIMAL,                                      //8     
    ASCII_CHAR_IS_DECIMAL,                                      //9     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //:     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //;     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //<     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //=     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //>     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //?     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //@     
    ASCII_CHAR_IS_CHARECTER,                                    //A     
    ASCII_CHAR_IS_CHARECTER,                                    //B     
    ASCII_CHAR_IS_CHARECTER,                                    //C     
    ASCII_CHAR_IS_CHARECTER,                                    //D     
    ASCII_CHAR_IS_CHARECTER,                                    //E     
    ASCII_CHAR_IS_CHARECTER,                                    //F     
    ASCII_CHAR_IS_CHARECTER,                                    //G     
    ASCII_CHAR_IS_CHARECTER,                                    //H     
    ASCII_CHAR_IS_CHARECTER,                                    //I     
    ASCII_CHAR_IS_CHARECTER,                                    //J     
    ASCII_CHAR_IS_CHARECTER,                                    //K     
    ASCII_CHAR_IS_CHARECTER,                                    //L     
    ASCII_CHAR_IS_CHARECTER,                                    //M     
    ASCII_CHAR_IS_CHARECTER,                                    //N     
    ASCII_CHAR_IS_CHARECTER,                                    //O     
    ASCII_CHAR_IS_CHARECTER,                                    //P     
    ASCII_CHAR_IS_CHARECTER,                                    //Q     
    ASCII_CHAR_IS_CHARECTER,                                    //R     
    ASCII_CHAR_IS_CHARECTER,                                    //S     
    ASCII_CHAR_IS_CHARECTER,                                    //T     
    ASCII_CHAR_IS_CHARECTER,                                    //U     
    ASCII_CHAR_IS_CHARECTER,                                    //V     
    ASCII_CHAR_IS_CHARECTER,                                    //W     
    ASCII_CHAR_IS_CHARECTER,                                    //X     
    ASCII_CHAR_IS_CHARECTER,                                    //Y     
    ASCII_CHAR_IS_CHARECTER,                                    //Z     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //[     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //Backslash     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //]     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //^     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //_     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //`     
    ASCII_CHAR_IS_CHARECTER,                                    //A Low 
    ASCII_CHAR_IS_CHARECTER,                                    //B Low 
    ASCII_CHAR_IS_CHARECTER,                                    //C Low 
    ASCII_CHAR_IS_CHARECTER,                                    //D Low 
    ASCII_CHAR_IS_CHARECTER,                                    //E Low 
    ASCII_CHAR_IS_CHARECTER,                                    //F Low 
    ASCII_CHAR_IS_CHARECTER,                                    //G Low 
    ASCII_CHAR_IS_CHARECTER,                                    //H Low 
    ASCII_CHAR_IS_CHARECTER,                                    //I Low 
    ASCII_CHAR_IS_CHARECTER,                                    //J Low 
    ASCII_CHAR_IS_CHARECTER,                                    //K Low 
    ASCII_CHAR_IS_CHARECTER,                                    //L Low 
    ASCII_CHAR_IS_CHARECTER,                                    //M Low 
    ASCII_CHAR_IS_CHARECTER,                                    //N Low 
    ASCII_CHAR_IS_CHARECTER,                                    //O Low 
    ASCII_CHAR_IS_CHARECTER,                                    //P Low 
    ASCII_CHAR_IS_CHARECTER,                                    //Q Low 
    ASCII_CHAR_IS_CHARECTER,                                    //R Low 
    ASCII_CHAR_IS_CHARECTER,                                    //S Low 
    ASCII_CHAR_IS_CHARECTER,                                    //T Low 
    ASCII_CHAR_IS_CHARECTER,                                    //U Low 
    ASCII_CHAR_IS_CHARECTER,                                    //V Low 
    ASCII_CHAR_IS_CHARECTER,                                    //W Low 
    ASCII_CHAR_IS_CHARECTER,                                    //X Low 
    ASCII_CHAR_IS_CHARECTER,                                    //Y Low 
    ASCII_CHAR_IS_CHARECTER,                                    //Z Low 
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //{     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //|     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //}     
    ASCII_CHAR_IS_CHARECTER | ASCII_SPECIAL_CHARECTER,          //~     
    ASCII_CHAR_IS_CONTROL_CHAR,                                 //DEL     
};


static
BOOLEAN 
IsAsciiDecimal(UCHAR Char){
    if(Char > ASCII_MAX_VALUE){
        return false;
    }
    return ((AsciiMap[Char] & ASCII_CHAR_IDENTITY_MASK) == ASCII_CHAR_IS_DECIMAL);
}

static 
SIZE 
AsciiDecimalToDecimal(CHAR Char){
    return (SIZE)(Char - '0');
}

static 
BOOLEAN 
IsAsciiHex(
    UCHAR Char
){
    if(IsAsciiDecimal(Char)){
        return true;
    }
    CHAR Foo = (CHAR)Char;
    return (((Foo <= 'F') && (Foo >= 'A')) || ((Foo <= 'f') && (Foo >= 'a')));
}

static 
SIZE 
AsciiHexToDecimal(CHAR Hex){
    if(IsAsciiDecimal((UCHAR)Hex)){
        return AsciiDecimalToDecimal(Hex);
    }
    if((Hex <= 'F') && (Hex >= 'A')){
        return (SIZE)(Hex - 'A') + 10;
    }else if((Hex <= 'f') && (Hex >= 'a')){
        return (SIZE)(Hex - 'a') + 10;
    } 
    LouPrint("LOUOSKRNL.EXE:AsciiHexToDecimal()BUGBUG\n");
    return 0x00;
}

static 
BOOLEAN 
Uint64AdditionWillOverflow(
    UINT64 A,
    UINT64 B
){
    return (A > UINT64_MAX - B);
}

static
BOOLEAN 
Uint64MultiplicationWillOverflow(
    UINT64 A,
    UINT64 B
){
    return ((B != 0) && (A > UINT64_MAX / B));
}


static 
BOOLEAN 
Uint32AdditionWillOverflow(
    UINT64 A,
    UINT64 B
){
    return (A > UINT32_MAX - B);
}

static
BOOLEAN 
Uint32MultiplicationWillOverflow(
    UINT64 A,
    UINT64 B
){
    return ((B != 0) && (A > UINT32_MAX / B));
}

KERNEL_EXPORT
LOUSTATUS
LouKeRtlCharToUint64(    
    PCSZ    String, 
    ULONG   Base, 
    UINT64* Value
){
    if((!Value) || (!String)){
        return STATUS_INVALID_PARAMETER;
    }
    SIZE Multiple = 1;
    SIZE Result = 0x00;
    SIZE Adder;
    BOOLEAN Negative = (*String == '-');
    if(Negative){
        String++;
    }

    int Index = strlen(String);
    *Value = 0x00;

    if((strncmp(String, "0x", 2)) || (strncmp(String, "0X", 2))){
        if((Base) && (Base != 16)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 16;
    }else if((strncmp(String, "0o", 2)) || (strncmp(String, "0O", 2))){
        if((Base) && (Base != 8)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 8;
    }else if((strncmp(String, "0b", 2)) || (strncmp(String, "0B", 2))){
        if((Base) && (Base != 2)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 2;
    }else if(!Base){
        Base = 10;
    }

    for(int i = (Index - 1); i >= 0; i--){
        if(Base == 10){
            if(!IsAsciiDecimal((UCHAR)String[i])){
                return STATUS_INVALID_PARAMETER;
            }
            Adder = AsciiDecimalToDecimal(String[i]);
        }else if(Base == 16){
            if(!IsAsciiHex(String[i])){
                return STATUS_INVALID_PARAMETER;
            }
            Adder = AsciiHexToDecimal(String[i]);
        }else{
            return STATUS_INVALID_PARAMETER;
        }

        if(i > 0){
            if(
                (Uint64MultiplicationWillOverflow(Adder, Multiple)) || 
                (Uint64MultiplicationWillOverflow(Multiple, Base)) || 
                (Uint64AdditionWillOverflow(Result, Adder * Multiple))
            ){
                return STATUS_INVALID_PARAMETER;
            }
            Result += Adder * Multiple;
            Multiple *= Base;
        }
    }
    if((Negative) && (Result > INT64_MAX)){
        return STATUS_INVALID_PARAMETER;
    }else if(Negative){
        Result = -Result;
    }
    *Value = Result;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT
LOUSTATUS
LouKeRtlCharToUint32(    
    PCSZ    String, 
    ULONG   Base, 
    UINT32* Value
){
if((!Value) || (!String)){
        return STATUS_INVALID_PARAMETER;
    }
    UINT32 Multiple = 1;
    UINT32 Result = 0x00;
    UINT32 Adder;
    BOOLEAN Negative = (*String == '-');
    if(Negative){
        String++;
    }

    int Index = strlen(String);
    *Value = 0x00;

    if((strncmp(String, "0x", 2)) || (strncmp(String, "0X", 2))){
        if((Base) && (Base != 16)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 16;
    }else if((strncmp(String, "0o", 2)) || (strncmp(String, "0O", 2))){
        if((Base) && (Base != 8)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 8;
    }else if((strncmp(String, "0b", 2)) || (strncmp(String, "0B", 2))){
        if((Base) && (Base != 2)){
            return STATUS_INVALID_PARAMETER;
        }
        Base = 2;
    }else if(!Base){
        Base = 10;
    }

    for(int i = (Index - 1); i >= 0; i--){
        if(Base == 10){
            if(!IsAsciiDecimal((UCHAR)String[i])){
                return STATUS_INVALID_PARAMETER;
            }
            Adder = AsciiDecimalToDecimal(String[i]);
        }else if(Base == 16){
            if(!IsAsciiHex(String[i])){
                return STATUS_INVALID_PARAMETER;
            }
            Adder = AsciiHexToDecimal(String[i]);
        }else{
            return STATUS_INVALID_PARAMETER;
        }

        if(i > 0){
            if(
                (Uint32MultiplicationWillOverflow(Adder, Multiple)) || 
                (Uint32MultiplicationWillOverflow(Multiple, Base)) || 
                (Uint32AdditionWillOverflow(Result, Adder * Multiple))
            ){
                return STATUS_INVALID_PARAMETER;
            }
            Result += Adder * Multiple;
            Multiple *= Base;
        }
    }
    if((Negative) && (Result > INT64_MAX)){
        return STATUS_INVALID_PARAMETER;
    }else if(Negative){
        Result = -Result;
    }
    *Value = Result;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlCharToInteger(
    PCSZ    String, 
    ULONG   Base, 
    PULONG  Value
){  
    UINT32 Tmp = 0x00;
    LOUSTATUS Status = LouKeRtlCharToUint32(
        String,
        Base,
        &Tmp
    );
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    *Value = (ULONG)Tmp;
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LONG 
LouKeRtlCompareString(
    const STRING*   String1, 
    const STRING*   String2,
    BOOLEAN         CaseInSensitive
){

    LouPrint("LouKeRtlCompareString()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
VOID 
LouKeRtlCopyString(
    PSTRING         DestinationString, 
    const STRING*   SourceString
){

    LouPrint("LouKeRtlCopyString()\n");
    while(1);

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlEqualString(
    const STRING*   String1, 
    const STRING*   String2, 
    BOOLEAN         CaseInSensitive
){

    LouPrint("LouKeRtlEqualString()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
ULONG64 
LouKeRtlGetEnabledExtendedFeatures(
    ULONG64 FeatureMask
){

    LouPrint("LouKeRtlGetEnabledExtendedFeatures()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlGetPersistedStateLocation(
    PCWSTR                  SourceID, 
    PCWSTR                  CustomValue, 
    PCWSTR                  DefaultPath, 
    STATE_LOCATION_TYPE     StateLocationType, 
    PWCHAR                  TargetPath, 
    ULONG                   BufferLengthIn, 
    PULONG                  BufferLengthOut
){

    LouPrint("LouKeRtlGetPersistedStateLocation()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIncrementCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector
){

    LouPrint("LouKeRtlIncrementCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInitializeCorrelationVector(
    PCORRELATION_VECTOR CorrelationVector, 
    int                 Version, 
    const GUID*         Guid
){

    LouPrint("LouKeRtlInitializeCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlIsStateSeparationEnabled(){

    LouPrint("LouKeRtlIsStateSeparationEnabled()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlIsZeroMemory(
    PVOID   Buffer, 
    SIZE_T  Length
){

    LouPrint("LouKeRtlIsZeroMemory()\n");
    while(1);
    return false;
    
}

KERNEL_EXPORT 
VOID 
LouKeRtlMapGenericMask(
    PACCESS_MASK            AccessMask, 
    const GENERIC_MAPPING*  GenericMapping
){

    LouPrint("LouKeRtlMapGenericMask()\n");
    while(1);

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlNormalizeSecurityDescriptor(
    PSECURITY_DESCRIPTOR*   SecurityDescriptor, 
    ULONG                   SecurityDescriptorLength, 
    PSECURITY_DESCRIPTOR*   NewSecurityDescriptor, 
    PULONG                  NewSecurityDescriptorLength, 
    BOOLEAN CheckOnly
){

    LouPrint("LouKeRtlNormalizeSecurityDescriptor()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
BOOLEAN 
LouKeRtlPrefixUnicodeString(
    PCUNICODE_STRING    String1, 
    PCUNICODE_STRING    String2, 
    BOOLEAN             CaseInSensitive
){

    LouPrint("LouKeRtlPrefixUnicodeString()\n");
    while(1);
    return false;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlQueryRegistryValueWithFallback(
    HANDLE          PrimaryHandle, 
    HANDLE          FallbackHandle, 
    PUNICODE_STRING ValueName, 
    ULONG           ValueLength, 
    PULONG          ValueType, 
    PVOID           ValueData, 
    PULONG          ResultLength
){

    LouPrint("LouKeRtlQueryRegistryValueWithFallback()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlRaiseCustomSystemEventTrigger(
    PCUSTOM_SYSTEM_EVENT_TRIGGER_CONFIG TriggerConfig
){

    LouPrint("LouKeRtlRaiseCustomSystemEventTrigger()\n");
    while(1);
    return STATUS_SUCCESS;
    
}

KERNEL_EXPORT 
VOID 
LouKeRtlRunOnceInitialize(
    PRTL_RUN_ONCE RunOnce
){

    LouPrint("LouKeRtlRunOnceInitialize()\n");
    while(1);

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUpcaseUnicodeString(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    BOOLEAN             AllocateDestinationString
){

    LouPrint("LouKeRtlUpcaseUnicodeString()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
CHAR 
LouKeRtlUpperChar(
    CHAR Character
){

    LouPrint("LouKeRtlUpperChar()\n");
    while(1);
    return 0x00;

}

KERNEL_EXPORT 
VOID 
LouKeRtlUpperString(
    PSTRING DestinationString, 
    const STRING* SourceString
){

    LouPrint("LouKeRtlUpperString()\n");
    while(1);

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlValidateCorrelationVector(
    PCORRELATION_VECTOR Vector
){

    LouPrint("LouKeRtlValidateCorrelationVector()\n");
    while(1);
    return STATUS_SUCCESS;

}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlVolumeDeviceToDosName(
    PVOID           VolumeDeviceObject, 
    PUNICODE_STRING DosName
){

    LouPrint("LouKeRtlVolumeDeviceToDosName()\n");
    while(1);
    return STATUS_SUCCESS;

}


KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInitStringEx(
    PSTRING DestinationString, 
    PCSZ SourceString
){
    LouPrint("LouKeRtlInitStringEx()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUTF8ToUnicodeN(
    PWSTR UnicodeStringDestination, 
    ULONG UnicodeStringMaxByteCount, 
    PULONG UnicodeStringActualByteCount, 
    PCCH UTF8StringSource, 
    ULONG UTF8StringByteCount
){
    LouPrint("LouKeRtlUTF8ToUnicodeN()\n");
    while(1);
    return STATUS_SUCCESS;
}


KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlByteToChar(
    BYTE bOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlByteToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlByteToInt8(
    BYTE bOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlByteToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlDWordPtrAdd(
    DWORD_PTR dwAugend, 
    DWORD_PTR dwAddend, 
    DWORD_PTR* pdwResult
){
    LouPrint("LouKeRtlDWordPtrAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlDWordPtrMult(
    DWORD_PTR dwMultiplicand, 
    DWORD_PTR dwMultiplier, 
    DWORD_PTR* pdwResult
){
    LouPrint("LouKeRtlDWordPtrMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlDWordPtrSub(
    DWORD_PTR dwMinuend, 
    DWORD_PTR dwSubtrahend, 
    DWORD_PTR* pdwResult
){
    LouPrint("LouKeRtlDWordPtrSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8Add(
    INT8 i8Augend, 
    INT8 i8Addend, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlInt8Add()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8Mult(
    INT8 i8Multiplicand, 
    INT8 i8Multiplier, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlInt8Mult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8Sub(
    INT8 i8Minuend, 
    INT8 i8Subtrahend, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlInt8Sub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToUChar(
    INT8 i8Operand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlInt8ToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToUInt(
    INT8 i8Operand, 
    UINT* puResult
){
    LouPrint("LouKeRtlInt8ToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToUInt8(
    INT8 i8Operand, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlInt8ToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToUIntPtr(
    INT8 i8Operand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlInt8ToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToULong(
    INT8 i8Operand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlInt8ToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToULongLong(
    INT8 i8Operand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlInt8ToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToULongPtr(
    INT8 i8Operand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlInt8ToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlInt8ToUShort(
    INT8 i8Operand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlInt8ToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntAdd(
    INT iAugend, 
    INT iAddend, 
    INT* piResult
){
    LouPrint("LouKeRtlIntAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntMult(
    INT iMultiplicand, 
    INT iMultiplier, 
    INT* piResult
){
    LouPrint("LouKeRtlIntMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrAdd(
    INT_PTR iAugend, 
    INT_PTR iAddend, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlIntPtrAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrMult(
    INT_PTR iMultiplicand, 
    INT_PTR iMultiplier, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlIntPtrMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrSub(
    INT_PTR iMinuend, 
    INT_PTR iSubtrahend, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlIntPtrSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToChar(
    INT_PTR iOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlIntPtrToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToInt8(
    INT_PTR iOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlIntPtrToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToLong(
    INT_PTR iOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlIntPtrToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToLongPtr(
    INT_PTR iOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlIntPtrToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToShort(
    INT_PTR iOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlIntPtrToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToUChar(
    INT_PTR iOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlIntPtrToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToUInt(
    INT_PTR iOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlIntPtrToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToUInt8(
    INT_PTR iOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlIntPtrToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToUIntPtr(
    INT_PTR iOperand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlIntPtrToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToULong(
    INT_PTR iOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlIntPtrToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToULongLong(
    INT_PTR iOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlIntPtrToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToULongPtr(
    INT_PTR iOperand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlIntPtrToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntPtrToUShort(
    INT_PTR iOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlIntPtrToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntSub(
    INT iMinuend, 
    INT iSubtrahend,
    INT* piResult
){
    LouPrint("LouKeRtlIntSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToChar(
    INT iOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlIntToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToInt8(
    INT iOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlIntToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToShort(
    INT iOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlIntToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToUChar(
    INT iOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlIntToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToUInt(
    INT iOperand,
    UINT* puResult
){
    LouPrint("LouKeRtlIntToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToUInt8(
    INT iOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlIntToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToULong(
    INT iOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlIntToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToULongLong(
    INT iOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlIntToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlIntToUShort(
    INT iOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlIntToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongAdd(
    LONG lAugend, 
    LONG lAddend, 
    LONG* plResult
){
    LouPrint("LouKeRtlLongAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongAdd(
    LONGLONG llAugend, 
    LONGLONG llAddend, 
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlLongLongAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongMult(
    LONGLONG llMultiplicand, 
    LONGLONG llMultiplier,
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlLongLongMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongSub(
    LONGLONG llMinuend, 
    LONGLONG llSubtrahend, 
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlLongLongSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToChar(
    LONGLONG llOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlLongLongToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToInt(
    LONGLONG llOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlLongLongToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToInt8(
    LONGLONG llOperand, INT8* pi8Result){
    LouPrint("LouKeRtlLongLongToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToIntPtr(
    LONGLONG llOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlLongLongToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToLong(
    LONGLONG llOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlLongLongToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToLongPtr(
    LONGLONG llOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlLongLongToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToShort(
    LONGLONG llOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlLongLongToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToUChar(
    LONGLONG llOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlLongLongToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToUInt(
    LONGLONG llOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlLongLongToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToUInt8(
    LONGLONG llOperand, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlLongLongToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToULong(
    LONGLONG llOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlLongLongToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToULongLong(
    LONGLONG llOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlLongLongToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongLongToUShort(
    LONGLONG llOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlLongLongToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongMult(
    LONG lMultiplicand, 
    LONG lMultiplier, 
    LONG *plResult
){
    LouPrint("LouKeRtlLongMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrAdd(
    LONG_PTR lAugend, 
    LONG_PTR lAddend, 
    LONG_PTR *plResult
){
    LouPrint("LouKeRtlLongPtrAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrMult(
    LONG_PTR lMultiplicand, 
    LONG_PTR lMultiplier, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlLongPtrMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrSub(
    LONG_PTR lMinuend, 
    LONG_PTR lSubtrahend, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlLongPtrSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToChar(
    LONG_PTR lOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlLongPtrToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToInt(
    LONG_PTR lOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlLongPtrToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToInt8(
    LONG_PTR lOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlLongPtrToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToIntPtr(
    LONG_PTR lOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlLongPtrToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToLong(
    LONG_PTR lOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlLongPtrToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToShort(
    LONG_PTR lOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlLongPtrToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToUChar(
    LONG_PTR lOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlLongPtrToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToUInt(
    LONG_PTR lOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlLongPtrToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToUInt8(
    LONG_PTR lOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlLongPtrToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToUIntPtr(
    LONG_PTR lOperand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlLongPtrToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToULong(
    LONG_PTR lOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlLongPtrToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToULongLong(
    LONG_PTR  lOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlLongPtrToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToULongPtr(
    LONG_PTR lOperand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlLongPtrToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongPtrToUShort(
    LONG_PTR lOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlLongPtrToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongSub(
    LONG lMinuend, 
    LONG lSubtrahend, 
    LONG* plResult
){
    LouPrint("LouKeRtlLongSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToChar(
    LONG lOperand, 
    CHAR *pch
){
    LouPrint("LouKeRtlLongToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToInt(
    LONG lOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlLongToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToInt8(
    LONG lOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlLongToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToIntPtr(
    LONG lOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlLongToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToShort(
    LONG lOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlLongToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToUChar(
    LONG lOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlLongToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToUInt(
    LONG lOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlLongToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToUInt8(
    LONG  lOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlLongToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToUIntPtr(
    LONG lOperand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlLongToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToULong(
    LONG lOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlLongToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToULongLong(
    LONG lOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlLongToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToULongPtr(
    LONG lOperand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlLongToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlLongToUShort(
    LONG lOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlLongToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlPtrdiffTAdd(
    ptrdiff_t Augend,
    ptrdiff_t Addend, 
    ptrdiff_t* pResult
){
    LouPrint("LouKeRtlPtrdiffTAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlPtrdiffTMult(
    ptrdiff_t Multiplicand, 
    ptrdiff_t Multiplier, 
    ptrdiff_t* pResult
){
    LouPrint("LouKeRtlPtrdiffTMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlPtrdiffTSub(
    ptrdiff_t Minuend, 
    ptrdiff_t Subtrahend, 
    ptrdiff_t* pResult
){
    LouPrint("LouKeRtlPtrdiffTSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortAdd(
    SHORT sAugend, 
    SHORT sAddend, 
    SHORT* psResult
){
    LouPrint("LouKeRtlShortAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortMult(
    SHORT sMultiplicand, 
    SHORT sMultiplier, 
    SHORT* psResult
){
    LouPrint("LouKeRtlShortMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortSub(
    SHORT sMinuend, 
    SHORT sSubtrahend, 
    SHORT* psResult
){
    LouPrint("LouKeRtlShortSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToChar(
    SHORT sOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlShortToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToDWordPtr(
    SHORT sOperand, 
    DWORD_PTR* pdwResult
){
    LouPrint("LouKeRtlShortToDWordPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToInt8(
    SHORT sOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlShortToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToUChar(
    SHORT sOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlShortToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToUInt(
    SHORT sOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlShortToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToUInt8(
    SHORT sOperand, 
    UINT8 *pui8Result
){
    LouPrint("LouKeRtlShortToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToUIntPtr(
    SHORT sOperand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlShortToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToULong(
    SHORT sOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlShortToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToULongLong(
    SHORT sOperand, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlShortToULongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToULongPtr(
    SHORT sOperand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlShortToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlShortToUShort(
    SHORT sOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlShortToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSizeTAdd(
    size_t Augend, 
    size_t Addend, 
    size_t* pResult
){
    LouPrint("LouKeRtlSizeTAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSizeTMult(
    size_t Multiplicand, 
    size_t Multiplier, 
    size_t* pResult
){
    LouPrint("LouKeRtlSizeTMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSizeTSub(
    size_t Minuend, 
    size_t Subtrahend, 
    size_t* pResult
){
    LouPrint("LouKeRtlSizeTSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSSIZETAdd(
    SSIZE_T Augend, 
    SSIZE_T Addend, 
    SSIZE_T* pResult
){
    LouPrint("LouKeRtlSSIZETAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSSIZETMult(
    SSIZE_T Multiplicand, 
    SSIZE_T Multiplier, 
    SSIZE_T* pResult
){
    LouPrint("LouKeRtlSSIZETMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlSSIZETSub(
    SSIZE_T Minuend, 
    SSIZE_T Subtrahend, 
    SSIZE_T* pResult
){
    LouPrint("LouKeRtlSSIZETSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUInt8Add(
    UINT8 u8Augend, 
    UINT8 u8Addend, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlUInt8Add()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUInt8Mult(
    UINT8 u8Multiplicand, 
    UINT8 u8Multiplier, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlUInt8Mult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUInt8Sub(
    UINT8 u8Minuend, 
    UINT8 u8Subtrahend, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlUInt8Sub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUInt8ToChar(
    UINT8 u8Operand, 
    CHAR* pch
){
    LouPrint("LouKeRtlUInt8ToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUInt8ToInt8(
    UINT8 u8Operand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlUInt8ToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntAdd(
    UINT uAugend, 
    UINT uAddend, 
    UINT* puResult
){
    LouPrint("LouKeRtlUIntAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntMult(
    UINT    uMultiplicand, 
    UINT    uMultiplier, 
    UINT*   puResult
){
    if(!puResult){
        return STATUS_INVALID_PARAMETER;
    }

    if(Uint32MultiplicationWillOverflow(uMultiplicand, uMultiplier)){
        return STATUS_INTEGER_OVERFLOW; 
    }

    *puResult = uMultiplicand * uMultiplier;
    
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrAdd(
    UINT_PTR uAugend, 
    UINT_PTR uAddend, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlUIntPtrAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrMult(
    UINT_PTR uMultiplicand, 
    UINT_PTR uMultiplier, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlUIntPtrMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrSub(
    UINT_PTR uMinuend, 
    UINT_PTR uSubtrahend, 
    UINT_PTR *puResult
){
    LouPrint("LouKeRtlUIntPtrSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToChar(
    UINT_PTR uOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlUIntPtrToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToInt(
    UINT_PTR uOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlUIntPtrToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToInt16(
    UINT_PTR uOperand, 
    INT16* pi16Result
){
    LouPrint("LouKeRtlUIntPtrToInt16()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToInt8(
    UINT_PTR uOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlUIntPtrToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToIntPtr(
    UINT_PTR uOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlUIntPtrToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToLong(
    UINT_PTR uOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlUIntPtrToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToLongLong(
    UINT_PTR uOperand, 
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlUIntPtrToLongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToLongPtr(
    UINT_PTR uOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlUIntPtrToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToShort(
    UINT_PTR uOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlUIntPtrToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToUChar(
    UINT_PTR uOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlUIntPtrToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToUInt(
    UINT_PTR uOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlUIntPtrToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToUInt16(
    UINT_PTR uOperand, 
    UINT16* pu16Result
){
    LouPrint("LouKeRtlUIntPtrToUInt16()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToUInt8(
    UINT_PTR uOperand, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlUIntPtrToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToULong(
    UINT_PTR uOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlUIntPtrToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntPtrToUShort(
    UINT_PTR uOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlUIntPtrToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntSub(
    UINT uMinuend, 
    UINT uSubtrahend, 
    UINT* puResult
){
    LouPrint("LouKeRtlUIntSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToChar(
    UINT uOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlUIntToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToInt(
    UINT uOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlUIntToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToInt8(
    UINT uOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlUIntToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToIntPtr(
    UINT uOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlUIntToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToLong(
    UINT uOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlUIntToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToLongPtr(
    UINT uOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlUIntToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToShort(
    UINT uOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlUIntToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToUChar(
    UINT uOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlUIntToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToUInt8(
    UINT uOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlUIntToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUIntToUShort(
    UINT uOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlUIntToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongAdd(
    ULONG ulAugend, 
    ULONG ulAddend, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlULongAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongAdd(
    ULONGLONG ullAugend, 
    ULONGLONG ullAddend, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlULongLongAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongMult(
    ULONGLONG ullMultiplicand, 
    ULONGLONG ullMultiplier, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlULongLongMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongSub(
    ULONGLONG ullMinuend, 
    ULONGLONG ullSubtrahend, 
    ULONGLONG* pullResult
){
    LouPrint("LouKeRtlULongLongSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToChar(
    ULONGLONG ullOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlULongLongToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToInt(
    ULONGLONG ullOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlULongLongToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToInt8(
    ULONGLONG ullOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlULongLongToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToLong(
    ULONGLONG ullOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlULongLongToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToLongLong(
    ULONGLONG ullOperand, 
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlULongLongToLongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToLongPtr(
    ULONGLONG ullOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlULongLongToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToShort(
    ULONGLONG ullOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlULongLongToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToUChar(
    ULONGLONG ullOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlULongLongToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToUInt(
    ULONGLONG ullOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlULongLongToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToUInt8(
    ULONGLONG ullOperand, 
    UINT8* pu8Result
){
    LouPrint("LouKeRtlULongLongToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToUIntPtr(
    ULONGLONG ullOperand, 
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlULongLongToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToULong(
    ULONGLONG ullOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlULongLongToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToULongPtr(
    ULONGLONG ullOperand, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlULongLongToULongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongLongToUShort(
    ULONGLONG ullOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlULongLongToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongMult(
    ULONG ulMultiplicand, 
    ULONG ulMultiplier, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlULongMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrAdd(
    ULONG_PTR ulAugend, 
    ULONG_PTR ulAddend, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlULongPtrAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrMult(
    ULONG_PTR ulMultiplicand, 
    ULONG_PTR ulMultiplier, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlULongPtrMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrSub(
    ULONG_PTR ulMinuend, 
    ULONG_PTR ulSubtrahend, 
    ULONG_PTR* pulResult
){
    LouPrint("LouKeRtlULongPtrSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToChar(
    ULONG_PTR ulOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlULongPtrToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToInt(
    ULONG_PTR ulOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlULongPtrToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToInt8(
    ULONG_PTR ulOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlULongPtrToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToIntPtr(
    ULONG_PTR ulOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlULongPtrToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToLong(
    ULONG_PTR ulOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlULongPtrToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToLongLong(
    ULONG_PTR ulOperand, 
    LONGLONG* pllResult
){
    LouPrint("LouKeRtlULongPtrToLongLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToLongPtr(
    ULONG_PTR ulOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlULongPtrToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToShort(
    ULONG_PTR ulOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlULongPtrToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToUInt(
    ULONG_PTR ulOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlULongPtrToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToUInt8(
    ULONG_PTR ulOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlULongPtrToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToUIntPtr(
    ULONG_PTR ulOperand,
    UINT_PTR* puResult
){
    LouPrint("LouKeRtlULongPtrToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToULong(
    ULONG_PTR ulOperand, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlULongPtrToULong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongPtrToUShort(
    ULONG_PTR ulOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlULongPtrToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongSub(
    ULONG ulMinuend, 
    ULONG ulSubtrahend, 
    ULONG* pulResult
){
    LouPrint("LouKeRtlULongSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToChar(
    ULONG ulOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlULongToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToInt(
    ULONG ulOperand, 
    INT* piResult
){
    LouPrint("LouKeRtlULongToInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToInt8(
    ULONG ulOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlULongToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToIntPtr(
    ULONG ulOperand, 
    INT_PTR* piResult
){
    LouPrint("LouKeRtlULongToIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToLong(
    ULONG ulOperand, 
    LONG* plResult
){
    LouPrint("LouKeRtlULongToLong()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToLongPtr(
    ULONG ulOperand, 
    LONG_PTR* plResult
){
    LouPrint("LouKeRtlULongToLongPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToShort(
    ULONG ulOperand, 
    SHORT* psResult
){
    LouPrint("()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToUChar(
    ULONG ulOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlULongToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToUInt(
    ULONG ulOperand, 
    UINT* puResult
){
    LouPrint("LouKeRtlULongToUInt()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToUInt8(
    ULONG ulOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlULongToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToUIntPtr(
    ULONG ulOperand, 
    UINT_PTR* puiResult
){
    LouPrint("LouKeRtlULongToUIntPtr()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlULongToUShort(
    ULONG ulOperand, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlULongToUShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortAdd(
    USHORT usAugend, 
    USHORT usAddend, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlUShortAdd()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortMult(
    USHORT usMultiplicand, 
    USHORT usMultiplier, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlUShortMult()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortSub(
    USHORT usMinuend, 
    USHORT usSubtrahend, 
    USHORT* pusResult
){
    LouPrint("LouKeRtlUShortSub()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortToChar(
    USHORT usOperand, 
    CHAR* pch
){
    LouPrint("LouKeRtlUShortToChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortToInt8(
    USHORT usOperand, 
    INT8* pi8Result
){
    LouPrint("LouKeRtlUShortToInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortToShort(
    USHORT usOperand, 
    SHORT* psResult
){
    LouPrint("LouKeRtlUShortToShort()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortToUChar(
    USHORT usOperand, 
    UCHAR* pch
){
    LouPrint("LouKeRtlUShortToUChar()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTATUS 
LouKeRtlUShortToUInt8(
    USHORT usOperand, 
    UINT8* pui8Result
){
    LouPrint("LouKeRtlUShortToUInt8()\n");
    while(1);
    return STATUS_SUCCESS;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszSrc
){
    LouPrint("LouKeRtlStringCbCatA()\n");
    while(1);
    return 0;    
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatExA(
    LOUSTRSAFE_PSTR     pszDest,
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszSrc, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCatExA()\n");
    while(1);
    return 0;   
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining,
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCatExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatNA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cbToAppend
){
    LouPrint("LouKeRtlStringCbCatNA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatNExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cbToAppend, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCatNExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatNExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cbToAppend, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCatNExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatNW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cbToAppend
){
    LouPrint("LouKeRtlStringCbCatNW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCatW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlStringCbCatW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszSrc
){
    LouPrint("LouKeRtlStringCbCopyA()");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszSrc, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCopyExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCopyExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyNA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cbToCopy
){
    LouPrint("LouKeRtlStringCbCopyNA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyNExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cbToCopy, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCopyNExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyNExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cbToCopy, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCopyNExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyNW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cbToCopy
){
    LouPrint("LouKeRtlStringCbCopyNW()");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyUnicodeString(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    PCUNICODE_STRING    SourceString
){
    LouPrint("LouKeRtlStringCbCopyUnicodeString()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyUnicodeStringEx(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    PCUNICODE_STRING    SourceString, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCbCopyUnicodeStringEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbCopyW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlStringCbCopyW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbLengthA(
    STRSAFE_PCNZCH      psz, 
    size_t              cbMax, 
    size_t*             pcbLength
){
    LouPrint("LouKeRtlStringCbLengthA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbLengthW(
    STRSAFE_PCNZWCH     psz, 
    size_t              cbMax, 
    size_t*             pcbLength
){
    LouPrint("LouKeRtlStringCbLengthW()\n");
    while(1);
    return 0;
}


KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbPrintfA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCbPrintfA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbPrintfExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    ...                 
){
    LouPrint("LouKeRtlStringCbPrintfExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbPrintfExW(
    LOUSTRSAFE_PWSTR    pszDest,
    size_t              cbDest, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags,
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCbPrintfExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbPrintfW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCbPrintfW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbVPrintfA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCSTR    pszFormat,
    va_list             argList
){
    LouPrint("LouKeRtlStringCbVPrintfA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbVPrintfExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCbVPrintfExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbVPrintfExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcbRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCbVPrintfExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCbVPrintfW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cbDest, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCbVPrintfW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszSrc
){
    LouPrint("LouKeRtlStringCchCatA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszSrc, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCatExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest,
    LOUSTRSAFE_PCWSTR   pszSrc, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCatExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatNA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cchToAppend
){
    LouPrint("LouKeRtlStringCchCatNA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatNExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cchToAppend, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCatNExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatNExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cchToAppend, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCatNExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatNW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cchToAppend
){
    LouPrint("LouKeRtlStringCchCatNW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCatW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlStringCchCatW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszSrc
){
    LouPrint("LouKeRtlStringCchCopyA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszSrc, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCopyExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCopyExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyNA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cchToCopy
){
    LouPrint("LouKeRtlStringCchCopyNA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyNExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZCH      pszSrc, 
    size_t              cchToCopy, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCopyNExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyNExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cchToCopy, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCopyNExW()\n");
    while(1);
    return 0;
}


KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyNW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    STRSAFE_PCNZWCH     pszSrc, 
    size_t              cchToCopy
){
    LouPrint("LouKeRtlStringCchCopyUnicodeString()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyUnicodeString(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    PCUNICODE_STRING    SourceString
){
    LouPrint("LouKeRtlStringCchCopyUnicodeString()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyUnicodeStringEx(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    PCUNICODE_STRING    SourceString, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlStringCchCopyUnicodeStringEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchCopyW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlStringCchCopyW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchLengthA(
    STRSAFE_PCNZCH  psz, 
    size_t          cchMax, 
    size_t*         pcchLength
){
    LouPrint("LouKeRtlStringCchLengthA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchLengthW(
    STRSAFE_PCNZWCH     psz, 
    size_t              cchMax, 
    size_t*             pcchLength
){
    LouPrint("LouKeRtlStringCchLengthW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchPrintfA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCchPrintfA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchPrintfExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCchPrintfExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchPrintfExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCchPrintfW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchPrintfW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlStringCchPrintfW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchVPrintfA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCchVPrintfA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchVPrintfExA(
    LOUSTRSAFE_PSTR     pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PSTR*    ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCSTR    pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCchVPrintfExA()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchVPrintfExW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PWSTR*   ppszDestEnd, 
    size_t*             pcchRemaining, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCchVPrintfExW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlStringCchVPrintfW(
    LOUSTRSAFE_PWSTR    pszDest, 
    size_t              cchDest, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlStringCchVPrintfW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnalignedStringCbLengthW(
    STRSAFE_PCUNZWCH    psz, 
    size_t              cbMax, 
    size_t*             pcbLength
){
    LouPrint("LouKeRtlUnalignedStringCbLengthW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnalignedStringCchLengthW(
    STRSAFE_PCUNZWCH    psz, 
    size_t              cchMax, 
    size_t*             pcchLength
){
    LouPrint("LouKeRtlUnalignedStringCchLengthW()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCat(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString
){
    LouPrint("LouKeRtlUnicodeStringCat()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCatEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCatEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCatString(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlUnicodeStringCatString()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCatStringEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCatStringEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCatN(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cbToAppend
){
    LouPrint("LouKeRtlUnicodeStringCbCatN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCatNEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cbToAppend, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCbCatNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCatStringN(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cbToAppend
){
    LouPrint("LouKeRtlUnicodeStringCbCatStringN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCatStringNEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cbToAppend, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCbCatStringNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCopyN(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cbToCopy
){
    LouPrint("LouKeRtlUnicodeStringCbCopyN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCopyNEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cbToCopy, 
    PUNICODE_STRING     RemainingString,
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCbCopyNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCopyStringN(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cbToCopy
){
    LouPrint("LouKeRtlUnicodeStringCbCopyStringN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCbCopyStringNEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cbToCopy, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCbCopyStringNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCatN(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cchToAppend
){
    LouPrint("LouKeRtlUnicodeStringCchCatN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCatNEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cchToAppend, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCchCatNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCatStringN(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cchToAppend
){
    LouPrint("LouKeRtlUnicodeStringCchCatStringN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCatStringNEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cchToAppend, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCchCatStringNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCopyN(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cchToCopy
){
    LouPrint("LouKeRtlUnicodeStringCchCopyN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCopyNEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    size_t              cchToCopy, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCchCopyNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCopyStringN(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cchToCopy
){
    LouPrint("LouKeRtlUnicodeStringCchCopyStringN()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCchCopyStringNEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    size_t              cchToCopy, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCchCopyStringNEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCopy(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString
){
    LouPrint("LouKeRtlUnicodeStringCopy()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCopyEx(
    PUNICODE_STRING     DestinationString, 
    PCUNICODE_STRING    SourceString, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCopyEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCopyString(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlUnicodeStringCopyString()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringCopyStringEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringCopyStringEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringInit(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc
){
    LouPrint("LouKeRtlUnicodeStringInit()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringInitEx(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszSrc, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringInitEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringPrintf(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlUnicodeStringPrintf()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringPrintfEx(
    PUNICODE_STRING     DestinationString, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    ...
){
    LouPrint("LouKeRtlUnicodeStringPrintfEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringValidate(
    PCUNICODE_STRING SourceString
){
    LouPrint("LouKeRtlUnicodeStringValidate()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringValidateEx(
    PCUNICODE_STRING    SourceString, 
    DWORD               dwFlags
){
    LouPrint("LouKeRtlUnicodeStringValidateEx()\n");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringVPrintf(
    PUNICODE_STRING     DestinationString, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlUnicodeStringVPrintf()");
    while(1);
    return 0;
}

KERNEL_EXPORT 
LOUSTRSAFEDDI 
LouKeRtlUnicodeStringVPrintfEx(
    PUNICODE_STRING     DestinationString, 
    PUNICODE_STRING     RemainingString, 
    DWORD               dwFlags, 
    LOUSTRSAFE_PCWSTR   pszFormat, 
    va_list             argList
){
    LouPrint("LouKeRtlUnicodeStringVPrintfEx()\n");
    while(1);
    return 0;
}