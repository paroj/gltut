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

#include <fat.h>
#include <malloc.h>
#include <opengx.h>

#define FIFO_SIZE (256*1024)

void fgPlatformInitialize(const char *displayName)
{
    VIDEO_Init();

    void *fifoBuffer = MEM_K0_TO_K1(memalign(32, FIFO_SIZE));
    memset(fifoBuffer, 0, FIFO_SIZE);

    GX_Init(fifoBuffer, FIFO_SIZE);
    fgDisplay.pDisplay.vmode = VIDEO_GetPreferredMode(NULL);
    fgOgcDisplaySetupVideoMode();

    ogx_initialize();

    fatInitDefault();

    fgState.Time = fgSystemTime();
    fgState.FPSInterval = 2000;
    fgState.Initialised = GL_TRUE;
}

void fgPlatformDeinitialiseInputDevices(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformCloseDisplay(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformDestroyContext(SFG_PlatformDisplay pDisplay,
                              SFG_WindowContextType MContext)
{
    fgWarning("%s() : not implemented", __func__);
}
