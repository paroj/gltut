///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-03-06
// Licence : This source is under MIT License
// File    : glm/gtx/projection.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_projection
#define glm_gtx_projection

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		void main_gtx_projection();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_projection extension: Projection of a vector to other one
	namespace projection
	{
		//! Projects x on Normal.
		//! From GLM_GTX_projection extension.
		template <typename T> 
		detail::tvec2<T> proj(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & Normal);
		
		//! Projects x on Normal.
		//! From GLM_GTX_projection extension.
		template <typename T> 
		detail::tvec3<T> proj(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & Normal);

		//! Projects x on Normal.
		//! From GLM_GTX_projection extension.
		template <typename T> 
		detail::tvec4<T> proj(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & Normal);
		
	}//namespace projection
    }//namespace gtx
}//namespace glm

#include "projection.inl"

namespace glm{using namespace gtx::projection;}

#endif//glm_gtx_projection
