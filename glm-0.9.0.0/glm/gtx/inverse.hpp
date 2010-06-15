///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-09-30
// Licence : This source is under MIT License
// File    : glm/gtx/inverse.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_inverse
#define glm_gtx_inverse

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_operation.hpp"

namespace glm{
namespace gtx{
//! GLM_GTX_inverse extension: Inverse matrix functions
namespace inverse
{
	using namespace gtc::matrix_operation;

	//! Fast matrix inverse for affine matrix.
	//! From GLM_GTX_inverse extension.
	template <typename genType> 
	genType affineInverse(genType const & m);
 
}//namespace inverse
}//namespace gtx
}//namespace glm

#include "inverse.inl"

namespace glm{using namespace gtx::inverse;}

#endif//glm_gtx_inverse
