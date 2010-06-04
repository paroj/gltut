///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-09
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/fast_exponential.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_half
// - GLM_GTX_double
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_fast_exponential
#define glm_gtx_fast_exponential

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/double_float.hpp"

namespace glm
{
   	namespace test{
		void main_gtx_fast_exponential();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_fast_exponential extension: Fast but less accurate implementations of exponential based functions.
	namespace fast_exponential
	{
		using namespace gtc::half_float;
		using namespace gtc::double_float;

		//! Faster than the common pow function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename valType> 
		valType fastPow(
			valType const & x, 
			valType const & y);

		//! Faster than the common pow function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T, typename U> 
		T fastPow(
			const T& x, 
			const U& y);
		
		//! Faster than the common exp function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastExp(const T& x);
		
		//! Faster than the common log function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLog(const T& x);

		//! Faster than the common exp2 function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastExp2(const T& x);
		
		//! Faster than the common log2 function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLog2(const T& x);

		//! Faster than the common ln function but less accurate.
		//! From GLM_GTX_fast_exponential extension.
		template <typename T> 
		T fastLn(const T& x);

	}//namespace fast_exponential
	}//namespace gtx
}//namespace glm

#include "fast_exponential.inl"

namespace glm{using namespace gtx::fast_exponential;}

#endif//glm_gtx_fast_exponential
