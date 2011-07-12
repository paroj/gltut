///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-01-25
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/spline.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_spline
#define glm_gtx_spline

// Dependency:
#include "../glm.hpp"
#include "../gtx/optimum_pow.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_spline extension included")
#endif

namespace glm{
namespace gtx{
namespace spline ///< GLM_GTX_spline extension: Spline functions
{
	using namespace gtx::optimum_pow;

	/// \addtogroup gtx_spline
	/// @{

	//! Return a point from a catmull rom curve.
	//! From GLM_GTX_spline extension.
	template <typename genType> 
	genType catmullRom(
		genType const & v1, 
		genType const & v2, 
		genType const & v3, 
		genType const & v4, 
		typename genType::value_type const & s);
		
	//! Return a point from a hermite curve.
	//! From GLM_GTX_spline extension.
    template <typename genType> 
	genType hermite(
		genType const & v1, 
		genType const & t1, 
		genType const & v2, 
		genType const & t2, 
		typename genType::value_type const & s);
		
    //! Return a point from a cubic curve. 
	//! From GLM_GTX_spline extension.
	template <typename genType> 
	genType cubic(
		genType const & v1, 
		genType const & v2, 
		genType const & v3, 
		genType const & v4, 
		typename genType::value_type const & s);

	/// @}
}//namespace spline
}//namespace gtx
}//namespace glm

#include "spline.inl"

namespace glm{using namespace gtx::spline;}

#endif//glm_gtx_spline

