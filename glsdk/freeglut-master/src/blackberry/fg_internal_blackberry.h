/*
 * fg_internal_blackberry.h
 *
 * The freeglut library private include file.
 *
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

#ifndef  FREEGLUT_INTERNAL_BLACKBERRY_H
#define  FREEGLUT_INTERNAL_BLACKBERRY_H

//Minor modified version of fg_internal_android.h

/* -- PLATFORM-SPECIFIC INCLUDES ------------------------------------------- */
/* BlackBerry OpenGL ES is accessed through EGL */
#include "egl/fg_internal_egl.h"
#include <screen/screen.h>
#include <bps/event.h>
#include <bps/navigator.h>

/* -- GLOBAL TYPE DEFINITIONS ---------------------------------------------- */
/* The structure used by display initialization in fg_init.c */
typedef struct tagSFG_PlatformDisplay SFG_PlatformDisplay;
struct tagSFG_PlatformDisplay
{
    struct tagSFG_PlatformDisplayEGL egl;
    screen_context_t screenContext;
    bps_event_t* event;
    EGLNativeWindowType single_native_window;
};

typedef struct tagSFG_PlatformContext SFG_PlatformContext;
/* SFG_PlatformContext is used for SFG_Window.Window */
struct tagSFG_PlatformContext
{
    struct tagSFG_PlatformContextEGL egl;
};


/**
 * Virtual PAD (spots on touchscreen that simulate keys)
 */
struct vpad_state {
    bool on;
    bool left;
    bool right;
    bool up;
    bool down;
};
struct touchscreen {
    struct vpad_state vpad;
    bool in_mmotion;
};

/* -- INPUT DEFINITIONS ---------------------------------------------------- */
#define WHEEL_DELTA 120 //This is taken from http://msdn.microsoft.com/en-us/library/windows/desktop/ms646254(v=vs.85).aspx


/* -- JOYSTICK-SPECIFIC STRUCTURES AND TYPES ------------------------------- */
/*
 * Initial defines from "js.h" starting around line 33 with the existing "fg_joystick.c"
 * interspersed
 */

/*
 * We'll put these values in and that should
 * allow the code to at least compile when there is
 * no support. The JS open routine should error out
 * and shut off all the code downstream anyway and if
 * the application doesn't use a joystick we'll be fine.
 */

struct JS_DATA_TYPE
{
    int buttons;
    int x;
    int y;
};

#define JS_RETURN (sizeof(struct JS_DATA_TYPE))

/* XXX It might be better to poll the operating system for the numbers of buttons and
 * XXX axes and then dynamically allocate the arrays.
 */
#define _JS_MAX_AXES 16
typedef struct tagSFG_PlatformJoystick SFG_PlatformJoystick;
struct tagSFG_PlatformJoystick
{
    struct JS_DATA_TYPE js;

    char fname [ 128 ];
    int  fd;
};

/* Window's state description. This structure should be kept portable. */
typedef struct tagSFG_PlatformWindowState SFG_PlatformWindowState;
struct tagSFG_PlatformWindowState
{
    int newWidth;
    int newHeight;
    int originalRotation;
    navigator_window_state_t windowState;
    GLboolean windowCovered;
    int keyboardHeight;
    GLboolean keyboardOpen;
};

/* Menu font and color definitions */
#define  FREEGLUT_MENU_FONT    NULL

#define  FREEGLUT_MENU_PEN_FORE_COLORS   {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_BACK_COLORS   {0.70f, 0.70f, 0.70f, 1.0f}
#define  FREEGLUT_MENU_PEN_HFORE_COLORS  {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_HBACK_COLORS  {1.0f,  1.0f,  1.0f,  1.0f}

#endif  /* FREEGLUT_INTERNAL_BLACKBERRY_H */
