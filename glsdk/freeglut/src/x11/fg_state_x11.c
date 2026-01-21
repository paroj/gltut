/*
 * fg_state_x11.c
 *
 * X11-specific freeglut state query methods.
 *
 * Copyright (c) 2012 Stephen J. Baker. All Rights Reserved.
 * Written by John F. Fay, <fayjf@sourceforge.net>
 * Creation date: Sat Feb 4 2012
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
#ifdef EGL_VERSION_1_0
#include "egl/fg_state_egl.h"
#else
#include "x11/fg_state_x11_glx.h"
#endif

int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
    switch( eWhat )
    {
    case GLUT_HAS_KEYBOARD:
        /*
         * X11 has a core keyboard by definition, although it can
         * be present as a virtual/dummy keyboard. For now, there
         * is no reliable way to tell if a real keyboard is present.
         */
        return 1;

    /* X11 has a mouse by definition */
    case GLUT_HAS_MOUSE:
        return 1 ;

    case GLUT_NUM_MOUSE_BUTTONS:
        /* We should be able to pass NULL when the last argument is zero,
         * but at least one X server has a bug where this causes a segfault.
         *
         * In XFree86/Xorg servers, a mouse wheel is seen as two buttons
         * rather than an Axis; "fg_main.c" expects this when
         * checking for a wheel event.
         */
        {
            unsigned char map;
            int nbuttons = XGetPointerMapping(fgDisplay.pDisplay.Display, &map,0);
            return nbuttons;
        }

    default:
        fgWarning( "glutDeviceGet(): missing enum handle %d", eWhat );
        break;
    }

    /* And now -- the failure. */
    return -1;
}


int fgPlatformGlutGet ( GLenum eWhat )
{
    switch( eWhat )
    {

    /*
     * Those calls are somewhat similar, as they use XGetWindowAttributes()
     * function
     */
    case GLUT_WINDOW_X:
    case GLUT_WINDOW_Y:
    {
        int x, y;
        Window p,w;

        if( fgStructure.CurrentWindow == NULL )
            return 0;

        if (fgStructure.CurrentWindow->Parent)
            /* For child window, we should return relative to upper-left
             * of parent's client area.
             */
            p = fgStructure.CurrentWindow->Parent->Window.Handle;
        else
            p = fgDisplay.pDisplay.RootWindow;
            
        XTranslateCoordinates(
            fgDisplay.pDisplay.Display,
            fgStructure.CurrentWindow->Window.Handle,
            p,
            0, 0, &x, &y, &w);

        switch ( eWhat )
        {
        case GLUT_WINDOW_X: return x;
        case GLUT_WINDOW_Y: return y;
        }
    }
    
    case GLUT_WINDOW_BORDER_WIDTH:
    case GLUT_WINDOW_HEADER_HEIGHT:
    {
        Atom actual_type, net_extents;
        int actual_format;
        unsigned long nitems, bytes_after;
        unsigned char *data = NULL;
        int result, top, left;
        
        if (fgStructure.CurrentWindow == NULL || fgStructure.CurrentWindow->Parent)
            /* can't get widths/heights if no current window
             * and child windows don't have borders */
            return 0;
        
        /* try to get through _NET_FRAME_EXTENTS */
        net_extents = XInternAtom(fgDisplay.pDisplay.Display, "_NET_FRAME_EXTENTS", False);
        
        result = XGetWindowProperty(
            fgDisplay.pDisplay.Display, fgStructure.CurrentWindow->Window.Handle, net_extents,
            0, 4, False, AnyPropertyType, 
            &actual_type, &actual_format, 
            &nitems, &bytes_after, &data);

        if (result == Success && nitems == 4 && bytes_after == 0)
            /* got the data we expected, here's to hoping that
             * _NET_FRAME_EXTENTS is supported and the data
             * contain sensible values */
        {
            long *extents = (long *)data;
            left = (int) extents[0]; /* we take left as border width, consistent with old logic. bottom and right better be the same... */
            top  = (int) extents[2];
        }
        else
        {
            /* try in the previous way as fall-back */
            Window w;
            int x,y;
            
            XTranslateCoordinates(
                fgDisplay.pDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                fgDisplay.pDisplay.RootWindow,
                0, 0, &x, &y, &w);
            
            if (w == 0)
                /* logic below needs w */
                return 0;
            
            XTranslateCoordinates(
                fgDisplay.pDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                w, 0, 0, &x, &y, &w);  
            
            left = x;
            top  = y;
        }
        if (result == Success)
            XFree(data);

        switch ( eWhat )
        {
        case GLUT_WINDOW_BORDER_WIDTH:  return left;
        case GLUT_WINDOW_HEADER_HEIGHT: return top;
        }
    }

    case GLUT_WINDOW_WIDTH:
    case GLUT_WINDOW_HEIGHT:
    {
        XWindowAttributes winAttributes;

        if( fgStructure.CurrentWindow == NULL )
            return 0;
        XGetWindowAttributes(
            fgDisplay.pDisplay.Display,
            fgStructure.CurrentWindow->Window.Handle,
            &winAttributes
        );
        switch ( eWhat )
        {
        case GLUT_WINDOW_WIDTH:            return winAttributes.width ;
        case GLUT_WINDOW_HEIGHT:           return winAttributes.height ;
        }
    }
    
    /* Colormap size is handled in a bit different way than all the rest */
    case GLUT_WINDOW_COLORMAP_SIZE:
        if(
#ifndef EGL_VERSION_1_0
	   fgPlatformGetConfig( GLX_RGBA ) ||
#endif
	   fgStructure.CurrentWindow == NULL)
        {
            /*
             * We've got a RGBA visual, so there is no colormap at all.
             * The other possibility is that we have no current window set.
             */
            return 0;
        }
        else
        {
          XVisualInfo * visualInfo;
		  int result;
#ifdef EGL_VERSION_1_0
	  EGLint vid = 0;
	  XVisualInfo visualTemplate;
	  int num_visuals;
	  if (!eglGetConfigAttrib(fgDisplay.pDisplay.egl.Display,
				  fgStructure.CurrentWindow->Window.pContext.egl.Config,
				  EGL_NATIVE_VISUAL_ID, &vid))
	    fgError("eglGetConfigAttrib(EGL_NATIVE_VISUAL_ID) failed");
	  visualTemplate.visualid = vid;
	  visualInfo = XGetVisualInfo(fgDisplay.pDisplay.Display, VisualIDMask, &visualTemplate, &num_visuals);
#else
	  {
#ifdef USE_FBCONFIG
          GLXFBConfig fbconfig;

          fbconfig = fgStructure.CurrentWindow->Window.pContext.FBConfig;
          visualInfo = glXGetVisualFromFBConfig(fgDisplay.pDisplay.Display, fbconfig);
#else
          visualInfo = fgStructure.CurrentWindow->Window.pContext.visinf;
#endif
	  }
#endif
          result = visualInfo->visual->map_entries;

#ifdef USE_FBCONFIG
		  /* only free if we got it from glXGetVisualFromFBConfig */
          XFree(visualInfo);
#endif

          return result;
        }

    default:
#ifdef EGL_VERSION_1_0
      return fghPlatformGlutGetEGL(eWhat);
#else
      return fghPlatformGlutGetGLX(eWhat);
#endif
    }
}
