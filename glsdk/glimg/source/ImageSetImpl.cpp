//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include "ImageSetImpl.h"
#include "Util.h"

namespace glimg
{
	detail::ImageSetImpl::ImageSetImpl( ImageFormat format, Dimensions dimensions,
		int mipmapCount, int arrayCount, int faceCount,
		std::vector<ImageBuffer> &imageData,
		std::vector<size_t> &imageSizes )
		: m_format(format)
		, m_dimensions(dimensions)
		, m_mipmapCount(mipmapCount)
		, m_arrayCount(arrayCount)
		, m_faceCount(faceCount)
	{
		m_imageData.swap(imageData);
		m_imageSizes.swap(imageSizes);
	}

	Dimensions detail::ImageSetImpl::GetDimensions( int mipmapLevel ) const
	{
		return ModifySizeForMipmap(m_dimensions, mipmapLevel);
	}

	const void * detail::ImageSetImpl::GetImageData( int mipmapLevel, int arrayIx, int faceIx ) const
	{
		size_t imageOffset = ((arrayIx * m_faceCount) + faceIx) * m_imageSizes[mipmapLevel];
		return &m_imageData[mipmapLevel][0] + imageOffset;
	}

	size_t detail::ImageSetImpl::GetImageByteSize( int mipmapLevel ) const
	{
		return m_imageSizes[mipmapLevel];
	}
}

