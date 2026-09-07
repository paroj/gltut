/* fg_cmap_x11.c
 *
 * X11 implementation of the colormap functions
 *
 * Copyright (C) 2022 John Tsiombikas <nuclear@member.fsf.org>
 * Creation date: Tue August 30 2022
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
	Display *dpy = fgDisplay.pDisplay.Display;
	Colormap cmap = fgStructure.CurrentWindow->Window.cmap;
	int cmap_size = fgStructure.CurrentWindow->Window.cmap_size;
	XColor color;

	if(idx >= 0 && idx < cmap_size) {
		color.pixel = idx;
		color.red = (unsigned short)(r * 65535.0f);
		color.green = (unsigned short)(g * 65535.0f);
		color.blue = (unsigned short)(b * 65535.0f);
		color.flags = DoRed | DoGreen | DoBlue;
		XStoreColor(dpy, cmap, &color);
	}
}

float fgPlatformGetColor(int idx, int comp)
{
	Display *dpy = fgDisplay.pDisplay.Display;
	Colormap cmap = fgStructure.CurrentWindow->Window.cmap;
	int cmap_size = fgStructure.CurrentWindow->Window.cmap_size;
	XColor color;

	if(idx < 0 || idx >= cmap_size) {
		return -1.0f;
	}

	color.pixel = idx;
	XQueryColor(dpy, cmap, &color);
	switch(comp) {
	case GLUT_RED:
		return color.red / 65535.0f;
	case GLUT_GREEN:
		return color.green / 65535.0f;
	case GLUT_BLUE:
		return color.blue / 65535.0f;
	default:
		break;
	}
	return -1.0f;
}

void fgPlatformCopyColormap(int win)
{
	/* TODO */
	fgWarning("glutCopyColormap not implemented yet on X11");
}
