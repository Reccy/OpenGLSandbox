#include "index_buffer.h"
#include "glad/glad.h"

namespace ROGLL
{
	IndexBuffer::IndexBuffer(const void* data, const int size)
	{
		glGenBuffers(1, &m_bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_bufferId);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
