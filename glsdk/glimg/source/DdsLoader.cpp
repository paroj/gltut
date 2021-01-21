//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include <stdio.h>
#include <string.h>
#include "glimg/ImageSet.h"
#include "ImageSetImpl.h"
#include "glimg/ImageCreator.h"
#include "glimg/DdsLoader.h"
#include "DdsLoaderInt.h"
#include "Util.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glimg
{
namespace loaders
{
namespace dds
{
	namespace
	{
		typedef std::vector<unsigned char> FileBuffer;

		void ThrowIfHeaderInvalid(const ddsHeader &header)
		{
			//TODO: Implement;
		}

		//Will either generate this or return the actual one.
		dds10Header GetDDS10Header(const ddsHeader &header, const FileBuffer &ddsData)
		{
			if(header.ddspf.dwFourCC == DDS10_FOUR_CC)
			{
				dds10Header header10;
				size_t offsetToNewHeader = 4 + sizeof(ddsHeader);

				memcpy(&header10, &ddsData[offsetToNewHeader], sizeof(dds10Header));

				return header10;
			}

			//Compute the header manually. Namely, compute the DXGI_FORMAT for the given
			//data.
			dds10Header header10;
			
			//Get dimensionality. Assume 2D unless otherwise stated.
			header10.resourceDimension = DDS_DIMENSION_TEXTURE2D;
			if((header.dwCaps2 & DDSCAPS2_VOLUME) && (header.dwFlags & DDSD_DEPTH))
				header10.resourceDimension = DDS_DIMENSION_TEXTURE3D;

			//Get cubemap.
			DWORD cubemapTest = header.dwCaps2 & DDSCAPS2_CUBEMAP_ALL;
			if(cubemapTest == 0)
			{
				header10.miscFlag = 0;
			}
			else
			{
				//All faces must be specified or none. Otherwise unsupported.
				if(cubemapTest != DDSCAPS2_CUBEMAP_ALL)
					throw DdsFileUnsupportedException(std::string(), "All cubemap faces must be specified.");
				header10.miscFlag = DDS_RESOURCE_MISC_TEXTURECUBE;
			}

			//Array size is... zero?
			header10.arraySize = 0;

			//Use the old-style format.
			header10.dxgiFormat = DXGI_FORMAT_UNKNOWN;

			return header10;
		}

		glimg::Dimensions GetDimensions(const ddsHeader &header, const dds10Header &header10)
		{
			Dimensions dims;
			dims.numDimensions = 1;
			dims.width = header.dwWidth;
			if(header.dwFlags & DDSD_HEIGHT)
			{
				dims.numDimensions = 2;
				dims.height = header.dwHeight;
			}
			if(header.dwFlags & DDSD_DEPTH)
			{
				dims.numDimensions = 3;
				dims.depth = header.dwDepth;
			}

			return dims;
		}

		struct OldDdsFmtMatch
		{
			DWORD dwFlags;
			DWORD bitDepth;
			DWORD rBitmask;
			DWORD gBitmask;
			DWORD bBitmask;
			DWORD aBitmask;
			DWORD fourCC;
		};

		struct OldDdsFormatConv
		{
			UncheckedImageFormat fmt;
			OldDdsFmtMatch ddsFmt;
		};

		bool DoesMatchFormat(const OldDdsFmtMatch &ddsFmt, const ddsHeader &header)
		{
			if(!(header.ddspf.dwFlags & ddsFmt.dwFlags))
				return false;

			if(ddsFmt.dwFlags & DDPF_FOURCC)
			{
				//None of the bit counts matter. Just check the fourCC
				if(ddsFmt.fourCC != header.ddspf.dwFourCC)
					return false;
			}
			else
			{
				//Check the bitcounts, not the fourCC.
				if(header.ddspf.dwRGBBitCount != ddsFmt.bitDepth)
					return false;
				if((ddsFmt.rBitmask & header.ddspf.dwRBitMask) != ddsFmt.rBitmask)
					return false;
				if((ddsFmt.gBitmask & header.ddspf.dwGBitMask) != ddsFmt.gBitmask)
					return false;
				if((ddsFmt.bBitmask & header.ddspf.dwBBitMask) != ddsFmt.bBitmask)
					return false;
				if((ddsFmt.aBitmask & header.ddspf.dwABitMask) != ddsFmt.aBitmask)
					return false;
			}

			return true;
		}

		OldDdsFormatConv g_oldFmtConvert[] =
		{
#include "OldDdsFmtConv.inc"
		};

		UncheckedImageFormat GetImageFormat(const ddsHeader &header, const dds10Header &header10)
		{
			if(header10.dxgiFormat != DXGI_FORMAT_UNKNOWN)
			{
				//TODO: implement.
				return UncheckedImageFormat();
			}

			for(size_t convIx = 0; convIx < ARRAY_COUNT(g_oldFmtConvert); convIx++)
			{
				if(DoesMatchFormat(g_oldFmtConvert[convIx].ddsFmt, header))
					return g_oldFmtConvert[convIx].fmt;
			}

			throw DdsFileUnsupportedException(std::string(), "Could not use the DDS9's image format.");
		}

		void GetImageCounts(int &numArrays, int &numMipmaps, int &numFaces,
			const ddsHeader &header, const dds10Header &header10)
		{
			if(header.dwFlags & DDSD_MIPMAPCOUNT)
				numMipmaps = header.dwMipMapCount;
			else
				numMipmaps = 1;

			if(header10.miscFlag & DDS_RESOURCE_MISC_TEXTURECUBE)
				numFaces = 6;
			else
				numFaces = 1;

			if(header10.arraySize > 1)
				numArrays = header10.arraySize;
			else
				numArrays = 1;
		}

		size_t GetByteOffsetToData(const ddsHeader &header)
		{
			size_t byteOffset = sizeof(ddsHeader) + 4;

			if(header.ddspf.dwFourCC == DDS10_FOUR_CC)
			{
				byteOffset += sizeof(dds10Header);
			}

			return byteOffset;
		}

		size_t GetImageByteSize(const UncheckedImageFormat &fmt, const glimg::Dimensions &dims,
			int mipmapLevel);

		//Computes the bytesize of a single scanline of an image of the given format,
		//with the given line width.
		//For compressed textures, the value returned is the number of bytes for every
		//4 scanlines.
		size_t CalcLineSize(const UncheckedImageFormat &fmt, int lineWidth)
		{
			//This is from the DDS suggestions for line size computations.
			if(fmt.eBitdepth == BD_COMPRESSED)
			{
				size_t blockSize = 16;

				if(fmt.eType == DT_COMPRESSED_BC1 ||
					fmt.eType == DT_COMPRESSED_UNSIGNED_BC4 || fmt.eType == DT_COMPRESSED_SIGNED_BC4)
					blockSize = 8;

				return ((lineWidth + 3) / 4) * blockSize;
			}

			size_t bytesPerPixel = CalcBytesPerPixel(fmt);
			return lineWidth * bytesPerPixel;
		}

		size_t CalcMipmapSize( const glimg::Dimensions & dims, int currLevel, const UncheckedImageFormat &fmt)
		{
			glimg::Dimensions mipmapDims = ModifySizeForMipmap(dims, currLevel);

			size_t lineSize = CalcLineSize(fmt, mipmapDims.width);

			int effectiveHeight = 1;
			if(mipmapDims.numDimensions > 1)
			{
				effectiveHeight = mipmapDims.height;
				if(fmt.eBitdepth == BD_COMPRESSED)
					effectiveHeight = (effectiveHeight + 3) / 4;
			}

			int effectiveDepth = 1;
			if(mipmapDims.numDimensions > 2)
			{
				effectiveDepth = mipmapDims.depth;
				if(fmt.eBitdepth == BD_COMPRESSED)
					effectiveDepth = (effectiveDepth + 3) / 4;
			}

			int numLines = effectiveHeight * effectiveDepth;
			return numLines * lineSize;
		}

		//Takes ownership of ddsData;
		ImageSet *ProcessDDSData(FileBuffer &ddsData, const std::string &filename = std::string())
		{
			//Check the first 4 bytes.
			unsigned int magicTest = 0;
			memcpy(&magicTest, &ddsData[0], 4);
			if(magicTest != DDS_MAGIC_NUMBER)
				throw DdsFileMalformedException(filename, "The Magic number is missing from the file.");

			if(ddsData.size() < sizeof(ddsHeader) + 4)
				throw DdsFileMalformedException(filename, "The data is way too small to store actual information.");

			//Now, get a DDS header.
			ddsHeader header;
			memcpy(&header, &ddsData[4], sizeof(ddsHeader));

			ThrowIfHeaderInvalid(header);

			//Collect info from the DDS file.
			dds10Header header10 = GetDDS10Header(header, ddsData);
			glimg::Dimensions dims = GetDimensions(header, header10);
			UncheckedImageFormat fmt = GetImageFormat(header, header10);

			int numMipmaps = 0;
			int numArrays = 0;
			int numFaces = 0;
			GetImageCounts(numArrays, numMipmaps, numFaces, header, header10);

			const size_t baseOffset = GetByteOffsetToData(header);

			//TODO: support array textures
			//Build the image creator. No more exceptions, except for those thrown by.
			//the ImageCreator.
			ImageCreator imgCreator(fmt, dims, numMipmaps, numArrays, numFaces);
			size_t cumulativeOffset = baseOffset;
			for(int arrayIx = 0; arrayIx < numArrays; arrayIx++)
			{
				for(int faceIx = 0; faceIx < numFaces; faceIx++)
				{
					for(int mipmapLevel = 0; mipmapLevel < numMipmaps; mipmapLevel++)
					{
						imgCreator.SetImageData(&ddsData[0] + cumulativeOffset,
							true, mipmapLevel, arrayIx, faceIx);
						cumulativeOffset += CalcMipmapSize(dims, mipmapLevel, fmt);
					}
				}
			}
			return imgCreator.CreateImage();
		}
	}

	ImageSet * LoadFromFile( const std::string &filename )
	{
		//Load the file.
		FILE *pFile = fopen(filename.c_str(),"rb");
		if(!pFile)
			throw DdsFileNotFoundException(filename);

		fseek(pFile, 0, SEEK_END);
		long int fileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		FileBuffer fileData;
		fileData.reserve(fileSize);
		fileData.resize(fileSize);

		fread(&fileData[0], fileSize, 1, pFile);
		fclose(pFile);

		return ProcessDDSData(fileData, filename);
	}

	ImageSet * LoadFromMemory( const unsigned char *buffer, size_t bufSize )
	{
		FileBuffer fileData(buffer, buffer + bufSize);

		return ProcessDDSData(fileData);
	}
}
}
}
