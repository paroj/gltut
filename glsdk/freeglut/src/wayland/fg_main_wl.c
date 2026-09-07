/*
 * fg_main_wl.c
 *
 * The Wayland-specific windows message processing methods.
 *
 * Copyright (c) 2015 Manuel Bachmann. All Rights Reserved.
 * Written by Manuel Bachmann, <tarnyko@tarnyko.net>
 * Creation date: Sun Mar 22 2015
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
#include <errno.h>
#include <poll.h>

void fgPlatformFullScreenToggle( SFG_Window *win );
void fgPlatformPositionWindow( SFG_Window *window, int x, int y );
void fgPlatformReshapeWindow( SFG_Window *window, int width, int height );
void fgPlatformPushWindow( SFG_Window *window );
void fgPlatformPopWindow( SFG_Window *window );
void fgPlatformHideWindow( SFG_Window *window );
void fgPlatformIconifyWindow( SFG_Window *window );
void fgPlatformShowWindow( SFG_Window *window );


fg_time_t fgPlatformSystemTime( void )
{
#ifdef CLOCK_MONOTONIC
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_nsec/1000000 + now.tv_sec*1000;
#elif defined(HAVE_GETTIMEOFDAY)
    struct timeval now;
    gettimeofday( &now, NULL );
    return now.tv_usec/1000 + now.tv_sec*1000;
#endif
}

void fgPlatformSleepForEvents( fg_time_t msec )
{
    struct pollfd pfd;
    int err;

    pfd.fd = wl_display_get_fd( fgDisplay.pDisplay.display );
    pfd.events = POLLIN | POLLERR | POLLHUP;

    wl_display_dispatch_pending( fgDisplay.pDisplay.display );
    if ( ! wl_display_flush( fgDisplay.pDisplay.display ) )
    {
        err = poll( &pfd, 1, msec );

        if( ( -1 == err ) && ( errno != EINTR ) )
          fgWarning ( "freeglut poll() error: %d", errno );
    }
}


void fgPlatformProcessSingleEvent( void )
{
    SFG_Window *win = fgStructure.CurrentWindow;

    wl_display_dispatch_pending( fgDisplay.pDisplay.display );
    INVOKE_WCB( *win, Display, ( ) );
}

void fgPlatformMainLoopPreliminaryWork( void )
{
    /* Under Wayland, this is a no-op */
}

void fgPlatformInitWork( SFG_Window* window )
{
    /* Under Wayland, all events happen relative to input handlers
     * -> this is a no-op
     */
     return;
}

void fgPlatformPosResZordWork( SFG_Window* window, unsigned int workMask )
{
    if( workMask & GLUT_FULL_SCREEN_WORK )
        fgPlatformFullScreenToggle( window );
    if( workMask & GLUT_POSITION_WORK )
        fgPlatformPositionWindow( window, window->State.DesiredXpos, window->State.DesiredYpos );
    if( workMask & GLUT_SIZE_WORK )
        fgPlatformReshapeWindow ( window, window->State.DesiredWidth, window->State.DesiredHeight );
    if( workMask & GLUT_ZORDER_WORK )
    {
        if( window->State.DesiredZOrder < 0 )
            fgPlatformPushWindow( window );
        else
            fgPlatformPopWindow( window );
    }
}

void fgPlatformVisibilityWork( SFG_Window* window )
{
    /* Visibility status of window gets updated in the window message handlers above 
     */
    SFG_Window *win = window;
    switch (window->State.DesiredVisibility)
    {
    case DesireHiddenState:
        fgPlatformHideWindow( window );
        break;
    case DesireIconicState:
        /* Call on top-level window */
        while (win->Parent)
            win = win->Parent;
        fgPlatformIconifyWindow( win );
        break;
    case DesireNormalState:
        fgPlatformShowWindow( window );
        break;
    }
}

/* dummy functions, not applicable on wayland */
void fgPlatformSetColor(int idx, float r, float g, float b)
{
}

float fgPlatformGetColor(int idx, int comp)
{
}

void fgPlatformCopyColormap(int win)
{
}
