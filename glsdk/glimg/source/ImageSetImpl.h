/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLIMG_IMAGE_SET_IMPL_H
#define GLIMG_IMAGE_SET_IMPL_H

#include "glimg/ImageSet.h"
#include "glimg/ImageCreator.h"


namespace glimg
{
	namespace detail
	{
		class ImageSetImpl
		{
		public:
			ImageSetImpl(ImageFormat format, Dimensions dimensions, int mipmapCount, int arrayCount,
				int faceCount, std::vector<ImageBuffer> &imageData, std::vector<size_t> &imageSizes);

			Dimensions GetDimensions() const {return m_dimensions;}
			Dimensions GetDimensions(int mipmapLevel) const;

			int GetArrayCount() const {return m_arrayCount;}
			int GetMipmapCount() const {return m_mipmapCount;}
			int GetFaceCount() const {return m_faceCount;}

			ImageFormat GetFormat() const {return m_format;}

			const void *GetImageData(int mipmapLevel, int arrayIx = 0, int faceIx = 0) const;

			//Returns the byte size for a single image of that mipmap's data.
			//This is for a single array layer/cube face, not the data for the entire mipmap.
			size_t GetImageByteSize(int mipmapLevel) const;

		private:
			ImageFormat m_format;
			Dimensions m_dimensions;
			int m_mipmapCount;
			int m_arrayCount;
			int m_faceCount;

			//Indexed by mipmap.
			std::vector<ImageBuffer> m_imageData;
			std::vector<size_t> m_imageSizes;
		};
	}
}

#endif // GLIMG_IMAGE_SET_IMPL_H
