///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_projection.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_matrix_projection
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_projection
#define glm_gtx_matrix_projection

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_projection.hpp"

namespace glm
{
   	namespace test{
		void main_gtx_matrix_projection();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_matrix_projection: Varius ways to build and operate on projection matrices
    namespace matrix_projection
    {
		using namespace gtc::matrix_projection;

		//! Builds a perspective projection matrix based on a field of view
		//! From GLM_GTX_matrix_projection extension.
		template <typename valType> 
		detail::tmat4x4<valType> perspectiveFov(
			valType const & fov, 
			valType const & width, 
			valType const & height, 
			valType const & zNear, 
			valType const & zFar);

		//! Creates a matrix for a symmetric perspective-view frustum with far plane at infinite .
		//! From GLM_GTX_matrix_projection extension.
        template <typename T> 
		detail::tmat4x4<T> infinitePerspective(
			T fovy, T aspect, T zNear);

		//! Creates a matrix for a symmetric perspective-view frustum with far plane at infinite for graphics hardware that doesn't support depth clamping.
		//! From GLM_GTX_matrix_projection extension.
        template <typename T> 
		detail::tmat4x4<T> tweakedInfinitePerspective(
			T fovy, T aspect, T zNear);

    }//namespace matrix_projection
    }//namespace gtx
}//namespace glm

#include "matrix_projection.inl"

namespace glm{using namespace gtx::matrix_projection;}

#endif//glm_gtx_matrix_projection
