///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
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

namespace glm
{
	namespace gtx{
	//! GLM_GTX_rotate_vector extension: Function to directly rotate a vector
	namespace rotate_vector
	{
		using namespace transform;

		//! Rotate a two dimentionnals vector.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec2<T> rotate(
			const detail::tvec2<T>& v, 
			T angle);
		
		//! Rotate a three dimentionnals vector around an axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec3<T> rotate(
			const detail::tvec3<T>& v, 
			T angle, 
			const detail::tvec3<T>& normal);
		
		//! Rotate a four dimentionnals vector around an axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec4<T> rotate(
			const detail::tvec4<T>& v, T angle, 
			const detail::tvec3<T>& normal);
		
		//! Rotate a three dimentionnals vector around the X axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec3<T> rotateX(
			const detail::tvec3<T>& v, 
			T angle);

		//! Rotate a three dimentionnals vector around the Y axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec3<T> rotateY(
			const detail::tvec3<T>& v, 
			T angle);
		
		//! Rotate a three dimentionnals vector around the Z axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec3<T> rotateZ(
			const detail::tvec3<T>& v, 
			T angle);
		
		//! Rotate a four dimentionnals vector around the X axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec4<T> rotateX(
			const detail::tvec4<T>& v, 
			T angle);
		
		//! Rotate a four dimentionnals vector around the X axis.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec4<T> rotateY(
			const detail::tvec4<T>& v, 
			T angle);
		
		//! Rotate a four dimentionnals vector around the X axis. 
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tvec4<T> rotateZ(
			const detail::tvec4<T>& v, 
			T angle);
		
		//! Build a rotation matrix from a normal and a up vector.
		//! From GLM_GTX_rotate_vector extension.
		template <typename T> 
		detail::tmat4x4<T> orientation(
			const detail::tvec3<T>& Normal, 
			const detail::tvec3<T>& Up);
		
	}//namespace rotate_vector
	}//namespace gtx
}//namespace glm

#include "rotate_vector.inl"

namespace glm{using namespace gtx::rotate_vector;}

#endif//glm_gtx_rotate_vector
