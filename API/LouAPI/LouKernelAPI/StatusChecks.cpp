#include <LouDDK.h>
#include <NtAPI.h>



LOUSTATUS TRANSLATE_STATUS(LOUSTATUS Status) {

	switch (Status) {
	
	case STATUS_SUCCESS:
		return STATUS_SUCCESS;
		
	default:
		return STATUS_UNSUCCESSFUL;
	}

}