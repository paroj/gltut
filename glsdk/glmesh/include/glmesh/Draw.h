/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_DRAW_H
#define GLSDK_MESH_DRAW_H

/**
\file
\brief Declares the Draw class and its helper types. Include an OpenGL header before including this one.
**/

#include <vector>
#include <string>
#include <exception>
#include <glm/glm.hpp>
#include "VertexFormat.h"
#include "StreamBuffer.h"
#include "VertexWriter.h"

namespace glmesh
{
	///\addtogroup module_glmesh_exceptions
	///@{

	///Base class for all Draw specific exceptions.
	class DrawException : public std::exception
	{
	public:
		virtual ~DrawException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	///Thrown when drawing with Draw and you did not provide as many vertices as promised.
	class TooFewVerticesSentException : public DrawException
	{
	public:
		TooFewVerticesSentException(int numProvided, size_t numStated);
	};

	///Thrown when calling Attrib and you are writing more vertices than you promised.
	class TooManyVerticesSentException : public DrawException
	{
	public:
		TooManyVerticesSentException()
		{
			message = "You provided more attribute data than you said you would.";
		}
	};

	///Thrown when creating a Draw with a primitive type that the current OpenGL implementation does not support.
	class PrimitiveTypeUnsupportedException : public DrawException
	{
	public:
		PrimitiveTypeUnsupportedException(const std::string &primTypename)
		{
			message = "The primitive type \"" + primTypename + "\" is not supported by OpenGL.";
		}
	};

	///Thrown when the primitive type and vertex count cannot be used together.
	class VertexCountPrimMismatchException : public DrawException
	{
	public:
		VertexCountPrimMismatchException(const std::string &primName, const std::string &primReqs,
			size_t vertexCount);
	};

	///@}

	///\addtogroup module_glmesh_draw
	///@{

	/**
	\brief RAII-style class for immediate-mode type rendering through a VertexFormat and StreamBuffer.

	The constructor of this class is given an OpenGL primitive type and the number of vertices to use.
	You must then call one of the Attrib member functions for each vertex and for each attribute
	in the VertexFormat. The order of attributes within a vertex corresponds to the order of
	attributes in the VertexFormat.

	The VertexWriter::Attrib specialization must match the type of the attribute from the VertexFormat
	\em exactly. The number of components however does not have to match.

	Successfully constructing an object of this type will affect the following OpenGL state (note: none
	of this state will be touched in the event of an exception in the constructor):

	- The current `GL_ARRAY_BUFFER` binding.
	- If VAOs are available, the current VAO will be affected. The current VAO after this object is
	destroyed will be VAO 0. The VAO used to render will be the communal one stored in the StreamBuffer.
	- If VAOs are not available, the current attribute array state will be modified as
	VertexFormat::Enable does. Note that you should make sure that all attributes are disabled
	*before* constructing this object. Otherwise, badness can result.

	\note Do \em not attempt to change buffer binding state during the lifetime of any instance of
	this class. Also, do not attempt to create two of these objects at the same time.

	The VertexWriter::Attrib functions, used to write attributes, will also throw
	TooManyVerticesSentException if more vertices have been sent than were originally specified.

	\note This class cannot be copied.
	**/
	class Draw : public VertexWriter<Draw>
	{
	public:
		/**
		\brief Creates a non-copyable object for drawing.

		\param primType The OpenGL primitive type to render.
		\param vertexCount The number of vertices you will provide. This must work with \a primType
		or an exception is thrown.
		\param fmt The format of the attributes in each vertex. Taken by reference; do not destroy
		this before this object is destroyed.
		\param buffer The streaming buffer that will be used to store the vertex data. Taken by
		reference; do not destroy this before this object is destroyed.

		\throw PrimitiveTypeUnsupportedException If \a primType is not supported on the OpenGL implementation.
		\throw VertexCountPrimMismatchException If \a vertexCount does not match \a primType's requirements.
		\throw StreamBuffer::Map Anything that this class throws, except for NotEnoughRemainingStorageForMapException.

		In the event of any exceptions, nothing is mapped and the StreamBuffer is not touched.
		**/
		Draw(GLenum primType, size_t vertexCount, const VertexFormat &fmt, StreamBuffer &buffer);

		/**
		\brief Draws, if the object has not been drawn previously with a call to Render().
		
		Unlike Render, this does not throw exceptions, since throwing exceptions in a destructor is bad.
		By letting this fall off the stack without an explicit render, you are effectively saying
		that you don't care to error check.

		Therefore, if not enough vertices have been provided, then nothing will be rendered.
		**/
		~Draw();

		/**
		\brief Draws the vertex data provided, if the object has not previously been drawn.

		You can only call this after calling the Attrib functions enough times to provide a full set
		of attribute data for all vertices, as specified by \a vertexCount in the constructor.

		\return true if the vertex data was rendered. False if Render has already been called or if the
		unmapping of the buffer failed. In both cases, nothing is rendered.

		\throw TooFewVerticesSentException If you have not provided all of the vertices promised by the vertex count.
		**/
		bool Render();

	private:
		GLenum m_primType;
		size_t m_vertexCount;
		const VertexFormat &m_fmt;
		StreamBuffer::Map m_map;
		StreamBuffer &m_buffer;

		const size_t m_bufferOffset;
		int m_verticesRemaining;
		std::vector<GLubyte> m_tempBuffer;
		

		//No copying.
		Draw(const Draw &);
		Draw& operator=(const Draw&);

		void WriteAttribute( const void *pData, size_t bytesPerComponent, size_t currAttrib );
		void *GetPtrForAttrib(size_t currAttrib);
		void *GetOutputPtrForVertex();

		template<typename BaseType>
		void VerifyType();

		int InternalRender();

		friend class VertexWriter<Draw>;
		const VertexFormat &GetVertexFormat() const {return m_fmt;}
	};

	///@}
}
#endif //GLSDK_MESH_DRAW_H
