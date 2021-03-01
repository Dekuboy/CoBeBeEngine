#ifndef _GLWRAP_TEXTURE
#define _GLWRAP_TEXTURE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace glwrap
{
	class Context;

	/**
	* \brief Holds information on a texture loaded into GL
	*/
	class Texture
	{
	public:
		Texture();
		Texture(int _width, int _height, bool _base);
		Texture(std::string _path);

		/**
		* \brief Retrieve the width and height of the Texture
		*/
		glm::vec2 getSize();
		/**
		* \brief Get the Texture Id
		*/
		GLuint getId();

	protected:
		friend class Context;

		GLuint m_id; //!< GL Id of Texture
		glm::vec2 m_size; //!< Width and height of Texture
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

	};
}
#endif