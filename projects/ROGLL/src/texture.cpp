#include "texture.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"

namespace ROGLL
{
	Texture::Texture(const std::string& path) :
		m_id(0),
		m_filePath(path),
		m_buffer(nullptr),
		m_width(0),
		m_height(0),
		m_bitsPerPixel(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_buffer)
			stbi_image_free(m_buffer);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
