//SPDX-Licence-IdentifierL AGPL 3.0
//Copyright (C) 2024-2025 Tyler Grenier
//Time Finished : 12/28/2024 11:23 PM
//Last Modified : 12/28/2024 11:23 PM

#include <LouDDK.h>

#ifndef _MPI_TYPES_H
#define _MPI_TYPES_H
#pragma pack(push,1)

//Declare Generic Types For Device
typedef int8_t      MPIS8;
typedef uint8_t     MPIU8;
typedef int16_t     MPIS16;
typedef uint16_t    MPIU16;

typedef int32_t     MPIS32;
typedef uint32_t    MPIU32;

//Declare Generic Pointer Types For Device
typedef MPIS8*      PMPIS8;
typedef MPIU8*      PMPIU8;
typedef MPIS16*     PMPIS16;
typedef MPIU16*     PMPIU16;
typedef MPIS32*     PMPIS32;
typedef MPIU32*     PMPIU32;

//Declare Structure for 64 bit Types because 
//32 Bit Systems Might Not Nativly Support It
//By Default
typedef struct _MPIS64{
    MPIU32 LowDWORD;
    MPIS32 HighDWORD;
}MPIS64, * PMPIS64;

typedef struct _MPIU64{
    MPIU32 LowDWORD;
    MPIU32 HighDWORD;
}MPIU64, * PMPIU64;


#pragma pack(pop)
#endif //_MPI_TYPES_H