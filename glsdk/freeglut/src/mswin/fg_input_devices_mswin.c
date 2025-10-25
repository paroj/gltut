/*
 * fg_input_devices_mswin.c
 *
 * The Windows-specific mouse cursor related stuff.
 *
 * Copyright (c) 2012 Stephen J. Baker. All Rights Reserved.
 * Written by John F. Fay, <fayjf@sourceforge.net>
 * Creation date: Sat Jan 21, 2012
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

#include <sys/types.h>
#include <winbase.h>

struct _serialport {
   HANDLE fh;
   COMMTIMEOUTS timeouts_save;
   DCB dcb_save;
};

typedef struct _serialport SERIALPORT;

/* Serial Port Prototypes */
SERIALPORT *fg_serial_open ( const char *device );
void fg_serial_close ( SERIALPORT *port );
int fg_serial_getchar ( SERIALPORT *port );
int fg_serial_putchar ( SERIALPORT *port, unsigned char ch );
void fg_serial_flush ( SERIALPORT *port );


void fgPlatformRegisterDialDevice ( const char *dial_device )
{
        if (!dial_device){
            static char devname[256];
            DWORD size=sizeof(devname);
            DWORD type = REG_SZ;
            HKEY key;
            if (RegOpenKeyA(HKEY_LOCAL_MACHINE,"SOFTWARE\\FreeGLUT",&key)==ERROR_SUCCESS) {
                if (RegQueryValueExA(key,"DialboxSerialPort",NULL,&type,(LPBYTE)devname,&size)==ERROR_SUCCESS){
                    dial_device=devname;
                }
                RegCloseKey(key);
            }
        }
}


/*  Serial Port Functions */
SERIALPORT *fg_serial_open(const char *device){
    HANDLE fh;
    DCB dcb={sizeof(DCB)};
    COMMTIMEOUTS timeouts;
    SERIALPORT *port;

    TCHAR* tdevice = fghTstrFromStr(device);
    fh = CreateFile(tdevice,GENERIC_READ|GENERIC_WRITE,0,NULL,
      OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    free(tdevice);
    if (!fh) return NULL;

    port = malloc(sizeof(SERIALPORT));
    ZeroMemory(port, sizeof(SERIALPORT));
    port->fh = fh;

    /* save current port settings */
    GetCommState(fh,&port->dcb_save);
    GetCommTimeouts(fh,&port->timeouts_save);

    dcb.DCBlength=sizeof(DCB);
    BuildCommDCBA("96,n,8,1",&dcb);
    SetCommState(fh,&dcb);

    ZeroMemory(&timeouts,sizeof(timeouts));
    timeouts.ReadTotalTimeoutConstant=1;
    timeouts.WriteTotalTimeoutConstant=1;
    SetCommTimeouts(fh,&timeouts);

    fg_serial_flush(port);

    return port;
}

void fg_serial_close(SERIALPORT *port){
    if (port){
        /* restore old port settings */
        SetCommState(port->fh,&port->dcb_save);
        SetCommTimeouts(port->fh,&port->timeouts_save);
        CloseHandle(port->fh);
        free(port);
    }
}

int fg_serial_getchar(SERIALPORT *port){
    DWORD n;
    unsigned char ch;
    if (!port) return EOF;
    if (!ReadFile(port->fh,&ch,1,&n,NULL)) return EOF;
    if (n==1) return ch;
    return EOF;
}

int fg_serial_putchar(SERIALPORT *port, unsigned char ch){
    DWORD n;
    if (!port) return 0;
    return WriteFile(port->fh,&ch,1,&n,NULL);
}

void fg_serial_flush ( SERIALPORT *port )
{
    FlushFileBuffers(port->fh);
}
