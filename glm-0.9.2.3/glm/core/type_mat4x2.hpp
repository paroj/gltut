///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-10-01
// Updated : 2010-02-11
// Licence : This source is under MIT License
// File    : glm/core/type_mat4x2.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat4x2
#define glm_core_type_mat4x2

#include "type_mat.hpp"

namespace glm{
namespace detail
{
	template <typename T> struct tvec1;
	template <typename T> struct tvec2;
	template <typename T> struct tvec3;
	template <typename T> struct tvec4;
	template <typename T> struct tmat2x2;
	template <typename T> struct tmat2x3;
	template <typename T> struct tmat2x4;
	template <typename T> struct tmat3x2;
	template <typename T> struct tmat3x3;
	template <typename T> struct tmat3x4;
	template <typename T> struct tmat4x2;
	template <typename T> struct tmat4x3;
	template <typename T> struct tmat4x4;

	//! \brief Template for 4 columns and 2 rows matrix of floating-point numbers.
	//! \ingroup core_template
	template <typename T> 
	struct tmat4x2
	{
		enum ctor{null};
		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec2<T> col_type;
		typedef tvec4<T> row_type;
		static GLM_FUNC_DECL size_type col_size();
		static GLM_FUNC_DECL size_type row_size();

		typedef tmat4x2<T> type;
		typedef tmat2x4<T> transpose_type;

	private:
		// Data 
		col_type value[4];

	public:
		// Constructors
		GLM_FUNC_DECL tmat4x2();
		GLM_FUNC_DECL tmat4x2(tmat4x2 const & m);

		GLM_FUNC_DECL explicit tmat4x2(
			ctor Null);
		GLM_FUNC_DECL explicit tmat4x2(
			value_type const & x);
		GLM_FUNC_DECL explicit tmat4x2(
			value_type const & x0, value_type const & y0,
			value_type const & x1, value_type const & y1,
			value_type const & x2, value_type const & y2,
			value_type const & x3, value_type const & y3);
		GLM_FUNC_DECL explicit tmat4x2(
			col_type const & v0, 
			col_type const & v1,
			col_type const & v2,
			col_type const & v3);
            
		//////////////////////////////////////
		// Conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat4x2(
            U const & x);
			
		template 
        <
            typename X1, typename Y1, 
            typename X2, typename Y2, 
            typename X3, typename Y3,
            typename X4, typename Y4
        > 
		GLM_FUNC_DECL explicit tmat4x2(
            X1 const & x1, Y1 const & y1, 
            X2 const & x2, Y2 const & y2,
            X3 const & x3, Y3 const & y3,
            X4 const & x4, Y4 const & y4);
			
		template <typename V1, typename V2, typename V3, typename V4> 
		GLM_FUNC_DECL explicit tmat4x2(
            tvec2<V1> const & v1, 
            tvec2<V2> const & v2,
            tvec2<V3> const & v3,
            tvec2<V4> const & v4);
            
		// Matrix conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat4x2(tmat4x2<U> const & m);
			
		GLM_FUNC_DECL explicit tmat4x2(tmat2x2<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat3x3<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat4x4<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat2x3<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat3x2<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat2x4<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat4x3<T> const & x);
		GLM_FUNC_DECL explicit tmat4x2(tmat3x4<T> const & x);

		// Accesses
		GLM_FUNC_DECL col_type & operator[](size_type i);
		GLM_FUNC_DECL col_type const & operator[](size_type i) const;

		// Unary updatable operators
		GLM_FUNC_DECL tmat4x2<T>& operator=  (tmat4x2<T> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator=  (tmat4x2<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator+= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator+= (tmat4x2<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator-= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator-= (tmat4x2<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator*= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator*= (tmat4x2<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x2<T>& operator/= (U const & s);

		GLM_FUNC_DECL tmat4x2<T>& operator++ ();
		GLM_FUNC_DECL tmat4x2<T>& operator-- ();
	};

	// Binary operators
	template <typename T> 
	tmat4x2<T> operator+ (
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s);
	    
	template <typename T> 
	tmat4x2<T> operator+ (
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2);
	    
	template <typename T> 
	tmat4x2<T> operator- (
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s);

	template <typename T> 
	tmat4x2<T> operator- (
		tmat4x2<T> const & m1, 
		tmat4x2<T> const & m2);

	template <typename T> 
	tmat4x2<T> operator* (
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s);

	template <typename T> 
	tmat4x2<T> operator* (
		typename tmat4x2<T>::value_type const & s, 
		tmat4x2<T> const & m);

	template <typename T>
	typename tmat4x2<T>::col_type operator* (
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::row_type const & v);

	template <typename T> 
	typename tmat4x2<T>::row_type operator* (
		typename tmat4x2<T>::col_type const & v, 
		tmat4x2<T> const & m);

	template <typename T> 
	tmat2x2<T> operator* (
		tmat4x2<T> const & m1, 
		tmat2x4<T> const & m2);

	template <typename T> 
	tmat4x2<T> operator/ (
		tmat4x2<T> const & m, 
		typename tmat4x2<T>::value_type const & s);

	template <typename T> 
	tmat4x2<T> operator/ (
		typename tmat4x2<T>::value_type const & s, 
		tmat4x2<T> const & m);

	// Unary constant operators
	template <typename T> 
	tmat4x2<T> const operator-  (
		tmat4x2<T> const & m);

	template <typename T> 
	tmat4x2<T> const operator-- (
		tmat4x2<T> const & m, 
		int);

	template <typename T> 
	tmat4x2<T> const operator++ (
		tmat4x2<T> const & m, 
		int);

} //namespace detail

namespace core{
namespace type{
namespace precision
{
	//! 4 columns of 2 components matrix of low precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x2<lowp_float>		lowp_mat4x2;

	//! 4 columns of 2 components matrix of medium precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x2<mediump_float>	mediump_mat4x2;

	//! 4 columns of 2 components matrix of high precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x2<highp_float>	highp_mat4x2;

}//namespace precision
}//namespace type
}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat4x2.inl"
#endif

#endif //glm_core_type_mat4x2
