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

#include <ogc/color.h>
#include <opengx.h>

void fgOgcDisplaySetupXfb()
{
    GXRModeObj *vmode = fgDisplay.pDisplay.vmode;

    if (fgDisplay.pDisplay.vmode_changed) {
        /* The size of the XFB might be different, so reallocate it */
        if (fgDisplay.pDisplay.xfb[0]) {
            free(MEM_K1_TO_K0(fgDisplay.pDisplay.xfb[0]));
            fgDisplay.pDisplay.xfb[0] = NULL;
        }
        if (fgDisplay.pDisplay.xfb[1]) {
            free(MEM_K1_TO_K0(fgDisplay.pDisplay.xfb[1]));
            fgDisplay.pDisplay.xfb[1] = NULL;
        }
    }

    if (!fgDisplay.pDisplay.xfb[0]) {
        fgDisplay.pDisplay.xfb[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(vmode));
    }
    if (fgState.DisplayMode & GLUT_DOUBLE && !fgDisplay.pDisplay.xfb[1]) {
        fgDisplay.pDisplay.xfb[1] =
            MEM_K0_TO_K1(SYS_AllocateFramebuffer(vmode));
    }

    if (fgState.DisplayMode & GLUT_STENCIL) {
        ogx_stencil_create(OGX_STENCIL_DIRTY_Z);
    }
}

void fgOgcDisplaySetupVideoMode()
{
    GXRModeObj *vmode = fgDisplay.pDisplay.vmode;

    fgOgcDisplaySetupXfb();

    VIDEO_Configure(vmode);
    VIDEO_ClearFrameBuffer(vmode, fgDisplay.pDisplay.xfb[0], COLOR_BLACK);
    VIDEO_SetNextFramebuffer(fgDisplay.pDisplay.xfb[0]);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();

    VIDEO_WaitVSync();
    if (vmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    f32 yscale = GX_GetYScaleFactor(vmode->efbHeight, vmode->xfbHeight);
    GX_SetDispCopyYScale(yscale);
    GX_SetDispCopySrc(0, 0, vmode->fbWidth, vmode->efbHeight);
    GX_SetDispCopyDst(vmode->fbWidth, vmode->xfbHeight);
    GX_SetCopyFilter(vmode->aa, vmode->sample_pattern, GX_TRUE, vmode->vfilter);

    fgDisplay.ScreenWidth = vmode->fbWidth;
    fgDisplay.ScreenHeight = vmode->efbHeight;
    fgDisplay.pDisplay.vmode_changed = 0;
}

void fgOgcDisplayShowEFB()
{
    void *xfb;
    u8 mustClear, mustWait;

    if (ogx_prepare_swap_buffers() < 0) return;

    fgOgcCursorDraw();

    if (fgState.DisplayMode & GLUT_DOUBLE) {
        mustClear = GX_TRUE;
        mustWait = GX_TRUE;
        xfb = fgDisplay.pDisplay.xfb[fgDisplay.pDisplay.fbIndex];
        fgDisplay.pDisplay.fbIndex ^= 1;
    } else {
        mustClear = GX_FALSE;
        mustWait = GX_FALSE;
        xfb = fgDisplay.pDisplay.xfb[0];
    }
    GX_CopyDisp(xfb, mustClear);
    GX_DrawDone();
    GX_Flush();

    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_Flush();
    if (mustWait)
        VIDEO_WaitVSync();
}

void fgPlatformGlutSwapBuffers(SFG_PlatformDisplay *pDisplayPtr,
                               SFG_Window *CurrentWindow)
{
    fgOgcDisplayShowEFB();
}
