///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-03
// Updated : 2010-02-04
// Licence : This source is under MIT License
// File    : glm/core/func_geometric.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_geometric
#define glm_core_func_geometric

namespace glm
{
	namespace core{
	namespace function{
	namespace geometric{ //!< Define all geometric functions from Section 8.4 of GLSL 1.30.8 specification. Included in glm namespace.

	/// \addtogroup core_funcs
	///@{

	//! Returns the length of x, i.e., sqrt(x * x).
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/length.xml">GLSL length man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
	template <typename genType> 
	typename genType::value_type length(
		genType const & x); 

	//! Returns the distance betwwen p0 and p1, i.e., length(p0 - p1).
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/distance.xml">GLSL distance man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
	template <typename genType> 
	typename genType::value_type distance(
		genType const & p0, 
		genType const & p1);

	//! Returns the dot product of x and y, i.e., result = x * y.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/dot.xml">GLSL dot man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
    template <typename genType> 
	typename genType::value_type dot(
		genType const & x, 
		genType const & y);

	//! Returns the cross product of x and y.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cross.xml">GLSL cross man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
    template <typename T> 
	detail::tvec3<T> cross(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y);

	//! Returns a vector in the same direction as x but with length of 1.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/normalize.xml">GLSL normalize man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
	template <typename genType> 
	genType normalize(
		genType const & x);

	//! If dot(Nref, I) < 0.0, return N, otherwise, return -N.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/faceforward.xml">GLSL faceforward man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
    template <typename genType> 
	genType faceforward(
		genType const & N, 
		genType const & I, 
		genType const & Nref);
  
	//! For the incident vector I and surface orientation N, 
	//! returns the reflection direction : result = I - 2.0 * dot(N, I) * N.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml">GLSL reflect man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
    template <typename genType> 
	genType reflect(
		genType const & I, 
		genType const & N);
  
	//! For the incident vector I and surface normal N, 
	//! and the ratio of indices of refraction eta, 
	//! return the refraction vector.
    //! 
    //! \li <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/refract.xml">GLSL refract man page</a>
    //! \li GLSL 1.30.08 specification, section 8.4
    template <typename genType> 
	genType refract(
		genType const & I, 
		genType const & N, 
		typename genType::value_type const & eta);

	///@}

	}//namespace geometric
	}//namespace function
	}//namespace core

	using namespace core::function::geometric;
}//namespace glm

#include "func_geometric.inl"

#endif//glm_core_func_geometric
