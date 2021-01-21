//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glutil/Shader.h"

namespace glutil
{
	namespace
	{
		void ThrowIfShaderCompileFailed(GLuint shader)
		{
			GLint status;
			gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
			if (status == gl::FALSE_)
				throw CompileLinkException(shader);
		}

		void ThrowIfProgramLinkFailed(GLuint program)
		{
			GLint status;
			gl::GetProgramiv (program, gl::LINK_STATUS, &status);
			if (status == gl::FALSE_)
			{
				throw CompileLinkException(program, true);
			}
		}

		void ThrowIfNotSeparable()
		{
			if(!glload::IsVersionGEQ(4, 1))
			{
				if(!gl::exts::var_ARB_separate_shader_objects)
					throw SeparateShaderNotSupported();
			}
		}
	}

	CompileLinkException::CompileLinkException( GLuint shader )
	{
		GLint infoLogLength;
		gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		gl::GetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		message.assign(strInfoLog, infoLogLength);

		delete[] strInfoLog;

		gl::DeleteShader(shader);
	}

	CompileLinkException::CompileLinkException( GLuint program, bool )
	{
		GLint infoLogLength;
		gl::GetProgramiv(program, gl::INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		gl::GetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		message.assign(strInfoLog, infoLogLength);

		delete[] strInfoLog;

		gl::DeleteProgram(program);
	}

	SeparateShaderNotSupported::SeparateShaderNotSupported()
		: ShaderException("Implementation does not support shader object separation.")
	{}

	GLuint CompileShader( GLenum shaderType, const std::string& shaderText )
	{
		GLuint shader = gl::CreateShader(shaderType);
		GLint textLength = (GLint)shaderText.size();
		const GLchar *pText = static_cast<const GLchar *>(shaderText.data());
		gl::ShaderSource(shader, 1, &pText, &textLength);
		gl::CompileShader(shader);

		ThrowIfShaderCompileFailed(shader);

		return shader;
	}

	GLuint CompileShader( GLenum shaderType, refs::array_ref<const char *> shaderList )
	{
		GLuint shader = gl::CreateShader(shaderType);
		gl::ShaderSource(shader, shaderList.size(),
			static_cast<const GLchar * const*>(shaderList.data()), NULL);
		gl::CompileShader(shader);

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

		GLuint shader = gl::CreateShader(shaderType);
		gl::ShaderSource(shader, shaderList.size(), &stringList[0], &stringLengths[0]);
		gl::CompileShader(shader);

		ThrowIfShaderCompileFailed(shader);

		return shader;
	}

	GLuint LinkProgram( GLuint shaderOne, GLuint shaderTwo )
	{
		GLuint program = gl::CreateProgram();
		return LinkProgram(program, shaderOne, shaderTwo);
	}

	GLuint LinkProgram( GLuint program, GLuint shaderOne, GLuint shaderTwo )
	{
		gl::AttachShader(program, shaderOne);
		gl::AttachShader(program, shaderTwo);	

		gl::LinkProgram(program);
		ThrowIfProgramLinkFailed(program);

		gl::DetachShader(program, shaderOne);
		gl::DetachShader(program, shaderTwo);	
		return program;
	}

	GLuint LinkProgram( const std::string& vertexShader, const std::string& fragmentShader )
	{
		UniqueShader vertShader(CompileShader(gl::VERTEX_SHADER, vertexShader));
		UniqueShader fragShader(CompileShader(gl::FRAGMENT_SHADER, fragmentShader));

		return LinkProgram(vertShader, fragShader);
	}

	GLuint LinkProgram( GLuint program, const std::string& vertexShader, const std::string& fragmentShader )
	{
		UniqueShader vertShader(CompileShader(gl::VERTEX_SHADER, vertexShader));
		UniqueShader fragShader(CompileShader(gl::FRAGMENT_SHADER, fragmentShader));

		return LinkProgram(program, vertShader, fragShader);;
	}

	GLuint LinkProgram( GLuint shader, bool isSeparable )
	{
		if(isSeparable)
			ThrowIfNotSeparable();

		GLuint program = gl::CreateProgram();
		if(isSeparable)
			gl::ProgramParameteri(program, gl::PROGRAM_SEPARABLE, gl::TRUE_);

		gl::AttachShader(program, shader);

		gl::LinkProgram(program);
		ThrowIfProgramLinkFailed(program);
		gl::DetachShader(program, shader);
		return program;
	}

	GLuint LinkProgram( refs::array_ref<GLuint> shaders, bool isSeparable )
	{
		if(isSeparable)
			ThrowIfNotSeparable();

		GLuint program = gl::CreateProgram();
		if(isSeparable)
			gl::ProgramParameteri(program, gl::PROGRAM_SEPARABLE, gl::TRUE_);

		return LinkProgram(program, shaders);
	}

	GLuint LinkProgram( GLuint program, refs::array_ref<GLuint> shaders )
	{
		for(size_t loop = 0; loop < shaders.size(); ++loop)
			gl::AttachShader(program, shaders[loop]);

		gl::LinkProgram(program);
		ThrowIfProgramLinkFailed(program);

		for(size_t loop = 0; loop < shaders.size(); ++loop)
			gl::DetachShader(program, shaders[loop]);

		return program;
	}

	GLuint MakeSeparableProgram( GLenum shaderType, const char *shaderText )
	{
		ThrowIfNotSeparable();

		GLuint program = gl::CreateShaderProgramv(shaderType, 1, &shaderText);
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

		GLuint program = gl::CreateShaderProgramv(shaderType, shaderList.size(),
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
		gl::DeleteShader(m_shader);
		m_shader = 0;
	}

	void UniqueProgram::Disengage()
	{
		gl::DeleteProgram(m_program);
		m_program = 0;
	}
}
