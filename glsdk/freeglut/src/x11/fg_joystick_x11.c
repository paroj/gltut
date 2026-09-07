/*
 * fg_joystick_x11.c
 *
 * Joystick handling code
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Steve Baker, <sjbaker1@airmail.net>
 * Copied for Platform code by Evan Felix <karcaw at gmail.com>
 * Creation date: Thur Feb 2 2012
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
 * FreeBSD port by Stephen Montgomery-Smith <stephen@math.missouri.edu>
 *
 * Redone by John Fay 2/4/04 with another look from the PLIB "js" library.
 *  Many thanks for Steve Baker for permission to pull from that library.
 */

#include <GL/freeglut.h>
#include "../fg_internal.h"
#ifdef HAVE_SYS_PARAM_H
#    include <sys/param.h>
#endif

#include <fcntl.h>


/* BSD defines from "jsBSD.cxx" around lines 42-270 */

#if defined(__NetBSD__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

#    ifdef HAVE_USB_JS
#        if defined(__NetBSD__)
#            ifdef HAVE_USBHID_H
#                include <usbhid.h>
#            else
#                include <usb.h>
#            endif
#            include <dev/usb/usb.h>
#        elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#            ifdef HAVE_USBHID_H
#                include <usbhid.h>
#            else
#                include <libusbhid.h>
#            endif
#if __FreeBSD_version < 800061
#            include <legacy/dev/usb/usb.h>
#else
#            include <dev/usb/usb_ioctl.h>
#            include <dev/usb/usb.h>
#endif
#        endif
#        include <dev/usb/usbhid.h>

/* Compatibility with older usb.h revisions */
#        if !defined(USB_MAX_DEVNAMES) && defined(MAXDEVNAMES)
#            define USB_MAX_DEVNAMES MAXDEVNAMES
#        endif
#    endif

struct os_specific_s {
  char             fname [128 ];
  int              fd;
  int              is_analog;
  /* The following structure members are specific to analog joysticks */
  struct joystick  ajs;
#    ifdef HAVE_USB_JS
  /* The following structure members are specific to USB joysticks */
  struct hid_item *hids;
  int              hid_dlen;
  int              hid_offset;
  char            *hid_data_buf;
  int              axes_usage [ _JS_MAX_AXES ];
#    endif
  /* We keep button and axes state ourselves, as they might not be updated
   * on every read of a USB device
   */
  int              cache_buttons;
  float            cache_axes [ _JS_MAX_AXES ];
};

/* Idents lower than USB_IDENT_OFFSET are for analog joysticks. */
#    define USB_IDENT_OFFSET    2

#    define USBDEV "/dev/usb"
#    define UHIDDEV "/dev/uhid"
#    define AJSDEV "/dev/joy"


#endif

#if defined(__NetBSD__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
static int hatmap_x[9] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
static int hatmap_y[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

#    ifdef HAVE_USB_JS
/*
* fghJoystickFindUSBdev (and its helper, fghJoystickWalkUSBdev) try to locate
* the full name of a USB device. If /dev/usbN isn't readable, we punt and
* return the uhidN device name. We warn the user of this situation once.
*/
static char *fghJoystickWalkUSBdev(int f, char *dev, char *out, int outlen)
{
#if __FreeBSD_version < 800061
    struct usb_device_info di;
    int i, a;
    char *cp;

    for (a = 1; a < USB_MAX_DEVICES; a++) {
        di.udi_addr = a;
        if (ioctl(f, USB_DEVICEINFO, &di) != 0)
            return NULL;
        for (i = 0; i < USB_MAX_DEVNAMES; i++)
            if (di.udi_devnames[i][0] &&
                strcmp(di.udi_devnames[i], dev) == 0) {
                cp = calloc(1, strlen(di.udi_vendor) + strlen(di.udi_product) + 2);
                strcpy(cp, di.udi_vendor);
                strcat(cp, " ");
                strcat(cp, di.udi_product);
                strncpy(out, cp, outlen - 1);
                out[outlen - 1] = 0;
                free(cp);
                return out;
            }
    }
#endif
    return NULL;
}

static int fghJoystickFindUSBdev(char *name, char *out, int outlen)
{
    int i, f;
    char buf[50];
    char *cp;
    static int protection_warned = 0;

    for (i = 0; i < 16; i++) {
        snprintf(buf, sizeof(buf), "%s%d", USBDEV, i);
        f = open(buf, O_RDONLY);
        if (f >= 0) {
            cp = fghJoystickWalkUSBdev(f, name, out, outlen);
            close(f);
            if (cp)
                return 1;
        }
        else if (errno == EACCES) {
            if (!protection_warned) {
                fgWarning("Can't open %s for read!", buf);
                protection_warned = 1;
            }
        }
    }
    return 0;
}
#endif

static int fghJoystickInitializeHID(struct os_specific_s *os,
                                    int *num_axes, int *num_buttons)
{
    int size, is_joystick;
#   ifdef HAVE_USBHID_H
    int report_id = 0;
#   endif
    struct hid_data *d;
    struct hid_item h;
    report_desc_t rd;

    if ((rd = hid_get_report_desc(os->fd)) == 0)
    {
        fgWarning("error: %s: %s", os->fname, strerror(errno));
        return FALSE;
    }

    os->hids = NULL;

#   ifdef HAVE_USBHID_H
    if (ioctl(os->fd, USB_GET_REPORT_ID, &report_id) < 0)
    {
        /*** XXX {report_id} may not be the right variable? ***/
        fgWarning("error: %s%d: %s", UHIDDEV, report_id, strerror(errno));
        return FALSE;
    }

    size = hid_report_size(rd, hid_input, report_id);
#   else
    size = hid_report_size(rd, 0, hid_input);
#   endif
    os->hid_data_buf = calloc(1, size);
    os->hid_dlen = size;

    is_joystick = 0;
#   ifdef HAVE_USBHID_H
    d = hid_start_parse(rd, 1 << hid_input, report_id);
#   else
    d = hid_start_parse(rd, 1 << hid_input);
#   endif
    while (hid_get_item(d, &h))
    {
        int usage, page, interesting_hid;

        page = HID_PAGE(h.usage);
        usage = HID_USAGE(h.usage);

        /* This test is somewhat too simplistic, but this is how MicroSoft
        * does, so I guess it works for all joysticks/game pads. */
        is_joystick = is_joystick ||
            (h.kind == hid_collection &&
             page == HUP_GENERIC_DESKTOP &&
             (usage == HUG_JOYSTICK || usage == HUG_GAME_PAD));

        if (h.kind != hid_input)
            continue;

        if (!is_joystick)
            continue;

        interesting_hid = TRUE;
        if (page == HUP_GENERIC_DESKTOP)
        {
            switch (usage)
            {
                case HUG_X:
                case HUG_RX:
                case HUG_Y:
                case HUG_RY:
                case HUG_Z:
                case HUG_RZ:
                case HUG_SLIDER:
                    if (*num_axes < _JS_MAX_AXES)
                    {
                        os->axes_usage[*num_axes] = usage;
                        (*num_axes)++;
                    }
                    break;
                case HUG_HAT_SWITCH:
                    /* Allocate two axes for a hat */
                    if (*num_axes + 1 < _JS_MAX_AXES)
                    {
                        os->axes_usage[*num_axes] = usage;
                        (*num_axes)++;
                        os->axes_usage[*num_axes] = usage;
                        (*num_axes)++;
                    }
                    break;
                default:
                    interesting_hid = FALSE;
                    break;
            }
        }
        else if (page == HUP_BUTTON)
        {
            interesting_hid = (usage > 0) &&
                (usage <= _JS_MAX_BUTTONS);

            if (interesting_hid && usage - 1 > *num_buttons)
                *num_buttons = usage - 1;
        }

        if (interesting_hid)
        {
            h.next = os->hids;
            os->hids = calloc(1, sizeof(struct hid_item));
            *os->hids = h;
        }
    }
    hid_end_parse(d);

    return os->hids != NULL;
}
#    endif
#endif


/*this should be defined in a header file */
#define MAX_NUM_JOYSTICKS  2
extern SFG_Joystick *fgJoystick [ MAX_NUM_JOYSTICKS ];

void fgPlatformJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    int status;

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    int len;

    if ( joy->pJoystick.os->is_analog )
    {
        int status = read ( joy->pJoystick.os->fd, &joy->pJoystick.os->ajs, sizeof(joy->pJoystick.os->ajs) );
        if ( status != sizeof(joy->pJoystick.os->ajs) ) {
            perror ( joy->pJoystick.os->fname );
            joy->error = GL_TRUE;
            return;
        }
        if ( buttons != NULL )
            *buttons = ( joy->pJoystick.os->ajs.b1 ? 1 : 0 ) | ( joy->pJoystick.os->ajs.b2 ? 2 : 0 );

        if ( axes != NULL )
        {
            axes[0] = (float) joy->pJoystick.os->ajs.x;
            axes[1] = (float) joy->pJoystick.os->ajs.y;
        }

        return;
    }

#  ifdef HAVE_USB_JS
    while ( ( len = read ( joy->pJoystick.os->fd, joy->pJoystick.os->hid_data_buf, joy->pJoystick.os->hid_dlen ) ) == joy->pJoystick.os->hid_dlen )
    {
        struct hid_item *h;

        for  ( h = joy->pJoystick.os->hids; h; h = h->next )
        {
            int d = hid_get_data ( joy->pJoystick.os->hid_data_buf, h );

            int page = HID_PAGE ( h->usage );
            int usage = HID_USAGE ( h->usage );

            if ( page == HUP_GENERIC_DESKTOP )
            {
                int i;
                for ( i = 0; i < joy->num_axes; i++ )
                    if (joy->pJoystick.os->axes_usage[i] == usage)
                    {
                        if (usage == HUG_HAT_SWITCH)
                        {
                            if (d < 0 || d > 8)
                                d = 0;  /* safety */
                            joy->pJoystick.os->cache_axes[i] = (float)hatmap_x[d];
                            joy->pJoystick.os->cache_axes[i + 1] = (float)hatmap_y[d];
                        }
                        else
                        {
                            joy->pJoystick.os->cache_axes[i] = (float)d;
                        }
                        break;
                    }
            }
            else if (page == HUP_BUTTON)
            {
               if (usage > 0 && usage < _JS_MAX_BUTTONS + 1)
               {
                   if (d)
                       joy->pJoystick.os->cache_buttons |=  (1 << ( usage - 1 ));
                   else
                       joy->pJoystick.os->cache_buttons &= ~(1 << ( usage - 1 ));
               }
            }
        }
    }
    if ( len < 0 && errno != EAGAIN )
    {
        perror( joy->pJoystick.os->fname );
        joy->error = 1;
    }
    if ( buttons != NULL ) *buttons = joy->pJoystick.os->cache_buttons;
    if ( axes    != NULL )
        memcpy ( axes, joy->pJoystick.os->cache_axes, sizeof(float) * joy->num_axes );
#  endif
#endif

#ifdef JS_NEW

    while ( 1 )
    {
        status = read ( joy->pJoystick.fd, &joy->pJoystick.js, sizeof(struct js_event) );

        if ( status != sizeof( struct js_event ) )
        {
            if ( errno == EAGAIN )
            {
                /* Use the old values */
                if ( buttons )
                    *buttons = joy->pJoystick.tmp_buttons;
                if ( axes )
                    memcpy( axes, joy->pJoystick.tmp_axes,
                            sizeof( float ) * joy->num_axes );
                return;
            }

            fgWarning ( "%s", joy->pJoystick.fname );
            joy->error = GL_TRUE;
            return;
        }

        switch ( joy->pJoystick.js.type & ~JS_EVENT_INIT )
        {
        case JS_EVENT_BUTTON:
            if( joy->pJoystick.js.value == 0 ) /* clear the flag */
                joy->pJoystick.tmp_buttons &= ~( 1 << joy->pJoystick.js.number );
            else
                joy->pJoystick.tmp_buttons |= ( 1 << joy->pJoystick.js.number );
            break;

        case JS_EVENT_AXIS:
            if ( joy->pJoystick.js.number < joy->num_axes )
            {
                joy->pJoystick.tmp_axes[ joy->pJoystick.js.number ] = ( float )joy->pJoystick.js.value;

                if( axes )
                    memcpy( axes, joy->pJoystick.tmp_axes, sizeof(float) * joy->num_axes );
            }
            break;

        default:
            fgWarning ( "PLIB_JS: Unrecognised /dev/js return!?!" );

            /* use the old values */

            if ( buttons != NULL ) *buttons = joy->pJoystick.tmp_buttons;
            if ( axes    != NULL )
                memcpy ( axes, joy->pJoystick.tmp_axes, sizeof(float) * joy->num_axes );

            return;
        }

        if( buttons )
            *buttons = joy->pJoystick.tmp_buttons;
    }
#else

    status = read( joy->pJoystick.fd, &joy->pJoystick.js, JS_RETURN );

    if ( status != JS_RETURN )
    {
        fgWarning( "%s", joy->pJoystick.fname );
        joy->error = GL_TRUE;
        return;
    }

    if ( buttons )
#    if defined( __FreeBSD__ ) || defined(__FreeBSD_kernel__) || defined( __NetBSD__ )
        *buttons = ( joy->pJoystick.js.b1 ? 1 : 0 ) | ( joy->pJoystick.js.b2 ? 2 : 0 );  /* XXX Should not be here -- BSD is handled earlier */
#    else
        *buttons = joy->pJoystick.js.buttons;
#    endif

    if ( axes )
    {
        axes[ 0 ] = (float) joy->pJoystick.js.x;
        axes[ 1 ] = (float) joy->pJoystick.js.y;
    }
#endif
}


void fgPlatformJoystickOpen( SFG_Joystick* joy )
{
#if defined( __FreeBSD__ ) || defined(__FreeBSD_kernel__)
    int i = 0;
       char *cp;
#endif
#ifdef JS_NEW
       unsigned char u;
    int i=0;
#else
#  if defined( __linux__ ) || TARGET_HOST_SOLARIS
    int i = 0;
    int counter = 0;
#  endif
#endif

#if defined( __FreeBSD__ ) || defined(__FreeBSD_kernel__)
    for( i = 0; i < _JS_MAX_AXES; i++ )
        joy->pJoystick.os->cache_axes[ i ] = 0.0f;

    joy->pJoystick.os->cache_buttons = 0;

    joy->pJoystick.os->fd = open( joy->pJoystick.os->fname, O_RDONLY | O_NONBLOCK);

    if( joy->pJoystick.os->fd < 0 && errno == EACCES )
        fgWarning ( "%s exists but is not readable by you", joy->pJoystick.os->fname );

    joy->error =( joy->pJoystick.os->fd < 0 );

    if( joy->error )
        return;

    joy->num_axes = 0;
    joy->num_buttons = 0;
    if( joy->pJoystick.os->is_analog )
    {
        FILE *joyfile;
        char joyfname[ 1024 ];
        int noargs, in_no_axes;

        float axes [ _JS_MAX_AXES ];
        int buttons[ _JS_MAX_AXES ];

        joy->num_axes    =  2;
        joy->num_buttons = 32;

        fgJoystickRawRead( joy, buttons, axes );
        joy->error = axes[ 0 ] < -1000000000.0f;
        if( joy->error )
            return;

        snprintf( joyfname, sizeof(joyfname), "%s/.joy%drc", getenv( "HOME" ), joy->id );

        joyfile = fopen( joyfname, "r" );
        joy->error =( joyfile == NULL );
        if( joy->error )
            return;

        noargs = fscanf( joyfile, "%d%f%f%f%f%f%f", &in_no_axes,
                         &joy->min[ 0 ], &joy->center[ 0 ], &joy->max[ 0 ],
                         &joy->min[ 1 ], &joy->center[ 1 ], &joy->max[ 1 ] );
        joy->error = noargs != 7 || in_no_axes != _JS_MAX_AXES;
        fclose( joyfile );
        if( joy->error )
            return;

        for( i = 0; i < _JS_MAX_AXES; i++ )
        {
            joy->dead_band[ i ] = 0.0f;
            joy->saturate [ i ] = 1.0f;
        }

        return;    /* End of analog code */
    }

#    ifdef HAVE_USB_JS
    if( ! fghJoystickInitializeHID( joy->pJoystick.os, &joy->num_axes,
                                    &joy->num_buttons ) )
    {
        close( joy->pJoystick.os->fd );
        joy->error = GL_TRUE;
        return;
    }

    cp = strrchr( joy->pJoystick.os->fname, '/' );
    if( cp )
    {
        if( fghJoystickFindUSBdev( &cp[1], joy->name, sizeof( joy->name ) ) ==
            0 )
            strcpy( joy->name, &cp[1] );
    }

    if( joy->num_axes > _JS_MAX_AXES )
        joy->num_axes = _JS_MAX_AXES;

    for( i = 0; i < _JS_MAX_AXES; i++ )
    {
        /* We really should get this from the HID, but that data seems
         * to be quite unreliable for analog-to-USB converters. Punt for
         * now.
         */
        if( joy->pJoystick.os->axes_usage[ i ] == HUG_HAT_SWITCH )
        {
            joy->max   [ i ] = 1.0f;
            joy->center[ i ] = 0.0f;
            joy->min   [ i ] = -1.0f;
        }
        else
        {
            joy->max   [ i ] = 255.0f;
            joy->center[ i ] = 127.0f;
            joy->min   [ i ] = 0.0f;
        }

        joy->dead_band[ i ] = 0.0f;
        joy->saturate[ i ] = 1.0f;
    }
#    endif
#endif

#if defined( __linux__ ) || TARGET_HOST_SOLARIS
    /* Default for older Linux systems. */
    joy->num_axes    =  2;
    joy->num_buttons = 32;

#    ifdef JS_NEW
    for( i = 0; i < _JS_MAX_AXES; i++ )
        joy->pJoystick.tmp_axes[ i ] = 0.0f;

    joy->pJoystick.tmp_buttons = 0;
#    endif

    joy->pJoystick.fd = open( joy->pJoystick.fname, O_RDONLY );

    joy->error =( joy->pJoystick.fd < 0 );

    if( joy->error )
        return;

    /* Set the correct number of axes for the linux driver */
#    ifdef JS_NEW
    /* Melchior Franz's fixes for big-endian Linuxes since writing
     *  to the upper byte of an uninitialized word doesn't work.
     *  9 April 2003
     */
    if(ioctl(joy->pJoystick.fd, JSIOCGAXES, &u) != -1)
        joy->num_axes = u;
    if(ioctl(joy->pJoystick.fd, JSIOCGBUTTONS, &u) != -1)
        joy->num_buttons = u;
    ioctl( joy->pJoystick.fd, JSIOCGNAME( sizeof( joy->name ) ), joy->name );
    fcntl(joy->pJoystick.fd, F_SETFL, fcntl(joy->pJoystick.fd, F_GETFL) | O_NONBLOCK);
#    endif

    /*
     * The Linux driver seems to return 512 for all axes
     * when no stick is present - but there is a chance
     * that could happen by accident - so it's gotta happen
     * on both axes for at least 100 attempts.
     *
     * PWO: shouldn't be that done somehow wiser on the kernel level?
     */
#    ifndef JS_NEW
    counter = 0;

    do
    {
        fgJoystickRawRead( joy, NULL, joy->center );
        counter++;
    } while( !joy->error &&
             counter < 100 &&
             joy->center[ 0 ] == 512.0f &&
             joy->center[ 1 ] == 512.0f );

    if ( counter >= 100 )
        joy->error = GL_TRUE;
#    endif

    for( i = 0; i < _JS_MAX_AXES; i++ )
    {
#    ifdef JS_NEW
        joy->max   [ i ] =  32767.0f;
        joy->center[ i ] =      0.0f;
        joy->min   [ i ] = -32767.0f;
#    else
        joy->max[ i ] = joy->center[ i ] * 2.0f;
        joy->min[ i ] = 0.0f;
#    endif
        joy->dead_band[ i ] = 0.0f;
        joy->saturate [ i ] = 1.0f;
    }
#endif
}


void fgPlatformJoystickInit( SFG_Joystick *fgJoystick[], int ident )
{
#if defined( __FreeBSD__ ) || defined(__FreeBSD_kernel__)
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;

    fgJoystick[ ident ]->pJoystick.os = calloc( 1, sizeof( struct os_specific_s ) );
    memset( fgJoystick[ ident ]->pJoystick.os, 0, sizeof( struct os_specific_s ) );
    if( ident < USB_IDENT_OFFSET )
        fgJoystick[ ident ]->pJoystick.os->is_analog = 1;
    if( fgJoystick[ ident ]->pJoystick.os->is_analog )
        snprintf( fgJoystick[ ident ]->pJoystick.os->fname, sizeof(fgJoystick[ ident ]->pJoystick.os->fname), "%s%d", AJSDEV, ident );
    else
        snprintf( fgJoystick[ ident ]->pJoystick.os->fname, sizeof(fgJoystick[ ident ]->pJoystick.os->fname), "%s%d", UHIDDEV,
                 ident - USB_IDENT_OFFSET );
#elif defined( __linux__ )
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;

    snprintf( fgJoystick[ident]->pJoystick.fname, sizeof(fgJoystick[ident]->pJoystick.fname), "/dev/input/js%d", ident );

    if( access( fgJoystick[ ident ]->pJoystick.fname, F_OK ) != 0 )
        snprintf( fgJoystick[ ident ]->pJoystick.fname, sizeof(fgJoystick[ ident ]->pJoystick.fname), "/dev/js%d", ident );
#endif
}


void fgPlatformJoystickClose ( int ident )
{
#if defined( __FreeBSD__ ) || defined(__FreeBSD_kernel__)
    if( fgJoystick[ident]->pJoystick.os )
    {
        if( ! fgJoystick[ ident ]->error )
            close( fgJoystick[ ident ]->pJoystick.os->fd );
#ifdef HAVE_USB_JS
        if( fgJoystick[ ident ]->pJoystick.os->hids )
            free (fgJoystick[ ident ]->pJoystick.os->hids);
        if( fgJoystick[ ident ]->pJoystick.os->hid_data_buf )
            free( fgJoystick[ ident ]->pJoystick.os->hid_data_buf );
#endif
        free( fgJoystick[ident]->pJoystick.os );
    }
#endif

    if( ! fgJoystick[ident]->error )
         close( fgJoystick[ ident ]->pJoystick.fd );
}

