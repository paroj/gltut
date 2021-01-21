/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/


#ifndef GLIMG_IMAGE_FORMAT_H
#define GLIMG_IMAGE_FORMAT_H

#include <string>
#include <exception>


/**
@file

\brief Contains all of the enums and objects related to formats.

\ingroup module_glimg_format
**/

namespace glimg
{
	///\addtogroup module_glimg_format
	///@{

	/**
	\brief Describes the basic type of the pixel data.

	The pixel data type of an image represents the basic type of data stored in the image.
	This can be floating-point, normalized unsigned integer, and the like. They also describe
	if they are compressed. You can test a `PixelDataType` to see if it is a compressed format
	by seeing if the value is less than `DT_NUM_UNCOMPRESSED_TYPES`.
	**/
	enum PixelDataType
	{
		DT_NORM_UNSIGNED_INTEGER,			///<Image data are unsigned integers that are mapped to floats on the range [0, 1].
		DT_NORM_SIGNED_INTEGER,				///<Image data are signed integers that are mapped to floats on the range [-1, 1].
		DT_UNSIGNED_INTEGRAL,				///<Image data are unsigned integers.
		DT_SIGNED_INTEGRAL,					///<Image data are signed integers.
		DT_FLOAT,							///<Image data are individual floating-point numbers.
		DT_SHARED_EXP_FLOAT,				///<Image data are floats, but each pixel uses the same exponent.
		DT_NUM_UNCOMPRESSED_TYPES,

		DT_COMPRESSED_BC1 = DT_NUM_UNCOMPRESSED_TYPES,	///<Image data is compressed with DXT1/BC1 compression. Unsigned normalized integers.
		DT_COMPRESSED_BC2,					///<Image data is compressed with DXT3/BC2 compression. Unsigned normalized integers.
		DT_COMPRESSED_BC3,					///<Image data is compressed with DXT5/BC3 compression. Unsigned normalized integers.
		DT_COMPRESSED_UNSIGNED_BC4,			///<Image is compressed with BC4 compression (1-component), with unsigned normalized integers.
		DT_COMPRESSED_SIGNED_BC4,			///<Image is compressed with BC4 compression (1-component), with signed normalized integers.
		DT_COMPRESSED_UNSIGNED_BC5,			///<Image is compressed with BC5 compression (2-component), with unsigned normalized integers.
		DT_COMPRESSED_SIGNED_BC5,			///<Image is compressed with BC5 compression (2-component), with signed normalized integers.
		DT_COMPRESSED_UNSIGNED_BC6H,		///<Image is compressed with BC6H compression, with unsigned floats [0, +inf).
		DT_COMPRESSED_SIGNED_BC6H,			///<Image is compressed with BC6H compression, with floats.
		DT_COMPRESSED_BC7,					///<Image data is compressed with BC7 compression. Unsigned normalized integers.

		DT_NUM_TYPES,
	};

	/**
	\brief Describes the components stored in a pixel of the image.

	Pixels can store between 1 and 4 values. This enumerator defines how many values are stored
	and what these values mean. It defines the colorspace of the values (sRGB vs. linear),
	and also whether the values are color or depth values.
	**/
	enum PixelComponents
	{
		FMT_COLOR_RED,					///<Image contains 1 color component, namely red.
		FMT_COLOR_RG,					///<Image contains 2 color components, red and green.
		FMT_COLOR_RGB,					///<Image contains 3 color components, red, green, and blue.
		FMT_COLOR_RGBX,					///<Image contains 3 color components, red, green, and blue. There is a fourth component, which takes up space in the data but should be discarded.
		FMT_COLOR_RGBA,					///<Image contains 4 color components, red, green, blue, and alpha.
		FMT_COLOR_RGB_sRGB,				///<Image contains 3 color components, which are in the sRGB colorspace.
		FMT_COLOR_RGBX_sRGB,			///<Image contains 3 color components, which are in the sRGB colorspace. There is a fourth component, which takes up space in the data but should be discarded.
		FMT_COLOR_RGBA_sRGB,			///<Image contains 4 color components; the RGB components are in the sRGB colorspace.

		FMT_DEPTH,						///<Image contains a single depth component.
		FMT_DEPTH_X,					///<Image contains a depth value (unsigned normalized integer) and a second component, who's value is discarded/irrelevant.

		FMT_NUM_FORMATS,
	};

	/**
	\brief Specifies the ordering of the component data in the image.

	This enumeration specifies the ordering of the components in the image's values. Components that are
	missing from the `BaseDataFormat` are ignored.

	Some combinations of order and bitdepth are not allowed.
	**/
	enum ComponentOrder
	{
		ORDER_RGBA,				///<Standard RGBA ordering.
		ORDER_BGRA,				///<Often used in conjunction with _REV Bitdepths.
		ORDER_RGBE,				///<For `DT_SHARED_EXP_FLOAT` types. The `E` is the exponent, and it comes last. Can only be used with `BD_PACKED_32_BIT_5999_REF`.

		ORDER_DEPTH_STENCIL,	///<Ordering for depth and depth-stencil image formats.

		ORDER_COMPRESSED,		///<The order is built into the compressed data format.

		ORDER_NUM_ORDERS,
	};

	/**
	\brief Specifies the bitdepth for each component of each pixel.

	Each component of each pixel has a particular bitdepth. The bitdepths specified here
	are either per-component or specify the size of an entire pixel. The PER_COMP
	enumerators specify the size of each component.

	So if `PER_COMP_16` is used with a RGB format, then each pixel takes up 48 bits.
	This could be using integers (shorts) or floats (half-floats). Whether it is
	16-bit integers or 16-bit floats is determined by the `PixelDataType`.

	The `PACKED` enumerators are for formats where each component does not have
	the same bitdepth. The number after `PACKED` specifies the overall bitdepth
	of the pixel. `PACKED_16_BIT` means that the pixel takes up 16 bits.
	The numbers after represent the bitdepth of the individual components, in the order
	specified by the ComponentOrder enumerator.

	`PACKED` formats that end in `_REV` reverse the order of the components. So `1555_REV`
	means that the lowest 5 bits are the first component, the next 5 are the second, 
	the 5 after that are the third, and the highest bit is the fourth component.
	**/
	enum Bitdepth
	{
		BD_COMPRESSED,					///<Used for compressed data types. They do not have a bitdepth.

		BD_PER_COMP_8,					///<Each component takes up 8 bits.
		BD_PER_COMP_16,					///<Each component takes up 16 bits.
		BD_PER_COMP_32,					///<Each component takes up 32 bits.
		BD_NUM_PER_COMPONENT,			

		BD_PACKED_16_BIT_565 = BD_NUM_PER_COMPONENT,///<The first and third components take up 5 bits, while the second takes up 6.
		BD_PACKED_16_BIT_5551,			///<The first three components take up 5 bits, and the last takes up 1.
		BD_PACKED_16_BIT_4444,			///<Each component takes up 4 bits.

		BD_PACKED_32_BIT_8888,			///<Each component takes up 8 bits.
		BD_PACKED_32_BIT_1010102,		///<The first three components take up 10 bits, and the last takes up 2.
		BD_PACKED_32_BIT_248,			///<The first component takes up 24 bits; the second takes up 8 bits.

		BD_PACKED_16_BIT_565_REV,		///<Reverse order. The first and third components take up 5 bits, while the second takes up 6.
		BD_PACKED_16_BIT_1555_REV,		///<Reverse order. The first three components take up 5 bits, and the last takes up 1.
		BD_PACKED_16_BIT_4444_REV,		///<Reverse order. Each component takes up 4 bits.

		BD_PACKED_32_BIT_8888_REV,		///<Reverse order. Each component takes up 8 bits.
		BD_PACKED_32_BIT_2101010_REV,	///<Reverse order. The first three components take up 10 bits, and the last takes up 2.
		BD_PACKED_32_BIT_101111_REV,	///<Reverse order. The first two components take 11 bits, and the third takes 10. Used only for `DT_FLOAT` types.
		BD_PACKED_32_BIT_5999_REV,		///<Reverse order. The first 3 components take 9 bits, and the last takes 5. Used only for `DT_SHARED_EXP_FLOAT` types. 

		BD_NUM_BITDEPTH,
	};

	/**
	\brief Represents a potentially valid image format.

	This struct stores the component information and other data that defines an image format.
	Not all combinations are valid image formats; there are functions to test validity.
	All of the APIs explicitly use ImageFormat instead of this type; that class's constructors
	will thrown an InvalidFormatException if the combination of values is not valid. So you are
	strongly encouraged to use that class directly.
	**/
	struct UncheckedImageFormat
	{
		PixelDataType eType;		///<The type of pixel data.
		PixelComponents eFormat;	///<The components stored by a pixel.
		ComponentOrder eOrder;		///<The order of the components of the pixel.
		Bitdepth eBitdepth;			///<The bitdepth of each pixel component.

		int lineAlignment;			///<The byte alignment of a horizontal line of pixel data.

		/**
		\brief Determines if the values set into this ImageFormat are valid.

		The ImageFormat object has no constructor, and therefore you could conceivably use
		any combination of parameters. However, there are specific constraints imposed on
		ImageFormat enumerators. If these constraints fail, then an error results.

		For details on the specifics of validation, see
		\ref page_glimg_format_validation.

		\return An empty string if the ImageFormat is valid, and an error message if it is not.
		**/
		std::string ValidateFormatText() const;

		///As ValidateFormatText, only returns true if valid and false otherwise.
		bool ValidateFormat() const;
	};

	///Thrown if an invalid format is used by any API. Usually contains an explanation of the problem.
	class InvalidFormatException : public std::exception
	{
	public:
		InvalidFormatException()
			: message("Invalid Image Format")
		{}

		InvalidFormatException(const std::string &msg)
			: message("Invalid Image Format:\n")
		{
			message += msg;
		}

		virtual ~InvalidFormatException() throw() {}

		virtual const char *what() const throw() {return message.c_str();}

	protected:
		std::string message;
	};

	/**
	\brief An immutable combination of image format parameters.

	The image format object will throw if the given format parameters are impossible or inconsistent.
	The \ref page_glimg_format_validation "rules for format validation are available."
	
	These objects are immutable once created.
	**/
	class ImageFormat
	{
	public:
		/**
		\brief Constructs an image format from individual image data.
		
		\throws InvalidFormatException If the combinations of parameters is
		\ref page_glimg_format_validation "not valid". The exception
		will have a string explaining the problem.
		**/
		ImageFormat(PixelDataType _eType,
					PixelComponents _eFormat,
					ComponentOrder _eOrder,
					Bitdepth _eBitdepth,
					int _lineAlignment);

		/**
		\brief Implicitly constructs an ImageFormat from an UncheckedImageFormat.
		
		\throws InvalidFormatException If \a _fmt does
		\ref page_glimg_format_validation "not contain valid data". The exception
		will have a string explaining the problem.
		**/
		ImageFormat(UncheckedImageFormat _fmt);

		///Retrieves the contents as an UncheckedImageFormat.
		UncheckedImageFormat GetUncheckedFormat() const {return fmt;}

		/**
		\name Accessors
		**/
		/**@{**/
		PixelDataType		Type() const		{return fmt.eType;}
		PixelComponents		Components() const	{return fmt.eFormat;}
		ComponentOrder		Order() const		{return fmt.eOrder;}
		Bitdepth			Depth() const		{return fmt.eBitdepth;}
		int					LineAlign() const	{return fmt.lineAlignment;}
		/**@}**/

		///Computes the aligned byte count from the line alignment.
		size_t AlignByteCount(size_t byteCount) const;

	private:
		UncheckedImageFormat fmt;
	};



	///@}
}


#endif //GLIMG_IMAGE_FORMAT_H
