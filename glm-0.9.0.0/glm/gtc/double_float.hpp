///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtc/double_float.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////
// Note:
// - This implementation doesn't need to redefine all build-in functions to
// support double based type.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_double_float
#define glm_gtc_double_float

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		bool main_gtc_double_float();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_double_float extension: Add support for double precision floating-point types
	namespace double_float
	{
		//! Vector of 2 single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tvec2<float>	fvec2;

		//! Vector of 3 single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tvec3<float>	fvec3;
		
		//! Vector of 4 single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tvec4<float>	fvec4;

		//! 2 * 2 matrix of single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tmat2x2<float>	fmat2;

		//! 3 * 3 matrix of single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tmat3x3<float>	fmat3;

		//! 4 * 4 matrix of single-precision floating-point numbers. 
		//! From GLM_GTC_double_float extension.
		typedef detail::tmat4x4<float>	fmat4;

	}//namespace double_float
	}//namespace gtc
}//namespace glm

#include "double_float.inl"

namespace glm{using namespace gtc::double_float;}

#endif//glm_gtc_double_float
