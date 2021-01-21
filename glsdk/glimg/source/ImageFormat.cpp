//Copyright (C) 2011-2013 by Jason L. McKesson
//This file is licensed by the MIT License.



#include "glimg/ImageFormat.h"
#include "Util.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace glimg
{
	namespace
	{
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

		PixelComponents g_alphaFormats[] = {FMT_COLOR_RGBA, FMT_COLOR_RGBA_sRGB};
		PixelComponents g_rgbFormats[] = {FMT_COLOR_RGB, FMT_COLOR_RGB_sRGB};
		Bitdepth g_floatBitdepths[] = {BD_PER_COMP_16, BD_PER_COMP_32, BD_PACKED_32_BIT_101111_REV};
		Bitdepth g_threeCompBitdepths[] = {BD_PACKED_16_BIT_565, BD_PACKED_16_BIT_565_REV};
		PixelComponents g_colorFormats[] = {FMT_COLOR_RED, FMT_COLOR_RG, FMT_COLOR_RGB,
			FMT_COLOR_RGBX, FMT_COLOR_RGBA, FMT_COLOR_RGB_sRGB, FMT_COLOR_RGBX_sRGB, FMT_COLOR_RGBA_sRGB};
		PixelComponents g_srgbFormats[] = {FMT_COLOR_RGB_sRGB, FMT_COLOR_RGBX_sRGB, FMT_COLOR_RGBA_sRGB};
	}

	bool UncheckedImageFormat::ValidateFormat() const
	{
		const std::string &theMsg = ValidateFormatText();

		if(theMsg.empty())
			return true;

		return false;
	}

	std::string UncheckedImageFormat::ValidateFormatText() const
	{
		//Alignment only matters for uncompressed types.
		if(eType < DT_NUM_UNCOMPRESSED_TYPES)
		{
			int tests[] = {1, 2, 4, 8};

			if(!IsOneOfThese<ARRAY_COUNT(tests)>(lineAlignment, tests))
				return std::string("Alignment must be 1, 2, 4, or 8 bytes.");

			if(eOrder == ORDER_COMPRESSED)
				return std::string("ORDER_COMPRESSED can only be used with compressed types.");

			if(eBitdepth == BD_COMPRESSED)
				return std::string("BD_COMPRESSED can only be used with compressed types.");
		}
		else
		{
			if(eOrder != ORDER_COMPRESSED)
				return std::string("Compressed types must use ORDER_COMPRESSED ordering.");

			if(eBitdepth != BD_COMPRESSED)
				return std::string("Compressed types must use BD_COMPRESSED bitdepth.");

			//Test the compressed formats with the colors.
			if(eType == DT_COMPRESSED_BC2 || eType == DT_COMPRESSED_BC3 || eType == DT_COMPRESSED_BC7)
			{
				if(!IsOneOfThese<ARRAY_COUNT(g_alphaFormats)>(eFormat, g_alphaFormats))
					return std::string("BC2, 3, and 7 compression must use an RGBA format.");
			}
			else if(eType == DT_COMPRESSED_BC1)
			{
				if( !IsOneOfThese<ARRAY_COUNT(g_rgbFormats)>(eFormat, g_rgbFormats) &&
					!IsOneOfThese<ARRAY_COUNT(g_alphaFormats)>(eFormat, g_alphaFormats))
					return std::string("BC1 compression must use an RGB or RGBA format");
			}
			if(eType == DT_COMPRESSED_UNSIGNED_BC4 || eType == DT_COMPRESSED_SIGNED_BC4)
			{
				if(eFormat != FMT_COLOR_RED)
					return std::string("BC4 compression must use the RED format.");
			}
			if(eType == DT_COMPRESSED_UNSIGNED_BC5 || eType == DT_COMPRESSED_SIGNED_BC5)
			{
				if(eFormat != FMT_COLOR_RG)
					return std::string("BC5 compression must use the RG format.");
			}
			if(eType == DT_COMPRESSED_UNSIGNED_BC6H || eType == DT_COMPRESSED_SIGNED_BC6H)
			{
				if(eFormat != FMT_COLOR_RGB)
					return std::string("BC6H compression must use the RGB format.");
			}

			//End of compressed stuff.
			return std::string();
		}

		//Check for shared float. It has only one legal arrangement of forms.
		{
			bool bSharedExp = (eType == DT_SHARED_EXP_FLOAT);
			bool bSharedOrder = (eOrder == ORDER_RGBE);
			bool bSharedDepth = (eBitdepth == BD_PACKED_32_BIT_5999_REV);
			if(bSharedExp != bSharedOrder ||
				bSharedOrder != bSharedDepth)
				return std::string("Shared floats must use DT_SHARED_EXP_FLOAT type, "
					"ORDER_RGBE order, and BD_PACKED_32_BIT_5999_REV bitdepth.");

			if(bSharedExp && (eFormat != FMT_COLOR_RGB))
				return std::string("Shared floats must use RGB format.");

			//Shared exponent only comes in one form.
			if(bSharedExp)
				return std::string();
		}

		//Check depth.
		if(eFormat == FMT_DEPTH || eFormat == FMT_DEPTH_X)
		{
			if(eOrder != ORDER_DEPTH_STENCIL)
				return std::string("Depth formats must use ORDER_DEPTH_STENCIL ordering.");

			//Depth can be either 16-bit normalized, 32-bit float, or 24x8 normalized.
			if(eType == DT_NORM_UNSIGNED_INTEGER)
			{
				if(eFormat == FMT_DEPTH)
				{
					if(eBitdepth != BD_PER_COMP_16)
						return std::string("FMT_DEPTH format with unsigned normalized integers must use BD_PER_COMP_16");
				}
				else
				{
					if(eBitdepth != BD_PACKED_32_BIT_248)
						return std::string("FMT_DEPTH_X format with unsigned normalized integers must use BD_PACKED_32_BIT_248");
				}
			}
			else if(eType == DT_FLOAT)
			{
				//Must be 32-bit float.
				if(eBitdepth != BD_PER_COMP_32 || eFormat != FMT_DEPTH)
					return std::string("DT_FLOAT types with depth formats must use BD_PER_COMP_32 bitdepth");
			}
			else
			{
				//Must be either normalized unsigned or float.
				return std::string("Depth formats must use either unsigned normalized or floating point types.");
			}

			//Short circuit. We've tested all possibilities for depth formats.
			return std::string("");
		}

		//We would not be here if the format contained depth, and this can only use depth.
		if(eBitdepth == BD_PACKED_32_BIT_248)
			return std::string("BD_PACKED_32_BIT_248 can only be used with a depth format.");

		//Floats must be at least 16-bits per component, or 101111.
		if(eType == DT_FLOAT)
		{
			if(!IsOneOfThese<ARRAY_COUNT(g_floatBitdepths)>(eBitdepth, g_floatBitdepths))
				return std::string("Floating-point types must use 16 or 32-bit bitdepths, or the BD_PACKED_32_BIT_101111_REV");
		}

		//Only normalized unsigned integers can be sRGB.
		if(IsOneOfThese<ARRAY_COUNT(g_srgbFormats)>(eFormat, g_srgbFormats))
		{
			if(eType != DT_NORM_UNSIGNED_INTEGER)
				return std::string("Only normalized, unsigned integers can be in the sRGB colorspace.");
		}

		//If 101111, then must be BGR, and must be float.
		if(eBitdepth == BD_PACKED_32_BIT_101111_REV)
		{
			if(!(eType == DT_FLOAT && eOrder == ORDER_RGBA && eFormat == FMT_COLOR_RGB))
				return std::string("The BD_PACKED_32_BIT_101111_REV bitdepth can only be used with DT_FLOAT, ORDER_RGBA, and FMT_COLOR_RGB.");

			//Short circuit.
			return std::string();
		}

		//Test all packed bitdepths.
		if(eBitdepth >= BD_NUM_PER_COMPONENT)
		{
			//Only unsigned integers and certain special floats can be packed.
			//The special floats have already been checked, so let them through.
			if(eType != DT_NORM_UNSIGNED_INTEGER && eType != DT_FLOAT)
				return std::string("Only normalized, unsigned integers and floats can use packed bitdepths.");

			//Ensure that bitdepth and the format match in terms of component count.
			switch(ComponentCount(eFormat))
			{
			case 1:
				//This can never work.
				return std::string("Single-component formats cannot work with packed bitdepths.");
			case 2:
				//Covered previously.
				return std::string("Non-depth two-component formats cannot work with packed bitdepths.");
			case 3:
				if(!IsOneOfThese<ARRAY_COUNT(g_threeCompBitdepths)>(eBitdepth, g_threeCompBitdepths))
					return std::string("The only packed formats available to 3-component formats are 565 or 565_REV.");
				break;
			case 4:
				if(IsOneOfThese<ARRAY_COUNT(g_threeCompBitdepths)>(eBitdepth, g_threeCompBitdepths))
					return std::string("Cannot use 565 or 565_REV with 4-component formats.");
				break;
			}
		}

		//Normalized types cannot use 32-bit per-component.
		if(eBitdepth == BD_PER_COMP_32)
		{
			if(eType == DT_NORM_UNSIGNED_INTEGER || eType == DT_NORM_SIGNED_INTEGER)
				return std::string("Normalized integer formats cannot be used with 32-bit per-component data.");
		}

		//BGRA ordering can only use 3 and 4 component types.
		if(eOrder == ORDER_BGRA)
		{
			if(ComponentCount(eFormat) < 3)
				return std::string("BGRA ordering can only use 3 or 4 components.");
		}

		return std::string();
	}

	ImageFormat::ImageFormat( PixelDataType _eType, PixelComponents _eFormat,
		ComponentOrder _eOrder, Bitdepth _eBitdepth, int _lineAlignment )
	{
		fmt.eType = _eType;
		fmt.eFormat = _eFormat;
		fmt.eOrder = _eOrder;
		fmt.eBitdepth = _eBitdepth;
		fmt.lineAlignment = _lineAlignment;

		const std::string msg = fmt.ValidateFormatText();
		if(!msg.empty())
			throw InvalidFormatException(msg);
	}

	ImageFormat::ImageFormat( UncheckedImageFormat _fmt )
		: fmt(_fmt)
	{
		const std::string msg = fmt.ValidateFormatText();
		if(!msg.empty())
			throw InvalidFormatException(msg);
	}

	size_t ImageFormat::AlignByteCount( size_t byteCount ) const
	{
		return (byteCount + (fmt.lineAlignment - 1)) / fmt.lineAlignment;
	}
}
