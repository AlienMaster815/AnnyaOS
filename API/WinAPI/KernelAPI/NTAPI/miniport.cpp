#include <NtAPI.h>
#include <LouDDK.h>

unsigned char _BitTest64(
	__int64 const* Base,
	__int64 Index
){
	int64_t FOO = *Base;
	return FOO & (1 << Index);
}


