#include "vertex_array.h"
#include "glad/glad.h"

namespace ROGLL
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_arrayId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_arrayId);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_arrayId);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetBuffer(const VertexAttributes& attributes, const VertexBuffer& buffer)
	{
		Bind();
		buffer.Bind();

		auto attributesVector = attributes.GetAttributes();

		for (size_t i = 0; i < attributesVector.size(); i++)
		{
			auto attribute = attributesVector[i];

			glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized, attributes.GetStride(), (void*)0);
			glEnableVertexAttribArray(i);
		}
	}
}
