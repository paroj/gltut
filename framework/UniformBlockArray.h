
#ifndef UNIFORM_BLOCK_ARRAY_H
#define UNIFORM_BLOCK_ARRAY_H

//To use this file, you must include one of the glload headers before including this.

#include <string.h>
#include <vector>

namespace Framework
{
	//This object can only be constructed after an OpenGL context has been created and initialized.
	template<typename UniformBlockObject, int arrayCount>
	class UniformBlockArray
	{
	public:
		UniformBlockArray()
			: m_storage()
			, m_blockOffset(0)
		{
			int uniformBufferAlignSize = 0;
			glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniformBufferAlignSize);

			m_blockOffset = sizeof(UniformBlockObject);
			m_blockOffset += uniformBufferAlignSize -
				(m_blockOffset % uniformBufferAlignSize);

			int sizeMaterialUniformBuffer = m_blockOffset * arrayCount;

			m_storage.resize(arrayCount * m_blockOffset, 0);
		}

		int size() const {return arrayCount;}

		//The array offset should be multiplied by the array index to get the offset
		//for a particular element.
		int GetArrayOffset() const {return m_blockOffset;}

		class BlockMemberReference
		{
		private:
			BlockMemberReference(UniformBlockArray &uboArray, int blockIndex)
				: m_array(uboArray)
				, m_blockIndex(blockIndex)
			{}

		public:
			~BlockMemberReference() {}

			operator UniformBlockObject () const
			{
				UniformBlockObject theObject;
				memcpy(&theObject,
					&m_array.m_storage[m_blockIndex * m_array.m_blockOffset],
					sizeof(UniformBlockObject));

				return theObject;
			}

			BlockMemberReference & operator=(const UniformBlockObject &input)
			{
				memcpy(&m_array.m_storage[m_blockIndex * m_array.m_blockOffset],
					&input, sizeof(UniformBlockObject));

				return *this;
			}


		private:
			UniformBlockArray &m_array;
			int m_blockIndex;

			friend class UniformBlockArray;
		};

		BlockMemberReference operator[] (size_t index)
		{
			assert(index < arrayCount);

			return BlockMemberReference(*this, index);
		}

		GLuint CreateBufferObject()
		{
			GLuint bufferObject;
			glGenBuffers(1, &bufferObject);
			glBindBuffer(GL_UNIFORM_BUFFER, bufferObject);
			glBufferData(GL_UNIFORM_BUFFER, m_storage.size(), &m_storage[0], GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			return bufferObject;
		}


	private:
		std::vector<GLubyte> m_storage;
		int m_blockOffset;
	};
}


#endif //UNIFORM_BLOCK_ARRAY_H
