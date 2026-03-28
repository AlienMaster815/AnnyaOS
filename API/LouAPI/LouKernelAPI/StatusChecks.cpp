//Copyright GPL-2 Tyler Grenier (2024 - 2026)
#include <LouDDK.h>


LOUSTATUS TRANSLATE_STATUS(LOUSTATUS Status) {

	switch (Status) {
	
	case STATUS_SUCCESS:
		return STATUS_SUCCESS;
		
	default:
		return STATUS_UNSUCCESSFUL;
	}

}