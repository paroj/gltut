--[[ This function returns a table of core extensions and the versions they were made core in.

The table is indexed by extension name. Each entry contains:

* name: The name of the extension. For redundancy.
* version: The version number (as a string) that it was made core in.

This list must be manually updated, as there is no equivalent in the spec files. Just add
to the list. When a new version comes out with new core extensions, add a new list and
add the local variable name to the master table as shown below.
]]


local coreExts3_0 = {
	"ARB_vertex_array_object",
	"ARB_texture_rg",
	"ARB_texture_compression_rgtc",
	"ARB_map_buffer_range",
	"ARB_half_float_vertex",
	"ARB_framebuffer_sRGB",
	"ARB_framebuffer_object",
	"ARB_depth_buffer_float",
};

local coreExts3_1 = {
	"ARB_uniform_buffer_object",
	"ARB_copy_buffer",
};

local coreExts3_2 = {
	"ARB_depth_clamp",
	"ARB_draw_elements_base_vertex",
	"ARB_fragment_coord_conventions",
	"ARB_provoking_vertex",
	"ARB_seamless_cube_map",
	"ARB_sync",
	"ARB_texture_multisample",
	"ARB_vertex_array_bgra",
};

local coreExts3_3 = {
	"ARB_texture_rgb10_a2ui",
	"ARB_texture_swizzle",
	"ARB_timer_query",
	"ARB_vertex_type_2_10_10_10_rev",
	"ARB_blend_func_extended",
	"ARB_occlusion_query2",
	"ARB_sampler_objects",
};

local coreExts4_0 = {
	"ARB_draw_indirect",
	"ARB_gpu_shader5",
	"ARB_gpu_shader_fp64",
	"ARB_shader_subroutine",
	"ARB_tessellation_shader",
	"ARB_transform_feedback2",
	"ARB_transform_feedback3",
};

local coreExts4_1 = {
	"ARB_ES2_compatibility",
	"ARB_get_program_binary",
	"ARB_separate_shader_objects",
	"ARB_vertex_attrib_64bit",
	"ARB_viewport_array",
};

local masterTable = {
	["3.0"] = coreExts3_0,
	["3.1"] = coreExts3_1,
	["3.2"] = coreExts3_2,
	["3.3"] = coreExts3_3,
	["4.0"] = coreExts4_0,
	["4.1"] = coreExts4_1,
};


--Build the actual table.
local ret = {};
for coreVersion, coreExtList in pairs(masterTable) do
	for i, coreExt in pairs(coreExtList) do
		ret[coreExt] = {name = coreExt, version = coreVersion};
	end
end

return ret;
