///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-04
// Updated : 2010-02-11
// Licence : This source is under MIT License
// File    : glm/core/type_mat4x3.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat4x3
#define glm_core_type_mat4x3

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

	//! \brief Template for 4 columns and 3 rows matrix of floating-point numbers.
	//! \ingroup core_template
	template <typename T> 
	struct tmat4x3
	{
		enum ctor{null};
		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec3<T> col_type;
		typedef tvec4<T> row_type;
		static GLM_FUNC_DECL size_type col_size();
		static GLM_FUNC_DECL size_type row_size();

		typedef tmat4x3<T> type;
		typedef tmat3x4<T> transpose_type;

	private:
		// Data 
		col_type value[4];

	public:
		// Constructors
		GLM_FUNC_DECL tmat4x3();
		GLM_FUNC_DECL tmat4x3(tmat4x3 const & m);

		GLM_FUNC_DECL explicit tmat4x3(
			ctor Null);
		GLM_FUNC_DECL explicit tmat4x3(
			value_type const & x);
		GLM_FUNC_DECL explicit tmat4x3(
			value_type const & x0, value_type const & y0, value_type const & z0,
			value_type const & x1, value_type const & y1, value_type const & z1,
			value_type const & x2, value_type const & y2, value_type const & z2,
			value_type const & x3, value_type const & y3, value_type const & z3);
		GLM_FUNC_DECL explicit tmat4x3(
			col_type const & v0, 
			col_type const & v1,
			col_type const & v2,
            col_type const & v3);
            
		//////////////////////////////////////
		// Conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat4x3(
            U const & x);
			
		template <
            typename X1, typename Y1, typename Z1, 
            typename X2, typename Y2, typename Z2, 
            typename X3, typename Y3, typename Z3, 
            typename X4, typename Y4, typename Z4> 
		GLM_FUNC_DECL explicit tmat4x3(
            X1 const & x1, Y1 const & y1, Z1 const & z1, 
            X2 const & x2, Y2 const & y2, Z2 const & z2, 
            X3 const & x3, Y3 const & y3, Z3 const & z3, 
            X4 const & x4, Y4 const & y4, Z4 const & z4);
			
		template <typename V1, typename V2, typename V3, typename V4> 
		GLM_FUNC_DECL explicit tmat4x3(
            tvec3<V1> const & v1, 
            tvec3<V2> const & v2,
            tvec3<V3> const & v3,
            tvec3<V4> const & v4);
            
		// Matrix conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat4x3(tmat4x3<U> const & m);
			
		GLM_FUNC_DECL explicit tmat4x3(tmat2x2<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat3x3<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat4x4<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat2x3<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat3x2<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat2x4<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat4x2<T> const & x);
		GLM_FUNC_DECL explicit tmat4x3(tmat3x4<T> const & x);

		// Accesses
		col_type & operator[](size_type i);
		col_type const & operator[](size_type i) const;

		// Unary updatable operators
		GLM_FUNC_DECL tmat4x3<T> & operator=  (tmat4x3<T> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator=  (tmat4x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator+= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator+= (tmat4x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator-= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator-= (tmat4x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator*= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator*= (tmat4x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat4x3<T> & operator/= (U const & s);

		GLM_FUNC_DECL tmat4x3<T> & operator++ ();
		GLM_FUNC_DECL tmat4x3<T> & operator-- ();
	};

	// Binary operators
	template <typename T> 
	tmat4x3<T> operator+ (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s);
	    
	template <typename T> 
	tmat4x3<T> operator+ (
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2);
	    
	template <typename T> 
	tmat4x3<T> operator- (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s);

	template <typename T> 
	tmat4x3<T> operator- (
		tmat4x3<T> const & m1, 
		tmat4x3<T> const & m2);

	template <typename T> 
	tmat4x3<T> operator* (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s);

	template <typename T> 
	tmat4x3<T> operator* (
		typename tmat4x3<T>::value_type const & s, 
		tmat4x3<T> const & m);

	template <typename T>
	typename tmat4x3<T>::col_type operator* (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::row_type const & v);

	template <typename T> 
	typename tmat4x3<T>::row_type operator* (
		typename tmat4x3<T>::col_type const & v, 
		tmat4x3<T> const & m);

	template <typename T> 
	tmat3x3<T> operator* (
		tmat4x3<T> const & m1, 
		tmat3x4<T> const & m2);

	template <typename T> 
	tmat4x3<T> operator/ (
		tmat4x3<T> const & m, 
		typename tmat4x3<T>::value_type const & s);

	template <typename T> 
	tmat4x3<T> operator/ (
		typename tmat4x3<T>::value_type const & s, 
		tmat4x3<T> const & m);

	// Unary constant operators
	template <typename T> 
	tmat4x3<T> const operator- (
		tmat4x3<T> const & m);

	template <typename T> 
	tmat4x3<T> const operator-- (
		tmat4x3<T> const & m, 
		int);

	template <typename T> 
	tmat4x3<T> const operator++ (
		tmat4x3<T> const & m, 
		int);

}//namespace detail

namespace core{
namespace type{
namespace precision
{
	//! 4 columns of 3 components matrix of low precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x3<lowp_float>		lowp_mat4x3;

	//! 4 columns of 3 components matrix of medium precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x3<mediump_float>	mediump_mat4x3;

	//! 4 columns of 3 components matrix of high precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	//! \ingroup core_precision
	typedef detail::tmat4x3<highp_float>	highp_mat4x3;

}//namespace precision
}//namespace type
}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat4x3.inl"
#endif //GLM_EXTERNAL_TEMPLATE

#endif//glm_core_type_mat4x3
