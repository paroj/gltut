///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_projection.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace matrix_projection
{
	template <typename valType>
	inline detail::tmat4x4<valType> perspectiveFov
	(
		valType const & fov, 
		valType const & width, 
		valType const & height, 
		valType const & zNear, 
		valType const & zFar
	)
	{
		valType rad = glm::radians(fov);
		valType h = glm::cos(valType(0.5) * rad) / glm::sin(valType(0.5) * rad);
		valType w = h * height / width;

		detail::tmat4x4<valType> Result(valType(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = (zFar + zNear) / (zFar - zNear);
		Result[2][3] = valType(1);
		Result[3][2] = -(valType(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template <typename T> 
	inline detail::tmat4x4<T> infinitePerspective(
		T fovy, 
		T aspect, 
		T zNear)
	{
		T range = tan(radians(fovy / T(2))) * zNear;	
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		detail::tmat4x4<T> Result(T(0));
		Result[0][0] = (T(2) * zNear) / (right - left);
		Result[1][1] = (T(2) * zNear) / (top - bottom);
		Result[2][2] = - T(1);
		Result[2][3] = - T(1);
		Result[3][2] = - T(2) * zNear;
		return Result;
	}

	template <typename T> 
	inline detail::tmat4x4<T> tweakedInfinitePerspective(
		T fovy, 
		T aspect, 
		T zNear)
	{
		T range = tan(radians(fovy / T(2))) * zNear;	
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		detail::tmat4x4<T> Result(T(0));
		Result[0][0] = (T(2) * zNear) / (right - left);
		Result[1][1] = (T(2) * zNear) / (top - bottom);
		Result[2][2] = T(0.0001) - T(1);
		Result[2][3] = T(-1);
		Result[3][2] = - (T(0.0001) - T(2)) * zNear;
		return Result;
	}

}//namespace matrix_projection
}//namespace gtc
}//namespace glm
