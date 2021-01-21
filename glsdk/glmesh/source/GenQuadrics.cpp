//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include <algorithm>
#include <cmath>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>

//#include "glmesh/BoostDraw.h"
#include "glmesh/CpuDataWriter.h"
#include "glmesh/VertexFormat.h"

#include "glmesh/Mesh.h"
#include "glmesh/GenQuadrics.h"
#include "GenHelper.h"
#include <glm/glm.hpp>

namespace glmesh
{
	namespace gen
	{
		namespace
		{
			const float g_pi = 3.1415726f;
			const float g_2pi = g_pi * 2.0f;
		}

		Mesh * UnitSphere( int numHorizSlices, int numVertSlices )
		{
			//The term "ring" refers to horizontal slices.
			//The term "segment" refers to vertical slices.

			//////////////////////////////////////////////////////////////////////////
			// Generate the vertex attribute data.
			numHorizSlices = std::max(numHorizSlices, 1);
			numVertSlices = std::max(numVertSlices, 3);

			//+2 to horizontal is for the top and bottom points, which are replicated due to texcoords.
			size_t numRingVerts = numHorizSlices + 2;
			//+1 to vertical is for doubling up on the initial point, again due to texcoords.
			size_t numSegVerts = numVertSlices + 1;
			size_t attribCount = numSegVerts * numRingVerts;

			glmesh::AttributeList attribs;
			attribs.push_back(glmesh::AttribDesc(ATTR_POS, 3, glmesh::VDT_SINGLE_FLOAT, glmesh::ADT_FLOAT));
			attribs.push_back(glmesh::AttribDesc(ATTR_NORMAL, 3, glmesh::VDT_SINGLE_FLOAT, glmesh::ADT_FLOAT));
			attribs.push_back(glmesh::AttribDesc(ATTR_TEXCOORD, 2, glmesh::VDT_SINGLE_FLOAT, glmesh::ADT_FLOAT));

			VertexFormat fmt(attribs);

			CpuDataWriter writer(fmt, attribCount);

			float deltaSegTexCoord = 1.0f / numSegVerts;
			float deltaRingTexCoord = 1.0f / numRingVerts;

			for(int segment = 0; segment < numVertSlices; ++segment)
			{
				writer.Attrib(0.0f, 1.0f, 0.0f);
				writer.Attrib(0.0f, 1.0f, 0.0f);
				writer.Attrib(deltaSegTexCoord * segment, 1.0f);
			}

			writer.Attrib(0.0f, 1.0f, 0.0f);
			writer.Attrib(0.0f, 1.0f, 0.0f);
			writer.Attrib(1.0f, 0.0f);

			float radThetaDelta = g_pi / (numHorizSlices + 1);
			float radRhoDelta = g_2pi / numVertSlices;

			for(int ring = 0; ring < numHorizSlices; ++ring)
			{
				float radTheta = radThetaDelta * (ring + 1);
				float sinTheta = std::sin(radTheta);
				float cosTheta = std::cos(radTheta);

				float ringTexCoord = 1.0f - ((ring + 1) * deltaRingTexCoord);

				for(int segment = 0; segment < numVertSlices; ++segment)
				{
					float radRho = radRhoDelta * segment;
					float sinRho = std::sin(-radRho);
					float cosRho = std::cos(-radRho);

					glm::vec3 currPos(sinTheta * cosRho, cosTheta, sinTheta * sinRho);
					writer.Attrib(currPos);
					writer.Attrib(currPos);
					writer.Attrib(deltaSegTexCoord * segment, ringTexCoord);
				}

				writer.Attrib(sinTheta, cosTheta, 0.0f);
				writer.Attrib(sinTheta, cosTheta, 0.0f);
				writer.Attrib(1.0f, ringTexCoord);
			}

			for(int segment = 0; segment < numVertSlices; ++segment)
			{
				writer.Attrib(0.0f, -1.0f, 0.0f);
				writer.Attrib(0.0f, -1.0f, 0.0f);
				writer.Attrib(deltaSegTexCoord * segment, 0.0f);
			}

			writer.Attrib(0.0f, 1.0f, 0.0f);
			writer.Attrib(0.0f, 1.0f, 0.0f);
			writer.Attrib(1.0f, 0.0f);

			//////////////////////////////////////////////////////////////////////////
			//Generate the index data.
			//Restart index.
			GLuint restartIndex = writer.GetNumVerticesWritten();

			size_t stripSize = ((2 * numVertSlices) + 2);
			//One strip for each ring vertex list, minus 1.
			size_t numStrips = (numRingVerts - 1);

			size_t numIndices = numStrips * stripSize;
			//Add one index between each strip for primitive restarting.
			numIndices += (numStrips - 1);

			std::vector<GLuint> indices;
			indices.reserve(numIndices);

			for(size_t strip = 0; strip < numStrips; ++strip)
			{
				GLuint topRingIndex = (strip * numSegVerts);
				GLuint botRingIndex = ((strip + 1) * numSegVerts);

				for(size_t segment = 0; segment < numSegVerts; ++segment)
				{
					indices.push_back(topRingIndex + segment);
					indices.push_back(botRingIndex + segment);
				}

				if(indices.size() != numIndices)
					indices.push_back(restartIndex);
			}

			//////////////////////////////////////////////////////////////////////////
			//Build the buffers.
			std::vector<GLuint> buffers(2);

			gl::GenBuffers(2, &buffers[0]);
			writer.TransferToBuffer(gl::ARRAY_BUFFER, gl::STATIC_DRAW, buffers[0]);

			//vertex data done. Now build the index buffer.
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
			gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
				&indices[0], gl::STATIC_DRAW);
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

			//Create VAOs.
			MeshVariantMap variantMap;

			gl::BindBuffer(gl::ARRAY_BUFFER, buffers[0]);

			GLuint currVao = 0;

			gl::GenVertexArrays(1, &currVao);
			gl::BindVertexArray(currVao);
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
			fmt.BindAttribute(0, 0);
			AddVariantToMap(variantMap, currVao, 0);

			gl::GenVertexArrays(1, &currVao);
			gl::BindVertexArray(currVao);
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
			fmt.BindAttribute(0, 0);
			fmt.BindAttribute(0, 1);
			AddVariantToMap(variantMap, currVao, VAR_NORMAL);

			gl::GenVertexArrays(1, &currVao);
			gl::BindVertexArray(currVao);
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
			fmt.BindAttribute(0, 0);
			fmt.BindAttribute(0, 2);
			AddVariantToMap(variantMap, currVao, VAR_TEX_COORD);

			gl::GenVertexArrays(1, &currVao);
			gl::BindVertexArray(currVao);
			gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffers[1]);
			fmt.BindAttribute(0, 0);
			fmt.BindAttribute(0, 1);
			fmt.BindAttribute(0, 2);
			AddVariantToMap(variantMap, currVao, VAR_TEX_COORD | VAR_NORMAL);

			gl::BindVertexArray(0);
			gl::BindBuffer(gl::ARRAY_BUFFER, 0);

			//////////////////////////////////////////////////////////////////////////
			//Create rendering commands.
			RenderCmdList renderCmds;
			if(glload::IsVersionGEQ(3, 1))
			{
				//Has primitive restart. Therefore, can draw two fans as one.
				renderCmds.PrimitiveRestartIndex(restartIndex);
				renderCmds.DrawElements(gl::TRIANGLE_STRIP, numIndices, gl::UNSIGNED_INT, 0);
				renderCmds.PrimitiveRestartIndex();
			}
			else
			{
				//No restart. Must draw each strip one after the other.
				for(size_t strip = 0; strip < numStrips; ++strip)
				{
					GLuint stripStart = strip * (stripSize + 1);

					renderCmds.DrawElements(gl::TRIANGLE_STRIP, stripSize, gl::UNSIGNED_INT,
						stripStart * sizeof(GLuint));
				}
			}

			GLuint mainVao = variantMap["lit-tex"];

			Mesh *pRet = new Mesh(buffers, mainVao, renderCmds, variantMap);
			return pRet;
		}
	}
}

