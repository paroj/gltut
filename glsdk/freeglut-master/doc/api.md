# Table of Contents

1. [Introduction](#introduction)

2. [Background](#background)

	- [Design Philosophy](#design-philosophy)
	- [Conventions](#conventions)
		- [Window placement and size](#window-placement-and-size)
		- [User-data callbacks](#user-data-callbacks)
	- [Terminology](#terminology)
	- [Differences from GLUT 3.7](#differences-from-glut-37)
		- [glutMainLoop Behaviour](#glutmainloop-behaviour)
		- [Action on Window Closure](#action-on-window-closure)
		- [Fullscreen windows](#fullscreen-windows)
		- [Changes to Callbacks](#changes-to-callbacks)
		- [String Rendering](#string-rendering)
		- [Geometry Rendering](#geometry-rendering)
		- [Extension Function Queries](#extension-function-queries)

3. [Initialization Functions](#initialization-functions)

	- [glutInit](#glutinit)
	- [glutInitWindowPosition](#glutinitwindowposition)
	- [glutInitWindowSize](#glutinitwindowsize)
	- [glutInitDisplayMode](#glutinitdisplaymode)
	- [glutInitDisplayString](#glutinitdisplaystring)
	- [glutInitErrorFunc [fg]](#glutiniterrorfunc)
	- [glutInitWarningFunc [fg]](#glutinitwarningfunc)

4. [Event Processing Functions](#event-processing-functions)

	- [glutMainLoop](#glutmainloop)
	- [glutMainLoopEvent [fg]](#glutmainloopevent)
	- [glutLeaveMainLoop [fg]](#glutleavemainloop)

5. [Window Functions](#window-functions)

	- [glutCreateWindow](#glutcreatewindow)
	- [glutCreateSubwindow](#glutcreatesubwindow)
	- [glutDestroyWindow](#glutdestroywindow)
	- [glutSetWindow](#glutsetwindow)
	- [glutGetWindow](#glutgetwindow)
	- [glutSetWindowTitle](#glutsetwindowtitle)
	- [glutSetIconTitle](#glutseticontitle)
	- [glutReshapeWindow](#glutreshapewindow)
	- [glutPositionWindow](#glutpositionwindow)
	- [glutShowWindow](#glutshowwindow)
	- [glutHideWindow](#gluthidewindow)
	- [glutIconifyWindow](#gluticonifywindow)
	- [glutPushWindow](#glutpushwindow)
	- [glutPopWindow](#glutpopwindow)
	- [glutFullScreen](#glutfullscreen)
	- [glutLeaveFullScreen [fg]](#glutleavefullscreen)
	- [glutFullScreenToggle [fg]](#glutfullscreentoggle)

6. [Display Functions](#display-functions)

	- [glutPostRedisplay](#glutpostredisplay)
	- [glutPostWindowRedisplay](#glutpostwindowredisplay)
	- [glutSwapBuffers](#glutswapbuffers)

7. [Mouse Cursor Functions](#mouse-cursor-functions)

	- [glutSetCursor](#glutsetcursor)
	- [glutWarpPointer](#glutwarppointer)

8. [Overlay Functions](#overlay-functions)

	- [glutEstablishOverlay](#glutestablishoverlay)
	- [glutRemoveOverlay](#glutremoveoverlay)
	- [glutUseLayer](#glutuselayer)
	- [glutPostOverlayRedisplay](#glutpostoverlayredisplay)
	- [glutPostWindowOverlayRedisplay](#glutpostwindowoverlayredisplay)
	- [glutShowOverlay](#glutshowoverlay)
	- [glutHideOverlay](#gluthideoverlay)

9. [Menu Functions](#menu-functions)

	- [glutCreateMenu](#glutcreatemenu)
	- [glutDestroyMenu](#glutdestroymenu)
	- [glutGetMenu](#glutgetmenu)
	- [glutSetMenu](#glutsetmenu)
	- [glutAddMenuEntry](#glutaddmenuentry)
	- [glutAddSubMenu](#glutaddsubmenu)
	- [glutChangeToMenuEntry](#glutchangetomenuentry)
	- [glutChangeToSubMenu](#glutchangetosubmenu)
	- [glutSetMenuFont [fg]](#glutsetmenufont)
	- [glutRemoveMenuItem](#glutremovemenuitem)
	- [glutAttachMenu](#glutattachmenu)
	- [glutDetachMenu](#glutdetachmenu)
	- [glutMenuDestroyFunc [fg]](#glutmenudestroyfunc)

10. [Global Callback Registration Functions](#global-callback-registration-functions)

	- [glutTimerFunc](#gluttimerfunc)
	- [glutIdleFunc](#glutidlefunc)
	- [glutMenuStatusFunc](#glutmenustatusfunc)
	- [glutMenuStateFunc](#glutmenustatefunc)

11. [Window-Specific Callback Registration Functions](#global-callback-registration-functions)

	- [glutDisplayFunc](#glutdisplayfunc)
	- [glutOverlayDisplayFunc](#glutoverlaydisplayfunc)
	- [glutReshapeFunc](#glutreshapefunc)
	- [glutPositionFunc [fg]](#glutpositionfunc)
	- [glutCloseFunc [fg]](#glutclosefunc)
	- [glutKeyboardFunc](#glutkeyboardfunc)
	- [glutSpecialFunc](#glutspecialfunc)
	- [glutKeyboardUpFunc](#glutkeyboardupfunc)
	- [glutSpecialUpFunc](#glutspecialupfunc)
	- [glutMotionFunc](#glutmotionfunc)
	- [glutPassiveMotionFunc](#glutpassivemotionfunc)
	- [glutMouseFunc](#glutmousefunc)
	- [glutMouseWheelFunc [fg]](#glutmousewheelfunc)
	- [glutEntryFunc](#glutentryfunc)
	- [glutJoystickFunc](#glutjoystickfunc)
	- [glutSpaceballMotionFunc](#glutspaceballmotionfunc)
	- [glutSpaceballRotateFunc](#glutspaceballrotatefunc)
	- [glutSpaceballButtonFunc](#glutspaceballbuttonfunc)
	- [glutButtonBoxFunc](#glutbuttonboxfunc)
	- [glutDialsFunc](#glutdialsfunc)
	- [glutTabletMotionFunc](#gluttabletmotionfunc)
	- [glutTabletButtonFunc](#gluttabletbuttonfunc)
	- [glutVisibilityFunc](#glutvisibilityfunc)
	- [glutWindowStatusFunc](#glutwindowstatusfunc)

12. [State Setting and Retrieval Functions](#state-setting-and-retrieval-functions)

	- [glutSetOption [fg]](#glutsetoption)
	- [glutGet](#glutget)
	- [glutDeviceGet](#glutdeviceget)
	- [glutGetModifiers](#glutgetmodifiers)
	- [glutLayerGet](#glutlayerget)
	- [glutExtensionSupported](#glutextensionsupported)
	- [glutGetProcAddress [fg]](#glutgetprocaddress)

13. [Font Rendering Functions](font-rendering-functions)

	- [glutBitmapCharacter](#glutbitmapcharacter)
	- [glutBitmapString [fg]](#glutbitmapstring)
	- [glutBitmapWidth](#glutbitmapwidth)
	- [glutBitmapLength](#glutbitmaplength)
	- [glutBitmapHeight [fg]](#glutbitmapheight)
	- [glutStrokeCharacter](#glutstrokecharacter)
	- [glutStrokeString [fg]](#glutstrokestring)
	- [glutStrokeWidth](#glutstrokewidth)
	- [glutStrokeWidthf](#glutstrokewidthf)
	- [glutStrokeLength](#glutstrokelength)
	- [glutStrokeLengthf](#glutstrokelengthf)
	- [glutStrokeHeight [fg]](#glutstrokeheight)

14. [Geometric Object Rendering Functions](#geometric-object-rendering-functions)

	- [glutWireSphere](#glutwiresphere)
	- [glutSolidSphere](#glutsolidsphere)
	- [glutWireTorus](#glutwiretorus)
	- [glutSolidTorus](#glutsolidtorus)
	- [glutWireCone](#glutwirecone)
	- [glutSolidCone](#glutsolidcone)
	- [glutWireCube](#glutwirecube)
	- [glutSolidCube](#glutsolidcube)
	- [glutWireTetrahedron](#glutwiretetrahedron)
	- [glutSolidTetrahedron](#glutsolidtetrahedron)
	- [glutWireOctahedron](#glutwireoctahedron)
	- [glutSolidOctahedron](#glutsolidoctahedron)
	- [glutWireDodecahedron](#glutwiredodecahedron)
	- [glutSolidDodecahedron](#glutsoliddodecahedron)
	- [glutWireIcosahedron](#glutwireicosahedron)
	- [glutSolidIcosahedron](#glutsolidicosahedron)
	- [glutWireRhombicDodecahedron [fg]](#glutwirerhombicdodecahedron)
	- [glutSolidRhombicDodecahedron [fg]](#glutsolidrhombicdodecahedron)
	- [glutWireTeapot](#glutwireteapot)
	- [glutSolidTeapot](#glutsolidteapot)
	- [glutWireTeacup [fg]](#glutwireteacup)
	- [glutSolidTeacup [fg]](#glutsolidteacup)
	- [glutWireTeaspoon [fg]](#glutwireteaspoon)
	- [glutSolidTeaspoon [fg]](#glutsolidteaspoon)
	- [glutSetVertexAttribCoord3 [fg]](#glutsetvertexattribcoord3)
	- [glutSetVertexAttribNormal [fg]](#glutsetvertexattribnormal)
	- [glutSetVertexAttribTexCoord2 [fg]](#glutsetvertexattribtexcoord2)

15. [Game Mode Functions](#game-mode-functions)

	- [glutGameModeString](#glutgamemodestring)
	- [glutEnterGameMode](#glutentergamemode)
	- [glutLeaveGameMode](#glutleavegamemode)
	- [glutGameModeGet](#glutgamemodeget)

16. [Video Resize Functions](#video-resize-functions)

	- [glutVideoResizeGet](#glutvideoresizeget)
	- [glutSetupVideoResizing](#glutsetupvideoresizing)
	- [glutStopVideoResizing](#glutstopvideoresizing)
	- [glutVideoResize](#glutvideoresize)
	- [glutVideoPan](#glutvideopan)

17. [Color Map Functions](#color-map-functions)

	- [glutSetColor](#glutsetcolor)
	- [glutGetColor](#glutgetcolor)
	- [glutCopyColormap](#glutcopycolormap)

18. [MultiTouch Functions](#multitouch-functions)

	- [glutMultiEntryFunc [fg]](#glutmultientryfunc)
	- [glutMultiButtonFunc [fg]](#glutmultibuttonfunc)
	- [glutMultiMotionFunc [fg]](#glutmultimotionfunc)
	- [glutMultiPassiveFunc [fg]](#glutmultipassivefunc)

19. [Mobile functions](#mobile-functions)

	- [glutInitContextFunc [fg]](#glutinitcontextfunc)
	- [glutAppStatusFunc [fg]](#glutappstatusfunc)

20. [Miscellaneous Functions](#miscellaneous-functions)

	- [glutSetKeyRepeat](#glutsetkeyrepeat)
	- [glutIgnoreKeyRepeat](#glutignorekeyrepeat)
	- [glutForceJoystickFunc](#glutforcejoystickfunc)
	- [glutReportErrors](#glutreporterrors)

21. [Usage Notes](#usage-notes)

	- [Implementation Notes](#implementation-notes)
	- [GLUT State](#glut-state)
	- ["freeglut.h" Header File](#freegluth-header-file)
	- [References](#references)
	- [Index](#index)

22. [Unsorted Functions](#unsorted-functions)

---

# Introduction

The Markdown document is meant to serve as a FreeGLUT programming reference guide.
This document focuses on the following goals:

- Act as a complete API function reference guide
- Instruct the user how the API is meant to be used
- Provide additional information and trivia

Keep in mind that any and all functions in the [Table of Contents](#table-of-contents)
that contain "[fg]" are extended functionality that is not part of GLUT.
This will, of course, be mentioned in the API reference for each function,
because who reads introductions!

# Background

The OpenGL programming world owes a tremendous debt to Mr. Mark J. Kilgard
for writing the OpenGL Utility Toolkit, or GLUT. The GLUT library of functions
allows an application programmer to create, control, and manipulate windows
independent of what operating system the program is running on. By hiding the
dependency on the operating system from the application programmer, he allowed
people to write truly portable OpenGL applications.

Mr. Kilgard copyrighted his library and gave it a rather unusual license.
Under his license, people are allowed freely to copy and distribute
the libraries and the source code, but they are not allowed to modify it.
For a long time this did not matter because the GLUT library worked so well
and because Mr. Kilgard was releasing updates on a regular basis. But with
the passage of time, people started wanting some slightly different behaviours
in their windowing system. When Mr. Kilgard stopped supporting the GLUT library
in 1999, having moved on to bigger and better things, this started to become a problem.

In December 1999, Mr. Pawel Olzsta started work on an open-source clone of the GLUT library.
This open-source clone, which does not use any of the GLUT source code, has evolved into
the present FreeGLUT library. This documentation specifies the application program interface
to the FreeGLUT library.

## Design Philosophy

TODO

## Conventions

In developing the FreeGLUT library, we have taken careful steps to ensure consistency
in function operation across the board, in such a manner as to maintain compatibility
with GLUT's behavior whenever possible. In this section some of the important conventions of
FreeGLUT, and their compatibility with GLUT, are made explicit.

### Window placement and size

There is considerable confusion about the "right thing to do" concerning window size and position.
GLUT itself is not consistent between Windows and UNIX/X11; since platform independence
is a virtue for FreeGLUT, we decided to break with GLUT's behaviour. Under UNIX/X11,
it is apparently not possible to get the window border sizes in order to subtract them off
the window's initial position until some time after the window has been created.
Therefore we decided on the following behavior, both under Windows and under UNIX/X11:

- When you create a window with position `(x,y)` and size `(w,h)`, the upper left hand corner of the
  outside of the window (the non-client area) is at `(x,y)` and the size of the drawable (client)
  area is `(w,h)`. The coordinates taken by `glutInitPosition` and `glutPositionWindow`, as well as the
  coordinates provided by FreeGLUT when it calls the `glutPositionFunc` callback, specify the
  top-left of the non-client area of the window. By default only positive-signed coordinates are
  supported. If `GLUT_ALLOW_NEGATIVE_WINDOW_POSITION` is enabled, then negative coordinates are
  supported. An exception for `glutPositionWindow` exists as it's always supported negative window coordinates.

- When you query the size and position of the window using glutGet, FreeGLUT will return
  the size of the drawable area, the `(w,h)`, that you specified when you created the window
  and the coordinates of the upper left hand corner of the drawable (client) area which is
  NOT the `(x,y)` position of the window you specified when you created it.

### User-data callbacks

GLUT was created as a tool to help teach OpenGL programming. To simplify development,
callbacks were used for handling display, input, and other events. But at the time it was developed,
the purpose, or for some other unknown reason, the callbacks lacked any user-provided data argument.
This has caused considerable difficulties for any significantly advanced usage of GLUT, and now FreeGLUT.
This has prevented any attempt to wrap FreeGLUT in a C++ wrapper, make per-window,
per-callback data structure, and potentially made it undesirable to modern C developers
who tend to be well versed in "don't use globals". To combat these complaints and issues,
many callbacks (with some deprecated callbacks excluded) support user-data callbacks
provided through additional functions provided in FreeGLUT.
All callbacks that support user-data callbacks are marked as such.

The general rule to follow is to take the FreeGLUT callback function and append "Ucall"
to the end of the function, add an additional `void*` argument to the end of the argument list
of both the FreeGLUT function and the callback function.
This will pass the user-data to the callback when it's invoked.

Examples include:

```c
void glutPositionFunc ( void (* func)( int x, int y ) );
void glutPositionFuncUcall ( void (* func)( int x, int y, void* user_data ), void* user_data );

void glutKeyboardUpFunc ( void (* func)( unsigned char key, int x, int y ) );
void glutKeyboardUpFuncUcall ( void (* func)( unsigned char key, int x, int y, void* user_data ), void* user_data );
```

## Terminology

TODO

## Differences from GLUT 3.7

Since the FreeGLUT library was developed in order to update GLUT, it is natural
that there will be some differences between the two.
Each function in the API notes any differences between the GLUT and the FreeGLUT function behaviours.
The important ones are summarized here.

### glutMainLoop Behaviour

One of the most common complaints about the GLUT library was that once an application
called `glutMainLoop`, it never got control back. There was no way for an application
to loop in GLUT for a while, possibly as a subloop while a specific window was open,
and then return to the calling function. A new function, `glutMainLoopEvent`, has been
added to allow this functionality. Another function, `glutLeaveMainLoop`, has also been
added to allow the application to tell FreeGLUT to clean up and close down.

### Action on Window Closure

Another difficulty with GLUT, especially with multiple-window programs, is that
if the user clicks on the "X" in the window header the application exits immediately.
The application programmer can now set an option, `GLUT_ACTION_ON_WINDOW_CLOSE`,
to specify whether `glutMainLoop` should continue execution, whether FreeGLUT should
return control to the main program, or whether FreeGLUT should simply exit (the default).

### Fullscreen windows

Functions to leave fullscreen window mode (`glutLeaveFullScreen`)
or to toggle between fullscreen and normal window mode (`glutFullScreenToggle`)
have been added.

### Changes to Callbacks

Several new callbacks have been added and several callbacks which were specific to Silicon Graphics
hardware have not been implemented. Most or all of the new callbacks are listed in the GLUT Version 4
"glut.h" header file but did not make it into the documentation. The new callbacks consist of
regular and special key release callbacks, a joystick callback, a menu state callback
(with one argument, distinct from the menu status callback which has three arguments),
a window status callback (also with one argument), and a window position callback.
Unsupported callbacks are the two Tablet callbacks. If the user has a need for an unsupported callback
he should contact the FreeGLUT development team.

### String Rendering

New functions have been added to render full character strings (including carriage returns),
rather than rendering one character at a time. More functions return the widths of character strings
and the font heights, in pixels for bitmapped fonts and in OpenGL units for the stroke fonts.

### Geometry Rendering

Two functions have been added to render a wireframe and a solid rhombic dodecahedron.

Furthermore, solid and wireframe versions of the original teacup and teaspoon that accompanied the famous Newell teapot.

As these geometry functions are often used for teaching purposes,
`glutSetOption(GLUT_GEOMETRY_VISUALIZE_NORMALS, true/false)` can now be used to
visualize the normal vectors for each vertex.

Lastly, to support drawing these objects with shaders,
three functions have been added with which users can
provide the locations of the vertex position, normal, and texture coordinates attributes:
`glutSetVertexAttribCoord3`, `glutSetVertexAttribNormal`, and `glutSetVertexAttribTexCoord2`.
Texture coordinates are only generated for the teaset.

### Extension Function Queries

`glutGetProcAddress` is a wrapper for the `glXGetProcAddressARB` and `wglGetProcAddress` functions.

# Initialization Functions

## glutInit

## glutInitWindowPosition

## glutInitWindowSize

## glutInitDisplayMode

## glutInitDisplayString

## glutInitErrorFunc

## glutInitWarningFunc



# Event Processing Functions

## glutMainLoop

## glutMainLoopEvent

## glutLeaveMainLoop



# Window Functions

## glutCreateWindow

## glutCreateSubwindow

## glutDestroyWindow

## glutSetWindow

## glutGetWindow

## glutSetWindowTitle

## glutSetIconTitle

## glutReshapeWindow

## glutPositionWindow

## glutShowWindow

## glutHideWindow

## glutIconifyWindow

## glutPushWindow

## glutPopWindow

## glutFullScreen

## glutLeaveFullScreen

## glutFullScreenToggle



# Display Functions

## glutPostRedisplay

## glutPostWindowRedisplay

## glutSwapBuffers



# Mouse Cursor Functions

## glutSetCursor

## glutWarpPointer



# Overlay Functions

## glutEstablishOverlay

## glutRemoveOverlay

## glutUseLayer

## glutPostOverlayRedisplay

## glutPostWindowOverlayRedisplay

## glutShowOverlay

## glutHideOverlay



# Menu Functions

## glutCreateMenu

## glutDestroyMenu

## glutGetMenu

## glutSetMenu

## glutAddMenuEntry

## glutAddSubMenu

## glutChangeToMenuEntry

## glutChangeToSubMenu

## glutSetMenuFont

## glutRemoveMenuItem

## glutAttachMenu

## glutDetachMenu

## glutMenuDestroyFunc



# Global Callback Registration Functions

## glutTimerFunc

## glutIdleFunc

## glutMenuStatusFunc

## glutMenuStateFunc



# Window-Specific Callback Registration Functions

## glutDisplayFunc

## glutOverlayDisplayFunc

## glutReshapeFunc

## glutPositionFunc

## glutCloseFunc

## glutKeyboardFunc

## glutSpecialFunc

## glutKeyboardUpFunc

## glutSpecialUpFunc

## glutMotionFunc

## glutPassiveMotionFunc

## glutMouseFunc

## glutMouseWheelFunc

## glutEntryFunc

## glutJoystickFunc

## glutSpaceballMotionFunc

## glutSpaceballRotateFunc

## glutSpaceballButtonFunc

## glutButtonBoxFunc

## glutDialsFunc

## glutTabletMotionFunc

## glutTabletButtonFunc

## glutVisibilityFunc

## glutWindowStatusFunc

# State Setting and Retrieval Functions

## glutSetOption

## glutGet

## glutDeviceGet

## glutGetModifiers

## glutLayerGet

## glutExtensionSupported

## glutGetProcAddress



# Font Rendering Functions

## glutBitmapCharacter

## glutBitmapString

## glutBitmapWidth

## glutBitmapLength

## glutBitmapHeight

## glutStrokeCharacter

## glutStrokeString

## glutStrokeWidth

## glutStrokeWidthf

## glutStrokeLength

## glutStrokeLengthf

## glutStrokeHeight


# Geometric Object Rendering Functions

## glutWireSphere

## glutSolidSphere

## glutWireTorus

## glutSolidTorus

## glutWireCone

## glutSolidCone

## glutWireCube

## glutSolidCube

## glutWireTetrahedron

## glutSolidTetrahedron

## glutWireOctahedron

## glutSolidOctahedron

## glutWireDodecahedron

## glutSolidDodecahedron

## glutWireIcosahedron

## glutSolidIcosahedron

## glutWireRhombicDodecahedron

## glutSolidRhombicDodecahedron

## glutWireTeapot

## glutSolidTeapot

## glutWireTeacup

## glutSolidTeacup

## glutWireTeaspoon

## glutSolidTeaspoon

## glutSetVertexAttribCoord3

## glutSetVertexAttribNormal

## glutSetVertexAttribTexCoord2



# Game Mode Functions

## glutGameModeString

## glutEnterGameMode

## glutLeaveGameMode

## glutGameModeGet



# Video Resize Functions

## glutVideoResizeGet

## glutSetupVideoResizing

## glutStopVideoResizing

## glutVideoResize

## glutVideoPan



# Color Map Functions

## glutSetColor

## glutGetColor

## glutCopyColormap



# MultiTouch Functions

## glutMultiEntryFunc

## glutMultiButtonFunc

## glutMultiMotionFunc

## glutMultiPassiveFunc



# Mobile functions

## glutInitContextFunc

## glutAppStatusFunc



# Miscellaneous Functions

## glutSetKeyRepeat

## glutIgnoreKeyRepeat

## glutForceJoystickFunc

## glutReportErrors



# Usage Notes

The following environment variables are recognized by FreeGLUT:

- `DISPLAY` - Specifies a display name
- `GLUT_FPS` - Specifies a time interval (in milliseconds) for reporting framerate messages to `stderr`.
               For example, if `GLUT_FPS` is set to 5000, every 5 seconds a message will be printed to
			   `stderr` showing the current frame rate. The frame rate is measured by counting the number
			   of times `glutSwapBuffers()` is called over the time interval.

Furthermore, on Windows, there is a resource file identifier `GLUT_ICON` that you can specify for your
executable file. It specifies the icon that goes in the upper left-hand corner of the FreeGLUT windows.
Your application's resource file should contain the line:
```c
GLUT_ICON ICON DISCARDABLE "icon.ico"
```
where `icon.ico` is the filename of your icon.

The "One" demo includes such an icon as an example.

## Implementation Notes

TODO

## GLUT State

TODO

## "freeglut.h" Header File

Application programmers who are porting their GLUT programs to FreeGLUT may continue to include `<GL/glut.h>`
in their programs. Programs which use the FreeGLUT-specific extensions to GLUT should include `<GL/freeglut.h>`.
One possible arrangement is as follows:

```c
#ifdef FREEGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
```

It was initially planned to define `FREEGLUT_VERSION_2_0`, `FREEGLUT_VERSION_2_1`, `FREEGLUT_VERSION_2_2`, etc.,
but this was only done for `FREEGLUT_VERSION_2_0`.
**This constant still exist in current FreeGLUT releases but is deprecated.**

The FreeGLUT version can be queried at runtime by calling `glutGet(GLUT_VERSION)`.
The result will be `X*10000 + Y*100 + Z` where `X` is the major version, `Y` is the minor version and `Z` is the patch level.

This may be used as follows:

```c
if (glutGet(GLUT_VERSION) < 20001) {
    printf("Sorry, you need FreeGLUT version 2.0.1 or later to run this program.\n");
    exit(1);
}
```

## References

TODO

## Index

TODO

# Unsorted Functions

Currently, functions which aren't placed in any category are the following:

- `glutExit`

- `glutWMCloseFunc`

- `glutGetModeValues`
- `glutGetWindowData`
- `glutSetWindowData`

- `glutGetMenuData`
- `glutSetMenuData`

- `glutWireSierpinskiSponge`
- `glutSolidSierpinskiSponge`

- `glutWireCylinder`
- `glutSolidCylinder`

- `glutJoystickGetNumAxes`
- `glutJoystickGetNumButtons`
- `glutJoystickNotWorking`
- `glutJoystickGetDeadBand`
- `glutJoystickSetDeadBand`
- `glutJoystickGetSaturation`
- `glutJoystickSetSaturation`
- `glutJoystickSetMinRange`
- `glutJoystickSetMaxRange`
- `glutJoystickSetCenter`
- `glutJoystickGetMinRange`
- `glutJoystickGetMaxRange`
- `glutJoystickGetCenter`

- `glutInitContextVersion`
- `glutInitContextFlags`
- `glutInitContextProfile`

- `glutCreateMenuUcall`
- `glutTimerFuncUcall`
- `glutIdleFuncUcall`
- `glutKeyboardFuncUcall`
- `glutSpecialFuncUcall`
- `glutReshapeFuncUcall`
- `glutVisibilityFuncUcall`
- `glutDisplayFuncUcall`
- `glutMouseFuncUcall`
- `glutMotionFuncUcall`
- `glutPassiveMotionFuncUcall`
- `glutEntryFuncUcall`
- `glutKeyboardUpFuncUcall`
- `glutSpecialUpFuncUcall`
- `glutJoystickFuncUcall`
- `glutMenuStatusFuncUcall`
- `glutOverlayDisplayFuncUcall`
- `glutWindowStatusFuncUcall`
- `glutSpaceballMotionFuncUcall`
- `glutSpaceballRotateFuncUcall`
- `glutSpaceballButtonFuncUcall`
- `glutButtonBoxFuncUcall`
- `glutDialsFuncUcall`
- `glutTabletMotionFuncUcall`
- `glutTabletButtonFuncUcall`
- `glutMouseWheelFuncUcall`
- `glutPositionFuncUcall`
- `glutCloseFuncUcall`
- `glutWMCloseFuncUcall`
- `glutMenuDestroyFuncUcall`
- `glutMultiEntryFuncUcall`
- `glutMultiButtonFuncUcall`
- `glutMultiMotionFuncUcall`
- `glutMultiPassiveFuncUcall`
- `glutInitErrorFuncUcall`
- `glutInitWarningFuncUcall`
- `glutInitContextFuncUcall`
- `glutAppStatusFuncUcall`