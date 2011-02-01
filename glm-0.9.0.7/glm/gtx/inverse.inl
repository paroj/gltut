///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-09-30
// Licence : This source is under MIT License
// File    : glm/gtx/inverse.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace inverse
{
	template <typename T> 
	inline detail::tmat3x3<T> affineInverse
	(
		detail::tmat3x3<T> const & m
	)
	{
		detail::tmat3x3<T> Result(m);
		Result[2] = detail::tvec3<T>(0, 0, 1);
		Result = transpose(Result);
		detail::tvec3<T> Translation = Result * detail::tvec3<T>(-detail::tvec2<T>(m[2]), m[2][2]);
		Result[2] = Translation;
		return Result;
	}

	template <typename T> 
	inline detail::tmat4x4<T> affineInverse
	(
		detail::tmat4x4<T> const & m
	)
	{
		detail::tmat4x4<T> Result(m);
		Result[3] = detail::tvec4<T>(0, 0, 0, 1);
		Result = transpose(Result);
		detail::tvec4<T> Translation = Result * detail::tvec4<T>(-detail::tvec3<T>(m[3]), m[3][3]);
		Result[3] = Translation;
		return Result;
	}

}//namespace inverse
}//namespace gtx
}//namespace glm
