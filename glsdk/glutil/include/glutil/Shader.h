/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

/**
\file
\brief Includes \ref module_glutil_program "functions to help load and validate shaders and programs". This header must be included after an OpenGL header.
**/

#include <exception>
#include <string>
#include <vector>
#include "array_ref.h"

namespace glutil
{
	///\addtogroup module_glutil_exceptions
	///@{

	///Base class for all exceptions thrown by shader and program creation functions.
	class ShaderException : public std::exception
	{
	public:
		virtual ~ShaderException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;

		ShaderException() {}
		ShaderException(const char *msg) : message(msg) {}
	};

	///Thrown if the user requests the creation of separate programs, but the implementation cannot do that.
	class SeparateShaderNotSupported : public ShaderException
	{
	public:
		SeparateShaderNotSupported();
	};

	///Thrown if the compilation or linking fails. The log will be stored in this exception.
	class CompileLinkException : public ShaderException
	{
	public:
		CompileLinkException(GLuint shader);
		CompileLinkException(GLuint program, bool);

		virtual ~CompileLinkException() throw() {}
	};
	///@}

	///\addtogroup module_glutil_program
	///@{

	/**
	\name Shader Compilation
	
	These functions generate shaders from text strings. They will throw exceptions in the event
	of compilation failure.
	**/
	///@{

	/**
	\brief Creates a shader object and compiles it with the given text string.

	This function compiles a single string of shader text to produce an OpenGL shader object
	for the given shader stage.

	\param shaderType The shader stage that the shader object is created for.
	\param shaderText The GLSL shader text string.
	\return The successfully compiled shader object.

	\throw CompileLinkException Thrown if the shader compilation fails. The shader object will
	be destroyed, and the error log will be stored in the exception.
	**/
	GLuint CompileShader(GLenum shaderType, const std::string& shaderText);

	/**
	\brief As CompileShader(GLenum, const char *), but with a list of strings.	
	**/
	GLuint CompileShader(GLenum shaderType, refs::array_ref<const char *> shaderList);

	/**
	\brief As CompileShader(GLenum, const char *), but with a list of strings.	
	**/
	GLuint CompileShader(GLenum shaderType, const std::vector<std::string> &shaderList);
	///@}

	/**
	\name Program Linking

	These functions take one or more shader objects and link them together into a program. In the event
	of a linker error, they will throw an exception.

	All shader objects are detached from the program that is returned.
	**/
	///@{

	/**
	\brief Links the two shader objects into a single program.

	This is a convenience function for the common case of pairing a vertex shader with a fragment
	shader. It takes the two shaders and links them together into a freshly-created program
	object.

	This function does not allow the user the chance to set pre-link parameters, like
	transform-feedback, vertex attributes, fragment data locations, or the like. Most of these
	can be hooked in via features like explicit_attrib_location and similar extensions.

	\throw CompileLinkException Thrown if the linking fails. The program will be
	destroyed, and the error log will be stored in the exception.
	**/
	GLuint LinkProgram(GLuint shaderOne, GLuint shaderTwo);

	///As LinkProgram(GLuint, GLuint), except that it is given a program to do the linking within.
	GLuint LinkProgram(GLuint program, GLuint shaderOne, GLuint shaderTwo);

	/**
	\brief Creates a program from two shader strings, one for a vertex shader and one for a fragment shader.
	
	This is a convenience function for the common case of pairing a vertex shader with a fragment
	shader. It takes the two shaders by string and links them together into a freshly-created program
	object.

	This function does not allow the user the chance to set pre-link parameters, like
	transform-feedback, vertex attributes, fragment data locations, or the like. Most of these
	can be hooked in via features like explicit_attrib_location and similar extensions.

	\throw CompileLinkException Thrown if the shader compilation or program linking fails.
	In all cases, any previously created shader/program objects will be destroyed.
	**/
	GLuint LinkProgram(const std::string& vertexShader, const std::string& fragmentShader);

	///As LinkProgram(boost::string_ref, boost::string_ref), except that it is given a program to do the linking within.
	GLuint LinkProgram(GLuint program, const std::string& vertexShader, const std::string& fragmentShader);


	/**
	\brief Takes a single shader and links it into a program.

	This function is generally only useful when using separable programs.
	
	\param shader The shader to link.
	\param isSeparable If true, then the program will be linked with the GL_SEPARABLE_PROGRAM option.
	\return The successfully linked program object.

	\throw CompileLinkException Thrown if the linking fails. The program will be
	destroyed, and the error log will be stored in the exception.
	\throw SeparateShaderNotSupported If \a isSeparable is true, thrown when the current GL
	implementation does not support ARB_separate_shader_objects or GL 4.1 or above.
	**/
	GLuint LinkProgram(GLuint shader, bool isSeparable = false);

	/**
	\brief As LinkProgram(GLuint, bool), only with a list of shaders.
	**/
	GLuint LinkProgram(refs::array_ref<GLuint> shaders, bool isSeparable = false);

	/**
	\brief Takes a program and links a number of shaders to it.

	\note If a CompileLinkException is thrown, the program object <em>will be destroyed.</em>

	\throw CompileLinkException Thrown if the linking fails. The program will be
	destroyed, and the error log will be stored in the exception.
	**/
	GLuint LinkProgram(GLuint program, refs::array_ref<GLuint> shaders);
	///@}

	/**
	\name Separable Program Creation
	
	These functions generate separable programs from text strings. They will throw exceptions
	in the event that ARB_separate_shader_objects or GL 4.1+ are not available. Exceptions will
	also be thrown if the compiling/linking fails.
	**/
	///@{

	/**
	\brief Creates a single-stage separable program from the given shader text.

	\param shaderType The shader stage that the shader object is created for.
	\param shaderText The GLSL shader text string.
	\return The successfully linked separable program object.
	
	\throw CompileLinkException Thrown if the compiling/linking fails. The program will be
	destroyed, and the error log will be stored in the exception.
	\throw SeparateShaderNotSupported Thrown when the current GL implementation
	does not support ARB_separate_shader_objects or GL 4.1 or above.
	**/
	GLuint MakeSeparableProgram(GLenum shaderType, const char *shaderText);

	/** \copydoc MakeSeparableProgram(GLenum, const char *) **/
	GLuint MakeSeparableProgram(GLenum shaderType, const std::string &shaderText);

	/**
	\brief As MakeSeparableProgram(GLenum, const char *), except with a list of strings.
	**/
	GLuint MakeSeparableProgram(GLenum shaderType, refs::array_ref<const char *> shaderList);

	/**
	\brief As MakeSeparableProgram(GLenum, const char *), except with a list of strings.
	**/
	GLuint MakeSeparableProgram(GLenum shaderType, const std::vector<std::string> &shaderList);
	///@}

	/**
	\brief RAII object for managing a shader object.

	This object manages the lifetime of a shader object. It represents a uniquely-owned shader object.
	It is implicitly convertible to GLuint, so you can use it more or less wherever you used a
	GLuint before.

	It is explicitly non-copyable. C++11 would eventually allow move-semantics, but that's not widely
	available enough to directly support. If you need to transfer ownership, it is swappable, so
	you'll have to make due with [using `swap`](http://en.cppreference.com/w/cpp/concept/Swappable).

	This RAII-style class makes it easy to be exception-safe with shader objects.

	\todo: Implement C++11 move semantics.
	**/
	class UniqueShader
	{
		UniqueShader(const UniqueShader&) = delete;
		UniqueShader& operator=(const UniqueShader&) = delete;
	public:
		///An empty UniqueShader, with shader name 0.
		UniqueShader() : m_shader(0) {}
		///Create a UniqueShader from an existing shader object.
		explicit UniqueShader(GLuint shader) : m_shader(shader) {}
		///Destroys the owned shader object, if any.
		~UniqueShader() {Disengage();}

		///Exchanges shader ownership between the two objects.
		void swap(UniqueShader &other)
		{
			using std::swap;
			swap(m_shader, other.m_shader);
		}

		///Implicit conversion to shader object.
		operator GLuint() const {return m_shader;}

		///The given shader becomes the current shader; the old one is deleted.
		void reset(GLuint newShader = 0)
		{
			Disengage();
			m_shader = newShader;
		}

		/**
		\brief Abandons ownership of the currently-owned shader object.

		After calling this function, the shader object will be unowned. It will \em not have
		been destroyed.

		\return The shader object that used to be owned.
		**/
		GLuint release()
		{
			GLuint shaderName = m_shader;
			m_shader = 0;
			return shaderName;
		}

	private:
		GLuint m_shader;

		void Disengage();
	};

	/**
	\brief RAII object for managing a program object.

	This object manages the lifetime of a program object. It represents a uniquely-owned program object.
	It is implicitly convertible to GLuint, so you can use it more or less wherever you used a
	GLuint before.

	It is explicitly non-copyable. C++11 would eventually allow move-semantics, but that's not widely
	available enough to directly support. If you need to transfer ownership, it is swappable, so
	you'll have to make due with [using `swap`](http://en.cppreference.com/w/cpp/concept/Swappable).

	This RAII-style class makes it easy to be exception-safe with program objects.

	\todo: Implement C++11 move semantics.
	**/
	class UniqueProgram
	{
		UniqueProgram(const UniqueProgram&) = delete;
		UniqueProgram& operator=(const UniqueProgram&) = delete;
	public:
		///An empty UniqueProgram, with program name 0.
		UniqueProgram() : m_program(0) {}
		///Create a UniqueProgram from an existing program object.
		explicit UniqueProgram(GLuint program) : m_program(program) {}
		///Destroys the owned program object, if any.
		~UniqueProgram() {Disengage();}

		///Exchanges program ownership between the two objects.
		void swap(UniqueProgram &other)
		{
			using std::swap;
			swap(m_program, other.m_program);
		}

		///Implicit conversion to program object.
		operator GLuint () const {return m_program;}

		///The given program becomes the current program; the old one is deleted.
		void reset(GLuint newProgram = 0)
		{
			Disengage();
			m_program = newProgram;
		}

		/**
		\brief Abandons ownership of the currently-owned program object.

		After calling this function, the program object will be unowned. It will \em not have
		been destroyed.

		\return The program object that used to be owned.
		**/
		GLuint release()
		{
			GLuint programName = m_program;
			m_program = 0;
			return programName;
		}

	private:
		GLuint m_program;

		void Disengage();
	};

	inline void swap(UniqueShader &lhs, UniqueShader &rhs) {lhs.swap(rhs);}
	inline void swap(UniqueProgram &lhs, UniqueProgram &rhs) {lhs.swap(rhs);}

	///@}
}

#endif //SHADER_UTIL_H
