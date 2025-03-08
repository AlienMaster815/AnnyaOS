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

#define IPV4_INTERNET_HEADER_FOMRAT_SIZE (sizeof(uint32_t) * 6)

#define IPV4_SECURITY_S_FEILD_UNCLASIFIED       0b0000000000000000
#define IPV4_SECURUTY_S_FEILD_CONFIDENTIAL      0b1111000100110101
#define IPV4_SECURITY_S_FIELD_EFTO              0b1011110001001101
#define IPV4_SECURITY_S_FEILD_MMMM              0b1011110001001101
#define IPV4_SECURITY_S_FEILD_PROG              0b0101111000100110
#define IPV4_SECURITY_S_FEILD_RESTRICTED        0b1010111100010011
#define IPV4_SECURITY_S_FEILD_SECRET            0b1101011110001000
#define IPV4_SECURITY_S_FIELD_TOP_SECRET        0b0110101111000101

#define IPV4_TIMESTAMP_TIMESTAMP_ONLY   0
#define IPV4_TIMESTAMP_IARE             1
#define IPV4_TIMESTAMP_IAFAP            3

typedef struct _IPV4_SERVICE_TYPE{
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
    uint8_t     VersionAndIHL;
    uint8_t     ServiceType;
    uint16_t    TotalLength;
    uint16_t    Identification;
    uint16_t    FlagsAndFrameOffset;
    uint8_t     TimeToLive;
    uint8_t     Protocol;
    uint16_t    HeaderChecksum;
    uint32_t    SourceAddress;
    uint32_t    DestinationAddress;
    uint32_t    OptionsAndPadding;
}IPV4_INTERNET_HEADER_FORMAT, * PIPV4_INTERNET_HEADER_FORMAT;


typedef struct _IPV4_NO_OPERATION{
    uint8_t Type; //1
}IPV4_NO_OPERATION, * PIPV4_NO_OPERATION;

typedef struct _IPV4_SECURITY{
    uint8_t     Type; //130
    uint8_t     Length; //11
    uint16_t    Security;
    uint16_t    Compartment;
    uint16_t    HandleingRestriction;
    uint32_t    TransmissionControlCode; //24 bits
}IPV4_SECURITY, * PIPV4_SECURITY;

typedef struct _IPV4_LOOSE_SOURCE_AND_RECORD_ROUTE{
    uint8_t     Type;
    uint8_t     Length;
    uint8_t     Pointer;
    uint32_t    RouteData[];
}IPV4_LOOSE_SOURCE_AND_RECORD_ROUTE, * PIPV4_LOOSE_SOURCE_AND_RECORD_ROUTE;

typedef struct _IPV4_STREAM_ID{
    uint8_t     Type; //136
    uint8_t     Length;
    uint16_t    StreamId;
}IPV4_STREAM_ID,  * PIPV4_STREAM_ID;

typedef struct _IPV4_INTERNET_TIMESTAMP{
    uint8_t     Type; //68
    uint8_t     Length;
    uint8_t     Pointer;
    uint8_t     OverFlowAndFlags;
    uint32_t    InternetAddress;
    uint32_t    TimeStamp;
    uint32_t    Padding[];
}IPV4_INTERNET_TIMESTAMP, * PIPV4_INTERNET_TIMESTAMP;


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //IP_V4_H
