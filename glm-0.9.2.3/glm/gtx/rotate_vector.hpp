///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-11-02
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/rotate_vector.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_rotate_vector
#define glm_gtx_rotate_vector

// Dependency:
#include "../glm.hpp"
#include "../gtx/transform.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_rotate_vector extension included")
#endif

namespace glm{
namespace gtx{
namespace rotate_vector ///< GLM_GTX_rotate_vector extension: Function to directly rotate a vector
{
	using namespace transform;

	/// \addtogroup gtx_rotate_vector
	/// @{

	//! Rotate a two dimensional vector.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec2<T> rotate(
        detail::tvec2<T> const & v, 
		T const & angle);
		
	//! Rotate a three dimensional vector around an axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec3<T> rotate(
        detail::tvec3<T> const & v, 
		T const & angle, 
        detail::tvec3<T> const & normal);
		
	//! Rotate a four dimensional vector around an axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec4<T> rotate(
        detail::tvec4<T> const & v, 
        T const & angle, 
		detail::tvec3<T> const & normal);
		
	//! Rotate a three dimensional vector around the X axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec3<T> rotateX(
        detail::tvec3<T> const & v, 
		T const & angle);

	//! Rotate a three dimensional vector around the Y axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec3<T> rotateY(
		detail::tvec3<T> const & v, 
		T const & angle);
		
	//! Rotate a three dimensional vector around the Z axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec3<T> rotateZ(
        detail::tvec3<T> const & v, 
		T const & angle);
		
	//! Rotate a four dimentionnals vector around the X axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec4<T> rotateX(
        detail::tvec4<T> const & v, 
		T const & angle);
		
	//! Rotate a four dimensional vector around the X axis.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec4<T> rotateY(
        detail::tvec4<T> const & v, 
		T const & angle);
		
	//! Rotate a four dimensional vector around the X axis. 
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tvec4<T> rotateZ(
        detail::tvec4<T> const & v, 
		T const & angle);
		
	//! Build a rotation matrix from a normal and a up vector.
	//! From GLM_GTX_rotate_vector extension.
	template <typename T> 
	detail::tmat4x4<T> orientation(
        detail::tvec3<T> const & Normal, 
        detail::tvec3<T> const & Up);

	/// @}
}//namespace rotate_vector
}//namespace gtx
}//namespace glm

#include "rotate_vector.inl"

namespace glm{using namespace gtx::rotate_vector;}

#endif//glm_gtx_rotate_vector
