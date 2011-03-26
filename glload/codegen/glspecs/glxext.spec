# glxext.spec file
# DON'T REMOVE PREVIOUS LINE!!! libspec depends on it!
#
# Copyright (c) 1991-2005 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2010 The Khronos Group, Inc.
#
# This document is licensed under the SGI Free Software B License Version
# 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
#
# $Revision: 12183 $ on $Date: 2010-08-06 02:53:05 -0700 (Fri, 06 Aug 2010) $

required-props:
param:		retval retained
glxflags:	client-handcode client-intercept server-handcode
glxvendorglx:	*
vectorequiv:	*
category:	VERSION_1_3 VERSION_1_4 ARB_get_proc_address ARB_multisample ARB_fbconfig_float EXT_import_context SGIX_dmbuffer SGIX_fbconfig SGIX_pbuffer SGIX_swap_barrier SGIX_swap_group SGIX_video_resize SGIX_video_source SGI_cushion SGI_make_current_read SGI_swap_control SGI_video_sync SUN_get_transparent_index MESA_agp_offset MESA_copy_sub_buffer MESA_pixmap_colormap MESA_release_buffers MESA_set_3dfx_mode SGIX_visual_select_group OML_sync_control SGIX_hyperpipe EXT_texture_from_pixmap NV_swap_group NV_video_output NV_present_video ARB_create_context NV_video_capture NV_copy_image EXT_swap_control ARB_framebuffer_sRGB
glxopcode:	*

#
# Boilerplate to define types used by some extensions. This is done
#   up front, since it involves some complexities in protecting
#   the declarations whether or not the -protect flag is given to
#   the generator scripts.
#

passthru: #ifndef GLX_ARB_get_proc_address
passthru: typedef void (*__GLXextFuncPtr)(void);
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_video_source
passthru: typedef XID GLXVideoSourceSGIX;
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_fbconfig
passthru: typedef XID GLXFBConfigIDSGIX;
passthru: typedef struct __GLXFBConfigRec *GLXFBConfigSGIX;
passthru: #endif
passthru:
passthru: #ifndef GLX_SGIX_pbuffer
passthru: typedef XID GLXPbufferSGIX;
passthru: typedef struct {
passthru:     int type;
passthru:     unsigned long serial;	  /* # of last request processed by server */
passthru:     Bool send_event;		  /* true if this came for SendEvent request */
passthru:     Display *display;		  /* display the event was read from */
passthru:     GLXDrawable drawable;	  /* i.d. of Drawable */
passthru:     int event_type;		  /* GLX_DAMAGED_SGIX or GLX_SAVED_SGIX */
passthru:     int draw_type;		  /* GLX_WINDOW_SGIX or GLX_PBUFFER_SGIX */
passthru:     unsigned int mask;	  /* mask indicating which buffers are affected*/
passthru:     int x, y;
passthru:     int width, height;
passthru:     int count;		  /* if nonzero, at least this many more */
passthru: } GLXBufferClobberEventSGIX;
passthru: #endif
passthru:
passthru: #ifndef GLX_NV_video_output
passthru: typedef unsigned int GLXVideoDeviceNV;
passthru: #endif
passthru:
passthru: #ifndef GLX_NV_video_capture
passthru: typedef XID GLXVideoCaptureDeviceNV;
passthru: #endif
passthru:
passthru: #ifndef GLEXT_64_TYPES_DEFINED
passthru: /* This code block is duplicated in glext.h, so must be protected */
passthru: #define GLEXT_64_TYPES_DEFINED
passthru: /* Define int32_t, int64_t, and uint64_t types for UST/MSC */
passthru: /* (as used in the GLX_OML_sync_control extension). */
passthru: #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
passthru: #include <inttypes.h>
passthru: #elif defined(__sun__) || defined(__digital__)
passthru: #include <inttypes.h>
passthru: #if defined(__STDC__)
passthru: #if defined(__arch64__) || defined(_LP64)
passthru: typedef long int int64_t;
passthru: typedef unsigned long int uint64_t;
passthru: #else
passthru: typedef long long int int64_t;
passthru: typedef unsigned long long int uint64_t;
passthru: #endif /* __arch64__ */
passthru: #endif /* __STDC__ */
passthru: #elif defined( __VMS ) || defined(__sgi)
passthru: #include <inttypes.h>
passthru: #elif defined(__SCO__) || defined(__USLC__)
passthru: #include <stdint.h>
passthru: #elif defined(__UNIXOS2__) || defined(__SOL64__)
passthru: typedef long int int32_t;
passthru: typedef long long int int64_t;
passthru: typedef unsigned long long int uint64_t;
passthru: #elif defined(_WIN32) && defined(__GNUC__)
passthru: #include <stdint.h>
passthru: #elif defined(_WIN32)
passthru: typedef __int32 int32_t;
passthru: typedef __int64 int64_t;
passthru: typedef unsigned __int64 uint64_t;
passthru: #else
passthru: #include <inttypes.h>     /* Fallback option */
passthru: #endif
passthru: #endif
passthru:

###############################################################################
#
# GLX 1.3 commands
#
###############################################################################

GetFBConfigs(dpy, screen, nelements)
	return		GLXFBConfigPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		nelements	int out reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	21

ChooseFBConfig(dpy, screen, attrib_list, nelements)
	return		GLXFBConfigPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		attrib_list	int in reference
	param		nelements	int out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetFBConfigAttrib(dpy, config, attribute, value)
	return		int
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		attribute	int in value
	param		value		int out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetVisualFromFBConfig(dpy, config)
	return		XVisualInfoPointer
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

CreateWindow(dpy, config, win, attrib_list)
	return		GLXWindow
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		win		Window in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	31

DestroyWindow(dpy, win)
	return		void
	param		dpy		Display out reference
	param		win		GLXWindow in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	32

CreatePixmap(dpy, config, pixmap, attrib_list)
	return		GLXPixmap
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		pixmap		Pixmap in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	22

DestroyPixmap(dpy, pixmap)
	return		void
	param		dpy		Display out reference
	param		pixmap		GLXPixmap in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	23

CreatePbuffer(dpy, config, attrib_list)
	return		GLXPbuffer
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		attrib_list	int in reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	27

DestroyPbuffer(dpy, pbuf)
	return		void
	param		dpy		Display out reference
	param		pbuf		GLXPbuffer in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	28

# glXGetDrawableAttributes -> GLX opcode 29
# glXChangeDrawableAttributes -> GLX opcode 30

# Uses glXGetDrawableAttributes protocol
QueryDrawable(dpy, draw, attribute, value)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		attribute	int in value
	param		value		uint out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

CreateNewContext(dpy, config, render_type, share_list, direct)
	return		GLXContext
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		render_type	int in value
	param		share_list	GLXContext in value
	param		direct		Bool in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	24

MakeContextCurrent(dpy, draw, read, ctx)
	return		Bool
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		read		GLXDrawable in value
	param		ctx		GLXContext in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	26

GetCurrentReadDrawable()
	return		GLXDrawable
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

GetCurrentDisplay()
	return		DisplayPointer
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

QueryContext(dpy, ctx, attribute, value)
	return		int
	param		dpy		Display out reference
	param		ctx		GLXContext in value
	param		attribute	int in value
	param		value		int out reference
	category	VERSION_1_3
	glxflags	client-handcode server-handcode
	glxopcode	25

# Uses glXChangeDrawableAttributes protocol
SelectEvent(dpy, draw, event_mask)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		event_mask	ulong in value
	category	VERSION_1_3
	glxflags	client-handcode server-handcode

# Uses glXGetDrawableAttributes protocol
GetSelectedEvent(dpy, draw, event_mask)
	return		void
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		event_mask	ulong out reference
	category	VERSION_1_3
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# GLX 1.4 commands
#
###############################################################################

GetProcAddress(procName)
	return		FunctionPointer
	param		procName	GLubyte in reference
	category	VERSION_1_4
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# ARB Extension #2
# ARB_get_proc_address commands
# @promoted to core in GLX 1.4, but there's no provision for aliasing
# @in GLX spec files, yet
#
###############################################################################

GetProcAddressARB(procName)
	return		FunctionPointer
	param		procName	GLubyte in reference
	category	ARB_get_proc_address
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# ARB Extension #5
# ARB_multisample commands
#
###############################################################################

# (none)
newcategory: ARB_multisample

###############################################################################
#
# ARB Extension #39
# ARB_fbconfig_float commands
#
###############################################################################

# (none)
newcategory: ARB_fbconfig_float

###############################################################################
#
# ARB Extension #46
# ARB_framebuffer_sRGB commands
#
###############################################################################

# (none)
newcategory: ARB_framebuffer_sRGB

###############################################################################
#
# ARB Extension #56
# ARB_create_context commands
#
###############################################################################

CreateContextAttribsARB(dpy, config, share_context, direct, attrib_list)
	return		GLXContext
	param		dpy		Display out reference
	param		config		GLXFBConfig in value
	param		share_context	GLXContext in value
	param		direct		Bool in value
	param		attrib_list	int in reference
	category	ARB_create_context
	glxflags	client-handcode client-intercept server-handcode
	glxopcode	34

###############################################################################
#
# ARB Extension #75
# ARB_create_context_profile commands
#
###############################################################################

# (none)
newcategory: ARB_create_context_profile

###############################################################################
#
# ARB Extension #101
# ARB_create_context_robustness commands
#
###############################################################################

# (none)
newcategory: ARB_create_context_robustness


###############################################################################
#
# Extension #25
# SGIS_multisample commands
#
###############################################################################

# (none)
newcategory: SGIS_multisample

###############################################################################
#
# Extension #28
# EXT_visual_info commands
#
###############################################################################

# (none)
newcategory: EXT_visual_info

###############################################################################
#
# Extension #40
# SGI_swap_control commands
#
###############################################################################

SwapIntervalSGI(interval)
	return		int
	param		interval	int in value
	category	SGI_swap_control
	glxflags	client-handcode server-handcode
	glxvendorglx	65536

###############################################################################
#
# Extension #41
# SGI_video_sync commands
#
###############################################################################

GetVideoSyncSGI(count)
	return		int
	param		count		uint out reference
	category	SGI_video_sync
	glxflags	client-handcode client-intercept server-handcode

WaitVideoSyncSGI(divisor, remainder, count)
	return		int
	param		divisor		int in value
	param		remainder	int in value
	param		count		uint out reference
	category	SGI_video_sync
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #42
# SGI_make_current_read commands
#
###############################################################################

MakeCurrentReadSGI(dpy, draw, read, ctx)
	return		Bool
	param		dpy		Display out reference
	param		draw		GLXDrawable in value
	param		read		GLXDrawable in value
	param		ctx		GLXContext in value
	category	SGI_make_current_read
	glxflags	client-handcode server-handcode
	glxvendorglx	65537

GetCurrentReadDrawableSGI()
	return		GLXDrawable
	category	SGI_make_current_read
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #43
# SGIX_video_source commands
#
###############################################################################

newcategory: SGIX_video_source
passthru: #ifdef _VL_H

CreateGLXVideoSourceSGIX(display, screen, server, path, nodeClass, drainNode)
	return		GLXVideoSourceSGIX
	param		display		Display out reference
	param		screen		int in value
	param		server		VLServer in value
	param		path		VLPath in value
	param		nodeClass	int in value
	param		drainNode	VLNode in value
	category	SGIX_video_source
	glxflags	client-handcode server-handcode
	glxvendorglx	65538

DestroyGLXVideoSourceSGIX(dpy, glxvideosource)
	return		void
	param		dpy		Display out reference
	param		glxvideosource	GLXVideoSourceSGIX in value
	category	SGIX_video_source
	glxflags	client-handcode server-handcode
	glxvendorglx	65539

passend: #endif /* _VL_H */
endcategory:

###############################################################################
#
# Extension #44
# EXT_visual_rating commands
#
###############################################################################

# (none)
newcategory: EXT_visual_rating

###############################################################################
#
# Extension #47
# EXT_import_context commands
#
###############################################################################

GetCurrentDisplayEXT()
	return		DisplayPointer
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

QueryContextInfoEXT(dpy, context, attribute, value)
	return		int
	param		dpy		Display out reference
	param		context		GLXContext in value
	param		attribute	int in value
	param		value		int out reference
	category	EXT_import_context
	glxflags	client-handcode server-handcode
	glxvendorglx	1024

# 'constGLXContext' is a hack; the extension specification and glx.h
# should be fixed instead.
GetContextIDEXT(context)
	return		GLXContextID
	param		context		constGLXContext in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

ImportContextEXT(dpy, contextID)
	return		GLXContext
	param		dpy		Display out reference
	param		contextID	GLXContextID in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

FreeContextEXT(dpy, context)
	return		void
	param		dpy		Display out reference
	param		context		GLXContext in value
	category	EXT_import_context
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #49
# SGIX_fbconfig commands
#
###############################################################################

# GetFBConfigsSGIX protocol -> VendorPrivate opcode 65540

GetFBConfigAttribSGIX(dpy, config, attribute, value)
	return		int
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		attribute	int in value
	param		value		int out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

ChooseFBConfigSGIX(dpy, screen, attrib_list, nelements)
	return		GLXFBConfigSGIXPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		attrib_list	int out reference
	param		nelements	int out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

CreateGLXPixmapWithConfigSGIX(dpy, config, pixmap)
	return		GLXPixmap
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		pixmap		Pixmap in value
	category	SGIX_fbconfig
	glxflags	client-handcode server-handcode
	glxvendorglx	65542

CreateContextWithConfigSGIX(dpy, config, render_type, share_list, direct)
	return		GLXContext
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		render_type	int in value
	param		share_list	GLXContext in value
	param		direct		Bool in value
	category	SGIX_fbconfig
	glxflags	client-handcode server-handcode
	glxvendorglx	65541

GetVisualFromFBConfigSGIX(dpy, config)
	return		XVisualInfoPointer
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

GetFBConfigFromVisualSGIX(dpy, vis)
	return		GLXFBConfigSGIX
	param		dpy		Display out reference
	param		vis		XVisualInfo out reference
	category	SGIX_fbconfig
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #50
# SGIX_pbuffer commands
#
###############################################################################

# ChangeDrawableAttributesSGIX protocol -> VendorPrivate opcode 65545
# GetDrawableAttributesSGIX protocol -> VendorPrivate opcode 65546

CreateGLXPbufferSGIX(dpy, config, width,  height, attrib_list)
	return		GLXPbufferSGIX
	param		dpy		Display out reference
	param		config		GLXFBConfigSGIX in value
	param		width		uint in value
	param		height		uint in value
	param		attrib_list	int out reference
	category	SGIX_pbuffer
	glxflags	client-handcode server-handcode
	glxvendorglx	65543

DestroyGLXPbufferSGIX(dpy, pbuf)
	return		void
	param		dpy		Display out reference
	param		pbuf		GLXPbufferSGIX in value
	category	SGIX_pbuffer
	glxflags	client-handcode
	glxvendorglx	65544

QueryGLXPbufferSGIX(dpy, pbuf, attribute, value)
	return		int
	param		dpy		Display out reference
	param		pbuf		GLXPbufferSGIX in value
	param		attribute	int in value
	param		value		uint out reference
	category	SGIX_pbuffer

SelectEventSGIX(dpy, drawable, mask)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		mask		ulong in value
	category	SGIX_pbuffer

GetSelectedEventSGIX(dpy, drawable, mask)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		mask		ulong out reference
	category	SGIX_pbuffer

###############################################################################
#
# Extension #62
# SGI_cushion commands
#
###############################################################################

CushionSGI(dpy, window, cushion)
	return		void
	param		dpy		Display out reference
	param		window		Window in value
	param		cushion		float in value
	category	SGI_cushion

###############################################################################
#
# Extension #83
# SGIX_video_resize commands
#
###############################################################################

BindChannelToWindowSGIX(display, screen, channel, window)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		window		Window in value
	category	SGIX_video_resize

ChannelRectSGIX(display, screen, channel, x, y, w, h)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		x		int in value
	param		y		int in value
	param		w		int in value
	param		h		int in value
	category	SGIX_video_resize

QueryChannelRectSGIX(display, screen, channel, dx, dy, dw, dh)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		dx		int out reference
	param		dy		int out reference
	param		dw		int out reference
	param		dh		int out reference
	category	SGIX_video_resize

QueryChannelDeltasSGIX(display, screen, channel, x, y, w, h)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		x		int out reference
	param		y		int out reference
	param		w		int out reference
	param		h		int out reference
	category	SGIX_video_resize

# @@@ Not in man page - this entry point may not be shipping?
ChannelRectSyncSGIX(display, screen, channel, synctype)
	return		int
	param		display		Display out reference
	param		screen		int in value
	param		channel		int in value
	param		synctype	GLenum in value
	category	SGIX_video_resize

###############################################################################
#
# Extension #86
# SGIX_dmbuffer commands
#
###############################################################################

newcategory: SGIX_dmbuffer
passthru: #ifdef _DM_BUFFER_H_

AssociateDMPbufferSGIX(dpy, pbuffer, params, dmbuffer)
	return		Bool
	param		dpy		Display out reference
	param		pbuffer		GLXPbufferSGIX in value
	param		params		DMparams out reference
	param		dmbuffer	DMbuffer in value
	category	SGIX_dmbuffer

passend: #endif /* _DM_BUFFER_H_ */
endcategory:

###############################################################################
#
# Extension #91
# SGIX_swap_group commands
#
###############################################################################

JoinSwapGroupSGIX(dpy, drawable, member)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		member		GLXDrawable in value
	category	SGIX_swap_group
	glxflags	client-handcode server-handcode
	glxvendorglx	65547

###############################################################################
#
# Extension #92
# SGIX_swap_barrier commands
#
###############################################################################

BindSwapBarrierSGIX(dpy, drawable, barrier)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		barrier		int in value
	category	SGIX_swap_barrier
	glxflags	client-handcode server-handcode
	glxvendorglx	65548

QueryMaxSwapBarriersSGIX(dpy, screen, max)
	return		Bool
	param		dpy		Display out reference
	param		screen		int in value
	param		max		int out reference
	category	SGIX_swap_barrier
	glxflags	client-handcode server-handcode
	glxvendorglx	65549

###############################################################################
#
# Extension #183
# SUN_get_transparent_index commands
#
###############################################################################

GetTransparentIndexSUN(dpy, overlay, underlay, pTransparentIndex)
	return		Status
	param		dpy		Display out reference
	param		overlay		Window in value
	param		underlay	Window in value
	param		pTransparentIndex	long out reference
	category	SUN_get_transparent_index

###############################################################################
#
# Extension #215
# MESA_copy_sub_buffer commands
#
###############################################################################

CopySubBufferMESA(dpy, drawable, x, y, width, height)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		x		int in value
	param		y		int in value
	param		width		int in value
	param		height		int in value
	category	MESA_copy_sub_buffer
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #216
# MESA_pixmap_colormap commands
#
###############################################################################

CreateGLXPixmapMESA(dpy, visual, pixmap, cmap)
	return		GLXPixmap
	param		dpy		Display out reference
	param		visual		XVisualInfo out reference
	param		pixmap		Pixmap in value
	param		cmap		Colormap in value
	category	MESA_pixmap_colormap
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #217
# MESA_release_buffers commands
#
###############################################################################

ReleaseBuffersMESA(dpy, drawable)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	category	MESA_release_buffers
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #218
# MESA_set_3dfx_mode commands
#
###############################################################################

# Brian's spec has this as returning 'GLboolean' and taking 'GLint mode'
Set3DfxModeMESA(mode)
	return		Bool
	param		mode		int in value
	category	MESA_set_3dfx_mode
	glxflags	client-handcode client-intercept server-handcode

###############################################################################
#
# Extension #234
# SGIX_visual_select_group commands
#
###############################################################################

# (none)
newcategory: SGIX_visual_select_group

###############################################################################
#
# Extension #237
# OML_swap_method commands
#
###############################################################################

# (none)
newcategory:  OML_swap_method

###############################################################################
#
# Extension #238
# OML_sync_control commands
#
###############################################################################

GetSyncValuesOML(dpy, drawable, ust, msc, sbc)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		ust		int64_t out reference
	param		msc		int64_t out reference
	param		sbc		int64_t out reference
	category	OML_sync_control
	glxflags	client-handcode server-handcode

GetMscRateOML(dpy, drawable, numerator, denominator)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		numerator	int32_t out reference
	param		denominator	int32_t out reference
	category	OML_sync_control
	glxflags	client-handcode server-handcode

SwapBuffersMscOML(dpy, drawable, target_msc, divisor, remainder)
	return		int64_t
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		target_msc	int64_t in value
	param		divisor		int64_t in value
	param		remainder	int64_t in value
	category	OML_sync_control
	glxflags	client-handcode server-handcode

WaitForMscOML(dpy, drawable, target_msc, divisor, remainder, ust, msc, sbc)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		target_msc	int64_t in value
	param		divisor		int64_t in value
	param		remainder	int64_t in value
	param		ust		int64_t out reference
	param		msc		int64_t out reference
	param		sbc		int64_t out reference
	category	OML_sync_control
	glxflags	client-handcode server-handcode

WaitForSbcOML(dpy, drawable, target_sbc, ust, msc, sbc)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		target_sbc	int64_t in value
	param		ust		int64_t out reference
	param		msc		int64_t out reference
	param		sbc		int64_t out reference
	category	OML_sync_control
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #281
# NV_float_buffer commands
#
###############################################################################

# (none)
newcategory: NV_float_buffer

###############################################################################
#
# Extension #307
# SGIX_hyperpipe commands
#
###############################################################################

newcategory: SGIX_hyperpipe
passthru:
passthru: typedef struct {
passthru:     char    pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
passthru:     int     networkId;
passthru: } GLXHyperpipeNetworkSGIX;
passthru:
passthru: typedef struct {
passthru:     char    pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
passthru:     int     channel;
passthru:     unsigned int
passthru:	      participationType;
passthru:     int     timeSlice;
passthru: } GLXHyperpipeConfigSGIX;
passthru:
passthru: typedef struct {
passthru:     char pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
passthru:     int srcXOrigin, srcYOrigin, srcWidth, srcHeight;
passthru:     int destXOrigin, destYOrigin, destWidth, destHeight;
passthru: } GLXPipeRect;
passthru:
passthru: typedef struct {
passthru:     char pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
passthru:     int XOrigin, YOrigin, maxHeight, maxWidth;
passthru: } GLXPipeRectLimits;
passthru:

QueryHyperpipeNetworkSGIX(dpy, npipes)
	return		GLXHyperpipeNetworkSGIXPointer
	param		dpy		Display out reference
	param		npipes		int out reference
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	65550

HyperpipeConfigSGIX(dpy, networkId, npipes, cfg, hpId)
	return		int
	param		dpy		Display out reference
	param		networkId	int in value
	param		npipes		int in value
	param		cfg		GLXHyperpipeConfigSGIX out array [COMPSIZE(npipes)]
	param		hpId		int out reference
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	65552

QueryHyperpipeConfigSGIX(dpy, hpId, npipes)
	return		GLXHyperpipeConfigSGIXPointer
	param		dpy		Display out reference
	param		hpId		int in value
	param		npipes		int out reference
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	65551

DestroyHyperpipeConfigSGIX(dpy, hpId)
	return		int
	param		dpy		Display out reference
	param		hpId		int in value
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	65553

BindHyperpipeSGIX(dpy, hpId)
	return		int
	param		dpy		Display out reference
	param		hpId		int in value
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	???

QueryHyperpipeBestAttribSGIX(dpy, timeSlice, attrib, size, attribList, returnAttribList)
	return		int
	param		dpy		Display out reference
	param		timeSlice	int in value
	param		attrib		int in value
	param		size		int in value
	param		attribList	void out array [COMPSIZE(size)]
	param		returnAttribList void out array [COMPSIZE(size)]
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	???

HyperpipeAttribSGIX(dpy, timeSlice, attrib, size, attribList)
	return		int
	param		dpy		Display out reference
	param		timeSlice	int in value
	param		attrib		int in value
	param		size		int in value
	param		attribList	void out array [COMPSIZE(size)]
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	???

QueryHyperpipeAttribSGIX(dpy, timeSlice, attrib, size, returnAttribList)
	return		int
	param		dpy		Display out reference
	param		timeSlice	int in value
	param		attrib		int in value
	param		size		int in value
	param		returnAttribList void out array [COMPSIZE(size)]
	glxflags	client-handcode server-handcode
	category	SGIX_hyperpipe
	glxvendorglx	???

###############################################################################
#
# Extension #308
# MESA_agp_offset commands
#
###############################################################################

GetAGPOffsetMESA(pointer)
	return		uint
	param		pointer		void in reference
	glxflags	client-handcode client-intercept server-handcode
	category	MESA_agp_offset

###############################################################################
#
# Extension #328
# EXT_fbconfig_packed_float commands
#
###############################################################################

# (none)
newcategory: EXT_fbconfig_packed_float

###############################################################################
#
# Extension #337
# EXT_framebuffer_sRGB commands
#
###############################################################################

# (none)
newcategory: EXT_framebuffer_sRGB

###############################################################################
#
# Extension #344
# EXT_texture_from_pixmap commands
#
###############################################################################

BindTexImageEXT(dpy, drawable, buffer, attrib_list)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		buffer		int in value
	param		attrib_list	int in reference
	category	EXT_texture_from_pixmap
	glxflags	client-handcode server-handcode
	glxvendorglx	1330

ReleaseTexImageEXT(dpy, drawable, buffer)
	return		void
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		buffer		int in value
	category	EXT_texture_from_pixmap
	glxflags	client-handcode server-handcode
	glxvendorglx	1331

###############################################################################
#
# Extension #347
# NV_present_video commands
#
###############################################################################

EnumerateVideoDevicesNV(dpy, screen, nelements)
	return		uintPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		nelements	int out reference
	category	NV_present_video
	glxflags	client-handcode server-handcode

BindVideoDeviceNV(dpy, video_slot, video_device, attrib_list)
	return		int
	param		dpy		Display out reference
	param		video_slot	uint in value
	param		video_device	uint in value
	param		attrib_list	int in reference
	category	NV_present_video
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #348
# NV_video_output commands
#
###############################################################################

GetVideoDeviceNV(dpy, screen, numVideoDevices, pVideoDevice)
	return		int
	param		dpy		Display out reference
	param		screen		int in value
	param		numVideoDevices int in value
	param		pVideoDevice	GLXVideoDeviceNV out array [COMPSIZE(numVideoDevices)]
	category	NV_video_output
	glxflags	client-handcode server-handcode

ReleaseVideoDeviceNV(dpy, screen, VideoDevice)
	return		int
	param		dpy		Display out reference
	param		screen		int in value
	param		VideoDevice	GLXVideoDeviceNV in value
	category	NV_video_output
	glxflags	client-handcode server-handcode

BindVideoImageNV(dpy, VideoDevice, pbuf, iVideoBuffer)
	return		int
	param		dpy		Display out reference
	param		VideoDevice	GLXVideoDeviceNV in value
	param		pbuf		GLXPbuffer in value
	param		iVideoBuffer	int in value
	category	NV_video_output
	glxflags	client-handcode server-handcode

ReleaseVideoImageNV(dpy, pbuf)
	return		int
	param		dpy		Display out reference
	param		pbuf		GLXPbuffer in value
	category	NV_video_output
	glxflags	client-handcode server-handcode

SendPbufferToVideoNV(dpy, pbuf, iBufferType, pulCounterPbuffer, bBlock)
	return		int
	param		dpy		Display out reference
	param		pbuf		GLXPbuffer in value
	param		iBufferType	int in value
	param		pulCounterPbuffer ulong out reference
	param		bBlock		GLboolean in value
	category	NV_video_output
	glxflags	client-handcode server-handcode

GetVideoInfoNV(dpy, screen, VideoDevice, pulCounterOutputPbuffer, pulCounterOutputVideo)
	return		int
	param		dpy		Display out reference
	param		screen		int in value
	param		VideoDevice	GLXVideoDeviceNV in value
	param		pulCounterOutputPbuffer ulong out reference
	param		pulCounterOutputVideo	ulong out reference
	category	NV_video_output
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #350
# NV_swap_group commands
#
###############################################################################

JoinSwapGroupNV(dpy, drawable, group)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		group		GLuint in value
	category	NV_swap_group
	glxflags	client-handcode server-handcode

BindSwapBarrierNV(dpy, group, barrier)
	return		Bool
	param		dpy		Display out reference
	param		group		GLuint in value
	param		barrier		GLuint in value
	category	NV_swap_group
	glxflags	client-handcode server-handcode

QuerySwapGroupNV(dpy, drawable, group, barrier)
	return		Bool
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		group		GLuint out reference
	param		barrier		GLuint out reference
	category	NV_swap_group
	glxflags	client-handcode server-handcode

QueryMaxSwapGroupsNV(dpy, screen, maxGroups, maxBarriers)
	return		Bool
	param		dpy		Display out reference
	param		screen		int in value
	param		maxGroups	GLuint out reference
	param		maxBarriers	GLuint out reference
	category	NV_swap_group
	glxflags	client-handcode server-handcode

QueryFrameCountNV(dpy, screen, count)
	return		Bool
	param		dpy		Display out reference
	param		screen		int in value
	param		count		GLuint out reference
	category	NV_swap_group
	glxflags	client-handcode server-handcode

ResetFrameCountNV(dpy, screen)
	return		Bool
	param		dpy		Display out reference
	param		screen		int in value
	category	NV_swap_group
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #374
# NV_video_capture commands
#
###############################################################################

BindVideoCaptureDeviceNV(dpy, video_capture_slot, device)
	return		int
	param		dpy		Display out reference
	param		video_capture_slot uint in value
	param		device		GLXVideoCaptureDeviceNV in value
	category	NV_video_capture
	glxflags	client-handcode server-handcode

EnumerateVideoCaptureDevicesNV(dpy, screen, nelements)
	return		GLXVideoCaptureDeviceNVPointer
	param		dpy		Display out reference
	param		screen		int in value
	param		nelements	int out reference
	category	NV_video_capture
	glxflags	client-handcode server-handcode

LockVideoCaptureDeviceNV(dpy, device)
	return		void
	param		dpy		Display out reference
	param		device		GLXVideoCaptureDeviceNV in value
	category	NV_video_capture
	glxflags	client-handcode server-handcode

QueryVideoCaptureDeviceNV(dpy, device, attribute, value)
	return		int
	param		dpy		Display out reference
	param		device		GLXVideoCaptureDeviceNV in value
	param		attribute	int in value
	param		value		int out array [COMPSIZE(attribute)]
	category	NV_video_capture
	glxflags	client-handcode server-handcode

ReleaseVideoCaptureDeviceNV(dpy, device)
	return		void
	param		dpy		Display out reference
	param		device		GLXVideoCaptureDeviceNV in value
	category	NV_video_capture
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #375
# EXT_swap_control commands
#
###############################################################################

SwapIntervalEXT(dpy, drawable, interval)
	return		int
	param		dpy		Display out reference
	param		drawable	GLXDrawable in value
	param		interval	int in value
	category	EXT_swap_control
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #376
# NV_copy_image commands
#
###############################################################################

CopyImageSubDataNV(dpy, srcCtx, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstCtx, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth)
	return		void
	param		dpy		Display out reference
	param		srcCtx		GLXContext in value
	param		srcName		GLuint in value
	param		srcTarget	GLenum in value
	param		srcLevel	GLint in value
	param		srcX		GLint in value
	param		srcY		GLint in value
	param		srcZ		GLint in value
	param		dstCtx		GLXContext in value
	param		dstName		GLuint in value
	param		dstTarget	GLenum in value
	param		dstLevel	GLint in value
	param		dstX		GLint in value
	param		dstY		GLint in value
	param		dstZ		GLint in value
	param		width		GLsizei in value
	param		height		GLsizei in value
	param		depth		GLsizei in value
	category	NV_copy_image
	glxflags	client-handcode server-handcode

###############################################################################
#
# Extension #384
# INTEL_swap_event commands
#
###############################################################################

# (none)
newcategory: INTEL_swap_event

###############################################################################
#
# Extension #393
# NV_multisample_coverage commands
#
###############################################################################

# (none)
newcategory: NV_multisample_coverage

###############################################################################
#
# Extension #399
# AMD_gpu_association commands
#
###############################################################################

# These are a weird mishmash of X and Windows types - are they correct?
# Leave out of glxext.h for the time being.

#@    UINT  glXGetGPUIDsAMD(UINT maxCount, UINT *ids);
#@    INT   glXGetGPUInfoAMD(UINT id, INT property, GLenum dataType,
#@			     UINT size, void *data)
#@    UINT  glXGetContextGPUIDAMD(GLXContext ctx);
#@    HGLRC glXCreateAssociatedContextAMD(UINT id, GLXContext share_list);
#@    HGLRC glXCreateAssociatedContextAttribsAMD(UINT id, GLXContext share_context,
#@						 const int *attribList);
#@    BOOL  glXDeleteAssociatedContextAMD(GLXContext ctx);
#@    BOOL  glXMakeAssociatedContextCurrentAMD(GLXContext ctx);
#@    HGLRC glXGetCurrentAssociatedContextAMD(void);
#@    VOID  glXBlitContextFramebufferAMD(GLXContext dstCtx, GLint srcX0, GLint srcY0,
#@					 GLint srcX1, GLint srcY1, GLint dstX0,
#@					 GLint dstY0, GLint dstX1, GLint dstY1,
#@					 GLbitfield mask, GLenum filter);

#@ glXGetGPUIDsAMD(maxCount, ids)
#@	   return	   UINT
#@	   param	   maxCount	   UINT in value
#@	   param	   ids		   UINT in array [???]
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXGetGPUInfoAMD(id, property, dataType, size, data)
#@	   return	   INT
#@	   param	   id		   UINT in value
#@	   param	   property	   INT in value
#@	   param	   dataType	   GLenum in value
#@	   param	   size		   UINT in value
#@	   param	   data		   void in array [???]
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXGetContextGPUIDAMD(ctx)
#@	   return	   UINT
#@	   param	   ctx		   GLXContext in value
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXCreateAssociatedContextAMD(id, share_list)
#@	   return	   HGLRC
#@	   param	   id		   UINT in value
#@	   param	   share_list	   GLXContext in value
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXCreateAssociatedContextAttribsAMD(id, share_context, attribList)
#@	   return	   HGLRC
#@	   param	   id		   UINT in value
#@	   param	   share_context   GLXContext in value
#@	   param	   attribList	   Int32 in array [???]
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXDeleteAssociatedContextAMD(ctx)
#@	   return	   BOOL
#@	   param	   ctx		   GLXContext in value
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXMakeAssociatedContextCurrentAMD(ctx)
#@	   return	   BOOL
#@	   param	   ctx		   GLXContext in value
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXGetCurrentAssociatedContextAMD()
#@	   return	   HGLRC
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
#@
#@ glXBlitContextFramebufferAMD(dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)
#@	   return	   VOID
#@	   param	   dstCtx	   GLXContext in value
#@	   param	   srcX0	   GLint in value
#@	   param	   srcY0	   GLint in value
#@	   param	   srcX1	   GLint in value
#@	   param	   srcY1	   GLint in value
#@	   param	   dstX0	   GLint in value
#@	   param	   dstY0	   GLint in value
#@	   param	   dstX1	   GLint in value
#@	   param	   dstY1	   GLint in value
#@	   param	   mask		   GLbitfield in value
#@	   param	   filter	   GLenum in value
#@	   category	   AMD_gpu_association
#@	   version	   4.1
#@	   extension
#@	   glxropcode	   ?
#@	   glxflags	   ignore
#@	   offset	   ?
