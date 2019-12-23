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
	public:
		Texture();
		Texture(int _width, int _height, bool _base);
		Texture(std::string _path);
		glm::vec2 getSize();
		GLuint getId();

	private:
		friend class RenderTexture;
		friend class DepthBuffer;
		friend class Context;

		GLuint m_id;
		glm::vec2 m_size;
		std::weak_ptr<Context> m_context;

	};
}
#endif