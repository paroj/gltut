
#include <assert.h>
#include <glload/gl_all.h>
#include <glload/gll.h>
#include "glimg/TextureGeneratorExceptions.h"
#include "glimg/TextureGenerator.h"
#include "ImageSetImpl.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glimg
{
	//////////////////////////////////////////////////////////////////////////
	/// INTERNAL FORMAT
	namespace
	{
		void ThrowIfS3TCNotSupported()
		{
			if(!glext_EXT_texture_compression_s3tc)
				throw ImageFormatUnsupportedException("S3TC not supported.");
		}

		void ThrowIfLATCNotSupported()
		{
			if(!glext_EXT_texture_compression_latc)
				throw ImageFormatUnsupportedException("LATC not supported.");
		}

		void ThrowIfRGTCNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!(glext_ARB_texture_compression_rgtc || glext_EXT_texture_compression_rgtc))
					throw ImageFormatUnsupportedException("RGTC, part of GL 3.0 and above, is not supported.");
			}
		}

		void ThrowIfBPTCNotSupported()
		{
			if(!glext_ARB_texture_compression_bptc)
				throw ImageFormatUnsupportedException("PBTC not supported.");
		}

		void ThrowIfSRGBNotSupported()
		{
			if(!glload::IsVersionGEQ(2, 1))
			{
				if(!glext_EXT_texture_sRGB)
					throw ImageFormatUnsupportedException("sRGB textures not supported.");
			}
		}

		void ThrowIfEXT_SRGBNotSupported()
		{
				if(!glext_EXT_texture_sRGB)
					throw ImageFormatUnsupportedException("sRGB and S3TC textures not supported.");
		}

		void ThrowIfSharedExpNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_EXT_texture_shared_exponent)
					throw ImageFormatUnsupportedException("Shared exponent texture format not supported.");
			}
		}

		void ThrowIfFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_ARB_texture_float)
					throw ImageFormatUnsupportedException("Float textures not supported.");
			}
		}

		void ThrowIfEXT_FloatNotSupported()
		{
			if(!glext_ARB_texture_float)
				throw ImageFormatUnsupportedException("ARB Float textures not supported.");
		}

		void ThrowIfHalfFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_ARB_half_float_pixel)
					throw ImageFormatUnsupportedException("Half floats textures not supported.");
			}
		}

		void ThrowIfSnormNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 1))
			{
				if(!glext_EXT_texture_snorm)
					throw ImageFormatUnsupportedException("Signed normalized textures not supported.");
			}
		}

		void ThrowIfEXT_SnormNotSupported()
		{
			if(!glext_EXT_texture_snorm)
				throw ImageFormatUnsupportedException("Signed normalized texture extension not supported.");
		}

		void ThrowIfPackedFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_EXT_packed_float)
					throw ImageFormatUnsupportedException("Packed 11, 11, 10 float textures not supported.");
			}
		}
		
		void ThrowIfIntegralNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_EXT_texture_integer)
					throw ImageFormatUnsupportedException("Integral textures not supported.");
			}
		}

		void ThrowIfEXT_IntegralNotSupported()
		{
			if(!glext_EXT_texture_integer)
				throw ImageFormatUnsupportedException("Integral texture extension not supported.");
		}

		void ThrowIfRGNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_ARB_texture_rg)
					throw ImageFormatUnsupportedException("RG textures not supported.");
			}
		}

		void ThrowIfLANotSupported()
		{
			if(!glload::IsVersionGEQ(3,0))
				return;
			if(!glload::IsVersionGEQ(3,2))
			{
				if(!glext_ARB_compatibility)
					throw ImageFormatUnsupportedException("Core OpenGL contexts cannot use Luminance/alpha.");
			}
			else
			{
				GLint profileMask = 0;
				glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);
				if(profileMask & GL_CONTEXT_CORE_PROFILE_BIT)
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
				if(!glext_ARB_depth_texture)
					throw ImageFormatUnsupportedException("Depth textures not supported.");
			}
		}

		void ThrowIfDepthStencilNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!(glext_EXT_packed_depth_stencil || glext_ARB_framebuffer_object))
					throw ImageFormatUnsupportedException("Depth/stencil textures not supported.");
			}
		}

		void ThrowIfDepthFloatNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_NV_depth_buffer_float)
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

			if(IsOneOfThese<ARRAY_COUNT(twoCompFormats)>(format.eFormat, twoCompFormats))
				return 2;

			if(IsOneOfThese<ARRAY_COUNT(threeCompFormats)>(format.eFormat, threeCompFormats))
				return 3;

			if(IsOneOfThese<ARRAY_COUNT(fourCompFormats)>(format.eFormat, fourCompFormats))
				return 4;

			return 1;
		}

		int PerComponentSize(const ImageFormat &format, unsigned int forceConvertBits)
		{
			//TODO: Forceconv.
			switch(format.eBitdepth)
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
			if(IsOneOfThese<ARRAY_COUNT(srgbFormats)>(format.eFormat, srgbFormats))
				return true;

			if(!(forceConvertBits & FORCE_SRGB_COLORSPACE_FMT))
				return false;

			PixelDataType srgbTypes[] = {DT_NORM_UNSIGNED_INTEGER,
				DT_COMPRESSED_BC1, DT_COMPRESSED_BC2, DT_COMPRESSED_BC3, DT_COMPRESSED_BC7};

			if(IsOneOfThese<ARRAY_COUNT(srgbTypes)>(format.eType, srgbTypes))
			{
				if(format.eType != DT_NORM_UNSIGNED_INTEGER)
					return true;
			}
			else
				return false;

			//unsigned normalized integers. Check for RGB or RGBA components.
			PixelComponents convertableFormats[] = {FMT_COLOR_RGB, FMT_COLOR_RGBX, FMT_COLOR_RGBA};
			if(IsOneOfThese<ARRAY_COUNT(convertableFormats)>(format.eFormat, convertableFormats))
				return true;

			return false;
		}

		bool FormatHasAlpha(const ImageFormat &format, unsigned int forceConvertBits)
		{
			//TODO: Forceconv. Check for color renderable.
			PixelComponents alphaFormats[] = {FMT_COLOR_RGBA, FMT_COLOR_RGBA_sRGB};
			if(IsOneOfThese<ARRAY_COUNT(alphaFormats)>(format.eFormat, alphaFormats))
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
				return format.eType;

			switch(format.eType)
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
			}

			return format.eType;
		}

		//Ordered by BaseDataFormat*2. The first is 16-bit, the second is 32-bit.
		GLenum g_floatFormats[] =
		{
			GL_R16F,
			GL_R32F,
			GL_RG16F,
			GL_RG32F,
			GL_RGB16F,
			GL_RGB32F,
			GL_RGB16F,
			GL_RGB32F,
			GL_RGBA16F,
			GL_RGBA32F,
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//sRGB
			0,			//16-bit float depth buffer. 
			GL_DEPTH_COMPONENT32F,
			0,			//UNorm+stencil.
		};

		//Ordered by number of components * size (8, 16, 32=>0, 1, 2).
		GLenum g_signIntegralFormats[] =
		{
			GL_R8I,			GL_R16I,			GL_R32I,
			GL_RG8I,		GL_RG16I,			GL_RG32I,
			GL_RGB8I,		GL_RGB16I,			GL_RGB32I,
			GL_RGBA8I,		GL_RGBA16I,			GL_RGBA32I,
		};

		//Ordered by number of components * size (8, 16, 32=>0, 1, 2).
		GLenum g_unsignIntegralFormats[] =
		{
			GL_R8UI,		GL_R16UI,			GL_R32UI,
			GL_RG8UI,		GL_RG16UI,			GL_RG32UI,
			GL_RGB8UI,		GL_RGB16UI,			GL_RGB32UI,
			GL_RGBA8UI,		GL_RGBA16UI,		GL_RGBA32UI,
		};

		//Ordered by number of components * size (8, 16=>0, 1, 2).
		GLenum g_signedNormFormats[] =
		{
			GL_R8_SNORM,		GL_R16_SNORM,
			GL_RG8_SNORM,		GL_RG16_SNORM,
			GL_RGB8_SNORM,		GL_RGB16_SNORM,
			GL_RGBA8_SNORM,		GL_RGBA16_SNORM,
		};

		GLenum ThrowInvalidFormatIfZero(GLenum input)
		{
			if(!input)
				throw ImageFormatUnexpectedException();

			return input;
		}

		unsigned int GetStandardOpenGLFormat( const ImageFormat &format, unsigned int forceConvertBits )
		{
			PixelDataType eType = GetDataType(format, forceConvertBits);

			switch(eType)
			{
			case DT_NORM_UNSIGNED_INTEGER:
				//Only 16-bit for non Depth_x.
				if(format.eFormat == FMT_DEPTH)
				{
					ThrowIfDepthNotSupported();
					return GL_DEPTH_COMPONENT16;
				}

				//Only 24x8 for this.
				if(format.eFormat == FMT_DEPTH_X)
				{
					ThrowIfDepthStencilNotSupported();
					return GL_DEPTH24_STENCIL8;
				}

				//Color formats.
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfSRGBNotSupported();
					if(ComponentCount(format, forceConvertBits) == 3)
						return GL_SRGB8;
					else
						return GL_SRGB8_ALPHA8;
				}

				switch(format.eBitdepth)
				{
				case BD_PER_COMP_8:
					{
						GLenum components[] = {GL_R8, GL_RG8, GL_RGB8, GL_RGBA8};
						int numComponents = ComponentCount(format, forceConvertBits);

						return components[numComponents - 1];
					}
				case BD_PER_COMP_16:
					{
						GLenum components[] = {GL_R16, GL_RG16, GL_RGB16, GL_RGBA16};
						int numComponents = ComponentCount(format, forceConvertBits);

						return components[numComponents - 1];
					}

				case BD_PACKED_16_BIT_565:
				case BD_PACKED_16_BIT_565_REV:
					return GL_RGB8;

				case BD_PACKED_16_BIT_5551:
				case BD_PACKED_16_BIT_1555_REV:
					return GL_RGB5_A1;

				case BD_PACKED_16_BIT_4444:
				case BD_PACKED_16_BIT_4444_REV:
					return GL_RGBA4;

				case BD_PACKED_32_BIT_8888:
				case BD_PACKED_32_BIT_8888_REV:
					return GL_RGBA8;

				case BD_PACKED_32_BIT_1010102:
				case BD_PACKED_32_BIT_2101010_REV:
					return GL_RGB10_A2;
				}

				throw ImageFormatUnexpectedException("Unisgned normalize integer doesn't match accepted bitdepths.");

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
				if(format.eBitdepth < BD_NUM_PER_COMPONENT)
				{
					int offset = 0;
					if(format.eBitdepth == BD_PER_COMP_32)
						offset = 1;
					else
						ThrowIfHalfFloatNotSupported();

					if(format.eFormat == FMT_DEPTH)
						ThrowIfDepthFloatNotSupported();

					return ThrowInvalidFormatIfZero(g_floatFormats[(2 * format.eFormat) + offset]);
				}
				else
				{
					//Only one packed format.
					ThrowIfPackedFloatNotSupported();
					return GL_R11F_G11F_B10F;
				}

			case DT_SHARED_EXP_FLOAT:
				ThrowIfSharedExpNotSupported();
				ThrowIfForceRendertarget(forceConvertBits);
				return GL_RGB9_E5;

			case DT_COMPRESSED_BC1:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					if(forceConvertBits & FORCE_BC1_ALPHA_FMT)
						return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
					else
					{
						if(ComponentCount(format, forceConvertBits) == 3)
							return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
						else
							return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
					}
				}
				else
				{
					if(forceConvertBits & FORCE_BC1_ALPHA_FMT)
						return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					else
					{
						if(ComponentCount(format, forceConvertBits) == 3)
							return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
						else
							return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					}
				}

			case DT_COMPRESSED_BC2:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
				}
				else
					return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;

			case DT_COMPRESSED_BC3:
				ThrowIfS3TCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
				{
					ThrowIfEXT_SRGBNotSupported();
					return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
				}
				else
					return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;

			case DT_COMPRESSED_UNSIGNED_BC4:
				return GL_COMPRESSED_RED_RGTC1;
			case DT_COMPRESSED_SIGNED_BC4:
				return GL_COMPRESSED_SIGNED_RED_RGTC1;

			case DT_COMPRESSED_UNSIGNED_BC5:
				return GL_COMPRESSED_RG_RGTC2;
			case DT_COMPRESSED_SIGNED_BC5:
				return GL_COMPRESSED_SIGNED_RG_RGTC2;

			case DT_COMPRESSED_UNSIGNED_BC6H:
				ThrowIfBPTCNotSupported();
				return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;

			case DT_COMPRESSED_SIGNED_BC6H:
				ThrowIfBPTCNotSupported();
				return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;

			case DT_COMPRESSED_BC7:
				ThrowIfBPTCNotSupported();
				if(IsSRGBFormat(format, forceConvertBits))
					return GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB;
				else
					return GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
			}

			throw ImageFormatUnexpectedException("???");
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


#define ONE_COMP_RG(size, suffix) GL_R ## size ## suffix
#define TWO_COMP_RG(size, suffix) GL_RG ## size ## suffix
#define ONE_COMP_LA(size, suffix) GL_LUMINANCE ## size ## suffix ## _EXT
#define TWO_COMP_LA(size, suffix) GL_LUMINANCE_ALPHA ## size ## suffix ## _EXT
#define ONE_ARB_LA(size, suffix) GL_LUMINANCE ## size ## suffix ## _ARB
#define TWO_ARB_LA(size, suffix) GL_LUMINANCE_ALPHA ## size ## suffix ## _ARB
#define ONE_SNORM_LA(size, suffix) GL_LUMINANCE ## size ## suffix
#define TWO_SNORM_LA(size, suffix) GL_LUMINANCE ## size ## _ALPHA ## size ## suffix

	unsigned int GetOpenGLType( const ImageFormat &format, OpenGLPixelTransferParams &ret, PixelDataType eType, GLenum g_packedTypes );
	unsigned int GetInternalFormat( const ImageFormat &format, unsigned int forceConvertBits )
	{
		{
			const std::string & msg = format.ValidateFormatText();
			if(!msg.empty())
				throw ImageFormatUnexpectedException(msg);
		}

		unsigned int internalFormat = GetStandardOpenGLFormat(format, forceConvertBits);

		bool bConvertToLA = UseLAInsteadOfRG(forceConvertBits);

		//Convert any R or RG formats to L or LA formats.
		switch(internalFormat)
		{
			LARG_COMPRESSED_CONV(GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_LUMINANCE_LATC1_EXT);
			LARG_COMPRESSED_CONV(GL_COMPRESSED_SIGNED_RED_RGTC1, GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT);
			LARG_COMPRESSED_CONV(GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT);
			LARG_COMPRESSED_CONV(GL_COMPRESSED_SIGNED_RG_RGTC2, GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT);

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

			LARG_NORM_CONV(GL_R8, GL_LUMINANCE8);
			LARG_NORM_CONV(GL_R16, GL_LUMINANCE16);
			LARG_NORM_CONV(GL_RG8, GL_LUMINANCE8_ALPHA8);
			LARG_NORM_CONV(GL_RG16, GL_LUMINANCE16_ALPHA16);
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
			GL_UNSIGNED_SHORT_5_6_5,			//BD_PACKED_16_BIT_565
			GL_UNSIGNED_SHORT_5_5_5_1,			//BD_PACKED_16_BIT_5551
			GL_UNSIGNED_SHORT_4_4_4_4,			//BD_PACKED_16_BIT_4444

			GL_UNSIGNED_INT_8_8_8_8,			//BD_PACKED_32_BIT_8888
			GL_UNSIGNED_INT_10_10_10_2,			//BD_PACKED_32_BIT_1010102
			GL_UNSIGNED_INT_24_8,				//BD_PACKED_32_BIT_248

			GL_UNSIGNED_SHORT_5_6_5_REV,		//BD_PACKED_16_BIT_565_REV
			GL_UNSIGNED_SHORT_1_5_5_5_REV,		//BD_PACKED_16_BIT_1555_REV
			GL_UNSIGNED_SHORT_4_4_4_4_REV,		//BD_PACKED_16_BIT_4444_REV

			GL_UNSIGNED_INT_8_8_8_8_REV,		//BD_PACKED_32_BIT_8888_REV
			GL_UNSIGNED_INT_2_10_10_10_REV,		//BD_PACKED_32_BIT_2101010_REV
			GL_UNSIGNED_INT_10F_11F_11F_REV,	//BD_PACKED_32_BIT_101111_REV
			GL_UNSIGNED_INT_5_9_9_9_REV,		//BD_PACKED_32_BIT_5999_REV
		};

		GLenum GetOpenGLType( const ImageFormat &format, PixelDataType eType, unsigned int forceConvertBits )
		{
			switch(format.eBitdepth)
			{
			case BD_COMPRESSED:
				return 0xFFFFFFFF;
			case BD_PER_COMP_8:
				if(IsTypeSigned(eType))
					return GL_BYTE;
				else
					return GL_UNSIGNED_BYTE;
				break;
			case BD_PER_COMP_16:
				if(eType == DT_FLOAT)
				{
					ThrowIfHalfFloatNotSupported();
					return GL_HALF_FLOAT;
				}
				else
				{
					if(IsTypeSigned(eType))
						return GL_SHORT;
					else
						return GL_UNSIGNED_SHORT;
				}
				break;
			case BD_PER_COMP_32:
				if(eType == DT_FLOAT)
				{
					ThrowIfFloatNotSupported();
					return GL_FLOAT;
				}
				else
				{
					if(IsTypeSigned(eType))
						return GL_INT;
					else
						return GL_UNSIGNED_INT;
				}
				break;
			default:
				{
					int typeIndex = format.eBitdepth - BD_NUM_PER_COMPONENT;
					if(!((0 <= typeIndex) && (typeIndex < ARRAY_COUNT(g_packedTypes))))
						throw ImageFormatUnexpectedException("Couldn't get the GL type field, due to the bitdepth being outside the packed type array.");

					GLenum testType = g_packedTypes[typeIndex];

					//Test for implemented features.
					switch(testType)
					{
					case GL_UNSIGNED_INT_10F_11F_11F_REV:
						ThrowIfPackedFloatNotSupported();
						break;
					case GL_UNSIGNED_INT_5_9_9_9_REV:
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
			GL_BGR,			GL_BGR_INTEGER,		//FMT_COLOR_RGB
			GL_BGRA,		GL_BGRA_INTEGER,	//FMT_COLOR_RGBX
			GL_BGRA,		GL_BGRA_INTEGER,	//FMT_COLOR_RGBA
			GL_BGR,			GL_BGR_INTEGER,		//FMT_COLOR_RGB_sRGB
			GL_BGRA,		GL_BGRA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			GL_BGRA,		GL_BGRA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		//Non-integral vs. integral.
		GLenum g_rgbaFormats[] =
		{
			GL_RED,			GL_RED_INTEGER,		//FMT_COLOR_RED
			GL_RG,			GL_RG_INTEGER,		//FMT_COLOR_RG
			GL_RGB,			GL_RGB_INTEGER,		//FMT_COLOR_RGB
			GL_RGBA,		GL_RGBA_INTEGER,	//FMT_COLOR_RGBX
			GL_RGBA,		GL_RGBA_INTEGER,	//FMT_COLOR_RGBA
			GL_RGB,			GL_RGB_INTEGER,		//FMT_COLOR_RGB_sRGB
			GL_RGBA,		GL_RGBA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			GL_RGBA,		GL_RGBA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		//Non-integral vs. integral.
		GLenum g_rgbaLuminanceFormats[] =
		{
			GL_LUMINANCE,			GL_LUMINANCE_INTEGER_EXT,				//FMT_COLOR_RED
			GL_LUMINANCE_ALPHA,		GL_LUMINANCE_ALPHA_INTEGER_EXT,			//FMT_COLOR_RG
			GL_RGB,					GL_RGB_INTEGER,		//FMT_COLOR_RGB
			GL_RGBA,				GL_RGBA_INTEGER,	//FMT_COLOR_RGBX
			GL_RGBA,				GL_RGBA_INTEGER,	//FMT_COLOR_RGBA
			GL_RGB,					GL_RGB_INTEGER,		//FMT_COLOR_RGB_sRGB
			GL_RGBA,				GL_RGBA_INTEGER,	//FMT_COLOR_RGBX_sRGB
			GL_RGBA,				GL_RGBA_INTEGER,	//FMT_COLOR_RGBA_sRGB
		};

		GLenum GetOpenGLFormat(const ImageFormat &format, PixelDataType eType, unsigned int forceConvertBits)
		{
			if(format.eFormat == FMT_DEPTH)
			{
				ThrowIfDepthNotSupported();
				return GL_DEPTH_COMPONENT;
			}

			if(format.eFormat == FMT_DEPTH_X)
			{
				ThrowIfDepthStencilNotSupported();
				return GL_DEPTH_STENCIL;
			}

			if(IsTypeIntegral(eType))
			{
				ThrowIfIntegralNotSupported();
			}

			int arrayOffset = IsTypeIntegral(eType) ? 1 : 0;

			if(format.eOrder == ORDER_BGRA)
			{
				int formatIndex = format.eFormat - FMT_COLOR_RGB;
				formatIndex *= 2;
				if(!((0 <= formatIndex) && (formatIndex < ARRAY_COUNT(g_bgraFormats))))
					throw ImageFormatUnexpectedException("Couldn't get the GL format field with ORDER_BGRA, due to the order being outside the bgraFormats array.");

				return g_bgraFormats[formatIndex];
			}
			else
			{
				int formatIndex = format.eFormat;
				formatIndex *= 2;
				if(!((0 <= formatIndex) && (formatIndex < ARRAY_COUNT(g_rgbaFormats))))
					throw ImageFormatUnexpectedException("Couldn't get the GL format field with ORDER_RGBA, due to the order being outside the rgbaFormats array.");

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
		{
			const std::string & msg = format.ValidateFormatText();
			if(!msg.empty())
				throw ImageFormatUnexpectedException(msg);
		}

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
			return ret;
		}

		ret.type = GetOpenGLType(format, eType, forceConvertBits);
		ret.format = GetOpenGLFormat(format, eType, forceConvertBits);

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////
	/// TEXTURE CREATION
	namespace
	{
		void SetupUploadState(const ImageFormat &format, unsigned int forceConvertBits)
		{
			glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
			glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
			glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
			glPixelStorei(GL_UNPACK_ALIGNMENT, format.lineAlignment);
		}

		void FinalizeTexture(GLenum texTarget, const detail::ImageSetImpl *pImage)
		{
			int numMipmaps = pImage->GetMipmapCount();
			glTexParameteri(texTarget, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(texTarget, GL_TEXTURE_MAX_LEVEL, numMipmaps - 1);

			//Ensure the texture is texture-complete.
			const ImageFormat &format = pImage->GetFormat();
			if(IsTypeIntegral(format.eType))
			{
				glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else
			{
				glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}

			glBindTexture(texTarget, 0);
		}

		void ThrowIfArrayTextureNotSupported()
		{
			if(!glload::IsVersionGEQ(3, 0))
			{
				if(!glext_EXT_texture_array)
					throw TextureUnsupportedException("No Array texture support.");
			}
		}

		void ThrowIfCubeArrayTextureNotSupported()
		{
			if(!glload::IsVersionGEQ(4, 0))
			{
				if(!glext_ARB_texture_cube_map_array)
					throw TextureUnsupportedException("No cube-map array texture support.");
			}
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

		void TexImage1D(GLenum texTarget, GLuint mipmap, GLuint internalFormat,
			GLuint width, const OpenGLPixelTransferParams &upload, const void *pPixelData)
		{
			if(upload.blockByteCount)
			{
				GLuint byteCount = CalcCompressedImageSize(width, 1, upload);
				glCompressedTexImage1D(texTarget, mipmap, internalFormat, width, 0,
					byteCount, pPixelData);
			}
			else
			{
				glTexImage1D(texTarget, mipmap, internalFormat, width, 0,
					upload.format, upload.type, pPixelData);
			}
		}

		void TexImage2D(GLenum texTarget, GLuint mipmap, GLuint internalFormat,
			GLuint width, GLuint height, const OpenGLPixelTransferParams &upload, const void *pPixelData)
		{
			if(upload.blockByteCount)
			{
				GLuint byteCount = CalcCompressedImageSize(width, height, upload);
				glCompressedTexImage2D(texTarget, mipmap, internalFormat, width, height, 0,
					byteCount, pPixelData);
			}
			else
			{
				glTexImage2D(texTarget, mipmap, internalFormat, width, height, 0,
					upload.format, upload.type, pPixelData);
			}
		}

		void TexImage3D(GLenum texTarget, GLuint mipmap, GLuint internalFormat,
			GLuint width, GLuint height, GLuint depth, const OpenGLPixelTransferParams &upload,
			const void *pPixelData)
		{
			if(upload.blockByteCount)
			{
				//compressed array textures are stored as 4x4x1 sheets.
				GLuint byteCount = CalcCompressedImageSize(width, height, upload) * depth;
				glCompressedTexImage3D(texTarget, mipmap, internalFormat, width, height, depth, 0,
					byteCount, pPixelData);
			}
			else
			{
				glTexImage3D(texTarget, mipmap, internalFormat, width, height, depth, 0,
					upload.format, upload.type, pPixelData);
			}
		}

		void Build1DArrayTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build1DTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			glBindTexture(GL_TEXTURE_1D, textureName);

			const int numMipmaps = pImage->GetMipmapCount();
			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				const detail::MipmapLevel &mipData = pImage->GetMipmapLevel(mipmap);
				Dimensions dims = pImage->GetDimensions(mipmap);

				const void *pPixelData = mipData.bFullLayer ?
					mipData.fullPixelData.pPixelData : mipData.individualDataList[0].pPixelData;

				TexImage1D(GL_TEXTURE_1D, mipmap, internalFormat, dims.width,
					upload, pPixelData);
			}

			FinalizeTexture(GL_TEXTURE_1D, pImage);
		}

		void Build2DCubeArrayTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			ThrowIfCubeArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build2DArrayTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfArrayTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build2DCubeTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			ThrowIfCubeTextureNotSupported();
			throw TextureUnexpectedException();
		}

		void Build2DTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			glBindTexture(GL_TEXTURE_2D, textureName);

			const int numMipmaps = pImage->GetMipmapCount();
			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				const detail::MipmapLevel &mipData = pImage->GetMipmapLevel(mipmap);
				Dimensions dims = pImage->GetDimensions(mipmap);
				const void *pPixelData = mipData.bFullLayer ?
					mipData.fullPixelData.pPixelData : mipData.individualDataList[0].pPixelData;

				TexImage2D(GL_TEXTURE_2D, mipmap, internalFormat, dims.width, dims.height,
					upload, pPixelData);
			}

			FinalizeTexture(GL_TEXTURE_2D, pImage);
		}

		void Build3DTexture(unsigned int textureName, const detail::ImageSetImpl *pImage,
			unsigned int forceConvertBits, GLuint internalFormat, const OpenGLPixelTransferParams &upload)
		{
			SetupUploadState(pImage->GetFormat(), forceConvertBits);
			glBindTexture(GL_TEXTURE_3D, textureName);

			const int numMipmaps = pImage->GetMipmapCount();
			for(int mipmap = 0; mipmap < numMipmaps; mipmap++)
			{
				const detail::MipmapLevel &mipData = pImage->GetMipmapLevel(mipmap);
				Dimensions dims = pImage->GetDimensions(mipmap);
				const void *pPixelData = mipData.bFullLayer ?
					mipData.fullPixelData.pPixelData : mipData.individualDataList[0].pPixelData;

				TexImage3D(GL_TEXTURE_2D, mipmap, internalFormat, dims.width, dims.height, dims.depth,
					upload, pPixelData);
			}

			FinalizeTexture(GL_TEXTURE_3D, pImage);
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

	unsigned int CreateTexture( const ImageSet *pImage, unsigned int forceConvertBits )
	{
		GLuint textureName = 0;
		glGenTextures(1, &textureName);

		try
		{
			CreateTexture(textureName, pImage, forceConvertBits);
		}
		catch(...)
		{
			glDeleteTextures(1, &textureName);
			throw;
		}

		return textureName;
	}

	void CreateTexture(unsigned int textureName, const ImageSet *pImage, unsigned int forceConvertBits)
	{
		const ImageFormat &format = pImage->GetFormat();
		GLuint internalFormat = GetInternalFormat(format, forceConvertBits);
		OpenGLPixelTransferParams upload = GetUploadFormatType(format, forceConvertBits);

		Dimensions dims = pImage->GetDimensions();

		switch(dims.numDimensions)
		{
		case 1:
			//May be 1D or 1D array.
			if(IsArrayTexture(pImage, forceConvertBits))
				Build1DArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
					internalFormat, upload);
			else
				Build1DTexture(textureName, pImage->m_pImpl, forceConvertBits,
					internalFormat, upload);
			break;
		case 2:
			//2D, 2D array, 2D cube, or 2D array cube.
			if(IsArrayTexture(pImage, forceConvertBits))
			{
				if(pImage->GetFaceCount() > 1)
					Build2DCubeArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
						internalFormat, upload);
				else
					Build2DArrayTexture(textureName, pImage->m_pImpl, forceConvertBits,
						internalFormat, upload);
			}
			else
			{
				if(pImage->GetFaceCount() > 1)
					Build2DCubeTexture(textureName, pImage->m_pImpl, forceConvertBits,
						internalFormat, upload);
				else
					Build2DTexture(textureName, pImage->m_pImpl, forceConvertBits,
						internalFormat, upload);
			}
			break;
		case 3:
			//3D.
			Build3DTexture(textureName, pImage->m_pImpl, forceConvertBits, internalFormat, upload);
			break;
		}
	}
}
