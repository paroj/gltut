/*
 * fg_init_blackberry.c
 *
 * Various freeglut initialization functions.
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

#include <GL/freeglut.h>
#include "fg_internal.h"
#include "fg_init.h"
#include "egl/fg_init_egl.h"
#include <bps/bps.h>
#include <screen/screen.h>

void fgPlatformInitialize()
{
    bps_initialize();

    fghPlatformInitializeEGL();

    /* Prepare for screen events */
    fgDisplay.pDisplay.event = NULL;
    fgDisplay.pDisplay.screenContext = NULL;

    /* Create window */
    if (screen_create_context(&fgDisplay.pDisplay.screenContext, 0)) {
        fgError("Could not create screen context");
        return;
    }

    /* Get screen size */
    int displayCount;
    screen_display_t* displays;
    int vals[2];
    if(screen_get_context_property_iv(fgDisplay.pDisplay.screenContext, SCREEN_PROPERTY_DISPLAY_COUNT, &displayCount)) {
        fgWarning("Could not get display count. Screen size not determined and will be left at default values");
    } else if(displayCount >= 1) {
        displays = (screen_display_t*)calloc(displayCount, sizeof(screen_display_t));
        if(screen_get_context_property_pv(fgDisplay.pDisplay.screenContext, SCREEN_PROPERTY_DISPLAYS, (void**)displays)) {
            fgWarning("Could not get displays. Screen size not determined and will be left at default values");
        } else {
            /* We only care about the first one, which is the device display */
            if(screen_get_display_property_iv(displays[0], SCREEN_PROPERTY_SIZE, vals)) {
                fgWarning("Could not get display size. Values will be left at default");
            } else {
                if(screen_get_display_property_iv(displays[0], SCREEN_PROPERTY_ROTATION, &displayCount) || (displayCount == 0 || displayCount == 180)) {
                    fgDisplay.ScreenWidth = vals[0];
                    fgDisplay.ScreenHeight = vals[1];
                } else {
                    fgDisplay.ScreenWidth = vals[1];
                    fgDisplay.ScreenHeight = vals[0];
                }
            }
            if(screen_get_display_property_iv(displays[0], SCREEN_PROPERTY_PHYSICAL_SIZE, vals)) {
                fgWarning("Could not get physical display size. Values will be left at default");
            } else {
                fgDisplay.ScreenWidthMM = vals[0];
                fgDisplay.ScreenHeightMM = vals[1];
            }
        }
        free(displays);
    }

    /* Get start time */
    fgState.Time = fgSystemTime();

    fgState.Initialised = GL_TRUE;
}

void fgPlatformCloseDisplay()
{
    fghPlatformCloseDisplayEGL();

    screen_destroy_context(fgDisplay.pDisplay.screenContext);
    fgDisplay.pDisplay.screenContext = NULL;

    bps_shutdown();
}

/**
 * Close joystick and serial input devices
 */
void fgPlatformDeinitialiseInputDevices ( void )
{
    fghCloseInputDevices ();
    fgState.JoysticksInitialised = GL_FALSE;
    fgState.InputDevsInitialised = GL_FALSE;
}
