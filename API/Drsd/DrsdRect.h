#ifndef _DRSD_RECT_H
#define _DRSD_RECT_H

static inline int DrsdRectWidth(PDRSD_RECT Rect){
    return Rect->X2 - Rect->X1;
}

static inline int DrsdRectHeight(PDRSD_RECT Rect){
    return Rect->Y2 - Rect->Y1;
}

static inline BOOLEAN DrsdRectVisable(PDRSD_RECT Rect){
    return ((DrsdRectWidth(Rect) > 0) && (DrsdRectHeight(Rect) > 0));
}

static inline BOOLEAN DrsdRectEquals(PDRSD_RECT R1, PDRSD_RECT R2){
    return R1->X1 == R2->X1 && R1->X2 == R2->X2 && R1->Y1 == R2->Y1 && R1->Y2 == R2->Y2;
}

DRIVER_EXPORT
void 
DrsdRectRotate(
    PDRSD_RECT  Rect,
    int         Width,
    int         Height,
    UINT        Rotation
);

DRIVER_EXPORT
LOUSTATUS 
DrsdRectCalcHScale(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    int         MinHScale,
    int         MaxHScale,
    int*        OutScale
);

DRIVER_EXPORT
LOUSTATUS
DrsdRectCalcVScale(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    int         MinVScale,
    int         MaxVScale,
    int*        OutScale
);

DRIVER_EXPORT
LOUSTATUS
DrsdRectClipScaled(
    PDRSD_RECT  Source,
    PDRSD_RECT  Destination,
    PDRSD_RECT  Clip,
    BOOLEAN*    Result
);

DRIVER_EXPORT
void
DrsdRectRotateInv(
    PDRSD_RECT  Rect,
    int         Width,
    int         Height,
    UINT        Rotation
);

#endif