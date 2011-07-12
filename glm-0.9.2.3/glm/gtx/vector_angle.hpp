///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-30
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/vector_angle.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_quaternion
// - GLM_GTX_epsilon
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_vector_angle
#define glm_gtx_vector_angle

// Dependency:
#include "../glm.hpp"
#include "../gtx/epsilon.hpp"
#include "../gtx/quaternion.hpp"
#include "../gtx/rotate_vector.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vector_angle extension included")
#endif

namespace glm{
namespace gtx{
namespace vector_angle ///< GLM_GTX_vector_angle extension: Compute angle between vectors
{
	using namespace quaternion;
	using namespace epsilon;

	/// \addtogroup gtx_vector_angle
	///@{

	//! Returns the absolute angle between two vectors
	//! Parameters need to be normalized.
	//! From GLM_GTX_vector_angle extension
	template <typename vecType> 
	GLM_FUNC_QUALIFIER typename vecType::value_type angle(
		vecType const & x, 
		vecType const & y);

	//! Returns the oriented angle between two 2d vectors 
	//! Parameters need to be normalized.
	//! From GLM_GTX_vector_angle extension.
	template <typename T> 
	GLM_FUNC_QUALIFIER T orientedAngle(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y);

	//! Returns the oriented angle between two 3d vectors based from a reference axis.
	//! Parameters need to be normalized.
	//! From GLM_GTX_vector_angle extension.
	template <typename T>
	GLM_FUNC_QUALIFIER T orientedAngle(
		detail::tvec3<T> const & x,
		detail::tvec3<T> const & y,
		detail::tvec3<T> const & ref);

	/// @}
}// namespace vector_angle
}// namespace gtx
}// namespace glm

#include "vector_angle.inl"

namespace glm{using namespace gtx::vector_angle;}

#endif//glm_gtx_vector_angle
