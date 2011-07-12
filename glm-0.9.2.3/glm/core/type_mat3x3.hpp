///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-01-27
// Updated : 2010-02-03
// Licence : This source is under MIT License
// File    : glm/core/type_mat3x3.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat3x3
#define glm_core_type_mat3x3

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

	//! \brief Template for 3 * 3 matrix of floating-point numbers.
	//! \ingroup core_template
	template <typename T> 
	struct tmat3x3
	{
		enum ctor{null};
		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec3<T> col_type;
		typedef tvec3<T> row_type;
		static GLM_FUNC_DECL size_type col_size();
		static GLM_FUNC_DECL size_type row_size();

		typedef tmat3x3<T> type;
		typedef tmat3x3<T> transpose_type;

	public:
		// Implementation detail
		GLM_FUNC_DECL tmat3x3<T> _inverse() const;

	private:
		// Data
		col_type value[3];

	public:
		// Constructors
		GLM_FUNC_DECL tmat3x3();
		GLM_FUNC_DECL tmat3x3(tmat3x3 const & m);

		GLM_FUNC_DECL explicit tmat3x3(
			ctor Null);
		GLM_FUNC_DECL explicit tmat3x3(
			value_type const & s);
		GLM_FUNC_DECL explicit tmat3x3(
			value_type const & x0, value_type const & y0, value_type const & z0,
			value_type const & x1, value_type const & y1, value_type const & z1,
			value_type const & x2, value_type const & y2, value_type const & z2);
		GLM_FUNC_DECL explicit tmat3x3(
			col_type const & v0, 
			col_type const & v1,
			col_type const & v2);

		//////////////////////////////////////
		// Conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat3x3(
            U const & x);
			
		template 
        <
            typename X1, typename Y1, typename Z1, 
            typename X2, typename Y2, typename Z2, 
            typename X3, typename Y3, typename Z3
        > 
		GLM_FUNC_DECL explicit tmat3x3(
            X1 const & x1, Y1 const & y1, Z1 const & z1, 
            X2 const & x2, Y2 const & y2, Z2 const & z2, 
            X3 const & x3, Y3 const & y3, Z3 const & z3);
			
		template <typename V1, typename V2, typename V3> 
		GLM_FUNC_DECL explicit tmat3x3(
            tvec3<V1> const & v1, 
            tvec3<V2> const & v2,
            tvec3<V3> const & v3);
            
		// Matrix conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat3x3(tmat3x3<U> const & m);

		GLM_FUNC_DECL explicit tmat3x3(tmat2x2<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat4x4<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat2x3<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat3x2<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat2x4<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat4x2<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat3x4<T> const & x);
		GLM_FUNC_DECL explicit tmat3x3(tmat4x3<T> const & x);

		// Accesses
		GLM_FUNC_DECL col_type & operator[](size_type i);
		GLM_FUNC_DECL col_type const & operator[](size_type i) const;

		// Unary updatable operators
		GLM_FUNC_DECL tmat3x3<T>& operator=  (tmat3x3<T> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator=  (tmat3x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator+= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator+= (tmat3x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator-= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator-= (tmat3x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator*= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator*= (tmat3x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator/= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat3x3<T>& operator/= (tmat3x3<U> const & m);
		GLM_FUNC_DECL tmat3x3<T>& operator++ ();
		GLM_FUNC_DECL tmat3x3<T>& operator-- ();
	};

	// Binary operators
	template <typename T> 
	tmat3x3<T> operator+ (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s);

	template <typename T> 
	tmat3x3<T> operator+ (
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m);

	template <typename T> 
	tmat3x3<T> operator+ (
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2);
	    
	template <typename T> 
	tmat3x3<T> operator- (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s);

	template <typename T> 
	tmat3x3<T> operator- (
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m);

	template <typename T> 
	tmat3x3<T> operator- (
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2);

	template <typename T> 
	tmat3x3<T> operator* (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s);

	template <typename T> 
	tmat3x3<T> operator* (
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m);

	template <typename T> 
	typename tmat3x3<T>::col_type operator* (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v);

	template <typename T> 
	typename tmat3x3<T>::row_type operator* (
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m);

	template <typename T> 
	tmat3x3<T> operator* (
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2);

	template <typename T> 
	tmat3x3<T> operator/ (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s);

	template <typename T> 
	tmat3x3<T> operator/ (
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m);

	template <typename T> 
	typename tmat3x3<T>::col_type operator/ (
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v);

	template <typename T> 
	typename tmat3x3<T>::row_type operator/ (
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m);

	template <typename T> 
	tmat3x3<T> operator/ (
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2);

	// Unary constant operators
	template <typename T> 
	tmat3x3<T> const operator-  (
		tmat3x3<T> const & m);

	template <typename T> 
	tmat3x3<T> const operator-- (
		tmat3x3<T> const & m, 
		int);

	template <typename T> 
	tmat3x3<T> const operator++ (
		tmat3x3<T> const & m, 
		int);

} //namespace detail

namespace core{
namespace type{
namespace precision
{
	//! 3 columns of 3 components matrix of low precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<lowp_float>		lowp_mat3;
	//! 3 columns of 3 components matrix of medium precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<mediump_float>	mediump_mat3;
	//! 3 columns of 3 components matrix of high precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<highp_float>	highp_mat3;

	//! 3 columns of 3 components matrix of low precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<lowp_float>		lowp_mat3x3;

	//! 3 columns of 3 components matrix of medium precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<mediump_float>	mediump_mat3x3;

	//! 3 columns of 3 components matrix of high precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers
	//! \ingroup core_precision
	typedef detail::tmat3x3<highp_float>	highp_mat3x3;

}//namespace precision
}//namespace type
}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat3x3.inl"
#endif

#endif //glm_core_type_mat3x3
