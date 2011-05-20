#include <stdio.h>
#include <vector>
#include <glload/gl_3_3_comp.h>

#include <glimg/glimg.h>
#include <glimg/TextureGenerator.h>
#include <glimg/TextureGeneratorExceptions.h>
#include "test.h"

using namespace glimg;

namespace
{
	struct TestData
	{
		ImageFormat format;
		unsigned int forceConvertBits;
	};

	void GetFormats(std::vector<TestData> &formats)
	{
		formats.reserve(100);

		TestData testFmt;
		//Succeed. GL_RGBA8 = 0x8058
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_32_BIT_8888;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_SRGB8_ALPHA8 = 0x8C43. From forced colorspace.
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_32_BIT_8888;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = FORCE_SRGB_COLORSPACE;
		formats.push_back(testFmt);

		//Succeed. GL_RGB5_A1 = 0x8057.
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_16_BIT_5551;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Fail. Packed format with RED.
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RED;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_16_BIT_5551;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Fail. Packed format with RG.
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RG;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_16_BIT_5551;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_SRGB8_ALPHA8 = 0x8C43.
		testFmt.format.eType = DT_NORM_UNSIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RGBA_sRGB;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_16_BIT_5551;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Fail. Wrong bitdepth for floats.
		testFmt.format.eType = DT_FLOAT;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_32_BIT_8888;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_RGBA16F = 0x881A.
		testFmt.format.eType = DT_FLOAT;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_16;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_RG16F = 0x822F.
		testFmt.format.eType = DT_FLOAT;
		testFmt.format.eFormat = FMT_COLOR_RG;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_16;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_LUMINANCE_ALPHA16F_ARB = 0x881F. Force Luminance.
		testFmt.format.eType = DT_FLOAT;
		testFmt.format.eFormat = FMT_COLOR_RG;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_16;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = FORCE_LUMINANCE_FORMATS;
		formats.push_back(testFmt);

		//Succeed. GL_R11F_G11F_B10F = 0x8C3A.
		testFmt.format.eType = DT_FLOAT;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_32_BIT_101111_REV;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Failed. Bad order.
		testFmt.format.eType = DT_COMPRESSED_BC1;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_COMPRESSED;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Failed. Bad bitdepth.
		testFmt.format.eType = DT_COMPRESSED_BC1;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_COMPRESSED;
		testFmt.format.eBitdepth = BD_PER_COMP_8;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeeded. GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0
		testFmt.format.eType = DT_COMPRESSED_BC1;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_COMPRESSED;
		testFmt.format.eBitdepth = BD_COMPRESSED;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeeded. GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1
		testFmt.format.eType = DT_COMPRESSED_BC1;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_COMPRESSED;
		testFmt.format.eBitdepth = BD_COMPRESSED;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeeded. GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT = 0x8C4D
		testFmt.format.eType = DT_COMPRESSED_BC1;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_COMPRESSED;
		testFmt.format.eBitdepth = BD_COMPRESSED;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = FORCE_BC1_ALPHA_TEXTURE | FORCE_SRGB_COLORSPACE;
		formats.push_back(testFmt);

		//Fail. Packed + integral = bad.
		testFmt.format.eType = DT_SIGNED_INTEGRAL;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PACKED_16_BIT_5551;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_RGBA8I = 0x8D8E.
		testFmt.format.eType = DT_SIGNED_INTEGRAL;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_8;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_RGB32I = 0x8D83.
		testFmt.format.eType = DT_SIGNED_INTEGRAL;
		testFmt.format.eFormat = FMT_COLOR_RGB;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_32;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);

		//Succeed. GL_RGBA8_SNORM = 0x8F97
		testFmt.format.eType = DT_NORM_SIGNED_INTEGER;
		testFmt.format.eFormat = FMT_COLOR_RGBA;
		testFmt.format.eOrder = ORDER_RGBA;
		testFmt.format.eBitdepth = BD_PER_COMP_8;
		testFmt.format.lineAlignment = 4;
		testFmt.forceConvertBits = 0;
		formats.push_back(testFmt);
	}
}


void TestImageFormats()
{
	std::vector<TestData> formats;
	GetFormats(formats);

	for(size_t loop = 0; loop < formats.size(); loop++)
	{
		try
		{
			GLuint internalFmt = glimg::GetInternalFormat(formats[loop].format, formats[loop].forceConvertBits);
			OpenGLUploadData upload = glimg::GetUploadFormatType(formats[loop].format, formats[loop].forceConvertBits);
			printf("Internal Format of %i: 0x%04x, [format=0x%04x, type=0x%04x]\n", loop, internalFmt,
				upload.format, upload.type);
		}
		catch(TextureGenerationException &e)
		{
			printf("---->Format %i failed:\n%s\n", loop, e.what());
		}
	}
}

