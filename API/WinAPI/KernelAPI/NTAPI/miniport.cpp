#include <NtAPI.h>
#include <LouDDK.h>

unsigned char _BitTest64(
	__int64 const* Base,
	__int64 Index
){
	int64_t FOO = *Base;
	return FOO & (1 << Index);
}

LONG InterlockedAnd(
	  LONG volatile* Destination,
	      LONG          Value
) {
	//AND WRAPPER
	return LouKeAndOperationLong((int32_t volatile*)Destination,(int32_t)Value);
}



LONG 
InterlockedCompareExchange(
	  LONG volatile* Destination,
	LONG          ExChange,
	LONG          Comperand
) {

	return LouKeCompareAtomicLongValue(
		(int32_t volatile*)Destination,
		(int32_t)		   ExChange,
		(int32_t)          Comperand
	);
}



PVOID 
InterlockedCompareExchangePointer(
	  PVOID volatile* Destination,
	      PVOID          Exchange,
	PVOID          Comperand
) {
	return LouKeComparePointer(Destination, Exchange, Comperand);
}



LONG
InterlockedOr(
	  LONG volatile* Destination,
	      LONG          Value
) {
	return LouKeOrOperationLong((int32_t volatile*)Destination,(int32_t)Value);
}



LONG 
InterlockedXor(
	  LONG volatile* Destination,
	      LONG          Value
) {
	return LouKeXorOperationLong((int32_t volatile*)Destination, (int32_t)Value);
}