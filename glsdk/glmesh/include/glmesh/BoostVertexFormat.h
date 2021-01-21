/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_VERTEX_FORMAT_WITH_BOOST_H
#define GLSDK_MESH_VERTEX_FORMAT_WITH_BOOST_H

#include "VertexFormat.h"
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

namespace glmesh
{
	namespace _detail
	{

	}

	template<typename VertexType>
	VertexFormat GetFormatFromType();
}


#endif //GLSDK_MESH_VERTEX_FORMAT_WITH_BOOST_H
