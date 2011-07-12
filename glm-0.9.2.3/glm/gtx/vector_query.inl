///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-05
// Updated : 2010-02-16
// Licence : This source is under MIT License
// File    : glm/gtx/vector_query.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

namespace glm{
namespace gtx{
namespace vector_query
{
	template <typename T>
	GLM_FUNC_QUALIFIER bool areCollinear
	(
		detail::tvec2<T> const & v0, 
		detail::tvec2<T> const & v1, 
		T const & epsilon
	)
	{
		return length(cross(detail::tvec3<T>(v0, T(0)), detail::tvec3<T>(v1, T(0)))) < epsilon;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER bool areCollinear
	(
		detail::tvec3<T> const & v0, 
		detail::tvec3<T> const & v1, 
		T const & epsilon
	)
	{
		return length(cross(v0, v1)) < epsilon;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER bool areCollinear
	(
		detail::tvec4<T> const & v0, 
		detail::tvec4<T> const & v1, 
		T const & epsilon
	)
	{
		return length(cross(detail::tvec3<T>(v0), detail::tvec3<T>(v1))) < epsilon;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER bool areOpposite
	(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon
	)
	{
		assert(isNormalized(v0) && isNormalized(v1));
        return((typename genType::value_type(1) + dot(v0, v1)) <= epsilon);
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER bool areOrthogonal
	(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon
	)
	{
		return abs(dot(v0, v1)) <= max(
			typename genType::value_type(1), 
			length(v0)) * max(
				typename genType::value_type(1), 
				length(v1)) * epsilon;
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER bool isNormalized
	(
		genType const & v, 
		typename genType::value_type const & epsilon
	)
	{
		return abs(length(v) - typename genType::value_type(1)) <= typename genType::value_type(2) * epsilon;
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER bool isNull
	(
		genType const & v, 
		typename genType::value_type const & epsilon
	)
	{
		return length(v) <= epsilon;
	}

    template <typename T> 
    GLM_FUNC_QUALIFIER bool isCompNull
	(
		T const & s, 
		T const & epsilon
	)
    {
        return abs(s) < epsilon;
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tvec2<bool> isCompNull
	(
		detail::tvec2<T> const & v, 
		T const & epsilon)
    {
        return detail::tvec2<bool>(
            (abs(v.x) < epsilon),
            (abs(v.y) < epsilon));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tvec3<bool> isCompNull
	(
		detail::tvec3<T> const & v, 
		T const & epsilon
	)
    {
        return detail::tvec3<bool>(
            abs(v.x) < epsilon,
            abs(v.y) < epsilon,
            abs(v.z) < epsilon);
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tvec4<bool> isCompNull
	(
		detail::tvec4<T> const & v, 
		T const & epsilon
	)
    {
        return detail::tvec4<bool>(
            abs(v.x) < epsilon,
            abs(v.y) < epsilon,
            abs(v.z) < epsilon,
            abs(v.w) < epsilon);
    }

	template <typename genType>
	GLM_FUNC_QUALIFIER bool areOrthonormal
	(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon
	)
	{
		return isNormalized(v0, epsilon) && isNormalized(v1, epsilon) && (abs(dot(v0, v1)) <= epsilon);
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER bool areSimilar
	(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon
	)
	{
		bool similar = true;
        for(typename genType::size_type i = 0; similar && i < genType::value_size(); i++)
			similar = (abs(v0[i] - v1[i]) <= epsilon);
		return similar;
	}

}//namespace vector_query
}//namespace gtx
}//namespace glm
