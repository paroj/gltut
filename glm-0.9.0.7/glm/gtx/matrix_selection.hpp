///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_selection.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_matrix_selection
#define glm_gtx_matrix_selection

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		void main_gtx_matrix_selection();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_matrix_selection extension: Access to matrix columns or rows.
	namespace matrix_selection
	{
		//! Returns a 2 components vector that contains the row of the matrix m witch values is the ones of the row index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec2<T> row(
			const detail::tmat2x2<T>& m, 
			int index);
		
		//! Returns a 3 components vector that contains the row of the matrix m witch values is the ones of the row index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec3<T> row(
			const detail::tmat3x3<T>& m, 
			int index);

		//! Returns a 4 components vector that contains the row of the matrix m witch values is the ones of the row index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec4<T> row(
			const detail::tmat4x4<T>& m, 
			int index);

		//! Returns a 2 components vector that contains the row of the matrix m witch values is the ones of the column index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec2<T> column(
			const detail::tmat2x2<T>& m, 
			int index);

		//! Returns a 3 components vector that contains the row of the matrix m witch values is the ones of the column index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec3<T> column(
			const detail::tmat3x3<T>& m, 
			int index);

		//! Returns a 4 components vector that contains the row of the matrix m witch values is the ones of the column index.
		//! From GLM_GTX_matrix_selection extension.
		template <typename T> 
		detail::tvec4<T> column(
			const detail::tmat4x4<T>& m, 
			int index);

	}//namespace matrix_selection
	}//namespace gtx
}//namespace glm

#include "matrix_selection.inl"

namespace glm{using namespace gtx::matrix_selection;}

#endif//glm_gtx_matrix_selection
