
#ifndef FRAMEWORK_SCENE_BINDERS_H
#define FRAMEWORK_SCENE_BINDERS_H

#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"

namespace Framework
{
	class StateBinder
	{
	public:
		virtual ~StateBinder() {}

		//The current program will be in use when this is called.
		virtual void BindState(GLuint prog) const = 0;

		//The current program will be in use when this is called.
		virtual void UnbindState(GLuint prog) const = 0;
	};

	class UniformBinderBase : public StateBinder
	{
	public:
		UniformBinderBase() {}

		void AssociateWithProgram(GLuint prog, const std::string &unifName)
		{
			m_progUnifLoc[prog] = glGetUniformLocation(prog, unifName.c_str());
		}

	protected:
		GLint GetUniformLoc(GLuint prog) const
		{
			std::map<GLuint, GLint>::const_iterator loc = m_progUnifLoc.find(prog);
			if(loc == m_progUnifLoc.end())
				return -1;

			return loc->second;
		}

	private:
		std::map<GLuint, GLint> m_progUnifLoc;
	};

	class UniformVec4Binder : public UniformBinderBase
	{
	public:
		UniformVec4Binder()
			: m_val(0.0f, 0.0f, 0.0f, 0.0f)	{}

		void SetValue(const glm::vec4 &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniform4fv(GetUniformLoc(prog), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		glm::vec4 m_val;
	};

	class UniformVec3Binder : public UniformBinderBase
	{
	public:
		UniformVec3Binder()
			: m_val(0.0f, 0.0f, 0.0f)	{}

		void SetValue(const glm::vec3 &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniform3fv(GetUniformLoc(prog), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		glm::vec3 m_val;
	};

	class UniformVec2Binder : public UniformBinderBase
	{
	public:
		UniformVec2Binder()
			: m_val(0.0f, 0.0f)	{}

		void SetValue(const glm::vec2 &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniform2fv(GetUniformLoc(prog), 1, glm::value_ptr(m_val));
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		glm::vec2 m_val;
	};

	class UniformFloatBinder : public UniformBinderBase
	{
	public:
		UniformFloatBinder()
			: m_val(0.0f)	{}

		void SetValue(const float &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniform1f(GetUniformLoc(prog), m_val);
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		float m_val;
	};

	class UniformIntBinder : public UniformBinderBase
	{
	public:
		UniformIntBinder()
			: m_val(0)	{}

		void SetValue(const int &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniform1i(GetUniformLoc(prog), m_val);
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		int m_val;
	};

	class UniformMat4Binder : public UniformBinderBase
	{
	public:
		UniformMat4Binder()
			: m_val(1.0f)	{}

		void SetValue(const glm::mat4 &val)	{ m_val = val; }

		virtual void BindState(GLuint prog) const
		{
			glUniformMatrix4fv(GetUniformLoc(prog), 1, GL_FALSE, glm::value_ptr(m_val));
		}

		virtual void UnbindState(GLuint prog) const {}

	private:
		glm::mat4 m_val;
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

		virtual void BindState(GLuint prog) const
		{
			glActiveTexture(GL_TEXTURE0 + m_texUnit);
			glBindTexture(m_texType, m_texObj);
			glBindSampler(m_texUnit, m_samplerObj);
		}

		virtual void UnbindState(GLuint prog) const
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

		virtual void BindState(GLuint prog) const
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, m_blockIndex, m_unifBuffer,
				m_buffOffset, m_buffSize);
		}

		virtual void UnbindState(GLuint prog) const
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, m_blockIndex, 0);
		}

	private:
		GLuint m_blockIndex;
		GLuint m_unifBuffer;
		GLintptr m_buffOffset;
		GLsizeiptr m_buffSize;
	};

	template<typename NodeForwardIterator, typename AssociationBinder>
	void AssociateUniformWithNodes(NodeForwardIterator start, NodeForwardIterator final,
		AssociationBinder &binder, const std::string &unifName)
	{
		for(NodeForwardIterator currIt = start; currIt != final; ++currIt)
		{
			currIt->AssociateWithBinder(binder, unifName);
//			binder.AssociateWithProgram(currIt->GetProgram(), unifName);
		}
	}

	template<typename NodeForwardRange>
	void AssociateUniformWithNodes(const NodeForwardRange &range,
		UniformBinderBase &binder, const std::string &unifName)
	{
		AssociateUniformWithNodes(range.begin(), range.end(), binder, unifName);
	}

	template<typename NodeForwardIterator>
	void SetStateBinderWithNodes(NodeForwardIterator start, NodeForwardIterator final,
		StateBinder &binder)
	{
		for(NodeForwardIterator currIt = start; currIt != final; ++currIt)
		{
			currIt->SetStateBinder(&binder);
		}
	}

	template<typename NodeForwardRange>
	void SetStateBinderWithNodes(NodeForwardRange &range,
		StateBinder &binder)
	{
		SetStateBinderWithNodes(range.begin(), range.end(), binder);
	}
}



#endif //FRAMEWORK_SCENE_BINDERS_H
