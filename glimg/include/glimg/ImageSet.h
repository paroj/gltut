
#ifndef GLIMG_IMAGE_SET_H
#define GLIMG_IMAGE_SET_H

#include "ImageFormat.h"

namespace glimg
{
	struct Dimensions
	{
		int numDimensions;
		int width;
		int height;
		int depth;
	};

	namespace detail
	{
		class ImageSetImpl;
	}

	class ImageSet;

	/**
	\brief Represents a single image of a certain dimensionality.
	**/
	class Image
	{
	public:
		~Image();

		Dimensions GetDimensions() const;

		ImageFormat GetFormat() const;

		const void *GetImageData() const;

	private:
		const detail::ImageSetImpl *m_pImpl;
		int m_arrayIx;
		int m_faceIx;
		int m_mipmapLevel;

		friend class detail::ImageSetImpl;
		friend class ImageSet;

		Image(const detail::ImageSetImpl *pImpl, int arrayIx, int faceIx, int mipmapLevel);
	};

	/**
	\brief Represents a set of images that can be stored in a texture object.

	This class represents the full range of possible image layouts with regard to texture objects. All
	images in the ImageSet use the same format.
	**/
	class ImageSet
	{
	public:
		~ImageSet();

		/**
		\brief Returns the number of dimensions in this image set, as well as the size of the base mipmap image.
		
		This function will return the number of dimensions that the images in the image set contains.
		It also returns the size in pixels of the base image. For dimensions less than 3,
		the base image size will be 0 for the dimensions that aren't present. For example, if
		the image is 2D, the ImageDimensions::depth will be zero.
		**/
		Dimensions GetDimensions() const;

		/**
		\brief Returns the number of array images this image set has.

		This function will return the number of array images in the image set. The minimum is 1.

		The API makes no distinction between an array of length 1 and a non-array texture.
		If such a distinction needs to be made, it should be made in the uploading, not in the storage.
		**/
		int GetArrayCount() const;

		/**
		\brief Returns the number of mipmap levels the image set contains.

		This function will return the number of mipmap levels in the image set. The minimum is 1.
		
		**/
		int GetMipmapCount() const;

		/**
		\brief Returns the number of faces in the image set.

		This function will return the number of faces in the image set. This will be 1 for regular
		images, and 6 for cubemaps and cubemap arrays.
		**/
		int GetFaceCount() const;

		/**
		\brief Retrieves the image format that describes all images in this ImageSet.
		
		**/
		ImageFormat GetFormat() const;

		/**
		\brief Retrieves the image at the given array index, face index, and mipmap level.
		
		\return A pointer to the image. Do not use it after the ImageSet object is destroyed. This pointer must be deleted manually.
		**/
		Image *GetImage(int ixMipmapLevel, int ixArray = 0, int ixFace = 0) const;

		/**
		\brief Retrieves a pointer to the full array data for a mipmap level.
		
		\return A pointer to the image data. DO NOT DELETE THIS POINTER. Also, do not use this pointer after this object is destroyed.
		**/
		const void *GetImageArray(int ixMipmapLevel) const;

	private:
		detail::ImageSetImpl *m_pImpl;

		explicit ImageSet(detail::ImageSetImpl *pImpl);

		friend class ImageCreator;
		friend void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
	};
}


#endif //GLIMG_IMAGE_SET_H
