
#include "ImageSetImpl.h"

namespace glimg
{
	namespace
	{
		Dimensions ModifySizeForMipmap(Dimensions origDim, int mipmapLevel)
		{
			for(int iLoop = 0; iLoop < mipmapLevel; iLoop++)
			{
				origDim.width /= 2;
				origDim.height /= 2;
				origDim.depth /= 2;
			}

			return origDim;
		}
	}


	detail::ImageSetImpl::ImageSetImpl( MemoryObject *pObject, Dimensions dimensions,
		int arrayCount, int mipmapCount, int faceCount,
		ImageFormat format, std::vector<MipmapLevel> &swapThisIn )
		: m_dimensions(dimensions)
		, m_format(format)
		, m_pMemory(pObject)
		, m_arrayCount(arrayCount)
		, m_mipmapCount(mipmapCount)
		, m_faceCount(faceCount)
	{
		std::swap(m_imageData, swapThisIn);
	}

	Dimensions detail::ImageSetImpl::GetDimensions( int mipmapLevel ) const
	{
		return ModifySizeForMipmap(m_dimensions, mipmapLevel);
	}
}

