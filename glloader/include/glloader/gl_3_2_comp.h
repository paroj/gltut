#ifndef GL_3_2_COMP_H
#define GL_3_2_COMP_H


#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include gle after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include gle after including glext.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include gle after including glATI.h
#endif

#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_


typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#ifdef WIN32

#ifndef APIENTRY
	#define GLE_REMOVE_APIENTRY
	#if defined(__MINGW32__)
		#define APIENTRY __stdcall
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#define APIENTRY __stdcall
	#else
		#define APIENTRY
	#endif
#endif //APIENTRY

#endif //WIN32

#ifdef GLE_FUNCPTR
#undef GLE_FUNCPTR
#endif //GLE_FUNCPTR

#if defined(_WIN32)
	#define GLE_FUNCPTR APIENTRY
#else
	#define GLE_FUNCPTR
#endif

#include <stddef.h>
#ifndef GL_VERSION_2_0
/* GL type for program/shader text */
typedef char GLchar;
#endif
#ifndef GL_VERSION_1_5
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif
#ifndef GL_ARB_vertex_buffer_object
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
#endif
#ifndef GL_ARB_shader_objects
/* GL types for program/shader text and shader object handles */
typedef char GLcharARB;
typedef unsigned int GLhandleARB;
#endif
/* GL type for "half" precision (s10e5) float data in host memory */
#ifndef GL_ARB_half_float_pixel
typedef unsigned short GLhalfARB;
#endif
#ifndef GL_NV_half_float
typedef unsigned short GLhalfNV;
#endif
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
#ifndef GL_EXT_timer_query
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
#endif
#ifndef GL_ARB_sync
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef struct __GLsync *GLsync;
#endif
#ifndef GL_ARB_cl_event
/* These incomplete types let us declare types compatible with OpenCL's cl_context and cl_event */
struct _cl_context;
struct _cl_event;
#endif
#ifndef GL_ARB_debug_output
typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,GLvoid *userParam);
#endif
#ifndef GL_AMD_debug_output
typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,GLvoid *userParam);
#endif
#ifndef GL_NV_vdpau_interop
typedef GLintptr GLvdpauSurfaceNV;
#endif

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


extern int glext_ARB_imaging;
extern int glext_ARB_multitexture;
extern int glext_ARB_transpose_matrix;
extern int glext_ARB_multisample;
extern int glext_ARB_texture_env_add;
extern int glext_ARB_texture_cube_map;
extern int glext_ARB_texture_compression;
extern int glext_ARB_texture_border_clamp;
extern int glext_ARB_point_parameters;
extern int glext_ARB_vertex_blend;
extern int glext_ARB_matrix_palette;
extern int glext_ARB_texture_env_combine;
extern int glext_ARB_texture_env_crossbar;
extern int glext_ARB_texture_env_dot3;
extern int glext_ARB_texture_mirrored_repeat;
extern int glext_ARB_depth_texture;
extern int glext_ARB_shadow;
extern int glext_ARB_shadow_ambient;
extern int glext_ARB_window_pos;
extern int glext_ARB_vertex_program;
extern int glext_ARB_fragment_program;
extern int glext_ARB_vertex_buffer_object;
extern int glext_ARB_occlusion_query;
extern int glext_ARB_shader_objects;
extern int glext_ARB_vertex_shader;
extern int glext_ARB_fragment_shader;
extern int glext_ARB_shading_language_100;
extern int glext_ARB_texture_non_power_of_two;
extern int glext_ARB_point_sprite;
extern int glext_ARB_fragment_program_shadow;
extern int glext_ARB_draw_buffers;
extern int glext_ARB_texture_rectangle;
extern int glext_ARB_color_buffer_float;
extern int glext_ARB_half_float_pixel;
extern int glext_ARB_texture_float;
extern int glext_ARB_pixel_buffer_object;
extern int glext_ARB_depth_buffer_float;
extern int glext_ARB_draw_instanced;
extern int glext_ARB_framebuffer_object;
extern int glext_ARB_framebuffer_sRGB;
extern int glext_ARB_geometry_shader4;
extern int glext_ARB_half_float_vertex;
extern int glext_ARB_instanced_arrays;
extern int glext_ARB_map_buffer_range;
extern int glext_ARB_texture_buffer_object;
extern int glext_ARB_texture_compression_rgtc;
extern int glext_ARB_texture_rg;
extern int glext_ARB_vertex_array_object;
extern int glext_ARB_uniform_buffer_object;
extern int glext_ARB_compatibility;
extern int glext_ARB_copy_buffer;
extern int glext_ARB_shader_texture_lod;
extern int glext_ARB_depth_clamp;
extern int glext_ARB_draw_elements_base_vertex;
extern int glext_ARB_fragment_coord_conventions;
extern int glext_ARB_provoking_vertex;
extern int glext_ARB_seamless_cube_map;
extern int glext_ARB_sync;
extern int glext_ARB_texture_multisample;
extern int glext_ARB_vertex_array_bgra;
extern int glext_ARB_draw_buffers_blend;
extern int glext_ARB_sample_shading;
extern int glext_ARB_texture_cube_map_array;
extern int glext_ARB_texture_gather;
extern int glext_ARB_texture_query_lod;
extern int glext_ARB_shading_language_include;
extern int glext_ARB_texture_compression_bptc;
extern int glext_ARB_blend_func_extended;
extern int glext_ARB_explicit_attrib_location;
extern int glext_ARB_occlusion_query2;
extern int glext_ARB_sampler_objects;
extern int glext_ARB_shader_bit_encoding;
extern int glext_ARB_texture_rgb10_a2ui;
extern int glext_ARB_texture_swizzle;
extern int glext_ARB_timer_query;
extern int glext_ARB_vertex_type_2_10_10_10_rev;
extern int glext_ARB_draw_indirect;
extern int glext_ARB_gpu_shader5;
extern int glext_ARB_gpu_shader_fp64;
extern int glext_ARB_shader_subroutine;
extern int glext_ARB_tessellation_shader;
extern int glext_ARB_texture_buffer_object_rgb32;
extern int glext_ARB_transform_feedback2;
extern int glext_ARB_transform_feedback3;
extern int glext_ARB_ES2_compatibility;
extern int glext_ARB_get_program_binary;
extern int glext_ARB_separate_shader_objects;
extern int glext_ARB_shader_precision;
extern int glext_ARB_vertex_attrib_64bit;
extern int glext_ARB_viewport_array;
extern int glext_ARB_cl_event;
extern int glext_ARB_debug_output;
extern int glext_ARB_robustness;
extern int glext_ARB_shader_stencil_export;
extern int glext_EXT_abgr;
extern int glext_EXT_blend_color;
extern int glext_EXT_polygon_offset;
extern int glext_EXT_texture;
extern int glext_EXT_texture3D;
extern int glext_SGIS_texture_filter4;
extern int glext_EXT_subtexture;
extern int glext_EXT_copy_texture;
extern int glext_EXT_histogram;
extern int glext_EXT_convolution;
extern int glext_SGI_color_matrix;
extern int glext_SGI_color_table;
extern int glext_SGIS_pixel_texture;
extern int glext_SGIX_pixel_texture;
extern int glext_SGIS_texture4D;
extern int glext_SGI_texture_color_table;
extern int glext_EXT_cmyka;
extern int glext_EXT_texture_object;
extern int glext_SGIS_detail_texture;
extern int glext_SGIS_sharpen_texture;
extern int glext_EXT_packed_pixels;
extern int glext_SGIS_texture_lod;
extern int glext_SGIS_multisample;
extern int glext_EXT_rescale_normal;
extern int glext_EXT_vertex_array;
extern int glext_EXT_misc_attribute;
extern int glext_SGIS_generate_mipmap;
extern int glext_SGIX_clipmap;
extern int glext_SGIX_shadow;
extern int glext_SGIS_texture_edge_clamp;
extern int glext_SGIS_texture_border_clamp;
extern int glext_EXT_blend_minmax;
extern int glext_EXT_blend_subtract;
extern int glext_EXT_blend_logic_op;
extern int glext_SGIX_interlace;
extern int glext_SGIX_pixel_tiles;
extern int glext_SGIS_texture_select;
extern int glext_SGIX_sprite;
extern int glext_SGIX_texture_multi_buffer;
extern int glext_EXT_point_parameters;
extern int glext_SGIS_point_parameters;
extern int glext_SGIX_instruments;
extern int glext_SGIX_texture_scale_bias;
extern int glext_SGIX_framezoom;
extern int glext_SGIX_tag_sample_buffer;
extern int glext_FfdMaskSGIX;
extern int glext_SGIX_polynomial_ffd;
extern int glext_SGIX_reference_plane;
extern int glext_SGIX_flush_raster;
extern int glext_SGIX_depth_texture;
extern int glext_SGIS_fog_function;
extern int glext_SGIX_fog_offset;
extern int glext_HP_image_transform;
extern int glext_HP_convolution_border_modes;
extern int glext_INGR_palette_buffer;
extern int glext_SGIX_texture_add_env;
extern int glext_EXT_color_subtable;
extern int glext_PGI_vertex_hints;
extern int glext_PGI_misc_hints;
extern int glext_EXT_paletted_texture;
extern int glext_EXT_clip_volume_hint;
extern int glext_SGIX_list_priority;
extern int glext_SGIX_ir_instrument1;
extern int glext_SGIX_calligraphic_fragment;
extern int glext_SGIX_texture_lod_bias;
extern int glext_SGIX_shadow_ambient;
extern int glext_EXT_index_texture;
extern int glext_EXT_index_material;
extern int glext_EXT_index_func;
extern int glext_EXT_index_array_formats;
extern int glext_EXT_compiled_vertex_array;
extern int glext_EXT_cull_vertex;
extern int glext_SGIX_ycrcb;
extern int glext_SGIX_fragment_lighting;
extern int glext_IBM_rasterpos_clip;
extern int glext_HP_texture_lighting;
extern int glext_EXT_draw_range_elements;
extern int glext_WIN_phong_shading;
extern int glext_WIN_specular_fog;
extern int glext_EXT_light_texture;
extern int glext_SGIX_blend_alpha_minmax;
extern int glext_SGIX_impact_pixel_texture;
extern int glext_EXT_bgra;
extern int glext_SGIX_async;
extern int glext_SGIX_async_pixel;
extern int glext_SGIX_async_histogram;
extern int glext_INTEL_texture_scissor;
extern int glext_INTEL_parallel_arrays;
extern int glext_HP_occlusion_test;
extern int glext_EXT_pixel_transform;
extern int glext_EXT_pixel_transform_color_table;
extern int glext_EXT_shared_texture_palette;
extern int glext_EXT_separate_specular_color;
extern int glext_EXT_secondary_color;
extern int glext_EXT_texture_perturb_normal;
extern int glext_EXT_multi_draw_arrays;
extern int glext_EXT_fog_coord;
extern int glext_REND_screen_coordinates;
extern int glext_EXT_coordinate_frame;
extern int glext_EXT_texture_env_combine;
extern int glext_APPLE_specular_vector;
extern int glext_APPLE_transform_hint;
extern int glext_SGIX_fog_scale;
extern int glext_SUNX_constant_data;
extern int glext_SUN_global_alpha;
extern int glext_SUN_triangle_list;
extern int glext_SUN_vertex;
extern int glext_EXT_blend_func_separate;
extern int glext_INGR_color_clamp;
extern int glext_INGR_interlace_read;
extern int glext_EXT_stencil_wrap;
extern int glext_EXT_422_pixels;
extern int glext_NV_texgen_reflection;
extern int glext_EXT_texture_cube_map;
extern int glext_SUN_convolution_border_modes;
extern int glext_EXT_texture_env_add;
extern int glext_EXT_texture_lod_bias;
extern int glext_EXT_texture_filter_anisotropic;
extern int glext_EXT_vertex_weighting;
extern int glext_NV_light_max_exponent;
extern int glext_NV_vertex_array_range;
extern int glext_NV_register_combiners;
extern int glext_NV_fog_distance;
extern int glext_NV_texgen_emboss;
extern int glext_NV_blend_square;
extern int glext_NV_texture_env_combine4;
extern int glext_MESA_resize_buffers;
extern int glext_MESA_window_pos;
extern int glext_EXT_texture_compression_s3tc;
extern int glext_IBM_cull_vertex;
extern int glext_IBM_multimode_draw_arrays;
extern int glext_IBM_vertex_array_lists;
extern int glext_SGIX_subsample;
extern int glext_SGIX_ycrcb_subsample;
extern int glext_SGIX_ycrcba;
extern int glext_SGI_depth_pass_instrument;
extern int glext_3DFX_texture_compression_FXT1;
extern int glext_3DFX_multisample;
extern int glext_3DFX_tbuffer;
extern int glext_EXT_multisample;
extern int glext_SGIX_vertex_preclip;
extern int glext_SGIX_convolution_accuracy;
extern int glext_SGIX_resample;
extern int glext_SGIS_point_line_texgen;
extern int glext_SGIS_texture_color_mask;
extern int glext_EXT_texture_env_dot3;
extern int glext_ATI_texture_mirror_once;
extern int glext_NV_fence;
extern int glext_IBM_texture_mirrored_repeat;
extern int glext_NV_evaluators;
extern int glext_NV_packed_depth_stencil;
extern int glext_NV_register_combiners2;
extern int glext_NV_texture_compression_vtc;
extern int glext_NV_texture_rectangle;
extern int glext_NV_texture_shader;
extern int glext_NV_texture_shader2;
extern int glext_NV_vertex_array_range2;
extern int glext_NV_vertex_program;
extern int glext_SGIX_texture_coordinate_clamp;
extern int glext_SGIX_scalebias_hint;
extern int glext_OML_interlace;
extern int glext_OML_subsample;
extern int glext_OML_resample;
extern int glext_NV_copy_depth_to_color;
extern int glext_ATI_envmap_bumpmap;
extern int glext_ATI_fragment_shader;
extern int glext_ATI_pn_triangles;
extern int glext_ATI_vertex_array_object;
extern int glext_EXT_vertex_shader;
extern int glext_ATI_vertex_streams;
extern int glext_ATI_element_array;
extern int glext_SUN_mesh_array;
extern int glext_SUN_slice_accum;
extern int glext_NV_multisample_filter_hint;
extern int glext_NV_depth_clamp;
extern int glext_NV_occlusion_query;
extern int glext_NV_point_sprite;
extern int glext_NV_texture_shader3;
extern int glext_NV_vertex_program1_1;
extern int glext_EXT_shadow_funcs;
extern int glext_EXT_stencil_two_side;
extern int glext_ATI_text_fragment_shader;
extern int glext_APPLE_client_storage;
extern int glext_APPLE_element_array;
extern int glext_APPLE_fence;
extern int glext_APPLE_vertex_array_object;
extern int glext_APPLE_vertex_array_range;
extern int glext_APPLE_ycbcr_422;
extern int glext_S3_s3tc;
extern int glext_ATI_draw_buffers;
extern int glext_ATI_pixel_format_float;
extern int glext_ATI_texture_env_combine3;
extern int glext_ATI_texture_float;
extern int glext_NV_float_buffer;
extern int glext_NV_fragment_program;
extern int glext_NV_half_float;
extern int glext_NV_pixel_data_range;
extern int glext_NV_primitive_restart;
extern int glext_NV_texture_expand_normal;
extern int glext_NV_vertex_program2;
extern int glext_ATI_map_object_buffer;
extern int glext_ATI_separate_stencil;
extern int glext_ATI_vertex_attrib_array_object;
extern int glext_OES_read_format;
extern int glext_EXT_depth_bounds_test;
extern int glext_EXT_texture_mirror_clamp;
extern int glext_EXT_blend_equation_separate;
extern int glext_MESA_pack_invert;
extern int glext_MESA_ycbcr_texture;
extern int glext_EXT_pixel_buffer_object;
extern int glext_NV_fragment_program_option;
extern int glext_NV_fragment_program2;
extern int glext_NV_vertex_program2_option;
extern int glext_NV_vertex_program3;
extern int glext_EXT_framebuffer_object;
extern int glext_GREMEDY_string_marker;
extern int glext_EXT_packed_depth_stencil;
extern int glext_EXT_stencil_clear_tag;
extern int glext_EXT_texture_sRGB;
extern int glext_EXT_framebuffer_blit;
extern int glext_EXT_framebuffer_multisample;
extern int glext_MESAX_texture_stack;
extern int glext_EXT_timer_query;
extern int glext_EXT_gpu_program_parameters;
extern int glext_APPLE_flush_buffer_range;
extern int glext_NV_gpu_program4;
extern int glext_NV_geometry_program4;
extern int glext_EXT_geometry_shader4;
extern int glext_NV_vertex_program4;
extern int glext_EXT_gpu_shader4;
extern int glext_EXT_draw_instanced;
extern int glext_EXT_packed_float;
extern int glext_EXT_texture_array;
extern int glext_EXT_texture_buffer_object;
extern int glext_EXT_texture_compression_latc;
extern int glext_EXT_texture_compression_rgtc;
extern int glext_EXT_texture_shared_exponent;
extern int glext_NV_depth_buffer_float;
extern int glext_NV_fragment_program4;
extern int glext_NV_framebuffer_multisample_coverage;
extern int glext_EXT_framebuffer_sRGB;
extern int glext_NV_geometry_shader4;
extern int glext_NV_parameter_buffer_object;
extern int glext_EXT_draw_buffers2;
extern int glext_NV_transform_feedback;
extern int glext_EXT_bindable_uniform;
extern int glext_EXT_texture_integer;
extern int glext_GREMEDY_frame_terminator;
extern int glext_NV_conditional_render;
extern int glext_NV_present_video;
extern int glext_EXT_transform_feedback;
extern int glext_EXT_direct_state_access;
extern int glext_EXT_vertex_array_bgra;
extern int glext_EXT_texture_swizzle;
extern int glext_NV_explicit_multisample;
extern int glext_NV_transform_feedback2;
extern int glext_ATI_meminfo;
extern int glext_AMD_performance_monitor;
extern int glext_AMD_texture_texture4;
extern int glext_AMD_vertex_shader_tesselator;
extern int glext_EXT_provoking_vertex;
extern int glext_EXT_texture_snorm;
extern int glext_AMD_draw_buffers_blend;
extern int glext_APPLE_texture_range;
extern int glext_APPLE_float_pixels;
extern int glext_APPLE_vertex_program_evaluators;
extern int glext_APPLE_aux_depth_stencil;
extern int glext_APPLE_object_purgeable;
extern int glext_APPLE_row_bytes;
extern int glext_APPLE_rgb_422;
extern int glext_NV_video_capture;
extern int glext_NV_copy_image;
extern int glext_EXT_separate_shader_objects;
extern int glext_NV_parameter_buffer_object2;
extern int glext_NV_shader_buffer_load;
extern int glext_NV_vertex_buffer_unified_memory;
extern int glext_NV_texture_barrier;
extern int glext_AMD_shader_stencil_export;
extern int glext_AMD_seamless_cubemap_per_texture;
extern int glext_AMD_conservative_depth;
extern int glext_EXT_shader_image_load_store;
extern int glext_EXT_vertex_attrib_64bit;
extern int glext_NV_gpu_program5;
extern int glext_NV_gpu_shader5;
extern int glext_NV_shader_buffer_store;
extern int glext_NV_tessellation_program5;
extern int glext_NV_vertex_attrib_integer_64bit;
extern int glext_NV_multisample_coverage;
extern int glext_AMD_name_gen_delete;
extern int glext_AMD_debug_output;
extern int glext_NV_vdpau_interop;
extern int glext_AMD_transform_feedback3_lines_triangles;


/******************************
* Version: 1.1
******************************/

#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_POINTS 0x0000
#define GL_LINES 0x0001
#define GL_LINE_LOOP 0x0002
#define GL_LINE_STRIP 0x0003
#define GL_TRIANGLES 0x0004
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_NEVER 0x0200
#define GL_LESS 0x0201
#define GL_EQUAL 0x0202
#define GL_LEQUAL 0x0203
#define GL_GREATER 0x0204
#define GL_NOTEQUAL 0x0205
#define GL_GEQUAL 0x0206
#define GL_ALWAYS 0x0207
#define GL_ZERO 0
#define GL_ONE 1
#define GL_SRC_COLOR 0x0300
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_DST_ALPHA 0x0304
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_DST_COLOR 0x0306
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_NONE 0
#define GL_FRONT_LEFT 0x0400
#define GL_FRONT_RIGHT 0x0401
#define GL_BACK_LEFT 0x0402
#define GL_BACK_RIGHT 0x0403
#define GL_FRONT 0x0404
#define GL_BACK 0x0405
#define GL_LEFT 0x0406
#define GL_RIGHT 0x0407
#define GL_FRONT_AND_BACK 0x0408
#define GL_NO_ERROR 0
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_OUT_OF_MEMORY 0x0505
#define GL_CW 0x0900
#define GL_CCW 0x0901
#define GL_POINT_SIZE 0x0B11
#define GL_POINT_SIZE_RANGE 0x0B12
#define GL_POINT_SIZE_GRANULARITY 0x0B13
#define GL_LINE_SMOOTH 0x0B20
#define GL_LINE_WIDTH 0x0B21
#define GL_LINE_WIDTH_RANGE 0x0B22
#define GL_LINE_WIDTH_GRANULARITY 0x0B23
#define GL_POLYGON_SMOOTH 0x0B41
#define GL_CULL_FACE 0x0B44
#define GL_CULL_FACE_MODE 0x0B45
#define GL_FRONT_FACE 0x0B46
#define GL_DEPTH_RANGE 0x0B70
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_WRITEMASK 0x0B72
#define GL_DEPTH_CLEAR_VALUE 0x0B73
#define GL_DEPTH_FUNC 0x0B74
#define GL_STENCIL_TEST 0x0B90
#define GL_STENCIL_CLEAR_VALUE 0x0B91
#define GL_STENCIL_FUNC 0x0B92
#define GL_STENCIL_VALUE_MASK 0x0B93
#define GL_STENCIL_FAIL 0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF 0x0B97
#define GL_STENCIL_WRITEMASK 0x0B98
#define GL_VIEWPORT 0x0BA2
#define GL_DITHER 0x0BD0
#define GL_BLEND_DST 0x0BE0
#define GL_BLEND_SRC 0x0BE1
#define GL_BLEND 0x0BE2
#define GL_LOGIC_OP_MODE 0x0BF0
#define GL_COLOR_LOGIC_OP 0x0BF2
#define GL_DRAW_BUFFER 0x0C01
#define GL_READ_BUFFER 0x0C02
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11
#define GL_COLOR_CLEAR_VALUE 0x0C22
#define GL_COLOR_WRITEMASK 0x0C23
#define GL_DOUBLEBUFFER 0x0C32
#define GL_STEREO 0x0C33
#define GL_LINE_SMOOTH_HINT 0x0C52
#define GL_POLYGON_SMOOTH_HINT 0x0C53
#define GL_UNPACK_SWAP_BYTES 0x0CF0
#define GL_UNPACK_LSB_FIRST 0x0CF1
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#define GL_UNPACK_SKIP_ROWS 0x0CF3
#define GL_UNPACK_SKIP_PIXELS 0x0CF4
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_PACK_SWAP_BYTES 0x0D00
#define GL_PACK_LSB_FIRST 0x0D01
#define GL_PACK_ROW_LENGTH 0x0D02
#define GL_PACK_SKIP_ROWS 0x0D03
#define GL_PACK_SKIP_PIXELS 0x0D04
#define GL_PACK_ALIGNMENT 0x0D05
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_VIEWPORT_DIMS 0x0D3A
#define GL_SUBPIXEL_BITS 0x0D50
#define GL_TEXTURE_1D 0x0DE0
#define GL_TEXTURE_2D 0x0DE1
#define GL_POLYGON_OFFSET_UNITS 0x2A00
#define GL_POLYGON_OFFSET_POINT 0x2A01
#define GL_POLYGON_OFFSET_LINE 0x2A02
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_POLYGON_OFFSET_FACTOR 0x8038
#define GL_TEXTURE_BINDING_1D 0x8068
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_TEXTURE_WIDTH 0x1000
#define GL_TEXTURE_HEIGHT 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_TEXTURE_RED_SIZE 0x805C
#define GL_TEXTURE_GREEN_SIZE 0x805D
#define GL_TEXTURE_BLUE_SIZE 0x805E
#define GL_TEXTURE_ALPHA_SIZE 0x805F
#define GL_DONT_CARE 0x1100
#define GL_FASTEST 0x1101
#define GL_NICEST 0x1102
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_DOUBLE 0x140A
#define GL_CLEAR 0x1500
#define GL_AND 0x1501
#define GL_AND_REVERSE 0x1502
#define GL_COPY 0x1503
#define GL_AND_INVERTED 0x1504
#define GL_NOOP 0x1505
#define GL_XOR 0x1506
#define GL_OR 0x1507
#define GL_NOR 0x1508
#define GL_EQUIV 0x1509
#define GL_INVERT 0x150A
#define GL_OR_REVERSE 0x150B
#define GL_COPY_INVERTED 0x150C
#define GL_OR_INVERTED 0x150D
#define GL_NAND 0x150E
#define GL_SET 0x150F
#define GL_TEXTURE 0x1702
#define GL_COLOR 0x1800
#define GL_DEPTH 0x1801
#define GL_STENCIL 0x1802
#define GL_STENCIL_INDEX 0x1901
#define GL_DEPTH_COMPONENT 0x1902
#define GL_RED 0x1903
#define GL_GREEN 0x1904
#define GL_BLUE 0x1905
#define GL_ALPHA 0x1906
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_POINT 0x1B00
#define GL_LINE 0x1B01
#define GL_FILL 0x1B02
#define GL_KEEP 0x1E00
#define GL_REPLACE 0x1E01
#define GL_INCR 0x1E02
#define GL_DECR 0x1E03
#define GL_VENDOR 0x1F00
#define GL_RENDERER 0x1F01
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_PROXY_TEXTURE_1D 0x8063
#define GL_PROXY_TEXTURE_2D 0x8064
#define GL_REPEAT 0x2901
#define GL_R3_G3_B2 0x2A10
#define GL_RGB4 0x804F
#define GL_RGB5 0x8050
#define GL_RGB8 0x8051
#define GL_RGB10 0x8052
#define GL_RGB12 0x8053
#define GL_RGB16 0x8054
#define GL_RGBA2 0x8055
#define GL_RGBA4 0x8056
#define GL_RGB5_A1 0x8057
#define GL_RGBA8 0x8058
#define GL_RGB10_A2 0x8059
#define GL_RGBA12 0x805A
#define GL_RGBA16 0x805B
#define GL_CURRENT_BIT 0x00000001
#define GL_POINT_BIT 0x00000002
#define GL_LINE_BIT 0x00000004
#define GL_POLYGON_BIT 0x00000008
#define GL_POLYGON_STIPPLE_BIT 0x00000010
#define GL_PIXEL_MODE_BIT 0x00000020
#define GL_LIGHTING_BIT 0x00000040
#define GL_FOG_BIT 0x00000080
#define GL_ACCUM_BUFFER_BIT 0x00000200
#define GL_VIEWPORT_BIT 0x00000800
#define GL_TRANSFORM_BIT 0x00001000
#define GL_ENABLE_BIT 0x00002000
#define GL_HINT_BIT 0x00008000
#define GL_EVAL_BIT 0x00010000
#define GL_LIST_BIT 0x00020000
#define GL_TEXTURE_BIT 0x00040000
#define GL_SCISSOR_BIT 0x00080000
#define GL_ALL_ATTRIB_BITS 0xFFFFFFFF
#define GL_CLIENT_PIXEL_STORE_BIT 0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT 0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS 0xFFFFFFFF
#define GL_QUADS 0x0007
#define GL_QUAD_STRIP 0x0008
#define GL_POLYGON 0x0009
#define GL_ACCUM 0x0100
#define GL_LOAD 0x0101
#define GL_RETURN 0x0102
#define GL_MULT 0x0103
#define GL_ADD 0x0104
#define GL_AUX0 0x0409
#define GL_AUX1 0x040A
#define GL_AUX2 0x040B
#define GL_AUX3 0x040C
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_2D 0x0600
#define GL_3D 0x0601
#define GL_3D_COLOR 0x0602
#define GL_3D_COLOR_TEXTURE 0x0603
#define GL_4D_COLOR_TEXTURE 0x0604
#define GL_PASS_THROUGH_TOKEN 0x0700
#define GL_POINT_TOKEN 0x0701
#define GL_LINE_TOKEN 0x0702
#define GL_POLYGON_TOKEN 0x0703
#define GL_BITMAP_TOKEN 0x0704
#define GL_DRAW_PIXEL_TOKEN 0x0705
#define GL_COPY_PIXEL_TOKEN 0x0706
#define GL_LINE_RESET_TOKEN 0x0707
#define GL_EXP 0x0800
#define GL_EXP2 0x0801
#define GL_COEFF 0x0A00
#define GL_ORDER 0x0A01
#define GL_DOMAIN 0x0A02
#define GL_PIXEL_MAP_I_TO_I 0x0C70
#define GL_PIXEL_MAP_S_TO_S 0x0C71
#define GL_PIXEL_MAP_I_TO_R 0x0C72
#define GL_PIXEL_MAP_I_TO_G 0x0C73
#define GL_PIXEL_MAP_I_TO_B 0x0C74
#define GL_PIXEL_MAP_I_TO_A 0x0C75
#define GL_PIXEL_MAP_R_TO_R 0x0C76
#define GL_PIXEL_MAP_G_TO_G 0x0C77
#define GL_PIXEL_MAP_B_TO_B 0x0C78
#define GL_PIXEL_MAP_A_TO_A 0x0C79
#define GL_VERTEX_ARRAY_POINTER 0x808E
#define GL_NORMAL_ARRAY_POINTER 0x808F
#define GL_COLOR_ARRAY_POINTER 0x8090
#define GL_INDEX_ARRAY_POINTER 0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER 0x8093
#define GL_FEEDBACK_BUFFER_POINTER 0x0DF0
#define GL_SELECTION_BUFFER_POINTER 0x0DF3
#define GL_CURRENT_COLOR 0x0B00
#define GL_CURRENT_INDEX 0x0B01
#define GL_CURRENT_NORMAL 0x0B02
#define GL_CURRENT_TEXTURE_COORDS 0x0B03
#define GL_CURRENT_RASTER_COLOR 0x0B04
#define GL_CURRENT_RASTER_INDEX 0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS 0x0B06
#define GL_CURRENT_RASTER_POSITION 0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID 0x0B08
#define GL_CURRENT_RASTER_DISTANCE 0x0B09
#define GL_POINT_SMOOTH 0x0B10
#define GL_LINE_STIPPLE 0x0B24
#define GL_LINE_STIPPLE_PATTERN 0x0B25
#define GL_LINE_STIPPLE_REPEAT 0x0B26
#define GL_LIST_MODE 0x0B30
#define GL_MAX_LIST_NESTING 0x0B31
#define GL_LIST_BASE 0x0B32
#define GL_LIST_INDEX 0x0B33
#define GL_POLYGON_MODE 0x0B40
#define GL_POLYGON_STIPPLE 0x0B42
#define GL_EDGE_FLAG 0x0B43
#define GL_LIGHTING 0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER 0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#define GL_LIGHT_MODEL_AMBIENT 0x0B53
#define GL_SHADE_MODEL 0x0B54
#define GL_COLOR_MATERIAL_FACE 0x0B55
#define GL_COLOR_MATERIAL_PARAMETER 0x0B56
#define GL_COLOR_MATERIAL 0x0B57
#define GL_FOG 0x0B60
#define GL_FOG_INDEX 0x0B61
#define GL_FOG_DENSITY 0x0B62
#define GL_FOG_START 0x0B63
#define GL_FOG_END 0x0B64
#define GL_FOG_MODE 0x0B65
#define GL_FOG_COLOR 0x0B66
#define GL_ACCUM_CLEAR_VALUE 0x0B80
#define GL_MATRIX_MODE 0x0BA0
#define GL_NORMALIZE 0x0BA1
#define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#define GL_PROJECTION_STACK_DEPTH 0x0BA4
#define GL_TEXTURE_STACK_DEPTH 0x0BA5
#define GL_MODELVIEW_MATRIX 0x0BA6
#define GL_PROJECTION_MATRIX 0x0BA7
#define GL_TEXTURE_MATRIX 0x0BA8
#define GL_ATTRIB_STACK_DEPTH 0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH 0x0BB1
#define GL_ALPHA_TEST 0x0BC0
#define GL_ALPHA_TEST_FUNC 0x0BC1
#define GL_ALPHA_TEST_REF 0x0BC2
#define GL_INDEX_LOGIC_OP 0x0BF1
#define GL_LOGIC_OP 0x0BF1
#define GL_AUX_BUFFERS 0x0C00
#define GL_INDEX_CLEAR_VALUE 0x0C20
#define GL_INDEX_WRITEMASK 0x0C21
#define GL_INDEX_MODE 0x0C30
#define GL_RGBA_MODE 0x0C31
#define GL_RENDER_MODE 0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#define GL_POINT_SMOOTH_HINT 0x0C51
#define GL_FOG_HINT 0x0C54
#define GL_TEXTURE_GEN_S 0x0C60
#define GL_TEXTURE_GEN_T 0x0C61
#define GL_TEXTURE_GEN_R 0x0C62
#define GL_TEXTURE_GEN_Q 0x0C63
#define GL_PIXEL_MAP_I_TO_I_SIZE 0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE 0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE 0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE 0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE 0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE 0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE 0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE 0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE 0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE 0x0CB9
#define GL_MAP_COLOR 0x0D10
#define GL_MAP_STENCIL 0x0D11
#define GL_INDEX_SHIFT 0x0D12
#define GL_INDEX_OFFSET 0x0D13
#define GL_RED_SCALE 0x0D14
#define GL_RED_BIAS 0x0D15
#define GL_ZOOM_X 0x0D16
#define GL_ZOOM_Y 0x0D17
#define GL_GREEN_SCALE 0x0D18
#define GL_GREEN_BIAS 0x0D19
#define GL_BLUE_SCALE 0x0D1A
#define GL_BLUE_BIAS 0x0D1B
#define GL_ALPHA_SCALE 0x0D1C
#define GL_ALPHA_BIAS 0x0D1D
#define GL_DEPTH_SCALE 0x0D1E
#define GL_DEPTH_BIAS 0x0D1F
#define GL_MAX_EVAL_ORDER 0x0D30
#define GL_MAX_LIGHTS 0x0D31
#define GL_MAX_CLIP_PLANES 0x0D32
#define GL_MAX_PIXEL_MAP_TABLE 0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH 0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH 0x0D36
#define GL_MAX_NAME_STACK_DEPTH 0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH 0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH 0x0D39
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 0x0D3B
#define GL_INDEX_BITS 0x0D51
#define GL_RED_BITS 0x0D52
#define GL_GREEN_BITS 0x0D53
#define GL_BLUE_BITS 0x0D54
#define GL_ALPHA_BITS 0x0D55
#define GL_DEPTH_BITS 0x0D56
#define GL_STENCIL_BITS 0x0D57
#define GL_ACCUM_RED_BITS 0x0D58
#define GL_ACCUM_GREEN_BITS 0x0D59
#define GL_ACCUM_BLUE_BITS 0x0D5A
#define GL_ACCUM_ALPHA_BITS 0x0D5B
#define GL_NAME_STACK_DEPTH 0x0D70
#define GL_AUTO_NORMAL 0x0D80
#define GL_MAP1_COLOR_4 0x0D90
#define GL_MAP1_INDEX 0x0D91
#define GL_MAP1_NORMAL 0x0D92
#define GL_MAP1_TEXTURE_COORD_1 0x0D93
#define GL_MAP1_TEXTURE_COORD_2 0x0D94
#define GL_MAP1_TEXTURE_COORD_3 0x0D95
#define GL_MAP1_TEXTURE_COORD_4 0x0D96
#define GL_MAP1_VERTEX_3 0x0D97
#define GL_MAP1_VERTEX_4 0x0D98
#define GL_MAP2_COLOR_4 0x0DB0
#define GL_MAP2_INDEX 0x0DB1
#define GL_MAP2_NORMAL 0x0DB2
#define GL_MAP2_TEXTURE_COORD_1 0x0DB3
#define GL_MAP2_TEXTURE_COORD_2 0x0DB4
#define GL_MAP2_TEXTURE_COORD_3 0x0DB5
#define GL_MAP2_TEXTURE_COORD_4 0x0DB6
#define GL_MAP2_VERTEX_3 0x0DB7
#define GL_MAP2_VERTEX_4 0x0DB8
#define GL_MAP1_GRID_DOMAIN 0x0DD0
#define GL_MAP1_GRID_SEGMENTS 0x0DD1
#define GL_MAP2_GRID_DOMAIN 0x0DD2
#define GL_MAP2_GRID_SEGMENTS 0x0DD3
#define GL_FEEDBACK_BUFFER_SIZE 0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE 0x0DF2
#define GL_SELECTION_BUFFER_SIZE 0x0DF4
#define GL_VERTEX_ARRAY 0x8074
#define GL_NORMAL_ARRAY 0x8075
#define GL_COLOR_ARRAY 0x8076
#define GL_INDEX_ARRAY 0x8077
#define GL_TEXTURE_COORD_ARRAY 0x8078
#define GL_EDGE_FLAG_ARRAY 0x8079
#define GL_VERTEX_ARRAY_SIZE 0x807A
#define GL_VERTEX_ARRAY_TYPE 0x807B
#define GL_VERTEX_ARRAY_STRIDE 0x807C
#define GL_NORMAL_ARRAY_TYPE 0x807E
#define GL_NORMAL_ARRAY_STRIDE 0x807F
#define GL_COLOR_ARRAY_SIZE 0x8081
#define GL_COLOR_ARRAY_TYPE 0x8082
#define GL_COLOR_ARRAY_STRIDE 0x8083
#define GL_INDEX_ARRAY_TYPE 0x8085
#define GL_INDEX_ARRAY_STRIDE 0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE 0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE 0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE 0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE 0x808C
#define GL_TEXTURE_COMPONENTS 0x1003
#define GL_TEXTURE_BORDER 0x1005
#define GL_TEXTURE_LUMINANCE_SIZE 0x8060
#define GL_TEXTURE_INTENSITY_SIZE 0x8061
#define GL_TEXTURE_PRIORITY 0x8066
#define GL_TEXTURE_RESIDENT 0x8067
#define GL_AMBIENT 0x1200
#define GL_DIFFUSE 0x1201
#define GL_SPECULAR 0x1202
#define GL_POSITION 0x1203
#define GL_SPOT_DIRECTION 0x1204
#define GL_SPOT_EXPONENT 0x1205
#define GL_SPOT_CUTOFF 0x1206
#define GL_CONSTANT_ATTENUATION 0x1207
#define GL_LINEAR_ATTENUATION 0x1208
#define GL_QUADRATIC_ATTENUATION 0x1209
#define GL_COMPILE 0x1300
#define GL_COMPILE_AND_EXECUTE 0x1301
#define GL_2_BYTES 0x1407
#define GL_3_BYTES 0x1408
#define GL_4_BYTES 0x1409
#define GL_EMISSION 0x1600
#define GL_SHININESS 0x1601
#define GL_AMBIENT_AND_DIFFUSE 0x1602
#define GL_COLOR_INDEXES 0x1603
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define GL_COLOR_INDEX 0x1900
#define GL_LUMINANCE 0x1909
#define GL_LUMINANCE_ALPHA 0x190A
#define GL_BITMAP 0x1A00
#define GL_RENDER 0x1C00
#define GL_FEEDBACK 0x1C01
#define GL_SELECT 0x1C02
#define GL_FLAT 0x1D00
#define GL_SMOOTH 0x1D01
#define GL_S 0x2000
#define GL_T 0x2001
#define GL_R 0x2002
#define GL_Q 0x2003
#define GL_MODULATE 0x2100
#define GL_DECAL 0x2101
#define GL_TEXTURE_ENV_MODE 0x2200
#define GL_TEXTURE_ENV_COLOR 0x2201
#define GL_TEXTURE_ENV 0x2300
#define GL_EYE_LINEAR 0x2400
#define GL_OBJECT_LINEAR 0x2401
#define GL_SPHERE_MAP 0x2402
#define GL_TEXTURE_GEN_MODE 0x2500
#define GL_OBJECT_PLANE 0x2501
#define GL_EYE_PLANE 0x2502
#define GL_CLAMP 0x2900
#define GL_ALPHA4 0x803B
#define GL_ALPHA8 0x803C
#define GL_ALPHA12 0x803D
#define GL_ALPHA16 0x803E
#define GL_LUMINANCE4 0x803F
#define GL_LUMINANCE8 0x8040
#define GL_LUMINANCE12 0x8041
#define GL_LUMINANCE16 0x8042
#define GL_LUMINANCE4_ALPHA4 0x8043
#define GL_LUMINANCE6_ALPHA2 0x8044
#define GL_LUMINANCE8_ALPHA8 0x8045
#define GL_LUMINANCE12_ALPHA4 0x8046
#define GL_LUMINANCE12_ALPHA12 0x8047
#define GL_LUMINANCE16_ALPHA16 0x8048
#define GL_INTENSITY 0x8049
#define GL_INTENSITY4 0x804A
#define GL_INTENSITY8 0x804B
#define GL_INTENSITY12 0x804C
#define GL_INTENSITY16 0x804D
#define GL_V2F 0x2A20
#define GL_V3F 0x2A21
#define GL_C4UB_V2F 0x2A22
#define GL_C4UB_V3F 0x2A23
#define GL_C3F_V3F 0x2A24
#define GL_N3F_V3F 0x2A25
#define GL_C4F_N3F_V3F 0x2A26
#define GL_T2F_V3F 0x2A27
#define GL_T4F_V4F 0x2A28
#define GL_T2F_C4UB_V3F 0x2A29
#define GL_T2F_C3F_V3F 0x2A2A
#define GL_T2F_N3F_V3F 0x2A2B
#define GL_T2F_C4F_N3F_V3F 0x2A2C
#define GL_T4F_C4F_N3F_V4F 0x2A2D
#define GL_CLIP_PLANE0 0x3000
#define GL_CLIP_PLANE1 0x3001
#define GL_CLIP_PLANE2 0x3002
#define GL_CLIP_PLANE3 0x3003
#define GL_CLIP_PLANE4 0x3004
#define GL_CLIP_PLANE5 0x3005
#define GL_LIGHT0 0x4000
#define GL_LIGHT1 0x4001
#define GL_LIGHT2 0x4002
#define GL_LIGHT3 0x4003
#define GL_LIGHT4 0x4004
#define GL_LIGHT5 0x4005
#define GL_LIGHT6 0x4006
#define GL_LIGHT7 0x4007


typedef void (GLE_FUNCPTR * PFNGLCULLFACEPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLFRONTFACEPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLHINTPROC)(GLenum target, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLLINEWIDTHPROC)(GLfloat width);
typedef void (GLE_FUNCPTR * PFNGLPOINTSIZEPROC)(GLfloat size);
typedef void (GLE_FUNCPTR * PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLCLEARPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (GLE_FUNCPTR * PFNGLCLEARSTENCILPROC)(GLint s);
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHPROC)(GLclampd depth);
typedef void (GLE_FUNCPTR * PFNGLSTENCILMASKPROC)(GLuint mask);
typedef void (GLE_FUNCPTR * PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (GLE_FUNCPTR * PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (GLE_FUNCPTR * PFNGLDISABLEPROC)(GLenum cap);
typedef void (GLE_FUNCPTR * PFNGLENABLEPROC)(GLenum cap);
typedef void (GLE_FUNCPTR * PFNGLFINISHPROC)();
typedef void (GLE_FUNCPTR * PFNGLFLUSHPROC)();
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (GLE_FUNCPTR * PFNGLLOGICOPPROC)(GLenum opcode);
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (GLE_FUNCPTR * PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (GLE_FUNCPTR * PFNGLDEPTHFUNCPROC)(GLenum func);
typedef void (GLE_FUNCPTR * PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLREADBUFFERPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *params);
typedef void (GLE_FUNCPTR * PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble *params);
typedef GLenum (GLE_FUNCPTR * PFNGLGETERRORPROC)();
typedef void (GLE_FUNCPTR * PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERVPROC)(GLenum pname, GLint *params);
typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGPROC)(GLenum name);
typedef void (GLE_FUNCPTR * PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint *params);
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDPROC)(GLenum cap);
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEPROC)(GLclampd near, GLclampd far);
typedef void (GLE_FUNCPTR * PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLENDLISTPROC)();
typedef void (GLE_FUNCPTR * PFNGLCALLLISTPROC)(GLuint list);
typedef void (GLE_FUNCPTR * PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const GLvoid *lists);
typedef void (GLE_FUNCPTR * PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
typedef GLuint (GLE_FUNCPTR * PFNGLGENLISTSPROC)(GLsizei range);
typedef void (GLE_FUNCPTR * PFNGLLISTBASEPROC)(GLuint base);
typedef void (GLE_FUNCPTR * PFNGLBEGINPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3BVPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UBVPROC)(const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UIVPROC)(const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3USVPROC)(const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4BVPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVPROC)(const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UIVPROC)(const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4USVPROC)(const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPROC)(GLboolean flag);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGVPROC)(const GLboolean *flag);
typedef void (GLE_FUNCPTR * PFNGLENDPROC)();
typedef void (GLE_FUNCPTR * PFNGLINDEXDPROC)(GLdouble c);
typedef void (GLE_FUNCPTR * PFNGLINDEXDVPROC)(const GLdouble *c);
typedef void (GLE_FUNCPTR * PFNGLINDEXFPROC)(GLfloat c);
typedef void (GLE_FUNCPTR * PFNGLINDEXFVPROC)(const GLfloat *c);
typedef void (GLE_FUNCPTR * PFNGLINDEXIPROC)(GLint c);
typedef void (GLE_FUNCPTR * PFNGLINDEXIVPROC)(const GLint *c);
typedef void (GLE_FUNCPTR * PFNGLINDEXSPROC)(GLshort c);
typedef void (GLE_FUNCPTR * PFNGLINDEXSVPROC)(const GLshort *c);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3BVPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
typedef void (GLE_FUNCPTR * PFNGLRECTDVPROC)(const GLdouble *v1, const GLdouble *v2);
typedef void (GLE_FUNCPTR * PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
typedef void (GLE_FUNCPTR * PFNGLRECTFVPROC)(const GLfloat *v1, const GLfloat *v2);
typedef void (GLE_FUNCPTR * PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
typedef void (GLE_FUNCPTR * PFNGLRECTIVPROC)(const GLint *v1, const GLint *v2);
typedef void (GLE_FUNCPTR * PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
typedef void (GLE_FUNCPTR * PFNGLRECTSVPROC)(const GLshort *v1, const GLshort *v2);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1DPROC)(GLdouble s);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1FPROC)(GLfloat s);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1IPROC)(GLint s);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1SPROC)(GLshort s);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2IPROC)(GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble *equation);
typedef void (GLE_FUNCPTR * PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLFOGFPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLFOGFVPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLFOGIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFOGIVPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
typedef void (GLE_FUNCPTR * PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPOLYGONSTIPPLEPROC)(const GLubyte *mask);
typedef void (GLE_FUNCPTR * PFNGLSHADEMODELPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
typedef void (GLE_FUNCPTR * PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat *buffer);
typedef void (GLE_FUNCPTR * PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint *buffer);
typedef GLint (GLE_FUNCPTR * PFNGLRENDERMODEPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLINITNAMESPROC)();
typedef void (GLE_FUNCPTR * PFNGLLOADNAMEPROC)(GLuint name);
typedef void (GLE_FUNCPTR * PFNGLPASSTHROUGHPROC)(GLfloat token);
typedef void (GLE_FUNCPTR * PFNGLPOPNAMEPROC)();
typedef void (GLE_FUNCPTR * PFNGLPUSHNAMEPROC)(GLuint name);
typedef void (GLE_FUNCPTR * PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (GLE_FUNCPTR * PFNGLCLEARINDEXPROC)(GLfloat c);
typedef void (GLE_FUNCPTR * PFNGLINDEXMASKPROC)(GLuint mask);
typedef void (GLE_FUNCPTR * PFNGLACCUMPROC)(GLenum op, GLfloat value);
typedef void (GLE_FUNCPTR * PFNGLPOPATTRIBPROC)();
typedef void (GLE_FUNCPTR * PFNGLPUSHATTRIBPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
typedef void (GLE_FUNCPTR * PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
typedef void (GLE_FUNCPTR * PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
typedef void (GLE_FUNCPTR * PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1DPROC)(GLdouble u);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1DVPROC)(const GLdouble *u);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1FPROC)(GLfloat u);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1FVPROC)(const GLfloat *u);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2DVPROC)(const GLdouble *u);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2FVPROC)(const GLfloat *u);
typedef void (GLE_FUNCPTR * PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
typedef void (GLE_FUNCPTR * PFNGLEVALPOINT1PROC)(GLint i);
typedef void (GLE_FUNCPTR * PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
typedef void (GLE_FUNCPTR * PFNGLEVALPOINT2PROC)(GLint i, GLint j);
typedef void (GLE_FUNCPTR * PFNGLALPHAFUNCPROC)(GLenum func, GLclampf ref);
typedef void (GLE_FUNCPTR * PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPFVPROC)(GLenum map, GLint mapsize, const GLfloat *values);
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPUIVPROC)(GLenum map, GLint mapsize, const GLuint *values);
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPUSVPROC)(GLenum map, GLint mapsize, const GLushort *values);
typedef void (GLE_FUNCPTR * PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
typedef void (GLE_FUNCPTR * PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble *equation);
typedef void (GLE_FUNCPTR * PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint *v);
typedef void (GLE_FUNCPTR * PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat *values);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint *values);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort *values);
typedef void (GLE_FUNCPTR * PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte *mask);
typedef void (GLE_FUNCPTR * PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint *params);
typedef GLboolean (GLE_FUNCPTR * PFNGLISLISTPROC)(GLuint list);
typedef void (GLE_FUNCPTR * PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLLOADIDENTITYPROC)();
typedef void (GLE_FUNCPTR * PFNGLLOADMATRIXFPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLLOADMATRIXDPROC)(const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXMODEPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLMULTMATRIXFPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMULTMATRIXDPROC)(const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLPOPMATRIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLPUSHMATRIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (GLE_FUNCPTR * PFNGLGETPOINTERVPROC)(GLenum pname, GLvoid* *params);
typedef void (GLE_FUNCPTR * PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
typedef void (GLE_FUNCPTR * PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTEXTUREPROC)(GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLARRAYELEMENTPROC)(GLint i);
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLENABLECLIENTSTATEPROC)(GLenum array);
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef GLboolean (GLE_FUNCPTR * PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint *textures, GLboolean *residences);
typedef void (GLE_FUNCPTR * PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint *textures, const GLclampf *priorities);
typedef void (GLE_FUNCPTR * PFNGLINDEXUBPROC)(GLubyte c);
typedef void (GLE_FUNCPTR * PFNGLINDEXUBVPROC)(const GLubyte *c);
typedef void (GLE_FUNCPTR * PFNGLPOPCLIENTATTRIBPROC)();
typedef void (GLE_FUNCPTR * PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);

extern PFNGLCULLFACEPROC __gleCullFace;
#define glCullFace __gleCullFace
extern PFNGLFRONTFACEPROC __gleFrontFace;
#define glFrontFace __gleFrontFace
extern PFNGLHINTPROC __gleHint;
#define glHint __gleHint
extern PFNGLLINEWIDTHPROC __gleLineWidth;
#define glLineWidth __gleLineWidth
extern PFNGLPOINTSIZEPROC __glePointSize;
#define glPointSize __glePointSize
extern PFNGLPOLYGONMODEPROC __glePolygonMode;
#define glPolygonMode __glePolygonMode
extern PFNGLSCISSORPROC __gleScissor;
#define glScissor __gleScissor
extern PFNGLTEXPARAMETERFPROC __gleTexParameterf;
#define glTexParameterf __gleTexParameterf
extern PFNGLTEXPARAMETERFVPROC __gleTexParameterfv;
#define glTexParameterfv __gleTexParameterfv
extern PFNGLTEXPARAMETERIPROC __gleTexParameteri;
#define glTexParameteri __gleTexParameteri
extern PFNGLTEXPARAMETERIVPROC __gleTexParameteriv;
#define glTexParameteriv __gleTexParameteriv
extern PFNGLTEXIMAGE1DPROC __gleTexImage1D;
#define glTexImage1D __gleTexImage1D
extern PFNGLTEXIMAGE2DPROC __gleTexImage2D;
#define glTexImage2D __gleTexImage2D
extern PFNGLDRAWBUFFERPROC __gleDrawBuffer;
#define glDrawBuffer __gleDrawBuffer
extern PFNGLCLEARPROC __gleClear;
#define glClear __gleClear
extern PFNGLCLEARCOLORPROC __gleClearColor;
#define glClearColor __gleClearColor
extern PFNGLCLEARSTENCILPROC __gleClearStencil;
#define glClearStencil __gleClearStencil
extern PFNGLCLEARDEPTHPROC __gleClearDepth;
#define glClearDepth __gleClearDepth
extern PFNGLSTENCILMASKPROC __gleStencilMask;
#define glStencilMask __gleStencilMask
extern PFNGLCOLORMASKPROC __gleColorMask;
#define glColorMask __gleColorMask
extern PFNGLDEPTHMASKPROC __gleDepthMask;
#define glDepthMask __gleDepthMask
extern PFNGLDISABLEPROC __gleDisable;
#define glDisable __gleDisable
extern PFNGLENABLEPROC __gleEnable;
#define glEnable __gleEnable
extern PFNGLFINISHPROC __gleFinish;
#define glFinish __gleFinish
extern PFNGLFLUSHPROC __gleFlush;
#define glFlush __gleFlush
extern PFNGLBLENDFUNCPROC __gleBlendFunc;
#define glBlendFunc __gleBlendFunc
extern PFNGLLOGICOPPROC __gleLogicOp;
#define glLogicOp __gleLogicOp
extern PFNGLSTENCILFUNCPROC __gleStencilFunc;
#define glStencilFunc __gleStencilFunc
extern PFNGLSTENCILOPPROC __gleStencilOp;
#define glStencilOp __gleStencilOp
extern PFNGLDEPTHFUNCPROC __gleDepthFunc;
#define glDepthFunc __gleDepthFunc
extern PFNGLPIXELSTOREFPROC __glePixelStoref;
#define glPixelStoref __glePixelStoref
extern PFNGLPIXELSTOREIPROC __glePixelStorei;
#define glPixelStorei __glePixelStorei
extern PFNGLREADBUFFERPROC __gleReadBuffer;
#define glReadBuffer __gleReadBuffer
extern PFNGLREADPIXELSPROC __gleReadPixels;
#define glReadPixels __gleReadPixels
extern PFNGLGETBOOLEANVPROC __gleGetBooleanv;
#define glGetBooleanv __gleGetBooleanv
extern PFNGLGETDOUBLEVPROC __gleGetDoublev;
#define glGetDoublev __gleGetDoublev
extern PFNGLGETERRORPROC __gleGetError;
#define glGetError __gleGetError
extern PFNGLGETFLOATVPROC __gleGetFloatv;
#define glGetFloatv __gleGetFloatv
extern PFNGLGETINTEGERVPROC __gleGetIntegerv;
#define glGetIntegerv __gleGetIntegerv
extern PFNGLGETSTRINGPROC __gleGetString;
#define glGetString __gleGetString
extern PFNGLGETTEXIMAGEPROC __gleGetTexImage;
#define glGetTexImage __gleGetTexImage
extern PFNGLGETTEXPARAMETERFVPROC __gleGetTexParameterfv;
#define glGetTexParameterfv __gleGetTexParameterfv
extern PFNGLGETTEXPARAMETERIVPROC __gleGetTexParameteriv;
#define glGetTexParameteriv __gleGetTexParameteriv
extern PFNGLGETTEXLEVELPARAMETERFVPROC __gleGetTexLevelParameterfv;
#define glGetTexLevelParameterfv __gleGetTexLevelParameterfv
extern PFNGLGETTEXLEVELPARAMETERIVPROC __gleGetTexLevelParameteriv;
#define glGetTexLevelParameteriv __gleGetTexLevelParameteriv
extern PFNGLISENABLEDPROC __gleIsEnabled;
#define glIsEnabled __gleIsEnabled
extern PFNGLDEPTHRANGEPROC __gleDepthRange;
#define glDepthRange __gleDepthRange
extern PFNGLVIEWPORTPROC __gleViewport;
#define glViewport __gleViewport
extern PFNGLNEWLISTPROC __gleNewList;
#define glNewList __gleNewList
extern PFNGLENDLISTPROC __gleEndList;
#define glEndList __gleEndList
extern PFNGLCALLLISTPROC __gleCallList;
#define glCallList __gleCallList
extern PFNGLCALLLISTSPROC __gleCallLists;
#define glCallLists __gleCallLists
extern PFNGLDELETELISTSPROC __gleDeleteLists;
#define glDeleteLists __gleDeleteLists
extern PFNGLGENLISTSPROC __gleGenLists;
#define glGenLists __gleGenLists
extern PFNGLLISTBASEPROC __gleListBase;
#define glListBase __gleListBase
extern PFNGLBEGINPROC __gleBegin;
#define glBegin __gleBegin
extern PFNGLBITMAPPROC __gleBitmap;
#define glBitmap __gleBitmap
extern PFNGLCOLOR3BPROC __gleColor3b;
#define glColor3b __gleColor3b
extern PFNGLCOLOR3BVPROC __gleColor3bv;
#define glColor3bv __gleColor3bv
extern PFNGLCOLOR3DPROC __gleColor3d;
#define glColor3d __gleColor3d
extern PFNGLCOLOR3DVPROC __gleColor3dv;
#define glColor3dv __gleColor3dv
extern PFNGLCOLOR3FPROC __gleColor3f;
#define glColor3f __gleColor3f
extern PFNGLCOLOR3FVPROC __gleColor3fv;
#define glColor3fv __gleColor3fv
extern PFNGLCOLOR3IPROC __gleColor3i;
#define glColor3i __gleColor3i
extern PFNGLCOLOR3IVPROC __gleColor3iv;
#define glColor3iv __gleColor3iv
extern PFNGLCOLOR3SPROC __gleColor3s;
#define glColor3s __gleColor3s
extern PFNGLCOLOR3SVPROC __gleColor3sv;
#define glColor3sv __gleColor3sv
extern PFNGLCOLOR3UBPROC __gleColor3ub;
#define glColor3ub __gleColor3ub
extern PFNGLCOLOR3UBVPROC __gleColor3ubv;
#define glColor3ubv __gleColor3ubv
extern PFNGLCOLOR3UIPROC __gleColor3ui;
#define glColor3ui __gleColor3ui
extern PFNGLCOLOR3UIVPROC __gleColor3uiv;
#define glColor3uiv __gleColor3uiv
extern PFNGLCOLOR3USPROC __gleColor3us;
#define glColor3us __gleColor3us
extern PFNGLCOLOR3USVPROC __gleColor3usv;
#define glColor3usv __gleColor3usv
extern PFNGLCOLOR4BPROC __gleColor4b;
#define glColor4b __gleColor4b
extern PFNGLCOLOR4BVPROC __gleColor4bv;
#define glColor4bv __gleColor4bv
extern PFNGLCOLOR4DPROC __gleColor4d;
#define glColor4d __gleColor4d
extern PFNGLCOLOR4DVPROC __gleColor4dv;
#define glColor4dv __gleColor4dv
extern PFNGLCOLOR4FPROC __gleColor4f;
#define glColor4f __gleColor4f
extern PFNGLCOLOR4FVPROC __gleColor4fv;
#define glColor4fv __gleColor4fv
extern PFNGLCOLOR4IPROC __gleColor4i;
#define glColor4i __gleColor4i
extern PFNGLCOLOR4IVPROC __gleColor4iv;
#define glColor4iv __gleColor4iv
extern PFNGLCOLOR4SPROC __gleColor4s;
#define glColor4s __gleColor4s
extern PFNGLCOLOR4SVPROC __gleColor4sv;
#define glColor4sv __gleColor4sv
extern PFNGLCOLOR4UBPROC __gleColor4ub;
#define glColor4ub __gleColor4ub
extern PFNGLCOLOR4UBVPROC __gleColor4ubv;
#define glColor4ubv __gleColor4ubv
extern PFNGLCOLOR4UIPROC __gleColor4ui;
#define glColor4ui __gleColor4ui
extern PFNGLCOLOR4UIVPROC __gleColor4uiv;
#define glColor4uiv __gleColor4uiv
extern PFNGLCOLOR4USPROC __gleColor4us;
#define glColor4us __gleColor4us
extern PFNGLCOLOR4USVPROC __gleColor4usv;
#define glColor4usv __gleColor4usv
extern PFNGLEDGEFLAGPROC __gleEdgeFlag;
#define glEdgeFlag __gleEdgeFlag
extern PFNGLEDGEFLAGVPROC __gleEdgeFlagv;
#define glEdgeFlagv __gleEdgeFlagv
extern PFNGLENDPROC __gleEnd;
#define glEnd __gleEnd
extern PFNGLINDEXDPROC __gleIndexd;
#define glIndexd __gleIndexd
extern PFNGLINDEXDVPROC __gleIndexdv;
#define glIndexdv __gleIndexdv
extern PFNGLINDEXFPROC __gleIndexf;
#define glIndexf __gleIndexf
extern PFNGLINDEXFVPROC __gleIndexfv;
#define glIndexfv __gleIndexfv
extern PFNGLINDEXIPROC __gleIndexi;
#define glIndexi __gleIndexi
extern PFNGLINDEXIVPROC __gleIndexiv;
#define glIndexiv __gleIndexiv
extern PFNGLINDEXSPROC __gleIndexs;
#define glIndexs __gleIndexs
extern PFNGLINDEXSVPROC __gleIndexsv;
#define glIndexsv __gleIndexsv
extern PFNGLNORMAL3BPROC __gleNormal3b;
#define glNormal3b __gleNormal3b
extern PFNGLNORMAL3BVPROC __gleNormal3bv;
#define glNormal3bv __gleNormal3bv
extern PFNGLNORMAL3DPROC __gleNormal3d;
#define glNormal3d __gleNormal3d
extern PFNGLNORMAL3DVPROC __gleNormal3dv;
#define glNormal3dv __gleNormal3dv
extern PFNGLNORMAL3FPROC __gleNormal3f;
#define glNormal3f __gleNormal3f
extern PFNGLNORMAL3FVPROC __gleNormal3fv;
#define glNormal3fv __gleNormal3fv
extern PFNGLNORMAL3IPROC __gleNormal3i;
#define glNormal3i __gleNormal3i
extern PFNGLNORMAL3IVPROC __gleNormal3iv;
#define glNormal3iv __gleNormal3iv
extern PFNGLNORMAL3SPROC __gleNormal3s;
#define glNormal3s __gleNormal3s
extern PFNGLNORMAL3SVPROC __gleNormal3sv;
#define glNormal3sv __gleNormal3sv
extern PFNGLRASTERPOS2DPROC __gleRasterPos2d;
#define glRasterPos2d __gleRasterPos2d
extern PFNGLRASTERPOS2DVPROC __gleRasterPos2dv;
#define glRasterPos2dv __gleRasterPos2dv
extern PFNGLRASTERPOS2FPROC __gleRasterPos2f;
#define glRasterPos2f __gleRasterPos2f
extern PFNGLRASTERPOS2FVPROC __gleRasterPos2fv;
#define glRasterPos2fv __gleRasterPos2fv
extern PFNGLRASTERPOS2IPROC __gleRasterPos2i;
#define glRasterPos2i __gleRasterPos2i
extern PFNGLRASTERPOS2IVPROC __gleRasterPos2iv;
#define glRasterPos2iv __gleRasterPos2iv
extern PFNGLRASTERPOS2SPROC __gleRasterPos2s;
#define glRasterPos2s __gleRasterPos2s
extern PFNGLRASTERPOS2SVPROC __gleRasterPos2sv;
#define glRasterPos2sv __gleRasterPos2sv
extern PFNGLRASTERPOS3DPROC __gleRasterPos3d;
#define glRasterPos3d __gleRasterPos3d
extern PFNGLRASTERPOS3DVPROC __gleRasterPos3dv;
#define glRasterPos3dv __gleRasterPos3dv
extern PFNGLRASTERPOS3FPROC __gleRasterPos3f;
#define glRasterPos3f __gleRasterPos3f
extern PFNGLRASTERPOS3FVPROC __gleRasterPos3fv;
#define glRasterPos3fv __gleRasterPos3fv
extern PFNGLRASTERPOS3IPROC __gleRasterPos3i;
#define glRasterPos3i __gleRasterPos3i
extern PFNGLRASTERPOS3IVPROC __gleRasterPos3iv;
#define glRasterPos3iv __gleRasterPos3iv
extern PFNGLRASTERPOS3SPROC __gleRasterPos3s;
#define glRasterPos3s __gleRasterPos3s
extern PFNGLRASTERPOS3SVPROC __gleRasterPos3sv;
#define glRasterPos3sv __gleRasterPos3sv
extern PFNGLRASTERPOS4DPROC __gleRasterPos4d;
#define glRasterPos4d __gleRasterPos4d
extern PFNGLRASTERPOS4DVPROC __gleRasterPos4dv;
#define glRasterPos4dv __gleRasterPos4dv
extern PFNGLRASTERPOS4FPROC __gleRasterPos4f;
#define glRasterPos4f __gleRasterPos4f
extern PFNGLRASTERPOS4FVPROC __gleRasterPos4fv;
#define glRasterPos4fv __gleRasterPos4fv
extern PFNGLRASTERPOS4IPROC __gleRasterPos4i;
#define glRasterPos4i __gleRasterPos4i
extern PFNGLRASTERPOS4IVPROC __gleRasterPos4iv;
#define glRasterPos4iv __gleRasterPos4iv
extern PFNGLRASTERPOS4SPROC __gleRasterPos4s;
#define glRasterPos4s __gleRasterPos4s
extern PFNGLRASTERPOS4SVPROC __gleRasterPos4sv;
#define glRasterPos4sv __gleRasterPos4sv
extern PFNGLRECTDPROC __gleRectd;
#define glRectd __gleRectd
extern PFNGLRECTDVPROC __gleRectdv;
#define glRectdv __gleRectdv
extern PFNGLRECTFPROC __gleRectf;
#define glRectf __gleRectf
extern PFNGLRECTFVPROC __gleRectfv;
#define glRectfv __gleRectfv
extern PFNGLRECTIPROC __gleRecti;
#define glRecti __gleRecti
extern PFNGLRECTIVPROC __gleRectiv;
#define glRectiv __gleRectiv
extern PFNGLRECTSPROC __gleRects;
#define glRects __gleRects
extern PFNGLRECTSVPROC __gleRectsv;
#define glRectsv __gleRectsv
extern PFNGLTEXCOORD1DPROC __gleTexCoord1d;
#define glTexCoord1d __gleTexCoord1d
extern PFNGLTEXCOORD1DVPROC __gleTexCoord1dv;
#define glTexCoord1dv __gleTexCoord1dv
extern PFNGLTEXCOORD1FPROC __gleTexCoord1f;
#define glTexCoord1f __gleTexCoord1f
extern PFNGLTEXCOORD1FVPROC __gleTexCoord1fv;
#define glTexCoord1fv __gleTexCoord1fv
extern PFNGLTEXCOORD1IPROC __gleTexCoord1i;
#define glTexCoord1i __gleTexCoord1i
extern PFNGLTEXCOORD1IVPROC __gleTexCoord1iv;
#define glTexCoord1iv __gleTexCoord1iv
extern PFNGLTEXCOORD1SPROC __gleTexCoord1s;
#define glTexCoord1s __gleTexCoord1s
extern PFNGLTEXCOORD1SVPROC __gleTexCoord1sv;
#define glTexCoord1sv __gleTexCoord1sv
extern PFNGLTEXCOORD2DPROC __gleTexCoord2d;
#define glTexCoord2d __gleTexCoord2d
extern PFNGLTEXCOORD2DVPROC __gleTexCoord2dv;
#define glTexCoord2dv __gleTexCoord2dv
extern PFNGLTEXCOORD2FPROC __gleTexCoord2f;
#define glTexCoord2f __gleTexCoord2f
extern PFNGLTEXCOORD2FVPROC __gleTexCoord2fv;
#define glTexCoord2fv __gleTexCoord2fv
extern PFNGLTEXCOORD2IPROC __gleTexCoord2i;
#define glTexCoord2i __gleTexCoord2i
extern PFNGLTEXCOORD2IVPROC __gleTexCoord2iv;
#define glTexCoord2iv __gleTexCoord2iv
extern PFNGLTEXCOORD2SPROC __gleTexCoord2s;
#define glTexCoord2s __gleTexCoord2s
extern PFNGLTEXCOORD2SVPROC __gleTexCoord2sv;
#define glTexCoord2sv __gleTexCoord2sv
extern PFNGLTEXCOORD3DPROC __gleTexCoord3d;
#define glTexCoord3d __gleTexCoord3d
extern PFNGLTEXCOORD3DVPROC __gleTexCoord3dv;
#define glTexCoord3dv __gleTexCoord3dv
extern PFNGLTEXCOORD3FPROC __gleTexCoord3f;
#define glTexCoord3f __gleTexCoord3f
extern PFNGLTEXCOORD3FVPROC __gleTexCoord3fv;
#define glTexCoord3fv __gleTexCoord3fv
extern PFNGLTEXCOORD3IPROC __gleTexCoord3i;
#define glTexCoord3i __gleTexCoord3i
extern PFNGLTEXCOORD3IVPROC __gleTexCoord3iv;
#define glTexCoord3iv __gleTexCoord3iv
extern PFNGLTEXCOORD3SPROC __gleTexCoord3s;
#define glTexCoord3s __gleTexCoord3s
extern PFNGLTEXCOORD3SVPROC __gleTexCoord3sv;
#define glTexCoord3sv __gleTexCoord3sv
extern PFNGLTEXCOORD4DPROC __gleTexCoord4d;
#define glTexCoord4d __gleTexCoord4d
extern PFNGLTEXCOORD4DVPROC __gleTexCoord4dv;
#define glTexCoord4dv __gleTexCoord4dv
extern PFNGLTEXCOORD4FPROC __gleTexCoord4f;
#define glTexCoord4f __gleTexCoord4f
extern PFNGLTEXCOORD4FVPROC __gleTexCoord4fv;
#define glTexCoord4fv __gleTexCoord4fv
extern PFNGLTEXCOORD4IPROC __gleTexCoord4i;
#define glTexCoord4i __gleTexCoord4i
extern PFNGLTEXCOORD4IVPROC __gleTexCoord4iv;
#define glTexCoord4iv __gleTexCoord4iv
extern PFNGLTEXCOORD4SPROC __gleTexCoord4s;
#define glTexCoord4s __gleTexCoord4s
extern PFNGLTEXCOORD4SVPROC __gleTexCoord4sv;
#define glTexCoord4sv __gleTexCoord4sv
extern PFNGLVERTEX2DPROC __gleVertex2d;
#define glVertex2d __gleVertex2d
extern PFNGLVERTEX2DVPROC __gleVertex2dv;
#define glVertex2dv __gleVertex2dv
extern PFNGLVERTEX2FPROC __gleVertex2f;
#define glVertex2f __gleVertex2f
extern PFNGLVERTEX2FVPROC __gleVertex2fv;
#define glVertex2fv __gleVertex2fv
extern PFNGLVERTEX2IPROC __gleVertex2i;
#define glVertex2i __gleVertex2i
extern PFNGLVERTEX2IVPROC __gleVertex2iv;
#define glVertex2iv __gleVertex2iv
extern PFNGLVERTEX2SPROC __gleVertex2s;
#define glVertex2s __gleVertex2s
extern PFNGLVERTEX2SVPROC __gleVertex2sv;
#define glVertex2sv __gleVertex2sv
extern PFNGLVERTEX3DPROC __gleVertex3d;
#define glVertex3d __gleVertex3d
extern PFNGLVERTEX3DVPROC __gleVertex3dv;
#define glVertex3dv __gleVertex3dv
extern PFNGLVERTEX3FPROC __gleVertex3f;
#define glVertex3f __gleVertex3f
extern PFNGLVERTEX3FVPROC __gleVertex3fv;
#define glVertex3fv __gleVertex3fv
extern PFNGLVERTEX3IPROC __gleVertex3i;
#define glVertex3i __gleVertex3i
extern PFNGLVERTEX3IVPROC __gleVertex3iv;
#define glVertex3iv __gleVertex3iv
extern PFNGLVERTEX3SPROC __gleVertex3s;
#define glVertex3s __gleVertex3s
extern PFNGLVERTEX3SVPROC __gleVertex3sv;
#define glVertex3sv __gleVertex3sv
extern PFNGLVERTEX4DPROC __gleVertex4d;
#define glVertex4d __gleVertex4d
extern PFNGLVERTEX4DVPROC __gleVertex4dv;
#define glVertex4dv __gleVertex4dv
extern PFNGLVERTEX4FPROC __gleVertex4f;
#define glVertex4f __gleVertex4f
extern PFNGLVERTEX4FVPROC __gleVertex4fv;
#define glVertex4fv __gleVertex4fv
extern PFNGLVERTEX4IPROC __gleVertex4i;
#define glVertex4i __gleVertex4i
extern PFNGLVERTEX4IVPROC __gleVertex4iv;
#define glVertex4iv __gleVertex4iv
extern PFNGLVERTEX4SPROC __gleVertex4s;
#define glVertex4s __gleVertex4s
extern PFNGLVERTEX4SVPROC __gleVertex4sv;
#define glVertex4sv __gleVertex4sv
extern PFNGLCLIPPLANEPROC __gleClipPlane;
#define glClipPlane __gleClipPlane
extern PFNGLCOLORMATERIALPROC __gleColorMaterial;
#define glColorMaterial __gleColorMaterial
extern PFNGLFOGFPROC __gleFogf;
#define glFogf __gleFogf
extern PFNGLFOGFVPROC __gleFogfv;
#define glFogfv __gleFogfv
extern PFNGLFOGIPROC __gleFogi;
#define glFogi __gleFogi
extern PFNGLFOGIVPROC __gleFogiv;
#define glFogiv __gleFogiv
extern PFNGLLIGHTFPROC __gleLightf;
#define glLightf __gleLightf
extern PFNGLLIGHTFVPROC __gleLightfv;
#define glLightfv __gleLightfv
extern PFNGLLIGHTIPROC __gleLighti;
#define glLighti __gleLighti
extern PFNGLLIGHTIVPROC __gleLightiv;
#define glLightiv __gleLightiv
extern PFNGLLIGHTMODELFPROC __gleLightModelf;
#define glLightModelf __gleLightModelf
extern PFNGLLIGHTMODELFVPROC __gleLightModelfv;
#define glLightModelfv __gleLightModelfv
extern PFNGLLIGHTMODELIPROC __gleLightModeli;
#define glLightModeli __gleLightModeli
extern PFNGLLIGHTMODELIVPROC __gleLightModeliv;
#define glLightModeliv __gleLightModeliv
extern PFNGLLINESTIPPLEPROC __gleLineStipple;
#define glLineStipple __gleLineStipple
extern PFNGLMATERIALFPROC __gleMaterialf;
#define glMaterialf __gleMaterialf
extern PFNGLMATERIALFVPROC __gleMaterialfv;
#define glMaterialfv __gleMaterialfv
extern PFNGLMATERIALIPROC __gleMateriali;
#define glMateriali __gleMateriali
extern PFNGLMATERIALIVPROC __gleMaterialiv;
#define glMaterialiv __gleMaterialiv
extern PFNGLPOLYGONSTIPPLEPROC __glePolygonStipple;
#define glPolygonStipple __glePolygonStipple
extern PFNGLSHADEMODELPROC __gleShadeModel;
#define glShadeModel __gleShadeModel
extern PFNGLTEXENVFPROC __gleTexEnvf;
#define glTexEnvf __gleTexEnvf
extern PFNGLTEXENVFVPROC __gleTexEnvfv;
#define glTexEnvfv __gleTexEnvfv
extern PFNGLTEXENVIPROC __gleTexEnvi;
#define glTexEnvi __gleTexEnvi
extern PFNGLTEXENVIVPROC __gleTexEnviv;
#define glTexEnviv __gleTexEnviv
extern PFNGLTEXGENDPROC __gleTexGend;
#define glTexGend __gleTexGend
extern PFNGLTEXGENDVPROC __gleTexGendv;
#define glTexGendv __gleTexGendv
extern PFNGLTEXGENFPROC __gleTexGenf;
#define glTexGenf __gleTexGenf
extern PFNGLTEXGENFVPROC __gleTexGenfv;
#define glTexGenfv __gleTexGenfv
extern PFNGLTEXGENIPROC __gleTexGeni;
#define glTexGeni __gleTexGeni
extern PFNGLTEXGENIVPROC __gleTexGeniv;
#define glTexGeniv __gleTexGeniv
extern PFNGLFEEDBACKBUFFERPROC __gleFeedbackBuffer;
#define glFeedbackBuffer __gleFeedbackBuffer
extern PFNGLSELECTBUFFERPROC __gleSelectBuffer;
#define glSelectBuffer __gleSelectBuffer
extern PFNGLRENDERMODEPROC __gleRenderMode;
#define glRenderMode __gleRenderMode
extern PFNGLINITNAMESPROC __gleInitNames;
#define glInitNames __gleInitNames
extern PFNGLLOADNAMEPROC __gleLoadName;
#define glLoadName __gleLoadName
extern PFNGLPASSTHROUGHPROC __glePassThrough;
#define glPassThrough __glePassThrough
extern PFNGLPOPNAMEPROC __glePopName;
#define glPopName __glePopName
extern PFNGLPUSHNAMEPROC __glePushName;
#define glPushName __glePushName
extern PFNGLCLEARACCUMPROC __gleClearAccum;
#define glClearAccum __gleClearAccum
extern PFNGLCLEARINDEXPROC __gleClearIndex;
#define glClearIndex __gleClearIndex
extern PFNGLINDEXMASKPROC __gleIndexMask;
#define glIndexMask __gleIndexMask
extern PFNGLACCUMPROC __gleAccum;
#define glAccum __gleAccum
extern PFNGLPOPATTRIBPROC __glePopAttrib;
#define glPopAttrib __glePopAttrib
extern PFNGLPUSHATTRIBPROC __glePushAttrib;
#define glPushAttrib __glePushAttrib
extern PFNGLMAP1DPROC __gleMap1d;
#define glMap1d __gleMap1d
extern PFNGLMAP1FPROC __gleMap1f;
#define glMap1f __gleMap1f
extern PFNGLMAP2DPROC __gleMap2d;
#define glMap2d __gleMap2d
extern PFNGLMAP2FPROC __gleMap2f;
#define glMap2f __gleMap2f
extern PFNGLMAPGRID1DPROC __gleMapGrid1d;
#define glMapGrid1d __gleMapGrid1d
extern PFNGLMAPGRID1FPROC __gleMapGrid1f;
#define glMapGrid1f __gleMapGrid1f
extern PFNGLMAPGRID2DPROC __gleMapGrid2d;
#define glMapGrid2d __gleMapGrid2d
extern PFNGLMAPGRID2FPROC __gleMapGrid2f;
#define glMapGrid2f __gleMapGrid2f
extern PFNGLEVALCOORD1DPROC __gleEvalCoord1d;
#define glEvalCoord1d __gleEvalCoord1d
extern PFNGLEVALCOORD1DVPROC __gleEvalCoord1dv;
#define glEvalCoord1dv __gleEvalCoord1dv
extern PFNGLEVALCOORD1FPROC __gleEvalCoord1f;
#define glEvalCoord1f __gleEvalCoord1f
extern PFNGLEVALCOORD1FVPROC __gleEvalCoord1fv;
#define glEvalCoord1fv __gleEvalCoord1fv
extern PFNGLEVALCOORD2DPROC __gleEvalCoord2d;
#define glEvalCoord2d __gleEvalCoord2d
extern PFNGLEVALCOORD2DVPROC __gleEvalCoord2dv;
#define glEvalCoord2dv __gleEvalCoord2dv
extern PFNGLEVALCOORD2FPROC __gleEvalCoord2f;
#define glEvalCoord2f __gleEvalCoord2f
extern PFNGLEVALCOORD2FVPROC __gleEvalCoord2fv;
#define glEvalCoord2fv __gleEvalCoord2fv
extern PFNGLEVALMESH1PROC __gleEvalMesh1;
#define glEvalMesh1 __gleEvalMesh1
extern PFNGLEVALPOINT1PROC __gleEvalPoint1;
#define glEvalPoint1 __gleEvalPoint1
extern PFNGLEVALMESH2PROC __gleEvalMesh2;
#define glEvalMesh2 __gleEvalMesh2
extern PFNGLEVALPOINT2PROC __gleEvalPoint2;
#define glEvalPoint2 __gleEvalPoint2
extern PFNGLALPHAFUNCPROC __gleAlphaFunc;
#define glAlphaFunc __gleAlphaFunc
extern PFNGLPIXELZOOMPROC __glePixelZoom;
#define glPixelZoom __glePixelZoom
extern PFNGLPIXELTRANSFERFPROC __glePixelTransferf;
#define glPixelTransferf __glePixelTransferf
extern PFNGLPIXELTRANSFERIPROC __glePixelTransferi;
#define glPixelTransferi __glePixelTransferi
extern PFNGLPIXELMAPFVPROC __glePixelMapfv;
#define glPixelMapfv __glePixelMapfv
extern PFNGLPIXELMAPUIVPROC __glePixelMapuiv;
#define glPixelMapuiv __glePixelMapuiv
extern PFNGLPIXELMAPUSVPROC __glePixelMapusv;
#define glPixelMapusv __glePixelMapusv
extern PFNGLCOPYPIXELSPROC __gleCopyPixels;
#define glCopyPixels __gleCopyPixels
extern PFNGLDRAWPIXELSPROC __gleDrawPixels;
#define glDrawPixels __gleDrawPixels
extern PFNGLGETCLIPPLANEPROC __gleGetClipPlane;
#define glGetClipPlane __gleGetClipPlane
extern PFNGLGETLIGHTFVPROC __gleGetLightfv;
#define glGetLightfv __gleGetLightfv
extern PFNGLGETLIGHTIVPROC __gleGetLightiv;
#define glGetLightiv __gleGetLightiv
extern PFNGLGETMAPDVPROC __gleGetMapdv;
#define glGetMapdv __gleGetMapdv
extern PFNGLGETMAPFVPROC __gleGetMapfv;
#define glGetMapfv __gleGetMapfv
extern PFNGLGETMAPIVPROC __gleGetMapiv;
#define glGetMapiv __gleGetMapiv
extern PFNGLGETMATERIALFVPROC __gleGetMaterialfv;
#define glGetMaterialfv __gleGetMaterialfv
extern PFNGLGETMATERIALIVPROC __gleGetMaterialiv;
#define glGetMaterialiv __gleGetMaterialiv
extern PFNGLGETPIXELMAPFVPROC __gleGetPixelMapfv;
#define glGetPixelMapfv __gleGetPixelMapfv
extern PFNGLGETPIXELMAPUIVPROC __gleGetPixelMapuiv;
#define glGetPixelMapuiv __gleGetPixelMapuiv
extern PFNGLGETPIXELMAPUSVPROC __gleGetPixelMapusv;
#define glGetPixelMapusv __gleGetPixelMapusv
extern PFNGLGETPOLYGONSTIPPLEPROC __gleGetPolygonStipple;
#define glGetPolygonStipple __gleGetPolygonStipple
extern PFNGLGETTEXENVFVPROC __gleGetTexEnvfv;
#define glGetTexEnvfv __gleGetTexEnvfv
extern PFNGLGETTEXENVIVPROC __gleGetTexEnviv;
#define glGetTexEnviv __gleGetTexEnviv
extern PFNGLGETTEXGENDVPROC __gleGetTexGendv;
#define glGetTexGendv __gleGetTexGendv
extern PFNGLGETTEXGENFVPROC __gleGetTexGenfv;
#define glGetTexGenfv __gleGetTexGenfv
extern PFNGLGETTEXGENIVPROC __gleGetTexGeniv;
#define glGetTexGeniv __gleGetTexGeniv
extern PFNGLISLISTPROC __gleIsList;
#define glIsList __gleIsList
extern PFNGLFRUSTUMPROC __gleFrustum;
#define glFrustum __gleFrustum
extern PFNGLLOADIDENTITYPROC __gleLoadIdentity;
#define glLoadIdentity __gleLoadIdentity
extern PFNGLLOADMATRIXFPROC __gleLoadMatrixf;
#define glLoadMatrixf __gleLoadMatrixf
extern PFNGLLOADMATRIXDPROC __gleLoadMatrixd;
#define glLoadMatrixd __gleLoadMatrixd
extern PFNGLMATRIXMODEPROC __gleMatrixMode;
#define glMatrixMode __gleMatrixMode
extern PFNGLMULTMATRIXFPROC __gleMultMatrixf;
#define glMultMatrixf __gleMultMatrixf
extern PFNGLMULTMATRIXDPROC __gleMultMatrixd;
#define glMultMatrixd __gleMultMatrixd
extern PFNGLORTHOPROC __gleOrtho;
#define glOrtho __gleOrtho
extern PFNGLPOPMATRIXPROC __glePopMatrix;
#define glPopMatrix __glePopMatrix
extern PFNGLPUSHMATRIXPROC __glePushMatrix;
#define glPushMatrix __glePushMatrix
extern PFNGLROTATEDPROC __gleRotated;
#define glRotated __gleRotated
extern PFNGLROTATEFPROC __gleRotatef;
#define glRotatef __gleRotatef
extern PFNGLSCALEDPROC __gleScaled;
#define glScaled __gleScaled
extern PFNGLSCALEFPROC __gleScalef;
#define glScalef __gleScalef
extern PFNGLTRANSLATEDPROC __gleTranslated;
#define glTranslated __gleTranslated
extern PFNGLTRANSLATEFPROC __gleTranslatef;
#define glTranslatef __gleTranslatef
extern PFNGLDRAWARRAYSPROC __gleDrawArrays;
#define glDrawArrays __gleDrawArrays
extern PFNGLDRAWELEMENTSPROC __gleDrawElements;
#define glDrawElements __gleDrawElements
extern PFNGLGETPOINTERVPROC __gleGetPointerv;
#define glGetPointerv __gleGetPointerv
extern PFNGLPOLYGONOFFSETPROC __glePolygonOffset;
#define glPolygonOffset __glePolygonOffset
extern PFNGLCOPYTEXIMAGE1DPROC __gleCopyTexImage1D;
#define glCopyTexImage1D __gleCopyTexImage1D
extern PFNGLCOPYTEXIMAGE2DPROC __gleCopyTexImage2D;
#define glCopyTexImage2D __gleCopyTexImage2D
extern PFNGLCOPYTEXSUBIMAGE1DPROC __gleCopyTexSubImage1D;
#define glCopyTexSubImage1D __gleCopyTexSubImage1D
extern PFNGLCOPYTEXSUBIMAGE2DPROC __gleCopyTexSubImage2D;
#define glCopyTexSubImage2D __gleCopyTexSubImage2D
extern PFNGLTEXSUBIMAGE1DPROC __gleTexSubImage1D;
#define glTexSubImage1D __gleTexSubImage1D
extern PFNGLTEXSUBIMAGE2DPROC __gleTexSubImage2D;
#define glTexSubImage2D __gleTexSubImage2D
extern PFNGLBINDTEXTUREPROC __gleBindTexture;
#define glBindTexture __gleBindTexture
extern PFNGLDELETETEXTURESPROC __gleDeleteTextures;
#define glDeleteTextures __gleDeleteTextures
extern PFNGLGENTEXTURESPROC __gleGenTextures;
#define glGenTextures __gleGenTextures
extern PFNGLISTEXTUREPROC __gleIsTexture;
#define glIsTexture __gleIsTexture
extern PFNGLARRAYELEMENTPROC __gleArrayElement;
#define glArrayElement __gleArrayElement
extern PFNGLCOLORPOINTERPROC __gleColorPointer;
#define glColorPointer __gleColorPointer
extern PFNGLDISABLECLIENTSTATEPROC __gleDisableClientState;
#define glDisableClientState __gleDisableClientState
extern PFNGLEDGEFLAGPOINTERPROC __gleEdgeFlagPointer;
#define glEdgeFlagPointer __gleEdgeFlagPointer
extern PFNGLENABLECLIENTSTATEPROC __gleEnableClientState;
#define glEnableClientState __gleEnableClientState
extern PFNGLINDEXPOINTERPROC __gleIndexPointer;
#define glIndexPointer __gleIndexPointer
extern PFNGLINTERLEAVEDARRAYSPROC __gleInterleavedArrays;
#define glInterleavedArrays __gleInterleavedArrays
extern PFNGLNORMALPOINTERPROC __gleNormalPointer;
#define glNormalPointer __gleNormalPointer
extern PFNGLTEXCOORDPOINTERPROC __gleTexCoordPointer;
#define glTexCoordPointer __gleTexCoordPointer
extern PFNGLVERTEXPOINTERPROC __gleVertexPointer;
#define glVertexPointer __gleVertexPointer
extern PFNGLARETEXTURESRESIDENTPROC __gleAreTexturesResident;
#define glAreTexturesResident __gleAreTexturesResident
extern PFNGLPRIORITIZETEXTURESPROC __glePrioritizeTextures;
#define glPrioritizeTextures __glePrioritizeTextures
extern PFNGLINDEXUBPROC __gleIndexub;
#define glIndexub __gleIndexub
extern PFNGLINDEXUBVPROC __gleIndexubv;
#define glIndexubv __gleIndexubv
extern PFNGLPOPCLIENTATTRIBPROC __glePopClientAttrib;
#define glPopClientAttrib __glePopClientAttrib
extern PFNGLPUSHCLIENTATTRIBPROC __glePushClientAttrib;
#define glPushClientAttrib __glePushClientAttrib


/******************************
* Version: 1.2
******************************/

#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#define GL_TEXTURE_BINDING_3D 0x806A
#define GL_PACK_SKIP_IMAGES 0x806B
#define GL_PACK_IMAGE_HEIGHT 0x806C
#define GL_UNPACK_SKIP_IMAGES 0x806D
#define GL_UNPACK_IMAGE_HEIGHT 0x806E
#define GL_TEXTURE_3D 0x806F
#define GL_PROXY_TEXTURE_3D 0x8070
#define GL_TEXTURE_DEPTH 0x8071
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_MAX_3D_TEXTURE_SIZE 0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1
#define GL_MAX_ELEMENTS_VERTICES 0x80E8
#define GL_MAX_ELEMENTS_INDICES 0x80E9
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_MIN_LOD 0x813A
#define GL_TEXTURE_MAX_LOD 0x813B
#define GL_TEXTURE_BASE_LEVEL 0x813C
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#define GL_RESCALE_NORMAL 0x803A
#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#define GL_SINGLE_COLOR 0x81F9
#define GL_SEPARATE_SPECULAR_COLOR 0x81FA
#define GL_ALIASED_POINT_SIZE_RANGE 0x846D


typedef void (GLE_FUNCPTR * PFNGLBLENDCOLORPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORTABLEPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOLORSUBTABLEPROC)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORSUBTABLEPROC)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER1DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER2DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIPROC)(GLenum target, GLenum pname, GLint params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER1DPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER2DPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
typedef void (GLE_FUNCPTR * PFNGLSEPARABLEFILTER2DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLHISTOGRAMPROC)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (GLE_FUNCPTR * PFNGLMINMAXPROC)(GLenum target, GLenum internalformat, GLboolean sink);
typedef void (GLE_FUNCPTR * PFNGLRESETHISTOGRAMPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLRESETMINMAXPROC)(GLenum target);

extern PFNGLBLENDCOLORPROC __gleBlendColor;
#define glBlendColor __gleBlendColor
extern PFNGLBLENDEQUATIONPROC __gleBlendEquation;
#define glBlendEquation __gleBlendEquation
extern PFNGLDRAWRANGEELEMENTSPROC __gleDrawRangeElements;
#define glDrawRangeElements __gleDrawRangeElements
extern PFNGLTEXIMAGE3DPROC __gleTexImage3D;
#define glTexImage3D __gleTexImage3D
extern PFNGLTEXSUBIMAGE3DPROC __gleTexSubImage3D;
#define glTexSubImage3D __gleTexSubImage3D
extern PFNGLCOPYTEXSUBIMAGE3DPROC __gleCopyTexSubImage3D;
#define glCopyTexSubImage3D __gleCopyTexSubImage3D
extern PFNGLCOLORTABLEPROC __gleColorTable;
#define glColorTable __gleColorTable
extern PFNGLCOLORTABLEPARAMETERFVPROC __gleColorTableParameterfv;
#define glColorTableParameterfv __gleColorTableParameterfv
extern PFNGLCOLORTABLEPARAMETERIVPROC __gleColorTableParameteriv;
#define glColorTableParameteriv __gleColorTableParameteriv
extern PFNGLCOPYCOLORTABLEPROC __gleCopyColorTable;
#define glCopyColorTable __gleCopyColorTable
extern PFNGLGETCOLORTABLEPROC __gleGetColorTable;
#define glGetColorTable __gleGetColorTable
extern PFNGLGETCOLORTABLEPARAMETERFVPROC __gleGetColorTableParameterfv;
#define glGetColorTableParameterfv __gleGetColorTableParameterfv
extern PFNGLGETCOLORTABLEPARAMETERIVPROC __gleGetColorTableParameteriv;
#define glGetColorTableParameteriv __gleGetColorTableParameteriv
extern PFNGLCOLORSUBTABLEPROC __gleColorSubTable;
#define glColorSubTable __gleColorSubTable
extern PFNGLCOPYCOLORSUBTABLEPROC __gleCopyColorSubTable;
#define glCopyColorSubTable __gleCopyColorSubTable
extern PFNGLCONVOLUTIONFILTER1DPROC __gleConvolutionFilter1D;
#define glConvolutionFilter1D __gleConvolutionFilter1D
extern PFNGLCONVOLUTIONFILTER2DPROC __gleConvolutionFilter2D;
#define glConvolutionFilter2D __gleConvolutionFilter2D
extern PFNGLCONVOLUTIONPARAMETERFPROC __gleConvolutionParameterf;
#define glConvolutionParameterf __gleConvolutionParameterf
extern PFNGLCONVOLUTIONPARAMETERFVPROC __gleConvolutionParameterfv;
#define glConvolutionParameterfv __gleConvolutionParameterfv
extern PFNGLCONVOLUTIONPARAMETERIPROC __gleConvolutionParameteri;
#define glConvolutionParameteri __gleConvolutionParameteri
extern PFNGLCONVOLUTIONPARAMETERIVPROC __gleConvolutionParameteriv;
#define glConvolutionParameteriv __gleConvolutionParameteriv
extern PFNGLCOPYCONVOLUTIONFILTER1DPROC __gleCopyConvolutionFilter1D;
#define glCopyConvolutionFilter1D __gleCopyConvolutionFilter1D
extern PFNGLCOPYCONVOLUTIONFILTER2DPROC __gleCopyConvolutionFilter2D;
#define glCopyConvolutionFilter2D __gleCopyConvolutionFilter2D
extern PFNGLGETCONVOLUTIONFILTERPROC __gleGetConvolutionFilter;
#define glGetConvolutionFilter __gleGetConvolutionFilter
extern PFNGLGETCONVOLUTIONPARAMETERFVPROC __gleGetConvolutionParameterfv;
#define glGetConvolutionParameterfv __gleGetConvolutionParameterfv
extern PFNGLGETCONVOLUTIONPARAMETERIVPROC __gleGetConvolutionParameteriv;
#define glGetConvolutionParameteriv __gleGetConvolutionParameteriv
extern PFNGLGETSEPARABLEFILTERPROC __gleGetSeparableFilter;
#define glGetSeparableFilter __gleGetSeparableFilter
extern PFNGLSEPARABLEFILTER2DPROC __gleSeparableFilter2D;
#define glSeparableFilter2D __gleSeparableFilter2D
extern PFNGLGETHISTOGRAMPROC __gleGetHistogram;
#define glGetHistogram __gleGetHistogram
extern PFNGLGETHISTOGRAMPARAMETERFVPROC __gleGetHistogramParameterfv;
#define glGetHistogramParameterfv __gleGetHistogramParameterfv
extern PFNGLGETHISTOGRAMPARAMETERIVPROC __gleGetHistogramParameteriv;
#define glGetHistogramParameteriv __gleGetHistogramParameteriv
extern PFNGLGETMINMAXPROC __gleGetMinmax;
#define glGetMinmax __gleGetMinmax
extern PFNGLGETMINMAXPARAMETERFVPROC __gleGetMinmaxParameterfv;
#define glGetMinmaxParameterfv __gleGetMinmaxParameterfv
extern PFNGLGETMINMAXPARAMETERIVPROC __gleGetMinmaxParameteriv;
#define glGetMinmaxParameteriv __gleGetMinmaxParameteriv
extern PFNGLHISTOGRAMPROC __gleHistogram;
#define glHistogram __gleHistogram
extern PFNGLMINMAXPROC __gleMinmax;
#define glMinmax __gleMinmax
extern PFNGLRESETHISTOGRAMPROC __gleResetHistogram;
#define glResetHistogram __gleResetHistogram
extern PFNGLRESETMINMAXPROC __gleResetMinmax;
#define glResetMinmax __gleResetMinmax


/******************************
* Version: 1.3
******************************/

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_MULTISAMPLE 0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLES 0x80A9
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP 0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#define GL_COMPRESSED_RGB 0x84ED
#define GL_COMPRESSED_RGBA 0x84EE
#define GL_TEXTURE_COMPRESSION_HINT 0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86A0
#define GL_TEXTURE_COMPRESSED 0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#define GL_MAX_TEXTURE_UNITS 0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX 0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX 0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX 0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX 0x84E6
#define GL_MULTISAMPLE_BIT 0x20000000
#define GL_NORMAL_MAP 0x8511
#define GL_REFLECTION_MAP 0x8512
#define GL_COMPRESSED_ALPHA 0x84E9
#define GL_COMPRESSED_LUMINANCE 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA 0x84EB
#define GL_COMPRESSED_INTENSITY 0x84EC
#define GL_COMBINE 0x8570
#define GL_COMBINE_RGB 0x8571
#define GL_COMBINE_ALPHA 0x8572
#define GL_SOURCE0_RGB 0x8580
#define GL_SOURCE1_RGB 0x8581
#define GL_SOURCE2_RGB 0x8582
#define GL_SOURCE0_ALPHA 0x8588
#define GL_SOURCE1_ALPHA 0x8589
#define GL_SOURCE2_ALPHA 0x858A
#define GL_OPERAND0_RGB 0x8590
#define GL_OPERAND1_RGB 0x8591
#define GL_OPERAND2_RGB 0x8592
#define GL_OPERAND0_ALPHA 0x8598
#define GL_OPERAND1_ALPHA 0x8599
#define GL_OPERAND2_ALPHA 0x859A
#define GL_RGB_SCALE 0x8573
#define GL_ADD_SIGNED 0x8574
#define GL_INTERPOLATE 0x8575
#define GL_SUBTRACT 0x84E7
#define GL_CONSTANT 0x8576
#define GL_PRIMARY_COLOR 0x8577
#define GL_PREVIOUS 0x8578
#define GL_DOT3_RGB 0x86AE
#define GL_DOT3_RGBA 0x86AF


typedef void (GLE_FUNCPTR * PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (GLE_FUNCPTR * PFNGLSAMPLECOVERAGEPROC)(GLclampf value, GLboolean invert);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, GLvoid *img);
typedef void (GLE_FUNCPTR * PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble *m);

extern PFNGLACTIVETEXTUREPROC __gleActiveTexture;
#define glActiveTexture __gleActiveTexture
extern PFNGLSAMPLECOVERAGEPROC __gleSampleCoverage;
#define glSampleCoverage __gleSampleCoverage
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC __gleCompressedTexImage3D;
#define glCompressedTexImage3D __gleCompressedTexImage3D
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC __gleCompressedTexImage2D;
#define glCompressedTexImage2D __gleCompressedTexImage2D
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC __gleCompressedTexImage1D;
#define glCompressedTexImage1D __gleCompressedTexImage1D
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC __gleCompressedTexSubImage3D;
#define glCompressedTexSubImage3D __gleCompressedTexSubImage3D
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __gleCompressedTexSubImage2D;
#define glCompressedTexSubImage2D __gleCompressedTexSubImage2D
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __gleCompressedTexSubImage1D;
#define glCompressedTexSubImage1D __gleCompressedTexSubImage1D
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC __gleGetCompressedTexImage;
#define glGetCompressedTexImage __gleGetCompressedTexImage
extern PFNGLCLIENTACTIVETEXTUREPROC __gleClientActiveTexture;
#define glClientActiveTexture __gleClientActiveTexture
extern PFNGLMULTITEXCOORD1DPROC __gleMultiTexCoord1d;
#define glMultiTexCoord1d __gleMultiTexCoord1d
extern PFNGLMULTITEXCOORD1DVPROC __gleMultiTexCoord1dv;
#define glMultiTexCoord1dv __gleMultiTexCoord1dv
extern PFNGLMULTITEXCOORD1FPROC __gleMultiTexCoord1f;
#define glMultiTexCoord1f __gleMultiTexCoord1f
extern PFNGLMULTITEXCOORD1FVPROC __gleMultiTexCoord1fv;
#define glMultiTexCoord1fv __gleMultiTexCoord1fv
extern PFNGLMULTITEXCOORD1IPROC __gleMultiTexCoord1i;
#define glMultiTexCoord1i __gleMultiTexCoord1i
extern PFNGLMULTITEXCOORD1IVPROC __gleMultiTexCoord1iv;
#define glMultiTexCoord1iv __gleMultiTexCoord1iv
extern PFNGLMULTITEXCOORD1SPROC __gleMultiTexCoord1s;
#define glMultiTexCoord1s __gleMultiTexCoord1s
extern PFNGLMULTITEXCOORD1SVPROC __gleMultiTexCoord1sv;
#define glMultiTexCoord1sv __gleMultiTexCoord1sv
extern PFNGLMULTITEXCOORD2DPROC __gleMultiTexCoord2d;
#define glMultiTexCoord2d __gleMultiTexCoord2d
extern PFNGLMULTITEXCOORD2DVPROC __gleMultiTexCoord2dv;
#define glMultiTexCoord2dv __gleMultiTexCoord2dv
extern PFNGLMULTITEXCOORD2FPROC __gleMultiTexCoord2f;
#define glMultiTexCoord2f __gleMultiTexCoord2f
extern PFNGLMULTITEXCOORD2FVPROC __gleMultiTexCoord2fv;
#define glMultiTexCoord2fv __gleMultiTexCoord2fv
extern PFNGLMULTITEXCOORD2IPROC __gleMultiTexCoord2i;
#define glMultiTexCoord2i __gleMultiTexCoord2i
extern PFNGLMULTITEXCOORD2IVPROC __gleMultiTexCoord2iv;
#define glMultiTexCoord2iv __gleMultiTexCoord2iv
extern PFNGLMULTITEXCOORD2SPROC __gleMultiTexCoord2s;
#define glMultiTexCoord2s __gleMultiTexCoord2s
extern PFNGLMULTITEXCOORD2SVPROC __gleMultiTexCoord2sv;
#define glMultiTexCoord2sv __gleMultiTexCoord2sv
extern PFNGLMULTITEXCOORD3DPROC __gleMultiTexCoord3d;
#define glMultiTexCoord3d __gleMultiTexCoord3d
extern PFNGLMULTITEXCOORD3DVPROC __gleMultiTexCoord3dv;
#define glMultiTexCoord3dv __gleMultiTexCoord3dv
extern PFNGLMULTITEXCOORD3FPROC __gleMultiTexCoord3f;
#define glMultiTexCoord3f __gleMultiTexCoord3f
extern PFNGLMULTITEXCOORD3FVPROC __gleMultiTexCoord3fv;
#define glMultiTexCoord3fv __gleMultiTexCoord3fv
extern PFNGLMULTITEXCOORD3IPROC __gleMultiTexCoord3i;
#define glMultiTexCoord3i __gleMultiTexCoord3i
extern PFNGLMULTITEXCOORD3IVPROC __gleMultiTexCoord3iv;
#define glMultiTexCoord3iv __gleMultiTexCoord3iv
extern PFNGLMULTITEXCOORD3SPROC __gleMultiTexCoord3s;
#define glMultiTexCoord3s __gleMultiTexCoord3s
extern PFNGLMULTITEXCOORD3SVPROC __gleMultiTexCoord3sv;
#define glMultiTexCoord3sv __gleMultiTexCoord3sv
extern PFNGLMULTITEXCOORD4DPROC __gleMultiTexCoord4d;
#define glMultiTexCoord4d __gleMultiTexCoord4d
extern PFNGLMULTITEXCOORD4DVPROC __gleMultiTexCoord4dv;
#define glMultiTexCoord4dv __gleMultiTexCoord4dv
extern PFNGLMULTITEXCOORD4FPROC __gleMultiTexCoord4f;
#define glMultiTexCoord4f __gleMultiTexCoord4f
extern PFNGLMULTITEXCOORD4FVPROC __gleMultiTexCoord4fv;
#define glMultiTexCoord4fv __gleMultiTexCoord4fv
extern PFNGLMULTITEXCOORD4IPROC __gleMultiTexCoord4i;
#define glMultiTexCoord4i __gleMultiTexCoord4i
extern PFNGLMULTITEXCOORD4IVPROC __gleMultiTexCoord4iv;
#define glMultiTexCoord4iv __gleMultiTexCoord4iv
extern PFNGLMULTITEXCOORD4SPROC __gleMultiTexCoord4s;
#define glMultiTexCoord4s __gleMultiTexCoord4s
extern PFNGLMULTITEXCOORD4SVPROC __gleMultiTexCoord4sv;
#define glMultiTexCoord4sv __gleMultiTexCoord4sv
extern PFNGLLOADTRANSPOSEMATRIXFPROC __gleLoadTransposeMatrixf;
#define glLoadTransposeMatrixf __gleLoadTransposeMatrixf
extern PFNGLLOADTRANSPOSEMATRIXDPROC __gleLoadTransposeMatrixd;
#define glLoadTransposeMatrixd __gleLoadTransposeMatrixd
extern PFNGLMULTTRANSPOSEMATRIXFPROC __gleMultTransposeMatrixf;
#define glMultTransposeMatrixf __gleMultTransposeMatrixf
extern PFNGLMULTTRANSPOSEMATRIXDPROC __gleMultTransposeMatrixd;
#define glMultTransposeMatrixd __gleMultTransposeMatrixd


/******************************
* Version: 1.4
******************************/

#define GL_BLEND_DST_RGB 0x80C8
#define GL_BLEND_SRC_RGB 0x80C9
#define GL_BLEND_DST_ALPHA 0x80CA
#define GL_BLEND_SRC_ALPHA 0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT32 0x81A7
#define GL_MIRRORED_REPEAT 0x8370
#define GL_MAX_TEXTURE_LOD_BIAS 0x84FD
#define GL_TEXTURE_LOD_BIAS 0x8501
#define GL_INCR_WRAP 0x8507
#define GL_DECR_WRAP 0x8508
#define GL_TEXTURE_DEPTH_SIZE 0x884A
#define GL_TEXTURE_COMPARE_MODE 0x884C
#define GL_TEXTURE_COMPARE_FUNC 0x884D
#define GL_POINT_SIZE_MIN 0x8126
#define GL_POINT_SIZE_MAX 0x8127
#define GL_POINT_DISTANCE_ATTENUATION 0x8129
#define GL_GENERATE_MIPMAP 0x8191
#define GL_GENERATE_MIPMAP_HINT 0x8192
#define GL_FOG_COORDINATE_SOURCE 0x8450
#define GL_FOG_COORDINATE 0x8451
#define GL_FRAGMENT_DEPTH 0x8452
#define GL_CURRENT_FOG_COORDINATE 0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE 0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE 0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER 0x8456
#define GL_FOG_COORDINATE_ARRAY 0x8457
#define GL_COLOR_SUM 0x8458
#define GL_CURRENT_SECONDARY_COLOR 0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE 0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE 0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE 0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER 0x845D
#define GL_SECONDARY_COLOR_ARRAY 0x845E
#define GL_TEXTURE_FILTER_CONTROL 0x8500
#define GL_DEPTH_TEXTURE_MODE 0x884B
#define GL_COMPARE_R_TO_TEXTURE 0x884E


typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFPROC)(GLfloat coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFVPROC)(const GLfloat *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDPROC)(GLdouble coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDVPROC)(const GLdouble *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USVPROC)(const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SVPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DVPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FVPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IVPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SVPROC)(const GLshort *v);

extern PFNGLBLENDFUNCSEPARATEPROC __gleBlendFuncSeparate;
#define glBlendFuncSeparate __gleBlendFuncSeparate
extern PFNGLMULTIDRAWARRAYSPROC __gleMultiDrawArrays;
#define glMultiDrawArrays __gleMultiDrawArrays
extern PFNGLMULTIDRAWELEMENTSPROC __gleMultiDrawElements;
#define glMultiDrawElements __gleMultiDrawElements
extern PFNGLPOINTPARAMETERFPROC __glePointParameterf;
#define glPointParameterf __glePointParameterf
extern PFNGLPOINTPARAMETERFVPROC __glePointParameterfv;
#define glPointParameterfv __glePointParameterfv
extern PFNGLPOINTPARAMETERIPROC __glePointParameteri;
#define glPointParameteri __glePointParameteri
extern PFNGLPOINTPARAMETERIVPROC __glePointParameteriv;
#define glPointParameteriv __glePointParameteriv
extern PFNGLFOGCOORDFPROC __gleFogCoordf;
#define glFogCoordf __gleFogCoordf
extern PFNGLFOGCOORDFVPROC __gleFogCoordfv;
#define glFogCoordfv __gleFogCoordfv
extern PFNGLFOGCOORDDPROC __gleFogCoordd;
#define glFogCoordd __gleFogCoordd
extern PFNGLFOGCOORDDVPROC __gleFogCoorddv;
#define glFogCoorddv __gleFogCoorddv
extern PFNGLFOGCOORDPOINTERPROC __gleFogCoordPointer;
#define glFogCoordPointer __gleFogCoordPointer
extern PFNGLSECONDARYCOLOR3BPROC __gleSecondaryColor3b;
#define glSecondaryColor3b __gleSecondaryColor3b
extern PFNGLSECONDARYCOLOR3BVPROC __gleSecondaryColor3bv;
#define glSecondaryColor3bv __gleSecondaryColor3bv
extern PFNGLSECONDARYCOLOR3DPROC __gleSecondaryColor3d;
#define glSecondaryColor3d __gleSecondaryColor3d
extern PFNGLSECONDARYCOLOR3DVPROC __gleSecondaryColor3dv;
#define glSecondaryColor3dv __gleSecondaryColor3dv
extern PFNGLSECONDARYCOLOR3FPROC __gleSecondaryColor3f;
#define glSecondaryColor3f __gleSecondaryColor3f
extern PFNGLSECONDARYCOLOR3FVPROC __gleSecondaryColor3fv;
#define glSecondaryColor3fv __gleSecondaryColor3fv
extern PFNGLSECONDARYCOLOR3IPROC __gleSecondaryColor3i;
#define glSecondaryColor3i __gleSecondaryColor3i
extern PFNGLSECONDARYCOLOR3IVPROC __gleSecondaryColor3iv;
#define glSecondaryColor3iv __gleSecondaryColor3iv
extern PFNGLSECONDARYCOLOR3SPROC __gleSecondaryColor3s;
#define glSecondaryColor3s __gleSecondaryColor3s
extern PFNGLSECONDARYCOLOR3SVPROC __gleSecondaryColor3sv;
#define glSecondaryColor3sv __gleSecondaryColor3sv
extern PFNGLSECONDARYCOLOR3UBPROC __gleSecondaryColor3ub;
#define glSecondaryColor3ub __gleSecondaryColor3ub
extern PFNGLSECONDARYCOLOR3UBVPROC __gleSecondaryColor3ubv;
#define glSecondaryColor3ubv __gleSecondaryColor3ubv
extern PFNGLSECONDARYCOLOR3UIPROC __gleSecondaryColor3ui;
#define glSecondaryColor3ui __gleSecondaryColor3ui
extern PFNGLSECONDARYCOLOR3UIVPROC __gleSecondaryColor3uiv;
#define glSecondaryColor3uiv __gleSecondaryColor3uiv
extern PFNGLSECONDARYCOLOR3USPROC __gleSecondaryColor3us;
#define glSecondaryColor3us __gleSecondaryColor3us
extern PFNGLSECONDARYCOLOR3USVPROC __gleSecondaryColor3usv;
#define glSecondaryColor3usv __gleSecondaryColor3usv
extern PFNGLSECONDARYCOLORPOINTERPROC __gleSecondaryColorPointer;
#define glSecondaryColorPointer __gleSecondaryColorPointer
extern PFNGLWINDOWPOS2DPROC __gleWindowPos2d;
#define glWindowPos2d __gleWindowPos2d
extern PFNGLWINDOWPOS2DVPROC __gleWindowPos2dv;
#define glWindowPos2dv __gleWindowPos2dv
extern PFNGLWINDOWPOS2FPROC __gleWindowPos2f;
#define glWindowPos2f __gleWindowPos2f
extern PFNGLWINDOWPOS2FVPROC __gleWindowPos2fv;
#define glWindowPos2fv __gleWindowPos2fv
extern PFNGLWINDOWPOS2IPROC __gleWindowPos2i;
#define glWindowPos2i __gleWindowPos2i
extern PFNGLWINDOWPOS2IVPROC __gleWindowPos2iv;
#define glWindowPos2iv __gleWindowPos2iv
extern PFNGLWINDOWPOS2SPROC __gleWindowPos2s;
#define glWindowPos2s __gleWindowPos2s
extern PFNGLWINDOWPOS2SVPROC __gleWindowPos2sv;
#define glWindowPos2sv __gleWindowPos2sv
extern PFNGLWINDOWPOS3DPROC __gleWindowPos3d;
#define glWindowPos3d __gleWindowPos3d
extern PFNGLWINDOWPOS3DVPROC __gleWindowPos3dv;
#define glWindowPos3dv __gleWindowPos3dv
extern PFNGLWINDOWPOS3FPROC __gleWindowPos3f;
#define glWindowPos3f __gleWindowPos3f
extern PFNGLWINDOWPOS3FVPROC __gleWindowPos3fv;
#define glWindowPos3fv __gleWindowPos3fv
extern PFNGLWINDOWPOS3IPROC __gleWindowPos3i;
#define glWindowPos3i __gleWindowPos3i
extern PFNGLWINDOWPOS3IVPROC __gleWindowPos3iv;
#define glWindowPos3iv __gleWindowPos3iv
extern PFNGLWINDOWPOS3SPROC __gleWindowPos3s;
#define glWindowPos3s __gleWindowPos3s
extern PFNGLWINDOWPOS3SVPROC __gleWindowPos3sv;
#define glWindowPos3sv __gleWindowPos3sv


/******************************
* Version: 1.5
******************************/

#define GL_BUFFER_SIZE 0x8764
#define GL_BUFFER_USAGE 0x8765
#define GL_QUERY_COUNTER_BITS 0x8864
#define GL_CURRENT_QUERY 0x8865
#define GL_QUERY_RESULT 0x8866
#define GL_QUERY_RESULT_AVAILABLE 0x8867
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY 0x88B8
#define GL_WRITE_ONLY 0x88B9
#define GL_READ_WRITE 0x88BA
#define GL_BUFFER_ACCESS 0x88BB
#define GL_BUFFER_MAPPED 0x88BC
#define GL_BUFFER_MAP_POINTER 0x88BD
#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_STREAM_COPY 0x88E2
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA
#define GL_SAMPLES_PASSED 0x8914
#define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING 0x889E
#define GL_FOG_COORD_SRC 0x8450
#define GL_FOG_COORD 0x8451
#define GL_CURRENT_FOG_COORD 0x8453
#define GL_FOG_COORD_ARRAY_TYPE 0x8454
#define GL_FOG_COORD_ARRAY_STRIDE 0x8455
#define GL_FOG_COORD_ARRAY_POINTER 0x8456
#define GL_FOG_COORD_ARRAY 0x8457
#define GL_FOG_COORD_ARRAY_BUFFER_BINDING 0x889D
#define GL_SRC0_RGB 0x8580
#define GL_SRC1_RGB 0x8581
#define GL_SRC2_RGB 0x8582
#define GL_SRC0_ALPHA 0x8588
#define GL_SRC1_ALPHA 0x8589
#define GL_SRC2_ALPHA 0x858A


typedef void (GLE_FUNCPTR * PFNGLGENQUERIESPROC)(GLsizei n, GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISQUERYPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDQUERYPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
typedef void (GLE_FUNCPTR * PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
typedef GLboolean (GLE_FUNCPTR * PFNGLISBUFFERPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (GLE_FUNCPTR * PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
typedef GLboolean (GLE_FUNCPTR * PFNGLUNMAPBUFFERPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, GLvoid* *params);

extern PFNGLGENQUERIESPROC __gleGenQueries;
#define glGenQueries __gleGenQueries
extern PFNGLDELETEQUERIESPROC __gleDeleteQueries;
#define glDeleteQueries __gleDeleteQueries
extern PFNGLISQUERYPROC __gleIsQuery;
#define glIsQuery __gleIsQuery
extern PFNGLBEGINQUERYPROC __gleBeginQuery;
#define glBeginQuery __gleBeginQuery
extern PFNGLENDQUERYPROC __gleEndQuery;
#define glEndQuery __gleEndQuery
extern PFNGLGETQUERYIVPROC __gleGetQueryiv;
#define glGetQueryiv __gleGetQueryiv
extern PFNGLGETQUERYOBJECTIVPROC __gleGetQueryObjectiv;
#define glGetQueryObjectiv __gleGetQueryObjectiv
extern PFNGLGETQUERYOBJECTUIVPROC __gleGetQueryObjectuiv;
#define glGetQueryObjectuiv __gleGetQueryObjectuiv
extern PFNGLBINDBUFFERPROC __gleBindBuffer;
#define glBindBuffer __gleBindBuffer
extern PFNGLDELETEBUFFERSPROC __gleDeleteBuffers;
#define glDeleteBuffers __gleDeleteBuffers
extern PFNGLGENBUFFERSPROC __gleGenBuffers;
#define glGenBuffers __gleGenBuffers
extern PFNGLISBUFFERPROC __gleIsBuffer;
#define glIsBuffer __gleIsBuffer
extern PFNGLBUFFERDATAPROC __gleBufferData;
#define glBufferData __gleBufferData
extern PFNGLBUFFERSUBDATAPROC __gleBufferSubData;
#define glBufferSubData __gleBufferSubData
extern PFNGLGETBUFFERSUBDATAPROC __gleGetBufferSubData;
#define glGetBufferSubData __gleGetBufferSubData
extern PFNGLMAPBUFFERPROC __gleMapBuffer;
#define glMapBuffer __gleMapBuffer
extern PFNGLUNMAPBUFFERPROC __gleUnmapBuffer;
#define glUnmapBuffer __gleUnmapBuffer
extern PFNGLGETBUFFERPARAMETERIVPROC __gleGetBufferParameteriv;
#define glGetBufferParameteriv __gleGetBufferParameteriv
extern PFNGLGETBUFFERPOINTERVPROC __gleGetBufferPointerv;
#define glGetBufferPointerv __gleGetBufferPointerv


/******************************
* Version: 2.0
******************************/

#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#define GL_CURRENT_VERTEX_ATTRIB 0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_MAX_DRAW_BUFFERS 0x8824
#define GL_DRAW_BUFFER0 0x8825
#define GL_DRAW_BUFFER1 0x8826
#define GL_DRAW_BUFFER2 0x8827
#define GL_DRAW_BUFFER3 0x8828
#define GL_DRAW_BUFFER4 0x8829
#define GL_DRAW_BUFFER5 0x882A
#define GL_DRAW_BUFFER6 0x882B
#define GL_DRAW_BUFFER7 0x882C
#define GL_DRAW_BUFFER8 0x882D
#define GL_DRAW_BUFFER9 0x882E
#define GL_DRAW_BUFFER10 0x882F
#define GL_DRAW_BUFFER11 0x8830
#define GL_DRAW_BUFFER12 0x8831
#define GL_DRAW_BUFFER13 0x8832
#define GL_DRAW_BUFFER14 0x8833
#define GL_DRAW_BUFFER15 0x8834
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
#define GL_MAX_VARYING_FLOATS 0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE 0x8B4F
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_INT_VEC2 0x8B53
#define GL_INT_VEC3 0x8B54
#define GL_INT_VEC4 0x8B55
#define GL_BOOL 0x8B56
#define GL_BOOL_VEC2 0x8B57
#define GL_BOOL_VEC3 0x8B58
#define GL_BOOL_VEC4 0x8B59
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_SAMPLER_1D 0x8B5D
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_3D 0x8B5F
#define GL_SAMPLER_CUBE 0x8B60
#define GL_SAMPLER_1D_SHADOW 0x8B61
#define GL_SAMPLER_2D_SHADOW 0x8B62
#define GL_DELETE_STATUS 0x8B80
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_VALIDATE_STATUS 0x8B83
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_ATTACHED_SHADERS 0x8B85
#define GL_ACTIVE_UNIFORMS 0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#define GL_SHADER_SOURCE_LENGTH 0x8B88
#define GL_ACTIVE_ATTRIBUTES 0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN 0x8CA0
#define GL_LOWER_LEFT 0x8CA1
#define GL_UPPER_LEFT 0x8CA2
#define GL_STENCIL_BACK_REF 0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
#define GL_POINT_SPRITE 0x8861
#define GL_COORD_REPLACE 0x8862
#define GL_MAX_TEXTURE_COORDS 0x8871


typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);
typedef void (GLE_FUNCPTR * PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (GLE_FUNCPTR * PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
typedef void (GLE_FUNCPTR * PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (GLE_FUNCPTR * PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint (GLE_FUNCPTR * PFNGLCREATEPROGRAMPROC)();
typedef GLuint (GLE_FUNCPTR * PFNGLCREATESHADERPROC)(GLenum type);
typedef void (GLE_FUNCPTR * PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void (GLE_FUNCPTR * PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (GLE_FUNCPTR * PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (GLE_FUNCPTR * PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (GLE_FUNCPTR * PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *obj);
typedef GLint (GLE_FUNCPTR * PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (GLE_FUNCPTR * PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, GLvoid* *pointer);
typedef GLboolean (GLE_FUNCPTR * PFNGLISPROGRAMPROC)(GLuint program);
typedef GLboolean (GLE_FUNCPTR * PFNGLISSHADERPROC)(GLuint shader);
typedef void (GLE_FUNCPTR * PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (GLE_FUNCPTR * PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
typedef void (GLE_FUNCPTR * PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLVALIDATEPROGRAMPROC)(GLuint program);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);

extern PFNGLBLENDEQUATIONSEPARATEPROC __gleBlendEquationSeparate;
#define glBlendEquationSeparate __gleBlendEquationSeparate
extern PFNGLDRAWBUFFERSPROC __gleDrawBuffers;
#define glDrawBuffers __gleDrawBuffers
extern PFNGLSTENCILOPSEPARATEPROC __gleStencilOpSeparate;
#define glStencilOpSeparate __gleStencilOpSeparate
extern PFNGLSTENCILFUNCSEPARATEPROC __gleStencilFuncSeparate;
#define glStencilFuncSeparate __gleStencilFuncSeparate
extern PFNGLSTENCILMASKSEPARATEPROC __gleStencilMaskSeparate;
#define glStencilMaskSeparate __gleStencilMaskSeparate
extern PFNGLATTACHSHADERPROC __gleAttachShader;
#define glAttachShader __gleAttachShader
extern PFNGLBINDATTRIBLOCATIONPROC __gleBindAttribLocation;
#define glBindAttribLocation __gleBindAttribLocation
extern PFNGLCOMPILESHADERPROC __gleCompileShader;
#define glCompileShader __gleCompileShader
extern PFNGLCREATEPROGRAMPROC __gleCreateProgram;
#define glCreateProgram __gleCreateProgram
extern PFNGLCREATESHADERPROC __gleCreateShader;
#define glCreateShader __gleCreateShader
extern PFNGLDELETEPROGRAMPROC __gleDeleteProgram;
#define glDeleteProgram __gleDeleteProgram
extern PFNGLDELETESHADERPROC __gleDeleteShader;
#define glDeleteShader __gleDeleteShader
extern PFNGLDETACHSHADERPROC __gleDetachShader;
#define glDetachShader __gleDetachShader
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC __gleDisableVertexAttribArray;
#define glDisableVertexAttribArray __gleDisableVertexAttribArray
extern PFNGLENABLEVERTEXATTRIBARRAYPROC __gleEnableVertexAttribArray;
#define glEnableVertexAttribArray __gleEnableVertexAttribArray
extern PFNGLGETACTIVEATTRIBPROC __gleGetActiveAttrib;
#define glGetActiveAttrib __gleGetActiveAttrib
extern PFNGLGETACTIVEUNIFORMPROC __gleGetActiveUniform;
#define glGetActiveUniform __gleGetActiveUniform
extern PFNGLGETATTACHEDSHADERSPROC __gleGetAttachedShaders;
#define glGetAttachedShaders __gleGetAttachedShaders
extern PFNGLGETATTRIBLOCATIONPROC __gleGetAttribLocation;
#define glGetAttribLocation __gleGetAttribLocation
extern PFNGLGETPROGRAMIVPROC __gleGetProgramiv;
#define glGetProgramiv __gleGetProgramiv
extern PFNGLGETPROGRAMINFOLOGPROC __gleGetProgramInfoLog;
#define glGetProgramInfoLog __gleGetProgramInfoLog
extern PFNGLGETSHADERIVPROC __gleGetShaderiv;
#define glGetShaderiv __gleGetShaderiv
extern PFNGLGETSHADERINFOLOGPROC __gleGetShaderInfoLog;
#define glGetShaderInfoLog __gleGetShaderInfoLog
extern PFNGLGETSHADERSOURCEPROC __gleGetShaderSource;
#define glGetShaderSource __gleGetShaderSource
extern PFNGLGETUNIFORMLOCATIONPROC __gleGetUniformLocation;
#define glGetUniformLocation __gleGetUniformLocation
extern PFNGLGETUNIFORMFVPROC __gleGetUniformfv;
#define glGetUniformfv __gleGetUniformfv
extern PFNGLGETUNIFORMIVPROC __gleGetUniformiv;
#define glGetUniformiv __gleGetUniformiv
extern PFNGLGETVERTEXATTRIBDVPROC __gleGetVertexAttribdv;
#define glGetVertexAttribdv __gleGetVertexAttribdv
extern PFNGLGETVERTEXATTRIBFVPROC __gleGetVertexAttribfv;
#define glGetVertexAttribfv __gleGetVertexAttribfv
extern PFNGLGETVERTEXATTRIBIVPROC __gleGetVertexAttribiv;
#define glGetVertexAttribiv __gleGetVertexAttribiv
extern PFNGLGETVERTEXATTRIBPOINTERVPROC __gleGetVertexAttribPointerv;
#define glGetVertexAttribPointerv __gleGetVertexAttribPointerv
extern PFNGLISPROGRAMPROC __gleIsProgram;
#define glIsProgram __gleIsProgram
extern PFNGLISSHADERPROC __gleIsShader;
#define glIsShader __gleIsShader
extern PFNGLLINKPROGRAMPROC __gleLinkProgram;
#define glLinkProgram __gleLinkProgram
extern PFNGLSHADERSOURCEPROC __gleShaderSource;
#define glShaderSource __gleShaderSource
extern PFNGLUSEPROGRAMPROC __gleUseProgram;
#define glUseProgram __gleUseProgram
extern PFNGLUNIFORM1FPROC __gleUniform1f;
#define glUniform1f __gleUniform1f
extern PFNGLUNIFORM2FPROC __gleUniform2f;
#define glUniform2f __gleUniform2f
extern PFNGLUNIFORM3FPROC __gleUniform3f;
#define glUniform3f __gleUniform3f
extern PFNGLUNIFORM4FPROC __gleUniform4f;
#define glUniform4f __gleUniform4f
extern PFNGLUNIFORM1IPROC __gleUniform1i;
#define glUniform1i __gleUniform1i
extern PFNGLUNIFORM2IPROC __gleUniform2i;
#define glUniform2i __gleUniform2i
extern PFNGLUNIFORM3IPROC __gleUniform3i;
#define glUniform3i __gleUniform3i
extern PFNGLUNIFORM4IPROC __gleUniform4i;
#define glUniform4i __gleUniform4i
extern PFNGLUNIFORM1FVPROC __gleUniform1fv;
#define glUniform1fv __gleUniform1fv
extern PFNGLUNIFORM2FVPROC __gleUniform2fv;
#define glUniform2fv __gleUniform2fv
extern PFNGLUNIFORM3FVPROC __gleUniform3fv;
#define glUniform3fv __gleUniform3fv
extern PFNGLUNIFORM4FVPROC __gleUniform4fv;
#define glUniform4fv __gleUniform4fv
extern PFNGLUNIFORM1IVPROC __gleUniform1iv;
#define glUniform1iv __gleUniform1iv
extern PFNGLUNIFORM2IVPROC __gleUniform2iv;
#define glUniform2iv __gleUniform2iv
extern PFNGLUNIFORM3IVPROC __gleUniform3iv;
#define glUniform3iv __gleUniform3iv
extern PFNGLUNIFORM4IVPROC __gleUniform4iv;
#define glUniform4iv __gleUniform4iv
extern PFNGLUNIFORMMATRIX2FVPROC __gleUniformMatrix2fv;
#define glUniformMatrix2fv __gleUniformMatrix2fv
extern PFNGLUNIFORMMATRIX3FVPROC __gleUniformMatrix3fv;
#define glUniformMatrix3fv __gleUniformMatrix3fv
extern PFNGLUNIFORMMATRIX4FVPROC __gleUniformMatrix4fv;
#define glUniformMatrix4fv __gleUniformMatrix4fv
extern PFNGLVALIDATEPROGRAMPROC __gleValidateProgram;
#define glValidateProgram __gleValidateProgram
extern PFNGLVERTEXATTRIB1DPROC __gleVertexAttrib1d;
#define glVertexAttrib1d __gleVertexAttrib1d
extern PFNGLVERTEXATTRIB1DVPROC __gleVertexAttrib1dv;
#define glVertexAttrib1dv __gleVertexAttrib1dv
extern PFNGLVERTEXATTRIB1FPROC __gleVertexAttrib1f;
#define glVertexAttrib1f __gleVertexAttrib1f
extern PFNGLVERTEXATTRIB1FVPROC __gleVertexAttrib1fv;
#define glVertexAttrib1fv __gleVertexAttrib1fv
extern PFNGLVERTEXATTRIB1SPROC __gleVertexAttrib1s;
#define glVertexAttrib1s __gleVertexAttrib1s
extern PFNGLVERTEXATTRIB1SVPROC __gleVertexAttrib1sv;
#define glVertexAttrib1sv __gleVertexAttrib1sv
extern PFNGLVERTEXATTRIB2DPROC __gleVertexAttrib2d;
#define glVertexAttrib2d __gleVertexAttrib2d
extern PFNGLVERTEXATTRIB2DVPROC __gleVertexAttrib2dv;
#define glVertexAttrib2dv __gleVertexAttrib2dv
extern PFNGLVERTEXATTRIB2FPROC __gleVertexAttrib2f;
#define glVertexAttrib2f __gleVertexAttrib2f
extern PFNGLVERTEXATTRIB2FVPROC __gleVertexAttrib2fv;
#define glVertexAttrib2fv __gleVertexAttrib2fv
extern PFNGLVERTEXATTRIB2SPROC __gleVertexAttrib2s;
#define glVertexAttrib2s __gleVertexAttrib2s
extern PFNGLVERTEXATTRIB2SVPROC __gleVertexAttrib2sv;
#define glVertexAttrib2sv __gleVertexAttrib2sv
extern PFNGLVERTEXATTRIB3DPROC __gleVertexAttrib3d;
#define glVertexAttrib3d __gleVertexAttrib3d
extern PFNGLVERTEXATTRIB3DVPROC __gleVertexAttrib3dv;
#define glVertexAttrib3dv __gleVertexAttrib3dv
extern PFNGLVERTEXATTRIB3FPROC __gleVertexAttrib3f;
#define glVertexAttrib3f __gleVertexAttrib3f
extern PFNGLVERTEXATTRIB3FVPROC __gleVertexAttrib3fv;
#define glVertexAttrib3fv __gleVertexAttrib3fv
extern PFNGLVERTEXATTRIB3SPROC __gleVertexAttrib3s;
#define glVertexAttrib3s __gleVertexAttrib3s
extern PFNGLVERTEXATTRIB3SVPROC __gleVertexAttrib3sv;
#define glVertexAttrib3sv __gleVertexAttrib3sv
extern PFNGLVERTEXATTRIB4NBVPROC __gleVertexAttrib4Nbv;
#define glVertexAttrib4Nbv __gleVertexAttrib4Nbv
extern PFNGLVERTEXATTRIB4NIVPROC __gleVertexAttrib4Niv;
#define glVertexAttrib4Niv __gleVertexAttrib4Niv
extern PFNGLVERTEXATTRIB4NSVPROC __gleVertexAttrib4Nsv;
#define glVertexAttrib4Nsv __gleVertexAttrib4Nsv
extern PFNGLVERTEXATTRIB4NUBPROC __gleVertexAttrib4Nub;
#define glVertexAttrib4Nub __gleVertexAttrib4Nub
extern PFNGLVERTEXATTRIB4NUBVPROC __gleVertexAttrib4Nubv;
#define glVertexAttrib4Nubv __gleVertexAttrib4Nubv
extern PFNGLVERTEXATTRIB4NUIVPROC __gleVertexAttrib4Nuiv;
#define glVertexAttrib4Nuiv __gleVertexAttrib4Nuiv
extern PFNGLVERTEXATTRIB4NUSVPROC __gleVertexAttrib4Nusv;
#define glVertexAttrib4Nusv __gleVertexAttrib4Nusv
extern PFNGLVERTEXATTRIB4BVPROC __gleVertexAttrib4bv;
#define glVertexAttrib4bv __gleVertexAttrib4bv
extern PFNGLVERTEXATTRIB4DPROC __gleVertexAttrib4d;
#define glVertexAttrib4d __gleVertexAttrib4d
extern PFNGLVERTEXATTRIB4DVPROC __gleVertexAttrib4dv;
#define glVertexAttrib4dv __gleVertexAttrib4dv
extern PFNGLVERTEXATTRIB4FPROC __gleVertexAttrib4f;
#define glVertexAttrib4f __gleVertexAttrib4f
extern PFNGLVERTEXATTRIB4FVPROC __gleVertexAttrib4fv;
#define glVertexAttrib4fv __gleVertexAttrib4fv
extern PFNGLVERTEXATTRIB4IVPROC __gleVertexAttrib4iv;
#define glVertexAttrib4iv __gleVertexAttrib4iv
extern PFNGLVERTEXATTRIB4SPROC __gleVertexAttrib4s;
#define glVertexAttrib4s __gleVertexAttrib4s
extern PFNGLVERTEXATTRIB4SVPROC __gleVertexAttrib4sv;
#define glVertexAttrib4sv __gleVertexAttrib4sv
extern PFNGLVERTEXATTRIB4UBVPROC __gleVertexAttrib4ubv;
#define glVertexAttrib4ubv __gleVertexAttrib4ubv
extern PFNGLVERTEXATTRIB4UIVPROC __gleVertexAttrib4uiv;
#define glVertexAttrib4uiv __gleVertexAttrib4uiv
extern PFNGLVERTEXATTRIB4USVPROC __gleVertexAttrib4usv;
#define glVertexAttrib4usv __gleVertexAttrib4usv
extern PFNGLVERTEXATTRIBPOINTERPROC __gleVertexAttribPointer;
#define glVertexAttribPointer __gleVertexAttribPointer


/******************************
* Version: 2.1
******************************/

#define GL_PIXEL_PACK_BUFFER 0x88EB
#define GL_PIXEL_UNPACK_BUFFER 0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING 0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88EF
#define GL_FLOAT_MAT2x3 0x8B65
#define GL_FLOAT_MAT2x4 0x8B66
#define GL_FLOAT_MAT3x2 0x8B67
#define GL_FLOAT_MAT3x4 0x8B68
#define GL_FLOAT_MAT4x2 0x8B69
#define GL_FLOAT_MAT4x3 0x8B6A
#define GL_SRGB 0x8C40
#define GL_SRGB8 0x8C41
#define GL_SRGB_ALPHA 0x8C42
#define GL_SRGB8_ALPHA8 0x8C43
#define GL_COMPRESSED_SRGB 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA 0x8C49
#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
#define GL_SLUMINANCE_ALPHA 0x8C44
#define GL_SLUMINANCE8_ALPHA8 0x8C45
#define GL_SLUMINANCE 0x8C46
#define GL_SLUMINANCE8 0x8C47
#define GL_COMPRESSED_SLUMINANCE 0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA 0x8C4B


typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

extern PFNGLUNIFORMMATRIX2X3FVPROC __gleUniformMatrix2x3fv;
#define glUniformMatrix2x3fv __gleUniformMatrix2x3fv
extern PFNGLUNIFORMMATRIX3X2FVPROC __gleUniformMatrix3x2fv;
#define glUniformMatrix3x2fv __gleUniformMatrix3x2fv
extern PFNGLUNIFORMMATRIX2X4FVPROC __gleUniformMatrix2x4fv;
#define glUniformMatrix2x4fv __gleUniformMatrix2x4fv
extern PFNGLUNIFORMMATRIX4X2FVPROC __gleUniformMatrix4x2fv;
#define glUniformMatrix4x2fv __gleUniformMatrix4x2fv
extern PFNGLUNIFORMMATRIX3X4FVPROC __gleUniformMatrix3x4fv;
#define glUniformMatrix3x4fv __gleUniformMatrix3x4fv
extern PFNGLUNIFORMMATRIX4X3FVPROC __gleUniformMatrix4x3fv;
#define glUniformMatrix4x3fv __gleUniformMatrix4x3fv


/******************************
* Version: 3.0
******************************/

#define GL_COMPARE_REF_TO_TEXTURE 0x884E
#define GL_CLIP_DISTANCE0 0x3000
#define GL_CLIP_DISTANCE1 0x3001
#define GL_CLIP_DISTANCE2 0x3002
#define GL_CLIP_DISTANCE3 0x3003
#define GL_CLIP_DISTANCE4 0x3004
#define GL_CLIP_DISTANCE5 0x3005
#define GL_CLIP_DISTANCE6 0x3006
#define GL_CLIP_DISTANCE7 0x3007
#define GL_MAX_CLIP_DISTANCES 0x0D32
#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
#define GL_NUM_EXTENSIONS 0x821D
#define GL_CONTEXT_FLAGS 0x821E
#define GL_DEPTH_BUFFER 0x8223
#define GL_STENCIL_BUFFER 0x8224
#define GL_COMPRESSED_RED 0x8225
#define GL_COMPRESSED_RG 0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x0001
#define GL_RGBA32F 0x8814
#define GL_RGB32F 0x8815
#define GL_RGBA16F 0x881A
#define GL_RGB16F 0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#define GL_CLAMP_READ_COLOR 0x891C
#define GL_FIXED_ONLY 0x891D
#define GL_TEXTURE_1D_ARRAY 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY 0x8C19
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY 0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#define GL_R11F_G11F_B10F 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#define GL_RGB9_E5 0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#define GL_TEXTURE_SHARED_SIZE 0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS 0x8C8C
#define GL_SEPARATE_ATTRIBS 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI 0x8D70
#define GL_RGB32UI 0x8D71
#define GL_RGBA16UI 0x8D76
#define GL_RGB16UI 0x8D77
#define GL_RGBA8UI 0x8D7C
#define GL_RGB8UI 0x8D7D
#define GL_RGBA32I 0x8D82
#define GL_RGB32I 0x8D83
#define GL_RGBA16I 0x8D88
#define GL_RGB16I 0x8D89
#define GL_RGBA8I 0x8D8E
#define GL_RGB8I 0x8D8F
#define GL_RED_INTEGER 0x8D94
#define GL_GREEN_INTEGER 0x8D95
#define GL_BLUE_INTEGER 0x8D96
#define GL_RGB_INTEGER 0x8D98
#define GL_RGBA_INTEGER 0x8D99
#define GL_BGR_INTEGER 0x8D9A
#define GL_BGRA_INTEGER 0x8D9B
#define GL_SAMPLER_1D_ARRAY 0x8DC0
#define GL_SAMPLER_2D_ARRAY 0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW 0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#define GL_UNSIGNED_INT_VEC2 0x8DC6
#define GL_UNSIGNED_INT_VEC3 0x8DC7
#define GL_UNSIGNED_INT_VEC4 0x8DC8
#define GL_INT_SAMPLER_1D 0x8DC9
#define GL_INT_SAMPLER_2D 0x8DCA
#define GL_INT_SAMPLER_3D 0x8DCB
#define GL_INT_SAMPLER_CUBE 0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY 0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D 0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#define GL_QUERY_WAIT 0x8E13
#define GL_QUERY_NO_WAIT 0x8E14
#define GL_QUERY_BY_REGION_WAIT 0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT 0x8E16
#define GL_BUFFER_ACCESS_FLAGS 0x911F
#define GL_BUFFER_MAP_LENGTH 0x9120
#define GL_BUFFER_MAP_OFFSET 0x9121
#define GL_DEPTH_COMPONENT32F 0x8CAC
#define GL_DEPTH32F_STENCIL8 0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_INDEX 0x8222
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#define GL_DEPTH_STENCIL 0x84F9
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_TEXTURE_STENCIL_SIZE 0x88F1
#define GL_TEXTURE_RED_TYPE 0x8C10
#define GL_TEXTURE_GREEN_TYPE 0x8C11
#define GL_TEXTURE_BLUE_TYPE 0x8C12
#define GL_TEXTURE_ALPHA_TYPE 0x8C13
#define GL_TEXTURE_DEPTH_TYPE 0x8C16
#define GL_UNSIGNED_NORMALIZED 0x8C17
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6 /* GL_FRAMEBUFFER_BINDING */
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#define GL_RENDERBUFFER_SAMPLES 0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_COLOR_ATTACHMENT4 0x8CE4
#define GL_COLOR_ATTACHMENT5 0x8CE5
#define GL_COLOR_ATTACHMENT6 0x8CE6
#define GL_COLOR_ATTACHMENT7 0x8CE7
#define GL_COLOR_ATTACHMENT8 0x8CE8
#define GL_COLOR_ATTACHMENT9 0x8CE9
#define GL_COLOR_ATTACHMENT10 0x8CEA
#define GL_COLOR_ATTACHMENT11 0x8CEB
#define GL_COLOR_ATTACHMENT12 0x8CEC
#define GL_COLOR_ATTACHMENT13 0x8CED
#define GL_COLOR_ATTACHMENT14 0x8CEE
#define GL_COLOR_ATTACHMENT15 0x8CEF
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_WIDTH 0x8D42
#define GL_RENDERBUFFER_HEIGHT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#define GL_STENCIL_INDEX1 0x8D46
#define GL_STENCIL_INDEX4 0x8D47
#define GL_STENCIL_INDEX8 0x8D48
#define GL_STENCIL_INDEX16 0x8D49
#define GL_RENDERBUFFER_RED_SIZE 0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES 0x8D57
#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_HALF_FLOAT 0x140B
#define GL_MAP_READ_BIT 0x0001
#define GL_MAP_WRITE_BIT 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT 0x0020
#define GL_COMPRESSED_RED_RGTC1 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#define GL_COMPRESSED_RG_RGTC2 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE
#define GL_RG 0x8227
#define GL_RG_INTEGER 0x8228
#define GL_R8 0x8229
#define GL_R16 0x822A
#define GL_RG8 0x822B
#define GL_RG16 0x822C
#define GL_R16F 0x822D
#define GL_R32F 0x822E
#define GL_RG16F 0x822F
#define GL_RG32F 0x8230
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823A
#define GL_RG32I 0x823B
#define GL_RG32UI 0x823C
#define GL_VERTEX_ARRAY_BINDING 0x85B5
#define GL_CLAMP_VERTEX_COLOR 0x891A
#define GL_CLAMP_FRAGMENT_COLOR 0x891B
#define GL_ALPHA_INTEGER 0x8D97
#define GL_TEXTURE_LUMINANCE_TYPE 0x8C14
#define GL_TEXTURE_INTENSITY_TYPE 0x8C15


typedef void (GLE_FUNCPTR * PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLENABLEIPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLDISABLEIPROC)(GLenum target, GLuint index);
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
typedef void (GLE_FUNCPTR * PFNGLENDTRANSFORMFEEDBACKPROC)();
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode);
typedef void (GLE_FUNCPTR * PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
typedef void (GLE_FUNCPTR * PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLENDCONDITIONALRENDERPROC)();
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);

extern PFNGLCOLORMASKIPROC __gleColorMaski;
#define glColorMaski __gleColorMaski
extern PFNGLGETBOOLEANI_VPROC __gleGetBooleani_v;
#define glGetBooleani_v __gleGetBooleani_v
extern PFNGLGETINTEGERI_VPROC __gleGetIntegeri_v;
#define glGetIntegeri_v __gleGetIntegeri_v
extern PFNGLENABLEIPROC __gleEnablei;
#define glEnablei __gleEnablei
extern PFNGLDISABLEIPROC __gleDisablei;
#define glDisablei __gleDisablei
extern PFNGLISENABLEDIPROC __gleIsEnabledi;
#define glIsEnabledi __gleIsEnabledi
extern PFNGLBEGINTRANSFORMFEEDBACKPROC __gleBeginTransformFeedback;
#define glBeginTransformFeedback __gleBeginTransformFeedback
extern PFNGLENDTRANSFORMFEEDBACKPROC __gleEndTransformFeedback;
#define glEndTransformFeedback __gleEndTransformFeedback
extern PFNGLBINDBUFFERRANGEPROC __gleBindBufferRange;
#define glBindBufferRange __gleBindBufferRange
extern PFNGLBINDBUFFERBASEPROC __gleBindBufferBase;
#define glBindBufferBase __gleBindBufferBase
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC __gleTransformFeedbackVaryings;
#define glTransformFeedbackVaryings __gleTransformFeedbackVaryings
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC __gleGetTransformFeedbackVarying;
#define glGetTransformFeedbackVarying __gleGetTransformFeedbackVarying
extern PFNGLCLAMPCOLORPROC __gleClampColor;
#define glClampColor __gleClampColor
extern PFNGLBEGINCONDITIONALRENDERPROC __gleBeginConditionalRender;
#define glBeginConditionalRender __gleBeginConditionalRender
extern PFNGLENDCONDITIONALRENDERPROC __gleEndConditionalRender;
#define glEndConditionalRender __gleEndConditionalRender
extern PFNGLVERTEXATTRIBIPOINTERPROC __gleVertexAttribIPointer;
#define glVertexAttribIPointer __gleVertexAttribIPointer
extern PFNGLGETVERTEXATTRIBIIVPROC __gleGetVertexAttribIiv;
#define glGetVertexAttribIiv __gleGetVertexAttribIiv
extern PFNGLGETVERTEXATTRIBIUIVPROC __gleGetVertexAttribIuiv;
#define glGetVertexAttribIuiv __gleGetVertexAttribIuiv
extern PFNGLVERTEXATTRIBI1IPROC __gleVertexAttribI1i;
#define glVertexAttribI1i __gleVertexAttribI1i
extern PFNGLVERTEXATTRIBI2IPROC __gleVertexAttribI2i;
#define glVertexAttribI2i __gleVertexAttribI2i
extern PFNGLVERTEXATTRIBI3IPROC __gleVertexAttribI3i;
#define glVertexAttribI3i __gleVertexAttribI3i
extern PFNGLVERTEXATTRIBI4IPROC __gleVertexAttribI4i;
#define glVertexAttribI4i __gleVertexAttribI4i
extern PFNGLVERTEXATTRIBI1UIPROC __gleVertexAttribI1ui;
#define glVertexAttribI1ui __gleVertexAttribI1ui
extern PFNGLVERTEXATTRIBI2UIPROC __gleVertexAttribI2ui;
#define glVertexAttribI2ui __gleVertexAttribI2ui
extern PFNGLVERTEXATTRIBI3UIPROC __gleVertexAttribI3ui;
#define glVertexAttribI3ui __gleVertexAttribI3ui
extern PFNGLVERTEXATTRIBI4UIPROC __gleVertexAttribI4ui;
#define glVertexAttribI4ui __gleVertexAttribI4ui
extern PFNGLVERTEXATTRIBI1IVPROC __gleVertexAttribI1iv;
#define glVertexAttribI1iv __gleVertexAttribI1iv
extern PFNGLVERTEXATTRIBI2IVPROC __gleVertexAttribI2iv;
#define glVertexAttribI2iv __gleVertexAttribI2iv
extern PFNGLVERTEXATTRIBI3IVPROC __gleVertexAttribI3iv;
#define glVertexAttribI3iv __gleVertexAttribI3iv
extern PFNGLVERTEXATTRIBI4IVPROC __gleVertexAttribI4iv;
#define glVertexAttribI4iv __gleVertexAttribI4iv
extern PFNGLVERTEXATTRIBI1UIVPROC __gleVertexAttribI1uiv;
#define glVertexAttribI1uiv __gleVertexAttribI1uiv
extern PFNGLVERTEXATTRIBI2UIVPROC __gleVertexAttribI2uiv;
#define glVertexAttribI2uiv __gleVertexAttribI2uiv
extern PFNGLVERTEXATTRIBI3UIVPROC __gleVertexAttribI3uiv;
#define glVertexAttribI3uiv __gleVertexAttribI3uiv
extern PFNGLVERTEXATTRIBI4UIVPROC __gleVertexAttribI4uiv;
#define glVertexAttribI4uiv __gleVertexAttribI4uiv
extern PFNGLVERTEXATTRIBI4BVPROC __gleVertexAttribI4bv;
#define glVertexAttribI4bv __gleVertexAttribI4bv
extern PFNGLVERTEXATTRIBI4SVPROC __gleVertexAttribI4sv;
#define glVertexAttribI4sv __gleVertexAttribI4sv
extern PFNGLVERTEXATTRIBI4UBVPROC __gleVertexAttribI4ubv;
#define glVertexAttribI4ubv __gleVertexAttribI4ubv
extern PFNGLVERTEXATTRIBI4USVPROC __gleVertexAttribI4usv;
#define glVertexAttribI4usv __gleVertexAttribI4usv
extern PFNGLGETUNIFORMUIVPROC __gleGetUniformuiv;
#define glGetUniformuiv __gleGetUniformuiv
extern PFNGLBINDFRAGDATALOCATIONPROC __gleBindFragDataLocation;
#define glBindFragDataLocation __gleBindFragDataLocation
extern PFNGLGETFRAGDATALOCATIONPROC __gleGetFragDataLocation;
#define glGetFragDataLocation __gleGetFragDataLocation
extern PFNGLUNIFORM1UIPROC __gleUniform1ui;
#define glUniform1ui __gleUniform1ui
extern PFNGLUNIFORM2UIPROC __gleUniform2ui;
#define glUniform2ui __gleUniform2ui
extern PFNGLUNIFORM3UIPROC __gleUniform3ui;
#define glUniform3ui __gleUniform3ui
extern PFNGLUNIFORM4UIPROC __gleUniform4ui;
#define glUniform4ui __gleUniform4ui
extern PFNGLUNIFORM1UIVPROC __gleUniform1uiv;
#define glUniform1uiv __gleUniform1uiv
extern PFNGLUNIFORM2UIVPROC __gleUniform2uiv;
#define glUniform2uiv __gleUniform2uiv
extern PFNGLUNIFORM3UIVPROC __gleUniform3uiv;
#define glUniform3uiv __gleUniform3uiv
extern PFNGLUNIFORM4UIVPROC __gleUniform4uiv;
#define glUniform4uiv __gleUniform4uiv
extern PFNGLTEXPARAMETERIIVPROC __gleTexParameterIiv;
#define glTexParameterIiv __gleTexParameterIiv
extern PFNGLTEXPARAMETERIUIVPROC __gleTexParameterIuiv;
#define glTexParameterIuiv __gleTexParameterIuiv
extern PFNGLGETTEXPARAMETERIIVPROC __gleGetTexParameterIiv;
#define glGetTexParameterIiv __gleGetTexParameterIiv
extern PFNGLGETTEXPARAMETERIUIVPROC __gleGetTexParameterIuiv;
#define glGetTexParameterIuiv __gleGetTexParameterIuiv
extern PFNGLCLEARBUFFERIVPROC __gleClearBufferiv;
#define glClearBufferiv __gleClearBufferiv
extern PFNGLCLEARBUFFERUIVPROC __gleClearBufferuiv;
#define glClearBufferuiv __gleClearBufferuiv
extern PFNGLCLEARBUFFERFVPROC __gleClearBufferfv;
#define glClearBufferfv __gleClearBufferfv
extern PFNGLCLEARBUFFERFIPROC __gleClearBufferfi;
#define glClearBufferfi __gleClearBufferfi
extern PFNGLGETSTRINGIPROC __gleGetStringi;
#define glGetStringi __gleGetStringi


/******************************
* Version: 3.1
******************************/

#define GL_SAMPLER_2D_RECT 0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW 0x8B64
#define GL_SAMPLER_BUFFER 0x8DC2
#define GL_INT_SAMPLER_2D_RECT 0x8DCD
#define GL_INT_SAMPLER_BUFFER 0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8DD8
#define GL_TEXTURE_BUFFER 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE 0x8C2B
#define GL_TEXTURE_BINDING_BUFFER 0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT 0x8C2E
#define GL_TEXTURE_RECTANGLE 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE 0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE 0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE 0x84F8
#define GL_RED_SNORM 0x8F90
#define GL_RG_SNORM 0x8F91
#define GL_RGB_SNORM 0x8F92
#define GL_RGBA_SNORM 0x8F93
#define GL_R8_SNORM 0x8F94
#define GL_RG8_SNORM 0x8F95
#define GL_RGB8_SNORM 0x8F96
#define GL_RGBA8_SNORM 0x8F97
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGBA16_SNORM 0x8F9B
#define GL_SIGNED_NORMALIZED 0x8F9C
#define GL_PRIMITIVE_RESTART 0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX 0x8F9E
#define GL_COPY_READ_BUFFER 0x8F36
#define GL_COPY_WRITE_BUFFER 0x8F37
#define GL_UNIFORM_BUFFER 0x8A11
#define GL_UNIFORM_BUFFER_BINDING 0x8A28
#define GL_UNIFORM_BUFFER_START 0x8A29
#define GL_UNIFORM_BUFFER_SIZE 0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS 0x8A36
#define GL_UNIFORM_TYPE 0x8A37
#define GL_UNIFORM_SIZE 0x8A38
#define GL_UNIFORM_NAME_LENGTH 0x8A39
#define GL_UNIFORM_BLOCK_INDEX 0x8A3A
#define GL_UNIFORM_OFFSET 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR 0x8A3E
#define GL_UNIFORM_BLOCK_BINDING 0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX 0xFFFFFFFF


typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);

extern PFNGLDRAWARRAYSINSTANCEDPROC __gleDrawArraysInstanced;
#define glDrawArraysInstanced __gleDrawArraysInstanced
extern PFNGLDRAWELEMENTSINSTANCEDPROC __gleDrawElementsInstanced;
#define glDrawElementsInstanced __gleDrawElementsInstanced
extern PFNGLTEXBUFFERPROC __gleTexBuffer;
#define glTexBuffer __gleTexBuffer
extern PFNGLPRIMITIVERESTARTINDEXPROC __glePrimitiveRestartIndex;
#define glPrimitiveRestartIndex __glePrimitiveRestartIndex


/******************************
* Version: 3.2
******************************/

#define GL_MAX_VARYING_COMPONENTS 0x8B4B
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY 0x000A
#define GL_LINE_STRIP_ADJACENCY 0x000B
#define GL_TRIANGLES_ADJACENCY 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_GEOMETRY_VERTICES_OUT 0x8916
#define GL_GEOMETRY_INPUT_TYPE 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#define GL_CONTEXT_PROFILE_MASK 0x9126
#define GL_DEPTH_CLAMP 0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#define GL_LAST_VERTEX_CONVENTION 0x8E4E
#define GL_PROVOKING_VERTEX 0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_OBJECT_TYPE 0x9112
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_STATUS 0x9114
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_UNSIGNALED 0x9118
#define GL_SIGNALED 0x9119
#define GL_ALREADY_SIGNALED 0x911A
#define GL_TIMEOUT_EXPIRED 0x911B
#define GL_CONDITION_SATISFIED 0x911C
#define GL_WAIT_FAILED 0x911D
#define GL_TIMEOUT_IGNORED 0xFFFFFFFFFFFFFFFF
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001
#define GL_SAMPLE_POSITION 0x8E50
#define GL_SAMPLE_MASK 0x8E51
#define GL_SAMPLE_MASK_VALUE 0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS 0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910F
#define GL_MAX_INTEGER_SAMPLES 0x9110


typedef void (GLE_FUNCPTR * PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 *data);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 *params);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);

extern PFNGLGETINTEGER64I_VPROC __gleGetInteger64i_v;
#define glGetInteger64i_v __gleGetInteger64i_v
extern PFNGLGETBUFFERPARAMETERI64VPROC __gleGetBufferParameteri64v;
#define glGetBufferParameteri64v __gleGetBufferParameteri64v
extern PFNGLFRAMEBUFFERTEXTUREPROC __gleFramebufferTexture;
#define glFramebufferTexture __gleFramebufferTexture




/******************************
* Extension: GL_3DFX_multisample
******************************/

#define GL_MULTISAMPLE_3DFX 0x86B2
#define GL_SAMPLE_BUFFERS_3DFX 0x86B3
#define GL_SAMPLES_3DFX 0x86B4
#define GL_MULTISAMPLE_BIT_3DFX 0x20000000


/******************************
* Extension: GL_3DFX_tbuffer
******************************/

typedef void (GLE_FUNCPTR * PFNGLTBUFFERMASK3DFXPROC)(GLuint mask);

extern PFNGLTBUFFERMASK3DFXPROC glTbufferMask3DFX;


/******************************
* Extension: GL_3DFX_texture_compression_FXT1
******************************/

#define GL_COMPRESSED_RGB_FXT1_3DFX 0x86B0
#define GL_COMPRESSED_RGBA_FXT1_3DFX 0x86B1


/******************************
* Extension: GL_AMD_conservative_depth
******************************/

/******************************
* Extension: GL_AMD_debug_output
******************************/

#define GL_MAX_DEBUG_LOGGED_MESSAGES_AMD 0x9144
#define GL_DEBUG_LOGGED_MESSAGES_AMD 0x9145
#define GL_DEBUG_SEVERITY_HIGH_AMD 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_AMD 0x9147
#define GL_DEBUG_SEVERITY_LOW_AMD 0x9148
#define GL_DEBUG_CATEGORY_API_ERROR_AMD 0x9149
#define GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD 0x914A
#define GL_DEBUG_CATEGORY_DEPRECATION_AMD 0x914B
#define GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD 0x914C
#define GL_DEBUG_CATEGORY_PERFORMANCE_AMD 0x914D
#define GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD 0x914E
#define GL_DEBUG_CATEGORY_APPLICATION_AMD 0x914F
#define GL_DEBUG_CATEGORY_OTHER_AMD 0x9150


typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEENABLEAMDPROC)(GLenum category, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEINSERTAMDPROC)(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar *buf);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECALLBACKAMDPROC)(GLDEBUGPROCAMD callback, GLvoid *userParam);
typedef GLuint (GLE_FUNCPTR * PFNGLGETDEBUGMESSAGELOGAMDPROC)(GLuint count, GLsizei bufsize, GLenum *categories, GLuint *severities, GLuint *ids, GLsizei *lengths, GLchar *message);

extern PFNGLDEBUGMESSAGEENABLEAMDPROC glDebugMessageEnableAMD;
extern PFNGLDEBUGMESSAGEINSERTAMDPROC glDebugMessageInsertAMD;
extern PFNGLDEBUGMESSAGECALLBACKAMDPROC glDebugMessageCallbackAMD;
extern PFNGLGETDEBUGMESSAGELOGAMDPROC glGetDebugMessageLogAMD;


/******************************
* Extension: GL_AMD_draw_buffers_blend
******************************/

typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCINDEXEDAMDPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONINDEXEDAMDPROC)(GLuint buf, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);

extern PFNGLBLENDFUNCINDEXEDAMDPROC glBlendFuncIndexedAMD;
extern PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC glBlendFuncSeparateIndexedAMD;
extern PFNGLBLENDEQUATIONINDEXEDAMDPROC glBlendEquationIndexedAMD;
extern PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC glBlendEquationSeparateIndexedAMD;


/******************************
* Extension: GL_AMD_name_gen_delete
******************************/

#define GL_DATA_BUFFER_AMD 0x9151
#define GL_PERFORMANCE_MONITOR_AMD 0x9152
#define GL_QUERY_OBJECT_AMD 0x9153
#define GL_VERTEX_ARRAY_OBJECT_AMD 0x9154
#define GL_SAMPLER_OBJECT_AMD 0x9155


typedef void (GLE_FUNCPTR * PFNGLGENNAMESAMDPROC)(GLenum identifier, GLuint num, GLuint *names);
typedef void (GLE_FUNCPTR * PFNGLDELETENAMESAMDPROC)(GLenum identifier, GLuint num, const GLuint *names);
typedef GLboolean (GLE_FUNCPTR * PFNGLISNAMEAMDPROC)(GLenum identifier, GLuint name);

extern PFNGLGENNAMESAMDPROC glGenNamesAMD;
extern PFNGLDELETENAMESAMDPROC glDeleteNamesAMD;
extern PFNGLISNAMEAMDPROC glIsNameAMD;


/******************************
* Extension: GL_AMD_performance_monitor
******************************/

#define GL_COUNTER_TYPE_AMD 0x8BC0
#define GL_COUNTER_RANGE_AMD 0x8BC1
#define GL_UNSIGNED_INT64_AMD 0x8BC2
#define GL_PERCENTAGE_AMD 0x8BC3
#define GL_PERFMON_RESULT_AVAILABLE_AMD 0x8BC4
#define GL_PERFMON_RESULT_SIZE_AMD 0x8BC5
#define GL_PERFMON_RESULT_AMD 0x8BC6


typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORGROUPSAMDPROC)(GLint *numGroups, GLsizei groupsSize, GLuint *groups);
typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORCOUNTERSAMDPROC)(GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters);
typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)(GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString);
typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)(GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString);
typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)(GLuint group, GLuint counter, GLenum pname, GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGENPERFMONITORSAMDPROC)(GLsizei n, GLuint *monitors);
typedef void (GLE_FUNCPTR * PFNGLDELETEPERFMONITORSAMDPROC)(GLsizei n, GLuint *monitors);
typedef void (GLE_FUNCPTR * PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList);
typedef void (GLE_FUNCPTR * PFNGLBEGINPERFMONITORAMDPROC)(GLuint monitor);
typedef void (GLE_FUNCPTR * PFNGLENDPERFMONITORAMDPROC)(GLuint monitor);
typedef void (GLE_FUNCPTR * PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten);

extern PFNGLGETPERFMONITORGROUPSAMDPROC glGetPerfMonitorGroupsAMD;
extern PFNGLGETPERFMONITORCOUNTERSAMDPROC glGetPerfMonitorCountersAMD;
extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC glGetPerfMonitorGroupStringAMD;
extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC glGetPerfMonitorCounterStringAMD;
extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC glGetPerfMonitorCounterInfoAMD;
extern PFNGLGENPERFMONITORSAMDPROC glGenPerfMonitorsAMD;
extern PFNGLDELETEPERFMONITORSAMDPROC glDeletePerfMonitorsAMD;
extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC glSelectPerfMonitorCountersAMD;
extern PFNGLBEGINPERFMONITORAMDPROC glBeginPerfMonitorAMD;
extern PFNGLENDPERFMONITORAMDPROC glEndPerfMonitorAMD;
extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC glGetPerfMonitorCounterDataAMD;


/******************************
* Extension: GL_AMD_seamless_cubemap_per_texture
******************************/

#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F


/******************************
* Extension: GL_AMD_shader_stencil_export
******************************/

/******************************
* Extension: GL_AMD_texture_texture4
******************************/

/******************************
* Extension: GL_AMD_transform_feedback3_lines_triangles
******************************/

/******************************
* Extension: GL_AMD_vertex_shader_tesselator
******************************/

#define GL_SAMPLER_BUFFER_AMD 0x9001
#define GL_INT_SAMPLER_BUFFER_AMD 0x9002
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD 0x9003
#define GL_TESSELLATION_MODE_AMD 0x9004
#define GL_TESSELLATION_FACTOR_AMD 0x9005
#define GL_DISCRETE_AMD 0x9006
#define GL_CONTINUOUS_AMD 0x9007


typedef void (GLE_FUNCPTR * PFNGLTESSELLATIONFACTORAMDPROC)(GLfloat factor);
typedef void (GLE_FUNCPTR * PFNGLTESSELLATIONMODEAMDPROC)(GLenum mode);

extern PFNGLTESSELLATIONFACTORAMDPROC glTessellationFactorAMD;
extern PFNGLTESSELLATIONMODEAMDPROC glTessellationModeAMD;


/******************************
* Extension: GL_APPLE_aux_depth_stencil
******************************/

#define GL_AUX_DEPTH_STENCIL_APPLE 0x8A14


/******************************
* Extension: GL_APPLE_client_storage
******************************/

#define GL_UNPACK_CLIENT_STORAGE_APPLE 0x85B2


/******************************
* Extension: GL_APPLE_element_array
******************************/

#define GL_ELEMENT_ARRAY_APPLE 0x8A0C
#define GL_ELEMENT_ARRAY_TYPE_APPLE 0x8A0D
#define GL_ELEMENT_ARRAY_POINTER_APPLE 0x8A0E


typedef void (GLE_FUNCPTR * PFNGLELEMENTPOINTERAPPLEPROC)(GLenum type, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTARRAYAPPLEPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);

extern PFNGLELEMENTPOINTERAPPLEPROC glElementPointerAPPLE;
extern PFNGLDRAWELEMENTARRAYAPPLEPROC glDrawElementArrayAPPLE;
extern PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC glDrawRangeElementArrayAPPLE;
extern PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC glMultiDrawElementArrayAPPLE;
extern PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC glMultiDrawRangeElementArrayAPPLE;


/******************************
* Extension: GL_APPLE_fence
******************************/

#define GL_DRAW_PIXELS_APPLE 0x8A0A
#define GL_FENCE_APPLE 0x8A0B


typedef void (GLE_FUNCPTR * PFNGLGENFENCESAPPLEPROC)(GLsizei n, GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLDELETEFENCESAPPLEPROC)(GLsizei n, const GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLSETFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTFENCEAPPLEPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLFINISHFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTOBJECTAPPLEPROC)(GLenum object, GLuint name);
typedef void (GLE_FUNCPTR * PFNGLFINISHOBJECTAPPLEPROC)(GLenum object, GLint name);

extern PFNGLGENFENCESAPPLEPROC glGenFencesAPPLE;
extern PFNGLDELETEFENCESAPPLEPROC glDeleteFencesAPPLE;
extern PFNGLSETFENCEAPPLEPROC glSetFenceAPPLE;
extern PFNGLISFENCEAPPLEPROC glIsFenceAPPLE;
extern PFNGLTESTFENCEAPPLEPROC glTestFenceAPPLE;
extern PFNGLFINISHFENCEAPPLEPROC glFinishFenceAPPLE;
extern PFNGLTESTOBJECTAPPLEPROC glTestObjectAPPLE;
extern PFNGLFINISHOBJECTAPPLEPROC glFinishObjectAPPLE;


/******************************
* Extension: GL_APPLE_float_pixels
******************************/

#define GL_HALF_APPLE 0x140B
#define GL_RGBA_FLOAT32_APPLE 0x8814
#define GL_RGB_FLOAT32_APPLE 0x8815
#define GL_ALPHA_FLOAT32_APPLE 0x8816
#define GL_INTENSITY_FLOAT32_APPLE 0x8817
#define GL_LUMINANCE_FLOAT32_APPLE 0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_APPLE 0x8819
#define GL_RGBA_FLOAT16_APPLE 0x881A
#define GL_RGB_FLOAT16_APPLE 0x881B
#define GL_ALPHA_FLOAT16_APPLE 0x881C
#define GL_INTENSITY_FLOAT16_APPLE 0x881D
#define GL_LUMINANCE_FLOAT16_APPLE 0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_APPLE 0x881F
#define GL_COLOR_FLOAT_APPLE 0x8A0F


/******************************
* Extension: GL_APPLE_flush_buffer_range
******************************/

#define GL_BUFFER_SERIALIZED_MODIFY_APPLE 0x8A12
#define GL_BUFFER_FLUSHING_UNMAP_APPLE 0x8A13


typedef void (GLE_FUNCPTR * PFNGLBUFFERPARAMETERIAPPLEPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)(GLenum target, GLintptr offset, GLsizeiptr size);

extern PFNGLBUFFERPARAMETERIAPPLEPROC glBufferParameteriAPPLE;
extern PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC glFlushMappedBufferRangeAPPLE;


/******************************
* Extension: GL_APPLE_object_purgeable
******************************/

#define GL_BUFFER_OBJECT_APPLE 0x85B3
#define GL_RELEASED_APPLE 0x8A19
#define GL_VOLATILE_APPLE 0x8A1A
#define GL_RETAINED_APPLE 0x8A1B
#define GL_UNDEFINED_APPLE 0x8A1C
#define GL_PURGEABLE_APPLE 0x8A1D


typedef GLenum (GLE_FUNCPTR * PFNGLOBJECTPURGEABLEAPPLEPROC)(GLenum objectType, GLuint name, GLenum option);
typedef GLenum (GLE_FUNCPTR * PFNGLOBJECTUNPURGEABLEAPPLEPROC)(GLenum objectType, GLuint name, GLenum option);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTPARAMETERIVAPPLEPROC)(GLenum objectType, GLuint name, GLenum pname, GLint *params);

extern PFNGLOBJECTPURGEABLEAPPLEPROC glObjectPurgeableAPPLE;
extern PFNGLOBJECTUNPURGEABLEAPPLEPROC glObjectUnpurgeableAPPLE;
extern PFNGLGETOBJECTPARAMETERIVAPPLEPROC glGetObjectParameterivAPPLE;


/******************************
* Extension: GL_APPLE_rgb_422
******************************/

#define GL_UNSIGNED_SHORT_8_8_APPLE 0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE 0x85BB
#define GL_RGB_422_APPLE 0x8A1F


/******************************
* Extension: GL_APPLE_row_bytes
******************************/

#define GL_PACK_ROW_BYTES_APPLE 0x8A15
#define GL_UNPACK_ROW_BYTES_APPLE 0x8A16


/******************************
* Extension: GL_APPLE_specular_vector
******************************/

#define GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE 0x85B0


/******************************
* Extension: GL_APPLE_texture_range
******************************/

#define GL_STORAGE_CACHED_APPLE 0x85BE
#define GL_STORAGE_SHARED_APPLE 0x85BF
#define GL_TEXTURE_RANGE_LENGTH_APPLE 0x85B7
#define GL_TEXTURE_RANGE_POINTER_APPLE 0x85B8
#define GL_TEXTURE_STORAGE_HINT_APPLE 0x85BC
#define GL_STORAGE_PRIVATE_APPLE 0x85BD


typedef void (GLE_FUNCPTR * PFNGLTEXTURERANGEAPPLEPROC)(GLenum target, GLsizei length, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)(GLenum target, GLenum pname, GLvoid* *params);

extern PFNGLTEXTURERANGEAPPLEPROC glTextureRangeAPPLE;
extern PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC glGetTexParameterPointervAPPLE;


/******************************
* Extension: GL_APPLE_transform_hint
******************************/

#define GL_TRANSFORM_HINT_APPLE 0x85B1


/******************************
* Extension: GL_APPLE_vertex_array_object
******************************/

#define GL_VERTEX_ARRAY_BINDING_APPLE 0x85B5


typedef void (GLE_FUNCPTR * PFNGLBINDVERTEXARRAYAPPLEPROC)(GLuint array);
typedef void (GLE_FUNCPTR * PFNGLDELETEVERTEXARRAYSAPPLEPROC)(GLsizei n, const GLuint *arrays);
typedef void (GLE_FUNCPTR * PFNGLGENVERTEXARRAYSAPPLEPROC)(GLsizei n, GLuint *arrays);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXARRAYAPPLEPROC)(GLuint array);

extern PFNGLBINDVERTEXARRAYAPPLEPROC glBindVertexArrayAPPLE;
extern PFNGLDELETEVERTEXARRAYSAPPLEPROC glDeleteVertexArraysAPPLE;
extern PFNGLGENVERTEXARRAYSAPPLEPROC glGenVertexArraysAPPLE;
extern PFNGLISVERTEXARRAYAPPLEPROC glIsVertexArrayAPPLE;


/******************************
* Extension: GL_APPLE_vertex_array_range
******************************/

#define GL_VERTEX_ARRAY_RANGE_APPLE 0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_APPLE 0x851E
#define GL_VERTEX_ARRAY_STORAGE_HINT_APPLE 0x851F
#define GL_VERTEX_ARRAY_RANGE_POINTER_APPLE 0x8521
#define GL_STORAGE_CLIENT_APPLE 0x85B4
#define GL_STORAGE_CACHED_APPLE 0x85BE
#define GL_STORAGE_SHARED_APPLE 0x85BF


typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYRANGEAPPLEPROC)(GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)(GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)(GLenum pname, GLint param);

extern PFNGLVERTEXARRAYRANGEAPPLEPROC glVertexArrayRangeAPPLE;
extern PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC glFlushVertexArrayRangeAPPLE;
extern PFNGLVERTEXARRAYPARAMETERIAPPLEPROC glVertexArrayParameteriAPPLE;


/******************************
* Extension: GL_APPLE_vertex_program_evaluators
******************************/

#define GL_VERTEX_ATTRIB_MAP1_APPLE 0x8A00
#define GL_VERTEX_ATTRIB_MAP2_APPLE 0x8A01
#define GL_VERTEX_ATTRIB_MAP1_SIZE_APPLE 0x8A02
#define GL_VERTEX_ATTRIB_MAP1_COEFF_APPLE 0x8A03
#define GL_VERTEX_ATTRIB_MAP1_ORDER_APPLE 0x8A04
#define GL_VERTEX_ATTRIB_MAP1_DOMAIN_APPLE 0x8A05
#define GL_VERTEX_ATTRIB_MAP2_SIZE_APPLE 0x8A06
#define GL_VERTEX_ATTRIB_MAP2_COEFF_APPLE 0x8A07
#define GL_VERTEX_ATTRIB_MAP2_ORDER_APPLE 0x8A08
#define GL_VERTEX_ATTRIB_MAP2_DOMAIN_APPLE 0x8A09


typedef void (GLE_FUNCPTR * PFNGLENABLEVERTEXATTRIBAPPLEPROC)(GLuint index, GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLDISABLEVERTEXATTRIBAPPLEPROC)(GLuint index, GLenum pname);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)(GLuint index, GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB1DAPPLEPROC)(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB1FAPPLEPROC)(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB2DAPPLEPROC)(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB2FAPPLEPROC)(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);

extern PFNGLENABLEVERTEXATTRIBAPPLEPROC glEnableVertexAttribAPPLE;
extern PFNGLDISABLEVERTEXATTRIBAPPLEPROC glDisableVertexAttribAPPLE;
extern PFNGLISVERTEXATTRIBENABLEDAPPLEPROC glIsVertexAttribEnabledAPPLE;
extern PFNGLMAPVERTEXATTRIB1DAPPLEPROC glMapVertexAttrib1dAPPLE;
extern PFNGLMAPVERTEXATTRIB1FAPPLEPROC glMapVertexAttrib1fAPPLE;
extern PFNGLMAPVERTEXATTRIB2DAPPLEPROC glMapVertexAttrib2dAPPLE;
extern PFNGLMAPVERTEXATTRIB2FAPPLEPROC glMapVertexAttrib2fAPPLE;


/******************************
* Extension: GL_APPLE_ycbcr_422
******************************/

#define GL_YCBCR_422_APPLE 0x85B9
#define GL_UNSIGNED_SHORT_8_8_APPLE 0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE 0x85BB


/******************************
* Extension: GL_ARB_ES2_compatibility
******************************/

#define GL_FIXED 0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_LOW_FLOAT 0x8DF0
#define GL_MEDIUM_FLOAT 0x8DF1
#define GL_HIGH_FLOAT 0x8DF2
#define GL_LOW_INT 0x8DF3
#define GL_MEDIUM_INT 0x8DF4
#define GL_HIGH_INT 0x8DF5
#define GL_SHADER_COMPILER 0x8DFA
#define GL_NUM_SHADER_BINARY_FORMATS 0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#define GL_MAX_VARYING_VECTORS 0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD


typedef void (GLE_FUNCPTR * PFNGLRELEASESHADERCOMPILERPROC)();
typedef void (GLE_FUNCPTR * PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const GLvoid *binary, GLsizei length);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEFPROC)(GLclampf n, GLclampf f);
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHFPROC)(GLclampf d);

extern PFNGLRELEASESHADERCOMPILERPROC __gleReleaseShaderCompiler;
#define glReleaseShaderCompiler __gleReleaseShaderCompiler
extern PFNGLSHADERBINARYPROC __gleShaderBinary;
#define glShaderBinary __gleShaderBinary
extern PFNGLGETSHADERPRECISIONFORMATPROC __gleGetShaderPrecisionFormat;
#define glGetShaderPrecisionFormat __gleGetShaderPrecisionFormat
extern PFNGLDEPTHRANGEFPROC __gleDepthRangef;
#define glDepthRangef __gleDepthRangef
extern PFNGLCLEARDEPTHFPROC __gleClearDepthf;
#define glClearDepthf __gleClearDepthf


/******************************
* Extension: GL_ARB_blend_func_extended
******************************/

#define GL_SRC1_ALPHA 0x8589
#define GL_SRC1_COLOR 0x88F9
#define GL_ONE_MINUS_SRC1_COLOR 0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA 0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88FC


typedef void (GLE_FUNCPTR * PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar *name);

extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC __gleBindFragDataLocationIndexed;
#define glBindFragDataLocationIndexed __gleBindFragDataLocationIndexed
extern PFNGLGETFRAGDATAINDEXPROC __gleGetFragDataIndex;
#define glGetFragDataIndex __gleGetFragDataIndex


/******************************
* Extension: GL_ARB_cl_event
******************************/

#define GL_SYNC_CL_EVENT_ARB 0x8240
#define GL_SYNC_CL_EVENT_COMPLETE_ARB 0x8241


typedef GLsync (GLE_FUNCPTR * PFNGLCREATESYNCFROMCLEVENTARBPROC)(struct _cl_context * context, struct _cl_event * event, GLbitfield flags);

extern PFNGLCREATESYNCFROMCLEVENTARBPROC glCreateSyncFromCLeventARB;


/******************************
* Extension: GL_ARB_color_buffer_float
******************************/

#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#define GL_CLAMP_VERTEX_COLOR_ARB 0x891A
#define GL_CLAMP_FRAGMENT_COLOR_ARB 0x891B
#define GL_CLAMP_READ_COLOR_ARB 0x891C
#define GL_FIXED_ONLY_ARB 0x891D


typedef void (GLE_FUNCPTR * PFNGLCLAMPCOLORARBPROC)(GLenum target, GLenum clamp);

extern PFNGLCLAMPCOLORARBPROC glClampColorARB;


/******************************
* Extension: GL_ARB_compatibility
******************************/

/******************************
* Extension: GL_ARB_copy_buffer
******************************/

#define GL_COPY_READ_BUFFER 0x8F36
#define GL_COPY_WRITE_BUFFER 0x8F37


typedef void (GLE_FUNCPTR * PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);

extern PFNGLCOPYBUFFERSUBDATAPROC __gleCopyBufferSubData;
#define glCopyBufferSubData __gleCopyBufferSubData


/******************************
* Extension: GL_ARB_debug_output
******************************/

#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB 0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB 0x8245
#define GL_DEBUG_SOURCE_API_ARB 0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB 0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB 0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB 0x824B
#define GL_DEBUG_TYPE_ERROR_ARB 0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB 0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB 0x8250
#define GL_DEBUG_TYPE_OTHER_ARB 0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB 0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB 0x9144
#define GL_DEBUG_LOGGED_MESSAGES_ARB 0x9145
#define GL_DEBUG_SEVERITY_HIGH_ARB 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB 0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB 0x9148


typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECONTROLARBPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEINSERTARBPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECALLBACKARBPROC)(GLDEBUGPROCARB callback, const GLvoid *userParam);
typedef GLuint (GLE_FUNCPTR * PFNGLGETDEBUGMESSAGELOGARBPROC)(GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);

extern PFNGLDEBUGMESSAGECONTROLARBPROC glDebugMessageControlARB;
extern PFNGLDEBUGMESSAGEINSERTARBPROC glDebugMessageInsertARB;
extern PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB;
extern PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageLogARB;


/******************************
* Extension: GL_ARB_depth_buffer_float
******************************/

#define GL_DEPTH_COMPONENT32F 0x8CAC
#define GL_DEPTH32F_STENCIL8 0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD


/******************************
* Extension: GL_ARB_depth_clamp
******************************/

#define GL_DEPTH_CLAMP 0x864F


/******************************
* Extension: GL_ARB_depth_texture
******************************/

#define GL_DEPTH_COMPONENT16_ARB 0x81A5
#define GL_DEPTH_COMPONENT24_ARB 0x81A6
#define GL_DEPTH_COMPONENT32_ARB 0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB 0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB 0x884B


/******************************
* Extension: GL_ARB_draw_buffers
******************************/

#define GL_MAX_DRAW_BUFFERS_ARB 0x8824
#define GL_DRAW_BUFFER0_ARB 0x8825
#define GL_DRAW_BUFFER1_ARB 0x8826
#define GL_DRAW_BUFFER2_ARB 0x8827
#define GL_DRAW_BUFFER3_ARB 0x8828
#define GL_DRAW_BUFFER4_ARB 0x8829
#define GL_DRAW_BUFFER5_ARB 0x882A
#define GL_DRAW_BUFFER6_ARB 0x882B
#define GL_DRAW_BUFFER7_ARB 0x882C
#define GL_DRAW_BUFFER8_ARB 0x882D
#define GL_DRAW_BUFFER9_ARB 0x882E
#define GL_DRAW_BUFFER10_ARB 0x882F
#define GL_DRAW_BUFFER11_ARB 0x8830
#define GL_DRAW_BUFFER12_ARB 0x8831
#define GL_DRAW_BUFFER13_ARB 0x8832
#define GL_DRAW_BUFFER14_ARB 0x8833
#define GL_DRAW_BUFFER15_ARB 0x8834


typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSARBPROC)(GLsizei n, const GLenum *bufs);

extern PFNGLDRAWBUFFERSARBPROC glDrawBuffersARB;


/******************************
* Extension: GL_ARB_draw_buffers_blend
******************************/

typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONIARBARBPROC)(GLuint buf, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEIARBARBPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCIARBARBPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEIARBARBPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

extern PFNGLBLENDEQUATIONIARBARBPROC glBlendEquationiARBARB;
extern PFNGLBLENDEQUATIONSEPARATEIARBARBPROC glBlendEquationSeparateiARBARB;
extern PFNGLBLENDFUNCIARBARBPROC glBlendFunciARBARB;
extern PFNGLBLENDFUNCSEPARATEIARBARBPROC glBlendFuncSeparateiARBARB;


/******************************
* Extension: GL_ARB_draw_elements_base_vertex
******************************/

typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount, const GLint *basevertex);

extern PFNGLDRAWELEMENTSBASEVERTEXPROC __gleDrawElementsBaseVertex;
#define glDrawElementsBaseVertex __gleDrawElementsBaseVertex
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC __gleDrawRangeElementsBaseVertex;
#define glDrawRangeElementsBaseVertex __gleDrawRangeElementsBaseVertex
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC __gleDrawElementsInstancedBaseVertex;
#define glDrawElementsInstancedBaseVertex __gleDrawElementsInstancedBaseVertex
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC __gleMultiDrawElementsBaseVertex;
#define glMultiDrawElementsBaseVertex __gleMultiDrawElementsBaseVertex


/******************************
* Extension: GL_ARB_draw_indirect
******************************/

#define GL_DRAW_INDIRECT_BUFFER 0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8F43


typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const GLvoid *indirect);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const GLvoid *indirect);

extern PFNGLDRAWARRAYSINDIRECTPROC __gleDrawArraysIndirect;
#define glDrawArraysIndirect __gleDrawArraysIndirect
extern PFNGLDRAWELEMENTSINDIRECTPROC __gleDrawElementsIndirect;
#define glDrawElementsIndirect __gleDrawElementsIndirect


/******************************
* Extension: GL_ARB_draw_instanced
******************************/

typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDARBPROC)(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDARBPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);

extern PFNGLDRAWARRAYSINSTANCEDARBPROC glDrawArraysInstancedARB;
extern PFNGLDRAWELEMENTSINSTANCEDARBPROC glDrawElementsInstancedARB;


/******************************
* Extension: GL_ARB_explicit_attrib_location
******************************/

/******************************
* Extension: GL_ARB_fragment_coord_conventions
******************************/

/******************************
* Extension: GL_ARB_fragment_program
******************************/

#define GL_FRAGMENT_PROGRAM_ARB 0x8804
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB 0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB 0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB 0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB 0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB 0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB 0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB 0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB 0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB 0x8810
#define GL_MAX_TEXTURE_COORDS_ARB 0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB 0x8872


/******************************
* Extension: GL_ARB_fragment_program_shadow
******************************/

/******************************
* Extension: GL_ARB_fragment_shader
******************************/

#define GL_FRAGMENT_SHADER_ARB 0x8B30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB 0x8B49
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB 0x8B8B


/******************************
* Extension: GL_ARB_framebuffer_object
******************************/

#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_INDEX 0x8222
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#define GL_DEPTH_STENCIL 0x84F9
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_TEXTURE_STENCIL_SIZE 0x88F1
#define GL_TEXTURE_RED_TYPE 0x8C10
#define GL_TEXTURE_GREEN_TYPE 0x8C11
#define GL_TEXTURE_BLUE_TYPE 0x8C12
#define GL_TEXTURE_ALPHA_TYPE 0x8C13
#define GL_TEXTURE_DEPTH_TYPE 0x8C16
#define GL_UNSIGNED_NORMALIZED 0x8C17
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6 /* GL_FRAMEBUFFER_BINDING */
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#define GL_RENDERBUFFER_SAMPLES 0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_COLOR_ATTACHMENT4 0x8CE4
#define GL_COLOR_ATTACHMENT5 0x8CE5
#define GL_COLOR_ATTACHMENT6 0x8CE6
#define GL_COLOR_ATTACHMENT7 0x8CE7
#define GL_COLOR_ATTACHMENT8 0x8CE8
#define GL_COLOR_ATTACHMENT9 0x8CE9
#define GL_COLOR_ATTACHMENT10 0x8CEA
#define GL_COLOR_ATTACHMENT11 0x8CEB
#define GL_COLOR_ATTACHMENT12 0x8CEC
#define GL_COLOR_ATTACHMENT13 0x8CED
#define GL_COLOR_ATTACHMENT14 0x8CEE
#define GL_COLOR_ATTACHMENT15 0x8CEF
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_WIDTH 0x8D42
#define GL_RENDERBUFFER_HEIGHT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#define GL_STENCIL_INDEX1 0x8D46
#define GL_STENCIL_INDEX4 0x8D47
#define GL_STENCIL_INDEX8 0x8D48
#define GL_STENCIL_INDEX16 0x8D49
#define GL_RENDERBUFFER_RED_SIZE 0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES 0x8D57
#define GL_TEXTURE_LUMINANCE_TYPE 0x8C14
#define GL_TEXTURE_INTENSITY_TYPE 0x8C15


typedef GLboolean (GLE_FUNCPTR * PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint *renderbuffers);
typedef void (GLE_FUNCPTR * PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint *renderbuffers);
typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
typedef void (GLE_FUNCPTR * PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void (GLE_FUNCPTR * PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint *framebuffers);
typedef void (GLE_FUNCPTR * PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint *framebuffers);
typedef GLenum (GLE_FUNCPTR * PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

extern PFNGLISRENDERBUFFERPROC __gleIsRenderbuffer;
#define glIsRenderbuffer __gleIsRenderbuffer
extern PFNGLBINDRENDERBUFFERPROC __gleBindRenderbuffer;
#define glBindRenderbuffer __gleBindRenderbuffer
extern PFNGLDELETERENDERBUFFERSPROC __gleDeleteRenderbuffers;
#define glDeleteRenderbuffers __gleDeleteRenderbuffers
extern PFNGLGENRENDERBUFFERSPROC __gleGenRenderbuffers;
#define glGenRenderbuffers __gleGenRenderbuffers
extern PFNGLRENDERBUFFERSTORAGEPROC __gleRenderbufferStorage;
#define glRenderbufferStorage __gleRenderbufferStorage
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC __gleGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv __gleGetRenderbufferParameteriv
extern PFNGLISFRAMEBUFFERPROC __gleIsFramebuffer;
#define glIsFramebuffer __gleIsFramebuffer
extern PFNGLBINDFRAMEBUFFERPROC __gleBindFramebuffer;
#define glBindFramebuffer __gleBindFramebuffer
extern PFNGLDELETEFRAMEBUFFERSPROC __gleDeleteFramebuffers;
#define glDeleteFramebuffers __gleDeleteFramebuffers
extern PFNGLGENFRAMEBUFFERSPROC __gleGenFramebuffers;
#define glGenFramebuffers __gleGenFramebuffers
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC __gleCheckFramebufferStatus;
#define glCheckFramebufferStatus __gleCheckFramebufferStatus
extern PFNGLFRAMEBUFFERTEXTURE1DPROC __gleFramebufferTexture1D;
#define glFramebufferTexture1D __gleFramebufferTexture1D
extern PFNGLFRAMEBUFFERTEXTURE2DPROC __gleFramebufferTexture2D;
#define glFramebufferTexture2D __gleFramebufferTexture2D
extern PFNGLFRAMEBUFFERTEXTURE3DPROC __gleFramebufferTexture3D;
#define glFramebufferTexture3D __gleFramebufferTexture3D
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC __gleFramebufferRenderbuffer;
#define glFramebufferRenderbuffer __gleFramebufferRenderbuffer
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC __gleGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv __gleGetFramebufferAttachmentParameteriv
extern PFNGLGENERATEMIPMAPPROC __gleGenerateMipmap;
#define glGenerateMipmap __gleGenerateMipmap
extern PFNGLBLITFRAMEBUFFERPROC __gleBlitFramebuffer;
#define glBlitFramebuffer __gleBlitFramebuffer
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC __gleRenderbufferStorageMultisample;
#define glRenderbufferStorageMultisample __gleRenderbufferStorageMultisample
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC __gleFramebufferTextureLayer;
#define glFramebufferTextureLayer __gleFramebufferTextureLayer


/******************************
* Extension: GL_ARB_framebuffer_sRGB
******************************/

#define GL_FRAMEBUFFER_SRGB 0x8DB9


/******************************
* Extension: GL_ARB_geometry_shader4
******************************/

#define GL_MAX_VARYING_COMPONENTS 0x8B4B
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_LINES_ADJACENCY_ARB 0x000A
#define GL_LINE_STRIP_ADJACENCY_ARB 0x000B
#define GL_TRIANGLES_ADJACENCY_ARB 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_ARB 0x000D
#define GL_PROGRAM_POINT_SIZE_ARB 0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB 0x8DA9
#define GL_GEOMETRY_SHADER_ARB 0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_ARB 0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_ARB 0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_ARB 0x8DDC
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB 0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_ARB 0x8DDE
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB 0x8DE1


typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIARBPROC)(GLuint program, GLenum pname, GLint value);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);

extern PFNGLPROGRAMPARAMETERIARBPROC glProgramParameteriARB;
extern PFNGLFRAMEBUFFERTEXTUREARBPROC glFramebufferTextureARB;
extern PFNGLFRAMEBUFFERTEXTURELAYERARBPROC glFramebufferTextureLayerARB;
extern PFNGLFRAMEBUFFERTEXTUREFACEARBPROC glFramebufferTextureFaceARB;


/******************************
* Extension: GL_ARB_get_program_binary
******************************/

#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH 0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS 0x87FE
#define GL_PROGRAM_BINARY_FORMATS 0x87FF


typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const GLvoid *binary, GLsizei length);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);

extern PFNGLGETPROGRAMBINARYPROC __gleGetProgramBinary;
#define glGetProgramBinary __gleGetProgramBinary
extern PFNGLPROGRAMBINARYPROC __gleProgramBinary;
#define glProgramBinary __gleProgramBinary
extern PFNGLPROGRAMPARAMETERIPROC __gleProgramParameteri;
#define glProgramParameteri __gleProgramParameteri


/******************************
* Extension: GL_ARB_gpu_shader5
******************************/

#define GL_GEOMETRY_SHADER_INVOCATIONS 0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_MAX_VERTEX_STREAMS 0x8E71


/******************************
* Extension: GL_ARB_gpu_shader_fp64
******************************/

#define GL_DOUBLE 0x140A
#define GL_DOUBLE_VEC2 0x8FFC
#define GL_DOUBLE_VEC3 0x8FFD
#define GL_DOUBLE_VEC4 0x8FFE
#define GL_DOUBLE_MAT2 0x8F46
#define GL_DOUBLE_MAT3 0x8F47
#define GL_DOUBLE_MAT4 0x8F48
#define GL_DOUBLE_MAT2x3 0x8F49
#define GL_DOUBLE_MAT2x4 0x8F4A
#define GL_DOUBLE_MAT3x2 0x8F4B
#define GL_DOUBLE_MAT3x4 0x8F4C
#define GL_DOUBLE_MAT4x2 0x8F4D
#define GL_DOUBLE_MAT4x3 0x8F4E


typedef void (GLE_FUNCPTR * PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble *params);

extern PFNGLUNIFORM1DPROC __gleUniform1d;
#define glUniform1d __gleUniform1d
extern PFNGLUNIFORM2DPROC __gleUniform2d;
#define glUniform2d __gleUniform2d
extern PFNGLUNIFORM3DPROC __gleUniform3d;
#define glUniform3d __gleUniform3d
extern PFNGLUNIFORM4DPROC __gleUniform4d;
#define glUniform4d __gleUniform4d
extern PFNGLUNIFORM1DVPROC __gleUniform1dv;
#define glUniform1dv __gleUniform1dv
extern PFNGLUNIFORM2DVPROC __gleUniform2dv;
#define glUniform2dv __gleUniform2dv
extern PFNGLUNIFORM3DVPROC __gleUniform3dv;
#define glUniform3dv __gleUniform3dv
extern PFNGLUNIFORM4DVPROC __gleUniform4dv;
#define glUniform4dv __gleUniform4dv
extern PFNGLUNIFORMMATRIX2DVPROC __gleUniformMatrix2dv;
#define glUniformMatrix2dv __gleUniformMatrix2dv
extern PFNGLUNIFORMMATRIX3DVPROC __gleUniformMatrix3dv;
#define glUniformMatrix3dv __gleUniformMatrix3dv
extern PFNGLUNIFORMMATRIX4DVPROC __gleUniformMatrix4dv;
#define glUniformMatrix4dv __gleUniformMatrix4dv
extern PFNGLUNIFORMMATRIX2X3DVPROC __gleUniformMatrix2x3dv;
#define glUniformMatrix2x3dv __gleUniformMatrix2x3dv
extern PFNGLUNIFORMMATRIX2X4DVPROC __gleUniformMatrix2x4dv;
#define glUniformMatrix2x4dv __gleUniformMatrix2x4dv
extern PFNGLUNIFORMMATRIX3X2DVPROC __gleUniformMatrix3x2dv;
#define glUniformMatrix3x2dv __gleUniformMatrix3x2dv
extern PFNGLUNIFORMMATRIX3X4DVPROC __gleUniformMatrix3x4dv;
#define glUniformMatrix3x4dv __gleUniformMatrix3x4dv
extern PFNGLUNIFORMMATRIX4X2DVPROC __gleUniformMatrix4x2dv;
#define glUniformMatrix4x2dv __gleUniformMatrix4x2dv
extern PFNGLUNIFORMMATRIX4X3DVPROC __gleUniformMatrix4x3dv;
#define glUniformMatrix4x3dv __gleUniformMatrix4x3dv
extern PFNGLGETUNIFORMDVPROC __gleGetUniformdv;
#define glGetUniformdv __gleGetUniformdv


/******************************
* Extension: GL_ARB_half_float_pixel
******************************/

#define GL_HALF_FLOAT_ARB 0x140B


/******************************
* Extension: GL_ARB_half_float_vertex
******************************/

#define GL_HALF_FLOAT 0x140B


/******************************
* Extension: GL_ARB_imaging
******************************/

#define GL_CONSTANT_COLOR 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_CONSTANT_ALPHA 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_BLEND_COLOR 0x8005
#define GL_FUNC_ADD 0x8006
#define GL_MIN 0x8007
#define GL_MAX 0x8008
#define GL_BLEND_EQUATION 0x8009
#define GL_FUNC_SUBTRACT 0x800A
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#define GL_CONVOLUTION_1D 0x8010
#define GL_CONVOLUTION_2D 0x8011
#define GL_SEPARABLE_2D 0x8012
#define GL_CONVOLUTION_BORDER_MODE 0x8013
#define GL_CONVOLUTION_FILTER_SCALE 0x8014
#define GL_CONVOLUTION_FILTER_BIAS 0x8015
#define GL_REDUCE 0x8016
#define GL_CONVOLUTION_FORMAT 0x8017
#define GL_CONVOLUTION_WIDTH 0x8018
#define GL_CONVOLUTION_HEIGHT 0x8019
#define GL_MAX_CONVOLUTION_WIDTH 0x801A
#define GL_MAX_CONVOLUTION_HEIGHT 0x801B
#define GL_POST_CONVOLUTION_RED_SCALE 0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE 0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE 0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE 0x801F
#define GL_POST_CONVOLUTION_RED_BIAS 0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS 0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS 0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS 0x8023
#define GL_HISTOGRAM 0x8024
#define GL_PROXY_HISTOGRAM 0x8025
#define GL_HISTOGRAM_WIDTH 0x8026
#define GL_HISTOGRAM_FORMAT 0x8027
#define GL_HISTOGRAM_RED_SIZE 0x8028
#define GL_HISTOGRAM_GREEN_SIZE 0x8029
#define GL_HISTOGRAM_BLUE_SIZE 0x802A
#define GL_HISTOGRAM_ALPHA_SIZE 0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE 0x802C
#define GL_HISTOGRAM_SINK 0x802D
#define GL_MINMAX 0x802E
#define GL_MINMAX_FORMAT 0x802F
#define GL_MINMAX_SINK 0x8030
#define GL_TABLE_TOO_LARGE 0x8031
#define GL_COLOR_MATRIX 0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH 0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH 0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE 0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE 0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE 0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE 0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS 0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS 0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS 0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS 0x80BB
#define GL_COLOR_TABLE 0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE 0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE 0x80D2
#define GL_PROXY_COLOR_TABLE 0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80D5
#define GL_COLOR_TABLE_SCALE 0x80D6
#define GL_COLOR_TABLE_BIAS 0x80D7
#define GL_COLOR_TABLE_FORMAT 0x80D8
#define GL_COLOR_TABLE_WIDTH 0x80D9
#define GL_COLOR_TABLE_RED_SIZE 0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE 0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE 0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE 0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE 0x80DF
#define GL_CONSTANT_BORDER 0x8151
#define GL_REPLICATE_BORDER 0x8153
#define GL_CONVOLUTION_BORDER_COLOR 0x8154


/******************************
* Extension: GL_ARB_instanced_arrays
******************************/

#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB 0x88FE


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBDIVISORARBPROC)(GLuint index, GLuint divisor);

extern PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisorARB;


/******************************
* Extension: GL_ARB_map_buffer_range
******************************/

#define GL_MAP_READ_BIT 0x0001
#define GL_MAP_WRITE_BIT 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT 0x0020


typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (GLE_FUNCPTR * PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);

extern PFNGLMAPBUFFERRANGEPROC __gleMapBufferRange;
#define glMapBufferRange __gleMapBufferRange
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC __gleFlushMappedBufferRange;
#define glFlushMappedBufferRange __gleFlushMappedBufferRange


/******************************
* Extension: GL_ARB_matrix_palette
******************************/

#define GL_MATRIX_PALETTE_ARB 0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB 0x8841
#define GL_MAX_PALETTE_MATRICES_ARB 0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB 0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB 0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB 0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB 0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB 0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB 0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB 0x8849


typedef void (GLE_FUNCPTR * PFNGLCURRENTPALETTEMATRIXARBPROC)(GLint index);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUBVARBPROC)(GLint size, const GLubyte *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUSVARBPROC)(GLint size, const GLushort *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUIVARBPROC)(GLint size, const GLuint *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXPOINTERARBPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern PFNGLCURRENTPALETTEMATRIXARBPROC glCurrentPaletteMatrixARB;
extern PFNGLMATRIXINDEXUBVARBPROC glMatrixIndexubvARB;
extern PFNGLMATRIXINDEXUSVARBPROC glMatrixIndexusvARB;
extern PFNGLMATRIXINDEXUIVARBPROC glMatrixIndexuivARB;
extern PFNGLMATRIXINDEXPOINTERARBPROC glMatrixIndexPointerARB;


/******************************
* Extension: GL_ARB_multisample
******************************/

#define GL_MULTISAMPLE_ARB 0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB 0x809F
#define GL_SAMPLE_COVERAGE_ARB 0x80A0
#define GL_SAMPLE_BUFFERS_ARB 0x80A8
#define GL_SAMPLES_ARB 0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB 0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB 0x80AB
#define GL_MULTISAMPLE_BIT_ARB 0x20000000


typedef void (GLE_FUNCPTR * PFNGLSAMPLECOVERAGEARBPROC)(GLclampf value, GLboolean invert);

extern PFNGLSAMPLECOVERAGEARBPROC glSampleCoverageARB;


/******************************
* Extension: GL_ARB_multitexture
******************************/

#define GL_TEXTURE0_ARB 0x84C0
#define GL_TEXTURE1_ARB 0x84C1
#define GL_TEXTURE2_ARB 0x84C2
#define GL_TEXTURE3_ARB 0x84C3
#define GL_TEXTURE4_ARB 0x84C4
#define GL_TEXTURE5_ARB 0x84C5
#define GL_TEXTURE6_ARB 0x84C6
#define GL_TEXTURE7_ARB 0x84C7
#define GL_TEXTURE8_ARB 0x84C8
#define GL_TEXTURE9_ARB 0x84C9
#define GL_TEXTURE10_ARB 0x84CA
#define GL_TEXTURE11_ARB 0x84CB
#define GL_TEXTURE12_ARB 0x84CC
#define GL_TEXTURE13_ARB 0x84CD
#define GL_TEXTURE14_ARB 0x84CE
#define GL_TEXTURE15_ARB 0x84CF
#define GL_TEXTURE16_ARB 0x84D0
#define GL_TEXTURE17_ARB 0x84D1
#define GL_TEXTURE18_ARB 0x84D2
#define GL_TEXTURE19_ARB 0x84D3
#define GL_TEXTURE20_ARB 0x84D4
#define GL_TEXTURE21_ARB 0x84D5
#define GL_TEXTURE22_ARB 0x84D6
#define GL_TEXTURE23_ARB 0x84D7
#define GL_TEXTURE24_ARB 0x84D8
#define GL_TEXTURE25_ARB 0x84D9
#define GL_TEXTURE26_ARB 0x84DA
#define GL_TEXTURE27_ARB 0x84DB
#define GL_TEXTURE28_ARB 0x84DC
#define GL_TEXTURE29_ARB 0x84DD
#define GL_TEXTURE30_ARB 0x84DE
#define GL_TEXTURE31_ARB 0x84DF
#define GL_ACTIVE_TEXTURE_ARB 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB 0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB 0x84E2


typedef void (GLE_FUNCPTR * PFNGLACTIVETEXTUREARBPROC)(GLenum texture);
typedef void (GLE_FUNCPTR * PFNGLCLIENTACTIVETEXTUREARBPROC)(GLenum texture);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DARBPROC)(GLenum target, GLdouble s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DVARBPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FARBPROC)(GLenum target, GLfloat s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FVARBPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IARBPROC)(GLenum target, GLint s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IVARBPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SARBPROC)(GLenum target, GLshort s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SVARBPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DARBPROC)(GLenum target, GLdouble s, GLdouble t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DVARBPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FARBPROC)(GLenum target, GLfloat s, GLfloat t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FVARBPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IARBPROC)(GLenum target, GLint s, GLint t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IVARBPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SARBPROC)(GLenum target, GLshort s, GLshort t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SVARBPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DARBPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DVARBPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FARBPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FVARBPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IARBPROC)(GLenum target, GLint s, GLint t, GLint r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IVARBPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SARBPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SVARBPROC)(GLenum target, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DARBPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DVARBPROC)(GLenum target, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FARBPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FVARBPROC)(GLenum target, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IARBPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IVARBPROC)(GLenum target, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SARBPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SVARBPROC)(GLenum target, const GLshort *v);

extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
extern PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;
extern PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;
extern PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;
extern PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;


/******************************
* Extension: GL_ARB_occlusion_query
******************************/

#define GL_QUERY_COUNTER_BITS_ARB 0x8864
#define GL_CURRENT_QUERY_ARB 0x8865
#define GL_QUERY_RESULT_ARB 0x8866
#define GL_QUERY_RESULT_AVAILABLE_ARB 0x8867
#define GL_SAMPLES_PASSED_ARB 0x8914


typedef void (GLE_FUNCPTR * PFNGLGENQUERIESARBPROC)(GLsizei n, GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLDELETEQUERIESARBPROC)(GLsizei n, const GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISQUERYARBPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYARBPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDQUERYARBPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYIVARBPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTIVARBPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUIVARBPROC)(GLuint id, GLenum pname, GLuint *params);

extern PFNGLGENQUERIESARBPROC glGenQueriesARB;
extern PFNGLDELETEQUERIESARBPROC glDeleteQueriesARB;
extern PFNGLISQUERYARBPROC glIsQueryARB;
extern PFNGLBEGINQUERYARBPROC glBeginQueryARB;
extern PFNGLENDQUERYARBPROC glEndQueryARB;
extern PFNGLGETQUERYIVARBPROC glGetQueryivARB;
extern PFNGLGETQUERYOBJECTIVARBPROC glGetQueryObjectivARB;
extern PFNGLGETQUERYOBJECTUIVARBPROC glGetQueryObjectuivARB;


/******************************
* Extension: GL_ARB_occlusion_query2
******************************/

#define GL_ANY_SAMPLES_PASSED 0x8C2F


/******************************
* Extension: GL_ARB_pixel_buffer_object
******************************/

#define GL_PIXEL_PACK_BUFFER_ARB 0x88EB
#define GL_PIXEL_UNPACK_BUFFER_ARB 0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB 0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB 0x88EF


/******************************
* Extension: GL_ARB_point_parameters
******************************/

#define GL_POINT_SIZE_MIN_ARB 0x8126
#define GL_POINT_SIZE_MAX_ARB 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB 0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB 0x8129


typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFARBPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVARBPROC)(GLenum pname, const GLfloat *params);

extern PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;


/******************************
* Extension: GL_ARB_point_sprite
******************************/

#define GL_POINT_SPRITE_ARB 0x8861
#define GL_COORD_REPLACE_ARB 0x8862


/******************************
* Extension: GL_ARB_provoking_vertex
******************************/

#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#define GL_LAST_VERTEX_CONVENTION 0x8E4E
#define GL_PROVOKING_VERTEX 0x8E4F


typedef void (GLE_FUNCPTR * PFNGLPROVOKINGVERTEXPROC)(GLenum mode);

extern PFNGLPROVOKINGVERTEXPROC __gleProvokingVertex;
#define glProvokingVertex __gleProvokingVertex


/******************************
* Extension: GL_ARB_robustness
******************************/

#define GL_NO_ERROR 0
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB 0x00000004
#define GL_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#define GL_GUILTY_CONTEXT_RESET_ARB 0x8253
#define GL_INNOCENT_CONTEXT_RESET_ARB 0x8254
#define GL_UNKNOWN_CONTEXT_RESET_ARB 0x8255
#define GL_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GL_NO_RESET_NOTIFICATION_ARB 0x8261


typedef GLenum (GLE_FUNCPTR * PFNGLGETGRAPHICSRESETSTATUSARBPROC)();
typedef void (GLE_FUNCPTR * PFNGLGETNMAPDVARBPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLGETNMAPFVARBPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLGETNMAPIVARBPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
typedef void (GLE_FUNCPTR * PFNGLGETNPIXELMAPFVARBPROC)(GLenum map, GLsizei bufSize, GLfloat *values);
typedef void (GLE_FUNCPTR * PFNGLGETNPIXELMAPUIVARBPROC)(GLenum map, GLsizei bufSize, GLuint *values);
typedef void (GLE_FUNCPTR * PFNGLGETNPIXELMAPUSVARBPROC)(GLenum map, GLsizei bufSize, GLushort *values);
typedef void (GLE_FUNCPTR * PFNGLGETNPOLYGONSTIPPLEARBPROC)(GLsizei bufSize, GLubyte *pattern);
typedef void (GLE_FUNCPTR * PFNGLGETNCOLORTABLEARBPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETNCONVOLUTIONFILTERARBPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLGETNSEPARABLEFILTERARBPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, GLvoid *row, GLsizei columnBufSize, GLvoid *column, GLvoid *span);
typedef void (GLE_FUNCPTR * PFNGLGETNHISTOGRAMARBPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETNMINMAXARBPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETNTEXIMAGEARBPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid *img);
typedef void (GLE_FUNCPTR * PFNGLREADNPIXELSARBPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)(GLenum target, GLint lod, GLsizei bufSize, GLvoid *img);
typedef void (GLE_FUNCPTR * PFNGLGETNUNIFORMFVARBPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETNUNIFORMIVARBPROC)(GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNUNIFORMUIVARBPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNUNIFORMDVARBPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);

extern PFNGLGETGRAPHICSRESETSTATUSARBPROC glGetGraphicsResetStatusARB;
extern PFNGLGETNMAPDVARBPROC glGetnMapdvARB;
extern PFNGLGETNMAPFVARBPROC glGetnMapfvARB;
extern PFNGLGETNMAPIVARBPROC glGetnMapivARB;
extern PFNGLGETNPIXELMAPFVARBPROC glGetnPixelMapfvARB;
extern PFNGLGETNPIXELMAPUIVARBPROC glGetnPixelMapuivARB;
extern PFNGLGETNPIXELMAPUSVARBPROC glGetnPixelMapusvARB;
extern PFNGLGETNPOLYGONSTIPPLEARBPROC glGetnPolygonStippleARB;
extern PFNGLGETNCOLORTABLEARBPROC glGetnColorTableARB;
extern PFNGLGETNCONVOLUTIONFILTERARBPROC glGetnConvolutionFilterARB;
extern PFNGLGETNSEPARABLEFILTERARBPROC glGetnSeparableFilterARB;
extern PFNGLGETNHISTOGRAMARBPROC glGetnHistogramARB;
extern PFNGLGETNMINMAXARBPROC glGetnMinmaxARB;
extern PFNGLGETNTEXIMAGEARBPROC glGetnTexImageARB;
extern PFNGLREADNPIXELSARBPROC glReadnPixelsARB;
extern PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC glGetnCompressedTexImageARB;
extern PFNGLGETNUNIFORMFVARBPROC glGetnUniformfvARB;
extern PFNGLGETNUNIFORMIVARBPROC glGetnUniformivARB;
extern PFNGLGETNUNIFORMUIVARBPROC glGetnUniformuivARB;
extern PFNGLGETNUNIFORMDVARBPROC glGetnUniformdvARB;


/******************************
* Extension: GL_ARB_sample_shading
******************************/

#define GL_SAMPLE_SHADING_ARB_ARB 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE_ARB_ARB 0x8C37


typedef void (GLE_FUNCPTR * PFNGLMINSAMPLESHADINGARBARBPROC)(GLclampf value);

extern PFNGLMINSAMPLESHADINGARBARBPROC glMinSampleShadingARBARB;


/******************************
* Extension: GL_ARB_sampler_objects
******************************/

#define GL_SAMPLER_BINDING 0x8919


typedef void (GLE_FUNCPTR * PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint *samplers);
typedef void (GLE_FUNCPTR * PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint *samplers);
typedef GLboolean (GLE_FUNCPTR * PFNGLISSAMPLERPROC)(GLuint sampler);
typedef void (GLE_FUNCPTR * PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint *param);
typedef void (GLE_FUNCPTR * PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint *param);
typedef void (GLE_FUNCPTR * PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint *params);

extern PFNGLGENSAMPLERSPROC __gleGenSamplers;
#define glGenSamplers __gleGenSamplers
extern PFNGLDELETESAMPLERSPROC __gleDeleteSamplers;
#define glDeleteSamplers __gleDeleteSamplers
extern PFNGLISSAMPLERPROC __gleIsSampler;
#define glIsSampler __gleIsSampler
extern PFNGLBINDSAMPLERPROC __gleBindSampler;
#define glBindSampler __gleBindSampler
extern PFNGLSAMPLERPARAMETERIPROC __gleSamplerParameteri;
#define glSamplerParameteri __gleSamplerParameteri
extern PFNGLSAMPLERPARAMETERIVPROC __gleSamplerParameteriv;
#define glSamplerParameteriv __gleSamplerParameteriv
extern PFNGLSAMPLERPARAMETERFPROC __gleSamplerParameterf;
#define glSamplerParameterf __gleSamplerParameterf
extern PFNGLSAMPLERPARAMETERFVPROC __gleSamplerParameterfv;
#define glSamplerParameterfv __gleSamplerParameterfv
extern PFNGLSAMPLERPARAMETERIIVPROC __gleSamplerParameterIiv;
#define glSamplerParameterIiv __gleSamplerParameterIiv
extern PFNGLSAMPLERPARAMETERIUIVPROC __gleSamplerParameterIuiv;
#define glSamplerParameterIuiv __gleSamplerParameterIuiv
extern PFNGLGETSAMPLERPARAMETERIVPROC __gleGetSamplerParameteriv;
#define glGetSamplerParameteriv __gleGetSamplerParameteriv
extern PFNGLGETSAMPLERPARAMETERIIVPROC __gleGetSamplerParameterIiv;
#define glGetSamplerParameterIiv __gleGetSamplerParameterIiv
extern PFNGLGETSAMPLERPARAMETERFVPROC __gleGetSamplerParameterfv;
#define glGetSamplerParameterfv __gleGetSamplerParameterfv
extern PFNGLGETSAMPLERPARAMETERIUIVPROC __gleGetSamplerParameterIuiv;
#define glGetSamplerParameterIuiv __gleGetSamplerParameterIuiv


/******************************
* Extension: GL_ARB_seamless_cube_map
******************************/

#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F


/******************************
* Extension: GL_ARB_separate_shader_objects
******************************/

#define GL_VERTEX_SHADER_BIT 0x00000001
#define GL_FRAGMENT_SHADER_BIT 0x00000002
#define GL_GEOMETRY_SHADER_BIT 0x00000004
#define GL_TESS_CONTROL_SHADER_BIT 0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT 0x00000010
#define GL_ALL_SHADER_BITS 0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE 0x8258
#define GL_ACTIVE_PROGRAM 0x8259
#define GL_PROGRAM_PIPELINE_BINDING 0x825A


typedef void (GLE_FUNCPTR * PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (GLE_FUNCPTR * PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
typedef GLuint (GLE_FUNCPTR * PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar* *strings);
typedef void (GLE_FUNCPTR * PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (GLE_FUNCPTR * PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint *pipelines);
typedef void (GLE_FUNCPTR * PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint *pipelines);
typedef GLboolean (GLE_FUNCPTR * PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

extern PFNGLUSEPROGRAMSTAGESPROC __gleUseProgramStages;
#define glUseProgramStages __gleUseProgramStages
extern PFNGLACTIVESHADERPROGRAMPROC __gleActiveShaderProgram;
#define glActiveShaderProgram __gleActiveShaderProgram
extern PFNGLCREATESHADERPROGRAMVPROC __gleCreateShaderProgramv;
#define glCreateShaderProgramv __gleCreateShaderProgramv
extern PFNGLBINDPROGRAMPIPELINEPROC __gleBindProgramPipeline;
#define glBindProgramPipeline __gleBindProgramPipeline
extern PFNGLDELETEPROGRAMPIPELINESPROC __gleDeleteProgramPipelines;
#define glDeleteProgramPipelines __gleDeleteProgramPipelines
extern PFNGLGENPROGRAMPIPELINESPROC __gleGenProgramPipelines;
#define glGenProgramPipelines __gleGenProgramPipelines
extern PFNGLISPROGRAMPIPELINEPROC __gleIsProgramPipeline;
#define glIsProgramPipeline __gleIsProgramPipeline
extern PFNGLGETPROGRAMPIPELINEIVPROC __gleGetProgramPipelineiv;
#define glGetProgramPipelineiv __gleGetProgramPipelineiv
extern PFNGLPROGRAMUNIFORM1IPROC __gleProgramUniform1i;
#define glProgramUniform1i __gleProgramUniform1i
extern PFNGLPROGRAMUNIFORM1IVPROC __gleProgramUniform1iv;
#define glProgramUniform1iv __gleProgramUniform1iv
extern PFNGLPROGRAMUNIFORM1FPROC __gleProgramUniform1f;
#define glProgramUniform1f __gleProgramUniform1f
extern PFNGLPROGRAMUNIFORM1FVPROC __gleProgramUniform1fv;
#define glProgramUniform1fv __gleProgramUniform1fv
extern PFNGLPROGRAMUNIFORM1DPROC __gleProgramUniform1d;
#define glProgramUniform1d __gleProgramUniform1d
extern PFNGLPROGRAMUNIFORM1DVPROC __gleProgramUniform1dv;
#define glProgramUniform1dv __gleProgramUniform1dv
extern PFNGLPROGRAMUNIFORM1UIPROC __gleProgramUniform1ui;
#define glProgramUniform1ui __gleProgramUniform1ui
extern PFNGLPROGRAMUNIFORM1UIVPROC __gleProgramUniform1uiv;
#define glProgramUniform1uiv __gleProgramUniform1uiv
extern PFNGLPROGRAMUNIFORM2IPROC __gleProgramUniform2i;
#define glProgramUniform2i __gleProgramUniform2i
extern PFNGLPROGRAMUNIFORM2IVPROC __gleProgramUniform2iv;
#define glProgramUniform2iv __gleProgramUniform2iv
extern PFNGLPROGRAMUNIFORM2FPROC __gleProgramUniform2f;
#define glProgramUniform2f __gleProgramUniform2f
extern PFNGLPROGRAMUNIFORM2FVPROC __gleProgramUniform2fv;
#define glProgramUniform2fv __gleProgramUniform2fv
extern PFNGLPROGRAMUNIFORM2DPROC __gleProgramUniform2d;
#define glProgramUniform2d __gleProgramUniform2d
extern PFNGLPROGRAMUNIFORM2DVPROC __gleProgramUniform2dv;
#define glProgramUniform2dv __gleProgramUniform2dv
extern PFNGLPROGRAMUNIFORM2UIPROC __gleProgramUniform2ui;
#define glProgramUniform2ui __gleProgramUniform2ui
extern PFNGLPROGRAMUNIFORM2UIVPROC __gleProgramUniform2uiv;
#define glProgramUniform2uiv __gleProgramUniform2uiv
extern PFNGLPROGRAMUNIFORM3IPROC __gleProgramUniform3i;
#define glProgramUniform3i __gleProgramUniform3i
extern PFNGLPROGRAMUNIFORM3IVPROC __gleProgramUniform3iv;
#define glProgramUniform3iv __gleProgramUniform3iv
extern PFNGLPROGRAMUNIFORM3FPROC __gleProgramUniform3f;
#define glProgramUniform3f __gleProgramUniform3f
extern PFNGLPROGRAMUNIFORM3FVPROC __gleProgramUniform3fv;
#define glProgramUniform3fv __gleProgramUniform3fv
extern PFNGLPROGRAMUNIFORM3DPROC __gleProgramUniform3d;
#define glProgramUniform3d __gleProgramUniform3d
extern PFNGLPROGRAMUNIFORM3DVPROC __gleProgramUniform3dv;
#define glProgramUniform3dv __gleProgramUniform3dv
extern PFNGLPROGRAMUNIFORM3UIPROC __gleProgramUniform3ui;
#define glProgramUniform3ui __gleProgramUniform3ui
extern PFNGLPROGRAMUNIFORM3UIVPROC __gleProgramUniform3uiv;
#define glProgramUniform3uiv __gleProgramUniform3uiv
extern PFNGLPROGRAMUNIFORM4IPROC __gleProgramUniform4i;
#define glProgramUniform4i __gleProgramUniform4i
extern PFNGLPROGRAMUNIFORM4IVPROC __gleProgramUniform4iv;
#define glProgramUniform4iv __gleProgramUniform4iv
extern PFNGLPROGRAMUNIFORM4FPROC __gleProgramUniform4f;
#define glProgramUniform4f __gleProgramUniform4f
extern PFNGLPROGRAMUNIFORM4FVPROC __gleProgramUniform4fv;
#define glProgramUniform4fv __gleProgramUniform4fv
extern PFNGLPROGRAMUNIFORM4DPROC __gleProgramUniform4d;
#define glProgramUniform4d __gleProgramUniform4d
extern PFNGLPROGRAMUNIFORM4DVPROC __gleProgramUniform4dv;
#define glProgramUniform4dv __gleProgramUniform4dv
extern PFNGLPROGRAMUNIFORM4UIPROC __gleProgramUniform4ui;
#define glProgramUniform4ui __gleProgramUniform4ui
extern PFNGLPROGRAMUNIFORM4UIVPROC __gleProgramUniform4uiv;
#define glProgramUniform4uiv __gleProgramUniform4uiv
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC __gleProgramUniformMatrix2fv;
#define glProgramUniformMatrix2fv __gleProgramUniformMatrix2fv
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC __gleProgramUniformMatrix3fv;
#define glProgramUniformMatrix3fv __gleProgramUniformMatrix3fv
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC __gleProgramUniformMatrix4fv;
#define glProgramUniformMatrix4fv __gleProgramUniformMatrix4fv
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC __gleProgramUniformMatrix2dv;
#define glProgramUniformMatrix2dv __gleProgramUniformMatrix2dv
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC __gleProgramUniformMatrix3dv;
#define glProgramUniformMatrix3dv __gleProgramUniformMatrix3dv
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC __gleProgramUniformMatrix4dv;
#define glProgramUniformMatrix4dv __gleProgramUniformMatrix4dv
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC __gleProgramUniformMatrix2x3fv;
#define glProgramUniformMatrix2x3fv __gleProgramUniformMatrix2x3fv
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC __gleProgramUniformMatrix3x2fv;
#define glProgramUniformMatrix3x2fv __gleProgramUniformMatrix3x2fv
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC __gleProgramUniformMatrix2x4fv;
#define glProgramUniformMatrix2x4fv __gleProgramUniformMatrix2x4fv
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC __gleProgramUniformMatrix4x2fv;
#define glProgramUniformMatrix4x2fv __gleProgramUniformMatrix4x2fv
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC __gleProgramUniformMatrix3x4fv;
#define glProgramUniformMatrix3x4fv __gleProgramUniformMatrix3x4fv
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC __gleProgramUniformMatrix4x3fv;
#define glProgramUniformMatrix4x3fv __gleProgramUniformMatrix4x3fv
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC __gleProgramUniformMatrix2x3dv;
#define glProgramUniformMatrix2x3dv __gleProgramUniformMatrix2x3dv
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC __gleProgramUniformMatrix3x2dv;
#define glProgramUniformMatrix3x2dv __gleProgramUniformMatrix3x2dv
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC __gleProgramUniformMatrix2x4dv;
#define glProgramUniformMatrix2x4dv __gleProgramUniformMatrix2x4dv
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC __gleProgramUniformMatrix4x2dv;
#define glProgramUniformMatrix4x2dv __gleProgramUniformMatrix4x2dv
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC __gleProgramUniformMatrix3x4dv;
#define glProgramUniformMatrix3x4dv __gleProgramUniformMatrix3x4dv
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC __gleProgramUniformMatrix4x3dv;
#define glProgramUniformMatrix4x3dv __gleProgramUniformMatrix4x3dv
extern PFNGLVALIDATEPROGRAMPIPELINEPROC __gleValidateProgramPipeline;
#define glValidateProgramPipeline __gleValidateProgramPipeline
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC __gleGetProgramPipelineInfoLog;
#define glGetProgramPipelineInfoLog __gleGetProgramPipelineInfoLog


/******************************
* Extension: GL_ARB_shader_bit_encoding
******************************/

/******************************
* Extension: GL_ARB_shader_objects
******************************/

#define GL_PROGRAM_OBJECT_ARB 0x8B40
#define GL_SHADER_OBJECT_ARB 0x8B48
#define GL_OBJECT_TYPE_ARB 0x8B4E
#define GL_OBJECT_SUBTYPE_ARB 0x8B4F
#define GL_FLOAT_VEC2_ARB 0x8B50
#define GL_FLOAT_VEC3_ARB 0x8B51
#define GL_FLOAT_VEC4_ARB 0x8B52
#define GL_INT_VEC2_ARB 0x8B53
#define GL_INT_VEC3_ARB 0x8B54
#define GL_INT_VEC4_ARB 0x8B55
#define GL_BOOL_ARB 0x8B56
#define GL_BOOL_VEC2_ARB 0x8B57
#define GL_BOOL_VEC3_ARB 0x8B58
#define GL_BOOL_VEC4_ARB 0x8B59
#define GL_FLOAT_MAT2_ARB 0x8B5A
#define GL_FLOAT_MAT3_ARB 0x8B5B
#define GL_FLOAT_MAT4_ARB 0x8B5C
#define GL_SAMPLER_1D_ARB 0x8B5D
#define GL_SAMPLER_2D_ARB 0x8B5E
#define GL_SAMPLER_3D_ARB 0x8B5F
#define GL_SAMPLER_CUBE_ARB 0x8B60
#define GL_SAMPLER_1D_SHADOW_ARB 0x8B61
#define GL_SAMPLER_2D_SHADOW_ARB 0x8B62
#define GL_SAMPLER_2D_RECT_ARB 0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB 0x8B64
#define GL_OBJECT_DELETE_STATUS_ARB 0x8B80
#define GL_OBJECT_COMPILE_STATUS_ARB 0x8B81
#define GL_OBJECT_LINK_STATUS_ARB 0x8B82
#define GL_OBJECT_VALIDATE_STATUS_ARB 0x8B83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB 0x8B84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB 0x8B85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB 0x8B86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB 0x8B87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB 0x8B88


typedef void (GLE_FUNCPTR * PFNGLDELETEOBJECTARBPROC)(GLhandleARB obj);
typedef GLhandleARB (GLE_FUNCPTR * PFNGLGETHANDLEARBPROC)(GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLDETACHOBJECTARBPROC)(GLhandleARB containerObj, GLhandleARB attachedObj);
typedef GLhandleARB (GLE_FUNCPTR * PFNGLCREATESHADEROBJECTARBPROC)(GLenum shaderType);
typedef void (GLE_FUNCPTR * PFNGLSHADERSOURCEARBPROC)(GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length);
typedef void (GLE_FUNCPTR * PFNGLCOMPILESHADERARBPROC)(GLhandleARB shaderObj);
typedef GLhandleARB (GLE_FUNCPTR * PFNGLCREATEPROGRAMOBJECTARBPROC)();
typedef void (GLE_FUNCPTR * PFNGLATTACHOBJECTARBPROC)(GLhandleARB containerObj, GLhandleARB obj);
typedef void (GLE_FUNCPTR * PFNGLLINKPROGRAMARBPROC)(GLhandleARB programObj);
typedef void (GLE_FUNCPTR * PFNGLUSEPROGRAMOBJECTARBPROC)(GLhandleARB programObj);
typedef void (GLE_FUNCPTR * PFNGLVALIDATEPROGRAMARBPROC)(GLhandleARB programObj);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FARBPROC)(GLint location, GLfloat v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FARBPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FARBPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FARBPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IARBPROC)(GLint location, GLint v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IARBPROC)(GLint location, GLint v0, GLint v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IARBPROC)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IARBPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FVARBPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FVARBPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FVARBPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FVARBPROC)(GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IVARBPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IVARBPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IVARBPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IVARBPROC)(GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2FVARBPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3FVARBPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4FVARBPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTPARAMETERFVARBPROC)(GLhandleARB obj, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTPARAMETERIVARBPROC)(GLhandleARB obj, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETINFOLOGARBPROC)(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
typedef void (GLE_FUNCPTR * PFNGLGETATTACHEDOBJECTSARBPROC)(GLhandleARB containerObj, GLsizei maxCount, GLsizei *count, GLhandleARB *obj);
typedef GLint (GLE_FUNCPTR * PFNGLGETUNIFORMLOCATIONARBPROC)(GLhandleARB programObj, const GLcharARB *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMARBPROC)(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMFVARBPROC)(GLhandleARB programObj, GLint location, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMIVARBPROC)(GLhandleARB programObj, GLint location, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERSOURCEARBPROC)(GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *source);

extern PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
extern PFNGLGETHANDLEARBPROC glGetHandleARB;
extern PFNGLDETACHOBJECTARBPROC glDetachObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
extern PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
extern PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
extern PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
extern PFNGLUNIFORM1FARBPROC glUniform1fARB;
extern PFNGLUNIFORM2FARBPROC glUniform2fARB;
extern PFNGLUNIFORM3FARBPROC glUniform3fARB;
extern PFNGLUNIFORM4FARBPROC glUniform4fARB;
extern PFNGLUNIFORM1IARBPROC glUniform1iARB;
extern PFNGLUNIFORM2IARBPROC glUniform2iARB;
extern PFNGLUNIFORM3IARBPROC glUniform3iARB;
extern PFNGLUNIFORM4IARBPROC glUniform4iARB;
extern PFNGLUNIFORM1FVARBPROC glUniform1fvARB;
extern PFNGLUNIFORM2FVARBPROC glUniform2fvARB;
extern PFNGLUNIFORM3FVARBPROC glUniform3fvARB;
extern PFNGLUNIFORM4FVARBPROC glUniform4fvARB;
extern PFNGLUNIFORM1IVARBPROC glUniform1ivARB;
extern PFNGLUNIFORM2IVARBPROC glUniform2ivARB;
extern PFNGLUNIFORM3IVARBPROC glUniform3ivARB;
extern PFNGLUNIFORM4IVARBPROC glUniform4ivARB;
extern PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB;
extern PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB;
extern PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
extern PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
extern PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
extern PFNGLGETATTACHEDOBJECTSARBPROC glGetAttachedObjectsARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
extern PFNGLGETACTIVEUNIFORMARBPROC glGetActiveUniformARB;
extern PFNGLGETUNIFORMFVARBPROC glGetUniformfvARB;
extern PFNGLGETUNIFORMIVARBPROC glGetUniformivARB;
extern PFNGLGETSHADERSOURCEARBPROC glGetShaderSourceARB;


/******************************
* Extension: GL_ARB_shader_precision
******************************/

/******************************
* Extension: GL_ARB_shader_stencil_export
******************************/

/******************************
* Extension: GL_ARB_shader_subroutine
******************************/

#define GL_UNIFORM_SIZE 0x8A38
#define GL_UNIFORM_NAME_LENGTH 0x8A39
#define GL_ACTIVE_SUBROUTINES 0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS 0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH 0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#define GL_MAX_SUBROUTINES 0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES 0x8E4A
#define GL_COMPATIBLE_SUBROUTINES 0x8E4B


typedef GLint (GLE_FUNCPTR * PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (GLE_FUNCPTR * PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint *values);

extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC __gleGetSubroutineUniformLocation;
#define glGetSubroutineUniformLocation __gleGetSubroutineUniformLocation
extern PFNGLGETSUBROUTINEINDEXPROC __gleGetSubroutineIndex;
#define glGetSubroutineIndex __gleGetSubroutineIndex
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC __gleGetActiveSubroutineUniformiv;
#define glGetActiveSubroutineUniformiv __gleGetActiveSubroutineUniformiv
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC __gleGetActiveSubroutineUniformName;
#define glGetActiveSubroutineUniformName __gleGetActiveSubroutineUniformName
extern PFNGLGETACTIVESUBROUTINENAMEPROC __gleGetActiveSubroutineName;
#define glGetActiveSubroutineName __gleGetActiveSubroutineName
extern PFNGLUNIFORMSUBROUTINESUIVPROC __gleUniformSubroutinesuiv;
#define glUniformSubroutinesuiv __gleUniformSubroutinesuiv
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC __gleGetUniformSubroutineuiv;
#define glGetUniformSubroutineuiv __gleGetUniformSubroutineuiv
extern PFNGLGETPROGRAMSTAGEIVPROC __gleGetProgramStageiv;
#define glGetProgramStageiv __gleGetProgramStageiv


/******************************
* Extension: GL_ARB_shader_texture_lod
******************************/

/******************************
* Extension: GL_ARB_shading_language_100
******************************/

#define GL_SHADING_LANGUAGE_VERSION_ARB 0x8B8C


/******************************
* Extension: GL_ARB_shading_language_include
******************************/

#define GL_SHADER_INCLUDE_ARB 0x8DAE
#define GL_NAMED_STRING_LENGTH_ARB 0x8DE9
#define GL_NAMED_STRING_TYPE_ARB 0x8DEA


typedef void (GLE_FUNCPTR * PFNGLNAMEDSTRINGARBPROC)(GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string);
typedef void (GLE_FUNCPTR * PFNGLDELETENAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLCOMPILESHADERINCLUDEARBPROC)(GLuint shader, GLsizei count, const GLchar* *path, const GLint *length);
typedef GLboolean (GLE_FUNCPTR * PFNGLISNAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDSTRINGIVARBPROC)(GLint namelen, const GLchar *name, GLenum pname, GLint *params);

extern PFNGLNAMEDSTRINGARBPROC glNamedStringARB;
extern PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
extern PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB;
extern PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB;
extern PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB;
extern PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB;


/******************************
* Extension: GL_ARB_shadow
******************************/

#define GL_TEXTURE_COMPARE_MODE_ARB 0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB 0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB 0x884E


/******************************
* Extension: GL_ARB_shadow_ambient
******************************/

#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB 0x80BF


/******************************
* Extension: GL_ARB_sync
******************************/

#define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#define GL_OBJECT_TYPE 0x9112
#define GL_SYNC_CONDITION 0x9113
#define GL_SYNC_STATUS 0x9114
#define GL_SYNC_FLAGS 0x9115
#define GL_SYNC_FENCE 0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#define GL_UNSIGNALED 0x9118
#define GL_SIGNALED 0x9119
#define GL_ALREADY_SIGNALED 0x911A
#define GL_TIMEOUT_EXPIRED 0x911B
#define GL_CONDITION_SATISFIED 0x911C
#define GL_WAIT_FAILED 0x911D
#define GL_TIMEOUT_IGNORED 0xFFFFFFFFFFFFFFFF
#define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001


typedef GLsync (GLE_FUNCPTR * PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
typedef GLboolean (GLE_FUNCPTR * PFNGLISSYNCPROC)(GLsync sync);
typedef void (GLE_FUNCPTR * PFNGLDELETESYNCPROC)(GLsync sync);
typedef GLenum (GLE_FUNCPTR * PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLE_FUNCPTR * PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 *params);
typedef void (GLE_FUNCPTR * PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

extern PFNGLFENCESYNCPROC __gleFenceSync;
#define glFenceSync __gleFenceSync
extern PFNGLISSYNCPROC __gleIsSync;
#define glIsSync __gleIsSync
extern PFNGLDELETESYNCPROC __gleDeleteSync;
#define glDeleteSync __gleDeleteSync
extern PFNGLCLIENTWAITSYNCPROC __gleClientWaitSync;
#define glClientWaitSync __gleClientWaitSync
extern PFNGLWAITSYNCPROC __gleWaitSync;
#define glWaitSync __gleWaitSync
extern PFNGLGETINTEGER64VPROC __gleGetInteger64v;
#define glGetInteger64v __gleGetInteger64v
extern PFNGLGETSYNCIVPROC __gleGetSynciv;
#define glGetSynciv __gleGetSynciv


/******************************
* Extension: GL_ARB_tessellation_shader
******************************/

#define GL_TRIANGLES 0x0004
#define GL_EQUAL 0x0202
#define GL_CW 0x0900
#define GL_CCW 0x0901
#define GL_QUADS 0x0007
#define GL_PATCHES 0x000E
#define GL_PATCH_VERTICES 0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL 0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8E75
#define GL_TESS_GEN_MODE 0x8E76
#define GL_TESS_GEN_SPACING 0x8E77
#define GL_TESS_GEN_VERTEX_ORDER 0x8E78
#define GL_TESS_GEN_POINT_MODE 0x8E79
#define GL_ISOLINES 0x8E7A
#define GL_FRACTIONAL_ODD 0x8E7B
#define GL_FRACTIONAL_EVEN 0x8E7C
#define GL_MAX_PATCH_VERTICES 0x8E7D
#define GL_MAX_TESS_GEN_LEVEL 0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS 0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_TESS_EVALUATION_SHADER 0x8E87
#define GL_TESS_CONTROL_SHADER 0x8E88


typedef void (GLE_FUNCPTR * PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
typedef void (GLE_FUNCPTR * PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat *values);

extern PFNGLPATCHPARAMETERIPROC __glePatchParameteri;
#define glPatchParameteri __glePatchParameteri
extern PFNGLPATCHPARAMETERFVPROC __glePatchParameterfv;
#define glPatchParameterfv __glePatchParameterfv


/******************************
* Extension: GL_ARB_texture_border_clamp
******************************/

#define GL_CLAMP_TO_BORDER_ARB 0x812D


/******************************
* Extension: GL_ARB_texture_buffer_object
******************************/

#define GL_TEXTURE_BUFFER_ARB 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_ARB 0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_ARB 0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB 0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_ARB 0x8C2E


typedef void (GLE_FUNCPTR * PFNGLTEXBUFFERARBPROC)(GLenum target, GLenum internalformat, GLuint buffer);

extern PFNGLTEXBUFFERARBPROC glTexBufferARB;


/******************************
* Extension: GL_ARB_texture_buffer_object_rgb32
******************************/

#define GL_RGB32F 0x8815
#define GL_RGB32UI 0x8D71
#define GL_RGB32I 0x8D83


/******************************
* Extension: GL_ARB_texture_compression
******************************/

#define GL_COMPRESSED_ALPHA_ARB 0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB 0x84EB
#define GL_COMPRESSED_INTENSITY_ARB 0x84EC
#define GL_COMPRESSED_RGB_ARB 0x84ED
#define GL_COMPRESSED_RGBA_ARB 0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB 0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB 0x86A0
#define GL_TEXTURE_COMPRESSED_ARB 0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB 0x86A3


typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)(GLenum target, GLint level, GLvoid *img);

extern PFNGLCOMPRESSEDTEXIMAGE3DARBPROC glCompressedTexImage3DARB;
extern PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
extern PFNGLCOMPRESSEDTEXIMAGE1DARBPROC glCompressedTexImage1DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1DARB;
extern PFNGLGETCOMPRESSEDTEXIMAGEARBPROC glGetCompressedTexImageARB;


/******************************
* Extension: GL_ARB_texture_compression_bptc
******************************/

#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8E8F


/******************************
* Extension: GL_ARB_texture_compression_rgtc
******************************/

#define GL_COMPRESSED_RED_RGTC1 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#define GL_COMPRESSED_RG_RGTC2 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE


/******************************
* Extension: GL_ARB_texture_cube_map
******************************/

#define GL_NORMAL_MAP_ARB 0x8511
#define GL_REFLECTION_MAP_ARB 0x8512
#define GL_TEXTURE_CUBE_MAP_ARB 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB 0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB 0x851C


/******************************
* Extension: GL_ARB_texture_cube_map_array
******************************/

#define GL_TEXTURE_CUBE_MAP_ARRAY_ARB_ARB 0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB_ARB 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB_ARB 0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY_ARB_ARB 0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB_ARB 0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB_ARB 0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB_ARB 0x900F


/******************************
* Extension: GL_ARB_texture_env_add
******************************/

/******************************
* Extension: GL_ARB_texture_env_combine
******************************/

#define GL_COMBINE_ARB 0x8570
#define GL_COMBINE_RGB_ARB 0x8571
#define GL_COMBINE_ALPHA_ARB 0x8572
#define GL_SOURCE0_RGB_ARB 0x8580
#define GL_SOURCE1_RGB_ARB 0x8581
#define GL_SOURCE2_RGB_ARB 0x8582
#define GL_SOURCE0_ALPHA_ARB 0x8588
#define GL_SOURCE1_ALPHA_ARB 0x8589
#define GL_SOURCE2_ALPHA_ARB 0x858A
#define GL_OPERAND0_RGB_ARB 0x8590
#define GL_OPERAND1_RGB_ARB 0x8591
#define GL_OPERAND2_RGB_ARB 0x8592
#define GL_OPERAND0_ALPHA_ARB 0x8598
#define GL_OPERAND1_ALPHA_ARB 0x8599
#define GL_OPERAND2_ALPHA_ARB 0x859A
#define GL_RGB_SCALE_ARB 0x8573
#define GL_ADD_SIGNED_ARB 0x8574
#define GL_INTERPOLATE_ARB 0x8575
#define GL_SUBTRACT_ARB 0x84E7
#define GL_CONSTANT_ARB 0x8576
#define GL_PRIMARY_COLOR_ARB 0x8577
#define GL_PREVIOUS_ARB 0x8578


/******************************
* Extension: GL_ARB_texture_env_crossbar
******************************/

/******************************
* Extension: GL_ARB_texture_env_dot3
******************************/

#define GL_DOT3_RGB_ARB 0x86AE
#define GL_DOT3_RGBA_ARB 0x86AF


/******************************
* Extension: GL_ARB_texture_float
******************************/

#define GL_TEXTURE_RED_TYPE_ARB 0x8C10
#define GL_TEXTURE_GREEN_TYPE_ARB 0x8C11
#define GL_TEXTURE_BLUE_TYPE_ARB 0x8C12
#define GL_TEXTURE_ALPHA_TYPE_ARB 0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB 0x8C14
#define GL_TEXTURE_INTENSITY_TYPE_ARB 0x8C15
#define GL_TEXTURE_DEPTH_TYPE_ARB 0x8C16
#define GL_UNSIGNED_NORMALIZED_ARB 0x8C17
#define GL_RGBA32F_ARB 0x8814
#define GL_RGB32F_ARB 0x8815
#define GL_ALPHA32F_ARB 0x8816
#define GL_INTENSITY32F_ARB 0x8817
#define GL_LUMINANCE32F_ARB 0x8818
#define GL_LUMINANCE_ALPHA32F_ARB 0x8819
#define GL_RGBA16F_ARB 0x881A
#define GL_RGB16F_ARB 0x881B
#define GL_ALPHA16F_ARB 0x881C
#define GL_INTENSITY16F_ARB 0x881D
#define GL_LUMINANCE16F_ARB 0x881E
#define GL_LUMINANCE_ALPHA16F_ARB 0x881F


/******************************
* Extension: GL_ARB_texture_gather
******************************/

#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8E5F


/******************************
* Extension: GL_ARB_texture_mirrored_repeat
******************************/

#define GL_MIRRORED_REPEAT_ARB 0x8370


/******************************
* Extension: GL_ARB_texture_multisample
******************************/

#define GL_SAMPLE_POSITION 0x8E50
#define GL_SAMPLE_MASK 0x8E51
#define GL_SAMPLE_MASK_VALUE 0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS 0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES 0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910F
#define GL_MAX_INTEGER_SAMPLES 0x9110


typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (GLE_FUNCPTR * PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat *val);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKIPROC)(GLuint index, GLbitfield mask);

extern PFNGLTEXIMAGE2DMULTISAMPLEPROC __gleTexImage2DMultisample;
#define glTexImage2DMultisample __gleTexImage2DMultisample
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC __gleTexImage3DMultisample;
#define glTexImage3DMultisample __gleTexImage3DMultisample
extern PFNGLGETMULTISAMPLEFVPROC __gleGetMultisamplefv;
#define glGetMultisamplefv __gleGetMultisamplefv
extern PFNGLSAMPLEMASKIPROC __gleSampleMaski;
#define glSampleMaski __gleSampleMaski


/******************************
* Extension: GL_ARB_texture_non_power_of_two
******************************/

/******************************
* Extension: GL_ARB_texture_query_lod
******************************/

/******************************
* Extension: GL_ARB_texture_rectangle
******************************/

#define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB 0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB 0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB 0x84F8


/******************************
* Extension: GL_ARB_texture_rg
******************************/

#define GL_RG 0x8227
#define GL_RG_INTEGER 0x8228
#define GL_R8 0x8229
#define GL_R16 0x822A
#define GL_RG8 0x822B
#define GL_RG16 0x822C
#define GL_R16F 0x822D
#define GL_R32F 0x822E
#define GL_RG16F 0x822F
#define GL_RG32F 0x8230
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823A
#define GL_RG32I 0x823B
#define GL_RG32UI 0x823C


/******************************
* Extension: GL_ARB_texture_rgb10_a2ui
******************************/

#define GL_RGB10_A2UI 0x906F


/******************************
* Extension: GL_ARB_texture_swizzle
******************************/

#define GL_TEXTURE_SWIZZLE_R 0x8E42
#define GL_TEXTURE_SWIZZLE_G 0x8E43
#define GL_TEXTURE_SWIZZLE_B 0x8E44
#define GL_TEXTURE_SWIZZLE_A 0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA 0x8E46


/******************************
* Extension: GL_ARB_timer_query
******************************/

#define GL_TIME_ELAPSED 0x88BF
#define GL_TIMESTAMP 0x8E28


typedef void (GLE_FUNCPTR * PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 *params);

extern PFNGLQUERYCOUNTERPROC __gleQueryCounter;
#define glQueryCounter __gleQueryCounter
extern PFNGLGETQUERYOBJECTI64VPROC __gleGetQueryObjecti64v;
#define glGetQueryObjecti64v __gleGetQueryObjecti64v
extern PFNGLGETQUERYOBJECTUI64VPROC __gleGetQueryObjectui64v;
#define glGetQueryObjectui64v __gleGetQueryObjectui64v


/******************************
* Extension: GL_ARB_transform_feedback2
******************************/

#define GL_TRANSFORM_FEEDBACK 0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING 0x8E25


typedef void (GLE_FUNCPTR * PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLPAUSETRANSFORMFEEDBACKPROC)();
typedef void (GLE_FUNCPTR * PFNGLRESUMETRANSFORMFEEDBACKPROC)();
typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);

extern PFNGLBINDTRANSFORMFEEDBACKPROC __gleBindTransformFeedback;
#define glBindTransformFeedback __gleBindTransformFeedback
extern PFNGLDELETETRANSFORMFEEDBACKSPROC __gleDeleteTransformFeedbacks;
#define glDeleteTransformFeedbacks __gleDeleteTransformFeedbacks
extern PFNGLGENTRANSFORMFEEDBACKSPROC __gleGenTransformFeedbacks;
#define glGenTransformFeedbacks __gleGenTransformFeedbacks
extern PFNGLISTRANSFORMFEEDBACKPROC __gleIsTransformFeedback;
#define glIsTransformFeedback __gleIsTransformFeedback
extern PFNGLPAUSETRANSFORMFEEDBACKPROC __glePauseTransformFeedback;
#define glPauseTransformFeedback __glePauseTransformFeedback
extern PFNGLRESUMETRANSFORMFEEDBACKPROC __gleResumeTransformFeedback;
#define glResumeTransformFeedback __gleResumeTransformFeedback
extern PFNGLDRAWTRANSFORMFEEDBACKPROC __gleDrawTransformFeedback;
#define glDrawTransformFeedback __gleDrawTransformFeedback


/******************************
* Extension: GL_ARB_transform_feedback3
******************************/

#define GL_MAX_VERTEX_STREAMS 0x8E71
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70


typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);

extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC __gleDrawTransformFeedbackStream;
#define glDrawTransformFeedbackStream __gleDrawTransformFeedbackStream
extern PFNGLBEGINQUERYINDEXEDPROC __gleBeginQueryIndexed;
#define glBeginQueryIndexed __gleBeginQueryIndexed
extern PFNGLENDQUERYINDEXEDPROC __gleEndQueryIndexed;
#define glEndQueryIndexed __gleEndQueryIndexed
extern PFNGLGETQUERYINDEXEDIVPROC __gleGetQueryIndexediv;
#define glGetQueryIndexediv __gleGetQueryIndexediv


/******************************
* Extension: GL_ARB_transpose_matrix
******************************/

#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB 0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB 0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB 0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB 0x84E6


typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXFARBPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXDARBPROC)(const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXFARBPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXDARBPROC)(const GLdouble *m);

extern PFNGLLOADTRANSPOSEMATRIXFARBPROC glLoadTransposeMatrixfARB;
extern PFNGLLOADTRANSPOSEMATRIXDARBPROC glLoadTransposeMatrixdARB;
extern PFNGLMULTTRANSPOSEMATRIXFARBPROC glMultTransposeMatrixfARB;
extern PFNGLMULTTRANSPOSEMATRIXDARBPROC glMultTransposeMatrixdARB;


/******************************
* Extension: GL_ARB_uniform_buffer_object
******************************/

#define GL_UNIFORM_BUFFER 0x8A11
#define GL_UNIFORM_BUFFER_BINDING 0x8A28
#define GL_UNIFORM_BUFFER_START 0x8A29
#define GL_UNIFORM_BUFFER_SIZE 0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS 0x8A36
#define GL_UNIFORM_TYPE 0x8A37
#define GL_UNIFORM_SIZE 0x8A38
#define GL_UNIFORM_NAME_LENGTH 0x8A39
#define GL_UNIFORM_BLOCK_INDEX 0x8A3A
#define GL_UNIFORM_OFFSET 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR 0x8A3E
#define GL_UNIFORM_BLOCK_BINDING 0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX 0xFFFFFFFF
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8A2C
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45


typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar* *uniformNames, GLuint *uniformIndices);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (GLE_FUNCPTR * PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar *uniformBlockName);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

extern PFNGLGETUNIFORMINDICESPROC __gleGetUniformIndices;
#define glGetUniformIndices __gleGetUniformIndices
extern PFNGLGETACTIVEUNIFORMSIVPROC __gleGetActiveUniformsiv;
#define glGetActiveUniformsiv __gleGetActiveUniformsiv
extern PFNGLGETACTIVEUNIFORMNAMEPROC __gleGetActiveUniformName;
#define glGetActiveUniformName __gleGetActiveUniformName
extern PFNGLGETUNIFORMBLOCKINDEXPROC __gleGetUniformBlockIndex;
#define glGetUniformBlockIndex __gleGetUniformBlockIndex
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC __gleGetActiveUniformBlockiv;
#define glGetActiveUniformBlockiv __gleGetActiveUniformBlockiv
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC __gleGetActiveUniformBlockName;
#define glGetActiveUniformBlockName __gleGetActiveUniformBlockName
extern PFNGLUNIFORMBLOCKBINDINGPROC __gleUniformBlockBinding;
#define glUniformBlockBinding __gleUniformBlockBinding


/******************************
* Extension: GL_ARB_vertex_array_bgra
******************************/

#define GL_BGRA 0x80E1


/******************************
* Extension: GL_ARB_vertex_array_object
******************************/

#define GL_VERTEX_ARRAY_BINDING 0x85B5


typedef void (GLE_FUNCPTR * PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (GLE_FUNCPTR * PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void (GLE_FUNCPTR * PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXARRAYPROC)(GLuint array);

extern PFNGLBINDVERTEXARRAYPROC __gleBindVertexArray;
#define glBindVertexArray __gleBindVertexArray
extern PFNGLDELETEVERTEXARRAYSPROC __gleDeleteVertexArrays;
#define glDeleteVertexArrays __gleDeleteVertexArrays
extern PFNGLGENVERTEXARRAYSPROC __gleGenVertexArrays;
#define glGenVertexArrays __gleGenVertexArrays
extern PFNGLISVERTEXARRAYPROC __gleIsVertexArray;
#define glIsVertexArray __gleIsVertexArray


/******************************
* Extension: GL_ARB_vertex_attrib_64bit
******************************/

#define GL_RGB32I 0x8D83
#define GL_DOUBLE_VEC2 0x8FFC
#define GL_DOUBLE_VEC3 0x8FFD
#define GL_DOUBLE_VEC4 0x8FFE
#define GL_DOUBLE_MAT2 0x8F46
#define GL_DOUBLE_MAT3 0x8F47
#define GL_DOUBLE_MAT4 0x8F48
#define GL_DOUBLE_MAT2x3 0x8F49
#define GL_DOUBLE_MAT2x4 0x8F4A
#define GL_DOUBLE_MAT3x2 0x8F4B
#define GL_DOUBLE_MAT3x4 0x8F4C
#define GL_DOUBLE_MAT4x2 0x8F4D
#define GL_DOUBLE_MAT4x3 0x8F4E


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble *params);

extern PFNGLVERTEXATTRIBL1DPROC __gleVertexAttribL1d;
#define glVertexAttribL1d __gleVertexAttribL1d
extern PFNGLVERTEXATTRIBL2DPROC __gleVertexAttribL2d;
#define glVertexAttribL2d __gleVertexAttribL2d
extern PFNGLVERTEXATTRIBL3DPROC __gleVertexAttribL3d;
#define glVertexAttribL3d __gleVertexAttribL3d
extern PFNGLVERTEXATTRIBL4DPROC __gleVertexAttribL4d;
#define glVertexAttribL4d __gleVertexAttribL4d
extern PFNGLVERTEXATTRIBL1DVPROC __gleVertexAttribL1dv;
#define glVertexAttribL1dv __gleVertexAttribL1dv
extern PFNGLVERTEXATTRIBL2DVPROC __gleVertexAttribL2dv;
#define glVertexAttribL2dv __gleVertexAttribL2dv
extern PFNGLVERTEXATTRIBL3DVPROC __gleVertexAttribL3dv;
#define glVertexAttribL3dv __gleVertexAttribL3dv
extern PFNGLVERTEXATTRIBL4DVPROC __gleVertexAttribL4dv;
#define glVertexAttribL4dv __gleVertexAttribL4dv
extern PFNGLVERTEXATTRIBLPOINTERPROC __gleVertexAttribLPointer;
#define glVertexAttribLPointer __gleVertexAttribLPointer
extern PFNGLGETVERTEXATTRIBLDVPROC __gleGetVertexAttribLdv;
#define glGetVertexAttribLdv __gleGetVertexAttribLdv


/******************************
* Extension: GL_ARB_vertex_blend
******************************/

#define GL_MAX_VERTEX_UNITS_ARB 0x86A4
#define GL_ACTIVE_VERTEX_UNITS_ARB 0x86A5
#define GL_WEIGHT_SUM_UNITY_ARB 0x86A6
#define GL_VERTEX_BLEND_ARB 0x86A7
#define GL_CURRENT_WEIGHT_ARB 0x86A8
#define GL_WEIGHT_ARRAY_TYPE_ARB 0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_ARB 0x86AA
#define GL_WEIGHT_ARRAY_SIZE_ARB 0x86AB
#define GL_WEIGHT_ARRAY_POINTER_ARB 0x86AC
#define GL_WEIGHT_ARRAY_ARB 0x86AD
#define GL_MODELVIEW0_ARB 0x1700
#define GL_MODELVIEW1_ARB 0x850A
#define GL_MODELVIEW2_ARB 0x8722
#define GL_MODELVIEW3_ARB 0x8723
#define GL_MODELVIEW4_ARB 0x8724
#define GL_MODELVIEW5_ARB 0x8725
#define GL_MODELVIEW6_ARB 0x8726
#define GL_MODELVIEW7_ARB 0x8727
#define GL_MODELVIEW8_ARB 0x8728
#define GL_MODELVIEW9_ARB 0x8729
#define GL_MODELVIEW10_ARB 0x872A
#define GL_MODELVIEW11_ARB 0x872B
#define GL_MODELVIEW12_ARB 0x872C
#define GL_MODELVIEW13_ARB 0x872D
#define GL_MODELVIEW14_ARB 0x872E
#define GL_MODELVIEW15_ARB 0x872F
#define GL_MODELVIEW16_ARB 0x8730
#define GL_MODELVIEW17_ARB 0x8731
#define GL_MODELVIEW18_ARB 0x8732
#define GL_MODELVIEW19_ARB 0x8733
#define GL_MODELVIEW20_ARB 0x8734
#define GL_MODELVIEW21_ARB 0x8735
#define GL_MODELVIEW22_ARB 0x8736
#define GL_MODELVIEW23_ARB 0x8737
#define GL_MODELVIEW24_ARB 0x8738
#define GL_MODELVIEW25_ARB 0x8739
#define GL_MODELVIEW26_ARB 0x873A
#define GL_MODELVIEW27_ARB 0x873B
#define GL_MODELVIEW28_ARB 0x873C
#define GL_MODELVIEW29_ARB 0x873D
#define GL_MODELVIEW30_ARB 0x873E
#define GL_MODELVIEW31_ARB 0x873F


typedef void (GLE_FUNCPTR * PFNGLWEIGHTBVARBPROC)(GLint size, const GLbyte *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTSVARBPROC)(GLint size, const GLshort *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTIVARBPROC)(GLint size, const GLint *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTFVARBPROC)(GLint size, const GLfloat *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTDVARBPROC)(GLint size, const GLdouble *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTUBVARBPROC)(GLint size, const GLubyte *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTUSVARBPROC)(GLint size, const GLushort *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTUIVARBPROC)(GLint size, const GLuint *weights);
typedef void (GLE_FUNCPTR * PFNGLWEIGHTPOINTERARBPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXBLENDARBPROC)(GLint count);

extern PFNGLWEIGHTBVARBPROC glWeightbvARB;
extern PFNGLWEIGHTSVARBPROC glWeightsvARB;
extern PFNGLWEIGHTIVARBPROC glWeightivARB;
extern PFNGLWEIGHTFVARBPROC glWeightfvARB;
extern PFNGLWEIGHTDVARBPROC glWeightdvARB;
extern PFNGLWEIGHTUBVARBPROC glWeightubvARB;
extern PFNGLWEIGHTUSVARBPROC glWeightusvARB;
extern PFNGLWEIGHTUIVARBPROC glWeightuivARB;
extern PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB;
extern PFNGLVERTEXBLENDARBPROC glVertexBlendARB;


/******************************
* Extension: GL_ARB_vertex_buffer_object
******************************/

#define GL_BUFFER_SIZE_ARB 0x8764
#define GL_BUFFER_USAGE_ARB 0x8765
#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889F
#define GL_READ_ONLY_ARB 0x88B8
#define GL_WRITE_ONLY_ARB 0x88B9
#define GL_READ_WRITE_ARB 0x88BA
#define GL_BUFFER_ACCESS_ARB 0x88BB
#define GL_BUFFER_MAPPED_ARB 0x88BC
#define GL_BUFFER_MAP_POINTER_ARB 0x88BD
#define GL_STREAM_DRAW_ARB 0x88E0
#define GL_STREAM_READ_ARB 0x88E1
#define GL_STREAM_COPY_ARB 0x88E2
#define GL_STATIC_DRAW_ARB 0x88E4
#define GL_STATIC_READ_ARB 0x88E5
#define GL_STATIC_COPY_ARB 0x88E6
#define GL_DYNAMIC_DRAW_ARB 0x88E8
#define GL_DYNAMIC_READ_ARB 0x88E9
#define GL_DYNAMIC_COPY_ARB 0x88EA


typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERARBPROC)(GLenum target, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLDELETEBUFFERSARBPROC)(GLsizei n, const GLuint *buffers);
typedef void (GLE_FUNCPTR * PFNGLGENBUFFERSARBPROC)(GLsizei n, GLuint *buffers);
typedef GLboolean (GLE_FUNCPTR * PFNGLISBUFFERARBPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLBUFFERDATAARBPROC)(GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage);
typedef void (GLE_FUNCPTR * PFNGLBUFFERSUBDATAARBPROC)(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERSUBDATAARBPROC)(GLenum target, GLintptrARB offset, GLsizeiptrARB size, GLvoid *data);
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPBUFFERARBPROC)(GLenum target, GLenum access);
typedef GLboolean (GLE_FUNCPTR * PFNGLUNMAPBUFFERARBPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERIVARBPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPOINTERVARBPROC)(GLenum target, GLenum pname, GLvoid* *params);

extern PFNGLBINDBUFFERARBPROC glBindBufferARB;
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;
extern PFNGLISBUFFERARBPROC glIsBufferARB;
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;
extern PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
extern PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
extern PFNGLMAPBUFFERARBPROC glMapBufferARB;
extern PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
extern PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
extern PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;


/******************************
* Extension: GL_ARB_vertex_program
******************************/

#define GL_COLOR_SUM_ARB 0x8458
#define GL_VERTEX_PROGRAM_ARB 0x8620
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB 0x8625
#define GL_CURRENT_VERTEX_ATTRIB_ARB 0x8626
#define GL_PROGRAM_LENGTH_ARB 0x8627
#define GL_PROGRAM_STRING_ARB 0x8628
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB 0x862E
#define GL_MAX_PROGRAM_MATRICES_ARB 0x862F
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB 0x8640
#define GL_CURRENT_MATRIX_ARB 0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB 0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB 0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB 0x8645
#define GL_PROGRAM_ERROR_POSITION_ARB 0x864B
#define GL_PROGRAM_BINDING_ARB 0x8677
#define GL_MAX_VERTEX_ATTRIBS_ARB 0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB 0x886A
#define GL_PROGRAM_ERROR_STRING_ARB 0x8874
#define GL_PROGRAM_FORMAT_ASCII_ARB 0x8875
#define GL_PROGRAM_FORMAT_ARB 0x8876
#define GL_PROGRAM_INSTRUCTIONS_ARB 0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB 0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB 0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB 0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB 0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB 0x88A7
#define GL_PROGRAM_PARAMETERS_ARB 0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB 0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB 0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB 0x88AB
#define GL_PROGRAM_ATTRIBS_ARB 0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB 0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB 0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB 0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB 0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB 0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB 0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB 0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB 0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB 0x88B6
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB 0x88B7
#define GL_MATRIX0_ARB 0x88C0
#define GL_MATRIX1_ARB 0x88C1
#define GL_MATRIX2_ARB 0x88C2
#define GL_MATRIX3_ARB 0x88C3
#define GL_MATRIX4_ARB 0x88C4
#define GL_MATRIX5_ARB 0x88C5
#define GL_MATRIX6_ARB 0x88C6
#define GL_MATRIX7_ARB 0x88C7
#define GL_MATRIX8_ARB 0x88C8
#define GL_MATRIX9_ARB 0x88C9
#define GL_MATRIX10_ARB 0x88CA
#define GL_MATRIX11_ARB 0x88CB
#define GL_MATRIX12_ARB 0x88CC
#define GL_MATRIX13_ARB 0x88CD
#define GL_MATRIX14_ARB 0x88CE
#define GL_MATRIX15_ARB 0x88CF
#define GL_MATRIX16_ARB 0x88D0
#define GL_MATRIX17_ARB 0x88D1
#define GL_MATRIX18_ARB 0x88D2
#define GL_MATRIX19_ARB 0x88D3
#define GL_MATRIX20_ARB 0x88D4
#define GL_MATRIX21_ARB 0x88D5
#define GL_MATRIX22_ARB 0x88D6
#define GL_MATRIX23_ARB 0x88D7
#define GL_MATRIX24_ARB 0x88D8
#define GL_MATRIX25_ARB 0x88D9
#define GL_MATRIX26_ARB 0x88DA
#define GL_MATRIX27_ARB 0x88DB
#define GL_MATRIX28_ARB 0x88DC
#define GL_MATRIX29_ARB 0x88DD
#define GL_MATRIX30_ARB 0x88DE
#define GL_MATRIX31_ARB 0x88DF


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DARBPROC)(GLuint index, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DVARBPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FARBPROC)(GLuint index, GLfloat x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FVARBPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SARBPROC)(GLuint index, GLshort x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SVARBPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DARBPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DVARBPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FARBPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FVARBPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SARBPROC)(GLuint index, GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SVARBPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DARBPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DVARBPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FARBPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FVARBPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SARBPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SVARBPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NBVARBPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NIVARBPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NSVARBPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBARBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBVARBPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUIVARBPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUSVARBPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4BVARBPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DARBPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DVARBPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FARBPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FVARBPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4IVARBPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SARBPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SVARBPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UBVARBPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UIVARBPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4USVARBPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBPOINTERARBPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLENABLEVERTEXATTRIBARRAYARBPROC)(GLuint index);
typedef void (GLE_FUNCPTR * PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)(GLuint index);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMSTRINGARBPROC)(GLenum target, GLenum format, GLsizei len, const GLvoid *string);
typedef void (GLE_FUNCPTR * PFNGLBINDPROGRAMARBPROC)(GLenum target, GLuint program);
typedef void (GLE_FUNCPTR * PFNGLDELETEPROGRAMSARBPROC)(GLsizei n, const GLuint *programs);
typedef void (GLE_FUNCPTR * PFNGLGENPROGRAMSARBPROC)(GLsizei n, GLuint *programs);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETER4DARBPROC)(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETER4DVARBPROC)(GLenum target, GLuint index, const GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETER4FARBPROC)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETER4FVARBPROC)(GLenum target, GLuint index, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETER4DARBPROC)(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)(GLenum target, GLuint index, const GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETER4FARBPROC)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)(GLenum target, GLuint index, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMENVPARAMETERDVARBPROC)(GLenum target, GLuint index, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMENVPARAMETERFVARBPROC)(GLenum target, GLuint index, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)(GLenum target, GLuint index, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)(GLenum target, GLuint index, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMIVARBPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSTRINGARBPROC)(GLenum target, GLenum pname, GLvoid *string);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBDVARBPROC)(GLuint index, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBFVARBPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIVARBPROC)(GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBPOINTERVARBPROC)(GLuint index, GLenum pname, GLvoid* *pointer);
typedef GLboolean (GLE_FUNCPTR * PFNGLISPROGRAMARBPROC)(GLuint program);

extern PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB;
extern PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB;
extern PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB;
extern PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB;
extern PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB;
extern PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB;
extern PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB;
extern PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB;
extern PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB;
extern PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB;
extern PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB;
extern PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB;
extern PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB;
extern PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB;
extern PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB;
extern PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB;
extern PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB;
extern PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB;
extern PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB;
extern PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB;
extern PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB;
extern PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB;
extern PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB;
extern PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB;
extern PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB;
extern PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB;
extern PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB;
extern PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB;
extern PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB;
extern PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB;
extern PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB;
extern PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB;
extern PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB;
extern PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB;
extern PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB;
extern PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
extern PFNGLPROGRAMSTRINGARBPROC glProgramStringARB;
extern PFNGLBINDPROGRAMARBPROC glBindProgramARB;
extern PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB;
extern PFNGLGENPROGRAMSARBPROC glGenProgramsARB;
extern PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB;
extern PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB;
extern PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB;
extern PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB;
extern PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB;
extern PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB;
extern PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB;
extern PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB;
extern PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB;
extern PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB;
extern PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB;
extern PFNGLGETPROGRAMIVARBPROC glGetProgramivARB;
extern PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB;
extern PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB;
extern PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB;
extern PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB;
extern PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointervARB;
extern PFNGLISPROGRAMARBPROC glIsProgramARB;


/******************************
* Extension: GL_ARB_vertex_shader
******************************/

#define GL_VERTEX_SHADER_ARB 0x8B31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB 0x8B4A
#define GL_MAX_VARYING_FLOATS_ARB 0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB 0x8B4D
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB 0x8B89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB 0x8B8A


typedef void (GLE_FUNCPTR * PFNGLBINDATTRIBLOCATIONARBPROC)(GLhandleARB programObj, GLuint index, const GLcharARB *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEATTRIBARBPROC)(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETATTRIBLOCATIONARBPROC)(GLhandleARB programObj, const GLcharARB *name);

extern PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
extern PFNGLGETACTIVEATTRIBARBPROC glGetActiveAttribARB;
extern PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB;


/******************************
* Extension: GL_ARB_vertex_type_2_10_10_10_rev
******************************/

#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#define GL_INT_2_10_10_10_REV 0x8D9F


typedef void (GLE_FUNCPTR * PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint *coords);
typedef void (GLE_FUNCPTR * PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (GLE_FUNCPTR * PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint *color);
typedef void (GLE_FUNCPTR * PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
typedef void (GLE_FUNCPTR * PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint *color);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint *color);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value);

extern PFNGLVERTEXP2UIPROC __gleVertexP2ui;
#define glVertexP2ui __gleVertexP2ui
extern PFNGLVERTEXP2UIVPROC __gleVertexP2uiv;
#define glVertexP2uiv __gleVertexP2uiv
extern PFNGLVERTEXP3UIPROC __gleVertexP3ui;
#define glVertexP3ui __gleVertexP3ui
extern PFNGLVERTEXP3UIVPROC __gleVertexP3uiv;
#define glVertexP3uiv __gleVertexP3uiv
extern PFNGLVERTEXP4UIPROC __gleVertexP4ui;
#define glVertexP4ui __gleVertexP4ui
extern PFNGLVERTEXP4UIVPROC __gleVertexP4uiv;
#define glVertexP4uiv __gleVertexP4uiv
extern PFNGLTEXCOORDP1UIPROC __gleTexCoordP1ui;
#define glTexCoordP1ui __gleTexCoordP1ui
extern PFNGLTEXCOORDP1UIVPROC __gleTexCoordP1uiv;
#define glTexCoordP1uiv __gleTexCoordP1uiv
extern PFNGLTEXCOORDP2UIPROC __gleTexCoordP2ui;
#define glTexCoordP2ui __gleTexCoordP2ui
extern PFNGLTEXCOORDP2UIVPROC __gleTexCoordP2uiv;
#define glTexCoordP2uiv __gleTexCoordP2uiv
extern PFNGLTEXCOORDP3UIPROC __gleTexCoordP3ui;
#define glTexCoordP3ui __gleTexCoordP3ui
extern PFNGLTEXCOORDP3UIVPROC __gleTexCoordP3uiv;
#define glTexCoordP3uiv __gleTexCoordP3uiv
extern PFNGLTEXCOORDP4UIPROC __gleTexCoordP4ui;
#define glTexCoordP4ui __gleTexCoordP4ui
extern PFNGLTEXCOORDP4UIVPROC __gleTexCoordP4uiv;
#define glTexCoordP4uiv __gleTexCoordP4uiv
extern PFNGLMULTITEXCOORDP1UIPROC __gleMultiTexCoordP1ui;
#define glMultiTexCoordP1ui __gleMultiTexCoordP1ui
extern PFNGLMULTITEXCOORDP1UIVPROC __gleMultiTexCoordP1uiv;
#define glMultiTexCoordP1uiv __gleMultiTexCoordP1uiv
extern PFNGLMULTITEXCOORDP2UIPROC __gleMultiTexCoordP2ui;
#define glMultiTexCoordP2ui __gleMultiTexCoordP2ui
extern PFNGLMULTITEXCOORDP2UIVPROC __gleMultiTexCoordP2uiv;
#define glMultiTexCoordP2uiv __gleMultiTexCoordP2uiv
extern PFNGLMULTITEXCOORDP3UIPROC __gleMultiTexCoordP3ui;
#define glMultiTexCoordP3ui __gleMultiTexCoordP3ui
extern PFNGLMULTITEXCOORDP3UIVPROC __gleMultiTexCoordP3uiv;
#define glMultiTexCoordP3uiv __gleMultiTexCoordP3uiv
extern PFNGLMULTITEXCOORDP4UIPROC __gleMultiTexCoordP4ui;
#define glMultiTexCoordP4ui __gleMultiTexCoordP4ui
extern PFNGLMULTITEXCOORDP4UIVPROC __gleMultiTexCoordP4uiv;
#define glMultiTexCoordP4uiv __gleMultiTexCoordP4uiv
extern PFNGLNORMALP3UIPROC __gleNormalP3ui;
#define glNormalP3ui __gleNormalP3ui
extern PFNGLNORMALP3UIVPROC __gleNormalP3uiv;
#define glNormalP3uiv __gleNormalP3uiv
extern PFNGLCOLORP3UIPROC __gleColorP3ui;
#define glColorP3ui __gleColorP3ui
extern PFNGLCOLORP3UIVPROC __gleColorP3uiv;
#define glColorP3uiv __gleColorP3uiv
extern PFNGLCOLORP4UIPROC __gleColorP4ui;
#define glColorP4ui __gleColorP4ui
extern PFNGLCOLORP4UIVPROC __gleColorP4uiv;
#define glColorP4uiv __gleColorP4uiv
extern PFNGLSECONDARYCOLORP3UIPROC __gleSecondaryColorP3ui;
#define glSecondaryColorP3ui __gleSecondaryColorP3ui
extern PFNGLSECONDARYCOLORP3UIVPROC __gleSecondaryColorP3uiv;
#define glSecondaryColorP3uiv __gleSecondaryColorP3uiv
extern PFNGLVERTEXATTRIBP1UIPROC __gleVertexAttribP1ui;
#define glVertexAttribP1ui __gleVertexAttribP1ui
extern PFNGLVERTEXATTRIBP1UIVPROC __gleVertexAttribP1uiv;
#define glVertexAttribP1uiv __gleVertexAttribP1uiv
extern PFNGLVERTEXATTRIBP2UIPROC __gleVertexAttribP2ui;
#define glVertexAttribP2ui __gleVertexAttribP2ui
extern PFNGLVERTEXATTRIBP2UIVPROC __gleVertexAttribP2uiv;
#define glVertexAttribP2uiv __gleVertexAttribP2uiv
extern PFNGLVERTEXATTRIBP3UIPROC __gleVertexAttribP3ui;
#define glVertexAttribP3ui __gleVertexAttribP3ui
extern PFNGLVERTEXATTRIBP3UIVPROC __gleVertexAttribP3uiv;
#define glVertexAttribP3uiv __gleVertexAttribP3uiv
extern PFNGLVERTEXATTRIBP4UIPROC __gleVertexAttribP4ui;
#define glVertexAttribP4ui __gleVertexAttribP4ui
extern PFNGLVERTEXATTRIBP4UIVPROC __gleVertexAttribP4uiv;
#define glVertexAttribP4uiv __gleVertexAttribP4uiv


/******************************
* Extension: GL_ARB_viewport_array
******************************/

#define GL_DEPTH_RANGE 0x0B70
#define GL_VIEWPORT 0x0BA2
#define GL_SCISSOR_BOX 0x0C10
#define GL_SCISSOR_TEST 0x0C11
#define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#define GL_LAST_VERTEX_CONVENTION 0x8E4E
#define GL_PROVOKING_VERTEX 0x8E4F
#define GL_MAX_VIEWPORTS 0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS 0x825C
#define GL_VIEWPORT_BOUNDS_RANGE 0x825D
#define GL_LAYER_PROVOKING_VERTEX 0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#define GL_UNDEFINED_VERTEX 0x8260


typedef void (GLE_FUNCPTR * PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (GLE_FUNCPTR * PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLclampd *v);
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLclampd n, GLclampd f);
typedef void (GLE_FUNCPTR * PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat *data);
typedef void (GLE_FUNCPTR * PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble *data);

extern PFNGLVIEWPORTARRAYVPROC __gleViewportArrayv;
#define glViewportArrayv __gleViewportArrayv
extern PFNGLVIEWPORTINDEXEDFPROC __gleViewportIndexedf;
#define glViewportIndexedf __gleViewportIndexedf
extern PFNGLVIEWPORTINDEXEDFVPROC __gleViewportIndexedfv;
#define glViewportIndexedfv __gleViewportIndexedfv
extern PFNGLSCISSORARRAYVPROC __gleScissorArrayv;
#define glScissorArrayv __gleScissorArrayv
extern PFNGLSCISSORINDEXEDPROC __gleScissorIndexed;
#define glScissorIndexed __gleScissorIndexed
extern PFNGLSCISSORINDEXEDVPROC __gleScissorIndexedv;
#define glScissorIndexedv __gleScissorIndexedv
extern PFNGLDEPTHRANGEARRAYVPROC __gleDepthRangeArrayv;
#define glDepthRangeArrayv __gleDepthRangeArrayv
extern PFNGLDEPTHRANGEINDEXEDPROC __gleDepthRangeIndexed;
#define glDepthRangeIndexed __gleDepthRangeIndexed
extern PFNGLGETFLOATI_VPROC __gleGetFloati_v;
#define glGetFloati_v __gleGetFloati_v
extern PFNGLGETDOUBLEI_VPROC __gleGetDoublei_v;
#define glGetDoublei_v __gleGetDoublei_v


/******************************
* Extension: GL_ARB_window_pos
******************************/

typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DARBPROC)(GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DVARBPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FARBPROC)(GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FVARBPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IARBPROC)(GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IVARBPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SARBPROC)(GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SVARBPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DARBPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DVARBPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FARBPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FVARBPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IARBPROC)(GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IVARBPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SARBPROC)(GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SVARBPROC)(const GLshort *v);

extern PFNGLWINDOWPOS2DARBPROC glWindowPos2dARB;
extern PFNGLWINDOWPOS2DVARBPROC glWindowPos2dvARB;
extern PFNGLWINDOWPOS2FARBPROC glWindowPos2fARB;
extern PFNGLWINDOWPOS2FVARBPROC glWindowPos2fvARB;
extern PFNGLWINDOWPOS2IARBPROC glWindowPos2iARB;
extern PFNGLWINDOWPOS2IVARBPROC glWindowPos2ivARB;
extern PFNGLWINDOWPOS2SARBPROC glWindowPos2sARB;
extern PFNGLWINDOWPOS2SVARBPROC glWindowPos2svARB;
extern PFNGLWINDOWPOS3DARBPROC glWindowPos3dARB;
extern PFNGLWINDOWPOS3DVARBPROC glWindowPos3dvARB;
extern PFNGLWINDOWPOS3FARBPROC glWindowPos3fARB;
extern PFNGLWINDOWPOS3FVARBPROC glWindowPos3fvARB;
extern PFNGLWINDOWPOS3IARBPROC glWindowPos3iARB;
extern PFNGLWINDOWPOS3IVARBPROC glWindowPos3ivARB;
extern PFNGLWINDOWPOS3SARBPROC glWindowPos3sARB;
extern PFNGLWINDOWPOS3SVARBPROC glWindowPos3svARB;


/******************************
* Extension: GL_ATI_draw_buffers
******************************/

#define GL_MAX_DRAW_BUFFERS_ATI 0x8824
#define GL_DRAW_BUFFER0_ATI 0x8825
#define GL_DRAW_BUFFER1_ATI 0x8826
#define GL_DRAW_BUFFER2_ATI 0x8827
#define GL_DRAW_BUFFER3_ATI 0x8828
#define GL_DRAW_BUFFER4_ATI 0x8829
#define GL_DRAW_BUFFER5_ATI 0x882A
#define GL_DRAW_BUFFER6_ATI 0x882B
#define GL_DRAW_BUFFER7_ATI 0x882C
#define GL_DRAW_BUFFER8_ATI 0x882D
#define GL_DRAW_BUFFER9_ATI 0x882E
#define GL_DRAW_BUFFER10_ATI 0x882F
#define GL_DRAW_BUFFER11_ATI 0x8830
#define GL_DRAW_BUFFER12_ATI 0x8831
#define GL_DRAW_BUFFER13_ATI 0x8832
#define GL_DRAW_BUFFER14_ATI 0x8833
#define GL_DRAW_BUFFER15_ATI 0x8834


typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSATIPROC)(GLsizei n, const GLenum *bufs);

extern PFNGLDRAWBUFFERSATIPROC glDrawBuffersATI;


/******************************
* Extension: GL_ATI_element_array
******************************/

#define GL_ELEMENT_ARRAY_ATI 0x8768
#define GL_ELEMENT_ARRAY_TYPE_ATI 0x8769
#define GL_ELEMENT_ARRAY_POINTER_ATI 0x876A


typedef void (GLE_FUNCPTR * PFNGLELEMENTPOINTERATIPROC)(GLenum type, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTARRAYATIPROC)(GLenum mode, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTARRAYATIPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count);

extern PFNGLELEMENTPOINTERATIPROC glElementPointerATI;
extern PFNGLDRAWELEMENTARRAYATIPROC glDrawElementArrayATI;
extern PFNGLDRAWRANGEELEMENTARRAYATIPROC glDrawRangeElementArrayATI;


/******************************
* Extension: GL_ATI_envmap_bumpmap
******************************/

#define GL_BUMP_ROT_MATRIX_ATI 0x8775
#define GL_BUMP_ROT_MATRIX_SIZE_ATI 0x8776
#define GL_BUMP_NUM_TEX_UNITS_ATI 0x8777
#define GL_BUMP_TEX_UNITS_ATI 0x8778
#define GL_DUDV_ATI 0x8779
#define GL_DU8DV8_ATI 0x877A
#define GL_BUMP_ENVMAP_ATI 0x877B
#define GL_BUMP_TARGET_ATI 0x877C


typedef void (GLE_FUNCPTR * PFNGLTEXBUMPPARAMETERIVATIPROC)(GLenum pname, const GLint *param);
typedef void (GLE_FUNCPTR * PFNGLTEXBUMPPARAMETERFVATIPROC)(GLenum pname, const GLfloat *param);
typedef void (GLE_FUNCPTR * PFNGLGETTEXBUMPPARAMETERIVATIPROC)(GLenum pname, GLint *param);
typedef void (GLE_FUNCPTR * PFNGLGETTEXBUMPPARAMETERFVATIPROC)(GLenum pname, GLfloat *param);

extern PFNGLTEXBUMPPARAMETERIVATIPROC glTexBumpParameterivATI;
extern PFNGLTEXBUMPPARAMETERFVATIPROC glTexBumpParameterfvATI;
extern PFNGLGETTEXBUMPPARAMETERIVATIPROC glGetTexBumpParameterivATI;
extern PFNGLGETTEXBUMPPARAMETERFVATIPROC glGetTexBumpParameterfvATI;


/******************************
* Extension: GL_ATI_fragment_shader
******************************/

#define GL_FRAGMENT_SHADER_ATI 0x8920
#define GL_REG_0_ATI 0x8921
#define GL_REG_1_ATI 0x8922
#define GL_REG_2_ATI 0x8923
#define GL_REG_3_ATI 0x8924
#define GL_REG_4_ATI 0x8925
#define GL_REG_5_ATI 0x8926
#define GL_REG_6_ATI 0x8927
#define GL_REG_7_ATI 0x8928
#define GL_REG_8_ATI 0x8929
#define GL_REG_9_ATI 0x892A
#define GL_REG_10_ATI 0x892B
#define GL_REG_11_ATI 0x892C
#define GL_REG_12_ATI 0x892D
#define GL_REG_13_ATI 0x892E
#define GL_REG_14_ATI 0x892F
#define GL_REG_15_ATI 0x8930
#define GL_REG_16_ATI 0x8931
#define GL_REG_17_ATI 0x8932
#define GL_REG_18_ATI 0x8933
#define GL_REG_19_ATI 0x8934
#define GL_REG_20_ATI 0x8935
#define GL_REG_21_ATI 0x8936
#define GL_REG_22_ATI 0x8937
#define GL_REG_23_ATI 0x8938
#define GL_REG_24_ATI 0x8939
#define GL_REG_25_ATI 0x893A
#define GL_REG_26_ATI 0x893B
#define GL_REG_27_ATI 0x893C
#define GL_REG_28_ATI 0x893D
#define GL_REG_29_ATI 0x893E
#define GL_REG_30_ATI 0x893F
#define GL_REG_31_ATI 0x8940
#define GL_CON_0_ATI 0x8941
#define GL_CON_1_ATI 0x8942
#define GL_CON_2_ATI 0x8943
#define GL_CON_3_ATI 0x8944
#define GL_CON_4_ATI 0x8945
#define GL_CON_5_ATI 0x8946
#define GL_CON_6_ATI 0x8947
#define GL_CON_7_ATI 0x8948
#define GL_CON_8_ATI 0x8949
#define GL_CON_9_ATI 0x894A
#define GL_CON_10_ATI 0x894B
#define GL_CON_11_ATI 0x894C
#define GL_CON_12_ATI 0x894D
#define GL_CON_13_ATI 0x894E
#define GL_CON_14_ATI 0x894F
#define GL_CON_15_ATI 0x8950
#define GL_CON_16_ATI 0x8951
#define GL_CON_17_ATI 0x8952
#define GL_CON_18_ATI 0x8953
#define GL_CON_19_ATI 0x8954
#define GL_CON_20_ATI 0x8955
#define GL_CON_21_ATI 0x8956
#define GL_CON_22_ATI 0x8957
#define GL_CON_23_ATI 0x8958
#define GL_CON_24_ATI 0x8959
#define GL_CON_25_ATI 0x895A
#define GL_CON_26_ATI 0x895B
#define GL_CON_27_ATI 0x895C
#define GL_CON_28_ATI 0x895D
#define GL_CON_29_ATI 0x895E
#define GL_CON_30_ATI 0x895F
#define GL_CON_31_ATI 0x8960
#define GL_MOV_ATI 0x8961
#define GL_ADD_ATI 0x8963
#define GL_MUL_ATI 0x8964
#define GL_SUB_ATI 0x8965
#define GL_DOT3_ATI 0x8966
#define GL_DOT4_ATI 0x8967
#define GL_MAD_ATI 0x8968
#define GL_LERP_ATI 0x8969
#define GL_CND_ATI 0x896A
#define GL_CND0_ATI 0x896B
#define GL_DOT2_ADD_ATI 0x896C
#define GL_SECONDARY_INTERPOLATOR_ATI 0x896D
#define GL_NUM_FRAGMENT_REGISTERS_ATI 0x896E
#define GL_NUM_FRAGMENT_CONSTANTS_ATI 0x896F
#define GL_NUM_PASSES_ATI 0x8970
#define GL_NUM_INSTRUCTIONS_PER_PASS_ATI 0x8971
#define GL_NUM_INSTRUCTIONS_TOTAL_ATI 0x8972
#define GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI 0x8973
#define GL_NUM_LOOPBACK_COMPONENTS_ATI 0x8974
#define GL_COLOR_ALPHA_PAIRING_ATI 0x8975
#define GL_SWIZZLE_STR_ATI 0x8976
#define GL_SWIZZLE_STQ_ATI 0x8977
#define GL_SWIZZLE_STR_DR_ATI 0x8978
#define GL_SWIZZLE_STQ_DQ_ATI 0x8979
#define GL_SWIZZLE_STRQ_ATI 0x897A
#define GL_SWIZZLE_STRQ_DQ_ATI 0x897B
#define GL_RED_BIT_ATI 0x00000001
#define GL_GREEN_BIT_ATI 0x00000002
#define GL_BLUE_BIT_ATI 0x00000004
#define GL_2X_BIT_ATI 0x00000001
#define GL_2X_BIT_ATI 0x00000001
#define GL_4X_BIT_ATI 0x00000002
#define GL_8X_BIT_ATI 0x00000004
#define GL_HALF_BIT_ATI 0x00000008
#define GL_QUARTER_BIT_ATI 0x00000010
#define GL_EIGHTH_BIT_ATI 0x00000020
#define GL_SATURATE_BIT_ATI 0x00000040
#define GL_COMP_BIT_ATI 0x00000002
#define GL_NEGATE_BIT_ATI 0x00000004
#define GL_BIAS_BIT_ATI 0x00000008


typedef GLuint (GLE_FUNCPTR * PFNGLGENFRAGMENTSHADERSATIPROC)(GLuint range);
typedef void (GLE_FUNCPTR * PFNGLBINDFRAGMENTSHADERATIPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETEFRAGMENTSHADERATIPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINFRAGMENTSHADERATIPROC)();
typedef void (GLE_FUNCPTR * PFNGLENDFRAGMENTSHADERATIPROC)();
typedef void (GLE_FUNCPTR * PFNGLPASSTEXCOORDATIPROC)(GLuint dst, GLuint coord, GLenum swizzle);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMAPATIPROC)(GLuint dst, GLuint interp, GLenum swizzle);
typedef void (GLE_FUNCPTR * PFNGLCOLORFRAGMENTOP1ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (GLE_FUNCPTR * PFNGLCOLORFRAGMENTOP2ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (GLE_FUNCPTR * PFNGLCOLORFRAGMENTOP3ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (GLE_FUNCPTR * PFNGLALPHAFRAGMENTOP1ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (GLE_FUNCPTR * PFNGLALPHAFRAGMENTOP2ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (GLE_FUNCPTR * PFNGLALPHAFRAGMENTOP3ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (GLE_FUNCPTR * PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)(GLuint dst, const GLfloat *value);

extern PFNGLGENFRAGMENTSHADERSATIPROC glGenFragmentShadersATI;
extern PFNGLBINDFRAGMENTSHADERATIPROC glBindFragmentShaderATI;
extern PFNGLDELETEFRAGMENTSHADERATIPROC glDeleteFragmentShaderATI;
extern PFNGLBEGINFRAGMENTSHADERATIPROC glBeginFragmentShaderATI;
extern PFNGLENDFRAGMENTSHADERATIPROC glEndFragmentShaderATI;
extern PFNGLPASSTEXCOORDATIPROC glPassTexCoordATI;
extern PFNGLSAMPLEMAPATIPROC glSampleMapATI;
extern PFNGLCOLORFRAGMENTOP1ATIPROC glColorFragmentOp1ATI;
extern PFNGLCOLORFRAGMENTOP2ATIPROC glColorFragmentOp2ATI;
extern PFNGLCOLORFRAGMENTOP3ATIPROC glColorFragmentOp3ATI;
extern PFNGLALPHAFRAGMENTOP1ATIPROC glAlphaFragmentOp1ATI;
extern PFNGLALPHAFRAGMENTOP2ATIPROC glAlphaFragmentOp2ATI;
extern PFNGLALPHAFRAGMENTOP3ATIPROC glAlphaFragmentOp3ATI;
extern PFNGLSETFRAGMENTSHADERCONSTANTATIPROC glSetFragmentShaderConstantATI;


/******************************
* Extension: GL_ATI_map_object_buffer
******************************/

typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLUNMAPOBJECTBUFFERATIPROC)(GLuint buffer);

extern PFNGLMAPOBJECTBUFFERATIPROC glMapObjectBufferATI;
extern PFNGLUNMAPOBJECTBUFFERATIPROC glUnmapObjectBufferATI;


/******************************
* Extension: GL_ATI_meminfo
******************************/

#define GL_VBO_FREE_MEMORY_ATI 0x87FB
#define GL_TEXTURE_FREE_MEMORY_ATI 0x87FC
#define GL_RENDERBUFFER_FREE_MEMORY_ATI 0x87FD


/******************************
* Extension: GL_ATI_pixel_format_float
******************************/

#define GL_TYPE_RGBA_FLOAT_ATI 0x8820
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI 0x8835


/******************************
* Extension: GL_ATI_pn_triangles
******************************/

#define GL_PN_TRIANGLES_ATI 0x87F0
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI 0x87F1
#define GL_PN_TRIANGLES_POINT_MODE_ATI 0x87F2
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI 0x87F3
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI 0x87F4
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI 0x87F5
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI 0x87F6
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI 0x87F7
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI 0x87F8


typedef void (GLE_FUNCPTR * PFNGLPNTRIANGLESIATIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPNTRIANGLESFATIPROC)(GLenum pname, GLfloat param);

extern PFNGLPNTRIANGLESIATIPROC glPNTrianglesiATI;
extern PFNGLPNTRIANGLESFATIPROC glPNTrianglesfATI;


/******************************
* Extension: GL_ATI_separate_stencil
******************************/

#define GL_STENCIL_BACK_FUNC_ATI 0x8800
#define GL_STENCIL_BACK_FAIL_ATI 0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI 0x8803


typedef void (GLE_FUNCPTR * PFNGLSTENCILOPSEPARATEATIPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCSEPARATEATIPROC)(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);

extern PFNGLSTENCILOPSEPARATEATIPROC glStencilOpSeparateATI;
extern PFNGLSTENCILFUNCSEPARATEATIPROC glStencilFuncSeparateATI;


/******************************
* Extension: GL_ATI_text_fragment_shader
******************************/

#define GL_TEXT_FRAGMENT_SHADER_ATI 0x8200


/******************************
* Extension: GL_ATI_texture_env_combine3
******************************/

#define GL_MODULATE_ADD_ATI 0x8744
#define GL_MODULATE_SIGNED_ADD_ATI 0x8745
#define GL_MODULATE_SUBTRACT_ATI 0x8746


/******************************
* Extension: GL_ATI_texture_float
******************************/

#define GL_RGBA_FLOAT32_ATI 0x8814
#define GL_RGB_FLOAT32_ATI 0x8815
#define GL_ALPHA_FLOAT32_ATI 0x8816
#define GL_INTENSITY_FLOAT32_ATI 0x8817
#define GL_LUMINANCE_FLOAT32_ATI 0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_ATI 0x8819
#define GL_RGBA_FLOAT16_ATI 0x881A
#define GL_RGB_FLOAT16_ATI 0x881B
#define GL_ALPHA_FLOAT16_ATI 0x881C
#define GL_INTENSITY_FLOAT16_ATI 0x881D
#define GL_LUMINANCE_FLOAT16_ATI 0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_ATI 0x881F


/******************************
* Extension: GL_ATI_texture_mirror_once
******************************/

#define GL_MIRROR_CLAMP_ATI 0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_ATI 0x8743


/******************************
* Extension: GL_ATI_vertex_array_object
******************************/

#define GL_STATIC_ATI 0x8760
#define GL_DYNAMIC_ATI 0x8761
#define GL_PRESERVE_ATI 0x8762
#define GL_DISCARD_ATI 0x8763
#define GL_OBJECT_BUFFER_SIZE_ATI 0x8764
#define GL_OBJECT_BUFFER_USAGE_ATI 0x8765
#define GL_ARRAY_OBJECT_BUFFER_ATI 0x8766
#define GL_ARRAY_OBJECT_OFFSET_ATI 0x8767


typedef GLuint (GLE_FUNCPTR * PFNGLNEWOBJECTBUFFERATIPROC)(GLsizei size, const GLvoid *pointer, GLenum usage);
typedef GLboolean (GLE_FUNCPTR * PFNGLISOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLUPDATEOBJECTBUFFERATIPROC)(GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTBUFFERFVATIPROC)(GLuint buffer, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTBUFFERIVATIPROC)(GLuint buffer, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFREEOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLARRAYOBJECTATIPROC)(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (GLE_FUNCPTR * PFNGLGETARRAYOBJECTFVATIPROC)(GLenum array, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETARRAYOBJECTIVATIPROC)(GLenum array, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLVARIANTARRAYOBJECTATIPROC)(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTARRAYOBJECTFVATIPROC)(GLuint id, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTARRAYOBJECTIVATIPROC)(GLuint id, GLenum pname, GLint *params);

extern PFNGLNEWOBJECTBUFFERATIPROC glNewObjectBufferATI;
extern PFNGLISOBJECTBUFFERATIPROC glIsObjectBufferATI;
extern PFNGLUPDATEOBJECTBUFFERATIPROC glUpdateObjectBufferATI;
extern PFNGLGETOBJECTBUFFERFVATIPROC glGetObjectBufferfvATI;
extern PFNGLGETOBJECTBUFFERIVATIPROC glGetObjectBufferivATI;
extern PFNGLFREEOBJECTBUFFERATIPROC glFreeObjectBufferATI;
extern PFNGLARRAYOBJECTATIPROC glArrayObjectATI;
extern PFNGLGETARRAYOBJECTFVATIPROC glGetArrayObjectfvATI;
extern PFNGLGETARRAYOBJECTIVATIPROC glGetArrayObjectivATI;
extern PFNGLVARIANTARRAYOBJECTATIPROC glVariantArrayObjectATI;
extern PFNGLGETVARIANTARRAYOBJECTFVATIPROC glGetVariantArrayObjectfvATI;
extern PFNGLGETVARIANTARRAYOBJECTIVATIPROC glGetVariantArrayObjectivATI;


/******************************
* Extension: GL_ATI_vertex_attrib_array_object
******************************/

typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)(GLuint index, GLenum pname, GLint *params);

extern PFNGLVERTEXATTRIBARRAYOBJECTATIPROC glVertexAttribArrayObjectATI;
extern PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC glGetVertexAttribArrayObjectfvATI;
extern PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC glGetVertexAttribArrayObjectivATI;


/******************************
* Extension: GL_ATI_vertex_streams
******************************/

#define GL_MAX_VERTEX_STREAMS_ATI 0x876B
#define GL_VERTEX_STREAM0_ATI 0x876C
#define GL_VERTEX_STREAM1_ATI 0x876D
#define GL_VERTEX_STREAM2_ATI 0x876E
#define GL_VERTEX_STREAM3_ATI 0x876F
#define GL_VERTEX_STREAM4_ATI 0x8770
#define GL_VERTEX_STREAM5_ATI 0x8771
#define GL_VERTEX_STREAM6_ATI 0x8772
#define GL_VERTEX_STREAM7_ATI 0x8773
#define GL_VERTEX_SOURCE_ATI 0x8774


typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1SATIPROC)(GLenum stream, GLshort x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1SVATIPROC)(GLenum stream, const GLshort *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1IATIPROC)(GLenum stream, GLint x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1IVATIPROC)(GLenum stream, const GLint *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1FATIPROC)(GLenum stream, GLfloat x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1FVATIPROC)(GLenum stream, const GLfloat *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1DATIPROC)(GLenum stream, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM1DVATIPROC)(GLenum stream, const GLdouble *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2SATIPROC)(GLenum stream, GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2SVATIPROC)(GLenum stream, const GLshort *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2IATIPROC)(GLenum stream, GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2IVATIPROC)(GLenum stream, const GLint *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2FATIPROC)(GLenum stream, GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2FVATIPROC)(GLenum stream, const GLfloat *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2DATIPROC)(GLenum stream, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM2DVATIPROC)(GLenum stream, const GLdouble *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3SATIPROC)(GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3SVATIPROC)(GLenum stream, const GLshort *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3IATIPROC)(GLenum stream, GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3IVATIPROC)(GLenum stream, const GLint *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3FATIPROC)(GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3FVATIPROC)(GLenum stream, const GLfloat *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3DATIPROC)(GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM3DVATIPROC)(GLenum stream, const GLdouble *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4SATIPROC)(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4SVATIPROC)(GLenum stream, const GLshort *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4IATIPROC)(GLenum stream, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4IVATIPROC)(GLenum stream, const GLint *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4FATIPROC)(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4FVATIPROC)(GLenum stream, const GLfloat *coords);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4DATIPROC)(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXSTREAM4DVATIPROC)(GLenum stream, const GLdouble *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3BATIPROC)(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3BVATIPROC)(GLenum stream, const GLbyte *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3SATIPROC)(GLenum stream, GLshort nx, GLshort ny, GLshort nz);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3SVATIPROC)(GLenum stream, const GLshort *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3IATIPROC)(GLenum stream, GLint nx, GLint ny, GLint nz);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3IVATIPROC)(GLenum stream, const GLint *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3FATIPROC)(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3FVATIPROC)(GLenum stream, const GLfloat *coords);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3DATIPROC)(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz);
typedef void (GLE_FUNCPTR * PFNGLNORMALSTREAM3DVATIPROC)(GLenum stream, const GLdouble *coords);
typedef void (GLE_FUNCPTR * PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC)(GLenum stream);
typedef void (GLE_FUNCPTR * PFNGLVERTEXBLENDENVIATIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLVERTEXBLENDENVFATIPROC)(GLenum pname, GLfloat param);

extern PFNGLVERTEXSTREAM1SATIPROC glVertexStream1sATI;
extern PFNGLVERTEXSTREAM1SVATIPROC glVertexStream1svATI;
extern PFNGLVERTEXSTREAM1IATIPROC glVertexStream1iATI;
extern PFNGLVERTEXSTREAM1IVATIPROC glVertexStream1ivATI;
extern PFNGLVERTEXSTREAM1FATIPROC glVertexStream1fATI;
extern PFNGLVERTEXSTREAM1FVATIPROC glVertexStream1fvATI;
extern PFNGLVERTEXSTREAM1DATIPROC glVertexStream1dATI;
extern PFNGLVERTEXSTREAM1DVATIPROC glVertexStream1dvATI;
extern PFNGLVERTEXSTREAM2SATIPROC glVertexStream2sATI;
extern PFNGLVERTEXSTREAM2SVATIPROC glVertexStream2svATI;
extern PFNGLVERTEXSTREAM2IATIPROC glVertexStream2iATI;
extern PFNGLVERTEXSTREAM2IVATIPROC glVertexStream2ivATI;
extern PFNGLVERTEXSTREAM2FATIPROC glVertexStream2fATI;
extern PFNGLVERTEXSTREAM2FVATIPROC glVertexStream2fvATI;
extern PFNGLVERTEXSTREAM2DATIPROC glVertexStream2dATI;
extern PFNGLVERTEXSTREAM2DVATIPROC glVertexStream2dvATI;
extern PFNGLVERTEXSTREAM3SATIPROC glVertexStream3sATI;
extern PFNGLVERTEXSTREAM3SVATIPROC glVertexStream3svATI;
extern PFNGLVERTEXSTREAM3IATIPROC glVertexStream3iATI;
extern PFNGLVERTEXSTREAM3IVATIPROC glVertexStream3ivATI;
extern PFNGLVERTEXSTREAM3FATIPROC glVertexStream3fATI;
extern PFNGLVERTEXSTREAM3FVATIPROC glVertexStream3fvATI;
extern PFNGLVERTEXSTREAM3DATIPROC glVertexStream3dATI;
extern PFNGLVERTEXSTREAM3DVATIPROC glVertexStream3dvATI;
extern PFNGLVERTEXSTREAM4SATIPROC glVertexStream4sATI;
extern PFNGLVERTEXSTREAM4SVATIPROC glVertexStream4svATI;
extern PFNGLVERTEXSTREAM4IATIPROC glVertexStream4iATI;
extern PFNGLVERTEXSTREAM4IVATIPROC glVertexStream4ivATI;
extern PFNGLVERTEXSTREAM4FATIPROC glVertexStream4fATI;
extern PFNGLVERTEXSTREAM4FVATIPROC glVertexStream4fvATI;
extern PFNGLVERTEXSTREAM4DATIPROC glVertexStream4dATI;
extern PFNGLVERTEXSTREAM4DVATIPROC glVertexStream4dvATI;
extern PFNGLNORMALSTREAM3BATIPROC glNormalStream3bATI;
extern PFNGLNORMALSTREAM3BVATIPROC glNormalStream3bvATI;
extern PFNGLNORMALSTREAM3SATIPROC glNormalStream3sATI;
extern PFNGLNORMALSTREAM3SVATIPROC glNormalStream3svATI;
extern PFNGLNORMALSTREAM3IATIPROC glNormalStream3iATI;
extern PFNGLNORMALSTREAM3IVATIPROC glNormalStream3ivATI;
extern PFNGLNORMALSTREAM3FATIPROC glNormalStream3fATI;
extern PFNGLNORMALSTREAM3FVATIPROC glNormalStream3fvATI;
extern PFNGLNORMALSTREAM3DATIPROC glNormalStream3dATI;
extern PFNGLNORMALSTREAM3DVATIPROC glNormalStream3dvATI;
extern PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC glClientActiveVertexStreamATI;
extern PFNGLVERTEXBLENDENVIATIPROC glVertexBlendEnviATI;
extern PFNGLVERTEXBLENDENVFATIPROC glVertexBlendEnvfATI;


/******************************
* Extension: GL_EXT_422_pixels
******************************/

#define GL_422_EXT 0x80CC
#define GL_422_REV_EXT 0x80CD
#define GL_422_AVERAGE_EXT 0x80CE
#define GL_422_REV_AVERAGE_EXT 0x80CF


/******************************
* Extension: GL_EXT_abgr
******************************/

#define GL_ABGR_EXT 0x8000


/******************************
* Extension: GL_EXT_bgra
******************************/

#define GL_BGR_EXT 0x80E0
#define GL_BGRA_EXT 0x80E1


/******************************
* Extension: GL_EXT_bindable_uniform
******************************/

#define GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT 0x8DE2
#define GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT 0x8DE3
#define GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT 0x8DE4
#define GL_MAX_BINDABLE_UNIFORM_SIZE_EXT 0x8DED
#define GL_UNIFORM_BUFFER_EXT 0x8DEE
#define GL_UNIFORM_BUFFER_BINDING_EXT 0x8DEF


typedef void (GLE_FUNCPTR * PFNGLUNIFORMBUFFEREXTPROC)(GLuint program, GLint location, GLuint buffer);
typedef GLint (GLE_FUNCPTR * PFNGLGETUNIFORMBUFFERSIZEEXTPROC)(GLuint program, GLint location);
typedef GLintptr (GLE_FUNCPTR * PFNGLGETUNIFORMOFFSETEXTPROC)(GLuint program, GLint location);

extern PFNGLUNIFORMBUFFEREXTPROC glUniformBufferEXT;
extern PFNGLGETUNIFORMBUFFERSIZEEXTPROC glGetUniformBufferSizeEXT;
extern PFNGLGETUNIFORMOFFSETEXTPROC glGetUniformOffsetEXT;


/******************************
* Extension: GL_EXT_blend_color
******************************/

#define GL_CONSTANT_COLOR_EXT 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT 0x8002
#define GL_CONSTANT_ALPHA_EXT 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT 0x8004
#define GL_BLEND_COLOR_EXT 0x8005


typedef void (GLE_FUNCPTR * PFNGLBLENDCOLOREXTPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

extern PFNGLBLENDCOLOREXTPROC glBlendColorEXT;


/******************************
* Extension: GL_EXT_blend_equation_separate
******************************/

#define GL_BLEND_EQUATION_RGB_EXT 0x8009
#define GL_BLEND_EQUATION_ALPHA_EXT 0x883D


typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEEXTPROC)(GLenum modeRGB, GLenum modeAlpha);

extern PFNGLBLENDEQUATIONSEPARATEEXTPROC glBlendEquationSeparateEXT;


/******************************
* Extension: GL_EXT_blend_func_separate
******************************/

#define GL_BLEND_DST_RGB_EXT 0x80C8
#define GL_BLEND_SRC_RGB_EXT 0x80C9
#define GL_BLEND_DST_ALPHA_EXT 0x80CA
#define GL_BLEND_SRC_ALPHA_EXT 0x80CB


typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEEXTPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

extern PFNGLBLENDFUNCSEPARATEEXTPROC glBlendFuncSeparateEXT;


/******************************
* Extension: GL_EXT_blend_logic_op
******************************/

/******************************
* Extension: GL_EXT_blend_minmax
******************************/

#define GL_FUNC_ADD_EXT 0x8006
#define GL_MIN_EXT 0x8007
#define GL_MAX_EXT 0x8008
#define GL_BLEND_EQUATION_EXT 0x8009


typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONEXTPROC)(GLenum mode);

extern PFNGLBLENDEQUATIONEXTPROC glBlendEquationEXT;


/******************************
* Extension: GL_EXT_blend_subtract
******************************/

#define GL_FUNC_SUBTRACT_EXT 0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT 0x800B


/******************************
* Extension: GL_EXT_clip_volume_hint
******************************/

#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT 0x80F0


/******************************
* Extension: GL_EXT_cmyka
******************************/

#define GL_CMYK_EXT 0x800C
#define GL_CMYKA_EXT 0x800D
#define GL_PACK_CMYK_HINT_EXT 0x800E
#define GL_UNPACK_CMYK_HINT_EXT 0x800F


/******************************
* Extension: GL_EXT_color_subtable
******************************/

typedef void (GLE_FUNCPTR * PFNGLCOLORSUBTABLEEXTPROC)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORSUBTABLEEXTPROC)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);

extern PFNGLCOLORSUBTABLEEXTPROC glColorSubTableEXT;
extern PFNGLCOPYCOLORSUBTABLEEXTPROC glCopyColorSubTableEXT;


/******************************
* Extension: GL_EXT_compiled_vertex_array
******************************/

#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT 0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT 0x81A9


typedef void (GLE_FUNCPTR * PFNGLLOCKARRAYSEXTPROC)(GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLUNLOCKARRAYSEXTPROC)();

extern PFNGLLOCKARRAYSEXTPROC glLockArraysEXT;
extern PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT;


/******************************
* Extension: GL_EXT_convolution
******************************/

#define GL_CONVOLUTION_1D_EXT 0x8010
#define GL_CONVOLUTION_2D_EXT 0x8011
#define GL_SEPARABLE_2D_EXT 0x8012
#define GL_CONVOLUTION_BORDER_MODE_EXT 0x8013
#define GL_CONVOLUTION_FILTER_SCALE_EXT 0x8014
#define GL_CONVOLUTION_FILTER_BIAS_EXT 0x8015
#define GL_REDUCE_EXT 0x8016
#define GL_CONVOLUTION_FORMAT_EXT 0x8017
#define GL_CONVOLUTION_WIDTH_EXT 0x8018
#define GL_CONVOLUTION_HEIGHT_EXT 0x8019
#define GL_MAX_CONVOLUTION_WIDTH_EXT 0x801A
#define GL_MAX_CONVOLUTION_HEIGHT_EXT 0x801B
#define GL_POST_CONVOLUTION_RED_SCALE_EXT 0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE_EXT 0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE_EXT 0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 0x801F
#define GL_POST_CONVOLUTION_RED_BIAS_EXT 0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS_EXT 0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS_EXT 0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS_EXT 0x8023


typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER1DEXTPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER2DEXTPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFEXTPROC)(GLenum target, GLenum pname, GLfloat params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFVEXTPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIEXTPROC)(GLenum target, GLenum pname, GLint params);
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIVEXTPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONFILTEREXTPROC)(GLenum target, GLenum format, GLenum type, GLvoid *image);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETSEPARABLEFILTEREXTPROC)(GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
typedef void (GLE_FUNCPTR * PFNGLSEPARABLEFILTER2DEXTPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);

extern PFNGLCONVOLUTIONFILTER1DEXTPROC glConvolutionFilter1DEXT;
extern PFNGLCONVOLUTIONFILTER2DEXTPROC glConvolutionFilter2DEXT;
extern PFNGLCONVOLUTIONPARAMETERFEXTPROC glConvolutionParameterfEXT;
extern PFNGLCONVOLUTIONPARAMETERFVEXTPROC glConvolutionParameterfvEXT;
extern PFNGLCONVOLUTIONPARAMETERIEXTPROC glConvolutionParameteriEXT;
extern PFNGLCONVOLUTIONPARAMETERIVEXTPROC glConvolutionParameterivEXT;
extern PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC glCopyConvolutionFilter1DEXT;
extern PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC glCopyConvolutionFilter2DEXT;
extern PFNGLGETCONVOLUTIONFILTEREXTPROC glGetConvolutionFilterEXT;
extern PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC glGetConvolutionParameterfvEXT;
extern PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC glGetConvolutionParameterivEXT;
extern PFNGLGETSEPARABLEFILTEREXTPROC glGetSeparableFilterEXT;
extern PFNGLSEPARABLEFILTER2DEXTPROC glSeparableFilter2DEXT;


/******************************
* Extension: GL_EXT_coordinate_frame
******************************/

#define GL_TANGENT_ARRAY_EXT 0x8439
#define GL_BINORMAL_ARRAY_EXT 0x843A
#define GL_CURRENT_TANGENT_EXT 0x843B
#define GL_CURRENT_BINORMAL_EXT 0x843C
#define GL_TANGENT_ARRAY_TYPE_EXT 0x843E
#define GL_TANGENT_ARRAY_STRIDE_EXT 0x843F
#define GL_BINORMAL_ARRAY_TYPE_EXT 0x8440
#define GL_BINORMAL_ARRAY_STRIDE_EXT 0x8441
#define GL_TANGENT_ARRAY_POINTER_EXT 0x8442
#define GL_BINORMAL_ARRAY_POINTER_EXT 0x8443
#define GL_MAP1_TANGENT_EXT 0x8444
#define GL_MAP2_TANGENT_EXT 0x8445
#define GL_MAP1_BINORMAL_EXT 0x8446
#define GL_MAP2_BINORMAL_EXT 0x8447


typedef void (GLE_FUNCPTR * PFNGLTANGENT3BEXTPROC)(GLbyte tx, GLbyte ty, GLbyte tz);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3BVEXTPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3DEXTPROC)(GLdouble tx, GLdouble ty, GLdouble tz);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3DVEXTPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3FEXTPROC)(GLfloat tx, GLfloat ty, GLfloat tz);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3FVEXTPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3IEXTPROC)(GLint tx, GLint ty, GLint tz);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3IVEXTPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3SEXTPROC)(GLshort tx, GLshort ty, GLshort tz);
typedef void (GLE_FUNCPTR * PFNGLTANGENT3SVEXTPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3BEXTPROC)(GLbyte bx, GLbyte by, GLbyte bz);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3BVEXTPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3DEXTPROC)(GLdouble bx, GLdouble by, GLdouble bz);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3DVEXTPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3FEXTPROC)(GLfloat bx, GLfloat by, GLfloat bz);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3FVEXTPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3IEXTPROC)(GLint bx, GLint by, GLint bz);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3IVEXTPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3SEXTPROC)(GLshort bx, GLshort by, GLshort bz);
typedef void (GLE_FUNCPTR * PFNGLBINORMAL3SVEXTPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLTANGENTPOINTEREXTPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLBINORMALPOINTEREXTPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);

extern PFNGLTANGENT3BEXTPROC glTangent3bEXT;
extern PFNGLTANGENT3BVEXTPROC glTangent3bvEXT;
extern PFNGLTANGENT3DEXTPROC glTangent3dEXT;
extern PFNGLTANGENT3DVEXTPROC glTangent3dvEXT;
extern PFNGLTANGENT3FEXTPROC glTangent3fEXT;
extern PFNGLTANGENT3FVEXTPROC glTangent3fvEXT;
extern PFNGLTANGENT3IEXTPROC glTangent3iEXT;
extern PFNGLTANGENT3IVEXTPROC glTangent3ivEXT;
extern PFNGLTANGENT3SEXTPROC glTangent3sEXT;
extern PFNGLTANGENT3SVEXTPROC glTangent3svEXT;
extern PFNGLBINORMAL3BEXTPROC glBinormal3bEXT;
extern PFNGLBINORMAL3BVEXTPROC glBinormal3bvEXT;
extern PFNGLBINORMAL3DEXTPROC glBinormal3dEXT;
extern PFNGLBINORMAL3DVEXTPROC glBinormal3dvEXT;
extern PFNGLBINORMAL3FEXTPROC glBinormal3fEXT;
extern PFNGLBINORMAL3FVEXTPROC glBinormal3fvEXT;
extern PFNGLBINORMAL3IEXTPROC glBinormal3iEXT;
extern PFNGLBINORMAL3IVEXTPROC glBinormal3ivEXT;
extern PFNGLBINORMAL3SEXTPROC glBinormal3sEXT;
extern PFNGLBINORMAL3SVEXTPROC glBinormal3svEXT;
extern PFNGLTANGENTPOINTEREXTPROC glTangentPointerEXT;
extern PFNGLBINORMALPOINTEREXTPROC glBinormalPointerEXT;


/******************************
* Extension: GL_EXT_copy_texture
******************************/

typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE1DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE2DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE1DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE2DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE3DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

extern PFNGLCOPYTEXIMAGE1DEXTPROC glCopyTexImage1DEXT;
extern PFNGLCOPYTEXIMAGE2DEXTPROC glCopyTexImage2DEXT;
extern PFNGLCOPYTEXSUBIMAGE1DEXTPROC glCopyTexSubImage1DEXT;
extern PFNGLCOPYTEXSUBIMAGE2DEXTPROC glCopyTexSubImage2DEXT;
extern PFNGLCOPYTEXSUBIMAGE3DEXTPROC glCopyTexSubImage3DEXT;


/******************************
* Extension: GL_EXT_cull_vertex
******************************/

#define GL_CULL_VERTEX_EXT 0x81AA
#define GL_CULL_VERTEX_EYE_POSITION_EXT 0x81AB
#define GL_CULL_VERTEX_OBJECT_POSITION_EXT 0x81AC


typedef void (GLE_FUNCPTR * PFNGLCULLPARAMETERDVEXTPROC)(GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLCULLPARAMETERFVEXTPROC)(GLenum pname, GLfloat *params);

extern PFNGLCULLPARAMETERDVEXTPROC glCullParameterdvEXT;
extern PFNGLCULLPARAMETERFVEXTPROC glCullParameterfvEXT;


/******************************
* Extension: GL_EXT_depth_bounds_test
******************************/

#define GL_DEPTH_BOUNDS_TEST_EXT 0x8890
#define GL_DEPTH_BOUNDS_EXT 0x8891


typedef void (GLE_FUNCPTR * PFNGLDEPTHBOUNDSEXTPROC)(GLclampd zmin, GLclampd zmax);

extern PFNGLDEPTHBOUNDSEXTPROC glDepthBoundsEXT;


/******************************
* Extension: GL_EXT_direct_state_access
******************************/

#define GL_PROGRAM_MATRIX_EXT 0x8E2D
#define GL_TRANSPOSE_PROGRAM_MATRIX_EXT 0x8E2E
#define GL_PROGRAM_MATRIX_STACK_DEPTH_EXT 0x8E2F


typedef void (GLE_FUNCPTR * PFNGLCLIENTATTRIBDEFAULTEXTPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLMATRIXLOADFEXTPROC)(GLenum mode, const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXLOADDEXTPROC)(GLenum mode, const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXMULTFEXTPROC)(GLenum mode, const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXMULTDEXTPROC)(GLenum mode, const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXLOADIDENTITYEXTPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLMATRIXROTATEFEXTPROC)(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXROTATEDEXTPROC)(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXSCALEFEXTPROC)(GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXSCALEDEXTPROC)(GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXTRANSLATEFEXTPROC)(GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXTRANSLATEDEXTPROC)(GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLMATRIXFRUSTUMEXTPROC)(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLMATRIXORTHOEXTPROC)(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLMATRIXPOPEXTPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLMATRIXPUSHEXTPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLMATRIXLOADTRANSPOSEFEXTPROC)(GLenum mode, const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXLOADTRANSPOSEDEXTPROC)(GLenum mode, const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXMULTTRANSPOSEFEXTPROC)(GLenum mode, const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMATRIXMULTTRANSPOSEDEXTPROC)(GLenum mode, const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERFEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERFVEXTPROC)(GLuint texture, GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERIEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXTURESUBIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXTURESUBIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXTUREIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXTUREIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTUREIMAGEEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTUREPARAMETERFVEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTUREPARAMETERIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREIMAGE3DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXTURESUBIMAGE3DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERFEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERFVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERIEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXSUBIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXSUBIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLCOPYMULTITEXIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYMULTITEXIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXIMAGEEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXPARAMETERFVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXPARAMETERIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXIMAGE3DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXSUBIMAGE3DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLBINDMULTITEXTUREEXTPROC)(GLenum texunit, GLenum target, GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)(GLenum array, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)(GLenum array, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORDPOINTEREXTPROC)(GLenum texunit, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXENVFEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXENVFVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXENVIEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXENVIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENDEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENDVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, const GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENFEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENFVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENIEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXGENIVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXENVFVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXENVIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXGENDVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXGENFVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXGENIVEXTPROC)(GLenum texunit, GLenum coord, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETFLOATINDEXEDVEXTPROC)(GLenum target, GLuint index, GLfloat *data);
typedef void (GLE_FUNCPTR * PFNGLGETDOUBLEINDEXEDVEXTPROC)(GLenum target, GLuint index, GLdouble *data);
typedef void (GLE_FUNCPTR * PFNGLGETPOINTERINDEXEDVEXTPROC)(GLenum target, GLuint index, GLvoid* *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)(GLuint texture, GLenum target, GLint lod, GLvoid *img);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *bits);
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)(GLenum texunit, GLenum target, GLint lod, GLvoid *img);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMSTRINGEXTPROC)(GLuint program, GLenum target, GLenum format, GLsizei len, const GLvoid *string);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)(GLuint program, GLenum target, GLuint index, const GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)(GLuint program, GLenum target, GLuint index, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)(GLuint program, GLenum target, GLuint index, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)(GLuint program, GLenum target, GLuint index, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMIVEXTPROC)(GLuint program, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)(GLuint program, GLenum target, GLenum pname, GLvoid *string);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)(GLuint program, GLenum target, GLuint index, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)(GLuint program, GLenum target, GLuint index, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)(GLuint program, GLenum target, GLuint index, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)(GLuint program, GLenum target, GLuint index, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERIIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREPARAMETERIUIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTUREPARAMETERIIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)(GLuint texture, GLenum target, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERIIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXPARAMETERIUIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXPARAMETERIIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)(GLenum texunit, GLenum target, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1FEXTPROC)(GLuint program, GLint location, GLfloat v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2FEXTPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3FEXTPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4FEXTPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1IEXTPROC)(GLuint program, GLint location, GLint v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2IEXTPROC)(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3IEXTPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4IEXTPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1FVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2FVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3FVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4FVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1IVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2IVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3IVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4IVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UIEXTPROC)(GLuint program, GLint location, GLuint v0);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UIEXTPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UIEXTPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UIEXTPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UIVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UIVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UIVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UIVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLNAMEDBUFFERDATAEXTPROC)(GLuint buffer, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (GLE_FUNCPTR * PFNGLNAMEDBUFFERSUBDATAEXTPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const GLvoid *data);
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPNAMEDBUFFEREXTPROC)(GLuint buffer, GLenum access);
typedef GLboolean (GLE_FUNCPTR * PFNGLUNMAPNAMEDBUFFEREXTPROC)(GLuint buffer);
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPNAMEDBUFFERRANGEEXTPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (GLE_FUNCPTR * PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (GLE_FUNCPTR * PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)(GLuint buffer, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)(GLuint buffer, GLenum pname, GLvoid* *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREBUFFEREXTPROC)(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXBUFFEREXTPROC)(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)(GLuint renderbuffer, GLenum pname, GLint *params);
typedef GLenum (GLE_FUNCPTR * PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)(GLuint framebuffer, GLenum target);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGENERATETEXTUREMIPMAPEXTPROC)(GLuint texture, GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGENERATEMULTITEXMIPMAPEXTPROC)(GLenum texunit, GLenum target);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)(GLuint framebuffer, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)(GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERREADBUFFEREXTPROC)(GLuint framebuffer, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)(GLuint framebuffer, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLE_FUNCPTR * PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (GLE_FUNCPTR * PFNGLTEXTURERENDERBUFFEREXTPROC)(GLuint texture, GLenum target, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXRENDERBUFFEREXTPROC)(GLenum texunit, GLenum target, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1DEXTPROC)(GLuint program, GLint location, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2DEXTPROC)(GLuint program, GLint location, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3DEXTPROC)(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4DEXTPROC)(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1DVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2DVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3DVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4DVEXTPROC)(GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);

extern PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT;
extern PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT;
extern PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT;
extern PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT;
extern PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT;
extern PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT;
extern PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
extern PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT;
extern PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT;
extern PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT;
extern PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT;
extern PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT;
extern PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT;
extern PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT;
extern PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
extern PFNGLMATRIXPOPEXTPROC glMatrixPopEXT;
extern PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT;
extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT;
extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT;
extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT;
extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT;
extern PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT;
extern PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT;
extern PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT;
extern PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT;
extern PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT;
extern PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT;
extern PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT;
extern PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT;
extern PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT;
extern PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT;
extern PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT;
extern PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT;
extern PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT;
extern PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT;
extern PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT;
extern PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT;
extern PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT;
extern PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT;
extern PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT;
extern PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT;
extern PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT;
extern PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT;
extern PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT;
extern PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT;
extern PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT;
extern PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT;
extern PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT;
extern PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT;
extern PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT;
extern PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT;
extern PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT;
extern PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT;
extern PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT;
extern PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT;
extern PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT;
extern PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT;
extern PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT;
extern PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT;
extern PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT;
extern PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT;
extern PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT;
extern PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT;
extern PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT;
extern PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT;
extern PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT;
extern PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT;
extern PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT;
extern PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT;
extern PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT;
extern PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT;
extern PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT;
extern PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT;
extern PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT;
extern PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT;
extern PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT;
extern PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glNamedProgramLocalParameter4dvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glNamedProgramLocalParameter4fvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glGetNamedProgramLocalParameterdvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glGetNamedProgramLocalParameterfvEXT;
extern PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT;
extern PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glNamedProgramLocalParameters4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glNamedProgramLocalParameterI4iEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glNamedProgramLocalParameterI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glNamedProgramLocalParametersI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glNamedProgramLocalParameterI4uiEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glNamedProgramLocalParameterI4uivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glNamedProgramLocalParametersI4uivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glGetNamedProgramLocalParameterIivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glGetNamedProgramLocalParameterIuivEXT;
extern PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT;
extern PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT;
extern PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT;
extern PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT;
extern PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT;
extern PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT;
extern PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT;
extern PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT;
extern PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT;
extern PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT;
extern PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT;
extern PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT;
extern PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT;
extern PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT;
extern PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT;
extern PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT;
extern PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT;
extern PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT;
extern PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT;
extern PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT;
extern PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT;
extern PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT;
extern PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT;
extern PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT;
extern PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT;
extern PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT;
extern PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT;
extern PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT;
extern PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT;
extern PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT;
extern PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT;
extern PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT;
extern PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT;
extern PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT;
extern PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT;
extern PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT;
extern PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT;
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT;
extern PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT;
extern PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT;
extern PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT;
extern PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT;
extern PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT;
extern PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glGetNamedRenderbufferParameterivEXT;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetNamedFramebufferAttachmentParameterivEXT;
extern PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT;
extern PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT;
extern PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT;
extern PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glNamedRenderbufferStorageMultisampleEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glNamedRenderbufferStorageMultisampleCoverageEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT;
extern PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT;
extern PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT;
extern PFNGLPROGRAMUNIFORM1DEXTPROC glProgramUniform1dEXT;
extern PFNGLPROGRAMUNIFORM2DEXTPROC glProgramUniform2dEXT;
extern PFNGLPROGRAMUNIFORM3DEXTPROC glProgramUniform3dEXT;
extern PFNGLPROGRAMUNIFORM4DEXTPROC glProgramUniform4dEXT;
extern PFNGLPROGRAMUNIFORM1DVEXTPROC glProgramUniform1dvEXT;
extern PFNGLPROGRAMUNIFORM2DVEXTPROC glProgramUniform2dvEXT;
extern PFNGLPROGRAMUNIFORM3DVEXTPROC glProgramUniform3dvEXT;
extern PFNGLPROGRAMUNIFORM4DVEXTPROC glProgramUniform4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC glProgramUniformMatrix2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC glProgramUniformMatrix3dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC glProgramUniformMatrix4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC glProgramUniformMatrix2x3dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC glProgramUniformMatrix2x4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC glProgramUniformMatrix3x2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC glProgramUniformMatrix3x4dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC glProgramUniformMatrix4x2dvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC glProgramUniformMatrix4x3dvEXT;


/******************************
* Extension: GL_EXT_draw_buffers2
******************************/

typedef void (GLE_FUNCPTR * PFNGLCOLORMASKINDEXEDEXTPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANINDEXEDVEXTPROC)(GLenum target, GLuint index, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERINDEXEDVEXTPROC)(GLenum target, GLuint index, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLENABLEINDEXEDEXTPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLDISABLEINDEXEDEXTPROC)(GLenum target, GLuint index);
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDINDEXEDEXTPROC)(GLenum target, GLuint index);

extern PFNGLCOLORMASKINDEXEDEXTPROC glColorMaskIndexedEXT;
extern PFNGLGETBOOLEANINDEXEDVEXTPROC glGetBooleanIndexedvEXT;
extern PFNGLGETINTEGERINDEXEDVEXTPROC glGetIntegerIndexedvEXT;
extern PFNGLENABLEINDEXEDEXTPROC glEnableIndexedEXT;
extern PFNGLDISABLEINDEXEDEXTPROC glDisableIndexedEXT;
extern PFNGLISENABLEDINDEXEDEXTPROC glIsEnabledIndexedEXT;


/******************************
* Extension: GL_EXT_draw_instanced
******************************/

typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDEXTPROC)(GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDEXTPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);

extern PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstancedEXT;
extern PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstancedEXT;


/******************************
* Extension: GL_EXT_draw_range_elements
******************************/

#define GL_MAX_ELEMENTS_VERTICES_EXT 0x80E8
#define GL_MAX_ELEMENTS_INDICES_EXT 0x80E9


typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSEXTPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

extern PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElementsEXT;


/******************************
* Extension: GL_EXT_fog_coord
******************************/

#define GL_FRAGMENT_DEPTH_EXT 0x8452
#define GL_FOG_COORDINATE_SOURCE_EXT 0x8450
#define GL_FOG_COORDINATE_EXT 0x8451
#define GL_CURRENT_FOG_COORDINATE_EXT 0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT 0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT 0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT 0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT 0x8457


typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFEXTPROC)(GLfloat coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFVEXTPROC)(const GLfloat *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDEXTPROC)(GLdouble coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDVEXTPROC)(const GLdouble *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTEREXTPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);

extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
extern PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT;
extern PFNGLFOGCOORDDEXTPROC glFogCoorddEXT;
extern PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT;
extern PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT;


/******************************
* Extension: GL_EXT_framebuffer_blit
******************************/

#define GL_READ_FRAMEBUFFER_EXT 0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT 0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_EXT 0x8CA6 /* GL_FRAMEBUFFER_BINDING_EXT */
#define GL_READ_FRAMEBUFFER_BINDING_EXT 0x8CAA


typedef void (GLE_FUNCPTR * PFNGLBLITFRAMEBUFFEREXTPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

extern PFNGLBLITFRAMEBUFFEREXTPROC glBlitFramebufferEXT;


/******************************
* Extension: GL_EXT_framebuffer_multisample
******************************/

#define GL_RENDERBUFFER_SAMPLES_EXT 0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#define GL_MAX_SAMPLES_EXT 0x8D57


typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glRenderbufferStorageMultisampleEXT;


/******************************
* Extension: GL_EXT_framebuffer_object
******************************/

#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT 0x84E8
#define GL_FRAMEBUFFER_BINDING_EXT 0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT 0x8CA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE_EXT 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS_EXT 0x8CDF
#define GL_COLOR_ATTACHMENT0_EXT 0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT 0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT 0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT 0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT 0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT 0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT 0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT 0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT 0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT 0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT 0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT 0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT 0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT 0x8CED
#define GL_COLOR_ATTACHMENT14_EXT 0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT 0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT 0x8D00
#define GL_STENCIL_ATTACHMENT_EXT 0x8D20
#define GL_FRAMEBUFFER_EXT 0x8D40
#define GL_RENDERBUFFER_EXT 0x8D41
#define GL_RENDERBUFFER_WIDTH_EXT 0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
#define GL_STENCIL_INDEX1_EXT 0x8D46
#define GL_STENCIL_INDEX4_EXT 0x8D47
#define GL_STENCIL_INDEX8_EXT 0x8D48
#define GL_STENCIL_INDEX16_EXT 0x8D49
#define GL_RENDERBUFFER_RED_SIZE_EXT 0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT 0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT 0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT 0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT 0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT 0x8D55


typedef GLboolean (GLE_FUNCPTR * PFNGLISRENDERBUFFEREXTPROC)(GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLBINDRENDERBUFFEREXTPROC)(GLenum target, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLDELETERENDERBUFFERSEXTPROC)(GLsizei n, const GLuint *renderbuffers);
typedef void (GLE_FUNCPTR * PFNGLGENRENDERBUFFERSEXTPROC)(GLsizei n, GLuint *renderbuffers);
typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEEXTPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFRAMEBUFFEREXTPROC)(GLuint framebuffer);
typedef void (GLE_FUNCPTR * PFNGLBINDFRAMEBUFFEREXTPROC)(GLenum target, GLuint framebuffer);
typedef void (GLE_FUNCPTR * PFNGLDELETEFRAMEBUFFERSEXTPROC)(GLsizei n, const GLuint *framebuffers);
typedef void (GLE_FUNCPTR * PFNGLGENFRAMEBUFFERSEXTPROC)(GLsizei n, GLuint *framebuffers);
typedef GLenum (GLE_FUNCPTR * PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (GLE_FUNCPTR * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)(GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGENERATEMIPMAPEXTPROC)(GLenum target);

extern PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
extern PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
extern PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
extern PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT;
extern PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
extern PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
extern PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
extern PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;


/******************************
* Extension: GL_EXT_framebuffer_sRGB
******************************/

#define GL_FRAMEBUFFER_SRGB_EXT 0x8DB9
#define GL_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x8DBA


/******************************
* Extension: GL_EXT_geometry_shader4
******************************/

#define GL_LINES_ADJACENCY_EXT 0x000A
#define GL_LINE_STRIP_ADJACENCY_EXT 0x000B
#define GL_TRIANGLES_ADJACENCY_EXT 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT 0x000D
#define GL_GEOMETRY_VERTICES_OUT_EXT 0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT 0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT 0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT 0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT 0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT 0x8642
#define GL_GEOMETRY_SHADER_EXT 0x8DD9
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT 0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT 0x8DDE
#define GL_MAX_VARYING_COMPONENTS_EXT 0x8B4B
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT 0x8DE1


typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIEXTPROC)(GLuint program, GLenum pname, GLint value);

extern PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT;


/******************************
* Extension: GL_EXT_gpu_program_parameters
******************************/

typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, const GLfloat *params);

extern PFNGLPROGRAMENVPARAMETERS4FVEXTPROC glProgramEnvParameters4fvEXT;
extern PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC glProgramLocalParameters4fvEXT;


/******************************
* Extension: GL_EXT_gpu_shader4
******************************/

#define GL_SAMPLER_1D_ARRAY_EXT 0x8DC0
#define GL_SAMPLER_2D_ARRAY_EXT 0x8DC1
#define GL_SAMPLER_BUFFER_EXT 0x8DC2
#define GL_SAMPLER_1D_ARRAY_SHADOW_EXT 0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW_EXT 0x8DC4
#define GL_SAMPLER_CUBE_SHADOW_EXT 0x8DC5
#define GL_UNSIGNED_INT_VEC2_EXT 0x8DC6
#define GL_UNSIGNED_INT_VEC3_EXT 0x8DC7
#define GL_UNSIGNED_INT_VEC4_EXT 0x8DC8
#define GL_INT_SAMPLER_1D_EXT 0x8DC9
#define GL_INT_SAMPLER_2D_EXT 0x8DCA
#define GL_INT_SAMPLER_3D_EXT 0x8DCB
#define GL_INT_SAMPLER_CUBE_EXT 0x8DCC
#define GL_INT_SAMPLER_2D_RECT_EXT 0x8DCD
#define GL_INT_SAMPLER_1D_ARRAY_EXT 0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY_EXT 0x8DCF
#define GL_INT_SAMPLER_BUFFER_EXT 0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_1D_EXT 0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D_EXT 0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D_EXT 0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE_EXT 0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT 0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT 0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT 0x8DD7
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT 0x8DD8


typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMUIVEXTPROC)(GLuint program, GLint location, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLBINDFRAGDATALOCATIONEXTPROC)(GLuint program, GLuint color, const GLchar *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETFRAGDATALOCATIONEXTPROC)(GLuint program, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIEXTPROC)(GLint location, GLuint v0);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIEXTPROC)(GLint location, GLuint v0, GLuint v1);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIEXTPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIEXTPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIVEXTPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIVEXTPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIVEXTPROC)(GLint location, GLsizei count, const GLuint *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIVEXTPROC)(GLint location, GLsizei count, const GLuint *value);

extern PFNGLGETUNIFORMUIVEXTPROC glGetUniformuivEXT;
extern PFNGLBINDFRAGDATALOCATIONEXTPROC glBindFragDataLocationEXT;
extern PFNGLGETFRAGDATALOCATIONEXTPROC glGetFragDataLocationEXT;
extern PFNGLUNIFORM1UIEXTPROC glUniform1uiEXT;
extern PFNGLUNIFORM2UIEXTPROC glUniform2uiEXT;
extern PFNGLUNIFORM3UIEXTPROC glUniform3uiEXT;
extern PFNGLUNIFORM4UIEXTPROC glUniform4uiEXT;
extern PFNGLUNIFORM1UIVEXTPROC glUniform1uivEXT;
extern PFNGLUNIFORM2UIVEXTPROC glUniform2uivEXT;
extern PFNGLUNIFORM3UIVEXTPROC glUniform3uivEXT;
extern PFNGLUNIFORM4UIVEXTPROC glUniform4uivEXT;


/******************************
* Extension: GL_EXT_histogram
******************************/

#define GL_HISTOGRAM_EXT 0x8024
#define GL_PROXY_HISTOGRAM_EXT 0x8025
#define GL_HISTOGRAM_WIDTH_EXT 0x8026
#define GL_HISTOGRAM_FORMAT_EXT 0x8027
#define GL_HISTOGRAM_RED_SIZE_EXT 0x8028
#define GL_HISTOGRAM_GREEN_SIZE_EXT 0x8029
#define GL_HISTOGRAM_BLUE_SIZE_EXT 0x802A
#define GL_HISTOGRAM_ALPHA_SIZE_EXT 0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE_EXT 0x802C
#define GL_HISTOGRAM_SINK_EXT 0x802D
#define GL_MINMAX_EXT 0x802E
#define GL_MINMAX_FORMAT_EXT 0x802F
#define GL_MINMAX_SINK_EXT 0x8030
#define GL_TABLE_TOO_LARGE_EXT 0x8031


typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMEXTPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXEXTPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLHISTOGRAMEXTPROC)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (GLE_FUNCPTR * PFNGLMINMAXEXTPROC)(GLenum target, GLenum internalformat, GLboolean sink);
typedef void (GLE_FUNCPTR * PFNGLRESETHISTOGRAMEXTPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLRESETMINMAXEXTPROC)(GLenum target);

extern PFNGLGETHISTOGRAMEXTPROC glGetHistogramEXT;
extern PFNGLGETHISTOGRAMPARAMETERFVEXTPROC glGetHistogramParameterfvEXT;
extern PFNGLGETHISTOGRAMPARAMETERIVEXTPROC glGetHistogramParameterivEXT;
extern PFNGLGETMINMAXEXTPROC glGetMinmaxEXT;
extern PFNGLGETMINMAXPARAMETERFVEXTPROC glGetMinmaxParameterfvEXT;
extern PFNGLGETMINMAXPARAMETERIVEXTPROC glGetMinmaxParameterivEXT;
extern PFNGLHISTOGRAMEXTPROC glHistogramEXT;
extern PFNGLMINMAXEXTPROC glMinmaxEXT;
extern PFNGLRESETHISTOGRAMEXTPROC glResetHistogramEXT;
extern PFNGLRESETMINMAXEXTPROC glResetMinmaxEXT;


/******************************
* Extension: GL_EXT_index_array_formats
******************************/

#define GL_IUI_V2F_EXT 0x81AD
#define GL_IUI_V3F_EXT 0x81AE
#define GL_IUI_N3F_V2F_EXT 0x81AF
#define GL_IUI_N3F_V3F_EXT 0x81B0
#define GL_T2F_IUI_V2F_EXT 0x81B1
#define GL_T2F_IUI_V3F_EXT 0x81B2
#define GL_T2F_IUI_N3F_V2F_EXT 0x81B3
#define GL_T2F_IUI_N3F_V3F_EXT 0x81B4


/******************************
* Extension: GL_EXT_index_func
******************************/

#define GL_INDEX_TEST_EXT 0x81B5
#define GL_INDEX_TEST_FUNC_EXT 0x81B6
#define GL_INDEX_TEST_REF_EXT 0x81B7


typedef void (GLE_FUNCPTR * PFNGLINDEXFUNCEXTPROC)(GLenum func, GLclampf ref);

extern PFNGLINDEXFUNCEXTPROC glIndexFuncEXT;


/******************************
* Extension: GL_EXT_index_material
******************************/

#define GL_INDEX_MATERIAL_EXT 0x81B8
#define GL_INDEX_MATERIAL_PARAMETER_EXT 0x81B9
#define GL_INDEX_MATERIAL_FACE_EXT 0x81BA


typedef void (GLE_FUNCPTR * PFNGLINDEXMATERIALEXTPROC)(GLenum face, GLenum mode);

extern PFNGLINDEXMATERIALEXTPROC glIndexMaterialEXT;


/******************************
* Extension: GL_EXT_index_texture
******************************/

/******************************
* Extension: GL_EXT_light_texture
******************************/

#define GL_FRAGMENT_MATERIAL_EXT 0x8349
#define GL_FRAGMENT_NORMAL_EXT 0x834A
#define GL_FRAGMENT_COLOR_EXT 0x834C
#define GL_ATTENUATION_EXT 0x834D
#define GL_SHADOW_ATTENUATION_EXT 0x834E
#define GL_TEXTURE_APPLICATION_MODE_EXT 0x834F
#define GL_TEXTURE_LIGHT_EXT 0x8350
#define GL_TEXTURE_MATERIAL_FACE_EXT 0x8351
#define GL_TEXTURE_MATERIAL_PARAMETER_EXT 0x8352
#define GL_FRAGMENT_DEPTH_EXT 0x8452


typedef void (GLE_FUNCPTR * PFNGLAPPLYTEXTUREEXTPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLTEXTURELIGHTEXTPROC)(GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREMATERIALEXTPROC)(GLenum face, GLenum mode);

extern PFNGLAPPLYTEXTUREEXTPROC glApplyTextureEXT;
extern PFNGLTEXTURELIGHTEXTPROC glTextureLightEXT;
extern PFNGLTEXTUREMATERIALEXTPROC glTextureMaterialEXT;


/******************************
* Extension: GL_EXT_misc_attribute
******************************/

/******************************
* Extension: GL_EXT_multi_draw_arrays
******************************/

typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWARRAYSEXTPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSEXTPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);

extern PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT;
extern PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT;


/******************************
* Extension: GL_EXT_multisample
******************************/

#define GL_MULTISAMPLE_EXT 0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_EXT 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_EXT 0x809F
#define GL_SAMPLE_MASK_EXT 0x80A0
#define GL_1PASS_EXT 0x80A1
#define GL_2PASS_0_EXT 0x80A2
#define GL_2PASS_1_EXT 0x80A3
#define GL_4PASS_0_EXT 0x80A4
#define GL_4PASS_1_EXT 0x80A5
#define GL_4PASS_2_EXT 0x80A6
#define GL_4PASS_3_EXT 0x80A7
#define GL_SAMPLE_BUFFERS_EXT 0x80A8
#define GL_SAMPLES_EXT 0x80A9
#define GL_SAMPLE_MASK_VALUE_EXT 0x80AA
#define GL_SAMPLE_MASK_INVERT_EXT 0x80AB
#define GL_SAMPLE_PATTERN_EXT 0x80AC
#define GL_MULTISAMPLE_BIT_EXT 0x20000000


typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKEXTPROC)(GLclampf value, GLboolean invert);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEPATTERNEXTPROC)(GLenum pattern);

extern PFNGLSAMPLEMASKEXTPROC glSampleMaskEXT;
extern PFNGLSAMPLEPATTERNEXTPROC glSamplePatternEXT;


/******************************
* Extension: GL_EXT_packed_depth_stencil
******************************/

#define GL_DEPTH_STENCIL_EXT 0x84F9
#define GL_UNSIGNED_INT_24_8_EXT 0x84FA
#define GL_DEPTH24_STENCIL8_EXT 0x88F0
#define GL_TEXTURE_STENCIL_SIZE_EXT 0x88F1


/******************************
* Extension: GL_EXT_packed_float
******************************/

#define GL_R11F_G11F_B10F_EXT 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV_EXT 0x8C3B
#define GL_RGBA_SIGNED_COMPONENTS_EXT 0x8C3C


/******************************
* Extension: GL_EXT_packed_pixels
******************************/

#define GL_UNSIGNED_BYTE_3_3_2_EXT 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT 0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT 0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT 0x8036


/******************************
* Extension: GL_EXT_paletted_texture
******************************/

#define GL_COLOR_INDEX1_EXT 0x80E2
#define GL_COLOR_INDEX2_EXT 0x80E3
#define GL_COLOR_INDEX4_EXT 0x80E4
#define GL_COLOR_INDEX8_EXT 0x80E5
#define GL_COLOR_INDEX12_EXT 0x80E6
#define GL_COLOR_INDEX16_EXT 0x80E7
#define GL_TEXTURE_INDEX_SIZE_EXT 0x80ED


typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEEXTPROC)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEEXTPROC)(GLenum target, GLenum format, GLenum type, GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);

extern PFNGLCOLORTABLEEXTPROC glColorTableEXT;
extern PFNGLGETCOLORTABLEEXTPROC glGetColorTableEXT;
extern PFNGLGETCOLORTABLEPARAMETERIVEXTPROC glGetColorTableParameterivEXT;
extern PFNGLGETCOLORTABLEPARAMETERFVEXTPROC glGetColorTableParameterfvEXT;


/******************************
* Extension: GL_EXT_pixel_buffer_object
******************************/

#define GL_PIXEL_PACK_BUFFER_EXT 0x88EB
#define GL_PIXEL_UNPACK_BUFFER_EXT 0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_EXT 0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_EXT 0x88EF


/******************************
* Extension: GL_EXT_pixel_transform
******************************/

#define GL_PIXEL_TRANSFORM_2D_EXT 0x8330
#define GL_PIXEL_MAG_FILTER_EXT 0x8331
#define GL_PIXEL_MIN_FILTER_EXT 0x8332
#define GL_PIXEL_CUBIC_WEIGHT_EXT 0x8333
#define GL_CUBIC_EXT 0x8334
#define GL_AVERAGE_EXT 0x8335
#define GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT 0x8336
#define GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT 0x8337
#define GL_PIXEL_TRANSFORM_2D_MATRIX_EXT 0x8338


typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)(GLenum target, GLenum pname, const GLfloat *params);

extern PFNGLPIXELTRANSFORMPARAMETERIEXTPROC glPixelTransformParameteriEXT;
extern PFNGLPIXELTRANSFORMPARAMETERFEXTPROC glPixelTransformParameterfEXT;
extern PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC glPixelTransformParameterivEXT;
extern PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC glPixelTransformParameterfvEXT;


/******************************
* Extension: GL_EXT_pixel_transform_color_table
******************************/

/******************************
* Extension: GL_EXT_point_parameters
******************************/

#define GL_POINT_SIZE_MIN_EXT 0x8126
#define GL_POINT_SIZE_MAX_EXT 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT 0x8128
#define GL_DISTANCE_ATTENUATION_EXT 0x8129


typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFEXTPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVEXTPROC)(GLenum pname, const GLfloat *params);

extern PFNGLPOINTPARAMETERFEXTPROC glPointParameterfEXT;
extern PFNGLPOINTPARAMETERFVEXTPROC glPointParameterfvEXT;


/******************************
* Extension: GL_EXT_polygon_offset
******************************/

#define GL_POLYGON_OFFSET_EXT 0x8037
#define GL_POLYGON_OFFSET_FACTOR_EXT 0x8038
#define GL_POLYGON_OFFSET_BIAS_EXT 0x8039


typedef void (GLE_FUNCPTR * PFNGLPOLYGONOFFSETEXTPROC)(GLfloat factor, GLfloat bias);

extern PFNGLPOLYGONOFFSETEXTPROC glPolygonOffsetEXT;


/******************************
* Extension: GL_EXT_provoking_vertex
******************************/

#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION_EXT 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION_EXT 0x8E4D
#define GL_LAST_VERTEX_CONVENTION_EXT 0x8E4E
#define GL_PROVOKING_VERTEX_EXT 0x8E4F


typedef void (GLE_FUNCPTR * PFNGLPROVOKINGVERTEXEXTPROC)(GLenum mode);

extern PFNGLPROVOKINGVERTEXEXTPROC glProvokingVertexEXT;


/******************************
* Extension: GL_EXT_rescale_normal
******************************/

#define GL_RESCALE_NORMAL_EXT 0x803A


/******************************
* Extension: GL_EXT_secondary_color
******************************/

#define GL_COLOR_SUM_EXT 0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT 0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT 0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT 0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT 0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT 0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT 0x845E


typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BEXTPROC)(GLbyte red, GLbyte green, GLbyte blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BVEXTPROC)(const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DEXTPROC)(GLdouble red, GLdouble green, GLdouble blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DVEXTPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FEXTPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FVEXTPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IEXTPROC)(GLint red, GLint green, GLint blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IVEXTPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SEXTPROC)(GLshort red, GLshort green, GLshort blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SVEXTPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBEXTPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBVEXTPROC)(const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIEXTPROC)(GLuint red, GLuint green, GLuint blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIVEXTPROC)(const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USEXTPROC)(GLushort red, GLushort green, GLushort blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USVEXTPROC)(const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern PFNGLSECONDARYCOLOR3BEXTPROC glSecondaryColor3bEXT;
extern PFNGLSECONDARYCOLOR3BVEXTPROC glSecondaryColor3bvEXT;
extern PFNGLSECONDARYCOLOR3DEXTPROC glSecondaryColor3dEXT;
extern PFNGLSECONDARYCOLOR3DVEXTPROC glSecondaryColor3dvEXT;
extern PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT;
extern PFNGLSECONDARYCOLOR3FVEXTPROC glSecondaryColor3fvEXT;
extern PFNGLSECONDARYCOLOR3IEXTPROC glSecondaryColor3iEXT;
extern PFNGLSECONDARYCOLOR3IVEXTPROC glSecondaryColor3ivEXT;
extern PFNGLSECONDARYCOLOR3SEXTPROC glSecondaryColor3sEXT;
extern PFNGLSECONDARYCOLOR3SVEXTPROC glSecondaryColor3svEXT;
extern PFNGLSECONDARYCOLOR3UBEXTPROC glSecondaryColor3ubEXT;
extern PFNGLSECONDARYCOLOR3UBVEXTPROC glSecondaryColor3ubvEXT;
extern PFNGLSECONDARYCOLOR3UIEXTPROC glSecondaryColor3uiEXT;
extern PFNGLSECONDARYCOLOR3UIVEXTPROC glSecondaryColor3uivEXT;
extern PFNGLSECONDARYCOLOR3USEXTPROC glSecondaryColor3usEXT;
extern PFNGLSECONDARYCOLOR3USVEXTPROC glSecondaryColor3usvEXT;
extern PFNGLSECONDARYCOLORPOINTEREXTPROC glSecondaryColorPointerEXT;


/******************************
* Extension: GL_EXT_separate_shader_objects
******************************/

#define GL_ACTIVE_PROGRAM_EXT 0x8B8D


typedef void (GLE_FUNCPTR * PFNGLUSESHADERPROGRAMEXTPROC)(GLenum type, GLuint program);
typedef void (GLE_FUNCPTR * PFNGLACTIVEPROGRAMEXTPROC)(GLuint program);
typedef GLuint (GLE_FUNCPTR * PFNGLCREATESHADERPROGRAMEXTPROC)(GLenum type, const GLchar *string);

extern PFNGLUSESHADERPROGRAMEXTPROC glUseShaderProgramEXT;
extern PFNGLACTIVEPROGRAMEXTPROC glActiveProgramEXT;
extern PFNGLCREATESHADERPROGRAMEXTPROC glCreateShaderProgramEXT;


/******************************
* Extension: GL_EXT_separate_specular_color
******************************/

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT 0x81F8
#define GL_SINGLE_COLOR_EXT 0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT 0x81FA


/******************************
* Extension: GL_EXT_shader_image_load_store
******************************/

#define GL_MAX_IMAGE_UNITS_EXT 0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS_EXT 0x8F39
#define GL_IMAGE_BINDING_NAME_EXT 0x8F3A
#define GL_IMAGE_BINDING_LEVEL_EXT 0x8F3B
#define GL_IMAGE_BINDING_LAYERED_EXT 0x8F3C
#define GL_IMAGE_BINDING_LAYER_EXT 0x8F3D
#define GL_IMAGE_BINDING_ACCESS_EXT 0x8F3E
#define GL_IMAGE_1D_EXT 0x904C
#define GL_IMAGE_2D_EXT 0x904D
#define GL_IMAGE_3D_EXT 0x904E
#define GL_IMAGE_2D_RECT_EXT 0x904F
#define GL_IMAGE_CUBE_EXT 0x9050
#define GL_IMAGE_BUFFER_EXT 0x9051
#define GL_IMAGE_1D_ARRAY_EXT 0x9052
#define GL_IMAGE_2D_ARRAY_EXT 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY_EXT 0x9054
#define GL_IMAGE_2D_MULTISAMPLE_EXT 0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x9056
#define GL_INT_IMAGE_1D_EXT 0x9057
#define GL_INT_IMAGE_2D_EXT 0x9058
#define GL_INT_IMAGE_3D_EXT 0x9059
#define GL_INT_IMAGE_2D_RECT_EXT 0x905A
#define GL_INT_IMAGE_CUBE_EXT 0x905B
#define GL_INT_IMAGE_BUFFER_EXT 0x905C
#define GL_INT_IMAGE_1D_ARRAY_EXT 0x905D
#define GL_INT_IMAGE_2D_ARRAY_EXT 0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE_EXT 0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D_EXT 0x9062
#define GL_UNSIGNED_INT_IMAGE_2D_EXT 0x9063
#define GL_UNSIGNED_INT_IMAGE_3D_EXT 0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT_EXT 0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE_EXT 0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER_EXT 0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY_EXT 0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY_EXT 0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_EXT 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT 0x906C
#define GL_MAX_IMAGE_SAMPLES_EXT 0x906D
#define GL_IMAGE_BINDING_FORMAT_EXT 0x906E
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT_EXT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT_EXT 0x00000002
#define GL_UNIFORM_BARRIER_BIT_EXT 0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT_EXT 0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT_EXT 0x00000020
#define GL_COMMAND_BARRIER_BIT_EXT 0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT_EXT 0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT_EXT 0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT_EXT 0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT_EXT 0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT_EXT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT_EXT 0x00001000
#define GL_ALL_BARRIER_BITS_EXT 0xFFFFFFFF


typedef void (GLE_FUNCPTR * PFNGLBINDIMAGETEXTUREEXTPROC)(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format);
typedef void (GLE_FUNCPTR * PFNGLMEMORYBARRIEREXTPROC)(GLbitfield barriers);

extern PFNGLBINDIMAGETEXTUREEXTPROC glBindImageTextureEXT;
extern PFNGLMEMORYBARRIEREXTPROC glMemoryBarrierEXT;


/******************************
* Extension: GL_EXT_shadow_funcs
******************************/

/******************************
* Extension: GL_EXT_shared_texture_palette
******************************/

#define GL_SHARED_TEXTURE_PALETTE_EXT 0x81FB


/******************************
* Extension: GL_EXT_stencil_clear_tag
******************************/

#define GL_STENCIL_TAG_BITS_EXT 0x88F2
#define GL_STENCIL_CLEAR_TAG_VALUE_EXT 0x88F3


typedef void (GLE_FUNCPTR * PFNGLSTENCILCLEARTAGEXTPROC)(GLsizei stencilTagBits, GLuint stencilClearTag);

extern PFNGLSTENCILCLEARTAGEXTPROC glStencilClearTagEXT;


/******************************
* Extension: GL_EXT_stencil_two_side
******************************/

#define GL_STENCIL_TEST_TWO_SIDE_EXT 0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT 0x8911


typedef void (GLE_FUNCPTR * PFNGLACTIVESTENCILFACEEXTPROC)(GLenum face);

extern PFNGLACTIVESTENCILFACEEXTPROC glActiveStencilFaceEXT;


/******************************
* Extension: GL_EXT_stencil_wrap
******************************/

#define GL_INCR_WRAP_EXT 0x8507
#define GL_DECR_WRAP_EXT 0x8508


/******************************
* Extension: GL_EXT_subtexture
******************************/

typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE1DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE2DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

extern PFNGLTEXSUBIMAGE1DEXTPROC glTexSubImage1DEXT;
extern PFNGLTEXSUBIMAGE2DEXTPROC glTexSubImage2DEXT;


/******************************
* Extension: GL_EXT_texture
******************************/

#define GL_ALPHA4_EXT 0x803B
#define GL_ALPHA8_EXT 0x803C
#define GL_ALPHA12_EXT 0x803D
#define GL_ALPHA16_EXT 0x803E
#define GL_LUMINANCE4_EXT 0x803F
#define GL_LUMINANCE8_EXT 0x8040
#define GL_LUMINANCE12_EXT 0x8041
#define GL_LUMINANCE16_EXT 0x8042
#define GL_LUMINANCE4_ALPHA4_EXT 0x8043
#define GL_LUMINANCE6_ALPHA2_EXT 0x8044
#define GL_LUMINANCE8_ALPHA8_EXT 0x8045
#define GL_LUMINANCE12_ALPHA4_EXT 0x8046
#define GL_LUMINANCE12_ALPHA12_EXT 0x8047
#define GL_LUMINANCE16_ALPHA16_EXT 0x8048
#define GL_INTENSITY_EXT 0x8049
#define GL_INTENSITY4_EXT 0x804A
#define GL_INTENSITY8_EXT 0x804B
#define GL_INTENSITY12_EXT 0x804C
#define GL_INTENSITY16_EXT 0x804D
#define GL_RGB2_EXT 0x804E
#define GL_RGB4_EXT 0x804F
#define GL_RGB5_EXT 0x8050
#define GL_RGB8_EXT 0x8051
#define GL_RGB10_EXT 0x8052
#define GL_RGB12_EXT 0x8053
#define GL_RGB16_EXT 0x8054
#define GL_RGBA2_EXT 0x8055
#define GL_RGBA4_EXT 0x8056
#define GL_RGB5_A1_EXT 0x8057
#define GL_RGBA8_EXT 0x8058
#define GL_RGB10_A2_EXT 0x8059
#define GL_RGBA12_EXT 0x805A
#define GL_RGBA16_EXT 0x805B
#define GL_TEXTURE_RED_SIZE_EXT 0x805C
#define GL_TEXTURE_GREEN_SIZE_EXT 0x805D
#define GL_TEXTURE_BLUE_SIZE_EXT 0x805E
#define GL_TEXTURE_ALPHA_SIZE_EXT 0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_EXT 0x8060
#define GL_TEXTURE_INTENSITY_SIZE_EXT 0x8061
#define GL_REPLACE_EXT 0x8062
#define GL_PROXY_TEXTURE_1D_EXT 0x8063
#define GL_PROXY_TEXTURE_2D_EXT 0x8064
#define GL_TEXTURE_TOO_LARGE_EXT 0x8065


/******************************
* Extension: GL_EXT_texture3D
******************************/

#define GL_PACK_SKIP_IMAGES_EXT 0x806B
#define GL_PACK_IMAGE_HEIGHT_EXT 0x806C
#define GL_UNPACK_SKIP_IMAGES_EXT 0x806D
#define GL_UNPACK_IMAGE_HEIGHT_EXT 0x806E
#define GL_TEXTURE_3D_EXT 0x806F
#define GL_PROXY_TEXTURE_3D_EXT 0x8070
#define GL_TEXTURE_DEPTH_EXT 0x8071
#define GL_TEXTURE_WRAP_R_EXT 0x8072
#define GL_MAX_3D_TEXTURE_SIZE_EXT 0x8073


typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE3DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);

extern PFNGLTEXIMAGE3DEXTPROC glTexImage3DEXT;
extern PFNGLTEXSUBIMAGE3DEXTPROC glTexSubImage3DEXT;


/******************************
* Extension: GL_EXT_texture_array
******************************/

#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT 0x8CD4
#define GL_TEXTURE_1D_ARRAY_EXT 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY_EXT 0x8C19
#define GL_TEXTURE_2D_ARRAY_EXT 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY_EXT 0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY_EXT 0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY_EXT 0x8C1D
#define GL_MAX_ARRAY_TEXTURE_LAYERS_EXT 0x88FF
#define GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT 0x884E


/******************************
* Extension: GL_EXT_texture_buffer_object
******************************/

#define GL_TEXTURE_BUFFER_EXT 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_EXT 0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_EXT 0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT 0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_EXT 0x8C2E


typedef void (GLE_FUNCPTR * PFNGLTEXBUFFEREXTPROC)(GLenum target, GLenum internalformat, GLuint buffer);

extern PFNGLTEXBUFFEREXTPROC glTexBufferEXT;


/******************************
* Extension: GL_EXT_texture_compression_latc
******************************/

#define GL_COMPRESSED_LUMINANCE_LATC1_EXT 0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT 0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT 0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT 0x8C73


/******************************
* Extension: GL_EXT_texture_compression_rgtc
******************************/

#define GL_COMPRESSED_RED_RGTC1_EXT 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#define GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE


/******************************
* Extension: GL_EXT_texture_compression_s3tc
******************************/

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3


/******************************
* Extension: GL_EXT_texture_cube_map
******************************/

#define GL_NORMAL_MAP_EXT 0x8511
#define GL_REFLECTION_MAP_EXT 0x8512
#define GL_TEXTURE_CUBE_MAP_EXT 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT 0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT 0x851C


/******************************
* Extension: GL_EXT_texture_env_add
******************************/

/******************************
* Extension: GL_EXT_texture_env_combine
******************************/

#define GL_COMBINE_EXT 0x8570
#define GL_COMBINE_RGB_EXT 0x8571
#define GL_COMBINE_ALPHA_EXT 0x8572
#define GL_RGB_SCALE_EXT 0x8573
#define GL_ADD_SIGNED_EXT 0x8574
#define GL_INTERPOLATE_EXT 0x8575
#define GL_CONSTANT_EXT 0x8576
#define GL_PRIMARY_COLOR_EXT 0x8577
#define GL_PREVIOUS_EXT 0x8578
#define GL_SOURCE0_RGB_EXT 0x8580
#define GL_SOURCE1_RGB_EXT 0x8581
#define GL_SOURCE2_RGB_EXT 0x8582
#define GL_SOURCE0_ALPHA_EXT 0x8588
#define GL_SOURCE1_ALPHA_EXT 0x8589
#define GL_SOURCE2_ALPHA_EXT 0x858A
#define GL_OPERAND0_RGB_EXT 0x8590
#define GL_OPERAND1_RGB_EXT 0x8591
#define GL_OPERAND2_RGB_EXT 0x8592
#define GL_OPERAND0_ALPHA_EXT 0x8598
#define GL_OPERAND1_ALPHA_EXT 0x8599
#define GL_OPERAND2_ALPHA_EXT 0x859A


/******************************
* Extension: GL_EXT_texture_env_dot3
******************************/

#define GL_DOT3_RGB_EXT 0x8740
#define GL_DOT3_RGBA_EXT 0x8741


/******************************
* Extension: GL_EXT_texture_filter_anisotropic
******************************/

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF


/******************************
* Extension: GL_EXT_texture_integer
******************************/

#define GL_RGBA32UI_EXT 0x8D70
#define GL_RGB32UI_EXT 0x8D71
#define GL_ALPHA32UI_EXT 0x8D72
#define GL_INTENSITY32UI_EXT 0x8D73
#define GL_LUMINANCE32UI_EXT 0x8D74
#define GL_LUMINANCE_ALPHA32UI_EXT 0x8D75
#define GL_RGBA16UI_EXT 0x8D76
#define GL_RGB16UI_EXT 0x8D77
#define GL_ALPHA16UI_EXT 0x8D78
#define GL_INTENSITY16UI_EXT 0x8D79
#define GL_LUMINANCE16UI_EXT 0x8D7A
#define GL_LUMINANCE_ALPHA16UI_EXT 0x8D7B
#define GL_RGBA8UI_EXT 0x8D7C
#define GL_RGB8UI_EXT 0x8D7D
#define GL_ALPHA8UI_EXT 0x8D7E
#define GL_INTENSITY8UI_EXT 0x8D7F
#define GL_LUMINANCE8UI_EXT 0x8D80
#define GL_LUMINANCE_ALPHA8UI_EXT 0x8D81
#define GL_RGBA32I_EXT 0x8D82
#define GL_RGB32I_EXT 0x8D83
#define GL_ALPHA32I_EXT 0x8D84
#define GL_INTENSITY32I_EXT 0x8D85
#define GL_LUMINANCE32I_EXT 0x8D86
#define GL_LUMINANCE_ALPHA32I_EXT 0x8D87
#define GL_RGBA16I_EXT 0x8D88
#define GL_RGB16I_EXT 0x8D89
#define GL_ALPHA16I_EXT 0x8D8A
#define GL_INTENSITY16I_EXT 0x8D8B
#define GL_LUMINANCE16I_EXT 0x8D8C
#define GL_LUMINANCE_ALPHA16I_EXT 0x8D8D
#define GL_RGBA8I_EXT 0x8D8E
#define GL_RGB8I_EXT 0x8D8F
#define GL_ALPHA8I_EXT 0x8D90
#define GL_INTENSITY8I_EXT 0x8D91
#define GL_LUMINANCE8I_EXT 0x8D92
#define GL_LUMINANCE_ALPHA8I_EXT 0x8D93
#define GL_RED_INTEGER_EXT 0x8D94
#define GL_GREEN_INTEGER_EXT 0x8D95
#define GL_BLUE_INTEGER_EXT 0x8D96
#define GL_ALPHA_INTEGER_EXT 0x8D97
#define GL_RGB_INTEGER_EXT 0x8D98
#define GL_RGBA_INTEGER_EXT 0x8D99
#define GL_BGR_INTEGER_EXT 0x8D9A
#define GL_BGRA_INTEGER_EXT 0x8D9B
#define GL_LUMINANCE_INTEGER_EXT 0x8D9C
#define GL_LUMINANCE_ALPHA_INTEGER_EXT 0x8D9D
#define GL_RGBA_INTEGER_MODE_EXT 0x8D9E


typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIIVEXTPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIUIVEXTPROC)(GLenum target, GLenum pname, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIUIVEXTPROC)(GLenum target, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORIIEXTPROC)(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORIUIEXTPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);

extern PFNGLTEXPARAMETERIIVEXTPROC glTexParameterIivEXT;
extern PFNGLTEXPARAMETERIUIVEXTPROC glTexParameterIuivEXT;
extern PFNGLGETTEXPARAMETERIIVEXTPROC glGetTexParameterIivEXT;
extern PFNGLGETTEXPARAMETERIUIVEXTPROC glGetTexParameterIuivEXT;
extern PFNGLCLEARCOLORIIEXTPROC glClearColorIiEXT;
extern PFNGLCLEARCOLORIUIEXTPROC glClearColorIuiEXT;


/******************************
* Extension: GL_EXT_texture_lod_bias
******************************/

#define GL_MAX_TEXTURE_LOD_BIAS_EXT 0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT 0x8500
#define GL_TEXTURE_LOD_BIAS_EXT 0x8501


/******************************
* Extension: GL_EXT_texture_mirror_clamp
******************************/

#define GL_MIRROR_CLAMP_EXT 0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_EXT 0x8743
#define GL_MIRROR_CLAMP_TO_BORDER_EXT 0x8912


/******************************
* Extension: GL_EXT_texture_object
******************************/

#define GL_TEXTURE_PRIORITY_EXT 0x8066
#define GL_TEXTURE_RESIDENT_EXT 0x8067
#define GL_TEXTURE_1D_BINDING_EXT 0x8068
#define GL_TEXTURE_2D_BINDING_EXT 0x8069
#define GL_TEXTURE_3D_BINDING_EXT 0x806A


typedef GLboolean (GLE_FUNCPTR * PFNGLARETEXTURESRESIDENTEXTPROC)(GLsizei n, const GLuint *textures, GLboolean *residences);
typedef void (GLE_FUNCPTR * PFNGLBINDTEXTUREEXTPROC)(GLenum target, GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLDELETETEXTURESEXTPROC)(GLsizei n, const GLuint *textures);
typedef void (GLE_FUNCPTR * PFNGLGENTEXTURESEXTPROC)(GLsizei n, GLuint *textures);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTEXTUREEXTPROC)(GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLPRIORITIZETEXTURESEXTPROC)(GLsizei n, const GLuint *textures, const GLclampf *priorities);

extern PFNGLARETEXTURESRESIDENTEXTPROC glAreTexturesResidentEXT;
extern PFNGLBINDTEXTUREEXTPROC glBindTextureEXT;
extern PFNGLDELETETEXTURESEXTPROC glDeleteTexturesEXT;
extern PFNGLGENTEXTURESEXTPROC glGenTexturesEXT;
extern PFNGLISTEXTUREEXTPROC glIsTextureEXT;
extern PFNGLPRIORITIZETEXTURESEXTPROC glPrioritizeTexturesEXT;


/******************************
* Extension: GL_EXT_texture_perturb_normal
******************************/

#define GL_PERTURB_EXT 0x85AE
#define GL_TEXTURE_NORMAL_EXT 0x85AF


typedef void (GLE_FUNCPTR * PFNGLTEXTURENORMALEXTPROC)(GLenum mode);

extern PFNGLTEXTURENORMALEXTPROC glTextureNormalEXT;


/******************************
* Extension: GL_EXT_texture_sRGB
******************************/

#define GL_SRGB_EXT 0x8C40
#define GL_SRGB8_EXT 0x8C41
#define GL_SRGB_ALPHA_EXT 0x8C42
#define GL_SRGB8_ALPHA8_EXT 0x8C43
#define GL_SLUMINANCE_ALPHA_EXT 0x8C44
#define GL_SLUMINANCE8_ALPHA8_EXT 0x8C45
#define GL_SLUMINANCE_EXT 0x8C46
#define GL_SLUMINANCE8_EXT 0x8C47
#define GL_COMPRESSED_SRGB_EXT 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA_EXT 0x8C49
#define GL_COMPRESSED_SLUMINANCE_EXT 0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA_EXT 0x8C4B
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT 0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F


/******************************
* Extension: GL_EXT_texture_shared_exponent
******************************/

#define GL_RGB9_E5_EXT 0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV_EXT 0x8C3E
#define GL_TEXTURE_SHARED_SIZE_EXT 0x8C3F


/******************************
* Extension: GL_EXT_texture_snorm
******************************/

#define GL_RED_SNORM 0x8F90
#define GL_RG_SNORM 0x8F91
#define GL_RGB_SNORM 0x8F92
#define GL_RGBA_SNORM 0x8F93
#define GL_R8_SNORM 0x8F94
#define GL_RG8_SNORM 0x8F95
#define GL_RGB8_SNORM 0x8F96
#define GL_RGBA8_SNORM 0x8F97
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGBA16_SNORM 0x8F9B
#define GL_SIGNED_NORMALIZED 0x8F9C
#define GL_ALPHA_SNORM 0x9010
#define GL_LUMINANCE_SNORM 0x9011
#define GL_LUMINANCE_ALPHA_SNORM 0x9012
#define GL_INTENSITY_SNORM 0x9013
#define GL_ALPHA8_SNORM 0x9014
#define GL_LUMINANCE8_SNORM 0x9015
#define GL_LUMINANCE8_ALPHA8_SNORM 0x9016
#define GL_INTENSITY8_SNORM 0x9017
#define GL_ALPHA16_SNORM 0x9018
#define GL_LUMINANCE16_SNORM 0x9019
#define GL_LUMINANCE16_ALPHA16_SNORM 0x901A
#define GL_INTENSITY16_SNORM 0x901B


/******************************
* Extension: GL_EXT_texture_swizzle
******************************/

#define GL_TEXTURE_SWIZZLE_R_EXT 0x8E42
#define GL_TEXTURE_SWIZZLE_G_EXT 0x8E43
#define GL_TEXTURE_SWIZZLE_B_EXT 0x8E44
#define GL_TEXTURE_SWIZZLE_A_EXT 0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA_EXT 0x8E46


/******************************
* Extension: GL_EXT_timer_query
******************************/

#define GL_TIME_ELAPSED_EXT 0x88BF


typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTI64VEXTPROC)(GLuint id, GLenum pname, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUI64VEXTPROC)(GLuint id, GLenum pname, GLuint64EXT *params);

extern PFNGLGETQUERYOBJECTI64VEXTPROC glGetQueryObjecti64vEXT;
extern PFNGLGETQUERYOBJECTUI64VEXTPROC glGetQueryObjectui64vEXT;


/******************************
* Extension: GL_EXT_transform_feedback
******************************/

#define GL_TRANSFORM_FEEDBACK_BUFFER_EXT 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_EXT 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT 0x8C85
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT 0x8C8F
#define GL_INTERLEAVED_ATTRIBS_EXT 0x8C8C
#define GL_SEPARATE_ATTRIBS_EXT 0x8C8D
#define GL_PRIMITIVES_GENERATED_EXT 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT 0x8C88
#define GL_RASTERIZER_DISCARD_EXT 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT 0x8C8B
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS_EXT 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT 0x8C7F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT 0x8C76


typedef void (GLE_FUNCPTR * PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)(GLenum primitiveMode);
typedef void (GLE_FUNCPTR * PFNGLENDTRANSFORMFEEDBACKEXTPROC)();
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERRANGEEXTPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFEROFFSETEXTPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERBASEEXTPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)(GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode);
typedef void (GLE_FUNCPTR * PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);

extern PFNGLBEGINTRANSFORMFEEDBACKEXTPROC glBeginTransformFeedbackEXT;
extern PFNGLENDTRANSFORMFEEDBACKEXTPROC glEndTransformFeedbackEXT;
extern PFNGLBINDBUFFERRANGEEXTPROC glBindBufferRangeEXT;
extern PFNGLBINDBUFFEROFFSETEXTPROC glBindBufferOffsetEXT;
extern PFNGLBINDBUFFERBASEEXTPROC glBindBufferBaseEXT;
extern PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC glTransformFeedbackVaryingsEXT;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC glGetTransformFeedbackVaryingEXT;


/******************************
* Extension: GL_EXT_vertex_array
******************************/

#define GL_VERTEX_ARRAY_EXT 0x8074
#define GL_NORMAL_ARRAY_EXT 0x8075
#define GL_COLOR_ARRAY_EXT 0x8076
#define GL_INDEX_ARRAY_EXT 0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT 0x8078
#define GL_EDGE_FLAG_ARRAY_EXT 0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT 0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT 0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT 0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT 0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT 0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT 0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT 0x8080
#define GL_COLOR_ARRAY_SIZE_EXT 0x8081
#define GL_COLOR_ARRAY_TYPE_EXT 0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT 0x8083
#define GL_COLOR_ARRAY_COUNT_EXT 0x8084
#define GL_INDEX_ARRAY_TYPE_EXT 0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT 0x8086
#define GL_INDEX_ARRAY_COUNT_EXT 0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT 0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT 0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT 0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT 0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT 0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT 0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT 0x808F
#define GL_COLOR_ARRAY_POINTER_EXT 0x8090
#define GL_INDEX_ARRAY_POINTER_EXT 0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT 0x8093


typedef void (GLE_FUNCPTR * PFNGLARRAYELEMENTEXTPROC)(GLint i);
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSEXTPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTEREXTPROC)(GLsizei stride, GLsizei count, const GLboolean *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETPOINTERVEXTPROC)(GLenum pname, GLvoid* *params);
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTEREXTPROC)(GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTEREXTPROC)(GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);

extern PFNGLARRAYELEMENTEXTPROC glArrayElementEXT;
extern PFNGLCOLORPOINTEREXTPROC glColorPointerEXT;
extern PFNGLDRAWARRAYSEXTPROC glDrawArraysEXT;
extern PFNGLEDGEFLAGPOINTEREXTPROC glEdgeFlagPointerEXT;
extern PFNGLGETPOINTERVEXTPROC glGetPointervEXT;
extern PFNGLINDEXPOINTEREXTPROC glIndexPointerEXT;
extern PFNGLNORMALPOINTEREXTPROC glNormalPointerEXT;
extern PFNGLTEXCOORDPOINTEREXTPROC glTexCoordPointerEXT;
extern PFNGLVERTEXPOINTEREXTPROC glVertexPointerEXT;


/******************************
* Extension: GL_EXT_vertex_array_bgra
******************************/

#define GL_BGRA 0x80E1


/******************************
* Extension: GL_EXT_vertex_attrib_64bit
******************************/

#define GL_DOUBLE 0x140A
#define GL_DOUBLE_VEC2_EXT 0x8FFC
#define GL_DOUBLE_VEC3_EXT 0x8FFD
#define GL_DOUBLE_VEC4_EXT 0x8FFE
#define GL_DOUBLE_MAT2_EXT 0x8F46
#define GL_DOUBLE_MAT3_EXT 0x8F47
#define GL_DOUBLE_MAT4_EXT 0x8F48
#define GL_DOUBLE_MAT2x3_EXT 0x8F49
#define GL_DOUBLE_MAT2x4_EXT 0x8F4A
#define GL_DOUBLE_MAT3x2_EXT 0x8F4B
#define GL_DOUBLE_MAT3x4_EXT 0x8F4C
#define GL_DOUBLE_MAT4x2_EXT 0x8F4D
#define GL_DOUBLE_MAT4x3_EXT 0x8F4E


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1DEXTPROC)(GLuint index, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2DEXTPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3DEXTPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4DEXTPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1DVEXTPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2DVEXTPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3DVEXTPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4DVEXTPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBLPOINTEREXTPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBLDVEXTPROC)(GLuint index, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);

extern PFNGLVERTEXATTRIBL1DEXTPROC glVertexAttribL1dEXT;
extern PFNGLVERTEXATTRIBL2DEXTPROC glVertexAttribL2dEXT;
extern PFNGLVERTEXATTRIBL3DEXTPROC glVertexAttribL3dEXT;
extern PFNGLVERTEXATTRIBL4DEXTPROC glVertexAttribL4dEXT;
extern PFNGLVERTEXATTRIBL1DVEXTPROC glVertexAttribL1dvEXT;
extern PFNGLVERTEXATTRIBL2DVEXTPROC glVertexAttribL2dvEXT;
extern PFNGLVERTEXATTRIBL3DVEXTPROC glVertexAttribL3dvEXT;
extern PFNGLVERTEXATTRIBL4DVEXTPROC glVertexAttribL4dvEXT;
extern PFNGLVERTEXATTRIBLPOINTEREXTPROC glVertexAttribLPointerEXT;
extern PFNGLGETVERTEXATTRIBLDVEXTPROC glGetVertexAttribLdvEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC glVertexArrayVertexAttribLOffsetEXT;


/******************************
* Extension: GL_EXT_vertex_shader
******************************/

#define GL_VERTEX_SHADER_EXT 0x8780
#define GL_VERTEX_SHADER_BINDING_EXT 0x8781
#define GL_OP_INDEX_EXT 0x8782
#define GL_OP_NEGATE_EXT 0x8783
#define GL_OP_DOT3_EXT 0x8784
#define GL_OP_DOT4_EXT 0x8785
#define GL_OP_MUL_EXT 0x8786
#define GL_OP_ADD_EXT 0x8787
#define GL_OP_MADD_EXT 0x8788
#define GL_OP_FRAC_EXT 0x8789
#define GL_OP_MAX_EXT 0x878A
#define GL_OP_MIN_EXT 0x878B
#define GL_OP_SET_GE_EXT 0x878C
#define GL_OP_SET_LT_EXT 0x878D
#define GL_OP_CLAMP_EXT 0x878E
#define GL_OP_FLOOR_EXT 0x878F
#define GL_OP_ROUND_EXT 0x8790
#define GL_OP_EXP_BASE_2_EXT 0x8791
#define GL_OP_LOG_BASE_2_EXT 0x8792
#define GL_OP_POWER_EXT 0x8793
#define GL_OP_RECIP_EXT 0x8794
#define GL_OP_RECIP_SQRT_EXT 0x8795
#define GL_OP_SUB_EXT 0x8796
#define GL_OP_CROSS_PRODUCT_EXT 0x8797
#define GL_OP_MULTIPLY_MATRIX_EXT 0x8798
#define GL_OP_MOV_EXT 0x8799
#define GL_OUTPUT_VERTEX_EXT 0x879A
#define GL_OUTPUT_COLOR0_EXT 0x879B
#define GL_OUTPUT_COLOR1_EXT 0x879C
#define GL_OUTPUT_TEXTURE_COORD0_EXT 0x879D
#define GL_OUTPUT_TEXTURE_COORD1_EXT 0x879E
#define GL_OUTPUT_TEXTURE_COORD2_EXT 0x879F
#define GL_OUTPUT_TEXTURE_COORD3_EXT 0x87A0
#define GL_OUTPUT_TEXTURE_COORD4_EXT 0x87A1
#define GL_OUTPUT_TEXTURE_COORD5_EXT 0x87A2
#define GL_OUTPUT_TEXTURE_COORD6_EXT 0x87A3
#define GL_OUTPUT_TEXTURE_COORD7_EXT 0x87A4
#define GL_OUTPUT_TEXTURE_COORD8_EXT 0x87A5
#define GL_OUTPUT_TEXTURE_COORD9_EXT 0x87A6
#define GL_OUTPUT_TEXTURE_COORD10_EXT 0x87A7
#define GL_OUTPUT_TEXTURE_COORD11_EXT 0x87A8
#define GL_OUTPUT_TEXTURE_COORD12_EXT 0x87A9
#define GL_OUTPUT_TEXTURE_COORD13_EXT 0x87AA
#define GL_OUTPUT_TEXTURE_COORD14_EXT 0x87AB
#define GL_OUTPUT_TEXTURE_COORD15_EXT 0x87AC
#define GL_OUTPUT_TEXTURE_COORD16_EXT 0x87AD
#define GL_OUTPUT_TEXTURE_COORD17_EXT 0x87AE
#define GL_OUTPUT_TEXTURE_COORD18_EXT 0x87AF
#define GL_OUTPUT_TEXTURE_COORD19_EXT 0x87B0
#define GL_OUTPUT_TEXTURE_COORD20_EXT 0x87B1
#define GL_OUTPUT_TEXTURE_COORD21_EXT 0x87B2
#define GL_OUTPUT_TEXTURE_COORD22_EXT 0x87B3
#define GL_OUTPUT_TEXTURE_COORD23_EXT 0x87B4
#define GL_OUTPUT_TEXTURE_COORD24_EXT 0x87B5
#define GL_OUTPUT_TEXTURE_COORD25_EXT 0x87B6
#define GL_OUTPUT_TEXTURE_COORD26_EXT 0x87B7
#define GL_OUTPUT_TEXTURE_COORD27_EXT 0x87B8
#define GL_OUTPUT_TEXTURE_COORD28_EXT 0x87B9
#define GL_OUTPUT_TEXTURE_COORD29_EXT 0x87BA
#define GL_OUTPUT_TEXTURE_COORD30_EXT 0x87BB
#define GL_OUTPUT_TEXTURE_COORD31_EXT 0x87BC
#define GL_OUTPUT_FOG_EXT 0x87BD
#define GL_SCALAR_EXT 0x87BE
#define GL_VECTOR_EXT 0x87BF
#define GL_MATRIX_EXT 0x87C0
#define GL_VARIANT_EXT 0x87C1
#define GL_INVARIANT_EXT 0x87C2
#define GL_LOCAL_CONSTANT_EXT 0x87C3
#define GL_LOCAL_EXT 0x87C4
#define GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT 0x87C5
#define GL_MAX_VERTEX_SHADER_VARIANTS_EXT 0x87C6
#define GL_MAX_VERTEX_SHADER_INVARIANTS_EXT 0x87C7
#define GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT 0x87C8
#define GL_MAX_VERTEX_SHADER_LOCALS_EXT 0x87C9
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT 0x87CA
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT 0x87CB
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT 0x87CC
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT 0x87CD
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT 0x87CE
#define GL_VERTEX_SHADER_INSTRUCTIONS_EXT 0x87CF
#define GL_VERTEX_SHADER_VARIANTS_EXT 0x87D0
#define GL_VERTEX_SHADER_INVARIANTS_EXT 0x87D1
#define GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT 0x87D2
#define GL_VERTEX_SHADER_LOCALS_EXT 0x87D3
#define GL_VERTEX_SHADER_OPTIMIZED_EXT 0x87D4
#define GL_X_EXT 0x87D5
#define GL_Y_EXT 0x87D6
#define GL_Z_EXT 0x87D7
#define GL_W_EXT 0x87D8
#define GL_NEGATIVE_X_EXT 0x87D9
#define GL_NEGATIVE_Y_EXT 0x87DA
#define GL_NEGATIVE_Z_EXT 0x87DB
#define GL_NEGATIVE_W_EXT 0x87DC
#define GL_ZERO_EXT 0x87DD
#define GL_ONE_EXT 0x87DE
#define GL_NEGATIVE_ONE_EXT 0x87DF
#define GL_NORMALIZED_RANGE_EXT 0x87E0
#define GL_FULL_RANGE_EXT 0x87E1
#define GL_CURRENT_VERTEX_EXT 0x87E2
#define GL_MVP_MATRIX_EXT 0x87E3
#define GL_VARIANT_VALUE_EXT 0x87E4
#define GL_VARIANT_DATATYPE_EXT 0x87E5
#define GL_VARIANT_ARRAY_STRIDE_EXT 0x87E6
#define GL_VARIANT_ARRAY_TYPE_EXT 0x87E7
#define GL_VARIANT_ARRAY_EXT 0x87E8
#define GL_VARIANT_ARRAY_POINTER_EXT 0x87E9
#define GL_INVARIANT_VALUE_EXT 0x87EA
#define GL_INVARIANT_DATATYPE_EXT 0x87EB
#define GL_LOCAL_CONSTANT_VALUE_EXT 0x87EC
#define GL_LOCAL_CONSTANT_DATATYPE_EXT 0x87ED


typedef void (GLE_FUNCPTR * PFNGLBEGINVERTEXSHADEREXTPROC)();
typedef void (GLE_FUNCPTR * PFNGLENDVERTEXSHADEREXTPROC)();
typedef void (GLE_FUNCPTR * PFNGLBINDVERTEXSHADEREXTPROC)(GLuint id);
typedef GLuint (GLE_FUNCPTR * PFNGLGENVERTEXSHADERSEXTPROC)(GLuint range);
typedef void (GLE_FUNCPTR * PFNGLDELETEVERTEXSHADEREXTPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLSHADEROP1EXTPROC)(GLenum op, GLuint res, GLuint arg1);
typedef void (GLE_FUNCPTR * PFNGLSHADEROP2EXTPROC)(GLenum op, GLuint res, GLuint arg1, GLuint arg2);
typedef void (GLE_FUNCPTR * PFNGLSHADEROP3EXTPROC)(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
typedef void (GLE_FUNCPTR * PFNGLSWIZZLEEXTPROC)(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (GLE_FUNCPTR * PFNGLWRITEMASKEXTPROC)(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (GLE_FUNCPTR * PFNGLINSERTCOMPONENTEXTPROC)(GLuint res, GLuint src, GLuint num);
typedef void (GLE_FUNCPTR * PFNGLEXTRACTCOMPONENTEXTPROC)(GLuint res, GLuint src, GLuint num);
typedef GLuint (GLE_FUNCPTR * PFNGLGENSYMBOLSEXTPROC)(GLenum datatype, GLenum storagetype, GLenum range, GLuint components);
typedef void (GLE_FUNCPTR * PFNGLSETINVARIANTEXTPROC)(GLuint id, GLenum type, const GLvoid *addr);
typedef void (GLE_FUNCPTR * PFNGLSETLOCALCONSTANTEXTPROC)(GLuint id, GLenum type, const GLvoid *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTBVEXTPROC)(GLuint id, const GLbyte *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTSVEXTPROC)(GLuint id, const GLshort *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTIVEXTPROC)(GLuint id, const GLint *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTFVEXTPROC)(GLuint id, const GLfloat *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTDVEXTPROC)(GLuint id, const GLdouble *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTUBVEXTPROC)(GLuint id, const GLubyte *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTUSVEXTPROC)(GLuint id, const GLushort *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTUIVEXTPROC)(GLuint id, const GLuint *addr);
typedef void (GLE_FUNCPTR * PFNGLVARIANTPOINTEREXTPROC)(GLuint id, GLenum type, GLuint stride, const GLvoid *addr);
typedef void (GLE_FUNCPTR * PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)(GLuint id);
typedef GLuint (GLE_FUNCPTR * PFNGLBINDLIGHTPARAMETEREXTPROC)(GLenum light, GLenum value);
typedef GLuint (GLE_FUNCPTR * PFNGLBINDMATERIALPARAMETEREXTPROC)(GLenum face, GLenum value);
typedef GLuint (GLE_FUNCPTR * PFNGLBINDTEXGENPARAMETEREXTPROC)(GLenum unit, GLenum coord, GLenum value);
typedef GLuint (GLE_FUNCPTR * PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)(GLenum unit, GLenum value);
typedef GLuint (GLE_FUNCPTR * PFNGLBINDPARAMETEREXTPROC)(GLenum value);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVARIANTENABLEDEXTPROC)(GLuint id, GLenum cap);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTBOOLEANVEXTPROC)(GLuint id, GLenum value, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTINTEGERVEXTPROC)(GLuint id, GLenum value, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTFLOATVEXTPROC)(GLuint id, GLenum value, GLfloat *data);
typedef void (GLE_FUNCPTR * PFNGLGETVARIANTPOINTERVEXTPROC)(GLuint id, GLenum value, GLvoid* *data);
typedef void (GLE_FUNCPTR * PFNGLGETINVARIANTBOOLEANVEXTPROC)(GLuint id, GLenum value, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETINVARIANTINTEGERVEXTPROC)(GLuint id, GLenum value, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLGETINVARIANTFLOATVEXTPROC)(GLuint id, GLenum value, GLfloat *data);
typedef void (GLE_FUNCPTR * PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)(GLuint id, GLenum value, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)(GLuint id, GLenum value, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLGETLOCALCONSTANTFLOATVEXTPROC)(GLuint id, GLenum value, GLfloat *data);

extern PFNGLBEGINVERTEXSHADEREXTPROC glBeginVertexShaderEXT;
extern PFNGLENDVERTEXSHADEREXTPROC glEndVertexShaderEXT;
extern PFNGLBINDVERTEXSHADEREXTPROC glBindVertexShaderEXT;
extern PFNGLGENVERTEXSHADERSEXTPROC glGenVertexShadersEXT;
extern PFNGLDELETEVERTEXSHADEREXTPROC glDeleteVertexShaderEXT;
extern PFNGLSHADEROP1EXTPROC glShaderOp1EXT;
extern PFNGLSHADEROP2EXTPROC glShaderOp2EXT;
extern PFNGLSHADEROP3EXTPROC glShaderOp3EXT;
extern PFNGLSWIZZLEEXTPROC glSwizzleEXT;
extern PFNGLWRITEMASKEXTPROC glWriteMaskEXT;
extern PFNGLINSERTCOMPONENTEXTPROC glInsertComponentEXT;
extern PFNGLEXTRACTCOMPONENTEXTPROC glExtractComponentEXT;
extern PFNGLGENSYMBOLSEXTPROC glGenSymbolsEXT;
extern PFNGLSETINVARIANTEXTPROC glSetInvariantEXT;
extern PFNGLSETLOCALCONSTANTEXTPROC glSetLocalConstantEXT;
extern PFNGLVARIANTBVEXTPROC glVariantbvEXT;
extern PFNGLVARIANTSVEXTPROC glVariantsvEXT;
extern PFNGLVARIANTIVEXTPROC glVariantivEXT;
extern PFNGLVARIANTFVEXTPROC glVariantfvEXT;
extern PFNGLVARIANTDVEXTPROC glVariantdvEXT;
extern PFNGLVARIANTUBVEXTPROC glVariantubvEXT;
extern PFNGLVARIANTUSVEXTPROC glVariantusvEXT;
extern PFNGLVARIANTUIVEXTPROC glVariantuivEXT;
extern PFNGLVARIANTPOINTEREXTPROC glVariantPointerEXT;
extern PFNGLENABLEVARIANTCLIENTSTATEEXTPROC glEnableVariantClientStateEXT;
extern PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC glDisableVariantClientStateEXT;
extern PFNGLBINDLIGHTPARAMETEREXTPROC glBindLightParameterEXT;
extern PFNGLBINDMATERIALPARAMETEREXTPROC glBindMaterialParameterEXT;
extern PFNGLBINDTEXGENPARAMETEREXTPROC glBindTexGenParameterEXT;
extern PFNGLBINDTEXTUREUNITPARAMETEREXTPROC glBindTextureUnitParameterEXT;
extern PFNGLBINDPARAMETEREXTPROC glBindParameterEXT;
extern PFNGLISVARIANTENABLEDEXTPROC glIsVariantEnabledEXT;
extern PFNGLGETVARIANTBOOLEANVEXTPROC glGetVariantBooleanvEXT;
extern PFNGLGETVARIANTINTEGERVEXTPROC glGetVariantIntegervEXT;
extern PFNGLGETVARIANTFLOATVEXTPROC glGetVariantFloatvEXT;
extern PFNGLGETVARIANTPOINTERVEXTPROC glGetVariantPointervEXT;
extern PFNGLGETINVARIANTBOOLEANVEXTPROC glGetInvariantBooleanvEXT;
extern PFNGLGETINVARIANTINTEGERVEXTPROC glGetInvariantIntegervEXT;
extern PFNGLGETINVARIANTFLOATVEXTPROC glGetInvariantFloatvEXT;
extern PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC glGetLocalConstantBooleanvEXT;
extern PFNGLGETLOCALCONSTANTINTEGERVEXTPROC glGetLocalConstantIntegervEXT;
extern PFNGLGETLOCALCONSTANTFLOATVEXTPROC glGetLocalConstantFloatvEXT;


/******************************
* Extension: GL_EXT_vertex_weighting
******************************/

#define GL_MODELVIEW0_STACK_DEPTH_EXT 0x0BA3 /* GL_MODELVIEW_STACK_DEPTH */
#define GL_MODELVIEW1_STACK_DEPTH_EXT 0x8502
#define GL_MODELVIEW0_MATRIX_EXT 0x0BA6 /* GL_MODELVIEW_MATRIX */
#define GL_MODELVIEW1_MATRIX_EXT 0x8506
#define GL_VERTEX_WEIGHTING_EXT 0x8509
#define GL_MODELVIEW0_EXT 0x1700 /* GL_MODELVIEW */
#define GL_MODELVIEW1_EXT 0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT 0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT 0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT 0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT 0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT 0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT 0x8510


typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTFEXTPROC)(GLfloat weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTFVEXTPROC)(const GLfloat *weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTPOINTEREXTPROC)(GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

extern PFNGLVERTEXWEIGHTFEXTPROC glVertexWeightfEXT;
extern PFNGLVERTEXWEIGHTFVEXTPROC glVertexWeightfvEXT;
extern PFNGLVERTEXWEIGHTPOINTEREXTPROC glVertexWeightPointerEXT;


/******************************
* Extension: GL_FfdMaskSGIX
******************************/

#define GL_TEXTURE_DEFORMATION_BIT_SGIX 0x00000001
#define GL_GEOMETRY_DEFORMATION_BIT_SGIX 0x00000002


/******************************
* Extension: GL_GREMEDY_frame_terminator
******************************/

typedef void (GLE_FUNCPTR * PFNGLFRAMETERMINATORGREMEDYPROC)();

extern PFNGLFRAMETERMINATORGREMEDYPROC glFrameTerminatorGREMEDY;


/******************************
* Extension: GL_GREMEDY_string_marker
******************************/

typedef void (GLE_FUNCPTR * PFNGLSTRINGMARKERGREMEDYPROC)(GLsizei len, const GLvoid *string);

extern PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY;


/******************************
* Extension: GL_HP_convolution_border_modes
******************************/

#define GL_IGNORE_BORDER_HP 0x8150
#define GL_CONSTANT_BORDER_HP 0x8151
#define GL_REPLICATE_BORDER_HP 0x8153
#define GL_CONVOLUTION_BORDER_COLOR_HP 0x8154


/******************************
* Extension: GL_HP_image_transform
******************************/

#define GL_IMAGE_SCALE_X_HP 0x8155
#define GL_IMAGE_SCALE_Y_HP 0x8156
#define GL_IMAGE_TRANSLATE_X_HP 0x8157
#define GL_IMAGE_TRANSLATE_Y_HP 0x8158
#define GL_IMAGE_ROTATE_ANGLE_HP 0x8159
#define GL_IMAGE_ROTATE_ORIGIN_X_HP 0x815A
#define GL_IMAGE_ROTATE_ORIGIN_Y_HP 0x815B
#define GL_IMAGE_MAG_FILTER_HP 0x815C
#define GL_IMAGE_MIN_FILTER_HP 0x815D
#define GL_IMAGE_CUBIC_WEIGHT_HP 0x815E
#define GL_CUBIC_HP 0x815F
#define GL_AVERAGE_HP 0x8160
#define GL_IMAGE_TRANSFORM_2D_HP 0x8161
#define GL_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP 0x8162
#define GL_PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP 0x8163


typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERIHPPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERFHPPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum target, GLenum pname, GLfloat *params);

extern PFNGLIMAGETRANSFORMPARAMETERIHPPROC glImageTransformParameteriHP;
extern PFNGLIMAGETRANSFORMPARAMETERFHPPROC glImageTransformParameterfHP;
extern PFNGLIMAGETRANSFORMPARAMETERIVHPPROC glImageTransformParameterivHP;
extern PFNGLIMAGETRANSFORMPARAMETERFVHPPROC glImageTransformParameterfvHP;
extern PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC glGetImageTransformParameterivHP;
extern PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC glGetImageTransformParameterfvHP;


/******************************
* Extension: GL_HP_occlusion_test
******************************/

#define GL_OCCLUSION_TEST_HP 0x8165
#define GL_OCCLUSION_TEST_RESULT_HP 0x8166


/******************************
* Extension: GL_HP_texture_lighting
******************************/

#define GL_TEXTURE_LIGHTING_MODE_HP 0x8167
#define GL_TEXTURE_POST_SPECULAR_HP 0x8168
#define GL_TEXTURE_PRE_SPECULAR_HP 0x8169


/******************************
* Extension: GL_IBM_cull_vertex
******************************/

#define GL_CULL_VERTEX_IBM 103050


/******************************
* Extension: GL_IBM_multimode_draw_arrays
******************************/

typedef void (GLE_FUNCPTR * PFNGLMULTIMODEDRAWARRAYSIBMPROC)(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride);
typedef void (GLE_FUNCPTR * PFNGLMULTIMODEDRAWELEMENTSIBMPROC)(const GLenum *mode, const GLsizei *count, GLenum type, const GLvoid* const *indices, GLsizei primcount, GLint modestride);

extern PFNGLMULTIMODEDRAWARRAYSIBMPROC glMultiModeDrawArraysIBM;
extern PFNGLMULTIMODEDRAWELEMENTSIBMPROC glMultiModeDrawElementsIBM;


/******************************
* Extension: GL_IBM_rasterpos_clip
******************************/

#define GL_RASTER_POSITION_UNCLIPPED_IBM 0x19262


/******************************
* Extension: GL_IBM_texture_mirrored_repeat
******************************/

#define GL_MIRRORED_REPEAT_IBM 0x8370


/******************************
* Extension: GL_IBM_vertex_array_lists
******************************/

#define GL_VERTEX_ARRAY_LIST_IBM 103070
#define GL_NORMAL_ARRAY_LIST_IBM 103071
#define GL_COLOR_ARRAY_LIST_IBM 103072
#define GL_INDEX_ARRAY_LIST_IBM 103073
#define GL_TEXTURE_COORD_ARRAY_LIST_IBM 103074
#define GL_EDGE_FLAG_ARRAY_LIST_IBM 103075
#define GL_FOG_COORDINATE_ARRAY_LIST_IBM 103076
#define GL_SECONDARY_COLOR_ARRAY_LIST_IBM 103077
#define GL_VERTEX_ARRAY_LIST_STRIDE_IBM 103080
#define GL_NORMAL_ARRAY_LIST_STRIDE_IBM 103081
#define GL_COLOR_ARRAY_LIST_STRIDE_IBM 103082
#define GL_INDEX_ARRAY_LIST_STRIDE_IBM 103083
#define GL_TEXTURE_COORD_ARRAY_LIST_STRIDE_IBM 103084
#define GL_EDGE_FLAG_ARRAY_LIST_STRIDE_IBM 103085
#define GL_FOG_COORDINATE_ARRAY_LIST_STRIDE_IBM 103086
#define GL_SECONDARY_COLOR_ARRAY_LIST_STRIDE_IBM 103087


typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTERLISTIBMPROC)(GLint stride, const GLboolean* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);

extern PFNGLCOLORPOINTERLISTIBMPROC glColorPointerListIBM;
extern PFNGLSECONDARYCOLORPOINTERLISTIBMPROC glSecondaryColorPointerListIBM;
extern PFNGLEDGEFLAGPOINTERLISTIBMPROC glEdgeFlagPointerListIBM;
extern PFNGLFOGCOORDPOINTERLISTIBMPROC glFogCoordPointerListIBM;
extern PFNGLINDEXPOINTERLISTIBMPROC glIndexPointerListIBM;
extern PFNGLNORMALPOINTERLISTIBMPROC glNormalPointerListIBM;
extern PFNGLTEXCOORDPOINTERLISTIBMPROC glTexCoordPointerListIBM;
extern PFNGLVERTEXPOINTERLISTIBMPROC glVertexPointerListIBM;


/******************************
* Extension: GL_INGR_color_clamp
******************************/

#define GL_RED_MIN_CLAMP_INGR 0x8560
#define GL_GREEN_MIN_CLAMP_INGR 0x8561
#define GL_BLUE_MIN_CLAMP_INGR 0x8562
#define GL_ALPHA_MIN_CLAMP_INGR 0x8563
#define GL_RED_MAX_CLAMP_INGR 0x8564
#define GL_GREEN_MAX_CLAMP_INGR 0x8565
#define GL_BLUE_MAX_CLAMP_INGR 0x8566
#define GL_ALPHA_MAX_CLAMP_INGR 0x8567


/******************************
* Extension: GL_INGR_interlace_read
******************************/

#define GL_INTERLACE_READ_INGR 0x8568


/******************************
* Extension: GL_INGR_palette_buffer
******************************/

/******************************
* Extension: GL_INTEL_parallel_arrays
******************************/

#define GL_PARALLEL_ARRAYS_INTEL 0x83F4
#define GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL 0x83F5
#define GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL 0x83F6
#define GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL 0x83F7
#define GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL 0x83F8


typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERVINTELPROC)(GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);

extern PFNGLVERTEXPOINTERVINTELPROC glVertexPointervINTEL;
extern PFNGLNORMALPOINTERVINTELPROC glNormalPointervINTEL;
extern PFNGLCOLORPOINTERVINTELPROC glColorPointervINTEL;
extern PFNGLTEXCOORDPOINTERVINTELPROC glTexCoordPointervINTEL;


/******************************
* Extension: GL_INTEL_texture_scissor
******************************/

/******************************
* Extension: GL_MESAX_texture_stack
******************************/

#define GL_TEXTURE_1D_STACK_MESAX 0x8759
#define GL_TEXTURE_2D_STACK_MESAX 0x875A
#define GL_PROXY_TEXTURE_1D_STACK_MESAX 0x875B
#define GL_PROXY_TEXTURE_2D_STACK_MESAX 0x875C
#define GL_TEXTURE_1D_STACK_BINDING_MESAX 0x875D
#define GL_TEXTURE_2D_STACK_BINDING_MESAX 0x875E


/******************************
* Extension: GL_MESA_pack_invert
******************************/

#define GL_PACK_INVERT_MESA 0x8758


/******************************
* Extension: GL_MESA_resize_buffers
******************************/

typedef void (GLE_FUNCPTR * PFNGLRESIZEBUFFERSMESAPROC)();

extern PFNGLRESIZEBUFFERSMESAPROC glResizeBuffersMESA;


/******************************
* Extension: GL_MESA_window_pos
******************************/

typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DMESAPROC)(GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DVMESAPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FMESAPROC)(GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FVMESAPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IMESAPROC)(GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IVMESAPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SMESAPROC)(GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SVMESAPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DMESAPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DVMESAPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FMESAPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FVMESAPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IMESAPROC)(GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IVMESAPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SMESAPROC)(GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SVMESAPROC)(const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4DMESAPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4DVMESAPROC)(const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4FMESAPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4FVMESAPROC)(const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4IMESAPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4IVMESAPROC)(const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4SMESAPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS4SVMESAPROC)(const GLshort *v);

extern PFNGLWINDOWPOS2DMESAPROC glWindowPos2dMESA;
extern PFNGLWINDOWPOS2DVMESAPROC glWindowPos2dvMESA;
extern PFNGLWINDOWPOS2FMESAPROC glWindowPos2fMESA;
extern PFNGLWINDOWPOS2FVMESAPROC glWindowPos2fvMESA;
extern PFNGLWINDOWPOS2IMESAPROC glWindowPos2iMESA;
extern PFNGLWINDOWPOS2IVMESAPROC glWindowPos2ivMESA;
extern PFNGLWINDOWPOS2SMESAPROC glWindowPos2sMESA;
extern PFNGLWINDOWPOS2SVMESAPROC glWindowPos2svMESA;
extern PFNGLWINDOWPOS3DMESAPROC glWindowPos3dMESA;
extern PFNGLWINDOWPOS3DVMESAPROC glWindowPos3dvMESA;
extern PFNGLWINDOWPOS3FMESAPROC glWindowPos3fMESA;
extern PFNGLWINDOWPOS3FVMESAPROC glWindowPos3fvMESA;
extern PFNGLWINDOWPOS3IMESAPROC glWindowPos3iMESA;
extern PFNGLWINDOWPOS3IVMESAPROC glWindowPos3ivMESA;
extern PFNGLWINDOWPOS3SMESAPROC glWindowPos3sMESA;
extern PFNGLWINDOWPOS3SVMESAPROC glWindowPos3svMESA;
extern PFNGLWINDOWPOS4DMESAPROC glWindowPos4dMESA;
extern PFNGLWINDOWPOS4DVMESAPROC glWindowPos4dvMESA;
extern PFNGLWINDOWPOS4FMESAPROC glWindowPos4fMESA;
extern PFNGLWINDOWPOS4FVMESAPROC glWindowPos4fvMESA;
extern PFNGLWINDOWPOS4IMESAPROC glWindowPos4iMESA;
extern PFNGLWINDOWPOS4IVMESAPROC glWindowPos4ivMESA;
extern PFNGLWINDOWPOS4SMESAPROC glWindowPos4sMESA;
extern PFNGLWINDOWPOS4SVMESAPROC glWindowPos4svMESA;


/******************************
* Extension: GL_MESA_ycbcr_texture
******************************/

#define GL_UNSIGNED_SHORT_8_8_MESA 0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_MESA 0x85BB
#define GL_YCBCR_MESA 0x8757


/******************************
* Extension: GL_NV_blend_square
******************************/

/******************************
* Extension: GL_NV_conditional_render
******************************/

#define GL_QUERY_WAIT_NV 0x8E13
#define GL_QUERY_NO_WAIT_NV 0x8E14
#define GL_QUERY_BY_REGION_WAIT_NV 0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT_NV 0x8E16


typedef void (GLE_FUNCPTR * PFNGLBEGINCONDITIONALRENDERNVPROC)(GLuint id, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLENDCONDITIONALRENDERNVPROC)();

extern PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV;
extern PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV;


/******************************
* Extension: GL_NV_copy_depth_to_color
******************************/

#define GL_DEPTH_STENCIL_TO_RGBA_NV 0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV 0x886F


/******************************
* Extension: GL_NV_copy_image
******************************/

typedef void (GLE_FUNCPTR * PFNGLCOPYIMAGESUBDATANVPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

extern PFNGLCOPYIMAGESUBDATANVPROC glCopyImageSubDataNV;


/******************************
* Extension: GL_NV_depth_buffer_float
******************************/

#define GL_DEPTH_COMPONENT32F_NV 0x8DAB
#define GL_DEPTH32F_STENCIL8_NV 0x8DAC
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV 0x8DAD
#define GL_DEPTH_BUFFER_FLOAT_MODE_NV 0x8DAF


typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEDNVPROC)(GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHDNVPROC)(GLdouble depth);
typedef void (GLE_FUNCPTR * PFNGLDEPTHBOUNDSDNVPROC)(GLdouble zmin, GLdouble zmax);

extern PFNGLDEPTHRANGEDNVPROC glDepthRangedNV;
extern PFNGLCLEARDEPTHDNVPROC glClearDepthdNV;
extern PFNGLDEPTHBOUNDSDNVPROC glDepthBoundsdNV;


/******************************
* Extension: GL_NV_depth_clamp
******************************/

#define GL_DEPTH_CLAMP_NV 0x864F


/******************************
* Extension: GL_NV_evaluators
******************************/

#define GL_EVAL_2D_NV 0x86C0
#define GL_EVAL_TRIANGULAR_2D_NV 0x86C1
#define GL_MAP_TESSELLATION_NV 0x86C2
#define GL_MAP_ATTRIB_U_ORDER_NV 0x86C3
#define GL_MAP_ATTRIB_V_ORDER_NV 0x86C4
#define GL_EVAL_FRACTIONAL_TESSELLATION_NV 0x86C5
#define GL_EVAL_VERTEX_ATTRIB0_NV 0x86C6
#define GL_EVAL_VERTEX_ATTRIB1_NV 0x86C7
#define GL_EVAL_VERTEX_ATTRIB2_NV 0x86C8
#define GL_EVAL_VERTEX_ATTRIB3_NV 0x86C9
#define GL_EVAL_VERTEX_ATTRIB4_NV 0x86CA
#define GL_EVAL_VERTEX_ATTRIB5_NV 0x86CB
#define GL_EVAL_VERTEX_ATTRIB6_NV 0x86CC
#define GL_EVAL_VERTEX_ATTRIB7_NV 0x86CD
#define GL_EVAL_VERTEX_ATTRIB8_NV 0x86CE
#define GL_EVAL_VERTEX_ATTRIB9_NV 0x86CF
#define GL_EVAL_VERTEX_ATTRIB10_NV 0x86D0
#define GL_EVAL_VERTEX_ATTRIB11_NV 0x86D1
#define GL_EVAL_VERTEX_ATTRIB12_NV 0x86D2
#define GL_EVAL_VERTEX_ATTRIB13_NV 0x86D3
#define GL_EVAL_VERTEX_ATTRIB14_NV 0x86D4
#define GL_EVAL_VERTEX_ATTRIB15_NV 0x86D5
#define GL_MAX_MAP_TESSELLATION_NV 0x86D6
#define GL_MAX_RATIONAL_EVAL_ORDER_NV 0x86D7


typedef void (GLE_FUNCPTR * PFNGLMAPCONTROLPOINTSNVPROC)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
typedef void (GLE_FUNCPTR * PFNGLMAPPARAMETERIVNVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMAPPARAMETERFVNVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPCONTROLPOINTSNVPROC)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
typedef void (GLE_FUNCPTR * PFNGLGETMAPPARAMETERIVNVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPPARAMETERFVNVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPATTRIBPARAMETERIVNVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPATTRIBPARAMETERFVNVPROC)(GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLEVALMAPSNVPROC)(GLenum target, GLenum mode);

extern PFNGLMAPCONTROLPOINTSNVPROC glMapControlPointsNV;
extern PFNGLMAPPARAMETERIVNVPROC glMapParameterivNV;
extern PFNGLMAPPARAMETERFVNVPROC glMapParameterfvNV;
extern PFNGLGETMAPCONTROLPOINTSNVPROC glGetMapControlPointsNV;
extern PFNGLGETMAPPARAMETERIVNVPROC glGetMapParameterivNV;
extern PFNGLGETMAPPARAMETERFVNVPROC glGetMapParameterfvNV;
extern PFNGLGETMAPATTRIBPARAMETERIVNVPROC glGetMapAttribParameterivNV;
extern PFNGLGETMAPATTRIBPARAMETERFVNVPROC glGetMapAttribParameterfvNV;
extern PFNGLEVALMAPSNVPROC glEvalMapsNV;


/******************************
* Extension: GL_NV_explicit_multisample
******************************/

#define GL_SAMPLE_POSITION_NV 0x8E50
#define GL_SAMPLE_MASK_NV 0x8E51
#define GL_SAMPLE_MASK_VALUE_NV 0x8E52
#define GL_TEXTURE_BINDING_RENDERBUFFER_NV 0x8E53
#define GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV 0x8E54
#define GL_TEXTURE_RENDERBUFFER_NV 0x8E55
#define GL_SAMPLER_RENDERBUFFER_NV 0x8E56
#define GL_INT_SAMPLER_RENDERBUFFER_NV 0x8E57
#define GL_UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV 0x8E58
#define GL_MAX_SAMPLE_MASK_WORDS_NV 0x8E59


typedef void (GLE_FUNCPTR * PFNGLGETMULTISAMPLEFVNVPROC)(GLenum pname, GLuint index, GLfloat *val);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKINDEXEDNVPROC)(GLuint index, GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLTEXRENDERBUFFERNVPROC)(GLenum target, GLuint renderbuffer);

extern PFNGLGETMULTISAMPLEFVNVPROC glGetMultisamplefvNV;
extern PFNGLSAMPLEMASKINDEXEDNVPROC glSampleMaskIndexedNV;
extern PFNGLTEXRENDERBUFFERNVPROC glTexRenderbufferNV;


/******************************
* Extension: GL_NV_fence
******************************/

#define GL_ALL_COMPLETED_NV 0x84F2
#define GL_FENCE_STATUS_NV 0x84F3
#define GL_FENCE_CONDITION_NV 0x84F4


typedef void (GLE_FUNCPTR * PFNGLDELETEFENCESNVPROC)(GLsizei n, const GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLGENFENCESNVPROC)(GLsizei n, GLuint *fences);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFENCENVPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTFENCENVPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLGETFENCEIVNVPROC)(GLuint fence, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFINISHFENCENVPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLSETFENCENVPROC)(GLuint fence, GLenum condition);

extern PFNGLDELETEFENCESNVPROC glDeleteFencesNV;
extern PFNGLGENFENCESNVPROC glGenFencesNV;
extern PFNGLISFENCENVPROC glIsFenceNV;
extern PFNGLTESTFENCENVPROC glTestFenceNV;
extern PFNGLGETFENCEIVNVPROC glGetFenceivNV;
extern PFNGLFINISHFENCENVPROC glFinishFenceNV;
extern PFNGLSETFENCENVPROC glSetFenceNV;


/******************************
* Extension: GL_NV_float_buffer
******************************/

#define GL_FLOAT_R_NV 0x8880
#define GL_FLOAT_RG_NV 0x8881
#define GL_FLOAT_RGB_NV 0x8882
#define GL_FLOAT_RGBA_NV 0x8883
#define GL_FLOAT_R16_NV 0x8884
#define GL_FLOAT_R32_NV 0x8885
#define GL_FLOAT_RG16_NV 0x8886
#define GL_FLOAT_RG32_NV 0x8887
#define GL_FLOAT_RGB16_NV 0x8888
#define GL_FLOAT_RGB32_NV 0x8889
#define GL_FLOAT_RGBA16_NV 0x888A
#define GL_FLOAT_RGBA32_NV 0x888B
#define GL_TEXTURE_FLOAT_COMPONENTS_NV 0x888C
#define GL_FLOAT_CLEAR_COLOR_VALUE_NV 0x888D
#define GL_FLOAT_RGBA_MODE_NV 0x888E


/******************************
* Extension: GL_NV_fog_distance
******************************/

#define GL_EYE_PLANE 0x2502
#define GL_FOG_DISTANCE_MODE_NV 0x855A
#define GL_EYE_RADIAL_NV 0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV 0x855C


/******************************
* Extension: GL_NV_fragment_program
******************************/

#define GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV 0x8868
#define GL_FRAGMENT_PROGRAM_NV 0x8870
#define GL_MAX_TEXTURE_COORDS_NV 0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_NV 0x8872
#define GL_FRAGMENT_PROGRAM_BINDING_NV 0x8873
#define GL_PROGRAM_ERROR_STRING_NV 0x8874


typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);

extern PFNGLPROGRAMNAMEDPARAMETER4FNVPROC glProgramNamedParameter4fNV;
extern PFNGLPROGRAMNAMEDPARAMETER4DNVPROC glProgramNamedParameter4dNV;
extern PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC glProgramNamedParameter4fvNV;
extern PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC glProgramNamedParameter4dvNV;
extern PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC glGetProgramNamedParameterfvNV;
extern PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC glGetProgramNamedParameterdvNV;


/******************************
* Extension: GL_NV_fragment_program2
******************************/

#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV 0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV 0x88F5
#define GL_MAX_PROGRAM_IF_DEPTH_NV 0x88F6
#define GL_MAX_PROGRAM_LOOP_DEPTH_NV 0x88F7
#define GL_MAX_PROGRAM_LOOP_COUNT_NV 0x88F8


/******************************
* Extension: GL_NV_fragment_program4
******************************/

/******************************
* Extension: GL_NV_fragment_program_option
******************************/

/******************************
* Extension: GL_NV_framebuffer_multisample_coverage
******************************/

#define GL_RENDERBUFFER_COVERAGE_SAMPLES_NV 0x8CAB
#define GL_RENDERBUFFER_COLOR_SAMPLES_NV 0x8E10
#define GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV 0x8E11
#define GL_MULTISAMPLE_COVERAGE_MODES_NV 0x8E12


typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);

extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC glRenderbufferStorageMultisampleCoverageNV;


/******************************
* Extension: GL_NV_geometry_program4
******************************/

#define GL_LINES_ADJACENCY_EXT 0x000A
#define GL_LINE_STRIP_ADJACENCY_EXT 0x000B
#define GL_TRIANGLES_ADJACENCY_EXT 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT 0x000D
#define GL_GEOMETRY_PROGRAM_NV 0x8C26
#define GL_MAX_PROGRAM_OUTPUT_VERTICES_NV 0x8C27
#define GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV 0x8C28
#define GL_GEOMETRY_VERTICES_OUT_EXT 0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT 0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT 0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT 0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT 0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT 0x8642


typedef void (GLE_FUNCPTR * PFNGLPROGRAMVERTEXLIMITNVPROC)(GLenum target, GLint limit);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREEXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);

extern PFNGLPROGRAMVERTEXLIMITNVPROC glProgramVertexLimitNV;
extern PFNGLFRAMEBUFFERTEXTUREEXTPROC glFramebufferTextureEXT;
extern PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC glFramebufferTextureLayerEXT;
extern PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC glFramebufferTextureFaceEXT;


/******************************
* Extension: GL_NV_geometry_shader4
******************************/

/******************************
* Extension: GL_NV_gpu_program4
******************************/

#define GL_MIN_PROGRAM_TEXEL_OFFSET_NV 0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET_NV 0x8905
#define GL_PROGRAM_ATTRIB_COMPONENTS_NV 0x8906
#define GL_PROGRAM_RESULT_COMPONENTS_NV 0x8907
#define GL_MAX_PROGRAM_ATTRIB_COMPONENTS_NV 0x8908
#define GL_MAX_PROGRAM_RESULT_COMPONENTS_NV 0x8909
#define GL_MAX_PROGRAM_GENERIC_ATTRIBS_NV 0x8DA5
#define GL_MAX_PROGRAM_GENERIC_RESULTS_NV 0x8DA6


typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERI4INVPROC)(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)(GLenum target, GLuint index, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)(GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)(GLenum target, GLuint index, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)(GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERI4INVPROC)(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERI4IVNVPROC)(GLenum target, GLuint index, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)(GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERI4UINVPROC)(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)(GLenum target, GLuint index, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)(GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)(GLenum target, GLuint index, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)(GLenum target, GLuint index, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)(GLenum target, GLuint index, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)(GLenum target, GLuint index, GLuint *params);

extern PFNGLPROGRAMLOCALPARAMETERI4INVPROC glProgramLocalParameterI4iNV;
extern PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC glProgramLocalParameterI4ivNV;
extern PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC glProgramLocalParametersI4ivNV;
extern PFNGLPROGRAMLOCALPARAMETERI4UINVPROC glProgramLocalParameterI4uiNV;
extern PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC glProgramLocalParameterI4uivNV;
extern PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC glProgramLocalParametersI4uivNV;
extern PFNGLPROGRAMENVPARAMETERI4INVPROC glProgramEnvParameterI4iNV;
extern PFNGLPROGRAMENVPARAMETERI4IVNVPROC glProgramEnvParameterI4ivNV;
extern PFNGLPROGRAMENVPARAMETERSI4IVNVPROC glProgramEnvParametersI4ivNV;
extern PFNGLPROGRAMENVPARAMETERI4UINVPROC glProgramEnvParameterI4uiNV;
extern PFNGLPROGRAMENVPARAMETERI4UIVNVPROC glProgramEnvParameterI4uivNV;
extern PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC glProgramEnvParametersI4uivNV;
extern PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC glGetProgramLocalParameterIivNV;
extern PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC glGetProgramLocalParameterIuivNV;
extern PFNGLGETPROGRAMENVPARAMETERIIVNVPROC glGetProgramEnvParameterIivNV;
extern PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC glGetProgramEnvParameterIuivNV;


/******************************
* Extension: GL_NV_gpu_program5
******************************/

#define GL_MAX_GEOMETRY_PROGRAM_INVOCATIONS_NV 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_NV 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_NV 0x8E5C
#define GL_FRAGMENT_PROGRAM_INTERPOLATION_OFFSET_BITS_NV 0x8E5D
#define GL_MAX_PROGRAM_SUBROUTINE_PARAMETERS_NV 0x8F44
#define GL_MAX_PROGRAM_SUBROUTINE_NUM_NV 0x8F45


typedef void (GLE_FUNCPTR * PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)(GLenum target, GLsizei count, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)(GLenum target, GLuint index, GLuint *param);

extern PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC glProgramSubroutineParametersuivNV;
extern PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC glGetProgramSubroutineParameteruivNV;


/******************************
* Extension: GL_NV_gpu_shader5
******************************/

#define GL_PATCHES 0x000E
#define GL_INT64_NV 0x140E
#define GL_UNSIGNED_INT64_NV 0x140F
#define GL_INT8_NV 0x8FE0
#define GL_INT8_VEC2_NV 0x8FE1
#define GL_INT8_VEC3_NV 0x8FE2
#define GL_INT8_VEC4_NV 0x8FE3
#define GL_INT16_NV 0x8FE4
#define GL_INT16_VEC2_NV 0x8FE5
#define GL_INT16_VEC3_NV 0x8FE6
#define GL_INT16_VEC4_NV 0x8FE7
#define GL_INT64_VEC2_NV 0x8FE9
#define GL_INT64_VEC3_NV 0x8FEA
#define GL_INT64_VEC4_NV 0x8FEB
#define GL_UNSIGNED_INT8_NV 0x8FEC
#define GL_UNSIGNED_INT8_VEC2_NV 0x8FED
#define GL_UNSIGNED_INT8_VEC3_NV 0x8FEE
#define GL_UNSIGNED_INT8_VEC4_NV 0x8FEF
#define GL_UNSIGNED_INT16_NV 0x8FF0
#define GL_UNSIGNED_INT16_VEC2_NV 0x8FF1
#define GL_UNSIGNED_INT16_VEC3_NV 0x8FF2
#define GL_UNSIGNED_INT16_VEC4_NV 0x8FF3
#define GL_UNSIGNED_INT64_VEC2_NV 0x8FF5
#define GL_UNSIGNED_INT64_VEC3_NV 0x8FF6
#define GL_UNSIGNED_INT64_VEC4_NV 0x8FF7
#define GL_FLOAT16_NV 0x8FF8
#define GL_FLOAT16_VEC2_NV 0x8FF9
#define GL_FLOAT16_VEC3_NV 0x8FFA
#define GL_FLOAT16_VEC4_NV 0x8FFB


typedef void (GLE_FUNCPTR * PFNGLUNIFORM1I64NVPROC)(GLint location, GLint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2I64NVPROC)(GLint location, GLint64EXT x, GLint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3I64NVPROC)(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4I64NVPROC)(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1I64VNVPROC)(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2I64VNVPROC)(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3I64VNVPROC)(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4I64VNVPROC)(GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UI64NVPROC)(GLint location, GLuint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UI64NVPROC)(GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UI64NVPROC)(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UI64NVPROC)(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UI64VNVPROC)(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UI64VNVPROC)(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UI64VNVPROC)(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UI64VNVPROC)(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMI64VNVPROC)(GLuint program, GLint location, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1I64NVPROC)(GLuint program, GLint location, GLint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2I64NVPROC)(GLuint program, GLint location, GLint64EXT x, GLint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3I64NVPROC)(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4I64NVPROC)(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1I64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2I64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3I64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4I64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UI64NVPROC)(GLuint program, GLint location, GLuint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UI64NVPROC)(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UI64NVPROC)(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UI64NVPROC)(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM1UI64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM2UI64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM3UI64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORM4UI64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);

extern PFNGLUNIFORM1I64NVPROC glUniform1i64NV;
extern PFNGLUNIFORM2I64NVPROC glUniform2i64NV;
extern PFNGLUNIFORM3I64NVPROC glUniform3i64NV;
extern PFNGLUNIFORM4I64NVPROC glUniform4i64NV;
extern PFNGLUNIFORM1I64VNVPROC glUniform1i64vNV;
extern PFNGLUNIFORM2I64VNVPROC glUniform2i64vNV;
extern PFNGLUNIFORM3I64VNVPROC glUniform3i64vNV;
extern PFNGLUNIFORM4I64VNVPROC glUniform4i64vNV;
extern PFNGLUNIFORM1UI64NVPROC glUniform1ui64NV;
extern PFNGLUNIFORM2UI64NVPROC glUniform2ui64NV;
extern PFNGLUNIFORM3UI64NVPROC glUniform3ui64NV;
extern PFNGLUNIFORM4UI64NVPROC glUniform4ui64NV;
extern PFNGLUNIFORM1UI64VNVPROC glUniform1ui64vNV;
extern PFNGLUNIFORM2UI64VNVPROC glUniform2ui64vNV;
extern PFNGLUNIFORM3UI64VNVPROC glUniform3ui64vNV;
extern PFNGLUNIFORM4UI64VNVPROC glUniform4ui64vNV;
extern PFNGLGETUNIFORMI64VNVPROC glGetUniformi64vNV;
extern PFNGLPROGRAMUNIFORM1I64NVPROC glProgramUniform1i64NV;
extern PFNGLPROGRAMUNIFORM2I64NVPROC glProgramUniform2i64NV;
extern PFNGLPROGRAMUNIFORM3I64NVPROC glProgramUniform3i64NV;
extern PFNGLPROGRAMUNIFORM4I64NVPROC glProgramUniform4i64NV;
extern PFNGLPROGRAMUNIFORM1I64VNVPROC glProgramUniform1i64vNV;
extern PFNGLPROGRAMUNIFORM2I64VNVPROC glProgramUniform2i64vNV;
extern PFNGLPROGRAMUNIFORM3I64VNVPROC glProgramUniform3i64vNV;
extern PFNGLPROGRAMUNIFORM4I64VNVPROC glProgramUniform4i64vNV;
extern PFNGLPROGRAMUNIFORM1UI64NVPROC glProgramUniform1ui64NV;
extern PFNGLPROGRAMUNIFORM2UI64NVPROC glProgramUniform2ui64NV;
extern PFNGLPROGRAMUNIFORM3UI64NVPROC glProgramUniform3ui64NV;
extern PFNGLPROGRAMUNIFORM4UI64NVPROC glProgramUniform4ui64NV;
extern PFNGLPROGRAMUNIFORM1UI64VNVPROC glProgramUniform1ui64vNV;
extern PFNGLPROGRAMUNIFORM2UI64VNVPROC glProgramUniform2ui64vNV;
extern PFNGLPROGRAMUNIFORM3UI64VNVPROC glProgramUniform3ui64vNV;
extern PFNGLPROGRAMUNIFORM4UI64VNVPROC glProgramUniform4ui64vNV;


/******************************
* Extension: GL_NV_half_float
******************************/

#define GL_HALF_FLOAT_NV 0x140B


typedef void (GLE_FUNCPTR * PFNGLVERTEX2HNVPROC)(GLhalfNV x, GLhalfNV y);
typedef void (GLE_FUNCPTR * PFNGLVERTEX2HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3HNVPROC)(GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (GLE_FUNCPTR * PFNGLVERTEX3HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4HNVPROC)(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (GLE_FUNCPTR * PFNGLVERTEX4HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3HNVPROC)(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3HNVPROC)(GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4HNVPROC)(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1HNVPROC)(GLhalfNV s);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2HNVPROC)(GLhalfNV s, GLhalfNV t);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3HNVPROC)(GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4HNVPROC)(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1HNVPROC)(GLenum target, GLhalfNV s);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1HVNVPROC)(GLenum target, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2HNVPROC)(GLenum target, GLhalfNV s, GLhalfNV t);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2HVNVPROC)(GLenum target, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3HNVPROC)(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3HVNVPROC)(GLenum target, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4HNVPROC)(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4HVNVPROC)(GLenum target, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDHNVPROC)(GLhalfNV fog);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDHVNVPROC)(const GLhalfNV *fog);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3HNVPROC)(GLhalfNV red, GLhalfNV green, GLhalfNV blue);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3HVNVPROC)(const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTHNVPROC)(GLhalfNV weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTHVNVPROC)(const GLhalfNV *weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1HNVPROC)(GLuint index, GLhalfNV x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1HVNVPROC)(GLuint index, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2HNVPROC)(GLuint index, GLhalfNV x, GLhalfNV y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2HVNVPROC)(GLuint index, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3HNVPROC)(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3HVNVPROC)(GLuint index, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4HNVPROC)(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4HVNVPROC)(GLuint index, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS1HVNVPROC)(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS2HVNVPROC)(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS3HVNVPROC)(GLuint index, GLsizei n, const GLhalfNV *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS4HVNVPROC)(GLuint index, GLsizei n, const GLhalfNV *v);

extern PFNGLVERTEX2HNVPROC glVertex2hNV;
extern PFNGLVERTEX2HVNVPROC glVertex2hvNV;
extern PFNGLVERTEX3HNVPROC glVertex3hNV;
extern PFNGLVERTEX3HVNVPROC glVertex3hvNV;
extern PFNGLVERTEX4HNVPROC glVertex4hNV;
extern PFNGLVERTEX4HVNVPROC glVertex4hvNV;
extern PFNGLNORMAL3HNVPROC glNormal3hNV;
extern PFNGLNORMAL3HVNVPROC glNormal3hvNV;
extern PFNGLCOLOR3HNVPROC glColor3hNV;
extern PFNGLCOLOR3HVNVPROC glColor3hvNV;
extern PFNGLCOLOR4HNVPROC glColor4hNV;
extern PFNGLCOLOR4HVNVPROC glColor4hvNV;
extern PFNGLTEXCOORD1HNVPROC glTexCoord1hNV;
extern PFNGLTEXCOORD1HVNVPROC glTexCoord1hvNV;
extern PFNGLTEXCOORD2HNVPROC glTexCoord2hNV;
extern PFNGLTEXCOORD2HVNVPROC glTexCoord2hvNV;
extern PFNGLTEXCOORD3HNVPROC glTexCoord3hNV;
extern PFNGLTEXCOORD3HVNVPROC glTexCoord3hvNV;
extern PFNGLTEXCOORD4HNVPROC glTexCoord4hNV;
extern PFNGLTEXCOORD4HVNVPROC glTexCoord4hvNV;
extern PFNGLMULTITEXCOORD1HNVPROC glMultiTexCoord1hNV;
extern PFNGLMULTITEXCOORD1HVNVPROC glMultiTexCoord1hvNV;
extern PFNGLMULTITEXCOORD2HNVPROC glMultiTexCoord2hNV;
extern PFNGLMULTITEXCOORD2HVNVPROC glMultiTexCoord2hvNV;
extern PFNGLMULTITEXCOORD3HNVPROC glMultiTexCoord3hNV;
extern PFNGLMULTITEXCOORD3HVNVPROC glMultiTexCoord3hvNV;
extern PFNGLMULTITEXCOORD4HNVPROC glMultiTexCoord4hNV;
extern PFNGLMULTITEXCOORD4HVNVPROC glMultiTexCoord4hvNV;
extern PFNGLFOGCOORDHNVPROC glFogCoordhNV;
extern PFNGLFOGCOORDHVNVPROC glFogCoordhvNV;
extern PFNGLSECONDARYCOLOR3HNVPROC glSecondaryColor3hNV;
extern PFNGLSECONDARYCOLOR3HVNVPROC glSecondaryColor3hvNV;
extern PFNGLVERTEXWEIGHTHNVPROC glVertexWeighthNV;
extern PFNGLVERTEXWEIGHTHVNVPROC glVertexWeighthvNV;
extern PFNGLVERTEXATTRIB1HNVPROC glVertexAttrib1hNV;
extern PFNGLVERTEXATTRIB1HVNVPROC glVertexAttrib1hvNV;
extern PFNGLVERTEXATTRIB2HNVPROC glVertexAttrib2hNV;
extern PFNGLVERTEXATTRIB2HVNVPROC glVertexAttrib2hvNV;
extern PFNGLVERTEXATTRIB3HNVPROC glVertexAttrib3hNV;
extern PFNGLVERTEXATTRIB3HVNVPROC glVertexAttrib3hvNV;
extern PFNGLVERTEXATTRIB4HNVPROC glVertexAttrib4hNV;
extern PFNGLVERTEXATTRIB4HVNVPROC glVertexAttrib4hvNV;
extern PFNGLVERTEXATTRIBS1HVNVPROC glVertexAttribs1hvNV;
extern PFNGLVERTEXATTRIBS2HVNVPROC glVertexAttribs2hvNV;
extern PFNGLVERTEXATTRIBS3HVNVPROC glVertexAttribs3hvNV;
extern PFNGLVERTEXATTRIBS4HVNVPROC glVertexAttribs4hvNV;


/******************************
* Extension: GL_NV_light_max_exponent
******************************/

#define GL_MAX_SHININESS_NV 0x8504
#define GL_MAX_SPOT_EXPONENT_NV 0x8505


/******************************
* Extension: GL_NV_multisample_coverage
******************************/

#define GL_COVERAGE_SAMPLES_NV 0x80A9
#define GL_COLOR_SAMPLES_NV 0x8E20


/******************************
* Extension: GL_NV_multisample_filter_hint
******************************/

#define GL_MULTISAMPLE_FILTER_HINT_NV 0x8534


/******************************
* Extension: GL_NV_occlusion_query
******************************/

#define GL_PIXEL_COUNTER_BITS_NV 0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV 0x8865
#define GL_PIXEL_COUNT_NV 0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV 0x8867


typedef void (GLE_FUNCPTR * PFNGLGENOCCLUSIONQUERIESNVPROC)(GLsizei n, GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLDELETEOCCLUSIONQUERIESNVPROC)(GLsizei n, const GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISOCCLUSIONQUERYNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINOCCLUSIONQUERYNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDOCCLUSIONQUERYNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLGETOCCLUSIONQUERYIVNVPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETOCCLUSIONQUERYUIVNVPROC)(GLuint id, GLenum pname, GLuint *params);

extern PFNGLGENOCCLUSIONQUERIESNVPROC glGenOcclusionQueriesNV;
extern PFNGLDELETEOCCLUSIONQUERIESNVPROC glDeleteOcclusionQueriesNV;
extern PFNGLISOCCLUSIONQUERYNVPROC glIsOcclusionQueryNV;
extern PFNGLBEGINOCCLUSIONQUERYNVPROC glBeginOcclusionQueryNV;
extern PFNGLENDOCCLUSIONQUERYNVPROC glEndOcclusionQueryNV;
extern PFNGLGETOCCLUSIONQUERYIVNVPROC glGetOcclusionQueryivNV;
extern PFNGLGETOCCLUSIONQUERYUIVNVPROC glGetOcclusionQueryuivNV;


/******************************
* Extension: GL_NV_packed_depth_stencil
******************************/

#define GL_DEPTH_STENCIL_NV 0x84F9
#define GL_UNSIGNED_INT_24_8_NV 0x84FA


/******************************
* Extension: GL_NV_parameter_buffer_object
******************************/

#define GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV 0x8DA0
#define GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV 0x8DA1
#define GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV 0x8DA2
#define GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV 0x8DA3
#define GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV 0x8DA4


typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLuint *params);

extern PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC glProgramBufferParametersfvNV;
extern PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC glProgramBufferParametersIivNV;
extern PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC glProgramBufferParametersIuivNV;


/******************************
* Extension: GL_NV_parameter_buffer_object2
******************************/

/******************************
* Extension: GL_NV_pixel_data_range
******************************/

#define GL_WRITE_PIXEL_DATA_RANGE_NV 0x8878
#define GL_READ_PIXEL_DATA_RANGE_NV 0x8879
#define GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV 0x887A
#define GL_READ_PIXEL_DATA_RANGE_LENGTH_NV 0x887B
#define GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV 0x887C
#define GL_READ_PIXEL_DATA_RANGE_POINTER_NV 0x887D


typedef void (GLE_FUNCPTR * PFNGLPIXELDATARANGENVPROC)(GLenum target, GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLFLUSHPIXELDATARANGENVPROC)(GLenum target);

extern PFNGLPIXELDATARANGENVPROC glPixelDataRangeNV;
extern PFNGLFLUSHPIXELDATARANGENVPROC glFlushPixelDataRangeNV;


/******************************
* Extension: GL_NV_point_sprite
******************************/

#define GL_POINT_SPRITE_NV 0x8861
#define GL_COORD_REPLACE_NV 0x8862
#define GL_POINT_SPRITE_R_MODE_NV 0x8863


typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERINVPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIVNVPROC)(GLenum pname, const GLint *params);

extern PFNGLPOINTPARAMETERINVPROC glPointParameteriNV;
extern PFNGLPOINTPARAMETERIVNVPROC glPointParameterivNV;


/******************************
* Extension: GL_NV_present_video
******************************/

#define GL_FRAME_NV 0x8E26
#define GL_FIELDS_NV 0x8E27
#define GL_CURRENT_TIME_NV 0x8E28
#define GL_NUM_FILL_STREAMS_NV 0x8E29
#define GL_PRESENT_TIME_NV 0x8E2A
#define GL_PRESENT_DURATION_NV 0x8E2B


typedef void (GLE_FUNCPTR * PFNGLPRESENTFRAMEKEYEDNVPROC)(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1);
typedef void (GLE_FUNCPTR * PFNGLPRESENTFRAMEDUALFILLNVPROC)(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOIVNVPROC)(GLuint video_slot, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOUIVNVPROC)(GLuint video_slot, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOI64VNVPROC)(GLuint video_slot, GLenum pname, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOUI64VNVPROC)(GLuint video_slot, GLenum pname, GLuint64EXT *params);

extern PFNGLPRESENTFRAMEKEYEDNVPROC glPresentFrameKeyedNV;
extern PFNGLPRESENTFRAMEDUALFILLNVPROC glPresentFrameDualFillNV;
extern PFNGLGETVIDEOIVNVPROC glGetVideoivNV;
extern PFNGLGETVIDEOUIVNVPROC glGetVideouivNV;
extern PFNGLGETVIDEOI64VNVPROC glGetVideoi64vNV;
extern PFNGLGETVIDEOUI64VNVPROC glGetVideoui64vNV;


/******************************
* Extension: GL_NV_primitive_restart
******************************/

#define GL_PRIMITIVE_RESTART_NV 0x8558
#define GL_PRIMITIVE_RESTART_INDEX_NV 0x8559


typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTINDEXNVPROC)(GLuint index);

extern PFNGLPRIMITIVERESTARTNVPROC glPrimitiveRestartNV;
extern PFNGLPRIMITIVERESTARTINDEXNVPROC glPrimitiveRestartIndexNV;


/******************************
* Extension: GL_NV_register_combiners
******************************/

#define GL_ZERO 0
#define GL_NONE 0
#define GL_FOG 0x0B60
#define GL_TEXTURE0_ARB 0x84C0
#define GL_TEXTURE1_ARB 0x84C1
#define GL_REGISTER_COMBINERS_NV 0x8522
#define GL_VARIABLE_A_NV 0x8523
#define GL_VARIABLE_B_NV 0x8524
#define GL_VARIABLE_C_NV 0x8525
#define GL_VARIABLE_D_NV 0x8526
#define GL_VARIABLE_E_NV 0x8527
#define GL_VARIABLE_F_NV 0x8528
#define GL_VARIABLE_G_NV 0x8529
#define GL_CONSTANT_COLOR0_NV 0x852A
#define GL_CONSTANT_COLOR1_NV 0x852B
#define GL_PRIMARY_COLOR_NV 0x852C
#define GL_SECONDARY_COLOR_NV 0x852D
#define GL_SPARE0_NV 0x852E
#define GL_SPARE1_NV 0x852F
#define GL_DISCARD_NV 0x8530
#define GL_E_TIMES_F_NV 0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV 0x8532
#define GL_UNSIGNED_IDENTITY_NV 0x8536
#define GL_UNSIGNED_INVERT_NV 0x8537
#define GL_EXPAND_NORMAL_NV 0x8538
#define GL_EXPAND_NEGATE_NV 0x8539
#define GL_HALF_BIAS_NORMAL_NV 0x853A
#define GL_HALF_BIAS_NEGATE_NV 0x853B
#define GL_SIGNED_IDENTITY_NV 0x853C
#define GL_SIGNED_NEGATE_NV 0x853D
#define GL_SCALE_BY_TWO_NV 0x853E
#define GL_SCALE_BY_FOUR_NV 0x853F
#define GL_SCALE_BY_ONE_HALF_NV 0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV 0x8541
#define GL_COMBINER_INPUT_NV 0x8542
#define GL_COMBINER_MAPPING_NV 0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV 0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV 0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV 0x8546
#define GL_COMBINER_MUX_SUM_NV 0x8547
#define GL_COMBINER_SCALE_NV 0x8548
#define GL_COMBINER_BIAS_NV 0x8549
#define GL_COMBINER_AB_OUTPUT_NV 0x854A
#define GL_COMBINER_CD_OUTPUT_NV 0x854B
#define GL_COMBINER_SUM_OUTPUT_NV 0x854C
#define GL_MAX_GENERAL_COMBINERS_NV 0x854D
#define GL_NUM_GENERAL_COMBINERS_NV 0x854E
#define GL_COLOR_SUM_CLAMP_NV 0x854F
#define GL_COMBINER0_NV 0x8550
#define GL_COMBINER1_NV 0x8551
#define GL_COMBINER2_NV 0x8552
#define GL_COMBINER3_NV 0x8553
#define GL_COMBINER4_NV 0x8554
#define GL_COMBINER5_NV 0x8555
#define GL_COMBINER6_NV 0x8556
#define GL_COMBINER7_NV 0x8557


typedef void (GLE_FUNCPTR * PFNGLCOMBINERPARAMETERFVNVPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCOMBINERPARAMETERFNVPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLCOMBINERPARAMETERIVNVPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOMBINERPARAMETERINVPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLCOMBINERINPUTNVPROC)(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (GLE_FUNCPTR * PFNGLCOMBINEROUTPUTNVPROC)(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (GLE_FUNCPTR * PFNGLFINALCOMBINERINPUTNVPROC)(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)(GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)(GLenum stage, GLenum portion, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)(GLenum variable, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)(GLenum variable, GLenum pname, GLint *params);

extern PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
extern PFNGLCOMBINERPARAMETERFNVPROC glCombinerParameterfNV;
extern PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV;
extern PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
extern PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
extern PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
extern PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;
extern PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV;
extern PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV;


/******************************
* Extension: GL_NV_register_combiners2
******************************/

#define GL_PER_STAGE_CONSTANTS_NV 0x8535


typedef void (GLE_FUNCPTR * PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum stage, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum stage, GLenum pname, GLfloat *params);

extern PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV;
extern PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC glGetCombinerStageParameterfvNV;


/******************************
* Extension: GL_NV_shader_buffer_load
******************************/

#define GL_BUFFER_GPU_ADDRESS_NV 0x8F1D
#define GL_GPU_ADDRESS_NV 0x8F34
#define GL_MAX_SHADER_BUFFER_ADDRESS_NV 0x8F35


typedef void (GLE_FUNCPTR * PFNGLMAKEBUFFERRESIDENTNVPROC)(GLenum target, GLenum access);
typedef void (GLE_FUNCPTR * PFNGLMAKEBUFFERNONRESIDENTNVPROC)(GLenum target);
typedef GLboolean (GLE_FUNCPTR * PFNGLISBUFFERRESIDENTNVPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)(GLuint buffer, GLenum access);
typedef void (GLE_FUNCPTR * PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)(GLuint buffer);
typedef GLboolean (GLE_FUNCPTR * PFNGLISNAMEDBUFFERRESIDENTNVPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERUI64VNVPROC)(GLenum target, GLenum pname, GLuint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)(GLuint buffer, GLenum pname, GLuint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERUI64VNVPROC)(GLenum value, GLuint64EXT *result);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMUI64NVPROC)(GLint location, GLuint64EXT value);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMUI64VNVPROC)(GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMUI64VNVPROC)(GLuint program, GLint location, GLuint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMUI64NVPROC)(GLuint program, GLint location, GLuint64EXT value);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMUNIFORMUI64VNVPROC)(GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);

extern PFNGLMAKEBUFFERRESIDENTNVPROC glMakeBufferResidentNV;
extern PFNGLMAKEBUFFERNONRESIDENTNVPROC glMakeBufferNonResidentNV;
extern PFNGLISBUFFERRESIDENTNVPROC glIsBufferResidentNV;
extern PFNGLMAKENAMEDBUFFERRESIDENTNVPROC glMakeNamedBufferResidentNV;
extern PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC glMakeNamedBufferNonResidentNV;
extern PFNGLISNAMEDBUFFERRESIDENTNVPROC glIsNamedBufferResidentNV;
extern PFNGLGETBUFFERPARAMETERUI64VNVPROC glGetBufferParameterui64vNV;
extern PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC glGetNamedBufferParameterui64vNV;
extern PFNGLGETINTEGERUI64VNVPROC glGetIntegerui64vNV;
extern PFNGLUNIFORMUI64NVPROC glUniformui64NV;
extern PFNGLUNIFORMUI64VNVPROC glUniformui64vNV;
extern PFNGLGETUNIFORMUI64VNVPROC glGetUniformui64vNV;
extern PFNGLPROGRAMUNIFORMUI64NVPROC glProgramUniformui64NV;
extern PFNGLPROGRAMUNIFORMUI64VNVPROC glProgramUniformui64vNV;


/******************************
* Extension: GL_NV_shader_buffer_store
******************************/

#define GL_WRITE_ONLY 0x88B9
#define GL_READ_WRITE 0x88BA
#define GL_SHADER_GLOBAL_ACCESS_BARRIER_BIT_NV 0x00000010


/******************************
* Extension: GL_NV_tessellation_program5
******************************/

#define GL_MAX_PROGRAM_PATCH_ATTRIBS_NV 0x86D8
#define GL_TESS_CONTROL_PROGRAM_NV 0x891E
#define GL_TESS_EVALUATION_PROGRAM_NV 0x891F
#define GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV 0x8C74
#define GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV 0x8C75


/******************************
* Extension: GL_NV_texgen_emboss
******************************/

#define GL_EMBOSS_LIGHT_NV 0x855D
#define GL_EMBOSS_CONSTANT_NV 0x855E
#define GL_EMBOSS_MAP_NV 0x855F


/******************************
* Extension: GL_NV_texgen_reflection
******************************/

#define GL_NORMAL_MAP_NV 0x8511
#define GL_REFLECTION_MAP_NV 0x8512


/******************************
* Extension: GL_NV_texture_barrier
******************************/

typedef void (GLE_FUNCPTR * PFNGLTEXTUREBARRIERNVPROC)();

extern PFNGLTEXTUREBARRIERNVPROC glTextureBarrierNV;


/******************************
* Extension: GL_NV_texture_compression_vtc
******************************/

/******************************
* Extension: GL_NV_texture_env_combine4
******************************/

#define GL_COMBINE4_NV 0x8503
#define GL_SOURCE3_RGB_NV 0x8583
#define GL_SOURCE3_ALPHA_NV 0x858B
#define GL_OPERAND3_RGB_NV 0x8593
#define GL_OPERAND3_ALPHA_NV 0x859B


/******************************
* Extension: GL_NV_texture_expand_normal
******************************/

#define GL_TEXTURE_UNSIGNED_REMAP_MODE_NV 0x888F


/******************************
* Extension: GL_NV_texture_rectangle
******************************/

#define GL_TEXTURE_RECTANGLE_NV 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV 0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV 0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV 0x84F8


/******************************
* Extension: GL_NV_texture_shader
******************************/

#define GL_OFFSET_TEXTURE_RECTANGLE_NV 0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV 0x864D
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV 0x864E
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV 0x86D9
#define GL_UNSIGNED_INT_S8_S8_8_8_NV 0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV 0x86DB
#define GL_DSDT_MAG_INTENSITY_NV 0x86DC
#define GL_SHADER_CONSISTENT_NV 0x86DD
#define GL_TEXTURE_SHADER_NV 0x86DE
#define GL_SHADER_OPERATION_NV 0x86DF
#define GL_CULL_MODES_NV 0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV 0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV 0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV 0x86E3
#define GL_OFFSET_TEXTURE_2D_MATRIX_NV 0x86E1 /* GL_OFFSET_TEXTURE_MATRIX_NV */
#define GL_OFFSET_TEXTURE_2D_SCALE_NV 0x86E2 /* GL_OFFSET_TEXTURE_SCALE_NV */
#define GL_OFFSET_TEXTURE_2D_BIAS_NV 0x86E3 /* GL_OFFSET_TEXTURE_BIAS_NV */
#define GL_PREVIOUS_TEXTURE_INPUT_NV 0x86E4
#define GL_CONST_EYE_NV 0x86E5
#define GL_PASS_THROUGH_NV 0x86E6
#define GL_CULL_FRAGMENT_NV 0x86E7
#define GL_OFFSET_TEXTURE_2D_NV 0x86E8
#define GL_DEPENDENT_AR_TEXTURE_2D_NV 0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV 0x86EA
#define GL_DOT_PRODUCT_NV 0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV 0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV 0x86EE
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV 0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV 0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV 0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV 0x86F3
#define GL_HILO_NV 0x86F4
#define GL_DSDT_NV 0x86F5
#define GL_DSDT_MAG_NV 0x86F6
#define GL_DSDT_MAG_VIB_NV 0x86F7
#define GL_HILO16_NV 0x86F8
#define GL_SIGNED_HILO_NV 0x86F9
#define GL_SIGNED_HILO16_NV 0x86FA
#define GL_SIGNED_RGBA_NV 0x86FB
#define GL_SIGNED_RGBA8_NV 0x86FC
#define GL_SIGNED_RGB_NV 0x86FE
#define GL_SIGNED_RGB8_NV 0x86FF
#define GL_SIGNED_LUMINANCE_NV 0x8701
#define GL_SIGNED_LUMINANCE8_NV 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV 0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV 0x8704
#define GL_SIGNED_ALPHA_NV 0x8705
#define GL_SIGNED_ALPHA8_NV 0x8706
#define GL_SIGNED_INTENSITY_NV 0x8707
#define GL_SIGNED_INTENSITY8_NV 0x8708
#define GL_DSDT8_NV 0x8709
#define GL_DSDT8_MAG8_NV 0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV 0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV 0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV 0x870D
#define GL_HI_SCALE_NV 0x870E
#define GL_LO_SCALE_NV 0x870F
#define GL_DS_SCALE_NV 0x8710
#define GL_DT_SCALE_NV 0x8711
#define GL_MAGNITUDE_SCALE_NV 0x8712
#define GL_VIBRANCE_SCALE_NV 0x8713
#define GL_HI_BIAS_NV 0x8714
#define GL_LO_BIAS_NV 0x8715
#define GL_DS_BIAS_NV 0x8716
#define GL_DT_BIAS_NV 0x8717
#define GL_MAGNITUDE_BIAS_NV 0x8718
#define GL_VIBRANCE_BIAS_NV 0x8719
#define GL_TEXTURE_BORDER_VALUES_NV 0x871A
#define GL_TEXTURE_HI_SIZE_NV 0x871B
#define GL_TEXTURE_LO_SIZE_NV 0x871C
#define GL_TEXTURE_DS_SIZE_NV 0x871D
#define GL_TEXTURE_DT_SIZE_NV 0x871E
#define GL_TEXTURE_MAG_SIZE_NV 0x871F


/******************************
* Extension: GL_NV_texture_shader2
******************************/

#define GL_DOT_PRODUCT_TEXTURE_3D_NV 0x86EF


/******************************
* Extension: GL_NV_texture_shader3
******************************/

#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV 0x8850
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV 0x8851
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8852
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV 0x8853
#define GL_OFFSET_HILO_TEXTURE_2D_NV 0x8854
#define GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV 0x8855
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV 0x8856
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV 0x8857
#define GL_DEPENDENT_HILO_TEXTURE_2D_NV 0x8858
#define GL_DEPENDENT_RGB_TEXTURE_3D_NV 0x8859
#define GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV 0x885A
#define GL_DOT_PRODUCT_PASS_THROUGH_NV 0x885B
#define GL_DOT_PRODUCT_TEXTURE_1D_NV 0x885C
#define GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV 0x885D
#define GL_HILO8_NV 0x885E
#define GL_SIGNED_HILO8_NV 0x885F
#define GL_FORCE_BLUE_TO_ONE_NV 0x8860


/******************************
* Extension: GL_NV_transform_feedback
******************************/

#define GL_BACK_PRIMARY_COLOR_NV 0x8C77
#define GL_BACK_SECONDARY_COLOR_NV 0x8C78
#define GL_TEXTURE_COORD_NV 0x8C79
#define GL_CLIP_DISTANCE_NV 0x8C7A
#define GL_VERTEX_ID_NV 0x8C7B
#define GL_PRIMITIVE_ID_NV 0x8C7C
#define GL_GENERIC_ATTRIB_NV 0x8C7D
#define GL_TRANSFORM_FEEDBACK_ATTRIBS_NV 0x8C7E
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_NV 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV 0x8C80
#define GL_ACTIVE_VARYINGS_NV 0x8C81
#define GL_ACTIVE_VARYING_MAX_LENGTH_NV 0x8C82
#define GL_TRANSFORM_FEEDBACK_VARYINGS_NV 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_NV 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_NV 0x8C85
#define GL_TRANSFORM_FEEDBACK_RECORD_NV 0x8C86
#define GL_PRIMITIVES_GENERATED_NV 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV 0x8C88
#define GL_RASTERIZER_DISCARD_NV 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_ATTRIBS_NV 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV 0x8C8B
#define GL_INTERLEAVED_ATTRIBS_NV 0x8C8C
#define GL_SEPARATE_ATTRIBS_NV 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER_NV 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_NV 0x8C8F
#define GL_LAYER_NV 0x8DAA


typedef void (GLE_FUNCPTR * PFNGLBEGINTRANSFORMFEEDBACKNVPROC)(GLenum primitiveMode);
typedef void (GLE_FUNCPTR * PFNGLENDTRANSFORMFEEDBACKNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)(GLuint count, const GLint *attribs, GLenum bufferMode);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERRANGENVPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFEROFFSETNVPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERBASENVPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)(GLuint program, GLsizei count, const GLint *locations, GLenum bufferMode);
typedef void (GLE_FUNCPTR * PFNGLACTIVEVARYINGNVPROC)(GLuint program, const GLchar *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETVARYINGLOCATIONNVPROC)(GLuint program, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEVARYINGNVPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)(GLuint program, GLuint index, GLint *location);
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)(GLsizei count, const GLint *attribs, GLsizei nbuffers, const GLint *bufstreams, GLenum bufferMode);

extern PFNGLBEGINTRANSFORMFEEDBACKNVPROC glBeginTransformFeedbackNV;
extern PFNGLENDTRANSFORMFEEDBACKNVPROC glEndTransformFeedbackNV;
extern PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC glTransformFeedbackAttribsNV;
extern PFNGLBINDBUFFERRANGENVPROC glBindBufferRangeNV;
extern PFNGLBINDBUFFEROFFSETNVPROC glBindBufferOffsetNV;
extern PFNGLBINDBUFFERBASENVPROC glBindBufferBaseNV;
extern PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC glTransformFeedbackVaryingsNV;
extern PFNGLACTIVEVARYINGNVPROC glActiveVaryingNV;
extern PFNGLGETVARYINGLOCATIONNVPROC glGetVaryingLocationNV;
extern PFNGLGETACTIVEVARYINGNVPROC glGetActiveVaryingNV;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC glGetTransformFeedbackVaryingNV;
extern PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC glTransformFeedbackStreamAttribsNV;


/******************************
* Extension: GL_NV_transform_feedback2
******************************/

#define GL_TRANSFORM_FEEDBACK_NV 0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING_NV 0x8E25


typedef void (GLE_FUNCPTR * PFNGLBINDTRANSFORMFEEDBACKNVPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETETRANSFORMFEEDBACKSNVPROC)(GLsizei n, const GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLGENTRANSFORMFEEDBACKSNVPROC)(GLsizei n, GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTRANSFORMFEEDBACKNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLPAUSETRANSFORMFEEDBACKNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLRESUMETRANSFORMFEEDBACKNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKNVPROC)(GLenum mode, GLuint id);

extern PFNGLBINDTRANSFORMFEEDBACKNVPROC glBindTransformFeedbackNV;
extern PFNGLDELETETRANSFORMFEEDBACKSNVPROC glDeleteTransformFeedbacksNV;
extern PFNGLGENTRANSFORMFEEDBACKSNVPROC glGenTransformFeedbacksNV;
extern PFNGLISTRANSFORMFEEDBACKNVPROC glIsTransformFeedbackNV;
extern PFNGLPAUSETRANSFORMFEEDBACKNVPROC glPauseTransformFeedbackNV;
extern PFNGLRESUMETRANSFORMFEEDBACKNVPROC glResumeTransformFeedbackNV;
extern PFNGLDRAWTRANSFORMFEEDBACKNVPROC glDrawTransformFeedbackNV;


/******************************
* Extension: GL_NV_vdpau_interop
******************************/

#define GL_SURFACE_STATE_NV 0x86EB
#define GL_SURFACE_REGISTERED_NV 0x86FD
#define GL_SURFACE_MAPPED_NV 0x8700
#define GL_WRITE_DISCARD_NV 0x88BE


typedef void (GLE_FUNCPTR * PFNGLVDPAUINITNVPROC)(const GLvoid *vdpDevice, const GLvoid *getProcAddress);
typedef void (GLE_FUNCPTR * PFNGLVDPAUFININVPROC)();
typedef GLvdpauSurfaceNV (GLE_FUNCPTR * PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)(GLvoid *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames);
typedef GLvdpauSurfaceNV (GLE_FUNCPTR * PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)(GLvoid *vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint *textureNames);
typedef void (GLE_FUNCPTR * PFNGLVDPAUISSURFACENVPROC)(GLvdpauSurfaceNV surface);
typedef void (GLE_FUNCPTR * PFNGLVDPAUUNREGISTERSURFACENVPROC)(GLvdpauSurfaceNV surface);
typedef void (GLE_FUNCPTR * PFNGLVDPAUGETSURFACEIVNVPROC)(GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
typedef void (GLE_FUNCPTR * PFNGLVDPAUSURFACEACCESSNVPROC)(GLvdpauSurfaceNV surface, GLenum access);
typedef void (GLE_FUNCPTR * PFNGLVDPAUMAPSURFACESNVPROC)(GLsizei numSurfaces, const GLvdpauSurfaceNV *surfaces);
typedef void (GLE_FUNCPTR * PFNGLVDPAUUNMAPSURFACESNVPROC)(GLsizei numSurface, const GLvdpauSurfaceNV *surfaces);

extern PFNGLVDPAUINITNVPROC glVDPAUInitNV;
extern PFNGLVDPAUFININVPROC glVDPAUFiniNV;
extern PFNGLVDPAUREGISTERVIDEOSURFACENVPROC glVDPAURegisterVideoSurfaceNV;
extern PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC glVDPAURegisterOutputSurfaceNV;
extern PFNGLVDPAUISSURFACENVPROC glVDPAUIsSurfaceNV;
extern PFNGLVDPAUUNREGISTERSURFACENVPROC glVDPAUUnregisterSurfaceNV;
extern PFNGLVDPAUGETSURFACEIVNVPROC glVDPAUGetSurfaceivNV;
extern PFNGLVDPAUSURFACEACCESSNVPROC glVDPAUSurfaceAccessNV;
extern PFNGLVDPAUMAPSURFACESNVPROC glVDPAUMapSurfacesNV;
extern PFNGLVDPAUUNMAPSURFACESNVPROC glVDPAUUnmapSurfacesNV;


/******************************
* Extension: GL_NV_vertex_array_range
******************************/

#define GL_VERTEX_ARRAY_RANGE_NV 0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV 0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV 0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV 0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV 0x8521


typedef void (GLE_FUNCPTR * PFNGLFLUSHVERTEXARRAYRANGENVPROC)();
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYRANGENVPROC)(GLsizei length, const GLvoid *pointer);

extern PFNGLFLUSHVERTEXARRAYRANGENVPROC glFlushVertexArrayRangeNV;
extern PFNGLVERTEXARRAYRANGENVPROC glVertexArrayRangeNV;


/******************************
* Extension: GL_NV_vertex_array_range2
******************************/

#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV 0x8533


/******************************
* Extension: GL_NV_vertex_attrib_integer_64bit
******************************/

#define GL_INT64_NV 0x140E
#define GL_UNSIGNED_INT64_NV 0x140F


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1I64NVPROC)(GLuint index, GLint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2I64NVPROC)(GLuint index, GLint64EXT x, GLint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3I64NVPROC)(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4I64NVPROC)(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1I64VNVPROC)(GLuint index, const GLint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2I64VNVPROC)(GLuint index, const GLint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3I64VNVPROC)(GLuint index, const GLint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4I64VNVPROC)(GLuint index, const GLint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1UI64NVPROC)(GLuint index, GLuint64EXT x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2UI64NVPROC)(GLuint index, GLuint64EXT x, GLuint64EXT y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3UI64NVPROC)(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4UI64NVPROC)(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL1UI64VNVPROC)(GLuint index, const GLuint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL2UI64VNVPROC)(GLuint index, const GLuint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL3UI64VNVPROC)(GLuint index, const GLuint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBL4UI64VNVPROC)(GLuint index, const GLuint64EXT *v);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBLI64VNVPROC)(GLuint index, GLenum pname, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBLUI64VNVPROC)(GLuint index, GLenum pname, GLuint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBLFORMATNVPROC)(GLuint index, GLint size, GLenum type, GLsizei stride);

extern PFNGLVERTEXATTRIBL1I64NVPROC glVertexAttribL1i64NV;
extern PFNGLVERTEXATTRIBL2I64NVPROC glVertexAttribL2i64NV;
extern PFNGLVERTEXATTRIBL3I64NVPROC glVertexAttribL3i64NV;
extern PFNGLVERTEXATTRIBL4I64NVPROC glVertexAttribL4i64NV;
extern PFNGLVERTEXATTRIBL1I64VNVPROC glVertexAttribL1i64vNV;
extern PFNGLVERTEXATTRIBL2I64VNVPROC glVertexAttribL2i64vNV;
extern PFNGLVERTEXATTRIBL3I64VNVPROC glVertexAttribL3i64vNV;
extern PFNGLVERTEXATTRIBL4I64VNVPROC glVertexAttribL4i64vNV;
extern PFNGLVERTEXATTRIBL1UI64NVPROC glVertexAttribL1ui64NV;
extern PFNGLVERTEXATTRIBL2UI64NVPROC glVertexAttribL2ui64NV;
extern PFNGLVERTEXATTRIBL3UI64NVPROC glVertexAttribL3ui64NV;
extern PFNGLVERTEXATTRIBL4UI64NVPROC glVertexAttribL4ui64NV;
extern PFNGLVERTEXATTRIBL1UI64VNVPROC glVertexAttribL1ui64vNV;
extern PFNGLVERTEXATTRIBL2UI64VNVPROC glVertexAttribL2ui64vNV;
extern PFNGLVERTEXATTRIBL3UI64VNVPROC glVertexAttribL3ui64vNV;
extern PFNGLVERTEXATTRIBL4UI64VNVPROC glVertexAttribL4ui64vNV;
extern PFNGLGETVERTEXATTRIBLI64VNVPROC glGetVertexAttribLi64vNV;
extern PFNGLGETVERTEXATTRIBLUI64VNVPROC glGetVertexAttribLui64vNV;
extern PFNGLVERTEXATTRIBLFORMATNVPROC glVertexAttribLFormatNV;


/******************************
* Extension: GL_NV_vertex_buffer_unified_memory
******************************/

#define GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV 0x8F1E
#define GL_ELEMENT_ARRAY_UNIFIED_NV 0x8F1F
#define GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV 0x8F20
#define GL_VERTEX_ARRAY_ADDRESS_NV 0x8F21
#define GL_NORMAL_ARRAY_ADDRESS_NV 0x8F22
#define GL_COLOR_ARRAY_ADDRESS_NV 0x8F23
#define GL_INDEX_ARRAY_ADDRESS_NV 0x8F24
#define GL_TEXTURE_COORD_ARRAY_ADDRESS_NV 0x8F25
#define GL_EDGE_FLAG_ARRAY_ADDRESS_NV 0x8F26
#define GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV 0x8F27
#define GL_FOG_COORD_ARRAY_ADDRESS_NV 0x8F28
#define GL_ELEMENT_ARRAY_ADDRESS_NV 0x8F29
#define GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV 0x8F2A
#define GL_VERTEX_ARRAY_LENGTH_NV 0x8F2B
#define GL_NORMAL_ARRAY_LENGTH_NV 0x8F2C
#define GL_COLOR_ARRAY_LENGTH_NV 0x8F2D
#define GL_INDEX_ARRAY_LENGTH_NV 0x8F2E
#define GL_TEXTURE_COORD_ARRAY_LENGTH_NV 0x8F2F
#define GL_EDGE_FLAG_ARRAY_LENGTH_NV 0x8F30
#define GL_SECONDARY_COLOR_ARRAY_LENGTH_NV 0x8F31
#define GL_FOG_COORD_ARRAY_LENGTH_NV 0x8F32
#define GL_ELEMENT_ARRAY_LENGTH_NV 0x8F33
#define GL_DRAW_INDIRECT_UNIFIED_NV 0x8F40
#define GL_DRAW_INDIRECT_ADDRESS_NV 0x8F41
#define GL_DRAW_INDIRECT_LENGTH_NV 0x8F42


typedef void (GLE_FUNCPTR * PFNGLBUFFERADDRESSRANGENVPROC)(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length);
typedef void (GLE_FUNCPTR * PFNGLVERTEXFORMATNVPROC)(GLint size, GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLNORMALFORMATNVPROC)(GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLCOLORFORMATNVPROC)(GLint size, GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLINDEXFORMATNVPROC)(GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDFORMATNVPROC)(GLint size, GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGFORMATNVPROC)(GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORFORMATNVPROC)(GLint size, GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFORMATNVPROC)(GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBFORMATNVPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBIFORMATNVPROC)(GLuint index, GLint size, GLenum type, GLsizei stride);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERUI64I_VNVPROC)(GLenum value, GLuint index, GLuint64EXT *result);

extern PFNGLBUFFERADDRESSRANGENVPROC glBufferAddressRangeNV;
extern PFNGLVERTEXFORMATNVPROC glVertexFormatNV;
extern PFNGLNORMALFORMATNVPROC glNormalFormatNV;
extern PFNGLCOLORFORMATNVPROC glColorFormatNV;
extern PFNGLINDEXFORMATNVPROC glIndexFormatNV;
extern PFNGLTEXCOORDFORMATNVPROC glTexCoordFormatNV;
extern PFNGLEDGEFLAGFORMATNVPROC glEdgeFlagFormatNV;
extern PFNGLSECONDARYCOLORFORMATNVPROC glSecondaryColorFormatNV;
extern PFNGLFOGCOORDFORMATNVPROC glFogCoordFormatNV;
extern PFNGLVERTEXATTRIBFORMATNVPROC glVertexAttribFormatNV;
extern PFNGLVERTEXATTRIBIFORMATNVPROC glVertexAttribIFormatNV;
extern PFNGLGETINTEGERUI64I_VNVPROC glGetIntegerui64i_vNV;


/******************************
* Extension: GL_NV_vertex_program
******************************/

#define GL_VERTEX_PROGRAM_NV 0x8620
#define GL_VERTEX_STATE_PROGRAM_NV 0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV 0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV 0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV 0x8625
#define GL_CURRENT_ATTRIB_NV 0x8626
#define GL_PROGRAM_LENGTH_NV 0x8627
#define GL_PROGRAM_STRING_NV 0x8628
#define GL_MODELVIEW_PROJECTION_NV 0x8629
#define GL_IDENTITY_NV 0x862A
#define GL_INVERSE_NV 0x862B
#define GL_TRANSPOSE_NV 0x862C
#define GL_INVERSE_TRANSPOSE_NV 0x862D
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV 0x862E
#define GL_MAX_TRACK_MATRICES_NV 0x862F
#define GL_MATRIX0_NV 0x8630
#define GL_MATRIX1_NV 0x8631
#define GL_MATRIX2_NV 0x8632
#define GL_MATRIX3_NV 0x8633
#define GL_MATRIX4_NV 0x8634
#define GL_MATRIX5_NV 0x8635
#define GL_MATRIX6_NV 0x8636
#define GL_MATRIX7_NV 0x8637
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV 0x8640
#define GL_CURRENT_MATRIX_NV 0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV 0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV 0x8643
#define GL_PROGRAM_PARAMETER_NV 0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV 0x8645
#define GL_PROGRAM_TARGET_NV 0x8646
#define GL_PROGRAM_RESIDENT_NV 0x8647
#define GL_TRACK_MATRIX_NV 0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV 0x8649
#define GL_VERTEX_PROGRAM_BINDING_NV 0x864A
#define GL_PROGRAM_ERROR_POSITION_NV 0x864B
#define GL_VERTEX_ATTRIB_ARRAY0_NV 0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV 0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV 0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV 0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV 0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV 0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV 0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV 0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV 0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV 0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV 0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV 0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV 0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV 0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV 0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV 0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV 0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV 0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV 0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV 0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV 0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV 0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV 0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV 0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV 0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV 0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV 0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV 0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV 0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV 0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV 0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV 0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV 0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV 0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV 0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV 0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV 0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV 0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV 0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV 0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV 0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV 0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV 0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV 0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV 0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV 0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV 0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV 0x867F


typedef GLboolean (GLE_FUNCPTR * PFNGLAREPROGRAMSRESIDENTNVPROC)(GLsizei n, const GLuint *programs, GLboolean *residences);
typedef void (GLE_FUNCPTR * PFNGLBINDPROGRAMNVPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETEPROGRAMSNVPROC)(GLsizei n, const GLuint *programs);
typedef void (GLE_FUNCPTR * PFNGLEXECUTEPROGRAMNVPROC)(GLenum target, GLuint id, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGENPROGRAMSNVPROC)(GLsizei n, GLuint *programs);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMPARAMETERDVNVPROC)(GLenum target, GLuint index, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMPARAMETERFVNVPROC)(GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMIVNVPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSTRINGNVPROC)(GLuint id, GLenum pname, GLubyte *program);
typedef void (GLE_FUNCPTR * PFNGLGETTRACKMATRIXIVNVPROC)(GLenum target, GLuint address, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBDVNVPROC)(GLuint index, GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBFVNVPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIVNVPROC)(GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBPOINTERVNVPROC)(GLuint index, GLenum pname, GLvoid* *pointer);
typedef GLboolean (GLE_FUNCPTR * PFNGLISPROGRAMNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLLOADPROGRAMNVPROC)(GLenum target, GLuint id, GLsizei len, const GLubyte *program);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETER4DNVPROC)(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETER4DVNVPROC)(GLenum target, GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETER4FNVPROC)(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETER4FVNVPROC)(GLenum target, GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERS4DVNVPROC)(GLenum target, GLuint index, GLuint count, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERS4FVNVPROC)(GLenum target, GLuint index, GLuint count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREQUESTRESIDENTPROGRAMSNVPROC)(GLsizei n, const GLuint *programs);
typedef void (GLE_FUNCPTR * PFNGLTRACKMATRIXNVPROC)(GLenum target, GLuint address, GLenum matrix, GLenum transform);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBPOINTERNVPROC)(GLuint index, GLint fsize, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DNVPROC)(GLuint index, GLdouble x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DVNVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FNVPROC)(GLuint index, GLfloat x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FVNVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SNVPROC)(GLuint index, GLshort x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SVNVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DNVPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DVNVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FNVPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FVNVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SNVPROC)(GLuint index, GLshort x, GLshort y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SVNVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DNVPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DVNVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FNVPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FVNVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SNVPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SVNVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DNVPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DVNVPROC)(GLuint index, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FNVPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FVNVPROC)(GLuint index, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SNVPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SVNVPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UBNVPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UBVNVPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS1DVNVPROC)(GLuint index, GLsizei count, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS1FVNVPROC)(GLuint index, GLsizei count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS1SVNVPROC)(GLuint index, GLsizei count, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS2DVNVPROC)(GLuint index, GLsizei count, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS2FVNVPROC)(GLuint index, GLsizei count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS2SVNVPROC)(GLuint index, GLsizei count, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS3DVNVPROC)(GLuint index, GLsizei count, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS3FVNVPROC)(GLuint index, GLsizei count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS3SVNVPROC)(GLuint index, GLsizei count, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS4DVNVPROC)(GLuint index, GLsizei count, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS4FVNVPROC)(GLuint index, GLsizei count, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS4SVNVPROC)(GLuint index, GLsizei count, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBS4UBVNVPROC)(GLuint index, GLsizei count, const GLubyte *v);

extern PFNGLAREPROGRAMSRESIDENTNVPROC glAreProgramsResidentNV;
extern PFNGLBINDPROGRAMNVPROC glBindProgramNV;
extern PFNGLDELETEPROGRAMSNVPROC glDeleteProgramsNV;
extern PFNGLEXECUTEPROGRAMNVPROC glExecuteProgramNV;
extern PFNGLGENPROGRAMSNVPROC glGenProgramsNV;
extern PFNGLGETPROGRAMPARAMETERDVNVPROC glGetProgramParameterdvNV;
extern PFNGLGETPROGRAMPARAMETERFVNVPROC glGetProgramParameterfvNV;
extern PFNGLGETPROGRAMIVNVPROC glGetProgramivNV;
extern PFNGLGETPROGRAMSTRINGNVPROC glGetProgramStringNV;
extern PFNGLGETTRACKMATRIXIVNVPROC glGetTrackMatrixivNV;
extern PFNGLGETVERTEXATTRIBDVNVPROC glGetVertexAttribdvNV;
extern PFNGLGETVERTEXATTRIBFVNVPROC glGetVertexAttribfvNV;
extern PFNGLGETVERTEXATTRIBIVNVPROC glGetVertexAttribivNV;
extern PFNGLGETVERTEXATTRIBPOINTERVNVPROC glGetVertexAttribPointervNV;
extern PFNGLISPROGRAMNVPROC glIsProgramNV;
extern PFNGLLOADPROGRAMNVPROC glLoadProgramNV;
extern PFNGLPROGRAMPARAMETER4DNVPROC glProgramParameter4dNV;
extern PFNGLPROGRAMPARAMETER4DVNVPROC glProgramParameter4dvNV;
extern PFNGLPROGRAMPARAMETER4FNVPROC glProgramParameter4fNV;
extern PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV;
extern PFNGLPROGRAMPARAMETERS4DVNVPROC glProgramParameters4dvNV;
extern PFNGLPROGRAMPARAMETERS4FVNVPROC glProgramParameters4fvNV;
extern PFNGLREQUESTRESIDENTPROGRAMSNVPROC glRequestResidentProgramsNV;
extern PFNGLTRACKMATRIXNVPROC glTrackMatrixNV;
extern PFNGLVERTEXATTRIBPOINTERNVPROC glVertexAttribPointerNV;
extern PFNGLVERTEXATTRIB1DNVPROC glVertexAttrib1dNV;
extern PFNGLVERTEXATTRIB1DVNVPROC glVertexAttrib1dvNV;
extern PFNGLVERTEXATTRIB1FNVPROC glVertexAttrib1fNV;
extern PFNGLVERTEXATTRIB1FVNVPROC glVertexAttrib1fvNV;
extern PFNGLVERTEXATTRIB1SNVPROC glVertexAttrib1sNV;
extern PFNGLVERTEXATTRIB1SVNVPROC glVertexAttrib1svNV;
extern PFNGLVERTEXATTRIB2DNVPROC glVertexAttrib2dNV;
extern PFNGLVERTEXATTRIB2DVNVPROC glVertexAttrib2dvNV;
extern PFNGLVERTEXATTRIB2FNVPROC glVertexAttrib2fNV;
extern PFNGLVERTEXATTRIB2FVNVPROC glVertexAttrib2fvNV;
extern PFNGLVERTEXATTRIB2SNVPROC glVertexAttrib2sNV;
extern PFNGLVERTEXATTRIB2SVNVPROC glVertexAttrib2svNV;
extern PFNGLVERTEXATTRIB3DNVPROC glVertexAttrib3dNV;
extern PFNGLVERTEXATTRIB3DVNVPROC glVertexAttrib3dvNV;
extern PFNGLVERTEXATTRIB3FNVPROC glVertexAttrib3fNV;
extern PFNGLVERTEXATTRIB3FVNVPROC glVertexAttrib3fvNV;
extern PFNGLVERTEXATTRIB3SNVPROC glVertexAttrib3sNV;
extern PFNGLVERTEXATTRIB3SVNVPROC glVertexAttrib3svNV;
extern PFNGLVERTEXATTRIB4DNVPROC glVertexAttrib4dNV;
extern PFNGLVERTEXATTRIB4DVNVPROC glVertexAttrib4dvNV;
extern PFNGLVERTEXATTRIB4FNVPROC glVertexAttrib4fNV;
extern PFNGLVERTEXATTRIB4FVNVPROC glVertexAttrib4fvNV;
extern PFNGLVERTEXATTRIB4SNVPROC glVertexAttrib4sNV;
extern PFNGLVERTEXATTRIB4SVNVPROC glVertexAttrib4svNV;
extern PFNGLVERTEXATTRIB4UBNVPROC glVertexAttrib4ubNV;
extern PFNGLVERTEXATTRIB4UBVNVPROC glVertexAttrib4ubvNV;
extern PFNGLVERTEXATTRIBS1DVNVPROC glVertexAttribs1dvNV;
extern PFNGLVERTEXATTRIBS1FVNVPROC glVertexAttribs1fvNV;
extern PFNGLVERTEXATTRIBS1SVNVPROC glVertexAttribs1svNV;
extern PFNGLVERTEXATTRIBS2DVNVPROC glVertexAttribs2dvNV;
extern PFNGLVERTEXATTRIBS2FVNVPROC glVertexAttribs2fvNV;
extern PFNGLVERTEXATTRIBS2SVNVPROC glVertexAttribs2svNV;
extern PFNGLVERTEXATTRIBS3DVNVPROC glVertexAttribs3dvNV;
extern PFNGLVERTEXATTRIBS3FVNVPROC glVertexAttribs3fvNV;
extern PFNGLVERTEXATTRIBS3SVNVPROC glVertexAttribs3svNV;
extern PFNGLVERTEXATTRIBS4DVNVPROC glVertexAttribs4dvNV;
extern PFNGLVERTEXATTRIBS4FVNVPROC glVertexAttribs4fvNV;
extern PFNGLVERTEXATTRIBS4SVNVPROC glVertexAttribs4svNV;
extern PFNGLVERTEXATTRIBS4UBVNVPROC glVertexAttribs4ubvNV;


/******************************
* Extension: GL_NV_vertex_program1_1
******************************/

/******************************
* Extension: GL_NV_vertex_program2
******************************/

/******************************
* Extension: GL_NV_vertex_program2_option
******************************/

#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV 0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV 0x88F5


/******************************
* Extension: GL_NV_vertex_program3
******************************/

#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB 0x8B4C


/******************************
* Extension: GL_NV_vertex_program4
******************************/

#define GL_VERTEX_ATTRIB_ARRAY_INTEGER_NV 0x88FD


typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IEXTPROC)(GLuint index, GLint x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IEXTPROC)(GLuint index, GLint x, GLint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IEXTPROC)(GLuint index, GLint x, GLint y, GLint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IEXTPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIEXTPROC)(GLuint index, GLuint x);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIEXTPROC)(GLuint index, GLuint x, GLuint y);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIEXTPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIEXTPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IVEXTPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IVEXTPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IVEXTPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IVEXTPROC)(GLuint index, const GLint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIVEXTPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIVEXTPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIVEXTPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIVEXTPROC)(GLuint index, const GLuint *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4BVEXTPROC)(GLuint index, const GLbyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4SVEXTPROC)(GLuint index, const GLshort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UBVEXTPROC)(GLuint index, const GLubyte *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4USVEXTPROC)(GLuint index, const GLushort *v);
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBIPOINTEREXTPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIIVEXTPROC)(GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIUIVEXTPROC)(GLuint index, GLenum pname, GLuint *params);

extern PFNGLVERTEXATTRIBI1IEXTPROC glVertexAttribI1iEXT;
extern PFNGLVERTEXATTRIBI2IEXTPROC glVertexAttribI2iEXT;
extern PFNGLVERTEXATTRIBI3IEXTPROC glVertexAttribI3iEXT;
extern PFNGLVERTEXATTRIBI4IEXTPROC glVertexAttribI4iEXT;
extern PFNGLVERTEXATTRIBI1UIEXTPROC glVertexAttribI1uiEXT;
extern PFNGLVERTEXATTRIBI2UIEXTPROC glVertexAttribI2uiEXT;
extern PFNGLVERTEXATTRIBI3UIEXTPROC glVertexAttribI3uiEXT;
extern PFNGLVERTEXATTRIBI4UIEXTPROC glVertexAttribI4uiEXT;
extern PFNGLVERTEXATTRIBI1IVEXTPROC glVertexAttribI1ivEXT;
extern PFNGLVERTEXATTRIBI2IVEXTPROC glVertexAttribI2ivEXT;
extern PFNGLVERTEXATTRIBI3IVEXTPROC glVertexAttribI3ivEXT;
extern PFNGLVERTEXATTRIBI4IVEXTPROC glVertexAttribI4ivEXT;
extern PFNGLVERTEXATTRIBI1UIVEXTPROC glVertexAttribI1uivEXT;
extern PFNGLVERTEXATTRIBI2UIVEXTPROC glVertexAttribI2uivEXT;
extern PFNGLVERTEXATTRIBI3UIVEXTPROC glVertexAttribI3uivEXT;
extern PFNGLVERTEXATTRIBI4UIVEXTPROC glVertexAttribI4uivEXT;
extern PFNGLVERTEXATTRIBI4BVEXTPROC glVertexAttribI4bvEXT;
extern PFNGLVERTEXATTRIBI4SVEXTPROC glVertexAttribI4svEXT;
extern PFNGLVERTEXATTRIBI4UBVEXTPROC glVertexAttribI4ubvEXT;
extern PFNGLVERTEXATTRIBI4USVEXTPROC glVertexAttribI4usvEXT;
extern PFNGLVERTEXATTRIBIPOINTEREXTPROC glVertexAttribIPointerEXT;
extern PFNGLGETVERTEXATTRIBIIVEXTPROC glGetVertexAttribIivEXT;
extern PFNGLGETVERTEXATTRIBIUIVEXTPROC glGetVertexAttribIuivEXT;


/******************************
* Extension: GL_NV_video_capture
******************************/

#define GL_VIDEO_BUFFER_NV 0x9020
#define GL_VIDEO_BUFFER_BINDING_NV 0x9021
#define GL_FIELD_UPPER_NV 0x9022
#define GL_FIELD_LOWER_NV 0x9023
#define GL_NUM_VIDEO_CAPTURE_STREAMS_NV 0x9024
#define GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV 0x9025
#define GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV 0x9026
#define GL_LAST_VIDEO_CAPTURE_STATUS_NV 0x9027
#define GL_VIDEO_BUFFER_PITCH_NV 0x9028
#define GL_VIDEO_COLOR_CONVERSION_MATRIX_NV 0x9029
#define GL_VIDEO_COLOR_CONVERSION_MAX_NV 0x902A
#define GL_VIDEO_COLOR_CONVERSION_MIN_NV 0x902B
#define GL_VIDEO_COLOR_CONVERSION_OFFSET_NV 0x902C
#define GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV 0x902D
#define GL_PARTIAL_SUCCESS_NV 0x902E
#define GL_SUCCESS_NV 0x902F
#define GL_FAILURE_NV 0x9030
#define GL_YCBYCR8_422_NV 0x9031
#define GL_YCBAYCR8A_4224_NV 0x9032
#define GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV 0x9033
#define GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV 0x9034
#define GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV 0x9035
#define GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV 0x9036
#define GL_Z4Y12Z4CB12Z4CR12_444_NV 0x9037
#define GL_VIDEO_CAPTURE_FRAME_WIDTH_NV 0x9038
#define GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV 0x9039
#define GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV 0x903A
#define GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV 0x903B
#define GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV 0x903C


typedef void (GLE_FUNCPTR * PFNGLBEGINVIDEOCAPTURENVPROC)(GLuint video_capture_slot);
typedef void (GLE_FUNCPTR * PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset);
typedef void (GLE_FUNCPTR * PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLENDVIDEOCAPTURENVPROC)(GLuint video_capture_slot);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOCAPTUREIVNVPROC)(GLuint video_capture_slot, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble *params);
typedef GLenum (GLE_FUNCPTR * PFNGLVIDEOCAPTURENVPROC)(GLuint video_capture_slot, GLuint *sequence_num, GLuint64EXT *capture_time);
typedef void (GLE_FUNCPTR * PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble *params);

extern PFNGLBEGINVIDEOCAPTURENVPROC glBeginVideoCaptureNV;
extern PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC glBindVideoCaptureStreamBufferNV;
extern PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC glBindVideoCaptureStreamTextureNV;
extern PFNGLENDVIDEOCAPTURENVPROC glEndVideoCaptureNV;
extern PFNGLGETVIDEOCAPTUREIVNVPROC glGetVideoCaptureivNV;
extern PFNGLGETVIDEOCAPTURESTREAMIVNVPROC glGetVideoCaptureStreamivNV;
extern PFNGLGETVIDEOCAPTURESTREAMFVNVPROC glGetVideoCaptureStreamfvNV;
extern PFNGLGETVIDEOCAPTURESTREAMDVNVPROC glGetVideoCaptureStreamdvNV;
extern PFNGLVIDEOCAPTURENVPROC glVideoCaptureNV;
extern PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC glVideoCaptureStreamParameterivNV;
extern PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC glVideoCaptureStreamParameterfvNV;
extern PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC glVideoCaptureStreamParameterdvNV;


/******************************
* Extension: GL_OES_read_format
******************************/

#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B


/******************************
* Extension: GL_OML_interlace
******************************/

#define GL_INTERLACE_OML 0x8980
#define GL_INTERLACE_READ_OML 0x8981


/******************************
* Extension: GL_OML_resample
******************************/

#define GL_PACK_RESAMPLE_OML 0x8984
#define GL_UNPACK_RESAMPLE_OML 0x8985
#define GL_RESAMPLE_REPLICATE_OML 0x8986
#define GL_RESAMPLE_ZERO_FILL_OML 0x8987
#define GL_RESAMPLE_AVERAGE_OML 0x8988
#define GL_RESAMPLE_DECIMATE_OML 0x8989


/******************************
* Extension: GL_OML_subsample
******************************/

#define GL_FORMAT_SUBSAMPLE_24_24_OML 0x8982
#define GL_FORMAT_SUBSAMPLE_244_244_OML 0x8983


/******************************
* Extension: GL_PGI_misc_hints
******************************/

#define GL_PREFER_DOUBLEBUFFER_HINT_PGI 0x1A1F8
#define GL_CONSERVE_MEMORY_HINT_PGI 0x1A1FD
#define GL_RECLAIM_MEMORY_HINT_PGI 0x1A1FE
#define GL_NATIVE_GRAPHICS_HANDLE_PGI 0x1A202
#define GL_NATIVE_GRAPHICS_BEGIN_HINT_PGI 0x1A203
#define GL_NATIVE_GRAPHICS_END_HINT_PGI 0x1A204
#define GL_ALWAYS_FAST_HINT_PGI 0x1A20C
#define GL_ALWAYS_SOFT_HINT_PGI 0x1A20D
#define GL_ALLOW_DRAW_OBJ_HINT_PGI 0x1A20E
#define GL_ALLOW_DRAW_WIN_HINT_PGI 0x1A20F
#define GL_ALLOW_DRAW_FRG_HINT_PGI 0x1A210
#define GL_ALLOW_DRAW_MEM_HINT_PGI 0x1A211
#define GL_STRICT_DEPTHFUNC_HINT_PGI 0x1A216
#define GL_STRICT_LIGHTING_HINT_PGI 0x1A217
#define GL_STRICT_SCISSOR_HINT_PGI 0x1A218
#define GL_FULL_STIPPLE_HINT_PGI 0x1A219
#define GL_CLIP_NEAR_HINT_PGI 0x1A220
#define GL_CLIP_FAR_HINT_PGI 0x1A221
#define GL_WIDE_LINE_HINT_PGI 0x1A222
#define GL_BACK_NORMALS_HINT_PGI 0x1A223


typedef void (GLE_FUNCPTR * PFNGLHINTPGIPROC)(GLenum target, GLint mode);

extern PFNGLHINTPGIPROC glHintPGI;


/******************************
* Extension: GL_PGI_vertex_hints
******************************/

#define GL_VERTEX_DATA_HINT_PGI 0x1A22A
#define GL_VERTEX_CONSISTENT_HINT_PGI 0x1A22B
#define GL_MATERIAL_SIDE_HINT_PGI 0x1A22C
#define GL_MAX_VERTEX_HINT_PGI 0x1A22D
#define GL_COLOR3_BIT_PGI 0x00010000
#define GL_COLOR4_BIT_PGI 0x00020000
#define GL_EDGEFLAG_BIT_PGI 0x00040000
#define GL_INDEX_BIT_PGI 0x00080000
#define GL_MAT_AMBIENT_BIT_PGI 0x00100000
#define GL_MAT_AMBIENT_AND_DIFFUSE_BIT_PGI 0x00200000
#define GL_MAT_DIFFUSE_BIT_PGI 0x00400000
#define GL_MAT_EMISSION_BIT_PGI 0x00800000
#define GL_MAT_COLOR_INDEXES_BIT_PGI 0x01000000
#define GL_MAT_SHININESS_BIT_PGI 0x02000000
#define GL_MAT_SPECULAR_BIT_PGI 0x04000000
#define GL_NORMAL_BIT_PGI 0x08000000
#define GL_TEXCOORD1_BIT_PGI 0x10000000
#define GL_TEXCOORD2_BIT_PGI 0x20000000
#define GL_TEXCOORD3_BIT_PGI 0x40000000
#define GL_TEXCOORD4_BIT_PGI 0x80000000
#define GL_VERTEX23_BIT_PGI 0x00000004
#define GL_VERTEX4_BIT_PGI 0x00000008


/******************************
* Extension: GL_REND_screen_coordinates
******************************/

#define GL_SCREEN_COORDINATES_REND 0x8490
#define GL_INVERTED_SCREEN_W_REND 0x8491


/******************************
* Extension: GL_S3_s3tc
******************************/

#define GL_RGB_S3TC 0x83A0
#define GL_RGB4_S3TC 0x83A1
#define GL_RGBA_S3TC 0x83A2
#define GL_RGBA4_S3TC 0x83A3


/******************************
* Extension: GL_SGIS_detail_texture
******************************/

#define GL_DETAIL_TEXTURE_2D_SGIS 0x8095
#define GL_DETAIL_TEXTURE_2D_BINDING_SGIS 0x8096
#define GL_LINEAR_DETAIL_SGIS 0x8097
#define GL_LINEAR_DETAIL_ALPHA_SGIS 0x8098
#define GL_LINEAR_DETAIL_COLOR_SGIS 0x8099
#define GL_DETAIL_TEXTURE_LEVEL_SGIS 0x809A
#define GL_DETAIL_TEXTURE_MODE_SGIS 0x809B
#define GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS 0x809C


typedef void (GLE_FUNCPTR * PFNGLDETAILTEXFUNCSGISPROC)(GLenum target, GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETDETAILTEXFUNCSGISPROC)(GLenum target, GLfloat *points);

extern PFNGLDETAILTEXFUNCSGISPROC glDetailTexFuncSGIS;
extern PFNGLGETDETAILTEXFUNCSGISPROC glGetDetailTexFuncSGIS;


/******************************
* Extension: GL_SGIS_fog_function
******************************/

#define GL_FOG_FUNC_SGIS 0x812A
#define GL_FOG_FUNC_POINTS_SGIS 0x812B
#define GL_MAX_FOG_FUNC_POINTS_SGIS 0x812C


typedef void (GLE_FUNCPTR * PFNGLFOGFUNCSGISPROC)(GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETFOGFUNCSGISPROC)(GLfloat *points);

extern PFNGLFOGFUNCSGISPROC glFogFuncSGIS;
extern PFNGLGETFOGFUNCSGISPROC glGetFogFuncSGIS;


/******************************
* Extension: GL_SGIS_generate_mipmap
******************************/

#define GL_GENERATE_MIPMAP_SGIS 0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS 0x8192


/******************************
* Extension: GL_SGIS_multisample
******************************/

#define GL_MULTISAMPLE_SGIS 0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_SGIS 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_SGIS 0x809F
#define GL_SAMPLE_MASK_SGIS 0x80A0
#define GL_1PASS_SGIS 0x80A1
#define GL_2PASS_0_SGIS 0x80A2
#define GL_2PASS_1_SGIS 0x80A3
#define GL_4PASS_0_SGIS 0x80A4
#define GL_4PASS_1_SGIS 0x80A5
#define GL_4PASS_2_SGIS 0x80A6
#define GL_4PASS_3_SGIS 0x80A7
#define GL_SAMPLE_BUFFERS_SGIS 0x80A8
#define GL_SAMPLES_SGIS 0x80A9
#define GL_SAMPLE_MASK_VALUE_SGIS 0x80AA
#define GL_SAMPLE_MASK_INVERT_SGIS 0x80AB
#define GL_SAMPLE_PATTERN_SGIS 0x80AC


typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKSGISPROC)(GLclampf value, GLboolean invert);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEPATTERNSGISPROC)(GLenum pattern);

extern PFNGLSAMPLEMASKSGISPROC glSampleMaskSGIS;
extern PFNGLSAMPLEPATTERNSGISPROC glSamplePatternSGIS;


/******************************
* Extension: GL_SGIS_pixel_texture
******************************/

#define GL_PIXEL_TEXTURE_SGIS 0x8353
#define GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS 0x8354
#define GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS 0x8355
#define GL_PIXEL_GROUP_COLOR_SGIS 0x8356


typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERISGISPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERIVSGISPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERFSGISPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERFVSGISPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)(GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)(GLenum pname, GLfloat *params);

extern PFNGLPIXELTEXGENPARAMETERISGISPROC glPixelTexGenParameteriSGIS;
extern PFNGLPIXELTEXGENPARAMETERIVSGISPROC glPixelTexGenParameterivSGIS;
extern PFNGLPIXELTEXGENPARAMETERFSGISPROC glPixelTexGenParameterfSGIS;
extern PFNGLPIXELTEXGENPARAMETERFVSGISPROC glPixelTexGenParameterfvSGIS;
extern PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC glGetPixelTexGenParameterivSGIS;
extern PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC glGetPixelTexGenParameterfvSGIS;


/******************************
* Extension: GL_SGIS_point_line_texgen
******************************/

#define GL_EYE_DISTANCE_TO_POINT_SGIS 0x81F0
#define GL_OBJECT_DISTANCE_TO_POINT_SGIS 0x81F1
#define GL_EYE_DISTANCE_TO_LINE_SGIS 0x81F2
#define GL_OBJECT_DISTANCE_TO_LINE_SGIS 0x81F3
#define GL_EYE_POINT_SGIS 0x81F4
#define GL_OBJECT_POINT_SGIS 0x81F5
#define GL_EYE_LINE_SGIS 0x81F6
#define GL_OBJECT_LINE_SGIS 0x81F7


/******************************
* Extension: GL_SGIS_point_parameters
******************************/

#define GL_POINT_SIZE_MIN_SGIS 0x8126
#define GL_POINT_SIZE_MAX_SGIS 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_SGIS 0x8128
#define GL_DISTANCE_ATTENUATION_SGIS 0x8129


typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFSGISPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVSGISPROC)(GLenum pname, const GLfloat *params);

extern PFNGLPOINTPARAMETERFSGISPROC glPointParameterfSGIS;
extern PFNGLPOINTPARAMETERFVSGISPROC glPointParameterfvSGIS;


/******************************
* Extension: GL_SGIS_sharpen_texture
******************************/

#define GL_LINEAR_SHARPEN_SGIS 0x80AD
#define GL_LINEAR_SHARPEN_ALPHA_SGIS 0x80AE
#define GL_LINEAR_SHARPEN_COLOR_SGIS 0x80AF
#define GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS 0x80B0


typedef void (GLE_FUNCPTR * PFNGLSHARPENTEXFUNCSGISPROC)(GLenum target, GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETSHARPENTEXFUNCSGISPROC)(GLenum target, GLfloat *points);

extern PFNGLSHARPENTEXFUNCSGISPROC glSharpenTexFuncSGIS;
extern PFNGLGETSHARPENTEXFUNCSGISPROC glGetSharpenTexFuncSGIS;


/******************************
* Extension: GL_SGIS_texture4D
******************************/

#define GL_PACK_SKIP_VOLUMES_SGIS 0x8130
#define GL_PACK_IMAGE_DEPTH_SGIS 0x8131
#define GL_UNPACK_SKIP_VOLUMES_SGIS 0x8132
#define GL_UNPACK_IMAGE_DEPTH_SGIS 0x8133
#define GL_TEXTURE_4D_SGIS 0x8134
#define GL_PROXY_TEXTURE_4D_SGIS 0x8135
#define GL_TEXTURE_4DSIZE_SGIS 0x8136
#define GL_TEXTURE_WRAP_Q_SGIS 0x8137
#define GL_MAX_4D_TEXTURE_SIZE_SGIS 0x8138
#define GL_TEXTURE_4D_BINDING_SGIS 0x814F


typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE4DSGISPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE4DSGISPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid *pixels);

extern PFNGLTEXIMAGE4DSGISPROC glTexImage4DSGIS;
extern PFNGLTEXSUBIMAGE4DSGISPROC glTexSubImage4DSGIS;


/******************************
* Extension: GL_SGIS_texture_border_clamp
******************************/

#define GL_CLAMP_TO_BORDER_SGIS 0x812D


/******************************
* Extension: GL_SGIS_texture_color_mask
******************************/

#define GL_TEXTURE_COLOR_WRITEMASK_SGIS 0x81EF


typedef void (GLE_FUNCPTR * PFNGLTEXTURECOLORMASKSGISPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

extern PFNGLTEXTURECOLORMASKSGISPROC glTextureColorMaskSGIS;


/******************************
* Extension: GL_SGIS_texture_edge_clamp
******************************/

#define GL_CLAMP_TO_EDGE_SGIS 0x812F


/******************************
* Extension: GL_SGIS_texture_filter4
******************************/

#define GL_FILTER4_SGIS 0x8146
#define GL_TEXTURE_FILTER4_SIZE_SGIS 0x8147


typedef void (GLE_FUNCPTR * PFNGLGETTEXFILTERFUNCSGISPROC)(GLenum target, GLenum filter, GLfloat *weights);
typedef void (GLE_FUNCPTR * PFNGLTEXFILTERFUNCSGISPROC)(GLenum target, GLenum filter, GLsizei n, const GLfloat *weights);

extern PFNGLGETTEXFILTERFUNCSGISPROC glGetTexFilterFuncSGIS;
extern PFNGLTEXFILTERFUNCSGISPROC glTexFilterFuncSGIS;


/******************************
* Extension: GL_SGIS_texture_lod
******************************/

#define GL_TEXTURE_MIN_LOD_SGIS 0x813A
#define GL_TEXTURE_MAX_LOD_SGIS 0x813B
#define GL_TEXTURE_BASE_LEVEL_SGIS 0x813C
#define GL_TEXTURE_MAX_LEVEL_SGIS 0x813D


/******************************
* Extension: GL_SGIS_texture_select
******************************/

#define GL_DUAL_ALPHA4_SGIS 0x8110
#define GL_DUAL_ALPHA8_SGIS 0x8111
#define GL_DUAL_ALPHA12_SGIS 0x8112
#define GL_DUAL_ALPHA16_SGIS 0x8113
#define GL_DUAL_LUMINANCE4_SGIS 0x8114
#define GL_DUAL_LUMINANCE8_SGIS 0x8115
#define GL_DUAL_LUMINANCE12_SGIS 0x8116
#define GL_DUAL_LUMINANCE16_SGIS 0x8117
#define GL_DUAL_INTENSITY4_SGIS 0x8118
#define GL_DUAL_INTENSITY8_SGIS 0x8119
#define GL_DUAL_INTENSITY12_SGIS 0x811A
#define GL_DUAL_INTENSITY16_SGIS 0x811B
#define GL_DUAL_LUMINANCE_ALPHA4_SGIS 0x811C
#define GL_DUAL_LUMINANCE_ALPHA8_SGIS 0x811D
#define GL_QUAD_ALPHA4_SGIS 0x811E
#define GL_QUAD_ALPHA8_SGIS 0x811F
#define GL_QUAD_LUMINANCE4_SGIS 0x8120
#define GL_QUAD_LUMINANCE8_SGIS 0x8121
#define GL_QUAD_INTENSITY4_SGIS 0x8122
#define GL_QUAD_INTENSITY8_SGIS 0x8123
#define GL_DUAL_TEXTURE_SELECT_SGIS 0x8124
#define GL_QUAD_TEXTURE_SELECT_SGIS 0x8125


/******************************
* Extension: GL_SGIX_async
******************************/

#define GL_ASYNC_MARKER_SGIX 0x8329


typedef void (GLE_FUNCPTR * PFNGLASYNCMARKERSGIXPROC)(GLuint marker);
typedef GLint (GLE_FUNCPTR * PFNGLFINISHASYNCSGIXPROC)(GLuint *markerp);
typedef GLint (GLE_FUNCPTR * PFNGLPOLLASYNCSGIXPROC)(GLuint *markerp);
typedef GLuint (GLE_FUNCPTR * PFNGLGENASYNCMARKERSSGIXPROC)(GLsizei range);
typedef void (GLE_FUNCPTR * PFNGLDELETEASYNCMARKERSSGIXPROC)(GLuint marker, GLsizei range);
typedef GLboolean (GLE_FUNCPTR * PFNGLISASYNCMARKERSGIXPROC)(GLuint marker);

extern PFNGLASYNCMARKERSGIXPROC glAsyncMarkerSGIX;
extern PFNGLFINISHASYNCSGIXPROC glFinishAsyncSGIX;
extern PFNGLPOLLASYNCSGIXPROC glPollAsyncSGIX;
extern PFNGLGENASYNCMARKERSSGIXPROC glGenAsyncMarkersSGIX;
extern PFNGLDELETEASYNCMARKERSSGIXPROC glDeleteAsyncMarkersSGIX;
extern PFNGLISASYNCMARKERSGIXPROC glIsAsyncMarkerSGIX;


/******************************
* Extension: GL_SGIX_async_histogram
******************************/

#define GL_ASYNC_HISTOGRAM_SGIX 0x832C
#define GL_MAX_ASYNC_HISTOGRAM_SGIX 0x832D


/******************************
* Extension: GL_SGIX_async_pixel
******************************/

#define GL_ASYNC_TEX_IMAGE_SGIX 0x835C
#define GL_ASYNC_DRAW_PIXELS_SGIX 0x835D
#define GL_ASYNC_READ_PIXELS_SGIX 0x835E
#define GL_MAX_ASYNC_TEX_IMAGE_SGIX 0x835F
#define GL_MAX_ASYNC_DRAW_PIXELS_SGIX 0x8360
#define GL_MAX_ASYNC_READ_PIXELS_SGIX 0x8361


/******************************
* Extension: GL_SGIX_blend_alpha_minmax
******************************/

#define GL_ALPHA_MIN_SGIX 0x8320
#define GL_ALPHA_MAX_SGIX 0x8321


/******************************
* Extension: GL_SGIX_calligraphic_fragment
******************************/

#define GL_CALLIGRAPHIC_FRAGMENT_SGIX 0x8183


/******************************
* Extension: GL_SGIX_clipmap
******************************/

#define GL_LINEAR_CLIPMAP_LINEAR_SGIX 0x8170
#define GL_TEXTURE_CLIPMAP_CENTER_SGIX 0x8171
#define GL_TEXTURE_CLIPMAP_FRAME_SGIX 0x8172
#define GL_TEXTURE_CLIPMAP_OFFSET_SGIX 0x8173
#define GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX 0x8174
#define GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX 0x8175
#define GL_TEXTURE_CLIPMAP_DEPTH_SGIX 0x8176
#define GL_MAX_CLIPMAP_DEPTH_SGIX 0x8177
#define GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX 0x8178
#define GL_NEAREST_CLIPMAP_NEAREST_SGIX 0x844D
#define GL_NEAREST_CLIPMAP_LINEAR_SGIX 0x844E
#define GL_LINEAR_CLIPMAP_NEAREST_SGIX 0x844F


/******************************
* Extension: GL_SGIX_convolution_accuracy
******************************/

#define GL_CONVOLUTION_HINT_SGIX 0x8316


/******************************
* Extension: GL_SGIX_depth_texture
******************************/

#define GL_DEPTH_COMPONENT16_SGIX 0x81A5
#define GL_DEPTH_COMPONENT24_SGIX 0x81A6
#define GL_DEPTH_COMPONENT32_SGIX 0x81A7


/******************************
* Extension: GL_SGIX_flush_raster
******************************/

typedef void (GLE_FUNCPTR * PFNGLFLUSHRASTERSGIXPROC)();

extern PFNGLFLUSHRASTERSGIXPROC glFlushRasterSGIX;


/******************************
* Extension: GL_SGIX_fog_offset
******************************/

#define GL_FOG_OFFSET_SGIX 0x8198
#define GL_FOG_OFFSET_VALUE_SGIX 0x8199


/******************************
* Extension: GL_SGIX_fog_scale
******************************/

#define GL_FOG_SCALE_SGIX 0x81FC
#define GL_FOG_SCALE_VALUE_SGIX 0x81FD


/******************************
* Extension: GL_SGIX_fragment_lighting
******************************/

#define GL_FRAGMENT_LIGHTING_SGIX 0x8400
#define GL_FRAGMENT_COLOR_MATERIAL_SGIX 0x8401
#define GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX 0x8402
#define GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX 0x8403
#define GL_MAX_FRAGMENT_LIGHTS_SGIX 0x8404
#define GL_MAX_ACTIVE_LIGHTS_SGIX 0x8405
#define GL_CURRENT_RASTER_NORMAL_SGIX 0x8406
#define GL_LIGHT_ENV_MODE_SGIX 0x8407
#define GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX 0x8408
#define GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX 0x8409
#define GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX 0x840A
#define GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX 0x840B
#define GL_FRAGMENT_LIGHT0_SGIX 0x840C
#define GL_FRAGMENT_LIGHT1_SGIX 0x840D
#define GL_FRAGMENT_LIGHT2_SGIX 0x840E
#define GL_FRAGMENT_LIGHT3_SGIX 0x840F
#define GL_FRAGMENT_LIGHT4_SGIX 0x8410
#define GL_FRAGMENT_LIGHT5_SGIX 0x8411
#define GL_FRAGMENT_LIGHT6_SGIX 0x8412
#define GL_FRAGMENT_LIGHT7_SGIX 0x8413


typedef void (GLE_FUNCPTR * PFNGLFRAGMENTCOLORMATERIALSGIXPROC)(GLenum face, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTFSGIXPROC)(GLenum light, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTFVSGIXPROC)(GLenum light, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTISGIXPROC)(GLenum light, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTIVSGIXPROC)(GLenum light, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTMODELFSGIXPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTMODELISGIXPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTMATERIALFSGIXPROC)(GLenum face, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTMATERIALFVSGIXPROC)(GLenum face, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTMATERIALISGIXPROC)(GLenum face, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFRAGMENTMATERIALIVSGIXPROC)(GLenum face, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETFRAGMENTLIGHTFVSGIXPROC)(GLenum light, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETFRAGMENTLIGHTIVSGIXPROC)(GLenum light, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETFRAGMENTMATERIALFVSGIXPROC)(GLenum face, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETFRAGMENTMATERIALIVSGIXPROC)(GLenum face, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLIGHTENVISGIXPROC)(GLenum pname, GLint param);

extern PFNGLFRAGMENTCOLORMATERIALSGIXPROC glFragmentColorMaterialSGIX;
extern PFNGLFRAGMENTLIGHTFSGIXPROC glFragmentLightfSGIX;
extern PFNGLFRAGMENTLIGHTFVSGIXPROC glFragmentLightfvSGIX;
extern PFNGLFRAGMENTLIGHTISGIXPROC glFragmentLightiSGIX;
extern PFNGLFRAGMENTLIGHTIVSGIXPROC glFragmentLightivSGIX;
extern PFNGLFRAGMENTLIGHTMODELFSGIXPROC glFragmentLightModelfSGIX;
extern PFNGLFRAGMENTLIGHTMODELFVSGIXPROC glFragmentLightModelfvSGIX;
extern PFNGLFRAGMENTLIGHTMODELISGIXPROC glFragmentLightModeliSGIX;
extern PFNGLFRAGMENTLIGHTMODELIVSGIXPROC glFragmentLightModelivSGIX;
extern PFNGLFRAGMENTMATERIALFSGIXPROC glFragmentMaterialfSGIX;
extern PFNGLFRAGMENTMATERIALFVSGIXPROC glFragmentMaterialfvSGIX;
extern PFNGLFRAGMENTMATERIALISGIXPROC glFragmentMaterialiSGIX;
extern PFNGLFRAGMENTMATERIALIVSGIXPROC glFragmentMaterialivSGIX;
extern PFNGLGETFRAGMENTLIGHTFVSGIXPROC glGetFragmentLightfvSGIX;
extern PFNGLGETFRAGMENTLIGHTIVSGIXPROC glGetFragmentLightivSGIX;
extern PFNGLGETFRAGMENTMATERIALFVSGIXPROC glGetFragmentMaterialfvSGIX;
extern PFNGLGETFRAGMENTMATERIALIVSGIXPROC glGetFragmentMaterialivSGIX;
extern PFNGLLIGHTENVISGIXPROC glLightEnviSGIX;


/******************************
* Extension: GL_SGIX_framezoom
******************************/

#define GL_FRAMEZOOM_SGIX 0x818B
#define GL_FRAMEZOOM_FACTOR_SGIX 0x818C
#define GL_MAX_FRAMEZOOM_FACTOR_SGIX 0x818D


typedef void (GLE_FUNCPTR * PFNGLFRAMEZOOMSGIXPROC)(GLint factor);

extern PFNGLFRAMEZOOMSGIXPROC glFrameZoomSGIX;


/******************************
* Extension: GL_SGIX_impact_pixel_texture
******************************/

#define GL_PIXEL_TEX_GEN_Q_CEILING_SGIX 0x8184
#define GL_PIXEL_TEX_GEN_Q_ROUND_SGIX 0x8185
#define GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX 0x8186
#define GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX 0x8187
#define GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX 0x8188
#define GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX 0x8189
#define GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX 0x818A


/******************************
* Extension: GL_SGIX_instruments
******************************/

#define GL_INSTRUMENT_BUFFER_POINTER_SGIX 0x8180
#define GL_INSTRUMENT_MEASUREMENTS_SGIX 0x8181


typedef GLint (GLE_FUNCPTR * PFNGLGETINSTRUMENTSSGIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLINSTRUMENTSBUFFERSGIXPROC)(GLsizei size, GLint *buffer);
typedef GLint (GLE_FUNCPTR * PFNGLPOLLINSTRUMENTSSGIXPROC)(GLint *marker_p);
typedef void (GLE_FUNCPTR * PFNGLREADINSTRUMENTSSGIXPROC)(GLint marker);
typedef void (GLE_FUNCPTR * PFNGLSTARTINSTRUMENTSSGIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLSTOPINSTRUMENTSSGIXPROC)(GLint marker);

extern PFNGLGETINSTRUMENTSSGIXPROC glGetInstrumentsSGIX;
extern PFNGLINSTRUMENTSBUFFERSGIXPROC glInstrumentsBufferSGIX;
extern PFNGLPOLLINSTRUMENTSSGIXPROC glPollInstrumentsSGIX;
extern PFNGLREADINSTRUMENTSSGIXPROC glReadInstrumentsSGIX;
extern PFNGLSTARTINSTRUMENTSSGIXPROC glStartInstrumentsSGIX;
extern PFNGLSTOPINSTRUMENTSSGIXPROC glStopInstrumentsSGIX;


/******************************
* Extension: GL_SGIX_interlace
******************************/

#define GL_INTERLACE_SGIX 0x8094


/******************************
* Extension: GL_SGIX_ir_instrument1
******************************/

#define GL_IR_INSTRUMENT1_SGIX 0x817F


/******************************
* Extension: GL_SGIX_list_priority
******************************/

#define GL_LIST_PRIORITY_SGIX 0x8182


typedef void (GLE_FUNCPTR * PFNGLGETLISTPARAMETERFVSGIXPROC)(GLuint list, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETLISTPARAMETERIVSGIXPROC)(GLuint list, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERFSGIXPROC)(GLuint list, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERFVSGIXPROC)(GLuint list, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERISGIXPROC)(GLuint list, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERIVSGIXPROC)(GLuint list, GLenum pname, const GLint *params);

extern PFNGLGETLISTPARAMETERFVSGIXPROC glGetListParameterfvSGIX;
extern PFNGLGETLISTPARAMETERIVSGIXPROC glGetListParameterivSGIX;
extern PFNGLLISTPARAMETERFSGIXPROC glListParameterfSGIX;
extern PFNGLLISTPARAMETERFVSGIXPROC glListParameterfvSGIX;
extern PFNGLLISTPARAMETERISGIXPROC glListParameteriSGIX;
extern PFNGLLISTPARAMETERIVSGIXPROC glListParameterivSGIX;


/******************************
* Extension: GL_SGIX_pixel_texture
******************************/

#define GL_PIXEL_TEX_GEN_SGIX 0x8139
#define GL_PIXEL_TEX_GEN_MODE_SGIX 0x832B


typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENSGIXPROC)(GLenum mode);

extern PFNGLPIXELTEXGENSGIXPROC glPixelTexGenSGIX;


/******************************
* Extension: GL_SGIX_pixel_tiles
******************************/

#define GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX 0x813E
#define GL_PIXEL_TILE_CACHE_INCREMENT_SGIX 0x813F
#define GL_PIXEL_TILE_WIDTH_SGIX 0x8140
#define GL_PIXEL_TILE_HEIGHT_SGIX 0x8141
#define GL_PIXEL_TILE_GRID_WIDTH_SGIX 0x8142
#define GL_PIXEL_TILE_GRID_HEIGHT_SGIX 0x8143
#define GL_PIXEL_TILE_GRID_DEPTH_SGIX 0x8144
#define GL_PIXEL_TILE_CACHE_SIZE_SGIX 0x8145


/******************************
* Extension: GL_SGIX_polynomial_ffd
******************************/

#define GL_GEOMETRY_DEFORMATION_SGIX 0x8194
#define GL_TEXTURE_DEFORMATION_SGIX 0x8195
#define GL_DEFORMATIONS_MASK_SGIX 0x8196
#define GL_MAX_DEFORMATION_ORDER_SGIX 0x8197


typedef void (GLE_FUNCPTR * PFNGLDEFORMATIONMAP3DSGIXPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLDEFORMATIONMAP3FSGIXPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLDEFORMSGIXPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)(GLbitfield mask);

extern PFNGLDEFORMATIONMAP3DSGIXPROC glDeformationMap3dSGIX;
extern PFNGLDEFORMATIONMAP3FSGIXPROC glDeformationMap3fSGIX;
extern PFNGLDEFORMSGIXPROC glDeformSGIX;
extern PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC glLoadIdentityDeformationMapSGIX;


/******************************
* Extension: GL_SGIX_reference_plane
******************************/

#define GL_REFERENCE_PLANE_SGIX 0x817D
#define GL_REFERENCE_PLANE_EQUATION_SGIX 0x817E


typedef void (GLE_FUNCPTR * PFNGLREFERENCEPLANESGIXPROC)(const GLdouble *equation);

extern PFNGLREFERENCEPLANESGIXPROC glReferencePlaneSGIX;


/******************************
* Extension: GL_SGIX_resample
******************************/

#define GL_PACK_RESAMPLE_SGIX 0x842C
#define GL_UNPACK_RESAMPLE_SGIX 0x842D
#define GL_RESAMPLE_REPLICATE_SGIX 0x842E
#define GL_RESAMPLE_ZERO_FILL_SGIX 0x842F
#define GL_RESAMPLE_DECIMATE_SGIX 0x8430


/******************************
* Extension: GL_SGIX_scalebias_hint
******************************/

#define GL_SCALEBIAS_HINT_SGIX 0x8322


/******************************
* Extension: GL_SGIX_shadow
******************************/

#define GL_TEXTURE_COMPARE_SGIX 0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX 0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX 0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX 0x819D


/******************************
* Extension: GL_SGIX_shadow_ambient
******************************/

#define GL_SHADOW_AMBIENT_SGIX 0x80BF


/******************************
* Extension: GL_SGIX_sprite
******************************/

#define GL_SPRITE_SGIX 0x8148
#define GL_SPRITE_MODE_SGIX 0x8149
#define GL_SPRITE_AXIS_SGIX 0x814A
#define GL_SPRITE_TRANSLATION_SGIX 0x814B
#define GL_SPRITE_AXIAL_SGIX 0x814C
#define GL_SPRITE_OBJECT_ALIGNED_SGIX 0x814D
#define GL_SPRITE_EYE_ALIGNED_SGIX 0x814E


typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERFSGIXPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERFVSGIXPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERISGIXPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERIVSGIXPROC)(GLenum pname, const GLint *params);

extern PFNGLSPRITEPARAMETERFSGIXPROC glSpriteParameterfSGIX;
extern PFNGLSPRITEPARAMETERFVSGIXPROC glSpriteParameterfvSGIX;
extern PFNGLSPRITEPARAMETERISGIXPROC glSpriteParameteriSGIX;
extern PFNGLSPRITEPARAMETERIVSGIXPROC glSpriteParameterivSGIX;


/******************************
* Extension: GL_SGIX_subsample
******************************/

#define GL_PACK_SUBSAMPLE_RATE_SGIX 0x85A0
#define GL_UNPACK_SUBSAMPLE_RATE_SGIX 0x85A1
#define GL_PIXEL_SUBSAMPLE_4444_SGIX 0x85A2
#define GL_PIXEL_SUBSAMPLE_2424_SGIX 0x85A3
#define GL_PIXEL_SUBSAMPLE_4242_SGIX 0x85A4


/******************************
* Extension: GL_SGIX_tag_sample_buffer
******************************/

typedef void (GLE_FUNCPTR * PFNGLTAGSAMPLEBUFFERSGIXPROC)();

extern PFNGLTAGSAMPLEBUFFERSGIXPROC glTagSampleBufferSGIX;


/******************************
* Extension: GL_SGIX_texture_add_env
******************************/

#define GL_TEXTURE_ENV_BIAS_SGIX 0x80BE


/******************************
* Extension: GL_SGIX_texture_coordinate_clamp
******************************/

#define GL_TEXTURE_MAX_CLAMP_S_SGIX 0x8369
#define GL_TEXTURE_MAX_CLAMP_T_SGIX 0x836A
#define GL_TEXTURE_MAX_CLAMP_R_SGIX 0x836B


/******************************
* Extension: GL_SGIX_texture_lod_bias
******************************/

#define GL_TEXTURE_LOD_BIAS_S_SGIX 0x818E
#define GL_TEXTURE_LOD_BIAS_T_SGIX 0x818F
#define GL_TEXTURE_LOD_BIAS_R_SGIX 0x8190


/******************************
* Extension: GL_SGIX_texture_multi_buffer
******************************/

#define GL_TEXTURE_MULTI_BUFFER_HINT_SGIX 0x812E


/******************************
* Extension: GL_SGIX_texture_scale_bias
******************************/

#define GL_POST_TEXTURE_FILTER_BIAS_SGIX 0x8179
#define GL_POST_TEXTURE_FILTER_SCALE_SGIX 0x817A
#define GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX 0x817B
#define GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX 0x817C


/******************************
* Extension: GL_SGIX_vertex_preclip
******************************/

#define GL_VERTEX_PRECLIP_SGIX 0x83EE
#define GL_VERTEX_PRECLIP_HINT_SGIX 0x83EF


/******************************
* Extension: GL_SGIX_ycrcb
******************************/

#define GL_YCRCB_422_SGIX 0x81BB
#define GL_YCRCB_444_SGIX 0x81BC


/******************************
* Extension: GL_SGIX_ycrcb_subsample
******************************/

#define GL_PACK_SUBSAMPLE_RATE_SGIX 0x85A0
#define GL_UNPACK_SUBSAMPLE_RATE_SGIX 0x85A1
#define GL_PIXEL_SUBSAMPLE_4444_SGIX 0x85A2
#define GL_PIXEL_SUBSAMPLE_2424_SGIX 0x85A3
#define GL_PIXEL_SUBSAMPLE_4242_SGIX 0x85A4


/******************************
* Extension: GL_SGIX_ycrcba
******************************/

#define GL_YCRCB_SGIX 0x8318
#define GL_YCRCBA_SGIX 0x8319


/******************************
* Extension: GL_SGI_color_matrix
******************************/

#define GL_COLOR_MATRIX_SGI 0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH_SGI 0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI 0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE_SGI 0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI 0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI 0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI 0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS_SGI 0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI 0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI 0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI 0x80BB


/******************************
* Extension: GL_SGI_color_table
******************************/

#define GL_COLOR_TABLE_SGI 0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE_SGI 0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI 0x80D2
#define GL_PROXY_COLOR_TABLE_SGI 0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI 0x80D5
#define GL_COLOR_TABLE_SCALE_SGI 0x80D6
#define GL_COLOR_TABLE_BIAS_SGI 0x80D7
#define GL_COLOR_TABLE_FORMAT_SGI 0x80D8
#define GL_COLOR_TABLE_WIDTH_SGI 0x80D9
#define GL_COLOR_TABLE_RED_SIZE_SGI 0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_SGI 0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_SGI 0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_SGI 0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_SGI 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_SGI 0x80DF


typedef void (GLE_FUNCPTR * PFNGLCOLORTABLESGIPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERFVSGIPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERIVSGIPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORTABLESGIPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLESGIPROC)(GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)(GLenum target, GLenum pname, GLint *params);

extern PFNGLCOLORTABLESGIPROC glColorTableSGI;
extern PFNGLCOLORTABLEPARAMETERFVSGIPROC glColorTableParameterfvSGI;
extern PFNGLCOLORTABLEPARAMETERIVSGIPROC glColorTableParameterivSGI;
extern PFNGLCOPYCOLORTABLESGIPROC glCopyColorTableSGI;
extern PFNGLGETCOLORTABLESGIPROC glGetColorTableSGI;
extern PFNGLGETCOLORTABLEPARAMETERFVSGIPROC glGetColorTableParameterfvSGI;
extern PFNGLGETCOLORTABLEPARAMETERIVSGIPROC glGetColorTableParameterivSGI;


/******************************
* Extension: GL_SGI_depth_pass_instrument
******************************/

#define GL_DEPTH_PASS_INSTRUMENT_SGIX 0x8310
#define GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX 0x8311
#define GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX 0x8312


/******************************
* Extension: GL_SGI_texture_color_table
******************************/

#define GL_TEXTURE_COLOR_TABLE_SGI 0x80BC
#define GL_PROXY_TEXTURE_COLOR_TABLE_SGI 0x80BD


/******************************
* Extension: GL_SUNX_constant_data
******************************/

#define GL_UNPACK_CONSTANT_DATA_SUNX 0x81D5
#define GL_TEXTURE_CONSTANT_DATA_SUNX 0x81D6


typedef void (GLE_FUNCPTR * PFNGLFINISHTEXTURESUNXPROC)();

extern PFNGLFINISHTEXTURESUNXPROC glFinishTextureSUNX;


/******************************
* Extension: GL_SUN_convolution_border_modes
******************************/

#define GL_WRAP_BORDER_SUN 0x81D4


/******************************
* Extension: GL_SUN_global_alpha
******************************/

#define GL_GLOBAL_ALPHA_SUN 0x81D9
#define GL_GLOBAL_ALPHA_FACTOR_SUN 0x81DA


typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORBSUNPROC)(GLbyte factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORSSUNPROC)(GLshort factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORISUNPROC)(GLint factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORFSUNPROC)(GLfloat factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORDSUNPROC)(GLdouble factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUBSUNPROC)(GLubyte factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUSSUNPROC)(GLushort factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUISUNPROC)(GLuint factor);

extern PFNGLGLOBALALPHAFACTORBSUNPROC glGlobalAlphaFactorbSUN;
extern PFNGLGLOBALALPHAFACTORSSUNPROC glGlobalAlphaFactorsSUN;
extern PFNGLGLOBALALPHAFACTORISUNPROC glGlobalAlphaFactoriSUN;
extern PFNGLGLOBALALPHAFACTORFSUNPROC glGlobalAlphaFactorfSUN;
extern PFNGLGLOBALALPHAFACTORDSUNPROC glGlobalAlphaFactordSUN;
extern PFNGLGLOBALALPHAFACTORUBSUNPROC glGlobalAlphaFactorubSUN;
extern PFNGLGLOBALALPHAFACTORUSSUNPROC glGlobalAlphaFactorusSUN;
extern PFNGLGLOBALALPHAFACTORUISUNPROC glGlobalAlphaFactoruiSUN;


/******************************
* Extension: GL_SUN_mesh_array
******************************/

#define GL_QUAD_MESH_SUN 0x8614
#define GL_TRIANGLE_MESH_SUN 0x8615


typedef void (GLE_FUNCPTR * PFNGLDRAWMESHARRAYSSUNPROC)(GLenum mode, GLint first, GLsizei count, GLsizei width);

extern PFNGLDRAWMESHARRAYSSUNPROC glDrawMeshArraysSUN;


/******************************
* Extension: GL_SUN_slice_accum
******************************/

#define GL_SLICE_ACCUM_SUN 0x85CC


/******************************
* Extension: GL_SUN_triangle_list
******************************/

#define GL_RESTART_SUN 0x0001
#define GL_REPLACE_MIDDLE_SUN 0x0002
#define GL_REPLACE_OLDEST_SUN 0x0003
#define GL_TRIANGLE_LIST_SUN 0x81D7
#define GL_REPLACEMENT_CODE_SUN 0x81D8
#define GL_REPLACEMENT_CODE_ARRAY_SUN 0x85C0
#define GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN 0x85C1
#define GL_REPLACEMENT_CODE_ARRAY_STRIDE_SUN 0x85C2
#define GL_REPLACEMENT_CODE_ARRAY_POINTER_SUN 0x85C3
#define GL_R1UI_V3F_SUN 0x85C4
#define GL_R1UI_C4UB_V3F_SUN 0x85C5
#define GL_R1UI_C3F_V3F_SUN 0x85C6
#define GL_R1UI_N3F_V3F_SUN 0x85C7
#define GL_R1UI_C4F_N3F_V3F_SUN 0x85C8
#define GL_R1UI_T2F_V3F_SUN 0x85C9
#define GL_R1UI_T2F_N3F_V3F_SUN 0x85CA
#define GL_R1UI_T2F_C4F_N3F_V3F_SUN 0x85CB


typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUISUNPROC)(GLuint code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUSSUNPROC)(GLushort code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUBSUNPROC)(GLubyte code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUIVSUNPROC)(const GLuint *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUSVSUNPROC)(const GLushort *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUBVSUNPROC)(const GLubyte *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEPOINTERSUNPROC)(GLenum type, GLsizei stride, const GLvoid* *pointer);

extern PFNGLREPLACEMENTCODEUISUNPROC glReplacementCodeuiSUN;
extern PFNGLREPLACEMENTCODEUSSUNPROC glReplacementCodeusSUN;
extern PFNGLREPLACEMENTCODEUBSUNPROC glReplacementCodeubSUN;
extern PFNGLREPLACEMENTCODEUIVSUNPROC glReplacementCodeuivSUN;
extern PFNGLREPLACEMENTCODEUSVSUNPROC glReplacementCodeusvSUN;
extern PFNGLREPLACEMENTCODEUBVSUNPROC glReplacementCodeubvSUN;
extern PFNGLREPLACEMENTCODEPOINTERSUNPROC glReplacementCodePointerSUN;


/******************************
* Extension: GL_SUN_vertex
******************************/

typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVERTEX2FSUNPROC)(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVERTEX2FVSUNPROC)(const GLubyte *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVERTEX3FSUNPROC)(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVERTEX3FVSUNPROC)(const GLubyte *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FVERTEX3FSUNPROC)(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FVERTEX3FVSUNPROC)(const GLfloat *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FVERTEX3FSUNPROC)(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FVERTEX3FVSUNPROC)(const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FVERTEX3FSUNPROC)(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FVERTEX3FVSUNPROC)(const GLfloat *tc, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FVERTEX4FSUNPROC)(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FVERTEX4FVSUNPROC)(const GLfloat *tc, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC)(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC)(const GLfloat *tc, const GLubyte *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC)(const GLfloat *tc, const GLfloat *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC)(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat *tc, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC)(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC)(const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC)(GLuint rc, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC)(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC)(const GLuint *rc, const GLubyte *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC)(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *c, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC)(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC)(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *tc, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC)(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)(const GLuint *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v);

extern PFNGLCOLOR4UBVERTEX2FSUNPROC glColor4ubVertex2fSUN;
extern PFNGLCOLOR4UBVERTEX2FVSUNPROC glColor4ubVertex2fvSUN;
extern PFNGLCOLOR4UBVERTEX3FSUNPROC glColor4ubVertex3fSUN;
extern PFNGLCOLOR4UBVERTEX3FVSUNPROC glColor4ubVertex3fvSUN;
extern PFNGLCOLOR3FVERTEX3FSUNPROC glColor3fVertex3fSUN;
extern PFNGLCOLOR3FVERTEX3FVSUNPROC glColor3fVertex3fvSUN;
extern PFNGLNORMAL3FVERTEX3FSUNPROC glNormal3fVertex3fSUN;
extern PFNGLNORMAL3FVERTEX3FVSUNPROC glNormal3fVertex3fvSUN;
extern PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC glColor4fNormal3fVertex3fSUN;
extern PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC glColor4fNormal3fVertex3fvSUN;
extern PFNGLTEXCOORD2FVERTEX3FSUNPROC glTexCoord2fVertex3fSUN;
extern PFNGLTEXCOORD2FVERTEX3FVSUNPROC glTexCoord2fVertex3fvSUN;
extern PFNGLTEXCOORD4FVERTEX4FSUNPROC glTexCoord4fVertex4fSUN;
extern PFNGLTEXCOORD4FVERTEX4FVSUNPROC glTexCoord4fVertex4fvSUN;
extern PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC glTexCoord2fColor4ubVertex3fSUN;
extern PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC glTexCoord2fColor4ubVertex3fvSUN;
extern PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC glTexCoord2fColor3fVertex3fSUN;
extern PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC glTexCoord2fColor3fVertex3fvSUN;
extern PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC glTexCoord2fNormal3fVertex3fSUN;
extern PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC glTexCoord2fNormal3fVertex3fvSUN;
extern PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC glTexCoord2fColor4fNormal3fVertex3fSUN;
extern PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC glTexCoord2fColor4fNormal3fVertex3fvSUN;
extern PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC glTexCoord4fColor4fNormal3fVertex4fSUN;
extern PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC glTexCoord4fColor4fNormal3fVertex4fvSUN;
extern PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC glReplacementCodeuiVertex3fSUN;
extern PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC glReplacementCodeuiVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC glReplacementCodeuiColor4ubVertex3fSUN;
extern PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC glReplacementCodeuiColor4ubVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC glReplacementCodeuiColor3fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC glReplacementCodeuiColor3fVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC glReplacementCodeuiNormal3fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiNormal3fVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiColor4fNormal3fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiColor4fNormal3fVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN;
extern PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN;


/******************************
* Extension: GL_WIN_phong_shading
******************************/

#define GL_PHONG_WIN 0x80EA
#define GL_PHONG_HINT_WIN 0x80EB


/******************************
* Extension: GL_WIN_specular_fog
******************************/

#define GL_FOG_SPECULAR_TEXTURE_WIN 0x80EC


#ifdef __cplusplus
}
#endif //__cplusplus


#ifdef GLE_REMOVE_APIENTRY
	#undef GLE_REMOVE_APIENTRY
	#undef APIENTRY
#endif //GLE_REMOVE_APIENTRY

#endif //GL_3_2_COMP_H

