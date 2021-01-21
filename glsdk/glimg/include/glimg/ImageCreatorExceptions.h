/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_IMAGE_CREATOR_EXCEPTIONS_H
#define GLIMG_IMAGE_CREATOR_EXCEPTIONS_H

#include <string>
#include <exception>

namespace glimg
{
	///\addtogroup module_glimg_exceptions
	///@{

	///Base class for all exceptions thrown by ImageCreator.
	class ImageCreationException : public std::exception
	{
	public:
	    virtual ~ImageCreationException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	///Thrown if the ImageCreator is given a face count other than 1 or 6.
	class BadFaceCountException : public ImageCreationException
	{
	public:
		BadFaceCountException()
		{
			message = "Must pass 1 or 6 as the face count.";
		}
	};

	///Thrown if the user attempts to provide a cubemap that isn't two-dimensional.
	class CubemapsMustBe2DException : public ImageCreationException
	{
	public:
		CubemapsMustBe2DException()
		{
			message = "Textures with a face count of 6 MUST be 2D textures.";
		}
	};

	///Thrown if the user attempts to have 3D array images, which are not allowed.
	class No3DTextureArrayException : public ImageCreationException
	{
	public:
		No3DTextureArrayException()
		{
			message = "Images cannot be 3D arrays.";
		}
	};

	///Thrown if the mipmap or array count is not greater than zero.
	class NoImagesSpecifiedException : public ImageCreationException
	{
	public:
		NoImagesSpecifiedException()
		{
			message = "Mipmap and array count must be > 0.";
		}
	};

	///Thrown if the ImageCreator is asked to insert an image outside of the \a arrayCount.
	class ArrayOutOfBoundsException : public ImageCreationException
	{
	public:
		ArrayOutOfBoundsException()
		{
			message = "Attempted to add an image to an array index that doesn't exist.";
		}
	};

	///Thrown if the ImageCreator is asked to insert an image outside of the \a mipmapCount
	class MipmapLayerOutOfBoundsException : public ImageCreationException
	{
	public:
		MipmapLayerOutOfBoundsException()
		{
			message = "Attempted to add an image to a mipmap layer that doesn't exist.";
		}
	};

	///Thrown if the ImageCreator is asked to insert an image outside of the \a faceCount
	class FaceIndexOutOfBoundsException : public ImageCreationException
	{
	public:
		FaceIndexOutOfBoundsException()
		{
			message = "Attempted to add an image to a face index that doesn't exist.";
		}
	};

	///Thrown when attempting to do anything except destroy an ImageCreator object after calling ImageCreator::CreateImage.
	class ImageSetAlreadyCreatedException : public ImageCreationException
	{
	public:
		ImageSetAlreadyCreatedException()
		{
			message = "Attempted to use an ImageCreator that has already been used to create an ImageSet.";
		}
	};
	///@}
}


#endif //GLIMG_IMAGE_CREATOR_EXCEPTIONS_H
