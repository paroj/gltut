#ifndef GLIMG_TEXTURE_GENERATOR_H
#define GLIMG_TEXTURE_GENERATOR_H

#include "ImageSet.h"


namespace glimg
{
	enum ForcedConvertBits
	{
		FORCE_SRGB_COLORSPACE		= 0x0001,	///<When possible, will force the format to use the sRGB colorspace. Does not cause erroring for formats that can't be sRGB, unless your GL implementation doesn't support sRGB.
		FORCE_BC1_ALPHA_TEXTURE		= 0x0002,	///<When used with a BC1 texture, will force the texture to have an alpha.
		FORCE_ARRAY_TEXTURE			= 0x0004,	///<The texture will be an array texture even if the depth is one. Ignored for formats that can't be arrays. Will throw if array textures of that type are not supported (ie: cubemap arrays, 2D arrays for lesser hardware, etc).
		FORCE_LUMINANCE_FORMATS		= 0x0008,	///<Red and RG textures will become luminance and luminance/alpha textures in all cases. Exceptions will be thrown if the GL implementation does not support those luminance/alpha formats.

		FORCE_REQUIRED_FORMATS		= 0x0010,	///<Will only get image formats that are required to exist by OpenGL.
		FORCE_INTEGRAL_FORMAT		= 0x0020,	///<Integer textures are considered integral.
		FORCE_SIGNED_FORMAT			= 0x0040,	///<Unsigned integer textures are considered signed integers.
		FORCE_COLOR_RENDERABLE		= 0x0080,	///<Will force the use of formats that are required to be valid render targets. This will add components if necessary, but it will throw if conversion would require fundamentally changing the basic format (from signed to unsigned, compressed textures, etc).
	};

	unsigned int GetInternalFormat(const ImageFormat &format, unsigned int forceConvertBits);

	struct OpenGLUploadData
	{
		unsigned int format;
		unsigned int type;
		unsigned int blockByteCount;
	};

	OpenGLUploadData GetUploadFormatType(const ImageFormat &format, unsigned int forceConvertBits);

	//Will not change OpenGL state in the event of an exception.
	//Will always return a texture-complete texture.
	unsigned int CreateTexture(const ImageSet *pImage, unsigned int forceConvertBits);
	void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
}



#endif //GLIMG_TEXTURE_GENERATOR_H
