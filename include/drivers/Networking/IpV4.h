#ifndef _IP_V4_H
#define _IP_V4_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C"{
#else
#include <LouAPI.h>
#endif

//Copyright Tyler Grenier Febuary 9th 2025
//information sited
//https://datatracker.ietf.org/doc/html/rfc791

#define IPV4_SERVICE_TYPE_PRECEDENCE_MASK   0x02
#define IPV4_SERVICE_TYPE_DELAY_MASK        1 << 3
#define IPV4_SERVICE_TYPE_THROUGHPUT_MASK   1 << 4
#define IPV4_SERVICE_TYPE_RELIABILITY_MASK  1 << 5

//Normal Delay is 0
#define IPV4_SERVICE_TYPE_LOW_DELAY         IPV4_SERVICE_TYPE_DELAY_MASK
//Normal Throughput is 0
#define IPV4_SERVICE_TYPE_HIGH_THROUGHPUT   IPV4_SERVICE_TYPE_THROUGHPUT_MASK
//Normal Reliability is 0
#define IPV4_SERVICE_TYPE_HIGH_RELIABILITY  IPV4_SERVICE_TYPE_RELIABILITY_MASK

#define IPV4_PRECEDENCE_ROUTINE             0
#define IPV4_PRECEDENCE_PRIORITY            1
#define IPV4_PRECEDENCE_IMMEDIATE           2
#define IPV4_PRECEDENCE_FLASH               3
#define IPV4_PRECEDENCE_FLASH_OVERIDE       4
#define IPV4_PRECEDENCE_CRITIC_ECP          5
#define IPV4_PRECEDENCE_INTERNET_CONTROL    6
#define IPV4_PRECEDENCE_NRETWORK_CONTROL    7

#define IPV4_OPTION_COPIED_MASK             1

#define IPV4_OPTION_CLASS_MASK              2 << 1
#define IPV4_OPTION_SET_CLASS(x)            (((x) & 0x02) << 1)

#define IPV4_OPTION_NUMBER_MASK             0x1F << 3
#define IPV4_OPTION_SET_NUMBER(x)           (((x) & 0x1F) << 3)

#define IPV4_OPTION_CLASS_CONTROL           0
#define IPV4_OPTION_CLASS_DEBUG_MESURE      2

#define IPV4_OPTION_END_OF_OPTION_LIST      0
#define IPV4_OPTION_NO_OPERATION            IPV4_OPTION_SET_NUMBER(1)
#define IPV4_OPTION_SECURITY                IPV4_OPTION_SET_NUMBER(2)
#define IPV4_OPTION_LOOSE_SOURCE_ROUTING    IPV4_OPTION_SET_NUMBER(3)
#define IPV4_OPTION_STRICT_SOURCE_ROUTING   IPV4_OPTION_SET_NUMBER(9)
#define IPV4_OPTION_RECORD_ROUTE            IPV4_OPTION_SET_NUMBER(7)
#define IPV4_OPTION_RECORD_STREAM_ID        IPV4_OPTION_SET_NUMBER(8)
#define IPV4_OPTION_INTERNET_TIMESTAMP      IPV4_OPTION_SET_NUMBER(4) | IPV4_OPTION_SET_CLASS(2)

#define IPV4_OPTION_SECURITY_LENGTH         11
#define IPV4_OPTION_STREAM_ID_LENGTH        4



typedef struct IPV4_SERVICE_TYPE{
    uint8_t     Precedence  : 3;
    uint8_t     Delay       : 1;
    uint8_t     Throughput  : 1;
    uint8_t     Reliability : 1;
}IPV4_SERVICE_TYPE, * PIPV4_SERVICE_TYPE;

typedef struct _IPV4_INTERNET_HEADER_FORMAT_FLAGS{
    uint8_t     Reserved    : 1;
    uint8_t     Fragment1   : 1;
    uint8_t     Fragment2   : 1;
}IPV4_INTERNET_HEADER_FORMAT_FLAGS, * PIPV4_INTERNET_HEADER_FORMAT_FLAGS;

typedef struct _IPV4_INTERNET_HEADER_FORMAT{
    uint32_t    Version                 : 4;
    uint32_t    InternetHeaderLength    : 4;
    uint32_t    ServiceType             : 8;
    uint32_t    TotalLength             : 16;
    uint32_t    Identification          : 16;
    uint32_t    Flags                   : 3;
    uint32_t    FragmentOffset          : 13;
    uint32_t    TimeToLive              : 8;
    uint32_t    Protocol                : 8;
    uint32_t    HeaderChecksum          : 16;
    uint32_t    SourceAddress           : 32;
    uint32_t    DestinationAddress      : 32;
    uint32_t    Options                 : 24;
    uint32_t    Padding                 : 8;
}IPV4_INTERNET_HEADER_FORMAT, * PIPV4_INTERNET_HEADER_FORMAT;

#define IPV4_INTERNET_HEADER_FOMRAT_SIZE (sizeof(uint32_t) * 6)

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //IP_V4_H
