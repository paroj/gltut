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

void fgPlatformRememberState(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformRestoreState(void)
{
    fgWarning("%s() : not implemented", __func__);
}

GLvoid fgPlatformGetGameModeVMaxExtent(SFG_Window *window, int *x, int *y)
{
    fgWarning("%s() : not implemented", __func__);
}

GLboolean fgPlatformChangeDisplayMode(GLboolean haveToTest)
{
    fgWarning("%s() : not implemented", __func__);
    /* Until we implement this, let's return TRUE. Otherwise all fullscreen
     * applications won't run at all. */
    return GL_TRUE;
}


void fgPlatformEnterGameMode(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformLeaveGameMode(void)
{
    fgWarning("%s() : not implemented", __func__);
}
