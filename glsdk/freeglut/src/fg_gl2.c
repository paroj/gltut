/*
 * fg_gl2.c
 *
 * Load OpenGL (ES) 2.0 functions used by fg_geometry
 *
 * Copyright (C) 2012  Sylvain Beucler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <GL/freeglut.h>
#include "fg_internal.h"
#include "fg_gl2.h"

#ifndef GL_ES_VERSION_2_0
/* GLES2 has the corresponding entry points built-in, and these fgh-prefixed
 * names are defined in fg_gl2.h header to reference them, for any other case,
 * define them as function pointers here.
 */
FGH_PFNGLGENBUFFERSPROC fghGenBuffers;
FGH_PFNGLDELETEBUFFERSPROC fghDeleteBuffers;
FGH_PFNGLBINDBUFFERPROC fghBindBuffer;
FGH_PFNGLBUFFERDATAPROC fghBufferData;
FGH_PFNGLENABLEVERTEXATTRIBARRAYPROC fghEnableVertexAttribArray;
FGH_PFNGLDISABLEVERTEXATTRIBARRAYPROC fghDisableVertexAttribArray;
FGH_PFNGLVERTEXATTRIBPOINTERPROC fghVertexAttribPointer;
#endif

void FGAPIENTRY glutSetVertexAttribCoord3(GLint attrib) {
  if (fgStructure.CurrentWindow != NULL)
    fgStructure.CurrentWindow->Window.attribute_v_coord = attrib;
}

void FGAPIENTRY glutSetVertexAttribNormal(GLint attrib) {
  if (fgStructure.CurrentWindow != NULL)
    fgStructure.CurrentWindow->Window.attribute_v_normal = attrib;
}

void FGAPIENTRY glutSetVertexAttribTexCoord2(GLint attrib) {
    if (fgStructure.CurrentWindow != NULL)
        fgStructure.CurrentWindow->Window.attribute_v_texture = attrib;
}

#define LOADFUNC(ptr, type, name)	\
	do { if(!(ptr = (type)glutGetProcAddress(name))) return; } while(0)

void fgInitGL2( void ) {
#ifdef GL_ES_VERSION_2_0
    fgState.HasOpenGL20 = (fgState.MajorVersion >= 2);
#else
    /* TODO: Mesa returns a valid stub function, rather than NULL,
       when we request a non-existent function */
    LOADFUNC(fghGenBuffers, FGH_PFNGLGENBUFFERSPROC, "glGenBuffers");
    LOADFUNC(fghDeleteBuffers, FGH_PFNGLDELETEBUFFERSPROC, "glDeleteBuffers");
    LOADFUNC(fghBindBuffer, FGH_PFNGLBINDBUFFERPROC, "glBindBuffer");
    LOADFUNC(fghBufferData, FGH_PFNGLBUFFERDATAPROC, "glBufferData");
    LOADFUNC(fghVertexAttribPointer, FGH_PFNGLVERTEXATTRIBPOINTERPROC, "glVertexAttribPointer");
    LOADFUNC(fghEnableVertexAttribArray, FGH_PFNGLENABLEVERTEXATTRIBARRAYPROC, "glEnableVertexAttribArray");
    LOADFUNC(fghDisableVertexAttribArray, FGH_PFNGLDISABLEVERTEXATTRIBARRAYPROC, "glDisableVertexAttribArray");
    fgState.HasOpenGL20 = 1;
#endif
}
