/*
 * fg_internal_wl.h
 *
 * The freeglut library private include file.
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

#ifndef  FREEGLUT_INTERNAL_WL_H
#define  FREEGLUT_INTERNAL_WL_H


/* -- PLATFORM-SPECIFIC INCLUDES ------------------------------------------- */
#include "egl/fg_internal_egl.h"
#include <wayland-egl.h>
#include <wayland-client.h>
#include <wayland-cursor.h>
#include <xkbcommon/xkbcommon.h>


/* -- GLOBAL TYPE DEFINITIONS ---------------------------------------------- */
/* The structure used by display initialization in fg_init.c */
typedef struct tagSFG_PlatformDisplay SFG_PlatformDisplay;
struct tagSFG_PlatformDisplay
{
    struct tagSFG_PlatformDisplayEGL egl;

    struct wl_display* display;        /* The display we are being run in    */
    struct wl_registry* registry;      /* The global interface registry      */
    struct wl_compositor* compositor;  /* The compositor                     */
    struct wl_shell* shell;            /* The shell, AKA window manager      */
    struct wl_seat* seat;              /* The seat, references input devices */

    struct xkb_context* xkb_context;   /* The global XKB keyboard context    */
    struct xkb_state* xkb_state;       /* The current XKB keyboard state     */
    struct wl_keyboard* keyboard;      /* The keyboard input device          */
    struct wl_pointer* pointer;        /* The pointer input device (mouse)   */
    struct wl_touch* touch;            /* The touchscreen input device       */

    struct wl_shm* shm;                    /* The software rendering engine  */
    struct wl_cursor_theme* cursor_theme;  /* The pointer cursor theme       */
};


/* The structure used by window creation in fg_window.c */
typedef struct tagSFG_PlatformContext SFG_PlatformContext;
struct tagSFG_PlatformContext
{
    struct tagSFG_PlatformContextEGL egl;
    GLboolean pointer_button_pressed;

    struct wl_surface* surface;            /* The drawing surface             */
    struct wl_shell_surface* shsurface;    /* The shell surface, has states   */
    struct wl_egl_window* egl_window;      /* Binding between WL/EGL surfaces */

    struct wl_cursor* cursor;              /* The active cursor */
    struct wl_surface* cursor_surface;     /* The active cursor surface */
};


/* The window state description. This structure should be kept portable. */
typedef struct tagSFG_PlatformWindowState SFG_PlatformWindowState;
struct tagSFG_PlatformWindowState
{
    int OldWidth;                        /* Window width from before a resize */
    int OldHeight;                       /*   "    height  "    "    "   "    */
};


/* -- JOYSTICK-SPECIFIC STRUCTURES AND TYPES ------------------------------- */
/*
 * Initial defines from "js.h" starting around line 33 with the existing "fg_joystick.c"
 * interspersed
 */
#    ifdef HAVE_SYS_IOCTL_H
#        include <sys/ioctl.h>
#    endif
#    ifdef HAVE_FCNTL_H
#        include <fcntl.h>
#    endif

#include <errno.h>
#include <string.h>

#    if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__)
#        define HAVE_USB_JS    1

#        include <sys/joystick.h>
#        define JS_DATA_TYPE joystick
#        define JS_RETURN (sizeof(struct JS_DATA_TYPE))
#    endif

#    if defined(__linux__)
#        include <linux/joystick.h>

/* check the joystick driver version */
#        if defined(JS_VERSION) && JS_VERSION >= 0x010000
#            define JS_NEW
#        endif
#    else  /* Not BSD or Linux */
#        ifndef JS_RETURN

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

#            define JS_RETURN (sizeof(struct JS_DATA_TYPE))
#        endif
#    endif

/* XXX It might be better to poll the operating system for the numbers of buttons and
 * XXX axes and then dynamically allocate the arrays.
 */
#    define _JS_MAX_AXES 16
typedef struct tagSFG_PlatformJoystick SFG_PlatformJoystick;
struct tagSFG_PlatformJoystick
{
#   if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__)
       struct os_specific_s *os;
#   endif

#   ifdef JS_NEW
       struct js_event     js;
       int          tmp_buttons;
       float        tmp_axes [ _JS_MAX_AXES ];
#   else
       struct JS_DATA_TYPE js;
#   endif

    char         fname [ 128 ];
    int          fd;
};


/* Menu font and color definitions */
#define  FREEGLUT_MENU_FONT    GLUT_BITMAP_HELVETICA_18

#define  FREEGLUT_MENU_PEN_FORE_COLORS   {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_BACK_COLORS   {0.70f, 0.70f, 0.70f, 1.0f}
#define  FREEGLUT_MENU_PEN_HFORE_COLORS  {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_HBACK_COLORS  {1.0f,  1.0f,  1.0f,  1.0f}


#endif  /* FREEGLUT_INTERNAL_WL_H */
