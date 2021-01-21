/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_CPU_DATA_WRITER_H
#define GLSDK_MESH_CPU_DATA_WRITER_H

/**
\file
\brief Declares the VertexWriter class and its helper types. Include an OpenGL header before including this one.
**/

#include <vector>
#include "VertexWriter.h"

namespace glmesh
{
	///\addtogroup module_glmesh_exceptions
	///@{

	///Base class for all CpuDataWriter specific exceptions.
	class CpuDataException : public std::exception
	{
	public:
		virtual ~CpuDataException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	///Thrown when attempting to get vertices from a CpuDataWriter when a vertex is incomplete.
	class IncompleteVertexException : public CpuDataException
	{
	public:
		IncompleteVertexException()
		{
			message = "All vertices must be complete before attempting to extract them from CpuDataWriter.";
		}
	};

	///@}

	///\addtogroup module_glmesh_draw
	///@{

	/**
	\brief Allows immediate mode drawing to a CPU buffer, rather than a buffer object.

	It is frequently useful to do immediate-mode style drawing to a CPU buffer. One might be doing
	old-style client-side array rendering, or just compiling lots of data to eventually be
	uploaded to actual buffer objects.

	This class does this. It stores the attribute data into a `std::vector<char>`, in accord with the
	given VertexFormat.

	Unlike glmesh::Draw, this class does not require you to provide a maximum upper limit on the number
	of vertices ahead of time. And because this class does not do any rendering,
	it also does not require you to provide a primitive type. So you can write as many vertices as you want.
	It will still throw if you attempt to extract the vertex data when a vertex is only partially specified,
	but otherwise, there are no limitations.

	You can extract the data by copying it into a `vector<char>`, by "moving" it into one, or by
	directly uploading it to a buffer object.
	**/
	class CpuDataWriter : public VertexWriter<CpuDataWriter>
	{
	public:
		/**
		\brief Creates a data writer with the given format.

		\param fmt The VertexFormat to use with this writer.
		\param vertexReserve If specified, the number of vertices to reserve space for. Solely an optimization.
		**/
		CpuDataWriter(const VertexFormat &fmt, size_t vertexReserve = 0);

		/**
		\name Data Extraction Functions

		These functions all pull written data out of the writer. If you call one of these
		in the middle of a vertex, then the function will throw.
		**/
		///@{
		/**
		\brief Delivers vertex data by "move".

		This function swaps the internal buffer into the \a output argument. This method causes no
		copying of the data. Once you call this, you could continue writing more attributes,
		but all prior attributes will have been removed.

		\throw IncompleteVertexException If a vertex has only been partially specified.
		**/
		void Extract(std::vector<char> &output);

		/**
		\brief Copies the buffer to the return value. Does not modify the internal data.

		\throw IncompleteVertexException If a vertex has only been partially specified.
		**/
		std::vector<char> Copy() const;

		/**
		\brief Uploads the data directly to an OpenGL buffer object.

		This function uploads the data to a buffer object via a call to glBufferData.
		This can be a new buffer if you don't specify the third parameter, or it can be
		a user-created buffer object name. In either case, the old buffer's data will be
		completely destroyed.

		The buffer binding for \a target in the OpenGL context will be reset to 0 if this
		function call is successful. If it throws, nothing in the context will be changed.

		\param target The buffer object binding point you want to bind the buffer to.
		\param usage The storage usage you want to use for the call to glBufferData.
		\param bufferObject The buffer object name you want to upload into. If not specified, this will create a new one.
		\return The buffer object uploaded into.

		\throw IncompleteVertexException If a vertex has only been partially specified.
		**/
		GLuint TransferToBuffer(GLenum target, GLenum usage, GLuint bufferObject = 0) const;
		///@}

		/**
		\brief Returns the number of complete vertices written to the data.
		**/
		size_t GetNumVerticesWritten() const {return m_numVerticesWritten;}

	private:
		std::vector<char> m_tempBuffer;
		std::vector<char> m_data;
		const VertexFormat &m_fmt;
		size_t m_numVerticesWritten;

		void *GetPtrForAttrib(size_t currAttrib);

		friend class VertexWriter<CpuDataWriter>;
		const VertexFormat &GetVertexFormat() const {return m_fmt;}
		void WriteAttribute( const void *pData, size_t bytesPerComponent, size_t currAttrib );
	};

	///@}
}

#endif //GLSDK_MESH_CPU_DATA_WRITER_H
