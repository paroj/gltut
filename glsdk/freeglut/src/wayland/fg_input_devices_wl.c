/*
 * fg_input_devices_wl.c
 *
 * Handles Wayland input devices : keyboard, pointer, touchscreen.
 *
 * Written by Manuel Bachmann <tarnyko@tarnyko.net> 2015
 *
 * Copyright (c) 2015 Manuel Bachmann. All Rights Reserved.
 * Creation date: Thur Mar 19 2015
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

#ifdef __linux__
#include <linux/input.h>
#else
#define BTN_LEFT    0x110
#define BTN_RIGHT   0x111
#define BTN_MIDDLE  0x112
#endif
#include <sys/mman.h>
#include <GL/freeglut.h>
#include "../fg_internal.h"

/*
 * This function will effectively set the pointer (mouse) cursor
 * depending on the GLUT_CURSOR_* choice.
 */
void fghPointerSetCursor( SFG_Window* window,
                          struct wl_pointer* pointer,
                          uint32_t serial )
{
    struct wl_cursor_image* image;
    struct wl_buffer* buffer;

    image = window->Window.pContext.cursor->images[0];
    buffer = wl_cursor_image_get_buffer( image );

    wl_surface_attach( window->Window.pContext.cursor_surface, buffer,
                       0, 0 );
    wl_surface_damage( window->Window.pContext.cursor_surface, 0, 0,
                       image->width, image->height );
    wl_surface_commit( window->Window.pContext.cursor_surface );

    wl_pointer_set_cursor( pointer, serial,
                           window->Window.pContext.cursor_surface,
                           image->hotspot_x, image->hotspot_y );
}

/*
 * This function will interpret a keyboard keysym, and call the
 * possible callbacks accordingly.
 */
void fghKeyboardInterpretKeysym(  SFG_Window* window,
                                  uint32_t key,
                                  xkb_keysym_t sym,
                                  uint32_t state )
{
    FGCBKeyboardUC keyboard_cb;
    FGCBSpecialUC special_cb;
    FGCBUserData keyboard_ud;
    FGCBUserData special_ud;
    char string[16];
    int special = -1;

    /* GLUT API tells us to have two separate callbacks, one for
     * the ASCII translateable keypresses, and one for all the
     * others, which need to be translated to GLUT_KEY_Xs... */
    if( state )
    {
        keyboard_cb = (FGCBKeyboardUC)( FETCH_WCB( *window, Keyboard ));
        special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, Special  ));
        keyboard_ud = FETCH_USER_DATA_WCB( *window, Keyboard );
        special_ud  = FETCH_USER_DATA_WCB( *window, Special  );
    }
    else
    {
        keyboard_cb = (FGCBKeyboardUC)( FETCH_WCB( *window, KeyboardUp ));
        special_cb  = (FGCBSpecialUC) ( FETCH_WCB( *window, SpecialUp  ));
        keyboard_ud = FETCH_USER_DATA_WCB( *window, KeyboardUp );
        special_ud  = FETCH_USER_DATA_WCB( *window, SpecialUp  );
    }

    switch( sym )
    {
    case XKB_KEY_F1:        special = GLUT_KEY_F1;        break;
    case XKB_KEY_F2:        special = GLUT_KEY_F2;        break;
    case XKB_KEY_F3:        special = GLUT_KEY_F3;        break;
    case XKB_KEY_F4:        special = GLUT_KEY_F4;        break;
    case XKB_KEY_F5:        special = GLUT_KEY_F5;        break;
    case XKB_KEY_F6:        special = GLUT_KEY_F6;        break;
    case XKB_KEY_F7:        special = GLUT_KEY_F7;        break;
    case XKB_KEY_F8:        special = GLUT_KEY_F8;        break;
    case XKB_KEY_F9:        special = GLUT_KEY_F9;        break;
    case XKB_KEY_F10:       special = GLUT_KEY_F10;       break;
    case XKB_KEY_F11:       special = GLUT_KEY_F11;       break;
    case XKB_KEY_F12:       special = GLUT_KEY_F12;       break;
    case XKB_KEY_Left:      special = GLUT_KEY_LEFT;      break;
    case XKB_KEY_Right:     special = GLUT_KEY_RIGHT;     break;
    case XKB_KEY_Up:        special = GLUT_KEY_UP;        break;
    case XKB_KEY_Down:      special = GLUT_KEY_DOWN;      break;
    case XKB_KEY_Page_Up:   special = GLUT_KEY_PAGE_UP;   break;
    case XKB_KEY_Page_Down: special = GLUT_KEY_PAGE_DOWN; break;
    case XKB_KEY_Home:      special = GLUT_KEY_HOME;      break;
    case XKB_KEY_End:       special = GLUT_KEY_END;       break;
    case XKB_KEY_Insert:    special = GLUT_KEY_INSERT;    break;
    case XKB_KEY_Num_Lock:  special = GLUT_KEY_NUM_LOCK;  break;
    case XKB_KEY_Begin:     special = GLUT_KEY_BEGIN;     break;
    case XKB_KEY_Delete:    special = GLUT_KEY_DELETE;    break;
    case XKB_KEY_Shift_L:   special = GLUT_KEY_SHIFT_L;   break;
    case XKB_KEY_Shift_R:   special = GLUT_KEY_SHIFT_R;   break;
    case XKB_KEY_Control_L: special = GLUT_KEY_CTRL_L;    break;
    case XKB_KEY_Control_R: special = GLUT_KEY_CTRL_R;    break;
    case XKB_KEY_Alt_L:     special = GLUT_KEY_ALT_L;     break;
    case XKB_KEY_Alt_R:     special = GLUT_KEY_ALT_R;     break;
    }

    if( special_cb && (special != -1) )
    {
        fgSetWindow( window );
        special_cb( special, window->State.MouseX, window->State.MouseY, special_ud );
    }
    else if( keyboard_cb && (special == -1) )
    {
        fgSetWindow( window );
        xkb_keysym_to_utf8( sym, string, sizeof( string ) );
        keyboard_cb( string[0], window->State.MouseX, window->State.MouseY, keyboard_ud );
    }
}


/*
 * Touchscreen section
 * For now, let us pretend it is a mouse with only one button
 */
static void fghTouchDown( void* data, struct wl_touch* touch,
                          uint32_t serial, uint32_t time,
                          struct wl_surface* surface,
                          int32_t id,
                          wl_fixed_t x_w, wl_fixed_t y_w )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    win->State.MouseX = wl_fixed_to_int( x_w );
    win->State.MouseY = wl_fixed_to_int( y_w );
    INVOKE_WCB( *win, Mouse, ( GLUT_LEFT_BUTTON,
                               GLUT_DOWN,
                               win->State.MouseX,
                               win->State.MouseY ) );
}
static void fghTouchUp( void* data, struct wl_touch* touch,
                        uint32_t serial, uint32_t time,
                        int32_t id )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    INVOKE_WCB( *win, Mouse, ( GLUT_LEFT_BUTTON,
                               GLUT_UP,
                               win->State.MouseX,
                               win->State.MouseY ) );
}
static void fghTouchMotion( void* data, struct wl_touch* touch,
                            uint32_t time, int32_t id,
                            wl_fixed_t x_w, wl_fixed_t y_w )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    win->State.MouseX = wl_fixed_to_int( x_w );
    win->State.MouseY = wl_fixed_to_int( y_w );
    INVOKE_WCB( *win, Motion, ( win->State.MouseX,
                                win->State.MouseY ) );
}
static void fghTouchFrame( void* data, struct wl_touch* touch )
{
}
static void fghTouchCancel( void* data, struct wl_touch* touch )
{
}
static const struct wl_touch_listener fghTouchListener =
{
	fghTouchDown,
	fghTouchUp,
	fghTouchMotion,
	fghTouchFrame,
	fghTouchCancel
};


/*
 * Pointer (mouse) section
 */
static void fghPointerEnter( void* data, struct wl_pointer* pointer,
                             uint32_t serial,
                             struct wl_surface* surface,
                             wl_fixed_t x_w, wl_fixed_t y_w )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    fghPointerSetCursor( win, pointer, serial );
    win->State.MouseX = wl_fixed_to_int( x_w );
    win->State.MouseY = wl_fixed_to_int( y_w );
    INVOKE_WCB( *win, Entry, ( GLUT_ENTERED ) );
}
static void fghPointerLeave( void* data, struct wl_pointer* pointer,
                             uint32_t serial,
                             struct wl_surface* surface )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    INVOKE_WCB( *win, Entry, ( GLUT_LEFT ) );
}
static void fghPointerMotion( void* data, struct wl_pointer* pointer,
                              uint32_t time,
                              wl_fixed_t x_w, wl_fixed_t y_w )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    win->State.MouseX = wl_fixed_to_int( x_w );
    win->State.MouseY = wl_fixed_to_int( y_w );

    if ( win->Window.pContext.pointer_button_pressed )
      INVOKE_WCB( *win, Motion, ( win->State.MouseX,
                                  win->State.MouseY ) );
    else
      INVOKE_WCB( *win, Passive, ( win->State.MouseX,
                                   win->State.MouseY ) );
}
static void fghPointerButton( void* data, struct wl_pointer* pointer,
                              uint32_t serial, uint32_t time,
                              uint32_t button, uint32_t state )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    int button_f;

    switch( button )
    {
    case BTN_LEFT:
        button_f = GLUT_LEFT_BUTTON;
        break;
    case BTN_RIGHT:
        button_f = GLUT_RIGHT_BUTTON;
        break;
    case BTN_MIDDLE:
        button_f = GLUT_MIDDLE_BUTTON;
        break;
    }

    win->Window.pContext.pointer_button_pressed =
      state ? GL_TRUE : GL_FALSE;

    INVOKE_WCB( *win, Mouse, ( button_f,
                               state ? GLUT_DOWN : GLUT_UP ,
                               win->State.MouseX,
                               win->State.MouseY ) );
}
static void fghPointerAxis( void* data, struct wl_pointer* pointer,
                            uint32_t time, uint32_t axis,
                            wl_fixed_t value )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    int direction = wl_fixed_to_int( value );

    INVOKE_WCB( *win, MouseWheel, ( 0,
                                    direction ,
                                    win->State.MouseX,
                                    win->State.MouseY ) );
}
static const struct wl_pointer_listener fghPointerListener =
{
	fghPointerEnter,
	fghPointerLeave,
	fghPointerMotion,
	fghPointerButton,
	fghPointerAxis
};


/*
 * Keyboard section
 */
static void fghKeyboardKeymap( void* data, struct wl_keyboard* keyboard,
                               uint32_t format, int fd, uint32_t size )
{
    SFG_PlatformDisplay* pDisplay = data;
    char* keymap_str;
    struct xkb_keymap* keymap;

    keymap_str = mmap( NULL, size, PROT_READ, MAP_SHARED, fd, 0 );
    keymap = xkb_keymap_new_from_string( pDisplay->xkb_context,
                                         keymap_str,
                                         XKB_KEYMAP_FORMAT_TEXT_V1,
                                         0 );
    munmap( keymap_str, size );

    if( pDisplay->xkb_state )
      xkb_state_unref( pDisplay->xkb_state );
    pDisplay->xkb_state = xkb_state_new( keymap );
}
static void fghKeyboardEnter( void* data, struct wl_keyboard* keyboard,
                              uint32_t serial, struct wl_surface* surface,
                              struct wl_array* keys )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    INVOKE_WCB( *win, Entry, ( GLUT_ENTERED ) );
}
static void fghKeyboardLeave( void* data, struct wl_keyboard* keyboard,
                              uint32_t serial, struct wl_surface* surface )
{
    SFG_Window* win = fgStructure.CurrentWindow;
    INVOKE_WCB( *win, Entry, ( GLUT_LEFT ) );
}
static void fghKeyboardKey( void* data, struct wl_keyboard* keyboard,
                            uint32_t serial, uint32_t time,
                            uint32_t key, uint32_t state )
{
    SFG_PlatformDisplay* pDisplay = data;
    SFG_Window* win = fgStructure.CurrentWindow;
    const xkb_keysym_t* syms;

    xkb_state_key_get_syms( pDisplay->xkb_state,
                            key + 8, &syms );
    fghKeyboardInterpretKeysym( win, key, syms[0], state );
}
static void fghKeyboardModifiers( void* data, struct wl_keyboard* keyboard,
                                  uint32_t serial, uint32_t mods_depr,
                                  uint32_t mods_latch, uint32_t mods_lock,
                                  uint32_t group )
{
}
static const struct wl_keyboard_listener fghKeyboardListener =
{
        fghKeyboardKeymap,
	fghKeyboardEnter,
	fghKeyboardLeave,
	fghKeyboardKey,
	fghKeyboardModifiers
};


/*
 * Discover potential input device(s) (keyboard, pointer, touch)
 */
static void fghSeatCapabilities( void* data,
                                 struct wl_seat* seat,
                                 enum wl_seat_capability capabilities )
{
    SFG_PlatformDisplay* pDisplay = data;

    if( capabilities & WL_SEAT_CAPABILITY_KEYBOARD )
    {
        pDisplay->xkb_context = xkb_context_new ( 0 );
        pDisplay->keyboard = wl_seat_get_keyboard( seat );
        wl_keyboard_add_listener( pDisplay->keyboard,
                                  &fghKeyboardListener,
                                  pDisplay );
    }

    if( capabilities & WL_SEAT_CAPABILITY_POINTER )
    {
        pDisplay->pointer = wl_seat_get_pointer( seat );
        wl_pointer_add_listener( pDisplay->pointer,
                                 &fghPointerListener,
                                 pDisplay );
    }

    if( capabilities & WL_SEAT_CAPABILITY_TOUCH )
    {
        pDisplay->touch = wl_seat_get_touch( seat );
        wl_touch_add_listener( pDisplay->touch,
                               &fghTouchListener,
                               pDisplay );
    }
}
static const struct wl_seat_listener fghSeatListener =
{
    fghSeatCapabilities
};


/*
 * Try initializing the input device(s)
 */
void fgPlatformInitialiseInputDevices( void )
{
    wl_seat_add_listener( fgDisplay.pDisplay.seat,
                          &fghSeatListener,
                          &fgDisplay.pDisplay );

    wl_display_roundtrip( fgDisplay.pDisplay.display );
}

/*
 * Try closing the input device(s)
 */
void fgPlatformCloseInputDevices( void )
{
    if( fgDisplay.pDisplay.touch )
      wl_touch_destroy( fgDisplay.pDisplay.touch );
    if( fgDisplay.pDisplay.pointer )
      wl_pointer_destroy( fgDisplay.pDisplay.pointer );
    if( fgDisplay.pDisplay.keyboard )
      wl_keyboard_destroy( fgDisplay.pDisplay.keyboard );
    if( fgDisplay.pDisplay.xkb_state )
      xkb_state_unref( fgDisplay.pDisplay.xkb_state );
    if( fgDisplay.pDisplay.xkb_context )
      xkb_context_unref( fgDisplay.pDisplay.xkb_context );
}


/*
 * Wayland backend will not be implementing spaceball at all
 */
void fgPlatformInitializeSpaceball( void )
{
}
void fgPlatformSpaceballClose( void )
{
}
void fgPlatformSpaceballSetWindow( SFG_Window *window )
{
}
int fgPlatformHasSpaceball( void )
{
    return 0;
}
int fgPlatformSpaceballNumButtons( void )
{
    return 0;
}

