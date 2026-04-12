#include "DrsdCore.h"

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    int             ValueCount
){
    //LouPrint("DRSDCORE.SYS:DrsdCreateProperty():%s\n", Name);
    PDRSD_PROPERTY NewProperty;
    LOUSTATUS Status;


    if((!Device) || (strlen(Name) > DRSD_PROPERTY_NAME_LENGTH)){
        return 0x00;
    }

    NewProperty = LouKeMallocType(DRSD_PROPERTY, KERNEL_GENERIC_MEMORY);
    if(!NewProperty){
        return 0x00;
    }

    NewProperty->Device = Device;
    NewProperty->ValueCount = ValueCount;
    if(ValueCount){
        NewProperty->Values = LouKeMallocArray(UINT64, ValueCount, KERNEL_GENERIC_MEMORY);
        if(!NewProperty->Values){
            goto _PROPERTY_CREATE_FAILED;   
        }
    }

    Status = DrsdModeObjectAdd(Device, &NewProperty->Base, DRSD_MODE_OBJECT_PROPERTY);
    if(Status != STATUS_SUCCESS){
        goto _PROPERTY_CREATE_FAILED;
    }

    NewProperty->Flags = Flags;

    strncpy(NewProperty->Name, Name, DRSD_PROPERTY_NAME_LENGTH);

    LouKeListAddTail(&NewProperty->Head, &Device->ModeConfig.PropertyList);

    //LouPrint("DRSDCORE.SYS:DrsdCreateProperty():%s STATUS_SUCCESS\n", Name);

    return NewProperty;

_PROPERTY_CREATE_FAILED:
    if(NewProperty->Values){
        LouKeFree(NewProperty->Values);
    }
    LouKeFree(NewProperty);
    return 0x00;
}

DRIVER_EXPORT
PDRSD_PROPERTY 
DrsdCreateEnumProperty(
    PDRSD_DEVICE                Device,
    UINT32                      Flags,
    LOUSTR                      Name,
    PDRSD_PROPERTY_ENUM_LIST    Properties,
    int                         ValueCount
){

    PDRSD_PROPERTY NewProperty;
    LOUSTATUS Status;

    Flags |= DRSD_MODE_PROPERTY_ENUM;

    NewProperty = DrsdCreateProperty(Device, Flags, Name, ValueCount);
    if(!NewProperty){
        return 0x00;
    }

    for(int i = 0 ; i < ValueCount; i++){
        Status = DrsdAddEnumProperty(NewProperty, Properties[i].Type, Properties[i].Name);
        if(Status != STATUS_SUCCESS){
            DrsdDestroyProperty(Device, NewProperty);
            return 0x00;
        }
    }

    return NewProperty;
}

DRIVER_EXPORT
void 
DrsdDestroyProperty(
    PDRSD_DEVICE    Device,
    PDRSD_PROPERTY  Property
){
    PDRSD_PROPERTY_ENUM PropertyEnum;
    PDRSD_PROPERTY_ENUM Pt;

    ForEachListEntrySafe(PropertyEnum, Pt, &Property->EnumList, Head){
        LouKeListDeleteAll(&PropertyEnum->Head);
        LouKeFree(PropertyEnum);
    }   

    if(Property->ValueCount){
        LouKeFree(Property->Values);
    }
    DrsdUnregisterModeObject(Device, &Property->Base);
    LouKeListDeleteAll(&Property->Head);
    LouKeFree(Property);
}

DRIVER_EXPORT
LOUSTATUS
DrsdAddEnumProperty(
    PDRSD_PROPERTY  Property,
    UINT64          Value,
    LOUSTR          Name
){
    PDRSD_PROPERTY_ENUM PropertyEnum;
    int Index = 0;
    if((!Property) || (strlen(Name) >= DRSD_PROPERTY_NAME_LENGTH) || (!Name)){
        return STATUS_INVALID_PARAMETER;
    }

    if((!DrsdPropertyTypeIs(Property , DRSD_MODE_PROPERTY_ENUM)) && (!DrsdPropertyTypeIs(Property , DRSD_MODE_PROPERTY_BITMASK))){
        LouPrint("DRSDCORE.SYS:DrsdAddEnumProperty():Input Not Enum Or Bitmask\n");
        return STATUS_INVALID_PARAMETER;
    }else if((DrsdPropertyTypeIs(Property , DRSD_MODE_PROPERTY_BITMASK)) && (Value > 63)){
        LouPrint("DRSDCORE.SYS:DrsdAddEnumProperty():Bitmask Input Excedes A Value Of 63\n");
        return STATUS_INVALID_PARAMETER;
    }

    ForEachListEntry(PropertyEnum, &Property->EnumList, Head){
        if(PropertyEnum->Value == Value){
            LouPrint("DRSDCORE.SYS:DrsdAddEnumProperty():Duplicate Value Detected\n");
            return STATUS_INVALID_PARAMETER;
        }
        Index++;
    }

    if(Index >= Property->ValueCount){
        LouPrint("DRSDCORE.SYS:DrsdAddEnumProperty():Value Overflow Detected\n");
        return STATUS_INVALID_PARAMETER;
    }

    PropertyEnum = LouKeMallocType(DRSD_PROPERTY_ENUM, KERNEL_GENERIC_MEMORY);
    if(!PropertyEnum){
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    strncpy(PropertyEnum->Name, Name, DRSD_PROPERTY_NAME_LENGTH);
    PropertyEnum->Value = Value;
    Property->Values[Index] = Value;
    LouKeListAddTail(&PropertyEnum->Head, &Property->EnumList);
    return STATUS_SUCCESS;
}

static PDRSD_PROPERTY CreateRangeProperty(
    PDRSD_DEVICE    Device, 
    UINT32          Flags,
    LOUSTR          Name,
    UINT64          Min,
    UINT64          Max
){
    PDRSD_PROPERTY Property = DrsdCreateProperty(Device, Flags, Name, 2);
    if(!Property){
        return 0x00;
    }

    Property->Values[0] = Min;
    Property->Values[1] = Max;

    return Property;
}

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateRangeProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    UINT64          Min,
    UINT64          Max
){
    return CreateRangeProperty(
        Device,
        Flags,
        Name,
        Min,
        Max
    );
}

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateSignedRangeProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    INT64           Min,
    INT64           Max
){
    return CreateRangeProperty(
        Device,
        Flags,
        Name,
        (UINT64)Min,
        (UINT64)Max
    );
}

DRIVER_EXPORT
PDRSD_PROPERTY
DrsdCreateObjectProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name,
    UINT32          Type
){
    PDRSD_PROPERTY NewProperty;
    if(!(Flags & DRSD_MODE_PROPERTY_ATOMIC)){
        LouPrint("DRSDCORE.SYS:DrsdCreateObjectProperty():Non Atomic Objects Forbiden\n");
        return 0x00;
    }
    Flags |= DRSD_MODE_PROPERTY_OBJECT;
    NewProperty = DrsdCreateProperty(Device, Flags, Name, 1);
    if(!NewProperty){
        return 0x00;
    }
    NewProperty->Values[0] = Type;
    return NewProperty;
}

DRIVER_EXPORT 
PDRSD_PROPERTY 
DrsdCreateBooleanProperty(
    PDRSD_DEVICE    Device,
    UINT32          Flags,
    LOUSTR          Name
){
    return DrsdCreateRangeProperty(
        Device,
        Flags,
        Name,
        0, 1
    );
}

DRIVER_EXPORT
PDRSD_PROPERTY
DrsdCreateBitmaskProperty(
    PDRSD_DEVICE                Device,
    UINT32                      Flags,
    LOUSTR                      Name,
    PDRSD_PROPERTY_ENUM_LIST    Properties,
    int                         PropertyCount,
    UINT64                      SupportedBits
){
    LOUSTATUS Status;
    int Count;
    PDRSD_PROPERTY Property;
    
    Flags |= DRSD_MODE_PROPERTY_BITMASK;

    for(size_t i = 0 ; i < 64; i++){
        if(SupportedBits & (1ULL << i)){
            Count = i;
        }
    }

    Property = DrsdCreateProperty(Device, Flags, Name, Count);
    if(!Property){
        return 0x00;
    }

    for(size_t i = 0; i < Count; i++){
        if(!(SupportedBits & (1ULL << i))){
            continue;
        }
        Status = DrsdAddEnumProperty(Property, Properties[i].Type, Properties[i].Name);
        if(Status != STATUS_SUCCESS){
            DrsdDestroyProperty(Device, Property);
            return 0x00;
        }
    }
    return Property;
}

DRIVER_EXPORT
PDRSD_PROPERTY_BLOB
DrsdCreateBlobProperty(){

}

DRIVER_EXPORT
void
DrsdPutBlobProperty(
    PDRSD_PROPERTY_BLOB Blob
){  
    if(!Blob){
        return;
    }
    DrsdModeObjectPut(&Blob->Base);
}