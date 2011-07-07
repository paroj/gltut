#ifndef GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H
#define GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H

#include <exception>
#include <string>

namespace glimg
{
	class TextureGenerationException : public std::exception
	{
	public:
	    virtual ~TextureGenerationException() throw() {}

		virtual const char *what() {return message.c_str();}

	protected:
		std::string message;
	};

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

	class CannotForceRenderTargetException : public TextureGenerationException
	{
	public:
		CannotForceRenderTargetException()
		{
			message = "The image format cannot be forced to be a renderable format without compromising the data.";
		}
	};

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

}



#endif //GLIMG_TEXTURE_GENERATOR_EXCEPTIONS_H
