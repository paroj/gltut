/** Copyright (C) 2011-2013 by Jason L. McKesson **/
/** This file is licensed by the MIT License. **/



#ifndef MATRIX_STACK_UTIL_H
#define MATRIX_STACK_UTIL_H

/**
\file
\brief Contains a \ref module_glutil_matrixstack "matrix stack and associated classes".
**/

#include <stack>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glutil
{
	///\addtogroup module_glutil_matrixstack
	///@{

	/**
	\brief Implements a stack for glm::mat4 transformations.

	A matrix stack is a sequence of transforms which you can preserve and restore as needed. The
	stack has the concept of a "current matrix", which can be retrieved with the Top() function.
	The top matrix can even be obtained as a float array. The pointer returned will remain valid until
	this object is destroyed (though its values will change when you modify the current matrix).
	This is useful for uploading matrices to OpenGL via
	[`glUniformMatrix4fv`](http://www.opengl.org/wiki/GLAPI/glUniform).

	The other functions will right-multiply a transformation matrix with the current matrix, thus
	changing the current matrix.

	The main power of the matrix stack is the ability to preserve and restore matrices in a stack fashion.
	The current matrix can be preserved on the stack with Push() and the most recently preserved matrix
	can be restored with Pop(). You must ensure that you do not Pop() more times than you Push(). Also,
	while this matrix stack does not have an explicit size limit, if you Push() more times than you Pop(),
	then you can eventually run out of memory (unless you create and destroy the MatrixStack every frame).

	The best way to manage the stack is to never use the Push() and Pop() methods directly.
	Instead, use the PushStack object to do all pushing and popping. That will ensure that
	overflows and underflows cannot not happen.
	**/
	class MatrixStack
	{
	public:
		///Initializes the matrix stack with the identity matrix.
		MatrixStack()
			: m_currMatrix(1)
		{}

		///Initializes the matrix stack with the given matrix.
		explicit MatrixStack(const glm::mat4 &initialMatrix)
			: m_currMatrix(initialMatrix)
		{}

		/**
		\name Stack Maintanence Functions

		These functions maintain the matrix stack. You must take care not to underflow or overflow the stack.
		**/
		///@{

		///Preserves the current matrix on the stack.
		void Push()
		{
			m_stack.push(m_currMatrix);
		}

		///Restores the most recently preserved matrix.
		void Pop()
		{
			m_currMatrix = m_stack.top();
			m_stack.pop();
		}

		/**
		\brief Restores the current matrix to the value of the most recently preserved matrix.
		
		This function does not affect the depth of the matrix stack.
		**/
		void Reset() { m_currMatrix = m_stack.top(); }

		///Retrieve the current matrix.
		const glm::mat4 &Top() const
		{
			return m_currMatrix;
		}
		///@}

		/**
		\name Rotation Matrix Functions

		These functions right-multiply the current matrix with a rotation matrix of some form.
		All rotation angles are counter-clockwise for an observer looking down the axis direction.
		If an observer is facing so that the axis of rotation is pointing directly towards the user,
		then positive angles will rotate counter-clockwise.
		**/
		///@{

		///Applies a rotation matrix about the given axis, with the given angle in degrees.
		void Rotate(const glm::vec3 axis, float angDegCCW);

		///Applies a rotation matrix about the given axis, with the given angle in radians.
		void RotateRadians(const glm::vec3 axis, float angRadCCW);

		///Applies a rotation matrix about the +X axis, with the given angle in degrees.
		void RotateX(float angDegCCW);
		///Applies a rotation matrix about the +Y axis, with the given angle in degrees.
		void RotateY(float angDegCCW);
		///Applies a rotation matrix about the +Z axis, with the given angle in degrees.
		void RotateZ(float angDegCCW);
		///@}

		/**
		\name Scale Matrix Functions

		These functions right-multiply the current matrix with a scaling matrix of some form.
		**/
		///@{

		///Applies a scale matrix, with the given glm::vec3 as the axis scales.
		void Scale(const glm::vec3 &scaleVec);
		///Applies a scale matrix, with the given values as the axis scales.
		void Scale(float scaleX, float scaleY, float scaleZ) {Scale(glm::vec3(scaleX, scaleY, scaleZ));}
		///Applies a uniform scale matrix.
		void Scale(float uniformScale) {Scale(glm::vec3(uniformScale));}
		///@}

		/**
		\name Translation Matrix Functions

		These functions right-multiply the current matrix with a translation matrix of some form.
		**/
		///@{

		///Applies a translation matrix, with the given glm::vec3 as the offset.
		void Translate(const glm::vec3 &offsetVec);
		///Applies a translation matrix, with the given X, Y and Z values as the offset.
		void Translate(float transX, float transY, float transZ) {Translate(glm::vec3(transX, transY, transZ));}
		///@}

		/**
		\name Camera Matrix Functions

		These functions right-multiply the current matrix with a matrix that transforms from a world space to
		the camera space expected by the Perspective() or Orthographic() functions.
		**/
		///@{

		/**
		\brief Applies a matrix that transforms to a camera-space defined by a position, a target in the world, and an up direction.
		
		\param cameraPos The world-space position of the camera.
		\param lookatPos The world-space position the camera should be facing. It should not be equal to \a cameraPos.
		\param upDir The world-space direction vector that should be considered up. The generated matrix will be bad
		if the up direction is along the same direction as the direction the camera faces (the direction between
		\a cameraPos and \a lookatPos).
		**/
		void LookAt(const glm::vec3 &cameraPos, const glm::vec3 &lookatPos, const glm::vec3 &upDir);
		///@}

		/**
		\name Projection Matrix Functions

		These functions right-multiply the current matrix with a projection matrix of some form. These
		functions all transform positions into the 4D homogeneous space expected by the output of
		OpenGL vertex shaders. As such, these can be used directly with GLSL shaders.

		The space that these matrices transform from is defined as follows. The pre-projection space,
		called camera space or eye space, has the camera/eye position at the origin. The camera faces down the
		-Z axis, so objects with larger negative Z values are farther away. +Y is up and +X is to the right.
		**/
		///@{

		/**
		\brief Applies a standard, OpenGL-style perspective projection matrix.

		\param degFOV The field of view. This is the angle in degrees between directly forward and the farthest
		visible point horizontally.
		\param aspectRatio The ratio of the width of the view area to the height.
		\param zNear The closest camera-space distance to the camera that can be seen.
		The projection will be clipped against this value. It cannot be negative or 0.0.
		\param zFar The farthest camera-space distance from the camera that can be seen.
		The projection will be clipped against this value. It must be larger than \a zNear.
		**/
		void Perspective(float degFOV, float aspectRatio, float zNear, float zFar);

		/**
		\brief Applies a standard, OpenGL-style orthographic projection matrix.

		\param left The left camera-space position in the X axis that will be captured within the projection.
		\param right The right camera-space position in the X axis that will be captured within the projection.
		\param bottom The bottom camera-space position in the Y axis that will be captured within the projection.
		\param top The top camera-space position in the Y axis that will be captured within the projection.
		\param zNear The front camera-space position in the Z axis that will be captured within the projection.
		\param zFar The rear camera-space position in the Z axis that will be captured within the projection.
		**/
		void Orthographic(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		/**
		\brief Applies an ortho matrix for pixel-accurate reproduction.

		A common use for orthographic projections is to create an ortho matrix that allows for pixel-accurate
		reproduction of textures. It allows you to provide vertices directly in window space.

		The camera space that this function creates can have the origin at the top-left (with +y going down)
		or bottom-left (with +y going up). Note that a top-left orientation will have to flip the Y coordinate,
		which means that the winding order of any triangles are reversed.

		The depth range is arbitrary and up to the user.

		\param size The size of the window space.
		\param depthRange The near and far depth range. The x coord is zNear, and the y coord is zFar.
		\param isTopLeft True if this should be top-left orientation, false if it should be bottom-left.
		**/
		void PixelPerfectOrtho(glm::ivec2 size, glm::vec2 depthRange, bool isTopLeft = true);
		///@}

		/**
		\name Matrix Application
		
		These functions right-multiply a user-provided matrix by the current matrix; the result
		becomes the new current matrix.
		**/
		///@{

		///Right-multiplies the current matrix with the given one, making the result new current matrix.
		void ApplyMatrix(const glm::mat4 &theMatrix);
		///Right-multiplies the current matrix with the given one, making the result new current matrix.
		MatrixStack &operator*=(const glm::mat4 &theMatrix) {ApplyMatrix(theMatrix); return *this;}
		///@}

		/**
		\name Matrix Setting
		
		These functions directly set the value of the current matrix, replacing the old value.
		Previously preserved matrices on the stack are unaffected.
		**/
		///@{

		///The given matrix becomes the current matrix.
		void SetMatrix(const glm::mat4 &theMatrix);
		///Sets the current matrix to the identity matrix.
		void SetIdentity();
		///@}

	private:
		std::stack<glm::mat4, std::vector<glm::mat4> > m_stack;
		glm::mat4 m_currMatrix;
	};

	/**
	\brief RAII-style object for pushing/popping MatrixStack objects.

	The constructor of this object pushes a MatrixStack, and its destructor will pop it.
	This technique is called <a href="http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization">RAII</a>;
	it ensures that, in the event of exceptions or other similar circumstances, the matrix stack will be pushed
	and popped. More importantly, if you add an early return statement in a block that didn't have one,
	you don't have to worry about the stack being in a malformed state.

	This object cannot be copied, so it cannot be returned from another function or otherwise passed around. And
	you shouldn't pass it around by reference.
	**/
	class PushStack
	{
	public:
		///Pushes the given MatrixStack.
		PushStack(MatrixStack &stack)
			: m_stack(stack)
		{
			m_stack.Push();
		}

		///Pops the MatrixStack that the constructor was given.
		~PushStack()
		{
			m_stack.Pop();
		}

		/**
		\brief Resets the current matrix of the MatrixStack to the value that was pushed in the constructor.

		This does not alter the stack depth. It just resets the matrix.
		**/
		void ResetStack()
		{
			m_stack.Reset();
		}

	private:
		MatrixStack &m_stack;

		PushStack(const PushStack &);
		PushStack &operator=(const PushStack&);
	};
	///@}
}



#endif //MATRIX_STACK_UTIL_H
