#pragma once
#include <string>

namespace ROGLL
{
	class Texture
	{
	private:
		unsigned int m_id;
		std::string m_filePath;
		unsigned char* m_buffer;
		int m_width, m_height, m_bitsPerPixel;
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;
	};
}
