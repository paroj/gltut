/*
 * fg_display_android.c
 *
 * Window management methods for EGL
 *
 * Copyright (C) 2012, 2014  Sylvain Beucler
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

int fghChooseConfig(EGLConfig* config) {
  EGLint num_config;
  EGLint attributes[32];
  int where = 0;
  ATTRIB_VAL(EGL_SURFACE_TYPE, EGL_WINDOW_BIT);
#ifdef EGL_OPENGL_ES3_BIT
  if (fgDisplay.pDisplay.egl.MinorVersion >= 5 && fgState.MajorVersion >= 3) {
    ATTRIB_VAL(EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT);
  } else
#endif
  if (fgState.MajorVersion >= 2) {
    /*
     * Khronos does not specify a EGL_OPENGL_ES3_BIT outside of the OpenGL extension "EGL_KHR_create_context" and EGL 1.5. There are numerous references on the internet 
     * that say to use EGL_OPENGL_ES3_BIT (pre-EGL 1.5), followed by many saying they can't find it in any headers. In fact, the official updated specification for EGL 
     * does not have any references to OpenGL ES 3.x. Tests have shown that EGL_OPENGL_ES2_BIT will work with ES 3.x.
     */
    ATTRIB_VAL(EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT);
  } else {
    ATTRIB_VAL(EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT);
  }
  /* Technically it's possible to request a standard OpenGL (non-ES)
     context, but currently our build system assumes EGL => GLES */
  /* attribs[i++] = EGL_RENDERABLE_TYPE; */
  /* attribs[i++] = EGL_OPENGL_BIT; */
#ifdef TARGET_HOST_BLACKBERRY
  /* Only 888 and 565 seem to work. Based on
       http://qt.gitorious.org/qt/qtbase/source/893deb1a93021cdfabe038cdf1869de33a60cbc9:src/plugins/platforms/qnx/qqnxglcontext.cpp and
       https://twitter.com/BlackBerryDev/status/380720927475912706 */
  ATTRIB_VAL(EGL_BLUE_SIZE, 8);
  ATTRIB_VAL(EGL_GREEN_SIZE, 8);
  ATTRIB_VAL(EGL_RED_SIZE, 8);
#else
  ATTRIB_VAL(EGL_BLUE_SIZE, 1);
  ATTRIB_VAL(EGL_GREEN_SIZE, 1);
  ATTRIB_VAL(EGL_RED_SIZE, 1);
#endif
  ATTRIB_VAL(EGL_ALPHA_SIZE, (fgState.DisplayMode & GLUT_ALPHA) ? 1 : 0);
  ATTRIB_VAL(EGL_DEPTH_SIZE, (fgState.DisplayMode & GLUT_DEPTH) ? 1 : 0);
  ATTRIB_VAL(EGL_STENCIL_SIZE, (fgState.DisplayMode & GLUT_STENCIL) ? 1 : 0);
  ATTRIB_VAL(EGL_SAMPLE_BUFFERS, (fgState.DisplayMode & GLUT_MULTISAMPLE) ? 1 : 0);
  ATTRIB_VAL(EGL_SAMPLES, (fgState.DisplayMode & GLUT_MULTISAMPLE) ? fgState.SampleNumber : 0);
  ATTRIB(EGL_NONE);

  if (!eglChooseConfig(fgDisplay.pDisplay.egl.Display,
               attributes, config, 1, &num_config)) {
    fgWarning("eglChooseConfig: error %x\n", eglGetError());
    return 0;
  }

  return 1;
}

/**
 * Initialize an EGL context for the current display.
 */
EGLContext fghCreateNewContextEGL( SFG_Window* window ) {
  EGLContext context;
  EGLint ver = -1;

  EGLDisplay eglDisplay = fgDisplay.pDisplay.egl.Display;
  EGLConfig eglConfig = window->Window.pContext.egl.Config;

  /* On GLES, user specifies the target version with glutInitContextVersion */
  EGLint attributes[32];
  int where = 0;
  ATTRIB_VAL(EGL_CONTEXT_CLIENT_VERSION, fgState.MajorVersion);
#ifdef EGL_CONTEXT_MINOR_VERSION
  if (fgDisplay.pDisplay.egl.MinorVersion >= 5) {
    /* EGL_CONTEXT_CLIENT_VERSION == EGL_CONTEXT_MAJOR_VERSION */
    ATTRIB_VAL(EGL_CONTEXT_MINOR_VERSION, fgState.MinorVersion);
  }
#endif
  ATTRIB(EGL_NONE);

  context = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, attributes);
  if (context == EGL_NO_CONTEXT) {
    fgWarning("Cannot initialize EGL context, err=%x\n", eglGetError());
    fghContextCreationError();
  }

  eglQueryContext(fgDisplay.pDisplay.egl.Display, context, EGL_CONTEXT_CLIENT_VERSION, &ver);
  if (ver < fgState.MajorVersion) {
    fgError("Wrong GLES major version: %d\n", ver);
  }
#ifdef EGL_CONTEXT_MINOR_VERSION
  if (fgDisplay.pDisplay.egl.MinorVersion >= 5) {
    eglQueryContext(fgDisplay.pDisplay.egl.Display, context, EGL_CONTEXT_MINOR_VERSION, &ver);
    if (ver < fgState.MinorVersion) {
      fgError("Wrong GLES minor version: %d\n", ver);
    }
  }
#endif

  return context;
}

void fgPlatformSetWindow ( SFG_Window *window )
{
  if ( window != fgStructure.CurrentWindow && window) {
    if (eglMakeCurrent(fgDisplay.pDisplay.egl.Display,
               window->Window.pContext.egl.Surface,
               window->Window.pContext.egl.Surface,
               window->Window.Context) == EGL_FALSE)
      fgError("eglMakeCurrent: err=%x\n", eglGetError());
  }
}

/*
 * Really opens a window when handle is available
 */
void fghPlatformOpenWindowEGL( SFG_Window* window )
{
  EGLDisplay display = fgDisplay.pDisplay.egl.Display;
  EGLConfig  config  = window->Window.pContext.egl.Config;

  EGLSurface surface = eglCreateWindowSurface(display, config, window->Window.Handle, NULL);
  if (surface == EGL_NO_SURFACE)
    fgError("Cannot create EGL window surface, err=%x\n", eglGetError());
  window->Window.pContext.egl.Surface = surface;

  fgPlatformSetWindow(window);

  /* EGLint w, h; */
  /* eglQuerySurface(display, surface, EGL_WIDTH, &w); */
  /* eglQuerySurface(display, surface, EGL_HEIGHT, &h); */

}

/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fghPlatformCloseWindowEGL( SFG_Window* window )
{
  /* Based on fg_window_mswin fgPlatformCloseWindow */
  if( fgStructure.CurrentWindow == window )
    eglMakeCurrent(fgDisplay.pDisplay.egl.Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

  if (window->Window.Context != EGL_NO_CONTEXT) {
    /* Step through the list of windows. If the rendering context is not being used by another window, then delete it */
    {
      GLboolean used = GL_FALSE;
      SFG_Window *iter;

      for( iter = (SFG_Window*)fgStructure.Windows.First;
           iter && used == GL_FALSE;
           iter = (SFG_Window*)iter->Node.Next)
      {
        if( (iter->Window.Context == window->Window.Context) &&
            (iter != window) )
          used = GL_TRUE;
      }

      if( !used )
        eglDestroyContext(fgDisplay.pDisplay.egl.Display, window->Window.Context);
    }
    window->Window.Context = EGL_NO_CONTEXT;
  }

  if (window->Window.pContext.egl.Surface != EGL_NO_SURFACE) {
    eglDestroySurface(fgDisplay.pDisplay.egl.Display, window->Window.pContext.egl.Surface);
    window->Window.pContext.egl.Surface = EGL_NO_SURFACE;
  }
}
