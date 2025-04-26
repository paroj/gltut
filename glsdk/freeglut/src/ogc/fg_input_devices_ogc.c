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

void fgPlatformInitialiseInputDevices(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformCloseInputDevices(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformInitializeSpaceball(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformSpaceballClose(void)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformSpaceballSetWindow(SFG_Window *window)
{
    fgWarning("%s() : not implemented", __func__);
}

int fgPlatformHasSpaceball(void)
{
    fgWarning("%s() : not implemented", __func__);
    return 0;
}

int fgPlatformSpaceballNumButtons(void)
{
    fgWarning("%s() : not implemented", __func__);
    return 0;
}

typedef struct _serialport SERIALPORT;

void fgPlatformRegisterDialDevice ( const char *dial_device ) {
    fgWarning("GLUT_HAS_DIAL_AND_BUTTON_BOX: not implemented");
}
SERIALPORT *fg_serial_open (const char *device) { return NULL; }
void fg_serial_close(SERIALPORT *port) {}
int fg_serial_getchar(SERIALPORT *port) { return EOF; }
int fg_serial_putchar(SERIALPORT *port, unsigned char ch) { return 0; }
void fg_serial_flush(SERIALPORT *port) {}
