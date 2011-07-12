///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-08-05
// Updated : 2010-02-11
// Licence : This source is under MIT License
// File    : glm/core/type_mat2x4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat2x4
#define glm_core_type_mat2x4

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

	//! Template for 2 columns and 4 rows matrix of floating-point numbers.
	//! \ingroup core_template
	template <typename T> 
	struct tmat2x4
	{
		enum ctor{null};
		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec4<T> col_type;
		typedef tvec2<T> row_type;
		static GLM_FUNC_DECL size_type col_size();
		static GLM_FUNC_DECL size_type row_size();

		typedef tmat2x4<T> type;
		typedef tmat4x2<T> transpose_type;

	private:
		// Data 
		col_type value[2];

	public:
		// Constructors
		GLM_FUNC_DECL tmat2x4();
		GLM_FUNC_DECL tmat2x4(tmat2x4 const & m);

		GLM_FUNC_DECL explicit tmat2x4(
			ctor);
		GLM_FUNC_DECL explicit tmat2x4(
			value_type const & s);
		GLM_FUNC_DECL explicit tmat2x4(
			value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
			value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1);
		GLM_FUNC_DECL explicit tmat2x4(
			col_type const & v0, 
			col_type const & v1);
            
		//////////////////////////////////////
		// Conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat2x4(
            U const & x);
			
		template <
            typename X1, typename Y1, typename Z1, typename W1, 
            typename X2, typename Y2, typename Z2, typename W2> 
		GLM_FUNC_DECL explicit tmat2x4(
            X1 const & x1, Y1 const & y1, Z1 const & z1, W1 const & w1, 
            X2 const & x2, Y2 const & y2, Z2 const & z2, W2 const & w2);
			
		template <typename U, typename V> 
		GLM_FUNC_DECL explicit tmat2x4(
            tvec4<U> const & v1, 
            tvec4<V> const & v2);
            
        //////////////////////////////////////
		// Matrix conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat2x4(tmat2x4<U> const & m);

		GLM_FUNC_DECL explicit tmat2x4(tmat2x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat3x3<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat4x4<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat2x3<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat3x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat3x4<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat4x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x4(tmat4x3<T> const & x);

		// Accesses
		GLM_FUNC_DECL col_type & operator[](size_type i);
		GLM_FUNC_DECL col_type const & operator[](size_type i) const;

		// Unary updatable operators
		GLM_FUNC_DECL tmat2x4<T>& operator=  (tmat2x4<T> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator=  (tmat2x4<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator+= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator+= (tmat2x4<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator-= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator-= (tmat2x4<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator*= (U const & s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator*= (tmat2x4<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x4<T>& operator/= (U const & s);

		GLM_FUNC_DECL tmat2x4<T>& operator++ ();
		GLM_FUNC_DECL tmat2x4<T>& operator-- ();
	};

	// Binary operators
	template <typename T> 
	tmat2x4<T> operator+ (
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s);
	    
	template <typename T> 
	tmat2x4<T> operator+ (
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2);
	    
	template <typename T> 
	tmat2x4<T> operator- (
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s);

	template <typename T> 
	tmat2x4<T> operator- (
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2);

	template <typename T> 
	tmat2x4<T> operator* (
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s);

	template <typename T> 
	tmat2x4<T> operator* (
		typename tmat2x4<T>::value_type const & s, 
		tmat2x4<T> const & m);

	template <typename T>
	typename tmat2x4<T>::col_type operator* (
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::row_type const & v);

	template <typename T> 
	typename tmat2x4<T>::row_type operator* (
		typename tmat2x4<T>::col_type const & v, 
		tmat2x4<T> const & m);

	template <typename T>
	tmat2x4<T> operator* (
		tmat2x4<T> const & m1, 
		tmat2x4<T> const & m2);

	template <typename T> 
	tmat2x4<T> operator/ (
		tmat2x4<T> const & m, 
		typename tmat2x4<T>::value_type const & s);

	template <typename T> 
	tmat2x4<T> operator/ (
		typename tmat2x4<T>::value_type const & s, 
		tmat2x4<T> const & m);

	// Unary constant operators
	template <typename T> 
	tmat2x4<T> const operator-  (
		tmat2x4<T> const & m);

	template <typename T> 
	tmat2x4<T> const operator-- (
		tmat2x4<T> const & m, 
		int);

	template <typename T> 
	tmat2x4<T> const operator++ (
		tmat2x4<T> const & m, 
		int);

} //namespace detail

namespace core{
namespace type{
namespace precision
{
	//! 2 columns of 4 components matrix of low precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	typedef detail::tmat2x4<lowp_float>		lowp_mat2x4;
	//! 2 columns of 4 components matrix of medium precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	typedef detail::tmat2x4<mediump_float>	mediump_mat2x4;
	//! 2 columns of 4 components matrix of high precision floating-point numbers.
	//! There is no guarantee on the actual precision.
	//! (From GLSL 1.30.8 specification, section 4.1.6 Matrices and section 4.5 Precision and Precision Qualifiers)
	typedef detail::tmat2x4<highp_float>	highp_mat2x4;
}//namespace precision
}//namespace type
}//namespace core
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat2x4.inl"
#endif

#endif //glm_core_type_mat2x4
