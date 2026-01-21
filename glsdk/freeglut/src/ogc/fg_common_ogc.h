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

#ifndef FREEGLUT_COMMON_OGC_H
#define FREEGLUT_COMMON_OGC_H

#include <GL/freeglut.h>
#include "../fg_internal.h"

#define MAX_GC_JOYSTICKS 4

#ifdef __wii__
#define MAX_WII_JOYSTICKS 4
#else
#define MAX_WII_JOYSTICKS 0
#endif

#define MAX_OGC_JOYSTICKS (MAX_GC_JOYSTICKS + MAX_WII_JOYSTICKS)

extern void fghOnReshapeNotify(SFG_Window *window, int width, int height,
                               GLboolean forceNotify);

void fgOgcCursorDraw();

void fgOgcDisplaySetupVideoMode();
void fgOgcDisplaySetupXfb();
void fgOgcDisplayShowEFB();

#endif /* FREEGLUT_COMMON_OGC_H */
