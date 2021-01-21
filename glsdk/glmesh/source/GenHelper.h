/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_GENERATOR_HELPER_H
#define GLSDK_GENERATOR_HELPER_H

#include <string>
#include "glmesh/Mesh.h"
#include "glmesh/VertexFormat.h"

//Requires having included GL defines.

namespace glmesh
{

	namespace gen
	{
		enum VariantComponents
		{
			VAR_COLOR		= 0x01,
			VAR_NORMAL		= 0x02,
			VAR_TEX_COORD	= 0x04,
		};

		//Generates a name for the given components. Just one of the names that can be used.
		std::string GenerateNameForVariant(const int components);

		void AddVariantToMap(MeshVariantMap &variantMap, GLuint vao, const int components);

		//components must be in the order of the attributes in the fmt. 0 is assumed to be the position
		//and is always there, so the first component must be 1, 2, etc. The array buffer should be bound.
		void BuildVariations(MeshVariantMap &variantMap, const std::vector<int> &components,
			const VertexFormat &fmt, GLuint indexBuffer = 0);
	}
}

#endif //GLSDK_GENERATOR_HELPER_H

