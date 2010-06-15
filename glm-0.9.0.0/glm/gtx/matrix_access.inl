///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-27
// Updated : 2005-12-27
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_access.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace matrix_access{

    template <typename genType>
    inline genType row(
		genType const & m, 
		int index, 
		typename genType::row_type const & x)
    {
        genType Result = m;
        for(typename genType::size_type i = 0; i < genType::row_size(); ++i)
			Result[i][index] = x[i];
        return Result;
    }

    template <typename genType>
    inline genType column(
		genType const & m, 
		int index, 
		typename genType::col_type const & x)
    {
        genType Result = m;
        Result[index] = x;
        return Result;
    }

}//namespace matrix_access
}//namespace gtx
}//namespace glm

