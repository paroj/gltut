/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/


#ifndef GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H
#define GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H

/**
\file
\brief Exceptions for texture generation functions.

**/

#include <exception>
#include <string>

namespace glimg
{
	///\addtogroup module_glimg_exceptions
	///@{

	///Base class for all exceptions thrown by the texture loaders.
	class TextureGenerationException : public std::exception
	{
	public:
	    virtual ~TextureGenerationException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	///Thrown if the image format cannot be used because the OpenGL implementation doesn't support the format.
	class ImageFormatUnsupportedException : public TextureGenerationException
	{
	public:
		ImageFormatUnsupportedException()
		{
			message = "The image format is not supported by this OpenGL implementation.";
		}

		explicit ImageFormatUnsupportedException(const std::string &msg)
		{
			message = "The image format is not supported by this OpenGL implementation for this reason:\n";
			message += msg;
		}
	};

	///Thrown if the texture type that was asked to be created is not supported by this OpenGL implementation.
	class TextureUnsupportedException : public TextureGenerationException
	{
	public:
		TextureUnsupportedException()
		{
			message = "The texture type is not supported by this OpenGL implementation.";
		}

		explicit TextureUnsupportedException(const std::string &msg)
		{
			message = "The texture type is not supported by this OpenGL implementation for this reason:\n";
			message += msg;
		}
	};

	///Thrown because the texture type is not yet supported by GL Image.
	class TextureUnexpectedException : public TextureGenerationException
	{
	public:
		TextureUnexpectedException()
		{
			message = "The texture type is not supported by glimg at this time.";
		}

		explicit TextureUnexpectedException(const std::string &msg)
		{
			message = "The texture type is not supported by glimg at this time:\n";
			message += msg;
		}
	};

	///Thrown when using the FORCE_REQUIRED_FORMATS flag and the format could not be converted to a required one without compromising data.
	class CannotForceRenderTargetException : public TextureGenerationException
	{
	public:
		CannotForceRenderTargetException()
		{
			message = "The image format cannot be forced to be a renderable format without compromising the data.";
		}
	};

	///Thrown when using the FORCE_TEXTURE_STORAGE flag and the OpenGL implementation doesn't support it.
	class CannotForceTextureStorage : public TextureGenerationException
	{
	public:
		CannotForceTextureStorage()
		{
			message = "The current OpenGL implementation does not support ARB_texture_storage or GL 4.2 or above.";
		}
	};


	///Thrown when using the FORCE_DSA flag and the OpenGL implementation doesn't support it.
	class CannotForceDSAUsage : public TextureGenerationException
	{
	public:
		CannotForceDSAUsage()
		{
			message = "The current OpenGL implementation does not support EXT_direct_state_access";
		}
	};
	///@}
}



#endif //GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H
