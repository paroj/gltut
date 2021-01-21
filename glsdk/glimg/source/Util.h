/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#include "glimg/ImageSet.h"

namespace glimg
{
	Dimensions ModifySizeForMipmap(Dimensions origDim, int mipmapLevel);

	//Does not work for compressed textures.
	size_t CalcBytesPerPixel(const ImageFormat &fmt);

	struct CompressedBlockData
	{
		//The dimensionality of a block.
		Dimensions dims;

		//Number of bytes in a block.
		size_t byteCount;
	};

	CompressedBlockData GetBlockCompressionData(PixelDataType eType);

	//Works for all texture formats.
	size_t CalcImageByteSize(const ImageFormat &fmt, const Dimensions &dims);

	int ComponentCount(PixelComponents eFormat);
}