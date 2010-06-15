///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2009 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-04-23
// Licence : This source is under MIT License
// File    : glm/gtx/determinant.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_determinant
#define glm_gtx_determinant

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_operation.hpp"

namespace glm
{
	namespace test{
		void main_gtx_determinant();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_determinant extension: Compute the determinant of a matrix
	namespace determinant
	{
		using namespace gtc::matrix_operation;

	}//namespace determinant
	}//namespace gtx
}//namespace glm

#define GLM_GTX_determinant namespace gtx::determinant
#ifndef GLM_GTX_GLOBAL
namespace glm {using GLM_GTX_determinant;}
#endif//GLM_GTC_GLOBAL

#include "determinant.inl"

#endif//glm_gtx_determinant
