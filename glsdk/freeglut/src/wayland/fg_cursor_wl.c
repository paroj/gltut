/*
 * fg_cursor_wl.c
 *
 * The Wayland-specific mouse cursor related stuff.
 *
 * Copyright (c) 2015 Manuel Bachmann. All Rights Reserved.
 * Written by Manuel Bachmann, <tarnyko@tarnyko.net>
 * Creation date: Thur Mar 19, 2015
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

#include <string.h>
#include <GL/freeglut.h>
#include "../fg_internal.h"

/*
 * Note: The arrangement of the table below depends on the fact that
 * the "normal" GLUT_CURSOR_* values start a 0 and are consecutive.
 */ 
static char* cursorList[] = {
    "UNSUPPORTED",          /* GLUT_CURSOR_RIGHT_ARROW */
    "left_ptr",             /* GLUT_CURSOR_LEFT_ARROW */
    "hand1",                /* GLUT_CURSOR_INFO */
    "UNSUPPORTED",          /* GLUT_CURSOR_DESTROY */
    "UNSUPPORTED",          /* GLUT_CURSOR_HELP */
    "UNSUPPORTED",          /* GLUT_CURSOR_CYCLE */
    "UNSUPPORTED",          /* GLUT_CURSOR_SPRAY */
    "watch",                /* GLUT_CURSOR_WAIT */
    "xterm",                /* GLUT_CURSOR_TEXT */
    "grabbing",             /* GLUT_CURSOR_CROSSHAIR */
    "UNSUPPORTED",          /* GLUT_CURSOR_UP_DOWN */
    "UNSUPPORTED",          /* GLUT_CURSOR_LEFT_RIGHT */
    "top_side",             /* GLUT_CURSOR_TOP_SIDE */
    "bottom_side",          /* GLUT_CURSOR_BOTTOM_SIDE */
    "left_side",            /* GLUT_CURSOR_LEFT_SIDE */
    "right_side",           /* GLUT_CURSOR_RIGHT_SIDE */
    "top_left_corner",      /* GLUT_CURSOR_TOP_LEFT_CORNER */
    "top_right_corner",     /* GLUT_CURSOR_TOP_RIGHT_CORNER */
    "bottom_right_corner",  /* GLUT_CURSOR_BOTTOM_RIGHT_CORNER */
    "bottom_left_corner"    /* GLUT_CURSOR_BOTTOM_LEFT_CORNER */
};

void fgPlatformSetCursor ( SFG_Window *window, int cursorID )
{
    /*
     * XXX FULL_CROSSHAIR demotes to plain CROSSHAIR. Old GLUT allows
     * for this, but if there is a system that easily supports a full-
     * window (or full-screen) crosshair, we might consider it.
     */
    int cursorIDToUse =
        ( cursorID == GLUT_CURSOR_FULL_CROSSHAIR ) ? GLUT_CURSOR_CROSSHAIR : cursorID;

    char* cursor;

    if( ( cursorIDToUse >= 0 ) &&
        ( cursorIDToUse < sizeof( cursorList ) / sizeof( cursorList[0] ) ) ) {

        cursor = cursorList[cursorIDToUse];

        /* if the type is UNSUPPORTED, fall back to GLUT_CURSOR_LEFT_ARROW */
        if ( ! strcmp( cursor, "UNSUPPORTED" ) )
        {
            fgWarning( "glutSetCursor(): cursor type unsupported under Wayland : %d",
                       cursorIDToUse );
            cursor = "left_ptr";
        }
    } else {
        switch( cursorIDToUse )
        {
        case GLUT_CURSOR_NONE:
        case GLUT_CURSOR_INHERIT:
            cursor = NULL;
            break;

        default:
            fgError( "Unknown cursor type: %d", cursorIDToUse );
            return;
        }
    }

    if ( cursorIDToUse == GLUT_CURSOR_INHERIT ) {
        if( window->Parent )
          window->Window.pContext.cursor =
            window->Parent->Window.pContext.cursor;
    } else {
        window->Window.pContext.cursor = wl_cursor_theme_get_cursor(
                                           fgDisplay.pDisplay.cursor_theme,
                                           cursor );
        if ( ! window->Window.pContext.cursor )
          fgError( "Failed to create cursor" );
    }
}


void fgPlatformWarpPointer ( int x, int y )
{
    /* unsupported under Wayland */
    fgWarning( "glutWarpPointer(): function unsupported under Wayland" );
}

void fghPlatformGetCursorPos(const SFG_Window *window, GLboolean client, SFG_XYUse *mouse_pos)
{
    /* Get current pointer location relative to top-left of client area of window (if client is true and window is not NULL)
     * We cannot get current pointer location in screen coordinates under Wayland, so inform the user and return -1 is this case
     */

    if (client && window)
    {
        mouse_pos->X = window->State.MouseX;
        mouse_pos->Y = window->State.MouseY;
    }
    else
    {
        fgWarning( "glutGetCursorPos(): cannot get screen position under Wayland" );
        mouse_pos->X = -1;
        mouse_pos->Y = -1;
    }

    mouse_pos->Use = GL_TRUE;
}

