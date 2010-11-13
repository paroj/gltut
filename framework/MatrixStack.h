#ifndef FRAMEWORK_MATRIX_STACK_H
#define FRAMEWORK_MATRIX_STACK_H


#include <stack>
#include <glm/glm.hpp>

namespace Framework
{
	class MatrixStack
	{
	public:
		MatrixStack()
			: m_currMat(1.0f)
		{
		}

		const glm::mat4 &Top()
		{
			return m_currMat;
		}

		void Rotate(glm::vec3 &axisOfRotation, float fAngDeg);
		void RotateRadians(glm::vec3 &axisOfRotation, float fAngRad);
		void RotateX(float fAngDeg);
		void RotateY(float fAngDeg);
		void RotateZ(float fAngDeg);

		void Scale(const glm::vec3 &scaleVec);
		void Scale(float fScaleX, float fScaleY, float fScaleZ) {Scale(glm::vec3(fScaleX, fScaleY, fScaleZ));}
		void Translate(const glm::vec3 &offsetVec);
		void Translate(float fTransX, float fTransY, float fTransZ) {Translate(glm::vec3(fTransX, fTransY, fTransZ));}

		void ApplyMatrix(const glm::mat4 &theMatrix);
		void SetMatrix(const glm::mat4 &theMatrix);
		void SetIdentity();
		void Perspective(float fDegFOV, float fAspectRatio, float fZNear, float fZFar);

	private:
		glm::mat4 m_currMat;
		std::stack<glm::mat4> m_matrices;

		friend class MatrixStackPusher;

		void Push()
		{
			m_matrices.push(m_currMat);
		}

		void Pop()
		{
			m_currMat = m_matrices.top();
			m_matrices.pop();
		}
	};

	class MatrixStackPusher
	{
	public:
		MatrixStackPusher(MatrixStack &matrixStack)
			: m_stack(matrixStack)
		{
			m_stack.Push();
		}

		~MatrixStackPusher()
		{
			m_stack.Pop();
		}

	private:
		MatrixStack &m_stack;

		//Declared but not defined, so that it cannot be copy constructed.
		MatrixStackPusher(const MatrixStackPusher &);
		//Declared but not defined, so that it cannot be copy assigned.
		MatrixStackPusher &operator=(const MatrixStackPusher &);
	};
}



#endif //FRAMEWORK_MATRIX_STACK_H
