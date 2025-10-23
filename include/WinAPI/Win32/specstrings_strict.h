/*
 * Copyright 2023 Vitaly Lipatov
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

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