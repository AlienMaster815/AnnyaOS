#ifndef _AML_INTERNALS_H
#define _AML_INTERNALS_H

//c Only
#include <LouAPI.h>

//list of all AML Interpretation functions

void LouKeAcpiParseExtendedOpRegion(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpMutex(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpEvent(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpCondRefOf(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpCreateFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpLoadTable(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpLoad(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpStall(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpSleep(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpAcquire( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpSignal( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpWait( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpReset( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpRelease( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpToBcd( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpRevision( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpBankFeild( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpDataRegion( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpDebug( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpDevice( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpFatal( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpFeild( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpIndexFeild( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpPowerRes( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpThermalXOne( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExtendedOpTimer( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLNotGreatorEqual( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLNotLessEqual( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLNotNotEqual( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixByte( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixDualName( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixDWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixMultiName( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixParent( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixQWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixRoot( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixString( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParsePrefixWord( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseZero(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseXor(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseWhile(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariablePackage(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseToString(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseToInteger(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseToHexString(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseToDecimalString(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseToBuffer(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseSubtract(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseStore(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseSizeof(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseShiftRight(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseShiftLeft(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseScope(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseReturn(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseRefOf(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseBreakPoint(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParsePackage(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseAdd(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseAlias(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseAnd(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg6(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg5(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg4(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg3(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg2(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg1(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseArg0(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable0(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable1(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable2(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable3(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable4(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable5(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable6(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseVariable7(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseBreak(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseBuffer(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseConcat(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseContinue(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseCopyObject(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseDecrement(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseCreateDivide(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseDerefOf(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseElse(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseExternal(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseFindSetBit(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseIf(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseIncrement(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseIndex(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLand(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLEqual(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLGreator(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLLess(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);


void LouKeAcpiParseLocal0(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal1(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal2(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal3(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseDivide(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal4(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal5(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal6(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseLocal7(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);


void LouKeAcpiParseLor(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseMatch(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseMethod(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseMid(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseMod(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseMultiply(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseNand(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseNoop(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseNor(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseNot(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseNotify(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseObjectType(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseOne(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseOnes(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseOr(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateQWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateBitFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateByteFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateDWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);
void LouKeAcpiParseCreateWordFeild(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseFindSetRightBit(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseFindSetLeftBit(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseConcatRes(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);

void LouKeAcpiParseName(
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context
);

void LouKeAcpiParseExtendedOpProcessor( 
    PLOU_ACPI_NAMESPACE_EXECUTION_CONTEXT Context 
);


#endif