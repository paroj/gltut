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

#define FREEGLUT_BUILDING_LIB

#include <GL/freeglut.h>
#include "../fg_internal.h"
#include "../fg_init.h"

#import <Cocoa/Cocoa.h>
#import <CoreVideo/CVDisplayLink.h>
#include <sys/time.h>

fg_time_t fgPlatformSystemTime( void );

void fgPlatformInitialize( const char *displayName )
{
    // Initialize the Cocoa application
    [NSApplication sharedApplication]; // This creates the singleton instance of NSApplication (NSApp)
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    // Get the main screen properties
    NSScreen *mainScreen   = [NSScreen mainScreen];
    NSRect    screenFrame  = [mainScreen visibleFrame]; // visibleFrame excludes the menu bar and dock
    fgDisplay.ScreenWidth  = screenFrame.size.width;
    fgDisplay.ScreenHeight = screenFrame.size.height;

    // Calculate screen size in millimeters
    NSNumber         *screenNumber  = mainScreen.deviceDescription[@"NSScreenNumber"];
    CGDirectDisplayID displayID     = [screenNumber unsignedIntValue];
    CGSize            displaySizeMM = CGDisplayScreenSize( displayID );
    fgDisplay.ScreenWidthMM         = displaySizeMM.width;
    fgDisplay.ScreenHeightMM        = displaySizeMM.height;

    // Prepare for CVDisplayLink (used for VSync)
    fgDisplay.pDisplay.DisplayLink = NULL; // Will be set up later in window creation

    fgState.Time = fgPlatformSystemTime( );

    // Clear the modifiers state
    fgState.Modifiers = 0;

    fgState.Initialised = GL_TRUE;

    atexit( fgDeinitialize );

    // Initialize input devices (joysticks, etc.)
    fgInitialiseInputDevices( );

    DBG( "Screen size: %dx%d, Screen size in mm: %dx%d",
        fgDisplay.ScreenWidth,
        fgDisplay.ScreenHeight,
        fgDisplay.ScreenWidthMM,
        fgDisplay.ScreenHeightMM );
}

void fgPlatformDeinitialiseInputDevices( void )
{
    fghCloseInputDevices( );

    fgState.JoysticksInitialised = GL_FALSE;
    fgState.InputDevsInitialised = GL_FALSE;
}

void fgPlatformCloseDisplay( void )
{
    // Clean up display-related resources
    if ( fgDisplay.pDisplay.DisplayLink != NULL ) {
        CVDisplayLinkStop( fgDisplay.pDisplay.DisplayLink );
        CVDisplayLinkRelease( fgDisplay.pDisplay.DisplayLink );
        fgDisplay.pDisplay.DisplayLink = NULL;
    }
}

void fgPlatformDestroyContext( SFG_PlatformDisplay pDisplay, SFG_WindowContextType MContext )
{
    NSOpenGLContext *context = (NSOpenGLContext *)MContext;
    [context clearDrawable]; // Ensure the context is detached from any drawable
    [context release];
}
