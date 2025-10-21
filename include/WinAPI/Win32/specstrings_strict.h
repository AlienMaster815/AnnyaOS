#ifndef _SPECSTRINGS_STRICT_H
#define _SPECSTRINGS_STRICT_H

#ifndef __SPECSTRINGS_STRICT_LEVEL
#define __SPECSTRINGS_STRICT_LEVEL 1
#endif

#if !defined(_midl) && !defined(__WIDL__) && (__SPECSTRINGS_STRICT_LEVEL > 0)

#define __field_bcount(Size)
#define __field_ecount(Size)
#define __field_xcount(Size)
#define __success(Status)

#ifdef _MSC_VER
#define __in
#define __out
#define __reserved
#endif

#endif
#endif