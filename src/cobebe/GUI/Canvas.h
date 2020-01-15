#include <glwrap/glwrap.h>

namespace cobebe
{
	class Environment;
	class Core;
	class Texture;
	class Shader;

	class Canvas
	{
	public:
		void drawTexture(std::shared_ptr<Texture> _image,
			glm::vec3 _position, glm::vec3 _size);

	private:
		friend class Core;

		glm::mat4 m_projection;
		int m_currentWidth;
		int m_currentHeight;
		std::shared_ptr<Shader> m_staticShader;

		std::weak_ptr<Environment> m_environment;
		std::weak_ptr<Core> m_core; /// Pointer to games Core

		void setProjection();
		void onInit();

	};
}