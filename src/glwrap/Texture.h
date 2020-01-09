#ifndef _GLWRAP_TEXTURE
#define _GLWRAP_TEXTURE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace glwrap
{
	class Context;

	class Texture
	{
	public:
		Texture();
		Texture(int _width, int _height, bool _base);
		Texture(std::string _path);
		glm::vec2 getSize();
		GLuint getId();

	protected:
		friend class Context;

		GLuint m_id;
		glm::vec2 m_size;
		std::weak_ptr<Context> m_context;

	};
}
#endif