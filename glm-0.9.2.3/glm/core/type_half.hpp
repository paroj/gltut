///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-17
// Updated : 2010-02-17
// Licence : This source is under MIT License
// File    : glm/core/type_half.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_half
#define glm_core_type_half

#include <cstdlib>

namespace glm{
namespace detail
{
	typedef short hdata;

	float toFloat32(hdata value);
	hdata toFloat16(float const & value);

	///16-bit floating point type.
	/// \ingroup gtc_half_float
	class thalf
	{
	public: 
		// Constructors
		GLM_FUNC_DECL thalf();
		GLM_FUNC_DECL thalf(thalf const & s);
			
		template <typename U>
		GLM_FUNC_DECL explicit thalf(U const & s);

		// Cast
		//operator float();
		GLM_FUNC_DECL operator float() const;
		//operator double();
		//operator double() const;

		// Unary updatable operators
		GLM_FUNC_DECL thalf& operator= (thalf const & s);
		GLM_FUNC_DECL thalf& operator+=(thalf const & s);
		GLM_FUNC_DECL thalf& operator-=(thalf const & s);
		GLM_FUNC_DECL thalf& operator*=(thalf const & s);
		GLM_FUNC_DECL thalf& operator/=(thalf const & s);
		GLM_FUNC_DECL thalf& operator++();
		GLM_FUNC_DECL thalf& operator--();
	
		GLM_FUNC_DECL float toFloat() const{return toFloat32(data);}

		GLM_FUNC_DECL hdata _data() const{return data;}

	private:
		hdata data;
	};

	thalf operator+ (thalf const & s1, thalf const & s2);

	thalf operator- (thalf const & s1, thalf const & s2);

	thalf operator* (thalf const & s1, thalf const & s2);

	thalf operator/ (thalf const & s1, thalf const & s2);

	// Unary constant operators
	thalf operator- (thalf const & s);

	thalf operator-- (thalf const & s, int);

	thalf operator++ (thalf const & s, int);

}//namespace detail
}//namespace glm

#include "type_half.inl"

#endif//glm_core_type_half
