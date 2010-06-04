///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-06-22
// Updated : 2008-10-27
// Licence : This source is under MIT License
// File    : glm/gtx/comparison.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_comparison
#define glm_gtx_comparison

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		void main_gtx_comparison();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_comparison extension: Defined comparison operators for vectors.
	namespace comparison{

		//! Define == operator for vectors
		//! From GLM_GTX_comparison extension.
		template <typename vecType>
		bool operator== (vecType const & x, vecType const & y);

		//! Define != operator for vectors
		//! From GLM_GTX_comparison extension.
		template <typename vecType>
		bool operator!= (vecType const & x, vecType const & y);

	}//namespace comparison
	}//namespace gtx
}//namespace glm

#include "comparison.inl"

namespace glm{using namespace gtx::comparison;}

#endif//glm_gtx_comparison
