/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_GENERATOR_COMMON_H
#define GLSDK_MESH_GENERATOR_COMMON_H

#include <glutil/array_ref.h>
#include <glm/glm.hpp>

/**
\file
\brief Common user interface definitions for \ref module_glmesh_mesh_generator "mesh generation".
**/

namespace glmesh
{
	namespace gen
	{
		///A simple vec4 for colors.
		typedef glm::detail::tvec4<GLubyte> Color;

		///A user-provided array of colors for mesh generation.
		typedef refs::array_ref<Color> ColorArray;
	}
}


#endif //GLSDK_MESH_GENERATOR_COMMON_H
