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

#include <pthread.h>

#import <Cocoa/Cocoa.h>

extern BOOL shouldQuit;

static pthread_mutex_t swapMutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  swapCond   = PTHREAD_COND_INITIALIZER;
static BOOL            frameReady = NO; /* synchronized by swapMutex */

/*
 * The display link callback is called when the display is refreshed, indicating that it is s
 */
CVReturn fgDisplayLinkCallback( CVDisplayLinkRef displayLink,
    const CVTimeStamp                           *now,
    const CVTimeStamp                           *outputTime,
    CVOptionFlags                                flagsIn,
    CVOptionFlags                               *flagsOut,
    void                                        *displayLinkContext )
{
    static uint64_t FGUNUSED frameCount = 0;

    pthread_mutex_lock( &swapMutex );
#ifdef REPORT_DROPPED_FRAMES
    static uint64_t dropped = 0;
    if ( !frameReady ) {
        DBG( "Dropped frame %llu - displayLinkCallback, no frame ready, %llu drops", frameCount, dropped );
        dropped++;
    }
    else
#endif
    {
        frameReady = false;
        pthread_cond_signal( &swapCond ); // Wake the main thread
    }
    pthread_mutex_unlock( &swapMutex );

    frameCount++;
    return kCVReturnSuccess;
}

void fgPlatformGlutSwapBuffers( SFG_PlatformDisplay *pDisplayPtr, SFG_Window *CurrentWindow )
{
    if ( pDisplayPtr->DisplayLink ) {

        /*
         * Emulate VSync using CVDisplayLink
         */

        pthread_mutex_lock( &swapMutex );
        frameReady = true;
        while ( frameReady && !shouldQuit ) {
            pthread_cond_wait( &swapCond, &swapMutex ); // Wait for presentation from the display callback
        }
        pthread_mutex_unlock( &swapMutex );

        /* The display just got refreshed, so we can swap the buffers */
    }

    NSOpenGLContext *context = (NSOpenGLContext *)CurrentWindow->Window.Context;
    [context flushBuffer]; // Swap buffers to present the frame
}
