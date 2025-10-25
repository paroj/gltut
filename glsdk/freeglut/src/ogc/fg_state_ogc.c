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

int fgPlatformGlutDeviceGet(GLenum eWhat)
{
    fgWarning("%s() : not implemented", __func__);
    return -1;
}

int fgPlatformGlutGet(GLenum eWhat)
{
    GLint ret = -1;

    switch (eWhat) {
    case GLUT_WINDOW_WIDTH:
        return fgStructure.CurrentWindow ?
            fgStructure.CurrentWindow->State.Width : 0;
    case GLUT_WINDOW_HEIGHT:
        return fgStructure.CurrentWindow ?
            fgStructure.CurrentWindow->State.Height : 0;
    case GLUT_WINDOW_STENCIL_SIZE:
        glGetIntegerv(GL_STENCIL_BITS, &ret);
        break;
    default:
        fgWarning("%s() : not implemented for %d", __func__, eWhat);
    }
    return ret;
}

int *fgPlatformGlutGetModeValues(GLenum eWhat, int *size)
{
    fgWarning("%s() : not implemented", __func__);
    return NULL;
}
