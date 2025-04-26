//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.

#ifdef __APPLE__
#define FREEGLUT_NO_GL_INCLUDE
#include <OpenGL/gl3.h>
#endif
#include "glutil/Shader.h"

namespace glutil
{
	namespace
	{
		void ThrowIfShaderCompileFailed(GLuint shader)
		{
			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
				throw CompileLinkException(shader);
		}

		void ThrowIfProgramLinkFailed(GLuint program)
		{
			GLint status;
			glGetProgramiv (program, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				throw CompileLinkException(program, true);
			}
		}

		void ThrowIfNotSeparable()
		{
			// if(!glload::IsVersionGEQ(4, 1))
			// {
			// 	if(!glexts::var_ARB_separate_shader_objects)
			// 		throw SeparateShaderNotSupported();
			// }
		}
	}

	CompileLinkException::CompileLinkException( GLuint shader )
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		message.assign(strInfoLog, infoLogLength);

		delete[] strInfoLog;

		glDeleteShader(shader);
	}

	CompileLinkException::CompileLinkException( GLuint program, bool )
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		message.assign(strInfoLog, infoLogLength);

		delete[] strInfoLog;

		glDeleteProgram(program);
	}

	SeparateShaderNotSupported::SeparateShaderNotSupported()
		: ShaderException("Implementation does not support shader object separation.")
	{}

	GLuint CompileShader( GLenum shaderType, const std::string& shaderText )
	{
		GLuint shader = glCreateShader(shaderType);
		GLint textLength = (GLint)shaderText.size();
		const GLchar *pText = static_cast<const GLchar *>(shaderText.data());
		glShaderSource(shader, 1, &pText, &textLength);
		glCompileShader(shader);

		ThrowIfShaderCompileFailed(shader);

		return shader;
	}

	GLuint CompileShader( GLenum shaderType, refs::array_ref<const char *> shaderList )
	{
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, shaderList.size(),
			static_cast<const GLchar * const*>(shaderList.data()), NULL);
		glCompileShader(shader);

		ThrowIfShaderCompileFailed(shader);

		return shader;
	}

	GLuint CompileShader( GLenum shaderType, const std::vector<std::string> &shaderList )
	{
		std::vector<const GLchar *> stringList;
		std::vector<GLint> stringLengths;
		stringList.reserve(shaderList.size());
		stringLengths.reserve(shaderList.size());

		for(size_t loop = 0; loop < shaderList.size(); ++loop)
		{
			stringLengths.push_back((GLint)shaderList[loop].size());
			stringList.push_back(static_cast<const GLchar *>(shaderList[loop].c_str()));
		}

		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, shaderList.size(), &stringList[0], &stringLengths[0]);
		glCompileShader(shader);

		ThrowIfShaderCompileFailed(shader);

		return shader;
	}

	GLuint LinkProgram( GLuint shaderOne, GLuint shaderTwo )
	{
		GLuint program = glCreateProgram();
		return LinkProgram(program, shaderOne, shaderTwo);
	}

	GLuint LinkProgram( GLuint program, GLuint shaderOne, GLuint shaderTwo )
	{
		glAttachShader(program, shaderOne);
		glAttachShader(program, shaderTwo);	

		glLinkProgram(program);
		ThrowIfProgramLinkFailed(program);

		glDetachShader(program, shaderOne);
		glDetachShader(program, shaderTwo);	
		return program;
	}

	GLuint LinkProgram( const std::string& vertexShader, const std::string& fragmentShader )
	{
		UniqueShader vertShader(CompileShader(GL_VERTEX_SHADER, vertexShader));
		UniqueShader fragShader(CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

		return LinkProgram(vertShader, fragShader);
	}

	GLuint LinkProgram( GLuint program, const std::string& vertexShader, const std::string& fragmentShader )
	{
		UniqueShader vertShader(CompileShader(GL_VERTEX_SHADER, vertexShader));
		UniqueShader fragShader(CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

		return LinkProgram(program, vertShader, fragShader);;
	}

	GLuint LinkProgram( GLuint shader, bool isSeparable )
	{
		if(isSeparable)
			ThrowIfNotSeparable();

		GLuint program = glCreateProgram();
		if(isSeparable)
			glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);

		glAttachShader(program, shader);

		glLinkProgram(program);
		ThrowIfProgramLinkFailed(program);
		glDetachShader(program, shader);
		return program;
	}

	GLuint LinkProgram( refs::array_ref<GLuint> shaders, bool isSeparable )
	{
		if(isSeparable)
			ThrowIfNotSeparable();

		GLuint program = glCreateProgram();
		if(isSeparable)
			glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);

		return LinkProgram(program, shaders);
	}

	GLuint LinkProgram( GLuint program, refs::array_ref<GLuint> shaders )
	{
		for(size_t loop = 0; loop < shaders.size(); ++loop)
			glAttachShader(program, shaders[loop]);

		glLinkProgram(program);
		ThrowIfProgramLinkFailed(program);

		for(size_t loop = 0; loop < shaders.size(); ++loop)
			glDetachShader(program, shaders[loop]);

		return program;
	}

	GLuint MakeSeparableProgram( GLenum shaderType, const char *shaderText )
	{
		ThrowIfNotSeparable();

		GLuint program = glCreateShaderProgramv(shaderType, 1, &shaderText);
		ThrowIfProgramLinkFailed(program);
		return program;
	}

	GLuint MakeSeparableProgram( GLenum shaderType, const std::string &shaderText )
	{
		return MakeSeparableProgram(shaderType, shaderText.c_str());
	}

	GLuint MakeSeparableProgram( GLenum shaderType, refs::array_ref<const char *> shaderList )
	{
		ThrowIfNotSeparable();

		GLuint program = glCreateShaderProgramv(shaderType, shaderList.size(),
			static_cast<const GLchar * const*>(shaderList.data()));
		ThrowIfProgramLinkFailed(program);
		return program;
	}

	GLuint MakeSeparableProgram( GLenum shaderType, const std::vector<std::string> &shaderList )
	{
		std::vector<const char *> stringList;
		stringList.reserve(shaderList.size());

		for(size_t loop = 0; loop < shaderList.size(); ++loop)
			stringList.push_back(shaderList[loop].c_str());

		return MakeSeparableProgram(shaderType, refs::array_ref<const char *>(stringList));
	}

	void UniqueShader::Disengage()
	{
		glDeleteShader(m_shader);
		m_shader = 0;
	}

	void UniqueProgram::Disengage()
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}
