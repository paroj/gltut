//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <algorithm>
#include <set>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glmesh/Mesh.h"


namespace glmesh
{
	namespace
	{
		struct RenderCmd
		{
			bool isIndexedCmd;
			GLenum ePrimType;
			GLsizei vertexCount;

			//Only valid if isIndexedCmd is false.
			GLint startIndex;		

			//Only valid if isIndexedCmd is true.
			GLenum dataType;
			GLintptr byteOffset;
			GLint baseVertex;
			bool hasPrimRestart;
			int primRestart;
		};
	}

	struct RenderCmdListData
	{
		RenderCmdListData() : hasRestartIndex(false) {}

		bool hasRestartIndex;
		GLint restartIndex;

		std::vector<RenderCmd> cmds;
	};

	struct MeshData
	{
		MeshData(const std::vector<GLuint> &_bufferObjects, GLuint _mainVao,
			const std::vector<RenderCmd> &_cmds, const MeshVariantMap &_variants)
			: bufferObjects(_bufferObjects)
			, mainVao(_mainVao)
			, variants(_variants)
			, cmds(_cmds)
		{}

		~MeshData()
		{
			std::set<GLuint> deletedVaos;

			if(mainVao)
			{
				deletedVaos.insert(mainVao);
				gl::DeleteVertexArrays(1, &mainVao);
			}

			for(MeshVariantMap::iterator currIt = variants.begin();
				currIt != variants.end();
				++currIt)
			{
				if(currIt->second && (deletedVaos.find(currIt->second) != deletedVaos.end()))
				{
					deletedVaos.insert(currIt->second);
					gl::DeleteVertexArrays(1, &currIt->second);
				}
			}

			gl::DeleteBuffers(bufferObjects.size(), &bufferObjects[0]);
		}

		std::vector<GLuint> bufferObjects;
		GLuint mainVao;
		MeshVariantMap variants;

		std::vector<RenderCmd> cmds;
	};

	RenderCmdList::RenderCmdList()
		: m_pData(new RenderCmdListData)
	{}

	RenderCmdList::RenderCmdList( class RenderCmdList &anOther )
		: m_pData(new RenderCmdListData(*anOther.m_pData))
	{}

	RenderCmdList::~RenderCmdList()
	{}

	RenderCmdList& RenderCmdList::operator=( class RenderCmdList &anOther )
	{
		*m_pData = *anOther.m_pData;
		return *this;
	}

	void RenderCmdList::DrawArrays( GLenum primitive, GLint startIndex, GLsizei vertexCount )
	{
		RenderCmd cmd;

		cmd.isIndexedCmd = false;
		cmd.ePrimType = primitive;
		cmd.vertexCount = vertexCount;
		cmd.startIndex = startIndex;

		m_pData->cmds.push_back(cmd);
	}

	void RenderCmdList::DrawElements( GLenum primitive, GLsizei vertexCount, GLenum dataType,
		GLintptr byteOffset, GLint baseVertex )
	{
		RenderCmd cmd;

		cmd.isIndexedCmd = true;
		cmd.ePrimType = primitive;
		cmd.vertexCount = vertexCount;
		cmd.dataType = dataType;
		cmd.byteOffset = byteOffset;
		cmd.baseVertex = baseVertex;
		cmd.hasPrimRestart = m_pData->hasRestartIndex;
		cmd.primRestart = m_pData->restartIndex;

		m_pData->cmds.push_back(cmd);
	}

	void RenderCmdList::PrimitiveRestartIndex()
	{
		m_pData->hasRestartIndex = false;
	}

	void RenderCmdList::PrimitiveRestartIndex( GLuint index )
	{
		m_pData->hasRestartIndex = true;
		m_pData->restartIndex = index;
	}

	Mesh::Mesh( const std::vector<GLuint> &bufferObjects, GLuint mainVao,
		const RenderCmdList &renderCmds, const MeshVariantMap &variants )
		: m_pData(new MeshData(bufferObjects, mainVao, renderCmds.m_pData->cmds, variants))
	{}

	Mesh::~Mesh()
	{}

	void Mesh::Render() const
	{
		if(m_pData->mainVao)
		{
			gl::BindVertexArray(m_pData->mainVao);
			RenderWithCurrVao();
			gl::BindVertexArray(0);
		}
	}

	void Mesh::Render( const std::string &variantName ) const
	{
		MeshVariantMap::iterator currVariant = m_pData->variants.find(variantName);
		if(currVariant == m_pData->variants.end() || (currVariant->second == 0))
			return;

		gl::BindVertexArray(currVariant->second);
		RenderWithCurrVao();
		gl::BindVertexArray(0);
	}

	void Mesh::RenderWithCurrVao() const
	{
		for(size_t loop = 0; loop < m_pData->cmds.size(); ++loop)
		{
			const RenderCmd &cmd = m_pData->cmds[loop];
			if(cmd.isIndexedCmd)
			{
				if(cmd.hasPrimRestart)
				{
					gl::Enable(gl::PRIMITIVE_RESTART);
					gl::PrimitiveRestartIndex(cmd.primRestart);
				}
				else
					gl::Disable(gl::PRIMITIVE_RESTART);

				if(cmd.baseVertex)
					gl::DrawElementsBaseVertex(cmd.ePrimType, cmd.vertexCount, cmd.dataType,
					reinterpret_cast<void*>(cmd.byteOffset), cmd.baseVertex);
				else
					gl::DrawElements(cmd.ePrimType, cmd.vertexCount, cmd.dataType,
					reinterpret_cast<void*>(cmd.byteOffset));
			}
			else
			{
				gl::Disable(gl::PRIMITIVE_RESTART);
				gl::DrawArrays(cmd.ePrimType, cmd.startIndex, cmd.vertexCount);
			}
		}

		gl::Disable(gl::PRIMITIVE_RESTART);
	}

	bool Mesh::DoesMainExist() const
	{
		if(m_pData->mainVao)
			return true;

		return false;
	}

	bool Mesh::DoesVariantExist( const std::string &variantName ) const
	{
		MeshVariantMap::iterator currVariant = m_pData->variants.find(variantName);
		if(currVariant == m_pData->variants.end() || (currVariant->second == 0))
			return false;

		return true;
	}
}