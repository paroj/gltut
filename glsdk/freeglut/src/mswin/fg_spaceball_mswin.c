/*
 * fg_spaceball_mswin.c
 *
 * Spaceball support for Windows
 *
 * Copyright (c) 2012 Stephen J. Baker. All Rights Reserved.
 * Written by Evan Felix <karcaw at gmail.com>
 * Creation date: Sat Feb 4, 2012
 *
 * Copyright (c) 2014 Jinrong Xie. All Rights Reserved.
 * Written by Jinrong Xie <stonexjr at gmail.com>
 * Modification date: Wed Dec 24, 2014
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

/*
 * Modified by Jinrong Xie <stonexjr at gmail.com> 12/24/2014
 * for Space Navigator support on Windows.
 * This code is enhanced by at least supporting 3Dconnexion's
 * six degree of freedom navigator.
 */

#include <GL/freeglut.h>
#include <stdlib.h>
#include "../fg_internal.h"

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0501)

enum {
    SPNAV_EVENT_ANY,
    SPNAV_EVENT_MOTION_TRANSLATION,
    SPNAV_EVENT_MOTION_ROTATION,
    SPNAV_EVENT_BUTTON  /* includes both press and release */
};

extern int fg_sball_initialized;
unsigned int __fgSpaceKeystate = 0;
RAWINPUTDEVICE __fgSpaceball = { 0x01, 0x08, 0x00, 0x00 };

/* It seems like some versions of winuser.h define RAWHID.bRawData as an array
 * (which makes sense because that's where the data start), and some define it
 * as a single byte, which is insane. This is probably a mistake which got
 * distributed by accident, but it means we need to work around it by defining
 * our own RAWHID structure.
 */
struct fgRAWHID {
    DWORD dwSizeHid;
    DWORD dwCount;
    BYTE bRawData[1];
};


typedef BOOL(*RegRawInpDevFunc)(PCRAWINPUTDEVICE, UINT, UINT);
typedef UINT(*GetRawInpDataFunc)(HRAWINPUT, UINT, LPVOID, PUINT, UINT);
typedef UINT(*GetRawInpDevInfoFunc)(HANDLE, UINT, LPVOID, PUINT);

static RegRawInpDevFunc fgRegisterRawInputDevices;
static GetRawInpDataFunc fgGetRawInputData;
static GetRawInpDevInfoFunc fgGetRawInputDeviceInfo;


void fgPlatformInitializeSpaceball(void)
{
    HMODULE dllmod;

    if(!fgStructure.CurrentWindow) return;

    if(!(dllmod = GetModuleHandle("user32.dll"))) {
        return;
    }
    fgRegisterRawInputDevices = (RegRawInpDevFunc)GetProcAddress(dllmod, "RegisterRawInputDevices");
    fgGetRawInputData = (GetRawInpDataFunc)GetProcAddress(dllmod, "GetRawInputData");
    fgGetRawInputDeviceInfo = (GetRawInpDevInfoFunc)GetProcAddress(dllmod, "GetRawInputDeviceInfoA");

    if(!fgRegisterRawInputDevices || !fgGetRawInputData || !fgGetRawInputDeviceInfo) {
        return;
    }

    __fgSpaceball.hwndTarget = fgStructure.CurrentWindow->Window.Handle;

    if(!fgRegisterRawInputDevices(&__fgSpaceball, 1, sizeof __fgSpaceball)) {
        __fgSpaceball.hwndTarget = NULL;
        return;
    }

    fg_sball_initialized = 1;
}

void fgPlatformSpaceballClose(void)
{
    return;
}

int fgPlatformHasSpaceball(void)
{
    return __fgSpaceball.hwndTarget ? 1 : 0;
}

int fgPlatformSpaceballNumButtons(void)
{
    return 0;
}

void fgPlatformSpaceballSetWindow(SFG_Window *window)
{
    return;
}

int fgIsSpaceballWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

#define VID_LOGITECH    0x46d
#define VID_3DCONN      0x256f

void fgSpaceballHandleWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    int i, x, y, z;
    short *dataptr;
    unsigned long keystate;
    HRAWINPUT hRawInput = (HRAWINPUT)lParam;
    UINT size;
    BYTE *rawInputBuffer;
    PRAWINPUT pRawInput;
    RID_DEVICE_INFO sRidDeviceInfo;
    SFG_Window *window;

    if(!fg_sball_initialized) {
        fgPlatformInitializeSpaceball();
        if(!fg_sball_initialized) return;
    }

    if(fgGetRawInputData(hRawInput, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER)) == -1) {
        return;
    }

    if(!(rawInputBuffer = malloc(size * sizeof *rawInputBuffer))) {
        return;
    }
    pRawInput = (PRAWINPUT)rawInputBuffer;

    if(fgGetRawInputData(hRawInput, RID_INPUT, pRawInput, &size, sizeof(RAWINPUTHEADER)) == -1) {
        free(rawInputBuffer);
        return;
    }
    if(pRawInput->header.dwType != RIM_TYPEHID) {
        free(rawInputBuffer);
        return;
    }

    sRidDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
    size = sizeof(RID_DEVICE_INFO);
    if(fgGetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_DEVICEINFO, &sRidDeviceInfo, &size) == -1) {
        free(rawInputBuffer);
        return;
    }
    if(!(window = fgWindowByHandle(hwnd))) {
        return;
    }

    if(sRidDeviceInfo.hid.dwVendorId == VID_LOGITECH || sRidDeviceInfo.hid.dwVendorId == VID_3DCONN) {
        /* see definition of fgRAWHID at the top of this file, for an
         * explanation of why we're doing this.
         */
        struct fgRAWHID *hid = (struct fgRAWHID*)&pRawInput->data.hid;

        /* Motion data comes in two parts: motion type and */
        /* displacement/rotation along three axis. */
        /* Orientation is a right handed coordinate system with */
        /* X goes right, Y goes up and Z goes towards viewer, e.g. */
        /* the one used in OpenGL */

        switch(hid->bRawData[0]) {
        case SPNAV_EVENT_MOTION_TRANSLATION:
            /* Translation vector */
            dataptr = (short*)(&hid->bRawData[1]);
            x = dataptr[0];
            y = -dataptr[2];
            z = dataptr[1];
            INVOKE_WCB(*window, SpaceMotion, (x, y, z));
            break;

        case SPNAV_EVENT_MOTION_ROTATION:
            /* Axis aligned rotation vector */
            dataptr = (short*)(&hid->bRawData[1]);
            x = dataptr[0];
            y = -dataptr[2];
            z = dataptr[1];
            INVOKE_WCB(*window, SpaceRotation, (x, y, z));

        case SPNAV_EVENT_BUTTON:
            /* State of the keys */
            keystate = *(unsigned long*)(&hid->bRawData[1]);
            if(FETCH_WCB(*window, SpaceButton)) {
                for(i=0; i<32; i++) {
                    unsigned long stateBefore = __fgSpaceKeystate & (1 << i);
                    unsigned long stateNow = keystate & (1 << i);

                    if(stateBefore && !stateNow) {
                        INVOKE_WCB(*window, SpaceButton, (stateBefore, GLUT_UP));
                    }
                    if(!stateBefore && stateNow) {
                        INVOKE_WCB(*window, SpaceButton, (stateNow, GLUT_DOWN));
                    }
                }
            }
            __fgSpaceKeystate = keystate;
            break;
        }
    }
}

#else
/* windows versions older than winxp don't have the raw HID support used by this
 * spaceball implementation. For now just leave the functions blank to make it
 * build without spaceball support on older versions of windows, until we can
 * investigate a fallback route.
 */

void fgPlatformInitializeSpaceball(void)
{
}

void fgPlatformSpaceballClose(void)
{
}

int fgPlatformHasSpaceball(void)
{
    return 0;
}

int fgPlatformSpaceballNumButtons(void)
{
    return 0;
}

void fgPlatformSpaceballSetWindow(SFG_Window *window)
{
}

int fgIsSpaceballWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void fgSpaceballHandleWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
}

#endif
