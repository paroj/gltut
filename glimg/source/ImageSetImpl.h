
#ifndef GLIMG_IMAGE_SET_IMPL_H
#define GLIMG_IMAGE_SET_IMPL_H

#include "glimg/ImageSet.h"
#include "glimg/ImageCreator.h"


namespace glimg
{
	namespace detail
	{
		struct PixelData
		{
			const void *pPixelData;
		};

		struct MipmapLevel
		{
			bool bFullLayer;
			PixelData fullPixelData;
			//This array is indexed with an arrayIx and faceIx. It is indexed
			//as follows: (arrayIx * arrayCount) + faceIx
			std::vector<PixelData> individualDataList;
		};

		class ImageSetImpl
		{
		public:
			ImageSetImpl(MemoryObject *pObject, Dimensions dimensions,
				int arrayCount, int mipmapCount, int faceCount, ImageFormat format,
				std::vector<MipmapLevel> &swapThisIn);

			~ImageSetImpl() {delete m_pMemory;}

			Dimensions GetDimensions() const {return m_dimensions;}
			Dimensions GetDimensions(int mipmapLevel) const;

			int GetArrayCount() const {return m_arrayCount;}
			int GetMipmapCount() const {return m_mipmapCount;}
			int GetFaceCount() const {return m_faceCount;}

			ImageFormat GetFormat() const {return m_format;}

			const MipmapLevel &GetMipmapLevel(int mipmapIx) const {return m_imageData.at(mipmapIx);}

			const void *OffsetPointerForImage(int mipmapIx, int arrayIx, int faceIx) const
			{
				//TODO: Implement this properly.
				return m_imageData.at(mipmapIx).fullPixelData.pPixelData;
			}

		private:
			Dimensions m_dimensions;
			ImageFormat m_format;
			MemoryObject *m_pMemory;
			int m_arrayCount;
			int m_mipmapCount;
			int m_faceCount;

			std::vector<MipmapLevel> m_imageData;
		};
	}
}

#endif // GLIMG_IMAGE_SET_IMPL_H
