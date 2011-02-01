namespace glm{
namespace gtc{
namespace glm_gtc_swizzle
{
	template <typename T>
	inline T swizzle
	(	
		detail::tvec4<T> const & v,
		comp x
	)
	{
		return v[x];
	}

	template <typename T>
	inline detail::tvec2<T> swizzle
	(
		detail::tvec4<T> const & v,
		comp x, comp y
	)
	{
		return detail::tvec2<T>(
			v[x],
			v[y]);
	}

	template <typename T>
	inline detail::tvec3<T> swizzle
	(
		detail::tvec4<T> const & v,
		comp x, comp y, comp z
	)
	{
		return detail::tvec3<T>(
			v[x],
			v[y],
			v[z]);
	}

	template <typename T>
	inline detail::tref4<T> swizzle
	(
		detail::tvec4<T> const & v,
		comp x, comp y, comp z, comp w
	)
	{
		return detail::tref4<T>(v[x], v[y],	v[z], v[w]);
	}

}//namespace glm_gtc_swizzle
}//namespace gtc
}//namespace glm
