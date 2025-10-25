/*
 * fg_state_blackberry.c
 *
 * BlackBerry-specific freeglut state query methods.
 *
 * Copyright (c) 2012 Stephen J. Baker. All Rights Reserved.
 * Written by John F. Fay, <fayjf@sourceforge.net>
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
#include <stdio.h>
#include <screen/screen.h>
#include "fg_internal.h"
#include "egl/fg_state_egl.h"

//From fg_state_android.c
int fgPlatformGlutDeviceGet ( GLenum eWhat )
{
#ifndef __PLAYBOOK__
    int deviceCount, i, value;
    screen_device_t* devices;
#endif

    switch( eWhat )
    {
    case GLUT_HAS_KEYBOARD:
        /* BlackBerry has a keyboard, though it may be virtual. */
        return 1;

    case GLUT_HAS_MOUSE:
        /* BlackBerry has a touchscreen. Consider it as a mouse since we have no guarantee
           that a mouse will be used (in which case it's a simulator). */
        return 1 ;

    case GLUT_NUM_MOUSE_BUTTONS:
        /* BlackBerry has a touchscreen, which we can consider a 1-button mouse at min.
           Otherwise check for an actual mouse, else get max touch points. PlayBook does not support this. */
#ifndef __PLAYBOOK__
        if(!screen_get_context_property_iv(fgDisplay.pDisplay.screenContext, SCREEN_PROPERTY_DEVICE_COUNT, &deviceCount)) {
            devices = (screen_device_t*)calloc(deviceCount, sizeof(screen_device_t));
            if(!screen_get_context_property_pv(fgDisplay.pDisplay.screenContext, SCREEN_PROPERTY_DEVICES, (void**)devices)) {
                /* Check for a pointer */
                for(i = 0; i < deviceCount; i++) {
                    if(!screen_get_device_property_iv(devices[i], SCREEN_PROPERTY_TYPE, &value) &&
                            value == SCREEN_EVENT_POINTER &&
                            !screen_get_device_property_iv(devices[i], SCREEN_PROPERTY_BUTTON_COUNT, &value)) {
                        free(devices);
                        return value;
                    }
                }
                /* Check for mtouch */
                for(i = 0; i < deviceCount; i++) {
                    if(!screen_get_device_property_iv(devices[i], SCREEN_PROPERTY_TYPE, &value) &&
                            value == SCREEN_EVENT_MTOUCH_TOUCH &&
                            !screen_get_device_property_iv(devices[i], SCREEN_PROPERTY_MAXIMUM_TOUCH_ID, &value)) {
                        free(devices);
                        return value;
                    }
                }
            }
            free(devices);
        }
#endif
        /* Backup, pretend it's a 1-button mouse */
        return 1;

    default:
        fgWarning( "glutDeviceGet(): missing enum handle %d", eWhat );
        break;
    }

    /* And now -- the failure. */
    return -1;
}

int fgPlatformGlutGet ( GLenum eWhat )
{
    switch (eWhat) {
    /* One full-screen window only */
    case GLUT_WINDOW_X:
    case GLUT_WINDOW_Y:
    case GLUT_WINDOW_BORDER_WIDTH:
    case GLUT_WINDOW_HEADER_HEIGHT:
        return 0;

    case GLUT_WINDOW_WIDTH:
    case GLUT_WINDOW_HEIGHT:
    {
        if ( fgStructure.CurrentWindow == NULL )
            return 0;

        int size[2];
        int orientation;
        if ( screen_get_window_property_iv(fgStructure.CurrentWindow->Window.Handle, SCREEN_PROPERTY_BUFFER_SIZE, size) != 0 )
            return 0;
        if ( screen_get_window_property_iv(fgStructure.CurrentWindow->Window.Handle, SCREEN_PROPERTY_ROTATION, &orientation) != 0 )
            return 0;

        int orientationDif = abs(orientation - fgStructure.CurrentWindow->State.pWState.originalRotation);
        if (orientationDif == 90 || orientationDif == 270) {
            /* Swap dim. if screen is rotated */
            int tmp = size[0];
            size[0] = size[1];
            size[1] = tmp;
        }
        switch ( eWhat )
        {
        case GLUT_WINDOW_WIDTH:
            return size[0];
        case GLUT_WINDOW_HEIGHT:
            return size[1];
        }
        break;
    }

    case GLUT_WINDOW_COLORMAP_SIZE:
        /* 0 for RGBA/non-indexed mode */
        /* Under BlackBerry and GLES more generally, no indexed-mode */
        return 0;

    default:
        return fghPlatformGlutGetEGL(eWhat);
    }
    return -1;
}
