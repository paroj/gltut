///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-02-20
// Updated : 2010-02-20
// Licence : This source is under MIT License
// File    : glm/gtc/swizzle.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_swizzle
#define glm_gtc_swizzle

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		void main_gtc_swizzle();
	}//namespace test

	namespace gtc{
	//! GLM_GTC_swizzle extension
	namespace swizzle{

		template <typename T>
		T swizzle(	
			detail::tvec4<T> const & v,
			comp x);

		template <typename T>
		detail::tvec2<T> swizzle(
			detail::tvec4<T> const & v,
			comp x, comp y);

		template <typename T>
		detail::tvec3<T> swizzle(
			detail::tvec4<T> const & v,
			comp x, comp y, comp z);

		template <typename T>
		inline detail::tref4<T> swizzle(
			detail::tvec4<T> const & v,
			comp x, comp y, comp z, comp w);

	}//namespace swizzle
	}//namespace gtc
}//namespace glm

#include "swizzle.inl"

namespace glm{using namespace gtc::swizzle;}

#endif//glm_gtc_swizzle
