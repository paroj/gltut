///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/epsilon.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
// - GLM_GTC_quaternion
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_epsilon
#define glm_gtx_epsilon

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_epsilon extension included")
#endif

namespace glm{
namespace gtx{
namespace epsilon ///< GLM_GTX_epsilon extension: Comparison functions for a user defined epsilon values.
{
	/// \addtogroup gtx_epsilon
	///@{

	//! Returns the component-wise compare of |x - y| < epsilon.
	//! From GLM_GTX_epsilon extension.
	template <typename genTypeT, typename genTypeU> 
	bool equalEpsilon(
		genTypeT const & x, 
		genTypeT const & y, 
		genTypeU const & epsilon);
		
	//! Returns the component-wise compare of |x - y| >= epsilon.
	//! From GLM_GTX_epsilon extension.
	template <typename genTypeT, typename genTypeU>
	bool notEqualEpsilon(
		genTypeT const & x, 
		genTypeT const & y, 
		genTypeU const & epsilon);

	///@}
}//namespace epsilon
}//namespace gtx
}//namespace glm

#include "epsilon.inl"

namespace glm{using namespace gtx::epsilon;}

#endif//glm_gtx_epsilon
