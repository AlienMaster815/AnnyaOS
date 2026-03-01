#include <LouAPI.h>

noreturn void LouKeStackPanic() {

	LouPanic("StkChk Failure");

	while (1);
}