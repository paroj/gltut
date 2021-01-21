/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/


#ifndef GLIMG_TEXTURE_GENERATOR_H
#define GLIMG_TEXTURE_GENERATOR_H

/**
\file
\brief Functions for generating textures and OpenGL-specific information.

**/


#include "ImageSet.h"
#include "TextureGeneratorExceptions.h"


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
		FORCE_LUMINANCE_FMT			= 0x0008,	///<Red and RG textures will become luminance and luminance/alpha textures in all cases. Exceptions will be thrown if the GL implementation does not support those luminance/alpha formats (ie: is core).

//Not supported yet.
//		FORCE_REQUIRED_FMT			= 0x0010,	///<Will only get image formats that are required to exist by OpenGL.
		FORCE_INTEGRAL_FMT			= 0x0020,	///<Image formats that contain normalized integers will be uploaded as non-normalized integers. Ignored for floating-point or compressed formats.
		FORCE_SIGNED_FMT			= 0x0040,	///<Image formats that contain unsigned integers will be uploaded as signed integers. Ignored if the format is not an integer/integral format, or if it isn't BC4 or BC5 compressed.
		FORCE_COLOR_RENDERABLE_FMT	= 0x0080,	///<NOT YET SUPPORTED! Will force the use of formats that are required to be valid render targets. This will add components if necessary, but it will throw if conversion would require fundamentally changing the basic format (from signed to unsigned, compressed textures, etc).

		FORCE_ARRAY_TEXTURE			= 0x0004,	///<NOT YET SUPPORTED! The texture will be an array texture even if the depth is not present. Ignored for formats that can't be arrays. Will throw if array textures of that type are not supported (ie: cubemap arrays, 2D arrays for lesser hardware, etc).
		USE_TEXTURE_STORAGE			= 0x0100,	///<If ARB_texture_storage or GL 4.2 is available, then texture storage functions will be used to create the textures. Otherwise regular glTex* functions will be used.
		FORCE_TEXTURE_STORAGE		= 0x0200,	///<If ARB_texture_storage or GL 4.2 is available, then texture storage functions will be used to create the textures. Otherwise, an exception will be thrown.
		USE_DSA						= 0x0400,	///<If EXT_direct_state_access is available, then DSA functions will be used to create the texture. Otherwise, regular ones will be used.
		FORCE_DSA					= 0x0800,	///<If EXT_direct_state_access is available, then DSA functions will be used to create the texture. Otherwise, an exception will be thrown.
	};

	/**
	\brief Retrieves the OpenGL internal format for the given image format and bits.

	This function should be used when you want to do the uploading of the texture data
	yourself.
	It returns the [internal format](http://www.opengl.org/wiki/Image_Format) to use for a particular image format and
	conversion bits.
	
	\note This function requires an active OpenGL context, and it requires
	that the [GL Load](@ref module_glload) has been initialized. It will only return internal formats
	supported by the current OpenGL context. It will use version numbers, core vs. compatibility,
	and so forth to detect this.
	
	Format mapping is done as follows. One and two channel glimg::PixelComponents
	(`RED` and `RG`) will be mapped to luminance and luminance alpha \em only if
	the OpenGL context doesn't support `GL_RED` and `GL_RG` textures. Both the
	EXT extension and the version number will be checked to verify the
	availability of the feature.
	
	Similarly, if you use `FORCE_LUMINANCE_FMT` on a core context, this function will
	throw.

	\param format The image format of the image data to have a texture created for it.
	\param forceConvertBits A bitfield containing values from ForcedConvertFlags.
	These affect how the format is generated.

	\return A `GLenum` representing the internal OpenGL format.

	\throws TextureUnsupportedException The type of texture that was asked to be created cannot be created
	because the OpenGL implementation doesn't support that kind of texture.
	\throws CannotForceRenderTargetException Only given if `FORCE_COLOR_RENDERABLE_FMT` is set and
	a color renderable format cannot be found that is appropriate.
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

	This function should be used if you wish to manually upload image data to OpenGL. It returns the
	pixel transfer parameters for uploading the data.

	\note This function requires an active OpenGL context, and it requires
	that \ref module_glload "GLLoad" has been initialized. It will only return pixel transfer
	parameters supported by the current OpenGL context.

	Here is an example of how to use this function:

	\code
glimg::ImageSet *pImgSet = ...;
glimg::SingleImage *pImage = pImgSet->GetImage(0);
OpenGLPixelTransferParams params = GetUploadFormatType(pImage->GetFormat(), 0);
glimg::Dimensions dims = pImage->GetDimensions();
glPixelStorei(GL_UNPACK_ALIGNMENT, pImage->GetFormat().LineAlign());
glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dims.width, dims.height,
	params.format, params.height, pImage->GetImageData());
	\endcode

	\param format The image format of the image data to have a texture created for it.
	\param forceConvertBits A bitfield containing values from glimg::ForcedConvertFlags. These
	affect how the format is generated.

	\return The OpenGL pixel transfer parameters, and a compressed block size field.

	\throws TextureUnsupportedException The type of texture that was asked to be created cannot be created
	because the OpenGL implementation doesn't support that kind of texture.
	\throws CannotForceRenderTargetException Only given if `FORCE_COLOR_RENDERABLE_FMT` is set and
	a color renderable format cannot be found that is appropriate.
	**/
	OpenGLPixelTransferParams GetUploadFormatType(const ImageFormat &format, unsigned int forceConvertBits);

	/**
	\brief Retrieves the texture type for the given ImageSet.

	When the glimg::CreateTexture functions are called, they will create a texture with a specific
	texture type. This is the target that the texture is bound to the context with, and this
	information is baked into the texture object. It is vital to know what this type will actually
	be, so that the texture object can be properly bound to the context.

	This function will return the texture target that glimg::CreateTexture will create, given
	\em exactly the same parameters as glimg::CreateTexture.

	\param pImage The image that would be uploaded in a glimg::CreateTexture call.
	\param forceConvertBits A bitfield containing values from glimg::ForcedConvertFlags.

	\return A GLenum for the texture type for a texture that would be created by glimg::CreateTexture.
	**/
	unsigned int GetTextureType(const ImageSet *pImage, unsigned int forceConvertBits);

	/**
	\brief Creates a texture object from the given ImageSet, with flags.

	If an exception is thrown, no OpenGL state will be changed. If a texture was created with
	glGenTextures before the exception was thrown, it will be deleted with glDeleteTextures
	after. So this function should be completely exception safe.

	\note This function requires an active OpenGL context, and it requires
	that [GLLoad(@ref module_glload) has been initialized.

	If an exception is not thrown, then the following OpenGL context state will be changed:

	\li [All `GL_UNPACK_*` state](http://www.opengl.org/wiki/Pixel_Transfer#Pixel_transfer_parameters).
	\li The current texture unit for the texture target of the returned texture (as determined by glimg::GetTextureType) will have texture object 0 bound to it.

	If you pass the `USE_DSA` or `FORCE_DSA` flags, and your implementation supports
	GL_EXT_direct_state_access, then the only state that will be changed are the `GL_UNPACK_*`
	state.

	\param pImage The image to upload to OpenGL.
	\param forceConvertBits A bitfield containing values from ForcedConvertFlags.

	\return The created texture. The texture returned will always be texture-complete,
	with the proper base and max mipmap level set, and reasonable filtering parameters
	set on it.

	\throws ImageFormatUnsupportedException The given ImageFormat cannot be used because the OpenGL
	implementation doesn't support the functionality necessary to use it.
	\throws TextureUnsupportedException The type of texture that was asked to be created cannot be created
	because the OpenGL implementation doesn't support that kind of texture.
	\throws TextureUnexpectedException The type of texture has not been implemented in GL Image.
	Appologies for that.
	\throws CannotForceRenderTargetException Only given if `FORCE_COLOR_RENDERABLE_FMT` is set and
	a color renderable format cannot be found that is appropriate.
	\throws CannotForceTextureStorage Only given if `FORCE_TEXTURE_STORAGE` is set and the OpenGL
	implementation does not implement GL 4.2 or the GL_ARB_texture_storage extension.
	\throws CannotForceDSAUsage Only given if `FORCE_DSA` is set, and the OpenGL implementation
	does not implement GL_EXT_direct_state_access.
	**/
	unsigned int CreateTexture(const ImageSet *pImage, unsigned int forceConvertBits);

	/**
	\brief As CreateTexture(const ImageSet *, unsigned int), but with a texture object provided by the user.
	
	The given texture object \em must not have been used at all. You cannot even have
	bound it to the OpenGL context once. It should be fresh from `glGenTextures`.

	\throws ... Everything that CreateTexture(const ImageSet *, unsigned int) throws.
	**/
	void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits);
	///@}
}



#endif //GLIMG_TEXTURE_GENERATOR_H
