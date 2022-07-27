#pragma once
#include "glad/glad.h"
#include <vector>

namespace ROGLL
{
	class VertexAttributes
	{
	private:
		struct VertexAttribute
		{
			GLsizei count;
			GLenum type;
			GLboolean normalized;
		};

		GLsizei m_stride;
		std::vector<VertexAttribute> m_attributes;
	public:
		VertexAttributes();

		template<typename T>
		void Add(GLsizei count, GLboolean normalized = false);

		template<>
		void Add<float>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_FLOAT, normalized });
			m_stride += sizeof(GLfloat) * count;
		}

		template<>
		void Add<int>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_INT, normalized });
			m_stride += sizeof(GLint) * count;
		}

		template<>
		void Add<unsigned int>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_UNSIGNED_INT, normalized });
			m_stride += sizeof(GLuint) * count;
		}

		template<>
		void Add<char>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_BYTE, normalized });
			m_stride += sizeof(GLbyte) * count;
		}

		template<>
		void Add<unsigned char>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_UNSIGNED_BYTE, normalized });
			m_stride += sizeof(GLubyte) * count;
		}

		template<>
		void Add<short>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_SHORT, normalized });
			m_stride += sizeof(GLshort) * count;
		}

		template<>
		void Add<unsigned short>(GLsizei count, GLboolean normalized)
		{
			m_attributes.push_back({ count, GL_UNSIGNED_SHORT, normalized});
			m_stride += sizeof(GLushort) * count;
		}

		const std::vector<VertexAttribute>& GetAttributes() const;
		const GLsizei GetStride() const;
	};
}
