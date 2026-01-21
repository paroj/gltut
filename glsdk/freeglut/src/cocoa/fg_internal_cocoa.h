/*
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

#ifndef FREEGLUT_INTERNAL_COCOA_H
#define FREEGLUT_INTERNAL_COCOA_H

/* Add '#define DEBUG_LOG' for debug logging */
#define UNIMPLEMENTED_WARNING

/* Use CVDisplayLink for display synchronization */
#define USE_CVDISPLAYLINK

#include <unistd.h>

#if defined( __GNUC__ ) && !defined( FGUNUSED )
#define FGUNUSED __attribute__( ( unused ) )
#else
#define FGUNUSED
#endif

#ifdef DEBUG_LOG
#define DBG fgWarning
#else
/* C89 doesn't support variadic macros */
static void FGUNUSED DBG( const char *fmt, ... )
{
}
#endif

#ifdef UNIMPLEMENTED_WARNING
#define PRINT_ONCE( fmt, args )     \
    do {                            \
        static int once;            \
        if ( !once ) {              \
            fgWarning( fmt, args ); \
            once = 1;               \
        }                           \
    } while ( 0 )
#define TODO_IMPL PRINT_ONCE( "%s not implemented yet in Cocoa", __func__ )
#define PART_IMPL PRINT_ONCE( "%s partially implemented in Cocoa", __func__ )
#define NO_IMPL   PRINT_ONCE( "%s not implemented in Cocoa", __func__ )
#else
#define TODO_IMPL
#define PART_IMPL
#define NO_IMPL
#endif

/* Menu font and color definitions */
#define FREEGLUT_MENU_FONT GLUT_BITMAP_HELVETICA_18

#define FREEGLUT_MENU_PEN_FORE_COLORS  { 0.0f, 0.0f, 0.0f, 1.0f }
#define FREEGLUT_MENU_PEN_BACK_COLORS  { 0.70f, 0.70f, 0.70f, 1.0f }
#define FREEGLUT_MENU_PEN_HFORE_COLORS { 0.0f, 0.0f, 0.0f, 1.0f }
#define FREEGLUT_MENU_PEN_HBACK_COLORS { 1.0f, 1.0f, 1.0f, 1.0f }

/* Platform-specific display structure */
struct CocoaPlatformDisplay {
    void *DisplayLink; /* Core Video Display Link for vsync - CVDisplayLinkRef */
};

/* Platform-specific window context */
struct CocoaPlatformContext {
    void *CocoaContext; /* OpenGL context - NSOpenGLContext* */
    void *PixelFormat;  /* Pixel format - NSOpenGLPixelFormat* */
};

/* Platform window state info */
struct CocoaWindowState {
    int OldWidth;
    int OldHeight;
    int FrameBufferWidth;
    int FrameBufferHeight;
};

#define _JS_MAX_AXES 16
struct CocoaPlatformJoystick {
    char fd;
};

/*
 * Make "freeglut" window handle and context types so that we don't need so
 * much conditionally-compiled code later in the library.
 */
typedef void                        *SFG_WindowHandleType;   /* NSWindow* */
typedef void                        *SFG_WindowContextType;  /* NSOpenGLContext* */
typedef void                        *SFG_WindowColormapType; /* CGColorSpaceRef */
typedef struct CocoaWindowState      SFG_PlatformWindowState;
typedef struct CocoaPlatformDisplay  SFG_PlatformDisplay;
typedef struct CocoaPlatformContext  SFG_PlatformContext;
typedef struct CocoaPlatformJoystick SFG_PlatformJoystick;

#endif /* FREEGLUT_INTERNAL_COCOA_H */
