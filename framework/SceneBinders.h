
#ifndef FRAMEWORK_SCENE_BINDERS_H
#define FRAMEWORK_SCENE_BINDERS_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Framework
{
	class StateBinder
	{
	public:
		virtual ~StateBinder() {}

		//The current program will be in use when this is called.
		virtual void BindState() const = 0;

		//The current program will be in use when this is called.
		virtual void UnbindState() const = 0;
	};

	class UniformBinderBase : public StateBinder
	{
	public:
		UniformBinderBase() : m_unifLoc(-1) {}

		void AssociateWithProgram(GLuint prog, const std::string &unifName)
		{
			m_unifLoc = glGetUniformLocation(prog, unifName.c_str());
		}

	protected:
		GLint GetUniformLoc() const {return m_unifLoc;}

	private:
		GLint m_unifLoc;
	};

	class UniformVec4Binder : public UniformBinderBase
	{
	public:
		UniformVec4Binder()
			: m_val(0.0f, 0.0f, 0.0f, 0.0f)	{}

		void SetValue(const glm::vec4 &val)	{ m_val = val; }

		virtual void BindState() const
		{
			glUniform4fv(GetUniformLoc(), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState() const {}

	private:
		glm::vec4 m_val;
	};

	class UniformVec3Binder : public UniformBinderBase
	{
	public:
		UniformVec3Binder()
			: m_val(0.0f, 0.0f, 0.0f)	{}

		void SetValue(const glm::vec3 &val)	{ m_val = val; }

		virtual void BindState() const
		{
			glUniform3fv(GetUniformLoc(), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState() const {}

	private:
		glm::vec3 m_val;
	};

	class UniformVec2Binder : public UniformBinderBase
	{
	public:
		UniformVec2Binder()
			: m_val(0.0f, 0.0f)	{}

		void SetValue(const glm::vec2 &val)	{ m_val = val; }

		virtual void BindState() const
		{
			glUniform2fv(GetUniformLoc(), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState() const {}

	private:
		glm::vec2 m_val;
	};

	class UniformFloatBinder : public UniformBinderBase
	{
	public:
		UniformFloatBinder()
			: m_val(0.0f)	{}

		void SetValue(const float &val)	{ m_val = val; }

		virtual void BindState() const
		{
			glUniform1f(GetUniformLoc(), m_val);
		}

		virtual void UnbindState() const {}

	private:
		float m_val;
	};

	class UniformIntBinder : public UniformBinderBase
	{
	public:
		UniformIntBinder()
			: m_val(0)	{}

		void SetValue(const int &val)	{ m_val = val; }

		virtual void BindState() const
		{
			glUniform1i(GetUniformLoc(), m_val);
		}

		virtual void UnbindState() const {}

	private:
		int m_val;
	};

	class TextureBinder : public StateBinder
	{
	public:
		TextureBinder()
			: m_texUnit(0)
			, m_texType(GL_TEXTURE_2D)
			, m_texObj(0)
			, m_samplerObj(0)
		{}

		void SetTexture(GLuint texUnit, GLenum texType, GLuint texObj, GLuint samplerObj)
		{
			m_texUnit = texUnit;
			m_texType = texType;
			m_texObj = texObj;
			m_samplerObj = samplerObj;
		}

		virtual void BindState() const
		{
			glActiveTexture(GL_TEXTURE0 + m_texUnit);
			glBindTexture(m_texType, m_texObj);
			glBindSampler(m_texUnit, m_samplerObj);
		}

		virtual void UnbindState() const
		{
			glActiveTexture(GL_TEXTURE0 + m_texUnit);
			glBindTexture(m_texType, 0);
			glBindSampler(m_texUnit, 0);
		}

	private:
		GLuint m_texUnit;
		GLenum m_texType;
		GLuint m_texObj;
		GLuint m_samplerObj;
	};

	class UniformBlockBinder : public StateBinder
	{
	public:
		UniformBlockBinder();

		void SetBlock(GLuint blockIndex, GLuint unifBuffer,
			GLintptr buffOffset, GLsizeiptr buffSize)
		{
			m_blockIndex = blockIndex;
			m_unifBuffer = unifBuffer;
			m_buffOffset = buffOffset;
			m_buffSize = buffSize;
		}

		virtual void BindState() const
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, m_blockIndex, m_unifBuffer,
				m_buffOffset, m_buffSize);
		}

		virtual void UnbindState() const
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, m_blockIndex, 0);
		}

	private:
		GLuint m_blockIndex;
		GLuint m_unifBuffer;
		GLintptr m_buffOffset;
		GLsizeiptr m_buffSize;
	};


}



#endif //FRAMEWORK_SCENE_BINDERS_H
