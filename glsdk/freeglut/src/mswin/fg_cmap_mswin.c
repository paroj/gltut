/* fg_cmap_mswin.c
 *
 * Win32 implementation of the colormap functions
 *
 * Copyright (C) 2022 John Tsiombikas <nuclear@member.fsf.org>
 * Creation date: Sat September 3 2022
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
#include <GL/freeglut.h>
#include "../fg_internal.h"

void fgPlatformSetColor(int idx, float r, float g, float b)
{
	HPALETTE pal;
	PALETTEENTRY col;
	HDC dc;

	if(idx < 0 || idx >= 256) {
		return;
	}

	col.peRed = (int)(r * 255.0f);
	col.peGreen = (int)(g * 255.0f);
	col.peBlue = (int)(b * 255.0f);
	col.peFlags = PC_NOCOLLAPSE;

	pal = fgStructure.CurrentWindow->Window.cmap;
	SetPaletteEntries(pal, idx, 1, &col);

	if(!(dc = fgStructure.CurrentWindow->Window.pContext.Device)) {
		return;
	}

	UnrealizeObject(pal);
	SelectPalette(dc, pal, 0);
	RealizePalette(dc);
}

float fgPlatformGetColor(int idx, int comp)
{
	PALETTEENTRY col;
	HPALETTE pal;

	if(idx < 0 || idx >= 256) {
		return -1.0f;
	}

	pal = fgStructure.CurrentWindow->Window.cmap;
	if(!GetPaletteEntries(pal, idx, 1, &col)) {
		return -1.0f;
	}

	switch(comp) {
	case GLUT_RED:
		return col.peRed / 255.0f;
	case GLUT_GREEN:
		return col.peGreen / 255.0f;
	case GLUT_BLUE:
		return col.peBlue / 255.0f;
	default:
		break;
	}
	return -1.0f;
}

void fgPlatformCopyColormap(int win)
{
	/* TODO */
	fgWarning("glutCopyColormap not implemented yet on Win32");
}
