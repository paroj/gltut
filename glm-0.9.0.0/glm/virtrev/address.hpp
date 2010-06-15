#ifndef GLM_EXT_VIRTREV_ADDRESS_HPP
#define GLM_EXT_VIRTREV_ADDRESS_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
// Virtrev SDK copyright matrem (matrem84.free.fr)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-07
// Updated : 
// Licence : This source is under MIT License
// File    : glm/ext/virtrev/address.h
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "../glm.hpp"


namespace glm
{
	namespace virtrev_glmext
	{
	//! GLM_VIRTREV_address extension: Vector & matrix content address (T const * type pointer).
	namespace address
	{
		/** Get the const address of the vector content. */
		template<typename T>
		T const * address(detail::tvec2<T> const & vec)
		{
			return &(vec.x);
		}
		/** Get the address of the vector content. */
		template<typename T>
		T * address(detail::tvec2<T> & vec)
		{
			return &(vec.x);
		}

		/** Get the const address of the vector content. */
		template<typename T>
		T const * address(detail::tvec3<T> const & vec)
		{
			return &(vec.x);
		}
		/** Get the address of the vector content. */
		template<typename T>
		T * address(detail::tvec3<T>  & vec)
		{
			return &(vec.x);
		}
		
		/** Get the const address of the vector content. */
		template<typename T>
		T const * address(detail::tvec4<T> const & vec)
		{
			return &(vec.x);
		}
		/** Get the address of the vector content. */
		template<typename T>
		T * address(detail::tvec4<T> & vec)
		{
			return &(vec.x);
		}

		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat2x2<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat2x2<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat3x3<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat3x3<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat4x4<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat4x4<T> & mat)
		{
			return &(mat[0].x);
		}

		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat2x3<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat2x3<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat3x2<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat3x2<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat2x4<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat2x4<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat4x2<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat4x2<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat3x4<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat3x4<T> & mat)
		{
			return &(mat[0].x);
		}
		
		/** Get the const address of the matrix content. */
		template<typename T>
		T const * address(detail::tmat4x3<T> const & mat)
		{
			return &(mat[0].x);
		}
		/** Get the address of the matrix content. */
		template<typename T>
		T * address(detail::tmat4x3<T> & mat)
		{
			return &(mat[0].x);
		}
	}
	}
}

namespace glm{using namespace virtrev_glmext::address;}

#endif//GLM_EXT_VIRTREV_ADDRESS_HPP

