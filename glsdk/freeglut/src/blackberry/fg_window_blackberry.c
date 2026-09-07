/*
 * fg_window_blackberry.c
 *
 * Window management methods for BlackBerry
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Copied for Platform code by Evan Felix <karcaw at gmail.com>
 * Copyright (C) 2012  Sylvain Beucler
 * Copyright (C) 2013  Vincent Simonetti
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

#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"
#include "egl/fg_window_egl.h"
#include <sys/pps.h>

/*
 * Opens a window. Requires a SFG_Window object created and attached
 * to the freeglut structure. OpenGL context is created here.
 */
void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow )
{
    /* TODO: only one full-screen window possible? */
    if (fgDisplay.pDisplay.single_native_window != NULL) {
        fgWarning("You can't have more than one window on BlackBerry");
        return;
    }

    /* Create window */
    screen_window_t sWindow;
    if (screen_create_window(&sWindow, fgDisplay.pDisplay.screenContext)) {
        fgError("Could not create window");
        return;
    }
    fgDisplay.pDisplay.single_native_window = sWindow;

    /* Choose config and screen format */
    fghChooseConfig(&window->Window.pContext.egl.Config);
    int screenFormat = SCREEN_FORMAT_RGBA8888; //Only SCREEN_FORMAT_RGBA8888 and SCREEN_FORMAT_RGB565 are supported. See fg_window_egl for more info
    int configAttri;
#define EGL_QUERY_COMP(att, comp) (eglGetConfigAttrib(fgDisplay.pDisplay.egl.Display, window->Window.pContext.egl.Config, att, &configAttri) == GL_TRUE && (configAttri comp))
    if (EGL_QUERY_COMP(EGL_ALPHA_SIZE, <= 0) && EGL_QUERY_COMP(EGL_RED_SIZE, <= 5) &&
            EGL_QUERY_COMP(EGL_GREEN_SIZE, <= 6) && EGL_QUERY_COMP(EGL_BLUE_SIZE, <= 5)) {
        screenFormat = SCREEN_FORMAT_RGB565;
    }
#undef EGL_QUERY_COMP

    /* Set window properties */
    int orientation = atoi(getenv("ORIENTATION"));
    int screenUsage = SCREEN_USAGE_ROTATION;
#ifdef SCREEN_USAGE_OPENGL_ES3
    if (fgState.MajorVersion >= 3) {
        screenUsage |= SCREEN_USAGE_OPENGL_ES3;
    } else
#endif
    if (fgState.MajorVersion >= 2) {
        screenUsage |= SCREEN_USAGE_OPENGL_ES2;
    } else {
        screenUsage |= SCREEN_USAGE_OPENGL_ES1;
    }
#if !defined(__X86__) && !defined(__PLAYBOOK__)
    screenUsage |= SCREEN_USAGE_DISPLAY; // Physical device copy directly into physical display
#endif
    if (screen_set_window_property_iv(sWindow, SCREEN_PROPERTY_FORMAT, &screenFormat)) {
        screen_destroy_window(sWindow);
        fgError("Could not set window format");
        return;
    }
    if (screen_set_window_property_iv(sWindow, SCREEN_PROPERTY_USAGE, &screenUsage)) {
        screen_destroy_window(sWindow);
        fgError("Could not set window usage");
        return;
    }

    int value[2];
    /* Uncomment when multiple windows are supported
    if(positionUse) {
        value[0] = x;
        value[1] = y;
        if (screen_set_window_property_iv(sWindow, SCREEN_PROPERTY_POSITION, value)) {
            screen_destroy_window(sWindow);
            fgError("Could not set window position");
            return;
        }
    }*/

    if(sizeUse) {
        /* Uncomment when multiple windows are supported
        value[0] = w;
        value[1] = h;
        */
        //TEMP until ^^ is uncommented
        if (screen_get_window_property_iv(sWindow, SCREEN_PROPERTY_BUFFER_SIZE, value)) {
            screen_destroy_window(sWindow);
            fgError("Could not get window mode");
            return;
        }
    } else {
        /* From PlatformBlackBerry in GamePlay3d */
        screen_display_t display;
        if (screen_get_window_property_pv(sWindow, SCREEN_PROPERTY_DISPLAY, (void**)&display)) {
            screen_destroy_window(sWindow);
            fgError("Could not get window display");
            return;
        }

        screen_display_mode_t displayMode;
        if (screen_get_display_property_pv(display, SCREEN_PROPERTY_MODE, (void**)&displayMode)) {
            screen_destroy_window(sWindow);
            fgError("Could not get display mode");
            return;
        }

        if (screen_get_window_property_iv(sWindow, SCREEN_PROPERTY_BUFFER_SIZE, value)) {
            screen_destroy_window(sWindow);
            fgError("Could not get window mode");
            return;
        }

        /* Adjust buffer sizes based on rotation */
        if ((orientation == 0) || (orientation == 180))
        {
            if (((displayMode.width > displayMode.height) && (value[0] < value[1])) ||
                ((displayMode.width < displayMode.height) && (value[0] > value[1])))
            {
                int tmp = value[1];
                value[1] = value[0];
                value[0] = tmp;
            }
        }
        else if ((orientation == 90) || (orientation == 270))
        {
            if (((displayMode.width > displayMode.height) && (value[0] > value[1])) ||
                ((displayMode.width < displayMode.height) && (value[0] < value[1])))
            {
                int tmp = value[1];
                value[1] = value[0];
                value[0] = tmp;
            }
        }
        else
        {
            screen_destroy_window(sWindow);
            fgError("Unexpected rotation angle");
            return;
        }
    }

    /* Set rotation if usage allows it */
    if (screen_set_window_property_iv(sWindow, SCREEN_PROPERTY_ROTATION, &orientation)) {
        screen_destroy_window(sWindow);
        fgError("Could not set window rotation");
        return;
    }
    window->State.pWState.originalRotation = orientation;

    /* Set buffer sizes */
    if (screen_set_window_property_iv(sWindow, SCREEN_PROPERTY_BUFFER_SIZE, value)) {
        screen_destroy_window(sWindow);
        fgError("Could not set window buffer size");
        return;
    }

    /* Create window buffers */
    if (screen_create_window_buffers(sWindow, (fgState.DisplayMode & GLUT_DOUBLE) ? 2 : 1)) {
        screen_destroy_window(sWindow);
        fgError("Could not create window buffers");
        return;
    }

    /* Save window and set state */
    window->Window.Handle = sWindow;
    window->State.WorkMask |= GLUT_INIT_WORK;
    window->State.IsFullscreen = GL_TRUE; //XXX Always fullscreen for now

    /* Create context */
    window->Window.Context = EGL_NO_CONTEXT;
    if( fgState.UseCurrentContext == GL_TRUE )
        window->Window.Context = eglGetCurrentContext();
    if( window->Window.Context == EGL_NO_CONTEXT )
        window->Window.Context = fghCreateNewContextEGL(window);

    /* Create EGL window */
    fghPlatformOpenWindowEGL(window);

    window->State.Visible = GL_TRUE;
}

void fgPlatformFlushCommands()
{
    if(screen_flush_context(fgDisplay.pDisplay.screenContext, 0)) {
        fgWarning("Could not flush screen context");
    }
}

void fgPlatformRotateWindow(SFG_Window* window, int rotation)
{
    if(screen_set_window_property_iv(window->Window.Handle, SCREEN_PROPERTY_ROTATION, &rotation)) {
        fgWarning("Could not set window rotation");
    }
}

/*
 * Request a window resize
 */
void fgPlatformReshapeWindow ( SFG_Window *window, int width, int height )
{
    fprintf(stderr, "fgPlatformReshapeWindow: STUB\n");
}

/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
    fghPlatformCloseWindowEGL(window);

    screen_destroy_window((screen_window_t)window->Window.Handle);
}

/*
 * This function makes the specified window visible
 */
void fgPlatformShowWindow( void )
{
    fprintf(stderr, "fgPlatformShowWindow: STUB\n");
}

/*
 * This function hides the specified window
 */
void fgPlatformHideWindow( SFG_Window *window )
{
    fprintf(stderr, "fgPlatformHideWindow: STUB\n");
}

/*
 * Iconify the specified window (top-level windows only)
 */
void fgPlatformIconifyWindow( SFG_Window *window )
{
#ifndef __PLAYBOOK__
    pps_encoder_t encoder;

    pps_encoder_initialize(&encoder, false);
    pps_encoder_add_string(&encoder, "msg", "minimizeWindow");

    if (navigator_raw_write(pps_encoder_buffer(&encoder), pps_encoder_length(&encoder)) != BPS_SUCCESS) {
        fgWarning("Could not iconify window on BlackBerry");
    }

    pps_encoder_cleanup(&encoder);
#else
    fprintf(stderr, "fgPlatformGlutIconifyWindow: STUB\n");
#endif
}

/*
 * Set the current window's title
 */
void fgPlatformGlutSetWindowTitle( const char* title )
{
    fprintf(stderr, "fgPlatformGlutSetWindowTitle: STUB\n");
}

/*
 * Set the current window's iconified title
 */
void fgPlatformGlutSetIconTitle( const char* title )
{
    //XXX Possibly a window cover label?
    fprintf(stderr, "fgPlatformGlutSetIconTitle: STUB\n");
}

/*
 * Change the specified window's position
 */
void fgPlatformPositionWindow( SFG_Window *window, int x, int y )
{
    fprintf(stderr, "fgPlatformPositionWindow: STUB\n");
}

/*
 * Lowers the specified window (by Z order change)
 */
void fgPlatformPushWindow( SFG_Window *window )
{
    fprintf(stderr, "fgPlatformPushWindow: STUB\n");
}

/*
 * Raises the specified window (by Z order change)
 */
void fgPlatformPopWindow( SFG_Window *window )
{
    fprintf(stderr, "fgPlatformPopWindow: STUB\n");
}

/*
 * Toggle the window's full screen state.
 */
void fgPlatformFullScreenToggle( SFG_Window *win )
{
    fprintf(stderr, "fgPlatformFullScreenToggle: STUB\n");
}
