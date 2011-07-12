///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-04-09
// Updated : 2011-04-09
// Licence : This source is under MIT License
// File    : glm/gtx/simplex.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_simplex
#define glm_gtx_simplex

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_simplex extension included")
#endif

namespace glm{
namespace gtx{
namespace spline ///< GLM_GTX_simplex extension: Spline functions
{
    /// \addtogroup gtx_spline
    ///@{
            
    //! Return a point from a catmull rom curve.
    //! From GLM_GTX_spline extension.
    template <typename genType> 
    genType catmullRom(
                        genType const & v1, 
                        genType const & v2, 
                        genType const & v3, 
                        genType const & v4, 
                        typename genType::value_type const & s);
            
    //! Return a point from a hermite curve.
    //! From GLM_GTX_spline extension.
    template <typename genType> 
    genType hermite(
                    genType const & v1, 
                    genType const & t1, 
                    genType const & v2, 
                    genType const & t2, 
                    typename genType::value_type const & s);
            
    //! Return a point from a cubic curve. 
    //! From GLM_GTX_spline extension.
    template <typename genType> 
    genType cubic(
                    genType const & v1, 
                    genType const & v2, 
                    genType const & v3, 
                    genType const & v4, 
                    typename genType::value_type const & s);
            
    /// @}
}// namespace simplex
}// namespace gtx
}// namespace glm

#include "simplex.inl"

namespace glm{using namespace gtx::simplex;}

#endif//glm_gtx_spline

