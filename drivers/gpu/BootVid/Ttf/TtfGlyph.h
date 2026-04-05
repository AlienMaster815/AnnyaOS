//Copyright GPL-2 Tyler Grenier (2026)
#ifndef _TTF_GLYPH_H
#define _TTF_GLYPH_H

#include "../BootVid.h"

typedef WORD FWORD, PFWORD;

//TTF Spec Glphy Metadata
typedef struct PACKED _TTF_GLPYH_DESCRIPTION{
    INT16       ContourCount;
    FWORD       XMin;
    FWORD       YMin;
    FWORD       XMax;
    FWORD       YMax;
}TTF_GLPYH_DESCRIPTION, * PTTF_GLPYH_DESCRIPTION;

//typedef struct PACKED _TTF_SIMPLE_GLYPH_DEFINITION{

//}TTF_SIMPLE_GLYPH_DEFINITION, * PTTF_SIMPLE_GLYPH_DEFINITION;



//end

LOUSTATUS 
TtfParseGlyphData(
    PVOID                   File, 
    PTTFOBJ_TABLE_DIRECTORY Directory,
    PTTF_OBJECT             TtfObject
);

#endif