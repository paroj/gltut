///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-25
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/type_vec1.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype1
#define glm_core_type_gentype1

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"

namespace glm{
namespace detail
{
	template <typename T> struct tref1;
	template <typename T> struct tref2;
	template <typename T> struct tref3;
	template <typename T> struct tref4;
	template <typename T> struct tvec1;
	template <typename T> struct tvec2;
	template <typename T> struct tvec3;
	template <typename T> struct tvec4;

	template <typename T>
	struct tvec1
	{
		enum ctor{null};

		typedef T value_type;
		typedef std::size_t size_type;
		GLM_FUNC_DECL size_type length() const;
		static GLM_FUNC_DECL size_type value_size();

		typedef tvec1<T> type;
		typedef tvec1<bool> bool_type;

		//////////////////////////////////////
		// Data

#		if(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
			value_type x;
#		else//(GLM_COMPONENT == GLM_COMPONENT_GLSL_NAMES)
			union {value_type x, r, s;};
#		endif//GLM_COMPONENT

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL value_type & operator[](size_type i);
		GLM_FUNC_DECL value_type const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec1();
		GLM_FUNC_DECL tvec1(tvec1<T> const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec1(
			ctor);
		GLM_FUNC_DECL explicit tvec1(
			value_type const & s);

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec1(tref1<T> const & r);

		//////////////////////////////////////
		// Convertion scalar constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec1(U const & s);

		//////////////////////////////////////
		// Convertion vector constructors

		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec1(tvec2<U> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec1(tvec3<U> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec1(tvec4<U> const & v);

		//////////////////////////////////////
		// Unary arithmetic operators

		GLM_FUNC_DECL tvec1<T> & operator= (tvec1<T> const & v);

		GLM_FUNC_DECL tvec1<T> & operator+=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator+=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator-=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator-=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator*=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator*=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator/=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator/=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator++();
		GLM_FUNC_DECL tvec1<T> & operator--();

		//////////////////////////////////////
		// Unary bit operators

		GLM_FUNC_DECL tvec1<T> & operator%=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator%=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator&=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator&=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator|=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator|=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator^=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator^=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator<<=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator<<=(tvec1<T> const & v);
		GLM_FUNC_DECL tvec1<T> & operator>>=(value_type const & s);
		GLM_FUNC_DECL tvec1<T> & operator>>=(tvec1<T> const & v);

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL value_type swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<T> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<T> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref1<T> swizzle(comp X);
	};

	template <typename T>
	struct tref1
	{
		GLM_FUNC_DECL tref1(T & x);
		GLM_FUNC_DECL tref1(tref1<T> const & r);
		GLM_FUNC_DECL tref1(tvec1<T> const & v);

		GLM_FUNC_DECL tref1<T> & operator= (tref1<T> const & r);
		GLM_FUNC_DECL tref1<T> & operator= (tvec1<T> const & v);

		T& x;
	};

	GLM_DETAIL_IS_VECTOR(tvec1);

	typedef detail::tvec1<core::type::precision::highp_float>		highp_vec1_t;
	typedef detail::tvec1<core::type::precision::mediump_float>		mediump_vec1_t;
	typedef detail::tvec1<core::type::precision::lowp_float>		lowp_vec1_t;
	typedef detail::tvec1<core::type::precision::highp_int>			highp_ivec1_t;
	typedef detail::tvec1<core::type::precision::mediump_int>		mediump_ivec1_t;
	typedef detail::tvec1<core::type::precision::lowp_int>			lowp_ivec1_t;
	typedef detail::tvec1<core::type::precision::highp_uint>		highp_uvec1_t;
	typedef detail::tvec1<core::type::precision::mediump_uint>		mediump_uvec1_t;
	typedef detail::tvec1<core::type::precision::lowp_uint>			lowp_uvec1_t;

}//namespace detail
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec1.inl"
#endif//GLM_EXTERNAL_TEMPLATE

#endif//glm_core_type_gentype1
