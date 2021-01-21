/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef GLSDK_MESH_MESH_H
#define GLSDK_MESH_MESH_H

/**
\file
\brief Defines the Mesh class and associated types for creating a Mesh. Include an OpenGL header before including this one.
**/

#include <memory>
#include <vector>
#include <map>
#include <string>

namespace glmesh
{
	///\addtogroup module_glmesh_mesh
	///@{

	///A list of variations of named variations of a mesh. Each name maps to a VAO to render from.
	typedef std::map<std::string, GLuint> MeshVariantMap;

	struct RenderCmdListData;

	/**
	\brief A list of rendering commands to be used by a Mesh.
	
	This class is part of the setup process for creating a Mesh. It stores a series of OpenGL
	rendering commands which will be used when rendering a particular Mesh. The series of commands
	will be used in the order given.

	Indexed rendering commands (`glDrawElements` and its ilk) will use the element buffer that is
	stored in the VAO used by the Mesh to render. You do not provide the element buffer to these
	functions.

	The rendering command functions mimic their OpenGL counterparts where possible.
	**/
	class RenderCmdList
	{
	public:
		///Creates an empty RenderCmdList.
		RenderCmdList();
		///Destroys the object.
		~RenderCmdList();

		RenderCmdList(class RenderCmdList &anOther);
		RenderCmdList& operator=(class RenderCmdList &anOther);

		/**
		\brief Adds a `glDrawArrays` command to the list of rendering commands.
		
		\param primitive The OpenGL primitive type to render.
		\param startIndex The first index in the vertex arrays to render.
		\param vertexCount The number of vertices to render.
		**/
		void DrawArrays(GLenum primitive, GLint startIndex, GLsizei vertexCount);

		/**
		\brief Adds a `glDrawElements`-style command to the list of rendering commands.

		If there is a currently set restart index (with PrimitiveRestartIndex(GLuint) ), then
		it will be rendered with that as the restart index.
		
		\param primitive The OpenGL primitive type to render.
		\param vertexCount The number of vertices to render.
		\param dataType The OpenGL data type of the indices (`GL_UNSIGNED_SHORT`, etc).
		\param byteOffset The offset from the beginning of the index buffer to where OpenGL will begin to pull data.
		\param baseVertex An integer offset to be added to each index before fetching from the buffer. The restart
		index check happens before adding \a baseVertex to the index.

		\note If you specify a non-zero \a baseVertex, then rendering with this command list will
		require OpenGL 3.2 or ARB_draw_elements_base_vertex. No exception will be thrown for lacking
		these features; the attempt to execute the rendering command will simply crash.
		**/
		void DrawElements(GLenum primitive, GLsizei vertexCount, GLenum dataType, GLintptr byteOffset,
			GLint baseVertex = 0);

		///Subsequent indexed rendering functions will not use a primitive restart index.
		void PrimitiveRestartIndex();

		/**
		\brief Subsequent indexed rendering functions will use the given index as the primitive restart index.

		The primitive restart index will affect all indexed rendering functions (like `glDrawElements`)
		until it is changed with a later call to this function. To stop using the restart index,
		use PrimitiveRestartIndex().

		\note If you specify a primitive restart index, then rendering with this command list will
		require OpenGL 3.0. No exception will be thrown for lacking this version; the attempt
		to execute the rendering command will simply crash.
		**/
		void PrimitiveRestartIndex(GLuint index);

	private:
		std::auto_ptr<RenderCmdListData> m_pData;

		friend class Mesh;
	};


	struct MeshData;

	/**
	\brief An object that represents a static collection of mesh data.

	Mesh objects are represent static mesh data.
	Mesh objects are composed of a VAO (which sets up all of the vertex attribute commands)
	coupled with a series of rendering commands, provided by a RenderCmdList.
	
	A Mesh can have multiple VAOs, each of which has a unique name. These named VAOs
	are called variants. The main VAO, which is unnamed, will be used when no name is given to render.
	All of the variants are rendered with the same sequence of rendering commands.

	This object owns the VAOs it is provided with, and it will delete them. It can also be given
	ownership of one or more buffer objects, which it will also delete when it is deleted. It does not
	use these buffer objects for any purpose other than to delete them.
	
	Rendering with this class (via any call to Render) will affect the following OpenGL state:

	\li The current VAO binding. After the call, it will be reset to 0.
	\li The current `GL_PRIMITIVE_RESTART` enable. After the call, it will be disabled.

	\note This class cannot be copied.

	\note This class requires OpenGL 3.2 or above. It can be used with OpenGL 3.0 so long as you don't
	use any rendering command that has a non-zero base vertex.

	\note You must ensure that the OpenGL context exists when Mesh's constructor is called.

	\todo Change the interface for Render() to use boost::optional strings and string_refs.
	**/
	class Mesh
	{
	public:
		/**
		\brief Creates a mesh, given a series of buffer objects, VAOs, and rendering commands.

		This class claims ownership of \em all OpenGL objects passed to it. Its destructor will delete
		every VAO and buffer object it is given. If you want to manage the lifetime of a buffer object
		elsewhere, do not pass it as a parameter. Your VAOs can still reference those buffers,
		but this class will not dig through VAOs to delete buffers stored in them.

		\param bufferObjects A series of buffer objects to be freed when this Mesh is destroyed.
		The same buffer object *must not* be in this array multiple times.
		\param mainVao The primary vertex array object, used when calling Render with no parameters.
		If it is 0, then the only way to render the mesh is with a named variant.
		\param renderCmds The series of rendering commands to be used to render this object. This sequence
		will be used for every variant.
		\param variants A std::map of named variants for the Mesh. It is legal to use the same VAOs for
		the \a mainVao and one of the variants, or between different variants.

		\todo bufferObjects should take an array_ref, not a vector.
		**/
		Mesh(const std::vector<GLuint> &bufferObjects, GLuint mainVao, const RenderCmdList &renderCmds,
			const MeshVariantMap &variants = MeshVariantMap());

		///Deletes all VAOs and buffer objects owned by this Mesh. The OpenGL context must still exist.
		~Mesh();

		///Renders the main VAO. Does nothing if there is no main VAO.
		void Render() const;

		///Renders a named variant. Does nothing if the named VAO does not exist.
		/// \todo Take a string_ref.
		void Render(const std::string &variantName) const;

		///Returns true if there is a main VAO.
		bool DoesMainExist() const;

		///Returns true if the named variant exists.
		/// \todo Take a string_ref.
		bool DoesVariantExist(const std::string &variantName) const;

	private:
		std::auto_ptr<MeshData> m_pData;

		Mesh(const Mesh&);
		Mesh &operator=(const Mesh&);

		void RenderWithCurrVao() const;
	};

	///@}
}



#endif //GLSDK_MESH_MESH_H
