///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-02-21
// Updated : 2009-02-21
// Licence : This source is under MIT License
// File    : glm/gtx/ulp.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_ulp
#define glm_gtx_ulp

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_ulp extension included")
#endif

namespace glm{
namespace gtx{
namespace ulp ///< GLM_GTX_ulp extension: Precision calculation functions
{
	/// \addtogroup gtx_ulp
	/// @{

	//! Return the next ULP value(s) after the input value(s).
	//! From GLM_GTX_ulp extension.
    template <typename genType>
    genType next_float(genType const & x);
        
	//! Return the previous ULP value(s) before the input value(s).
	//! From GLM_GTX_ulp extension.
    template <typename genType>
    genType prev_float(genType const & x);

	//! Return the value(s) ULP distance after the input value(s).
	//! From GLM_GTX_ulp extension.
    template <typename genType>
    genType next_float(genType const & x, uint const & Distance);
        
    //! Return the value(s) ULP distance before the input value(s).
	//! From GLM_GTX_ulp extension.
    template <typename genType>
    genType prev_float(genType const & x, uint const & Distance);
        
    //! Return the distance in the number of ULP between 2 scalars.
	//! From GLM_GTX_ulp extension.
    template <typename T>
    uint float_distance(T const & x, T const & y);
        
    //! Return the distance in the number of ULP between 2 vectors.
	//! From GLM_GTX_ulp extension.
    template<typename T, template<typename> class vecType>
    vecType<uint> float_distance(vecType<T> const & x, vecType<T> const & y);
        
	///@}
}// namespace ulp
}// namespace gtx
}// namespace glm

#include "ulp.inl"

namespace glm{using namespace gtx::ulp;}

#endif//glm_gtx_ulp

