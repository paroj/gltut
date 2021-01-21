//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <string.h>
#include <sstream>
#include <glload/gl_all.hpp>
#include "glmesh/VertexWriter.h"

namespace glmesh
{
	const GLubyte _detail::InfoTraits<GLubyte>::zero = 0;
	const GLubyte _detail::InfoTraits<GLubyte>::one = 0xFFU;
	const GLbyte _detail::InfoTraits<GLbyte>::zero = 0;
	const GLbyte _detail::InfoTraits<GLbyte>::one = 0x7F;
	const GLushort _detail::InfoTraits<GLushort>::zero = 0;
	const GLushort _detail::InfoTraits<GLushort>::one = 0xFFFFU;
	const GLshort _detail::InfoTraits<GLshort>::zero = 0;
	const GLshort _detail::InfoTraits<GLshort>::one = 0x7FFF;
	const GLuint _detail::InfoTraits<GLuint>::zero = 0;
	const GLuint _detail::InfoTraits<GLuint>::one = 0xFFFFFFFFU;
	const GLint _detail::InfoTraits<GLint>::zero = 0;
	const GLint _detail::InfoTraits<GLint>::one = 0x7FFFFFFF;


	const glm::half _detail::InfoTraits<glm::half>::zero = glm::half(0.0f);
	const glm::half _detail::InfoTraits<glm::half>::one = glm::half(1.0f);
	const GLfloat _detail::InfoTraits<GLfloat>::zero = 0.0f;
	const GLfloat _detail::InfoTraits<GLfloat>::one = 1.0f;
	const GLdouble _detail::InfoTraits<GLdouble>::zero = 0.0;
	const GLdouble _detail::InfoTraits<GLdouble>::one = 1.0;

	MismatchWriterTypeException::MismatchWriterTypeException( int eRequiredType, const std::string &realType )
	{
		std::ostringstream temp;
		temp << "You provided the type \"" << realType << "\", for an attribute of type \"" << eRequiredType
			<< "\"" << std::endl;
		message = temp.str();
	}
}


