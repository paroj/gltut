///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_transform.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_matrix_operation
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_transform
#define glm_gtc_matrix_transform

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_operation.hpp"

namespace glm
{
	namespace test{
		bool main_gtc_matrix_transform();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_matrix_transform extension: Add transformation matrices
	namespace matrix_transform
	{
		using namespace gtc::matrix_operation;

		//! Builds a translation 4 * 4 matrix created from a vector of 3 components.
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> translate(
			detail::tmat4x4<T> const & m,
			detail::tvec3<T> const & v);
		
		//! Builds a rotation 4 * 4 matrix created from an axis vector and an angle expressed in degrees. 
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> rotate(
			detail::tmat4x4<T> const & m,
			T const & angle, 
			detail::tvec3<T> const & v);

		//! Builds a scale 4 * 4 matrix created from 3 scalars. 
		//! From GLM_GTC_matrix_transform extension.
		template <typename T> 
		detail::tmat4x4<T> scale(
			detail::tmat4x4<T> const & m,
			detail::tvec3<T> const & v);

	}//namespace matrix_transform
	}//namespace gtc
}//namespace glm

#include "matrix_transform.inl"

namespace glm{using namespace gtc::matrix_transform;}

#endif//glm_gtc_matrix_transform
