#include <LouAPI.h>

__attribute__((noreturn))
void LouKeStackPanic() {

	LouPanic("StkChk Failure");

	while (1);
}