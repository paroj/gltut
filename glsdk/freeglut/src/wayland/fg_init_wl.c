/*
 * fg_init_wl.c
 *
 * Various freeglut Wayland initialization functions.
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

#define FREEGLUT_BUILDING_LIB
#include <string.h>
#include <GL/freeglut.h>
#include "fg_internal.h"
#include "egl/fg_init_egl.h"

void fgPlatformInitialiseInputDevices( void );
void fgPlatformCloseInputDevices( void );


static void fghRegistryGlobal( void* data,
                               struct wl_registry* registry,
                               uint32_t id,
                               const char* interface,
                               uint32_t version )
{
    SFG_PlatformDisplay* pDisplay = data;

    if ( ! strcmp( interface, "wl_compositor" ) )
      pDisplay->compositor = wl_registry_bind ( registry, id,
                                                &wl_compositor_interface, 1 );
    else if ( ! strcmp( interface, "wl_shell" ) )
      pDisplay->shell = wl_registry_bind ( registry, id,
                                           &wl_shell_interface, 1 );
    else if ( ! strcmp( interface, "wl_seat" ) )
      pDisplay->seat = wl_registry_bind ( registry, id,
                                          &wl_seat_interface, 1 );
    else if ( ! strcmp( interface, "wl_shm" ) )
      pDisplay->shm = wl_registry_bind ( registry, id,
                                         &wl_shm_interface, 1 );
}
static void fghRegistryGlobalRemove( void* data,
                                     struct wl_registry* registry,
                                     uint32_t id )
{
}
static const struct wl_registry_listener fghRegistryListener =
{
    fghRegistryGlobal,
    fghRegistryGlobalRemove
};


static void fghInitialiseCursorTheme(void)
{
    fgDisplay.pDisplay.cursor_theme = wl_cursor_theme_load (
                                        "default", 32,
                                        fgDisplay.pDisplay.shm );
};

void fgPlatformInitialize( const char* displayName )
{
    fgDisplay.pDisplay.display = wl_display_connect( NULL );

    if( fgDisplay.pDisplay.display == NULL )
        fgError( "failed to connect to a Wayland compositor" );

    fgDisplay.pDisplay.registry = wl_display_get_registry(
                                    fgDisplay.pDisplay.display );
    wl_registry_add_listener( fgDisplay.pDisplay.registry,
                              &fghRegistryListener,
                              &fgDisplay.pDisplay );
    wl_display_roundtrip( fgDisplay.pDisplay.display );

    if( fgDisplay.pDisplay.compositor == NULL ||
        fgDisplay.pDisplay.shell == NULL ||
        fgDisplay.pDisplay.seat == NULL ||
        fgDisplay.pDisplay.shm == NULL )
          fgError( "failed to discover all needed compositor interfaces" );

    fghInitialiseCursorTheme();

    fghPlatformInitializeEGL();

    /* Get start time */
    fgState.Time = fgSystemTime();

    fgState.Initialised = GL_TRUE;

    atexit(fgDeinitialize);

    /* InputDevice uses GlutTimerFunc(), so fgState.Initialised must be TRUE */
    fgPlatformInitialiseInputDevices();
}


void fgPlatformDeinitialiseInputDevices ( void )
{
    fgPlatformCloseInputDevices();

    fgState.InputDevsInitialised = GL_FALSE;
}


void fgPlatformCloseDisplay ( void )
{
    wl_cursor_theme_destroy( fgDisplay.pDisplay.cursor_theme );

    wl_shm_destroy( fgDisplay.pDisplay.shm );
    wl_seat_destroy( fgDisplay.pDisplay.seat );
    wl_shell_destroy( fgDisplay.pDisplay.shell );
    wl_compositor_destroy( fgDisplay.pDisplay.compositor );
    wl_registry_destroy( fgDisplay.pDisplay.registry );

    wl_display_disconnect( fgDisplay.pDisplay.display );
}

