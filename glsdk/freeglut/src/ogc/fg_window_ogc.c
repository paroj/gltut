/*
 * Copyright (c) 2024 Alberto Mardegan <mardy@users.sourceforge.net>
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

#include "fg_common_ogc.h"

void fgPlatformSetWindow(SFG_Window *window)
{
}

void fgPlatformOpenWindow(SFG_Window *window, const char *title,
                          GLboolean positionUse, int x, int y,
                          GLboolean sizeUse, int w, int h,
                          GLboolean gameMode, GLboolean isSubWindow)
{
    fgWarning("%s(): %d,%d - %dx%d", __func__, x, y, w, h);
    /* We always ignore the requested size, we only support fullscreen windows
     */
    window->State.IsFullscreen = GL_TRUE;
    window->State.Xpos = 0;
    window->State.Ypos = 0;

    window->State.WorkMask |= GLUT_INIT_WORK | GLUT_VISIBILITY_WORK;
    window->State.Visible = GL_TRUE;

    /* This sets up the XFB for the chosen buffering scheme */
    fgOgcDisplaySetupXfb();
}

void fgPlatformReshapeWindow(SFG_Window *window, int width, int height)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformCloseWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformShowWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformHideWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformIconifyWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformGlutSetWindowTitle(const char *title)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformGlutSetIconTitle(const char *title)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformPositionWindow(SFG_Window *window, int x, int y)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformPushWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformPopWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformFullScreenToggle(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}
