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

#import <Cocoa/Cocoa.h>

void fghOnReshapeNotify( SFG_Window *window, int width, int height, GLboolean forceNotify );
void fghOnPositionNotify( SFG_Window *window, int x, int y, GLboolean forceNotify );

/* CVDisplayLink callback function */
CVReturn fgDisplayLinkCallback( CVDisplayLinkRef displayLink,
    const CVTimeStamp                           *now,
    const CVTimeStamp                           *outputTime,
    CVOptionFlags                                flagsIn,
    CVOptionFlags                               *flagsOut,
    void                                        *displayLinkContext );

enum { FG_MOUSE_WHEEL_Y = 0, FG_MOUSE_WHEEL_X = 1 };
static const double fgWheelThreshold = 1.0; // Threshold for mouse wheel events. TODO: decide on a suitable value

BOOL shouldQuit = NO;

/*****************************************************************
 * Window Delegate                                               *
 *****************************************************************/

@interface                       fgWindowDelegate : NSObject <NSWindowDelegate>
@property ( assign ) SFG_Window *fgWindow; // Freeglut’s window structure
@end

@implementation fgWindowDelegate

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    glutDestroyWindow( self.fgWindow->ID ); // Freeglut’s window cleanup
    shouldQuit = YES;
    return YES;
}

- (void)windowDidChangeOcclusionState:(NSNotification *)notification
{
    BOOL isVisible               = [notification.object occlusionState] & NSWindowOcclusionStateVisible;
    self.fgWindow->State.Visible = isVisible;

    if ( isVisible ) {
        INVOKE_WCB( *self.fgWindow, WindowStatus, ( GLUT_FULLY_RETAINED ) );
    }
    else {
        INVOKE_WCB( *self.fgWindow, WindowStatus, ( GLUT_FULLY_COVERED ) );
    }
}
@end

/*****************************************************************
 * OpenGL View                                                   *
 *****************************************************************/

@interface                       fgOpenGLView : NSOpenGLView
@property ( assign ) SFG_Window *fgWindow; // Freeglut’s window structure
@end

@implementation fgOpenGLView

/*
 * Standardizes key codes across platforms by mapping macOS-specific key codes
 * to universal key codes.  This normalization must occur before conversion to special keys to ensure
 * special keys are handled correctly.
 */
+ (uint16_t)standardizeKeyCode:(uint16_t)key
{
    switch ( key ) {
    case 0x7F:       // macOS Delete key (forward delete)
        return 0x08; // Maps to universal Backspace key code
    default:
        return (uint16_t)key;
    }
}

/*
 * Handles the conversion of various non-character keys including:
 * - Arrow keys (up, down, left, right)
 * - Function keys (F1-F12)
 * - Navigation keys (Home, End, Page Up/Down, Insert, Delete)
 */
+ (char)convertFunctionKeyToGlutSpecial:(uint16_t)key
{
    switch ( key ) {
    case NSUpArrowFunctionKey:
        return GLUT_KEY_UP;
    case NSDownArrowFunctionKey:
        return GLUT_KEY_DOWN;
    case NSLeftArrowFunctionKey:
        return GLUT_KEY_LEFT;
    case NSRightArrowFunctionKey:
        return GLUT_KEY_RIGHT;

    case NSF1FunctionKey:
        return GLUT_KEY_F1;
    case NSF2FunctionKey:
        return GLUT_KEY_F2;
    case NSF3FunctionKey:
        return GLUT_KEY_F3;
    case NSF4FunctionKey:
        return GLUT_KEY_F4;
    case NSF5FunctionKey:
        return GLUT_KEY_F5;
    case NSF6FunctionKey:
        return GLUT_KEY_F6;
    case NSF7FunctionKey:
        return GLUT_KEY_F7;
    case NSF8FunctionKey:
        return GLUT_KEY_F8;
    case NSF9FunctionKey:
        return GLUT_KEY_F9;
    case NSF10FunctionKey:
        return GLUT_KEY_F10;
    case NSF11FunctionKey:
        return GLUT_KEY_F11;
    case NSF12FunctionKey:
        return GLUT_KEY_F12;

    case NSPageUpFunctionKey:
        return GLUT_KEY_PAGE_UP;
    case NSPageDownFunctionKey:
        return GLUT_KEY_PAGE_DOWN;
    case NSHomeFunctionKey:
        return GLUT_KEY_HOME;
    case NSEndFunctionKey:
        return GLUT_KEY_END;
    case NSInsertFunctionKey:
    case NSInsertCharFunctionKey:
        return GLUT_KEY_INSERT;
    case NSDeleteFunctionKey:
    case NSDeleteCharFunctionKey:
        return GLUT_KEY_DELETE;
    }
    return (char)key;
}

/*
 * Converts macOS modifier key codes to their corresponding GLUT special key constants.
 *
 * Note: Modifer key codes overlap standard key codes, so this conversion only applies to
 * modifier keys.
 */
+ (char)convertModifierToGlutSpecial:(uint16_t)modifierKey
{
    switch ( modifierKey ) {
    // macOS hardware key codes for modifier keys
    case 0x38: // Left Shift
        return GLUT_KEY_SHIFT_L;
    case 0x3C: // Right Shift
        return GLUT_KEY_SHIFT_R;
    case 0x3B: // Left Control
        return GLUT_KEY_CTRL_L;
    case 0x3E: // Right Control
        return GLUT_KEY_CTRL_R;
    case 0x3A: // Left Option (Alt)
        return GLUT_KEY_ALT_L;
    case 0x3D: // Right Option (Alt)
        return GLUT_KEY_ALT_R;
    case 0x37: // Left Command
        return GLUT_KEY_SUPER_L;
    case 0x36: // Right Command
        return GLUT_KEY_SUPER_R;
    }
    return (char)modifierKey;
}

- (BOOL)acceptsFirstResponder
{
    return YES; // Allow the view to receive keyboard events
}

#pragma mark Mouse Section

- (NSPoint)mouseLocation:(NSEvent *)event fromOutsideEvent:(BOOL)fromOutside
{
    NSPoint mouseLoc;
    if ( fromOutside ) {
        // Get mouse location even when the event occurred outside the event (used for key events)
        mouseLoc = [[self window] mouseLocationOutsideOfEventStream];
    }
    else {
        // Get mouse location from the event itself
        mouseLoc = [event locationInWindow];
    }

    // Convert the point to view coordinates
    mouseLoc = [self convertPoint:mouseLoc fromView:nil];
    int x    = (int)mouseLoc.x;
    int y    = (int)( self.bounds.size.height - mouseLoc.y ); // Flip y for OpenGL

    return NSMakePoint( x, y );
}

/* Enable mouse movement events */
- (BOOL)acceptsMouseMovedEvents
{
    return YES;
}

/* Left button */
- (void)mouseDown:(NSEvent *)event
{
    [self handleMouseEvent:event withButton:GLUT_LEFT_BUTTON state:GLUT_DOWN];
}

- (void)mouseUp:(NSEvent *)event
{
    [self handleMouseEvent:event withButton:GLUT_LEFT_BUTTON state:GLUT_UP];
}

/* Right button */
- (void)rightMouseDown:(NSEvent *)event
{
    [self handleMouseEvent:event withButton:GLUT_RIGHT_BUTTON state:GLUT_DOWN];
}

- (void)rightMouseUp:(NSEvent *)event
{
    [self handleMouseEvent:event withButton:GLUT_RIGHT_BUTTON state:GLUT_UP];
}

/* Middle button */
- (void)otherMouseDown:(NSEvent *)event
{
    int button = ( [event buttonNumber] == 2 ) ? GLUT_MIDDLE_BUTTON : [event buttonNumber];
    [self handleMouseEvent:event withButton:button state:GLUT_DOWN];
}

- (void)otherMouseUp:(NSEvent *)event
{
    int button = ( [event buttonNumber] == 2 ) ? GLUT_MIDDLE_BUTTON : [event buttonNumber];
    [self handleMouseEvent:event withButton:button state:GLUT_UP];
}

/* Centralized handler for mouse events */
- (void)handleMouseEvent:(NSEvent *)event withButton:(int)button state:(int)state
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:NO];
    INVOKE_WCB( *self.fgWindow, Mouse, ( button, state, mouseLoc.x, mouseLoc.y ) );
}

/* Passive motion: mouse moves with no buttons pressed */
- (void)mouseMoved:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:NO];
    INVOKE_WCB( *self.fgWindow, Passive, ( mouseLoc.x, mouseLoc.y ) );
}

/* Active motion: left mouse moves with a button pressed */
- (void)mouseDragged:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:NO];
    INVOKE_WCB( *self.fgWindow, Motion, ( mouseLoc.x, mouseLoc.y ) );
}

- (void)rightMouseDragged:(NSEvent *)event
{
    [self mouseDragged:event];
}

- (void)otherMouseDragged:(NSEvent *)event
{
    [self mouseDragged:event];
}

- (void)scrollWheel:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    static double FGUNUSED bufferedX = 0.0;
    static double          bufferedY = 0.0;

    // Get mouse coordinates in the view
    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:NO];

    double FGUNUSED deltaX = [event scrollingDeltaX];
    double          deltaY = [event scrollingDeltaY];

    if ( [event hasPreciseScrollingDeltas] ) {
        deltaX *= 0.1;
        deltaY *= 0.1;
    }

    // unofficial horizontal scrolling - calls MouseWheel with wheel = fgMouseXWheel (1)
#ifdef REPORT_MOUSEWHEEL_X_AXIS
    if ( fabs( bufferedX ) > fgWheelThreshold ) {
        int direction = ( bufferedX > 0 ) ? GLUT_UP : GLUT_DOWN;
        INVOKE_WCB( *self.fgWindow, MouseWheel, ( fgMouseXWheel, direction, x, y ) );
        bufferedX = 0.0;
    }
    else {
        bufferedX += deltaX;
    }
#endif

    // TODO: Decide on a suitable threshold for scrolling events
    // Macos sends a lot of small delta values, so we need to filter them if we want to match the
    // behavior of other platforms
    bufferedY += deltaY;
    while ( fabs( bufferedY ) > fgWheelThreshold ) {
        int direction = ( bufferedY > 0 ) ? 1 : -1;
        INVOKE_WCB( *self.fgWindow, MouseWheel, ( FG_MOUSE_WHEEL_Y, direction, mouseLoc.x, mouseLoc.y ) );
        bufferedY -= direction * fgWheelThreshold;
    }
}

#pragma mark Key Section

- (void)updateModifiers:(NSEvent *)event
{
    // Update the modifier key state
    int modifiers = 0;
    if ( [event modifierFlags] & NSEventModifierFlagShift ) {
        modifiers |= GLUT_ACTIVE_SHIFT;
    }
    if ( [event modifierFlags] & NSEventModifierFlagControl ) {
        modifiers |= GLUT_ACTIVE_CTRL;
    }
    if ( [event modifierFlags] & NSEventModifierFlagOption ) {
        modifiers |= GLUT_ACTIVE_ALT;
    }
    if ( [event modifierFlags] & NSEventModifierFlagCommand ) {
        modifiers |= GLUT_ACTIVE_SUPER;
    }
    fgState.Modifiers = modifiers;
}

/* Handles individual modifier key changes */
- (void)flagsChanged:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    NSEventModifierFlags flags   = [event modifierFlags];
    uint16_t             keyCode = [event keyCode];

    // updates the modifier freeglut state
    [self updateModifiers:event];

    // now lets notify any special key press callbacks
    int  state      = -1;
    char specialKey = [fgOpenGLView convertModifierToGlutSpecial:keyCode];

    switch ( specialKey ) {
    case GLUT_KEY_SHIFT_L:
    case GLUT_KEY_SHIFT_R:
        state = ( flags & NSEventModifierFlagShift ) ? GLUT_DOWN : GLUT_UP;
        break;
    case GLUT_KEY_CTRL_L:
    case GLUT_KEY_CTRL_R:
        state = ( flags & NSEventModifierFlagControl ) ? GLUT_DOWN : GLUT_UP;
        break;
    case GLUT_KEY_ALT_L: // Option key on macOS
    case GLUT_KEY_ALT_R:
        state = ( flags & NSEventModifierFlagOption ) ? GLUT_DOWN : GLUT_UP;
        break;
    case GLUT_KEY_SUPER_L:
    case GLUT_KEY_SUPER_R:
        state = ( flags & NSEventModifierFlagCommand ) ? GLUT_DOWN : GLUT_UP;
        break;
    default:
        return; // Ignore unmapped keys
    }

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:YES];

    if ( state == GLUT_DOWN ) {
        INVOKE_WCB( *self.fgWindow, Special, ( specialKey, mouseLoc.x, mouseLoc.y ) );
    }
    else {
        INVOKE_WCB( *self.fgWindow, SpecialUp, ( specialKey, mouseLoc.x, mouseLoc.y ) );
    }
}

- (void)keyDown:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    if ( ![[event characters] length] ) {
        return; // Ignore events with no characters
    }

    unichar key    = [[event charactersIgnoringModifiers] characterAtIndex:0];
    key            = [fgOpenGLView standardizeKeyCode:key];
    char convKey   = [fgOpenGLView convertFunctionKeyToGlutSpecial:key];
    BOOL isSpecial = ( convKey != key );

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:YES];

    if ( isSpecial ) {
        INVOKE_WCB( *self.fgWindow, Special, ( convKey, mouseLoc.x, mouseLoc.y ) );
    }
    else {
        INVOKE_WCB( *self.fgWindow, Keyboard, ( convKey, mouseLoc.x, mouseLoc.y ) );
    }
}

- (void)keyUp:(NSEvent *)event
{
    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    if ( ![[event characters] length] ) {
        return; // Ignore events with no characters
    }

    uint16_t key   = [[event charactersIgnoringModifiers] characterAtIndex:0];
    key            = [fgOpenGLView standardizeKeyCode:key];
    char convKey   = [fgOpenGLView convertFunctionKeyToGlutSpecial:key];
    BOOL isSpecial = ( convKey != key );

    NSPoint mouseLoc = [self mouseLocation:event fromOutsideEvent:YES];

    if ( isSpecial ) {
        INVOKE_WCB( *self.fgWindow, SpecialUp, ( convKey, mouseLoc.x, mouseLoc.y ) );
    }
    else {
        INVOKE_WCB( *self.fgWindow, KeyboardUp, ( convKey, mouseLoc.x, mouseLoc.y ) );
    }
}

#pragma mark -

/*
 * Handle window resize events - notify freeglut
 */

- (void)reshape
{
    [super reshape];

    if ( !self.fgWindow ) {
        fgError( "Freeglut window not set for %s", __func__ );
    }

    NSWindow *window        = self.fgWindow->Window.Handle;
    NSRect    frame         = [window contentRectForFrameRect:[window frame]];
    NSRect    backingBounds = [self convertRectToBacking:[self bounds]];

    /* Update the window size */
    SFG_PlatformWindowState *pWState = &self.fgWindow->State.pWState;
    pWState->FrameBufferWidth        = (int)backingBounds.size.width;
    pWState->FrameBufferHeight       = (int)backingBounds.size.height;

    /* Update state and call callback, if there was a change */
    fghOnPositionNotify( self.fgWindow, frame.origin.x, frame.origin.y, GL_FALSE );
    fghOnReshapeNotify( self.fgWindow, pWState->FrameBufferWidth, pWState->FrameBufferHeight, GL_FALSE );

    // TODO: Resizing the window with accumulation buffers does not work correctly, may need to get creative and
    // reinitialize the openGL context
}

@end

/*
 * Freeglut request a window resize
 */
void fgPlatformReshapeWindow( SFG_Window *window, int width, int height )
{
    printf( "fgPlatformReshapeWindow, width: %d, height: %d\n", width, height );
    NSWindow *nsWindow = (NSWindow *)window->Window.Handle;
    [nsWindow setContentSize:NSMakeSize( width, height )];

    // Update OpenGL viewport
    [(NSOpenGLContext *)window->Window.Context makeCurrentContext];
    glViewport( 0, 0, width, height );
}

BOOL isValidOpenGLContext( int MajorVersion, int MinorVersion, int ContextFlags, int ContextProfile )
{
    // Case 1: OpenGL 2.1 or below (Compatibility mode)
    if ( MajorVersion < 2 || ( MajorVersion == 2 && MinorVersion <= 1 ) ) {
        if ( ContextProfile != 0 && ContextProfile != GLUT_COMPATIBILITY_PROFILE ) {
            return NO; // Profile must be compatibility or unspecified for 2.1
        }
        return YES; // Valid configuration
    }

    // Case 2: OpenGL 3.2 through 4.1 (Core Profile only)
    if ( ( MajorVersion == 3 && MinorVersion >= 2 ) || ( MajorVersion == 4 && MinorVersion <= 1 ) ) {

        // Must be Core Profile
        if ( ContextProfile != GLUT_CORE_PROFILE ) {
            return NO; // Only Core Profile is supported for 3.2+
        }
        return YES; // Valid configuration
    }

    // Case 3: OpenGL 3.0-3.1 (not supported on macOS)
    if ( MajorVersion == 3 && MinorVersion < 2 ) {
        return NO;
    }

    // Case 4: OpenGL 4.2+ (not supported on macOS)
    if ( MajorVersion > 4 || ( MajorVersion == 4 && MinorVersion > 1 ) ) {
        return NO;
    }

    return NO; // Any other configuration is invalid
}

/*
 * Set the current window’s OpenGL context
 * This is a long function, but it’s mostly boilerplate code so keeping it all in one place
 */
void fgPlatformOpenWindow( SFG_Window *window,
    const char                        *title,
    GLboolean                          positionUse,
    int                                x,
    int                                y,
    GLboolean                          sizeUse,
    int                                w,
    int                                h,
    GLboolean                          gameMode,
    GLboolean                          isSubWindow )
{
    //
    // 0. Sanity Checks
    //

    if ( fgState.ContextFlags & GLUT_DEBUG ) {
        fgWarning( "WARNING - Debug context requested, but not supported on macOS, ignoring" );
        fgState.ContextFlags &= ~GLUT_DEBUG;
    }

    if ( !isValidOpenGLContext(
             fgState.MajorVersion, fgState.MinorVersion, fgState.ContextFlags, fgState.ContextProfile ) ) {
        fgError(
            "ERROR - MacOS only supports Compatibility OpenGL 2.1 and below OR OpenGL Core Profile 3.2 through 4.1" );
    }

    //
    // 1. Define pixel format attributes based on fgState.DisplayMode
    //
    // TODO: Move this to a separate function to support fgPlatformGlutGet(GLUT_DISPLAY_MODE_POSSIBLE)
    //

    NSOpenGLPixelFormatAttribute attrs[32];
    int                          attrIndex = 0;
    attrs[attrIndex++]                     = NSOpenGLPFAAccelerated; // choose hardware acceleration
    attrs[attrIndex++]                     = NSOpenGLPFAColorSize;
    attrs[attrIndex++]                     = 24; // 8 bits per RGB channel
    attrs[attrIndex++]                     = NSOpenGLPFAAlphaSize;
    attrs[attrIndex++]                     = 8;
    if ( fgState.DisplayMode & GLUT_DOUBLE ) {
        attrs[attrIndex++] = NSOpenGLPFADoubleBuffer;
    }
    if ( fgState.DisplayMode & GLUT_DEPTH ) {
        // TODO make this configurable when glutInitDisplayString implementation is complete eg depth>=24
        attrs[attrIndex++] = NSOpenGLPFADepthSize;
        attrs[attrIndex++] = 24;
    }
    if ( fgState.DisplayMode & GLUT_STENCIL ) {
        // TODO make this configurable when glutInitDisplayString implementation is complete eg stencil<=8
        attrs[attrIndex++] = NSOpenGLPFAStencilSize;
        attrs[attrIndex++] = 8;
    }
    if ( fgState.DisplayMode & GLUT_ACCUM ) {
        // TODO make this configurable when glutInitDisplayString implementation is complete eg acca~32
        attrs[attrIndex++] = NSOpenGLPFAAccumSize;
        attrs[attrIndex++] = 32;
    }
    if ( fgState.DisplayMode & GLUT_AUX ) {
        attrs[attrIndex++] = NSOpenGLPFAAuxBuffers;
        attrs[attrIndex++] = fghNumberOfAuxBuffersRequested( );
    }
    if ( fgState.DisplayMode & GLUT_MULTISAMPLE ) {
        attrs[attrIndex++] = NSOpenGLPFAMultisample; // boolean
        attrs[attrIndex++] = NSOpenGLPFASampleBuffers;
        attrs[attrIndex++] = 1;
        attrs[attrIndex++] = NSOpenGLPFASamples;
        attrs[attrIndex++] = fgState.SampleNumber;
    }
    // profile selection
    attrs[attrIndex++] = NSOpenGLPFAOpenGLProfile;
    if ( fgState.MajorVersion == 3 )
        attrs[attrIndex++] = NSOpenGLProfileVersion3_2Core;
    else if ( fgState.MajorVersion == 4 )
        attrs[attrIndex++] = NSOpenGLProfileVersion4_1Core;
    else
        attrs[attrIndex++] = NSOpenGLProfileVersionLegacy;
    attrs[attrIndex++] = 0; // Null terminator

    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
    if ( !pixelFormat ) {
        fgError( "Failed to create pixel format" );
    }
    window->Window.pContext.PixelFormat = pixelFormat;

    //
    // 2. Create fgOpenGLView with the pixel format
    //

    // Flip y coordinate for OpenGL
    y = positionUse ? fgDisplay.ScreenHeight - y - h : fgDisplay.ScreenHeight - h;
    x = positionUse ? x : 0;

    NSRect        frame      = NSMakeRect( x, y, sizeUse ? w : 300, sizeUse ? h : 300 );
    fgOpenGLView *openGLView = [[fgOpenGLView alloc] initWithFrame:frame pixelFormat:pixelFormat];
    if ( !openGLView ) {
        fgError( "Failed to create fgOpenGLView" );
    }
    openGLView.fgWindow = window; // Link to the FreeGLUT window structure

    // TODO: Make this configurable, and handle transitions between high DPI and low DPI displays
    // FIXME: High DPI support is not fully implemented yet
    // Things to verify:
    //  - mouse coordinates are correct
    //  - window size is correct
    //  - OpenGL viewport is correct
    //  - OpenGL framebuffer size is correct
    [openGLView setWantsBestResolutionOpenGLSurface:NO];

    //
    // 3. Create NSWindow and set fgOpenGLView as content view
    //

    NSWindowStyleMask style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
                              NSWindowStyleMaskResizable;
    if ( window->IsMenu || gameMode || ( fgState.DisplayMode & GLUT_BORDERLESS ) ) {
        style = NSWindowStyleMaskBorderless;
    }
    NSWindow *nsWindow = [[NSWindow alloc] initWithContentRect:frame
                                                     styleMask:style
                                                       backing:NSBackingStoreBuffered
                                                         defer:NO];
    [nsWindow setAcceptsMouseMovedEvents:YES];
    [nsWindow setTitle:[NSString stringWithUTF8String:title ? title : "freeglut"]];
    window->Window.Handle = nsWindow;

    // use the fgOpenGLView as the content view
    [nsWindow setContentView:openGLView];

    //
    // 4. Set window delegate
    //

    fgWindowDelegate *delegate = [[fgWindowDelegate alloc] init];
    delegate.fgWindow          = window;
    [nsWindow setDelegate:delegate];

    //
    // 5. Retrieve the NSOpenGLContext from the fgOpenGLView
    //

    NSOpenGLContext *glContext = [openGLView openGLContext];
    if ( !glContext ) {
        fgError( "Failed to retrieve NSOpenGLContext from fgOpenGLView" );
    }
    window->Window.Context = glContext;

    //
    // 6. Make the context current for OpenGL rendering
    //

    [glContext makeCurrentContext];

    //
    // 7. Show the window if not a menu and make it first responder
    //

    if ( !window->IsMenu ) {
        [nsWindow makeKeyAndOrderFront:nil];
        [nsWindow makeFirstResponder:openGLView]; // Ensure view receives events
        window->State.Visible = GL_TRUE;
    }

    //
    // 8. Store initial window size
    //

    window->State.pWState.OldWidth  = frame.size.width;
    window->State.pWState.OldHeight = frame.size.height;

    // Get the actual framebuffer dimensions
    NSRect backingBounds                    = [openGLView convertRectToBacking:[openGLView bounds]];
    window->State.pWState.FrameBufferWidth  = (int)backingBounds.size.width;
    window->State.pWState.FrameBufferHeight = (int)backingBounds.size.height;

    //
    // 9. Setup CVLinkDisplay for VSync
    //

    // Create and configure CVDisplayLink
#ifdef USE_CVDISPLAYLINK
    if ( fgState.DisplayMode & GLUT_DOUBLE ) {
        CVDisplayLinkCreateWithActiveCGDisplays( (CVDisplayLinkRef *)&fgDisplay.pDisplay.DisplayLink );
        CVDisplayLinkSetOutputCallback(
            fgDisplay.pDisplay.DisplayLink, &fgDisplayLinkCallback, (__bridge void *)openGLView );
        CVDisplayLinkStart( fgDisplay.pDisplay.DisplayLink );
    }
#else
    // As of macOS 15, VSync is not functional, so CVDisplayLink is the recommended way to handle VSync

    // Set the swap interval parameter
    GLint swapInterval = 1; // 1 for VSync, 0 for no VSync
    [glContext setValues:&swapInterval forParameter:NSOpenGLContextParameterSwapInterval];
#endif

    DBG( "OpenGL Version: %s", glGetString( GL_VERSION ) );
    DBG( "Window: %dx%d\tFramebuffer: %dx%d",
        w,
        h,
        window->State.pWState.FrameBufferWidth,
        window->State.pWState.FrameBufferHeight );
}

/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fgPlatformCloseWindow( SFG_Window *window )
{
    NSWindow        *nsWindow = (NSWindow *)window->Window.Handle;
    NSOpenGLContext *context  = (NSOpenGLContext *)window->Window.Context;

    [context clearDrawable];

    [nsWindow close];

    [context release];
    [nsWindow release];
}

/*
 * This function makes the specified window visible
 */
void fgPlatformShowWindow( SFG_Window *window )
{
    TODO_IMPL;
}

/*
 * This function hides the specified window
 */
void fgPlatformHideWindow( SFG_Window *window )
{
    TODO_IMPL;
}

/*
 * Iconify the specified window (top-level windows only)
 */
void fgPlatformIconifyWindow( SFG_Window *window )
{
    TODO_IMPL;
}

/*
 * Set the current window's title
 */
void fgPlatformGlutSetWindowTitle( const char *str )
{
    TODO_IMPL;
}

/*
 * Set the current window's iconified title
 */
void fgPlatformGlutSetIconTitle( const char *str )
{
    TODO_IMPL;
}

/*
 * Change the specified window's position
 */
void fgPlatformPositionWindow( SFG_Window *window, int x, int y )
{
    TODO_IMPL;
}

/*
 * Lowers the specified window (by Z order change)
 */
void fgPlatformPushWindow( SFG_Window *window )
{
    TODO_IMPL;
}

/*
 * Raises the specified window (by Z order change)
 */
void fgPlatformPopWindow( SFG_Window *window )
{
    TODO_IMPL;
}

/*
 * Toggle the window's full screen state.
 */
void fgPlatformFullScreenToggle( SFG_Window *win )
{
    TODO_IMPL;
}

void fgPlatformSetWindow( SFG_Window *window )
{
    if ( window && window->Window.Context ) {
        [(NSOpenGLContext *)window->Window.Context makeCurrentContext];
    }
    else {
        [NSOpenGLContext clearCurrentContext];
    }
}
