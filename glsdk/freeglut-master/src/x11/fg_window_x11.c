/*
 * fg_window_x11.c
 *
 * Window management methods for X11
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
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

#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include <limits.h>     /* LONG_MAX */
#include <unistd.h>     /* usleep, gethostname, getpid */
#include <sys/types.h>  /* pid_t */
#include "../fg_internal.h"

#ifdef EGL_VERSION_1_0
#include "egl/fg_window_egl.h"
#define fghCreateNewContext fghCreateNewContextEGL
#else
#include "x11/fg_window_x11_glx.h"
#endif

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX	255
#endif

static void set_title(Window win, Atom prop, const char *str);
#ifdef X_HAVE_UTF8_STRING
static int set_utf8_title(Window win, Atom prop, const char *str);
#endif

/* Motif window hints, only define needed ones */
typedef struct
{
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
} MotifWmHints;
#define MWM_HINTS_DECORATIONS         (1L << 1)
#define MWM_DECOR_BORDER              (1L << 1)

static int fghResizeFullscrToggle(void)
{
    XWindowAttributes attributes;
    SFG_Window *win = fgStructure.CurrentWindow;

    if(glutGet(GLUT_FULL_SCREEN)) {
        /* restore original window size */
        fgStructure.CurrentWindow->State.WorkMask = GLUT_SIZE_WORK;
        fgStructure.CurrentWindow->State.DesiredWidth  = win->State.pWState.OldWidth;
        fgStructure.CurrentWindow->State.DesiredHeight = win->State.pWState.OldHeight;

    } else {
        fgStructure.CurrentWindow->State.pWState.OldWidth  = win->State.Width;
        fgStructure.CurrentWindow->State.pWState.OldHeight = win->State.Height;

        /* resize the window to cover the entire screen */
        XGetWindowAttributes(fgDisplay.pDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                &attributes);

        /*
         * The "x" and "y" members of "attributes" are the window's coordinates
         * relative to its parent, i.e. to the decoration window.
         */
        XMoveResizeWindow(fgDisplay.pDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                -attributes.x,
                -attributes.y,
                fgDisplay.ScreenWidth,
                fgDisplay.ScreenHeight);
    }
    return 0;
}

#define _NET_WM_STATE_TOGGLE    2
static int fghEwmhFullscrToggle(void)
{
    XEvent xev;
    long evmask = SubstructureRedirectMask | SubstructureNotifyMask;

    if(!fgDisplay.pDisplay.State || !fgDisplay.pDisplay.StateFullScreen) {
        return -1;
    }

    xev.type = ClientMessage;
    xev.xclient.window = fgStructure.CurrentWindow->Window.Handle;
    xev.xclient.message_type = fgDisplay.pDisplay.State;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = _NET_WM_STATE_TOGGLE;
    xev.xclient.data.l[1] = fgDisplay.pDisplay.StateFullScreen;
    xev.xclient.data.l[2] = 0;	/* no second property to toggle */
    xev.xclient.data.l[3] = 1;	/* source indication: application */
    xev.xclient.data.l[4] = 0;	/* unused */

    if(!XSendEvent(fgDisplay.pDisplay.Display, fgDisplay.pDisplay.RootWindow, 0, evmask, &xev)) {
        return -1;
    }
    return 0;
}

static int fghToggleFullscreen(void)
{
    /* first try the EWMH (_NET_WM_STATE) method ... */
    if(fghEwmhFullscrToggle() != -1) {
        return 0;
    }

    /* fall back to resizing the window */
    if(fghResizeFullscrToggle() != -1) {
        return 0;
    }
    return -1;
}

static Bool fghWindowIsVisible( Display *display, XEvent *event, XPointer arg)
{
    Window window = (Window)arg;
    return (event->type == MapNotify) && (event->xmap.window == window);
}

/*
 * Opens a window. Requires a SFG_Window object created and attached
 * to the freeglut structure. OpenGL context is created here.
 */
void fgPlatformOpenWindow( SFG_Window* window, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow )
{
	Display *dpy = fgDisplay.pDisplay.Display;
	Window rootwin = fgDisplay.pDisplay.RootWindow;
	Window parent = window->Parent ? window->Parent->Window.Handle : 0;
	Window win;
	Colormap cmap;
	XVisualInfo * visualInfo = NULL;
	XSetWindowAttributes wattr;
	XSizeHints sizeHints;
	XWMHints wmHints;
	XEvent eventReturnBuffer; /* return buffer required for a call */
	unsigned long mask;
	unsigned int current_DisplayMode = fgState.DisplayMode;
	XEvent fakeEvent = {0};
	Atom xa_motif_wm_hints = XInternAtom(dpy, "_MOTIF_WM_HINTS", False);

#ifdef EGL_VERSION_1_0
	EGLint vid = 0;
	XVisualInfo visualTemplate;
	int num_visuals;
#endif

	/* Save the display mode if we are creating a menu window */
	if(window->IsMenu && !fgStructure.MenuContext) {
		fgState.DisplayMode = GLUT_DOUBLE | GLUT_RGB;
	}

#ifdef EGL_VERSION_1_0
#define WINDOW_CONFIG window->Window.pContext.egl.Config
#else
#ifdef USE_FBCONFIG
#define WINDOW_CONFIG window->Window.pContext.FBConfig
#else
#define WINDOW_CONFIG window->Window.pContext.visinf
#endif  /* !def USE_FBCONFIG */
#endif
	fghChooseConfig(&WINDOW_CONFIG);

	if(window->IsMenu && !fgStructure.MenuContext) {
		fgState.DisplayMode = current_DisplayMode;
	}

	if(!WINDOW_CONFIG) {
		/*
		 * The "fghChooseConfig" returned a null meaning that the visual
		 * context is not available.
		 * Try a couple of variations to see if they will work.
		 */
#ifndef EGL_VERSION_1_0
		if(!(fgState.DisplayMode & GLUT_DOUBLE)) {
			fgState.DisplayMode |= GLUT_DOUBLE;
			fghChooseConfig(&WINDOW_CONFIG);
			fgState.DisplayMode &= ~GLUT_DOUBLE;

			if(WINDOW_CONFIG) goto done_retry;
		}
#endif

		if(fgState.DisplayMode & GLUT_MULTISAMPLE) {
			fgState.DisplayMode &= ~GLUT_MULTISAMPLE;
			fghChooseConfig(&WINDOW_CONFIG);
			fgState.DisplayMode |= GLUT_MULTISAMPLE;

			if(WINDOW_CONFIG) goto done_retry;
		}

		if(fgState.DisplayMode & GLUT_SRGB) {
			fgState.DisplayMode &= ~GLUT_SRGB;
			fghChooseConfig(&WINDOW_CONFIG);
			fgState.DisplayMode |= GLUT_SRGB;

			if(WINDOW_CONFIG) goto done_retry;
		}
	}
done_retry:

#ifdef USE_FBCONFIG
	FREEGLUT_INTERNAL_ERROR_EXIT(WINDOW_CONFIG != NULL,
			"FBConfig with necessary capabilities not found", "fgOpenWindow");
#else
	FREEGLUT_INTERNAL_ERROR_EXIT(WINDOW_CONFIG != NULL,
			"GLX Visual with necessary capabilities not found", "fgOpenWindow");
#endif

	/*  Get the X visual.  */
#ifdef EGL_VERSION_1_0
	if(!eglGetConfigAttrib(fgDisplay.pDisplay.egl.Display, window->Window.pContext.egl.Config, EGL_NATIVE_VISUAL_ID, &vid)) {
		fgError("eglGetConfigAttrib(EGL_NATIVE_VISUAL_ID) failed");
	}
	visualTemplate.visualid = vid;
	visualInfo = XGetVisualInfo(dpy, VisualIDMask, &visualTemplate, &num_visuals);
#else
#ifdef USE_FBCONFIG
	visualInfo = glXGetVisualFromFBConfig(dpy, window->Window.pContext.FBConfig);

	FREEGLUT_INTERNAL_ERROR_EXIT( visualInfo != NULL,
			"visualInfo could not be retrieved from FBConfig", "fgOpenWindow");
#else
	visualInfo = window->Window.pContext.visinf;
#endif  /* !def USE_FBCONFIG */
#endif  /* GLX part */

	if(fgState.DisplayMode & GLUT_INDEX) {
		cmap = XCreateColormap(dpy, rootwin, visualInfo->visual, AllocAll);
		FREEGLUT_INTERNAL_ERROR_EXIT(cmap,
				"Failed to allocate the whole colormap, which is required in index color mode", "fgOpenWindow");
		window->Window.cmap_size = visualInfo->colormap_size;
	} else {
		cmap = XCreateColormap(dpy, rootwin, visualInfo->visual, AllocNone);
		window->Window.cmap_size = 0;
	}
	window->Window.cmap = cmap;

	/*
	 * XXX HINT: the masks should be updated when adding/removing callbacks.
	 * XXX       This might speed up message processing. Is that true?
	 * XXX
	 * XXX A: Not appreciably, but it WILL make it easier to debug.
	 * XXX    Try tracing old GLUT and try tracing freeglut.  Old GLUT
	 * XXX    turns off events that it doesn't need and is a whole lot
	 * XXX    more pleasant to trace.  (Think mouse-motion!  Tons of
	 * XXX    ``bonus'' GUI events stream in.)
	 *
	 * TODO: we absolutely need to fix this. In network rendering, flooding the
	 *       wire with unnecessary mouse motion events is Bad. At the very least
	 *       make the PointerMotionMask dynamic.
	 */
	wattr.event_mask =
		StructureNotifyMask | SubstructureNotifyMask | ExposureMask |
		ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
		VisibilityChangeMask | EnterWindowMask | LeaveWindowMask |
		PointerMotionMask | ButtonMotionMask;
	wattr.background_pixmap = None;
	wattr.background_pixel  = 0;
	wattr.border_pixel      = 0;
	wattr.colormap = cmap;

	mask = CWBackPixmap | CWBorderPixel | CWColormap | CWEventMask;

	if(window->IsMenu || gameMode) {
		wattr.override_redirect = True;
		mask |= CWOverrideRedirect;
	}

	if(!positionUse)
		x = y = -1; /* default window position */
	if(!sizeUse)
		w = h = 300; /* default window size */

	win = XCreateWindow(dpy, parent ? parent : rootwin, x, y, w, h, 0,
			visualInfo->depth, InputOutput, visualInfo->visual, mask, &wattr);
	window->Window.Handle = win;

	/* Fake configure event to force viewport setup
	 * even with no window manager.
	 */
	fakeEvent.xconfigure.type = ConfigureNotify;
	fakeEvent.xconfigure.display = dpy;
	fakeEvent.xconfigure.window = win;
	fakeEvent.xconfigure.x = x;
	fakeEvent.xconfigure.y = y;
	fakeEvent.xconfigure.width = w;
	fakeEvent.xconfigure.height = h;
	XPutBackEvent(dpy, &fakeEvent);

	/*
	 * The GLX context creation, possibly trying the direct context rendering
	 *  or else use the current context if the user has so specified
	 */
	if(window->IsMenu) {
		/*
		 * If there isn't already an OpenGL rendering context for menu
		 * windows, make one
		 */
		if(!fgStructure.MenuContext) {
			fgStructure.MenuContext = malloc(sizeof *fgStructure.MenuContext);
			fgStructure.MenuContext->MContext = fghCreateNewContext(window);
		}

		/* window->Window.Context = fgStructure.MenuContext->MContext; */
		window->Window.Context = fghCreateNewContext(window);

	} else if(fgState.UseCurrentContext) {
#ifdef EGL_VERSION_1_0
		window->Window.Context = eglGetCurrentContext();
#else
		window->Window.Context = glXGetCurrentContext();
#endif

		if(!window->Window.Context) {
			window->Window.Context = fghCreateNewContext(window);
		}
	} else {
		window->Window.Context = fghCreateNewContext(window);
	}

#if !defined( __FreeBSD__ ) && !defined( __NetBSD__ ) && !defined(EGL_VERSION_1_0)
	if(!glXIsDirect(dpy, window->Window.Context)) {
		if(fgState.DirectContext == GLUT_FORCE_DIRECT_CONTEXT) {
			fgError("Unable to force direct context rendering for window '%s'", title);
		}
	}
#endif

	sizeHints.flags = 0;
	if(positionUse)
		sizeHints.flags |= USPosition;
	if(sizeUse)
		sizeHints.flags |= USSize;

	/*
	 * Fill in the size hints values now (the x, y, width and height
	 * settings are obsolete, are there any more WMs that support them?)
	 * Unless the X servers actually stop supporting these, we should
	 * continue to fill them in.  It is *not* our place to tell the user
	 * that they should replace a window manager that they like, and which
	 * works, just because *we* think that it's not "modern" enough.
	 */
	sizeHints.x      = x;
	sizeHints.y      = y;
	sizeHints.width  = w;
	sizeHints.height = h;

	wmHints.flags = StateHint;
	wmHints.initial_state = fgState.ForceIconic ? IconicState : NormalState;
	XSetWMProperties(dpy, win, 0, 0, 0, 0, &sizeHints, &wmHints, 0);

	set_title(win, XA_WM_NAME, title);
	set_title(win, XA_WM_ICON_NAME, title);
#ifdef X_HAVE_UTF8_STRING
	set_utf8_title(win, fgDisplay.pDisplay.NetWMName, title);
	set_utf8_title(win, fgDisplay.pDisplay.NetWMIconName, title);
#endif

	XSetWMProtocols(dpy, win, &fgDisplay.pDisplay.DeleteWindow, 1);

	if (!isSubWindow && !window->IsMenu &&
			((fgState.DisplayMode & GLUT_BORDERLESS) || (fgState.DisplayMode & GLUT_CAPTIONLESS)))
	{
		/* _MOTIF_WM_HINTS is replaced by _NET_WM_WINDOW_TYPE, but that property does not allow precise
		 * control over the visual style of the window, which is what we are trying to achieve here.
		 * Stick with Motif and hope for the best... */
		MotifWmHints hints = {0};
		hints.flags = MWM_HINTS_DECORATIONS;
		hints.decorations = (fgState.DisplayMode & GLUT_CAPTIONLESS) ? MWM_DECOR_BORDER:0;

		XChangeProperty(dpy, win, xa_motif_wm_hints, xa_motif_wm_hints, 32, PropModeReplace,
				(unsigned char*)&hints, sizeof(MotifWmHints) / sizeof(long));
	}


	if (fgDisplay.pDisplay.NetWMSupported
			&& fgDisplay.pDisplay.NetWMPid != None
			&& fgDisplay.pDisplay.ClientMachine != None)
	{
		char hostname[HOST_NAME_MAX];
		pid_t pid = getpid();

		if (pid > 0 && gethostname(hostname, sizeof(hostname)) > -1)
		{
			hostname[sizeof(hostname) - 1] = '\0';

			XChangeProperty(dpy, win, fgDisplay.pDisplay.NetWMPid, XA_CARDINAL, 32,
					PropModeReplace, (unsigned char*)&pid, 1);

			XChangeProperty(dpy, win, fgDisplay.pDisplay.ClientMachine, XA_STRING, 8,
					PropModeReplace, (unsigned char*)hostname, strlen(hostname));
		}
	}

#ifdef EGL_VERSION_1_0
	fghPlatformOpenWindowEGL(window);
#elif defined(GLX_VERSION_1_3)
	glXMakeContextCurrent(dpy, win, win, window->Window.Context);
#else
	glXMakeCurrent(dpy, win, window->Window.Context);
#endif

	/* register extension events _before_ window is mapped */
#ifdef HAVE_X11_EXTENSIONS_XINPUT2_H
	fgRegisterDevices(dpy, win);
#endif

	if(!window->IsMenu) {   /* Don't show window after creation if its a menu */
		XMapWindow(dpy, win);
		window->State.Visible = GL_TRUE;
	}

#ifdef USE_FBCONFIG
	/* on the non-fbconfig path, the visualInfo pointer is the one owned by the
	 * window, so delete only if we got this from glXGetVisualFromFBConfig
	 */
	XFree(visualInfo);
#endif

	/* wait till window visible */
	if(!isSubWindow && !window->IsMenu) {
		XPeekIfEvent(dpy, &eventReturnBuffer, &fghWindowIsVisible, (XPointer)window->Window.Handle);
	}
#undef WINDOW_CONFIG
}


/*
 * Request a window resize
 */
void fgPlatformReshapeWindow ( SFG_Window *window, int width, int height )
{
    XResizeWindow( fgDisplay.pDisplay.Display, window->Window.Handle,
                   width, height );
    XFlush( fgDisplay.pDisplay.Display ); /* XXX Shouldn't need this */
}


/*
 * Closes a window, destroying the frame and OpenGL context
 */
void fgPlatformCloseWindow( SFG_Window* window )
{
#ifdef EGL_VERSION_1_0
    fghPlatformCloseWindowEGL(window);
#else
    if( window->Window.Context )
        glXDestroyContext( fgDisplay.pDisplay.Display, window->Window.Context );
#ifdef USE_FBCONFIG
    window->Window.pContext.FBConfig = NULL;
#else
    XFree(window->Window.pContext.visinf);
    window->Window.pContext.visinf = NULL;
#endif  /* !def USE_FBCONFIG */
#endif  /* GLX part */

    if( window->Window.Handle ) {
        XDestroyWindow( fgDisplay.pDisplay.Display, window->Window.Handle );
    }
    /* XFlush( fgDisplay.pDisplay.Display ); */ /* XXX Shouldn't need this */
}


/*
 * This function makes the specified window visible
 */
void fgPlatformShowWindow( SFG_Window *window )
{
    XMapWindow( fgDisplay.pDisplay.Display, window->Window.Handle );
    XFlush( fgDisplay.pDisplay.Display ); /* XXX Shouldn't need this */
}

/*
 * This function hides the specified window
 */
void fgPlatformHideWindow( SFG_Window *window )
{
    if( window->Parent == NULL )
        XWithdrawWindow( fgDisplay.pDisplay.Display,
                         window->Window.Handle,
                         fgDisplay.pDisplay.Screen );
    else
        XUnmapWindow( fgDisplay.pDisplay.Display,
                      window->Window.Handle );
    XFlush( fgDisplay.pDisplay.Display ); /* XXX Shouldn't need this */
}

/*
 * Iconify the specified window (top-level windows only)
 */
void fgPlatformIconifyWindow( SFG_Window *window )
{
    XIconifyWindow( fgDisplay.pDisplay.Display, window->Window.Handle,
                    fgDisplay.pDisplay.Screen );
    XFlush( fgDisplay.pDisplay.Display ); /* XXX Shouldn't need this */

    fgStructure.CurrentWindow->State.Visible   = GL_FALSE;
}

/* NOTE: about UTF8 in window titles or icon names.
 *
 * By the letter of the ICCCM and EHWM specifications, if we wish to set a UTF8
 * (non-ASCII) name, it should go to _NET_WM_NAME or _NET_WM_ICON_NAME tagged as
 * UTF8_STRING type, instead of the older WM_NAME/WM_ICON_NAME properties which
 * should be of type STRING.
 *
 * But in case we don't have the Xlib utf8 extensions, or in any case for the
 * sake of compatibility with old window managers, it's best to always set
 * WM_NAME/WM_ICON_NAME, regardless of the actual encoding. Modern EWMH-compliant
 * window managers should ignore WM_NAME if _NET_WM_NAME is also set anyway,
 * and older window managers can still hope to show something semi-reasonable
 * in the title-bar (some WMs can cope with utf8 strings mislabeled as STRING in
 * WM_NAME just fine anyway).
 *
 * So we'll set the old ICCCM properties unconditionally, and if we can, we'll
 * also set the EHWM ones, and hope for the best.
 *
 * See git commit d3799755874dfae53540caf75003dfed68738720 for an earlier
 * attempt to detect and set only one or the other.
 */

#ifdef X_HAVE_UTF8_STRING
/* sets utf8 window title (_NET_WM_NAME or _NET_WM_ICON_NAME) */
static int set_utf8_title(Window win, Atom prop, const char *str)
{
	Display *dpy = fgDisplay.pDisplay.Display;
	XTextProperty text;

	if(!prop) return -1;

	if(Xutf8TextListToTextProperty(dpy, (char**)&str, 1, XUTF8StringStyle, &text) < 0) {
		return -1;
	}
	XChangeProperty(dpy, win, prop, text.encoding, 8, PropModeReplace,
			(unsigned char*)str, strlen(str));
	XFree(text.value);
	return 0;
}
#endif	/* X_HAVE_UTF8_STRING */

/* sets WM_NAME and/or WM_ICON_NAME (type STRING) */
static void set_title(Window win, Atom prop, const char *str)
{
	Display *dpy = fgDisplay.pDisplay.Display;
	XTextProperty text;

	text.value = (unsigned char*)str;
	text.encoding = XA_STRING;
	text.format = 8;
	text.nitems = strlen(str);

	if(prop == XA_WM_NAME) {
		XSetWMName(dpy, win, &text);
	} else if(prop == XA_WM_ICON_NAME) {
		XSetWMIconName(dpy, win, &text);
	}
}

/* Set the current window's title */
void fgPlatformGlutSetWindowTitle(const char *str)
{
	Window win = fgStructure.CurrentWindow->Window.Handle;
	if(!str || !*str) return;

	set_title(win, XA_WM_NAME, str);
#ifdef X_HAVE_UTF8_STRING
	if(set_utf8_title(win, fgDisplay.pDisplay.NetWMName, str) == -1) {
		/* if we failed to set _NET_WM_NAME because it's not a valid utf8 string
		 * then we should remove the property in case it was set before, so that
		 * WM_NAME will be used, otherwise _NET_WM_NAME takes precedence
		 */
		Display *dpy = fgDisplay.pDisplay.Display;
		XDeleteProperty(dpy, win, fgDisplay.pDisplay.NetWMName);
	}
#endif
}

/*
 * Set the current window's iconified title
 */
void fgPlatformGlutSetIconTitle(const char *str)
{
	Window win = fgStructure.CurrentWindow->Window.Handle;
	if(!str || !*str) return;

	set_title(win, XA_WM_ICON_NAME, str);
#ifdef X_HAVE_UTF8_STRING
	if(set_utf8_title(win, fgDisplay.pDisplay.NetWMIconName, str) == -1) {
		/* see fgPlatformGlutSetWindowTitle above */
		Display *dpy = fgDisplay.pDisplay.Display;
		XDeleteProperty(dpy, win, fgDisplay.pDisplay.NetWMIconName);
	}
#endif
}

/*
 * Change the specified window's position
 */
void fgPlatformPositionWindow( SFG_Window *window, int x, int y )
{
    XMoveWindow( fgDisplay.pDisplay.Display, window->Window.Handle,
                 x, y );
    XFlush( fgDisplay.pDisplay.Display ); /* XXX Shouldn't need this */
}

/*
 * Lowers the specified window (by Z order change)
 */
void fgPlatformPushWindow( SFG_Window *window )
{
    XLowerWindow( fgDisplay.pDisplay.Display, window->Window.Handle );
}

/*
 * Raises the specified window (by Z order change)
 */
void fgPlatformPopWindow( SFG_Window *window )
{
    XRaiseWindow( fgDisplay.pDisplay.Display, window->Window.Handle );
}

/*
 * Toggle the window's full screen state.
 */
void fgPlatformFullScreenToggle( SFG_Window *win )
{
    if(fghToggleFullscreen() != -1) {
        win->State.IsFullscreen = !win->State.IsFullscreen;
    }
}

