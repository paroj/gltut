///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-04-29
// Updated : 2010-02-07
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_projection.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtc{
namespace matrix_projection
{
	template <typename valType> 
	inline detail::tmat4x4<valType> ortho(
		valType const & left, 
		valType const & right, 
		valType const & bottom, 
		valType const & top)
	{
		detail::tmat4x4<valType> Result(1);
		Result[0][0] = valType(2) / (right - left);
		Result[1][1] = valType(2) / (top - bottom);
		Result[2][2] = - valType(1);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		return Result;
	}

	template <typename valType> 
	inline detail::tmat4x4<valType> ortho(
		valType const & left, 
		valType const & right, 
		valType const & bottom, 
		valType const & top, 
		valType const & zNear, 
		valType const & zFar)
	{
		detail::tmat4x4<valType> Result(1);
		Result[0][0] = valType(2) / (right - left);
		Result[1][1] = valType(2) / (top - bottom);
		Result[2][2] = - valType(2) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - (zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template <typename valType> 
	inline detail::tmat4x4<valType> frustum(
		valType const & left, 
		valType const & right, 
		valType const & bottom, 
		valType const & top, 
		valType const & nearVal, 
		valType const & farVal)
	{
		detail::tmat4x4<valType> Result(0);
		Result[0][0] = (valType(2) * nearVal) / (right - left);
		Result[1][1] = (valType(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
		Result[2][3] = valType(-1);
		Result[3][2] = -(valType(2) * farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template <typename valType> 
	inline detail::tmat4x4<valType> perspective(
		valType const & fovy, 
		valType const & aspect, 
		valType const & zNear, 
		valType const & zFar)
	{
		valType range = tan(radians(fovy / valType(2))) * zNear;	
		valType left = -range * aspect;
		valType right = range * aspect;
		valType bottom = -range;
		valType top = range;

		detail::tmat4x4<valType> Result(valType(0));
		Result[0][0] = (valType(2) * zNear) / (right - left);
		Result[1][1] = (valType(2) * zNear) / (top - bottom);
		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result[2][3] = - valType(1);
		Result[3][2] = - (valType(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template <typename T, typename U>
	inline detail::tvec3<T> project(
		detail::tvec3<T> const & obj, 
		detail::tmat4x4<T> const & model, 
		detail::tmat4x4<T> const & proj, 
		detail::tvec4<U> const & viewport)
	{
		detail::tvec4<T> tmp = detail::tvec4<T>(obj, T(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * T(0.5) + T(0.5);
		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return detail::tvec3<T>(tmp);
	}

	template <typename T, typename U>
	inline detail::tvec3<T> unProject(
		detail::tvec3<T> const & win, 
		detail::tmat4x4<T> const & model, 
		detail::tmat4x4<T> const & proj, 
		detail::tvec4<U> const & viewport)
	{
		detail::tmat4x4<T> inverse = glm::inverse(proj * model);

		detail::tvec4<T> tmp = detail::tvec4<T>(win, T(1));
		tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
		tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
		tmp = tmp * T(2) - T(1);

		detail::tvec4<T> obj = inverse * tmp;
		obj /= obj.w;

		return detail::tvec3<T>(obj);
	}

}//namespace matrix_projection
}//namespace gtc
}//namespace glm
