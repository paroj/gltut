/*
 * fg_gamemode_wl.c
 *
 * The game mode handling code.
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
#include "../fg_internal.h"

/* Pointer locking is a Weston-specific WIP protocol (for now)
 *
 * #include "pointer-lock-client-protocol.h"
 * #include "relative-pointer-client-protocol.h"
 *
 * static struct _wl_relative_pointer_manager* relative_pointer_manager;
 * static struct _wl_pointer_lock* pointer_lock;
 *
 * static struct _wl_relative_pointer* relative_pointer;
 * static struct _wl_locked_pointer* locked_pointer;
 *
 *
 * static void fghRelativeMotion( void* data, struct _wl_relative_pointer
 *                                pointer, uint32_t time,
 *                                wl_fixed_t x_w, wl_fixed_t y_w,
 *                                wl_fixed_t x_noacc, wl_fixed_t y_noacc )
 * {
 *     SFG_Window* win = fgStructure.CurrentWindow;
 *     win->State.MouseX = wl_fixed_to_int( x_w );
 *     win->State.MouseY = wl_fixed_to_int( y_w );
 *     INVOKE_WCB( *win, Passive, ( win->State.MouseX,
 *                                  win->State.MouseY ) );
 * }
 * static const struct _wl_relative_pointer_listener
 *                                fghRelativeListener =
 * {
 *   fghRelativeMotion
 * };
 *
 * static void fghLockedLocked( void* data, struct _wl_locked_pointer
 *                              pointer, uint32_t serial )
 * {
 *     fgPlatformRememberState();
 *     fgPlatformSetCursor( win, GLUT_CURSOR_NONE ):
 * }
 * static void fghLockedUnlocked( void* data, struct _wl_locked_pointer
 *                                pointer )
 * {
 *     fgPlatformRestoreState();
 * }
 * static const struct _wl_locked_pointer_listener
 *                                 fghLockedListener =
 * {
 *   fghLockedLocked,
 *   fghLockedUnlocked
 * };
 */


static struct wl_cursor* saved_cursor;

/*
 * Remembers the current visual settings, so that
 * we can change them and restore later...
 */
void fgPlatformRememberState( void )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    saved_cursor = win->Window.pContext.cursor;
}

/*
 * Restores the previously remembered visual settings
 */
void fgPlatformRestoreState( void )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    win->Window.pContext.cursor = saved_cursor;
}

/*
 *  * Private function to get the virtual maximum screen extent
 *   */
GLvoid fgPlatformGetGameModeVMaxExtent( SFG_Window* window, int* x, int* y )
{
    /*
     * under Wayland, just return the size of the window,
     * at least until we start messing with the outputs...
     */
    *x = window->State.Width;
    *y = window->State.Height;
}

/*
 * Changes the current display mode to match user's settings
 */
GLboolean fgPlatformChangeDisplayMode( GLboolean haveToTest )
{
    /* Such a protocol is being studied in Wayland */
    return GL_FALSE;
}


void fgPlatformEnterGameMode( void )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    struct wl_region* region;

    region = wl_compositor_create_region (
                                 fgDisplay.pDisplay.compositor );
    wl_region_add( region, 0, 0,
                   win->State.Width,
                   win->State.Height );
   /*
    * relative_pointer =
    *      _wl_relative_pointer_manager_get_relative_pointer (
    *                relative_pointer_manager,
    *                fgDisplay.pDisplay.seat );
    * _wl_relative_pointer_add_listener( relative_pointer,
    *                                    &fghRelativeListener,
    *                                    NULL );
    * locked_pointer = _wl_pointer_lock_lock_pointer (
    *                             pointer_lock,
    *                             win->Window.pContext.surface,
    *                             fgDisplay.pDisplay.seat,
    *                             NULL);
    * _wl_locked_pointer_add_listener( locked_pointer,
    *                                  &fghLockedListener,
    *                                  NULL );
    */
    wl_region_destroy( region );
}

void fgPlatformLeaveGameMode( void )
{
   /* 
    * _wl_locked_pointer_destroy( locked_pointer );
    * _wl_relative_pointer_release( relative_pointer );
    */
}

