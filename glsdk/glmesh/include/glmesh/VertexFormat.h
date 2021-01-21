/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_VERTEX_FORMAT_H
#define GLSDK_MESH_VERTEX_FORMAT_H

/**
\file
\brief Declares the VertexFormat class and its helper types. Include an OpenGL header before including this one.
**/

#include <vector>
#include <string>
#include <exception>

namespace glmesh
{
	///\addtogroup module_glmesh_exceptions
	///@{

	///Base class for all exceptions thrown by AttribDesc, VertexFormat and VertexFormat::Enable.
	class VertexFormatException : public std::exception
	{
	public:
		virtual ~VertexFormatException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	///Thrown if the values passed to AttribDesc's constructor are not allowed.
	class AttributeDataInvalidException : public VertexFormatException
	{
	public:
		AttributeDataInvalidException(int numComponentsGiven);

		AttributeDataInvalidException(const std::string &msg)
		{
			message = msg;
		}
	};

	///Thrown if the values passed to AttribDesc's constructor do not meet the implementation-specific requirements.
	class AttributeDataUnsupportedException : public VertexFormatException
	{
	public:
		AttributeDataUnsupportedException(unsigned int requestedAttrib, GLint maxAttribs);

		AttributeDataUnsupportedException(const std::string &msg)
		{
			message = msg;
		}
	};

	///Thrown if VertexFormat is given two AttribDesc objects that use the same attribute index.
	class AttributeIndexMultipleRefException : public VertexFormatException
	{
	public:
		AttributeIndexMultipleRefException(unsigned int attribIndex);
	};


	///@}

	///\addtogroup module_glmesh_draw
	///@{

	/**
	\brief The C data type that you will be providing the vertex attribute data in.
	**/
	enum VertexDataType
	{
		VDT_HALF_FLOAT,		///<16-bit half-floats.
		VDT_SINGLE_FLOAT,	///<32-bit single-precision floats.
		VDT_DOUBLE_FLOAT,	///<64-bit double-precision floats.

		VDT_SIGN_BYTE,		///<8-bit signed integers.
		VDT_UNSIGN_BYTE,	///<8-bit unsigned integers.
		VDT_SIGN_SHORT,		///<16-bit signed integers.
		VDT_UNSIGN_SHORT,	///<16-bit unsigned integers.
		VDT_SIGN_INT,		///<32-bit signed integers.
		VDT_UNSIGN_INT,		///<32-bit unsigned integers.

		NUM_VERTEX_DATA_TYPES,
	};

	/**
	\brief The expected interpretation of the attribute data by GLSL.

	This type must match its corresponding glmesh::VertexDataType or an error will result.

	\li `ADT_FLOAT` can be used with anything.
	\li `ADT_NORM_FLOAT` can only be used with the integer types, signed or unsigned.
	\li `ADT_INTEGER` can only be used with the integer types, signed or unsigned.
	\li `ADT_DOUBLE` can only be used with `VDT_DOUBLE_FLOAT`.
	**/
	enum AttribDataType
	{
		ADT_FLOAT,			///<Values are used directly as floats. Integer types like 24 are converted to 24.0f floats.
		ADT_NORM_FLOAT,		///<Integer values are normalized. So 128 as an unsigned byte becomes 0.502.
		ADT_INTEGER,		///<Integer values are taken as integers.
		ADT_DOUBLE,			///<Values are used as double-precision. The shader must use \c double or \c dvec attributes.

		NUM_ATTRIB_DATA_TYPES,
	};


	/**
	\brief Describes the storage for a single vertex attribute.

	This object is used as part of the construction for a VertexFormat. It allows for "atomic"
	construction of VertexFormat objects, such that all attributes are added at once during
	construction.
	
	\note A valid OpenGL context must be active to create one of these objects.
	Do not make global variables of these.
	**/
	class AttribDesc
	{
	public:
		/**
		\brief Creates a valid AttribDesc

		\throw AttributeDataUnsupportedException If \a attribIndex is outside the [implementation-defined allowed range of OpenGL attributes](http://www.opengl.org/wiki/Vertex_Attribute).
		\throw AttributeDataInvalidException If \a vertType and \a attribType do not match, as defined in glmesh::AttribDataType.
		\throw AttributeDataInvalidException If \a numComponents is not on the range [1, 4].
		\throw AttributeDataUnsupportedException If \a attribType is `ADT_DOUBLE` and the implementation doesn't support double-precision attributes.
		\throw AttributeDataUnsupportedException If \a attribType is `ADT_INTEGER` and the implementation doesn't support integral attributes.
		\throw AttributeDataUnsupportedException If \a vertType is `VDT_HALF_FLOAT` and the implementation doesn't support half-floating point attributes.
		**/
		AttribDesc(unsigned int attribIndex, unsigned int numComponents,
			VertexDataType vertType, AttribDataType attribType);

		///Get the attribute index to be passed to glVertexAttribPointer for this attribute.
		unsigned int GetAttribIndex() const {return m_attribIndex;}

		///Get the number of components in the attribute's data.
		unsigned int GetNumComponents() const {return m_numComponents;}

		///Get the C/C++ type of the attribute data.
		VertexDataType GetVertexDataType() const {return m_vertType;}

		///Get the interpretation of that attribute's type.
		AttribDataType GetAttribDataType() const {return m_attribType;}

		///Computes the size in bytes of this attribute
		size_t ByteSize() const;

	private:
		unsigned int m_attribIndex;
		unsigned int m_numComponents;
		VertexDataType m_vertType;
		AttribDataType m_attribType;
	};

	///Convenience typedef for std::vector's of attributes.
	typedef std::vector<AttribDesc> AttributeList;

	///Used in VertexFormat::Enable to differentiate constructors.
	struct SeparateAttribFormatTag {};

	///Use this in VertexFormat::Enable to use the separate attribute format constructor.
	const SeparateAttribFormatTag sepFormat;

	/**
	\brief Describes the layout for a sequence of vertex attributes, to be used for rendering.

	VertexFormat creates an interleaved layout, where each attribute is interleaved with each
	other. The attributes always have 4 byte alignment, as there are some hardware that
	really doesn't like misaligned data. Double-precision attributes have 8-byte alignment.

	The byte offset of each attribute from the beginning of the vertex can be queried. This is
	useful if all of the attributes come from the same buffer object's source.

	Note that the order of the attribute sequence is the same as the order of the AttributeList.
	This means that the order is \em not the order of the OpenGL attribute location. The attribute
	sequence order, as defined by the AttributeList, is the order the attributes will be stored in
	within the buffer object.

	Any function that takes an \a attribIx parameter is taking an index into the attribute sequence
	order, *not* an OpenGL attribute location.

	You may use VertexFormat::Enable to perform all of the \c glEnableVertexAttribArray
	and \c glVertexAttrib*Pointer calls to associate a buffer object with this format.
	It is a RAII class, so the destructor will call \c glDisableVertexAttribArray to
	disable the arrays.

	This class uses value semantics and is copyable.
	**/
	class VertexFormat
	{
	public:
		/**
		\brief Creates an empty vertex format. You should fill it with data via copy assignment.
		
		This exists mainly to make it easy to store these.
		**/
		VertexFormat();

		/**
		\brief Creates a VertexFormat from a sequence of AttribDesc objects.

		The order of the sequence of attributes will match the order of \a attribs.
		
		\throw AttributeIndexMultipleRefException If any of the \a attribs refer to the same attribute location as any of the others.
		**/
		VertexFormat(const AttributeList &attribs);

		///Retrieves the size of an entire vertex, including any padding.
		size_t GetVertexByteSize() const {return m_vertexSize;}

		///Gets the number of vertex attributes.
		size_t GetNumAttribs() const {return m_attribs.size();}

		///Gets the AttribDesc, given an index between 0 and GetNumAttribs.
		///\throw std::out_of_range If attribIx is >= GetNumAttribs.
		AttribDesc GetAttribDesc(size_t attribIx) const;

		///Gets the byte offset for a particular attribute, given an index between 0 and GetNumAttribs.
		///\throw std::out_of_range If attribIx is >= GetNumAttribs.
		size_t GetAttribByteOffset(size_t attribIx) const;

		/**
		\brief Binds the VertexFormat to the context.

		This function assumes that a valid VAO is bound (if one is needed), as well as `GL_ARRAY_BUFFER`.

		The following OpenGL state is touched by this function:

		\li The enable state of all of the attributes in the format will be set to enabled.
		\li For each such attribute location, `glVertexAttrib*Pointer` will be called.

		This function assumes that all vertex attributes come from the buffer object currently bound
		to `GL_ARRAY_BUFFER`. Therefore, you can only use it with a single buffer object.

		\param baseOffset The byte offset from the start of the buffer object to where the vertex data is.
		**/
		void BindAttributes(size_t baseOffset) const;

		/**
		\brief Binds the attribute given by the attribute index to the context.
		
		This function assumes that a valid VAO is bound (if one is needed), as well as `GL_ARRAY_BUFFER`.

		The following OpenGL state is touched by this function:

		\li The enable state of the attribute referred to by \a attribIx will be set to enable.
		\li The attribute location for \a attribIx will have glVertexAttrib*Pointer called on it.

		This function assumes that all vertex attributes come from the buffer object currently bound
		to `GL_ARRAY_BUFFER`. Therefore, you can only use it with a single buffer object.

		\param baseOffset The byte offset from the start of the buffer object to where the vertex data is.
		\param attribIx The index of the attribute to bind.
		**/
		void BindAttribute(size_t baseOffset, size_t attribIx) const;

		/**
		\brief Binds the VertexFormat using
		[ARB_vertex_attrib_format](http://www.opengl.org/wiki/Vertex_Specification#Separate_attribute_format).

		This function assumes that a valid VAO is bound (if one is needed).

		The following OpenGL state is touched by this function:

		- The enable state of all of the attributes in the format will be set to enabled.
		- For each such attribute location, `glVertexAttrib*Format` will be called.
		- For each such attribute location, `glVertexAttribBinding` will be called with \a bindingIndex.

		This function uses the offsets computed by GetAttribByteOffset(), so it assumes that all vertex
		attributes come from a single buffer object. You can bind the buffer later with `glBindVertexBuffer`.

		\param bindingIndex The buffer binding index to use for all vertex attributes.

		\note No exception will be thrown if ARB_vertex_attrib_format or GL 4.3 are not available.
		**/
		void BindAttribFormats(GLuint bindingIndex) const;

		/**
		\brief Binds the attribute given by the attribute index using
		[ARB_vertex_attrib_format](http://www.opengl.org/wiki/Vertex_Specification#Separate_attribute_format).

		This function assumes that a valid VAO is bound (if one is needed).

		The following OpenGL state is touched by this function:

		- The enable state of the attribute referred to by \a attribIx will be set to enable.
		- The attribute location for \a attribIx will have `glVertexAttrib*Format` will be called.
		- The attribute location for \a attribIx will have `glVertexAttribBinding` called with \a bindingIndex.

		This function uses the offsets computed by GetAttribByteOffset(), so it assumes that all vertex
		attributes come from a single buffer object. You can bind the buffer later with `glBindVertexBuffer`.

		\note No exception will be thrown if ARB_vertex_attrib_format or GL 4.3 are not available.
		**/
		void BindAttribFormat( size_t attribIx, GLuint bindingIndex ) const;

		/**
		\brief Disables the attributes.

		The following OpenGL state is touched by this function:

		\li The enable state of all of the attributes in the format will be set to disabled.
		**/
		void DisableAttributes() const;

		/**
		\ingroup module_glmesh_draw
		\brief RAII-style class for binding a VertexFormat to the OpenGL context.
		
		The constructors of this class call VertexFormat::BindAttributes or
		VertexFormat::BindAttribFormat, as appropriate. The destructor
		calls VertexFormat::DisableAttributes.
		
		This class can
		[use the ARB_vertex_attrib_binding functionality](http://www.opengl.org/wiki/Vertex_Specification#Separate_attribute_format)
		instead of `glVertexAttribPointer`. If you do, then this class
		only changes the vertex format state, not the buffer binding state. That is, it will call
		`glEnable/DisableVertexAttrbiArray` and [`glVertexAttribFormat`](http://www.opengl.org/wiki/GLAPI/glVertexAttribFormat),
		but not `glVertexAttribBinding`,
		`glBindVertexBuffer`, or `glVertexBindingDivisor`.

		Note that all of the attributes will still have the same stride, and the offsets will be computed
		as though it all comes from a single buffer. You can use multiple separate VertexFormat objects
		if you want to have different buffers with different attributes for the same mesh.
		
		If you are not using ARB_vertex_attrib_binding, then this class assumes that
		all vertex data comes from the buffer currently bound to `GL_ARRAY_BUFFER`.

		The constructors have the effect of calling VertexFormat::BindAttributes or
		VertexFormat::BindAttributeFormats, as appropriate. Those functions define the
		OpenGL state that will be changed. The destructor will call VertexFormat::DisableAttributes.

		Assuming all of your buffer setup is in order (ie: if you're using separate attribute formats,
		you [have bound a buffer](http://www.opengl.org/wiki/GLAPI/glBindVertexBuffer)
		and [set the attribute binding](http://www.opengl.org/wiki/GLAPI/glVertexAttribBinding)),
		you can [use any OpenGL rendering functions](http://www.opengl.org/wiki/Vertex_Rendering)
		to render using the VertexFormat given.
		**/
		class Enable
		{
			Enable(const Enable&) = delete;
			Enable& operator=(const Enable&) = delete;
		public:
			/**
			\brief Binds the vertex format to the OpenGL context, given a byte offset to the first vertex.

			Calls VertexFormat::BindAttributes on \a fmt.
			**/
			Enable(const VertexFormat &fmt, size_t baseOffset);

			/**
			\brief Binds the vertex format to the OpenGL context, using
			[ARB_vertex_attrib_binding](http://www.opengl.org/wiki/Vertex_Specification#Separate_attribute_format).

			Calls VertexFormat::BindAttribFormat on \a fmt. You are expected to make the appropriate
			`glBindVertexBuffer` calls for the buffer yourself.

			To call this function, pass glmesh::sepFormat as the third parameter (or a default-constructed
			object).

			\note No exception will be thrown if ARB_vertex_attrib_format or GL 4.3 are not available.
			**/
			Enable(const VertexFormat &fmt, GLuint bindingIndex, SeparateAttribFormatTag);

			///Unbinds the vertex format by calling VertexFormat::DisableAttributes.
			~Enable();

		private:
			const VertexFormat &m_fmt;
		};

	private:
		AttributeList m_attribs;
		std::vector<size_t> m_attribOffsets;
		size_t m_vertexSize;
	};

	///@}
}


#endif //GLSDK_MESH_VERTEX_FORMAT_H
