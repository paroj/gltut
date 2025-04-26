/*
 * fg_joystick.c
 *
 * Joystick handling code
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Steve Baker, <sjbaker1@airmail.net>
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
#include "fg_internal.h"
#ifdef HAVE_SYS_PARAM_H
#    include <sys/param.h>
#endif

#define JS_TRUE  1
#define JS_FALSE 0

/*
 * Functions associated with the "jsJoystick" class in PLIB
 */
#if TARGET_HOST_MAC_OSX
#define K_NUM_DEVICES   32
int numDevices;
io_object_t ioDevices[K_NUM_DEVICES];

static void fghJoystickFindDevices ( SFG_Joystick* joy, mach_port_t );
static CFDictionaryRef fghJoystickGetCFProperties ( SFG_Joystick* joy, io_object_t );

static void fghJoystickEnumerateElements ( SFG_Joystick* joy, CFTypeRef element );
/* callback for CFArrayApply */
static void fghJoystickElementEnumerator ( SFG_Joystick* joy, void *element, void* vjs );

static void fghJoystickAddAxisElement ( SFG_Joystick* joy, CFDictionaryRef axis );
static void fghJoystickAddButtonElement ( SFG_Joystick* joy, CFDictionaryRef button );
static void fghJoystickAddHatElement ( SFG_Joystick* joy, CFDictionaryRef hat );
#endif


/* External function declarations (mostly platform-specific) */
extern void fgPlatformJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes );
extern void fgPlatformJoystickOpen( SFG_Joystick* joy );
extern void fgPlatformJoystickInit( SFG_Joystick *fgJoystick[], int ident );
extern void fgPlatformJoystickClose ( int ident );

/*
 * The static joystick structure pointer
 */
SFG_Joystick *fgJoystick [ MAX_NUM_JOYSTICKS ];

/*
 * Read the raw joystick data
 */
void fgJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    int i;

    /* Defaults */
    if( buttons )
        *buttons = 0;

    if( axes )
        for( i = 0; i < joy->num_axes; i++ )
            axes[ i ] = 1500.0f;

    if( joy->error )
        return;

    fgPlatformJoystickRawRead ( joy, buttons, axes );
}

/*
 * Correct the joystick axis data
 */
static float fghJoystickFudgeAxis( SFG_Joystick* joy, float value, int axis )
{
    if( value < joy->center[ axis ] )
    {
        float xx = ( value - joy->center[ axis ] ) / ( joy->center[ axis ] -
                                                       joy->min[ axis ] );

        if( xx < -joy->saturate[ axis ] )
            return -1.0f;

        if( xx > -joy->dead_band [ axis ] )
            return 0.0f;

        xx = ( xx + joy->dead_band[ axis ] ) / ( joy->saturate[ axis ] -
                                                 joy->dead_band[ axis ] );

        return ( xx < -1.0f ) ? -1.0f : xx;
    }
    else
    {
        float xx = ( value - joy->center [ axis ] ) / ( joy->max[ axis ] -
                                                        joy->center[ axis ] );

        if( xx > joy->saturate[ axis ] )
            return 1.0f;

        if( xx < joy->dead_band[ axis ] )
            return 0.0f;

        xx = ( xx - joy->dead_band[ axis ] ) / ( joy->saturate[ axis ] -
                                                 joy->dead_band[ axis ] );

        return ( xx > 1.0f ) ? 1.0f : xx;
    }
}

/*
 * Read the corrected joystick data
 */
static void fghJoystickRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    float raw_axes[ _JS_MAX_AXES ];
    int  i;

    if( joy->error )
    {
        if( buttons )
            *buttons = 0;

        if( axes )
            for ( i=0; i<joy->num_axes; i++ )
                axes[ i ] = 0.0f;
    }

    fgJoystickRawRead( joy, buttons, raw_axes );

    if( axes )
        for( i=0; i<joy->num_axes; i++ )
            axes[ i ] = fghJoystickFudgeAxis( joy, raw_axes[ i ], i );
}

/*
 * Happy happy happy joy joy joy (happy new year toudi :D)
 */


#if TARGET_HOST_MAC_OSX
/** open the IOKit connection, enumerate all the HID devices, add their
interface references to the static array. We then use the array index
as the device number when we come to open() the joystick. */
static int fghJoystickFindDevices ( SFG_Joystick *joy, mach_port_t masterPort )
{
    CFMutableDictionaryRef hidMatch = NULL;
    IOReturn rv = kIOReturnSuccess;

    io_iterator_t hidIterator;
    io_object_t ioDev;

    /* build a dictionary matching HID devices */
    hidMatch = IOServiceMatching(kIOHIDDeviceKey);

    rv = IOServiceGetMatchingServices(masterPort, hidMatch, &hidIterator);
    if (rv != kIOReturnSuccess || !hidIterator) {
      fgWarning( "no joystick (HID) devices found" );
      return;
    }

    /* iterate */
    while ((ioDev = IOIteratorNext(hidIterator))) {
        /* filter out keyboard and mouse devices */
        CFDictionaryRef properties = getCFProperties(ioDev);
        long usage, page;

        CFTypeRef refPage = CFDictionaryGetValue (properties, CFSTR(kIOHIDPrimaryUsagePageKey));
        CFTypeRef refUsage = CFDictionaryGetValue (properties, CFSTR(kIOHIDPrimaryUsageKey));
        CFNumberGetValue((CFNumberRef) refUsage, kCFNumberLongType, &usage);
        CFNumberGetValue((CFNumberRef) refPage, kCFNumberLongType, &page);

        /* keep only joystick devices */
        if ( ( page == kHIDPage_GenericDesktop ) && (
                            (usage == kHIDUsage_GD_Joystick)
                         || (usage == kHIDUsage_GD_GamePad)
                         || (usage == kHIDUsage_GD_MultiAxisController)
                         || (usage == kHIDUsage_GD_Hatswitch) /* last two necessary ? */
            /* add it to the array */
            ioDevices[numDevices++] = ioDev;
    }

    IOObjectRelease(hidIterator);
}

static CFDictionaryRef fghJoystickGetCFProperties ( SFG_Joystick *joy, io_object_t ioDev )
{
    IOReturn rv;
    CFMutableDictionaryRef cfProperties;

#if 0
    /* comment copied from darwin/SDL_sysjoystick.c */
    /* Mac OS X currently is not mirroring all USB properties to HID page so need to look at USB device page also
     * get dictionary for usb properties: step up two levels and get CF dictionary for USB properties
     */

    io_registry_entry_t parent1, parent2;

    rv = IORegistryEntryGetParentEntry (ioDev, kIOServicePlane, &parent1);
    if (rv != kIOReturnSuccess) {
        fgWarning ( "error getting device entry parent");
        return NULL;
    }

    rv = IORegistryEntryGetParentEntry (parent1, kIOServicePlane, &parent2);
    if (rv != kIOReturnSuccess) {
        fgWarning ( "error getting device entry parent 2");
        return NULL;
    }
#endif

    rv = IORegistryEntryCreateCFProperties( ioDev /*parent2*/,
        &cfProperties, kCFAllocatorDefault, kNilOptions);
    if (rv != kIOReturnSuccess || !cfProperties) {
        fgWarning ( "error getting device properties");
        return NULL;
    }

    return cfProperties;
}

static void fghJoystickElementEnumerator ( SFG_Joystick *joy, void *element, void* vjs )
{
      if (CFGetTypeID((CFTypeRef) element) != CFDictionaryGetTypeID()) {
            fgError ( "%s", "element enumerator passed non-dictionary value");
            return;
    }

      static_cast<jsJoystick*>(vjs)->parseElement ( (CFDictionaryRef) element );
}

/** element enumerator function : pass NULL for top-level*/
static void fghJoystickEnumerateElements ( SFG_Joystick *joy, CFTypeRef element )
{
      FREEGLUT_INTERNAL_ERROR_EXIT( (CFGetTypeID(element) == CFArrayGetTypeID(),
                                    "Joystick element type mismatch",
                                    "fghJoystickEnumerateElements" );

      CFRange range = {0, CFArrayGetCount ((CFArrayRef)element)};
      CFArrayApplyFunction((CFArrayRef) element, range,
            &fghJoystickElementEnumerator, joy );
}

static void fghJoystickAddAxisElement ( SFG_Joystick *joy, CFDictionaryRef axis )
{
    long cookie, lmin, lmax;
    int index = joy->num_axes++;

    CFNumberGetValue ((CFNumberRef)
        CFDictionaryGetValue ( axis, CFSTR(kIOHIDElementCookieKey) ),
        kCFNumberLongType, &cookie);

    joy->pJoystick.axisCookies[index] = (IOHIDElementCookie) cookie;

    CFNumberGetValue ((CFNumberRef)
        CFDictionaryGetValue ( axis, CFSTR(kIOHIDElementMinKey) ),
        kCFNumberLongType, &lmin);

    CFNumberGetValue ((CFNumberRef)
        CFDictionaryGetValue ( axis, CFSTR(kIOHIDElementMaxKey) ),
        kCFNumberLongType, &lmax);

    joy->min[index] = lmin;
    joy->max[index] = lmax;
    joy->dead_band[index] = 0.0;
    joy->saturate[index] = 1.0;
    joy->center[index] = (lmax + lmin) * 0.5;
}

static void fghJoystickAddButtonElement ( SFG_Joystick *joy, CFDictionaryRef button )
{
    long cookie;
    CFNumberGetValue ((CFNumberRef)
            CFDictionaryGetValue ( button, CFSTR(kIOHIDElementCookieKey) ),
            kCFNumberLongType, &cookie);

    joy->pJoystick.buttonCookies[num_buttons++] = (IOHIDElementCookie) cookie;
    /* anything else for buttons? */
}

static void fghJoystickAddHatElement ( SFG_Joystick *joy, CFDictionaryRef button )
{
    /* hatCookies[num_hats++] = (IOHIDElementCookie) cookie; */
    /* do we map hats to axes or buttons? */
}
#endif

/*
 *  Platform-Specific Code
 */

#if TARGET_HOST_MACINTOSH
void fgPlatformJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    int i;

    if ( buttons )
    {
        *buttons = 0;

        for ( i = 0; i < joy->num_buttons; i++ )
        {
            UInt32 state;
            int err = ISpElement_GetSimpleState ( joy->pJoystick.isp_elem [ i + ISP_NUM_AXIS ], &state);
            ISP_CHECK_ERR(err)

            *buttons |= state << i;
        }
    }

    if ( axes )
    {
        for ( i = 0; i < joy->num_axes; i++ )
        {
            UInt32 state;
            int err = ISpElement_GetSimpleState ( joy->pJoystick.isp_elem [ i ], &state );
            ISP_CHECK_ERR(err)

            axes [i] = (float) state;
        }
    }
}


void fgPlatformJoystickOpen( SFG_Joystick* joy )
{
    int i = 0;
    OSStatus err;

    /* XXX FIXME: get joystick name in Mac */

    err = ISpStartup( );

    if( err == noErr )
    {
#define ISP_CHECK_ERR(x) if( x != noErr ) { joy->error = GL_TRUE; return; }

        joy->error = GL_TRUE;

        /* initialize the needs structure */
        ISpNeed temp_isp_needs[ ISP_NUM_NEEDS ] =
        {
          { "\pX-Axis",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pY-Axis",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pZ-Axis",    128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pR-Axis",    128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   4",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   5",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   6",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   7",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   8",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },

          { "\pButton 0",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 1",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 2",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 3",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 4",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 5",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 6",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 7",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 8",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 9",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 10", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 11", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 12", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 13", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 14", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 15", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 16", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 17", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 18", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 19", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 20", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 21", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 22", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 23", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 24", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 25", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 26", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 27", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 28", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 29", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 30", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 31", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
        };

        memcpy( joy->pJoystick.isp_needs, temp_isp_needs, sizeof (temp_isp_needs ) );


        /* next two calls allow keyboard and mouse to emulate other input
         * devices (gamepads, joysticks, etc)
         */
        /*
          err = ISpDevices_ActivateClass ( kISpDeviceClass_Keyboard );
          ISP_CHECK_ERR(err)


          err = ISpDevices_ActivateClass ( kISpDeviceClass_Mouse );
          ISP_CHECK_ERR(err)
        */

        err = ISpElement_NewVirtualFromNeeds( ISP_NUM_NEEDS,
                                              joy->pJoystick.isp_needs, joy->pJoystick.isp_elem,
                                              0 );
        ISP_CHECK_ERR( err )

        err = ISpInit( ISP_NUM_NEEDS, joy->pJoystick.isp_needs, joy->pJoystick.isp_elem,
                       'freeglut', nil, 0, 128, 0 );
        ISP_CHECK_ERR( err )

        joy->num_buttons = ISP_NUM_NEEDS - ISP_NUM_AXIS;
        joy->num_axes    = ISP_NUM_AXIS;

        for( i = 0; i < joy->num_axes; i++ )
        {
            joy->dead_band[ i ] = 0;
            joy->saturate [ i ] = 1;
            joy->center   [ i ] = kISpAxisMiddle;
            joy->max      [ i ] = kISpAxisMaximum;
            joy->min      [ i ] = kISpAxisMinimum;
        }

        joy->error = GL_FALSE;
    }
    else
        joy->num_buttons = joy->num_axes = 0;
}


void fgPlatformJoystickInit( SFG_Joystick *fgJoystick[], int ident )
{
    fgJoystick[ ident ]->id = ident;
    snprintf( fgJoystick[ ident ]->pJoystick.fname, sizeof(fgJoystick[ ident ]->pJoystick.fname), "/dev/js%d", ident ); /* FIXME */
    fgJoystick[ ident ]->error = GL_FALSE;
}


void fgPlatformJoystickClose ( int ident )
{
    ISpSuspend( );
    ISpStop( );
    ISpShutdown( );
}
#endif

#if TARGET_HOST_MAC_OSX
void fgPlatformJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    int i;

    if ( buttons != NULL )
    {
        *buttons = 0;

        for ( i = 0; i < joy->num_buttons; i++ )
        {
            IOHIDEventStruct hidEvent;
            (*(joy->pJoystick.hidDev))->getElementValue ( joy->pJoystick.hidDev, joy->pJoystick.buttonCookies[i], &hidEvent );
            if ( hidEvent.value )
                *buttons |= 1 << i;
        }
    }

    if ( axes != NULL )
    {
        for ( i = 0; i < joy->num_axes; i++ )
        {
            IOHIDEventStruct hidEvent;
            (*(joy->pJoystick.hidDev))->getElementValue ( joy->pJoystick.hidDev, joy->pJoystick.axisCookies[i], &hidEvent );
            axes[i] = hidEvent.value;
        }
    }
}


void fgPlatformJoystickOpen( SFG_Joystick* joy )
{
    IOReturn rv;
    SInt32 score;
    IOCFPlugInInterface **plugin;

    HRESULT pluginResult;

    CFDictionaryRef props;
    CFTypeRef topLevelElement;

    if( joy->id >= numDevices )
    {
        fgWarning( "device index out of range in fgJoystickOpen()" );
        return;
    }

    /* create device interface */
    rv = IOCreatePlugInInterfaceForService( ioDevices[ joy->id ],
                                            kIOHIDDeviceUserClientTypeID,
                                            kIOCFPlugInInterfaceID,
                                            &plugin, &score );

    if( rv != kIOReturnSuccess )
    {
        fgWarning( "error creating plugin for io device" );
        return;
    }

    pluginResult = ( *plugin )->QueryInterface(
        plugin,
        CFUUIDGetUUIDBytes(kIOHIDDeviceInterfaceID),
        &( LPVOID )joy->pJoystick.hidDev
    );

    if( pluginResult != S_OK )
        fgWarning ( "QI-ing IO plugin to HID Device interface failed" );

    ( *plugin )->Release( plugin ); /* don't leak a ref */
    if( joy->pJoystick.hidDev == NULL )
        return;

    /* store the interface in this instance */
    rv = ( *( joy->pJoystick.hidDev ) )->open( joy->pJoystick.hidDev, 0 );
    if( rv != kIOReturnSuccess )
    {
        fgWarning( "error opening device interface");
        return;
    }

    props = getCFProperties( ioDevices[ joy->id ] );

    /* recursively enumerate all the bits */
    CFTypeRef topLevelElement =
        CFDictionaryGetValue( props, CFSTR( kIOHIDElementKey ) );
    enumerateElements( topLevelElement );

    CFRelease( props );
}


void fgPlatformJoystickInit( SFG_Joystick *fgJoystick[], int ident )
{
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;
    fgJoystick[ ident ]->num_axes = 0;
    fgJoystick[ ident ]->num_buttons = 0;

    if( numDevices < 0 )
    {
        /* do first-time init (since we can't over-ride jsInit, hmm */
        numDevices = 0;

        mach_port_t masterPort;
        IOReturn rv = IOMasterPort( bootstrap_port, &masterPort );
        if( rv != kIOReturnSuccess )
        {
            fgWarning( "error getting master Mach port" );
            return;
        }
        fghJoystickFindDevices( masterPort );
    }

    if ( ident >= numDevices )
    {
        fgJoystick[ ident ]->error = GL_TRUE;
        return;
    }

    /* get the name now too */
    CFDictionaryRef properties = getCFProperties( ioDevices[ ident ] );
    CFTypeRef ref = CFDictionaryGetValue( properties,
                                          CFSTR( kIOHIDProductKey ) );
    if (!ref)
        ref = CFDictionaryGetValue(properties, CFSTR( "USB Product Name" ) );

    if( !ref ||
        !CFStringGetCString( ( CFStringRef )ref, name, 128,
                             CFStringGetSystemEncoding( ) ) )
    {
        fgWarning( "error getting device name" );
        name[ 0 ] = '\0';
    }
}


void fgPlatformJoystickClose ( int ident )
{
    ( *( fgJoystick[ ident ]->pJoystick.hidDev ) )->
        close( fgJoystick[ ident ]->pJoystick.hidDev );
}
#endif




static void fghJoystickOpen( SFG_Joystick* joy )
{
    /*
     * Default values (for no joystick -- each conditional will reset the
     * error flag)
     */
    joy->error = TRUE;
    joy->num_axes = joy->num_buttons = 0;
    joy->name[ 0 ] = '\0';

    fgPlatformJoystickOpen ( joy );

}

/*
 * This function replaces the constructor method in the JS library.
 */
static void fghJoystickInit( int ident )
{
    if( ident >= MAX_NUM_JOYSTICKS )
      fgError( "Too large a joystick number: %d", ident );

    if( fgJoystick[ ident ] )
        fgError( "illegal attempt to initialize joystick device again" );

    fgJoystick[ ident ] =
        ( SFG_Joystick * )calloc( sizeof( SFG_Joystick ), 1 );

    /* Set defaults */
    fgJoystick[ ident ]->num_axes = fgJoystick[ ident ]->num_buttons = 0;
    fgJoystick[ ident ]->error = GL_TRUE;

    fgPlatformJoystickInit( fgJoystick, ident );

    fghJoystickOpen( fgJoystick[ ident  ] );
}

/*
 * Try initializing all the joysticks (well, both of them)
 */
void fgInitialiseJoysticks ( void )
{
    if( !fgState.JoysticksInitialised )
    {
        int ident ;
        for ( ident = 0; ident < MAX_NUM_JOYSTICKS; ident++ )
            fghJoystickInit( ident );

        fgState.JoysticksInitialised = GL_TRUE;
    }
}


void fgJoystickClose( void )
{
    int ident ;
    for( ident = 0; ident < MAX_NUM_JOYSTICKS; ident++ )
    {
        if( fgJoystick[ ident ] )
        {
            fgPlatformJoystickClose ( ident );

            free( fgJoystick[ ident ] );
            fgJoystick[ ident ] = NULL;
            /* show joystick has been deinitialized */
        }
    }
}

/*
 * Polls the joystick and executes the joystick callback hooked to the
 * window specified in the function's parameter:
 */
void fgJoystickPollWindow( SFG_Window* window )
{
    float axes[ _JS_MAX_AXES ];
    int buttons;
    int ident;

    freeglut_return_if_fail( window );
    freeglut_return_if_fail( FETCH_WCB( *window, Joystick ) );

    for( ident = 0; ident < MAX_NUM_JOYSTICKS; ident++ )
    {
        if( fgJoystick[ident] )
        {
            fghJoystickRead( fgJoystick[ident], &buttons, axes );

            if( !fgJoystick[ident]->error )
                INVOKE_WCB( *window, Joystick,
                            ( buttons,
                              (int) ( axes[ 0 ] * 1000.0f ),
                              (int) ( axes[ 1 ] * 1000.0f ),
                              (int) ( axes[ 2 ] * 1000.0f ) )
                );
        }
    }
}

/*
 * Implementation for glutDeviceGet(GLUT_HAS_JOYSTICK)
 */
int fgJoystickDetect( void )
{
    int ident;

    fgInitialiseJoysticks ();

    if ( !fgState.JoysticksInitialised )
        return 0;

    for( ident=0; ident<MAX_NUM_JOYSTICKS; ident++ )
        if( fgJoystick[ident] && !fgJoystick[ident]->error )
            return 1;

    return 0;
}

/*
 * Joystick information, setup and execution functions
 */

/*
 * Forces the joystick callback to be executed
 */
void FGAPIENTRY glutForceJoystickFunc( void )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutForceJoystickFunc" );
#if !defined(_WIN32_WCE)
    freeglut_return_if_fail( fgStructure.CurrentWindow != NULL );
    freeglut_return_if_fail( FETCH_WCB( *( fgStructure.CurrentWindow ), Joystick ) );
    fgJoystickPollWindow( fgStructure.CurrentWindow );
#endif /* !defined(_WIN32_WCE) */
}
int  glutJoystickGetNumAxes( int ident )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetNumAxes" );
    return fgJoystick[ ident ]->num_axes;
}
int  glutJoystickGetNumButtons( int ident )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetNumButtons" );
    return fgJoystick[ ident ]->num_buttons;
}
int  glutJoystickNotWorking( int ident )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickNotWorking" );
    return fgJoystick[ ident ]->error;
}

float glutJoystickGetDeadBand( int ident, int axis )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetDeadBand" );
    return fgJoystick[ ident ]->dead_band [ axis ];
}
void  glutJoystickSetDeadBand( int ident, int axis, float db )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickSetDeadBand" );
    fgJoystick[ ident ]->dead_band[ axis ] = db;
}

float glutJoystickGetSaturation( int ident, int axis )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetSaturation" );
    return fgJoystick[ ident ]->saturate[ axis ];
}
void  glutJoystickSetSaturation( int ident, int axis, float st )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickSetSaturation" );
    fgJoystick[ ident ]->saturate [ axis ] = st;
}

void glutJoystickSetMinRange( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickSetMinRange" );
    memcpy( fgJoystick[ ident ]->min, axes,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}
void glutJoystickSetMaxRange( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickSetMaxRange" );
    memcpy( fgJoystick[ ident ]->max, axes,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}
void glutJoystickSetCenter( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickSetCenter" );
    memcpy( fgJoystick[ ident ]->center, axes,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}

void glutJoystickGetMinRange( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetMinRange" );
    memcpy( axes, fgJoystick[ ident ]->min,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}
void glutJoystickGetMaxRange( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetMaxRange" );
    memcpy( axes, fgJoystick[ ident ]->max,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}
void glutJoystickGetCenter( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetCenter" );
    memcpy( axes, fgJoystick[ ident ]->center,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}

/*** END OF FILE ***/
