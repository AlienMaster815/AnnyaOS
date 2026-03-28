//Copyright GPL-2 Tyler Grenier (2026)

#include "LouDll.h"

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

LOUDLL_API
LOUSTATUS
LouRtlCharToUint64(    
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

LOUDLL_API
LOUSTATUS
LouRtlCharToUint32(    
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

LOUDLL_API 
LOUSTATUS 
LouRtlCharToInteger(
    PCSZ    String, 
    ULONG   Base, 
    PULONG  Value
){  
    UINT32 Tmp = 0x00;
    LOUSTATUS Status = LouRtlCharToUint32(
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