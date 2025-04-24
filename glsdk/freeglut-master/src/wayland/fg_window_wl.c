/*
 * fg_window_wl.c
 *
 * Window management methods for Wayland
 *
 * Copyright (c) 2015 Manuel Bachmann. All Rights Reserved.
 * Written by Manuel Bachmann, <tarnyko@tarnyko.net>
 * Creation date: Tue Mar 17, 2015
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

#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "../fg_internal.h"
#include "egl/fg_window_egl.h"
#define fghCreateNewContext fghCreateNewContextEGL

extern void fghOnReshapeNotify( SFG_Window *window, int width, int height, GLboolean forceNotify );
void fgPlatformReshapeWindow( SFG_Window *window, int width, int height );
void fgPlatformIconifyWindow( SFG_Window *window );


static void fghShSurfacePing( void* data,
                           struct wl_shell_surface* shsurface,
                           uint32_t serial )
{
    wl_shell_surface_pong( shsurface, serial );
}
static void fghShSurfaceConfigure( void* data,
                                struct wl_shell_surface* shsurface,
                                uint32_t edges,
                                int32_t width, int32_t height )
{
    SFG_Window* window = data;
    fgPlatformReshapeWindow( window, width, height );
}
static const struct wl_shell_surface_listener fghShSurfaceListener =
{
    fghShSurfacePing,
    fghShSurfaceConfigure,
    NULL
};


static int fghToggleFullscreen(void)
{
    SFG_Window* win = fgStructure.CurrentWindow;

    if ( ! win->State.IsFullscreen )
    {
      win->State.pWState.OldWidth = win->State.Width;
      win->State.pWState.OldHeight = win->State.Height;
      wl_shell_surface_set_fullscreen( win->Window.pContext.shsurface,
                                       WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,
                                       0, NULL );
    }
    else
    {
      fgPlatformReshapeWindow( win, win->State.pWState.OldWidth,
                                    win->State.pWState.OldHeight );
      wl_shell_surface_set_toplevel( win->Window.pContext.shsurface );
    }

    return 0;
}

void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow )
{
    /* Save the display mode if we are creating a menu window */
    if( window->IsMenu && ( ! fgStructure.MenuContext ) )
        fgState.DisplayMode = GLUT_DOUBLE | GLUT_RGB ;

    fghChooseConfig( &window->Window.pContext.egl.Config );

    if( ! window->Window.pContext.egl.Config )
    {
        /*
         * The "fghChooseConfig" returned a null meaning that the visual
         * context is not available.
         * Try a couple of variations to see if they will work.
         */
        if( fgState.DisplayMode & GLUT_MULTISAMPLE )
        {
            fgState.DisplayMode &= ~GLUT_MULTISAMPLE ;
            fghChooseConfig( &window->Window.pContext.egl.Config );
            fgState.DisplayMode |= GLUT_MULTISAMPLE;
        }
    }

    FREEGLUT_INTERNAL_ERROR_EXIT( window->Window.pContext.egl.Config != NULL,
                                  "EGL configuration with necessary capabilities "
                                  "not found", "fgOpenWindow" );

    if( ! positionUse )
        x = y = -1; /* default window position */
    if( ! sizeUse )
        w = h = 300; /* default window size */

    /*  Create the cursor  */
   window->Window.pContext.cursor = wl_cursor_theme_get_cursor(
                                      fgDisplay.pDisplay.cursor_theme,
                                      "left_ptr" ); 
   window->Window.pContext.cursor_surface = wl_compositor_create_surface(
                                              fgDisplay.pDisplay.compositor );

    /*  Create the main surface  */
    window->Window.pContext.surface = wl_compositor_create_surface(
                                        fgDisplay.pDisplay.compositor );

    /*  Create the shell surface with respects to the parent/child tree  */
    window->Window.pContext.shsurface = wl_shell_get_shell_surface(
                                          fgDisplay.pDisplay.shell,
                                           window->Window.pContext.surface );
    wl_shell_surface_add_listener( window->Window.pContext.shsurface,
                                   &fghShSurfaceListener, window );

    if( title)
      wl_shell_surface_set_title( window->Window.pContext.shsurface, title );

    if( gameMode )
    {
        window->State.IsFullscreen = GL_TRUE;
        wl_shell_surface_set_fullscreen( window->Window.pContext.shsurface,
                                         WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,
                                         0, NULL );
    }
    else if( !isSubWindow && !window->IsMenu )
    {
        wl_shell_surface_set_toplevel( window->Window.pContext.shsurface );
    }
    else
    {
        wl_shell_surface_set_transient( window->Window.pContext.shsurface,
                                        window->Parent->Window.pContext.surface,
                                        x, y, 0 );
    }

    /*  Create the Wl_EGL_Window  */
    window->Window.Context = fghCreateNewContext( window );
    window->Window.pContext.egl_window = wl_egl_window_create( 
                                           window->Window.pContext.surface,
                                           w, h);
    window->Window.pContext.egl.Surface = eglCreateWindowSurface( 
                              fgDisplay.pDisplay.egl.Display,
                              window->Window.pContext.egl.Config,
                              (EGLNativeWindowType)window->Window.pContext.egl_window,
                              NULL );
    eglMakeCurrent( fgDisplay.pDisplay.egl.Display, window->Window.pContext.egl.Surface,
                    window->Window.pContext.egl.Surface, window->Window.Context );

   window->Window.pContext.pointer_button_pressed = GL_FALSE;
}


/*
 * Request a window resize
 */
void fgPlatformReshapeWindow( SFG_Window *window, int width, int height )
{
    fghOnReshapeNotify(window, width, height, GL_FALSE);

    if( window->Window.pContext.egl_window )
      wl_egl_window_resize( window->Window.pContext.egl_window,
                            width, height, 0, 0 );
}


/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
    fghPlatformCloseWindowEGL(window);

    if ( window->Window.pContext.egl_window )
      wl_egl_window_destroy( window->Window.pContext.egl_window );
    if ( window->Window.pContext.shsurface )
      wl_shell_surface_destroy( window->Window.pContext.shsurface );
    if ( window->Window.pContext.surface )
      wl_surface_destroy( window->Window.pContext.surface );
    if ( window->Window.pContext.cursor_surface )
      wl_surface_destroy( window->Window.pContext.cursor_surface );
}


/*
 * This function re-creates the window assets if they
 * have been destroyed
 */
void fgPlatformShowWindow( SFG_Window *window )
{
    if ( ! window->Window.pContext.egl_window ||
         ! window->Window.pContext.shsurface ||
         ! window->Window.pContext.surface)
    {
        fgPlatformCloseWindow( window );
        fgPlatformOpenWindow( window, "", /* TODO : save the title for further use */
                              GL_TRUE, window->State.Xpos, window->State.Ypos,
                              GL_TRUE, window->State.Width, window->State.Height,
                              (GLboolean)(window->State.IsFullscreen ? GL_TRUE : GL_FALSE),
                              (GLboolean)(window->Parent ? GL_TRUE : GL_FALSE) );
    }
    else 
    {
    /*     TODO : support this once we start using xdg-shell
     *
     *     xdg_surface_present( window->Window.pContext.shsurface, 0 );
     *     INVOKE_WCB( *window, WindowStatus, ( GLUT_FULLY_RETAINED ) );
     *     window->State.Visible = GL_TRUE;
     */
        fgWarning( "glutShownWindow(): function unsupported for an already existing"
                                     " window under Wayland" );
    }
}

/*
 * This function hides the specified window
 */
void fgPlatformHideWindow( SFG_Window *window )
{
    fgPlatformIconifyWindow( window );
}

/*
 * Iconify the specified window (top-level windows only)
 */
void fgPlatformIconifyWindow( SFG_Window *window )
{
    /* TODO : support this once we start using xdg-shell
     *
     * xdg_surface_set_minimized( window->Window.pContext.shsurface );
     * INVOKE_WCB( *window, WindowStatus, ( GLUT_HIDDEN ) );
     * window->State.Visible = GL_FALSE;
     */
    fgWarning( "glutIconifyWindow(): function unsupported under Wayland" );
}

/*
 * Set the current window's title
 */
void fgPlatformGlutSetWindowTitle( const char* title )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    wl_shell_surface_set_title( win->Window.pContext.shsurface, title );
}

/*
 * Set the current window's iconified title
 */
void fgPlatformGlutSetIconTitle( const char* title )
{
    fgPlatformGlutSetWindowTitle( title );
}

/*
 * Change the specified window's position
 */
void fgPlatformPositionWindow( SFG_Window *window, int x, int y )
{
    /* pointless under Wayland */
    fgWarning( "glutPositionWindow(): function unsupported under Wayland" );
}

/*
 * Lowers the specified window (by Z order change)
 */
void fgPlatformPushWindow( SFG_Window *window )
{
    /* pointless under Wayland */
    fgWarning( "glutPushWindow(): function unsupported under Wayland" );
}

/*
 * Raises the specified window (by Z order change)
 */
void fgPlatformPopWindow( SFG_Window *window )
{
    /* pointless under Wayland */
    fgWarning( "glutPopWindow(): function unsupported under Wayland" );
}

/*
 * Toggle the window's full screen state.
 */
void fgPlatformFullScreenToggle( SFG_Window *win )
{
    if(fghToggleFullscreen() != -1) {
        win->State.IsFullscreen = !win->State.IsFullscreen;
    }
}

