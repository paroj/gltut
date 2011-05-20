
#ifndef GLIMG_IMAGE_CREATOR_H
#define GLIMG_IMAGE_CREATOR_H

#include <string>
#include <vector>
#include <exception>
#include "ImageSet.h"
#include "ImageCreatorExceptions.h"

namespace glimg
{
	namespace detail
	{
		struct SimpleImage
		{
			const void *pData;
			int arrayIx;
			int mipmapIx;
			int faceIx;
		};

		struct FullLayerImage
		{
			const void *pData;
			int mipmapIx;
		};
	}

	class MemoryObject
	{
	public:
		virtual ~MemoryObject() {}
	};

	class ImageCreator
	{
	public:
		ImageCreator(MemoryObject *pObject, Dimensions dimensions, int arrayCount, int mipmapCount,
			int faceCount, ImageFormat format);

		~ImageCreator();

		void AddImage(const void *pixelData, int arrayIx, int mipmapIx, int faceIx);

		//Adds an array of image data in a single go, specifying an entire mipmap layer.
		//The expected order of the image data is as follows. Each array in the image
		//contain X faces, where X is the faceCount.
		void AddImage(const void *pixelData, int mipmapIx);

		ImageSet *CreateImage();

	private:
		Dimensions m_dimensions;
		ImageFormat m_format;
		MemoryObject *m_pObject;
		int m_arrayCount;
		int m_mipmapCount;
		int m_faceCount;

		std::vector<detail::SimpleImage> m_simpleImages;
		std::vector<detail::FullLayerImage> m_fullLayerImages;
	};
}


#endif //GLIMG_IMAGE_CREATOR_H
