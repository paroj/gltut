///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_selection.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace matrix_selection
{
    template <typename T>
    inline detail::tvec2<T> row(
		const detail::tmat2x2<T>& m, 
		int index)
    {
        return detail::tvec2<T>(m[0][index], m[1][index]);
    }

    template <typename T>
    inline detail::tvec3<T> row(
		const detail::tmat3x3<T>& m, 
		int index)
    {
        return detail::tvec3<T>(m[0][index], m[1][index], m[2][index]);
    }

    template <typename T>
    inline detail::tvec4<T> row(
		const detail::tmat4x4<T>& m, 
		int index)
    {
        return detail::tvec4<T>(m[0][index], m[1][index], m[2][index], m[3][index]);
    }

    template <typename T>
    inline detail::tvec2<T> column(
		const detail::tmat2x2<T>& m, 
		int index)
    {
        return m[index];
    }

    template <typename T>
    inline detail::tvec3<T> column(
		const detail::tmat3x3<T>& m, 
		int index)
    {
        return m[index];
    }

    template <typename T>
    inline detail::tvec4<T> column(
		const detail::tmat4x4<T>& m, 
		int index)
    {
        return m[index];
    }

}//namespace matrix_selection
}//namespace gtx
}//namespace glm

