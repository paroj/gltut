///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-03-05
// Updated : 2011-03-05
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_interpolation.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_matric_interpolation
///////////////////////////////////////////////////////////////////////////////////////////////////
// This extension has been written by Ghenadii Ursachi (the.asteroth@gmail.com)
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_interpolation
#define glm_gtx_matrix_interpolation

// Dependency:
//#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_interpolation extension included")
#endif

namespace glm{
namespace gtx{
namespace matrix_interpolation ///< GLM_GTX_matrix_interpolation extension: Add transformation matrices
{
	/// \addtogroup gtx_matrix_interpolation
	/// @{

	//! Get the axis and angle of the rotation from a matrix.
    //! From GLM_GTX_matrix_interpolation extension.
	template <typename T>
    void axisAngle(
        detail::tmat4x4<T> const & mat,
        detail::tvec3<T> & axis,
        T & angle);

    //! Build a matrix from axis and angle.
    //! From GLM_GTX_matrix_interpolation extension.
	template <typename T>
    detail::tmat4x4<T> axisAngleMatrix(
        detail::tvec3<T> const & axis,
        T const angle);

	//! Build a interpolation of 4 * 4 matrixes.
    //! From GLM_GTX_matrix_interpolation extension.
    //! Warning! works only with rotation and/or translation matrixes, scale will generate unexpected results.
	template <typename T>
    detail::tmat4x4<T> interpolate(
        detail::tmat4x4<T> const & m1,
        detail::tmat4x4<T> const & m2,
        T const delta);

	/// @}
}//namespace matrix_interpolation
}//namespace gtx
}//namespace glm

#include "matrix_interpolation.inl"

namespace glm{using namespace gtx::matrix_interpolation;}

#endif//glm_gtx_transform
