/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_IMAGE_SET_H
#define GLIMG_IMAGE_SET_H

/**
\file

\brief Contains the ImageSet class and associated objects.
**/

#include "ImageFormat.h"
#include <memory>

namespace glimg
{
	///\addtogroup module_glimg_imageset
	///@{

	/**
	\brief Describes the dimensionality of an image.
	
	**/
	struct Dimensions
	{
		int numDimensions;	///<The number of dimensions of an image. Can be 1, 2, or 3.
		int width;			///<The width of the image. Always valid.
		int height;			///<The height of the image. Only valid if numDimensions is 2 or 3.
		int depth;			///<The depth of the image. Only valid if numDimensions is 3.

		///Computes the number of rows of pixel data in the image.
		int NumLines() const
		{
			switch(numDimensions)
			{
			case 1:
				return 1;
			case 2:
				return height;
			case 3:
				return depth * height;
			}

			//Should not be possible.
			return -1;
		}
	};

	namespace detail
	{
		class ImageSetImpl;
		typedef std::shared_ptr<const ImageSetImpl> ImageSetImplPtr;
	}

	class ImageSet;

	/**
	\brief Represents a single image of a certain dimensionality.

	The internal data of the image can be retrieved. Objects of this type can be retrieved from
	an ImageSet, via ImageSet::GetImage.

	This object uses reference semantics. Every copy of it will refer to the same image from the same
	ImageSet.
	**/
	class SingleImage
	{
	public:
		///Get the dimensions of the image.
		Dimensions GetDimensions() const;

		///Get the format of the image.
		ImageFormat GetFormat() const;

		/**
		\brief Retrieves a pointer to this image's pixel data.

		The format of this pixel data is defined by the ImageFormat returned from GetFormat().

		Do not delete this pointer. It is owned by this object (and the ImageSet it came from).
		**/
		const void *GetImageData() const;

		///Returns the size in bytes of the image's pixel data.
		size_t GetImageByteSize() const;

	private:
		detail::ImageSetImplPtr m_pImpl;
		int m_arrayIx;
		int m_faceIx;
		int m_mipmapLevel;

		friend class detail::ImageSetImpl;
		friend class ImageSet;

		SingleImage(detail::ImageSetImplPtr pImpl, int mipmapLevel, int arrayIx, int faceIx);
	};

	/**
	\brief Represents a set of images that can be stored in a texture object.

	This class represents the full range of possible image layouts with regard to texture objects. All
	images in the ImageSet use the same format.

	The images in an ImageSet are named by a triple of numbers: mipmap level, array index, and face index.
	The maximum number of each of these is queriable. The size of the ImageSet is the size of all images from
	mipmap level 0. Each mipmap will have the same number of array indices and faces.

	Faces represent the faces of a cubemap. So for non-cubemap textures, GetFaceCount will return 1. The order
	of the faces in the cubemap is the same as the order of the faces for ARB_texture_cube_map_array extension.
	That is, the order of the GL_TEXTURE_CUBE_MAP_* enumerators.
	
	Array indices represent images that go into an array texture. Array-cubemap textures are arranged in memory
	as specified in the ARB_texture_cube_map_array extension.

	This object uses reference semantics. Every copy of it will refer to the same image data.
	**/
	class ImageSet
	{
	public:
		/**
		\brief Returns the dimensionality of the base mipmap image.
		**/
		Dimensions GetDimensions() const;

		/**
		\brief Returns the number of mipmap levels the image set contains.

		\return The number of mipmap levels in the image set. The minimum is 1.
		**/
		int GetMipmapCount() const;

		/**
		\brief Returns the number of array images this image set has.

		This function will return the number of array images in the image set. The minimum is 1.

		This API makes no distinction between an array of length 1 and a non-array texture.
		If such a distinction needs to be made, it should be made in the uploading of the image's data,
		not in the ImageSet.
		**/
		int GetArrayCount() const;

		/**
		\brief Returns the number of faces in the image set.

		\return The number of faces in the image set. It will be 1 for regular images,
		and 6 for cubemaps and cubemap arrays.
		**/
		int GetFaceCount() const;

		/**
		\brief Retrieves the image format that describes all images in this ImageSet.
		**/
		ImageFormat GetFormat() const;

		/**
		\brief Retrieves the image at the given mipmap level, array index, and face index.
		
		\return A reference to the image. As long as this object or a SingleImage that
		references this object exists, the image data will continue to exist.
		**/
		SingleImage GetImage(int mipmapLevel, int arrayIx = 0, int faceIx = 0) const;

		/**
		\brief Retrieves a pointer to the full array data for the entire mipmap level.

		This data is formatted explicitly for use with array textures and cubemap-array textures.
		
		\return A pointer to the image data. DO NOT DELETE THIS POINTER. Also, do not use this
		pointer after this object is destroyed.
		**/
		const void *GetImageArray(int mipmapLevel) const;

	private:
		detail::ImageSetImplPtr m_pImpl;

		explicit ImageSet(detail::ImageSetImplPtr pImpl);

		friend class ImageCreator;
		friend void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
	};

	///@}
}


#endif //GLIMG_IMAGE_SET_H
