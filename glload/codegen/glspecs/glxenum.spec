# Copyright (c) 1991-2005 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2010 The Khronos Group, Inc.
#
# This document is licensed under the SGI Free Software B License Version
# 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
#
# $Revision: 12183 $ on $Date: 2010-08-06 02:53:05 -0700 (Fri, 06 Aug 2010) $

# This is the GLX enumerant registry.
#
# It is an extremely important file. Do not mess with it unless
# you know what you're doing and have permission to do so.
#
# Rules for modification are the same as the rules for the OpenGL
# enumerant registry (gl.spec). Basically, don't modify this
# file unless you're the Khronos API Registrar.

Extensions define:
	VERSION_1_1					= 1
	VERSION_1_2					= 1
	VERSION_1_3					= 1
	VERSION_1_4					= 1
	SGIS_multisample				= 1
	EXT_visual_info					= 1
	SGI_swap_control				= 1
	SGI_video_sync					= 1
	SGI_make_current_read				= 1
	SGIX_video_source				= 1
	EXT_visual_rating				= 1
	EXT_import_context				= 1
	SGIX_fbconfig					= 1
	SGIX_pbuffer					= 1
	SGI_cushion					= 1
	SGIX_video_resize				= 1
	SGIX_dmbuffer					= 1
	SGIX_swap_group					= 1
	SGIX_swap_barrier				= 1
	SGIS_blended_overlay				= 1
	SGIS_shared_multisample				= 1
	SUN_get_transparent_index			= 1
	3DFX_multisample				= 1
	MESA_copy_sub_buffer				= 1
	MESA_pixmap_colormap				= 1
	MESA_release_buffers				= 1
	MESA_set_3dfx_mode				= 1
	SGIX_visual_select_group			= 1
	SGIX_hyperpipe				  = 1

GLXStringName enum:
	VENDOR						= 0x1
	VERSION						= 0x2
	EXTENSIONS					= 0x3

GLXErrorCode enum:
	BAD_SCREEN					= 1
	BAD_ATTRIBUTE					= 2
	NO_EXTENSION					= 3
	BAD_VISUAL					= 4
	BAD_CONTEXT					= 5
	BAD_VALUE					= 6
	BAD_ENUM					= 7
	BAD_HYPERPIPE_CONFIG_SGIX			= 91		# SGIX_hyperpipe
	BAD_HYPERPIPE_SGIX				= 92		#   "

# Reserved bits in bitfields of various purposes

GLXDrawableTypeMask enum:
	WINDOW_BIT					= 0x00000001	# DRAWABLE_TYPE value
	PIXMAP_BIT					= 0x00000002	#   "
	PBUFFER_BIT					= 0x00000004	#   "
	WINDOW_BIT_SGIX					= 0x00000001	# DRAWABLE_TYPE_SGIX value
	PIXMAP_BIT_SGIX					= 0x00000002	#   "
	PBUFFER_BIT_SGIX				= 0x00000004	#   "

GLXRenderTypeMask enum:
	RGBA_BIT					= 0x00000001	# RENDER_TYPE value
	COLOR_INDEX_BIT					= 0x00000002	#   "
	RGBA_BIT_SGIX					= 0x00000001	# RENDER_TYPE_SGIX value
	COLOR_INDEX_BIT_SGIX				= 0x00000002	#   "
	RGBA_FLOAT_BIT_ARB				= 0x00000004	# RENDER_TYPE value (from ARB_fbconfig_float)
	RGBA_UNSIGNED_FLOAT_BIT_EXT			= 0x00000008	# RENDER_TYPE value (from EXT_fbconfig_packed_float)

GLXSyncType enum:
	SYNC_FRAME_SGIX					= 0x00000000	# ChannelRectSyncSGIX synctype
	SYNC_SWAP_SGIX					= 0x00000001	#   "

GLXEventMask enum:
	PBUFFER_CLOBBER_MASK				= 0x08000000	# SelectEvent mask
	BUFFER_CLOBBER_MASK_SGIX			= 0x08000000	# SelectEventSGIX mask
	BUFFER_SWAP_COMPLETE_INTEL_MASK			= 0x04000000	# SelectEvent mask (for GLX_INTEL_swap_event)

GLXPbufferClobberMask enum:
	FRONT_LEFT_BUFFER_BIT				= 0x00000001	# PbufferClobberEvent mask
	FRONT_RIGHT_BUFFER_BIT				= 0x00000002	#   "
	BACK_LEFT_BUFFER_BIT				= 0x00000004	#   "
	BACK_RIGHT_BUFFER_BIT				= 0x00000008	#   "
	AUX_BUFFERS_BIT					= 0x00000010	#   "
	DEPTH_BUFFER_BIT				= 0x00000020	#   "
	STENCIL_BUFFER_BIT				= 0x00000040	#   "
	ACCUM_BUFFER_BIT				= 0x00000080	#   "
	FRONT_LEFT_BUFFER_BIT_SGIX			= 0x00000001	# BufferClobberEventSGIX mask
	FRONT_RIGHT_BUFFER_BIT_SGIX			= 0x00000002	#   "
	BACK_LEFT_BUFFER_BIT_SGIX			= 0x00000004	#   "
	BACK_RIGHT_BUFFER_BIT_SGIX			= 0x00000008	#   "
	AUX_BUFFERS_BIT_SGIX				= 0x00000010	#   "
	DEPTH_BUFFER_BIT_SGIX				= 0x00000020	#   "
	STENCIL_BUFFER_BIT_SGIX				= 0x00000040	#   "
	ACCUM_BUFFER_BIT_SGIX				= 0x00000080	#   "
	SAMPLE_BUFFERS_BIT_SGIX				= 0x00000100	#   "

GLXHyperpipeTypeMask enum:
	HYPERPIPE_DISPLAY_PIPE_SGIX			= 0x00000001	# SGIX_hyperpipe
	HYPERPIPE_RENDER_PIPE_SGIX			= 0x00000002	#   "

GLXHyperpipeAttrib enum:
	PIPE_RECT_SGIX					= 0x00000001	# SGIX_hyperpipe
	PIPE_RECT_LIMITS_SGIX				= 0x00000002	#   "
	HYPERPIPE_STEREO_SGIX				= 0x00000003	#   "
	HYPERPIPE_PIXEL_AVERAGE_SGIX			= 0x00000004	#   "

GLXHyperpipeMisc enum:
	HYPERPIPE_PIPE_NAME_LENGTH_SGIX			= 80		# SGIX_hyperpipe

GLXBindToTextureTargetMask enum:
	TEXTURE_1D_BIT_EXT				= 0x00000001	# EXT_texture_from_pixmap
	TEXTURE_2D_BIT_EXT				= 0x00000002
	TEXTURE_RECTANGLE_BIT_EXT			= 0x00000004

# CONTEXT_FLAGS_ARB bits (shared with WGL and GL)
GLXContextFlags enum:
	CONTEXT_DEBUG_BIT_ARB				= 0x00000001	# ARB_create_context
	CONTEXT_FORWARD_COMPATIBLE_BIT_ARB		= 0x00000002	# ARB_create_context
	CONTEXT_ROBUST_ACCESS_BIT_ARB			= 0x00000004	# ARB_create_context_robustness

# CONTEXT_PROFILE_MASK_ARB bits
GLXContextProfileMask enum:
	CONTEXT_CORE_PROFILE_BIT_ARB			= 0x00000001	# ARB_create_context_profile
	CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB		= 0x00000002	# ARB_create_context_profile
	CONTEXT_ES2_PROFILE_BIT_EXT			= 0x00000004	# EXT_create_context_es2_profile

GLXAttribute enum:
	USE_GL						= 1		# Visual attributes
	BUFFER_SIZE					= 2		#   "
	LEVEL						= 3		#   "
	RGBA						= 4		#   "
	DOUBLEBUFFER					= 5		#   "
	STEREO						= 6		#   "
	AUX_BUFFERS					= 7		#   "
	RED_SIZE					= 8		#   "
	GREEN_SIZE					= 9		#   "
	BLUE_SIZE					= 10		#   "
	ALPHA_SIZE					= 11		#   "
	DEPTH_SIZE					= 12		#   "
	STENCIL_SIZE					= 13		#   "
	ACCUM_RED_SIZE					= 14		#   "
	ACCUM_GREEN_SIZE				= 15		#   "
	ACCUM_BLUE_SIZE					= 16		#   "
	ACCUM_ALPHA_SIZE				= 17		#   "
	CONFIG_CAVEAT					= 0x20		#   "
	X_VISUAL_TYPE					= 0x22		#   "
	TRANSPARENT_TYPE				= 0x23		#   "
	TRANSPARENT_INDEX_VALUE				= 0x24		#   "
	TRANSPARENT_RED_VALUE				= 0x25		#   "
	TRANSPARENT_GREEN_VALUE				= 0x26		#   "
	TRANSPARENT_BLUE_VALUE				= 0x27		#   "
	TRANSPARENT_ALPHA_VALUE				= 0x28		#   "
	DONT_CARE					= 0xFFFFFFFF	# may be specified for ChooseFBConfig attributes
	NONE						= 0x8000	# several attribute values
	SLOW_CONFIG					= 0x8001	# CONFIG_CAVEAT attribute value
	TRUE_COLOR					= 0x8002	# X_VISUAL_TYPE attribute value
	DIRECT_COLOR					= 0x8003	#   "
	PSEUDO_COLOR					= 0x8004	#   "
	STATIC_COLOR					= 0x8005	#   "
	GRAY_SCALE					= 0x8006	#   "
	STATIC_GRAY					= 0x8007	#   "
	TRANSPARENT_RGB					= 0x8008	# TRANSPARENT_TYPE attribute value
	TRANSPARENT_INDEX				= 0x8009	#   "
	VISUAL_ID					= 0x800B	# Context attribute
	SCREEN						= 0x800C	#   "
	NON_CONFORMANT_CONFIG				= 0x800D	# CONFIG_CAVEAT attribute value
	DRAWABLE_TYPE					= 0x8010	# FBConfig attribute
	RENDER_TYPE					= 0x8011	#   "
	X_RENDERABLE					= 0x8012	#   "
	FBCONFIG_ID					= 0x8013	#   "
	RGBA_TYPE					= 0x8014	# CreateNewContext render_type value
	COLOR_INDEX_TYPE				= 0x8015	#   "
	MAX_PBUFFER_WIDTH				= 0x8016	# FBConfig attribute
	MAX_PBUFFER_HEIGHT				= 0x8017	#   "
	MAX_PBUFFER_PIXELS				= 0x8018	#   "
	PRESERVED_CONTENTS				= 0x801B	# CreateGLXPbuffer attribute
	LARGEST_PBUFFER					= 0x801C	#   "
	WIDTH						= 0x801D	# Drawable attribute
	HEIGHT						= 0x801E	#   "
	EVENT_MASK					= 0x801F	#   "
	DAMAGED						= 0x8020	# PbufferClobber event_type value
	SAVED						= 0x8021	#   "
	WINDOW						= 0x8022	# PbufferClobber draw_type value
	PBUFFER						= 0x8023	#   "
	PBUFFER_HEIGHT					= 0x8040	# CreateGLXPbuffer attribute
	PBUFFER_WIDTH					= 0x8041	#   "
	VISUAL_CAVEAT_EXT				= 0x20		# Visual attribute
	X_VISUAL_TYPE_EXT				= 0x22		#   "
	TRANSPARENT_TYPE_EXT				= 0x23		#   "
	TRANSPARENT_INDEX_VALUE_EXT			= 0x24		#   "
	TRANSPARENT_RED_VALUE_EXT			= 0x25		#   "
	TRANSPARENT_GREEN_VALUE_EXT			= 0x26		#   "
	TRANSPARENT_BLUE_VALUE_EXT			= 0x27		#   "
	TRANSPARENT_ALPHA_VALUE_EXT			= 0x28		#   "
	NONE_EXT					= 0x8000	# several EXT attribute values
	SLOW_VISUAL_EXT					= 0x8001	# VISUAL_CAVEAT_EXT attribute value
	TRUE_COLOR_EXT					= 0x8002	# X_VISUAL_TYPE_EXT attribute value
	DIRECT_COLOR_EXT				= 0x8003	#   "
	PSEUDO_COLOR_EXT				= 0x8004	#   "
	STATIC_COLOR_EXT				= 0x8005	#   "
	GRAY_SCALE_EXT					= 0x8006	#   "
	STATIC_GRAY_EXT					= 0x8007	#   "
	TRANSPARENT_RGB_EXT				= 0x8008	# TRANSPARENT_TYPE_EXT attribute value
	TRANSPARENT_INDEX_EXT				= 0x8009	#   "
	SHARE_CONTEXT_EXT				= 0x800A	# QueryContextInfoEXT attribute
	VISUAL_ID_EXT					= 0x800B	#   "
	SCREEN_EXT					= 0x800C	#   "
	NON_CONFORMANT_VISUAL_EXT			= 0x800D	# VISUAL_CAVEAT_EXT attribute value
	DRAWABLE_TYPE_SGIX				= 0x8010	# FBConfigSGIX attribute
	RENDER_TYPE_SGIX				= 0x8011	#   "
	X_RENDERABLE_SGIX				= 0x8012	#   "
	FBCONFIG_ID_SGIX				= 0x8013	#   "
	RGBA_TYPE_SGIX					= 0x8014	# CreateContextWithConfigSGIX render_type value
	COLOR_INDEX_TYPE_SGIX				= 0x8015	#   "
	MAX_PBUFFER_WIDTH_SGIX				= 0x8016	# FBConfigSGIX attribute
	MAX_PBUFFER_HEIGHT_SGIX				= 0x8017	#   "
	MAX_PBUFFER_PIXELS_SGIX				= 0x8018	#   "
	OPTIMAL_PBUFFER_WIDTH_SGIX			= 0x8019	#   "
	OPTIMAL_PBUFFER_HEIGHT_SGIX			= 0x801A	#   "
	PRESERVED_CONTENTS_SGIX				= 0x801B	# PbufferSGIX attribute
	LARGEST_PBUFFER_SGIX				= 0x801C	#   "
	WIDTH_SGIX					= 0x801D	#   "
	HEIGHT_SGIX					= 0x801E	#   "
	EVENT_MASK_SGIX					= 0x801F	#   "
	DAMAGED_SGIX					= 0x8020	# BufferClobberSGIX event_type value
	SAVED_SGIX					= 0x8021	#   "
	WINDOW_SGIX					= 0x8022	# BufferClobberSGIX draw_type value
	PBUFFER_SGIX					= 0x8023	#   "
	DIGITAL_MEDIA_PBUFFER_SGIX			= 0x8024	# PbufferSGIX attribute
	BLENDED_RGBA_SGIS				= 0x8025	# TRANSPARENT_TYPE_EXT attribute value
	MULTISAMPLE_SUB_RECT_WIDTH_SGIS			= 0x8026	# Visual attribute (shared_multisample)
	MULTISAMPLE_SUB_RECT_HEIGHT_SGIS		= 0x8027	#   "
	VISUAL_SELECT_GROUP_SGIX			= 0x8028	# Visual attribute (visual_select_group)
	HYPERPIPE_ID_SGIX				= 0x8030	# Associated hyperpipe ID (SGIX_hyperpipe)
	SAMPLE_BUFFERS_SGIS				= 100000	# Visual attribute (SGIS_multisample)
	SAMPLES_SGIS					= 100001	#   "
	SAMPLE_BUFFERS_ARB				= 100000	# Visual attribute (ARB_multisample - alias of SGIS_multisample)
	SAMPLES_ARB					= 100001	#   "
	SAMPLE_BUFFERS					= 100000	# Visual attribute (GLX 1.4 core - alias of SGIS_multisample)
	SAMPLES						= 100001	#   "
	COVERAGE_SAMPLES_NV				= 100001	# Visual attribute (NV_multisample_coverage - reuse SAMPLES_ARB)

###############################################################################

# AMD: 0x1F00-0x1F02 (additional; see below; equivalent to corresponding WGL/GL tokens)

###############################################################################

# ARB: 0x2070-0x209F

# Shared with WGL, synchronize create_context_* enums with wglenum.spec!

# Also includes a bitmask - see ContextFlags above
# ARB_create_context enum:
	CONTEXT_MAJOR_VERSION_ARB			= 0x2091
	CONTEXT_MINOR_VERSION_ARB			= 0x2092
# 0x2093 used for WGL_CONTEXT_LAYER_PLANE_ARB
	CONTEXT_FLAGS_ARB				= 0x2094
# 0x2095 collides with WGL_ERROR_INVALID_VERSION_ARB!
	CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB	= 0x2095
# 0x2096 used for WGL_ERROR_INVALID_PROFILE_ARB

# ARB_future_use: 0x2097-0x209F

###############################################################################

# NVIDIA: 0x20A0 - 0x219F (shared with WGL)

# NV_float_buffer enum:
	FLOAT_COMPONENTS_NV				= 0x20B0
# EXT_fbconfig_packed_float enum:
	RGBA_UNSIGNED_FLOAT_TYPE_EXT			= 0x20B1
# ARB_framebuffer_sRGB enum:
	FRAMEBUFFER_SRGB_CAPABLE_ARB			= 0x20B2
# EXT_framebuffer_sRGB enum:
	FRAMEBUFFER_SRGB_CAPABLE_EXT			= 0x20B2
# NV_multisample_coverage enum:
	COLOR_SAMPLES_NV				= 0x20B3

# NV_future_use: 0x20B4-0x20B8

# ARB_fbconfig_float enum:
	RGBA_FLOAT_TYPE_ARB				= 0x20B9

# NV_future_use: 0x20BA-0x20C2

# NV_video_out enum:
	VIDEO_OUT_COLOR_NV				= 0x20C3
	VIDEO_OUT_ALPHA_NV				= 0x20C4
	VIDEO_OUT_DEPTH_NV				= 0x20C5
	VIDEO_OUT_COLOR_AND_ALPHA_NV			= 0x20C6
	VIDEO_OUT_COLOR_AND_DEPTH_NV			= 0x20C7
	VIDEO_OUT_FRAME_NV				= 0x20C8
	VIDEO_OUT_FIELD_1_NV				= 0x20C9
	VIDEO_OUT_FIELD_2_NV				= 0x20CA
	VIDEO_OUT_STACKED_FIELDS_1_2_NV			= 0x20CB
	VIDEO_OUT_STACKED_FIELDS_2_1_NV			= 0x20CC

# NV_video_capture enum:
	DEVICE_ID_NV					= 0x20CD
	UNIQUE_ID_NV					= 0x20CE
	NUM_VIDEO_CAPTURE_SLOTS_NV			= 0x20CF

# EXT_texture_from_pixmap enum:
	BIND_TO_TEXTURE_RGB_EXT				= 0x20D0
	BIND_TO_TEXTURE_RGBA_EXT			= 0x20D1
	BIND_TO_MIPMAP_TEXTURE_EXT			= 0x20D2
	BIND_TO_TEXTURE_TARGETS_EXT			= 0x20D3
	Y_INVERTED_EXT					= 0x20D4
	TEXTURE_FORMAT_EXT				= 0x20D5
	TEXTURE_TARGET_EXT				= 0x20D6
	MIPMAP_TEXTURE_EXT				= 0x20D7
	TEXTURE_FORMAT_NONE_EXT				= 0x20D8
	TEXTURE_FORMAT_RGB_EXT				= 0x20D9
	TEXTURE_FORMAT_RGBA_EXT				= 0x20DA
	TEXTURE_1D_EXT					= 0x20DB
	TEXTURE_2D_EXT					= 0x20DC
	TEXTURE_RECTANGLE_EXT				= 0x20DD
	FRONT_LEFT_EXT					= 0x20DE
	FRONT_RIGHT_EXT					= 0x20DF
	BACK_LEFT_EXT					= 0x20E0
	BACK_RIGHT_EXT					= 0x20E1
	FRONT_EXT					= GLX_FRONT_LEFT_EXT
	BACK_EXT					= GLX_BACK_LEFT_EXT
	AUX0_EXT					= 0x20E2
	AUX1_EXT					= 0x20E3
	AUX2_EXT					= 0x20E4
	AUX3_EXT					= 0x20E5
	AUX4_EXT					= 0x20E6
	AUX5_EXT					= 0x20E7
	AUX6_EXT					= 0x20E8
	AUX7_EXT					= 0x20E9
	AUX8_EXT					= 0x20EA
	AUX9_EXT					= 0x20EB

# NV_future_use: 0x20EC-0x20EF

NV_present_video enum:
	NUM_VIDEO_SLOTS_NV				= 0x20F0

EXT_swap_control enum:
	SWAP_INTERVAL_EXT				= 0x20F1
	MAX_SWAP_INTERVAL_EXT				= 0x20F2

# NV_future_use: 0x20F3-0x219F

###############################################################################

# AMD: 0x21A0-0x21AF

# Shared with WGL, synchronize with wglenum.spec!

# WGL extensions: 0x21A0-0x21A1

GLX_AMD_gpu_association enum:
	GPU_VENDOR_AMD					= 0x1F00
	GPU_RENDERER_STRING_AMD				= 0x1F01
	GPU_OPENGL_VERSION_STRING_AMD			= 0x1F02
	GPU_FASTEST_TARGET_GPUS_AMD			= 0x21A2
	GPU_RAM_AMD					= 0x21A3
	GPU_CLOCK_AMD					= 0x21A4
	GPU_NUM_PIPES_AMD				= 0x21A5
	GPU_NUM_SIMD_AMD				= 0x21A6
	GPU_NUM_RB_AMD					= 0x21A7
	GPU_NUM_SPI_AMD					= 0x21A8

# AMD_future_use: 0x21A9-0x21AF

###############################################################################

# MESA (not in a reserved block)

# MESA_set_3dfx_mode enum:
#	3DFX_WINDOW_MODE_MESA				= 0x1
#	3DFX_FULLSCREEN_MODE_MESA			= 0x2

###############################################################################

# SGI_future_use: 0x8029-0x802F
# SGIX_hyperpipe adds attribute name HYPERPIPE_ID_SGIX = 0x8030
# SGI_future_use: 0x8031-0x803F

###############################################################################

# ARB_future_use: 0x8042-0x804F

###############################################################################

# 3DFX: 0x8050-0x805F

# 3DFX_multisample enum:
#	SAMPLE_BUFFERS_3DFX				= 0x8050
#	SAMPLES_3DFX					= 0x8051

###############################################################################

# OML: 0x8060-0x806F

# OML_swap_method enum:
#	SWAP_METHOD_OML					= 0x8060
#	SWAP_EXCHANGE_OML				= 0x8061
#	SWAP_COPY_OML					= 0x8062
#	SWAP_UNDEFINED_OML				= 0x8063

# OML_future_use: 0x8064-0x806F

###############################################################################

# NVIDIA: 0x8070 - 0x816F

NVIDIA_future_use: 0x8070-0x816F

###############################################################################

# SUN: 0x8170 - 0x817F

SUN_future_use: 0x8170-0x817F

###############################################################################

# INTEL: 0x8180 - 0x818F

# INTEL_swap_event: 0x8180-0x8182
#	EXCHANGE_COMPLETE_INTEL				= 0x8180
#	COPY_COMPLETE_INTEL				= 0x8181
#	FLIP_COMPLETE_INTEL				= 0x8182

INTEL_future_use: 0x8183-0x818F

###############################################################################
### Please remember that new GLX enum allocations must be obtained by request
### to the Khronos API Registrar (see comments at the top of this file)
### File requests in the Khronos Bugzilla, OpenGL project, Registry component.
### Also note that some GLX enum values are shared with GL and WGL, and
### new ranges should be allocated with such overlaps in mind.
###############################################################################

# Any_vendor_future_use: 0x8190-0x824F

###############################################################################

# ARB: 0x8250-0x826F
# No additional values should be used from this range, which includes
# the range used by GL_ARB_robustness rounded up to multiples of 16.

# Also includes a bitmask - see ContextFlags above
# All values are shared with GLX and GL
GLX_ARB_create_context_robustness enum:
	LOSE_CONTEXT_ON_RESET_ARB			= 0x8252    # shared with GL_ARB_robustness
	CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB		= 0x8256    # shared with GL_ARB_robustness
	NO_RESET_NOTIFICATION_ARB			= 0x8261    # shared with GL_ARB_robustness

# Any_vendor_future_use: 0x8270-0x9125

# Also includes a bitmask - see ContextProfileMask above
# All values are shared with GLX and GL
ARB_create_context_profile enum:
	CONTEXT_PROFILE_MASK_ARB			= 0x9126

# Any_vendor_future_use: 0x9127-0xFFFF
#
#   This range must be the last range in the file.  To generate a new
#   range, allocate multiples of 16 from the beginning of the first
#   Any_vendor_future_use range and update glxenum.spec, glxenumext.spec,
#   and extensions.reserved.
