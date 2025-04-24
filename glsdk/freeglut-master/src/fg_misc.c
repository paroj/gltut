/*
 * fg_misc.c
 *
 * Functions that didn't fit anywhere else...
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Thu Dec 9 1999
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


/* platform-specific colormap functions */
void fgPlatformSetColor(int idx, float r, float g, float b);
float fgPlatformGetColor(int idx, int comp);
void fgPlatformCopyColormap(int win);


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*
 * This functions checks if an OpenGL extension is supported or not
 *
 * XXX Wouldn't this be simpler and clearer if we used strtok()?
 */
int FGAPIENTRY glutExtensionSupported( const char* extension )
{
  const char *extensions, *start;
  const size_t len = strlen( extension );

  /* Make sure there is a current window, and thus a current context available */
  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutExtensionSupported" );
  freeglut_return_val_if_fail( fgStructure.CurrentWindow != NULL, 0 );

  if (strchr(extension, ' '))
    return 0;
  start = extensions = (const char *) glGetString(GL_EXTENSIONS);

  /* XXX consider printing a warning to stderr that there's no current
   * rendering context.
   */
  freeglut_return_val_if_fail( extensions != NULL, 0 );

  while (1) {
     const char *p = strstr(extensions, extension);
     if (!p)
        return 0;  /* not found */
     /* check that the match isn't a super string */
     if ((p == start || p[-1] == ' ') && (p[len] == ' ' || p[len] == 0))
        return 1;
     /* skip the false match and continue */
     extensions = p + len;
  }

  return 0 ;
}

#ifndef GL_INVALID_FRAMEBUFFER_OPERATION
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION_EXT
#define GL_INVALID_FRAMEBUFFER_OPERATION GL_INVALID_FRAMEBUFFER_OPERATION_EXT
#else
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#endif
#endif

#ifndef GL_TABLE_TOO_LARGE
#ifdef GL_TABLE_TOO_LARGE_EXT
#define GL_TABLE_TOO_LARGE GL_TABLE_TOO_LARGE_EXT
#else
#define GL_TABLE_TOO_LARGE 0x8031
#endif
#endif

#ifndef GL_TEXTURE_TOO_LARGE
#ifdef GL_TEXTURE_TOO_LARGE_EXT
#define GL_TEXTURE_TOO_LARGE GL_TEXTURE_TOO_LARGE_EXT
#else
#define GL_TEXTURE_TOO_LARGE 0x8065
#endif
#endif

/*
 * A cut-down local version of gluErrorString to avoid depending on GLU.
 */
static const char* fghErrorString( GLenum error )
{
  switch ( error ) {
  case GL_INVALID_ENUM: return "invalid enumerant";
  case GL_INVALID_VALUE: return "invalid value";
  case GL_INVALID_OPERATION: return "invalid operation";
#ifndef GL_ES_VERSION_2_0
  case GL_STACK_OVERFLOW: return "stack overflow";
  case GL_STACK_UNDERFLOW: return "stack underflow";
#endif
  case GL_OUT_OF_MEMORY: return "out of memory";
  case GL_TABLE_TOO_LARGE: return "table too large";
  case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
  case GL_TEXTURE_TOO_LARGE: return "texture too large";
  default: return "unknown GL error";
  }
}

/*
 * This function reports all the OpenGL errors that happened till now
 */
void FGAPIENTRY glutReportErrors( void )
{
    GLenum error;
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutReportErrors" );
    while( ( error = glGetError() ) != GL_NO_ERROR )
        fgWarning( "GL error: %s", fghErrorString( error ) );
}

/*
 * Control the auto-repeat of keystrokes to the current window
 */
void FGAPIENTRY glutIgnoreKeyRepeat( int ignore )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutIgnoreKeyRepeat" );
    FREEGLUT_EXIT_IF_NO_WINDOW ( "glutIgnoreKeyRepeat" );

    fgStructure.CurrentWindow->State.IgnoreKeyRepeat = ignore ? GL_TRUE : GL_FALSE;
}

/*
 * Set global auto-repeat of keystrokes
 *
 * RepeatMode should be any of:
 *    GLUT_KEY_REPEAT_OFF
 *    GLUT_KEY_REPEAT_ON
 *    GLUT_KEY_REPEAT_DEFAULT
 */
void FGAPIENTRY glutSetKeyRepeat( int repeatMode )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSetKeyRepeat" );

    switch( repeatMode )
    {
    case GLUT_KEY_REPEAT_OFF:
     fgState.KeyRepeat = GLUT_KEY_REPEAT_OFF;
     break;

    case GLUT_KEY_REPEAT_ON:
    case GLUT_KEY_REPEAT_DEFAULT:
     fgState.KeyRepeat = GLUT_KEY_REPEAT_ON;
     break;

    default:
        fgError ("Invalid glutSetKeyRepeat mode: %d", repeatMode);
        break;
    }
}

/*
 *
 */
void FGAPIENTRY glutSetColor(int idx, GLfloat r, GLfloat g, GLfloat b)
{
	FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSetColor" );
	fgPlatformSetColor(idx, r, g, b);
}

/*
 *
 */
GLfloat FGAPIENTRY glutGetColor(int idx, int component)
{
	FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutGetColor" );
	return fgPlatformGetColor(idx, component);
}

/*
 *
 */
void FGAPIENTRY glutCopyColormap(int window)
{
	FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutCopyColormap" );
	fgPlatformCopyColormap(window);
}

/*** END OF FILE ***/
