#ifndef GLIMG_TEXTURE_GENERATOR_H
#define GLIMG_TEXTURE_GENERATOR_H

/**
\file
\brief Functions for generating textures and OpenGL-specific information.

**/


#include "ImageSet.h"


namespace glimg
{
	///\addtogroup module_glimg_texture
	///@{

	/**
	\brief Control flags for texture conversion processes.

	These flags allow the user to alter the process used to select image formats and upload
	texture data. The enumerators that end in "FMT" affect how the format is chosen, while
	the ones ending in "TEX" affect the texture choice.
	
	\todo Finish implementing color renderable forcing.
	\todo Implement the forcing of required formats.
	**/
	enum ForcedConvertFlags
	{
		FORCE_SRGB_COLORSPACE_FMT	= 0x0001,	///<When possible, will force the format to use the sRGB colorspace. Does not cause erroring for formats that can't be sRGB, unless your GL implementation doesn't support sRGB.
		FORCE_BC1_ALPHA_FMT			= 0x0002,	///<When used with a BC1 texture, will force the texture to have an alpha. Ignored otherwise.
		FORCE_ARRAY_TEXTURE			= 0x0004,	///<NOT YET SUPPORTED! The texture will be an array texture even if the depth is not present. Ignored for formats that can't be arrays. Will throw if array textures of that type are not supported (ie: cubemap arrays, 2D arrays for lesser hardware, etc).
		FORCE_LUMINANCE_FMT			= 0x0008,	///<Red and RG textures will become luminance and luminance/alpha textures in all cases. Exceptions will be thrown if the GL implementation does not support those luminance/alpha formats (ie: is core).

//Not supported yet.
//		FORCE_REQUIRED_FMT			= 0x0010,	///<Will only get image formats that are required to exist by OpenGL.
		FORCE_INTEGRAL_FMT			= 0x0020,	///<Image formats that contain normalized integers will be uploaded as non-normalized integers.
		FORCE_SIGNED_FMT			= 0x0040,	///<Image formats that contain unsigned integers will be uploaded as signed integers.
		FORCE_COLOR_RENDERABLE_FMT	= 0x0080,	///<NOT YET SUPPORTED! Will force the use of formats that are required to be valid render targets. This will add components if necessary, but it will throw if conversion would require fundamentally changing the basic format (from signed to unsigned, compressed textures, etc).
	};

	/**
	\brief Retrieves the OpenGL internal format for the given image format and bits.

	This function should be used when you want to do the uploading of the texture data
	yourself.

	\param format The image format of the image data to have a texture created for it.
	\param forceConvertBits A bitfield containing values from ForcedConvertFlags. These affect how the format is generated.

	\return A GLenum representing the internal OpenGL format.

	\throws TextureGenerationException If the format is invalid, or if the format cannot be used.
	Also thrown if the format isn't supported yet. This is a base class; the various derived
	classes of this type are thrown for specific errors.
	**/
	unsigned int GetInternalFormat(const ImageFormat &format, unsigned int forceConvertBits);

	/**
	\brief Contains the pixel transfer parameters for OpenGL texture upload functions.
	**/
	struct OpenGLPixelTransferParams
	{
		unsigned int format;			///<The GLenum format value of pixel transfer operations.
		unsigned int type;				///<The GLenum type value of pixel transfer operations.
		unsigned int blockByteCount;	///<The size in bytes for blocks in compressed formats. Necessary to compute the size of the pixel data.
	};

	/**
	\brief Retrieves the pixel transfer parameters for the given image format.

	This function should be used if you wish to manually upload image data to OpenGL.
	
	\param format The image format of the image data to have a texture created for it.
	\param forceConvertBits A bitfield containing values from ForcedConvertFlags. These affect how the format is generated.

	\return The OpenGL pixel transfer parameters, and a compressed block size field.

	\throws TextureGenerationException If the format is invalid, or if the format cannot be used.
	Also thrown if the format isn't supported yet. This is a base class; the various derived
	classes of this type are thrown for specific errors.
	**/
	OpenGLPixelTransferParams GetUploadFormatType(const ImageFormat &format, unsigned int forceConvertBits);

	/**
	\brief Creates a texture object from the given ImageSet, with flags.

	If an exception is thrown, no OpenGL state will be changed. If a texture was created with
	glGenTextures before the exception was thrown, it will be deleted with glDeleteTextures
	after. So this function should be completely exception safe.
	
	If an exception is not thrown, then the following OpenGL context state will be changed:

	\li All GL_UNPACK state.
	\li The texture target of the returned texture will have no texture object bound to it.

	\param pImage The image to upload to OpenGL.
	\param forceConvertBits A bitfield containing values from ForcedConvertFlags.

	\return The created texture. The texture returned will always be texture-complete,
	with the proper base and max mipmap level set, and reasonable filtering parameters
	set on it.

	\throws TextureGenerationException If the format is invalid, or if the format cannot be used.
	Also thrown if the format isn't supported yet. This is a base class; the various derived
	classes of this type are thrown for specific errors.
	**/
	unsigned int CreateTexture(const ImageSet *pImage, unsigned int forceConvertBits);

	/**
	\brief As CreateTexture(const ImageSet *, unsigned int), but with a texture object provided by the user.
	
	The given texture object \em must not have been used at all. You cannot even have
	bound it to the OpenGL context once. It should be fresh from glGenTextures.

	\throws TextureGenerationException If the format is invalid, or if the format cannot be used.
	Also thrown if the format isn't supported yet. This is a base class; the various derived
	classes of this type are thrown for specific errors.
	**/
	void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
	///@}
}



#endif //GLIMG_TEXTURE_GENERATOR_H
