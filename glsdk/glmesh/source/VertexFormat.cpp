//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <set>
#include <sstream>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glmesh/VertexFormat.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glmesh
{
	namespace
	{
		size_t g_byteSizesVertexTypes[] =
		{
			2,
			4,
			8,

			1,
			1,
			2,
			2,
			4,
			4,
		};

		static_assert(NUM_VERTEX_DATA_TYPES == ARRAY_COUNT(g_byteSizesVertexTypes), "");
	}

	AttributeDataInvalidException::AttributeDataInvalidException( int numComponentsGiven )
	{
		std::ostringstream temp;
		temp << "The number of components for AttribDesc must be on the range [1, 4]\n"
			"You provided " << numComponentsGiven << "." << std::endl;
		message = temp.str();
	}

	AttributeIndexMultipleRefException::AttributeIndexMultipleRefException( unsigned int attribIndex )
	{
		std::ostringstream temp;
		temp << "The attribute index " << attribIndex << " was referenced multiple times in your attribute list."
			<< std::endl;
		message = temp.str();
	}

	AttributeDataUnsupportedException::AttributeDataUnsupportedException(
		unsigned int requestedAttrib, GLint maxAttribs )
	{
		std::ostringstream temp;
		temp << "The maximum number of attributes in this implementation is " << maxAttribs << "\n"
			"You asked for index " << requestedAttrib << ", which is too large." << std::endl;
		message = temp.str();
	}

	AttribDesc::AttribDesc( unsigned int attribIndex, unsigned int numComponents,
		VertexDataType vertType, AttribDataType attribType )
		: m_attribIndex(attribIndex)
		, m_numComponents(numComponents)
		, m_vertType(vertType)
		, m_attribType(attribType)
	{
		if(!((1 <= m_numComponents) && (m_numComponents <= 4)))
			throw AttributeDataInvalidException(m_numComponents);

		static GLint maxAttribs = 0;
		if(maxAttribs == 0)
			gl::GetIntegerv(gl::MAX_VERTEX_ATTRIBS, &maxAttribs);

		if(m_attribIndex >= (GLuint)maxAttribs)
			throw AttributeDataUnsupportedException(m_attribIndex, maxAttribs);

		//Check for half-float support.
		if(m_vertType == VDT_HALF_FLOAT)
		{
			if(!glload::IsVersionGEQ(3, 0) && !gl::exts::var_ARB_half_float_vertex)
			{
				throw AttributeDataUnsupportedException(
					"half-float attributes are not supported on this OpenGL implementation.");
			}
		}

		switch(m_attribType)
		{
		case ADT_FLOAT:
			break;
		case ADT_NORM_FLOAT:
			if(m_vertType == VDT_HALF_FLOAT || m_vertType == VDT_SINGLE_FLOAT || m_vertType == VDT_DOUBLE_FLOAT)
				throw AttributeDataInvalidException("Normalized ADTs cannot be used with float types.");
			break;
		case ADT_INTEGER:
			if(m_vertType == VDT_HALF_FLOAT || m_vertType == VDT_SINGLE_FLOAT || m_vertType == VDT_DOUBLE_FLOAT)
				throw AttributeDataInvalidException("Integer ADTs cannot be used with floats");

			//Check for integer support.
			if(!glload::IsVersionGEQ(3, 0) && !gl::exts::var_EXT_gpu_shader4)
			{
				throw AttributeDataUnsupportedException(
					"Integer attributes are not supported on this OpenGL implementation.");
			}
			break;
		case ADT_DOUBLE:
			if(m_vertType != VDT_DOUBLE_FLOAT)
				throw AttributeDataInvalidException("Only VDT_DOUBLE_FLOAT can be paired with ADT_DOUBLE.");

			//Check for double-precision support.
			if(!glload::IsVersionGEQ(4, 1) && !gl::exts::var_ARB_vertex_attrib_64bit)
			{
				throw AttributeDataUnsupportedException(
					"Double attributes are not supported on this OpenGL implementation.");
			}
			break;
		}
	}

	size_t AttribDesc::ByteSize() const
	{
		return g_byteSizesVertexTypes[m_vertType] * m_numComponents;
	}

	VertexFormat::VertexFormat()
		: m_vertexSize(0)
	{}

	VertexFormat::VertexFormat( const AttributeList &attribs )
		: m_attribs(attribs)
	{
		m_attribOffsets.reserve(m_attribs.size());

		std::set<unsigned int> foundIndices;

		AttributeList::const_iterator currIt = m_attribs.begin();
		const AttributeList::const_iterator endIt = m_attribs.end();

		size_t currOffset = 0;
		for(; currIt != endIt; ++currIt)
		{
			const AttribDesc &currAttrib = *currIt;

			//Round currOffset up to the nearest 8 bytes if a double.
			if(currAttrib.GetVertexDataType() == VDT_DOUBLE_FLOAT)
				currOffset = ((currOffset + 7) / 8) * 8;

			m_attribOffsets.push_back(currOffset);
			currOffset += currAttrib.ByteSize();

			//Round currOffset up to the nearest 4 bytes.
			currOffset = ((currOffset + 3) / 4) * 4;

			if(foundIndices.find(currAttrib.GetAttribIndex()) != foundIndices.end())
				throw AttributeIndexMultipleRefException(currAttrib.GetAttribIndex());

			foundIndices.insert(currAttrib.GetAttribIndex());
		}

		m_vertexSize = currOffset;
	}

	glmesh::AttribDesc VertexFormat::GetAttribDesc( size_t attribIx ) const
	{
		return m_attribs.at(attribIx);
	}

	size_t VertexFormat::GetAttribByteOffset( size_t attribIx ) const
	{
		return m_attribOffsets.at(attribIx);
	}

	namespace
	{
		GLenum t_vertexUploadType[] =
		{
			gl::HALF_FLOAT,
			gl::FLOAT,
			gl::DOUBLE,

			gl::BYTE,
			gl::UNSIGNED_BYTE,
			gl::SHORT,
			gl::UNSIGNED_SHORT,
			gl::INT,
			gl::UNSIGNED_INT,
		};

		static_assert(NUM_VERTEX_DATA_TYPES == ARRAY_COUNT(t_vertexUploadType), "");
	}

	void VertexFormat::BindAttributes( size_t baseOffset ) const
	{
		const size_t numAttribs = GetNumAttribs();
		for(size_t attribIx = 0; attribIx < numAttribs; ++attribIx)
		{
			BindAttribute(baseOffset, attribIx);
		}
	}

	void VertexFormat::BindAttribute( size_t baseOffset, size_t attribIx ) const
	{
		const AttribDesc &attribute = GetAttribDesc(attribIx);
		size_t offset = GetAttribByteOffset(attribIx);
		const GLuint attributeIndex = attribute.GetAttribIndex();

		gl::EnableVertexAttribArray(attributeIndex);
		GLenum type = t_vertexUploadType[attribute.GetVertexDataType()];
		GLint numComponents = static_cast<GLint>(attribute.GetNumComponents());
		switch(attribute.GetAttribDataType())
		{
		case ADT_FLOAT:
			gl::VertexAttribPointer(attributeIndex, numComponents, type, gl::FALSE_,
				GetVertexByteSize(), reinterpret_cast<void*>(baseOffset + offset));
			break;
		case ADT_NORM_FLOAT:
			gl::VertexAttribPointer(attributeIndex, numComponents, type, gl::TRUE_,
				GetVertexByteSize(), reinterpret_cast<void*>(baseOffset + offset));
			break;
		case ADT_INTEGER:
			gl::VertexAttribIPointer(attributeIndex, numComponents, type,
				GetVertexByteSize(), reinterpret_cast<void*>(baseOffset + offset));
			break;
		case ADT_DOUBLE:
			gl::VertexAttribLPointer(attributeIndex, numComponents, type,
				GetVertexByteSize(), reinterpret_cast<void*>(baseOffset + offset));
			break;
		}
	}

	void VertexFormat::BindAttribFormats(GLuint bindingIndex) const
	{
		const size_t numAttribs = GetNumAttribs();
		for(size_t attribIx = 0; attribIx < numAttribs; ++attribIx)
		{
			BindAttribFormat(attribIx, bindingIndex);
		}
	}

	void VertexFormat::BindAttribFormat( size_t attribIx, GLuint bindingIndex) const
	{
		const AttribDesc &attribute = GetAttribDesc(attribIx);
		size_t offset = GetAttribByteOffset(attribIx);
		const GLuint attributeIndex = attribute.GetAttribIndex();

		gl::EnableVertexAttribArray(attributeIndex);
		gl::VertexAttribBinding(attributeIndex, bindingIndex);
		GLenum type = t_vertexUploadType[attribute.GetVertexDataType()];
		GLint numComponents = static_cast<GLint>(attribute.GetNumComponents());

		switch(attribute.GetAttribDataType())
		{
		case ADT_FLOAT:
			gl::VertexAttribFormat(attributeIndex, numComponents, type, gl::FALSE_, offset);
			break;
		case ADT_NORM_FLOAT:
			gl::VertexAttribFormat(attributeIndex, numComponents, type, gl::TRUE_, offset);
			break;
		case ADT_INTEGER:
			gl::VertexAttribIFormat(attributeIndex, numComponents, type, offset);
			break;
		case ADT_DOUBLE:
			gl::VertexAttribLFormat(attributeIndex, numComponents, type, offset);
			break;
		}
	}

	void VertexFormat::DisableAttributes() const
	{
		for(const AttribDesc &attribute: m_attribs)
		{
			gl::DisableVertexAttribArray(attribute.GetAttribIndex());
		}
	}

	VertexFormat::Enable::Enable( const VertexFormat &fmt, size_t baseOffset )
		: m_fmt(fmt)
	{
		m_fmt.BindAttributes(baseOffset);
	}

	VertexFormat::Enable::Enable( const VertexFormat &fmt, GLuint bindingIndex, SeparateAttribFormatTag )
		: m_fmt(fmt)
	{
		m_fmt.BindAttribFormats(bindingIndex);
	}

	VertexFormat::Enable::~Enable()
	{
		m_fmt.DisableAttributes();
	}
}
