#include "DrsdCore.h"

static DRSD_PROPERTY_ENUM_LIST DrsdPlaneTypeEnumList[] = {
    {OVERLAY_PLANE, "Overlay"},
    {PRIMARY_PLANE, "Primary"},
    {CURSOR_PLANE, "Cursor"},
};

static 
LOUSTATUS
DrsdModeCreateStandardProperties(
    PDRSD_DEVICE    Device
){
    LOUSTATUS Status;
    PDRSD_PROPERTY Property;

    Status = DrsdConnectorCreateStandardProperties(Device);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    
    Property = DrsdCreateEnumProperty(Device, DRSD_MODE_PROPERTY_IMMUTABLE, "Type", DrsdPlaneTypeEnumList, ARRAY_SIZE(DrsdPlaneTypeEnumList));
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PlaneTypeProperty = Property;

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "SRC_X", 0, UINT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropSrcX = Property;

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "SRC_Y", 0, UINT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropSrcY = Property;    

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "SRC_W", 0, UINT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropSrcW = Property;

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "SRC_H", 0, UINT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropSrcH = Property;

    Property = DrsdCreateSignedRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "CRTC_Y", INT32_MIN, INT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropCrtcY = Property;

    Property = DrsdCreateSignedRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "CRTC_X", INT32_MIN, INT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropCrtcX = Property;

    Property = DrsdCreateSignedRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "CRTC_W", INT32_MIN, INT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropCrtcW = Property;

    Property = DrsdCreateSignedRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "CRTC_H", INT32_MIN, INT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropCrtcH = Property;

    Property = DrsdCreateObjectProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "FB_ID", DRSD_MODE_OBJECT_FB);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropFbId = Property;    

    Property = DrsdCreateSignedRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "IN_FENCE_FD", -1, INT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropInFenceFd = Property;    

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "OUT_FENCE_PTR", 0, UINT64_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropOutFencePtr = Property;    

    Property = DrsdCreateObjectProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "CRTC_ID", DRSD_MODE_OBJECT_CRTC);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropCrtcId = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_ATOMIC | DRSD_MODE_PROPERTY_BLOB, "FB_DAMAGE_CLIPS", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropFbDamageClips = Property;

    Property = DrsdCreateBooleanProperty(Device, DRSD_MODE_PROPERTY_ATOMIC, "ACTIVE");
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropActive = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_ATOMIC | DRSD_MODE_PROPERTY_BLOB, "MODE_ID", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropModeId = Property;

    Property = DrsdCreateBooleanProperty(Device, 0, "VRR_ENABLED");
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.PropVrrEnabled = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_BLOB, "DEGAMMA_LUT", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    Device->ModeConfig.DeGammaLutProperty = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_BLOB, "CTM", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.CtmProperty = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_BLOB, "GAMMA_LUT", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.GammaLutProperty = Property;

    Property = DrsdCreateRangeProperty(Device, DRSD_MODE_PROPERTY_BLOB, "GAMMA_LUT_SIZE", 0, UINT32_MAX);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.GammaLutSizeProperty = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_IMMUTABLE | DRSD_MODE_PROPERTY_BLOB, "IN_FORMATS", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.ModifiersProperty = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_IMMUTABLE | DRSD_MODE_PROPERTY_BLOB, "IN_FORMATS_ASYNC", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.ASyncModifiersProperty = Property;

    Property = DrsdCreateProperty(Device, DRSD_MODE_PROPERTY_IMMUTABLE | DRSD_MODE_PROPERTY_BLOB, "SIZE_HINTS", 0);
    if(!Property){
        return STATUS_INSUFFICIENT_RESOURCES;
    }    
    Device->ModeConfig.SizeHintsProperty = Property;

    return STATUS_SUCCESS;
}

DRIVER_EXPORT 
LOUSTATUS 
DrsdModeConfigInit(
    PDRSD_DEVICE Device
){
    LOUSTATUS Status;
    LouPrint("DrsdModeConfigInit\n");

    LouKeLouQInitializeWork(&Device->ModeConfig.ConnectorFreeWork, DrsdConnectorFreeWorkFunction, &Device->ModeConfig.ConnectorFreeWork);

    Status = DrsdModeCreateStandardProperties(Device);
    if(Status != STATUS_SUCCESS){
        LouPrint("DrsdModeConfigInit:ERROR Unable To Create Standard Properties\n");
        //TODO:Mode Config Cleanup
        while(1);
        return Status;
    }

    Device->ModeConfig.FbCount = 0;
    Device->ModeConfig.ConnectorCount = 0;
    Device->ModeConfig.CrtcCount = 0;
    Device->ModeConfig.EncoderCount = 0;
    Device->ModeConfig.TotalPlaneCount = 0;
    Device->ModeConfig.ColorOpCount = 0;

    //TODO: CONFIG_LOCKDEP

    LouPrint("DrsdModeConfigInit STATUS_SUCCESS\n");
    return STATUS_SUCCESS;
}