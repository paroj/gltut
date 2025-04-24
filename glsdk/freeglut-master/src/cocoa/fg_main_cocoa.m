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

#include <GL/freeglut.h>
#include "../fg_internal.h"

#include <Cocoa/Cocoa.h>

void fgPlatformSetWindow( SFG_Window *window );

fg_time_t fgPlatformSystemTime( void )
{
    uint64_t now_ns = clock_gettime_nsec_np( CLOCK_REALTIME );
    return (fg_time_t)( now_ns / 1000000LL ); // Return time in milliseconds
}

/*
 * Does the magic required to relinquish the CPU until something interesting
 * happens.
 */
void fgPlatformSleepForEvents( fg_time_t msec )
{
    // Implement sleep functionality according to msec
    @autoreleasepool {
        NSTimeInterval timeout_sec = ( msec == INT_MAX ) ? 1.0 : ( msec / 1000.0 );
        NSEvent       *event       = [NSApp nextEventMatchingMask:NSEventMaskAny
                                            untilDate:[NSDate dateWithTimeIntervalSinceNow:timeout_sec]
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];
        if ( event ) {
            [NSApp sendEvent:event];
        }
    }
}

void fgPlatformProcessSingleEvent( void )
{
    @autoreleasepool {
        // Process all pending Cocoa events
        while ( true ) {
            NSEvent *event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                untilDate:[NSDate distantPast] // Return immediately
                                                   inMode:NSDefaultRunLoopMode
                                                  dequeue:YES];
            if ( !event )
                break; // Exit when no more events are pending

            [NSApp sendEvent:event];
        }

        // Set the current window’s OpenGL context after event processing
        if ( fgStructure.CurrentWindow ) {
            fgPlatformSetWindow( fgStructure.CurrentWindow );
        }
    }
}

void fgPlatformMainLoopPreliminaryWork( void )
{
    [NSApp finishLaunching];               // Completes the app launch process
    [NSApp activateIgnoringOtherApps:YES]; // Bring app to the front
}

/* deal with work list items */
void fgPlatformInitWork( SFG_Window *window )
{
    PART_IMPL;
    // NSWindow *nsWindow = (NSWindow *)window->Window.Handle;
    // Placeholder for initialization tasks
}

void fgPlatformPosResZordWork( SFG_Window *window, unsigned int workMask )
{
    TODO_IMPL;
}

void fgPlatformVisibilityWork( SFG_Window *window )
{
    TODO_IMPL;
}
