#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace glwrap
{
	Texture::Texture()
	{
		int w = 0;
		int h = 0;
		int channels = 0;

		unsigned char *data = stbi_load("../images/Power.png", &w, &h, &channels, 4);

		if (!data)
		{
			throw std::exception();
		}
		m_size.x = w;
		m_size.y = h;

		// Create and bind a texture.

		glGenTextures(1, &m_id);
		if (!m_id)
		{
			throw std::exception();
		}

		glBindTexture(GL_TEXTURE_2D, m_id);

		// Upload the image data to the bound texture unit in the GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);

		// Free the loaded data because we now have a copy on the GPU
		free(data);

		// Generate Mipmap so the texture can be mapped correctly
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture because we are done operating on it
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(int width, int height, bool _base)
	{
		m_size.x = width;
		m_size.y = height;
	}

	Texture::Texture(std::string file)
	{
		int w = 0;
		int h = 0;
		int channels = 0;

		unsigned char *data = stbi_load(file.c_str(), &w, &h, &channels, 4);

		if (!data)
		{
			throw std::exception();
		}

		m_size.x = w;
		m_size.y = h;

		// Create and bind a texture.

		glGenTextures(1, &m_id);
		if (!m_id)
		{
			throw std::exception();
		}

		glBindTexture(GL_TEXTURE_2D, m_id);

		// Upload the image data to the bound texture unit in the GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);

		// Free the loaded data because we now have a copy on the GPU
		free(data);

		// Generate Mipmap so the texture can be mapped correctly
		glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture because we are done operating on it
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glm::vec2 Texture::getSize()
	{
		return m_size;
	}

	GLuint Texture::getId()
	{
		return m_id;
	}
}
