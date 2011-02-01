///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-07-07
// Updated : 2010-07-07
// Licence : This source is under MIT License
// File    : glm/gtx/int_10_10_10_2.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_int_10_10_10_2
#define glm_gtx_int_10_10_10_2

// Dependency:
#include "../glm.hpp"
#include "../gtx/raw_data.hpp"

namespace glm
{
	namespace gtx{
	//! GLM_GTX_int_10_10_10_2 extension: Add support for integer for core functions
	namespace int_10_10_10_2
	{
		using namespace gtx::raw_data;

		//! From GLM_GTX_int_10_10_10_2 extension.
		//! Cast a vec4 to an u_10_10_10_2.
		dword uint10_10_10_2_cast(glm::vec4 const & v);

	}//namespace integer
	}//namespace gtx
}//namespace glm

#include "int_10_10_10_2.inl"

namespace glm{using namespace gtx::int_10_10_10_2;}

#endif//glm_gtx_int_10_10_10_2
