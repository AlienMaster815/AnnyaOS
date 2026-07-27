#ifndef _DRSD_DLL_H
#define _DRSD_DLL_H

#include <Annya.h>

#define DRSD_API __declspec(dllexport)

struct _DRSD_FB_CONTEXT;

typedef struct _DRSD_FB_CONTEXT{ 
    struct _DRSD_FB_CONTEXT*    Supervisor;
    ListHeader                  Peers;
    ListHeader                  Subordinates;
    int                         XLocation;
    int                         YLocation;
    int                         Width;
    int                         Height;
    UINT16                      BytesPerPixel;
    BOOLEAN                     Dirty;
    UINT32                      Data[];
}DRSD_FB_CONTEXT, * PDRSD_FB_CONTEXT;

#endif
