 ///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-05
// Updated : 2007-03-05
// Licence : This source is under MIT License
// File    : glm/gtx/vector_query.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_vector_query
#define glm_gtx_vector_query

// Dependency:
#include "../glm.hpp"
#include <cfloat>
#include <limits>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vector_query extension included")
#endif

namespace glm{
namespace gtx{
namespace vector_query ///< GLM_GTX_vector_query extension: Query informations of vector types
{
	/// \addtogroup gtx_vector_query
	/// @{

	//! Check if two vectors are collinears.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areCollinear(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());
		
    //! Check if two vectors are opposites.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areOpposite(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());
		
    //! Check if two vectors are orthogonals.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areOrthogonal(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());

	//! Check if a vector is normalized.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool isNormalized(
		genType const & v, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());
		
	//! Check if a vector is null.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool isNull(
		genType const & v, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());

	//! Check if two vectors are orthonormal.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType>
	bool areOrthonormal(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());

	//! Check if two vectors are similar.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areSimilar(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon = std::numeric_limits<typename genType::value_type>::epsilon());

	/// @}
}// namespace vector_query
}// namespace gtx
}// namespace glm

#include "vector_query.inl"

namespace glm{using namespace gtx::vector_query;}

#endif//glm_gtx_vector_query
