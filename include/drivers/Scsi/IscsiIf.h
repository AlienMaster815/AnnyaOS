#ifndef _ISCSI_IF_H
#define _ISCSI_IF_H

#ifdef __cplusplus
#include <LouDDK.h>
extern "C" {
#else
#include <LouAPI.h>
#endif

#define ISCSI_TARGET_DISCOVER_SEND_TARGETS      1
#define ISCSI_TARGET_DISCOVER_ISNS              2
#define ISCSI_TARGET_DISCOVER_SLP               3

#define ISCSI_HOST_EVENT_LINK_UP                1
#define ISCSI_HOST_EVENT_LINK_DOWN              2
#define ISCSI_HOST_EVENT_MAX                    3

typedef struct _ISCSI_CREATE_SESSION_IO_REQUEST{
    uint32_t    InitialCommand;
    uint16_t    MaximumCommand;
    uint16_t    QueueDepth;
}ISCSI_CREATE_SESSION_IO_REQUEST, * PISCSI_CREATE_SESSION_IO_REQUEST;

typedef struct _ISCSI_CREATE_BOUND_SESSION_IO_REQUEST{
    uint64_t    IORequestHandle;
    uint32_t    InitialCommand;
    uint16_t    MaximumCommand;
    uint16_t    QueueDepth;
}ISCSI_CREATE_BOUND_SESSION_IO_REQUEST, * PISCSI_CREATE_BOUND_SESSION_IO_REQUEST;;

typedef struct _ISCSI_DESTROY_SESSION_IO_REQUEST{
    uint32_t    SessionIdentification;
}ISCSI_DESTROY_SESSION_IO_REQUEST, * PISCSI_DESTROY_SESSION_IO_REQUEST;

typedef struct _ISCSI_CREATE_CONNECTION_IO_REQUEST{
    uint32_t SessionIdentification;
    uint32_t ConnectionIdentification;
}ISCSI_CREATE_CONNECTION_IO_REQUEST, * PISCSI_CREATE_CONNECTION_IO_REQUEST;

typedef struct _ISCSI_BIND_CONNECTION_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
    uint64_t    IORequestHandle;
    uint32_t    Leading;
}ISCSI_BIND_CONNECTION_IO_REQUEST, * PISCSI_BIND_CONNECTION_IO_REQUEST;

typedef struct _ISCSI_DESTROY_CONNECTION_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
}ISCSI_DESTROY_CONNECTION_IO_REQUEST, * PISCSI_DESTROY_CONNECTION_IO_REQUEST;

typedef struct _ISCSI_SEND_PDU_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
    uint32_t    HeaderSize;
    uint32_t    DataSize;
}ISCSI_SEND_PDU_IO_REQUEST, * PISCSI_SEND_PDU_IO_REQUEST;

typedef struct _ISCSI_SET_PARAMETERS_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
    uint32_t    Parameters;
    uint32_t    Length;
}ISCSI_SET_PARAMETERS_IO_REQUEST, * PISCSI_SET_PARAMETERS_IO_REQUEST;

typedef struct _ISCSI_START_CONNECTION_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
}ISCSI_START_CONNECTION_IO_REQUEST, * PISCSI_START_CONNECTION_IO_REQUEST;

typedef struct _ISCSI_STOP_CONNECTION_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
    uint64_t    ConnectionHandle;
    uint32_t    Flags;
}ISCSI_STOP_CONNECTION_IO_REQUEST, * PISCSI_STOP_CONNECTION_IO_REQUEST;

typedef struct _ISCSI_GET_STATUS_IO_REQUEST{
    uint32_t    SessionIdentification;
    uint32_t    ConnectionIdentification;
}ISCSI_GET_STATUS_IO_REQUEST, * PISCSI_GET_STATUS_IO_REQUEST;

typedef struct _ISCSI_CONNECT_TRANSPORT_IO_REQUEST{
    uint32_t    NonBlocking;
}ISCSI_CONNECT_TRANSPORT_IO_REQUEST, * PISCSI_CONNECT_TRANSPORT_IO_REQUEST;

typedef struct _ISCSI_CONNECT_TRANSPORT_THROGUH_HOST_IO_REQUEST{
    uint32_t    HostNumber;
    uint32_t    NonBlocking;
}ISCSI_CONNECT_TRANSPORT_THROGUH_HOST_IO_REQUEST, * PISCSI_CONNECT_TRANSPORT_THROGUH_HOST_IO_REQUEST;

typedef struct _ISCSI_POLL_TRANSPORT_IO_REQUEST{
    uint32_t    IORequestHandle;
    uint32_t    TimeoutQuarks;
}ISCSI_POLL_TRANSPORT_IO_REQUEST, * PISCSI_POLL_TRANSPORT_IO_REQUEST;

typedef struct _ISCSI_DISCONNECT_TRANSPORT_IO_REQUEST{
    uint64_t    IORequestHandle;
}ISCSI_DISCONNECT_TRANSPORT_IO_REQUEST, * PISCSI_DISCONNECT_TRANSPORT_IO_REQUEST;

typedef struct _ISCSI_TARGET_DISCOVER_IO_REQUEST{
    uint32_t    DiscoverTyped;
    uint32_t    HostNumber;
    uint32_t    Enable;
}ISCSI_TARGET_DISCOVER_IO_REQUEST, * PISCSI_TARGET_DISCOVER_IO_REQUEST;

typedef struct _ISCSI_SET_HOST_PARAMETER_IO_REQUEST{
    uint32_t    HostNumber;
    uint32_t    Parameter;
    uint32_t    Length;
}ISCSI_SET_HOST_PARAMETER_IO_REQUEST, * PISCSI_SET_HOST_PARAMETER_IO_REQUEST;

typedef struct _ISCSI_SET_PATH_IO_REQUEST{
    uint32_t    HostNumber;
}ISCSI_SET_PATH_IO_REQUEST, * PISCSI_SET_PATH_IO_REQUEST;

typedef struct _ISCSI_SET_INTERFACE_PARAMETERS_IO_REQUEST{
    uint32_t    HostNumber;
    uint32_t    Count;
}ISCSI_SET_INTERFACE_PARAMETERS_IO_REQUEST, * PISCSI_SET_INTERFACE_PARAMETERS_IO_REQUEST;

typedef struct _LOUSINE_ISCSI_IO_STACK_OBJECT{
    ListHeader  StackWalker;
    uint32_t    EventType;
    uint32_t    InterfaceError;
}LOUSINE_ISCSI_IO_STACK_OBJECT, * PLOUSINE_ISCSI_IO_STACK_OBJECT;

#ifdef __cplusplus
}
#endif

#endif //_ISCSI_IF_H