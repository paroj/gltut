//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <sstream>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glmesh/StreamBuffer.h"

namespace glmesh
{
	namespace
	{
		bool HasVAO()
		{
			if(glload::IsVersionGEQ(3, 0) || gl::exts::var_ARB_vertex_array_object)
				return true;

			return false;
		}
	}

	NotEnoughStorageForMapException::NotEnoughStorageForMapException( size_t requestedSize, size_t bufferSize )
	{
		std::ostringstream temp;
		temp << "The StreamBuffer was asked to map " << requestedSize << " bytes, but it only "
			"contains " << bufferSize << " bytes." << std::endl;
		message = temp.str();
	}

	NotEnoughRemainingStorageForMapException::NotEnoughRemainingStorageForMapException( size_t pos,
		size_t requestedSize, size_t bufferSize )
	{
		std::ostringstream temp;
		temp << "The StreamBuffer, currently at offset " << pos << " was asked to map " <<
			requestedSize << " bytes, but there are only  " << bufferSize - pos << " bytes left." << std::endl;
		message = temp.str();
	}

	StreamBuffer::StreamBuffer( size_t bufferSize )
		: m_bufferObject(0)
		, m_bufferSize(bufferSize)
		, m_currOffset(0)
		, m_isMapped(false)
		, m_vao(0)
	{
		gl::GenBuffers(1, &m_bufferObject);
		gl::BindBuffer(gl::ARRAY_BUFFER, m_bufferObject);
		gl::BufferData(gl::ARRAY_BUFFER, bufferSize, NULL, gl::STREAM_DRAW);
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		if(HasVAO())
			gl::GenVertexArrays(1, &m_vao);
	}

	StreamBuffer::~StreamBuffer()
	{
		if(m_vao)
		{
			gl::DeleteVertexArrays(1, &m_vao);
			m_vao = 0;
		}

		gl::DeleteBuffers(1, &m_bufferObject);
		m_bufferObject = 0;
	}

	size_t StreamBuffer::GetSpaceRemaining() const
	{
		return m_bufferSize - m_currOffset;
	}

	void StreamBuffer::InvalidateBuffer()
	{
		if(m_isMapped)
			throw StoreAlreadyMappedException();

		gl::BindBuffer(gl::ARRAY_BUFFER, m_bufferObject);
		gl::BufferData(gl::ARRAY_BUFFER, m_bufferSize, NULL, gl::STREAM_DRAW);
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		m_currOffset = 0;
	}


	StreamBuffer::Map::Map( StreamBuffer &storage, size_t numBytes, bool invalidateIfNotAvailable )
		: m_pData(&storage)
		, m_pCurrPtr(NULL)
		, m_bytesMapped(numBytes)
	{
		if(m_pData->m_isMapped)
			throw StoreAlreadyMappedException();

		if(numBytes > m_pData->GetTotalBufferSize())
			throw NotEnoughStorageForMapException(m_bytesMapped, m_pData->GetTotalBufferSize());

		int bitfield = gl::MAP_WRITE_BIT | gl::MAP_UNSYNCHRONIZED_BIT;

		if(numBytes > m_pData->GetSpaceRemaining())
		{
			if(!invalidateIfNotAvailable)
			{
				throw NotEnoughRemainingStorageForMapException(m_pData->m_currOffset,
					m_bytesMapped, m_pData->GetTotalBufferSize());
			}

			bitfield |= gl::MAP_INVALIDATE_BUFFER_BIT;
			m_pData->m_currOffset = 0;
		}

		gl::BindBuffer(gl::ARRAY_BUFFER, m_pData->m_bufferObject);
		m_pCurrPtr = gl::MapBufferRange(gl::ARRAY_BUFFER, m_pData->m_currOffset,
			m_bytesMapped, bitfield);
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		m_pData->m_isMapped = true;
	}

	StreamBuffer::Map::~Map()
	{
		Release();
	}

	bool StreamBuffer::Map::Release()
	{
		if(!m_pData)
			return false;

		m_pData->m_isMapped = false;
		m_pData->m_currOffset += m_bytesMapped;

		bool ret = true;
		gl::BindBuffer(gl::ARRAY_BUFFER, m_pData->m_bufferObject);
		if(gl::UnmapBuffer(gl::ARRAY_BUFFER) == gl::FALSE_)
			ret = false;
		gl::BindBuffer(gl::ARRAY_BUFFER, 0);

		m_pData = NULL;
		m_pCurrPtr = NULL;

		return ret;
	}
}
