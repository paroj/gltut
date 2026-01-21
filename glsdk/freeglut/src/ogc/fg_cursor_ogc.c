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
#include "fg_cursor_ogc.h"

#include <malloc.h>
#include <ogc/cache.h>
#include <wiiuse/wpad.h>

typedef struct {
    const FgOgcCursor *image;
    void *texels;
    int hot_x, hot_y;
    int w, h;
} OGC_CursorData;

typedef struct {
    int glutCursorId;
    OGC_CursorData cursor;
} CursorMapping;

static CursorMapping cursor_mapping[] = {
    { GLUT_CURSOR_NONE, { NULL, }},
    { GLUT_CURSOR_RIGHT_ARROW, { &OGC_cursor_arrow, }},
    { GLUT_CURSOR_INHERIT, { &OGC_cursor_hand, }},
};
#define MAPPING_SIZE (sizeof(cursor_mapping) / sizeof(cursor_mapping[0]))

static void drawCursorRect(OGC_CursorData *curdata)
{
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    GX_Position2s16(-curdata->hot_x, -curdata->hot_y);
    GX_TexCoord2u8(0, 0);
    GX_Position2s16(curdata->w - curdata->hot_x, -curdata->hot_y);
    GX_TexCoord2u8(1, 0);
    GX_Position2s16(curdata->w - curdata->hot_x, curdata->h - curdata->hot_y);
    GX_TexCoord2u8(1, 1);
    GX_Position2s16(-curdata->hot_x, curdata->h - curdata->hot_y);
    GX_TexCoord2u8(0, 1);
    GX_End();
}

/* Convert the RGBA pixels to the 4x4 tile ARGB texture used by GX */
static void setPixelToTextureARGB(char *texture, u32 offset, u32 color)
{
    *(u16*)(texture + offset) = color >> 16;
    *(u16*)(texture + offset + 32) = color;
}

static void setPixelToTextureRGBA(char *texture, u32 offset, u32 color)
{
    setPixelToTextureARGB(texture, offset, (color << 24) | (color >> 8));
}

static void pixelsToTextureARGB(const void *pixels, s16 width, s16 height,
                                s16 pitch, void *texture)
{
    s16 tex_pitch = (width + 3) / 4 * 4;
    int row, col;

    for (row = 0; row < height; row++) {
        int y = row;
        u32 *src = (u32 *)((u8 *)pixels + pitch * row);
        for (col = 0; col < width; col++) {
            int x = col;
            u32 offset = (((y >> 2) << 4) * tex_pitch) +
                ((x >> 2) << 6) + (((y % 4 << 2) + x % 4) << 1);
            setPixelToTextureRGBA(texture, offset, *src++);
        }
    }
}

GLboolean setupCursor(OGC_CursorData *curdata)
{
    u32 textureSize;

    curdata->hot_x = curdata->image->hot_x;
    curdata->hot_y = curdata->image->hot_y;
    curdata->w = curdata->image->width;
    curdata->h = curdata->image->height;

    textureSize = GX_GetTexBufferSize(curdata->w, curdata->h, GX_TF_RGBA8,
                                      GX_FALSE, 0);
    curdata->texels = memalign(32, textureSize);
    if (!curdata->texels) {
        return GL_FALSE;
    }

    pixelsToTextureARGB(curdata->image->pixel_data, curdata->w, curdata->h,
                        curdata->w * 4, curdata->texels);
    DCStoreRange(curdata->texels, textureSize);
    GX_InvalidateTexAll();

    return GL_TRUE;
}

void fgOgcCursorDraw()
{
    OGC_CursorData *curdata = NULL;
    SFG_Window *window = fgStructure.CurrentWindow;
    int cursorId, i;
    GXTexObj texobj;
    Mtx44 proj;
    Mtx mv;

    if (!fgStructure.CurrentWindow) return;

    /* Don't show a cursor if none of the mouse callback functions have been
     * registered */
    if (!FETCH_WCB(*window, Motion) && !FETCH_WCB(*window, Mouse)) return;

    cursorId = fgStructure.CurrentWindow->State.Cursor;
    for (i = 0; i < MAPPING_SIZE; i++) {
        CursorMapping *mapping = &cursor_mapping[i];
        if (mapping->glutCursorId == cursorId) {
            curdata = &mapping->cursor;
            break;
        }
    }

    if (!curdata) return;

    if (!curdata->texels) {
        setupCursor(curdata);
    }

    GX_InitTexObj(&texobj, curdata->texels,
                  curdata->w, curdata->h,
                  GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GX_InitTexObjLOD(&texobj, GX_LINEAR, GX_LINEAR,
                     0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GX_LoadTexObj(&texobj, GX_TEXMAP0);

    guOrtho(proj, 0, fgDisplay.ScreenHeight, 0, fgDisplay.ScreenWidth, 0, 1);
    GX_LoadProjectionMtx(proj, GX_ORTHOGRAPHIC);

    guMtxIdentity(mv);
    guMtxScaleApply(mv, mv,
                    fgDisplay.ScreenWidth / 640.0f,
                    fgDisplay.ScreenHeight / 480.0f, 1.0f);
    /* If this is the Wii default cursor, rotate it too */
    if (cursorId == GLUT_CURSOR_INHERIT) {
        Mtx rot;
        float angle;
        WPADData *data = WPAD_Data(0);

        angle = data->ir.angle;
        guMtxRotDeg(rot, 'z', angle);
        guMtxConcat(mv, rot, mv);
    }
    guMtxTransApply(mv, mv,
                    window->State.MouseX,
                    window->State.MouseY, 0);
    GX_LoadPosMtxImm(mv, GX_PNMTX1);

    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

    GX_SetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GX_SetNumTevStages(1);
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    GX_SetNumTexGens(1);
    GX_SetCurrentMtx(GX_PNMTX1);
    GX_SetZMode(GX_DISABLE, GX_ALWAYS, GX_FALSE);
    drawCursorRect(curdata);
    GX_SetCurrentMtx(GX_PNMTX0);
    GX_DrawDone();
}

void fgPlatformSetCursor(SFG_Window *window, int cursorID)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformWarpPointer(int x, int y)
{
    fgWarning("%s() : not implemented", __func__);
}

void fghPlatformGetCursorPos(const SFG_Window *window, GLboolean client, SFG_XYUse *mouse_pos)
{
    fgWarning("%s() : not implemented", __func__);
}
