#ifndef _DRSD_PROPERTY_H
#define _DRSD_PROPERTY_H

#include "DrsdCore.h"

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    int             ValueCount
);

DRIVER_EXPORT
PDRSD_PROPERTY 
DrsdCreateEnumProperty(
    PDRSD_DEVICE                Device,
    UINT32                      Flags,
    LOUSTR                      Name,
    PDRSD_PROPERTY_ENUM_LIST    Properties,
    int                         ValueCount
);

DRIVER_EXPORT
void 
DrsdDestroyProperty(
    PDRSD_DEVICE    Device,
    PDRSD_PROPERTY  Property
);

DRIVER_EXPORT
LOUSTATUS
DrsdAddEnumProperty(
    PDRSD_PROPERTY  Property,
    UINT64          Value,
    LOUSTR          Name
);

DRIVER_EXPORT
PDRSD_PROPERTY
DrsdCreateBitmaskProperty(
    PDRSD_DEVICE                Device,
    UINT32                      Flags,
    LOUSTR                      Name,
    PDRSD_PROPERTY_ENUM_LIST    Properties,
    int                         PropertyCount,
    UINT64                      SupportedBits
);

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateRangeProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    UINT64          Min,
    UINT64          Max
);

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateBooleanProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name
);

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateSignedRangeProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    INT64           Min,
    INT64           Max
);

DRIVER_EXPORT
PDRSD_PROPERTY
DrsdCreateObjectProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    UINT32          Type
);

static inline BOOLEAN DrsdPropertyTypeIs(PDRSD_PROPERTY Property, UINT32 Type){
    if(Property->Flags & DRSD_MODE_PROPERTY_EXTENDED_TYPE){
        return ((Property->Flags & DRSD_MODE_PROPERTY_EXTENDED_TYPE) == Type);
    }
    return Property->Flags & Type;
}

#endif