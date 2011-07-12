
#include "glimg/ImageSet.h"

namespace glimg
{
	Dimensions ModifySizeForMipmap(Dimensions origDim, int mipmapLevel);

	//Does not work for compressed textures.
	size_t CalcBytesPerPixel(const ImageFormat &fmt);

	int ComponentCount(PixelComponents eFormat);
}