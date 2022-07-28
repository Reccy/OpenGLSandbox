#pragma once

namespace ROGLL
{
	class IndexBuffer
	{
	private:
		unsigned int m_bufferId;
	public:
		IndexBuffer(const void* data, const int size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}
