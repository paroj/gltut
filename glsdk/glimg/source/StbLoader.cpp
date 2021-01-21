//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include "stb_image.h"
#include "glimg/ImageSet.h"
#include "ImageSetImpl.h"
#include "glimg/StbLoader.h"
#include "glimg/ImageCreator.h"


namespace glimg
{
	namespace
	{
		ImageSet *BuildImageSetFromIntegerData(const unsigned char *pixelData,
			int width, int height, int numComp)
		{
			Dimensions dims;
			dims.numDimensions = 2;
			dims.depth = 0;
			dims.width = width;
			dims.height = height;

			UncheckedImageFormat fmt;
			fmt.eType = DT_NORM_UNSIGNED_INTEGER;
			switch(numComp)
			{
			case 1:
				fmt.eFormat = FMT_COLOR_RED;
				break;
			case 2:
				fmt.eFormat = FMT_COLOR_RG;
				break;
			case 3:
				fmt.eFormat = FMT_COLOR_RGB;
				break;
			case 4:
				fmt.eFormat = FMT_COLOR_RGBA;
				break;
			}
			fmt.eOrder = ORDER_RGBA;
			fmt.eBitdepth = BD_PER_COMP_8;
			fmt.lineAlignment = 1;

			ImageCreator imgCreator(fmt, dims, 1, 1, 1);
			imgCreator.SetImageData(pixelData, true, 0, 0, 0);
			return imgCreator.CreateImage();
		}
	}

	ImageSet * loaders::stb::LoadFromFile( const std::string &filename )
	{
		int width = 0;
		int height = 0;
		int numComp = 0;

		unsigned char *pixelData = stbi_load(filename.c_str(), &width, &height, &numComp, 0);

		if(!pixelData)
			throw UnableToLoadException(filename);

		ImageSet *pImageSet = NULL;

		try
		{
			pImageSet = BuildImageSetFromIntegerData(pixelData, width, height, numComp);
		}
		catch(...)
		{
			stbi_image_free(pixelData);
			throw;
		}

		stbi_image_free(pixelData);
		return pImageSet;
	}

	ImageSet * loaders::stb::LoadFromMemory( const unsigned char *buffer, size_t bufSize )
	{
		int width = 0;
		int height = 0;
		int numComp = 0;

		unsigned char *pixelData = stbi_load_from_memory(buffer, (int)bufSize,
			&width, &height, &numComp, 0);

		if(!pixelData)
			throw UnableToLoadException();

		ImageSet *pImageSet = NULL;

		try
		{
			pImageSet = BuildImageSetFromIntegerData(pixelData, width, height, numComp);
		}
		catch(...)
		{
			stbi_image_free(pixelData);
			throw;
		}

		stbi_image_free(pixelData);
		return pImageSet;
	}
}



