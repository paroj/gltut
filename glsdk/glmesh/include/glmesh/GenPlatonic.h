/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_GENERATE_PLATONIC_H
#define GLSDK_MESH_GENERATE_PLATONIC_H

/**
\file
\brief Defines mesh generators for the Platonic solids.
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
		\name Platonic Solids
		These functions generate meshes for the 5 Platonic solids. All of them take an optional
		list of colors to be applied to faces. All of them provide face normals, since they
		are all faceted.
		**/
		///@{

		/**
		\brief Generates a regular, unit tetrahedron.

		A tetrahedron is a 4-sided, triangular solid. It is regular in the sense that all of
		the triangles used to construct it are equilateral.

		The tetrahedron is generated with one vertex pointed in the +Y direction,
		with the flat size directly facing the -Y direction. It is a regular tetrahedron,
		so all of the triangles are equilateral. The geometric center of the tetrahedron is
		at the origin. The points of the tetrahedron are within the [-1, 1] range of the origin.

		The top point of the tetrahedron is exactly at (0, 1, 0).

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.
		**/
		Mesh *Tetrahedron(const ColorArray &colorSequence = ColorArray());

		/**
		\brief Generates a unit cube.

		A cube is... OK, do you really need me to tell you what a \em cube is?

		The cube is on the range [-1, 1], so the lengths of its sides are 2. The cube is axis-aligned.

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.

		The order of the colors is such that, if you pass a 3 element list, then each pair of
		faces on opposite sides of the cube will have the same color. The order of colors is:
		+Y, +X, +Z, -Y, -X, -Z.
		**/
		Mesh *Cube(const ColorArray &colorSequence = ColorArray());

		/**
		\brief Generates a regular, unit octahedron.

		An octahedron is an 8-sided, triangular solid. It is regular in that all of the triangles used
		in creating it are equilateral.

		The octahedron's 6 vertices point in the axial directions. All of the points lie in [-1, 1],
		and the 6 positions are all right on the border.

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.

		**/
		Mesh *Octahedron(const ColorArray &colorSequence = ColorArray());

		/**
		\brief Generates a regular, (nearly) unit dodecahedron.

		A dodecahedron is a 12-sided solid, where each face is a pentagon. It is regular in that
		the pentagonal faces are all equilateral.

		The dodecahedron is oriented so that two opposite faces face directly in the +Y and -Y
		axes.
		
		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.

		Note that the color here represents the color per \em face, not just per
		triangle used to build that face. So each of the triangles in a pentagon gets the same color.
		The order of the colors is such that, if you provide 6 colors, then the opposite faces will
		all have the same color.
		
		The first color is for the top face (+Y). The next 5 are for the faces that point in the +Y axis,
		starting from the one facing directly +X (with no Z in its facing). These proceed clockwise, as
		seen when looking down at the dodecahedron. The other 6 faces are the opposing faces for those
		faces.
		**/
		Mesh *Dodecahedron(const ColorArray &colorSequence = ColorArray());

		/**
		\brief Generates a regular, unit icosahedron.

		An icosahedron is a 20-sided, triangular solid. It is regular in that all of the triangles
		used in creating it are equilateral.

		The icosahedron is oriented so that two opposite vertices are in the +Y and -Y axes.

		Available attributes:
		\li normals
		\li color, if you pass a non-empty \a colorSequence argument.
		
		**/
		Mesh *Icosahedron(const ColorArray &colorSequence = ColorArray());

		///@}


		///@}
	}
}

#endif //GLSDK_MESH_GENERATE_PLATONIC_H
