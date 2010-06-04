///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
// VirtreV SDK copyright matrem (matrem84.free.fr)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-09-23
// Updated : 
// Licence : This source is under MIT License
// File    : glm/ext/virtrev/equal_operator.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_virtrev_equal_operator
#define glm_virtrev_equal_operator

#include "../glm.hpp"

namespace glm
{
	namespace virtrev_glmext
	{
	//! GLM_VIRTREV_equal_operator extension: equal operator for vectors.
	namespace equal_operator
	{
		template<typename T>
		inline bool operator == (glm::detail::tvec2<T> const & v1, glm::detail::tvec2<T> const & v2)
		{
			return v1.x==v2.x && v1.y==v2.y;
		}

		template<typename T>
		inline bool operator == (glm::detail::tvec3<T> const & v1, glm::detail::tvec3<T> const & v2)
		{
			return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z;
		}

		template<typename T>
		inline bool operator == (glm::detail::tvec4<T> const & v1, glm::detail::tvec4<T> const & v2)
		{
			return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z && v1.w==v2.w;
		}

		template<typename T>
		inline bool operator != (glm::detail::tvec2<T> const & v1, glm::detail::tvec2<T> const & v2)
		{
			return v1.x!=v2.x || v1.y!=v2.y;
		}

		template<typename T>
		inline bool operator != (glm::detail::tvec3<T> const & v1, glm::detail::tvec3<T> const & v2)
		{
			return v1.x!=v2.x || v1.y!=v2.y || v1.z!=v2.z;
		}

		template<typename T>
		inline bool operator != (glm::detail::tvec4<T> const & v1, glm::detail::tvec4<T> const & v2)
		{
			return v1.x!=v2.x || v1.y!=v2.y || v1.z!=v2.z || v1.w!=v2.w;
		}
	}
	}
}

namespace glm {using namespace virtrev_glmext::equal_operator;}

#endif//glm_virtrev_equal_operator

