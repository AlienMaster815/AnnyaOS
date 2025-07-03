/*-------------------------------
--  Tyler Grenier : IntelFamily.h
--  Informal Clean Room Remake 
--  of Linux's intel-family.h 
-------------------------------*/

#ifndef _INTEL_FAMILY_H
#define _INTEL_FAMILY_H

#define INTEL_FAMILY_MODEL(Family, Model)           DEFINE_VFM(X86_64_VENDOR_INTEL, Family, Model)
#define ANY_INTEL                                   INTEL_FAMILY_MODEL(X86_64_FAMILY_ANY, X86_64_MODEL_ANY)

//family 5

#define INTEL_FAMILY_5_START                        INTEL_FAMILY_MODEL(5, 0x00)
#define INTEL_PENTIUM_75                            INTEL_FAMILY_MODEL(5, 0x02)
#define INTEL_PENTIUM_MMX                           INTEL_FAMILY_MODEL(5, 0x04)
#define INTEL_QUARK_X1000                           INTEL_FAMILY_MODEL(5, 0x09)

//family 6

#define INTEL_FAMILY_6_START                        INTEL_FAMILY_MODEL(6, 0x00)
#define INTEL_PENTIUM_PRO                           INTEL_FAMILY_MODEL(6, 0x01)
#define INTEL_PENTIUM_2_KLAMATH                     INTEL_FAMILY_MODEL(6, 0x03)
#define INTEL_PENTIUM_3_DESCHUTES                   INTEL_FAMILY_MODEL(6, 0x05)
#define INTEL_PENTIUM_3_TUALATIN                    INTEL_FAMILY_MODEL(6, 0x0B)
#define INTEL_PENTIUM_M_DOTHAN                      INTEL_FAMILY_MODEL(6, 0x0D)
#define INTEL_CORE_YONAH                            INTEL_FAMILY_MODEL(6 ,0x0E)
#define INTEL_CORE_2_MEROM                          INTEL_FAMILY_MODEL(6, 0x0F)
#define INTEL_CORE_2_MEROM_LONG                     INTEL_FAMILY_MODEL(6, 0x16)
#define INTEL_CORE_2_PENRYN                         INTEL_FAMILY_MODEL(6, 0x17)
#define INTEL_CORE_2_DUNNINGTON                     INTEL_FAMILY_MODEL(6, 0x1D)
#define INTEL_NEHALEM                               INTEL_FAMILY_MODEL(6, 0x1E)
#define INTEL_NEHALEM_G                             INTEL_FAMILY_MODEL(6, 0x1F)
#define INTEL_NEHALEM_EP                            INTEL_FAMILY_MODEL(6, 0x1A)
#define INTEL_NEHALEM_EX                            INTEL_FAMILY_MODEL(6, 0x2E)
#define INTEL_WESTMERE                              INTEL_FAMILY_MODEL(6, 0x25)
#define INTEL_WESTMERE_EP                           INTEL_FAMILY_MODEL(6, 0x2C)
#define INTEL_WESTMERE_EX                           INTEL_FAMILY_MODEL(6, 0x2F)
#define INTEL_SANDYBRIDGE                           INTEL_FAMILY_MODEL(6, 0x2A)
#define INTEL_SANDYBRIDGE_X                         INTEL_FAMILY_MODEL(6, 0x2D)
#define INTEL_IVYBRIDGE                             INTEL_FAMILY_MODEL(6, 0x3A)
#define INTEL_IVYBRIDGE_X                           INTEL_FAMILY_MODEL(6, 0x3E)
#define INTEL_HASWELL                               INTEL_FAMILY_MODEL(6, 0x3C)
#define INTEL_HASWELL_X                             INTEL_FAMILY_MODEL(6, 0x3F)
#define INTEL_HASWELL_L                             INTEL_FAMILY_MODEL(6, 0x45)
#define INTEL_HASWELL_G                             INTEL_FAMILY_MODEL(6, 0x46)
#define INTEL_BROADWELL                             INTEL_FAMILY_MODEL(6, 0x3D)
#define INTEL_BROADWELL_G                           INTEL_FAMILY_MODEL(6, 0x47)
#define INTEL_BROADWELL_X                           INTEL_FAMILY_MODEL(6, 0x4F)
#define INTEL_BROADWELL_D                           INTEL_FAMILY_MODEL(6, 0x56)
#define INTEL_SKYLAKE_L                             INTEL_FAMILY_MODEL(6, 0x4E)
#define INTEL_SKYLAKE                               INTEL_FAMILY_MODEL(6, 0x5E)
#define INTEL_SKYLAKE_X                             INTEL_FAMILY_MODEL(6, 0x55)
//CASCADELAKE_X is related to skylake_l 0x55 through S:7
//COOPERLAKE_X is related to skylake_l 0x55 through  S:11
#define INTEL_KABYLAKE_L                            INTEL_FAMILY_MODEL(6, 0x8E)
//AMBERLAKE_L is related to Kabylake_l 0x8E through  S:9
//COFFEELAKE_L is related to Kabylake_l 0x8E through S:10
//WHISKYLAKE_L is related to Kabylake_l 0x8E through S:11 : 12
#define INTEL_KABYLAKE                              INTEL_FAMILY_MODEL(6, 0x9E)
//COFFEELAKE is related to kabylake 0x9E through     s:10 - 13
#define INTEL_COMETLAKE                             INTEL_FAMILY_MODEL(6, 0xA5)
#define INTEL_COMETLAKE_L                           INTEL_FAMILY_MODEL(6, 0xA6)
#define INTEL_CANNONLAKE_L                          INTEL_FAMILY_MODEL(6, 0x66)
#define INTEL_ICELAKE_X                             INTEL_FAMILY_MODEL(6, 0x6A)
#define INTEL_ICELAKE_D                             INTEL_FAMILY_MODEL(6, 0x6C)
#define INTEL_ICELAKE                               INTEL_FAMILY_MODEL(6, 0x7D)
#define INTEL_ICELAKE_L                             INTEL_FAMILY_MODEL(6, 0x7E)
#define INTEL_ICELAKE_NNPI                          INTEL_FAMILY_MODEL(6, 0x9D)
#define INTEL_ROCKETLAKE                            INTEL_FAMILY_MODEL(6, 0xA7)
#define INTEL_TIGERLAKE_L                           INTEL_FAMILY_MODEL(6, 0x8C)
#define INTEL_TIGERLAKE                             INTEL_FAMILY_MODEL(6, 0x8D)
#define INTEL_SAPPHIRERAPIDS_X                      INTEL_FAMILY_MODEL(6, 0x8F)
#define INTEL_EMERALDRAPIDS_X                       INTEL_FAMILY_MODEL(6, 0xCF)
#define INTEL_GRANITERAPIDS_X                       INTEL_FAMILY_MODEL(6, 0xAD)
#define INTEL_GRANITERAPIDS_D                       INTEL_FAMILY_MODEL(6, 0xAE)
#define INTEL_BARTLETTLAKE                          INTEL_FAMILY_MODEL(6, 0xD7)

//"Hybrid" Core Processors aka PCORE and ECORE chips

#define INTEL_LAKEFIELD                             INTEL_FAMILY_MODEL(6, 0x8A)
#define INTEL_ALDERLAKE                             INTEL_FAMILY_MODEL(6, 0x97)
#define INTEL_ALDERLAKE_L                           INTEL_FAMILY_MODEL(6, 0x9A)
#define INTEL_RAPTORLAKE                            INTEL_FAMILY_MODEL(6, 0xB7)
#define INTEL_RAPTORLAKE_P                          INTEL_FAMILY_MODEL(6, 0xBA)
#define INTEL_RAPTORLAKE_S                          INTEL_FAMILY_MODEL(6, 0xBF)
#define INTEL_METEORLAKE                            INTEL_FAMILY_MODEL(6, 0xAC)
#define INTEL_METEORLAKE_L                          INTEL_FAMILY_MODEL(6, 0xAA)
#define INTEL_ARROWLAKE_H                           INTEL_FAMILY_MODEL(6, 0xC5)
#define INTEL_ARROWLAKE                             INTEL_FAMILY_MODEL(6, 0xC6)
#define INTEL_ARROWLAKE_U                           INTEL_FAMILY_MODEL(6, 0xB5)
#define INTEL_LUNARLAKE_M                           INTEL_FAMILY_MODEL(6, 0xBD)
#define INTEL_PANTHERLAKE_L                         INTEL_FAMILY_MODEL(6, 0xCC)

//"Small Core" Core Proccessors aka Atom and chips

#define INTEL_ATOM_BONNELL                          INTEL_FAMILY_MODEL(6, 0x1C)
#define INTEL_ATOM_BONNELL_MID                      INTEL_FAMILY_MODEL(6, 0x26)
#define INTEL_ATOM_SALTWELL                         INTEL_FAMILY_MODEL(6, 0x36)
#define INTEL_ATOM_SALTWELL_MID                     INTEL_FAMILY_MODEL(6, 0x27)
#define INTEL_ATOM_SALTWELL_TABLET                  INTEL_FAMILY_MODEL(6, 0x35)
#define INTEL_ATOM_SILVERMONT                       INTEL_FAMILY_MODEL(6, 0x37)
#define INTEL_ATOM_SILVERMONT_D                     INTEL_FAMILY_MODEL(6, 0x4D)
#define INTEL_ATOM_SILVERMONT_MID                   INTEL_FAMILY_MODEL(6, 0x4A)
#define INTEL_ATOM_SILVERMONT_MID2                  INTEL_FAMILY_MODEL(6, 0x5A)
#define INTEL_ATOM_AIRMONT                          INTEL_FAMILY_MODEL(6, 0x4C)
#define INTEL_ATOM_AIRMONT_NP                       INTEL_FAMILY_MODEL(6, 0x75)
#define INTEL_ATOM_GOLDMONT                         INTEL_FAMILY_MODEL(6, 0x5C)
#define INTEL_ATOM_GOLDMONT_D                       INTEL_FAMILY_MODEL(6, 0x5F)
#define INTEL_ATOM_GOLDMONT_PLUS                    INTEL_FAMILY_MODEL(6, 0x7A)
#define INTEL_ATOM_TREMONT_D                        INTEL_FAMILY_MODEL(6, 0x86)
#define INTEL_ATOM_TREMONT                          INTEL_FAMILY_MODEL(6, 0x96)
#define INTEL_ATOM_TREMONT_L                        INTEL_FAMILY_MODEL(6, 0x9C)
#define INTEL_ATOM_GRACEMONT                        INTEL_FAMILY_MODEL(6, 0xBE)
#define INTEL_ATOM_CRESTMONT_X                      INTEL_FAMILY_MODEL(6, 0xAF)
#define INTEL_ATOM_CRESTMONT                        INTEL_FAMILY_MODEL(6, 0xB6)
#define INTEL_ATOM_DARKMONT_X                       INTEL_FAMILY_MODEL(6, 0xDD)

//XEON Phi

#define INTEL_XEON_PHI_KNL                          INTEL_FAMILY_MODEL(6, 0x57)
#define INTEL_XEON_PHI_KNM                          INTEL_FAMILY_MODEL(6, 0x85)

#define INTEL_FAMILY_6_LAST                         INTEL_FAMILY_MODEL(6, 0xFF)

//Family 15

#define INTEL_P4_WILLAMETTE                         INTEL_FAMILY_MODEL(15, 0x01)
#define INTEL_P4_PRESCOTT                           INTEL_FAMILY_MODEL(15, 0x03)
#define INTEL_P4_PRESCOTT_2M                        INTEL_FAMILY_MODEL(15, 0x04)
#define INTEL_P4_CEADARMILL                         INTEL_FAMILY_MODEL(15, 0x06)

//Family 19

#define INTEL_PANTHERCOVE_X                         INTEL_FAMILY_MODEL(19, 0x01)

typedef enum {
    INTEL_CPU_UNKOWN    =   0x00,
    INTEL_CPU_ATOM      =   0x20,
    INTEL_CPU_CORE      =   0x40,
}INTEL_CPU_TYPE;

typedef enum {
    INTEL_ATOM_CMT_NATIVE_ID    =   0x02,
    INTEL_ATOM_SKT_NATIVE_ID    =   0x03,
}INTEL_NATIVE_ID;

#endif