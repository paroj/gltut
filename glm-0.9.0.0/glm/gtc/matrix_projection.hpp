///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2010-02-07
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_projection.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_matrix_operation
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_matrix_projection
#define glm_gtc_matrix_projection

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_operation.hpp"

namespace glm
{
   	namespace test{
		bool main_gtc_matrix_projection();
	}//namespace test

    namespace gtc{
	//! GLM_GTC_matrix_projection: Varius ways to build and operate on projection matrices
    namespace matrix_projection
    {
		using namespace gtc::matrix_operation;

		//! Creates a matrix for projecting two-dimensional coordinates onto the screen.
		//! From GLM_GTC_matrix_projection extension.
        template <typename T> 
		detail::tmat4x4<T> ortho(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top);

		//! Creates a matrix for an orthographic parallel viewing volume.
		//! From GLM_GTC_matrix_projection extension.
		template <typename T> 
		detail::tmat4x4<T> ortho(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top, 
			T const & zNear, 
			T const & zFar);

		//! Creates a frustum matrix.
		//! From GLM_GTC_matrix_projection extension.
		template <typename T> 
		detail::tmat4x4<T> frustum(
			T const & left, 
			T const & right, 
			T const & bottom, 
			T const & top, 
			T const & nearVal, 
			T const & farVal);

		//! Creates a matrix for a symetric perspective-view frustum.
		//! From GLM_GTC_matrix_projection extension.
		template <typename T> 
		detail::tmat4x4<T> perspective(
			T const & fovy, 
			T const & aspect, 
			T const & zNear, 
			T const & zFar);

		//! Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
		//! From GLM_GTC_matrix_projection extension.
		template <typename T, typename U> 
		detail::tvec3<T> project(
			detail::tvec3<T> const & obj, 
			detail::tmat4x4<T> const & model, 
			detail::tmat4x4<T> const & proj, 
			detail::tvec4<U> const & viewport);

		//! Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
		//! From GLM_GTC_matrix_projection extension.
		template <typename T, typename U> 
		detail::tvec3<T> unProject(
			detail::tvec3<T> const & win, 
			detail::tmat4x4<T> const & model, 
			detail::tmat4x4<T> const & proj, 
			detail::tvec4<U> const & viewport);

    }//namespace matrix_projection
    }//namespace gtc
}//namespace glm

#include "matrix_projection.inl"

namespace glm{using namespace gtc::matrix_projection;}

#endif//glm_gtc_matrix_projection
