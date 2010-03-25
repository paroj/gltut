/* -*- C++ -*-
 * File: libraw_version.h
 * Copyright 2008-2009 LibRaw LLC (info@libraw.org)
 * Created: Mon Sept  8, 2008 
 *
 * LibRaw (Lite) version info
 *
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __VERSION_H
#define __VERSION_H

#define LIBRAW_MAJOR_VERSION  0
#define LIBRAW_MINOR_VERSION  7
#define LIBRAW_PATCH_VERSION  2
#define LIBRAW_VERSION_TAIL   Release(Lite)

#define _LIBRAW_VERSION_MAKE(a,b,c,d) #a"."#b"."#c"-"#d
#define LIBRAW_VERSION_MAKE(a,b,c,d) _LIBRAW_VERSION_MAKE(a,b,c,d)

#define LIBRAW_VERSION_STR LIBRAW_VERSION_MAKE(LIBRAW_MAJOR_VERSION,LIBRAW_MINOR_VERSION,LIBRAW_PATCH_VERSION,LIBRAW_VERSION_TAIL)

#define LIBRAW_MAKE_VERSION(major,minor,patch) \
    (((major) << 16) | ((minor) << 8) | (patch))

#define LIBRAW_VERSION \
    LIBRAW_MAKE_VERSION(LIBRAW_MAJOR_VERSION,LIBRAW_MINOR_VERSION,LIBRAW_PATCH_VERSION)

#define LIBRAW_CHECK_VERSION(major,minor,patch) \
    ( LibRaw::versionNumber() >= LIBRAW_MAKE_VERSION(major,minor,patch) )


#endif
