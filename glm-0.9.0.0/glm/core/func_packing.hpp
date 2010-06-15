///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-17
// Licence : This source is under MIT License
// File    : glm/core/func_packing.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_packing
#define glm_core_func_packing

namespace glm
{
	namespace test{
		void main_core_func_packing();
	}//namespace test

	namespace core{
	namespace function{
	//! Define packing functions from section 8.4 floating-point pack and unpack functions of GLSL 4.00.8 specification
	namespace packing
	{
		uint packUnorm2x16(vec2 const & v);
		uint packUnorm4x8(vec4 const & v);
		uint packSnorm4x8(vec4 const & v);

		vec2 unpackUnorm2x16(uint const & p);
		vec4 unpackUnorm4x8(uint const & p);
		vec4 unpackSnorm4x8(uint const & p);

		double packDouble2x32(uvec2 const & v);
		uvec2 unpackDouble2x32(double const & v);

	}//namespace packing
	}//namespace function
	}//namespace core

	using namespace core::function::packing;
}//namespace glm

#include "func_packing.inl"

#endif//glm_core_func_packing

