#include <LouACPI.h>
#include "AmlInternals.h"

SET_OPTIMIZATION(3) LOUSTATUS LouKeAcpiInterperateData(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
){
    size_t TableLength;
    size_t TableIndex;
    uint8_t* DsdtAmlSpace;

    if((Context) && (Context->AmlStream) && (Context->Length)) {
        DsdtAmlSpace = Context->AmlStream;
        TableLength = Context->Length;
        TableIndex = Context->Index;
    }else{
        return STATUS_INVALID_PARAMETER;
    }
    //this is going to look weird to some so 
    //im going to explain this as i go along
    while(TableIndex < TableLength){
        if(Context->InterpreterReturn){
            return STATUS_SUCCESS;
        }
        switch(DsdtAmlSpace[TableIndex]){
            //there are two 16 bit instruction types
            //EXTENDED and LNOT
            case AML_PREFIX_EXTENDED_OPCODE:{
                TableIndex++;
                switch(DsdtAmlSpace[TableIndex]){
                    case AML_EXTENDED_OPCODE_MUTEX:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpMutex(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_EVENT:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpEvent(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_COND_REF_OF:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpCondRefOf(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_CREATE_FEILD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpCreateFeild(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_LOAD_TABLE:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpLoadTable(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_LOAD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpLoad(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_STALL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpStall(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_SLEEP:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpSleep(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_AQUIRE:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpAcquire(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_SIGNAL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpSignal(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_WAIT:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpWait(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_RESET:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpReset(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_RELEASE:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpRelease(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_TO_BCD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpToBcd(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_REVISION:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpRevision(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_DEBUG:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpDebug(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_FATAL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpFatal(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_TIMER:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpTimer(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_OP_REGION:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpRegion(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_FEILD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpFeild(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_DEVICE:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpDevice(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_POWER_RES:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpPowerRes(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_THERMAL_XONE:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpThermalXOne(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_INDEX_FEILD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpIndexFeild(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_BANK_FEILD:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpBankFeild(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    case AML_EXTENDED_OPCODE_DATA_REGION:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseExtendedOpRegion(Context);
                        TableIndex = Context->Index;
                        continue;
                    }
                    default:
                        Context->ExecutionState = INVALID_OPCODE;
                        return STATUS_UNSUCCESSFUL;
                }
                continue;
            }
            case AML_OPCODE_LNOT:{
                TableIndex++;
                switch(DsdtAmlSpace[TableIndex]){
                    case AML_OPCODE_LNOT_EQUAL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseLNotNotEqual(Context);
                        TableIndex = Context->Index;
                        continue;                     
                    }
                    case AML_OPCODE_LLES_EQUAL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseLNotLessEqual(Context);
                        TableIndex = Context->Index;
                        continue;                       
                    }
                    case AML_OPCODE_LGREATOR_EQUAL:{
                        Context->Index = TableIndex; 
                        LouKeAcpiParseLNotGreatorEqual(Context);
                        TableIndex = Context->Index;
                        continue;                     
                    }
                    default:
                        Context->ExecutionState = INVALID_OPCODE;
                        return STATUS_UNSUCCESSFUL;
                }
                continue;
            }
            //the rest of the systems are 8 bit
            case AML_OPCODE_ZERO:{
                Context->Index = TableIndex; 
                LouKeAcpiParseZero(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ONE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseOne(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ALIAS:{
                Context->Index = TableIndex; 
                LouKeAcpiParseAlias(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_SCOPE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseScope(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_BUFFER:{
                Context->Index = TableIndex; 
                LouKeAcpiParseBuffer(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_PACKAGE:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePackage(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_VARIABLE_PACKAGE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseVariablePackage(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_METHOD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseMethod(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_EXTERNAL:{
                Context->Index = TableIndex; 
                LouKeAcpiParseExternal(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL0:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal0(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL1:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal1(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL2:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal1(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL3:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal3(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL4:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal4(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL5:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal5(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL6:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal6(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOCAL7:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLocal7(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG0:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg0(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG1:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg1(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG2:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg2(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG3:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg3(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG4:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg4(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG5:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg5(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ARG6:{
                Context->Index = TableIndex; 
                LouKeAcpiParseArg6(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_STORE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseStore(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_REF_OF:{
                Context->Index = TableIndex; 
                LouKeAcpiParseRefOf(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ADD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseAdd(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CONCAT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseConcat(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_SUBTRACT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseSubtract(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_INCREMENT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseIncrement(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_DECREMENT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseDecrement(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_MULTIPLY:{
                Context->Index = TableIndex; 
                LouKeAcpiParseMultiply(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_DIVIDE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseDivide(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_SHIFT_LEFT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseShiftLeft(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_SHIFT_RIGHT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseShiftRight(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_AND:{
                Context->Index = TableIndex; 
                LouKeAcpiParseAnd(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NAND:{
                Context->Index = TableIndex; 
                LouKeAcpiParseNand(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_OR:{
                Context->Index = TableIndex; 
                LouKeAcpiParseOr(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NOR:{
                Context->Index = TableIndex; 
                LouKeAcpiParseNor(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_XOR:{
                Context->Index = TableIndex; 
                LouKeAcpiParseXor(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NOT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseNot(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_FIND_SET_LEFT_BIT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseFindSetLeftBit(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_FIND_SET_RIGHT_BIT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseFindSetRightBit(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_DEREF_OF:{
                Context->Index = TableIndex; 
                LouKeAcpiParseDerefOf(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CONCAT_RES:{
                Context->Index = TableIndex; 
                LouKeAcpiParseConcatRes(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_MOD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseMod(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NOTIFY:{
                Context->Index = TableIndex; 
                LouKeAcpiParseNotify(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_SIZEOF:{
                Context->Index = TableIndex; 
                LouKeAcpiParseSizeof(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_INDEX:{
                Context->Index = TableIndex; 
                LouKeAcpiParseIndex(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_MATCH:{
                Context->Index = TableIndex; 
                LouKeAcpiParseMatch(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CREATE_DWORD_FEILD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCreateDWordFeild(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CREATE_WORD_FEILD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCreateWordFeild(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CREATE_BYTE_FEILD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCreateByteFeild(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CREATE_BIT_FEILD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCreateBitFeild(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_OBJECT_TYPE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseObjectType(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CREATE_QWORD_FEILD:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCreateQWordFeild(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LAND:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLand(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LOR:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLor(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LEQUAL:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLEqual(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LGREATOR:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLGreator(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_LLESS:{
                Context->Index = TableIndex; 
                LouKeAcpiParseLLess(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_TO_BUFFER:{
                Context->Index = TableIndex; 
                LouKeAcpiParseToBuffer(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_TO_DECIMAL_STRING:{
                Context->Index = TableIndex; 
                LouKeAcpiParseToDecimalString(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_TO_HEX_STRING:{
                Context->Index = TableIndex; 
                LouKeAcpiParseToHexString(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_TO_INTEGER:{
                Context->Index = TableIndex; 
                LouKeAcpiParseToInteger(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_TO_STRING:{
                Context->Index = TableIndex; 
                LouKeAcpiParseToString(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_COPY_OBJECT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseCopyObject(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_MID:{
                Context->Index = TableIndex; 
                LouKeAcpiParseMid(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_CONTINUE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseContinue(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_IF:{
                Context->Index = TableIndex; 
                LouKeAcpiParseIf(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ELSE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseElse(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_WHILE:{
                Context->Index = TableIndex; 
                LouKeAcpiParseWhile(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NOOP:{
                Context->Index = TableIndex; 
                LouKeAcpiParseNoop(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_RETURN:{
                Context->Index = TableIndex; 
                LouKeAcpiParseReturn(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_BREAK:{
                Context->Index = TableIndex; 
                LouKeAcpiParseBreak(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_BREAK_POINT:{
                Context->Index = TableIndex; 
                LouKeAcpiParseBreakPoint(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_NAME:{
                Context->Index = TableIndex; 
                LouKeAcpiParseName(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_OPCODE_ONES:{
                Context->Index = TableIndex; 
                LouKeAcpiParseOnes(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_BYTE:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixByte(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_WORD:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixWord(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_DWORD:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixDWord(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_QWORD:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixQWord(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_STRING:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixString(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_DUAL_NAME:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixDualName(Context);
                TableIndex = Context->Index;
                continue;
            }
            case AML_PREFIX_MULTI_NAME:{
                Context->Index = TableIndex; 
                LouKeAcpiParsePrefixMultiName(Context);
                TableIndex = Context->Index;
                continue;
            }
            default:
                LouPrint("Op:%s Table Index:%d Of %d\n", &DsdtAmlSpace[TableIndex], TableIndex, TableLength);
                Context->ExecutionState = INVALID_OPCODE;
                LouPrint("Exection Encountered An Ivalid Opcode\n");
                return STATUS_UNSUCCESSFUL;
        }

    }
    return STATUS_SUCCESS;
}

SET_OPTIMIZATION(3) bool LouKeAcpiIsByteOpcode(uint8_t byte){
    switch(byte){
        case AML_PREFIX_EXTENDED_OPCODE:
        case AML_OPCODE_ZERO:
        case AML_OPCODE_ONE:
        case AML_OPCODE_ALIAS:
        case AML_OPCODE_NAME:
        case AML_OPCODE_SCOPE:
        case AML_OPCODE_BUFFER:
        case AML_OPCODE_PACKAGE:
        case AML_OPCODE_VARIABLE_PACKAGE:
        case AML_OPCODE_METHOD:
        case AML_OPCODE_EXTERNAL:
        case AML_OPCODE_LOCAL0:
        case AML_OPCODE_LOCAL1:
        case AML_OPCODE_LOCAL2:
        case AML_OPCODE_LOCAL3:
        case AML_OPCODE_LOCAL4:
        case AML_OPCODE_LOCAL5:
        case AML_OPCODE_LOCAL6:
        case AML_OPCODE_LOCAL7:
        case AML_OPCODE_ARG0:
        case AML_OPCODE_ARG1:
        case AML_OPCODE_ARG2:
        case AML_OPCODE_ARG3:
        case AML_OPCODE_ARG4:
        case AML_OPCODE_ARG5:
        case AML_OPCODE_ARG6:
        case AML_OPCODE_STORE:
        case AML_OPCODE_REF_OF:
        case AML_OPCODE_ADD:
        case AML_OPCODE_CONCAT:
        case AML_OPCODE_SUBTRACT:
        case AML_OPCODE_INCREMENT:
        case AML_OPCODE_DECREMENT:
        case AML_OPCODE_MULTIPLY:
        case AML_OPCODE_DIVIDE:
        case AML_OPCODE_SHIFT_LEFT:
        case AML_OPCODE_SHIFT_RIGHT:
        case AML_OPCODE_AND:
        case AML_OPCODE_NAND:
        case AML_OPCODE_OR:
        case AML_OPCODE_NOR:
        case AML_OPCODE_XOR:
        case AML_OPCODE_NOT:
        case AML_OPCODE_FIND_SET_LEFT_BIT:
        case AML_OPCODE_FIND_SET_RIGHT_BIT:
        case AML_OPCODE_DEREF_OF:
        case AML_OPCODE_CONCAT_RES:
        case AML_OPCODE_MOD:
        case AML_OPCODE_NOTIFY:
        case AML_OPCODE_SIZEOF:
        case AML_OPCODE_INDEX:
        case AML_OPCODE_MATCH:
        case AML_OPCODE_CREATE_DWORD_FEILD:
        case AML_OPCODE_CREATE_WORD_FEILD:
        case AML_OPCODE_CREATE_BYTE_FEILD:
        case AML_OPCODE_CREATE_BIT_FEILD:
        case AML_OPCODE_OBJECT_TYPE:
        case AML_OPCODE_CREATE_QWORD_FEILD:
        case AML_OPCODE_LAND:
        case AML_OPCODE_LOR:
        case AML_OPCODE_LNOT:
        case AML_OPCODE_LEQUAL:
        case AML_OPCODE_LGREATOR:
        case AML_OPCODE_LLESS:
        case AML_OPCODE_TO_BUFFER:
        case AML_OPCODE_TO_DECIMAL_STRING:
        case AML_OPCODE_TO_HEX_STRING:
        case AML_OPCODE_TO_INTEGER:
        case AML_OPCODE_TO_STRING:
        case AML_OPCODE_COPY_OBJECT:
        case AML_OPCODE_MID:
        case AML_OPCODE_CONTINUE:
        case AML_OPCODE_IF:
        case AML_OPCODE_ELSE:
        case AML_OPCODE_WHILE:
        case AML_OPCODE_NOOP:
        case AML_OPCODE_RETURN:
        case AML_OPCODE_BREAK:
        case AML_OPCODE_BREAK_POINT:
        case AML_OPCODE_ONES:
            return true;
        default:
            return false;
    }
}

SET_OPTIMIZATION(1) void LouKeAcpiExecuteSubPackageContext(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context,
    NAMESPACE_HANDLE CurrentDirectory,
    size_t DataStart,
    size_t PackageLength
){
    //SAVE CONTEXT
    NAMESPACE_HANDLE ReturnDirectory = Context->CurrentDirectory;
    uint8_t* AmlStream = Context->AmlStream;
    size_t ReturnLength = Context->Length;
    size_t ReturnIndex = Context->Index;
    //SETUP NEW CONTEXT 
    Context->Length = PackageLength - (DataStart - ReturnIndex);
    Context->Index = 0;
    Context->AmlStream = (uint8_t*)&Context->AmlStream[DataStart];
    Context->CurrentDirectory = CurrentDirectory;
    //RUN CONTEXT
    LouKeAcpiInterperateData(Context);
    //RESTORE CONNTEXT
    Context->AmlStream = AmlStream;
    Context->Index = ReturnIndex;
    Context->Length = ReturnLength;
    Context->CurrentDirectory = ReturnDirectory;
}


SET_OPTIMIZATION(3) void LouKeAcpiNameSpaceAddChild(
    NAMESPACE_HANDLE CurrentDirectory,
    NAMESPACE_HANDLE NewStream
){
    NAMESPACE_HANDLE Tmp = (NAMESPACE_HANDLE)CurrentDirectory->SubTree.NextHeader;
    if(!Tmp){
        CurrentDirectory->SubTree.NextHeader = (PListHeader)NewStream;
        NewStream->SubTree.LastHeader = (PListHeader)CurrentDirectory;
        return;
    }
    while(Tmp->AmlTree.NextHeader){
        Tmp = (NAMESPACE_HANDLE)Tmp->AmlTree.NextHeader;
    }
    Tmp->AmlTree.NextHeader = (PListHeader)NewStream;
    NewStream->AmlTree.LastHeader = (PListHeader)Tmp;
}

SET_OPTIMIZATION(3) size_t LouKeAcpiGetAmlPackageLength(uint8_t* Buffer){
    PAML_PACKAGE_LEAD_BYTE LeadByte = (PAML_PACKAGE_LEAD_BYTE)Buffer;
    if(LeadByte->ByteCount > 0){
        size_t Result = LeadByte->Length;
        for(uint8_t i = 0; i < LeadByte->ByteCount; i++){
            Result |= (Buffer[i + 1] << (4 + (i * 8)));
        }    
        return Result;
    }else{
        return (LeadByte->Length | (LeadByte->Reserved << 4));
    }
}

SET_OPTIMIZATION(3) void LouKeAcpiParsePackageLength(
    uint8_t* AmlStream, 
    size_t Index, 
    string* NameHandle,
    size_t* PackageLength,
    size_t* DataStart
){
    size_t NameLength;
    Index++; // Skip opcode
    size_t LenByteCount = LouKeAcpiGetAmlPackageByteCount(&AmlStream[Index]);
    size_t PkgLength = LouKeAcpiGetAmlPackageLength(&AmlStream[Index]);
    if (PackageLength) {
        *PackageLength = PkgLength;
    }
    Index += LenByteCount;
    if (NameHandle) {
        *NameHandle = CreateUTF8StringFromAcpiNameString(&AmlStream[Index]);
    }
    NameLength = AmlNameSpaceNameStringLength(&AmlStream[Index]);
    if (DataStart) {
        *DataStart = Index + NameLength;
    }
}

