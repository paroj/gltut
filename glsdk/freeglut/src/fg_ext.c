/*
 * fg_ext.c
 *
 * Functions related to OpenGL extensions.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Thu Dec 9 1999
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

#define GLX_GLXEXT_PROTOTYPES
#include <GL/freeglut.h>
#include "fg_internal.h"

extern SFG_Proc fgPlatformGetProcAddress( const char *procName );
extern GLUTproc fgPlatformGetGLUTProcAddress( const char *procName );

static GLUTproc fghGetGLUTProcAddress( const char* procName )
{
    /* optimization: quick initial check */
    if( strncmp( procName, "glut", 4 ) != 0 )
        return NULL;

#define CHECK_NAME(x) if( strcmp( procName, #x ) == 0) return (GLUTproc)x;
    CHECK_NAME(glutInit);
    CHECK_NAME(glutInitDisplayMode);
    CHECK_NAME(glutInitDisplayString);
    CHECK_NAME(glutInitWindowPosition);
    CHECK_NAME(glutInitWindowSize);
    CHECK_NAME(glutMainLoop);
    CHECK_NAME(glutExit);
    CHECK_NAME(glutCreateWindow);
    CHECK_NAME(glutCreateSubWindow);
    CHECK_NAME(glutDestroyWindow);
    CHECK_NAME(glutPostRedisplay);
    CHECK_NAME(glutPostWindowRedisplay);
    CHECK_NAME(glutSwapBuffers);
    CHECK_NAME(glutGetWindow);
    CHECK_NAME(glutSetWindow);
    CHECK_NAME(glutSetWindowTitle);
    CHECK_NAME(glutSetIconTitle);
    CHECK_NAME(glutPositionWindow);
    CHECK_NAME(glutReshapeWindow);
    CHECK_NAME(glutPopWindow);
    CHECK_NAME(glutPushWindow);
    CHECK_NAME(glutIconifyWindow);
    CHECK_NAME(glutShowWindow);
    CHECK_NAME(glutHideWindow);
    CHECK_NAME(glutFullScreen);
    CHECK_NAME(glutSetCursor);
    CHECK_NAME(glutWarpPointer);
    CHECK_NAME(glutEstablishOverlay);
    CHECK_NAME(glutRemoveOverlay);
    CHECK_NAME(glutUseLayer);
    CHECK_NAME(glutPostOverlayRedisplay);
    CHECK_NAME(glutPostWindowOverlayRedisplay);
    CHECK_NAME(glutShowOverlay);
    CHECK_NAME(glutHideOverlay);
    CHECK_NAME(glutCreateMenu);
    CHECK_NAME(glutDestroyMenu);
    CHECK_NAME(glutGetMenu);
    CHECK_NAME(glutSetMenu);
    CHECK_NAME(glutAddMenuEntry);
    CHECK_NAME(glutAddSubMenu);
    CHECK_NAME(glutChangeToMenuEntry);
    CHECK_NAME(glutChangeToSubMenu);
    CHECK_NAME(glutRemoveMenuItem);
    CHECK_NAME(glutAttachMenu);
    CHECK_NAME(glutDetachMenu);
    CHECK_NAME(glutDisplayFunc);
    CHECK_NAME(glutReshapeFunc);
    CHECK_NAME(glutPositionFunc);
    CHECK_NAME(glutKeyboardFunc);
    CHECK_NAME(glutMouseFunc);
    CHECK_NAME(glutMultiEntryFunc);
    CHECK_NAME(glutMultiMotionFunc);
    CHECK_NAME(glutMultiButtonFunc);
    CHECK_NAME(glutMultiPassiveFunc);
    CHECK_NAME(glutMotionFunc);
    CHECK_NAME(glutPassiveMotionFunc);
    CHECK_NAME(glutEntryFunc);
    CHECK_NAME(glutVisibilityFunc);
    CHECK_NAME(glutIdleFunc);
    CHECK_NAME(glutTimerFunc);
    CHECK_NAME(glutMenuStateFunc);
    CHECK_NAME(glutSpecialFunc);
    CHECK_NAME(glutSpaceballMotionFunc);
    CHECK_NAME(glutSpaceballRotateFunc);
    CHECK_NAME(glutSpaceballButtonFunc);
    CHECK_NAME(glutButtonBoxFunc);
    CHECK_NAME(glutDialsFunc);
    CHECK_NAME(glutTabletMotionFunc);
    CHECK_NAME(glutTabletButtonFunc);
    CHECK_NAME(glutMenuStatusFunc);
    CHECK_NAME(glutOverlayDisplayFunc);
    CHECK_NAME(glutWindowStatusFunc);
    CHECK_NAME(glutKeyboardUpFunc);
    CHECK_NAME(glutSpecialUpFunc);
    CHECK_NAME(glutSetColor);
    CHECK_NAME(glutGetColor);
    CHECK_NAME(glutCopyColormap);
    CHECK_NAME(glutGet);
    CHECK_NAME(glutDeviceGet);
    CHECK_NAME(glutExtensionSupported);
    CHECK_NAME(glutGetModifiers);
    CHECK_NAME(glutLayerGet);
    CHECK_NAME(glutBitmapCharacter);
    CHECK_NAME(glutBitmapWidth);
    CHECK_NAME(glutStrokeCharacter);
    CHECK_NAME(glutStrokeWidth);
    CHECK_NAME(glutStrokeWidthf);
    CHECK_NAME(glutBitmapLength);
    CHECK_NAME(glutStrokeLength);
    CHECK_NAME(glutStrokeLengthf);
    CHECK_NAME(glutWireSphere);
    CHECK_NAME(glutSolidSphere);
    CHECK_NAME(glutWireCone);
    CHECK_NAME(glutSolidCone);
    CHECK_NAME(glutWireTorus);
    CHECK_NAME(glutSolidTorus);
    CHECK_NAME(glutWireCylinder);
    CHECK_NAME(glutSolidCylinder);
    CHECK_NAME(glutWireTeapot);
    CHECK_NAME(glutSolidTeapot);
    CHECK_NAME(glutWireTeacup);
    CHECK_NAME(glutSolidTeacup);
    CHECK_NAME(glutWireTeaspoon);
    CHECK_NAME(glutSolidTeaspoon);
    CHECK_NAME(glutWireCube);
    CHECK_NAME(glutSolidCube);
    CHECK_NAME(glutWireDodecahedron);
    CHECK_NAME(glutSolidDodecahedron);
    CHECK_NAME(glutWireOctahedron);
    CHECK_NAME(glutSolidOctahedron);
    CHECK_NAME(glutWireTetrahedron);
    CHECK_NAME(glutSolidTetrahedron);
    CHECK_NAME(glutWireIcosahedron);
    CHECK_NAME(glutSolidIcosahedron);
    CHECK_NAME(glutWireRhombicDodecahedron);
    CHECK_NAME(glutSolidRhombicDodecahedron);
    CHECK_NAME(glutWireSierpinskiSponge);
    CHECK_NAME(glutSolidSierpinskiSponge);
    CHECK_NAME(glutVideoResizeGet);
    CHECK_NAME(glutSetupVideoResizing);
    CHECK_NAME(glutStopVideoResizing);
    CHECK_NAME(glutVideoResize);
    CHECK_NAME(glutVideoPan);
    CHECK_NAME(glutReportErrors);
    CHECK_NAME(glutIgnoreKeyRepeat);
    CHECK_NAME(glutSetKeyRepeat);

    /* freeglut extensions */
    CHECK_NAME(glutMainLoopEvent);
    CHECK_NAME(glutLeaveMainLoop);
    CHECK_NAME(glutCloseFunc);
    CHECK_NAME(glutWMCloseFunc);
    CHECK_NAME(glutMenuDestroyFunc);
    CHECK_NAME(glutFullScreenToggle);
    CHECK_NAME(glutLeaveFullScreen);
    CHECK_NAME(glutSetMenuFont);
    CHECK_NAME(glutSetOption);
    CHECK_NAME(glutGetModeValues);
    CHECK_NAME(glutSetWindowData);
    CHECK_NAME(glutGetWindowData);
    CHECK_NAME(glutSetMenuData);
    CHECK_NAME(glutGetMenuData);
    CHECK_NAME(glutBitmapHeight);
    CHECK_NAME(glutStrokeHeight);
    CHECK_NAME(glutBitmapString);
    CHECK_NAME(glutStrokeString);
    CHECK_NAME(glutGetProcAddress);
    CHECK_NAME(glutMouseWheelFunc);
    CHECK_NAME(glutJoystickGetNumAxes);
    CHECK_NAME(glutJoystickGetNumButtons);
    CHECK_NAME(glutJoystickNotWorking);
    CHECK_NAME(glutJoystickGetDeadBand);
    CHECK_NAME(glutJoystickSetDeadBand);
    CHECK_NAME(glutJoystickGetSaturation);
    CHECK_NAME(glutJoystickSetSaturation);
    CHECK_NAME(glutJoystickSetMinRange);
    CHECK_NAME(glutJoystickSetMaxRange);
    CHECK_NAME(glutJoystickSetCenter);
    CHECK_NAME(glutJoystickGetMinRange);
    CHECK_NAME(glutJoystickGetMaxRange);
    CHECK_NAME(glutJoystickGetCenter);
    CHECK_NAME(glutInitContextVersion);
    CHECK_NAME(glutInitContextFlags);
    CHECK_NAME(glutInitContextProfile);
    CHECK_NAME(glutInitErrorFunc);
    CHECK_NAME(glutInitWarningFunc);
    CHECK_NAME(glutInitContextFunc);
    CHECK_NAME(glutAppStatusFunc);
    CHECK_NAME(glutSetVertexAttribCoord3);
    CHECK_NAME(glutSetVertexAttribNormal);
    CHECK_NAME(glutSetVertexAttribTexCoord2);

    /* freeglut user callback functions */
    CHECK_NAME(glutCreateMenuUcall);
    CHECK_NAME(glutTimerFuncUcall);
    CHECK_NAME(glutIdleFuncUcall);
    CHECK_NAME(glutKeyboardFuncUcall);
    CHECK_NAME(glutSpecialFuncUcall);
    CHECK_NAME(glutReshapeFuncUcall);
    CHECK_NAME(glutVisibilityFuncUcall);
    CHECK_NAME(glutDisplayFuncUcall);
    CHECK_NAME(glutMouseFuncUcall);
    CHECK_NAME(glutMotionFuncUcall);
    CHECK_NAME(glutPassiveMotionFuncUcall);
    CHECK_NAME(glutEntryFuncUcall);
    CHECK_NAME(glutKeyboardUpFuncUcall);
    CHECK_NAME(glutSpecialUpFuncUcall);
    CHECK_NAME(glutJoystickFuncUcall);
    CHECK_NAME(glutMenuStatusFuncUcall);
    CHECK_NAME(glutOverlayDisplayFuncUcall);
    CHECK_NAME(glutWindowStatusFuncUcall);
    CHECK_NAME(glutSpaceballMotionFuncUcall);
    CHECK_NAME(glutSpaceballRotateFuncUcall);
    CHECK_NAME(glutSpaceballButtonFuncUcall);
    CHECK_NAME(glutButtonBoxFuncUcall);
    CHECK_NAME(glutDialsFuncUcall);
    CHECK_NAME(glutTabletMotionFuncUcall);
    CHECK_NAME(glutTabletButtonFuncUcall);
    CHECK_NAME(glutMouseWheelFuncUcall);
    CHECK_NAME(glutPositionFuncUcall);
    CHECK_NAME(glutCloseFuncUcall);
    CHECK_NAME(glutWMCloseFuncUcall);
    CHECK_NAME(glutMenuDestroyFuncUcall);
    CHECK_NAME(glutMultiEntryFuncUcall);
    CHECK_NAME(glutMultiButtonFuncUcall);
    CHECK_NAME(glutMultiMotionFuncUcall);
    CHECK_NAME(glutMultiPassiveFuncUcall);
    CHECK_NAME(glutInitErrorFuncUcall);
    CHECK_NAME(glutInitWarningFuncUcall);
    CHECK_NAME(glutInitContextFuncUcall);
    CHECK_NAME(glutAppStatusFuncUcall);
#undef CHECK_NAME

    return NULL;
}



GLUTproc FGAPIENTRY
glutGetProcAddress( const char *procName )
{
    GLUTproc p;
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutGetProcAddress" );

    /* Try GLUT functions first, then core GL functions */
    p = fghGetGLUTProcAddress( procName );

    /* Some GLUT functions are platform-specific: */
    if ( !p )
      p = fgPlatformGetGLUTProcAddress( procName );

    return ( p != NULL ) ? p : fgPlatformGetProcAddress( procName );
}
