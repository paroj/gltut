///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
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
#include "../gtc/type_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_swizzle extension included")
#endif

namespace glm{
namespace gtc{
namespace swizzle ///< GLM_GTC_swizzle extension
{
	using namespace gtc::half_float;

	template <typename T, template <typename> class vecType>
	T const & swizzle(	
		vecType<T> const & v,
		comp x);

	template <typename T, template <typename> class vecType>
	detail::tvec2<T> const & swizzle(
		vecType<T> const & v,
		comp x, comp y);

	template <typename T, template <typename> class vecType>
	detail::tvec3<T> const & swizzle(
		vecType<T> const & v,
		comp x, comp y, comp z);

	template <typename T, template <typename> class vecType>
	detail::tvec4<T> const & swizzle(
		vecType<T> const & v,
		comp x, comp y, comp z, comp w);

	template <typename T, template <typename> class vecType>
	T & swizzle(
		vecType<T> & v,
		comp x);

	template <typename T, template <typename> class vecType>
	detail::tref2<T> swizzle(
		vecType<T> & v,
		comp x, comp y);

	template <typename T, template <typename> class vecType>
	detail::tref3<T> swizzle(
		vecType<T> & v,
		comp x, comp y, comp z);

	template <typename T, template <typename> class vecType>
	detail::tref4<T> swizzle(
		vecType<T> & v,
		comp x, comp y, comp z, comp w);

#	define static_swizzle1_const(TYPE, SIZE)							\
		template <comp x>										\
		GLM_FUNC_QUALIFIER TYPE swizzle(detail::tvec##SIZE<TYPE> const & v)	\
		{return v[x];}											
																
#	define static_swizzle1_ref(TYPE, SIZE)									\
		template <comp x>													\
		GLM_FUNC_QUALIFIER TYPE& swizzle(detail::tvec##SIZE<TYPE> & v)		\
		{return v[x];}

	static_swizzle1_ref(detail::float16, 2)
	static_swizzle1_ref(detail::float16, 3)
	static_swizzle1_ref(detail::float16, 4)
	static_swizzle1_ref(detail::float32, 2)
	static_swizzle1_ref(detail::float32, 3)
	static_swizzle1_ref(detail::float32, 4)
	static_swizzle1_ref(detail::float64, 2)
	static_swizzle1_ref(detail::float64, 3)
	static_swizzle1_ref(detail::float64, 4)

	static_swizzle1_ref(detail::int8,  2)
	static_swizzle1_ref(detail::int8,  3)
	static_swizzle1_ref(detail::int8,  4)
	static_swizzle1_ref(detail::int16, 2)
	static_swizzle1_ref(detail::int16, 3)
	static_swizzle1_ref(detail::int16, 4)
	static_swizzle1_ref(detail::int32, 2)
	static_swizzle1_ref(detail::int32, 3)
	static_swizzle1_ref(detail::int32, 4)
	static_swizzle1_ref(detail::int64, 2)
	static_swizzle1_ref(detail::int64, 3)
	static_swizzle1_ref(detail::int64, 4)

	static_swizzle1_ref(detail::uint8,  2)
	static_swizzle1_ref(detail::uint8,  3)
	static_swizzle1_ref(detail::uint8,  4)
	static_swizzle1_ref(detail::uint16, 2)
	static_swizzle1_ref(detail::uint16, 3)
	static_swizzle1_ref(detail::uint16, 4)
	static_swizzle1_ref(detail::uint32, 2)
	static_swizzle1_ref(detail::uint32, 3)
	static_swizzle1_ref(detail::uint32, 4)
	static_swizzle1_ref(detail::uint64, 2)
	static_swizzle1_ref(detail::uint64, 3)
	static_swizzle1_ref(detail::uint64, 4)
/*
#	define static_swizzle2_const(TYPE) \
		template <comp x, comp y> \
		GLM_FUNC_QUALIFIER TYPE swizzle(TYPE const & v) \
		{return TYPE(v[x], v[y]);}

#	define static_swizzle3_const(TYPE) \
		template <comp x, comp y, comp z> \
		GLM_FUNC_QUALIFIER TYPE swizzle(TYPE const & v) \
		{return TYPE(v[x], v[y], v[z]);}

#	define static_swizzle4_const(TYPE) \
		template <comp x, comp y, comp z, comp w> \
		GLM_FUNC_QUALIFIER TYPE swizzle(TYPE const & v) \
		{return TYPE(v[x], v[y], v[z], v[w]);}
*/

#	define static_swizzle2_const(TYPE, SIZE)									\
		template <comp x, comp y>												\
		GLM_FUNC_QUALIFIER detail::tvec2<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
		{return detail::tvec2<TYPE>(v[x], v[y]);}

#	define static_swizzle3_const(TYPE, SIZE)									\
		template <comp x, comp y, comp z>										\
		GLM_FUNC_QUALIFIER detail::tvec3<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
		{return detail::tvec3<TYPE>(v[x], v[y], v[z]);}

#	define static_swizzle4_const(TYPE, SIZE)									\
		template <comp x, comp y, comp z, comp w>								\
		GLM_FUNC_QUALIFIER detail::tvec4<TYPE> swizzle(detail::tvec##SIZE<TYPE> const & v)	\
		{return detail::tvec4<TYPE>(v[x], v[y], v[z], v[w]);}


	static_swizzle2_const(glm::f16, 2)
	static_swizzle2_const(glm::f16, 3)
	static_swizzle2_const(glm::f16, 4)
	static_swizzle2_const(glm::f32, 2)
	static_swizzle2_const(glm::f32, 3)
	static_swizzle2_const(glm::f32, 4)
	static_swizzle2_const(glm::f64, 2)
	static_swizzle2_const(glm::f64, 3)
	static_swizzle2_const(glm::f64, 4)

	static_swizzle2_const(glm::i8, 2)
	static_swizzle2_const(glm::i8, 3)
	static_swizzle2_const(glm::i8, 4)
	static_swizzle2_const(glm::i16, 2)
	static_swizzle2_const(glm::i16, 3)
	static_swizzle2_const(glm::i16, 4)
	static_swizzle2_const(glm::i32, 2)
	static_swizzle2_const(glm::i32, 3)
	static_swizzle2_const(glm::i32, 4)
	static_swizzle2_const(glm::i64, 2)
	static_swizzle2_const(glm::i64, 3)
	static_swizzle2_const(glm::i64, 4)

	static_swizzle2_const(glm::u8, 2)
	static_swizzle2_const(glm::u8, 3)
	static_swizzle2_const(glm::u8, 4)
	static_swizzle2_const(glm::u16, 2)
	static_swizzle2_const(glm::u16, 3)
	static_swizzle2_const(glm::u16, 4)
	static_swizzle2_const(glm::u32, 2)
	static_swizzle2_const(glm::u32, 3)
	static_swizzle2_const(glm::u32, 4)
	static_swizzle2_const(glm::u64, 2)
	static_swizzle2_const(glm::u64, 3)
	static_swizzle2_const(glm::u64, 4)

	static_swizzle3_const(glm::f16, 2)
	static_swizzle3_const(glm::f16, 3)
	static_swizzle3_const(glm::f16, 4)
	static_swizzle3_const(glm::f32, 2)
	static_swizzle3_const(glm::f32, 3)
	static_swizzle3_const(glm::f32, 4)
	static_swizzle3_const(glm::f64, 2)
	static_swizzle3_const(glm::f64, 3)
	static_swizzle3_const(glm::f64, 4)

	static_swizzle3_const(glm::i8, 2)
	static_swizzle3_const(glm::i8, 3)
	static_swizzle3_const(glm::i8, 4)
	static_swizzle3_const(glm::i16, 2)
	static_swizzle3_const(glm::i16, 3)
	static_swizzle3_const(glm::i16, 4)
	static_swizzle3_const(glm::i32, 2)
	static_swizzle3_const(glm::i32, 3)
	static_swizzle3_const(glm::i32, 4)
	static_swizzle3_const(glm::i64, 2)
	static_swizzle3_const(glm::i64, 3)
	static_swizzle3_const(glm::i64, 4)

	static_swizzle3_const(glm::u8, 2)
	static_swizzle3_const(glm::u8, 3)
	static_swizzle3_const(glm::u8, 4)
	static_swizzle3_const(glm::u16, 2)
	static_swizzle3_const(glm::u16, 3)
	static_swizzle3_const(glm::u16, 4)
	static_swizzle3_const(glm::u32, 2)
	static_swizzle3_const(glm::u32, 3)
	static_swizzle3_const(glm::u32, 4)
	static_swizzle3_const(glm::u64, 2)
	static_swizzle3_const(glm::u64, 3)
	static_swizzle3_const(glm::u64, 4)

	static_swizzle4_const(glm::f16, 2)
	static_swizzle4_const(glm::f16, 3)
	static_swizzle4_const(glm::f16, 4)
	static_swizzle4_const(glm::f32, 2)
	static_swizzle4_const(glm::f32, 3)
	static_swizzle4_const(glm::f32, 4)
	static_swizzle4_const(glm::f64, 2)
	static_swizzle4_const(glm::f64, 3)
	static_swizzle4_const(glm::f64, 4)

	static_swizzle4_const(glm::i8, 2)
	static_swizzle4_const(glm::i8, 3)
	static_swizzle4_const(glm::i8, 4)
	static_swizzle4_const(glm::i16, 2)
	static_swizzle4_const(glm::i16, 3)
	static_swizzle4_const(glm::i16, 4)
	static_swizzle4_const(glm::i32, 2)
	static_swizzle4_const(glm::i32, 3)
	static_swizzle4_const(glm::i32, 4)
	static_swizzle4_const(glm::i64, 2)
	static_swizzle4_const(glm::i64, 3)
	static_swizzle4_const(glm::i64, 4)

	static_swizzle4_const(glm::u8, 2)
	static_swizzle4_const(glm::u8, 3)
	static_swizzle4_const(glm::u8, 4)
	static_swizzle4_const(glm::u16, 2)
	static_swizzle4_const(glm::u16, 3)
	static_swizzle4_const(glm::u16, 4)
	static_swizzle4_const(glm::u32, 2)
	static_swizzle4_const(glm::u32, 3)
	static_swizzle4_const(glm::u32, 4)
	static_swizzle4_const(glm::u64, 2)
	static_swizzle4_const(glm::u64, 3)
	static_swizzle4_const(glm::u64, 4)

#	define static_swizzle2_ref(TYPE, SIZE) \
		template <glm::comp x, glm::comp y> \
		GLM_FUNC_QUALIFIER glm::detail::tref2<TYPE> swizzle(detail::tvec##SIZE<TYPE> & v) \
		{return glm::detail::tref2<TYPE>(v[x], v[y]);}	

#	define static_swizzle3_ref(TYPE, SIZE) \
		template <glm::comp x, glm::comp y, glm::comp z> \
		GLM_FUNC_QUALIFIER glm::detail::tref3<TYPE> swizzle(detail::tvec##SIZE<TYPE> & v) \
		{return glm::detail::tref3<TYPE>(v[x], v[y], v[z]);}	

#	define static_swizzle4_ref(TYPE, SIZE) \
		template <glm::comp x, glm::comp y, glm::comp z, glm::comp w> \
		GLM_FUNC_QUALIFIER glm::detail::tref4<TYPE> swizzle(detail::tvec##SIZE<TYPE> & v) \
		{return glm::detail::tref4<TYPE>(v[x], v[y], v[z], v[w]);}	

	static_swizzle2_ref(glm::f16, 2)
	static_swizzle2_ref(glm::f16, 3)
	static_swizzle2_ref(glm::f16, 4)
	static_swizzle2_ref(glm::f32, 2)
	static_swizzle2_ref(glm::f32, 3)
	static_swizzle2_ref(glm::f32, 4)
	static_swizzle2_ref(glm::f64, 2)
	static_swizzle2_ref(glm::f64, 3)
	static_swizzle2_ref(glm::f64, 4)

	static_swizzle2_ref(glm::i8, 2)
	static_swizzle2_ref(glm::i8, 3)
	static_swizzle2_ref(glm::i8, 4)
	static_swizzle2_ref(glm::i16, 2)
	static_swizzle2_ref(glm::i16, 3)
	static_swizzle2_ref(glm::i16, 4)
	static_swizzle2_ref(glm::i32, 2)
	static_swizzle2_ref(glm::i32, 3)
	static_swizzle2_ref(glm::i32, 4)
	static_swizzle2_ref(glm::i64, 2)
	static_swizzle2_ref(glm::i64, 3)
	static_swizzle2_ref(glm::i64, 4)

	static_swizzle2_ref(glm::u8, 2)
	static_swizzle2_ref(glm::u8, 3)
	static_swizzle2_ref(glm::u8, 4)
	static_swizzle2_ref(glm::u16, 2)
	static_swizzle2_ref(glm::u16, 3)
	static_swizzle2_ref(glm::u16, 4)
	static_swizzle2_ref(glm::u32, 2)
	static_swizzle2_ref(glm::u32, 3)
	static_swizzle2_ref(glm::u32, 4)
	static_swizzle2_ref(glm::u64, 2)
	static_swizzle2_ref(glm::u64, 3)
	static_swizzle2_ref(glm::u64, 4)

	static_swizzle3_ref(glm::f16, 3)
	static_swizzle3_ref(glm::f16, 4)
	static_swizzle3_ref(glm::f32, 3)
	static_swizzle3_ref(glm::f32, 4)
	static_swizzle3_ref(glm::f64, 3)
	static_swizzle3_ref(glm::f64, 4)

	static_swizzle3_ref(glm::i8, 3)
	static_swizzle3_ref(glm::i8, 4)
	static_swizzle3_ref(glm::i16, 3)
	static_swizzle3_ref(glm::i16, 4)
	static_swizzle3_ref(glm::i32, 3)
	static_swizzle3_ref(glm::i32, 4)
	static_swizzle3_ref(glm::i64, 3)
	static_swizzle3_ref(glm::i64, 4)

	static_swizzle3_ref(glm::u8, 3)
	static_swizzle3_ref(glm::u8, 4)
	static_swizzle3_ref(glm::u16, 3)
	static_swizzle3_ref(glm::u16, 4)
	static_swizzle3_ref(glm::u32, 3)
	static_swizzle3_ref(glm::u32, 4)
	static_swizzle3_ref(glm::u64, 3)
	static_swizzle3_ref(glm::u64, 4)

	static_swizzle4_ref(glm::f16, 4)
	static_swizzle4_ref(glm::f32, 4)
	static_swizzle4_ref(glm::f64, 4)

	static_swizzle4_ref(glm::i8, 4)
	static_swizzle4_ref(glm::i16, 4)
	static_swizzle4_ref(glm::i32, 4)
	static_swizzle4_ref(glm::i64, 4)

	static_swizzle4_ref(glm::u8, 4)
	static_swizzle4_ref(glm::u16, 4)
	static_swizzle4_ref(glm::u32, 4)
	static_swizzle4_ref(glm::u64, 4)

}//namespace swizzle
}//namespace gtc
}//namespace glm

#include "swizzle.inl"

namespace glm{using namespace gtc::swizzle;}

#endif//glm_gtc_swizzle
