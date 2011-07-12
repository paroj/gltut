///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Based on the work of Stefan Gustavson and Ashima Arts on "webgl-noise": 
// https://github.com/ashima/webgl-noise 
// Following Stefan Gustavson's paper "Simplex noise demystified": 
// http://www.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-21
// Updated : 2011-04-21
// Licence : This source is under MIT License
// File    : glm/gtx/noise.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_noise
#define glm_gtx_noise

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_noise extension included")
#endif

namespace glm{
namespace gtx{
namespace noise	///< GLM_GTX_noise extension: Comparison functions for a user defined epsilon values.
{
	/// \addtogroup gtx_noise
	/// @{

	//! Classic perlin noise.
	//! From GLM_GTX_noise extension.
	template <typename T, template<typename> class vecType> 
    T perlin(
		vecType<T> const & p);
		
	//! Periodic perlin noise.
	//! From GLM_GTX_noise extension.
	template <typename T, template<typename> class vecType> 
    T perlin(
		vecType<T> const & p, 
		vecType<T> const & rep);

	//! Simplex noise.
	//! From GLM_GTX_noise extension.
	template <typename T, template<typename> class vecType> 
    T simplex(
		vecType<T> const & p);

	/// @}
}//namespace noise
}//namespace gtx
}//namespace glm

#include "noise.inl"

namespace glm{using namespace gtx::noise;}

#endif//glm_gtx_noise
