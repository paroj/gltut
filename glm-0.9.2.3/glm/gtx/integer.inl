///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-24
// Updated : 2006-12-06
// Licence : This source is under MIT License
// File    : glm/gtx/integer.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace integer
{
    // pow
    GLM_FUNC_QUALIFIER int pow(int x, int y)
    {
		if(y == 0)
			return 1;
        int result = x;
        for(int i = 1; i < y; ++i)
            result *= x;
        return result;
    }

    // sqrt: From Christopher J. Musial, An integer square root, Graphics Gems, 1990, page 387
    GLM_FUNC_QUALIFIER int sqrt(int x)
    {
        if(x <= 1) return x;

        int NextTrial = x >> 1;
        int CurrentAnswer;

        do
        {
            CurrentAnswer = NextTrial;
            NextTrial = (NextTrial + x / NextTrial) >> 1;
        } while(NextTrial < CurrentAnswer);

        return CurrentAnswer;
    }

    // mod
	GLM_FUNC_QUALIFIER int mod(int x, int y)
	{
		return x - y * (x / y);
	}

    // factorial (!12 max, integer only)
	template <typename genType>
    GLM_FUNC_QUALIFIER genType factorial(genType const & x)
    {
		genType Temp = x;
        genType Result;
        for(Result = 1; Temp > 1; --Temp)
            Result *= Temp;
        return Result;
    }

	template <typename valType>
    GLM_FUNC_QUALIFIER detail::tvec2<valType> factorial(
		detail::tvec2<valType> const & x)
    {
        return detail::tvec2<valType>(
            factorial(x.x),
            factorial(x.y));
    }

	template <typename valType>
    GLM_FUNC_QUALIFIER detail::tvec3<valType> factorial(
		detail::tvec3<valType> const & x)
    {
        return detail::tvec3<valType>(
            factorial(x.x),
            factorial(x.y),
            factorial(x.z));
    }

	template <typename valType>
    GLM_FUNC_QUALIFIER detail::tvec4<valType> factorial(
		detail::tvec4<valType> const & x)
    {
        return detail::tvec4<valType>(
            factorial(x.x),
            factorial(x.y),
            factorial(x.z),
            factorial(x.w));
    }

}//namespace integer
}//namespace gtx
}//namespace glm
