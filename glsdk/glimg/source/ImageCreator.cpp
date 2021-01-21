//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include "glimg/ImageSet.h"
#include "glimg/ImageCreator.h"
#include "ImageSetImpl.h"
#include "Util.h"

namespace glimg
{
	ImageCreator::ImageCreator( ImageFormat format, Dimensions dimensions,
		int mipmapCount, int arrayCount, int faceCount )
		: m_format(format)
		, m_dims(dimensions)
		, m_mipmapCount(mipmapCount)
		, m_arrayCount(arrayCount)
		, m_faceCount(faceCount)
		, m_imageData(mipmapCount)
		, m_imageSizes(mipmapCount)
	{
		if(m_faceCount != 6 && m_faceCount != 1)
			throw BadFaceCountException();

		if(m_faceCount == 6 && m_dims.numDimensions != 2)
			throw CubemapsMustBe2DException();

		if(m_dims.numDimensions == 3 && m_arrayCount != 1)
			throw No3DTextureArrayException();

		if(m_mipmapCount <= 0 || m_arrayCount <= 0)
			throw NoImagesSpecifiedException();

		//Allocate the memory for our data.
		int bpp = CalcBytesPerPixel(m_format);
		for(int level = 0; level < mipmapCount; ++level)
		{
			Dimensions mipmapDims = ModifySizeForMipmap(m_dims, level);
			size_t imageSize = CalcImageByteSize(m_format, mipmapDims);
			m_imageData[level].resize(imageSize * m_faceCount * m_arrayCount);
			m_imageSizes[level] = imageSize;
		}
	}

	namespace
	{
		//Returns a pointer to the next image.
		const void * CopyPixelsFlipped( unsigned char * pMipmapData, const Dimensions &dims,
			const ImageFormat &format, int mipmapLevel, const void * pixelData, int imageSize )
		{
			//Flip the data. Copy line by line.
			size_t numLines = dims.NumLines();
			size_t lineByteSize = format.AlignByteCount(CalcBytesPerPixel(format) * dims.width);

			//Move the pixel data to the last row.
			const unsigned char *pInputRow = static_cast<const unsigned char *>(pixelData);
			pInputRow += imageSize;
			pInputRow -= lineByteSize;
			for(size_t line = 0; line < numLines; ++line)
			{
				memcpy(pMipmapData, pInputRow, lineByteSize);
				pMipmapData += lineByteSize;
				pInputRow -= lineByteSize;
			}

			return static_cast<const unsigned char *>(pixelData) + imageSize;
		}

		void CopyBlockBC1Flipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			//First 4 bytes are 2 16-bit colors. Keep them the same.
			memcpy(pDst, pSrc, 4);

			//Next four bytes are 16 2-bit values, in row-major, top-to-bottom order,
			//representing the 4x4 pixel data for the block. So copy the bytes in reverse order.
			pDst[4] = pSrc[7];
			pDst[5] = pSrc[6];
			pDst[6] = pSrc[5];
			pDst[7] = pSrc[4];
		}

		void CopyBlockBC2Flipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			//First 8 bytes are stored as 16 4-bit values, in row-major, top-to-bottom order,
			//representing the 4x4 pixel data for the block. So copy every every two bytes backwards.
			pDst[0] = pSrc[6];
			pDst[1] = pSrc[7];
			pDst[2] = pSrc[4];
			pDst[3] = pSrc[5];
			pDst[4] = pSrc[2];
			pDst[5] = pSrc[3];
			pDst[6] = pSrc[0];
			pDst[7] = pSrc[1];

			//Second 8 bytes are BC1 compressed.
			CopyBlockBC1Flipped(pDst + 8, pSrc + 8);
		}

		//Copies the alpha block of a DXT-5, or the R/RG style values.
		void CopyBlockS3TCAlphaFlipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			//First 2 bytes are the alpha values. Copy directly.
			pDst[0] = pSrc[0];
			pDst[1] = pSrc[1];

			pDst += 2;
			pSrc += 2;

			//Next 6 bytes are 16 3-bit values, in row-major, top-to-bottom order,
			//representing the 4x4 pixel data for the block. So copy the bytes in reverse order.
			//Each row is 12-bits in size, and the entire 48-bit value is taken as a little-endian
			//unsigned integer, so the logic is kinda weird.

			/*
			Take the 6 bytes as follows:
			0 1 2 3 4 5

			Label each nibble with a letter:
			0 1 2 3 4 5
			LKJIHGFEDCBA

			If we decode this into a proper 48-bit integer, the order of the data is:
			BADCFEHGJILK

			Now, split it into the 4 rows, each 3 nibbles in size:
			BAD-CFE-HGJ-ILK

			We want to reverse the order of these. So the nibbles we want are in this order:
			ILK-HGJ-CFE-BAD

			In 48-bit integer form, this is
			ILKHGJCFEBAD

			Now, we need to put that in the little-endian order:
			0 1 2 3 4 5
			ADEBCFGJKHIL
			*/

			pDst[0]  = (pSrc[5] & 0x0F) << 4;	//A
			pDst[0] |= (pSrc[4] & 0xF0) >> 4;	//D
			pDst[1]  = (pSrc[3] & 0x0F) << 4;	//E
			pDst[1] |= (pSrc[5] & 0xF0) >> 4;	//B
			pDst[2]  = (pSrc[4] & 0x0F) << 4;	//C
			pDst[2] |= (pSrc[3] & 0xF0) >> 4;	//F

			pDst[3]  = (pSrc[2] & 0x0F) << 4;	//G
			pDst[3] |= (pSrc[1] & 0xF0) >> 4;	//J
			pDst[4]  = (pSrc[0] & 0x0F) << 4;	//K
			pDst[4] |= (pSrc[2] & 0xF0) >> 4;	//H
			pDst[5]  = (pSrc[1] & 0x0F) << 4;	//I
			pDst[5] |= (pSrc[0] & 0xF0) >> 4;	//L
		}

		void CopyBlockBC3Flipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			//First 8 bytes are alpha S3TC compressed.
			CopyBlockS3TCAlphaFlipped(pDst, pSrc);

			//Second 8 bytes are BC1 compressed.
			CopyBlockBC1Flipped(pDst + 8, pSrc + 8);
		}

		void CopyBlockBC4Flipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			CopyBlockS3TCAlphaFlipped(pDst, pSrc);
		}

		void CopyBlockBC5Flipped(unsigned char * pDst, const unsigned char * pSrc)
		{
			CopyBlockS3TCAlphaFlipped(pDst, pSrc);
			CopyBlockS3TCAlphaFlipped(pDst + 8, pSrc + 8);
		}


		template<typename FlipFunc>
		const void *CopyBCFlipped(unsigned char *pMipmapData, const Dimensions &dims,
			const ImageFormat &format, int mipmapLevel, const void *pixelData, int imageSize, FlipFunc FlippingFunc)
		{
			//No support for 3D compressed formats.
			assert(dims.numDimensions != 3);

			CompressedBlockData blockData = GetBlockCompressionData(format.Type());
			const size_t blocksPerRow = (dims.width + (blockData.dims.width - 1)) / blockData.dims.width;

			const size_t blockRowByteSize = blocksPerRow * blockData.byteCount;
			const size_t numTotalBlocks = imageSize / blockData.byteCount;
			const size_t numLines = numTotalBlocks / blocksPerRow;

			//Copy each block.
			const unsigned char *pInputRow = static_cast<const unsigned char *>(pixelData);
			pInputRow += imageSize;
			pInputRow -= blockRowByteSize;
			for(size_t line = 0; line < numLines; ++line)
			{
				for(size_t block = 0; block < blocksPerRow; ++block)
				{
					FlippingFunc(pMipmapData, pInputRow);
					pMipmapData += blockData.byteCount;
					pInputRow += blockData.byteCount;
				}
				//First goes back to beginning, second goes back one row.
				pInputRow -= blockRowByteSize;
				pInputRow -= blockRowByteSize;
			}

			return static_cast<const unsigned char *>(pixelData) + imageSize;
		}
	}

	void ImageCreator::SetImageData( const void *pixelData, bool isTopLeft,
		int mipmapLevel, int arrayIx, int faceIx )
	{
		if(m_imageData.empty())
			throw ImageSetAlreadyCreatedException();

		//Check inputs.
		if((arrayIx < 0) || (m_arrayCount <= arrayIx))
			throw ArrayOutOfBoundsException();

		if((mipmapLevel < 0) || (m_mipmapCount <= mipmapLevel))
			throw MipmapLayerOutOfBoundsException();

		if((faceIx < 0) || (m_faceCount <= faceIx))
			throw FaceIndexOutOfBoundsException();

		size_t imageOffset = ((arrayIx * m_faceCount) + faceIx) * m_imageSizes[mipmapLevel];

		unsigned char *pMipmapData = &m_imageData[mipmapLevel][0];
		pMipmapData += imageOffset;
		if(!isTopLeft)
		{
			memcpy(pMipmapData, pixelData, m_imageSizes[mipmapLevel]);
		}
		else
		{
			CopyImageFlipped(pixelData, pMipmapData, mipmapLevel);
		}
	}

	void ImageCreator::SetFullMipmapLevel( const void *pixelData, bool isTopLeft, int mipmapLevel )
	{
		if(m_imageData.empty())
			throw ImageSetAlreadyCreatedException();

		//Check inputs.
		if((mipmapLevel < 0) || (m_mipmapCount <= mipmapLevel))
			throw MipmapLayerOutOfBoundsException();

		unsigned char *pMipmapData = &m_imageData[mipmapLevel][0];
		const unsigned char *pSrcData = static_cast<const unsigned char *>(pixelData);
		if(!isTopLeft)
		{
			memcpy(pMipmapData, pixelData, m_imageSizes[mipmapLevel] * m_arrayCount * m_faceCount);
		}
		else
		{
			for(int image = 0; image < m_arrayCount * m_faceCount; ++image)
			{
				CopyImageFlipped(pSrcData, pMipmapData, mipmapLevel);
				pSrcData += m_imageSizes[mipmapLevel];
				pMipmapData += m_imageSizes[mipmapLevel];
			}
		}
	}

	ImageSet * ImageCreator::CreateImage()
	{
		if(m_imageData.empty())
			throw ImageSetAlreadyCreatedException();

		std::shared_ptr<detail::ImageSetImpl> pImageData =
			std::make_shared<detail::ImageSetImpl>(m_format, m_dims,
			m_mipmapCount, m_arrayCount, m_faceCount, std::ref(m_imageData), std::ref(m_imageSizes));

		ImageSet *pImageSet = new ImageSet(pImageData);

		return pImageSet;
	}

	void ImageCreator::CopyImageFlipped(const void * pixelData, unsigned char *pDstData, int mipmapLevel)
	{
		Dimensions dims = ModifySizeForMipmap(m_dims, mipmapLevel);
		if(m_format.Type() < DT_NUM_UNCOMPRESSED_TYPES)
		{
			CopyPixelsFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
				m_imageSizes[mipmapLevel]);
		}
		else
		{
			//Have to decode the pixel data and flip it manually.
			switch(m_format.Type())
			{
			case DT_COMPRESSED_BC1:
				CopyBCFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
					m_imageSizes[mipmapLevel], CopyBlockBC1Flipped);
				break;
			case DT_COMPRESSED_BC2:
				CopyBCFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
					m_imageSizes[mipmapLevel], CopyBlockBC2Flipped);
				break;
			case DT_COMPRESSED_BC3:
				CopyBCFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
					m_imageSizes[mipmapLevel], CopyBlockBC3Flipped);
				break;
			case DT_COMPRESSED_UNSIGNED_BC4:
			case DT_COMPRESSED_SIGNED_BC4:
				CopyBCFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
					m_imageSizes[mipmapLevel], CopyBlockBC4Flipped);
				break;
			case DT_COMPRESSED_UNSIGNED_BC5:
			case DT_COMPRESSED_SIGNED_BC5:
				CopyBCFlipped(pDstData, dims, m_format, mipmapLevel, pixelData,
					m_imageSizes[mipmapLevel], CopyBlockBC5Flipped);
				break;
			default:
				memcpy(pDstData, pixelData, m_imageSizes[mipmapLevel]);
				break;
			}
		}
	}
}
