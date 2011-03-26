# Copyright (c) 1991-2005 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2010 The Khronos Group, Inc.
#
# This document is licensed under the SGI Free Software B License Version
# 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
#
# $Revision: 12183 $ on $Date: 2010-08-06 02:53:05 -0700 (Fri, 06 Aug 2010) $

# List of GLX enumerants for glxext.h header
#
# This is NOT the master GLX enumerant registry (glxenum.spec).
#
# Unlike glxenum.spec, glxenumext.spec is
#   (1) In order by extension number.
#   (2) Includes only GLX extensions and GLX 1.3/1.4 core enumerants,
#	since it's assumed all <glx.h> today support at least GLX 1.2.
#   (3) Has no 'Extensions' section, since enums are always
#	conditionally protected against multiple definition
#	by glextenum.pl.
#   (4) Is processed by glextenum.pl, which has evolved
#	from enum.pl - should merge back into one script.

# glxext.h version number - this should be automatically updated,
#   when changing either enum or template spec files.

passthru:
passthru: /* Header file version number, required by OpenGL ABI for Linux */
passthru: /* glxext.h last updated 2010/08/06 */
passthru: /* Current version at http://www.opengl.org/registry/ */
passthru: #define GLX_GLXEXT_VERSION 32

###############################################################################
#
# GLX 1.3 enums
#
###############################################################################

VERSION_1_3 enum:
	WINDOW_BIT					= 0x00000001	# DRAWABLE_TYPE value
	PIXMAP_BIT					= 0x00000002	#   "
	PBUFFER_BIT					= 0x00000004	#   "
	RGBA_BIT					= 0x00000001	# RENDER_TYPE value
	COLOR_INDEX_BIT					= 0x00000002	#   "
	PBUFFER_CLOBBER_MASK				= 0x08000000	# SelectEvent mask
	FRONT_LEFT_BUFFER_BIT				= 0x00000001	# PbufferClobberEvent mask
	FRONT_RIGHT_BUFFER_BIT				= 0x00000002	#   "
	BACK_LEFT_BUFFER_BIT				= 0x00000004	#   "
	BACK_RIGHT_BUFFER_BIT				= 0x00000008	#   "
	AUX_BUFFERS_BIT					= 0x00000010	#   "
	DEPTH_BUFFER_BIT				= 0x00000020	#   "
	STENCIL_BUFFER_BIT				= 0x00000040	#   "
	ACCUM_BUFFER_BIT				= 0x00000080	#   "
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

###############################################################################
#
# GLX 1.4 enums
#
###############################################################################

VERSION_1_4 enum:
	SAMPLE_BUFFERS					= 100000
	SAMPLES						= 100001

###############################################################################
#
# ARB GLX extensions, in ARB extension order
#
###############################################################################

###############################################################################

# No new tokens
# ARB Extension #2
ARB_get_proc_address enum:

###############################################################################

# ARB Extension #5
ARB_multisample enum:
	SAMPLE_BUFFERS_ARB				= 100000
	SAMPLES_ARB					= 100001

###############################################################################

# ARB Extension #28
ARB_vertex_buffer_object enum:
	CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB	= 0x2095

###############################################################################

# ARB Extension #39
ARB_fbconfig_float enum:
	RGBA_FLOAT_TYPE_ARB				= 0x20B9
	RGBA_FLOAT_BIT_ARB				= 0x00000004

###############################################################################

# ARB Extension #46
ARB_framebuffer_sRGB enum:
	FRAMEBUFFER_SRGB_CAPABLE_ARB			= 0x20B2

###############################################################################

# ARB Extension #56
ARB_create_context enum:
	CONTEXT_DEBUG_BIT_ARB				= 0x00000001
	CONTEXT_FORWARD_COMPATIBLE_BIT_ARB		= 0x00000002
	CONTEXT_MAJOR_VERSION_ARB			= 0x2091
	CONTEXT_MINOR_VERSION_ARB			= 0x2092
	CONTEXT_FLAGS_ARB				= 0x2094

###############################################################################

# ARB Extension #75
ARB_create_context_profile enum:
	CONTEXT_CORE_PROFILE_BIT_ARB			= 0x00000001
	CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB		= 0x00000002
	CONTEXT_PROFILE_MASK_ARB			= 0x9126

###############################################################################

# ARB Extension #101
# All values are shared with GLX and GL
ARB_create_context_robustness enum:
	CONTEXT_ROBUST_ACCESS_BIT_ARB			= 0x00000004
	LOSE_CONTEXT_ON_RESET_ARB			= 0x8252
	CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB		= 0x8256
	NO_RESET_NOTIFICATION_ARB			= 0x8261

###############################################################################
#
# non-ARB GLX extensions, in registry order
#
###############################################################################

###############################################################################

# Unfortunately, the SGIS_multisample specification and the IRIX
#  implementation are inconsistent; the spec assigns enums as follows.
#  ARB_multisample reuses these enums with ARB suffixes, and it can't
#  be changed at this point. So in the interest of supporting both
#  extensions on non-IRIX platforms, the SGIS enums will be defined
#  here as originally specified.

# Extension #25
SGIS_multisample enum:
	SAMPLE_BUFFERS_SGIS				= 100000
	SAMPLES_SGIS					= 100001

###############################################################################

# Extension #28
EXT_visual_info enum:
	X_VISUAL_TYPE_EXT				= 0x22
	TRANSPARENT_TYPE_EXT				= 0x23
	TRANSPARENT_INDEX_VALUE_EXT			= 0x24
	TRANSPARENT_RED_VALUE_EXT			= 0x25
	TRANSPARENT_GREEN_VALUE_EXT			= 0x26
	TRANSPARENT_BLUE_VALUE_EXT			= 0x27
	TRANSPARENT_ALPHA_VALUE_EXT			= 0x28
	NONE_EXT					= 0x8000
	TRUE_COLOR_EXT					= 0x8002
	DIRECT_COLOR_EXT				= 0x8003
	PSEUDO_COLOR_EXT				= 0x8004
	STATIC_COLOR_EXT				= 0x8005
	GRAY_SCALE_EXT					= 0x8006
	STATIC_GRAY_EXT					= 0x8007
	TRANSPARENT_RGB_EXT				= 0x8008
	TRANSPARENT_INDEX_EXT				= 0x8009

###############################################################################

# No new tokens
# Extension #40
SGI_swap_control enum:

###############################################################################

# No new tokens
# Extension #41
SGI_video_sync enum:

###############################################################################

# No new tokens
# Extension #42
SGI_make_current_read enum:

###############################################################################

# No new tokens
# Extension #43
SGIX_video_source enum:

###############################################################################

# Extension #44
EXT_visual_rating enum:
	VISUAL_CAVEAT_EXT				= 0x20
	SLOW_VISUAL_EXT					= 0x8001
	NON_CONFORMANT_VISUAL_EXT			= 0x800D
	use EXT_visual_info NONE_EXT

###############################################################################

# Extension #47
EXT_import_context enum:
	SHARE_CONTEXT_EXT				= 0x800A
	VISUAL_ID_EXT					= 0x800B
	SCREEN_EXT					= 0x800C

###############################################################################

# Extension #49
SGIX_fbconfig enum:
	WINDOW_BIT_SGIX					= 0x00000001
	PIXMAP_BIT_SGIX					= 0x00000002
	RGBA_BIT_SGIX					= 0x00000001
	COLOR_INDEX_BIT_SGIX				= 0x00000002
	DRAWABLE_TYPE_SGIX				= 0x8010
	RENDER_TYPE_SGIX				= 0x8011
	X_RENDERABLE_SGIX				= 0x8012
	FBCONFIG_ID_SGIX				= 0x8013
	RGBA_TYPE_SGIX					= 0x8014
	COLOR_INDEX_TYPE_SGIX				= 0x8015
	use EXT_import_context SCREEN_EXT

###############################################################################

# Extension #50
SGIX_pbuffer enum:
	PBUFFER_BIT_SGIX				= 0x00000004
	BUFFER_CLOBBER_MASK_SGIX			= 0x08000000
	FRONT_LEFT_BUFFER_BIT_SGIX			= 0x00000001
	FRONT_RIGHT_BUFFER_BIT_SGIX			= 0x00000002
	BACK_LEFT_BUFFER_BIT_SGIX			= 0x00000004
	BACK_RIGHT_BUFFER_BIT_SGIX			= 0x00000008
	AUX_BUFFERS_BIT_SGIX				= 0x00000010
	DEPTH_BUFFER_BIT_SGIX				= 0x00000020
	STENCIL_BUFFER_BIT_SGIX				= 0x00000040
	ACCUM_BUFFER_BIT_SGIX				= 0x00000080
	SAMPLE_BUFFERS_BIT_SGIX				= 0x00000100
	MAX_PBUFFER_WIDTH_SGIX				= 0x8016
	MAX_PBUFFER_HEIGHT_SGIX				= 0x8017
	MAX_PBUFFER_PIXELS_SGIX				= 0x8018
	OPTIMAL_PBUFFER_WIDTH_SGIX			= 0x8019
	OPTIMAL_PBUFFER_HEIGHT_SGIX			= 0x801A
	PRESERVED_CONTENTS_SGIX				= 0x801B
	LARGEST_PBUFFER_SGIX				= 0x801C
	WIDTH_SGIX					= 0x801D
	HEIGHT_SGIX					= 0x801E
	EVENT_MASK_SGIX					= 0x801F
	DAMAGED_SGIX					= 0x8020
	SAVED_SGIX					= 0x8021
	WINDOW_SGIX					= 0x8022
	PBUFFER_SGIX					= 0x8023

###############################################################################

# Extension #62
SGI_cushion enum:
#	 CUSHION_BUFFERS_SGI	 ????

###############################################################################

# Extension #83
SGIX_video_resize enum:
	SYNC_FRAME_SGIX					= 0x00000000
	SYNC_SWAP_SGIX					= 0x00000001

###############################################################################

# Extension #86
SGIX_dmbuffer enum:
	DIGITAL_MEDIA_PBUFFER_SGIX			= 0x8024

###############################################################################

# No new tokens
# Extension #91
SGIX_swap_group enum:

###############################################################################

# No new tokens
# Extension #92
SGIX_swap_barrier enum:

###############################################################################

# Extension #142
SGIS_blended_overlay enum:
	BLENDED_RGBA_SGIS				= 0x8025

###############################################################################

# Extension #143
SGIS_shared_multisample enum:
	MULTISAMPLE_SUB_RECT_WIDTH_SGIS			= 0x8026
	MULTISAMPLE_SUB_RECT_HEIGHT_SGIS		= 0x8027

###############################################################################

# No new tokens
# Extension #183
SUN_get_transparent_index enum:

###############################################################################

# Extension #207
3DFX_multisample enum:
	SAMPLE_BUFFERS_3DFX				= 0x8050
	SAMPLES_3DFX					= 0x8051

###############################################################################

# No new tokens
# Extension #215
MESA_copy_sub_buffer enum:

###############################################################################

# No new tokens
# Extension #216
MESA_pixmap_colormap enum:

###############################################################################

# No new tokens
# Extension #217
MESA_release_buffers enum:

###############################################################################

# Extension #218
MESA_set_3dfx_mode enum:
	3DFX_WINDOW_MODE_MESA				= 0x1
	3DFX_FULLSCREEN_MODE_MESA			= 0x2

###############################################################################

# Extension #234
SGIX_visual_select_group enum:
	VISUAL_SELECT_GROUP_SGIX			= 0x8028

###############################################################################

# Extension #237
OML_swap_method enum:
	SWAP_METHOD_OML					= 0x8060
	SWAP_EXCHANGE_OML				= 0x8061
	SWAP_COPY_OML					= 0x8062
	SWAP_UNDEFINED_OML				= 0x8063

###############################################################################

# No new tokens
# Extension #238
OML_sync_control enum:

###############################################################################

# Extension #281
NV_float_buffer enum:
	FLOAT_COMPONENTS_NV				= 0x20B0

###############################################################################

# Extension #307
SGIX_hyperpipe enum:
	HYPERPIPE_PIPE_NAME_LENGTH_SGIX			= 80
	BAD_HYPERPIPE_CONFIG_SGIX			= 91
	BAD_HYPERPIPE_SGIX				= 92
	HYPERPIPE_DISPLAY_PIPE_SGIX			= 0x00000001
	HYPERPIPE_RENDER_PIPE_SGIX			= 0x00000002
	PIPE_RECT_SGIX					= 0x00000001
	PIPE_RECT_LIMITS_SGIX				= 0x00000002
	HYPERPIPE_STEREO_SGIX				= 0x00000003
	HYPERPIPE_PIXEL_AVERAGE_SGIX			= 0x00000004
	HYPERPIPE_ID_SGIX				= 0x8030

###############################################################################

# No new tokens
# Extension #308
MESA_agp_offset enum:

###############################################################################

# Extension #328
EXT_fbconfig_packed_float enum:
	RGBA_UNSIGNED_FLOAT_TYPE_EXT			= 0x20B1
	RGBA_UNSIGNED_FLOAT_BIT_EXT			= 0x00000008

###############################################################################

# Extension #337
EXT_framebuffer_sRGB enum:
	FRAMEBUFFER_SRGB_CAPABLE_EXT			= 0x20B2

###############################################################################

# Extension #344
EXT_texture_from_pixmap enum:
	TEXTURE_1D_BIT_EXT				= 0x00000001
	TEXTURE_2D_BIT_EXT				= 0x00000002
	TEXTURE_RECTANGLE_BIT_EXT			= 0x00000004
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

###############################################################################

# Extension #347
NV_present_video enum:
	NUM_VIDEO_SLOTS_NV				= 0x20F0

###############################################################################

# Extension #348
NV_video_out enum:
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

###############################################################################

# No new tokens
# Extension #350
NV_swap_group enum:

###############################################################################

# Extension #374
NV_video_capture enum:
	DEVICE_ID_NV					= 0x20CD
	UNIQUE_ID_NV					= 0x20CE
	NUM_VIDEO_CAPTURE_SLOTS_NV			= 0x20CF

###############################################################################

# Extension #375
EXT_swap_control enum:
	SWAP_INTERVAL_EXT				= 0x20F1
	MAX_SWAP_INTERVAL_EXT				= 0x20F2

###############################################################################

# No new tokens
# Extension #376
NV_copy_image enum:

###############################################################################

# Extension #384
INTEL_swap_event enum:
	BUFFER_SWAP_COMPLETE_INTEL_MASK			= 0x04000000
	EXCHANGE_COMPLETE_INTEL				= 0x8180
	COPY_COMPLETE_INTEL				= 0x8181
	FLIP_COMPLETE_INTEL				= 0x8182

###############################################################################

# Extension #393
NV_multisample_coverage enum:
	COVERAGE_SAMPLES_NV				= 100001
	COLOR_SAMPLES_NV				= 0x20B3

###############################################################################

# Extension #398
AMD_gpu_association enum:
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

###############################################################################

# Extension #399
# All values are shared with WGL and GL
EXT_create_context_es2_profile enum:
	CONTEXT_ES2_PROFILE_BIT_EXT			= 0x00000004
