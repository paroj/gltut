
#ifndef GLIMG_IMAGE_SET_H
#define GLIMG_IMAGE_SET_H

/**
\file

\brief Contains the ImageSet class and associated objects.
**/

#include "ImageFormat.h"

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
	};

	namespace detail
	{
		class ImageSetImpl;
	}

	class ImageSet;

	/**
	\brief Represents a single image of a certain dimensionality.
	**/
	class SingleImage
	{
	public:
		~SingleImage();

		Dimensions GetDimensions() const;

		ImageFormat GetFormat() const;

		/**
		\brief Retrieves a pointer to this image's pixel data.

		The format of this pixel data is defined by the ImageFormat returned from GetFormat().

		Do not delete this pointer. It is owned by this object (and the ImageSet it came from).
		**/
		const void *GetImageData() const;

	private:
		const detail::ImageSetImpl *m_pImpl;
		int m_arrayIx;
		int m_faceIx;
		int m_mipmapLevel;

		friend class detail::ImageSetImpl;
		friend class ImageSet;

		SingleImage(const detail::ImageSetImpl *pImpl, int arrayIx, int faceIx, int mipmapLevel);
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
		\brief Returns the dimensionality of the base mipmap image.
		**/
		Dimensions GetDimensions() const;

		/**
		\brief Returns the number of array images this image set has.

		This function will return the number of array images in the image set. The minimum is 1.

		This API makes no distinction between an array of length 1 and a non-array texture.
		If such a distinction needs to be made, it should be made in the uploading of the image's data,
		not in the ImageSet.
		**/
		int GetArrayCount() const;

		/**
		\brief Returns the number of mipmap levels the image set contains.

		\return The number of mipmap levels in the image set. The minimum is 1.
		**/
		int GetMipmapCount() const;

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
		
		\return A pointer to the image. Do not use it after the ImageSet object is destroyed.
		This pointer must be deleted manually.
		**/
		SingleImage *GetImage(int ixMipmapLevel, int ixArray = 0, int ixFace = 0) const;

		/**
		\brief Retrieves a pointer to the full array data for a mipmap level.
		
		\return A pointer to the image data. DO NOT DELETE THIS POINTER. Also, do not use this
		pointer after this object is destroyed.
		**/
		const void *GetImageArray(int ixMipmapLevel) const;

	private:
		detail::ImageSetImpl *m_pImpl;

		explicit ImageSet(detail::ImageSetImpl *pImpl);

		friend class ImageCreator;
		friend void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
	};

	///@}
}


#endif //GLIMG_IMAGE_SET_H
