///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-06-22
// Updated : 2008-10-27
// Licence : This source is under MIT License
// File    : glm/gtx/comparison.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace comparison{

template <typename valType>
inline bool operator== 
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
	return glm::all(glm::equal(x, y));
}

template <typename valType>
inline bool operator== 
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
	return glm::all(glm::equal(x, y));
}

template <typename valType>
inline bool operator== 
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
	return glm::all(glm::equal(x, y));
}

template <typename valType>
inline bool operator!= 
(
	detail::tvec2<valType> const & x, 
	detail::tvec2<valType> const & y
)
{
	return glm::any(glm::notEqual(x, y));
}

template <typename valType>
inline bool operator!= 
(
	detail::tvec3<valType> const & x, 
	detail::tvec3<valType> const & y
)
{
	return glm::any(glm::notEqual(x, y));
}

template <typename valType>
inline bool operator!= 
(
	detail::tvec4<valType> const & x, 
	detail::tvec4<valType> const & y
)
{
	return glm::any(glm::notEqual(x, y));
}

}//namespace comparison
}//namespace gtx
}//namespace glm
