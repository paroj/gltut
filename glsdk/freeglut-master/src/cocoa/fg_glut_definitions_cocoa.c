/*
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

/*
 * The following are font symbols that fg_font.c expects to be present.  I'm guess this
 * allows different platforms to provide different fonts.  Using the included font symbols
 * glutStrokeRoman, glutBitmap9By15, etc. will use the default fonts.
 */

extern SFG_Font       fgFontFixed8x13;
extern SFG_Font       fgFontFixed9x15;
extern SFG_Font       fgFontHelvetica10;
extern SFG_Font       fgFontHelvetica12;
extern SFG_Font       fgFontHelvetica18;
extern SFG_Font       fgFontTimesRoman10;
extern SFG_Font       fgFontTimesRoman24;
extern SFG_StrokeFont fgStrokeRoman;
extern SFG_StrokeFont fgStrokeMonoRoman;

void *glutStrokeRoman     = &fgFontFixed8x13;
void *glutStrokeMonoRoman = &glutStrokeMonoRoman;

void *glutBitmap9By15        = &glutBitmap9By15;
void *glutBitmap8By13        = &glutBitmap8By13;
void *glutBitmapTimesRoman10 = &glutBitmapTimesRoman10;
void *glutBitmapTimesRoman24 = &glutBitmapTimesRoman24;
void *glutBitmapHelvetica10  = &glutBitmapHelvetica10;
void *glutBitmapHelvetica12  = &glutBitmapHelvetica12;
void *glutBitmapHelvetica18  = &glutBitmapHelvetica18;

/*
 * Other functions that fg_input.c expects to be present.  Not sure why they are not prefixed with
 * fgPlatform.
 */

typedef struct _serialport SERIALPORT;
SERIALPORT                *fg_serial_open( const char *device )
{
    TODO_IMPL;
    return NULL;
}
void fg_serial_close( SERIALPORT *port )
{
    TODO_IMPL;
}
int fg_serial_getchar( SERIALPORT *port )
{
    TODO_IMPL;
    return EOF;
}
int fg_serial_putchar( SERIALPORT *port, unsigned char ch )
{
    TODO_IMPL;
    return 0;
}
void fg_serial_flush( SERIALPORT *port )
{
    TODO_IMPL;
}
