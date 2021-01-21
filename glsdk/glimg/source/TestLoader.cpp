//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <vector>
#include "glimg/ImageSet.h"
#include "ImageSetImpl.h"
#include "glimg/TestLoader.h"
#include "glimg/ImageCreator.h"

namespace
{
	const int TEST_WIDTH = 16;
	const int TEST_HEIGHT = 16;
}

glimg::ImageSet *glimg::loaders::test::TestImage2D()
{
	ImageBuffer pixelData(TEST_WIDTH*TEST_HEIGHT*4, 128);

	//Fill in the data.
	for(int xLoc = 0; xLoc < TEST_WIDTH/2; xLoc++)
	{
		for(int yLoc = 0; yLoc < TEST_HEIGHT/2; yLoc++)
		{
			int index = (yLoc * TEST_WIDTH + xLoc) * 4;
			pixelData[index + 0] = 255;
			pixelData[index + 1] = 0;
			pixelData[index + 2] = 0;
			pixelData[index + 3] = 255;

			index = (yLoc * TEST_WIDTH + (xLoc + TEST_WIDTH/2)) * 4;
			pixelData[index + 0] = 0;
			pixelData[index + 1] = 128;
			pixelData[index + 2] = 0;
			pixelData[index + 3] = 255;

			index = ((yLoc + TEST_HEIGHT/2) * TEST_WIDTH + xLoc) * 4;
			pixelData[index + 0] = 128;
			pixelData[index + 1] = 128;
			pixelData[index + 2] = 255;
			pixelData[index + 3] = 255;

			index = ((yLoc + TEST_HEIGHT/2) * TEST_WIDTH + (xLoc + TEST_WIDTH/2)) * 4;
			pixelData[index + 0] = 192;
			pixelData[index + 1] = 192;
			pixelData[index + 2] = 192;
			pixelData[index + 3] = 255;
		}
	}

	//Make an image creator and create the image.
	Dimensions dims;
	dims.numDimensions = 2;
	dims.depth = 0;
	dims.width = TEST_WIDTH;
	dims.height = TEST_HEIGHT;

	UncheckedImageFormat fmt;
	fmt.eType = DT_NORM_UNSIGNED_INTEGER;
	fmt.eFormat = FMT_COLOR_RGBA;
	fmt.eOrder = ORDER_RGBA;
	fmt.eBitdepth = BD_PER_COMP_8;
	fmt.lineAlignment = 1;

	ImageCreator imgCreator(fmt, dims, 1, 1, 1);

	imgCreator.SetFullMipmapLevel(&pixelData[0], false, 0);

	return imgCreator.CreateImage();
}

