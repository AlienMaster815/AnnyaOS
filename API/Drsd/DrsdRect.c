#include "DrsdCore.h"

static 
LOUSTATUS
ClipScaled(
    int     Source,
    int     Destination,
    int*    Clip,
    UINT32* Out
){
    UINT32 Tmp;

    if(!Destination){
        *Out = 0;
        return STATUS_SUCCESS;
    }

    *Clip = MIN(*Clip, Destination);

    LOUSTATUS Status = LouKeRtlUIntMult(Source, Destination, &Tmp);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if(Source < (Destination << 16)){
        *Out = DIVIDE_ROUND_UP(Tmp, Destination);
        return STATUS_SUCCESS;
    }
    *Out = DIVIDE_ROUND_DOWN(Tmp, Destination);
    return STATUS_SUCCESS;
}

static 
LOUSTATUS
DrsdCalcScale(
    int  Source, 
    int  Destination,
    int* OutScale 
){
    *OutScale = 0;
    
    if((Source < 0) || (Destination < 0)){
        LouPrint("DRSDCORE.SYS:DrsdCalcScale():ERROR Invaldid Input\n");
        return STATUS_INVALID_PARAMETER;
    }

    if(Destination == 0){
        return STATUS_SUCCESS;
    }

    if(Source > (Destination << 16)){
        *OutScale = DIVIDE_ROUND_UP(Source, Destination);
        return STATUS_SUCCESS;
    }

    *OutScale = Source / Destination;
    return STATUS_SUCCESS;
}


DRIVER_EXPORT
LOUSTATUS
DrsdRectClipScaled(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    PDRSD_RECT  Clip,
    BOOLEAN*    Result
){
    int Diff;
    LOUSTATUS Status;
    UINT32 NewSourceHeight;
    UINT32 NewSourceWidth;
    Diff = Clip->X1 - Destination->X1;
    if(Diff > 0){
        Status = ClipScaled(DrsdRectWidth(Source), DrsdRectWidth(Destination), &Diff, &NewSourceWidth);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Source->X1 = Source->X2 - NewSourceWidth;
        Destination->X1 += Diff;
    }

    Diff = Clip->Y1 - Destination->Y1;
    if(Diff > 0){
        Status = ClipScaled(DrsdRectHeight(Source), DrsdRectHeight(Destination), &Diff, &NewSourceHeight);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Source->Y1 = Source->Y2 - NewSourceHeight;
        Destination->Y1 += Diff;
    }

    Diff = Destination->X2 - Clip->X2;
    if(Diff > 0){
        Status = ClipScaled(DrsdRectWidth(Source), DrsdRectWidth(Destination), &Diff, &NewSourceWidth);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Source->X2 = Source->X1 + NewSourceWidth;
        Destination->X2 -= Diff;
    }

    Diff = Destination->Y2 - Clip->Y2;
    if(Diff > 0){
        Status = ClipScaled(DrsdRectHeight(Source), DrsdRectHeight(Destination), &Diff, &NewSourceHeight);
        if(Status != STATUS_SUCCESS){
            return Status;
        }
        Source->Y2 = Source->Y1 + NewSourceHeight;
        Destination->Y2 -= Diff;
    }

    return DrsdRectVisable(Destination);
}

DRIVER_EXPORT
LOUSTATUS 
DrsdRectCalcHScale(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    int         MinHScale,
    int         MaxHScale,
    int*        OutScale
){
    if(!OutScale){
        LouPrint("DRSDCORE.SYS:DrsdRectCalcHScale() ERROR OutScale Is Null\n");
        return STATUS_INVALID_PARAMETER;
    }
    int HScale = 0;
    int SourceWidth = DrsdRectWidth(Source);
    int DestinationWidth = DrsdRectWidth(Destination);
    LOUSTATUS Status = DrsdCalcScale(SourceWidth, DestinationWidth, OutScale);
    if(Status != STATUS_SUCCESS){
        return Status;
    }
    
    if((*OutScale < 0) || (DestinationWidth == 0)){
        return STATUS_SUCCESS;
    }

    if((*OutScale < MinHScale) || (*OutScale > MaxHScale)){
        return STATUS_INTEGER_OVERFLOW;
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
LOUSTATUS
DrsdRectCalcVScale(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    int         MinVScale,
    int         MaxVScale,
    int*        OutScale
){
    if(!OutScale){
        LouPrint("DRSDCORE.SYS:DrsdRectCalcVScale():ERROR OutScale Is Null\n");
        return STATUS_INVALID_PARAMETER;
    }

    int SourceHeight = DrsdRectHeight(Source);
    int DestinationHeight = DrsdRectHeight(Destination);
    LOUSTATUS Status = DrsdCalcScale(SourceHeight, DestinationHeight, OutScale);
    if(Status != STATUS_SUCCESS){
        return Status;
    }

    if((*OutScale < 0) || (DestinationHeight == 0)){
        return STATUS_SUCCESS;
    }

    if((*OutScale < MinVScale) || (*OutScale > MaxVScale)){
        return STATUS_INTEGER_OVERFLOW;
    }

    return STATUS_SUCCESS;
}

DRIVER_EXPORT
void 
DrsdRectRotate(
    PDRSD_RECT  Rect,
    int         Width,
    int         Height,
    UINT        Rotation
){
    DRSD_RECT Tmp;

    if(Rotation & (DRSD_MODE_REFLECT_X | DRSD_MODE_REFLECT_Y)){
        Tmp = *Rect;

        if(Rotation & DRSD_MODE_REFLECT_X){
            Rect->X1 = Width - Tmp.X2;
            Rect->X2 = Width - Tmp.X1;
        }

        if(Rotation & DRSD_MODE_REFLECT_Y){
            Rect->Y1 = Height - Tmp.Y2;
            Rect->Y2 = Height - Tmp.Y1;
        }
    }

    switch(Rotation & DRSD_MODE_ROTATE_MASK){
        case DRSD_MODE_ROTATE_0:
            break;
        case DRSD_MODE_ROTATE_90:
            Tmp = *Rect;
            Rect->X1 = Tmp.Y1;
            Rect->X2 = Tmp.Y2;
            Rect->Y1 = Width - Tmp.X2;
            Rect->Y2 = Width - Tmp.X1;
            break;
        case DRSD_MODE_ROTATE_180:
            Tmp = *Rect;
            Rect->X1 = Width - Tmp.X2;
            Rect->X2 = Width - Tmp.X1;
            Rect->Y1 = Height - Tmp.Y2;
            Rect->Y2 = Height - Tmp.Y1;
            break;
        case DRSD_MODE_ROTATE_270:
            Tmp = *Rect;
            Rect->X1 = Height - Tmp.Y2;
            Rect->X2 = Height - Tmp.Y1;
            Rect->Y1 = Tmp.X1;
            Rect->Y2 = Tmp.X2; 
            break;
        default:    
            break;
    }

}

DRIVER_EXPORT
void
DrsdRectRotateInv(
    PDRSD_RECT  Rect,
    int         Width,
    int         Height,
    UINT        Rotation
){
    DRSD_RECT Tmp;
    switch(Rotation & DRSD_MODE_ROTATE_MASK){
        case DRSD_MODE_ROTATE_0:
            break;
        case DRSD_MODE_ROTATE_90:
            Tmp = *Rect;
            Rect->X1 = Width - Tmp.Y2;
            Rect->X2 = Width - Tmp.Y1;
            Rect->Y1 = Tmp.X1;
            Rect->Y2 = Tmp.X2;
            break;
        case DRSD_MODE_ROTATE_180:
            Tmp = *Rect;
            Rect->X1 = Width - Tmp.X2;
            Rect->X2 = Width - Tmp.X1;
            Rect->Y1 = Height - Tmp.Y2;
            Rect->Y2 = Height - Tmp.Y1;
            break;
        case DRSD_MODE_ROTATE_270:
            Tmp = *Rect;
            Rect->X1 = Tmp.Y1;
            Rect->X2 = Tmp.Y2;
            Rect->Y1 = Height - Tmp.X2;
            Rect->Y2 = Height - Tmp.X1;
            break;
        default:
            break;
    } 
    
    if(Rotation & (DRSD_MODE_REFLECT_X | DRSD_MODE_REFLECT_Y)){
        Tmp = *Rect;
        if(Rotation & DRSD_MODE_REFLECT_X){
            Rect->X1 = Width - Tmp.X2;
            Rect->X2 = Width - Tmp.X1;
        }
        if(Rotation & DRSD_MODE_REFLECT_Y){
            Rect->Y1 = Width - Tmp.Y2;
            Rect->Y2 = Width - Tmp.Y1;
        }
    }
}