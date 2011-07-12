///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-17
// Licence : This source is under MIT License
// File    : glm/core/func_packing.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_packing
#define glm_core_func_packing

namespace glm
{
	namespace core{
	namespace function{
	//! Define packing functions from section 8.4 floating-point pack and unpack functions of GLSL 4.00.8 specification
	namespace packing
	{
		/// \addtogroup core_funcs
		///@{

        //! First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values. 
        //! Then, the results are packed into the returned 32-bit unsigned integer.
        //! 
        //! The conversion for component c of v to fixed point is done as follows:
        //! packUnorm2x16: round(clamp(c, 0, +1) * 65535.0) 
        //! 
        //! The first component of the vector will be written to the least significant bits of the output; 
        //! the last component will be written to the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm2x16.xml">GLSL packUnorm2x16 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::uint32 packUnorm2x16(detail::tvec2<detail::float32> const & v);
        
        //! First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values. 
        //! Then, the results are packed into the returned 32-bit unsigned integer.
        //! 
        //! The conversion for component c of v to fixed point is done as follows:
        //! packUnorm4x8:	round(clamp(c, 0, +1) * 255.0)
        //! 
        //! The first component of the vector will be written to the least significant bits of the output; 
        //! the last component will be written to the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm4x8.xml">GLSL packUnorm4x8 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::uint32 packUnorm4x8(detail::tvec4<detail::float32> const & v);
        
        //! First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values. 
        //! Then, the results are packed into the returned 32-bit unsigned integer.
        //! 
        //! The conversion for component c of v to fixed point is done as follows:
        //! packSnorm4x8:	round(clamp(c, -1, +1) * 127.0) 
        //! 
        //! The first component of the vector will be written to the least significant bits of the output; 
        //! the last component will be written to the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packSnorm4x8.xml">GLSL packSnorm4x8 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::uint32 packSnorm4x8(detail::tvec4<detail::float32> const & v);

        //! First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers. 
        //! Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
        //! 
        //! The conversion for unpacked fixed-point value f to floating point is done as follows:
        //! unpackUnorm2x16: f / 65535.0 
        //! 
        //! The first component of the returned vector will be extracted from the least significant bits of the input; 
        //! the last component will be extracted from the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm2x16.xml">GLSL unpackUnorm2x16 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::tvec2<detail::float32> unpackUnorm2x16(detail::uint32 const & p);

        //! First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers. 
        //! Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
        //! 
        //! The conversion for unpacked fixed-point value f to floating point is done as follows:
        //! unpackUnorm4x8: f / 255.0
        //! 
        //! The first component of the returned vector will be extracted from the least significant bits of the input; 
        //! the last component will be extracted from the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm4x8.xml">GLSL unpackUnorm4x8 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
        detail::tvec4<detail::float32> unpackUnorm4x8(detail::uint32 const & p);
        
        //! First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers. 
        //! Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
        //! 
        //! The conversion for unpacked fixed-point value f to floating point is done as follows:
        //! unpackSnorm4x8: clamp(f / 127.0, -1, +1)
        //! 
        //! The first component of the returned vector will be extracted from the least significant bits of the input; 
        //! the last component will be extracted from the most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackSnorm4x8.xml">GLSL unpackSnorm4x8 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::tvec4<detail::float32> unpackSnorm4x8(detail::uint32 const & p);

        //! Returns a double-precision value obtained by packing the components of v into a 64-bit value. 
        //! If an IEEE 754 Inf or NaN is created, it will not signal, and the resulting floating point value is unspecified. 
        //! Otherwise, the bit- level representation of v is preserved. 
        //! The first vector component specifies the 32 least significant bits; 
        //! the second component specifies the 32 most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packDouble2x32.xml">GLSL packDouble2x32 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		double packDouble2x32(detail::tvec2<detail::uint32> const & v);
        
        //! Returns a two-component unsigned integer vector representation of v. 
        //! The bit-level representation of v is preserved. 
        //! The first component of the vector contains the 32 least significant bits of the double; 
        //! the second component consists the 32 most significant bits.
        //! 
        //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackDouble2x32.xml">GLSL unpackDouble2x32 man page</a>
        //! \li GLSL 4.00.08 specification, section 8.4
		detail::tvec2<detail::uint32> unpackDouble2x32(double const & v);

		///@}

	}//namespace packing
	}//namespace function
	}//namespace core

	using namespace core::function::packing;
}//namespace glm

#include "func_packing.inl"

#endif//glm_core_func_packing

