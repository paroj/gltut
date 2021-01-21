//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.


#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>

//#include "glmesh/BoostDraw.h"
#include "glmesh/CpuDataWriter.h"
#include "glmesh/VertexFormat.h"

#include "glmesh/Mesh.h"
#include "glmesh/GenMeshMisc.h"
#include "GenHelper.h"
#include <glm/glm.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glmesh
{
namespace gen
{
	Mesh *FullScreenQuad()
	{
		glmesh::AttributeList attribs;
		attribs.push_back(glmesh::AttribDesc(ATTR_POS, 2, glmesh::VDT_SIGN_SHORT, glmesh::ADT_NORM_FLOAT));
		VertexFormat fmt(attribs);

		CpuDataWriter writer(fmt, 4);

		writer.Attrib<GLshort>(-32768, 32767);
		writer.Attrib<GLshort>(-32768, -32768);
		writer.Attrib<GLshort>(32767, 32767);
		writer.Attrib<GLshort>(32767, -32768);

		std::vector<GLuint> buffer(1);
		buffer[0] = writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW);
		gl::BindBuffer(gl::ARRAY_BUFFER, buffer[0]);

		MeshVariantMap variantMap;

		GLuint mainVao = 0;
		gl::GenVertexArrays(1, &mainVao);
		gl::BindVertexArray(mainVao);
		fmt.BindAttribute(0, 0);
		AddVariantToMap(variantMap, mainVao, 0);

		gl::BindVertexArray(0);
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		RenderCmdList renderCmds;
		renderCmds.DrawArrays(gl::TRIANGLE_STRIP, 0, 4);

		Mesh *pRet = new Mesh(buffer, mainVao, renderCmds, variantMap);
		return pRet;
	}

	Mesh * GroundPlane( int numXVerts, int numYVerts, bool bDoubleSided )
	{
		numXVerts = std::max(numXVerts, 2);
		numYVerts = std::max(numYVerts, 2);

		//////////////////////////////////////////////////////////////////////////
		//Generate vertex data
		glmesh::AttributeList attribs;
		attribs.push_back(glmesh::AttribDesc(ATTR_POS, 2, glmesh::VDT_SIGN_SHORT, glmesh::ADT_NORM_FLOAT));
		attribs.push_back(glmesh::AttribDesc(ATTR_NORMAL, 4, glmesh::VDT_SIGN_BYTE, glmesh::ADT_NORM_FLOAT));
		attribs.push_back(glmesh::AttribDesc(ATTR_TEXCOORD, 2, glmesh::VDT_UNSIGN_SHORT, glmesh::ADT_NORM_FLOAT));
		VertexFormat fmt(attribs);

		int numVerts = numXVerts * numYVerts;
		numVerts = bDoubleSided ? numVerts * 2 : numVerts;

		CpuDataWriter writer(fmt, numVerts);

		glm::detail::tvec4<GLbyte> normal(0, 0, 127, 0);

		for(int zVert = 0; zVert < numYVerts; ++zVert)
		{
			const float perZ = zVert == numYVerts ? 1.0f : zVert / (float)(numYVerts - 1);

			for(int xVert = 0; xVert < numXVerts; ++xVert)
			{
				const float perX = xVert == numXVerts ? 1.0f : xVert / (float)(numXVerts - 1);

				glm::detail::tvec2<GLushort> texCoord(65535 * perX, 65535 * (1.0f - perZ));

				glm::detail::tvec2<int> intPos(texCoord.x, texCoord.y);
				glm::detail::tvec2<GLshort> pos(intPos.x - 32768, intPos.y - 32768);

				writer.Attrib(pos);
				writer.Attrib(normal);
				writer.Attrib(texCoord);
			}
		}

		if(bDoubleSided)
		{
			normal = glm::detail::tvec4<GLbyte>(0, 0, -128, 0);

			for(int zVert = 0; zVert < numYVerts; ++zVert)
			{
				const float perZ = zVert == numYVerts ? 1.0f : zVert / (float)(numYVerts - 1);

				for(int xVert = 0; xVert < numXVerts; ++xVert)
				{
					const float perX = xVert == numXVerts ? 1.0f : xVert / (float)(numXVerts - 1);

					glm::detail::tvec2<GLushort> texCoord(65535 * perX, 65535 * (1.0f - perZ));

					glm::detail::tvec2<int> intPos(texCoord.x, texCoord.y);
					glm::detail::tvec2<GLshort> pos(intPos.x - 32768, intPos.y - 32768);

					writer.Attrib(pos);
					writer.Attrib(normal);
					writer.Attrib(texCoord);
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Generate index data.
		const int numRows = numYVerts - 1;
		const int numIndices = numRows * numXVerts * 2 + 1; //2 indices per row, +1 for the restart index.
		std::vector<GLuint> indices;
		indices.reserve(numIndices * 2); //Enough space for double-sided.
		const GLuint restartIx = numVerts;

		//Top side.
		for(int rowIx = 0; rowIx < numRows; ++rowIx)
		{
			for(int column = 0; column < numXVerts; ++column)
			{
				indices.push_back((rowIx * numXVerts) + column);
				indices.push_back(((rowIx + 1) * numXVerts) + column);
			}

			indices.push_back(restartIx);
		}

		if(bDoubleSided)
		{
			for(int rowIx = 0; rowIx < numRows; ++rowIx)
			{
				for(int column = 0; column < numXVerts; ++column)
				{
					//Reversed from front side.
					indices.push_back(((rowIx + 1) * numXVerts) + column + (numVerts/2));
					indices.push_back((rowIx * numXVerts) + column + (numVerts/2));
				}

				indices.push_back(restartIx);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Build the buffers.
		std::vector<GLuint> buffers(2);
		gl::GenBuffers(2, &buffers[0]);
		writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW, buffers[0]);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
			&indices[0], gl::STATIC_DRAW);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

		//Create VAOs.
		MeshVariantMap variantMap;

		gl::BindBuffer(gl::ARRAY_BUFFER, buffers[0]);

		std::vector<int> components;
		components.push_back(VAR_NORMAL);
		components.push_back(VAR_TEX_COORD);

		BuildVariations(variantMap, components, fmt, buffers[1]);

		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		//////////////////////////////////////////////////////////////////////////
		//Create rendering commands.
		RenderCmdList renderCmds;

		renderCmds.PrimitiveRestartIndex(restartIx);
		renderCmds.DrawElements(gl::TRIANGLE_STRIP, numIndices, gl::UNSIGNED_INT, 0);
		if(bDoubleSided)
		{
			renderCmds.DrawElements(gl::TRIANGLE_STRIP, numIndices, gl::UNSIGNED_INT,
				numIndices * sizeof(GLuint));
		}
		renderCmds.PrimitiveRestartIndex();

		GLuint mainVao = variantMap["lit-tex"];

		Mesh *pRet = new Mesh(buffers, mainVao, renderCmds, variantMap);
		return pRet;
	}

	Mesh * Axes( ColorArray colorSequence )
	{
		Color defaults[3] = {Color(255, 0, 0, 255), Color(0, 255, 0, 255), Color(0, 0, 255, 255)};

		if(colorSequence.size() < 3)
		{
			colorSequence = ColorArray(defaults);
		}

		glmesh::AttributeList attribs;
		attribs.push_back(glmesh::AttribDesc(ATTR_POS, 3, glmesh::VDT_SIGN_SHORT, glmesh::ADT_NORM_FLOAT));
		attribs.push_back(glmesh::AttribDesc(ATTR_COLOR, 4, glmesh::VDT_UNSIGN_BYTE, glmesh::ADT_NORM_FLOAT));

		VertexFormat fmt(attribs);

		CpuDataWriter writer(fmt, 6);

		writer.Attrib<GLshort>(32767, 0, 0);
		writer.Attrib(colorSequence[0]);
		writer.Attrib<GLshort>(0, 0, 0);
		writer.Attrib(colorSequence[0]);
		writer.Attrib<GLshort>(0, 32767, 0);
		writer.Attrib(colorSequence[1]);
		writer.Attrib<GLshort>(0, 0, 0);
		writer.Attrib(colorSequence[1]);
		writer.Attrib<GLshort>(0, 0, 32767);
		writer.Attrib(colorSequence[2]);
		writer.Attrib<GLshort>(0, 0, 0);
		writer.Attrib(colorSequence[2]);

		//////////////////////////////////////////////////////////////////////////
		//Build the buffers.
		std::vector<GLuint> buffers(1);
		gl::GenBuffers(1, &buffers[0]);
		writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW, buffers[0]);

		//Create VAOs.
		MeshVariantMap variantMap;

		gl::BindBuffer(gl::ARRAY_BUFFER, buffers[0]);

		std::vector<int> components;
		components.push_back(VAR_COLOR);

		BuildVariations(variantMap, components, fmt, 0);

		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		//////////////////////////////////////////////////////////////////////////
		//Create rendering commands.
		RenderCmdList renderCmds;

		renderCmds.DrawArrays(gl::LINES, 0, 6);

		GLuint mainVao = variantMap["color"];

		Mesh *pRet = new Mesh(buffers, mainVao, renderCmds, variantMap);
		return pRet;
	}


	namespace
	{
		typedef glm::detail::tvec3<GLshort> svec3;
		typedef glm::detail::tvec4<GLbyte> btvec4;

		/*
		Cube faces are written in this order:
		0-2
		| |
		1-3
		*/
		void WriteCubeLayer(CpuDataWriter &writer, const int numCubesOnEdge, const GLshort heightOfCenter,
			const ColorArray &colorSequence)
		{
			const svec3 cubeSides[] =
			{
				//+y
				svec3(-1,  1, -1),
				svec3(-1,  1,  1),
				svec3( 1,  1, -1),
				svec3( 1,  1,  1),

				//+x
				svec3( 1,  1, -1),
				svec3( 1,  1,  1),
				svec3( 1, -1, -1),
				svec3( 1, -1,  1),

				//-y
				svec3( 1, -1, -1),
				svec3( 1, -1,  1),
				svec3(-1, -1, -1),
				svec3(-1, -1,  1),

				//-x
				svec3(-1, -1, -1),
				svec3(-1, -1,  1),
				svec3(-1,  1, -1),
				svec3(-1,  1,  1),

				//+z
				svec3(-1,  1,  1),
				svec3(-1, -1,  1),
				svec3( 1,  1,  1),
				svec3( 1, -1,  1),

				//-z
				svec3( 1,  1, -1),
				svec3( 1, -1, -1),
				svec3(-1,  1, -1),
				svec3(-1, -1, -1),

			};

			static_assert(ARRAY_COUNT(cubeSides) == 24, "");

			const btvec4 normals[] =
			{
				btvec4(0, 127, 0, 0),
				btvec4(127, 0, 0, 0),
				btvec4(0, -128, 0, 0),
				btvec4(-128, 0, 0, 0),
				btvec4(0, 0, 127, 0),
				btvec4(0, 0, -128, 0),
			};

			static_assert(ARRAY_COUNT(normals) == 6, "");

			//The center of the current cube.
			svec3 currCube(-2 * (numCubesOnEdge - 1), heightOfCenter, -2 * (numCubesOnEdge - 1));

			size_t currColor = 0;

			for(int x = 0; x < numCubesOnEdge; ++x, currCube.x += 4)
			{
				currCube.z = -2 * (numCubesOnEdge - 1);
				for(int z = 0; z < numCubesOnEdge; z++, currCube.z += 4)
				{
					for(int face = 0; face < 6; ++face)
					{
						writer.Attrib(currCube + cubeSides[face * 4 + 0]);
						writer.Attrib(normals[face]);
						if(!colorSequence.empty())
							writer.Attrib(colorSequence[currColor]);
						writer.Attrib(currCube + cubeSides[face * 4 + 1]);
						writer.Attrib(normals[face]);
						if(!colorSequence.empty())
							writer.Attrib(colorSequence[currColor]);
						writer.Attrib(currCube + cubeSides[face * 4 + 2]);
						writer.Attrib(normals[face]);
						if(!colorSequence.empty())
							writer.Attrib(colorSequence[currColor]);
						writer.Attrib(currCube + cubeSides[face * 4 + 3]);
						writer.Attrib(normals[face]);
						if(!colorSequence.empty())
							writer.Attrib(colorSequence[currColor]);

						if(!colorSequence.empty())
						{
							++currColor;
							currColor = currColor % colorSequence.size();
						}
					}
				}
			}
		}
	}

	Mesh * CubeBlock( int numCubesOnEdge, const ColorArray &colorSequence )
	{
		numCubesOnEdge = std::max(numCubesOnEdge, 1);
		numCubesOnEdge = std::min(numCubesOnEdge, 16384); //Because we're using shorts.

		const int numLayers = (2 * numCubesOnEdge) - 1;

		const int cubesPerBigLayer = numCubesOnEdge * numCubesOnEdge;
		const int cubesPerSmallLayer = (numCubesOnEdge - 1) * (numCubesOnEdge - 1);

		const int numCubesTotal = (cubesPerBigLayer * numCubesOnEdge) +
			(cubesPerSmallLayer * (numCubesOnEdge-1));

		//////////////////////////////////////////////////////////////////////////
		//Generate vertex data
		glmesh::AttributeList attribs;
		attribs.push_back(glmesh::AttribDesc(ATTR_POS, 3, glmesh::VDT_SIGN_SHORT, glmesh::ADT_FLOAT));
		attribs.push_back(glmesh::AttribDesc(ATTR_NORMAL, 4, glmesh::VDT_SIGN_BYTE, glmesh::ADT_NORM_FLOAT));
		if(!colorSequence.empty())
			attribs.push_back(glmesh::AttribDesc(ATTR_COLOR, 4, glmesh::VDT_UNSIGN_BYTE, glmesh::ADT_NORM_FLOAT));
		VertexFormat fmt(attribs);

		CpuDataWriter writer(fmt,  numCubesTotal * 24);
		GLshort height = 2 * (numCubesOnEdge - 1);

		for(int layer = 0; layer < numLayers; ++layer, height -= 2)
		{
			WriteCubeLayer(writer, layer % 2 ? numCubesOnEdge - 1 : numCubesOnEdge, height, colorSequence);
		}

		//////////////////////////////////////////////////////////////////////////
		//Generate index data.
		std::vector<GLuint> indices;
		indices.reserve(numCubesTotal * 36); //Drawn as triangles.

		for(int cube = 0; cube < (numCubesTotal * 6); ++cube)
		{
			indices.push_back((cube * 4) + 0);
			indices.push_back((cube * 4) + 1);
			indices.push_back((cube * 4) + 2);

			indices.push_back((cube * 4) + 2);
			indices.push_back((cube * 4) + 1);
			indices.push_back((cube * 4) + 3);
		}

		//////////////////////////////////////////////////////////////////////////
		//Build the buffers.
		std::vector<GLuint> buffers(2);
		gl::GenBuffers(2, &buffers[0]);
		writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW, buffers[0]);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
			&indices[0], gl::STATIC_DRAW);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

		//Create VAOs.
		MeshVariantMap variantMap;

		gl::BindBuffer(gl::ARRAY_BUFFER, buffers[0]);

		std::vector<int> components;
		components.push_back(VAR_NORMAL);
		if(!colorSequence.empty())
			components.push_back(VAR_COLOR);

		BuildVariations(variantMap, components, fmt, buffers[1]);

		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		//////////////////////////////////////////////////////////////////////////
		//Create rendering commands.
		RenderCmdList renderCmds;

		renderCmds.DrawElements(gl::TRIANGLES, indices.size(), gl::UNSIGNED_INT, 0);

		GLuint mainVao = colorSequence.empty() ? variantMap["lit"] : variantMap["lit-color"];

		Mesh *pRet = new Mesh(buffers, mainVao, renderCmds, variantMap);
		return pRet;
	}

	Mesh * CubePyramid( int numCubesTall, const ColorArray &colorSequence )
	{
		numCubesTall = std::max(numCubesTall, 1);
		numCubesTall = std::min(numCubesTall, 16383); //Because we're using shorts.

		//////////////////////////////////////////////////////////////////////////
		//Generate vertex data
		glmesh::AttributeList attribs;
		attribs.push_back(glmesh::AttribDesc(ATTR_POS, 3, glmesh::VDT_SIGN_SHORT, glmesh::ADT_FLOAT));
		attribs.push_back(glmesh::AttribDesc(ATTR_NORMAL, 4, glmesh::VDT_SIGN_BYTE, glmesh::ADT_NORM_FLOAT));
		if(!colorSequence.empty())
			attribs.push_back(glmesh::AttribDesc(ATTR_COLOR, 4, glmesh::VDT_UNSIGN_BYTE, glmesh::ADT_NORM_FLOAT));
		VertexFormat fmt(attribs);

		CpuDataWriter writer(fmt);
		GLshort height = 2 * numCubesTall - 1;

		for(int layer = 0; layer < numCubesTall; ++layer, height -= 2)
		{
			WriteCubeLayer(writer, layer + 1, height, colorSequence);
		}

		const size_t numCubesTotal = writer.GetNumVerticesWritten() / 24;

		//////////////////////////////////////////////////////////////////////////
		//Generate index data.
		std::vector<GLuint> indices;
		indices.reserve(numCubesTotal * 36); //Drawn as triangles.

		for(size_t cube = 0; cube < (numCubesTotal * 6); ++cube)
		{
			indices.push_back((cube * 4) + 0);
			indices.push_back((cube * 4) + 1);
			indices.push_back((cube * 4) + 2);

			indices.push_back((cube * 4) + 2);
			indices.push_back((cube * 4) + 1);
			indices.push_back((cube * 4) + 3);
		}

		//////////////////////////////////////////////////////////////////////////
		//Build the buffers.
		std::vector<GLuint> buffers(2);
		gl::GenBuffers(2, &buffers[0]);
		writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW, buffers[0]);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
			&indices[0], gl::STATIC_DRAW);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

		//Create VAOs.
		MeshVariantMap variantMap;

		gl::BindBuffer(gl::ARRAY_BUFFER, buffers[0]);

		std::vector<int> components;
		components.push_back(VAR_NORMAL);
		if(!colorSequence.empty())
			components.push_back(VAR_COLOR);

		BuildVariations(variantMap, components, fmt, buffers[1]);

		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		//////////////////////////////////////////////////////////////////////////
		//Create rendering commands.
		RenderCmdList renderCmds;

		renderCmds.DrawElements(gl::TRIANGLES, indices.size(), gl::UNSIGNED_INT, 0);

		GLuint mainVao = colorSequence.empty() ? variantMap["lit"] : variantMap["lit-color"];

		Mesh *pRet = new Mesh(buffers, mainVao, renderCmds, variantMap);
		return pRet;
	}
}
}
