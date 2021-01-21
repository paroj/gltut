/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_DRAW_WITH_BOOST_H
#define GLSDK_MESH_DRAW_WITH_BOOST_H

/**
\file

\brief Boost header for special Boost-based drawing functions.
**/

#include "Draw.h"
#include "VertexFormat.h"
#include "VertexWriter.h"
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

namespace glmesh
{
	namespace _detail
	{
		template<typename AttribType>
		struct AttribTypeTraits
		{
			typedef AttribType value_type;
		};

		template<typename T>
		struct AttribTypeTraits<glm::detail::tvec1<T> >
		{
			typedef T value_type;
		};

		template<typename T>
		struct AttribTypeTraits<glm::detail::tvec2<T> >
		{
			typedef T value_type;
		};

		template<typename T>
		struct AttribTypeTraits<glm::detail::tvec3<T> >
		{
			typedef T value_type;
		};

		template<typename T>
		struct AttribTypeTraits<glm::detail::tvec4<T> >
		{
			typedef T value_type;
		};


		template<typename Sink>
		struct WriteAttrib
		{
			WriteAttrib(VertexWriter<Sink> &drawable) : m_drawable(drawable) {}

			template<typename AttribType>
			void operator()(const AttribType &attribute) const
			{
			    typedef typename glmesh::_detail::AttribTypeTraits<AttribType>::value_type GccSucks;
				m_drawable.template Attrib<GccSucks>(attribute);
			}

		private:
			VertexWriter<Sink> &m_drawable;
		};
	}

	/**
	\brief A Boost.Fusion-based function for drawing attribute structs.

	Boost.Fusion makes it possible to compile-time iterate over boost::tuples,
	fusion::sequences, and similar types. With the use of certain Boost.Fusion
	preprocessor commands, it is also possible to iterate over plain structs.

	When using glmesh::Draw, if you have some struct that has vertex data, you normally must
	either write a function to send its vertex data to a glmesh::Draw object, or you must
	write it out manually at the location where you send vertex data. But if you
	store your vertex data in a struct that is a valid Boost.Fusion sequence, you can
	use this function to iterate over them.

	Here is an example:

	\code
	#include <boost/tuple/tuple.hpp>
	#include <boost/range.hpp>
	#include <boost/foreach.hpp>

	typedef boost::tuple<glm::hvec4, glm::detail::tvec4<GLubyte> > VertexType;

	VertexType vertexData[] = ... //Fill in array.

	//Draw the mesh.
	glmesh::Draw immMode(gl::TRIANGLES, boost::size(g_vertexData), vertexFormat, streamBuffer);
	BOOST_FOREACH(const VertexType &vertex, vertexData)
	{
	  glmesh::Attrib(immMode, vertex);
	}
	\endcode

	Here is a version that uses Boost.Fusion's struct adaptor utilities:

	\code
	#include <boost/fusion/adapted/struct/adapt_struct.hpp>
	#include <boost/fusion/include/adapt_struct.hpp>
	#include <boost/range.hpp>
	#include <boost/foreach.hpp>

	struct VertexType
	{
	  glm::hvec4 position;
	  glm::tvec4<GLubyte> color;
	};

	BOOST_FUSION_ADAPT_STRUCT(
	  VertexType,
	  (glm::hvec4, position)
	  (glm::detail::tvec4<GLubyte>, color))

	VertexType vertexData[] = ... //Fill in array.

	glmesh::Draw immMode(gl::TRIANGLES, boost::size(g_vertexData), vertexFormat, streamBuffer);
	BOOST_FOREACH(const VertexType &vertex, vertexData)
	{
	  glmesh::Attrib(immMode, vertex);
	}
	\endcode

	You can change the vertex type to match whatever you use. In the future, there may be a function
	that takes a Boost.Fusion type and converts it into a vertex format directly.

	\ingroup module_glmesh_draw

	**/
	template<typename Sink, typename VertexSequence>
	void Attrib(VertexWriter<Sink> &drawable, const VertexSequence &vertexData)
	{
		boost::fusion::for_each(vertexData, _detail::WriteAttrib<Sink>(drawable));
	}
}



#endif //GLSDK_MESH_DRAW_WITH_BOOST_H
