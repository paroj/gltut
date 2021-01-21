/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_GENERATE_MISCELLANEOUS_H
#define GLSDK_MESH_GENERATE_MISCELLANEOUS_H

/**
\file
\brief Various miscellaneous mesh generators.
**/

#include "GenDescriptors.h"
#include "GenCommon.h"

namespace glmesh
{
	class Mesh;

	namespace gen
	{
		///\addtogroup module_glmesh_mesh_generator
		///@{

		/**
		\brief A mesh of a full-screen quad. Useful for post-processing effects.

		This is a quad that covers the screen. Your vertex shader should pass the positions without
		transformation. The positions are already in clip-space.

		This mesh has only the position attribute. The position's Z is always 0, and the W is 1.
		**/
		Mesh *FullScreenQuad();

		/**
		\brief A mesh ground plane. Can be double-sided and arbitrarily tessellated.
		
		This creates a square, on the range [-1, 1] in the XY plane (faces in the +Z direction).
		The quad can be tessellated arbitrarily, via parameters.

		Available attributes:
		\li normals
		\li texture coordinates: The lower-left corner of the texture is in the -X/-Y part of the square.

		\param numXVerts Number of vertices along the X axis. Must be 2 or greater.
		\param numYVerts Number of vertices along the Y axis. Must be 2 or greater.
		\param bDoubleSided Whether the ground is double-sided or not. If not, then CCW will point in the positive-Y.
		**/
		Mesh *GroundPlane(int numXVerts, int numYVerts, bool bDoubleSided = true);

		/**
		\name Structures
		These generators build larger, complex structures out of smaller functional units. These
		shapes are useful for showing off lighting and other effects. These functions are
		parameterized, allowing them to produce structures of arbitrary (within reason) sizes.
		**/
		///@{

		/**
		\brief Creates a cubical block of cubes in an alternating pattern.

		Each cube is a cube of size 2. The entire array will be centered around it's centerpoint.
		The array's length on one side will be `2 * (2n - 1)`, where `n` is the number of cubes on an edge.

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.
		
		\param numCubesOnEdge The number of cubes that will appear on each edge. Will be clamped to the range [1, 16384].
		\param colorSequence A series of colors used to color the faces of the objects. The order of faces is:
		+y, +x, -y, -x, +z, -z. The color used will wrap around, so if you provide 6 colors, then each cube will get
		the same six colors.
		**/
		Mesh *CubeBlock(int numCubesOnEdge, const ColorArray &colorSequence = ColorArray());

		/**
		\brief Creates a pyramid made of cubes, in an alternating pattern.

		Each cube is a cube of size 2. The pyramid will be pointing in the positive y axis.
		The entire array will be centered around its X/Z centerpoint, with the zero y at the base of the pyramid.
		The height will be `2*n`, where `n` is the number of cubes in height. The width/depth will be
		`2 * (2n - 1)`.

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.
		
		\param numCubesTall How many cubes in height the pyramid will be. Will be clamped to the range [1, 16383].
		\param colorSequence A series of colors used to color the faces of the objects. The order of faces is:
		+y, +x, -y, -x, +z, -z. The color used will wrap around, so if you provide 6 colors, then each cube will get
		the same six colors.
		**/
		Mesh *CubePyramid(int numCubesTall, const ColorArray &colorSequence = ColorArray());

		///@}

		///@}
	}
}



#endif //GLSDK_MESH_GENERATE_MISCELLANEOUS_H
