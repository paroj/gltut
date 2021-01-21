//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <string.h>
#include <glload/gl_all.hpp>
#include "glmesh/CpuDataWriter.h"

namespace glmesh
{
	CpuDataWriter::CpuDataWriter( const VertexFormat &fmt, size_t vertexReserve )
		: m_tempBuffer(fmt.GetVertexByteSize())
		, m_fmt(fmt)
		, m_numVerticesWritten(0)
	{
		if(vertexReserve)
			m_data.reserve(m_fmt.GetVertexByteSize() * vertexReserve);
	}

	void CpuDataWriter::Extract( std::vector<char> &output )
	{
		if(GetCurrAttrib() != 0)
			throw IncompleteVertexException();

		output.swap(m_data);
		m_data.clear();
		m_numVerticesWritten = 0;
	}

	std::vector<char> CpuDataWriter::Copy() const
	{
		if(GetCurrAttrib() != 0)
			throw IncompleteVertexException();

		return m_data;
	}

	GLuint CpuDataWriter::TransferToBuffer( GLenum target, GLenum usage, GLuint bufferObject /*= 0*/ ) const
	{
		if(GetCurrAttrib() != 0)
			throw IncompleteVertexException();

		if(!bufferObject)
			gl::GenBuffers(1, &bufferObject);

		gl::BindBuffer(target, bufferObject);
		gl::BufferData(target, m_data.size(), &m_data[0], usage);
		gl::BindBuffer(target, 0);
		return bufferObject;
	}

	void CpuDataWriter::WriteAttribute( const void *pData, size_t bytesPerComponent, size_t currAttrib )
	{
		size_t numComponents = m_fmt.GetAttribDesc(currAttrib).GetNumComponents();

		memcpy(GetPtrForAttrib(currAttrib), pData, bytesPerComponent * numComponents);

		if(currAttrib + 1 == m_fmt.GetNumAttribs())
		{
			m_data.insert(m_data.end(), m_tempBuffer.begin(), m_tempBuffer.end());
			++m_numVerticesWritten;
		}
	}

	void * CpuDataWriter::GetPtrForAttrib(size_t currAttrib)
	{
		size_t offset = m_fmt.GetAttribByteOffset(currAttrib);
		char *pData = (&m_tempBuffer[0]);
		return (pData + offset);
	}
}

