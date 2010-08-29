#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <stack>
#include <glm/glm.hpp>

namespace Framework
{
	GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);

	class MatrixStack
	{
		MatrixStack()
			: m_currMat(1.0f)
		{
		}

		const glm::mat4 &Top()
		{
			return m_currMat;
		}

		void Rotate(glm::vec3 &axisOfRotation, float fAngDeg);
		void RotateX(float fAngDeg);
		void RotateY(float fAngDeg);
		void RotateZ(float fAngDeg);

		void Scale(const glm::vec3 &scaleVec);
		void Translate(const glm::vec3 &offsetVec);

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

#endif //FRAMEWORK_H
