# wglext.spec file
# DON'T REMOVE PREVIOUS LINE!!! libspec depends on it!
#
# Copyright (c) 1991-2002 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2010 The Khronos Group, Inc.
#
# This document is licensed under the SGI Free Software B License Version
# 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
#
# $Revision: 12183 $ on $Date: 2010-08-06 02:53:05 -0700 (Fri, 06 Aug 2010) $

required-props:
param:		retval retained
category:	wgl ARB_buffer_region ARB_extensions_string ARB_pixel_format ARB_make_current_read ARB_pbuffer ARB_render_texture ARB_pixel_format_float EXT_display_color_table EXT_extensions_string EXT_make_current_read EXT_pbuffer EXT_pixel_format EXT_swap_control OML_sync_control I3D_digital_video_control I3D_gamma I3D_genlock I3D_image_buffer I3D_swap_frame_lock I3D_swap_frame_usage NV_vertex_array_range 3DL_stereo_control NV_swap_group NV_video_output NV_present_video ARB_create_context NV_gpu_affinity AMD_gpu_association NV_video_capture NV_copy_image ARB_framebuffer_sRGB
# required-props in wgl.spec (which is not used for anything):
# dlflags:	  notlistable handcode
# wglflags:	  client-handcode server-handcode non-dispatch

#
# Boilerplate to define types used by some extensions. This is done
#   up front, since it involves some complexities in protecting
#   the declarations whether or not the -protect flag is given to
#   the generator scripts.
#

passthru: #ifndef WGL_ARB_pbuffer
passthru: DECLARE_HANDLE(HPBUFFERARB);
passthru: #endif
passthru: #ifndef WGL_EXT_pbuffer
passthru: DECLARE_HANDLE(HPBUFFEREXT);
passthru: #endif
passthru: #ifndef WGL_NV_present_video
passthru: DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
passthru: #endif
passthru: #ifndef WGL_NV_video_output
passthru: DECLARE_HANDLE(HPVIDEODEV);
passthru: #endif
passthru: #ifndef WGL_NV_gpu_affinity
passthru: DECLARE_HANDLE(HPGPUNV);
passthru: DECLARE_HANDLE(HGPUNV);
passthru:
passthru: typedef struct _GPU_DEVICE {
passthru:     DWORD  cb;
passthru:     CHAR   DeviceName[32];
passthru:     CHAR   DeviceString[128];
passthru:     DWORD  Flags;
passthru:     RECT   rcVirtualScreen;
passthru: } GPU_DEVICE, *PGPU_DEVICE;
passthru: #endif
passthru: #ifndef WGL_NV_video_capture
passthru: DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
passthru: #endif
passthru:


###############################################################################
#
# ARB Extension #4
# ARB_buffer_region commands
#
###############################################################################

CreateBufferRegionARB(hDC, iLayerPlane, uType)
	return		HANDLE
	param		hDC		HDC in value
	param		iLayerPlane	int in value
	param		uType		UINT in value
	category	ARB_buffer_region

DeleteBufferRegionARB(hRegion)
	return		VOID
	param		hRegion		HANDLE in value
	category	ARB_buffer_region

SaveBufferRegionARB(hRegion, x, y, width, height)
	return		BOOL
	param		hRegion		HANDLE in value
	param		x		int in value
	param		y		int in value
	param		width		int in value
	param		height		int in value
	category	ARB_buffer_region

RestoreBufferRegionARB(hRegion, x, y, width, height, xSrc, ySrc)
	return		BOOL
	param		hRegion		HANDLE in value
	param		x		int in value
	param		y		int in value
	param		width		int in value
	param		height		int in value
	param		xSrc		int in value
	param		ySrc		int in value
	category	ARB_buffer_region

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
# ARB Extension #8
# ARB_extensions_string commands
#
###############################################################################

GetExtensionsStringARB(hdc)
	return		String
	param		hdc		HDC in value
	category	ARB_extensions_string

###############################################################################
#
# ARB Extension #9
# ARB_pixel_format commands
#
###############################################################################

GetPixelFormatAttribivARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues)
	return		BOOL
	param		hdc		HDC in value
	param		iPixelFormat	int in value
	param		iLayerPlane	int in value
	param		nAttributes	UINT in value
	param		piAttributes	int in array [nAttributes]
	param		piValues	int out array [nAttributes]
	category	ARB_pixel_format

GetPixelFormatAttribfvARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues)
	return		BOOL
	param		hdc		HDC in value
	param		iPixelFormat	int in value
	param		iLayerPlane	int in value
	param		nAttributes	UINT in value
	param		piAttributes	int in array [nAttributes]
	param		pfValues	FLOAT out array [nAttributes]
	category	ARB_pixel_format

ChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats)
	return		BOOL
	param		hdc		HDC in value
	param		piAttribIList	int in array [COMPSIZE()]
	param		pfAttribFList	FLOAT in array [COMPSIZE()]
	param		nMaxFormats	UINT in value
	param		piFormats	int out array [COMPSIZE(nNumFormats)]
	param		nNumFormats	UINT out reference
	category	ARB_pixel_format

###############################################################################
#
# ARB Extension #10
# ARB_make_current_read commands
#
###############################################################################

MakeContextCurrentARB(hDrawDC, hReadDC, hglrc)
	return		BOOL
	param		hDrawDC		HDC in value
	param		hReadDC		HDC in value
	param		hglrc		HGLRC in value
	category	ARB_make_current_read

GetCurrentReadDCARB()
	return		HDC
	category	ARB_make_current_read

###############################################################################
#
# ARB Extension #11
# ARB_pbuffer commands
#
###############################################################################

CreatePbufferARB(hDC, iPixelFormat, iWidth, iHeight, piAttribList)
	return		HPBUFFERARB
	param		hDC		HDC in value
	param		iPixelFormat	int in value
	param		iWidth		int in value
	param		iHeight		int in value
	param		piAttribList	int in array [COMPSIZE()]
	category	ARB_pbuffer

GetPbufferDCARB(hPbuffer)
	return		HDC
	param		hPbuffer	HPBUFFERARB in value
	category	ARB_pbuffer

ReleasePbufferDCARB(hPbuffer, hDC)
	return		int
	param		hPbuffer	HPBUFFERARB in value
	param		hDC		HDC in value
	category	ARB_pbuffer

DestroyPbufferARB(hPbuffer)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	category	ARB_pbuffer

QueryPbufferARB(hPbuffer, iAttribute, piValue)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		iAttribute	int in value
	param		piValue		int out reference
	category	ARB_pbuffer

###############################################################################
#
# ARB Extension #20
# ARB_render_texture commands
#
###############################################################################

BindTexImageARB(hPbuffer, iBuffer)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		iBuffer		int in value
	category	ARB_render_texture

ReleaseTexImageARB(hPbuffer, iBuffer)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		iBuffer		int in value
	category	ARB_render_texture

SetPbufferAttribARB(hPbuffer, piAttribList)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		piAttribList	int in array [COMPSIZE()]
	category	ARB_render_texture

###############################################################################
#
# ARB Extension #39
# ARB_pixel_format_float commands
#
###############################################################################

# (none)
newcategory: ARB_pixel_format_float

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
# ARB Extension #55
# ARB_create_context commands
#
###############################################################################

CreateContextAttribsARB(hDC, hShareContext, attribList)
	return		HGLRC
	param		hDC		HDC in value
	param		hShareContext	HGLRC in value
	param		attribList	int in array [COMPSIZE()]
	category	ARB_create_context

###############################################################################
#
# ARB Extension #74
# ARB_create_context_profile commands
#
###############################################################################

# (none)
newcategory: ARB_create_context_profile

###############################################################################
#
# ARB Extension #102
# ARB_create_context_robustness commands
#
###############################################################################

# (none)
newcategory: ARB_create_context_robustness


###############################################################################
#
# Extension #167
# EXT_display_color_table commands
#
###############################################################################

CreateDisplayColorTableEXT(id)
	return		GLboolean
	param		id		GLushort in value
	category	EXT_display_color_table

LoadDisplayColorTableEXT(table, length)
	return		GLboolean
	param		table		GLushort in array [length]
	param		length		GLuint in value
	category	EXT_display_color_table

BindDisplayColorTableEXT(id)
	return		GLboolean
	param		id		GLushort in value
	category	EXT_display_color_table

DestroyDisplayColorTableEXT(id)
	return		VOID
	param		id		GLushort in value
	category	EXT_display_color_table

###############################################################################
#
# Extension #168
# EXT_extensions_string commands
#
###############################################################################

GetExtensionsStringEXT()
	return		String
	category	EXT_extensions_string

###############################################################################
#
# Extension #169
# EXT_make_current_read commands
#
###############################################################################

MakeContextCurrentEXT(hDrawDC, hReadDC, hglrc)
	return		BOOL
	param		hDrawDC		HDC in value
	param		hReadDC		HDC in value
	param		hglrc		HGLRC in value
	category	EXT_make_current_read

GetCurrentReadDCEXT()
	return		HDC
	category	EXT_make_current_read

###############################################################################
#
# Extension #171
# EXT_pbuffer commands
#
###############################################################################

CreatePbufferEXT(hDC, iPixelFormat, iWidth, iHeight, piAttribList)
	return		HPBUFFEREXT
	param		hDC		HDC in value
	param		iPixelFormat	int in value
	param		iWidth		int in value
	param		iHeight		int in value
	param		piAttribList	int in array [COMPSIZE()]
	category	EXT_pbuffer

GetPbufferDCEXT(hPbuffer)
	return		HDC
	param		hPbuffer	HPBUFFEREXT in value
	category	EXT_pbuffer

ReleasePbufferDCEXT(hPbuffer, hDC)
	return		int
	param		hPbuffer	HPBUFFEREXT in value
	param		hDC		HDC in value
	category	EXT_pbuffer

DestroyPbufferEXT(hPbuffer)
	return		BOOL
	param		hPbuffer	HPBUFFEREXT in value
	category	EXT_pbuffer

QueryPbufferEXT(hPbuffer, iAttribute, piValue)
	return		BOOL
	param		hPbuffer	HPBUFFEREXT in value
	param		iAttribute	int in value
	param		piValue		int out reference
	category	EXT_pbuffer

###############################################################################
#
# Extension #170
# EXT_pixel_format commands
#
###############################################################################

GetPixelFormatAttribivEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues)
	return		BOOL
	param		hdc		HDC in value
	param		iPixelFormat	int in value
	param		iLayerPlane	int in value
	param		nAttributes	UINT in value
	param		piAttributes	int out array [nAttributes]
	param		piValues	int out array [nAttributes]
	category	EXT_pixel_format

GetPixelFormatAttribfvEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues)
	return		BOOL
	param		hdc		HDC in value
	param		iPixelFormat	int in value
	param		iLayerPlane	int in value
	param		nAttributes	UINT in value
	param		piAttributes	int out array [nAttributes]
	param		pfValues	FLOAT out array [nAttributes]
	category	EXT_pixel_format

ChoosePixelFormatEXT(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats)
	return		BOOL
	param		hdc		HDC in value
	param		piAttribIList	int in array [COMPSIZE()]
	param		pfAttribFList	FLOAT in array [COMPSIZE()]
	param		nMaxFormats	UINT in value
	param		piFormats	int out array [COMPSIZE(nNumFormats)]
	param		nNumFormats	UINT out reference
	category	EXT_pixel_format

###############################################################################
#
# Extension #172
# EXT_swap_control commands
#
###############################################################################

SwapIntervalEXT(interval)
	return		BOOL
	param		interval	int in value
	category	EXT_swap_control

GetSwapIntervalEXT()
	return		int
	category	EXT_swap_control

###############################################################################
#
# Extension #177
# EXT_depth_float commands
#
###############################################################################

# (none)
newcategory: EXT_depth_float

###############################################################################
#
# Extension #190
# NV_vertex_array_range commands
#
###############################################################################

AllocateMemoryNV(size, readfreq, writefreq, priority)
	return		VoidPointer
	param		size		    GLsizei in value
	param		readfreq	    GLfloat in value
	param		writefreq	    GLfloat in value
	param		priority	    GLfloat in value
	category	NV_vertex_array_range

FreeMemoryNV(pointer)
	return		void
	param		pointer		    void out array [1]
	category	NV_vertex_array_range

###############################################################################
#
# Extension #207
# 3DFX_multisample commands
#
###############################################################################

# (none)
newcategory: 3DFX_multisample

###############################################################################
#
# Extension #209
# EXT_multisample commands
#
###############################################################################

# (none)
newcategory: EXT_multisample

###############################################################################
#
# Extension #242
# OML_sync_control commands
#
###############################################################################

GetSyncValuesOML(hdc, ust, msc, sbc)
	return		BOOL
	param		hdc		HDC in value
	param		ust		INT64 out array [1]
	param		msc		INT64 out array [1]
	param		sbc		INT64 out array [1]
	category	OML_sync_control

GetMscRateOML(hdc, numerator, denominator)
	return		BOOL
	param		hdc		HDC in value
	param		numerator	INT32 out array [1]
	param		denominator	INT32 out array [1]
	category	OML_sync_control

SwapBuffersMscOML(hdc, target_msc, divisor, remainder)
	return		INT64
	param		hdc		HDC in value
	param		target_msc	INT64 in value
	param		divisor		INT64 in value
	param		remainder	INT64 in value
	category	OML_sync_control

SwapLayerBuffersMscOML(hdc, fuPlanes, target_msc, divisor, remainder)
	return		INT64
	param		hdc		HDC in value
	param		fuPlanes	int in value
	param		target_msc	INT64 in value
	param		divisor		INT64 in value
	param		remainder	INT64 in value
	category	OML_sync_control

WaitForMscOML(hdc, target_msc, divisor, remainder , ust, msc, sbc)
	return		BOOL
	param		hdc		HDC in value
	param		target_msc	INT64 in value
	param		divisor		INT64 in value
	param		remainder	INT64 in value
	param		ust		INT64 out array [1]
	param		msc		INT64 out array [1]
	param		sbc		INT64 out array [1]
	category	OML_sync_control

WaitForSbcOML(hdc, target_sbc, ust, msc, sbc)
	return		BOOL
	param		hdc		HDC in value
	param		target_sbc	INT64 in value
	param		ust		INT64 out array [1]
	param		msc		INT64 out array [1]
	param		sbc		INT64 out array [1]
	category	OML_sync_control

###############################################################################
#
# Extension #250
# I3D_digital_video_control commands
#
###############################################################################

GetDigitalVideoParametersI3D(hDC, iAttribute, piValue)
	return		BOOL
	param		hDC		HDC in value
	param		iAttribute	int in value
	param		piValue		int out array [COMPSIZE(iAttribute)]
	category	I3D_digital_video_control

SetDigitalVideoParametersI3D(hDC, iAttribute, piValue)
	return		BOOL
	param		hDC		HDC in value
	param		iAttribute	int in value
	param		piValue		int in array [COMPSIZE(iAttribute)]
	category	I3D_digital_video_control

###############################################################################
#
# Extension #251
# I3D_gamma commands
#
###############################################################################

GetGammaTableParametersI3D(hDC, iAttribute, piValue)
	return		BOOL
	param		hDC		HDC in value
	param		iAttribute	int in value
	param		piValue		int out array [COMPSIZE(iAttribute)]
	category	I3D_gamma

SetGammaTableParametersI3D(hDC, iAttribute, piValue)
	return		BOOL
	param		hDC		HDC in value
	param		iAttribute	int in value
	param		piValue		int in array [COMPSIZE(iAttribute)]
	category	I3D_gamma

GetGammaTableI3D(hDC, iEntries, puRed, puGreen, puBlue)
	return		BOOL
	param		hDC		HDC in value
	param		iEntries	int in value
	param		puRed		USHORT out array [iEntries]
	param		puGreen		USHORT out array [iEntries]
	param		puBlue		USHORT out array [iEntries]
	category	I3D_gamma

SetGammaTableI3D(hDC, iEntries, puRed, puGreen, puBlue)
	return		BOOL
	param		hDC		HDC in value
	param		iEntries	int in value
	param		puRed		USHORT in array [iEntries]
	param		puGreen		USHORT in array [iEntries]
	param		puBlue		USHORT in array [iEntries]
	category	I3D_gamma

###############################################################################
#
# Extension #252
# I3D_genlock commands
#
###############################################################################

EnableGenlockI3D(hDC)
	return		BOOL
	param		hDC		HDC in value
	category	I3D_genlock

DisableGenlockI3D(hDC)
	return		BOOL
	param		hDC		HDC in value
	category	I3D_genlock

IsEnabledGenlockI3D(hDC, pFlag)
	return		BOOL
	param		hDC		HDC in value
	param		pFlag		BOOL out reference
	category	I3D_genlock

GenlockSourceI3D(hDC,  uSource)
	return		BOOL
	param		hDC		HDC in value
	param		uSource		UINT in value
	category	I3D_genlock

GetGenlockSourceI3D(hDC, uSource)
	return		BOOL
	param		hDC		HDC in value
	param		uSource		UINT out reference
	category	I3D_genlock

GenlockSourceEdgeI3D(hDC,  uEdge)
	return		BOOL
	param		hDC		HDC in value
	param		uEdge		UINT in value
	category	I3D_genlock

GetGenlockSourceEdgeI3D(hDC, uEdge)
	return		BOOL
	param		hDC		HDC in value
	param		uEdge		UINT out reference
	category	I3D_genlock

GenlockSampleRateI3D(hDC,  uRate)
	return		BOOL
	param		hDC		HDC in value
	param		uRate		UINT in value
	category	I3D_genlock

GetGenlockSampleRateI3D(hDC, uRate)
	return		BOOL
	param		hDC		HDC in value
	param		uRate		UINT out reference
	category	I3D_genlock

GenlockSourceDelayI3D(hDC,  uDelay)
	return		BOOL
	param		hDC		HDC in value
	param		uDelay		UINT in value
	category	I3D_genlock

GetGenlockSourceDelayI3D(hDC, uDelay)
	return		BOOL
	param		hDC		HDC in value
	param		uDelay		UINT out reference
	category	I3D_genlock

QueryGenlockMaxSourceDelayI3D(hDC, uMaxLineDelay, uMaxPixelDelay)
	return		BOOL
	param		hDC		HDC in value
	param		uMaxLineDelay	UINT out reference
	param		uMaxPixelDelay	UINT out reference
	category	I3D_genlock

###############################################################################
#
# Extension #253
# I3D_image_buffer commands
#
###############################################################################

CreateImageBufferI3D(hDC, dwSize,  uFlags)
	return		LPVOID
	param		hDC		HDC in value
	param		dwSize		DWORD in value
	param		uFlags		UINT in value
	category	I3D_image_buffer

DestroyImageBufferI3D(hDC, pAddress)
	return		BOOL
	param		hDC		HDC in value
	param		pAddress	LPVOID in value
	category	I3D_image_buffer

AssociateImageBufferEventsI3D(hDC,  pEvent, pAddress, pSize,  count)
	return		BOOL
	param		hDC		HDC in value
	param		pEvent		HANDLE in array [count]
	param		pAddress	LPVOID in array [count]
	param		pSize		DWORD in array [count]
	param		count		UINT in value
	category	I3D_image_buffer

ReleaseImageBufferEventsI3D(hDC, pAddress,  count)
	return		BOOL
	param		hDC		HDC in value
	param		pAddress	LPVOID in array [count]
	param		count		UINT in value
	category	I3D_image_buffer

###############################################################################
#
# Extension #254
# I3D_swap_frame_lock commands
#
###############################################################################

EnableFrameLockI3D()
	return		BOOL
	category	I3D_swap_frame_lock

DisableFrameLockI3D()
	return		BOOL
	category	I3D_swap_frame_lock

IsEnabledFrameLockI3D(pFlag)
	return		BOOL
	param		pFlag		BOOL out reference
	category	I3D_swap_frame_lock

QueryFrameLockMasterI3D(pFlag)
	return		BOOL
	param		pFlag		BOOL out reference
	category	I3D_swap_frame_lock

###############################################################################
#
# Extension #255
# I3D_swap_frame_usage commands
#
###############################################################################

GetFrameUsageI3D(pUsage)
	return		BOOL
	param		pUsage		float out reference
	category	I3D_swap_frame_usage

BeginFrameTrackingI3D()
	return		BOOL
	category	I3D_swap_frame_usage

EndFrameTrackingI3D()
	return		BOOL
	category	I3D_swap_frame_usage

QueryFrameTrackingI3D(pFrameCount, pMissedFrames, pLastMissedUsage)
	return		BOOL
	param		pFrameCount	DWORD out reference
	param		pMissedFrames	DWORD out reference
	param		pLastMissedUsage    float out reference
	category	I3D_swap_frame_usage

###############################################################################
#
# Extension #278
# ATI_pixel_format_float commands
#
###############################################################################

# (none)
newcategory: ATI_pixel_format_float

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
# Extension #313
# 3DL_stereo_control commands
#
###############################################################################

SetStereoEmitterState3DL(hDC, uState)
	return		BOOL
	param		hDC		HDC in value
	param		uState		UINT in value
	category	3DL_stereo_control

###############################################################################
#
# Extension #328
# EXT_pixel_format_packed_float commands
#
###############################################################################

# (none)
newcategory: EXT_pixel_format_packed_float

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
# Extension #347
# NV_present_video commands
#
###############################################################################

EnumerateVideoDevicesNV(hDC, phDeviceList)
	return		int
	param		hDC		HDC in value
	param		phDeviceList	HVIDEOOUTPUTDEVICENV out array
	category	NV_present_video

BindVideoDeviceNV(hDC, uVideoSlot, hVideoDevice, piAttribList)
	return		BOOL
	param		hDC		HDC in value
	param		uVideoSlot	uint in value
	param		hVideoDevice	HVIDEOOUTPUTDEVICENV in value
	param		piAttribList	int in array [COMPSIZE()]
	category	NV_present_video

QueryCurrentContextNV(iAttribute, piValue)
	return		BOOL
	param		iAttribute	int in value
	param		piValue		int out array [COMPSIZE()]
	category	NV_present_video

###############################################################################
#
# Extension #349
# NV_video_output commands
#
###############################################################################

GetVideoDeviceNV(hDC, numDevices, hVideoDevice)
	return		BOOL
	param		hDC		HDC in value
	param		numDevices	int in value
	param		hVideoDevice	HPVIDEODEV out reference
	category	NV_video_output

ReleaseVideoDeviceNV(hVideoDevice)
	return		BOOL
	param		hVideoDevice	HPVIDEODEV in value
	category	NV_video_output

BindVideoImageNV(hVideoDevice, hPbuffer, iVideoBuffer)
	return		BOOL
	param		hVideoDevice	HPVIDEODEV in value
	param		hPbuffer	HPBUFFERARB in value
	param		iVideoBuffer	int in value
	category	NV_video_output

ReleaseVideoImageNV(hPbuffer, iVideoBuffer)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		iVideoBuffer	int in value
	category	NV_video_output

SendPbufferToVideoNV(hPbuffer, iBufferType, pulCounterPbuffer, bBlock)
	return		BOOL
	param		hPbuffer	HPBUFFERARB in value
	param		iBufferType	int in value
	param		pulCounterPbuffer   ulong out reference
	param		bBlock		BOOL in value
	category	NV_video_output

GetVideoInfoNV(hpVideoDevice, pulCounterOutputPbuffer, pulCounterOutputVideo)
	return		BOOL
	param		hpVideoDevice	HPVIDEODEV in value
	param		pulCounterOutputPbuffer ulong out reference
	param		pulCounterOutputVideo	ulong out reference
	category	NV_video_output

###############################################################################
#
# Extension #351
# NV_swap_group commands
#
###############################################################################

JoinSwapGroupNV(hDC, group)
	return		BOOL
	param		hDC		HDC in value
	param		group		GLuint in value
	category	NV_swap_group

BindSwapBarrierNV(group, barrier)
	return		BOOL
	param		group		GLuint in value
	param		barrier		GLuint in value
	category	NV_swap_group

QuerySwapGroupNV(hDC, group, barrier)
	return		BOOL
	param		hDC		HDC in value
	param		group		GLuint out reference
	param		barrier		GLuint out reference
	category	NV_swap_group

QueryMaxSwapGroupsNV(hDC, maxGroups, maxBarriers)
	return		BOOL
	param		hDC		HDC in value
	param		maxGroups	GLuint out reference
	param		maxBarriers	GLuint out reference
	category	NV_swap_group

QueryFrameCountNV(hDC, count)
	return		BOOL
	param		hDC		HDC in value
	param		count		GLuint out reference
	category	NV_swap_group

ResetFrameCountNV(hDC)
	return		BOOL
	param		hDC		HDC in value
	category	NV_swap_group

###############################################################################
#
# Extension #355
# NV_gpu_affinity commands
#
###############################################################################

EnumGpusNV(iGpuIndex, phGpu)
	return		BOOL
	param		iGpuIndex	UINT in value
	param		phGpu		HGPUNV out reference
	category	NV_gpu_affinity

EnumGpuDevicesNV(hGpu, iDeviceIndex, lpGpuDevice)
	return		BOOL
	param		hGpu		HGPUNV in value
	param		iDeviceIndex	UINT in value
	param		lpGpuDevice	PGPU_DEVICE in value
	category	NV_gpu_affinity

CreateAffinityDCNV(phGpuList)
	return		HDC
	param		phGpuList	HGPUNV in array [COMPSIZE()]
	category	NV_gpu_affinity

EnumGpusFromAffinityDCNV(hAffinityDC, iGpuIndex, hGpu)
	return		BOOL
	param		hAffinityDC	HDC in value
	param		iGpuIndex	UINT in value
	param		hGpu		HGPUNV out reference
	category	NV_gpu_affinity

DeleteDCNV(hdc)
	return		BOOL
	param		hdc		HDC in value
	category	NV_gpu_affinity

###############################################################################
#
# Extension #361
# AMD_gpu_association commands
#
###############################################################################

GetGPUIDsAMD(maxCount, ids)
	return		UINT
	param		maxCount	UINT in value
	param		ids		UINT out array [maxCount]
	category	AMD_gpu_association

GetGPUInfoAMD(id, property, dataType, size, data)
	return		INT
	param		id		UINT in value
	param		property	int in value
	param		dataType	GLenum in value
	param		size		UINT in value
	param		data		void out array [COMPSIZE(dataType,size)]
	category	AMD_gpu_association

GetContextGPUIDAMD(hglrc)
	return		UINT
	param		hglrc		HGLRC in value
	category	AMD_gpu_association

CreateAssociatedContextAMD(id)
	return		HGLRC
	param		id		UINT in value
	category	AMD_gpu_association

CreateAssociatedContextAttribsAMD(id, hShareContext, attribList)
	return		HGLRC
	param		id		UINT in value
	param		hShareContext	HGLRC in value
	param		attribList	int in array [COMPSIZE()]
	category	AMD_gpu_association

DeleteAssociatedContextAMD(hglrc)
	return		BOOL
	param		hglrc		HGLRC in value
	category	AMD_gpu_association

MakeAssociatedContextCurrentAMD(hglrc)
	return		BOOL
	param		hglrc		HGLRC in value
	category	AMD_gpu_association

GetCurrentAssociatedContextAMD()
	return		HGLRC
	category	AMD_gpu_association

BlitContextFramebufferAMD(dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)
	return		VOID
	param		dstCtx		HGLRC in value
	param		srcX0		GLint in value
	param		srcY0		GLint in value
	param		srcX1		GLint in value
	param		srcY1		GLint in value
	param		dstX0		GLint in value
	param		dstY0		GLint in value
	param		dstX1		GLint in value
	param		dstY1		GLint in value
	param		mask		GLbitfield in value
	param		filter		GLenum in value
	category	AMD_gpu_association

###############################################################################
#
# Extension #374
# NV_video_capture commands
#
###############################################################################

BindVideoCaptureDeviceNV(uVideoSlot, hDevice)
	return		BOOL
	param		uVideoSlot	UINT in value
	param		hDevice		HVIDEOINPUTDEVICENV in value
	category	NV_video_capture

EnumerateVideoCaptureDevicesNV(hDc, phDeviceList)
	return		UINT
	param		hDc		HDC in value
	param		phDeviceList	HVIDEOINPUTDEVICENV out reference
	category	NV_video_capture

LockVideoCaptureDeviceNV(hDc, hDevice)
	return		BOOL
	param		hDc		HDC in value
	param		hDevice		HVIDEOINPUTDEVICENV in value
	category	NV_video_capture

QueryVideoCaptureDeviceNV(hDc, hDevice, iAttribute, piValue)
	return		BOOL
	param		hDc		HDC in value
	param		hDevice		HVIDEOINPUTDEVICENV in value
	param		iAttribute	int in value
	param		piValue		int out reference
	category	NV_video_capture

ReleaseVideoCaptureDeviceNV(hDc, hDevice)
	return		BOOL
	param		hDc		HDC in value
	param		hDevice		HVIDEOINPUTDEVICENV in value
	category	NV_video_capture

###############################################################################
#
# Extension #376
# WGL_NV_copy_image commands
#
###############################################################################

CopyImageSubDataNV(hSrcRC, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, hDstRC, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth)
	return		BOOL
	param		hSrcRC		HGLRC in value
	param		srcName		GLuint in value
	param		srcTarget	GLenum in value
	param		srcLevel	GLint in value
	param		srcX		GLint in value
	param		srcY		GLint in value
	param		srcZ		GLint in value
	param		hDstRC		HGLRC in value
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

###############################################################################
#
# Extension #393
# NV_multisample_coverage commands
#
###############################################################################

# (none)
newcategory: NV_multisample_coverage
