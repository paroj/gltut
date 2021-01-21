//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <assert.h>
#include <glload/gl_all.hpp>
#include <glload/gl_load.hpp>
#include "glimg/TextureGeneratorExceptions.h"
#include "glimg/TextureGenerator.h"
#include "ImageSetImpl.h"
#include "Util.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glimg
{
	//////////////////////////////////////////////////////////////////////////
	/// INTERNAL FORMAT
	namespace
	{
		void ThrowIfS3TCNotSupported()
		{
			if(!gl::exts::var_EXT_texture_compression_s3tc)
				throw ImageFormatUnsupportedException("S3TC not supported.");
		}

		void ThrowIfLATCNotSupported()
		{
			if(!gl::exts::var_EXT_texture_compression_latc)
				throw ImageFormatUnsupportedException("LATC not supported.");
		}

		void ThrowIfRGTCNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!(gl::exts::var_ARB_texture_compression_rgtc || gl::exts::var_EXT_texture_compression_rgtc))
					throw ImageFormatUnsupportedException("RGTC, part of GL 3.0 and above, is not supported.");
			}
		}

		void ThrowIfBPTCNotSupported()
		{
			if(!gl::exts::var_ARB_texture_compression_bptc)
				throw ImageFormatUnsupportedException("PBTC not supported.");
		}

		void ThrowIfSRGBNotSupported()
		{
			if(!glload::IsVersionGEQ(2, 1))
			{
				if(!gl::exts::var_EXT_texture_sRGB)
					throw ImageFormatUnsupportedException("sRGB textures not supported.");
			}
		}

		void ThrowIfEXT_SRGBNotSupported()
		{
				if(!gl::exts::var_EXT_texture_sRGB)
					throw ImageFormatUnsupportedException("sRGB and S3TC textures not supported.");
		}

		void ThrowIfSharedExpNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_EXT_texture_shared_exponent)
					throw ImageFormatUnsupportedException("Shared exponent texture format not supported.");
			}
		}

		void ThrowIfFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_ARB_texture_float)
					throw ImageFormatUnsupportedException("Float textures not supported.");
			}
		}

		void ThrowIfEXT_FloatNotSupported()
		{
			if(!gl::exts::var_ARB_texture_float)
				throw ImageFormatUnsupportedException("ARB Float textures not supported.");
		}

		void ThrowIfHalfFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_ARB_half_float_pixel)
					throw ImageFormatUnsupportedException("Half floats textures not supported.");
			}
		}

		void ThrowIfSnormNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 1))
			{
				if(!gl::exts::var_EXT_texture_snorm)
					throw ImageFormatUnsupportedException("Signed normalized textures not supported.");
			}
		}

		void ThrowIfEXT_SnormNotSupported()
		{
			if(!gl::exts::var_EXT_texture_snorm)
				throw ImageFormatUnsupportedException("Signed normalized texture extension not supported.");
		}

		void ThrowIfPackedFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_EXT_packed_float)
					throw ImageFormatUnsupportedException("Packed 11, 11, 10 float textures not supported.");
			}
		}
		
		void ThrowIfIntegralNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_EXT_texture_integer)
					throw ImageFormatUnsupportedException("Integral textures not supported.");
			}
		}

		void ThrowIfEXT_IntegralNotSupported()
		{
			if(!gl::exts::var_EXT_texture_integer)
				throw ImageFormatUnsupportedException("Integral texture extension not supported.");
		}

		void ThrowIfRGNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_ARB_texture_rg)
					throw ImageFormatUnsupportedException("RG textures not supported.");
			}
		}

		void ThrowIfLANotSupported()
		{
			if(!glload::IsVersionGEQ(3,0))
				return;
			if(!glload::IsVersionGEQ(3,2))
			{
				if(!gl::exts::var_ARB_compatibility)
					throw ImageFormatUnsupportedException("Core OpenGL contexts cannot use Luminance/alpha.");
			}
			else
			{
				GLint profileMask = 0;
				gl::GetIntegerv(gl::CONTEXT_PROFILE_MASK, &profileMask);
				if(profileMask & gl::CONTEXT_CORE_PROFILE_BIT)
					throw ImageFormatUnsupportedException("Core OpenGL contexts cannot use Luminance/alpha.");
			}
		}

		void ThrowIfForceRendertarget(unsigned int forceConvertBits)
		{
			if(forceConvertBits & FORCE_COLOR_RENDERABLE_FMT)
				throw CannotForceRenderTargetException();
		}

		void ThrowIfDepthNotSupported()
		{
			if(!glload::IsVersionGEQ(1, 4)) //Yes, really. Depth textures are old.
			{
				if(!gl::exts::var_ARB_depth_texture)
					throw ImageFormatUnsupportedException("Depth textures not supported.");
			}
		}

		void ThrowIfDepthStencilNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!(gl::exts::var_EXT_packed_depth_stencil || gl::exts::var_ARB_framebuffer_object))
					throw ImageFormatUnsupportedException("Depth/stencil textures not supported.");
			}
		}

		void ThrowIfDepthFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_NV_depth_buffer_float)
					throw ImageFormatUnsupportedException("Floating-point depth buffers not supported.");
			}
		}

		template<int arrayCount, typename TestType>
		bool IsOneOfThese(TestType testValue, TestType *testArray)
		{
			for(int loop = 0; loop < arrayCount; loop++)
			{
				if(testValue == testArray[loop])
					return true;
			}

			return false;
		}

		int ComponentCount(const ImageFormat &format, unsigned int forceConvertBits)
		{
			//TODO: Forceconv.
			PixelComponents twoCompFormats[] = {FMT_COLOR_RG, FMT_DEPTH_X};
			PixelComponents threeCompFormats[] = {FMT_COLOR_RGB, FMT_COLOR_RGB_sRGB};
			PixelComponents fourCompFormats[] = {FMT_COLOR_RGBX, FMT_COLOR_RGBA,
				FMT_COLOR_RGBX_sRGB, FMT_COLOR_RGBA_sRGB};

			if(IsOneOfThese<ARRAY_COUNT(twoCompFormats)>(format.Components(), twoCompFormats))
				return 2;

			if(IsOneOfThese<ARRAY_COUNT(threeCompFormats)>(format.Components(), threeCompFormats))
				return 3;

			if(IsOneOfThese<ARRAY_COUNT(fourCompFormats)>(format.Components(), fourCompFormats))
				return 4;

			return 1;
		}

		int PerComponentSize(const ImageFormat &format, unsigned int forceConvertBits)
		{
			//TODO: Forceconv.
			switch(format.Depth())
			{
			case BD_PER_COMP_8: return 8;
			case BD_PER_COMP_16: return 16;
			case BD_PER_COMP_32: return 32;
			default:
				return -1;
			}
		}

		bool IsSRGBFormat(const ImageFormat &format, unsigned int forceConvertBits)
		{
			PixelComponents srgbFormats[] = {FMT_COLOR_RGB_sRGB, FMT_COLOR_RGBX_sRGB, FMT_COLOR_RGBA_sRGB};
			if(IsOneOfThese<ARRAY_COUNT(srgbFormats)>(format.Components(), srgbFormats))
				return true;

			if(!(forceConvertBits & FORCE_SRGB_COLORSPACE_FMT))
				return false;

			PixelDataType srgbTypes[] = {DT_NORM_UNSIGNED_INTEGER,
				DT_COMPRESSED_BC1, DT_COMPRESSED_BC2, DT_COMPRESSED_BC3, DT_COMPRESSED_BC7};

			if(IsOneOfThese<ARRAY_COUNT(srgbTypes)>(format.Type(), srgbTypes))
			{
				if(format.Type() != DT_NORM_UNSIGNED_INTEGER)
					return true;
			}
			else
				return false;

			//unsigned normalized integers. Check for RGB or RGBA components.
			PixelComponents convertableFormats[] = {FMT_COLOR_RGB, FMT_COLOR_RGBX, FMT_COLOR_RGBA};
			if(IsOneOfThese<ARRAY_COUNT(convertableFormats)>(format.Components(), convertableFormats))
				return true;

			return false;
		}

		bool FormatHasAlpha(const ImageFormat &format, unsigned int forceConvertBits)
		{
			//TODO: Forceconv. Check for color renderable.
			PixelComponents alphaFormats[] = {FMT_COLOR_RGBA, FMT_COLOR_RGBA_sRGB};
			if(IsOneOfThese<ARRAY_COUNT(alphaFormats)>(format.Components(), alphaFormats))
				return true;

			return false;
		}

		bool UseLAInsteadOfRG(unsigned int forceConvertBits)
		{
			if(forceConvertBits & FORCE_LUMINANCE_FMT)
				return true;

			try
			{
				ThrowIfRGNotSupported();
			}
			catch(TextureGenerationException &)
			{
				return true;
			}

			return false;
		}

		PixelDataType GetDataType(const ImageFormat &format, unsigned int forceConvertBits)
		{
			bool bForceIntegral = (forceConvertBits & FORCE_INTEGRAL_FMT) != 0;
			bool bForceSigned = (forceConvertBits & FORCE_SIGNED_FMT) != 0;
			if(!bForceIntegral && !bForceSigned)
				return format.Type();

			switch(format.Type())
			{
			case DT_NORM_UNSIGNED_INTEGER:
				if(bForceIntegral)
				{
					if(bForceSigned)
						return DT_SIGNED_INTEGRAL;
					else
						return DT_UNSIGNED_INTEGRAL;
				}
				else
				{
					if(bForceSigned)
						return DT_NORM_SIGNED_INTEGER;
				}
				break;
			case DT_NORM_SIGNED_INTEGER:
				if(bForceIntegral)
					return DT_SIGNED_INTEGRAL;
				break;
			case DT_UNSIGNED_INTEGRAL:
				if(bForceSigned)
					return DT_SIGNED_INTEGRAL;
				break;
			case DT_COMPRESSED_UNSIGNED_BC4:
				if(bForceSigned)
					return DT_COMPRESSED_SIGNED_BC4;
			case DT_COMPRESSED_UNSIGNED_BC5:
				if(bForceSigned)
					return DT_COMPRESSED_SIGNED_BC5;
				break;
			}

			return format.Type();
		}

		//Ordered by BaseDataFormat*2. The first is 16-bit, the second is 32-bit.
		GLenum g_floatFormats[] =
		{
			gl::R16F,
			gl::R32F,
			gl::RG16F,
			gl::RG32F,
			gl::RGB16F,
			gl::RGB32F,
			gl::RGB16F,
			gl::RGB32F,
			gl::RGBA16F,
			gl::RGBA32F,
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//16-bit float depth buffer. 
			gl::DEPTH_COMPONENT32F,
			0,			//UNorm+stencil.
		};

		//Ordered by number of components * size (8, 16, 32=>0, 1, 2).
		GLenum g_signIntegralFormats[] =
		{
			gl::R8I,			gl::R16I,			gl::R32I,
			gl::RG8I,		gl::RG16I,			gl::RG32I,
			gl::RGB8I,		gl::RGB16I,			gl::RGB32I,
			gl::RGBA8I,		gl::RGBA16I,			gl::RGBA32I,
		};

		//Ordered by number of components * size (8, 16, 32=>0, 1, 2).
		GLenum g_unsignIntegralFormats[] =
		{
			gl::R8UI,		gl::R16UI,			gl::R32UI,
			gl::RG8UI,		gl::RG16UI,			gl::RG32UI,
			gl::RGB8UI,		gl::RGB16UI,			gl::RGB32UI,
			gl::RGBA8UI,		gl::RGBA16UI,		gl::RGBA32UI,
		};

		//Ordered by number of components * size (8, 16=>0, 1, 2).
		GLenum g_signedNormFormats[] =
		{
			gl::R8_SNORM,		gl::R16_SNORM,
			gl::RG8_SNORM,		gl::RG16_SNORM,
			gl::RGB8_SNORM,		gl::RGB16_SNORM,
			gl::RGBA8_SNORM,		gl::RGBA16_SNORM,
		};

		GLenum ThrowInvalidFormatIfZero(GLenum input)
		{
			if(!input)
				throw ImageFormatUnsupportedException();

			return input;
		}

		unsigned int GetStandardOpenGLFormat( const ImageFormat &format, unsigned int forceConvertBits )
		{
			PixelDataType eType = GetDataType(format, forceConvertBits);

			switch(eType)
			{
			case DT_NORM_UNSIGNED_INTEGER:
				//Only 16-bit for non Depth_x.
				if(format.Components() == FMT_DEPTH)
				{
					ThrowIfDepthNotSupported();
					return gl::DEPTH_COMPONENT16;
				}

				//Only 24x8 for this.
				if(format.Components() == FMT_DEPTH_X)
				{
					ThrowIfDepthStencilNotSupported();
					return gl::DEPTH24_STENCIL8;
				}

				//Color formats.
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfSRGBNotSupported();
					if(ComponentCount(format, forceConvertBits) == 3)
						return gl::SRGB8;
					else
						return gl::SRGB8_ALPHA8;
				}

				switch(format.Depth())
				{
				case BD_PER_COMP_8:
					{
						GLenum components[] = {gl::R8, gl::RG8, gl::RGB8, gl::RGBA8};
						int numComponents = ComponentCount(format, forceConvertBits);

						return components[numComponents - 1];
					}
				case BD_PER_COMP_16:
					{
						GLenum components[] = {gl::R16, gl::RG16, gl::RGB16, gl::RGBA16};
						int numComponents = ComponentCount(format, forceConvertBits);

						return components[numComponents - 1];
					}

				case BD_PACKED_16_BIT_565:
				case BD_PACKED_16_BIT_565_REV:
					return gl::RGB8;

				case BD_PACKED_16_BIT_5551:
				case BD_PACKED_16_BIT_1555_REV:
					return gl::RGB5_A1;

				case BD_PACKED_16_BIT_4444:
				case BD_PACKED_16_BIT_4444_REV:
					return gl::RGBA4;

				case BD_PACKED_32_BIT_8888:
				case BD_PACKED_32_BIT_8888_REV:
					return gl::RGBA8;

				case BD_PACKED_32_BIT_1010102:
				case BD_PACKED_32_BIT_2101010_REV:
					return gl::RGB10_A2;
				}

				throw ImageFormatUnsupportedException("Unisgned normalize integer doesn't match accepted bitdepths.");

			case DT_NORM_SIGNED_INTEGER:
				ThrowIfSnormNotSupported();
				ThrowIfForceRendertarget(forceConvertBits);
				{
					int numComponents = ComponentCount(format, forceConvertBits);
					int compSize = PerComponentSize(format, forceConvertBits);
					compSize /= 16; //map to 0, 1.

					int index = ((numComponents - 1) * 2) + compSize;

					return g_signedNormFormats[index];
				}

			case DT_UNSIGNED_INTEGRAL:
			case DT_SIGNED_INTEGRAL:
				ThrowIfIntegralNotSupported();
				{
					int numComponents = ComponentCount(format, forceConvertBits);
					int compSize = PerComponentSize(format, forceConvertBits);
					compSize /= 16; //map to 0, 1, 2.

					int index = ((numComponents - 1) * 3) + compSize;

					if(eType == DT_SIGNED_INTEGRAL)
						return g_signIntegralFormats[index];
					else
						return g_unsignIntegralFormats[index];
				}

			case DT_FLOAT:
				ThrowIfFloatNotSupported();
				if(format.Depth() < BD_NUM_PER_COMPONENT)
				{
					int offset = 0;
					if(format.Depth() == BD_PER_COMP_32)
						offset = 1;
					else
						ThrowIfHalfFloatNotSupported();

					if(format.Components() == FMT_DEPTH)
						ThrowIfDepthFloatNotSupported();

					return ThrowInvalidFormatIfZero(g_floatFormats[(2 * format.Components()) + offset]);
				}
				else
				{
					//Only one packed format.
					ThrowIfPackedFloatNotSupported();
					return gl::R11F_G11F_B10F;
				}

			case DT_SHARED_EXP_FLOAT:
				ThrowIfSharedExpNotSupported();
				ThrowIfForceRendertarget(forceConvertBits);
				return gl::RGB9_E5;

			case DT_COMPRESSED_BC1:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					if(forceConvertBits & FORCE_BC1_ALPHA_FMT)
						return gl::COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
					else
					{
						if(ComponentCount(format, forceConvertBits) == 3)
							return gl::COMPRESSED_SRGB_S3TC_DXT1_EXT;
						else
							return gl::COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
					}
				}
				else
				{
					if(forceConvertBits & FORCE_BC1_ALPHA_FMT)
						return gl::COMPRESSED_RGBA_S3TC_DXT1_EXT;
					else
					{
						if(ComponentCount(format, forceConvertBits) == 3)
							return gl::COMPRESSED_RGB_S3TC_DXT1_EXT;
						else
							return gl::COMPRESSED_RGBA_S3TC_DXT1_EXT;
					}
				}

			case DT_COMPRESSED_BC2:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					return gl::COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
				}
				else
					return gl::COMPRESSED_RGBA_S3TC_DXT3_EXT;

			case DT_COMPRESSED_BC3:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					return gl::COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
				}
				else
					return gl::COMPRESSED_RGBA_S3TC_DXT5_EXT;

			case DT_COMPRESSED_UNSIGNED_BC4:
				return gl::COMPRESSED_RED_RGTC1;
			case DT_COMPRESSED_SIGNED_BC4:
				return gl::COMPRESSED_SIGNED_RED_RGTC1;

			case DT_COMPRESSED_UNSIGNED_BC5:
				return gl::COMPRESSED_RG_RGTC2;
			case DT_COMPRESSED_SIGNED_BC5:
				return gl::COMPRESSED_SIGNED_RG_RGTC2;

			case DT_COMPRESSED_UNSIGNED_BC6H:
				ThrowIfBPTCNotSupported();
				return gl::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;

			case DT_COMPRESSED_SIGNED_BC6H:
				ThrowIfBPTCNotSupported();
				return gl::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;

			case DT_COMPRESSED_BC7:
				ThrowIfBPTCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
					return gl::COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB;
				else
					return gl::COMPRESSED_RGBA_BPTC_UNORM_ARB;
			}

			throw ImageFormatUnsupportedException("???");
		}
	}

#define LARG_COMPRESSED_CONV(oldFormat, newFormat)\
	case oldFormat:\
		if(bConvertToLA)\
		{\
			ThrowIfLATCNotSupported();\
			internalFormat = newFormat;\
		}\
		else\
			ThrowIfRGTCNotSupported();\
		break;


#define LARG_INTEGRAL_CONV(oldFormat, newFormat)\
	case oldFormat:\
	if(bConvertToLA)\
		{\
			ThrowIfEXT_IntegralNotSupported();\
			internalFormat = newFormat;\
		}\
		else\
			ThrowIfRGNotSupported();\
		break;

#define LARG_FLOAT_CONV(oldFormat, newFormat)\
	case oldFormat:\
	if(bConvertToLA)\
		{\
			ThrowIfEXT_FloatNotSupported();\
			internalFormat = newFormat;\
		}\
		else\
			ThrowIfRGNotSupported();\
		break;

#define LARG_SNORM_CONV(oldFormat, newFormat)\
	case oldFormat:\
		if(bConvertToLA)\
		{\
			ThrowIfEXT_SnormNotSupported();\
			internalFormat = newFormat;\
		}\
		else\
			ThrowIfRGNotSupported();\
		break;

#define LARG_NORM_CONV(oldFormat, newFormat)\
	case oldFormat:\
		if(bConvertToLA)\
		{\
			ThrowIfLANotSupported();\
			internalFormat = newFormat;\
		}\
		else\
			ThrowIfRGNotSupported();\
		break;


#define ONE_COMP_RG(size, suffix) gl::R ## size ## suffix
#define TWO_COMP_RG(size, suffix) gl::RG ## size ## suffix
#define ONE_COMP_LA(size, suffix) gl::LUMINANCE ## size ## suffix ## _EXT
#define TWO_COMP_LA(size, suffix) gl::LUMINANCE_ALPHA ## size ## suffix ## _EXT
#define ONE_ARB_LA(size, suffix) gl::LUMINANCE ## size ## suffix ## _ARB
#define TWO_ARB_LA(size, suffix) gl::LUMINANCE_ALPHA ## size ## suffix ## _ARB
#define ONE_SNORM_LA(size, suffix) gl::LUMINANCE ## size ## suffix
#define TWO_SNORM_LA(size, suffix) gl::LUMINANCE ## size ## _ALPHA ## size ## suffix

	unsigned int GetOpenGLType( const ImageFormat &format, OpenGLPixelTransferParams &ret, PixelDataType eType, GLenum g_packedTypes );
	unsigned int GetInternalFormat( const ImageFormat &format, unsigned int forceConvertBits )
	{
		unsigned int internalFormat = GetStandardOpenGLFormat(format, forceConvertBits);

		bool bConvertToLA = UseLAInsteadOfRG(forceConvertBits);

		//Convert any R or RG formats to L or LA formats.
		switch(internalFormat)
		{
			LARG_COMPRESSED_CONV(gl::COMPRESSED_RED_RGTC1, gl::COMPRESSED_LUMINANCE_LATC1_EXT);
			LARG_COMPRESSED_CONV(gl::COMPRESSED_SIGNED_RED_RGTC1, gl::COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT);
			LARG_COMPRESSED_CONV(gl::COMPRESSED_RG_RGTC2, gl::COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT);
			LARG_COMPRESSED_CONV(gl::COMPRESSED_SIGNED_RG_RGTC2, gl::COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT);

			LARG_INTEGRAL_CONV(ONE_COMP_RG(8, I), ONE_COMP_LA(8, I));
			LARG_INTEGRAL_CONV(ONE_COMP_RG(16, I), ONE_COMP_LA(16, I));
			LARG_INTEGRAL_CONV(ONE_COMP_RG(32, I), ONE_COMP_LA(32, I));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(8, I), TWO_COMP_LA(8, I));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(16, I), TWO_COMP_LA(16, I));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(32, I), TWO_COMP_LA(32, I));

			LARG_INTEGRAL_CONV(ONE_COMP_RG(8, UI), ONE_COMP_LA(8, UI));
			LARG_INTEGRAL_CONV(ONE_COMP_RG(16, UI), ONE_COMP_LA(16, UI));
			LARG_INTEGRAL_CONV(ONE_COMP_RG(32, UI), ONE_COMP_LA(32, UI));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(8, UI), TWO_COMP_LA(8, UI));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(16, UI), TWO_COMP_LA(16, UI));
			LARG_INTEGRAL_CONV(TWO_COMP_RG(32, UI), TWO_COMP_LA(32, UI));

			LARG_FLOAT_CONV(ONE_COMP_RG(16, F), ONE_ARB_LA(16, F));
			LARG_FLOAT_CONV(ONE_COMP_RG(32, F), ONE_ARB_LA(32, F));
			LARG_FLOAT_CONV(TWO_COMP_RG(16, F), TWO_ARB_LA(16, F));
			LARG_FLOAT_CONV(TWO_COMP_RG(32, F), TWO_ARB_LA(32, F));

			LARG_SNORM_CONV(ONE_COMP_RG(8, _SNORM), ONE_SNORM_LA(8, _SNORM));
			LARG_SNORM_CONV(ONE_COMP_RG(16, _SNORM), ONE_SNORM_LA(16, _SNORM));
			LARG_SNORM_CONV(TWO_COMP_RG(8, _SNORM), TWO_SNORM_LA(8, _SNORM));
			LARG_SNORM_CONV(TWO_COMP_RG(16, _SNORM), TWO_SNORM_LA(16, _SNORM));

			LARG_NORM_CONV(gl::R8, gl::LUMINANCE8);
			LARG_NORM_CONV(gl::R16, gl::LUMINANCE16);
			LARG_NORM_CONV(gl::RG8, gl::LUMINANCE8_ALPHA8);
			LARG_NORM_CONV(gl::RG16, gl::LUMINANCE16_ALPHA16);
		}

		return internalFormat;
	}

	//////////////////////////////////////////////////////////////////////////
	/// UPLOAD FORMAT AND TYPE.
	namespace
	{
		bool IsTypeSigned(PixelDataType eType)
		{
			PixelDataType signedIntegerFormats[] = {DT_SIGNED_INTEGRAL, DT_NORM_SIGNED_INTEGER};
			return IsOneOfThese<ARRAY_COUNT(signedIntegerFormats)>(eType, signedIntegerFormats);
		}

		bool IsTypeIntegral(PixelDataType eType)
		{
			PixelDataType integralIntegerFormats[] = {DT_SIGNED_INTEGRAL, DT_UNSIGNED_INTEGRAL};
			return IsOneOfThese<ARRAY_COUNT(integralIntegerFormats)>(eType, integralIntegerFormats);
		}

		GLenum g_packedTypes[] =
		{
			gl::UNSIGNED_SHORT_5_6_5,			//BD_PACKED_16_BIT_565
			gl::UNSIGNED_SHORT_5_5_5_1,			//BD_PACKED_16_BIT_5551
			gl::UNSIGNED_SHORT_4_4_4_4,			//BD_PACKED_16_BIT_4444

			gl::UNSIGNED_INT_8_8_8_8,			//BD_PACKED_32_BIT_8888
			gl::UNSIGNED_INT_10_10_10_2,			//BD_PACKED_32_BIT_1010102
			gl::UNSIGNED_INT_24_8,				//BD_PACKED_32_BIT_248

			gl::UNSIGNED_SHORT_5_6_5_REV,		//BD_PACKED_16_BIT_565_REV
			gl::UNSIGNED_SHORT_1_5_5_5_REV,		//BD_PACKED_16_BIT_1555_REV
			gl::UNSIGNED_SHORT_4_4_4_4_REV,		//BD_PACKED_16_BIT_4444_REV

			gl::UNSIGNED_INT_8_8_8_8_REV,		//BD_PACKED_32_BIT_8888_REV
			gl::UNSIGNED_INT_2_10_10_10_REV,		//BD_PACKED_32_BIT_2101010_REV
			gl::UNSIGNED_INT_10F_11F_11F_REV,	//BD_PACKED_32_BIT_101111_REV
			gl::UNSIGNED_INT_5_9_9_9_REV,		//BD_PACKED_32_BIT_5999_REV
		};

		GLenum GetOpenGLType( const ImageFormat &format, PixelDataType eType, unsigned int forceConvertBits )
		{
			switch(format.Depth())
			{
			case BD_COMPRESSED:
				return 0xFFFFFFFF;
			case BD_PER_COMP_8:
				if(IsTypeSigned(eType))
					return gl::BYTE;
				else
					return gl::UNSIGNED_BYTE;
				break;
			case BD_PER_COMP_16:
				if(eType == DT_FLOAT)
				{
					ThrowIfHalfFloatNotSupported();
					return gl::HALF_FLOAT;
				}
				else
				{
					if(IsTypeSigned(eType))
						return gl::SHORT;
					else
						return gl::UNSIGNED_SHORT;
				}
				break;
			case BD_PER_COMP_32:
				if(eType == DT_FLOAT)
				{
					ThrowIfFloatNotSupported();
					return gl::FLOAT;
				}
				else
				{
					if(IsTypeSigned(eType))
						return gl::INT;
					else
						return gl::UNSIGNED_INT;
				}
				break;
			default:
				{
					int typeIndex = format.Depth() - BD_NUM_PER_COMPONENT;
					if(!((0 <= typeIndex) && (typeIndex < ARRAY_COUNT(g_packedTypes))))
						throw ImageFormatUnsupportedException("Couldn't get the GL type field, due to the bitdepth being outside the packed type array.");

					GLenum testType = g_packedTypes[typeIndex];

					//Test for implemented features.
					switch(testType)
					{
					case gl::UNSIGNED_INT_10F_11F_11F_REV:
						ThrowIfPackedFloatNotSupported();
						break;
					case gl::UNSIGNED_INT_5_9_9_9_REV:
						ThrowIfSharedExpNotSupported();
						break;
					}

					return testType;
				}
			}
		}

		//Starts from FMT_COLOR_RGB. non-integral vs. integral.
		GLenum g_bgraFormats[] =
		{
			gl::BGR,			gl::BGR_INTEGER,		//FMT_COLOR_RGB
			gl::BGRA,		gl::BGRA_INTEGER,	//FMT_COLOR_RGBX
			gl::BGRA,		gl::BGRA_INTEGER,	//FMT_COLOR_RGBA
			gl::BGR,			gl::BGR_INTEGER,		//FMT_COLOR_RGB_sRGB
			gl::BGRA,		gl::BGRA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			gl::BGRA,		gl::BGRA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		//Non-integral vs. integral.
		GLenum g_rgbaFormats[] =
		{
			gl::RED,			gl::RED_INTEGER,		//FMT_COLOR_RED
			gl::RG,			gl::RG_INTEGER,		//FMT_COLOR_RG
			gl::RGB,			gl::RGB_INTEGER,		//FMT_COLOR_RGB
			gl::RGBA,		gl::RGBA_INTEGER,	//FMT_COLOR_RGBX
			gl::RGBA,		gl::RGBA_INTEGER,	//FMT_COLOR_RGBA
			gl::RGB,			gl::RGB_INTEGER,		//FMT_COLOR_RGB_sRGB
			gl::RGBA,		gl::RGBA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			gl::RGBA,		gl::RGBA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		//Non-integral vs. integral.
		GLenum g_rgbaLuminanceFormats[] =
		{
			gl::LUMINANCE,			gl::LUMINANCE_INTEGER_EXT,				//FMT_COLOR_RED
			gl::LUMINANCE_ALPHA,		gl::LUMINANCE_ALPHA_INTEGER_EXT,			//FMT_COLOR_RG
			gl::RGB,					gl::RGB_INTEGER,		//FMT_COLOR_RGB
			gl::RGBA,				gl::RGBA_INTEGER,	//FMT_COLOR_RGBX
			gl::RGBA,				gl::RGBA_INTEGER,	//FMT_COLOR_RGBA
			gl::RGB,					gl::RGB_INTEGER,		//FMT_COLOR_RGB_sRGB
			gl::RGBA,				gl::RGBA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			gl::RGBA,				gl::RGBA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		GLenum GetOpenGLFormat(const ImageFormat &format, PixelDataType eType, unsigned int forceConvertBits)
		{
			if(format.Components() == FMT_DEPTH)
			{
				ThrowIfDepthNotSupported();
				return gl::DEPTH_COMPONENT;
			}

			if(format.Components() == FMT_DEPTH_X)
			{
				ThrowIfDepthStencilNotSupported();
				return gl::DEPTH_STENCIL;
			}

			if(IsTypeIntegral(eType))
			{
				ThrowIfIntegralNotSupported();
			}

			int arrayOffset = IsTypeIntegral(eType) ? 1 : 0;

			if(format.Order() == ORDER_BGRA)
			{
				int formatIndex = format.Components() - FMT_COLOR_RGB;
				formatIndex *= 2;
				if(!((0 <= formatIndex) && (formatIndex < ARRAY_COUNT(g_bgraFormats))))
					throw ImageFormatUnsupportedException("Couldn't get the GL format field with ORDER_BGRA, due to the order being outside the bgraFormats array.");

				return g_bgraFormats[formatIndex];
			}
			else
			{
				int formatIndex = format.Components();
				formatIndex *= 2;
				if(!((0 <= formatIndex) && (formatIndex < ARRAY_COUNT(g_rgbaFormats))))
					throw ImageFormatUnsupportedException("Couldn't get the GL format field with ORDER_RGBA, due to the order being outside the rgbaFormats array.");

				bool isRGChannel = ComponentCount(format, forceConvertBits) < 3;
				
				if(UseLAInsteadOfRG(forceConvertBits))
				{
					if(isRGChannel && arrayOffset == 1)
						ThrowIfEXT_IntegralNotSupported();

					if(isRGChannel)
						ThrowIfLANotSupported();

					return g_rgbaLuminanceFormats[formatIndex];
				}
				else
				{
					if(isRGChannel)
						ThrowIfRGNotSupported();

					return g_rgbaFormats[formatIndex];
				}
			}
		}
	}

	OpenGLPixelTransferParams GetUploadFormatType( const ImageFormat &format, unsigned int forceConvertBits )
	{
		OpenGLPixelTransferParams ret;
		ret.type = 0xFFFFFFFF;
		ret.format = 0xFFFFFFFF;
		ret.blockByteCount = 0;

		PixelDataType eType = GetDataType(format, forceConvertBits);
		if(eType >= DT_NUM_UNCOMPRESSED_TYPES)
		{
			switch(eType)
			{
			case DT_COMPRESSED_BC1:
			case DT_COMPRESSED_UNSIGNED_BC4:
			case DT_COMPRESSED_SIGNED_BC4:
				ret.blockByteCount = 8;
				break;
			default:
				ret.blockByteCount = 16;
				break;
			}

			//Provide reasonable parameters.
			ret.format = gl::RGBA;
			if(eType != DT_COMPRESSED_UNSIGNED_BC6H || eType != DT_COMPRESSED_SIGNED_BC6H)
				ret.type = gl::FLOAT;
			else
				ret.type = gl::UNSIGNED_BYTE;
			return ret;
		}

		ret.type = GetOpenGLType(format, eType, forceConvertBits);
		ret.format = GetOpenGLFormat(format, eType, forceConvertBits);

		return ret;
	}
}

namespace glimg
{
	//////////////////////////////////////////////////////////////////////////
	/// TEXTURE CREATION
	namespace
	{
		void SetupUploadState(const ImageFormat &format, unsigned int forceConvertBits)
		{
			gl::PixelStorei(gl::UNPACK_SWAP_BYTES, gl::FALSE_);
			gl::PixelStorei(gl::UNPACK_LSB_FIRST, gl::FALSE_);
			gl::PixelStorei(gl::UNPACK_ROW_LENGTH, 0);
			gl::PixelStorei(gl::UNPACK_SKIP_ROWS, 0);
			gl::PixelStorei(gl::UNPACK_SKIP_PIXELS, 0);
			gl::PixelStorei(gl::UNPACK_IMAGE_HEIGHT, 0);
			gl::PixelStorei(gl::UNPACK_SKIP_IMAGES, 0);
			gl::PixelStorei(gl::UNPACK_ALIGNMENT, format.LineAlign());
		}

		//Texture must be bound to the target.
		void FinalizeTexture(GLenum texTarget, detail::ImageSetImplPtr pImage)
		{
			int numMipmaps = pImage->GetMipmapCount();
			gl::TexParameteri(texTarget, gl::TEXTURE_BASE_LEVEL, 0);
			gl::TexParameteri(texTarget, gl::TEXTURE_MAX_LEVEL, numMipmaps - 1);

			//Ensure the texture is texture-complete.
			const ImageFormat &format = pImage->GetFormat();
			if(IsTypeIntegral(format.Type()))
			{
				gl::TexParameteri(texTarget, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
				gl::TexParameteri(texTarget, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
			}
			else
			{
				gl::TexParameteri(texTarget, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
				gl::TexParameteri(texTarget, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
			}
		}

		void FinalizeTexture(GLuint texture, GLenum texTarget, detail::ImageSetImplPtr pImage)
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				FinalizeTexture(texTarget, pImage);
				return;
			}

			int numMipmaps = pImage->GetMipmapCount();
			gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_BASE_LEVEL, 0);
			gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_MAX_LEVEL, numMipmaps - 1);

			//Ensure the texture is texture-complete.
			const ImageFormat &format = pImage->GetFormat();
			if(IsTypeIntegral(format.Type()))
			{
				gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
				gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
			}
			else
			{
				gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
				gl::TextureParameteriEXT(texture, texTarget, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
			}
		}

		void ThrowIfArrayTextureNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!gl::exts::var_EXT_texture_array)
					throw TextureUnsupportedException("No Array texture support.");
			}
		}

		void ThrowIfCubeArrayTextureNotSupported()
		{
			if(!glload::IsVersionGEQ(4, 0))
			{
				if(!gl::exts::var_ARB_texture_cube_map_array)
					throw TextureUnsupportedException("No cube-map array texture support.");
			}
		}

		bool IsTextureStorageSupported()
		{
			if(!glload::IsVersionGEQ(4, 2))
			{
				if(!gl::exts::var_ARB_texture_storage)
					return false;
			}

			return true;
		}

		bool IsDirectStateAccessSupported()
		{
			if(!gl::exts::var_EXT_direct_state_access)
				return false;

			return true;
		}

		void ThrowIfCubeTextureNotSupported()
		{
			//Too old to bother checking.
		}

		GLuint CalcCompressedImageSize(GLuint width, GLuint height, const OpenGLPixelTransferParams &upload)
		{
			GLuint columnCount = (width + 3) / 4;
			GLuint rowCount = (height + 3) / 4;
			return columnCount * upload.blockByteCount * rowCount;
		}

		//Texture must be bound to the target.
		void TexStorage( GLenum texTarget, Dimensions dims, GLuint numMipmaps, GLenum internalFormat )
		{
			switch(dims.numDimensions)
			{
			case 1:
				gl::TexStorage1D(texTarget, numMipmaps, internalFormat, dims.width);
				break;
			case 2:
				gl::TexStorage2D(texTarget, numMipmaps, internalFormat, dims.width, dims.height);
				break;
			case 3:
				gl::TexStorage3D(texTarget, numMipmaps, internalFormat, dims.width, dims.height, dims.depth);
				break;
			}
		}

		void TexStorage( GLuint texture, GLenum texTarget, Dimensions dims, GLuint numMipmaps,
			GLenum internalFormat )
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				TexStorage(texTarget, dims, numMipmaps, internalFormat);
				return;
			}

			switch(dims.numDimensions)
			{
			case 1:
				gl::TextureStorage1DEXT(texture, texTarget, numMipmaps, internalFormat, dims.width);
				break;
			case 2:
				gl::TextureStorage2DEXT(texture, texTarget, numMipmaps, internalFormat, dims.width, dims.height);
				break;
			case 3:
				gl::TextureStorage3DEXT(texture, texTarget, numMipmaps, internalFormat,
					dims.width, dims.height, dims.depth);
				break;
			}
		}

		//Only works for TEXTURE_1D, 2D, and 3D.
		//Texture must be bound to the target.
		void ManTexStorageBase(GLenum texTarget, Dimensions dims, GLuint numMipmaps, GLenum internalFormat,
			const OpenGLPixelTransferParams &upload)
		{
			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				switch(dims.numDimensions)
				{
				case 1:
					gl::TexImage1D(texTarget, mipmap, internalFormat, levelDims.width, 0,
						upload.format, upload.type, NULL);
					break;
				case 2:
					gl::TexImage2D(texTarget, mipmap, internalFormat, levelDims.width, levelDims.height, 0,
						upload.format, upload.type, NULL);
					break;
				case 3:
					gl::TexImage1D(texTarget, mipmap, internalFormat, levelDims.width, 0,
						upload.format, upload.type, NULL);
					break;
				}
			}
		}

		//For 1D, 2D arrays, and array/cubemap
		//Texture must be bound to the target.
		void ManTexStorageArray(GLenum texTarget, Dimensions dims, GLuint numMipmaps, GLuint arrayCount,
			GLenum internalFormat, const OpenGLPixelTransferParams &upload)
		{
			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				switch(dims.numDimensions)
				{
				case 1:
					gl::TexImage2D(texTarget, mipmap, internalFormat, levelDims.width, arrayCount, 0,
						upload.format, upload.type, NULL);
					break;
				case 2:
					if(texTarget == gl::TEXTURE_CUBE_MAP_ARRAY)
						arrayCount *= 6;

					gl::TexImage3D(texTarget, mipmap, internalFormat, levelDims.width, levelDims.height, arrayCount,
						0, upload.format, upload.type, NULL);
					break;
				}
			}
		}

		//For non-array cubemap
		//Texture must be bound to the target.
		void ManTexStorageCube(GLenum texTarget, Dimensions dims, GLuint numMipmaps,
			GLenum internalFormat, const OpenGLPixelTransferParams &upload)
		{
			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_X, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_NEGATIVE_X, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_Y, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_NEGATIVE_Y, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_Z, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TexImage2D(gl::TEXTURE_CUBE_MAP_NEGATIVE_Z, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
			}
		}

		//Only works for TEXTURE_1D, 2D, and 3D.
		//DSA-style
		void ManTexStorageBase(GLuint texture, GLenum texTarget, Dimensions dims, GLuint numMipmaps,
			GLenum internalFormat, const OpenGLPixelTransferParams &upload)
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				ManTexStorageBase(texTarget, dims, numMipmaps, internalFormat, upload);
				return;
			}

			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				switch(dims.numDimensions)
				{
				case 1:
					gl::TextureImage1DEXT(texture, texTarget, mipmap, internalFormat, levelDims.width, 0,
						upload.format, upload.type, NULL);
					break;
				case 2:
					gl::TextureImage2DEXT(texture, texTarget, mipmap, internalFormat, levelDims.width, levelDims.height, 0,
						upload.format, upload.type, NULL);
					break;
				case 3:
					gl::TextureImage1DEXT(texture, texTarget, mipmap, internalFormat, levelDims.width, 0,
						upload.format, upload.type, NULL);
					break;
				}
			}
		}

		//For 1D, 2D arrays, and array/cubemap
		//DSA-style
		void ManTexStorageArray(GLuint texture, GLenum texTarget, Dimensions dims, GLuint numMipmaps,
			GLuint arrayCount, GLenum internalFormat, const OpenGLPixelTransferParams &upload)
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				ManTexStorageArray(texTarget, dims, numMipmaps, arrayCount, internalFormat, upload);
				return;
			}

			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				switch(dims.numDimensions)
				{
				case 1:
					gl::TextureImage2DEXT(texture, texTarget, mipmap, internalFormat, levelDims.width, arrayCount, 0,
						upload.format, upload.type, NULL);
					break;
				case 2:
					gl::TextureImage3DEXT(texture, texTarget, mipmap, internalFormat, levelDims.width,
						levelDims.height, arrayCount, 0, upload.format, upload.type, NULL);
					break;
				}
			}
		}

		//For non-array cubemap
		//DSA-style
		void ManTexStorageCube(GLuint texture, GLenum texTarget, Dimensions dims, GLuint numMipmaps,
			GLenum internalFormat, const OpenGLPixelTransferParams &upload)
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				ManTexStorageCube(texTarget, dims, numMipmaps, internalFormat, upload);
				return;
			}

			for(GLuint mipmap = 0; mipmap < numMipmaps; ++mipmap)
			{
				Dimensions levelDims = ModifySizeForMipmap(dims, mipmap);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_POSITIVE_X, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_NEGATIVE_X, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_POSITIVE_Y, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_NEGATIVE_Y, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_POSITIVE_Z, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
				gl::TextureImage2DEXT(texture, gl::TEXTURE_CUBE_MAP_NEGATIVE_Z, mipmap, internalFormat,
					levelDims.width, levelDims.height, 0, upload.format, upload.type, NULL);
			}
		}

		//Texture must be bound to the target.
		void TexSubImage(GLenum texTarget, GLuint mipmap, GLuint internalFormat,
			Dimensions dims, const OpenGLPixelTransferParams &upload,
			const void *pPixelData, size_t pixelByteSize)
		{
			switch(dims.numDimensions)
			{
			case 1:
				if(upload.blockByteCount)
					gl::CompressedTexSubImage1D(texTarget, mipmap, 0,
					dims.width,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TexSubImage1D(texTarget, mipmap, 0,
					dims.width,
					upload.format, upload.type, pPixelData);
				break;
			case 2:
				if(upload.blockByteCount)
					gl::CompressedTexSubImage2D(texTarget, mipmap, 0, 0,
					dims.width, dims.height,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TexSubImage2D(texTarget, mipmap, 0, 0,
					dims.width, dims.height,
					upload.format, upload.type, pPixelData);
				break;
			case 3:
				if(upload.blockByteCount)
					gl::CompressedTexSubImage3D(texTarget, mipmap, 0, 0, 0,
					dims.width, dims.height, dims.depth,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TexSubImage3D(texTarget, mipmap, 0, 0, 0,
					dims.width, dims.height, dims.depth,
					upload.format, upload.type, pPixelData);
				break;
			}
		}

		void TexSubImage(GLuint texture, GLenum texTarget, GLuint mipmap, GLuint internalFormat,
			Dimensions dims, const OpenGLPixelTransferParams &upload,
			const void *pPixelData, size_t pixelByteSize)
		{
			//Zero means bound, so no DSA.
			if(texture == 0)
			{
				TexSubImage(texTarget, mipmap, internalFormat, dims, upload, pPixelData, pixelByteSize);
				return;
			}

			switch(dims.numDimensions)
			{
			case 1:
				if(upload.blockByteCount)
					gl::CompressedTextureSubImage1DEXT(texture, texTarget, mipmap, 0,
					dims.width,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TextureSubImage1DEXT(texture, texTarget, mipmap, 0,
					dims.width,
					upload.format, upload.type, pPixelData);
				break;
			case 2:
				if(upload.blockByteCount)
					gl::CompressedTextureSubImage2DEXT(texture, texTarget, mipmap, 0, 0,
					dims.width, dims.height,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TextureSubImage2DEXT(texture, texTarget, mipmap, 0, 0,
					dims.width, dims.height,
					upload.format, upload.type, pPixelData);
				break;
			case 3:
				if(upload.blockByteCount)
					gl::CompressedTextureSubImage3DEXT(texture, texTarget, mipmap, 0, 0, 0,
					dims.width, dims.height, dims.depth,
					internalFormat, pixelByteSize, pPixelData);
				else
					gl::TextureSubImage3DEXT(texture, texTarget, mipmap, 0, 0, 0,
					dims.width, dims.height, dims.depth,
					upload.format, upload.type, pPixelData);
				break;
			}
		}

		enum
		{
			NO_DSA_NO_STORAGE,
			NO_DSA_YES_STORAGE,
			YES_DSA_NO_STORAGE,
			YES_DSA_YES_STORAGE,
		};

		int GetUploadClass(unsigned int forceConvertBits)
		{
			int ret = 0;
			if(forceConvertBits & USE_TEXTURE_STORAGE)
				ret |= 0x1;
			if(forceConvertBits & USE_DSA)
				ret |= 0x2;
			return ret;
		}

		//Works for just 1D/2D/3D.
		void TexStorageBase( GLenum texTarget, unsigned int forceConvertBits, Dimensions dims,
			const int numMipmaps, GLuint internalFormat, const OpenGLPixelTransferParams & upload,
			GLuint textureName )
		{
			if(forceConvertBits & USE_TEXTURE_STORAGE)
				TexStorage(textureName, texTarget, dims, numMipmaps, internalFormat);
			else
			{
				ManTexStorageBase(textureName, texTarget, dims, numMipmaps,
					internalFormat, upload);
			}
		}

		void TexStorageCube( GLenum texTarget, unsigned int forceConvertBits, Dimensions dims,
			const int numMipmaps, GLuint internalFormat, const OpenGLPixelTransferParams & upload,
			GLuint textureName )
		{
			if(forceConvertBits & USE_TEXTURE_STORAGE)
				TexStorage(textureName, texTarget, dims, numMipmaps, internalFormat);
			else
			{
				ManTexStorageCube(textureName, texTarget, dims, numMipmaps,
					internalFormat, upload);
			}
		}


		class TextureBinder
		{
		public:
			TextureBinder() : texture(0), texTarget(0) {}
			void Bind(GLenum _texTarget, GLuint _texture)
			{
				texture = _texture;
				texTarget = _texTarget;
				gl::BindTexture(texTarget, texture);
			}
			~TextureBinder() {if(texture) gl::BindTexture(texTarget, 0);}
		private:
			GLuint texture;
			GLenum texTarget;
		};

		void Build1DArrayTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build1DTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			TextureBinder bind;
			if(!(forceConvertBits & USE_DSA))
			{
				bind.Bind(gl::TEXTURE_1D, textureName);
				textureName = 0;
			}

			const int numMipmaps = pImage->GetMipmapCount();
			TexStorageBase(gl::TEXTURE_1D, forceConvertBits, pImage->GetDimensions(),
				numMipmaps, internalFormat, upload, textureName);

			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				Dimensions dims = pImage->GetDimensions(mipmap);
				const void *pPixelData = pImage->GetImageData(mipmap, 0, 0);

				TexSubImage(textureName, gl::TEXTURE_1D, mipmap, internalFormat, dims, upload,
					pPixelData, pImage->GetImageByteSize(mipmap));
			}

			FinalizeTexture(textureName, gl::TEXTURE_1D, pImage);
		}

		void Build2DCubeArrayTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			ThrowIfCubeArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build2DArrayTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build2DCubeTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfCubeTextureNotSupported();

			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			TextureBinder bind;
			if(!(forceConvertBits & USE_DSA))
			{
				bind.Bind(gl::TEXTURE_CUBE_MAP, textureName);
				textureName = 0;
			}

			const int numMipmaps = pImage->GetMipmapCount();
			TexStorageCube(gl::TEXTURE_CUBE_MAP, forceConvertBits, pImage->GetDimensions(),
				numMipmaps, internalFormat, upload, textureName);

			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				Dimensions dims = pImage->GetDimensions(mipmap);

				for(int faceIx = 0; faceIx < 6; ++faceIx)
				{
					const void *pPixelData = pImage->GetImageData(mipmap, 0, faceIx);

					TexSubImage(textureName, gl::TEXTURE_CUBE_MAP_POSITIVE_X + faceIx,
						mipmap, internalFormat, dims, upload,
						pPixelData, pImage->GetImageByteSize(mipmap));
				}
			}

			FinalizeTexture(textureName, gl::TEXTURE_CUBE_MAP, pImage);
		}

		void Build2DTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			TextureBinder bind;
			if(!(forceConvertBits & USE_DSA))
			{
				bind.Bind(gl::TEXTURE_2D, textureName);
				textureName = 0;
			}

			const int numMipmaps = pImage->GetMipmapCount();
			TexStorageBase(gl::TEXTURE_2D, forceConvertBits, pImage->GetDimensions(),
				numMipmaps, internalFormat, upload, textureName);

			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				Dimensions dims = pImage->GetDimensions(mipmap);
				const void *pPixelData = pImage->GetImageData(mipmap);

				TexSubImage(textureName, gl::TEXTURE_2D, mipmap, internalFormat, dims, upload,
					pPixelData, pImage->GetImageByteSize(mipmap));
			}

			FinalizeTexture(textureName, gl::TEXTURE_2D, pImage);
		}

		void Build3DTexture(unsigned int textureName, detail::ImageSetImplPtr pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			TextureBinder bind;
			if(!(forceConvertBits & USE_DSA))
			{
				bind.Bind(gl::TEXTURE_3D, textureName);
				textureName = 0;
			}

			const int numMipmaps = pImage->GetMipmapCount();
			TexStorageBase(gl::TEXTURE_3D, forceConvertBits, pImage->GetDimensions(),
				numMipmaps, internalFormat, upload, textureName);

			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				Dimensions dims = pImage->GetDimensions(mipmap);
				const void *pPixelData = pImage->GetImageData(mipmap);

				TexSubImage(textureName, gl::TEXTURE_3D, mipmap, internalFormat, dims, upload, pPixelData,
					pImage->GetImageByteSize(mipmap));
			}

			FinalizeTexture(textureName, gl::TEXTURE_3D, pImage);
		}

		bool IsArrayTexture(const ImageSet *pImage, unsigned int forceConvertBits)
		{
			//No such thing as 3D array textures.
			if(pImage->GetDimensions().numDimensions == 3)
				return false;

			if((forceConvertBits & FORCE_ARRAY_TEXTURE) || pImage->GetArrayCount() > 1)
				return true;

			return false;
		}
	}

	unsigned int GetTextureType( const ImageSet *pImage, unsigned int forceConvertBits )
	{
		Dimensions dims = pImage->GetDimensions();

		switch(dims.numDimensions)
		{
		case 1:
			//May be 1D or 1D array.
			if(IsArrayTexture(pImage, forceConvertBits))
				return gl::TEXTURE_1D_ARRAY;
			else
				return gl::TEXTURE_1D;
		case 2:
			//2D, 2D array, 2D cube, or 2D array cube.
			if(IsArrayTexture(pImage, forceConvertBits))
			{
				if(pImage->GetFaceCount() > 1)
					return gl::TEXTURE_CUBE_MAP_ARRAY;
				else
					return gl::TEXTURE_2D_ARRAY;
			}
			else
			{
				if(pImage->GetFaceCount() > 1)
					return gl::TEXTURE_CUBE_MAP;
				else
					return gl::TEXTURE_2D;
			}
			break;
		case 3:
			//3D.
			return gl::TEXTURE_3D;
		}

		return 0xFFFFFFFF;
	}

	unsigned int CreateTexture( const ImageSet *pImage, unsigned int forceConvertBits )
	{
		GLuint textureName = 0;
		gl::GenTextures(1, &textureName);

		try
		{
			CreateTexture(textureName, pImage, forceConvertBits);
		}
		catch(...)
		{
			gl::DeleteTextures(1, &textureName);
			throw;
		}

		return textureName;
	}

	void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits)
	{
		if(forceConvertBits & FORCE_TEXTURE_STORAGE)
		{
			if(!IsTextureStorageSupported())
				throw CannotForceTextureStorage();
			forceConvertBits |= USE_TEXTURE_STORAGE;
		}

		if(forceConvertBits & USE_TEXTURE_STORAGE)
		{
			if(!IsTextureStorageSupported())
				forceConvertBits &= ~USE_TEXTURE_STORAGE;
		}

		if(forceConvertBits & FORCE_DSA)
		{
			if(!IsDirectStateAccessSupported())
				throw CannotForceDSAUsage();
			forceConvertBits |= USE_DSA;
		}

		if(forceConvertBits & USE_DSA)
		{
			if(!IsDirectStateAccessSupported())
				forceConvertBits &= ~USE_DSA;
		}

		const ImageFormat &format = pImage->GetFormat();
		GLuint internalFormat = GetInternalFormat(format, forceConvertBits);
		OpenGLPixelTransferParams upload = GetUploadFormatType(format, forceConvertBits);

		switch(GetTextureType(pImage, forceConvertBits))
		{
		case gl::TEXTURE_1D:
			Build1DTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_2D:
			Build2DTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_3D:
			Build3DTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_1D_ARRAY:
			Build1DArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_2D_ARRAY:
			Build2DArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_CUBE_MAP:
			Build2DCubeTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		case gl::TEXTURE_CUBE_MAP_ARRAY:
			Build2DCubeArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
				internalFormat, upload);
			break;
		}
	}
}
