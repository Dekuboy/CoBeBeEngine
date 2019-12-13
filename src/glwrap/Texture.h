#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace glwrap
{
	class Context;
	class RenderTexture;
	class DepthBuffer;

	class Texture
	{
		friend class RenderTexture;
		friend class DepthBuffer;
		friend class Context;
	private:
		GLuint m_id;
		glm::vec2 m_size;
		std::weak_ptr<Context> m_context;

	public:
		Texture();
		Texture(int width, int height, bool _base);
		Texture(std::string file);
		glm::vec2 getSize();
		GLuint getId();

	};
}
#endif