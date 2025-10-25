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

#include <ogc/lwp_watchdog.h>
#include <wiikeyboard/keyboard.h>
#include <wiiuse/wpad.h>

extern SFG_Joystick *fgJoystick[MAX_OGC_JOYSTICKS];

static void keysym_to_utf8(uint16_t symbol, char *utf8)
{
    /* ignore private symbols, used by wiikeyboard for special keys */
    if ((symbol >= 0xE000 && symbol <= 0xF8FF) || symbol == 0xFFFF)
        return;

    /* convert UCS-2 to UTF-8 */
    if (symbol < 0x80) {
        utf8[0] = symbol;
    } else if (symbol < 0x800) {
        utf8[0] = 0xC0 | (symbol >> 6);
        utf8[1] = 0x80 | (symbol & 0x3F);
    } else {
        utf8[0] = 0xE0 |  (symbol >> 12);
        utf8[1] = 0x80 | ((symbol >> 6) & 0x3F);
        utf8[2] = 0x80 |  (symbol & 0x3F);
    }
}

static void processKeyboardEvent()
{
    SFG_Window* window = fgStructure.CurrentWindow;
    FGCBKeyboardUC keyboard_cb;
    FGCBSpecialUC special_cb;
    FGCBUserData keyboard_ud;
    FGCBUserData special_ud;
    char string[4] = {'\0'};
    int special = -1;
    keyboard_event ke;

    s32 res = KEYBOARD_GetEvent(&ke);
    if (!res || (ke.type != KEYBOARD_RELEASED && ke.type != KEYBOARD_PRESSED))
        return;

    if (ke.type == KEYBOARD_PRESSED) {
        fprintf(stderr, "Key pressed 0x%04x\n", (int)ke.symbol);
        keyboard_cb = (FGCBKeyboardUC)(FETCH_WCB(*window, Keyboard));
        special_cb  = (FGCBSpecialUC)(FETCH_WCB(*window, Special));
        keyboard_ud = FETCH_USER_DATA_WCB(*window, Keyboard);
        special_ud  = FETCH_USER_DATA_WCB(*window, Special);
    } else {
        keyboard_cb = (FGCBKeyboardUC)(FETCH_WCB(*window, KeyboardUp));
        special_cb  = (FGCBSpecialUC)(FETCH_WCB(*window, SpecialUp));
        keyboard_ud = FETCH_USER_DATA_WCB(*window, KeyboardUp);
        special_ud  = FETCH_USER_DATA_WCB(*window, SpecialUp);
    }

    switch (ke.symbol) {
    case KS_Up: special = GLUT_KEY_UP; break;
    case KS_Down: special = GLUT_KEY_DOWN; break;
    case KS_Left: special = GLUT_KEY_LEFT; break;
    case KS_Right: special = GLUT_KEY_RIGHT; break;
    case KS_Prior: special = GLUT_KEY_PAGE_UP; break;
    case KS_Next: special = GLUT_KEY_PAGE_DOWN; break;
    case KS_Home: special = GLUT_KEY_HOME; break;
    case KS_End: special = GLUT_KEY_END; break;
    case KS_Insert: special = GLUT_KEY_INSERT; break;
    }
    if (special == -1) {
        if (ke.symbol >= KS_F1 && ke.symbol <= KS_F12) {
            special = ke.symbol + GLUT_KEY_F1 - KS_F1;
        } else if (ke.symbol >= KS_f1 && ke.symbol <= KS_f12) {
            special = ke.symbol + GLUT_KEY_F1 - KS_f1;
        }
    }

    if (special_cb && special != -1) {
        special_cb(special, window->State.MouseX, window->State.MouseY, special_ud);
    } else if (keyboard_cb && special == -1) {
        unsigned char key = 0;
        switch (ke.symbol) {
        case KS_Return: key = '\n'; break;
        case KS_Escape: key = 27; break;
        default:
            keysym_to_utf8(ke.symbol, string);
            key = string[0];
        }
        keyboard_cb(key, window->State.MouseX, window->State.MouseY, keyboard_ud);
    }
}

static void updateJoysticks()
{
    static u32 lastScanPads = 0;

    if (fgState.JoysticksInitialised) {
        lastScanPads = PAD_ScanPads();
        for (int i = 0; i < MAX_GC_JOYSTICKS; i++) {
            SFG_Joystick *joy = fgJoystick[i];
            joy->error = !(lastScanPads & (1 << joy->id));
        }
    }

#ifdef __wii__
    /* The WPAD data is also used for the mouse, so we read it even if
     * joysticks haven't been initialized */
    WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
    if (fgState.JoysticksInitialised) {
        for (int i = 0; i < MAX_WII_JOYSTICKS; i++) {
            SFG_Joystick *joy = fgJoystick[i + MAX_GC_JOYSTICKS];
            WPADData *data = WPAD_Data(i);
            joy->error = data->err != WPAD_ERR_NONE || !data->data_present;
        }
    }
#endif
}

/* We don't have a mouse-like device we can use on the GameCube. On the Wii,
 * we'll use the first WiiMote IR. */
#ifdef __wii__

static const struct {
    int wii;
    int mouse;
} s_mouse_button_map[] = {
    { WPAD_BUTTON_B, GLUT_LEFT_BUTTON },
    { WPAD_BUTTON_A, GLUT_RIGHT_BUTTON },
    { WPAD_BUTTON_PLUS, GLUT_MIDDLE_BUTTON },
};
#define MAX_WII_MOUSE_BUTTONS \
    (sizeof(s_mouse_button_map) / sizeof(s_mouse_button_map[0]))

static void updateMouse()
{
    int oldX, oldY;
    WPADData *data = WPAD_Data(0);
    if (!data->ir.valid) return;

    SFG_Window *window = fgStructure.CurrentWindow;
    if (!window) return;

    oldX = window->State.MouseX;
    oldY = window->State.MouseY;
    window->State.MouseX = data->ir.x * fgDisplay.ScreenWidth / 640;
    window->State.MouseY = data->ir.y * fgDisplay.ScreenHeight / 480;

    bool buttonPressed = false;
    for (int b = 0; b < MAX_WII_MOUSE_BUTTONS; b++) {
        if (data->btns_d & s_mouse_button_map[b].wii) {
            INVOKE_WCB(*window, Mouse,
                (s_mouse_button_map[b].mouse,
                 GLUT_DOWN,
                 window->State.MouseX,
                 window->State.MouseY)
            );
        }
        if (data->btns_u & s_mouse_button_map[b].wii) {
            INVOKE_WCB(*window, Mouse,
                (s_mouse_button_map[b].mouse,
                 GLUT_UP,
                 window->State.MouseX,
                 window->State.MouseY)
            );
            buttonPressed = true;
        }
        if (data->btns_h & s_mouse_button_map[b].wii) {
            buttonPressed = true;
        }
    }

    if (oldX != window->State.MouseX || oldY != window->State.MouseY) {
        if (buttonPressed) {
            INVOKE_WCB(*window, Motion, (window->State.MouseX,
                                         window->State.MouseY));
        } else {
            INVOKE_WCB(*window, Passive, (window->State.MouseX,
                                          window->State.MouseY));
        }
    }
}
#endif

fg_time_t fgPlatformSystemTime(void)
{
    return gettime() / TB_TIMER_CLOCK;
}

void fgPlatformSleepForEvents(fg_time_t ms)
{
    /* FreeGlut does not offer a hook for redrawing the window in single-buffer
     * mode, so let's to it here. */
    if (!(fgState.DisplayMode & GLUT_DOUBLE)) {
        fgOgcDisplayShowEFB();
    }

    /* If the mouse is active, reduce the sleep time to a few milliseconds
     * only, since our mouse is emulated via the Wiimote, which must be
     * regularly polled */
    if (ms > 10 && fgStructure.CurrentWindow &&
        (FETCH_WCB(*fgStructure.CurrentWindow, Motion) ||
         FETCH_WCB(*fgStructure.CurrentWindow, Mouse))) {
        ms = 10;
    }

    struct timespec tv;
    tv.tv_sec = ms / 1000;
    tv.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&tv, NULL);
}

void fgPlatformProcessSingleEvent(void)
{
    /* If an idle callback is specified, then fgPlatformSleepForEvents is not
     * called, so we must find another place to render our scene (if using a
     * single buffer). Let's do it here. */
    if (fgState.IdleCallback && !(fgState.DisplayMode & GLUT_DOUBLE)) {
        fgOgcDisplayShowEFB();
    }

    processKeyboardEvent();
    updateJoysticks();
#ifdef __wii__
    updateMouse();
#endif
}

void fgPlatformMainLoopPreliminaryWork(void)
{
    fgWarning("%s()", __func__);
    KEYBOARD_Init(NULL);
#ifdef __wii__
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetVRes(WPAD_CHAN_ALL, 640, 480);
#endif
}

void fgPlatformInitWork(SFG_Window *window)
{
    fghOnReshapeNotify(window,
                       fgDisplay.ScreenWidth, fgDisplay.ScreenHeight,
                       GL_FALSE);
}

void fgPlatformPosResZordWork(SFG_Window *window, unsigned int workMask)
{
    fgWarning("%s() : not implemented", __func__);
}

void fgPlatformVisibilityWork(SFG_Window *window)
{
    INVOKE_WCB(*window, WindowStatus, (GLUT_FULLY_RETAINED));
}

void fgPlatformSetColor(int idx, float r, float g, float b)
{
    fgWarning("%s() : not implemented", __func__);
}

float fgPlatformGetColor(int idx, int comp)
{
    fgWarning("%s() : not implemented", __func__);
    return 0.0;
}

void fgPlatformCopyColormap(int win)
{
    fgWarning("%s() : not implemented", __func__);
}
