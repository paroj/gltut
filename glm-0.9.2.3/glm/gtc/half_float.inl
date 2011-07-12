///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2010-02-07
// Licence : This source is under MIT licence
// File    : glm/gtc/half_float.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail{

#ifndef _MSC_EXTENSIONS

//////////////////////////////////////
// hvec2

GLM_FUNC_QUALIFIER tvec2<thalf>::size_type tvec2<thalf>::value_size()
{
	return 2;
}

//////////////////////////////////////
// Accesses

GLM_FUNC_QUALIFIER thalf & tvec2<thalf>::operator[](tvec2<thalf>::size_type i)
{
	assert(/*i >= tvec2<thalf>::size_type(0) && */i < tvec2<thalf>::value_size());
	return (&x)[i];
}

GLM_FUNC_QUALIFIER thalf const & tvec2<thalf>::operator[](tvec2<thalf>::size_type i) const
{
	assert(/*i >= tvec2<thalf>::size_type(0) && */i < tvec2<thalf>::value_size());
	return (&x)[i];
}

//////////////////////////////////////
// Implicit basic constructors

GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2() :
	x(thalf(0.f)),
	y(thalf(0.f))
{}

GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	tvec2<thalf> const & v
) :
	x(v.x),
	y(v.y)
{}

//////////////////////////////////////
// Explicit basic constructors

GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	thalf const & s
) :
	x(s),
	y(s)
{}

GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	thalf const & s1, 
	thalf const & s2
) :
	x(s1),
	y(s2)
{}

//////////////////////////////////////
// Swizzle constructors

GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	tref2<thalf> const & r
) :
	x(r.x),
	y(r.y)
{}

//////////////////////////////////////
// Convertion scalar constructors

template <typename U> 
GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	U const & x
) :
	x(thalf(x)),
	y(thalf(x))
{}

template <typename U, typename V> 
GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	U const & x, 
	V const & y
) :
	x(thalf(x)),
	y(thalf(y))
{}

//////////////////////////////////////
// Convertion vector constructors

template <typename U> 
GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	tvec2<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y))
{}

template <typename U> 
GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(	
	tvec3<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y))
{}

template <typename U> 
GLM_FUNC_QUALIFIER tvec2<thalf>::tvec2
(
	tvec4<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y))
{}

//////////////////////////////////////
// Unary arithmetic operators

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator= 
(
	tvec2<thalf> const & v
)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator+=
(
	thalf const & s
)
{
	this->x += s;
	this->y += s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator+=
(
	tvec2<thalf> const & v
)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator-=
(
	thalf const & s
)
{
	this->x -= s;
	this->y -= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator-=
(
	tvec2<thalf> const & v
)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf>& tvec2<thalf>::operator*=
(
	thalf const & s
)
{
	this->x *= s;
	this->y *= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator*=
(
	tvec2<thalf> const & v
)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator/=
(
	thalf const & s
)
{
	this->x /= s;
	this->y /= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator/=
(
	tvec2<thalf> const & v
)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf> & tvec2<thalf>::operator++()
{
	++this->x;
	++this->y;
	return *this;
}

GLM_FUNC_QUALIFIER tvec2<thalf>& tvec2<thalf>::operator--()
{
	--this->x;
	--this->y;
	return *this;
}

//////////////////////////////////////
// Swizzle operators

GLM_FUNC_QUALIFIER thalf tvec2<thalf>::swizzle(comp x) const
{
	return (*this)[x];
}

GLM_FUNC_QUALIFIER tvec2<thalf> tvec2<thalf>::swizzle(comp x, comp y) const
{
	return tvec2<thalf>(
		(*this)[x],
		(*this)[y]);
}

GLM_FUNC_QUALIFIER tvec3<thalf> tvec2<thalf>::swizzle(comp x, comp y, comp z) const
{
	return tvec3<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z]);
}

GLM_FUNC_QUALIFIER tvec4<thalf> tvec2<thalf>::swizzle(comp x, comp y, comp z, comp w) const
{
	return tvec4<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z],
		(*this)[w]);
}

GLM_FUNC_QUALIFIER tref2<thalf> tvec2<thalf>::swizzle(comp x, comp y)
{
	return tref2<thalf>(
		(*this)[x],
		(*this)[y]);
}

//////////////////////////////////////
// hvec3

GLM_FUNC_QUALIFIER tvec3<thalf>::size_type tvec3<thalf>::value_size()
{
	return 3;
}

//////////////////////////////////////
// Accesses

GLM_FUNC_QUALIFIER thalf & tvec3<thalf>::operator[]
(
	tvec3<thalf>::size_type i
)
{
	assert(/*i >= tvec3<thalf>::size_type(0) &&*/ i < tvec3<thalf>::value_size());

	return (&x)[i];
}

GLM_FUNC_QUALIFIER thalf const & tvec3<thalf>::operator[]
(
	tvec3<thalf>::size_type i
) const
{
	assert(/*i >= tvec3<thalf>::size_type(0) &&*/ i < tvec3<thalf>::value_size());

	return (&x)[i];
}

//////////////////////////////////////
// Implicit basic constructors

GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3() :
	x(thalf(0)),
	y(thalf(0)),
	z(thalf(0))
{}

GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	tvec3<thalf> const & v
) :
	x(v.x),
	y(v.y),
	z(v.z)
{}

//////////////////////////////////////
// Explicit basic constructors

GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	thalf const & s
) :
	x(s),
	y(s),
	z(s)
{}

GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	thalf const & s0, 
	thalf const & s1, 
	thalf const & s2
) :
	x(s0),
	y(s1),
	z(s2)
{}

//////////////////////////////////////
// Swizzle constructors

GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	tref3<thalf> const & r
) :
	x(r.x),
	y(r.y),
	z(r.z)
{}

//////////////////////////////////////
// Convertion scalar constructors

template <typename U> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	U const & x
) :
	x(thalf(x)),
	y(thalf(x)),
	z(thalf(x))
{}

template <typename A, typename B, typename C> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	A const & x, 
	B const & y, 
	C const & z
) :
	x(thalf(x)),
	y(thalf(y)),
	z(thalf(z))
{}

//////////////////////////////////////
// Convertion vector constructors

template <typename A, typename B> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	tvec2<A> const & v, 
	B const & s
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(s))
{}

template <typename A, typename B> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	A const & s, 
	tvec2<B> const & v
) :
	x(thalf(s)),
	y(thalf(v.x)),
	z(thalf(v.y))
{}

template <typename U> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	tvec3<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(v.z))
{}

template <typename U> 
GLM_FUNC_QUALIFIER tvec3<thalf>::tvec3
(
	tvec4<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(v.z))
{}

//////////////////////////////////////
// Unary arithmetic operators

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator= 
(
	tvec3<thalf> const & v
)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator+=
(
	thalf const & s
)
{
	this->x += s;
	this->y += s;
	this->z += s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator+=
(
	tvec3<thalf> const & v
)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator-=
(
	thalf const & s
)
{
	this->x -= s;
	this->y -= s;
	this->z -= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator-=
(
	tvec3<thalf> const & v
)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator*=
(
	thalf const & s
)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator*=
(
	tvec3<thalf> const & v
)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator/=
(
	thalf const & s
)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator/=
(
	tvec3<thalf> const & v
)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator++()
{
	++this->x;
	++this->y;
	++this->z;
	return *this;
}

GLM_FUNC_QUALIFIER tvec3<thalf> & tvec3<thalf>::operator--()
{
	--this->x;
	--this->y;
	--this->z;
	return *this;
}

//////////////////////////////////////
// Swizzle operators

GLM_FUNC_QUALIFIER thalf tvec3<thalf>::swizzle(comp x) const
{
	return (*this)[x];
}

GLM_FUNC_QUALIFIER tvec2<thalf> tvec3<thalf>::swizzle(comp x, comp y) const
{
	return tvec2<thalf>(
		(*this)[x],
		(*this)[y]);
}

GLM_FUNC_QUALIFIER tvec3<thalf> tvec3<thalf>::swizzle(comp x, comp y, comp z) const
{
	return tvec3<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z]);
}

GLM_FUNC_QUALIFIER tvec4<thalf> tvec3<thalf>::swizzle(comp x, comp y, comp z, comp w) const
{
	return tvec4<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z],
		(*this)[w]);
}

GLM_FUNC_QUALIFIER tref3<thalf> tvec3<thalf>::swizzle(comp x, comp y, comp z)
{
	return tref3<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z]);
}

//////////////////////////////////////
// hvec4

GLM_FUNC_QUALIFIER tvec4<thalf>::size_type tvec4<thalf>::value_size()
{
	return 4;
}

//////////////////////////////////////
// Accesses

GLM_FUNC_QUALIFIER thalf & tvec4<thalf>::operator[]
(
	tvec4<thalf>::size_type i
)
{
	assert(/*i >= tvec4<thalf>::size_type(0) && */i < tvec4<thalf>::value_size());

	return (&x)[i];
}

GLM_FUNC_QUALIFIER thalf const & tvec4<thalf>::operator[]
(
	tvec4<thalf>::size_type i
) const
{
	assert(/*i >= tvec4<thalf>::size_type(0) && */i < tvec4<thalf>::value_size());

	return (&x)[i];
}

//////////////////////////////////////
// Implicit basic constructors

GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4() :
	x(thalf(0)),
	y(thalf(0)),
	z(thalf(0)),
	w(thalf(0))
{}

GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tvec4<thalf> const & v
) :
	x(v.x),
	y(v.y),
	z(v.z),
	w(v.w)
{}

//////////////////////////////////////
// Explicit basic constructors

GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	thalf const & s
) :
	x(s),
	y(s),
	z(s),
	w(s)
{}

GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	thalf const & s1, 
	thalf const & s2, 
	thalf const & s3, 
	thalf const & s4
) :
	x(s1),
	y(s2),
	z(s3),
	w(s4)
{}

//////////////////////////////////////
// Swizzle constructors

GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tref4<thalf> const & r
) :
	x(r.x),
	y(r.y),
	z(r.z),
	w(r.w)
{}

//////////////////////////////////////
// Convertion scalar constructors

template <typename U> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	U const & x
) :
	x(thalf(x)),
	y(thalf(x)),
	z(thalf(x)),
	w(thalf(x))
{}

template <typename A, typename B, typename C, typename D> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	A const & x, 
	B const & y, 
	C const & z, 
	D const & w
) :
	x(thalf(x)),
	y(thalf(y)),
	z(thalf(z)),
	w(thalf(w))
{}

//////////////////////////////////////
// Convertion vector constructors

template <typename A, typename B, typename C> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tvec2<A> const & v, 
	B const & s1, 
	C const & s2
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(s1)),
	w(thalf(s2))
{}

template <typename A, typename B, typename C> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	A const & s1, 
	tvec2<B> const & v, 
	C const & s2
) :
	x(thalf(s1)),
	y(thalf(v.x)),
	z(thalf(v.y)),
	w(thalf(s2))
{}

template <typename A, typename B, typename C> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	A const & s1, 
	B const & s2, 
	tvec2<C> const & v
) :
	x(thalf(s1)),
	y(thalf(s2)),
	z(thalf(v.x)),
	w(thalf(v.y))
{}

template <typename A, typename B> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tvec3<A> const & v, 
	B const & s
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(v.z)),
	w(thalf(s))
{}

template <typename A, typename B> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	A const & s, 
	tvec3<B> const & v
) :
	x(thalf(s)),
	y(thalf(v.x)),
	z(thalf(v.y)),
	w(thalf(v.z))
{}

template <typename A, typename B> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tvec2<A> const & v1, 
	tvec2<B> const & v2
) :
	x(thalf(v1.x)),
	y(thalf(v1.y)),
	z(thalf(v2.x)),
	w(thalf(v2.y))
{}

template <typename U> 
GLM_FUNC_QUALIFIER tvec4<thalf>::tvec4
(
	tvec4<U> const & v
) :
	x(thalf(v.x)),
	y(thalf(v.y)),
	z(thalf(v.z)),
	w(thalf(v.w))
{}

//////////////////////////////////////
// Unary arithmetic operators

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator= 
(
	tvec4<thalf> const & v
)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator+=
(
	thalf const & s
)
{
	this->x += s;
	this->y += s;
	this->z += s;
	this->w += s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator+=
(
	tvec4<thalf> const & v
)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator-=
(
	thalf const & s
)
{
	this->x -= s;
	this->y -= s;
	this->z -= s;
	this->w -= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator-=
(
	tvec4<thalf> const & v
)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator*=
(
	thalf const & s
)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator*=
(
	tvec4<thalf> const & v
)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator/=
(
	thalf const & s
)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator/=
(
	tvec4<thalf> const & v
)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator++()
{
	++this->x;
	++this->y;
	++this->z;
	++this->w;
	return *this;
}

GLM_FUNC_QUALIFIER tvec4<thalf>& tvec4<thalf>::operator--()
{
	--this->x;
	--this->y;
	--this->z;
	--this->w;
	return *this;
}

//////////////////////////////////////
// Swizzle operators

GLM_FUNC_QUALIFIER thalf tvec4<thalf>::swizzle(comp x) const
{
	return (*this)[x];
}

GLM_FUNC_QUALIFIER tvec2<thalf> tvec4<thalf>::swizzle(comp x, comp y) const
{
	return tvec2<thalf>(
		(*this)[x],
		(*this)[y]);
}

GLM_FUNC_QUALIFIER tvec3<thalf> tvec4<thalf>::swizzle(comp x, comp y, comp z) const
{
	return tvec3<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z]);
}

GLM_FUNC_QUALIFIER tvec4<thalf> tvec4<thalf>::swizzle(comp x, comp y, comp z, comp w) const
{
	return tvec4<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z],
		(*this)[w]);
}

GLM_FUNC_QUALIFIER tref4<thalf> tvec4<thalf>::swizzle(comp x, comp y, comp z, comp w)
{
	return tref4<thalf>(
		(*this)[x],
		(*this)[y],
		(*this)[z],
		(*this)[w]);
}

#endif//_MSC_EXTENSIONS

}//namespace detail
}//namespace glm
