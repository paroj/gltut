//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.




#include "glimg/ImageSet.h"
#include "ImageSetImpl.h"

namespace glimg
{
	SingleImage::SingleImage( detail::ImageSetImplPtr pImpl, int mipmapLevel, int arrayIx, int faceIx )
		: m_pImpl(pImpl)
		, m_arrayIx(arrayIx)
		, m_faceIx(faceIx)
		, m_mipmapLevel(mipmapLevel)
	{}

	glimg::Dimensions SingleImage::GetDimensions() const
	{
		return m_pImpl->GetDimensions(m_mipmapLevel);
	}

	glimg::ImageFormat SingleImage::GetFormat() const
	{
		return m_pImpl->GetFormat();
	}

	const void * SingleImage::GetImageData() const
	{
		return m_pImpl->GetImageData(m_mipmapLevel, m_arrayIx, m_faceIx);
	}

	size_t SingleImage::GetImageByteSize() const
	{
		return m_pImpl->GetImageByteSize(m_mipmapLevel);
	}

///////////////////////////////////////////////////////////
	ImageSet::ImageSet( detail::ImageSetImplPtr pImpl )
		: m_pImpl(pImpl)
	{}

	glimg::Dimensions ImageSet::GetDimensions() const
	{
		return m_pImpl->GetDimensions();
	}

	int ImageSet::GetArrayCount() const
	{
		return m_pImpl->GetArrayCount();
	}

	int ImageSet::GetMipmapCount() const
	{
		return m_pImpl->GetMipmapCount();
	}

	int ImageSet::GetFaceCount() const
	{
		return m_pImpl->GetFaceCount();
	}

	glimg::ImageFormat ImageSet::GetFormat() const
	{
		return m_pImpl->GetFormat();
	}

	SingleImage ImageSet::GetImage( int mipmapLevel, int arrayIx, int faceIx ) const
	{
		return SingleImage(m_pImpl, mipmapLevel, arrayIx, faceIx);
	}

	const void * ImageSet::GetImageArray( int mipmapLevel ) const
	{
		return m_pImpl->GetImageData(mipmapLevel, 0, 0);
	}
}

