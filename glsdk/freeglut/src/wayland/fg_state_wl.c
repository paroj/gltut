/*
 * fg_state_wl.c
 *
 * Wayland-specific freeglut state query methods.
 *
 * Copyright (c) 2015 Manuel Bachmann. All Rights Reserved.
 * Written by Manuel Bachmann, <tarnyko@tarnyko.net>
 * Creation date: Sun Mar 23 2015
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
 * MANUEL BACHMANN BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <GL/freeglut.h>
#include "fg_internal.h"
#include "egl/fg_state_egl.h"

int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
    switch( eWhat )
    {
    case GLUT_HAS_KEYBOARD:
        if( fgDisplay.pDisplay.keyboard )
          return 1;
        else
          return 0;

    case GLUT_HAS_MOUSE:
        /* we want the touchscreen to behave like a mouse,
         * so let us pretend it is one.
         */
        if( fgDisplay.pDisplay.pointer ||
            fgDisplay.pDisplay.touch )
          return 1;
        else
          return 0;

    case GLUT_NUM_MOUSE_BUTTONS:
        /* Wayland has no way of telling us how much buttons
         * a mouse has, unless the actual event gets sent to
         * the client. As we are only handling 3 buttons
         * currently, return this fixed number for now.
         */
        if( fgDisplay.pDisplay.pointer )
          return 3;
        /* touchscreen is considered as having one button */
        else if( fgDisplay.pDisplay.touch )
          return 1;
        else
          return 0;

    default:
        fgWarning( "glutDeviceGet(): missing enum handle %d", eWhat );
        return -1;
    }
}


int fgPlatformGlutGet ( GLenum eWhat )
{
    switch( eWhat )
    {

    /*
     * Those calls are pointless under Wayland, so inform the user
     */
    case GLUT_WINDOW_X:
    case GLUT_WINDOW_Y:
    {
        if( fgStructure.CurrentWindow == NULL )
        {
            return 0;
        }
        else
        {
            fgWarning( "glutGet(): GLUT_WINDOW_X/Y properties "
                                   "unsupported under Wayland" );
            return -1;
        }
    }

    /*
     * TODO : support this correctly once we will start drawing
     *  client-side decorations
     */
    case GLUT_WINDOW_BORDER_WIDTH:
    case GLUT_WINDOW_HEADER_HEIGHT:
    {
        if( fgStructure.CurrentWindow == NULL ||
            fgStructure.CurrentWindow->Parent )
            /* can't get widths/heights if no current window
             * and child windows don't have borders */
            return 0;

        return 0;
    }

    case GLUT_WINDOW_WIDTH:
    case GLUT_WINDOW_HEIGHT:
    {
        if( fgStructure.CurrentWindow == NULL )
            return 0;

        switch ( eWhat )
        {
        case GLUT_WINDOW_WIDTH:
            return fgStructure.CurrentWindow->State.Width;
        case GLUT_WINDOW_HEIGHT:
            return fgStructure.CurrentWindow->State.Height;
        }
    }

    /* Colormap size is handled in a bit different way than all the rest */
    case GLUT_WINDOW_COLORMAP_SIZE:
    {
        if( fgStructure.CurrentWindow == NULL )
        {
            return 0;
        }
        else
        {
            int result = 0;
	    if ( ! eglGetConfigAttrib( fgDisplay.pDisplay.egl.Display,
                     fgStructure.CurrentWindow->Window.pContext.egl.Config,
                     EGL_BUFFER_SIZE, &result ) )
	      fgError( "eglGetConfigAttrib(EGL_BUFFER_SIZE) failed" );

            return result;
        }
    }

    default:
      return fghPlatformGlutGetEGL( eWhat );
    }
}

