/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_GENERATE_QUADRICS_H
#define GLSDK_MESH_GENERATE_QUADRICS_H

/**
\file
\brief Defines mesh generators for various quadric and curved surfaces.
**/

#include "GenDescriptors.h"

namespace glmesh
{
	class Mesh;

	namespace gen
	{
		///\addtogroup module_glmesh_mesh_generator
		///@{

		/**
		\name Quadric Surfaces
		[Quadric Surfaces](http://en.wikipedia.org/wiki/Quadric) are curved surfaces defined by
		multi-dimensional quadratic equations. It is a special class of surface that includes
		cones, cylinders, and spheres. These functions generate unit meshes for these shapes.
		**/
		///@{

		/**
		\brief Creates a unit sphere at the origin.

		A unit sphere is a sphere of radius 1, so it extends from [-1, 1] in all three axes.

		Available attributes:

		\li normal
		\li texture coordinate: It has a degeneracy at the top and bottom.

		\param numHorizSlices The number of horizontal slices of the sphere. More slices make it smoother.
		\param numVertSlices The number of vertical slices of the sphere. More slices make it smoother.
		**/
		Mesh *UnitSphere(int numHorizSlices, int numVertSlices);

		///@}

		///@}
	}
}



#endif //GLSDK_MESH_GENERATE_QUADRICS_H
