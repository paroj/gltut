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

#include <wiiuse/wpad.h>

void fgPlatformJoystickRawRead(SFG_Joystick *joy, int *buttons, float *axes)
{
    *buttons = 0;

    if (joy->id < MAX_GC_JOYSTICKS) {
        u16 btns = PAD_ButtonsHeld(joy->id);
        if (btns & PAD_BUTTON_A) *buttons |= 0x1;
        if (btns & PAD_BUTTON_B) *buttons |= 0x2;
        if (btns & PAD_BUTTON_X) *buttons |= 0x4;
        if (btns & PAD_BUTTON_Y) *buttons |= 0x8;
        if (btns & PAD_TRIGGER_L) *buttons |= 0x10;
        if (btns & PAD_TRIGGER_R) *buttons |= 0x20;
        if (btns & PAD_TRIGGER_Z) *buttons |= 0x40;
        if (btns & PAD_BUTTON_MENU) *buttons |= 0x80;
        if (btns & PAD_BUTTON_START) *buttons |= 0x100;
        axes[0] = PAD_StickX(joy->id) / 127.0;
        axes[1] = PAD_StickY(joy->id) / 127.0;
        axes[2] = PAD_SubStickX(joy->id) / 127.0;
        axes[3] = PAD_SubStickY(joy->id) / 127.0;
        return;
    }

#ifdef __wii__
    int id = joy->id - MAX_GC_JOYSTICKS;
    if (id < MAX_WII_JOYSTICKS) {
        WPADData *data = WPAD_Data(id);
        u32 btns = data->btns_h;
        axes[0] = 0.0;
        axes[1] = 0.0;
        if (btns & WPAD_BUTTON_LEFT) axes[0] = -1.0;
        if (btns & WPAD_BUTTON_RIGHT) axes[0] = 1.0;
        if (btns & WPAD_BUTTON_UP) axes[1] = 1.0;
        if (btns & WPAD_BUTTON_DOWN) axes[1] = -1.0;

        if (btns & WPAD_BUTTON_1) *buttons |= 0x1;
        if (btns & WPAD_BUTTON_2) *buttons |= 0x2;
        if (btns & WPAD_BUTTON_A) *buttons |= 0x4;
        if (btns & WPAD_BUTTON_B) *buttons |= 0x8;
        if (btns & WPAD_BUTTON_MINUS) *buttons |= 0x10;
        if (btns & WPAD_BUTTON_PLUS) *buttons |= 0x20;
        if (btns & WPAD_BUTTON_HOME) *buttons |= 0x40;
    }
#endif
}

void fgPlatformJoystickOpen(SFG_Joystick *joy)
{
    fgWarning("%s() called for joystick %d", __func__, joy->id);
    joy->error = GL_FALSE;
    if (joy->id < MAX_GC_JOYSTICKS) {
        sprintf(joy->name, "GameCube #%d", joy->id);
        joy->num_axes = 4;
        joy->num_buttons = 8;
    } else {
        sprintf(joy->name, "Wiimote #%d", joy->id - MAX_GC_JOYSTICKS);
        joy->num_axes = 2;
        joy->num_buttons = 7;
    }

    for (int i = 0; i < joy->num_axes; i++) {
        joy->center[i] = 0.0;
        joy->max[i] = 1.0;
        joy->min[i] = -1.0;
        joy->dead_band[i] = 0.0;
        joy->saturate[i] = 1.0;
    }
}

void fgPlatformJoystickInit(SFG_Joystick *fgJoystick[], int ident)
{
    static bool initialized = false;
    if (!initialized) {
        initialized = true;

        PAD_Init();
        /* WPAD is initialized in fgPlatformMainLoopPreliminaryWork(), since
         * it's used for mouse emulation as well. */
    }

    fgWarning("%s called for ident %d\n", __func__, ident);
    if (ident < MAX_OGC_JOYSTICKS) {
        SFG_Joystick *joy = fgJoystick[ident];
        joy->id = ident;
        joy->error = GL_FALSE;
    }
}

void fgPlatformJoystickClose(int ident)
{
    fgWarning("%s() : not implemented", __func__);
}
