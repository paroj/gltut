/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_GENERATOR_DESCRIPTORS_H
#define GLSDK_MESH_GENERATOR_DESCRIPTORS_H

/**
\file
\brief Describes the mesh generator flags.

**/

namespace glmesh
{
	namespace gen
	{
		enum StandardAttributeIndices
		{
			ATTR_POS = 0,
			ATTR_COLOR = 1,
			ATTR_NORMAL = 2,
			ATTR_TANGENT = 3,
			ATTR_BITANGENT = 4,
			ATTR_TEXCOORD = 5,
		};
	}
}




#endif //GLSDK_MESH_GENERATOR_DESCRIPTORS_H
