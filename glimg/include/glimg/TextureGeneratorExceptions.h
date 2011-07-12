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

		virtual const char *what() {return message.c_str();}

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

	///Thrown if the image format given to a texture conversion routine is invalid.
	class ImageFormatUnexpectedException : public TextureGenerationException
	{
	public:
		ImageFormatUnexpectedException()
		{
			message = "This image format is not supported by glimg.\nNo idea how we got here.";
		}

		explicit ImageFormatUnexpectedException(const std::string &msg)
		{
			message = "This image format is not supported by glimg.\n";
			message += msg;
		}
	};
	///@}
}



#endif //GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H
