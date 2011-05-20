
#include <assert.h>
#include <algorithm>
#include "glimg/ImageSet.h"
#include "glimg/ImageCreator.h"
#include "ImageSetImpl.h"

namespace glimg
{
	ImageCreator::ImageCreator( MemoryObject *pObject, Dimensions dimensions,
		int arrayCount, int mipmapCount, int faceCount, ImageFormat format )
		: m_dimensions(dimensions)
		, m_format(format)
		, m_pObject(pObject)
		, m_arrayCount(arrayCount)
		, m_mipmapCount(mipmapCount)
		, m_faceCount(faceCount)
	{
		assert(m_pObject);
		assert(m_faceCount == 6 || m_faceCount == 1);

		const std::string &msg = m_format.ValidateFormatText();
		if(!msg.empty())
		{
			delete(m_pObject);
			throw InvalidImageFormatException(msg);
		}
	}

	ImageCreator::~ImageCreator()
	{
		if(m_pObject)
			delete m_pObject;
	}

	namespace
	{
		struct MipmapPred
		{
			MipmapPred(int _mipmapIx) : mipmapIx(_mipmapIx) {}

			bool operator()(const detail::SimpleImage &img)
			{
				return img.mipmapIx == mipmapIx;
			}

			bool operator()(const detail::FullLayerImage &img)
			{
				return img.mipmapIx == mipmapIx;
			}

			int mipmapIx;
		};

		struct ImagePred
		{
			ImagePred(int _arrayIx, int _mipmapIx, int _faceIx)
				: arrayIx(_arrayIx), mipmapIx(_mipmapIx), faceIx(_faceIx)
			{}
			
			bool operator()(const detail::SimpleImage &img)
			{
				return
					(img.arrayIx == arrayIx) && 
					(img.mipmapIx == mipmapIx) && 
					(img.faceIx == faceIx);
			}

			int arrayIx;
			int mipmapIx;
			int faceIx;
		};
	}

	void ImageCreator::AddImage( const void *pixelData, int arrayIx, int mipmapIx, int faceIx )
	{
		if(!m_pObject)
			throw ImageSetAlreadyCreatedException();

		//Check inputs.
		if((arrayIx < 0) || (m_arrayCount <= arrayIx))
			throw ArrayOutOfBoundsException();

		if((mipmapIx < 0) || (m_mipmapCount <= mipmapIx))
			throw MipmapLayerOutOfBoundsException();

		if((faceIx < 0) || (m_mipmapCount <= faceIx))
			throw MipmapLayerOutOfBoundsException();

		//Check to see if this image exists.
		{
			std::vector<detail::FullLayerImage>::iterator found =
				std::find_if(m_fullLayerImages.begin(), m_fullLayerImages.end(), MipmapPred(mipmapIx));

			if(found != m_fullLayerImages.end())
				throw ImageAlreadySpecifiedException();
		}

		{
			std::vector<detail::SimpleImage>::iterator found =
				std::find_if(m_simpleImages.begin(), m_simpleImages.end(),
				ImagePred(arrayIx, mipmapIx, faceIx));

			if(found != m_simpleImages.end())
				throw ImageAlreadySpecifiedException();
		}

		//The image can now be added.
		detail::SimpleImage newData;
		newData.arrayIx = arrayIx;
		newData.mipmapIx = mipmapIx;
		newData.faceIx = faceIx;
		newData.pData = pixelData;

		m_simpleImages.push_back(newData);
	}

	void ImageCreator::AddImage( const void *pixelData, int mipmapIx )
	{
		if(!m_pObject)
			throw ImageSetAlreadyCreatedException();

		//Check inputs.
		if((mipmapIx < 0) || (m_mipmapCount <= mipmapIx))
			throw MipmapLayerOutOfBoundsException();

		//Check to see if this image exists.
		{
			std::vector<detail::FullLayerImage>::iterator found =
				std::find_if(m_fullLayerImages.begin(), m_fullLayerImages.end(), MipmapPred(mipmapIx));

			if(found != m_fullLayerImages.end())
				throw ImageAlreadySpecifiedException();
		}

		{
			std::vector<detail::SimpleImage>::iterator found =
				std::find_if(m_simpleImages.begin(), m_simpleImages.end(),
				MipmapPred(mipmapIx));

			if(found != m_simpleImages.end())
				throw ImageAlreadySpecifiedException();
		}

		//The image can now be added.
		detail::FullLayerImage newData;
		newData.mipmapIx = mipmapIx;
		newData.pData = pixelData;

		m_fullLayerImages.push_back(newData);
	}

	ImageSet * ImageCreator::CreateImage()
	{
		std::vector<detail::MipmapLevel> mipmapList;
		mipmapList.resize(m_mipmapCount);

		//Make sure that we have all of the images we should.
		//Also, build the mipmap data pointer list.
		for(int mipmapIx = 0; mipmapIx < m_mipmapCount; mipmapIx++)
		{
			detail::MipmapLevel &mipmap = mipmapList[mipmapIx];

			std::vector<detail::FullLayerImage>::iterator found =
				std::find_if(m_fullLayerImages.begin(), m_fullLayerImages.end(), MipmapPred(mipmapIx));

			if(found != m_fullLayerImages.end())
			{
				//Add this to the list.
				mipmap.bFullLayer = true;
				detail::PixelData pixelData;
				pixelData.pPixelData = found->pData;
				mipmap.fullPixelData = pixelData;
			}
			else
			{
				mipmap.bFullLayer = false;
				detail::PixelData pixelData;
				pixelData.pPixelData = NULL;
				mipmap.fullPixelData = pixelData;
				mipmap.individualDataList.reserve(m_arrayCount * m_faceCount);

				//Find all of the faces and arrays with this mipmap level in the simple images.
				int iSubIx = 0;
				for(int arrayIx = 0; arrayIx < m_arrayCount; arrayIx++)
				{
					for(int faceIx = 0; faceIx < m_faceCount; faceIx++)
					{
						std::vector<detail::SimpleImage>::iterator found =
							std::find_if(m_simpleImages.begin(), m_simpleImages.end(),
							ImagePred(arrayIx, mipmapIx, faceIx));

						if(found != m_simpleImages.end())
						{
							detail::PixelData pixelData;
							pixelData.pPixelData = found->pData;
							mipmap.individualDataList.push_back(pixelData);
						}
						else
						{
							throw MissingImageException();
						}
					}
				}
			}
		}

		//Create the ImageSetImpl object.
		detail::ImageSetImpl *pImageData = new detail::ImageSetImpl(m_pObject, m_dimensions,
			m_arrayCount, m_mipmapCount, m_faceCount, m_format, mipmapList);

		ImageSet *pImageSet = new ImageSet(pImageData);

		//Transfer ownership.
		m_pObject = NULL;

		return pImageSet;
	}
}
