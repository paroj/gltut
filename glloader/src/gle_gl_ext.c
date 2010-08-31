#include <stdlib.h>
#include <string.h>
#include "gle_gl_ext.h"
#include "gle_gl_core.h"

#include <stddef.h>	
	
static int TestPointer(const void *pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

#if defined(__APPLE__)
#include <mach-o/dyld.h>

void* AppleGLGetProcAddress (const GLubyte *name)
{
  static const struct mach_header* image = NULL;
  NSSymbol symbol;
  char* symbolName;
  if (NULL == image)
  {
    image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
  }
  /* prepend a '_' for the Unix C symbol mangling convention */
  symbolName = malloc(strlen((const char*)name) + 2);
  strcpy(symbolName+1, (const char*)name);
  symbolName[0] = '_';
  symbol = NULL;
  /* if (NSIsSymbolNameDefined(symbolName))
	 symbol = NSLookupAndBindSymbol(symbolName); */
  symbol = image ? NSLookupSymbolInImage(image, symbolName, NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR) : NULL;
  free(symbolName);
  return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif //WIN32_LEAN_AND_MEAN
	#include <windows.h>
	
	#define gleIntGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#else
	#if defined(__APPLE__)
		#define gleIntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define gleIntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
			#define gleIntGetProcAddress(name) (*glXGetProcAddressARB)(name)
		#endif
	#endif
#endif

int glext_ARB_imaging = 0;
int glext_ARB_multitexture = 0;
int glext_ARB_transpose_matrix = 0;
int glext_ARB_multisample = 0;
int glext_ARB_texture_env_add = 0;
int glext_ARB_texture_cube_map = 0;
int glext_ARB_texture_compression = 0;
int glext_ARB_texture_border_clamp = 0;
int glext_ARB_point_parameters = 0;
int glext_ARB_vertex_blend = 0;
int glext_ARB_matrix_palette = 0;
int glext_ARB_texture_env_combine = 0;
int glext_ARB_texture_env_crossbar = 0;
int glext_ARB_texture_env_dot3 = 0;
int glext_ARB_texture_mirrored_repeat = 0;
int glext_ARB_depth_texture = 0;
int glext_ARB_shadow = 0;
int glext_ARB_shadow_ambient = 0;
int glext_ARB_window_pos = 0;
int glext_ARB_vertex_program = 0;
int glext_ARB_fragment_program = 0;
int glext_ARB_vertex_buffer_object = 0;
int glext_ARB_occlusion_query = 0;
int glext_ARB_shader_objects = 0;
int glext_ARB_vertex_shader = 0;
int glext_ARB_fragment_shader = 0;
int glext_ARB_shading_language_100 = 0;
int glext_ARB_texture_non_power_of_two = 0;
int glext_ARB_point_sprite = 0;
int glext_ARB_fragment_program_shadow = 0;
int glext_ARB_draw_buffers = 0;
int glext_ARB_texture_rectangle = 0;
int glext_ARB_color_buffer_float = 0;
int glext_ARB_half_float_pixel = 0;
int glext_ARB_texture_float = 0;
int glext_ARB_pixel_buffer_object = 0;
int glext_ARB_depth_buffer_float = 0;
int glext_ARB_draw_instanced = 0;
int glext_ARB_framebuffer_object = 0;
int glext_ARB_framebuffer_sRGB = 0;
int glext_ARB_geometry_shader4 = 0;
int glext_ARB_half_float_vertex = 0;
int glext_ARB_instanced_arrays = 0;
int glext_ARB_map_buffer_range = 0;
int glext_ARB_texture_buffer_object = 0;
int glext_ARB_texture_compression_rgtc = 0;
int glext_ARB_texture_rg = 0;
int glext_ARB_vertex_array_object = 0;
int glext_ARB_uniform_buffer_object = 0;
int glext_ARB_compatibility = 0;
int glext_ARB_copy_buffer = 0;
int glext_ARB_shader_texture_lod = 0;
int glext_ARB_depth_clamp = 0;
int glext_ARB_draw_elements_base_vertex = 0;
int glext_ARB_fragment_coord_conventions = 0;
int glext_ARB_provoking_vertex = 0;
int glext_ARB_seamless_cube_map = 0;
int glext_ARB_sync = 0;
int glext_ARB_texture_multisample = 0;
int glext_ARB_vertex_array_bgra = 0;
int glext_ARB_draw_buffers_blend = 0;
int glext_ARB_sample_shading = 0;
int glext_ARB_texture_cube_map_array = 0;
int glext_ARB_texture_gather = 0;
int glext_ARB_texture_query_lod = 0;
int glext_ARB_shading_language_include = 0;
int glext_ARB_texture_compression_bptc = 0;
int glext_ARB_blend_func_extended = 0;
int glext_ARB_explicit_attrib_location = 0;
int glext_ARB_occlusion_query2 = 0;
int glext_ARB_sampler_objects = 0;
int glext_ARB_shader_bit_encoding = 0;
int glext_ARB_texture_rgb10_a2ui = 0;
int glext_ARB_texture_swizzle = 0;
int glext_ARB_timer_query = 0;
int glext_ARB_vertex_type_2_10_10_10_rev = 0;
int glext_ARB_draw_indirect = 0;
int glext_ARB_gpu_shader5 = 0;
int glext_ARB_gpu_shader_fp64 = 0;
int glext_ARB_shader_subroutine = 0;
int glext_ARB_tessellation_shader = 0;
int glext_ARB_texture_buffer_object_rgb32 = 0;
int glext_ARB_transform_feedback2 = 0;
int glext_ARB_transform_feedback3 = 0;
int glext_ARB_ES2_compatibility = 0;
int glext_ARB_get_program_binary = 0;
int glext_ARB_separate_shader_objects = 0;
int glext_ARB_shader_precision = 0;
int glext_ARB_vertex_attrib_64bit = 0;
int glext_ARB_viewport_array = 0;
int glext_ARB_cl_event = 0;
int glext_ARB_debug_output = 0;
int glext_ARB_robustness = 0;
int glext_ARB_shader_stencil_export = 0;
int glext_EXT_abgr = 0;
int glext_EXT_blend_color = 0;
int glext_EXT_polygon_offset = 0;
int glext_EXT_texture = 0;
int glext_EXT_texture3D = 0;
int glext_SGIS_texture_filter4 = 0;
int glext_EXT_subtexture = 0;
int glext_EXT_copy_texture = 0;
int glext_EXT_histogram = 0;
int glext_EXT_convolution = 0;
int glext_SGI_color_matrix = 0;
int glext_SGI_color_table = 0;
int glext_SGIS_pixel_texture = 0;
int glext_SGIX_pixel_texture = 0;
int glext_SGIS_texture4D = 0;
int glext_SGI_texture_color_table = 0;
int glext_EXT_cmyka = 0;
int glext_EXT_texture_object = 0;
int glext_SGIS_detail_texture = 0;
int glext_SGIS_sharpen_texture = 0;
int glext_EXT_packed_pixels = 0;
int glext_SGIS_texture_lod = 0;
int glext_SGIS_multisample = 0;
int glext_EXT_rescale_normal = 0;
int glext_EXT_vertex_array = 0;
int glext_EXT_misc_attribute = 0;
int glext_SGIS_generate_mipmap = 0;
int glext_SGIX_clipmap = 0;
int glext_SGIX_shadow = 0;
int glext_SGIS_texture_edge_clamp = 0;
int glext_SGIS_texture_border_clamp = 0;
int glext_EXT_blend_minmax = 0;
int glext_EXT_blend_subtract = 0;
int glext_EXT_blend_logic_op = 0;
int glext_SGIX_interlace = 0;
int glext_SGIX_pixel_tiles = 0;
int glext_SGIS_texture_select = 0;
int glext_SGIX_sprite = 0;
int glext_SGIX_texture_multi_buffer = 0;
int glext_EXT_point_parameters = 0;
int glext_SGIS_point_parameters = 0;
int glext_SGIX_instruments = 0;
int glext_SGIX_texture_scale_bias = 0;
int glext_SGIX_framezoom = 0;
int glext_SGIX_tag_sample_buffer = 0;
int glext_FfdMaskSGIX = 0;
int glext_SGIX_polynomial_ffd = 0;
int glext_SGIX_reference_plane = 0;
int glext_SGIX_flush_raster = 0;
int glext_SGIX_depth_texture = 0;
int glext_SGIS_fog_function = 0;
int glext_SGIX_fog_offset = 0;
int glext_HP_image_transform = 0;
int glext_HP_convolution_border_modes = 0;
int glext_INGR_palette_buffer = 0;
int glext_SGIX_texture_add_env = 0;
int glext_EXT_color_subtable = 0;
int glext_PGI_vertex_hints = 0;
int glext_PGI_misc_hints = 0;
int glext_EXT_paletted_texture = 0;
int glext_EXT_clip_volume_hint = 0;
int glext_SGIX_list_priority = 0;
int glext_SGIX_ir_instrument1 = 0;
int glext_SGIX_calligraphic_fragment = 0;
int glext_SGIX_texture_lod_bias = 0;
int glext_SGIX_shadow_ambient = 0;
int glext_EXT_index_texture = 0;
int glext_EXT_index_material = 0;
int glext_EXT_index_func = 0;
int glext_EXT_index_array_formats = 0;
int glext_EXT_compiled_vertex_array = 0;
int glext_EXT_cull_vertex = 0;
int glext_SGIX_ycrcb = 0;
int glext_SGIX_fragment_lighting = 0;
int glext_IBM_rasterpos_clip = 0;
int glext_HP_texture_lighting = 0;
int glext_EXT_draw_range_elements = 0;
int glext_WIN_phong_shading = 0;
int glext_WIN_specular_fog = 0;
int glext_EXT_light_texture = 0;
int glext_SGIX_blend_alpha_minmax = 0;
int glext_SGIX_impact_pixel_texture = 0;
int glext_EXT_bgra = 0;
int glext_SGIX_async = 0;
int glext_SGIX_async_pixel = 0;
int glext_SGIX_async_histogram = 0;
int glext_INTEL_texture_scissor = 0;
int glext_INTEL_parallel_arrays = 0;
int glext_HP_occlusion_test = 0;
int glext_EXT_pixel_transform = 0;
int glext_EXT_pixel_transform_color_table = 0;
int glext_EXT_shared_texture_palette = 0;
int glext_EXT_separate_specular_color = 0;
int glext_EXT_secondary_color = 0;
int glext_EXT_texture_perturb_normal = 0;
int glext_EXT_multi_draw_arrays = 0;
int glext_EXT_fog_coord = 0;
int glext_REND_screen_coordinates = 0;
int glext_EXT_coordinate_frame = 0;
int glext_EXT_texture_env_combine = 0;
int glext_APPLE_specular_vector = 0;
int glext_APPLE_transform_hint = 0;
int glext_SGIX_fog_scale = 0;
int glext_SUNX_constant_data = 0;
int glext_SUN_global_alpha = 0;
int glext_SUN_triangle_list = 0;
int glext_SUN_vertex = 0;
int glext_EXT_blend_func_separate = 0;
int glext_INGR_color_clamp = 0;
int glext_INGR_interlace_read = 0;
int glext_EXT_stencil_wrap = 0;
int glext_EXT_422_pixels = 0;
int glext_NV_texgen_reflection = 0;
int glext_EXT_texture_cube_map = 0;
int glext_SUN_convolution_border_modes = 0;
int glext_EXT_texture_env_add = 0;
int glext_EXT_texture_lod_bias = 0;
int glext_EXT_texture_filter_anisotropic = 0;
int glext_EXT_vertex_weighting = 0;
int glext_NV_light_max_exponent = 0;
int glext_NV_vertex_array_range = 0;
int glext_NV_register_combiners = 0;
int glext_NV_fog_distance = 0;
int glext_NV_texgen_emboss = 0;
int glext_NV_blend_square = 0;
int glext_NV_texture_env_combine4 = 0;
int glext_MESA_resize_buffers = 0;
int glext_MESA_window_pos = 0;
int glext_EXT_texture_compression_s3tc = 0;
int glext_IBM_cull_vertex = 0;
int glext_IBM_multimode_draw_arrays = 0;
int glext_IBM_vertex_array_lists = 0;
int glext_SGIX_subsample = 0;
int glext_SGIX_ycrcb_subsample = 0;
int glext_SGIX_ycrcba = 0;
int glext_SGI_depth_pass_instrument = 0;
int glext_3DFX_texture_compression_FXT1 = 0;
int glext_3DFX_multisample = 0;
int glext_3DFX_tbuffer = 0;
int glext_EXT_multisample = 0;
int glext_SGIX_vertex_preclip = 0;
int glext_SGIX_convolution_accuracy = 0;
int glext_SGIX_resample = 0;
int glext_SGIS_point_line_texgen = 0;
int glext_SGIS_texture_color_mask = 0;
int glext_EXT_texture_env_dot3 = 0;
int glext_ATI_texture_mirror_once = 0;
int glext_NV_fence = 0;
int glext_IBM_texture_mirrored_repeat = 0;
int glext_NV_evaluators = 0;
int glext_NV_packed_depth_stencil = 0;
int glext_NV_register_combiners2 = 0;
int glext_NV_texture_compression_vtc = 0;
int glext_NV_texture_rectangle = 0;
int glext_NV_texture_shader = 0;
int glext_NV_texture_shader2 = 0;
int glext_NV_vertex_array_range2 = 0;
int glext_NV_vertex_program = 0;
int glext_SGIX_texture_coordinate_clamp = 0;
int glext_SGIX_scalebias_hint = 0;
int glext_OML_interlace = 0;
int glext_OML_subsample = 0;
int glext_OML_resample = 0;
int glext_NV_copy_depth_to_color = 0;
int glext_ATI_envmap_bumpmap = 0;
int glext_ATI_fragment_shader = 0;
int glext_ATI_pn_triangles = 0;
int glext_ATI_vertex_array_object = 0;
int glext_EXT_vertex_shader = 0;
int glext_ATI_vertex_streams = 0;
int glext_ATI_element_array = 0;
int glext_SUN_mesh_array = 0;
int glext_SUN_slice_accum = 0;
int glext_NV_multisample_filter_hint = 0;
int glext_NV_depth_clamp = 0;
int glext_NV_occlusion_query = 0;
int glext_NV_point_sprite = 0;
int glext_NV_texture_shader3 = 0;
int glext_NV_vertex_program1_1 = 0;
int glext_EXT_shadow_funcs = 0;
int glext_EXT_stencil_two_side = 0;
int glext_ATI_text_fragment_shader = 0;
int glext_APPLE_client_storage = 0;
int glext_APPLE_element_array = 0;
int glext_APPLE_fence = 0;
int glext_APPLE_vertex_array_object = 0;
int glext_APPLE_vertex_array_range = 0;
int glext_APPLE_ycbcr_422 = 0;
int glext_S3_s3tc = 0;
int glext_ATI_draw_buffers = 0;
int glext_ATI_pixel_format_float = 0;
int glext_ATI_texture_env_combine3 = 0;
int glext_ATI_texture_float = 0;
int glext_NV_float_buffer = 0;
int glext_NV_fragment_program = 0;
int glext_NV_half_float = 0;
int glext_NV_pixel_data_range = 0;
int glext_NV_primitive_restart = 0;
int glext_NV_texture_expand_normal = 0;
int glext_NV_vertex_program2 = 0;
int glext_ATI_map_object_buffer = 0;
int glext_ATI_separate_stencil = 0;
int glext_ATI_vertex_attrib_array_object = 0;
int glext_OES_read_format = 0;
int glext_EXT_depth_bounds_test = 0;
int glext_EXT_texture_mirror_clamp = 0;
int glext_EXT_blend_equation_separate = 0;
int glext_MESA_pack_invert = 0;
int glext_MESA_ycbcr_texture = 0;
int glext_EXT_pixel_buffer_object = 0;
int glext_NV_fragment_program_option = 0;
int glext_NV_fragment_program2 = 0;
int glext_NV_vertex_program2_option = 0;
int glext_NV_vertex_program3 = 0;
int glext_EXT_framebuffer_object = 0;
int glext_GREMEDY_string_marker = 0;
int glext_EXT_packed_depth_stencil = 0;
int glext_EXT_stencil_clear_tag = 0;
int glext_EXT_texture_sRGB = 0;
int glext_EXT_framebuffer_blit = 0;
int glext_EXT_framebuffer_multisample = 0;
int glext_MESAX_texture_stack = 0;
int glext_EXT_timer_query = 0;
int glext_EXT_gpu_program_parameters = 0;
int glext_APPLE_flush_buffer_range = 0;
int glext_NV_gpu_program4 = 0;
int glext_NV_geometry_program4 = 0;
int glext_EXT_geometry_shader4 = 0;
int glext_NV_vertex_program4 = 0;
int glext_EXT_gpu_shader4 = 0;
int glext_EXT_draw_instanced = 0;
int glext_EXT_packed_float = 0;
int glext_EXT_texture_array = 0;
int glext_EXT_texture_buffer_object = 0;
int glext_EXT_texture_compression_latc = 0;
int glext_EXT_texture_compression_rgtc = 0;
int glext_EXT_texture_shared_exponent = 0;
int glext_NV_depth_buffer_float = 0;
int glext_NV_fragment_program4 = 0;
int glext_NV_framebuffer_multisample_coverage = 0;
int glext_EXT_framebuffer_sRGB = 0;
int glext_NV_geometry_shader4 = 0;
int glext_NV_parameter_buffer_object = 0;
int glext_EXT_draw_buffers2 = 0;
int glext_NV_transform_feedback = 0;
int glext_EXT_bindable_uniform = 0;
int glext_EXT_texture_integer = 0;
int glext_GREMEDY_frame_terminator = 0;
int glext_NV_conditional_render = 0;
int glext_NV_present_video = 0;
int glext_EXT_transform_feedback = 0;
int glext_EXT_direct_state_access = 0;
int glext_EXT_vertex_array_bgra = 0;
int glext_EXT_texture_swizzle = 0;
int glext_NV_explicit_multisample = 0;
int glext_NV_transform_feedback2 = 0;
int glext_ATI_meminfo = 0;
int glext_AMD_performance_monitor = 0;
int glext_AMD_texture_texture4 = 0;
int glext_AMD_vertex_shader_tesselator = 0;
int glext_EXT_provoking_vertex = 0;
int glext_EXT_texture_snorm = 0;
int glext_AMD_draw_buffers_blend = 0;
int glext_APPLE_texture_range = 0;
int glext_APPLE_float_pixels = 0;
int glext_APPLE_vertex_program_evaluators = 0;
int glext_APPLE_aux_depth_stencil = 0;
int glext_APPLE_object_purgeable = 0;
int glext_APPLE_row_bytes = 0;
int glext_APPLE_rgb_422 = 0;
int glext_NV_video_capture = 0;
int glext_NV_copy_image = 0;
int glext_EXT_separate_shader_objects = 0;
int glext_NV_parameter_buffer_object2 = 0;
int glext_NV_shader_buffer_load = 0;
int glext_NV_vertex_buffer_unified_memory = 0;
int glext_NV_texture_barrier = 0;
int glext_AMD_shader_stencil_export = 0;
int glext_AMD_seamless_cubemap_per_texture = 0;
int glext_AMD_conservative_depth = 0;
int glext_EXT_shader_image_load_store = 0;
int glext_EXT_vertex_attrib_64bit = 0;
int glext_NV_gpu_program5 = 0;
int glext_NV_gpu_shader5 = 0;
int glext_NV_shader_buffer_store = 0;
int glext_NV_tessellation_program5 = 0;
int glext_NV_vertex_attrib_integer_64bit = 0;
int glext_NV_multisample_coverage = 0;
int glext_AMD_name_gen_delete = 0;
int glext_AMD_debug_output = 0;
int glext_NV_vdpau_interop = 0;
int glext_AMD_transform_feedback3_lines_triangles = 0;


void gleIntClear()
{
	glext_ARB_imaging = 0;
	glext_ARB_multitexture = 0;
	glext_ARB_transpose_matrix = 0;
	glext_ARB_multisample = 0;
	glext_ARB_texture_env_add = 0;
	glext_ARB_texture_cube_map = 0;
	glext_ARB_texture_compression = 0;
	glext_ARB_texture_border_clamp = 0;
	glext_ARB_point_parameters = 0;
	glext_ARB_vertex_blend = 0;
	glext_ARB_matrix_palette = 0;
	glext_ARB_texture_env_combine = 0;
	glext_ARB_texture_env_crossbar = 0;
	glext_ARB_texture_env_dot3 = 0;
	glext_ARB_texture_mirrored_repeat = 0;
	glext_ARB_depth_texture = 0;
	glext_ARB_shadow = 0;
	glext_ARB_shadow_ambient = 0;
	glext_ARB_window_pos = 0;
	glext_ARB_vertex_program = 0;
	glext_ARB_fragment_program = 0;
	glext_ARB_vertex_buffer_object = 0;
	glext_ARB_occlusion_query = 0;
	glext_ARB_shader_objects = 0;
	glext_ARB_vertex_shader = 0;
	glext_ARB_fragment_shader = 0;
	glext_ARB_shading_language_100 = 0;
	glext_ARB_texture_non_power_of_two = 0;
	glext_ARB_point_sprite = 0;
	glext_ARB_fragment_program_shadow = 0;
	glext_ARB_draw_buffers = 0;
	glext_ARB_texture_rectangle = 0;
	glext_ARB_color_buffer_float = 0;
	glext_ARB_half_float_pixel = 0;
	glext_ARB_texture_float = 0;
	glext_ARB_pixel_buffer_object = 0;
	glext_ARB_depth_buffer_float = 0;
	glext_ARB_draw_instanced = 0;
	glext_ARB_framebuffer_object = 0;
	glext_ARB_framebuffer_sRGB = 0;
	glext_ARB_geometry_shader4 = 0;
	glext_ARB_half_float_vertex = 0;
	glext_ARB_instanced_arrays = 0;
	glext_ARB_map_buffer_range = 0;
	glext_ARB_texture_buffer_object = 0;
	glext_ARB_texture_compression_rgtc = 0;
	glext_ARB_texture_rg = 0;
	glext_ARB_vertex_array_object = 0;
	glext_ARB_uniform_buffer_object = 0;
	glext_ARB_compatibility = 0;
	glext_ARB_copy_buffer = 0;
	glext_ARB_shader_texture_lod = 0;
	glext_ARB_depth_clamp = 0;
	glext_ARB_draw_elements_base_vertex = 0;
	glext_ARB_fragment_coord_conventions = 0;
	glext_ARB_provoking_vertex = 0;
	glext_ARB_seamless_cube_map = 0;
	glext_ARB_sync = 0;
	glext_ARB_texture_multisample = 0;
	glext_ARB_vertex_array_bgra = 0;
	glext_ARB_draw_buffers_blend = 0;
	glext_ARB_sample_shading = 0;
	glext_ARB_texture_cube_map_array = 0;
	glext_ARB_texture_gather = 0;
	glext_ARB_texture_query_lod = 0;
	glext_ARB_shading_language_include = 0;
	glext_ARB_texture_compression_bptc = 0;
	glext_ARB_blend_func_extended = 0;
	glext_ARB_explicit_attrib_location = 0;
	glext_ARB_occlusion_query2 = 0;
	glext_ARB_sampler_objects = 0;
	glext_ARB_shader_bit_encoding = 0;
	glext_ARB_texture_rgb10_a2ui = 0;
	glext_ARB_texture_swizzle = 0;
	glext_ARB_timer_query = 0;
	glext_ARB_vertex_type_2_10_10_10_rev = 0;
	glext_ARB_draw_indirect = 0;
	glext_ARB_gpu_shader5 = 0;
	glext_ARB_gpu_shader_fp64 = 0;
	glext_ARB_shader_subroutine = 0;
	glext_ARB_tessellation_shader = 0;
	glext_ARB_texture_buffer_object_rgb32 = 0;
	glext_ARB_transform_feedback2 = 0;
	glext_ARB_transform_feedback3 = 0;
	glext_ARB_ES2_compatibility = 0;
	glext_ARB_get_program_binary = 0;
	glext_ARB_separate_shader_objects = 0;
	glext_ARB_shader_precision = 0;
	glext_ARB_vertex_attrib_64bit = 0;
	glext_ARB_viewport_array = 0;
	glext_ARB_cl_event = 0;
	glext_ARB_debug_output = 0;
	glext_ARB_robustness = 0;
	glext_ARB_shader_stencil_export = 0;
	glext_EXT_abgr = 0;
	glext_EXT_blend_color = 0;
	glext_EXT_polygon_offset = 0;
	glext_EXT_texture = 0;
	glext_EXT_texture3D = 0;
	glext_SGIS_texture_filter4 = 0;
	glext_EXT_subtexture = 0;
	glext_EXT_copy_texture = 0;
	glext_EXT_histogram = 0;
	glext_EXT_convolution = 0;
	glext_SGI_color_matrix = 0;
	glext_SGI_color_table = 0;
	glext_SGIS_pixel_texture = 0;
	glext_SGIX_pixel_texture = 0;
	glext_SGIS_texture4D = 0;
	glext_SGI_texture_color_table = 0;
	glext_EXT_cmyka = 0;
	glext_EXT_texture_object = 0;
	glext_SGIS_detail_texture = 0;
	glext_SGIS_sharpen_texture = 0;
	glext_EXT_packed_pixels = 0;
	glext_SGIS_texture_lod = 0;
	glext_SGIS_multisample = 0;
	glext_EXT_rescale_normal = 0;
	glext_EXT_vertex_array = 0;
	glext_EXT_misc_attribute = 0;
	glext_SGIS_generate_mipmap = 0;
	glext_SGIX_clipmap = 0;
	glext_SGIX_shadow = 0;
	glext_SGIS_texture_edge_clamp = 0;
	glext_SGIS_texture_border_clamp = 0;
	glext_EXT_blend_minmax = 0;
	glext_EXT_blend_subtract = 0;
	glext_EXT_blend_logic_op = 0;
	glext_SGIX_interlace = 0;
	glext_SGIX_pixel_tiles = 0;
	glext_SGIS_texture_select = 0;
	glext_SGIX_sprite = 0;
	glext_SGIX_texture_multi_buffer = 0;
	glext_EXT_point_parameters = 0;
	glext_SGIS_point_parameters = 0;
	glext_SGIX_instruments = 0;
	glext_SGIX_texture_scale_bias = 0;
	glext_SGIX_framezoom = 0;
	glext_SGIX_tag_sample_buffer = 0;
	glext_FfdMaskSGIX = 0;
	glext_SGIX_polynomial_ffd = 0;
	glext_SGIX_reference_plane = 0;
	glext_SGIX_flush_raster = 0;
	glext_SGIX_depth_texture = 0;
	glext_SGIS_fog_function = 0;
	glext_SGIX_fog_offset = 0;
	glext_HP_image_transform = 0;
	glext_HP_convolution_border_modes = 0;
	glext_INGR_palette_buffer = 0;
	glext_SGIX_texture_add_env = 0;
	glext_EXT_color_subtable = 0;
	glext_PGI_vertex_hints = 0;
	glext_PGI_misc_hints = 0;
	glext_EXT_paletted_texture = 0;
	glext_EXT_clip_volume_hint = 0;
	glext_SGIX_list_priority = 0;
	glext_SGIX_ir_instrument1 = 0;
	glext_SGIX_calligraphic_fragment = 0;
	glext_SGIX_texture_lod_bias = 0;
	glext_SGIX_shadow_ambient = 0;
	glext_EXT_index_texture = 0;
	glext_EXT_index_material = 0;
	glext_EXT_index_func = 0;
	glext_EXT_index_array_formats = 0;
	glext_EXT_compiled_vertex_array = 0;
	glext_EXT_cull_vertex = 0;
	glext_SGIX_ycrcb = 0;
	glext_SGIX_fragment_lighting = 0;
	glext_IBM_rasterpos_clip = 0;
	glext_HP_texture_lighting = 0;
	glext_EXT_draw_range_elements = 0;
	glext_WIN_phong_shading = 0;
	glext_WIN_specular_fog = 0;
	glext_EXT_light_texture = 0;
	glext_SGIX_blend_alpha_minmax = 0;
	glext_SGIX_impact_pixel_texture = 0;
	glext_EXT_bgra = 0;
	glext_SGIX_async = 0;
	glext_SGIX_async_pixel = 0;
	glext_SGIX_async_histogram = 0;
	glext_INTEL_texture_scissor = 0;
	glext_INTEL_parallel_arrays = 0;
	glext_HP_occlusion_test = 0;
	glext_EXT_pixel_transform = 0;
	glext_EXT_pixel_transform_color_table = 0;
	glext_EXT_shared_texture_palette = 0;
	glext_EXT_separate_specular_color = 0;
	glext_EXT_secondary_color = 0;
	glext_EXT_texture_perturb_normal = 0;
	glext_EXT_multi_draw_arrays = 0;
	glext_EXT_fog_coord = 0;
	glext_REND_screen_coordinates = 0;
	glext_EXT_coordinate_frame = 0;
	glext_EXT_texture_env_combine = 0;
	glext_APPLE_specular_vector = 0;
	glext_APPLE_transform_hint = 0;
	glext_SGIX_fog_scale = 0;
	glext_SUNX_constant_data = 0;
	glext_SUN_global_alpha = 0;
	glext_SUN_triangle_list = 0;
	glext_SUN_vertex = 0;
	glext_EXT_blend_func_separate = 0;
	glext_INGR_color_clamp = 0;
	glext_INGR_interlace_read = 0;
	glext_EXT_stencil_wrap = 0;
	glext_EXT_422_pixels = 0;
	glext_NV_texgen_reflection = 0;
	glext_EXT_texture_cube_map = 0;
	glext_SUN_convolution_border_modes = 0;
	glext_EXT_texture_env_add = 0;
	glext_EXT_texture_lod_bias = 0;
	glext_EXT_texture_filter_anisotropic = 0;
	glext_EXT_vertex_weighting = 0;
	glext_NV_light_max_exponent = 0;
	glext_NV_vertex_array_range = 0;
	glext_NV_register_combiners = 0;
	glext_NV_fog_distance = 0;
	glext_NV_texgen_emboss = 0;
	glext_NV_blend_square = 0;
	glext_NV_texture_env_combine4 = 0;
	glext_MESA_resize_buffers = 0;
	glext_MESA_window_pos = 0;
	glext_EXT_texture_compression_s3tc = 0;
	glext_IBM_cull_vertex = 0;
	glext_IBM_multimode_draw_arrays = 0;
	glext_IBM_vertex_array_lists = 0;
	glext_SGIX_subsample = 0;
	glext_SGIX_ycrcb_subsample = 0;
	glext_SGIX_ycrcba = 0;
	glext_SGI_depth_pass_instrument = 0;
	glext_3DFX_texture_compression_FXT1 = 0;
	glext_3DFX_multisample = 0;
	glext_3DFX_tbuffer = 0;
	glext_EXT_multisample = 0;
	glext_SGIX_vertex_preclip = 0;
	glext_SGIX_convolution_accuracy = 0;
	glext_SGIX_resample = 0;
	glext_SGIS_point_line_texgen = 0;
	glext_SGIS_texture_color_mask = 0;
	glext_EXT_texture_env_dot3 = 0;
	glext_ATI_texture_mirror_once = 0;
	glext_NV_fence = 0;
	glext_IBM_texture_mirrored_repeat = 0;
	glext_NV_evaluators = 0;
	glext_NV_packed_depth_stencil = 0;
	glext_NV_register_combiners2 = 0;
	glext_NV_texture_compression_vtc = 0;
	glext_NV_texture_rectangle = 0;
	glext_NV_texture_shader = 0;
	glext_NV_texture_shader2 = 0;
	glext_NV_vertex_array_range2 = 0;
	glext_NV_vertex_program = 0;
	glext_SGIX_texture_coordinate_clamp = 0;
	glext_SGIX_scalebias_hint = 0;
	glext_OML_interlace = 0;
	glext_OML_subsample = 0;
	glext_OML_resample = 0;
	glext_NV_copy_depth_to_color = 0;
	glext_ATI_envmap_bumpmap = 0;
	glext_ATI_fragment_shader = 0;
	glext_ATI_pn_triangles = 0;
	glext_ATI_vertex_array_object = 0;
	glext_EXT_vertex_shader = 0;
	glext_ATI_vertex_streams = 0;
	glext_ATI_element_array = 0;
	glext_SUN_mesh_array = 0;
	glext_SUN_slice_accum = 0;
	glext_NV_multisample_filter_hint = 0;
	glext_NV_depth_clamp = 0;
	glext_NV_occlusion_query = 0;
	glext_NV_point_sprite = 0;
	glext_NV_texture_shader3 = 0;
	glext_NV_vertex_program1_1 = 0;
	glext_EXT_shadow_funcs = 0;
	glext_EXT_stencil_two_side = 0;
	glext_ATI_text_fragment_shader = 0;
	glext_APPLE_client_storage = 0;
	glext_APPLE_element_array = 0;
	glext_APPLE_fence = 0;
	glext_APPLE_vertex_array_object = 0;
	glext_APPLE_vertex_array_range = 0;
	glext_APPLE_ycbcr_422 = 0;
	glext_S3_s3tc = 0;
	glext_ATI_draw_buffers = 0;
	glext_ATI_pixel_format_float = 0;
	glext_ATI_texture_env_combine3 = 0;
	glext_ATI_texture_float = 0;
	glext_NV_float_buffer = 0;
	glext_NV_fragment_program = 0;
	glext_NV_half_float = 0;
	glext_NV_pixel_data_range = 0;
	glext_NV_primitive_restart = 0;
	glext_NV_texture_expand_normal = 0;
	glext_NV_vertex_program2 = 0;
	glext_ATI_map_object_buffer = 0;
	glext_ATI_separate_stencil = 0;
	glext_ATI_vertex_attrib_array_object = 0;
	glext_OES_read_format = 0;
	glext_EXT_depth_bounds_test = 0;
	glext_EXT_texture_mirror_clamp = 0;
	glext_EXT_blend_equation_separate = 0;
	glext_MESA_pack_invert = 0;
	glext_MESA_ycbcr_texture = 0;
	glext_EXT_pixel_buffer_object = 0;
	glext_NV_fragment_program_option = 0;
	glext_NV_fragment_program2 = 0;
	glext_NV_vertex_program2_option = 0;
	glext_NV_vertex_program3 = 0;
	glext_EXT_framebuffer_object = 0;
	glext_GREMEDY_string_marker = 0;
	glext_EXT_packed_depth_stencil = 0;
	glext_EXT_stencil_clear_tag = 0;
	glext_EXT_texture_sRGB = 0;
	glext_EXT_framebuffer_blit = 0;
	glext_EXT_framebuffer_multisample = 0;
	glext_MESAX_texture_stack = 0;
	glext_EXT_timer_query = 0;
	glext_EXT_gpu_program_parameters = 0;
	glext_APPLE_flush_buffer_range = 0;
	glext_NV_gpu_program4 = 0;
	glext_NV_geometry_program4 = 0;
	glext_EXT_geometry_shader4 = 0;
	glext_NV_vertex_program4 = 0;
	glext_EXT_gpu_shader4 = 0;
	glext_EXT_draw_instanced = 0;
	glext_EXT_packed_float = 0;
	glext_EXT_texture_array = 0;
	glext_EXT_texture_buffer_object = 0;
	glext_EXT_texture_compression_latc = 0;
	glext_EXT_texture_compression_rgtc = 0;
	glext_EXT_texture_shared_exponent = 0;
	glext_NV_depth_buffer_float = 0;
	glext_NV_fragment_program4 = 0;
	glext_NV_framebuffer_multisample_coverage = 0;
	glext_EXT_framebuffer_sRGB = 0;
	glext_NV_geometry_shader4 = 0;
	glext_NV_parameter_buffer_object = 0;
	glext_EXT_draw_buffers2 = 0;
	glext_NV_transform_feedback = 0;
	glext_EXT_bindable_uniform = 0;
	glext_EXT_texture_integer = 0;
	glext_GREMEDY_frame_terminator = 0;
	glext_NV_conditional_render = 0;
	glext_NV_present_video = 0;
	glext_EXT_transform_feedback = 0;
	glext_EXT_direct_state_access = 0;
	glext_EXT_vertex_array_bgra = 0;
	glext_EXT_texture_swizzle = 0;
	glext_NV_explicit_multisample = 0;
	glext_NV_transform_feedback2 = 0;
	glext_ATI_meminfo = 0;
	glext_AMD_performance_monitor = 0;
	glext_AMD_texture_texture4 = 0;
	glext_AMD_vertex_shader_tesselator = 0;
	glext_EXT_provoking_vertex = 0;
	glext_EXT_texture_snorm = 0;
	glext_AMD_draw_buffers_blend = 0;
	glext_APPLE_texture_range = 0;
	glext_APPLE_float_pixels = 0;
	glext_APPLE_vertex_program_evaluators = 0;
	glext_APPLE_aux_depth_stencil = 0;
	glext_APPLE_object_purgeable = 0;
	glext_APPLE_row_bytes = 0;
	glext_APPLE_rgb_422 = 0;
	glext_NV_video_capture = 0;
	glext_NV_copy_image = 0;
	glext_EXT_separate_shader_objects = 0;
	glext_NV_parameter_buffer_object2 = 0;
	glext_NV_shader_buffer_load = 0;
	glext_NV_vertex_buffer_unified_memory = 0;
	glext_NV_texture_barrier = 0;
	glext_AMD_shader_stencil_export = 0;
	glext_AMD_seamless_cubemap_per_texture = 0;
	glext_AMD_conservative_depth = 0;
	glext_EXT_shader_image_load_store = 0;
	glext_EXT_vertex_attrib_64bit = 0;
	glext_NV_gpu_program5 = 0;
	glext_NV_gpu_shader5 = 0;
	glext_NV_shader_buffer_store = 0;
	glext_NV_tessellation_program5 = 0;
	glext_NV_vertex_attrib_integer_64bit = 0;
	glext_NV_multisample_coverage = 0;
	glext_AMD_name_gen_delete = 0;
	glext_AMD_debug_output = 0;
	glext_NV_vdpau_interop = 0;
	glext_AMD_transform_feedback3_lines_triangles = 0;
}



typedef void (GLE_FUNCPTR * PFNGLTBUFFERMASK3DFXPROC)(GLuint mask);

PFNGLTBUFFERMASK3DFXPROC glTbufferMask3DFX;

static int gleIntLoad_3DFX_tbuffer()
{
	int bIsLoaded = 1;
	glTbufferMask3DFX = (PFNGLTBUFFERMASK3DFXPROC)gleIntGetProcAddress("glTbufferMask3DFX");
	if(!TestPointer(glTbufferMask3DFX)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEENABLEAMDPROC)(GLenum category, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEINSERTAMDPROC)(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar *buf);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECALLBACKAMDPROC)(GLDEBUGPROCAMD callback, GLvoid *userParam);
typedef GLuint (GLE_FUNCPTR * PFNGLGETDEBUGMESSAGELOGAMDPROC)(GLuint count, GLsizei bufsize, GLenum *categories, GLuint *severities, GLuint *ids, GLsizei *lengths, GLchar *message);

PFNGLDEBUGMESSAGEENABLEAMDPROC glDebugMessageEnableAMD;
PFNGLDEBUGMESSAGEINSERTAMDPROC glDebugMessageInsertAMD;
PFNGLDEBUGMESSAGECALLBACKAMDPROC glDebugMessageCallbackAMD;
PFNGLGETDEBUGMESSAGELOGAMDPROC glGetDebugMessageLogAMD;

static int gleIntLoad_AMD_debug_output()
{
	int bIsLoaded = 1;
	glDebugMessageEnableAMD = (PFNGLDEBUGMESSAGEENABLEAMDPROC)gleIntGetProcAddress("glDebugMessageEnableAMD");
	if(!TestPointer(glDebugMessageEnableAMD)) bIsLoaded = 0;
	glDebugMessageInsertAMD = (PFNGLDEBUGMESSAGEINSERTAMDPROC)gleIntGetProcAddress("glDebugMessageInsertAMD");
	if(!TestPointer(glDebugMessageInsertAMD)) bIsLoaded = 0;
	glDebugMessageCallbackAMD = (PFNGLDEBUGMESSAGECALLBACKAMDPROC)gleIntGetProcAddress("glDebugMessageCallbackAMD");
	if(!TestPointer(glDebugMessageCallbackAMD)) bIsLoaded = 0;
	glGetDebugMessageLogAMD = (PFNGLGETDEBUGMESSAGELOGAMDPROC)gleIntGetProcAddress("glGetDebugMessageLogAMD");
	if(!TestPointer(glGetDebugMessageLogAMD)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCINDEXEDAMDPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONINDEXEDAMDPROC)(GLuint buf, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);

PFNGLBLENDFUNCINDEXEDAMDPROC glBlendFuncIndexedAMD;
PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC glBlendFuncSeparateIndexedAMD;
PFNGLBLENDEQUATIONINDEXEDAMDPROC glBlendEquationIndexedAMD;
PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC glBlendEquationSeparateIndexedAMD;

static int gleIntLoad_AMD_draw_buffers_blend()
{
	int bIsLoaded = 1;
	glBlendFuncIndexedAMD = (PFNGLBLENDFUNCINDEXEDAMDPROC)gleIntGetProcAddress("glBlendFuncIndexedAMD");
	if(!TestPointer(glBlendFuncIndexedAMD)) bIsLoaded = 0;
	glBlendFuncSeparateIndexedAMD = (PFNGLBLENDFUNCSEPARATEINDEXEDAMDPROC)gleIntGetProcAddress("glBlendFuncSeparateIndexedAMD");
	if(!TestPointer(glBlendFuncSeparateIndexedAMD)) bIsLoaded = 0;
	glBlendEquationIndexedAMD = (PFNGLBLENDEQUATIONINDEXEDAMDPROC)gleIntGetProcAddress("glBlendEquationIndexedAMD");
	if(!TestPointer(glBlendEquationIndexedAMD)) bIsLoaded = 0;
	glBlendEquationSeparateIndexedAMD = (PFNGLBLENDEQUATIONSEPARATEINDEXEDAMDPROC)gleIntGetProcAddress("glBlendEquationSeparateIndexedAMD");
	if(!TestPointer(glBlendEquationSeparateIndexedAMD)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGENNAMESAMDPROC)(GLenum identifier, GLuint num, GLuint *names);
typedef void (GLE_FUNCPTR * PFNGLDELETENAMESAMDPROC)(GLenum identifier, GLuint num, const GLuint *names);
typedef GLboolean (GLE_FUNCPTR * PFNGLISNAMEAMDPROC)(GLenum identifier, GLuint name);

PFNGLGENNAMESAMDPROC glGenNamesAMD;
PFNGLDELETENAMESAMDPROC glDeleteNamesAMD;
PFNGLISNAMEAMDPROC glIsNameAMD;

static int gleIntLoad_AMD_name_gen_delete()
{
	int bIsLoaded = 1;
	glGenNamesAMD = (PFNGLGENNAMESAMDPROC)gleIntGetProcAddress("glGenNamesAMD");
	if(!TestPointer(glGenNamesAMD)) bIsLoaded = 0;
	glDeleteNamesAMD = (PFNGLDELETENAMESAMDPROC)gleIntGetProcAddress("glDeleteNamesAMD");
	if(!TestPointer(glDeleteNamesAMD)) bIsLoaded = 0;
	glIsNameAMD = (PFNGLISNAMEAMDPROC)gleIntGetProcAddress("glIsNameAMD");
	if(!TestPointer(glIsNameAMD)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGETPERFMONITORGROUPSAMDPROC glGetPerfMonitorGroupsAMD;
PFNGLGETPERFMONITORCOUNTERSAMDPROC glGetPerfMonitorCountersAMD;
PFNGLGETPERFMONITORGROUPSTRINGAMDPROC glGetPerfMonitorGroupStringAMD;
PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC glGetPerfMonitorCounterStringAMD;
PFNGLGETPERFMONITORCOUNTERINFOAMDPROC glGetPerfMonitorCounterInfoAMD;
PFNGLGENPERFMONITORSAMDPROC glGenPerfMonitorsAMD;
PFNGLDELETEPERFMONITORSAMDPROC glDeletePerfMonitorsAMD;
PFNGLSELECTPERFMONITORCOUNTERSAMDPROC glSelectPerfMonitorCountersAMD;
PFNGLBEGINPERFMONITORAMDPROC glBeginPerfMonitorAMD;
PFNGLENDPERFMONITORAMDPROC glEndPerfMonitorAMD;
PFNGLGETPERFMONITORCOUNTERDATAAMDPROC glGetPerfMonitorCounterDataAMD;

static int gleIntLoad_AMD_performance_monitor()
{
	int bIsLoaded = 1;
	glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC)gleIntGetProcAddress("glGetPerfMonitorGroupsAMD");
	if(!TestPointer(glGetPerfMonitorGroupsAMD)) bIsLoaded = 0;
	glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC)gleIntGetProcAddress("glGetPerfMonitorCountersAMD");
	if(!TestPointer(glGetPerfMonitorCountersAMD)) bIsLoaded = 0;
	glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)gleIntGetProcAddress("glGetPerfMonitorGroupStringAMD");
	if(!TestPointer(glGetPerfMonitorGroupStringAMD)) bIsLoaded = 0;
	glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)gleIntGetProcAddress("glGetPerfMonitorCounterStringAMD");
	if(!TestPointer(glGetPerfMonitorCounterStringAMD)) bIsLoaded = 0;
	glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)gleIntGetProcAddress("glGetPerfMonitorCounterInfoAMD");
	if(!TestPointer(glGetPerfMonitorCounterInfoAMD)) bIsLoaded = 0;
	glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC)gleIntGetProcAddress("glGenPerfMonitorsAMD");
	if(!TestPointer(glGenPerfMonitorsAMD)) bIsLoaded = 0;
	glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC)gleIntGetProcAddress("glDeletePerfMonitorsAMD");
	if(!TestPointer(glDeletePerfMonitorsAMD)) bIsLoaded = 0;
	glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)gleIntGetProcAddress("glSelectPerfMonitorCountersAMD");
	if(!TestPointer(glSelectPerfMonitorCountersAMD)) bIsLoaded = 0;
	glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC)gleIntGetProcAddress("glBeginPerfMonitorAMD");
	if(!TestPointer(glBeginPerfMonitorAMD)) bIsLoaded = 0;
	glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC)gleIntGetProcAddress("glEndPerfMonitorAMD");
	if(!TestPointer(glEndPerfMonitorAMD)) bIsLoaded = 0;
	glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)gleIntGetProcAddress("glGetPerfMonitorCounterDataAMD");
	if(!TestPointer(glGetPerfMonitorCounterDataAMD)) bIsLoaded = 0;
	return bIsLoaded;
}




typedef void (GLE_FUNCPTR * PFNGLTESSELLATIONFACTORAMDPROC)(GLfloat factor);
typedef void (GLE_FUNCPTR * PFNGLTESSELLATIONMODEAMDPROC)(GLenum mode);

PFNGLTESSELLATIONFACTORAMDPROC glTessellationFactorAMD;
PFNGLTESSELLATIONMODEAMDPROC glTessellationModeAMD;

static int gleIntLoad_AMD_vertex_shader_tesselator()
{
	int bIsLoaded = 1;
	glTessellationFactorAMD = (PFNGLTESSELLATIONFACTORAMDPROC)gleIntGetProcAddress("glTessellationFactorAMD");
	if(!TestPointer(glTessellationFactorAMD)) bIsLoaded = 0;
	glTessellationModeAMD = (PFNGLTESSELLATIONMODEAMDPROC)gleIntGetProcAddress("glTessellationModeAMD");
	if(!TestPointer(glTessellationModeAMD)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLELEMENTPOINTERAPPLEPROC)(GLenum type, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTARRAYAPPLEPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)(GLenum mode, GLuint start, GLuint end, const GLint *first, const GLsizei *count, GLsizei primcount);

PFNGLELEMENTPOINTERAPPLEPROC glElementPointerAPPLE;
PFNGLDRAWELEMENTARRAYAPPLEPROC glDrawElementArrayAPPLE;
PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC glDrawRangeElementArrayAPPLE;
PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC glMultiDrawElementArrayAPPLE;
PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC glMultiDrawRangeElementArrayAPPLE;

static int gleIntLoad_APPLE_element_array()
{
	int bIsLoaded = 1;
	glElementPointerAPPLE = (PFNGLELEMENTPOINTERAPPLEPROC)gleIntGetProcAddress("glElementPointerAPPLE");
	if(!TestPointer(glElementPointerAPPLE)) bIsLoaded = 0;
	glDrawElementArrayAPPLE = (PFNGLDRAWELEMENTARRAYAPPLEPROC)gleIntGetProcAddress("glDrawElementArrayAPPLE");
	if(!TestPointer(glDrawElementArrayAPPLE)) bIsLoaded = 0;
	glDrawRangeElementArrayAPPLE = (PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)gleIntGetProcAddress("glDrawRangeElementArrayAPPLE");
	if(!TestPointer(glDrawRangeElementArrayAPPLE)) bIsLoaded = 0;
	glMultiDrawElementArrayAPPLE = (PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)gleIntGetProcAddress("glMultiDrawElementArrayAPPLE");
	if(!TestPointer(glMultiDrawElementArrayAPPLE)) bIsLoaded = 0;
	glMultiDrawRangeElementArrayAPPLE = (PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)gleIntGetProcAddress("glMultiDrawRangeElementArrayAPPLE");
	if(!TestPointer(glMultiDrawRangeElementArrayAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGENFENCESAPPLEPROC)(GLsizei n, GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLDELETEFENCESAPPLEPROC)(GLsizei n, const GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLSETFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTFENCEAPPLEPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLFINISHFENCEAPPLEPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTOBJECTAPPLEPROC)(GLenum object, GLuint name);
typedef void (GLE_FUNCPTR * PFNGLFINISHOBJECTAPPLEPROC)(GLenum object, GLint name);

PFNGLGENFENCESAPPLEPROC glGenFencesAPPLE;
PFNGLDELETEFENCESAPPLEPROC glDeleteFencesAPPLE;
PFNGLSETFENCEAPPLEPROC glSetFenceAPPLE;
PFNGLISFENCEAPPLEPROC glIsFenceAPPLE;
PFNGLTESTFENCEAPPLEPROC glTestFenceAPPLE;
PFNGLFINISHFENCEAPPLEPROC glFinishFenceAPPLE;
PFNGLTESTOBJECTAPPLEPROC glTestObjectAPPLE;
PFNGLFINISHOBJECTAPPLEPROC glFinishObjectAPPLE;

static int gleIntLoad_APPLE_fence()
{
	int bIsLoaded = 1;
	glGenFencesAPPLE = (PFNGLGENFENCESAPPLEPROC)gleIntGetProcAddress("glGenFencesAPPLE");
	if(!TestPointer(glGenFencesAPPLE)) bIsLoaded = 0;
	glDeleteFencesAPPLE = (PFNGLDELETEFENCESAPPLEPROC)gleIntGetProcAddress("glDeleteFencesAPPLE");
	if(!TestPointer(glDeleteFencesAPPLE)) bIsLoaded = 0;
	glSetFenceAPPLE = (PFNGLSETFENCEAPPLEPROC)gleIntGetProcAddress("glSetFenceAPPLE");
	if(!TestPointer(glSetFenceAPPLE)) bIsLoaded = 0;
	glIsFenceAPPLE = (PFNGLISFENCEAPPLEPROC)gleIntGetProcAddress("glIsFenceAPPLE");
	if(!TestPointer(glIsFenceAPPLE)) bIsLoaded = 0;
	glTestFenceAPPLE = (PFNGLTESTFENCEAPPLEPROC)gleIntGetProcAddress("glTestFenceAPPLE");
	if(!TestPointer(glTestFenceAPPLE)) bIsLoaded = 0;
	glFinishFenceAPPLE = (PFNGLFINISHFENCEAPPLEPROC)gleIntGetProcAddress("glFinishFenceAPPLE");
	if(!TestPointer(glFinishFenceAPPLE)) bIsLoaded = 0;
	glTestObjectAPPLE = (PFNGLTESTOBJECTAPPLEPROC)gleIntGetProcAddress("glTestObjectAPPLE");
	if(!TestPointer(glTestObjectAPPLE)) bIsLoaded = 0;
	glFinishObjectAPPLE = (PFNGLFINISHOBJECTAPPLEPROC)gleIntGetProcAddress("glFinishObjectAPPLE");
	if(!TestPointer(glFinishObjectAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLBUFFERPARAMETERIAPPLEPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)(GLenum target, GLintptr offset, GLsizeiptr size);

PFNGLBUFFERPARAMETERIAPPLEPROC glBufferParameteriAPPLE;
PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC glFlushMappedBufferRangeAPPLE;

static int gleIntLoad_APPLE_flush_buffer_range()
{
	int bIsLoaded = 1;
	glBufferParameteriAPPLE = (PFNGLBUFFERPARAMETERIAPPLEPROC)gleIntGetProcAddress("glBufferParameteriAPPLE");
	if(!TestPointer(glBufferParameteriAPPLE)) bIsLoaded = 0;
	glFlushMappedBufferRangeAPPLE = (PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)gleIntGetProcAddress("glFlushMappedBufferRangeAPPLE");
	if(!TestPointer(glFlushMappedBufferRangeAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef GLenum (GLE_FUNCPTR * PFNGLOBJECTPURGEABLEAPPLEPROC)(GLenum objectType, GLuint name, GLenum option);
typedef GLenum (GLE_FUNCPTR * PFNGLOBJECTUNPURGEABLEAPPLEPROC)(GLenum objectType, GLuint name, GLenum option);
typedef void (GLE_FUNCPTR * PFNGLGETOBJECTPARAMETERIVAPPLEPROC)(GLenum objectType, GLuint name, GLenum pname, GLint *params);

PFNGLOBJECTPURGEABLEAPPLEPROC glObjectPurgeableAPPLE;
PFNGLOBJECTUNPURGEABLEAPPLEPROC glObjectUnpurgeableAPPLE;
PFNGLGETOBJECTPARAMETERIVAPPLEPROC glGetObjectParameterivAPPLE;

static int gleIntLoad_APPLE_object_purgeable()
{
	int bIsLoaded = 1;
	glObjectPurgeableAPPLE = (PFNGLOBJECTPURGEABLEAPPLEPROC)gleIntGetProcAddress("glObjectPurgeableAPPLE");
	if(!TestPointer(glObjectPurgeableAPPLE)) bIsLoaded = 0;
	glObjectUnpurgeableAPPLE = (PFNGLOBJECTUNPURGEABLEAPPLEPROC)gleIntGetProcAddress("glObjectUnpurgeableAPPLE");
	if(!TestPointer(glObjectUnpurgeableAPPLE)) bIsLoaded = 0;
	glGetObjectParameterivAPPLE = (PFNGLGETOBJECTPARAMETERIVAPPLEPROC)gleIntGetProcAddress("glGetObjectParameterivAPPLE");
	if(!TestPointer(glGetObjectParameterivAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLTEXTURERANGEAPPLEPROC)(GLenum target, GLsizei length, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)(GLenum target, GLenum pname, GLvoid* *params);

PFNGLTEXTURERANGEAPPLEPROC glTextureRangeAPPLE;
PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC glGetTexParameterPointervAPPLE;

static int gleIntLoad_APPLE_texture_range()
{
	int bIsLoaded = 1;
	glTextureRangeAPPLE = (PFNGLTEXTURERANGEAPPLEPROC)gleIntGetProcAddress("glTextureRangeAPPLE");
	if(!TestPointer(glTextureRangeAPPLE)) bIsLoaded = 0;
	glGetTexParameterPointervAPPLE = (PFNGLGETTEXPARAMETERPOINTERVAPPLEPROC)gleIntGetProcAddress("glGetTexParameterPointervAPPLE");
	if(!TestPointer(glGetTexParameterPointervAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLBINDVERTEXARRAYAPPLEPROC)(GLuint array);
typedef void (GLE_FUNCPTR * PFNGLDELETEVERTEXARRAYSAPPLEPROC)(GLsizei n, const GLuint *arrays);
typedef void (GLE_FUNCPTR * PFNGLGENVERTEXARRAYSAPPLEPROC)(GLsizei n, GLuint *arrays);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXARRAYAPPLEPROC)(GLuint array);

PFNGLBINDVERTEXARRAYAPPLEPROC glBindVertexArrayAPPLE;
PFNGLDELETEVERTEXARRAYSAPPLEPROC glDeleteVertexArraysAPPLE;
PFNGLGENVERTEXARRAYSAPPLEPROC glGenVertexArraysAPPLE;
PFNGLISVERTEXARRAYAPPLEPROC glIsVertexArrayAPPLE;

static int gleIntLoad_APPLE_vertex_array_object()
{
	int bIsLoaded = 1;
	glBindVertexArrayAPPLE = (PFNGLBINDVERTEXARRAYAPPLEPROC)gleIntGetProcAddress("glBindVertexArrayAPPLE");
	if(!TestPointer(glBindVertexArrayAPPLE)) bIsLoaded = 0;
	glDeleteVertexArraysAPPLE = (PFNGLDELETEVERTEXARRAYSAPPLEPROC)gleIntGetProcAddress("glDeleteVertexArraysAPPLE");
	if(!TestPointer(glDeleteVertexArraysAPPLE)) bIsLoaded = 0;
	glGenVertexArraysAPPLE = (PFNGLGENVERTEXARRAYSAPPLEPROC)gleIntGetProcAddress("glGenVertexArraysAPPLE");
	if(!TestPointer(glGenVertexArraysAPPLE)) bIsLoaded = 0;
	glIsVertexArrayAPPLE = (PFNGLISVERTEXARRAYAPPLEPROC)gleIntGetProcAddress("glIsVertexArrayAPPLE");
	if(!TestPointer(glIsVertexArrayAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYRANGEAPPLEPROC)(GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)(GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)(GLenum pname, GLint param);

PFNGLVERTEXARRAYRANGEAPPLEPROC glVertexArrayRangeAPPLE;
PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC glFlushVertexArrayRangeAPPLE;
PFNGLVERTEXARRAYPARAMETERIAPPLEPROC glVertexArrayParameteriAPPLE;

static int gleIntLoad_APPLE_vertex_array_range()
{
	int bIsLoaded = 1;
	glVertexArrayRangeAPPLE = (PFNGLVERTEXARRAYRANGEAPPLEPROC)gleIntGetProcAddress("glVertexArrayRangeAPPLE");
	if(!TestPointer(glVertexArrayRangeAPPLE)) bIsLoaded = 0;
	glFlushVertexArrayRangeAPPLE = (PFNGLFLUSHVERTEXARRAYRANGEAPPLEPROC)gleIntGetProcAddress("glFlushVertexArrayRangeAPPLE");
	if(!TestPointer(glFlushVertexArrayRangeAPPLE)) bIsLoaded = 0;
	glVertexArrayParameteriAPPLE = (PFNGLVERTEXARRAYPARAMETERIAPPLEPROC)gleIntGetProcAddress("glVertexArrayParameteriAPPLE");
	if(!TestPointer(glVertexArrayParameteriAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLENABLEVERTEXATTRIBAPPLEPROC)(GLuint index, GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLDISABLEVERTEXATTRIBAPPLEPROC)(GLuint index, GLenum pname);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)(GLuint index, GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB1DAPPLEPROC)(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB1FAPPLEPROC)(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB2DAPPLEPROC)(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLMAPVERTEXATTRIB2FAPPLEPROC)(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);

PFNGLENABLEVERTEXATTRIBAPPLEPROC glEnableVertexAttribAPPLE;
PFNGLDISABLEVERTEXATTRIBAPPLEPROC glDisableVertexAttribAPPLE;
PFNGLISVERTEXATTRIBENABLEDAPPLEPROC glIsVertexAttribEnabledAPPLE;
PFNGLMAPVERTEXATTRIB1DAPPLEPROC glMapVertexAttrib1dAPPLE;
PFNGLMAPVERTEXATTRIB1FAPPLEPROC glMapVertexAttrib1fAPPLE;
PFNGLMAPVERTEXATTRIB2DAPPLEPROC glMapVertexAttrib2dAPPLE;
PFNGLMAPVERTEXATTRIB2FAPPLEPROC glMapVertexAttrib2fAPPLE;

static int gleIntLoad_APPLE_vertex_program_evaluators()
{
	int bIsLoaded = 1;
	glEnableVertexAttribAPPLE = (PFNGLENABLEVERTEXATTRIBAPPLEPROC)gleIntGetProcAddress("glEnableVertexAttribAPPLE");
	if(!TestPointer(glEnableVertexAttribAPPLE)) bIsLoaded = 0;
	glDisableVertexAttribAPPLE = (PFNGLDISABLEVERTEXATTRIBAPPLEPROC)gleIntGetProcAddress("glDisableVertexAttribAPPLE");
	if(!TestPointer(glDisableVertexAttribAPPLE)) bIsLoaded = 0;
	glIsVertexAttribEnabledAPPLE = (PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)gleIntGetProcAddress("glIsVertexAttribEnabledAPPLE");
	if(!TestPointer(glIsVertexAttribEnabledAPPLE)) bIsLoaded = 0;
	glMapVertexAttrib1dAPPLE = (PFNGLMAPVERTEXATTRIB1DAPPLEPROC)gleIntGetProcAddress("glMapVertexAttrib1dAPPLE");
	if(!TestPointer(glMapVertexAttrib1dAPPLE)) bIsLoaded = 0;
	glMapVertexAttrib1fAPPLE = (PFNGLMAPVERTEXATTRIB1FAPPLEPROC)gleIntGetProcAddress("glMapVertexAttrib1fAPPLE");
	if(!TestPointer(glMapVertexAttrib1fAPPLE)) bIsLoaded = 0;
	glMapVertexAttrib2dAPPLE = (PFNGLMAPVERTEXATTRIB2DAPPLEPROC)gleIntGetProcAddress("glMapVertexAttrib2dAPPLE");
	if(!TestPointer(glMapVertexAttrib2dAPPLE)) bIsLoaded = 0;
	glMapVertexAttrib2fAPPLE = (PFNGLMAPVERTEXATTRIB2FAPPLEPROC)gleIntGetProcAddress("glMapVertexAttrib2fAPPLE");
	if(!TestPointer(glMapVertexAttrib2fAPPLE)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLRELEASESHADERCOMPILERPROC)();
typedef void (GLE_FUNCPTR * PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const GLvoid *binary, GLsizei length);
typedef void (GLE_FUNCPTR * PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEFPROC)(GLclampf n, GLclampf f);
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHFPROC)(GLclampf d);

PFNGLRELEASESHADERCOMPILERPROC __gleReleaseShaderCompiler;
PFNGLSHADERBINARYPROC __gleShaderBinary;
PFNGLGETSHADERPRECISIONFORMATPROC __gleGetShaderPrecisionFormat;
PFNGLDEPTHRANGEFPROC __gleDepthRangef;
PFNGLCLEARDEPTHFPROC __gleClearDepthf;

static int gleIntLoad_ARB_ES2_compatibility()
{
	int bIsLoaded = 1;
	__gleReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)gleIntGetProcAddress("glReleaseShaderCompiler");
	if(!TestPointer(__gleReleaseShaderCompiler)) bIsLoaded = 0;
	__gleShaderBinary = (PFNGLSHADERBINARYPROC)gleIntGetProcAddress("glShaderBinary");
	if(!TestPointer(__gleShaderBinary)) bIsLoaded = 0;
	__gleGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)gleIntGetProcAddress("glGetShaderPrecisionFormat");
	if(!TestPointer(__gleGetShaderPrecisionFormat)) bIsLoaded = 0;
	__gleDepthRangef = (PFNGLDEPTHRANGEFPROC)gleIntGetProcAddress("glDepthRangef");
	if(!TestPointer(__gleDepthRangef)) bIsLoaded = 0;
	__gleClearDepthf = (PFNGLCLEARDEPTHFPROC)gleIntGetProcAddress("glClearDepthf");
	if(!TestPointer(__gleClearDepthf)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar *name);

PFNGLBINDFRAGDATALOCATIONINDEXEDPROC __gleBindFragDataLocationIndexed;
PFNGLGETFRAGDATAINDEXPROC __gleGetFragDataIndex;

static int gleIntLoad_ARB_blend_func_extended()
{
	int bIsLoaded = 1;
	__gleBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)gleIntGetProcAddress("glBindFragDataLocationIndexed");
	if(!TestPointer(__gleBindFragDataLocationIndexed)) bIsLoaded = 0;
	__gleGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)gleIntGetProcAddress("glGetFragDataIndex");
	if(!TestPointer(__gleGetFragDataIndex)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef GLsync (GLE_FUNCPTR * PFNGLCREATESYNCFROMCLEVENTARBPROC)(struct _cl_context * context, struct _cl_event * event, GLbitfield flags);

PFNGLCREATESYNCFROMCLEVENTARBPROC glCreateSyncFromCLeventARB;

static int gleIntLoad_ARB_cl_event()
{
	int bIsLoaded = 1;
	glCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC)gleIntGetProcAddress("glCreateSyncFromCLeventARB");
	if(!TestPointer(glCreateSyncFromCLeventARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCLAMPCOLORARBPROC)(GLenum target, GLenum clamp);

PFNGLCLAMPCOLORARBPROC glClampColorARB;

static int gleIntLoad_ARB_color_buffer_float()
{
	int bIsLoaded = 1;
	glClampColorARB = (PFNGLCLAMPCOLORARBPROC)gleIntGetProcAddress("glClampColorARB");
	if(!TestPointer(glClampColorARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);

PFNGLCOPYBUFFERSUBDATAPROC __gleCopyBufferSubData;

static int gleIntLoad_ARB_copy_buffer()
{
	int bIsLoaded = 1;
	__gleCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)gleIntGetProcAddress("glCopyBufferSubData");
	if(!TestPointer(__gleCopyBufferSubData)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECONTROLARBPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGEINSERTARBPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (GLE_FUNCPTR * PFNGLDEBUGMESSAGECALLBACKARBPROC)(GLDEBUGPROCARB callback, const GLvoid *userParam);
typedef GLuint (GLE_FUNCPTR * PFNGLGETDEBUGMESSAGELOGARBPROC)(GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);

PFNGLDEBUGMESSAGECONTROLARBPROC glDebugMessageControlARB;
PFNGLDEBUGMESSAGEINSERTARBPROC glDebugMessageInsertARB;
PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB;
PFNGLGETDEBUGMESSAGELOGARBPROC glGetDebugMessageLogARB;

static int gleIntLoad_ARB_debug_output()
{
	int bIsLoaded = 1;
	glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)gleIntGetProcAddress("glDebugMessageControlARB");
	if(!TestPointer(glDebugMessageControlARB)) bIsLoaded = 0;
	glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)gleIntGetProcAddress("glDebugMessageInsertARB");
	if(!TestPointer(glDebugMessageInsertARB)) bIsLoaded = 0;
	glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)gleIntGetProcAddress("glDebugMessageCallbackARB");
	if(!TestPointer(glDebugMessageCallbackARB)) bIsLoaded = 0;
	glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC)gleIntGetProcAddress("glGetDebugMessageLogARB");
	if(!TestPointer(glGetDebugMessageLogARB)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSARBPROC)(GLsizei n, const GLenum *bufs);

PFNGLDRAWBUFFERSARBPROC glDrawBuffersARB;

static int gleIntLoad_ARB_draw_buffers()
{
	int bIsLoaded = 1;
	glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC)gleIntGetProcAddress("glDrawBuffersARB");
	if(!TestPointer(glDrawBuffersARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONIARBARBPROC)(GLuint buf, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEIARBARBPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCIARBARBPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEIARBARBPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

PFNGLBLENDEQUATIONIARBARBPROC glBlendEquationiARBARB;
PFNGLBLENDEQUATIONSEPARATEIARBARBPROC glBlendEquationSeparateiARBARB;
PFNGLBLENDFUNCIARBARBPROC glBlendFunciARBARB;
PFNGLBLENDFUNCSEPARATEIARBARBPROC glBlendFuncSeparateiARBARB;

static int gleIntLoad_ARB_draw_buffers_blend()
{
	int bIsLoaded = 1;
	glBlendEquationiARBARB = (PFNGLBLENDEQUATIONIARBARBPROC)gleIntGetProcAddress("glBlendEquationiARBARB");
	if(!TestPointer(glBlendEquationiARBARB)) bIsLoaded = 0;
	glBlendEquationSeparateiARBARB = (PFNGLBLENDEQUATIONSEPARATEIARBARBPROC)gleIntGetProcAddress("glBlendEquationSeparateiARBARB");
	if(!TestPointer(glBlendEquationSeparateiARBARB)) bIsLoaded = 0;
	glBlendFunciARBARB = (PFNGLBLENDFUNCIARBARBPROC)gleIntGetProcAddress("glBlendFunciARBARB");
	if(!TestPointer(glBlendFunciARBARB)) bIsLoaded = 0;
	glBlendFuncSeparateiARBARB = (PFNGLBLENDFUNCSEPARATEIARBARBPROC)gleIntGetProcAddress("glBlendFuncSeparateiARBARB");
	if(!TestPointer(glBlendFuncSeparateiARBARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount, GLint basevertex);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount, const GLint *basevertex);

PFNGLDRAWELEMENTSBASEVERTEXPROC __gleDrawElementsBaseVertex;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC __gleDrawRangeElementsBaseVertex;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC __gleDrawElementsInstancedBaseVertex;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC __gleMultiDrawElementsBaseVertex;

static int gleIntLoad_ARB_draw_elements_base_vertex()
{
	int bIsLoaded = 1;
	__gleDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glDrawElementsBaseVertex");
	if(!TestPointer(__gleDrawElementsBaseVertex)) bIsLoaded = 0;
	__gleDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glDrawRangeElementsBaseVertex");
	if(!TestPointer(__gleDrawRangeElementsBaseVertex)) bIsLoaded = 0;
	__gleDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)gleIntGetProcAddress("glDrawElementsInstancedBaseVertex");
	if(!TestPointer(__gleDrawElementsInstancedBaseVertex)) bIsLoaded = 0;
	__gleMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glMultiDrawElementsBaseVertex");
	if(!TestPointer(__gleMultiDrawElementsBaseVertex)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const GLvoid *indirect);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const GLvoid *indirect);

PFNGLDRAWARRAYSINDIRECTPROC __gleDrawArraysIndirect;
PFNGLDRAWELEMENTSINDIRECTPROC __gleDrawElementsIndirect;

static int gleIntLoad_ARB_draw_indirect()
{
	int bIsLoaded = 1;
	__gleDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)gleIntGetProcAddress("glDrawArraysIndirect");
	if(!TestPointer(__gleDrawArraysIndirect)) bIsLoaded = 0;
	__gleDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)gleIntGetProcAddress("glDrawElementsIndirect");
	if(!TestPointer(__gleDrawElementsIndirect)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDARBPROC)(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDARBPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);

PFNGLDRAWARRAYSINSTANCEDARBPROC glDrawArraysInstancedARB;
PFNGLDRAWELEMENTSINSTANCEDARBPROC glDrawElementsInstancedARB;

static int gleIntLoad_ARB_draw_instanced()
{
	int bIsLoaded = 1;
	glDrawArraysInstancedARB = (PFNGLDRAWARRAYSINSTANCEDARBPROC)gleIntGetProcAddress("glDrawArraysInstancedARB");
	if(!TestPointer(glDrawArraysInstancedARB)) bIsLoaded = 0;
	glDrawElementsInstancedARB = (PFNGLDRAWELEMENTSINSTANCEDARBPROC)gleIntGetProcAddress("glDrawElementsInstancedARB");
	if(!TestPointer(glDrawElementsInstancedARB)) bIsLoaded = 0;
	return bIsLoaded;
}





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

PFNGLISRENDERBUFFERPROC __gleIsRenderbuffer;
PFNGLBINDRENDERBUFFERPROC __gleBindRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC __gleDeleteRenderbuffers;
PFNGLGENRENDERBUFFERSPROC __gleGenRenderbuffers;
PFNGLRENDERBUFFERSTORAGEPROC __gleRenderbufferStorage;
PFNGLGETRENDERBUFFERPARAMETERIVPROC __gleGetRenderbufferParameteriv;
PFNGLISFRAMEBUFFERPROC __gleIsFramebuffer;
PFNGLBINDFRAMEBUFFERPROC __gleBindFramebuffer;
PFNGLDELETEFRAMEBUFFERSPROC __gleDeleteFramebuffers;
PFNGLGENFRAMEBUFFERSPROC __gleGenFramebuffers;
PFNGLCHECKFRAMEBUFFERSTATUSPROC __gleCheckFramebufferStatus;
PFNGLFRAMEBUFFERTEXTURE1DPROC __gleFramebufferTexture1D;
PFNGLFRAMEBUFFERTEXTURE2DPROC __gleFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE3DPROC __gleFramebufferTexture3D;
PFNGLFRAMEBUFFERRENDERBUFFERPROC __gleFramebufferRenderbuffer;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC __gleGetFramebufferAttachmentParameteriv;
PFNGLGENERATEMIPMAPPROC __gleGenerateMipmap;
PFNGLBLITFRAMEBUFFERPROC __gleBlitFramebuffer;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC __gleRenderbufferStorageMultisample;
PFNGLFRAMEBUFFERTEXTURELAYERPROC __gleFramebufferTextureLayer;

static int gleIntLoad_ARB_framebuffer_object()
{
	int bIsLoaded = 1;
	__gleIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)gleIntGetProcAddress("glIsRenderbuffer");
	if(!TestPointer(__gleIsRenderbuffer)) bIsLoaded = 0;
	__gleBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)gleIntGetProcAddress("glBindRenderbuffer");
	if(!TestPointer(__gleBindRenderbuffer)) bIsLoaded = 0;
	__gleDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)gleIntGetProcAddress("glDeleteRenderbuffers");
	if(!TestPointer(__gleDeleteRenderbuffers)) bIsLoaded = 0;
	__gleGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)gleIntGetProcAddress("glGenRenderbuffers");
	if(!TestPointer(__gleGenRenderbuffers)) bIsLoaded = 0;
	__gleRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)gleIntGetProcAddress("glRenderbufferStorage");
	if(!TestPointer(__gleRenderbufferStorage)) bIsLoaded = 0;
	__gleGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)gleIntGetProcAddress("glGetRenderbufferParameteriv");
	if(!TestPointer(__gleGetRenderbufferParameteriv)) bIsLoaded = 0;
	__gleIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)gleIntGetProcAddress("glIsFramebuffer");
	if(!TestPointer(__gleIsFramebuffer)) bIsLoaded = 0;
	__gleBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)gleIntGetProcAddress("glBindFramebuffer");
	if(!TestPointer(__gleBindFramebuffer)) bIsLoaded = 0;
	__gleDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)gleIntGetProcAddress("glDeleteFramebuffers");
	if(!TestPointer(__gleDeleteFramebuffers)) bIsLoaded = 0;
	__gleGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)gleIntGetProcAddress("glGenFramebuffers");
	if(!TestPointer(__gleGenFramebuffers)) bIsLoaded = 0;
	__gleCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)gleIntGetProcAddress("glCheckFramebufferStatus");
	if(!TestPointer(__gleCheckFramebufferStatus)) bIsLoaded = 0;
	__gleFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)gleIntGetProcAddress("glFramebufferTexture1D");
	if(!TestPointer(__gleFramebufferTexture1D)) bIsLoaded = 0;
	__gleFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)gleIntGetProcAddress("glFramebufferTexture2D");
	if(!TestPointer(__gleFramebufferTexture2D)) bIsLoaded = 0;
	__gleFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)gleIntGetProcAddress("glFramebufferTexture3D");
	if(!TestPointer(__gleFramebufferTexture3D)) bIsLoaded = 0;
	__gleFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)gleIntGetProcAddress("glFramebufferRenderbuffer");
	if(!TestPointer(__gleFramebufferRenderbuffer)) bIsLoaded = 0;
	__gleGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)gleIntGetProcAddress("glGetFramebufferAttachmentParameteriv");
	if(!TestPointer(__gleGetFramebufferAttachmentParameteriv)) bIsLoaded = 0;
	__gleGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)gleIntGetProcAddress("glGenerateMipmap");
	if(!TestPointer(__gleGenerateMipmap)) bIsLoaded = 0;
	__gleBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)gleIntGetProcAddress("glBlitFramebuffer");
	if(!TestPointer(__gleBlitFramebuffer)) bIsLoaded = 0;
	__gleRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)gleIntGetProcAddress("glRenderbufferStorageMultisample");
	if(!TestPointer(__gleRenderbufferStorageMultisample)) bIsLoaded = 0;
	__gleFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)gleIntGetProcAddress("glFramebufferTextureLayer");
	if(!TestPointer(__gleFramebufferTextureLayer)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIARBPROC)(GLuint program, GLenum pname, GLint value);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);

PFNGLPROGRAMPARAMETERIARBPROC glProgramParameteriARB;
PFNGLFRAMEBUFFERTEXTUREARBPROC glFramebufferTextureARB;
PFNGLFRAMEBUFFERTEXTURELAYERARBPROC glFramebufferTextureLayerARB;
PFNGLFRAMEBUFFERTEXTUREFACEARBPROC glFramebufferTextureFaceARB;

static int gleIntLoad_ARB_geometry_shader4()
{
	int bIsLoaded = 1;
	glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)gleIntGetProcAddress("glProgramParameteriARB");
	if(!TestPointer(glProgramParameteriARB)) bIsLoaded = 0;
	glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC)gleIntGetProcAddress("glFramebufferTextureARB");
	if(!TestPointer(glFramebufferTextureARB)) bIsLoaded = 0;
	glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)gleIntGetProcAddress("glFramebufferTextureLayerARB");
	if(!TestPointer(glFramebufferTextureLayerARB)) bIsLoaded = 0;
	glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)gleIntGetProcAddress("glFramebufferTextureFaceARB");
	if(!TestPointer(glFramebufferTextureFaceARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const GLvoid *binary, GLsizei length);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);

PFNGLGETPROGRAMBINARYPROC __gleGetProgramBinary;
PFNGLPROGRAMBINARYPROC __gleProgramBinary;
PFNGLPROGRAMPARAMETERIPROC __gleProgramParameteri;

static int gleIntLoad_ARB_get_program_binary()
{
	int bIsLoaded = 1;
	__gleGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)gleIntGetProcAddress("glGetProgramBinary");
	if(!TestPointer(__gleGetProgramBinary)) bIsLoaded = 0;
	__gleProgramBinary = (PFNGLPROGRAMBINARYPROC)gleIntGetProcAddress("glProgramBinary");
	if(!TestPointer(__gleProgramBinary)) bIsLoaded = 0;
	__gleProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)gleIntGetProcAddress("glProgramParameteri");
	if(!TestPointer(__gleProgramParameteri)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLUNIFORM1DPROC __gleUniform1d;
PFNGLUNIFORM2DPROC __gleUniform2d;
PFNGLUNIFORM3DPROC __gleUniform3d;
PFNGLUNIFORM4DPROC __gleUniform4d;
PFNGLUNIFORM1DVPROC __gleUniform1dv;
PFNGLUNIFORM2DVPROC __gleUniform2dv;
PFNGLUNIFORM3DVPROC __gleUniform3dv;
PFNGLUNIFORM4DVPROC __gleUniform4dv;
PFNGLUNIFORMMATRIX2DVPROC __gleUniformMatrix2dv;
PFNGLUNIFORMMATRIX3DVPROC __gleUniformMatrix3dv;
PFNGLUNIFORMMATRIX4DVPROC __gleUniformMatrix4dv;
PFNGLUNIFORMMATRIX2X3DVPROC __gleUniformMatrix2x3dv;
PFNGLUNIFORMMATRIX2X4DVPROC __gleUniformMatrix2x4dv;
PFNGLUNIFORMMATRIX3X2DVPROC __gleUniformMatrix3x2dv;
PFNGLUNIFORMMATRIX3X4DVPROC __gleUniformMatrix3x4dv;
PFNGLUNIFORMMATRIX4X2DVPROC __gleUniformMatrix4x2dv;
PFNGLUNIFORMMATRIX4X3DVPROC __gleUniformMatrix4x3dv;
PFNGLGETUNIFORMDVPROC __gleGetUniformdv;

static int gleIntLoad_ARB_gpu_shader_fp64()
{
	int bIsLoaded = 1;
	__gleUniform1d = (PFNGLUNIFORM1DPROC)gleIntGetProcAddress("glUniform1d");
	if(!TestPointer(__gleUniform1d)) bIsLoaded = 0;
	__gleUniform2d = (PFNGLUNIFORM2DPROC)gleIntGetProcAddress("glUniform2d");
	if(!TestPointer(__gleUniform2d)) bIsLoaded = 0;
	__gleUniform3d = (PFNGLUNIFORM3DPROC)gleIntGetProcAddress("glUniform3d");
	if(!TestPointer(__gleUniform3d)) bIsLoaded = 0;
	__gleUniform4d = (PFNGLUNIFORM4DPROC)gleIntGetProcAddress("glUniform4d");
	if(!TestPointer(__gleUniform4d)) bIsLoaded = 0;
	__gleUniform1dv = (PFNGLUNIFORM1DVPROC)gleIntGetProcAddress("glUniform1dv");
	if(!TestPointer(__gleUniform1dv)) bIsLoaded = 0;
	__gleUniform2dv = (PFNGLUNIFORM2DVPROC)gleIntGetProcAddress("glUniform2dv");
	if(!TestPointer(__gleUniform2dv)) bIsLoaded = 0;
	__gleUniform3dv = (PFNGLUNIFORM3DVPROC)gleIntGetProcAddress("glUniform3dv");
	if(!TestPointer(__gleUniform3dv)) bIsLoaded = 0;
	__gleUniform4dv = (PFNGLUNIFORM4DVPROC)gleIntGetProcAddress("glUniform4dv");
	if(!TestPointer(__gleUniform4dv)) bIsLoaded = 0;
	__gleUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)gleIntGetProcAddress("glUniformMatrix2dv");
	if(!TestPointer(__gleUniformMatrix2dv)) bIsLoaded = 0;
	__gleUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)gleIntGetProcAddress("glUniformMatrix3dv");
	if(!TestPointer(__gleUniformMatrix3dv)) bIsLoaded = 0;
	__gleUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)gleIntGetProcAddress("glUniformMatrix4dv");
	if(!TestPointer(__gleUniformMatrix4dv)) bIsLoaded = 0;
	__gleUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)gleIntGetProcAddress("glUniformMatrix2x3dv");
	if(!TestPointer(__gleUniformMatrix2x3dv)) bIsLoaded = 0;
	__gleUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)gleIntGetProcAddress("glUniformMatrix2x4dv");
	if(!TestPointer(__gleUniformMatrix2x4dv)) bIsLoaded = 0;
	__gleUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)gleIntGetProcAddress("glUniformMatrix3x2dv");
	if(!TestPointer(__gleUniformMatrix3x2dv)) bIsLoaded = 0;
	__gleUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)gleIntGetProcAddress("glUniformMatrix3x4dv");
	if(!TestPointer(__gleUniformMatrix3x4dv)) bIsLoaded = 0;
	__gleUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)gleIntGetProcAddress("glUniformMatrix4x2dv");
	if(!TestPointer(__gleUniformMatrix4x2dv)) bIsLoaded = 0;
	__gleUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)gleIntGetProcAddress("glUniformMatrix4x3dv");
	if(!TestPointer(__gleUniformMatrix4x3dv)) bIsLoaded = 0;
	__gleGetUniformdv = (PFNGLGETUNIFORMDVPROC)gleIntGetProcAddress("glGetUniformdv");
	if(!TestPointer(__gleGetUniformdv)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBDIVISORARBPROC)(GLuint index, GLuint divisor);

PFNGLVERTEXATTRIBDIVISORARBPROC glVertexAttribDivisorARB;

static int gleIntLoad_ARB_instanced_arrays()
{
	int bIsLoaded = 1;
	glVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC)gleIntGetProcAddress("glVertexAttribDivisorARB");
	if(!TestPointer(glVertexAttribDivisorARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (GLE_FUNCPTR * PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);

PFNGLMAPBUFFERRANGEPROC __gleMapBufferRange;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC __gleFlushMappedBufferRange;

static int gleIntLoad_ARB_map_buffer_range()
{
	int bIsLoaded = 1;
	__gleMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)gleIntGetProcAddress("glMapBufferRange");
	if(!TestPointer(__gleMapBufferRange)) bIsLoaded = 0;
	__gleFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)gleIntGetProcAddress("glFlushMappedBufferRange");
	if(!TestPointer(__gleFlushMappedBufferRange)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCURRENTPALETTEMATRIXARBPROC)(GLint index);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUBVARBPROC)(GLint size, const GLubyte *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUSVARBPROC)(GLint size, const GLushort *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXUIVARBPROC)(GLint size, const GLuint *indices);
typedef void (GLE_FUNCPTR * PFNGLMATRIXINDEXPOINTERARBPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

PFNGLCURRENTPALETTEMATRIXARBPROC glCurrentPaletteMatrixARB;
PFNGLMATRIXINDEXUBVARBPROC glMatrixIndexubvARB;
PFNGLMATRIXINDEXUSVARBPROC glMatrixIndexusvARB;
PFNGLMATRIXINDEXUIVARBPROC glMatrixIndexuivARB;
PFNGLMATRIXINDEXPOINTERARBPROC glMatrixIndexPointerARB;

static int gleIntLoad_ARB_matrix_palette()
{
	int bIsLoaded = 1;
	glCurrentPaletteMatrixARB = (PFNGLCURRENTPALETTEMATRIXARBPROC)gleIntGetProcAddress("glCurrentPaletteMatrixARB");
	if(!TestPointer(glCurrentPaletteMatrixARB)) bIsLoaded = 0;
	glMatrixIndexubvARB = (PFNGLMATRIXINDEXUBVARBPROC)gleIntGetProcAddress("glMatrixIndexubvARB");
	if(!TestPointer(glMatrixIndexubvARB)) bIsLoaded = 0;
	glMatrixIndexusvARB = (PFNGLMATRIXINDEXUSVARBPROC)gleIntGetProcAddress("glMatrixIndexusvARB");
	if(!TestPointer(glMatrixIndexusvARB)) bIsLoaded = 0;
	glMatrixIndexuivARB = (PFNGLMATRIXINDEXUIVARBPROC)gleIntGetProcAddress("glMatrixIndexuivARB");
	if(!TestPointer(glMatrixIndexuivARB)) bIsLoaded = 0;
	glMatrixIndexPointerARB = (PFNGLMATRIXINDEXPOINTERARBPROC)gleIntGetProcAddress("glMatrixIndexPointerARB");
	if(!TestPointer(glMatrixIndexPointerARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLSAMPLECOVERAGEARBPROC)(GLclampf value, GLboolean invert);

PFNGLSAMPLECOVERAGEARBPROC glSampleCoverageARB;

static int gleIntLoad_ARB_multisample()
{
	int bIsLoaded = 1;
	glSampleCoverageARB = (PFNGLSAMPLECOVERAGEARBPROC)gleIntGetProcAddress("glSampleCoverageARB");
	if(!TestPointer(glSampleCoverageARB)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB;
PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB;
PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB;
PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;
PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB;
PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB;
PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;
PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB;
PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB;
PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB;
PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;
PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB;
PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB;
PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB;
PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;

static int gleIntLoad_ARB_multitexture()
{
	int bIsLoaded = 1;
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)gleIntGetProcAddress("glActiveTextureARB");
	if(!TestPointer(glActiveTextureARB)) bIsLoaded = 0;
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)gleIntGetProcAddress("glClientActiveTextureARB");
	if(!TestPointer(glClientActiveTextureARB)) bIsLoaded = 0;
	glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)gleIntGetProcAddress("glMultiTexCoord1dARB");
	if(!TestPointer(glMultiTexCoord1dARB)) bIsLoaded = 0;
	glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)gleIntGetProcAddress("glMultiTexCoord1dvARB");
	if(!TestPointer(glMultiTexCoord1dvARB)) bIsLoaded = 0;
	glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)gleIntGetProcAddress("glMultiTexCoord1fARB");
	if(!TestPointer(glMultiTexCoord1fARB)) bIsLoaded = 0;
	glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)gleIntGetProcAddress("glMultiTexCoord1fvARB");
	if(!TestPointer(glMultiTexCoord1fvARB)) bIsLoaded = 0;
	glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)gleIntGetProcAddress("glMultiTexCoord1iARB");
	if(!TestPointer(glMultiTexCoord1iARB)) bIsLoaded = 0;
	glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)gleIntGetProcAddress("glMultiTexCoord1ivARB");
	if(!TestPointer(glMultiTexCoord1ivARB)) bIsLoaded = 0;
	glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)gleIntGetProcAddress("glMultiTexCoord1sARB");
	if(!TestPointer(glMultiTexCoord1sARB)) bIsLoaded = 0;
	glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)gleIntGetProcAddress("glMultiTexCoord1svARB");
	if(!TestPointer(glMultiTexCoord1svARB)) bIsLoaded = 0;
	glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)gleIntGetProcAddress("glMultiTexCoord2dARB");
	if(!TestPointer(glMultiTexCoord2dARB)) bIsLoaded = 0;
	glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)gleIntGetProcAddress("glMultiTexCoord2dvARB");
	if(!TestPointer(glMultiTexCoord2dvARB)) bIsLoaded = 0;
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)gleIntGetProcAddress("glMultiTexCoord2fARB");
	if(!TestPointer(glMultiTexCoord2fARB)) bIsLoaded = 0;
	glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)gleIntGetProcAddress("glMultiTexCoord2fvARB");
	if(!TestPointer(glMultiTexCoord2fvARB)) bIsLoaded = 0;
	glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)gleIntGetProcAddress("glMultiTexCoord2iARB");
	if(!TestPointer(glMultiTexCoord2iARB)) bIsLoaded = 0;
	glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)gleIntGetProcAddress("glMultiTexCoord2ivARB");
	if(!TestPointer(glMultiTexCoord2ivARB)) bIsLoaded = 0;
	glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)gleIntGetProcAddress("glMultiTexCoord2sARB");
	if(!TestPointer(glMultiTexCoord2sARB)) bIsLoaded = 0;
	glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)gleIntGetProcAddress("glMultiTexCoord2svARB");
	if(!TestPointer(glMultiTexCoord2svARB)) bIsLoaded = 0;
	glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)gleIntGetProcAddress("glMultiTexCoord3dARB");
	if(!TestPointer(glMultiTexCoord3dARB)) bIsLoaded = 0;
	glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)gleIntGetProcAddress("glMultiTexCoord3dvARB");
	if(!TestPointer(glMultiTexCoord3dvARB)) bIsLoaded = 0;
	glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)gleIntGetProcAddress("glMultiTexCoord3fARB");
	if(!TestPointer(glMultiTexCoord3fARB)) bIsLoaded = 0;
	glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)gleIntGetProcAddress("glMultiTexCoord3fvARB");
	if(!TestPointer(glMultiTexCoord3fvARB)) bIsLoaded = 0;
	glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)gleIntGetProcAddress("glMultiTexCoord3iARB");
	if(!TestPointer(glMultiTexCoord3iARB)) bIsLoaded = 0;
	glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)gleIntGetProcAddress("glMultiTexCoord3ivARB");
	if(!TestPointer(glMultiTexCoord3ivARB)) bIsLoaded = 0;
	glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)gleIntGetProcAddress("glMultiTexCoord3sARB");
	if(!TestPointer(glMultiTexCoord3sARB)) bIsLoaded = 0;
	glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)gleIntGetProcAddress("glMultiTexCoord3svARB");
	if(!TestPointer(glMultiTexCoord3svARB)) bIsLoaded = 0;
	glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)gleIntGetProcAddress("glMultiTexCoord4dARB");
	if(!TestPointer(glMultiTexCoord4dARB)) bIsLoaded = 0;
	glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)gleIntGetProcAddress("glMultiTexCoord4dvARB");
	if(!TestPointer(glMultiTexCoord4dvARB)) bIsLoaded = 0;
	glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)gleIntGetProcAddress("glMultiTexCoord4fARB");
	if(!TestPointer(glMultiTexCoord4fARB)) bIsLoaded = 0;
	glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)gleIntGetProcAddress("glMultiTexCoord4fvARB");
	if(!TestPointer(glMultiTexCoord4fvARB)) bIsLoaded = 0;
	glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)gleIntGetProcAddress("glMultiTexCoord4iARB");
	if(!TestPointer(glMultiTexCoord4iARB)) bIsLoaded = 0;
	glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)gleIntGetProcAddress("glMultiTexCoord4ivARB");
	if(!TestPointer(glMultiTexCoord4ivARB)) bIsLoaded = 0;
	glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)gleIntGetProcAddress("glMultiTexCoord4sARB");
	if(!TestPointer(glMultiTexCoord4sARB)) bIsLoaded = 0;
	glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)gleIntGetProcAddress("glMultiTexCoord4svARB");
	if(!TestPointer(glMultiTexCoord4svARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGENQUERIESARBPROC)(GLsizei n, GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLDELETEQUERIESARBPROC)(GLsizei n, const GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISQUERYARBPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYARBPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDQUERYARBPROC)(GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYIVARBPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTIVARBPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUIVARBPROC)(GLuint id, GLenum pname, GLuint *params);

PFNGLGENQUERIESARBPROC glGenQueriesARB;
PFNGLDELETEQUERIESARBPROC glDeleteQueriesARB;
PFNGLISQUERYARBPROC glIsQueryARB;
PFNGLBEGINQUERYARBPROC glBeginQueryARB;
PFNGLENDQUERYARBPROC glEndQueryARB;
PFNGLGETQUERYIVARBPROC glGetQueryivARB;
PFNGLGETQUERYOBJECTIVARBPROC glGetQueryObjectivARB;
PFNGLGETQUERYOBJECTUIVARBPROC glGetQueryObjectuivARB;

static int gleIntLoad_ARB_occlusion_query()
{
	int bIsLoaded = 1;
	glGenQueriesARB = (PFNGLGENQUERIESARBPROC)gleIntGetProcAddress("glGenQueriesARB");
	if(!TestPointer(glGenQueriesARB)) bIsLoaded = 0;
	glDeleteQueriesARB = (PFNGLDELETEQUERIESARBPROC)gleIntGetProcAddress("glDeleteQueriesARB");
	if(!TestPointer(glDeleteQueriesARB)) bIsLoaded = 0;
	glIsQueryARB = (PFNGLISQUERYARBPROC)gleIntGetProcAddress("glIsQueryARB");
	if(!TestPointer(glIsQueryARB)) bIsLoaded = 0;
	glBeginQueryARB = (PFNGLBEGINQUERYARBPROC)gleIntGetProcAddress("glBeginQueryARB");
	if(!TestPointer(glBeginQueryARB)) bIsLoaded = 0;
	glEndQueryARB = (PFNGLENDQUERYARBPROC)gleIntGetProcAddress("glEndQueryARB");
	if(!TestPointer(glEndQueryARB)) bIsLoaded = 0;
	glGetQueryivARB = (PFNGLGETQUERYIVARBPROC)gleIntGetProcAddress("glGetQueryivARB");
	if(!TestPointer(glGetQueryivARB)) bIsLoaded = 0;
	glGetQueryObjectivARB = (PFNGLGETQUERYOBJECTIVARBPROC)gleIntGetProcAddress("glGetQueryObjectivARB");
	if(!TestPointer(glGetQueryObjectivARB)) bIsLoaded = 0;
	glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC)gleIntGetProcAddress("glGetQueryObjectuivARB");
	if(!TestPointer(glGetQueryObjectuivARB)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFARBPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVARBPROC)(GLenum pname, const GLfloat *params);

PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;
PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;

static int gleIntLoad_ARB_point_parameters()
{
	int bIsLoaded = 1;
	glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC)gleIntGetProcAddress("glPointParameterfARB");
	if(!TestPointer(glPointParameterfARB)) bIsLoaded = 0;
	glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)gleIntGetProcAddress("glPointParameterfvARB");
	if(!TestPointer(glPointParameterfvARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPROVOKINGVERTEXPROC)(GLenum mode);

PFNGLPROVOKINGVERTEXPROC __gleProvokingVertex;

static int gleIntLoad_ARB_provoking_vertex()
{
	int bIsLoaded = 1;
	__gleProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)gleIntGetProcAddress("glProvokingVertex");
	if(!TestPointer(__gleProvokingVertex)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGETGRAPHICSRESETSTATUSARBPROC glGetGraphicsResetStatusARB;
PFNGLGETNMAPDVARBPROC glGetnMapdvARB;
PFNGLGETNMAPFVARBPROC glGetnMapfvARB;
PFNGLGETNMAPIVARBPROC glGetnMapivARB;
PFNGLGETNPIXELMAPFVARBPROC glGetnPixelMapfvARB;
PFNGLGETNPIXELMAPUIVARBPROC glGetnPixelMapuivARB;
PFNGLGETNPIXELMAPUSVARBPROC glGetnPixelMapusvARB;
PFNGLGETNPOLYGONSTIPPLEARBPROC glGetnPolygonStippleARB;
PFNGLGETNCOLORTABLEARBPROC glGetnColorTableARB;
PFNGLGETNCONVOLUTIONFILTERARBPROC glGetnConvolutionFilterARB;
PFNGLGETNSEPARABLEFILTERARBPROC glGetnSeparableFilterARB;
PFNGLGETNHISTOGRAMARBPROC glGetnHistogramARB;
PFNGLGETNMINMAXARBPROC glGetnMinmaxARB;
PFNGLGETNTEXIMAGEARBPROC glGetnTexImageARB;
PFNGLREADNPIXELSARBPROC glReadnPixelsARB;
PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC glGetnCompressedTexImageARB;
PFNGLGETNUNIFORMFVARBPROC glGetnUniformfvARB;
PFNGLGETNUNIFORMIVARBPROC glGetnUniformivARB;
PFNGLGETNUNIFORMUIVARBPROC glGetnUniformuivARB;
PFNGLGETNUNIFORMDVARBPROC glGetnUniformdvARB;

static int gleIntLoad_ARB_robustness()
{
	int bIsLoaded = 1;
	glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC)gleIntGetProcAddress("glGetGraphicsResetStatusARB");
	if(!TestPointer(glGetGraphicsResetStatusARB)) bIsLoaded = 0;
	glGetnMapdvARB = (PFNGLGETNMAPDVARBPROC)gleIntGetProcAddress("glGetnMapdvARB");
	if(!TestPointer(glGetnMapdvARB)) bIsLoaded = 0;
	glGetnMapfvARB = (PFNGLGETNMAPFVARBPROC)gleIntGetProcAddress("glGetnMapfvARB");
	if(!TestPointer(glGetnMapfvARB)) bIsLoaded = 0;
	glGetnMapivARB = (PFNGLGETNMAPIVARBPROC)gleIntGetProcAddress("glGetnMapivARB");
	if(!TestPointer(glGetnMapivARB)) bIsLoaded = 0;
	glGetnPixelMapfvARB = (PFNGLGETNPIXELMAPFVARBPROC)gleIntGetProcAddress("glGetnPixelMapfvARB");
	if(!TestPointer(glGetnPixelMapfvARB)) bIsLoaded = 0;
	glGetnPixelMapuivARB = (PFNGLGETNPIXELMAPUIVARBPROC)gleIntGetProcAddress("glGetnPixelMapuivARB");
	if(!TestPointer(glGetnPixelMapuivARB)) bIsLoaded = 0;
	glGetnPixelMapusvARB = (PFNGLGETNPIXELMAPUSVARBPROC)gleIntGetProcAddress("glGetnPixelMapusvARB");
	if(!TestPointer(glGetnPixelMapusvARB)) bIsLoaded = 0;
	glGetnPolygonStippleARB = (PFNGLGETNPOLYGONSTIPPLEARBPROC)gleIntGetProcAddress("glGetnPolygonStippleARB");
	if(!TestPointer(glGetnPolygonStippleARB)) bIsLoaded = 0;
	glGetnColorTableARB = (PFNGLGETNCOLORTABLEARBPROC)gleIntGetProcAddress("glGetnColorTableARB");
	if(!TestPointer(glGetnColorTableARB)) bIsLoaded = 0;
	glGetnConvolutionFilterARB = (PFNGLGETNCONVOLUTIONFILTERARBPROC)gleIntGetProcAddress("glGetnConvolutionFilterARB");
	if(!TestPointer(glGetnConvolutionFilterARB)) bIsLoaded = 0;
	glGetnSeparableFilterARB = (PFNGLGETNSEPARABLEFILTERARBPROC)gleIntGetProcAddress("glGetnSeparableFilterARB");
	if(!TestPointer(glGetnSeparableFilterARB)) bIsLoaded = 0;
	glGetnHistogramARB = (PFNGLGETNHISTOGRAMARBPROC)gleIntGetProcAddress("glGetnHistogramARB");
	if(!TestPointer(glGetnHistogramARB)) bIsLoaded = 0;
	glGetnMinmaxARB = (PFNGLGETNMINMAXARBPROC)gleIntGetProcAddress("glGetnMinmaxARB");
	if(!TestPointer(glGetnMinmaxARB)) bIsLoaded = 0;
	glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC)gleIntGetProcAddress("glGetnTexImageARB");
	if(!TestPointer(glGetnTexImageARB)) bIsLoaded = 0;
	glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC)gleIntGetProcAddress("glReadnPixelsARB");
	if(!TestPointer(glReadnPixelsARB)) bIsLoaded = 0;
	glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)gleIntGetProcAddress("glGetnCompressedTexImageARB");
	if(!TestPointer(glGetnCompressedTexImageARB)) bIsLoaded = 0;
	glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC)gleIntGetProcAddress("glGetnUniformfvARB");
	if(!TestPointer(glGetnUniformfvARB)) bIsLoaded = 0;
	glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC)gleIntGetProcAddress("glGetnUniformivARB");
	if(!TestPointer(glGetnUniformivARB)) bIsLoaded = 0;
	glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC)gleIntGetProcAddress("glGetnUniformuivARB");
	if(!TestPointer(glGetnUniformuivARB)) bIsLoaded = 0;
	glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC)gleIntGetProcAddress("glGetnUniformdvARB");
	if(!TestPointer(glGetnUniformdvARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLMINSAMPLESHADINGARBARBPROC)(GLclampf value);

PFNGLMINSAMPLESHADINGARBARBPROC glMinSampleShadingARBARB;

static int gleIntLoad_ARB_sample_shading()
{
	int bIsLoaded = 1;
	glMinSampleShadingARBARB = (PFNGLMINSAMPLESHADINGARBARBPROC)gleIntGetProcAddress("glMinSampleShadingARBARB");
	if(!TestPointer(glMinSampleShadingARBARB)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGENSAMPLERSPROC __gleGenSamplers;
PFNGLDELETESAMPLERSPROC __gleDeleteSamplers;
PFNGLISSAMPLERPROC __gleIsSampler;
PFNGLBINDSAMPLERPROC __gleBindSampler;
PFNGLSAMPLERPARAMETERIPROC __gleSamplerParameteri;
PFNGLSAMPLERPARAMETERIVPROC __gleSamplerParameteriv;
PFNGLSAMPLERPARAMETERFPROC __gleSamplerParameterf;
PFNGLSAMPLERPARAMETERFVPROC __gleSamplerParameterfv;
PFNGLSAMPLERPARAMETERIIVPROC __gleSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC __gleSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERIVPROC __gleGetSamplerParameteriv;
PFNGLGETSAMPLERPARAMETERIIVPROC __gleGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERFVPROC __gleGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIUIVPROC __gleGetSamplerParameterIuiv;

static int gleIntLoad_ARB_sampler_objects()
{
	int bIsLoaded = 1;
	__gleGenSamplers = (PFNGLGENSAMPLERSPROC)gleIntGetProcAddress("glGenSamplers");
	if(!TestPointer(__gleGenSamplers)) bIsLoaded = 0;
	__gleDeleteSamplers = (PFNGLDELETESAMPLERSPROC)gleIntGetProcAddress("glDeleteSamplers");
	if(!TestPointer(__gleDeleteSamplers)) bIsLoaded = 0;
	__gleIsSampler = (PFNGLISSAMPLERPROC)gleIntGetProcAddress("glIsSampler");
	if(!TestPointer(__gleIsSampler)) bIsLoaded = 0;
	__gleBindSampler = (PFNGLBINDSAMPLERPROC)gleIntGetProcAddress("glBindSampler");
	if(!TestPointer(__gleBindSampler)) bIsLoaded = 0;
	__gleSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)gleIntGetProcAddress("glSamplerParameteri");
	if(!TestPointer(__gleSamplerParameteri)) bIsLoaded = 0;
	__gleSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)gleIntGetProcAddress("glSamplerParameteriv");
	if(!TestPointer(__gleSamplerParameteriv)) bIsLoaded = 0;
	__gleSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)gleIntGetProcAddress("glSamplerParameterf");
	if(!TestPointer(__gleSamplerParameterf)) bIsLoaded = 0;
	__gleSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)gleIntGetProcAddress("glSamplerParameterfv");
	if(!TestPointer(__gleSamplerParameterfv)) bIsLoaded = 0;
	__gleSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)gleIntGetProcAddress("glSamplerParameterIiv");
	if(!TestPointer(__gleSamplerParameterIiv)) bIsLoaded = 0;
	__gleSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)gleIntGetProcAddress("glSamplerParameterIuiv");
	if(!TestPointer(__gleSamplerParameterIuiv)) bIsLoaded = 0;
	__gleGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)gleIntGetProcAddress("glGetSamplerParameteriv");
	if(!TestPointer(__gleGetSamplerParameteriv)) bIsLoaded = 0;
	__gleGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)gleIntGetProcAddress("glGetSamplerParameterIiv");
	if(!TestPointer(__gleGetSamplerParameterIiv)) bIsLoaded = 0;
	__gleGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)gleIntGetProcAddress("glGetSamplerParameterfv");
	if(!TestPointer(__gleGetSamplerParameterfv)) bIsLoaded = 0;
	__gleGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)gleIntGetProcAddress("glGetSamplerParameterIuiv");
	if(!TestPointer(__gleGetSamplerParameterIuiv)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLUSEPROGRAMSTAGESPROC __gleUseProgramStages;
PFNGLACTIVESHADERPROGRAMPROC __gleActiveShaderProgram;
PFNGLCREATESHADERPROGRAMVPROC __gleCreateShaderProgramv;
PFNGLBINDPROGRAMPIPELINEPROC __gleBindProgramPipeline;
PFNGLDELETEPROGRAMPIPELINESPROC __gleDeleteProgramPipelines;
PFNGLGENPROGRAMPIPELINESPROC __gleGenProgramPipelines;
PFNGLISPROGRAMPIPELINEPROC __gleIsProgramPipeline;
PFNGLGETPROGRAMPIPELINEIVPROC __gleGetProgramPipelineiv;
PFNGLPROGRAMUNIFORM1IPROC __gleProgramUniform1i;
PFNGLPROGRAMUNIFORM1IVPROC __gleProgramUniform1iv;
PFNGLPROGRAMUNIFORM1FPROC __gleProgramUniform1f;
PFNGLPROGRAMUNIFORM1FVPROC __gleProgramUniform1fv;
PFNGLPROGRAMUNIFORM1DPROC __gleProgramUniform1d;
PFNGLPROGRAMUNIFORM1DVPROC __gleProgramUniform1dv;
PFNGLPROGRAMUNIFORM1UIPROC __gleProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UIVPROC __gleProgramUniform1uiv;
PFNGLPROGRAMUNIFORM2IPROC __gleProgramUniform2i;
PFNGLPROGRAMUNIFORM2IVPROC __gleProgramUniform2iv;
PFNGLPROGRAMUNIFORM2FPROC __gleProgramUniform2f;
PFNGLPROGRAMUNIFORM2FVPROC __gleProgramUniform2fv;
PFNGLPROGRAMUNIFORM2DPROC __gleProgramUniform2d;
PFNGLPROGRAMUNIFORM2DVPROC __gleProgramUniform2dv;
PFNGLPROGRAMUNIFORM2UIPROC __gleProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UIVPROC __gleProgramUniform2uiv;
PFNGLPROGRAMUNIFORM3IPROC __gleProgramUniform3i;
PFNGLPROGRAMUNIFORM3IVPROC __gleProgramUniform3iv;
PFNGLPROGRAMUNIFORM3FPROC __gleProgramUniform3f;
PFNGLPROGRAMUNIFORM3FVPROC __gleProgramUniform3fv;
PFNGLPROGRAMUNIFORM3DPROC __gleProgramUniform3d;
PFNGLPROGRAMUNIFORM3DVPROC __gleProgramUniform3dv;
PFNGLPROGRAMUNIFORM3UIPROC __gleProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UIVPROC __gleProgramUniform3uiv;
PFNGLPROGRAMUNIFORM4IPROC __gleProgramUniform4i;
PFNGLPROGRAMUNIFORM4IVPROC __gleProgramUniform4iv;
PFNGLPROGRAMUNIFORM4FPROC __gleProgramUniform4f;
PFNGLPROGRAMUNIFORM4FVPROC __gleProgramUniform4fv;
PFNGLPROGRAMUNIFORM4DPROC __gleProgramUniform4d;
PFNGLPROGRAMUNIFORM4DVPROC __gleProgramUniform4dv;
PFNGLPROGRAMUNIFORM4UIPROC __gleProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UIVPROC __gleProgramUniform4uiv;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC __gleProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC __gleProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC __gleProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC __gleProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC __gleProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC __gleProgramUniformMatrix4dv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC __gleProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC __gleProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC __gleProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC __gleProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC __gleProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC __gleProgramUniformMatrix4x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC __gleProgramUniformMatrix2x3dv;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC __gleProgramUniformMatrix3x2dv;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC __gleProgramUniformMatrix2x4dv;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC __gleProgramUniformMatrix4x2dv;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC __gleProgramUniformMatrix3x4dv;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC __gleProgramUniformMatrix4x3dv;
PFNGLVALIDATEPROGRAMPIPELINEPROC __gleValidateProgramPipeline;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC __gleGetProgramPipelineInfoLog;

static int gleIntLoad_ARB_separate_shader_objects()
{
	int bIsLoaded = 1;
	__gleUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)gleIntGetProcAddress("glUseProgramStages");
	if(!TestPointer(__gleUseProgramStages)) bIsLoaded = 0;
	__gleActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)gleIntGetProcAddress("glActiveShaderProgram");
	if(!TestPointer(__gleActiveShaderProgram)) bIsLoaded = 0;
	__gleCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)gleIntGetProcAddress("glCreateShaderProgramv");
	if(!TestPointer(__gleCreateShaderProgramv)) bIsLoaded = 0;
	__gleBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)gleIntGetProcAddress("glBindProgramPipeline");
	if(!TestPointer(__gleBindProgramPipeline)) bIsLoaded = 0;
	__gleDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)gleIntGetProcAddress("glDeleteProgramPipelines");
	if(!TestPointer(__gleDeleteProgramPipelines)) bIsLoaded = 0;
	__gleGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)gleIntGetProcAddress("glGenProgramPipelines");
	if(!TestPointer(__gleGenProgramPipelines)) bIsLoaded = 0;
	__gleIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)gleIntGetProcAddress("glIsProgramPipeline");
	if(!TestPointer(__gleIsProgramPipeline)) bIsLoaded = 0;
	__gleGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)gleIntGetProcAddress("glGetProgramPipelineiv");
	if(!TestPointer(__gleGetProgramPipelineiv)) bIsLoaded = 0;
	__gleProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)gleIntGetProcAddress("glProgramUniform1i");
	if(!TestPointer(__gleProgramUniform1i)) bIsLoaded = 0;
	__gleProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)gleIntGetProcAddress("glProgramUniform1iv");
	if(!TestPointer(__gleProgramUniform1iv)) bIsLoaded = 0;
	__gleProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)gleIntGetProcAddress("glProgramUniform1f");
	if(!TestPointer(__gleProgramUniform1f)) bIsLoaded = 0;
	__gleProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)gleIntGetProcAddress("glProgramUniform1fv");
	if(!TestPointer(__gleProgramUniform1fv)) bIsLoaded = 0;
	__gleProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)gleIntGetProcAddress("glProgramUniform1d");
	if(!TestPointer(__gleProgramUniform1d)) bIsLoaded = 0;
	__gleProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)gleIntGetProcAddress("glProgramUniform1dv");
	if(!TestPointer(__gleProgramUniform1dv)) bIsLoaded = 0;
	__gleProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)gleIntGetProcAddress("glProgramUniform1ui");
	if(!TestPointer(__gleProgramUniform1ui)) bIsLoaded = 0;
	__gleProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)gleIntGetProcAddress("glProgramUniform1uiv");
	if(!TestPointer(__gleProgramUniform1uiv)) bIsLoaded = 0;
	__gleProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)gleIntGetProcAddress("glProgramUniform2i");
	if(!TestPointer(__gleProgramUniform2i)) bIsLoaded = 0;
	__gleProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)gleIntGetProcAddress("glProgramUniform2iv");
	if(!TestPointer(__gleProgramUniform2iv)) bIsLoaded = 0;
	__gleProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)gleIntGetProcAddress("glProgramUniform2f");
	if(!TestPointer(__gleProgramUniform2f)) bIsLoaded = 0;
	__gleProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)gleIntGetProcAddress("glProgramUniform2fv");
	if(!TestPointer(__gleProgramUniform2fv)) bIsLoaded = 0;
	__gleProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)gleIntGetProcAddress("glProgramUniform2d");
	if(!TestPointer(__gleProgramUniform2d)) bIsLoaded = 0;
	__gleProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)gleIntGetProcAddress("glProgramUniform2dv");
	if(!TestPointer(__gleProgramUniform2dv)) bIsLoaded = 0;
	__gleProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)gleIntGetProcAddress("glProgramUniform2ui");
	if(!TestPointer(__gleProgramUniform2ui)) bIsLoaded = 0;
	__gleProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)gleIntGetProcAddress("glProgramUniform2uiv");
	if(!TestPointer(__gleProgramUniform2uiv)) bIsLoaded = 0;
	__gleProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)gleIntGetProcAddress("glProgramUniform3i");
	if(!TestPointer(__gleProgramUniform3i)) bIsLoaded = 0;
	__gleProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)gleIntGetProcAddress("glProgramUniform3iv");
	if(!TestPointer(__gleProgramUniform3iv)) bIsLoaded = 0;
	__gleProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)gleIntGetProcAddress("glProgramUniform3f");
	if(!TestPointer(__gleProgramUniform3f)) bIsLoaded = 0;
	__gleProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)gleIntGetProcAddress("glProgramUniform3fv");
	if(!TestPointer(__gleProgramUniform3fv)) bIsLoaded = 0;
	__gleProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)gleIntGetProcAddress("glProgramUniform3d");
	if(!TestPointer(__gleProgramUniform3d)) bIsLoaded = 0;
	__gleProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)gleIntGetProcAddress("glProgramUniform3dv");
	if(!TestPointer(__gleProgramUniform3dv)) bIsLoaded = 0;
	__gleProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)gleIntGetProcAddress("glProgramUniform3ui");
	if(!TestPointer(__gleProgramUniform3ui)) bIsLoaded = 0;
	__gleProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)gleIntGetProcAddress("glProgramUniform3uiv");
	if(!TestPointer(__gleProgramUniform3uiv)) bIsLoaded = 0;
	__gleProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)gleIntGetProcAddress("glProgramUniform4i");
	if(!TestPointer(__gleProgramUniform4i)) bIsLoaded = 0;
	__gleProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)gleIntGetProcAddress("glProgramUniform4iv");
	if(!TestPointer(__gleProgramUniform4iv)) bIsLoaded = 0;
	__gleProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)gleIntGetProcAddress("glProgramUniform4f");
	if(!TestPointer(__gleProgramUniform4f)) bIsLoaded = 0;
	__gleProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)gleIntGetProcAddress("glProgramUniform4fv");
	if(!TestPointer(__gleProgramUniform4fv)) bIsLoaded = 0;
	__gleProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)gleIntGetProcAddress("glProgramUniform4d");
	if(!TestPointer(__gleProgramUniform4d)) bIsLoaded = 0;
	__gleProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)gleIntGetProcAddress("glProgramUniform4dv");
	if(!TestPointer(__gleProgramUniform4dv)) bIsLoaded = 0;
	__gleProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)gleIntGetProcAddress("glProgramUniform4ui");
	if(!TestPointer(__gleProgramUniform4ui)) bIsLoaded = 0;
	__gleProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)gleIntGetProcAddress("glProgramUniform4uiv");
	if(!TestPointer(__gleProgramUniform4uiv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2fv");
	if(!TestPointer(__gleProgramUniformMatrix2fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3fv");
	if(!TestPointer(__gleProgramUniformMatrix3fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4fv");
	if(!TestPointer(__gleProgramUniformMatrix4fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2dv");
	if(!TestPointer(__gleProgramUniformMatrix2dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3dv");
	if(!TestPointer(__gleProgramUniformMatrix3dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4dv");
	if(!TestPointer(__gleProgramUniformMatrix4dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3fv");
	if(!TestPointer(__gleProgramUniformMatrix2x3fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2fv");
	if(!TestPointer(__gleProgramUniformMatrix3x2fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4fv");
	if(!TestPointer(__gleProgramUniformMatrix2x4fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2fv");
	if(!TestPointer(__gleProgramUniformMatrix4x2fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4fv");
	if(!TestPointer(__gleProgramUniformMatrix3x4fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3fv");
	if(!TestPointer(__gleProgramUniformMatrix4x3fv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3dv");
	if(!TestPointer(__gleProgramUniformMatrix2x3dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2dv");
	if(!TestPointer(__gleProgramUniformMatrix3x2dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4dv");
	if(!TestPointer(__gleProgramUniformMatrix2x4dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2dv");
	if(!TestPointer(__gleProgramUniformMatrix4x2dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4dv");
	if(!TestPointer(__gleProgramUniformMatrix3x4dv)) bIsLoaded = 0;
	__gleProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3dv");
	if(!TestPointer(__gleProgramUniformMatrix4x3dv)) bIsLoaded = 0;
	__gleValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)gleIntGetProcAddress("glValidateProgramPipeline");
	if(!TestPointer(__gleValidateProgramPipeline)) bIsLoaded = 0;
	__gleGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)gleIntGetProcAddress("glGetProgramPipelineInfoLog");
	if(!TestPointer(__gleGetProgramPipelineInfoLog)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
PFNGLGETHANDLEARBPROC glGetHandleARB;
PFNGLDETACHOBJECTARBPROC glDetachObjectARB;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
PFNGLUNIFORM1FARBPROC glUniform1fARB;
PFNGLUNIFORM2FARBPROC glUniform2fARB;
PFNGLUNIFORM3FARBPROC glUniform3fARB;
PFNGLUNIFORM4FARBPROC glUniform4fARB;
PFNGLUNIFORM1IARBPROC glUniform1iARB;
PFNGLUNIFORM2IARBPROC glUniform2iARB;
PFNGLUNIFORM3IARBPROC glUniform3iARB;
PFNGLUNIFORM4IARBPROC glUniform4iARB;
PFNGLUNIFORM1FVARBPROC glUniform1fvARB;
PFNGLUNIFORM2FVARBPROC glUniform2fvARB;
PFNGLUNIFORM3FVARBPROC glUniform3fvARB;
PFNGLUNIFORM4FVARBPROC glUniform4fvARB;
PFNGLUNIFORM1IVARBPROC glUniform1ivARB;
PFNGLUNIFORM2IVARBPROC glUniform2ivARB;
PFNGLUNIFORM3IVARBPROC glUniform3ivARB;
PFNGLUNIFORM4IVARBPROC glUniform4ivARB;
PFNGLUNIFORMMATRIX2FVARBPROC glUniformMatrix2fvARB;
PFNGLUNIFORMMATRIX3FVARBPROC glUniformMatrix3fvARB;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB;
PFNGLGETOBJECTPARAMETERFVARBPROC glGetObjectParameterfvARB;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
PFNGLGETATTACHEDOBJECTSARBPROC glGetAttachedObjectsARB;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
PFNGLGETACTIVEUNIFORMARBPROC glGetActiveUniformARB;
PFNGLGETUNIFORMFVARBPROC glGetUniformfvARB;
PFNGLGETUNIFORMIVARBPROC glGetUniformivARB;
PFNGLGETSHADERSOURCEARBPROC glGetShaderSourceARB;

static int gleIntLoad_ARB_shader_objects()
{
	int bIsLoaded = 1;
	glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)gleIntGetProcAddress("glDeleteObjectARB");
	if(!TestPointer(glDeleteObjectARB)) bIsLoaded = 0;
	glGetHandleARB = (PFNGLGETHANDLEARBPROC)gleIntGetProcAddress("glGetHandleARB");
	if(!TestPointer(glGetHandleARB)) bIsLoaded = 0;
	glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC)gleIntGetProcAddress("glDetachObjectARB");
	if(!TestPointer(glDetachObjectARB)) bIsLoaded = 0;
	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)gleIntGetProcAddress("glCreateShaderObjectARB");
	if(!TestPointer(glCreateShaderObjectARB)) bIsLoaded = 0;
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)gleIntGetProcAddress("glShaderSourceARB");
	if(!TestPointer(glShaderSourceARB)) bIsLoaded = 0;
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)gleIntGetProcAddress("glCompileShaderARB");
	if(!TestPointer(glCompileShaderARB)) bIsLoaded = 0;
	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)gleIntGetProcAddress("glCreateProgramObjectARB");
	if(!TestPointer(glCreateProgramObjectARB)) bIsLoaded = 0;
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)gleIntGetProcAddress("glAttachObjectARB");
	if(!TestPointer(glAttachObjectARB)) bIsLoaded = 0;
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)gleIntGetProcAddress("glLinkProgramARB");
	if(!TestPointer(glLinkProgramARB)) bIsLoaded = 0;
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)gleIntGetProcAddress("glUseProgramObjectARB");
	if(!TestPointer(glUseProgramObjectARB)) bIsLoaded = 0;
	glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC)gleIntGetProcAddress("glValidateProgramARB");
	if(!TestPointer(glValidateProgramARB)) bIsLoaded = 0;
	glUniform1fARB = (PFNGLUNIFORM1FARBPROC)gleIntGetProcAddress("glUniform1fARB");
	if(!TestPointer(glUniform1fARB)) bIsLoaded = 0;
	glUniform2fARB = (PFNGLUNIFORM2FARBPROC)gleIntGetProcAddress("glUniform2fARB");
	if(!TestPointer(glUniform2fARB)) bIsLoaded = 0;
	glUniform3fARB = (PFNGLUNIFORM3FARBPROC)gleIntGetProcAddress("glUniform3fARB");
	if(!TestPointer(glUniform3fARB)) bIsLoaded = 0;
	glUniform4fARB = (PFNGLUNIFORM4FARBPROC)gleIntGetProcAddress("glUniform4fARB");
	if(!TestPointer(glUniform4fARB)) bIsLoaded = 0;
	glUniform1iARB = (PFNGLUNIFORM1IARBPROC)gleIntGetProcAddress("glUniform1iARB");
	if(!TestPointer(glUniform1iARB)) bIsLoaded = 0;
	glUniform2iARB = (PFNGLUNIFORM2IARBPROC)gleIntGetProcAddress("glUniform2iARB");
	if(!TestPointer(glUniform2iARB)) bIsLoaded = 0;
	glUniform3iARB = (PFNGLUNIFORM3IARBPROC)gleIntGetProcAddress("glUniform3iARB");
	if(!TestPointer(glUniform3iARB)) bIsLoaded = 0;
	glUniform4iARB = (PFNGLUNIFORM4IARBPROC)gleIntGetProcAddress("glUniform4iARB");
	if(!TestPointer(glUniform4iARB)) bIsLoaded = 0;
	glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)gleIntGetProcAddress("glUniform1fvARB");
	if(!TestPointer(glUniform1fvARB)) bIsLoaded = 0;
	glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)gleIntGetProcAddress("glUniform2fvARB");
	if(!TestPointer(glUniform2fvARB)) bIsLoaded = 0;
	glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)gleIntGetProcAddress("glUniform3fvARB");
	if(!TestPointer(glUniform3fvARB)) bIsLoaded = 0;
	glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)gleIntGetProcAddress("glUniform4fvARB");
	if(!TestPointer(glUniform4fvARB)) bIsLoaded = 0;
	glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)gleIntGetProcAddress("glUniform1ivARB");
	if(!TestPointer(glUniform1ivARB)) bIsLoaded = 0;
	glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)gleIntGetProcAddress("glUniform2ivARB");
	if(!TestPointer(glUniform2ivARB)) bIsLoaded = 0;
	glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)gleIntGetProcAddress("glUniform3ivARB");
	if(!TestPointer(glUniform3ivARB)) bIsLoaded = 0;
	glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)gleIntGetProcAddress("glUniform4ivARB");
	if(!TestPointer(glUniform4ivARB)) bIsLoaded = 0;
	glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)gleIntGetProcAddress("glUniformMatrix2fvARB");
	if(!TestPointer(glUniformMatrix2fvARB)) bIsLoaded = 0;
	glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)gleIntGetProcAddress("glUniformMatrix3fvARB");
	if(!TestPointer(glUniformMatrix3fvARB)) bIsLoaded = 0;
	glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)gleIntGetProcAddress("glUniformMatrix4fvARB");
	if(!TestPointer(glUniformMatrix4fvARB)) bIsLoaded = 0;
	glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)gleIntGetProcAddress("glGetObjectParameterfvARB");
	if(!TestPointer(glGetObjectParameterfvARB)) bIsLoaded = 0;
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)gleIntGetProcAddress("glGetObjectParameterivARB");
	if(!TestPointer(glGetObjectParameterivARB)) bIsLoaded = 0;
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)gleIntGetProcAddress("glGetInfoLogARB");
	if(!TestPointer(glGetInfoLogARB)) bIsLoaded = 0;
	glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)gleIntGetProcAddress("glGetAttachedObjectsARB");
	if(!TestPointer(glGetAttachedObjectsARB)) bIsLoaded = 0;
	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)gleIntGetProcAddress("glGetUniformLocationARB");
	if(!TestPointer(glGetUniformLocationARB)) bIsLoaded = 0;
	glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)gleIntGetProcAddress("glGetActiveUniformARB");
	if(!TestPointer(glGetActiveUniformARB)) bIsLoaded = 0;
	glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC)gleIntGetProcAddress("glGetUniformfvARB");
	if(!TestPointer(glGetUniformfvARB)) bIsLoaded = 0;
	glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC)gleIntGetProcAddress("glGetUniformivARB");
	if(!TestPointer(glGetUniformivARB)) bIsLoaded = 0;
	glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC)gleIntGetProcAddress("glGetShaderSourceARB");
	if(!TestPointer(glGetShaderSourceARB)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef GLint (GLE_FUNCPTR * PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (GLE_FUNCPTR * PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint *values);

PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC __gleGetSubroutineUniformLocation;
PFNGLGETSUBROUTINEINDEXPROC __gleGetSubroutineIndex;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC __gleGetActiveSubroutineUniformiv;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC __gleGetActiveSubroutineUniformName;
PFNGLGETACTIVESUBROUTINENAMEPROC __gleGetActiveSubroutineName;
PFNGLUNIFORMSUBROUTINESUIVPROC __gleUniformSubroutinesuiv;
PFNGLGETUNIFORMSUBROUTINEUIVPROC __gleGetUniformSubroutineuiv;
PFNGLGETPROGRAMSTAGEIVPROC __gleGetProgramStageiv;

static int gleIntLoad_ARB_shader_subroutine()
{
	int bIsLoaded = 1;
	__gleGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)gleIntGetProcAddress("glGetSubroutineUniformLocation");
	if(!TestPointer(__gleGetSubroutineUniformLocation)) bIsLoaded = 0;
	__gleGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)gleIntGetProcAddress("glGetSubroutineIndex");
	if(!TestPointer(__gleGetSubroutineIndex)) bIsLoaded = 0;
	__gleGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)gleIntGetProcAddress("glGetActiveSubroutineUniformiv");
	if(!TestPointer(__gleGetActiveSubroutineUniformiv)) bIsLoaded = 0;
	__gleGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)gleIntGetProcAddress("glGetActiveSubroutineUniformName");
	if(!TestPointer(__gleGetActiveSubroutineUniformName)) bIsLoaded = 0;
	__gleGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)gleIntGetProcAddress("glGetActiveSubroutineName");
	if(!TestPointer(__gleGetActiveSubroutineName)) bIsLoaded = 0;
	__gleUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)gleIntGetProcAddress("glUniformSubroutinesuiv");
	if(!TestPointer(__gleUniformSubroutinesuiv)) bIsLoaded = 0;
	__gleGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)gleIntGetProcAddress("glGetUniformSubroutineuiv");
	if(!TestPointer(__gleGetUniformSubroutineuiv)) bIsLoaded = 0;
	__gleGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)gleIntGetProcAddress("glGetProgramStageiv");
	if(!TestPointer(__gleGetProgramStageiv)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLNAMEDSTRINGARBPROC)(GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string);
typedef void (GLE_FUNCPTR * PFNGLDELETENAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLCOMPILESHADERINCLUDEARBPROC)(GLuint shader, GLsizei count, const GLchar* *path, const GLint *length);
typedef GLboolean (GLE_FUNCPTR * PFNGLISNAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDSTRINGARBPROC)(GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string);
typedef void (GLE_FUNCPTR * PFNGLGETNAMEDSTRINGIVARBPROC)(GLint namelen, const GLchar *name, GLenum pname, GLint *params);

PFNGLNAMEDSTRINGARBPROC glNamedStringARB;
PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB;
PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB;
PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB;
PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB;

static int gleIntLoad_ARB_shading_language_include()
{
	int bIsLoaded = 1;
	glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)gleIntGetProcAddress("glNamedStringARB");
	if(!TestPointer(glNamedStringARB)) bIsLoaded = 0;
	glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)gleIntGetProcAddress("glDeleteNamedStringARB");
	if(!TestPointer(glDeleteNamedStringARB)) bIsLoaded = 0;
	glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)gleIntGetProcAddress("glCompileShaderIncludeARB");
	if(!TestPointer(glCompileShaderIncludeARB)) bIsLoaded = 0;
	glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)gleIntGetProcAddress("glIsNamedStringARB");
	if(!TestPointer(glIsNamedStringARB)) bIsLoaded = 0;
	glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)gleIntGetProcAddress("glGetNamedStringARB");
	if(!TestPointer(glGetNamedStringARB)) bIsLoaded = 0;
	glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)gleIntGetProcAddress("glGetNamedStringivARB");
	if(!TestPointer(glGetNamedStringivARB)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef GLsync (GLE_FUNCPTR * PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
typedef GLboolean (GLE_FUNCPTR * PFNGLISSYNCPROC)(GLsync sync);
typedef void (GLE_FUNCPTR * PFNGLDELETESYNCPROC)(GLsync sync);
typedef GLenum (GLE_FUNCPTR * PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLE_FUNCPTR * PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 *params);
typedef void (GLE_FUNCPTR * PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);

PFNGLFENCESYNCPROC __gleFenceSync;
PFNGLISSYNCPROC __gleIsSync;
PFNGLDELETESYNCPROC __gleDeleteSync;
PFNGLCLIENTWAITSYNCPROC __gleClientWaitSync;
PFNGLWAITSYNCPROC __gleWaitSync;
PFNGLGETINTEGER64VPROC __gleGetInteger64v;
PFNGLGETSYNCIVPROC __gleGetSynciv;

static int gleIntLoad_ARB_sync()
{
	int bIsLoaded = 1;
	__gleFenceSync = (PFNGLFENCESYNCPROC)gleIntGetProcAddress("glFenceSync");
	if(!TestPointer(__gleFenceSync)) bIsLoaded = 0;
	__gleIsSync = (PFNGLISSYNCPROC)gleIntGetProcAddress("glIsSync");
	if(!TestPointer(__gleIsSync)) bIsLoaded = 0;
	__gleDeleteSync = (PFNGLDELETESYNCPROC)gleIntGetProcAddress("glDeleteSync");
	if(!TestPointer(__gleDeleteSync)) bIsLoaded = 0;
	__gleClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)gleIntGetProcAddress("glClientWaitSync");
	if(!TestPointer(__gleClientWaitSync)) bIsLoaded = 0;
	__gleWaitSync = (PFNGLWAITSYNCPROC)gleIntGetProcAddress("glWaitSync");
	if(!TestPointer(__gleWaitSync)) bIsLoaded = 0;
	__gleGetInteger64v = (PFNGLGETINTEGER64VPROC)gleIntGetProcAddress("glGetInteger64v");
	if(!TestPointer(__gleGetInteger64v)) bIsLoaded = 0;
	__gleGetSynciv = (PFNGLGETSYNCIVPROC)gleIntGetProcAddress("glGetSynciv");
	if(!TestPointer(__gleGetSynciv)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
typedef void (GLE_FUNCPTR * PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat *values);

PFNGLPATCHPARAMETERIPROC __glePatchParameteri;
PFNGLPATCHPARAMETERFVPROC __glePatchParameterfv;

static int gleIntLoad_ARB_tessellation_shader()
{
	int bIsLoaded = 1;
	__glePatchParameteri = (PFNGLPATCHPARAMETERIPROC)gleIntGetProcAddress("glPatchParameteri");
	if(!TestPointer(__glePatchParameteri)) bIsLoaded = 0;
	__glePatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)gleIntGetProcAddress("glPatchParameterfv");
	if(!TestPointer(__glePatchParameterfv)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTEXBUFFERARBPROC)(GLenum target, GLenum internalformat, GLuint buffer);

PFNGLTEXBUFFERARBPROC glTexBufferARB;

static int gleIntLoad_ARB_texture_buffer_object()
{
	int bIsLoaded = 1;
	glTexBufferARB = (PFNGLTEXBUFFERARBPROC)gleIntGetProcAddress("glTexBufferARB");
	if(!TestPointer(glTexBufferARB)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)(GLenum target, GLint level, GLvoid *img);

PFNGLCOMPRESSEDTEXIMAGE3DARBPROC glCompressedTexImage3DARB;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC glCompressedTexImage1DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1DARB;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC glGetCompressedTexImageARB;

static int gleIntLoad_ARB_texture_compression()
{
	int bIsLoaded = 1;
	glCompressedTexImage3DARB = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)gleIntGetProcAddress("glCompressedTexImage3DARB");
	if(!TestPointer(glCompressedTexImage3DARB)) bIsLoaded = 0;
	glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)gleIntGetProcAddress("glCompressedTexImage2DARB");
	if(!TestPointer(glCompressedTexImage2DARB)) bIsLoaded = 0;
	glCompressedTexImage1DARB = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)gleIntGetProcAddress("glCompressedTexImage1DARB");
	if(!TestPointer(glCompressedTexImage1DARB)) bIsLoaded = 0;
	glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)gleIntGetProcAddress("glCompressedTexSubImage3DARB");
	if(!TestPointer(glCompressedTexSubImage3DARB)) bIsLoaded = 0;
	glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)gleIntGetProcAddress("glCompressedTexSubImage2DARB");
	if(!TestPointer(glCompressedTexSubImage2DARB)) bIsLoaded = 0;
	glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)gleIntGetProcAddress("glCompressedTexSubImage1DARB");
	if(!TestPointer(glCompressedTexSubImage1DARB)) bIsLoaded = 0;
	glGetCompressedTexImageARB = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)gleIntGetProcAddress("glGetCompressedTexImageARB");
	if(!TestPointer(glGetCompressedTexImageARB)) bIsLoaded = 0;
	return bIsLoaded;
}











typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (GLE_FUNCPTR * PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat *val);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKIPROC)(GLuint index, GLbitfield mask);

PFNGLTEXIMAGE2DMULTISAMPLEPROC __gleTexImage2DMultisample;
PFNGLTEXIMAGE3DMULTISAMPLEPROC __gleTexImage3DMultisample;
PFNGLGETMULTISAMPLEFVPROC __gleGetMultisamplefv;
PFNGLSAMPLEMASKIPROC __gleSampleMaski;

static int gleIntLoad_ARB_texture_multisample()
{
	int bIsLoaded = 1;
	__gleTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)gleIntGetProcAddress("glTexImage2DMultisample");
	if(!TestPointer(__gleTexImage2DMultisample)) bIsLoaded = 0;
	__gleTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)gleIntGetProcAddress("glTexImage3DMultisample");
	if(!TestPointer(__gleTexImage3DMultisample)) bIsLoaded = 0;
	__gleGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)gleIntGetProcAddress("glGetMultisamplefv");
	if(!TestPointer(__gleGetMultisamplefv)) bIsLoaded = 0;
	__gleSampleMaski = (PFNGLSAMPLEMASKIPROC)gleIntGetProcAddress("glSampleMaski");
	if(!TestPointer(__gleSampleMaski)) bIsLoaded = 0;
	return bIsLoaded;
}






typedef void (GLE_FUNCPTR * PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 *params);

PFNGLQUERYCOUNTERPROC __gleQueryCounter;
PFNGLGETQUERYOBJECTI64VPROC __gleGetQueryObjecti64v;
PFNGLGETQUERYOBJECTUI64VPROC __gleGetQueryObjectui64v;

static int gleIntLoad_ARB_timer_query()
{
	int bIsLoaded = 1;
	__gleQueryCounter = (PFNGLQUERYCOUNTERPROC)gleIntGetProcAddress("glQueryCounter");
	if(!TestPointer(__gleQueryCounter)) bIsLoaded = 0;
	__gleGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)gleIntGetProcAddress("glGetQueryObjecti64v");
	if(!TestPointer(__gleGetQueryObjecti64v)) bIsLoaded = 0;
	__gleGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)gleIntGetProcAddress("glGetQueryObjectui64v");
	if(!TestPointer(__gleGetQueryObjectui64v)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLPAUSETRANSFORMFEEDBACKPROC)();
typedef void (GLE_FUNCPTR * PFNGLRESUMETRANSFORMFEEDBACKPROC)();
typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);

PFNGLBINDTRANSFORMFEEDBACKPROC __gleBindTransformFeedback;
PFNGLDELETETRANSFORMFEEDBACKSPROC __gleDeleteTransformFeedbacks;
PFNGLGENTRANSFORMFEEDBACKSPROC __gleGenTransformFeedbacks;
PFNGLISTRANSFORMFEEDBACKPROC __gleIsTransformFeedback;
PFNGLPAUSETRANSFORMFEEDBACKPROC __glePauseTransformFeedback;
PFNGLRESUMETRANSFORMFEEDBACKPROC __gleResumeTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKPROC __gleDrawTransformFeedback;

static int gleIntLoad_ARB_transform_feedback2()
{
	int bIsLoaded = 1;
	__gleBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glBindTransformFeedback");
	if(!TestPointer(__gleBindTransformFeedback)) bIsLoaded = 0;
	__gleDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)gleIntGetProcAddress("glDeleteTransformFeedbacks");
	if(!TestPointer(__gleDeleteTransformFeedbacks)) bIsLoaded = 0;
	__gleGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)gleIntGetProcAddress("glGenTransformFeedbacks");
	if(!TestPointer(__gleGenTransformFeedbacks)) bIsLoaded = 0;
	__gleIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glIsTransformFeedback");
	if(!TestPointer(__gleIsTransformFeedback)) bIsLoaded = 0;
	__glePauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glPauseTransformFeedback");
	if(!TestPointer(__glePauseTransformFeedback)) bIsLoaded = 0;
	__gleResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glResumeTransformFeedback");
	if(!TestPointer(__gleResumeTransformFeedback)) bIsLoaded = 0;
	__gleDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glDrawTransformFeedback");
	if(!TestPointer(__gleDrawTransformFeedback)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);

PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC __gleDrawTransformFeedbackStream;
PFNGLBEGINQUERYINDEXEDPROC __gleBeginQueryIndexed;
PFNGLENDQUERYINDEXEDPROC __gleEndQueryIndexed;
PFNGLGETQUERYINDEXEDIVPROC __gleGetQueryIndexediv;

static int gleIntLoad_ARB_transform_feedback3()
{
	int bIsLoaded = 1;
	__gleDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)gleIntGetProcAddress("glDrawTransformFeedbackStream");
	if(!TestPointer(__gleDrawTransformFeedbackStream)) bIsLoaded = 0;
	__gleBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)gleIntGetProcAddress("glBeginQueryIndexed");
	if(!TestPointer(__gleBeginQueryIndexed)) bIsLoaded = 0;
	__gleEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)gleIntGetProcAddress("glEndQueryIndexed");
	if(!TestPointer(__gleEndQueryIndexed)) bIsLoaded = 0;
	__gleGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)gleIntGetProcAddress("glGetQueryIndexediv");
	if(!TestPointer(__gleGetQueryIndexediv)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXFARBPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXDARBPROC)(const GLdouble *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXFARBPROC)(const GLfloat *m);
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXDARBPROC)(const GLdouble *m);

PFNGLLOADTRANSPOSEMATRIXFARBPROC glLoadTransposeMatrixfARB;
PFNGLLOADTRANSPOSEMATRIXDARBPROC glLoadTransposeMatrixdARB;
PFNGLMULTTRANSPOSEMATRIXFARBPROC glMultTransposeMatrixfARB;
PFNGLMULTTRANSPOSEMATRIXDARBPROC glMultTransposeMatrixdARB;

static int gleIntLoad_ARB_transpose_matrix()
{
	int bIsLoaded = 1;
	glLoadTransposeMatrixfARB = (PFNGLLOADTRANSPOSEMATRIXFARBPROC)gleIntGetProcAddress("glLoadTransposeMatrixfARB");
	if(!TestPointer(glLoadTransposeMatrixfARB)) bIsLoaded = 0;
	glLoadTransposeMatrixdARB = (PFNGLLOADTRANSPOSEMATRIXDARBPROC)gleIntGetProcAddress("glLoadTransposeMatrixdARB");
	if(!TestPointer(glLoadTransposeMatrixdARB)) bIsLoaded = 0;
	glMultTransposeMatrixfARB = (PFNGLMULTTRANSPOSEMATRIXFARBPROC)gleIntGetProcAddress("glMultTransposeMatrixfARB");
	if(!TestPointer(glMultTransposeMatrixfARB)) bIsLoaded = 0;
	glMultTransposeMatrixdARB = (PFNGLMULTTRANSPOSEMATRIXDARBPROC)gleIntGetProcAddress("glMultTransposeMatrixdARB");
	if(!TestPointer(glMultTransposeMatrixdARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar* *uniformNames, GLuint *uniformIndices);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (GLE_FUNCPTR * PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar *uniformBlockName);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (GLE_FUNCPTR * PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

PFNGLGETUNIFORMINDICESPROC __gleGetUniformIndices;
PFNGLGETACTIVEUNIFORMSIVPROC __gleGetActiveUniformsiv;
PFNGLGETACTIVEUNIFORMNAMEPROC __gleGetActiveUniformName;
PFNGLGETUNIFORMBLOCKINDEXPROC __gleGetUniformBlockIndex;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC __gleGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC __gleGetActiveUniformBlockName;
PFNGLUNIFORMBLOCKBINDINGPROC __gleUniformBlockBinding;

static int gleIntLoad_ARB_uniform_buffer_object()
{
	int bIsLoaded = 1;
	__gleGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)gleIntGetProcAddress("glGetUniformIndices");
	if(!TestPointer(__gleGetUniformIndices)) bIsLoaded = 0;
	__gleGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)gleIntGetProcAddress("glGetActiveUniformsiv");
	if(!TestPointer(__gleGetActiveUniformsiv)) bIsLoaded = 0;
	__gleGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)gleIntGetProcAddress("glGetActiveUniformName");
	if(!TestPointer(__gleGetActiveUniformName)) bIsLoaded = 0;
	__gleGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)gleIntGetProcAddress("glGetUniformBlockIndex");
	if(!TestPointer(__gleGetUniformBlockIndex)) bIsLoaded = 0;
	__gleGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)gleIntGetProcAddress("glGetActiveUniformBlockiv");
	if(!TestPointer(__gleGetActiveUniformBlockiv)) bIsLoaded = 0;
	__gleGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)gleIntGetProcAddress("glGetActiveUniformBlockName");
	if(!TestPointer(__gleGetActiveUniformBlockName)) bIsLoaded = 0;
	__gleUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)gleIntGetProcAddress("glUniformBlockBinding");
	if(!TestPointer(__gleUniformBlockBinding)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (GLE_FUNCPTR * PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void (GLE_FUNCPTR * PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef GLboolean (GLE_FUNCPTR * PFNGLISVERTEXARRAYPROC)(GLuint array);

PFNGLBINDVERTEXARRAYPROC __gleBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC __gleDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC __gleGenVertexArrays;
PFNGLISVERTEXARRAYPROC __gleIsVertexArray;

static int gleIntLoad_ARB_vertex_array_object()
{
	int bIsLoaded = 1;
	__gleBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)gleIntGetProcAddress("glBindVertexArray");
	if(!TestPointer(__gleBindVertexArray)) bIsLoaded = 0;
	__gleDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)gleIntGetProcAddress("glDeleteVertexArrays");
	if(!TestPointer(__gleDeleteVertexArrays)) bIsLoaded = 0;
	__gleGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)gleIntGetProcAddress("glGenVertexArrays");
	if(!TestPointer(__gleGenVertexArrays)) bIsLoaded = 0;
	__gleIsVertexArray = (PFNGLISVERTEXARRAYPROC)gleIntGetProcAddress("glIsVertexArray");
	if(!TestPointer(__gleIsVertexArray)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVERTEXATTRIBL1DPROC __gleVertexAttribL1d;
PFNGLVERTEXATTRIBL2DPROC __gleVertexAttribL2d;
PFNGLVERTEXATTRIBL3DPROC __gleVertexAttribL3d;
PFNGLVERTEXATTRIBL4DPROC __gleVertexAttribL4d;
PFNGLVERTEXATTRIBL1DVPROC __gleVertexAttribL1dv;
PFNGLVERTEXATTRIBL2DVPROC __gleVertexAttribL2dv;
PFNGLVERTEXATTRIBL3DVPROC __gleVertexAttribL3dv;
PFNGLVERTEXATTRIBL4DVPROC __gleVertexAttribL4dv;
PFNGLVERTEXATTRIBLPOINTERPROC __gleVertexAttribLPointer;
PFNGLGETVERTEXATTRIBLDVPROC __gleGetVertexAttribLdv;

static int gleIntLoad_ARB_vertex_attrib_64bit()
{
	int bIsLoaded = 1;
	__gleVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)gleIntGetProcAddress("glVertexAttribL1d");
	if(!TestPointer(__gleVertexAttribL1d)) bIsLoaded = 0;
	__gleVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)gleIntGetProcAddress("glVertexAttribL2d");
	if(!TestPointer(__gleVertexAttribL2d)) bIsLoaded = 0;
	__gleVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)gleIntGetProcAddress("glVertexAttribL3d");
	if(!TestPointer(__gleVertexAttribL3d)) bIsLoaded = 0;
	__gleVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)gleIntGetProcAddress("glVertexAttribL4d");
	if(!TestPointer(__gleVertexAttribL4d)) bIsLoaded = 0;
	__gleVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)gleIntGetProcAddress("glVertexAttribL1dv");
	if(!TestPointer(__gleVertexAttribL1dv)) bIsLoaded = 0;
	__gleVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)gleIntGetProcAddress("glVertexAttribL2dv");
	if(!TestPointer(__gleVertexAttribL2dv)) bIsLoaded = 0;
	__gleVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)gleIntGetProcAddress("glVertexAttribL3dv");
	if(!TestPointer(__gleVertexAttribL3dv)) bIsLoaded = 0;
	__gleVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)gleIntGetProcAddress("glVertexAttribL4dv");
	if(!TestPointer(__gleVertexAttribL4dv)) bIsLoaded = 0;
	__gleVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)gleIntGetProcAddress("glVertexAttribLPointer");
	if(!TestPointer(__gleVertexAttribLPointer)) bIsLoaded = 0;
	__gleGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)gleIntGetProcAddress("glGetVertexAttribLdv");
	if(!TestPointer(__gleGetVertexAttribLdv)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLWEIGHTBVARBPROC glWeightbvARB;
PFNGLWEIGHTSVARBPROC glWeightsvARB;
PFNGLWEIGHTIVARBPROC glWeightivARB;
PFNGLWEIGHTFVARBPROC glWeightfvARB;
PFNGLWEIGHTDVARBPROC glWeightdvARB;
PFNGLWEIGHTUBVARBPROC glWeightubvARB;
PFNGLWEIGHTUSVARBPROC glWeightusvARB;
PFNGLWEIGHTUIVARBPROC glWeightuivARB;
PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB;
PFNGLVERTEXBLENDARBPROC glVertexBlendARB;

static int gleIntLoad_ARB_vertex_blend()
{
	int bIsLoaded = 1;
	glWeightbvARB = (PFNGLWEIGHTBVARBPROC)gleIntGetProcAddress("glWeightbvARB");
	if(!TestPointer(glWeightbvARB)) bIsLoaded = 0;
	glWeightsvARB = (PFNGLWEIGHTSVARBPROC)gleIntGetProcAddress("glWeightsvARB");
	if(!TestPointer(glWeightsvARB)) bIsLoaded = 0;
	glWeightivARB = (PFNGLWEIGHTIVARBPROC)gleIntGetProcAddress("glWeightivARB");
	if(!TestPointer(glWeightivARB)) bIsLoaded = 0;
	glWeightfvARB = (PFNGLWEIGHTFVARBPROC)gleIntGetProcAddress("glWeightfvARB");
	if(!TestPointer(glWeightfvARB)) bIsLoaded = 0;
	glWeightdvARB = (PFNGLWEIGHTDVARBPROC)gleIntGetProcAddress("glWeightdvARB");
	if(!TestPointer(glWeightdvARB)) bIsLoaded = 0;
	glWeightubvARB = (PFNGLWEIGHTUBVARBPROC)gleIntGetProcAddress("glWeightubvARB");
	if(!TestPointer(glWeightubvARB)) bIsLoaded = 0;
	glWeightusvARB = (PFNGLWEIGHTUSVARBPROC)gleIntGetProcAddress("glWeightusvARB");
	if(!TestPointer(glWeightusvARB)) bIsLoaded = 0;
	glWeightuivARB = (PFNGLWEIGHTUIVARBPROC)gleIntGetProcAddress("glWeightuivARB");
	if(!TestPointer(glWeightuivARB)) bIsLoaded = 0;
	glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC)gleIntGetProcAddress("glWeightPointerARB");
	if(!TestPointer(glWeightPointerARB)) bIsLoaded = 0;
	glVertexBlendARB = (PFNGLVERTEXBLENDARBPROC)gleIntGetProcAddress("glVertexBlendARB");
	if(!TestPointer(glVertexBlendARB)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLISBUFFERARBPROC glIsBufferARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
PFNGLMAPBUFFERARBPROC glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;

static int gleIntLoad_ARB_vertex_buffer_object()
{
	int bIsLoaded = 1;
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)gleIntGetProcAddress("glBindBufferARB");
	if(!TestPointer(glBindBufferARB)) bIsLoaded = 0;
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)gleIntGetProcAddress("glDeleteBuffersARB");
	if(!TestPointer(glDeleteBuffersARB)) bIsLoaded = 0;
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)gleIntGetProcAddress("glGenBuffersARB");
	if(!TestPointer(glGenBuffersARB)) bIsLoaded = 0;
	glIsBufferARB = (PFNGLISBUFFERARBPROC)gleIntGetProcAddress("glIsBufferARB");
	if(!TestPointer(glIsBufferARB)) bIsLoaded = 0;
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)gleIntGetProcAddress("glBufferDataARB");
	if(!TestPointer(glBufferDataARB)) bIsLoaded = 0;
	glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)gleIntGetProcAddress("glBufferSubDataARB");
	if(!TestPointer(glBufferSubDataARB)) bIsLoaded = 0;
	glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)gleIntGetProcAddress("glGetBufferSubDataARB");
	if(!TestPointer(glGetBufferSubDataARB)) bIsLoaded = 0;
	glMapBufferARB = (PFNGLMAPBUFFERARBPROC)gleIntGetProcAddress("glMapBufferARB");
	if(!TestPointer(glMapBufferARB)) bIsLoaded = 0;
	glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)gleIntGetProcAddress("glUnmapBufferARB");
	if(!TestPointer(glUnmapBufferARB)) bIsLoaded = 0;
	glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)gleIntGetProcAddress("glGetBufferParameterivARB");
	if(!TestPointer(glGetBufferParameterivARB)) bIsLoaded = 0;
	glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)gleIntGetProcAddress("glGetBufferPointervARB");
	if(!TestPointer(glGetBufferPointervARB)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVERTEXATTRIB1DARBPROC glVertexAttrib1dARB;
PFNGLVERTEXATTRIB1DVARBPROC glVertexAttrib1dvARB;
PFNGLVERTEXATTRIB1FARBPROC glVertexAttrib1fARB;
PFNGLVERTEXATTRIB1FVARBPROC glVertexAttrib1fvARB;
PFNGLVERTEXATTRIB1SARBPROC glVertexAttrib1sARB;
PFNGLVERTEXATTRIB1SVARBPROC glVertexAttrib1svARB;
PFNGLVERTEXATTRIB2DARBPROC glVertexAttrib2dARB;
PFNGLVERTEXATTRIB2DVARBPROC glVertexAttrib2dvARB;
PFNGLVERTEXATTRIB2FARBPROC glVertexAttrib2fARB;
PFNGLVERTEXATTRIB2FVARBPROC glVertexAttrib2fvARB;
PFNGLVERTEXATTRIB2SARBPROC glVertexAttrib2sARB;
PFNGLVERTEXATTRIB2SVARBPROC glVertexAttrib2svARB;
PFNGLVERTEXATTRIB3DARBPROC glVertexAttrib3dARB;
PFNGLVERTEXATTRIB3DVARBPROC glVertexAttrib3dvARB;
PFNGLVERTEXATTRIB3FARBPROC glVertexAttrib3fARB;
PFNGLVERTEXATTRIB3FVARBPROC glVertexAttrib3fvARB;
PFNGLVERTEXATTRIB3SARBPROC glVertexAttrib3sARB;
PFNGLVERTEXATTRIB3SVARBPROC glVertexAttrib3svARB;
PFNGLVERTEXATTRIB4NBVARBPROC glVertexAttrib4NbvARB;
PFNGLVERTEXATTRIB4NIVARBPROC glVertexAttrib4NivARB;
PFNGLVERTEXATTRIB4NSVARBPROC glVertexAttrib4NsvARB;
PFNGLVERTEXATTRIB4NUBARBPROC glVertexAttrib4NubARB;
PFNGLVERTEXATTRIB4NUBVARBPROC glVertexAttrib4NubvARB;
PFNGLVERTEXATTRIB4NUIVARBPROC glVertexAttrib4NuivARB;
PFNGLVERTEXATTRIB4NUSVARBPROC glVertexAttrib4NusvARB;
PFNGLVERTEXATTRIB4BVARBPROC glVertexAttrib4bvARB;
PFNGLVERTEXATTRIB4DARBPROC glVertexAttrib4dARB;
PFNGLVERTEXATTRIB4DVARBPROC glVertexAttrib4dvARB;
PFNGLVERTEXATTRIB4FARBPROC glVertexAttrib4fARB;
PFNGLVERTEXATTRIB4FVARBPROC glVertexAttrib4fvARB;
PFNGLVERTEXATTRIB4IVARBPROC glVertexAttrib4ivARB;
PFNGLVERTEXATTRIB4SARBPROC glVertexAttrib4sARB;
PFNGLVERTEXATTRIB4SVARBPROC glVertexAttrib4svARB;
PFNGLVERTEXATTRIB4UBVARBPROC glVertexAttrib4ubvARB;
PFNGLVERTEXATTRIB4UIVARBPROC glVertexAttrib4uivARB;
PFNGLVERTEXATTRIB4USVARBPROC glVertexAttrib4usvARB;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
PFNGLPROGRAMSTRINGARBPROC glProgramStringARB;
PFNGLBINDPROGRAMARBPROC glBindProgramARB;
PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB;
PFNGLGENPROGRAMSARBPROC glGenProgramsARB;
PFNGLPROGRAMENVPARAMETER4DARBPROC glProgramEnvParameter4dARB;
PFNGLPROGRAMENVPARAMETER4DVARBPROC glProgramEnvParameter4dvARB;
PFNGLPROGRAMENVPARAMETER4FARBPROC glProgramEnvParameter4fARB;
PFNGLPROGRAMENVPARAMETER4FVARBPROC glProgramEnvParameter4fvARB;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glProgramLocalParameter4dARB;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glProgramLocalParameter4dvARB;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glProgramLocalParameter4fARB;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glGetProgramEnvParameterdvARB;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glGetProgramEnvParameterfvARB;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glGetProgramLocalParameterdvARB;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glGetProgramLocalParameterfvARB;
PFNGLGETPROGRAMIVARBPROC glGetProgramivARB;
PFNGLGETPROGRAMSTRINGARBPROC glGetProgramStringARB;
PFNGLGETVERTEXATTRIBDVARBPROC glGetVertexAttribdvARB;
PFNGLGETVERTEXATTRIBFVARBPROC glGetVertexAttribfvARB;
PFNGLGETVERTEXATTRIBIVARBPROC glGetVertexAttribivARB;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glGetVertexAttribPointervARB;
PFNGLISPROGRAMARBPROC glIsProgramARB;

static int gleIntLoad_ARB_vertex_program()
{
	int bIsLoaded = 1;
	glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC)gleIntGetProcAddress("glVertexAttrib1dARB");
	if(!TestPointer(glVertexAttrib1dARB)) bIsLoaded = 0;
	glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC)gleIntGetProcAddress("glVertexAttrib1dvARB");
	if(!TestPointer(glVertexAttrib1dvARB)) bIsLoaded = 0;
	glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC)gleIntGetProcAddress("glVertexAttrib1fARB");
	if(!TestPointer(glVertexAttrib1fARB)) bIsLoaded = 0;
	glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC)gleIntGetProcAddress("glVertexAttrib1fvARB");
	if(!TestPointer(glVertexAttrib1fvARB)) bIsLoaded = 0;
	glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC)gleIntGetProcAddress("glVertexAttrib1sARB");
	if(!TestPointer(glVertexAttrib1sARB)) bIsLoaded = 0;
	glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC)gleIntGetProcAddress("glVertexAttrib1svARB");
	if(!TestPointer(glVertexAttrib1svARB)) bIsLoaded = 0;
	glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC)gleIntGetProcAddress("glVertexAttrib2dARB");
	if(!TestPointer(glVertexAttrib2dARB)) bIsLoaded = 0;
	glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC)gleIntGetProcAddress("glVertexAttrib2dvARB");
	if(!TestPointer(glVertexAttrib2dvARB)) bIsLoaded = 0;
	glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC)gleIntGetProcAddress("glVertexAttrib2fARB");
	if(!TestPointer(glVertexAttrib2fARB)) bIsLoaded = 0;
	glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC)gleIntGetProcAddress("glVertexAttrib2fvARB");
	if(!TestPointer(glVertexAttrib2fvARB)) bIsLoaded = 0;
	glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC)gleIntGetProcAddress("glVertexAttrib2sARB");
	if(!TestPointer(glVertexAttrib2sARB)) bIsLoaded = 0;
	glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC)gleIntGetProcAddress("glVertexAttrib2svARB");
	if(!TestPointer(glVertexAttrib2svARB)) bIsLoaded = 0;
	glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC)gleIntGetProcAddress("glVertexAttrib3dARB");
	if(!TestPointer(glVertexAttrib3dARB)) bIsLoaded = 0;
	glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC)gleIntGetProcAddress("glVertexAttrib3dvARB");
	if(!TestPointer(glVertexAttrib3dvARB)) bIsLoaded = 0;
	glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC)gleIntGetProcAddress("glVertexAttrib3fARB");
	if(!TestPointer(glVertexAttrib3fARB)) bIsLoaded = 0;
	glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC)gleIntGetProcAddress("glVertexAttrib3fvARB");
	if(!TestPointer(glVertexAttrib3fvARB)) bIsLoaded = 0;
	glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC)gleIntGetProcAddress("glVertexAttrib3sARB");
	if(!TestPointer(glVertexAttrib3sARB)) bIsLoaded = 0;
	glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC)gleIntGetProcAddress("glVertexAttrib3svARB");
	if(!TestPointer(glVertexAttrib3svARB)) bIsLoaded = 0;
	glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC)gleIntGetProcAddress("glVertexAttrib4NbvARB");
	if(!TestPointer(glVertexAttrib4NbvARB)) bIsLoaded = 0;
	glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC)gleIntGetProcAddress("glVertexAttrib4NivARB");
	if(!TestPointer(glVertexAttrib4NivARB)) bIsLoaded = 0;
	glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC)gleIntGetProcAddress("glVertexAttrib4NsvARB");
	if(!TestPointer(glVertexAttrib4NsvARB)) bIsLoaded = 0;
	glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC)gleIntGetProcAddress("glVertexAttrib4NubARB");
	if(!TestPointer(glVertexAttrib4NubARB)) bIsLoaded = 0;
	glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC)gleIntGetProcAddress("glVertexAttrib4NubvARB");
	if(!TestPointer(glVertexAttrib4NubvARB)) bIsLoaded = 0;
	glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC)gleIntGetProcAddress("glVertexAttrib4NuivARB");
	if(!TestPointer(glVertexAttrib4NuivARB)) bIsLoaded = 0;
	glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC)gleIntGetProcAddress("glVertexAttrib4NusvARB");
	if(!TestPointer(glVertexAttrib4NusvARB)) bIsLoaded = 0;
	glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC)gleIntGetProcAddress("glVertexAttrib4bvARB");
	if(!TestPointer(glVertexAttrib4bvARB)) bIsLoaded = 0;
	glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC)gleIntGetProcAddress("glVertexAttrib4dARB");
	if(!TestPointer(glVertexAttrib4dARB)) bIsLoaded = 0;
	glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC)gleIntGetProcAddress("glVertexAttrib4dvARB");
	if(!TestPointer(glVertexAttrib4dvARB)) bIsLoaded = 0;
	glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC)gleIntGetProcAddress("glVertexAttrib4fARB");
	if(!TestPointer(glVertexAttrib4fARB)) bIsLoaded = 0;
	glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC)gleIntGetProcAddress("glVertexAttrib4fvARB");
	if(!TestPointer(glVertexAttrib4fvARB)) bIsLoaded = 0;
	glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC)gleIntGetProcAddress("glVertexAttrib4ivARB");
	if(!TestPointer(glVertexAttrib4ivARB)) bIsLoaded = 0;
	glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC)gleIntGetProcAddress("glVertexAttrib4sARB");
	if(!TestPointer(glVertexAttrib4sARB)) bIsLoaded = 0;
	glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC)gleIntGetProcAddress("glVertexAttrib4svARB");
	if(!TestPointer(glVertexAttrib4svARB)) bIsLoaded = 0;
	glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC)gleIntGetProcAddress("glVertexAttrib4ubvARB");
	if(!TestPointer(glVertexAttrib4ubvARB)) bIsLoaded = 0;
	glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC)gleIntGetProcAddress("glVertexAttrib4uivARB");
	if(!TestPointer(glVertexAttrib4uivARB)) bIsLoaded = 0;
	glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC)gleIntGetProcAddress("glVertexAttrib4usvARB");
	if(!TestPointer(glVertexAttrib4usvARB)) bIsLoaded = 0;
	glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)gleIntGetProcAddress("glVertexAttribPointerARB");
	if(!TestPointer(glVertexAttribPointerARB)) bIsLoaded = 0;
	glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)gleIntGetProcAddress("glEnableVertexAttribArrayARB");
	if(!TestPointer(glEnableVertexAttribArrayARB)) bIsLoaded = 0;
	glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)gleIntGetProcAddress("glDisableVertexAttribArrayARB");
	if(!TestPointer(glDisableVertexAttribArrayARB)) bIsLoaded = 0;
	glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)gleIntGetProcAddress("glProgramStringARB");
	if(!TestPointer(glProgramStringARB)) bIsLoaded = 0;
	glBindProgramARB = (PFNGLBINDPROGRAMARBPROC)gleIntGetProcAddress("glBindProgramARB");
	if(!TestPointer(glBindProgramARB)) bIsLoaded = 0;
	glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC)gleIntGetProcAddress("glDeleteProgramsARB");
	if(!TestPointer(glDeleteProgramsARB)) bIsLoaded = 0;
	glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC)gleIntGetProcAddress("glGenProgramsARB");
	if(!TestPointer(glGenProgramsARB)) bIsLoaded = 0;
	glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC)gleIntGetProcAddress("glProgramEnvParameter4dARB");
	if(!TestPointer(glProgramEnvParameter4dARB)) bIsLoaded = 0;
	glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC)gleIntGetProcAddress("glProgramEnvParameter4dvARB");
	if(!TestPointer(glProgramEnvParameter4dvARB)) bIsLoaded = 0;
	glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC)gleIntGetProcAddress("glProgramEnvParameter4fARB");
	if(!TestPointer(glProgramEnvParameter4fARB)) bIsLoaded = 0;
	glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)gleIntGetProcAddress("glProgramEnvParameter4fvARB");
	if(!TestPointer(glProgramEnvParameter4fvARB)) bIsLoaded = 0;
	glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)gleIntGetProcAddress("glProgramLocalParameter4dARB");
	if(!TestPointer(glProgramLocalParameter4dARB)) bIsLoaded = 0;
	glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)gleIntGetProcAddress("glProgramLocalParameter4dvARB");
	if(!TestPointer(glProgramLocalParameter4dvARB)) bIsLoaded = 0;
	glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)gleIntGetProcAddress("glProgramLocalParameter4fARB");
	if(!TestPointer(glProgramLocalParameter4fARB)) bIsLoaded = 0;
	glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)gleIntGetProcAddress("glProgramLocalParameter4fvARB");
	if(!TestPointer(glProgramLocalParameter4fvARB)) bIsLoaded = 0;
	glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC)gleIntGetProcAddress("glGetProgramEnvParameterdvARB");
	if(!TestPointer(glGetProgramEnvParameterdvARB)) bIsLoaded = 0;
	glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)gleIntGetProcAddress("glGetProgramEnvParameterfvARB");
	if(!TestPointer(glGetProgramEnvParameterfvARB)) bIsLoaded = 0;
	glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)gleIntGetProcAddress("glGetProgramLocalParameterdvARB");
	if(!TestPointer(glGetProgramLocalParameterdvARB)) bIsLoaded = 0;
	glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)gleIntGetProcAddress("glGetProgramLocalParameterfvARB");
	if(!TestPointer(glGetProgramLocalParameterfvARB)) bIsLoaded = 0;
	glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC)gleIntGetProcAddress("glGetProgramivARB");
	if(!TestPointer(glGetProgramivARB)) bIsLoaded = 0;
	glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC)gleIntGetProcAddress("glGetProgramStringARB");
	if(!TestPointer(glGetProgramStringARB)) bIsLoaded = 0;
	glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC)gleIntGetProcAddress("glGetVertexAttribdvARB");
	if(!TestPointer(glGetVertexAttribdvARB)) bIsLoaded = 0;
	glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC)gleIntGetProcAddress("glGetVertexAttribfvARB");
	if(!TestPointer(glGetVertexAttribfvARB)) bIsLoaded = 0;
	glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC)gleIntGetProcAddress("glGetVertexAttribivARB");
	if(!TestPointer(glGetVertexAttribivARB)) bIsLoaded = 0;
	glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC)gleIntGetProcAddress("glGetVertexAttribPointervARB");
	if(!TestPointer(glGetVertexAttribPointervARB)) bIsLoaded = 0;
	glIsProgramARB = (PFNGLISPROGRAMARBPROC)gleIntGetProcAddress("glIsProgramARB");
	if(!TestPointer(glIsProgramARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBINDATTRIBLOCATIONARBPROC)(GLhandleARB programObj, GLuint index, const GLcharARB *name);
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEATTRIBARBPROC)(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
typedef GLint (GLE_FUNCPTR * PFNGLGETATTRIBLOCATIONARBPROC)(GLhandleARB programObj, const GLcharARB *name);

PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB;
PFNGLGETACTIVEATTRIBARBPROC glGetActiveAttribARB;
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB;

static int gleIntLoad_ARB_vertex_shader()
{
	int bIsLoaded = 1;
	glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC)gleIntGetProcAddress("glBindAttribLocationARB");
	if(!TestPointer(glBindAttribLocationARB)) bIsLoaded = 0;
	glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC)gleIntGetProcAddress("glGetActiveAttribARB");
	if(!TestPointer(glGetActiveAttribARB)) bIsLoaded = 0;
	glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)gleIntGetProcAddress("glGetAttribLocationARB");
	if(!TestPointer(glGetAttribLocationARB)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVERTEXP2UIPROC __gleVertexP2ui;
PFNGLVERTEXP2UIVPROC __gleVertexP2uiv;
PFNGLVERTEXP3UIPROC __gleVertexP3ui;
PFNGLVERTEXP3UIVPROC __gleVertexP3uiv;
PFNGLVERTEXP4UIPROC __gleVertexP4ui;
PFNGLVERTEXP4UIVPROC __gleVertexP4uiv;
PFNGLTEXCOORDP1UIPROC __gleTexCoordP1ui;
PFNGLTEXCOORDP1UIVPROC __gleTexCoordP1uiv;
PFNGLTEXCOORDP2UIPROC __gleTexCoordP2ui;
PFNGLTEXCOORDP2UIVPROC __gleTexCoordP2uiv;
PFNGLTEXCOORDP3UIPROC __gleTexCoordP3ui;
PFNGLTEXCOORDP3UIVPROC __gleTexCoordP3uiv;
PFNGLTEXCOORDP4UIPROC __gleTexCoordP4ui;
PFNGLTEXCOORDP4UIVPROC __gleTexCoordP4uiv;
PFNGLMULTITEXCOORDP1UIPROC __gleMultiTexCoordP1ui;
PFNGLMULTITEXCOORDP1UIVPROC __gleMultiTexCoordP1uiv;
PFNGLMULTITEXCOORDP2UIPROC __gleMultiTexCoordP2ui;
PFNGLMULTITEXCOORDP2UIVPROC __gleMultiTexCoordP2uiv;
PFNGLMULTITEXCOORDP3UIPROC __gleMultiTexCoordP3ui;
PFNGLMULTITEXCOORDP3UIVPROC __gleMultiTexCoordP3uiv;
PFNGLMULTITEXCOORDP4UIPROC __gleMultiTexCoordP4ui;
PFNGLMULTITEXCOORDP4UIVPROC __gleMultiTexCoordP4uiv;
PFNGLNORMALP3UIPROC __gleNormalP3ui;
PFNGLNORMALP3UIVPROC __gleNormalP3uiv;
PFNGLCOLORP3UIPROC __gleColorP3ui;
PFNGLCOLORP3UIVPROC __gleColorP3uiv;
PFNGLCOLORP4UIPROC __gleColorP4ui;
PFNGLCOLORP4UIVPROC __gleColorP4uiv;
PFNGLSECONDARYCOLORP3UIPROC __gleSecondaryColorP3ui;
PFNGLSECONDARYCOLORP3UIVPROC __gleSecondaryColorP3uiv;
PFNGLVERTEXATTRIBP1UIPROC __gleVertexAttribP1ui;
PFNGLVERTEXATTRIBP1UIVPROC __gleVertexAttribP1uiv;
PFNGLVERTEXATTRIBP2UIPROC __gleVertexAttribP2ui;
PFNGLVERTEXATTRIBP2UIVPROC __gleVertexAttribP2uiv;
PFNGLVERTEXATTRIBP3UIPROC __gleVertexAttribP3ui;
PFNGLVERTEXATTRIBP3UIVPROC __gleVertexAttribP3uiv;
PFNGLVERTEXATTRIBP4UIPROC __gleVertexAttribP4ui;
PFNGLVERTEXATTRIBP4UIVPROC __gleVertexAttribP4uiv;

static int gleIntLoad_ARB_vertex_type_2_10_10_10_rev()
{
	int bIsLoaded = 1;
	__gleVertexP2ui = (PFNGLVERTEXP2UIPROC)gleIntGetProcAddress("glVertexP2ui");
	if(!TestPointer(__gleVertexP2ui)) bIsLoaded = 0;
	__gleVertexP2uiv = (PFNGLVERTEXP2UIVPROC)gleIntGetProcAddress("glVertexP2uiv");
	if(!TestPointer(__gleVertexP2uiv)) bIsLoaded = 0;
	__gleVertexP3ui = (PFNGLVERTEXP3UIPROC)gleIntGetProcAddress("glVertexP3ui");
	if(!TestPointer(__gleVertexP3ui)) bIsLoaded = 0;
	__gleVertexP3uiv = (PFNGLVERTEXP3UIVPROC)gleIntGetProcAddress("glVertexP3uiv");
	if(!TestPointer(__gleVertexP3uiv)) bIsLoaded = 0;
	__gleVertexP4ui = (PFNGLVERTEXP4UIPROC)gleIntGetProcAddress("glVertexP4ui");
	if(!TestPointer(__gleVertexP4ui)) bIsLoaded = 0;
	__gleVertexP4uiv = (PFNGLVERTEXP4UIVPROC)gleIntGetProcAddress("glVertexP4uiv");
	if(!TestPointer(__gleVertexP4uiv)) bIsLoaded = 0;
	__gleTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)gleIntGetProcAddress("glTexCoordP1ui");
	if(!TestPointer(__gleTexCoordP1ui)) bIsLoaded = 0;
	__gleTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)gleIntGetProcAddress("glTexCoordP1uiv");
	if(!TestPointer(__gleTexCoordP1uiv)) bIsLoaded = 0;
	__gleTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)gleIntGetProcAddress("glTexCoordP2ui");
	if(!TestPointer(__gleTexCoordP2ui)) bIsLoaded = 0;
	__gleTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)gleIntGetProcAddress("glTexCoordP2uiv");
	if(!TestPointer(__gleTexCoordP2uiv)) bIsLoaded = 0;
	__gleTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)gleIntGetProcAddress("glTexCoordP3ui");
	if(!TestPointer(__gleTexCoordP3ui)) bIsLoaded = 0;
	__gleTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)gleIntGetProcAddress("glTexCoordP3uiv");
	if(!TestPointer(__gleTexCoordP3uiv)) bIsLoaded = 0;
	__gleTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)gleIntGetProcAddress("glTexCoordP4ui");
	if(!TestPointer(__gleTexCoordP4ui)) bIsLoaded = 0;
	__gleTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)gleIntGetProcAddress("glTexCoordP4uiv");
	if(!TestPointer(__gleTexCoordP4uiv)) bIsLoaded = 0;
	__gleMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)gleIntGetProcAddress("glMultiTexCoordP1ui");
	if(!TestPointer(__gleMultiTexCoordP1ui)) bIsLoaded = 0;
	__gleMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)gleIntGetProcAddress("glMultiTexCoordP1uiv");
	if(!TestPointer(__gleMultiTexCoordP1uiv)) bIsLoaded = 0;
	__gleMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)gleIntGetProcAddress("glMultiTexCoordP2ui");
	if(!TestPointer(__gleMultiTexCoordP2ui)) bIsLoaded = 0;
	__gleMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)gleIntGetProcAddress("glMultiTexCoordP2uiv");
	if(!TestPointer(__gleMultiTexCoordP2uiv)) bIsLoaded = 0;
	__gleMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)gleIntGetProcAddress("glMultiTexCoordP3ui");
	if(!TestPointer(__gleMultiTexCoordP3ui)) bIsLoaded = 0;
	__gleMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)gleIntGetProcAddress("glMultiTexCoordP3uiv");
	if(!TestPointer(__gleMultiTexCoordP3uiv)) bIsLoaded = 0;
	__gleMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)gleIntGetProcAddress("glMultiTexCoordP4ui");
	if(!TestPointer(__gleMultiTexCoordP4ui)) bIsLoaded = 0;
	__gleMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)gleIntGetProcAddress("glMultiTexCoordP4uiv");
	if(!TestPointer(__gleMultiTexCoordP4uiv)) bIsLoaded = 0;
	__gleNormalP3ui = (PFNGLNORMALP3UIPROC)gleIntGetProcAddress("glNormalP3ui");
	if(!TestPointer(__gleNormalP3ui)) bIsLoaded = 0;
	__gleNormalP3uiv = (PFNGLNORMALP3UIVPROC)gleIntGetProcAddress("glNormalP3uiv");
	if(!TestPointer(__gleNormalP3uiv)) bIsLoaded = 0;
	__gleColorP3ui = (PFNGLCOLORP3UIPROC)gleIntGetProcAddress("glColorP3ui");
	if(!TestPointer(__gleColorP3ui)) bIsLoaded = 0;
	__gleColorP3uiv = (PFNGLCOLORP3UIVPROC)gleIntGetProcAddress("glColorP3uiv");
	if(!TestPointer(__gleColorP3uiv)) bIsLoaded = 0;
	__gleColorP4ui = (PFNGLCOLORP4UIPROC)gleIntGetProcAddress("glColorP4ui");
	if(!TestPointer(__gleColorP4ui)) bIsLoaded = 0;
	__gleColorP4uiv = (PFNGLCOLORP4UIVPROC)gleIntGetProcAddress("glColorP4uiv");
	if(!TestPointer(__gleColorP4uiv)) bIsLoaded = 0;
	__gleSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)gleIntGetProcAddress("glSecondaryColorP3ui");
	if(!TestPointer(__gleSecondaryColorP3ui)) bIsLoaded = 0;
	__gleSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)gleIntGetProcAddress("glSecondaryColorP3uiv");
	if(!TestPointer(__gleSecondaryColorP3uiv)) bIsLoaded = 0;
	__gleVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)gleIntGetProcAddress("glVertexAttribP1ui");
	if(!TestPointer(__gleVertexAttribP1ui)) bIsLoaded = 0;
	__gleVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)gleIntGetProcAddress("glVertexAttribP1uiv");
	if(!TestPointer(__gleVertexAttribP1uiv)) bIsLoaded = 0;
	__gleVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)gleIntGetProcAddress("glVertexAttribP2ui");
	if(!TestPointer(__gleVertexAttribP2ui)) bIsLoaded = 0;
	__gleVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)gleIntGetProcAddress("glVertexAttribP2uiv");
	if(!TestPointer(__gleVertexAttribP2uiv)) bIsLoaded = 0;
	__gleVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)gleIntGetProcAddress("glVertexAttribP3ui");
	if(!TestPointer(__gleVertexAttribP3ui)) bIsLoaded = 0;
	__gleVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)gleIntGetProcAddress("glVertexAttribP3uiv");
	if(!TestPointer(__gleVertexAttribP3uiv)) bIsLoaded = 0;
	__gleVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)gleIntGetProcAddress("glVertexAttribP4ui");
	if(!TestPointer(__gleVertexAttribP4ui)) bIsLoaded = 0;
	__gleVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)gleIntGetProcAddress("glVertexAttribP4uiv");
	if(!TestPointer(__gleVertexAttribP4uiv)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVIEWPORTARRAYVPROC __gleViewportArrayv;
PFNGLVIEWPORTINDEXEDFPROC __gleViewportIndexedf;
PFNGLVIEWPORTINDEXEDFVPROC __gleViewportIndexedfv;
PFNGLSCISSORARRAYVPROC __gleScissorArrayv;
PFNGLSCISSORINDEXEDPROC __gleScissorIndexed;
PFNGLSCISSORINDEXEDVPROC __gleScissorIndexedv;
PFNGLDEPTHRANGEARRAYVPROC __gleDepthRangeArrayv;
PFNGLDEPTHRANGEINDEXEDPROC __gleDepthRangeIndexed;
PFNGLGETFLOATI_VPROC __gleGetFloati_v;
PFNGLGETDOUBLEI_VPROC __gleGetDoublei_v;

static int gleIntLoad_ARB_viewport_array()
{
	int bIsLoaded = 1;
	__gleViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)gleIntGetProcAddress("glViewportArrayv");
	if(!TestPointer(__gleViewportArrayv)) bIsLoaded = 0;
	__gleViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)gleIntGetProcAddress("glViewportIndexedf");
	if(!TestPointer(__gleViewportIndexedf)) bIsLoaded = 0;
	__gleViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)gleIntGetProcAddress("glViewportIndexedfv");
	if(!TestPointer(__gleViewportIndexedfv)) bIsLoaded = 0;
	__gleScissorArrayv = (PFNGLSCISSORARRAYVPROC)gleIntGetProcAddress("glScissorArrayv");
	if(!TestPointer(__gleScissorArrayv)) bIsLoaded = 0;
	__gleScissorIndexed = (PFNGLSCISSORINDEXEDPROC)gleIntGetProcAddress("glScissorIndexed");
	if(!TestPointer(__gleScissorIndexed)) bIsLoaded = 0;
	__gleScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)gleIntGetProcAddress("glScissorIndexedv");
	if(!TestPointer(__gleScissorIndexedv)) bIsLoaded = 0;
	__gleDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)gleIntGetProcAddress("glDepthRangeArrayv");
	if(!TestPointer(__gleDepthRangeArrayv)) bIsLoaded = 0;
	__gleDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)gleIntGetProcAddress("glDepthRangeIndexed");
	if(!TestPointer(__gleDepthRangeIndexed)) bIsLoaded = 0;
	__gleGetFloati_v = (PFNGLGETFLOATI_VPROC)gleIntGetProcAddress("glGetFloati_v");
	if(!TestPointer(__gleGetFloati_v)) bIsLoaded = 0;
	__gleGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)gleIntGetProcAddress("glGetDoublei_v");
	if(!TestPointer(__gleGetDoublei_v)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLWINDOWPOS2DARBPROC glWindowPos2dARB;
PFNGLWINDOWPOS2DVARBPROC glWindowPos2dvARB;
PFNGLWINDOWPOS2FARBPROC glWindowPos2fARB;
PFNGLWINDOWPOS2FVARBPROC glWindowPos2fvARB;
PFNGLWINDOWPOS2IARBPROC glWindowPos2iARB;
PFNGLWINDOWPOS2IVARBPROC glWindowPos2ivARB;
PFNGLWINDOWPOS2SARBPROC glWindowPos2sARB;
PFNGLWINDOWPOS2SVARBPROC glWindowPos2svARB;
PFNGLWINDOWPOS3DARBPROC glWindowPos3dARB;
PFNGLWINDOWPOS3DVARBPROC glWindowPos3dvARB;
PFNGLWINDOWPOS3FARBPROC glWindowPos3fARB;
PFNGLWINDOWPOS3FVARBPROC glWindowPos3fvARB;
PFNGLWINDOWPOS3IARBPROC glWindowPos3iARB;
PFNGLWINDOWPOS3IVARBPROC glWindowPos3ivARB;
PFNGLWINDOWPOS3SARBPROC glWindowPos3sARB;
PFNGLWINDOWPOS3SVARBPROC glWindowPos3svARB;

static int gleIntLoad_ARB_window_pos()
{
	int bIsLoaded = 1;
	glWindowPos2dARB = (PFNGLWINDOWPOS2DARBPROC)gleIntGetProcAddress("glWindowPos2dARB");
	if(!TestPointer(glWindowPos2dARB)) bIsLoaded = 0;
	glWindowPos2dvARB = (PFNGLWINDOWPOS2DVARBPROC)gleIntGetProcAddress("glWindowPos2dvARB");
	if(!TestPointer(glWindowPos2dvARB)) bIsLoaded = 0;
	glWindowPos2fARB = (PFNGLWINDOWPOS2FARBPROC)gleIntGetProcAddress("glWindowPos2fARB");
	if(!TestPointer(glWindowPos2fARB)) bIsLoaded = 0;
	glWindowPos2fvARB = (PFNGLWINDOWPOS2FVARBPROC)gleIntGetProcAddress("glWindowPos2fvARB");
	if(!TestPointer(glWindowPos2fvARB)) bIsLoaded = 0;
	glWindowPos2iARB = (PFNGLWINDOWPOS2IARBPROC)gleIntGetProcAddress("glWindowPos2iARB");
	if(!TestPointer(glWindowPos2iARB)) bIsLoaded = 0;
	glWindowPos2ivARB = (PFNGLWINDOWPOS2IVARBPROC)gleIntGetProcAddress("glWindowPos2ivARB");
	if(!TestPointer(glWindowPos2ivARB)) bIsLoaded = 0;
	glWindowPos2sARB = (PFNGLWINDOWPOS2SARBPROC)gleIntGetProcAddress("glWindowPos2sARB");
	if(!TestPointer(glWindowPos2sARB)) bIsLoaded = 0;
	glWindowPos2svARB = (PFNGLWINDOWPOS2SVARBPROC)gleIntGetProcAddress("glWindowPos2svARB");
	if(!TestPointer(glWindowPos2svARB)) bIsLoaded = 0;
	glWindowPos3dARB = (PFNGLWINDOWPOS3DARBPROC)gleIntGetProcAddress("glWindowPos3dARB");
	if(!TestPointer(glWindowPos3dARB)) bIsLoaded = 0;
	glWindowPos3dvARB = (PFNGLWINDOWPOS3DVARBPROC)gleIntGetProcAddress("glWindowPos3dvARB");
	if(!TestPointer(glWindowPos3dvARB)) bIsLoaded = 0;
	glWindowPos3fARB = (PFNGLWINDOWPOS3FARBPROC)gleIntGetProcAddress("glWindowPos3fARB");
	if(!TestPointer(glWindowPos3fARB)) bIsLoaded = 0;
	glWindowPos3fvARB = (PFNGLWINDOWPOS3FVARBPROC)gleIntGetProcAddress("glWindowPos3fvARB");
	if(!TestPointer(glWindowPos3fvARB)) bIsLoaded = 0;
	glWindowPos3iARB = (PFNGLWINDOWPOS3IARBPROC)gleIntGetProcAddress("glWindowPos3iARB");
	if(!TestPointer(glWindowPos3iARB)) bIsLoaded = 0;
	glWindowPos3ivARB = (PFNGLWINDOWPOS3IVARBPROC)gleIntGetProcAddress("glWindowPos3ivARB");
	if(!TestPointer(glWindowPos3ivARB)) bIsLoaded = 0;
	glWindowPos3sARB = (PFNGLWINDOWPOS3SARBPROC)gleIntGetProcAddress("glWindowPos3sARB");
	if(!TestPointer(glWindowPos3sARB)) bIsLoaded = 0;
	glWindowPos3svARB = (PFNGLWINDOWPOS3SVARBPROC)gleIntGetProcAddress("glWindowPos3svARB");
	if(!TestPointer(glWindowPos3svARB)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSATIPROC)(GLsizei n, const GLenum *bufs);

PFNGLDRAWBUFFERSATIPROC glDrawBuffersATI;

static int gleIntLoad_ATI_draw_buffers()
{
	int bIsLoaded = 1;
	glDrawBuffersATI = (PFNGLDRAWBUFFERSATIPROC)gleIntGetProcAddress("glDrawBuffersATI");
	if(!TestPointer(glDrawBuffersATI)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLELEMENTPOINTERATIPROC)(GLenum type, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTARRAYATIPROC)(GLenum mode, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTARRAYATIPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count);

PFNGLELEMENTPOINTERATIPROC glElementPointerATI;
PFNGLDRAWELEMENTARRAYATIPROC glDrawElementArrayATI;
PFNGLDRAWRANGEELEMENTARRAYATIPROC glDrawRangeElementArrayATI;

static int gleIntLoad_ATI_element_array()
{
	int bIsLoaded = 1;
	glElementPointerATI = (PFNGLELEMENTPOINTERATIPROC)gleIntGetProcAddress("glElementPointerATI");
	if(!TestPointer(glElementPointerATI)) bIsLoaded = 0;
	glDrawElementArrayATI = (PFNGLDRAWELEMENTARRAYATIPROC)gleIntGetProcAddress("glDrawElementArrayATI");
	if(!TestPointer(glDrawElementArrayATI)) bIsLoaded = 0;
	glDrawRangeElementArrayATI = (PFNGLDRAWRANGEELEMENTARRAYATIPROC)gleIntGetProcAddress("glDrawRangeElementArrayATI");
	if(!TestPointer(glDrawRangeElementArrayATI)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLTEXBUMPPARAMETERIVATIPROC)(GLenum pname, const GLint *param);
typedef void (GLE_FUNCPTR * PFNGLTEXBUMPPARAMETERFVATIPROC)(GLenum pname, const GLfloat *param);
typedef void (GLE_FUNCPTR * PFNGLGETTEXBUMPPARAMETERIVATIPROC)(GLenum pname, GLint *param);
typedef void (GLE_FUNCPTR * PFNGLGETTEXBUMPPARAMETERFVATIPROC)(GLenum pname, GLfloat *param);

PFNGLTEXBUMPPARAMETERIVATIPROC glTexBumpParameterivATI;
PFNGLTEXBUMPPARAMETERFVATIPROC glTexBumpParameterfvATI;
PFNGLGETTEXBUMPPARAMETERIVATIPROC glGetTexBumpParameterivATI;
PFNGLGETTEXBUMPPARAMETERFVATIPROC glGetTexBumpParameterfvATI;

static int gleIntLoad_ATI_envmap_bumpmap()
{
	int bIsLoaded = 1;
	glTexBumpParameterivATI = (PFNGLTEXBUMPPARAMETERIVATIPROC)gleIntGetProcAddress("glTexBumpParameterivATI");
	if(!TestPointer(glTexBumpParameterivATI)) bIsLoaded = 0;
	glTexBumpParameterfvATI = (PFNGLTEXBUMPPARAMETERFVATIPROC)gleIntGetProcAddress("glTexBumpParameterfvATI");
	if(!TestPointer(glTexBumpParameterfvATI)) bIsLoaded = 0;
	glGetTexBumpParameterivATI = (PFNGLGETTEXBUMPPARAMETERIVATIPROC)gleIntGetProcAddress("glGetTexBumpParameterivATI");
	if(!TestPointer(glGetTexBumpParameterivATI)) bIsLoaded = 0;
	glGetTexBumpParameterfvATI = (PFNGLGETTEXBUMPPARAMETERFVATIPROC)gleIntGetProcAddress("glGetTexBumpParameterfvATI");
	if(!TestPointer(glGetTexBumpParameterfvATI)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGENFRAGMENTSHADERSATIPROC glGenFragmentShadersATI;
PFNGLBINDFRAGMENTSHADERATIPROC glBindFragmentShaderATI;
PFNGLDELETEFRAGMENTSHADERATIPROC glDeleteFragmentShaderATI;
PFNGLBEGINFRAGMENTSHADERATIPROC glBeginFragmentShaderATI;
PFNGLENDFRAGMENTSHADERATIPROC glEndFragmentShaderATI;
PFNGLPASSTEXCOORDATIPROC glPassTexCoordATI;
PFNGLSAMPLEMAPATIPROC glSampleMapATI;
PFNGLCOLORFRAGMENTOP1ATIPROC glColorFragmentOp1ATI;
PFNGLCOLORFRAGMENTOP2ATIPROC glColorFragmentOp2ATI;
PFNGLCOLORFRAGMENTOP3ATIPROC glColorFragmentOp3ATI;
PFNGLALPHAFRAGMENTOP1ATIPROC glAlphaFragmentOp1ATI;
PFNGLALPHAFRAGMENTOP2ATIPROC glAlphaFragmentOp2ATI;
PFNGLALPHAFRAGMENTOP3ATIPROC glAlphaFragmentOp3ATI;
PFNGLSETFRAGMENTSHADERCONSTANTATIPROC glSetFragmentShaderConstantATI;

static int gleIntLoad_ATI_fragment_shader()
{
	int bIsLoaded = 1;
	glGenFragmentShadersATI = (PFNGLGENFRAGMENTSHADERSATIPROC)gleIntGetProcAddress("glGenFragmentShadersATI");
	if(!TestPointer(glGenFragmentShadersATI)) bIsLoaded = 0;
	glBindFragmentShaderATI = (PFNGLBINDFRAGMENTSHADERATIPROC)gleIntGetProcAddress("glBindFragmentShaderATI");
	if(!TestPointer(glBindFragmentShaderATI)) bIsLoaded = 0;
	glDeleteFragmentShaderATI = (PFNGLDELETEFRAGMENTSHADERATIPROC)gleIntGetProcAddress("glDeleteFragmentShaderATI");
	if(!TestPointer(glDeleteFragmentShaderATI)) bIsLoaded = 0;
	glBeginFragmentShaderATI = (PFNGLBEGINFRAGMENTSHADERATIPROC)gleIntGetProcAddress("glBeginFragmentShaderATI");
	if(!TestPointer(glBeginFragmentShaderATI)) bIsLoaded = 0;
	glEndFragmentShaderATI = (PFNGLENDFRAGMENTSHADERATIPROC)gleIntGetProcAddress("glEndFragmentShaderATI");
	if(!TestPointer(glEndFragmentShaderATI)) bIsLoaded = 0;
	glPassTexCoordATI = (PFNGLPASSTEXCOORDATIPROC)gleIntGetProcAddress("glPassTexCoordATI");
	if(!TestPointer(glPassTexCoordATI)) bIsLoaded = 0;
	glSampleMapATI = (PFNGLSAMPLEMAPATIPROC)gleIntGetProcAddress("glSampleMapATI");
	if(!TestPointer(glSampleMapATI)) bIsLoaded = 0;
	glColorFragmentOp1ATI = (PFNGLCOLORFRAGMENTOP1ATIPROC)gleIntGetProcAddress("glColorFragmentOp1ATI");
	if(!TestPointer(glColorFragmentOp1ATI)) bIsLoaded = 0;
	glColorFragmentOp2ATI = (PFNGLCOLORFRAGMENTOP2ATIPROC)gleIntGetProcAddress("glColorFragmentOp2ATI");
	if(!TestPointer(glColorFragmentOp2ATI)) bIsLoaded = 0;
	glColorFragmentOp3ATI = (PFNGLCOLORFRAGMENTOP3ATIPROC)gleIntGetProcAddress("glColorFragmentOp3ATI");
	if(!TestPointer(glColorFragmentOp3ATI)) bIsLoaded = 0;
	glAlphaFragmentOp1ATI = (PFNGLALPHAFRAGMENTOP1ATIPROC)gleIntGetProcAddress("glAlphaFragmentOp1ATI");
	if(!TestPointer(glAlphaFragmentOp1ATI)) bIsLoaded = 0;
	glAlphaFragmentOp2ATI = (PFNGLALPHAFRAGMENTOP2ATIPROC)gleIntGetProcAddress("glAlphaFragmentOp2ATI");
	if(!TestPointer(glAlphaFragmentOp2ATI)) bIsLoaded = 0;
	glAlphaFragmentOp3ATI = (PFNGLALPHAFRAGMENTOP3ATIPROC)gleIntGetProcAddress("glAlphaFragmentOp3ATI");
	if(!TestPointer(glAlphaFragmentOp3ATI)) bIsLoaded = 0;
	glSetFragmentShaderConstantATI = (PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)gleIntGetProcAddress("glSetFragmentShaderConstantATI");
	if(!TestPointer(glSetFragmentShaderConstantATI)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLUNMAPOBJECTBUFFERATIPROC)(GLuint buffer);

PFNGLMAPOBJECTBUFFERATIPROC glMapObjectBufferATI;
PFNGLUNMAPOBJECTBUFFERATIPROC glUnmapObjectBufferATI;

static int gleIntLoad_ATI_map_object_buffer()
{
	int bIsLoaded = 1;
	glMapObjectBufferATI = (PFNGLMAPOBJECTBUFFERATIPROC)gleIntGetProcAddress("glMapObjectBufferATI");
	if(!TestPointer(glMapObjectBufferATI)) bIsLoaded = 0;
	glUnmapObjectBufferATI = (PFNGLUNMAPOBJECTBUFFERATIPROC)gleIntGetProcAddress("glUnmapObjectBufferATI");
	if(!TestPointer(glUnmapObjectBufferATI)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLPNTRIANGLESIATIPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPNTRIANGLESFATIPROC)(GLenum pname, GLfloat param);

PFNGLPNTRIANGLESIATIPROC glPNTrianglesiATI;
PFNGLPNTRIANGLESFATIPROC glPNTrianglesfATI;

static int gleIntLoad_ATI_pn_triangles()
{
	int bIsLoaded = 1;
	glPNTrianglesiATI = (PFNGLPNTRIANGLESIATIPROC)gleIntGetProcAddress("glPNTrianglesiATI");
	if(!TestPointer(glPNTrianglesiATI)) bIsLoaded = 0;
	glPNTrianglesfATI = (PFNGLPNTRIANGLESFATIPROC)gleIntGetProcAddress("glPNTrianglesfATI");
	if(!TestPointer(glPNTrianglesfATI)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLSTENCILOPSEPARATEATIPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCSEPARATEATIPROC)(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask);

PFNGLSTENCILOPSEPARATEATIPROC glStencilOpSeparateATI;
PFNGLSTENCILFUNCSEPARATEATIPROC glStencilFuncSeparateATI;

static int gleIntLoad_ATI_separate_stencil()
{
	int bIsLoaded = 1;
	glStencilOpSeparateATI = (PFNGLSTENCILOPSEPARATEATIPROC)gleIntGetProcAddress("glStencilOpSeparateATI");
	if(!TestPointer(glStencilOpSeparateATI)) bIsLoaded = 0;
	glStencilFuncSeparateATI = (PFNGLSTENCILFUNCSEPARATEATIPROC)gleIntGetProcAddress("glStencilFuncSeparateATI");
	if(!TestPointer(glStencilFuncSeparateATI)) bIsLoaded = 0;
	return bIsLoaded;
}




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

PFNGLNEWOBJECTBUFFERATIPROC glNewObjectBufferATI;
PFNGLISOBJECTBUFFERATIPROC glIsObjectBufferATI;
PFNGLUPDATEOBJECTBUFFERATIPROC glUpdateObjectBufferATI;
PFNGLGETOBJECTBUFFERFVATIPROC glGetObjectBufferfvATI;
PFNGLGETOBJECTBUFFERIVATIPROC glGetObjectBufferivATI;
PFNGLFREEOBJECTBUFFERATIPROC glFreeObjectBufferATI;
PFNGLARRAYOBJECTATIPROC glArrayObjectATI;
PFNGLGETARRAYOBJECTFVATIPROC glGetArrayObjectfvATI;
PFNGLGETARRAYOBJECTIVATIPROC glGetArrayObjectivATI;
PFNGLVARIANTARRAYOBJECTATIPROC glVariantArrayObjectATI;
PFNGLGETVARIANTARRAYOBJECTFVATIPROC glGetVariantArrayObjectfvATI;
PFNGLGETVARIANTARRAYOBJECTIVATIPROC glGetVariantArrayObjectivATI;

static int gleIntLoad_ATI_vertex_array_object()
{
	int bIsLoaded = 1;
	glNewObjectBufferATI = (PFNGLNEWOBJECTBUFFERATIPROC)gleIntGetProcAddress("glNewObjectBufferATI");
	if(!TestPointer(glNewObjectBufferATI)) bIsLoaded = 0;
	glIsObjectBufferATI = (PFNGLISOBJECTBUFFERATIPROC)gleIntGetProcAddress("glIsObjectBufferATI");
	if(!TestPointer(glIsObjectBufferATI)) bIsLoaded = 0;
	glUpdateObjectBufferATI = (PFNGLUPDATEOBJECTBUFFERATIPROC)gleIntGetProcAddress("glUpdateObjectBufferATI");
	if(!TestPointer(glUpdateObjectBufferATI)) bIsLoaded = 0;
	glGetObjectBufferfvATI = (PFNGLGETOBJECTBUFFERFVATIPROC)gleIntGetProcAddress("glGetObjectBufferfvATI");
	if(!TestPointer(glGetObjectBufferfvATI)) bIsLoaded = 0;
	glGetObjectBufferivATI = (PFNGLGETOBJECTBUFFERIVATIPROC)gleIntGetProcAddress("glGetObjectBufferivATI");
	if(!TestPointer(glGetObjectBufferivATI)) bIsLoaded = 0;
	glFreeObjectBufferATI = (PFNGLFREEOBJECTBUFFERATIPROC)gleIntGetProcAddress("glFreeObjectBufferATI");
	if(!TestPointer(glFreeObjectBufferATI)) bIsLoaded = 0;
	glArrayObjectATI = (PFNGLARRAYOBJECTATIPROC)gleIntGetProcAddress("glArrayObjectATI");
	if(!TestPointer(glArrayObjectATI)) bIsLoaded = 0;
	glGetArrayObjectfvATI = (PFNGLGETARRAYOBJECTFVATIPROC)gleIntGetProcAddress("glGetArrayObjectfvATI");
	if(!TestPointer(glGetArrayObjectfvATI)) bIsLoaded = 0;
	glGetArrayObjectivATI = (PFNGLGETARRAYOBJECTIVATIPROC)gleIntGetProcAddress("glGetArrayObjectivATI");
	if(!TestPointer(glGetArrayObjectivATI)) bIsLoaded = 0;
	glVariantArrayObjectATI = (PFNGLVARIANTARRAYOBJECTATIPROC)gleIntGetProcAddress("glVariantArrayObjectATI");
	if(!TestPointer(glVariantArrayObjectATI)) bIsLoaded = 0;
	glGetVariantArrayObjectfvATI = (PFNGLGETVARIANTARRAYOBJECTFVATIPROC)gleIntGetProcAddress("glGetVariantArrayObjectfvATI");
	if(!TestPointer(glGetVariantArrayObjectfvATI)) bIsLoaded = 0;
	glGetVariantArrayObjectivATI = (PFNGLGETVARIANTARRAYOBJECTIVATIPROC)gleIntGetProcAddress("glGetVariantArrayObjectivATI");
	if(!TestPointer(glGetVariantArrayObjectivATI)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)(GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)(GLuint index, GLenum pname, GLint *params);

PFNGLVERTEXATTRIBARRAYOBJECTATIPROC glVertexAttribArrayObjectATI;
PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC glGetVertexAttribArrayObjectfvATI;
PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC glGetVertexAttribArrayObjectivATI;

static int gleIntLoad_ATI_vertex_attrib_array_object()
{
	int bIsLoaded = 1;
	glVertexAttribArrayObjectATI = (PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)gleIntGetProcAddress("glVertexAttribArrayObjectATI");
	if(!TestPointer(glVertexAttribArrayObjectATI)) bIsLoaded = 0;
	glGetVertexAttribArrayObjectfvATI = (PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)gleIntGetProcAddress("glGetVertexAttribArrayObjectfvATI");
	if(!TestPointer(glGetVertexAttribArrayObjectfvATI)) bIsLoaded = 0;
	glGetVertexAttribArrayObjectivATI = (PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)gleIntGetProcAddress("glGetVertexAttribArrayObjectivATI");
	if(!TestPointer(glGetVertexAttribArrayObjectivATI)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVERTEXSTREAM1SATIPROC glVertexStream1sATI;
PFNGLVERTEXSTREAM1SVATIPROC glVertexStream1svATI;
PFNGLVERTEXSTREAM1IATIPROC glVertexStream1iATI;
PFNGLVERTEXSTREAM1IVATIPROC glVertexStream1ivATI;
PFNGLVERTEXSTREAM1FATIPROC glVertexStream1fATI;
PFNGLVERTEXSTREAM1FVATIPROC glVertexStream1fvATI;
PFNGLVERTEXSTREAM1DATIPROC glVertexStream1dATI;
PFNGLVERTEXSTREAM1DVATIPROC glVertexStream1dvATI;
PFNGLVERTEXSTREAM2SATIPROC glVertexStream2sATI;
PFNGLVERTEXSTREAM2SVATIPROC glVertexStream2svATI;
PFNGLVERTEXSTREAM2IATIPROC glVertexStream2iATI;
PFNGLVERTEXSTREAM2IVATIPROC glVertexStream2ivATI;
PFNGLVERTEXSTREAM2FATIPROC glVertexStream2fATI;
PFNGLVERTEXSTREAM2FVATIPROC glVertexStream2fvATI;
PFNGLVERTEXSTREAM2DATIPROC glVertexStream2dATI;
PFNGLVERTEXSTREAM2DVATIPROC glVertexStream2dvATI;
PFNGLVERTEXSTREAM3SATIPROC glVertexStream3sATI;
PFNGLVERTEXSTREAM3SVATIPROC glVertexStream3svATI;
PFNGLVERTEXSTREAM3IATIPROC glVertexStream3iATI;
PFNGLVERTEXSTREAM3IVATIPROC glVertexStream3ivATI;
PFNGLVERTEXSTREAM3FATIPROC glVertexStream3fATI;
PFNGLVERTEXSTREAM3FVATIPROC glVertexStream3fvATI;
PFNGLVERTEXSTREAM3DATIPROC glVertexStream3dATI;
PFNGLVERTEXSTREAM3DVATIPROC glVertexStream3dvATI;
PFNGLVERTEXSTREAM4SATIPROC glVertexStream4sATI;
PFNGLVERTEXSTREAM4SVATIPROC glVertexStream4svATI;
PFNGLVERTEXSTREAM4IATIPROC glVertexStream4iATI;
PFNGLVERTEXSTREAM4IVATIPROC glVertexStream4ivATI;
PFNGLVERTEXSTREAM4FATIPROC glVertexStream4fATI;
PFNGLVERTEXSTREAM4FVATIPROC glVertexStream4fvATI;
PFNGLVERTEXSTREAM4DATIPROC glVertexStream4dATI;
PFNGLVERTEXSTREAM4DVATIPROC glVertexStream4dvATI;
PFNGLNORMALSTREAM3BATIPROC glNormalStream3bATI;
PFNGLNORMALSTREAM3BVATIPROC glNormalStream3bvATI;
PFNGLNORMALSTREAM3SATIPROC glNormalStream3sATI;
PFNGLNORMALSTREAM3SVATIPROC glNormalStream3svATI;
PFNGLNORMALSTREAM3IATIPROC glNormalStream3iATI;
PFNGLNORMALSTREAM3IVATIPROC glNormalStream3ivATI;
PFNGLNORMALSTREAM3FATIPROC glNormalStream3fATI;
PFNGLNORMALSTREAM3FVATIPROC glNormalStream3fvATI;
PFNGLNORMALSTREAM3DATIPROC glNormalStream3dATI;
PFNGLNORMALSTREAM3DVATIPROC glNormalStream3dvATI;
PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC glClientActiveVertexStreamATI;
PFNGLVERTEXBLENDENVIATIPROC glVertexBlendEnviATI;
PFNGLVERTEXBLENDENVFATIPROC glVertexBlendEnvfATI;

static int gleIntLoad_ATI_vertex_streams()
{
	int bIsLoaded = 1;
	glVertexStream1sATI = (PFNGLVERTEXSTREAM1SATIPROC)gleIntGetProcAddress("glVertexStream1sATI");
	if(!TestPointer(glVertexStream1sATI)) bIsLoaded = 0;
	glVertexStream1svATI = (PFNGLVERTEXSTREAM1SVATIPROC)gleIntGetProcAddress("glVertexStream1svATI");
	if(!TestPointer(glVertexStream1svATI)) bIsLoaded = 0;
	glVertexStream1iATI = (PFNGLVERTEXSTREAM1IATIPROC)gleIntGetProcAddress("glVertexStream1iATI");
	if(!TestPointer(glVertexStream1iATI)) bIsLoaded = 0;
	glVertexStream1ivATI = (PFNGLVERTEXSTREAM1IVATIPROC)gleIntGetProcAddress("glVertexStream1ivATI");
	if(!TestPointer(glVertexStream1ivATI)) bIsLoaded = 0;
	glVertexStream1fATI = (PFNGLVERTEXSTREAM1FATIPROC)gleIntGetProcAddress("glVertexStream1fATI");
	if(!TestPointer(glVertexStream1fATI)) bIsLoaded = 0;
	glVertexStream1fvATI = (PFNGLVERTEXSTREAM1FVATIPROC)gleIntGetProcAddress("glVertexStream1fvATI");
	if(!TestPointer(glVertexStream1fvATI)) bIsLoaded = 0;
	glVertexStream1dATI = (PFNGLVERTEXSTREAM1DATIPROC)gleIntGetProcAddress("glVertexStream1dATI");
	if(!TestPointer(glVertexStream1dATI)) bIsLoaded = 0;
	glVertexStream1dvATI = (PFNGLVERTEXSTREAM1DVATIPROC)gleIntGetProcAddress("glVertexStream1dvATI");
	if(!TestPointer(glVertexStream1dvATI)) bIsLoaded = 0;
	glVertexStream2sATI = (PFNGLVERTEXSTREAM2SATIPROC)gleIntGetProcAddress("glVertexStream2sATI");
	if(!TestPointer(glVertexStream2sATI)) bIsLoaded = 0;
	glVertexStream2svATI = (PFNGLVERTEXSTREAM2SVATIPROC)gleIntGetProcAddress("glVertexStream2svATI");
	if(!TestPointer(glVertexStream2svATI)) bIsLoaded = 0;
	glVertexStream2iATI = (PFNGLVERTEXSTREAM2IATIPROC)gleIntGetProcAddress("glVertexStream2iATI");
	if(!TestPointer(glVertexStream2iATI)) bIsLoaded = 0;
	glVertexStream2ivATI = (PFNGLVERTEXSTREAM2IVATIPROC)gleIntGetProcAddress("glVertexStream2ivATI");
	if(!TestPointer(glVertexStream2ivATI)) bIsLoaded = 0;
	glVertexStream2fATI = (PFNGLVERTEXSTREAM2FATIPROC)gleIntGetProcAddress("glVertexStream2fATI");
	if(!TestPointer(glVertexStream2fATI)) bIsLoaded = 0;
	glVertexStream2fvATI = (PFNGLVERTEXSTREAM2FVATIPROC)gleIntGetProcAddress("glVertexStream2fvATI");
	if(!TestPointer(glVertexStream2fvATI)) bIsLoaded = 0;
	glVertexStream2dATI = (PFNGLVERTEXSTREAM2DATIPROC)gleIntGetProcAddress("glVertexStream2dATI");
	if(!TestPointer(glVertexStream2dATI)) bIsLoaded = 0;
	glVertexStream2dvATI = (PFNGLVERTEXSTREAM2DVATIPROC)gleIntGetProcAddress("glVertexStream2dvATI");
	if(!TestPointer(glVertexStream2dvATI)) bIsLoaded = 0;
	glVertexStream3sATI = (PFNGLVERTEXSTREAM3SATIPROC)gleIntGetProcAddress("glVertexStream3sATI");
	if(!TestPointer(glVertexStream3sATI)) bIsLoaded = 0;
	glVertexStream3svATI = (PFNGLVERTEXSTREAM3SVATIPROC)gleIntGetProcAddress("glVertexStream3svATI");
	if(!TestPointer(glVertexStream3svATI)) bIsLoaded = 0;
	glVertexStream3iATI = (PFNGLVERTEXSTREAM3IATIPROC)gleIntGetProcAddress("glVertexStream3iATI");
	if(!TestPointer(glVertexStream3iATI)) bIsLoaded = 0;
	glVertexStream3ivATI = (PFNGLVERTEXSTREAM3IVATIPROC)gleIntGetProcAddress("glVertexStream3ivATI");
	if(!TestPointer(glVertexStream3ivATI)) bIsLoaded = 0;
	glVertexStream3fATI = (PFNGLVERTEXSTREAM3FATIPROC)gleIntGetProcAddress("glVertexStream3fATI");
	if(!TestPointer(glVertexStream3fATI)) bIsLoaded = 0;
	glVertexStream3fvATI = (PFNGLVERTEXSTREAM3FVATIPROC)gleIntGetProcAddress("glVertexStream3fvATI");
	if(!TestPointer(glVertexStream3fvATI)) bIsLoaded = 0;
	glVertexStream3dATI = (PFNGLVERTEXSTREAM3DATIPROC)gleIntGetProcAddress("glVertexStream3dATI");
	if(!TestPointer(glVertexStream3dATI)) bIsLoaded = 0;
	glVertexStream3dvATI = (PFNGLVERTEXSTREAM3DVATIPROC)gleIntGetProcAddress("glVertexStream3dvATI");
	if(!TestPointer(glVertexStream3dvATI)) bIsLoaded = 0;
	glVertexStream4sATI = (PFNGLVERTEXSTREAM4SATIPROC)gleIntGetProcAddress("glVertexStream4sATI");
	if(!TestPointer(glVertexStream4sATI)) bIsLoaded = 0;
	glVertexStream4svATI = (PFNGLVERTEXSTREAM4SVATIPROC)gleIntGetProcAddress("glVertexStream4svATI");
	if(!TestPointer(glVertexStream4svATI)) bIsLoaded = 0;
	glVertexStream4iATI = (PFNGLVERTEXSTREAM4IATIPROC)gleIntGetProcAddress("glVertexStream4iATI");
	if(!TestPointer(glVertexStream4iATI)) bIsLoaded = 0;
	glVertexStream4ivATI = (PFNGLVERTEXSTREAM4IVATIPROC)gleIntGetProcAddress("glVertexStream4ivATI");
	if(!TestPointer(glVertexStream4ivATI)) bIsLoaded = 0;
	glVertexStream4fATI = (PFNGLVERTEXSTREAM4FATIPROC)gleIntGetProcAddress("glVertexStream4fATI");
	if(!TestPointer(glVertexStream4fATI)) bIsLoaded = 0;
	glVertexStream4fvATI = (PFNGLVERTEXSTREAM4FVATIPROC)gleIntGetProcAddress("glVertexStream4fvATI");
	if(!TestPointer(glVertexStream4fvATI)) bIsLoaded = 0;
	glVertexStream4dATI = (PFNGLVERTEXSTREAM4DATIPROC)gleIntGetProcAddress("glVertexStream4dATI");
	if(!TestPointer(glVertexStream4dATI)) bIsLoaded = 0;
	glVertexStream4dvATI = (PFNGLVERTEXSTREAM4DVATIPROC)gleIntGetProcAddress("glVertexStream4dvATI");
	if(!TestPointer(glVertexStream4dvATI)) bIsLoaded = 0;
	glNormalStream3bATI = (PFNGLNORMALSTREAM3BATIPROC)gleIntGetProcAddress("glNormalStream3bATI");
	if(!TestPointer(glNormalStream3bATI)) bIsLoaded = 0;
	glNormalStream3bvATI = (PFNGLNORMALSTREAM3BVATIPROC)gleIntGetProcAddress("glNormalStream3bvATI");
	if(!TestPointer(glNormalStream3bvATI)) bIsLoaded = 0;
	glNormalStream3sATI = (PFNGLNORMALSTREAM3SATIPROC)gleIntGetProcAddress("glNormalStream3sATI");
	if(!TestPointer(glNormalStream3sATI)) bIsLoaded = 0;
	glNormalStream3svATI = (PFNGLNORMALSTREAM3SVATIPROC)gleIntGetProcAddress("glNormalStream3svATI");
	if(!TestPointer(glNormalStream3svATI)) bIsLoaded = 0;
	glNormalStream3iATI = (PFNGLNORMALSTREAM3IATIPROC)gleIntGetProcAddress("glNormalStream3iATI");
	if(!TestPointer(glNormalStream3iATI)) bIsLoaded = 0;
	glNormalStream3ivATI = (PFNGLNORMALSTREAM3IVATIPROC)gleIntGetProcAddress("glNormalStream3ivATI");
	if(!TestPointer(glNormalStream3ivATI)) bIsLoaded = 0;
	glNormalStream3fATI = (PFNGLNORMALSTREAM3FATIPROC)gleIntGetProcAddress("glNormalStream3fATI");
	if(!TestPointer(glNormalStream3fATI)) bIsLoaded = 0;
	glNormalStream3fvATI = (PFNGLNORMALSTREAM3FVATIPROC)gleIntGetProcAddress("glNormalStream3fvATI");
	if(!TestPointer(glNormalStream3fvATI)) bIsLoaded = 0;
	glNormalStream3dATI = (PFNGLNORMALSTREAM3DATIPROC)gleIntGetProcAddress("glNormalStream3dATI");
	if(!TestPointer(glNormalStream3dATI)) bIsLoaded = 0;
	glNormalStream3dvATI = (PFNGLNORMALSTREAM3DVATIPROC)gleIntGetProcAddress("glNormalStream3dvATI");
	if(!TestPointer(glNormalStream3dvATI)) bIsLoaded = 0;
	glClientActiveVertexStreamATI = (PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC)gleIntGetProcAddress("glClientActiveVertexStreamATI");
	if(!TestPointer(glClientActiveVertexStreamATI)) bIsLoaded = 0;
	glVertexBlendEnviATI = (PFNGLVERTEXBLENDENVIATIPROC)gleIntGetProcAddress("glVertexBlendEnviATI");
	if(!TestPointer(glVertexBlendEnviATI)) bIsLoaded = 0;
	glVertexBlendEnvfATI = (PFNGLVERTEXBLENDENVFATIPROC)gleIntGetProcAddress("glVertexBlendEnvfATI");
	if(!TestPointer(glVertexBlendEnvfATI)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLUNIFORMBUFFEREXTPROC)(GLuint program, GLint location, GLuint buffer);
typedef GLint (GLE_FUNCPTR * PFNGLGETUNIFORMBUFFERSIZEEXTPROC)(GLuint program, GLint location);
typedef GLintptr (GLE_FUNCPTR * PFNGLGETUNIFORMOFFSETEXTPROC)(GLuint program, GLint location);

PFNGLUNIFORMBUFFEREXTPROC glUniformBufferEXT;
PFNGLGETUNIFORMBUFFERSIZEEXTPROC glGetUniformBufferSizeEXT;
PFNGLGETUNIFORMOFFSETEXTPROC glGetUniformOffsetEXT;

static int gleIntLoad_EXT_bindable_uniform()
{
	int bIsLoaded = 1;
	glUniformBufferEXT = (PFNGLUNIFORMBUFFEREXTPROC)gleIntGetProcAddress("glUniformBufferEXT");
	if(!TestPointer(glUniformBufferEXT)) bIsLoaded = 0;
	glGetUniformBufferSizeEXT = (PFNGLGETUNIFORMBUFFERSIZEEXTPROC)gleIntGetProcAddress("glGetUniformBufferSizeEXT");
	if(!TestPointer(glGetUniformBufferSizeEXT)) bIsLoaded = 0;
	glGetUniformOffsetEXT = (PFNGLGETUNIFORMOFFSETEXTPROC)gleIntGetProcAddress("glGetUniformOffsetEXT");
	if(!TestPointer(glGetUniformOffsetEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLENDCOLOREXTPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

PFNGLBLENDCOLOREXTPROC glBlendColorEXT;

static int gleIntLoad_EXT_blend_color()
{
	int bIsLoaded = 1;
	glBlendColorEXT = (PFNGLBLENDCOLOREXTPROC)gleIntGetProcAddress("glBlendColorEXT");
	if(!TestPointer(glBlendColorEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEEXTPROC)(GLenum modeRGB, GLenum modeAlpha);

PFNGLBLENDEQUATIONSEPARATEEXTPROC glBlendEquationSeparateEXT;

static int gleIntLoad_EXT_blend_equation_separate()
{
	int bIsLoaded = 1;
	glBlendEquationSeparateEXT = (PFNGLBLENDEQUATIONSEPARATEEXTPROC)gleIntGetProcAddress("glBlendEquationSeparateEXT");
	if(!TestPointer(glBlendEquationSeparateEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEEXTPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);

PFNGLBLENDFUNCSEPARATEEXTPROC glBlendFuncSeparateEXT;

static int gleIntLoad_EXT_blend_func_separate()
{
	int bIsLoaded = 1;
	glBlendFuncSeparateEXT = (PFNGLBLENDFUNCSEPARATEEXTPROC)gleIntGetProcAddress("glBlendFuncSeparateEXT");
	if(!TestPointer(glBlendFuncSeparateEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONEXTPROC)(GLenum mode);

PFNGLBLENDEQUATIONEXTPROC glBlendEquationEXT;

static int gleIntLoad_EXT_blend_minmax()
{
	int bIsLoaded = 1;
	glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC)gleIntGetProcAddress("glBlendEquationEXT");
	if(!TestPointer(glBlendEquationEXT)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLCOLORSUBTABLEEXTPROC)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORSUBTABLEEXTPROC)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);

PFNGLCOLORSUBTABLEEXTPROC glColorSubTableEXT;
PFNGLCOPYCOLORSUBTABLEEXTPROC glCopyColorSubTableEXT;

static int gleIntLoad_EXT_color_subtable()
{
	int bIsLoaded = 1;
	glColorSubTableEXT = (PFNGLCOLORSUBTABLEEXTPROC)gleIntGetProcAddress("glColorSubTableEXT");
	if(!TestPointer(glColorSubTableEXT)) bIsLoaded = 0;
	glCopyColorSubTableEXT = (PFNGLCOPYCOLORSUBTABLEEXTPROC)gleIntGetProcAddress("glCopyColorSubTableEXT");
	if(!TestPointer(glCopyColorSubTableEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLLOCKARRAYSEXTPROC)(GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLUNLOCKARRAYSEXTPROC)();

PFNGLLOCKARRAYSEXTPROC glLockArraysEXT;
PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT;

static int gleIntLoad_EXT_compiled_vertex_array()
{
	int bIsLoaded = 1;
	glLockArraysEXT = (PFNGLLOCKARRAYSEXTPROC)gleIntGetProcAddress("glLockArraysEXT");
	if(!TestPointer(glLockArraysEXT)) bIsLoaded = 0;
	glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC)gleIntGetProcAddress("glUnlockArraysEXT");
	if(!TestPointer(glUnlockArraysEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLCONVOLUTIONFILTER1DEXTPROC glConvolutionFilter1DEXT;
PFNGLCONVOLUTIONFILTER2DEXTPROC glConvolutionFilter2DEXT;
PFNGLCONVOLUTIONPARAMETERFEXTPROC glConvolutionParameterfEXT;
PFNGLCONVOLUTIONPARAMETERFVEXTPROC glConvolutionParameterfvEXT;
PFNGLCONVOLUTIONPARAMETERIEXTPROC glConvolutionParameteriEXT;
PFNGLCONVOLUTIONPARAMETERIVEXTPROC glConvolutionParameterivEXT;
PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC glCopyConvolutionFilter1DEXT;
PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC glCopyConvolutionFilter2DEXT;
PFNGLGETCONVOLUTIONFILTEREXTPROC glGetConvolutionFilterEXT;
PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC glGetConvolutionParameterfvEXT;
PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC glGetConvolutionParameterivEXT;
PFNGLGETSEPARABLEFILTEREXTPROC glGetSeparableFilterEXT;
PFNGLSEPARABLEFILTER2DEXTPROC glSeparableFilter2DEXT;

static int gleIntLoad_EXT_convolution()
{
	int bIsLoaded = 1;
	glConvolutionFilter1DEXT = (PFNGLCONVOLUTIONFILTER1DEXTPROC)gleIntGetProcAddress("glConvolutionFilter1DEXT");
	if(!TestPointer(glConvolutionFilter1DEXT)) bIsLoaded = 0;
	glConvolutionFilter2DEXT = (PFNGLCONVOLUTIONFILTER2DEXTPROC)gleIntGetProcAddress("glConvolutionFilter2DEXT");
	if(!TestPointer(glConvolutionFilter2DEXT)) bIsLoaded = 0;
	glConvolutionParameterfEXT = (PFNGLCONVOLUTIONPARAMETERFEXTPROC)gleIntGetProcAddress("glConvolutionParameterfEXT");
	if(!TestPointer(glConvolutionParameterfEXT)) bIsLoaded = 0;
	glConvolutionParameterfvEXT = (PFNGLCONVOLUTIONPARAMETERFVEXTPROC)gleIntGetProcAddress("glConvolutionParameterfvEXT");
	if(!TestPointer(glConvolutionParameterfvEXT)) bIsLoaded = 0;
	glConvolutionParameteriEXT = (PFNGLCONVOLUTIONPARAMETERIEXTPROC)gleIntGetProcAddress("glConvolutionParameteriEXT");
	if(!TestPointer(glConvolutionParameteriEXT)) bIsLoaded = 0;
	glConvolutionParameterivEXT = (PFNGLCONVOLUTIONPARAMETERIVEXTPROC)gleIntGetProcAddress("glConvolutionParameterivEXT");
	if(!TestPointer(glConvolutionParameterivEXT)) bIsLoaded = 0;
	glCopyConvolutionFilter1DEXT = (PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)gleIntGetProcAddress("glCopyConvolutionFilter1DEXT");
	if(!TestPointer(glCopyConvolutionFilter1DEXT)) bIsLoaded = 0;
	glCopyConvolutionFilter2DEXT = (PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)gleIntGetProcAddress("glCopyConvolutionFilter2DEXT");
	if(!TestPointer(glCopyConvolutionFilter2DEXT)) bIsLoaded = 0;
	glGetConvolutionFilterEXT = (PFNGLGETCONVOLUTIONFILTEREXTPROC)gleIntGetProcAddress("glGetConvolutionFilterEXT");
	if(!TestPointer(glGetConvolutionFilterEXT)) bIsLoaded = 0;
	glGetConvolutionParameterfvEXT = (PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetConvolutionParameterfvEXT");
	if(!TestPointer(glGetConvolutionParameterfvEXT)) bIsLoaded = 0;
	glGetConvolutionParameterivEXT = (PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetConvolutionParameterivEXT");
	if(!TestPointer(glGetConvolutionParameterivEXT)) bIsLoaded = 0;
	glGetSeparableFilterEXT = (PFNGLGETSEPARABLEFILTEREXTPROC)gleIntGetProcAddress("glGetSeparableFilterEXT");
	if(!TestPointer(glGetSeparableFilterEXT)) bIsLoaded = 0;
	glSeparableFilter2DEXT = (PFNGLSEPARABLEFILTER2DEXTPROC)gleIntGetProcAddress("glSeparableFilter2DEXT");
	if(!TestPointer(glSeparableFilter2DEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLTANGENT3BEXTPROC glTangent3bEXT;
PFNGLTANGENT3BVEXTPROC glTangent3bvEXT;
PFNGLTANGENT3DEXTPROC glTangent3dEXT;
PFNGLTANGENT3DVEXTPROC glTangent3dvEXT;
PFNGLTANGENT3FEXTPROC glTangent3fEXT;
PFNGLTANGENT3FVEXTPROC glTangent3fvEXT;
PFNGLTANGENT3IEXTPROC glTangent3iEXT;
PFNGLTANGENT3IVEXTPROC glTangent3ivEXT;
PFNGLTANGENT3SEXTPROC glTangent3sEXT;
PFNGLTANGENT3SVEXTPROC glTangent3svEXT;
PFNGLBINORMAL3BEXTPROC glBinormal3bEXT;
PFNGLBINORMAL3BVEXTPROC glBinormal3bvEXT;
PFNGLBINORMAL3DEXTPROC glBinormal3dEXT;
PFNGLBINORMAL3DVEXTPROC glBinormal3dvEXT;
PFNGLBINORMAL3FEXTPROC glBinormal3fEXT;
PFNGLBINORMAL3FVEXTPROC glBinormal3fvEXT;
PFNGLBINORMAL3IEXTPROC glBinormal3iEXT;
PFNGLBINORMAL3IVEXTPROC glBinormal3ivEXT;
PFNGLBINORMAL3SEXTPROC glBinormal3sEXT;
PFNGLBINORMAL3SVEXTPROC glBinormal3svEXT;
PFNGLTANGENTPOINTEREXTPROC glTangentPointerEXT;
PFNGLBINORMALPOINTEREXTPROC glBinormalPointerEXT;

static int gleIntLoad_EXT_coordinate_frame()
{
	int bIsLoaded = 1;
	glTangent3bEXT = (PFNGLTANGENT3BEXTPROC)gleIntGetProcAddress("glTangent3bEXT");
	if(!TestPointer(glTangent3bEXT)) bIsLoaded = 0;
	glTangent3bvEXT = (PFNGLTANGENT3BVEXTPROC)gleIntGetProcAddress("glTangent3bvEXT");
	if(!TestPointer(glTangent3bvEXT)) bIsLoaded = 0;
	glTangent3dEXT = (PFNGLTANGENT3DEXTPROC)gleIntGetProcAddress("glTangent3dEXT");
	if(!TestPointer(glTangent3dEXT)) bIsLoaded = 0;
	glTangent3dvEXT = (PFNGLTANGENT3DVEXTPROC)gleIntGetProcAddress("glTangent3dvEXT");
	if(!TestPointer(glTangent3dvEXT)) bIsLoaded = 0;
	glTangent3fEXT = (PFNGLTANGENT3FEXTPROC)gleIntGetProcAddress("glTangent3fEXT");
	if(!TestPointer(glTangent3fEXT)) bIsLoaded = 0;
	glTangent3fvEXT = (PFNGLTANGENT3FVEXTPROC)gleIntGetProcAddress("glTangent3fvEXT");
	if(!TestPointer(glTangent3fvEXT)) bIsLoaded = 0;
	glTangent3iEXT = (PFNGLTANGENT3IEXTPROC)gleIntGetProcAddress("glTangent3iEXT");
	if(!TestPointer(glTangent3iEXT)) bIsLoaded = 0;
	glTangent3ivEXT = (PFNGLTANGENT3IVEXTPROC)gleIntGetProcAddress("glTangent3ivEXT");
	if(!TestPointer(glTangent3ivEXT)) bIsLoaded = 0;
	glTangent3sEXT = (PFNGLTANGENT3SEXTPROC)gleIntGetProcAddress("glTangent3sEXT");
	if(!TestPointer(glTangent3sEXT)) bIsLoaded = 0;
	glTangent3svEXT = (PFNGLTANGENT3SVEXTPROC)gleIntGetProcAddress("glTangent3svEXT");
	if(!TestPointer(glTangent3svEXT)) bIsLoaded = 0;
	glBinormal3bEXT = (PFNGLBINORMAL3BEXTPROC)gleIntGetProcAddress("glBinormal3bEXT");
	if(!TestPointer(glBinormal3bEXT)) bIsLoaded = 0;
	glBinormal3bvEXT = (PFNGLBINORMAL3BVEXTPROC)gleIntGetProcAddress("glBinormal3bvEXT");
	if(!TestPointer(glBinormal3bvEXT)) bIsLoaded = 0;
	glBinormal3dEXT = (PFNGLBINORMAL3DEXTPROC)gleIntGetProcAddress("glBinormal3dEXT");
	if(!TestPointer(glBinormal3dEXT)) bIsLoaded = 0;
	glBinormal3dvEXT = (PFNGLBINORMAL3DVEXTPROC)gleIntGetProcAddress("glBinormal3dvEXT");
	if(!TestPointer(glBinormal3dvEXT)) bIsLoaded = 0;
	glBinormal3fEXT = (PFNGLBINORMAL3FEXTPROC)gleIntGetProcAddress("glBinormal3fEXT");
	if(!TestPointer(glBinormal3fEXT)) bIsLoaded = 0;
	glBinormal3fvEXT = (PFNGLBINORMAL3FVEXTPROC)gleIntGetProcAddress("glBinormal3fvEXT");
	if(!TestPointer(glBinormal3fvEXT)) bIsLoaded = 0;
	glBinormal3iEXT = (PFNGLBINORMAL3IEXTPROC)gleIntGetProcAddress("glBinormal3iEXT");
	if(!TestPointer(glBinormal3iEXT)) bIsLoaded = 0;
	glBinormal3ivEXT = (PFNGLBINORMAL3IVEXTPROC)gleIntGetProcAddress("glBinormal3ivEXT");
	if(!TestPointer(glBinormal3ivEXT)) bIsLoaded = 0;
	glBinormal3sEXT = (PFNGLBINORMAL3SEXTPROC)gleIntGetProcAddress("glBinormal3sEXT");
	if(!TestPointer(glBinormal3sEXT)) bIsLoaded = 0;
	glBinormal3svEXT = (PFNGLBINORMAL3SVEXTPROC)gleIntGetProcAddress("glBinormal3svEXT");
	if(!TestPointer(glBinormal3svEXT)) bIsLoaded = 0;
	glTangentPointerEXT = (PFNGLTANGENTPOINTEREXTPROC)gleIntGetProcAddress("glTangentPointerEXT");
	if(!TestPointer(glTangentPointerEXT)) bIsLoaded = 0;
	glBinormalPointerEXT = (PFNGLBINORMALPOINTEREXTPROC)gleIntGetProcAddress("glBinormalPointerEXT");
	if(!TestPointer(glBinormalPointerEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE1DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE2DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE1DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE2DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE3DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

PFNGLCOPYTEXIMAGE1DEXTPROC glCopyTexImage1DEXT;
PFNGLCOPYTEXIMAGE2DEXTPROC glCopyTexImage2DEXT;
PFNGLCOPYTEXSUBIMAGE1DEXTPROC glCopyTexSubImage1DEXT;
PFNGLCOPYTEXSUBIMAGE2DEXTPROC glCopyTexSubImage2DEXT;
PFNGLCOPYTEXSUBIMAGE3DEXTPROC glCopyTexSubImage3DEXT;

static int gleIntLoad_EXT_copy_texture()
{
	int bIsLoaded = 1;
	glCopyTexImage1DEXT = (PFNGLCOPYTEXIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyTexImage1DEXT");
	if(!TestPointer(glCopyTexImage1DEXT)) bIsLoaded = 0;
	glCopyTexImage2DEXT = (PFNGLCOPYTEXIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyTexImage2DEXT");
	if(!TestPointer(glCopyTexImage2DEXT)) bIsLoaded = 0;
	glCopyTexSubImage1DEXT = (PFNGLCOPYTEXSUBIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyTexSubImage1DEXT");
	if(!TestPointer(glCopyTexSubImage1DEXT)) bIsLoaded = 0;
	glCopyTexSubImage2DEXT = (PFNGLCOPYTEXSUBIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyTexSubImage2DEXT");
	if(!TestPointer(glCopyTexSubImage2DEXT)) bIsLoaded = 0;
	glCopyTexSubImage3DEXT = (PFNGLCOPYTEXSUBIMAGE3DEXTPROC)gleIntGetProcAddress("glCopyTexSubImage3DEXT");
	if(!TestPointer(glCopyTexSubImage3DEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCULLPARAMETERDVEXTPROC)(GLenum pname, GLdouble *params);
typedef void (GLE_FUNCPTR * PFNGLCULLPARAMETERFVEXTPROC)(GLenum pname, GLfloat *params);

PFNGLCULLPARAMETERDVEXTPROC glCullParameterdvEXT;
PFNGLCULLPARAMETERFVEXTPROC glCullParameterfvEXT;

static int gleIntLoad_EXT_cull_vertex()
{
	int bIsLoaded = 1;
	glCullParameterdvEXT = (PFNGLCULLPARAMETERDVEXTPROC)gleIntGetProcAddress("glCullParameterdvEXT");
	if(!TestPointer(glCullParameterdvEXT)) bIsLoaded = 0;
	glCullParameterfvEXT = (PFNGLCULLPARAMETERFVEXTPROC)gleIntGetProcAddress("glCullParameterfvEXT");
	if(!TestPointer(glCullParameterfvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDEPTHBOUNDSEXTPROC)(GLclampd zmin, GLclampd zmax);

PFNGLDEPTHBOUNDSEXTPROC glDepthBoundsEXT;

static int gleIntLoad_EXT_depth_bounds_test()
{
	int bIsLoaded = 1;
	glDepthBoundsEXT = (PFNGLDEPTHBOUNDSEXTPROC)gleIntGetProcAddress("glDepthBoundsEXT");
	if(!TestPointer(glDepthBoundsEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT;
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT;
PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT;
PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT;
PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT;
PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT;
PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT;
PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT;
PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT;
PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT;
PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT;
PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT;
PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT;
PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
PFNGLMATRIXPOPEXTPROC glMatrixPopEXT;
PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT;
PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT;
PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT;
PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT;
PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT;
PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT;
PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT;
PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT;
PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT;
PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT;
PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT;
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT;
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT;
PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT;
PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT;
PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT;
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT;
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT;
PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT;
PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT;
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT;
PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT;
PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT;
PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT;
PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT;
PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT;
PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT;
PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT;
PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT;
PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT;
PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT;
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT;
PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT;
PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT;
PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT;
PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT;
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT;
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT;
PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT;
PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT;
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT;
PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT;
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT;
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT;
PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT;
PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT;
PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT;
PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT;
PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT;
PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT;
PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT;
PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT;
PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT;
PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT;
PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT;
PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT;
PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT;
PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT;
PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT;
PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT;
PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT;
PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT;
PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT;
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT;
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT;
PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glNamedProgramLocalParameter4dvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glNamedProgramLocalParameter4fvEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glGetNamedProgramLocalParameterdvEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glGetNamedProgramLocalParameterfvEXT;
PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT;
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glNamedProgramLocalParameters4fvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glNamedProgramLocalParameterI4iEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glNamedProgramLocalParameterI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glNamedProgramLocalParametersI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glNamedProgramLocalParameterI4uiEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glNamedProgramLocalParameterI4uivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glNamedProgramLocalParametersI4uivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glGetNamedProgramLocalParameterIivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glGetNamedProgramLocalParameterIuivEXT;
PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT;
PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT;
PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT;
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT;
PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT;
PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT;
PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT;
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT;
PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT;
PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT;
PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT;
PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT;
PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT;
PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT;
PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT;
PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT;
PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT;
PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT;
PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT;
PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT;
PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT;
PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT;
PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT;
PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT;
PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT;
PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT;
PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT;
PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT;
PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT;
PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT;
PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT;
PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT;
PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT;
PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT;
PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT;
PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT;
PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT;
PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT;
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT;
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT;
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT;
PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT;
PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glGetNamedRenderbufferParameterivEXT;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetNamedFramebufferAttachmentParameterivEXT;
PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT;
PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT;
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT;
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT;
PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT;
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glNamedRenderbufferStorageMultisampleEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glNamedRenderbufferStorageMultisampleCoverageEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT;
PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT;
PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT;
PFNGLPROGRAMUNIFORM1DEXTPROC glProgramUniform1dEXT;
PFNGLPROGRAMUNIFORM2DEXTPROC glProgramUniform2dEXT;
PFNGLPROGRAMUNIFORM3DEXTPROC glProgramUniform3dEXT;
PFNGLPROGRAMUNIFORM4DEXTPROC glProgramUniform4dEXT;
PFNGLPROGRAMUNIFORM1DVEXTPROC glProgramUniform1dvEXT;
PFNGLPROGRAMUNIFORM2DVEXTPROC glProgramUniform2dvEXT;
PFNGLPROGRAMUNIFORM3DVEXTPROC glProgramUniform3dvEXT;
PFNGLPROGRAMUNIFORM4DVEXTPROC glProgramUniform4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC glProgramUniformMatrix2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC glProgramUniformMatrix3dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC glProgramUniformMatrix4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC glProgramUniformMatrix2x3dvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC glProgramUniformMatrix2x4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC glProgramUniformMatrix3x2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC glProgramUniformMatrix3x4dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC glProgramUniformMatrix4x2dvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC glProgramUniformMatrix4x3dvEXT;

static int gleIntLoad_EXT_direct_state_access()
{
	int bIsLoaded = 1;
	glClientAttribDefaultEXT = (PFNGLCLIENTATTRIBDEFAULTEXTPROC)gleIntGetProcAddress("glClientAttribDefaultEXT");
	if(!TestPointer(glClientAttribDefaultEXT)) bIsLoaded = 0;
	glPushClientAttribDefaultEXT = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)gleIntGetProcAddress("glPushClientAttribDefaultEXT");
	if(!TestPointer(glPushClientAttribDefaultEXT)) bIsLoaded = 0;
	glMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC)gleIntGetProcAddress("glMatrixLoadfEXT");
	if(!TestPointer(glMatrixLoadfEXT)) bIsLoaded = 0;
	glMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC)gleIntGetProcAddress("glMatrixLoaddEXT");
	if(!TestPointer(glMatrixLoaddEXT)) bIsLoaded = 0;
	glMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC)gleIntGetProcAddress("glMatrixMultfEXT");
	if(!TestPointer(glMatrixMultfEXT)) bIsLoaded = 0;
	glMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC)gleIntGetProcAddress("glMatrixMultdEXT");
	if(!TestPointer(glMatrixMultdEXT)) bIsLoaded = 0;
	glMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC)gleIntGetProcAddress("glMatrixLoadIdentityEXT");
	if(!TestPointer(glMatrixLoadIdentityEXT)) bIsLoaded = 0;
	glMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC)gleIntGetProcAddress("glMatrixRotatefEXT");
	if(!TestPointer(glMatrixRotatefEXT)) bIsLoaded = 0;
	glMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC)gleIntGetProcAddress("glMatrixRotatedEXT");
	if(!TestPointer(glMatrixRotatedEXT)) bIsLoaded = 0;
	glMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC)gleIntGetProcAddress("glMatrixScalefEXT");
	if(!TestPointer(glMatrixScalefEXT)) bIsLoaded = 0;
	glMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC)gleIntGetProcAddress("glMatrixScaledEXT");
	if(!TestPointer(glMatrixScaledEXT)) bIsLoaded = 0;
	glMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC)gleIntGetProcAddress("glMatrixTranslatefEXT");
	if(!TestPointer(glMatrixTranslatefEXT)) bIsLoaded = 0;
	glMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC)gleIntGetProcAddress("glMatrixTranslatedEXT");
	if(!TestPointer(glMatrixTranslatedEXT)) bIsLoaded = 0;
	glMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC)gleIntGetProcAddress("glMatrixFrustumEXT");
	if(!TestPointer(glMatrixFrustumEXT)) bIsLoaded = 0;
	glMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC)gleIntGetProcAddress("glMatrixOrthoEXT");
	if(!TestPointer(glMatrixOrthoEXT)) bIsLoaded = 0;
	glMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC)gleIntGetProcAddress("glMatrixPopEXT");
	if(!TestPointer(glMatrixPopEXT)) bIsLoaded = 0;
	glMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC)gleIntGetProcAddress("glMatrixPushEXT");
	if(!TestPointer(glMatrixPushEXT)) bIsLoaded = 0;
	glMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC)gleIntGetProcAddress("glMatrixLoadTransposefEXT");
	if(!TestPointer(glMatrixLoadTransposefEXT)) bIsLoaded = 0;
	glMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC)gleIntGetProcAddress("glMatrixLoadTransposedEXT");
	if(!TestPointer(glMatrixLoadTransposedEXT)) bIsLoaded = 0;
	glMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC)gleIntGetProcAddress("glMatrixMultTransposefEXT");
	if(!TestPointer(glMatrixMultTransposefEXT)) bIsLoaded = 0;
	glMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC)gleIntGetProcAddress("glMatrixMultTransposedEXT");
	if(!TestPointer(glMatrixMultTransposedEXT)) bIsLoaded = 0;
	glTextureParameterfEXT = (PFNGLTEXTUREPARAMETERFEXTPROC)gleIntGetProcAddress("glTextureParameterfEXT");
	if(!TestPointer(glTextureParameterfEXT)) bIsLoaded = 0;
	glTextureParameterfvEXT = (PFNGLTEXTUREPARAMETERFVEXTPROC)gleIntGetProcAddress("glTextureParameterfvEXT");
	if(!TestPointer(glTextureParameterfvEXT)) bIsLoaded = 0;
	glTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC)gleIntGetProcAddress("glTextureParameteriEXT");
	if(!TestPointer(glTextureParameteriEXT)) bIsLoaded = 0;
	glTextureParameterivEXT = (PFNGLTEXTUREPARAMETERIVEXTPROC)gleIntGetProcAddress("glTextureParameterivEXT");
	if(!TestPointer(glTextureParameterivEXT)) bIsLoaded = 0;
	glTextureImage1DEXT = (PFNGLTEXTUREIMAGE1DEXTPROC)gleIntGetProcAddress("glTextureImage1DEXT");
	if(!TestPointer(glTextureImage1DEXT)) bIsLoaded = 0;
	glTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC)gleIntGetProcAddress("glTextureImage2DEXT");
	if(!TestPointer(glTextureImage2DEXT)) bIsLoaded = 0;
	glTextureSubImage1DEXT = (PFNGLTEXTURESUBIMAGE1DEXTPROC)gleIntGetProcAddress("glTextureSubImage1DEXT");
	if(!TestPointer(glTextureSubImage1DEXT)) bIsLoaded = 0;
	glTextureSubImage2DEXT = (PFNGLTEXTURESUBIMAGE2DEXTPROC)gleIntGetProcAddress("glTextureSubImage2DEXT");
	if(!TestPointer(glTextureSubImage2DEXT)) bIsLoaded = 0;
	glCopyTextureImage1DEXT = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyTextureImage1DEXT");
	if(!TestPointer(glCopyTextureImage1DEXT)) bIsLoaded = 0;
	glCopyTextureImage2DEXT = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyTextureImage2DEXT");
	if(!TestPointer(glCopyTextureImage2DEXT)) bIsLoaded = 0;
	glCopyTextureSubImage1DEXT = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyTextureSubImage1DEXT");
	if(!TestPointer(glCopyTextureSubImage1DEXT)) bIsLoaded = 0;
	glCopyTextureSubImage2DEXT = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyTextureSubImage2DEXT");
	if(!TestPointer(glCopyTextureSubImage2DEXT)) bIsLoaded = 0;
	glGetTextureImageEXT = (PFNGLGETTEXTUREIMAGEEXTPROC)gleIntGetProcAddress("glGetTextureImageEXT");
	if(!TestPointer(glGetTextureImageEXT)) bIsLoaded = 0;
	glGetTextureParameterfvEXT = (PFNGLGETTEXTUREPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetTextureParameterfvEXT");
	if(!TestPointer(glGetTextureParameterfvEXT)) bIsLoaded = 0;
	glGetTextureParameterivEXT = (PFNGLGETTEXTUREPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetTextureParameterivEXT");
	if(!TestPointer(glGetTextureParameterivEXT)) bIsLoaded = 0;
	glGetTextureLevelParameterfvEXT = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetTextureLevelParameterfvEXT");
	if(!TestPointer(glGetTextureLevelParameterfvEXT)) bIsLoaded = 0;
	glGetTextureLevelParameterivEXT = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetTextureLevelParameterivEXT");
	if(!TestPointer(glGetTextureLevelParameterivEXT)) bIsLoaded = 0;
	glTextureImage3DEXT = (PFNGLTEXTUREIMAGE3DEXTPROC)gleIntGetProcAddress("glTextureImage3DEXT");
	if(!TestPointer(glTextureImage3DEXT)) bIsLoaded = 0;
	glTextureSubImage3DEXT = (PFNGLTEXTURESUBIMAGE3DEXTPROC)gleIntGetProcAddress("glTextureSubImage3DEXT");
	if(!TestPointer(glTextureSubImage3DEXT)) bIsLoaded = 0;
	glCopyTextureSubImage3DEXT = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)gleIntGetProcAddress("glCopyTextureSubImage3DEXT");
	if(!TestPointer(glCopyTextureSubImage3DEXT)) bIsLoaded = 0;
	glMultiTexParameterfEXT = (PFNGLMULTITEXPARAMETERFEXTPROC)gleIntGetProcAddress("glMultiTexParameterfEXT");
	if(!TestPointer(glMultiTexParameterfEXT)) bIsLoaded = 0;
	glMultiTexParameterfvEXT = (PFNGLMULTITEXPARAMETERFVEXTPROC)gleIntGetProcAddress("glMultiTexParameterfvEXT");
	if(!TestPointer(glMultiTexParameterfvEXT)) bIsLoaded = 0;
	glMultiTexParameteriEXT = (PFNGLMULTITEXPARAMETERIEXTPROC)gleIntGetProcAddress("glMultiTexParameteriEXT");
	if(!TestPointer(glMultiTexParameteriEXT)) bIsLoaded = 0;
	glMultiTexParameterivEXT = (PFNGLMULTITEXPARAMETERIVEXTPROC)gleIntGetProcAddress("glMultiTexParameterivEXT");
	if(!TestPointer(glMultiTexParameterivEXT)) bIsLoaded = 0;
	glMultiTexImage1DEXT = (PFNGLMULTITEXIMAGE1DEXTPROC)gleIntGetProcAddress("glMultiTexImage1DEXT");
	if(!TestPointer(glMultiTexImage1DEXT)) bIsLoaded = 0;
	glMultiTexImage2DEXT = (PFNGLMULTITEXIMAGE2DEXTPROC)gleIntGetProcAddress("glMultiTexImage2DEXT");
	if(!TestPointer(glMultiTexImage2DEXT)) bIsLoaded = 0;
	glMultiTexSubImage1DEXT = (PFNGLMULTITEXSUBIMAGE1DEXTPROC)gleIntGetProcAddress("glMultiTexSubImage1DEXT");
	if(!TestPointer(glMultiTexSubImage1DEXT)) bIsLoaded = 0;
	glMultiTexSubImage2DEXT = (PFNGLMULTITEXSUBIMAGE2DEXTPROC)gleIntGetProcAddress("glMultiTexSubImage2DEXT");
	if(!TestPointer(glMultiTexSubImage2DEXT)) bIsLoaded = 0;
	glCopyMultiTexImage1DEXT = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyMultiTexImage1DEXT");
	if(!TestPointer(glCopyMultiTexImage1DEXT)) bIsLoaded = 0;
	glCopyMultiTexImage2DEXT = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyMultiTexImage2DEXT");
	if(!TestPointer(glCopyMultiTexImage2DEXT)) bIsLoaded = 0;
	glCopyMultiTexSubImage1DEXT = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)gleIntGetProcAddress("glCopyMultiTexSubImage1DEXT");
	if(!TestPointer(glCopyMultiTexSubImage1DEXT)) bIsLoaded = 0;
	glCopyMultiTexSubImage2DEXT = (PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)gleIntGetProcAddress("glCopyMultiTexSubImage2DEXT");
	if(!TestPointer(glCopyMultiTexSubImage2DEXT)) bIsLoaded = 0;
	glGetMultiTexImageEXT = (PFNGLGETMULTITEXIMAGEEXTPROC)gleIntGetProcAddress("glGetMultiTexImageEXT");
	if(!TestPointer(glGetMultiTexImageEXT)) bIsLoaded = 0;
	glGetMultiTexParameterfvEXT = (PFNGLGETMULTITEXPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetMultiTexParameterfvEXT");
	if(!TestPointer(glGetMultiTexParameterfvEXT)) bIsLoaded = 0;
	glGetMultiTexParameterivEXT = (PFNGLGETMULTITEXPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetMultiTexParameterivEXT");
	if(!TestPointer(glGetMultiTexParameterivEXT)) bIsLoaded = 0;
	glGetMultiTexLevelParameterfvEXT = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetMultiTexLevelParameterfvEXT");
	if(!TestPointer(glGetMultiTexLevelParameterfvEXT)) bIsLoaded = 0;
	glGetMultiTexLevelParameterivEXT = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetMultiTexLevelParameterivEXT");
	if(!TestPointer(glGetMultiTexLevelParameterivEXT)) bIsLoaded = 0;
	glMultiTexImage3DEXT = (PFNGLMULTITEXIMAGE3DEXTPROC)gleIntGetProcAddress("glMultiTexImage3DEXT");
	if(!TestPointer(glMultiTexImage3DEXT)) bIsLoaded = 0;
	glMultiTexSubImage3DEXT = (PFNGLMULTITEXSUBIMAGE3DEXTPROC)gleIntGetProcAddress("glMultiTexSubImage3DEXT");
	if(!TestPointer(glMultiTexSubImage3DEXT)) bIsLoaded = 0;
	glCopyMultiTexSubImage3DEXT = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)gleIntGetProcAddress("glCopyMultiTexSubImage3DEXT");
	if(!TestPointer(glCopyMultiTexSubImage3DEXT)) bIsLoaded = 0;
	glBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC)gleIntGetProcAddress("glBindMultiTextureEXT");
	if(!TestPointer(glBindMultiTextureEXT)) bIsLoaded = 0;
	glEnableClientStateIndexedEXT = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)gleIntGetProcAddress("glEnableClientStateIndexedEXT");
	if(!TestPointer(glEnableClientStateIndexedEXT)) bIsLoaded = 0;
	glDisableClientStateIndexedEXT = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)gleIntGetProcAddress("glDisableClientStateIndexedEXT");
	if(!TestPointer(glDisableClientStateIndexedEXT)) bIsLoaded = 0;
	glMultiTexCoordPointerEXT = (PFNGLMULTITEXCOORDPOINTEREXTPROC)gleIntGetProcAddress("glMultiTexCoordPointerEXT");
	if(!TestPointer(glMultiTexCoordPointerEXT)) bIsLoaded = 0;
	glMultiTexEnvfEXT = (PFNGLMULTITEXENVFEXTPROC)gleIntGetProcAddress("glMultiTexEnvfEXT");
	if(!TestPointer(glMultiTexEnvfEXT)) bIsLoaded = 0;
	glMultiTexEnvfvEXT = (PFNGLMULTITEXENVFVEXTPROC)gleIntGetProcAddress("glMultiTexEnvfvEXT");
	if(!TestPointer(glMultiTexEnvfvEXT)) bIsLoaded = 0;
	glMultiTexEnviEXT = (PFNGLMULTITEXENVIEXTPROC)gleIntGetProcAddress("glMultiTexEnviEXT");
	if(!TestPointer(glMultiTexEnviEXT)) bIsLoaded = 0;
	glMultiTexEnvivEXT = (PFNGLMULTITEXENVIVEXTPROC)gleIntGetProcAddress("glMultiTexEnvivEXT");
	if(!TestPointer(glMultiTexEnvivEXT)) bIsLoaded = 0;
	glMultiTexGendEXT = (PFNGLMULTITEXGENDEXTPROC)gleIntGetProcAddress("glMultiTexGendEXT");
	if(!TestPointer(glMultiTexGendEXT)) bIsLoaded = 0;
	glMultiTexGendvEXT = (PFNGLMULTITEXGENDVEXTPROC)gleIntGetProcAddress("glMultiTexGendvEXT");
	if(!TestPointer(glMultiTexGendvEXT)) bIsLoaded = 0;
	glMultiTexGenfEXT = (PFNGLMULTITEXGENFEXTPROC)gleIntGetProcAddress("glMultiTexGenfEXT");
	if(!TestPointer(glMultiTexGenfEXT)) bIsLoaded = 0;
	glMultiTexGenfvEXT = (PFNGLMULTITEXGENFVEXTPROC)gleIntGetProcAddress("glMultiTexGenfvEXT");
	if(!TestPointer(glMultiTexGenfvEXT)) bIsLoaded = 0;
	glMultiTexGeniEXT = (PFNGLMULTITEXGENIEXTPROC)gleIntGetProcAddress("glMultiTexGeniEXT");
	if(!TestPointer(glMultiTexGeniEXT)) bIsLoaded = 0;
	glMultiTexGenivEXT = (PFNGLMULTITEXGENIVEXTPROC)gleIntGetProcAddress("glMultiTexGenivEXT");
	if(!TestPointer(glMultiTexGenivEXT)) bIsLoaded = 0;
	glGetMultiTexEnvfvEXT = (PFNGLGETMULTITEXENVFVEXTPROC)gleIntGetProcAddress("glGetMultiTexEnvfvEXT");
	if(!TestPointer(glGetMultiTexEnvfvEXT)) bIsLoaded = 0;
	glGetMultiTexEnvivEXT = (PFNGLGETMULTITEXENVIVEXTPROC)gleIntGetProcAddress("glGetMultiTexEnvivEXT");
	if(!TestPointer(glGetMultiTexEnvivEXT)) bIsLoaded = 0;
	glGetMultiTexGendvEXT = (PFNGLGETMULTITEXGENDVEXTPROC)gleIntGetProcAddress("glGetMultiTexGendvEXT");
	if(!TestPointer(glGetMultiTexGendvEXT)) bIsLoaded = 0;
	glGetMultiTexGenfvEXT = (PFNGLGETMULTITEXGENFVEXTPROC)gleIntGetProcAddress("glGetMultiTexGenfvEXT");
	if(!TestPointer(glGetMultiTexGenfvEXT)) bIsLoaded = 0;
	glGetMultiTexGenivEXT = (PFNGLGETMULTITEXGENIVEXTPROC)gleIntGetProcAddress("glGetMultiTexGenivEXT");
	if(!TestPointer(glGetMultiTexGenivEXT)) bIsLoaded = 0;
	glGetFloatIndexedvEXT = (PFNGLGETFLOATINDEXEDVEXTPROC)gleIntGetProcAddress("glGetFloatIndexedvEXT");
	if(!TestPointer(glGetFloatIndexedvEXT)) bIsLoaded = 0;
	glGetDoubleIndexedvEXT = (PFNGLGETDOUBLEINDEXEDVEXTPROC)gleIntGetProcAddress("glGetDoubleIndexedvEXT");
	if(!TestPointer(glGetDoubleIndexedvEXT)) bIsLoaded = 0;
	glGetPointerIndexedvEXT = (PFNGLGETPOINTERINDEXEDVEXTPROC)gleIntGetProcAddress("glGetPointerIndexedvEXT");
	if(!TestPointer(glGetPointerIndexedvEXT)) bIsLoaded = 0;
	glCompressedTextureImage3DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)gleIntGetProcAddress("glCompressedTextureImage3DEXT");
	if(!TestPointer(glCompressedTextureImage3DEXT)) bIsLoaded = 0;
	glCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)gleIntGetProcAddress("glCompressedTextureImage2DEXT");
	if(!TestPointer(glCompressedTextureImage2DEXT)) bIsLoaded = 0;
	glCompressedTextureImage1DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)gleIntGetProcAddress("glCompressedTextureImage1DEXT");
	if(!TestPointer(glCompressedTextureImage1DEXT)) bIsLoaded = 0;
	glCompressedTextureSubImage3DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)gleIntGetProcAddress("glCompressedTextureSubImage3DEXT");
	if(!TestPointer(glCompressedTextureSubImage3DEXT)) bIsLoaded = 0;
	glCompressedTextureSubImage2DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)gleIntGetProcAddress("glCompressedTextureSubImage2DEXT");
	if(!TestPointer(glCompressedTextureSubImage2DEXT)) bIsLoaded = 0;
	glCompressedTextureSubImage1DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)gleIntGetProcAddress("glCompressedTextureSubImage1DEXT");
	if(!TestPointer(glCompressedTextureSubImage1DEXT)) bIsLoaded = 0;
	glGetCompressedTextureImageEXT = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)gleIntGetProcAddress("glGetCompressedTextureImageEXT");
	if(!TestPointer(glGetCompressedTextureImageEXT)) bIsLoaded = 0;
	glCompressedMultiTexImage3DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexImage3DEXT");
	if(!TestPointer(glCompressedMultiTexImage3DEXT)) bIsLoaded = 0;
	glCompressedMultiTexImage2DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexImage2DEXT");
	if(!TestPointer(glCompressedMultiTexImage2DEXT)) bIsLoaded = 0;
	glCompressedMultiTexImage1DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexImage1DEXT");
	if(!TestPointer(glCompressedMultiTexImage1DEXT)) bIsLoaded = 0;
	glCompressedMultiTexSubImage3DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexSubImage3DEXT");
	if(!TestPointer(glCompressedMultiTexSubImage3DEXT)) bIsLoaded = 0;
	glCompressedMultiTexSubImage2DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexSubImage2DEXT");
	if(!TestPointer(glCompressedMultiTexSubImage2DEXT)) bIsLoaded = 0;
	glCompressedMultiTexSubImage1DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)gleIntGetProcAddress("glCompressedMultiTexSubImage1DEXT");
	if(!TestPointer(glCompressedMultiTexSubImage1DEXT)) bIsLoaded = 0;
	glGetCompressedMultiTexImageEXT = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)gleIntGetProcAddress("glGetCompressedMultiTexImageEXT");
	if(!TestPointer(glGetCompressedMultiTexImageEXT)) bIsLoaded = 0;
	glNamedProgramStringEXT = (PFNGLNAMEDPROGRAMSTRINGEXTPROC)gleIntGetProcAddress("glNamedProgramStringEXT");
	if(!TestPointer(glNamedProgramStringEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameter4dEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameter4dEXT");
	if(!TestPointer(glNamedProgramLocalParameter4dEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameter4dvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameter4dvEXT");
	if(!TestPointer(glNamedProgramLocalParameter4dvEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameter4fEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameter4fEXT");
	if(!TestPointer(glNamedProgramLocalParameter4fEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameter4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameter4fvEXT");
	if(!TestPointer(glNamedProgramLocalParameter4fvEXT)) bIsLoaded = 0;
	glGetNamedProgramLocalParameterdvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)gleIntGetProcAddress("glGetNamedProgramLocalParameterdvEXT");
	if(!TestPointer(glGetNamedProgramLocalParameterdvEXT)) bIsLoaded = 0;
	glGetNamedProgramLocalParameterfvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetNamedProgramLocalParameterfvEXT");
	if(!TestPointer(glGetNamedProgramLocalParameterfvEXT)) bIsLoaded = 0;
	glGetNamedProgramivEXT = (PFNGLGETNAMEDPROGRAMIVEXTPROC)gleIntGetProcAddress("glGetNamedProgramivEXT");
	if(!TestPointer(glGetNamedProgramivEXT)) bIsLoaded = 0;
	glGetNamedProgramStringEXT = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)gleIntGetProcAddress("glGetNamedProgramStringEXT");
	if(!TestPointer(glGetNamedProgramStringEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameters4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameters4fvEXT");
	if(!TestPointer(glNamedProgramLocalParameters4fvEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameterI4iEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameterI4iEXT");
	if(!TestPointer(glNamedProgramLocalParameterI4iEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameterI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameterI4ivEXT");
	if(!TestPointer(glNamedProgramLocalParameterI4ivEXT)) bIsLoaded = 0;
	glNamedProgramLocalParametersI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParametersI4ivEXT");
	if(!TestPointer(glNamedProgramLocalParametersI4ivEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameterI4uiEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameterI4uiEXT");
	if(!TestPointer(glNamedProgramLocalParameterI4uiEXT)) bIsLoaded = 0;
	glNamedProgramLocalParameterI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParameterI4uivEXT");
	if(!TestPointer(glNamedProgramLocalParameterI4uivEXT)) bIsLoaded = 0;
	glNamedProgramLocalParametersI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)gleIntGetProcAddress("glNamedProgramLocalParametersI4uivEXT");
	if(!TestPointer(glNamedProgramLocalParametersI4uivEXT)) bIsLoaded = 0;
	glGetNamedProgramLocalParameterIivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)gleIntGetProcAddress("glGetNamedProgramLocalParameterIivEXT");
	if(!TestPointer(glGetNamedProgramLocalParameterIivEXT)) bIsLoaded = 0;
	glGetNamedProgramLocalParameterIuivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glGetNamedProgramLocalParameterIuivEXT");
	if(!TestPointer(glGetNamedProgramLocalParameterIuivEXT)) bIsLoaded = 0;
	glTextureParameterIivEXT = (PFNGLTEXTUREPARAMETERIIVEXTPROC)gleIntGetProcAddress("glTextureParameterIivEXT");
	if(!TestPointer(glTextureParameterIivEXT)) bIsLoaded = 0;
	glTextureParameterIuivEXT = (PFNGLTEXTUREPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glTextureParameterIuivEXT");
	if(!TestPointer(glTextureParameterIuivEXT)) bIsLoaded = 0;
	glGetTextureParameterIivEXT = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC)gleIntGetProcAddress("glGetTextureParameterIivEXT");
	if(!TestPointer(glGetTextureParameterIivEXT)) bIsLoaded = 0;
	glGetTextureParameterIuivEXT = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glGetTextureParameterIuivEXT");
	if(!TestPointer(glGetTextureParameterIuivEXT)) bIsLoaded = 0;
	glMultiTexParameterIivEXT = (PFNGLMULTITEXPARAMETERIIVEXTPROC)gleIntGetProcAddress("glMultiTexParameterIivEXT");
	if(!TestPointer(glMultiTexParameterIivEXT)) bIsLoaded = 0;
	glMultiTexParameterIuivEXT = (PFNGLMULTITEXPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glMultiTexParameterIuivEXT");
	if(!TestPointer(glMultiTexParameterIuivEXT)) bIsLoaded = 0;
	glGetMultiTexParameterIivEXT = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC)gleIntGetProcAddress("glGetMultiTexParameterIivEXT");
	if(!TestPointer(glGetMultiTexParameterIivEXT)) bIsLoaded = 0;
	glGetMultiTexParameterIuivEXT = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glGetMultiTexParameterIuivEXT");
	if(!TestPointer(glGetMultiTexParameterIuivEXT)) bIsLoaded = 0;
	glProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC)gleIntGetProcAddress("glProgramUniform1fEXT");
	if(!TestPointer(glProgramUniform1fEXT)) bIsLoaded = 0;
	glProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC)gleIntGetProcAddress("glProgramUniform2fEXT");
	if(!TestPointer(glProgramUniform2fEXT)) bIsLoaded = 0;
	glProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC)gleIntGetProcAddress("glProgramUniform3fEXT");
	if(!TestPointer(glProgramUniform3fEXT)) bIsLoaded = 0;
	glProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC)gleIntGetProcAddress("glProgramUniform4fEXT");
	if(!TestPointer(glProgramUniform4fEXT)) bIsLoaded = 0;
	glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC)gleIntGetProcAddress("glProgramUniform1iEXT");
	if(!TestPointer(glProgramUniform1iEXT)) bIsLoaded = 0;
	glProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC)gleIntGetProcAddress("glProgramUniform2iEXT");
	if(!TestPointer(glProgramUniform2iEXT)) bIsLoaded = 0;
	glProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC)gleIntGetProcAddress("glProgramUniform3iEXT");
	if(!TestPointer(glProgramUniform3iEXT)) bIsLoaded = 0;
	glProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC)gleIntGetProcAddress("glProgramUniform4iEXT");
	if(!TestPointer(glProgramUniform4iEXT)) bIsLoaded = 0;
	glProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC)gleIntGetProcAddress("glProgramUniform1fvEXT");
	if(!TestPointer(glProgramUniform1fvEXT)) bIsLoaded = 0;
	glProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC)gleIntGetProcAddress("glProgramUniform2fvEXT");
	if(!TestPointer(glProgramUniform2fvEXT)) bIsLoaded = 0;
	glProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC)gleIntGetProcAddress("glProgramUniform3fvEXT");
	if(!TestPointer(glProgramUniform3fvEXT)) bIsLoaded = 0;
	glProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC)gleIntGetProcAddress("glProgramUniform4fvEXT");
	if(!TestPointer(glProgramUniform4fvEXT)) bIsLoaded = 0;
	glProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC)gleIntGetProcAddress("glProgramUniform1ivEXT");
	if(!TestPointer(glProgramUniform1ivEXT)) bIsLoaded = 0;
	glProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC)gleIntGetProcAddress("glProgramUniform2ivEXT");
	if(!TestPointer(glProgramUniform2ivEXT)) bIsLoaded = 0;
	glProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC)gleIntGetProcAddress("glProgramUniform3ivEXT");
	if(!TestPointer(glProgramUniform3ivEXT)) bIsLoaded = 0;
	glProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC)gleIntGetProcAddress("glProgramUniform4ivEXT");
	if(!TestPointer(glProgramUniform4ivEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2fvEXT");
	if(!TestPointer(glProgramUniformMatrix2fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3fvEXT");
	if(!TestPointer(glProgramUniformMatrix3fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4fvEXT");
	if(!TestPointer(glProgramUniformMatrix4fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3fvEXT");
	if(!TestPointer(glProgramUniformMatrix2x3fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2fvEXT");
	if(!TestPointer(glProgramUniformMatrix3x2fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4fvEXT");
	if(!TestPointer(glProgramUniformMatrix2x4fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2fvEXT");
	if(!TestPointer(glProgramUniformMatrix4x2fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4fvEXT");
	if(!TestPointer(glProgramUniformMatrix3x4fvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3fvEXT");
	if(!TestPointer(glProgramUniformMatrix4x3fvEXT)) bIsLoaded = 0;
	glProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC)gleIntGetProcAddress("glProgramUniform1uiEXT");
	if(!TestPointer(glProgramUniform1uiEXT)) bIsLoaded = 0;
	glProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC)gleIntGetProcAddress("glProgramUniform2uiEXT");
	if(!TestPointer(glProgramUniform2uiEXT)) bIsLoaded = 0;
	glProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC)gleIntGetProcAddress("glProgramUniform3uiEXT");
	if(!TestPointer(glProgramUniform3uiEXT)) bIsLoaded = 0;
	glProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC)gleIntGetProcAddress("glProgramUniform4uiEXT");
	if(!TestPointer(glProgramUniform4uiEXT)) bIsLoaded = 0;
	glProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC)gleIntGetProcAddress("glProgramUniform1uivEXT");
	if(!TestPointer(glProgramUniform1uivEXT)) bIsLoaded = 0;
	glProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC)gleIntGetProcAddress("glProgramUniform2uivEXT");
	if(!TestPointer(glProgramUniform2uivEXT)) bIsLoaded = 0;
	glProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC)gleIntGetProcAddress("glProgramUniform3uivEXT");
	if(!TestPointer(glProgramUniform3uivEXT)) bIsLoaded = 0;
	glProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC)gleIntGetProcAddress("glProgramUniform4uivEXT");
	if(!TestPointer(glProgramUniform4uivEXT)) bIsLoaded = 0;
	glNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC)gleIntGetProcAddress("glNamedBufferDataEXT");
	if(!TestPointer(glNamedBufferDataEXT)) bIsLoaded = 0;
	glNamedBufferSubDataEXT = (PFNGLNAMEDBUFFERSUBDATAEXTPROC)gleIntGetProcAddress("glNamedBufferSubDataEXT");
	if(!TestPointer(glNamedBufferSubDataEXT)) bIsLoaded = 0;
	glMapNamedBufferEXT = (PFNGLMAPNAMEDBUFFEREXTPROC)gleIntGetProcAddress("glMapNamedBufferEXT");
	if(!TestPointer(glMapNamedBufferEXT)) bIsLoaded = 0;
	glUnmapNamedBufferEXT = (PFNGLUNMAPNAMEDBUFFEREXTPROC)gleIntGetProcAddress("glUnmapNamedBufferEXT");
	if(!TestPointer(glUnmapNamedBufferEXT)) bIsLoaded = 0;
	glMapNamedBufferRangeEXT = (PFNGLMAPNAMEDBUFFERRANGEEXTPROC)gleIntGetProcAddress("glMapNamedBufferRangeEXT");
	if(!TestPointer(glMapNamedBufferRangeEXT)) bIsLoaded = 0;
	glFlushMappedNamedBufferRangeEXT = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)gleIntGetProcAddress("glFlushMappedNamedBufferRangeEXT");
	if(!TestPointer(glFlushMappedNamedBufferRangeEXT)) bIsLoaded = 0;
	glNamedCopyBufferSubDataEXT = (PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)gleIntGetProcAddress("glNamedCopyBufferSubDataEXT");
	if(!TestPointer(glNamedCopyBufferSubDataEXT)) bIsLoaded = 0;
	glGetNamedBufferParameterivEXT = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetNamedBufferParameterivEXT");
	if(!TestPointer(glGetNamedBufferParameterivEXT)) bIsLoaded = 0;
	glGetNamedBufferPointervEXT = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)gleIntGetProcAddress("glGetNamedBufferPointervEXT");
	if(!TestPointer(glGetNamedBufferPointervEXT)) bIsLoaded = 0;
	glGetNamedBufferSubDataEXT = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)gleIntGetProcAddress("glGetNamedBufferSubDataEXT");
	if(!TestPointer(glGetNamedBufferSubDataEXT)) bIsLoaded = 0;
	glTextureBufferEXT = (PFNGLTEXTUREBUFFEREXTPROC)gleIntGetProcAddress("glTextureBufferEXT");
	if(!TestPointer(glTextureBufferEXT)) bIsLoaded = 0;
	glMultiTexBufferEXT = (PFNGLMULTITEXBUFFEREXTPROC)gleIntGetProcAddress("glMultiTexBufferEXT");
	if(!TestPointer(glMultiTexBufferEXT)) bIsLoaded = 0;
	glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)gleIntGetProcAddress("glNamedRenderbufferStorageEXT");
	if(!TestPointer(glNamedRenderbufferStorageEXT)) bIsLoaded = 0;
	glGetNamedRenderbufferParameterivEXT = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetNamedRenderbufferParameterivEXT");
	if(!TestPointer(glGetNamedRenderbufferParameterivEXT)) bIsLoaded = 0;
	glCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)gleIntGetProcAddress("glCheckNamedFramebufferStatusEXT");
	if(!TestPointer(glCheckNamedFramebufferStatusEXT)) bIsLoaded = 0;
	glNamedFramebufferTexture1DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)gleIntGetProcAddress("glNamedFramebufferTexture1DEXT");
	if(!TestPointer(glNamedFramebufferTexture1DEXT)) bIsLoaded = 0;
	glNamedFramebufferTexture2DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)gleIntGetProcAddress("glNamedFramebufferTexture2DEXT");
	if(!TestPointer(glNamedFramebufferTexture2DEXT)) bIsLoaded = 0;
	glNamedFramebufferTexture3DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)gleIntGetProcAddress("glNamedFramebufferTexture3DEXT");
	if(!TestPointer(glNamedFramebufferTexture3DEXT)) bIsLoaded = 0;
	glNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)gleIntGetProcAddress("glNamedFramebufferRenderbufferEXT");
	if(!TestPointer(glNamedFramebufferRenderbufferEXT)) bIsLoaded = 0;
	glGetNamedFramebufferAttachmentParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetNamedFramebufferAttachmentParameterivEXT");
	if(!TestPointer(glGetNamedFramebufferAttachmentParameterivEXT)) bIsLoaded = 0;
	glGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC)gleIntGetProcAddress("glGenerateTextureMipmapEXT");
	if(!TestPointer(glGenerateTextureMipmapEXT)) bIsLoaded = 0;
	glGenerateMultiTexMipmapEXT = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC)gleIntGetProcAddress("glGenerateMultiTexMipmapEXT");
	if(!TestPointer(glGenerateMultiTexMipmapEXT)) bIsLoaded = 0;
	glFramebufferDrawBufferEXT = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)gleIntGetProcAddress("glFramebufferDrawBufferEXT");
	if(!TestPointer(glFramebufferDrawBufferEXT)) bIsLoaded = 0;
	glFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)gleIntGetProcAddress("glFramebufferDrawBuffersEXT");
	if(!TestPointer(glFramebufferDrawBuffersEXT)) bIsLoaded = 0;
	glFramebufferReadBufferEXT = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC)gleIntGetProcAddress("glFramebufferReadBufferEXT");
	if(!TestPointer(glFramebufferReadBufferEXT)) bIsLoaded = 0;
	glGetFramebufferParameterivEXT = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetFramebufferParameterivEXT");
	if(!TestPointer(glGetFramebufferParameterivEXT)) bIsLoaded = 0;
	glNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)gleIntGetProcAddress("glNamedRenderbufferStorageMultisampleEXT");
	if(!TestPointer(glNamedRenderbufferStorageMultisampleEXT)) bIsLoaded = 0;
	glNamedRenderbufferStorageMultisampleCoverageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)gleIntGetProcAddress("glNamedRenderbufferStorageMultisampleCoverageEXT");
	if(!TestPointer(glNamedRenderbufferStorageMultisampleCoverageEXT)) bIsLoaded = 0;
	glNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)gleIntGetProcAddress("glNamedFramebufferTextureEXT");
	if(!TestPointer(glNamedFramebufferTextureEXT)) bIsLoaded = 0;
	glNamedFramebufferTextureLayerEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)gleIntGetProcAddress("glNamedFramebufferTextureLayerEXT");
	if(!TestPointer(glNamedFramebufferTextureLayerEXT)) bIsLoaded = 0;
	glNamedFramebufferTextureFaceEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)gleIntGetProcAddress("glNamedFramebufferTextureFaceEXT");
	if(!TestPointer(glNamedFramebufferTextureFaceEXT)) bIsLoaded = 0;
	glTextureRenderbufferEXT = (PFNGLTEXTURERENDERBUFFEREXTPROC)gleIntGetProcAddress("glTextureRenderbufferEXT");
	if(!TestPointer(glTextureRenderbufferEXT)) bIsLoaded = 0;
	glMultiTexRenderbufferEXT = (PFNGLMULTITEXRENDERBUFFEREXTPROC)gleIntGetProcAddress("glMultiTexRenderbufferEXT");
	if(!TestPointer(glMultiTexRenderbufferEXT)) bIsLoaded = 0;
	glProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC)gleIntGetProcAddress("glProgramUniform1dEXT");
	if(!TestPointer(glProgramUniform1dEXT)) bIsLoaded = 0;
	glProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC)gleIntGetProcAddress("glProgramUniform2dEXT");
	if(!TestPointer(glProgramUniform2dEXT)) bIsLoaded = 0;
	glProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC)gleIntGetProcAddress("glProgramUniform3dEXT");
	if(!TestPointer(glProgramUniform3dEXT)) bIsLoaded = 0;
	glProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC)gleIntGetProcAddress("glProgramUniform4dEXT");
	if(!TestPointer(glProgramUniform4dEXT)) bIsLoaded = 0;
	glProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC)gleIntGetProcAddress("glProgramUniform1dvEXT");
	if(!TestPointer(glProgramUniform1dvEXT)) bIsLoaded = 0;
	glProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC)gleIntGetProcAddress("glProgramUniform2dvEXT");
	if(!TestPointer(glProgramUniform2dvEXT)) bIsLoaded = 0;
	glProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC)gleIntGetProcAddress("glProgramUniform3dvEXT");
	if(!TestPointer(glProgramUniform3dvEXT)) bIsLoaded = 0;
	glProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC)gleIntGetProcAddress("glProgramUniform4dvEXT");
	if(!TestPointer(glProgramUniform4dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2dvEXT");
	if(!TestPointer(glProgramUniformMatrix2dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3dvEXT");
	if(!TestPointer(glProgramUniformMatrix3dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4dvEXT");
	if(!TestPointer(glProgramUniformMatrix4dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3dvEXT");
	if(!TestPointer(glProgramUniformMatrix2x3dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4dvEXT");
	if(!TestPointer(glProgramUniformMatrix2x4dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2dvEXT");
	if(!TestPointer(glProgramUniformMatrix3x2dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4dvEXT");
	if(!TestPointer(glProgramUniformMatrix3x4dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2dvEXT");
	if(!TestPointer(glProgramUniformMatrix4x2dvEXT)) bIsLoaded = 0;
	glProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3dvEXT");
	if(!TestPointer(glProgramUniformMatrix4x3dvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCOLORMASKINDEXEDEXTPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANINDEXEDVEXTPROC)(GLenum target, GLuint index, GLboolean *data);
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERINDEXEDVEXTPROC)(GLenum target, GLuint index, GLint *data);
typedef void (GLE_FUNCPTR * PFNGLENABLEINDEXEDEXTPROC)(GLenum target, GLuint index);
typedef void (GLE_FUNCPTR * PFNGLDISABLEINDEXEDEXTPROC)(GLenum target, GLuint index);
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDINDEXEDEXTPROC)(GLenum target, GLuint index);

PFNGLCOLORMASKINDEXEDEXTPROC glColorMaskIndexedEXT;
PFNGLGETBOOLEANINDEXEDVEXTPROC glGetBooleanIndexedvEXT;
PFNGLGETINTEGERINDEXEDVEXTPROC glGetIntegerIndexedvEXT;
PFNGLENABLEINDEXEDEXTPROC glEnableIndexedEXT;
PFNGLDISABLEINDEXEDEXTPROC glDisableIndexedEXT;
PFNGLISENABLEDINDEXEDEXTPROC glIsEnabledIndexedEXT;

static int gleIntLoad_EXT_draw_buffers2()
{
	int bIsLoaded = 1;
	glColorMaskIndexedEXT = (PFNGLCOLORMASKINDEXEDEXTPROC)gleIntGetProcAddress("glColorMaskIndexedEXT");
	if(!TestPointer(glColorMaskIndexedEXT)) bIsLoaded = 0;
	glGetBooleanIndexedvEXT = (PFNGLGETBOOLEANINDEXEDVEXTPROC)gleIntGetProcAddress("glGetBooleanIndexedvEXT");
	if(!TestPointer(glGetBooleanIndexedvEXT)) bIsLoaded = 0;
	glGetIntegerIndexedvEXT = (PFNGLGETINTEGERINDEXEDVEXTPROC)gleIntGetProcAddress("glGetIntegerIndexedvEXT");
	if(!TestPointer(glGetIntegerIndexedvEXT)) bIsLoaded = 0;
	glEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC)gleIntGetProcAddress("glEnableIndexedEXT");
	if(!TestPointer(glEnableIndexedEXT)) bIsLoaded = 0;
	glDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC)gleIntGetProcAddress("glDisableIndexedEXT");
	if(!TestPointer(glDisableIndexedEXT)) bIsLoaded = 0;
	glIsEnabledIndexedEXT = (PFNGLISENABLEDINDEXEDEXTPROC)gleIntGetProcAddress("glIsEnabledIndexedEXT");
	if(!TestPointer(glIsEnabledIndexedEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDEXTPROC)(GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDEXTPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);

PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstancedEXT;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstancedEXT;

static int gleIntLoad_EXT_draw_instanced()
{
	int bIsLoaded = 1;
	glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC)gleIntGetProcAddress("glDrawArraysInstancedEXT");
	if(!TestPointer(glDrawArraysInstancedEXT)) bIsLoaded = 0;
	glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC)gleIntGetProcAddress("glDrawElementsInstancedEXT");
	if(!TestPointer(glDrawElementsInstancedEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSEXTPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElementsEXT;

static int gleIntLoad_EXT_draw_range_elements()
{
	int bIsLoaded = 1;
	glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC)gleIntGetProcAddress("glDrawRangeElementsEXT");
	if(!TestPointer(glDrawRangeElementsEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFEXTPROC)(GLfloat coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFVEXTPROC)(const GLfloat *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDEXTPROC)(GLdouble coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDVEXTPROC)(const GLdouble *coord);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTEREXTPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);

PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT;
PFNGLFOGCOORDDEXTPROC glFogCoorddEXT;
PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT;
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT;

static int gleIntLoad_EXT_fog_coord()
{
	int bIsLoaded = 1;
	glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC)gleIntGetProcAddress("glFogCoordfEXT");
	if(!TestPointer(glFogCoordfEXT)) bIsLoaded = 0;
	glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC)gleIntGetProcAddress("glFogCoordfvEXT");
	if(!TestPointer(glFogCoordfvEXT)) bIsLoaded = 0;
	glFogCoorddEXT = (PFNGLFOGCOORDDEXTPROC)gleIntGetProcAddress("glFogCoorddEXT");
	if(!TestPointer(glFogCoorddEXT)) bIsLoaded = 0;
	glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC)gleIntGetProcAddress("glFogCoorddvEXT");
	if(!TestPointer(glFogCoorddvEXT)) bIsLoaded = 0;
	glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC)gleIntGetProcAddress("glFogCoordPointerEXT");
	if(!TestPointer(glFogCoordPointerEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBLITFRAMEBUFFEREXTPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

PFNGLBLITFRAMEBUFFEREXTPROC glBlitFramebufferEXT;

static int gleIntLoad_EXT_framebuffer_blit()
{
	int bIsLoaded = 1;
	glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC)gleIntGetProcAddress("glBlitFramebufferEXT");
	if(!TestPointer(glBlitFramebufferEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glRenderbufferStorageMultisampleEXT;

static int gleIntLoad_EXT_framebuffer_multisample()
{
	int bIsLoaded = 1;
	glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)gleIntGetProcAddress("glRenderbufferStorageMultisampleEXT");
	if(!TestPointer(glRenderbufferStorageMultisampleEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;

static int gleIntLoad_EXT_framebuffer_object()
{
	int bIsLoaded = 1;
	glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)gleIntGetProcAddress("glIsRenderbufferEXT");
	if(!TestPointer(glIsRenderbufferEXT)) bIsLoaded = 0;
	glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)gleIntGetProcAddress("glBindRenderbufferEXT");
	if(!TestPointer(glBindRenderbufferEXT)) bIsLoaded = 0;
	glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)gleIntGetProcAddress("glDeleteRenderbuffersEXT");
	if(!TestPointer(glDeleteRenderbuffersEXT)) bIsLoaded = 0;
	glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)gleIntGetProcAddress("glGenRenderbuffersEXT");
	if(!TestPointer(glGenRenderbuffersEXT)) bIsLoaded = 0;
	glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)gleIntGetProcAddress("glRenderbufferStorageEXT");
	if(!TestPointer(glRenderbufferStorageEXT)) bIsLoaded = 0;
	glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetRenderbufferParameterivEXT");
	if(!TestPointer(glGetRenderbufferParameterivEXT)) bIsLoaded = 0;
	glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)gleIntGetProcAddress("glIsFramebufferEXT");
	if(!TestPointer(glIsFramebufferEXT)) bIsLoaded = 0;
	glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)gleIntGetProcAddress("glBindFramebufferEXT");
	if(!TestPointer(glBindFramebufferEXT)) bIsLoaded = 0;
	glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)gleIntGetProcAddress("glDeleteFramebuffersEXT");
	if(!TestPointer(glDeleteFramebuffersEXT)) bIsLoaded = 0;
	glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)gleIntGetProcAddress("glGenFramebuffersEXT");
	if(!TestPointer(glGenFramebuffersEXT)) bIsLoaded = 0;
	glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)gleIntGetProcAddress("glCheckFramebufferStatusEXT");
	if(!TestPointer(glCheckFramebufferStatusEXT)) bIsLoaded = 0;
	glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)gleIntGetProcAddress("glFramebufferTexture1DEXT");
	if(!TestPointer(glFramebufferTexture1DEXT)) bIsLoaded = 0;
	glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)gleIntGetProcAddress("glFramebufferTexture2DEXT");
	if(!TestPointer(glFramebufferTexture2DEXT)) bIsLoaded = 0;
	glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)gleIntGetProcAddress("glFramebufferTexture3DEXT");
	if(!TestPointer(glFramebufferTexture3DEXT)) bIsLoaded = 0;
	glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)gleIntGetProcAddress("glFramebufferRenderbufferEXT");
	if(!TestPointer(glFramebufferRenderbufferEXT)) bIsLoaded = 0;
	glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
	if(!TestPointer(glGetFramebufferAttachmentParameterivEXT)) bIsLoaded = 0;
	glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)gleIntGetProcAddress("glGenerateMipmapEXT");
	if(!TestPointer(glGenerateMipmapEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPROGRAMPARAMETERIEXTPROC)(GLuint program, GLenum pname, GLint value);

PFNGLPROGRAMPARAMETERIEXTPROC glProgramParameteriEXT;

static int gleIntLoad_EXT_geometry_shader4()
{
	int bIsLoaded = 1;
	glProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC)gleIntGetProcAddress("glProgramParameteriEXT");
	if(!TestPointer(glProgramParameteriEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)(GLenum target, GLuint index, GLsizei count, const GLfloat *params);

PFNGLPROGRAMENVPARAMETERS4FVEXTPROC glProgramEnvParameters4fvEXT;
PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC glProgramLocalParameters4fvEXT;

static int gleIntLoad_EXT_gpu_program_parameters()
{
	int bIsLoaded = 1;
	glProgramEnvParameters4fvEXT = (PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)gleIntGetProcAddress("glProgramEnvParameters4fvEXT");
	if(!TestPointer(glProgramEnvParameters4fvEXT)) bIsLoaded = 0;
	glProgramLocalParameters4fvEXT = (PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)gleIntGetProcAddress("glProgramLocalParameters4fvEXT");
	if(!TestPointer(glProgramLocalParameters4fvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGETUNIFORMUIVEXTPROC glGetUniformuivEXT;
PFNGLBINDFRAGDATALOCATIONEXTPROC glBindFragDataLocationEXT;
PFNGLGETFRAGDATALOCATIONEXTPROC glGetFragDataLocationEXT;
PFNGLUNIFORM1UIEXTPROC glUniform1uiEXT;
PFNGLUNIFORM2UIEXTPROC glUniform2uiEXT;
PFNGLUNIFORM3UIEXTPROC glUniform3uiEXT;
PFNGLUNIFORM4UIEXTPROC glUniform4uiEXT;
PFNGLUNIFORM1UIVEXTPROC glUniform1uivEXT;
PFNGLUNIFORM2UIVEXTPROC glUniform2uivEXT;
PFNGLUNIFORM3UIVEXTPROC glUniform3uivEXT;
PFNGLUNIFORM4UIVEXTPROC glUniform4uivEXT;

static int gleIntLoad_EXT_gpu_shader4()
{
	int bIsLoaded = 1;
	glGetUniformuivEXT = (PFNGLGETUNIFORMUIVEXTPROC)gleIntGetProcAddress("glGetUniformuivEXT");
	if(!TestPointer(glGetUniformuivEXT)) bIsLoaded = 0;
	glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC)gleIntGetProcAddress("glBindFragDataLocationEXT");
	if(!TestPointer(glBindFragDataLocationEXT)) bIsLoaded = 0;
	glGetFragDataLocationEXT = (PFNGLGETFRAGDATALOCATIONEXTPROC)gleIntGetProcAddress("glGetFragDataLocationEXT");
	if(!TestPointer(glGetFragDataLocationEXT)) bIsLoaded = 0;
	glUniform1uiEXT = (PFNGLUNIFORM1UIEXTPROC)gleIntGetProcAddress("glUniform1uiEXT");
	if(!TestPointer(glUniform1uiEXT)) bIsLoaded = 0;
	glUniform2uiEXT = (PFNGLUNIFORM2UIEXTPROC)gleIntGetProcAddress("glUniform2uiEXT");
	if(!TestPointer(glUniform2uiEXT)) bIsLoaded = 0;
	glUniform3uiEXT = (PFNGLUNIFORM3UIEXTPROC)gleIntGetProcAddress("glUniform3uiEXT");
	if(!TestPointer(glUniform3uiEXT)) bIsLoaded = 0;
	glUniform4uiEXT = (PFNGLUNIFORM4UIEXTPROC)gleIntGetProcAddress("glUniform4uiEXT");
	if(!TestPointer(glUniform4uiEXT)) bIsLoaded = 0;
	glUniform1uivEXT = (PFNGLUNIFORM1UIVEXTPROC)gleIntGetProcAddress("glUniform1uivEXT");
	if(!TestPointer(glUniform1uivEXT)) bIsLoaded = 0;
	glUniform2uivEXT = (PFNGLUNIFORM2UIVEXTPROC)gleIntGetProcAddress("glUniform2uivEXT");
	if(!TestPointer(glUniform2uivEXT)) bIsLoaded = 0;
	glUniform3uivEXT = (PFNGLUNIFORM3UIVEXTPROC)gleIntGetProcAddress("glUniform3uivEXT");
	if(!TestPointer(glUniform3uivEXT)) bIsLoaded = 0;
	glUniform4uivEXT = (PFNGLUNIFORM4UIVEXTPROC)gleIntGetProcAddress("glUniform4uivEXT");
	if(!TestPointer(glUniform4uivEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLGETHISTOGRAMEXTPROC glGetHistogramEXT;
PFNGLGETHISTOGRAMPARAMETERFVEXTPROC glGetHistogramParameterfvEXT;
PFNGLGETHISTOGRAMPARAMETERIVEXTPROC glGetHistogramParameterivEXT;
PFNGLGETMINMAXEXTPROC glGetMinmaxEXT;
PFNGLGETMINMAXPARAMETERFVEXTPROC glGetMinmaxParameterfvEXT;
PFNGLGETMINMAXPARAMETERIVEXTPROC glGetMinmaxParameterivEXT;
PFNGLHISTOGRAMEXTPROC glHistogramEXT;
PFNGLMINMAXEXTPROC glMinmaxEXT;
PFNGLRESETHISTOGRAMEXTPROC glResetHistogramEXT;
PFNGLRESETMINMAXEXTPROC glResetMinmaxEXT;

static int gleIntLoad_EXT_histogram()
{
	int bIsLoaded = 1;
	glGetHistogramEXT = (PFNGLGETHISTOGRAMEXTPROC)gleIntGetProcAddress("glGetHistogramEXT");
	if(!TestPointer(glGetHistogramEXT)) bIsLoaded = 0;
	glGetHistogramParameterfvEXT = (PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetHistogramParameterfvEXT");
	if(!TestPointer(glGetHistogramParameterfvEXT)) bIsLoaded = 0;
	glGetHistogramParameterivEXT = (PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetHistogramParameterivEXT");
	if(!TestPointer(glGetHistogramParameterivEXT)) bIsLoaded = 0;
	glGetMinmaxEXT = (PFNGLGETMINMAXEXTPROC)gleIntGetProcAddress("glGetMinmaxEXT");
	if(!TestPointer(glGetMinmaxEXT)) bIsLoaded = 0;
	glGetMinmaxParameterfvEXT = (PFNGLGETMINMAXPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetMinmaxParameterfvEXT");
	if(!TestPointer(glGetMinmaxParameterfvEXT)) bIsLoaded = 0;
	glGetMinmaxParameterivEXT = (PFNGLGETMINMAXPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetMinmaxParameterivEXT");
	if(!TestPointer(glGetMinmaxParameterivEXT)) bIsLoaded = 0;
	glHistogramEXT = (PFNGLHISTOGRAMEXTPROC)gleIntGetProcAddress("glHistogramEXT");
	if(!TestPointer(glHistogramEXT)) bIsLoaded = 0;
	glMinmaxEXT = (PFNGLMINMAXEXTPROC)gleIntGetProcAddress("glMinmaxEXT");
	if(!TestPointer(glMinmaxEXT)) bIsLoaded = 0;
	glResetHistogramEXT = (PFNGLRESETHISTOGRAMEXTPROC)gleIntGetProcAddress("glResetHistogramEXT");
	if(!TestPointer(glResetHistogramEXT)) bIsLoaded = 0;
	glResetMinmaxEXT = (PFNGLRESETMINMAXEXTPROC)gleIntGetProcAddress("glResetMinmaxEXT");
	if(!TestPointer(glResetMinmaxEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLINDEXFUNCEXTPROC)(GLenum func, GLclampf ref);

PFNGLINDEXFUNCEXTPROC glIndexFuncEXT;

static int gleIntLoad_EXT_index_func()
{
	int bIsLoaded = 1;
	glIndexFuncEXT = (PFNGLINDEXFUNCEXTPROC)gleIntGetProcAddress("glIndexFuncEXT");
	if(!TestPointer(glIndexFuncEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLINDEXMATERIALEXTPROC)(GLenum face, GLenum mode);

PFNGLINDEXMATERIALEXTPROC glIndexMaterialEXT;

static int gleIntLoad_EXT_index_material()
{
	int bIsLoaded = 1;
	glIndexMaterialEXT = (PFNGLINDEXMATERIALEXTPROC)gleIntGetProcAddress("glIndexMaterialEXT");
	if(!TestPointer(glIndexMaterialEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLAPPLYTEXTUREEXTPROC)(GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLTEXTURELIGHTEXTPROC)(GLenum pname);
typedef void (GLE_FUNCPTR * PFNGLTEXTUREMATERIALEXTPROC)(GLenum face, GLenum mode);

PFNGLAPPLYTEXTUREEXTPROC glApplyTextureEXT;
PFNGLTEXTURELIGHTEXTPROC glTextureLightEXT;
PFNGLTEXTUREMATERIALEXTPROC glTextureMaterialEXT;

static int gleIntLoad_EXT_light_texture()
{
	int bIsLoaded = 1;
	glApplyTextureEXT = (PFNGLAPPLYTEXTUREEXTPROC)gleIntGetProcAddress("glApplyTextureEXT");
	if(!TestPointer(glApplyTextureEXT)) bIsLoaded = 0;
	glTextureLightEXT = (PFNGLTEXTURELIGHTEXTPROC)gleIntGetProcAddress("glTextureLightEXT");
	if(!TestPointer(glTextureLightEXT)) bIsLoaded = 0;
	glTextureMaterialEXT = (PFNGLTEXTUREMATERIALEXTPROC)gleIntGetProcAddress("glTextureMaterialEXT");
	if(!TestPointer(glTextureMaterialEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWARRAYSEXTPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSEXTPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);

PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT;
PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT;

static int gleIntLoad_EXT_multi_draw_arrays()
{
	int bIsLoaded = 1;
	glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC)gleIntGetProcAddress("glMultiDrawArraysEXT");
	if(!TestPointer(glMultiDrawArraysEXT)) bIsLoaded = 0;
	glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC)gleIntGetProcAddress("glMultiDrawElementsEXT");
	if(!TestPointer(glMultiDrawElementsEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKEXTPROC)(GLclampf value, GLboolean invert);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEPATTERNEXTPROC)(GLenum pattern);

PFNGLSAMPLEMASKEXTPROC glSampleMaskEXT;
PFNGLSAMPLEPATTERNEXTPROC glSamplePatternEXT;

static int gleIntLoad_EXT_multisample()
{
	int bIsLoaded = 1;
	glSampleMaskEXT = (PFNGLSAMPLEMASKEXTPROC)gleIntGetProcAddress("glSampleMaskEXT");
	if(!TestPointer(glSampleMaskEXT)) bIsLoaded = 0;
	glSamplePatternEXT = (PFNGLSAMPLEPATTERNEXTPROC)gleIntGetProcAddress("glSamplePatternEXT");
	if(!TestPointer(glSamplePatternEXT)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEEXTPROC)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEEXTPROC)(GLenum target, GLenum format, GLenum type, GLvoid *data);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);

PFNGLCOLORTABLEEXTPROC glColorTableEXT;
PFNGLGETCOLORTABLEEXTPROC glGetColorTableEXT;
PFNGLGETCOLORTABLEPARAMETERIVEXTPROC glGetColorTableParameterivEXT;
PFNGLGETCOLORTABLEPARAMETERFVEXTPROC glGetColorTableParameterfvEXT;

static int gleIntLoad_EXT_paletted_texture()
{
	int bIsLoaded = 1;
	glColorTableEXT = (PFNGLCOLORTABLEEXTPROC)gleIntGetProcAddress("glColorTableEXT");
	if(!TestPointer(glColorTableEXT)) bIsLoaded = 0;
	glGetColorTableEXT = (PFNGLGETCOLORTABLEEXTPROC)gleIntGetProcAddress("glGetColorTableEXT");
	if(!TestPointer(glGetColorTableEXT)) bIsLoaded = 0;
	glGetColorTableParameterivEXT = (PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)gleIntGetProcAddress("glGetColorTableParameterivEXT");
	if(!TestPointer(glGetColorTableParameterivEXT)) bIsLoaded = 0;
	glGetColorTableParameterfvEXT = (PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)gleIntGetProcAddress("glGetColorTableParameterfvEXT");
	if(!TestPointer(glGetColorTableParameterfvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)(GLenum target, GLenum pname, const GLfloat *params);

PFNGLPIXELTRANSFORMPARAMETERIEXTPROC glPixelTransformParameteriEXT;
PFNGLPIXELTRANSFORMPARAMETERFEXTPROC glPixelTransformParameterfEXT;
PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC glPixelTransformParameterivEXT;
PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC glPixelTransformParameterfvEXT;

static int gleIntLoad_EXT_pixel_transform()
{
	int bIsLoaded = 1;
	glPixelTransformParameteriEXT = (PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)gleIntGetProcAddress("glPixelTransformParameteriEXT");
	if(!TestPointer(glPixelTransformParameteriEXT)) bIsLoaded = 0;
	glPixelTransformParameterfEXT = (PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)gleIntGetProcAddress("glPixelTransformParameterfEXT");
	if(!TestPointer(glPixelTransformParameterfEXT)) bIsLoaded = 0;
	glPixelTransformParameterivEXT = (PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)gleIntGetProcAddress("glPixelTransformParameterivEXT");
	if(!TestPointer(glPixelTransformParameterivEXT)) bIsLoaded = 0;
	glPixelTransformParameterfvEXT = (PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)gleIntGetProcAddress("glPixelTransformParameterfvEXT");
	if(!TestPointer(glPixelTransformParameterfvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFEXTPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVEXTPROC)(GLenum pname, const GLfloat *params);

PFNGLPOINTPARAMETERFEXTPROC glPointParameterfEXT;
PFNGLPOINTPARAMETERFVEXTPROC glPointParameterfvEXT;

static int gleIntLoad_EXT_point_parameters()
{
	int bIsLoaded = 1;
	glPointParameterfEXT = (PFNGLPOINTPARAMETERFEXTPROC)gleIntGetProcAddress("glPointParameterfEXT");
	if(!TestPointer(glPointParameterfEXT)) bIsLoaded = 0;
	glPointParameterfvEXT = (PFNGLPOINTPARAMETERFVEXTPROC)gleIntGetProcAddress("glPointParameterfvEXT");
	if(!TestPointer(glPointParameterfvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPOLYGONOFFSETEXTPROC)(GLfloat factor, GLfloat bias);

PFNGLPOLYGONOFFSETEXTPROC glPolygonOffsetEXT;

static int gleIntLoad_EXT_polygon_offset()
{
	int bIsLoaded = 1;
	glPolygonOffsetEXT = (PFNGLPOLYGONOFFSETEXTPROC)gleIntGetProcAddress("glPolygonOffsetEXT");
	if(!TestPointer(glPolygonOffsetEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPROVOKINGVERTEXEXTPROC)(GLenum mode);

PFNGLPROVOKINGVERTEXEXTPROC glProvokingVertexEXT;

static int gleIntLoad_EXT_provoking_vertex()
{
	int bIsLoaded = 1;
	glProvokingVertexEXT = (PFNGLPROVOKINGVERTEXEXTPROC)gleIntGetProcAddress("glProvokingVertexEXT");
	if(!TestPointer(glProvokingVertexEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLSECONDARYCOLOR3BEXTPROC glSecondaryColor3bEXT;
PFNGLSECONDARYCOLOR3BVEXTPROC glSecondaryColor3bvEXT;
PFNGLSECONDARYCOLOR3DEXTPROC glSecondaryColor3dEXT;
PFNGLSECONDARYCOLOR3DVEXTPROC glSecondaryColor3dvEXT;
PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT;
PFNGLSECONDARYCOLOR3FVEXTPROC glSecondaryColor3fvEXT;
PFNGLSECONDARYCOLOR3IEXTPROC glSecondaryColor3iEXT;
PFNGLSECONDARYCOLOR3IVEXTPROC glSecondaryColor3ivEXT;
PFNGLSECONDARYCOLOR3SEXTPROC glSecondaryColor3sEXT;
PFNGLSECONDARYCOLOR3SVEXTPROC glSecondaryColor3svEXT;
PFNGLSECONDARYCOLOR3UBEXTPROC glSecondaryColor3ubEXT;
PFNGLSECONDARYCOLOR3UBVEXTPROC glSecondaryColor3ubvEXT;
PFNGLSECONDARYCOLOR3UIEXTPROC glSecondaryColor3uiEXT;
PFNGLSECONDARYCOLOR3UIVEXTPROC glSecondaryColor3uivEXT;
PFNGLSECONDARYCOLOR3USEXTPROC glSecondaryColor3usEXT;
PFNGLSECONDARYCOLOR3USVEXTPROC glSecondaryColor3usvEXT;
PFNGLSECONDARYCOLORPOINTEREXTPROC glSecondaryColorPointerEXT;

static int gleIntLoad_EXT_secondary_color()
{
	int bIsLoaded = 1;
	glSecondaryColor3bEXT = (PFNGLSECONDARYCOLOR3BEXTPROC)gleIntGetProcAddress("glSecondaryColor3bEXT");
	if(!TestPointer(glSecondaryColor3bEXT)) bIsLoaded = 0;
	glSecondaryColor3bvEXT = (PFNGLSECONDARYCOLOR3BVEXTPROC)gleIntGetProcAddress("glSecondaryColor3bvEXT");
	if(!TestPointer(glSecondaryColor3bvEXT)) bIsLoaded = 0;
	glSecondaryColor3dEXT = (PFNGLSECONDARYCOLOR3DEXTPROC)gleIntGetProcAddress("glSecondaryColor3dEXT");
	if(!TestPointer(glSecondaryColor3dEXT)) bIsLoaded = 0;
	glSecondaryColor3dvEXT = (PFNGLSECONDARYCOLOR3DVEXTPROC)gleIntGetProcAddress("glSecondaryColor3dvEXT");
	if(!TestPointer(glSecondaryColor3dvEXT)) bIsLoaded = 0;
	glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC)gleIntGetProcAddress("glSecondaryColor3fEXT");
	if(!TestPointer(glSecondaryColor3fEXT)) bIsLoaded = 0;
	glSecondaryColor3fvEXT = (PFNGLSECONDARYCOLOR3FVEXTPROC)gleIntGetProcAddress("glSecondaryColor3fvEXT");
	if(!TestPointer(glSecondaryColor3fvEXT)) bIsLoaded = 0;
	glSecondaryColor3iEXT = (PFNGLSECONDARYCOLOR3IEXTPROC)gleIntGetProcAddress("glSecondaryColor3iEXT");
	if(!TestPointer(glSecondaryColor3iEXT)) bIsLoaded = 0;
	glSecondaryColor3ivEXT = (PFNGLSECONDARYCOLOR3IVEXTPROC)gleIntGetProcAddress("glSecondaryColor3ivEXT");
	if(!TestPointer(glSecondaryColor3ivEXT)) bIsLoaded = 0;
	glSecondaryColor3sEXT = (PFNGLSECONDARYCOLOR3SEXTPROC)gleIntGetProcAddress("glSecondaryColor3sEXT");
	if(!TestPointer(glSecondaryColor3sEXT)) bIsLoaded = 0;
	glSecondaryColor3svEXT = (PFNGLSECONDARYCOLOR3SVEXTPROC)gleIntGetProcAddress("glSecondaryColor3svEXT");
	if(!TestPointer(glSecondaryColor3svEXT)) bIsLoaded = 0;
	glSecondaryColor3ubEXT = (PFNGLSECONDARYCOLOR3UBEXTPROC)gleIntGetProcAddress("glSecondaryColor3ubEXT");
	if(!TestPointer(glSecondaryColor3ubEXT)) bIsLoaded = 0;
	glSecondaryColor3ubvEXT = (PFNGLSECONDARYCOLOR3UBVEXTPROC)gleIntGetProcAddress("glSecondaryColor3ubvEXT");
	if(!TestPointer(glSecondaryColor3ubvEXT)) bIsLoaded = 0;
	glSecondaryColor3uiEXT = (PFNGLSECONDARYCOLOR3UIEXTPROC)gleIntGetProcAddress("glSecondaryColor3uiEXT");
	if(!TestPointer(glSecondaryColor3uiEXT)) bIsLoaded = 0;
	glSecondaryColor3uivEXT = (PFNGLSECONDARYCOLOR3UIVEXTPROC)gleIntGetProcAddress("glSecondaryColor3uivEXT");
	if(!TestPointer(glSecondaryColor3uivEXT)) bIsLoaded = 0;
	glSecondaryColor3usEXT = (PFNGLSECONDARYCOLOR3USEXTPROC)gleIntGetProcAddress("glSecondaryColor3usEXT");
	if(!TestPointer(glSecondaryColor3usEXT)) bIsLoaded = 0;
	glSecondaryColor3usvEXT = (PFNGLSECONDARYCOLOR3USVEXTPROC)gleIntGetProcAddress("glSecondaryColor3usvEXT");
	if(!TestPointer(glSecondaryColor3usvEXT)) bIsLoaded = 0;
	glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC)gleIntGetProcAddress("glSecondaryColorPointerEXT");
	if(!TestPointer(glSecondaryColorPointerEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLUSESHADERPROGRAMEXTPROC)(GLenum type, GLuint program);
typedef void (GLE_FUNCPTR * PFNGLACTIVEPROGRAMEXTPROC)(GLuint program);
typedef GLuint (GLE_FUNCPTR * PFNGLCREATESHADERPROGRAMEXTPROC)(GLenum type, const GLchar *string);

PFNGLUSESHADERPROGRAMEXTPROC glUseShaderProgramEXT;
PFNGLACTIVEPROGRAMEXTPROC glActiveProgramEXT;
PFNGLCREATESHADERPROGRAMEXTPROC glCreateShaderProgramEXT;

static int gleIntLoad_EXT_separate_shader_objects()
{
	int bIsLoaded = 1;
	glUseShaderProgramEXT = (PFNGLUSESHADERPROGRAMEXTPROC)gleIntGetProcAddress("glUseShaderProgramEXT");
	if(!TestPointer(glUseShaderProgramEXT)) bIsLoaded = 0;
	glActiveProgramEXT = (PFNGLACTIVEPROGRAMEXTPROC)gleIntGetProcAddress("glActiveProgramEXT");
	if(!TestPointer(glActiveProgramEXT)) bIsLoaded = 0;
	glCreateShaderProgramEXT = (PFNGLCREATESHADERPROGRAMEXTPROC)gleIntGetProcAddress("glCreateShaderProgramEXT");
	if(!TestPointer(glCreateShaderProgramEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLBINDIMAGETEXTUREEXTPROC)(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format);
typedef void (GLE_FUNCPTR * PFNGLMEMORYBARRIEREXTPROC)(GLbitfield barriers);

PFNGLBINDIMAGETEXTUREEXTPROC glBindImageTextureEXT;
PFNGLMEMORYBARRIEREXTPROC glMemoryBarrierEXT;

static int gleIntLoad_EXT_shader_image_load_store()
{
	int bIsLoaded = 1;
	glBindImageTextureEXT = (PFNGLBINDIMAGETEXTUREEXTPROC)gleIntGetProcAddress("glBindImageTextureEXT");
	if(!TestPointer(glBindImageTextureEXT)) bIsLoaded = 0;
	glMemoryBarrierEXT = (PFNGLMEMORYBARRIEREXTPROC)gleIntGetProcAddress("glMemoryBarrierEXT");
	if(!TestPointer(glMemoryBarrierEXT)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLSTENCILCLEARTAGEXTPROC)(GLsizei stencilTagBits, GLuint stencilClearTag);

PFNGLSTENCILCLEARTAGEXTPROC glStencilClearTagEXT;

static int gleIntLoad_EXT_stencil_clear_tag()
{
	int bIsLoaded = 1;
	glStencilClearTagEXT = (PFNGLSTENCILCLEARTAGEXTPROC)gleIntGetProcAddress("glStencilClearTagEXT");
	if(!TestPointer(glStencilClearTagEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLACTIVESTENCILFACEEXTPROC)(GLenum face);

PFNGLACTIVESTENCILFACEEXTPROC glActiveStencilFaceEXT;

static int gleIntLoad_EXT_stencil_two_side()
{
	int bIsLoaded = 1;
	glActiveStencilFaceEXT = (PFNGLACTIVESTENCILFACEEXTPROC)gleIntGetProcAddress("glActiveStencilFaceEXT");
	if(!TestPointer(glActiveStencilFaceEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE1DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE2DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);

PFNGLTEXSUBIMAGE1DEXTPROC glTexSubImage1DEXT;
PFNGLTEXSUBIMAGE2DEXTPROC glTexSubImage2DEXT;

static int gleIntLoad_EXT_subtexture()
{
	int bIsLoaded = 1;
	glTexSubImage1DEXT = (PFNGLTEXSUBIMAGE1DEXTPROC)gleIntGetProcAddress("glTexSubImage1DEXT");
	if(!TestPointer(glTexSubImage1DEXT)) bIsLoaded = 0;
	glTexSubImage2DEXT = (PFNGLTEXSUBIMAGE2DEXTPROC)gleIntGetProcAddress("glTexSubImage2DEXT");
	if(!TestPointer(glTexSubImage2DEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DEXTPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE3DEXTPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);

PFNGLTEXIMAGE3DEXTPROC glTexImage3DEXT;
PFNGLTEXSUBIMAGE3DEXTPROC glTexSubImage3DEXT;

static int gleIntLoad_EXT_texture3D()
{
	int bIsLoaded = 1;
	glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC)gleIntGetProcAddress("glTexImage3DEXT");
	if(!TestPointer(glTexImage3DEXT)) bIsLoaded = 0;
	glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC)gleIntGetProcAddress("glTexSubImage3DEXT");
	if(!TestPointer(glTexSubImage3DEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTEXBUFFEREXTPROC)(GLenum target, GLenum internalformat, GLuint buffer);

PFNGLTEXBUFFEREXTPROC glTexBufferEXT;

static int gleIntLoad_EXT_texture_buffer_object()
{
	int bIsLoaded = 1;
	glTexBufferEXT = (PFNGLTEXBUFFEREXTPROC)gleIntGetProcAddress("glTexBufferEXT");
	if(!TestPointer(glTexBufferEXT)) bIsLoaded = 0;
	return bIsLoaded;
}








typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIIVEXTPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIUIVEXTPROC)(GLenum target, GLenum pname, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIUIVEXTPROC)(GLenum target, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORIIEXTPROC)(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORIUIEXTPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);

PFNGLTEXPARAMETERIIVEXTPROC glTexParameterIivEXT;
PFNGLTEXPARAMETERIUIVEXTPROC glTexParameterIuivEXT;
PFNGLGETTEXPARAMETERIIVEXTPROC glGetTexParameterIivEXT;
PFNGLGETTEXPARAMETERIUIVEXTPROC glGetTexParameterIuivEXT;
PFNGLCLEARCOLORIIEXTPROC glClearColorIiEXT;
PFNGLCLEARCOLORIUIEXTPROC glClearColorIuiEXT;

static int gleIntLoad_EXT_texture_integer()
{
	int bIsLoaded = 1;
	glTexParameterIivEXT = (PFNGLTEXPARAMETERIIVEXTPROC)gleIntGetProcAddress("glTexParameterIivEXT");
	if(!TestPointer(glTexParameterIivEXT)) bIsLoaded = 0;
	glTexParameterIuivEXT = (PFNGLTEXPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glTexParameterIuivEXT");
	if(!TestPointer(glTexParameterIuivEXT)) bIsLoaded = 0;
	glGetTexParameterIivEXT = (PFNGLGETTEXPARAMETERIIVEXTPROC)gleIntGetProcAddress("glGetTexParameterIivEXT");
	if(!TestPointer(glGetTexParameterIivEXT)) bIsLoaded = 0;
	glGetTexParameterIuivEXT = (PFNGLGETTEXPARAMETERIUIVEXTPROC)gleIntGetProcAddress("glGetTexParameterIuivEXT");
	if(!TestPointer(glGetTexParameterIuivEXT)) bIsLoaded = 0;
	glClearColorIiEXT = (PFNGLCLEARCOLORIIEXTPROC)gleIntGetProcAddress("glClearColorIiEXT");
	if(!TestPointer(glClearColorIiEXT)) bIsLoaded = 0;
	glClearColorIuiEXT = (PFNGLCLEARCOLORIUIEXTPROC)gleIntGetProcAddress("glClearColorIuiEXT");
	if(!TestPointer(glClearColorIuiEXT)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef GLboolean (GLE_FUNCPTR * PFNGLARETEXTURESRESIDENTEXTPROC)(GLsizei n, const GLuint *textures, GLboolean *residences);
typedef void (GLE_FUNCPTR * PFNGLBINDTEXTUREEXTPROC)(GLenum target, GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLDELETETEXTURESEXTPROC)(GLsizei n, const GLuint *textures);
typedef void (GLE_FUNCPTR * PFNGLGENTEXTURESEXTPROC)(GLsizei n, GLuint *textures);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTEXTUREEXTPROC)(GLuint texture);
typedef void (GLE_FUNCPTR * PFNGLPRIORITIZETEXTURESEXTPROC)(GLsizei n, const GLuint *textures, const GLclampf *priorities);

PFNGLARETEXTURESRESIDENTEXTPROC glAreTexturesResidentEXT;
PFNGLBINDTEXTUREEXTPROC glBindTextureEXT;
PFNGLDELETETEXTURESEXTPROC glDeleteTexturesEXT;
PFNGLGENTEXTURESEXTPROC glGenTexturesEXT;
PFNGLISTEXTUREEXTPROC glIsTextureEXT;
PFNGLPRIORITIZETEXTURESEXTPROC glPrioritizeTexturesEXT;

static int gleIntLoad_EXT_texture_object()
{
	int bIsLoaded = 1;
	glAreTexturesResidentEXT = (PFNGLARETEXTURESRESIDENTEXTPROC)gleIntGetProcAddress("glAreTexturesResidentEXT");
	if(!TestPointer(glAreTexturesResidentEXT)) bIsLoaded = 0;
	glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)gleIntGetProcAddress("glBindTextureEXT");
	if(!TestPointer(glBindTextureEXT)) bIsLoaded = 0;
	glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC)gleIntGetProcAddress("glDeleteTexturesEXT");
	if(!TestPointer(glDeleteTexturesEXT)) bIsLoaded = 0;
	glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)gleIntGetProcAddress("glGenTexturesEXT");
	if(!TestPointer(glGenTexturesEXT)) bIsLoaded = 0;
	glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)gleIntGetProcAddress("glIsTextureEXT");
	if(!TestPointer(glIsTextureEXT)) bIsLoaded = 0;
	glPrioritizeTexturesEXT = (PFNGLPRIORITIZETEXTURESEXTPROC)gleIntGetProcAddress("glPrioritizeTexturesEXT");
	if(!TestPointer(glPrioritizeTexturesEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLTEXTURENORMALEXTPROC)(GLenum mode);

PFNGLTEXTURENORMALEXTPROC glTextureNormalEXT;

static int gleIntLoad_EXT_texture_perturb_normal()
{
	int bIsLoaded = 1;
	glTextureNormalEXT = (PFNGLTEXTURENORMALEXTPROC)gleIntGetProcAddress("glTextureNormalEXT");
	if(!TestPointer(glTextureNormalEXT)) bIsLoaded = 0;
	return bIsLoaded;
}




typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTI64VEXTPROC)(GLuint id, GLenum pname, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUI64VEXTPROC)(GLuint id, GLenum pname, GLuint64EXT *params);

PFNGLGETQUERYOBJECTI64VEXTPROC glGetQueryObjecti64vEXT;
PFNGLGETQUERYOBJECTUI64VEXTPROC glGetQueryObjectui64vEXT;

static int gleIntLoad_EXT_timer_query()
{
	int bIsLoaded = 1;
	glGetQueryObjecti64vEXT = (PFNGLGETQUERYOBJECTI64VEXTPROC)gleIntGetProcAddress("glGetQueryObjecti64vEXT");
	if(!TestPointer(glGetQueryObjecti64vEXT)) bIsLoaded = 0;
	glGetQueryObjectui64vEXT = (PFNGLGETQUERYOBJECTUI64VEXTPROC)gleIntGetProcAddress("glGetQueryObjectui64vEXT");
	if(!TestPointer(glGetQueryObjectui64vEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)(GLenum primitiveMode);
typedef void (GLE_FUNCPTR * PFNGLENDTRANSFORMFEEDBACKEXTPROC)();
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERRANGEEXTPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFEROFFSETEXTPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset);
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERBASEEXTPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)(GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode);
typedef void (GLE_FUNCPTR * PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);

PFNGLBEGINTRANSFORMFEEDBACKEXTPROC glBeginTransformFeedbackEXT;
PFNGLENDTRANSFORMFEEDBACKEXTPROC glEndTransformFeedbackEXT;
PFNGLBINDBUFFERRANGEEXTPROC glBindBufferRangeEXT;
PFNGLBINDBUFFEROFFSETEXTPROC glBindBufferOffsetEXT;
PFNGLBINDBUFFERBASEEXTPROC glBindBufferBaseEXT;
PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC glTransformFeedbackVaryingsEXT;
PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC glGetTransformFeedbackVaryingEXT;

static int gleIntLoad_EXT_transform_feedback()
{
	int bIsLoaded = 1;
	glBeginTransformFeedbackEXT = (PFNGLBEGINTRANSFORMFEEDBACKEXTPROC)gleIntGetProcAddress("glBeginTransformFeedbackEXT");
	if(!TestPointer(glBeginTransformFeedbackEXT)) bIsLoaded = 0;
	glEndTransformFeedbackEXT = (PFNGLENDTRANSFORMFEEDBACKEXTPROC)gleIntGetProcAddress("glEndTransformFeedbackEXT");
	if(!TestPointer(glEndTransformFeedbackEXT)) bIsLoaded = 0;
	glBindBufferRangeEXT = (PFNGLBINDBUFFERRANGEEXTPROC)gleIntGetProcAddress("glBindBufferRangeEXT");
	if(!TestPointer(glBindBufferRangeEXT)) bIsLoaded = 0;
	glBindBufferOffsetEXT = (PFNGLBINDBUFFEROFFSETEXTPROC)gleIntGetProcAddress("glBindBufferOffsetEXT");
	if(!TestPointer(glBindBufferOffsetEXT)) bIsLoaded = 0;
	glBindBufferBaseEXT = (PFNGLBINDBUFFERBASEEXTPROC)gleIntGetProcAddress("glBindBufferBaseEXT");
	if(!TestPointer(glBindBufferBaseEXT)) bIsLoaded = 0;
	glTransformFeedbackVaryingsEXT = (PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC)gleIntGetProcAddress("glTransformFeedbackVaryingsEXT");
	if(!TestPointer(glTransformFeedbackVaryingsEXT)) bIsLoaded = 0;
	glGetTransformFeedbackVaryingEXT = (PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC)gleIntGetProcAddress("glGetTransformFeedbackVaryingEXT");
	if(!TestPointer(glGetTransformFeedbackVaryingEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLARRAYELEMENTEXTPROC)(GLint i);
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSEXTPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTEREXTPROC)(GLsizei stride, GLsizei count, const GLboolean *pointer);
typedef void (GLE_FUNCPTR * PFNGLGETPOINTERVEXTPROC)(GLenum pname, GLvoid* *params);
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTEREXTPROC)(GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTEREXTPROC)(GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTEREXTPROC)(GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);

PFNGLARRAYELEMENTEXTPROC glArrayElementEXT;
PFNGLCOLORPOINTEREXTPROC glColorPointerEXT;
PFNGLDRAWARRAYSEXTPROC glDrawArraysEXT;
PFNGLEDGEFLAGPOINTEREXTPROC glEdgeFlagPointerEXT;
PFNGLGETPOINTERVEXTPROC glGetPointervEXT;
PFNGLINDEXPOINTEREXTPROC glIndexPointerEXT;
PFNGLNORMALPOINTEREXTPROC glNormalPointerEXT;
PFNGLTEXCOORDPOINTEREXTPROC glTexCoordPointerEXT;
PFNGLVERTEXPOINTEREXTPROC glVertexPointerEXT;

static int gleIntLoad_EXT_vertex_array()
{
	int bIsLoaded = 1;
	glArrayElementEXT = (PFNGLARRAYELEMENTEXTPROC)gleIntGetProcAddress("glArrayElementEXT");
	if(!TestPointer(glArrayElementEXT)) bIsLoaded = 0;
	glColorPointerEXT = (PFNGLCOLORPOINTEREXTPROC)gleIntGetProcAddress("glColorPointerEXT");
	if(!TestPointer(glColorPointerEXT)) bIsLoaded = 0;
	glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC)gleIntGetProcAddress("glDrawArraysEXT");
	if(!TestPointer(glDrawArraysEXT)) bIsLoaded = 0;
	glEdgeFlagPointerEXT = (PFNGLEDGEFLAGPOINTEREXTPROC)gleIntGetProcAddress("glEdgeFlagPointerEXT");
	if(!TestPointer(glEdgeFlagPointerEXT)) bIsLoaded = 0;
	glGetPointervEXT = (PFNGLGETPOINTERVEXTPROC)gleIntGetProcAddress("glGetPointervEXT");
	if(!TestPointer(glGetPointervEXT)) bIsLoaded = 0;
	glIndexPointerEXT = (PFNGLINDEXPOINTEREXTPROC)gleIntGetProcAddress("glIndexPointerEXT");
	if(!TestPointer(glIndexPointerEXT)) bIsLoaded = 0;
	glNormalPointerEXT = (PFNGLNORMALPOINTEREXTPROC)gleIntGetProcAddress("glNormalPointerEXT");
	if(!TestPointer(glNormalPointerEXT)) bIsLoaded = 0;
	glTexCoordPointerEXT = (PFNGLTEXCOORDPOINTEREXTPROC)gleIntGetProcAddress("glTexCoordPointerEXT");
	if(!TestPointer(glTexCoordPointerEXT)) bIsLoaded = 0;
	glVertexPointerEXT = (PFNGLVERTEXPOINTEREXTPROC)gleIntGetProcAddress("glVertexPointerEXT");
	if(!TestPointer(glVertexPointerEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLVERTEXATTRIBL1DEXTPROC glVertexAttribL1dEXT;
PFNGLVERTEXATTRIBL2DEXTPROC glVertexAttribL2dEXT;
PFNGLVERTEXATTRIBL3DEXTPROC glVertexAttribL3dEXT;
PFNGLVERTEXATTRIBL4DEXTPROC glVertexAttribL4dEXT;
PFNGLVERTEXATTRIBL1DVEXTPROC glVertexAttribL1dvEXT;
PFNGLVERTEXATTRIBL2DVEXTPROC glVertexAttribL2dvEXT;
PFNGLVERTEXATTRIBL3DVEXTPROC glVertexAttribL3dvEXT;
PFNGLVERTEXATTRIBL4DVEXTPROC glVertexAttribL4dvEXT;
PFNGLVERTEXATTRIBLPOINTEREXTPROC glVertexAttribLPointerEXT;
PFNGLGETVERTEXATTRIBLDVEXTPROC glGetVertexAttribLdvEXT;
PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC glVertexArrayVertexAttribLOffsetEXT;

static int gleIntLoad_EXT_vertex_attrib_64bit()
{
	int bIsLoaded = 1;
	glVertexAttribL1dEXT = (PFNGLVERTEXATTRIBL1DEXTPROC)gleIntGetProcAddress("glVertexAttribL1dEXT");
	if(!TestPointer(glVertexAttribL1dEXT)) bIsLoaded = 0;
	glVertexAttribL2dEXT = (PFNGLVERTEXATTRIBL2DEXTPROC)gleIntGetProcAddress("glVertexAttribL2dEXT");
	if(!TestPointer(glVertexAttribL2dEXT)) bIsLoaded = 0;
	glVertexAttribL3dEXT = (PFNGLVERTEXATTRIBL3DEXTPROC)gleIntGetProcAddress("glVertexAttribL3dEXT");
	if(!TestPointer(glVertexAttribL3dEXT)) bIsLoaded = 0;
	glVertexAttribL4dEXT = (PFNGLVERTEXATTRIBL4DEXTPROC)gleIntGetProcAddress("glVertexAttribL4dEXT");
	if(!TestPointer(glVertexAttribL4dEXT)) bIsLoaded = 0;
	glVertexAttribL1dvEXT = (PFNGLVERTEXATTRIBL1DVEXTPROC)gleIntGetProcAddress("glVertexAttribL1dvEXT");
	if(!TestPointer(glVertexAttribL1dvEXT)) bIsLoaded = 0;
	glVertexAttribL2dvEXT = (PFNGLVERTEXATTRIBL2DVEXTPROC)gleIntGetProcAddress("glVertexAttribL2dvEXT");
	if(!TestPointer(glVertexAttribL2dvEXT)) bIsLoaded = 0;
	glVertexAttribL3dvEXT = (PFNGLVERTEXATTRIBL3DVEXTPROC)gleIntGetProcAddress("glVertexAttribL3dvEXT");
	if(!TestPointer(glVertexAttribL3dvEXT)) bIsLoaded = 0;
	glVertexAttribL4dvEXT = (PFNGLVERTEXATTRIBL4DVEXTPROC)gleIntGetProcAddress("glVertexAttribL4dvEXT");
	if(!TestPointer(glVertexAttribL4dvEXT)) bIsLoaded = 0;
	glVertexAttribLPointerEXT = (PFNGLVERTEXATTRIBLPOINTEREXTPROC)gleIntGetProcAddress("glVertexAttribLPointerEXT");
	if(!TestPointer(glVertexAttribLPointerEXT)) bIsLoaded = 0;
	glGetVertexAttribLdvEXT = (PFNGLGETVERTEXATTRIBLDVEXTPROC)gleIntGetProcAddress("glGetVertexAttribLdvEXT");
	if(!TestPointer(glGetVertexAttribLdvEXT)) bIsLoaded = 0;
	glVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)gleIntGetProcAddress("glVertexArrayVertexAttribLOffsetEXT");
	if(!TestPointer(glVertexArrayVertexAttribLOffsetEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLBEGINVERTEXSHADEREXTPROC glBeginVertexShaderEXT;
PFNGLENDVERTEXSHADEREXTPROC glEndVertexShaderEXT;
PFNGLBINDVERTEXSHADEREXTPROC glBindVertexShaderEXT;
PFNGLGENVERTEXSHADERSEXTPROC glGenVertexShadersEXT;
PFNGLDELETEVERTEXSHADEREXTPROC glDeleteVertexShaderEXT;
PFNGLSHADEROP1EXTPROC glShaderOp1EXT;
PFNGLSHADEROP2EXTPROC glShaderOp2EXT;
PFNGLSHADEROP3EXTPROC glShaderOp3EXT;
PFNGLSWIZZLEEXTPROC glSwizzleEXT;
PFNGLWRITEMASKEXTPROC glWriteMaskEXT;
PFNGLINSERTCOMPONENTEXTPROC glInsertComponentEXT;
PFNGLEXTRACTCOMPONENTEXTPROC glExtractComponentEXT;
PFNGLGENSYMBOLSEXTPROC glGenSymbolsEXT;
PFNGLSETINVARIANTEXTPROC glSetInvariantEXT;
PFNGLSETLOCALCONSTANTEXTPROC glSetLocalConstantEXT;
PFNGLVARIANTBVEXTPROC glVariantbvEXT;
PFNGLVARIANTSVEXTPROC glVariantsvEXT;
PFNGLVARIANTIVEXTPROC glVariantivEXT;
PFNGLVARIANTFVEXTPROC glVariantfvEXT;
PFNGLVARIANTDVEXTPROC glVariantdvEXT;
PFNGLVARIANTUBVEXTPROC glVariantubvEXT;
PFNGLVARIANTUSVEXTPROC glVariantusvEXT;
PFNGLVARIANTUIVEXTPROC glVariantuivEXT;
PFNGLVARIANTPOINTEREXTPROC glVariantPointerEXT;
PFNGLENABLEVARIANTCLIENTSTATEEXTPROC glEnableVariantClientStateEXT;
PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC glDisableVariantClientStateEXT;
PFNGLBINDLIGHTPARAMETEREXTPROC glBindLightParameterEXT;
PFNGLBINDMATERIALPARAMETEREXTPROC glBindMaterialParameterEXT;
PFNGLBINDTEXGENPARAMETEREXTPROC glBindTexGenParameterEXT;
PFNGLBINDTEXTUREUNITPARAMETEREXTPROC glBindTextureUnitParameterEXT;
PFNGLBINDPARAMETEREXTPROC glBindParameterEXT;
PFNGLISVARIANTENABLEDEXTPROC glIsVariantEnabledEXT;
PFNGLGETVARIANTBOOLEANVEXTPROC glGetVariantBooleanvEXT;
PFNGLGETVARIANTINTEGERVEXTPROC glGetVariantIntegervEXT;
PFNGLGETVARIANTFLOATVEXTPROC glGetVariantFloatvEXT;
PFNGLGETVARIANTPOINTERVEXTPROC glGetVariantPointervEXT;
PFNGLGETINVARIANTBOOLEANVEXTPROC glGetInvariantBooleanvEXT;
PFNGLGETINVARIANTINTEGERVEXTPROC glGetInvariantIntegervEXT;
PFNGLGETINVARIANTFLOATVEXTPROC glGetInvariantFloatvEXT;
PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC glGetLocalConstantBooleanvEXT;
PFNGLGETLOCALCONSTANTINTEGERVEXTPROC glGetLocalConstantIntegervEXT;
PFNGLGETLOCALCONSTANTFLOATVEXTPROC glGetLocalConstantFloatvEXT;

static int gleIntLoad_EXT_vertex_shader()
{
	int bIsLoaded = 1;
	glBeginVertexShaderEXT = (PFNGLBEGINVERTEXSHADEREXTPROC)gleIntGetProcAddress("glBeginVertexShaderEXT");
	if(!TestPointer(glBeginVertexShaderEXT)) bIsLoaded = 0;
	glEndVertexShaderEXT = (PFNGLENDVERTEXSHADEREXTPROC)gleIntGetProcAddress("glEndVertexShaderEXT");
	if(!TestPointer(glEndVertexShaderEXT)) bIsLoaded = 0;
	glBindVertexShaderEXT = (PFNGLBINDVERTEXSHADEREXTPROC)gleIntGetProcAddress("glBindVertexShaderEXT");
	if(!TestPointer(glBindVertexShaderEXT)) bIsLoaded = 0;
	glGenVertexShadersEXT = (PFNGLGENVERTEXSHADERSEXTPROC)gleIntGetProcAddress("glGenVertexShadersEXT");
	if(!TestPointer(glGenVertexShadersEXT)) bIsLoaded = 0;
	glDeleteVertexShaderEXT = (PFNGLDELETEVERTEXSHADEREXTPROC)gleIntGetProcAddress("glDeleteVertexShaderEXT");
	if(!TestPointer(glDeleteVertexShaderEXT)) bIsLoaded = 0;
	glShaderOp1EXT = (PFNGLSHADEROP1EXTPROC)gleIntGetProcAddress("glShaderOp1EXT");
	if(!TestPointer(glShaderOp1EXT)) bIsLoaded = 0;
	glShaderOp2EXT = (PFNGLSHADEROP2EXTPROC)gleIntGetProcAddress("glShaderOp2EXT");
	if(!TestPointer(glShaderOp2EXT)) bIsLoaded = 0;
	glShaderOp3EXT = (PFNGLSHADEROP3EXTPROC)gleIntGetProcAddress("glShaderOp3EXT");
	if(!TestPointer(glShaderOp3EXT)) bIsLoaded = 0;
	glSwizzleEXT = (PFNGLSWIZZLEEXTPROC)gleIntGetProcAddress("glSwizzleEXT");
	if(!TestPointer(glSwizzleEXT)) bIsLoaded = 0;
	glWriteMaskEXT = (PFNGLWRITEMASKEXTPROC)gleIntGetProcAddress("glWriteMaskEXT");
	if(!TestPointer(glWriteMaskEXT)) bIsLoaded = 0;
	glInsertComponentEXT = (PFNGLINSERTCOMPONENTEXTPROC)gleIntGetProcAddress("glInsertComponentEXT");
	if(!TestPointer(glInsertComponentEXT)) bIsLoaded = 0;
	glExtractComponentEXT = (PFNGLEXTRACTCOMPONENTEXTPROC)gleIntGetProcAddress("glExtractComponentEXT");
	if(!TestPointer(glExtractComponentEXT)) bIsLoaded = 0;
	glGenSymbolsEXT = (PFNGLGENSYMBOLSEXTPROC)gleIntGetProcAddress("glGenSymbolsEXT");
	if(!TestPointer(glGenSymbolsEXT)) bIsLoaded = 0;
	glSetInvariantEXT = (PFNGLSETINVARIANTEXTPROC)gleIntGetProcAddress("glSetInvariantEXT");
	if(!TestPointer(glSetInvariantEXT)) bIsLoaded = 0;
	glSetLocalConstantEXT = (PFNGLSETLOCALCONSTANTEXTPROC)gleIntGetProcAddress("glSetLocalConstantEXT");
	if(!TestPointer(glSetLocalConstantEXT)) bIsLoaded = 0;
	glVariantbvEXT = (PFNGLVARIANTBVEXTPROC)gleIntGetProcAddress("glVariantbvEXT");
	if(!TestPointer(glVariantbvEXT)) bIsLoaded = 0;
	glVariantsvEXT = (PFNGLVARIANTSVEXTPROC)gleIntGetProcAddress("glVariantsvEXT");
	if(!TestPointer(glVariantsvEXT)) bIsLoaded = 0;
	glVariantivEXT = (PFNGLVARIANTIVEXTPROC)gleIntGetProcAddress("glVariantivEXT");
	if(!TestPointer(glVariantivEXT)) bIsLoaded = 0;
	glVariantfvEXT = (PFNGLVARIANTFVEXTPROC)gleIntGetProcAddress("glVariantfvEXT");
	if(!TestPointer(glVariantfvEXT)) bIsLoaded = 0;
	glVariantdvEXT = (PFNGLVARIANTDVEXTPROC)gleIntGetProcAddress("glVariantdvEXT");
	if(!TestPointer(glVariantdvEXT)) bIsLoaded = 0;
	glVariantubvEXT = (PFNGLVARIANTUBVEXTPROC)gleIntGetProcAddress("glVariantubvEXT");
	if(!TestPointer(glVariantubvEXT)) bIsLoaded = 0;
	glVariantusvEXT = (PFNGLVARIANTUSVEXTPROC)gleIntGetProcAddress("glVariantusvEXT");
	if(!TestPointer(glVariantusvEXT)) bIsLoaded = 0;
	glVariantuivEXT = (PFNGLVARIANTUIVEXTPROC)gleIntGetProcAddress("glVariantuivEXT");
	if(!TestPointer(glVariantuivEXT)) bIsLoaded = 0;
	glVariantPointerEXT = (PFNGLVARIANTPOINTEREXTPROC)gleIntGetProcAddress("glVariantPointerEXT");
	if(!TestPointer(glVariantPointerEXT)) bIsLoaded = 0;
	glEnableVariantClientStateEXT = (PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)gleIntGetProcAddress("glEnableVariantClientStateEXT");
	if(!TestPointer(glEnableVariantClientStateEXT)) bIsLoaded = 0;
	glDisableVariantClientStateEXT = (PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)gleIntGetProcAddress("glDisableVariantClientStateEXT");
	if(!TestPointer(glDisableVariantClientStateEXT)) bIsLoaded = 0;
	glBindLightParameterEXT = (PFNGLBINDLIGHTPARAMETEREXTPROC)gleIntGetProcAddress("glBindLightParameterEXT");
	if(!TestPointer(glBindLightParameterEXT)) bIsLoaded = 0;
	glBindMaterialParameterEXT = (PFNGLBINDMATERIALPARAMETEREXTPROC)gleIntGetProcAddress("glBindMaterialParameterEXT");
	if(!TestPointer(glBindMaterialParameterEXT)) bIsLoaded = 0;
	glBindTexGenParameterEXT = (PFNGLBINDTEXGENPARAMETEREXTPROC)gleIntGetProcAddress("glBindTexGenParameterEXT");
	if(!TestPointer(glBindTexGenParameterEXT)) bIsLoaded = 0;
	glBindTextureUnitParameterEXT = (PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)gleIntGetProcAddress("glBindTextureUnitParameterEXT");
	if(!TestPointer(glBindTextureUnitParameterEXT)) bIsLoaded = 0;
	glBindParameterEXT = (PFNGLBINDPARAMETEREXTPROC)gleIntGetProcAddress("glBindParameterEXT");
	if(!TestPointer(glBindParameterEXT)) bIsLoaded = 0;
	glIsVariantEnabledEXT = (PFNGLISVARIANTENABLEDEXTPROC)gleIntGetProcAddress("glIsVariantEnabledEXT");
	if(!TestPointer(glIsVariantEnabledEXT)) bIsLoaded = 0;
	glGetVariantBooleanvEXT = (PFNGLGETVARIANTBOOLEANVEXTPROC)gleIntGetProcAddress("glGetVariantBooleanvEXT");
	if(!TestPointer(glGetVariantBooleanvEXT)) bIsLoaded = 0;
	glGetVariantIntegervEXT = (PFNGLGETVARIANTINTEGERVEXTPROC)gleIntGetProcAddress("glGetVariantIntegervEXT");
	if(!TestPointer(glGetVariantIntegervEXT)) bIsLoaded = 0;
	glGetVariantFloatvEXT = (PFNGLGETVARIANTFLOATVEXTPROC)gleIntGetProcAddress("glGetVariantFloatvEXT");
	if(!TestPointer(glGetVariantFloatvEXT)) bIsLoaded = 0;
	glGetVariantPointervEXT = (PFNGLGETVARIANTPOINTERVEXTPROC)gleIntGetProcAddress("glGetVariantPointervEXT");
	if(!TestPointer(glGetVariantPointervEXT)) bIsLoaded = 0;
	glGetInvariantBooleanvEXT = (PFNGLGETINVARIANTBOOLEANVEXTPROC)gleIntGetProcAddress("glGetInvariantBooleanvEXT");
	if(!TestPointer(glGetInvariantBooleanvEXT)) bIsLoaded = 0;
	glGetInvariantIntegervEXT = (PFNGLGETINVARIANTINTEGERVEXTPROC)gleIntGetProcAddress("glGetInvariantIntegervEXT");
	if(!TestPointer(glGetInvariantIntegervEXT)) bIsLoaded = 0;
	glGetInvariantFloatvEXT = (PFNGLGETINVARIANTFLOATVEXTPROC)gleIntGetProcAddress("glGetInvariantFloatvEXT");
	if(!TestPointer(glGetInvariantFloatvEXT)) bIsLoaded = 0;
	glGetLocalConstantBooleanvEXT = (PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)gleIntGetProcAddress("glGetLocalConstantBooleanvEXT");
	if(!TestPointer(glGetLocalConstantBooleanvEXT)) bIsLoaded = 0;
	glGetLocalConstantIntegervEXT = (PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)gleIntGetProcAddress("glGetLocalConstantIntegervEXT");
	if(!TestPointer(glGetLocalConstantIntegervEXT)) bIsLoaded = 0;
	glGetLocalConstantFloatvEXT = (PFNGLGETLOCALCONSTANTFLOATVEXTPROC)gleIntGetProcAddress("glGetLocalConstantFloatvEXT");
	if(!TestPointer(glGetLocalConstantFloatvEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTFEXTPROC)(GLfloat weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTFVEXTPROC)(const GLfloat *weight);
typedef void (GLE_FUNCPTR * PFNGLVERTEXWEIGHTPOINTEREXTPROC)(GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

PFNGLVERTEXWEIGHTFEXTPROC glVertexWeightfEXT;
PFNGLVERTEXWEIGHTFVEXTPROC glVertexWeightfvEXT;
PFNGLVERTEXWEIGHTPOINTEREXTPROC glVertexWeightPointerEXT;

static int gleIntLoad_EXT_vertex_weighting()
{
	int bIsLoaded = 1;
	glVertexWeightfEXT = (PFNGLVERTEXWEIGHTFEXTPROC)gleIntGetProcAddress("glVertexWeightfEXT");
	if(!TestPointer(glVertexWeightfEXT)) bIsLoaded = 0;
	glVertexWeightfvEXT = (PFNGLVERTEXWEIGHTFVEXTPROC)gleIntGetProcAddress("glVertexWeightfvEXT");
	if(!TestPointer(glVertexWeightfvEXT)) bIsLoaded = 0;
	glVertexWeightPointerEXT = (PFNGLVERTEXWEIGHTPOINTEREXTPROC)gleIntGetProcAddress("glVertexWeightPointerEXT");
	if(!TestPointer(glVertexWeightPointerEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLFRAMETERMINATORGREMEDYPROC)();

PFNGLFRAMETERMINATORGREMEDYPROC glFrameTerminatorGREMEDY;

static int gleIntLoad_GREMEDY_frame_terminator()
{
	int bIsLoaded = 1;
	glFrameTerminatorGREMEDY = (PFNGLFRAMETERMINATORGREMEDYPROC)gleIntGetProcAddress("glFrameTerminatorGREMEDY");
	if(!TestPointer(glFrameTerminatorGREMEDY)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLSTRINGMARKERGREMEDYPROC)(GLsizei len, const GLvoid *string);

PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY;

static int gleIntLoad_GREMEDY_string_marker()
{
	int bIsLoaded = 1;
	glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)gleIntGetProcAddress("glStringMarkerGREMEDY");
	if(!TestPointer(glStringMarkerGREMEDY)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERIHPPROC)(GLenum target, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERFHPPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)(GLenum target, GLenum pname, GLfloat *params);

PFNGLIMAGETRANSFORMPARAMETERIHPPROC glImageTransformParameteriHP;
PFNGLIMAGETRANSFORMPARAMETERFHPPROC glImageTransformParameterfHP;
PFNGLIMAGETRANSFORMPARAMETERIVHPPROC glImageTransformParameterivHP;
PFNGLIMAGETRANSFORMPARAMETERFVHPPROC glImageTransformParameterfvHP;
PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC glGetImageTransformParameterivHP;
PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC glGetImageTransformParameterfvHP;

static int gleIntLoad_HP_image_transform()
{
	int bIsLoaded = 1;
	glImageTransformParameteriHP = (PFNGLIMAGETRANSFORMPARAMETERIHPPROC)gleIntGetProcAddress("glImageTransformParameteriHP");
	if(!TestPointer(glImageTransformParameteriHP)) bIsLoaded = 0;
	glImageTransformParameterfHP = (PFNGLIMAGETRANSFORMPARAMETERFHPPROC)gleIntGetProcAddress("glImageTransformParameterfHP");
	if(!TestPointer(glImageTransformParameterfHP)) bIsLoaded = 0;
	glImageTransformParameterivHP = (PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)gleIntGetProcAddress("glImageTransformParameterivHP");
	if(!TestPointer(glImageTransformParameterivHP)) bIsLoaded = 0;
	glImageTransformParameterfvHP = (PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)gleIntGetProcAddress("glImageTransformParameterfvHP");
	if(!TestPointer(glImageTransformParameterfvHP)) bIsLoaded = 0;
	glGetImageTransformParameterivHP = (PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)gleIntGetProcAddress("glGetImageTransformParameterivHP");
	if(!TestPointer(glGetImageTransformParameterivHP)) bIsLoaded = 0;
	glGetImageTransformParameterfvHP = (PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)gleIntGetProcAddress("glGetImageTransformParameterfvHP");
	if(!TestPointer(glGetImageTransformParameterfvHP)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLMULTIMODEDRAWARRAYSIBMPROC)(const GLenum *mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride);
typedef void (GLE_FUNCPTR * PFNGLMULTIMODEDRAWELEMENTSIBMPROC)(const GLenum *mode, const GLsizei *count, GLenum type, const GLvoid* const *indices, GLsizei primcount, GLint modestride);

PFNGLMULTIMODEDRAWARRAYSIBMPROC glMultiModeDrawArraysIBM;
PFNGLMULTIMODEDRAWELEMENTSIBMPROC glMultiModeDrawElementsIBM;

static int gleIntLoad_IBM_multimode_draw_arrays()
{
	int bIsLoaded = 1;
	glMultiModeDrawArraysIBM = (PFNGLMULTIMODEDRAWARRAYSIBMPROC)gleIntGetProcAddress("glMultiModeDrawArraysIBM");
	if(!TestPointer(glMultiModeDrawArraysIBM)) bIsLoaded = 0;
	glMultiModeDrawElementsIBM = (PFNGLMULTIMODEDRAWELEMENTSIBMPROC)gleIntGetProcAddress("glMultiModeDrawElementsIBM");
	if(!TestPointer(glMultiModeDrawElementsIBM)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTERLISTIBMPROC)(GLint stride, const GLboolean* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERLISTIBMPROC)(GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERLISTIBMPROC)(GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride);

PFNGLCOLORPOINTERLISTIBMPROC glColorPointerListIBM;
PFNGLSECONDARYCOLORPOINTERLISTIBMPROC glSecondaryColorPointerListIBM;
PFNGLEDGEFLAGPOINTERLISTIBMPROC glEdgeFlagPointerListIBM;
PFNGLFOGCOORDPOINTERLISTIBMPROC glFogCoordPointerListIBM;
PFNGLINDEXPOINTERLISTIBMPROC glIndexPointerListIBM;
PFNGLNORMALPOINTERLISTIBMPROC glNormalPointerListIBM;
PFNGLTEXCOORDPOINTERLISTIBMPROC glTexCoordPointerListIBM;
PFNGLVERTEXPOINTERLISTIBMPROC glVertexPointerListIBM;

static int gleIntLoad_IBM_vertex_array_lists()
{
	int bIsLoaded = 1;
	glColorPointerListIBM = (PFNGLCOLORPOINTERLISTIBMPROC)gleIntGetProcAddress("glColorPointerListIBM");
	if(!TestPointer(glColorPointerListIBM)) bIsLoaded = 0;
	glSecondaryColorPointerListIBM = (PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)gleIntGetProcAddress("glSecondaryColorPointerListIBM");
	if(!TestPointer(glSecondaryColorPointerListIBM)) bIsLoaded = 0;
	glEdgeFlagPointerListIBM = (PFNGLEDGEFLAGPOINTERLISTIBMPROC)gleIntGetProcAddress("glEdgeFlagPointerListIBM");
	if(!TestPointer(glEdgeFlagPointerListIBM)) bIsLoaded = 0;
	glFogCoordPointerListIBM = (PFNGLFOGCOORDPOINTERLISTIBMPROC)gleIntGetProcAddress("glFogCoordPointerListIBM");
	if(!TestPointer(glFogCoordPointerListIBM)) bIsLoaded = 0;
	glIndexPointerListIBM = (PFNGLINDEXPOINTERLISTIBMPROC)gleIntGetProcAddress("glIndexPointerListIBM");
	if(!TestPointer(glIndexPointerListIBM)) bIsLoaded = 0;
	glNormalPointerListIBM = (PFNGLNORMALPOINTERLISTIBMPROC)gleIntGetProcAddress("glNormalPointerListIBM");
	if(!TestPointer(glNormalPointerListIBM)) bIsLoaded = 0;
	glTexCoordPointerListIBM = (PFNGLTEXCOORDPOINTERLISTIBMPROC)gleIntGetProcAddress("glTexCoordPointerListIBM");
	if(!TestPointer(glTexCoordPointerListIBM)) bIsLoaded = 0;
	glVertexPointerListIBM = (PFNGLVERTEXPOINTERLISTIBMPROC)gleIntGetProcAddress("glVertexPointerListIBM");
	if(!TestPointer(glVertexPointerListIBM)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERVINTELPROC)(GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERVINTELPROC)(GLint size, GLenum type, const GLvoid* *pointer);

PFNGLVERTEXPOINTERVINTELPROC glVertexPointervINTEL;
PFNGLNORMALPOINTERVINTELPROC glNormalPointervINTEL;
PFNGLCOLORPOINTERVINTELPROC glColorPointervINTEL;
PFNGLTEXCOORDPOINTERVINTELPROC glTexCoordPointervINTEL;

static int gleIntLoad_INTEL_parallel_arrays()
{
	int bIsLoaded = 1;
	glVertexPointervINTEL = (PFNGLVERTEXPOINTERVINTELPROC)gleIntGetProcAddress("glVertexPointervINTEL");
	if(!TestPointer(glVertexPointervINTEL)) bIsLoaded = 0;
	glNormalPointervINTEL = (PFNGLNORMALPOINTERVINTELPROC)gleIntGetProcAddress("glNormalPointervINTEL");
	if(!TestPointer(glNormalPointervINTEL)) bIsLoaded = 0;
	glColorPointervINTEL = (PFNGLCOLORPOINTERVINTELPROC)gleIntGetProcAddress("glColorPointervINTEL");
	if(!TestPointer(glColorPointervINTEL)) bIsLoaded = 0;
	glTexCoordPointervINTEL = (PFNGLTEXCOORDPOINTERVINTELPROC)gleIntGetProcAddress("glTexCoordPointervINTEL");
	if(!TestPointer(glTexCoordPointervINTEL)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLRESIZEBUFFERSMESAPROC)();

PFNGLRESIZEBUFFERSMESAPROC glResizeBuffersMESA;

static int gleIntLoad_MESA_resize_buffers()
{
	int bIsLoaded = 1;
	glResizeBuffersMESA = (PFNGLRESIZEBUFFERSMESAPROC)gleIntGetProcAddress("glResizeBuffersMESA");
	if(!TestPointer(glResizeBuffersMESA)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLWINDOWPOS2DMESAPROC glWindowPos2dMESA;
PFNGLWINDOWPOS2DVMESAPROC glWindowPos2dvMESA;
PFNGLWINDOWPOS2FMESAPROC glWindowPos2fMESA;
PFNGLWINDOWPOS2FVMESAPROC glWindowPos2fvMESA;
PFNGLWINDOWPOS2IMESAPROC glWindowPos2iMESA;
PFNGLWINDOWPOS2IVMESAPROC glWindowPos2ivMESA;
PFNGLWINDOWPOS2SMESAPROC glWindowPos2sMESA;
PFNGLWINDOWPOS2SVMESAPROC glWindowPos2svMESA;
PFNGLWINDOWPOS3DMESAPROC glWindowPos3dMESA;
PFNGLWINDOWPOS3DVMESAPROC glWindowPos3dvMESA;
PFNGLWINDOWPOS3FMESAPROC glWindowPos3fMESA;
PFNGLWINDOWPOS3FVMESAPROC glWindowPos3fvMESA;
PFNGLWINDOWPOS3IMESAPROC glWindowPos3iMESA;
PFNGLWINDOWPOS3IVMESAPROC glWindowPos3ivMESA;
PFNGLWINDOWPOS3SMESAPROC glWindowPos3sMESA;
PFNGLWINDOWPOS3SVMESAPROC glWindowPos3svMESA;
PFNGLWINDOWPOS4DMESAPROC glWindowPos4dMESA;
PFNGLWINDOWPOS4DVMESAPROC glWindowPos4dvMESA;
PFNGLWINDOWPOS4FMESAPROC glWindowPos4fMESA;
PFNGLWINDOWPOS4FVMESAPROC glWindowPos4fvMESA;
PFNGLWINDOWPOS4IMESAPROC glWindowPos4iMESA;
PFNGLWINDOWPOS4IVMESAPROC glWindowPos4ivMESA;
PFNGLWINDOWPOS4SMESAPROC glWindowPos4sMESA;
PFNGLWINDOWPOS4SVMESAPROC glWindowPos4svMESA;

static int gleIntLoad_MESA_window_pos()
{
	int bIsLoaded = 1;
	glWindowPos2dMESA = (PFNGLWINDOWPOS2DMESAPROC)gleIntGetProcAddress("glWindowPos2dMESA");
	if(!TestPointer(glWindowPos2dMESA)) bIsLoaded = 0;
	glWindowPos2dvMESA = (PFNGLWINDOWPOS2DVMESAPROC)gleIntGetProcAddress("glWindowPos2dvMESA");
	if(!TestPointer(glWindowPos2dvMESA)) bIsLoaded = 0;
	glWindowPos2fMESA = (PFNGLWINDOWPOS2FMESAPROC)gleIntGetProcAddress("glWindowPos2fMESA");
	if(!TestPointer(glWindowPos2fMESA)) bIsLoaded = 0;
	glWindowPos2fvMESA = (PFNGLWINDOWPOS2FVMESAPROC)gleIntGetProcAddress("glWindowPos2fvMESA");
	if(!TestPointer(glWindowPos2fvMESA)) bIsLoaded = 0;
	glWindowPos2iMESA = (PFNGLWINDOWPOS2IMESAPROC)gleIntGetProcAddress("glWindowPos2iMESA");
	if(!TestPointer(glWindowPos2iMESA)) bIsLoaded = 0;
	glWindowPos2ivMESA = (PFNGLWINDOWPOS2IVMESAPROC)gleIntGetProcAddress("glWindowPos2ivMESA");
	if(!TestPointer(glWindowPos2ivMESA)) bIsLoaded = 0;
	glWindowPos2sMESA = (PFNGLWINDOWPOS2SMESAPROC)gleIntGetProcAddress("glWindowPos2sMESA");
	if(!TestPointer(glWindowPos2sMESA)) bIsLoaded = 0;
	glWindowPos2svMESA = (PFNGLWINDOWPOS2SVMESAPROC)gleIntGetProcAddress("glWindowPos2svMESA");
	if(!TestPointer(glWindowPos2svMESA)) bIsLoaded = 0;
	glWindowPos3dMESA = (PFNGLWINDOWPOS3DMESAPROC)gleIntGetProcAddress("glWindowPos3dMESA");
	if(!TestPointer(glWindowPos3dMESA)) bIsLoaded = 0;
	glWindowPos3dvMESA = (PFNGLWINDOWPOS3DVMESAPROC)gleIntGetProcAddress("glWindowPos3dvMESA");
	if(!TestPointer(glWindowPos3dvMESA)) bIsLoaded = 0;
	glWindowPos3fMESA = (PFNGLWINDOWPOS3FMESAPROC)gleIntGetProcAddress("glWindowPos3fMESA");
	if(!TestPointer(glWindowPos3fMESA)) bIsLoaded = 0;
	glWindowPos3fvMESA = (PFNGLWINDOWPOS3FVMESAPROC)gleIntGetProcAddress("glWindowPos3fvMESA");
	if(!TestPointer(glWindowPos3fvMESA)) bIsLoaded = 0;
	glWindowPos3iMESA = (PFNGLWINDOWPOS3IMESAPROC)gleIntGetProcAddress("glWindowPos3iMESA");
	if(!TestPointer(glWindowPos3iMESA)) bIsLoaded = 0;
	glWindowPos3ivMESA = (PFNGLWINDOWPOS3IVMESAPROC)gleIntGetProcAddress("glWindowPos3ivMESA");
	if(!TestPointer(glWindowPos3ivMESA)) bIsLoaded = 0;
	glWindowPos3sMESA = (PFNGLWINDOWPOS3SMESAPROC)gleIntGetProcAddress("glWindowPos3sMESA");
	if(!TestPointer(glWindowPos3sMESA)) bIsLoaded = 0;
	glWindowPos3svMESA = (PFNGLWINDOWPOS3SVMESAPROC)gleIntGetProcAddress("glWindowPos3svMESA");
	if(!TestPointer(glWindowPos3svMESA)) bIsLoaded = 0;
	glWindowPos4dMESA = (PFNGLWINDOWPOS4DMESAPROC)gleIntGetProcAddress("glWindowPos4dMESA");
	if(!TestPointer(glWindowPos4dMESA)) bIsLoaded = 0;
	glWindowPos4dvMESA = (PFNGLWINDOWPOS4DVMESAPROC)gleIntGetProcAddress("glWindowPos4dvMESA");
	if(!TestPointer(glWindowPos4dvMESA)) bIsLoaded = 0;
	glWindowPos4fMESA = (PFNGLWINDOWPOS4FMESAPROC)gleIntGetProcAddress("glWindowPos4fMESA");
	if(!TestPointer(glWindowPos4fMESA)) bIsLoaded = 0;
	glWindowPos4fvMESA = (PFNGLWINDOWPOS4FVMESAPROC)gleIntGetProcAddress("glWindowPos4fvMESA");
	if(!TestPointer(glWindowPos4fvMESA)) bIsLoaded = 0;
	glWindowPos4iMESA = (PFNGLWINDOWPOS4IMESAPROC)gleIntGetProcAddress("glWindowPos4iMESA");
	if(!TestPointer(glWindowPos4iMESA)) bIsLoaded = 0;
	glWindowPos4ivMESA = (PFNGLWINDOWPOS4IVMESAPROC)gleIntGetProcAddress("glWindowPos4ivMESA");
	if(!TestPointer(glWindowPos4ivMESA)) bIsLoaded = 0;
	glWindowPos4sMESA = (PFNGLWINDOWPOS4SMESAPROC)gleIntGetProcAddress("glWindowPos4sMESA");
	if(!TestPointer(glWindowPos4sMESA)) bIsLoaded = 0;
	glWindowPos4svMESA = (PFNGLWINDOWPOS4SVMESAPROC)gleIntGetProcAddress("glWindowPos4svMESA");
	if(!TestPointer(glWindowPos4svMESA)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLBEGINCONDITIONALRENDERNVPROC)(GLuint id, GLenum mode);
typedef void (GLE_FUNCPTR * PFNGLENDCONDITIONALRENDERNVPROC)();

PFNGLBEGINCONDITIONALRENDERNVPROC glBeginConditionalRenderNV;
PFNGLENDCONDITIONALRENDERNVPROC glEndConditionalRenderNV;

static int gleIntLoad_NV_conditional_render()
{
	int bIsLoaded = 1;
	glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)gleIntGetProcAddress("glBeginConditionalRenderNV");
	if(!TestPointer(glBeginConditionalRenderNV)) bIsLoaded = 0;
	glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)gleIntGetProcAddress("glEndConditionalRenderNV");
	if(!TestPointer(glEndConditionalRenderNV)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLCOPYIMAGESUBDATANVPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

PFNGLCOPYIMAGESUBDATANVPROC glCopyImageSubDataNV;

static int gleIntLoad_NV_copy_image()
{
	int bIsLoaded = 1;
	glCopyImageSubDataNV = (PFNGLCOPYIMAGESUBDATANVPROC)gleIntGetProcAddress("glCopyImageSubDataNV");
	if(!TestPointer(glCopyImageSubDataNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEDNVPROC)(GLdouble zNear, GLdouble zFar);
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHDNVPROC)(GLdouble depth);
typedef void (GLE_FUNCPTR * PFNGLDEPTHBOUNDSDNVPROC)(GLdouble zmin, GLdouble zmax);

PFNGLDEPTHRANGEDNVPROC glDepthRangedNV;
PFNGLCLEARDEPTHDNVPROC glClearDepthdNV;
PFNGLDEPTHBOUNDSDNVPROC glDepthBoundsdNV;

static int gleIntLoad_NV_depth_buffer_float()
{
	int bIsLoaded = 1;
	glDepthRangedNV = (PFNGLDEPTHRANGEDNVPROC)gleIntGetProcAddress("glDepthRangedNV");
	if(!TestPointer(glDepthRangedNV)) bIsLoaded = 0;
	glClearDepthdNV = (PFNGLCLEARDEPTHDNVPROC)gleIntGetProcAddress("glClearDepthdNV");
	if(!TestPointer(glClearDepthdNV)) bIsLoaded = 0;
	glDepthBoundsdNV = (PFNGLDEPTHBOUNDSDNVPROC)gleIntGetProcAddress("glDepthBoundsdNV");
	if(!TestPointer(glDepthBoundsdNV)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLMAPCONTROLPOINTSNVPROC)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
typedef void (GLE_FUNCPTR * PFNGLMAPPARAMETERIVNVPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLMAPPARAMETERFVNVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPCONTROLPOINTSNVPROC)(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
typedef void (GLE_FUNCPTR * PFNGLGETMAPPARAMETERIVNVPROC)(GLenum target, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPPARAMETERFVNVPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPATTRIBPARAMETERIVNVPROC)(GLenum target, GLuint index, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETMAPATTRIBPARAMETERFVNVPROC)(GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLEVALMAPSNVPROC)(GLenum target, GLenum mode);

PFNGLMAPCONTROLPOINTSNVPROC glMapControlPointsNV;
PFNGLMAPPARAMETERIVNVPROC glMapParameterivNV;
PFNGLMAPPARAMETERFVNVPROC glMapParameterfvNV;
PFNGLGETMAPCONTROLPOINTSNVPROC glGetMapControlPointsNV;
PFNGLGETMAPPARAMETERIVNVPROC glGetMapParameterivNV;
PFNGLGETMAPPARAMETERFVNVPROC glGetMapParameterfvNV;
PFNGLGETMAPATTRIBPARAMETERIVNVPROC glGetMapAttribParameterivNV;
PFNGLGETMAPATTRIBPARAMETERFVNVPROC glGetMapAttribParameterfvNV;
PFNGLEVALMAPSNVPROC glEvalMapsNV;

static int gleIntLoad_NV_evaluators()
{
	int bIsLoaded = 1;
	glMapControlPointsNV = (PFNGLMAPCONTROLPOINTSNVPROC)gleIntGetProcAddress("glMapControlPointsNV");
	if(!TestPointer(glMapControlPointsNV)) bIsLoaded = 0;
	glMapParameterivNV = (PFNGLMAPPARAMETERIVNVPROC)gleIntGetProcAddress("glMapParameterivNV");
	if(!TestPointer(glMapParameterivNV)) bIsLoaded = 0;
	glMapParameterfvNV = (PFNGLMAPPARAMETERFVNVPROC)gleIntGetProcAddress("glMapParameterfvNV");
	if(!TestPointer(glMapParameterfvNV)) bIsLoaded = 0;
	glGetMapControlPointsNV = (PFNGLGETMAPCONTROLPOINTSNVPROC)gleIntGetProcAddress("glGetMapControlPointsNV");
	if(!TestPointer(glGetMapControlPointsNV)) bIsLoaded = 0;
	glGetMapParameterivNV = (PFNGLGETMAPPARAMETERIVNVPROC)gleIntGetProcAddress("glGetMapParameterivNV");
	if(!TestPointer(glGetMapParameterivNV)) bIsLoaded = 0;
	glGetMapParameterfvNV = (PFNGLGETMAPPARAMETERFVNVPROC)gleIntGetProcAddress("glGetMapParameterfvNV");
	if(!TestPointer(glGetMapParameterfvNV)) bIsLoaded = 0;
	glGetMapAttribParameterivNV = (PFNGLGETMAPATTRIBPARAMETERIVNVPROC)gleIntGetProcAddress("glGetMapAttribParameterivNV");
	if(!TestPointer(glGetMapAttribParameterivNV)) bIsLoaded = 0;
	glGetMapAttribParameterfvNV = (PFNGLGETMAPATTRIBPARAMETERFVNVPROC)gleIntGetProcAddress("glGetMapAttribParameterfvNV");
	if(!TestPointer(glGetMapAttribParameterfvNV)) bIsLoaded = 0;
	glEvalMapsNV = (PFNGLEVALMAPSNVPROC)gleIntGetProcAddress("glEvalMapsNV");
	if(!TestPointer(glEvalMapsNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLGETMULTISAMPLEFVNVPROC)(GLenum pname, GLuint index, GLfloat *val);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKINDEXEDNVPROC)(GLuint index, GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLTEXRENDERBUFFERNVPROC)(GLenum target, GLuint renderbuffer);

PFNGLGETMULTISAMPLEFVNVPROC glGetMultisamplefvNV;
PFNGLSAMPLEMASKINDEXEDNVPROC glSampleMaskIndexedNV;
PFNGLTEXRENDERBUFFERNVPROC glTexRenderbufferNV;

static int gleIntLoad_NV_explicit_multisample()
{
	int bIsLoaded = 1;
	glGetMultisamplefvNV = (PFNGLGETMULTISAMPLEFVNVPROC)gleIntGetProcAddress("glGetMultisamplefvNV");
	if(!TestPointer(glGetMultisamplefvNV)) bIsLoaded = 0;
	glSampleMaskIndexedNV = (PFNGLSAMPLEMASKINDEXEDNVPROC)gleIntGetProcAddress("glSampleMaskIndexedNV");
	if(!TestPointer(glSampleMaskIndexedNV)) bIsLoaded = 0;
	glTexRenderbufferNV = (PFNGLTEXRENDERBUFFERNVPROC)gleIntGetProcAddress("glTexRenderbufferNV");
	if(!TestPointer(glTexRenderbufferNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDELETEFENCESNVPROC)(GLsizei n, const GLuint *fences);
typedef void (GLE_FUNCPTR * PFNGLGENFENCESNVPROC)(GLsizei n, GLuint *fences);
typedef GLboolean (GLE_FUNCPTR * PFNGLISFENCENVPROC)(GLuint fence);
typedef GLboolean (GLE_FUNCPTR * PFNGLTESTFENCENVPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLGETFENCEIVNVPROC)(GLuint fence, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLFINISHFENCENVPROC)(GLuint fence);
typedef void (GLE_FUNCPTR * PFNGLSETFENCENVPROC)(GLuint fence, GLenum condition);

PFNGLDELETEFENCESNVPROC glDeleteFencesNV;
PFNGLGENFENCESNVPROC glGenFencesNV;
PFNGLISFENCENVPROC glIsFenceNV;
PFNGLTESTFENCENVPROC glTestFenceNV;
PFNGLGETFENCEIVNVPROC glGetFenceivNV;
PFNGLFINISHFENCENVPROC glFinishFenceNV;
PFNGLSETFENCENVPROC glSetFenceNV;

static int gleIntLoad_NV_fence()
{
	int bIsLoaded = 1;
	glDeleteFencesNV = (PFNGLDELETEFENCESNVPROC)gleIntGetProcAddress("glDeleteFencesNV");
	if(!TestPointer(glDeleteFencesNV)) bIsLoaded = 0;
	glGenFencesNV = (PFNGLGENFENCESNVPROC)gleIntGetProcAddress("glGenFencesNV");
	if(!TestPointer(glGenFencesNV)) bIsLoaded = 0;
	glIsFenceNV = (PFNGLISFENCENVPROC)gleIntGetProcAddress("glIsFenceNV");
	if(!TestPointer(glIsFenceNV)) bIsLoaded = 0;
	glTestFenceNV = (PFNGLTESTFENCENVPROC)gleIntGetProcAddress("glTestFenceNV");
	if(!TestPointer(glTestFenceNV)) bIsLoaded = 0;
	glGetFenceivNV = (PFNGLGETFENCEIVNVPROC)gleIntGetProcAddress("glGetFenceivNV");
	if(!TestPointer(glGetFenceivNV)) bIsLoaded = 0;
	glFinishFenceNV = (PFNGLFINISHFENCENVPROC)gleIntGetProcAddress("glFinishFenceNV");
	if(!TestPointer(glFinishFenceNV)) bIsLoaded = 0;
	glSetFenceNV = (PFNGLSETFENCENVPROC)gleIntGetProcAddress("glSetFenceNV");
	if(!TestPointer(glSetFenceNV)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, const GLfloat *v);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, const GLdouble *v);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)(GLuint id, GLsizei len, const GLubyte *name, GLdouble *params);

PFNGLPROGRAMNAMEDPARAMETER4FNVPROC glProgramNamedParameter4fNV;
PFNGLPROGRAMNAMEDPARAMETER4DNVPROC glProgramNamedParameter4dNV;
PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC glProgramNamedParameter4fvNV;
PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC glProgramNamedParameter4dvNV;
PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC glGetProgramNamedParameterfvNV;
PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC glGetProgramNamedParameterdvNV;

static int gleIntLoad_NV_fragment_program()
{
	int bIsLoaded = 1;
	glProgramNamedParameter4fNV = (PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)gleIntGetProcAddress("glProgramNamedParameter4fNV");
	if(!TestPointer(glProgramNamedParameter4fNV)) bIsLoaded = 0;
	glProgramNamedParameter4dNV = (PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)gleIntGetProcAddress("glProgramNamedParameter4dNV");
	if(!TestPointer(glProgramNamedParameter4dNV)) bIsLoaded = 0;
	glProgramNamedParameter4fvNV = (PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)gleIntGetProcAddress("glProgramNamedParameter4fvNV");
	if(!TestPointer(glProgramNamedParameter4fvNV)) bIsLoaded = 0;
	glProgramNamedParameter4dvNV = (PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)gleIntGetProcAddress("glProgramNamedParameter4dvNV");
	if(!TestPointer(glProgramNamedParameter4dvNV)) bIsLoaded = 0;
	glGetProgramNamedParameterfvNV = (PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)gleIntGetProcAddress("glGetProgramNamedParameterfvNV");
	if(!TestPointer(glGetProgramNamedParameterfvNV)) bIsLoaded = 0;
	glGetProgramNamedParameterdvNV = (PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)gleIntGetProcAddress("glGetProgramNamedParameterdvNV");
	if(!TestPointer(glGetProgramNamedParameterdvNV)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);

PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC glRenderbufferStorageMultisampleCoverageNV;

static int gleIntLoad_NV_framebuffer_multisample_coverage()
{
	int bIsLoaded = 1;
	glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)gleIntGetProcAddress("glRenderbufferStorageMultisampleCoverageNV");
	if(!TestPointer(glRenderbufferStorageMultisampleCoverageNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPROGRAMVERTEXLIMITNVPROC)(GLenum target, GLint limit);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREEXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);

PFNGLPROGRAMVERTEXLIMITNVPROC glProgramVertexLimitNV;
PFNGLFRAMEBUFFERTEXTUREEXTPROC glFramebufferTextureEXT;
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC glFramebufferTextureLayerEXT;
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC glFramebufferTextureFaceEXT;

static int gleIntLoad_NV_geometry_program4()
{
	int bIsLoaded = 1;
	glProgramVertexLimitNV = (PFNGLPROGRAMVERTEXLIMITNVPROC)gleIntGetProcAddress("glProgramVertexLimitNV");
	if(!TestPointer(glProgramVertexLimitNV)) bIsLoaded = 0;
	glFramebufferTextureEXT = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)gleIntGetProcAddress("glFramebufferTextureEXT");
	if(!TestPointer(glFramebufferTextureEXT)) bIsLoaded = 0;
	glFramebufferTextureLayerEXT = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)gleIntGetProcAddress("glFramebufferTextureLayerEXT");
	if(!TestPointer(glFramebufferTextureLayerEXT)) bIsLoaded = 0;
	glFramebufferTextureFaceEXT = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)gleIntGetProcAddress("glFramebufferTextureFaceEXT");
	if(!TestPointer(glFramebufferTextureFaceEXT)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLPROGRAMLOCALPARAMETERI4INVPROC glProgramLocalParameterI4iNV;
PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC glProgramLocalParameterI4ivNV;
PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC glProgramLocalParametersI4ivNV;
PFNGLPROGRAMLOCALPARAMETERI4UINVPROC glProgramLocalParameterI4uiNV;
PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC glProgramLocalParameterI4uivNV;
PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC glProgramLocalParametersI4uivNV;
PFNGLPROGRAMENVPARAMETERI4INVPROC glProgramEnvParameterI4iNV;
PFNGLPROGRAMENVPARAMETERI4IVNVPROC glProgramEnvParameterI4ivNV;
PFNGLPROGRAMENVPARAMETERSI4IVNVPROC glProgramEnvParametersI4ivNV;
PFNGLPROGRAMENVPARAMETERI4UINVPROC glProgramEnvParameterI4uiNV;
PFNGLPROGRAMENVPARAMETERI4UIVNVPROC glProgramEnvParameterI4uivNV;
PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC glProgramEnvParametersI4uivNV;
PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC glGetProgramLocalParameterIivNV;
PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC glGetProgramLocalParameterIuivNV;
PFNGLGETPROGRAMENVPARAMETERIIVNVPROC glGetProgramEnvParameterIivNV;
PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC glGetProgramEnvParameterIuivNV;

static int gleIntLoad_NV_gpu_program4()
{
	int bIsLoaded = 1;
	glProgramLocalParameterI4iNV = (PFNGLPROGRAMLOCALPARAMETERI4INVPROC)gleIntGetProcAddress("glProgramLocalParameterI4iNV");
	if(!TestPointer(glProgramLocalParameterI4iNV)) bIsLoaded = 0;
	glProgramLocalParameterI4ivNV = (PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)gleIntGetProcAddress("glProgramLocalParameterI4ivNV");
	if(!TestPointer(glProgramLocalParameterI4ivNV)) bIsLoaded = 0;
	glProgramLocalParametersI4ivNV = (PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)gleIntGetProcAddress("glProgramLocalParametersI4ivNV");
	if(!TestPointer(glProgramLocalParametersI4ivNV)) bIsLoaded = 0;
	glProgramLocalParameterI4uiNV = (PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)gleIntGetProcAddress("glProgramLocalParameterI4uiNV");
	if(!TestPointer(glProgramLocalParameterI4uiNV)) bIsLoaded = 0;
	glProgramLocalParameterI4uivNV = (PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)gleIntGetProcAddress("glProgramLocalParameterI4uivNV");
	if(!TestPointer(glProgramLocalParameterI4uivNV)) bIsLoaded = 0;
	glProgramLocalParametersI4uivNV = (PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)gleIntGetProcAddress("glProgramLocalParametersI4uivNV");
	if(!TestPointer(glProgramLocalParametersI4uivNV)) bIsLoaded = 0;
	glProgramEnvParameterI4iNV = (PFNGLPROGRAMENVPARAMETERI4INVPROC)gleIntGetProcAddress("glProgramEnvParameterI4iNV");
	if(!TestPointer(glProgramEnvParameterI4iNV)) bIsLoaded = 0;
	glProgramEnvParameterI4ivNV = (PFNGLPROGRAMENVPARAMETERI4IVNVPROC)gleIntGetProcAddress("glProgramEnvParameterI4ivNV");
	if(!TestPointer(glProgramEnvParameterI4ivNV)) bIsLoaded = 0;
	glProgramEnvParametersI4ivNV = (PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)gleIntGetProcAddress("glProgramEnvParametersI4ivNV");
	if(!TestPointer(glProgramEnvParametersI4ivNV)) bIsLoaded = 0;
	glProgramEnvParameterI4uiNV = (PFNGLPROGRAMENVPARAMETERI4UINVPROC)gleIntGetProcAddress("glProgramEnvParameterI4uiNV");
	if(!TestPointer(glProgramEnvParameterI4uiNV)) bIsLoaded = 0;
	glProgramEnvParameterI4uivNV = (PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)gleIntGetProcAddress("glProgramEnvParameterI4uivNV");
	if(!TestPointer(glProgramEnvParameterI4uivNV)) bIsLoaded = 0;
	glProgramEnvParametersI4uivNV = (PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)gleIntGetProcAddress("glProgramEnvParametersI4uivNV");
	if(!TestPointer(glProgramEnvParametersI4uivNV)) bIsLoaded = 0;
	glGetProgramLocalParameterIivNV = (PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)gleIntGetProcAddress("glGetProgramLocalParameterIivNV");
	if(!TestPointer(glGetProgramLocalParameterIivNV)) bIsLoaded = 0;
	glGetProgramLocalParameterIuivNV = (PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)gleIntGetProcAddress("glGetProgramLocalParameterIuivNV");
	if(!TestPointer(glGetProgramLocalParameterIuivNV)) bIsLoaded = 0;
	glGetProgramEnvParameterIivNV = (PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)gleIntGetProcAddress("glGetProgramEnvParameterIivNV");
	if(!TestPointer(glGetProgramEnvParameterIivNV)) bIsLoaded = 0;
	glGetProgramEnvParameterIuivNV = (PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)gleIntGetProcAddress("glGetProgramEnvParameterIuivNV");
	if(!TestPointer(glGetProgramEnvParameterIuivNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)(GLenum target, GLsizei count, const GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)(GLenum target, GLuint index, GLuint *param);

PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC glProgramSubroutineParametersuivNV;
PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC glGetProgramSubroutineParameteruivNV;

static int gleIntLoad_NV_gpu_program5()
{
	int bIsLoaded = 1;
	glProgramSubroutineParametersuivNV = (PFNGLPROGRAMSUBROUTINEPARAMETERSUIVNVPROC)gleIntGetProcAddress("glProgramSubroutineParametersuivNV");
	if(!TestPointer(glProgramSubroutineParametersuivNV)) bIsLoaded = 0;
	glGetProgramSubroutineParameteruivNV = (PFNGLGETPROGRAMSUBROUTINEPARAMETERUIVNVPROC)gleIntGetProcAddress("glGetProgramSubroutineParameteruivNV");
	if(!TestPointer(glGetProgramSubroutineParameteruivNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLUNIFORM1I64NVPROC glUniform1i64NV;
PFNGLUNIFORM2I64NVPROC glUniform2i64NV;
PFNGLUNIFORM3I64NVPROC glUniform3i64NV;
PFNGLUNIFORM4I64NVPROC glUniform4i64NV;
PFNGLUNIFORM1I64VNVPROC glUniform1i64vNV;
PFNGLUNIFORM2I64VNVPROC glUniform2i64vNV;
PFNGLUNIFORM3I64VNVPROC glUniform3i64vNV;
PFNGLUNIFORM4I64VNVPROC glUniform4i64vNV;
PFNGLUNIFORM1UI64NVPROC glUniform1ui64NV;
PFNGLUNIFORM2UI64NVPROC glUniform2ui64NV;
PFNGLUNIFORM3UI64NVPROC glUniform3ui64NV;
PFNGLUNIFORM4UI64NVPROC glUniform4ui64NV;
PFNGLUNIFORM1UI64VNVPROC glUniform1ui64vNV;
PFNGLUNIFORM2UI64VNVPROC glUniform2ui64vNV;
PFNGLUNIFORM3UI64VNVPROC glUniform3ui64vNV;
PFNGLUNIFORM4UI64VNVPROC glUniform4ui64vNV;
PFNGLGETUNIFORMI64VNVPROC glGetUniformi64vNV;
PFNGLPROGRAMUNIFORM1I64NVPROC glProgramUniform1i64NV;
PFNGLPROGRAMUNIFORM2I64NVPROC glProgramUniform2i64NV;
PFNGLPROGRAMUNIFORM3I64NVPROC glProgramUniform3i64NV;
PFNGLPROGRAMUNIFORM4I64NVPROC glProgramUniform4i64NV;
PFNGLPROGRAMUNIFORM1I64VNVPROC glProgramUniform1i64vNV;
PFNGLPROGRAMUNIFORM2I64VNVPROC glProgramUniform2i64vNV;
PFNGLPROGRAMUNIFORM3I64VNVPROC glProgramUniform3i64vNV;
PFNGLPROGRAMUNIFORM4I64VNVPROC glProgramUniform4i64vNV;
PFNGLPROGRAMUNIFORM1UI64NVPROC glProgramUniform1ui64NV;
PFNGLPROGRAMUNIFORM2UI64NVPROC glProgramUniform2ui64NV;
PFNGLPROGRAMUNIFORM3UI64NVPROC glProgramUniform3ui64NV;
PFNGLPROGRAMUNIFORM4UI64NVPROC glProgramUniform4ui64NV;
PFNGLPROGRAMUNIFORM1UI64VNVPROC glProgramUniform1ui64vNV;
PFNGLPROGRAMUNIFORM2UI64VNVPROC glProgramUniform2ui64vNV;
PFNGLPROGRAMUNIFORM3UI64VNVPROC glProgramUniform3ui64vNV;
PFNGLPROGRAMUNIFORM4UI64VNVPROC glProgramUniform4ui64vNV;

static int gleIntLoad_NV_gpu_shader5()
{
	int bIsLoaded = 1;
	glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC)gleIntGetProcAddress("glUniform1i64NV");
	if(!TestPointer(glUniform1i64NV)) bIsLoaded = 0;
	glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC)gleIntGetProcAddress("glUniform2i64NV");
	if(!TestPointer(glUniform2i64NV)) bIsLoaded = 0;
	glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC)gleIntGetProcAddress("glUniform3i64NV");
	if(!TestPointer(glUniform3i64NV)) bIsLoaded = 0;
	glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC)gleIntGetProcAddress("glUniform4i64NV");
	if(!TestPointer(glUniform4i64NV)) bIsLoaded = 0;
	glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC)gleIntGetProcAddress("glUniform1i64vNV");
	if(!TestPointer(glUniform1i64vNV)) bIsLoaded = 0;
	glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC)gleIntGetProcAddress("glUniform2i64vNV");
	if(!TestPointer(glUniform2i64vNV)) bIsLoaded = 0;
	glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC)gleIntGetProcAddress("glUniform3i64vNV");
	if(!TestPointer(glUniform3i64vNV)) bIsLoaded = 0;
	glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC)gleIntGetProcAddress("glUniform4i64vNV");
	if(!TestPointer(glUniform4i64vNV)) bIsLoaded = 0;
	glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC)gleIntGetProcAddress("glUniform1ui64NV");
	if(!TestPointer(glUniform1ui64NV)) bIsLoaded = 0;
	glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC)gleIntGetProcAddress("glUniform2ui64NV");
	if(!TestPointer(glUniform2ui64NV)) bIsLoaded = 0;
	glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC)gleIntGetProcAddress("glUniform3ui64NV");
	if(!TestPointer(glUniform3ui64NV)) bIsLoaded = 0;
	glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC)gleIntGetProcAddress("glUniform4ui64NV");
	if(!TestPointer(glUniform4ui64NV)) bIsLoaded = 0;
	glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC)gleIntGetProcAddress("glUniform1ui64vNV");
	if(!TestPointer(glUniform1ui64vNV)) bIsLoaded = 0;
	glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC)gleIntGetProcAddress("glUniform2ui64vNV");
	if(!TestPointer(glUniform2ui64vNV)) bIsLoaded = 0;
	glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC)gleIntGetProcAddress("glUniform3ui64vNV");
	if(!TestPointer(glUniform3ui64vNV)) bIsLoaded = 0;
	glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC)gleIntGetProcAddress("glUniform4ui64vNV");
	if(!TestPointer(glUniform4ui64vNV)) bIsLoaded = 0;
	glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC)gleIntGetProcAddress("glGetUniformi64vNV");
	if(!TestPointer(glGetUniformi64vNV)) bIsLoaded = 0;
	glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC)gleIntGetProcAddress("glProgramUniform1i64NV");
	if(!TestPointer(glProgramUniform1i64NV)) bIsLoaded = 0;
	glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC)gleIntGetProcAddress("glProgramUniform2i64NV");
	if(!TestPointer(glProgramUniform2i64NV)) bIsLoaded = 0;
	glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC)gleIntGetProcAddress("glProgramUniform3i64NV");
	if(!TestPointer(glProgramUniform3i64NV)) bIsLoaded = 0;
	glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC)gleIntGetProcAddress("glProgramUniform4i64NV");
	if(!TestPointer(glProgramUniform4i64NV)) bIsLoaded = 0;
	glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC)gleIntGetProcAddress("glProgramUniform1i64vNV");
	if(!TestPointer(glProgramUniform1i64vNV)) bIsLoaded = 0;
	glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC)gleIntGetProcAddress("glProgramUniform2i64vNV");
	if(!TestPointer(glProgramUniform2i64vNV)) bIsLoaded = 0;
	glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC)gleIntGetProcAddress("glProgramUniform3i64vNV");
	if(!TestPointer(glProgramUniform3i64vNV)) bIsLoaded = 0;
	glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC)gleIntGetProcAddress("glProgramUniform4i64vNV");
	if(!TestPointer(glProgramUniform4i64vNV)) bIsLoaded = 0;
	glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC)gleIntGetProcAddress("glProgramUniform1ui64NV");
	if(!TestPointer(glProgramUniform1ui64NV)) bIsLoaded = 0;
	glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC)gleIntGetProcAddress("glProgramUniform2ui64NV");
	if(!TestPointer(glProgramUniform2ui64NV)) bIsLoaded = 0;
	glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC)gleIntGetProcAddress("glProgramUniform3ui64NV");
	if(!TestPointer(glProgramUniform3ui64NV)) bIsLoaded = 0;
	glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC)gleIntGetProcAddress("glProgramUniform4ui64NV");
	if(!TestPointer(glProgramUniform4ui64NV)) bIsLoaded = 0;
	glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC)gleIntGetProcAddress("glProgramUniform1ui64vNV");
	if(!TestPointer(glProgramUniform1ui64vNV)) bIsLoaded = 0;
	glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC)gleIntGetProcAddress("glProgramUniform2ui64vNV");
	if(!TestPointer(glProgramUniform2ui64vNV)) bIsLoaded = 0;
	glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC)gleIntGetProcAddress("glProgramUniform3ui64vNV");
	if(!TestPointer(glProgramUniform3ui64vNV)) bIsLoaded = 0;
	glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC)gleIntGetProcAddress("glProgramUniform4ui64vNV");
	if(!TestPointer(glProgramUniform4ui64vNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVERTEX2HNVPROC glVertex2hNV;
PFNGLVERTEX2HVNVPROC glVertex2hvNV;
PFNGLVERTEX3HNVPROC glVertex3hNV;
PFNGLVERTEX3HVNVPROC glVertex3hvNV;
PFNGLVERTEX4HNVPROC glVertex4hNV;
PFNGLVERTEX4HVNVPROC glVertex4hvNV;
PFNGLNORMAL3HNVPROC glNormal3hNV;
PFNGLNORMAL3HVNVPROC glNormal3hvNV;
PFNGLCOLOR3HNVPROC glColor3hNV;
PFNGLCOLOR3HVNVPROC glColor3hvNV;
PFNGLCOLOR4HNVPROC glColor4hNV;
PFNGLCOLOR4HVNVPROC glColor4hvNV;
PFNGLTEXCOORD1HNVPROC glTexCoord1hNV;
PFNGLTEXCOORD1HVNVPROC glTexCoord1hvNV;
PFNGLTEXCOORD2HNVPROC glTexCoord2hNV;
PFNGLTEXCOORD2HVNVPROC glTexCoord2hvNV;
PFNGLTEXCOORD3HNVPROC glTexCoord3hNV;
PFNGLTEXCOORD3HVNVPROC glTexCoord3hvNV;
PFNGLTEXCOORD4HNVPROC glTexCoord4hNV;
PFNGLTEXCOORD4HVNVPROC glTexCoord4hvNV;
PFNGLMULTITEXCOORD1HNVPROC glMultiTexCoord1hNV;
PFNGLMULTITEXCOORD1HVNVPROC glMultiTexCoord1hvNV;
PFNGLMULTITEXCOORD2HNVPROC glMultiTexCoord2hNV;
PFNGLMULTITEXCOORD2HVNVPROC glMultiTexCoord2hvNV;
PFNGLMULTITEXCOORD3HNVPROC glMultiTexCoord3hNV;
PFNGLMULTITEXCOORD3HVNVPROC glMultiTexCoord3hvNV;
PFNGLMULTITEXCOORD4HNVPROC glMultiTexCoord4hNV;
PFNGLMULTITEXCOORD4HVNVPROC glMultiTexCoord4hvNV;
PFNGLFOGCOORDHNVPROC glFogCoordhNV;
PFNGLFOGCOORDHVNVPROC glFogCoordhvNV;
PFNGLSECONDARYCOLOR3HNVPROC glSecondaryColor3hNV;
PFNGLSECONDARYCOLOR3HVNVPROC glSecondaryColor3hvNV;
PFNGLVERTEXWEIGHTHNVPROC glVertexWeighthNV;
PFNGLVERTEXWEIGHTHVNVPROC glVertexWeighthvNV;
PFNGLVERTEXATTRIB1HNVPROC glVertexAttrib1hNV;
PFNGLVERTEXATTRIB1HVNVPROC glVertexAttrib1hvNV;
PFNGLVERTEXATTRIB2HNVPROC glVertexAttrib2hNV;
PFNGLVERTEXATTRIB2HVNVPROC glVertexAttrib2hvNV;
PFNGLVERTEXATTRIB3HNVPROC glVertexAttrib3hNV;
PFNGLVERTEXATTRIB3HVNVPROC glVertexAttrib3hvNV;
PFNGLVERTEXATTRIB4HNVPROC glVertexAttrib4hNV;
PFNGLVERTEXATTRIB4HVNVPROC glVertexAttrib4hvNV;
PFNGLVERTEXATTRIBS1HVNVPROC glVertexAttribs1hvNV;
PFNGLVERTEXATTRIBS2HVNVPROC glVertexAttribs2hvNV;
PFNGLVERTEXATTRIBS3HVNVPROC glVertexAttribs3hvNV;
PFNGLVERTEXATTRIBS4HVNVPROC glVertexAttribs4hvNV;

static int gleIntLoad_NV_half_float()
{
	int bIsLoaded = 1;
	glVertex2hNV = (PFNGLVERTEX2HNVPROC)gleIntGetProcAddress("glVertex2hNV");
	if(!TestPointer(glVertex2hNV)) bIsLoaded = 0;
	glVertex2hvNV = (PFNGLVERTEX2HVNVPROC)gleIntGetProcAddress("glVertex2hvNV");
	if(!TestPointer(glVertex2hvNV)) bIsLoaded = 0;
	glVertex3hNV = (PFNGLVERTEX3HNVPROC)gleIntGetProcAddress("glVertex3hNV");
	if(!TestPointer(glVertex3hNV)) bIsLoaded = 0;
	glVertex3hvNV = (PFNGLVERTEX3HVNVPROC)gleIntGetProcAddress("glVertex3hvNV");
	if(!TestPointer(glVertex3hvNV)) bIsLoaded = 0;
	glVertex4hNV = (PFNGLVERTEX4HNVPROC)gleIntGetProcAddress("glVertex4hNV");
	if(!TestPointer(glVertex4hNV)) bIsLoaded = 0;
	glVertex4hvNV = (PFNGLVERTEX4HVNVPROC)gleIntGetProcAddress("glVertex4hvNV");
	if(!TestPointer(glVertex4hvNV)) bIsLoaded = 0;
	glNormal3hNV = (PFNGLNORMAL3HNVPROC)gleIntGetProcAddress("glNormal3hNV");
	if(!TestPointer(glNormal3hNV)) bIsLoaded = 0;
	glNormal3hvNV = (PFNGLNORMAL3HVNVPROC)gleIntGetProcAddress("glNormal3hvNV");
	if(!TestPointer(glNormal3hvNV)) bIsLoaded = 0;
	glColor3hNV = (PFNGLCOLOR3HNVPROC)gleIntGetProcAddress("glColor3hNV");
	if(!TestPointer(glColor3hNV)) bIsLoaded = 0;
	glColor3hvNV = (PFNGLCOLOR3HVNVPROC)gleIntGetProcAddress("glColor3hvNV");
	if(!TestPointer(glColor3hvNV)) bIsLoaded = 0;
	glColor4hNV = (PFNGLCOLOR4HNVPROC)gleIntGetProcAddress("glColor4hNV");
	if(!TestPointer(glColor4hNV)) bIsLoaded = 0;
	glColor4hvNV = (PFNGLCOLOR4HVNVPROC)gleIntGetProcAddress("glColor4hvNV");
	if(!TestPointer(glColor4hvNV)) bIsLoaded = 0;
	glTexCoord1hNV = (PFNGLTEXCOORD1HNVPROC)gleIntGetProcAddress("glTexCoord1hNV");
	if(!TestPointer(glTexCoord1hNV)) bIsLoaded = 0;
	glTexCoord1hvNV = (PFNGLTEXCOORD1HVNVPROC)gleIntGetProcAddress("glTexCoord1hvNV");
	if(!TestPointer(glTexCoord1hvNV)) bIsLoaded = 0;
	glTexCoord2hNV = (PFNGLTEXCOORD2HNVPROC)gleIntGetProcAddress("glTexCoord2hNV");
	if(!TestPointer(glTexCoord2hNV)) bIsLoaded = 0;
	glTexCoord2hvNV = (PFNGLTEXCOORD2HVNVPROC)gleIntGetProcAddress("glTexCoord2hvNV");
	if(!TestPointer(glTexCoord2hvNV)) bIsLoaded = 0;
	glTexCoord3hNV = (PFNGLTEXCOORD3HNVPROC)gleIntGetProcAddress("glTexCoord3hNV");
	if(!TestPointer(glTexCoord3hNV)) bIsLoaded = 0;
	glTexCoord3hvNV = (PFNGLTEXCOORD3HVNVPROC)gleIntGetProcAddress("glTexCoord3hvNV");
	if(!TestPointer(glTexCoord3hvNV)) bIsLoaded = 0;
	glTexCoord4hNV = (PFNGLTEXCOORD4HNVPROC)gleIntGetProcAddress("glTexCoord4hNV");
	if(!TestPointer(glTexCoord4hNV)) bIsLoaded = 0;
	glTexCoord4hvNV = (PFNGLTEXCOORD4HVNVPROC)gleIntGetProcAddress("glTexCoord4hvNV");
	if(!TestPointer(glTexCoord4hvNV)) bIsLoaded = 0;
	glMultiTexCoord1hNV = (PFNGLMULTITEXCOORD1HNVPROC)gleIntGetProcAddress("glMultiTexCoord1hNV");
	if(!TestPointer(glMultiTexCoord1hNV)) bIsLoaded = 0;
	glMultiTexCoord1hvNV = (PFNGLMULTITEXCOORD1HVNVPROC)gleIntGetProcAddress("glMultiTexCoord1hvNV");
	if(!TestPointer(glMultiTexCoord1hvNV)) bIsLoaded = 0;
	glMultiTexCoord2hNV = (PFNGLMULTITEXCOORD2HNVPROC)gleIntGetProcAddress("glMultiTexCoord2hNV");
	if(!TestPointer(glMultiTexCoord2hNV)) bIsLoaded = 0;
	glMultiTexCoord2hvNV = (PFNGLMULTITEXCOORD2HVNVPROC)gleIntGetProcAddress("glMultiTexCoord2hvNV");
	if(!TestPointer(glMultiTexCoord2hvNV)) bIsLoaded = 0;
	glMultiTexCoord3hNV = (PFNGLMULTITEXCOORD3HNVPROC)gleIntGetProcAddress("glMultiTexCoord3hNV");
	if(!TestPointer(glMultiTexCoord3hNV)) bIsLoaded = 0;
	glMultiTexCoord3hvNV = (PFNGLMULTITEXCOORD3HVNVPROC)gleIntGetProcAddress("glMultiTexCoord3hvNV");
	if(!TestPointer(glMultiTexCoord3hvNV)) bIsLoaded = 0;
	glMultiTexCoord4hNV = (PFNGLMULTITEXCOORD4HNVPROC)gleIntGetProcAddress("glMultiTexCoord4hNV");
	if(!TestPointer(glMultiTexCoord4hNV)) bIsLoaded = 0;
	glMultiTexCoord4hvNV = (PFNGLMULTITEXCOORD4HVNVPROC)gleIntGetProcAddress("glMultiTexCoord4hvNV");
	if(!TestPointer(glMultiTexCoord4hvNV)) bIsLoaded = 0;
	glFogCoordhNV = (PFNGLFOGCOORDHNVPROC)gleIntGetProcAddress("glFogCoordhNV");
	if(!TestPointer(glFogCoordhNV)) bIsLoaded = 0;
	glFogCoordhvNV = (PFNGLFOGCOORDHVNVPROC)gleIntGetProcAddress("glFogCoordhvNV");
	if(!TestPointer(glFogCoordhvNV)) bIsLoaded = 0;
	glSecondaryColor3hNV = (PFNGLSECONDARYCOLOR3HNVPROC)gleIntGetProcAddress("glSecondaryColor3hNV");
	if(!TestPointer(glSecondaryColor3hNV)) bIsLoaded = 0;
	glSecondaryColor3hvNV = (PFNGLSECONDARYCOLOR3HVNVPROC)gleIntGetProcAddress("glSecondaryColor3hvNV");
	if(!TestPointer(glSecondaryColor3hvNV)) bIsLoaded = 0;
	glVertexWeighthNV = (PFNGLVERTEXWEIGHTHNVPROC)gleIntGetProcAddress("glVertexWeighthNV");
	if(!TestPointer(glVertexWeighthNV)) bIsLoaded = 0;
	glVertexWeighthvNV = (PFNGLVERTEXWEIGHTHVNVPROC)gleIntGetProcAddress("glVertexWeighthvNV");
	if(!TestPointer(glVertexWeighthvNV)) bIsLoaded = 0;
	glVertexAttrib1hNV = (PFNGLVERTEXATTRIB1HNVPROC)gleIntGetProcAddress("glVertexAttrib1hNV");
	if(!TestPointer(glVertexAttrib1hNV)) bIsLoaded = 0;
	glVertexAttrib1hvNV = (PFNGLVERTEXATTRIB1HVNVPROC)gleIntGetProcAddress("glVertexAttrib1hvNV");
	if(!TestPointer(glVertexAttrib1hvNV)) bIsLoaded = 0;
	glVertexAttrib2hNV = (PFNGLVERTEXATTRIB2HNVPROC)gleIntGetProcAddress("glVertexAttrib2hNV");
	if(!TestPointer(glVertexAttrib2hNV)) bIsLoaded = 0;
	glVertexAttrib2hvNV = (PFNGLVERTEXATTRIB2HVNVPROC)gleIntGetProcAddress("glVertexAttrib2hvNV");
	if(!TestPointer(glVertexAttrib2hvNV)) bIsLoaded = 0;
	glVertexAttrib3hNV = (PFNGLVERTEXATTRIB3HNVPROC)gleIntGetProcAddress("glVertexAttrib3hNV");
	if(!TestPointer(glVertexAttrib3hNV)) bIsLoaded = 0;
	glVertexAttrib3hvNV = (PFNGLVERTEXATTRIB3HVNVPROC)gleIntGetProcAddress("glVertexAttrib3hvNV");
	if(!TestPointer(glVertexAttrib3hvNV)) bIsLoaded = 0;
	glVertexAttrib4hNV = (PFNGLVERTEXATTRIB4HNVPROC)gleIntGetProcAddress("glVertexAttrib4hNV");
	if(!TestPointer(glVertexAttrib4hNV)) bIsLoaded = 0;
	glVertexAttrib4hvNV = (PFNGLVERTEXATTRIB4HVNVPROC)gleIntGetProcAddress("glVertexAttrib4hvNV");
	if(!TestPointer(glVertexAttrib4hvNV)) bIsLoaded = 0;
	glVertexAttribs1hvNV = (PFNGLVERTEXATTRIBS1HVNVPROC)gleIntGetProcAddress("glVertexAttribs1hvNV");
	if(!TestPointer(glVertexAttribs1hvNV)) bIsLoaded = 0;
	glVertexAttribs2hvNV = (PFNGLVERTEXATTRIBS2HVNVPROC)gleIntGetProcAddress("glVertexAttribs2hvNV");
	if(!TestPointer(glVertexAttribs2hvNV)) bIsLoaded = 0;
	glVertexAttribs3hvNV = (PFNGLVERTEXATTRIBS3HVNVPROC)gleIntGetProcAddress("glVertexAttribs3hvNV");
	if(!TestPointer(glVertexAttribs3hvNV)) bIsLoaded = 0;
	glVertexAttribs4hvNV = (PFNGLVERTEXATTRIBS4HVNVPROC)gleIntGetProcAddress("glVertexAttribs4hvNV");
	if(!TestPointer(glVertexAttribs4hvNV)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLGENOCCLUSIONQUERIESNVPROC)(GLsizei n, GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLDELETEOCCLUSIONQUERIESNVPROC)(GLsizei n, const GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISOCCLUSIONQUERYNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLBEGINOCCLUSIONQUERYNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLENDOCCLUSIONQUERYNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLGETOCCLUSIONQUERYIVNVPROC)(GLuint id, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETOCCLUSIONQUERYUIVNVPROC)(GLuint id, GLenum pname, GLuint *params);

PFNGLGENOCCLUSIONQUERIESNVPROC glGenOcclusionQueriesNV;
PFNGLDELETEOCCLUSIONQUERIESNVPROC glDeleteOcclusionQueriesNV;
PFNGLISOCCLUSIONQUERYNVPROC glIsOcclusionQueryNV;
PFNGLBEGINOCCLUSIONQUERYNVPROC glBeginOcclusionQueryNV;
PFNGLENDOCCLUSIONQUERYNVPROC glEndOcclusionQueryNV;
PFNGLGETOCCLUSIONQUERYIVNVPROC glGetOcclusionQueryivNV;
PFNGLGETOCCLUSIONQUERYUIVNVPROC glGetOcclusionQueryuivNV;

static int gleIntLoad_NV_occlusion_query()
{
	int bIsLoaded = 1;
	glGenOcclusionQueriesNV = (PFNGLGENOCCLUSIONQUERIESNVPROC)gleIntGetProcAddress("glGenOcclusionQueriesNV");
	if(!TestPointer(glGenOcclusionQueriesNV)) bIsLoaded = 0;
	glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC)gleIntGetProcAddress("glDeleteOcclusionQueriesNV");
	if(!TestPointer(glDeleteOcclusionQueriesNV)) bIsLoaded = 0;
	glIsOcclusionQueryNV = (PFNGLISOCCLUSIONQUERYNVPROC)gleIntGetProcAddress("glIsOcclusionQueryNV");
	if(!TestPointer(glIsOcclusionQueryNV)) bIsLoaded = 0;
	glBeginOcclusionQueryNV = (PFNGLBEGINOCCLUSIONQUERYNVPROC)gleIntGetProcAddress("glBeginOcclusionQueryNV");
	if(!TestPointer(glBeginOcclusionQueryNV)) bIsLoaded = 0;
	glEndOcclusionQueryNV = (PFNGLENDOCCLUSIONQUERYNVPROC)gleIntGetProcAddress("glEndOcclusionQueryNV");
	if(!TestPointer(glEndOcclusionQueryNV)) bIsLoaded = 0;
	glGetOcclusionQueryivNV = (PFNGLGETOCCLUSIONQUERYIVNVPROC)gleIntGetProcAddress("glGetOcclusionQueryivNV");
	if(!TestPointer(glGetOcclusionQueryivNV)) bIsLoaded = 0;
	glGetOcclusionQueryuivNV = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)gleIntGetProcAddress("glGetOcclusionQueryuivNV");
	if(!TestPointer(glGetOcclusionQueryuivNV)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)(GLenum target, GLuint buffer, GLuint index, GLsizei count, const GLuint *params);

PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC glProgramBufferParametersfvNV;
PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC glProgramBufferParametersIivNV;
PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC glProgramBufferParametersIuivNV;

static int gleIntLoad_NV_parameter_buffer_object()
{
	int bIsLoaded = 1;
	glProgramBufferParametersfvNV = (PFNGLPROGRAMBUFFERPARAMETERSFVNVPROC)gleIntGetProcAddress("glProgramBufferParametersfvNV");
	if(!TestPointer(glProgramBufferParametersfvNV)) bIsLoaded = 0;
	glProgramBufferParametersIivNV = (PFNGLPROGRAMBUFFERPARAMETERSIIVNVPROC)gleIntGetProcAddress("glProgramBufferParametersIivNV");
	if(!TestPointer(glProgramBufferParametersIivNV)) bIsLoaded = 0;
	glProgramBufferParametersIuivNV = (PFNGLPROGRAMBUFFERPARAMETERSIUIVNVPROC)gleIntGetProcAddress("glProgramBufferParametersIuivNV");
	if(!TestPointer(glProgramBufferParametersIuivNV)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPIXELDATARANGENVPROC)(GLenum target, GLsizei length, GLvoid *pointer);
typedef void (GLE_FUNCPTR * PFNGLFLUSHPIXELDATARANGENVPROC)(GLenum target);

PFNGLPIXELDATARANGENVPROC glPixelDataRangeNV;
PFNGLFLUSHPIXELDATARANGENVPROC glFlushPixelDataRangeNV;

static int gleIntLoad_NV_pixel_data_range()
{
	int bIsLoaded = 1;
	glPixelDataRangeNV = (PFNGLPIXELDATARANGENVPROC)gleIntGetProcAddress("glPixelDataRangeNV");
	if(!TestPointer(glPixelDataRangeNV)) bIsLoaded = 0;
	glFlushPixelDataRangeNV = (PFNGLFLUSHPIXELDATARANGENVPROC)gleIntGetProcAddress("glFlushPixelDataRangeNV");
	if(!TestPointer(glFlushPixelDataRangeNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERINVPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIVNVPROC)(GLenum pname, const GLint *params);

PFNGLPOINTPARAMETERINVPROC glPointParameteriNV;
PFNGLPOINTPARAMETERIVNVPROC glPointParameterivNV;

static int gleIntLoad_NV_point_sprite()
{
	int bIsLoaded = 1;
	glPointParameteriNV = (PFNGLPOINTPARAMETERINVPROC)gleIntGetProcAddress("glPointParameteriNV");
	if(!TestPointer(glPointParameteriNV)) bIsLoaded = 0;
	glPointParameterivNV = (PFNGLPOINTPARAMETERIVNVPROC)gleIntGetProcAddress("glPointParameterivNV");
	if(!TestPointer(glPointParameterivNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPRESENTFRAMEKEYEDNVPROC)(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1);
typedef void (GLE_FUNCPTR * PFNGLPRESENTFRAMEDUALFILLNVPROC)(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOIVNVPROC)(GLuint video_slot, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOUIVNVPROC)(GLuint video_slot, GLenum pname, GLuint *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOI64VNVPROC)(GLuint video_slot, GLenum pname, GLint64EXT *params);
typedef void (GLE_FUNCPTR * PFNGLGETVIDEOUI64VNVPROC)(GLuint video_slot, GLenum pname, GLuint64EXT *params);

PFNGLPRESENTFRAMEKEYEDNVPROC glPresentFrameKeyedNV;
PFNGLPRESENTFRAMEDUALFILLNVPROC glPresentFrameDualFillNV;
PFNGLGETVIDEOIVNVPROC glGetVideoivNV;
PFNGLGETVIDEOUIVNVPROC glGetVideouivNV;
PFNGLGETVIDEOI64VNVPROC glGetVideoi64vNV;
PFNGLGETVIDEOUI64VNVPROC glGetVideoui64vNV;

static int gleIntLoad_NV_present_video()
{
	int bIsLoaded = 1;
	glPresentFrameKeyedNV = (PFNGLPRESENTFRAMEKEYEDNVPROC)gleIntGetProcAddress("glPresentFrameKeyedNV");
	if(!TestPointer(glPresentFrameKeyedNV)) bIsLoaded = 0;
	glPresentFrameDualFillNV = (PFNGLPRESENTFRAMEDUALFILLNVPROC)gleIntGetProcAddress("glPresentFrameDualFillNV");
	if(!TestPointer(glPresentFrameDualFillNV)) bIsLoaded = 0;
	glGetVideoivNV = (PFNGLGETVIDEOIVNVPROC)gleIntGetProcAddress("glGetVideoivNV");
	if(!TestPointer(glGetVideoivNV)) bIsLoaded = 0;
	glGetVideouivNV = (PFNGLGETVIDEOUIVNVPROC)gleIntGetProcAddress("glGetVideouivNV");
	if(!TestPointer(glGetVideouivNV)) bIsLoaded = 0;
	glGetVideoi64vNV = (PFNGLGETVIDEOI64VNVPROC)gleIntGetProcAddress("glGetVideoi64vNV");
	if(!TestPointer(glGetVideoi64vNV)) bIsLoaded = 0;
	glGetVideoui64vNV = (PFNGLGETVIDEOUI64VNVPROC)gleIntGetProcAddress("glGetVideoui64vNV");
	if(!TestPointer(glGetVideoui64vNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTINDEXNVPROC)(GLuint index);

PFNGLPRIMITIVERESTARTNVPROC glPrimitiveRestartNV;
PFNGLPRIMITIVERESTARTINDEXNVPROC glPrimitiveRestartIndexNV;

static int gleIntLoad_NV_primitive_restart()
{
	int bIsLoaded = 1;
	glPrimitiveRestartNV = (PFNGLPRIMITIVERESTARTNVPROC)gleIntGetProcAddress("glPrimitiveRestartNV");
	if(!TestPointer(glPrimitiveRestartNV)) bIsLoaded = 0;
	glPrimitiveRestartIndexNV = (PFNGLPRIMITIVERESTARTINDEXNVPROC)gleIntGetProcAddress("glPrimitiveRestartIndexNV");
	if(!TestPointer(glPrimitiveRestartIndexNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
PFNGLCOMBINERPARAMETERFNVPROC glCombinerParameterfNV;
PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV;
PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;
PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV;
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV;
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV;

static int gleIntLoad_NV_register_combiners()
{
	int bIsLoaded = 1;
	glCombinerParameterfvNV = (PFNGLCOMBINERPARAMETERFVNVPROC)gleIntGetProcAddress("glCombinerParameterfvNV");
	if(!TestPointer(glCombinerParameterfvNV)) bIsLoaded = 0;
	glCombinerParameterfNV = (PFNGLCOMBINERPARAMETERFNVPROC)gleIntGetProcAddress("glCombinerParameterfNV");
	if(!TestPointer(glCombinerParameterfNV)) bIsLoaded = 0;
	glCombinerParameterivNV = (PFNGLCOMBINERPARAMETERIVNVPROC)gleIntGetProcAddress("glCombinerParameterivNV");
	if(!TestPointer(glCombinerParameterivNV)) bIsLoaded = 0;
	glCombinerParameteriNV = (PFNGLCOMBINERPARAMETERINVPROC)gleIntGetProcAddress("glCombinerParameteriNV");
	if(!TestPointer(glCombinerParameteriNV)) bIsLoaded = 0;
	glCombinerInputNV = (PFNGLCOMBINERINPUTNVPROC)gleIntGetProcAddress("glCombinerInputNV");
	if(!TestPointer(glCombinerInputNV)) bIsLoaded = 0;
	glCombinerOutputNV = (PFNGLCOMBINEROUTPUTNVPROC)gleIntGetProcAddress("glCombinerOutputNV");
	if(!TestPointer(glCombinerOutputNV)) bIsLoaded = 0;
	glFinalCombinerInputNV = (PFNGLFINALCOMBINERINPUTNVPROC)gleIntGetProcAddress("glFinalCombinerInputNV");
	if(!TestPointer(glFinalCombinerInputNV)) bIsLoaded = 0;
	glGetCombinerInputParameterfvNV = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)gleIntGetProcAddress("glGetCombinerInputParameterfvNV");
	if(!TestPointer(glGetCombinerInputParameterfvNV)) bIsLoaded = 0;
	glGetCombinerInputParameterivNV = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)gleIntGetProcAddress("glGetCombinerInputParameterivNV");
	if(!TestPointer(glGetCombinerInputParameterivNV)) bIsLoaded = 0;
	glGetCombinerOutputParameterfvNV = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)gleIntGetProcAddress("glGetCombinerOutputParameterfvNV");
	if(!TestPointer(glGetCombinerOutputParameterfvNV)) bIsLoaded = 0;
	glGetCombinerOutputParameterivNV = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)gleIntGetProcAddress("glGetCombinerOutputParameterivNV");
	if(!TestPointer(glGetCombinerOutputParameterivNV)) bIsLoaded = 0;
	glGetFinalCombinerInputParameterfvNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)gleIntGetProcAddress("glGetFinalCombinerInputParameterfvNV");
	if(!TestPointer(glGetFinalCombinerInputParameterfvNV)) bIsLoaded = 0;
	glGetFinalCombinerInputParameterivNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)gleIntGetProcAddress("glGetFinalCombinerInputParameterivNV");
	if(!TestPointer(glGetFinalCombinerInputParameterivNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum stage, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)(GLenum stage, GLenum pname, GLfloat *params);

PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV;
PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC glGetCombinerStageParameterfvNV;

static int gleIntLoad_NV_register_combiners2()
{
	int bIsLoaded = 1;
	glCombinerStageParameterfvNV = (PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)gleIntGetProcAddress("glCombinerStageParameterfvNV");
	if(!TestPointer(glCombinerStageParameterfvNV)) bIsLoaded = 0;
	glGetCombinerStageParameterfvNV = (PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)gleIntGetProcAddress("glGetCombinerStageParameterfvNV");
	if(!TestPointer(glGetCombinerStageParameterfvNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLMAKEBUFFERRESIDENTNVPROC glMakeBufferResidentNV;
PFNGLMAKEBUFFERNONRESIDENTNVPROC glMakeBufferNonResidentNV;
PFNGLISBUFFERRESIDENTNVPROC glIsBufferResidentNV;
PFNGLMAKENAMEDBUFFERRESIDENTNVPROC glMakeNamedBufferResidentNV;
PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC glMakeNamedBufferNonResidentNV;
PFNGLISNAMEDBUFFERRESIDENTNVPROC glIsNamedBufferResidentNV;
PFNGLGETBUFFERPARAMETERUI64VNVPROC glGetBufferParameterui64vNV;
PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC glGetNamedBufferParameterui64vNV;
PFNGLGETINTEGERUI64VNVPROC glGetIntegerui64vNV;
PFNGLUNIFORMUI64NVPROC glUniformui64NV;
PFNGLUNIFORMUI64VNVPROC glUniformui64vNV;
PFNGLGETUNIFORMUI64VNVPROC glGetUniformui64vNV;
PFNGLPROGRAMUNIFORMUI64NVPROC glProgramUniformui64NV;
PFNGLPROGRAMUNIFORMUI64VNVPROC glProgramUniformui64vNV;

static int gleIntLoad_NV_shader_buffer_load()
{
	int bIsLoaded = 1;
	glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)gleIntGetProcAddress("glMakeBufferResidentNV");
	if(!TestPointer(glMakeBufferResidentNV)) bIsLoaded = 0;
	glMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC)gleIntGetProcAddress("glMakeBufferNonResidentNV");
	if(!TestPointer(glMakeBufferNonResidentNV)) bIsLoaded = 0;
	glIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC)gleIntGetProcAddress("glIsBufferResidentNV");
	if(!TestPointer(glIsBufferResidentNV)) bIsLoaded = 0;
	glMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)gleIntGetProcAddress("glMakeNamedBufferResidentNV");
	if(!TestPointer(glMakeNamedBufferResidentNV)) bIsLoaded = 0;
	glMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)gleIntGetProcAddress("glMakeNamedBufferNonResidentNV");
	if(!TestPointer(glMakeNamedBufferNonResidentNV)) bIsLoaded = 0;
	glIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC)gleIntGetProcAddress("glIsNamedBufferResidentNV");
	if(!TestPointer(glIsNamedBufferResidentNV)) bIsLoaded = 0;
	glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)gleIntGetProcAddress("glGetBufferParameterui64vNV");
	if(!TestPointer(glGetBufferParameterui64vNV)) bIsLoaded = 0;
	glGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)gleIntGetProcAddress("glGetNamedBufferParameterui64vNV");
	if(!TestPointer(glGetNamedBufferParameterui64vNV)) bIsLoaded = 0;
	glGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC)gleIntGetProcAddress("glGetIntegerui64vNV");
	if(!TestPointer(glGetIntegerui64vNV)) bIsLoaded = 0;
	glUniformui64NV = (PFNGLUNIFORMUI64NVPROC)gleIntGetProcAddress("glUniformui64NV");
	if(!TestPointer(glUniformui64NV)) bIsLoaded = 0;
	glUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC)gleIntGetProcAddress("glUniformui64vNV");
	if(!TestPointer(glUniformui64vNV)) bIsLoaded = 0;
	glGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC)gleIntGetProcAddress("glGetUniformui64vNV");
	if(!TestPointer(glGetUniformui64vNV)) bIsLoaded = 0;
	glProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC)gleIntGetProcAddress("glProgramUniformui64NV");
	if(!TestPointer(glProgramUniformui64NV)) bIsLoaded = 0;
	glProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC)gleIntGetProcAddress("glProgramUniformui64vNV");
	if(!TestPointer(glProgramUniformui64vNV)) bIsLoaded = 0;
	return bIsLoaded;
}




typedef void (GLE_FUNCPTR * PFNGLTEXTUREBARRIERNVPROC)();

PFNGLTEXTUREBARRIERNVPROC glTextureBarrierNV;

static int gleIntLoad_NV_texture_barrier()
{
	int bIsLoaded = 1;
	glTextureBarrierNV = (PFNGLTEXTUREBARRIERNVPROC)gleIntGetProcAddress("glTextureBarrierNV");
	if(!TestPointer(glTextureBarrierNV)) bIsLoaded = 0;
	return bIsLoaded;
}







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

PFNGLBEGINTRANSFORMFEEDBACKNVPROC glBeginTransformFeedbackNV;
PFNGLENDTRANSFORMFEEDBACKNVPROC glEndTransformFeedbackNV;
PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC glTransformFeedbackAttribsNV;
PFNGLBINDBUFFERRANGENVPROC glBindBufferRangeNV;
PFNGLBINDBUFFEROFFSETNVPROC glBindBufferOffsetNV;
PFNGLBINDBUFFERBASENVPROC glBindBufferBaseNV;
PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC glTransformFeedbackVaryingsNV;
PFNGLACTIVEVARYINGNVPROC glActiveVaryingNV;
PFNGLGETVARYINGLOCATIONNVPROC glGetVaryingLocationNV;
PFNGLGETACTIVEVARYINGNVPROC glGetActiveVaryingNV;
PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC glGetTransformFeedbackVaryingNV;
PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC glTransformFeedbackStreamAttribsNV;

static int gleIntLoad_NV_transform_feedback()
{
	int bIsLoaded = 1;
	glBeginTransformFeedbackNV = (PFNGLBEGINTRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glBeginTransformFeedbackNV");
	if(!TestPointer(glBeginTransformFeedbackNV)) bIsLoaded = 0;
	glEndTransformFeedbackNV = (PFNGLENDTRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glEndTransformFeedbackNV");
	if(!TestPointer(glEndTransformFeedbackNV)) bIsLoaded = 0;
	glTransformFeedbackAttribsNV = (PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)gleIntGetProcAddress("glTransformFeedbackAttribsNV");
	if(!TestPointer(glTransformFeedbackAttribsNV)) bIsLoaded = 0;
	glBindBufferRangeNV = (PFNGLBINDBUFFERRANGENVPROC)gleIntGetProcAddress("glBindBufferRangeNV");
	if(!TestPointer(glBindBufferRangeNV)) bIsLoaded = 0;
	glBindBufferOffsetNV = (PFNGLBINDBUFFEROFFSETNVPROC)gleIntGetProcAddress("glBindBufferOffsetNV");
	if(!TestPointer(glBindBufferOffsetNV)) bIsLoaded = 0;
	glBindBufferBaseNV = (PFNGLBINDBUFFERBASENVPROC)gleIntGetProcAddress("glBindBufferBaseNV");
	if(!TestPointer(glBindBufferBaseNV)) bIsLoaded = 0;
	glTransformFeedbackVaryingsNV = (PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)gleIntGetProcAddress("glTransformFeedbackVaryingsNV");
	if(!TestPointer(glTransformFeedbackVaryingsNV)) bIsLoaded = 0;
	glActiveVaryingNV = (PFNGLACTIVEVARYINGNVPROC)gleIntGetProcAddress("glActiveVaryingNV");
	if(!TestPointer(glActiveVaryingNV)) bIsLoaded = 0;
	glGetVaryingLocationNV = (PFNGLGETVARYINGLOCATIONNVPROC)gleIntGetProcAddress("glGetVaryingLocationNV");
	if(!TestPointer(glGetVaryingLocationNV)) bIsLoaded = 0;
	glGetActiveVaryingNV = (PFNGLGETACTIVEVARYINGNVPROC)gleIntGetProcAddress("glGetActiveVaryingNV");
	if(!TestPointer(glGetActiveVaryingNV)) bIsLoaded = 0;
	glGetTransformFeedbackVaryingNV = (PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)gleIntGetProcAddress("glGetTransformFeedbackVaryingNV");
	if(!TestPointer(glGetTransformFeedbackVaryingNV)) bIsLoaded = 0;
	glTransformFeedbackStreamAttribsNV = (PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)gleIntGetProcAddress("glTransformFeedbackStreamAttribsNV");
	if(!TestPointer(glTransformFeedbackStreamAttribsNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLBINDTRANSFORMFEEDBACKNVPROC)(GLenum target, GLuint id);
typedef void (GLE_FUNCPTR * PFNGLDELETETRANSFORMFEEDBACKSNVPROC)(GLsizei n, const GLuint *ids);
typedef void (GLE_FUNCPTR * PFNGLGENTRANSFORMFEEDBACKSNVPROC)(GLsizei n, GLuint *ids);
typedef GLboolean (GLE_FUNCPTR * PFNGLISTRANSFORMFEEDBACKNVPROC)(GLuint id);
typedef void (GLE_FUNCPTR * PFNGLPAUSETRANSFORMFEEDBACKNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLRESUMETRANSFORMFEEDBACKNVPROC)();
typedef void (GLE_FUNCPTR * PFNGLDRAWTRANSFORMFEEDBACKNVPROC)(GLenum mode, GLuint id);

PFNGLBINDTRANSFORMFEEDBACKNVPROC glBindTransformFeedbackNV;
PFNGLDELETETRANSFORMFEEDBACKSNVPROC glDeleteTransformFeedbacksNV;
PFNGLGENTRANSFORMFEEDBACKSNVPROC glGenTransformFeedbacksNV;
PFNGLISTRANSFORMFEEDBACKNVPROC glIsTransformFeedbackNV;
PFNGLPAUSETRANSFORMFEEDBACKNVPROC glPauseTransformFeedbackNV;
PFNGLRESUMETRANSFORMFEEDBACKNVPROC glResumeTransformFeedbackNV;
PFNGLDRAWTRANSFORMFEEDBACKNVPROC glDrawTransformFeedbackNV;

static int gleIntLoad_NV_transform_feedback2()
{
	int bIsLoaded = 1;
	glBindTransformFeedbackNV = (PFNGLBINDTRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glBindTransformFeedbackNV");
	if(!TestPointer(glBindTransformFeedbackNV)) bIsLoaded = 0;
	glDeleteTransformFeedbacksNV = (PFNGLDELETETRANSFORMFEEDBACKSNVPROC)gleIntGetProcAddress("glDeleteTransformFeedbacksNV");
	if(!TestPointer(glDeleteTransformFeedbacksNV)) bIsLoaded = 0;
	glGenTransformFeedbacksNV = (PFNGLGENTRANSFORMFEEDBACKSNVPROC)gleIntGetProcAddress("glGenTransformFeedbacksNV");
	if(!TestPointer(glGenTransformFeedbacksNV)) bIsLoaded = 0;
	glIsTransformFeedbackNV = (PFNGLISTRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glIsTransformFeedbackNV");
	if(!TestPointer(glIsTransformFeedbackNV)) bIsLoaded = 0;
	glPauseTransformFeedbackNV = (PFNGLPAUSETRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glPauseTransformFeedbackNV");
	if(!TestPointer(glPauseTransformFeedbackNV)) bIsLoaded = 0;
	glResumeTransformFeedbackNV = (PFNGLRESUMETRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glResumeTransformFeedbackNV");
	if(!TestPointer(glResumeTransformFeedbackNV)) bIsLoaded = 0;
	glDrawTransformFeedbackNV = (PFNGLDRAWTRANSFORMFEEDBACKNVPROC)gleIntGetProcAddress("glDrawTransformFeedbackNV");
	if(!TestPointer(glDrawTransformFeedbackNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLVDPAUINITNVPROC glVDPAUInitNV;
PFNGLVDPAUFININVPROC glVDPAUFiniNV;
PFNGLVDPAUREGISTERVIDEOSURFACENVPROC glVDPAURegisterVideoSurfaceNV;
PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC glVDPAURegisterOutputSurfaceNV;
PFNGLVDPAUISSURFACENVPROC glVDPAUIsSurfaceNV;
PFNGLVDPAUUNREGISTERSURFACENVPROC glVDPAUUnregisterSurfaceNV;
PFNGLVDPAUGETSURFACEIVNVPROC glVDPAUGetSurfaceivNV;
PFNGLVDPAUSURFACEACCESSNVPROC glVDPAUSurfaceAccessNV;
PFNGLVDPAUMAPSURFACESNVPROC glVDPAUMapSurfacesNV;
PFNGLVDPAUUNMAPSURFACESNVPROC glVDPAUUnmapSurfacesNV;

static int gleIntLoad_NV_vdpau_interop()
{
	int bIsLoaded = 1;
	glVDPAUInitNV = (PFNGLVDPAUINITNVPROC)gleIntGetProcAddress("glVDPAUInitNV");
	if(!TestPointer(glVDPAUInitNV)) bIsLoaded = 0;
	glVDPAUFiniNV = (PFNGLVDPAUFININVPROC)gleIntGetProcAddress("glVDPAUFiniNV");
	if(!TestPointer(glVDPAUFiniNV)) bIsLoaded = 0;
	glVDPAURegisterVideoSurfaceNV = (PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)gleIntGetProcAddress("glVDPAURegisterVideoSurfaceNV");
	if(!TestPointer(glVDPAURegisterVideoSurfaceNV)) bIsLoaded = 0;
	glVDPAURegisterOutputSurfaceNV = (PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)gleIntGetProcAddress("glVDPAURegisterOutputSurfaceNV");
	if(!TestPointer(glVDPAURegisterOutputSurfaceNV)) bIsLoaded = 0;
	glVDPAUIsSurfaceNV = (PFNGLVDPAUISSURFACENVPROC)gleIntGetProcAddress("glVDPAUIsSurfaceNV");
	if(!TestPointer(glVDPAUIsSurfaceNV)) bIsLoaded = 0;
	glVDPAUUnregisterSurfaceNV = (PFNGLVDPAUUNREGISTERSURFACENVPROC)gleIntGetProcAddress("glVDPAUUnregisterSurfaceNV");
	if(!TestPointer(glVDPAUUnregisterSurfaceNV)) bIsLoaded = 0;
	glVDPAUGetSurfaceivNV = (PFNGLVDPAUGETSURFACEIVNVPROC)gleIntGetProcAddress("glVDPAUGetSurfaceivNV");
	if(!TestPointer(glVDPAUGetSurfaceivNV)) bIsLoaded = 0;
	glVDPAUSurfaceAccessNV = (PFNGLVDPAUSURFACEACCESSNVPROC)gleIntGetProcAddress("glVDPAUSurfaceAccessNV");
	if(!TestPointer(glVDPAUSurfaceAccessNV)) bIsLoaded = 0;
	glVDPAUMapSurfacesNV = (PFNGLVDPAUMAPSURFACESNVPROC)gleIntGetProcAddress("glVDPAUMapSurfacesNV");
	if(!TestPointer(glVDPAUMapSurfacesNV)) bIsLoaded = 0;
	glVDPAUUnmapSurfacesNV = (PFNGLVDPAUUNMAPSURFACESNVPROC)gleIntGetProcAddress("glVDPAUUnmapSurfacesNV");
	if(!TestPointer(glVDPAUUnmapSurfacesNV)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLFLUSHVERTEXARRAYRANGENVPROC)();
typedef void (GLE_FUNCPTR * PFNGLVERTEXARRAYRANGENVPROC)(GLsizei length, const GLvoid *pointer);

PFNGLFLUSHVERTEXARRAYRANGENVPROC glFlushVertexArrayRangeNV;
PFNGLVERTEXARRAYRANGENVPROC glVertexArrayRangeNV;

static int gleIntLoad_NV_vertex_array_range()
{
	int bIsLoaded = 1;
	glFlushVertexArrayRangeNV = (PFNGLFLUSHVERTEXARRAYRANGENVPROC)gleIntGetProcAddress("glFlushVertexArrayRangeNV");
	if(!TestPointer(glFlushVertexArrayRangeNV)) bIsLoaded = 0;
	glVertexArrayRangeNV = (PFNGLVERTEXARRAYRANGENVPROC)gleIntGetProcAddress("glVertexArrayRangeNV");
	if(!TestPointer(glVertexArrayRangeNV)) bIsLoaded = 0;
	return bIsLoaded;
}

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

PFNGLVERTEXATTRIBL1I64NVPROC glVertexAttribL1i64NV;
PFNGLVERTEXATTRIBL2I64NVPROC glVertexAttribL2i64NV;
PFNGLVERTEXATTRIBL3I64NVPROC glVertexAttribL3i64NV;
PFNGLVERTEXATTRIBL4I64NVPROC glVertexAttribL4i64NV;
PFNGLVERTEXATTRIBL1I64VNVPROC glVertexAttribL1i64vNV;
PFNGLVERTEXATTRIBL2I64VNVPROC glVertexAttribL2i64vNV;
PFNGLVERTEXATTRIBL3I64VNVPROC glVertexAttribL3i64vNV;
PFNGLVERTEXATTRIBL4I64VNVPROC glVertexAttribL4i64vNV;
PFNGLVERTEXATTRIBL1UI64NVPROC glVertexAttribL1ui64NV;
PFNGLVERTEXATTRIBL2UI64NVPROC glVertexAttribL2ui64NV;
PFNGLVERTEXATTRIBL3UI64NVPROC glVertexAttribL3ui64NV;
PFNGLVERTEXATTRIBL4UI64NVPROC glVertexAttribL4ui64NV;
PFNGLVERTEXATTRIBL1UI64VNVPROC glVertexAttribL1ui64vNV;
PFNGLVERTEXATTRIBL2UI64VNVPROC glVertexAttribL2ui64vNV;
PFNGLVERTEXATTRIBL3UI64VNVPROC glVertexAttribL3ui64vNV;
PFNGLVERTEXATTRIBL4UI64VNVPROC glVertexAttribL4ui64vNV;
PFNGLGETVERTEXATTRIBLI64VNVPROC glGetVertexAttribLi64vNV;
PFNGLGETVERTEXATTRIBLUI64VNVPROC glGetVertexAttribLui64vNV;
PFNGLVERTEXATTRIBLFORMATNVPROC glVertexAttribLFormatNV;

static int gleIntLoad_NV_vertex_attrib_integer_64bit()
{
	int bIsLoaded = 1;
	glVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC)gleIntGetProcAddress("glVertexAttribL1i64NV");
	if(!TestPointer(glVertexAttribL1i64NV)) bIsLoaded = 0;
	glVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC)gleIntGetProcAddress("glVertexAttribL2i64NV");
	if(!TestPointer(glVertexAttribL2i64NV)) bIsLoaded = 0;
	glVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC)gleIntGetProcAddress("glVertexAttribL3i64NV");
	if(!TestPointer(glVertexAttribL3i64NV)) bIsLoaded = 0;
	glVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC)gleIntGetProcAddress("glVertexAttribL4i64NV");
	if(!TestPointer(glVertexAttribL4i64NV)) bIsLoaded = 0;
	glVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC)gleIntGetProcAddress("glVertexAttribL1i64vNV");
	if(!TestPointer(glVertexAttribL1i64vNV)) bIsLoaded = 0;
	glVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC)gleIntGetProcAddress("glVertexAttribL2i64vNV");
	if(!TestPointer(glVertexAttribL2i64vNV)) bIsLoaded = 0;
	glVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC)gleIntGetProcAddress("glVertexAttribL3i64vNV");
	if(!TestPointer(glVertexAttribL3i64vNV)) bIsLoaded = 0;
	glVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC)gleIntGetProcAddress("glVertexAttribL4i64vNV");
	if(!TestPointer(glVertexAttribL4i64vNV)) bIsLoaded = 0;
	glVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC)gleIntGetProcAddress("glVertexAttribL1ui64NV");
	if(!TestPointer(glVertexAttribL1ui64NV)) bIsLoaded = 0;
	glVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC)gleIntGetProcAddress("glVertexAttribL2ui64NV");
	if(!TestPointer(glVertexAttribL2ui64NV)) bIsLoaded = 0;
	glVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC)gleIntGetProcAddress("glVertexAttribL3ui64NV");
	if(!TestPointer(glVertexAttribL3ui64NV)) bIsLoaded = 0;
	glVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC)gleIntGetProcAddress("glVertexAttribL4ui64NV");
	if(!TestPointer(glVertexAttribL4ui64NV)) bIsLoaded = 0;
	glVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC)gleIntGetProcAddress("glVertexAttribL1ui64vNV");
	if(!TestPointer(glVertexAttribL1ui64vNV)) bIsLoaded = 0;
	glVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC)gleIntGetProcAddress("glVertexAttribL2ui64vNV");
	if(!TestPointer(glVertexAttribL2ui64vNV)) bIsLoaded = 0;
	glVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC)gleIntGetProcAddress("glVertexAttribL3ui64vNV");
	if(!TestPointer(glVertexAttribL3ui64vNV)) bIsLoaded = 0;
	glVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC)gleIntGetProcAddress("glVertexAttribL4ui64vNV");
	if(!TestPointer(glVertexAttribL4ui64vNV)) bIsLoaded = 0;
	glGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC)gleIntGetProcAddress("glGetVertexAttribLi64vNV");
	if(!TestPointer(glGetVertexAttribLi64vNV)) bIsLoaded = 0;
	glGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC)gleIntGetProcAddress("glGetVertexAttribLui64vNV");
	if(!TestPointer(glGetVertexAttribLui64vNV)) bIsLoaded = 0;
	glVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC)gleIntGetProcAddress("glVertexAttribLFormatNV");
	if(!TestPointer(glVertexAttribLFormatNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLBUFFERADDRESSRANGENVPROC glBufferAddressRangeNV;
PFNGLVERTEXFORMATNVPROC glVertexFormatNV;
PFNGLNORMALFORMATNVPROC glNormalFormatNV;
PFNGLCOLORFORMATNVPROC glColorFormatNV;
PFNGLINDEXFORMATNVPROC glIndexFormatNV;
PFNGLTEXCOORDFORMATNVPROC glTexCoordFormatNV;
PFNGLEDGEFLAGFORMATNVPROC glEdgeFlagFormatNV;
PFNGLSECONDARYCOLORFORMATNVPROC glSecondaryColorFormatNV;
PFNGLFOGCOORDFORMATNVPROC glFogCoordFormatNV;
PFNGLVERTEXATTRIBFORMATNVPROC glVertexAttribFormatNV;
PFNGLVERTEXATTRIBIFORMATNVPROC glVertexAttribIFormatNV;
PFNGLGETINTEGERUI64I_VNVPROC glGetIntegerui64i_vNV;

static int gleIntLoad_NV_vertex_buffer_unified_memory()
{
	int bIsLoaded = 1;
	glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)gleIntGetProcAddress("glBufferAddressRangeNV");
	if(!TestPointer(glBufferAddressRangeNV)) bIsLoaded = 0;
	glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)gleIntGetProcAddress("glVertexFormatNV");
	if(!TestPointer(glVertexFormatNV)) bIsLoaded = 0;
	glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)gleIntGetProcAddress("glNormalFormatNV");
	if(!TestPointer(glNormalFormatNV)) bIsLoaded = 0;
	glColorFormatNV = (PFNGLCOLORFORMATNVPROC)gleIntGetProcAddress("glColorFormatNV");
	if(!TestPointer(glColorFormatNV)) bIsLoaded = 0;
	glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)gleIntGetProcAddress("glIndexFormatNV");
	if(!TestPointer(glIndexFormatNV)) bIsLoaded = 0;
	glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)gleIntGetProcAddress("glTexCoordFormatNV");
	if(!TestPointer(glTexCoordFormatNV)) bIsLoaded = 0;
	glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)gleIntGetProcAddress("glEdgeFlagFormatNV");
	if(!TestPointer(glEdgeFlagFormatNV)) bIsLoaded = 0;
	glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)gleIntGetProcAddress("glSecondaryColorFormatNV");
	if(!TestPointer(glSecondaryColorFormatNV)) bIsLoaded = 0;
	glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)gleIntGetProcAddress("glFogCoordFormatNV");
	if(!TestPointer(glFogCoordFormatNV)) bIsLoaded = 0;
	glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)gleIntGetProcAddress("glVertexAttribFormatNV");
	if(!TestPointer(glVertexAttribFormatNV)) bIsLoaded = 0;
	glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)gleIntGetProcAddress("glVertexAttribIFormatNV");
	if(!TestPointer(glVertexAttribIFormatNV)) bIsLoaded = 0;
	glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)gleIntGetProcAddress("glGetIntegerui64i_vNV");
	if(!TestPointer(glGetIntegerui64i_vNV)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLAREPROGRAMSRESIDENTNVPROC glAreProgramsResidentNV;
PFNGLBINDPROGRAMNVPROC glBindProgramNV;
PFNGLDELETEPROGRAMSNVPROC glDeleteProgramsNV;
PFNGLEXECUTEPROGRAMNVPROC glExecuteProgramNV;
PFNGLGENPROGRAMSNVPROC glGenProgramsNV;
PFNGLGETPROGRAMPARAMETERDVNVPROC glGetProgramParameterdvNV;
PFNGLGETPROGRAMPARAMETERFVNVPROC glGetProgramParameterfvNV;
PFNGLGETPROGRAMIVNVPROC glGetProgramivNV;
PFNGLGETPROGRAMSTRINGNVPROC glGetProgramStringNV;
PFNGLGETTRACKMATRIXIVNVPROC glGetTrackMatrixivNV;
PFNGLGETVERTEXATTRIBDVNVPROC glGetVertexAttribdvNV;
PFNGLGETVERTEXATTRIBFVNVPROC glGetVertexAttribfvNV;
PFNGLGETVERTEXATTRIBIVNVPROC glGetVertexAttribivNV;
PFNGLGETVERTEXATTRIBPOINTERVNVPROC glGetVertexAttribPointervNV;
PFNGLISPROGRAMNVPROC glIsProgramNV;
PFNGLLOADPROGRAMNVPROC glLoadProgramNV;
PFNGLPROGRAMPARAMETER4DNVPROC glProgramParameter4dNV;
PFNGLPROGRAMPARAMETER4DVNVPROC glProgramParameter4dvNV;
PFNGLPROGRAMPARAMETER4FNVPROC glProgramParameter4fNV;
PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV;
PFNGLPROGRAMPARAMETERS4DVNVPROC glProgramParameters4dvNV;
PFNGLPROGRAMPARAMETERS4FVNVPROC glProgramParameters4fvNV;
PFNGLREQUESTRESIDENTPROGRAMSNVPROC glRequestResidentProgramsNV;
PFNGLTRACKMATRIXNVPROC glTrackMatrixNV;
PFNGLVERTEXATTRIBPOINTERNVPROC glVertexAttribPointerNV;
PFNGLVERTEXATTRIB1DNVPROC glVertexAttrib1dNV;
PFNGLVERTEXATTRIB1DVNVPROC glVertexAttrib1dvNV;
PFNGLVERTEXATTRIB1FNVPROC glVertexAttrib1fNV;
PFNGLVERTEXATTRIB1FVNVPROC glVertexAttrib1fvNV;
PFNGLVERTEXATTRIB1SNVPROC glVertexAttrib1sNV;
PFNGLVERTEXATTRIB1SVNVPROC glVertexAttrib1svNV;
PFNGLVERTEXATTRIB2DNVPROC glVertexAttrib2dNV;
PFNGLVERTEXATTRIB2DVNVPROC glVertexAttrib2dvNV;
PFNGLVERTEXATTRIB2FNVPROC glVertexAttrib2fNV;
PFNGLVERTEXATTRIB2FVNVPROC glVertexAttrib2fvNV;
PFNGLVERTEXATTRIB2SNVPROC glVertexAttrib2sNV;
PFNGLVERTEXATTRIB2SVNVPROC glVertexAttrib2svNV;
PFNGLVERTEXATTRIB3DNVPROC glVertexAttrib3dNV;
PFNGLVERTEXATTRIB3DVNVPROC glVertexAttrib3dvNV;
PFNGLVERTEXATTRIB3FNVPROC glVertexAttrib3fNV;
PFNGLVERTEXATTRIB3FVNVPROC glVertexAttrib3fvNV;
PFNGLVERTEXATTRIB3SNVPROC glVertexAttrib3sNV;
PFNGLVERTEXATTRIB3SVNVPROC glVertexAttrib3svNV;
PFNGLVERTEXATTRIB4DNVPROC glVertexAttrib4dNV;
PFNGLVERTEXATTRIB4DVNVPROC glVertexAttrib4dvNV;
PFNGLVERTEXATTRIB4FNVPROC glVertexAttrib4fNV;
PFNGLVERTEXATTRIB4FVNVPROC glVertexAttrib4fvNV;
PFNGLVERTEXATTRIB4SNVPROC glVertexAttrib4sNV;
PFNGLVERTEXATTRIB4SVNVPROC glVertexAttrib4svNV;
PFNGLVERTEXATTRIB4UBNVPROC glVertexAttrib4ubNV;
PFNGLVERTEXATTRIB4UBVNVPROC glVertexAttrib4ubvNV;
PFNGLVERTEXATTRIBS1DVNVPROC glVertexAttribs1dvNV;
PFNGLVERTEXATTRIBS1FVNVPROC glVertexAttribs1fvNV;
PFNGLVERTEXATTRIBS1SVNVPROC glVertexAttribs1svNV;
PFNGLVERTEXATTRIBS2DVNVPROC glVertexAttribs2dvNV;
PFNGLVERTEXATTRIBS2FVNVPROC glVertexAttribs2fvNV;
PFNGLVERTEXATTRIBS2SVNVPROC glVertexAttribs2svNV;
PFNGLVERTEXATTRIBS3DVNVPROC glVertexAttribs3dvNV;
PFNGLVERTEXATTRIBS3FVNVPROC glVertexAttribs3fvNV;
PFNGLVERTEXATTRIBS3SVNVPROC glVertexAttribs3svNV;
PFNGLVERTEXATTRIBS4DVNVPROC glVertexAttribs4dvNV;
PFNGLVERTEXATTRIBS4FVNVPROC glVertexAttribs4fvNV;
PFNGLVERTEXATTRIBS4SVNVPROC glVertexAttribs4svNV;
PFNGLVERTEXATTRIBS4UBVNVPROC glVertexAttribs4ubvNV;

static int gleIntLoad_NV_vertex_program()
{
	int bIsLoaded = 1;
	glAreProgramsResidentNV = (PFNGLAREPROGRAMSRESIDENTNVPROC)gleIntGetProcAddress("glAreProgramsResidentNV");
	if(!TestPointer(glAreProgramsResidentNV)) bIsLoaded = 0;
	glBindProgramNV = (PFNGLBINDPROGRAMNVPROC)gleIntGetProcAddress("glBindProgramNV");
	if(!TestPointer(glBindProgramNV)) bIsLoaded = 0;
	glDeleteProgramsNV = (PFNGLDELETEPROGRAMSNVPROC)gleIntGetProcAddress("glDeleteProgramsNV");
	if(!TestPointer(glDeleteProgramsNV)) bIsLoaded = 0;
	glExecuteProgramNV = (PFNGLEXECUTEPROGRAMNVPROC)gleIntGetProcAddress("glExecuteProgramNV");
	if(!TestPointer(glExecuteProgramNV)) bIsLoaded = 0;
	glGenProgramsNV = (PFNGLGENPROGRAMSNVPROC)gleIntGetProcAddress("glGenProgramsNV");
	if(!TestPointer(glGenProgramsNV)) bIsLoaded = 0;
	glGetProgramParameterdvNV = (PFNGLGETPROGRAMPARAMETERDVNVPROC)gleIntGetProcAddress("glGetProgramParameterdvNV");
	if(!TestPointer(glGetProgramParameterdvNV)) bIsLoaded = 0;
	glGetProgramParameterfvNV = (PFNGLGETPROGRAMPARAMETERFVNVPROC)gleIntGetProcAddress("glGetProgramParameterfvNV");
	if(!TestPointer(glGetProgramParameterfvNV)) bIsLoaded = 0;
	glGetProgramivNV = (PFNGLGETPROGRAMIVNVPROC)gleIntGetProcAddress("glGetProgramivNV");
	if(!TestPointer(glGetProgramivNV)) bIsLoaded = 0;
	glGetProgramStringNV = (PFNGLGETPROGRAMSTRINGNVPROC)gleIntGetProcAddress("glGetProgramStringNV");
	if(!TestPointer(glGetProgramStringNV)) bIsLoaded = 0;
	glGetTrackMatrixivNV = (PFNGLGETTRACKMATRIXIVNVPROC)gleIntGetProcAddress("glGetTrackMatrixivNV");
	if(!TestPointer(glGetTrackMatrixivNV)) bIsLoaded = 0;
	glGetVertexAttribdvNV = (PFNGLGETVERTEXATTRIBDVNVPROC)gleIntGetProcAddress("glGetVertexAttribdvNV");
	if(!TestPointer(glGetVertexAttribdvNV)) bIsLoaded = 0;
	glGetVertexAttribfvNV = (PFNGLGETVERTEXATTRIBFVNVPROC)gleIntGetProcAddress("glGetVertexAttribfvNV");
	if(!TestPointer(glGetVertexAttribfvNV)) bIsLoaded = 0;
	glGetVertexAttribivNV = (PFNGLGETVERTEXATTRIBIVNVPROC)gleIntGetProcAddress("glGetVertexAttribivNV");
	if(!TestPointer(glGetVertexAttribivNV)) bIsLoaded = 0;
	glGetVertexAttribPointervNV = (PFNGLGETVERTEXATTRIBPOINTERVNVPROC)gleIntGetProcAddress("glGetVertexAttribPointervNV");
	if(!TestPointer(glGetVertexAttribPointervNV)) bIsLoaded = 0;
	glIsProgramNV = (PFNGLISPROGRAMNVPROC)gleIntGetProcAddress("glIsProgramNV");
	if(!TestPointer(glIsProgramNV)) bIsLoaded = 0;
	glLoadProgramNV = (PFNGLLOADPROGRAMNVPROC)gleIntGetProcAddress("glLoadProgramNV");
	if(!TestPointer(glLoadProgramNV)) bIsLoaded = 0;
	glProgramParameter4dNV = (PFNGLPROGRAMPARAMETER4DNVPROC)gleIntGetProcAddress("glProgramParameter4dNV");
	if(!TestPointer(glProgramParameter4dNV)) bIsLoaded = 0;
	glProgramParameter4dvNV = (PFNGLPROGRAMPARAMETER4DVNVPROC)gleIntGetProcAddress("glProgramParameter4dvNV");
	if(!TestPointer(glProgramParameter4dvNV)) bIsLoaded = 0;
	glProgramParameter4fNV = (PFNGLPROGRAMPARAMETER4FNVPROC)gleIntGetProcAddress("glProgramParameter4fNV");
	if(!TestPointer(glProgramParameter4fNV)) bIsLoaded = 0;
	glProgramParameter4fvNV = (PFNGLPROGRAMPARAMETER4FVNVPROC)gleIntGetProcAddress("glProgramParameter4fvNV");
	if(!TestPointer(glProgramParameter4fvNV)) bIsLoaded = 0;
	glProgramParameters4dvNV = (PFNGLPROGRAMPARAMETERS4DVNVPROC)gleIntGetProcAddress("glProgramParameters4dvNV");
	if(!TestPointer(glProgramParameters4dvNV)) bIsLoaded = 0;
	glProgramParameters4fvNV = (PFNGLPROGRAMPARAMETERS4FVNVPROC)gleIntGetProcAddress("glProgramParameters4fvNV");
	if(!TestPointer(glProgramParameters4fvNV)) bIsLoaded = 0;
	glRequestResidentProgramsNV = (PFNGLREQUESTRESIDENTPROGRAMSNVPROC)gleIntGetProcAddress("glRequestResidentProgramsNV");
	if(!TestPointer(glRequestResidentProgramsNV)) bIsLoaded = 0;
	glTrackMatrixNV = (PFNGLTRACKMATRIXNVPROC)gleIntGetProcAddress("glTrackMatrixNV");
	if(!TestPointer(glTrackMatrixNV)) bIsLoaded = 0;
	glVertexAttribPointerNV = (PFNGLVERTEXATTRIBPOINTERNVPROC)gleIntGetProcAddress("glVertexAttribPointerNV");
	if(!TestPointer(glVertexAttribPointerNV)) bIsLoaded = 0;
	glVertexAttrib1dNV = (PFNGLVERTEXATTRIB1DNVPROC)gleIntGetProcAddress("glVertexAttrib1dNV");
	if(!TestPointer(glVertexAttrib1dNV)) bIsLoaded = 0;
	glVertexAttrib1dvNV = (PFNGLVERTEXATTRIB1DVNVPROC)gleIntGetProcAddress("glVertexAttrib1dvNV");
	if(!TestPointer(glVertexAttrib1dvNV)) bIsLoaded = 0;
	glVertexAttrib1fNV = (PFNGLVERTEXATTRIB1FNVPROC)gleIntGetProcAddress("glVertexAttrib1fNV");
	if(!TestPointer(glVertexAttrib1fNV)) bIsLoaded = 0;
	glVertexAttrib1fvNV = (PFNGLVERTEXATTRIB1FVNVPROC)gleIntGetProcAddress("glVertexAttrib1fvNV");
	if(!TestPointer(glVertexAttrib1fvNV)) bIsLoaded = 0;
	glVertexAttrib1sNV = (PFNGLVERTEXATTRIB1SNVPROC)gleIntGetProcAddress("glVertexAttrib1sNV");
	if(!TestPointer(glVertexAttrib1sNV)) bIsLoaded = 0;
	glVertexAttrib1svNV = (PFNGLVERTEXATTRIB1SVNVPROC)gleIntGetProcAddress("glVertexAttrib1svNV");
	if(!TestPointer(glVertexAttrib1svNV)) bIsLoaded = 0;
	glVertexAttrib2dNV = (PFNGLVERTEXATTRIB2DNVPROC)gleIntGetProcAddress("glVertexAttrib2dNV");
	if(!TestPointer(glVertexAttrib2dNV)) bIsLoaded = 0;
	glVertexAttrib2dvNV = (PFNGLVERTEXATTRIB2DVNVPROC)gleIntGetProcAddress("glVertexAttrib2dvNV");
	if(!TestPointer(glVertexAttrib2dvNV)) bIsLoaded = 0;
	glVertexAttrib2fNV = (PFNGLVERTEXATTRIB2FNVPROC)gleIntGetProcAddress("glVertexAttrib2fNV");
	if(!TestPointer(glVertexAttrib2fNV)) bIsLoaded = 0;
	glVertexAttrib2fvNV = (PFNGLVERTEXATTRIB2FVNVPROC)gleIntGetProcAddress("glVertexAttrib2fvNV");
	if(!TestPointer(glVertexAttrib2fvNV)) bIsLoaded = 0;
	glVertexAttrib2sNV = (PFNGLVERTEXATTRIB2SNVPROC)gleIntGetProcAddress("glVertexAttrib2sNV");
	if(!TestPointer(glVertexAttrib2sNV)) bIsLoaded = 0;
	glVertexAttrib2svNV = (PFNGLVERTEXATTRIB2SVNVPROC)gleIntGetProcAddress("glVertexAttrib2svNV");
	if(!TestPointer(glVertexAttrib2svNV)) bIsLoaded = 0;
	glVertexAttrib3dNV = (PFNGLVERTEXATTRIB3DNVPROC)gleIntGetProcAddress("glVertexAttrib3dNV");
	if(!TestPointer(glVertexAttrib3dNV)) bIsLoaded = 0;
	glVertexAttrib3dvNV = (PFNGLVERTEXATTRIB3DVNVPROC)gleIntGetProcAddress("glVertexAttrib3dvNV");
	if(!TestPointer(glVertexAttrib3dvNV)) bIsLoaded = 0;
	glVertexAttrib3fNV = (PFNGLVERTEXATTRIB3FNVPROC)gleIntGetProcAddress("glVertexAttrib3fNV");
	if(!TestPointer(glVertexAttrib3fNV)) bIsLoaded = 0;
	glVertexAttrib3fvNV = (PFNGLVERTEXATTRIB3FVNVPROC)gleIntGetProcAddress("glVertexAttrib3fvNV");
	if(!TestPointer(glVertexAttrib3fvNV)) bIsLoaded = 0;
	glVertexAttrib3sNV = (PFNGLVERTEXATTRIB3SNVPROC)gleIntGetProcAddress("glVertexAttrib3sNV");
	if(!TestPointer(glVertexAttrib3sNV)) bIsLoaded = 0;
	glVertexAttrib3svNV = (PFNGLVERTEXATTRIB3SVNVPROC)gleIntGetProcAddress("glVertexAttrib3svNV");
	if(!TestPointer(glVertexAttrib3svNV)) bIsLoaded = 0;
	glVertexAttrib4dNV = (PFNGLVERTEXATTRIB4DNVPROC)gleIntGetProcAddress("glVertexAttrib4dNV");
	if(!TestPointer(glVertexAttrib4dNV)) bIsLoaded = 0;
	glVertexAttrib4dvNV = (PFNGLVERTEXATTRIB4DVNVPROC)gleIntGetProcAddress("glVertexAttrib4dvNV");
	if(!TestPointer(glVertexAttrib4dvNV)) bIsLoaded = 0;
	glVertexAttrib4fNV = (PFNGLVERTEXATTRIB4FNVPROC)gleIntGetProcAddress("glVertexAttrib4fNV");
	if(!TestPointer(glVertexAttrib4fNV)) bIsLoaded = 0;
	glVertexAttrib4fvNV = (PFNGLVERTEXATTRIB4FVNVPROC)gleIntGetProcAddress("glVertexAttrib4fvNV");
	if(!TestPointer(glVertexAttrib4fvNV)) bIsLoaded = 0;
	glVertexAttrib4sNV = (PFNGLVERTEXATTRIB4SNVPROC)gleIntGetProcAddress("glVertexAttrib4sNV");
	if(!TestPointer(glVertexAttrib4sNV)) bIsLoaded = 0;
	glVertexAttrib4svNV = (PFNGLVERTEXATTRIB4SVNVPROC)gleIntGetProcAddress("glVertexAttrib4svNV");
	if(!TestPointer(glVertexAttrib4svNV)) bIsLoaded = 0;
	glVertexAttrib4ubNV = (PFNGLVERTEXATTRIB4UBNVPROC)gleIntGetProcAddress("glVertexAttrib4ubNV");
	if(!TestPointer(glVertexAttrib4ubNV)) bIsLoaded = 0;
	glVertexAttrib4ubvNV = (PFNGLVERTEXATTRIB4UBVNVPROC)gleIntGetProcAddress("glVertexAttrib4ubvNV");
	if(!TestPointer(glVertexAttrib4ubvNV)) bIsLoaded = 0;
	glVertexAttribs1dvNV = (PFNGLVERTEXATTRIBS1DVNVPROC)gleIntGetProcAddress("glVertexAttribs1dvNV");
	if(!TestPointer(glVertexAttribs1dvNV)) bIsLoaded = 0;
	glVertexAttribs1fvNV = (PFNGLVERTEXATTRIBS1FVNVPROC)gleIntGetProcAddress("glVertexAttribs1fvNV");
	if(!TestPointer(glVertexAttribs1fvNV)) bIsLoaded = 0;
	glVertexAttribs1svNV = (PFNGLVERTEXATTRIBS1SVNVPROC)gleIntGetProcAddress("glVertexAttribs1svNV");
	if(!TestPointer(glVertexAttribs1svNV)) bIsLoaded = 0;
	glVertexAttribs2dvNV = (PFNGLVERTEXATTRIBS2DVNVPROC)gleIntGetProcAddress("glVertexAttribs2dvNV");
	if(!TestPointer(glVertexAttribs2dvNV)) bIsLoaded = 0;
	glVertexAttribs2fvNV = (PFNGLVERTEXATTRIBS2FVNVPROC)gleIntGetProcAddress("glVertexAttribs2fvNV");
	if(!TestPointer(glVertexAttribs2fvNV)) bIsLoaded = 0;
	glVertexAttribs2svNV = (PFNGLVERTEXATTRIBS2SVNVPROC)gleIntGetProcAddress("glVertexAttribs2svNV");
	if(!TestPointer(glVertexAttribs2svNV)) bIsLoaded = 0;
	glVertexAttribs3dvNV = (PFNGLVERTEXATTRIBS3DVNVPROC)gleIntGetProcAddress("glVertexAttribs3dvNV");
	if(!TestPointer(glVertexAttribs3dvNV)) bIsLoaded = 0;
	glVertexAttribs3fvNV = (PFNGLVERTEXATTRIBS3FVNVPROC)gleIntGetProcAddress("glVertexAttribs3fvNV");
	if(!TestPointer(glVertexAttribs3fvNV)) bIsLoaded = 0;
	glVertexAttribs3svNV = (PFNGLVERTEXATTRIBS3SVNVPROC)gleIntGetProcAddress("glVertexAttribs3svNV");
	if(!TestPointer(glVertexAttribs3svNV)) bIsLoaded = 0;
	glVertexAttribs4dvNV = (PFNGLVERTEXATTRIBS4DVNVPROC)gleIntGetProcAddress("glVertexAttribs4dvNV");
	if(!TestPointer(glVertexAttribs4dvNV)) bIsLoaded = 0;
	glVertexAttribs4fvNV = (PFNGLVERTEXATTRIBS4FVNVPROC)gleIntGetProcAddress("glVertexAttribs4fvNV");
	if(!TestPointer(glVertexAttribs4fvNV)) bIsLoaded = 0;
	glVertexAttribs4svNV = (PFNGLVERTEXATTRIBS4SVNVPROC)gleIntGetProcAddress("glVertexAttribs4svNV");
	if(!TestPointer(glVertexAttribs4svNV)) bIsLoaded = 0;
	glVertexAttribs4ubvNV = (PFNGLVERTEXATTRIBS4UBVNVPROC)gleIntGetProcAddress("glVertexAttribs4ubvNV");
	if(!TestPointer(glVertexAttribs4ubvNV)) bIsLoaded = 0;
	return bIsLoaded;
}




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

PFNGLVERTEXATTRIBI1IEXTPROC glVertexAttribI1iEXT;
PFNGLVERTEXATTRIBI2IEXTPROC glVertexAttribI2iEXT;
PFNGLVERTEXATTRIBI3IEXTPROC glVertexAttribI3iEXT;
PFNGLVERTEXATTRIBI4IEXTPROC glVertexAttribI4iEXT;
PFNGLVERTEXATTRIBI1UIEXTPROC glVertexAttribI1uiEXT;
PFNGLVERTEXATTRIBI2UIEXTPROC glVertexAttribI2uiEXT;
PFNGLVERTEXATTRIBI3UIEXTPROC glVertexAttribI3uiEXT;
PFNGLVERTEXATTRIBI4UIEXTPROC glVertexAttribI4uiEXT;
PFNGLVERTEXATTRIBI1IVEXTPROC glVertexAttribI1ivEXT;
PFNGLVERTEXATTRIBI2IVEXTPROC glVertexAttribI2ivEXT;
PFNGLVERTEXATTRIBI3IVEXTPROC glVertexAttribI3ivEXT;
PFNGLVERTEXATTRIBI4IVEXTPROC glVertexAttribI4ivEXT;
PFNGLVERTEXATTRIBI1UIVEXTPROC glVertexAttribI1uivEXT;
PFNGLVERTEXATTRIBI2UIVEXTPROC glVertexAttribI2uivEXT;
PFNGLVERTEXATTRIBI3UIVEXTPROC glVertexAttribI3uivEXT;
PFNGLVERTEXATTRIBI4UIVEXTPROC glVertexAttribI4uivEXT;
PFNGLVERTEXATTRIBI4BVEXTPROC glVertexAttribI4bvEXT;
PFNGLVERTEXATTRIBI4SVEXTPROC glVertexAttribI4svEXT;
PFNGLVERTEXATTRIBI4UBVEXTPROC glVertexAttribI4ubvEXT;
PFNGLVERTEXATTRIBI4USVEXTPROC glVertexAttribI4usvEXT;
PFNGLVERTEXATTRIBIPOINTEREXTPROC glVertexAttribIPointerEXT;
PFNGLGETVERTEXATTRIBIIVEXTPROC glGetVertexAttribIivEXT;
PFNGLGETVERTEXATTRIBIUIVEXTPROC glGetVertexAttribIuivEXT;

static int gleIntLoad_NV_vertex_program4()
{
	int bIsLoaded = 1;
	glVertexAttribI1iEXT = (PFNGLVERTEXATTRIBI1IEXTPROC)gleIntGetProcAddress("glVertexAttribI1iEXT");
	if(!TestPointer(glVertexAttribI1iEXT)) bIsLoaded = 0;
	glVertexAttribI2iEXT = (PFNGLVERTEXATTRIBI2IEXTPROC)gleIntGetProcAddress("glVertexAttribI2iEXT");
	if(!TestPointer(glVertexAttribI2iEXT)) bIsLoaded = 0;
	glVertexAttribI3iEXT = (PFNGLVERTEXATTRIBI3IEXTPROC)gleIntGetProcAddress("glVertexAttribI3iEXT");
	if(!TestPointer(glVertexAttribI3iEXT)) bIsLoaded = 0;
	glVertexAttribI4iEXT = (PFNGLVERTEXATTRIBI4IEXTPROC)gleIntGetProcAddress("glVertexAttribI4iEXT");
	if(!TestPointer(glVertexAttribI4iEXT)) bIsLoaded = 0;
	glVertexAttribI1uiEXT = (PFNGLVERTEXATTRIBI1UIEXTPROC)gleIntGetProcAddress("glVertexAttribI1uiEXT");
	if(!TestPointer(glVertexAttribI1uiEXT)) bIsLoaded = 0;
	glVertexAttribI2uiEXT = (PFNGLVERTEXATTRIBI2UIEXTPROC)gleIntGetProcAddress("glVertexAttribI2uiEXT");
	if(!TestPointer(glVertexAttribI2uiEXT)) bIsLoaded = 0;
	glVertexAttribI3uiEXT = (PFNGLVERTEXATTRIBI3UIEXTPROC)gleIntGetProcAddress("glVertexAttribI3uiEXT");
	if(!TestPointer(glVertexAttribI3uiEXT)) bIsLoaded = 0;
	glVertexAttribI4uiEXT = (PFNGLVERTEXATTRIBI4UIEXTPROC)gleIntGetProcAddress("glVertexAttribI4uiEXT");
	if(!TestPointer(glVertexAttribI4uiEXT)) bIsLoaded = 0;
	glVertexAttribI1ivEXT = (PFNGLVERTEXATTRIBI1IVEXTPROC)gleIntGetProcAddress("glVertexAttribI1ivEXT");
	if(!TestPointer(glVertexAttribI1ivEXT)) bIsLoaded = 0;
	glVertexAttribI2ivEXT = (PFNGLVERTEXATTRIBI2IVEXTPROC)gleIntGetProcAddress("glVertexAttribI2ivEXT");
	if(!TestPointer(glVertexAttribI2ivEXT)) bIsLoaded = 0;
	glVertexAttribI3ivEXT = (PFNGLVERTEXATTRIBI3IVEXTPROC)gleIntGetProcAddress("glVertexAttribI3ivEXT");
	if(!TestPointer(glVertexAttribI3ivEXT)) bIsLoaded = 0;
	glVertexAttribI4ivEXT = (PFNGLVERTEXATTRIBI4IVEXTPROC)gleIntGetProcAddress("glVertexAttribI4ivEXT");
	if(!TestPointer(glVertexAttribI4ivEXT)) bIsLoaded = 0;
	glVertexAttribI1uivEXT = (PFNGLVERTEXATTRIBI1UIVEXTPROC)gleIntGetProcAddress("glVertexAttribI1uivEXT");
	if(!TestPointer(glVertexAttribI1uivEXT)) bIsLoaded = 0;
	glVertexAttribI2uivEXT = (PFNGLVERTEXATTRIBI2UIVEXTPROC)gleIntGetProcAddress("glVertexAttribI2uivEXT");
	if(!TestPointer(glVertexAttribI2uivEXT)) bIsLoaded = 0;
	glVertexAttribI3uivEXT = (PFNGLVERTEXATTRIBI3UIVEXTPROC)gleIntGetProcAddress("glVertexAttribI3uivEXT");
	if(!TestPointer(glVertexAttribI3uivEXT)) bIsLoaded = 0;
	glVertexAttribI4uivEXT = (PFNGLVERTEXATTRIBI4UIVEXTPROC)gleIntGetProcAddress("glVertexAttribI4uivEXT");
	if(!TestPointer(glVertexAttribI4uivEXT)) bIsLoaded = 0;
	glVertexAttribI4bvEXT = (PFNGLVERTEXATTRIBI4BVEXTPROC)gleIntGetProcAddress("glVertexAttribI4bvEXT");
	if(!TestPointer(glVertexAttribI4bvEXT)) bIsLoaded = 0;
	glVertexAttribI4svEXT = (PFNGLVERTEXATTRIBI4SVEXTPROC)gleIntGetProcAddress("glVertexAttribI4svEXT");
	if(!TestPointer(glVertexAttribI4svEXT)) bIsLoaded = 0;
	glVertexAttribI4ubvEXT = (PFNGLVERTEXATTRIBI4UBVEXTPROC)gleIntGetProcAddress("glVertexAttribI4ubvEXT");
	if(!TestPointer(glVertexAttribI4ubvEXT)) bIsLoaded = 0;
	glVertexAttribI4usvEXT = (PFNGLVERTEXATTRIBI4USVEXTPROC)gleIntGetProcAddress("glVertexAttribI4usvEXT");
	if(!TestPointer(glVertexAttribI4usvEXT)) bIsLoaded = 0;
	glVertexAttribIPointerEXT = (PFNGLVERTEXATTRIBIPOINTEREXTPROC)gleIntGetProcAddress("glVertexAttribIPointerEXT");
	if(!TestPointer(glVertexAttribIPointerEXT)) bIsLoaded = 0;
	glGetVertexAttribIivEXT = (PFNGLGETVERTEXATTRIBIIVEXTPROC)gleIntGetProcAddress("glGetVertexAttribIivEXT");
	if(!TestPointer(glGetVertexAttribIivEXT)) bIsLoaded = 0;
	glGetVertexAttribIuivEXT = (PFNGLGETVERTEXATTRIBIUIVEXTPROC)gleIntGetProcAddress("glGetVertexAttribIuivEXT");
	if(!TestPointer(glGetVertexAttribIuivEXT)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLBEGINVIDEOCAPTURENVPROC glBeginVideoCaptureNV;
PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC glBindVideoCaptureStreamBufferNV;
PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC glBindVideoCaptureStreamTextureNV;
PFNGLENDVIDEOCAPTURENVPROC glEndVideoCaptureNV;
PFNGLGETVIDEOCAPTUREIVNVPROC glGetVideoCaptureivNV;
PFNGLGETVIDEOCAPTURESTREAMIVNVPROC glGetVideoCaptureStreamivNV;
PFNGLGETVIDEOCAPTURESTREAMFVNVPROC glGetVideoCaptureStreamfvNV;
PFNGLGETVIDEOCAPTURESTREAMDVNVPROC glGetVideoCaptureStreamdvNV;
PFNGLVIDEOCAPTURENVPROC glVideoCaptureNV;
PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC glVideoCaptureStreamParameterivNV;
PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC glVideoCaptureStreamParameterfvNV;
PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC glVideoCaptureStreamParameterdvNV;

static int gleIntLoad_NV_video_capture()
{
	int bIsLoaded = 1;
	glBeginVideoCaptureNV = (PFNGLBEGINVIDEOCAPTURENVPROC)gleIntGetProcAddress("glBeginVideoCaptureNV");
	if(!TestPointer(glBeginVideoCaptureNV)) bIsLoaded = 0;
	glBindVideoCaptureStreamBufferNV = (PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)gleIntGetProcAddress("glBindVideoCaptureStreamBufferNV");
	if(!TestPointer(glBindVideoCaptureStreamBufferNV)) bIsLoaded = 0;
	glBindVideoCaptureStreamTextureNV = (PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)gleIntGetProcAddress("glBindVideoCaptureStreamTextureNV");
	if(!TestPointer(glBindVideoCaptureStreamTextureNV)) bIsLoaded = 0;
	glEndVideoCaptureNV = (PFNGLENDVIDEOCAPTURENVPROC)gleIntGetProcAddress("glEndVideoCaptureNV");
	if(!TestPointer(glEndVideoCaptureNV)) bIsLoaded = 0;
	glGetVideoCaptureivNV = (PFNGLGETVIDEOCAPTUREIVNVPROC)gleIntGetProcAddress("glGetVideoCaptureivNV");
	if(!TestPointer(glGetVideoCaptureivNV)) bIsLoaded = 0;
	glGetVideoCaptureStreamivNV = (PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)gleIntGetProcAddress("glGetVideoCaptureStreamivNV");
	if(!TestPointer(glGetVideoCaptureStreamivNV)) bIsLoaded = 0;
	glGetVideoCaptureStreamfvNV = (PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)gleIntGetProcAddress("glGetVideoCaptureStreamfvNV");
	if(!TestPointer(glGetVideoCaptureStreamfvNV)) bIsLoaded = 0;
	glGetVideoCaptureStreamdvNV = (PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)gleIntGetProcAddress("glGetVideoCaptureStreamdvNV");
	if(!TestPointer(glGetVideoCaptureStreamdvNV)) bIsLoaded = 0;
	glVideoCaptureNV = (PFNGLVIDEOCAPTURENVPROC)gleIntGetProcAddress("glVideoCaptureNV");
	if(!TestPointer(glVideoCaptureNV)) bIsLoaded = 0;
	glVideoCaptureStreamParameterivNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)gleIntGetProcAddress("glVideoCaptureStreamParameterivNV");
	if(!TestPointer(glVideoCaptureStreamParameterivNV)) bIsLoaded = 0;
	glVideoCaptureStreamParameterfvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)gleIntGetProcAddress("glVideoCaptureStreamParameterfvNV");
	if(!TestPointer(glVideoCaptureStreamParameterfvNV)) bIsLoaded = 0;
	glVideoCaptureStreamParameterdvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)gleIntGetProcAddress("glVideoCaptureStreamParameterdvNV");
	if(!TestPointer(glVideoCaptureStreamParameterdvNV)) bIsLoaded = 0;
	return bIsLoaded;
}




typedef void (GLE_FUNCPTR * PFNGLHINTPGIPROC)(GLenum target, GLint mode);

PFNGLHINTPGIPROC glHintPGI;

static int gleIntLoad_PGI_misc_hints()
{
	int bIsLoaded = 1;
	glHintPGI = (PFNGLHINTPGIPROC)gleIntGetProcAddress("glHintPGI");
	if(!TestPointer(glHintPGI)) bIsLoaded = 0;
	return bIsLoaded;
}



typedef void (GLE_FUNCPTR * PFNGLDETAILTEXFUNCSGISPROC)(GLenum target, GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETDETAILTEXFUNCSGISPROC)(GLenum target, GLfloat *points);

PFNGLDETAILTEXFUNCSGISPROC glDetailTexFuncSGIS;
PFNGLGETDETAILTEXFUNCSGISPROC glGetDetailTexFuncSGIS;

static int gleIntLoad_SGIS_detail_texture()
{
	int bIsLoaded = 1;
	glDetailTexFuncSGIS = (PFNGLDETAILTEXFUNCSGISPROC)gleIntGetProcAddress("glDetailTexFuncSGIS");
	if(!TestPointer(glDetailTexFuncSGIS)) bIsLoaded = 0;
	glGetDetailTexFuncSGIS = (PFNGLGETDETAILTEXFUNCSGISPROC)gleIntGetProcAddress("glGetDetailTexFuncSGIS");
	if(!TestPointer(glGetDetailTexFuncSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLFOGFUNCSGISPROC)(GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETFOGFUNCSGISPROC)(GLfloat *points);

PFNGLFOGFUNCSGISPROC glFogFuncSGIS;
PFNGLGETFOGFUNCSGISPROC glGetFogFuncSGIS;

static int gleIntLoad_SGIS_fog_function()
{
	int bIsLoaded = 1;
	glFogFuncSGIS = (PFNGLFOGFUNCSGISPROC)gleIntGetProcAddress("glFogFuncSGIS");
	if(!TestPointer(glFogFuncSGIS)) bIsLoaded = 0;
	glGetFogFuncSGIS = (PFNGLGETFOGFUNCSGISPROC)gleIntGetProcAddress("glGetFogFuncSGIS");
	if(!TestPointer(glGetFogFuncSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLSAMPLEMASKSGISPROC)(GLclampf value, GLboolean invert);
typedef void (GLE_FUNCPTR * PFNGLSAMPLEPATTERNSGISPROC)(GLenum pattern);

PFNGLSAMPLEMASKSGISPROC glSampleMaskSGIS;
PFNGLSAMPLEPATTERNSGISPROC glSamplePatternSGIS;

static int gleIntLoad_SGIS_multisample()
{
	int bIsLoaded = 1;
	glSampleMaskSGIS = (PFNGLSAMPLEMASKSGISPROC)gleIntGetProcAddress("glSampleMaskSGIS");
	if(!TestPointer(glSampleMaskSGIS)) bIsLoaded = 0;
	glSamplePatternSGIS = (PFNGLSAMPLEPATTERNSGISPROC)gleIntGetProcAddress("glSamplePatternSGIS");
	if(!TestPointer(glSamplePatternSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERISGISPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERIVSGISPROC)(GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERFSGISPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENPARAMETERFVSGISPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)(GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)(GLenum pname, GLfloat *params);

PFNGLPIXELTEXGENPARAMETERISGISPROC glPixelTexGenParameteriSGIS;
PFNGLPIXELTEXGENPARAMETERIVSGISPROC glPixelTexGenParameterivSGIS;
PFNGLPIXELTEXGENPARAMETERFSGISPROC glPixelTexGenParameterfSGIS;
PFNGLPIXELTEXGENPARAMETERFVSGISPROC glPixelTexGenParameterfvSGIS;
PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC glGetPixelTexGenParameterivSGIS;
PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC glGetPixelTexGenParameterfvSGIS;

static int gleIntLoad_SGIS_pixel_texture()
{
	int bIsLoaded = 1;
	glPixelTexGenParameteriSGIS = (PFNGLPIXELTEXGENPARAMETERISGISPROC)gleIntGetProcAddress("glPixelTexGenParameteriSGIS");
	if(!TestPointer(glPixelTexGenParameteriSGIS)) bIsLoaded = 0;
	glPixelTexGenParameterivSGIS = (PFNGLPIXELTEXGENPARAMETERIVSGISPROC)gleIntGetProcAddress("glPixelTexGenParameterivSGIS");
	if(!TestPointer(glPixelTexGenParameterivSGIS)) bIsLoaded = 0;
	glPixelTexGenParameterfSGIS = (PFNGLPIXELTEXGENPARAMETERFSGISPROC)gleIntGetProcAddress("glPixelTexGenParameterfSGIS");
	if(!TestPointer(glPixelTexGenParameterfSGIS)) bIsLoaded = 0;
	glPixelTexGenParameterfvSGIS = (PFNGLPIXELTEXGENPARAMETERFVSGISPROC)gleIntGetProcAddress("glPixelTexGenParameterfvSGIS");
	if(!TestPointer(glPixelTexGenParameterfvSGIS)) bIsLoaded = 0;
	glGetPixelTexGenParameterivSGIS = (PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)gleIntGetProcAddress("glGetPixelTexGenParameterivSGIS");
	if(!TestPointer(glGetPixelTexGenParameterivSGIS)) bIsLoaded = 0;
	glGetPixelTexGenParameterfvSGIS = (PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)gleIntGetProcAddress("glGetPixelTexGenParameterfvSGIS");
	if(!TestPointer(glGetPixelTexGenParameterfvSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFSGISPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVSGISPROC)(GLenum pname, const GLfloat *params);

PFNGLPOINTPARAMETERFSGISPROC glPointParameterfSGIS;
PFNGLPOINTPARAMETERFVSGISPROC glPointParameterfvSGIS;

static int gleIntLoad_SGIS_point_parameters()
{
	int bIsLoaded = 1;
	glPointParameterfSGIS = (PFNGLPOINTPARAMETERFSGISPROC)gleIntGetProcAddress("glPointParameterfSGIS");
	if(!TestPointer(glPointParameterfSGIS)) bIsLoaded = 0;
	glPointParameterfvSGIS = (PFNGLPOINTPARAMETERFVSGISPROC)gleIntGetProcAddress("glPointParameterfvSGIS");
	if(!TestPointer(glPointParameterfvSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLSHARPENTEXFUNCSGISPROC)(GLenum target, GLsizei n, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLGETSHARPENTEXFUNCSGISPROC)(GLenum target, GLfloat *points);

PFNGLSHARPENTEXFUNCSGISPROC glSharpenTexFuncSGIS;
PFNGLGETSHARPENTEXFUNCSGISPROC glGetSharpenTexFuncSGIS;

static int gleIntLoad_SGIS_sharpen_texture()
{
	int bIsLoaded = 1;
	glSharpenTexFuncSGIS = (PFNGLSHARPENTEXFUNCSGISPROC)gleIntGetProcAddress("glSharpenTexFuncSGIS");
	if(!TestPointer(glSharpenTexFuncSGIS)) bIsLoaded = 0;
	glGetSharpenTexFuncSGIS = (PFNGLGETSHARPENTEXFUNCSGISPROC)gleIntGetProcAddress("glGetSharpenTexFuncSGIS");
	if(!TestPointer(glGetSharpenTexFuncSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE4DSGISPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE4DSGISPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid *pixels);

PFNGLTEXIMAGE4DSGISPROC glTexImage4DSGIS;
PFNGLTEXSUBIMAGE4DSGISPROC glTexSubImage4DSGIS;

static int gleIntLoad_SGIS_texture4D()
{
	int bIsLoaded = 1;
	glTexImage4DSGIS = (PFNGLTEXIMAGE4DSGISPROC)gleIntGetProcAddress("glTexImage4DSGIS");
	if(!TestPointer(glTexImage4DSGIS)) bIsLoaded = 0;
	glTexSubImage4DSGIS = (PFNGLTEXSUBIMAGE4DSGISPROC)gleIntGetProcAddress("glTexSubImage4DSGIS");
	if(!TestPointer(glTexSubImage4DSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTEXTURECOLORMASKSGISPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

PFNGLTEXTURECOLORMASKSGISPROC glTextureColorMaskSGIS;

static int gleIntLoad_SGIS_texture_color_mask()
{
	int bIsLoaded = 1;
	glTextureColorMaskSGIS = (PFNGLTEXTURECOLORMASKSGISPROC)gleIntGetProcAddress("glTextureColorMaskSGIS");
	if(!TestPointer(glTextureColorMaskSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLGETTEXFILTERFUNCSGISPROC)(GLenum target, GLenum filter, GLfloat *weights);
typedef void (GLE_FUNCPTR * PFNGLTEXFILTERFUNCSGISPROC)(GLenum target, GLenum filter, GLsizei n, const GLfloat *weights);

PFNGLGETTEXFILTERFUNCSGISPROC glGetTexFilterFuncSGIS;
PFNGLTEXFILTERFUNCSGISPROC glTexFilterFuncSGIS;

static int gleIntLoad_SGIS_texture_filter4()
{
	int bIsLoaded = 1;
	glGetTexFilterFuncSGIS = (PFNGLGETTEXFILTERFUNCSGISPROC)gleIntGetProcAddress("glGetTexFilterFuncSGIS");
	if(!TestPointer(glGetTexFilterFuncSGIS)) bIsLoaded = 0;
	glTexFilterFuncSGIS = (PFNGLTEXFILTERFUNCSGISPROC)gleIntGetProcAddress("glTexFilterFuncSGIS");
	if(!TestPointer(glTexFilterFuncSGIS)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLASYNCMARKERSGIXPROC)(GLuint marker);
typedef GLint (GLE_FUNCPTR * PFNGLFINISHASYNCSGIXPROC)(GLuint *markerp);
typedef GLint (GLE_FUNCPTR * PFNGLPOLLASYNCSGIXPROC)(GLuint *markerp);
typedef GLuint (GLE_FUNCPTR * PFNGLGENASYNCMARKERSSGIXPROC)(GLsizei range);
typedef void (GLE_FUNCPTR * PFNGLDELETEASYNCMARKERSSGIXPROC)(GLuint marker, GLsizei range);
typedef GLboolean (GLE_FUNCPTR * PFNGLISASYNCMARKERSGIXPROC)(GLuint marker);

PFNGLASYNCMARKERSGIXPROC glAsyncMarkerSGIX;
PFNGLFINISHASYNCSGIXPROC glFinishAsyncSGIX;
PFNGLPOLLASYNCSGIXPROC glPollAsyncSGIX;
PFNGLGENASYNCMARKERSSGIXPROC glGenAsyncMarkersSGIX;
PFNGLDELETEASYNCMARKERSSGIXPROC glDeleteAsyncMarkersSGIX;
PFNGLISASYNCMARKERSGIXPROC glIsAsyncMarkerSGIX;

static int gleIntLoad_SGIX_async()
{
	int bIsLoaded = 1;
	glAsyncMarkerSGIX = (PFNGLASYNCMARKERSGIXPROC)gleIntGetProcAddress("glAsyncMarkerSGIX");
	if(!TestPointer(glAsyncMarkerSGIX)) bIsLoaded = 0;
	glFinishAsyncSGIX = (PFNGLFINISHASYNCSGIXPROC)gleIntGetProcAddress("glFinishAsyncSGIX");
	if(!TestPointer(glFinishAsyncSGIX)) bIsLoaded = 0;
	glPollAsyncSGIX = (PFNGLPOLLASYNCSGIXPROC)gleIntGetProcAddress("glPollAsyncSGIX");
	if(!TestPointer(glPollAsyncSGIX)) bIsLoaded = 0;
	glGenAsyncMarkersSGIX = (PFNGLGENASYNCMARKERSSGIXPROC)gleIntGetProcAddress("glGenAsyncMarkersSGIX");
	if(!TestPointer(glGenAsyncMarkersSGIX)) bIsLoaded = 0;
	glDeleteAsyncMarkersSGIX = (PFNGLDELETEASYNCMARKERSSGIXPROC)gleIntGetProcAddress("glDeleteAsyncMarkersSGIX");
	if(!TestPointer(glDeleteAsyncMarkersSGIX)) bIsLoaded = 0;
	glIsAsyncMarkerSGIX = (PFNGLISASYNCMARKERSGIXPROC)gleIntGetProcAddress("glIsAsyncMarkerSGIX");
	if(!TestPointer(glIsAsyncMarkerSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}







typedef void (GLE_FUNCPTR * PFNGLFLUSHRASTERSGIXPROC)();

PFNGLFLUSHRASTERSGIXPROC glFlushRasterSGIX;

static int gleIntLoad_SGIX_flush_raster()
{
	int bIsLoaded = 1;
	glFlushRasterSGIX = (PFNGLFLUSHRASTERSGIXPROC)gleIntGetProcAddress("glFlushRasterSGIX");
	if(!TestPointer(glFlushRasterSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}


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

PFNGLFRAGMENTCOLORMATERIALSGIXPROC glFragmentColorMaterialSGIX;
PFNGLFRAGMENTLIGHTFSGIXPROC glFragmentLightfSGIX;
PFNGLFRAGMENTLIGHTFVSGIXPROC glFragmentLightfvSGIX;
PFNGLFRAGMENTLIGHTISGIXPROC glFragmentLightiSGIX;
PFNGLFRAGMENTLIGHTIVSGIXPROC glFragmentLightivSGIX;
PFNGLFRAGMENTLIGHTMODELFSGIXPROC glFragmentLightModelfSGIX;
PFNGLFRAGMENTLIGHTMODELFVSGIXPROC glFragmentLightModelfvSGIX;
PFNGLFRAGMENTLIGHTMODELISGIXPROC glFragmentLightModeliSGIX;
PFNGLFRAGMENTLIGHTMODELIVSGIXPROC glFragmentLightModelivSGIX;
PFNGLFRAGMENTMATERIALFSGIXPROC glFragmentMaterialfSGIX;
PFNGLFRAGMENTMATERIALFVSGIXPROC glFragmentMaterialfvSGIX;
PFNGLFRAGMENTMATERIALISGIXPROC glFragmentMaterialiSGIX;
PFNGLFRAGMENTMATERIALIVSGIXPROC glFragmentMaterialivSGIX;
PFNGLGETFRAGMENTLIGHTFVSGIXPROC glGetFragmentLightfvSGIX;
PFNGLGETFRAGMENTLIGHTIVSGIXPROC glGetFragmentLightivSGIX;
PFNGLGETFRAGMENTMATERIALFVSGIXPROC glGetFragmentMaterialfvSGIX;
PFNGLGETFRAGMENTMATERIALIVSGIXPROC glGetFragmentMaterialivSGIX;
PFNGLLIGHTENVISGIXPROC glLightEnviSGIX;

static int gleIntLoad_SGIX_fragment_lighting()
{
	int bIsLoaded = 1;
	glFragmentColorMaterialSGIX = (PFNGLFRAGMENTCOLORMATERIALSGIXPROC)gleIntGetProcAddress("glFragmentColorMaterialSGIX");
	if(!TestPointer(glFragmentColorMaterialSGIX)) bIsLoaded = 0;
	glFragmentLightfSGIX = (PFNGLFRAGMENTLIGHTFSGIXPROC)gleIntGetProcAddress("glFragmentLightfSGIX");
	if(!TestPointer(glFragmentLightfSGIX)) bIsLoaded = 0;
	glFragmentLightfvSGIX = (PFNGLFRAGMENTLIGHTFVSGIXPROC)gleIntGetProcAddress("glFragmentLightfvSGIX");
	if(!TestPointer(glFragmentLightfvSGIX)) bIsLoaded = 0;
	glFragmentLightiSGIX = (PFNGLFRAGMENTLIGHTISGIXPROC)gleIntGetProcAddress("glFragmentLightiSGIX");
	if(!TestPointer(glFragmentLightiSGIX)) bIsLoaded = 0;
	glFragmentLightivSGIX = (PFNGLFRAGMENTLIGHTIVSGIXPROC)gleIntGetProcAddress("glFragmentLightivSGIX");
	if(!TestPointer(glFragmentLightivSGIX)) bIsLoaded = 0;
	glFragmentLightModelfSGIX = (PFNGLFRAGMENTLIGHTMODELFSGIXPROC)gleIntGetProcAddress("glFragmentLightModelfSGIX");
	if(!TestPointer(glFragmentLightModelfSGIX)) bIsLoaded = 0;
	glFragmentLightModelfvSGIX = (PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)gleIntGetProcAddress("glFragmentLightModelfvSGIX");
	if(!TestPointer(glFragmentLightModelfvSGIX)) bIsLoaded = 0;
	glFragmentLightModeliSGIX = (PFNGLFRAGMENTLIGHTMODELISGIXPROC)gleIntGetProcAddress("glFragmentLightModeliSGIX");
	if(!TestPointer(glFragmentLightModeliSGIX)) bIsLoaded = 0;
	glFragmentLightModelivSGIX = (PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)gleIntGetProcAddress("glFragmentLightModelivSGIX");
	if(!TestPointer(glFragmentLightModelivSGIX)) bIsLoaded = 0;
	glFragmentMaterialfSGIX = (PFNGLFRAGMENTMATERIALFSGIXPROC)gleIntGetProcAddress("glFragmentMaterialfSGIX");
	if(!TestPointer(glFragmentMaterialfSGIX)) bIsLoaded = 0;
	glFragmentMaterialfvSGIX = (PFNGLFRAGMENTMATERIALFVSGIXPROC)gleIntGetProcAddress("glFragmentMaterialfvSGIX");
	if(!TestPointer(glFragmentMaterialfvSGIX)) bIsLoaded = 0;
	glFragmentMaterialiSGIX = (PFNGLFRAGMENTMATERIALISGIXPROC)gleIntGetProcAddress("glFragmentMaterialiSGIX");
	if(!TestPointer(glFragmentMaterialiSGIX)) bIsLoaded = 0;
	glFragmentMaterialivSGIX = (PFNGLFRAGMENTMATERIALIVSGIXPROC)gleIntGetProcAddress("glFragmentMaterialivSGIX");
	if(!TestPointer(glFragmentMaterialivSGIX)) bIsLoaded = 0;
	glGetFragmentLightfvSGIX = (PFNGLGETFRAGMENTLIGHTFVSGIXPROC)gleIntGetProcAddress("glGetFragmentLightfvSGIX");
	if(!TestPointer(glGetFragmentLightfvSGIX)) bIsLoaded = 0;
	glGetFragmentLightivSGIX = (PFNGLGETFRAGMENTLIGHTIVSGIXPROC)gleIntGetProcAddress("glGetFragmentLightivSGIX");
	if(!TestPointer(glGetFragmentLightivSGIX)) bIsLoaded = 0;
	glGetFragmentMaterialfvSGIX = (PFNGLGETFRAGMENTMATERIALFVSGIXPROC)gleIntGetProcAddress("glGetFragmentMaterialfvSGIX");
	if(!TestPointer(glGetFragmentMaterialfvSGIX)) bIsLoaded = 0;
	glGetFragmentMaterialivSGIX = (PFNGLGETFRAGMENTMATERIALIVSGIXPROC)gleIntGetProcAddress("glGetFragmentMaterialivSGIX");
	if(!TestPointer(glGetFragmentMaterialivSGIX)) bIsLoaded = 0;
	glLightEnviSGIX = (PFNGLLIGHTENVISGIXPROC)gleIntGetProcAddress("glLightEnviSGIX");
	if(!TestPointer(glLightEnviSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLFRAMEZOOMSGIXPROC)(GLint factor);

PFNGLFRAMEZOOMSGIXPROC glFrameZoomSGIX;

static int gleIntLoad_SGIX_framezoom()
{
	int bIsLoaded = 1;
	glFrameZoomSGIX = (PFNGLFRAMEZOOMSGIXPROC)gleIntGetProcAddress("glFrameZoomSGIX");
	if(!TestPointer(glFrameZoomSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef GLint (GLE_FUNCPTR * PFNGLGETINSTRUMENTSSGIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLINSTRUMENTSBUFFERSGIXPROC)(GLsizei size, GLint *buffer);
typedef GLint (GLE_FUNCPTR * PFNGLPOLLINSTRUMENTSSGIXPROC)(GLint *marker_p);
typedef void (GLE_FUNCPTR * PFNGLREADINSTRUMENTSSGIXPROC)(GLint marker);
typedef void (GLE_FUNCPTR * PFNGLSTARTINSTRUMENTSSGIXPROC)();
typedef void (GLE_FUNCPTR * PFNGLSTOPINSTRUMENTSSGIXPROC)(GLint marker);

PFNGLGETINSTRUMENTSSGIXPROC glGetInstrumentsSGIX;
PFNGLINSTRUMENTSBUFFERSGIXPROC glInstrumentsBufferSGIX;
PFNGLPOLLINSTRUMENTSSGIXPROC glPollInstrumentsSGIX;
PFNGLREADINSTRUMENTSSGIXPROC glReadInstrumentsSGIX;
PFNGLSTARTINSTRUMENTSSGIXPROC glStartInstrumentsSGIX;
PFNGLSTOPINSTRUMENTSSGIXPROC glStopInstrumentsSGIX;

static int gleIntLoad_SGIX_instruments()
{
	int bIsLoaded = 1;
	glGetInstrumentsSGIX = (PFNGLGETINSTRUMENTSSGIXPROC)gleIntGetProcAddress("glGetInstrumentsSGIX");
	if(!TestPointer(glGetInstrumentsSGIX)) bIsLoaded = 0;
	glInstrumentsBufferSGIX = (PFNGLINSTRUMENTSBUFFERSGIXPROC)gleIntGetProcAddress("glInstrumentsBufferSGIX");
	if(!TestPointer(glInstrumentsBufferSGIX)) bIsLoaded = 0;
	glPollInstrumentsSGIX = (PFNGLPOLLINSTRUMENTSSGIXPROC)gleIntGetProcAddress("glPollInstrumentsSGIX");
	if(!TestPointer(glPollInstrumentsSGIX)) bIsLoaded = 0;
	glReadInstrumentsSGIX = (PFNGLREADINSTRUMENTSSGIXPROC)gleIntGetProcAddress("glReadInstrumentsSGIX");
	if(!TestPointer(glReadInstrumentsSGIX)) bIsLoaded = 0;
	glStartInstrumentsSGIX = (PFNGLSTARTINSTRUMENTSSGIXPROC)gleIntGetProcAddress("glStartInstrumentsSGIX");
	if(!TestPointer(glStartInstrumentsSGIX)) bIsLoaded = 0;
	glStopInstrumentsSGIX = (PFNGLSTOPINSTRUMENTSSGIXPROC)gleIntGetProcAddress("glStopInstrumentsSGIX");
	if(!TestPointer(glStopInstrumentsSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLGETLISTPARAMETERFVSGIXPROC)(GLuint list, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETLISTPARAMETERIVSGIXPROC)(GLuint list, GLenum pname, GLint *params);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERFSGIXPROC)(GLuint list, GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERFVSGIXPROC)(GLuint list, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERISGIXPROC)(GLuint list, GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLLISTPARAMETERIVSGIXPROC)(GLuint list, GLenum pname, const GLint *params);

PFNGLGETLISTPARAMETERFVSGIXPROC glGetListParameterfvSGIX;
PFNGLGETLISTPARAMETERIVSGIXPROC glGetListParameterivSGIX;
PFNGLLISTPARAMETERFSGIXPROC glListParameterfSGIX;
PFNGLLISTPARAMETERFVSGIXPROC glListParameterfvSGIX;
PFNGLLISTPARAMETERISGIXPROC glListParameteriSGIX;
PFNGLLISTPARAMETERIVSGIXPROC glListParameterivSGIX;

static int gleIntLoad_SGIX_list_priority()
{
	int bIsLoaded = 1;
	glGetListParameterfvSGIX = (PFNGLGETLISTPARAMETERFVSGIXPROC)gleIntGetProcAddress("glGetListParameterfvSGIX");
	if(!TestPointer(glGetListParameterfvSGIX)) bIsLoaded = 0;
	glGetListParameterivSGIX = (PFNGLGETLISTPARAMETERIVSGIXPROC)gleIntGetProcAddress("glGetListParameterivSGIX");
	if(!TestPointer(glGetListParameterivSGIX)) bIsLoaded = 0;
	glListParameterfSGIX = (PFNGLLISTPARAMETERFSGIXPROC)gleIntGetProcAddress("glListParameterfSGIX");
	if(!TestPointer(glListParameterfSGIX)) bIsLoaded = 0;
	glListParameterfvSGIX = (PFNGLLISTPARAMETERFVSGIXPROC)gleIntGetProcAddress("glListParameterfvSGIX");
	if(!TestPointer(glListParameterfvSGIX)) bIsLoaded = 0;
	glListParameteriSGIX = (PFNGLLISTPARAMETERISGIXPROC)gleIntGetProcAddress("glListParameteriSGIX");
	if(!TestPointer(glListParameteriSGIX)) bIsLoaded = 0;
	glListParameterivSGIX = (PFNGLLISTPARAMETERIVSGIXPROC)gleIntGetProcAddress("glListParameterivSGIX");
	if(!TestPointer(glListParameterivSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLPIXELTEXGENSGIXPROC)(GLenum mode);

PFNGLPIXELTEXGENSGIXPROC glPixelTexGenSGIX;

static int gleIntLoad_SGIX_pixel_texture()
{
	int bIsLoaded = 1;
	glPixelTexGenSGIX = (PFNGLPIXELTEXGENSGIXPROC)gleIntGetProcAddress("glPixelTexGenSGIX");
	if(!TestPointer(glPixelTexGenSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLDEFORMATIONMAP3DSGIXPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points);
typedef void (GLE_FUNCPTR * PFNGLDEFORMATIONMAP3FSGIXPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points);
typedef void (GLE_FUNCPTR * PFNGLDEFORMSGIXPROC)(GLbitfield mask);
typedef void (GLE_FUNCPTR * PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)(GLbitfield mask);

PFNGLDEFORMATIONMAP3DSGIXPROC glDeformationMap3dSGIX;
PFNGLDEFORMATIONMAP3FSGIXPROC glDeformationMap3fSGIX;
PFNGLDEFORMSGIXPROC glDeformSGIX;
PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC glLoadIdentityDeformationMapSGIX;

static int gleIntLoad_SGIX_polynomial_ffd()
{
	int bIsLoaded = 1;
	glDeformationMap3dSGIX = (PFNGLDEFORMATIONMAP3DSGIXPROC)gleIntGetProcAddress("glDeformationMap3dSGIX");
	if(!TestPointer(glDeformationMap3dSGIX)) bIsLoaded = 0;
	glDeformationMap3fSGIX = (PFNGLDEFORMATIONMAP3FSGIXPROC)gleIntGetProcAddress("glDeformationMap3fSGIX");
	if(!TestPointer(glDeformationMap3fSGIX)) bIsLoaded = 0;
	glDeformSGIX = (PFNGLDEFORMSGIXPROC)gleIntGetProcAddress("glDeformSGIX");
	if(!TestPointer(glDeformSGIX)) bIsLoaded = 0;
	glLoadIdentityDeformationMapSGIX = (PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)gleIntGetProcAddress("glLoadIdentityDeformationMapSGIX");
	if(!TestPointer(glLoadIdentityDeformationMapSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLREFERENCEPLANESGIXPROC)(const GLdouble *equation);

PFNGLREFERENCEPLANESGIXPROC glReferencePlaneSGIX;

static int gleIntLoad_SGIX_reference_plane()
{
	int bIsLoaded = 1;
	glReferencePlaneSGIX = (PFNGLREFERENCEPLANESGIXPROC)gleIntGetProcAddress("glReferencePlaneSGIX");
	if(!TestPointer(glReferencePlaneSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}




typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERFSGIXPROC)(GLenum pname, GLfloat param);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERFVSGIXPROC)(GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERISGIXPROC)(GLenum pname, GLint param);
typedef void (GLE_FUNCPTR * PFNGLSPRITEPARAMETERIVSGIXPROC)(GLenum pname, const GLint *params);

PFNGLSPRITEPARAMETERFSGIXPROC glSpriteParameterfSGIX;
PFNGLSPRITEPARAMETERFVSGIXPROC glSpriteParameterfvSGIX;
PFNGLSPRITEPARAMETERISGIXPROC glSpriteParameteriSGIX;
PFNGLSPRITEPARAMETERIVSGIXPROC glSpriteParameterivSGIX;

static int gleIntLoad_SGIX_sprite()
{
	int bIsLoaded = 1;
	glSpriteParameterfSGIX = (PFNGLSPRITEPARAMETERFSGIXPROC)gleIntGetProcAddress("glSpriteParameterfSGIX");
	if(!TestPointer(glSpriteParameterfSGIX)) bIsLoaded = 0;
	glSpriteParameterfvSGIX = (PFNGLSPRITEPARAMETERFVSGIXPROC)gleIntGetProcAddress("glSpriteParameterfvSGIX");
	if(!TestPointer(glSpriteParameterfvSGIX)) bIsLoaded = 0;
	glSpriteParameteriSGIX = (PFNGLSPRITEPARAMETERISGIXPROC)gleIntGetProcAddress("glSpriteParameteriSGIX");
	if(!TestPointer(glSpriteParameteriSGIX)) bIsLoaded = 0;
	glSpriteParameterivSGIX = (PFNGLSPRITEPARAMETERIVSGIXPROC)gleIntGetProcAddress("glSpriteParameterivSGIX");
	if(!TestPointer(glSpriteParameterivSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLTAGSAMPLEBUFFERSGIXPROC)();

PFNGLTAGSAMPLEBUFFERSGIXPROC glTagSampleBufferSGIX;

static int gleIntLoad_SGIX_tag_sample_buffer()
{
	int bIsLoaded = 1;
	glTagSampleBufferSGIX = (PFNGLTAGSAMPLEBUFFERSGIXPROC)gleIntGetProcAddress("glTagSampleBufferSGIX");
	if(!TestPointer(glTagSampleBufferSGIX)) bIsLoaded = 0;
	return bIsLoaded;
}










typedef void (GLE_FUNCPTR * PFNGLCOLORTABLESGIPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERFVSGIPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERIVSGIPROC)(GLenum target, GLenum pname, const GLint *params);
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORTABLESGIPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLESGIPROC)(GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)(GLenum target, GLenum pname, GLfloat *params);
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)(GLenum target, GLenum pname, GLint *params);

PFNGLCOLORTABLESGIPROC glColorTableSGI;
PFNGLCOLORTABLEPARAMETERFVSGIPROC glColorTableParameterfvSGI;
PFNGLCOLORTABLEPARAMETERIVSGIPROC glColorTableParameterivSGI;
PFNGLCOPYCOLORTABLESGIPROC glCopyColorTableSGI;
PFNGLGETCOLORTABLESGIPROC glGetColorTableSGI;
PFNGLGETCOLORTABLEPARAMETERFVSGIPROC glGetColorTableParameterfvSGI;
PFNGLGETCOLORTABLEPARAMETERIVSGIPROC glGetColorTableParameterivSGI;

static int gleIntLoad_SGI_color_table()
{
	int bIsLoaded = 1;
	glColorTableSGI = (PFNGLCOLORTABLESGIPROC)gleIntGetProcAddress("glColorTableSGI");
	if(!TestPointer(glColorTableSGI)) bIsLoaded = 0;
	glColorTableParameterfvSGI = (PFNGLCOLORTABLEPARAMETERFVSGIPROC)gleIntGetProcAddress("glColorTableParameterfvSGI");
	if(!TestPointer(glColorTableParameterfvSGI)) bIsLoaded = 0;
	glColorTableParameterivSGI = (PFNGLCOLORTABLEPARAMETERIVSGIPROC)gleIntGetProcAddress("glColorTableParameterivSGI");
	if(!TestPointer(glColorTableParameterivSGI)) bIsLoaded = 0;
	glCopyColorTableSGI = (PFNGLCOPYCOLORTABLESGIPROC)gleIntGetProcAddress("glCopyColorTableSGI");
	if(!TestPointer(glCopyColorTableSGI)) bIsLoaded = 0;
	glGetColorTableSGI = (PFNGLGETCOLORTABLESGIPROC)gleIntGetProcAddress("glGetColorTableSGI");
	if(!TestPointer(glGetColorTableSGI)) bIsLoaded = 0;
	glGetColorTableParameterfvSGI = (PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)gleIntGetProcAddress("glGetColorTableParameterfvSGI");
	if(!TestPointer(glGetColorTableParameterfvSGI)) bIsLoaded = 0;
	glGetColorTableParameterivSGI = (PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)gleIntGetProcAddress("glGetColorTableParameterivSGI");
	if(!TestPointer(glGetColorTableParameterivSGI)) bIsLoaded = 0;
	return bIsLoaded;
}


typedef void (GLE_FUNCPTR * PFNGLFINISHTEXTURESUNXPROC)();

PFNGLFINISHTEXTURESUNXPROC glFinishTextureSUNX;

static int gleIntLoad_SUNX_constant_data()
{
	int bIsLoaded = 1;
	glFinishTextureSUNX = (PFNGLFINISHTEXTURESUNXPROC)gleIntGetProcAddress("glFinishTextureSUNX");
	if(!TestPointer(glFinishTextureSUNX)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORBSUNPROC)(GLbyte factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORSSUNPROC)(GLshort factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORISUNPROC)(GLint factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORFSUNPROC)(GLfloat factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORDSUNPROC)(GLdouble factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUBSUNPROC)(GLubyte factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUSSUNPROC)(GLushort factor);
typedef void (GLE_FUNCPTR * PFNGLGLOBALALPHAFACTORUISUNPROC)(GLuint factor);

PFNGLGLOBALALPHAFACTORBSUNPROC glGlobalAlphaFactorbSUN;
PFNGLGLOBALALPHAFACTORSSUNPROC glGlobalAlphaFactorsSUN;
PFNGLGLOBALALPHAFACTORISUNPROC glGlobalAlphaFactoriSUN;
PFNGLGLOBALALPHAFACTORFSUNPROC glGlobalAlphaFactorfSUN;
PFNGLGLOBALALPHAFACTORDSUNPROC glGlobalAlphaFactordSUN;
PFNGLGLOBALALPHAFACTORUBSUNPROC glGlobalAlphaFactorubSUN;
PFNGLGLOBALALPHAFACTORUSSUNPROC glGlobalAlphaFactorusSUN;
PFNGLGLOBALALPHAFACTORUISUNPROC glGlobalAlphaFactoruiSUN;

static int gleIntLoad_SUN_global_alpha()
{
	int bIsLoaded = 1;
	glGlobalAlphaFactorbSUN = (PFNGLGLOBALALPHAFACTORBSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactorbSUN");
	if(!TestPointer(glGlobalAlphaFactorbSUN)) bIsLoaded = 0;
	glGlobalAlphaFactorsSUN = (PFNGLGLOBALALPHAFACTORSSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactorsSUN");
	if(!TestPointer(glGlobalAlphaFactorsSUN)) bIsLoaded = 0;
	glGlobalAlphaFactoriSUN = (PFNGLGLOBALALPHAFACTORISUNPROC)gleIntGetProcAddress("glGlobalAlphaFactoriSUN");
	if(!TestPointer(glGlobalAlphaFactoriSUN)) bIsLoaded = 0;
	glGlobalAlphaFactorfSUN = (PFNGLGLOBALALPHAFACTORFSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactorfSUN");
	if(!TestPointer(glGlobalAlphaFactorfSUN)) bIsLoaded = 0;
	glGlobalAlphaFactordSUN = (PFNGLGLOBALALPHAFACTORDSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactordSUN");
	if(!TestPointer(glGlobalAlphaFactordSUN)) bIsLoaded = 0;
	glGlobalAlphaFactorubSUN = (PFNGLGLOBALALPHAFACTORUBSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactorubSUN");
	if(!TestPointer(glGlobalAlphaFactorubSUN)) bIsLoaded = 0;
	glGlobalAlphaFactorusSUN = (PFNGLGLOBALALPHAFACTORUSSUNPROC)gleIntGetProcAddress("glGlobalAlphaFactorusSUN");
	if(!TestPointer(glGlobalAlphaFactorusSUN)) bIsLoaded = 0;
	glGlobalAlphaFactoruiSUN = (PFNGLGLOBALALPHAFACTORUISUNPROC)gleIntGetProcAddress("glGlobalAlphaFactoruiSUN");
	if(!TestPointer(glGlobalAlphaFactoruiSUN)) bIsLoaded = 0;
	return bIsLoaded;
}
typedef void (GLE_FUNCPTR * PFNGLDRAWMESHARRAYSSUNPROC)(GLenum mode, GLint first, GLsizei count, GLsizei width);

PFNGLDRAWMESHARRAYSSUNPROC glDrawMeshArraysSUN;

static int gleIntLoad_SUN_mesh_array()
{
	int bIsLoaded = 1;
	glDrawMeshArraysSUN = (PFNGLDRAWMESHARRAYSSUNPROC)gleIntGetProcAddress("glDrawMeshArraysSUN");
	if(!TestPointer(glDrawMeshArraysSUN)) bIsLoaded = 0;
	return bIsLoaded;
}

typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUISUNPROC)(GLuint code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUSSUNPROC)(GLushort code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUBSUNPROC)(GLubyte code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUIVSUNPROC)(const GLuint *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUSVSUNPROC)(const GLushort *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEUBVSUNPROC)(const GLubyte *code);
typedef void (GLE_FUNCPTR * PFNGLREPLACEMENTCODEPOINTERSUNPROC)(GLenum type, GLsizei stride, const GLvoid* *pointer);

PFNGLREPLACEMENTCODEUISUNPROC glReplacementCodeuiSUN;
PFNGLREPLACEMENTCODEUSSUNPROC glReplacementCodeusSUN;
PFNGLREPLACEMENTCODEUBSUNPROC glReplacementCodeubSUN;
PFNGLREPLACEMENTCODEUIVSUNPROC glReplacementCodeuivSUN;
PFNGLREPLACEMENTCODEUSVSUNPROC glReplacementCodeusvSUN;
PFNGLREPLACEMENTCODEUBVSUNPROC glReplacementCodeubvSUN;
PFNGLREPLACEMENTCODEPOINTERSUNPROC glReplacementCodePointerSUN;

static int gleIntLoad_SUN_triangle_list()
{
	int bIsLoaded = 1;
	glReplacementCodeuiSUN = (PFNGLREPLACEMENTCODEUISUNPROC)gleIntGetProcAddress("glReplacementCodeuiSUN");
	if(!TestPointer(glReplacementCodeuiSUN)) bIsLoaded = 0;
	glReplacementCodeusSUN = (PFNGLREPLACEMENTCODEUSSUNPROC)gleIntGetProcAddress("glReplacementCodeusSUN");
	if(!TestPointer(glReplacementCodeusSUN)) bIsLoaded = 0;
	glReplacementCodeubSUN = (PFNGLREPLACEMENTCODEUBSUNPROC)gleIntGetProcAddress("glReplacementCodeubSUN");
	if(!TestPointer(glReplacementCodeubSUN)) bIsLoaded = 0;
	glReplacementCodeuivSUN = (PFNGLREPLACEMENTCODEUIVSUNPROC)gleIntGetProcAddress("glReplacementCodeuivSUN");
	if(!TestPointer(glReplacementCodeuivSUN)) bIsLoaded = 0;
	glReplacementCodeusvSUN = (PFNGLREPLACEMENTCODEUSVSUNPROC)gleIntGetProcAddress("glReplacementCodeusvSUN");
	if(!TestPointer(glReplacementCodeusvSUN)) bIsLoaded = 0;
	glReplacementCodeubvSUN = (PFNGLREPLACEMENTCODEUBVSUNPROC)gleIntGetProcAddress("glReplacementCodeubvSUN");
	if(!TestPointer(glReplacementCodeubvSUN)) bIsLoaded = 0;
	glReplacementCodePointerSUN = (PFNGLREPLACEMENTCODEPOINTERSUNPROC)gleIntGetProcAddress("glReplacementCodePointerSUN");
	if(!TestPointer(glReplacementCodePointerSUN)) bIsLoaded = 0;
	return bIsLoaded;
}
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

PFNGLCOLOR4UBVERTEX2FSUNPROC glColor4ubVertex2fSUN;
PFNGLCOLOR4UBVERTEX2FVSUNPROC glColor4ubVertex2fvSUN;
PFNGLCOLOR4UBVERTEX3FSUNPROC glColor4ubVertex3fSUN;
PFNGLCOLOR4UBVERTEX3FVSUNPROC glColor4ubVertex3fvSUN;
PFNGLCOLOR3FVERTEX3FSUNPROC glColor3fVertex3fSUN;
PFNGLCOLOR3FVERTEX3FVSUNPROC glColor3fVertex3fvSUN;
PFNGLNORMAL3FVERTEX3FSUNPROC glNormal3fVertex3fSUN;
PFNGLNORMAL3FVERTEX3FVSUNPROC glNormal3fVertex3fvSUN;
PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC glColor4fNormal3fVertex3fSUN;
PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC glColor4fNormal3fVertex3fvSUN;
PFNGLTEXCOORD2FVERTEX3FSUNPROC glTexCoord2fVertex3fSUN;
PFNGLTEXCOORD2FVERTEX3FVSUNPROC glTexCoord2fVertex3fvSUN;
PFNGLTEXCOORD4FVERTEX4FSUNPROC glTexCoord4fVertex4fSUN;
PFNGLTEXCOORD4FVERTEX4FVSUNPROC glTexCoord4fVertex4fvSUN;
PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC glTexCoord2fColor4ubVertex3fSUN;
PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC glTexCoord2fColor4ubVertex3fvSUN;
PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC glTexCoord2fColor3fVertex3fSUN;
PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC glTexCoord2fColor3fVertex3fvSUN;
PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC glTexCoord2fNormal3fVertex3fSUN;
PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC glTexCoord2fNormal3fVertex3fvSUN;
PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC glTexCoord2fColor4fNormal3fVertex3fSUN;
PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC glTexCoord2fColor4fNormal3fVertex3fvSUN;
PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC glTexCoord4fColor4fNormal3fVertex4fSUN;
PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC glTexCoord4fColor4fNormal3fVertex4fvSUN;
PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC glReplacementCodeuiVertex3fSUN;
PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC glReplacementCodeuiVertex3fvSUN;
PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC glReplacementCodeuiColor4ubVertex3fSUN;
PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC glReplacementCodeuiColor4ubVertex3fvSUN;
PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC glReplacementCodeuiColor3fVertex3fSUN;
PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC glReplacementCodeuiColor3fVertex3fvSUN;
PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC glReplacementCodeuiNormal3fVertex3fSUN;
PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiNormal3fVertex3fvSUN;
PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiColor4fNormal3fVertex3fSUN;
PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiColor4fNormal3fVertex3fvSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fVertex3fSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fVertex3fvSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN;
PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN;

static int gleIntLoad_SUN_vertex()
{
	int bIsLoaded = 1;
	glColor4ubVertex2fSUN = (PFNGLCOLOR4UBVERTEX2FSUNPROC)gleIntGetProcAddress("glColor4ubVertex2fSUN");
	if(!TestPointer(glColor4ubVertex2fSUN)) bIsLoaded = 0;
	glColor4ubVertex2fvSUN = (PFNGLCOLOR4UBVERTEX2FVSUNPROC)gleIntGetProcAddress("glColor4ubVertex2fvSUN");
	if(!TestPointer(glColor4ubVertex2fvSUN)) bIsLoaded = 0;
	glColor4ubVertex3fSUN = (PFNGLCOLOR4UBVERTEX3FSUNPROC)gleIntGetProcAddress("glColor4ubVertex3fSUN");
	if(!TestPointer(glColor4ubVertex3fSUN)) bIsLoaded = 0;
	glColor4ubVertex3fvSUN = (PFNGLCOLOR4UBVERTEX3FVSUNPROC)gleIntGetProcAddress("glColor4ubVertex3fvSUN");
	if(!TestPointer(glColor4ubVertex3fvSUN)) bIsLoaded = 0;
	glColor3fVertex3fSUN = (PFNGLCOLOR3FVERTEX3FSUNPROC)gleIntGetProcAddress("glColor3fVertex3fSUN");
	if(!TestPointer(glColor3fVertex3fSUN)) bIsLoaded = 0;
	glColor3fVertex3fvSUN = (PFNGLCOLOR3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glColor3fVertex3fvSUN");
	if(!TestPointer(glColor3fVertex3fvSUN)) bIsLoaded = 0;
	glNormal3fVertex3fSUN = (PFNGLNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glNormal3fVertex3fSUN");
	if(!TestPointer(glNormal3fVertex3fSUN)) bIsLoaded = 0;
	glNormal3fVertex3fvSUN = (PFNGLNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glNormal3fVertex3fvSUN");
	if(!TestPointer(glNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glColor4fNormal3fVertex3fSUN = (PFNGLCOLOR4FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glColor4fNormal3fVertex3fSUN");
	if(!TestPointer(glColor4fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glColor4fNormal3fVertex3fvSUN = (PFNGLCOLOR4FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glColor4fNormal3fVertex3fvSUN");
	if(!TestPointer(glColor4fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord2fVertex3fSUN = (PFNGLTEXCOORD2FVERTEX3FSUNPROC)gleIntGetProcAddress("glTexCoord2fVertex3fSUN");
	if(!TestPointer(glTexCoord2fVertex3fSUN)) bIsLoaded = 0;
	glTexCoord2fVertex3fvSUN = (PFNGLTEXCOORD2FVERTEX3FVSUNPROC)gleIntGetProcAddress("glTexCoord2fVertex3fvSUN");
	if(!TestPointer(glTexCoord2fVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord4fVertex4fSUN = (PFNGLTEXCOORD4FVERTEX4FSUNPROC)gleIntGetProcAddress("glTexCoord4fVertex4fSUN");
	if(!TestPointer(glTexCoord4fVertex4fSUN)) bIsLoaded = 0;
	glTexCoord4fVertex4fvSUN = (PFNGLTEXCOORD4FVERTEX4FVSUNPROC)gleIntGetProcAddress("glTexCoord4fVertex4fvSUN");
	if(!TestPointer(glTexCoord4fVertex4fvSUN)) bIsLoaded = 0;
	glTexCoord2fColor4ubVertex3fSUN = (PFNGLTEXCOORD2FCOLOR4UBVERTEX3FSUNPROC)gleIntGetProcAddress("glTexCoord2fColor4ubVertex3fSUN");
	if(!TestPointer(glTexCoord2fColor4ubVertex3fSUN)) bIsLoaded = 0;
	glTexCoord2fColor4ubVertex3fvSUN = (PFNGLTEXCOORD2FCOLOR4UBVERTEX3FVSUNPROC)gleIntGetProcAddress("glTexCoord2fColor4ubVertex3fvSUN");
	if(!TestPointer(glTexCoord2fColor4ubVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord2fColor3fVertex3fSUN = (PFNGLTEXCOORD2FCOLOR3FVERTEX3FSUNPROC)gleIntGetProcAddress("glTexCoord2fColor3fVertex3fSUN");
	if(!TestPointer(glTexCoord2fColor3fVertex3fSUN)) bIsLoaded = 0;
	glTexCoord2fColor3fVertex3fvSUN = (PFNGLTEXCOORD2FCOLOR3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glTexCoord2fColor3fVertex3fvSUN");
	if(!TestPointer(glTexCoord2fColor3fVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord2fNormal3fVertex3fSUN = (PFNGLTEXCOORD2FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glTexCoord2fNormal3fVertex3fSUN");
	if(!TestPointer(glTexCoord2fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glTexCoord2fNormal3fVertex3fvSUN = (PFNGLTEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glTexCoord2fNormal3fVertex3fvSUN");
	if(!TestPointer(glTexCoord2fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord2fColor4fNormal3fVertex3fSUN = (PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glTexCoord2fColor4fNormal3fVertex3fSUN");
	if(!TestPointer(glTexCoord2fColor4fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glTexCoord2fColor4fNormal3fVertex3fvSUN = (PFNGLTEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glTexCoord2fColor4fNormal3fVertex3fvSUN");
	if(!TestPointer(glTexCoord2fColor4fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glTexCoord4fColor4fNormal3fVertex4fSUN = (PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FSUNPROC)gleIntGetProcAddress("glTexCoord4fColor4fNormal3fVertex4fSUN");
	if(!TestPointer(glTexCoord4fColor4fNormal3fVertex4fSUN)) bIsLoaded = 0;
	glTexCoord4fColor4fNormal3fVertex4fvSUN = (PFNGLTEXCOORD4FCOLOR4FNORMAL3FVERTEX4FVSUNPROC)gleIntGetProcAddress("glTexCoord4fColor4fNormal3fVertex4fvSUN");
	if(!TestPointer(glTexCoord4fColor4fNormal3fVertex4fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiVertex3fSUN = (PFNGLREPLACEMENTCODEUIVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiVertex3fvSUN = (PFNGLREPLACEMENTCODEUIVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor4ubVertex3fSUN = (PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor4ubVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiColor4ubVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor4ubVertex3fvSUN = (PFNGLREPLACEMENTCODEUICOLOR4UBVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor4ubVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiColor4ubVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor3fVertex3fSUN = (PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor3fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiColor3fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor3fVertex3fvSUN = (PFNGLREPLACEMENTCODEUICOLOR3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor3fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiColor3fVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiNormal3fVertex3fSUN = (PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiNormal3fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiNormal3fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiNormal3fVertex3fvSUN = (PFNGLREPLACEMENTCODEUINORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiNormal3fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor4fNormal3fVertex3fSUN = (PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor4fNormal3fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiColor4fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiColor4fNormal3fVertex3fvSUN = (PFNGLREPLACEMENTCODEUICOLOR4FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiColor4fNormal3fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiColor4fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fVertex3fSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fVertex3fvSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN)) bIsLoaded = 0;
	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN = (PFNGLREPLACEMENTCODEUITEXCOORD2FCOLOR4FNORMAL3FVERTEX3FVSUNPROC)gleIntGetProcAddress("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");
	if(!TestPointer(glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN)) bIsLoaded = 0;
	return bIsLoaded;
}


StrToExtMap gleIntExtensionMap[] = {
	{"GL_3DFX_multisample", &glext_3DFX_multisample, NULL},
	{"GL_3DFX_tbuffer", &glext_3DFX_tbuffer, gleIntLoad_3DFX_tbuffer},
	{"GL_3DFX_texture_compression_FXT1", &glext_3DFX_texture_compression_FXT1, NULL},
	{"GL_AMD_conservative_depth", &glext_AMD_conservative_depth, NULL},
	{"GL_AMD_debug_output", &glext_AMD_debug_output, gleIntLoad_AMD_debug_output},
	{"GL_AMD_draw_buffers_blend", &glext_AMD_draw_buffers_blend, gleIntLoad_AMD_draw_buffers_blend},
	{"GL_AMD_name_gen_delete", &glext_AMD_name_gen_delete, gleIntLoad_AMD_name_gen_delete},
	{"GL_AMD_performance_monitor", &glext_AMD_performance_monitor, gleIntLoad_AMD_performance_monitor},
	{"GL_AMD_seamless_cubemap_per_texture", &glext_AMD_seamless_cubemap_per_texture, NULL},
	{"GL_AMD_shader_stencil_export", &glext_AMD_shader_stencil_export, NULL},
	{"GL_AMD_texture_texture4", &glext_AMD_texture_texture4, NULL},
	{"GL_AMD_transform_feedback3_lines_triangles", &glext_AMD_transform_feedback3_lines_triangles, NULL},
	{"GL_AMD_vertex_shader_tesselator", &glext_AMD_vertex_shader_tesselator, gleIntLoad_AMD_vertex_shader_tesselator},
	{"GL_APPLE_aux_depth_stencil", &glext_APPLE_aux_depth_stencil, NULL},
	{"GL_APPLE_client_storage", &glext_APPLE_client_storage, NULL},
	{"GL_APPLE_element_array", &glext_APPLE_element_array, gleIntLoad_APPLE_element_array},
	{"GL_APPLE_fence", &glext_APPLE_fence, gleIntLoad_APPLE_fence},
	{"GL_APPLE_float_pixels", &glext_APPLE_float_pixels, NULL},
	{"GL_APPLE_flush_buffer_range", &glext_APPLE_flush_buffer_range, gleIntLoad_APPLE_flush_buffer_range},
	{"GL_APPLE_object_purgeable", &glext_APPLE_object_purgeable, gleIntLoad_APPLE_object_purgeable},
	{"GL_APPLE_rgb_422", &glext_APPLE_rgb_422, NULL},
	{"GL_APPLE_row_bytes", &glext_APPLE_row_bytes, NULL},
	{"GL_APPLE_specular_vector", &glext_APPLE_specular_vector, NULL},
	{"GL_APPLE_texture_range", &glext_APPLE_texture_range, gleIntLoad_APPLE_texture_range},
	{"GL_APPLE_transform_hint", &glext_APPLE_transform_hint, NULL},
	{"GL_APPLE_vertex_array_object", &glext_APPLE_vertex_array_object, gleIntLoad_APPLE_vertex_array_object},
	{"GL_APPLE_vertex_array_range", &glext_APPLE_vertex_array_range, gleIntLoad_APPLE_vertex_array_range},
	{"GL_APPLE_vertex_program_evaluators", &glext_APPLE_vertex_program_evaluators, gleIntLoad_APPLE_vertex_program_evaluators},
	{"GL_APPLE_ycbcr_422", &glext_APPLE_ycbcr_422, NULL},
	{"GL_ARB_ES2_compatibility", &glext_ARB_ES2_compatibility, gleIntLoad_ARB_ES2_compatibility},
	{"GL_ARB_blend_func_extended", &glext_ARB_blend_func_extended, gleIntLoad_ARB_blend_func_extended},
	{"GL_ARB_cl_event", &glext_ARB_cl_event, gleIntLoad_ARB_cl_event},
	{"GL_ARB_color_buffer_float", &glext_ARB_color_buffer_float, gleIntLoad_ARB_color_buffer_float},
	{"GL_ARB_compatibility", &glext_ARB_compatibility, NULL},
	{"GL_ARB_copy_buffer", &glext_ARB_copy_buffer, gleIntLoad_ARB_copy_buffer},
	{"GL_ARB_debug_output", &glext_ARB_debug_output, gleIntLoad_ARB_debug_output},
	{"GL_ARB_depth_buffer_float", &glext_ARB_depth_buffer_float, NULL},
	{"GL_ARB_depth_clamp", &glext_ARB_depth_clamp, NULL},
	{"GL_ARB_depth_texture", &glext_ARB_depth_texture, NULL},
	{"GL_ARB_draw_buffers", &glext_ARB_draw_buffers, gleIntLoad_ARB_draw_buffers},
	{"GL_ARB_draw_buffers_blend", &glext_ARB_draw_buffers_blend, gleIntLoad_ARB_draw_buffers_blend},
	{"GL_ARB_draw_elements_base_vertex", &glext_ARB_draw_elements_base_vertex, gleIntLoad_ARB_draw_elements_base_vertex},
	{"GL_ARB_draw_indirect", &glext_ARB_draw_indirect, gleIntLoad_ARB_draw_indirect},
	{"GL_ARB_draw_instanced", &glext_ARB_draw_instanced, gleIntLoad_ARB_draw_instanced},
	{"GL_ARB_explicit_attrib_location", &glext_ARB_explicit_attrib_location, NULL},
	{"GL_ARB_fragment_coord_conventions", &glext_ARB_fragment_coord_conventions, NULL},
	{"GL_ARB_fragment_program", &glext_ARB_fragment_program, NULL},
	{"GL_ARB_fragment_program_shadow", &glext_ARB_fragment_program_shadow, NULL},
	{"GL_ARB_fragment_shader", &glext_ARB_fragment_shader, NULL},
	{"GL_ARB_framebuffer_object", &glext_ARB_framebuffer_object, gleIntLoad_ARB_framebuffer_object},
	{"GL_ARB_framebuffer_sRGB", &glext_ARB_framebuffer_sRGB, NULL},
	{"GL_ARB_geometry_shader4", &glext_ARB_geometry_shader4, gleIntLoad_ARB_geometry_shader4},
	{"GL_ARB_get_program_binary", &glext_ARB_get_program_binary, gleIntLoad_ARB_get_program_binary},
	{"GL_ARB_gpu_shader5", &glext_ARB_gpu_shader5, NULL},
	{"GL_ARB_gpu_shader_fp64", &glext_ARB_gpu_shader_fp64, gleIntLoad_ARB_gpu_shader_fp64},
	{"GL_ARB_half_float_pixel", &glext_ARB_half_float_pixel, NULL},
	{"GL_ARB_half_float_vertex", &glext_ARB_half_float_vertex, NULL},
	{"GL_ARB_imaging", &glext_ARB_imaging, NULL},
	{"GL_ARB_instanced_arrays", &glext_ARB_instanced_arrays, gleIntLoad_ARB_instanced_arrays},
	{"GL_ARB_map_buffer_range", &glext_ARB_map_buffer_range, gleIntLoad_ARB_map_buffer_range},
	{"GL_ARB_matrix_palette", &glext_ARB_matrix_palette, gleIntLoad_ARB_matrix_palette},
	{"GL_ARB_multisample", &glext_ARB_multisample, gleIntLoad_ARB_multisample},
	{"GL_ARB_multitexture", &glext_ARB_multitexture, gleIntLoad_ARB_multitexture},
	{"GL_ARB_occlusion_query", &glext_ARB_occlusion_query, gleIntLoad_ARB_occlusion_query},
	{"GL_ARB_occlusion_query2", &glext_ARB_occlusion_query2, NULL},
	{"GL_ARB_pixel_buffer_object", &glext_ARB_pixel_buffer_object, NULL},
	{"GL_ARB_point_parameters", &glext_ARB_point_parameters, gleIntLoad_ARB_point_parameters},
	{"GL_ARB_point_sprite", &glext_ARB_point_sprite, NULL},
	{"GL_ARB_provoking_vertex", &glext_ARB_provoking_vertex, gleIntLoad_ARB_provoking_vertex},
	{"GL_ARB_robustness", &glext_ARB_robustness, gleIntLoad_ARB_robustness},
	{"GL_ARB_sample_shading", &glext_ARB_sample_shading, gleIntLoad_ARB_sample_shading},
	{"GL_ARB_sampler_objects", &glext_ARB_sampler_objects, gleIntLoad_ARB_sampler_objects},
	{"GL_ARB_seamless_cube_map", &glext_ARB_seamless_cube_map, NULL},
	{"GL_ARB_separate_shader_objects", &glext_ARB_separate_shader_objects, gleIntLoad_ARB_separate_shader_objects},
	{"GL_ARB_shader_bit_encoding", &glext_ARB_shader_bit_encoding, NULL},
	{"GL_ARB_shader_objects", &glext_ARB_shader_objects, gleIntLoad_ARB_shader_objects},
	{"GL_ARB_shader_precision", &glext_ARB_shader_precision, NULL},
	{"GL_ARB_shader_stencil_export", &glext_ARB_shader_stencil_export, NULL},
	{"GL_ARB_shader_subroutine", &glext_ARB_shader_subroutine, gleIntLoad_ARB_shader_subroutine},
	{"GL_ARB_shader_texture_lod", &glext_ARB_shader_texture_lod, NULL},
	{"GL_ARB_shading_language_100", &glext_ARB_shading_language_100, NULL},
	{"GL_ARB_shading_language_include", &glext_ARB_shading_language_include, gleIntLoad_ARB_shading_language_include},
	{"GL_ARB_shadow", &glext_ARB_shadow, NULL},
	{"GL_ARB_shadow_ambient", &glext_ARB_shadow_ambient, NULL},
	{"GL_ARB_sync", &glext_ARB_sync, gleIntLoad_ARB_sync},
	{"GL_ARB_tessellation_shader", &glext_ARB_tessellation_shader, gleIntLoad_ARB_tessellation_shader},
	{"GL_ARB_texture_border_clamp", &glext_ARB_texture_border_clamp, NULL},
	{"GL_ARB_texture_buffer_object", &glext_ARB_texture_buffer_object, gleIntLoad_ARB_texture_buffer_object},
	{"GL_ARB_texture_buffer_object_rgb32", &glext_ARB_texture_buffer_object_rgb32, NULL},
	{"GL_ARB_texture_compression", &glext_ARB_texture_compression, gleIntLoad_ARB_texture_compression},
	{"GL_ARB_texture_compression_bptc", &glext_ARB_texture_compression_bptc, NULL},
	{"GL_ARB_texture_compression_rgtc", &glext_ARB_texture_compression_rgtc, NULL},
	{"GL_ARB_texture_cube_map", &glext_ARB_texture_cube_map, NULL},
	{"GL_ARB_texture_cube_map_array", &glext_ARB_texture_cube_map_array, NULL},
	{"GL_ARB_texture_env_add", &glext_ARB_texture_env_add, NULL},
	{"GL_ARB_texture_env_combine", &glext_ARB_texture_env_combine, NULL},
	{"GL_ARB_texture_env_crossbar", &glext_ARB_texture_env_crossbar, NULL},
	{"GL_ARB_texture_env_dot3", &glext_ARB_texture_env_dot3, NULL},
	{"GL_ARB_texture_float", &glext_ARB_texture_float, NULL},
	{"GL_ARB_texture_gather", &glext_ARB_texture_gather, NULL},
	{"GL_ARB_texture_mirrored_repeat", &glext_ARB_texture_mirrored_repeat, NULL},
	{"GL_ARB_texture_multisample", &glext_ARB_texture_multisample, gleIntLoad_ARB_texture_multisample},
	{"GL_ARB_texture_non_power_of_two", &glext_ARB_texture_non_power_of_two, NULL},
	{"GL_ARB_texture_query_lod", &glext_ARB_texture_query_lod, NULL},
	{"GL_ARB_texture_rectangle", &glext_ARB_texture_rectangle, NULL},
	{"GL_ARB_texture_rg", &glext_ARB_texture_rg, NULL},
	{"GL_ARB_texture_rgb10_a2ui", &glext_ARB_texture_rgb10_a2ui, NULL},
	{"GL_ARB_texture_swizzle", &glext_ARB_texture_swizzle, NULL},
	{"GL_ARB_timer_query", &glext_ARB_timer_query, gleIntLoad_ARB_timer_query},
	{"GL_ARB_transform_feedback2", &glext_ARB_transform_feedback2, gleIntLoad_ARB_transform_feedback2},
	{"GL_ARB_transform_feedback3", &glext_ARB_transform_feedback3, gleIntLoad_ARB_transform_feedback3},
	{"GL_ARB_transpose_matrix", &glext_ARB_transpose_matrix, gleIntLoad_ARB_transpose_matrix},
	{"GL_ARB_uniform_buffer_object", &glext_ARB_uniform_buffer_object, gleIntLoad_ARB_uniform_buffer_object},
	{"GL_ARB_vertex_array_bgra", &glext_ARB_vertex_array_bgra, NULL},
	{"GL_ARB_vertex_array_object", &glext_ARB_vertex_array_object, gleIntLoad_ARB_vertex_array_object},
	{"GL_ARB_vertex_attrib_64bit", &glext_ARB_vertex_attrib_64bit, gleIntLoad_ARB_vertex_attrib_64bit},
	{"GL_ARB_vertex_blend", &glext_ARB_vertex_blend, gleIntLoad_ARB_vertex_blend},
	{"GL_ARB_vertex_buffer_object", &glext_ARB_vertex_buffer_object, gleIntLoad_ARB_vertex_buffer_object},
	{"GL_ARB_vertex_program", &glext_ARB_vertex_program, gleIntLoad_ARB_vertex_program},
	{"GL_ARB_vertex_shader", &glext_ARB_vertex_shader, gleIntLoad_ARB_vertex_shader},
	{"GL_ARB_vertex_type_2_10_10_10_rev", &glext_ARB_vertex_type_2_10_10_10_rev, gleIntLoad_ARB_vertex_type_2_10_10_10_rev},
	{"GL_ARB_viewport_array", &glext_ARB_viewport_array, gleIntLoad_ARB_viewport_array},
	{"GL_ARB_window_pos", &glext_ARB_window_pos, gleIntLoad_ARB_window_pos},
	{"GL_ATI_draw_buffers", &glext_ATI_draw_buffers, gleIntLoad_ATI_draw_buffers},
	{"GL_ATI_element_array", &glext_ATI_element_array, gleIntLoad_ATI_element_array},
	{"GL_ATI_envmap_bumpmap", &glext_ATI_envmap_bumpmap, gleIntLoad_ATI_envmap_bumpmap},
	{"GL_ATI_fragment_shader", &glext_ATI_fragment_shader, gleIntLoad_ATI_fragment_shader},
	{"GL_ATI_map_object_buffer", &glext_ATI_map_object_buffer, gleIntLoad_ATI_map_object_buffer},
	{"GL_ATI_meminfo", &glext_ATI_meminfo, NULL},
	{"GL_ATI_pixel_format_float", &glext_ATI_pixel_format_float, NULL},
	{"GL_ATI_pn_triangles", &glext_ATI_pn_triangles, gleIntLoad_ATI_pn_triangles},
	{"GL_ATI_separate_stencil", &glext_ATI_separate_stencil, gleIntLoad_ATI_separate_stencil},
	{"GL_ATI_text_fragment_shader", &glext_ATI_text_fragment_shader, NULL},
	{"GL_ATI_texture_env_combine3", &glext_ATI_texture_env_combine3, NULL},
	{"GL_ATI_texture_float", &glext_ATI_texture_float, NULL},
	{"GL_ATI_texture_mirror_once", &glext_ATI_texture_mirror_once, NULL},
	{"GL_ATI_vertex_array_object", &glext_ATI_vertex_array_object, gleIntLoad_ATI_vertex_array_object},
	{"GL_ATI_vertex_attrib_array_object", &glext_ATI_vertex_attrib_array_object, gleIntLoad_ATI_vertex_attrib_array_object},
	{"GL_ATI_vertex_streams", &glext_ATI_vertex_streams, gleIntLoad_ATI_vertex_streams},
	{"GL_EXT_422_pixels", &glext_EXT_422_pixels, NULL},
	{"GL_EXT_abgr", &glext_EXT_abgr, NULL},
	{"GL_EXT_bgra", &glext_EXT_bgra, NULL},
	{"GL_EXT_bindable_uniform", &glext_EXT_bindable_uniform, gleIntLoad_EXT_bindable_uniform},
	{"GL_EXT_blend_color", &glext_EXT_blend_color, gleIntLoad_EXT_blend_color},
	{"GL_EXT_blend_equation_separate", &glext_EXT_blend_equation_separate, gleIntLoad_EXT_blend_equation_separate},
	{"GL_EXT_blend_func_separate", &glext_EXT_blend_func_separate, gleIntLoad_EXT_blend_func_separate},
	{"GL_EXT_blend_logic_op", &glext_EXT_blend_logic_op, NULL},
	{"GL_EXT_blend_minmax", &glext_EXT_blend_minmax, gleIntLoad_EXT_blend_minmax},
	{"GL_EXT_blend_subtract", &glext_EXT_blend_subtract, NULL},
	{"GL_EXT_clip_volume_hint", &glext_EXT_clip_volume_hint, NULL},
	{"GL_EXT_cmyka", &glext_EXT_cmyka, NULL},
	{"GL_EXT_color_subtable", &glext_EXT_color_subtable, gleIntLoad_EXT_color_subtable},
	{"GL_EXT_compiled_vertex_array", &glext_EXT_compiled_vertex_array, gleIntLoad_EXT_compiled_vertex_array},
	{"GL_EXT_convolution", &glext_EXT_convolution, gleIntLoad_EXT_convolution},
	{"GL_EXT_coordinate_frame", &glext_EXT_coordinate_frame, gleIntLoad_EXT_coordinate_frame},
	{"GL_EXT_copy_texture", &glext_EXT_copy_texture, gleIntLoad_EXT_copy_texture},
	{"GL_EXT_cull_vertex", &glext_EXT_cull_vertex, gleIntLoad_EXT_cull_vertex},
	{"GL_EXT_depth_bounds_test", &glext_EXT_depth_bounds_test, gleIntLoad_EXT_depth_bounds_test},
	{"GL_EXT_direct_state_access", &glext_EXT_direct_state_access, gleIntLoad_EXT_direct_state_access},
	{"GL_EXT_draw_buffers2", &glext_EXT_draw_buffers2, gleIntLoad_EXT_draw_buffers2},
	{"GL_EXT_draw_instanced", &glext_EXT_draw_instanced, gleIntLoad_EXT_draw_instanced},
	{"GL_EXT_draw_range_elements", &glext_EXT_draw_range_elements, gleIntLoad_EXT_draw_range_elements},
	{"GL_EXT_fog_coord", &glext_EXT_fog_coord, gleIntLoad_EXT_fog_coord},
	{"GL_EXT_framebuffer_blit", &glext_EXT_framebuffer_blit, gleIntLoad_EXT_framebuffer_blit},
	{"GL_EXT_framebuffer_multisample", &glext_EXT_framebuffer_multisample, gleIntLoad_EXT_framebuffer_multisample},
	{"GL_EXT_framebuffer_object", &glext_EXT_framebuffer_object, gleIntLoad_EXT_framebuffer_object},
	{"GL_EXT_framebuffer_sRGB", &glext_EXT_framebuffer_sRGB, NULL},
	{"GL_EXT_geometry_shader4", &glext_EXT_geometry_shader4, gleIntLoad_EXT_geometry_shader4},
	{"GL_EXT_gpu_program_parameters", &glext_EXT_gpu_program_parameters, gleIntLoad_EXT_gpu_program_parameters},
	{"GL_EXT_gpu_shader4", &glext_EXT_gpu_shader4, gleIntLoad_EXT_gpu_shader4},
	{"GL_EXT_histogram", &glext_EXT_histogram, gleIntLoad_EXT_histogram},
	{"GL_EXT_index_array_formats", &glext_EXT_index_array_formats, NULL},
	{"GL_EXT_index_func", &glext_EXT_index_func, gleIntLoad_EXT_index_func},
	{"GL_EXT_index_material", &glext_EXT_index_material, gleIntLoad_EXT_index_material},
	{"GL_EXT_index_texture", &glext_EXT_index_texture, NULL},
	{"GL_EXT_light_texture", &glext_EXT_light_texture, gleIntLoad_EXT_light_texture},
	{"GL_EXT_misc_attribute", &glext_EXT_misc_attribute, NULL},
	{"GL_EXT_multi_draw_arrays", &glext_EXT_multi_draw_arrays, gleIntLoad_EXT_multi_draw_arrays},
	{"GL_EXT_multisample", &glext_EXT_multisample, gleIntLoad_EXT_multisample},
	{"GL_EXT_packed_depth_stencil", &glext_EXT_packed_depth_stencil, NULL},
	{"GL_EXT_packed_float", &glext_EXT_packed_float, NULL},
	{"GL_EXT_packed_pixels", &glext_EXT_packed_pixels, NULL},
	{"GL_EXT_paletted_texture", &glext_EXT_paletted_texture, gleIntLoad_EXT_paletted_texture},
	{"GL_EXT_pixel_buffer_object", &glext_EXT_pixel_buffer_object, NULL},
	{"GL_EXT_pixel_transform", &glext_EXT_pixel_transform, gleIntLoad_EXT_pixel_transform},
	{"GL_EXT_pixel_transform_color_table", &glext_EXT_pixel_transform_color_table, NULL},
	{"GL_EXT_point_parameters", &glext_EXT_point_parameters, gleIntLoad_EXT_point_parameters},
	{"GL_EXT_polygon_offset", &glext_EXT_polygon_offset, gleIntLoad_EXT_polygon_offset},
	{"GL_EXT_provoking_vertex", &glext_EXT_provoking_vertex, gleIntLoad_EXT_provoking_vertex},
	{"GL_EXT_rescale_normal", &glext_EXT_rescale_normal, NULL},
	{"GL_EXT_secondary_color", &glext_EXT_secondary_color, gleIntLoad_EXT_secondary_color},
	{"GL_EXT_separate_shader_objects", &glext_EXT_separate_shader_objects, gleIntLoad_EXT_separate_shader_objects},
	{"GL_EXT_separate_specular_color", &glext_EXT_separate_specular_color, NULL},
	{"GL_EXT_shader_image_load_store", &glext_EXT_shader_image_load_store, gleIntLoad_EXT_shader_image_load_store},
	{"GL_EXT_shadow_funcs", &glext_EXT_shadow_funcs, NULL},
	{"GL_EXT_shared_texture_palette", &glext_EXT_shared_texture_palette, NULL},
	{"GL_EXT_stencil_clear_tag", &glext_EXT_stencil_clear_tag, gleIntLoad_EXT_stencil_clear_tag},
	{"GL_EXT_stencil_two_side", &glext_EXT_stencil_two_side, gleIntLoad_EXT_stencil_two_side},
	{"GL_EXT_stencil_wrap", &glext_EXT_stencil_wrap, NULL},
	{"GL_EXT_subtexture", &glext_EXT_subtexture, gleIntLoad_EXT_subtexture},
	{"GL_EXT_texture", &glext_EXT_texture, NULL},
	{"GL_EXT_texture3D", &glext_EXT_texture3D, gleIntLoad_EXT_texture3D},
	{"GL_EXT_texture_array", &glext_EXT_texture_array, NULL},
	{"GL_EXT_texture_buffer_object", &glext_EXT_texture_buffer_object, gleIntLoad_EXT_texture_buffer_object},
	{"GL_EXT_texture_compression_latc", &glext_EXT_texture_compression_latc, NULL},
	{"GL_EXT_texture_compression_rgtc", &glext_EXT_texture_compression_rgtc, NULL},
	{"GL_EXT_texture_compression_s3tc", &glext_EXT_texture_compression_s3tc, NULL},
	{"GL_EXT_texture_cube_map", &glext_EXT_texture_cube_map, NULL},
	{"GL_EXT_texture_env_add", &glext_EXT_texture_env_add, NULL},
	{"GL_EXT_texture_env_combine", &glext_EXT_texture_env_combine, NULL},
	{"GL_EXT_texture_env_dot3", &glext_EXT_texture_env_dot3, NULL},
	{"GL_EXT_texture_filter_anisotropic", &glext_EXT_texture_filter_anisotropic, NULL},
	{"GL_EXT_texture_integer", &glext_EXT_texture_integer, gleIntLoad_EXT_texture_integer},
	{"GL_EXT_texture_lod_bias", &glext_EXT_texture_lod_bias, NULL},
	{"GL_EXT_texture_mirror_clamp", &glext_EXT_texture_mirror_clamp, NULL},
	{"GL_EXT_texture_object", &glext_EXT_texture_object, gleIntLoad_EXT_texture_object},
	{"GL_EXT_texture_perturb_normal", &glext_EXT_texture_perturb_normal, gleIntLoad_EXT_texture_perturb_normal},
	{"GL_EXT_texture_sRGB", &glext_EXT_texture_sRGB, NULL},
	{"GL_EXT_texture_shared_exponent", &glext_EXT_texture_shared_exponent, NULL},
	{"GL_EXT_texture_snorm", &glext_EXT_texture_snorm, NULL},
	{"GL_EXT_texture_swizzle", &glext_EXT_texture_swizzle, NULL},
	{"GL_EXT_timer_query", &glext_EXT_timer_query, gleIntLoad_EXT_timer_query},
	{"GL_EXT_transform_feedback", &glext_EXT_transform_feedback, gleIntLoad_EXT_transform_feedback},
	{"GL_EXT_vertex_array", &glext_EXT_vertex_array, gleIntLoad_EXT_vertex_array},
	{"GL_EXT_vertex_array_bgra", &glext_EXT_vertex_array_bgra, NULL},
	{"GL_EXT_vertex_attrib_64bit", &glext_EXT_vertex_attrib_64bit, gleIntLoad_EXT_vertex_attrib_64bit},
	{"GL_EXT_vertex_shader", &glext_EXT_vertex_shader, gleIntLoad_EXT_vertex_shader},
	{"GL_EXT_vertex_weighting", &glext_EXT_vertex_weighting, gleIntLoad_EXT_vertex_weighting},
	{"GL_FfdMaskSGIX", &glext_FfdMaskSGIX, NULL},
	{"GL_GREMEDY_frame_terminator", &glext_GREMEDY_frame_terminator, gleIntLoad_GREMEDY_frame_terminator},
	{"GL_GREMEDY_string_marker", &glext_GREMEDY_string_marker, gleIntLoad_GREMEDY_string_marker},
	{"GL_HP_convolution_border_modes", &glext_HP_convolution_border_modes, NULL},
	{"GL_HP_image_transform", &glext_HP_image_transform, gleIntLoad_HP_image_transform},
	{"GL_HP_occlusion_test", &glext_HP_occlusion_test, NULL},
	{"GL_HP_texture_lighting", &glext_HP_texture_lighting, NULL},
	{"GL_IBM_cull_vertex", &glext_IBM_cull_vertex, NULL},
	{"GL_IBM_multimode_draw_arrays", &glext_IBM_multimode_draw_arrays, gleIntLoad_IBM_multimode_draw_arrays},
	{"GL_IBM_rasterpos_clip", &glext_IBM_rasterpos_clip, NULL},
	{"GL_IBM_texture_mirrored_repeat", &glext_IBM_texture_mirrored_repeat, NULL},
	{"GL_IBM_vertex_array_lists", &glext_IBM_vertex_array_lists, gleIntLoad_IBM_vertex_array_lists},
	{"GL_INGR_color_clamp", &glext_INGR_color_clamp, NULL},
	{"GL_INGR_interlace_read", &glext_INGR_interlace_read, NULL},
	{"GL_INGR_palette_buffer", &glext_INGR_palette_buffer, NULL},
	{"GL_INTEL_parallel_arrays", &glext_INTEL_parallel_arrays, gleIntLoad_INTEL_parallel_arrays},
	{"GL_INTEL_texture_scissor", &glext_INTEL_texture_scissor, NULL},
	{"GL_MESAX_texture_stack", &glext_MESAX_texture_stack, NULL},
	{"GL_MESA_pack_invert", &glext_MESA_pack_invert, NULL},
	{"GL_MESA_resize_buffers", &glext_MESA_resize_buffers, gleIntLoad_MESA_resize_buffers},
	{"GL_MESA_window_pos", &glext_MESA_window_pos, gleIntLoad_MESA_window_pos},
	{"GL_MESA_ycbcr_texture", &glext_MESA_ycbcr_texture, NULL},
	{"GL_NV_blend_square", &glext_NV_blend_square, NULL},
	{"GL_NV_conditional_render", &glext_NV_conditional_render, gleIntLoad_NV_conditional_render},
	{"GL_NV_copy_depth_to_color", &glext_NV_copy_depth_to_color, NULL},
	{"GL_NV_copy_image", &glext_NV_copy_image, gleIntLoad_NV_copy_image},
	{"GL_NV_depth_buffer_float", &glext_NV_depth_buffer_float, gleIntLoad_NV_depth_buffer_float},
	{"GL_NV_depth_clamp", &glext_NV_depth_clamp, NULL},
	{"GL_NV_evaluators", &glext_NV_evaluators, gleIntLoad_NV_evaluators},
	{"GL_NV_explicit_multisample", &glext_NV_explicit_multisample, gleIntLoad_NV_explicit_multisample},
	{"GL_NV_fence", &glext_NV_fence, gleIntLoad_NV_fence},
	{"GL_NV_float_buffer", &glext_NV_float_buffer, NULL},
	{"GL_NV_fog_distance", &glext_NV_fog_distance, NULL},
	{"GL_NV_fragment_program", &glext_NV_fragment_program, gleIntLoad_NV_fragment_program},
	{"GL_NV_fragment_program2", &glext_NV_fragment_program2, NULL},
	{"GL_NV_fragment_program4", &glext_NV_fragment_program4, NULL},
	{"GL_NV_fragment_program_option", &glext_NV_fragment_program_option, NULL},
	{"GL_NV_framebuffer_multisample_coverage", &glext_NV_framebuffer_multisample_coverage, gleIntLoad_NV_framebuffer_multisample_coverage},
	{"GL_NV_geometry_program4", &glext_NV_geometry_program4, gleIntLoad_NV_geometry_program4},
	{"GL_NV_geometry_shader4", &glext_NV_geometry_shader4, NULL},
	{"GL_NV_gpu_program4", &glext_NV_gpu_program4, gleIntLoad_NV_gpu_program4},
	{"GL_NV_gpu_program5", &glext_NV_gpu_program5, gleIntLoad_NV_gpu_program5},
	{"GL_NV_gpu_shader5", &glext_NV_gpu_shader5, gleIntLoad_NV_gpu_shader5},
	{"GL_NV_half_float", &glext_NV_half_float, gleIntLoad_NV_half_float},
	{"GL_NV_light_max_exponent", &glext_NV_light_max_exponent, NULL},
	{"GL_NV_multisample_coverage", &glext_NV_multisample_coverage, NULL},
	{"GL_NV_multisample_filter_hint", &glext_NV_multisample_filter_hint, NULL},
	{"GL_NV_occlusion_query", &glext_NV_occlusion_query, gleIntLoad_NV_occlusion_query},
	{"GL_NV_packed_depth_stencil", &glext_NV_packed_depth_stencil, NULL},
	{"GL_NV_parameter_buffer_object", &glext_NV_parameter_buffer_object, gleIntLoad_NV_parameter_buffer_object},
	{"GL_NV_parameter_buffer_object2", &glext_NV_parameter_buffer_object2, NULL},
	{"GL_NV_pixel_data_range", &glext_NV_pixel_data_range, gleIntLoad_NV_pixel_data_range},
	{"GL_NV_point_sprite", &glext_NV_point_sprite, gleIntLoad_NV_point_sprite},
	{"GL_NV_present_video", &glext_NV_present_video, gleIntLoad_NV_present_video},
	{"GL_NV_primitive_restart", &glext_NV_primitive_restart, gleIntLoad_NV_primitive_restart},
	{"GL_NV_register_combiners", &glext_NV_register_combiners, gleIntLoad_NV_register_combiners},
	{"GL_NV_register_combiners2", &glext_NV_register_combiners2, gleIntLoad_NV_register_combiners2},
	{"GL_NV_shader_buffer_load", &glext_NV_shader_buffer_load, gleIntLoad_NV_shader_buffer_load},
	{"GL_NV_shader_buffer_store", &glext_NV_shader_buffer_store, NULL},
	{"GL_NV_tessellation_program5", &glext_NV_tessellation_program5, NULL},
	{"GL_NV_texgen_emboss", &glext_NV_texgen_emboss, NULL},
	{"GL_NV_texgen_reflection", &glext_NV_texgen_reflection, NULL},
	{"GL_NV_texture_barrier", &glext_NV_texture_barrier, gleIntLoad_NV_texture_barrier},
	{"GL_NV_texture_compression_vtc", &glext_NV_texture_compression_vtc, NULL},
	{"GL_NV_texture_env_combine4", &glext_NV_texture_env_combine4, NULL},
	{"GL_NV_texture_expand_normal", &glext_NV_texture_expand_normal, NULL},
	{"GL_NV_texture_rectangle", &glext_NV_texture_rectangle, NULL},
	{"GL_NV_texture_shader", &glext_NV_texture_shader, NULL},
	{"GL_NV_texture_shader2", &glext_NV_texture_shader2, NULL},
	{"GL_NV_texture_shader3", &glext_NV_texture_shader3, NULL},
	{"GL_NV_transform_feedback", &glext_NV_transform_feedback, gleIntLoad_NV_transform_feedback},
	{"GL_NV_transform_feedback2", &glext_NV_transform_feedback2, gleIntLoad_NV_transform_feedback2},
	{"GL_NV_vdpau_interop", &glext_NV_vdpau_interop, gleIntLoad_NV_vdpau_interop},
	{"GL_NV_vertex_array_range", &glext_NV_vertex_array_range, gleIntLoad_NV_vertex_array_range},
	{"GL_NV_vertex_array_range2", &glext_NV_vertex_array_range2, NULL},
	{"GL_NV_vertex_attrib_integer_64bit", &glext_NV_vertex_attrib_integer_64bit, gleIntLoad_NV_vertex_attrib_integer_64bit},
	{"GL_NV_vertex_buffer_unified_memory", &glext_NV_vertex_buffer_unified_memory, gleIntLoad_NV_vertex_buffer_unified_memory},
	{"GL_NV_vertex_program", &glext_NV_vertex_program, gleIntLoad_NV_vertex_program},
	{"GL_NV_vertex_program1_1", &glext_NV_vertex_program1_1, NULL},
	{"GL_NV_vertex_program2", &glext_NV_vertex_program2, NULL},
	{"GL_NV_vertex_program2_option", &glext_NV_vertex_program2_option, NULL},
	{"GL_NV_vertex_program3", &glext_NV_vertex_program3, NULL},
	{"GL_NV_vertex_program4", &glext_NV_vertex_program4, gleIntLoad_NV_vertex_program4},
	{"GL_NV_video_capture", &glext_NV_video_capture, gleIntLoad_NV_video_capture},
	{"GL_OES_read_format", &glext_OES_read_format, NULL},
	{"GL_OML_interlace", &glext_OML_interlace, NULL},
	{"GL_OML_resample", &glext_OML_resample, NULL},
	{"GL_OML_subsample", &glext_OML_subsample, NULL},
	{"GL_PGI_misc_hints", &glext_PGI_misc_hints, gleIntLoad_PGI_misc_hints},
	{"GL_PGI_vertex_hints", &glext_PGI_vertex_hints, NULL},
	{"GL_REND_screen_coordinates", &glext_REND_screen_coordinates, NULL},
	{"GL_S3_s3tc", &glext_S3_s3tc, NULL},
	{"GL_SGIS_detail_texture", &glext_SGIS_detail_texture, gleIntLoad_SGIS_detail_texture},
	{"GL_SGIS_fog_function", &glext_SGIS_fog_function, gleIntLoad_SGIS_fog_function},
	{"GL_SGIS_generate_mipmap", &glext_SGIS_generate_mipmap, NULL},
	{"GL_SGIS_multisample", &glext_SGIS_multisample, gleIntLoad_SGIS_multisample},
	{"GL_SGIS_pixel_texture", &glext_SGIS_pixel_texture, gleIntLoad_SGIS_pixel_texture},
	{"GL_SGIS_point_line_texgen", &glext_SGIS_point_line_texgen, NULL},
	{"GL_SGIS_point_parameters", &glext_SGIS_point_parameters, gleIntLoad_SGIS_point_parameters},
	{"GL_SGIS_sharpen_texture", &glext_SGIS_sharpen_texture, gleIntLoad_SGIS_sharpen_texture},
	{"GL_SGIS_texture4D", &glext_SGIS_texture4D, gleIntLoad_SGIS_texture4D},
	{"GL_SGIS_texture_border_clamp", &glext_SGIS_texture_border_clamp, NULL},
	{"GL_SGIS_texture_color_mask", &glext_SGIS_texture_color_mask, gleIntLoad_SGIS_texture_color_mask},
	{"GL_SGIS_texture_edge_clamp", &glext_SGIS_texture_edge_clamp, NULL},
	{"GL_SGIS_texture_filter4", &glext_SGIS_texture_filter4, gleIntLoad_SGIS_texture_filter4},
	{"GL_SGIS_texture_lod", &glext_SGIS_texture_lod, NULL},
	{"GL_SGIS_texture_select", &glext_SGIS_texture_select, NULL},
	{"GL_SGIX_async", &glext_SGIX_async, gleIntLoad_SGIX_async},
	{"GL_SGIX_async_histogram", &glext_SGIX_async_histogram, NULL},
	{"GL_SGIX_async_pixel", &glext_SGIX_async_pixel, NULL},
	{"GL_SGIX_blend_alpha_minmax", &glext_SGIX_blend_alpha_minmax, NULL},
	{"GL_SGIX_calligraphic_fragment", &glext_SGIX_calligraphic_fragment, NULL},
	{"GL_SGIX_clipmap", &glext_SGIX_clipmap, NULL},
	{"GL_SGIX_convolution_accuracy", &glext_SGIX_convolution_accuracy, NULL},
	{"GL_SGIX_depth_texture", &glext_SGIX_depth_texture, NULL},
	{"GL_SGIX_flush_raster", &glext_SGIX_flush_raster, gleIntLoad_SGIX_flush_raster},
	{"GL_SGIX_fog_offset", &glext_SGIX_fog_offset, NULL},
	{"GL_SGIX_fog_scale", &glext_SGIX_fog_scale, NULL},
	{"GL_SGIX_fragment_lighting", &glext_SGIX_fragment_lighting, gleIntLoad_SGIX_fragment_lighting},
	{"GL_SGIX_framezoom", &glext_SGIX_framezoom, gleIntLoad_SGIX_framezoom},
	{"GL_SGIX_impact_pixel_texture", &glext_SGIX_impact_pixel_texture, NULL},
	{"GL_SGIX_instruments", &glext_SGIX_instruments, gleIntLoad_SGIX_instruments},
	{"GL_SGIX_interlace", &glext_SGIX_interlace, NULL},
	{"GL_SGIX_ir_instrument1", &glext_SGIX_ir_instrument1, NULL},
	{"GL_SGIX_list_priority", &glext_SGIX_list_priority, gleIntLoad_SGIX_list_priority},
	{"GL_SGIX_pixel_texture", &glext_SGIX_pixel_texture, gleIntLoad_SGIX_pixel_texture},
	{"GL_SGIX_pixel_tiles", &glext_SGIX_pixel_tiles, NULL},
	{"GL_SGIX_polynomial_ffd", &glext_SGIX_polynomial_ffd, gleIntLoad_SGIX_polynomial_ffd},
	{"GL_SGIX_reference_plane", &glext_SGIX_reference_plane, gleIntLoad_SGIX_reference_plane},
	{"GL_SGIX_resample", &glext_SGIX_resample, NULL},
	{"GL_SGIX_scalebias_hint", &glext_SGIX_scalebias_hint, NULL},
	{"GL_SGIX_shadow", &glext_SGIX_shadow, NULL},
	{"GL_SGIX_shadow_ambient", &glext_SGIX_shadow_ambient, NULL},
	{"GL_SGIX_sprite", &glext_SGIX_sprite, gleIntLoad_SGIX_sprite},
	{"GL_SGIX_subsample", &glext_SGIX_subsample, NULL},
	{"GL_SGIX_tag_sample_buffer", &glext_SGIX_tag_sample_buffer, gleIntLoad_SGIX_tag_sample_buffer},
	{"GL_SGIX_texture_add_env", &glext_SGIX_texture_add_env, NULL},
	{"GL_SGIX_texture_coordinate_clamp", &glext_SGIX_texture_coordinate_clamp, NULL},
	{"GL_SGIX_texture_lod_bias", &glext_SGIX_texture_lod_bias, NULL},
	{"GL_SGIX_texture_multi_buffer", &glext_SGIX_texture_multi_buffer, NULL},
	{"GL_SGIX_texture_scale_bias", &glext_SGIX_texture_scale_bias, NULL},
	{"GL_SGIX_vertex_preclip", &glext_SGIX_vertex_preclip, NULL},
	{"GL_SGIX_ycrcb", &glext_SGIX_ycrcb, NULL},
	{"GL_SGIX_ycrcb_subsample", &glext_SGIX_ycrcb_subsample, NULL},
	{"GL_SGIX_ycrcba", &glext_SGIX_ycrcba, NULL},
	{"GL_SGI_color_matrix", &glext_SGI_color_matrix, NULL},
	{"GL_SGI_color_table", &glext_SGI_color_table, gleIntLoad_SGI_color_table},
	{"GL_SGI_depth_pass_instrument", &glext_SGI_depth_pass_instrument, NULL},
	{"GL_SGI_texture_color_table", &glext_SGI_texture_color_table, NULL},
	{"GL_SUNX_constant_data", &glext_SUNX_constant_data, gleIntLoad_SUNX_constant_data},
	{"GL_SUN_convolution_border_modes", &glext_SUN_convolution_border_modes, NULL},
	{"GL_SUN_global_alpha", &glext_SUN_global_alpha, gleIntLoad_SUN_global_alpha},
	{"GL_SUN_mesh_array", &glext_SUN_mesh_array, gleIntLoad_SUN_mesh_array},
	{"GL_SUN_slice_accum", &glext_SUN_slice_accum, NULL},
	{"GL_SUN_triangle_list", &glext_SUN_triangle_list, gleIntLoad_SUN_triangle_list},
	{"GL_SUN_vertex", &glext_SUN_vertex, gleIntLoad_SUN_vertex},
	{"GL_WIN_phong_shading", &glext_WIN_phong_shading, NULL},
	{"GL_WIN_specular_fog", &glext_WIN_specular_fog, NULL},
};

int gleIntExtensionMapSize = 386;

typedef void (GLE_FUNCPTR * PFNGLCULLFACEPROC)(GLenum mode);
PFNGLCULLFACEPROC __gleCullFace;
typedef void (GLE_FUNCPTR * PFNGLFRONTFACEPROC)(GLenum mode);
PFNGLFRONTFACEPROC __gleFrontFace;
typedef void (GLE_FUNCPTR * PFNGLHINTPROC)(GLenum target, GLenum mode);
PFNGLHINTPROC __gleHint;
typedef void (GLE_FUNCPTR * PFNGLLINEWIDTHPROC)(GLfloat width);
PFNGLLINEWIDTHPROC __gleLineWidth;
typedef void (GLE_FUNCPTR * PFNGLPOINTSIZEPROC)(GLfloat size);
PFNGLPOINTSIZEPROC __glePointSize;
typedef void (GLE_FUNCPTR * PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
PFNGLPOLYGONMODEPROC __glePolygonMode;
typedef void (GLE_FUNCPTR * PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLSCISSORPROC __gleScissor;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
PFNGLTEXPARAMETERFPROC __gleTexParameterf;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
PFNGLTEXPARAMETERFVPROC __gleTexParameterfv;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
PFNGLTEXPARAMETERIPROC __gleTexParameteri;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
PFNGLTEXPARAMETERIVPROC __gleTexParameteriv;
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXIMAGE1DPROC __gleTexImage1D;
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXIMAGE2DPROC __gleTexImage2D;
typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERPROC)(GLenum mode);
PFNGLDRAWBUFFERPROC __gleDrawBuffer;
typedef void (GLE_FUNCPTR * PFNGLCLEARPROC)(GLbitfield mask);
PFNGLCLEARPROC __gleClear;
typedef void (GLE_FUNCPTR * PFNGLCLEARCOLORPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
PFNGLCLEARCOLORPROC __gleClearColor;
typedef void (GLE_FUNCPTR * PFNGLCLEARSTENCILPROC)(GLint s);
PFNGLCLEARSTENCILPROC __gleClearStencil;
typedef void (GLE_FUNCPTR * PFNGLCLEARDEPTHPROC)(GLclampd depth);
PFNGLCLEARDEPTHPROC __gleClearDepth;
typedef void (GLE_FUNCPTR * PFNGLSTENCILMASKPROC)(GLuint mask);
PFNGLSTENCILMASKPROC __gleStencilMask;
typedef void (GLE_FUNCPTR * PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
PFNGLCOLORMASKPROC __gleColorMask;
typedef void (GLE_FUNCPTR * PFNGLDEPTHMASKPROC)(GLboolean flag);
PFNGLDEPTHMASKPROC __gleDepthMask;
typedef void (GLE_FUNCPTR * PFNGLDISABLEPROC)(GLenum cap);
PFNGLDISABLEPROC __gleDisable;
typedef void (GLE_FUNCPTR * PFNGLENABLEPROC)(GLenum cap);
PFNGLENABLEPROC __gleEnable;
typedef void (GLE_FUNCPTR * PFNGLFINISHPROC)();
PFNGLFINISHPROC __gleFinish;
typedef void (GLE_FUNCPTR * PFNGLFLUSHPROC)();
PFNGLFLUSHPROC __gleFlush;
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
PFNGLBLENDFUNCPROC __gleBlendFunc;
typedef void (GLE_FUNCPTR * PFNGLLOGICOPPROC)(GLenum opcode);
PFNGLLOGICOPPROC __gleLogicOp;
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
PFNGLSTENCILFUNCPROC __gleStencilFunc;
typedef void (GLE_FUNCPTR * PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
PFNGLSTENCILOPPROC __gleStencilOp;
typedef void (GLE_FUNCPTR * PFNGLDEPTHFUNCPROC)(GLenum func);
PFNGLDEPTHFUNCPROC __gleDepthFunc;
typedef void (GLE_FUNCPTR * PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
PFNGLPIXELSTOREFPROC __glePixelStoref;
typedef void (GLE_FUNCPTR * PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
PFNGLPIXELSTOREIPROC __glePixelStorei;
typedef void (GLE_FUNCPTR * PFNGLREADBUFFERPROC)(GLenum mode);
PFNGLREADBUFFERPROC __gleReadBuffer;
typedef void (GLE_FUNCPTR * PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
PFNGLREADPIXELSPROC __gleReadPixels;
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean *params);
PFNGLGETBOOLEANVPROC __gleGetBooleanv;
typedef void (GLE_FUNCPTR * PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble *params);
PFNGLGETDOUBLEVPROC __gleGetDoublev;
typedef GLenum (GLE_FUNCPTR * PFNGLGETERRORPROC)();
PFNGLGETERRORPROC __gleGetError;
typedef void (GLE_FUNCPTR * PFNGLGETFLOATVPROC)(GLenum pname, GLfloat *params);
PFNGLGETFLOATVPROC __gleGetFloatv;
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERVPROC)(GLenum pname, GLint *params);
PFNGLGETINTEGERVPROC __gleGetIntegerv;
typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGPROC)(GLenum name);
PFNGLGETSTRINGPROC __gleGetString;
typedef void (GLE_FUNCPTR * PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
PFNGLGETTEXIMAGEPROC __gleGetTexImage;
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETTEXPARAMETERFVPROC __gleGetTexParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETTEXPARAMETERIVPROC __gleGetTexParameteriv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat *params);
PFNGLGETTEXLEVELPARAMETERFVPROC __gleGetTexLevelParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint *params);
PFNGLGETTEXLEVELPARAMETERIVPROC __gleGetTexLevelParameteriv;
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDPROC)(GLenum cap);
PFNGLISENABLEDPROC __gleIsEnabled;
typedef void (GLE_FUNCPTR * PFNGLDEPTHRANGEPROC)(GLclampd near, GLclampd far);
PFNGLDEPTHRANGEPROC __gleDepthRange;
typedef void (GLE_FUNCPTR * PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLVIEWPORTPROC __gleViewport;
typedef void (GLE_FUNCPTR * PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
PFNGLNEWLISTPROC __gleNewList;
typedef void (GLE_FUNCPTR * PFNGLENDLISTPROC)();
PFNGLENDLISTPROC __gleEndList;
typedef void (GLE_FUNCPTR * PFNGLCALLLISTPROC)(GLuint list);
PFNGLCALLLISTPROC __gleCallList;
typedef void (GLE_FUNCPTR * PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const GLvoid *lists);
PFNGLCALLLISTSPROC __gleCallLists;
typedef void (GLE_FUNCPTR * PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
PFNGLDELETELISTSPROC __gleDeleteLists;
typedef GLuint (GLE_FUNCPTR * PFNGLGENLISTSPROC)(GLsizei range);
PFNGLGENLISTSPROC __gleGenLists;
typedef void (GLE_FUNCPTR * PFNGLLISTBASEPROC)(GLuint base);
PFNGLLISTBASEPROC __gleListBase;
typedef void (GLE_FUNCPTR * PFNGLBEGINPROC)(GLenum mode);
PFNGLBEGINPROC __gleBegin;
typedef void (GLE_FUNCPTR * PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
PFNGLBITMAPPROC __gleBitmap;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
PFNGLCOLOR3BPROC __gleColor3b;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3BVPROC)(const GLbyte *v);
PFNGLCOLOR3BVPROC __gleColor3bv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
PFNGLCOLOR3DPROC __gleColor3d;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3DVPROC)(const GLdouble *v);
PFNGLCOLOR3DVPROC __gleColor3dv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
PFNGLCOLOR3FPROC __gleColor3f;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3FVPROC)(const GLfloat *v);
PFNGLCOLOR3FVPROC __gleColor3fv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
PFNGLCOLOR3IPROC __gleColor3i;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3IVPROC)(const GLint *v);
PFNGLCOLOR3IVPROC __gleColor3iv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
PFNGLCOLOR3SPROC __gleColor3s;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3SVPROC)(const GLshort *v);
PFNGLCOLOR3SVPROC __gleColor3sv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
PFNGLCOLOR3UBPROC __gleColor3ub;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UBVPROC)(const GLubyte *v);
PFNGLCOLOR3UBVPROC __gleColor3ubv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
PFNGLCOLOR3UIPROC __gleColor3ui;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3UIVPROC)(const GLuint *v);
PFNGLCOLOR3UIVPROC __gleColor3uiv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
PFNGLCOLOR3USPROC __gleColor3us;
typedef void (GLE_FUNCPTR * PFNGLCOLOR3USVPROC)(const GLushort *v);
PFNGLCOLOR3USVPROC __gleColor3usv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
PFNGLCOLOR4BPROC __gleColor4b;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4BVPROC)(const GLbyte *v);
PFNGLCOLOR4BVPROC __gleColor4bv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
PFNGLCOLOR4DPROC __gleColor4d;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4DVPROC)(const GLdouble *v);
PFNGLCOLOR4DVPROC __gleColor4dv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCOLOR4FPROC __gleColor4f;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4FVPROC)(const GLfloat *v);
PFNGLCOLOR4FVPROC __gleColor4fv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
PFNGLCOLOR4IPROC __gleColor4i;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4IVPROC)(const GLint *v);
PFNGLCOLOR4IVPROC __gleColor4iv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
PFNGLCOLOR4SPROC __gleColor4s;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4SVPROC)(const GLshort *v);
PFNGLCOLOR4SVPROC __gleColor4sv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
PFNGLCOLOR4UBPROC __gleColor4ub;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UBVPROC)(const GLubyte *v);
PFNGLCOLOR4UBVPROC __gleColor4ubv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
PFNGLCOLOR4UIPROC __gleColor4ui;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4UIVPROC)(const GLuint *v);
PFNGLCOLOR4UIVPROC __gleColor4uiv;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
PFNGLCOLOR4USPROC __gleColor4us;
typedef void (GLE_FUNCPTR * PFNGLCOLOR4USVPROC)(const GLushort *v);
PFNGLCOLOR4USVPROC __gleColor4usv;
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPROC)(GLboolean flag);
PFNGLEDGEFLAGPROC __gleEdgeFlag;
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGVPROC)(const GLboolean *flag);
PFNGLEDGEFLAGVPROC __gleEdgeFlagv;
typedef void (GLE_FUNCPTR * PFNGLENDPROC)();
PFNGLENDPROC __gleEnd;
typedef void (GLE_FUNCPTR * PFNGLINDEXDPROC)(GLdouble c);
PFNGLINDEXDPROC __gleIndexd;
typedef void (GLE_FUNCPTR * PFNGLINDEXDVPROC)(const GLdouble *c);
PFNGLINDEXDVPROC __gleIndexdv;
typedef void (GLE_FUNCPTR * PFNGLINDEXFPROC)(GLfloat c);
PFNGLINDEXFPROC __gleIndexf;
typedef void (GLE_FUNCPTR * PFNGLINDEXFVPROC)(const GLfloat *c);
PFNGLINDEXFVPROC __gleIndexfv;
typedef void (GLE_FUNCPTR * PFNGLINDEXIPROC)(GLint c);
PFNGLINDEXIPROC __gleIndexi;
typedef void (GLE_FUNCPTR * PFNGLINDEXIVPROC)(const GLint *c);
PFNGLINDEXIVPROC __gleIndexiv;
typedef void (GLE_FUNCPTR * PFNGLINDEXSPROC)(GLshort c);
PFNGLINDEXSPROC __gleIndexs;
typedef void (GLE_FUNCPTR * PFNGLINDEXSVPROC)(const GLshort *c);
PFNGLINDEXSVPROC __gleIndexsv;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
PFNGLNORMAL3BPROC __gleNormal3b;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3BVPROC)(const GLbyte *v);
PFNGLNORMAL3BVPROC __gleNormal3bv;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
PFNGLNORMAL3DPROC __gleNormal3d;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3DVPROC)(const GLdouble *v);
PFNGLNORMAL3DVPROC __gleNormal3dv;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
PFNGLNORMAL3FPROC __gleNormal3f;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3FVPROC)(const GLfloat *v);
PFNGLNORMAL3FVPROC __gleNormal3fv;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
PFNGLNORMAL3IPROC __gleNormal3i;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3IVPROC)(const GLint *v);
PFNGLNORMAL3IVPROC __gleNormal3iv;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
PFNGLNORMAL3SPROC __gleNormal3s;
typedef void (GLE_FUNCPTR * PFNGLNORMAL3SVPROC)(const GLshort *v);
PFNGLNORMAL3SVPROC __gleNormal3sv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
PFNGLRASTERPOS2DPROC __gleRasterPos2d;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2DVPROC)(const GLdouble *v);
PFNGLRASTERPOS2DVPROC __gleRasterPos2dv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
PFNGLRASTERPOS2FPROC __gleRasterPos2f;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2FVPROC)(const GLfloat *v);
PFNGLRASTERPOS2FVPROC __gleRasterPos2fv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
PFNGLRASTERPOS2IPROC __gleRasterPos2i;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2IVPROC)(const GLint *v);
PFNGLRASTERPOS2IVPROC __gleRasterPos2iv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
PFNGLRASTERPOS2SPROC __gleRasterPos2s;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS2SVPROC)(const GLshort *v);
PFNGLRASTERPOS2SVPROC __gleRasterPos2sv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLRASTERPOS3DPROC __gleRasterPos3d;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3DVPROC)(const GLdouble *v);
PFNGLRASTERPOS3DVPROC __gleRasterPos3dv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLRASTERPOS3FPROC __gleRasterPos3f;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3FVPROC)(const GLfloat *v);
PFNGLRASTERPOS3FVPROC __gleRasterPos3fv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
PFNGLRASTERPOS3IPROC __gleRasterPos3i;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3IVPROC)(const GLint *v);
PFNGLRASTERPOS3IVPROC __gleRasterPos3iv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLRASTERPOS3SPROC __gleRasterPos3s;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS3SVPROC)(const GLshort *v);
PFNGLRASTERPOS3SVPROC __gleRasterPos3sv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLRASTERPOS4DPROC __gleRasterPos4d;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4DVPROC)(const GLdouble *v);
PFNGLRASTERPOS4DVPROC __gleRasterPos4dv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLRASTERPOS4FPROC __gleRasterPos4f;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4FVPROC)(const GLfloat *v);
PFNGLRASTERPOS4FVPROC __gleRasterPos4fv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
PFNGLRASTERPOS4IPROC __gleRasterPos4i;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4IVPROC)(const GLint *v);
PFNGLRASTERPOS4IVPROC __gleRasterPos4iv;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLRASTERPOS4SPROC __gleRasterPos4s;
typedef void (GLE_FUNCPTR * PFNGLRASTERPOS4SVPROC)(const GLshort *v);
PFNGLRASTERPOS4SVPROC __gleRasterPos4sv;
typedef void (GLE_FUNCPTR * PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
PFNGLRECTDPROC __gleRectd;
typedef void (GLE_FUNCPTR * PFNGLRECTDVPROC)(const GLdouble *v1, const GLdouble *v2);
PFNGLRECTDVPROC __gleRectdv;
typedef void (GLE_FUNCPTR * PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
PFNGLRECTFPROC __gleRectf;
typedef void (GLE_FUNCPTR * PFNGLRECTFVPROC)(const GLfloat *v1, const GLfloat *v2);
PFNGLRECTFVPROC __gleRectfv;
typedef void (GLE_FUNCPTR * PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
PFNGLRECTIPROC __gleRecti;
typedef void (GLE_FUNCPTR * PFNGLRECTIVPROC)(const GLint *v1, const GLint *v2);
PFNGLRECTIVPROC __gleRectiv;
typedef void (GLE_FUNCPTR * PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
PFNGLRECTSPROC __gleRects;
typedef void (GLE_FUNCPTR * PFNGLRECTSVPROC)(const GLshort *v1, const GLshort *v2);
PFNGLRECTSVPROC __gleRectsv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1DPROC)(GLdouble s);
PFNGLTEXCOORD1DPROC __gleTexCoord1d;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1DVPROC)(const GLdouble *v);
PFNGLTEXCOORD1DVPROC __gleTexCoord1dv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1FPROC)(GLfloat s);
PFNGLTEXCOORD1FPROC __gleTexCoord1f;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1FVPROC)(const GLfloat *v);
PFNGLTEXCOORD1FVPROC __gleTexCoord1fv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1IPROC)(GLint s);
PFNGLTEXCOORD1IPROC __gleTexCoord1i;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1IVPROC)(const GLint *v);
PFNGLTEXCOORD1IVPROC __gleTexCoord1iv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1SPROC)(GLshort s);
PFNGLTEXCOORD1SPROC __gleTexCoord1s;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD1SVPROC)(const GLshort *v);
PFNGLTEXCOORD1SVPROC __gleTexCoord1sv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
PFNGLTEXCOORD2DPROC __gleTexCoord2d;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2DVPROC)(const GLdouble *v);
PFNGLTEXCOORD2DVPROC __gleTexCoord2dv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
PFNGLTEXCOORD2FPROC __gleTexCoord2f;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2FVPROC)(const GLfloat *v);
PFNGLTEXCOORD2FVPROC __gleTexCoord2fv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
PFNGLTEXCOORD2IPROC __gleTexCoord2i;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2IVPROC)(const GLint *v);
PFNGLTEXCOORD2IVPROC __gleTexCoord2iv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
PFNGLTEXCOORD2SPROC __gleTexCoord2s;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD2SVPROC)(const GLshort *v);
PFNGLTEXCOORD2SVPROC __gleTexCoord2sv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
PFNGLTEXCOORD3DPROC __gleTexCoord3d;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3DVPROC)(const GLdouble *v);
PFNGLTEXCOORD3DVPROC __gleTexCoord3dv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
PFNGLTEXCOORD3FPROC __gleTexCoord3f;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3FVPROC)(const GLfloat *v);
PFNGLTEXCOORD3FVPROC __gleTexCoord3fv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
PFNGLTEXCOORD3IPROC __gleTexCoord3i;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3IVPROC)(const GLint *v);
PFNGLTEXCOORD3IVPROC __gleTexCoord3iv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
PFNGLTEXCOORD3SPROC __gleTexCoord3s;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD3SVPROC)(const GLshort *v);
PFNGLTEXCOORD3SVPROC __gleTexCoord3sv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
PFNGLTEXCOORD4DPROC __gleTexCoord4d;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4DVPROC)(const GLdouble *v);
PFNGLTEXCOORD4DVPROC __gleTexCoord4dv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
PFNGLTEXCOORD4FPROC __gleTexCoord4f;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4FVPROC)(const GLfloat *v);
PFNGLTEXCOORD4FVPROC __gleTexCoord4fv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
PFNGLTEXCOORD4IPROC __gleTexCoord4i;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4IVPROC)(const GLint *v);
PFNGLTEXCOORD4IVPROC __gleTexCoord4iv;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
PFNGLTEXCOORD4SPROC __gleTexCoord4s;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORD4SVPROC)(const GLshort *v);
PFNGLTEXCOORD4SVPROC __gleTexCoord4sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
PFNGLVERTEX2DPROC __gleVertex2d;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2DVPROC)(const GLdouble *v);
PFNGLVERTEX2DVPROC __gleVertex2dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
PFNGLVERTEX2FPROC __gleVertex2f;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2FVPROC)(const GLfloat *v);
PFNGLVERTEX2FVPROC __gleVertex2fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2IPROC)(GLint x, GLint y);
PFNGLVERTEX2IPROC __gleVertex2i;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2IVPROC)(const GLint *v);
PFNGLVERTEX2IVPROC __gleVertex2iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
PFNGLVERTEX2SPROC __gleVertex2s;
typedef void (GLE_FUNCPTR * PFNGLVERTEX2SVPROC)(const GLshort *v);
PFNGLVERTEX2SVPROC __gleVertex2sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLVERTEX3DPROC __gleVertex3d;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3DVPROC)(const GLdouble *v);
PFNGLVERTEX3DVPROC __gleVertex3dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLVERTEX3FPROC __gleVertex3f;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3FVPROC)(const GLfloat *v);
PFNGLVERTEX3FVPROC __gleVertex3fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
PFNGLVERTEX3IPROC __gleVertex3i;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3IVPROC)(const GLint *v);
PFNGLVERTEX3IVPROC __gleVertex3iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLVERTEX3SPROC __gleVertex3s;
typedef void (GLE_FUNCPTR * PFNGLVERTEX3SVPROC)(const GLshort *v);
PFNGLVERTEX3SVPROC __gleVertex3sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLVERTEX4DPROC __gleVertex4d;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4DVPROC)(const GLdouble *v);
PFNGLVERTEX4DVPROC __gleVertex4dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLVERTEX4FPROC __gleVertex4f;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4FVPROC)(const GLfloat *v);
PFNGLVERTEX4FVPROC __gleVertex4fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
PFNGLVERTEX4IPROC __gleVertex4i;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4IVPROC)(const GLint *v);
PFNGLVERTEX4IVPROC __gleVertex4iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLVERTEX4SPROC __gleVertex4s;
typedef void (GLE_FUNCPTR * PFNGLVERTEX4SVPROC)(const GLshort *v);
PFNGLVERTEX4SVPROC __gleVertex4sv;
typedef void (GLE_FUNCPTR * PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble *equation);
PFNGLCLIPPLANEPROC __gleClipPlane;
typedef void (GLE_FUNCPTR * PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
PFNGLCOLORMATERIALPROC __gleColorMaterial;
typedef void (GLE_FUNCPTR * PFNGLFOGFPROC)(GLenum pname, GLfloat param);
PFNGLFOGFPROC __gleFogf;
typedef void (GLE_FUNCPTR * PFNGLFOGFVPROC)(GLenum pname, const GLfloat *params);
PFNGLFOGFVPROC __gleFogfv;
typedef void (GLE_FUNCPTR * PFNGLFOGIPROC)(GLenum pname, GLint param);
PFNGLFOGIPROC __gleFogi;
typedef void (GLE_FUNCPTR * PFNGLFOGIVPROC)(GLenum pname, const GLint *params);
PFNGLFOGIVPROC __gleFogiv;
typedef void (GLE_FUNCPTR * PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
PFNGLLIGHTFPROC __gleLightf;
typedef void (GLE_FUNCPTR * PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat *params);
PFNGLLIGHTFVPROC __gleLightfv;
typedef void (GLE_FUNCPTR * PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
PFNGLLIGHTIPROC __gleLighti;
typedef void (GLE_FUNCPTR * PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint *params);
PFNGLLIGHTIVPROC __gleLightiv;
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
PFNGLLIGHTMODELFPROC __gleLightModelf;
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat *params);
PFNGLLIGHTMODELFVPROC __gleLightModelfv;
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
PFNGLLIGHTMODELIPROC __gleLightModeli;
typedef void (GLE_FUNCPTR * PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint *params);
PFNGLLIGHTMODELIVPROC __gleLightModeliv;
typedef void (GLE_FUNCPTR * PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
PFNGLLINESTIPPLEPROC __gleLineStipple;
typedef void (GLE_FUNCPTR * PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
PFNGLMATERIALFPROC __gleMaterialf;
typedef void (GLE_FUNCPTR * PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat *params);
PFNGLMATERIALFVPROC __gleMaterialfv;
typedef void (GLE_FUNCPTR * PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
PFNGLMATERIALIPROC __gleMateriali;
typedef void (GLE_FUNCPTR * PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint *params);
PFNGLMATERIALIVPROC __gleMaterialiv;
typedef void (GLE_FUNCPTR * PFNGLPOLYGONSTIPPLEPROC)(const GLubyte *mask);
PFNGLPOLYGONSTIPPLEPROC __glePolygonStipple;
typedef void (GLE_FUNCPTR * PFNGLSHADEMODELPROC)(GLenum mode);
PFNGLSHADEMODELPROC __gleShadeModel;
typedef void (GLE_FUNCPTR * PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
PFNGLTEXENVFPROC __gleTexEnvf;
typedef void (GLE_FUNCPTR * PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
PFNGLTEXENVFVPROC __gleTexEnvfv;
typedef void (GLE_FUNCPTR * PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
PFNGLTEXENVIPROC __gleTexEnvi;
typedef void (GLE_FUNCPTR * PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint *params);
PFNGLTEXENVIVPROC __gleTexEnviv;
typedef void (GLE_FUNCPTR * PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
PFNGLTEXGENDPROC __gleTexGend;
typedef void (GLE_FUNCPTR * PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble *params);
PFNGLTEXGENDVPROC __gleTexGendv;
typedef void (GLE_FUNCPTR * PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
PFNGLTEXGENFPROC __gleTexGenf;
typedef void (GLE_FUNCPTR * PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat *params);
PFNGLTEXGENFVPROC __gleTexGenfv;
typedef void (GLE_FUNCPTR * PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
PFNGLTEXGENIPROC __gleTexGeni;
typedef void (GLE_FUNCPTR * PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint *params);
PFNGLTEXGENIVPROC __gleTexGeniv;
typedef void (GLE_FUNCPTR * PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat *buffer);
PFNGLFEEDBACKBUFFERPROC __gleFeedbackBuffer;
typedef void (GLE_FUNCPTR * PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint *buffer);
PFNGLSELECTBUFFERPROC __gleSelectBuffer;
typedef GLint (GLE_FUNCPTR * PFNGLRENDERMODEPROC)(GLenum mode);
PFNGLRENDERMODEPROC __gleRenderMode;
typedef void (GLE_FUNCPTR * PFNGLINITNAMESPROC)();
PFNGLINITNAMESPROC __gleInitNames;
typedef void (GLE_FUNCPTR * PFNGLLOADNAMEPROC)(GLuint name);
PFNGLLOADNAMEPROC __gleLoadName;
typedef void (GLE_FUNCPTR * PFNGLPASSTHROUGHPROC)(GLfloat token);
PFNGLPASSTHROUGHPROC __glePassThrough;
typedef void (GLE_FUNCPTR * PFNGLPOPNAMEPROC)();
PFNGLPOPNAMEPROC __glePopName;
typedef void (GLE_FUNCPTR * PFNGLPUSHNAMEPROC)(GLuint name);
PFNGLPUSHNAMEPROC __glePushName;
typedef void (GLE_FUNCPTR * PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARACCUMPROC __gleClearAccum;
typedef void (GLE_FUNCPTR * PFNGLCLEARINDEXPROC)(GLfloat c);
PFNGLCLEARINDEXPROC __gleClearIndex;
typedef void (GLE_FUNCPTR * PFNGLINDEXMASKPROC)(GLuint mask);
PFNGLINDEXMASKPROC __gleIndexMask;
typedef void (GLE_FUNCPTR * PFNGLACCUMPROC)(GLenum op, GLfloat value);
PFNGLACCUMPROC __gleAccum;
typedef void (GLE_FUNCPTR * PFNGLPOPATTRIBPROC)();
PFNGLPOPATTRIBPROC __glePopAttrib;
typedef void (GLE_FUNCPTR * PFNGLPUSHATTRIBPROC)(GLbitfield mask);
PFNGLPUSHATTRIBPROC __glePushAttrib;
typedef void (GLE_FUNCPTR * PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
PFNGLMAP1DPROC __gleMap1d;
typedef void (GLE_FUNCPTR * PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
PFNGLMAP1FPROC __gleMap1f;
typedef void (GLE_FUNCPTR * PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
PFNGLMAP2DPROC __gleMap2d;
typedef void (GLE_FUNCPTR * PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
PFNGLMAP2FPROC __gleMap2f;
typedef void (GLE_FUNCPTR * PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
PFNGLMAPGRID1DPROC __gleMapGrid1d;
typedef void (GLE_FUNCPTR * PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
PFNGLMAPGRID1FPROC __gleMapGrid1f;
typedef void (GLE_FUNCPTR * PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
PFNGLMAPGRID2DPROC __gleMapGrid2d;
typedef void (GLE_FUNCPTR * PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
PFNGLMAPGRID2FPROC __gleMapGrid2f;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1DPROC)(GLdouble u);
PFNGLEVALCOORD1DPROC __gleEvalCoord1d;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1DVPROC)(const GLdouble *u);
PFNGLEVALCOORD1DVPROC __gleEvalCoord1dv;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1FPROC)(GLfloat u);
PFNGLEVALCOORD1FPROC __gleEvalCoord1f;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD1FVPROC)(const GLfloat *u);
PFNGLEVALCOORD1FVPROC __gleEvalCoord1fv;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
PFNGLEVALCOORD2DPROC __gleEvalCoord2d;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2DVPROC)(const GLdouble *u);
PFNGLEVALCOORD2DVPROC __gleEvalCoord2dv;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
PFNGLEVALCOORD2FPROC __gleEvalCoord2f;
typedef void (GLE_FUNCPTR * PFNGLEVALCOORD2FVPROC)(const GLfloat *u);
PFNGLEVALCOORD2FVPROC __gleEvalCoord2fv;
typedef void (GLE_FUNCPTR * PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
PFNGLEVALMESH1PROC __gleEvalMesh1;
typedef void (GLE_FUNCPTR * PFNGLEVALPOINT1PROC)(GLint i);
PFNGLEVALPOINT1PROC __gleEvalPoint1;
typedef void (GLE_FUNCPTR * PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
PFNGLEVALMESH2PROC __gleEvalMesh2;
typedef void (GLE_FUNCPTR * PFNGLEVALPOINT2PROC)(GLint i, GLint j);
PFNGLEVALPOINT2PROC __gleEvalPoint2;
typedef void (GLE_FUNCPTR * PFNGLALPHAFUNCPROC)(GLenum func, GLclampf ref);
PFNGLALPHAFUNCPROC __gleAlphaFunc;
typedef void (GLE_FUNCPTR * PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
PFNGLPIXELZOOMPROC __glePixelZoom;
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
PFNGLPIXELTRANSFERFPROC __glePixelTransferf;
typedef void (GLE_FUNCPTR * PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
PFNGLPIXELTRANSFERIPROC __glePixelTransferi;
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPFVPROC)(GLenum map, GLint mapsize, const GLfloat *values);
PFNGLPIXELMAPFVPROC __glePixelMapfv;
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPUIVPROC)(GLenum map, GLint mapsize, const GLuint *values);
PFNGLPIXELMAPUIVPROC __glePixelMapuiv;
typedef void (GLE_FUNCPTR * PFNGLPIXELMAPUSVPROC)(GLenum map, GLint mapsize, const GLushort *values);
PFNGLPIXELMAPUSVPROC __glePixelMapusv;
typedef void (GLE_FUNCPTR * PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
PFNGLCOPYPIXELSPROC __gleCopyPixels;
typedef void (GLE_FUNCPTR * PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLDRAWPIXELSPROC __gleDrawPixels;
typedef void (GLE_FUNCPTR * PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble *equation);
PFNGLGETCLIPPLANEPROC __gleGetClipPlane;
typedef void (GLE_FUNCPTR * PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat *params);
PFNGLGETLIGHTFVPROC __gleGetLightfv;
typedef void (GLE_FUNCPTR * PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint *params);
PFNGLGETLIGHTIVPROC __gleGetLightiv;
typedef void (GLE_FUNCPTR * PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble *v);
PFNGLGETMAPDVPROC __gleGetMapdv;
typedef void (GLE_FUNCPTR * PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat *v);
PFNGLGETMAPFVPROC __gleGetMapfv;
typedef void (GLE_FUNCPTR * PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint *v);
PFNGLGETMAPIVPROC __gleGetMapiv;
typedef void (GLE_FUNCPTR * PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat *params);
PFNGLGETMATERIALFVPROC __gleGetMaterialfv;
typedef void (GLE_FUNCPTR * PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint *params);
PFNGLGETMATERIALIVPROC __gleGetMaterialiv;
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat *values);
PFNGLGETPIXELMAPFVPROC __gleGetPixelMapfv;
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint *values);
PFNGLGETPIXELMAPUIVPROC __gleGetPixelMapuiv;
typedef void (GLE_FUNCPTR * PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort *values);
PFNGLGETPIXELMAPUSVPROC __gleGetPixelMapusv;
typedef void (GLE_FUNCPTR * PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte *mask);
PFNGLGETPOLYGONSTIPPLEPROC __gleGetPolygonStipple;
typedef void (GLE_FUNCPTR * PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETTEXENVFVPROC __gleGetTexEnvfv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETTEXENVIVPROC __gleGetTexEnviv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble *params);
PFNGLGETTEXGENDVPROC __gleGetTexGendv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat *params);
PFNGLGETTEXGENFVPROC __gleGetTexGenfv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint *params);
PFNGLGETTEXGENIVPROC __gleGetTexGeniv;
typedef GLboolean (GLE_FUNCPTR * PFNGLISLISTPROC)(GLuint list);
PFNGLISLISTPROC __gleIsList;
typedef void (GLE_FUNCPTR * PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
PFNGLFRUSTUMPROC __gleFrustum;
typedef void (GLE_FUNCPTR * PFNGLLOADIDENTITYPROC)();
PFNGLLOADIDENTITYPROC __gleLoadIdentity;
typedef void (GLE_FUNCPTR * PFNGLLOADMATRIXFPROC)(const GLfloat *m);
PFNGLLOADMATRIXFPROC __gleLoadMatrixf;
typedef void (GLE_FUNCPTR * PFNGLLOADMATRIXDPROC)(const GLdouble *m);
PFNGLLOADMATRIXDPROC __gleLoadMatrixd;
typedef void (GLE_FUNCPTR * PFNGLMATRIXMODEPROC)(GLenum mode);
PFNGLMATRIXMODEPROC __gleMatrixMode;
typedef void (GLE_FUNCPTR * PFNGLMULTMATRIXFPROC)(const GLfloat *m);
PFNGLMULTMATRIXFPROC __gleMultMatrixf;
typedef void (GLE_FUNCPTR * PFNGLMULTMATRIXDPROC)(const GLdouble *m);
PFNGLMULTMATRIXDPROC __gleMultMatrixd;
typedef void (GLE_FUNCPTR * PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
PFNGLORTHOPROC __gleOrtho;
typedef void (GLE_FUNCPTR * PFNGLPOPMATRIXPROC)();
PFNGLPOPMATRIXPROC __glePopMatrix;
typedef void (GLE_FUNCPTR * PFNGLPUSHMATRIXPROC)();
PFNGLPUSHMATRIXPROC __glePushMatrix;
typedef void (GLE_FUNCPTR * PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
PFNGLROTATEDPROC __gleRotated;
typedef void (GLE_FUNCPTR * PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
PFNGLROTATEFPROC __gleRotatef;
typedef void (GLE_FUNCPTR * PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLSCALEDPROC __gleScaled;
typedef void (GLE_FUNCPTR * PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLSCALEFPROC __gleScalef;
typedef void (GLE_FUNCPTR * PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLTRANSLATEDPROC __gleTranslated;
typedef void (GLE_FUNCPTR * PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLTRANSLATEFPROC __gleTranslatef;
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
PFNGLDRAWARRAYSPROC __gleDrawArrays;
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
PFNGLDRAWELEMENTSPROC __gleDrawElements;
typedef void (GLE_FUNCPTR * PFNGLGETPOINTERVPROC)(GLenum pname, GLvoid* *params);
PFNGLGETPOINTERVPROC __gleGetPointerv;
typedef void (GLE_FUNCPTR * PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
PFNGLPOLYGONOFFSETPROC __glePolygonOffset;
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
PFNGLCOPYTEXIMAGE1DPROC __gleCopyTexImage1D;
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
PFNGLCOPYTEXIMAGE2DPROC __gleCopyTexImage2D;
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
PFNGLCOPYTEXSUBIMAGE1DPROC __gleCopyTexSubImage1D;
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXSUBIMAGE2DPROC __gleCopyTexSubImage2D;
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXSUBIMAGE1DPROC __gleTexSubImage1D;
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXSUBIMAGE2DPROC __gleTexSubImage2D;
typedef void (GLE_FUNCPTR * PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
PFNGLBINDTEXTUREPROC __gleBindTexture;
typedef void (GLE_FUNCPTR * PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
PFNGLDELETETEXTURESPROC __gleDeleteTextures;
typedef void (GLE_FUNCPTR * PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
PFNGLGENTEXTURESPROC __gleGenTextures;
typedef GLboolean (GLE_FUNCPTR * PFNGLISTEXTUREPROC)(GLuint texture);
PFNGLISTEXTUREPROC __gleIsTexture;
typedef void (GLE_FUNCPTR * PFNGLARRAYELEMENTPROC)(GLint i);
PFNGLARRAYELEMENTPROC __gleArrayElement;
typedef void (GLE_FUNCPTR * PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLCOLORPOINTERPROC __gleColorPointer;
typedef void (GLE_FUNCPTR * PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
PFNGLDISABLECLIENTSTATEPROC __gleDisableClientState;
typedef void (GLE_FUNCPTR * PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const GLvoid *pointer);
PFNGLEDGEFLAGPOINTERPROC __gleEdgeFlagPointer;
typedef void (GLE_FUNCPTR * PFNGLENABLECLIENTSTATEPROC)(GLenum array);
PFNGLENABLECLIENTSTATEPROC __gleEnableClientState;
typedef void (GLE_FUNCPTR * PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLINDEXPOINTERPROC __gleIndexPointer;
typedef void (GLE_FUNCPTR * PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const GLvoid *pointer);
PFNGLINTERLEAVEDARRAYSPROC __gleInterleavedArrays;
typedef void (GLE_FUNCPTR * PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLNORMALPOINTERPROC __gleNormalPointer;
typedef void (GLE_FUNCPTR * PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLTEXCOORDPOINTERPROC __gleTexCoordPointer;
typedef void (GLE_FUNCPTR * PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLVERTEXPOINTERPROC __gleVertexPointer;
typedef GLboolean (GLE_FUNCPTR * PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint *textures, GLboolean *residences);
PFNGLARETEXTURESRESIDENTPROC __gleAreTexturesResident;
typedef void (GLE_FUNCPTR * PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint *textures, const GLclampf *priorities);
PFNGLPRIORITIZETEXTURESPROC __glePrioritizeTextures;
typedef void (GLE_FUNCPTR * PFNGLINDEXUBPROC)(GLubyte c);
PFNGLINDEXUBPROC __gleIndexub;
typedef void (GLE_FUNCPTR * PFNGLINDEXUBVPROC)(const GLubyte *c);
PFNGLINDEXUBVPROC __gleIndexubv;
typedef void (GLE_FUNCPTR * PFNGLPOPCLIENTATTRIBPROC)();
PFNGLPOPCLIENTATTRIBPROC __glePopClientAttrib;
typedef void (GLE_FUNCPTR * PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);
PFNGLPUSHCLIENTATTRIBPROC __glePushClientAttrib;
typedef void (GLE_FUNCPTR * PFNGLBLENDCOLORPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
PFNGLBLENDCOLORPROC __gleBlendColor;
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONPROC)(GLenum mode);
PFNGLBLENDEQUATIONPROC __gleBlendEquation;
typedef void (GLE_FUNCPTR * PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
PFNGLDRAWRANGEELEMENTSPROC __gleDrawRangeElements;
typedef void (GLE_FUNCPTR * PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXIMAGE3DPROC __gleTexImage3D;
typedef void (GLE_FUNCPTR * PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
PFNGLTEXSUBIMAGE3DPROC __gleTexSubImage3D;
typedef void (GLE_FUNCPTR * PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXSUBIMAGE3DPROC __gleCopyTexSubImage3D;
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
PFNGLCOLORTABLEPROC __gleColorTable;
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
PFNGLCOLORTABLEPARAMETERFVPROC __gleColorTableParameterfv;
typedef void (GLE_FUNCPTR * PFNGLCOLORTABLEPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
PFNGLCOLORTABLEPARAMETERIVPROC __gleColorTableParameteriv;
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORTABLEPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
PFNGLCOPYCOLORTABLEPROC __gleCopyColorTable;
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLvoid *table);
PFNGLGETCOLORTABLEPROC __gleGetColorTable;
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETCOLORTABLEPARAMETERFVPROC __gleGetColorTableParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETCOLORTABLEPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETCOLORTABLEPARAMETERIVPROC __gleGetColorTableParameteriv;
typedef void (GLE_FUNCPTR * PFNGLCOLORSUBTABLEPROC)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
PFNGLCOLORSUBTABLEPROC __gleColorSubTable;
typedef void (GLE_FUNCPTR * PFNGLCOPYCOLORSUBTABLEPROC)(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
PFNGLCOPYCOLORSUBTABLEPROC __gleCopyColorSubTable;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER1DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
PFNGLCONVOLUTIONFILTER1DPROC __gleConvolutionFilter1D;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONFILTER2DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
PFNGLCONVOLUTIONFILTER2DPROC __gleConvolutionFilter2D;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat params);
PFNGLCONVOLUTIONPARAMETERFPROC __gleConvolutionParameterf;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
PFNGLCONVOLUTIONPARAMETERFVPROC __gleConvolutionParameterfv;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIPROC)(GLenum target, GLenum pname, GLint params);
PFNGLCONVOLUTIONPARAMETERIPROC __gleConvolutionParameteri;
typedef void (GLE_FUNCPTR * PFNGLCONVOLUTIONPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint *params);
PFNGLCONVOLUTIONPARAMETERIVPROC __gleConvolutionParameteriv;
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER1DPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
PFNGLCOPYCONVOLUTIONFILTER1DPROC __gleCopyConvolutionFilter1D;
typedef void (GLE_FUNCPTR * PFNGLCOPYCONVOLUTIONFILTER2DPROC)(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYCONVOLUTIONFILTER2DPROC __gleCopyConvolutionFilter2D;
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLvoid *image);
PFNGLGETCONVOLUTIONFILTERPROC __gleGetConvolutionFilter;
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETCONVOLUTIONPARAMETERFVPROC __gleGetConvolutionParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETCONVOLUTIONPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETCONVOLUTIONPARAMETERIVPROC __gleGetConvolutionParameteriv;
typedef void (GLE_FUNCPTR * PFNGLGETSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
PFNGLGETSEPARABLEFILTERPROC __gleGetSeparableFilter;
typedef void (GLE_FUNCPTR * PFNGLSEPARABLEFILTER2DPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
PFNGLSEPARABLEFILTER2DPROC __gleSeparableFilter2D;
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
PFNGLGETHISTOGRAMPROC __gleGetHistogram;
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETHISTOGRAMPARAMETERFVPROC __gleGetHistogramParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETHISTOGRAMPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETHISTOGRAMPARAMETERIVPROC __gleGetHistogramParameteriv;
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
PFNGLGETMINMAXPROC __gleGetMinmax;
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat *params);
PFNGLGETMINMAXPARAMETERFVPROC __gleGetMinmaxParameterfv;
typedef void (GLE_FUNCPTR * PFNGLGETMINMAXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETMINMAXPARAMETERIVPROC __gleGetMinmaxParameteriv;
typedef void (GLE_FUNCPTR * PFNGLHISTOGRAMPROC)(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
PFNGLHISTOGRAMPROC __gleHistogram;
typedef void (GLE_FUNCPTR * PFNGLMINMAXPROC)(GLenum target, GLenum internalformat, GLboolean sink);
PFNGLMINMAXPROC __gleMinmax;
typedef void (GLE_FUNCPTR * PFNGLRESETHISTOGRAMPROC)(GLenum target);
PFNGLRESETHISTOGRAMPROC __gleResetHistogram;
typedef void (GLE_FUNCPTR * PFNGLRESETMINMAXPROC)(GLenum target);
PFNGLRESETMINMAXPROC __gleResetMinmax;
typedef void (GLE_FUNCPTR * PFNGLACTIVETEXTUREPROC)(GLenum texture);
PFNGLACTIVETEXTUREPROC __gleActiveTexture;
typedef void (GLE_FUNCPTR * PFNGLSAMPLECOVERAGEPROC)(GLclampf value, GLboolean invert);
PFNGLSAMPLECOVERAGEPROC __gleSampleCoverage;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXIMAGE3DPROC __gleCompressedTexImage3D;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXIMAGE2DPROC __gleCompressedTexImage2D;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXIMAGE1DPROC __gleCompressedTexImage1D;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC __gleCompressedTexSubImage3D;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __gleCompressedTexSubImage2D;
typedef void (GLE_FUNCPTR * PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __gleCompressedTexSubImage1D;
typedef void (GLE_FUNCPTR * PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, GLvoid *img);
PFNGLGETCOMPRESSEDTEXIMAGEPROC __gleGetCompressedTexImage;
typedef void (GLE_FUNCPTR * PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
PFNGLCLIENTACTIVETEXTUREPROC __gleClientActiveTexture;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
PFNGLMULTITEXCOORD1DPROC __gleMultiTexCoord1d;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble *v);
PFNGLMULTITEXCOORD1DVPROC __gleMultiTexCoord1dv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
PFNGLMULTITEXCOORD1FPROC __gleMultiTexCoord1f;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat *v);
PFNGLMULTITEXCOORD1FVPROC __gleMultiTexCoord1fv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
PFNGLMULTITEXCOORD1IPROC __gleMultiTexCoord1i;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint *v);
PFNGLMULTITEXCOORD1IVPROC __gleMultiTexCoord1iv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
PFNGLMULTITEXCOORD1SPROC __gleMultiTexCoord1s;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort *v);
PFNGLMULTITEXCOORD1SVPROC __gleMultiTexCoord1sv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
PFNGLMULTITEXCOORD2DPROC __gleMultiTexCoord2d;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble *v);
PFNGLMULTITEXCOORD2DVPROC __gleMultiTexCoord2dv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
PFNGLMULTITEXCOORD2FPROC __gleMultiTexCoord2f;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat *v);
PFNGLMULTITEXCOORD2FVPROC __gleMultiTexCoord2fv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
PFNGLMULTITEXCOORD2IPROC __gleMultiTexCoord2i;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint *v);
PFNGLMULTITEXCOORD2IVPROC __gleMultiTexCoord2iv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
PFNGLMULTITEXCOORD2SPROC __gleMultiTexCoord2s;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort *v);
PFNGLMULTITEXCOORD2SVPROC __gleMultiTexCoord2sv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
PFNGLMULTITEXCOORD3DPROC __gleMultiTexCoord3d;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble *v);
PFNGLMULTITEXCOORD3DVPROC __gleMultiTexCoord3dv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
PFNGLMULTITEXCOORD3FPROC __gleMultiTexCoord3f;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat *v);
PFNGLMULTITEXCOORD3FVPROC __gleMultiTexCoord3fv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
PFNGLMULTITEXCOORD3IPROC __gleMultiTexCoord3i;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint *v);
PFNGLMULTITEXCOORD3IVPROC __gleMultiTexCoord3iv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
PFNGLMULTITEXCOORD3SPROC __gleMultiTexCoord3s;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort *v);
PFNGLMULTITEXCOORD3SVPROC __gleMultiTexCoord3sv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
PFNGLMULTITEXCOORD4DPROC __gleMultiTexCoord4d;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble *v);
PFNGLMULTITEXCOORD4DVPROC __gleMultiTexCoord4dv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
PFNGLMULTITEXCOORD4FPROC __gleMultiTexCoord4f;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat *v);
PFNGLMULTITEXCOORD4FVPROC __gleMultiTexCoord4fv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
PFNGLMULTITEXCOORD4IPROC __gleMultiTexCoord4i;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint *v);
PFNGLMULTITEXCOORD4IVPROC __gleMultiTexCoord4iv;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
PFNGLMULTITEXCOORD4SPROC __gleMultiTexCoord4s;
typedef void (GLE_FUNCPTR * PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort *v);
PFNGLMULTITEXCOORD4SVPROC __gleMultiTexCoord4sv;
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat *m);
PFNGLLOADTRANSPOSEMATRIXFPROC __gleLoadTransposeMatrixf;
typedef void (GLE_FUNCPTR * PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble *m);
PFNGLLOADTRANSPOSEMATRIXDPROC __gleLoadTransposeMatrixd;
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat *m);
PFNGLMULTTRANSPOSEMATRIXFPROC __gleMultTransposeMatrixf;
typedef void (GLE_FUNCPTR * PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble *m);
PFNGLMULTTRANSPOSEMATRIXDPROC __gleMultTransposeMatrixd;
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
PFNGLBLENDFUNCSEPARATEPROC __gleBlendFuncSeparate;
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
PFNGLMULTIDRAWARRAYSPROC __gleMultiDrawArrays;
typedef void (GLE_FUNCPTR * PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
PFNGLMULTIDRAWELEMENTSPROC __gleMultiDrawElements;
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
PFNGLPOINTPARAMETERFPROC __glePointParameterf;
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat *params);
PFNGLPOINTPARAMETERFVPROC __glePointParameterfv;
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
PFNGLPOINTPARAMETERIPROC __glePointParameteri;
typedef void (GLE_FUNCPTR * PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint *params);
PFNGLPOINTPARAMETERIVPROC __glePointParameteriv;
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFPROC)(GLfloat coord);
PFNGLFOGCOORDFPROC __gleFogCoordf;
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDFVPROC)(const GLfloat *coord);
PFNGLFOGCOORDFVPROC __gleFogCoordfv;
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDPROC)(GLdouble coord);
PFNGLFOGCOORDDPROC __gleFogCoordd;
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDDVPROC)(const GLdouble *coord);
PFNGLFOGCOORDDVPROC __gleFogCoorddv;
typedef void (GLE_FUNCPTR * PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLFOGCOORDPOINTERPROC __gleFogCoordPointer;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
PFNGLSECONDARYCOLOR3BPROC __gleSecondaryColor3b;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte *v);
PFNGLSECONDARYCOLOR3BVPROC __gleSecondaryColor3bv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
PFNGLSECONDARYCOLOR3DPROC __gleSecondaryColor3d;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble *v);
PFNGLSECONDARYCOLOR3DVPROC __gleSecondaryColor3dv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
PFNGLSECONDARYCOLOR3FPROC __gleSecondaryColor3f;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat *v);
PFNGLSECONDARYCOLOR3FVPROC __gleSecondaryColor3fv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
PFNGLSECONDARYCOLOR3IPROC __gleSecondaryColor3i;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3IVPROC)(const GLint *v);
PFNGLSECONDARYCOLOR3IVPROC __gleSecondaryColor3iv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
PFNGLSECONDARYCOLOR3SPROC __gleSecondaryColor3s;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3SVPROC)(const GLshort *v);
PFNGLSECONDARYCOLOR3SVPROC __gleSecondaryColor3sv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
PFNGLSECONDARYCOLOR3UBPROC __gleSecondaryColor3ub;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte *v);
PFNGLSECONDARYCOLOR3UBVPROC __gleSecondaryColor3ubv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
PFNGLSECONDARYCOLOR3UIPROC __gleSecondaryColor3ui;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint *v);
PFNGLSECONDARYCOLOR3UIVPROC __gleSecondaryColor3uiv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
PFNGLSECONDARYCOLOR3USPROC __gleSecondaryColor3us;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLOR3USVPROC)(const GLushort *v);
PFNGLSECONDARYCOLOR3USVPROC __gleSecondaryColor3usv;
typedef void (GLE_FUNCPTR * PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLSECONDARYCOLORPOINTERPROC __gleSecondaryColorPointer;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
PFNGLWINDOWPOS2DPROC __gleWindowPos2d;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2DVPROC)(const GLdouble *v);
PFNGLWINDOWPOS2DVPROC __gleWindowPos2dv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
PFNGLWINDOWPOS2FPROC __gleWindowPos2f;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2FVPROC)(const GLfloat *v);
PFNGLWINDOWPOS2FVPROC __gleWindowPos2fv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
PFNGLWINDOWPOS2IPROC __gleWindowPos2i;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2IVPROC)(const GLint *v);
PFNGLWINDOWPOS2IVPROC __gleWindowPos2iv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
PFNGLWINDOWPOS2SPROC __gleWindowPos2s;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS2SVPROC)(const GLshort *v);
PFNGLWINDOWPOS2SVPROC __gleWindowPos2sv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLWINDOWPOS3DPROC __gleWindowPos3d;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3DVPROC)(const GLdouble *v);
PFNGLWINDOWPOS3DVPROC __gleWindowPos3dv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLWINDOWPOS3FPROC __gleWindowPos3f;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3FVPROC)(const GLfloat *v);
PFNGLWINDOWPOS3FVPROC __gleWindowPos3fv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
PFNGLWINDOWPOS3IPROC __gleWindowPos3i;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3IVPROC)(const GLint *v);
PFNGLWINDOWPOS3IVPROC __gleWindowPos3iv;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLWINDOWPOS3SPROC __gleWindowPos3s;
typedef void (GLE_FUNCPTR * PFNGLWINDOWPOS3SVPROC)(const GLshort *v);
PFNGLWINDOWPOS3SVPROC __gleWindowPos3sv;
typedef void (GLE_FUNCPTR * PFNGLGENQUERIESPROC)(GLsizei n, GLuint *ids);
PFNGLGENQUERIESPROC __gleGenQueries;
typedef void (GLE_FUNCPTR * PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint *ids);
PFNGLDELETEQUERIESPROC __gleDeleteQueries;
typedef GLboolean (GLE_FUNCPTR * PFNGLISQUERYPROC)(GLuint id);
PFNGLISQUERYPROC __gleIsQuery;
typedef void (GLE_FUNCPTR * PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
PFNGLBEGINQUERYPROC __gleBeginQuery;
typedef void (GLE_FUNCPTR * PFNGLENDQUERYPROC)(GLenum target);
PFNGLENDQUERYPROC __gleEndQuery;
typedef void (GLE_FUNCPTR * PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETQUERYIVPROC __gleGetQueryiv;
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint *params);
PFNGLGETQUERYOBJECTIVPROC __gleGetQueryObjectiv;
typedef void (GLE_FUNCPTR * PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint *params);
PFNGLGETQUERYOBJECTUIVPROC __gleGetQueryObjectuiv;
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
PFNGLBINDBUFFERPROC __gleBindBuffer;
typedef void (GLE_FUNCPTR * PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
PFNGLDELETEBUFFERSPROC __gleDeleteBuffers;
typedef void (GLE_FUNCPTR * PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
PFNGLGENBUFFERSPROC __gleGenBuffers;
typedef GLboolean (GLE_FUNCPTR * PFNGLISBUFFERPROC)(GLuint buffer);
PFNGLISBUFFERPROC __gleIsBuffer;
typedef void (GLE_FUNCPTR * PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
PFNGLBUFFERDATAPROC __gleBufferData;
typedef void (GLE_FUNCPTR * PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
PFNGLBUFFERSUBDATAPROC __gleBufferSubData;
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data);
PFNGLGETBUFFERSUBDATAPROC __gleGetBufferSubData;
typedef GLvoid* (GLE_FUNCPTR * PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
PFNGLMAPBUFFERPROC __gleMapBuffer;
typedef GLboolean (GLE_FUNCPTR * PFNGLUNMAPBUFFERPROC)(GLenum target);
PFNGLUNMAPBUFFERPROC __gleUnmapBuffer;
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETBUFFERPARAMETERIVPROC __gleGetBufferParameteriv;
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, GLvoid* *params);
PFNGLGETBUFFERPOINTERVPROC __gleGetBufferPointerv;
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
PFNGLBLENDEQUATIONSEPARATEPROC __gleBlendEquationSeparate;
typedef void (GLE_FUNCPTR * PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);
PFNGLDRAWBUFFERSPROC __gleDrawBuffers;
typedef void (GLE_FUNCPTR * PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
PFNGLSTENCILOPSEPARATEPROC __gleStencilOpSeparate;
typedef void (GLE_FUNCPTR * PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
PFNGLSTENCILFUNCSEPARATEPROC __gleStencilFuncSeparate;
typedef void (GLE_FUNCPTR * PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
PFNGLSTENCILMASKSEPARATEPROC __gleStencilMaskSeparate;
typedef void (GLE_FUNCPTR * PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLATTACHSHADERPROC __gleAttachShader;
typedef void (GLE_FUNCPTR * PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar *name);
PFNGLBINDATTRIBLOCATIONPROC __gleBindAttribLocation;
typedef void (GLE_FUNCPTR * PFNGLCOMPILESHADERPROC)(GLuint shader);
PFNGLCOMPILESHADERPROC __gleCompileShader;
typedef GLuint (GLE_FUNCPTR * PFNGLCREATEPROGRAMPROC)();
PFNGLCREATEPROGRAMPROC __gleCreateProgram;
typedef GLuint (GLE_FUNCPTR * PFNGLCREATESHADERPROC)(GLenum type);
PFNGLCREATESHADERPROC __gleCreateShader;
typedef void (GLE_FUNCPTR * PFNGLDELETEPROGRAMPROC)(GLuint program);
PFNGLDELETEPROGRAMPROC __gleDeleteProgram;
typedef void (GLE_FUNCPTR * PFNGLDELETESHADERPROC)(GLuint shader);
PFNGLDELETESHADERPROC __gleDeleteShader;
typedef void (GLE_FUNCPTR * PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLDETACHSHADERPROC __gleDetachShader;
typedef void (GLE_FUNCPTR * PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLDISABLEVERTEXATTRIBARRAYPROC __gleDisableVertexAttribArray;
typedef void (GLE_FUNCPTR * PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLENABLEVERTEXATTRIBARRAYPROC __gleEnableVertexAttribArray;
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
PFNGLGETACTIVEATTRIBPROC __gleGetActiveAttrib;
typedef void (GLE_FUNCPTR * PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
PFNGLGETACTIVEUNIFORMPROC __gleGetActiveUniform;
typedef void (GLE_FUNCPTR * PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *obj);
PFNGLGETATTACHEDSHADERSPROC __gleGetAttachedShaders;
typedef GLint (GLE_FUNCPTR * PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar *name);
PFNGLGETATTRIBLOCATIONPROC __gleGetAttribLocation;
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
PFNGLGETPROGRAMIVPROC __gleGetProgramiv;
typedef void (GLE_FUNCPTR * PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
PFNGLGETPROGRAMINFOLOGPROC __gleGetProgramInfoLog;
typedef void (GLE_FUNCPTR * PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
PFNGLGETSHADERIVPROC __gleGetShaderiv;
typedef void (GLE_FUNCPTR * PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
PFNGLGETSHADERINFOLOGPROC __gleGetShaderInfoLog;
typedef void (GLE_FUNCPTR * PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
PFNGLGETSHADERSOURCEPROC __gleGetShaderSource;
typedef GLint (GLE_FUNCPTR * PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
PFNGLGETUNIFORMLOCATIONPROC __gleGetUniformLocation;
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat *params);
PFNGLGETUNIFORMFVPROC __gleGetUniformfv;
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint *params);
PFNGLGETUNIFORMIVPROC __gleGetUniformiv;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble *params);
PFNGLGETVERTEXATTRIBDVPROC __gleGetVertexAttribdv;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat *params);
PFNGLGETVERTEXATTRIBFVPROC __gleGetVertexAttribfv;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint *params);
PFNGLGETVERTEXATTRIBIVPROC __gleGetVertexAttribiv;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, GLvoid* *pointer);
PFNGLGETVERTEXATTRIBPOINTERVPROC __gleGetVertexAttribPointerv;
typedef GLboolean (GLE_FUNCPTR * PFNGLISPROGRAMPROC)(GLuint program);
PFNGLISPROGRAMPROC __gleIsProgram;
typedef GLboolean (GLE_FUNCPTR * PFNGLISSHADERPROC)(GLuint shader);
PFNGLISSHADERPROC __gleIsShader;
typedef void (GLE_FUNCPTR * PFNGLLINKPROGRAMPROC)(GLuint program);
PFNGLLINKPROGRAMPROC __gleLinkProgram;
typedef void (GLE_FUNCPTR * PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
PFNGLSHADERSOURCEPROC __gleShaderSource;
typedef void (GLE_FUNCPTR * PFNGLUSEPROGRAMPROC)(GLuint program);
PFNGLUSEPROGRAMPROC __gleUseProgram;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
PFNGLUNIFORM1FPROC __gleUniform1f;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
PFNGLUNIFORM2FPROC __gleUniform2f;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
PFNGLUNIFORM3FPROC __gleUniform3f;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
PFNGLUNIFORM4FPROC __gleUniform4f;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
PFNGLUNIFORM1IPROC __gleUniform1i;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
PFNGLUNIFORM2IPROC __gleUniform2i;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
PFNGLUNIFORM3IPROC __gleUniform3i;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
PFNGLUNIFORM4IPROC __gleUniform4i;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);
PFNGLUNIFORM1FVPROC __gleUniform1fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);
PFNGLUNIFORM2FVPROC __gleUniform2fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
PFNGLUNIFORM3FVPROC __gleUniform3fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat *value);
PFNGLUNIFORM4FVPROC __gleUniform4fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint *value);
PFNGLUNIFORM1IVPROC __gleUniform1iv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint *value);
PFNGLUNIFORM2IVPROC __gleUniform2iv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint *value);
PFNGLUNIFORM3IVPROC __gleUniform3iv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint *value);
PFNGLUNIFORM4IVPROC __gleUniform4iv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX2FVPROC __gleUniformMatrix2fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX3FVPROC __gleUniformMatrix3fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX4FVPROC __gleUniformMatrix4fv;
typedef void (GLE_FUNCPTR * PFNGLVALIDATEPROGRAMPROC)(GLuint program);
PFNGLVALIDATEPROGRAMPROC __gleValidateProgram;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
PFNGLVERTEXATTRIB1DPROC __gleVertexAttrib1d;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble *v);
PFNGLVERTEXATTRIB1DVPROC __gleVertexAttrib1dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
PFNGLVERTEXATTRIB1FPROC __gleVertexAttrib1f;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat *v);
PFNGLVERTEXATTRIB1FVPROC __gleVertexAttrib1fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
PFNGLVERTEXATTRIB1SPROC __gleVertexAttrib1s;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIB1SVPROC __gleVertexAttrib1sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
PFNGLVERTEXATTRIB2DPROC __gleVertexAttrib2d;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble *v);
PFNGLVERTEXATTRIB2DVPROC __gleVertexAttrib2dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
PFNGLVERTEXATTRIB2FPROC __gleVertexAttrib2f;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat *v);
PFNGLVERTEXATTRIB2FVPROC __gleVertexAttrib2fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
PFNGLVERTEXATTRIB2SPROC __gleVertexAttrib2s;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIB2SVPROC __gleVertexAttrib2sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
PFNGLVERTEXATTRIB3DPROC __gleVertexAttrib3d;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble *v);
PFNGLVERTEXATTRIB3DVPROC __gleVertexAttrib3dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
PFNGLVERTEXATTRIB3FPROC __gleVertexAttrib3f;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat *v);
PFNGLVERTEXATTRIB3FVPROC __gleVertexAttrib3fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
PFNGLVERTEXATTRIB3SPROC __gleVertexAttrib3s;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIB3SVPROC __gleVertexAttrib3sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte *v);
PFNGLVERTEXATTRIB4NBVPROC __gleVertexAttrib4Nbv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIB4NIVPROC __gleVertexAttrib4Niv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIB4NSVPROC __gleVertexAttrib4Nsv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
PFNGLVERTEXATTRIB4NUBPROC __gleVertexAttrib4Nub;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte *v);
PFNGLVERTEXATTRIB4NUBVPROC __gleVertexAttrib4Nubv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIB4NUIVPROC __gleVertexAttrib4Nuiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort *v);
PFNGLVERTEXATTRIB4NUSVPROC __gleVertexAttrib4Nusv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte *v);
PFNGLVERTEXATTRIB4BVPROC __gleVertexAttrib4bv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLVERTEXATTRIB4DPROC __gleVertexAttrib4d;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble *v);
PFNGLVERTEXATTRIB4DVPROC __gleVertexAttrib4dv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLVERTEXATTRIB4FPROC __gleVertexAttrib4f;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat *v);
PFNGLVERTEXATTRIB4FVPROC __gleVertexAttrib4fv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIB4IVPROC __gleVertexAttrib4iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLVERTEXATTRIB4SPROC __gleVertexAttrib4s;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIB4SVPROC __gleVertexAttrib4sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte *v);
PFNGLVERTEXATTRIB4UBVPROC __gleVertexAttrib4ubv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIB4UIVPROC __gleVertexAttrib4uiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort *v);
PFNGLVERTEXATTRIB4USVPROC __gleVertexAttrib4usv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
PFNGLVERTEXATTRIBPOINTERPROC __gleVertexAttribPointer;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX2X3FVPROC __gleUniformMatrix2x3fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX3X2FVPROC __gleUniformMatrix3x2fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX2X4FVPROC __gleUniformMatrix2x4fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX4X2FVPROC __gleUniformMatrix4x2fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX3X4FVPROC __gleUniformMatrix3x4fv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX4X3FVPROC __gleUniformMatrix4x3fv;
typedef void (GLE_FUNCPTR * PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
PFNGLCOLORMASKIPROC __gleColorMaski;
typedef void (GLE_FUNCPTR * PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean *data);
PFNGLGETBOOLEANI_VPROC __gleGetBooleani_v;
typedef void (GLE_FUNCPTR * PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint *data);
PFNGLGETINTEGERI_VPROC __gleGetIntegeri_v;
typedef void (GLE_FUNCPTR * PFNGLENABLEIPROC)(GLenum target, GLuint index);
PFNGLENABLEIPROC __gleEnablei;
typedef void (GLE_FUNCPTR * PFNGLDISABLEIPROC)(GLenum target, GLuint index);
PFNGLDISABLEIPROC __gleDisablei;
typedef GLboolean (GLE_FUNCPTR * PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
PFNGLISENABLEDIPROC __gleIsEnabledi;
typedef void (GLE_FUNCPTR * PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
PFNGLBEGINTRANSFORMFEEDBACKPROC __gleBeginTransformFeedback;
typedef void (GLE_FUNCPTR * PFNGLENDTRANSFORMFEEDBACKPROC)();
PFNGLENDTRANSFORMFEEDBACKPROC __gleEndTransformFeedback;
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
PFNGLBINDBUFFERRANGEPROC __gleBindBufferRange;
typedef void (GLE_FUNCPTR * PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
PFNGLBINDBUFFERBASEPROC __gleBindBufferBase;
typedef void (GLE_FUNCPTR * PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar* *varyings, GLenum bufferMode);
PFNGLTRANSFORMFEEDBACKVARYINGSPROC __gleTransformFeedbackVaryings;
typedef void (GLE_FUNCPTR * PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC __gleGetTransformFeedbackVarying;
typedef void (GLE_FUNCPTR * PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
PFNGLCLAMPCOLORPROC __gleClampColor;
typedef void (GLE_FUNCPTR * PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
PFNGLBEGINCONDITIONALRENDERPROC __gleBeginConditionalRender;
typedef void (GLE_FUNCPTR * PFNGLENDCONDITIONALRENDERPROC)();
PFNGLENDCONDITIONALRENDERPROC __gleEndConditionalRender;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
PFNGLVERTEXATTRIBIPOINTERPROC __gleVertexAttribIPointer;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint *params);
PFNGLGETVERTEXATTRIBIIVPROC __gleGetVertexAttribIiv;
typedef void (GLE_FUNCPTR * PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint *params);
PFNGLGETVERTEXATTRIBIUIVPROC __gleGetVertexAttribIuiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
PFNGLVERTEXATTRIBI1IPROC __gleVertexAttribI1i;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
PFNGLVERTEXATTRIBI2IPROC __gleVertexAttribI2i;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
PFNGLVERTEXATTRIBI3IPROC __gleVertexAttribI3i;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
PFNGLVERTEXATTRIBI4IPROC __gleVertexAttribI4i;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
PFNGLVERTEXATTRIBI1UIPROC __gleVertexAttribI1ui;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
PFNGLVERTEXATTRIBI2UIPROC __gleVertexAttribI2ui;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
PFNGLVERTEXATTRIBI3UIPROC __gleVertexAttribI3ui;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
PFNGLVERTEXATTRIBI4UIPROC __gleVertexAttribI4ui;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIBI1IVPROC __gleVertexAttribI1iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIBI2IVPROC __gleVertexAttribI2iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIBI3IVPROC __gleVertexAttribI3iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint *v);
PFNGLVERTEXATTRIBI4IVPROC __gleVertexAttribI4iv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIBI1UIVPROC __gleVertexAttribI1uiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIBI2UIVPROC __gleVertexAttribI2uiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIBI3UIVPROC __gleVertexAttribI3uiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint *v);
PFNGLVERTEXATTRIBI4UIVPROC __gleVertexAttribI4uiv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte *v);
PFNGLVERTEXATTRIBI4BVPROC __gleVertexAttribI4bv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort *v);
PFNGLVERTEXATTRIBI4SVPROC __gleVertexAttribI4sv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte *v);
PFNGLVERTEXATTRIBI4UBVPROC __gleVertexAttribI4ubv;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort *v);
PFNGLVERTEXATTRIBI4USVPROC __gleVertexAttribI4usv;
typedef void (GLE_FUNCPTR * PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint *params);
PFNGLGETUNIFORMUIVPROC __gleGetUniformuiv;
typedef void (GLE_FUNCPTR * PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar *name);
PFNGLBINDFRAGDATALOCATIONPROC __gleBindFragDataLocation;
typedef GLint (GLE_FUNCPTR * PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar *name);
PFNGLGETFRAGDATALOCATIONPROC __gleGetFragDataLocation;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
PFNGLUNIFORM1UIPROC __gleUniform1ui;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
PFNGLUNIFORM2UIPROC __gleUniform2ui;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
PFNGLUNIFORM3UIPROC __gleUniform3ui;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
PFNGLUNIFORM4UIPROC __gleUniform4ui;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint *value);
PFNGLUNIFORM1UIVPROC __gleUniform1uiv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint *value);
PFNGLUNIFORM2UIVPROC __gleUniform2uiv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint *value);
PFNGLUNIFORM3UIVPROC __gleUniform3uiv;
typedef void (GLE_FUNCPTR * PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint *value);
PFNGLUNIFORM4UIVPROC __gleUniform4uiv;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint *params);
PFNGLTEXPARAMETERIIVPROC __gleTexParameterIiv;
typedef void (GLE_FUNCPTR * PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint *params);
PFNGLTEXPARAMETERIUIVPROC __gleTexParameterIuiv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint *params);
PFNGLGETTEXPARAMETERIIVPROC __gleGetTexParameterIiv;
typedef void (GLE_FUNCPTR * PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint *params);
PFNGLGETTEXPARAMETERIUIVPROC __gleGetTexParameterIuiv;
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint *value);
PFNGLCLEARBUFFERIVPROC __gleClearBufferiv;
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint *value);
PFNGLCLEARBUFFERUIVPROC __gleClearBufferuiv;
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat *value);
PFNGLCLEARBUFFERFVPROC __gleClearBufferfv;
typedef void (GLE_FUNCPTR * PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
PFNGLCLEARBUFFERFIPROC __gleClearBufferfi;
typedef const GLubyte * (GLE_FUNCPTR * PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
PFNGLGETSTRINGIPROC __gleGetStringi;
typedef void (GLE_FUNCPTR * PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
PFNGLDRAWARRAYSINSTANCEDPROC __gleDrawArraysInstanced;
typedef void (GLE_FUNCPTR * PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);
PFNGLDRAWELEMENTSINSTANCEDPROC __gleDrawElementsInstanced;
typedef void (GLE_FUNCPTR * PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
PFNGLTEXBUFFERPROC __gleTexBuffer;
typedef void (GLE_FUNCPTR * PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
PFNGLPRIMITIVERESTARTINDEXPROC __glePrimitiveRestartIndex;
typedef void (GLE_FUNCPTR * PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 *data);
PFNGLGETINTEGER64I_VPROC __gleGetInteger64i_v;
typedef void (GLE_FUNCPTR * PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 *params);
PFNGLGETBUFFERPARAMETERI64VPROC __gleGetBufferParameteri64v;
typedef void (GLE_FUNCPTR * PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
PFNGLFRAMEBUFFERTEXTUREPROC __gleFramebufferTexture;
typedef void (GLE_FUNCPTR * PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
PFNGLVERTEXATTRIBDIVISORPROC __gleVertexAttribDivisor;
typedef void (GLE_FUNCPTR * PFNGLMINSAMPLESHADINGPROC)(GLclampf value);
PFNGLMINSAMPLESHADINGPROC __gleMinSampleShading;
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
PFNGLBLENDEQUATIONIPROC __gleBlendEquationi;
typedef void (GLE_FUNCPTR * PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
PFNGLBLENDEQUATIONSEPARATEIPROC __gleBlendEquationSeparatei;
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
PFNGLBLENDFUNCIPROC __gleBlendFunci;
typedef void (GLE_FUNCPTR * PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
PFNGLBLENDFUNCSEPARATEIPROC __gleBlendFuncSeparatei;

static int gleIntLoadCore_1_1_Version_3_1()
{
	int bIsLoaded = 1;
	__gleCullFace = (PFNGLCULLFACEPROC)gleIntGetProcAddress("glCullFace");
	if(!TestPointer(__gleCullFace))
	{
		__gleCullFace = gle_CoreStruct.gleVarCullFace;
		if(!__gleCullFace) bIsLoaded = 0;
	}
	__gleFrontFace = (PFNGLFRONTFACEPROC)gleIntGetProcAddress("glFrontFace");
	if(!TestPointer(__gleFrontFace))
	{
		__gleFrontFace = gle_CoreStruct.gleVarFrontFace;
		if(!__gleFrontFace) bIsLoaded = 0;
	}
	__gleHint = (PFNGLHINTPROC)gleIntGetProcAddress("glHint");
	if(!TestPointer(__gleHint))
	{
		__gleHint = gle_CoreStruct.gleVarHint;
		if(!__gleHint) bIsLoaded = 0;
	}
	__gleLineWidth = (PFNGLLINEWIDTHPROC)gleIntGetProcAddress("glLineWidth");
	if(!TestPointer(__gleLineWidth))
	{
		__gleLineWidth = gle_CoreStruct.gleVarLineWidth;
		if(!__gleLineWidth) bIsLoaded = 0;
	}
	__glePointSize = (PFNGLPOINTSIZEPROC)gleIntGetProcAddress("glPointSize");
	if(!TestPointer(__glePointSize))
	{
		__glePointSize = gle_CoreStruct.gleVarPointSize;
		if(!__glePointSize) bIsLoaded = 0;
	}
	__glePolygonMode = (PFNGLPOLYGONMODEPROC)gleIntGetProcAddress("glPolygonMode");
	if(!TestPointer(__glePolygonMode))
	{
		__glePolygonMode = gle_CoreStruct.gleVarPolygonMode;
		if(!__glePolygonMode) bIsLoaded = 0;
	}
	__gleScissor = (PFNGLSCISSORPROC)gleIntGetProcAddress("glScissor");
	if(!TestPointer(__gleScissor))
	{
		__gleScissor = gle_CoreStruct.gleVarScissor;
		if(!__gleScissor) bIsLoaded = 0;
	}
	__gleTexParameterf = (PFNGLTEXPARAMETERFPROC)gleIntGetProcAddress("glTexParameterf");
	if(!TestPointer(__gleTexParameterf))
	{
		__gleTexParameterf = gle_CoreStruct.gleVarTexParameterf;
		if(!__gleTexParameterf) bIsLoaded = 0;
	}
	__gleTexParameterfv = (PFNGLTEXPARAMETERFVPROC)gleIntGetProcAddress("glTexParameterfv");
	if(!TestPointer(__gleTexParameterfv))
	{
		__gleTexParameterfv = gle_CoreStruct.gleVarTexParameterfv;
		if(!__gleTexParameterfv) bIsLoaded = 0;
	}
	__gleTexParameteri = (PFNGLTEXPARAMETERIPROC)gleIntGetProcAddress("glTexParameteri");
	if(!TestPointer(__gleTexParameteri))
	{
		__gleTexParameteri = gle_CoreStruct.gleVarTexParameteri;
		if(!__gleTexParameteri) bIsLoaded = 0;
	}
	__gleTexParameteriv = (PFNGLTEXPARAMETERIVPROC)gleIntGetProcAddress("glTexParameteriv");
	if(!TestPointer(__gleTexParameteriv))
	{
		__gleTexParameteriv = gle_CoreStruct.gleVarTexParameteriv;
		if(!__gleTexParameteriv) bIsLoaded = 0;
	}
	__gleTexImage1D = (PFNGLTEXIMAGE1DPROC)gleIntGetProcAddress("glTexImage1D");
	if(!TestPointer(__gleTexImage1D))
	{
		__gleTexImage1D = gle_CoreStruct.gleVarTexImage1D;
		if(!__gleTexImage1D) bIsLoaded = 0;
	}
	__gleTexImage2D = (PFNGLTEXIMAGE2DPROC)gleIntGetProcAddress("glTexImage2D");
	if(!TestPointer(__gleTexImage2D))
	{
		__gleTexImage2D = gle_CoreStruct.gleVarTexImage2D;
		if(!__gleTexImage2D) bIsLoaded = 0;
	}
	__gleDrawBuffer = (PFNGLDRAWBUFFERPROC)gleIntGetProcAddress("glDrawBuffer");
	if(!TestPointer(__gleDrawBuffer))
	{
		__gleDrawBuffer = gle_CoreStruct.gleVarDrawBuffer;
		if(!__gleDrawBuffer) bIsLoaded = 0;
	}
	__gleClear = (PFNGLCLEARPROC)gleIntGetProcAddress("glClear");
	if(!TestPointer(__gleClear))
	{
		__gleClear = gle_CoreStruct.gleVarClear;
		if(!__gleClear) bIsLoaded = 0;
	}
	__gleClearColor = (PFNGLCLEARCOLORPROC)gleIntGetProcAddress("glClearColor");
	if(!TestPointer(__gleClearColor))
	{
		__gleClearColor = gle_CoreStruct.gleVarClearColor;
		if(!__gleClearColor) bIsLoaded = 0;
	}
	__gleClearStencil = (PFNGLCLEARSTENCILPROC)gleIntGetProcAddress("glClearStencil");
	if(!TestPointer(__gleClearStencil))
	{
		__gleClearStencil = gle_CoreStruct.gleVarClearStencil;
		if(!__gleClearStencil) bIsLoaded = 0;
	}
	__gleClearDepth = (PFNGLCLEARDEPTHPROC)gleIntGetProcAddress("glClearDepth");
	if(!TestPointer(__gleClearDepth))
	{
		__gleClearDepth = gle_CoreStruct.gleVarClearDepth;
		if(!__gleClearDepth) bIsLoaded = 0;
	}
	__gleStencilMask = (PFNGLSTENCILMASKPROC)gleIntGetProcAddress("glStencilMask");
	if(!TestPointer(__gleStencilMask))
	{
		__gleStencilMask = gle_CoreStruct.gleVarStencilMask;
		if(!__gleStencilMask) bIsLoaded = 0;
	}
	__gleColorMask = (PFNGLCOLORMASKPROC)gleIntGetProcAddress("glColorMask");
	if(!TestPointer(__gleColorMask))
	{
		__gleColorMask = gle_CoreStruct.gleVarColorMask;
		if(!__gleColorMask) bIsLoaded = 0;
	}
	__gleDepthMask = (PFNGLDEPTHMASKPROC)gleIntGetProcAddress("glDepthMask");
	if(!TestPointer(__gleDepthMask))
	{
		__gleDepthMask = gle_CoreStruct.gleVarDepthMask;
		if(!__gleDepthMask) bIsLoaded = 0;
	}
	__gleDisable = (PFNGLDISABLEPROC)gleIntGetProcAddress("glDisable");
	if(!TestPointer(__gleDisable))
	{
		__gleDisable = gle_CoreStruct.gleVarDisable;
		if(!__gleDisable) bIsLoaded = 0;
	}
	__gleEnable = (PFNGLENABLEPROC)gleIntGetProcAddress("glEnable");
	if(!TestPointer(__gleEnable))
	{
		__gleEnable = gle_CoreStruct.gleVarEnable;
		if(!__gleEnable) bIsLoaded = 0;
	}
	__gleFinish = (PFNGLFINISHPROC)gleIntGetProcAddress("glFinish");
	if(!TestPointer(__gleFinish))
	{
		__gleFinish = gle_CoreStruct.gleVarFinish;
		if(!__gleFinish) bIsLoaded = 0;
	}
	__gleFlush = (PFNGLFLUSHPROC)gleIntGetProcAddress("glFlush");
	if(!TestPointer(__gleFlush))
	{
		__gleFlush = gle_CoreStruct.gleVarFlush;
		if(!__gleFlush) bIsLoaded = 0;
	}
	__gleBlendFunc = (PFNGLBLENDFUNCPROC)gleIntGetProcAddress("glBlendFunc");
	if(!TestPointer(__gleBlendFunc))
	{
		__gleBlendFunc = gle_CoreStruct.gleVarBlendFunc;
		if(!__gleBlendFunc) bIsLoaded = 0;
	}
	__gleLogicOp = (PFNGLLOGICOPPROC)gleIntGetProcAddress("glLogicOp");
	if(!TestPointer(__gleLogicOp))
	{
		__gleLogicOp = gle_CoreStruct.gleVarLogicOp;
		if(!__gleLogicOp) bIsLoaded = 0;
	}
	__gleStencilFunc = (PFNGLSTENCILFUNCPROC)gleIntGetProcAddress("glStencilFunc");
	if(!TestPointer(__gleStencilFunc))
	{
		__gleStencilFunc = gle_CoreStruct.gleVarStencilFunc;
		if(!__gleStencilFunc) bIsLoaded = 0;
	}
	__gleStencilOp = (PFNGLSTENCILOPPROC)gleIntGetProcAddress("glStencilOp");
	if(!TestPointer(__gleStencilOp))
	{
		__gleStencilOp = gle_CoreStruct.gleVarStencilOp;
		if(!__gleStencilOp) bIsLoaded = 0;
	}
	__gleDepthFunc = (PFNGLDEPTHFUNCPROC)gleIntGetProcAddress("glDepthFunc");
	if(!TestPointer(__gleDepthFunc))
	{
		__gleDepthFunc = gle_CoreStruct.gleVarDepthFunc;
		if(!__gleDepthFunc) bIsLoaded = 0;
	}
	__glePixelStoref = (PFNGLPIXELSTOREFPROC)gleIntGetProcAddress("glPixelStoref");
	if(!TestPointer(__glePixelStoref))
	{
		__glePixelStoref = gle_CoreStruct.gleVarPixelStoref;
		if(!__glePixelStoref) bIsLoaded = 0;
	}
	__glePixelStorei = (PFNGLPIXELSTOREIPROC)gleIntGetProcAddress("glPixelStorei");
	if(!TestPointer(__glePixelStorei))
	{
		__glePixelStorei = gle_CoreStruct.gleVarPixelStorei;
		if(!__glePixelStorei) bIsLoaded = 0;
	}
	__gleReadBuffer = (PFNGLREADBUFFERPROC)gleIntGetProcAddress("glReadBuffer");
	if(!TestPointer(__gleReadBuffer))
	{
		__gleReadBuffer = gle_CoreStruct.gleVarReadBuffer;
		if(!__gleReadBuffer) bIsLoaded = 0;
	}
	__gleReadPixels = (PFNGLREADPIXELSPROC)gleIntGetProcAddress("glReadPixels");
	if(!TestPointer(__gleReadPixels))
	{
		__gleReadPixels = gle_CoreStruct.gleVarReadPixels;
		if(!__gleReadPixels) bIsLoaded = 0;
	}
	__gleGetBooleanv = (PFNGLGETBOOLEANVPROC)gleIntGetProcAddress("glGetBooleanv");
	if(!TestPointer(__gleGetBooleanv))
	{
		__gleGetBooleanv = gle_CoreStruct.gleVarGetBooleanv;
		if(!__gleGetBooleanv) bIsLoaded = 0;
	}
	__gleGetDoublev = (PFNGLGETDOUBLEVPROC)gleIntGetProcAddress("glGetDoublev");
	if(!TestPointer(__gleGetDoublev))
	{
		__gleGetDoublev = gle_CoreStruct.gleVarGetDoublev;
		if(!__gleGetDoublev) bIsLoaded = 0;
	}
	__gleGetError = (PFNGLGETERRORPROC)gleIntGetProcAddress("glGetError");
	if(!TestPointer(__gleGetError))
	{
		__gleGetError = gle_CoreStruct.gleVarGetError;
		if(!__gleGetError) bIsLoaded = 0;
	}
	__gleGetFloatv = (PFNGLGETFLOATVPROC)gleIntGetProcAddress("glGetFloatv");
	if(!TestPointer(__gleGetFloatv))
	{
		__gleGetFloatv = gle_CoreStruct.gleVarGetFloatv;
		if(!__gleGetFloatv) bIsLoaded = 0;
	}
	__gleGetIntegerv = (PFNGLGETINTEGERVPROC)gleIntGetProcAddress("glGetIntegerv");
	if(!TestPointer(__gleGetIntegerv))
	{
		__gleGetIntegerv = gle_CoreStruct.gleVarGetIntegerv;
		if(!__gleGetIntegerv) bIsLoaded = 0;
	}
	__gleGetString = (PFNGLGETSTRINGPROC)gleIntGetProcAddress("glGetString");
	if(!TestPointer(__gleGetString))
	{
		__gleGetString = gle_CoreStruct.gleVarGetString;
		if(!__gleGetString) bIsLoaded = 0;
	}
	__gleGetTexImage = (PFNGLGETTEXIMAGEPROC)gleIntGetProcAddress("glGetTexImage");
	if(!TestPointer(__gleGetTexImage))
	{
		__gleGetTexImage = gle_CoreStruct.gleVarGetTexImage;
		if(!__gleGetTexImage) bIsLoaded = 0;
	}
	__gleGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)gleIntGetProcAddress("glGetTexParameterfv");
	if(!TestPointer(__gleGetTexParameterfv))
	{
		__gleGetTexParameterfv = gle_CoreStruct.gleVarGetTexParameterfv;
		if(!__gleGetTexParameterfv) bIsLoaded = 0;
	}
	__gleGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)gleIntGetProcAddress("glGetTexParameteriv");
	if(!TestPointer(__gleGetTexParameteriv))
	{
		__gleGetTexParameteriv = gle_CoreStruct.gleVarGetTexParameteriv;
		if(!__gleGetTexParameteriv) bIsLoaded = 0;
	}
	__gleGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)gleIntGetProcAddress("glGetTexLevelParameterfv");
	if(!TestPointer(__gleGetTexLevelParameterfv))
	{
		__gleGetTexLevelParameterfv = gle_CoreStruct.gleVarGetTexLevelParameterfv;
		if(!__gleGetTexLevelParameterfv) bIsLoaded = 0;
	}
	__gleGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)gleIntGetProcAddress("glGetTexLevelParameteriv");
	if(!TestPointer(__gleGetTexLevelParameteriv))
	{
		__gleGetTexLevelParameteriv = gle_CoreStruct.gleVarGetTexLevelParameteriv;
		if(!__gleGetTexLevelParameteriv) bIsLoaded = 0;
	}
	__gleIsEnabled = (PFNGLISENABLEDPROC)gleIntGetProcAddress("glIsEnabled");
	if(!TestPointer(__gleIsEnabled))
	{
		__gleIsEnabled = gle_CoreStruct.gleVarIsEnabled;
		if(!__gleIsEnabled) bIsLoaded = 0;
	}
	__gleDepthRange = (PFNGLDEPTHRANGEPROC)gleIntGetProcAddress("glDepthRange");
	if(!TestPointer(__gleDepthRange))
	{
		__gleDepthRange = gle_CoreStruct.gleVarDepthRange;
		if(!__gleDepthRange) bIsLoaded = 0;
	}
	__gleViewport = (PFNGLVIEWPORTPROC)gleIntGetProcAddress("glViewport");
	if(!TestPointer(__gleViewport))
	{
		__gleViewport = gle_CoreStruct.gleVarViewport;
		if(!__gleViewport) bIsLoaded = 0;
	}
	__gleDrawArrays = (PFNGLDRAWARRAYSPROC)gleIntGetProcAddress("glDrawArrays");
	if(!TestPointer(__gleDrawArrays))
	{
		__gleDrawArrays = gle_CoreStruct.gleVarDrawArrays;
		if(!__gleDrawArrays) bIsLoaded = 0;
	}
	__gleDrawElements = (PFNGLDRAWELEMENTSPROC)gleIntGetProcAddress("glDrawElements");
	if(!TestPointer(__gleDrawElements))
	{
		__gleDrawElements = gle_CoreStruct.gleVarDrawElements;
		if(!__gleDrawElements) bIsLoaded = 0;
	}
	__gleGetPointerv = (PFNGLGETPOINTERVPROC)gleIntGetProcAddress("glGetPointerv");
	if(!TestPointer(__gleGetPointerv))
	{
		__gleGetPointerv = gle_CoreStruct.gleVarGetPointerv;
		if(!__gleGetPointerv) bIsLoaded = 0;
	}
	__glePolygonOffset = (PFNGLPOLYGONOFFSETPROC)gleIntGetProcAddress("glPolygonOffset");
	if(!TestPointer(__glePolygonOffset))
	{
		__glePolygonOffset = gle_CoreStruct.gleVarPolygonOffset;
		if(!__glePolygonOffset) bIsLoaded = 0;
	}
	__gleCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)gleIntGetProcAddress("glCopyTexImage1D");
	if(!TestPointer(__gleCopyTexImage1D))
	{
		__gleCopyTexImage1D = gle_CoreStruct.gleVarCopyTexImage1D;
		if(!__gleCopyTexImage1D) bIsLoaded = 0;
	}
	__gleCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)gleIntGetProcAddress("glCopyTexImage2D");
	if(!TestPointer(__gleCopyTexImage2D))
	{
		__gleCopyTexImage2D = gle_CoreStruct.gleVarCopyTexImage2D;
		if(!__gleCopyTexImage2D) bIsLoaded = 0;
	}
	__gleCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)gleIntGetProcAddress("glCopyTexSubImage1D");
	if(!TestPointer(__gleCopyTexSubImage1D))
	{
		__gleCopyTexSubImage1D = gle_CoreStruct.gleVarCopyTexSubImage1D;
		if(!__gleCopyTexSubImage1D) bIsLoaded = 0;
	}
	__gleCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)gleIntGetProcAddress("glCopyTexSubImage2D");
	if(!TestPointer(__gleCopyTexSubImage2D))
	{
		__gleCopyTexSubImage2D = gle_CoreStruct.gleVarCopyTexSubImage2D;
		if(!__gleCopyTexSubImage2D) bIsLoaded = 0;
	}
	__gleTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)gleIntGetProcAddress("glTexSubImage1D");
	if(!TestPointer(__gleTexSubImage1D))
	{
		__gleTexSubImage1D = gle_CoreStruct.gleVarTexSubImage1D;
		if(!__gleTexSubImage1D) bIsLoaded = 0;
	}
	__gleTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)gleIntGetProcAddress("glTexSubImage2D");
	if(!TestPointer(__gleTexSubImage2D))
	{
		__gleTexSubImage2D = gle_CoreStruct.gleVarTexSubImage2D;
		if(!__gleTexSubImage2D) bIsLoaded = 0;
	}
	__gleBindTexture = (PFNGLBINDTEXTUREPROC)gleIntGetProcAddress("glBindTexture");
	if(!TestPointer(__gleBindTexture))
	{
		__gleBindTexture = gle_CoreStruct.gleVarBindTexture;
		if(!__gleBindTexture) bIsLoaded = 0;
	}
	__gleDeleteTextures = (PFNGLDELETETEXTURESPROC)gleIntGetProcAddress("glDeleteTextures");
	if(!TestPointer(__gleDeleteTextures))
	{
		__gleDeleteTextures = gle_CoreStruct.gleVarDeleteTextures;
		if(!__gleDeleteTextures) bIsLoaded = 0;
	}
	__gleGenTextures = (PFNGLGENTEXTURESPROC)gleIntGetProcAddress("glGenTextures");
	if(!TestPointer(__gleGenTextures))
	{
		__gleGenTextures = gle_CoreStruct.gleVarGenTextures;
		if(!__gleGenTextures) bIsLoaded = 0;
	}
	__gleIsTexture = (PFNGLISTEXTUREPROC)gleIntGetProcAddress("glIsTexture");
	if(!TestPointer(__gleIsTexture))
	{
		__gleIsTexture = gle_CoreStruct.gleVarIsTexture;
		if(!__gleIsTexture) bIsLoaded = 0;
	}
	__gleIndexub = (PFNGLINDEXUBPROC)gleIntGetProcAddress("glIndexub");
	if(!TestPointer(__gleIndexub))
	{
		__gleIndexub = gle_CoreStruct.gleVarIndexub;
		if(!__gleIndexub) bIsLoaded = 0;
	}
	__gleIndexubv = (PFNGLINDEXUBVPROC)gleIntGetProcAddress("glIndexubv");
	if(!TestPointer(__gleIndexubv))
	{
		__gleIndexubv = gle_CoreStruct.gleVarIndexubv;
		if(!__gleIndexubv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_2_Version_3_1()
{
	int bIsLoaded = 1;
	__gleBlendColor = (PFNGLBLENDCOLORPROC)gleIntGetProcAddress("glBlendColor");
	if(!TestPointer(__gleBlendColor))
	{
		__gleBlendColor = gle_CoreStruct.gleVarBlendColor;
		if(!__gleBlendColor) bIsLoaded = 0;
	}
	__gleBlendEquation = (PFNGLBLENDEQUATIONPROC)gleIntGetProcAddress("glBlendEquation");
	if(!TestPointer(__gleBlendEquation))
	{
		__gleBlendEquation = gle_CoreStruct.gleVarBlendEquation;
		if(!__gleBlendEquation) bIsLoaded = 0;
	}
	__gleDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)gleIntGetProcAddress("glDrawRangeElements");
	if(!TestPointer(__gleDrawRangeElements))
	{
		__gleDrawRangeElements = gle_CoreStruct.gleVarDrawRangeElements;
		if(!__gleDrawRangeElements) bIsLoaded = 0;
	}
	__gleTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)gleIntGetProcAddress("glTexSubImage3D");
	if(!TestPointer(__gleTexSubImage3D))
	{
		__gleTexSubImage3D = gle_CoreStruct.gleVarTexSubImage3D;
		if(!__gleTexSubImage3D) bIsLoaded = 0;
	}
	__gleCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)gleIntGetProcAddress("glCopyTexSubImage3D");
	if(!TestPointer(__gleCopyTexSubImage3D))
	{
		__gleCopyTexSubImage3D = gle_CoreStruct.gleVarCopyTexSubImage3D;
		if(!__gleCopyTexSubImage3D) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_3_Version_3_1()
{
	int bIsLoaded = 1;
	__gleActiveTexture = (PFNGLACTIVETEXTUREPROC)gleIntGetProcAddress("glActiveTexture");
	if(!TestPointer(__gleActiveTexture))
	{
		__gleActiveTexture = gle_CoreStruct.gleVarActiveTexture;
		if(!__gleActiveTexture) bIsLoaded = 0;
	}
	__gleSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)gleIntGetProcAddress("glSampleCoverage");
	if(!TestPointer(__gleSampleCoverage))
	{
		__gleSampleCoverage = gle_CoreStruct.gleVarSampleCoverage;
		if(!__gleSampleCoverage) bIsLoaded = 0;
	}
	__gleCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)gleIntGetProcAddress("glCompressedTexImage3D");
	if(!TestPointer(__gleCompressedTexImage3D))
	{
		__gleCompressedTexImage3D = gle_CoreStruct.gleVarCompressedTexImage3D;
		if(!__gleCompressedTexImage3D) bIsLoaded = 0;
	}
	__gleCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)gleIntGetProcAddress("glCompressedTexImage2D");
	if(!TestPointer(__gleCompressedTexImage2D))
	{
		__gleCompressedTexImage2D = gle_CoreStruct.gleVarCompressedTexImage2D;
		if(!__gleCompressedTexImage2D) bIsLoaded = 0;
	}
	__gleCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)gleIntGetProcAddress("glCompressedTexImage1D");
	if(!TestPointer(__gleCompressedTexImage1D))
	{
		__gleCompressedTexImage1D = gle_CoreStruct.gleVarCompressedTexImage1D;
		if(!__gleCompressedTexImage1D) bIsLoaded = 0;
	}
	__gleCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)gleIntGetProcAddress("glCompressedTexSubImage3D");
	if(!TestPointer(__gleCompressedTexSubImage3D))
	{
		__gleCompressedTexSubImage3D = gle_CoreStruct.gleVarCompressedTexSubImage3D;
		if(!__gleCompressedTexSubImage3D) bIsLoaded = 0;
	}
	__gleCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)gleIntGetProcAddress("glCompressedTexSubImage2D");
	if(!TestPointer(__gleCompressedTexSubImage2D))
	{
		__gleCompressedTexSubImage2D = gle_CoreStruct.gleVarCompressedTexSubImage2D;
		if(!__gleCompressedTexSubImage2D) bIsLoaded = 0;
	}
	__gleCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)gleIntGetProcAddress("glCompressedTexSubImage1D");
	if(!TestPointer(__gleCompressedTexSubImage1D))
	{
		__gleCompressedTexSubImage1D = gle_CoreStruct.gleVarCompressedTexSubImage1D;
		if(!__gleCompressedTexSubImage1D) bIsLoaded = 0;
	}
	__gleGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)gleIntGetProcAddress("glGetCompressedTexImage");
	if(!TestPointer(__gleGetCompressedTexImage))
	{
		__gleGetCompressedTexImage = gle_CoreStruct.gleVarGetCompressedTexImage;
		if(!__gleGetCompressedTexImage) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_4_Version_3_1()
{
	int bIsLoaded = 1;
	__gleBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)gleIntGetProcAddress("glBlendFuncSeparate");
	if(!TestPointer(__gleBlendFuncSeparate))
	{
		__gleBlendFuncSeparate = gle_CoreStruct.gleVarBlendFuncSeparate;
		if(!__gleBlendFuncSeparate) bIsLoaded = 0;
	}
	__gleMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)gleIntGetProcAddress("glMultiDrawArrays");
	if(!TestPointer(__gleMultiDrawArrays))
	{
		__gleMultiDrawArrays = gle_CoreStruct.gleVarMultiDrawArrays;
		if(!__gleMultiDrawArrays) bIsLoaded = 0;
	}
	__gleMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)gleIntGetProcAddress("glMultiDrawElements");
	if(!TestPointer(__gleMultiDrawElements))
	{
		__gleMultiDrawElements = gle_CoreStruct.gleVarMultiDrawElements;
		if(!__gleMultiDrawElements) bIsLoaded = 0;
	}
	__glePointParameterf = (PFNGLPOINTPARAMETERFPROC)gleIntGetProcAddress("glPointParameterf");
	if(!TestPointer(__glePointParameterf))
	{
		__glePointParameterf = gle_CoreStruct.gleVarPointParameterf;
		if(!__glePointParameterf) bIsLoaded = 0;
	}
	__glePointParameterfv = (PFNGLPOINTPARAMETERFVPROC)gleIntGetProcAddress("glPointParameterfv");
	if(!TestPointer(__glePointParameterfv))
	{
		__glePointParameterfv = gle_CoreStruct.gleVarPointParameterfv;
		if(!__glePointParameterfv) bIsLoaded = 0;
	}
	__glePointParameteri = (PFNGLPOINTPARAMETERIPROC)gleIntGetProcAddress("glPointParameteri");
	if(!TestPointer(__glePointParameteri))
	{
		__glePointParameteri = gle_CoreStruct.gleVarPointParameteri;
		if(!__glePointParameteri) bIsLoaded = 0;
	}
	__glePointParameteriv = (PFNGLPOINTPARAMETERIVPROC)gleIntGetProcAddress("glPointParameteriv");
	if(!TestPointer(__glePointParameteriv))
	{
		__glePointParameteriv = gle_CoreStruct.gleVarPointParameteriv;
		if(!__glePointParameteriv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_5_Version_3_1()
{
	int bIsLoaded = 1;
	__gleGenQueries = (PFNGLGENQUERIESPROC)gleIntGetProcAddress("glGenQueries");
	if(!TestPointer(__gleGenQueries))
	{
		__gleGenQueries = gle_CoreStruct.gleVarGenQueries;
		if(!__gleGenQueries) bIsLoaded = 0;
	}
	__gleDeleteQueries = (PFNGLDELETEQUERIESPROC)gleIntGetProcAddress("glDeleteQueries");
	if(!TestPointer(__gleDeleteQueries))
	{
		__gleDeleteQueries = gle_CoreStruct.gleVarDeleteQueries;
		if(!__gleDeleteQueries) bIsLoaded = 0;
	}
	__gleIsQuery = (PFNGLISQUERYPROC)gleIntGetProcAddress("glIsQuery");
	if(!TestPointer(__gleIsQuery))
	{
		__gleIsQuery = gle_CoreStruct.gleVarIsQuery;
		if(!__gleIsQuery) bIsLoaded = 0;
	}
	__gleBeginQuery = (PFNGLBEGINQUERYPROC)gleIntGetProcAddress("glBeginQuery");
	if(!TestPointer(__gleBeginQuery))
	{
		__gleBeginQuery = gle_CoreStruct.gleVarBeginQuery;
		if(!__gleBeginQuery) bIsLoaded = 0;
	}
	__gleEndQuery = (PFNGLENDQUERYPROC)gleIntGetProcAddress("glEndQuery");
	if(!TestPointer(__gleEndQuery))
	{
		__gleEndQuery = gle_CoreStruct.gleVarEndQuery;
		if(!__gleEndQuery) bIsLoaded = 0;
	}
	__gleGetQueryiv = (PFNGLGETQUERYIVPROC)gleIntGetProcAddress("glGetQueryiv");
	if(!TestPointer(__gleGetQueryiv))
	{
		__gleGetQueryiv = gle_CoreStruct.gleVarGetQueryiv;
		if(!__gleGetQueryiv) bIsLoaded = 0;
	}
	__gleGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)gleIntGetProcAddress("glGetQueryObjectiv");
	if(!TestPointer(__gleGetQueryObjectiv))
	{
		__gleGetQueryObjectiv = gle_CoreStruct.gleVarGetQueryObjectiv;
		if(!__gleGetQueryObjectiv) bIsLoaded = 0;
	}
	__gleGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)gleIntGetProcAddress("glGetQueryObjectuiv");
	if(!TestPointer(__gleGetQueryObjectuiv))
	{
		__gleGetQueryObjectuiv = gle_CoreStruct.gleVarGetQueryObjectuiv;
		if(!__gleGetQueryObjectuiv) bIsLoaded = 0;
	}
	__gleBindBuffer = (PFNGLBINDBUFFERPROC)gleIntGetProcAddress("glBindBuffer");
	if(!TestPointer(__gleBindBuffer))
	{
		__gleBindBuffer = gle_CoreStruct.gleVarBindBuffer;
		if(!__gleBindBuffer) bIsLoaded = 0;
	}
	__gleDeleteBuffers = (PFNGLDELETEBUFFERSPROC)gleIntGetProcAddress("glDeleteBuffers");
	if(!TestPointer(__gleDeleteBuffers))
	{
		__gleDeleteBuffers = gle_CoreStruct.gleVarDeleteBuffers;
		if(!__gleDeleteBuffers) bIsLoaded = 0;
	}
	__gleGenBuffers = (PFNGLGENBUFFERSPROC)gleIntGetProcAddress("glGenBuffers");
	if(!TestPointer(__gleGenBuffers))
	{
		__gleGenBuffers = gle_CoreStruct.gleVarGenBuffers;
		if(!__gleGenBuffers) bIsLoaded = 0;
	}
	__gleIsBuffer = (PFNGLISBUFFERPROC)gleIntGetProcAddress("glIsBuffer");
	if(!TestPointer(__gleIsBuffer))
	{
		__gleIsBuffer = gle_CoreStruct.gleVarIsBuffer;
		if(!__gleIsBuffer) bIsLoaded = 0;
	}
	__gleBufferData = (PFNGLBUFFERDATAPROC)gleIntGetProcAddress("glBufferData");
	if(!TestPointer(__gleBufferData))
	{
		__gleBufferData = gle_CoreStruct.gleVarBufferData;
		if(!__gleBufferData) bIsLoaded = 0;
	}
	__gleBufferSubData = (PFNGLBUFFERSUBDATAPROC)gleIntGetProcAddress("glBufferSubData");
	if(!TestPointer(__gleBufferSubData))
	{
		__gleBufferSubData = gle_CoreStruct.gleVarBufferSubData;
		if(!__gleBufferSubData) bIsLoaded = 0;
	}
	__gleGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)gleIntGetProcAddress("glGetBufferSubData");
	if(!TestPointer(__gleGetBufferSubData))
	{
		__gleGetBufferSubData = gle_CoreStruct.gleVarGetBufferSubData;
		if(!__gleGetBufferSubData) bIsLoaded = 0;
	}
	__gleMapBuffer = (PFNGLMAPBUFFERPROC)gleIntGetProcAddress("glMapBuffer");
	if(!TestPointer(__gleMapBuffer))
	{
		__gleMapBuffer = gle_CoreStruct.gleVarMapBuffer;
		if(!__gleMapBuffer) bIsLoaded = 0;
	}
	__gleUnmapBuffer = (PFNGLUNMAPBUFFERPROC)gleIntGetProcAddress("glUnmapBuffer");
	if(!TestPointer(__gleUnmapBuffer))
	{
		__gleUnmapBuffer = gle_CoreStruct.gleVarUnmapBuffer;
		if(!__gleUnmapBuffer) bIsLoaded = 0;
	}
	__gleGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)gleIntGetProcAddress("glGetBufferParameteriv");
	if(!TestPointer(__gleGetBufferParameteriv))
	{
		__gleGetBufferParameteriv = gle_CoreStruct.gleVarGetBufferParameteriv;
		if(!__gleGetBufferParameteriv) bIsLoaded = 0;
	}
	__gleGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)gleIntGetProcAddress("glGetBufferPointerv");
	if(!TestPointer(__gleGetBufferPointerv))
	{
		__gleGetBufferPointerv = gle_CoreStruct.gleVarGetBufferPointerv;
		if(!__gleGetBufferPointerv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_2_0_Version_3_1()
{
	int bIsLoaded = 1;
	__gleBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)gleIntGetProcAddress("glBlendEquationSeparate");
	if(!TestPointer(__gleBlendEquationSeparate))
	{
		__gleBlendEquationSeparate = gle_CoreStruct.gleVarBlendEquationSeparate;
		if(!__gleBlendEquationSeparate) bIsLoaded = 0;
	}
	__gleDrawBuffers = (PFNGLDRAWBUFFERSPROC)gleIntGetProcAddress("glDrawBuffers");
	if(!TestPointer(__gleDrawBuffers))
	{
		__gleDrawBuffers = gle_CoreStruct.gleVarDrawBuffers;
		if(!__gleDrawBuffers) bIsLoaded = 0;
	}
	__gleStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)gleIntGetProcAddress("glStencilOpSeparate");
	if(!TestPointer(__gleStencilOpSeparate))
	{
		__gleStencilOpSeparate = gle_CoreStruct.gleVarStencilOpSeparate;
		if(!__gleStencilOpSeparate) bIsLoaded = 0;
	}
	__gleStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)gleIntGetProcAddress("glStencilFuncSeparate");
	if(!TestPointer(__gleStencilFuncSeparate))
	{
		__gleStencilFuncSeparate = gle_CoreStruct.gleVarStencilFuncSeparate;
		if(!__gleStencilFuncSeparate) bIsLoaded = 0;
	}
	__gleStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)gleIntGetProcAddress("glStencilMaskSeparate");
	if(!TestPointer(__gleStencilMaskSeparate))
	{
		__gleStencilMaskSeparate = gle_CoreStruct.gleVarStencilMaskSeparate;
		if(!__gleStencilMaskSeparate) bIsLoaded = 0;
	}
	__gleAttachShader = (PFNGLATTACHSHADERPROC)gleIntGetProcAddress("glAttachShader");
	if(!TestPointer(__gleAttachShader))
	{
		__gleAttachShader = gle_CoreStruct.gleVarAttachShader;
		if(!__gleAttachShader) bIsLoaded = 0;
	}
	__gleBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)gleIntGetProcAddress("glBindAttribLocation");
	if(!TestPointer(__gleBindAttribLocation))
	{
		__gleBindAttribLocation = gle_CoreStruct.gleVarBindAttribLocation;
		if(!__gleBindAttribLocation) bIsLoaded = 0;
	}
	__gleCompileShader = (PFNGLCOMPILESHADERPROC)gleIntGetProcAddress("glCompileShader");
	if(!TestPointer(__gleCompileShader))
	{
		__gleCompileShader = gle_CoreStruct.gleVarCompileShader;
		if(!__gleCompileShader) bIsLoaded = 0;
	}
	__gleCreateProgram = (PFNGLCREATEPROGRAMPROC)gleIntGetProcAddress("glCreateProgram");
	if(!TestPointer(__gleCreateProgram))
	{
		__gleCreateProgram = gle_CoreStruct.gleVarCreateProgram;
		if(!__gleCreateProgram) bIsLoaded = 0;
	}
	__gleCreateShader = (PFNGLCREATESHADERPROC)gleIntGetProcAddress("glCreateShader");
	if(!TestPointer(__gleCreateShader))
	{
		__gleCreateShader = gle_CoreStruct.gleVarCreateShader;
		if(!__gleCreateShader) bIsLoaded = 0;
	}
	__gleDeleteProgram = (PFNGLDELETEPROGRAMPROC)gleIntGetProcAddress("glDeleteProgram");
	if(!TestPointer(__gleDeleteProgram))
	{
		__gleDeleteProgram = gle_CoreStruct.gleVarDeleteProgram;
		if(!__gleDeleteProgram) bIsLoaded = 0;
	}
	__gleDeleteShader = (PFNGLDELETESHADERPROC)gleIntGetProcAddress("glDeleteShader");
	if(!TestPointer(__gleDeleteShader))
	{
		__gleDeleteShader = gle_CoreStruct.gleVarDeleteShader;
		if(!__gleDeleteShader) bIsLoaded = 0;
	}
	__gleDetachShader = (PFNGLDETACHSHADERPROC)gleIntGetProcAddress("glDetachShader");
	if(!TestPointer(__gleDetachShader))
	{
		__gleDetachShader = gle_CoreStruct.gleVarDetachShader;
		if(!__gleDetachShader) bIsLoaded = 0;
	}
	__gleDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)gleIntGetProcAddress("glDisableVertexAttribArray");
	if(!TestPointer(__gleDisableVertexAttribArray))
	{
		__gleDisableVertexAttribArray = gle_CoreStruct.gleVarDisableVertexAttribArray;
		if(!__gleDisableVertexAttribArray) bIsLoaded = 0;
	}
	__gleEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)gleIntGetProcAddress("glEnableVertexAttribArray");
	if(!TestPointer(__gleEnableVertexAttribArray))
	{
		__gleEnableVertexAttribArray = gle_CoreStruct.gleVarEnableVertexAttribArray;
		if(!__gleEnableVertexAttribArray) bIsLoaded = 0;
	}
	__gleGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)gleIntGetProcAddress("glGetActiveAttrib");
	if(!TestPointer(__gleGetActiveAttrib))
	{
		__gleGetActiveAttrib = gle_CoreStruct.gleVarGetActiveAttrib;
		if(!__gleGetActiveAttrib) bIsLoaded = 0;
	}
	__gleGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)gleIntGetProcAddress("glGetActiveUniform");
	if(!TestPointer(__gleGetActiveUniform))
	{
		__gleGetActiveUniform = gle_CoreStruct.gleVarGetActiveUniform;
		if(!__gleGetActiveUniform) bIsLoaded = 0;
	}
	__gleGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)gleIntGetProcAddress("glGetAttachedShaders");
	if(!TestPointer(__gleGetAttachedShaders))
	{
		__gleGetAttachedShaders = gle_CoreStruct.gleVarGetAttachedShaders;
		if(!__gleGetAttachedShaders) bIsLoaded = 0;
	}
	__gleGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)gleIntGetProcAddress("glGetAttribLocation");
	if(!TestPointer(__gleGetAttribLocation))
	{
		__gleGetAttribLocation = gle_CoreStruct.gleVarGetAttribLocation;
		if(!__gleGetAttribLocation) bIsLoaded = 0;
	}
	__gleGetProgramiv = (PFNGLGETPROGRAMIVPROC)gleIntGetProcAddress("glGetProgramiv");
	if(!TestPointer(__gleGetProgramiv))
	{
		__gleGetProgramiv = gle_CoreStruct.gleVarGetProgramiv;
		if(!__gleGetProgramiv) bIsLoaded = 0;
	}
	__gleGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)gleIntGetProcAddress("glGetProgramInfoLog");
	if(!TestPointer(__gleGetProgramInfoLog))
	{
		__gleGetProgramInfoLog = gle_CoreStruct.gleVarGetProgramInfoLog;
		if(!__gleGetProgramInfoLog) bIsLoaded = 0;
	}
	__gleGetShaderiv = (PFNGLGETSHADERIVPROC)gleIntGetProcAddress("glGetShaderiv");
	if(!TestPointer(__gleGetShaderiv))
	{
		__gleGetShaderiv = gle_CoreStruct.gleVarGetShaderiv;
		if(!__gleGetShaderiv) bIsLoaded = 0;
	}
	__gleGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)gleIntGetProcAddress("glGetShaderInfoLog");
	if(!TestPointer(__gleGetShaderInfoLog))
	{
		__gleGetShaderInfoLog = gle_CoreStruct.gleVarGetShaderInfoLog;
		if(!__gleGetShaderInfoLog) bIsLoaded = 0;
	}
	__gleGetShaderSource = (PFNGLGETSHADERSOURCEPROC)gleIntGetProcAddress("glGetShaderSource");
	if(!TestPointer(__gleGetShaderSource))
	{
		__gleGetShaderSource = gle_CoreStruct.gleVarGetShaderSource;
		if(!__gleGetShaderSource) bIsLoaded = 0;
	}
	__gleGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)gleIntGetProcAddress("glGetUniformLocation");
	if(!TestPointer(__gleGetUniformLocation))
	{
		__gleGetUniformLocation = gle_CoreStruct.gleVarGetUniformLocation;
		if(!__gleGetUniformLocation) bIsLoaded = 0;
	}
	__gleGetUniformfv = (PFNGLGETUNIFORMFVPROC)gleIntGetProcAddress("glGetUniformfv");
	if(!TestPointer(__gleGetUniformfv))
	{
		__gleGetUniformfv = gle_CoreStruct.gleVarGetUniformfv;
		if(!__gleGetUniformfv) bIsLoaded = 0;
	}
	__gleGetUniformiv = (PFNGLGETUNIFORMIVPROC)gleIntGetProcAddress("glGetUniformiv");
	if(!TestPointer(__gleGetUniformiv))
	{
		__gleGetUniformiv = gle_CoreStruct.gleVarGetUniformiv;
		if(!__gleGetUniformiv) bIsLoaded = 0;
	}
	__gleGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)gleIntGetProcAddress("glGetVertexAttribdv");
	if(!TestPointer(__gleGetVertexAttribdv))
	{
		__gleGetVertexAttribdv = gle_CoreStruct.gleVarGetVertexAttribdv;
		if(!__gleGetVertexAttribdv) bIsLoaded = 0;
	}
	__gleGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)gleIntGetProcAddress("glGetVertexAttribfv");
	if(!TestPointer(__gleGetVertexAttribfv))
	{
		__gleGetVertexAttribfv = gle_CoreStruct.gleVarGetVertexAttribfv;
		if(!__gleGetVertexAttribfv) bIsLoaded = 0;
	}
	__gleGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)gleIntGetProcAddress("glGetVertexAttribiv");
	if(!TestPointer(__gleGetVertexAttribiv))
	{
		__gleGetVertexAttribiv = gle_CoreStruct.gleVarGetVertexAttribiv;
		if(!__gleGetVertexAttribiv) bIsLoaded = 0;
	}
	__gleGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)gleIntGetProcAddress("glGetVertexAttribPointerv");
	if(!TestPointer(__gleGetVertexAttribPointerv))
	{
		__gleGetVertexAttribPointerv = gle_CoreStruct.gleVarGetVertexAttribPointerv;
		if(!__gleGetVertexAttribPointerv) bIsLoaded = 0;
	}
	__gleIsProgram = (PFNGLISPROGRAMPROC)gleIntGetProcAddress("glIsProgram");
	if(!TestPointer(__gleIsProgram))
	{
		__gleIsProgram = gle_CoreStruct.gleVarIsProgram;
		if(!__gleIsProgram) bIsLoaded = 0;
	}
	__gleIsShader = (PFNGLISSHADERPROC)gleIntGetProcAddress("glIsShader");
	if(!TestPointer(__gleIsShader))
	{
		__gleIsShader = gle_CoreStruct.gleVarIsShader;
		if(!__gleIsShader) bIsLoaded = 0;
	}
	__gleLinkProgram = (PFNGLLINKPROGRAMPROC)gleIntGetProcAddress("glLinkProgram");
	if(!TestPointer(__gleLinkProgram))
	{
		__gleLinkProgram = gle_CoreStruct.gleVarLinkProgram;
		if(!__gleLinkProgram) bIsLoaded = 0;
	}
	__gleShaderSource = (PFNGLSHADERSOURCEPROC)gleIntGetProcAddress("glShaderSource");
	if(!TestPointer(__gleShaderSource))
	{
		__gleShaderSource = gle_CoreStruct.gleVarShaderSource;
		if(!__gleShaderSource) bIsLoaded = 0;
	}
	__gleUseProgram = (PFNGLUSEPROGRAMPROC)gleIntGetProcAddress("glUseProgram");
	if(!TestPointer(__gleUseProgram))
	{
		__gleUseProgram = gle_CoreStruct.gleVarUseProgram;
		if(!__gleUseProgram) bIsLoaded = 0;
	}
	__gleUniform1f = (PFNGLUNIFORM1FPROC)gleIntGetProcAddress("glUniform1f");
	if(!TestPointer(__gleUniform1f))
	{
		__gleUniform1f = gle_CoreStruct.gleVarUniform1f;
		if(!__gleUniform1f) bIsLoaded = 0;
	}
	__gleUniform2f = (PFNGLUNIFORM2FPROC)gleIntGetProcAddress("glUniform2f");
	if(!TestPointer(__gleUniform2f))
	{
		__gleUniform2f = gle_CoreStruct.gleVarUniform2f;
		if(!__gleUniform2f) bIsLoaded = 0;
	}
	__gleUniform3f = (PFNGLUNIFORM3FPROC)gleIntGetProcAddress("glUniform3f");
	if(!TestPointer(__gleUniform3f))
	{
		__gleUniform3f = gle_CoreStruct.gleVarUniform3f;
		if(!__gleUniform3f) bIsLoaded = 0;
	}
	__gleUniform4f = (PFNGLUNIFORM4FPROC)gleIntGetProcAddress("glUniform4f");
	if(!TestPointer(__gleUniform4f))
	{
		__gleUniform4f = gle_CoreStruct.gleVarUniform4f;
		if(!__gleUniform4f) bIsLoaded = 0;
	}
	__gleUniform1i = (PFNGLUNIFORM1IPROC)gleIntGetProcAddress("glUniform1i");
	if(!TestPointer(__gleUniform1i))
	{
		__gleUniform1i = gle_CoreStruct.gleVarUniform1i;
		if(!__gleUniform1i) bIsLoaded = 0;
	}
	__gleUniform2i = (PFNGLUNIFORM2IPROC)gleIntGetProcAddress("glUniform2i");
	if(!TestPointer(__gleUniform2i))
	{
		__gleUniform2i = gle_CoreStruct.gleVarUniform2i;
		if(!__gleUniform2i) bIsLoaded = 0;
	}
	__gleUniform3i = (PFNGLUNIFORM3IPROC)gleIntGetProcAddress("glUniform3i");
	if(!TestPointer(__gleUniform3i))
	{
		__gleUniform3i = gle_CoreStruct.gleVarUniform3i;
		if(!__gleUniform3i) bIsLoaded = 0;
	}
	__gleUniform4i = (PFNGLUNIFORM4IPROC)gleIntGetProcAddress("glUniform4i");
	if(!TestPointer(__gleUniform4i))
	{
		__gleUniform4i = gle_CoreStruct.gleVarUniform4i;
		if(!__gleUniform4i) bIsLoaded = 0;
	}
	__gleUniform1fv = (PFNGLUNIFORM1FVPROC)gleIntGetProcAddress("glUniform1fv");
	if(!TestPointer(__gleUniform1fv))
	{
		__gleUniform1fv = gle_CoreStruct.gleVarUniform1fv;
		if(!__gleUniform1fv) bIsLoaded = 0;
	}
	__gleUniform2fv = (PFNGLUNIFORM2FVPROC)gleIntGetProcAddress("glUniform2fv");
	if(!TestPointer(__gleUniform2fv))
	{
		__gleUniform2fv = gle_CoreStruct.gleVarUniform2fv;
		if(!__gleUniform2fv) bIsLoaded = 0;
	}
	__gleUniform3fv = (PFNGLUNIFORM3FVPROC)gleIntGetProcAddress("glUniform3fv");
	if(!TestPointer(__gleUniform3fv))
	{
		__gleUniform3fv = gle_CoreStruct.gleVarUniform3fv;
		if(!__gleUniform3fv) bIsLoaded = 0;
	}
	__gleUniform4fv = (PFNGLUNIFORM4FVPROC)gleIntGetProcAddress("glUniform4fv");
	if(!TestPointer(__gleUniform4fv))
	{
		__gleUniform4fv = gle_CoreStruct.gleVarUniform4fv;
		if(!__gleUniform4fv) bIsLoaded = 0;
	}
	__gleUniform1iv = (PFNGLUNIFORM1IVPROC)gleIntGetProcAddress("glUniform1iv");
	if(!TestPointer(__gleUniform1iv))
	{
		__gleUniform1iv = gle_CoreStruct.gleVarUniform1iv;
		if(!__gleUniform1iv) bIsLoaded = 0;
	}
	__gleUniform2iv = (PFNGLUNIFORM2IVPROC)gleIntGetProcAddress("glUniform2iv");
	if(!TestPointer(__gleUniform2iv))
	{
		__gleUniform2iv = gle_CoreStruct.gleVarUniform2iv;
		if(!__gleUniform2iv) bIsLoaded = 0;
	}
	__gleUniform3iv = (PFNGLUNIFORM3IVPROC)gleIntGetProcAddress("glUniform3iv");
	if(!TestPointer(__gleUniform3iv))
	{
		__gleUniform3iv = gle_CoreStruct.gleVarUniform3iv;
		if(!__gleUniform3iv) bIsLoaded = 0;
	}
	__gleUniform4iv = (PFNGLUNIFORM4IVPROC)gleIntGetProcAddress("glUniform4iv");
	if(!TestPointer(__gleUniform4iv))
	{
		__gleUniform4iv = gle_CoreStruct.gleVarUniform4iv;
		if(!__gleUniform4iv) bIsLoaded = 0;
	}
	__gleUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)gleIntGetProcAddress("glUniformMatrix2fv");
	if(!TestPointer(__gleUniformMatrix2fv))
	{
		__gleUniformMatrix2fv = gle_CoreStruct.gleVarUniformMatrix2fv;
		if(!__gleUniformMatrix2fv) bIsLoaded = 0;
	}
	__gleUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)gleIntGetProcAddress("glUniformMatrix3fv");
	if(!TestPointer(__gleUniformMatrix3fv))
	{
		__gleUniformMatrix3fv = gle_CoreStruct.gleVarUniformMatrix3fv;
		if(!__gleUniformMatrix3fv) bIsLoaded = 0;
	}
	__gleUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)gleIntGetProcAddress("glUniformMatrix4fv");
	if(!TestPointer(__gleUniformMatrix4fv))
	{
		__gleUniformMatrix4fv = gle_CoreStruct.gleVarUniformMatrix4fv;
		if(!__gleUniformMatrix4fv) bIsLoaded = 0;
	}
	__gleValidateProgram = (PFNGLVALIDATEPROGRAMPROC)gleIntGetProcAddress("glValidateProgram");
	if(!TestPointer(__gleValidateProgram))
	{
		__gleValidateProgram = gle_CoreStruct.gleVarValidateProgram;
		if(!__gleValidateProgram) bIsLoaded = 0;
	}
	__gleVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)gleIntGetProcAddress("glVertexAttribPointer");
	if(!TestPointer(__gleVertexAttribPointer))
	{
		__gleVertexAttribPointer = gle_CoreStruct.gleVarVertexAttribPointer;
		if(!__gleVertexAttribPointer) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_2_1_Version_3_1()
{
	int bIsLoaded = 1;
	__gleUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)gleIntGetProcAddress("glUniformMatrix2x3fv");
	if(!TestPointer(__gleUniformMatrix2x3fv))
	{
		__gleUniformMatrix2x3fv = gle_CoreStruct.gleVarUniformMatrix2x3fv;
		if(!__gleUniformMatrix2x3fv) bIsLoaded = 0;
	}
	__gleUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)gleIntGetProcAddress("glUniformMatrix3x2fv");
	if(!TestPointer(__gleUniformMatrix3x2fv))
	{
		__gleUniformMatrix3x2fv = gle_CoreStruct.gleVarUniformMatrix3x2fv;
		if(!__gleUniformMatrix3x2fv) bIsLoaded = 0;
	}
	__gleUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)gleIntGetProcAddress("glUniformMatrix2x4fv");
	if(!TestPointer(__gleUniformMatrix2x4fv))
	{
		__gleUniformMatrix2x4fv = gle_CoreStruct.gleVarUniformMatrix2x4fv;
		if(!__gleUniformMatrix2x4fv) bIsLoaded = 0;
	}
	__gleUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)gleIntGetProcAddress("glUniformMatrix4x2fv");
	if(!TestPointer(__gleUniformMatrix4x2fv))
	{
		__gleUniformMatrix4x2fv = gle_CoreStruct.gleVarUniformMatrix4x2fv;
		if(!__gleUniformMatrix4x2fv) bIsLoaded = 0;
	}
	__gleUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)gleIntGetProcAddress("glUniformMatrix3x4fv");
	if(!TestPointer(__gleUniformMatrix3x4fv))
	{
		__gleUniformMatrix3x4fv = gle_CoreStruct.gleVarUniformMatrix3x4fv;
		if(!__gleUniformMatrix3x4fv) bIsLoaded = 0;
	}
	__gleUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)gleIntGetProcAddress("glUniformMatrix4x3fv");
	if(!TestPointer(__gleUniformMatrix4x3fv))
	{
		__gleUniformMatrix4x3fv = gle_CoreStruct.gleVarUniformMatrix4x3fv;
		if(!__gleUniformMatrix4x3fv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_3_0_Version_3_1()
{
	int bIsLoaded = 1;
	__gleColorMaski = (PFNGLCOLORMASKIPROC)gleIntGetProcAddress("glColorMaski");
	if(!TestPointer(__gleColorMaski))
	{
		__gleColorMaski = gle_CoreStruct.gleVarColorMaski;
		if(!__gleColorMaski) bIsLoaded = 0;
	}
	__gleGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)gleIntGetProcAddress("glGetBooleani_v");
	if(!TestPointer(__gleGetBooleani_v))
	{
		__gleGetBooleani_v = gle_CoreStruct.gleVarGetBooleani_v;
		if(!__gleGetBooleani_v) bIsLoaded = 0;
	}
	__gleGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)gleIntGetProcAddress("glGetIntegeri_v");
	if(!TestPointer(__gleGetIntegeri_v))
	{
		__gleGetIntegeri_v = gle_CoreStruct.gleVarGetIntegeri_v;
		if(!__gleGetIntegeri_v) bIsLoaded = 0;
	}
	__gleEnablei = (PFNGLENABLEIPROC)gleIntGetProcAddress("glEnablei");
	if(!TestPointer(__gleEnablei))
	{
		__gleEnablei = gle_CoreStruct.gleVarEnablei;
		if(!__gleEnablei) bIsLoaded = 0;
	}
	__gleDisablei = (PFNGLDISABLEIPROC)gleIntGetProcAddress("glDisablei");
	if(!TestPointer(__gleDisablei))
	{
		__gleDisablei = gle_CoreStruct.gleVarDisablei;
		if(!__gleDisablei) bIsLoaded = 0;
	}
	__gleIsEnabledi = (PFNGLISENABLEDIPROC)gleIntGetProcAddress("glIsEnabledi");
	if(!TestPointer(__gleIsEnabledi))
	{
		__gleIsEnabledi = gle_CoreStruct.gleVarIsEnabledi;
		if(!__gleIsEnabledi) bIsLoaded = 0;
	}
	__gleBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glBeginTransformFeedback");
	if(!TestPointer(__gleBeginTransformFeedback))
	{
		__gleBeginTransformFeedback = gle_CoreStruct.gleVarBeginTransformFeedback;
		if(!__gleBeginTransformFeedback) bIsLoaded = 0;
	}
	__gleEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glEndTransformFeedback");
	if(!TestPointer(__gleEndTransformFeedback))
	{
		__gleEndTransformFeedback = gle_CoreStruct.gleVarEndTransformFeedback;
		if(!__gleEndTransformFeedback) bIsLoaded = 0;
	}
	__gleBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)gleIntGetProcAddress("glBindBufferRange");
	if(!TestPointer(__gleBindBufferRange))
	{
		__gleBindBufferRange = gle_CoreStruct.gleVarBindBufferRange;
		if(!__gleBindBufferRange) bIsLoaded = 0;
	}
	__gleBindBufferBase = (PFNGLBINDBUFFERBASEPROC)gleIntGetProcAddress("glBindBufferBase");
	if(!TestPointer(__gleBindBufferBase))
	{
		__gleBindBufferBase = gle_CoreStruct.gleVarBindBufferBase;
		if(!__gleBindBufferBase) bIsLoaded = 0;
	}
	__gleTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)gleIntGetProcAddress("glTransformFeedbackVaryings");
	if(!TestPointer(__gleTransformFeedbackVaryings))
	{
		__gleTransformFeedbackVaryings = gle_CoreStruct.gleVarTransformFeedbackVaryings;
		if(!__gleTransformFeedbackVaryings) bIsLoaded = 0;
	}
	__gleGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)gleIntGetProcAddress("glGetTransformFeedbackVarying");
	if(!TestPointer(__gleGetTransformFeedbackVarying))
	{
		__gleGetTransformFeedbackVarying = gle_CoreStruct.gleVarGetTransformFeedbackVarying;
		if(!__gleGetTransformFeedbackVarying) bIsLoaded = 0;
	}
	__gleClampColor = (PFNGLCLAMPCOLORPROC)gleIntGetProcAddress("glClampColor");
	if(!TestPointer(__gleClampColor))
	{
		__gleClampColor = gle_CoreStruct.gleVarClampColor;
		if(!__gleClampColor) bIsLoaded = 0;
	}
	__gleBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)gleIntGetProcAddress("glBeginConditionalRender");
	if(!TestPointer(__gleBeginConditionalRender))
	{
		__gleBeginConditionalRender = gle_CoreStruct.gleVarBeginConditionalRender;
		if(!__gleBeginConditionalRender) bIsLoaded = 0;
	}
	__gleEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)gleIntGetProcAddress("glEndConditionalRender");
	if(!TestPointer(__gleEndConditionalRender))
	{
		__gleEndConditionalRender = gle_CoreStruct.gleVarEndConditionalRender;
		if(!__gleEndConditionalRender) bIsLoaded = 0;
	}
	__gleVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)gleIntGetProcAddress("glVertexAttribIPointer");
	if(!TestPointer(__gleVertexAttribIPointer))
	{
		__gleVertexAttribIPointer = gle_CoreStruct.gleVarVertexAttribIPointer;
		if(!__gleVertexAttribIPointer) bIsLoaded = 0;
	}
	__gleGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)gleIntGetProcAddress("glGetVertexAttribIiv");
	if(!TestPointer(__gleGetVertexAttribIiv))
	{
		__gleGetVertexAttribIiv = gle_CoreStruct.gleVarGetVertexAttribIiv;
		if(!__gleGetVertexAttribIiv) bIsLoaded = 0;
	}
	__gleGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)gleIntGetProcAddress("glGetVertexAttribIuiv");
	if(!TestPointer(__gleGetVertexAttribIuiv))
	{
		__gleGetVertexAttribIuiv = gle_CoreStruct.gleVarGetVertexAttribIuiv;
		if(!__gleGetVertexAttribIuiv) bIsLoaded = 0;
	}
	__gleGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)gleIntGetProcAddress("glGetUniformuiv");
	if(!TestPointer(__gleGetUniformuiv))
	{
		__gleGetUniformuiv = gle_CoreStruct.gleVarGetUniformuiv;
		if(!__gleGetUniformuiv) bIsLoaded = 0;
	}
	__gleBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)gleIntGetProcAddress("glBindFragDataLocation");
	if(!TestPointer(__gleBindFragDataLocation))
	{
		__gleBindFragDataLocation = gle_CoreStruct.gleVarBindFragDataLocation;
		if(!__gleBindFragDataLocation) bIsLoaded = 0;
	}
	__gleGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)gleIntGetProcAddress("glGetFragDataLocation");
	if(!TestPointer(__gleGetFragDataLocation))
	{
		__gleGetFragDataLocation = gle_CoreStruct.gleVarGetFragDataLocation;
		if(!__gleGetFragDataLocation) bIsLoaded = 0;
	}
	__gleUniform1ui = (PFNGLUNIFORM1UIPROC)gleIntGetProcAddress("glUniform1ui");
	if(!TestPointer(__gleUniform1ui))
	{
		__gleUniform1ui = gle_CoreStruct.gleVarUniform1ui;
		if(!__gleUniform1ui) bIsLoaded = 0;
	}
	__gleUniform2ui = (PFNGLUNIFORM2UIPROC)gleIntGetProcAddress("glUniform2ui");
	if(!TestPointer(__gleUniform2ui))
	{
		__gleUniform2ui = gle_CoreStruct.gleVarUniform2ui;
		if(!__gleUniform2ui) bIsLoaded = 0;
	}
	__gleUniform3ui = (PFNGLUNIFORM3UIPROC)gleIntGetProcAddress("glUniform3ui");
	if(!TestPointer(__gleUniform3ui))
	{
		__gleUniform3ui = gle_CoreStruct.gleVarUniform3ui;
		if(!__gleUniform3ui) bIsLoaded = 0;
	}
	__gleUniform4ui = (PFNGLUNIFORM4UIPROC)gleIntGetProcAddress("glUniform4ui");
	if(!TestPointer(__gleUniform4ui))
	{
		__gleUniform4ui = gle_CoreStruct.gleVarUniform4ui;
		if(!__gleUniform4ui) bIsLoaded = 0;
	}
	__gleUniform1uiv = (PFNGLUNIFORM1UIVPROC)gleIntGetProcAddress("glUniform1uiv");
	if(!TestPointer(__gleUniform1uiv))
	{
		__gleUniform1uiv = gle_CoreStruct.gleVarUniform1uiv;
		if(!__gleUniform1uiv) bIsLoaded = 0;
	}
	__gleUniform2uiv = (PFNGLUNIFORM2UIVPROC)gleIntGetProcAddress("glUniform2uiv");
	if(!TestPointer(__gleUniform2uiv))
	{
		__gleUniform2uiv = gle_CoreStruct.gleVarUniform2uiv;
		if(!__gleUniform2uiv) bIsLoaded = 0;
	}
	__gleUniform3uiv = (PFNGLUNIFORM3UIVPROC)gleIntGetProcAddress("glUniform3uiv");
	if(!TestPointer(__gleUniform3uiv))
	{
		__gleUniform3uiv = gle_CoreStruct.gleVarUniform3uiv;
		if(!__gleUniform3uiv) bIsLoaded = 0;
	}
	__gleUniform4uiv = (PFNGLUNIFORM4UIVPROC)gleIntGetProcAddress("glUniform4uiv");
	if(!TestPointer(__gleUniform4uiv))
	{
		__gleUniform4uiv = gle_CoreStruct.gleVarUniform4uiv;
		if(!__gleUniform4uiv) bIsLoaded = 0;
	}
	__gleTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)gleIntGetProcAddress("glTexParameterIiv");
	if(!TestPointer(__gleTexParameterIiv))
	{
		__gleTexParameterIiv = gle_CoreStruct.gleVarTexParameterIiv;
		if(!__gleTexParameterIiv) bIsLoaded = 0;
	}
	__gleTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)gleIntGetProcAddress("glTexParameterIuiv");
	if(!TestPointer(__gleTexParameterIuiv))
	{
		__gleTexParameterIuiv = gle_CoreStruct.gleVarTexParameterIuiv;
		if(!__gleTexParameterIuiv) bIsLoaded = 0;
	}
	__gleGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)gleIntGetProcAddress("glGetTexParameterIiv");
	if(!TestPointer(__gleGetTexParameterIiv))
	{
		__gleGetTexParameterIiv = gle_CoreStruct.gleVarGetTexParameterIiv;
		if(!__gleGetTexParameterIiv) bIsLoaded = 0;
	}
	__gleGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)gleIntGetProcAddress("glGetTexParameterIuiv");
	if(!TestPointer(__gleGetTexParameterIuiv))
	{
		__gleGetTexParameterIuiv = gle_CoreStruct.gleVarGetTexParameterIuiv;
		if(!__gleGetTexParameterIuiv) bIsLoaded = 0;
	}
	__gleClearBufferiv = (PFNGLCLEARBUFFERIVPROC)gleIntGetProcAddress("glClearBufferiv");
	if(!TestPointer(__gleClearBufferiv))
	{
		__gleClearBufferiv = gle_CoreStruct.gleVarClearBufferiv;
		if(!__gleClearBufferiv) bIsLoaded = 0;
	}
	__gleClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)gleIntGetProcAddress("glClearBufferuiv");
	if(!TestPointer(__gleClearBufferuiv))
	{
		__gleClearBufferuiv = gle_CoreStruct.gleVarClearBufferuiv;
		if(!__gleClearBufferuiv) bIsLoaded = 0;
	}
	__gleClearBufferfv = (PFNGLCLEARBUFFERFVPROC)gleIntGetProcAddress("glClearBufferfv");
	if(!TestPointer(__gleClearBufferfv))
	{
		__gleClearBufferfv = gle_CoreStruct.gleVarClearBufferfv;
		if(!__gleClearBufferfv) bIsLoaded = 0;
	}
	__gleClearBufferfi = (PFNGLCLEARBUFFERFIPROC)gleIntGetProcAddress("glClearBufferfi");
	if(!TestPointer(__gleClearBufferfi))
	{
		__gleClearBufferfi = gle_CoreStruct.gleVarClearBufferfi;
		if(!__gleClearBufferfi) bIsLoaded = 0;
	}
	__gleGetStringi = (PFNGLGETSTRINGIPROC)gleIntGetProcAddress("glGetStringi");
	if(!TestPointer(__gleGetStringi))
	{
		__gleGetStringi = gle_CoreStruct.gleVarGetStringi;
		if(!__gleGetStringi) bIsLoaded = 0;
	}
	__gleIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)gleIntGetProcAddress("glIsRenderbuffer");
	if(!TestPointer(__gleIsRenderbuffer))
	{
		__gleIsRenderbuffer = gle_CoreStruct.gleVarIsRenderbuffer;
		if(!__gleIsRenderbuffer) bIsLoaded = 0;
	}
	__gleBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)gleIntGetProcAddress("glBindRenderbuffer");
	if(!TestPointer(__gleBindRenderbuffer))
	{
		__gleBindRenderbuffer = gle_CoreStruct.gleVarBindRenderbuffer;
		if(!__gleBindRenderbuffer) bIsLoaded = 0;
	}
	__gleDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)gleIntGetProcAddress("glDeleteRenderbuffers");
	if(!TestPointer(__gleDeleteRenderbuffers))
	{
		__gleDeleteRenderbuffers = gle_CoreStruct.gleVarDeleteRenderbuffers;
		if(!__gleDeleteRenderbuffers) bIsLoaded = 0;
	}
	__gleGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)gleIntGetProcAddress("glGenRenderbuffers");
	if(!TestPointer(__gleGenRenderbuffers))
	{
		__gleGenRenderbuffers = gle_CoreStruct.gleVarGenRenderbuffers;
		if(!__gleGenRenderbuffers) bIsLoaded = 0;
	}
	__gleRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)gleIntGetProcAddress("glRenderbufferStorage");
	if(!TestPointer(__gleRenderbufferStorage))
	{
		__gleRenderbufferStorage = gle_CoreStruct.gleVarRenderbufferStorage;
		if(!__gleRenderbufferStorage) bIsLoaded = 0;
	}
	__gleGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)gleIntGetProcAddress("glGetRenderbufferParameteriv");
	if(!TestPointer(__gleGetRenderbufferParameteriv))
	{
		__gleGetRenderbufferParameteriv = gle_CoreStruct.gleVarGetRenderbufferParameteriv;
		if(!__gleGetRenderbufferParameteriv) bIsLoaded = 0;
	}
	__gleIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)gleIntGetProcAddress("glIsFramebuffer");
	if(!TestPointer(__gleIsFramebuffer))
	{
		__gleIsFramebuffer = gle_CoreStruct.gleVarIsFramebuffer;
		if(!__gleIsFramebuffer) bIsLoaded = 0;
	}
	__gleBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)gleIntGetProcAddress("glBindFramebuffer");
	if(!TestPointer(__gleBindFramebuffer))
	{
		__gleBindFramebuffer = gle_CoreStruct.gleVarBindFramebuffer;
		if(!__gleBindFramebuffer) bIsLoaded = 0;
	}
	__gleDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)gleIntGetProcAddress("glDeleteFramebuffers");
	if(!TestPointer(__gleDeleteFramebuffers))
	{
		__gleDeleteFramebuffers = gle_CoreStruct.gleVarDeleteFramebuffers;
		if(!__gleDeleteFramebuffers) bIsLoaded = 0;
	}
	__gleGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)gleIntGetProcAddress("glGenFramebuffers");
	if(!TestPointer(__gleGenFramebuffers))
	{
		__gleGenFramebuffers = gle_CoreStruct.gleVarGenFramebuffers;
		if(!__gleGenFramebuffers) bIsLoaded = 0;
	}
	__gleCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)gleIntGetProcAddress("glCheckFramebufferStatus");
	if(!TestPointer(__gleCheckFramebufferStatus))
	{
		__gleCheckFramebufferStatus = gle_CoreStruct.gleVarCheckFramebufferStatus;
		if(!__gleCheckFramebufferStatus) bIsLoaded = 0;
	}
	__gleFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)gleIntGetProcAddress("glFramebufferTexture1D");
	if(!TestPointer(__gleFramebufferTexture1D))
	{
		__gleFramebufferTexture1D = gle_CoreStruct.gleVarFramebufferTexture1D;
		if(!__gleFramebufferTexture1D) bIsLoaded = 0;
	}
	__gleFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)gleIntGetProcAddress("glFramebufferTexture2D");
	if(!TestPointer(__gleFramebufferTexture2D))
	{
		__gleFramebufferTexture2D = gle_CoreStruct.gleVarFramebufferTexture2D;
		if(!__gleFramebufferTexture2D) bIsLoaded = 0;
	}
	__gleFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)gleIntGetProcAddress("glFramebufferTexture3D");
	if(!TestPointer(__gleFramebufferTexture3D))
	{
		__gleFramebufferTexture3D = gle_CoreStruct.gleVarFramebufferTexture3D;
		if(!__gleFramebufferTexture3D) bIsLoaded = 0;
	}
	__gleFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)gleIntGetProcAddress("glFramebufferRenderbuffer");
	if(!TestPointer(__gleFramebufferRenderbuffer))
	{
		__gleFramebufferRenderbuffer = gle_CoreStruct.gleVarFramebufferRenderbuffer;
		if(!__gleFramebufferRenderbuffer) bIsLoaded = 0;
	}
	__gleGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)gleIntGetProcAddress("glGetFramebufferAttachmentParameteriv");
	if(!TestPointer(__gleGetFramebufferAttachmentParameteriv))
	{
		__gleGetFramebufferAttachmentParameteriv = gle_CoreStruct.gleVarGetFramebufferAttachmentParameteriv;
		if(!__gleGetFramebufferAttachmentParameteriv) bIsLoaded = 0;
	}
	__gleGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)gleIntGetProcAddress("glGenerateMipmap");
	if(!TestPointer(__gleGenerateMipmap))
	{
		__gleGenerateMipmap = gle_CoreStruct.gleVarGenerateMipmap;
		if(!__gleGenerateMipmap) bIsLoaded = 0;
	}
	__gleBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)gleIntGetProcAddress("glBlitFramebuffer");
	if(!TestPointer(__gleBlitFramebuffer))
	{
		__gleBlitFramebuffer = gle_CoreStruct.gleVarBlitFramebuffer;
		if(!__gleBlitFramebuffer) bIsLoaded = 0;
	}
	__gleRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)gleIntGetProcAddress("glRenderbufferStorageMultisample");
	if(!TestPointer(__gleRenderbufferStorageMultisample))
	{
		__gleRenderbufferStorageMultisample = gle_CoreStruct.gleVarRenderbufferStorageMultisample;
		if(!__gleRenderbufferStorageMultisample) bIsLoaded = 0;
	}
	__gleFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)gleIntGetProcAddress("glFramebufferTextureLayer");
	if(!TestPointer(__gleFramebufferTextureLayer))
	{
		__gleFramebufferTextureLayer = gle_CoreStruct.gleVarFramebufferTextureLayer;
		if(!__gleFramebufferTextureLayer) bIsLoaded = 0;
	}
	glext_ARB_framebuffer_object = 1;
	__gleMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)gleIntGetProcAddress("glMapBufferRange");
	if(!TestPointer(__gleMapBufferRange))
	{
		__gleMapBufferRange = gle_CoreStruct.gleVarMapBufferRange;
		if(!__gleMapBufferRange) bIsLoaded = 0;
	}
	__gleFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)gleIntGetProcAddress("glFlushMappedBufferRange");
	if(!TestPointer(__gleFlushMappedBufferRange))
	{
		__gleFlushMappedBufferRange = gle_CoreStruct.gleVarFlushMappedBufferRange;
		if(!__gleFlushMappedBufferRange) bIsLoaded = 0;
	}
	glext_ARB_map_buffer_range = 1;
	__gleBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)gleIntGetProcAddress("glBindVertexArray");
	if(!TestPointer(__gleBindVertexArray))
	{
		__gleBindVertexArray = gle_CoreStruct.gleVarBindVertexArray;
		if(!__gleBindVertexArray) bIsLoaded = 0;
	}
	__gleDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)gleIntGetProcAddress("glDeleteVertexArrays");
	if(!TestPointer(__gleDeleteVertexArrays))
	{
		__gleDeleteVertexArrays = gle_CoreStruct.gleVarDeleteVertexArrays;
		if(!__gleDeleteVertexArrays) bIsLoaded = 0;
	}
	__gleGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)gleIntGetProcAddress("glGenVertexArrays");
	if(!TestPointer(__gleGenVertexArrays))
	{
		__gleGenVertexArrays = gle_CoreStruct.gleVarGenVertexArrays;
		if(!__gleGenVertexArrays) bIsLoaded = 0;
	}
	__gleIsVertexArray = (PFNGLISVERTEXARRAYPROC)gleIntGetProcAddress("glIsVertexArray");
	if(!TestPointer(__gleIsVertexArray))
	{
		__gleIsVertexArray = gle_CoreStruct.gleVarIsVertexArray;
		if(!__gleIsVertexArray) bIsLoaded = 0;
	}
	glext_ARB_vertex_array_object = 1;
	return bIsLoaded;
}

static int gleIntLoadCore_1_1_Base()
{
	int bIsLoaded = gleIntLoadCore_1_1_Version_3_1();
	__gleNewList = (PFNGLNEWLISTPROC)gleIntGetProcAddress("glNewList");
	if(!TestPointer(__gleNewList))
	{
		__gleNewList = gle_CoreStruct.gleVarNewList;
		if(!__gleNewList) bIsLoaded = 0;
	}
	__gleEndList = (PFNGLENDLISTPROC)gleIntGetProcAddress("glEndList");
	if(!TestPointer(__gleEndList))
	{
		__gleEndList = gle_CoreStruct.gleVarEndList;
		if(!__gleEndList) bIsLoaded = 0;
	}
	__gleCallList = (PFNGLCALLLISTPROC)gleIntGetProcAddress("glCallList");
	if(!TestPointer(__gleCallList))
	{
		__gleCallList = gle_CoreStruct.gleVarCallList;
		if(!__gleCallList) bIsLoaded = 0;
	}
	__gleCallLists = (PFNGLCALLLISTSPROC)gleIntGetProcAddress("glCallLists");
	if(!TestPointer(__gleCallLists))
	{
		__gleCallLists = gle_CoreStruct.gleVarCallLists;
		if(!__gleCallLists) bIsLoaded = 0;
	}
	__gleDeleteLists = (PFNGLDELETELISTSPROC)gleIntGetProcAddress("glDeleteLists");
	if(!TestPointer(__gleDeleteLists))
	{
		__gleDeleteLists = gle_CoreStruct.gleVarDeleteLists;
		if(!__gleDeleteLists) bIsLoaded = 0;
	}
	__gleGenLists = (PFNGLGENLISTSPROC)gleIntGetProcAddress("glGenLists");
	if(!TestPointer(__gleGenLists))
	{
		__gleGenLists = gle_CoreStruct.gleVarGenLists;
		if(!__gleGenLists) bIsLoaded = 0;
	}
	__gleListBase = (PFNGLLISTBASEPROC)gleIntGetProcAddress("glListBase");
	if(!TestPointer(__gleListBase))
	{
		__gleListBase = gle_CoreStruct.gleVarListBase;
		if(!__gleListBase) bIsLoaded = 0;
	}
	__gleBegin = (PFNGLBEGINPROC)gleIntGetProcAddress("glBegin");
	if(!TestPointer(__gleBegin))
	{
		__gleBegin = gle_CoreStruct.gleVarBegin;
		if(!__gleBegin) bIsLoaded = 0;
	}
	__gleBitmap = (PFNGLBITMAPPROC)gleIntGetProcAddress("glBitmap");
	if(!TestPointer(__gleBitmap))
	{
		__gleBitmap = gle_CoreStruct.gleVarBitmap;
		if(!__gleBitmap) bIsLoaded = 0;
	}
	__gleColor3b = (PFNGLCOLOR3BPROC)gleIntGetProcAddress("glColor3b");
	if(!TestPointer(__gleColor3b))
	{
		__gleColor3b = gle_CoreStruct.gleVarColor3b;
		if(!__gleColor3b) bIsLoaded = 0;
	}
	__gleColor3bv = (PFNGLCOLOR3BVPROC)gleIntGetProcAddress("glColor3bv");
	if(!TestPointer(__gleColor3bv))
	{
		__gleColor3bv = gle_CoreStruct.gleVarColor3bv;
		if(!__gleColor3bv) bIsLoaded = 0;
	}
	__gleColor3d = (PFNGLCOLOR3DPROC)gleIntGetProcAddress("glColor3d");
	if(!TestPointer(__gleColor3d))
	{
		__gleColor3d = gle_CoreStruct.gleVarColor3d;
		if(!__gleColor3d) bIsLoaded = 0;
	}
	__gleColor3dv = (PFNGLCOLOR3DVPROC)gleIntGetProcAddress("glColor3dv");
	if(!TestPointer(__gleColor3dv))
	{
		__gleColor3dv = gle_CoreStruct.gleVarColor3dv;
		if(!__gleColor3dv) bIsLoaded = 0;
	}
	__gleColor3f = (PFNGLCOLOR3FPROC)gleIntGetProcAddress("glColor3f");
	if(!TestPointer(__gleColor3f))
	{
		__gleColor3f = gle_CoreStruct.gleVarColor3f;
		if(!__gleColor3f) bIsLoaded = 0;
	}
	__gleColor3fv = (PFNGLCOLOR3FVPROC)gleIntGetProcAddress("glColor3fv");
	if(!TestPointer(__gleColor3fv))
	{
		__gleColor3fv = gle_CoreStruct.gleVarColor3fv;
		if(!__gleColor3fv) bIsLoaded = 0;
	}
	__gleColor3i = (PFNGLCOLOR3IPROC)gleIntGetProcAddress("glColor3i");
	if(!TestPointer(__gleColor3i))
	{
		__gleColor3i = gle_CoreStruct.gleVarColor3i;
		if(!__gleColor3i) bIsLoaded = 0;
	}
	__gleColor3iv = (PFNGLCOLOR3IVPROC)gleIntGetProcAddress("glColor3iv");
	if(!TestPointer(__gleColor3iv))
	{
		__gleColor3iv = gle_CoreStruct.gleVarColor3iv;
		if(!__gleColor3iv) bIsLoaded = 0;
	}
	__gleColor3s = (PFNGLCOLOR3SPROC)gleIntGetProcAddress("glColor3s");
	if(!TestPointer(__gleColor3s))
	{
		__gleColor3s = gle_CoreStruct.gleVarColor3s;
		if(!__gleColor3s) bIsLoaded = 0;
	}
	__gleColor3sv = (PFNGLCOLOR3SVPROC)gleIntGetProcAddress("glColor3sv");
	if(!TestPointer(__gleColor3sv))
	{
		__gleColor3sv = gle_CoreStruct.gleVarColor3sv;
		if(!__gleColor3sv) bIsLoaded = 0;
	}
	__gleColor3ub = (PFNGLCOLOR3UBPROC)gleIntGetProcAddress("glColor3ub");
	if(!TestPointer(__gleColor3ub))
	{
		__gleColor3ub = gle_CoreStruct.gleVarColor3ub;
		if(!__gleColor3ub) bIsLoaded = 0;
	}
	__gleColor3ubv = (PFNGLCOLOR3UBVPROC)gleIntGetProcAddress("glColor3ubv");
	if(!TestPointer(__gleColor3ubv))
	{
		__gleColor3ubv = gle_CoreStruct.gleVarColor3ubv;
		if(!__gleColor3ubv) bIsLoaded = 0;
	}
	__gleColor3ui = (PFNGLCOLOR3UIPROC)gleIntGetProcAddress("glColor3ui");
	if(!TestPointer(__gleColor3ui))
	{
		__gleColor3ui = gle_CoreStruct.gleVarColor3ui;
		if(!__gleColor3ui) bIsLoaded = 0;
	}
	__gleColor3uiv = (PFNGLCOLOR3UIVPROC)gleIntGetProcAddress("glColor3uiv");
	if(!TestPointer(__gleColor3uiv))
	{
		__gleColor3uiv = gle_CoreStruct.gleVarColor3uiv;
		if(!__gleColor3uiv) bIsLoaded = 0;
	}
	__gleColor3us = (PFNGLCOLOR3USPROC)gleIntGetProcAddress("glColor3us");
	if(!TestPointer(__gleColor3us))
	{
		__gleColor3us = gle_CoreStruct.gleVarColor3us;
		if(!__gleColor3us) bIsLoaded = 0;
	}
	__gleColor3usv = (PFNGLCOLOR3USVPROC)gleIntGetProcAddress("glColor3usv");
	if(!TestPointer(__gleColor3usv))
	{
		__gleColor3usv = gle_CoreStruct.gleVarColor3usv;
		if(!__gleColor3usv) bIsLoaded = 0;
	}
	__gleColor4b = (PFNGLCOLOR4BPROC)gleIntGetProcAddress("glColor4b");
	if(!TestPointer(__gleColor4b))
	{
		__gleColor4b = gle_CoreStruct.gleVarColor4b;
		if(!__gleColor4b) bIsLoaded = 0;
	}
	__gleColor4bv = (PFNGLCOLOR4BVPROC)gleIntGetProcAddress("glColor4bv");
	if(!TestPointer(__gleColor4bv))
	{
		__gleColor4bv = gle_CoreStruct.gleVarColor4bv;
		if(!__gleColor4bv) bIsLoaded = 0;
	}
	__gleColor4d = (PFNGLCOLOR4DPROC)gleIntGetProcAddress("glColor4d");
	if(!TestPointer(__gleColor4d))
	{
		__gleColor4d = gle_CoreStruct.gleVarColor4d;
		if(!__gleColor4d) bIsLoaded = 0;
	}
	__gleColor4dv = (PFNGLCOLOR4DVPROC)gleIntGetProcAddress("glColor4dv");
	if(!TestPointer(__gleColor4dv))
	{
		__gleColor4dv = gle_CoreStruct.gleVarColor4dv;
		if(!__gleColor4dv) bIsLoaded = 0;
	}
	__gleColor4f = (PFNGLCOLOR4FPROC)gleIntGetProcAddress("glColor4f");
	if(!TestPointer(__gleColor4f))
	{
		__gleColor4f = gle_CoreStruct.gleVarColor4f;
		if(!__gleColor4f) bIsLoaded = 0;
	}
	__gleColor4fv = (PFNGLCOLOR4FVPROC)gleIntGetProcAddress("glColor4fv");
	if(!TestPointer(__gleColor4fv))
	{
		__gleColor4fv = gle_CoreStruct.gleVarColor4fv;
		if(!__gleColor4fv) bIsLoaded = 0;
	}
	__gleColor4i = (PFNGLCOLOR4IPROC)gleIntGetProcAddress("glColor4i");
	if(!TestPointer(__gleColor4i))
	{
		__gleColor4i = gle_CoreStruct.gleVarColor4i;
		if(!__gleColor4i) bIsLoaded = 0;
	}
	__gleColor4iv = (PFNGLCOLOR4IVPROC)gleIntGetProcAddress("glColor4iv");
	if(!TestPointer(__gleColor4iv))
	{
		__gleColor4iv = gle_CoreStruct.gleVarColor4iv;
		if(!__gleColor4iv) bIsLoaded = 0;
	}
	__gleColor4s = (PFNGLCOLOR4SPROC)gleIntGetProcAddress("glColor4s");
	if(!TestPointer(__gleColor4s))
	{
		__gleColor4s = gle_CoreStruct.gleVarColor4s;
		if(!__gleColor4s) bIsLoaded = 0;
	}
	__gleColor4sv = (PFNGLCOLOR4SVPROC)gleIntGetProcAddress("glColor4sv");
	if(!TestPointer(__gleColor4sv))
	{
		__gleColor4sv = gle_CoreStruct.gleVarColor4sv;
		if(!__gleColor4sv) bIsLoaded = 0;
	}
	__gleColor4ub = (PFNGLCOLOR4UBPROC)gleIntGetProcAddress("glColor4ub");
	if(!TestPointer(__gleColor4ub))
	{
		__gleColor4ub = gle_CoreStruct.gleVarColor4ub;
		if(!__gleColor4ub) bIsLoaded = 0;
	}
	__gleColor4ubv = (PFNGLCOLOR4UBVPROC)gleIntGetProcAddress("glColor4ubv");
	if(!TestPointer(__gleColor4ubv))
	{
		__gleColor4ubv = gle_CoreStruct.gleVarColor4ubv;
		if(!__gleColor4ubv) bIsLoaded = 0;
	}
	__gleColor4ui = (PFNGLCOLOR4UIPROC)gleIntGetProcAddress("glColor4ui");
	if(!TestPointer(__gleColor4ui))
	{
		__gleColor4ui = gle_CoreStruct.gleVarColor4ui;
		if(!__gleColor4ui) bIsLoaded = 0;
	}
	__gleColor4uiv = (PFNGLCOLOR4UIVPROC)gleIntGetProcAddress("glColor4uiv");
	if(!TestPointer(__gleColor4uiv))
	{
		__gleColor4uiv = gle_CoreStruct.gleVarColor4uiv;
		if(!__gleColor4uiv) bIsLoaded = 0;
	}
	__gleColor4us = (PFNGLCOLOR4USPROC)gleIntGetProcAddress("glColor4us");
	if(!TestPointer(__gleColor4us))
	{
		__gleColor4us = gle_CoreStruct.gleVarColor4us;
		if(!__gleColor4us) bIsLoaded = 0;
	}
	__gleColor4usv = (PFNGLCOLOR4USVPROC)gleIntGetProcAddress("glColor4usv");
	if(!TestPointer(__gleColor4usv))
	{
		__gleColor4usv = gle_CoreStruct.gleVarColor4usv;
		if(!__gleColor4usv) bIsLoaded = 0;
	}
	__gleEdgeFlag = (PFNGLEDGEFLAGPROC)gleIntGetProcAddress("glEdgeFlag");
	if(!TestPointer(__gleEdgeFlag))
	{
		__gleEdgeFlag = gle_CoreStruct.gleVarEdgeFlag;
		if(!__gleEdgeFlag) bIsLoaded = 0;
	}
	__gleEdgeFlagv = (PFNGLEDGEFLAGVPROC)gleIntGetProcAddress("glEdgeFlagv");
	if(!TestPointer(__gleEdgeFlagv))
	{
		__gleEdgeFlagv = gle_CoreStruct.gleVarEdgeFlagv;
		if(!__gleEdgeFlagv) bIsLoaded = 0;
	}
	__gleEnd = (PFNGLENDPROC)gleIntGetProcAddress("glEnd");
	if(!TestPointer(__gleEnd))
	{
		__gleEnd = gle_CoreStruct.gleVarEnd;
		if(!__gleEnd) bIsLoaded = 0;
	}
	__gleIndexd = (PFNGLINDEXDPROC)gleIntGetProcAddress("glIndexd");
	if(!TestPointer(__gleIndexd))
	{
		__gleIndexd = gle_CoreStruct.gleVarIndexd;
		if(!__gleIndexd) bIsLoaded = 0;
	}
	__gleIndexdv = (PFNGLINDEXDVPROC)gleIntGetProcAddress("glIndexdv");
	if(!TestPointer(__gleIndexdv))
	{
		__gleIndexdv = gle_CoreStruct.gleVarIndexdv;
		if(!__gleIndexdv) bIsLoaded = 0;
	}
	__gleIndexf = (PFNGLINDEXFPROC)gleIntGetProcAddress("glIndexf");
	if(!TestPointer(__gleIndexf))
	{
		__gleIndexf = gle_CoreStruct.gleVarIndexf;
		if(!__gleIndexf) bIsLoaded = 0;
	}
	__gleIndexfv = (PFNGLINDEXFVPROC)gleIntGetProcAddress("glIndexfv");
	if(!TestPointer(__gleIndexfv))
	{
		__gleIndexfv = gle_CoreStruct.gleVarIndexfv;
		if(!__gleIndexfv) bIsLoaded = 0;
	}
	__gleIndexi = (PFNGLINDEXIPROC)gleIntGetProcAddress("glIndexi");
	if(!TestPointer(__gleIndexi))
	{
		__gleIndexi = gle_CoreStruct.gleVarIndexi;
		if(!__gleIndexi) bIsLoaded = 0;
	}
	__gleIndexiv = (PFNGLINDEXIVPROC)gleIntGetProcAddress("glIndexiv");
	if(!TestPointer(__gleIndexiv))
	{
		__gleIndexiv = gle_CoreStruct.gleVarIndexiv;
		if(!__gleIndexiv) bIsLoaded = 0;
	}
	__gleIndexs = (PFNGLINDEXSPROC)gleIntGetProcAddress("glIndexs");
	if(!TestPointer(__gleIndexs))
	{
		__gleIndexs = gle_CoreStruct.gleVarIndexs;
		if(!__gleIndexs) bIsLoaded = 0;
	}
	__gleIndexsv = (PFNGLINDEXSVPROC)gleIntGetProcAddress("glIndexsv");
	if(!TestPointer(__gleIndexsv))
	{
		__gleIndexsv = gle_CoreStruct.gleVarIndexsv;
		if(!__gleIndexsv) bIsLoaded = 0;
	}
	__gleNormal3b = (PFNGLNORMAL3BPROC)gleIntGetProcAddress("glNormal3b");
	if(!TestPointer(__gleNormal3b))
	{
		__gleNormal3b = gle_CoreStruct.gleVarNormal3b;
		if(!__gleNormal3b) bIsLoaded = 0;
	}
	__gleNormal3bv = (PFNGLNORMAL3BVPROC)gleIntGetProcAddress("glNormal3bv");
	if(!TestPointer(__gleNormal3bv))
	{
		__gleNormal3bv = gle_CoreStruct.gleVarNormal3bv;
		if(!__gleNormal3bv) bIsLoaded = 0;
	}
	__gleNormal3d = (PFNGLNORMAL3DPROC)gleIntGetProcAddress("glNormal3d");
	if(!TestPointer(__gleNormal3d))
	{
		__gleNormal3d = gle_CoreStruct.gleVarNormal3d;
		if(!__gleNormal3d) bIsLoaded = 0;
	}
	__gleNormal3dv = (PFNGLNORMAL3DVPROC)gleIntGetProcAddress("glNormal3dv");
	if(!TestPointer(__gleNormal3dv))
	{
		__gleNormal3dv = gle_CoreStruct.gleVarNormal3dv;
		if(!__gleNormal3dv) bIsLoaded = 0;
	}
	__gleNormal3f = (PFNGLNORMAL3FPROC)gleIntGetProcAddress("glNormal3f");
	if(!TestPointer(__gleNormal3f))
	{
		__gleNormal3f = gle_CoreStruct.gleVarNormal3f;
		if(!__gleNormal3f) bIsLoaded = 0;
	}
	__gleNormal3fv = (PFNGLNORMAL3FVPROC)gleIntGetProcAddress("glNormal3fv");
	if(!TestPointer(__gleNormal3fv))
	{
		__gleNormal3fv = gle_CoreStruct.gleVarNormal3fv;
		if(!__gleNormal3fv) bIsLoaded = 0;
	}
	__gleNormal3i = (PFNGLNORMAL3IPROC)gleIntGetProcAddress("glNormal3i");
	if(!TestPointer(__gleNormal3i))
	{
		__gleNormal3i = gle_CoreStruct.gleVarNormal3i;
		if(!__gleNormal3i) bIsLoaded = 0;
	}
	__gleNormal3iv = (PFNGLNORMAL3IVPROC)gleIntGetProcAddress("glNormal3iv");
	if(!TestPointer(__gleNormal3iv))
	{
		__gleNormal3iv = gle_CoreStruct.gleVarNormal3iv;
		if(!__gleNormal3iv) bIsLoaded = 0;
	}
	__gleNormal3s = (PFNGLNORMAL3SPROC)gleIntGetProcAddress("glNormal3s");
	if(!TestPointer(__gleNormal3s))
	{
		__gleNormal3s = gle_CoreStruct.gleVarNormal3s;
		if(!__gleNormal3s) bIsLoaded = 0;
	}
	__gleNormal3sv = (PFNGLNORMAL3SVPROC)gleIntGetProcAddress("glNormal3sv");
	if(!TestPointer(__gleNormal3sv))
	{
		__gleNormal3sv = gle_CoreStruct.gleVarNormal3sv;
		if(!__gleNormal3sv) bIsLoaded = 0;
	}
	__gleRasterPos2d = (PFNGLRASTERPOS2DPROC)gleIntGetProcAddress("glRasterPos2d");
	if(!TestPointer(__gleRasterPos2d))
	{
		__gleRasterPos2d = gle_CoreStruct.gleVarRasterPos2d;
		if(!__gleRasterPos2d) bIsLoaded = 0;
	}
	__gleRasterPos2dv = (PFNGLRASTERPOS2DVPROC)gleIntGetProcAddress("glRasterPos2dv");
	if(!TestPointer(__gleRasterPos2dv))
	{
		__gleRasterPos2dv = gle_CoreStruct.gleVarRasterPos2dv;
		if(!__gleRasterPos2dv) bIsLoaded = 0;
	}
	__gleRasterPos2f = (PFNGLRASTERPOS2FPROC)gleIntGetProcAddress("glRasterPos2f");
	if(!TestPointer(__gleRasterPos2f))
	{
		__gleRasterPos2f = gle_CoreStruct.gleVarRasterPos2f;
		if(!__gleRasterPos2f) bIsLoaded = 0;
	}
	__gleRasterPos2fv = (PFNGLRASTERPOS2FVPROC)gleIntGetProcAddress("glRasterPos2fv");
	if(!TestPointer(__gleRasterPos2fv))
	{
		__gleRasterPos2fv = gle_CoreStruct.gleVarRasterPos2fv;
		if(!__gleRasterPos2fv) bIsLoaded = 0;
	}
	__gleRasterPos2i = (PFNGLRASTERPOS2IPROC)gleIntGetProcAddress("glRasterPos2i");
	if(!TestPointer(__gleRasterPos2i))
	{
		__gleRasterPos2i = gle_CoreStruct.gleVarRasterPos2i;
		if(!__gleRasterPos2i) bIsLoaded = 0;
	}
	__gleRasterPos2iv = (PFNGLRASTERPOS2IVPROC)gleIntGetProcAddress("glRasterPos2iv");
	if(!TestPointer(__gleRasterPos2iv))
	{
		__gleRasterPos2iv = gle_CoreStruct.gleVarRasterPos2iv;
		if(!__gleRasterPos2iv) bIsLoaded = 0;
	}
	__gleRasterPos2s = (PFNGLRASTERPOS2SPROC)gleIntGetProcAddress("glRasterPos2s");
	if(!TestPointer(__gleRasterPos2s))
	{
		__gleRasterPos2s = gle_CoreStruct.gleVarRasterPos2s;
		if(!__gleRasterPos2s) bIsLoaded = 0;
	}
	__gleRasterPos2sv = (PFNGLRASTERPOS2SVPROC)gleIntGetProcAddress("glRasterPos2sv");
	if(!TestPointer(__gleRasterPos2sv))
	{
		__gleRasterPos2sv = gle_CoreStruct.gleVarRasterPos2sv;
		if(!__gleRasterPos2sv) bIsLoaded = 0;
	}
	__gleRasterPos3d = (PFNGLRASTERPOS3DPROC)gleIntGetProcAddress("glRasterPos3d");
	if(!TestPointer(__gleRasterPos3d))
	{
		__gleRasterPos3d = gle_CoreStruct.gleVarRasterPos3d;
		if(!__gleRasterPos3d) bIsLoaded = 0;
	}
	__gleRasterPos3dv = (PFNGLRASTERPOS3DVPROC)gleIntGetProcAddress("glRasterPos3dv");
	if(!TestPointer(__gleRasterPos3dv))
	{
		__gleRasterPos3dv = gle_CoreStruct.gleVarRasterPos3dv;
		if(!__gleRasterPos3dv) bIsLoaded = 0;
	}
	__gleRasterPos3f = (PFNGLRASTERPOS3FPROC)gleIntGetProcAddress("glRasterPos3f");
	if(!TestPointer(__gleRasterPos3f))
	{
		__gleRasterPos3f = gle_CoreStruct.gleVarRasterPos3f;
		if(!__gleRasterPos3f) bIsLoaded = 0;
	}
	__gleRasterPos3fv = (PFNGLRASTERPOS3FVPROC)gleIntGetProcAddress("glRasterPos3fv");
	if(!TestPointer(__gleRasterPos3fv))
	{
		__gleRasterPos3fv = gle_CoreStruct.gleVarRasterPos3fv;
		if(!__gleRasterPos3fv) bIsLoaded = 0;
	}
	__gleRasterPos3i = (PFNGLRASTERPOS3IPROC)gleIntGetProcAddress("glRasterPos3i");
	if(!TestPointer(__gleRasterPos3i))
	{
		__gleRasterPos3i = gle_CoreStruct.gleVarRasterPos3i;
		if(!__gleRasterPos3i) bIsLoaded = 0;
	}
	__gleRasterPos3iv = (PFNGLRASTERPOS3IVPROC)gleIntGetProcAddress("glRasterPos3iv");
	if(!TestPointer(__gleRasterPos3iv))
	{
		__gleRasterPos3iv = gle_CoreStruct.gleVarRasterPos3iv;
		if(!__gleRasterPos3iv) bIsLoaded = 0;
	}
	__gleRasterPos3s = (PFNGLRASTERPOS3SPROC)gleIntGetProcAddress("glRasterPos3s");
	if(!TestPointer(__gleRasterPos3s))
	{
		__gleRasterPos3s = gle_CoreStruct.gleVarRasterPos3s;
		if(!__gleRasterPos3s) bIsLoaded = 0;
	}
	__gleRasterPos3sv = (PFNGLRASTERPOS3SVPROC)gleIntGetProcAddress("glRasterPos3sv");
	if(!TestPointer(__gleRasterPos3sv))
	{
		__gleRasterPos3sv = gle_CoreStruct.gleVarRasterPos3sv;
		if(!__gleRasterPos3sv) bIsLoaded = 0;
	}
	__gleRasterPos4d = (PFNGLRASTERPOS4DPROC)gleIntGetProcAddress("glRasterPos4d");
	if(!TestPointer(__gleRasterPos4d))
	{
		__gleRasterPos4d = gle_CoreStruct.gleVarRasterPos4d;
		if(!__gleRasterPos4d) bIsLoaded = 0;
	}
	__gleRasterPos4dv = (PFNGLRASTERPOS4DVPROC)gleIntGetProcAddress("glRasterPos4dv");
	if(!TestPointer(__gleRasterPos4dv))
	{
		__gleRasterPos4dv = gle_CoreStruct.gleVarRasterPos4dv;
		if(!__gleRasterPos4dv) bIsLoaded = 0;
	}
	__gleRasterPos4f = (PFNGLRASTERPOS4FPROC)gleIntGetProcAddress("glRasterPos4f");
	if(!TestPointer(__gleRasterPos4f))
	{
		__gleRasterPos4f = gle_CoreStruct.gleVarRasterPos4f;
		if(!__gleRasterPos4f) bIsLoaded = 0;
	}
	__gleRasterPos4fv = (PFNGLRASTERPOS4FVPROC)gleIntGetProcAddress("glRasterPos4fv");
	if(!TestPointer(__gleRasterPos4fv))
	{
		__gleRasterPos4fv = gle_CoreStruct.gleVarRasterPos4fv;
		if(!__gleRasterPos4fv) bIsLoaded = 0;
	}
	__gleRasterPos4i = (PFNGLRASTERPOS4IPROC)gleIntGetProcAddress("glRasterPos4i");
	if(!TestPointer(__gleRasterPos4i))
	{
		__gleRasterPos4i = gle_CoreStruct.gleVarRasterPos4i;
		if(!__gleRasterPos4i) bIsLoaded = 0;
	}
	__gleRasterPos4iv = (PFNGLRASTERPOS4IVPROC)gleIntGetProcAddress("glRasterPos4iv");
	if(!TestPointer(__gleRasterPos4iv))
	{
		__gleRasterPos4iv = gle_CoreStruct.gleVarRasterPos4iv;
		if(!__gleRasterPos4iv) bIsLoaded = 0;
	}
	__gleRasterPos4s = (PFNGLRASTERPOS4SPROC)gleIntGetProcAddress("glRasterPos4s");
	if(!TestPointer(__gleRasterPos4s))
	{
		__gleRasterPos4s = gle_CoreStruct.gleVarRasterPos4s;
		if(!__gleRasterPos4s) bIsLoaded = 0;
	}
	__gleRasterPos4sv = (PFNGLRASTERPOS4SVPROC)gleIntGetProcAddress("glRasterPos4sv");
	if(!TestPointer(__gleRasterPos4sv))
	{
		__gleRasterPos4sv = gle_CoreStruct.gleVarRasterPos4sv;
		if(!__gleRasterPos4sv) bIsLoaded = 0;
	}
	__gleRectd = (PFNGLRECTDPROC)gleIntGetProcAddress("glRectd");
	if(!TestPointer(__gleRectd))
	{
		__gleRectd = gle_CoreStruct.gleVarRectd;
		if(!__gleRectd) bIsLoaded = 0;
	}
	__gleRectdv = (PFNGLRECTDVPROC)gleIntGetProcAddress("glRectdv");
	if(!TestPointer(__gleRectdv))
	{
		__gleRectdv = gle_CoreStruct.gleVarRectdv;
		if(!__gleRectdv) bIsLoaded = 0;
	}
	__gleRectf = (PFNGLRECTFPROC)gleIntGetProcAddress("glRectf");
	if(!TestPointer(__gleRectf))
	{
		__gleRectf = gle_CoreStruct.gleVarRectf;
		if(!__gleRectf) bIsLoaded = 0;
	}
	__gleRectfv = (PFNGLRECTFVPROC)gleIntGetProcAddress("glRectfv");
	if(!TestPointer(__gleRectfv))
	{
		__gleRectfv = gle_CoreStruct.gleVarRectfv;
		if(!__gleRectfv) bIsLoaded = 0;
	}
	__gleRecti = (PFNGLRECTIPROC)gleIntGetProcAddress("glRecti");
	if(!TestPointer(__gleRecti))
	{
		__gleRecti = gle_CoreStruct.gleVarRecti;
		if(!__gleRecti) bIsLoaded = 0;
	}
	__gleRectiv = (PFNGLRECTIVPROC)gleIntGetProcAddress("glRectiv");
	if(!TestPointer(__gleRectiv))
	{
		__gleRectiv = gle_CoreStruct.gleVarRectiv;
		if(!__gleRectiv) bIsLoaded = 0;
	}
	__gleRects = (PFNGLRECTSPROC)gleIntGetProcAddress("glRects");
	if(!TestPointer(__gleRects))
	{
		__gleRects = gle_CoreStruct.gleVarRects;
		if(!__gleRects) bIsLoaded = 0;
	}
	__gleRectsv = (PFNGLRECTSVPROC)gleIntGetProcAddress("glRectsv");
	if(!TestPointer(__gleRectsv))
	{
		__gleRectsv = gle_CoreStruct.gleVarRectsv;
		if(!__gleRectsv) bIsLoaded = 0;
	}
	__gleTexCoord1d = (PFNGLTEXCOORD1DPROC)gleIntGetProcAddress("glTexCoord1d");
	if(!TestPointer(__gleTexCoord1d))
	{
		__gleTexCoord1d = gle_CoreStruct.gleVarTexCoord1d;
		if(!__gleTexCoord1d) bIsLoaded = 0;
	}
	__gleTexCoord1dv = (PFNGLTEXCOORD1DVPROC)gleIntGetProcAddress("glTexCoord1dv");
	if(!TestPointer(__gleTexCoord1dv))
	{
		__gleTexCoord1dv = gle_CoreStruct.gleVarTexCoord1dv;
		if(!__gleTexCoord1dv) bIsLoaded = 0;
	}
	__gleTexCoord1f = (PFNGLTEXCOORD1FPROC)gleIntGetProcAddress("glTexCoord1f");
	if(!TestPointer(__gleTexCoord1f))
	{
		__gleTexCoord1f = gle_CoreStruct.gleVarTexCoord1f;
		if(!__gleTexCoord1f) bIsLoaded = 0;
	}
	__gleTexCoord1fv = (PFNGLTEXCOORD1FVPROC)gleIntGetProcAddress("glTexCoord1fv");
	if(!TestPointer(__gleTexCoord1fv))
	{
		__gleTexCoord1fv = gle_CoreStruct.gleVarTexCoord1fv;
		if(!__gleTexCoord1fv) bIsLoaded = 0;
	}
	__gleTexCoord1i = (PFNGLTEXCOORD1IPROC)gleIntGetProcAddress("glTexCoord1i");
	if(!TestPointer(__gleTexCoord1i))
	{
		__gleTexCoord1i = gle_CoreStruct.gleVarTexCoord1i;
		if(!__gleTexCoord1i) bIsLoaded = 0;
	}
	__gleTexCoord1iv = (PFNGLTEXCOORD1IVPROC)gleIntGetProcAddress("glTexCoord1iv");
	if(!TestPointer(__gleTexCoord1iv))
	{
		__gleTexCoord1iv = gle_CoreStruct.gleVarTexCoord1iv;
		if(!__gleTexCoord1iv) bIsLoaded = 0;
	}
	__gleTexCoord1s = (PFNGLTEXCOORD1SPROC)gleIntGetProcAddress("glTexCoord1s");
	if(!TestPointer(__gleTexCoord1s))
	{
		__gleTexCoord1s = gle_CoreStruct.gleVarTexCoord1s;
		if(!__gleTexCoord1s) bIsLoaded = 0;
	}
	__gleTexCoord1sv = (PFNGLTEXCOORD1SVPROC)gleIntGetProcAddress("glTexCoord1sv");
	if(!TestPointer(__gleTexCoord1sv))
	{
		__gleTexCoord1sv = gle_CoreStruct.gleVarTexCoord1sv;
		if(!__gleTexCoord1sv) bIsLoaded = 0;
	}
	__gleTexCoord2d = (PFNGLTEXCOORD2DPROC)gleIntGetProcAddress("glTexCoord2d");
	if(!TestPointer(__gleTexCoord2d))
	{
		__gleTexCoord2d = gle_CoreStruct.gleVarTexCoord2d;
		if(!__gleTexCoord2d) bIsLoaded = 0;
	}
	__gleTexCoord2dv = (PFNGLTEXCOORD2DVPROC)gleIntGetProcAddress("glTexCoord2dv");
	if(!TestPointer(__gleTexCoord2dv))
	{
		__gleTexCoord2dv = gle_CoreStruct.gleVarTexCoord2dv;
		if(!__gleTexCoord2dv) bIsLoaded = 0;
	}
	__gleTexCoord2f = (PFNGLTEXCOORD2FPROC)gleIntGetProcAddress("glTexCoord2f");
	if(!TestPointer(__gleTexCoord2f))
	{
		__gleTexCoord2f = gle_CoreStruct.gleVarTexCoord2f;
		if(!__gleTexCoord2f) bIsLoaded = 0;
	}
	__gleTexCoord2fv = (PFNGLTEXCOORD2FVPROC)gleIntGetProcAddress("glTexCoord2fv");
	if(!TestPointer(__gleTexCoord2fv))
	{
		__gleTexCoord2fv = gle_CoreStruct.gleVarTexCoord2fv;
		if(!__gleTexCoord2fv) bIsLoaded = 0;
	}
	__gleTexCoord2i = (PFNGLTEXCOORD2IPROC)gleIntGetProcAddress("glTexCoord2i");
	if(!TestPointer(__gleTexCoord2i))
	{
		__gleTexCoord2i = gle_CoreStruct.gleVarTexCoord2i;
		if(!__gleTexCoord2i) bIsLoaded = 0;
	}
	__gleTexCoord2iv = (PFNGLTEXCOORD2IVPROC)gleIntGetProcAddress("glTexCoord2iv");
	if(!TestPointer(__gleTexCoord2iv))
	{
		__gleTexCoord2iv = gle_CoreStruct.gleVarTexCoord2iv;
		if(!__gleTexCoord2iv) bIsLoaded = 0;
	}
	__gleTexCoord2s = (PFNGLTEXCOORD2SPROC)gleIntGetProcAddress("glTexCoord2s");
	if(!TestPointer(__gleTexCoord2s))
	{
		__gleTexCoord2s = gle_CoreStruct.gleVarTexCoord2s;
		if(!__gleTexCoord2s) bIsLoaded = 0;
	}
	__gleTexCoord2sv = (PFNGLTEXCOORD2SVPROC)gleIntGetProcAddress("glTexCoord2sv");
	if(!TestPointer(__gleTexCoord2sv))
	{
		__gleTexCoord2sv = gle_CoreStruct.gleVarTexCoord2sv;
		if(!__gleTexCoord2sv) bIsLoaded = 0;
	}
	__gleTexCoord3d = (PFNGLTEXCOORD3DPROC)gleIntGetProcAddress("glTexCoord3d");
	if(!TestPointer(__gleTexCoord3d))
	{
		__gleTexCoord3d = gle_CoreStruct.gleVarTexCoord3d;
		if(!__gleTexCoord3d) bIsLoaded = 0;
	}
	__gleTexCoord3dv = (PFNGLTEXCOORD3DVPROC)gleIntGetProcAddress("glTexCoord3dv");
	if(!TestPointer(__gleTexCoord3dv))
	{
		__gleTexCoord3dv = gle_CoreStruct.gleVarTexCoord3dv;
		if(!__gleTexCoord3dv) bIsLoaded = 0;
	}
	__gleTexCoord3f = (PFNGLTEXCOORD3FPROC)gleIntGetProcAddress("glTexCoord3f");
	if(!TestPointer(__gleTexCoord3f))
	{
		__gleTexCoord3f = gle_CoreStruct.gleVarTexCoord3f;
		if(!__gleTexCoord3f) bIsLoaded = 0;
	}
	__gleTexCoord3fv = (PFNGLTEXCOORD3FVPROC)gleIntGetProcAddress("glTexCoord3fv");
	if(!TestPointer(__gleTexCoord3fv))
	{
		__gleTexCoord3fv = gle_CoreStruct.gleVarTexCoord3fv;
		if(!__gleTexCoord3fv) bIsLoaded = 0;
	}
	__gleTexCoord3i = (PFNGLTEXCOORD3IPROC)gleIntGetProcAddress("glTexCoord3i");
	if(!TestPointer(__gleTexCoord3i))
	{
		__gleTexCoord3i = gle_CoreStruct.gleVarTexCoord3i;
		if(!__gleTexCoord3i) bIsLoaded = 0;
	}
	__gleTexCoord3iv = (PFNGLTEXCOORD3IVPROC)gleIntGetProcAddress("glTexCoord3iv");
	if(!TestPointer(__gleTexCoord3iv))
	{
		__gleTexCoord3iv = gle_CoreStruct.gleVarTexCoord3iv;
		if(!__gleTexCoord3iv) bIsLoaded = 0;
	}
	__gleTexCoord3s = (PFNGLTEXCOORD3SPROC)gleIntGetProcAddress("glTexCoord3s");
	if(!TestPointer(__gleTexCoord3s))
	{
		__gleTexCoord3s = gle_CoreStruct.gleVarTexCoord3s;
		if(!__gleTexCoord3s) bIsLoaded = 0;
	}
	__gleTexCoord3sv = (PFNGLTEXCOORD3SVPROC)gleIntGetProcAddress("glTexCoord3sv");
	if(!TestPointer(__gleTexCoord3sv))
	{
		__gleTexCoord3sv = gle_CoreStruct.gleVarTexCoord3sv;
		if(!__gleTexCoord3sv) bIsLoaded = 0;
	}
	__gleTexCoord4d = (PFNGLTEXCOORD4DPROC)gleIntGetProcAddress("glTexCoord4d");
	if(!TestPointer(__gleTexCoord4d))
	{
		__gleTexCoord4d = gle_CoreStruct.gleVarTexCoord4d;
		if(!__gleTexCoord4d) bIsLoaded = 0;
	}
	__gleTexCoord4dv = (PFNGLTEXCOORD4DVPROC)gleIntGetProcAddress("glTexCoord4dv");
	if(!TestPointer(__gleTexCoord4dv))
	{
		__gleTexCoord4dv = gle_CoreStruct.gleVarTexCoord4dv;
		if(!__gleTexCoord4dv) bIsLoaded = 0;
	}
	__gleTexCoord4f = (PFNGLTEXCOORD4FPROC)gleIntGetProcAddress("glTexCoord4f");
	if(!TestPointer(__gleTexCoord4f))
	{
		__gleTexCoord4f = gle_CoreStruct.gleVarTexCoord4f;
		if(!__gleTexCoord4f) bIsLoaded = 0;
	}
	__gleTexCoord4fv = (PFNGLTEXCOORD4FVPROC)gleIntGetProcAddress("glTexCoord4fv");
	if(!TestPointer(__gleTexCoord4fv))
	{
		__gleTexCoord4fv = gle_CoreStruct.gleVarTexCoord4fv;
		if(!__gleTexCoord4fv) bIsLoaded = 0;
	}
	__gleTexCoord4i = (PFNGLTEXCOORD4IPROC)gleIntGetProcAddress("glTexCoord4i");
	if(!TestPointer(__gleTexCoord4i))
	{
		__gleTexCoord4i = gle_CoreStruct.gleVarTexCoord4i;
		if(!__gleTexCoord4i) bIsLoaded = 0;
	}
	__gleTexCoord4iv = (PFNGLTEXCOORD4IVPROC)gleIntGetProcAddress("glTexCoord4iv");
	if(!TestPointer(__gleTexCoord4iv))
	{
		__gleTexCoord4iv = gle_CoreStruct.gleVarTexCoord4iv;
		if(!__gleTexCoord4iv) bIsLoaded = 0;
	}
	__gleTexCoord4s = (PFNGLTEXCOORD4SPROC)gleIntGetProcAddress("glTexCoord4s");
	if(!TestPointer(__gleTexCoord4s))
	{
		__gleTexCoord4s = gle_CoreStruct.gleVarTexCoord4s;
		if(!__gleTexCoord4s) bIsLoaded = 0;
	}
	__gleTexCoord4sv = (PFNGLTEXCOORD4SVPROC)gleIntGetProcAddress("glTexCoord4sv");
	if(!TestPointer(__gleTexCoord4sv))
	{
		__gleTexCoord4sv = gle_CoreStruct.gleVarTexCoord4sv;
		if(!__gleTexCoord4sv) bIsLoaded = 0;
	}
	__gleVertex2d = (PFNGLVERTEX2DPROC)gleIntGetProcAddress("glVertex2d");
	if(!TestPointer(__gleVertex2d))
	{
		__gleVertex2d = gle_CoreStruct.gleVarVertex2d;
		if(!__gleVertex2d) bIsLoaded = 0;
	}
	__gleVertex2dv = (PFNGLVERTEX2DVPROC)gleIntGetProcAddress("glVertex2dv");
	if(!TestPointer(__gleVertex2dv))
	{
		__gleVertex2dv = gle_CoreStruct.gleVarVertex2dv;
		if(!__gleVertex2dv) bIsLoaded = 0;
	}
	__gleVertex2f = (PFNGLVERTEX2FPROC)gleIntGetProcAddress("glVertex2f");
	if(!TestPointer(__gleVertex2f))
	{
		__gleVertex2f = gle_CoreStruct.gleVarVertex2f;
		if(!__gleVertex2f) bIsLoaded = 0;
	}
	__gleVertex2fv = (PFNGLVERTEX2FVPROC)gleIntGetProcAddress("glVertex2fv");
	if(!TestPointer(__gleVertex2fv))
	{
		__gleVertex2fv = gle_CoreStruct.gleVarVertex2fv;
		if(!__gleVertex2fv) bIsLoaded = 0;
	}
	__gleVertex2i = (PFNGLVERTEX2IPROC)gleIntGetProcAddress("glVertex2i");
	if(!TestPointer(__gleVertex2i))
	{
		__gleVertex2i = gle_CoreStruct.gleVarVertex2i;
		if(!__gleVertex2i) bIsLoaded = 0;
	}
	__gleVertex2iv = (PFNGLVERTEX2IVPROC)gleIntGetProcAddress("glVertex2iv");
	if(!TestPointer(__gleVertex2iv))
	{
		__gleVertex2iv = gle_CoreStruct.gleVarVertex2iv;
		if(!__gleVertex2iv) bIsLoaded = 0;
	}
	__gleVertex2s = (PFNGLVERTEX2SPROC)gleIntGetProcAddress("glVertex2s");
	if(!TestPointer(__gleVertex2s))
	{
		__gleVertex2s = gle_CoreStruct.gleVarVertex2s;
		if(!__gleVertex2s) bIsLoaded = 0;
	}
	__gleVertex2sv = (PFNGLVERTEX2SVPROC)gleIntGetProcAddress("glVertex2sv");
	if(!TestPointer(__gleVertex2sv))
	{
		__gleVertex2sv = gle_CoreStruct.gleVarVertex2sv;
		if(!__gleVertex2sv) bIsLoaded = 0;
	}
	__gleVertex3d = (PFNGLVERTEX3DPROC)gleIntGetProcAddress("glVertex3d");
	if(!TestPointer(__gleVertex3d))
	{
		__gleVertex3d = gle_CoreStruct.gleVarVertex3d;
		if(!__gleVertex3d) bIsLoaded = 0;
	}
	__gleVertex3dv = (PFNGLVERTEX3DVPROC)gleIntGetProcAddress("glVertex3dv");
	if(!TestPointer(__gleVertex3dv))
	{
		__gleVertex3dv = gle_CoreStruct.gleVarVertex3dv;
		if(!__gleVertex3dv) bIsLoaded = 0;
	}
	__gleVertex3f = (PFNGLVERTEX3FPROC)gleIntGetProcAddress("glVertex3f");
	if(!TestPointer(__gleVertex3f))
	{
		__gleVertex3f = gle_CoreStruct.gleVarVertex3f;
		if(!__gleVertex3f) bIsLoaded = 0;
	}
	__gleVertex3fv = (PFNGLVERTEX3FVPROC)gleIntGetProcAddress("glVertex3fv");
	if(!TestPointer(__gleVertex3fv))
	{
		__gleVertex3fv = gle_CoreStruct.gleVarVertex3fv;
		if(!__gleVertex3fv) bIsLoaded = 0;
	}
	__gleVertex3i = (PFNGLVERTEX3IPROC)gleIntGetProcAddress("glVertex3i");
	if(!TestPointer(__gleVertex3i))
	{
		__gleVertex3i = gle_CoreStruct.gleVarVertex3i;
		if(!__gleVertex3i) bIsLoaded = 0;
	}
	__gleVertex3iv = (PFNGLVERTEX3IVPROC)gleIntGetProcAddress("glVertex3iv");
	if(!TestPointer(__gleVertex3iv))
	{
		__gleVertex3iv = gle_CoreStruct.gleVarVertex3iv;
		if(!__gleVertex3iv) bIsLoaded = 0;
	}
	__gleVertex3s = (PFNGLVERTEX3SPROC)gleIntGetProcAddress("glVertex3s");
	if(!TestPointer(__gleVertex3s))
	{
		__gleVertex3s = gle_CoreStruct.gleVarVertex3s;
		if(!__gleVertex3s) bIsLoaded = 0;
	}
	__gleVertex3sv = (PFNGLVERTEX3SVPROC)gleIntGetProcAddress("glVertex3sv");
	if(!TestPointer(__gleVertex3sv))
	{
		__gleVertex3sv = gle_CoreStruct.gleVarVertex3sv;
		if(!__gleVertex3sv) bIsLoaded = 0;
	}
	__gleVertex4d = (PFNGLVERTEX4DPROC)gleIntGetProcAddress("glVertex4d");
	if(!TestPointer(__gleVertex4d))
	{
		__gleVertex4d = gle_CoreStruct.gleVarVertex4d;
		if(!__gleVertex4d) bIsLoaded = 0;
	}
	__gleVertex4dv = (PFNGLVERTEX4DVPROC)gleIntGetProcAddress("glVertex4dv");
	if(!TestPointer(__gleVertex4dv))
	{
		__gleVertex4dv = gle_CoreStruct.gleVarVertex4dv;
		if(!__gleVertex4dv) bIsLoaded = 0;
	}
	__gleVertex4f = (PFNGLVERTEX4FPROC)gleIntGetProcAddress("glVertex4f");
	if(!TestPointer(__gleVertex4f))
	{
		__gleVertex4f = gle_CoreStruct.gleVarVertex4f;
		if(!__gleVertex4f) bIsLoaded = 0;
	}
	__gleVertex4fv = (PFNGLVERTEX4FVPROC)gleIntGetProcAddress("glVertex4fv");
	if(!TestPointer(__gleVertex4fv))
	{
		__gleVertex4fv = gle_CoreStruct.gleVarVertex4fv;
		if(!__gleVertex4fv) bIsLoaded = 0;
	}
	__gleVertex4i = (PFNGLVERTEX4IPROC)gleIntGetProcAddress("glVertex4i");
	if(!TestPointer(__gleVertex4i))
	{
		__gleVertex4i = gle_CoreStruct.gleVarVertex4i;
		if(!__gleVertex4i) bIsLoaded = 0;
	}
	__gleVertex4iv = (PFNGLVERTEX4IVPROC)gleIntGetProcAddress("glVertex4iv");
	if(!TestPointer(__gleVertex4iv))
	{
		__gleVertex4iv = gle_CoreStruct.gleVarVertex4iv;
		if(!__gleVertex4iv) bIsLoaded = 0;
	}
	__gleVertex4s = (PFNGLVERTEX4SPROC)gleIntGetProcAddress("glVertex4s");
	if(!TestPointer(__gleVertex4s))
	{
		__gleVertex4s = gle_CoreStruct.gleVarVertex4s;
		if(!__gleVertex4s) bIsLoaded = 0;
	}
	__gleVertex4sv = (PFNGLVERTEX4SVPROC)gleIntGetProcAddress("glVertex4sv");
	if(!TestPointer(__gleVertex4sv))
	{
		__gleVertex4sv = gle_CoreStruct.gleVarVertex4sv;
		if(!__gleVertex4sv) bIsLoaded = 0;
	}
	__gleClipPlane = (PFNGLCLIPPLANEPROC)gleIntGetProcAddress("glClipPlane");
	if(!TestPointer(__gleClipPlane))
	{
		__gleClipPlane = gle_CoreStruct.gleVarClipPlane;
		if(!__gleClipPlane) bIsLoaded = 0;
	}
	__gleColorMaterial = (PFNGLCOLORMATERIALPROC)gleIntGetProcAddress("glColorMaterial");
	if(!TestPointer(__gleColorMaterial))
	{
		__gleColorMaterial = gle_CoreStruct.gleVarColorMaterial;
		if(!__gleColorMaterial) bIsLoaded = 0;
	}
	__gleFogf = (PFNGLFOGFPROC)gleIntGetProcAddress("glFogf");
	if(!TestPointer(__gleFogf))
	{
		__gleFogf = gle_CoreStruct.gleVarFogf;
		if(!__gleFogf) bIsLoaded = 0;
	}
	__gleFogfv = (PFNGLFOGFVPROC)gleIntGetProcAddress("glFogfv");
	if(!TestPointer(__gleFogfv))
	{
		__gleFogfv = gle_CoreStruct.gleVarFogfv;
		if(!__gleFogfv) bIsLoaded = 0;
	}
	__gleFogi = (PFNGLFOGIPROC)gleIntGetProcAddress("glFogi");
	if(!TestPointer(__gleFogi))
	{
		__gleFogi = gle_CoreStruct.gleVarFogi;
		if(!__gleFogi) bIsLoaded = 0;
	}
	__gleFogiv = (PFNGLFOGIVPROC)gleIntGetProcAddress("glFogiv");
	if(!TestPointer(__gleFogiv))
	{
		__gleFogiv = gle_CoreStruct.gleVarFogiv;
		if(!__gleFogiv) bIsLoaded = 0;
	}
	__gleLightf = (PFNGLLIGHTFPROC)gleIntGetProcAddress("glLightf");
	if(!TestPointer(__gleLightf))
	{
		__gleLightf = gle_CoreStruct.gleVarLightf;
		if(!__gleLightf) bIsLoaded = 0;
	}
	__gleLightfv = (PFNGLLIGHTFVPROC)gleIntGetProcAddress("glLightfv");
	if(!TestPointer(__gleLightfv))
	{
		__gleLightfv = gle_CoreStruct.gleVarLightfv;
		if(!__gleLightfv) bIsLoaded = 0;
	}
	__gleLighti = (PFNGLLIGHTIPROC)gleIntGetProcAddress("glLighti");
	if(!TestPointer(__gleLighti))
	{
		__gleLighti = gle_CoreStruct.gleVarLighti;
		if(!__gleLighti) bIsLoaded = 0;
	}
	__gleLightiv = (PFNGLLIGHTIVPROC)gleIntGetProcAddress("glLightiv");
	if(!TestPointer(__gleLightiv))
	{
		__gleLightiv = gle_CoreStruct.gleVarLightiv;
		if(!__gleLightiv) bIsLoaded = 0;
	}
	__gleLightModelf = (PFNGLLIGHTMODELFPROC)gleIntGetProcAddress("glLightModelf");
	if(!TestPointer(__gleLightModelf))
	{
		__gleLightModelf = gle_CoreStruct.gleVarLightModelf;
		if(!__gleLightModelf) bIsLoaded = 0;
	}
	__gleLightModelfv = (PFNGLLIGHTMODELFVPROC)gleIntGetProcAddress("glLightModelfv");
	if(!TestPointer(__gleLightModelfv))
	{
		__gleLightModelfv = gle_CoreStruct.gleVarLightModelfv;
		if(!__gleLightModelfv) bIsLoaded = 0;
	}
	__gleLightModeli = (PFNGLLIGHTMODELIPROC)gleIntGetProcAddress("glLightModeli");
	if(!TestPointer(__gleLightModeli))
	{
		__gleLightModeli = gle_CoreStruct.gleVarLightModeli;
		if(!__gleLightModeli) bIsLoaded = 0;
	}
	__gleLightModeliv = (PFNGLLIGHTMODELIVPROC)gleIntGetProcAddress("glLightModeliv");
	if(!TestPointer(__gleLightModeliv))
	{
		__gleLightModeliv = gle_CoreStruct.gleVarLightModeliv;
		if(!__gleLightModeliv) bIsLoaded = 0;
	}
	__gleLineStipple = (PFNGLLINESTIPPLEPROC)gleIntGetProcAddress("glLineStipple");
	if(!TestPointer(__gleLineStipple))
	{
		__gleLineStipple = gle_CoreStruct.gleVarLineStipple;
		if(!__gleLineStipple) bIsLoaded = 0;
	}
	__gleMaterialf = (PFNGLMATERIALFPROC)gleIntGetProcAddress("glMaterialf");
	if(!TestPointer(__gleMaterialf))
	{
		__gleMaterialf = gle_CoreStruct.gleVarMaterialf;
		if(!__gleMaterialf) bIsLoaded = 0;
	}
	__gleMaterialfv = (PFNGLMATERIALFVPROC)gleIntGetProcAddress("glMaterialfv");
	if(!TestPointer(__gleMaterialfv))
	{
		__gleMaterialfv = gle_CoreStruct.gleVarMaterialfv;
		if(!__gleMaterialfv) bIsLoaded = 0;
	}
	__gleMateriali = (PFNGLMATERIALIPROC)gleIntGetProcAddress("glMateriali");
	if(!TestPointer(__gleMateriali))
	{
		__gleMateriali = gle_CoreStruct.gleVarMateriali;
		if(!__gleMateriali) bIsLoaded = 0;
	}
	__gleMaterialiv = (PFNGLMATERIALIVPROC)gleIntGetProcAddress("glMaterialiv");
	if(!TestPointer(__gleMaterialiv))
	{
		__gleMaterialiv = gle_CoreStruct.gleVarMaterialiv;
		if(!__gleMaterialiv) bIsLoaded = 0;
	}
	__glePolygonStipple = (PFNGLPOLYGONSTIPPLEPROC)gleIntGetProcAddress("glPolygonStipple");
	if(!TestPointer(__glePolygonStipple))
	{
		__glePolygonStipple = gle_CoreStruct.gleVarPolygonStipple;
		if(!__glePolygonStipple) bIsLoaded = 0;
	}
	__gleShadeModel = (PFNGLSHADEMODELPROC)gleIntGetProcAddress("glShadeModel");
	if(!TestPointer(__gleShadeModel))
	{
		__gleShadeModel = gle_CoreStruct.gleVarShadeModel;
		if(!__gleShadeModel) bIsLoaded = 0;
	}
	__gleTexEnvf = (PFNGLTEXENVFPROC)gleIntGetProcAddress("glTexEnvf");
	if(!TestPointer(__gleTexEnvf))
	{
		__gleTexEnvf = gle_CoreStruct.gleVarTexEnvf;
		if(!__gleTexEnvf) bIsLoaded = 0;
	}
	__gleTexEnvfv = (PFNGLTEXENVFVPROC)gleIntGetProcAddress("glTexEnvfv");
	if(!TestPointer(__gleTexEnvfv))
	{
		__gleTexEnvfv = gle_CoreStruct.gleVarTexEnvfv;
		if(!__gleTexEnvfv) bIsLoaded = 0;
	}
	__gleTexEnvi = (PFNGLTEXENVIPROC)gleIntGetProcAddress("glTexEnvi");
	if(!TestPointer(__gleTexEnvi))
	{
		__gleTexEnvi = gle_CoreStruct.gleVarTexEnvi;
		if(!__gleTexEnvi) bIsLoaded = 0;
	}
	__gleTexEnviv = (PFNGLTEXENVIVPROC)gleIntGetProcAddress("glTexEnviv");
	if(!TestPointer(__gleTexEnviv))
	{
		__gleTexEnviv = gle_CoreStruct.gleVarTexEnviv;
		if(!__gleTexEnviv) bIsLoaded = 0;
	}
	__gleTexGend = (PFNGLTEXGENDPROC)gleIntGetProcAddress("glTexGend");
	if(!TestPointer(__gleTexGend))
	{
		__gleTexGend = gle_CoreStruct.gleVarTexGend;
		if(!__gleTexGend) bIsLoaded = 0;
	}
	__gleTexGendv = (PFNGLTEXGENDVPROC)gleIntGetProcAddress("glTexGendv");
	if(!TestPointer(__gleTexGendv))
	{
		__gleTexGendv = gle_CoreStruct.gleVarTexGendv;
		if(!__gleTexGendv) bIsLoaded = 0;
	}
	__gleTexGenf = (PFNGLTEXGENFPROC)gleIntGetProcAddress("glTexGenf");
	if(!TestPointer(__gleTexGenf))
	{
		__gleTexGenf = gle_CoreStruct.gleVarTexGenf;
		if(!__gleTexGenf) bIsLoaded = 0;
	}
	__gleTexGenfv = (PFNGLTEXGENFVPROC)gleIntGetProcAddress("glTexGenfv");
	if(!TestPointer(__gleTexGenfv))
	{
		__gleTexGenfv = gle_CoreStruct.gleVarTexGenfv;
		if(!__gleTexGenfv) bIsLoaded = 0;
	}
	__gleTexGeni = (PFNGLTEXGENIPROC)gleIntGetProcAddress("glTexGeni");
	if(!TestPointer(__gleTexGeni))
	{
		__gleTexGeni = gle_CoreStruct.gleVarTexGeni;
		if(!__gleTexGeni) bIsLoaded = 0;
	}
	__gleTexGeniv = (PFNGLTEXGENIVPROC)gleIntGetProcAddress("glTexGeniv");
	if(!TestPointer(__gleTexGeniv))
	{
		__gleTexGeniv = gle_CoreStruct.gleVarTexGeniv;
		if(!__gleTexGeniv) bIsLoaded = 0;
	}
	__gleFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC)gleIntGetProcAddress("glFeedbackBuffer");
	if(!TestPointer(__gleFeedbackBuffer))
	{
		__gleFeedbackBuffer = gle_CoreStruct.gleVarFeedbackBuffer;
		if(!__gleFeedbackBuffer) bIsLoaded = 0;
	}
	__gleSelectBuffer = (PFNGLSELECTBUFFERPROC)gleIntGetProcAddress("glSelectBuffer");
	if(!TestPointer(__gleSelectBuffer))
	{
		__gleSelectBuffer = gle_CoreStruct.gleVarSelectBuffer;
		if(!__gleSelectBuffer) bIsLoaded = 0;
	}
	__gleRenderMode = (PFNGLRENDERMODEPROC)gleIntGetProcAddress("glRenderMode");
	if(!TestPointer(__gleRenderMode))
	{
		__gleRenderMode = gle_CoreStruct.gleVarRenderMode;
		if(!__gleRenderMode) bIsLoaded = 0;
	}
	__gleInitNames = (PFNGLINITNAMESPROC)gleIntGetProcAddress("glInitNames");
	if(!TestPointer(__gleInitNames))
	{
		__gleInitNames = gle_CoreStruct.gleVarInitNames;
		if(!__gleInitNames) bIsLoaded = 0;
	}
	__gleLoadName = (PFNGLLOADNAMEPROC)gleIntGetProcAddress("glLoadName");
	if(!TestPointer(__gleLoadName))
	{
		__gleLoadName = gle_CoreStruct.gleVarLoadName;
		if(!__gleLoadName) bIsLoaded = 0;
	}
	__glePassThrough = (PFNGLPASSTHROUGHPROC)gleIntGetProcAddress("glPassThrough");
	if(!TestPointer(__glePassThrough))
	{
		__glePassThrough = gle_CoreStruct.gleVarPassThrough;
		if(!__glePassThrough) bIsLoaded = 0;
	}
	__glePopName = (PFNGLPOPNAMEPROC)gleIntGetProcAddress("glPopName");
	if(!TestPointer(__glePopName))
	{
		__glePopName = gle_CoreStruct.gleVarPopName;
		if(!__glePopName) bIsLoaded = 0;
	}
	__glePushName = (PFNGLPUSHNAMEPROC)gleIntGetProcAddress("glPushName");
	if(!TestPointer(__glePushName))
	{
		__glePushName = gle_CoreStruct.gleVarPushName;
		if(!__glePushName) bIsLoaded = 0;
	}
	__gleClearAccum = (PFNGLCLEARACCUMPROC)gleIntGetProcAddress("glClearAccum");
	if(!TestPointer(__gleClearAccum))
	{
		__gleClearAccum = gle_CoreStruct.gleVarClearAccum;
		if(!__gleClearAccum) bIsLoaded = 0;
	}
	__gleClearIndex = (PFNGLCLEARINDEXPROC)gleIntGetProcAddress("glClearIndex");
	if(!TestPointer(__gleClearIndex))
	{
		__gleClearIndex = gle_CoreStruct.gleVarClearIndex;
		if(!__gleClearIndex) bIsLoaded = 0;
	}
	__gleIndexMask = (PFNGLINDEXMASKPROC)gleIntGetProcAddress("glIndexMask");
	if(!TestPointer(__gleIndexMask))
	{
		__gleIndexMask = gle_CoreStruct.gleVarIndexMask;
		if(!__gleIndexMask) bIsLoaded = 0;
	}
	__gleAccum = (PFNGLACCUMPROC)gleIntGetProcAddress("glAccum");
	if(!TestPointer(__gleAccum))
	{
		__gleAccum = gle_CoreStruct.gleVarAccum;
		if(!__gleAccum) bIsLoaded = 0;
	}
	__glePopAttrib = (PFNGLPOPATTRIBPROC)gleIntGetProcAddress("glPopAttrib");
	if(!TestPointer(__glePopAttrib))
	{
		__glePopAttrib = gle_CoreStruct.gleVarPopAttrib;
		if(!__glePopAttrib) bIsLoaded = 0;
	}
	__glePushAttrib = (PFNGLPUSHATTRIBPROC)gleIntGetProcAddress("glPushAttrib");
	if(!TestPointer(__glePushAttrib))
	{
		__glePushAttrib = gle_CoreStruct.gleVarPushAttrib;
		if(!__glePushAttrib) bIsLoaded = 0;
	}
	__gleMap1d = (PFNGLMAP1DPROC)gleIntGetProcAddress("glMap1d");
	if(!TestPointer(__gleMap1d))
	{
		__gleMap1d = gle_CoreStruct.gleVarMap1d;
		if(!__gleMap1d) bIsLoaded = 0;
	}
	__gleMap1f = (PFNGLMAP1FPROC)gleIntGetProcAddress("glMap1f");
	if(!TestPointer(__gleMap1f))
	{
		__gleMap1f = gle_CoreStruct.gleVarMap1f;
		if(!__gleMap1f) bIsLoaded = 0;
	}
	__gleMap2d = (PFNGLMAP2DPROC)gleIntGetProcAddress("glMap2d");
	if(!TestPointer(__gleMap2d))
	{
		__gleMap2d = gle_CoreStruct.gleVarMap2d;
		if(!__gleMap2d) bIsLoaded = 0;
	}
	__gleMap2f = (PFNGLMAP2FPROC)gleIntGetProcAddress("glMap2f");
	if(!TestPointer(__gleMap2f))
	{
		__gleMap2f = gle_CoreStruct.gleVarMap2f;
		if(!__gleMap2f) bIsLoaded = 0;
	}
	__gleMapGrid1d = (PFNGLMAPGRID1DPROC)gleIntGetProcAddress("glMapGrid1d");
	if(!TestPointer(__gleMapGrid1d))
	{
		__gleMapGrid1d = gle_CoreStruct.gleVarMapGrid1d;
		if(!__gleMapGrid1d) bIsLoaded = 0;
	}
	__gleMapGrid1f = (PFNGLMAPGRID1FPROC)gleIntGetProcAddress("glMapGrid1f");
	if(!TestPointer(__gleMapGrid1f))
	{
		__gleMapGrid1f = gle_CoreStruct.gleVarMapGrid1f;
		if(!__gleMapGrid1f) bIsLoaded = 0;
	}
	__gleMapGrid2d = (PFNGLMAPGRID2DPROC)gleIntGetProcAddress("glMapGrid2d");
	if(!TestPointer(__gleMapGrid2d))
	{
		__gleMapGrid2d = gle_CoreStruct.gleVarMapGrid2d;
		if(!__gleMapGrid2d) bIsLoaded = 0;
	}
	__gleMapGrid2f = (PFNGLMAPGRID2FPROC)gleIntGetProcAddress("glMapGrid2f");
	if(!TestPointer(__gleMapGrid2f))
	{
		__gleMapGrid2f = gle_CoreStruct.gleVarMapGrid2f;
		if(!__gleMapGrid2f) bIsLoaded = 0;
	}
	__gleEvalCoord1d = (PFNGLEVALCOORD1DPROC)gleIntGetProcAddress("glEvalCoord1d");
	if(!TestPointer(__gleEvalCoord1d))
	{
		__gleEvalCoord1d = gle_CoreStruct.gleVarEvalCoord1d;
		if(!__gleEvalCoord1d) bIsLoaded = 0;
	}
	__gleEvalCoord1dv = (PFNGLEVALCOORD1DVPROC)gleIntGetProcAddress("glEvalCoord1dv");
	if(!TestPointer(__gleEvalCoord1dv))
	{
		__gleEvalCoord1dv = gle_CoreStruct.gleVarEvalCoord1dv;
		if(!__gleEvalCoord1dv) bIsLoaded = 0;
	}
	__gleEvalCoord1f = (PFNGLEVALCOORD1FPROC)gleIntGetProcAddress("glEvalCoord1f");
	if(!TestPointer(__gleEvalCoord1f))
	{
		__gleEvalCoord1f = gle_CoreStruct.gleVarEvalCoord1f;
		if(!__gleEvalCoord1f) bIsLoaded = 0;
	}
	__gleEvalCoord1fv = (PFNGLEVALCOORD1FVPROC)gleIntGetProcAddress("glEvalCoord1fv");
	if(!TestPointer(__gleEvalCoord1fv))
	{
		__gleEvalCoord1fv = gle_CoreStruct.gleVarEvalCoord1fv;
		if(!__gleEvalCoord1fv) bIsLoaded = 0;
	}
	__gleEvalCoord2d = (PFNGLEVALCOORD2DPROC)gleIntGetProcAddress("glEvalCoord2d");
	if(!TestPointer(__gleEvalCoord2d))
	{
		__gleEvalCoord2d = gle_CoreStruct.gleVarEvalCoord2d;
		if(!__gleEvalCoord2d) bIsLoaded = 0;
	}
	__gleEvalCoord2dv = (PFNGLEVALCOORD2DVPROC)gleIntGetProcAddress("glEvalCoord2dv");
	if(!TestPointer(__gleEvalCoord2dv))
	{
		__gleEvalCoord2dv = gle_CoreStruct.gleVarEvalCoord2dv;
		if(!__gleEvalCoord2dv) bIsLoaded = 0;
	}
	__gleEvalCoord2f = (PFNGLEVALCOORD2FPROC)gleIntGetProcAddress("glEvalCoord2f");
	if(!TestPointer(__gleEvalCoord2f))
	{
		__gleEvalCoord2f = gle_CoreStruct.gleVarEvalCoord2f;
		if(!__gleEvalCoord2f) bIsLoaded = 0;
	}
	__gleEvalCoord2fv = (PFNGLEVALCOORD2FVPROC)gleIntGetProcAddress("glEvalCoord2fv");
	if(!TestPointer(__gleEvalCoord2fv))
	{
		__gleEvalCoord2fv = gle_CoreStruct.gleVarEvalCoord2fv;
		if(!__gleEvalCoord2fv) bIsLoaded = 0;
	}
	__gleEvalMesh1 = (PFNGLEVALMESH1PROC)gleIntGetProcAddress("glEvalMesh1");
	if(!TestPointer(__gleEvalMesh1))
	{
		__gleEvalMesh1 = gle_CoreStruct.gleVarEvalMesh1;
		if(!__gleEvalMesh1) bIsLoaded = 0;
	}
	__gleEvalPoint1 = (PFNGLEVALPOINT1PROC)gleIntGetProcAddress("glEvalPoint1");
	if(!TestPointer(__gleEvalPoint1))
	{
		__gleEvalPoint1 = gle_CoreStruct.gleVarEvalPoint1;
		if(!__gleEvalPoint1) bIsLoaded = 0;
	}
	__gleEvalMesh2 = (PFNGLEVALMESH2PROC)gleIntGetProcAddress("glEvalMesh2");
	if(!TestPointer(__gleEvalMesh2))
	{
		__gleEvalMesh2 = gle_CoreStruct.gleVarEvalMesh2;
		if(!__gleEvalMesh2) bIsLoaded = 0;
	}
	__gleEvalPoint2 = (PFNGLEVALPOINT2PROC)gleIntGetProcAddress("glEvalPoint2");
	if(!TestPointer(__gleEvalPoint2))
	{
		__gleEvalPoint2 = gle_CoreStruct.gleVarEvalPoint2;
		if(!__gleEvalPoint2) bIsLoaded = 0;
	}
	__gleAlphaFunc = (PFNGLALPHAFUNCPROC)gleIntGetProcAddress("glAlphaFunc");
	if(!TestPointer(__gleAlphaFunc))
	{
		__gleAlphaFunc = gle_CoreStruct.gleVarAlphaFunc;
		if(!__gleAlphaFunc) bIsLoaded = 0;
	}
	__glePixelZoom = (PFNGLPIXELZOOMPROC)gleIntGetProcAddress("glPixelZoom");
	if(!TestPointer(__glePixelZoom))
	{
		__glePixelZoom = gle_CoreStruct.gleVarPixelZoom;
		if(!__glePixelZoom) bIsLoaded = 0;
	}
	__glePixelTransferf = (PFNGLPIXELTRANSFERFPROC)gleIntGetProcAddress("glPixelTransferf");
	if(!TestPointer(__glePixelTransferf))
	{
		__glePixelTransferf = gle_CoreStruct.gleVarPixelTransferf;
		if(!__glePixelTransferf) bIsLoaded = 0;
	}
	__glePixelTransferi = (PFNGLPIXELTRANSFERIPROC)gleIntGetProcAddress("glPixelTransferi");
	if(!TestPointer(__glePixelTransferi))
	{
		__glePixelTransferi = gle_CoreStruct.gleVarPixelTransferi;
		if(!__glePixelTransferi) bIsLoaded = 0;
	}
	__glePixelMapfv = (PFNGLPIXELMAPFVPROC)gleIntGetProcAddress("glPixelMapfv");
	if(!TestPointer(__glePixelMapfv))
	{
		__glePixelMapfv = gle_CoreStruct.gleVarPixelMapfv;
		if(!__glePixelMapfv) bIsLoaded = 0;
	}
	__glePixelMapuiv = (PFNGLPIXELMAPUIVPROC)gleIntGetProcAddress("glPixelMapuiv");
	if(!TestPointer(__glePixelMapuiv))
	{
		__glePixelMapuiv = gle_CoreStruct.gleVarPixelMapuiv;
		if(!__glePixelMapuiv) bIsLoaded = 0;
	}
	__glePixelMapusv = (PFNGLPIXELMAPUSVPROC)gleIntGetProcAddress("glPixelMapusv");
	if(!TestPointer(__glePixelMapusv))
	{
		__glePixelMapusv = gle_CoreStruct.gleVarPixelMapusv;
		if(!__glePixelMapusv) bIsLoaded = 0;
	}
	__gleCopyPixels = (PFNGLCOPYPIXELSPROC)gleIntGetProcAddress("glCopyPixels");
	if(!TestPointer(__gleCopyPixels))
	{
		__gleCopyPixels = gle_CoreStruct.gleVarCopyPixels;
		if(!__gleCopyPixels) bIsLoaded = 0;
	}
	__gleDrawPixels = (PFNGLDRAWPIXELSPROC)gleIntGetProcAddress("glDrawPixels");
	if(!TestPointer(__gleDrawPixels))
	{
		__gleDrawPixels = gle_CoreStruct.gleVarDrawPixels;
		if(!__gleDrawPixels) bIsLoaded = 0;
	}
	__gleGetClipPlane = (PFNGLGETCLIPPLANEPROC)gleIntGetProcAddress("glGetClipPlane");
	if(!TestPointer(__gleGetClipPlane))
	{
		__gleGetClipPlane = gle_CoreStruct.gleVarGetClipPlane;
		if(!__gleGetClipPlane) bIsLoaded = 0;
	}
	__gleGetLightfv = (PFNGLGETLIGHTFVPROC)gleIntGetProcAddress("glGetLightfv");
	if(!TestPointer(__gleGetLightfv))
	{
		__gleGetLightfv = gle_CoreStruct.gleVarGetLightfv;
		if(!__gleGetLightfv) bIsLoaded = 0;
	}
	__gleGetLightiv = (PFNGLGETLIGHTIVPROC)gleIntGetProcAddress("glGetLightiv");
	if(!TestPointer(__gleGetLightiv))
	{
		__gleGetLightiv = gle_CoreStruct.gleVarGetLightiv;
		if(!__gleGetLightiv) bIsLoaded = 0;
	}
	__gleGetMapdv = (PFNGLGETMAPDVPROC)gleIntGetProcAddress("glGetMapdv");
	if(!TestPointer(__gleGetMapdv))
	{
		__gleGetMapdv = gle_CoreStruct.gleVarGetMapdv;
		if(!__gleGetMapdv) bIsLoaded = 0;
	}
	__gleGetMapfv = (PFNGLGETMAPFVPROC)gleIntGetProcAddress("glGetMapfv");
	if(!TestPointer(__gleGetMapfv))
	{
		__gleGetMapfv = gle_CoreStruct.gleVarGetMapfv;
		if(!__gleGetMapfv) bIsLoaded = 0;
	}
	__gleGetMapiv = (PFNGLGETMAPIVPROC)gleIntGetProcAddress("glGetMapiv");
	if(!TestPointer(__gleGetMapiv))
	{
		__gleGetMapiv = gle_CoreStruct.gleVarGetMapiv;
		if(!__gleGetMapiv) bIsLoaded = 0;
	}
	__gleGetMaterialfv = (PFNGLGETMATERIALFVPROC)gleIntGetProcAddress("glGetMaterialfv");
	if(!TestPointer(__gleGetMaterialfv))
	{
		__gleGetMaterialfv = gle_CoreStruct.gleVarGetMaterialfv;
		if(!__gleGetMaterialfv) bIsLoaded = 0;
	}
	__gleGetMaterialiv = (PFNGLGETMATERIALIVPROC)gleIntGetProcAddress("glGetMaterialiv");
	if(!TestPointer(__gleGetMaterialiv))
	{
		__gleGetMaterialiv = gle_CoreStruct.gleVarGetMaterialiv;
		if(!__gleGetMaterialiv) bIsLoaded = 0;
	}
	__gleGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC)gleIntGetProcAddress("glGetPixelMapfv");
	if(!TestPointer(__gleGetPixelMapfv))
	{
		__gleGetPixelMapfv = gle_CoreStruct.gleVarGetPixelMapfv;
		if(!__gleGetPixelMapfv) bIsLoaded = 0;
	}
	__gleGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC)gleIntGetProcAddress("glGetPixelMapuiv");
	if(!TestPointer(__gleGetPixelMapuiv))
	{
		__gleGetPixelMapuiv = gle_CoreStruct.gleVarGetPixelMapuiv;
		if(!__gleGetPixelMapuiv) bIsLoaded = 0;
	}
	__gleGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC)gleIntGetProcAddress("glGetPixelMapusv");
	if(!TestPointer(__gleGetPixelMapusv))
	{
		__gleGetPixelMapusv = gle_CoreStruct.gleVarGetPixelMapusv;
		if(!__gleGetPixelMapusv) bIsLoaded = 0;
	}
	__gleGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC)gleIntGetProcAddress("glGetPolygonStipple");
	if(!TestPointer(__gleGetPolygonStipple))
	{
		__gleGetPolygonStipple = gle_CoreStruct.gleVarGetPolygonStipple;
		if(!__gleGetPolygonStipple) bIsLoaded = 0;
	}
	__gleGetTexEnvfv = (PFNGLGETTEXENVFVPROC)gleIntGetProcAddress("glGetTexEnvfv");
	if(!TestPointer(__gleGetTexEnvfv))
	{
		__gleGetTexEnvfv = gle_CoreStruct.gleVarGetTexEnvfv;
		if(!__gleGetTexEnvfv) bIsLoaded = 0;
	}
	__gleGetTexEnviv = (PFNGLGETTEXENVIVPROC)gleIntGetProcAddress("glGetTexEnviv");
	if(!TestPointer(__gleGetTexEnviv))
	{
		__gleGetTexEnviv = gle_CoreStruct.gleVarGetTexEnviv;
		if(!__gleGetTexEnviv) bIsLoaded = 0;
	}
	__gleGetTexGendv = (PFNGLGETTEXGENDVPROC)gleIntGetProcAddress("glGetTexGendv");
	if(!TestPointer(__gleGetTexGendv))
	{
		__gleGetTexGendv = gle_CoreStruct.gleVarGetTexGendv;
		if(!__gleGetTexGendv) bIsLoaded = 0;
	}
	__gleGetTexGenfv = (PFNGLGETTEXGENFVPROC)gleIntGetProcAddress("glGetTexGenfv");
	if(!TestPointer(__gleGetTexGenfv))
	{
		__gleGetTexGenfv = gle_CoreStruct.gleVarGetTexGenfv;
		if(!__gleGetTexGenfv) bIsLoaded = 0;
	}
	__gleGetTexGeniv = (PFNGLGETTEXGENIVPROC)gleIntGetProcAddress("glGetTexGeniv");
	if(!TestPointer(__gleGetTexGeniv))
	{
		__gleGetTexGeniv = gle_CoreStruct.gleVarGetTexGeniv;
		if(!__gleGetTexGeniv) bIsLoaded = 0;
	}
	__gleIsList = (PFNGLISLISTPROC)gleIntGetProcAddress("glIsList");
	if(!TestPointer(__gleIsList))
	{
		__gleIsList = gle_CoreStruct.gleVarIsList;
		if(!__gleIsList) bIsLoaded = 0;
	}
	__gleFrustum = (PFNGLFRUSTUMPROC)gleIntGetProcAddress("glFrustum");
	if(!TestPointer(__gleFrustum))
	{
		__gleFrustum = gle_CoreStruct.gleVarFrustum;
		if(!__gleFrustum) bIsLoaded = 0;
	}
	__gleLoadIdentity = (PFNGLLOADIDENTITYPROC)gleIntGetProcAddress("glLoadIdentity");
	if(!TestPointer(__gleLoadIdentity))
	{
		__gleLoadIdentity = gle_CoreStruct.gleVarLoadIdentity;
		if(!__gleLoadIdentity) bIsLoaded = 0;
	}
	__gleLoadMatrixf = (PFNGLLOADMATRIXFPROC)gleIntGetProcAddress("glLoadMatrixf");
	if(!TestPointer(__gleLoadMatrixf))
	{
		__gleLoadMatrixf = gle_CoreStruct.gleVarLoadMatrixf;
		if(!__gleLoadMatrixf) bIsLoaded = 0;
	}
	__gleLoadMatrixd = (PFNGLLOADMATRIXDPROC)gleIntGetProcAddress("glLoadMatrixd");
	if(!TestPointer(__gleLoadMatrixd))
	{
		__gleLoadMatrixd = gle_CoreStruct.gleVarLoadMatrixd;
		if(!__gleLoadMatrixd) bIsLoaded = 0;
	}
	__gleMatrixMode = (PFNGLMATRIXMODEPROC)gleIntGetProcAddress("glMatrixMode");
	if(!TestPointer(__gleMatrixMode))
	{
		__gleMatrixMode = gle_CoreStruct.gleVarMatrixMode;
		if(!__gleMatrixMode) bIsLoaded = 0;
	}
	__gleMultMatrixf = (PFNGLMULTMATRIXFPROC)gleIntGetProcAddress("glMultMatrixf");
	if(!TestPointer(__gleMultMatrixf))
	{
		__gleMultMatrixf = gle_CoreStruct.gleVarMultMatrixf;
		if(!__gleMultMatrixf) bIsLoaded = 0;
	}
	__gleMultMatrixd = (PFNGLMULTMATRIXDPROC)gleIntGetProcAddress("glMultMatrixd");
	if(!TestPointer(__gleMultMatrixd))
	{
		__gleMultMatrixd = gle_CoreStruct.gleVarMultMatrixd;
		if(!__gleMultMatrixd) bIsLoaded = 0;
	}
	__gleOrtho = (PFNGLORTHOPROC)gleIntGetProcAddress("glOrtho");
	if(!TestPointer(__gleOrtho))
	{
		__gleOrtho = gle_CoreStruct.gleVarOrtho;
		if(!__gleOrtho) bIsLoaded = 0;
	}
	__glePopMatrix = (PFNGLPOPMATRIXPROC)gleIntGetProcAddress("glPopMatrix");
	if(!TestPointer(__glePopMatrix))
	{
		__glePopMatrix = gle_CoreStruct.gleVarPopMatrix;
		if(!__glePopMatrix) bIsLoaded = 0;
	}
	__glePushMatrix = (PFNGLPUSHMATRIXPROC)gleIntGetProcAddress("glPushMatrix");
	if(!TestPointer(__glePushMatrix))
	{
		__glePushMatrix = gle_CoreStruct.gleVarPushMatrix;
		if(!__glePushMatrix) bIsLoaded = 0;
	}
	__gleRotated = (PFNGLROTATEDPROC)gleIntGetProcAddress("glRotated");
	if(!TestPointer(__gleRotated))
	{
		__gleRotated = gle_CoreStruct.gleVarRotated;
		if(!__gleRotated) bIsLoaded = 0;
	}
	__gleRotatef = (PFNGLROTATEFPROC)gleIntGetProcAddress("glRotatef");
	if(!TestPointer(__gleRotatef))
	{
		__gleRotatef = gle_CoreStruct.gleVarRotatef;
		if(!__gleRotatef) bIsLoaded = 0;
	}
	__gleScaled = (PFNGLSCALEDPROC)gleIntGetProcAddress("glScaled");
	if(!TestPointer(__gleScaled))
	{
		__gleScaled = gle_CoreStruct.gleVarScaled;
		if(!__gleScaled) bIsLoaded = 0;
	}
	__gleScalef = (PFNGLSCALEFPROC)gleIntGetProcAddress("glScalef");
	if(!TestPointer(__gleScalef))
	{
		__gleScalef = gle_CoreStruct.gleVarScalef;
		if(!__gleScalef) bIsLoaded = 0;
	}
	__gleTranslated = (PFNGLTRANSLATEDPROC)gleIntGetProcAddress("glTranslated");
	if(!TestPointer(__gleTranslated))
	{
		__gleTranslated = gle_CoreStruct.gleVarTranslated;
		if(!__gleTranslated) bIsLoaded = 0;
	}
	__gleTranslatef = (PFNGLTRANSLATEFPROC)gleIntGetProcAddress("glTranslatef");
	if(!TestPointer(__gleTranslatef))
	{
		__gleTranslatef = gle_CoreStruct.gleVarTranslatef;
		if(!__gleTranslatef) bIsLoaded = 0;
	}
	__gleArrayElement = (PFNGLARRAYELEMENTPROC)gleIntGetProcAddress("glArrayElement");
	if(!TestPointer(__gleArrayElement))
	{
		__gleArrayElement = gle_CoreStruct.gleVarArrayElement;
		if(!__gleArrayElement) bIsLoaded = 0;
	}
	__gleColorPointer = (PFNGLCOLORPOINTERPROC)gleIntGetProcAddress("glColorPointer");
	if(!TestPointer(__gleColorPointer))
	{
		__gleColorPointer = gle_CoreStruct.gleVarColorPointer;
		if(!__gleColorPointer) bIsLoaded = 0;
	}
	__gleDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)gleIntGetProcAddress("glDisableClientState");
	if(!TestPointer(__gleDisableClientState))
	{
		__gleDisableClientState = gle_CoreStruct.gleVarDisableClientState;
		if(!__gleDisableClientState) bIsLoaded = 0;
	}
	__gleEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)gleIntGetProcAddress("glEdgeFlagPointer");
	if(!TestPointer(__gleEdgeFlagPointer))
	{
		__gleEdgeFlagPointer = gle_CoreStruct.gleVarEdgeFlagPointer;
		if(!__gleEdgeFlagPointer) bIsLoaded = 0;
	}
	__gleEnableClientState = (PFNGLENABLECLIENTSTATEPROC)gleIntGetProcAddress("glEnableClientState");
	if(!TestPointer(__gleEnableClientState))
	{
		__gleEnableClientState = gle_CoreStruct.gleVarEnableClientState;
		if(!__gleEnableClientState) bIsLoaded = 0;
	}
	__gleIndexPointer = (PFNGLINDEXPOINTERPROC)gleIntGetProcAddress("glIndexPointer");
	if(!TestPointer(__gleIndexPointer))
	{
		__gleIndexPointer = gle_CoreStruct.gleVarIndexPointer;
		if(!__gleIndexPointer) bIsLoaded = 0;
	}
	__gleInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)gleIntGetProcAddress("glInterleavedArrays");
	if(!TestPointer(__gleInterleavedArrays))
	{
		__gleInterleavedArrays = gle_CoreStruct.gleVarInterleavedArrays;
		if(!__gleInterleavedArrays) bIsLoaded = 0;
	}
	__gleNormalPointer = (PFNGLNORMALPOINTERPROC)gleIntGetProcAddress("glNormalPointer");
	if(!TestPointer(__gleNormalPointer))
	{
		__gleNormalPointer = gle_CoreStruct.gleVarNormalPointer;
		if(!__gleNormalPointer) bIsLoaded = 0;
	}
	__gleTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)gleIntGetProcAddress("glTexCoordPointer");
	if(!TestPointer(__gleTexCoordPointer))
	{
		__gleTexCoordPointer = gle_CoreStruct.gleVarTexCoordPointer;
		if(!__gleTexCoordPointer) bIsLoaded = 0;
	}
	__gleVertexPointer = (PFNGLVERTEXPOINTERPROC)gleIntGetProcAddress("glVertexPointer");
	if(!TestPointer(__gleVertexPointer))
	{
		__gleVertexPointer = gle_CoreStruct.gleVarVertexPointer;
		if(!__gleVertexPointer) bIsLoaded = 0;
	}
	__gleAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)gleIntGetProcAddress("glAreTexturesResident");
	if(!TestPointer(__gleAreTexturesResident))
	{
		__gleAreTexturesResident = gle_CoreStruct.gleVarAreTexturesResident;
		if(!__gleAreTexturesResident) bIsLoaded = 0;
	}
	__glePrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)gleIntGetProcAddress("glPrioritizeTextures");
	if(!TestPointer(__glePrioritizeTextures))
	{
		__glePrioritizeTextures = gle_CoreStruct.gleVarPrioritizeTextures;
		if(!__glePrioritizeTextures) bIsLoaded = 0;
	}
	__glePopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)gleIntGetProcAddress("glPopClientAttrib");
	if(!TestPointer(__glePopClientAttrib))
	{
		__glePopClientAttrib = gle_CoreStruct.gleVarPopClientAttrib;
		if(!__glePopClientAttrib) bIsLoaded = 0;
	}
	__glePushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)gleIntGetProcAddress("glPushClientAttrib");
	if(!TestPointer(__glePushClientAttrib))
	{
		__glePushClientAttrib = gle_CoreStruct.gleVarPushClientAttrib;
		if(!__glePushClientAttrib) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_2_Base()
{
	int bIsLoaded = gleIntLoadCore_1_2_Version_3_1();
	__gleTexImage3D = (PFNGLTEXIMAGE3DPROC)gleIntGetProcAddress("glTexImage3D");
	if(!TestPointer(__gleTexImage3D))
	{
		__gleTexImage3D = gle_CoreStruct.gleVarTexImage3D;
		if(!__gleTexImage3D) bIsLoaded = 0;
	}
	__gleColorTable = (PFNGLCOLORTABLEPROC)gleIntGetProcAddress("glColorTable");
	if(!TestPointer(__gleColorTable))
	{
		__gleColorTable = gle_CoreStruct.gleVarColorTable;
		if(!__gleColorTable) bIsLoaded = 0;
	}
	__gleColorTableParameterfv = (PFNGLCOLORTABLEPARAMETERFVPROC)gleIntGetProcAddress("glColorTableParameterfv");
	if(!TestPointer(__gleColorTableParameterfv))
	{
		__gleColorTableParameterfv = gle_CoreStruct.gleVarColorTableParameterfv;
		if(!__gleColorTableParameterfv) bIsLoaded = 0;
	}
	__gleColorTableParameteriv = (PFNGLCOLORTABLEPARAMETERIVPROC)gleIntGetProcAddress("glColorTableParameteriv");
	if(!TestPointer(__gleColorTableParameteriv))
	{
		__gleColorTableParameteriv = gle_CoreStruct.gleVarColorTableParameteriv;
		if(!__gleColorTableParameteriv) bIsLoaded = 0;
	}
	__gleCopyColorTable = (PFNGLCOPYCOLORTABLEPROC)gleIntGetProcAddress("glCopyColorTable");
	if(!TestPointer(__gleCopyColorTable))
	{
		__gleCopyColorTable = gle_CoreStruct.gleVarCopyColorTable;
		if(!__gleCopyColorTable) bIsLoaded = 0;
	}
	__gleGetColorTable = (PFNGLGETCOLORTABLEPROC)gleIntGetProcAddress("glGetColorTable");
	if(!TestPointer(__gleGetColorTable))
	{
		__gleGetColorTable = gle_CoreStruct.gleVarGetColorTable;
		if(!__gleGetColorTable) bIsLoaded = 0;
	}
	__gleGetColorTableParameterfv = (PFNGLGETCOLORTABLEPARAMETERFVPROC)gleIntGetProcAddress("glGetColorTableParameterfv");
	if(!TestPointer(__gleGetColorTableParameterfv))
	{
		__gleGetColorTableParameterfv = gle_CoreStruct.gleVarGetColorTableParameterfv;
		if(!__gleGetColorTableParameterfv) bIsLoaded = 0;
	}
	__gleGetColorTableParameteriv = (PFNGLGETCOLORTABLEPARAMETERIVPROC)gleIntGetProcAddress("glGetColorTableParameteriv");
	if(!TestPointer(__gleGetColorTableParameteriv))
	{
		__gleGetColorTableParameteriv = gle_CoreStruct.gleVarGetColorTableParameteriv;
		if(!__gleGetColorTableParameteriv) bIsLoaded = 0;
	}
	__gleColorSubTable = (PFNGLCOLORSUBTABLEPROC)gleIntGetProcAddress("glColorSubTable");
	if(!TestPointer(__gleColorSubTable))
	{
		__gleColorSubTable = gle_CoreStruct.gleVarColorSubTable;
		if(!__gleColorSubTable) bIsLoaded = 0;
	}
	__gleCopyColorSubTable = (PFNGLCOPYCOLORSUBTABLEPROC)gleIntGetProcAddress("glCopyColorSubTable");
	if(!TestPointer(__gleCopyColorSubTable))
	{
		__gleCopyColorSubTable = gle_CoreStruct.gleVarCopyColorSubTable;
		if(!__gleCopyColorSubTable) bIsLoaded = 0;
	}
	__gleConvolutionFilter1D = (PFNGLCONVOLUTIONFILTER1DPROC)gleIntGetProcAddress("glConvolutionFilter1D");
	if(!TestPointer(__gleConvolutionFilter1D))
	{
		__gleConvolutionFilter1D = gle_CoreStruct.gleVarConvolutionFilter1D;
		if(!__gleConvolutionFilter1D) bIsLoaded = 0;
	}
	__gleConvolutionFilter2D = (PFNGLCONVOLUTIONFILTER2DPROC)gleIntGetProcAddress("glConvolutionFilter2D");
	if(!TestPointer(__gleConvolutionFilter2D))
	{
		__gleConvolutionFilter2D = gle_CoreStruct.gleVarConvolutionFilter2D;
		if(!__gleConvolutionFilter2D) bIsLoaded = 0;
	}
	__gleConvolutionParameterf = (PFNGLCONVOLUTIONPARAMETERFPROC)gleIntGetProcAddress("glConvolutionParameterf");
	if(!TestPointer(__gleConvolutionParameterf))
	{
		__gleConvolutionParameterf = gle_CoreStruct.gleVarConvolutionParameterf;
		if(!__gleConvolutionParameterf) bIsLoaded = 0;
	}
	__gleConvolutionParameterfv = (PFNGLCONVOLUTIONPARAMETERFVPROC)gleIntGetProcAddress("glConvolutionParameterfv");
	if(!TestPointer(__gleConvolutionParameterfv))
	{
		__gleConvolutionParameterfv = gle_CoreStruct.gleVarConvolutionParameterfv;
		if(!__gleConvolutionParameterfv) bIsLoaded = 0;
	}
	__gleConvolutionParameteri = (PFNGLCONVOLUTIONPARAMETERIPROC)gleIntGetProcAddress("glConvolutionParameteri");
	if(!TestPointer(__gleConvolutionParameteri))
	{
		__gleConvolutionParameteri = gle_CoreStruct.gleVarConvolutionParameteri;
		if(!__gleConvolutionParameteri) bIsLoaded = 0;
	}
	__gleConvolutionParameteriv = (PFNGLCONVOLUTIONPARAMETERIVPROC)gleIntGetProcAddress("glConvolutionParameteriv");
	if(!TestPointer(__gleConvolutionParameteriv))
	{
		__gleConvolutionParameteriv = gle_CoreStruct.gleVarConvolutionParameteriv;
		if(!__gleConvolutionParameteriv) bIsLoaded = 0;
	}
	__gleCopyConvolutionFilter1D = (PFNGLCOPYCONVOLUTIONFILTER1DPROC)gleIntGetProcAddress("glCopyConvolutionFilter1D");
	if(!TestPointer(__gleCopyConvolutionFilter1D))
	{
		__gleCopyConvolutionFilter1D = gle_CoreStruct.gleVarCopyConvolutionFilter1D;
		if(!__gleCopyConvolutionFilter1D) bIsLoaded = 0;
	}
	__gleCopyConvolutionFilter2D = (PFNGLCOPYCONVOLUTIONFILTER2DPROC)gleIntGetProcAddress("glCopyConvolutionFilter2D");
	if(!TestPointer(__gleCopyConvolutionFilter2D))
	{
		__gleCopyConvolutionFilter2D = gle_CoreStruct.gleVarCopyConvolutionFilter2D;
		if(!__gleCopyConvolutionFilter2D) bIsLoaded = 0;
	}
	__gleGetConvolutionFilter = (PFNGLGETCONVOLUTIONFILTERPROC)gleIntGetProcAddress("glGetConvolutionFilter");
	if(!TestPointer(__gleGetConvolutionFilter))
	{
		__gleGetConvolutionFilter = gle_CoreStruct.gleVarGetConvolutionFilter;
		if(!__gleGetConvolutionFilter) bIsLoaded = 0;
	}
	__gleGetConvolutionParameterfv = (PFNGLGETCONVOLUTIONPARAMETERFVPROC)gleIntGetProcAddress("glGetConvolutionParameterfv");
	if(!TestPointer(__gleGetConvolutionParameterfv))
	{
		__gleGetConvolutionParameterfv = gle_CoreStruct.gleVarGetConvolutionParameterfv;
		if(!__gleGetConvolutionParameterfv) bIsLoaded = 0;
	}
	__gleGetConvolutionParameteriv = (PFNGLGETCONVOLUTIONPARAMETERIVPROC)gleIntGetProcAddress("glGetConvolutionParameteriv");
	if(!TestPointer(__gleGetConvolutionParameteriv))
	{
		__gleGetConvolutionParameteriv = gle_CoreStruct.gleVarGetConvolutionParameteriv;
		if(!__gleGetConvolutionParameteriv) bIsLoaded = 0;
	}
	__gleGetSeparableFilter = (PFNGLGETSEPARABLEFILTERPROC)gleIntGetProcAddress("glGetSeparableFilter");
	if(!TestPointer(__gleGetSeparableFilter))
	{
		__gleGetSeparableFilter = gle_CoreStruct.gleVarGetSeparableFilter;
		if(!__gleGetSeparableFilter) bIsLoaded = 0;
	}
	__gleSeparableFilter2D = (PFNGLSEPARABLEFILTER2DPROC)gleIntGetProcAddress("glSeparableFilter2D");
	if(!TestPointer(__gleSeparableFilter2D))
	{
		__gleSeparableFilter2D = gle_CoreStruct.gleVarSeparableFilter2D;
		if(!__gleSeparableFilter2D) bIsLoaded = 0;
	}
	__gleGetHistogram = (PFNGLGETHISTOGRAMPROC)gleIntGetProcAddress("glGetHistogram");
	if(!TestPointer(__gleGetHistogram))
	{
		__gleGetHistogram = gle_CoreStruct.gleVarGetHistogram;
		if(!__gleGetHistogram) bIsLoaded = 0;
	}
	__gleGetHistogramParameterfv = (PFNGLGETHISTOGRAMPARAMETERFVPROC)gleIntGetProcAddress("glGetHistogramParameterfv");
	if(!TestPointer(__gleGetHistogramParameterfv))
	{
		__gleGetHistogramParameterfv = gle_CoreStruct.gleVarGetHistogramParameterfv;
		if(!__gleGetHistogramParameterfv) bIsLoaded = 0;
	}
	__gleGetHistogramParameteriv = (PFNGLGETHISTOGRAMPARAMETERIVPROC)gleIntGetProcAddress("glGetHistogramParameteriv");
	if(!TestPointer(__gleGetHistogramParameteriv))
	{
		__gleGetHistogramParameteriv = gle_CoreStruct.gleVarGetHistogramParameteriv;
		if(!__gleGetHistogramParameteriv) bIsLoaded = 0;
	}
	__gleGetMinmax = (PFNGLGETMINMAXPROC)gleIntGetProcAddress("glGetMinmax");
	if(!TestPointer(__gleGetMinmax))
	{
		__gleGetMinmax = gle_CoreStruct.gleVarGetMinmax;
		if(!__gleGetMinmax) bIsLoaded = 0;
	}
	__gleGetMinmaxParameterfv = (PFNGLGETMINMAXPARAMETERFVPROC)gleIntGetProcAddress("glGetMinmaxParameterfv");
	if(!TestPointer(__gleGetMinmaxParameterfv))
	{
		__gleGetMinmaxParameterfv = gle_CoreStruct.gleVarGetMinmaxParameterfv;
		if(!__gleGetMinmaxParameterfv) bIsLoaded = 0;
	}
	__gleGetMinmaxParameteriv = (PFNGLGETMINMAXPARAMETERIVPROC)gleIntGetProcAddress("glGetMinmaxParameteriv");
	if(!TestPointer(__gleGetMinmaxParameteriv))
	{
		__gleGetMinmaxParameteriv = gle_CoreStruct.gleVarGetMinmaxParameteriv;
		if(!__gleGetMinmaxParameteriv) bIsLoaded = 0;
	}
	__gleHistogram = (PFNGLHISTOGRAMPROC)gleIntGetProcAddress("glHistogram");
	if(!TestPointer(__gleHistogram))
	{
		__gleHistogram = gle_CoreStruct.gleVarHistogram;
		if(!__gleHistogram) bIsLoaded = 0;
	}
	__gleMinmax = (PFNGLMINMAXPROC)gleIntGetProcAddress("glMinmax");
	if(!TestPointer(__gleMinmax))
	{
		__gleMinmax = gle_CoreStruct.gleVarMinmax;
		if(!__gleMinmax) bIsLoaded = 0;
	}
	__gleResetHistogram = (PFNGLRESETHISTOGRAMPROC)gleIntGetProcAddress("glResetHistogram");
	if(!TestPointer(__gleResetHistogram))
	{
		__gleResetHistogram = gle_CoreStruct.gleVarResetHistogram;
		if(!__gleResetHistogram) bIsLoaded = 0;
	}
	__gleResetMinmax = (PFNGLRESETMINMAXPROC)gleIntGetProcAddress("glResetMinmax");
	if(!TestPointer(__gleResetMinmax))
	{
		__gleResetMinmax = gle_CoreStruct.gleVarResetMinmax;
		if(!__gleResetMinmax) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_3_Base()
{
	int bIsLoaded = gleIntLoadCore_1_3_Version_3_1();
	__gleClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)gleIntGetProcAddress("glClientActiveTexture");
	if(!TestPointer(__gleClientActiveTexture))
	{
		__gleClientActiveTexture = gle_CoreStruct.gleVarClientActiveTexture;
		if(!__gleClientActiveTexture) bIsLoaded = 0;
	}
	__gleMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)gleIntGetProcAddress("glMultiTexCoord1d");
	if(!TestPointer(__gleMultiTexCoord1d))
	{
		__gleMultiTexCoord1d = gle_CoreStruct.gleVarMultiTexCoord1d;
		if(!__gleMultiTexCoord1d) bIsLoaded = 0;
	}
	__gleMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)gleIntGetProcAddress("glMultiTexCoord1dv");
	if(!TestPointer(__gleMultiTexCoord1dv))
	{
		__gleMultiTexCoord1dv = gle_CoreStruct.gleVarMultiTexCoord1dv;
		if(!__gleMultiTexCoord1dv) bIsLoaded = 0;
	}
	__gleMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)gleIntGetProcAddress("glMultiTexCoord1f");
	if(!TestPointer(__gleMultiTexCoord1f))
	{
		__gleMultiTexCoord1f = gle_CoreStruct.gleVarMultiTexCoord1f;
		if(!__gleMultiTexCoord1f) bIsLoaded = 0;
	}
	__gleMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)gleIntGetProcAddress("glMultiTexCoord1fv");
	if(!TestPointer(__gleMultiTexCoord1fv))
	{
		__gleMultiTexCoord1fv = gle_CoreStruct.gleVarMultiTexCoord1fv;
		if(!__gleMultiTexCoord1fv) bIsLoaded = 0;
	}
	__gleMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)gleIntGetProcAddress("glMultiTexCoord1i");
	if(!TestPointer(__gleMultiTexCoord1i))
	{
		__gleMultiTexCoord1i = gle_CoreStruct.gleVarMultiTexCoord1i;
		if(!__gleMultiTexCoord1i) bIsLoaded = 0;
	}
	__gleMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)gleIntGetProcAddress("glMultiTexCoord1iv");
	if(!TestPointer(__gleMultiTexCoord1iv))
	{
		__gleMultiTexCoord1iv = gle_CoreStruct.gleVarMultiTexCoord1iv;
		if(!__gleMultiTexCoord1iv) bIsLoaded = 0;
	}
	__gleMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)gleIntGetProcAddress("glMultiTexCoord1s");
	if(!TestPointer(__gleMultiTexCoord1s))
	{
		__gleMultiTexCoord1s = gle_CoreStruct.gleVarMultiTexCoord1s;
		if(!__gleMultiTexCoord1s) bIsLoaded = 0;
	}
	__gleMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)gleIntGetProcAddress("glMultiTexCoord1sv");
	if(!TestPointer(__gleMultiTexCoord1sv))
	{
		__gleMultiTexCoord1sv = gle_CoreStruct.gleVarMultiTexCoord1sv;
		if(!__gleMultiTexCoord1sv) bIsLoaded = 0;
	}
	__gleMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)gleIntGetProcAddress("glMultiTexCoord2d");
	if(!TestPointer(__gleMultiTexCoord2d))
	{
		__gleMultiTexCoord2d = gle_CoreStruct.gleVarMultiTexCoord2d;
		if(!__gleMultiTexCoord2d) bIsLoaded = 0;
	}
	__gleMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)gleIntGetProcAddress("glMultiTexCoord2dv");
	if(!TestPointer(__gleMultiTexCoord2dv))
	{
		__gleMultiTexCoord2dv = gle_CoreStruct.gleVarMultiTexCoord2dv;
		if(!__gleMultiTexCoord2dv) bIsLoaded = 0;
	}
	__gleMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)gleIntGetProcAddress("glMultiTexCoord2f");
	if(!TestPointer(__gleMultiTexCoord2f))
	{
		__gleMultiTexCoord2f = gle_CoreStruct.gleVarMultiTexCoord2f;
		if(!__gleMultiTexCoord2f) bIsLoaded = 0;
	}
	__gleMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)gleIntGetProcAddress("glMultiTexCoord2fv");
	if(!TestPointer(__gleMultiTexCoord2fv))
	{
		__gleMultiTexCoord2fv = gle_CoreStruct.gleVarMultiTexCoord2fv;
		if(!__gleMultiTexCoord2fv) bIsLoaded = 0;
	}
	__gleMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)gleIntGetProcAddress("glMultiTexCoord2i");
	if(!TestPointer(__gleMultiTexCoord2i))
	{
		__gleMultiTexCoord2i = gle_CoreStruct.gleVarMultiTexCoord2i;
		if(!__gleMultiTexCoord2i) bIsLoaded = 0;
	}
	__gleMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)gleIntGetProcAddress("glMultiTexCoord2iv");
	if(!TestPointer(__gleMultiTexCoord2iv))
	{
		__gleMultiTexCoord2iv = gle_CoreStruct.gleVarMultiTexCoord2iv;
		if(!__gleMultiTexCoord2iv) bIsLoaded = 0;
	}
	__gleMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)gleIntGetProcAddress("glMultiTexCoord2s");
	if(!TestPointer(__gleMultiTexCoord2s))
	{
		__gleMultiTexCoord2s = gle_CoreStruct.gleVarMultiTexCoord2s;
		if(!__gleMultiTexCoord2s) bIsLoaded = 0;
	}
	__gleMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)gleIntGetProcAddress("glMultiTexCoord2sv");
	if(!TestPointer(__gleMultiTexCoord2sv))
	{
		__gleMultiTexCoord2sv = gle_CoreStruct.gleVarMultiTexCoord2sv;
		if(!__gleMultiTexCoord2sv) bIsLoaded = 0;
	}
	__gleMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)gleIntGetProcAddress("glMultiTexCoord3d");
	if(!TestPointer(__gleMultiTexCoord3d))
	{
		__gleMultiTexCoord3d = gle_CoreStruct.gleVarMultiTexCoord3d;
		if(!__gleMultiTexCoord3d) bIsLoaded = 0;
	}
	__gleMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)gleIntGetProcAddress("glMultiTexCoord3dv");
	if(!TestPointer(__gleMultiTexCoord3dv))
	{
		__gleMultiTexCoord3dv = gle_CoreStruct.gleVarMultiTexCoord3dv;
		if(!__gleMultiTexCoord3dv) bIsLoaded = 0;
	}
	__gleMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)gleIntGetProcAddress("glMultiTexCoord3f");
	if(!TestPointer(__gleMultiTexCoord3f))
	{
		__gleMultiTexCoord3f = gle_CoreStruct.gleVarMultiTexCoord3f;
		if(!__gleMultiTexCoord3f) bIsLoaded = 0;
	}
	__gleMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)gleIntGetProcAddress("glMultiTexCoord3fv");
	if(!TestPointer(__gleMultiTexCoord3fv))
	{
		__gleMultiTexCoord3fv = gle_CoreStruct.gleVarMultiTexCoord3fv;
		if(!__gleMultiTexCoord3fv) bIsLoaded = 0;
	}
	__gleMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)gleIntGetProcAddress("glMultiTexCoord3i");
	if(!TestPointer(__gleMultiTexCoord3i))
	{
		__gleMultiTexCoord3i = gle_CoreStruct.gleVarMultiTexCoord3i;
		if(!__gleMultiTexCoord3i) bIsLoaded = 0;
	}
	__gleMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)gleIntGetProcAddress("glMultiTexCoord3iv");
	if(!TestPointer(__gleMultiTexCoord3iv))
	{
		__gleMultiTexCoord3iv = gle_CoreStruct.gleVarMultiTexCoord3iv;
		if(!__gleMultiTexCoord3iv) bIsLoaded = 0;
	}
	__gleMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)gleIntGetProcAddress("glMultiTexCoord3s");
	if(!TestPointer(__gleMultiTexCoord3s))
	{
		__gleMultiTexCoord3s = gle_CoreStruct.gleVarMultiTexCoord3s;
		if(!__gleMultiTexCoord3s) bIsLoaded = 0;
	}
	__gleMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)gleIntGetProcAddress("glMultiTexCoord3sv");
	if(!TestPointer(__gleMultiTexCoord3sv))
	{
		__gleMultiTexCoord3sv = gle_CoreStruct.gleVarMultiTexCoord3sv;
		if(!__gleMultiTexCoord3sv) bIsLoaded = 0;
	}
	__gleMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)gleIntGetProcAddress("glMultiTexCoord4d");
	if(!TestPointer(__gleMultiTexCoord4d))
	{
		__gleMultiTexCoord4d = gle_CoreStruct.gleVarMultiTexCoord4d;
		if(!__gleMultiTexCoord4d) bIsLoaded = 0;
	}
	__gleMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)gleIntGetProcAddress("glMultiTexCoord4dv");
	if(!TestPointer(__gleMultiTexCoord4dv))
	{
		__gleMultiTexCoord4dv = gle_CoreStruct.gleVarMultiTexCoord4dv;
		if(!__gleMultiTexCoord4dv) bIsLoaded = 0;
	}
	__gleMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)gleIntGetProcAddress("glMultiTexCoord4f");
	if(!TestPointer(__gleMultiTexCoord4f))
	{
		__gleMultiTexCoord4f = gle_CoreStruct.gleVarMultiTexCoord4f;
		if(!__gleMultiTexCoord4f) bIsLoaded = 0;
	}
	__gleMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)gleIntGetProcAddress("glMultiTexCoord4fv");
	if(!TestPointer(__gleMultiTexCoord4fv))
	{
		__gleMultiTexCoord4fv = gle_CoreStruct.gleVarMultiTexCoord4fv;
		if(!__gleMultiTexCoord4fv) bIsLoaded = 0;
	}
	__gleMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)gleIntGetProcAddress("glMultiTexCoord4i");
	if(!TestPointer(__gleMultiTexCoord4i))
	{
		__gleMultiTexCoord4i = gle_CoreStruct.gleVarMultiTexCoord4i;
		if(!__gleMultiTexCoord4i) bIsLoaded = 0;
	}
	__gleMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)gleIntGetProcAddress("glMultiTexCoord4iv");
	if(!TestPointer(__gleMultiTexCoord4iv))
	{
		__gleMultiTexCoord4iv = gle_CoreStruct.gleVarMultiTexCoord4iv;
		if(!__gleMultiTexCoord4iv) bIsLoaded = 0;
	}
	__gleMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)gleIntGetProcAddress("glMultiTexCoord4s");
	if(!TestPointer(__gleMultiTexCoord4s))
	{
		__gleMultiTexCoord4s = gle_CoreStruct.gleVarMultiTexCoord4s;
		if(!__gleMultiTexCoord4s) bIsLoaded = 0;
	}
	__gleMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)gleIntGetProcAddress("glMultiTexCoord4sv");
	if(!TestPointer(__gleMultiTexCoord4sv))
	{
		__gleMultiTexCoord4sv = gle_CoreStruct.gleVarMultiTexCoord4sv;
		if(!__gleMultiTexCoord4sv) bIsLoaded = 0;
	}
	__gleLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)gleIntGetProcAddress("glLoadTransposeMatrixf");
	if(!TestPointer(__gleLoadTransposeMatrixf))
	{
		__gleLoadTransposeMatrixf = gle_CoreStruct.gleVarLoadTransposeMatrixf;
		if(!__gleLoadTransposeMatrixf) bIsLoaded = 0;
	}
	__gleLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)gleIntGetProcAddress("glLoadTransposeMatrixd");
	if(!TestPointer(__gleLoadTransposeMatrixd))
	{
		__gleLoadTransposeMatrixd = gle_CoreStruct.gleVarLoadTransposeMatrixd;
		if(!__gleLoadTransposeMatrixd) bIsLoaded = 0;
	}
	__gleMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)gleIntGetProcAddress("glMultTransposeMatrixf");
	if(!TestPointer(__gleMultTransposeMatrixf))
	{
		__gleMultTransposeMatrixf = gle_CoreStruct.gleVarMultTransposeMatrixf;
		if(!__gleMultTransposeMatrixf) bIsLoaded = 0;
	}
	__gleMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)gleIntGetProcAddress("glMultTransposeMatrixd");
	if(!TestPointer(__gleMultTransposeMatrixd))
	{
		__gleMultTransposeMatrixd = gle_CoreStruct.gleVarMultTransposeMatrixd;
		if(!__gleMultTransposeMatrixd) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_4_Base()
{
	int bIsLoaded = gleIntLoadCore_1_4_Version_3_1();
	__gleFogCoordf = (PFNGLFOGCOORDFPROC)gleIntGetProcAddress("glFogCoordf");
	if(!TestPointer(__gleFogCoordf))
	{
		__gleFogCoordf = gle_CoreStruct.gleVarFogCoordf;
		if(!__gleFogCoordf) bIsLoaded = 0;
	}
	__gleFogCoordfv = (PFNGLFOGCOORDFVPROC)gleIntGetProcAddress("glFogCoordfv");
	if(!TestPointer(__gleFogCoordfv))
	{
		__gleFogCoordfv = gle_CoreStruct.gleVarFogCoordfv;
		if(!__gleFogCoordfv) bIsLoaded = 0;
	}
	__gleFogCoordd = (PFNGLFOGCOORDDPROC)gleIntGetProcAddress("glFogCoordd");
	if(!TestPointer(__gleFogCoordd))
	{
		__gleFogCoordd = gle_CoreStruct.gleVarFogCoordd;
		if(!__gleFogCoordd) bIsLoaded = 0;
	}
	__gleFogCoorddv = (PFNGLFOGCOORDDVPROC)gleIntGetProcAddress("glFogCoorddv");
	if(!TestPointer(__gleFogCoorddv))
	{
		__gleFogCoorddv = gle_CoreStruct.gleVarFogCoorddv;
		if(!__gleFogCoorddv) bIsLoaded = 0;
	}
	__gleFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)gleIntGetProcAddress("glFogCoordPointer");
	if(!TestPointer(__gleFogCoordPointer))
	{
		__gleFogCoordPointer = gle_CoreStruct.gleVarFogCoordPointer;
		if(!__gleFogCoordPointer) bIsLoaded = 0;
	}
	__gleSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)gleIntGetProcAddress("glSecondaryColor3b");
	if(!TestPointer(__gleSecondaryColor3b))
	{
		__gleSecondaryColor3b = gle_CoreStruct.gleVarSecondaryColor3b;
		if(!__gleSecondaryColor3b) bIsLoaded = 0;
	}
	__gleSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)gleIntGetProcAddress("glSecondaryColor3bv");
	if(!TestPointer(__gleSecondaryColor3bv))
	{
		__gleSecondaryColor3bv = gle_CoreStruct.gleVarSecondaryColor3bv;
		if(!__gleSecondaryColor3bv) bIsLoaded = 0;
	}
	__gleSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)gleIntGetProcAddress("glSecondaryColor3d");
	if(!TestPointer(__gleSecondaryColor3d))
	{
		__gleSecondaryColor3d = gle_CoreStruct.gleVarSecondaryColor3d;
		if(!__gleSecondaryColor3d) bIsLoaded = 0;
	}
	__gleSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)gleIntGetProcAddress("glSecondaryColor3dv");
	if(!TestPointer(__gleSecondaryColor3dv))
	{
		__gleSecondaryColor3dv = gle_CoreStruct.gleVarSecondaryColor3dv;
		if(!__gleSecondaryColor3dv) bIsLoaded = 0;
	}
	__gleSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)gleIntGetProcAddress("glSecondaryColor3f");
	if(!TestPointer(__gleSecondaryColor3f))
	{
		__gleSecondaryColor3f = gle_CoreStruct.gleVarSecondaryColor3f;
		if(!__gleSecondaryColor3f) bIsLoaded = 0;
	}
	__gleSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)gleIntGetProcAddress("glSecondaryColor3fv");
	if(!TestPointer(__gleSecondaryColor3fv))
	{
		__gleSecondaryColor3fv = gle_CoreStruct.gleVarSecondaryColor3fv;
		if(!__gleSecondaryColor3fv) bIsLoaded = 0;
	}
	__gleSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)gleIntGetProcAddress("glSecondaryColor3i");
	if(!TestPointer(__gleSecondaryColor3i))
	{
		__gleSecondaryColor3i = gle_CoreStruct.gleVarSecondaryColor3i;
		if(!__gleSecondaryColor3i) bIsLoaded = 0;
	}
	__gleSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)gleIntGetProcAddress("glSecondaryColor3iv");
	if(!TestPointer(__gleSecondaryColor3iv))
	{
		__gleSecondaryColor3iv = gle_CoreStruct.gleVarSecondaryColor3iv;
		if(!__gleSecondaryColor3iv) bIsLoaded = 0;
	}
	__gleSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)gleIntGetProcAddress("glSecondaryColor3s");
	if(!TestPointer(__gleSecondaryColor3s))
	{
		__gleSecondaryColor3s = gle_CoreStruct.gleVarSecondaryColor3s;
		if(!__gleSecondaryColor3s) bIsLoaded = 0;
	}
	__gleSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)gleIntGetProcAddress("glSecondaryColor3sv");
	if(!TestPointer(__gleSecondaryColor3sv))
	{
		__gleSecondaryColor3sv = gle_CoreStruct.gleVarSecondaryColor3sv;
		if(!__gleSecondaryColor3sv) bIsLoaded = 0;
	}
	__gleSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)gleIntGetProcAddress("glSecondaryColor3ub");
	if(!TestPointer(__gleSecondaryColor3ub))
	{
		__gleSecondaryColor3ub = gle_CoreStruct.gleVarSecondaryColor3ub;
		if(!__gleSecondaryColor3ub) bIsLoaded = 0;
	}
	__gleSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)gleIntGetProcAddress("glSecondaryColor3ubv");
	if(!TestPointer(__gleSecondaryColor3ubv))
	{
		__gleSecondaryColor3ubv = gle_CoreStruct.gleVarSecondaryColor3ubv;
		if(!__gleSecondaryColor3ubv) bIsLoaded = 0;
	}
	__gleSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)gleIntGetProcAddress("glSecondaryColor3ui");
	if(!TestPointer(__gleSecondaryColor3ui))
	{
		__gleSecondaryColor3ui = gle_CoreStruct.gleVarSecondaryColor3ui;
		if(!__gleSecondaryColor3ui) bIsLoaded = 0;
	}
	__gleSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)gleIntGetProcAddress("glSecondaryColor3uiv");
	if(!TestPointer(__gleSecondaryColor3uiv))
	{
		__gleSecondaryColor3uiv = gle_CoreStruct.gleVarSecondaryColor3uiv;
		if(!__gleSecondaryColor3uiv) bIsLoaded = 0;
	}
	__gleSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)gleIntGetProcAddress("glSecondaryColor3us");
	if(!TestPointer(__gleSecondaryColor3us))
	{
		__gleSecondaryColor3us = gle_CoreStruct.gleVarSecondaryColor3us;
		if(!__gleSecondaryColor3us) bIsLoaded = 0;
	}
	__gleSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)gleIntGetProcAddress("glSecondaryColor3usv");
	if(!TestPointer(__gleSecondaryColor3usv))
	{
		__gleSecondaryColor3usv = gle_CoreStruct.gleVarSecondaryColor3usv;
		if(!__gleSecondaryColor3usv) bIsLoaded = 0;
	}
	__gleSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)gleIntGetProcAddress("glSecondaryColorPointer");
	if(!TestPointer(__gleSecondaryColorPointer))
	{
		__gleSecondaryColorPointer = gle_CoreStruct.gleVarSecondaryColorPointer;
		if(!__gleSecondaryColorPointer) bIsLoaded = 0;
	}
	__gleWindowPos2d = (PFNGLWINDOWPOS2DPROC)gleIntGetProcAddress("glWindowPos2d");
	if(!TestPointer(__gleWindowPos2d))
	{
		__gleWindowPos2d = gle_CoreStruct.gleVarWindowPos2d;
		if(!__gleWindowPos2d) bIsLoaded = 0;
	}
	__gleWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)gleIntGetProcAddress("glWindowPos2dv");
	if(!TestPointer(__gleWindowPos2dv))
	{
		__gleWindowPos2dv = gle_CoreStruct.gleVarWindowPos2dv;
		if(!__gleWindowPos2dv) bIsLoaded = 0;
	}
	__gleWindowPos2f = (PFNGLWINDOWPOS2FPROC)gleIntGetProcAddress("glWindowPos2f");
	if(!TestPointer(__gleWindowPos2f))
	{
		__gleWindowPos2f = gle_CoreStruct.gleVarWindowPos2f;
		if(!__gleWindowPos2f) bIsLoaded = 0;
	}
	__gleWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)gleIntGetProcAddress("glWindowPos2fv");
	if(!TestPointer(__gleWindowPos2fv))
	{
		__gleWindowPos2fv = gle_CoreStruct.gleVarWindowPos2fv;
		if(!__gleWindowPos2fv) bIsLoaded = 0;
	}
	__gleWindowPos2i = (PFNGLWINDOWPOS2IPROC)gleIntGetProcAddress("glWindowPos2i");
	if(!TestPointer(__gleWindowPos2i))
	{
		__gleWindowPos2i = gle_CoreStruct.gleVarWindowPos2i;
		if(!__gleWindowPos2i) bIsLoaded = 0;
	}
	__gleWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)gleIntGetProcAddress("glWindowPos2iv");
	if(!TestPointer(__gleWindowPos2iv))
	{
		__gleWindowPos2iv = gle_CoreStruct.gleVarWindowPos2iv;
		if(!__gleWindowPos2iv) bIsLoaded = 0;
	}
	__gleWindowPos2s = (PFNGLWINDOWPOS2SPROC)gleIntGetProcAddress("glWindowPos2s");
	if(!TestPointer(__gleWindowPos2s))
	{
		__gleWindowPos2s = gle_CoreStruct.gleVarWindowPos2s;
		if(!__gleWindowPos2s) bIsLoaded = 0;
	}
	__gleWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)gleIntGetProcAddress("glWindowPos2sv");
	if(!TestPointer(__gleWindowPos2sv))
	{
		__gleWindowPos2sv = gle_CoreStruct.gleVarWindowPos2sv;
		if(!__gleWindowPos2sv) bIsLoaded = 0;
	}
	__gleWindowPos3d = (PFNGLWINDOWPOS3DPROC)gleIntGetProcAddress("glWindowPos3d");
	if(!TestPointer(__gleWindowPos3d))
	{
		__gleWindowPos3d = gle_CoreStruct.gleVarWindowPos3d;
		if(!__gleWindowPos3d) bIsLoaded = 0;
	}
	__gleWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)gleIntGetProcAddress("glWindowPos3dv");
	if(!TestPointer(__gleWindowPos3dv))
	{
		__gleWindowPos3dv = gle_CoreStruct.gleVarWindowPos3dv;
		if(!__gleWindowPos3dv) bIsLoaded = 0;
	}
	__gleWindowPos3f = (PFNGLWINDOWPOS3FPROC)gleIntGetProcAddress("glWindowPos3f");
	if(!TestPointer(__gleWindowPos3f))
	{
		__gleWindowPos3f = gle_CoreStruct.gleVarWindowPos3f;
		if(!__gleWindowPos3f) bIsLoaded = 0;
	}
	__gleWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)gleIntGetProcAddress("glWindowPos3fv");
	if(!TestPointer(__gleWindowPos3fv))
	{
		__gleWindowPos3fv = gle_CoreStruct.gleVarWindowPos3fv;
		if(!__gleWindowPos3fv) bIsLoaded = 0;
	}
	__gleWindowPos3i = (PFNGLWINDOWPOS3IPROC)gleIntGetProcAddress("glWindowPos3i");
	if(!TestPointer(__gleWindowPos3i))
	{
		__gleWindowPos3i = gle_CoreStruct.gleVarWindowPos3i;
		if(!__gleWindowPos3i) bIsLoaded = 0;
	}
	__gleWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)gleIntGetProcAddress("glWindowPos3iv");
	if(!TestPointer(__gleWindowPos3iv))
	{
		__gleWindowPos3iv = gle_CoreStruct.gleVarWindowPos3iv;
		if(!__gleWindowPos3iv) bIsLoaded = 0;
	}
	__gleWindowPos3s = (PFNGLWINDOWPOS3SPROC)gleIntGetProcAddress("glWindowPos3s");
	if(!TestPointer(__gleWindowPos3s))
	{
		__gleWindowPos3s = gle_CoreStruct.gleVarWindowPos3s;
		if(!__gleWindowPos3s) bIsLoaded = 0;
	}
	__gleWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)gleIntGetProcAddress("glWindowPos3sv");
	if(!TestPointer(__gleWindowPos3sv))
	{
		__gleWindowPos3sv = gle_CoreStruct.gleVarWindowPos3sv;
		if(!__gleWindowPos3sv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_1_5_Base()
{
	int bIsLoaded = gleIntLoadCore_1_5_Version_3_1();
	return bIsLoaded;
}

static int gleIntLoadCore_2_0_Base()
{
	int bIsLoaded = gleIntLoadCore_2_0_Version_3_1();
	__gleVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)gleIntGetProcAddress("glVertexAttrib1d");
	if(!TestPointer(__gleVertexAttrib1d))
	{
		__gleVertexAttrib1d = gle_CoreStruct.gleVarVertexAttrib1d;
		if(!__gleVertexAttrib1d) bIsLoaded = 0;
	}
	__gleVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)gleIntGetProcAddress("glVertexAttrib1dv");
	if(!TestPointer(__gleVertexAttrib1dv))
	{
		__gleVertexAttrib1dv = gle_CoreStruct.gleVarVertexAttrib1dv;
		if(!__gleVertexAttrib1dv) bIsLoaded = 0;
	}
	__gleVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)gleIntGetProcAddress("glVertexAttrib1f");
	if(!TestPointer(__gleVertexAttrib1f))
	{
		__gleVertexAttrib1f = gle_CoreStruct.gleVarVertexAttrib1f;
		if(!__gleVertexAttrib1f) bIsLoaded = 0;
	}
	__gleVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)gleIntGetProcAddress("glVertexAttrib1fv");
	if(!TestPointer(__gleVertexAttrib1fv))
	{
		__gleVertexAttrib1fv = gle_CoreStruct.gleVarVertexAttrib1fv;
		if(!__gleVertexAttrib1fv) bIsLoaded = 0;
	}
	__gleVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)gleIntGetProcAddress("glVertexAttrib1s");
	if(!TestPointer(__gleVertexAttrib1s))
	{
		__gleVertexAttrib1s = gle_CoreStruct.gleVarVertexAttrib1s;
		if(!__gleVertexAttrib1s) bIsLoaded = 0;
	}
	__gleVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)gleIntGetProcAddress("glVertexAttrib1sv");
	if(!TestPointer(__gleVertexAttrib1sv))
	{
		__gleVertexAttrib1sv = gle_CoreStruct.gleVarVertexAttrib1sv;
		if(!__gleVertexAttrib1sv) bIsLoaded = 0;
	}
	__gleVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)gleIntGetProcAddress("glVertexAttrib2d");
	if(!TestPointer(__gleVertexAttrib2d))
	{
		__gleVertexAttrib2d = gle_CoreStruct.gleVarVertexAttrib2d;
		if(!__gleVertexAttrib2d) bIsLoaded = 0;
	}
	__gleVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)gleIntGetProcAddress("glVertexAttrib2dv");
	if(!TestPointer(__gleVertexAttrib2dv))
	{
		__gleVertexAttrib2dv = gle_CoreStruct.gleVarVertexAttrib2dv;
		if(!__gleVertexAttrib2dv) bIsLoaded = 0;
	}
	__gleVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)gleIntGetProcAddress("glVertexAttrib2f");
	if(!TestPointer(__gleVertexAttrib2f))
	{
		__gleVertexAttrib2f = gle_CoreStruct.gleVarVertexAttrib2f;
		if(!__gleVertexAttrib2f) bIsLoaded = 0;
	}
	__gleVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)gleIntGetProcAddress("glVertexAttrib2fv");
	if(!TestPointer(__gleVertexAttrib2fv))
	{
		__gleVertexAttrib2fv = gle_CoreStruct.gleVarVertexAttrib2fv;
		if(!__gleVertexAttrib2fv) bIsLoaded = 0;
	}
	__gleVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)gleIntGetProcAddress("glVertexAttrib2s");
	if(!TestPointer(__gleVertexAttrib2s))
	{
		__gleVertexAttrib2s = gle_CoreStruct.gleVarVertexAttrib2s;
		if(!__gleVertexAttrib2s) bIsLoaded = 0;
	}
	__gleVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)gleIntGetProcAddress("glVertexAttrib2sv");
	if(!TestPointer(__gleVertexAttrib2sv))
	{
		__gleVertexAttrib2sv = gle_CoreStruct.gleVarVertexAttrib2sv;
		if(!__gleVertexAttrib2sv) bIsLoaded = 0;
	}
	__gleVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)gleIntGetProcAddress("glVertexAttrib3d");
	if(!TestPointer(__gleVertexAttrib3d))
	{
		__gleVertexAttrib3d = gle_CoreStruct.gleVarVertexAttrib3d;
		if(!__gleVertexAttrib3d) bIsLoaded = 0;
	}
	__gleVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)gleIntGetProcAddress("glVertexAttrib3dv");
	if(!TestPointer(__gleVertexAttrib3dv))
	{
		__gleVertexAttrib3dv = gle_CoreStruct.gleVarVertexAttrib3dv;
		if(!__gleVertexAttrib3dv) bIsLoaded = 0;
	}
	__gleVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)gleIntGetProcAddress("glVertexAttrib3f");
	if(!TestPointer(__gleVertexAttrib3f))
	{
		__gleVertexAttrib3f = gle_CoreStruct.gleVarVertexAttrib3f;
		if(!__gleVertexAttrib3f) bIsLoaded = 0;
	}
	__gleVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)gleIntGetProcAddress("glVertexAttrib3fv");
	if(!TestPointer(__gleVertexAttrib3fv))
	{
		__gleVertexAttrib3fv = gle_CoreStruct.gleVarVertexAttrib3fv;
		if(!__gleVertexAttrib3fv) bIsLoaded = 0;
	}
	__gleVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)gleIntGetProcAddress("glVertexAttrib3s");
	if(!TestPointer(__gleVertexAttrib3s))
	{
		__gleVertexAttrib3s = gle_CoreStruct.gleVarVertexAttrib3s;
		if(!__gleVertexAttrib3s) bIsLoaded = 0;
	}
	__gleVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)gleIntGetProcAddress("glVertexAttrib3sv");
	if(!TestPointer(__gleVertexAttrib3sv))
	{
		__gleVertexAttrib3sv = gle_CoreStruct.gleVarVertexAttrib3sv;
		if(!__gleVertexAttrib3sv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)gleIntGetProcAddress("glVertexAttrib4Nbv");
	if(!TestPointer(__gleVertexAttrib4Nbv))
	{
		__gleVertexAttrib4Nbv = gle_CoreStruct.gleVarVertexAttrib4Nbv;
		if(!__gleVertexAttrib4Nbv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)gleIntGetProcAddress("glVertexAttrib4Niv");
	if(!TestPointer(__gleVertexAttrib4Niv))
	{
		__gleVertexAttrib4Niv = gle_CoreStruct.gleVarVertexAttrib4Niv;
		if(!__gleVertexAttrib4Niv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)gleIntGetProcAddress("glVertexAttrib4Nsv");
	if(!TestPointer(__gleVertexAttrib4Nsv))
	{
		__gleVertexAttrib4Nsv = gle_CoreStruct.gleVarVertexAttrib4Nsv;
		if(!__gleVertexAttrib4Nsv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)gleIntGetProcAddress("glVertexAttrib4Nub");
	if(!TestPointer(__gleVertexAttrib4Nub))
	{
		__gleVertexAttrib4Nub = gle_CoreStruct.gleVarVertexAttrib4Nub;
		if(!__gleVertexAttrib4Nub) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)gleIntGetProcAddress("glVertexAttrib4Nubv");
	if(!TestPointer(__gleVertexAttrib4Nubv))
	{
		__gleVertexAttrib4Nubv = gle_CoreStruct.gleVarVertexAttrib4Nubv;
		if(!__gleVertexAttrib4Nubv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)gleIntGetProcAddress("glVertexAttrib4Nuiv");
	if(!TestPointer(__gleVertexAttrib4Nuiv))
	{
		__gleVertexAttrib4Nuiv = gle_CoreStruct.gleVarVertexAttrib4Nuiv;
		if(!__gleVertexAttrib4Nuiv) bIsLoaded = 0;
	}
	__gleVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)gleIntGetProcAddress("glVertexAttrib4Nusv");
	if(!TestPointer(__gleVertexAttrib4Nusv))
	{
		__gleVertexAttrib4Nusv = gle_CoreStruct.gleVarVertexAttrib4Nusv;
		if(!__gleVertexAttrib4Nusv) bIsLoaded = 0;
	}
	__gleVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)gleIntGetProcAddress("glVertexAttrib4bv");
	if(!TestPointer(__gleVertexAttrib4bv))
	{
		__gleVertexAttrib4bv = gle_CoreStruct.gleVarVertexAttrib4bv;
		if(!__gleVertexAttrib4bv) bIsLoaded = 0;
	}
	__gleVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)gleIntGetProcAddress("glVertexAttrib4d");
	if(!TestPointer(__gleVertexAttrib4d))
	{
		__gleVertexAttrib4d = gle_CoreStruct.gleVarVertexAttrib4d;
		if(!__gleVertexAttrib4d) bIsLoaded = 0;
	}
	__gleVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)gleIntGetProcAddress("glVertexAttrib4dv");
	if(!TestPointer(__gleVertexAttrib4dv))
	{
		__gleVertexAttrib4dv = gle_CoreStruct.gleVarVertexAttrib4dv;
		if(!__gleVertexAttrib4dv) bIsLoaded = 0;
	}
	__gleVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)gleIntGetProcAddress("glVertexAttrib4f");
	if(!TestPointer(__gleVertexAttrib4f))
	{
		__gleVertexAttrib4f = gle_CoreStruct.gleVarVertexAttrib4f;
		if(!__gleVertexAttrib4f) bIsLoaded = 0;
	}
	__gleVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)gleIntGetProcAddress("glVertexAttrib4fv");
	if(!TestPointer(__gleVertexAttrib4fv))
	{
		__gleVertexAttrib4fv = gle_CoreStruct.gleVarVertexAttrib4fv;
		if(!__gleVertexAttrib4fv) bIsLoaded = 0;
	}
	__gleVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)gleIntGetProcAddress("glVertexAttrib4iv");
	if(!TestPointer(__gleVertexAttrib4iv))
	{
		__gleVertexAttrib4iv = gle_CoreStruct.gleVarVertexAttrib4iv;
		if(!__gleVertexAttrib4iv) bIsLoaded = 0;
	}
	__gleVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)gleIntGetProcAddress("glVertexAttrib4s");
	if(!TestPointer(__gleVertexAttrib4s))
	{
		__gleVertexAttrib4s = gle_CoreStruct.gleVarVertexAttrib4s;
		if(!__gleVertexAttrib4s) bIsLoaded = 0;
	}
	__gleVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)gleIntGetProcAddress("glVertexAttrib4sv");
	if(!TestPointer(__gleVertexAttrib4sv))
	{
		__gleVertexAttrib4sv = gle_CoreStruct.gleVarVertexAttrib4sv;
		if(!__gleVertexAttrib4sv) bIsLoaded = 0;
	}
	__gleVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)gleIntGetProcAddress("glVertexAttrib4ubv");
	if(!TestPointer(__gleVertexAttrib4ubv))
	{
		__gleVertexAttrib4ubv = gle_CoreStruct.gleVarVertexAttrib4ubv;
		if(!__gleVertexAttrib4ubv) bIsLoaded = 0;
	}
	__gleVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)gleIntGetProcAddress("glVertexAttrib4uiv");
	if(!TestPointer(__gleVertexAttrib4uiv))
	{
		__gleVertexAttrib4uiv = gle_CoreStruct.gleVarVertexAttrib4uiv;
		if(!__gleVertexAttrib4uiv) bIsLoaded = 0;
	}
	__gleVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)gleIntGetProcAddress("glVertexAttrib4usv");
	if(!TestPointer(__gleVertexAttrib4usv))
	{
		__gleVertexAttrib4usv = gle_CoreStruct.gleVarVertexAttrib4usv;
		if(!__gleVertexAttrib4usv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_2_1_Base()
{
	int bIsLoaded = gleIntLoadCore_2_1_Version_3_1();
	return bIsLoaded;
}

static int gleIntLoadCore_3_0_Base()
{
	int bIsLoaded = gleIntLoadCore_3_0_Version_3_1();
	__gleVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)gleIntGetProcAddress("glVertexAttribI1i");
	if(!TestPointer(__gleVertexAttribI1i))
	{
		__gleVertexAttribI1i = gle_CoreStruct.gleVarVertexAttribI1i;
		if(!__gleVertexAttribI1i) bIsLoaded = 0;
	}
	__gleVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)gleIntGetProcAddress("glVertexAttribI2i");
	if(!TestPointer(__gleVertexAttribI2i))
	{
		__gleVertexAttribI2i = gle_CoreStruct.gleVarVertexAttribI2i;
		if(!__gleVertexAttribI2i) bIsLoaded = 0;
	}
	__gleVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)gleIntGetProcAddress("glVertexAttribI3i");
	if(!TestPointer(__gleVertexAttribI3i))
	{
		__gleVertexAttribI3i = gle_CoreStruct.gleVarVertexAttribI3i;
		if(!__gleVertexAttribI3i) bIsLoaded = 0;
	}
	__gleVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)gleIntGetProcAddress("glVertexAttribI4i");
	if(!TestPointer(__gleVertexAttribI4i))
	{
		__gleVertexAttribI4i = gle_CoreStruct.gleVarVertexAttribI4i;
		if(!__gleVertexAttribI4i) bIsLoaded = 0;
	}
	__gleVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)gleIntGetProcAddress("glVertexAttribI1ui");
	if(!TestPointer(__gleVertexAttribI1ui))
	{
		__gleVertexAttribI1ui = gle_CoreStruct.gleVarVertexAttribI1ui;
		if(!__gleVertexAttribI1ui) bIsLoaded = 0;
	}
	__gleVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)gleIntGetProcAddress("glVertexAttribI2ui");
	if(!TestPointer(__gleVertexAttribI2ui))
	{
		__gleVertexAttribI2ui = gle_CoreStruct.gleVarVertexAttribI2ui;
		if(!__gleVertexAttribI2ui) bIsLoaded = 0;
	}
	__gleVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)gleIntGetProcAddress("glVertexAttribI3ui");
	if(!TestPointer(__gleVertexAttribI3ui))
	{
		__gleVertexAttribI3ui = gle_CoreStruct.gleVarVertexAttribI3ui;
		if(!__gleVertexAttribI3ui) bIsLoaded = 0;
	}
	__gleVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)gleIntGetProcAddress("glVertexAttribI4ui");
	if(!TestPointer(__gleVertexAttribI4ui))
	{
		__gleVertexAttribI4ui = gle_CoreStruct.gleVarVertexAttribI4ui;
		if(!__gleVertexAttribI4ui) bIsLoaded = 0;
	}
	__gleVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)gleIntGetProcAddress("glVertexAttribI1iv");
	if(!TestPointer(__gleVertexAttribI1iv))
	{
		__gleVertexAttribI1iv = gle_CoreStruct.gleVarVertexAttribI1iv;
		if(!__gleVertexAttribI1iv) bIsLoaded = 0;
	}
	__gleVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)gleIntGetProcAddress("glVertexAttribI2iv");
	if(!TestPointer(__gleVertexAttribI2iv))
	{
		__gleVertexAttribI2iv = gle_CoreStruct.gleVarVertexAttribI2iv;
		if(!__gleVertexAttribI2iv) bIsLoaded = 0;
	}
	__gleVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)gleIntGetProcAddress("glVertexAttribI3iv");
	if(!TestPointer(__gleVertexAttribI3iv))
	{
		__gleVertexAttribI3iv = gle_CoreStruct.gleVarVertexAttribI3iv;
		if(!__gleVertexAttribI3iv) bIsLoaded = 0;
	}
	__gleVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)gleIntGetProcAddress("glVertexAttribI4iv");
	if(!TestPointer(__gleVertexAttribI4iv))
	{
		__gleVertexAttribI4iv = gle_CoreStruct.gleVarVertexAttribI4iv;
		if(!__gleVertexAttribI4iv) bIsLoaded = 0;
	}
	__gleVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)gleIntGetProcAddress("glVertexAttribI1uiv");
	if(!TestPointer(__gleVertexAttribI1uiv))
	{
		__gleVertexAttribI1uiv = gle_CoreStruct.gleVarVertexAttribI1uiv;
		if(!__gleVertexAttribI1uiv) bIsLoaded = 0;
	}
	__gleVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)gleIntGetProcAddress("glVertexAttribI2uiv");
	if(!TestPointer(__gleVertexAttribI2uiv))
	{
		__gleVertexAttribI2uiv = gle_CoreStruct.gleVarVertexAttribI2uiv;
		if(!__gleVertexAttribI2uiv) bIsLoaded = 0;
	}
	__gleVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)gleIntGetProcAddress("glVertexAttribI3uiv");
	if(!TestPointer(__gleVertexAttribI3uiv))
	{
		__gleVertexAttribI3uiv = gle_CoreStruct.gleVarVertexAttribI3uiv;
		if(!__gleVertexAttribI3uiv) bIsLoaded = 0;
	}
	__gleVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)gleIntGetProcAddress("glVertexAttribI4uiv");
	if(!TestPointer(__gleVertexAttribI4uiv))
	{
		__gleVertexAttribI4uiv = gle_CoreStruct.gleVarVertexAttribI4uiv;
		if(!__gleVertexAttribI4uiv) bIsLoaded = 0;
	}
	__gleVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)gleIntGetProcAddress("glVertexAttribI4bv");
	if(!TestPointer(__gleVertexAttribI4bv))
	{
		__gleVertexAttribI4bv = gle_CoreStruct.gleVarVertexAttribI4bv;
		if(!__gleVertexAttribI4bv) bIsLoaded = 0;
	}
	__gleVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)gleIntGetProcAddress("glVertexAttribI4sv");
	if(!TestPointer(__gleVertexAttribI4sv))
	{
		__gleVertexAttribI4sv = gle_CoreStruct.gleVarVertexAttribI4sv;
		if(!__gleVertexAttribI4sv) bIsLoaded = 0;
	}
	__gleVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)gleIntGetProcAddress("glVertexAttribI4ubv");
	if(!TestPointer(__gleVertexAttribI4ubv))
	{
		__gleVertexAttribI4ubv = gle_CoreStruct.gleVarVertexAttribI4ubv;
		if(!__gleVertexAttribI4ubv) bIsLoaded = 0;
	}
	__gleVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)gleIntGetProcAddress("glVertexAttribI4usv");
	if(!TestPointer(__gleVertexAttribI4usv))
	{
		__gleVertexAttribI4usv = gle_CoreStruct.gleVarVertexAttribI4usv;
		if(!__gleVertexAttribI4usv) bIsLoaded = 0;
	}
	return bIsLoaded;
}

static int gleIntLoadCore_3_1_Base()
{
	int bIsLoaded = 1;
	__gleDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)gleIntGetProcAddress("glDrawArraysInstanced");
	if(!TestPointer(__gleDrawArraysInstanced))
	{
		__gleDrawArraysInstanced = gle_CoreStruct.gleVarDrawArraysInstanced;
		if(!__gleDrawArraysInstanced) bIsLoaded = 0;
	}
	__gleDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)gleIntGetProcAddress("glDrawElementsInstanced");
	if(!TestPointer(__gleDrawElementsInstanced))
	{
		__gleDrawElementsInstanced = gle_CoreStruct.gleVarDrawElementsInstanced;
		if(!__gleDrawElementsInstanced) bIsLoaded = 0;
	}
	__gleTexBuffer = (PFNGLTEXBUFFERPROC)gleIntGetProcAddress("glTexBuffer");
	if(!TestPointer(__gleTexBuffer))
	{
		__gleTexBuffer = gle_CoreStruct.gleVarTexBuffer;
		if(!__gleTexBuffer) bIsLoaded = 0;
	}
	__glePrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)gleIntGetProcAddress("glPrimitiveRestartIndex");
	if(!TestPointer(__glePrimitiveRestartIndex))
	{
		__glePrimitiveRestartIndex = gle_CoreStruct.gleVarPrimitiveRestartIndex;
		if(!__glePrimitiveRestartIndex) bIsLoaded = 0;
	}
	__gleGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)gleIntGetProcAddress("glGetUniformIndices");
	if(!TestPointer(__gleGetUniformIndices))
	{
		__gleGetUniformIndices = gle_CoreStruct.gleVarGetUniformIndices;
		if(!__gleGetUniformIndices) bIsLoaded = 0;
	}
	__gleGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)gleIntGetProcAddress("glGetActiveUniformsiv");
	if(!TestPointer(__gleGetActiveUniformsiv))
	{
		__gleGetActiveUniformsiv = gle_CoreStruct.gleVarGetActiveUniformsiv;
		if(!__gleGetActiveUniformsiv) bIsLoaded = 0;
	}
	__gleGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)gleIntGetProcAddress("glGetActiveUniformName");
	if(!TestPointer(__gleGetActiveUniformName))
	{
		__gleGetActiveUniformName = gle_CoreStruct.gleVarGetActiveUniformName;
		if(!__gleGetActiveUniformName) bIsLoaded = 0;
	}
	__gleGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)gleIntGetProcAddress("glGetUniformBlockIndex");
	if(!TestPointer(__gleGetUniformBlockIndex))
	{
		__gleGetUniformBlockIndex = gle_CoreStruct.gleVarGetUniformBlockIndex;
		if(!__gleGetUniformBlockIndex) bIsLoaded = 0;
	}
	__gleGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)gleIntGetProcAddress("glGetActiveUniformBlockiv");
	if(!TestPointer(__gleGetActiveUniformBlockiv))
	{
		__gleGetActiveUniformBlockiv = gle_CoreStruct.gleVarGetActiveUniformBlockiv;
		if(!__gleGetActiveUniformBlockiv) bIsLoaded = 0;
	}
	__gleGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)gleIntGetProcAddress("glGetActiveUniformBlockName");
	if(!TestPointer(__gleGetActiveUniformBlockName))
	{
		__gleGetActiveUniformBlockName = gle_CoreStruct.gleVarGetActiveUniformBlockName;
		if(!__gleGetActiveUniformBlockName) bIsLoaded = 0;
	}
	__gleUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)gleIntGetProcAddress("glUniformBlockBinding");
	if(!TestPointer(__gleUniformBlockBinding))
	{
		__gleUniformBlockBinding = gle_CoreStruct.gleVarUniformBlockBinding;
		if(!__gleUniformBlockBinding) bIsLoaded = 0;
	}
	glext_ARB_uniform_buffer_object = 1;
	__gleCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)gleIntGetProcAddress("glCopyBufferSubData");
	if(!TestPointer(__gleCopyBufferSubData))
	{
		__gleCopyBufferSubData = gle_CoreStruct.gleVarCopyBufferSubData;
		if(!__gleCopyBufferSubData) bIsLoaded = 0;
	}
	glext_ARB_copy_buffer = 1;
	return bIsLoaded;
}

static int gleIntLoadCore_3_2_Base()
{
	int bIsLoaded = 1;
	__gleGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)gleIntGetProcAddress("glGetInteger64i_v");
	if(!TestPointer(__gleGetInteger64i_v))
	{
		__gleGetInteger64i_v = gle_CoreStruct.gleVarGetInteger64i_v;
		if(!__gleGetInteger64i_v) bIsLoaded = 0;
	}
	__gleGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)gleIntGetProcAddress("glGetBufferParameteri64v");
	if(!TestPointer(__gleGetBufferParameteri64v))
	{
		__gleGetBufferParameteri64v = gle_CoreStruct.gleVarGetBufferParameteri64v;
		if(!__gleGetBufferParameteri64v) bIsLoaded = 0;
	}
	__gleFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)gleIntGetProcAddress("glFramebufferTexture");
	if(!TestPointer(__gleFramebufferTexture))
	{
		__gleFramebufferTexture = gle_CoreStruct.gleVarFramebufferTexture;
		if(!__gleFramebufferTexture) bIsLoaded = 0;
	}
	__gleTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)gleIntGetProcAddress("glTexImage2DMultisample");
	if(!TestPointer(__gleTexImage2DMultisample))
	{
		__gleTexImage2DMultisample = gle_CoreStruct.gleVarTexImage2DMultisample;
		if(!__gleTexImage2DMultisample) bIsLoaded = 0;
	}
	__gleTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)gleIntGetProcAddress("glTexImage3DMultisample");
	if(!TestPointer(__gleTexImage3DMultisample))
	{
		__gleTexImage3DMultisample = gle_CoreStruct.gleVarTexImage3DMultisample;
		if(!__gleTexImage3DMultisample) bIsLoaded = 0;
	}
	__gleGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)gleIntGetProcAddress("glGetMultisamplefv");
	if(!TestPointer(__gleGetMultisamplefv))
	{
		__gleGetMultisamplefv = gle_CoreStruct.gleVarGetMultisamplefv;
		if(!__gleGetMultisamplefv) bIsLoaded = 0;
	}
	__gleSampleMaski = (PFNGLSAMPLEMASKIPROC)gleIntGetProcAddress("glSampleMaski");
	if(!TestPointer(__gleSampleMaski))
	{
		__gleSampleMaski = gle_CoreStruct.gleVarSampleMaski;
		if(!__gleSampleMaski) bIsLoaded = 0;
	}
	glext_ARB_texture_multisample = 1;
	__gleDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glDrawElementsBaseVertex");
	if(!TestPointer(__gleDrawElementsBaseVertex))
	{
		__gleDrawElementsBaseVertex = gle_CoreStruct.gleVarDrawElementsBaseVertex;
		if(!__gleDrawElementsBaseVertex) bIsLoaded = 0;
	}
	__gleDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glDrawRangeElementsBaseVertex");
	if(!TestPointer(__gleDrawRangeElementsBaseVertex))
	{
		__gleDrawRangeElementsBaseVertex = gle_CoreStruct.gleVarDrawRangeElementsBaseVertex;
		if(!__gleDrawRangeElementsBaseVertex) bIsLoaded = 0;
	}
	__gleDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)gleIntGetProcAddress("glDrawElementsInstancedBaseVertex");
	if(!TestPointer(__gleDrawElementsInstancedBaseVertex))
	{
		__gleDrawElementsInstancedBaseVertex = gle_CoreStruct.gleVarDrawElementsInstancedBaseVertex;
		if(!__gleDrawElementsInstancedBaseVertex) bIsLoaded = 0;
	}
	__gleMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)gleIntGetProcAddress("glMultiDrawElementsBaseVertex");
	if(!TestPointer(__gleMultiDrawElementsBaseVertex))
	{
		__gleMultiDrawElementsBaseVertex = gle_CoreStruct.gleVarMultiDrawElementsBaseVertex;
		if(!__gleMultiDrawElementsBaseVertex) bIsLoaded = 0;
	}
	glext_ARB_draw_elements_base_vertex = 1;
	__gleProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)gleIntGetProcAddress("glProvokingVertex");
	if(!TestPointer(__gleProvokingVertex))
	{
		__gleProvokingVertex = gle_CoreStruct.gleVarProvokingVertex;
		if(!__gleProvokingVertex) bIsLoaded = 0;
	}
	glext_ARB_provoking_vertex = 1;
	__gleFenceSync = (PFNGLFENCESYNCPROC)gleIntGetProcAddress("glFenceSync");
	if(!TestPointer(__gleFenceSync))
	{
		__gleFenceSync = gle_CoreStruct.gleVarFenceSync;
		if(!__gleFenceSync) bIsLoaded = 0;
	}
	__gleIsSync = (PFNGLISSYNCPROC)gleIntGetProcAddress("glIsSync");
	if(!TestPointer(__gleIsSync))
	{
		__gleIsSync = gle_CoreStruct.gleVarIsSync;
		if(!__gleIsSync) bIsLoaded = 0;
	}
	__gleDeleteSync = (PFNGLDELETESYNCPROC)gleIntGetProcAddress("glDeleteSync");
	if(!TestPointer(__gleDeleteSync))
	{
		__gleDeleteSync = gle_CoreStruct.gleVarDeleteSync;
		if(!__gleDeleteSync) bIsLoaded = 0;
	}
	__gleClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)gleIntGetProcAddress("glClientWaitSync");
	if(!TestPointer(__gleClientWaitSync))
	{
		__gleClientWaitSync = gle_CoreStruct.gleVarClientWaitSync;
		if(!__gleClientWaitSync) bIsLoaded = 0;
	}
	__gleWaitSync = (PFNGLWAITSYNCPROC)gleIntGetProcAddress("glWaitSync");
	if(!TestPointer(__gleWaitSync))
	{
		__gleWaitSync = gle_CoreStruct.gleVarWaitSync;
		if(!__gleWaitSync) bIsLoaded = 0;
	}
	__gleGetInteger64v = (PFNGLGETINTEGER64VPROC)gleIntGetProcAddress("glGetInteger64v");
	if(!TestPointer(__gleGetInteger64v))
	{
		__gleGetInteger64v = gle_CoreStruct.gleVarGetInteger64v;
		if(!__gleGetInteger64v) bIsLoaded = 0;
	}
	__gleGetSynciv = (PFNGLGETSYNCIVPROC)gleIntGetProcAddress("glGetSynciv");
	if(!TestPointer(__gleGetSynciv))
	{
		__gleGetSynciv = gle_CoreStruct.gleVarGetSynciv;
		if(!__gleGetSynciv) bIsLoaded = 0;
	}
	glext_ARB_sync = 1;
	return bIsLoaded;
}

static int gleIntLoadCore_3_3_Base()
{
	int bIsLoaded = 1;
	__gleVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)gleIntGetProcAddress("glVertexAttribDivisor");
	if(!TestPointer(__gleVertexAttribDivisor))
	{
		__gleVertexAttribDivisor = gle_CoreStruct.gleVarVertexAttribDivisor;
		if(!__gleVertexAttribDivisor) bIsLoaded = 0;
	}
	__gleQueryCounter = (PFNGLQUERYCOUNTERPROC)gleIntGetProcAddress("glQueryCounter");
	if(!TestPointer(__gleQueryCounter))
	{
		__gleQueryCounter = gle_CoreStruct.gleVarQueryCounter;
		if(!__gleQueryCounter) bIsLoaded = 0;
	}
	__gleGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)gleIntGetProcAddress("glGetQueryObjecti64v");
	if(!TestPointer(__gleGetQueryObjecti64v))
	{
		__gleGetQueryObjecti64v = gle_CoreStruct.gleVarGetQueryObjecti64v;
		if(!__gleGetQueryObjecti64v) bIsLoaded = 0;
	}
	__gleGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)gleIntGetProcAddress("glGetQueryObjectui64v");
	if(!TestPointer(__gleGetQueryObjectui64v))
	{
		__gleGetQueryObjectui64v = gle_CoreStruct.gleVarGetQueryObjectui64v;
		if(!__gleGetQueryObjectui64v) bIsLoaded = 0;
	}
	glext_ARB_timer_query = 1;
	__gleVertexP2ui = (PFNGLVERTEXP2UIPROC)gleIntGetProcAddress("glVertexP2ui");
	if(!TestPointer(__gleVertexP2ui))
	{
		__gleVertexP2ui = gle_CoreStruct.gleVarVertexP2ui;
		if(!__gleVertexP2ui) bIsLoaded = 0;
	}
	__gleVertexP2uiv = (PFNGLVERTEXP2UIVPROC)gleIntGetProcAddress("glVertexP2uiv");
	if(!TestPointer(__gleVertexP2uiv))
	{
		__gleVertexP2uiv = gle_CoreStruct.gleVarVertexP2uiv;
		if(!__gleVertexP2uiv) bIsLoaded = 0;
	}
	__gleVertexP3ui = (PFNGLVERTEXP3UIPROC)gleIntGetProcAddress("glVertexP3ui");
	if(!TestPointer(__gleVertexP3ui))
	{
		__gleVertexP3ui = gle_CoreStruct.gleVarVertexP3ui;
		if(!__gleVertexP3ui) bIsLoaded = 0;
	}
	__gleVertexP3uiv = (PFNGLVERTEXP3UIVPROC)gleIntGetProcAddress("glVertexP3uiv");
	if(!TestPointer(__gleVertexP3uiv))
	{
		__gleVertexP3uiv = gle_CoreStruct.gleVarVertexP3uiv;
		if(!__gleVertexP3uiv) bIsLoaded = 0;
	}
	__gleVertexP4ui = (PFNGLVERTEXP4UIPROC)gleIntGetProcAddress("glVertexP4ui");
	if(!TestPointer(__gleVertexP4ui))
	{
		__gleVertexP4ui = gle_CoreStruct.gleVarVertexP4ui;
		if(!__gleVertexP4ui) bIsLoaded = 0;
	}
	__gleVertexP4uiv = (PFNGLVERTEXP4UIVPROC)gleIntGetProcAddress("glVertexP4uiv");
	if(!TestPointer(__gleVertexP4uiv))
	{
		__gleVertexP4uiv = gle_CoreStruct.gleVarVertexP4uiv;
		if(!__gleVertexP4uiv) bIsLoaded = 0;
	}
	__gleTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)gleIntGetProcAddress("glTexCoordP1ui");
	if(!TestPointer(__gleTexCoordP1ui))
	{
		__gleTexCoordP1ui = gle_CoreStruct.gleVarTexCoordP1ui;
		if(!__gleTexCoordP1ui) bIsLoaded = 0;
	}
	__gleTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)gleIntGetProcAddress("glTexCoordP1uiv");
	if(!TestPointer(__gleTexCoordP1uiv))
	{
		__gleTexCoordP1uiv = gle_CoreStruct.gleVarTexCoordP1uiv;
		if(!__gleTexCoordP1uiv) bIsLoaded = 0;
	}
	__gleTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)gleIntGetProcAddress("glTexCoordP2ui");
	if(!TestPointer(__gleTexCoordP2ui))
	{
		__gleTexCoordP2ui = gle_CoreStruct.gleVarTexCoordP2ui;
		if(!__gleTexCoordP2ui) bIsLoaded = 0;
	}
	__gleTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)gleIntGetProcAddress("glTexCoordP2uiv");
	if(!TestPointer(__gleTexCoordP2uiv))
	{
		__gleTexCoordP2uiv = gle_CoreStruct.gleVarTexCoordP2uiv;
		if(!__gleTexCoordP2uiv) bIsLoaded = 0;
	}
	__gleTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)gleIntGetProcAddress("glTexCoordP3ui");
	if(!TestPointer(__gleTexCoordP3ui))
	{
		__gleTexCoordP3ui = gle_CoreStruct.gleVarTexCoordP3ui;
		if(!__gleTexCoordP3ui) bIsLoaded = 0;
	}
	__gleTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)gleIntGetProcAddress("glTexCoordP3uiv");
	if(!TestPointer(__gleTexCoordP3uiv))
	{
		__gleTexCoordP3uiv = gle_CoreStruct.gleVarTexCoordP3uiv;
		if(!__gleTexCoordP3uiv) bIsLoaded = 0;
	}
	__gleTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)gleIntGetProcAddress("glTexCoordP4ui");
	if(!TestPointer(__gleTexCoordP4ui))
	{
		__gleTexCoordP4ui = gle_CoreStruct.gleVarTexCoordP4ui;
		if(!__gleTexCoordP4ui) bIsLoaded = 0;
	}
	__gleTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)gleIntGetProcAddress("glTexCoordP4uiv");
	if(!TestPointer(__gleTexCoordP4uiv))
	{
		__gleTexCoordP4uiv = gle_CoreStruct.gleVarTexCoordP4uiv;
		if(!__gleTexCoordP4uiv) bIsLoaded = 0;
	}
	__gleMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)gleIntGetProcAddress("glMultiTexCoordP1ui");
	if(!TestPointer(__gleMultiTexCoordP1ui))
	{
		__gleMultiTexCoordP1ui = gle_CoreStruct.gleVarMultiTexCoordP1ui;
		if(!__gleMultiTexCoordP1ui) bIsLoaded = 0;
	}
	__gleMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)gleIntGetProcAddress("glMultiTexCoordP1uiv");
	if(!TestPointer(__gleMultiTexCoordP1uiv))
	{
		__gleMultiTexCoordP1uiv = gle_CoreStruct.gleVarMultiTexCoordP1uiv;
		if(!__gleMultiTexCoordP1uiv) bIsLoaded = 0;
	}
	__gleMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)gleIntGetProcAddress("glMultiTexCoordP2ui");
	if(!TestPointer(__gleMultiTexCoordP2ui))
	{
		__gleMultiTexCoordP2ui = gle_CoreStruct.gleVarMultiTexCoordP2ui;
		if(!__gleMultiTexCoordP2ui) bIsLoaded = 0;
	}
	__gleMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)gleIntGetProcAddress("glMultiTexCoordP2uiv");
	if(!TestPointer(__gleMultiTexCoordP2uiv))
	{
		__gleMultiTexCoordP2uiv = gle_CoreStruct.gleVarMultiTexCoordP2uiv;
		if(!__gleMultiTexCoordP2uiv) bIsLoaded = 0;
	}
	__gleMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)gleIntGetProcAddress("glMultiTexCoordP3ui");
	if(!TestPointer(__gleMultiTexCoordP3ui))
	{
		__gleMultiTexCoordP3ui = gle_CoreStruct.gleVarMultiTexCoordP3ui;
		if(!__gleMultiTexCoordP3ui) bIsLoaded = 0;
	}
	__gleMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)gleIntGetProcAddress("glMultiTexCoordP3uiv");
	if(!TestPointer(__gleMultiTexCoordP3uiv))
	{
		__gleMultiTexCoordP3uiv = gle_CoreStruct.gleVarMultiTexCoordP3uiv;
		if(!__gleMultiTexCoordP3uiv) bIsLoaded = 0;
	}
	__gleMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)gleIntGetProcAddress("glMultiTexCoordP4ui");
	if(!TestPointer(__gleMultiTexCoordP4ui))
	{
		__gleMultiTexCoordP4ui = gle_CoreStruct.gleVarMultiTexCoordP4ui;
		if(!__gleMultiTexCoordP4ui) bIsLoaded = 0;
	}
	__gleMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)gleIntGetProcAddress("glMultiTexCoordP4uiv");
	if(!TestPointer(__gleMultiTexCoordP4uiv))
	{
		__gleMultiTexCoordP4uiv = gle_CoreStruct.gleVarMultiTexCoordP4uiv;
		if(!__gleMultiTexCoordP4uiv) bIsLoaded = 0;
	}
	__gleNormalP3ui = (PFNGLNORMALP3UIPROC)gleIntGetProcAddress("glNormalP3ui");
	if(!TestPointer(__gleNormalP3ui))
	{
		__gleNormalP3ui = gle_CoreStruct.gleVarNormalP3ui;
		if(!__gleNormalP3ui) bIsLoaded = 0;
	}
	__gleNormalP3uiv = (PFNGLNORMALP3UIVPROC)gleIntGetProcAddress("glNormalP3uiv");
	if(!TestPointer(__gleNormalP3uiv))
	{
		__gleNormalP3uiv = gle_CoreStruct.gleVarNormalP3uiv;
		if(!__gleNormalP3uiv) bIsLoaded = 0;
	}
	__gleColorP3ui = (PFNGLCOLORP3UIPROC)gleIntGetProcAddress("glColorP3ui");
	if(!TestPointer(__gleColorP3ui))
	{
		__gleColorP3ui = gle_CoreStruct.gleVarColorP3ui;
		if(!__gleColorP3ui) bIsLoaded = 0;
	}
	__gleColorP3uiv = (PFNGLCOLORP3UIVPROC)gleIntGetProcAddress("glColorP3uiv");
	if(!TestPointer(__gleColorP3uiv))
	{
		__gleColorP3uiv = gle_CoreStruct.gleVarColorP3uiv;
		if(!__gleColorP3uiv) bIsLoaded = 0;
	}
	__gleColorP4ui = (PFNGLCOLORP4UIPROC)gleIntGetProcAddress("glColorP4ui");
	if(!TestPointer(__gleColorP4ui))
	{
		__gleColorP4ui = gle_CoreStruct.gleVarColorP4ui;
		if(!__gleColorP4ui) bIsLoaded = 0;
	}
	__gleColorP4uiv = (PFNGLCOLORP4UIVPROC)gleIntGetProcAddress("glColorP4uiv");
	if(!TestPointer(__gleColorP4uiv))
	{
		__gleColorP4uiv = gle_CoreStruct.gleVarColorP4uiv;
		if(!__gleColorP4uiv) bIsLoaded = 0;
	}
	__gleSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)gleIntGetProcAddress("glSecondaryColorP3ui");
	if(!TestPointer(__gleSecondaryColorP3ui))
	{
		__gleSecondaryColorP3ui = gle_CoreStruct.gleVarSecondaryColorP3ui;
		if(!__gleSecondaryColorP3ui) bIsLoaded = 0;
	}
	__gleSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)gleIntGetProcAddress("glSecondaryColorP3uiv");
	if(!TestPointer(__gleSecondaryColorP3uiv))
	{
		__gleSecondaryColorP3uiv = gle_CoreStruct.gleVarSecondaryColorP3uiv;
		if(!__gleSecondaryColorP3uiv) bIsLoaded = 0;
	}
	__gleVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)gleIntGetProcAddress("glVertexAttribP1ui");
	if(!TestPointer(__gleVertexAttribP1ui))
	{
		__gleVertexAttribP1ui = gle_CoreStruct.gleVarVertexAttribP1ui;
		if(!__gleVertexAttribP1ui) bIsLoaded = 0;
	}
	__gleVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)gleIntGetProcAddress("glVertexAttribP1uiv");
	if(!TestPointer(__gleVertexAttribP1uiv))
	{
		__gleVertexAttribP1uiv = gle_CoreStruct.gleVarVertexAttribP1uiv;
		if(!__gleVertexAttribP1uiv) bIsLoaded = 0;
	}
	__gleVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)gleIntGetProcAddress("glVertexAttribP2ui");
	if(!TestPointer(__gleVertexAttribP2ui))
	{
		__gleVertexAttribP2ui = gle_CoreStruct.gleVarVertexAttribP2ui;
		if(!__gleVertexAttribP2ui) bIsLoaded = 0;
	}
	__gleVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)gleIntGetProcAddress("glVertexAttribP2uiv");
	if(!TestPointer(__gleVertexAttribP2uiv))
	{
		__gleVertexAttribP2uiv = gle_CoreStruct.gleVarVertexAttribP2uiv;
		if(!__gleVertexAttribP2uiv) bIsLoaded = 0;
	}
	__gleVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)gleIntGetProcAddress("glVertexAttribP3ui");
	if(!TestPointer(__gleVertexAttribP3ui))
	{
		__gleVertexAttribP3ui = gle_CoreStruct.gleVarVertexAttribP3ui;
		if(!__gleVertexAttribP3ui) bIsLoaded = 0;
	}
	__gleVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)gleIntGetProcAddress("glVertexAttribP3uiv");
	if(!TestPointer(__gleVertexAttribP3uiv))
	{
		__gleVertexAttribP3uiv = gle_CoreStruct.gleVarVertexAttribP3uiv;
		if(!__gleVertexAttribP3uiv) bIsLoaded = 0;
	}
	__gleVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)gleIntGetProcAddress("glVertexAttribP4ui");
	if(!TestPointer(__gleVertexAttribP4ui))
	{
		__gleVertexAttribP4ui = gle_CoreStruct.gleVarVertexAttribP4ui;
		if(!__gleVertexAttribP4ui) bIsLoaded = 0;
	}
	__gleVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)gleIntGetProcAddress("glVertexAttribP4uiv");
	if(!TestPointer(__gleVertexAttribP4uiv))
	{
		__gleVertexAttribP4uiv = gle_CoreStruct.gleVarVertexAttribP4uiv;
		if(!__gleVertexAttribP4uiv) bIsLoaded = 0;
	}
	glext_ARB_vertex_type_2_10_10_10_rev = 1;
	__gleGenSamplers = (PFNGLGENSAMPLERSPROC)gleIntGetProcAddress("glGenSamplers");
	if(!TestPointer(__gleGenSamplers))
	{
		__gleGenSamplers = gle_CoreStruct.gleVarGenSamplers;
		if(!__gleGenSamplers) bIsLoaded = 0;
	}
	__gleDeleteSamplers = (PFNGLDELETESAMPLERSPROC)gleIntGetProcAddress("glDeleteSamplers");
	if(!TestPointer(__gleDeleteSamplers))
	{
		__gleDeleteSamplers = gle_CoreStruct.gleVarDeleteSamplers;
		if(!__gleDeleteSamplers) bIsLoaded = 0;
	}
	__gleIsSampler = (PFNGLISSAMPLERPROC)gleIntGetProcAddress("glIsSampler");
	if(!TestPointer(__gleIsSampler))
	{
		__gleIsSampler = gle_CoreStruct.gleVarIsSampler;
		if(!__gleIsSampler) bIsLoaded = 0;
	}
	__gleBindSampler = (PFNGLBINDSAMPLERPROC)gleIntGetProcAddress("glBindSampler");
	if(!TestPointer(__gleBindSampler))
	{
		__gleBindSampler = gle_CoreStruct.gleVarBindSampler;
		if(!__gleBindSampler) bIsLoaded = 0;
	}
	__gleSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)gleIntGetProcAddress("glSamplerParameteri");
	if(!TestPointer(__gleSamplerParameteri))
	{
		__gleSamplerParameteri = gle_CoreStruct.gleVarSamplerParameteri;
		if(!__gleSamplerParameteri) bIsLoaded = 0;
	}
	__gleSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)gleIntGetProcAddress("glSamplerParameteriv");
	if(!TestPointer(__gleSamplerParameteriv))
	{
		__gleSamplerParameteriv = gle_CoreStruct.gleVarSamplerParameteriv;
		if(!__gleSamplerParameteriv) bIsLoaded = 0;
	}
	__gleSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)gleIntGetProcAddress("glSamplerParameterf");
	if(!TestPointer(__gleSamplerParameterf))
	{
		__gleSamplerParameterf = gle_CoreStruct.gleVarSamplerParameterf;
		if(!__gleSamplerParameterf) bIsLoaded = 0;
	}
	__gleSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)gleIntGetProcAddress("glSamplerParameterfv");
	if(!TestPointer(__gleSamplerParameterfv))
	{
		__gleSamplerParameterfv = gle_CoreStruct.gleVarSamplerParameterfv;
		if(!__gleSamplerParameterfv) bIsLoaded = 0;
	}
	__gleSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)gleIntGetProcAddress("glSamplerParameterIiv");
	if(!TestPointer(__gleSamplerParameterIiv))
	{
		__gleSamplerParameterIiv = gle_CoreStruct.gleVarSamplerParameterIiv;
		if(!__gleSamplerParameterIiv) bIsLoaded = 0;
	}
	__gleSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)gleIntGetProcAddress("glSamplerParameterIuiv");
	if(!TestPointer(__gleSamplerParameterIuiv))
	{
		__gleSamplerParameterIuiv = gle_CoreStruct.gleVarSamplerParameterIuiv;
		if(!__gleSamplerParameterIuiv) bIsLoaded = 0;
	}
	__gleGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)gleIntGetProcAddress("glGetSamplerParameteriv");
	if(!TestPointer(__gleGetSamplerParameteriv))
	{
		__gleGetSamplerParameteriv = gle_CoreStruct.gleVarGetSamplerParameteriv;
		if(!__gleGetSamplerParameteriv) bIsLoaded = 0;
	}
	__gleGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)gleIntGetProcAddress("glGetSamplerParameterIiv");
	if(!TestPointer(__gleGetSamplerParameterIiv))
	{
		__gleGetSamplerParameterIiv = gle_CoreStruct.gleVarGetSamplerParameterIiv;
		if(!__gleGetSamplerParameterIiv) bIsLoaded = 0;
	}
	__gleGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)gleIntGetProcAddress("glGetSamplerParameterfv");
	if(!TestPointer(__gleGetSamplerParameterfv))
	{
		__gleGetSamplerParameterfv = gle_CoreStruct.gleVarGetSamplerParameterfv;
		if(!__gleGetSamplerParameterfv) bIsLoaded = 0;
	}
	__gleGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)gleIntGetProcAddress("glGetSamplerParameterIuiv");
	if(!TestPointer(__gleGetSamplerParameterIuiv))
	{
		__gleGetSamplerParameterIuiv = gle_CoreStruct.gleVarGetSamplerParameterIuiv;
		if(!__gleGetSamplerParameterIuiv) bIsLoaded = 0;
	}
	glext_ARB_sampler_objects = 1;
	__gleBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)gleIntGetProcAddress("glBindFragDataLocationIndexed");
	if(!TestPointer(__gleBindFragDataLocationIndexed))
	{
		__gleBindFragDataLocationIndexed = gle_CoreStruct.gleVarBindFragDataLocationIndexed;
		if(!__gleBindFragDataLocationIndexed) bIsLoaded = 0;
	}
	__gleGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)gleIntGetProcAddress("glGetFragDataIndex");
	if(!TestPointer(__gleGetFragDataIndex))
	{
		__gleGetFragDataIndex = gle_CoreStruct.gleVarGetFragDataIndex;
		if(!__gleGetFragDataIndex) bIsLoaded = 0;
	}
	glext_ARB_blend_func_extended = 1;
	return bIsLoaded;
}

static int gleIntLoadCore_4_0_Base()
{
	int bIsLoaded = 1;
	__gleMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)gleIntGetProcAddress("glMinSampleShading");
	if(!TestPointer(__gleMinSampleShading))
	{
		__gleMinSampleShading = gle_CoreStruct.gleVarMinSampleShading;
		if(!__gleMinSampleShading) bIsLoaded = 0;
	}
	__gleBlendEquationi = (PFNGLBLENDEQUATIONIPROC)gleIntGetProcAddress("glBlendEquationi");
	if(!TestPointer(__gleBlendEquationi))
	{
		__gleBlendEquationi = gle_CoreStruct.gleVarBlendEquationi;
		if(!__gleBlendEquationi) bIsLoaded = 0;
	}
	__gleBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)gleIntGetProcAddress("glBlendEquationSeparatei");
	if(!TestPointer(__gleBlendEquationSeparatei))
	{
		__gleBlendEquationSeparatei = gle_CoreStruct.gleVarBlendEquationSeparatei;
		if(!__gleBlendEquationSeparatei) bIsLoaded = 0;
	}
	__gleBlendFunci = (PFNGLBLENDFUNCIPROC)gleIntGetProcAddress("glBlendFunci");
	if(!TestPointer(__gleBlendFunci))
	{
		__gleBlendFunci = gle_CoreStruct.gleVarBlendFunci;
		if(!__gleBlendFunci) bIsLoaded = 0;
	}
	__gleBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)gleIntGetProcAddress("glBlendFuncSeparatei");
	if(!TestPointer(__gleBlendFuncSeparatei))
	{
		__gleBlendFuncSeparatei = gle_CoreStruct.gleVarBlendFuncSeparatei;
		if(!__gleBlendFuncSeparatei) bIsLoaded = 0;
	}
	__gleBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glBindTransformFeedback");
	if(!TestPointer(__gleBindTransformFeedback))
	{
		__gleBindTransformFeedback = gle_CoreStruct.gleVarBindTransformFeedback;
		if(!__gleBindTransformFeedback) bIsLoaded = 0;
	}
	__gleDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)gleIntGetProcAddress("glDeleteTransformFeedbacks");
	if(!TestPointer(__gleDeleteTransformFeedbacks))
	{
		__gleDeleteTransformFeedbacks = gle_CoreStruct.gleVarDeleteTransformFeedbacks;
		if(!__gleDeleteTransformFeedbacks) bIsLoaded = 0;
	}
	__gleGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)gleIntGetProcAddress("glGenTransformFeedbacks");
	if(!TestPointer(__gleGenTransformFeedbacks))
	{
		__gleGenTransformFeedbacks = gle_CoreStruct.gleVarGenTransformFeedbacks;
		if(!__gleGenTransformFeedbacks) bIsLoaded = 0;
	}
	__gleIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glIsTransformFeedback");
	if(!TestPointer(__gleIsTransformFeedback))
	{
		__gleIsTransformFeedback = gle_CoreStruct.gleVarIsTransformFeedback;
		if(!__gleIsTransformFeedback) bIsLoaded = 0;
	}
	__glePauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glPauseTransformFeedback");
	if(!TestPointer(__glePauseTransformFeedback))
	{
		__glePauseTransformFeedback = gle_CoreStruct.gleVarPauseTransformFeedback;
		if(!__glePauseTransformFeedback) bIsLoaded = 0;
	}
	__gleResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glResumeTransformFeedback");
	if(!TestPointer(__gleResumeTransformFeedback))
	{
		__gleResumeTransformFeedback = gle_CoreStruct.gleVarResumeTransformFeedback;
		if(!__gleResumeTransformFeedback) bIsLoaded = 0;
	}
	__gleDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)gleIntGetProcAddress("glDrawTransformFeedback");
	if(!TestPointer(__gleDrawTransformFeedback))
	{
		__gleDrawTransformFeedback = gle_CoreStruct.gleVarDrawTransformFeedback;
		if(!__gleDrawTransformFeedback) bIsLoaded = 0;
	}
	glext_ARB_transform_feedback2 = 1;
	__gleDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)gleIntGetProcAddress("glDrawTransformFeedbackStream");
	if(!TestPointer(__gleDrawTransformFeedbackStream))
	{
		__gleDrawTransformFeedbackStream = gle_CoreStruct.gleVarDrawTransformFeedbackStream;
		if(!__gleDrawTransformFeedbackStream) bIsLoaded = 0;
	}
	__gleBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)gleIntGetProcAddress("glBeginQueryIndexed");
	if(!TestPointer(__gleBeginQueryIndexed))
	{
		__gleBeginQueryIndexed = gle_CoreStruct.gleVarBeginQueryIndexed;
		if(!__gleBeginQueryIndexed) bIsLoaded = 0;
	}
	__gleEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)gleIntGetProcAddress("glEndQueryIndexed");
	if(!TestPointer(__gleEndQueryIndexed))
	{
		__gleEndQueryIndexed = gle_CoreStruct.gleVarEndQueryIndexed;
		if(!__gleEndQueryIndexed) bIsLoaded = 0;
	}
	__gleGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)gleIntGetProcAddress("glGetQueryIndexediv");
	if(!TestPointer(__gleGetQueryIndexediv))
	{
		__gleGetQueryIndexediv = gle_CoreStruct.gleVarGetQueryIndexediv;
		if(!__gleGetQueryIndexediv) bIsLoaded = 0;
	}
	glext_ARB_transform_feedback3 = 1;
	__glePatchParameteri = (PFNGLPATCHPARAMETERIPROC)gleIntGetProcAddress("glPatchParameteri");
	if(!TestPointer(__glePatchParameteri))
	{
		__glePatchParameteri = gle_CoreStruct.gleVarPatchParameteri;
		if(!__glePatchParameteri) bIsLoaded = 0;
	}
	__glePatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)gleIntGetProcAddress("glPatchParameterfv");
	if(!TestPointer(__glePatchParameterfv))
	{
		__glePatchParameterfv = gle_CoreStruct.gleVarPatchParameterfv;
		if(!__glePatchParameterfv) bIsLoaded = 0;
	}
	glext_ARB_tessellation_shader = 1;
	__gleUniform1d = (PFNGLUNIFORM1DPROC)gleIntGetProcAddress("glUniform1d");
	if(!TestPointer(__gleUniform1d))
	{
		__gleUniform1d = gle_CoreStruct.gleVarUniform1d;
		if(!__gleUniform1d) bIsLoaded = 0;
	}
	__gleUniform2d = (PFNGLUNIFORM2DPROC)gleIntGetProcAddress("glUniform2d");
	if(!TestPointer(__gleUniform2d))
	{
		__gleUniform2d = gle_CoreStruct.gleVarUniform2d;
		if(!__gleUniform2d) bIsLoaded = 0;
	}
	__gleUniform3d = (PFNGLUNIFORM3DPROC)gleIntGetProcAddress("glUniform3d");
	if(!TestPointer(__gleUniform3d))
	{
		__gleUniform3d = gle_CoreStruct.gleVarUniform3d;
		if(!__gleUniform3d) bIsLoaded = 0;
	}
	__gleUniform4d = (PFNGLUNIFORM4DPROC)gleIntGetProcAddress("glUniform4d");
	if(!TestPointer(__gleUniform4d))
	{
		__gleUniform4d = gle_CoreStruct.gleVarUniform4d;
		if(!__gleUniform4d) bIsLoaded = 0;
	}
	__gleUniform1dv = (PFNGLUNIFORM1DVPROC)gleIntGetProcAddress("glUniform1dv");
	if(!TestPointer(__gleUniform1dv))
	{
		__gleUniform1dv = gle_CoreStruct.gleVarUniform1dv;
		if(!__gleUniform1dv) bIsLoaded = 0;
	}
	__gleUniform2dv = (PFNGLUNIFORM2DVPROC)gleIntGetProcAddress("glUniform2dv");
	if(!TestPointer(__gleUniform2dv))
	{
		__gleUniform2dv = gle_CoreStruct.gleVarUniform2dv;
		if(!__gleUniform2dv) bIsLoaded = 0;
	}
	__gleUniform3dv = (PFNGLUNIFORM3DVPROC)gleIntGetProcAddress("glUniform3dv");
	if(!TestPointer(__gleUniform3dv))
	{
		__gleUniform3dv = gle_CoreStruct.gleVarUniform3dv;
		if(!__gleUniform3dv) bIsLoaded = 0;
	}
	__gleUniform4dv = (PFNGLUNIFORM4DVPROC)gleIntGetProcAddress("glUniform4dv");
	if(!TestPointer(__gleUniform4dv))
	{
		__gleUniform4dv = gle_CoreStruct.gleVarUniform4dv;
		if(!__gleUniform4dv) bIsLoaded = 0;
	}
	__gleUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)gleIntGetProcAddress("glUniformMatrix2dv");
	if(!TestPointer(__gleUniformMatrix2dv))
	{
		__gleUniformMatrix2dv = gle_CoreStruct.gleVarUniformMatrix2dv;
		if(!__gleUniformMatrix2dv) bIsLoaded = 0;
	}
	__gleUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)gleIntGetProcAddress("glUniformMatrix3dv");
	if(!TestPointer(__gleUniformMatrix3dv))
	{
		__gleUniformMatrix3dv = gle_CoreStruct.gleVarUniformMatrix3dv;
		if(!__gleUniformMatrix3dv) bIsLoaded = 0;
	}
	__gleUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)gleIntGetProcAddress("glUniformMatrix4dv");
	if(!TestPointer(__gleUniformMatrix4dv))
	{
		__gleUniformMatrix4dv = gle_CoreStruct.gleVarUniformMatrix4dv;
		if(!__gleUniformMatrix4dv) bIsLoaded = 0;
	}
	__gleUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)gleIntGetProcAddress("glUniformMatrix2x3dv");
	if(!TestPointer(__gleUniformMatrix2x3dv))
	{
		__gleUniformMatrix2x3dv = gle_CoreStruct.gleVarUniformMatrix2x3dv;
		if(!__gleUniformMatrix2x3dv) bIsLoaded = 0;
	}
	__gleUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)gleIntGetProcAddress("glUniformMatrix2x4dv");
	if(!TestPointer(__gleUniformMatrix2x4dv))
	{
		__gleUniformMatrix2x4dv = gle_CoreStruct.gleVarUniformMatrix2x4dv;
		if(!__gleUniformMatrix2x4dv) bIsLoaded = 0;
	}
	__gleUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)gleIntGetProcAddress("glUniformMatrix3x2dv");
	if(!TestPointer(__gleUniformMatrix3x2dv))
	{
		__gleUniformMatrix3x2dv = gle_CoreStruct.gleVarUniformMatrix3x2dv;
		if(!__gleUniformMatrix3x2dv) bIsLoaded = 0;
	}
	__gleUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)gleIntGetProcAddress("glUniformMatrix3x4dv");
	if(!TestPointer(__gleUniformMatrix3x4dv))
	{
		__gleUniformMatrix3x4dv = gle_CoreStruct.gleVarUniformMatrix3x4dv;
		if(!__gleUniformMatrix3x4dv) bIsLoaded = 0;
	}
	__gleUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)gleIntGetProcAddress("glUniformMatrix4x2dv");
	if(!TestPointer(__gleUniformMatrix4x2dv))
	{
		__gleUniformMatrix4x2dv = gle_CoreStruct.gleVarUniformMatrix4x2dv;
		if(!__gleUniformMatrix4x2dv) bIsLoaded = 0;
	}
	__gleUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)gleIntGetProcAddress("glUniformMatrix4x3dv");
	if(!TestPointer(__gleUniformMatrix4x3dv))
	{
		__gleUniformMatrix4x3dv = gle_CoreStruct.gleVarUniformMatrix4x3dv;
		if(!__gleUniformMatrix4x3dv) bIsLoaded = 0;
	}
	__gleGetUniformdv = (PFNGLGETUNIFORMDVPROC)gleIntGetProcAddress("glGetUniformdv");
	if(!TestPointer(__gleGetUniformdv))
	{
		__gleGetUniformdv = gle_CoreStruct.gleVarGetUniformdv;
		if(!__gleGetUniformdv) bIsLoaded = 0;
	}
	glext_ARB_gpu_shader_fp64 = 1;
	__gleDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)gleIntGetProcAddress("glDrawArraysIndirect");
	if(!TestPointer(__gleDrawArraysIndirect))
	{
		__gleDrawArraysIndirect = gle_CoreStruct.gleVarDrawArraysIndirect;
		if(!__gleDrawArraysIndirect) bIsLoaded = 0;
	}
	__gleDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)gleIntGetProcAddress("glDrawElementsIndirect");
	if(!TestPointer(__gleDrawElementsIndirect))
	{
		__gleDrawElementsIndirect = gle_CoreStruct.gleVarDrawElementsIndirect;
		if(!__gleDrawElementsIndirect) bIsLoaded = 0;
	}
	glext_ARB_draw_indirect = 1;
	__gleGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)gleIntGetProcAddress("glGetSubroutineUniformLocation");
	if(!TestPointer(__gleGetSubroutineUniformLocation))
	{
		__gleGetSubroutineUniformLocation = gle_CoreStruct.gleVarGetSubroutineUniformLocation;
		if(!__gleGetSubroutineUniformLocation) bIsLoaded = 0;
	}
	__gleGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)gleIntGetProcAddress("glGetSubroutineIndex");
	if(!TestPointer(__gleGetSubroutineIndex))
	{
		__gleGetSubroutineIndex = gle_CoreStruct.gleVarGetSubroutineIndex;
		if(!__gleGetSubroutineIndex) bIsLoaded = 0;
	}
	__gleGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)gleIntGetProcAddress("glGetActiveSubroutineUniformiv");
	if(!TestPointer(__gleGetActiveSubroutineUniformiv))
	{
		__gleGetActiveSubroutineUniformiv = gle_CoreStruct.gleVarGetActiveSubroutineUniformiv;
		if(!__gleGetActiveSubroutineUniformiv) bIsLoaded = 0;
	}
	__gleGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)gleIntGetProcAddress("glGetActiveSubroutineUniformName");
	if(!TestPointer(__gleGetActiveSubroutineUniformName))
	{
		__gleGetActiveSubroutineUniformName = gle_CoreStruct.gleVarGetActiveSubroutineUniformName;
		if(!__gleGetActiveSubroutineUniformName) bIsLoaded = 0;
	}
	__gleGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)gleIntGetProcAddress("glGetActiveSubroutineName");
	if(!TestPointer(__gleGetActiveSubroutineName))
	{
		__gleGetActiveSubroutineName = gle_CoreStruct.gleVarGetActiveSubroutineName;
		if(!__gleGetActiveSubroutineName) bIsLoaded = 0;
	}
	__gleUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)gleIntGetProcAddress("glUniformSubroutinesuiv");
	if(!TestPointer(__gleUniformSubroutinesuiv))
	{
		__gleUniformSubroutinesuiv = gle_CoreStruct.gleVarUniformSubroutinesuiv;
		if(!__gleUniformSubroutinesuiv) bIsLoaded = 0;
	}
	__gleGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)gleIntGetProcAddress("glGetUniformSubroutineuiv");
	if(!TestPointer(__gleGetUniformSubroutineuiv))
	{
		__gleGetUniformSubroutineuiv = gle_CoreStruct.gleVarGetUniformSubroutineuiv;
		if(!__gleGetUniformSubroutineuiv) bIsLoaded = 0;
	}
	__gleGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)gleIntGetProcAddress("glGetProgramStageiv");
	if(!TestPointer(__gleGetProgramStageiv))
	{
		__gleGetProgramStageiv = gle_CoreStruct.gleVarGetProgramStageiv;
		if(!__gleGetProgramStageiv) bIsLoaded = 0;
	}
	glext_ARB_shader_subroutine = 1;
	return bIsLoaded;
}

static int gleIntLoadCore_4_1_Base()
{
	int bIsLoaded = 1;
	__gleVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)gleIntGetProcAddress("glVertexAttribL1d");
	if(!TestPointer(__gleVertexAttribL1d))
	{
		__gleVertexAttribL1d = gle_CoreStruct.gleVarVertexAttribL1d;
		if(!__gleVertexAttribL1d) bIsLoaded = 0;
	}
	__gleVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)gleIntGetProcAddress("glVertexAttribL2d");
	if(!TestPointer(__gleVertexAttribL2d))
	{
		__gleVertexAttribL2d = gle_CoreStruct.gleVarVertexAttribL2d;
		if(!__gleVertexAttribL2d) bIsLoaded = 0;
	}
	__gleVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)gleIntGetProcAddress("glVertexAttribL3d");
	if(!TestPointer(__gleVertexAttribL3d))
	{
		__gleVertexAttribL3d = gle_CoreStruct.gleVarVertexAttribL3d;
		if(!__gleVertexAttribL3d) bIsLoaded = 0;
	}
	__gleVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)gleIntGetProcAddress("glVertexAttribL4d");
	if(!TestPointer(__gleVertexAttribL4d))
	{
		__gleVertexAttribL4d = gle_CoreStruct.gleVarVertexAttribL4d;
		if(!__gleVertexAttribL4d) bIsLoaded = 0;
	}
	__gleVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)gleIntGetProcAddress("glVertexAttribL1dv");
	if(!TestPointer(__gleVertexAttribL1dv))
	{
		__gleVertexAttribL1dv = gle_CoreStruct.gleVarVertexAttribL1dv;
		if(!__gleVertexAttribL1dv) bIsLoaded = 0;
	}
	__gleVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)gleIntGetProcAddress("glVertexAttribL2dv");
	if(!TestPointer(__gleVertexAttribL2dv))
	{
		__gleVertexAttribL2dv = gle_CoreStruct.gleVarVertexAttribL2dv;
		if(!__gleVertexAttribL2dv) bIsLoaded = 0;
	}
	__gleVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)gleIntGetProcAddress("glVertexAttribL3dv");
	if(!TestPointer(__gleVertexAttribL3dv))
	{
		__gleVertexAttribL3dv = gle_CoreStruct.gleVarVertexAttribL3dv;
		if(!__gleVertexAttribL3dv) bIsLoaded = 0;
	}
	__gleVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)gleIntGetProcAddress("glVertexAttribL4dv");
	if(!TestPointer(__gleVertexAttribL4dv))
	{
		__gleVertexAttribL4dv = gle_CoreStruct.gleVarVertexAttribL4dv;
		if(!__gleVertexAttribL4dv) bIsLoaded = 0;
	}
	__gleVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)gleIntGetProcAddress("glVertexAttribLPointer");
	if(!TestPointer(__gleVertexAttribLPointer))
	{
		__gleVertexAttribLPointer = gle_CoreStruct.gleVarVertexAttribLPointer;
		if(!__gleVertexAttribLPointer) bIsLoaded = 0;
	}
	__gleGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)gleIntGetProcAddress("glGetVertexAttribLdv");
	if(!TestPointer(__gleGetVertexAttribLdv))
	{
		__gleGetVertexAttribLdv = gle_CoreStruct.gleVarGetVertexAttribLdv;
		if(!__gleGetVertexAttribLdv) bIsLoaded = 0;
	}
	glext_ARB_vertex_attrib_64bit = 1;
	__gleViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)gleIntGetProcAddress("glViewportArrayv");
	if(!TestPointer(__gleViewportArrayv))
	{
		__gleViewportArrayv = gle_CoreStruct.gleVarViewportArrayv;
		if(!__gleViewportArrayv) bIsLoaded = 0;
	}
	__gleViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)gleIntGetProcAddress("glViewportIndexedf");
	if(!TestPointer(__gleViewportIndexedf))
	{
		__gleViewportIndexedf = gle_CoreStruct.gleVarViewportIndexedf;
		if(!__gleViewportIndexedf) bIsLoaded = 0;
	}
	__gleViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)gleIntGetProcAddress("glViewportIndexedfv");
	if(!TestPointer(__gleViewportIndexedfv))
	{
		__gleViewportIndexedfv = gle_CoreStruct.gleVarViewportIndexedfv;
		if(!__gleViewportIndexedfv) bIsLoaded = 0;
	}
	__gleScissorArrayv = (PFNGLSCISSORARRAYVPROC)gleIntGetProcAddress("glScissorArrayv");
	if(!TestPointer(__gleScissorArrayv))
	{
		__gleScissorArrayv = gle_CoreStruct.gleVarScissorArrayv;
		if(!__gleScissorArrayv) bIsLoaded = 0;
	}
	__gleScissorIndexed = (PFNGLSCISSORINDEXEDPROC)gleIntGetProcAddress("glScissorIndexed");
	if(!TestPointer(__gleScissorIndexed))
	{
		__gleScissorIndexed = gle_CoreStruct.gleVarScissorIndexed;
		if(!__gleScissorIndexed) bIsLoaded = 0;
	}
	__gleScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)gleIntGetProcAddress("glScissorIndexedv");
	if(!TestPointer(__gleScissorIndexedv))
	{
		__gleScissorIndexedv = gle_CoreStruct.gleVarScissorIndexedv;
		if(!__gleScissorIndexedv) bIsLoaded = 0;
	}
	__gleDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)gleIntGetProcAddress("glDepthRangeArrayv");
	if(!TestPointer(__gleDepthRangeArrayv))
	{
		__gleDepthRangeArrayv = gle_CoreStruct.gleVarDepthRangeArrayv;
		if(!__gleDepthRangeArrayv) bIsLoaded = 0;
	}
	__gleDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)gleIntGetProcAddress("glDepthRangeIndexed");
	if(!TestPointer(__gleDepthRangeIndexed))
	{
		__gleDepthRangeIndexed = gle_CoreStruct.gleVarDepthRangeIndexed;
		if(!__gleDepthRangeIndexed) bIsLoaded = 0;
	}
	__gleGetFloati_v = (PFNGLGETFLOATI_VPROC)gleIntGetProcAddress("glGetFloati_v");
	if(!TestPointer(__gleGetFloati_v))
	{
		__gleGetFloati_v = gle_CoreStruct.gleVarGetFloati_v;
		if(!__gleGetFloati_v) bIsLoaded = 0;
	}
	__gleGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)gleIntGetProcAddress("glGetDoublei_v");
	if(!TestPointer(__gleGetDoublei_v))
	{
		__gleGetDoublei_v = gle_CoreStruct.gleVarGetDoublei_v;
		if(!__gleGetDoublei_v) bIsLoaded = 0;
	}
	glext_ARB_viewport_array = 1;
	__gleUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)gleIntGetProcAddress("glUseProgramStages");
	if(!TestPointer(__gleUseProgramStages))
	{
		__gleUseProgramStages = gle_CoreStruct.gleVarUseProgramStages;
		if(!__gleUseProgramStages) bIsLoaded = 0;
	}
	__gleActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)gleIntGetProcAddress("glActiveShaderProgram");
	if(!TestPointer(__gleActiveShaderProgram))
	{
		__gleActiveShaderProgram = gle_CoreStruct.gleVarActiveShaderProgram;
		if(!__gleActiveShaderProgram) bIsLoaded = 0;
	}
	__gleCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)gleIntGetProcAddress("glCreateShaderProgramv");
	if(!TestPointer(__gleCreateShaderProgramv))
	{
		__gleCreateShaderProgramv = gle_CoreStruct.gleVarCreateShaderProgramv;
		if(!__gleCreateShaderProgramv) bIsLoaded = 0;
	}
	__gleBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)gleIntGetProcAddress("glBindProgramPipeline");
	if(!TestPointer(__gleBindProgramPipeline))
	{
		__gleBindProgramPipeline = gle_CoreStruct.gleVarBindProgramPipeline;
		if(!__gleBindProgramPipeline) bIsLoaded = 0;
	}
	__gleDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)gleIntGetProcAddress("glDeleteProgramPipelines");
	if(!TestPointer(__gleDeleteProgramPipelines))
	{
		__gleDeleteProgramPipelines = gle_CoreStruct.gleVarDeleteProgramPipelines;
		if(!__gleDeleteProgramPipelines) bIsLoaded = 0;
	}
	__gleGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)gleIntGetProcAddress("glGenProgramPipelines");
	if(!TestPointer(__gleGenProgramPipelines))
	{
		__gleGenProgramPipelines = gle_CoreStruct.gleVarGenProgramPipelines;
		if(!__gleGenProgramPipelines) bIsLoaded = 0;
	}
	__gleIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)gleIntGetProcAddress("glIsProgramPipeline");
	if(!TestPointer(__gleIsProgramPipeline))
	{
		__gleIsProgramPipeline = gle_CoreStruct.gleVarIsProgramPipeline;
		if(!__gleIsProgramPipeline) bIsLoaded = 0;
	}
	__gleGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)gleIntGetProcAddress("glGetProgramPipelineiv");
	if(!TestPointer(__gleGetProgramPipelineiv))
	{
		__gleGetProgramPipelineiv = gle_CoreStruct.gleVarGetProgramPipelineiv;
		if(!__gleGetProgramPipelineiv) bIsLoaded = 0;
	}
	__gleProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)gleIntGetProcAddress("glProgramUniform1i");
	if(!TestPointer(__gleProgramUniform1i))
	{
		__gleProgramUniform1i = gle_CoreStruct.gleVarProgramUniform1i;
		if(!__gleProgramUniform1i) bIsLoaded = 0;
	}
	__gleProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)gleIntGetProcAddress("glProgramUniform1iv");
	if(!TestPointer(__gleProgramUniform1iv))
	{
		__gleProgramUniform1iv = gle_CoreStruct.gleVarProgramUniform1iv;
		if(!__gleProgramUniform1iv) bIsLoaded = 0;
	}
	__gleProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)gleIntGetProcAddress("glProgramUniform1f");
	if(!TestPointer(__gleProgramUniform1f))
	{
		__gleProgramUniform1f = gle_CoreStruct.gleVarProgramUniform1f;
		if(!__gleProgramUniform1f) bIsLoaded = 0;
	}
	__gleProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)gleIntGetProcAddress("glProgramUniform1fv");
	if(!TestPointer(__gleProgramUniform1fv))
	{
		__gleProgramUniform1fv = gle_CoreStruct.gleVarProgramUniform1fv;
		if(!__gleProgramUniform1fv) bIsLoaded = 0;
	}
	__gleProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)gleIntGetProcAddress("glProgramUniform1d");
	if(!TestPointer(__gleProgramUniform1d))
	{
		__gleProgramUniform1d = gle_CoreStruct.gleVarProgramUniform1d;
		if(!__gleProgramUniform1d) bIsLoaded = 0;
	}
	__gleProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)gleIntGetProcAddress("glProgramUniform1dv");
	if(!TestPointer(__gleProgramUniform1dv))
	{
		__gleProgramUniform1dv = gle_CoreStruct.gleVarProgramUniform1dv;
		if(!__gleProgramUniform1dv) bIsLoaded = 0;
	}
	__gleProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)gleIntGetProcAddress("glProgramUniform1ui");
	if(!TestPointer(__gleProgramUniform1ui))
	{
		__gleProgramUniform1ui = gle_CoreStruct.gleVarProgramUniform1ui;
		if(!__gleProgramUniform1ui) bIsLoaded = 0;
	}
	__gleProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)gleIntGetProcAddress("glProgramUniform1uiv");
	if(!TestPointer(__gleProgramUniform1uiv))
	{
		__gleProgramUniform1uiv = gle_CoreStruct.gleVarProgramUniform1uiv;
		if(!__gleProgramUniform1uiv) bIsLoaded = 0;
	}
	__gleProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)gleIntGetProcAddress("glProgramUniform2i");
	if(!TestPointer(__gleProgramUniform2i))
	{
		__gleProgramUniform2i = gle_CoreStruct.gleVarProgramUniform2i;
		if(!__gleProgramUniform2i) bIsLoaded = 0;
	}
	__gleProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)gleIntGetProcAddress("glProgramUniform2iv");
	if(!TestPointer(__gleProgramUniform2iv))
	{
		__gleProgramUniform2iv = gle_CoreStruct.gleVarProgramUniform2iv;
		if(!__gleProgramUniform2iv) bIsLoaded = 0;
	}
	__gleProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)gleIntGetProcAddress("glProgramUniform2f");
	if(!TestPointer(__gleProgramUniform2f))
	{
		__gleProgramUniform2f = gle_CoreStruct.gleVarProgramUniform2f;
		if(!__gleProgramUniform2f) bIsLoaded = 0;
	}
	__gleProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)gleIntGetProcAddress("glProgramUniform2fv");
	if(!TestPointer(__gleProgramUniform2fv))
	{
		__gleProgramUniform2fv = gle_CoreStruct.gleVarProgramUniform2fv;
		if(!__gleProgramUniform2fv) bIsLoaded = 0;
	}
	__gleProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)gleIntGetProcAddress("glProgramUniform2d");
	if(!TestPointer(__gleProgramUniform2d))
	{
		__gleProgramUniform2d = gle_CoreStruct.gleVarProgramUniform2d;
		if(!__gleProgramUniform2d) bIsLoaded = 0;
	}
	__gleProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)gleIntGetProcAddress("glProgramUniform2dv");
	if(!TestPointer(__gleProgramUniform2dv))
	{
		__gleProgramUniform2dv = gle_CoreStruct.gleVarProgramUniform2dv;
		if(!__gleProgramUniform2dv) bIsLoaded = 0;
	}
	__gleProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)gleIntGetProcAddress("glProgramUniform2ui");
	if(!TestPointer(__gleProgramUniform2ui))
	{
		__gleProgramUniform2ui = gle_CoreStruct.gleVarProgramUniform2ui;
		if(!__gleProgramUniform2ui) bIsLoaded = 0;
	}
	__gleProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)gleIntGetProcAddress("glProgramUniform2uiv");
	if(!TestPointer(__gleProgramUniform2uiv))
	{
		__gleProgramUniform2uiv = gle_CoreStruct.gleVarProgramUniform2uiv;
		if(!__gleProgramUniform2uiv) bIsLoaded = 0;
	}
	__gleProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)gleIntGetProcAddress("glProgramUniform3i");
	if(!TestPointer(__gleProgramUniform3i))
	{
		__gleProgramUniform3i = gle_CoreStruct.gleVarProgramUniform3i;
		if(!__gleProgramUniform3i) bIsLoaded = 0;
	}
	__gleProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)gleIntGetProcAddress("glProgramUniform3iv");
	if(!TestPointer(__gleProgramUniform3iv))
	{
		__gleProgramUniform3iv = gle_CoreStruct.gleVarProgramUniform3iv;
		if(!__gleProgramUniform3iv) bIsLoaded = 0;
	}
	__gleProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)gleIntGetProcAddress("glProgramUniform3f");
	if(!TestPointer(__gleProgramUniform3f))
	{
		__gleProgramUniform3f = gle_CoreStruct.gleVarProgramUniform3f;
		if(!__gleProgramUniform3f) bIsLoaded = 0;
	}
	__gleProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)gleIntGetProcAddress("glProgramUniform3fv");
	if(!TestPointer(__gleProgramUniform3fv))
	{
		__gleProgramUniform3fv = gle_CoreStruct.gleVarProgramUniform3fv;
		if(!__gleProgramUniform3fv) bIsLoaded = 0;
	}
	__gleProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)gleIntGetProcAddress("glProgramUniform3d");
	if(!TestPointer(__gleProgramUniform3d))
	{
		__gleProgramUniform3d = gle_CoreStruct.gleVarProgramUniform3d;
		if(!__gleProgramUniform3d) bIsLoaded = 0;
	}
	__gleProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)gleIntGetProcAddress("glProgramUniform3dv");
	if(!TestPointer(__gleProgramUniform3dv))
	{
		__gleProgramUniform3dv = gle_CoreStruct.gleVarProgramUniform3dv;
		if(!__gleProgramUniform3dv) bIsLoaded = 0;
	}
	__gleProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)gleIntGetProcAddress("glProgramUniform3ui");
	if(!TestPointer(__gleProgramUniform3ui))
	{
		__gleProgramUniform3ui = gle_CoreStruct.gleVarProgramUniform3ui;
		if(!__gleProgramUniform3ui) bIsLoaded = 0;
	}
	__gleProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)gleIntGetProcAddress("glProgramUniform3uiv");
	if(!TestPointer(__gleProgramUniform3uiv))
	{
		__gleProgramUniform3uiv = gle_CoreStruct.gleVarProgramUniform3uiv;
		if(!__gleProgramUniform3uiv) bIsLoaded = 0;
	}
	__gleProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)gleIntGetProcAddress("glProgramUniform4i");
	if(!TestPointer(__gleProgramUniform4i))
	{
		__gleProgramUniform4i = gle_CoreStruct.gleVarProgramUniform4i;
		if(!__gleProgramUniform4i) bIsLoaded = 0;
	}
	__gleProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)gleIntGetProcAddress("glProgramUniform4iv");
	if(!TestPointer(__gleProgramUniform4iv))
	{
		__gleProgramUniform4iv = gle_CoreStruct.gleVarProgramUniform4iv;
		if(!__gleProgramUniform4iv) bIsLoaded = 0;
	}
	__gleProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)gleIntGetProcAddress("glProgramUniform4f");
	if(!TestPointer(__gleProgramUniform4f))
	{
		__gleProgramUniform4f = gle_CoreStruct.gleVarProgramUniform4f;
		if(!__gleProgramUniform4f) bIsLoaded = 0;
	}
	__gleProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)gleIntGetProcAddress("glProgramUniform4fv");
	if(!TestPointer(__gleProgramUniform4fv))
	{
		__gleProgramUniform4fv = gle_CoreStruct.gleVarProgramUniform4fv;
		if(!__gleProgramUniform4fv) bIsLoaded = 0;
	}
	__gleProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)gleIntGetProcAddress("glProgramUniform4d");
	if(!TestPointer(__gleProgramUniform4d))
	{
		__gleProgramUniform4d = gle_CoreStruct.gleVarProgramUniform4d;
		if(!__gleProgramUniform4d) bIsLoaded = 0;
	}
	__gleProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)gleIntGetProcAddress("glProgramUniform4dv");
	if(!TestPointer(__gleProgramUniform4dv))
	{
		__gleProgramUniform4dv = gle_CoreStruct.gleVarProgramUniform4dv;
		if(!__gleProgramUniform4dv) bIsLoaded = 0;
	}
	__gleProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)gleIntGetProcAddress("glProgramUniform4ui");
	if(!TestPointer(__gleProgramUniform4ui))
	{
		__gleProgramUniform4ui = gle_CoreStruct.gleVarProgramUniform4ui;
		if(!__gleProgramUniform4ui) bIsLoaded = 0;
	}
	__gleProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)gleIntGetProcAddress("glProgramUniform4uiv");
	if(!TestPointer(__gleProgramUniform4uiv))
	{
		__gleProgramUniform4uiv = gle_CoreStruct.gleVarProgramUniform4uiv;
		if(!__gleProgramUniform4uiv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2fv");
	if(!TestPointer(__gleProgramUniformMatrix2fv))
	{
		__gleProgramUniformMatrix2fv = gle_CoreStruct.gleVarProgramUniformMatrix2fv;
		if(!__gleProgramUniformMatrix2fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3fv");
	if(!TestPointer(__gleProgramUniformMatrix3fv))
	{
		__gleProgramUniformMatrix3fv = gle_CoreStruct.gleVarProgramUniformMatrix3fv;
		if(!__gleProgramUniformMatrix3fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4fv");
	if(!TestPointer(__gleProgramUniformMatrix4fv))
	{
		__gleProgramUniformMatrix4fv = gle_CoreStruct.gleVarProgramUniformMatrix4fv;
		if(!__gleProgramUniformMatrix4fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2dv");
	if(!TestPointer(__gleProgramUniformMatrix2dv))
	{
		__gleProgramUniformMatrix2dv = gle_CoreStruct.gleVarProgramUniformMatrix2dv;
		if(!__gleProgramUniformMatrix2dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3dv");
	if(!TestPointer(__gleProgramUniformMatrix3dv))
	{
		__gleProgramUniformMatrix3dv = gle_CoreStruct.gleVarProgramUniformMatrix3dv;
		if(!__gleProgramUniformMatrix3dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4dv");
	if(!TestPointer(__gleProgramUniformMatrix4dv))
	{
		__gleProgramUniformMatrix4dv = gle_CoreStruct.gleVarProgramUniformMatrix4dv;
		if(!__gleProgramUniformMatrix4dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3fv");
	if(!TestPointer(__gleProgramUniformMatrix2x3fv))
	{
		__gleProgramUniformMatrix2x3fv = gle_CoreStruct.gleVarProgramUniformMatrix2x3fv;
		if(!__gleProgramUniformMatrix2x3fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2fv");
	if(!TestPointer(__gleProgramUniformMatrix3x2fv))
	{
		__gleProgramUniformMatrix3x2fv = gle_CoreStruct.gleVarProgramUniformMatrix3x2fv;
		if(!__gleProgramUniformMatrix3x2fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4fv");
	if(!TestPointer(__gleProgramUniformMatrix2x4fv))
	{
		__gleProgramUniformMatrix2x4fv = gle_CoreStruct.gleVarProgramUniformMatrix2x4fv;
		if(!__gleProgramUniformMatrix2x4fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2fv");
	if(!TestPointer(__gleProgramUniformMatrix4x2fv))
	{
		__gleProgramUniformMatrix4x2fv = gle_CoreStruct.gleVarProgramUniformMatrix4x2fv;
		if(!__gleProgramUniformMatrix4x2fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4fv");
	if(!TestPointer(__gleProgramUniformMatrix3x4fv))
	{
		__gleProgramUniformMatrix3x4fv = gle_CoreStruct.gleVarProgramUniformMatrix3x4fv;
		if(!__gleProgramUniformMatrix3x4fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3fv");
	if(!TestPointer(__gleProgramUniformMatrix4x3fv))
	{
		__gleProgramUniformMatrix4x3fv = gle_CoreStruct.gleVarProgramUniformMatrix4x3fv;
		if(!__gleProgramUniformMatrix4x3fv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x3dv");
	if(!TestPointer(__gleProgramUniformMatrix2x3dv))
	{
		__gleProgramUniformMatrix2x3dv = gle_CoreStruct.gleVarProgramUniformMatrix2x3dv;
		if(!__gleProgramUniformMatrix2x3dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x2dv");
	if(!TestPointer(__gleProgramUniformMatrix3x2dv))
	{
		__gleProgramUniformMatrix3x2dv = gle_CoreStruct.gleVarProgramUniformMatrix3x2dv;
		if(!__gleProgramUniformMatrix3x2dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix2x4dv");
	if(!TestPointer(__gleProgramUniformMatrix2x4dv))
	{
		__gleProgramUniformMatrix2x4dv = gle_CoreStruct.gleVarProgramUniformMatrix2x4dv;
		if(!__gleProgramUniformMatrix2x4dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x2dv");
	if(!TestPointer(__gleProgramUniformMatrix4x2dv))
	{
		__gleProgramUniformMatrix4x2dv = gle_CoreStruct.gleVarProgramUniformMatrix4x2dv;
		if(!__gleProgramUniformMatrix4x2dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)gleIntGetProcAddress("glProgramUniformMatrix3x4dv");
	if(!TestPointer(__gleProgramUniformMatrix3x4dv))
	{
		__gleProgramUniformMatrix3x4dv = gle_CoreStruct.gleVarProgramUniformMatrix3x4dv;
		if(!__gleProgramUniformMatrix3x4dv) bIsLoaded = 0;
	}
	__gleProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)gleIntGetProcAddress("glProgramUniformMatrix4x3dv");
	if(!TestPointer(__gleProgramUniformMatrix4x3dv))
	{
		__gleProgramUniformMatrix4x3dv = gle_CoreStruct.gleVarProgramUniformMatrix4x3dv;
		if(!__gleProgramUniformMatrix4x3dv) bIsLoaded = 0;
	}
	__gleValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)gleIntGetProcAddress("glValidateProgramPipeline");
	if(!TestPointer(__gleValidateProgramPipeline))
	{
		__gleValidateProgramPipeline = gle_CoreStruct.gleVarValidateProgramPipeline;
		if(!__gleValidateProgramPipeline) bIsLoaded = 0;
	}
	__gleGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)gleIntGetProcAddress("glGetProgramPipelineInfoLog");
	if(!TestPointer(__gleGetProgramPipelineInfoLog))
	{
		__gleGetProgramPipelineInfoLog = gle_CoreStruct.gleVarGetProgramPipelineInfoLog;
		if(!__gleGetProgramPipelineInfoLog) bIsLoaded = 0;
	}
	glext_ARB_separate_shader_objects = 1;
	__gleGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)gleIntGetProcAddress("glGetProgramBinary");
	if(!TestPointer(__gleGetProgramBinary))
	{
		__gleGetProgramBinary = gle_CoreStruct.gleVarGetProgramBinary;
		if(!__gleGetProgramBinary) bIsLoaded = 0;
	}
	__gleProgramBinary = (PFNGLPROGRAMBINARYPROC)gleIntGetProcAddress("glProgramBinary");
	if(!TestPointer(__gleProgramBinary))
	{
		__gleProgramBinary = gle_CoreStruct.gleVarProgramBinary;
		if(!__gleProgramBinary) bIsLoaded = 0;
	}
	__gleProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)gleIntGetProcAddress("glProgramParameteri");
	if(!TestPointer(__gleProgramParameteri))
	{
		__gleProgramParameteri = gle_CoreStruct.gleVarProgramParameteri;
		if(!__gleProgramParameteri) bIsLoaded = 0;
	}
	glext_ARB_get_program_binary = 1;
	__gleReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)gleIntGetProcAddress("glReleaseShaderCompiler");
	if(!TestPointer(__gleReleaseShaderCompiler))
	{
		__gleReleaseShaderCompiler = gle_CoreStruct.gleVarReleaseShaderCompiler;
		if(!__gleReleaseShaderCompiler) bIsLoaded = 0;
	}
	__gleShaderBinary = (PFNGLSHADERBINARYPROC)gleIntGetProcAddress("glShaderBinary");
	if(!TestPointer(__gleShaderBinary))
	{
		__gleShaderBinary = gle_CoreStruct.gleVarShaderBinary;
		if(!__gleShaderBinary) bIsLoaded = 0;
	}
	__gleGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)gleIntGetProcAddress("glGetShaderPrecisionFormat");
	if(!TestPointer(__gleGetShaderPrecisionFormat))
	{
		__gleGetShaderPrecisionFormat = gle_CoreStruct.gleVarGetShaderPrecisionFormat;
		if(!__gleGetShaderPrecisionFormat) bIsLoaded = 0;
	}
	__gleDepthRangef = (PFNGLDEPTHRANGEFPROC)gleIntGetProcAddress("glDepthRangef");
	if(!TestPointer(__gleDepthRangef))
	{
		__gleDepthRangef = gle_CoreStruct.gleVarDepthRangef;
		if(!__gleDepthRangef) bIsLoaded = 0;
	}
	__gleClearDepthf = (PFNGLCLEARDEPTHFPROC)gleIntGetProcAddress("glClearDepthf");
	if(!TestPointer(__gleClearDepthf))
	{
		__gleClearDepthf = gle_CoreStruct.gleVarClearDepthf;
		if(!__gleClearDepthf) bIsLoaded = 0;
	}
	glext_ARB_ES2_compatibility = 1;
	return bIsLoaded;
}

int gleIntLoad_Version_2_1()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_0()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_1()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_1_Comp()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_2()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_2_Comp()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_3()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_3_3_Comp()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_4_0()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_0_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_4_0_Comp()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_0_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_4_1()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Version_3_1()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_1_Base()) bIsLoaded = 0;

	return bIsLoaded;
}

int gleIntLoad_Version_4_1_Comp()
{
	int bIsLoaded = 1;
	gleIntClear();
	gleIntCoreInit();
	if(!gleIntLoadCore_1_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_4_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_1_5_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_2_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_1_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_2_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_3_3_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_0_Base()) bIsLoaded = 0;
	if(!gleIntLoadCore_4_1_Base()) bIsLoaded = 0;

	return bIsLoaded;
}


void gleIntLoadBaseFuncs()
{
	int bIsLoaded = 1; //Unimportant here.
	gleIntCoreInit();
	__gleGetString = (PFNGLGETSTRINGPROC)gleIntGetProcAddress("glGetString");
	if(!TestPointer(__gleGetString))
	{
		__gleGetString = gle_CoreStruct.gleVarGetString;
		if(!__gleGetString) bIsLoaded = 0;
	}
	__gleGetStringi = (PFNGLGETSTRINGIPROC)gleIntGetProcAddress("glGetStringi");
	if(!TestPointer(__gleGetStringi))
	{
		__gleGetStringi = gle_CoreStruct.gleVarGetStringi;
		if(!__gleGetStringi) bIsLoaded = 0;
	}
	__gleGetIntegerv = (PFNGLGETINTEGERVPROC)gleIntGetProcAddress("glGetIntegerv");
	if(!TestPointer(__gleGetIntegerv))
	{
		__gleGetIntegerv = gle_CoreStruct.gleVarGetIntegerv;
		if(!__gleGetIntegerv) bIsLoaded = 0;
	}
}
