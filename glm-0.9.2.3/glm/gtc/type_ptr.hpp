///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-06
// Updated : 2010-04-30
// Licence : This source is under MIT License
// File    : glm/gtc/type_ptr.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtc_type_ptr
#define glm_gtc_type_ptr

// Dependency:
#include "../glm.hpp"
#include <cstring>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_type_ptr extension included")
#endif

namespace glm{
namespace gtc{
namespace type_ptr ///< GLM_GTC_type_ptr extension: Get access to vectors & matrices value type address.
{ 

	/// \addtogroup gtc_type_ptr
	///@{

	//! Get the const address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tvec2<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Get the address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tvec2<T> & vec
	)
	{
		return &(vec.x);
	}

	//! Get the const address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tvec3<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Get the address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tvec3<T> & vec
	)
	{
		return &(vec.x);
	}
		
	//! Get the const address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(	
		detail::tvec4<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Get the address of the vector content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(	
		detail::tvec4<T> & vec
	)
	{
		return &(vec.x);
	}

	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x3<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat4x4<T> & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x3<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x4<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(	
		detail::tmat4x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x4<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Get the const address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Get the address of the matrix content.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr(detail::tmat4x3<T> & mat)
	{
		return &(mat[0].x);
	}

	//! Build a vector from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> make_vec2(T const * const ptr)
	{
		detail::tvec2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec2<T>));
		return Result;
	}

	//! Build a vector from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> make_vec3(T const * const ptr)
	{
		detail::tvec3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec3<T>));
		return Result;
	}

	//! Build a vector from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> make_vec4(T const * const ptr)
	{
		detail::tvec4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec4<T>));
		return Result;
	}

	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> make_mat2x2(T const * const ptr)
	{
		detail::tmat2x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x3<T> make_mat2x3(T const * const ptr)
	{
		detail::tmat2x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x3<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x4<T> make_mat2x4(T const * const ptr)
	{
		detail::tmat2x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x4<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x2<T> make_mat3x2(T const * const ptr)
	{
		detail::tmat3x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> make_mat3x3(T const * const ptr)
	{
		detail::tmat3x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x3<T>));
		return Result;
	}

	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x4<T> make_mat3x4(T const * const ptr)
	{
		detail::tmat3x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x4<T>));
		return Result;
	}

        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x2<T> make_mat4x2(T const * const ptr)
	{
		detail::tmat4x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x3<T> make_mat4x3(T const * const ptr)
	{
		detail::tmat4x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x3<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> make_mat4x4(T const * const ptr)
	{
		detail::tmat4x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x4<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> make_mat2(T const * const ptr)
	{
		return make_mat2x2(ptr);
	}
        
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> make_mat3(T const * const ptr)
	{
		return make_mat3x3(ptr);
	}
		
	//! Build a matrix from a pointer.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> make_mat4(T const * const ptr)
	{
		return make_mat4x4(ptr);
	}
        
	///@}

}//namespace type_ptr
}//namespace gtc
}//namespace glm

#include "type_ptr.inl"

namespace glm{using namespace gtc::type_ptr;}

#endif//glm_gtx_type_ptr

