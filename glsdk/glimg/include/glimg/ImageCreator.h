/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_IMAGE_CREATOR_H
#define GLIMG_IMAGE_CREATOR_H

#include <vector>
#include <exception>
#include "ImageSet.h"
#include "ImageCreatorExceptions.h"

/**
\file

\brief Include this to gain access to the ability to \ref module_glimg_creation "create ImageSets manually".
**/


namespace glimg
{
	///\addtogroup module_glimg_creation
	///@{

	///A useful typedef for automatic memory management of image data.
	typedef std::vector<unsigned char> ImageBuffer;

	/**
	\brief A factory object for creating ImageSet objects.

	Creating a valid ImageSet is a complicated task. To ensure the validity and veracity of data
	for ImageSet objects, the task of creating them is managed by this factory object.

	This object can be copy constructed (but not copy-assigned), which will copy all of the
	pixel data uploaded thus far.

	The ImageFormat given to this class's constructor serves double-duty. It will be the ImageFormat that
	the resulting ImageSet gets, but it also describes the expected arrangement of any pixel data given
	to the object. This includes the \em alignment part of the ImageFormat.

	Since ImageCreator is designed to be used with OpenGL, it can flip any incoming pixel data written to it.
	If you send image data in top-left coordinates, it will flip the pixels to bottom-left. This \em includes
	compressed textures.
	**/
	class ImageCreator
	{
	public:
		/**
		\brief Creates an ImageCreator factory for making ImageSet objects.

		This constructor will initialize all pixel data to 0. All memory allocation is done by the constructor;
		this ensures that there will be data for images that were asked for even if the user does not specify them.

		\param format The ImageFormat for the ImageSet to be created.
		\param dimensions The dimensionality of the base layer of the image.
		\param mipmapCount The number of mipmaps in the image.
		\param arrayCount The number of arrays of the image.
		\param faceCount The number of faces of the image. Must be either 1 or 6.

		\throw BadFaceCountException If \a faceCount is not 1 or 6.
		\throw CubemapsMustBe2DException If \a faceCount is 6 and \a dimensions.numDimensions != 2.
		\throw No3DTextureArrayException If \a arrayCount > 1 and \a dimensions.numDimensions == 3.
		\throw NoImagesSpecifiedException If \a mipmapCount or \a arrayCount is <= 0, thus specifying no images.
		**/
		ImageCreator(ImageFormat format, Dimensions dimensions, int mipmapCount, int arrayCount, int faceCount);

		/**
		\brief Sets the data for a single image.

		The pixel data from the given buffer will be copied into the given image in the ImageCreator.

		\param pixelData The pixel data for the mipmap. It is expected to be formatted exactly as specified
		by the ImageFormat given to this ImageCreator at creation time.
		\param isTopLeft True if the orientation of the given image data is top-left. False if it is bottom-left.
		\param mipmapLevel The mipmap layer of the image to set.
		\param arrayIx The array index of the image to set.
		\param faceIx The face index of the image to set.

		\throw ImageSetAlreadyCreatedException If CreateImage has already been called for this ImageCreator.
		\throw MipmapLayerOutOfBoundsException If \a mipmapLevel is outside of the \a mipmapCount range
		specified in the constructor.
		\throw ArrayOutOfBoundsException If \a arrayIx is outside of the \a arrayCount range specified in the constructor.
		\throw FaceIndexOutOfBoundsException If \a faceIx is outside of the \a faceCount range specified in the constructor.
		**/
		void SetImageData(const void *pixelData, bool isTopLeft, int mipmapLevel, int arrayIx = 0, int faceIx = 0);

		/**
		\brief Sets the data for an entire mipmap layer.
		
		Each mipmap layer contains a number of array images and faces. This function will specify all
		of this data in one shot. Each array of the image data contains \a faceCount faces. These cubemap
		faces are ordered as defined by the ARB_texture_cube_map_array extension.

		If \a faceCount was 1, then there will only be one face instead of the 6. If \a arrayCount was 1
		then there will only be one set of faces. And if they were both 1, then there is only one image per mipmap level.

		\param pixelData The pixel data for the mipmap. It is expected to be formatted exactly as specified
		by the ImageFormat given to this ImageCreator at creation time. It must contain all of the pixel data
		in the order as above.
		\param isTopLeft True if the orientation of the given image data is top-left. False if it is bottom-left.
		\param mipmapLevel The mipmap layer to set to.

		\throw ImageSetAlreadyCreatedException If CreateImage has already been called for this ImageCreator.
		\throw MipmapLayerOutOfBoundsException If \a mipmapLevel is outside of the \a mipmapCount range
		specified in the constructor.
		**/
		///
		void SetFullMipmapLevel(const void *pixelData, bool isTopLeft, int mipmapLevel);

		/**
		\brief Creates an ImageSet from the stored data. After the completion of this function, this ImageCreator object is now dead.

		Do not use the ImageCreator object after calling this. Deleting it is fine, but the data
		has been \em transferred to the ImageSet, and no longer resides in the ImageCreator. Any attempt
		to use this object afterwards will result in a ImageSetAlreadyCreatedException exception.

		This object is a copyable object (so long as you use copy construction, not copy assignment),
		so if you want to make multiple ImageSet objects from the same ImageCreator,
		just copy construct the object before creating it. The copy will replicate the data.
		**/
		ImageSet *CreateImage();

	private:
		const ImageFormat m_format;
		const Dimensions m_dims;
		const int m_mipmapCount;
		const int m_arrayCount;
		const int m_faceCount;

		//Indexed by mipmap.
		std::vector<ImageBuffer> m_imageData;
		std::vector<size_t> m_imageSizes;

		void CopyImageFlipped(const void *pixelData, unsigned char *pSrcData, int mipmapLevel);
	};

	///@}
}


#endif //GLIMG_IMAGE_CREATOR_H
